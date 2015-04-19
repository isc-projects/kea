dnl @synopsis AX_ISC_VISIBILITY
dnl
dnl @summary optionally built shared object with -fvisibility=hidden
dnl
dnl When enabled this macro checks if the compiler 
dnl
dnl If you do not pass --enable-visibility to configure, C[XX]FLAGS stay
dnl unchanged.

AC_DEFUN([AX_ISC_VISIBILITY], [

AC_ARG_ENABLE(visibility,
    [AC_HELP_STRING([--enable-visibility], [Use the -fvisibility=hidden g++ flag])],
    visibility=$enableval, visibility=no)

SHLIB_CXXFLAGS=
if test x$visibility = xyes; then
    # Check if -fvisibility=hidden & co are accepted
    CXXFLAGS_SAVED="$CXXFLAGS"
    CXXFLAGS="$CXXFLAGS -fvisibility=hidden"

    AC_MSG_CHECKING([whether -fvisibility=hidden flag is available in compiler])
    AC_TRY_COMPILE(
        [#if defined (__GNUC__) && (__GNUC__ < 4 || (__GNUC__ == 4 && __GNUC_MINOR__ <= 1))
         # error too old
         #endif
         __attribute__((visibility("default"))) int x = 0;],
        [ return x;],
        [ AC_MSG_RESULT(yes)
          SHLIB_CXXFLAGS="-fvisibility=hidden"
          AC_DEFINE([HAVE_ATTRIBUTE_VISIBILITY], [1],
          [Define to 1 if __attribute__((visibility("default"))) works])
        ],[ AC_MSG_RESULT(no)])

    CXXFLAGS="$CXXFLAGS_SAVED"
fi

AC_SUBST(SHLIB_CXXFLAGS)

])dnl AX_ISC_VISIBILITY
