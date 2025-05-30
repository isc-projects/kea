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
    version: '3.0.0-git',
    meson_version: '>=1.1.0',
    license: 'MPL-2.0',
    license_files: ['COPYING'],
    default_options: [
        'b_asneeded=true',
        'b_lundef=false',  # required for clang++ when used with sanitizers and for BSD ld when linking with extern char **environ.
        'b_pch=false',
        'b_pie=true',
        'install_umask=0027',
        'warning_level=2',
    ],
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

# Meson is annoying with its opinionated alteration of certain paths based on whether prefix is default or not.
# So we revert what it does.
if PREFIX == '/usr/local'
    LOCALSTATEDIR = 'var'    # Otherwise, it would have been 'var/local'.
endif

DATABASE_SCRIPTS_DIR = TOP_BUILD_DIR / 'src/share/database/scripts'
HOOKS_PATH = LIBDIR / 'kea/hooks'
DEFAULT_HOOKS_PATH = PREFIX / HOOKS_PATH
KEA_ADMIN_BUILT = TOP_BUILD_DIR / 'src/bin/admin/kea-admin'
KEA_ADMIN_INSTALLED = PREFIX / SBINDIR / 'kea-admin'
KEA_LFC_BUILT = TOP_BUILD_DIR / 'src/bin/lfc/kea-lfc'
KEA_LFC_INSTALLED = PREFIX / SBINDIR / 'kea-lfc'
LOCALSTATEDIR_INSTALLED = PREFIX / LOCALSTATEDIR
LIBDIR_INSTALLED = PREFIX / LIBDIR
LOGDIR = LOCALSTATEDIR / 'log/kea'
LOGDIR_INSTALLED = PREFIX / LOGDIR
RUNSTATEDIR = LOCALSTATEDIR / 'run/kea'
RUNSTATEDIR_INSTALLED = PREFIX / RUNSTATEDIR
SHAREDSTATEDIR = LOCALSTATEDIR / 'lib/kea'
SHAREDSTATEDIR_INSTALLED = PREFIX / SHAREDSTATEDIR
SYSCONFDIR_INSTALLED = PREFIX / SYSCONFDIR
TEST_CA_DIR = TOP_SOURCE_DIR / 'src/lib/asiolink/testutils/ca'

# Meson is annoying with its opinionated alteration of certain paths based on whether prefix is default or not.
# So we revert what it does.
if PREFIX == '/usr/local'
    SYSCONFDIR_INSTALLED = '/usr/local/etc'
    LOGDIR_INSTALLED = '/usr/local/var/log/kea'
    RUNSTATEDIR_INSTALLED = '/usr/local/var/run/kea'
    SHAREDSTATEDIR_INSTALLED = '/usr/local/var/lib/kea'
endif

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

# TODO: Remaining define macros used in code, but not handled by meson:
# - USE_STATIC_LINK

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
    'boost/multiprecision/cpp_int.hpp',
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
    'yang-prefix',
    default_value: 'unknown',
) == 'unknown'
    error('Dependency not found: NETCONF.')
endif

# Google Test
GTEST_DEP = dependency(
    'gtest',
    fallback: ['gtest', 'gtest_dep'],
    required: FUZZ_OPT.enabled() or TESTS_OPT.enabled(),
)

# Crypto
if crypto_opt == 'botan'
    if botan.found()
        CRYPTO_DEP = botan
    else
        error('botan required but not found')
    endif
elif crypto_opt == 'openssl'
    if openssl.found()
        CRYPTO_DEP = openssl
    else
        error('openssl required but not found')
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

# The required keyword in cpp.run() is an 1.5.0 feature.
result = cpp.run(
    fs.read('compiler-checks/get-cpp-standard.cc'),
    name: 'Get cpp standard',
)
if result.returncode() == 0
    cpp_standard = result.stdout().strip()
else
    error('C++ standard is unknown')
endif
message(f'Detected C++ standard (__cplusplus value) is @cpp_standard@.')
cpp_std_opt = get_option('cpp_std')
no_cpp_std_opt_msg = 'Please set a C++ standard by passing the -D cpp_std argument to meson.'
cpp_std_opt_msg = f'-D cpp_std=@cpp_std_opt@ is not enough.'
if cpp_standard.version_compare('<201100')
    msgs = [
        'Kea requires at least C++11 to build.',
        'Recommended C++ standard is C++14 but some dependencies require at least C++20',
    ]
    if cpp_std_opt == 'none'
        msgs += no_cpp_std_opt_msg
    else
        msgs += cpp_std_opt_msg
    endif
    error('\n'.join(msgs))
endif
if cpp_standard.version_compare('<201400')
    result = cpp.run(
        fs.read('compiler-checks/boost-math-cpp14.cc'),
        name: 'BOOST_MATH_REQUIRES_CPP14',
        dependencies: [boost_dep, threads_dep],
    )
    if result.returncode() != 0
        msgs = ['Boost Math requires at least C++14.']
        if cpp_std_opt == 'none'
            msgs += no_cpp_std_opt_msg
        else
            msgs += cpp_std_opt_msg
        endif
        error('\n'.join(msgs))
    endif
endif
# Add Botan 3 to this.
if NETCONF_DEP.found() and cpp_standard.version_compare('<202000')
    msgs = ['NETCONF dependency requires at least C++20.']
    if cpp_std_opt == 'none'
        msgs += no_cpp_std_opt_msg
    else
        msgs += cpp_std_opt_msg
    endif
    if netconf_opt.enabled()
        error('\n'.join(msgs))
    else
        msgs += 'Disabling NETCONF.'
        warning('\n'.join(msgs))
        NETCONF_DEP = disabler()
    endif
endif

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

if CRYPTO_DEP.name() == openssl.name()
    result1 = cpp.run(
        fs.read('compiler-checks/have-generic-tls-method.cc'),
        name: 'HAVE_GENERIC_TLS_METHOD',
        dependencies: [boost_dep, CRYPTO_DEP, threads_dep],
    )
    result2 = cpp.run(
        fs.read('compiler-checks/stream-truncated-error.cc'),
        name: 'HAVE_STREAM_TRUNCATED_ERROR',
        dependencies: [boost_dep, CRYPTO_DEP, threads_dep],
    )
    if result1.returncode() != 0 or result2.returncode() != 0
        error('Boost TLS support broken.')
    endif
endif

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
    # Wrap dependencies cannot be used in compiler checks: https://github.com/mesonbuild/meson/issues/11575
    # We can safely assume that googletest 1.15.2 has CreateUnifiedDiff though.
    if GTEST_DEP.type_name() == 'internal'
        conf_data.set('HAVE_CREATE_UNIFIED_DIFF', true)
    else
        result = cpp.run(
            fs.read('compiler-checks/have-create-unified-diff.cc'),
            name: 'HAVE_CREATE_UNIFIED_DIFF',
            dependencies: [GTEST_DEP],
        )
        conf_data.set('HAVE_CREATE_UNIFIED_DIFF', result.returncode() == 0)
    endif
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
    SOURCE_OF_INSTALLATION = f'@kea_pkg_version_in_configure@ @kea_pkg_type_in_configure@'
elif fs.is_dir('.git')
    SOURCE_OF_INSTALLATION = 'git'
    if git.found()
        result = run_command(
            CD_AND_RUN,
            TOP_SOURCE_DIR,
            git,
            'rev-parse',
            'HEAD',
            check: false,
        )
        if result.returncode() == 0
            SOURCE_OF_INSTALLATION += ' ' + result.stdout().strip()
        endif
    endif
else
    SOURCE_OF_INSTALLATION = 'tarball'
endif
conf_data.set(
    'EXTENDED_VERSION',
    f'"@PROJECT_VERSION@ (@SOURCE_OF_INSTALLATION@)"',
)

if PROJECT_VERSION.split('.')[1].to_int() % 2 == 0
    package_version_type = 'stable'
else
    package_version_type = 'development'
endif
conf_data.set('PACKAGE_VERSION_TYPE', f'"@package_version_type@"')

#### Compiler

compile_args = []
link_args = []

# TODO: Use $ORIGIN
# $ORIGIN documented at https://www.man7.org/linux/man-pages/man8/ld.so.8.html
# It is preferable since it would allow Kea to start even if the installation is moved.
# We have to be careful at making executables work both in the build directory and in the installation directory.
# Also, Meson might use it by default, but might not use it on all systems, so lots of variables...
# EXECUTABLE_RPATH = f'$ORIGIN/../@LIBDIR@'
# HOOK_RPATH = '$ORIGIN/../..'

BUILD_RPATH = TOP_BUILD_DIR / 'src/lib'
INSTALL_RPATH = LIBDIR_INSTALLED

# Add rpaths for NETCONF dependencies.
if NETCONF_DEP.found()
    # Flag needed to force use of rpath instead of runpath which is transitive
    # e.g. sysrepo is able to find libyang.
    if cpp.has_link_argument('-Wl,--disable-new-dtags')
        add_project_link_arguments(['-Wl,--disable-new-dtags'], language: 'cpp')
    endif

    foreach i : ['yang', 'yang-cpp', 'sysrepo', 'sysrepo-cpp']
        libdir = NETCONF_DEP.get_variable(f'@i@-libdir')
        BUILD_RPATH += f':@libdir@'
        INSTALL_RPATH += f':@libdir@'
    endforeach
endif

# rpmbuild complains about rpaths to standard locations so let us conform to
# its liking and remove them. And let's do it consistently for all packages.
if kea_pkg_type_in_configure != ''
    BUILD_RPATH = ''
    INSTALL_RPATH = ''
endif

if SYSTEM == 'darwin'
    compile_args += '-D__APPLE_USE_RFC_3542'
    add_project_arguments('-D__APPLE_USE_RFC_3542', language: 'cpp')
endif

cpp_args_opt = get_option('cpp_args')
werror_opt = get_option('werror')

# List of warnings to add and to remove.
warnings = [
    '-Wnon-virtual-dtor',
    '-Wwrite-strings',
    '-Wno-missing-field-initializers',
    #   '-Wshadow',
]
no_warnings = ['-Wno-sign-compare']
# Clang++ specific settings.
cxx_id = cpp.get_id()
if cxx_id == 'clang' and cpp_args_opt.length() == 0
    add_project_arguments('-Qunused-arguments', language: 'cpp')
    compile_args += '-Qunused-arguments'
    no_warnings += ['-Wno-unused-variable', '-Wno-unused-parameter']
endif
if werror_opt
    warnings += no_warnings
endif
if cpp_args_opt.length() == 0
    foreach warning : warnings
        if cpp.has_argument(warning)
            add_project_arguments(warning, language: 'cpp')
            compile_args += warning
        else
            message(f'@warning@ is not supported by the compiler')
        endif
    endforeach
endif

#### Premium hooks

premium = fs.is_dir('premium')
if premium
    conf_data.set('PREMIUM', 'yes')
    conf_data.set(
        'PREMIUM_EXTENDED_VERSION',
        f'"yes (@SOURCE_OF_INSTALLATION@)"',
    )
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
    f'@PROJECT_VERSION@ (@SOURCE_OF_INSTALLATION@)',
)
report_conf_data.set('OS_TYPE', OS_TYPE)
report_conf_data.set('PREFIX', PREFIX)
report_conf_data.set('HOOKS_DIR', DEFAULT_HOOKS_PATH)
report_conf_data.set('PREMIUM', premium ? 'yes' : 'no')
report_conf_data.set('MESON_VERSION', meson.version())
report_conf_data.set('MESON_INFO', DATADIR / 'kea/meson-info')
build_options = meson.build_options()
report_conf_data.set('BUILD_OPTIONS', build_options.replace('\'', '"'))
report_conf_data.set('CXX', ' '.join(cpp.cmd_array()))
report_conf_data.set('CXX_ID', cxx_id)
result = run_command(cpp, '--version', check: false)
if result.returncode() == 0
    v = result.stdout().strip().split('\n')
    report_conf_data.set('CXX_VERSION', v.get(0, 'unknown'))
else
    report_conf_data.set('CXX_VERSION', 'unknown')
endif
report_conf_data.set('CXX_STANDARD', cpp_standard)
compile_args += cpp_args_opt
report_conf_data.set('CXX_ARGS', ' '.join(compile_args))
report_conf_data.set('LD_ID', cpp.get_linker_id())
link_args += get_option('cpp_link_args')
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
    report_conf_data.set('SPACES', '                ')
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
    report_conf_data.set('SPACES', '              ')
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
        'YANG_VERSION',
        NETCONF_DEP.get_variable(
            'yang-version',
            default_value: 'unknown version',
        ),
    )
    report_conf_data.set(
        'YANG_PREFIX',
        NETCONF_DEP.get_variable('yang-prefix', default_value: 'unknown'),
    )
    report_conf_data.set(
        'YANGCPP_VERSION',
        NETCONF_DEP.get_variable(
            'yang-cpp-version',
            default_value: 'unknown version',
        ),
    )
    report_conf_data.set(
        'YANGCPP_PREFIX',
        NETCONF_DEP.get_variable('yang-cpp-prefix', default_value: 'unknown'),
    )
    report_conf_data.set(
        'SYSREPO_VERSION',
        NETCONF_DEP.get_variable(
            'sysrepo-version',
            default_value: 'unknown version',
        ),
    )
    report_conf_data.set(
        'SYSREPO_PREFIX',
        NETCONF_DEP.get_variable('sysrepo-prefix', default_value: 'unknown'),
    )
    report_conf_data.set(
        'SYSREPOCPP_VERSION',
        NETCONF_DEP.get_variable(
            'sysrepo-cpp-version',
            default_value: 'unknown version',
        ),
    )
    report_conf_data.set(
        'SYSREPOCPP_PREFIX',
        NETCONF_DEP.get_variable('sysrepo-cpp-prefix', default_value: 'unknown'),
    )
else
    report_conf_data.set('HAVE_NETCONF', 'no')
    report_conf_data.set('YANG_VERSION', 'no')
    report_conf_data.set('YANG_PREFIX', 'no')
    report_conf_data.set('YANGCPP_VERSION', 'no')
    report_conf_data.set('YANGCPP_PREFIX', 'no')
    report_conf_data.set('SYSREPO_VERSION', 'no')
    report_conf_data.set('SYSREPO_PREFIX', 'no')
    report_conf_data.set('SYSREPOCPP_VERSION', 'no')
    report_conf_data.set('SYSREPOCPP_PREFIX', 'no')
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
    input: 'config.h.in',
    output: 'config.h',
    configuration: conf_data,
    install: true,
    install_dir: INCLUDEDIR / 'kea',
)

# TODO: Change to kea_version.h.in when autotools are removed.
configure_file(
    input: 'kea_version.h.in',
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

install_emptydir(LOGDIR)
install_emptydir(RUNSTATEDIR)
install_emptydir(SHAREDSTATEDIR)

# Meson is annoying with its opinionated alteration of certain paths based on whether prefix is default or not.
# So we revert what it does..
# In case prefix is default, install to hardcoded path.
if PREFIX == '/usr/local'
    install_emptydir('/usr/local/lib/kea')
    install_emptydir('/usr/local/var/lib/kea')
    install_emptydir('/usr/local/var/log/kea')
    install_emptydir('/usr/local/var/run/kea')
endif

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
