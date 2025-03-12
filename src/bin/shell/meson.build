kea_shell_conf_data = configuration_data()
kea_shell_conf_data.set('PYTHON', PYTHON.full_path())
kea_shell_conf_data.set('PACKAGE_VERSION', PROJECT_VERSION)
kea_shell_conf_data.set('EXTENDED_VERSION', PROJECT_VERSION + ' (tarball)')

python = import('python')
py_installation = python.find_installation('python3', required: true)
python_install_dir = py_installation.get_install_dir(pure: true)
pkgpythondir = python_install_dir / 'kea'
kea_shell_conf_data.set('PKGPYTHONDIR', pkgpythondir)

configure_file(
    input: 'kea-shell.in',
    output: 'kea-shell',
    configuration: kea_shell_conf_data,
    install: true,
    install_dir: get_option('sbindir'),
)
configure_file(
    input: 'kea_conn.py',
    output: 'kea_conn.py',
    copy: true,
    install: true,
    install_dir: pkgpythondir,
)
configure_file(
    input: 'kea_connector3.py',
    output: 'kea_connector3.py',
    copy: true,
    install: true,
    install_dir: pkgpythondir,
)
subdir('tests')
