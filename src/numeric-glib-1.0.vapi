/* Numerical Type Extensions for Vala
 * Copyright 2016 Guillaume Poirier-Morency <guillaumepoiriermorency@gmail.com>
 *
 * These require GCC extensions described in https://gcc.gnu.org/onlinedocs/gcc/C-Extensions.html
 * and specific compiler argments in order to work properly.
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

	[FloatingType (rank = 4)]
	public struct float16 {}

	[FloatingType (rank = 12)]
	public struct float80 {}

	[FloatingType (rank = 12)]
	public struct float128 {}

	[FloatingType (rank = 6)]
	public struct decimal32 {}

	[FloatingType (rank = 10)]
	public struct decimal64 {}

	[FloatingType (rank = 12)]
	public struct decimal128 {}

	[FloatingType (rank = 6)]
	public struct complex {}

	[FloatingType (rank = 12)]
	public struct complex80 {}

	[FloatingType (rank = 12)]
	public struct complex128 {}
}
