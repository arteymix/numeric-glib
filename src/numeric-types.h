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
numeric_##type##_from_##gtype (g##gtype num);                   \
                                                                \
g##gtype                                                        \
numeric_##type##_to_##gtype (numeric_##type num);

DEFINE_NUMERIC_PROTOTYPE_WITH_BITSWAP (int_le,    gint,    int)
DEFINE_NUMERIC_PROTOTYPE_WITH_BITSWAP (int_be,    gint,    int)
DEFINE_NUMERIC_PROTOTYPE_WITH_BITSWAP (uint_le,   guint,   uint)
DEFINE_NUMERIC_PROTOTYPE_WITH_BITSWAP (uint_be,   guint,   uint)
DEFINE_NUMERIC_PROTOTYPE_WITH_BITSWAP (long_le,   glong,   long)
DEFINE_NUMERIC_PROTOTYPE_WITH_BITSWAP (long_be,   glong,   long)
DEFINE_NUMERIC_PROTOTYPE_WITH_BITSWAP (ulong_le,  gulong,  ulong)
DEFINE_NUMERIC_PROTOTYPE_WITH_BITSWAP (ulong_be,  gulong,  ulong)
DEFINE_NUMERIC_PROTOTYPE_WITH_BITSWAP (int16_le,  gint16,  int16)
DEFINE_NUMERIC_PROTOTYPE_WITH_BITSWAP (int16_be,  gint16,  int16)
DEFINE_NUMERIC_PROTOTYPE_WITH_BITSWAP (uint16_le, guint16, uint16)
DEFINE_NUMERIC_PROTOTYPE_WITH_BITSWAP (uint16_be, guint16, uint16)
DEFINE_NUMERIC_PROTOTYPE_WITH_BITSWAP (int32_le,  gint32,  int32)
DEFINE_NUMERIC_PROTOTYPE_WITH_BITSWAP (int32_be,  gint32,  int32)
DEFINE_NUMERIC_PROTOTYPE_WITH_BITSWAP (uint32_le, guint32, uint32)
DEFINE_NUMERIC_PROTOTYPE_WITH_BITSWAP (uint32_be, guint32, uint32)
DEFINE_NUMERIC_PROTOTYPE_WITH_BITSWAP (int64_le,  gint64,  int64)
DEFINE_NUMERIC_PROTOTYPE_WITH_BITSWAP (int64_be,  gint64,  int64)
DEFINE_NUMERIC_PROTOTYPE_WITH_BITSWAP (uint64_le, guint64, uint64)
DEFINE_NUMERIC_PROTOTYPE_WITH_BITSWAP (uint64_be, guint64, uint64)
DEFINE_NUMERIC_PROTOTYPE_WITH_BITSWAP (float_le,  gfloat,  float)
DEFINE_NUMERIC_PROTOTYPE_WITH_BITSWAP (float_be,  gfloat,  float)
DEFINE_NUMERIC_PROTOTYPE_WITH_BITSWAP (double_le, gdouble, double)
DEFINE_NUMERIC_PROTOTYPE_WITH_BITSWAP (double_be, gdouble, double)

#define NUMERIC_TYPE_INT_LE    (numeric_int_le_get_type    ())
#define NUMERIC_TYPE_INT_BE    (numeric_int_be_get_type    ())
#define NUMERIC_TYPE_UINT_LE   (numeric_uint_le_get_type   ())
#define NUMERIC_TYPE_UINT_BE   (numeric_uint_be_get_type   ())
#define NUMERIC_TYPE_LONG_LE   (numeric_long_le_get_type   ())
#define NUMERIC_TYPE_LONG_BE   (numeric_long_be_get_type   ())
#define NUMERIC_TYPE_ULONG_LE  (numeric_ulong_le_get_type  ())
#define NUMERIC_TYPE_ULONG_BE  (numeric_ulong_be_get_type  ())
#define NUMERIC_TYPE_INT16_LE  (numeric_int16_le_get_type  ())
#define NUMERIC_TYPE_INT16_BE  (numeric_int16_be_get_type  ())
#define NUMERIC_TYPE_UINT16_LE (numeric_uint16_le_get_type ())
#define NUMERIC_TYPE_UINT16_BE (numeric_uint16_be_get_type ())
#define NUMERIC_TYPE_INT32_LE  (numeric_int32_le_get_type  ())
#define NUMERIC_TYPE_INT32_BE  (numeric_int32_be_get_type  ())
#define NUMERIC_TYPE_UINT32_LE (numeric_uint32_le_get_type ())
#define NUMERIC_TYPE_UINT32_BE (numeric_uint32_be_get_type ())
#define NUMERIC_TYPE_INT64_LE  (numeric_int64_le_get_type  ())
#define NUMERIC_TYPE_INT64_BE  (numeric_int64_be_get_type  ())
#define NUMERIC_TYPE_UINT64_LE (numeric_uint64_le_get_type ())
#define NUMERIC_TYPE_UINT64_BE (numeric_uint64_be_get_type ())
#define NUMERIC_TYPE_FLOAT_LE  (numeric_float_le_get_type  ())
#define NUMERIC_TYPE_FLOAT_BE  (numeric_float_be_get_type  ())
#define NUMERIC_TYPE_DOUBLE_LE (numeric_double_le_get_type ())
#define NUMERIC_TYPE_DOUBLE_BE (numeric_double_be_get_type ())

G_END_DECLS

#endif
