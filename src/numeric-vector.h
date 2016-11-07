/* Copyright 2016 Guillaume Poirier-Morency <guillaumepoiriermorency@gmail.com>
 *
 * This file is part of Numeric-GLib.
 *
 * Numeric-GLib is free software: you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License as published by the Free
 * Software Foundation, either version 3 of the License, or (at your option) any
 * later version.
 *
 * Numeric-GLib is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for more
 * details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with Numeric-GLib.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <glib-object.h>

#include "numeric.h"

#ifndef NUMERIC_VECTOR_H
#define NUMERIC_VECTOR_H

G_BEGIN_DECLS

#define DEFINE_VECTOR_PROTOTYPE(ctype, type, twidth, vsize)                                                                                               \
typedef ctype             numeric_##type##_v##vsize __attribute__ ((vector_size (vsize)));                                                        \
GType                     numeric_##type##_v##vsize##_get_type ();                                                                                \
numeric_##type##_v##vsize numeric_##type##_v##vsize##_init     ();                                                                                \
numeric_##type##_v##vsize *numeric_##type##_v##vsize##_copy    (numeric_##type##_v##vsize *self);                                                                                \
void                      numeric_##type##_v##vsize##_free     (numeric_##type##_v##vsize *self);                                                                                \
void                      numeric_##type##_v##vsize##_set      (numeric_##type##_v##vsize *self, gsize offset, ctype val);                       \
ctype                     numeric_##type##_v##vsize##_get      (numeric_##type##_v##vsize *self, gsize offset);                                  \
void numeric_##type##_v##vsize##_add      (const numeric_##type##_v##vsize *x, const numeric_##type##_v##vsize *y, numeric_##type##_v##vsize *z); \
void numeric_##type##_v##vsize##_sub      (const numeric_##type##_v##vsize *x, const numeric_##type##_v##vsize *y, numeric_##type##_v##vsize *z); \
void numeric_##type##_v##vsize##_mul      (const numeric_##type##_v##vsize *x, const numeric_##type##_v##vsize *y, numeric_##type##_v##vsize *z); \
void numeric_##type##_v##vsize##_div      (const numeric_##type##_v##vsize *x, const numeric_##type##_v##vsize *y, numeric_##type##_v##vsize *z); \
void numeric_##type##_v##vsize##_neg      (const numeric_##type##_v##vsize *x,                                     numeric_##type##_v##vsize *z); \
void numeric_##type##_v##vsize##_eq       (const numeric_##type##_v##vsize *x, const numeric_##type##_v##vsize *y, numeric_##type##_v##vsize *z); \
void numeric_##type##_v##vsize##_ne       (const numeric_##type##_v##vsize *x, const numeric_##type##_v##vsize *y, numeric_##type##_v##vsize *z); \
void numeric_##type##_v##vsize##_lt       (const numeric_##type##_v##vsize *x, const numeric_##type##_v##vsize *y, numeric_##type##_v##vsize *z); \
void numeric_##type##_v##vsize##_le       (const numeric_##type##_v##vsize *x, const numeric_##type##_v##vsize *y, numeric_##type##_v##vsize *z); \
void numeric_##type##_v##vsize##_gt       (const numeric_##type##_v##vsize *x, const numeric_##type##_v##vsize *y, numeric_##type##_v##vsize *z); \
void numeric_##type##_v##vsize##_ge       (const numeric_##type##_v##vsize *x, const numeric_##type##_v##vsize *y, numeric_##type##_v##vsize *z); \
void numeric_##type##_v##vsize##_shuffle  (const numeric_##type##_v##vsize *x, const numeric_int##twidth##_v##vsize *mask, numeric_##type##_v##vsize *z); \
void numeric_##type##_v##vsize##_shuffle2 (const numeric_##type##_v##vsize *x, const numeric_##type##_v##vsize *y, const numeric_int##twidth##_v##vsize *mask, numeric_##type##_v##vsize *z);

#define DEFINE_INT_VECTOR_PROTOTYPE(ctype, type, twidth, vsize)                                                                                           \
DEFINE_VECTOR_PROTOTYPE (ctype, type, twidth, vsize) \
void numeric_##type##_v##vsize##_xor      (const numeric_##type##_v##vsize *x, const numeric_##type##_v##vsize *y, numeric_##type##_v##vsize *z); \
void numeric_##type##_v##vsize##_or       (const numeric_##type##_v##vsize *x, const numeric_##type##_v##vsize *y, numeric_##type##_v##vsize *z); \
void numeric_##type##_v##vsize##_and      (const numeric_##type##_v##vsize *x, const numeric_##type##_v##vsize *y, numeric_##type##_v##vsize *z); \
void numeric_##type##_v##vsize##_not      (const numeric_##type##_v##vsize *x,                                     numeric_##type##_v##vsize *z); \
void numeric_##type##_v##vsize##_mod      (const numeric_##type##_v##vsize *x, const numeric_##type##_v##vsize *y, numeric_##type##_v##vsize *z); \
void numeric_##type##_v##vsize##_lshift   (const numeric_##type##_v##vsize *x, const numeric_##type##_v##vsize *y, numeric_##type##_v##vsize *z); \
void numeric_##type##_v##vsize##_rshift   (const numeric_##type##_v##vsize *x, const numeric_##type##_v##vsize *y, numeric_##type##_v##vsize *z); \
void numeric_##type##_v##vsize##_rshift   (const numeric_##type##_v##vsize *x, const numeric_##type##_v##vsize *y, numeric_##type##_v##vsize *z); \

DEFINE_INT_VECTOR_PROTOTYPE (gint8, int8, 8, 2);
DEFINE_INT_VECTOR_PROTOTYPE (gint8, int8, 8, 4);
DEFINE_INT_VECTOR_PROTOTYPE (gint8, int8, 8, 8);
DEFINE_INT_VECTOR_PROTOTYPE (gint8, int8, 8, 16);

DEFINE_INT_VECTOR_PROTOTYPE (guint8, uint8, 8, 2);
DEFINE_INT_VECTOR_PROTOTYPE (guint8, uint8, 8, 4);
DEFINE_INT_VECTOR_PROTOTYPE (guint8, uint8, 8, 8);
DEFINE_INT_VECTOR_PROTOTYPE (guint8, uint8, 8, 16);

DEFINE_INT_VECTOR_PROTOTYPE (gint16, int16, 16, 4);
DEFINE_INT_VECTOR_PROTOTYPE (gint16, int16, 16, 8);
DEFINE_INT_VECTOR_PROTOTYPE (gint16, int16, 16, 16);

DEFINE_INT_VECTOR_PROTOTYPE (guint16, uint16, 16, 4);
DEFINE_INT_VECTOR_PROTOTYPE (guint16, uint16, 16, 8);
DEFINE_INT_VECTOR_PROTOTYPE (guint16, uint16, 16, 16);

DEFINE_INT_VECTOR_PROTOTYPE (gint32, int32, 32, 4);
DEFINE_INT_VECTOR_PROTOTYPE (gint32, int32, 32, 8);
DEFINE_INT_VECTOR_PROTOTYPE (gint32, int32, 32, 16);

DEFINE_INT_VECTOR_PROTOTYPE (guint32, uint32, 32, 4);
DEFINE_INT_VECTOR_PROTOTYPE (guint32, uint32, 32, 8);
DEFINE_INT_VECTOR_PROTOTYPE (guint32, uint32, 32, 16);

DEFINE_INT_VECTOR_PROTOTYPE (gint64, int64, 64, 8);
DEFINE_INT_VECTOR_PROTOTYPE (gint64, int64, 64, 16);

DEFINE_INT_VECTOR_PROTOTYPE (guint64, uint64, 64, 8);
DEFINE_INT_VECTOR_PROTOTYPE (guint64, uint64, 64, 16);

DEFINE_VECTOR_PROTOTYPE (gfloat, float, 32, 4);
DEFINE_VECTOR_PROTOTYPE (gfloat, float, 32, 8);
DEFINE_VECTOR_PROTOTYPE (gfloat, float, 32, 16);

DEFINE_VECTOR_PROTOTYPE (gdouble, double, 64, 8);
DEFINE_VECTOR_PROTOTYPE (gdouble, double, 64, 16);

#define NUMERIC_TYPE_INT32_V16 numeric_int32_v16_get_type ()

G_END_DECLS

#endif
