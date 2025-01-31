if not mysql.found()
    subdir_done()
endif

kea_mysql_lib = library(
    'kea-mysql',
    'mysql_binding.cc',
    'mysql_binding.h',
    'mysql_connection.cc',
    'mysql_connection.h',
    'mysql_constants.h',
    cpp_args: [f'-DKEA_ADMIN="@KEA_ADMIN@"'],
    dependencies: [mysql],
    include_directories: [include_directories('.')] + INCLUDES,
    install: true,
    install_dir: 'lib',
    link_with: LIBS_BUILT_SO_FAR,
)
LIBS_BUILT_SO_FAR = [kea_mysql_lib] + LIBS_BUILT_SO_FAR
subdir('testutils')
subdir('tests')
