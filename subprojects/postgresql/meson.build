project('postgresql')
postgresql = disabler()
pg_config = find_program('pg_config', required: false)
if pg_config.found()
    cppflags = run_command([pg_config, '--cppflags'], check: false)
    includedir = run(command[pg_config, '--includedir'], check: false)
    libs = run_command([pg_config, '--libs'], check: false)
    version = run_command([pg_config, '--version'], check: false)
    if cppflags.returncode() == 0 and includedir.returncode() == 0 and libs.returncode() == 0 and version.returncode() == 0
        pgsql_compile_args = cppflags.stdout().split()
        pgsql_includedir_args = includedir.stdout().split()
        pgsql_link_args = libs.stdout().split()
        pgsql_version = version.stdout().strip()
        postgresql = declare_dependency(
            compile_args: pgsql_compile_args,
            include_directories: pgsql_includedir_args,
            link_args: pgsql_link_args,
            version: pgsql_version,
        )
    endif
endif
