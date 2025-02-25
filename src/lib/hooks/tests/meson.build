if not gtest.found()
    subdir_done()
endif

kea_hooks_conf_data = configuration_data()
kea_hooks_conf_data.set('abs_builddir', meson.current_build_dir())
kea_hooks_conf_data.set('dotlibs', '')
configure_file(
    input: 'marker_file.h.in',
    output: 'marker_file.h',
    configuration: kea_hooks_conf_data,
)
configure_file(
    input: 'test_libraries.h.in',
    output: 'test_libraries.h',
    configuration: kea_hooks_conf_data,
)

nvl = shared_library(
    'nvl',
    'no_version_library.cc',
    include_directories: [include_directories('.')] + INCLUDES,
    link_with: LIBS_BUILT_SO_FAR,
    build_rpath: '/nowhere',
    name_suffix: 'so',
)
ivl = shared_library(
    'ivl',
    'incorrect_version_library.cc',
    include_directories: [include_directories('.')] + INCLUDES,
    link_with: LIBS_BUILT_SO_FAR,
    build_rpath: '/nowhere',
    name_suffix: 'so',
)
fxl = shared_library(
    'fxl',
    'framework_exception_library.cc',
    include_directories: [include_directories('.')] + INCLUDES,
    link_with: LIBS_BUILT_SO_FAR,
    build_rpath: '/nowhere',
    name_suffix: 'so',
)
bcl = shared_library(
    'bcl',
    'basic_callout_library.cc',
    include_directories: [include_directories('.')] + INCLUDES,
    link_with: LIBS_BUILT_SO_FAR,
    build_rpath: '/nowhere',
    name_suffix: 'so',
)
lcl = shared_library(
    'lcl',
    'load_callout_library.cc',
    include_directories: [include_directories('.')] + INCLUDES,
    link_with: LIBS_BUILT_SO_FAR,
    build_rpath: '/nowhere',
    name_suffix: 'so',
)
lecl = shared_library(
    'lecl',
    'load_error_callout_library.cc',
    include_directories: [include_directories('.')] + INCLUDES,
    link_with: LIBS_BUILT_SO_FAR,
    build_rpath: '/nowhere',
    name_suffix: 'so',
)
ucl = shared_library(
    'ucl',
    'unload_callout_library.cc',
    include_directories: [include_directories('.')] + INCLUDES,
    link_with: LIBS_BUILT_SO_FAR,
    build_rpath: '/nowhere',
    name_suffix: 'so',
)
fcl = shared_library(
    'fcl',
    'full_callout_library.cc',
    include_directories: [include_directories('.')] + INCLUDES,
    link_with: LIBS_BUILT_SO_FAR,
    build_rpath: '/nowhere',
    name_suffix: 'so',
)
pcl = shared_library(
    'pcl',
    'callout_params_library.cc',
    include_directories: [include_directories('.')] + INCLUDES,
    link_with: LIBS_BUILT_SO_FAR,
    build_rpath: '/nowhere',
    name_suffix: 'so',
)
acl = shared_library(
    'acl',
    'async_callout_library.cc',
    include_directories: [include_directories('.')] + INCLUDES,
    link_with: LIBS_BUILT_SO_FAR,
    build_rpath: '/nowhere',
    name_suffix: 'so',
)

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
test(
    'kea-hooks-tests',
    kea_hooks_tests,
    depends: [nvl, ivl, fxl, bcl, lcl, lecl, ucl, fcl, pcl, acl],
    protocol: 'gtest',
)

