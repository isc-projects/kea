AC_DEFUN([AX_GSS_API], [

gssapi_path=""

AC_ARG_WITH([gssapi],
            [AS_HELP_STRING([--with-gssapi[[=PATH]]],
                            [optionally specify the path to a krb5-config file])],
        [gssapi_path="$withval"; enable_gssapi="yes"])

#
# Check availability of gssapi, which will be used for unit tests.
#
ENABLE_GSSAPI=no
GSSAPI_CFLAGS=
GSSAPI_LIBS=
DISTCHECK_GSSAPI_CONFIGURE_FLAG="--with-gssapi=$gssapi_path"

AC_MSG_CHECKING([for gssapi support])
if test "x$gssapi_path" = "x" ; then
    AC_MSG_RESULT([no])
else
    AC_MSG_RESULT([yes])
    if test "$gssapi_path" = "yes"; then
        AC_PATH_PROG([KRB5_CONFIG], [krb5-config])
    else
        KRB5_CONFIG="$gssapi_path"
    fi
    if test -x "${KRB5_CONFIG}" ; then
        GSSAPI_CFLAGS=`${KRB5_CONFIG} --cflags gssapi`
        GSSAPI_LIBS=`${KRB5_CONFIG} --libs gssapi`
    else
        AC_MSG_ERROR([Unable to locate krb5-config.])
    fi
    CXXFLAGS_SAVED="$CXXFLAGS"
    CXXFLAGS="$CXXFLAGS $GSSAPI_CFLAGS"

    # In general it is not required but some warnings about compiling to
    # work but not the preprocessor were reported...
    CPPFLAGS_SAVED="$CPPFLAGS"
    CPPFLAGS="$CPPFLAGS $GSSAPI_CFLAGS"

    # Checks
    AC_CHECK_HEADERS([gssapi/gssapi.h gssapi/gssapi_krb5.h],,
        AC_MSG_ERROR([Missing required gss-api header files]))

    AC_CHECK_HEADERS([krb5/krb5.h],,
        [AC_CHECK_HEADERS([krb5.h],,
         AC_MSG_ERROR([Missing required krb5 header files]))])

    # Verify that GSS-API with Kerberos 5 is usable.
    LIBS_SAVED="$LIBS"
    LIBS="$LIBS $GSSAPI_LIBS"
    if test $enable_static_link = yes; then
       LIBS="-static $LIBS"
    fi
    AC_MSG_CHECKING([checking for GSS-API with Kerberos 5 libraries])
    AC_LINK_IFELSE(
       [AC_LANG_PROGRAM(
           [[#include <gssapi/gssapi_krb5.h>]],
           [[gss_ctx_id_t ctx;
             OM_uint32 minor;
             OM_uint32 major;
             major = gss_delete_sec_context(&minor, &ctx, GSS_C_NO_BUFFER);]])],
       [AC_MSG_RESULT([yes])],
       [AC_MSG_RESULT([no])
        AC_MSG_ERROR([failed to link with GSS-API with Kerberos 5 libraries])])
    AC_MSG_CHECKING([checking for gss_str_to_oid availability])
    AC_COMPILE_IFELSE(
       [AC_LANG_PROGRAM(
           [[#include <gssapi/gssapi.h>]],
           [[return (gss_str_to_oid(0, 0, 0));]])],
       [AC_MSG_RESULT([yes])
        AC_DEFINE([HAVE_GSS_STR_TO_OID], [1], [gss_str_to_oid is available])],
       [AC_MSG_RESULT([no])])
    CXXFLAGS="$CXXFLAGS_SAVED"
    CPPFLAGS="$CPPFLAGS_SAVED"
    LIBS="$LIBS_SAVED"
    AC_MSG_CHECKING([checking for MIT implementation vs Heimdal])
    if `${KRB5_CONFIG} --all | grep Vendor | grep -q Heimdal`; then
        AC_MSG_RESULT([Heimdal])
        AC_DEFINE([WITH_HEIMDAL], [1], [Heimdal GSS-API implementation])
    else
        AC_MSG_RESULT([MIT])
    fi
    ENABLE_GSSAPI=yes
fi

AC_SUBST(GSSAPI_CFLAGS)
AC_SUBST(GSSAPI_LIBS)
AC_SUBST(DISTCHECK_GSSAPI_CONFIGURE_FLAG)
AM_CONDITIONAL([HAVE_GSSAPI], [test $ENABLE_GSSAPI = "yes"])

])dnl AX_GSS_API
