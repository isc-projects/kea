#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.64])
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

#
# Check availablity of gtest, which will be used for unit tests.
#
AC_ARG_WITH(gtest,
[  --with-gtest=PATH       specify a path to gtest header files (PATH/include) and library (PATH/lib)],
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
                 src/lib/Makefile
                 src/lib/dns/Makefile
                 src/lib/dns/cpp/Makefile])
AC_OUTPUT
