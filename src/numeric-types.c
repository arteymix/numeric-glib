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
