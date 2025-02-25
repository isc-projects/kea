if not gtest.found()
    subdir_done()
endif

current_build_dir = meson.current_build_dir()
kea_lfc_tests = executable(
    'kea-lfc-tests',
    'lfc_controller_unittests.cc',
    'lfc_unittests.cc',
    cpp_args: [f'-DTEST_DATA_BUILDDIR="@current_build_dir@"'],
    dependencies: [gtest],
    include_directories: [include_directories('.')] + INCLUDES,
    link_with: [lfc_lib] + LIBS_BUILT_SO_FAR,
)
test(
    'kea-lfc-tests',
    kea_lfc_tests,
    # kea_lfc is not really a dependency of this set of tests, but it is used
    # in other tests such as memfile_tests.sh, and since it cannot be specified
    # on the "depends" of a shell test, specify it here instead to have it
    # created on "meson test".
    depends: [kea_lfc],
    protocol: 'gtest',
)
