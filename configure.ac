#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.59])
AC_INIT(bind10, 10.0.0, bind10-bugs@isc.org)
AC_CONFIG_SRCDIR(README)
AM_INIT_AUTOMAKE
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
AC_PROG_RANLIB

AC_PROG_LIBTOOL

m4_define([_AM_PYTHON_INTERPRETER_LIST], [python python3 python3.1])
AM_PATH_PYTHON([3.1])

# default compiler warning settings
if test "X$GCC" = "Xyes"; then
CXXFLAGS="-g -Wall -Wwrite-strings -Woverloaded-virtual -Wno-sign-compare"
fi

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

PKG_CHECK_MODULES(SQLITE, sqlite3)

# Checks for library functions.

AC_CONFIG_FILES([Makefile
                 src/Makefile
                 src/bin/Makefile
                 src/bin/bind10/Makefile
                 src/bin/cmdctl/Makefile
                 src/bin/bindctl/Makefile
                 src/bin/cfgmgr/Makefile
                 src/bin/host/Makefile
                 src/bin/msgq/Makefile
                 src/bin/auth/Makefile
                 src/lib/Makefile
                 src/lib/cc/Makefile
                 src/lib/cc/cpp/Makefile
                 src/lib/cc/python/Makefile
                 src/lib/cc/python/isc/Makefile
                 src/lib/cc/python/isc/cc/Makefile
                 src/lib/cc/python/isc/Util/Makefile
                 src/lib/config/Makefile
                 src/lib/config/cpp/Makefile
                 src/lib/config/python/Makefile
                 src/lib/config/python/isc/Makefile
                 src/lib/config/python/isc/config/Makefile
                 src/lib/dns/Makefile
                 src/lib/dns/cpp/Makefile
                 src/lib/dns/cpp/tests/Makefile
                 src/lib/exceptions/cpp/Makefile
                 src/lib/exceptions/Makefile
                 src/lib/auth/Makefile
                 src/lib/auth/cpp/Makefile
               ])
AC_OUTPUT([src/bin/cfgmgr/b10-cfgmgr.py
           src/bin/cmdctl/cmdctl.py
           src/bin/cmdctl/run_b10-cmdctl.sh
           src/bin/cmdctl/unittest/cmdctl_test
           src/bin/bind10/bind10.py
           src/bin/bind10/bind10_test
           src/bin/bind10/run_bind10.sh
           src/bin/bindctl/bindctl
           src/bin/bindctl/unittest/bindctl_test
           src/bin/msgq/msgq.py
           src/bin/msgq/msgq_test
           src/bin/msgq/run_msgq.sh
           src/bin/auth/config.h
           src/lib/config/cpp/data_def_unittests_config.h
           src/lib/config/python/isc/config/unittests/config_test
           src/lib/dns/cpp/gen-rdatacode.py
          ], [
           chmod +x src/bin/cfgmgr/run_b10-cfgmgr.sh
           chmod +x src/bin/cmdctl/run_b10-cmdctl.sh
           chmod +x src/bin/bind10/run_bind10.sh
           chmod +x src/bin/cmdctl/unittest/cmdctl_test
           chmod +x src/bin/bindctl/unittest/bindctl_test
           chmod +x src/bin/bindctl/bindctl
           chmod +x src/bin/msgq/run_msgq.sh
           chmod +x src/bin/msgq/msgq_test
	   chmod +x src/lib/dns/cpp/gen-rdatacode.py
          ])
AC_OUTPUT
