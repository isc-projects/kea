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

# We'll tweak both CXXFLAGS and CCFLAGS so this function will work whichever
# language is used in the main script.  Note also that it's not LDFLAGS;
# technically this is a linker flag, but we've noticed $LDFLAGS can be placed
# where the compiler could interpret it as a compiler option, leading to
# subtle failure mode.  So, in the check below using the compiler flag is
# safer (in the actual Makefiles the flag should be set in LDFLAGS).
CXXFLAGS_SAVED="$CXXFLAGS"
CXXFLAGS="$CXXFLAGS -Wl,-R/usr/lib"
CCFLAGS_SAVED="$CCFLAGS"
CCFLAGS="$CCFLAGS -Wl,-R/usr/lib"

# check -Wl,-R and -R rather than gcc specific -rpath to be as portable
# as possible.  -Wl,-R seems to be safer, so we try it first.  In some cases
# -R is not actually recognized but AC_TRY_LINK doesn't fail due to that.
AC_MSG_CHECKING([whether -Wl,-R flag is available in linker])
AC_TRY_LINK([],[],
    [ AC_MSG_RESULT(yes)
        ISC_RPATH_FLAG=-Wl,-R
    ],[ AC_MSG_RESULT(no)
        AC_MSG_CHECKING([whether -R flag is available in linker])
	CXXFLAGS="$CXXFLAGS_SAVED -R"
	CCFLAGS="$CCFLAGS_SAVED -R"
        AC_TRY_LINK([], [],
            [ AC_MSG_RESULT([yes; note that -R is more sensitive about the position in option arguments])
                ISC_RPATH_FLAG=-R
            ],[ AC_MSG_RESULT(no) ])
    ])

CXXFLAGS=$CXXFLAGS_SAVED
CCFLAGS=$CCFLAGS_SAVED

])dnl AX_ISC_RPATH
