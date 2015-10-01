#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.59])

# For released versions, this is in x.y.z format.
# For GIT versions, this is x.y.z-git, where x.y.z denotes the software
# version that was used as a base + changes that were made later, but
# are not released yet.
AC_INIT(kea, 0.9.2-git, kea-dev@lists.isc.org)
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
AC_DEFINE_UNQUOTED([EXTENDED_VERSION], ["${KEA_SRCID}"], [Extended Kea version])

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
AM_CONDITIONAL(USE_CLANGPP, test "X${CLANGPP}" = "Xyes")

dnl Determine if we are using GNU sed
GNU_SED=no
$SED --version 2> /dev/null | grep GNU > /dev/null 2>&1
if test $? -eq 0; then
  GNU_SED=yes
fi

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
  CXXFLAGS="$CXXFLAGS $1"

  AC_LINK_IFELSE([AC_LANG_SOURCE([int main(void){ return 0;}])],
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
MULTITHREADING_FLAG="-mt"
fi

# Newer versions of clang++ promotes "unused driver arguments" warnings to
# a fatal error with -Werror, causing build failure.  Since we use multiple
# compilers on multiple systems, this can easily happen due to settings for
# non clang++ environments that could be just ignored otherwise.  It can also
# happen if clang++ is used via ccache.  So, although probably suboptimal,
# we suppress this particular warning.  Note that it doesn't weaken checks
# on the source code.
if test "$CLANGPP" = "yes"; then
CXX_VERSION=`$CXX --version 2> /dev/null | head -1`
KEA_CXXFLAGS="$KEA_CXXFLAGS -Qunused-arguments"
fi

KEA_CXX_TRY_FLAG([-Wno-missing-field-initializers],
	[WARNING_NO_MISSING_FIELD_INITIALIZERS_CFLAG="-Wno-missing-field-initializers"])
AC_SUBST(WARNING_NO_MISSING_FIELD_INITIALIZERS_CFLAG)

# gcc specific settings:
if test "X$GXX" = "Xyes"; then
CXX_VERSION=`$CXX --version 2> /dev/null | head -1`
KEA_CXXFLAGS="$KEA_CXXFLAGS -Wall -Wextra -Wnon-virtual-dtor -Wwrite-strings -Woverloaded-virtual -Wno-sign-compare"
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

# Don't use -Werror if configured not to
AC_ARG_WITH(werror,
    AC_HELP_STRING([--with-werror], [Compile using -Werror (default=yes)]),
    [
     case "${withval}" in
         yes) with_werror=1 ;;
         no)  with_werror=0 ;;
         *)   AC_MSG_ERROR(bad value ${withval} for --with-werror) ;;
     esac],
     [with_werror=1])

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

fi				dnl GXX = yes

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

m4_define([_AM_PYTHON_INTERPRETER_LIST], [python python3.4 python3.3 python3.2 python3.1 python3])
AC_ARG_WITH([pythonpath],
AC_HELP_STRING([--with-pythonpath=PATH],
  [specify an absolute path to python executable when automatic version check (incorrectly) fails]),
  [python_path="$withval"], [python_path="auto"])
if test "$python_path" = auto; then
	AM_PATH_PYTHON([3.1],,[PYTHON=no])
else
	# Older versions of automake can't handle python3 well.  This is an
	# in-house workaround for them.
	PYTHON=$python_path
	AC_SUBST(PYTHON)
	PYTHON_PREFIX='${prefix}'
	AC_SUBST(PYTHON_PREFIX)
	PYTHON_EXEC_PREFIX='$(exec_prefix)'
	AC_SUBST(PYTHON_EXEC_PREFIX)
	PYTHON_VERSION=[`$PYTHON -c "import sys; sys.stdout.write(sys.version[:3])"`]
	if test `echo "$PYTHON_VERSION >= 3.1" | bc` != 1 ; then
		AC_MSG_ERROR(["Python version too old: $PYTHON_VERSION, need 3.1 or higher"])
	fi
	AC_SUBST(PYTHON_VERSION)
	PYTHON_PLATFORM=`$PYTHON -c "import sys; print(sys.platform)"`
	AC_SUBST(PYTHON_PLATFORM)
	pythondir='${prefix}/lib/python'$PYTHON_VERSION'/site-packages'
	AC_SUBST(pythondir)
	pkgpythondir='${pythondir}/'$PACKAGE
	AC_SUBST(pkgpythondir)
	pyexecdir='${exec_prefix}/lib/python'$PYTHON_VERSION'/site-packages'
	AC_SUBST(pyexecdir)
	pkgpyexecdir='${pyexecdir}/'$PACKAGE
	AC_SUBST(pkgpyexecdir)
fi

# produce PIC unless we disable shared libraries. need this for python bindings.
if test $enable_shared != "no" -a "X$GXX" = "Xyes"; then
   KEA_CXXFLAGS="$KEA_CXXFLAGS -fPIC"
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
#		AC_MSG_ERROR("lcov needs gtest for test coverage report")
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

# Simplified, non-caching AC_CHECK_PROG
# Searches $PATH for the existence of argument 2,
# and sets the full path to the variable in argument 1.
# if not found, and a third argument is given, the value
# is set to that. If not, the value is untouched.
# Does not take absolute paths into account at this point,
# and also works for single files only (arguments are not
# stripped like in AC_CHECK_PROG)
AC_DEFUN([ACX_CHECK_PROG_NONCACHE], [
    RESULT=""
    IFS_SAVED="$IFS"
    IFS=${PATH_SEPARATOR}
    for cur_path in ${PATH} ; do
      if test -e "${cur_path}/$2" ; then
          RESULT="${cur_path}/$2"
      fi
    done
    if test "$RESULT" = "" ; then
        :
        m4_ifvaln([$3], [$1=$3])
    else
        $1=$RESULT
    fi
    IFS="$IFS_SAVED"
])

# Avoid checking Botan if OpenSSL is wanted
AC_ARG_WITH([openssl],
            [AS_HELP_STRING([--with-openssl[[=PATH]]], [Enables OpenSSL,
            location can be specified optionally])],
            [use_openssl="$withval"],
            [use_openssl="auto"])

# Botan helper test function
# Tries to compile a botan program, given the output of the given
# config tool
# Arguments:
# - name of tool (checked for path), must support --libs and --cflags
# - fixed argument(s) for tool
# - action if successful
AC_DEFUN([ACX_TRY_BOTAN_TOOL], [
    TOOL=$1
    TOOL_ARG=$2
    BOTAN_TOOL=""
    ACX_CHECK_PROG_NONCACHE([BOTAN_TOOL], [${TOOL}])
    AC_MSG_CHECKING([usability of ${TOOL} ${TOOL_ARG}])
    if test "$BOTAN_TOOL" != "" ; then
        if test -x ${BOTAN_TOOL}; then
            CRYPTO_LIBS=`$BOTAN_TOOL $TOOL_ARG --libs`
            LIBS_SAVED=${LIBS}
            LIBS="$LIBS $CRYPTO_LIBS"
            CRYPTO_INCLUDES=`$BOTAN_TOOL $TOOL_ARG --cflags`
            CPPFLAGS_SAVED=${CPPFLAGS}
            CPPFLAGS="$CRYPTO_INCLUDES $CPPFLAGS"
            #AC_MSG_RESULT([found])
            AC_LINK_IFELSE(
                [AC_LANG_PROGRAM([#include <botan/botan.h>
                                  #include <botan/hash.h>
                                 ],
                                 [using namespace Botan;
                                  LibraryInitializer::initialize();
                                  HashFunction *h = get_hash("MD5");
                                 ])],
                [ AC_MSG_RESULT([ok])
                  $3
                ],
                [ AC_MSG_RESULT([not usable]) ]
            )
            LIBS=${LIBS_SAVED}
            CPPFLAGS=${CPPFLAGS_SAVED}
        else
            AC_MSG_RESULT([not executable])
        fi
    else
        AC_MSG_RESULT([not found])
    fi
    BOTAN_TOOL=""
    AC_SUBST(BOTAN_TOOL)
    ]
)

# Check for Botan
#
# Unless --with-botan-config is given, we first try to find these config
# scripts ourselves. Unfortunately, on some systems, these scripts do not
# provide the correct implementation, so for each script found, we try
# a compilation test (ACX_TRY_BOTAN_TOOL). If none are found, or none of
# them work, we see if pkg-config is available. If so, we try the several
# potential pkg-config .pc files. Again, on some systems, these can return
# incorrect information as well, so the try-compile test is repeated for
# each.
#
# If a working config script or pkgconfig file is found, we then munge its
# output for use in our Makefiles, and to make sure it works, another header
# and compilation test is done (this should also check whether we can compile
# against botan should neither -config scripts nor pkgconfig data exist).
#
botan_config="yes"
if test "${use_openssl}" != "auto" -a "${use_openssl}" != "no" ; then
   botan_config="no"
fi
AC_ARG_WITH([botan-config],
  AC_HELP_STRING([--with-botan-config=PATH],
    [specify the path to the botan-config script]),
    [botan_config="$withval"])
if test "${botan_config}" = "no" ; then
    if test "${use_openssl}" = "no" ; then
       AC_MSG_ERROR([Need Botan or OpenSSL for libcryptolink])
    fi
elif test "${botan_config}" != "yes" ; then
    if test -x "${botan_config}" ; then
        if test -d "${botan_config}" ; then
            AC_MSG_ERROR([${botan_config} is a directory])
        else
            BOTAN_CONFIG="${botan_config}"
        fi
    else
        AC_MSG_ERROR([--with-botan-config should point to a botan-config program and not a directory (${botan_config})])
    fi
else
    BOTAN_CONFIG=""
    # first try several possible names of the config script
    # (botan-config-1.8 is there just in case, the official name change
    # came later)
    BOTAN_CONFIG_VERSIONS="botan-config-1.10 botan-config-1.9 botan-config-1.8 botan-config"
    for botan_config in $BOTAN_CONFIG_VERSIONS; do
        ACX_TRY_BOTAN_TOOL([$botan_config],,
                           [ BOTAN_CONFIG="$botan_config"  ]
                          )
        if test "$BOTAN_CONFIG" != "" ; then
            break
        fi
    done
    if test "$BOTAN_CONFIG" = "" ; then
        AC_PATH_PROG([PKG_CONFIG], [pkg-config])
        if test "$PKG_CONFIG" != "" ; then
            # Ok so no script found, see if pkg-config knows of it.
            # Unfortunately, the botan.pc files also have their minor version
            # in their name, so we need to try them one by one
            BOTAN_VERSIONS="botan-1.10 botan-1.9 botan-1.8"
            for version in $BOTAN_VERSIONS; do
                ACX_TRY_BOTAN_TOOL([pkg-config], ["$version --silence-errors"],
                                   [ BOTAN_CONFIG="$PKG_CONFIG $version" ]
                                  )
            if test "$BOTAN_CONFIG" != "" ; then
                break
            fi
            done
        fi
    fi
fi

if test "x${BOTAN_CONFIG}" != "x"
then
    CRYPTO_LIBS=`${BOTAN_CONFIG} --libs`
    CRYPTO_INCLUDES=`${BOTAN_CONFIG} --cflags`

    # We expect botan-config --libs to contain -L<path_to_libbotan>, but
    # this is not always the case.  As a heuristics workaround we add
    # -L`botan-config --prefix/lib` in this case (if not present already).
    # Same for CRYPTO_INCLUDES (but using include instead of lib) below.
    if [ ${BOTAN_CONFIG} --prefix >/dev/null 2>&1 ] ; then
        echo ${CRYPTO_LIBS} | grep -- -L > /dev/null || \
            CRYPTO_LIBS="-L`${BOTAN_CONFIG} --prefix`/lib ${CRYPTO_LIBS}"
        echo ${CRYPTO_INCLUDES} | grep -- -I > /dev/null || \
            CRYPTO_INCLUDES="-I`${BOTAN_CONFIG} --prefix`/include ${CRYPTO_INCLUDES}"
    fi
fi

if test "x${CRYPTO_LIBS}" != "x"
then
   dnl Determine the Botan version
   AC_MSG_CHECKING([Botan version])
   cat > conftest.cpp << EOF
#include <botan/version.h>
AUTOCONF_BOTAN_VERSION=BOTAN_VERSION_MAJOR . BOTAN_VERSION_MINOR . BOTAN_VERSION_PATCH
EOF

   CRYPTO_VERSION=`$CPP $CPPFLAGS $CRYPTO_INCLUDES conftest.cpp | grep '^AUTOCONF_BOTAN_VERSION=' | $SED -e 's/^AUTOCONF_BOTAN_VERSION=//' -e 's/[[ 	]]//g' -e 's/"//g' 2> /dev/null`
   if test -z "$CRYPTO_VERSION"; then
      CRYPTO_VERSION="unknown"
   fi
   $RM -f conftest.cpp
   AC_MSG_RESULT([$CRYPTO_VERSION])

   # botan-config script (and the way we call pkg-config) returns -L and -l
   # as one string, but we need them in separate values
   CRYPTO_LDFLAGS=
   for flag in ${CRYPTO_LIBS}; do
       CRYPTO_LDFLAGS="${CRYPTO_LDFLAGS} `echo $flag | ${SED} -ne '/^\(\-L\)/p'`"
       CRYPTO_LIBS="${CRYPTO_LIBS} `echo $flag | ${SED} -ne '/^\(\-l\)/p'`"
   done

   # See crypto_rpath for some info on why we do this
   if test "x$ISC_RPATH_FLAG" != "x"; then
       CRYPTO_RPATH=
       for flag in ${CRYPTO_LIBS}; do
               CRYPTO_RPATH="${CRYPTO_RPATH} `echo $flag | ${SED} -ne "s/^\(\-L\)/${ISC_RPATH_FLAG}/p"`"
       done
   # According to the libtool manual, it should be sufficient if we
   # specify the "-R libdir" in our wrapper library of botan (no other
   # programs will need libbotan directly); "libdir" should be added to
   # the program's binary image.  But we've seen in our build environments
   # that (some versions of?) libtool doesn't propagate -R as documented,
   # and it caused a linker error at run time.  To work around this, we
   # also add the rpath to the global LDFLAGS.
       LDFLAGS="$CRYPTO_RPATH $LDFLAGS"
   fi

   # Even though chances are high we already performed a real compilation check
   # in the search for the right (pkg)config data, we try again here, to
   # be sure.
   CPPFLAGS_SAVED=$CPPFLAGS
   CPPFLAGS="$CRYPTO_INCLUDES $CPPFLAGS"
   LIBS_SAVED="$LIBS"
   LIBS="$LIBS $CRYPTO_LIBS"

   # ac_header_preproc is an autoconf symbol (undocumented but stable) that
   # is set if the pre-processor phase passes. Thus by adding a custom
   # failure handler we can detect the difference between a header not existing
   # (or not even passing the pre-processor phase) and a header file resulting
   # in compilation failures.
   AC_CHECK_HEADERS([botan/botan.h],,[
        CRYPTO_INCLUDES=""
        CRYPTO_LIBS=""
        CRYPTO_LDFLAGS=""
        CRYPTO_RPATH=""
	if test "x$ac_header_preproc" = "xyes"; then
		AC_MSG_RESULT([
botan/botan.h was found but is unusable. The most common cause of this problem
is attempting to use an updated C++ compiler with older C++ libraries, such as
the version of Botan that comes with your distribution. If you have updated
your C++ compiler we highly recommend that you use support libraries such as
Boost and Botan that were compiled with the same compiler version.])
	else
		AC_MSG_RESULT([Missing required header files.])
	fi]
   )
   CPPFLAGS=$CPPFLAGS_SAVED
   LIBS=$LIBS_SAVED
fi

if test "x${CRYPTO_LIBS}" != "x"
then
   CPPFLAGS_SAVED=$CPPFLAGS
   CPPFLAGS="$CRYPTO_INCLUDES $CPPFLAGS"
   LIBS_SAVED="$LIBS"
   LIBS="$LIBS $CRYPTO_LIBS"
   AC_LINK_IFELSE(
        [AC_LANG_PROGRAM([#include <botan/botan.h>
                          #include <botan/hash.h>
                         ],
                         [using namespace Botan;
                          LibraryInitializer::initialize();
                          HashFunction *h = get_hash("MD5");
                         ])],
        [AC_MSG_RESULT([checking for Botan library... yes])],
        [AC_MSG_RESULT([checking for Botan library... no])
         CRYPTO_INCLUDES=""
         CRYPTO_LIBS=""
         CRYPTO_LDFLAGS=""
         CRYPTO_RPATH=""
         AC_MSG_RESULT([Needs Botan library 1.8 or higher. On some systems,
         the botan package has a few missing dependencies (libbz2 and
         libgmp), if libbotan has been installed and you see this message,
         try upgrading to a higher version of botan or installing libbz2
         and libgmp.])]
   )
   CPPFLAGS=$CPPFLAGS_SAVED
   LIBS=$LIBS_SAVED
fi

if test "x${CRYPTO_LIBS}" != "x"
then
   CRYPTO_NAME="Botan"
   DISABLED_CRYPTO="OpenSSL"
   CRYPTO_PACKAGE="botan-1.8"
   CRYPTO_CFLAGS=""
   DISTCHECK_CRYPTO_CONFIGURE_FLAG="--with-botan=$botan_config"
   AC_DEFINE_UNQUOTED([WITH_BOTAN], [], [Compile with Botan crypto])
else
   CRYPTO_NAME="OpenSSL"
   DISABLED_CRYPTO="Botan"
   CRYPTO_PACKAGE="openssl-1.0.0"
   AC_DEFINE_UNQUOTED([WITH_OPENSSL], [], [Compile with OpenSSL crypto])
   AC_MSG_CHECKING(for OpenSSL library)
   # from bind9

   if test "${use_openssl}" = "auto" ; then
      use_openssl="yes"
   fi
   if test "${use_openssl}" = "yes" ; then
      for d in /usr /usr/local /usr/local/ssl /usr/pkg /usr/sfw; do
          if test -f $d/include/openssl/opensslv.h; then
             use_openssl=$d; break
          fi
      done
   fi
   if test "${use_openssl}" = "yes" ; then
      AC_MSG_ERROR([OpenSSL auto detection failed])
   fi
   if ! test -f "${use_openssl}"/include/openssl/opensslv.h ; then
      AC_MSG_ERROR([OpenSSL not found at ${use_openssl}])
   fi
   AC_MSG_RESULT(yes)
   if test "${use_openssl}" = "/usr" ; then
      CRYPTO_INCLUDES=""
      CRYPTO_LIBS="-lcrypto"
      DISTCHECK_CRYPTO_CONFIGURE_FLAG="--with-openssl"
      case "$host" in
          *-apple-darwin*)
              # Starting with OSX 10.7 (Lion) OpenSSL is deprecated
              CRYPTO_CFLAGS="-Wno-deprecated-declarations"
              ;;
          *)
              CRYPTO_CFLAGS=""
              ;;
      esac
   else
      CRYPTO_CFLAGS=""
      CRYPTO_INCLUDES="-I${use_openssl}/include"
      DISTCHECK_CRYPTO_CONFIGURE_FLAG="--with-openssl=${use_openssl}"
      case $host in
          *-solaris*)
              CRYPTO_LIBS="-L${use_openssl}/lib -R${use_openssl}/lib -lcrypto"
              ;;
          *-hp-hpux*)
              CRYPTO_LIBS="-L${use_openssl}/lib -Wl,+b: -lcrypto"
              ;;
          *-apple-darwin*)
              if test -f "${use_openssl}/lib/libcrypto.dylib" ; then
                 CRYPTO_LIBS="-L${use_openssl}/lib -lcrypto"
              else
                 CRYPTO_LIBS="${use_openssl}/lib/libcrypto.a"
              fi
              ;;
          *)
              CRYPTO_LIBS="-L${use_openssl}/lib -lcrypto"
              ;;
      esac
    fi
    dnl Determine the OpenSSL version
    AC_MSG_CHECKING([OpenSSL version])
    cat > conftest.cpp << EOF
#include <openssl/opensslv.h>
AUTOCONF_OPENSSL_VERSION=OPENSSL_VERSION_TEXT
EOF

    CRYPTO_VERSION=`$CPP $CPPFLAGS $CRYPTO_INCLUDES conftest.cpp | grep '^AUTOCONF_OPENSSL_VERSION=' | $SED -e 's/^AUTOCONF_OPENSSL_VERSION=//' -e 's/"//g' 2> /dev/null`
    if test -z "$CRYPTO_VERSION" ; then
       CRYPTO_VERSION="unknown"
    fi
    $RM -f conftest.cpp
    AC_MSG_RESULT([$CRYPTO_VERSION])
    #CRYPTO_LDFLAGS="-ldl"
    CRYPTO_LDFLAGS=""
    CRYPTO_RPATH=""
    dnl Check avaibility of SHA-2
    AC_MSG_CHECKING([support of SHA-2])
    LIBS_SAVED=${LIBS}
    LIBS="$LIBS $CRYPTO_LIBS"
    CPPFLAGS_SAVED=${CPPFLAGS}
    CPPFLAGS="$CRYPTO_INCLUDES $CPPFLAGS"
    AC_LINK_IFELSE(
        [AC_LANG_PROGRAM([#include <openssl/evp.h>],
                         [const EVP_MD* h224 = EVP_sha224();
                          const EVP_MD* h256 = EVP_sha256();
                          const EVP_MD* h384 = EVP_sha384();
                          const EVP_MD* h512 = EVP_sha512();
                          ])],
        [AC_MSG_RESULT([yes])],
        [AC_MSG_ERROR([missing EVP entry for SHA-2])])
    LIBS=${LIBS_SAVED}
    CPPFLAGS=${CPPFLAGS_SAVED}
fi

AM_CONDITIONAL(HAVE_BOTAN, test "$CRYPTO_NAME" = "Botan")
AM_CONDITIONAL(HAVE_OPENSSL, test "$CRYPTO_NAME" = "OpenSSL")
AC_SUBST(CRYPTO_INCLUDES)
AC_SUBST(CRYPTO_CFLAGS)
AC_SUBST(CRYPTO_LIBS)
AC_SUBST(CRYPTO_LDFLAGS)
AC_SUBST(CRYPTO_PACKAGE)
AC_SUBST(CRYPTO_RPATH)
AC_SUBST(DISTCHECK_CRYPTO_CONFIGURE_FLAG)

# Check for MySql.  The path to the mysql_config program is given with
# the --with-mysql-config (default to /usr/bin/mysql-config).  By default,
# the software is not built with MySQL support enabled.
mysql_config="no"
AC_ARG_WITH([dhcp-mysql],
  AC_HELP_STRING([--with-dhcp-mysql=PATH],
    [path to the MySQL 'mysql_config' script (MySQL is used for the DHCP database)]),
    [mysql_config="$withval"])

if test "${mysql_config}" = "yes" ; then
    MYSQL_CONFIG="/usr/bin/mysql_config"
elif test "${mysql_config}" != "no" ; then
    MYSQL_CONFIG="${withval}"
fi

if test "$MYSQL_CONFIG" != "" ; then
    if test -d "$MYSQL_CONFIG" -o ! -x "$MYSQL_CONFIG" ; then
        AC_MSG_ERROR([--with-dhcp-mysql should point to a mysql_config program])
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

    CPPFLAGS=$CPPFLAGS_SAVED
    LIBS=$LIBS_SAVED

    # Note that MYSQL is present in the config.h file
    AC_DEFINE([HAVE_MYSQL], [1], [MySQL is present])
fi

# Solaris puts FIONREAD in filio.h
AC_CHECK_HEADERS(sys/filio.h,,,)

# ... and at the shell level, so Makefile.am can take action depending on this.
AM_CONDITIONAL(HAVE_MYSQL, test "$MYSQL_CONFIG" != "")

pg_config="no"
AC_ARG_WITH([dhcp-pgsql],
  AC_HELP_STRING([--with-dhcp-pgsql=PATH],
    [path to the PostgreSQL 'pg_config' script]),
    [pg_config="$withval"])

if test "${pg_config}" = "yes" ; then
    PG_CONFIG="/usr/bin/pg_config"
elif test "${pg_config}" != "no" ; then
    PG_CONFIG="${withval}"
fi

if test "$PG_CONFIG" != "" ; then
    if test -d "$PG_CONFIG" -o ! -x "$PG_CONFIG" ; then
        AC_MSG_ERROR([--with-dhcp-pgsql should point to a pg_config program])
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

# Check for log4cplus
log4cplus_path="yes"
AC_ARG_WITH([log4cplus],
  AC_HELP_STRING([--with-log4cplus=PATH],
    [specify exact directory of log4cplus library and headers]),
    [log4cplus_path="$withval"])
if test "${log4cplus_path}" = "no" ; then
    AC_MSG_ERROR([Need log4cplus])
elif test "${log4cplus_path}" != "yes" ; then
  LOG4CPLUS_INCLUDES="-I${log4cplus_path}/include"
  LOG4CPLUS_LIBS="-L${log4cplus_path}/lib"
else
# If not specified, try some common paths.
	log4cplusdirs="/usr/local /usr/pkg /opt /opt/local"
	for d in $log4cplusdirs
	do
		if test -f $d/include/log4cplus/logger.h; then
			LOG4CPLUS_INCLUDES="-I$d/include"
			LOG4CPLUS_LIBS="-L$d/lib"
			break
		fi
	done
fi

LOG4CPLUS_LIBS="$LOG4CPLUS_LIBS -llog4cplus $MULTITHREADING_FLAG"

AC_SUBST(LOG4CPLUS_LIBS)
AC_SUBST(LOG4CPLUS_INCLUDES)

CPPFLAGS_SAVED=$CPPFLAGS
CPPFLAGS="$LOG4CPLUS_INCLUDES $CPPFLAGS"
LIBS_SAVED="$LIBS"
LIBS="$LOG4CPLUS_LIBS $LIBS"

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

LOG4CPLUS_VERSION=`$CPP $CPPFLAGS conftest.cpp | grep '^AUTOCONF_LOG4CPLUS_VERSION=' | $SED -e 's/^AUTOCONF_LOG4CPLUS_VERSION=//' -e 's/[[ 	]]//g' -e 's/"//g' 2> /dev/null`
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
if test "$BOOST_OFFSET_PTR_WOULDFAIL" = "yes" -a "$werror_ok" = 1; then
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
PTHREAD_LDFLAGS=
AC_CHECK_LIB(pthread, pthread_create,[ PTHREAD_LDFLAGS=-lpthread ], [])
AC_SUBST(PTHREAD_LDFLAGS)
AC_SUBST(MULTITHREADING_FLAG)

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
            AC_CHECK_FILES([$GTEST_SOURCE/src/gtest-all.cc]
                [$GTEST_SOURCE/src/gtest_main.cc],
                [have_gtest_source=yes],
                [AC_MSG_ERROR([no gtest source at $GTEST_SOURCE])])
        fi
        have_gtest_source=yes
        GTEST_LDFLAGS="\$(top_builddir)/ext/gtest/libgtest.a"
        DISTCHECK_GTEST_CONFIGURE_FLAG="--with-gtest-source=$GTEST_SOURCE"
        GTEST_INCLUDES="-I$GTEST_SOURCE -I$GTEST_SOURCE/include"
        # See $GTEST_SOURCE/include/gtest/internal/gtest-port.h
        # about GTEST_HAS_PTHREAD.
        case "$host" in
            *-solaris*|*-linux*|*-hpux*)
                GTEST_LDADD="$GTEST_LDADD $PTHREAD_LDFLAGS"
                ;;
        esac
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
                    GTEST_INCLUDES="-I$dir/include"
                    GTEST_LDFLAGS="-L$dir/lib"
                    GTEST_LDADD="-lgtest"
                    GTEST_FOUND="true"
                    # There is no gtest-config script on this
                    # system, which is supposed to inform us
                    # whether we need pthreads as well (a
                    # gtest compile-time option). So we still
                    # need to test that manually.
                    CPPFLAGS_SAVED="$CPPFLAGS"
                    CPPFLAGS="$CPPFLAGS $GTEST_INCLUDES"
                    LDFLAGS_SAVED="$LDFLAGS"
                    LDFLAGS="$LDFLAGS $GTEST_LDFLAGS"
                    LIBS_SAVED=$LIBS
                    LIBS="$LIBS $GTEST_LDADD"
                    AC_MSG_CHECKING([Checking whether gtest tests need pthreads])
                    # First try to compile without pthreads
                    AC_TRY_LINK([
                        #include <gtest/gtest.h>
                        ],[
                            int i = 0;
                            char* c = NULL;
                            ::testing::InitGoogleTest(&i, &c);
                            return (0);
                        ],
                        [ AC_MSG_RESULT(no) ],
                        [
                            LIBS="$SAVED_LIBS $GTEST_LDADD $PTHREAD_LDFLAGS"
                            # Now try to compile with pthreads
                            AC_TRY_LINK([
                                #include <gtest/gtest.h>
                                ],[
                                    int i = 0;
                                    char* c = NULL;
                                    ::testing::InitGoogleTest(&i, &c);
                                    return (0);
                                ],
                                [ AC_MSG_RESULT(yes)
                                  GTEST_LDADD="$GTEST_LDADD $PTHREAD_LDFLAGS"
                                ],
                                # Apparently we can't compile it at all
                                [ AC_MSG_ERROR(unable to compile with gtest) ])
                    ])
                    CPPFLAGS=$CPPFLAGS_SAVED
                    LDFLAGS=$LDFLAGS_SAVED
                    LIBS=$LIBS_SAVED
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
# ASIO: we extensively use it as the C++ event management module.
#
# Use our 'coroutine' header from ext
CPPFLAGS="$CPPFLAGS -I\$(top_srcdir)/ext/coroutine"
#
# Doesn't seem to be required?
CPPFLAGS="$CPPFLAGS -DBOOST_ASIO_HEADER_ONLY"
#
# Disable threads: Currently we don't use them.
CPPFLAGS="$CPPFLAGS -DBOOST_ASIO_DISABLE_THREADS=1"

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

AC_ARG_ENABLE(generate_docs, [AC_HELP_STRING([--enable-generate-docs],
  [regenerate documentation using Docbook [default=no]])],
  enable_generate_docs=$enableval, enable_generate_docs=no)

if test "x$enable_generate_docs" != xno ; then
  if test "$PYTHON" == "no" ; then
    AC_MSG_ERROR("Python3 is required for enable-generate-docs")
  fi

# Check for xsltproc
  AC_PATH_PROG([XSLTPROC], [xsltproc])
  if test -z "$XSLTPROC"; then
    AC_MSG_ERROR("xsltproc not found; it is required for --enable-generate-docs")
  else
    AC_MSG_CHECKING([if $XSLTPROC works])
    # run xsltproc to see if works
    $XSLTPROC --novalid --xinclude --nonet http://docbook.sourceforge.net/release/xsl/current/manpages/docbook.xsl
    if test $? -ne 0 ; then
      AC_MSG_ERROR("Error with $XSLTPROC using release/xsl/current/manpages/docbook.xsl")
    fi
    $XSLTPROC --novalid --xinclude --nonet http://docbook.sourceforge.net/release/xsl/current/html/docbook.xsl
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

AC_CONFIG_FILES([compatcheck/Makefile
                 dns++.pc
                 doc/design/datasrc/Makefile
                 doc/design/Makefile
                 doc/guide/Makefile
                 doc/Makefile
                 doc/version.ent
                 ext/coroutine/Makefile
                 ext/gtest/Makefile
                 ext/Makefile
                 m4macros/Makefile
                 Makefile
                 src/Makefile
                 src/bin/Makefile
                 src/bin/d2/Makefile
                 src/bin/d2/spec_config.h.pre
                 src/bin/d2/tests/Makefile
                 src/bin/d2/tests/d2_process_tests.sh
                 src/bin/d2/tests/test_data_files_config.h
                 src/bin/dhcp4/Makefile
                 src/bin/dhcp4/spec_config.h.pre
                 src/bin/dhcp4/tests/Makefile
                 src/bin/dhcp4/tests/dhcp4_process_tests.sh
                 src/bin/dhcp4/tests/marker_file.h
                 src/bin/dhcp4/tests/test_data_files_config.h
                 src/bin/dhcp4/tests/test_libraries.h
                 src/bin/dhcp6/Makefile
                 src/bin/dhcp6/spec_config.h.pre
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
                 src/bin/perfdhcp/Makefile
                 src/bin/perfdhcp/tests/Makefile
                 src/bin/perfdhcp/tests/testdata/Makefile
                 src/bin/admin/Makefile
                 src/bin/admin/kea-admin
                 src/bin/admin/scripts/Makefile
                 src/bin/admin/tests/Makefile
                 src/bin/admin/tests/data/Makefile
                 src/bin/admin/tests/memfile_tests.sh
                 src/bin/admin/tests/mysql_tests.sh
                 src/bin/admin/tests/pgsql_tests.sh
                 src/bin/admin/scripts/mysql/Makefile
                 src/bin/admin/scripts/mysql/upgrade_1.0_to_2.0.sh
                 src/bin/admin/scripts/mysql/upgrade_2.0_to_3.0.sh
                 src/bin/admin/scripts/pgsql/Makefile
                 src/hooks/Makefile
                 src/hooks/dhcp/Makefile
                 src/hooks/dhcp/user_chk/Makefile
                 src/hooks/dhcp/user_chk/tests/Makefile
                 src/hooks/dhcp/user_chk/tests/test_data_files_config.h
                 src/lib/Makefile
                 src/lib/asiodns/Makefile
                 src/lib/asiodns/tests/Makefile
                 src/lib/asiolink/Makefile
                 src/lib/asiolink/tests/Makefile
                 src/lib/cc/Makefile
                 src/lib/cc/tests/Makefile
                 src/lib/cfgrpt/Makefile
                 src/lib/cfgrpt/tests/Makefile
                 src/lib/config/Makefile
                 src/lib/config/tests/Makefile
                 src/lib/config/tests/data_def_unittests_config.h
                 src/lib/config/tests/testdata/Makefile
                 src/lib/cryptolink/Makefile
                 src/lib/cryptolink/tests/Makefile
                 src/lib/dhcp/Makefile
                 src/lib/dhcp/tests/Makefile
                 src/lib/dhcp_ddns/Makefile
                 src/lib/dhcp_ddns/tests/Makefile
                 src/lib/dhcpsrv/Makefile
                 src/lib/dhcpsrv/tests/Makefile
                 src/lib/dhcpsrv/tests/test_libraries.h
                 src/lib/dhcpsrv/testutils/Makefile
                 src/lib/dns/Makefile
                 src/lib/dns/gen-rdatacode.py
                 src/lib/dns/tests/Makefile
                 src/lib/dns/tests/testdata/Makefile
                 src/lib/exceptions/Makefile
                 src/lib/exceptions/tests/Makefile
                 src/lib/hooks/Makefile
                 src/lib/hooks/tests/Makefile
                 src/lib/hooks/tests/marker_file.h
                 src/lib/hooks/tests/test_libraries.h
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
                 src/lib/testutils/Makefile
                 src/lib/testutils/dhcp_test_lib.sh
                 src/lib/stats/Makefile
                 src/lib/stats/tests/Makefile
                 src/lib/util/Makefile
                 src/lib/util/io/Makefile
                 src/lib/util/python/Makefile
                 src/lib/util/python/gen_wiredata.py
                 src/lib/util/tests/Makefile
                 src/lib/util/tests/process_spawn_app.sh
                 src/lib/util/threads/Makefile
                 src/lib/util/threads/tests/Makefile
                 src/lib/util/unittests/Makefile
                 tools/path_replacer.sh
])

 AC_CONFIG_COMMANDS([permissions], [
           chmod +x src/bin/dhcp4/tests/dhcp4_process_tests.sh
           chmod +x src/bin/dhcp6/tests/dhcp6_process_tests.sh
           chmod +x src/bin/keactrl/keactrl
           chmod +x src/bin/keactrl/tests/keactrl_tests.sh
           chmod +x src/bin/admin/kea-admin
           chmod +x src/lib/dns/gen-rdatacode.py
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

cat > config.report << END

       Kea source configure results:
    -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

Package:
  Name:            ${PACKAGE_NAME}
  Version:         ${PACKAGE_VERSION}
  Extended version:${EXTENDED_VERSION}
  OS Family:       ${OS_TYPE}
  Using GNU sed:   ${GNU_SED}

C++ Compiler:
  CXX:             ${CXX}
  CXX_VERSION:     ${CXX_VERSION}
  DEFS:            ${DEFS}
  CPPFLAGS:        ${CPPFLAGS}
  CXXFLAGS:        ${CXXFLAGS}
  LDFLAGS:         ${LDFLAGS}
  KEA_CXXFLAGS:    ${KEA_CXXFLAGS}
END

if test "$PYTHON" != "no" ; then
cat >> config.report << END

Python3:
  PYTHON_VERSION:  ${PYTHON_VERSION}
  PYTHON_INCLUDES: ${PYTHON_INCLUDES}
  PYTHON_CXXFLAGS: ${PYTHON_CXXFLAGS}
  PYTHON_LDFLAGS:  ${PYTHON_LDFLAGS}
  PYTHON_LIB:      ${PYTHON_LIB}

END
else
cat >> config.report << END

Python3:
  not installed

END
fi

cat >> config.report << END
Boost:
  BOOST_VERSION:   ${BOOST_VERSION}
  BOOST_INCLUDES:  ${BOOST_INCLUDES}
  BOOST_LIBS:      ${BOOST_LIBS}

${CRYPTO_NAME}:
  CRYPTO_VERSION:  ${CRYPTO_VERSION}
  CRYPTO_CFLAGS:   ${CRYPTO_CFLAGS}
  CRYPTO_INCLUDES: ${CRYPTO_INCLUDES}
  CRYPTO_LDFLAGS:  ${CRYPTO_LDFLAGS}
  CRYPTO_LIBS:     ${CRYPTO_LIBS}

${DISABLED_CRYPTO}: no

Log4cplus:
  LOG4CPLUS_VERSION: ${LOG4CPLUS_VERSION}
  LOG4CPLUS_INCLUDES: ${LOG4CPLUS_INCLUDES}
  LOG4CPLUS_LIBS:  ${LOG4CPLUS_LIBS}

Kea config backend:
  CONFIG_BACKEND:  ${CONFIG_BACKEND}
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

if test "$enable_gtest" != "no"; then
cat >> config.report << END

GTest:
  GTEST_VERSION:   ${GTEST_VERSION}
  GTEST_INCLUDES:  ${GTEST_INCLUDES}
  GTEST_LDFLAGS:   ${GTEST_LDFLAGS}
  GTEST_LDADD:     ${GTEST_LDADD}
  GTEST_SOURCE:    ${GTEST_SOURCE}
END
fi

cat >> config.report << END

Features:
  $enable_features

Developer:
  Enable Debugging: $debug_enabled
  Google Tests: $enable_gtest
  Valgrind: $found_valgrind
  C++ Code Coverage: $USE_LCOV
  Logger checks: $enable_logger_checks
  Generate Documentation: $enable_generate_docs

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
