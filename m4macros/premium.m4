# Premium configuration
PREMIUM_DIR=premium

# This lists all possible hooks that are currently supported.
PREMIUM_HOOKS="forensic_log flex_id host_cmds subnet_cmds high_availability radius host_cache"

# This lists the hooks that are actually detected.
INCLUDED_PACKAGES=

AC_DEFUN([AX_PREMIUM], [

for h in ${PREMIUM_HOOKS}; do
    AC_MSG_CHECKING(for premium hook $h availability...)
    if test -f premium/$h.m4; then
       INCLUDED_HOOKS="${INCLUDED_HOOKS} $h"
       INCLUDED_PACKAGES="${INCLUDED_PACKAGES} $h"
       export "HOOK_${h}=yes"
       AC_MSG_RESULT(found)
    else
       export "HOOK_${h}=no"
       AC_MSG_RESULT(no)
    fi
done


AM_CONDITIONAL(PREMIUM, test -d "$srcdir/premium/src")
  AC_MSG_CHECKING([if premium package is available])

  if test -d "$srcdir/premium/src"; then
    # Define it in the config.h, so C++ code could use it.
    AC_DEFINE([PREMIUM], [1], [Kea-premium hooks found])

    # Export it here, so code in configure could use it.
    PREMIUM=1
    AC_MSG_RESULT(yes)

    # read settings (it's possible to include config.setup file in premium repo
    # with some extra settings)
    if test -f "$srcdir/premium/config.setup"; then
        . "$srcdir/premium/config.setup"
    fi

    # Check availability of FreeRADIUS client
    AC_MSG_CHECKING(FreeRADIUS client)
    freeradius_dir=no
    FREERADIUS_INCLUDE=
    FREERADIUS_LIB=
    AC_ARG_WITH([freeradius],
                [AC_HELP_STRING([--with-freeradius=PATH],
                                [Enables FreeRADIUS client, location is required])],
                [freeradius_dir="$withval"])
    if test "x${freeradius_dir}" = "xyes"; then
        AC_MSG_ERROR([need FreeRADIUS client path])
    elif test "x${freeradius_dir}" = "xno"; then
        AC_MSG_RESULT([no])
        freeradius_dir=""
    else
        AC_MSG_RESULT([yes])
    fi

    if test "x${freeradius_dir}" != "x"; then
        AC_MSG_CHECKING([looking for FreeRADIUS client include])
        if test -f ${freeradius_dir}/include/freeradius-client.h; then
            AC_MSG_RESULT([found])
        else
            AC_MSG_ERROR([no ${freeradius_dir}/include/freeradius-client.h file])
        fi
        FREERADIUS_INCLUDE="-I${freeradius_dir}/include"

        AC_MSG_CHECKING([looking for FreeRADIUS client library])
        freeradius_libdir="${freeradius_dir}/lib"
        if test -f ${freeradius_libdir}/libfreeradius-client.la -o \
                -f ${freeradius_libdir}/libfreeradius-client.a; then
            AC_MSG_RESULT([found])
        else
            AC_MSG_ERROR([no ${freeradius_libdir}/libfreeradius-client.[l]a file])
        fi
        FREERADIUS_LIB="-L${freeradius_libdir} -lfreeradius-client"

        CPPFLAGS_SAVED="$CPPFLAGS"
        CPPFLAGS="$CPPFLAGS $FREERADIUS_INCLUDE"
        
        AC_MSG_CHECKING([looking for async support])
        AC_CHECK_DECL([READBLOCK_RC],
                      [AC_DEFINE([ASYNC_RADIUS], [1],
                       [Define to 1 if async support is available])],
                      [],
                      [[#include <freeradius-client.h>]])

        AC_MSG_CHECKING([looking for Framed-Pool])
        # Assume that if it is in the header it is in the dictionary.
        AC_CHECK_DECL([PW_FRAMED_POOL],
                      [],
                      [AC_MSG_ERROR([Framed-Pool is unknown: please use a more recent FreeRADIUS client version])],
                      [[#include <freeradius-client.h>]])

        CPPFLAGS="$CPPFLAGS_SAVED"

        # Check availability of FreeRADIUS dictionary
        AC_MSG_CHECKING(FreeRADIUS dictionary)
        FREERADIUS_DICTIONARY=
        freeradius_dict_dir=
        freeradius_dict=
        if test "x${freeradius_dir}" != "x" -a \
            -f ${freeradius_dir}/etc/radiusclient/dictionary; then
            freeradius_dict_dir="${freeradius_dir}/etc/radiusclient"
        fi
        AC_ARG_WITH([freeradius-dictionary],
                    [AC_HELP_STRING([--with-freeradius-dictionary[=PATH]],
                                    [FreeRADIUS dictionary location])],
                    [freeradius_dict="$withval"],
                    [freeradius_dict="yes"])
        if test "x${freeradius_dict}" = "xyes"; then
            if test "x${freeradius_dict_dir}" = "x"; then
                AC_MSG_ERROR([need FreeRADIUS dictionary path])
            fi
            freeradius_dict="${freeradius_dict_dir}/dictionary"
            AC_MSG_RESULT([found at default])
        elif test "x${freeradius_dict}" = "xno"; then
            AC_MSG_RESULT([no])
            freeradius_dict=""
        elif test "x${include_tier2}" != "xyes"; then
            AC_MSG_RESULT([no (radius lib not found)])
            freeradius_dict=""
        elif test -f ${freeradius_dict}; then
            AC_MSG_RESULT([found])
        else
            AC_MSG_ERROR([no ${freeradius_dict} file])
        fi        
        FREERADIUS_DICTIONARY="${freeradius_dict}"
    fi
    AM_CONDITIONAL([HAVE_FREERADIUS], [test x$freeradius_dir != "x"])
    AC_SUBST(FREERADIUS_INCLUDE)
    AC_SUBST(FREERADIUS_LIB)
    AC_SUBST(FREERADIUS_DICTIONARY)

    #DISTCHECK_PREMIUM_CONFIGURE_FLAG="--with-tier1=${include_tier1} --with-tier2=${include_tier2}"

    if test "x${freeradius_dir}" != "x"; then
        DISTCHECK_PREMIUM_CONFIGURE_FLAG="$DISTCHECK_PREMIUM_CONFIGURE_FLAG --with-freeradius=${freeradius_dir}"
    fi

#    AC_SUBST(TIER1_PACKAGES)
#    AC_SUBST(TIER2_PACKAGES)
    AC_SUBST(INCLUDED_PACKAGES)
    AC_SUBST(SHARE_DIR)

    AC_CONFIG_FILES([premium/Makefile
                     premium/src/Makefile
                     premium/src/hooks/Makefile
                     premium/src/hooks/dhcp/Makefile])

    # Ok, now include makefiles specific to the hooks that we detected.
    # @todo: How to make this in a loop? We have all the libraries defined in
    # INCLUDED_PACKAGES
    if test "x${HOOK_forensic_log}" = "xyes"; then
        m4_sinclude(premium/forensic_log.m4)
	true
    fi

    if test "x${HOOK_flex_id}" = "xyes"; then
        m4_sinclude(premium/flex_id.m4)
	true
    fi

    if test "x${HOOK_host_cmds}" = "xyes"; then
        m4_sinclude(premium/host_cmds.m4)
	true
    fi

    if test "x${HOOK_subnet_cmds}" = "xyes"; then
        m4_sinclude(premium/subnet_cmds.m4)
	true
    fi

    if test "x${HOOK_high_availability}" = "xyes"; then
        m4_sinclude(premium/high_availability.m4)
	true
    fi

    if test "x${HOOK_radius}" = "xyes"; then
        m4_sinclude(premium/radius.m4)
	true
    fi

    if test "x${HOOK_host_cache}" = "xyes"; then
        m4_sinclude(premium/host_cache.m4)
	true
    fi

  else
     AC_MSG_RESULT(no)
  fi
])
