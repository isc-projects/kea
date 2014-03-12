dnl @synopsis AX_PYTHON_SQLITE3
dnl
dnl Test for the Python sqlite3 module used by BIND10's datasource
dnl

AC_DEFUN([AX_PYTHON_SQLITE3], [

# Check for the python sqlite3 module
AC_MSG_CHECKING(for python sqlite3 module)
if "$PYTHON" -c 'import sqlite3' 2>/dev/null ; then
    AC_MSG_RESULT(ok)
else
    AC_MSG_RESULT(missing)

    if test "x$want_dns" = "xyes" ; then
        AC_MSG_ERROR([Missing sqlite3 python module that is required by DNS components.])
    fi
fi

])dnl AX_PYTHON_SQLITE3
