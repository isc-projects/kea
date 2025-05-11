if not MYSQL_DEP.found()
    subdir_done()
endif

kea_mysql_lib = shared_library(
    'kea-mysql',
    'mysql_binding.cc',
    'mysql_connection.cc',
    cpp_args: [f'-DKEA_ADMIN="@KEA_ADMIN_INSTALLED@"'],
    dependencies: [MYSQL_DEP],
    include_directories: [include_directories('.')] + INCLUDES,
    install: true,
    install_dir: LIBDIR,
    install_rpath: INSTALL_RPATH,
    build_rpath: BUILD_RPATH,
    link_with: LIBS_BUILT_SO_FAR,
    version: '86.0.0',
)
LIBS_BUILT_SO_FAR = [kea_mysql_lib] + LIBS_BUILT_SO_FAR
subdir('testutils')
subdir('tests')
kea_mysql_headers = [
    'mysql_binding.h',
    'mysql_connection.h',
    'mysql_constants.h',
]
install_headers(kea_mysql_headers, preserve_path: true, subdir: 'kea/mysql')
