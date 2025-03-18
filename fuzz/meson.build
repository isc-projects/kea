if not FUZZ_OPT.enabled()
    subdir_done()
endif

subdir('tests')

fuzz_sources = ['fuzz.cc', 'fuzz.h']
cpp_flags = [
    f'-DKEA_LFC_INSTALLATION="@KEA_LFC_INSTALLED@"',
    f'-DKEA_LFC_SOURCES="@KEA_LFC_BUILT@"',
]
if FUZZING_WITH_CLUSTERFUZZLITE
    cpp_flags = ['-fsanitize=fuzzer', '-gdwarf-4']
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
)

executable(
    'fuzz_config_kea_dhcp6',
    'fuzz_config_kea_dhcp6.cc',
    fuzz_sources,
    cpp_args: cpp_flags,
    dependencies: [CRYPTO_DEP, GTEST_DEP],
    include_directories: includes,
    link_with: [dhcp6_lib, fuzz_lib] + LIBS_BUILT_SO_FAR,
)

executable(
    'fuzz_http_endpoint_kea_dhcp4',
    'fuzz_http_endpoint_kea_dhcp4.cc',
    fuzz_sources,
    cpp_args: cpp_flags,
    dependencies: [CRYPTO_DEP, GTEST_DEP],
    include_directories: includes,
    link_with: [dhcp4_lib, fuzz_lib] + LIBS_BUILT_SO_FAR,
)

executable(
    'fuzz_http_endpoint_kea_dhcp6',
    'fuzz_http_endpoint_kea_dhcp6.cc',
    fuzz_sources,
    cpp_args: cpp_flags,
    dependencies: [CRYPTO_DEP, GTEST_DEP],
    include_directories: includes,
    link_with: [dhcp6_lib, fuzz_lib] + LIBS_BUILT_SO_FAR,
)

executable(
    'fuzz_packets_kea_dhcp4',
    'fuzz_packets_kea_dhcp4.cc',
    fuzz_sources,
    cpp_args: cpp_flags,
    dependencies: [CRYPTO_DEP, GTEST_DEP],
    include_directories: includes,
    link_with: [dhcp4_lib, kea_dhcpsrv_lib, fuzz_lib] + LIBS_BUILT_SO_FAR,
)

executable(
    'fuzz_packets_kea_dhcp6',
    'fuzz_packets_kea_dhcp6.cc',
    fuzz_sources,
    cpp_args: cpp_flags,
    dependencies: [CRYPTO_DEP, GTEST_DEP],
    include_directories: includes,
    link_with: [dhcp6_lib, kea_dhcpsrv_lib, fuzz_lib] + LIBS_BUILT_SO_FAR,
)

executable(
    'fuzz_unix_socket_kea_dhcp4',
    'fuzz_unix_socket_kea_dhcp4.cc',
    fuzz_sources,
    cpp_args: cpp_flags,
    dependencies: [CRYPTO_DEP, GTEST_DEP],
    include_directories: includes,
    link_with: [dhcp4_lib, kea_testutils_lib, fuzz_lib] + LIBS_BUILT_SO_FAR,
)

executable(
    'fuzz_unix_socket_kea_dhcp6',
    'fuzz_unix_socket_kea_dhcp6.cc',
    fuzz_sources,
    cpp_args: cpp_flags,
    dependencies: [CRYPTO_DEP, GTEST_DEP],
    include_directories: includes,
    link_with: [dhcp6_lib, kea_testutils_lib, fuzz_lib] + LIBS_BUILT_SO_FAR,
)
