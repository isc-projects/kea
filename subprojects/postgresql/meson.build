project('postgresql')
postgresql = disabler()
pg_config = find_program('pg_config', required: false)
if pg_config.found()
    cflags = run_command([pg_config, '--cflags'], check: false)
    libs = run_command([pg_config, '--libs'], check: false)
    version = run_command([pg_config, '--version'], check: false)
    if cflags.returncode() == 0 and libs.returncode() == 0 and version.returncode() == 0
        pgsql_compile_args = cflags.stdout().split()
        pgsql_link_args = libs.stdout().split()
        pgsql_version = version.stdout().strip()
        postgresql = declare_dependency(
            compile_args: pgsql_compile_args,
            link_args: pgsql_link_args,
            version: pgsql_version,
        )
    endif
endif
