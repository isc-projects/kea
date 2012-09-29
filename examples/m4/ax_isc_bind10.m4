dnl @synopsis AX_BIND10
dnl
dnl @summary figure out how to build C++ programs using ISC BIND 10 libraries
dnl
dnl If no path to the installed BIND 10 header files or libraries is given
dnl via the --with-bind10-include  or --with-bind10-lib option, the macro
dnl searchs under /usr/local/{include, lib}, /usr/pkg/{include, lib},
dnl /opt/{include, lib}, /opt/local/{include, lib} directories, respectively.
dnl
dnl This macro calls:
dnl
dnl   AC_SUBST(BIND10_CPPFLAGS)
dnl   AC_SUBST(BIND10_LDFLAGS)
dnl   AC_SUBST(BIND10_DNS_LIB)
dnl


AC_DEFUN([AX_ISC_BIND10], [
AC_REQUIRE([AX_BOOST_INCLUDE])
AC_LANG_SAVE
AC_LANG([C++])

AX_BOOST_INCLUDE

# Check for BIND10 libdns++ headers

AC_ARG_WITH(bind10-include,
  AS_HELP_STRING([--with-bind10-include=PATH],
  [specify a path to BIND 10 header files]),
    bind10_inc_path="$withval", bind10_inc_path="no")
# If not specified, try some common paths.
if test "$bind10_inc_path" = "no"; then
   for d in /usr/local /usr/pkg /opt /opt/local
   do
	if test -f $d/include/dns/rrtype.h; then
	   bind10_inc_path=$d
	   break
	fi
   done
fi
CPPFLAGS_SAVES="$CPPFLAGS"
if test "${bind10_inc_path}" ; then
   BIND10_CPPFLAGS="-I${bind10_inc_path}"
   CPPFLAGS="$CPPFLAGS $BIND10_CPPFLAGS"
fi
AC_CHECK_HEADERS([dns/rrtype.h],,
  AC_MSG_ERROR([Missing required BIND 10 header files.]))
CPPFLAGS="$CPPFLAGS_SAVES"
AC_SUBST(BIND10_CPPFLAGS)

# Check for BIND10 libraries
CPPFLAGS_SAVED="$CPPFLAGS"
CPPFLAGS="$CPPFLAGS $BIND10_CPPFLAGS"

AC_ARG_WITH(bind10-lib,
  AS_HELP_STRING([--with-bind10-lib=PATH],
  [specify a path to BIND 10 library files]),
    bind10_lib_path="$withval", bind10_lib_path="no")
if test $bind10_lib_path != "no"; then
   bind10_lib_dirs=$bind10_lib_path
else
   # If not specified, try some common paths.
   bind10_lib_dirs="/usr/local/lib /usr/pkg/lib /opt/lib /opt/local/lib"
fi

# make sure we have buildable libraries
AC_MSG_CHECKING([BIND 10 libraries])
BIND10_DNS_LIB="-lb10-dns++ -lb10-util -lb10-exceptions"
LDFLAGS="$LDFLAGS $BIND10_LDFLAGS"
LIBS="$LIBS $BIND10_DNS_LIB"
for d in $bind10_lib_dirs
do
  LDFLAGS_SAVED="$LDFLAGS"
  LDFLAGS="$LDFLAGS -L$d"
  AC_TRY_LINK([
#include <dns/rrtype.h>
],[
isc::dns::RRType rrtype(1);
], [BIND10_LDFLAGS="-L${d}"])
  if test "x$BIND10_LDFLAGS" != "x"; then
     break
  fi
  LDFLAGS="$LDFLAGS_SAVED"
done
if test "x$BIND10_LDFLAGS" != "x"; then
  AC_MSG_RESULT(yes)
else
  AC_MSG_RESULT(no)
  AC_MSG_ERROR(unable to find required BIND 10 libraries)
fi

CPPFLAGS="$CPPFLAGS_SAVED"
LDFLAGS="$LDFLAGS_SAVES"
LIBS="$LIBS_SAVES"

AC_SUBST(BIND10_LDFLAGS)
AC_SUBST(BIND10_DNS_LIB)

AC_LANG_RESTORE
])dnl AX_ISC_BIND10
