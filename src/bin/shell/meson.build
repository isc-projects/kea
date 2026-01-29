kea_shell_conf_data = configuration_data()
kea_shell_conf_data.set('PYTHON', PYTHON.full_path())
kea_shell_conf_data.set('PACKAGE_VERSION', PROJECT_VERSION)
kea_shell_conf_data.set('EXTENDED_VERSION', EXTENDED_VERSION)
kea_shell_conf_data.set('PKGPYTHONDIR', PKGPYTHONDIR)

configure_file(
    input: 'kea-shell.in',
    output: 'kea-shell',
    configuration: kea_shell_conf_data,
    install: true,
    install_dir: SBINDIR,
)
configure_file(
    input: 'kea_conn.py',
    output: 'kea_conn.py',
    copy: true,
    install: true,
    install_dir: PKGPYTHONDIR,
)
configure_file(
    input: 'kea_connector3.py',
    output: 'kea_connector3.py',
    copy: true,
    install: true,
    install_dir: PKGPYTHONDIR,
)
subdir('tests')
