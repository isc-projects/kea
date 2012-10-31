dnl @synopsis AX_BOOST_INCLUDE
dnl
dnl Test for the Boost C++ header files
dnl
dnl If no path to the installed boost header files is given via the
dnl --with-boost-include option,  the macro searchs under
dnl /usr/local /usr/pkg /opt /opt/local directories.
dnl
dnl This macro calls:
dnl
dnl   AC_SUBST(BOOST_CPPFLAGS)
dnl

AC_DEFUN([AX_BOOST_INCLUDE], [
AC_LANG_SAVE
AC_LANG([C++])

#
# Configure Boost header path
#
# If explicitly specified, use it.
AC_ARG_WITH([boost-include],
  AS_HELP_STRING([--with-boost-include=PATH],
    [specify exact directory for Boost headers]),
    [boost_include_path="$withval"])
# If not specified, try some common paths.
if test -z "$with_boost_include"; then
	boostdirs="/usr/local /usr/pkg /opt /opt/local"
	for d in $boostdirs
	do
		if test -f $d/include/boost/shared_ptr.hpp; then
			boost_include_path=$d/include
			break
		fi
	done
fi
CPPFLAGS_SAVED="$CPPFLAGS"
if test "${boost_include_path}" ; then
	BOOST_CPPFLAGS="-I${boost_include_path}"
	CPPFLAGS="$CPPFLAGS $BOOST_CPPFLAGS"
fi
# Make sure some commonly used headers are available
AC_CHECK_HEADERS([boost/shared_ptr.hpp boost/bind.hpp boost/function.hpp],,
  AC_MSG_ERROR([Missing required Boost header files.]))

# Detect whether Boost tries to use threads by default, and, if not,
# make it sure explicitly.  In some systems the automatic detection
# may depend on preceding header files, and if inconsistency happens
# it could lead to a critical disruption.
AC_MSG_CHECKING([whether Boost tries to use threads])
AC_TRY_COMPILE([
#include <boost/config.hpp>
#ifdef BOOST_HAS_THREADS
#error "boost will use threads"
#endif],,
[AC_MSG_RESULT(no)
 CPPFLAGS_BOOST_THREADCONF="-DBOOST_DISABLE_THREADS=1"],
[AC_MSG_RESULT(yes)])

CPPFLAGS="$CPPFLAGS_SAVED $CPPFLAGS_BOOST_THREADCONF"
AC_SUBST(BOOST_CPPFLAGS)

AC_LANG_RESTORE
])dnl AX_BOOST_INCLUDE
