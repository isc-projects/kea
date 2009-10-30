#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.61])
AC_INIT(bind, 10.0.0, bind10-bugs@isc.org)
AC_CONFIG_SRCDIR(README)
AM_INIT_AUTOMAKE
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
AC_PROG_RANLIB

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

#
# Check availablity of gtest, which might be used for unit tests.
#
AC_ARG_WITH(gtest,
[  --with-gtest=PATH       specify a path to Gtest header files (PATH/include) and library (PATH/lib)],
    gtest_path="$withval", gtest_path="no")
if test "$gtest_path" != "no"
then
	GTEST_INCLUDES="-I${gtest_path}/include"
	GTEST_LDFLAGS="-L${gtest_path}/lib"
	GTEST_LDADD="-lgtest"
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
                 src/bin/host/Makefile
                 src/bin/parkinglot/Makefile
                 src/lib/Makefile
                 src/lib/cc/Makefile
                 src/lib/cc/cpp/Makefile
                 src/lib/dns/Makefile
               ])
AC_OUTPUT([src/bin/bind-cfgd/bind-cfgd])
AC_OUTPUT
