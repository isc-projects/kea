#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])

# For released versions, this is in x.y.z format.
# For GIT versions, this is x.y.z-git, where x.y.z denotes the next development
# version that is worked on and that is to be released.
AC_INIT(kea, 2.3.9-git, kea-dev@lists.isc.org)
AC_CONFIG_SRCDIR(README)

# serial-tests is not available in automake version before 1.13, so
# we'll check that and conditionally use serial-tests. This check is
# adopted from code by Richard W.M. Jones:
# https://www.redhat.com/archives/libguestfs/2013-February/msg00102.html
m4_define([serial_tests], [
    m4_esyscmd([automake --version |
                head -1 |
                awk '{split ($NF,a,"."); if (a[1] == 1 && a[2] >= 12) { print "serial-tests" }}'
    ])
])
AM_INIT_AUTOMAKE(foreign serial_tests)

m4_ifdef([AM_SILENT_RULES], [AM_SILENT_RULES([yes])])dnl be backward compatible
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_MACRO_DIR([m4macros])

AC_CANONICAL_HOST
AC_CANONICAL_BUILD

# Check for compilers.
AC_PROG_CXX

# Check for preprocessors.
AC_PROG_CXXCPP

# Check for exact Kea version.
AC_MSG_CHECKING(whether this is a tarball or git source)
if test -d "${srcdir}/.git"; then
        KEA_SRCID="git `(cd "${top_srcdir}";git rev-parse HEAD)`"
        AC_MSG_RESULT("git")
else
        KEA_SRCID="tarball"
        AC_MSG_RESULT("tarball")
fi
# Export KEA_SRCID to config.h
# This will be either "tarball" or "git abcd".
# We do not want to put this in a config.h, because it messes up ccache
# horribly. When building different branches, the commit-id is different
# and since the config.h is included in most files *and* has a different
# content, ccache can't use cached content and thus has to do full compilation.
# Now it is in kea_version.h and config.status substitutes it.
AC_SUBST(KEA_SRCID)

# Check whether the version is a development one (odd minor).
AC_MSG_CHECKING(whether this is a development or stable version)
PACKAGE_VERSION_MINOR=`echo $PACKAGE_VERSION | cut -d '.' -f 2`
PACKAGE_VERSION_TYPE="stable"
if expr "$PACKAGE_VERSION_MINOR" % 2 = 1; then
        PACKAGE_VERSION_TYPE="development"
fi
# Export PACKAGE_VERSION_TYPE to kea_version.h
AC_SUBST(PACKAGE_VERSION_TYPE)

# Find a separator for path_replacer
for sep in "+" "," ";" "&" "__NONE__"; do
        if `pwd | grep -q $sep`; then continue; fi
        if `echo ${prefix} | grep -q $sep`; then continue; fi
        if `echo ${sysconfdir} | grep -q $sep`; then continue; fi
        if `echo ${localstatedir} | grep -q $sep`; then continue; fi
        SEP=$sep
        break
done
if test "$sep" = "__NONE__"; then
        AC_MSG_ERROR([can't find a separator character in '+,;&' for the path_replacer shell script])
fi
AC_SUBST(SEP)

# pkg-config can be required.
AC_PATH_PROG([PKG_CONFIG], [pkg-config])

# check against BusyBox ps not supporting ps -p.
ps -p 1234 2>&1 > /dev/null | grep 'unrecognized option: p'
if test $? -eq 0; then
        AC_MSG_WARN("ps does not support -p. It is likely the BusyBox ps: please install a full ps like procps")
fi

# Enable low-performing debugging facilities? This option optionally
# enables some debugging aids that perform slowly and hence aren't built
# by default.
AC_ARG_ENABLE([debug],
  [AS_HELP_STRING([--enable-debug],
    [enable debugging (default is no)])],
  [case "${enableval}" in
    yes) debug_enabled=yes ;;
    no)  debug_enabled=no ;;
    *)   AC_MSG_ERROR([bad value ${enableval} for --enable-debug]) ;;
  esac],[debug_enabled=no])
AM_CONDITIONAL([DEBUG_ENABLED], [test x$debug_enabled = xyes])
AM_COND_IF([DEBUG_ENABLED], [AC_DEFINE([ENABLE_DEBUG], [1], [Enable low-performing debugging facilities?])])

# Include premium configuration
INCLUDED_HOOKS=

PREMIUM_DIR=
DISTCHECK_PREMIUM_CONFIGURE_FLAG=
AC_DEFUN([AX_PREMIUM],[])
# m4_sinclude includes the file if it exists at autoreconf time
m4_sinclude(premium/config.m4)
AC_SUBST(PREMIUM_DIR)
AC_SUBST(DISTCHECK_PREMIUM_CONFIGURE_FLAG)
AX_PREMIUM

# Include contrib configuration
# (currently only a provision copied from premium support)
CONTRIB_DIR=
DISTCHECK_CONTRIB_CONFIGURE_FLAG=
AC_DEFUN([AX_CONTRIB],[])
m4_sinclude(contrib/config.m4)
AC_SUBST(CONTRIB_DIR)
AC_SUBST(DISTCHECK_CONTRIB_CONFIGURE_FLAG)
AX_CONTRIB

# Libtool configuration
#

# libtool cannot handle spaces in paths, so exit early if there is one
if [ test `echo $PWD | grep -c ' '` != "0"  ]; then
    AC_MSG_ERROR([Kea cannot be built in a directory that contains spaces, because of libtool limitations. Please change the directory name, or use a symbolic link that does not contain spaces.])
fi

# On FreeBSD (and probably some others), clang++ does not meet an autoconf
# assumption in identifying libtool configuration regarding shared library:
# the configure script will execute "$CC -shared $CFLAGS/$CXXFLAGS -v" and
# expect the output contains -Lxxx or -Ryyy.  This is the case for g++, but
# not for clang++, and, as a result, it will cause various errors in linking
# programs or running them with a shared object (such as some of our python
# scripts).
# To work around this problem we define a temporary variable
# "CXX_LIBTOOL_LDFLAGS".  It's expected to be defined as, e.g, "-L/usr/lib"
# to temporarily fake the output so that it will be compatible with that of
# g++.
CFLAGS_SAVED=$CFLAGS
CXXFLAGS_SAVED=$CXXFLAGS
CFLAGS="$CFLAGS $CXX_LIBTOOL_LDFLAGS"
CXXFLAGS="$CXXFLAGS $CXX_LIBTOOL_LDFLAGS"
LT_INIT
CFLAGS=$CFLAGS_SAVED
CXXFLAGS=$CXXFLAGS_SAVED

# Use C++ language
AC_LANG([C++])

# Identify the compiler: this check must be after AC_PROG_CXX and AC_LANG.
AM_CONDITIONAL(USE_GXX, test "X${GXX}" = "Xyes")
AC_CHECK_DECL([__SUNPRO_CC], [SUNCXX="yes"], [SUNCXX="no"])
AC_CHECK_DECL([__clang__], [CLANGPP="yes"], [CLANGPP="no"])
# USE_CLANGPP is no longer used, keep it by symmetry with USE_GXX?
AM_CONDITIONAL(USE_CLANGPP, test "X${CLANGPP}" = "Xyes")

# Check for C++11 features support
AX_ISC_CPP11

# Check for C++20 compiler support.
AX_ISC_CPP20

# Check for std::is_base_of support
AC_MSG_CHECKING([for std::is_base_of])
AC_COMPILE_IFELSE(
    [AC_LANG_PROGRAM(
        [#include <type_traits>
        class A {};
        class B : A {};]
        [static_assert(std::is_base_of<A, B>::value, "");])],
    [AC_MSG_RESULT(yes)
    AC_DEFINE([HAVE_IS_BASE_OF], [1],
    [Define to 1 if std::is_base_of is available])],
    [AC_MSG_RESULT(no)])

# Check if system and steady clocks use the same duration type.
AC_MSG_CHECKING([for different std::chrono::duration types])
AC_COMPILE_IFELSE(
    [AC_LANG_PROGRAM(
        [#include <chrono>
        #include <type_traits>]
        [static_assert(!std::is_same<
                           std::chrono::system_clock::duration,
                           std::chrono::steady_clock::duration
                                    >::value, "");])],
    [AC_MSG_RESULT(yes)],
    [AC_MSG_RESULT(no)
    AC_DEFINE([CHRONO_SAME_DURATION], [1],
    [Define to 1 if system and steady clocks use the same duration type])])

dnl Determine if we are using GNU sed
GNU_SED=no
$SED --version 2> /dev/null | grep GNU > /dev/null 2>&1
if test $? -eq 0; then
  GNU_SED=yes
fi

# Display the C++ version
AC_MSG_CHECKING([C++ version])
cat > conftest.cpp << EOF
long v = __cplusplus;
EOF
CXX_STANDARD=`$CXX $CXXFLAGS -E -o - conftest.cpp | grep '^long v = ' | $SED -e 's/^long v = //' -e 's/[[^0-9]]*$//' 2> /dev/null`
if test -z "$CXX_STANDARD"; then
        CXX_STANDARD="unknown"
fi
AC_MSG_RESULT([$CXX_STANDARD])

# Linker options

# check -R, "-Wl,-R" or -rpath
AX_ISC_RPATH

# Compiler dependent settings: define some mandatory CXXFLAGS here.
# We also use a separate variable KEA_CXXFLAGS.  This will (and should) be
# used as the default value for each specific AM_CXXFLAGS:
# AM_CXXFLAGS = $(KEA_CXXFLAGS)
# AM_CXXFLAGS += ... # add module specific flags
# We need this so that we can disable some specific compiler warnings per
# module basis; since AM_CXXFLAGS are placed before CXXFLAGS, and since
# gcc's -Wno-XXX option must be specified after -Wall or -Wextra, we cannot
# specify the default warning flags in CXXFLAGS and let specific modules
# "override" the default.

# This may be used to try linker flags.
AC_DEFUN([KEA_CXX_TRY_FLAG], [
  AC_MSG_CHECKING([whether $CXX supports $1])

  kea_save_CXXFLAGS="$CXXFLAGS"
  CXXFLAGS="$CXXFLAGS -Werror $1"

  AC_LINK_IFELSE([AC_LANG_SOURCE([int main(){ return 0;}])],
                 [kea_cxx_flag=yes], [kea_cxx_flag=no])
  CXXFLAGS="$kea_save_CXXFLAGS"

  if test "x$kea_cxx_flag" = "xyes"; then
    ifelse([$2], , :, [$2])
  else
    ifelse([$3], , :, [$3])
  fi

  AC_MSG_RESULT([$kea_cxx_flag])
])

CXX_VERSION="unknown"

# SunStudio compiler requires special compiler options for boost
# (http://blogs.sun.com/sga/entry/boost_mini_howto)
if test "$SUNCXX" = "yes"; then
CXX_VERSION=`$CXX -V 2> /dev/null | head -1`
CXXFLAGS="$CXXFLAGS -library=stlport4 -features=tmplife -features=tmplrefstatic"
KEA_CXXFLAGS="$KEA_CXXFLAGS -mt"
MULTITHREADING_FLAG="-mt"
fi

# Newer versions of clang++ promotes "unused driver arguments" warnings to
# a fatal error with -Werror, causing build failure.  Since we use multiple
# compilers on multiple systems, this can easily happen due to settings for
# non clang++ environments that could be just ignored otherwise.  It can also
# happen if clang++ is used via ccache.  So, although probably suboptimal,
# we suppress this particular warning.  Note that it doesn't weaken checks
# on the source code.
if test "X$CLANGPP" = "Xyes"; then
CXX_VERSION=`$CXX --version 2> /dev/null | head -1`
KEA_CXXFLAGS="$KEA_CXXFLAGS -Qunused-arguments"
fi

# Comparison function based on the sort command that works with decimal numbers
# in a portable manner to the detriment of expr, test and most other commands.
less_than() {
    # Equal means not less than.
    if test "${1}" = "${2}"; then
        return 1
    fi

    # Sort numerically, check the first item against ${1}.
    if test "$(printf '%s\n%s\n' "${1}" "${2}" | sort -V | head -n 1)" = "${1}"; then
        return 0
    fi

    # ${2} is smaller than ${1}.
    return 1
}

# gcc/clang specific settings:
if test "X$GXX" = "Xyes"; then
CXX_VERSION=`$CXX --version 2> /dev/null | head -1`
KEA_CXXFLAGS="$KEA_CXXFLAGS -Wall -Wextra -Wnon-virtual-dtor -Wwrite-strings -Woverloaded-virtual -Wno-sign-compare"
# gcc 4.4 would emit warnings about breaking strict aliasing rules.
# See https://gcc.gnu.org/bugzilla/show_bug.cgi?id=41874
CXX_DUMP_VERSION=`$CXX -dumpversion | cut -f1-2 -d.`
if less_than "$CXX_DUMP_VERSION" "4.5"; then
       WARNING_GCC_44_STRICT_ALIASING_CFLAG="-fno-strict-aliasing"
fi
AC_SUBST(WARNING_GCC_44_STRICT_ALIASING_CFLAG)
CPPP="$CXXCPP"
# gcc 5 preprocessor requires -P for checking its output
if less_than "5" "$CXX_DUMP_VERSION"; then
       CPPP="$CPPP -P"
fi

case "$host" in
*-solaris*)
        MULTITHREADING_FLAG=-pthreads
        # In Solaris, IN6ADDR_ANY_INIT and IN6ADDR_LOOPBACK_INIT need -Wno-missing-braces
        KEA_CXXFLAGS="$KEA_CXXFLAGS -Wno-missing-braces"
        ;;
*-apple-darwin*)
        MULTITHREADING_FLAG=
        ;;
*)
        MULTITHREADING_FLAG=-pthread
        ;;
esac
KEA_CXXFLAGS="$KEA_CXXFLAGS $MULTITHREADING_FLAG"

dumpmachine=`$CXX -dumpmachine`
case "$dumpmachine" in
*-musl)
        AC_MSG_WARN("Detected musl libc: musl dlclose() is a noop")
        AC_DEFINE([LIBC_MUSL], [1], [Define to 1 if libc is musl])
        ;;
esac

# Disable -Werror by default. Only use it if specifically enabled.
# The usage of this flag is:
#
# No flag:            -Werror is disabled
# --with-werror:      -Werror is enabled
# --with-werror=yes:  -Werror is enabled
# --with-werror=no:   -Werror is disabled
# --with-werror=value -Werror is enabled and "value" is included in the compiler flags
#
# In the last case, "value" may be one or more compiler flags, e.g.

# --with-werror=-Wundef
# --with-werror='-Wundef -Wconversion'

werror_extras=
AC_ARG_WITH(werror,
    [AS_HELP_STRING([--with-werror],[Compile using -Werror (default=no)])],
    [
     case "${withval}" in
         yes) with_werror=1 ;;
         no)  with_werror=0 ;;
         -*)  with_werror=1; werror_extras=${withval} ;;
         *)   AC_MSG_ERROR(bad value ${withval} for --with-werror) ;;
     esac],
     [with_werror=0])

werror_ok=0

# Certain versions of gcc (g++) have a bug that incorrectly warns about
# the use of anonymous name spaces even if they're closed in a single
# translation unit.  For these versions we have to disable -Werror.
if test $with_werror = 1; then
   CXXFLAGS_SAVED="$CXXFLAGS"
   CXXFLAGS="$CXXFLAGS $KEA_CXXFLAGS -Werror"
   AC_MSG_CHECKING(for in-TU anonymous namespace breakage)
   # We use struct, not class, here, because some compilers complain about
   # "unused private members", causing a false positive.
   AC_COMPILE_IFELSE(
    [AC_LANG_PROGRAM([[
      namespace { struct Foo {}; }
      namespace isc { struct Bar { Foo foo_; }; }
    ]], [[]])],
    [AC_MSG_RESULT(no)
     werror_ok=1
     KEA_CXXFLAGS="$KEA_CXXFLAGS -Werror"],
    [AC_MSG_RESULT(yes)]
   )
   CXXFLAGS="$CXXFLAGS_SAVED"
fi

# Added flags after -Werror

# Some versions of GCC warn about some versions of Boost regarding
# missing initializer for members in its posix_time.
# https://svn.boost.org/trac/boost/ticket/3477
# But older GCC compilers don't have the flag.
KEA_CXX_TRY_FLAG([-Wno-missing-field-initializers],
        [KEA_CXXFLAGS="$KEA_CXXFLAGS -Wno-missing-field-initializers"])

if test "X$CLANGPP" = "Xyes"; then
        # This is to workaround unused variables tcout and tcerr in
        # log4cplus's streams.h and unused parameters from some of the
        # Boost headers.
        KEA_CXXFLAGS="$KEA_CXXFLAGS -Wno-unused-variable -Wno-unused-parameter"
fi

# Add the extras at the very last
# Note it can be used to re-enable a (fatal) warning
for extra in $werror_extras; do
        KEA_CXX_TRY_FLAG([$extra],
                [KEA_CXXFLAGS="$KEA_CXXFLAGS $extra"],
                [AC_MSG_ERROR([$CXX does not support $extra"])])
done

fi                              dnl GXX = yes

# allow building programs with static link.  we need to make it selective
# because loadable modules cannot be statically linked.
AC_ARG_ENABLE([static-link],
  [AS_HELP_STRING([--enable-static-link],
    [build programs with static link [[default=no]]])],
  [enable_static_link=yes], [enable_static_link=no])
AM_CONDITIONAL(USE_STATIC_LINK, test $enable_static_link = yes)
AM_COND_IF([USE_STATIC_LINK], [AC_DEFINE([USE_STATIC_LINK], [1], [Was Kea statically linked?])])

# Check validity about some libtool options
if test $enable_static_link = yes -a $enable_static = no; then
        AC_MSG_ERROR([--enable-static-link requires --enable-static])
fi
if test $enable_static_link = no -a $enable_shared = no; then
        AC_MSG_ERROR([--disable-static-link requires --enable-shared])
fi

# OS dependent configuration
kea_undefined_pthread_behavior=no

case "$host" in
*-solaris*)
        # Solaris requires special definitions to get some standard libraries
        # (e.g. getopt(3)) available with common used header files.
        CPPFLAGS="$CPPFLAGS -D_XPG4_2 -D__EXTENSIONS__"
        # "now" binding is necessary to prevent deadlocks in C++ static initialization code
        LDFLAGS="$LDFLAGS -z now"
        # Destroying locked mutexes, condition variables being waited
        # on, etc. are undefined behavior on Solaris, so we set it as
        # such here.
        kea_undefined_pthread_behavior=yes
        ;;
*-apple-darwin*)
        # Starting with OSX 10.7 (Lion) we must choose which IPv6 API to use
        # (RFC2292 or RFC3542).
        CPPFLAGS="$CPPFLAGS -D__APPLE_USE_RFC_3542"

        # In OS X 10.9 (and possibly any future versions?) pthread_cond_destroy
        # doesn't work as documented, which makes some of unit tests fail.
        AC_MSG_CHECKING([OS X versions where destroying locked locks do not fail])
        AC_COMPILE_IFELSE(
         [AC_LANG_PROGRAM([[
          #include <Availability.h>
         ]], [[
          #ifdef __MAC_OS_X_VERSION_MIN_REQUIRED
          #if __MAC_OS_X_VERSION_MIN_REQUIRED >= 1090
          #error " OS X >= 10.9"
          #endif
          #endif
          return 1;
         ]])],
         [AC_MSG_RESULT([OS X < 10.9])],
         [AC_MSG_RESULT([OS X >= 10.9])
          kea_undefined_pthread_behavior=yes])
        ;;
*-freebsd*)
        # On FreeBSD10.1 pthread_cond_destroy doesn't work as documented, which
        # causes the CondVarTest.destroyWhileWait test to fail. According to the
        # pthread_cond_destroy documentation for FreeBSD, this function should
        # return EBUSY error when there is a thread waiting for the conditional
        # variable, whereas this function returned success code. We treat it here
        # as an undefined behavior. Also note that this issue was only visible
        # when gtest 1.7 was in use, because the previous versions of gtest
        # didn't seem to have support for the death tests on FreeBSD. As a
        # result, the test was not executed and the error didn't occur.
        kea_undefined_pthread_behavior=yes
        ;;
esac
if [ test $kea_undefined_pthread_behavior = "yes" ]; then
   AC_DEFINE([HAS_UNDEFINED_PTHREAD_BEHAVIOR], [1], [Does this platform have some undefined pthreads behavior?])
fi

# Our experiments have shown Solaris 10 has broken support for the
# IPV6_USE_MIN_MTU socket option for getsockopt(); it doesn't return the value
# previously set via setsockopt().  We know it doesn't happen on one instance
# on Solaris 11, but we don't know whether it happens for any Solaris 10
# implementations or for earlier versions of Solaris.  In any case, at the
# moment this matters for only one unittest case, so we'll simply disable
# the affected test using the following definition with the specific hardcoding
# of that version of Solaris.
case "$host" in
*-solaris2.10)
        AC_DEFINE([HAVE_BROKEN_GET_IPV6_USE_MIN_MTU], [1],
        [Define to 1 if getsockopt(IPV6_USE_MIN_MTU) does not work])
        ;;
esac

# Made perfdhcp optional.
AC_ARG_ENABLE(perfdhcp, [AS_HELP_STRING([--enable-perfdhcp],
              [enable perfdhcp, a DHCP benchmarking tool [default=no]])],
              enable_perfdhcp=$enableval, enable_perfdhcp=no)

DISTCHECK_PERFDHCP_CONFIGURE_FLAG=
if test "x$enable_perfdhcp" != xno ; then
  DISTCHECK_PERFDHCP_CONFIGURE_FLAG="--enable-perfdhcp"
fi

# Export to makefiles the info whether we have perfdhcp enabled or not
AM_CONDITIONAL(PERFDHCP, test x$enable_perfdhcp != xno)
AC_SUBST(DISTCHECK_PERFDHCP_CONFIGURE_FLAG)

# produce PIC unless we disable shared libraries. need this for python bindings.
if test $enable_shared != "no" -a "X$GXX" = "Xyes"; then
   KEA_CXXFLAGS="$KEA_CXXFLAGS -fPIC"
fi

# Look for glib static libs if they're trying to do static builds
if test $enable_static_link != "no"; then
   CXX_SAVED=$CXX
   CXX="$CXX -static"

   AC_LINK_IFELSE(
     [AC_LANG_PROGRAM([#include <math.h>],[(void)sqrt(-1.0);])],
     [AC_MSG_RESULT([checking for static glib libraries... yes])],
     [AC_MSG_RESULT([checking for static glib libraries... no])
      AC_MSG_ERROR([Building with --enable-static-link does not work. You appear to be missing glib static libraries. Check config.log for details.])])

   CXX=$CXX_SAVED
fi

AC_SUBST(KEA_CXXFLAGS)

# Checks for libraries.

AC_SEARCH_LIBS(inet_pton, [nsl])
AC_SEARCH_LIBS(recvfrom, [socket])
AC_SEARCH_LIBS(nanosleep, [rt])
AC_SEARCH_LIBS(dlsym, [dl])

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_TYPE_SIZE_T
AC_TYPE_SSIZE_T

# Detect OS type (it may be used to do OS-specific things, e.g.
# interface detection in DHCP)
AC_MSG_CHECKING(OS type)
BSD_TYPE="notaBSD"
case $host in
    *-linux*)
      AC_DEFINE([OS_LINUX], [1], [Running on Linux?])
      OS_TYPE="Linux"
      CPPFLAGS="$CPPFLAGS -DOS_LINUX"
      ;;
    *-apple-darwin*)
      AC_DEFINE([OS_BSD], [1], [Running on BSD?])
      AC_DEFINE([OS_OSX], [1], [Running on OSX?])
      OS_TYPE="BSD"
      BSD_TYPE="OSX"
      CPPFLAGS="$CPPFLAGS -DOS_BSD"
      ;;
    *-freebsd*)
      AC_DEFINE([OS_BSD], [1], [Running on BSD?])
      AC_DEFINE([OS_FREEBSD], [1], [Running on FreeBSD?])
      OS_TYPE="BSD"
      BSD_TYPE="FreeBSD"
      CPPFLAGS="$CPPFLAGS -DOS_BSD"
      ;;
    *-netbsd*)
      AC_DEFINE([OS_BSD], [1], [Running on BSD?])
      AC_DEFINE([OS_NETBSD], [1], [Running on NetBSD?])
      OS_TYPE="BSD"
      BSD_TYPE="NetBSD"
      CPPFLAGS="$CPPFLAGS -DOS_BSD"
      ;;
    *-openbsd*)
      AC_DEFINE([OS_BSD], [1], [Running on BSD?])
      AC_DEFINE([OS_OPENBSD], [1], [Running on OpenBSD?])
      OS_TYPE="BSD"
      BSD_TYPE="OpenBSD"
      CPPFLAGS="$CPPFLAGS -DOS_BSD"
      ;;
    *-solaris*)
      AC_DEFINE([OS_SOLARIS], [1], [Running on Solaris?])
      OS_TYPE="Solaris"
      CPPFLAGS="$CPPFLAGS -DOS_SUN"
      ;;
    *)
      OS_TYPE="Unknown"
      # $host_os is more user friendly than full $host
      AC_MSG_WARN("Unsupported OS: $host_os")
      ;;
esac
AC_MSG_RESULT($OS_TYPE)

AM_CONDITIONAL(OS_LINUX, test $OS_TYPE = Linux)
AM_CONDITIONAL(OS_BSD, test $OS_TYPE = BSD)
AM_CONDITIONAL(OS_SOLARIS, test $OS_TYPE = Solaris)
AM_CONDITIONAL(OS_OSX, test $BSD_TYPE = OSX)
AM_CONDITIONAL(OS_FREEBSD, test $BSD_TYPE = FreeBSD)
AM_CONDITIONAL(OS_NETBSD, test $BSD_TYPE = NetBSD)
AM_CONDITIONAL(OS_OPENBSD, test $BSD_TYPE = OpenBSD)


AC_MSG_CHECKING(for sa_len in struct sockaddr)
AC_COMPILE_IFELSE(
  [AC_LANG_PROGRAM([[
    #include <sys/types.h>
    #include <sys/socket.h>
  ]], [[
    struct sockaddr sa;
    sa.sa_len = 0;
    return (0);
  ]])],
  [AC_MSG_RESULT(yes)
   AC_DEFINE(HAVE_SA_LEN, 1, [Define to 1 if sockaddr has a sa_len member, and corresponding sin_len and sun_len])],
  [AC_MSG_RESULT(no)]
)

usable_regex=
AC_MSG_CHECKING(for usable C++11 regex)
AC_RUN_IFELSE([AC_LANG_SOURCE([[
#include <regex>
#include <iostream>
int main() {
  const std::regex regex(".*");
  const std::string string = "This should match!";
  const auto result = std::regex_search(string, regex);
  return result ? EXIT_SUCCESS : EXIT_FAILURE;
}]])],
        [AC_MSG_RESULT(yes)
         usable_regex="yes"],
        [AC_MSG_RESULT(no)
         usable_regex="no"],
        [AC_MSG_RESULT(cross compiling)])
# When cross-compiling we don't have any way to check if regex is
# usable or not.
# Let's be optimistic and assume it is by testing only the negative case.
if test "x$usable_regex" != "xno" ; then
        AC_DEFINE(USE_REGEX, 1, [Define to 1 if C++11 regex is usable])
fi

# Check for NETCONF support. If NETCONF was enabled in the build, and this check
# passes, it will enforce the --std=c++20 flag. Let's do the check as early as
# possible so that the rest of the checks include the flag as well.
AX_NETCONF

# Run the gtest detection routines. This supports --with-gtest and --with-gtest-source
# parameters. If specified, those will set the HAVE_GTEST, HAVE_GTEST_SOURCE,
# DISTCHECK_GTEST_CONFIGURE_FLAG, GTEST_INCLUDES, GTEST_LDFLAGS, GTEST_LDADD, GTEST_SOURCE
# variables.
AX_ISC_GTEST

# Sets up for use of botan unless openssl is specified
# sets variables CRYPTO_*
AX_CRYPTO

# List of directories, where tools like mysql_config or pgsql_config will be
# searched for
defaultdirs="/usr /usr/local /usr/pkg /opt /opt/local"

# Check for MySql.  The path to the mysql_config program is given with
# the --with-mysql-config (default to /usr/bin/mysql-config).  By default,
# the software is not built with MySQL support enabled.
mysql_config="no"
AC_ARG_WITH([mysql],
  [AS_HELP_STRING([--with-mysql[[=PATH]]],
    [path to the MySQL 'mysql_config' script (MySQL is used for the DHCP database)])],
  [mysql_config="$withval"])

deprec_msg="no"
AC_ARG_WITH([dhcp-mysql],,
    [mysql_config="$withval";deprec_msg="yes"])

if test "${deprec_msg}" = "yes" ; then
    AC_MSG_WARN([--with-dhcp-mysql has been deprecated, please use --with-mysql])
fi

if test "${mysql_config}" = "yes" ; then
    MYSQL_CONFIG="/usr/bin/mysql_config"
    for d in $defaultdirs
    do
        if test -f $d/bin/mysql_config; then
            MYSQL_CONFIG="$d/bin/mysql_config"
            break
        fi
    done
elif test "${mysql_config}" != "no" ; then
    MYSQL_CONFIG="${withval}"
fi

DISTCHECK_MYSQL_CONFIGURE_FLAG=
if test "$MYSQL_CONFIG" != "" ; then
    if test -d "$MYSQL_CONFIG" -o ! -x "$MYSQL_CONFIG" ; then
        AC_MSG_ERROR([MySQL dependencies cannot be found. Please install MySQL libraries or point --with-mysql to mysql_config program if it is located in non-default directory, eg. --with-mysql=/opt/mysql/bin/mysql_config.])
    fi

    DISTCHECK_MYSQL_CONFIGURE_FLAG="--with-mysql=$MYSQL_CONFIG"

    MYSQL_CPPFLAGS=`$MYSQL_CONFIG --cflags`
    MYSQL_LIBS=`$MYSQL_CONFIG --libs`
    MYSQL_LIBS="$MYSQL_LIBS $CRYPTO_LIBS"
    MYSQL_VERSION=`$MYSQL_CONFIG --version`

    AC_SUBST(MYSQL_CPPFLAGS)
    AC_SUBST(MYSQL_LIBS)
    AC_SUBST(DISTCHECK_MYSQL_CONFIGURE_FLAG)

    # Check that a simple program using MySQL functions can compile and link.
    CPPFLAGS_SAVED="$CPPFLAGS"
    LIBS_SAVED="$LIBS"

    CPPFLAGS="$MYSQL_CPPFLAGS $CPPFLAGS"
    LIBS="$MYSQL_LIBS $LIBS"

    AC_LINK_IFELSE(
        [AC_LANG_PROGRAM([#include <mysql.h>],
                         [MYSQL mysql_handle;
                          (void) mysql_init(&mysql_handle);
                         ])],
        [AC_MSG_RESULT([checking for MySQL headers and library... yes])],
        [AC_MSG_RESULT([checking for MySQL headers and library... no])
         AC_MSG_ERROR([Needs MySQL library])]
    )

    # Note that MYSQL is present in the config.h file
    AC_DEFINE([HAVE_MYSQL], [1], [MySQL is present])

    # Check if my_bool is defined.
    AC_COMPILE_IFELSE(
        [AC_LANG_PROGRAM([#include <mysql.h>
                          const my_bool MLM_FALSE = 0;]
                         [])],
        [AC_MSG_RESULT([checking for MySQL my_bool... yes])
         AC_DEFINE([HAVE_MYSQL_MY_BOOL], [1], [MySQL uses my_bool])],
        [AC_MSG_RESULT([checking for MySQL my_bool... no])])

    # Check if mysql_get_option is defined.
    AC_MSG_CHECKING([for MySQL mysql_get_option])
    AC_LINK_IFELSE(
        [AC_LANG_PROGRAM(
            [#include <mysql.h>],
            [MYSQL handle;
             unsigned int timeout;
             mysql_get_option(&handle, MYSQL_OPT_CONNECT_TIMEOUT, &timeout);]
        )],
        [AC_MSG_RESULT([yes])
         AC_DEFINE([HAVE_MYSQL_GET_OPTION], [true], [MySQL has mysql_get_option defined.])],
        [AC_MSG_RESULT([no])
         AC_MSG_WARN([mysql_get_option program failed to build:

$(cat conftest.cpp)

$(cat conftest.err)])]
    )

    CPPFLAGS=$CPPFLAGS_SAVED
    LIBS=$LIBS_SAVED
fi

# Solaris puts FIONREAD in filio.h
AC_CHECK_HEADERS(sys/filio.h,,,)

# ... and at the shell level, so Makefile.am can take action depending on this.
AM_CONDITIONAL(HAVE_MYSQL, test "$MYSQL_CONFIG" != "")

pg_config="no"
AC_ARG_WITH([pgsql],
  [AS_HELP_STRING([--with-pgsql[[=PATH]]],
    [path to the PostgreSQL 'pg_config' script])],
  [pg_config="$withval"])

deprec_msg="no"
AC_ARG_WITH([dhcp-pgsql],,
    [pg_config="$withval";deprec_msg="yes"])

if test "${deprec_msg}" = "yes" ; then
    AC_MSG_WARN([--with-dhcp-pgsql has been deprecated, please use --with-pgsql])
fi

if test "${pg_config}" = "yes" ; then
    PG_CONFIG="/usr/bin/pg_config"
    for d in $defaultdirs
    do
        if test -f $d/bin/pg_config; then
            PG_CONFIG="$d/bin/pg_config"
            break
        fi
    done
elif test "${pg_config}" != "no" ; then
    PG_CONFIG="${withval}"
fi

DISTCHECK_PGSQL_CONFIGURE_FLAG=
if test "$PG_CONFIG" != "" ; then
    if test -d "$PG_CONFIG" -o ! -x "$PG_CONFIG" ; then
        AC_MSG_ERROR([PostgreSQL dependencies cannot be found. Please install PostgreSQL libraries or point --with-pgsql to pg_config program if it is located in non-default directory, eg. --with-pgsql=/opt/pgsql/bin/pg_config.])
    fi

    DISTCHECK_PGSQL_CONFIGURE_FLAG="--with-pgsql=$PG_CONFIG"

    PGSQL_CPPFLAGS=`$PG_CONFIG --cppflags`
    PGSQL_INCLUDEDIR=`$PG_CONFIG --includedir`
    PGSQL_INCLUDEDIR_SERVER=`$PG_CONFIG --includedir-server`
    PGSQL_CPPFLAGS="$PGSQL_CPPFLAGS -I$PGSQL_INCLUDEDIR -I$PGSQL_INCLUDEDIR_SERVER"
    PGSQL_LIBS=`$PG_CONFIG --libdir`
    PGSQL_LIBS="-L$PGSQL_LIBS -lpq"
    PGSQL_VERSION=`$PG_CONFIG --version`
    PGSQL_MAJOR_VERSION=`$PG_CONFIG --version | cut -f2 -d' ' | cut -f1 -d'.'`

    AC_SUBST(PGSQL_CPPFLAGS)
    AC_SUBST(PGSQL_LIBS)
    AC_SUBST(DISTCHECK_PGSQL_CONFIGURE_FLAG)

    # Check that a simple program using PostgreSQL functions can compile and link.
    CPPFLAGS_SAVED="$CPPFLAGS"
    LIBS_SAVED="$LIBS"

    CPPFLAGS="$PGSQL_CPPFLAGS $CPPFLAGS"
    LIBS="$PGSQL_LIBS $LIBS"

    AC_LINK_IFELSE(
            [AC_LANG_PROGRAM([#include <libpq-fe.h>],
                             [PGconn * c = PQconnectdb("dbname = 'postgres'");
                              PQfinish(c);])],
            [AC_MSG_RESULT([checking for PostgreSQL headers and library... yes])],
            [AC_MSG_RESULT([checking for PostgreSQL headers and library... no])
             AC_MSG_ERROR([Needs PostgreSQL library])]
    )

    AC_CHECK_HEADERS([utils/errcodes.h],,
    AC_MSG_ERROR([Missing required header file (errcodes.h) from PostgreSQL server-development package]))

    CPPFLAGS=$CPPFLAGS_SAVED
    LIBS=$LIBS_SAVED

    # Note that PostgreSQL is present in the config.h file
    AC_DEFINE([HAVE_PGSQL], [1], [PostgreSQL is present])

if test $PGSQL_MAJOR_VERSION -ge 12; then
   AC_DEFINE([HAVE_PGSQL_TCP_USER_TIMEOUT], [1], [PostgreSQL connection parameter tcp_user_timeout supported])
fi
fi

# ... and at the shell level, so Makefile.am can take action depending on this.
AM_CONDITIONAL(HAVE_PGSQL, test "$PG_CONFIG" != "")

# allow building kea programs with a PostgreSQL without OpenSSL.
AC_ARG_ENABLE([pgsql-ssl],
  [AS_HELP_STRING([--enable-pgsql-ssl],
    [enable OpenSSL support in PostgreSQL [default=yes]])],
  [pgsql_ssl=$enableval], [pgsql_ssl=no], [pgsql_ssl=yes])
if test "${pgsql_ssl}" = "yes"; then
    AC_DEFINE([HAVE_PGSQL_SSL], [1], [PostgreSQL was built with OpenSSL support])
fi

# Check for log4cplus
DISTCHECK_LOG4CPLUS_CONFIGURE_FLAG=
log4cplus_path="yes"
AC_ARG_WITH([log4cplus],
            [AS_HELP_STRING([--with-log4cplus[[=PATH]]],
                            [optional path to the log4cplus installation directory])],
            [log4cplus_path="$withval"])
if test "${log4cplus_path}" = "no" ; then
    AC_MSG_ERROR([Need log4cplus])
elif test "${log4cplus_path}" != "yes" ; then
  DISTCHECK_LOG4CPLUS_CONFIGURE_FLAG="-with-log4cplus=${log4cplus_path}"
  LOG4CPLUS_INCLUDES="-I${log4cplus_path}/include"
  LOG4CPLUS_LIBS="-L${log4cplus_path}/lib"
else
# If not specified, try some common paths.
        for d in $defaultdirs
        do
                if test -f $d/include/log4cplus/logger.h; then
                        LOG4CPLUS_INCLUDES="-I$d/include"
                        LOG4CPLUS_LIBS="-L$d/lib"
                        if test -d $d/lib64; then
                                LOG4CPLUS_LIBS="$LOG4CPLUS_LIBS -L$d/lib64"
                        fi
                        break
                fi
        done
        DISTCHECK_LOG4CPLUS_CONFIGURE_FLAG="-with-log4cplus"
fi

LOG4CPLUS_LIBS="$LOG4CPLUS_LIBS -llog4cplus"

AC_SUBST(DISTCHECK_LOG4CPLUS_CONFIGURE_FLAG)
AC_SUBST(LOG4CPLUS_LIBS)
AC_SUBST(LOG4CPLUS_INCLUDES)

CPPFLAGS_SAVED=$CPPFLAGS
CPPFLAGS="$LOG4CPLUS_INCLUDES $CPPFLAGS"
LIBS_SAVED="$LIBS"
LIBS="$LOG4CPLUS_LIBS $MULTITHREADING_FLAG $LIBS"

AC_CHECK_HEADERS([log4cplus/logger.h],,
                 AC_MSG_ERROR([Missing required header file (logger.h) from the log4cplus package]))
AC_LINK_IFELSE(
        [AC_LANG_PROGRAM([#include <log4cplus/logger.h>
                         ],
                         [using namespace log4cplus;
                          Logger logger = Logger::getInstance("main");
                         ])],
        [AC_MSG_RESULT([checking for log4cplus library... yes])],
        [AC_MSG_RESULT([checking for log4cplus library... no])
         AC_MSG_ERROR([Needs log4cplus library])]
)

dnl Determine the log4cplus version, used mainly for config.report.
AC_MSG_CHECKING([log4cplus version])
cat > conftest.cpp << EOF
#include <log4cplus/version.h>
AUTOCONF_LOG4CPLUS_VERSION=LOG4CPLUS_VERSION_STR
EOF

# The tabulation below is NOT an error: PLEASE keep it.
LOG4CPLUS_VERSION=`$CPPP $CPPFLAGS conftest.cpp | grep '^AUTOCONF_LOG4CPLUS_VERSION=' | $SED -e 's/^AUTOCONF_LOG4CPLUS_VERSION=//' -e 's/[[ 	]]//g' -e 's/"//g' 2> /dev/null`
if test -z "$LOG4CPLUS_VERSION"; then
  LOG4CPLUS_VERSION="unknown"
fi
$RM -f conftest.cpp
AC_MSG_RESULT([$LOG4CPLUS_VERSION])

CPPFLAGS=$CPPFLAGS_SAVED
LIBS=$LIBS_SAVED

# Older log4cplus versions (1.2.0) don't have the initializer.h header that
# would allow explicit initialization. Newer versions (2.0.4 for sure, possibly
# older as well) have it and it's recommended to use it. We detect whether
# it's present or not and do explicit initialization if possible.
CPPFLAGS_SAVED=$CPPFLAGS
CPPFLAGS="$LOG4CPLUS_INCLUDES $CPPFLAGS"
LIBS_SAVED="$LIBS"
LIBS="$LOG4CPLUS_LIBS $LIBS"
AC_MSG_CHECKING([log4cplus explicit initialization (log4cplus/initializer.h)])
AC_LINK_IFELSE(
        [AC_LANG_PROGRAM([#include <log4cplus/initializer.h>],
                         [log4cplus::Initializer initializer;]
                         )],
        [AC_MSG_RESULT([yes])
         AC_DEFINE(LOG4CPLUS_INITIALIZER_H, [1], [Explicit initialization of log4cplus possible])],
        [AC_MSG_RESULT(no)])
LIBS="$LIBS_SAVED"
CPPFLAGS=$CPPFLAGS_SAVED

#
# Configure Boost header path
#
AX_BOOST_FOR_KEA
# Boost offset_ptr is required in one library and not optional right now, so
# we unconditionally fail here if it doesn't work.
if test "$BOOST_OFFSET_PTR_WOULDFAIL" = "yes" -a X"$werror_ok" = X1; then
    AC_MSG_ERROR([Failed to compile a required header file.  Try upgrading Boost to 1.44 or higher (when using clang++) or specifying --without-werror.  See the ChangeLog entry for Trac no. 2147 for more details.])
fi

if test "$BOOST_STATIC_ASSERT_WOULDFAIL" = "yes" -a X"$werror_ok" = X1; then
    AC_MSG_ERROR([Failed to use Boost static assertions. Try upgrading Boost to 1.54 or higher (when using GCC 4.8) or specifying --without-werror.  See trac ticket no. 3039 for more details.])
fi

# There's a known bug in FreeBSD ports for Boost that would trigger a false
# warning in build with g++ and -Werror (we exclude clang++ explicitly to
# avoid unexpected false positives).
if test "$BOOST_NUMERIC_CAST_WOULDFAIL" = "yes" -a X"$werror_ok" = X1 -a $CLANGPP = "no"; then
    AC_MSG_ERROR([Failed to compile a required header file.  If you are using FreeBSD and Boost installed via ports, retry with specifying --without-werror.  See the ChangeLog entry for Trac no. 1991 for more details.])
fi

# Add some default CPP flags needed for Boost, identified by the AX macro.
CPPFLAGS="$CPPFLAGS $CPPFLAGS_BOOST_THREADCONF"

# Can be required by gtest, boost and perhaps still asio
AC_CHECK_LIB(pthread, pthread_create,[ LDFLAGS="$LDFLAGS -lpthread" ], [])

# Now that Crypto backend and Boost were done we can address TLS.
AX_TLS

#
# Some Googletest versions bug with C++11 compilers
#
if test $enable_gtest != "no"; then
   AC_MSG_CHECKING([if Google Test is compatible with the compiler])
   CPPFLAGS_SAVED=$CPPFLAGS
   CPPFLAGS="$CPPFLAGS $BOOST_INCLUDES $GTEST_INCLUDES"
   AC_COMPILE_IFELSE(
       [AC_LANG_PROGRAM(
            [#include <boost/shared_ptr.hpp>
            #include <gtest/gtest.h>
            void foo() {
                boost::shared_ptr<int> bar;
                ASSERT_TRUE(bar);
            }],
            [return 0;])],
        [AC_MSG_RESULT(yes)],
        [AC_MSG_ERROR([XXX_TRUE() Google Test macros won't compile; the most likely reason is that a later version of Google Test is required])])
    CPPFLAGS=$CPPFLAGS_SAVED
fi

# Check for CreateUnifiedDiff from gtest >= 1.8.0
if test $enable_gtest != "no"; then
   AC_MSG_CHECKING([for CreateUnifiedDiff in $GTEST_INCLUDES/gtest.h])
   CPPFLAGS_SAVED=$CPPFLAGS
   CPPFLAGS="$CPPFLAGS $BOOST_INCLUDES $GTEST_INCLUDES"
   AC_COMPILE_IFELSE(
       [AC_LANG_PROGRAM(
            [#include <boost/algorithm/string.hpp>
            #include <gtest/gtest.h>
            #include <string>
            #include <vector>
            std::string nodiff(std::string text) {
                std::vector<std::string> lines;
                boost::split(lines, text, boost::is_any_of("\n"));
                using namespace testing::internal;
                return (edit_distance::CreateUnifiedDiff(lines, lines));
            }],
            [return 0;])],
        [AC_MSG_RESULT(yes)
        AC_DEFINE([HAVE_CREATE_UNIFIED_DIFF], [1],
        [Define to 1 if gtest defines edit_distance::CreateUnifiedDiff])],
        [AC_MSG_RESULT(no)])
    CPPFLAGS=$CPPFLAGS_SAVED
fi

# Provide the ability to include our coroutine header or other headers from ext.
CPPFLAGS="$CPPFLAGS -I\$(top_srcdir) -I\$(top_builddir)"

# Doesn't seem to be required?
#CPPFLAGS="$CPPFLAGS -DBOOST_ASIO_HEADER_ONLY"
#
# Disable threads: they seems to break things on some systems
# As now we use threads in boost ASIO this is commented out...
# CPPFLAGS="$CPPFLAGS -DBOOST_ASIO_DISABLE_THREADS=1"

# We tried to stay header only
if test "x${BOOST_LIBS}" = "x"; then
   # Don't want boost system library
   CPPFLAGS="$CPPFLAGS -DBOOST_ERROR_CODE_HEADER_ONLY"
   # Avoid boost::system::throws multiple defines
   CPPFLAGS="$CPPFLAGS -DBOOST_SYSTEM_NO_DEPRECATED"
fi

# Check for functions that are not available on all platforms
AC_CHECK_FUNCS([pselect])

# /dev/poll issue: ASIO uses /dev/poll by default if it's available (generally
# the case with Solaris).  Unfortunately its /dev/poll specific code would
# trigger the gcc's "missing-field-initializers" warning, which would
# subsequently make the build fail with -Werror.  Further, older versions of
# gcc don't provide an option to selectively suppress this warning.
# So, for the moment, we simply disable the use of /dev/poll.  Unless we
# implement recursive DNS server with randomized ports, we don't need the
# scalability that /dev/poll can provide, so this decision wouldn't affect
# run time performance.  Hopefully we can find a better solution or the ASIO
# code will be updated by the time we really need it.
AC_CHECK_HEADERS(sys/devpoll.h, ac_cv_have_devpoll=yes, ac_cv_have_devpoll=no)
if test "X$ac_cv_have_devpoll" = "Xyes" -a "X$GXX" = "Xyes"; then
    CPPFLAGS="$CPPFLAGS -DBOOST_ASIO_DISABLE_DEV_POLL=1"
fi

#
# Perl is optional; it is used only by some of the system test scripts.
#
AC_PATH_PROGS(PERL, perl5 perl)
AC_SUBST(PERL)
AC_PATH_PROGS(AWK, gawk awk)
AC_SUBST(AWK)

AC_ARG_ENABLE(generate_messages,
  [AS_HELP_STRING([--enable-generate-messages],
    [indicates that the messages files will be regenerated. [default=no]])],
  enable_generate_messages=$enableval, enable_generate_messages=no)

AM_CONDITIONAL([GENERATE_MESSAGES], [test x$enable_generate_messages != xno])

# cross compiling is not compatible with enable-generate-messages.
if test "$cross_compiling" = "yes"; then
    if test "$enable_generate_messages" != "no"; then
        AC_MSG_WARN([To build the message compiler is not compatible with cross compiling])
    fi
fi

AC_ARG_ENABLE(generate_parser,
  [AS_HELP_STRING([--enable-generate-parser],
    [indicates that the parsers will be regenerated. This implies that the
     bison and flex are required [default=no]])],
  enable_generate_parser=$enableval, enable_generate_parser=no)

# Check if flex is available. Flex is not needed for building Kea sources,
# unless you want to regenerate grammars.
# Autoconf 2.70 added an option and warns if not provided,
m4_version_prereq([2.70],
  [AC_PROG_LEX(noyywrap)],
  [AC_PROG_LEX])

# Check if bison is available. Bison is not needed for building Kea sources,
# unless you want to regenerate grammars
AC_PATH_PROG(YACC, bison)
AC_SUBST(YACC)

if test "x$enable_generate_parser" != "xno"; then

    if test "x$LEX" != "xflex"; then
       AC_MSG_ERROR([Flex is required for enable-generate-parser, but was not found])
    fi

    if test "x$YACC" = "x"; then
       AC_MSG_ERROR([Bison is required for enable-generate-parser, but was not found])
    fi

# Let's check if we have at least 3.3.0 version of the bison. The
# api.parser.class is available with 3.2.91, but let's be safe and offer support
# for minor versions, as opposed to patch versions.
   cat > bisontest.y << EOF
%require "3.3.0"
%token X
%%
%start Y;
Y: X;
EOF
# Try to compile.
    $YACC bisontest.y -o bisontest.cc

    if test $? -ne 0 ; then
        $YACC -V
        $RM -f bisontest.y bisontest.cc
        AC_MSG_ERROR("Error with $YACC. Possibly incorrect version? Required at least 3.3.0.")
    fi
    $RM -f bisontest.y bisontest.cc
fi

AM_CONDITIONAL([GENERATE_PARSER], [test x$enable_generate_parser != xno])

# Kea-shell is written in python. It can work with python 2.7 or any 3.x.
# It may likely work with earlier versions, but 2.7 was the oldest one we tested
# it with. We require python only if kea-shell was enabled. It is disabled
# by default to not introduce hard dependency on python.
AC_ARG_ENABLE(shell,
  [AS_HELP_STRING([--enable-shell],
    [enable kea-shell, a text management client for Control Agent [default=no]])],
  enable_shell=$enableval, enable_shell=no)


AC_ARG_ENABLE(generate_docs,
  [AS_HELP_STRING([--enable-generate-docs],
    [regenerate documentation using Sphinx [default=no]])],
  enable_generate_docs=$enableval, enable_generate_docs=no)


DISTCHECK_KEA_SHELL_CONFIGURE_FLAG=
PKGPYTHONDIR=
PYTHON_PREFIX=
PYTHON_EXEC_PREFIX=
shell_report=no
if test "x$enable_shell" != xno -o "x$enable_generate_docs" != xno; then

  # Temporarily replace NONE with the default prefix while --enable-shell is parsed.
  saved_prefix="$prefix"
  if test "$prefix" = "NONE"; then
    prefix=$ac_default_prefix
  fi

  # If kea-shell is enabled, we really need python. 2.7 or anything newer will do.
  # We try to find 3.x first. If not found, we can do with 2.7.
  m4_define_default([_AM_PYTHON_INTERPRETER_LIST],
                    [python3 python python2])
  AM_PATH_PYTHON([2.7])

  # Determine if the --with-site-packages flag was provided.
  AC_ARG_WITH(site-packages,
              [AS_HELP_STRING([--with-site-packages],
                              [place to install Kea Python module])],
              [with_site_packages="${withval}"])

  if test -z "${with_site_packages}"; then
    # --with-site-packages not provided. Set a default location explicitly to
    # make sure it doesn't change based on external factors. The path resembles
    # what python set by default at the time of this writing.
    pythondir="${prefix}/lib/python${PYTHON_VERSION}/site-packages"

  elif test "${with_site_packages}" = 'yes'; then
    # --with-site-packages provided, but without a value. It's not clear what is meant.
    AC_MSG_ERROR([If enabled, site-packages must be specified explicitly, e.g. --with-site-packages=/usr/lib/python3/dist-packages])

  else
    # --with-site-packages provided with value. Override pythondir.
    pythondir="${with_site_packages}"
  fi

  # pythondir needs to be expanded.
  old=
  while test "${old}" != "${pythondir}"; do
    old="${pythondir}"
    eval pythondir="\"${old}\""
  done

  # Set variables used in makefiles.
  DISTCHECK_KEA_SHELL_CONFIGURE_FLAG="--enable-shell"
  PKGPYTHONDIR="${pythondir}/${PACKAGE_NAME}"
  PYTHON_PREFIX="${prefix}"
  PYTHON_EXEC_PREFIX="${prefix}"

  # Restore prefix.
  prefix="$saved_prefix"

  shell_report='yes'
else
  PYTHON=no
fi

# Export to makefiles the info whether we have shell enabled or not
AM_CONDITIONAL(KEA_SHELL, test x$enable_shell != xno)
AC_SUBST(DISTCHECK_KEA_SHELL_CONFIGURE_FLAG)
AC_SUBST(PKGPYTHONDIR)
AC_SUBST(PYTHON_PREFIX)
AC_SUBST(PYTHON_EXEC_PREFIX)

# Decide if TLS is supported.
tls_support=no
if test "x${CRYPTO_NAME}" = "xOpenSSL"; then
  tls_support=yes
fi
if test "x${CRYPTO_NAME}" = "xBotan" && test "x$BOTAN_BOOST" = "xyes"; then
  tls_support=yes
fi

# Decide if the shell TLS test can work.
### This will be simpler when Python 2 support will be dropped.
ca_tls_test=no
if test "x$enable_shell" != "xno"; then
  major=`echo $PYTHON_VERSION | cut -d '.' -f 1`
  if test "x$major" = "x3"; then
    ca_tls_test="$tls_support"
  else
    AC_MSG_WARN("python2 kea-shell does not support HTTPS")
  fi
fi
AM_CONDITIONAL(CA_TLS_TEST, test x$ca_tls_test != xno)

AC_ARG_WITH([sphinx],
  [AS_HELP_STRING([--with-sphinx=PATH],[path to sphinx-build tool])],
  [sphinx_path="$withval"])

AC_ARG_WITH([pdflatex],
  [AS_HELP_STRING([--with-pdflatex=PATH],[path to pdflatex tool])],
  [pdflatex_path="$withval"])
PDFLATEX=no

if test "x$enable_generate_docs" != xno ; then
  # Check for sphinx-build
  AC_MSG_CHECKING([for sphinx-build])
  if test -z "$sphinx_path"; then
     AC_PATH_PROGS([SPHINXBUILD], [sphinx-build sphinx-build-3])
  else
     SPHINXBUILD="$sphinx_path"
  fi

  if test -z "$SPHINXBUILD"; then
    AC_MSG_ERROR([sphinx-build not found; it is required for --enable-generate-docs, please see http://www.sphinx-doc.org/en/master/usage/installation.html for details])
  else
    AC_MSG_RESULT([$SPHINXBUILD])

    AC_MSG_CHECKING([whether $SPHINXBUILD is runnable])
    $SPHINXBUILD --version > conftest.err 2>&1
    if test $? -ne 0 ; then
      AC_MSG_ERROR([error with $SPHINXBUILD --version, check conftest.err for details])
    fi
    rm -f conftest.err
    AC_MSG_RESULT([yes])
  fi

  # Check for pdflatex
  if test -z "$pdflatex_path"; then
     AC_PATH_PROG([PDFLATEX], [pdflatex])
  else
     PDFLATEX="$pdflatex_path"
  fi

  if test -z "$PDFLATEX"; then
    PDFLATEX=no
  elif test "x$PDFLATEX" = "xno"; then
    AC_MSG_CHECKING([for pdflatex])
    AC_MSG_RESULT([no (disabled)])
  else
    AC_MSG_CHECKING([whether $PDFLATEX is runnable])
    $PDFLATEX --version > /dev/null 2>&1
    if test $? -ne 0 ; then
      AC_MSG_RESULT([no - disabled building docs in PDF])
      PDFLATEX=no
    else
      AC_MSG_RESULT([yes])
    fi
  fi

  if test -n "$SPHINXBUILD" -a "x$PDFLATEX" != "xno"; then
    AC_MSG_CHECKING([whether $SPHINXBUILD and $PDFLATEX work])
    ti=`mktemp -d`
    to=`mktemp -d`
    oldpath=`pwd`
    echo 'hello' > $ti/contents.rst
    $SPHINXBUILD -b latex -C $ti $to > /dev/null 2>&1
    cd $to > /dev/null 2>&1
    $PDFLATEX -interaction nonstopmode [[pP]]ython.tex > /dev/null 2>&1
    cd $oldpath > /dev/null 2>&1
    file $to/[[pP]]ython.pdf | grep PDF > /dev/null 2>&1
    if test $? -ne 0 ; then
      AC_MSG_RESULT([no - disabled building docs in PDF])
      PDFLATEX=no
    else
      AC_MSG_RESULT([ok])
    fi
    rm -rf $ti $to
  fi

  if test "x$PDFLATEX" != "xno"; then
    generate_docs_report="html, man and pdf"
  else
    generate_docs_report="html, man but no pdf"
  fi
  install_mans="no"
else
  # now let's check if there are some existing manuals
  # checking just one is sufficient
  if test -f `pwd`/doc/sphinx/_build/man/kea-dhcp6.8; then
    install_mans="yes"
  else
    install_mans="no"
  fi
  generate_docs_report="no"
fi
AM_CONDITIONAL(INSTALL_MANS, test "x$install_mans" == "xyes")
AM_CONDITIONAL(HAVE_PDFLATEX, test "x$PDFLATEX" != "xno")
AM_CONDITIONAL(GENERATE_DOCS, test x$enable_generate_docs != xno)

AC_ARG_ENABLE(install-configurations,
  [AS_HELP_STRING([--disable-install-configurations],
  [do not install configuration])], install_configurations=$enableval, install_configurations=yes)

AM_CONDITIONAL(INSTALL_CONFIGURATIONS, test x$install_configurations = xyes || test x$install_configurations = xtrue)

AC_ARG_ENABLE(logger-checks,
  [AS_HELP_STRING([--enable-logger-checks],
  [check logger messages [default=no]])], enable_logger_checks=$enableval, enable_logger_checks=no)
AM_CONDITIONAL(ENABLE_LOGGER_CHECKS, test x$enable_logger_checks != xno)
AM_COND_IF([ENABLE_LOGGER_CHECKS], [AC_DEFINE([ENABLE_LOGGER_CHECKS], [1], [Check logger messages?])])

# Check for asciidoc
AC_PATH_PROG(ASCIIDOC, asciidoc, no)
AM_CONDITIONAL(HAVE_ASCIIDOC, test "x$ASCIIDOC" != "xno")

# Check for plantuml
AC_PATH_PROG(PLANTUML, plantuml, no)
AM_CONDITIONAL(HAVE_PLANTUML, test "x$PLANTUML" != "xno")

# Check for valgrind
AC_PATH_PROG(VALGRIND, valgrind, no)
AM_CONDITIONAL(HAVE_VALGRIND, test "x$VALGRIND" != "xno")

# Also check for valgrind headers
# We could consider adding them to the source code tree, as this
# is the encouraged method of using them; they are BSD-licensed.
# However, until we find that this is a problem, we just use
# the system-provided ones, if available
AC_CHECK_HEADERS(valgrind/valgrind.h, [AC_DEFINE([HAVE_VALGRIND_HEADERS], [1], [Check valgrind headers])])

found_valgrind="not found"
if test "x$VALGRIND" != "xno"; then
   found_valgrind="found"
fi

AC_ARG_ENABLE([fuzzing],
  [AS_HELP_STRING([--enable-fuzzing],
  [indicates that the code will be built with AFL (American Fuzzy Lop) support.
   Code built this way is unusable as a regular server. [default=no]])],
  [enable_fuzzing=$enableval], [enable_fuzzing=no])
AM_CONDITIONAL([ENABLE_AFL], [test x$enable_fuzzing != xno])

if test "x$enable_fuzzing" != "xno" ; then
    AC_DEFINE([ENABLE_AFL], [1], [AFL fuzzing was enabled.])
    AC_MSG_CHECKING([for AFL enabled compiler])
    AC_COMPILE_IFELSE([AC_LANG_PROGRAM([],
                                          [#ifndef __AFL_COMPILER
                                           #error AFL compiler required
                                           #endif
                                          ])],
                         [AC_MSG_RESULT([yes])],
                         [AC_MSG_ERROR([set CXX to afl-clang-fast++ when --enable-fuzzing is used])])
fi


# Check for optreset in unistd.h. On BSD systems the optreset is
# used to reset the state of getopt() function. Resetting its state
# is required if command line arguments are parsed multiple times
# during a program. On Linux this variable will not exist because
# getopt() reset is performed by setting optind = 0. On Operating
# Systems where optreset is defined use optreset = 1 and optind = 1
# to reset internal state of getopt(). Failing to do so will result
# in unpredictable output from getopt().
AC_MSG_CHECKING([whether optreset variable is defined in unistd.h])
AC_LINK_IFELSE(
  [AC_LANG_PROGRAM([[
    #include <unistd.h>
  ]], [[
    extern int optreset;
    optreset=1;
  ]])],
  [AC_MSG_RESULT(yes)
   var_optreset_exists=yes],
  [AC_MSG_RESULT(no)
   var_optreset_exists=no]
)
AM_CONDITIONAL(HAVE_OPTRESET, test "x$var_optreset_exists" != "xno")
AM_COND_IF([HAVE_OPTRESET], [AC_DEFINE([HAVE_OPTRESET], [1], [Check for optreset?])])

# GSS-API (from bind9)
AX_GSS_API

AC_DEFINE([CONFIG_H_WAS_INCLUDED], [1], [config.h inclusion marker])

# Autoconf 2.70 has runstatedir.
m4_version_prereq([2.70], [], [dnl
    AC_ARG_VAR(runstatedir, [$localstatedir/run for autoconf < 2.70])dnl
    AC_SUBST(runstatedir)dnl
])
if test "x$runstatedir" = "x"; then
    runstatedir="$localstatedir/run"
fi

# Expand runstatedir to remove ${localstatedir} from it
if (echo ${runstatedir} | grep -q localstatedir); then
    runstatedir="$(eval echo ${runstatedir})"
fi

AC_CONFIG_FILES([Makefile])
AC_CONFIG_FILES([doc/Makefile])
AC_CONFIG_FILES([doc/sphinx/Makefile])
AC_CONFIG_FILES([doc/devel/Makefile])
AC_CONFIG_FILES([ext/Makefile])
AC_CONFIG_FILES([ext/gtest/Makefile])
AC_CONFIG_FILES([ext/coroutine/Makefile])
AC_CONFIG_FILES([kea_version.h])
AC_CONFIG_FILES([m4macros/Makefile])
AC_CONFIG_FILES([src/Makefile])
AC_CONFIG_FILES([src/bin/Makefile])
AC_CONFIG_FILES([src/bin/admin/Makefile])
AC_CONFIG_FILES([src/bin/admin/admin-utils.sh])
AC_CONFIG_FILES([src/bin/admin/kea-admin],
                [chmod +x src/bin/admin/kea-admin])
AC_CONFIG_FILES([src/bin/admin/tests/Makefile])
AC_CONFIG_FILES([src/bin/admin/tests/data/Makefile])
AC_CONFIG_FILES([src/bin/admin/tests/admin_tests.sh],
                [chmod +x src/bin/admin/tests/admin_tests.sh])
AC_CONFIG_FILES([src/bin/admin/tests/memfile_tests.sh],
                [chmod +x src/bin/admin/tests/memfile_tests.sh])
AC_CONFIG_FILES([src/bin/admin/tests/mysql_tests.sh],
                [chmod +x src/bin/admin/tests/mysql_tests.sh])
AC_CONFIG_FILES([src/bin/admin/tests/pgsql_tests.sh],
                [chmod +x src/bin/admin/tests/pgsql_tests.sh])
AC_CONFIG_FILES([src/bin/agent/Makefile])
AC_CONFIG_FILES([src/bin/agent/tests/Makefile])
AC_CONFIG_FILES([src/bin/agent/tests/ca_process_tests.sh],
                [chmod +x src/bin/agent/tests/ca_process_tests.sh])
AC_CONFIG_FILES([src/bin/agent/tests/test_basic_auth_libraries.h])
AC_CONFIG_FILES([src/bin/agent/tests/test_callout_libraries.h])
AC_CONFIG_FILES([src/bin/agent/tests/test_data_files_config.h])
AC_CONFIG_FILES([src/bin/d2/Makefile])
AC_CONFIG_FILES([src/bin/d2/tests/Makefile])
AC_CONFIG_FILES([src/bin/d2/tests/d2_process_tests.sh],
                [chmod +x src/bin/d2/tests/d2_process_tests.sh])
AC_CONFIG_FILES([src/bin/d2/tests/test_callout_libraries.h])
AC_CONFIG_FILES([src/bin/d2/tests/test_configured_libraries.h])
AC_CONFIG_FILES([src/bin/d2/tests/test_data_files_config.h])
AC_CONFIG_FILES([src/bin/dhcp4/Makefile])
AC_CONFIG_FILES([src/bin/dhcp4/tests/Makefile])
AC_CONFIG_FILES([src/bin/dhcp4/tests/dhcp4_process_tests.sh],
                [chmod +x src/bin/dhcp4/tests/dhcp4_process_tests.sh])
AC_CONFIG_FILES([src/bin/dhcp4/tests/marker_file.h])
AC_CONFIG_FILES([src/bin/dhcp4/tests/test_data_files_config.h])
AC_CONFIG_FILES([src/bin/dhcp4/tests/test_libraries.h])
AC_CONFIG_FILES([src/bin/dhcp6/Makefile])
AC_CONFIG_FILES([src/bin/dhcp6/tests/Makefile])
AC_CONFIG_FILES([src/bin/dhcp6/tests/dhcp6_process_tests.sh],
                [chmod +x src/bin/dhcp6/tests/dhcp6_process_tests.sh])
AC_CONFIG_FILES([src/bin/dhcp6/tests/marker_file.h])
AC_CONFIG_FILES([src/bin/dhcp6/tests/test_data_files_config.h])
AC_CONFIG_FILES([src/bin/dhcp6/tests/test_libraries.h])
AC_CONFIG_FILES([src/bin/keactrl/Makefile])
AC_CONFIG_FILES([src/bin/keactrl/keactrl],
                [chmod +x src/bin/keactrl/keactrl])
AC_CONFIG_FILES([src/bin/keactrl/keactrl.conf])
AC_CONFIG_FILES([src/bin/keactrl/tests/Makefile])
AC_CONFIG_FILES([src/bin/keactrl/tests/keactrl_tests.sh],
                [chmod +x src/bin/keactrl/tests/keactrl_tests.sh])
AC_CONFIG_FILES([src/bin/lfc/Makefile])
AC_CONFIG_FILES([src/bin/lfc/tests/Makefile])
AC_CONFIG_FILES([src/bin/netconf/Makefile])
AC_CONFIG_FILES([src/bin/netconf/tests/Makefile])
AC_CONFIG_FILES([src/bin/netconf/tests/shtests/Makefile])
AC_CONFIG_FILES([src/bin/netconf/tests/shtests/netconf_tests.sh],
                [chmod +x src/bin/netconf/tests/shtests/netconf_tests.sh])
AC_CONFIG_FILES([src/bin/netconf/tests/test_data_files_config.h])
AC_CONFIG_FILES([src/bin/netconf/tests/test_libraries.h])
AC_CONFIG_FILES([src/bin/perfdhcp/Makefile])
AC_CONFIG_FILES([src/bin/perfdhcp/tests/Makefile])
AC_CONFIG_FILES([src/bin/perfdhcp/tests/testdata/Makefile])
AC_CONFIG_FILES([src/bin/shell/Makefile])
AC_CONFIG_FILES([src/bin/shell/kea-shell],
                [chmod +x src/bin/shell/kea-shell])
AC_CONFIG_FILES([src/bin/shell/tests/Makefile])
AC_CONFIG_FILES([src/bin/shell/tests/basic_auth_tests.sh],
                [chmod +x src/bin/shell/tests/basic_auth_tests.sh])
AC_CONFIG_FILES([src/bin/shell/tests/shell_process_tests.sh],
                [chmod +x src/bin/shell/tests/shell_process_tests.sh])
AC_CONFIG_FILES([src/bin/shell/tests/shell_unittest.py],
                [chmod +x src/bin/shell/tests/shell_unittest.py])
AC_CONFIG_FILES([src/bin/shell/tests/tls_ca_process_tests.sh],
                [chmod +x src/bin/shell/tests/tls_ca_process_tests.sh])
AC_CONFIG_FILES([src/hooks/Makefile])
AC_CONFIG_FILES([src/hooks/dhcp/Makefile])
AC_CONFIG_FILES([src/hooks/dhcp/bootp/Makefile])
AC_CONFIG_FILES([src/hooks/dhcp/bootp/libloadtests/Makefile])
AC_CONFIG_FILES([src/hooks/dhcp/bootp/tests/Makefile])
AC_CONFIG_FILES([src/hooks/dhcp/flex_option/Makefile])
AC_CONFIG_FILES([src/hooks/dhcp/flex_option/libloadtests/Makefile])
AC_CONFIG_FILES([src/hooks/dhcp/flex_option/tests/Makefile])
AC_CONFIG_FILES([src/hooks/dhcp/high_availability/Makefile])
AC_CONFIG_FILES([src/hooks/dhcp/high_availability/libloadtests/Makefile])
AC_CONFIG_FILES([src/hooks/dhcp/high_availability/tests/Makefile])
AC_CONFIG_FILES([src/hooks/dhcp/lease_cmds/Makefile])
AC_CONFIG_FILES([src/hooks/dhcp/lease_cmds/libloadtests/Makefile])
AC_CONFIG_FILES([src/hooks/dhcp/lease_cmds/tests/Makefile])
AC_CONFIG_FILES([src/hooks/dhcp/mysql_cb/Makefile])
AC_CONFIG_FILES([src/hooks/dhcp/mysql_cb/libloadtests/Makefile])
AC_CONFIG_FILES([src/hooks/dhcp/mysql_cb/tests/Makefile])
AC_CONFIG_FILES([src/hooks/dhcp/pgsql_cb/Makefile])
AC_CONFIG_FILES([src/hooks/dhcp/pgsql_cb/libloadtests/Makefile])
AC_CONFIG_FILES([src/hooks/dhcp/pgsql_cb/tests/Makefile])
AC_CONFIG_FILES([src/hooks/dhcp/run_script/Makefile])
AC_CONFIG_FILES([src/hooks/dhcp/run_script/libloadtests/Makefile])
AC_CONFIG_FILES([src/hooks/dhcp/run_script/tests/Makefile])
AC_CONFIG_FILES([src/hooks/dhcp/run_script/tests/run_script_test.sh],
                [chmod +x src/hooks/dhcp/run_script/tests/run_script_test.sh])
AC_CONFIG_FILES([src/hooks/dhcp/stat_cmds/Makefile])
AC_CONFIG_FILES([src/hooks/dhcp/stat_cmds/libloadtests/Makefile])
AC_CONFIG_FILES([src/hooks/dhcp/stat_cmds/tests/Makefile])
AC_CONFIG_FILES([src/hooks/dhcp/user_chk/Makefile])
AC_CONFIG_FILES([src/hooks/dhcp/user_chk/tests/Makefile])
AC_CONFIG_FILES([src/hooks/dhcp/user_chk/tests/test_data_files_config.h])
AC_CONFIG_FILES([src/lib/Makefile])
AC_CONFIG_FILES([src/lib/asiodns/Makefile])
AC_CONFIG_FILES([src/lib/asiodns/tests/Makefile])
AC_CONFIG_FILES([src/lib/asiolink/Makefile])
AC_CONFIG_FILES([src/lib/asiolink/testutils/Makefile])
AC_CONFIG_FILES([src/lib/asiolink/tests/Makefile])
AC_CONFIG_FILES([src/lib/asiolink/tests/process_spawn_app.sh],
                [chmod +x src/lib/asiolink/tests/process_spawn_app.sh])
AC_CONFIG_FILES([src/lib/cc/Makefile])
AC_CONFIG_FILES([src/lib/cc/tests/Makefile])
AC_CONFIG_FILES([src/lib/config/Makefile])
AC_CONFIG_FILES([src/lib/config/tests/Makefile])
AC_CONFIG_FILES([src/lib/config/tests/data_def_unittests_config.h])
AC_CONFIG_FILES([src/lib/config/tests/testdata/Makefile])
AC_CONFIG_FILES([src/lib/config_backend/Makefile])
AC_CONFIG_FILES([src/lib/config_backend/tests/Makefile])
AC_CONFIG_FILES([src/lib/cryptolink/Makefile])
AC_CONFIG_FILES([src/lib/cryptolink/tests/Makefile])
AC_CONFIG_FILES([src/lib/d2srv/Makefile])
AC_CONFIG_FILES([src/lib/d2srv/testutils/Makefile])
AC_CONFIG_FILES([src/lib/d2srv/tests/Makefile])
AC_CONFIG_FILES([src/lib/database/Makefile])
AC_CONFIG_FILES([src/lib/database/tests/Makefile])
AC_CONFIG_FILES([src/lib/database/testutils/Makefile])
AC_CONFIG_FILES([src/lib/dhcp/Makefile])
AC_CONFIG_FILES([src/lib/dhcp/tests/Makefile])
AC_CONFIG_FILES([src/lib/dhcp_ddns/Makefile])
AC_CONFIG_FILES([src/lib/dhcp_ddns/tests/Makefile])
AC_CONFIG_FILES([src/lib/dhcpsrv/Makefile])
AC_CONFIG_FILES([src/lib/dhcpsrv/tests/Makefile])
AC_CONFIG_FILES([src/lib/dhcpsrv/tests/test_libraries.h])
AC_CONFIG_FILES([src/lib/dhcpsrv/testutils/Makefile])
AC_CONFIG_FILES([src/lib/dns/Makefile])
AC_CONFIG_FILES([src/lib/dns/gen-rdatacode.py],
                [chmod +x src/lib/dns/gen-rdatacode.py])
AC_CONFIG_FILES([src/lib/dns/tests/Makefile])
AC_CONFIG_FILES([src/lib/dns/tests/testdata/Makefile])
AC_CONFIG_FILES([src/lib/eval/Makefile])
AC_CONFIG_FILES([src/lib/eval/tests/Makefile])
AC_CONFIG_FILES([src/lib/exceptions/Makefile])
AC_CONFIG_FILES([src/lib/exceptions/tests/Makefile])
AC_CONFIG_FILES([src/lib/hooks/Makefile])
AC_CONFIG_FILES([src/lib/hooks/tests/Makefile])
AC_CONFIG_FILES([src/lib/hooks/tests/marker_file.h])
AC_CONFIG_FILES([src/lib/hooks/tests/test_libraries.h])
AC_CONFIG_FILES([src/lib/http/Makefile])
AC_CONFIG_FILES([src/lib/http/tests/Makefile])
AC_CONFIG_FILES([src/lib/log/Makefile])
AC_CONFIG_FILES([src/lib/log/compiler/Makefile])
AC_CONFIG_FILES([src/lib/log/interprocess/Makefile])
AC_CONFIG_FILES([src/lib/log/interprocess/tests/Makefile])
AC_CONFIG_FILES([src/lib/log/tests/Makefile])
AC_CONFIG_FILES([src/lib/log/tests/buffer_logger_test.sh],
                [chmod +x src/lib/log/tests/buffer_logger_test.sh])
AC_CONFIG_FILES([src/lib/log/tests/console_test.sh],
                [chmod +x src/lib/log/tests/console_test.sh])
AC_CONFIG_FILES([src/lib/log/tests/destination_test.sh],
                [chmod +x src/lib/log/tests/destination_test.sh])
AC_CONFIG_FILES([src/lib/log/tests/init_logger_test.sh],
                [chmod +x src/lib/log/tests/init_logger_test.sh])
AC_CONFIG_FILES([src/lib/log/tests/local_file_test.sh],
                [chmod +x src/lib/log/tests/local_file_test.sh])
AC_CONFIG_FILES([src/lib/log/tests/logger_lock_test.sh],
                [chmod +x src/lib/log/tests/logger_lock_test.sh])
AC_CONFIG_FILES([src/lib/log/tests/severity_test.sh],
                [chmod +x src/lib/log/tests/severity_test.sh])
AC_CONFIG_FILES([src/lib/log/tests/tempdir.h])
AC_CONFIG_FILES([src/lib/mysql/Makefile])
AC_CONFIG_FILES([src/lib/mysql/testutils/Makefile])
AC_CONFIG_FILES([src/lib/mysql/tests/Makefile])
AC_CONFIG_FILES([src/lib/pgsql/Makefile])
AC_CONFIG_FILES([src/lib/pgsql/tests/Makefile])
AC_CONFIG_FILES([src/lib/pgsql/testutils/Makefile])
AC_CONFIG_FILES([src/lib/process/Makefile])
AC_CONFIG_FILES([src/lib/process/cfgrpt/Makefile])
AC_CONFIG_FILES([src/lib/process/cfgrpt/tests/Makefile])
AC_CONFIG_FILES([src/lib/process/tests/Makefile])
AC_CONFIG_FILES([src/lib/process/testutils/Makefile])
AC_CONFIG_FILES([src/lib/stats/Makefile])
AC_CONFIG_FILES([src/lib/stats/tests/Makefile])
AC_CONFIG_FILES([src/lib/stats/testutils/Makefile])
AC_CONFIG_FILES([src/lib/tcp/Makefile])
AC_CONFIG_FILES([src/lib/tcp/tests/Makefile])
AC_CONFIG_FILES([src/lib/testutils/Makefile])
AC_CONFIG_FILES([src/lib/testutils/dhcp_test_lib.sh],
                [chmod +x src/lib/testutils/dhcp_test_lib.sh])
AC_CONFIG_FILES([src/lib/testutils/xml_reporting_test_lib.sh],
                [chmod +x src/lib/testutils/xml_reporting_test_lib.sh])
AC_CONFIG_FILES([src/lib/util/Makefile])
AC_CONFIG_FILES([src/lib/util/io/Makefile])
AC_CONFIG_FILES([src/lib/util/python/Makefile])
AC_CONFIG_FILES([src/lib/util/python/gen_wiredata.py],
                [chmod +x src/lib/util/python/gen_wiredata.py])
AC_CONFIG_FILES([src/lib/util/tests/Makefile])
AC_CONFIG_FILES([src/lib/util/unittests/Makefile])
AC_CONFIG_FILES([src/lib/yang/Makefile])
AC_CONFIG_FILES([src/lib/yang/pretests/Makefile])
AC_CONFIG_FILES([src/lib/yang/tests/Makefile])
AC_CONFIG_FILES([src/lib/yang/testutils/Makefile])
AC_CONFIG_FILES([src/share/Makefile])
AC_CONFIG_FILES([src/share/api/Makefile])
AC_CONFIG_FILES([src/share/database/Makefile])
AC_CONFIG_FILES([src/share/database/scripts/Makefile])
AC_CONFIG_FILES([src/share/database/scripts/mysql/Makefile])
AC_CONFIG_FILES([src/share/database/scripts/mysql/upgrade_001.0_to_002.0.sh],
                [chmod +x src/share/database/scripts/mysql/upgrade_001.0_to_002.0.sh])
AC_CONFIG_FILES([src/share/database/scripts/mysql/upgrade_002.0_to_003.0.sh],
                [chmod +x src/share/database/scripts/mysql/upgrade_002.0_to_003.0.sh])
AC_CONFIG_FILES([src/share/database/scripts/mysql/upgrade_003.0_to_004.0.sh],
                [chmod +x src/share/database/scripts/mysql/upgrade_003.0_to_004.0.sh])
AC_CONFIG_FILES([src/share/database/scripts/mysql/upgrade_004.0_to_004.1.sh],
                [chmod +x src/share/database/scripts/mysql/upgrade_004.0_to_004.1.sh])
AC_CONFIG_FILES([src/share/database/scripts/mysql/upgrade_004.1_to_005.0.sh],
                [chmod +x src/share/database/scripts/mysql/upgrade_004.1_to_005.0.sh])
AC_CONFIG_FILES([src/share/database/scripts/mysql/upgrade_005.0_to_005.1.sh],
                [chmod +x src/share/database/scripts/mysql/upgrade_005.0_to_005.1.sh])
AC_CONFIG_FILES([src/share/database/scripts/mysql/upgrade_005.1_to_005.2.sh],
                [chmod +x src/share/database/scripts/mysql/upgrade_005.1_to_005.2.sh])
AC_CONFIG_FILES([src/share/database/scripts/mysql/upgrade_005.2_to_006.0.sh],
                [chmod +x src/share/database/scripts/mysql/upgrade_005.2_to_006.0.sh])
AC_CONFIG_FILES([src/share/database/scripts/mysql/upgrade_006.0_to_007.0.sh],
                [chmod +x src/share/database/scripts/mysql/upgrade_006.0_to_007.0.sh])
AC_CONFIG_FILES([src/share/database/scripts/mysql/upgrade_007.0_to_008.0.sh],
                [chmod +x src/share/database/scripts/mysql/upgrade_007.0_to_008.0.sh])
AC_CONFIG_FILES([src/share/database/scripts/mysql/upgrade_008.0_to_008.1.sh],
                [chmod +x src/share/database/scripts/mysql/upgrade_008.0_to_008.1.sh])
AC_CONFIG_FILES([src/share/database/scripts/mysql/upgrade_008.1_to_008.2.sh],
                [chmod +x src/share/database/scripts/mysql/upgrade_008.1_to_008.2.sh])
AC_CONFIG_FILES([src/share/database/scripts/mysql/upgrade_008.2_to_009.0.sh],
                [chmod +x src/share/database/scripts/mysql/upgrade_008.2_to_009.0.sh])
AC_CONFIG_FILES([src/share/database/scripts/mysql/upgrade_009.0_to_009.1.sh],
                [chmod +x src/share/database/scripts/mysql/upgrade_009.0_to_009.1.sh])
AC_CONFIG_FILES([src/share/database/scripts/mysql/upgrade_009.1_to_009.2.sh],
                [chmod +x src/share/database/scripts/mysql/upgrade_009.1_to_009.2.sh])
AC_CONFIG_FILES([src/share/database/scripts/mysql/upgrade_009.2_to_009.3.sh],
                [chmod +x src/share/database/scripts/mysql/upgrade_009.2_to_009.3.sh])
AC_CONFIG_FILES([src/share/database/scripts/mysql/upgrade_009.3_to_009.4.sh],
                [chmod +x src/share/database/scripts/mysql/upgrade_009.3_to_009.4.sh])
AC_CONFIG_FILES([src/share/database/scripts/mysql/upgrade_009.4_to_009.5.sh],
                [chmod +x src/share/database/scripts/mysql/upgrade_009.4_to_009.5.sh])
AC_CONFIG_FILES([src/share/database/scripts/mysql/upgrade_009.5_to_009.6.sh],
                [chmod +x src/share/database/scripts/mysql/upgrade_009.5_to_009.6.sh])
AC_CONFIG_FILES([src/share/database/scripts/mysql/upgrade_009.6_to_010.0.sh],
                [chmod +x src/share/database/scripts/mysql/upgrade_009.6_to_010.0.sh])
AC_CONFIG_FILES([src/share/database/scripts/mysql/upgrade_010_to_011.sh],
                [chmod +x src/share/database/scripts/mysql/upgrade_010_to_011.sh])
AC_CONFIG_FILES([src/share/database/scripts/mysql/upgrade_011_to_012.sh],
                [chmod +x src/share/database/scripts/mysql/upgrade_011_to_012.sh])
AC_CONFIG_FILES([src/share/database/scripts/mysql/upgrade_012_to_013.sh],
                [chmod +x src/share/database/scripts/mysql/upgrade_012_to_013.sh])
AC_CONFIG_FILES([src/share/database/scripts/mysql/upgrade_013_to_014.sh],
                [chmod +x src/share/database/scripts/mysql/upgrade_013_to_014.sh])
AC_CONFIG_FILES([src/share/database/scripts/mysql/upgrade_014_to_015.sh],
                [chmod +x src/share/database/scripts/mysql/upgrade_014_to_015.sh])
AC_CONFIG_FILES([src/share/database/scripts/mysql/upgrade_015_to_016.sh],
                [chmod +x src/share/database/scripts/mysql/upgrade_015_to_016.sh])
AC_CONFIG_FILES([src/share/database/scripts/mysql/upgrade_016_to_017.sh],
                [chmod +x src/share/database/scripts/mysql/upgrade_016_to_017.sh])
AC_CONFIG_FILES([src/share/database/scripts/mysql/upgrade_017_to_018.sh],
                [chmod +x src/share/database/scripts/mysql/upgrade_017_to_018.sh])
AC_CONFIG_FILES([src/share/database/scripts/mysql/upgrade_018_to_019.sh],
                [chmod +x src/share/database/scripts/mysql/upgrade_018_to_019.sh])
AC_CONFIG_FILES([src/share/database/scripts/mysql/wipe_data.sh],
                [chmod +x src/share/database/scripts/mysql/wipe_data.sh])
AC_CONFIG_FILES([src/share/database/scripts/pgsql/Makefile])
AC_CONFIG_FILES([src/share/database/scripts/pgsql/upgrade_001.0_to_002.0.sh],
                [chmod +x src/share/database/scripts/pgsql/upgrade_001.0_to_002.0.sh])
AC_CONFIG_FILES([src/share/database/scripts/pgsql/upgrade_002.0_to_003.0.sh],
                [chmod +x src/share/database/scripts/pgsql/upgrade_002.0_to_003.0.sh])
AC_CONFIG_FILES([src/share/database/scripts/pgsql/upgrade_003.0_to_003.1.sh],
                [chmod +x src/share/database/scripts/pgsql/upgrade_003.0_to_003.1.sh])
AC_CONFIG_FILES([src/share/database/scripts/pgsql/upgrade_003.1_to_003.2.sh],
                [chmod +x src/share/database/scripts/pgsql/upgrade_003.1_to_003.2.sh])
AC_CONFIG_FILES([src/share/database/scripts/pgsql/upgrade_003.2_to_003.3.sh],
                [chmod +x src/share/database/scripts/pgsql/upgrade_003.2_to_003.3.sh])
AC_CONFIG_FILES([src/share/database/scripts/pgsql/upgrade_003.3_to_004.0.sh],
                [chmod +x src/share/database/scripts/pgsql/upgrade_003.3_to_004.0.sh])
AC_CONFIG_FILES([src/share/database/scripts/pgsql/upgrade_004.0_to_005.0.sh],
                [chmod +x src/share/database/scripts/pgsql/upgrade_004.0_to_005.0.sh])
AC_CONFIG_FILES([src/share/database/scripts/pgsql/upgrade_005.0_to_005.1.sh],
                [chmod +x src/share/database/scripts/pgsql/upgrade_005.0_to_005.1.sh])
AC_CONFIG_FILES([src/share/database/scripts/pgsql/upgrade_005.1_to_006.0.sh],
                [chmod +x src/share/database/scripts/pgsql/upgrade_005.1_to_006.0.sh])
AC_CONFIG_FILES([src/share/database/scripts/pgsql/upgrade_006.0_to_006.1.sh],
                [chmod +x src/share/database/scripts/pgsql/upgrade_006.0_to_006.1.sh])
AC_CONFIG_FILES([src/share/database/scripts/pgsql/upgrade_006.1_to_006.2.sh],
                [chmod +x src/share/database/scripts/pgsql/upgrade_006.1_to_006.2.sh])
AC_CONFIG_FILES([src/share/database/scripts/pgsql/upgrade_006.2_to_007.0.sh],
                [chmod +x src/share/database/scripts/pgsql/upgrade_006.2_to_007.0.sh])
AC_CONFIG_FILES([src/share/database/scripts/pgsql/upgrade_007_to_008.sh],
                [chmod +x src/share/database/scripts/pgsql/upgrade_007_to_008.sh])
AC_CONFIG_FILES([src/share/database/scripts/pgsql/upgrade_008_to_009.sh],
                [chmod +x src/share/database/scripts/pgsql/upgrade_008_to_009.sh])
AC_CONFIG_FILES([src/share/database/scripts/pgsql/upgrade_009_to_010.sh],
                [chmod +x src/share/database/scripts/pgsql/upgrade_009_to_010.sh])
AC_CONFIG_FILES([src/share/database/scripts/pgsql/upgrade_010_to_011.sh],
                [chmod +x src/share/database/scripts/pgsql/upgrade_010_to_011.sh])
AC_CONFIG_FILES([src/share/database/scripts/pgsql/upgrade_011_to_012.sh],
                [chmod +x src/share/database/scripts/pgsql/upgrade_011_to_012.sh])
AC_CONFIG_FILES([src/share/database/scripts/pgsql/upgrade_012_to_013.sh],
                [chmod +x src/share/database/scripts/pgsql/upgrade_012_to_013.sh])
AC_CONFIG_FILES([src/share/database/scripts/pgsql/upgrade_013_to_014.sh],
                [chmod +x src/share/database/scripts/pgsql/upgrade_013_to_014.sh])
AC_CONFIG_FILES([src/share/database/scripts/pgsql/upgrade_014_to_015.sh],
                [chmod +x src/share/database/scripts/pgsql/upgrade_014_to_015.sh])
AC_CONFIG_FILES([src/share/database/scripts/pgsql/upgrade_015_to_016.sh],
                [chmod +x src/share/database/scripts/pgsql/upgrade_015_to_016.sh])
AC_CONFIG_FILES([src/share/database/scripts/pgsql/upgrade_016_to_017.sh],
                [chmod +x src/share/database/scripts/pgsql/upgrade_016_to_017.sh])
AC_CONFIG_FILES([src/share/database/scripts/pgsql/upgrade_017_to_018.sh],
                [chmod +x src/share/database/scripts/pgsql/upgrade_017_to_018.sh])
AC_CONFIG_FILES([src/share/database/scripts/pgsql/wipe_data.sh],
                [chmod +x src/share/database/scripts/pgsql/wipe_data.sh])
AC_CONFIG_FILES([src/share/yang/Makefile])
AC_CONFIG_FILES([src/share/yang/modules/Makefile])
AC_CONFIG_FILES([src/share/yang/modules/utils/Makefile])
AC_CONFIG_FILES([src/share/yang/modules/utils/check-hashes.sh],
                [chmod +x src/share/yang/modules/utils/check-hashes.sh])
AC_CONFIG_FILES([src/share/yang/modules/utils/check-revisions.sh],
                [chmod +x src/share/yang/modules/utils/check-revisions.sh])
AC_CONFIG_FILES([src/share/yang/modules/utils/reinstall.sh],
                [chmod +x src/share/yang/modules/utils/reinstall.sh])
AC_CONFIG_FILES([tools/Makefile])
AC_CONFIG_FILES([tools/path_replacer.sh],
                [chmod +x tools/path_replacer.sh])
AC_CONFIG_FILES([tools/extract_bnf.sh],
                [chmod +x tools/extract_bnf.sh])


AC_OUTPUT

dnl Print the results
dnl

EXTENDED_VERSION=${PACKAGE_VERSION}
if test "$KEA_SRCID" != ""; then
   EXTENDED_VERSION="${EXTENDED_VERSION} ($KEA_SRCID)"
fi

# By default the following variables are defined:
# - prefix = /usr/local
# - exec_prefix = ${prefix}
# - libdir = ${exec_prefix}/lib
# The exec_prefix and libdir variables contain unexpanded,literal ${prefix}.
# This is done on purpose. The idea is to be able to make this expansion
# late, so use can do:
# make install prefix=/my/own/prefix
#
# Now, we want to print those directories in the config.report, but we
# don't want to modify the actual variables. So we need to expand them.
# Since libdir contains $exec_prefix and exec_prefix contains $prefix, then
# to get the real value, we need to expand it twice.
libdir_real="$(eval echo ${libdir})"
libdir_real="$(eval echo ${libdir_real})"

cat > config.report << END

       Kea source configure results:
    -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

Package:
  Name:              ${PACKAGE_NAME}
  Version:           ${PACKAGE_VERSION}
  Extended version:  ${EXTENDED_VERSION}
  Version type:      ${PACKAGE_VERSION_TYPE}
  OS Family:         ${OS_TYPE}

  Prefix:            ${prefix}
  Hooks directory:   ${libdir_real}/kea/hooks
END
if test "$PREMIUM" != ""; then
cat >> config.report << END
  Premium hooks:     yes
  Included Hooks:   ${INCLUDED_HOOKS}
END
else
cat >> config.report << END
  Premium hooks:     no
END
fi

cat >> config.report << END

Configure arguments:
$ac_configure_args
END

cat >> config.report << END

C++ Compiler:
  CXX:             ${CXX}
  CXX_VERSION:     ${CXX_VERSION}
  CXX_STANDARD:    ${CXX_STANDARD}
  DEFS:            ${DEFS}
  CPPFLAGS:        ${CPPFLAGS}
  CXXFLAGS:        ${CXXFLAGS}
  LDFLAGS:         ${LDFLAGS}
  KEA_CXXFLAGS:    ${KEA_CXXFLAGS}
END

if test "$PYTHON" != "no" ; then
cat >> config.report << END

Python:
  PYTHON:               ${PYTHON}
  PYTHON_VERSION:       ${PYTHON_VERSION}
  PYTHON_PREFIX:        ${PYTHON_PREFIX}
  PYTHON_EXEC_PREFIX:   ${PYTHON_EXEC_PREFIX}
  PKGPYTHONDIR:         ${PKGPYTHONDIR}

END
else
cat >> config.report << END

Python:
  PYTHON_VERSION:  not needed (because kea-shell is disabled)

END
fi

cat >> config.report << END
Boost:
  BOOST_VERSION:   ${BOOST_VERSION}
  BOOST_INCLUDES:  ${BOOST_INCLUDES}
  BOOST_LIBS:      ${BOOST_LIBS}

END
if test x"$BOOST_LIBS" = "x"; then
   cat >> config.report << END
    WARNING: You will be building with boost headers only rather
    than linking with boost_system library. This is NOT recommended as
    it may result in non-optimized code on some platforms and
    introduce runtime errors on others.

END
fi

cat >> config.report << END
${CRYPTO_NAME}:
  CRYPTO_VERSION:  ${CRYPTO_VERSION}
  CRYPTO_CFLAGS:   ${CRYPTO_CFLAGS}
  CRYPTO_INCLUDES: ${CRYPTO_INCLUDES}
  CRYPTO_LDFLAGS:  ${CRYPTO_LDFLAGS}
  CRYPTO_LIBS:     ${CRYPTO_LIBS}
  TLS support:     $tls_support

${DISABLED_CRYPTO}: no

Log4cplus:
  LOG4CPLUS_VERSION:  ${LOG4CPLUS_VERSION}
  LOG4CPLUS_INCLUDES: ${LOG4CPLUS_INCLUDES}
  LOG4CPLUS_LIBS:     ${LOG4CPLUS_LIBS}

Flex/bison:
  FLEX:  ${LEX}
  BISON: ${YACC}
END

# Avoid confusion on DNS/DHCP and only mention MySQL if it
# were specified on the command line.
if test "$MYSQL_CPPFLAGS" != "" ; then
cat >> config.report << END

MySQL:
  MYSQL_VERSION:   ${MYSQL_VERSION}
  MYSQL_CPPFLAGS:  ${MYSQL_CPPFLAGS}
  MYSQL_LIBS:      ${MYSQL_LIBS}
END
else
cat >> config.report << END

MySQL:
  no
END
fi

if test "$PGSQL_CPPFLAGS" != "" ; then
cat >> config.report << END

PostgreSQL:
  PGSQL_VERSION:   ${PGSQL_VERSION}
  PGSQL_CPPFLAGS:  ${PGSQL_CPPFLAGS}
  PGSQL_LIBS:      ${PGSQL_LIBS}
END
else
cat >> config.report << END

PostgreSQL:
  no
END
fi

cat >> config.report << END

NETCONF:
  ${HAVE_NETCONF-no}
END

if test -n "${LIBYANG_VERSION}"; then
  cat >> config.report << END

  libyang:
    LIBYANG_CPPFLAGS:      ${LIBYANG_CPPFLAGS}
    LIBYANG_INCLUDEDIR:    ${LIBYANG_INCLUDEDIR}
    LIBYANG_LIBS:          ${LIBYANG_LIBS}
    LIBYANG_PREFIX:        ${LIBYANG_PREFIX}
    LIBYANG_VERSION:       ${LIBYANG_VERSION}
END
else
  cat >> config.report << END

  libyang:
    no
END
fi

if test -n "${LIBYANGCPP_VERSION}"; then
  cat >> config.report << END

  libyang-cpp:
    LIBYANGCPP_CPPFLAGS:   ${LIBYANGCPP_CPPFLAGS}
    LIBYANGCPP_INCLUDEDIR: ${LIBYANGCPP_INCLUDEDIR}
    LIBYANGCPP_LIBS:       ${LIBYANGCPP_LIBS}
    LIBYANGCPP_PREFIX:     ${LIBYANGCPP_PREFIX}
    LIBYANGCPP_VERSION:    ${LIBYANGCPP_VERSION}
END
else
  cat >> config.report << END

  libyang-cpp:
    no
END
fi

if test -n "${SYSREPO_VERSION}"; then
  cat >> config.report << END

  sysrepo:
    SYSREPO_CPPFLAGS:      ${SYSREPO_CPPFLAGS}
    SYSREPO_INCLUDEDIR:    ${SYSREPO_INCLUDEDIR}
    SYSREPO_LIBS:          ${SYSREPO_LIBS}
    SYSREPO_PREFIX:        ${SYSREPO_PREFIX}
    SYSREPO_VERSION:       ${SYSREPO_VERSION}

    SR_REPO_PATH:          ${SR_REPO_PATH}
    SR_PLUGINS_PATH:       ${SR_PLUGINS_PATH}
    SRPD_PLUGINS_PATH:     ${SRPD_PLUGINS_PATH}
END
else
  cat >> config.report << END

  sysrepo:
    no
END
fi

if test -n "${SYSREPOCPP_VERSION}"; then
  cat >> config.report << END

  sysrepo-cpp:
    SYSREPOCPP_CPPFLAGS:   ${SYSREPOCPP_CPPFLAGS}
    SYSREPOCPP_INCLUDEDIR: ${SYSREPOCPP_INCLUDEDIR}
    SYSREPOCPP_LIBS:       ${SYSREPOCPP_LIBS}
    SYSREPOCPP_PREFIX :    ${SYSREPOCPP_PREFIX}
    SYSREPOCPP_VERSION:    ${SYSREPOCPP_VERSION}
END
else
  cat >> config.report << END

  sysrepo-cpp:
    no
END
fi

if test "$enable_gtest" != "no"; then
cat >> config.report << END

Google Test:
  GTEST_VERSION:   ${GTEST_VERSION}
  GTEST_INCLUDES:  ${GTEST_INCLUDES}
  GTEST_LDFLAGS:   ${GTEST_LDFLAGS}
  GTEST_LDADD:     ${GTEST_LDADD}
  GTEST_SOURCE:    ${GTEST_SOURCE}
END
else
cat >> config.report << END

Google Test:
  no
END
fi

if test "$FREERADIUS_INCLUDE" != ""; then
cat >> config.report << END

FreeRADIUS client:
  FREERADIUS_INCLUDE:    ${FREERADIUS_INCLUDE}
  FREERADIUS_LIB:        ${FREERADIUS_LIB}
  FREERADIUS_DICTIONARY: ${FREERADIUS_DICTIONARY}
END
fi

if test "$ENABLE_GSSAPI" = "yes"; then
cat >> config.report << END

GSS-API support:
  GSSAPI_CFLAGS:         ${GSSAPI_CFLAGS}
  GSSAPI_LIBS:           ${GSSAPI_LIBS}
END
fi

cat >> config.report << END

Developer:
  Enable Debugging:          $debug_enabled
  Google Tests:              $enable_gtest
  Valgrind:                  $found_valgrind
  C++ Code Coverage:         $USE_LCOV
  Logger checks:             $enable_logger_checks
  Install existing manuals:  $install_mans
  Generate Documentation:    $generate_docs_report
  Generate Parser:           $enable_generate_parser
  Generate Messages Files:   $enable_generate_messages
  Perfdhcp:                  $enable_perfdhcp
  Kea-shell:                 $shell_report
  Enable fuzzing:            $enable_fuzzing

END

cat config.report
cat <<EOF

  Now you can type "make" to build Kea. Note that if you intend to
  run "make check", you must run "make" first as some files need to be
  generated by "make" before "make check" can be run.

  When running "make install" do not use any form of parallel or job
  server options (such as GNU make's -j option). Doing so may cause
  errors.
EOF
