project(
    'kea',
    'cpp',
    version: '2.7.7-git',
    default_options: ['default_library=shared'],
)

cpp = meson.get_compiler('cpp')
project_version = meson.project_version()

#### Imports

fs = import('fs')

#### Variables

TOP_BUILD_DIR = meson.current_build_dir()
TOP_SOURCE_DIR = meson.current_source_dir()
KEA_ADMIN = f'@TOP_BUILD_DIR@/src/bin/admin/kea-admin'
KEA_LFC = f'@TOP_BUILD_DIR@/src/bin/lfc/kea-lfc'
TEST_CA_DIR = f'@TOP_SOURCE_DIR@/src/lib/asiolink/testutils/ca'

# TODO: Control it via a build option.
FUZZING_IN_CI = false

#### Configuration Data

conf_data = configuration_data(
    {
        # 'CONFIG_H_WAS_INCLUDED': true,
        # 'ENABLE_DEBUG': false,
        # 'ENABLE_LOGGER_CHECKS': false,
        'EXTENDED_VERSION': f'"@project_version@"',
        # 'FUZZING': false,
        # 'FUZZING_IN_CI': false,
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
        # 'PACKAGE_NAME': 'kea',
        # 'PACKAGE_STRING': f'kea "@project_version@"',
        # 'PACKAGE_TARNAME': 'kea',
        # 'PACKAGE_URL': '',
        # 'PACKAGE_VERSION': meson.project_version(),
        'PACKAGE_VERSION_TYPE': '"tarball"',
        # 'PREMIUM': false,
        'PREMIUM_EXTENDED_VERSION': f'"@project_version@"',
        # 'STDC_HEADERS': false,
        # 'TOP_BUILDDIR': false,
        # 'USE_STATIC_LINK': false,
        'VERSION': f'"@project_version@"',
        # 'WITH_HEIMDAL': false,
        # 'YYTEXT_POINTER': false,
        # 'SIZE_T': 'size_t',
        # 'SSIZE_T': 'ssize_t',
    },
)

#### Dependencies

boost = dependency('boost', version: '>=1.66')
gtest = dependency('gtest', required: false)
log4cplus = dependency('log4cplus')
threads = dependency('threads')

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
if openssl.found()
    crypto = openssl
    conf_data.set('WITH_OPENSSL', true)
    message('Using OpenSSL.')
elif botan.found()
    crypto = botan
    conf_data.set('WITH_BOTAN', true)
    message('Using Botan.')
    message('Checking Botan Boost support.')
    cpp.has_header('botan/asio_stream.h', dependencies: [botan], required: true)
endif
if not crypto.found()
    error('Build failed: Could not find neither botan nor openssl libraries.')
endif

# Kerberos
krb5 = dependency('krb5', required: false)
if not krb5.found()
    krb5_config = find_program('krb5-config', required: false)
    cflags = run_command([krb5_config, '--cflags'], check: false)
    libs = run_command([krb5_config, '--libs'], check: false)
    if cflags.returncode() == 0 and libs.returncode() == 0
        krb5 = declare_dependency(
            compile_args: cflags.stdout().split(),
            link_args: libs.stdout().split(),
        )
    endif
endif

# MySQL
mysql = dependency('mariadb', required: false)
if not mysql.found()
    mysql = dependency('mysql', required: false)
endif
foreach mysql_config : ['mariadb_config', 'mysql_config']
    if mysql.found()
        continue
    endif
    mysql_config = find_program(mysql_config, required: false)
    if not mysql_config.found()
        continue
    endif
    cflags = run_command([mysql_config, '--cflags'], check: false)
    libs = run_command([mysql_config, '--libs'], check: false)
    if cflags.returncode() == 0 and libs.returncode() == 0
        mysql = declare_dependency(
            compile_args: cflags.stdout().split(),
            link_args: libs.stdout().split(),
        )
        break
    endif
endforeach
if mysql.found()
    conf_data.set('HAVE_MYSQL', true)
endif

# PostgreSQL
postgresql = dependency('libpq', required: false)
if not postgresql.found()
    pg_config = find_program('pg_config', required: false)
    cflags = run_command([pg_config, '--cflags'], check: false)
    libs = run_command([pg_config, '--libs'], check: false)
    if cflags.returncode() == 0 and libs.returncode() == 0
        postgresql = declare_dependency(
            compile_args: cflags.stdout().split(),
            link_args: libs.stdout().split(),
        )
    endif
endif
if postgresql.found()
    conf_data.set('HAVE_PGSQL', true)
endif

# NETCONF
netconf_deps = {}
netconf_deps_array = []
netconf_deps_found = true
foreach dep : ['yang', 'yang-cpp', 'sysrepo', 'sysrepo-cpp']
    netconf_deps = netconf_deps + {dep: dependency(dep, required: false)}
    if not netconf_deps[dep].found()
        lib = cpp.find_library(dep, dirs: [f'/opt/@dep@/lib'], required: false)
        if lib.found()
            netconf_deps = netconf_deps + {
                dep: declare_dependency(
                    dependencies: [lib],
                    include_directories: include_directories(
                        f'/opt/@dep@/include',
                    ),
                ),
            }
        endif
    endif
    if netconf_deps[dep].found()
        netconf_deps_array += netconf_deps[dep]
    else
        netconf_deps_found = false
    endif
endforeach

#### Compiler Checks

result = cpp.run(
    fs.read('compiler-checks/chrono-same-duration.cc'),
    name: 'CHRONO_SAME_DURATION',
    dependencies: [boost],
)
conf_data.set('CHRONO_SAME_DURATION', result.returncode() == 0)

result = cpp.run(
    fs.read('compiler-checks/have-generic-tls-method.cc'),
    name: 'HAVE_GENERIC_TLS_METHOD',
    dependencies: [crypto],
)
conf_data.set('HAVE_GENERIC_TLS_METHOD', result.returncode() == 0)

result = cpp.run(fs.read('compiler-checks/have-sa-len.cc'), name: 'HAVE_SA_LEN')
conf_data.set('HAVE_SA_LEN', result.returncode() == 0)

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

#### System-specific Variables

SYSTEM = build_machine.system()
if SYSTEM == 'linux'
    conf_data.set('OS_LINUX', true)
elif SYSTEM == 'freebsd'
    conf_data.set('OS_BSD', true)
    conf_data.set('OS_FREEBSD', true)
elif SYSTEM == 'netbsd'
    conf_data.set('OS_BSD', true)
    conf_data.set('OS_NETBSD', true)
elif SYSTEM == 'openbsd'
    conf_data.set('OS_BSD', true)
    conf_data.set('OS_OPENBSD', true)
elif SYSTEM == 'sun'
    conf_data.set('OS_SOLARIS', true)
elif SYSTEM == 'darwin'
    conf_data.set('OS_BSD', true)
    conf_data.set('OS_OSX', true)
else
    error(f'Build failed: Unsupported system "@SYSTEM@".')
endif
message(f'Detected system "@SYSTEM@".')

#### System-specific Compiler Flags

PREFIX = get_option('prefix')
if SYSTEM == 'darwin'
    add_project_arguments('-D__APPLE_USE_RFC_3542', language: 'cpp')
    add_project_link_arguments(f'-Wl,-rpath,@PREFIX@/lib', language: 'cpp')
else
    add_project_link_arguments(f'-Wl,-rpath=@PREFIX@/lib', language: 'cpp')
endif

have_premium = fs.is_dir('premium')
if have_premium
    conf_data.set('PREMIUM', true)
endif

#### Configuration Files

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

#### Default Includes

INCLUDES = [
    include_directories('.'),
    include_directories('src/bin'),
    include_directories('src/lib'),
]

#### Build Starts Here

LIBS_BUILT_SO_FAR = []
subdir('src')
subdir('fuzz')
if have_premium
    subdir('premium')
endif
