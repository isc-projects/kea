#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.59])
AC_INIT(bind10-devel, 20120817, bind10-dev@isc.org)
AC_CONFIG_SRCDIR(README)
AM_INIT_AUTOMAKE([foreign])
m4_ifdef([AM_SILENT_RULES], [AM_SILENT_RULES([yes])])dnl be backward compatible
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_MACRO_DIR([m4macros])

# Checks for programs.
AC_PROG_CXX

# Libtool configuration
#

# libtool cannot handle spaces in paths, so exit early if there is one
if [ test `echo $PWD | grep -c ' '` != "0"  ]; then
    AC_MSG_ERROR([BIND 10 cannot be built in a directory that contains spaces, because of libtool limitations. Please change the directory name, or use a symbolic link that does not contain spaces.])
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
AC_PROG_LIBTOOL
CFLAGS=$CFLAGS_SAVED
CXXFLAGS=$CXXFLAGS_SAVED

# Use C++ language
AC_LANG([C++])

# Identify the compiler: this check must be after AC_PROG_CXX and AC_LANG.
AM_CONDITIONAL(USE_GXX, test "X${GXX}" = "Xyes")
AC_CHECK_DECL([__SUNPRO_CC], [SUNCXX="yes"], [SUNCXX="no"])
AC_CHECK_DECL([__clang__], [CLANGPP="yes"], [CLANGPP="no"])
AM_CONDITIONAL(USE_CLANGPP, test "X${CLANGPP}" = "Xyes")

# Linker options

# check -R and -Wl,-R rather than gcc specific -rpath to be as portable
# as possible.
AC_MSG_CHECKING([whether -R flag is available in linker])
LDFLAGS_SAVED="$LDFLAGS"
LDFLAGS="$LDFLAGS -R/usr/lib"
AC_TRY_LINK([],[],
    [ AC_MSG_RESULT(yes)
        rpath_flag=-R
    ],[ AC_MSG_RESULT(no)
        AC_MSG_CHECKING([whether -Wl,-R flag is available in linker])
        LDFLAGS="$LDFLAGS_SAVED -Wl,-R"
        AC_TRY_LINK([], [],
            [ AC_MSG_RESULT(yes)
                rpath_flag=-Wl,-R
            ],[ AC_MSG_RESULT(no)
                 rpath_flag=no
            ])
    ])
LDFLAGS=$LDFLAGS_SAVED

# Compiler dependent settings: define some mandatory CXXFLAGS here.
# We also use a separate variable B10_CXXFLAGS.  This will (and should) be
# used as the default value for each specific AM_CXXFLAGS:
# AM_CXXFLAGS = $(B10_CXXFLAGS)
# AM_CXXFLAGS += ... # add module specific flags
# We need this so that we can disable some specific compiler warnings per
# module basis; since AM_CXXFLAGS are placed before CXXFLAGS, and since
# gcc's -Wno-XXX option must be specified after -Wall or -Wextra, we cannot
# specify the default warning flags in CXXFLAGS and let specific modules
# "override" the default.

# This may be used to try linker flags.
AC_DEFUN([BIND10_CXX_TRY_FLAG], [
  AC_MSG_CHECKING([whether $CXX supports $1])

  bind10_save_CXXFLAGS="$CXXFLAGS"
  CXXFLAGS="$CXXFLAGS $1"

  AC_LINK_IFELSE([AC_LANG_SOURCE([int main(void){ return 0;}])],
                 [bind10_cxx_flag=yes], [bind10_cxx_flag=no])
  CXXFLAGS="$bind10_save_CXXFLAGS"

  if test "x$bind10_cxx_flag" = "xyes"; then
    ifelse([$2], , :, [$2])
  else
    ifelse([$3], , :, [$3])
  fi

  AC_MSG_RESULT([$bind10_cxx_flag])
])

# SunStudio compiler requires special compiler options for boost
# (http://blogs.sun.com/sga/entry/boost_mini_howto)
if test "$SUNCXX" = "yes"; then
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
	B10_CXXFLAGS="$B10_CXXFLAGS -Qunused-arguments"
fi

BIND10_CXX_TRY_FLAG([-Wno-missing-field-initializers],
	[WARNING_NO_MISSING_FIELD_INITIALIZERS_CFLAG="-Wno-missing-field-initializers"])
AC_SUBST(WARNING_NO_MISSING_FIELD_INITIALIZERS_CFLAG)

# gcc specific settings:
if test "X$GXX" = "Xyes"; then
B10_CXXFLAGS="$B10_CXXFLAGS -Wall -Wextra -Wwrite-strings -Woverloaded-virtual -Wno-sign-compare"
case "$host" in
*-solaris*)
	MULTITHREADING_FLAG=-pthreads
	# In Solaris, IN6ADDR_ANY_INIT and IN6ADDR_LOOPBACK_INIT need -Wno-missing-braces
	B10_CXXFLAGS="$B10_CXXFLAGS -Wno-missing-braces"
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
   CXXFLAGS="$CXXFLAGS $B10_CXXFLAGS -Werror"
   AC_MSG_CHECKING(for in-TU anonymous namespace breakage)
   AC_TRY_COMPILE([namespace { class Foo {}; }
   namespace isc {class Bar {Foo foo_;};} ],,
	[AC_MSG_RESULT(no)
	 werror_ok=1
	 B10_CXXFLAGS="$B10_CXXFLAGS -Werror"],
	[AC_MSG_RESULT(yes)])
   CXXFLAGS="$CXXFLAGS_SAVED"
fi

fi				dnl GXX = yes

AM_CONDITIONAL(GCC_WERROR_OK, test $werror_ok = 1)

# allow building programs with static link.  we need to make it selective
# because loadable modules cannot be statically linked.
AC_ARG_ENABLE([static-link],
AC_HELP_STRING([--enable-static-link],
  [build programs with static link [[default=no]]]),
  [enable_static_link=yes], [enable_static_link=no])
AM_CONDITIONAL(USE_STATIC_LINK, test $enable_static_link = yes)

# Check validity about some libtool options
if test $enable_static_link = yes -a $enable_static = no; then
	AC_MSG_ERROR([--enable-static-link requires --enable-static])
fi
if test $enable_shared = no; then
	AC_MSG_ERROR([BIND 10 requires shared libraries to be built])
fi

# allow configuring without setproctitle.
AC_ARG_ENABLE(setproctitle-check,
AC_HELP_STRING([--disable-setproctitle-check],
  [do not check for python setproctitle module (used to give nice names to python processes)]),
  setproctitle_check=$enableval, setproctitle_check=yes)

# OS dependent configuration
SET_ENV_LIBRARY_PATH=no
ENV_LIBRARY_PATH=LD_LIBRARY_PATH

case "$host" in
*-solaris*)
	# Solaris requires special definitions to get some standard libraries
	# (e.g. getopt(3)) available with common used header files.
	CPPFLAGS="$CPPFLAGS -D_XPG4_2 -D__EXTENSIONS__"
	# "now" binding is necessary to prevent deadlocks in C++ static initialization code
	LDFLAGS="$LDFLAGS -z now"
	;;
*-apple-darwin*)
	# Starting with OSX 10.7 (Lion) we must choose which IPv6 API to use
	# (RFC2292 or RFC3542).
	CPPFLAGS="$CPPFLAGS -D__APPLE_USE_RFC_3542"

	# libtool doesn't work perfectly with Darwin: libtool embeds the
	# final install path in dynamic libraries and our loadable python
	# modules always refer to that path even if it's loaded within the
	# source tree.  This prevents pre-install tests from working.
	# To work around this problem we explicitly specify paths to dynamic
	# libraries when we use them in the source tree.
	SET_ENV_LIBRARY_PATH=yes
	ENV_LIBRARY_PATH=DYLD_LIBRARY_PATH
	;;
*-freebsd*)
	SET_ENV_LIBRARY_PATH=yes
	;;
*-netbsd*)
	SET_ENV_LIBRARY_PATH=yes
	;;
*-openbsd*)
	SET_ENV_LIBRARY_PATH=yes
	;;
esac
AM_CONDITIONAL(SET_ENV_LIBRARY_PATH, test $SET_ENV_LIBRARY_PATH = yes)
AC_SUBST(SET_ENV_LIBRARY_PATH)
AC_SUBST(ENV_LIBRARY_PATH)

m4_define([_AM_PYTHON_INTERPRETER_LIST], [python python3.2 python3.1 python3])
AC_ARG_WITH([pythonpath],
AC_HELP_STRING([--with-pythonpath=PATH],
  [specify an absolute path to python executable when automatic version check (incorrectly) fails]),
  [python_path="$withval"], [python_path="auto"])
if test "$python_path" = auto; then
	AM_PATH_PYTHON([3.1])
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

# We need to store the default pyexecdir in a separate variable so that
# we can specify in Makefile.am the install directory of various BIND 10
# python scripts and loadable modules; in Makefile.am we cannot replace
# $(pyexecdir) using itself, e.g, this doesn't work:
# pyexecdir = $(pyexecdir)/isc/some_module
# The separate variable makes this setup possible as follows:
# pyexecdir = $(PYTHON_SITEPKG_DIR)/isc/some_module
PYTHON_SITEPKG_DIR=${pyexecdir}
AC_SUBST(PYTHON_SITEPKG_DIR)

# This will be commonly used in various Makefile.am's that need to generate
# python log messages.
PYTHON_LOGMSGPKG_DIR="\$(top_builddir)/src/lib/python/isc/log_messages"
AC_SUBST(PYTHON_LOGMSGPKG_DIR)

# This is python package paths commonly used in python tests.  See
# README of log_messages for why it's included.
COMMON_PYTHON_PATH="\$(abs_top_builddir)/src/lib/python/isc/log_messages:\$(abs_top_srcdir)/src/lib/python:\$(abs_top_builddir)/src/lib/python"
AC_SUBST(COMMON_PYTHON_PATH)

# Check for python development environments
if test -x ${PYTHON}-config; then
	PYTHON_INCLUDES=`${PYTHON}-config --includes`

	for flag in `${PYTHON}-config --ldflags`; do
		# add any '-L..." flags to PYTHON_LDFLAGS
		flag=`echo $flag | sed -ne 's/^\(\-L.*\)$/\1/p'`
		if test "X${flag}" != X; then
			PYTHON_LDFLAGS="$PYTHON_LDFLAGS ${flag}"
		fi
	done
	# on some platforms, ${PYTHON}-config --ldflags doesn't provide a -L
	# option while having the library under a non trivial directory.
	# as a workaround we try the "lib" sub directory under the common
	# prefix for this python.
	if test -z "${PYTHON_LDFLAGS}"; then
		PYTHON_LDFLAGS="-L`${PYTHON}-config --prefix`/lib"
	fi
else
	if test "X$PYTHON_INCLUDES" = X -o "X$PYTHON_LDFLAGS" = X; then
		AC_MSG_WARN([${PYTHON}-config does not exist or is not executable, so we could not detect python development environment.  Your system may require an additional package (e.g. "python3-dev").  Alternatively, if you are sure you have python headers and libraries, define PYTHON_INCLUDES and PYTHON_LDFLAGS and run this script.])
	fi
fi

# Some OSes including NetBSD don't install libpython.so in a well known path.
# To avoid requiring dynamic library path with our python wrapper loadable
# modules, we embed the path to the modules when possible.  We do this even
# when the path is known in the common operational environment (e.g. when
# it's stored in a common "hint" file) for simplicity.
if test $rpath_flag != no; then
	python_rpath=
	for flag in ${PYTHON_LDFLAGS}; do
		python_rpath="${python_rpath} `echo $flag | sed -ne "s/^\(\-L\)/${rpath_flag}/p"`"
	done
	PYTHON_LDFLAGS="${PYTHON_LDFLAGS} ${python_rpath}"
fi

AC_SUBST(PYTHON_INCLUDES)
AC_SUBST(PYTHON_LDFLAGS)

CPPFLAGS_SAVED="$CPPFLAGS"
CPPFLAGS="$CPPFLAGS ${PYTHON_INCLUDES}"
AC_CHECK_HEADERS([Python.h],, AC_MSG_ERROR([Missing Python.h]))
CPPFLAGS="$CPPFLAGS_SAVED"

# Check for python library.  Needed for Python-wrapper libraries.
LDFLAGS_SAVED="$LDFLAGS"
LDFLAGS="$LDFLAGS $PYTHON_LDFLAGS"
python_bin="python${PYTHON_VERSION}"
AC_CHECK_LIB($python_bin, main, python_lib=$python_bin, python_lib=no)
if test $python_lib != "no"; then
	PYTHON_LIB="-l$python_lib"
fi
AC_SUBST(PYTHON_LIB)
LDFLAGS=$LDFLAGS_SAVED

# Check for the setproctitle module
if test "$setproctitle_check" = "yes" ; then
    AC_MSG_CHECKING(for setproctitle module)
    if "$PYTHON" -c 'import setproctitle' 2>/dev/null ; then
        AC_MSG_RESULT(ok)
    else
        AC_MSG_RESULT(missing)
        AC_MSG_WARN([Missing setproctitle python module.
Use --disable-setproctitle-check to skip this check.
In this case we will continue, but naming of python processes will not work.])
    fi
fi

# TODO: check for _sqlite3.py module

# (g++ only check)
# Python 3.2 has an unused parameter in one of its headers. This
# has been reported, but not fixed as of yet, so we check if we need
# to set -Wno-unused-parameter.
if test "X$GXX" = "Xyes" -a $werror_ok = 1; then
	CPPFLAGS_SAVED="$CPPFLAGS"
	CPPFLAGS=${PYTHON_INCLUDES}
	CXXFLAGS_SAVED="$CXXFLAGS"
	CXXFLAGS="$CXXFLAGS $B10_CXXFLAGS -Werror"
	AC_MSG_CHECKING([whether we need -Wno-unused-parameter for python])
	AC_TRY_COMPILE(
		[#include <Python.h>],
		[],
		[AC_MSG_RESULT(no)],
		[
		CXXFLAGS="$CXXFLAGS -Wno-unused-parameter"
		AC_TRY_COMPILE([#include <Python.h>],
		[],
		[AC_MSG_RESULT(yes)
		 PYTHON_CXXFLAGS="${PYTHON_CXXFLAGS} -Wno-unused-parameter"
		 AC_SUBST(PYTHON_CXXFLAGS)
		],
		[AC_MSG_ERROR([Can't compile against Python.h.  If you're using MacOS X and have installed Python with Homebrew, see http://bind10.isc.org/wiki/SystemNotesMacOSX])]
                )
                ]
	)
	CXXFLAGS="$CXXFLAGS_SAVED"
	CPPFLAGS="$CPPFLAGS_SAVED"
fi

# produce PIC unless we disable shared libraries. need this for python bindings.
if test $enable_shared != "no" -a "X$GXX" = "Xyes"; then
   B10_CXXFLAGS="$B10_CXXFLAGS -fPIC"
fi

AC_SUBST(B10_CXXFLAGS)

# Checks for libraries.

AC_SEARCH_LIBS(inet_pton, [nsl])
AC_SEARCH_LIBS(recvfrom, [socket])
AC_SEARCH_LIBS(nanosleep, [rt])

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_TYPE_SIZE_T


# Detect OS type (it may be used to do OS-specific things, e.g.
# interface detection in DHCP)
AC_MSG_CHECKING(OS family)
system=`uname -s`
case $system in
    Linux)
      OS_TYPE="Linux"
      CPPFLAGS="$CPPFLAGS -DOS_LINUX"
      ;;
    Darwin | FreeBSD | NetBSD | OpenBSD)
      OS_TYPE="BSD"
      CPPFLAGS="$CPPFLAGS -DOS_BSD"
      ;;
    SunOS)
      OS_TYPE="Solaris"
      CPPFLAGS="$CPPFLAGS -DOS_SUN"
      ;;
    *)
      OS_TYPE="Unknown"
      AC_MSG_WARN("Unsupported OS: uname returned $system")
      ;;
esac
AC_MSG_RESULT($OS_TYPE)

AM_CONDITIONAL(OS_LINUX, test $OS_TYPE = Linux)
AM_COND_IF([OS_LINUX], [AC_DEFINE([OS_LINUX], [1], [Running on Linux?])])
AM_CONDITIONAL(OS_BSD, test $OS_TYPE = BSD)
AM_COND_IF([OS_BSD], [AC_DEFINE([OS_BSD], [1], [Running on BSD?])])
AM_CONDITIONAL(OS_SOLARIS, test $OS_TYPE = Solaris)
AM_COND_IF([OS_SOLARIS], [AC_DEFINE([OS_SOLARIS], [1], [Running on Solaris?])])

AC_MSG_CHECKING(for sa_len in struct sockaddr)
AC_TRY_COMPILE([
#include <sys/types.h>
#include <sys/socket.h>],
[struct sockaddr sa; sa.sa_len = 0; return (0);],
        [AC_MSG_RESULT(yes)
        AC_DEFINE(HAVE_SA_LEN, 1, [Define to 1 if sockaddr has a sa_len member, and corresponding sin_len and sun_len])],
        AC_MSG_RESULT(no))

AC_ARG_WITH(pycoverage,
[  --with-pycoverage[=PROGRAM]         enable python code coverage using the specified coverage], pycoverage="$withval", pycoverage="no")
if test "$pycoverage" = "no" ; then
	# just run the tests normally with python
	PYCOVERAGE_RUN="${PYTHON}"
	USE_PYCOVERAGE="no"
elif test "$pycoverage" = "yes" ; then
	PYCOVERAGE="coverage"
	PYCOVERAGE_RUN="${PYCOVERAGE} run --branch --append"
	USE_PYCOVERAGE="yes"
else
	PYCOVERAGE="$pycoverage"
	PYCOVERAGE_RUN="${PYCOVERAGE} run --branch --append"
	USE_PYCOVERAGE="yes"
fi
AM_CONDITIONAL(ENABLE_PYTHON_COVERAGE, test x$USE_PYCOVERAGE != xno)
AC_SUBST(PYCOVERAGE)
AC_SUBST(PYCOVERAGE_RUN)
AC_SUBST(USE_PYCOVERAGE)

enable_gtest="no"
GTEST_INCLUDES=

AC_ARG_WITH([gtest-source],
            [AS_HELP_STRING([--with-gtest-source=PATH],
                            [location of the Googletest source, defaults to /usr/src/gtest])],
            [enable_gtest="yes" ; GTEST_SOURCE="$withval"],
            [GTEST_SOURCE="/usr/src/gtest"])

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
	GENHTML=`echo "$LCOV" | sed s/lcov$/genhtml/`
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
            BOTAN_LIBS=`$BOTAN_TOOL $TOOL_ARG --libs`
            LIBS_SAVED=${LIBS}
            LIBS="$LIBS $BOTAN_LIBS"
            BOTAN_INCLUDES=`$BOTAN_TOOL $TOOL_ARG --cflags`
            CPPFLAGS_SAVED=${CPPFLAGS}
            CPPFLAGS="$BOTAN_INCLUDES $CPPFLAGS"
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
AC_ARG_WITH([botan-config],
  AC_HELP_STRING([--with-botan-config=PATH],
    [specify the path to the botan-config script]),
    [botan_config="$withval"])
if test "${botan_config}" = "no" ; then
    AC_MSG_ERROR([Need botan for libcryptolink])
fi
if test "${botan_config}" != "yes" ; then
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
    BOTAN_LIBS=`${BOTAN_CONFIG} --libs`
    BOTAN_INCLUDES=`${BOTAN_CONFIG} --cflags`

    # We expect botan-config --libs to contain -L<path_to_libbotan>, but
    # this is not always the case.  As a heuristics workaround we add
    # -L`botan-config --prefix/lib` in this case (if not present already).
    # Same for BOTAN_INCLUDES (but using include instead of lib) below.
    if [ ${BOTAN_CONFIG} --prefix >/dev/null 2>&1 ] ; then
        echo ${BOTAN_LIBS} | grep -- -L > /dev/null || \
            BOTAN_LIBS="-L`${BOTAN_CONFIG} --prefix`/lib ${BOTAN_LIBS}"
        echo ${BOTAN_INCLUDES} | grep -- -I > /dev/null || \
            BOTAN_INCLUDES="-I`${BOTAN_CONFIG} --prefix`/include ${BOTAN_INCLUDES}"
    fi
fi
# botan-config script (and the way we call pkg-config) returns -L and -l
# as one string, but we need them in separate values
BOTAN_LDFLAGS=
BOTAN_NEWLIBS=
for flag in ${BOTAN_LIBS}; do
    BOTAN_LDFLAGS="${BOTAN_LDFLAGS} `echo $flag | sed -ne '/^\(\-L\)/p'`"
    BOTAN_LIBS="${BOTAN_LIBS} `echo $flag | sed -ne '/^\(\-l\)/p'`"
done

# See python_rpath for some info on why we do this
if test $rpath_flag != no; then
    BOTAN_RPATH=
    for flag in ${BOTAN_LIBS}; do
            BOTAN_RPATH="${BOTAN_RPATH} `echo $flag | sed -ne "s/^\(\-L\)/${rpath_flag}/p"`"
    done
AC_SUBST(BOTAN_RPATH)

# According to the libtool manual, it should be sufficient if we
# specify the "-R libdir" in our wrapper library of botan (no other
# programs will need libbotan directly); "libdir" should be added to
# the program's binary image.  But we've seen in our build environments
# that (some versions of?) libtool doesn't propagate -R as documented,
# and it caused a linker error at run time.  To work around this, we
# also add the rpath to the global LDFLAGS.
    LDFLAGS="$BOTAN_RPATH $LDFLAGS"
fi

AC_SUBST(BOTAN_LDFLAGS)
AC_SUBST(BOTAN_LIBS)
AC_SUBST(BOTAN_INCLUDES)

# Even though chances are high we already performed a real compilation check
# in the search for the right (pkg)config data, we try again here, to
# be sure.
CPPFLAGS_SAVED=$CPPFLAGS
CPPFLAGS="$BOTAN_INCLUDES $CPPFLAGS"
LIBS_SAVED="$LIBS"
LIBS="$LIBS $BOTAN_LIBS"
AC_CHECK_HEADERS([botan/botan.h],,AC_MSG_ERROR([Missing required header files.]))
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
         AC_MSG_ERROR([Needs Botan library 1.8 or higher. On some systems,
         the botan package has a few missing dependencies (libbz2 and
         libgmp), if libbotan has been installed and you see this error,
         try upgrading to a higher version of botan or installing libbz2
         and libgmp.])]
)
CPPFLAGS=$CPPFLAGS_SAVED
LIBS=$LIBS_SAVED

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

CPPFLAGS=$CPPFLAGS_SAVED
LIBS=$LIBS_SAVED

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
CPPFLAGS_SAVES="$CPPFLAGS"
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

# Boost offset_ptr is required in one library (not optional right now), and
# it's known it doesn't compile on some platforms, depending on boost version,
# its local configuration, and compiler.
AC_MSG_CHECKING([Boost offset_ptr compiles])
AC_TRY_COMPILE([
#include <boost/interprocess/offset_ptr.hpp>
],,
[AC_MSG_RESULT(yes)],
[AC_MSG_RESULT(no)
 AC_MSG_ERROR([Failed to compile a required header file.  Try upgrading Boost to 1.44 or higher (when using clang++) or specifying --without-werror.  See the ChangeLog entry for Trac no. 2147 for more details.])])

CPPFLAGS="$CPPFLAGS_SAVES $CPPFLAGS_BOOST_THREADCONF"
AC_SUBST(BOOST_INCLUDES)

# I can't get some of the #include <asio.hpp> right without this
# TODO: find the real cause of asio/boost wanting pthreads
# (this currently only occurs for src/lib/cc/session_unittests)
PTHREAD_LDFLAGS=
AC_CHECK_LIB(pthread, pthread_create,[ PTHREAD_LDFLAGS=-lpthread ], [])
AC_SUBST(PTHREAD_LDFLAGS)
AC_SUBST(MULTITHREADING_FLAG)

#
# Check availability of gtest, which will be used for unit tests.
#
GTEST_LDFLAGS=
GTEST_LDADD=
# TODO: set DISTCHECK_GTEST_CONFIGURE_FLAG for --with-gtest too
DISTCHECK_GTEST_CONFIGURE_FLAG=

if test "x$enable_gtest" = "xyes" ; then

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
          GTEST_LDFLAGS="\$(top_builddir)/libgtest.a"
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

dnl check for pkg-config itself so we don't try the m4 macro without pkg-config
AC_CHECK_PROG(HAVE_PKG_CONFIG, pkg-config, yes, no)
if test "x$HAVE_PKG_CONFIG" = "xno" ; then
  AC_MSG_ERROR(Please install pkg-config)
fi
PKG_CHECK_MODULES(SQLITE, sqlite3 >= 3.3.9, enable_features="$enable_features SQLite3")

#
# ASIO: we extensively use it as the C++ event management module.
#
# Use local ASIO headers from ext
#
CPPFLAGS="$CPPFLAGS -I\$(top_srcdir)/ext/asio"
#
# Use our 'coroutine' header from ext
CPPFLAGS="$CPPFLAGS -I\$(top_srcdir)/ext/coroutine"
#
# Disable threads: Currently we don't use them.
CPPFLAGS="$CPPFLAGS -DASIO_DISABLE_THREADS=1"

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
	CPPFLAGS="$CPPFLAGS -DASIO_DISABLE_DEV_POLL=1"
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

# Check for xsltproc
if test "x$enable_generate_docs" != xno ; then
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
fi


AM_CONDITIONAL(GENERATE_DOCS, test x$enable_generate_docs != xno)

AC_ARG_ENABLE(install-configurations,
  [AC_HELP_STRING([--disable-install-configurations],
  [do not install configuration])], install_configurations=$enableval, install_configurations=yes)

AM_CONDITIONAL(INSTALL_CONFIGURATIONS, test x$install_configurations = xyes || test x$install_configurations = xtrue)

AC_ARG_ENABLE(logger-checks, [AC_HELP_STRING([--enable-logger-checks],
  [check logger messages [default=no]])], enable_logger_checks=$enableval, enable_logger_checks=no)
AM_CONDITIONAL(ENABLE_LOGGER_CHECKS, test x$enable_logger_checks != xno)
AM_COND_IF([ENABLE_LOGGER_CHECKS], [AC_DEFINE([ENABLE_LOGGER_CHECKS], [1], [Check logger messages?])])

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

AC_CONFIG_FILES([Makefile
                 doc/Makefile
                 doc/guide/Makefile
                 compatcheck/Makefile
                 src/Makefile
                 src/bin/Makefile
                 src/bin/bind10/Makefile
                 src/bin/bind10/tests/Makefile
                 src/bin/cmdctl/Makefile
                 src/bin/cmdctl/tests/Makefile
                 src/bin/bindctl/Makefile
                 src/bin/bindctl/tests/Makefile
                 src/bin/cfgmgr/Makefile
                 src/bin/cfgmgr/plugins/Makefile
                 src/bin/cfgmgr/plugins/tests/Makefile
                 src/bin/cfgmgr/tests/Makefile
                 src/bin/dbutil/Makefile
                 src/bin/dbutil/tests/Makefile
                 src/bin/dbutil/tests/testdata/Makefile
                 src/bin/loadzone/Makefile
                 src/bin/loadzone/tests/correct/Makefile
                 src/bin/loadzone/tests/error/Makefile
                 src/bin/msgq/Makefile
                 src/bin/msgq/tests/Makefile
                 src/bin/auth/Makefile
                 src/bin/auth/tests/Makefile
                 src/bin/auth/tests/testdata/Makefile
                 src/bin/auth/benchmarks/Makefile
                 src/bin/ddns/Makefile
                 src/bin/ddns/tests/Makefile
                 src/bin/dhcp6/Makefile
                 src/bin/dhcp6/tests/Makefile
                 src/bin/dhcp4/Makefile
                 src/bin/dhcp4/tests/Makefile
                 src/bin/resolver/Makefile
                 src/bin/resolver/tests/Makefile
                 src/bin/sysinfo/Makefile
                 src/bin/sockcreator/Makefile
                 src/bin/sockcreator/tests/Makefile
                 src/bin/xfrin/Makefile
                 src/bin/xfrin/tests/Makefile
                 src/bin/xfrin/tests/testdata/Makefile
                 src/bin/xfrout/Makefile
                 src/bin/xfrout/tests/Makefile
                 src/bin/zonemgr/Makefile
                 src/bin/zonemgr/tests/Makefile
                 src/bin/stats/Makefile
                 src/bin/stats/tests/Makefile
                 src/bin/stats/tests/testdata/Makefile
                 src/bin/usermgr/Makefile
                 src/bin/tests/Makefile
                 src/lib/Makefile
                 src/lib/asiolink/Makefile
                 src/lib/asiolink/tests/Makefile
                 src/lib/asiodns/Makefile
                 src/lib/asiodns/tests/Makefile
                 src/lib/bench/Makefile
                 src/lib/bench/example/Makefile
                 src/lib/bench/tests/Makefile
                 src/lib/cc/Makefile
                 src/lib/cc/tests/Makefile
                 src/lib/python/Makefile
                 src/lib/python/isc/Makefile
                 src/lib/python/isc/acl/Makefile
                 src/lib/python/isc/acl/tests/Makefile
                 src/lib/python/isc/util/Makefile
                 src/lib/python/isc/util/tests/Makefile
                 src/lib/python/isc/util/cio/Makefile
                 src/lib/python/isc/util/cio/tests/Makefile
                 src/lib/python/isc/datasrc/Makefile
                 src/lib/python/isc/datasrc/tests/Makefile
                 src/lib/python/isc/dns/Makefile
                 src/lib/python/isc/cc/Makefile
                 src/lib/python/isc/cc/tests/Makefile
                 src/lib/python/isc/config/Makefile
                 src/lib/python/isc/config/tests/Makefile
                 src/lib/python/isc/log/Makefile
                 src/lib/python/isc/log/tests/Makefile
                 src/lib/python/isc/log_messages/Makefile
                 src/lib/python/isc/log_messages/work/Makefile
                 src/lib/python/isc/net/Makefile
                 src/lib/python/isc/net/tests/Makefile
                 src/lib/python/isc/notify/Makefile
                 src/lib/python/isc/notify/tests/Makefile
                 src/lib/python/isc/testutils/Makefile
                 src/lib/python/isc/bind10/Makefile
                 src/lib/python/isc/bind10/tests/Makefile
                 src/lib/python/isc/ddns/Makefile
                 src/lib/python/isc/ddns/tests/Makefile
                 src/lib/python/isc/xfrin/Makefile
                 src/lib/python/isc/xfrin/tests/Makefile
                 src/lib/python/isc/server_common/Makefile
                 src/lib/python/isc/server_common/tests/Makefile
                 src/lib/python/isc/sysinfo/Makefile
                 src/lib/python/isc/sysinfo/tests/Makefile
                 src/lib/config/Makefile
                 src/lib/config/tests/Makefile
                 src/lib/config/tests/testdata/Makefile
                 src/lib/cryptolink/Makefile
                 src/lib/cryptolink/tests/Makefile
                 src/lib/dns/Makefile
                 src/lib/dns/tests/Makefile
                 src/lib/dns/tests/testdata/Makefile
                 src/lib/dns/python/Makefile
                 src/lib/dns/python/tests/Makefile
                 src/lib/dns/benchmarks/Makefile
                 src/lib/dhcp/Makefile
                 src/lib/dhcp/tests/Makefile
                 src/lib/exceptions/Makefile
                 src/lib/exceptions/tests/Makefile
                 src/lib/datasrc/Makefile
                 src/lib/datasrc/memory/Makefile
                 src/lib/datasrc/memory/benchmarks/Makefile
                 src/lib/datasrc/tests/Makefile
                 src/lib/datasrc/tests/testdata/Makefile
                 src/lib/datasrc/tests/memory/Makefile
                 src/lib/datasrc/tests/memory/testdata/Makefile
                 src/lib/xfr/Makefile
                 src/lib/xfr/tests/Makefile
                 src/lib/log/Makefile
                 src/lib/log/compiler/Makefile
                 src/lib/log/tests/Makefile
                 src/lib/resolve/Makefile
                 src/lib/resolve/tests/Makefile
                 src/lib/testutils/Makefile
                 src/lib/testutils/testdata/Makefile
                 src/lib/nsas/Makefile
                 src/lib/nsas/tests/Makefile
                 src/lib/cache/Makefile
                 src/lib/cache/tests/Makefile
                 src/lib/server_common/Makefile
                 src/lib/server_common/tests/Makefile
                 src/lib/util/Makefile
                 src/lib/util/io/Makefile
                 src/lib/util/threads/Makefile
                 src/lib/util/threads/tests/Makefile
                 src/lib/util/unittests/Makefile
                 src/lib/util/python/Makefile
                 src/lib/util/pyunittests/Makefile
                 src/lib/util/tests/Makefile
                 src/lib/acl/Makefile
                 src/lib/acl/tests/Makefile
                 src/lib/statistics/Makefile
                 src/lib/statistics/tests/Makefile
                 tests/Makefile
                 tests/system/Makefile
                 tests/tools/Makefile
                 tests/tools/badpacket/Makefile
                 tests/tools/badpacket/tests/Makefile
                 tests/tools/perfdhcp/Makefile
                 tests/tools/perfdhcp/tests/Makefile
                 tests/tools/perfdhcp/templates/Makefile
                 dns++.pc
               ])
AC_OUTPUT([doc/version.ent
           src/bin/cfgmgr/b10-cfgmgr.py
           src/bin/cfgmgr/tests/b10-cfgmgr_test.py
           src/bin/cfgmgr/plugins/datasrc.spec.pre
           src/bin/cmdctl/cmdctl.py
           src/bin/cmdctl/run_b10-cmdctl.sh
           src/bin/cmdctl/tests/cmdctl_test
           src/bin/cmdctl/cmdctl.spec.pre
           src/bin/dbutil/dbutil.py
           src/bin/dbutil/run_dbutil.sh
           src/bin/dbutil/tests/dbutil_test.sh
           src/bin/ddns/ddns.py
           src/bin/xfrin/tests/xfrin_test
           src/bin/xfrin/xfrin.py
           src/bin/xfrin/run_b10-xfrin.sh
           src/bin/xfrout/xfrout.py
           src/bin/xfrout/xfrout.spec.pre
           src/bin/xfrout/tests/xfrout_test
           src/bin/xfrout/tests/xfrout_test.py
           src/bin/xfrout/run_b10-xfrout.sh
           src/bin/resolver/resolver.spec.pre
           src/bin/resolver/spec_config.h.pre
           src/bin/zonemgr/zonemgr.py
           src/bin/zonemgr/zonemgr.spec.pre
           src/bin/zonemgr/tests/zonemgr_test
           src/bin/zonemgr/run_b10-zonemgr.sh
           src/bin/sysinfo/sysinfo.py
           src/bin/stats/stats.py
           src/bin/stats/stats_httpd.py
           src/bin/bind10/bind10_src.py
           src/bin/bind10/run_bind10.sh
           src/bin/bind10/tests/bind10_test.py
           src/bin/bindctl/run_bindctl.sh
           src/bin/bindctl/bindctl_main.py
           src/bin/bindctl/tests/bindctl_test
           src/bin/loadzone/run_loadzone.sh
           src/bin/loadzone/tests/correct/correct_test.sh
           src/bin/loadzone/tests/error/error_test.sh
           src/bin/loadzone/b10-loadzone.py
           src/bin/usermgr/run_b10-cmdctl-usermgr.sh
           src/bin/usermgr/b10-cmdctl-usermgr.py
           src/bin/msgq/msgq.py
           src/bin/msgq/tests/msgq_test
           src/bin/msgq/run_msgq.sh
           src/bin/auth/auth.spec.pre
           src/bin/auth/spec_config.h.pre
           src/bin/dhcp4/spec_config.h.pre
           src/bin/dhcp6/spec_config.h.pre
           src/bin/tests/process_rename_test.py
           src/lib/config/tests/data_def_unittests_config.h
           src/lib/python/isc/config/tests/config_test
           src/lib/python/isc/cc/tests/cc_test
           src/lib/python/isc/notify/tests/notify_out_test
           src/lib/python/isc/log/tests/log_console.py
           src/lib/python/isc/log_messages/work/__init__.py
           src/lib/dns/gen-rdatacode.py
           src/lib/python/bind10_config.py
           src/lib/cc/session_config.h.pre
           src/lib/cc/tests/session_unittests_config.h
           src/lib/datasrc/datasrc_config.h.pre
           src/lib/log/tests/console_test.sh
           src/lib/log/tests/destination_test.sh
           src/lib/log/tests/init_logger_test.sh
           src/lib/log/tests/local_file_test.sh
           src/lib/log/tests/logger_lock_test.sh
           src/lib/log/tests/severity_test.sh
           src/lib/log/tests/tempdir.h
           src/lib/util/python/mkpywrapper.py
           src/lib/util/python/gen_wiredata.py
           src/lib/server_common/tests/data_path.h
           tests/lettuce/setup_intree_bind10.sh
           tests/system/conf.sh
           tests/system/run.sh
           tests/system/glue/setup.sh
           tests/system/glue/nsx1/b10-config.db
           tests/system/bindctl/nsx1/b10-config.db.template
           tests/system/ixfr/db.example.n0
           tests/system/ixfr/db.example.n2
           tests/system/ixfr/db.example.n2.refresh
           tests/system/ixfr/db.example.n4
           tests/system/ixfr/db.example.n6
           tests/system/ixfr/ixfr_init.sh
           tests/system/ixfr/b10-config.db
           tests/system/ixfr/common_tests.sh
           tests/system/ixfr/in-1/setup.sh
           tests/system/ixfr/in-2/setup.sh
           tests/system/ixfr/in-3/setup.sh
           tests/system/ixfr/in-4/setup.sh
          ], [
           chmod +x src/bin/cmdctl/run_b10-cmdctl.sh
           chmod +x src/bin/xfrin/run_b10-xfrin.sh
           chmod +x src/bin/xfrout/run_b10-xfrout.sh
           chmod +x src/bin/zonemgr/run_b10-zonemgr.sh
           chmod +x src/bin/bind10/run_bind10.sh
           chmod +x src/bin/cmdctl/tests/cmdctl_test
           chmod +x src/bin/dbutil/run_dbutil.sh
           chmod +x src/bin/dbutil/tests/dbutil_test.sh
           chmod +x src/bin/xfrin/tests/xfrin_test
           chmod +x src/bin/xfrout/tests/xfrout_test
           chmod +x src/bin/zonemgr/tests/zonemgr_test
           chmod +x src/bin/bindctl/tests/bindctl_test
           chmod +x src/bin/bindctl/run_bindctl.sh
           chmod +x src/bin/loadzone/run_loadzone.sh
           chmod +x src/bin/loadzone/tests/correct/correct_test.sh
           chmod +x src/bin/loadzone/tests/error/error_test.sh
           chmod +x src/bin/usermgr/run_b10-cmdctl-usermgr.sh
           chmod +x src/bin/msgq/run_msgq.sh
           chmod +x src/bin/msgq/tests/msgq_test
           chmod +x src/lib/dns/gen-rdatacode.py
           chmod +x src/lib/log/tests/console_test.sh
           chmod +x src/lib/log/tests/destination_test.sh
           chmod +x src/lib/log/tests/init_logger_test.sh
           chmod +x src/lib/log/tests/local_file_test.sh
           chmod +x src/lib/log/tests/logger_lock_test.sh
           chmod +x src/lib/log/tests/severity_test.sh
           chmod +x src/lib/util/python/mkpywrapper.py
           chmod +x src/lib/util/python/gen_wiredata.py
           chmod +x src/lib/python/isc/log/tests/log_console.py
           chmod +x tests/system/conf.sh
           chmod +x tests/system/run.sh
           chmod +x tests/system/ixfr/ixfr_init.sh
           chmod +x tests/system/ixfr/common_tests.sh
           chmod +x tests/system/ixfr/in-1/setup.sh
           chmod +x tests/system/ixfr/in-2/setup.sh
           chmod +x tests/system/ixfr/in-3/setup.sh
           chmod +x tests/system/ixfr/in-4/setup.sh
          ])
AC_OUTPUT

dnl Print the results
dnl

cat > config.report << END

     BIND 10 source configure results:
    -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

Package:
  Name:          $PACKAGE_NAME
  Version:       $PACKAGE_VERSION

C++ Compiler:    $CXX

Flags:
  DEFS:          $DEFS
  CPPFLAGS:      $CPPFLAGS
  CXXFLAGS:      $CXXFLAGS
  LDFLAGS:       $LDFLAGS
  B10_CXXFLAGS:  $B10_CXXFLAGS
  OS Family:     $OS_TYPE
dnl includes too
  Python:        ${PYTHON_INCLUDES}
                 ${PYTHON_CXXFLAGS}
                 ${PYTHON_LDFLAGS}
                 ${PYTHON_LIB}
  Boost:         ${BOOST_INCLUDES}
  Botan:         ${BOTAN_INCLUDES}
                 ${BOTAN_LDFLAGS}
                 ${BOTAN_LIBS}
  Log4cplus:     ${LOG4CPLUS_INCLUDES}
                 ${LOG4CPLUS_LIBS}
  SQLite:        $SQLITE_CFLAGS
                 $SQLITE_LIBS

Features:
  $enable_features

Developer:
  Google Tests: $enable_gtest
  Valgrind: $found_valgrind
  C++ Code Coverage: $USE_LCOV
  Python Code Coverage: $USE_PYCOVERAGE
  Logger checks: $enable_logger_checks
  Generate Documentation: $enable_generate_docs

END

cat config.report
cat <<EOF

  Now you can type "make" to build BIND 10

EOF
