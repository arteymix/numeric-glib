posix = meson.get_compiler('vala').find_library('posix')
test('numeric', executable('numeric-test', 'numeric-test.vala',
                           dependencies: [posix, glib, gobject, numeric_glib, quadmath, dfp]))
