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
AM_CONDITIONAL(GCC, test "$GCC" = yes)
AC_PROG_RANLIB

AC_PROG_LIBTOOL

# Checks for libraries.

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_TYPE_SIZE_T

# default compiler warning settings
if test "X$GCC" = "Xyes"; then
CXXFLAGS="-g -Wall -Wwrite-strings -Woverloaded-virtual -Wno-sign-compare"
fi

# produce PIC unless we disable shared libraries. need this for python bindings.
if test $enable_shared != "no" -a "X$GCC" = "Xyes"; then
   CXXFLAGS="$CXXFLAGS -fPIC"
fi

#
# Check availablity of boost: 
#
AC_ARG_WITH(boost,
[  --with-boost=PATH       specify a path to the boost if it's not automatically found],
    boost_path="$withval", boost_path="no")
if test "$boost_path" != "no"
then
	BOOST_INCLUDES="-I$boost_path/include"
else
	BOOST_INCLUDES=
fi

AC_SUBST(BOOST_INCLUDES)

#
# Check availablity of gtest, which will be used for unit tests.
#
AC_ARG_WITH(gtest,
[  --with-gtest=PATH       specify a path to gtest header files (PATH/include) and library (PATH/lib)],
    gtest_path="$withval", gtest_path="no")
if test "$gtest_path" != "no"
then
	if test "$gtest_path" != "yes"
	then
		GTEST_INCLUDES="-I${gtest_path}/include"
		GTEST_LDFLAGS="-L${gtest_path}/lib"
		GTEST_LDADD="-lgtest"
	else
		# todo: check for default paths (/usr and /usr/local?)
		GTEST_INCLUDE="-I/usr/include"
		GTEST_LDFLAGS="-L/usr/lib"
		GTEST_LDADD="-lgtest"
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

AC_ARG_WITH(lcov,
[  --with-lcov[=PROGRAM]     enable gtest and coverage target using the specified lcov], lcov="$withval", lcov="no")

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
	CXXFLAGS="$CXXFLAGS -fprofile-arcs -ftest-coverage"
	LIBS=" $LIBS -lgcov"
fi

AC_SUBST(CXXFLAGS)
AC_SUBST(LIBS)

# Checks for library functions.

AC_CONFIG_FILES([Makefile
                 src/Makefile
                 src/lib/Makefile
                 src/lib/dns/Makefile
                 src/lib/dns/cpp/Makefile])
AC_OUTPUT
