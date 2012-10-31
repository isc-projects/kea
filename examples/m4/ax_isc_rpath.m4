dnl @synopsis AX_ISC_RPATH
dnl
dnl @summary figure out whether and which "rpath" linker option is available
dnl
dnl This macro checks if the linker supports an option to embed a path
dnl to a runtime library (often installed in an uncommon place), such as
dnl gcc's -rpath option.  If found, it sets the ISC_RPATH_FLAG variable to
dnl the found option flag.  The main configure.ac can use it as follows:
dnl if test "x$ISC_RPATH_FLAG" != "x"; then
dnl     LDFLAGS="$LDFLAGS ${ISC_RPATH_FLAG}/usr/local/lib/some_library"
dnl fi

AC_DEFUN([AX_ISC_RPATH], [

# check -R and -Wl,-R rather than gcc specific -rpath to be as portable
# as possible.
AC_MSG_CHECKING([whether -R flag is available in linker])
LDFLAGS_SAVED="$LDFLAGS"
LDFLAGS="$LDFLAGS -R/usr/lib"
AC_TRY_LINK([],[],
    [ AC_MSG_RESULT(yes)
        ISC_RPATH_FLAG=-R
    ],[ AC_MSG_RESULT(no)
        AC_MSG_CHECKING([whether -Wl,-R flag is available in linker])
        LDFLAGS="$LDFLAGS_SAVED -Wl,-R"
        AC_TRY_LINK([], [],
            [ AC_MSG_RESULT(yes)
                ISC_RPATH_FLAG=-Wl,-R
            ],[ AC_MSG_RESULT(no) ])
    ])
LDFLAGS=$LDFLAGS_SAVED

])dnl AX_ISC_RPATH
