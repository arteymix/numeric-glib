numeric_glib_lib = library('numeric-glib-1.0', 'numeric.c', 'numeric-vector.c',
                           dependencies: [glib, gobject],
                           link_args: '-Wl,-init=numeric_init',
                           install: true)

numeric_glib = declare_dependency(link_with: numeric_glib_lib,
                                  include_directories: include_directories('.'),
                                  sources: 'numeric-glib-1.0.vapi')

install_headers('numeric.h', subdir: 'numeric-glib-1.0')
install_data('numeric-glib-1.0.vapi', install_dir: 'share/vala/vapi')

pkgconfig = import('pkgconfig')
pkgconfig.generate(name: 'Numeric-GLib',
                   description: 'Numeric data types for GLib via GCC extensions',
                   requires: ['glib-2.0', 'gobject-2.0'],
                   libraries: numeric_glib_lib,
                   filebase: 'numeric-glib-1.0',
                   subdirs: 'numeric-glib-1.0')
