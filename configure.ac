#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.59])
AC_INIT(bind10-devel, 20100318, bind10-bugs@isc.org)
AC_CONFIG_SRCDIR(README)
AM_INIT_AUTOMAKE
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
AC_PROG_LIBTOOL

# Use C++ language
AC_LANG_CPLUSPLUS

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

PYTHON_INCLUDES=`${PYTHON}-config --includes`
AC_SUBST(PYTHON_INCLUDES)
for flag in `${PYTHON}-config --ldflags`; do
	PYTHON_LDFLAGS="$PYTHON_LDFLAGS `echo $flag | sed -ne 's/^\(\-L.*\)$/\1/p'`"
done
AC_SUBST(PYTHON_LDFLAGS)

# Check for python library (not absolutely mandatory, but needed for
# Boost.Python when we use it.  See below.)
LDFLAGS_SAVED="$LDFLAGS"
LDFLAGS="$LDFLAGS $PYTHON_LDFLAGS"
python_bin="python${PYTHON_VERSION}"
AC_CHECK_LIB($python_bin, main, python_lib=$python_bin, python_lib=no)
if test $python_lib != "no"; then
	PYTHON_LIB="-l$python_lib"
fi
AC_SUBST(PYTHON_LIB)

# TODO: check for _sqlite3.py module

# default compiler warning settings
if test "X$GCC" = "Xyes"; then
CXXFLAGS="$CXXFLAGS -g -Wall -Wextra -Wwrite-strings -Woverloaded-virtual -Wno-sign-compare"
UNUSED_PARAM_ATTRIBUTE='__attribute__((unused))'

# Certain versions of gcc (g++) have a bug that incorrectly warns about
# the use of anonymous name spaces even if they're closed in a single
# translation unit.  For these versions we have to disable -Werror.
werror_ok=0
CXXFLAGS_SAVED="$CXXFLAGS"
CXXFLAGS="$CXXFLAGS -Werror"
AC_MSG_CHECKING(for in-TU anonymous namespace breakage)
AC_TRY_COMPILE([namespace { class Foo {}; }
namespace isc {class Bar {Foo foo_;};} ],,
	[AC_MSG_RESULT(no)
	 werror_ok=1],
	[AC_MSG_RESULT(yes)])
CXXFLAGS="$CXXFLAGS_SAVED"
fi
AC_DEFINE_UNQUOTED(UNUSED_PARAM, $UNUSED_PARAM_ATTRIBUTE, Define to compiler keyword indicating a function argument is intentionally unused)
AM_CONDITIONAL(GCC_WERROR_OK, test $werror_ok = 1)

# produce PIC unless we disable shared libraries. need this for python bindings.
if test $enable_shared != "no" -a "X$GCC" = "Xyes"; then
   CXXFLAGS="$CXXFLAGS -fPIC"
fi

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
        AC_DEFINE(HAVE_SIN_LEN, 1, Define to 1 if sockaddr_in has a sin_len member)],
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

AC_ARG_WITH([boost-lib],
AC_HELP_STRING([--with-boost-lib=PATH],
  [specify exact directory for Boost libraries]),
  [boostlib_path="$withval"])
if test "X$boostlib_path" != "X"; then
	BOOST_LDFLAGS="-L$boostlib_path"
fi
AC_SUBST(BOOST_LDFLAGS)

# Check availability of the Boost System library

AC_MSG_CHECKING([for boost::system library])
AC_ARG_WITH([boost-system],
AC_HELP_STRING([--with-boost-system],
  [specify whether to use the boost system library]),
  [with_boost_system="$withval"], [with_boost_system="auto"])

if test "$with_boost_system" != "no"; then
	LDFLAGS_SAVED="$LDFLAGS"
	LIBS_SAVED="$LIBS"
	CPPFLAGS_SAVED="$CPPFLAGS"
	CPPFLAGS="$CPPFLAGS -Iext"

	for BOOST_TRY_LIB in boost_system boost_system-mt; do
		LDFLAGS="$LDFLAGS_SAVED ${BOOST_LDFLAGS}"
		LIBS="$LIBS_SAVED -l${BOOST_TRY_LIB}"
		AC_TRY_LINK([#include <boost/system/error_code.hpp>],
			[ boost::system::error_code error_code;
			std::string message(error_code.message());
			return 0; ],
			[ AC_MSG_RESULT(yes)
			BOOST_SYSTEM_LIB="-l${BOOST_TRY_LIB}"
			],[])
		if test "X${BOOST_SYSTEM_LIB}" != X; then
        		break
		fi
	done

	LDFLAGS="$LDFLAGS_SAVED"
	CPPFLAGS="$CPPFLAGS_SAVED"
	LIBS="$LIBS_SAVED"
fi

if test "X${BOOST_SYSTEM_LIB}" = X; then
	AC_MSG_RESULT(no)
	if test "$with_boost_system" = "yes"; then
	   AC_MSG_ERROR([boost system library is requested but not found])
	fi
else
	AC_DEFINE(HAVE_BOOST_SYSTEM, 1, Define to 1 if boost system library is available)
fi

AM_CONDITIONAL(HAVE_BOOST_SYSTEM, test "X${BOOST_SYSTEM_LIB}" != X)
AC_SUBST(BOOST_SYSTEM_LIB)

# Check availability of the Boost Python library

AC_MSG_CHECKING([for boost::python library])
AC_ARG_WITH([boost-python],
AC_HELP_STRING([--with-boost-python],
  [specify whether to use the boost python library]),
  [with_boost_python="$withval"], [with_boost_python="auto"])
if test "$with_boost_python" != "no"; then
	if test "$with_boost_python" != "auto" -a "X$PYTHON_LIB" = X; then
		AC_MSG_ERROR([Boost.Python requested but python library is not available])
	fi
	LDFLAGS_SAVED="$LDFLAGS"
	LIBS_SAVED="$LIBS"
	CPPFLAGS_SAVED="$CPPFLAGS"
	CPPFLAGS="$CPPFLAGS $PYTHON_INCLUDES"

	for BOOST_TRY_LIB in boost_python boost_python-mt; do
		LDFLAGS="$LDFLAGS_SAVED ${BOOST_LDFLAGS} ${PYTHON_LDFLAGS}"
		LIBS="$LIBS_SAVED -l${BOOST_TRY_LIB} ${PYTHON_LIB}"
		AC_TRY_LINK([#include <boost/python/module.hpp>
	      using namespace boost::python;
	      BOOST_PYTHON_MODULE(test) { throw "Boost::Python test."; }],
			[ return 0; ],
			[ AC_MSG_RESULT(yes)
			BOOST_PYTHON_LIB="-l${BOOST_TRY_LIB}"
			],[])
		if test "X${BOOST_PYTHON_LIB}" != X; then
        		break
		fi
	done

	LDFLAGS="$LDFLAGS_SAVED"
	CPPFLAGS="$CPPFLAGS_SAVED"
	LIBS="$LIBS_SAVED"
fi

if test "X${BOOST_PYTHON_LIB}" = X; then
	AC_MSG_RESULT(no)
	if test "$with_boost_python" = "yes"; then
	   AC_MSG_ERROR([boost python library is requested but not found])
	fi
else
	AC_DEFINE(HAVE_BOOST_PYTHON, 1, Define to 1 if boost python library is available)
fi

AM_CONDITIONAL(HAVE_BOOST_PYTHON, test "X${BOOST_PYTHON_LIB}" != X)
AC_SUBST(BOOST_PYTHON_LIB)

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

PKG_CHECK_MODULES(SQLITE, sqlite3 >= 3.3.9)

# Check for headers from required devel kits.
# boost/shared_ptr.hpp is in ext in svn but not in tarball.
CPPFLAGS_SAVED=$CPPFLAGS
if test "X$BOOST_INCLUDES" = "X"; then
	# abs_top_srcdir not defined yet
	# so this is only useful to check.  We'll replace it after the check.
	CPPFLAGS="$CPPFLAGS -Iext"
fi
AC_CHECK_HEADERS([boost/shared_ptr.hpp boost/foreach.hpp],,
  AC_MSG_ERROR([Missing required header files.]))
CPPFLAGS=$CPPFLAGS_SAVED
if test "X$BOOST_INCLUDES" = "X"; then
	CPPFLAGS="$CPPFLAGS -I\$(top_srcdir)/ext"
fi

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
                 src/bin/cmdctl/Makefile
                 src/bin/bindctl/Makefile
                 src/bin/cfgmgr/Makefile
                 src/bin/host/Makefile
                 src/bin/loadzone/Makefile
                 src/bin/msgq/Makefile
                 src/bin/auth/Makefile
                 src/bin/auth/tests/Makefile
                 src/bin/xfrin/Makefile
                 src/bin/usermgr/Makefile
                 src/lib/Makefile
                 src/lib/cc/Makefile
                 src/lib/python/Makefile
                 src/lib/python/isc/Makefile
                 src/lib/python/isc/auth/Makefile
                 src/lib/python/isc/cc/Makefile
                 src/lib/python/isc/config/Makefile
                 src/lib/config/Makefile
                 src/lib/config/tests/Makefile
                 src/lib/dns/Makefile
                 src/lib/dns/tests/Makefile
                 src/lib/exceptions/Makefile
                 src/lib/auth/Makefile
                 src/lib/auth/tests/Makefile
               ])
AC_OUTPUT([src/bin/cfgmgr/b10-cfgmgr.py
           src/bin/cmdctl/cmdctl.py
           src/bin/cmdctl/run_b10-cmdctl.sh
           src/bin/cmdctl/unittest/cmdctl_test
           src/bin/xfrin/unittest/xfrin_test
           src/bin/xfrin/xfrin.py
           src/bin/xfrin/xfrin.pre
           src/bin/xfrin/run_b10-xfrin.sh
           src/bin/bind10/bind10.py
           src/bin/bind10/tests/bind10_test
           src/bin/bind10/run_bind10.sh
           src/bin/bindctl/run_bindctl.sh
           src/bin/bindctl/bindctl-source.py
           src/bin/bindctl/unittest/bindctl_test
           src/bin/loadzone/run_loadzone.sh
           src/bin/loadzone/b10-loadzone.py
           src/bin/usermgr/run_b10-cmdctl-usermgr.sh
           src/bin/usermgr/b10-cmdctl-usermgr.py
           src/bin/msgq/msgq.py
           src/bin/msgq/msgq_test
           src/bin/msgq/run_msgq.sh
           src/bin/auth/auth.pre
           src/bin/auth/spec_config.h
           src/lib/config/tests/data_def_unittests_config.h
           src/lib/python/isc/config/tests/config_test
           src/lib/python/isc/cc/tests/cc_test
           src/lib/dns/gen-rdatacode.py
           src/lib/dns/tests/testdata/gen-wiredata.py
          ], [
           chmod +x src/bin/cmdctl/run_b10-cmdctl.sh
           chmod +x src/bin/xfrin/run_b10-xfrin.sh
           chmod +x src/bin/bind10/run_bind10.sh
           chmod +x src/bin/cmdctl/unittest/cmdctl_test
           chmod +x src/bin/xfrin/unittest/xfrin_test
           chmod +x src/bin/bindctl/unittest/bindctl_test
           chmod +x src/bin/bindctl/run_bindctl.sh
           chmod +x src/bin/loadzone/run_loadzone.sh
           chmod +x src/bin/usermgr/run_b10-cmdctl-usermgr.sh
           chmod +x src/bin/msgq/run_msgq.sh
           chmod +x src/bin/msgq/msgq_test
           chmod +x src/lib/dns/gen-rdatacode.py
           chmod +x src/lib/dns/tests/testdata/gen-wiredata.py
          ])
AC_OUTPUT
