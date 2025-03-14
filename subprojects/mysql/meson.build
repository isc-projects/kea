project('mysql')
mysql = dependency('mysql', required: false)
foreach mysql_config_file : ['mariadb_config', 'mysql_config']
    if mysql.found()
        continue
    endif
    mysql_config = find_program(mysql_config_file, required: false)
    if not mysql_config.found()
        continue
    endif
    cflags = run_command([mysql_config, '--cflags'], check: false)
    libs = run_command([mysql_config, '--libs'], check: false)
    version = run_command([mysql_config, '--version'], check: false)

    if cflags.returncode() == 0 and libs.returncode() == 0 and version.returncode() == 0
        mysql_compile_args = cflags.stdout().split()
        mysql_link_args = libs.stdout().split()
        mysql_version = version.stdout().strip()
        mysql = declare_dependency(
            compile_args: mysql_compile_args,
            link_args: mysql_link_args,
            version: mysql_version,
        )
        break
    endif
endforeach

