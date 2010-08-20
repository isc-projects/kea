#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.59])
AC_INIT(bind10-devel, 20100701, bind10-dev@isc.org)
AC_CONFIG_SRCDIR(README)
AM_INIT_AUTOMAKE
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CXX
AC_PROG_LIBTOOL

# Use C++ language
AC_LANG([C++])

# Identify the compiler: this check must be after AC_PROG_CXX and AC_LANG.
AM_CONDITIONAL(USE_GXX, test "X${GXX}" = "Xyes")
AC_CHECK_DECL([__SUNPRO_CC], [SUNCXX="yes"], [SUNCXX="no"])

# Linker options

# check -R rather than gcc specific -rpath to be as portable as possible.
AC_MSG_CHECKING([whether -R flag is available in linker])
LDFLAGS_SAVED="$LDFLAGS"
LDFLAGS="$LDFLAGS -R/usr/lib"
AC_TRY_LINK([],[],
	[ AC_MSG_RESULT(yes)
		rpath_available=yes
	],[ AC_MSG_RESULT(no)
	rpath_available=no
	])
LDFLAGS=$LDFLAGS_SAVED

# allow building programs with static link.  we need to make it selective
# because loadable modules cannot be statically linked.
AC_ARG_ENABLE([static-link],
AC_HELP_STRING([--enable-static-link],
  [build programs with static link [[default=no]]]),
  [enable_static_link=yes], [enable_static_link=no])
AM_CONDITIONAL(USE_STATIC_LINK, test $enable_static_link = yes)

# OS dependent configuration
SET_ENV_LIBRARY_PATH=no
ENV_LIBRARY_PATH=LD_LIBRARY_PATH

case "$host" in
*-solaris*)
	# Solaris requires special definitions to get some standard libraries
	# (e.g. getopt(3)) available with common used header files.
	CPPFLAGS="$CPPFLAGS -D_XPG4_2 -D__EXTENSIONS__"
	;;
*-apple-darwin*)
	# libtool doesn't work pefectly with Darwin: libtool embeds the
	# final install path in dynamic libraries and our loadable python
	# modules always refer to that path even if it's loaded within the
	# source tree.  This prevents pre-install tests from working.
	# To work around this problem we explicitly specify paths to dynamic
	# libraries when we use them in the source tree.
	SET_ENV_LIBRARY_PATH=yes
	ENV_LIBRARY_PATH=DYLD_LIBRARY_PATH
	;;
esac
AM_CONDITIONAL(SET_ENV_LIBRARY_PATH, test $SET_ENV_LIBRARY_PATH = yes)
AC_SUBST(SET_ENV_LIBRARY_PATH)
AC_SUBST(ENV_LIBRARY_PATH)

m4_define([_AM_PYTHON_INTERPRETER_LIST], [python python3 python3.1])
AC_ARG_WITH([pythonpath],
AC_HELP_STRING([--with-pythonpath=PATH],
  [specify an absolute path to python executable when automatic version check (incorrectly) fails]),
  [python_path="$withval"], [python_path="auto"])
if test "$python_path" = auto; then
	AM_PATH_PYTHON([3.1])
else
	# Older versions of automake can't handle python3 well.  This is an
	# in-house workaround for them.
	PYTHON=$python_path
	AC_SUBST(PYTHON)
	PYTHON_PREFIX='${prefix}'
	AC_SUBST(PYTHON_PREFIX)
	PYTHON_EXEC_PREFIX='$(exec_prefix)'
	AC_SUBST(PYTHON_EXEC_PREFIX)
	PYTHON_VERSION=[`$PYTHON -c "import sys; sys.stdout.write(sys.version[:3])"`]
	if test `echo "$PYTHON_VERSION >= 3.1" | bc` != 1 ; then
		AC_MSG_ERROR(["Python version too old: $PYTHON_VERSION, need 3.1 or higher"])
	fi
	AC_SUBST(PYTHON_VERSION)
	PYTHON_PLATFORM=`$PYTHON -c "import sys; print(sys.platform)"`
	AC_SUBST(PYTHON_PLATFORM)
	pythondir='${prefix}/lib/python'$PYTHON_VERSION'/site-packages'
	AC_SUBST(pythondir)
	pkgpythondir='${pythondir}/'$PACKAGE
	AC_SUBST(pkgpythondir)
	pyexecdir='${exec_prefix}/lib/python'$PYTHON_VERSION'/site-packages'
	AC_SUBST(pyexecdir)
	pkgpyexecdir='${pyexecdir}/'$PACKAGE
	AC_SUBST(pkgpyexecdir)
fi

# Check for python development environments
if test -x ${PYTHON}-config; then
	PYTHON_INCLUDES=`${PYTHON}-config --includes`

	for flag in `${PYTHON}-config --ldflags`; do
		# add any '-L..." flags to PYTHON_LDFLAGS
		flag=`echo $flag | sed -ne 's/^\(\-L.*\)$/\1/p'`
		if test "X${flag}" != X; then
			PYTHON_LDFLAGS="$PYTHON_LDFLAGS ${flag}"
		fi
	done
	# on some platforms, ${PYTHON}-config --ldflags doesn't provide a -L
	# option while having the library under a non trivial directory.
	# as a workaround we try the "lib" sub directory under the common
	# prefix for this python.
	if test -z "${PYTHON_LDFLAGS}"; then
		PYTHON_LDFLAGS="-L`${PYTHON}-config --prefix`/lib"
	fi
else
	if test "X$PYTHON_INCLUDES" = X -o "X$PYTHON_LDFLAGS" = X; then
		AC_MSG_WARN([${PYTHON}-config does not exist or is not executable, so we could not detect python development environment.  Your system may require an additional package (e.g. "python3-dev").  Alternatively, if you are sure you have python headers and libraries, define PYTHON_INCLUDES and PYTHON_LDFLAGS and run this script.])
	fi
fi

# Some OSes including NetBSD don't install libpython.so in a well known path.
# To avoid requiring dynamic library path with our python wrapper loadable
# modules, we embed the path to the modules when possible.  We do this even
# when the path is known in the common operational environment (e.g. when
# it's stored in a common "hint" file) for simplicity.
if test $rpath_available = yes; then
	python_rpath=
	for flag in ${PYTHON_LDFLAGS}; do
		python_rpath="${python_rpath} `echo $flag | sed -ne 's/^\(\-L\)/-R/p'`"
	done
	PYTHON_LDFLAGS="${PYTHON_LDFLAGS} ${python_rpath}"
fi

AC_SUBST(PYTHON_INCLUDES)
AC_SUBST(PYTHON_LDFLAGS)

CPPFLAGS_SAVED="$CPPFLAGS"
CPPFLAGS="$CPPFLAGS ${PYTHON_INCLUDES}"
AC_CHECK_HEADERS([Python.h],, AC_MSG_ERROR([Missing Python.h]))
CPPFLAGS="$CPPFLAGS_SAVED"

# Check for python library.  Needed for Python-wrapper libraries.
LDFLAGS_SAVED="$LDFLAGS"
LDFLAGS="$LDFLAGS $PYTHON_LDFLAGS"
python_bin="python${PYTHON_VERSION}"
AC_CHECK_LIB($python_bin, main, python_lib=$python_bin, python_lib=no)
if test $python_lib != "no"; then
	PYTHON_LIB="-l$python_lib"
fi
AC_SUBST(PYTHON_LIB)
LDFLAGS=$LDFLAGS_SAVED

# TODO: check for _sqlite3.py module

# Compiler dependent settings: define some mandatory CXXFLAGS here.
# We also use a separate variable B10_CXXFLAGS.  This will (and should) be
# used as the default value for each specifc AM_CXXFLAGS:
# AM_CXXFLAGS = $(B10_CXXFLAGS)
# AM_CXXFLAGS += ... # add module specific flags
# We need this so that we can disable some specific compiler warnings per
# module basis; since AM_CXXFLAGS are placed before CXXFLAGS, and since
# gcc's -Wno-XXX option must be specified after -Wall or -Wextra, we cannot
# specify the default warning flags in CXXFLAGS and let specific modules
# "override" the default.

CXXFLAGS=-g
werror_ok=0

# SunStudio compiler requires special compiler options for boost
# (http://blogs.sun.com/sga/entry/boost_mini_howto)
if test "$SUNCXX" = "yes"; then
CXXFLAGS="$CXXFLAGS -library=stlport4 -features=tmplife -features=tmplrefstatic"
fi

# gcc specific settings:
if test "X$GXX" = "Xyes"; then
B10_CXXFLAGS="-Wall -Wextra -Wwrite-strings -Woverloaded-virtual -Wno-sign-compare"
UNUSED_PARAM_ATTRIBUTE='__attribute__((unused))'

# Certain versions of gcc (g++) have a bug that incorrectly warns about
# the use of anonymous name spaces even if they're closed in a single
# translation unit.  For these versions we have to disable -Werror.
CXXFLAGS_SAVED="$CXXFLAGS"
CXXFLAGS="$CXXFLAGS $B10_CXXFLAGS -Werror"
AC_MSG_CHECKING(for in-TU anonymous namespace breakage)
AC_TRY_COMPILE([namespace { class Foo {}; }
namespace isc {class Bar {Foo foo_;};} ],,
	[AC_MSG_RESULT(no)
	 werror_ok=1
	 B10_CXXFLAGS="$B10_CXXFLAGS -Werror"],
	[AC_MSG_RESULT(yes)])
CXXFLAGS="$CXXFLAGS_SAVED"

fi				dnl GXX = yes

AM_CONDITIONAL(GCC_WERROR_OK, test $werror_ok = 1)
AC_DEFINE_UNQUOTED(UNUSED_PARAM, $UNUSED_PARAM_ATTRIBUTE, Define to compiler keyword indicating a function argument is intentionally unused)

# produce PIC unless we disable shared libraries. need this for python bindings.
if test $enable_shared != "no" -a "X$GXX" = "Xyes"; then
   B10_CXXFLAGS="$B10_CXXFLAGS -fPIC"
fi

AC_SUBST(B10_CXXFLAGS)

# Checks for libraries.

AC_SEARCH_LIBS(inet_pton, [nsl])
AC_SEARCH_LIBS(recvfrom, [socket])

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_TYPE_SIZE_T



AC_MSG_CHECKING(for sa_len in struct sockaddr)
AC_TRY_COMPILE([
#include <sys/types.h>
#include <sys/socket.h>],
[struct sockaddr sa; sa.sa_len = 0; return (0);],
        [AC_MSG_RESULT(yes)
        AC_DEFINE(HAVE_SA_LEN, 1, [Define to 1 if sockaddr has a sa_len member, and corresponding sin_len and sun_len])],
        AC_MSG_RESULT(no))

AC_ARG_WITH(lcov,
[  --with-lcov[=PROGRAM]         enable gtest and coverage target using the specified lcov], lcov="$withval", lcov="no")

AC_ARG_WITH(gtest,
[  --with-gtest=PATH       specify a path to gtest header files (PATH/include) and library (PATH/lib)],
    gtest_path="$withval", gtest_path="no")


USE_LCOV="no"
if test "$lcov" != "no"; then
	# force gtest if not set
	if test "$gtest_path" = "no"; then
#		AC_MSG_ERROR("lcov needs gtest for test coverage report")
		AC_MSG_NOTICE([gtest support is now enabled, because used by coverage tests])
		gtest_path="yes"
	fi
	if test "$lcov" != "yes"; then
		LCOV=$lcov
	else
		AC_PATH_PROG([LCOV], [lcov])
	fi
	if test -x "${LCOV}"; then
		USE_LCOV="yes"
	else
		AC_MSG_ERROR([Cannot find lcov.])
	fi
	# is genhtml always in the same directory?
	GENHTML=`echo "$LCOV" | sed s/lcov$/genhtml/`
	if test ! -x $GENHTML; then
		AC_MSG_ERROR([genhtml not found, needed for lcov])
	fi
	# GCC specific?
	CXXFLAGS="$CXXFLAGS -fprofile-arcs -ftest-coverage"
	LIBS=" $LIBS -lgcov"
	AC_SUBST(CPPFLAGS)
	AC_SUBST(LIBS)
	AC_SUBST(LCOV)
	AC_SUBST(GENHTML)
fi
AC_SUBST(USE_LCOV)

AC_ARG_WITH([boost-include],
  AC_HELP_STRING([--with-boost-include=PATH],
    [specify exact directory for Boost headers]),
    [boost_include_path="$withval"])
if test "${boost_include_path}" ; then
	BOOST_INCLUDES="-I${boost_include_path}"
	CPPFLAGS="$CPPFLAGS $BOOST_INCLUDES"
fi
AC_SUBST(BOOST_INCLUDES)

#
# Check availability of gtest, which will be used for unit tests.
#
if test "$gtest_path" != "no"
then
	if test "$gtest_path" != "yes"; then
		GTEST_PATHS=$gtest_path
		if test -x "${gtest_path}/bin/gtest-config" ; then
			GTEST_CONFIG="${gtest_path}/bin/gtest-config"
		fi
	else
		AC_PATH_PROG([GTEST_CONFIG], [gtest-config])
	fi
	if test -x "${GTEST_CONFIG}" ; then :
		# using cppflags instead of cxxflags
		GTEST_INCLUDES=`${GTEST_CONFIG} --cppflags`
		GTEST_LDFLAGS=`${GTEST_CONFIG} --ldflags`
		GTEST_LDADD=`${GTEST_CONFIG} --libs`
		GTEST_FOUND="true"
	else
		AC_MSG_WARN([Unable to locate Google Test gtest-config.])
		if test -z "${GTEST_PATHS}" ; then
			GTEST_PATHS="/usr /usr/local"
		fi
		GTEST_FOUND="false"
	fi
	if test "${GTEST_FOUND}" != "true"; then
		GTEST_FOUND="false"
		for dir in $GTEST_PATHS; do
			if test -f "$dir/include/gtest/gtest.h"; then
				GTEST_INCLUDES="-I$dir/include"
				GTEST_LDFLAGS="-L$dir/lib"
				GTEST_LDADD="-lgtest"
				GTEST_FOUND="true"
				break
			fi
		done
	fi
	if test "${GTEST_FOUND}" != "true"; then
		AC_MSG_ERROR([Cannot find gtest in: $GTEST_PATHS])
	fi
else
	GTEST_INCLUDES=
	GTEST_LDFLAGS=
	GTEST_LDADD=
fi
AM_CONDITIONAL(HAVE_GTEST, test $gtest_path != "no")
AC_SUBST(GTEST_INCLUDES)
AC_SUBST(GTEST_LDFLAGS)
AC_SUBST(GTEST_LDADD)

dnl check for pkg-config itself so we don't try the m4 macro without pkg-config
AC_CHECK_PROG(HAVE_PKG_CONFIG, pkg-config, yes, no)
if test "x$HAVE_PKG_CONFIG" = "xno" ; then
  AC_MSG_ERROR(Please install pkg-config)
fi
PKG_CHECK_MODULES(SQLITE, sqlite3 >= 3.3.9, enable_features="$enable_features SQLite3")

# I can't get some of the #include <asio.hpp> right without this
# TODO: find the real cause of asio/boost wanting pthreads
# (this currently only occurs for src/lib/cc/session_unittests)
PTHREAD_LDFLAGS=
AC_CHECK_LIB(pthread, pthread_create,[ PTHREAD_LDFLAGS=-lpthread ], [])
AC_SUBST(PTHREAD_LDFLAGS)

#
# ASIO: we extensively use it as the C++ event management module.
#
# Use local ASIO headers from ext
#
CPPFLAGS="$CPPFLAGS -I\$(top_srcdir)/ext/asio"
#
# kqueue portability: ASIO uses kqueue by default if it's available (it's
# generally available in BSD variants).  Unfortunately, some public
# implementation of kqueue forces a conversion from a pointer to an integer,
# which is prohibited in C++ unless reinterpret_cast, C++'s most evil beast
# (and ASIO doesn't use it anyway) is used.  This will cause build error for
# some of our C++ files including ASIO header files.  The following check
# detects such cases and tells ASIO not to use kqueue if so.
AC_CHECK_FUNC(kqueue, ac_cv_have_kqueue=yes, ac_cv_have_kqueue=no)
if test "X$ac_cv_have_kqueue" = "Xyes"; then
	AC_MSG_CHECKING([whether kqueue EV_SET compiles in C++])
	AC_TRY_COMPILE([
#include <sys/types.h>
#include <sys/param.h>
#include <sys/event.h>],
[char* udata;
EV_SET(NULL, 0, 0, 0, 0, 0, udata);],
	[AC_MSG_RESULT(yes)],
	[AC_MSG_RESULT([no, disable kqueue for ASIO])
	 CPPFLAGS="$CPPFLAGS -DASIO_DISABLE_KQUEUE=1"
	])
fi

# /dev/poll issue: ASIO uses /dev/poll by default if it's available (generally
# the case with Solaris).  Unfortunately its /dev/poll specific code would
# trigger the gcc's "missing-field-initializers" warning, which would
# subsequently make the build fail with -Werror.  Further, older versions of
# gcc don't provide an option to selectively suppress this warning.
# So, for the moment, we simply disable the use of /dev/poll.  Unless we
# implement recursive DNS server with randomized ports, we don't need the
# scalability that /dev/poll can provide, so this decision wouldn't affect
# run time performance.  Hpefully we can find a better solution or the ASIO
# code will be updated by the time we really need it.
AC_CHECK_HEADERS(sys/devpoll.h, ac_cv_have_devpoll=yes, ac_cv_have_devpoll=no)
if test "X$ac_cv_have_devpoll" = "Xyes" -a "X$GXX" = "Xyes"; then
	CPPFLAGS="$CPPFLAGS -DASIO_DISABLE_DEV_POLL=1"
fi

# Check for headers from required devel kits.
AC_CHECK_HEADERS([boost/shared_ptr.hpp boost/foreach.hpp],,
  AC_MSG_ERROR([Missing required header files.]))

AC_ARG_ENABLE(man, [AC_HELP_STRING([--enable-man],
  [regenerate man pages [default=no]])] ,enable_man=yes, enable_man=no)

AM_CONDITIONAL(ENABLE_MAN, test x$enable_man != xno)

AC_ARG_ENABLE(install-configurations,
  [AC_HELP_STRING([--disable-install-configurations],
  [do not install configuration])], install_configurations=$enableval, install_configurations=yes)

AM_CONDITIONAL(INSTALL_CONFIGURATIONS, test x$install_configurations = xyes || test x$install_configurations = xtrue)

AC_CONFIG_FILES([Makefile
                 src/Makefile
                 src/bin/Makefile
                 src/bin/bind10/Makefile
                 src/bin/bind10/tests/Makefile
                 src/bin/cmdctl/Makefile
                 src/bin/cmdctl/tests/Makefile
                 src/bin/bindctl/Makefile
                 src/bin/bindctl/tests/Makefile
                 src/bin/cfgmgr/Makefile
                 src/bin/cfgmgr/tests/Makefile
                 src/bin/host/Makefile
                 src/bin/loadzone/Makefile
                 src/bin/loadzone/tests/correct/Makefile
                 src/bin/loadzone/tests/error/Makefile
                 src/bin/msgq/Makefile
                 src/bin/msgq/tests/Makefile
                 src/bin/auth/Makefile
                 src/bin/auth/tests/Makefile
                 src/bin/xfrin/Makefile
                 src/bin/xfrin/tests/Makefile
                 src/bin/xfrout/Makefile
                 src/bin/xfrout/tests/Makefile
                 src/bin/zonemgr/Makefile
                 src/bin/zonemgr/tests/Makefile
                 src/bin/usermgr/Makefile
                 src/lib/Makefile
                 src/lib/bench/Makefile
                 src/lib/bench/example/Makefile
                 src/lib/bench/tests/Makefile
                 src/lib/cc/Makefile
                 src/lib/cc/tests/Makefile
                 src/lib/python/Makefile
                 src/lib/python/isc/Makefile
                 src/lib/python/isc/datasrc/Makefile
                 src/lib/python/isc/cc/Makefile
                 src/lib/python/isc/cc/tests/Makefile
                 src/lib/python/isc/config/Makefile
                 src/lib/python/isc/config/tests/Makefile
                 src/lib/python/isc/log/Makefile
                 src/lib/python/isc/log/tests/Makefile
                 src/lib/python/isc/notify/Makefile
                 src/lib/python/isc/notify/tests/Makefile
                 src/lib/config/Makefile
                 src/lib/config/tests/Makefile
                 src/lib/config/testdata/Makefile
                 src/lib/dns/Makefile
                 src/lib/dns/tests/Makefile
                 src/lib/dns/python/Makefile
                 src/lib/dns/python/tests/Makefile
                 src/lib/exceptions/Makefile
                 src/lib/exceptions/tests/Makefile
                 src/lib/datasrc/Makefile
                 src/lib/datasrc/tests/Makefile
                 src/lib/xfr/Makefile
               ])
AC_OUTPUT([src/bin/cfgmgr/b10-cfgmgr.py
           src/bin/cfgmgr/tests/b10-cfgmgr_test.py
           src/bin/cmdctl/cmdctl.py
           src/bin/cmdctl/run_b10-cmdctl.sh
           src/bin/cmdctl/tests/cmdctl_test
           src/bin/cmdctl/cmdctl.spec.pre
           src/bin/xfrin/tests/xfrin_test
           src/bin/xfrin/xfrin.py
           src/bin/xfrin/xfrin.spec.pre
           src/bin/xfrin/run_b10-xfrin.sh
           src/bin/xfrout/xfrout.py
           src/bin/xfrout/xfrout.spec.pre
           src/bin/xfrout/tests/xfrout_test
           src/bin/xfrout/run_b10-xfrout.sh
           src/bin/zonemgr/zonemgr.py
           src/bin/zonemgr/zonemgr.spec.pre
           src/bin/zonemgr/tests/zonemgr_test
           src/bin/zonemgr/run_b10-zonemgr.sh
           src/bin/bind10/bind10.py
           src/bin/bind10/tests/bind10_test
           src/bin/bind10/run_bind10.sh
           src/bin/bindctl/run_bindctl.sh
           src/bin/bindctl/bindctl-source.py
           src/bin/bindctl/tests/bindctl_test
           src/bin/loadzone/run_loadzone.sh
           src/bin/loadzone/tests/correct/correct_test.sh
           src/bin/loadzone/tests/error/error_test.sh
           src/bin/loadzone/b10-loadzone.py
           src/bin/usermgr/run_b10-cmdctl-usermgr.sh
           src/bin/usermgr/b10-cmdctl-usermgr.py
           src/bin/msgq/msgq.py
           src/bin/msgq/tests/msgq_test
           src/bin/msgq/run_msgq.sh
           src/bin/auth/auth.spec.pre
           src/bin/auth/spec_config.h.pre
           src/lib/config/tests/data_def_unittests_config.h
           src/lib/python/isc/config/tests/config_test
           src/lib/python/isc/cc/tests/cc_test
           src/lib/python/isc/log/tests/log_test
           src/lib/python/isc/notify/tests/notify_out_test
           src/lib/dns/gen-rdatacode.py
           src/lib/python/bind10_config.py
           src/lib/dns/tests/testdata/gen-wiredata.py
           src/lib/cc/session_config.h.pre
           src/lib/cc/tests/session_unittests_config.h
          ], [
           chmod +x src/bin/cmdctl/run_b10-cmdctl.sh
           chmod +x src/bin/xfrin/run_b10-xfrin.sh
           chmod +x src/bin/xfrout/run_b10-xfrout.sh
           chmod +x src/bin/zonemgr/run_b10-zonemgr.sh
           chmod +x src/bin/bind10/run_bind10.sh
           chmod +x src/bin/cmdctl/tests/cmdctl_test
           chmod +x src/bin/xfrin/tests/xfrin_test
           chmod +x src/bin/xfrout/tests/xfrout_test
           chmod +x src/bin/zonemgr/tests/zonemgr_test
           chmod +x src/bin/bindctl/tests/bindctl_test
           chmod +x src/bin/bindctl/run_bindctl.sh
           chmod +x src/bin/loadzone/run_loadzone.sh
           chmod +x src/bin/loadzone/tests/correct/correct_test.sh
           chmod +x src/bin/loadzone/tests/error/error_test.sh
           chmod +x src/bin/usermgr/run_b10-cmdctl-usermgr.sh
           chmod +x src/bin/msgq/run_msgq.sh
           chmod +x src/bin/msgq/tests/msgq_test
           chmod +x src/lib/dns/gen-rdatacode.py
           chmod +x src/lib/dns/tests/testdata/gen-wiredata.py
          ])
AC_OUTPUT

dnl Print the results
dnl

cat > config.report << END

     BIND 10 source configure results:
    -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

Package:
  Name:          $PACKAGE_NAME
  Version:       $PACKAGE_VERSION

Flags:
  DEFS:          $DEFS
  CPPFLAGS:      $CPPFLAGS
  CFLAGS:        $CFLAGS
  CXXFLAGS:      $CXXFLAGS
  B10_CXXFLAGS:  $B10_CXXFLAGS
dnl includes too
  Python:        ${PYTHON_INCLUDES}
                 ${PYTHON_LDFLAGS}
                 ${PYTHON_LIB}
  SQLite:        $SQLITE_CFLAGS
                 $SQLITE_LIBS

Features:
  $enable_features

Developer:
  Google Tests:  $gtest_path
  Code Coverage: $USE_LCOV
  Generate Manuals:  $enable_man

END

cat config.report
cat <<EOF

  Now you can type "make" to build BIND 10

EOF

