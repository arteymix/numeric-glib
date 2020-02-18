test('numeric', executable('numeric-test', 'numeric-test.vala',
                           dependencies: [glib_dep, gobject_dep, numeric_glib_vala_dep, quadmath_dep]))

if dfp_dep.found()
    test('decimal', executable('decimal-test', 'decimal-test.vala',
                               dependencies: [glib_dep, gobject_dep, numeric_glib_vala_dep, quadmath_dep, dfp_dep]))
    test('decimal-c', executable('decimal-c-test', 'decimal-c-test.c',
                                 dependencies: [glib_dep, gobject_dep, numeric_glib_dep, quadmath_dep, dfp_dep]))
endif
