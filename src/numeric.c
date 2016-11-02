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
// DEFINE_NUMERIC (float16)
DEFINE_NUMERIC (float80)
DEFINE_NUMERIC (float128)
DEFINE_NUMERIC (decimal32)
DEFINE_NUMERIC (decimal64)
DEFINE_NUMERIC (decimal128)
DEFINE_NUMERIC (complex)
DEFINE_NUMERIC (complex80)
DEFINE_NUMERIC (complex128)

void numeric_init ()
{
    // TODO: g_value_register_transform_func ();
}
