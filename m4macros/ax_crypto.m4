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
                [AC_LANG_PROGRAM([#include <botan/hash.h>],
                                 [using namespace Botan;
                                  auto h = HashFunction::create("MD5");
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
# End of ACX_TRY_BOTAN_TOOL


AC_DEFUN([AX_CRYPTO], [
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

# Avoid checking Botan if OpenSSL is wanted
AC_ARG_WITH([openssl],
            [AS_HELP_STRING([--with-openssl[[=PATH]]], [Enables OpenSSL,
            location can be specified optionally])],
            [use_openssl="$withval"],
            [use_openssl="auto"])

use_botan="yes"
if test "${use_openssl}" != "auto" -a "${use_openssl}" != "no" ; then
   use_botan="no"
fi
AC_ARG_WITH([botan],
  [AS_HELP_STRING([--with-botan[[=PATH]]],
  [Enables Botan, name to the pkg-config library can be specified optionally])],
  [use_botan="$withval"])
if test "${use_botan}" = ""; then
    use_botan="yes"
fi
distcheck_botan="--with-botan=${use_botan}"
if test "${use_botan}" = "no" ; then
    if test "${use_openssl}" = "no" ; then
       AC_MSG_ERROR([Need Botan or OpenSSL for libcryptolink])
    fi
elif test "${use_botan}" != "yes" ; then
    BOTAN_VERSIONS="${use_botan}"
else
    BOTAN_VERSIONS="botan-2"
fi

BOTAN_CONFIG=""
AC_PATH_PROG([PKG_CONFIG], [pkg-config])
if test "$PKG_CONFIG" != "" ; then
    for version in $BOTAN_VERSIONS; do
        ACX_TRY_BOTAN_TOOL([pkg-config], ["$version --silence-errors"],
                           [BOTAN_CONFIG="$PKG_CONFIG $version"])
        if test "$BOTAN_CONFIG" != "" ; then
            CRYPTO_LIBS=`${BOTAN_CONFIG} --libs`
            CRYPTO_INCLUDES=`${BOTAN_CONFIG} --cflags`
            break
        fi
    done
fi

if test "x${CRYPTO_LIBS}" != "x"
then
   dnl Determine the Botan version
   AC_MSG_CHECKING([Botan version])
   cat > conftest.cpp << EOF
#include <botan/version.h>
AUTOCONF_BOTAN_VERSION=BOTAN_VERSION_MAJOR . BOTAN_VERSION_MINOR . BOTAN_VERSION_PATCH
EOF

   CRYPTO_VERSION=`$CPPP $CPPFLAGS $CRYPTO_INCLUDES conftest.cpp | grep '^AUTOCONF_BOTAN_VERSION=' | $SED -e 's/^AUTOCONF_BOTAN_VERSION=//' -e 's/[[    ]]//g' -e 's/"//g' 2> /dev/null`
   if test -z "$CRYPTO_VERSION"; then
      CRYPTO_VERSION="unknown"
   fi
   $RM -f conftest.cpp
   AC_MSG_RESULT([$CRYPTO_VERSION])

   # # check -R, "-Wl,-R" or -rpath
   AX_ISC_RPATH

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
   AC_CHECK_HEADERS([botan/build.h],,[
        CRYPTO_INCLUDES=""
        CRYPTO_LIBS=""
        CRYPTO_LDFLAGS=""
        CRYPTO_RPATH=""
        if test "x$ac_header_preproc" = "xyes"; then
                AC_MSG_RESULT([botan/build.h
was found but is unusable. The most common cause of this problem
is attempting to use an updated C++ compiler with older C++ libraries, such as
the version of Botan that comes with your distribution. If you have updated
your C++ compiler we highly recommend that you use support libraries such as
Boost and Botan that were compiled with the same compiler version.])
        else
                AC_MSG_RESULT([Missing required libcrypto header files])
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
        [AC_LANG_PROGRAM([#include <botan/hash.h>],
                         [using namespace Botan;
                          auto h = HashFunction::create("MD5");
                         ])],
        [AC_MSG_RESULT([checking for Botan library... yes])],
        [AC_MSG_RESULT([checking for Botan library... no])
         CRYPTO_INCLUDES=""
         CRYPTO_LIBS=""
         CRYPTO_LDFLAGS=""
         CRYPTO_RPATH=""
         AC_MSG_RESULT([Needs Botan library 2.0 or higher. On some systems,
         the botan package has a few missing dependencies (libbz2 and
         libgmp), if libbotan has been installed and you see this message,
         try upgrading to a higher version of botan or installing libbz2
         and libgmp.])]
   )
   CPPFLAGS=$CPPFLAGS_SAVED
   LIBS=$LIBS_SAVED
   CRYPTO_NAME="Botan"
   CRYPTO_PACKAGE="botan-2"
fi

if test "x${CRYPTO_LIBS}" != "x"
then
   DISABLED_CRYPTO="OpenSSL"
   CRYPTO_CFLAGS=""
   DISTCHECK_CRYPTO_CONFIGURE_FLAG="$distcheck_botan"
   AC_DEFINE_UNQUOTED([WITH_BOTAN], [], [Compile with Botan crypto])
else
   CRYPTO_NAME="OpenSSL"
   DISABLED_CRYPTO="Botan"
   CRYPTO_PACKAGE="openssl-1.1.0"
   DISTCHECK_CRYPTO_CONFIGURE_FLAG="--with-openssl=${use_openssl}"
   AC_DEFINE_UNQUOTED([WITH_OPENSSL], [], [Compile with OpenSSL crypto])
   AC_MSG_CHECKING(for OpenSSL library)
   openssl_headers=
   openssl_libraries=

   case "${use_openssl}" in
      auto)
         use_openssl="yes"
         ;;
      yes)
         ;;
      *)
         # no was already handled
         openssl_headers="${use_openssl}/include"
         openssl_libraries="${use_openssl}/lib"
         ;;
   esac

   # Now search for the system OpenSSL library.
   if test "${use_openssl}" = "yes" ; then
      for d in /usr /usr/local /usr/local/ssl /usr/local/opt/openssl /usr/pkg /usr/sfw; do
         if test -f $d/include/openssl/opensslv.h; then
            use_openssl="${d}"
            openssl_headers="${d}/include"
            for l in lib lib64; do
               if test -f "${d}/${l}/libssl.so"; then
                  openssl_libraries="${d}/${l}"
                  break
               fi
            done
            if test -n "${openssl_headers}" && test -n "${openssl_libraries}"; then
               break
            fi
         fi
      done
   fi

   if test "${use_openssl}" = "yes" ; then
      AC_MSG_ERROR([OpenSSL auto detection failed])
   fi
   AC_MSG_RESULT(yes)

   if test "${openssl_headers}" = "/usr/include" ; then
      CRYPTO_CFLAGS=""
      CRYPTO_INCLUDES=""
      CRYPTO_LIBS="-lssl -lcrypto"
   else
      CRYPTO_CFLAGS=""
      CRYPTO_INCLUDES="-I${openssl_headers}"
      case $host in
          *-solaris*)
              CRYPTO_LIBS="-L${openssl_libraries} -R${openssl_libraries} -lssl -lcrypto"
              ;;
          *-hp-hpux*)
              CRYPTO_LIBS="-L${openssl_libraries} -Wl,+b: -lssl -lcrypto"
              ;;
          *-apple-darwin*)
              if test -f "${openssl_libraries}/libcrypto.dylib" ; then
                 CRYPTO_LIBS="-L${openssl_libraries} -lssl -lcrypto"
              else
                 CRYPTO_LIBS="${openssl_libraries}/libssl.a ${openssl_libraries}/libcrypto.a"
              fi
              ;;
          *)
              CRYPTO_LIBS="-L${openssl_libraries} -lssl -lcrypto"
              ;;
      esac
    fi
    dnl Determine the OpenSSL version
    # Officially we support >= 1.0.1, 0.9.8 should fail the HMAC API,
    # 1.0.0 could work but is not recommended.
    AC_MSG_CHECKING([OpenSSL version])
    cat > conftest.cpp << EOF
#include <openssl/opensslv.h>
AUTOCONF_OPENSSL_VERSION=OPENSSL_VERSION_TEXT
EOF

    CRYPTO_VERSION=`$CPPP $CPPFLAGS $CRYPTO_INCLUDES conftest.cpp | grep '^AUTOCONF_OPENSSL_VERSION=' | $SED -e 's/^AUTOCONF_OPENSSL_VERSION=//' -e 's/"//g' 2> /dev/null`
    if test -z "$CRYPTO_VERSION" ; then
       CRYPTO_VERSION="unknown"
    fi
    $RM -f conftest.cpp
    AC_MSG_RESULT([$CRYPTO_VERSION])
    #CRYPTO_LDFLAGS="-ldl"
    CRYPTO_LDFLAGS=""
    CRYPTO_RPATH=""
    AC_MSG_CHECKING([support of SHA-2])
    LIBS_SAVED=${LIBS}
    LIBS="$LIBS $CRYPTO_LIBS"
    CPPFLAGS_SAVED=${CPPFLAGS}
    CPPFLAGS="$CRYPTO_INCLUDES $CPPFLAGS"
    dnl Check availability of legacy hash
    AC_CHECK_FUNC([EVP_md5],,[missing EVP entry for MD5])
    AC_CHECK_FUNC([EVP_sha1],,[missing EVP entry for SHA1])
    dnl Check availability of SHA-2
    AC_CHECK_FUNC([EVP_sha224],,[missing EVP entry for SHA224])
    AC_CHECK_FUNC([EVP_sha256],,[missing EVP entry for SHA256])
    AC_CHECK_FUNC([EVP_sha384],,[missing EVP entry for SHA384])
    AC_CHECK_FUNC([EVP_sha512],,[missing EVP entry for SHA512])
    dnl Two generations of EVP_MD_CTX functions
    AC_CHECK_FUNCS([EVP_MD_CTX_new EVP_MD_CTX_free],,
        [AC_CHECK_FUNCS([EVP_MD_CTX_create EVP_MD_CTX_destroy],,
        [AC_MSG_ERROR([missing EVP MD CTX functions])])])
    dnl Same for EVP and HMAC
    AC_CHECK_FUNCS([EVP_PKEY_new_raw_private_key],,
        [AC_CHECK_FUNCS([EVP_PKEY_new_mac_key],,
        [AC_MSG_ERROR([missing EVP PKEY new key function])])])
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
]
)
# End of AX_CRYPTO

# Test TLS support using both crypto and boost.
AC_DEFUN([AX_TLS], [
if test "x${CRYPTO_NAME}" = "xBotan"
then
    dnl Check Botan boost ASIO TLS
    CPPFLAGS_SAVED=$CPPFLAGS
    CPPFLAGS="$CRYPTO_INCLUDES $CPPFLAGS $BOOST_INCLUDES"
    AC_CHECK_HEADERS([botan/asio_stream.h],
        [AC_MSG_CHECKING([Botan boost TLS support])
         AC_COMPILE_IFELSE(
             [AC_LANG_PROGRAM([#include <botan/asio_stream.h>],
                              [#ifndef BOTAN_TLS_SERVER_H_
                               #error botan/tls_server.h is not included by botan/asio_stream.h
                               #endif])],
              [AC_MSG_RESULT(yes)],
              [AC_MSG_RESULT(no)
               AC_MSG_ERROR([Botan is configured with boost support but is too old: only Botan >= 2.14.0 can be used for TLS support.])])],
        [AC_MSG_ERROR([Botan cannot be used for TLS support, because it was installed without boost support, so required headers are missing.])])
    CPPFLAGS=${CPPFLAGS_SAVED}
fi
if test "x${CRYPTO_NAME}" = "xOpenSSL"
then
    CPPFLAGS_SAVED=$CPPFLAGS
    CPPFLAGS="$CRYPTO_INCLUDES $CPPFLAGS $BOOST_INCLUDES"
    dnl Check boost ASIO SSL
    AC_CHECK_HEADERS([boost/asio/ssl.hpp],,
        [AC_MSG_ERROR([Missing required boost ssl header file])])
    dnl Check if the generic TLS method is available
    AC_MSG_CHECKING([Generic TLS method])
    AC_COMPILE_IFELSE(
        [AC_LANG_PROGRAM([#include <boost/asio/ssl.hpp>],
                         [auto ctx(boost::asio::ssl::context::tls);])],
        [AC_MSG_RESULT(yes)],
        [AC_MSG_RESULT(no)
         AC_MSG_ERROR([Boost version >= 1.66 is required])])
    dnl Check if the stream_truncated (SSL short read) error is available
    AC_MSG_CHECKING([stream_truncated (SSL short read) error])
    AC_COMPILE_IFELSE(
        [AC_LANG_PROGRAM([#include <boost/asio/ssl.hpp>],
                         [const int ec =
                          boost::asio::ssl::error::stream_truncated;])],
        [AC_MSG_RESULT(yes)],
        [AC_MSG_RESULT(no)
         AC_MSG_ERROR([Boost version >= 1.66 is required])])
    CPPFLAGS=${CPPFLAGS_SAVED}
fi
])
# End of AX_TLS
