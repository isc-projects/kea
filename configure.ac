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

#
# Check availablity of boost
#
AC_ARG_WITH(boost,
[  --with-boost=PATH       specify a path to the boost if it's not automatically found],
    boost_path="$withval", boost_path="no")
if test "$boost_path" != "no"
then
	CPPFLAGS="$CPPFLAGS -I$boost_path"	
fi

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
                 src/lib/Makefile
                 src/lib/dns/Makefile
               ])
AC_OUTPUT([src/bin/bind-cfgd])
AC_OUTPUT
