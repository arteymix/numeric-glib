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

[CCode (cprefix = "numeric_", cheader_filename = "numeric.h")]
namespace Numeric
{
	[IntegerType (rank = 12, width = 16)]
	[CCode (get_value_function = "numeric_value_get_int128", set_value_function = "numeric_value_set_int128")]
	public struct int128 {}

	[IntegerType (rank = 13, width = 16)]
	[CCode (get_value_function = "numeric_value_get_uint128", set_value_function = "numeric_value_set_uint128")]
	public struct uint128 {}

	[FloatingType (rank = 10, width = 4)]
	[CCode (get_value_function = "numeric_value_get_float_le", set_value_function = "numeric_value_set_float_le")]
	public struct float_le
	{
		public static float_le from_float (float num);
		public float to_float ();
	}

	[FloatingType (rank = 10, width = 4)]
	[CCode (get_value_function = "numeric_value_get_float_be", set_value_function = "numeric_value_set_float_be")]
	public struct float_be
	{
		public static float_be from_float (float num);
		public float to_float ();
	}

	[FloatingType (rank = 11, width = 8)]
	[CCode (get_value_function = "numeric_value_get_double_le", set_value_function = "numeric_value_set_double_le")]
	public struct double_le
	{
		public static double_le from_double (double num);
		public double to_double ();
	}

	[FloatingType (rank = 11, width = 8)]
	[CCode (get_value_function = "numeric_value_get_double_be", set_value_function = "numeric_value_set_double_be")]
	public struct double_be {
		public static double_be from_double (double num);
		public double to_double ();
	}

	[FloatingType (rank = 12, width = 10)]
	[CCode (get_value_function = "numeric_value_get_float80", set_value_function = "numeric_value_set_float80")]
	public struct float80
	{
		[CCode (cname = "strtold", cheader_filename = "stdlib.h")]
		public static float80 parse (string s, out char sp = null);
	}

	[FloatingType (rank = 12, width = 16)]
	[CCode (cprefix = "FLT128_", get_value_function = "numeric_value_get_float128", set_value_function = "numeric_value_set_float128")]
	public struct float128
	{
		[CCode (cname = "NUMERIC_FLOAT128_FORMAT")]
		public const string FORMAT;
		[CCode (cname = "NUMERIC_FLOAT128_MODIFIER")]
		public const string FORMAT_MODIFIER;

		[CCode (cheader_filename = "quadmath.h")]
		public const float128 MAX;
		[CCode (cheader_filename = "quadmath.h")]
		public const float128 MIN;
		[CCode (cheader_filename = "quadmath.h")]
		public const float128 EPSILON;
		[CCode (cheader_filename = "quadmath.h")]
		public const float128 DENORM_MIN;
		[CCode (cheader_filename = "quadmath.h")]
		public const int MANT_DIG;
		[CCode (cheader_filename = "quadmath.h")]
		public const int MIN_EXP;
		[CCode (cheader_filename = "quadmath.h")]
		public const int MAX_EXP;
		[CCode (cheader_filename = "quadmath.h")]
		public const int DIG;
		[CCode (cheader_filename = "quadmath.h")]
		public const int MIN_10_EXP;
		[CCode (cheader_filename = "quadmath.h")]
		public const int MAX_10_EXP;
		[CCode (cname = "strtoflt128", cheader_filename = "quadmath.h")]
		public static float128 parse (string s, out char sp = null);
		[CCode (cname = "quadmath_snprintf")]
		private static int _quadmath_snprintf (char[] s, string format, ...);
		public string to_string (string format = "%" + FORMAT)
		{
			var buffer = new char[128];
			var n = _quadmath_snprintf (buffer, format, this);
			if (n >= buffer.length) {
				buffer = new char[n + 1];
				_quadmath_snprintf (buffer, format, this);
			}
			return (string) buffer;
		}
	}

	[FloatingType (decimal = true, rank = 6, width = 4)]
	[CCode (get_value_function = "numeric_value_get_decimal32", set_value_function = "numeric_value_set_decimal32")]
	public struct decimal32
	{
		public const string FORMAT;
		[CCode (cname = "NUMERIC_DECIMAL32_MODIFIER")]
		public const string FORMAT_MODIFIER;

		[CCode (cname = "DEC_NAN", cheader_filename = "math.h")]
		public const decimal32 NAN;
		[CCode (cname = "DEC_INFINITY", cheader_filename = "math.h")]
		public const decimal32 INFINITY;

		[CCode (cname = "strtod32", cheader_filename = "stdlib.h")]
		public static decimal32 parse (string s, out char sp = null);

		public string to_string (string format = "%" + FORMAT)
		{
			return format.printf (this);
		}
	}

	[FloatingType (decimal = true, rank = 10, width = 8)]
	[CCode (get_value_function = "numeric_value_get_decimal64", set_value_function = "numeric_value_set_decimal64")]
	public struct decimal64
	{
		public const string FORMAT;
		[CCode (cname = "NUMERIC_DECIMAL64_MODIFIER")]
		public const string FORMAT_MODIFIER;

		[CCode (cname = "strtod64", cheader_filename = "stdlib.h")]
		public static decimal64 parse (string s, out char sp = null);

		public string to_string (string format = "%" + FORMAT)
		{
			return format.printf (this);
		}
	}

	[FloatingType (decimal = true, rank = 12, width = 16)]
	[CCode (get_value_function = "numeric_value_get_decimal128", set_value_function = "numeric_value_set_decimal128")]
	public struct decimal128
	{
		public const string FORMAT;
		[CCode (cname = "NUMERIC_DECIMAL128_MODIFIER")]
		public const string FORMAT_MODIFIER;

		[CCode (cname = "strtod128", cheader_filename = "stdlib.h")]
		public static decimal128 parse (string s, out char sp = null);

		public string to_string (string format = "%" + FORMAT)
		{
			return format.printf (this);
		}
	}

	[FloatingType (rank = 6, width = 8)]
	[CCode (get_value_function = "numeric_value_get_complex32", set_value_function = "numeric_value_set_complex32")]
	public struct complex32
	{
		[CCode (cname = "crealf", cheader_filename = "complex.h")]
		public float real ();
		[CCode (cname = "cimagf", cheader_filename = "complex.h")]
		public float image ();
	}

	[FloatingType (rank = 6, width = 8)]
	[CCode (get_value_function = "numeric_value_get_complex64", set_value_function = "numeric_value_set_complex64")]
	public struct complex64
	{
		[CCode (cname = "creal", cheader_filename = "complex.h")]
		public double real ();
		[CCode (cname = "cimag", cheader_filename = "complex.h")]
		public double image ();
	}

	[FloatingType (rank = 12, width = 10)]
	[CCode (get_value_function = "numeric_value_get_complex80", set_value_function = "numeric_value_set_complex80")]
	public struct complex80
	{
		[CCode (cname = "creall", cheader_filename = "complex.h")]
		public float80 real ();
		[CCode (cname = "cimagl", cheader_filename = "complex.h")]
		public float80 image ();
	}

	[FloatingType (rank = 12, width = 16)]
	[CCode (get_value_function = "numeric_value_get_complex128", set_value_function = "numeric_value_set_complex128")]
	public struct complex128
	{
		[CCode (cname = "crealq", cheader_filename = "quadmath.h")]
		public float128 real ();
		[CCode (cname = "cimagq", cheader_filename = "quadmath.h")]
		public float128 image ();
	}

	public struct int32_v16
	{
		public static int32_v16 add (int32_v16 x, int32_v16 y);
		public static int32_v16 sub (int32_v16 x, int32_v16 y);
		public int get (size_t index);
		public void set (size_t index, int val);
	}

	[CCode (cprefix = "M_", lower_case_cprefix = "", cheader_filename = "math.h,quadmath.h")]
	namespace Math
	{
		[CCode (cprefix = "", cheader_filename = "complex.h")]
		public const complex64 I;
		public const float128 Eq;
		public const float128 LOG2Eq;
		public const float128 LOG10Eq;
		public const float128 LN2q;
		public const float128 LN10q;
		public const float128 PIq;
		public const float128 PI_2q;
		public const float128 PI_4q;
		public const float128 1_PIq;
		public const float128 2_PIq;
		public const float128 2_SQRTPIq;
		public const float128 SQRT2q;
		public const float128 SQRT1_2q;
		public float128 acosq (float128 x);
		public float128 acoshq (float128 x);
		public float128 asinq (float128 x);
		public float128 asinhq (float128 x);
		public float128 atanq (float128 x);
		public float128 atanhq (float128 x);
		public float128 atan2q (float128 x, float128 y);
		public float128 cbrtq (float128 x);
		public float128 ceilq (float128 x);
		public float128 copysignq (float128 x, float128 y);
		public float128 coshq (float128 x);
		public float128 cosq (float128 x);
		public float128 erfq (float128 x);
		public float128 erfcq (float128 x);
		public float128 expq (float128 x);
		public float128 expm1q (float128 x);
		public float128 fabsq (float128 x);
		public float128 fdimq (float128 x, float128 y);
		public float128 finiteq (float128 x);
		public float128 floorq (float128 x);
		public float128 fmaq (float128 x, float128 y);
		public float128 fmaxq (float128 x, float128 y);
		public float128 fminq (float128 x, float128 y);
		public float128 fmodq (float128 x, float128 y);
		public float128 frexpq (float128 x, out int e);
		public float128 hypotq (float128 x, float128 y);
		public float128 ilogbq (float128 x);
		public float128 isinfq (float128 x);
		public float128 isnanq (float128 x);
		public float128 j0q (float128 x);
		public float128 j1q (float128 x);
		public float128 jnq (int n, float128 x);
		public float128 ldexpq (float128 x, int e);
		public float128 lgammaq (float128 x);
		public float128 llrintq (float128 x);
		public float128 llroundq (float128 x);
		public float128 logq (float128 x);
		public float128 log10q (float128 x);
		public float128 log1pq (float128 x);
		public float128 log2q (float128 x);
		public float128 lrintq (float128 x);
		public float128 lroundq (float128 x);
		public float128 modfq (float128 x, float128 y);
		public float128 nanq (string x);
		public float128 nearbyintq (float128 x);
		public float128 nextafterq (float128 x, float128 y);
		public float128 powq (float128 x, float128 y);
		public float128 remainderq (float128 x, float128 y);
		public float128 remquoq (float128 x, float128 y, out int e);
		public float128 rintq (float128 x);
		public float128 roundq (float128 x);
		public float128 scalblnq (float128 x, long e);
		public float128 scalbnq (float128 x, int e);
		public float128 signbitq (float128 x);
		public float128 sincosq (float128 x, float128 y);
		public float128 sinhq (float128 x);
		public float128 sinq (float128 x);
		public float128 sqrtq (float128 x);
		public float128 tanq (float128 x);
		public float128 tanhq (float128 x);
		public float128 tgammaq (float128 x);
		public float128 truncq (float128 x);
		public float128 y0q (float128 x);
		public float128 y1q (float128 x);
		public float128 ynq (int n, float128 x);
		public float128 cabsq (complex128 x);
		public float128 cargq (complex128 x);
		public float128 cimagq (complex128 x);
		public float128 crealq (complex128 x);
		public complex128 cacoshq (complex128 x);
		public complex128 cacosq (complex128 x);
		public complex128 casinhq (complex128 x);
		public complex128 casinq (complex128 x);
		public complex128 catanhq (complex128 x);
		public complex128 catanq (complex128 x);
		public complex128 ccosq (complex128 x);
		public complex128 ccoshq (complex128 x);
		public complex128 cexpq (complex128 x);
		public complex128 cexpiq (complex128 x);
		public complex128 real (complex128 x);
		public complex128 clogq (complex128 x);
		public complex128 clog10q (complex128 x);
		public complex128 conjq (complex128 x);
		public complex128 cpowq (complex128 x);
		public complex128 cprojq (complex128 x);
		public complex128 csinq (complex128 x);
		public complex128 csinhq (complex128 x);
		public complex128 csqrtq (complex128 x);
		public complex128 ctanq (complex128 x);
		public complex128 ctanhq (complex128 x);
		/* the following definitions are in a overwritten math.h file located in dfp/math.h */
		public const decimal128 Edl;
		public const decimal128 LOG2Edl;
		public const decimal128 LOG10Edl;
		public const decimal128 LN2dl;
		public const decimal128 LN10dl;
		public const decimal128 PIdl;
		public const decimal128 PI_2dl;
		public const decimal128 PI_4dl;
		public const decimal128 1_PIdl;
		public const decimal128 2_PIdl;
		public const decimal128 2_SQRTPIdl;
		public const decimal128 SQRT2dl;
		public const decimal128 SQRT1_2dl;
		public decimal128 expd128 (decimal128 x);
	}
}
