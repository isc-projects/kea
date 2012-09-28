#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.59])
AC_INIT(bind10-examples, 20120817, bind10-dev@isc.org)
AC_CONFIG_SRCDIR([README])
AM_INIT_AUTOMAKE
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CXX
AC_LANG([C++])

# Checks for libraries.

# Check for BIND10 libdns++ headers
AC_ARG_WITH(bind10-include,
  AC_HELP_STRING([--with-bind10-include=PATH],
  [specify a path to BIND 10 header files
   (PATH, often needs to be in a BIND 10 source such as
   <somewhere>/bind10/src/lib)]),
    bind10_inc_path="$withval", bind10_inc_path="no")
# If not specified, try some common paths.
if test "$bind10_inc_path" = "no"; then
	bind10dirs="/usr/local /usr/pkg /opt /opt/local"
	for d in $bind10dirs
	do
		if test -f $d/dns/rrtype.h; then
			bind10_inc_path=$d
			break
		fi
	done
fi
CPPFLAGS_SAVES="$CPPFLAGS"
if test "${bind10_inc_path}" ; then
	BIND10_INCLUDES="-I${bind10_inc_path}"
	CPPFLAGS="$CPPFLAGS $BIND10_INCLUDES"
fi
AC_CHECK_HEADERS([dns/rrtype.h],,
  AC_MSG_ERROR([Missing required BIND 10 header files.]))
CPPFLAGS="$CPPFLAGS_SAVES"
AC_SUBST(BIND10_INCLUDES)

# Check for BIND10 lib libraries
AC_ARG_WITH(bind10-lib,
  AC_HELP_STRING([--with-bind10-lib=PATH],
  [specify a path to BIND 10 library files (PATH)]),
    bind10_lib_path="$withval", bind10_lib_path="no")

if test bind10_lib_path != "no"; then
	BIND10_LDFLAGS="-L$bind10_lib_path"
fi
BIND10_LDADD="-lb10-dns++ -lb10-util -lb10-exceptions"

CPPFLAGS_SAVED="$CPPFLAGS"
CPPFLAGS="$CPPFLAGS $BIND10_INCLUDES"
LDFLAGS_SAVED="$LDFLAGS"
LDFLAGS="$LDFLAGS $BIND10_LDFLAGS"
LIBS_SAVED=$LIBS
LIBS="$LIBS $BIND10_LDADD"

AC_MSG_CHECKING([BIND 10 libraries])
AC_TRY_LINK([
#include <dns/rrtype.h>
],[
isc::dns::RRType rrtype(1);
],
[ AC_MSG_RESULT(yes)],
[ AC_MSG_RESULT(no)
  AC_MSG_ERROR(unable to find required BIND 10 libraries)])

CPPFLAGS="$CPPFLAGS_SAVED"
LDFLAGS="$LDFLAGS_SAVES"
LIBS="$LIBS_SAVES"

AC_SUBST(BIND10_LDFLAGS)
AC_SUBST(BIND10_LDADD)

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL

# Checks for library functions.
AC_CHECK_FUNCS([gettimeofday memset socket])

AC_CONFIG_FILES([Makefile
                 host/Makefile])

AC_OUTPUT
