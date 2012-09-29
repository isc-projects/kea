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

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL

AC_CONFIG_FILES([Makefile
                 host/Makefile])

AC_OUTPUT
