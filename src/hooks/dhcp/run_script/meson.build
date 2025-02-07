dhcp_run_script_lib = shared_library(
    'dhcp_run_script',
    'run_script.cc',
    'run_script_callouts.cc',
    'run_script_log.cc',
    'run_script_messages.cc',
    'version.cc',
    dependencies: [crypto],
    include_directories: [include_directories('.')] + INCLUDES,
    install: true,
    install_dir: 'lib/kea/hooks',
    link_with: LIBS_BUILT_SO_FAR,
    name_suffix: 'so',
)
dhcp_run_script_archive = static_library(
    'dhcp_run_script',
    objects: dhcp_run_script_lib.extract_all_objects(recursive: false),
)
# Do tests first
subdir('tests')
subdir('libloadtests')
