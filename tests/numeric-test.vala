/*
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

		assert (sizeof (float128) == 16);

		assert (sizeof (decimal32) == 4);
		assert (sizeof (decimal64) == 8);
		assert (sizeof (decimal128) == 16);

		assert (sizeof (complex) == 16);
	});

	Test.add_func ("/declaration", () => {
		float128 f = 12.5;
		assert (12.5 == (double) f);
	});

	Test.add_func ("/transform", () => {
		var src_value  = Value (typeof (int));
		var dest_value = Value (typeof (int128));

		dest_value.set_boxed (null);

		src_value.transform (ref dest_value);
	});

	return Test.run ();
}
