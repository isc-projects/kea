if not gtest.found() or not NETCONF_DEPS_FOUND
    subdir_done()
endif

kea_yang_testutils_lib = static_library(
    'kea-yang-testutils',
    'translator_test.cc',
    dependencies: NETCONF_DEPS_ARRAY + [gtest],
    include_directories: [include_directories('.')] + INCLUDES,
    override_options: ['cpp_std=c++20'],
)
