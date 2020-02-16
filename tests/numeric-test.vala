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

class Foo : Object
{
	public float128 bar { get; set; default = float128.parse ("0.1"); }
}

public int main (string[] args)
{
	Test.init (ref args);

	Test.add_func ("/type_info", () => {
		unowned Numeric.TypeInfo ti = Numeric.get_type_info_from_name ("float128");
		assert (ti.byte_order == ByteOrder.HOST);
	});

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

	Test.add_func ("/float_be", () => {
		unowned Numeric.TypeInfo ti = get_type_info (typeof (float_be));

		assert (ti.name == "float_be");
		assert (ti.byte_order == ByteOrder.BIG_ENDIAN);

		var a = Value (typeof (float));
		a.set_float (5.0f);

		var b = Value (typeof (float_be));
		assert (a.transform (ref b));
		assert (*(float*) b.get_boxed () != a.get_float ());
		var b_val = *(float_be*) b.get_boxed ();
		assert (5.0f != b_val);
		assert (5.0f == b_val.to_float ());

		var c = Value (typeof (float));
		assert (b.transform (ref c));
		assert (a.get_float () == c.get_float ());

		var d = float_be.from_float (5.0f);
		assert (5.0f != d);
		assert (5.0f == d.to_float ());
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

	Test.add_func ("/vector", () => {
		int32_v16 x = int32_v16 ();
		int32_v16 y = int32_v16 ();

		x[0] = 1;
		x[1] = 2;
		x[2] = 3;
		x[3] = 4;

		assert (1 == x[0]);
		assert (2 == x[1]);
		assert (3 == x[2]);
		assert (4 == x[3]);

		y[0] = 1;
		y[1] = 2;
		y[2] = 3;
		y[3] = 4;

		var z = int32_v16.add (x, y);

		assert (2 == z[0]);
		assert (4 == z[1]);
		assert (6 == z[2]);
		assert (8 == z[3]);
	});

	Test.add_func ("/vector/boxed", () => {
		int32_v16 x = int32_v16 ();

		x[0] = 1;
		x[1] = 2;
		x[2] = 3;
		x[3] = 4;

		var val = Value (typeof (int32_v16));
		val.set_boxed (&x);

		int32_v16 y = *(int32_v16*) val.get_boxed ();

		assert (1 == y[0]);
		assert (2 == y[1]);
		assert (3 == y[2]);
		assert (4 == y[3]);
	});

#if HAVE_LIBDFP
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
	});
#endif

	Test.add_func ("/gobject", () => {
		var foo = new Foo ();
		assert (foo.bar == float128.parse ("0.1"));
		foo.bar = 12;
		assert (foo.bar == 12);
		print (foo.bar.to_string ());
		assert (foo.bar.to_string () == "12.000000");
		foo.set_property ("bar", float128.parse ("0.2"));
		assert (foo.bar == float128.parse ("0.2"));
		var ret = Value (typeof (float128));
		foo.get_property ("bar", ref ret);
		assert ((float128) ret == float128.parse ("0.2"));
	});

	return Test.run ();
}
