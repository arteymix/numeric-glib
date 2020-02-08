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

#include <stdlib.h>
#include <stdio.h>

#include <dfp/stdlib.h>
#include <dfp/math.h>
#include <glib.h>

#include <numeric.h>

void
test_decimal128 (void)
{
    numeric_decimal128 a;

    a = strtod128 ("0.1", NULL);

    g_assert (a == 0.1DL);
    g_assert_cmpfloat (a + a, ==, 0.2DL);
    g_assert_cmpfloat (fabsd128 (a), ==, 0.1DL);

    char buffer[128];
    snprintf (buffer, sizeof buffer, "%DDf", a);

    g_assert_cmpstr (buffer, ==, "0.100000");
}

int
main (int argc, char **argv)
{
    g_test_init (&argc, &argv, NULL);

    g_test_add_func ("/decimal128", test_decimal128);

    return g_test_run ();
}
