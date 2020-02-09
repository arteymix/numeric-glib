project('Numeric-GLib', 'c', 'vala',
        meson_version: '>=0.46')

glib_dep = dependency('glib-2.0')
gobject_dep = dependency('gobject-2.0')
quadmath_dep = meson.get_compiler('c').find_library('quadmath')

if get_option('with_libdfp')
    dfp_lib = meson.get_compiler('c').find_library('dfp')
    dfp_dep = declare_dependency(dependencies: [dfp_lib],
                                 compile_args: '-D__STDC_WANT_DEC_FP__')
    add_project_arguments(['-D', 'HAVE_LIBDFP'], language: 'vala')
    add_project_arguments(['-DHAVE_LIBDFP'], language: 'c')
else
    dfp = []
endif

subdir('src')
subdir('tests')
