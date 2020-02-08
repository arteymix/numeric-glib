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
	[IntegerType (rank = 12)]
	public struct int128 {}

	[IntegerType (rank = 13)]
	public struct uint128 {}

	[FloatingType (rank = 10)]
	public struct float_le
	{
		public static float_le from_float (float num);
		public float to_float ();
	}

	[FloatingType (rank = 10)]
	public struct float_be
	{
		public static float_be from_float (float num);
		public float to_float ();
	}

	[FloatingType (rank = 11)]
	public struct double_le
	{
		public static double_le from_double (double num);
		public double to_double ();
	}

	[FloatingType (rank = 11)]
	public struct double_be {
		public static double_be from_double (double num);
		public double to_double ();
	}

	[FloatingType (rank = 12)]
	public struct float80 {}

	[FloatingType (rank = 12)]
	[CCode (cprefix = "FLT128_")]
	public struct float128
	{
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
		public string to_string (string format = "%Q")
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

	[FloatingType (rank = 6)]
	public struct decimal32
	{
		[CCode (cname = "strtod32", cheader_filename="dfp/stdlib.h")]
		public static decimal32 parse (string s, out char sp = null);
		public string to_string ()
		{
			return "%Hf".printf (this);
		}
	}

	[FloatingType (rank = 10)]
	public struct decimal64
	{
		[CCode (cname = "strtod64", cheader_filename="dfp/stdlib.h")]
		public static decimal64 parse (string s, out char sp = null);
		public string to_string ()
		{
			return "%Df".printf (this);
		}
	}

	[FloatingType (rank = 12)]
	public struct decimal128
	{
		[CCode (cname = "strtod128", cheader_filename="dfp/stdlib.h")]
		public static decimal128 parse (string s, out char sp = null);

		[CCode (cname = "snprintf", cheader_filename = "stdio.h")]
		private static int _snprintf (char[] s, string format, ...);

		public string to_string ()
		{
			var buffer = new char[128];
			var format = "%DDf";
			var n = _snprintf (buffer, format, this);
			if (n >= buffer.length) {
				buffer = new char[n + 1];
				_snprintf (buffer, format, this);
			}
			return (string) buffer;
		}
	}

	[FloatingType (rank = 6)]
	public struct complex {}

	[FloatingType (rank = 12)]
	public struct complex80 {}

	[FloatingType (rank = 12)]
	public struct complex128 {}

	public struct int32_v16
	{
		public static int32_v16 add (int32_v16 x, int32_v16 y);
		public static int32_v16 sub (int32_v16 x, int32_v16 y);
		public int get (size_t index);
		public void set (size_t index, int val);
	}

	[CCode (cprefix = "M_", lower_case_cprefix = "", cheader_filename = "quadmath.h")]
	namespace Math
	{
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
	}
}
