project('kea', 'cpp', version: '2.7.6-git', default_options : ['default_library=shared'])

cpp = meson.get_compiler('cpp')

fs = import('fs')

conf_data = configuration_data({
  # 'CHRONO_SAME_DURATION': true,
  # 'CONFIG_H_WAS_INCLUDED': true,
  # 'ENABLE_DEBUG': false,
  # 'ENABLE_LOGGER_CHECKS': false,
  'EXTENDED_VERSION': '"@0@"'.format(meson.project_version()),
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
  'HAVE_GENERIC_TLS_METHOD': true,
  # 'HAVE_GSSAPI_GSSAPI_H': false,
  # 'HAVE_GSSAPI_GSSAPI_KRB': false,
  # 'HAVE_GSS_STR_TO_OID': false,
  # 'HAVE_INTTYPES_H': false,
  # 'HAVE_IS_BASE_OF': false,
  # 'HAVE_KRB': false,
  # 'HAVE_LOG': false,
  # 'HAVE_MYSQL': false,
  # 'HAVE_MYSQL_GET_OPTION': false,
  # 'HAVE_MYSQL_MY_BOOL': false,
  # 'HAVE_MYSQL_OPT_RECONNECT': false,
  # 'HAVE_NETCONF': false,
  # 'HAVE_OPTRESET': false,
  # 'HAVE_PGSQL': false,
  # 'HAVE_PGSQL_SSL': false,
  # 'HAVE_PGSQL_TCP_USER_TIMEOUT': false,
  # 'HAVE_PSELECT': false,
  # 'HAVE_SA_LEN': false,
  # 'HAVE_STDBOOL_H': false,
  # 'HAVE_STDINT_H': false,
  # 'HAVE_STDIO_H': false,
  # 'HAVE_STDLIB_H': false,
  # 'HAVE_STREAM_TRUNCATED_ERROR': false,
  # 'HAVE_STRINGS_H': false,
  # 'HAVE_STRING_H': false,
  # 'HAVE_SYS_DEVPOLL_H': false,
  # 'HAVE_SYS_FILIO_H': false,
  # 'HAVE_SYS_STAT_H': false,
  # 'HAVE_SYS_TYPES_H': false,
  # 'HAVE_TLS_': false,
  # 'HAVE_UNISTD_H': false,
  # 'HAVE_UTILS_ERRCODES_H': false,
  # 'HAVE_VALGRIND_HEADERS': false,
  # 'HAVE_VALGRIND_VALGRIND_H': false,
  # 'HAVE__BOOL': false,
  # 'LIBC_MUSL': false,
  # 'LOG': false,
  # 'LT_OBJDIR': false,
  # 'OS_BSD': false,
  # 'OS_FREEBSD': false,
  # 'OS_LINUX': false,
  # 'OS_NETBSD': false,
  # 'OS_OPENBSD': false,
  # 'OS_OSX': false,
  # 'OS_SOLARIS': false,
  # 'PACKAGE': 'kea',
  # 'PACKAGE_BUGREPORT': 'kea-dev@lists.isc.org',
  # 'PACKAGE_NAME': 'kea',
  # 'PACKAGE_STRING': 'kea @0@'.format(meson.project_version()),
  # 'PACKAGE_TARNAME': 'kea',
  # 'PACKAGE_URL': '',
  # 'PACKAGE_VERSION': meson.project_version(),
  'PACKAGE_VERSION_TYPE': '"tarball"',
  # 'PREMIUM': false,
  'PREMIUM_EXTENDED_VERSION': '"@0@"'.format(meson.project_version()),
  # 'STDC_HEADERS': false,
  # 'TOP_BUILDDIR': false,
  # 'USE_STATIC_LINK': false,
  'VERSION': '"@0@"'.format(meson.project_version()),
  # 'WITH_BOTAN': false,
  # 'WITH_HEIMDAL': false,
  # 'WITH_OPENSSL': false,
  # 'YYTEXT_POINTER': false,
  # 'SIZE_T': 'size_t',
  # 'SSIZE_T': 'ssize_t',
})

boost = dependency('boost', version: '>=1.66')
botan = dependency('botan', required: false)
gtest = dependency('gtest', required: false)
log4cplus = dependency('log4cplus')
krb5 = dependency('krb5', required: false)
mysql = dependency('mariadb', required: false)
if not mysql.found()
  mysql = dependency('mysql', required: false)
endif
if not mysql.found()
  mysql_config = find_program('mariadb_config', required: false)
  if mysql_config.found()
    mysql = declare_dependency(compile_args: run_command([mysql_config, '--cflags']).stdout().split(),
                               link_args: run_command([mysql_config, '--libs']).stdout().split())
  endif
endif
if not mysql.found()
  mysql_config = find_program('mysql_config')
  if mysql_config.found()
    mysql = declare_dependency(compile_args: run_command([mysql_config, '--cflags']).stdout().split(),
                               link_args: run_command([mysql_config, '--libs']).stdout().split())
  endif
endif
postgresql = dependency('libpq', required: false)
openssl = dependency('openssl', required: false)

netconf_deps = {}
netconf_deps_array = []
netconf_deps_found = true
foreach dep : ['yang', 'yang-cpp', 'sysrepo', 'sysrepo-cpp']
  netconf_deps = netconf_deps + {dep: cpp.find_library(dep, dirs: [f'/opt/@dep@/lib'], required: false)}
  if netconf_deps[dep].found()
    netconf_deps = netconf_deps + {dep: declare_dependency(
      dependencies: netconf_deps[dep],
      include_directories: include_directories(f'/opt/@dep@/include'),
    )}
    netconf_deps_array += netconf_deps[dep]
  else
    netconf_deps_found = false
    break
  endif
endforeach
if netconf_deps_found
  add_project_arguments('-std=c++20', language: 'cpp')
endif

if openssl.found()
  crypto = openssl
  conf_data.set('WITH_OPENSSL', true)
  message('Using OpenSSL.')
elif botan.found()
  crypto = botan
  conf_data.set('WITH_BOTAN', true)
  message('Using Botan.')
else
  error('Build failed: Could not find neither botan nor openssl libraries.')
endif

result = cpp.run(fs.read('compiler-checks/stream-truncated-error.cc'), name: 'HAVE_STREAM_TRUNCATED_ERROR', dependencies: [crypto])
if result.compiled() and result.returncode() == 0
  conf_data.set('HAVE_STREAM_TRUNCATED_ERROR', true)
endif

if mysql.found()
  result = cpp.run(fs.read('compiler-checks/mysql-my-bool.cc'), name: 'HAVE_MYSQL_MY_BOOL', dependencies: [mysql])
  if result.compiled() and result.returncode() == 0
    conf_data.set('HAVE_MYSQL_MY_BOOL', true)
  endif
endif

system = build_machine.system()
if system == 'linux'
  conf_data.set('OS_LINUX', true)
elif system == 'freebsd'
  conf_data.set('OS_BSD', true)
  conf_data.set('OS_FREEBSD', true)
  conf_data.set('HAVE_SA_LEN', true)
elif system == 'netbsd'
  conf_data.set('OS_BSD', true)
  conf_data.set('OS_NETBSD', true)
  conf_data.set('HAVE_SA_LEN', true)
elif system == 'openbsd'
  conf_data.set('OS_BSD', true)
  conf_data.set('OS_OPENBSD', true)
  conf_data.set('HAVE_SA_LEN', true)
elif system == 'sun'
  conf_data.set('OS_SOLARIS', true)
elif system == 'darwin'
  conf_data.set('OS_BSD', true)
  conf_data.set('OS_OSX', true)
  conf_data.set('HAVE_SA_LEN', true)
else
  error(f'Build failed: Unsupported system "@system@".')
endif
message(f'Detected system "@system@".')

prefix = get_option('prefix')
if system == 'darwin'
  add_project_arguments('-D__APPLE_USE_RFC_3542', language: 'cpp')
  add_project_link_arguments(f'-Wl,-rpath,@prefix@/lib', language: 'cpp')
else
  conf_data.set('CHRONO_SAME_DURATION', true)
  add_project_link_arguments(f'-Wl,-rpath=@prefix@/lib', language: 'cpp')
endif

have_premium = false
if fs.is_dir('premium')
  have_premium = true
  conf_data.set('PREMIUM', true)
endif

configure_file(input : 'config.h.in',
               output : 'config.h',
               configuration : conf_data)

configure_file(input : 'kea_version.h.in',
               output : 'kea_version.h',
               configuration : conf_data)

includes = [
  include_directories('.'),
  include_directories('src/bin'),
  include_directories('src/lib'),
]

kea_admin = '@0@/src/bin/admin/kea-admin'.format(meson.current_build_dir())
kea_lfc = '@0@/src/bin/lfc/kea-lfc'.format(meson.current_build_dir())

libs_built_so_far = []
subdir('src')
if have_premium
  subdir('premium')
endif
