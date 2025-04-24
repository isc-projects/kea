project('postgresql')
postgresql = disabler()

cpp = meson.get_compiler('cpp')
libpq = cpp.find_library('pq', required: false)

pg_config = find_program('pg_config', required: false)
if pg_config.found()
    cppflags = run_command([pg_config, '--cppflags'], check: false)
    includedir = run_command([pg_config, '--includedir'], check: false)
    ldflags = run_command([pg_config, '--ldflags'], check: false)
    libdir = run_command([pg_config, '--libdir'], check: false)
    libs = run_command([pg_config, '--libs'], check: false)
    version = run_command([pg_config, '--version'], check: false)
    if cppflags.returncode() == 0 and includedir.returncode() == 0 and libdir.returncode() == 0 and ldflags.returncode() == 0 and libs.returncode() == 0 and version.returncode() == 0
        pgsql_compile_args = cppflags.stdout().split()
        pgsql_includedir_args = includedir.stdout().split()
        pgsql_ldflags = ldflags.stdout().split()
        pgsql_libdir = libdir.stdout().strip()
        pgsql_link_args = libs.stdout().split()
        pgsql_version = version.stdout().strip()

        link_args = [f'-L@pgsql_libdir@'] + pgsql_ldflags + pgsql_link_args
        if libpq.found()
            link_args += ['-lpq']
        endif

        postgresql = declare_dependency(
            compile_args: pgsql_compile_args,
            include_directories: pgsql_includedir_args,
            link_args: link_args,
            version: pgsql_version,
        )
    endif
endif

# Last resort
if not postgresql.found()
    postgresql = libpq
endif
