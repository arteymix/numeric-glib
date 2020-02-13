project('Numeric-GLib', 'c', 'vala',
        meson_version: '>=0.46')

add_project_arguments(['--vapidir', join_paths(meson.current_source_dir(), 'vapi')],
                      language: 'vala')

glib_dep = dependency('glib-2.0')
gobject_dep = dependency('gobject-2.0')
quadmath_dep = meson.get_compiler('c').find_library('quadmath')
dfp_dep = dependency('libdfp', required: false)

subdir('src')
subdir('tests')
