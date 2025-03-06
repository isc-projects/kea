# Require meson >= 0.64.0 for preserve_path arg in install_data.
# Require meson >= 1.1.0 for meson.options file.
project('kea', 'cpp', version: '2.7.7-git', meson_version: '>=1.1.0')

cpp = meson.get_compiler('cpp')
PROJECT_VERSION = meson.project_version()

#### Imports

fs = import('fs')

#### Variables

TOP_BUILD_DIR = meson.current_build_dir()
TOP_SOURCE_DIR = meson.current_source_dir()
RUN_STATE_DIR = get_option('localstatedir')
PREFIX = get_option('prefix')
DATADIR = get_option('datadir')
SYSCONFDIR = get_option('sysconfdir')

DHCP_DATA_DIR = f'@PREFIX@/@RUN_STATE_DIR@/run/kea'
DEFAULT_HOOKS_PATH = f'@PREFIX@/lib/kea/hooks'
KEA_ADMIN = f'@TOP_BUILD_DIR@/src/bin/admin/kea-admin'
KEA_LFC = f'@TOP_BUILD_DIR@/src/bin/lfc/kea-lfc'
TEST_CA_DIR = f'@TOP_SOURCE_DIR@/src/lib/asiolink/testutils/ca'
DATABASE_SCRIPTS_DIR = f'@TOP_BUILD_DIR@/src/share/database/scripts'
LEGAL_LOG_DIR = f'@PREFIX@/@RUN_STATE_DIR@/lib/kea'

#### Configuration Data

conf_data = configuration_data(
    {
        # 'CONFIG_H_WAS_INCLUDED': true,
        # 'ENABLE_DEBUG': false,
        # 'ENABLE_LOGGER_CHECKS': false,
        'EXTENDED_VERSION': '"tarball"',
        # 'HAS_UNDEFINED_PTHREAD_BEHAVIOR': false,
        # 'HAVE_AFL': false,
        # 'HAVE_BOOST_ASIO_COROUTINE_HPP': false,
        # 'HAVE_BOOST_ASIO_HPP': false,
        # 'HAVE_BOOST_ASIO_IP_ADDRESS_HPP': false,
        # 'HAVE_BOOST_ASIO_SIGNAL_SET_HPP': false,
        # 'HAVE_BOOST_ASIO_SSL_HPP': false,
        # 'HAVE_BOOST_ATOMIC_HPP': false,
        # 'HAVE_BOOST_CIRCULAR_BUFFER_HPP': false,
        # 'HAVE_BOOST_DATE_TIME_POSIX_TIME_POSIX_TIME_TYPES_HPP': false,
        # 'HAVE_BOOST_FOREACH_HPP': false,
        # 'HAVE_BOOST_FUNCTIONAL_HASH_HPP': false,
        # 'HAVE_BOOST_INTEGER_COMMON_FACTOR_HPP': false,
        # 'HAVE_BOOST_INTERPROCESS_SYNC_INTERPROCESS_UPGRADABLE_MUTEX_HPP': false,
        # 'HAVE_BOOST_SHARED_PTR_HPP': false,
        # 'HAVE_BOOST_SYSTEM_ERROR_CODE_HPP': false,
        # 'HAVE_BOTAN_ASIO_STREAM_H': false,
        # 'HAVE_BOTAN_BUILD_H': false,
        # 'HAVE_BROKEN_GET_IPV': false,
        # 'HAVE_CREATE_UNIFIED_DIFF': false,
        # 'HAVE_DLFCN_H': false,
        # 'HAVE_EVP_MD_CTX_CREATE': false,
        # 'HAVE_EVP_MD_CTX_DESTROY': false,
        # 'HAVE_EVP_MD_CTX_FREE': false,
        # 'HAVE_EVP_MD_CTX_NEW': false,
        # 'HAVE_EVP_PKEY_NEW_MAC_KEY': false,
        # 'HAVE_EVP_PKEY_NEW_RAW_PRIVATE_KEY': false,
        # 'HAVE_GSSAPI_GSSAPI_H': false,
        # 'HAVE_GSSAPI_GSSAPI_KRB': false,
        # 'HAVE_GSS_STR_TO_OID': false,
        # 'HAVE_INTTYPES_H': false,
        # 'HAVE_IS_BASE_OF': false,
        # 'HAVE_KRB': false,
        # 'HAVE_LOG': false,
        # 'HAVE_MYSQL_GET_OPTION': false,
        # 'HAVE_MYSQL_OPT_RECONNECT': false,
        # 'HAVE_NETCONF': false,
        # 'HAVE_OPTRESET': false,
        # 'HAVE_PGSQL_SSL': false,
        # 'HAVE_PGSQL_TCP_USER_TIMEOUT': false,
        # 'HAVE_PSELECT': false,
        # 'HAVE_STDBOOL_H': false,
        # 'HAVE_STDINT_H': false,
        # 'HAVE_STDIO_H': false,
        # 'HAVE_STDLIB_H': false,
        # 'HAVE_STRINGS_H': false,
        # 'HAVE_STRING_H': false,
        # 'HAVE_SYS_DEVPOLL_H': false,
        # 'HAVE_SYS_FILIO_H': false,
        # 'HAVE_SYS_STAT_H': false,
        # 'HAVE_SYS_TYPES_H': false,
        # 'HAVE_TLS_': false,
        # 'HAVE_UNISTD_H': false,
        # 'HAVE_VALGRIND_HEADERS': false,
        # 'HAVE_VALGRIND_VALGRIND_H': false,
        # 'HAVE__BOOL': false,
        # 'LIBC_MUSL': false,
        # 'LOG': false,
        # 'LT_OBJDIR': false,
        # 'PACKAGE': 'kea',
        # 'PACKAGE_BUGREPORT': 'kea-dev@lists.isc.org',
        'PACKAGE_NAME': 'kea',
        # 'PACKAGE_STRING': f'kea "@PROJECT_VERSION@"',
        # 'PACKAGE_TARNAME': 'kea',
        # 'PACKAGE_URL': '',
        'PACKAGE_VERSION': PROJECT_VERSION,
        'PACKAGE_VERSION_TYPE': '"development"',
        # 'PREMIUM': false,
        # 'PREMIUM_EXTENDED_VERSION': '"no"',
        # 'STDC_HEADERS': false,
        # 'TOP_BUILDDIR': false,
        # 'USE_STATIC_LINK': false,
        'VERSION': f'"@PROJECT_VERSION@"',
        # 'WITH_HEIMDAL': false,
        # 'YYTEXT_POINTER': false,
        # 'SIZE_T': 'size_t',
        # 'SSIZE_T': 'ssize_t',
    },
)

#### System-specific Variables

SYSTEM = build_machine.system()
if SYSTEM == 'linux'
    conf_data.set('OS_LINUX', true)
    OS_TYPE = 'Linux'
elif SYSTEM == 'freebsd'
    conf_data.set('OS_BSD', true)
    conf_data.set('OS_FREEBSD', true)
    OS_TYPE = 'BSD'
elif SYSTEM == 'netbsd'
    conf_data.set('OS_BSD', true)
    conf_data.set('OS_NETBSD', true)
    OS_TYPE = 'BSD'
elif SYSTEM == 'openbsd'
    conf_data.set('OS_BSD', true)
    conf_data.set('OS_OPENBSD', true)
    OS_TYPE = 'BSD'
elif SYSTEM == 'sun'
    conf_data.set('OS_SOLARIS', true)
    OS_TYPE = 'Solaris'
elif SYSTEM == 'darwin'
    conf_data.set('OS_BSD', true)
    conf_data.set('OS_OSX', true)
    OS_TYPE = 'BSD'
else
    error(f'Unsupported system "@SYSTEM@".')
endif
message(f'Detected system "@SYSTEM@".')

#### Programs

# External programs used only in this file.
cppcheck = find_program('cppcheck', required: false)
cppcheck_htmlreport = find_program('cppcheck-htmlreport', required: false)
valgrind = find_program('valgrind', required: false)

AWK = find_program('gawk', 'awk', required: false)
BISON = find_program('bison', version: '>=3.3.0', required: false)
DOXYGEN = find_program('doxygen', required: false)
FLEX = find_program('flex', version: '>=2.6.4', required: false)
INSTALL = find_program('install', required: true)
PDFLATEX = find_program('pdflatex', required: false)
PIP_COMPILE = find_program('pip-compile', required: false)
PLANTUML = find_program('plantuml', required: false)
PYTHON = find_program('python3', 'python', required: false)
SPHINX = find_program('sphinx-build', 'sphinx-build-3', required: false)
XMLLINT = find_program('xmllint', required: false)

CD_AND_RUN = find_program(f'@TOP_SOURCE_DIR@/cd-and-run.sh')
KEA_MSG_COMPILER = disabler()

#### Dependencies

boost = dependency('boost', version: '>=1.66')
threads = dependency('threads')
add_project_dependencies(boost, threads, language: ['cpp'])

gtest = dependency('gtest', required: false)

# Logging
log4cplus = dependency('log4cplus', required: false)
# TODO: leave only dependecy() when support for Ubuntu 20.04 gets removed.
if not log4cplus.found()
    log4cplus = cpp.find_library('log4cplus')
endif

# Cryptography
crypto = disabler()
botan = disabler()
foreach dep : ['botan-2', 'botan']
    botan = dependency(dep, required: false)
    if botan.found()
        break
    endif
endforeach
openssl = dependency('openssl', required: false)

# Kerberos
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
if not krb5.found()
    krb5 = dependency('krb5', required: false)
endif

# MySQL
mysql = dependency('mariadb', required: false)
if not mysql.found()
    mysql = dependency('mysql', required: false)
endif
mysql_config = disabler()
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

# PostgreSQL
postgresql = dependency('libpq', required: false)
pg_config = disabler()
if not postgresql.found()
    pg_config = find_program('pg_config', required: false)
endif
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

# NETCONF
netconf_deps = {}
NETCONF_DEPS_ARRAY = []
NETCONF_DEPS_FOUND = true
foreach dep : ['yang', 'yang-cpp', 'sysrepo', 'sysrepo-cpp']
    netconf_deps = netconf_deps + {dep: dependency(dep, required: false)}
    if netconf_deps[dep].found()
        continue
    endif

    # Try adding lib to it. libyang and libyang-cpp define the wrong pkg-config.
    netconf_deps = netconf_deps + {
        dep: dependency('lib' + dep, required: false),
    }
    if netconf_deps[dep].found()
        continue
    endif

    # Search in /opt.
    foreach prefix : ['', 'lib']
        path = f'/opt/@prefix@@dep@'
        lib = cpp.find_library(dep, dirs: [f'/@path@/lib'], required: false)
        if lib.found()
            netconf_deps = netconf_deps + {
                dep: declare_dependency(
                    dependencies: [lib],
                    include_directories: include_directories(f'/@path@/include'),
                    variables: {'prefix': f'@path@'},
                ),
            }
            if SYSTEM == 'darwin'
                add_project_link_arguments(
                    f'-Wl,-rpath,@path@/lib',
                    language: 'cpp',
                )
            else
                add_project_link_arguments(
                    f'-Wl,-rpath=@path@/lib',
                    language: 'cpp',
                )
            endif
        endif
    endforeach
endforeach
foreach dep : ['yang', 'yang-cpp', 'sysrepo', 'sysrepo-cpp']
    if netconf_deps[dep].found()
        NETCONF_DEPS_ARRAY += netconf_deps[dep]
    else
        NETCONF_DEPS_FOUND = false
    endif
endforeach

#### Build Options

all_opt = get_option('all')
crypto_opt = get_option('crypto')
gtest_opt = get_option('gtest')
krb5_opt = get_option('krb5')
mysql_opt = get_option('mysql')
netconf_opt = get_option('netconf')
postgresql_opt = get_option('postgresql')

# docs_opt = get_option('docs')
# parser_opt = get_option('parser')

FUZZ_OPT = get_option('fuzz')
PERFDHCP_OPT = get_option('perfdhcp')
SHELL_OPT = get_option('shell')
if SHELL_OPT == 'enabled' and not PYTHON.found()
    error('kea-shell requires python. Python not found.')
endif

if crypto_opt == 'auto'
    if openssl.found()
        crypto = openssl
    elif botan.found()
        crypto = botan
    endif
elif crypto_opt == 'botan'
    if botan.found()
        crypto = botan
    endif
elif crypto_opt == 'openssl'
    if openssl.found()
        crypto = openssl
    endif
endif

if crypto.name() == botan.name()
    message('Checking Botan Boost support.')
    cpp.has_header('botan/asio_stream.h', dependencies: [botan], required: true)
    conf_data.set('WITH_BOTAN', true)
    message('Using Botan.')
elif crypto.name() == openssl.name()
    conf_data.set('WITH_OPENSSL', true)
    message('Using OpenSSL.')
else
    error('Dependency not found: neither Botan nor OpenSSL.')
endif

if all_opt.enabled()
    if gtest_opt == 'disabled'
        gtest = disabler()
    elif not gtest.found()
        error('Dependency not found: GTest.')
    endif
    if krb5_opt == 'disabled'
        krb5 = disabler()
    elif not krb5.found()
        error('Dependency not found: Kerberos 5 with GSSAPI.')
    endif
    if mysql_opt == 'disabled'
        mysql = disabler()
    elif not mysql.found()
        error('Dependency not found: MySQL.')
    endif
    if netconf_opt == 'disabled'
        NETCONF_DEPS_FOUND = false
    elif not NETCONF_DEPS_FOUND
        error('Dependency not found: NETCONF.')
    endif
    if postgresql_opt == 'disabled'
        postgresql = disabler()
    elif not postgresql.found()
        error('Dependency not found: PostgreSQL.')
    endif
    if FUZZ_OPT != 'disabled'
        FUZZ_OPT = 'enabled'
    endif
    if PERFDHCP_OPT != 'disabled'
        PERFDHCP_OPT = 'enabled'
    endif
    if SHELL_OPT != 'disabled'
        SHELL_OPT = 'enabled'
    endif
elif all_opt.disabled()
    if gtest_opt != 'enabled'
        gtest = disabler()
    endif
    if krb5_opt != 'enabled'
        krb5 = disabler()
    endif
    if mysql_opt != 'enabled'
        mysql = disabler()
    endif
    if netconf_opt != 'enabled'
        NETCONF_DEPS_FOUND = false
    endif
    if postgresql_opt != 'enabled'
        postgresql = disabler()
    endif
    if FUZZ_OPT != 'enabled'
        FUZZ_OPT = 'disabled'
    endif
    if PERFDHCP_OPT != 'enabled'
        PERFDHCP_OPT = 'disabled'
    endif
    if SHELL_OPT != 'enabled'
        SHELL_OPT = 'disabled'
    endif
elif all_opt.auto()
    if gtest_opt == 'enabled' and not gtest.found()
        error('Dependency not found: GTest.')
    endif

    if krb5_opt == 'enabled' and not krb5.found()
        error('Dependency not found: Kerberos 5 with GSSAPI.')
    endif

    if mysql_opt == 'enabled' and not mysql.found()
        error('Dependency not found: MySQL.')
    endif

    if netconf_opt == 'enabled' and not NETCONF_DEPS_FOUND
        error('Dependency not found: NETCONF.')
    endif

    if postgresql_opt == 'enabled' and not postgresql.found()
        error('Dependency not found: PostgreSQL.')
    endif
else
    error('Unknown value for -Dall')
endif

if FUZZ_OPT == 'enabled'
    if not gtest.found()
        error('Fuzzing requires gtest. Gtest not found.')
    endif
    conf_data.set('FUZZING', true)
endif

if mysql.found()
    conf_data.set('HAVE_MYSQL', true)
endif

if postgresql.found()
    conf_data.set('HAVE_PGSQL', true)
endif

#### Compiler Checks

result = cpp.run(
    fs.read('compiler-checks/chrono-same-duration.cc'),
    name: 'CHRONO_SAME_DURATION',
    dependencies: [boost],
)
conf_data.set('CHRONO_SAME_DURATION', result.returncode() == 0)

ENVIRON_SHLIB_FLAGS = []
# --no-undefined is not supported by all loaders.
if cpp.has_link_argument('-Wl,--no-undefined')
    result = cpp.links(
        fs.read('compiler-checks/environ-in-shlib.cc'),
        name: 'ENVIRON_SHLIB_FLAGS',
        args: ['--shared', '-fPIC', '-Wl,--no-undefined'],
    )
    if not result
        ENVIRON_SHLIB_FLAGS += ['b_lundef=false']
    endif
endif

result = cpp.run(
    fs.read('compiler-checks/have-generic-tls-method.cc'),
    name: 'HAVE_GENERIC_TLS_METHOD',
    dependencies: [crypto],
)
conf_data.set('HAVE_GENERIC_TLS_METHOD', result.returncode() == 0)

result = cpp.run(
    fs.read('compiler-checks/have-optreset.cc'),
    name: 'HAVE_OPTRESET',
)
conf_data.set('HAVE_OPTRESET', result.returncode() == 0)

result = cpp.run(fs.read('compiler-checks/have-sa-len.cc'), name: 'HAVE_SA_LEN')
conf_data.set('HAVE_SA_LEN', result.returncode() == 0)

result = cpp.run(
    fs.read('compiler-checks/log4cplus-initializer.cc'),
    name: 'LOG4CPLUS_INITIALIZER_H',
    dependencies: [log4cplus],
)
conf_data.set('LOG4CPLUS_INITIALIZER_H', result.returncode() == 0)

if mysql.found()
    result = cpp.run(
        fs.read('compiler-checks/mysql-my-bool.cc'),
        name: 'HAVE_MYSQL_MY_BOOL',
        dependencies: [mysql],
    )
    conf_data.set('HAVE_MYSQL_MY_BOOL', result.returncode() == 0)
endif

result = cpp.run(
    fs.read('compiler-checks/stream-truncated-error.cc'),
    name: 'HAVE_STREAM_TRUNCATED_ERROR',
    dependencies: [crypto],
)
conf_data.set('HAVE_STREAM_TRUNCATED_ERROR', result.returncode() == 0)

#### System-specific Compiler Flags

compile_args = []
link_args = []

# $ORIGIN documented at https://www.man7.org/linux/man-pages/man8/ld.so.8.html
rpath = '$ORIGIN/../lib'
if SYSTEM == 'darwin'
    compile_args += ['-D__APPLE_USE_RFC_3542']
    add_project_arguments('-D__APPLE_USE_RFC_3542', language: 'cpp')
    link_arg = f'-Wl,-rpath,@rpath@'
    link_args += [link_arg]
    add_project_link_arguments(link_arg, language: 'cpp')
else
    link_arg = f'-Wl,-rpath=@rpath@'
    link_args += [link_arg]
    add_project_link_arguments(link_arg, language: 'cpp')
endif

have_premium = fs.is_dir('premium')
if have_premium
    conf_data.set('PREMIUM', 'yes')
    conf_data.set('PREMIUM_EXTENDED_VERSION', f'"@PROJECT_VERSION@"')
else
    conf_data.set('PREMIUM', 'no')
    conf_data.set('PREMIUM_EXTENDED_VERSION', '"no"')
endif
have_contrib = fs.is_dir('contrib')

#### Default Includes

INCLUDES = [
    include_directories('.'),
    include_directories('src'),
    include_directories('src/bin'),
    include_directories('src/lib'),
]

#### Build report

report_conf_data = configuration_data()
report_conf_data.merge_from(conf_data)
report_conf_data.set('TOP_BUILD_DIR', TOP_BUILD_DIR)
report_conf_data.set('PACKAGE_NAME', 'kea')
report_conf_data.set('PACKAGE_VERSION', PROJECT_VERSION)
report_conf_data.set('EXTENDED_VERSION', PROJECT_VERSION + ' (tarball)')
report_conf_data.set('PACKAGE_VERSION_TYPE', 'development')
report_conf_data.set('OS_TYPE', OS_TYPE)
report_conf_data.set('PREFIX', PREFIX)
report_conf_data.set('HOOKS_DIR', DEFAULT_HOOKS_PATH)
if have_premium
    report_conf_data.set('PREMIUM', 'yes')
else
    report_conf_data.set('PREMIUM', 'no')
endif
report_conf_data.set('BUILD_OPTIONS', meson.build_options())
report_conf_data.set('MESON_VERSION', meson.version())
report_conf_data.set('CXX', ' '.join(cpp.cmd_array()))
report_conf_data.set('CXX_ID', cpp.get_id())
result = run_command(cpp, '--version', check: false)
if result.returncode() == 0
    v = result.stdout().strip().split('\n')
    report_conf_data.set('CXX_VERSION', v.get(0, 'unknown'))
else
    report_conf_data.set('CXX_VERSION', 'unknown')
endif
result = cpp.run(
    fs.read('compiler-checks/get-cpp-standard.cc'),
    name: 'Get cpp standard',
)
if result.returncode() == 0
    report_conf_data.set('CXX_STANDARD', result.stdout().strip())
else
    report_conf_data.set('CXX_STANDARD', 'unknown')
endif
report_conf_data.set('CXX_ARGS', ' '.join(compile_args))
report_conf_data.set('LD_ID', cpp.get_linker_id())
report_conf_data.set('LD_ARGS', ' '.join(link_args))
if PYTHON.found()
    report_conf_data.set('HAVE_PYTHON', 'yes')
    report_conf_data.set('PYTHON_PATH', PYTHON.full_path())
    result = run_command(
        PYTHON,
        '-c',
        'import sysconfig; print(sysconfig.get_paths()[\'purelib\'])',
        check: false,
    )
    if result.returncode() == 0
        report_conf_data.set('PKGPYTHONDIR', result.stdout().strip() + '/kea')
    else
        report_conf_data.set('PKGPYTHONDIR', 'unknown')
    endif
else
    report_conf_data.set('HAVE_PYTHON', 'no')
endif
result = cpp.run(
    fs.read('compiler-checks/get-boost-version.cc'),
    name: 'Get Boost version',
    dependencies: [boost],
)
if result.returncode() == 0
    report_conf_data.set('BOOST_VERSION', result.stdout().strip())
else
    report_conf_data.set('BOOST_VERSION', 'unknown')
endif
report_conf_data.set(
    'BOOST_INCLUDE',
    boost.get_variable('includedir', default_value: 'unknown'),
)
report_conf_data.set(
    'BOOST_LIBDIR',
    boost.get_variable('libdir', default_value: 'unknown'),
)
report_conf_data.set(
    'CRYPTO_INCLUDE',
    crypto.get_variable('includedir', default_value: 'unknown'),
)
report_conf_data.set(
    'CRYPTO_LIBDIR',
    crypto.get_variable('libdir', default_value: 'unknown'),
)
if crypto.name() == botan.name()
    report_conf_data.set('CRYPTO_NAME', 'Botan')
    result = cpp.run(
        fs.read('compiler-checks/get-botan-version.cc'),
        name: 'Get Botan version',
        dependencies: [crypto],
    )
    if result.returncode() == 0
        report_conf_data.set('CRYPTO_VERSION', result.stdout().strip())
    else
        report_conf_data.set('CRYPTO_VERSION', botan.version())
    endif
elif crypto.name() == openssl.name()
    report_conf_data.set('CRYPTO_NAME', 'OpenSSL')
    result = cpp.run(
        fs.read('compiler-checks/get-openssl-version.cc'),
        name: 'Get OpenSSL version',
        dependencies: [crypto],
    )
    if result.returncode() == 0
        report_conf_data.set('CRYPTO_VERSION', result.stdout().strip())
    else
        report_conf_data.set('CRYPTO_VERSION', openssl.version())
    endif
endif
# TODO: remove if-condition when support for Ubuntu 20.04 gets removed.
if log4cplus.type_name() == 'pkgconfig'
    report_conf_data.set(
        'LOG4CPLUS_INCLUDE',
        log4cplus.get_variable('includedir', default_value: 'unknown'),
    )
    report_conf_data.set(
        'LOG4CPLUS_LIBDIR',
        log4cplus.get_variable('libdir', default_value: 'unknown'),
    )
endif
result = cpp.run(
    fs.read('compiler-checks/get-log4cplus-version.cc'),
    name: 'Get Log4cplus version',
    dependencies: [log4cplus],
)
if result.returncode() == 0
    report_conf_data.set('LOG4CPLUS_VERSION', result.stdout().strip())
else
    report_conf_data.set('LOG4CPLUS_VERSION', log4cplus.version())
endif
if FLEX.found()
    report_conf_data.set('FLEX', FLEX.full_path())
else
    report_conf_data.set('FLEX', 'unknown')
endif
if BISON.found()
    report_conf_data.set('BISON', BISON.full_path())
else
    report_conf_data.set('BISON', 'unknown')
endif
if mysql.found()
    if not mysql_config.found()
        report_conf_data.set('MYSQL_VERSION', mysql.version())
        report_conf_data.set(
            'MYSQL_INCLUDE',
            mysql.get_variable('includedir', default_value: 'unknown'),
        )
        report_conf_data.set(
            'MYSQL_LIBDIR',
            mysql.get_variable('libdir', default_value: 'unknown'),
        )
    else
        report_conf_data.set('MYSQL_VERSION', mysql_version)
        report_conf_data.set('MYSQL_INCLUDE', ' '.join(mysql_compile_args))
        report_conf_data.set('MYSQL_LIBDIR', ' '.join(mysql_link_args))
    endif
else
    report_conf_data.set('HAVE_MYSQL', 'no')
    report_conf_data.set('MYSQL_VERSION', 'unknown')
    report_conf_data.set('MYSQL_INCLUDE', 'unknown')
    report_conf_data.set('MYSQL_LIBDIR', 'unknown')
endif
if postgresql.found()
    report_conf_data.set('HAVE_PGSQL', 'yes')
    if not pg_config.found()
        report_conf_data.set('PGSQL_VERSION', postgresql.version())
        report_conf_data.set(
            'PGSQL_INCLUDE',
            postgresql.get_variable('includedir', default_value: 'unknown'),
        )
        report_conf_data.set(
            'PGSQL_LIBDIR',
            postgresql.get_variable('libdir', default_value: 'unknown'),
        )
    else
        report_conf_data.set('PGSQL_VERSION', pgsql_version)
        report_conf_data.set('PGSQL_INCLUDE', ' '.join(pgsql_compile_args))
        report_conf_data.set('PGSQL_LIBDIR', ' '.join(pgsql_link_args))
    endif
else
    report_conf_data.set('HAVE_PGSQL', 'no')
    report_conf_data.set('PGSQL_VERSION', 'unknown')
    report_conf_data.set('PGSQL_INCLUDE', 'unknown')
    report_conf_data.set('PGSQL_LIBDIR', 'unknown')
endif
report_conf_data.set('HAVE_NETCONF', 'no')
if gtest.found()
    report_conf_data.set('HAVE_GTEST', 'yes')
    report_conf_data.set(
        'GTEST_INCLUDE',
        gtest.get_variable('includedir', default_value: 'unknown'),
    )
    report_conf_data.set(
        'GTEST_LIBDIR',
        gtest.get_variable('libdir', default_value: 'unknown'),
    )
    report_conf_data.set('GTEST_VERSION', gtest.version())
else
    report_conf_data.set('HAVE_GTEST', 'no')
    report_conf_data.set('GTEST_VERSION', 'unknown')
    report_conf_data.set('GTEST_INCLUDE', 'unknown')
    report_conf_data.set('GTEST_LIBDIR', 'unknown')
endif

#### Custom Targets

run_target(
    'add-changelog-entry',
    command: [f'@TOP_SOURCE_DIR@/changelog_unreleased/.add-entry.sh'],
)

if cppcheck.found()
    run_target(
        'cppcheck',
        command: [
            cppcheck,
            '-I.',
            '-I./src/lib',
            '-I./src/bin',
            '--inline-suppr',
            '--quiet',
            '--max-configs=256',
            f'--suppressions-list=@TOP_SOURCE_DIR@/src/cppcheck-suppress.lst',
            '--template={file}:{line}: check_fail: {message} ({severity},{id})',
            '--xml',
            '--xml-version=2',
            '.',
        ],
    )
endif

if cppcheck_htmlreport.found()
    run_target(
        'cppcheck-report',
        command: [
            cppcheck_htmlreport,
            '--file',
            './cppcheck-result.xml',
            '--report-dir',
            './report',
            '--title',
            '"cppcheck report"',
        ],
    )
endif

if valgrind.found()
    add_test_setup(
        'valgrind',
        exe_wrapper: [
            valgrind,
            '--child-silent-after-fork=yes',
            '--error-exitcode=0',
            '--fullpath-after=',
            '--leak-check=full',
            '--num-callers=64',
            '--quiet',
            '--show-leak-kinds=all',
            '--suppressions=src/valgrind.supp',
            '--xml=yes',
            '--xml-file=valgrind-results-%p.xml',
        ],
        exclude_suites: ['python-tests', 'shell-tests'],
    )
    add_test_setup(
        'valgrind_gen_suppressions',
        exe_wrapper: [
            valgrind,
            '--child-silent-after-fork=yes',
            '--error-exitcode=0',
            '--fullpath-after=',
            '--leak-check=full',
            '--num-callers=64',
            '--quiet',
            '--show-leak-kinds=all',
            '--suppressions=src/valgrind.supp',
            '--gen-suppressions=all',
            '--log-file=valgrind.supp',
        ],
        exclude_suites: ['python-tests', 'shell-tests'],
    )
endif

#### Configuration Files

config_report_sh = configure_file(
    input: 'config-report.sh.in',
    output: 'config-report.sh',
    configuration: report_conf_data,
)

CONFIG_REPORT = configure_file(
    output: 'config.report',
    input: config_report_sh,
    command: [f'@TOP_BUILD_DIR@/config-report.sh'],
)

# TODO: Change to config.h.in when autotools are removed.
configure_file(
    input: 'meson-config.h.in',
    output: 'config.h',
    configuration: conf_data,
    install: true,
    install_dir: 'include/kea',
)

# TODO: Change to kea_version.h.in when autotools are removed.
configure_file(
    input: 'meson-kea_version.h.in',
    output: 'kea_version.h',
    configuration: conf_data,
    install: true,
    install_dir: 'include/kea',
)

#### Build Starts Here

LIBS_BUILT_SO_FAR = []
TARGETS_GEN_MESSAGES = []
TARGETS_GEN_PARSER = []
subdir('tools')
subdir('src')
subdir('fuzz')
subdir('doc')
if have_premium
    subdir('premium')
endif
if have_contrib
    subdir('contrib')
endif

#### More Custom Targets

if TARGETS_GEN_MESSAGES.length() > 0
    alias_target('messages', TARGETS_GEN_MESSAGES)
else
    error(
        'No messages to generate. This is probably an error in the ' + 'meson.build files.',
    )
endif
if TARGETS_GEN_PARSER.length() > 0
    alias_target('parser', TARGETS_GEN_PARSER)
else
    run_target('parser', command: 'echo Parser generation is disabled.'.split())
endif

#### Installation

top_docs = [
    'AUTHORS',
    'CONTRIBUTING.md',
    'COPYING',
    'ChangeLog',
    'README',
    'SECURITY.md',
    'code_of_conduct.md',
    'platforms.rst',
]
install_data(top_docs, install_dir: 'share/doc/kea')
install_emptydir('var/run/kea')

# Print the setup report.
message(run_command(['cat', CONFIG_REPORT], check: true).stdout())

