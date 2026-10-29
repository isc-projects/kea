if not TESTS_OPT.enabled()
    subdir_done()
endif

dhcp_rbac_tests_libs = [dhcp_rbac_archive, kea_testutils_lib]
dhcp_rbac_tests = executable(
    'dhcp-rbac-tests',
    'rbac_acl_unittests.cc',
    'rbac_api_unittests.cc',
    'rbac_callout_unittests.cc',
    'rbac_config_unittests.cc',
    'rbac_response_filter_unittests.cc',
    'rbac_role_unittests.cc',
    'rbac_unittests.cc',
    'run_unittests.cc',
    cpp_args: [f'-DAPI_DIR="@TOP_SOURCE_DIR@/src/share/api"'],
    dependencies: [GTEST_DEP],
    include_directories: HINCLUDES + INCLUDES,
    link_with: [dhcp_rbac_tests_libs] + LIBS_BUILT_SO_FAR,
)
test(
    'dhcp-rbac-tests',
    dhcp_rbac_tests,
    is_parallel: false,
    priority: -1,
    protocol: 'gtest',
    timeout: 60,
)
