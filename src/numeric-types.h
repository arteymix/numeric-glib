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

#if !defined (NUMERIC_INSIDE) && !defined (NUMERIC_COMPILATION)
#error "Only <numeric.h> can be included directly."
#endif

#ifndef NUMERIC_TYPES_H
#define NUMERIC_TYPES_H

#include <glib-object.h>

G_BEGIN_DECLS

#define DEFINE_NUMERIC_PROTOTYPE(type,ctype)                     \
typedef ctype   numeric_##type;                                  \
GType           numeric_##type##_get_type (void) G_GNUC_CONST;   \
numeric_##type *numeric_##type##_copy     (numeric_##type *num); \
void            numeric_##type##_free     (numeric_##type *num);

// http://gcc.gnu.org/onlinedocs/gcc/Floating-Types.html#Floating-Types
typedef __float80                                _Float80;
typedef __float128                               _Float128;
typedef _Complex float __attribute__((mode(TC))) _Complex128;
typedef _Complex float __attribute__((mode(XC))) _Complex80;

DEFINE_NUMERIC_PROTOTYPE (int128,     __int128)
DEFINE_NUMERIC_PROTOTYPE (uint128,    unsigned __int128)
DEFINE_NUMERIC_PROTOTYPE (float80,    _Float80)
DEFINE_NUMERIC_PROTOTYPE (float128,   _Float128)
DEFINE_NUMERIC_PROTOTYPE (decimal32,  _Decimal32)
DEFINE_NUMERIC_PROTOTYPE (decimal64,  _Decimal64)
DEFINE_NUMERIC_PROTOTYPE (decimal128, _Decimal128)
DEFINE_NUMERIC_PROTOTYPE (complex,    _Complex)
DEFINE_NUMERIC_PROTOTYPE (complex80,  _Complex80)
DEFINE_NUMERIC_PROTOTYPE (complex128, _Complex128)

#define NUMERIC_TYPE_INT128     (numeric_int128_get_type     ())
#define NUMERIC_TYPE_UINT128    (numeric_uint128_get_type    ())
#define NUMERIC_TYPE_FLOAT80    (numeric_float80_get_type    ())
#define NUMERIC_TYPE_FLOAT128   (numeric_float128_get_type   ())
#define NUMERIC_TYPE_DECIMAL32  (numeric_decimal32_get_type  ())
#define NUMERIC_TYPE_DECIMAL64  (numeric_decimal64_get_type  ())
#define NUMERIC_TYPE_DECIMAL128 (numeric_decimal128_get_type ())
#define NUMERIC_TYPE_COMPLEX    (numeric_complex_get_type    ())
#define NUMERIC_TYPE_COMPLEX80  (numeric_complex80_get_type  ())
#define NUMERIC_TYPE_COMPLEX128 (numeric_complex128_get_type ())

#define DEFINE_NUMERIC_PROTOTYPE_WITH_BITSWAP(type,ctype,gtype) \
DEFINE_NUMERIC_PROTOTYPE (type,       ctype)                    \
numeric_##type                                                  \
numeric_##type##_from_##gtype (gtype num);                      \
                                                                \
gtype                                                           \
numeric_##type##_to_##gtype (numeric_##type num);

DEFINE_NUMERIC_PROTOTYPE_WITH_BITSWAP(float_le,  gfloat,  float)
DEFINE_NUMERIC_PROTOTYPE_WITH_BITSWAP(float_be,  gfloat,  float)
DEFINE_NUMERIC_PROTOTYPE_WITH_BITSWAP(double_le, gdouble, double)
DEFINE_NUMERIC_PROTOTYPE_WITH_BITSWAP(double_be, gdouble, double)

#define NUMERIC_TYPE_FLOAT_LE   (numeric_float_le_get_type   ())
#define NUMERIC_TYPE_FLOAT_BE   (numeric_float_be_get_type   ())
#define NUMERIC_TYPE_DOUBLE_LE  (numeric_double_le_get_type  ())
#define NUMERIC_TYPE_DOUBLE_BE  (numeric_double_be_get_type  ())

G_END_DECLS

#endif
