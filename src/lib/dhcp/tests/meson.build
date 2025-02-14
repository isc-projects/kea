if not gtest.found()
    subdir_done()
endif

if SYSTEM == 'linux'
    pkt_filter_xpf_unittest_cc = 'pkt_filter_lpf_unittest.cc'
elif SYSTEM == 'freebsd' or SYSTEM == 'netbsd' or SYSTEM == 'openbsd' or SYSTEM == 'darwin'
    pkt_filter_xpf_unittest_cc = 'pkt_filter_bpf_unittest.cc'
else
    error(f'Build failed: Unsupported system "@SYSTEM@".')
endif

current_build_dir = meson.current_build_dir()
libs_testutils = [kea_dhcp_testutils_lib, kea_testutils_lib]
kea_dhcp_tests = executable(
    'kea-dhcp-tests',
    'classify_unittest.cc',
    'duid_factory_unittest.cc',
    'duid_unittest.cc',
    'hwaddr_unittest.cc',
    'iface_mgr_unittest.cc',
    'libdhcp++_unittest.cc',
    'opaque_data_tuple_unittest.cc',
    'option4_addrlst_unittest.cc',
    'option4_client_fqdn_unittest.cc',
    'option4_dnr_unittest.cc',
    'option6_addrlst_unittest.cc',
    'option6_auth_unittest.cc',
    'option6_client_fqdn_unittest.cc',
    'option6_dnr_unittest.cc',
    'option6_ia_unittest.cc',
    'option6_iaaddr_unittest.cc',
    'option6_iaprefix_unittest.cc',
    'option6_pdexclude_unittest.cc',
    'option6_status_code_unittest.cc',
    'option_classless_static_route_unittest.cc',
    'option_copy_unittest.cc',
    'option_custom_unittest.cc',
    'option_data_types_unittest.cc',
    'option_definition_unittest.cc',
    'option_int_array_unittest.cc',
    'option_int_unittest.cc',
    'option_opaque_data_tuples_unittest.cc',
    'option_space_unittest.cc',
    'option_string_unittest.cc',
    'option_unittest.cc',
    'option_vendor_class_unittest.cc',
    'option_vendor_unittest.cc',
    'packet_queue4_unittest.cc',
    'packet_queue6_unittest.cc',
    'packet_queue_mgr4_unittest.cc',
    'packet_queue_mgr6_unittest.cc',
    'pkt4_unittest.cc',
    'pkt4o6_unittest.cc',
    'pkt6_unittest.cc',
    'pkt_filter6_test_utils.cc',
    'pkt_filter_inet6_unittest.cc',
    'pkt_filter_inet_unittest.cc',
    'pkt_filter_test_utils.cc',
    'pkt_filter_unittest.cc',
    'protocol_util_unittest.cc',
    'run_unittests.cc',
    pkt_filter_xpf_unittest_cc,
    dependencies: [gtest, crypto],
    cpp_args: [f'-DTEST_DATA_BUILDDIR="@current_build_dir@"'],
    include_directories: [include_directories('.')] + INCLUDES,
    link_with: [kea_util_unittests_lib, libs_testutils] + LIBS_BUILT_SO_FAR,
)
test('kea-dhcp-tests', kea_dhcp_tests, protocol: 'gtest')
