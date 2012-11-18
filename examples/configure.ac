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

# Checks for BIND 10 headers and libraries
AX_ISC_BIND10

# We use -R, -rpath etc so the resulting program will be more likekly to
# "just work" by default.  Embedding a specific library path is a controversial
# practice, though; if you don't like it you can remove the following setting.
if test "x$BIND10_RPATH" != "x"; then
   LDFLAGS="$LDFLAGS $BIND10_RPATH"
fi

# For the example host program, we require some socket API library
# and the BIND 10 DNS library.

# In practice, these are specific to Solaris, but wouldn't do any harm for
# others except for the checking overhead.
AC_SEARCH_LIBS(inet_pton, [nsl])
AC_SEARCH_LIBS(recvfrom, [socket])

if test "x$BIND10_DNS_LIB" = "x"; then
   AC_MSG_ERROR([unable to find BIND 10 DNS library needed to build 'host'])
fi

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL

AC_CONFIG_FILES([Makefile
                 host/Makefile])

AC_OUTPUT
