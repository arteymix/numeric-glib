project('Numeric-GLib', 'c', 'vala',
        meson_version: '>=0.46')

glib_dep = dependency('glib-2.0')
gobject_dep = dependency('gobject-2.0')
quadmath_dep = meson.get_compiler('c').find_library('quadmath')

if get_option('with_libdfp')
    dfp_dep = meson.get_compiler('c').find_library('dfp')
    add_project_arguments(['-D', 'HAVE_LIBDFP'], language: 'vala')
    add_project_arguments(['-DHAVE_LIBDFP', '-D__STDC_WANT_DEC_FP__'], language: 'c')
else
    dfp = []
endif

subdir('src')
subdir('tests')
