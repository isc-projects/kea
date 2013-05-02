dnl @synopsis AX_SQLITE3_FOR_BIND10
dnl
dnl Test for the sqlite3 library and program, intended to be used within
dnl BIND 10, and to test BIND 10.
dnl
dnl We use pkg-config to look for the sqlite3 library, so the sqlite3
dnl development package with the .pc file must be installed.
dnl
dnl This macro sets SQLITE_CFLAGS and SQLITE_LIBS. It also sets
dnl SQLITE3_PROGRAM to the path of the sqlite3 program, if it is found
dnl in PATH.

AC_DEFUN([AX_SQLITE3_FOR_BIND10], [

PKG_CHECK_MODULES(SQLITE, sqlite3 >= 3.3.9,
    have_sqlite="yes",
    have_sqlite="no (sqlite3 not detected)")

# Check for sqlite3 program
AC_PATH_PROG(SQLITE3_PROGRAM, sqlite3, no)
AM_CONDITIONAL(HAVE_SQLITE3_PROGRAM, test "x$SQLITE3_PROGRAM" != "xno")

# TODO: check for _sqlite3.py module

])dnl AX_SQLITE3_FOR_BIND10
