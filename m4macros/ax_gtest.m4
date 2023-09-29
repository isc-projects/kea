AC_DEFUN([AX_ISC_GTEST], [

enable_gtest="no"
GTEST_INCLUDES=

AC_ARG_WITH([gtest-source],
            [AS_HELP_STRING([--with-gtest-source[[=PATH]]],
                            [location of the Googletest source])],
            [enable_gtest="yes" ; GTEST_SOURCE="$withval"])

AC_ARG_WITH([gtest],
            [AS_HELP_STRING([--with-gtest[[=PATH]]],
                            [specify a path to gtest header files (PATH/include) and library (PATH/lib)])],
        [gtest_path="$withval"; enable_gtest="yes"], [gtest_path="no"])

AC_ARG_WITH([lcov],
            [AS_HELP_STRING([--with-lcov[[=PROGRAM]]],
                            [enable gtest and coverage target using the specified lcov])],
                            [lcov="$withval"],
                            [lcov="no"])

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

        AC_MSG_CHECKING([for gtest source])

        if test "x$GTEST_SOURCE" = "xyes" ; then

            # If not specified, try some common paths.
            GTEST_SOURCE=
            for d in /usr/src/googletest /usr/src/gtest /usr/local /usr/pkg /opt /opt/local ; do
                if test ! -d "$d"/src -a -d "$d"/googletest; then
                    d=$d/googletest
                fi
                if test -f $d/src/gtest-all.cc -a -f $d/src/gtest_main.cc; then
                    GTEST_SOURCE=$d
                    AC_MSG_RESULT([$GTEST_SOURCE])
                    break
                fi
            done
            if test -z $GTEST_SOURCE ; then
                AC_MSG_ERROR([no gtest sources found])
            fi
        else
            if test ! -d $GTEST_SOURCE/src -a -d $GTEST_SOURCE/googletest; then
                GTEST_SOURCE=$GTEST_SOURCE/googletest
            fi
            if test -f $GTEST_SOURCE/src/gtest-all.cc -a -f $GTEST_SOURCE/src/gtest_main.cc; then
                AC_MSG_RESULT([$GTEST_SOURCE])
            else
                AC_MSG_ERROR([no gtest source at $GTEST_SOURCE])
            fi
        fi
        have_gtest_source=yes

        GTEST_LDADD="\$(top_builddir)/ext/gtest/libgtest.a"
        DISTCHECK_GTEST_CONFIGURE_FLAG="--with-gtest-source=$GTEST_SOURCE"
        GTEST_INCLUDES="-I$GTEST_SOURCE -I$GTEST_SOURCE/include"
        GTEST_VERSION="$(basename $GTEST_SOURCE)"

        # Versions starting from 1.8.0 are put in the googletest directory. If the basename
        # returns googletest string, we need to cut it off and try basename again.
        cmakelists=
        if test "$GTEST_VERSION" = "googletest"; then
            GTEST_VERSION=${GTEST_SOURCE%"/googletest"}
            cmakelists="$GTEST_VERSION/CMakeLists.txt"
            GTEST_VERSION=$(basename "$GTEST_VERSION")
        fi
        GTEST_VERSION="${GTEST_VERSION#googletest-release-}"
        GTEST_VERSION="${GTEST_VERSION#gtest-}"
        GTEST_VERSION="${GTEST_VERSION#googletest-}"

        posix_regex=$(expr "5" : "\([[:digit:]]\)")
        if test "${posix_regex}" = "5" ; then
            semver_regex='[^[:digit:]]\{0,\}\([[:digit:]]\{1,\}\.[[:digit:]]\{1,\}\.[[:digit:]]\{1,\}\).\{0,\}'
        else
            semver_regex='[[^0-9]]\{0,\}\([[0-9]]\{1,\}\.[[0-9]]\{1,\}\.[[0-9]]\{1,\}\).\{0,\}'
        fi

        gtest_version_candidate=
        gtest_version_candidate=$(expr "$GTEST_VERSION" : "$semver_regex")
        gtest_version_found="no"

        if test -z "$gtest_version_candidate" ; then
            # If the GTEST_VERSION is still not correct semver, we need to determine googletest version in other way.
            # Let's try to extract it from CMake build script used by Google Test starting from version 1.8.0.
            if test -f "$cmakelists" ; then
                gtest_version_line=$($AWK '/set\(GOOGLETEST_VERSION/ { print }' "$cmakelists")
                gtest_version_candidate=$(expr "$gtest_version_line" : "$semver_regex")
                if test -n "$gtest_version_candidate"; then
                    gtest_version_found="yes"
                    GTEST_VERSION=$gtest_version_candidate
                fi
            fi
            if test $gtest_version_found = "no" ; then
                # Try to get googletest version from debian/ubuntu package
                AC_PATH_PROG(DPKG, dpkg)
                AC_PATH_PROG(DPKGQUERY, dpkg-query)
                if test -n "${DPKG}" -a -n "${DPKGQUERY}"; then
                    # Let's check if there is a googletest package owning files under given GTEST_SOURCE path
                    ${DPKG} -S "$GTEST_SOURCE" 2>/dev/null | grep googletest >/dev/null 2>&1
                    if test $? -eq 0; then
                        gtest_version_found="yes"
                        GTEST_VERSION="$(${DPKGQUERY} --showformat='${Version}' --show googletest | cut -d'-' -f1)"
                    fi
                fi
            fi
        else
            gtest_version_found="yes"
            GTEST_VERSION=$gtest_version_candidate
        fi

        if test $gtest_version_found = "no" ; then
            AC_MSG_WARN([Could not find GTEST version])
            GTEST_VERSION="unknown"
        fi
    fi

    if test "$gtest_path" != "no" ; then
        if test "$gtest_path" != "yes"; then
            GTEST_PATHS=$gtest_path
            AC_PATH_PROG([GTEST_CONFIG], [gtest-config], [], [${gtest_path}/bin])
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
            AC_MSG_CHECKING([for gtest lib path])
            GTEST_FOUND="false"
            for dir in $GTEST_PATHS; do
                if test -f "$dir/include/gtest/gtest.h"; then
                    if test -f "$dir/lib/libgtest.a" || \
                       test -f "$dir/lib/libgtest.so"; then
                        GTEST_INCLUDES="-I$dir/include"
                        GTEST_LDFLAGS="-L$dir/lib"
                        GTEST_LDADD="-lgtest"
                        GTEST_FOUND="true"
                        AC_MSG_RESULT([$dir/lib])
                        if test -f "$dir/lib/pkgconfig/gtest.pc" ; then
                            AX_FIND_LIBRARY([gtest], ["$dir/lib/pkgconfig/gtest.pc"])
                            if "${LIBRARY_FOUND}"; then
                              GTEST_VERSION="${LIBRARY_VERSION}"
                            fi
                        fi
                        break
                    elif test -f "$dir/lib/$dumpmachine/libgtest.a" || \
                         test -f "$dir/lib/$dumpmachine/libgtest.so"; then
                        GTEST_INCLUDES="-I$dir/include"
                        # check also multiarch dir in debian/ubuntu distributions
                        GTEST_LDFLAGS="-L$dir/lib/$dumpmachine"
                        GTEST_LDADD="-lgtest"
                        GTEST_FOUND="true"
                        AC_MSG_RESULT([$dir/lib/$dumpmachine])
                        if test -f "$dir/lib/$dumpmachine/pkgconfig/gtest.pc" ; then
                            AX_FIND_LIBRARY([gtest], ["$dir/lib/$dumpmachine/pkgconfig/gtest.pc"])
                            if "${LIBRARY_FOUND}"; then
                              GTEST_VERSION="${LIBRARY_VERSION}"
                            fi
                        fi
                        break
                    else
                        AC_MSG_WARN([Found Google Test include but not the library in $dir.])
                    fi
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

])dnl AX_ISC_GTEST
