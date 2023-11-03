/*
  This file is part of t8code.
  t8code is a C library to manage a collection (a forest) of multiple
  connected adaptive space-trees of general element types in parallel.

  Copyright (C) 2010 The University of Texas System
  Written by Carsten Burstedde, Lucas C. Wilcox, and Tobin Isaac

  t8code is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  t8code is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with t8code; if not, write to the Free Software Foundation, Inc.,
  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
*/

#include <gtest/gtest.h>
#include <t8_eclass.h>
#include <t8_schemes/t8_default/t8_default_cxx.hxx>
#include <t8_schemes/t8_standalone/t8_standalone_cxx.hxx>

/* This program tests the consistency between the child_face and parent_face function of an element. */

/* *INDENT-OFF* */
class parent_child_face: public testing::TestWithParam<std::tuple<int, t8_eclass_t> > {
 public:
  /** recursive tests check something for all descendants of a starting element 
 * Checkfunction: iterate over all faces and determine the facechildren
 * Then iterate over those children and determine the childface corresponding to the parentface
 * Afterwards determine the parentface corresponding to the childface 
 * Check, that this is equal to the face that we started with
*/
  void
  check_element (const t8_element_t *elem)
  {
    int num_faces = ts->t8_element_num_faces (elem);
    t8_debugf ("num_faces %i:\n", num_faces);
    for (int iface = 0; iface < num_faces; iface++) {
      t8_debugf ("iface %i:\n", iface);
      /* Iterate over all faces and determine the facechildren*/
      int num_face_children = ts->t8_element_num_face_children (elem, iface);
      t8_element_t **children;
      children = T8_ALLOC (t8_element_t *, num_face_children);
      ts->t8_element_new (num_face_children, children);
      ts->t8_element_children_at_face (elem, iface, children, num_face_children, NULL);
      for (int ifacechild = 0; ifacechild < num_face_children; ifacechild++) {
        t8_debugf ("ifacechild: %i\n", ifacechild);
        /* Iterate over those children and determine the childface corresponding to the parentface */
        int childface = ts->t8_element_face_child_face (elem, iface, ifacechild);
        ASSERT_NE (childface, -1);
        /* Determine the parentface corresponding to the childface */
        int parentface = ts->t8_element_face_parent_face (children[ifacechild], childface);
        /* Check, that this is equal to the face that we started with */
        EXPECT_EQ (iface, parentface);
      }
      ts->t8_element_destroy (num_face_children, children);
      T8_FREE (children);
    }
  }
  /** recursive depth first search to iterate over all descendants of elem up to maxlvl */
  void
  check_recursive_dfs_to_max_lvl (t8_element_t *elem)
  {
    int level = ts->t8_element_level (elem);
    ASSERT_LE (level, maxlvl);
    ASSERT_LT (maxlvl, ts->t8_element_maxlevel ());

    check_element (elem);

    t8_debugf ("elem level %i:\n", ts->t8_element_level (elem));
    t8_debugf ("max level %i:\n", maxlvl);

    if (ts->t8_element_level (elem) < maxlvl) {
      t8_debugf ("iterate over children:\n");
      /* iterate over all children */
      int num_children = ts->t8_element_num_children (elem);
      for (int ichild = 0; ichild < num_children; ichild++) {
        ts->t8_element_child (elem, ichild, elem);
        check_recursive_dfs_to_max_lvl (elem);
        ts->t8_element_parent (elem, elem);
      }
    }
  }

 protected:
  void
  SetUp () override
  {
    auto params = GetParam ();
    int scheme_param = std::get<0> (params);
    switch (scheme_param) {
    case 0:
      scheme = t8_scheme_new_default_cxx ();
      break;
    case 1:
      scheme = t8_scheme_new_standalone_cxx ();
      break;
    default:
      SC_ABORT ("wrong scheme parameter!\n");
    }
    eclass = std::get<1> (params);
    ts = scheme->eclass_schemes[eclass];
  }
  void
  TearDown () override
  {
    t8_scheme_cxx_unref (&scheme);
  }
  t8_scheme_cxx *scheme;
  t8_eclass_t eclass;
  t8_eclass_scheme_c *ts;

  const int maxlvl = 3;
};

TEST_P (parent_child_face, test_recursive_upto_maxlvl)
{
  t8_element_t *root;
  ts->t8_element_new (1, &root);
  ts->t8_element_set_linear_id (root, 0, 0);
  check_recursive_dfs_to_max_lvl (root);
  ts->t8_element_destroy (1, &root);
}

auto allImplementations = ::testing::Combine (testing::Range (1, 2), testing::Range (T8_ECLASS_ZERO, T8_ECLASS_COUNT));
INSTANTIATE_TEST_SUITE_P (t8_gtest_pcf, parent_child_face, allImplementations);
/* *INDENT-ON* */
