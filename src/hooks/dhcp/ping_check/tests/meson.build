if not TESTS_OPT.enabled()
    subdir_done()
endif

dhcp_ping_check_tests = executable(
    'dhcp-ping-check-tests',
    'config_cache_unittests.cc',
    'icmp_endpoint_unittests.cc',
    'icmp_msg_unittests.cc',
    'icmp_socket_unittests.cc',
    'ping_channel_unittests.cc',
    'ping_check_config_unittests.cc',
    'ping_check_mgr_unittests.cc',
    'ping_context_store_unittests.cc',
    'ping_context_unittests.cc',
    'run_unittests.cc',
    dependencies: [CRYPTO_DEP, GTEST_DEP],
    include_directories: [include_directories('.'), include_directories('..')] + INCLUDES,
    link_with: [dhcp_ping_check_archive] + LIBS_BUILT_SO_FAR,
)

root_tests = 'RootICMPSocketTest.*:RootPingChannelTest.*:RootPingCheckMgr.*:RootPingCheckMgrTest.*'

test(
    'dhcp-ping-check-tests',
    dhcp_ping_check_tests,
    args: [f'--gtest_filter=-@root_tests@'],
    protocol: 'gtest',
    is_parallel: false,
    priority: -1,
)

if PASSWORDLESS_SUDO_SET_UP
    test(
        'sudo-dhcp-ping-check-tests',
        SUDO,
        args: [dhcp_ping_check_tests, f'--gtest_filter=@root_tests@'],
        protocol: 'gtest',
        is_parallel: false,
        priority: -1,
        suite: 'sudo-tests',
    )
endif
