/* Copyright 2016 Guillaume Poirier-Morency
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

using GLib;
using Numeric;

public int main (string[] args)
{
	Test.init (ref args);

	Test.add_func ("/size", () => {
		assert (sizeof (int128) == 16);
		assert (sizeof (uint128) == 16);

		assert (sizeof (float80) == 16);
		assert (sizeof (float128) == 16);

		assert (sizeof (decimal32) == 4);
		assert (sizeof (decimal64) == 8);
		assert (sizeof (decimal128) == 16);

		assert (sizeof (complex) == 16);
	});

	Test.add_func ("/float128", () => {
		float128 f = 12.5;
		float128 g = 13.5;
		assert (26 == (double) (f + g));
		assert (12.5 == (double) f);
		assert ("1.096910e+00" == Numeric.Math.log10q (f).to_string ("%Qe"));
		assert ("1.189731e+4932" == float128.MAX.to_string ("%Qe"));
		assert (12.5 == float128.parse ("12.5"));
	});

	Test.add_func ("/transform/identity", () => {
		var src_value = Value (typeof (int128));
		var dest_value = Value (typeof (int128));

		int128 val = 12;
		src_value.set_boxed (&val);

		src_value.transform (ref dest_value);

		assert (src_value.get_boxed () != dest_value.get_boxed ());
		assert (12 == *(int128*) dest_value.get_boxed ());
	});

	return Test.run ();
}
