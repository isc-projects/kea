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
fi

AC_SUBST(GSSAPI_CFLAGS)
AC_SUBST(GSSAPI_LIBS)

])dnl AX_GSS_API
