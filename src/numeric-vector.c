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

#include "numeric-vector.h"

#include <string.h>

#define DEFINE_VECTOR(ctype, type, twidth, vsize)                                      \
G_DEFINE_BOXED_TYPE (numeric_##type##_v##vsize,                                \
                     numeric_##type##_v##vsize,                                \
                     numeric_##type##_v##vsize##_copy,                         \
                     numeric_##type##_v##vsize##_free)                         \
numeric_##type##_v##vsize                                                      \
numeric_##type##_v##vsize##_init     ()                                        \
{                                                                              \
    numeric_##type##_v##vsize _ = {};                                          \
    return _;                                                                  \
}                                                                              \
numeric_##type##_v##vsize *                                                    \
numeric_##type##_v##vsize##_copy     (numeric_##type##_v##vsize *self)         \
{                                                                              \
    gpointer ptr = g_malloc (sizeof (numeric_##type##_v##vsize));              \
    memcpy (ptr, self, sizeof (numeric_##type##_v##vsize));                    \
    return ptr;                                                                \
}                                                                              \
void                                                                           \
numeric_##type##_v##vsize##_free     (numeric_##type##_v##vsize *self)         \
{                                                                              \
    g_free (self);                                                             \
}                                                                              \
ctype                                                                          \
numeric_##type##_v##vsize##_get      (numeric_##type##_v##vsize       *self,   \
                                      gsize                            offset) \
{                                                                              \
    return (*self)[offset];                                                    \
}                                                                              \
void                                                                           \
numeric_##type##_v##vsize##_set      (numeric_##type##_v##vsize       *self,   \
                                      gsize                            offset, \
                                      ctype                            val)    \
{                                                                              \
    (*self)[offset] = val;                                                     \
}                                                                              \
void                                                                           \
numeric_##type##_v##vsize##_add      (const numeric_##type##_v##vsize *x,      \
                                      const numeric_##type##_v##vsize *y,      \
                                      numeric_##type##_v##vsize       *z)      \
{                                                                              \
    *z = *x + *y;                                                              \
}                                                                              \
void                                                                           \
numeric_##type##_v##vsize##_sub      (const numeric_##type##_v##vsize *x,      \
                                      const numeric_##type##_v##vsize *y,      \
                                      numeric_##type##_v##vsize       *z)      \
{                                                                              \
    *z = *x - *y;                                                              \
}                                                                              \
void                                                                           \
numeric_##type##_v##vsize##_mul      (const numeric_##type##_v##vsize *x,      \
                                      const numeric_##type##_v##vsize *y,      \
                                      numeric_##type##_v##vsize       *z)      \
{                                                                              \
    *z = *x * *y;                                                              \
}                                                                              \
void                                                                           \
numeric_##type##_v##vsize##_div      (const numeric_##type##_v##vsize *x,      \
                                      const numeric_##type##_v##vsize *y,      \
                                      numeric_##type##_v##vsize       *z)      \
{                                                                              \
    *z = *x / *y;                                                              \
}                                                                              \
void                                                                           \
numeric_##type##_v##vsize##_neg      (const numeric_##type##_v##vsize *x,      \
                                      numeric_##type##_v##vsize       *z)      \
{                                                                              \
    *z = -*x;                                                                  \
}                                                                              \
void                                                                           \
numeric_##type##_v##vsize##_eq       (const numeric_##type##_v##vsize *x,      \
                                      const numeric_##type##_v##vsize *y,      \
                                      numeric_##type##_v##vsize       *z)      \
{                                                                              \
    *z = *x == *y;                                                             \
}                                                                              \
void                                                                           \
numeric_##type##_v##vsize##_ne       (const numeric_##type##_v##vsize *x,      \
                                      const numeric_##type##_v##vsize *y,      \
                                      numeric_##type##_v##vsize       *z)      \
{                                                                              \
    *z = *x != *y;                                                             \
}                                                                              \
void                                                                           \
numeric_##type##_v##vsize##_lt       (const numeric_##type##_v##vsize *x,      \
                                      const numeric_##type##_v##vsize *y,      \
                                      numeric_##type##_v##vsize       *z)      \
{                                                                              \
    *z = *x < *y;                                                              \
}                                                                              \
void                                                                           \
numeric_##type##_v##vsize##_le       (const numeric_##type##_v##vsize *x,      \
                                      const numeric_##type##_v##vsize *y,      \
                                      numeric_##type##_v##vsize       *z)      \
{                                                                              \
    *z = *x <= *y;                                                             \
}                                                                              \
void                                                                           \
numeric_##type##_v##vsize##_gt       (const numeric_##type##_v##vsize *x,      \
                                      const numeric_##type##_v##vsize *y,      \
                                      numeric_##type##_v##vsize       *z)      \
{                                                                              \
    *z = *x <= *y;                                                             \
}                                                                              \
void                                                                           \
numeric_##type##_v##vsize##_ge       (const numeric_##type##_v##vsize *x,      \
                                      const numeric_##type##_v##vsize *y,      \
                                      numeric_##type##_v##vsize       *z)      \
{                                                                              \
    *z = *x <= *y;                                                             \
}                                                                              \
void                                                                           \
numeric_##type##_v##vsize##_shuffle  (const numeric_##type##_v##vsize *x,      \
                                      const numeric_int##twidth##_v##vsize *mask,   \
                                      numeric_##type##_v##vsize       *z)      \
{                                                                              \
    *z = __builtin_shuffle (*x, *mask);                                        \
}                                                                              \
void                                                                           \
numeric_##type##_v##vsize##_shuffle2 (const numeric_##type##_v##vsize *x,      \
                                      const numeric_##type##_v##vsize *y,      \
                                      const numeric_int##twidth##_v##vsize *mask,   \
                                      numeric_##type##_v##vsize       *z)      \
{                                                                              \
    *z = __builtin_shuffle (*x, *y, *mask);                                    \
}

#define DEFINE_INT_VECTOR(ctype, type, twidth, vsize) \
DEFINE_VECTOR (ctype, type, twidth, vsize)

DEFINE_INT_VECTOR (gint8, int8, 8, 2)
DEFINE_INT_VECTOR (gint8, int8, 8, 4)
DEFINE_INT_VECTOR (gint8, int8, 8, 8)
DEFINE_INT_VECTOR (gint8, int8, 8, 16)

DEFINE_INT_VECTOR (guint8, uint8, 8, 2)
DEFINE_INT_VECTOR (guint8, uint8, 8, 4)
DEFINE_INT_VECTOR (guint8, uint8, 8, 8)
DEFINE_INT_VECTOR (guint8, uint8, 8, 16)

DEFINE_INT_VECTOR (gint16,  int16,  16, 4)
DEFINE_INT_VECTOR (gint16,  int16,  16, 8)
DEFINE_INT_VECTOR (gint16,  int16,  16, 16)

DEFINE_INT_VECTOR (guint16, uint16, 16, 4)
DEFINE_INT_VECTOR (guint16, uint16, 16, 8)
DEFINE_INT_VECTOR (guint16, uint16, 16, 16)

DEFINE_INT_VECTOR (gint32,  int32,  32, 4)
DEFINE_INT_VECTOR (gint32,  int32,  32, 8)
DEFINE_INT_VECTOR (gint32,  int32,  32, 16)

DEFINE_INT_VECTOR (guint32, uint32, 32, 4)
DEFINE_INT_VECTOR (guint32, uint32, 32, 8)
DEFINE_INT_VECTOR (guint32, uint32, 32, 16)

DEFINE_INT_VECTOR (gint64,  int64,  64, 8)
DEFINE_INT_VECTOR (gint64,  int64,  64, 16)

DEFINE_INT_VECTOR (guint64, uint64, 64, 8)
DEFINE_INT_VECTOR (guint64, uint64, 64, 16)

DEFINE_VECTOR (gfloat, float, 32, 4)
DEFINE_VECTOR (gfloat, float, 32, 8)
DEFINE_VECTOR (gfloat, float, 32, 16)

DEFINE_VECTOR (gdouble, double, 64, 8)
DEFINE_VECTOR (gdouble, double, 64, 16)
