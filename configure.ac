#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])

# For released versions, this is in x.y.z format.
# For GIT versions, this is x.y.z-git, where x.y.z denotes the software
# version that was used as a base + changes that were made later, but
# are not released yet.
AC_INIT(kea,1.5.0-git, kea-dev@lists.isc.org)
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

# Checks for programs.
AC_PROG_CXX

# Check for exact Kea version.
AC_MSG_CHECKING(whether this is a tarball or git source)
if test -d "${srcdir}/.git"; then
        KEA_SRCID="git `(cd "${top_srcdir}";git rev-parse HEAD)`"
        AC_MSG_RESULT("git")
else
        KEA_SRCID="tarball"
        AC_MSG_RESULT("tarball")
fi
# Export EXTENDED_VERSION to config.h
# This will be either "tarball" or "git abcd".
# We do not want to put this in a config.h, because it messes up ccache
# horribly. When building different branches, the commit-id is different
# and since the config.h is included in most files *and* has a different
# content, ccache can't use cached content and thus has to do full compilation.
# Now it is in kea_version.h and config.status substitutes it.
AC_SUBST(KEA_SRCID)

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

# Enable low-performing debugging facilities? This option optionally
# enables some debugging aids that perform slowly and hence aren't built
# by default.
AC_ARG_ENABLE([debug],
  AS_HELP_STRING([--enable-debug],
    [enable debugging (default is no)]),
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

# gcc/clang specific settings:
if test "X$GXX" = "Xyes"; then
CXX_VERSION=`$CXX --version 2> /dev/null | head -1`
KEA_CXXFLAGS="$KEA_CXXFLAGS -Wall -Wextra -Wnon-virtual-dtor -Wwrite-strings -Woverloaded-virtual -Wno-sign-compare"
# gcc 4.4 would emit warnings about breaking strict aliasing rules.
# See https://gcc.gnu.org/bugzilla/show_bug.cgi?id=41874
CXX_DUMP_VERSION=`$CXX -dumpversion | cut -f1-2 -d.`
if expr "$CXX_DUMP_VERSION" \< "4.5" > /dev/null; then
       WARNING_GCC_44_STRICT_ALIASING_CFLAG="-fno-strict-aliasing"
fi
AC_SUBST(WARNING_GCC_44_STRICT_ALIASING_CFLAG)
CPPP="$CPP"
# gcc 5 preprocessor requires -P for checking its output
if expr "$CXX_DUMP_VERSION" \> "5" > /dev/null; then
       CPPP="$CPP -P"
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
    AC_HELP_STRING([--with-werror], [Compile using -Werror (default=no)]),
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
   AC_TRY_COMPILE([namespace { struct Foo {}; }
   namespace isc {struct Bar {Foo foo_;};} ],,
        [AC_MSG_RESULT(no)
         werror_ok=1
         KEA_CXXFLAGS="$KEA_CXXFLAGS -Werror"],
        [AC_MSG_RESULT(yes)])
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
AC_HELP_STRING([--enable-static-link],
  [build programs with static link [[default=no]]]),
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
        AC_TRY_COMPILE(
        [#include <Availability.h>],
        [#ifdef __MAC_OS_X_VERSION_MIN_REQUIRED
         #if __MAC_OS_X_VERSION_MIN_REQUIRED >= 1090
         #error " OS X >= 10.9"
         #endif
         #endif
         return 1;],
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
AC_ARG_ENABLE(perfdhcp, [AC_HELP_STRING([--enable-perfdhcp],
  [enable perfdhcp, a DHCP benchmarking tool [default=no]])],
  enable_perfdhcp=$enableval, enable_perfdhcp=no)

DISTCHECK_PERFDHCP_CONFIGURE_FLAG=
if test "x$enable_perfdhcp" != xno ; then
  DISTCHECK_PERFDHCP_CONFIGURE_FLAG="--enable-perfdhcp"
fi

# Export to makefiles the info whether we have perfdhcp enabled or not
AM_CONDITIONAL(PERFDHCP, test x$enable_perfdhcp != xno)
AC_SUBST(DISTCHECK_PERFDHCP_CONFIGURE_FLAG)

# Kea-shell is written in python. It can work with python 2.7 or any 3.x.
# It may likely work with earlier versions, but 2.7 was the oldest one we tested
# it with. We require python only if kea-shell was enabled. It is disabled
# by default to not introduce hard dependency on python.
AC_ARG_ENABLE(shell, [AC_HELP_STRING([--enable-shell],
  [enable kea-shell, a text management client for Control Agent [default=no]])],
  enable_shell=$enableval, enable_shell=no)

DISTCHECK_KEA_SHELL_CONFIGURE_FLAG=
PKGPYTHONDIR=
m4_define_default([_AM_PYTHON_INTERPRETER_LIST],
 [python3 python3.9 python3.8 python3.7 python3.6 python3.5 python3.4 dnl
  python3.3 python3.2 python3.1 python3.0 python python2 python2.7])
if test "x$enable_shell" != xno ; then
# If kea-shell is enabled, we really need python. 2.7 or anything newer will do.
# We try to find 3.x first. If not found, we can do with 2.7.
  AM_PATH_PYTHON([2.7])
  # pkgpythondir needs to be expanded
  saved_prefix="$prefix"
  if test "$prefix" = "NONE"; then
    prefix=$ac_default_prefix
  fi
  PKGPYTHONDIR="$pkgpythondir"
  OLD=
  while test "x$OLD" != "x$PKGPYTHONDIR"; do
    OLD="$PKGPYTHONDIR"
    eval PKGPYTHONDIR="\"$OLD\""
  done
  prefix="$saved_prefix"
  DISTCHECK_KEA_SHELL_CONFIGURE_FLAG="--enable-shell"
else
  PYTHON=no
fi

# Export to makefiles the info whether we have shell enabled or not
AM_CONDITIONAL(KEA_SHELL, test x$enable_shell != xno)
AC_SUBST(DISTCHECK_KEA_SHELL_CONFIGURE_FLAG)
AC_SUBST(PKGPYTHONDIR)

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
AC_TRY_COMPILE([
#include <sys/types.h>
#include <sys/socket.h>],
[struct sockaddr sa; sa.sa_len = 0; return (0);],
        [AC_MSG_RESULT(yes)
        AC_DEFINE(HAVE_SA_LEN, 1, [Define to 1 if sockaddr has a sa_len member, and corresponding sin_len and sun_len])],
        AC_MSG_RESULT(no))

AC_MSG_CHECKING(for usuable C++11 regex)
AC_TRY_RUN([
#include <regex>
#include <iostream>
int main() {
  const std::regex regex(".*");
  const std::string string = "This should match!";
  const auto result = std::regex_search(string, regex);
  return result ? EXIT_SUCCESS : EXIT_FAILURE;
}],
        [AC_MSG_RESULT(yes)
        AC_DEFINE(USE_REGEX, 1, [Define to 1 if C++11 regex is usable])],
        AC_MSG_RESULT(no))

enable_gtest="no"
GTEST_INCLUDES=

AC_ARG_WITH([gtest-source],
            [AS_HELP_STRING([--with-gtest-source=PATH],
                            [location of the Googletest source])],
            [enable_gtest="yes" ; GTEST_SOURCE="$withval"])

AC_ARG_WITH([gtest],
            [AS_HELP_STRING([--with-gtest=PATH],
                            [specify a path to gtest header files (PATH/include) and library (PATH/lib)])],
        [gtest_path="$withval"; enable_gtest="yes"], [gtest_path="no"])

AC_ARG_WITH(lcov,
[  --with-lcov[=PROGRAM]         enable gtest and coverage target using the specified lcov], lcov="$withval", lcov="no")

USE_LCOV="no"
if test "$lcov" != "no"; then
        # force gtest if not set
        if test "$enable_gtest" = "no"; then
#               AC_MSG_ERROR("lcov needs gtest for test coverage report")
                AC_MSG_NOTICE([gtest support is now enabled, because used by coverage tests])
                enable_gtest="yes"
        fi
        if test "$lcov" != "yes"; then
                LCOV=$lcov
        else
                AC_PATH_PROG([LCOV], [lcov])
        fi
        if test -x "${LCOV}"; then
                USE_LCOV="yes"
        else
                AC_MSG_ERROR([Cannot find lcov.])
        fi
        # is genhtml always in the same directory?
        GENHTML=`echo "$LCOV" | ${SED} s/lcov$/genhtml/`
        if test ! -x $GENHTML; then
                AC_MSG_ERROR([genhtml not found, needed for lcov])
        fi
        # GCC specific?
        CXXFLAGS="$CXXFLAGS -fprofile-arcs -ftest-coverage"
        LIBS=" $LIBS -lgcov"
        AC_SUBST(CPPFLAGS)
        AC_SUBST(LIBS)
        AC_SUBST(LCOV)
        AC_SUBST(GENHTML)
fi
AC_SUBST(USE_LCOV)

enable_benchmark="no"
BENCHMARK_INCLUDES=

AC_ARG_WITH([benchmark-source],
            [AS_HELP_STRING([--with-benchmark-source=PATH],
                            [location of the benchmark source])],
            [enable_benchmark="yes" ; BENCHMARK_SOURCE="$withval"])

AC_ARG_WITH([benchmark],
            [AS_HELP_STRING([--with-benchmark=PATH],
                            [specify a path to benchmark header files (PATH/include) and library (PATH/lib)])],
        [benchmark_path="$withval"; enable_benchmark="yes"], [benchmark_path="no"])

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
  AC_HELP_STRING([--with-mysql=PATH],
    [path to the MySQL 'mysql_config' script (MySQL is used for the DHCP database)]),
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

if test "$MYSQL_CONFIG" != "" ; then
    if test -d "$MYSQL_CONFIG" -o ! -x "$MYSQL_CONFIG" ; then
        AC_MSG_ERROR([MySQL dependencies cannot be found. Please install MySQL libraries or point --with-mysql to mysql_config program if it is located in non-default directory, eg. --with-mysql=/opt/mysql/bin/mysql_config.])
    fi

    MYSQL_CPPFLAGS=`$MYSQL_CONFIG --cflags`
    MYSQL_LIBS=`$MYSQL_CONFIG --libs`
    MYSQL_VERSION=`$MYSQL_CONFIG --version`

    AC_SUBST(MYSQL_CPPFLAGS)
    AC_SUBST(MYSQL_LIBS)

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

    # Check is my_bool is defined.
    AC_COMPILE_IFELSE(
        [AC_LANG_PROGRAM([#include <mysql.h>
                          const my_bool MLM_FALSE = 0;]
                         [])],
        [AC_MSG_RESULT([checking for MySQL my_bool... yes])
         AC_DEFINE([HAVE_MYSQL_MY_BOOL], [1], [MySQL uses my_bool])],
        [AC_MSG_RESULT([checking for MySQL my_bool... no])])

    CPPFLAGS=$CPPFLAGS_SAVED
    LIBS=$LIBS_SAVED

fi

# Solaris puts FIONREAD in filio.h
AC_CHECK_HEADERS(sys/filio.h,,,)

# ... and at the shell level, so Makefile.am can take action depending on this.
AM_CONDITIONAL(HAVE_MYSQL, test "$MYSQL_CONFIG" != "")

pg_config="no"
AC_ARG_WITH([pgsql],
  AC_HELP_STRING([--with-pgsql=PATH],
    [path to the PostgreSQL 'pg_config' script]),
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

if test "$PG_CONFIG" != "" ; then
    if test -d "$PG_CONFIG" -o ! -x "$PG_CONFIG" ; then
        AC_MSG_ERROR([PostgreSQL dependencies cannot be found. Please install PostgreSQL libraries or point --with-pgsql to pg_config program if it is located in non-default directory, eg. --with-pgsql=/opt/pgsql/bin/pg_config.])
    fi

    PGSQL_CPPFLAGS=`$PG_CONFIG --cppflags`
    PGSQL_INCLUDEDIR=`$PG_CONFIG --includedir`
    PGSQL_INCLUDEDIR_SERVER=`$PG_CONFIG --includedir-server`
    PGSQL_CPPFLAGS="$PGSQL_CPPFLAGS -I$PGSQL_INCLUDEDIR -I$PGSQL_INCLUDEDIR_SERVER"
    PGSQL_LIBS=`$PG_CONFIG --libdir`
    PGSQL_LIBS="-L$PGSQL_LIBS -lpq"
    PGSQL_VERSION=`$PG_CONFIG --version`

    AC_SUBST(PGSQL_CPPFLAGS)
    AC_SUBST(PGSQL_LIBS)

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
fi

# ... and at the shell level, so Makefile.am can take action depending on this.
AM_CONDITIONAL(HAVE_PGSQL, test "$PG_CONFIG" != "")

# allow building kea programs with static link to cassandra cpp-driver.
AC_ARG_ENABLE([cql-static-lib],
AS_HELP_STRING([--enable-cql-static-lib],
    [build programs with cassandra cpp driver static library [[default=no]]]),
    [enable_cql_static_lib=yes], [enable_cql_static_lib=no])
AM_CONDITIONAL(USE_CQL_STATIC_LIB, test "$enable_cql_static_lib" = yes)
#AC_DEFINE USE_CQL_STATIC_LIB? (unused)

cql_lib="cassandra"
if test "${enable_cql_static_lib}" = "yes" ; then
    cql_lib="${cql_lib}_static"
fi

cql_config="no"
AC_ARG_WITH([cql],
  AC_HELP_STRING([--with-cql=PATH],
    [path to pkg-config or the Cassandra CQL 'cql_config' script]),
    [cql_config="$withval"])

if test "${cql_config}" = "yes" ; then
    CQL_CONFIG="$PKG_CONFIG"
elif test "${cql_config}" != "no" ; then
    CQL_CONFIG="${cql_config}"
fi

if test "$CQL_CONFIG" != "" ; then
    if test -d "$CQL_CONFIG" -o ! -x "$CQL_CONFIG" ; then
        AC_MSG_ERROR([--with-cql should point to a pkg-config or cql_config program])
    fi

    $CQL_CONFIG --print-errors $cql_lib
    if test $? -ne 0; then
        AC_MSG_ERROR([$CQL_CONFIG $cql_lib failed])
    fi

    CQL_INCLUDEDIR=`$CQL_CONFIG --cflags-only-I $cql_lib`
    CQL_CPPFLAGS="$CQL_INCLUDEDIR `$CQL_CONFIG --cflags-only-other $cql_lib`"
    CQL_LIBS="`$CQL_CONFIG --libs $cql_lib`"
    CQL_VERSION=`$CQL_CONFIG --modversion $cql_lib`

    AC_SUBST(CQL_CPPFLAGS)
    AC_SUBST(CQL_LIBS)

    # Check that a simple program using CQL functions can compile and link.
    CPPFLAGS_SAVED="$CPPFLAGS"
    LIBS_SAVED="$LIBS"

    CPPFLAGS="$CQL_CPPFLAGS $CPPFLAGS"
    LIBS="$CQL_LIBS $LIBS"

    AC_LINK_IFELSE(
            [AC_LANG_PROGRAM([#include <cassandra.h>],
                             [CassCluster* cluster = cass_cluster_new();
                              cass_cluster_free(cluster);])],
            [AC_MSG_RESULT([checking for Cassandra CQL headers and library... yes])],
            [AC_MSG_RESULT([checking for Cassandra CQL headers and library... no])
             AC_MSG_ERROR([Needs Cassandra CQL library])]
    )
    CPPFLAGS=$CPPFLAGS_SAVED
    LIBS=$LIBS_SAVED

    # Note that CQL is present in the config.h file
    AC_DEFINE([HAVE_CQL], [1], [CQL is present])
fi

# ... and at the shell level, so Makefile.am can take action depending on this.
AM_CONDITIONAL(HAVE_CQL, test "$CQL_CONFIG" != "")

DISTCHECK_SYSREPO_CONFIGURE_FLAG=
sysrepo_config="no"
AC_ARG_WITH([sysrepo],
  AC_HELP_STRING([--with-sysrepo=PATH],
    [path to pkg-config or the Sysrepo 'sysrepo_config' script]),
    [sysrepo_config="$withval"])

if test "${sysrepo_config}" = "yes" ; then
    SYSREPO_CONFIG="$PKG_CONFIG"
    DISTCHECK_SYSREPO_CONFIGURE_FLAG="-with-sysrepo=${sysrepo_config}"
elif test "${sysrepo_config}" != "no" ; then
    SYSREPO_CONFIG="${sysrepo_config}"
    DISTCHECK_SYSREPO_CONFIGURE_FLAG="-with-sysrepo=${sysrepo_config}"
fi
AC_SUBST(DISTCHECK_SYSREPO_CONFIGURE_FLAG)

if test "$SYSREPO_CONFIG" != "" ; then
    if test -d "$SYSREPO_CONFIG" -o ! -x "$SYSREPO_CONFIG" ; then
        AC_MSG_ERROR([--with-sysrepo should point to a pkg-config or sysrepo_config program])
    fi

    # Let's get the configuration environment for pure Sysrepo (written in C) first
    SYSREPO_INCLUDEDIR=`$SYSREPO_CONFIG --cflags-only-I libsysrepo`
    SYSREPO_CPPFLAGS="$SYSREPO_INCLUDEDIR `$SYSREPO_CONFIG --cflags-only-other libsysrepo`"
    SYSREPO_LIBS="`$SYSREPO_CONFIG --libs libsysrepo`"
    SYSREPO_VERSION=`$SYSREPO_CONFIG --modversion libsysrepo`
    SYSREPO_REPO=`$SYSREPO_CONFIG --variable=SR_REPOSITORY_LOC libsysrepo`

    # Now get the environment for C++ bindings for Sysrepo.
    SYSREPOCPP_INCLUDEDIR=`$SYSREPO_CONFIG --cflags-only-I libSysrepo-cpp`
    SYSREPOCPP_CPPFLAGS="$SYSREPO_INCLUDEDIR `$SYSREPO_CONFIG --cflags-only-other libSysrepo-cpp`"
    SYSREPOCPP_LIBS="`$SYSREPO_CONFIG --libs libSysrepo-cpp`"
    SYSREPOCPP_VERSION=`$SYSREPO_CONFIG --modversion libSysrepo-cpp`

    # If include paths are equal, there's no need to include both. But if they're different,
    # we need both.
    if test "${SYSREPO_INCLUDEDIR}" != "${SYSREPOCPP_INCLUDEDIR}"; then
       SYSREPO_INCLUDEDIR="${SYSREPO_INCLUDEDIR} ${SYSREPOCPP_INCLUDEDIR}"
    fi

    if test "${SYSREPO_CPPFLAGS}" != "${SYSREPOCPP_CPPFLAGS}"; then
       SYSREPO_CPPFLAGS="${SYSREPO_CPPFLAGS} ${SYSREPOCPP_CPPFLAGS}"
    fi

    if test "${SYSREPO_LIBS}" != "${SYSREPOCPP_LIBS}"; then
       SYSREPO_LIBS="${SYSREPO_LIBS} ${SYSREPOCPP_LIBS}"
    fi

    AC_SUBST(SYSREPO_CPPFLAGS)
    AC_SUBST(SYSREPO_LIBS)
    AC_SUBST(SYSREPO_REPO)

    # Check that a simple program using Sysrepo functions can compile and link.
    CPPFLAGS_SAVED="$CPPFLAGS"
    LIBS_SAVED="$LIBS"

    CPPFLAGS="$SYSREPO_CPPFLAGS $CPPFLAGS"
    LIBS="$SYSREPO_LIBS $LIBS"

    AC_LINK_IFELSE(
            [AC_LANG_PROGRAM([extern "C" {
                              #include <sysrepo.h>
                              }],
                              [sr_conn_ctx_t *connection = NULL;
                              sr_session_ctx_t *session = NULL;
                              sr_connect("configure_test", SR_CONN_DEFAULT, &connection);
                              sr_disconnect(connection);])],
            [AC_MSG_RESULT([checking for Sysrepo headers and library... yes])],
            [AC_MSG_RESULT([checking for Sysrepo headers and library... no])
             AC_MSG_ERROR([Needs Sysrepo library])]
    )

    AC_LINK_IFELSE(
        [AC_LANG_PROGRAM(
            [#include <sysrepo-cpp/Session.hpp>],
            [sysrepo::Connection("conn-name");])],
        [AC_MSG_RESULT([checking for Sysrepo C++ bindings headers and library... yes])],
        [AC_LINK_IFELSE(
            [AC_LANG_PROGRAM(
                [#include <sysrepo-cpp/Session.h>],
                [Connection("conn-name");])],
            [AC_MSG_RESULT([checking for Sysrepo C++ bindings headers and library... old])
             AC_DEFINE([HAVE_PRE_0_7_6_SYSREPO], [1], [Using sysrepo < 0.7.6])],
             [AC_MSG_RESULT([checking for Sysrepo C++ bindings headers and library... no])
              AC_MSG_ERROR([Needs Sysrepo C++ bindings (unable to find Sysrepo-ccp library. To get it, you need to compile sysrepo with -DGEN_CPP_BINDINGS=ON.)])]
        )]
    )

    CPPFLAGS=$CPPFLAGS_SAVED
    LIBS=$LIBS_SAVED

    # Note that Sysrepo is present in the config.h file
    AC_DEFINE([HAVE_SYSREPO], [1], [SYSREPO is present])
fi

# ... and at the shell level, so Makefile.am can take action depending on this.
AM_CONDITIONAL(HAVE_SYSREPO, test "$SYSREPO_CONFIG" != "")

# Check for log4cplus
DISTCHECK_LOG4CPLUS_CONFIGURE_FLAG=
log4cplus_path="yes"
AC_ARG_WITH([log4cplus],
  AC_HELP_STRING([--with-log4cplus=PATH],
    [specify exact directory of log4cplus library and headers]),
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

AC_CHECK_HEADERS([log4cplus/logger.h],,AC_MSG_ERROR([Missing required header files.]))
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

LOG4CPLUS_VERSION=`$CPPP $CPPFLAGS conftest.cpp | grep '^AUTOCONF_LOG4CPLUS_VERSION=' | $SED -e 's/^AUTOCONF_LOG4CPLUS_VERSION=//' -e 's/[[ 	]]//g' -e 's/"//g' 2> /dev/null`
if test -z "$LOG4CPLUS_VERSION"; then
  LOG4CPLUS_VERSION="unknown"
fi
$RM -f conftest.cpp
AC_MSG_RESULT([$LOG4CPLUS_VERSION])

CPPFLAGS=$CPPFLAGS_SAVED
LIBS=$LIBS_SAVED

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

#
# Check availability of gtest, which will be used for unit tests.
#
GTEST_LDFLAGS=
GTEST_LDADD=
DISTCHECK_GTEST_CONFIGURE_FLAG=
GTEST_VERSION="unknown"

if test "x$enable_gtest" = "xyes" ; then

    DISTCHECK_GTEST_CONFIGURE_FLAG="--with-gtest=$gtest_path"

    if test -n "$with_gtest_source" ; then

        if test "x$GTEST_SOURCE" = "xyes" ; then

            AC_MSG_CHECKING([for gtest source])
            # If not specified, try some common paths.
            GTEST_SOURCE=
            for d in /usr/src/gtest /usr/local /usr/pkg /opt /opt/local ; do
                if test -f $d/src/gtest-all.cc -a $d/src/gtest_main.cc; then
                    GTEST_SOURCE=$d
                    AC_MSG_RESULT([$GTEST_SOURCE])
                    break
                fi
            done
            if test -z $GTEST_SOURCE ; then
                AC_MSG_ERROR([no gtest source but it was selected])
            fi
        else
            if test ! -d $GTEST_SOURCE/src -a -d $GTEST_SOURCE/googletest; then
                GTEST_SOURCE=$GTEST_SOURCE/googletest
            fi
            AC_CHECK_FILES([$GTEST_SOURCE/src/gtest-all.cc]
                [$GTEST_SOURCE/src/gtest_main.cc],
                [have_gtest_source=yes],
                [AC_MSG_ERROR([no gtest source at $GTEST_SOURCE])])
        fi
        have_gtest_source=yes
        GTEST_LDADD="\$(top_builddir)/ext/gtest/libgtest.a"
        DISTCHECK_GTEST_CONFIGURE_FLAG="--with-gtest-source=$GTEST_SOURCE"
        GTEST_INCLUDES="-I$GTEST_SOURCE -I$GTEST_SOURCE/include"
        GTEST_VERSION="`basename $GTEST_SOURCE`"
    fi

    if test "$gtest_path" != "no" ; then
        if test "$gtest_path" != "yes"; then
            GTEST_PATHS=$gtest_path
            if test -x "${gtest_path}/bin/gtest-config" ; then
                GTEST_CONFIG="${gtest_path}/bin/gtest-config"
            fi
        else
            AC_PATH_PROG([GTEST_CONFIG], [gtest-config])
        fi
        if test -x "${GTEST_CONFIG}" ; then :
            # using cppflags instead of cxxflags
            GTEST_INCLUDES=`${GTEST_CONFIG} --cppflags`
            GTEST_LDFLAGS=`${GTEST_CONFIG} --ldflags`
            GTEST_LDADD=`${GTEST_CONFIG} --libs`
            GTEST_VERSION=`${GTEST_CONFIG} --version`
            GTEST_FOUND="true"
        else
            AC_MSG_WARN([Unable to locate Google Test gtest-config.])
            if test -z "${GTEST_PATHS}" ; then
                GTEST_PATHS="/usr /usr/local"
            fi
            GTEST_FOUND="false"
        fi
        if test "${GTEST_FOUND}" != "true"; then
            GTEST_FOUND="false"
            for dir in $GTEST_PATHS; do
                if test -f "$dir/include/gtest/gtest.h"; then
                    if ! test -f "$dir/lib/libgtests.a"; then
                        AC_MSG_WARN([Found Google Test include but not the library in $dir.])
                        continue
                    fi
                    GTEST_INCLUDES="-I$dir/include"
                    GTEST_LDFLAGS="-L$dir/lib"
                    GTEST_LDADD="-lgtest"
                    GTEST_FOUND="true"
                    break
                fi
            done
        fi
        if test "${GTEST_FOUND}" != "true"; then
            AC_MSG_ERROR([Cannot find gtest in: $GTEST_PATHS])
        fi

    fi
fi
AM_CONDITIONAL(HAVE_GTEST, test $enable_gtest != "no")
AM_CONDITIONAL(HAVE_GTEST_SOURCE, test "X$have_gtest_source" = "Xyes")
AC_SUBST(DISTCHECK_GTEST_CONFIGURE_FLAG)
AC_SUBST(GTEST_INCLUDES)
AC_SUBST(GTEST_LDFLAGS)
AC_SUBST(GTEST_LDADD)
AC_SUBST(GTEST_SOURCE)

#
# Check availability of benchmark.
#
BENCHMARK_CPPFLAGS=
BENCHMARK_LDFLAGS=
BENCHMARK_LDADD=
DISTCHECK_BENCHMARK_CONFIGURE_FLAG=
BENCHMARK_VERSION="unknown"

if test "x$enable_benchmark" = "xyes" ; then

    DISTCHECK_BENCHMARK_CONFIGURE_FLAG="--with-benchmark=$benchmark_path"

    if test -n "$with_benchmark_source" ; then

        if test "x$BENCHMARK_SOURCE" = "xyes" ; then

            AC_MSG_CHECKING([for benchmark source])
            # If not specified, try some common paths.
            BENCHMARK_SOURCE=
            for d in /usr/src/benchmark /usr/local /usr/pkg /opt /opt/local ; do
                if test -f $d/src/benchmark.cc; then
                    BENCHMARK_SOURCE=$d
                    AC_MSG_RESULT([$BENCHMARK_SOURCE])
                    break
                fi
            done
            if test -z $BENCHMARK_SOURCE ; then
                AC_MSG_ERROR([no benchmark source but it was selected])
            fi
        else
            if test ! -d $BENCHMARK_SOURCE/src; then
                BENCHMARK_SOURCE=$BENCHMARK_SOURCE/benchmark
            fi
            AC_CHECK_FILES([$BENCHMARK_SOURCE/src/benchmark.cc],
                [have_benchmark_source=yes],
                [AC_MSG_ERROR([no benchmark source at $BENCHMARK_SOURCE])])
        fi
        have_benchmark_source=yes
        BENCHMARK_CPPFLAGS=`cat \${BENCHMARK_SOURCE}/build/src/CMakeFiles/benchmark.dir/flags.make | grep CXX_DEFINES | cut -d "=" -f 2`
        BENCHMARK_LDADD="\$(BENCHMARK_SOURCE)/build/src/libbenchmark.a"
        DISTCHECK_BENCHMARK_CONFIGURE_FLAG="--with-benchmark-source=$BENCHMARK_SOURCE"
        BENCHMARK_INCLUDES="-I$BENCHMARK_SOURCE \
                            -I$BENCHMARK_SOURCE/src \
                            -I$BENCHMARK_SOURCE/include \
                            -I$BENCHMARK_SOURCE/include/benchmark"
        BENCHMARK_VERSION="$(basename $BENCHMARK_SOURCE)"
    fi

    if test "$benchmark_path" != "no" ; then
        if test "$benchmark_path" != "yes"; then
            BENCHMARK_PATHS=$benchmark_path
        fi
        if test -z "${BENCHMARK_PATHS}" ; then
            BENCHMARK_PATHS="/usr /usr/local"
        fi
        BENCHMARK_FOUND="false"
        for dir in ${BENCHMARK_PATHS}; do
            if test -f "$dir/include/benchmark/benchmark.h"; then
                if ! test -f "$dir/lib/libbenchmark.a"; then
                    AC_MSG_WARN([Found Google Benchmark include but not the library in $dir.])
                    continue
                fi
                BENCHMARK_INCLUDES="-I$dir/include"
                BENCHMARK_LDFLAGS="-L$dir/lib"
                BENCHMARK_LDADD="$dir/lib/libbenchmark.a "
                BENCHMARK_FOUND="true"
                break
            fi
        done
        if test "${BENCHMARK_FOUND}" != "true"; then
            AC_MSG_ERROR([Cannot find benchmark in: $BENCHMARK_PATHS])
        fi

    fi

    if test $enable_gtest = no; then
        AC_MSG_ERROR([--with-benchmark and --with-benchmark-source require --with-gtest or --with-gtest-source])
    fi

fi
AM_CONDITIONAL(HAVE_BENCHMARK, test $enable_benchmark != "no")
AM_CONDITIONAL(HAVE_BENCHMARK_SOURCE, test "X$have_benchmark_source" = "Xyes")
AC_SUBST(DISTCHECK_BENCHMARK_CONFIGURE_FLAG)
AC_SUBST(BENCHMARK_CPPFLAGS)
AC_SUBST(BENCHMARK_INCLUDES)
AC_SUBST(BENCHMARK_LDFLAGS)
AC_SUBST(BENCHMARK_LDADD)
AC_SUBST(BENCHMARK_SOURCE)

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

#
# ASIO: we extensively use it as the C++ event management module.
#
# Use our 'coroutine' header from ext
# CPPFLAGS="$CPPFLAGS -I\$(top_srcdir)/ext/coroutine"

#
# Doesn't seem to be required?
CPPFLAGS="$CPPFLAGS -DBOOST_ASIO_HEADER_ONLY"
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

AC_ARG_ENABLE(generate_messages, [AC_HELP_STRING([--enable-generate-messages],
  [indicates that the messages files will be regenerated. [default=no]])],
  enable_generate_messages=$enableval, enable_generate_messages=no)

AM_CONDITIONAL([GENERATE_MESSAGES], [test x$enable_generate_messages != xno])

# cross compiling is not compatible with enable-generate-messages.
if test "$cross_compiling" = "yes"; then
    if test "$enable_generate_messages" != "no"; then
        AC_MSG_WARN([To build the message compiler is not compatible with cross compiling])
    fi
fi

AC_ARG_ENABLE(generate_parser, [AC_HELP_STRING([--enable-generate-parser],
  [indicates that the parsers will be regenerated. This implies that the
   bison and flex are required [default=no]])],
   enable_generate_parser=$enableval, enable_generate_parser=no)

# Check if flex is available. Flex is not needed for building Kea sources,
# unless you want to regenerate grammars
AC_PROG_LEX

# Check if bison is available. Bison is not needed for building Kea sources,
# unless you want to regenerate grammars
AC_PATH_PROG(YACC, bison)
AC_SUBST(YACC)

if test "x$enable_generate_parser" != "xno"; then

    if test "x$LEX" != "xflex"; then
       AC_MSG_ERROR([Flex is required for enable-generate-parser, but was not found])
    fi

    if test "x$YACC" == "x"; then
       AC_MSG_ERROR([Bison is required for enable-generate-parser, but was not found])
    fi

# Ok, let's check if we have at least 3.0.0 version of the bison. The code used
# to generate parsers is roughly based on bison 3.0 examples.
   cat > bisontest.y << EOF
%require "3.0.0"
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
        AC_MSG_ERROR("Error with $YACC. Possibly incorrect version? Required at least 3.0.0.")
    fi
    $RM -f bisontest.y bisontest.cc
fi

AM_CONDITIONAL([GENERATE_PARSER], [test x$enable_generate_parser != xno])

AC_ARG_ENABLE(generate_docs, [AC_HELP_STRING([--enable-generate-docs],
  [regenerate documentation using Docbook [default=no]])],
  enable_generate_docs=$enableval, enable_generate_docs=no)

if test "x$enable_generate_docs" != xno ; then

# xsltproc --nonet parameter
  NONET="--nonet"
  AC_ARG_VAR(XSLTPROC_NET, [xsltproc uses the Internet to fetch DTDs, entities or documents.])
  if test "x$XSLTPROC_NET" != x ; then
    NONET=
  fi
  AC_SUBST(NONET)

# Check for xsltproc
  AC_PATH_PROG([XSLTPROC], [xsltproc])
  if test -z "$XSLTPROC"; then
    AC_MSG_ERROR("xsltproc not found; it is required for --enable-generate-docs")
  else
    AC_MSG_CHECKING([if $XSLTPROC works])
    # run xsltproc to see if works
    $XSLTPROC --novalid --xinclude $NONET http://docbook.sourceforge.net/release/xsl/current/manpages/docbook.xsl
    if test $? -ne 0 ; then
      AC_MSG_ERROR("Error with $XSLTPROC using release/xsl/current/manpages/docbook.xsl")
    fi
    $XSLTPROC --novalid --xinclude $NONET http://docbook.sourceforge.net/release/xsl/current/html/docbook.xsl
    if test $? -ne 0 ; then
      AC_MSG_ERROR("Error with $XSLTPROC using release/xsl/current/html/docbook.xsl")
    fi
    AC_MSG_RESULT(yes)
  fi

  AC_PATH_PROG([ELINKS], [elinks])
  if test -z "$ELINKS"; then
    AC_MSG_ERROR("elinks not found; it is required for --enable-generate-docs")
  fi
fi

# Don't fail here if not found, used to generate PDF documentation.
AC_PATH_PROG([DBLATEX], [dblatex])
AM_CONDITIONAL(HAVE_DBLATEX, test "x$DBLATEX" != "x")

AM_CONDITIONAL(GENERATE_DOCS, test x$enable_generate_docs != xno)

AC_ARG_ENABLE(install-configurations,
  [AC_HELP_STRING([--disable-install-configurations],
  [do not install configuration])], install_configurations=$enableval, install_configurations=yes)

AM_CONDITIONAL(INSTALL_CONFIGURATIONS, test x$install_configurations = xyes || test x$install_configurations = xtrue)

AC_ARG_ENABLE(logger-checks, [AC_HELP_STRING([--enable-logger-checks],
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

# Check for optreset in unistd.h. On BSD systems the optreset is
# used to reset the state of getopt() function. Resetting its state
# is required if command line arguments are parsed multiple times
# during a program. On Linux this variable will not exist because
# getopt() reset is performed by setting optind = 0. On Operating
# Systems where optreset is defined use optreset = 1 and optind = 1
# to reset internal state of getopt(). Failing to do so will result
# in unpredictable output from getopt().
AC_MSG_CHECKING([whether optreset variable is defined in unistd.h])
AC_TRY_LINK(
    [#include <unistd.h>],
    [extern int optreset; optreset=1;],
    [ AC_MSG_RESULT(yes)
      var_optreset_exists=yes],
    [ AC_MSG_RESULT(no)
      var_optreset_exists=no]
)
AM_CONDITIONAL(HAVE_OPTRESET, test "x$var_optreset_exists" != "xno")
AM_COND_IF([HAVE_OPTRESET], [AC_DEFINE([HAVE_OPTRESET], [1], [Check for optreset?])])

AC_DEFINE([CONFIG_H_WAS_INCLUDED], [1], [config.h inclusion marker])

AC_CONFIG_FILES([Makefile
                 compatcheck/Makefile
                 doc/Makefile
                 doc/guide/Makefile
                 doc/version.ent
                 doc/docgen/Makefile
                 ext/Makefile
                 ext/gtest/Makefile
                 ext/coroutine/Makefile
                 kea_version.h
                 m4macros/Makefile
                 src/Makefile
                 src/bin/Makefile
                 src/bin/admin/Makefile
                 src/bin/admin/kea-admin
                 src/bin/admin/tests/Makefile
                 src/bin/admin/tests/cql_tests.sh
                 src/bin/admin/tests/data/Makefile
                 src/bin/admin/tests/memfile_tests.sh
                 src/bin/admin/tests/mysql_tests.sh
                 src/bin/admin/tests/pgsql_tests.sh
                 src/bin/agent/Makefile
                 src/bin/agent/tests/Makefile
                 src/bin/agent/tests/ca_process_tests.sh
                 src/bin/agent/tests/test_data_files_config.h
                 src/bin/agent/tests/test_libraries.h
                 src/bin/d2/Makefile
                 src/bin/d2/tests/Makefile
                 src/bin/d2/tests/d2_process_tests.sh
                 src/bin/d2/tests/test_data_files_config.h
                 src/bin/dhcp4/Makefile
                 src/bin/dhcp4/tests/Makefile
                 src/bin/dhcp4/tests/dhcp4_process_tests.sh
                 src/bin/dhcp4/tests/marker_file.h
                 src/bin/dhcp4/tests/test_data_files_config.h
                 src/bin/dhcp4/tests/test_libraries.h
                 src/bin/dhcp6/Makefile
                 src/bin/dhcp6/tests/Makefile
                 src/bin/dhcp6/tests/dhcp6_process_tests.sh
                 src/bin/dhcp6/tests/marker_file.h
                 src/bin/dhcp6/tests/test_data_files_config.h
                 src/bin/dhcp6/tests/test_libraries.h
                 src/bin/keactrl/Makefile
                 src/bin/keactrl/keactrl
                 src/bin/keactrl/keactrl.conf
                 src/bin/keactrl/tests/Makefile
                 src/bin/keactrl/tests/keactrl_tests.sh
                 src/bin/lfc/Makefile
                 src/bin/lfc/tests/Makefile
                 src/bin/netconf/Makefile
                 src/bin/netconf/tests/Makefile
                 src/bin/netconf/tests/shtests/Makefile
                 src/bin/netconf/tests/shtests/netconf_tests.sh
                 src/bin/netconf/tests/test_data_files_config.h
                 src/bin/netconf/tests/test_libraries.h
                 src/bin/perfdhcp/Makefile
                 src/bin/perfdhcp/tests/Makefile
                 src/bin/perfdhcp/tests/testdata/Makefile
                 src/bin/shell/Makefile
                 src/bin/shell/kea-shell
                 src/bin/shell/tests/Makefile
                 src/bin/shell/tests/shell_process_tests.sh
                 src/bin/shell/tests/shell_unittest.py
                 src/hooks/Makefile
                 src/hooks/dhcp/Makefile
                 src/hooks/dhcp/high_availability/Makefile
                 src/hooks/dhcp/high_availability/tests/Makefile
                 src/hooks/dhcp/lease_cmds/Makefile
                 src/hooks/dhcp/lease_cmds/tests/Makefile
                 src/hooks/dhcp/mysql_cb/Makefile
                 src/hooks/dhcp/mysql_cb/tests/Makefile
                 src/hooks/dhcp/user_chk/Makefile
                 src/hooks/dhcp/user_chk/tests/Makefile
                 src/hooks/dhcp/user_chk/tests/test_data_files_config.h
                 src/hooks/dhcp/stat_cmds/Makefile
                 src/hooks/dhcp/stat_cmds/tests/Makefile
                 src/lib/Makefile
                 src/lib/asiodns/Makefile
                 src/lib/asiodns/tests/Makefile
                 src/lib/asiolink/Makefile
                 src/lib/asiolink/testutils/Makefile
                 src/lib/asiolink/tests/Makefile
                 src/lib/cc/Makefile
                 src/lib/cc/tests/Makefile
                 src/lib/cfgrpt/Makefile
                 src/lib/cfgrpt/tests/Makefile
                 src/lib/config/Makefile
                 src/lib/config/tests/Makefile
                 src/lib/config/tests/data_def_unittests_config.h
                 src/lib/config/tests/testdata/Makefile
                 src/lib/config_backend/Makefile
                 src/lib/config_backend/tests/Makefile
                 src/lib/cryptolink/Makefile
                 src/lib/cryptolink/tests/Makefile
                 src/lib/database/Makefile
                 src/lib/database/tests/Makefile
                 src/lib/database/testutils/Makefile
                 src/lib/dhcp/Makefile
                 src/lib/dhcp/tests/Makefile
                 src/lib/dhcp_ddns/Makefile
                 src/lib/dhcp_ddns/tests/Makefile
                 src/lib/dhcpsrv/Makefile
                 src/lib/dhcpsrv/benchmarks/Makefile
                 src/lib/dhcpsrv/tests/Makefile
                 src/lib/dhcpsrv/tests/test_libraries.h
                 src/lib/dhcpsrv/testutils/Makefile
                 src/lib/dns/Makefile
                 src/lib/dns/gen-rdatacode.py
                 src/lib/dns/tests/Makefile
                 src/lib/dns/tests/testdata/Makefile
                 src/lib/eval/Makefile
                 src/lib/eval/tests/Makefile
                 src/lib/exceptions/Makefile
                 src/lib/exceptions/tests/Makefile
                 src/lib/hooks/Makefile
                 src/lib/hooks/tests/Makefile
                 src/lib/hooks/tests/marker_file.h
                 src/lib/hooks/tests/test_libraries.h
                 src/lib/http/Makefile
                 src/lib/http/tests/Makefile
                 src/lib/log/Makefile
                 src/lib/log/compiler/Makefile
                 src/lib/log/interprocess/Makefile
                 src/lib/log/interprocess/tests/Makefile
                 src/lib/log/tests/Makefile
                 src/lib/log/tests/buffer_logger_test.sh
                 src/lib/log/tests/console_test.sh
                 src/lib/log/tests/destination_test.sh
                 src/lib/log/tests/init_logger_test.sh
                 src/lib/log/tests/local_file_test.sh
                 src/lib/log/tests/logger_lock_test.sh
                 src/lib/log/tests/severity_test.sh
                 src/lib/log/tests/tempdir.h
                 src/lib/mysql/Makefile
                 src/lib/mysql/testutils/Makefile
                 src/lib/mysql/tests/Makefile
                 src/lib/pgsql/Makefile
                 src/lib/pgsql/tests/Makefile
                 src/lib/pgsql/testutils/Makefile
                 src/lib/cql/Makefile
                 src/lib/cql/tests/Makefile
                 src/lib/cql/testutils/Makefile
                 src/lib/process/Makefile
                 src/lib/process/tests/Makefile
                 src/lib/process/testutils/Makefile
                 src/lib/stats/Makefile
                 src/lib/stats/tests/Makefile
                 src/lib/testutils/Makefile
                 src/lib/testutils/dhcp_test_lib.sh
                 src/lib/util/Makefile
                 src/lib/util/io/Makefile
                 src/lib/util/python/Makefile
                 src/lib/util/python/gen_wiredata.py
                 src/lib/util/tests/Makefile
                 src/lib/util/tests/process_spawn_app.sh
                 src/lib/util/threads/Makefile
                 src/lib/util/threads/tests/Makefile
                 src/lib/util/unittests/Makefile
                 src/lib/yang/Makefile
                 src/lib/yang/pretests/Makefile
                 src/lib/yang/tests/Makefile
                 src/lib/yang/testutils/Makefile
                 src/share/Makefile
                 src/share/database/Makefile
                 src/share/database/scripts/Makefile
                 src/share/database/scripts/cql/Makefile
                 src/share/database/scripts/cql/upgrade_1.0_to_2.0.sh
                 src/share/database/scripts/cql/upgrade_2.0_to_3.0.sh
                 src/share/database/scripts/cql/wipe_data.sh
                 src/share/database/scripts/mysql/Makefile
                 src/share/database/scripts/mysql/upgrade_1.0_to_2.0.sh
                 src/share/database/scripts/mysql/upgrade_2.0_to_3.0.sh
                 src/share/database/scripts/mysql/upgrade_3.0_to_4.0.sh
                 src/share/database/scripts/mysql/upgrade_4.0_to_4.1.sh
                 src/share/database/scripts/mysql/upgrade_4.1_to_5.0.sh
                 src/share/database/scripts/mysql/upgrade_5.0_to_5.1.sh
                 src/share/database/scripts/mysql/upgrade_5.1_to_5.2.sh
                 src/share/database/scripts/mysql/upgrade_5.2_to_6.0.sh
                 src/share/database/scripts/mysql/upgrade_6.0_to_7.0.sh
                 src/share/database/scripts/mysql/upgrade_7.0_to_8.0.sh
                 src/share/database/scripts/mysql/wipe_data.sh
                 src/share/database/scripts/pgsql/Makefile
                 src/share/database/scripts/pgsql/upgrade_1.0_to_2.0.sh
                 src/share/database/scripts/pgsql/upgrade_2.0_to_3.0.sh
                 src/share/database/scripts/pgsql/upgrade_3.0_to_3.1.sh
                 src/share/database/scripts/pgsql/upgrade_3.1_to_3.2.sh
                 src/share/database/scripts/pgsql/upgrade_3.2_to_3.3.sh
                 src/share/database/scripts/pgsql/upgrade_3.3_to_4.0.sh
                 src/share/database/scripts/pgsql/upgrade_4.0_to_5.0.sh
                 src/share/database/scripts/pgsql/wipe_data.sh
                 src/share/yang/Makefile
                 src/share/yang/modules/Makefile
                 tools/Makefile
                 tools/path_replacer.sh
])

AC_CONFIG_COMMANDS([permissions], [
           chmod +x src/bin/admin/kea-admin
           chmod +x src/bin/dhcp4/tests/dhcp4_process_tests.sh
           chmod +x src/bin/dhcp6/tests/dhcp6_process_tests.sh
           chmod +x src/bin/keactrl/keactrl
           chmod +x src/bin/keactrl/tests/keactrl_tests.sh
           chmod +x src/bin/shell/kea-shell
           chmod +x src/bin/shell/tests/shell_process_tests.sh
           chmod +x src/bin/shell/tests/shell_unittest.py
           chmod +x src/lib/dns/gen-rdatacode.py
           chmod +x src/lib/log/tests/buffer_logger_test.sh
           chmod +x src/lib/log/tests/console_test.sh
           chmod +x src/lib/log/tests/destination_test.sh
           chmod +x src/lib/log/tests/init_logger_test.sh
           chmod +x src/lib/log/tests/local_file_test.sh
           chmod +x src/lib/log/tests/logger_lock_test.sh
           chmod +x src/lib/log/tests/severity_test.sh
           chmod +x src/lib/util/python/gen_wiredata.py
           chmod +x src/lib/util/tests/process_spawn_app.sh
           chmod +x tools/path_replacer.sh
])

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
  PYTHON:          ${PYTHON}
  PYTHON_VERSION:  ${PYTHON_VERSION}

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

if test "$CQL_CPPFLAGS" != "" ; then
cat >> config.report << END

Cassandra CQL:
  CQL_VERSION:     ${CQL_VERSION}
  CQL_CPPFLAGS:    ${CQL_CPPFLAGS}
  CQL_LIBS:        ${CQL_LIBS}
END
else
cat >> config.report << END

Cassandra CQL:
  no
END
fi

if test "$SYSREPO_CPPFLAGS" != "" ; then
cat >> config.report << END

Sysrepo:
  SYSREPO_VERSION:     ${SYSREPO_VERSION}
  SYSREPO_CPPFLAGS:    ${SYSREPO_CPPFLAGS}
  SYSREPO_LIBS:        ${SYSREPO_LIBS}
  SYSREPO_REPO:        ${SYSREPO_REPO}
END
else
cat >> config.report << END

Sysrepo:
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

if test "$enable_benchmark" != "no"; then
cat >> config.report << END

Google Benchmark:
  BENCHMARK_VERSION:   ${BENCHMARK_VERSION}
  BENCHMARK_CPPFLAGS:  ${BENCHMARK_CPPFLAGS}
  BENCHMARK_INCLUDES:  ${BENCHMARK_INCLUDES}
  BENCHMARK_LDFLAGS:   ${BENCHMARK_LDFLAGS}
  BENCHMARK_LDADD:     ${BENCHMARK_LDADD}
  BENCHMARK_SOURCE:    ${BENCHMARK_SOURCE}
END
else
cat >> config.report << END

Google Benchmark:
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

cat >> config.report << END

Developer:
  Enable Debugging:          $debug_enabled
  Google Tests:              $enable_gtest
  Google Benchmark:          $enable_benchmark
  Valgrind:                  $found_valgrind
  C++ Code Coverage:         $USE_LCOV
  Logger checks:             $enable_logger_checks
  Generate Documentation:    $enable_generate_docs
  Generate Parser:           $enable_generate_parser
  Generate Messages Files:   $enable_generate_messages
  Perfdhcp:                  $enable_perfdhcp
  Kea-shell:                 $enable_shell

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
