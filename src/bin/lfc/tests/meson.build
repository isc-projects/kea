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
test('kea-lfc-tests', kea_lfc_tests, protocol: 'gtest')
