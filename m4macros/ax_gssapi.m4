AC_DEFUN([AX_GSS_API], [

gssapi_path=""

AC_ARG_WITH([gssapi],
            [AS_HELP_STRING([--with-gssapi=PATH],
                            [specify a path to krb5-config file])],
        [gssapi_path="$withval"; enable_gssapi="yes"])

#
# Check availability of gssapi, which will be used for unit tests.
#
GSSAPI_CFLAGS=
GSSAPI_LIBS=

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

    # Checks
    AC_CHECK_HEADERS([gssapi/gssapi.h gssapi/gssapi_krb5.h krb5/krb5.h],,
        AC_MSG_ERROR([Missing required gss-api or krb5 header files]))

    # Verify that GSS-API with Kerberos 5 is usable.
    CXXFLAGS_SAVED="$CXXFLAGS"
    LIBS_SAVED="$LIBS"
    CXXFLAGS="$CXXFLAGS $GSSAPI_CFLAGS"
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
        AC_MSG_ERROR([failed to link with  GSS-API with Kerberos 5 libraries])])
    AC_MSG_CHECKING([checking for MIT implementation vs Heimdal])
    AC_COMPILE_IFELSE(
       [AC_LANG_PROGRAM(
           [[#include <gssapi/gssapi_krb5.h>]],
           [[return (krb5_cccol_last_change_time(0, 0, 0));]])],
       [AC_MSG_RESULT([Heimdal])
        AC_MSG_WARN([Heimdal is not supported, please switch to the MIT implementation])],
       [AC_MSG_RESULT([MIT])])
    CXXFLAGS="$CXXFLAGS_SAVED"
    LIBS="$LIBS_SAVED"
fi

AC_SUBST(GSSAPI_CFLAGS)
AC_SUBST(GSSAPI_LIBS)

])dnl AX_GSS_API
