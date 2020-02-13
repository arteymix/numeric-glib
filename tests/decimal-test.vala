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

	Test.add_func ("/decimal32", () => {
		var a = decimal32.parse ("0.1");
		var b = decimal32.parse ("0.1");
		var c = decimal32.parse ("0.1");
		var d = decimal32.parse ("-0.3");

		var expected = decimal32.parse ("0.0");

		assert (a + b + c + d  ==  expected);

		assert (decimal32.FORMAT_MODIFIER == "H");
		assert (a.to_string () == "0.100000");
		assert (expected.to_string () == "0.000000");

		var a_value = GLib.Value (typeof (decimal32));
		a_value.set_boxed (&a);
		var a_unboxed = (decimal32*) a_value.get_boxed ();
		assert (*a_unboxed == decimal32.parse ("0.1"));

		assert (decimal32.INFINITY > 0);
		assert (decimal32.NAN != decimal32.NAN);
	});

	Test.add_func ("/decimal64", () => {
		var a = decimal64.parse ("0.1");
		var b = decimal64.parse ("0.1");
		var c = decimal64.parse ("0.1");
		var d = decimal64.parse ("-0.3");

		var expected = decimal64.parse ("0.0");

		assert (a + b + c + d  ==  expected);

		assert (decimal64.FORMAT_MODIFIER == "D");
		assert (a.to_string () == "0.100000");
		assert (expected.to_string () == "0.000000");
	});

	Test.add_func ("/decimal128", () => {
		var a = decimal128.parse ("0.1");
		var b = decimal128.parse ("0.1");
		var c = decimal128.parse ("0.1");
		var d = decimal128.parse ("-0.3");

		var expected = decimal128.parse ("0.0");

		assert (a + b + c + d  ==  expected);

		assert (decimal128.FORMAT_MODIFIER == "DD");
		assert (a.to_string () == "0.100000");
		assert (expected.to_string () == "0.000000");

		Numeric.Math.expd128 (a);
	});

	Test.add_func ("/setround", () => {
		assert (Libdfp.getround () == Libdfp.RoundingDirection.TONEAREST);
		var orig = Libdfp.setround (Libdfp.RoundingDirection.UPWARD);
		assert (Libdfp.getround () == Libdfp.RoundingDirection.UPWARD);
		Libdfp.setround (orig);
	});

	return Test.run ();
}
