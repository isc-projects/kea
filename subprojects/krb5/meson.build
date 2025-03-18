project('krb5')
current_source_dir = meson.current_source_dir()
krb5 = disabler()
krb5_config = find_program('krb5-config', required: false)

if krb5_config.found()
    # Detect vendor.
    vendor_cmd = run_command([krb5_config, '--vendor'], check: false)
    vendor = 'unknown'
    if vendor_cmd.returncode() == 0
        vendor = vendor_cmd.stdout().strip()
    else
        all = run_command([krb5_config, '--all'], check: false)
        if all.returncode() == 0
            foreach i : all.stdout().split('\n')
                if i.startswith('Vendor')
                    vendor = i.split(':')[1].strip()
                    break
                endif
            endforeach
        endif
    endif

    cflags = run_command([krb5_config, '--cflags', 'gssapi'], check: false)
    libs = run_command([krb5_config, '--libs', 'gssapi'], check: false)
    version = run_command([krb5_config, '--version'], check: false)
    if cflags.returncode() == 0 and libs.returncode() == 0 and version.returncode() == 0
        krb5_version = version.stdout().strip()
        krb5 = declare_dependency(
            compile_args: cflags.stdout().split(),
            link_args: libs.stdout().split(),
            version: krb5_version,
            variables: {
                'cflags': cflags.stdout().strip(),
                'libs': libs.stdout().strip(),
                'vendor': vendor,
            },
        )
    endif
endif
