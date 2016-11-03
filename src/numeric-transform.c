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
#ifdef __STD_DEC_FP__
DEFINE_COPY (numeric_decimal32,  numeric_decimal32)
DEFINE_COPY (numeric_decimal64,  numeric_decimal64)
DEFINE_COPY (numeric_decimal128, numeric_decimal128)
#endif
DEFINE_COPY (numeric_complex,    numeric_complex)
DEFINE_COPY (numeric_complex80,  numeric_complex80)
DEFINE_COPY (numeric_complex128, numeric_complex128)

#define DEFINE_CAST_FROM_FIELD(src_type, src_field, dest_type)             \
static void                                                                \
src_type##_to_##dest_type (const GValue *src_value, GValue *dest_value)    \
{                                                                          \
    src_type src_data = (src_type) src_value->data[0].src_field;           \
    dest_type dest_data = (dest_type) src_data;                            \
    dest_value->data[0].v_pointer = g_malloc (sizeof (dest_type));         \
    memcpy (dest_value->data[0].v_pointer, &dest_data, sizeof (src_type)); \
}

#define DEFINE_CAST_FROM_ALL_FIELDS(src_type)        \
DEFINE_CAST_FROM_FIELD (gchar,   v_int,    src_type) \
DEFINE_CAST_FROM_FIELD (guchar,  v_int,    src_type) \
DEFINE_CAST_FROM_FIELD (gint,    v_int,    src_type) \
DEFINE_CAST_FROM_FIELD (guint,   v_uint,   src_type) \
DEFINE_CAST_FROM_FIELD (glong,   v_long,   src_type) \
DEFINE_CAST_FROM_FIELD (gulong,  v_ulong,  src_type) \
DEFINE_CAST_FROM_FIELD (gint64,  v_int64,  src_type) \
DEFINE_CAST_FROM_FIELD (guint64, v_uint64, src_type) \
DEFINE_CAST_FROM_FIELD (gfloat,  v_float,  src_type) \
DEFINE_CAST_FROM_FIELD (gdouble, v_double, src_type)

DEFINE_CAST_FROM_ALL_FIELDS (numeric_int128)
DEFINE_CAST_FROM_ALL_FIELDS (numeric_uint128)
DEFINE_CAST_FROM_ALL_FIELDS (numeric_float80)
DEFINE_CAST_FROM_ALL_FIELDS (numeric_float128)

#ifdef __STD_DEC_FP__
DEFINE_CAST_FROM_ALL_FIELDS (numeric_decimal32)
DEFINE_CAST_FROM_ALL_FIELDS (numeric_decimal64)
DEFINE_CAST_FROM_ALL_FIELDS (numeric_decimal128)
#endif

DEFINE_CAST_FROM_ALL_FIELDS (numeric_complex)
DEFINE_CAST_FROM_ALL_FIELDS (numeric_complex80)
DEFINE_CAST_FROM_ALL_FIELDS (numeric_complex128)

#define DEFINE_CAST_TO_FIELD(src_type, dest_field, dest_type)              \
static void                                                                \
src_type##_to_##dest_type (const GValue *src_value, GValue *dest_value)    \
{                                                                          \
    src_type src_data = *(src_type*) src_value->data[0].v_pointer;          \
    dest_type dest_data = (dest_type) src_data;                            \
    dest_value->data[0].dest_field = dest_data;                            \
}

#define DEFINE_CAST_TO_ALL_FIELDS(src_type)        \
DEFINE_CAST_TO_FIELD (src_type, v_int,    gchar)   \
DEFINE_CAST_TO_FIELD (src_type, v_int,    guchar)  \
DEFINE_CAST_TO_FIELD (src_type, v_int,    gint)    \
DEFINE_CAST_TO_FIELD (src_type, v_uint,   guint)   \
DEFINE_CAST_TO_FIELD (src_type, v_long,   glong)   \
DEFINE_CAST_TO_FIELD (src_type, v_ulong,  gulong)  \
DEFINE_CAST_TO_FIELD (src_type, v_int64,  gint64)  \
DEFINE_CAST_TO_FIELD (src_type, v_uint64, guint64) \
DEFINE_CAST_TO_FIELD (src_type, v_float,  gfloat)  \
DEFINE_CAST_TO_FIELD (src_type, v_double, gdouble)

DEFINE_CAST_TO_ALL_FIELDS (numeric_int128)
DEFINE_CAST_TO_ALL_FIELDS (numeric_uint128)
DEFINE_CAST_TO_ALL_FIELDS (numeric_float80)
DEFINE_CAST_TO_ALL_FIELDS (numeric_float128)

#ifdef __STD_DEC_FP__
DEFINE_CAST_TO_ALL_FIELDS (numeric_decimal32)
DEFINE_CAST_TO_ALL_FIELDS (numeric_decimal64)
DEFINE_CAST_TO_ALL_FIELDS (numeric_decimal128)
#endif

DEFINE_CAST_TO_ALL_FIELDS (numeric_complex)
DEFINE_CAST_TO_ALL_FIELDS (numeric_complex80)
DEFINE_CAST_TO_ALL_FIELDS (numeric_complex128)

#define DEFINE_CAST(src_type, dest_type)                                   \
static void                                                                \
src_type##_to_##dest_type (const GValue *src_value, GValue *dest_value)    \
{                                                                          \
    src_type src_data = *(src_type*) src_value->data[0].v_pointer;         \
    dest_type dest_data = (dest_type) src_data;                            \
    dest_value->data[0].v_pointer = g_malloc (sizeof (dest_type));         \
    memcpy (dest_value->data[0].v_pointer, &dest_data, sizeof (src_type)); \
}

// int128
DEFINE_CAST(numeric_int128, numeric_uint128)
DEFINE_CAST(numeric_int128, numeric_float80)
DEFINE_CAST(numeric_int128, numeric_float128)
#ifdef __STDC_DEC_FP__
DEFINE_CAST(numeric_int128, numeric_decimal32)
DEFINE_CAST(numeric_int128, numeric_decimal64)
DEFINE_CAST(numeric_int128, numeric_decimal128)
#endif
DEFINE_CAST(numeric_int128, numeric_complex)
DEFINE_CAST(numeric_int128, numeric_complex80)
DEFINE_CAST(numeric_int128, numeric_complex128)

// uint128
DEFINE_CAST(numeric_uint128, numeric_int128)
DEFINE_CAST(numeric_uint128, numeric_float80)
DEFINE_CAST(numeric_uint128, numeric_float128)
#ifdef __STDC_DEC_FP__
DEFINE_CAST(numeric_uint128, numeric_decimal32)
DEFINE_CAST(numeric_uint128, numeric_decimal64)
DEFINE_CAST(numeric_uint128, numeric_decimal128)
#endif
DEFINE_CAST(numeric_uint128, numeric_complex)
DEFINE_CAST(numeric_uint128, numeric_complex80)
DEFINE_CAST(numeric_uint128, numeric_complex128)

// float80
DEFINE_CAST(numeric_float80, numeric_int128)
DEFINE_CAST(numeric_float80, numeric_uint128)
DEFINE_CAST(numeric_float80, numeric_float128)
#ifdef __STDC_DEC_FP__
DEFINE_CAST(numeric_float80, numeric_decimal32)
DEFINE_CAST(numeric_float80, numeric_decimal64)
DEFINE_CAST(numeric_float80, numeric_decimal128)
#endif
DEFINE_CAST(numeric_float80, numeric_complex)
DEFINE_CAST(numeric_float80, numeric_complex80)
DEFINE_CAST(numeric_float80, numeric_complex128)

// float128
DEFINE_CAST(numeric_float128, numeric_int128)
DEFINE_CAST(numeric_float128, numeric_uint128)
DEFINE_CAST(numeric_float128, numeric_float80)
#ifdef __STDC_DEC_FP__
DEFINE_CAST(numeric_float128, numeric_decimal32)
DEFINE_CAST(numeric_float128, numeric_decimal64)
DEFINE_CAST(numeric_float128, numeric_decimal128)
#endif
DEFINE_CAST(numeric_float128, numeric_complex)
DEFINE_CAST(numeric_float128, numeric_complex80)
DEFINE_CAST(numeric_float128, numeric_complex128)

// complex
DEFINE_CAST(numeric_complex, numeric_int128)
DEFINE_CAST(numeric_complex, numeric_uint128)
DEFINE_CAST(numeric_complex, numeric_float80)
DEFINE_CAST(numeric_complex, numeric_float128)
#ifdef __STDC_DEC_FP__
DEFINE_CAST(numeric_complex, numeric_decimal32)
DEFINE_CAST(numeric_complex, numeric_decimal64)
DEFINE_CAST(numeric_complex, numeric_decimal128)
#endif
DEFINE_CAST(numeric_complex, numeric_complex80)
DEFINE_CAST(numeric_complex, numeric_complex128)

// complex80
DEFINE_CAST(numeric_complex80, numeric_int128)
DEFINE_CAST(numeric_complex80, numeric_uint128)
DEFINE_CAST(numeric_complex80, numeric_float80)
DEFINE_CAST(numeric_complex80, numeric_float128)
#ifdef __STDC_DEC_FP__
DEFINE_CAST(numeric_complex80, numeric_decimal32)
DEFINE_CAST(numeric_complex80, numeric_decimal64)
DEFINE_CAST(numeric_complex80, numeric_decimal128)
#endif
DEFINE_CAST(numeric_complex80, numeric_complex)
DEFINE_CAST(numeric_complex80, numeric_complex128)

// complex128
DEFINE_CAST(numeric_complex128, numeric_int128)
DEFINE_CAST(numeric_complex128, numeric_uint128)
DEFINE_CAST(numeric_complex128, numeric_float80)
DEFINE_CAST(numeric_complex128, numeric_float128)
#ifdef __STDC_DEC_FP__
DEFINE_CAST(numeric_complex128, numeric_decimal32)
DEFINE_CAST(numeric_complex128, numeric_decimal64)
DEFINE_CAST(numeric_complex128, numeric_decimal128)
#endif
DEFINE_CAST(numeric_complex128, numeric_complex)
DEFINE_CAST(numeric_complex128, numeric_complex80)

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

#define REGISTER_ALL_TRANSFORMS_FROM(from_type_id,from_type)                                                    \
    g_value_register_transform_func (from_type_id, G_TYPE_CHAR,             from_type##_to_gchar);              \
    g_value_register_transform_func (from_type_id, G_TYPE_UCHAR,            from_type##_to_guchar);             \
    g_value_register_transform_func (from_type_id, G_TYPE_INT,              from_type##_to_gint);               \
    g_value_register_transform_func (from_type_id, G_TYPE_UINT,             from_type##_to_guint);              \
    g_value_register_transform_func (from_type_id, G_TYPE_INT64,            from_type##_to_gint64);             \
    g_value_register_transform_func (from_type_id, G_TYPE_UINT64,           from_type##_to_guint64);            \
    g_value_register_transform_func (from_type_id, G_TYPE_LONG,             from_type##_to_glong);              \
    g_value_register_transform_func (from_type_id, G_TYPE_ULONG,            from_type##_to_gulong);             \
    g_value_register_transform_func (from_type_id, G_TYPE_FLOAT,            from_type##_to_gfloat);             \
    g_value_register_transform_func (from_type_id, G_TYPE_DOUBLE,           from_type##_to_gdouble);            \
    g_value_register_transform_func (from_type_id, NUMERIC_TYPE_INT128,     from_type##_to_numeric_int128);     \
    g_value_register_transform_func (from_type_id, NUMERIC_TYPE_UINT128,    from_type##_to_numeric_uint128);    \
    g_value_register_transform_func (from_type_id, NUMERIC_TYPE_FLOAT80,    from_type##_to_numeric_float80);    \
    g_value_register_transform_func (from_type_id, NUMERIC_TYPE_FLOAT128,   from_type##_to_numeric_float128);   \
    g_value_register_transform_func (from_type_id, NUMERIC_TYPE_COMPLEX,    from_type##_to_numeric_complex);    \
    g_value_register_transform_func (from_type_id, NUMERIC_TYPE_COMPLEX80,  from_type##_to_numeric_complex80);  \
    g_value_register_transform_func (from_type_id, NUMERIC_TYPE_COMPLEX128, from_type##_to_numeric_complex128);

#define REGISTER_ALL_TRANSFORMS_TO(to_type_id,to_type)                                                     \
    g_value_register_transform_func (G_TYPE_CHAR,             to_type_id, gchar_to_##to_type);             \
    g_value_register_transform_func (G_TYPE_UCHAR,            to_type_id, guchar_to_##to_type);            \
    g_value_register_transform_func (G_TYPE_INT,              to_type_id, gint_to_##to_type);              \
    g_value_register_transform_func (G_TYPE_UINT,             to_type_id, guint_to_##to_type);             \
    g_value_register_transform_func (G_TYPE_LONG,             to_type_id, glong_to_##to_type);             \
    g_value_register_transform_func (G_TYPE_ULONG,            to_type_id, gulong_to_##to_type);            \
    g_value_register_transform_func (G_TYPE_INT64,            to_type_id, gint64_to_##to_type);            \
    g_value_register_transform_func (G_TYPE_UINT64,           to_type_id, guint64_to_##to_type);           \
    g_value_register_transform_func (G_TYPE_FLOAT,            to_type_id, gfloat_to_##to_type);            \
    g_value_register_transform_func (G_TYPE_DOUBLE,           to_type_id, gdouble_to_##to_type);           \
    g_value_register_transform_func (NUMERIC_TYPE_INT128,     to_type_id, numeric_int128_to_##to_type);    \
    g_value_register_transform_func (NUMERIC_TYPE_UINT128,    to_type_id, numeric_uint128_to_##to_type);   \
    g_value_register_transform_func (NUMERIC_TYPE_FLOAT80,    to_type_id, numeric_float80_to_##to_type);   \
    g_value_register_transform_func (NUMERIC_TYPE_FLOAT128,   to_type_id, numeric_float128_to_##to_type);  \
    g_value_register_transform_func (NUMERIC_TYPE_COMPLEX,    to_type_id, numeric_complex_to_##to_type);   \
    g_value_register_transform_func (NUMERIC_TYPE_COMPLEX80,  to_type_id, numeric_complex80_to_##to_type); \
    g_value_register_transform_func (NUMERIC_TYPE_COMPLEX128, to_type_id, numeric_complex128_to_##to_type);

#define REGISTER_ALL_TRANSFORMS(type_id,type) \
REGISTER_ALL_TRANSFORMS_FROM (type_id, type) \
REGISTER_ALL_TRANSFORMS_TO   (type_id, type)

__attribute__ ((constructor))
static void
numeric_transforms_init (void)
{
    REGISTER_ALL_TRANSFORMS (NUMERIC_TYPE_INT128,   numeric_int128)
    REGISTER_ALL_TRANSFORMS (NUMERIC_TYPE_UINT128,  numeric_uint128)
    REGISTER_ALL_TRANSFORMS (NUMERIC_TYPE_FLOAT80,  numeric_float80)
    REGISTER_ALL_TRANSFORMS (NUMERIC_TYPE_FLOAT128, numeric_float128)
#ifdef __STDC_DEC_FP__
    REGISTER_ALL_TRANSFORMS (NUMERIC_TYPE_DECIMAL32,  numeric_decimal32)
    REGISTER_ALL_TRANSFORMS (NUMERIC_TYPE_DECIMAL64,  numeric_decimal64)
    REGISTER_ALL_TRANSFORMS (NUMERIC_TYPE_DECIMAL128, numeric_decimal128)
#endif
    REGISTER_ALL_TRANSFORMS (NUMERIC_TYPE_COMPLEX,    numeric_complex)
    REGISTER_ALL_TRANSFORMS (NUMERIC_TYPE_COMPLEX80,  numeric_complex80)
    REGISTER_ALL_TRANSFORMS (NUMERIC_TYPE_COMPLEX128, numeric_complex128)

    // byteswaps
    g_value_register_transform_func (G_TYPE_FLOAT,           NUMERIC_TYPE_FLOAT_LE,  gfloat_to_numeric_float_le);
    g_value_register_transform_func (G_TYPE_FLOAT,           NUMERIC_TYPE_FLOAT_BE,  gfloat_to_numeric_float_be);
    g_value_register_transform_func (G_TYPE_DOUBLE,          NUMERIC_TYPE_DOUBLE_LE, gdouble_to_numeric_double_le);
    g_value_register_transform_func (G_TYPE_DOUBLE,          NUMERIC_TYPE_DOUBLE_BE, gdouble_to_numeric_double_be);
    g_value_register_transform_func (NUMERIC_TYPE_FLOAT_LE,  G_TYPE_FLOAT,           numeric_float_le_to_gfloat);
    g_value_register_transform_func (NUMERIC_TYPE_FLOAT_BE,  G_TYPE_FLOAT,           numeric_float_be_to_gfloat);
    g_value_register_transform_func (NUMERIC_TYPE_DOUBLE_LE, G_TYPE_DOUBLE,          numeric_double_le_to_gdouble);
    g_value_register_transform_func (NUMERIC_TYPE_DOUBLE_BE, G_TYPE_DOUBLE,          numeric_double_be_to_gdouble);
}
