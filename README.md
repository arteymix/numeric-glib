# Numeric-GLib

Numeric data types for GLib via GCC extensions

# Features

 - 128 bit integers with `int128` and `uint128`
 - `float80` and quad-precision `float128`
 - decimal with `decimal32`, `decimal64` and `decimal128`
 - C99 `complex`, `complex80` and `complex128`
 - vectorized operations on supported types
 - little and big endian variants with `_le` and `_be` suffix

All types are prefixed with `numeric_`, but can be used as-is by importing the
`Numeric` namespace in Vala.

# Usage

In Vala, one can simply add `--pkg=numeric-glib-1.0` to include the type
definitions and link against the shared library to initialize all the types and
transformations.

```bash
vala --pkg=numeric-glib-1.0 main.vala
```

Or via Meson, the `numeric_glib` dependency can be included in any target.

```python
project('Foo')

glib = dependency('glib-2.0')
gobject = dependency('gobject-2.0')
numeric_glib = dependency('numeric-glib-1.0', fallback: ['numeric-glib', 'numeric_glib'])

executable('foo', dependencies: [glib, gobject, numeric_glib])
```
