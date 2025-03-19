# Copyright (C) 2025 Internet Systems Consortium, Inc. ("ISC")
#
# SPDX-License-Identifier: MPL-2.0
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0.  If a copy of the MPL was not distributed with this
# file, you can obtain one at https://mozilla.org/MPL/2.0/.
#
# See the COPYING file distributed with this work for additional
# information regarding copyright ownership.

# Require meson >= 0.64.0 for preserve_path arg in install_data.
# Require meson >= 1.1.0 for meson.options file.
# bug_report is not yet supported by meson,its value will be
# 'kea-dev@lists.isc.org'

project(
    'kea',
    'cpp',
    version: '2.7.7-git',
    meson_version: '>=1.1.0',
    license: 'MPL-2.0',
    license_files: ['COPYING'],
    default_options: ['b_asneeded=true', 'b_pch=false', 'b_pie=true'],
)

cpp = meson.get_compiler('cpp')
PROJECT_VERSION = meson.project_version()

#### Imports

fs = import('fs')
python_module = import('python')

#### Variables

TOP_BUILD_DIR = meson.current_build_dir()
TOP_SOURCE_DIR = meson.current_source_dir()

BINDIR = get_option('bindir')
DATADIR = get_option('datadir')
INCLUDEDIR = get_option('includedir')
LIBDIR = get_option('libdir')
LOCALSTATEDIR = get_option('localstatedir')
MANDIR = get_option('mandir')
PREFIX = get_option('prefix')
SBINDIR = get_option('sbindir')
SYSCONFDIR = get_option('sysconfdir')

DATABASE_SCRIPTS_DIR = TOP_BUILD_DIR / 'src/share/database/scripts'
DEFAULT_HOOKS_PATH = PREFIX / LIBDIR / 'kea/hooks'
KEA_ADMIN_BUILT = TOP_BUILD_DIR / 'src/bin/lfc/kea-admin'
KEA_ADMIN_INSTALLED = PREFIX / SBINDIR / 'kea-admin'
KEA_LFC_BUILT = TOP_BUILD_DIR / 'src/bin/lfc/kea-lfc'
KEA_LFC_INSTALLED = PREFIX / SBINDIR / 'kea-lfc'
LEGAL_LOG_DIR = PREFIX / LOCALSTATEDIR / 'lib/kea'
RUNSTATEDIR = LOCALSTATEDIR / 'run/kea'
RUNSTATEDIR_INSTALLED = PREFIX / RUNSTATEDIR
TEST_CA_DIR = TOP_SOURCE_DIR / 'src/lib/asiolink/testutils/ca'

#### Build Options

crypto_opt = get_option('crypto')
krb5_opt = get_option('krb5')
mysql_opt = get_option('mysql')
netconf_opt = get_option('netconf')
postgresql_opt = get_option('postgresql')

FUZZ_OPT = get_option('fuzz')
TESTS_OPT = get_option('tests')

#### Programs

# External programs used only in this file.
cppcheck = find_program('cppcheck', required: false)
cppcheck_htmlreport = find_program('cppcheck-htmlreport', required: false)
git = find_program('git', required: false)
valgrind = find_program('valgrind', required: false)

AWK = find_program('gawk', 'awk', required: false)
BISON = find_program('bison', version: '>=3.3.0', required: false)
DOXYGEN = find_program('doxygen', required: false)
FLEX = find_program('flex', version: '>=2.6.4', required: false)
INSTALL = find_program('install', required: true)
PDFLATEX = find_program('pdflatex', required: false)
PIP_COMPILE = find_program('pip-compile', required: false)
PLANTUML = find_program('plantuml', required: false)
PYTHON = find_program('python3', 'python', required: true)
SPHINX = find_program('sphinx-build', 'sphinx-build-3', required: false)
XMLLINT = find_program('xmllint', required: false)

CD_AND_RUN = find_program(TOP_SOURCE_DIR / 'scripts/cd-and-run.sh')
ENV = find_program(TOP_SOURCE_DIR / 'scripts/env.sh')
GRABBER = find_program(TOP_SOURCE_DIR / 'scripts/grabber.py')
KEA_MSG_COMPILER = disabler()

#### Configuration Data

# 'HAVE_BOTAN_ASIO_STREAM_H': false,
# 'HAVE_PGSQL_SSL': false,
# 'USE_STATIC_LINK': false,
conf_data = configuration_data(
    {
        'PACKAGE': 'kea',
        'PACKAGE_NAME': 'kea',
        'PACKAGE_VERSION': PROJECT_VERSION,
        'VERSION': f'"@PROJECT_VERSION@"',
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

#### Dependencies

boost_dep = dependency('boost', version: '>=1.66', modules: ['system'])
dl_dep = dependency('dl')
threads_dep = dependency('threads')
add_project_dependencies(boost_dep, dl_dep, threads_dep, language: ['cpp'])

# check boost headers
boost_headers = [
    'boost/asio.hpp',
    'boost/asio/coroutine.hpp',
    'boost/asio/io_context.hpp',
    'boost/asio/ip/address.hpp',
    'boost/asio/signal_set.hpp',
    'boost/circular_buffer.hpp',
    'boost/date_time/posix_time/posix_time_types.hpp',
    'boost/foreach.hpp',
    'boost/functional/hash.hpp',
    'boost/integer/common_factor.hpp',
    'boost/interprocess/sync/interprocess_upgradable_mutex.hpp',
    'boost/shared_ptr.hpp',
    'boost/system/error_code.hpp',
]
foreach hdr : boost_headers
    cpp.has_header(hdr, dependencies: [boost_dep], required: true)
endforeach

# Logging
# TODO: remove fallback when support for Ubuntu 20.04 gets removed.
LOG4CPLUS_DEP = dependency('log4cplus', fallback: ['log4cplus', 'log4cplus'])

# Cryptography
CRYPTO_DEP = disabler()
botan = disabler()
foreach dep : ['botan-2', 'botan']
    botan = dependency(dep, required: false)
    if botan.found()
        break
    endif
endforeach
openssl = dependency('openssl', required: false)

# Kerberos
KRB5_DEP = dependency(
    'krb5-gssapi',
    fallback: ['krb5', 'krb5'],
    required: krb5_opt,
)
if KRB5_DEP.found()
    cpp.has_header('gssapi/gssapi.h', dependencies: [KRB5_DEP], required: true)
    cpp.has_header(
        'gssapi/gssapi_krb5.h',
        dependencies: [KRB5_DEP],
        required: true,
    )
endif

# MySQL
MYSQL_DEP = dependency(
    'mariadb',
    fallback: ['mysql', 'mysql'],
    required: mysql_opt,
)

# PostgreSQL
POSTGRESQL_DEP = dependency(
    'libpq',
    fallback: ['postgresql', 'postgresql'],
    required: postgresql_opt,
)

# NETCONF
NETCONF_DEP = dependency(
    'yang+yang-cpp+sysrepo+sysrepo-cpp',
    fallback: ['netconf', 'netconf'],
    required: netconf_opt,
)
if netconf_opt.enabled() and NETCONF_DEP.get_variable(
    'libyang_prefix',
    default_value: 'unknown',
) == 'unknown'
    error('Dependency not found: NETCONF.')
endif

GTEST_DEP = dependency(
    'gtest',
    required: TESTS_OPT.enabled() or FUZZ_OPT.enabled(),
)

# Crypto
if crypto_opt == 'botan'
    if botan.found()
        CRYPTO_DEP = botan
    endif
elif crypto_opt == 'openssl'
    if openssl.found()
        CRYPTO_DEP = openssl
    endif
endif

if CRYPTO_DEP.name() == botan.name()
    message('Checking Botan Boost support.')
    cpp.has_header('botan/asio_stream.h', dependencies: [botan], required: true)
    conf_data.set('WITH_BOTAN', true)
    message('Using Botan.')
elif CRYPTO_DEP.name() == openssl.name()
    conf_data.set('WITH_OPENSSL', true)
    cpp.has_header(
        'boost/asio/ssl.hpp',
        dependencies: [boost_dep],
        required: true,
    )
    message('Using OpenSSL.')
else
    error('Dependency not found: neither Botan nor OpenSSL.')
endif

# Kea shell
PKGPYTHONDIR = 'unknown'
py_installation = python_module.find_installation('python3', required: false)
if py_installation.found()
    PKGPYTHONDIR = py_installation.get_install_dir(pure: true) / 'kea'
else
    result = run_command(
        PYTHON,
        '-c',
        'import sysconfig; print(sysconfig.get_paths()[\'purelib\'])',
        check: false,
    )
    if result.returncode() == 0
        PKGPYTHONDIR = result.stdout().strip() / 'kea'
    endif
endif

if TESTS_OPT.enabled()
    conf_data.set('ENABLE_DEBUG', true)
    conf_data.set('ENABLE_LOGGER_CHECKS', true)
endif
conf_data.set('FUZZING', FUZZ_OPT.enabled())
conf_data.set('HAVE_MYSQL', MYSQL_DEP.found())
conf_data.set('HAVE_PGSQL', POSTGRESQL_DEP.found())

#### Compiler Checks

result = cpp.run(
    fs.read('compiler-checks/boost-has-threads.cc'),
    dependencies: [boost_dep, threads_dep],
    name: 'BOOST_HAS_THREADS',
)
if result.returncode() != 0
    error('boost is not configured to use threads')
endif

if cpp.has_header('boost/regex.h', dependencies: [boost_dep], required: false)
    result = cpp.run(
        fs.read('compiler-checks/boost-regex.cc'),
        dependencies: [boost_dep, threads_dep],
        name: 'GET_SYSTEM_VS_BOOST_REGEX_HEADER',
    )
    if result.returncode() != 0
        error('boost/regex.h is used in place of system regex.h')
    endif
endif

result = cpp.run(
    fs.read('compiler-checks/chrono-same-duration.cc'),
    name: 'CHRONO_SAME_DURATION',
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
    dependencies: [boost_dep, CRYPTO_DEP, threads_dep],
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
    dependencies: [LOG4CPLUS_DEP],
)
conf_data.set('LOG4CPLUS_INITIALIZER_H', result.returncode() == 0)

if MYSQL_DEP.found()
    result = cpp.run(
        fs.read('compiler-checks/mysql-my-bool.cc'),
        name: 'MYSQL_MY_BOOL',
        dependencies: [MYSQL_DEP],
    )
    conf_data.set('HAVE_MYSQL_MY_BOOL', result.returncode() == 0)

    result = cpp.run(
        fs.read('compiler-checks/mysql-get-option.cc'),
        name: 'HAVE_MYSQL_GET_OPTION',
        dependencies: [MYSQL_DEP],
    )
    conf_data.set('HAVE_MYSQL_GET_OPTION', result.returncode() == 0)
endif

result = cpp.run(
    fs.read('compiler-checks/stream-truncated-error.cc'),
    name: 'HAVE_STREAM_TRUNCATED_ERROR',
    dependencies: [boost_dep, CRYPTO_DEP, threads_dep],
)
conf_data.set('HAVE_STREAM_TRUNCATED_ERROR', result.returncode() == 0)

# TODO: implement when integrating with CI
result = cpp.run(
    fs.read('compiler-checks/fuzzing-with-clusterfuzzlite.cc'),
    name: 'FUZZING_WITH_CLUSTERFUZZLITE',
)
FUZZING_WITH_CLUSTERFUZZLITE = result.returncode() == 0

have_afl = false
result = cpp.run(fs.read('compiler-checks/have-afl.cc'), name: 'HAVE_AFL')
if result.returncode() == 0
    have_afl = true
endif
conf_data.set('HAVE_AFL', have_afl)

if GTEST_DEP.found()
    result = cpp.run(
        fs.read('compiler-checks/have-create-unified-diff.cc'),
        name: 'HAVE_CREATE_UNIFIED_DIFF',
        dependencies: [GTEST_DEP],
    )
    conf_data.set('HAVE_CREATE_UNIFIED_DIFF', result.returncode() == 0)
endif

if KRB5_DEP.found()
    result = cpp.run(
        fs.read('compiler-checks/have-gss-str-to-oid.cc'),
        name: 'HAVE_GSS_STR_TO_OID',
        dependencies: [KRB5_DEP],
    )
    conf_data.set('HAVE_GSS_STR_TO_OID', result.returncode() == 0)
endif

#### Other checks.

if POSTGRESQL_DEP.found()
    # TODO: change to proper check, not version check.
    version = POSTGRESQL_DEP.version()
    conf_data.set(
        'HAVE_PGSQL_TCP_USER_TIMEOUT',
        version.version_compare('>=12.0'),
    )
endif

# For Solaris.
conf_data.set('HAVE_SYS_FILIO_H', cpp.has_header('sys/filio.h', required: false))

if valgrind.found()
    conf_data.set(
        'HAVE_VALGRIND_HEADERS',
        cpp.has_header('valgrind/valgrind.h', required: false),
    )
endif

result = run_command(cpp, '-dumpmachine', check: false)
if result.returncode() == 0
    d = result.stdout().strip()
    conf_data.set('LIBC_MUSL', d.endswith('-musl'))
endif

if KRB5_DEP.found() and KRB5_DEP.get_variable('vendor').contains('Heimdal')
    conf_data.set('WITH_HEIMDAL', true)
endif

# KEA_PKG_VERSION_IN_CONFIGURE: date and timestamp of the package e.g. "isc20230921141113"
# KEA_PKG_TYPE_IN_CONFIGURE: type of the package "rpm", "deb" or "apk"
kea_pkg_type_in_configure = run_command(
    ENV,
    'KEA_PKG_TYPE_IN_CONFIGURE',
    check: true,
).stdout().strip()
kea_pkg_version_in_configure = run_command(
    ENV,
    'KEA_PKG_VERSION_IN_CONFIGURE',
    check: true,
).stdout().strip()
if kea_pkg_type_in_configure != '' and kea_pkg_version_in_configure != ''
    extended_version = f'@kea_pkg_version_in_configure@ @kea_pkg_type_in_configure@'
else
    if fs.is_dir('.git') and git.found()
        result = run_command(
            CD_AND_RUN,
            TOP_SOURCE_DIR,
            git,
            'rev-parse',
            'HEAD',
            check: false,
        )
        if result.returncode() == 0
            extended_version = 'git ' + result.stdout().strip()
        endif
    else
        extended_version = 'tarball'
    endif
endif
conf_data.set('EXTENDED_VERSION', f'"@PROJECT_VERSION@ (@extended_version@)"')

if PROJECT_VERSION.split('.')[1].to_int() % 2 == 0
    package_version_type = 'stable'
else
    package_version_type = 'development'
endif
conf_data.set('PACKAGE_VERSION_TYPE', f'"@package_version_type@"')

#### System-specific Compiler Flags

compile_args = []
link_args = []

# $ORIGIN documented at https://www.man7.org/linux/man-pages/man8/ld.so.8.html
rpath1 = '$ORIGIN/../lib'  # rpath for executables
rpath2 = '$ORIGIN/../..'  # rpath for hook libraries
if SYSTEM == 'darwin'
    compile_args += ['-D__APPLE_USE_RFC_3542']
    add_project_arguments('-D__APPLE_USE_RFC_3542', language: 'cpp')
    link_arg = f'-Wl,-rpath,@rpath1@,-rpath,@rpath2@'
    link_args += [link_arg]
    add_project_link_arguments(link_arg, language: 'cpp')
else
    link_arg = f'-Wl,-rpath=@rpath1@,-rpath=@rpath2@'
    link_args += [link_arg]
    add_project_link_arguments(link_arg, language: 'cpp')
endif

premium = fs.is_dir('premium')
if premium
    conf_data.set('PREMIUM', 'yes')
    conf_data.set('PREMIUM_EXTENDED_VERSION', f'"yes (@extended_version@)"')
else
    conf_data.set('PREMIUM', 'no')
    conf_data.set('PREMIUM_EXTENDED_VERSION', '"no"')
endif

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
report_conf_data.set('PACKAGE_VERSION_TYPE', package_version_type)
report_conf_data.set(
    'EXTENDED_VERSION',
    f'@PROJECT_VERSION@ (@extended_version@)',
)
report_conf_data.set('OS_TYPE', OS_TYPE)
report_conf_data.set('PREFIX', PREFIX)
report_conf_data.set('HOOKS_DIR', DEFAULT_HOOKS_PATH)
report_conf_data.set('PREMIUM', premium ? 'yes' : 'no')
report_conf_data.set('BUILD_OPTIONS', meson.build_options())
report_conf_data.set('MESON_VERSION', meson.version())
if fs.is_dir(TOP_BUILD_DIR / 'meson-info')
    MESON_INFO = PREFIX / DATADIR / 'kea/meson-info'
else
    MESON_INFO = 'not installed'
endif
report_conf_data.set('MESON_INFO', MESON_INFO)
report_conf_data.set('CXX', ' '.join(cpp.cmd_array()))
report_conf_data.set('CXX_ID', cpp.get_id())
result = run_command(cpp, '--version', check: false)
if result.returncode() == 0
    v = result.stdout().strip().split('\n')
    report_conf_data.set('CXX_VERSION', v.get(0, 'unknown'))
else
    report_conf_data.set('CXX_VERSION', 'unknown')
endif
# The required keyword in cpp.run() is an 1.5.0 feature.
result = cpp.run(
    fs.read('compiler-checks/get-cpp-standard.cc'),
    name: 'Get cpp standard',
)
if result.returncode() == 0
    report_conf_data.set('CXX_STANDARD', result.stdout().strip())
else
    error('Cpp standard is unknown')
endif
report_conf_data.set('CXX_ARGS', ' '.join(compile_args))
report_conf_data.set('LD_ID', cpp.get_linker_id())
report_conf_data.set('LD_ARGS', ' '.join(link_args))
report_conf_data.set('PYTHON_PATH', PYTHON.full_path())
report_conf_data.set('PYTHON_VERSION', PYTHON.version())
report_conf_data.set('PKGPYTHONDIR', PKGPYTHONDIR)
result = cpp.run(
    fs.read('compiler-checks/get-boost-version.cc'),
    dependencies: [boost_dep, threads_dep],
    name: 'Get Boost version',
)
if result.returncode() == 0
    report_conf_data.set('BOOST_VERSION', result.stdout().strip())
else
    report_conf_data.set('BOOST_VERSION', 'unknown version')
endif
if CRYPTO_DEP.name() == botan.name()
    report_conf_data.set('CRYPTO_NAME', 'Botan')
    report_conf_data.set('SPACES', '             ')
    result = cpp.run(
        fs.read('compiler-checks/get-botan-version.cc'),
        name: 'Get Botan version',
        dependencies: [CRYPTO_DEP],
    )
    if result.returncode() == 0
        version = result.stdout().strip()
    else
        version = botan.version()
    endif
    if version == 'unknown'
        version = 'unknown version'
    endif
    report_conf_data.set('CRYPTO_VERSION', version)
elif CRYPTO_DEP.name() == openssl.name()
    report_conf_data.set('CRYPTO_NAME', 'OpenSSL')
    report_conf_data.set('SPACES', '           ')
    result = cpp.run(
        fs.read('compiler-checks/get-openssl-version.cc'),
        name: 'Get OpenSSL version',
        dependencies: [CRYPTO_DEP],
    )
    if result.returncode() == 0
        version = result.stdout().strip()
    else
        version = openssl.version()
    endif
    if version == 'unknown'
        version = 'unknown version'
    endif
    report_conf_data.set('CRYPTO_VERSION', version)
endif
result = cpp.run(
    fs.read('compiler-checks/get-log4cplus-version.cc'),
    name: 'Get Log4cplus version',
    dependencies: [LOG4CPLUS_DEP],
)
if result.returncode() == 0
    version = result.stdout().strip()
else
    version = log4cplus.version()
endif
if version == 'unknown'
    version = 'unknown version'
endif
report_conf_data.set('LOG4CPLUS_VERSION', version)
if FLEX.found()
    report_conf_data.set('FLEX', FLEX.full_path())
else
    report_conf_data.set('FLEX', 'no')
endif
if BISON.found()
    report_conf_data.set('BISON', BISON.full_path())
else
    report_conf_data.set('BISON', 'no')
endif
if MYSQL_DEP.found()
    report_conf_data.set('HAVE_MYSQL', 'yes')
    version = MYSQL_DEP.version()
    if version == 'unknown'
        version = 'unknown version'
    endif
    report_conf_data.set('MYSQL_VERSION', version)
else
    report_conf_data.set('HAVE_MYSQL', 'no')
    report_conf_data.set('MYSQL_VERSION', 'no')
endif
if POSTGRESQL_DEP.found()
    report_conf_data.set('HAVE_PGSQL', 'yes')
    version = POSTGRESQL_DEP.version()
    if version == 'unknown'
        version = 'unknown version'
    endif
    report_conf_data.set('PGSQL_VERSION', version)
else
    report_conf_data.set('HAVE_PGSQL', 'no')
    report_conf_data.set('PGSQL_VERSION', 'no')
endif
if NETCONF_DEP.found()
    report_conf_data.set('HAVE_NETCONF', 'yes')
    report_conf_data.set(
        'LIBYANG_PREFIX',
        NETCONF_DEP.get_variable('libyang_prefix', default_value: 'unknown'),
    )
    report_conf_data.set(
        'SYSREPO_PREFIX',
        NETCONF_DEP.get_variable('sysrepo_prefix', default_value: 'unknown'),
    )
    report_conf_data.set(
        'LIBYANG_VERSION',
        NETCONF_DEP.get_variable(
            'libyang_version',
            default_value: 'unknown version',
        ),
    )
    report_conf_data.set(
        'LIBYANGCPP_VERSION',
        NETCONF_DEP.get_variable(
            'libyangcpp_version',
            default_value: 'unknown version',
        ),
    )
    report_conf_data.set(
        'SYSREPO_VERSION',
        NETCONF_DEP.get_variable(
            'sysrepo_version',
            default_value: 'unknown version',
        ),
    )
    report_conf_data.set(
        'SYSREPOCPP_VERSION',
        NETCONF_DEP.get_variable(
            'sysrepocpp_version',
            default_value: 'unknown version',
        ),
    )
else
    report_conf_data.set('HAVE_NETCONF', 'no')
    report_conf_data.set('LIBYANG_PREFIX', 'no')
    report_conf_data.set('SYSREPO_PREFIX', 'no')
    report_conf_data.set('LIBYANG_VERSION', 'no')
    report_conf_data.set('LIBYANGCPP_VERSION', 'no')
    report_conf_data.set('SYSREPO_VERSION', 'no')
    report_conf_data.set('SYSREPOCPP_VERSION', 'no')
endif
if FUZZ_OPT.enabled() or TESTS_OPT.enabled()
    report_conf_data.set('HAVE_GTEST', 'yes')
    version = GTEST_DEP.version()
    if version == 'unknown'
        version = 'unknown version'
    endif
    report_conf_data.set('GTEST_VERSION', version)
else
    report_conf_data.set('HAVE_GTEST', 'no')
    report_conf_data.set('GTEST_VERSION', 'no')
endif
if KRB5_DEP.found()
    report_conf_data.set('HAVE_KRB5', 'yes')
    version = KRB5_DEP.version()
    if version == 'unknown'
        version = 'unknown version'
    endif
    report_conf_data.set('KRB5_GSSAPI_VERSION', version)
    report_conf_data.set(
        'KRB5_GSSAPI_VENDOR',
        KRB5_DEP.get_variable('vendor', default_value: 'unknown'),
    )
else
    report_conf_data.set('HAVE_KRB5', 'no')
    report_conf_data.set('KRB5_GSSAPI_VERSION', 'unknown')
    report_conf_data.set('KRB5_GSSAPI_VENDOR', 'unknown')
endif
if TESTS_OPT.enabled()
    report_conf_data.set('TESTS_ENABLED', 'enabled')
else
    report_conf_data.set('TESTS_ENABLED', 'disabled')
endif
if FUZZ_OPT.enabled()
    report_conf_data.set('FUZZ_ENABLED', 'enabled')
else
    report_conf_data.set('FUZZ_ENABLED', 'disabled')
endif
if valgrind.found()
    report_conf_data.set('VALGRIND', valgrind.full_path())
else
    report_conf_data.set('VALGRIND', 'no')
endif
if have_afl
    report_conf_data.set('HAVE_AFL', 'yes')
else
    report_conf_data.set('HAVE_AFL', 'no')
endif

#### Custom Targets

run_target(
    'add-changelog-entry',
    command: [TOP_SOURCE_DIR / 'changelog_unreleased/.add-entry.sh'],
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
            f'--suppressions=@TOP_SOURCE_DIR@/src/valgrind.supp',
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
            f'--suppressions=@TOP_SOURCE_DIR@/src/valgrind.supp',
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
    command: [TOP_BUILD_DIR / 'config-report.sh'],
)

# TODO: Change to config.h.in when autotools are removed.
configure_file(
    input: 'meson-config.h.in',
    output: 'config.h',
    configuration: conf_data,
    install: true,
    install_dir: INCLUDEDIR / 'kea',
)

# TODO: Change to kea_version.h.in when autotools are removed.
configure_file(
    input: 'meson-kea_version.h.in',
    output: 'kea_version.h',
    configuration: conf_data,
    install: true,
    install_dir: INCLUDEDIR / 'kea',
)

#### Build Starts Here

# LIBS_BUILT_SO_FAR makes sense because the linker is called with
# the --as-needed flag so ignores (i.e. does not link) unused libraries.
LIBS_BUILT_SO_FAR = []

TARGETS_GEN_MESSAGES = []
TARGETS_GEN_PARSER = []

subdir('tools')
subdir('src')
subdir('fuzz')
subdir('doc')
if premium
    subdir('premium')
endif

#### More Custom Targets

if TARGETS_GEN_MESSAGES.length() > 0
    alias_target('messages', TARGETS_GEN_MESSAGES)
else
    error(
        'No messages to generate. This is probably an error in the meson.build files.',
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
install_data(top_docs, install_dir: DATADIR / 'doc/kea')
install_emptydir(RUNSTATEDIR)

# Print the setup report.
message(run_command(['cat', CONFIG_REPORT], check: true).stdout())

# Copy the meson.info directory during installation.
install_meson_info = configure_file(
    input: 'install-meson-info.sh.in',
    output: 'install-meson-info.sh',
    configuration: configuration_data(
        {
            'INSTALL': INSTALL.full_path(),
            'PREFIX': PREFIX,
            'TOP_BUILD_DIR': TOP_BUILD_DIR,
            'DATADIR': DATADIR,
        },
    ),
)
meson.add_install_script(install_meson_info)
