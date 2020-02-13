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

#include <glib.h>
#include <string.h>

#define DEFINE_NUMERIC(type)                                     \
G_DEFINE_BOXED_TYPE (numeric_##type,                             \
                     numeric_##type,                             \
                     numeric_##type##_copy,                      \
                     numeric_##type##_free)                      \
                                                                 \
numeric_##type *                                                 \
numeric_##type##_copy (numeric_##type *num)                      \
{                                                                \
    gpointer ptr = g_new (numeric_##type, 1);                    \
    memcpy (ptr, num, sizeof (numeric_##type));                  \
    return ptr;                                                  \
}                                                                \
                                                                 \
void                                                             \
numeric_##type##_free (numeric_##type *num)                      \
{                                                                \
    g_free (num);                                                \
}                                                                \
                                                                 \
numeric_##type                                                   \
numeric_value_get_##type (const GValue *val)                     \
{                                                                \
    return *(numeric_##type*)g_value_get_boxed (val);            \
}                                                                \
                                                                 \
void                                                             \
numeric_value_set_##type (GValue *val, numeric_##type x)         \
{                                                                \
    numeric_##type *ptr = g_new (numeric_##type, 1);             \
    *ptr = x;                                                    \
    g_value_set_boxed (val, ptr);                                \
}

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

typedef struct _NumericTypeInfo
{
    GType             type;
    const gchar      *name;
    gsize             width;
    NumericByteOrder  byte_order;
} NumericTypeInfo;

GArray *TYPE_TABLE = NULL;

void
numeric_type_register_static (GType        type,
                              const gchar *name,
                              gsize width,
                              NumericByteOrder byte_order)
{
    if (TYPE_TABLE == NULL)
    {
        TYPE_TABLE = g_array_new (FALSE, FALSE, sizeof (NumericTypeInfo));
    }

    NumericTypeInfo ti = {
        .type       = type,
        .name       = g_strdup (name),
        .width      = width,
        .byte_order = byte_order};

    g_array_append_val (TYPE_TABLE,
                        ti);
}

NumericTypeInfo*
numeric_type_get_info (GType type)
{
    gint i;
    for (i = 0; i < TYPE_TABLE->len; i++)
    {
        NumericTypeInfo* ti = &g_array_index (TYPE_TABLE, NumericTypeInfo, i);
        if (ti->type == type)
        {
            return ti;
        }
    }

    g_return_val_if_reached (NULL);
}

GTypeInfo *type_database;

/**
 * numeric_type_get_name:
 * Obtain the number of bytes occupied by @numeric_type.
 */
const gchar *
numeric_type_get_name (GType numeric_type)
{
    NumericTypeInfo *type_info;
    type_info = numeric_type_get_info (numeric_type);
    return type_info->name;
}

/**
 * numeric_type_get_width:
 * Obtain the number of bytes occupied by @numeric_type.
 */
gsize
numeric_type_get_width (GType numeric_type)
{
    NumericTypeInfo *type_info;
    type_info = numeric_type_get_info (numeric_type);
    return type_info->width;
}

/**
 * numeric_type_get_byte_order:
 * Obtain the byte order of @numeric_type.
 */
NumericByteOrder
numeric_type_get_byte_order (GType numeric_type)
{
    NumericTypeInfo *type_info;
    type_info = numeric_type_get_info (numeric_type);
    return type_info->byte_order;
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

DEFINE_NUMERIC_WITH_BYTESWAP (int_le,    int,    gint,    GINT,    LE)
DEFINE_NUMERIC_WITH_BYTESWAP (int_be,    int,    gint,    GINT,    BE)
DEFINE_NUMERIC_WITH_BYTESWAP (uint_le,   uint,   guint,   GUINT,   LE)
DEFINE_NUMERIC_WITH_BYTESWAP (uint_be,   uint,   guint,   GUINT,   BE)
DEFINE_NUMERIC_WITH_BYTESWAP (long_le,   long,   glong,   GLONG,   LE)
DEFINE_NUMERIC_WITH_BYTESWAP (long_be,   long,   glong,   GLONG,   BE)
DEFINE_NUMERIC_WITH_BYTESWAP (ulong_le,  ulong,  gulong,  GLONG,   LE)
DEFINE_NUMERIC_WITH_BYTESWAP (ulong_be,  ulong,  gulong,  GLONG,   BE)
DEFINE_NUMERIC_WITH_BYTESWAP (int64_le,  int64,  gint64,  GINT64,  LE)
DEFINE_NUMERIC_WITH_BYTESWAP (int64_be,  int64,  gint64,  GINT64,  BE)
DEFINE_NUMERIC_WITH_BYTESWAP (uint64_le, uint64, guint64, GUINT64, LE)
DEFINE_NUMERIC_WITH_BYTESWAP (uint64_be, uint64, guint64, GUINT64, BE)
DEFINE_NUMERIC_WITH_BYTESWAP (float_le,  float,  gint32,  GINT32,  LE)
DEFINE_NUMERIC_WITH_BYTESWAP (float_be,  float,  gint32,  GINT32,  BE)
DEFINE_NUMERIC_WITH_BYTESWAP (double_le, double, gint32,  GINT64,  LE)
DEFINE_NUMERIC_WITH_BYTESWAP (double_be, double, gint32,  GINT64,  BE)

#if HAVE_LIBDFP
extern void register_printf_dfp (void);
#endif

__attribute__ ((constructor))
static void
numeric_types_init (void)
{
    numeric_type_register_static (numeric_decimal128_get_type (),
                                  "decimal128",
                                  sizeof (numeric_decimal128),
                                  NUMERIC_BYTE_ORDER_UNKNOWN);

#if HAVE_LIBDFP
    register_printf_dfp ();
#endif
}
