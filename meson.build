project('Numeric-GLib', 'c', 'vala')

glib = dependency('glib-2.0')
gobject = dependency('gobject-2.0')
quadmath = meson.get_compiler('c').find_library('quadmath')

dfp = meson.get_compiler('c').find_library('dfp')
add_project_arguments(['-D', 'HAVE_LIBDFP'], language: 'vala')
add_project_arguments(['-D__STDC_WANT_DEC_FP__'], language: 'c')

subdir('src')
subdir('tests')
