subdir('input')
subdir('tests')

fuzz_sources = ['fuzz.cc', 'fuzz.h']
cpp_flags = []
if FUZZING_IN_CI
    cpp_flags = ['-fsanitize=fuzzer', '-gdwarf-4']
else
    fuzz_sources += ['main.cc']
endif

fuzz_lib = static_library(
    'fuzz_lib',
    fuzz_sources,
    cpp_args: cpp_flags + [
        f'-DKEA_LFC_SOURCES="@KEA_LFC@"',
        f'-DKEA_LFC_INSTALLATION="@PREFIX@/sbin/kea-lfc"',
    ],
    dependencies: [crypto],
    include_directories: [include_directories('.')] + INCLUDES,
)

executable(
    'fuzz_config_kea_dhcp4',
    'fuzz_config_kea_dhcp4.cc',
    fuzz_sources,
    cpp_args: cpp_flags + [
        f'-DKEA_LFC_SOURCES="@KEA_LFC@"',
        f'-DKEA_LFC_INSTALLATION="@PREFIX@/sbin/kea-lfc"',
    ],
    dependencies: [crypto],
    include_directories: [include_directories('.')] + INCLUDES,
    link_with: [dhcp4_lib, fuzz_lib] + LIBS_BUILT_SO_FAR,
)
