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
# Check availablity of CppUnit, which will be used for unit tests.
#
AC_ARG_WITH(cppunit,
[  --with-cppunit=PATH     specify a path to CppUnit header files (PATH/include) and library (PATH/lib)],
    cppunit_path="$withval", cppunit_path="no")
if test "$cppunit_path" != "no"
then
	CPPUNIT_INCLUDES="-I${cppunit_path}/include"
	CPPUNIT_LDFLAGS="-L${cppunit_path}/lib"
	CPPUNIT_LDADD="-lcppunit"
else
	CPPUNIT_INCLUDES=
	CPPUNIT_LDFLAGS=
	CPPUNIT_LDADD=
fi
AM_CONDITIONAL(HAVE_CPPUNIT, test $cppunit_path != "no")
AC_SUBST(CPPUNIT_INCLUDES)
AC_SUBST(CPPUNIT_LDFLAGS)
AC_SUBST(CPPUNIT_LDADD)

# Checks for library functions.

AC_CONFIG_FILES([Makefile
                 src/Makefile
                 src/lib/Makefile
                 src/lib/dns/Makefile
                 src/lib/dns/cpp/Makefile])
AC_OUTPUT
