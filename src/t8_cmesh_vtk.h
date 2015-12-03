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

/** file t8_cmesh_vtk.h
 */
/* TODO: document this file */

#ifndef T8_CMESH_VTK_H
#define T8_CMESH_VTK_H

#include <t8.h>
#include <t8_cmesh.h>

/* typedef and macros */

/* TODO: these macros need to be set by configure */
#ifndef T8_VTK_DOUBLES
#define T8_VTK_FLOAT_NAME "Float32"
#define T8_VTK_FLOAT_TYPE float
#else
#define T8_VTK_FLOAT_NAME "Float64"
#define T8_VTK_FLOAT_TYPE double
#endif

#ifndef T8_VTK_BINARY
#define T8_VTK_ASCII 1
#define T8_VTK_FORMAT_STRING "ascii"
#else
#define T8_VTK_FORMAT_STRING "binary"
#endif

#define T8_VTK_TOPIDX "Int32"

T8_EXTERN_C_BEGIN ();
/* function declarations */

int                 t8_cmesh_vtk_write_file (t8_cmesh_t cmesh,
                                             const char *fileprefix,
                                             double scale);

T8_EXTERN_C_END ();

#endif /* !T8_CMESH_VTK_H */
