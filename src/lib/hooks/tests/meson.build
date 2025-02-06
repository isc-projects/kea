if not gtest.found()
    subdir_done()
endif

# Generate marker_file.h test_libraries.h
kea_hooks_tests = executable(
    'kea-hooks-tests',
    'callout_handle_associate_unittest.cc',
    'callout_handle_unittest.cc',
    'callout_manager_unittest.cc',
    'handles_unittest.cc',
    'hooks_manager_unittest.cc',
    'library_manager_collection_unittest.cc',
    'library_manager_unittest.cc',
    'parking_lots_unittest.cc',
    'run_unittests.cc',
    'server_hooks_unittest.cc',
    dependencies: [gtest],
    include_directories: [include_directories('.')] + INCLUDES,
    link_with: [kea_util_unittests_lib] + LIBS_BUILT_SO_FAR,
)
test('kea_hooks_tests', kea_hooks_tests, protocol: 'gtest')

kea_hooks_conf_data = configuration_data()
kea_hooks_conf_data.set('abs_builddir', meson.current_build_dir())
configure_file(
    input: 'marker_file.h.in',
    output: 'marker_file.h',
    configuration: kea_hooks_conf_data,
)
configure_file(
    input: 'meson-test_libraries.h.in',
    output: 'test_libraries.h',
    configuration: kea_hooks_conf_data,
)

shared_library(
    'nvl',
    'no_version_library.cc',
    dependencies: [boost],
    include_directories: [include_directories('.')] + INCLUDES,
    link_with: LIBS_BUILT_SO_FAR,
    build_rpath: '/nowhere',
    name_suffix: 'so',
)
shared_library(
    'ivl',
    'incorrect_version_library.cc',
    dependencies: [boost],
    include_directories: [include_directories('.')] + INCLUDES,
    link_with: LIBS_BUILT_SO_FAR,
    build_rpath: '/nowhere',
    name_suffix: 'so',
)
shared_library(
    'fxl',
    'framework_exception_library.cc',
    dependencies: [boost],
    include_directories: [include_directories('.')] + INCLUDES,
    link_with: LIBS_BUILT_SO_FAR,
    build_rpath: '/nowhere',
    name_suffix: 'so',
)
shared_library(
    'bcl',
    'basic_callout_library.cc',
    dependencies: [boost],
    include_directories: [include_directories('.')] + INCLUDES,
    link_with: LIBS_BUILT_SO_FAR,
    build_rpath: '/nowhere',
    name_suffix: 'so',
)
shared_library(
    'lcl',
    'load_callout_library.cc',
    dependencies: [boost],
    include_directories: [include_directories('.')] + INCLUDES,
    link_with: LIBS_BUILT_SO_FAR,
    build_rpath: '/nowhere',
    name_suffix: 'so',
)
shared_library(
    'lecl',
    'load_error_callout_library.cc',
    dependencies: [boost],
    include_directories: [include_directories('.')] + INCLUDES,
    link_with: LIBS_BUILT_SO_FAR,
    build_rpath: '/nowhere',
    name_suffix: 'so',
)
shared_library(
    'ucl',
    'unload_callout_library.cc',
    dependencies: [boost],
    include_directories: [include_directories('.')] + INCLUDES,
    link_with: LIBS_BUILT_SO_FAR,
    build_rpath: '/nowhere',
    name_suffix: 'so',
)
shared_library(
    'fcl',
    'full_callout_library.cc',
    dependencies: [boost],
    include_directories: [include_directories('.')] + INCLUDES,
    link_with: LIBS_BUILT_SO_FAR,
    build_rpath: '/nowhere',
    name_suffix: 'so',
)
shared_library(
    'pcl',
    'callout_params_library.cc',
    dependencies: [boost],
    include_directories: [include_directories('.')] + INCLUDES,
    link_with: LIBS_BUILT_SO_FAR,
    build_rpath: '/nowhere',
    name_suffix: 'so',
)
shared_library(
    'acl',
    'async_callout_library.cc',
    dependencies: [boost],
    include_directories: [include_directories('.')] + INCLUDES,
    link_with: LIBS_BUILT_SO_FAR,
    build_rpath: '/nowhere',
    name_suffix: 'so',
)
