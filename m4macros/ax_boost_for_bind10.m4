dnl @synopsis AX_BOOST_FOR_BIND10
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

AC_DEFUN([AX_BOOST_FOR_BIND10], [
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
AC_MSG_CHECKING([Boost offset_ptr compiles])
AC_TRY_COMPILE([
#include <boost/interprocess/offset_ptr.hpp>
],,
[AC_MSG_RESULT(yes)
 BOOST_OFFSET_PTR_WOULDFAIL=no],
[AC_MSG_RESULT(no)
 BOOST_OFFSET_PTR_WOULDFAIL=yes])

# Detect build failure case known to happen with Boost installed via
# FreeBSD ports
if test "X$GXX" = "Xyes"; then
   CXXFLAGS_SAVED="$CXXFLAGS"
   CXXFLAGS="$CXXFLAGS -Werror"

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

   CXXFLAGS="$CXXFLAGS_SAVED"
fi

# Boost interprocess::managed_mapped_file is highly system dependent and
# can cause many portability issues.  We are going to check if it could
# compile at all, possibly with being lenient about compiler warnings.
BOOST_MAPPED_FILE_WOULDFAIL=yes
BOOST_MAPPED_FILE_CXXFLAG=
CXXFLAGS_SAVED="$CXXFLAGS"
try_flags="no"
if test "X$GXX" = "Xyes"; then
  CXXFLAGS="$CXXFLAGS -Werror"
  try_flags="$try_flags -Wno-error"
fi
# clang can cause false positives with -Werror without -Qunused-arguments
AC_CHECK_DECL([__clang__], [CXXFLAGS="$CXXFLAGS -Qunused-arguments"], [])

AC_MSG_CHECKING([Boost managed_mapped_file compiles])
CXXFLAGS_SAVED2="$CXXFLAGS"
for flag in $try_flags; do
  if test "$flag" != no; then
    BOOST_MAPPED_FILE_CXXFLAG="$flag"
  fi
  CXXFLAGS="$CXXFLAGS $BOOST_MAPPED_FILE_CXXFLAG"
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

CXXFLAGS="$CXXFLAGS_SAVED"

AC_SUBST(BOOST_INCLUDES)

CPPFLAGS="$CPPFLAGS_SAVED"
AC_LANG_RESTORE
])dnl AX_BOOST_FOR_BIND10
