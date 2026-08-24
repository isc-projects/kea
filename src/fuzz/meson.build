if not FUZZ_OPT.enabled()
    subdir_done()
endif

current_build_dir = meson.current_build_dir()
current_source_dir = meson.current_source_dir()

fuzz_sources = ['fuzz.cc', 'fuzz.h']
cpp_flags = [
    f'-DKEA_LFC_INSTALLATION="@KEA_LFC_INSTALLED@"',
    f'-DKEA_LFC_SOURCES="@KEA_LFC_BUILT@"',
]

# The include paths are a bit invasive, but if we wanted to only have "../hooks" we would need to
# tweak the include paths in the hooks themselves either to be referenced from "src" or
# "src/hooks" or to have quotes instead of angled brackets and that is more work.
includes = [
    include_directories('.'),
    include_directories('../hooks'),
    include_directories('../hooks/d2/gss_tsig'),
    include_directories('../hooks/dhcp/mysql'),
    include_directories('../hooks/dhcp/pgsql'),
    include_directories('../hooks/dhcp/user_chk'),
] + INCLUDES

fuzz_lib = static_library(
    'fuzz_lib',
    fuzz_sources,
    cpp_args: cpp_flags,
    dependencies: [KRB5_DEP, CRYPTO_DEP, GTEST_DEP],
    include_directories: includes,
    link_with: LIBS_BUILT_SO_FAR,
)

FUZZING_HARNESSES = []

foreach i : [
    'fuzz_config_kea_dhcp4',
    'fuzz_http_endpoint_kea_dhcp4',
    'fuzz_packets_kea_dhcp4',
    'fuzz_unix_socket_kea_dhcp4',
]
    FUZZING_HARNESSES += static_library(
        i,
        f'@i@.cc',
        fuzz_sources,
        cpp_args: cpp_flags,
        dependencies: [CRYPTO_DEP, GTEST_DEP],
        include_directories: includes,
        link_with: [dhcp4_lib, kea_testutils_lib, fuzz_lib] + LIBS_BUILT_SO_FAR,
        build_rpath: BUILD_RPATH,
    )
endforeach

foreach i : [
    'fuzz_config_kea_dhcp6',
    'fuzz_http_endpoint_kea_dhcp6',
    'fuzz_packets_kea_dhcp6',
    'fuzz_unix_socket_kea_dhcp6',
]
    FUZZING_HARNESSES += static_library(
        i,
        f'@i@.cc',
        fuzz_sources,
        cpp_args: cpp_flags,
        dependencies: [CRYPTO_DEP, GTEST_DEP],
        include_directories: includes,
        link_with: [dhcp6_lib, kea_testutils_lib, fuzz_lib] + LIBS_BUILT_SO_FAR,
        build_rpath: BUILD_RPATH,
    )
endforeach

# From external contribution.
# These source files include LLVM's FuzzedDataProvider.h.
# As a result, they can only be compiled using clang++.
cpp = meson.get_compiler('cpp')
if cpp.get_id() == 'clang'
    maybe_ddns_gss_tsig_lib = []
    if KRB5_DEP.found()
        maybe_ddns_gss_tsig_lib += [ddns_gss_tsig_lib]
    endif
    fuzz_libs = [
        d2_lib,
        dhcp_lease_query_lib,
        dhcp_flex_id_lib,
        dhcp_ddns_tuning_lib,
        dhcp_lease_cmds_lib,
        dhcp_radius_lib,
        dhcp_run_script_lib,
        dhcp_user_chk_lib,
        kea_testutils_lib,
        fuzz_lib,
    ]
    fuzz_libs += maybe_ddns_gss_tsig_lib
    foreach i : [
        'fuzz_cc',
        'fuzz_crypto',
        'fuzz_cryptolink',
        'fuzz_d2',
        'fuzz_dhcpsrv',
        'fuzz_dhcpsrv_csv_lease',
        'fuzz_dns',
        'fuzz_encode',
        'fuzz_http',
        'fuzz_ioaddress',
        'fuzz_util',
    ]
        FUZZING_HARNESSES += static_library(
            i,
            f'@i@.cc',
            'empty_llvm_functions.cc',
            'helper_func.cc',
            fuzz_sources,
            cpp_args: cpp_flags,
            dependencies: [CRYPTO_DEP, GTEST_DEP, KRB5_DEP],
            include_directories: includes,
            link_with: fuzz_libs + LIBS_BUILT_SO_FAR,
            build_rpath: BUILD_RPATH,
        )
    endforeach
    fuzz_libs = [
        dhcp_lease_query_lib,
        dhcp_flex_id_lib,
        dhcp_ddns_tuning_lib,
        dhcp_lease_cmds_lib,
        dhcp_radius_lib,
        dhcp_run_script_lib,
        dhcp_user_chk_lib,
        dhcp4_lib,
        kea_testutils_lib,
        fuzz_lib,
    ]
    fuzz_libs += maybe_ddns_gss_tsig_lib
    foreach i : [
        'fuzz_dhcp_parser4',
        'fuzz_dhcp_pkt4',
        'fuzz_dhcp_pkt_process4',
        'fuzz_eval4',
        'fuzz_hook_ddns_tuning4',
        'fuzz_hook_flex_id4',
        'fuzz_hook_lease_query4',
        'fuzz_hook_radius4',
        'fuzz_hook_run_script4',
        'fuzz_hook_user_chk4',
    ]
        FUZZING_HARNESSES += static_library(
            i,
            f'@i@.cc',
            'empty_llvm_functions.cc',
            'helper_func.cc',
            fuzz_sources,
            cpp_args: cpp_flags,
            dependencies: [CRYPTO_DEP, GTEST_DEP, KRB5_DEP],
            include_directories: includes,
            link_with: fuzz_libs + LIBS_BUILT_SO_FAR,
            build_rpath: BUILD_RPATH,
        )
    endforeach
    fuzz_libs = [
        dhcp_lease_query_lib,
        dhcp_flex_id_lib,
        dhcp_ddns_tuning_lib,
        dhcp_lease_cmds_lib,
        dhcp_radius_lib,
        dhcp_run_script_lib,
        dhcp_user_chk_lib,
        dhcp6_lib,
        kea_testutils_lib,
        fuzz_lib,
    ]
    fuzz_libs += maybe_ddns_gss_tsig_lib
    foreach i : [
        'fuzz_dhcp_parser6',
        'fuzz_dhcp_pkt6',
        'fuzz_dhcp_pkt_process6',
        'fuzz_eval6',
        'fuzz_hook_ddns_tuning6',
        'fuzz_hook_flex_id6',
        'fuzz_hook_lease_query6',
        'fuzz_hook_radius6',
        'fuzz_hook_run_script6',
        'fuzz_hook_user_chk6',
    ]
        FUZZING_HARNESSES += static_library(
            i,
            f'@i@.cc',
            'empty_llvm_functions.cc',
            'helper_func.cc',
            fuzz_sources,
            cpp_args: cpp_flags,
            dependencies: [CRYPTO_DEP, GTEST_DEP, KRB5_DEP],
            include_directories: includes,
            link_with: fuzz_libs + LIBS_BUILT_SO_FAR,
            build_rpath: BUILD_RPATH,
        )
    endforeach
    if MYSQL_DEP.found()
        foreach i : ['fuzz_mysql4', 'fuzz_mysql6']
            FUZZING_HARNESSES += static_library(
                i,
                f'@i@.cc',
                'empty_llvm_functions.cc',
                'helper_func.cc',
                'mysqlmock.cc',
                fuzz_sources,
                cpp_args: cpp_flags,
                dependencies: [MYSQL_DEP, CRYPTO_DEP, GTEST_DEP, KRB5_DEP],
                include_directories: includes,
                link_with: fuzz_libs + [dhcp_mysql_lib] + LIBS_BUILT_SO_FAR,
                build_rpath: BUILD_RPATH,
            )
        endforeach
    endif
    if KRB5_DEP.found()
        files = ['fuzz_hook_tsig']
        maybe_pgsqlmock = []
        maybe_pgsql_lib = []
        if POSTGRESQL_DEP.found()
            files += ['fuzz_pgsql4', 'fuzz_pgsql6']
            maybe_pgsqlmock += ['pgsqlmock.cc']
            maybe_pgsql_lib += [dhcp_pgsql_lib]
        endif
        foreach i : files
            FUZZING_HARNESSES += static_library(
                i,
                f'@i@.cc',
                'empty_llvm_functions.cc',
                'helper_func.cc',
                maybe_pgsqlmock,
                fuzz_sources,
                cpp_args: cpp_flags,
                dependencies: [POSTGRESQL_DEP, CRYPTO_DEP, GTEST_DEP, KRB5_DEP],
                include_directories: includes,
                link_with: fuzz_libs + maybe_pgsql_lib + LIBS_BUILT_SO_FAR,
                build_rpath: BUILD_RPATH,
            )
        endforeach
    endif
endif

subdir('corp')
subdir('tests')
