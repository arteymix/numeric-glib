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

#include "numeric.h"

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

static void
numeric_register_transforms ()
{
    g_value_register_transform_func (NUMERIC_TYPE_INT128,     NUMERIC_TYPE_INT128,     numeric_int128_to_numeric_int128);
    g_value_register_transform_func (NUMERIC_TYPE_UINT128,    NUMERIC_TYPE_UINT128,    numeric_uint128_to_numeric_uint128);
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
