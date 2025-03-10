project('krb5')
krb5 = disabler()
krb5_config = find_program('krb5-config', required: false)
if krb5_config.found()
    cflags = run_command([krb5_config, '--cflags', 'gssapi'], check: false)
    libs = run_command([krb5_config, '--libs', 'gssapi'], check: false)
    version = run_command([krb5_config, '--version'], check: false)
    if cflags.returncode() == 0 and libs.returncode() == 0 and version.returncode() == 0
        krb5_version = version.stdout().strip()
        krb5 = declare_dependency(
            compile_args: cflags.stdout().split(),
            link_args: libs.stdout().split(),
            version: krb5_version,
        )
    endif
endif
