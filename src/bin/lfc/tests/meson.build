if not gtest.found()
    subdir_done()
endif

CURRENT_BUILD_DIR = meson.current_build_dir()
lfc_unittests = executable(
    'lfc-unittests',
    'lfc_controller_unittests.cc',
    'lfc_unittests.cc',
    cpp_args: [f'-DTEST_DATA_BUILDDIR="@CURRENT_BUILD_DIR@"'],
    dependencies: [gtest],
    include_directories: [include_directories('.')] + INCLUDES,
    link_with: [lfc_lib] + LIBS_BUILT_SO_FAR,
)
test('lfc_unittests', lfc_unittests, protocol: 'gtest')
