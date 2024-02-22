/*
  This file is part of t8code.
  t8code is a C library to manage a collection (a forest) of multiple
  connected adaptive space-trees of general element classes in parallel.

  Copyright (C) 2015 the developers

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

#include <t8_schemes/t8_default/t8_default_common/t8_default_common_cxx.hxx>
#include <t8_schemes/t8_default/t8_default_vertex/t8_default_vertex_cxx.hxx>
#include <t8_schemes/t8_default/t8_default_vertex/t8_dvertex_bits.h>

/* We want to export the whole implementation to be callable from "C" */
T8_EXTERN_C_BEGIN ();

int
t8_default_scheme_vertex_c::t8_element_maxlevel (void) const
{
  return T8_DVERTEX_MAXLEVEL;
}

int
t8_default_scheme_vertex_c::t8_element_level (const t8_element_t *elem) const
{
  T8_ASSERT (t8_element_is_valid (elem));
  return t8_dvertex_get_level ((const t8_dvertex_t *) elem);
}

t8_eclass_t
t8_default_scheme_vertex_c::t8_element_child_eclass (int childid) const
{
  T8_ASSERT (childid == 0);
  return T8_ECLASS_VERTEX;
}

void
t8_default_scheme_vertex_c::t8_element_copy (const t8_element_t *source, t8_element_t *dest) const
{
  T8_ASSERT (t8_element_is_valid (source));
  T8_ASSERT (t8_element_is_valid (dest));
  t8_dvertex_copy ((const t8_dvertex_t *) source, (t8_dvertex_t *) dest);
}

int
t8_default_scheme_vertex_c::t8_element_compare (const t8_element_t *elem1, const t8_element_t *elem2) const
{
  return t8_dvertex_compare ((const t8_dvertex_t *) elem1, (const t8_dvertex_t *) elem2);
}

int
t8_default_scheme_vertex_c::t8_element_equal (const t8_element_t *elem1, const t8_element_t *elem2) const
{
  return t8_dvertex_equal ((const t8_dvertex_t *) elem1, (const t8_dvertex_t *) elem2);
}

void
t8_default_scheme_vertex_c::t8_element_parent (const t8_element_t *elem, t8_element_t *parent) const
{
  const t8_dvertex_t *v = (const t8_dvertex_t *) elem;
  t8_dvertex_t *p = (t8_dvertex_t *) parent;

  T8_ASSERT (t8_element_is_valid (elem));
  T8_ASSERT (t8_element_is_valid (parent));
  t8_dvertex_parent (v, p);
}

void
t8_default_scheme_vertex_c::t8_element_sibling (const t8_element_t *elem, int sibid, t8_element_t *sibling) const
{
  const t8_dvertex_t *v = (const t8_dvertex_t *) elem;
  t8_dvertex_t *s = (t8_dvertex_t *) sibling;

  T8_ASSERT (t8_element_is_valid (elem));
  T8_ASSERT (t8_element_is_valid (sibling));
  t8_dvertex_sibling (v, sibid, s);
}

int
t8_default_scheme_vertex_c::t8_element_num_faces (const t8_element_t *elem) const
{
  T8_ASSERT (t8_element_is_valid (elem));
  return T8_DVERTEX_FACES;
}

int
t8_default_scheme_vertex_c::t8_element_max_num_faces (const t8_element_t *elem) const
{
  return T8_DVERTEX_FACES;
}

int
t8_default_scheme_vertex_c::t8_element_num_children (const t8_element_t *elem) const
{
  T8_ASSERT (t8_element_is_valid (elem));
  return T8_DVERTEX_CHILDREN;
}

int
t8_default_scheme_vertex_c::t8_element_num_face_children (const t8_element_t *elem, int face) const
{
  T8_ASSERT (t8_element_is_valid (elem));
  return T8_DVERTEX_FACE_CHILDREN;
}

void
t8_default_scheme_vertex_c::t8_element_child (const t8_element_t *elem, int childid, t8_element_t *child) const
{
  const t8_dvertex_t *v = (const t8_dvertex_t *) elem;
  t8_dvertex_t *c = (t8_dvertex_t *) child;
  T8_ASSERT (t8_element_is_valid (elem));
  T8_ASSERT (t8_element_is_valid (child));

  T8_ASSERT (childid == 0);
  t8_dvertex_child (v, c);
}

void
t8_default_scheme_vertex_c::t8_element_children (const t8_element_t *elem, int length, t8_element_t *c[]) const
{
  T8_ASSERT (length == T8_DVERTEX_CHILDREN);
  T8_ASSERT (t8_element_is_valid (elem));
#ifdef T8_ENABLE_DEBUG
  int i;
  for (i = 0; i < T8_DVERTEX_CHILDREN; i++) {
    T8_ASSERT (t8_element_is_valid (c[i]));
  }
#endif
  t8_dvertex_childrenpv ((const t8_dvertex_t *) elem, (t8_dvertex_t **) c);
}

int
t8_default_scheme_vertex_c::t8_element_child_id (const t8_element_t *elem) const
{
  T8_ASSERT (t8_element_is_valid (elem));
  return t8_dvertex_child_id ((const t8_dvertex_t *) elem);
}

int
t8_default_scheme_vertex_c::t8_element_ancestor_id (const t8_element_t *elem, int level) const
{
  return t8_dvertex_ancestor_id ((const t8_dvertex_t *) elem, level);
}

int
t8_default_scheme_vertex_c::t8_element_is_family (t8_element_t **fam) const
{
#ifdef T8_ENABLE_DEBUG
  int i;
  for (i = 0; i < T8_DVERTEX_CHILDREN; i++) {
    T8_ASSERT (t8_element_is_valid (fam[i]));
  }
#endif
  return t8_dvertex_is_familypv ((const t8_dvertex_t **) fam);
}

void
t8_default_scheme_vertex_c::t8_element_nca (const t8_element_t *elem1, const t8_element_t *elem2,
                                            t8_element_t *nca) const
{
  const t8_dvertex_t *v1 = (const t8_dvertex_t *) elem1;
  const t8_dvertex_t *v2 = (const t8_dvertex_t *) elem2;
  t8_dvertex_t *c = (t8_dvertex_t *) nca;

  T8_ASSERT (t8_element_is_valid (elem1));
  T8_ASSERT (t8_element_is_valid (elem2));
  t8_dvertex_nearest_common_ancestor (v1, v2, c);
}

/** Transform the coordinates of a vertex considered as boundary element
 *  in a tree-tree connection. */
void
t8_default_scheme_vertex_c::t8_element_transform_face (const t8_element_t *elem1, t8_element_t *elem2, int orientation,
                                                       int sign, int is_smaller_face) const
{
  T8_ASSERT (t8_element_is_valid (elem1));
  T8_ASSERT (t8_element_is_valid (elem2));

  t8_dvertex_transform_face ((const t8_dvertex_t *) elem1, (t8_dvertex_t *) elem2);
}

int
t8_default_scheme_vertex_c::t8_element_is_root_boundary (const t8_element_t *elem, int face) const
{
  const t8_dvertex_t *v = (const t8_dvertex_t *) elem;

  T8_ASSERT (t8_element_is_valid (elem));
  return t8_dvertex_is_root_boundary (v, face);
}

void
t8_default_scheme_vertex_c::t8_element_anchor (const t8_element_t *elem, int anchor[3]) const
{
  T8_ASSERT (t8_element_is_valid (elem));

  anchor[0] = 0;
  anchor[1] = 0;
  anchor[2] = 0;
}

void
t8_default_scheme_vertex_c::t8_element_vertex_coords (const t8_element_t *elem, int vertex, int coords[]) const
{
  T8_ASSERT (t8_element_is_valid (elem));
  t8_dvertex_vertex_coords ((const t8_dvertex_t *) elem, vertex, coords);
}

/** Compute the coordinates of a given element vertex inside a reference tree
   *  that is embedded into [0,1]^d (d = dimension).
   *   \param [in] elem    The element.
   *   \param [in] vertex  The id of the vertex whose coordinates shall be computed.
   *   \param [out] coords An array of at least as many doubles as the element's dimension
   *                      whose entries will be filled with the coordinates of \a vertex.
   */
void
t8_default_scheme_vertex_c::t8_element_vertex_reference_coords (const t8_element_t *elem, const int vertex,
                                                                double coords[]) const
{
  T8_ASSERT (t8_element_is_valid (elem));
  T8_ASSERT (vertex == 0);

  t8_dvertex_vertex_ref_coords ((const t8_dvertex_t *) elem, vertex, coords);
}

void
t8_default_scheme_vertex_c::t8_element_reference_coords (const t8_element_t *elem, const double *ref_coords,
                                                         const size_t num_coords, double *out_coords) const
{
  T8_ASSERT (t8_element_is_valid (elem));
  t8_dvertex_compute_reference_coords ((const t8_dvertex_t *) elem, ref_coords, num_coords, out_coords);
}

#ifdef T8_ENABLE_DEBUG
int
t8_default_scheme_vertex_c::t8_element_is_valid (const t8_element_t *elem) const

{
  return t8_dvertex_is_valid ((const t8_dvertex_t *) elem);
}

void
t8_default_scheme_vertex_c::t8_element_to_string (const t8_element_t *elem, char *debug_string,
                                                  const int string_size) const
{
  T8_ASSERT (t8_element_is_valid (elem));
  T8_ASSERT (debug_string != NULL);
  t8_dvertex_t *vertex = (t8_dvertex_t *) elem;
  snprintf (debug_string, string_size, "level: %i", vertex->level);
}
#endif

int
t8_default_scheme_vertex_c::t8_element_refines_irregular () const
{
  /*vertices refine regularly */
  return 0;
}

void
t8_default_scheme_vertex_c::t8_element_new (int length, t8_element_t **elem) const
{
  /* allocate memory for a vertex */
  t8_default_scheme_common_c::t8_element_new (length, elem);

  /* in debug mode, set sensible default values. */
#ifdef T8_ENABLE_DEBUG
  {
    int i;
    for (i = 0; i < length; i++) {
      t8_element_init (1, elem[i], 0);
    }
  }
#endif
}

void
t8_default_scheme_vertex_c::t8_element_init (int length, t8_element_t *elem, int new_called) const
{
#ifdef T8_ENABLE_DEBUG
  if (!new_called) {
    int i;
    t8_dvertex_t *vertexs = (t8_dvertex_t *) elem;
    for (i = 0; i < length; i++) {
      t8_dvertex_init (vertexs + i);
    }
  }
#endif
}

/* Constructor */
t8_default_scheme_vertex_c::t8_default_scheme_vertex_c (void)
  : t8_default_scheme_common_c (T8_ECLASS_VERTEX, sizeof (t8_dvertex_t))
{
}

/* Destructor */
t8_default_scheme_vertex_c::~t8_default_scheme_vertex_c ()
{
  /* This destructor is empty since the destructor of the
   * default_common scheme is called automatically and it
   * suffices to destroy the quad_scheme.
   * However we need to provide an implementation of the destructor
   * and hence this empty function. */
}
void
t8_default_scheme_vertex_c::t8_element_root (t8_element_t *elem) const
{
  t8_dvertex_t *vertex = (t8_dvertex_t *) elem;
  vertex->level = 0;
}
T8_EXTERN_C_END ();
