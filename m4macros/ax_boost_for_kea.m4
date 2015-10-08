dnl @synopsis AX_BOOST_FOR_KEA
dnl
dnl Test for the Boost C++ header files intended to be used within Kea
dnl
dnl If no path to the installed boost header files is given via the
dnl --with-boost-include option,  the macro searchs under
dnl /usr/local /usr/pkg /opt /opt/local directories.
dnl If it cannot detect any workable path for Boost, this macro treats it
dnl as a fatal error (so it cannot be called if the availability of Boost
dnl is optional).
dnl
dnl This macro also tries to identify some known portability issues, and
dnl sets corresponding variables so the caller can react to (or ignore,
dnl depending on other configuration) specific issues appropriately.
dnl
dnl Boost.Asio depends on Boost.System which can be header only with
dnl versions >= 1.56. On older and perhaps some recent versions
dnl libboost_system is required.
dnl --with-boost-libs can help forcing link with a Boost library,
dnl e.g., --with-boost-libs=-lboost_system
dnl
dnl This macro calls:
dnl
dnl   AC_SUBST(BOOST_INCLUDES)
dnl   AC_SUBST(BOOST_LIBS)
dnl   AC_SUBST(DISTCHECK_BOOST_CONFIGURE_FLAG)
dnl
dnl And possibly sets:
dnl   CPPFLAGS_BOOST_THREADCONF should be added to CPPFLAGS by caller
dnl   BOOST_OFFSET_PTR_WOULDFAIL set to "yes" if offset_ptr would cause build
dnl                              error; otherwise set to "no"
dnl   BOOST_NUMERIC_CAST_WOULDFAIL set to "yes" if numeric_cast would cause
dnl                                build error; otherwise set to "no"
dnl   BOOST_STATIC_ASSERT_WOULDFAIL set to "yes" if BOOST_STATIC_ASSERT would
dnl                                 cause build error; otherwise set to "no"

AC_DEFUN([AX_BOOST_FOR_KEA], [
AC_LANG_SAVE
AC_LANG([C++])

DISTCHECK_BOOST_CONFIGURE_FLAG=

# No library by default (and as goal)
BOOST_LIBS=
BOOST_LIB_DIR=
boost_lib_path=

#
# Configure Boost header path
#
# If explicitly specified, use it.
AC_ARG_WITH([boost-include],
  AC_HELP_STRING([--with-boost-include=PATH],
    [specify exact directory for Boost headers]),
    [boost_include_path="$withval"])
# If not specified, try some common paths.
if test -z "$with_boost_include"; then
	boostdirs="/usr/local /usr/pkg /opt /opt/local"
	for d in $boostdirs
	do
		if test -f $d/include/boost/shared_ptr.hpp; then
			boost_include_path=$d/include
			boost_lib_path=$d/lib
			break
		fi
	done
else
	DISTCHECK_BOOST_CONFIGURE_FLAG="--with-boost-include=${boost_include_path}"
fi

# Check the path with some specific headers.
CPPFLAGS_SAVED="$CPPFLAGS"
if test "${boost_include_path}" ; then
	BOOST_INCLUDES="-I${boost_include_path}"
	CPPFLAGS="$CPPFLAGS $BOOST_INCLUDES"
fi
AC_CHECK_HEADERS([boost/shared_ptr.hpp boost/foreach.hpp boost/interprocess/sync/interprocess_upgradable_mutex.hpp boost/date_time/posix_time/posix_time_types.hpp boost/bind.hpp boost/function.hpp boost/asio.hpp boost/asio/ip/address.hpp boost/system/error_code.hpp],,
  AC_MSG_ERROR([Missing required header files.]))

# clang can cause false positives with -Werror without -Qunused-arguments.
# it can be triggered if used with ccache.
AC_CHECK_DECL([__clang__], [CLANG_CXXFLAGS="-Qunused-arguments"], [])

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

# Boost offset_ptr is known to not compile on some platforms, depending on
# boost version, its local configuration, and compiler.  Detect it.
CXXFLAGS_SAVED="$CXXFLAGS"
CXXFLAGS="$CXXFLAGS $CLANG_CXXFLAGS -Werror"
AC_MSG_CHECKING([Boost offset_ptr compiles])
AC_TRY_COMPILE([
#include <boost/interprocess/offset_ptr.hpp>
],,
[AC_MSG_RESULT(yes)
 BOOST_OFFSET_PTR_WOULDFAIL=no],
[AC_MSG_RESULT(no)
 BOOST_OFFSET_PTR_WOULDFAIL=yes])
CXXFLAGS="$CXXFLAGS_SAVED"

# Detect build failure case known to happen with Boost installed via
# FreeBSD ports
if test "X$GXX" = "Xyes"; then
   CXXFLAGS_SAVED="$CXXFLAGS"
   CXXFLAGS="$CXXFLAGS $CLANG_CXXFLAGS -Werror"

   AC_MSG_CHECKING([Boost numeric_cast compiles with -Werror])
   AC_TRY_COMPILE([
   #include <boost/numeric/conversion/cast.hpp>
   ],[
   return (boost::numeric_cast<short>(0));
   ],[AC_MSG_RESULT(yes)
      BOOST_NUMERIC_CAST_WOULDFAIL=no],
   [AC_MSG_RESULT(no)
    BOOST_NUMERIC_CAST_WOULDFAIL=yes])

   CXXFLAGS="$CXXFLAGS_SAVED"
else
   # This doesn't matter for non-g++
   BOOST_NUMERIC_CAST_WOULDFAIL=no
fi

# BOOST_STATIC_ASSERT in versions below Boost 1.54.0 is known to result
# in warnings with GCC 4.8.  Detect it.
AC_MSG_CHECKING([BOOST_STATIC_ASSERT compiles])
AC_TRY_COMPILE([
#include <boost/static_assert.hpp>
void testfn(void) { BOOST_STATIC_ASSERT(true); }
],,
[AC_MSG_RESULT(yes)
 BOOST_STATIC_ASSERT_WOULDFAIL=no],
[AC_MSG_RESULT(no)
 BOOST_STATIC_ASSERT_WOULDFAIL=yes])

# Get libs when explicitly configured
AC_ARG_WITH([boost-libs],
  AC_HELP_STRING([--with-boost-libs=SPEC],
    [specify Boost libraries to link with, e.g., '-lboost_system']),
    [BOOST_LIBS="$withval"
     DISTCHECK_BOOST_CONFIGURE_FLAG="$DISTCHECK_BOOST_CONFIGURE_FLAG --with-boost-libs=$withval"])

# Get lib dir when explicitly configured
AC_ARG_WITH([boost-lib-dir],
  AC_HELP_STRING([--with-boost-lib-dir=PATH],
    [specify directory where to find Boost libraries]),
    [BOOST_LIB_DIR="$withval"
     DISTCHECK_BOOST_CONFIGURE_FLAG="$DISTCHECK_BOOST_CONFIGURE_FLAG --with-boot-lib-dir=$withval"])

# BOOST_ERROR_CODE_HEADER_ONLY in versions below Boost 1.56.0 can fail
# to find the error_code.cpp file.
if test "x${BOOST_LIBS}" = "x"; then
   AC_MSG_CHECKING([BOOST_ERROR_CODE_HEADER_ONLY works])
   CXXFLAGS_SAVED2="$CPPFLAGS"
   CPPFLAGS="$CPPFLAGS -DBOOST_ERROR_CODE_HEADER_ONLY"
   CPPFLAGS="$CPPFLAGS -DBOOST_SYSTEM_NO_DEPRECATED"

   AC_TRY_COMPILE([
   #include <boost/system/error_code.hpp>
   ],,
   [AC_MSG_RESULT(yes)],
   [AC_MSG_RESULT(no)
    AC_MSG_WARN([The Boost system library is required.])
    BOOST_LIBS="-lboost_system"
    if test "x${BOOST_LIB_DIR}" = "x"; then
       BOOST_LIB_DIR="$boost_lib_path"
    fi])

   CPPFLAGS="$CXXFLAGS_SAVED2"
fi

# A Boost library is used.
if test "x${BOOST_LIBS}" != "x"; then
   if test "x${BOOST_LIB_DIR}" != "x"; then
      BOOST_LIBS="-L$BOOST_LIB_DIR $BOOST_LIBS"
   fi
   LIBS_SAVED="$LIBS"
   LIBS="$BOOST_LIBS $LIBS"

   AC_LINK_IFELSE(
     [AC_LANG_PROGRAM([#include <boost/system/error_code.hpp>],
                      [boost::system::error_code ec;])],
     [AC_MSG_RESULT([checking for Boost system library... yes])],
     [AC_MSG_RESULT([checking for Boost system library... no])
      AC_MSG_ERROR([Linking with ${BOOST_LIBS} is not enough: please make sure libboost_system is installed])])

    LIBS="$LIBS_SAVED"
fi

CXXFLAGS="$CXXFLAGS_SAVED"

AC_SUBST(BOOST_INCLUDES)
AC_SUBST(BOOST_LIBS)
AC_SUBST(DISTCHECK_BOOST_CONFIGURE_FLAG)

dnl Determine the Boost version, used mainly for config.report.
AC_MSG_CHECKING([Boost version])
cat > conftest.cpp << EOF
#include <boost/version.hpp>
AUTOCONF_BOOST_LIB_VERSION=BOOST_LIB_VERSION
EOF

BOOST_VERSION=`$CPP $CPPFLAGS conftest.cpp | grep '^AUTOCONF_BOOST_LIB_VERSION=' | $SED -e 's/^AUTOCONF_BOOST_LIB_VERSION=//' -e 's/_/./g' -e 's/"//g' 2> /dev/null`
if test -z "$BOOST_VERSION"; then
  BOOST_VERSION="unknown"
fi
$RM -f conftest.cpp
AC_MSG_RESULT([$BOOST_VERSION])

CPPFLAGS="$CPPFLAGS_SAVED"
AC_LANG_RESTORE
])dnl AX_BOOST_FOR_KEA
