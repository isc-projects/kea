if not gtest.found()
    subdir_done()
endif

kea_yang_testutils_lib = static_library(
    'kea-yang-testutils',
    'translator_test.cc',
    dependencies: netconf_deps_array + [gtest],
    include_directories: [include_directories('.')] + INCLUDES,
)
