#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.59])
AC_INIT(bind, 10.0.0, bind10-bugs@isc.org)
AC_CONFIG_SRCDIR(README)
AM_INIT_AUTOMAKE
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
AC_PROG_RANLIB

m4_define([_AM_PYTHON_INTERPRETER_LIST], [python python3 python3.1])
AM_PATH_PYTHON([3.1])

# Checks for libraries.

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
		gtest_path="yes"
	fi
	if test "$lcov" != "yes"; then
		LCOV_PATHS=$lcov
	else
		LCOV_PATHS="/usr/bin/lcov /usr/local/bin/lcov"
	fi
	for f in $LCOV_PATHS; do
		if test -x "$f"; then
			USE_LCOV="yes"
			LCOV=$f
		fi
	done
	if test $USE_LCOV != "yes"; then
		AC_MSG_ERROR([Cannot find lcov in: $LCOV_PATHS])
	fi
	# is genhtml always in the same directory?
	GENHTML=`echo "$LCOV" | sed s/lcov$/genhtml/`
	if test ! -x $GENHTML; then
		AC_MSG_ERROR([genhtml not found, needed for lcov])
	fi
	# GCC specific?
	CPPFLAGS="$CPPFLAGS -fprofile-arcs -ftest-coverage"
	LIBS=" $LIBS -lgcov"
	AC_SUBST(CPPFLAGS)
	AC_SUBST(LIBS)
	AC_SUBST(LCOV)
	AC_SUBST(GENHTML)
fi
AC_SUBST(USE_LCOV)

#
# Check availablity of gtest, which will be used for unit tests.
#
if test "$gtest_path" != "no"
then
	if test "$gtest_path" != "yes"; then
		GTEST_PATHS=$gtest_path
	else
		GTEST_PATHS="/usr /usr/local"
	fi

	GTEST_FOUND="false"
	for dir in $GTEST_PATHS; do
		if test -f "$dir/include/gtest/gtest.h"; then
			GTEST_INCLUDES="-I$dir/include"
			GTEST_LDFLAGS="-L$dir/lib"
			GTEST_LDADD="-lgtest"
			GTEST_FOUND="true"
		fi
	done
	if test $GTEST_FOUND != "true"; then
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

# Checks for library functions.

AC_CONFIG_FILES([Makefile
                 src/Makefile
                 src/bin/Makefile
                 src/bin/bigtool/Makefile
                 src/bin/bind10/Makefile
                 src/bin/host/Makefile
                 src/bin/msgq/Makefile
                 src/bin/parkinglot/Makefile
                 src/lib/Makefile
                 src/lib/cc/Makefile
                 src/lib/cc/cpp/Makefile
                 src/lib/dns/Makefile
               ])
AC_OUTPUT([src/bin/bind-cfgd/bind-cfgd
           src/bin/bigtool/run_bigtool
           src/bin/bind10/bind10
           src/bin/bind10/bind10_test
	   src/bin/msgq/msgq
	   src/bin/msgq/msgq_test
           src/bin/parkinglot/config.h
          ], [
           chmod +x src/bin/bind-cfgd/bind-cfgd
           chmod +x src/bin/bigtool/run_bigtool
           chmod +x src/bin/bind10/bind10
           chmod +x src/bin/msgq/msgq
           chmod +x src/bin/msgq/msgq_test
          ])
AC_OUTPUT
