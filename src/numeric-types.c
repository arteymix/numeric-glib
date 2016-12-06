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

#include "numeric-types.h"

#include <string.h>

#define DEFINE_NUMERIC(type)                           \
G_DEFINE_BOXED_TYPE (numeric_##type,                   \
                     numeric_##type,                   \
                     numeric_##type##_copy,            \
                     numeric_##type##_free)            \
                                                       \
numeric_##type *                                       \
numeric_##type##_copy (numeric_##type *num)            \
{                                                      \
    gpointer ptr = g_malloc (sizeof (numeric_##type)); \
    memcpy (ptr, num, sizeof (numeric_##type));        \
    return ptr;                                        \
}                                                      \
                                                       \
void                                                   \
numeric_##type##_free (numeric_##type *num)            \
{                                                      \
    g_free (num);                                      \
}

DEFINE_NUMERIC (int128)
DEFINE_NUMERIC (uint128)
DEFINE_NUMERIC (float80)
DEFINE_NUMERIC (float128)
DEFINE_NUMERIC (decimal32)
DEFINE_NUMERIC (decimal64)
DEFINE_NUMERIC (decimal128)
DEFINE_NUMERIC (complex)
DEFINE_NUMERIC (complex80)
DEFINE_NUMERIC (complex128)

#define DEFINE_NUMERIC_WITH_BYTESWAP(type,gtype,stype,routine,order) \
DEFINE_NUMERIC (type)                                                \
numeric_##type                                                       \
numeric_##type##_from_##gtype (g##gtype num)                         \
{                                                                    \
    union {                                                          \
        stype          v_swap;                                       \
        numeric_##type v_##type;                                     \
        g##gtype       v_##gtype;                                    \
    } data;                                                          \
    data.v_##gtype = num;                                            \
    data.v_swap    = routine##_TO_##order (data.v_swap);             \
    return data.v_##type;                                            \
}                                                                    \
                                                                     \
g##gtype                                                             \
numeric_##type##_to_##gtype (numeric_##type num)                     \
{                                                                    \
    union {                                                          \
        stype          v_swap;                                       \
        numeric_##type v_##type;                                     \
        g##gtype       v_##gtype;                                    \
    } data;                                                          \
    data.v_##type = num;                                             \
    data.v_swap   = routine##_FROM_##order (data.v_swap);            \
    return data.v_##gtype;                                           \
}

DEFINE_NUMERIC_WITH_BYTESWAP (int_le,    int,    gint,    GINT,    LE)
DEFINE_NUMERIC_WITH_BYTESWAP (int_be,    int,    gint,    GINT,    BE)
DEFINE_NUMERIC_WITH_BYTESWAP (uint_le,   uint,   guint,   GUINT,   LE)
DEFINE_NUMERIC_WITH_BYTESWAP (uint_be,   uint,   guint,   GUINT,   BE)
DEFINE_NUMERIC_WITH_BYTESWAP (long_le,   long,   glong,   GLONG,   LE)
DEFINE_NUMERIC_WITH_BYTESWAP (long_be,   long,   glong,   GLONG,   BE)
DEFINE_NUMERIC_WITH_BYTESWAP (ulong_le,  ulong,  gulong,  GLONG,   LE)
DEFINE_NUMERIC_WITH_BYTESWAP (ulong_be,  ulong,  gulong,  GLONG,   BE)
DEFINE_NUMERIC_WITH_BYTESWAP (int16_le,  int16,  gint16,  GINT16,  LE)
DEFINE_NUMERIC_WITH_BYTESWAP (int16_be,  int16,  gint16,  GINT16,  BE)
DEFINE_NUMERIC_WITH_BYTESWAP (uint16_le, uint16, guint16, GUINT16, LE)
DEFINE_NUMERIC_WITH_BYTESWAP (uint16_be, uint16, guint16, GUINT16, BE)
DEFINE_NUMERIC_WITH_BYTESWAP (int32_le,  int32,  gint32,  GINT32,  LE)
DEFINE_NUMERIC_WITH_BYTESWAP (int32_be,  int32,  gint32,  GINT32,  BE)
DEFINE_NUMERIC_WITH_BYTESWAP (uint32_le, uint32, guint32, GUINT32, LE)
DEFINE_NUMERIC_WITH_BYTESWAP (uint32_be, uint32, guint32, GUINT32, BE)
DEFINE_NUMERIC_WITH_BYTESWAP (int64_le,  int64,  gint64,  GINT64,  LE)
DEFINE_NUMERIC_WITH_BYTESWAP (int64_be,  int64,  gint64,  GINT64,  BE)
DEFINE_NUMERIC_WITH_BYTESWAP (uint64_le, uint64, guint64, GUINT64, LE)
DEFINE_NUMERIC_WITH_BYTESWAP (uint64_be, uint64, guint64, GUINT64, BE)
DEFINE_NUMERIC_WITH_BYTESWAP (float_le,  float,  gint32,  GINT32,  LE)
DEFINE_NUMERIC_WITH_BYTESWAP (float_be,  float,  gint32,  GINT32,  BE)
DEFINE_NUMERIC_WITH_BYTESWAP (double_le, double, gint32,  GINT64,  LE)
DEFINE_NUMERIC_WITH_BYTESWAP (double_be, double, gint32,  GINT64,  BE)

// if 'src_value' can be copied to 'dest_value'
#define DEFINE_COPY(from_type, to_type)                                                       \
static void                                                                                   \
from_type##_to_##to_type (const GValue *src_value, GValue *dest_value)                        \
{                                                                                             \
    dest_value->data[0].v_pointer = g_malloc (sizeof (to_type));                              \
    memcpy (dest_value->data[0].v_pointer, src_value->data[0].v_pointer, sizeof (from_type)); \
}                                                                                             \

DEFINE_COPY (numeric_int128,     numeric_int128)
DEFINE_COPY (numeric_uint128,    numeric_uint128)
DEFINE_COPY (numeric_float80,    numeric_float80)
DEFINE_COPY (numeric_float128,   numeric_float128)
DEFINE_COPY (numeric_decimal32,  numeric_decimal32)
DEFINE_COPY (numeric_decimal64,  numeric_decimal64)
DEFINE_COPY (numeric_decimal128, numeric_decimal128)
DEFINE_COPY (numeric_complex,    numeric_complex)
DEFINE_COPY (numeric_complex80,  numeric_complex80)
DEFINE_COPY (numeric_complex128, numeric_complex128)

#define DEFINE_BYTESWAP_TO(from_type,to_type,order,bits)                                               \
static void                                                                                            \
from_type##_to_##to_type (const GValue* src_value, GValue* dest_value)                                 \
{                                                                                                      \
    dest_value->data[0].v_pointer            = g_malloc (sizeof (numeric_float_le));                   \
    *(gint##bits*) dest_value->data[0].v_pointer = GINT##bits##_TO_##order (src_value->data[0].v_int); \
}

DEFINE_BYTESWAP_TO (gfloat,  numeric_float_le,  LE, 32)
DEFINE_BYTESWAP_TO (gfloat,  numeric_float_be,  BE, 32)
DEFINE_BYTESWAP_TO (gdouble, numeric_double_le, LE, 64)
DEFINE_BYTESWAP_TO (gdouble, numeric_double_be, BE, 64)

#define DEFINE_BYTESWAP_FROM(from_type,to_type,order,bits)                                                \
static void                                                                                               \
from_type##_to_##to_type (const GValue* src_value, GValue* dest_value)                                    \
{                                                                                                         \
    dest_value->data[0].v_int = GINT##bits##_FROM_##order (*(guint##bits*) src_value->data[0].v_pointer); \
}

DEFINE_BYTESWAP_FROM (numeric_float_le,  gfloat,  LE, 32)
DEFINE_BYTESWAP_FROM (numeric_float_be,  gfloat,  BE, 32)
DEFINE_BYTESWAP_FROM (numeric_double_le, gdouble, LE, 64)
DEFINE_BYTESWAP_FROM (numeric_double_be, gdouble, BE, 32)

static void
numeric_register_transforms ()
{
    g_value_register_transform_func (G_TYPE_FLOAT,            NUMERIC_TYPE_FLOAT_LE,   gfloat_to_numeric_float_le);
    g_value_register_transform_func (G_TYPE_FLOAT,            NUMERIC_TYPE_FLOAT_BE,   gfloat_to_numeric_float_be);
    g_value_register_transform_func (G_TYPE_DOUBLE,           NUMERIC_TYPE_DOUBLE_LE,  gdouble_to_numeric_double_le);
    g_value_register_transform_func (G_TYPE_DOUBLE,           NUMERIC_TYPE_DOUBLE_BE,  gdouble_to_numeric_double_be);
    g_value_register_transform_func (NUMERIC_TYPE_INT128,     NUMERIC_TYPE_INT128,     numeric_int128_to_numeric_int128);
    g_value_register_transform_func (NUMERIC_TYPE_UINT128,    NUMERIC_TYPE_UINT128,    numeric_uint128_to_numeric_uint128);
    g_value_register_transform_func (NUMERIC_TYPE_FLOAT_LE,   G_TYPE_FLOAT,            numeric_float_le_to_gfloat);
    g_value_register_transform_func (NUMERIC_TYPE_FLOAT_BE,   G_TYPE_FLOAT,            numeric_float_be_to_gfloat);
    g_value_register_transform_func (NUMERIC_TYPE_DOUBLE_LE,  G_TYPE_DOUBLE,           numeric_double_le_to_gdouble);
    g_value_register_transform_func (NUMERIC_TYPE_DOUBLE_BE,  G_TYPE_DOUBLE,           numeric_double_be_to_gdouble);
    g_value_register_transform_func (NUMERIC_TYPE_FLOAT80,    NUMERIC_TYPE_FLOAT80,    numeric_float80_to_numeric_float80);
    g_value_register_transform_func (NUMERIC_TYPE_FLOAT128,   NUMERIC_TYPE_FLOAT128,   numeric_float128_to_numeric_float128);
    g_value_register_transform_func (NUMERIC_TYPE_DECIMAL32,  NUMERIC_TYPE_DECIMAL32,  numeric_decimal32_to_numeric_decimal32);
    g_value_register_transform_func (NUMERIC_TYPE_DECIMAL64,  NUMERIC_TYPE_DECIMAL64,  numeric_decimal64_to_numeric_decimal64);
    g_value_register_transform_func (NUMERIC_TYPE_DECIMAL128, NUMERIC_TYPE_DECIMAL128, numeric_decimal128_to_numeric_decimal128);
    g_value_register_transform_func (NUMERIC_TYPE_COMPLEX,    NUMERIC_TYPE_COMPLEX,    numeric_complex_to_numeric_complex);
    g_value_register_transform_func (NUMERIC_TYPE_COMPLEX80,  NUMERIC_TYPE_COMPLEX80,  numeric_complex80_to_numeric_complex80);
    g_value_register_transform_func (NUMERIC_TYPE_COMPLEX128, NUMERIC_TYPE_COMPLEX128, numeric_complex128_to_numeric_complex128);
}

void numeric_init ()
{
    numeric_register_transforms ();
}
