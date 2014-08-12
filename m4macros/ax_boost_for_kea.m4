dnl @synopsis AX_BOOST_FOR_KEA
dnl
dnl Test for the Boost C++ header files intended to be used within BIND 10
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
dnl This macro calls:
dnl
dnl   AC_SUBST(BOOST_INCLUDES)
dnl
dnl And possibly sets:
dnl   CPPFLAGS_BOOST_THREADCONF should be added to CPPFLAGS by caller
dnl   BOOST_OFFSET_PTR_WOULDFAIL set to "yes" if offset_ptr would cause build
dnl                              error; otherwise set to "no"
dnl   BOOST_NUMERIC_CAST_WOULDFAIL set to "yes" if numeric_cast would cause
dnl                                build error; otherwise set to "no"
dnl   BOOST_MAPPED_FILE_WOULDFAIL set to "yes" if managed_mapped_file would
dnl                               cause build failure; otherwise set to "no"
dnl   BOOST_MAPPED_FILE_CXXFLAG set to the compiler flag that would need to
dnl                             compile managed_mapped_file (can be empty).
dnl                             It is of no use if "WOULDFAIL" is yes.
dnl   BOOST_STATIC_ASSERT_WOULDFAIL set to "yes" if BOOST_STATIC_ASSERT would
dnl                                 cause build error; otherwise set to "no"

dnl   BOOST_OFFSET_PTR_OLD set to "yes" if the version of boost is older than
dnl                        1.48. Older versions of boost have a bug which
dnl                        causes segfaults in offset_ptr implementation when
dnl                        compiled by GCC with optimisations enabled.
dnl                        See ticket no. 3025 for details.

AC_DEFUN([AX_BOOST_FOR_KEA], [
AC_LANG_SAVE
AC_LANG([C++])

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
			break
		fi
	done
fi

# Check the path with some specific headers.
CPPFLAGS_SAVED="$CPPFLAGS"
if test "${boost_include_path}" ; then
	BOOST_INCLUDES="-I${boost_include_path}"
	CPPFLAGS="$CPPFLAGS $BOOST_INCLUDES"
fi
AC_CHECK_HEADERS([boost/shared_ptr.hpp boost/foreach.hpp boost/interprocess/sync/interprocess_upgradable_mutex.hpp boost/date_time/posix_time/posix_time_types.hpp boost/bind.hpp boost/function.hpp],,
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

   AC_MSG_CHECKING([Boost rbtree is old])
   AC_TRY_COMPILE([
   #include <boost/version.hpp>
   #if BOOST_VERSION < 104800
   #error Too old
   #endif
   ],,[AC_MSG_RESULT(no)
       BOOST_OFFSET_PTR_OLD=no
   ],[AC_MSG_RESULT(yes)
      BOOST_OFFSET_PTR_OLD=yes])
else
   # This doesn't matter for non-g++
   BOOST_NUMERIC_CAST_WOULDFAIL=no
   BOOST_OFFSET_PTR_OLD=no
fi

# Boost interprocess::managed_mapped_file is highly system dependent and
# can cause many portability issues.  We are going to check if it could
# compile at all, possibly with being lenient about compiler warnings.
BOOST_MAPPED_FILE_WOULDFAIL=yes
BOOST_MAPPED_FILE_CXXFLAG=
CXXFLAGS_SAVED="$CXXFLAGS"
try_flags="no"
if test "X$GXX" = "Xyes"; then
  CXXFLAGS="$CXXFLAGS $CLANG_CXXFLAGS -Wall -Wextra -Werror"
  try_flags="$try_flags -Wno-error"
fi

AC_MSG_CHECKING([Boost managed_mapped_file compiles])
CXXFLAGS_SAVED2="$CXXFLAGS"
for flag in $try_flags; do
  if test "$flag" != no; then
    BOOST_MAPPED_FILE_CXXFLAG="$flag"
  fi
  CXXFLAGS="$CXXFLAGS $CLANG_CXXFLAGS $BOOST_MAPPED_FILE_CXXFLAG"
  AC_TRY_COMPILE([
  #include <boost/interprocess/managed_mapped_file.hpp>
  ],[
  return (boost::interprocess::managed_mapped_file().all_memory_deallocated());
  ],[AC_MSG_RESULT([yes, with $flag flag])
     BOOST_MAPPED_FILE_WOULDFAIL=no
     break
  ],[])

  CXXFLAGS="$CXXFLAGS_SAVED2"
done

if test $BOOST_MAPPED_FILE_WOULDFAIL = yes; then
  AC_MSG_RESULT(no)
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

CXXFLAGS="$CXXFLAGS_SAVED"

AC_SUBST(BOOST_INCLUDES)

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
