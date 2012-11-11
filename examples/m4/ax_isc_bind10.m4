dnl @synopsis AX_ISC_BIND10
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
dnl   AC_SUBST(BIND10_COMMON_LIB)
dnl   AC_SUBST(BIND10_DNS_LIB)
dnl
dnl If this macro finds CPPFLAGS, LDFLAGS or COMMON_LIB unavailable, it treats
dnl that as a fatal error.
dnl Checks for other BIND 10 module libraries are option, as not all
dnl applications need all libraries.  The main configure.ac can handle any
dnl missing library as fatal by checking whether the corresponding
dnl BIND10_xxx_LIB is defined.
dnl
dnl In addition, it sets the BIND10_RPATH variable to a usable linker option
dnl to embed the path to the BIND 10 library to the programs that are to be
dnl linked with the library.  If the developer wants to use the option,
dnl it can be used as follows:
dnl if test "x$BIND10_RPATH" != "x"; then
dnl     LDFLAGS="$LDFLAGS $BIND10_RPATH"
dnl fi

AC_DEFUN([AX_ISC_BIND10], [
AC_REQUIRE([AX_BOOST_INCLUDE])
AC_REQUIRE([AX_ISC_RPATH])
AC_LANG_SAVE
AC_LANG([C++])

# Check for BIND10 common headers

AC_ARG_WITH(bind10-include,
  AS_HELP_STRING([--with-bind10-include=PATH],
  [specify a path to BIND 10 header files]),
    bind10_inc_path="$withval", bind10_inc_path="no")
# If not specified, try some common paths.
if test "$bind10_inc_path" = "no"; then
   for d in /usr/local /usr/pkg /opt /opt/local
   do
	if test -f $d/include/util/buffer.h; then
	   bind10_inc_path=$d
	   break
	fi
   done
fi
CPPFLAGS_SAVED="$CPPFLAGS"
CPPFLAGS="$CPPFLAGS $BOOST_CPPFLAGS" # boost headers will be used in buffer.h
if test "${bind10_inc_path}" != "no"; then
   BIND10_CPPFLAGS="-I${bind10_inc_path}"
   CPPFLAGS="$CPPFLAGS $BIND10_CPPFLAGS"
fi
AC_CHECK_HEADERS([util/buffer.h],,
  AC_MSG_ERROR([Missing a commonly used BIND 10 header file]))
CPPFLAGS="$CPPFLAGS_SAVED"
AC_SUBST(BIND10_CPPFLAGS)

# Check for BIND10 libraries
CPPFLAGS_SAVED="$CPPFLAGS"
CPPFLAGS="$CPPFLAGS $BOOST_CPPFLAGS $BIND10_CPPFLAGS"

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
AC_MSG_CHECKING([for BIND 10 common library])
BIND10_COMMON_LIB="-lb10-util -lb10-exceptions"
LDFLAGS_SAVED="$LDFLAGS"
LDFLAGS_CHECK_COMMON="$LDFLAGS $BIND10_LDFLAGS"
LIBS_SAVED="$LIBS"
LIBS="$LIBS $BIND10_COMMON_LIB"
for d in $bind10_lib_dirs
do
  LDFLAGS="$LDFLAGS_CHECK_COMMON -L$d"
  AC_TRY_LINK([
#include <util/buffer.h>
],[
isc::util::OutputBuffer buffer(0);
], [BIND10_LDFLAGS="-L${d}"
    if test "x$ISC_RPATH_FLAG" != "x"; then
       BIND10_RPATH="${ISC_RPATH_FLAG}${d}"
    fi
    ])
  if test "x$BIND10_LDFLAGS" != "x"; then
     break
  fi
done
if test "x$BIND10_LDFLAGS" != "x"; then
  AC_MSG_RESULT(yes)
else
  AC_MSG_RESULT(no)
  AC_MSG_ERROR([unable to find required BIND 10 libraries])
fi

# restore LIBS once at this point
LIBS="$LIBS_SAVED"

AC_SUBST(BIND10_LDFLAGS)
AC_SUBST(BIND10_COMMON_LIB)

# Check per-module BIND 10 libraries

# DNS library
AC_MSG_CHECKING([for BIND 10 DNS library])
LIBS="$LIBS $BIND10_COMMON_LIB -lb10-dns++"
AC_TRY_LINK([
#include <dns/rrtype.h>
],[
isc::dns::RRType rrtype(1);
], [BIND10_DNS_LIB="-lb10-dns++"
    AC_MSG_RESULT(yes)],
   [AC_MSG_RESULT(no)])
LIBS="$LIBS_SAVED"
AC_SUBST(BIND10_DNS_LIB)

# Restore other flags
CPPFLAGS="$CPPFLAGS_SAVED"
LDFLAGS="$LDFLAGS_SAVED"

AC_LANG_RESTORE
])dnl AX_ISC_BIND10
