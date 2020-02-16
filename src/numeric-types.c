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

#define DEFINE_NUMERIC(type,byte_order)                          \
G_DEFINE_BOXED_TYPE_WITH_CODE (numeric_##type,                   \
                               numeric_##type,                   \
                               numeric_##type##_copy,            \
                               numeric_##type##_free,            \
                               numeric_type_register_static_simple (g_define_type_id, G_STRINGIFY(type), sizeof (numeric_##type), byte_order)) \
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

#define DEFINE_NUMERIC_WITH_BYTESWAP(type,byte_order,gtype,stype,routine,order) \
DEFINE_NUMERIC (type,byte_order)                                     \
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

static GArray *TYPE_TABLE = NULL;

/**
 *
 */
void numeric_type_register_static (GType                  type,
                                   const gchar            *name,
                                   const NumericTypeInfo *type_info)
{
    if (TYPE_TABLE == NULL)
    {
        TYPE_TABLE = g_array_new (FALSE, FALSE, sizeof (NumericTypeInfo));
    }

    /* make sure we don't register the same type twice */
    gint i;
    for (i = 0; i < TYPE_TABLE->len; i++)
    {
        NumericTypeInfo* ti = &g_array_index (TYPE_TABLE, NumericTypeInfo, i);
        if (ti->type == type_info->type)
            return;
    }

    g_array_append_vals (TYPE_TABLE, type_info, 1);
}

void
numeric_type_register_static_simple (GType        type,
                                     const gchar *name,
                                     gsize        width,
                                     gint         byte_order)
{
    NumericTypeInfo ti = {
        .type       = type,
        .name       = g_strdup (name),
        .width      = width,
        .byte_order = byte_order};

    numeric_type_register_static (type, name, &ti);
}

/*
 * GLib numerical types already have existing definitions for *_get_type(),
 * preventing us from registering their numeric_{type}_get_type() counterpart
 * lazily.
 */
static void
register_glib_numerical_types ()
{
    numeric_type_register_static_simple (G_TYPE_CHAR,   "char",   sizeof (gchar),   G_BYTE_ORDER);
    numeric_type_register_static_simple (G_TYPE_UCHAR,  "uchar",  sizeof (guchar),  G_BYTE_ORDER);
    numeric_type_register_static_simple (G_TYPE_INT,    "int",    sizeof (gint),    G_BYTE_ORDER);
    numeric_type_register_static_simple (G_TYPE_UINT,   "uint",   sizeof (guint),   G_BYTE_ORDER);
    numeric_type_register_static_simple (G_TYPE_LONG,   "long",   sizeof (glong),   G_BYTE_ORDER);
    numeric_type_register_static_simple (G_TYPE_ULONG,  "ulong",  sizeof (gulong),  G_BYTE_ORDER);
    numeric_type_register_static_simple (G_TYPE_INT64,  "int64",  sizeof (gint64),  G_BYTE_ORDER);
    numeric_type_register_static_simple (G_TYPE_UINT64, "uint64", sizeof (guint64), G_BYTE_ORDER);
    numeric_type_register_static_simple (G_TYPE_FLOAT,  "float",  sizeof (gfloat),  G_BYTE_ORDER);
    numeric_type_register_static_simple (G_TYPE_DOUBLE, "double", sizeof (gdouble), G_BYTE_ORDER);
}

const NumericTypeInfo *
numeric_get_type_info (GType type)
{
    register_glib_numerical_types ();

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

const NumericTypeInfo *
numeric_get_type_info_from_name (const gchar *name)
{
    register_glib_numerical_types ();

    gint i;
    for (i = 0; i < TYPE_TABLE->len; i++)
    {
        const NumericTypeInfo* ti = &g_array_index (TYPE_TABLE, NumericTypeInfo, i);
        if (g_strcmp0 (ti->name, name) == 0)
        {
            return ti;
        }
    }

    g_return_val_if_reached (NULL);
}

DEFINE_NUMERIC (int128,     G_BYTE_ORDER)
DEFINE_NUMERIC (uint128,    G_BYTE_ORDER)
DEFINE_NUMERIC (float80,    G_BYTE_ORDER)
DEFINE_NUMERIC (float128,   G_BYTE_ORDER)
DEFINE_NUMERIC (decimal32,  G_BYTE_ORDER)
DEFINE_NUMERIC (decimal64,  G_BYTE_ORDER)
DEFINE_NUMERIC (decimal128, G_BYTE_ORDER)
DEFINE_NUMERIC (complex,    G_BYTE_ORDER)
DEFINE_NUMERIC (complex80,  G_BYTE_ORDER)
DEFINE_NUMERIC (complex128, G_BYTE_ORDER)

DEFINE_NUMERIC_WITH_BYTESWAP (int_le,    G_LITTLE_ENDIAN, int,    gint,    GINT,    LE)
DEFINE_NUMERIC_WITH_BYTESWAP (int_be,    G_BIG_ENDIAN,    int,    gint,    GINT,    BE)
DEFINE_NUMERIC_WITH_BYTESWAP (uint_le,   G_LITTLE_ENDIAN, uint,   guint,   GUINT,   LE)
DEFINE_NUMERIC_WITH_BYTESWAP (uint_be,   G_BIG_ENDIAN,    uint,   guint,   GUINT,   BE)
DEFINE_NUMERIC_WITH_BYTESWAP (long_le,   G_LITTLE_ENDIAN, long,   glong,   GLONG,   LE)
DEFINE_NUMERIC_WITH_BYTESWAP (long_be,   G_BIG_ENDIAN,    long,   glong,   GLONG,   BE)
DEFINE_NUMERIC_WITH_BYTESWAP (ulong_le,  G_LITTLE_ENDIAN, ulong,  gulong,  GLONG,   LE)
DEFINE_NUMERIC_WITH_BYTESWAP (ulong_be,  G_BIG_ENDIAN,    ulong,  gulong,  GLONG,   BE)
DEFINE_NUMERIC_WITH_BYTESWAP (int64_le,  G_LITTLE_ENDIAN, int64,  gint64,  GINT64,  LE)
DEFINE_NUMERIC_WITH_BYTESWAP (int64_be,  G_BIG_ENDIAN,    int64,  gint64,  GINT64,  BE)
DEFINE_NUMERIC_WITH_BYTESWAP (uint64_le, G_LITTLE_ENDIAN, uint64, guint64, GUINT64, LE)
DEFINE_NUMERIC_WITH_BYTESWAP (uint64_be, G_BIG_ENDIAN,    uint64, guint64, GUINT64, BE)
DEFINE_NUMERIC_WITH_BYTESWAP (float_le,  G_LITTLE_ENDIAN, float,  gint32,  GINT32,  LE)
DEFINE_NUMERIC_WITH_BYTESWAP (float_be,  G_BIG_ENDIAN,    float,  gint32,  GINT32,  BE)
DEFINE_NUMERIC_WITH_BYTESWAP (double_le, G_LITTLE_ENDIAN, double, gint32,  GINT64,  LE)
DEFINE_NUMERIC_WITH_BYTESWAP (double_be, G_BIG_ENDIAN,    double, gint32,  GINT64,  BE)

#if HAVE_LIBDFP
extern void register_printf_dfp (void);
#endif

__attribute__ ((constructor))
static void
numeric_types_init (void)
{
#if HAVE_LIBDFP
    register_printf_dfp ();
#endif
}
