if not FUZZ_OPT.enabled()
    subdir_done()
endif

current_source_dir = meson.current_source_dir()
list = []
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
    command = run_command(
        GRABBER,
        f'input/@i@',
        '*',
        check: true,
    )
    foreach j : command.stdout().strip().split('\n')
        # configure_file doesn't work with path segments in the output, so let
        # us simulate it with commands.
        run_command([f'mkdir', '-p', f'@TOP_BUILD_DIR@/fuzz/input/@i@'], check: true)
        run_command([f'cp', f'input/@i@/@j@', f'@TOP_BUILD_DIR@/fuzz/input/@i@/@j@'], check: true)
    endforeach
endforeach

fuzz_sources = ['fuzz.cc', 'fuzz.h']
cpp_flags = [
    f'-DKEA_LFC_INSTALLATION="@KEA_LFC_INSTALLED@"',
    f'-DKEA_LFC_SOURCES="@KEA_LFC_BUILT@"',
]
if FUZZING_WITH_CLUSTERFUZZLITE
    cpp_flags += ['-fsanitize=fuzzer', '-gdwarf-4']
else
    fuzz_sources += ['main.cc']
endif

includes = [include_directories('.')] + INCLUDES

fuzz_lib = static_library(
    'fuzz_lib',
    fuzz_sources,
    cpp_args: cpp_flags,
    dependencies: [CRYPTO_DEP, GTEST_DEP],
    include_directories: includes,
    link_with: LIBS_BUILT_SO_FAR,
)

executable(
    'fuzz_config_kea_dhcp4',
    'fuzz_config_kea_dhcp4.cc',
    fuzz_sources,
    cpp_args: cpp_flags,
    dependencies: [CRYPTO_DEP, GTEST_DEP],
    include_directories: includes,
    link_with: [dhcp4_lib, fuzz_lib] + LIBS_BUILT_SO_FAR,
    install: true,
    install_dir: SBINDIR,
)

executable(
    'fuzz_config_kea_dhcp6',
    'fuzz_config_kea_dhcp6.cc',
    fuzz_sources,
    cpp_args: cpp_flags,
    dependencies: [CRYPTO_DEP, GTEST_DEP],
    include_directories: includes,
    link_with: [dhcp6_lib, fuzz_lib] + LIBS_BUILT_SO_FAR,
    install: true,
    install_dir: SBINDIR,
)

executable(
    'fuzz_http_endpoint_kea_dhcp4',
    'fuzz_http_endpoint_kea_dhcp4.cc',
    fuzz_sources,
    cpp_args: cpp_flags,
    dependencies: [CRYPTO_DEP, GTEST_DEP],
    include_directories: includes,
    link_with: [dhcp4_lib, fuzz_lib] + LIBS_BUILT_SO_FAR,
    install: true,
    install_dir: SBINDIR,
)

executable(
    'fuzz_http_endpoint_kea_dhcp6',
    'fuzz_http_endpoint_kea_dhcp6.cc',
    fuzz_sources,
    cpp_args: cpp_flags,
    dependencies: [CRYPTO_DEP, GTEST_DEP],
    include_directories: includes,
    link_with: [dhcp6_lib, fuzz_lib] + LIBS_BUILT_SO_FAR,
    install: true,
    install_dir: SBINDIR,
)

executable(
    'fuzz_packets_kea_dhcp4',
    'fuzz_packets_kea_dhcp4.cc',
    fuzz_sources,
    cpp_args: cpp_flags,
    dependencies: [CRYPTO_DEP, GTEST_DEP],
    include_directories: includes,
    link_with: [dhcp4_lib, kea_dhcpsrv_lib, fuzz_lib] + LIBS_BUILT_SO_FAR,
    install: true,
    install_dir: SBINDIR,
)

executable(
    'fuzz_packets_kea_dhcp6',
    'fuzz_packets_kea_dhcp6.cc',
    fuzz_sources,
    cpp_args: cpp_flags,
    dependencies: [CRYPTO_DEP, GTEST_DEP],
    include_directories: includes,
    link_with: [dhcp6_lib, kea_dhcpsrv_lib, fuzz_lib] + LIBS_BUILT_SO_FAR,
    install: true,
    install_dir: SBINDIR,
)

executable(
    'fuzz_unix_socket_kea_dhcp4',
    'fuzz_unix_socket_kea_dhcp4.cc',
    fuzz_sources,
    cpp_args: cpp_flags,
    dependencies: [CRYPTO_DEP, GTEST_DEP],
    include_directories: includes,
    link_with: [dhcp4_lib, kea_testutils_lib, fuzz_lib] + LIBS_BUILT_SO_FAR,
    install: true,
    install_dir: SBINDIR,
)

executable(
    'fuzz_unix_socket_kea_dhcp6',
    'fuzz_unix_socket_kea_dhcp6.cc',
    fuzz_sources,
    cpp_args: cpp_flags,
    dependencies: [CRYPTO_DEP, GTEST_DEP],
    include_directories: includes,
    link_with: [dhcp6_lib, kea_testutils_lib, fuzz_lib] + LIBS_BUILT_SO_FAR,
    install: true,
    install_dir: SBINDIR,
)

subdir('tests')
