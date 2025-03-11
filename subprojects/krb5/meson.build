project('krb5')
current_source_dir = meson.current_source_dir()
krb5 = disabler()
krb5_config = find_program('krb5-config', required: false)

check_heimdal = find_program(
    f'@current_source_dir@/check-heimdal.sh',
    required: true,
)
if krb5_config.found()
    cflags = run_command([krb5_config, '--cflags', 'gssapi'], check: false)
    libs = run_command([krb5_config, '--libs', 'gssapi'], check: false)
    version = run_command([krb5_config, '--version'], check: false)
    heimdal = run_command(check_heimdal, krb5_config.full_path(), check: false)
    if heimdal.returncode() == 0
        vendor = 'Heimdal'
    else
        vendor = 'MIT'
    endif
    if cflags.returncode() == 0 and libs.returncode() == 0 and version.returncode() == 0
        krb5_version = version.stdout().strip()
        krb5 = declare_dependency(
            compile_args: cflags.stdout().split(),
            link_args: libs.stdout().split(),
            version: krb5_version,
            variables: {'vendor': vendor},
        )
    endif
endif
