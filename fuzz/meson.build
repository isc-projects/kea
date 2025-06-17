if not FUZZ_OPT.enabled()
    subdir_done()
endif

current_build_dir = meson.current_build_dir()
current_source_dir = meson.current_source_dir()

foreach i : [
    'fuzz_config_kea_dhcp4',
    'fuzz_config_kea_dhcp6',
    'fuzz_http_endpoint_kea_dhcp4',
    'fuzz_http_endpoint_kea_dhcp6',
    'fuzz_packets_kea_dhcp4',
    'fuzz_packets_kea_dhcp6',
    'fuzz_unix_socket_kea_dhcp4',
    'fuzz_unix_socket_kea_dhcp6',
    'fuzz_config_kea_dhcp4/doc-examples',
    'fuzz_config_kea_dhcp6/doc-examples',
]
    command = run_command(GRABBER, f'input/@i@', '*', check: true)
    foreach j : command.stdout().strip().split('\n')
        # configure_file doesn't work with path segments in the output, so let
        # us simulate it with commands.
        run_command(
            ['mkdir', '-p', f'@TOP_BUILD_DIR@/fuzz/input/@i@'],
            check: true,
        )
        run_command(
            ['cp', f'input/@i@/@j@', f'@TOP_BUILD_DIR@/fuzz/input/@i@/@j@'],
            check: true,
        )
    endforeach

endforeach
foreach i : ['kea-dhcp4.conf', 'kea-dhcp6.conf']
    run_command(
        ['cp', f'input/@i@', f'@TOP_BUILD_DIR@/fuzz/input/@i@'],
        check: true,
    )
endforeach

fuzz_sources = ['fuzz.cc', 'fuzz.h', 'main.cc']
cpp_flags = [
    f'-DKEA_LFC_INSTALLATION="@KEA_LFC_INSTALLED@"',
    f'-DKEA_LFC_SOURCES="@KEA_LFC_BUILT@"',
]

includes = [include_directories('.')] + INCLUDES

fuzz_lib = static_library(
    'fuzz_lib',
    fuzz_sources,
    cpp_args: cpp_flags,
    dependencies: [CRYPTO_DEP, GTEST_DEP],
    include_directories: includes,
    link_with: LIBS_BUILT_SO_FAR,
)

FUZZER_EXECUTABLES = []

foreach i : [
    'fuzz_config_kea_dhcp4',
    'fuzz_http_endpoint_kea_dhcp4',
    'fuzz_packets_kea_dhcp4',
    'fuzz_unix_socket_kea_dhcp4',
]
    FUZZER_EXECUTABLES += executable(
        i,
        f'@i@.cc',
        fuzz_sources,
        cpp_args: cpp_flags,
        dependencies: [CRYPTO_DEP, GTEST_DEP],
        include_directories: includes,
        link_with: [dhcp4_lib, kea_testutils_lib, fuzz_lib] + LIBS_BUILT_SO_FAR,
        install: true,
        install_dir: SBINDIR,
        install_rpath: INSTALL_RPATH,
        build_rpath: BUILD_RPATH,
    )
endforeach
foreach i : [
    'fuzz_config_kea_dhcp6',
    'fuzz_http_endpoint_kea_dhcp6',
    'fuzz_packets_kea_dhcp6',
    'fuzz_unix_socket_kea_dhcp6',
]
    FUZZER_EXECUTABLES += executable(
        i,
        f'@i@.cc',
        fuzz_sources,
        cpp_args: cpp_flags,
        dependencies: [CRYPTO_DEP, GTEST_DEP],
        include_directories: includes,
        link_with: [dhcp6_lib, kea_testutils_lib, fuzz_lib] + LIBS_BUILT_SO_FAR,
        install: true,
        install_dir: SBINDIR,
        install_rpath: INSTALL_RPATH,
        build_rpath: BUILD_RPATH,
    )
endforeach

subdir('tests')
