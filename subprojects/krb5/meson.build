project('krb5')
current_source_dir = meson.current_source_dir()
krb5 = disabler()
krb5_config = find_program('krb5-config', required: false)

if krb5_config.found()
    # Detect vendor.
    vendor_cmd = run_command([krb5_config, '--vendor'], check: false)
    if vendor_cmd.returncode() != 0
        path = krb5_config.full_path()
        message(f'Very old and not usable config script at @path@')
    else
        vendor = vendor_cmd.stdout().strip()
    endif

    cflags = run_command([krb5_config, '--cflags', 'gssapi'], check: false)
    libs = run_command([krb5_config, '--libs', 'gssapi'], check: false)
    version = run_command([krb5_config, '--version'], check: false)
    if vendor_cmd.returncode() == 0 and cflags.returncode() == 0 and libs.returncode() == 0 and version.returncode() == 0
        krb5_version = version.stdout().strip()
        krb5 = declare_dependency(
            compile_args: cflags.stdout().split(),
            link_args: libs.stdout().split(),
            version: krb5_version,
            variables: {'vendor': vendor},
        )
    endif
endif
