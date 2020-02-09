numeric_sources = [
    'numeric.c',
    'numeric-transform.c',
    'numeric-types.c',
    'numeric-vector.c']
numeric_glib_lib = library('numeric-glib-1.0', numeric_sources,
                           dependencies: [glib_dep, gobject_dep, dfp_dep],
                           c_args: '-DNUMERIC_COMPILATION',
                           install: true)

numeric_glib_dep = declare_dependency(link_with: numeric_glib_lib,
                                    include_directories: include_directories('.'))

numeric_glib_vala_dep = declare_dependency(dependencies: numeric_glib_dep,
                                           sources: 'numeric-glib-1.0.vapi')

install_headers(['numeric.h', 'numeric-types.h', 'numeric-vector.h'], subdir: 'numeric-glib-1.0')
install_data('numeric-glib-1.0.vapi', install_dir: 'share/vala/vapi')

pkgconfig = import('pkgconfig')
pkgconfig.generate(numeric_glib_lib,
                   version: meson.project_version(),
                   description: 'Numeric data types for GLib via GCC extensions',
                   subdirs: 'numeric-glib-1.0')
