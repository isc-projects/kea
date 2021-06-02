AC_DEFUN([AX_FIND_LIBRARY], [
  library="${1}"

  AC_ARG_WITH([${library}],
    AS_HELP_STRING([--with-${library}=PATH], [path to the ${library}.pc file or to the ${library} installation directory]),
    [with_library="$withval"])

  library_found=false
  if test -n "${with_library}"; then
    if test -f "${with_library}"; then

      # User has pointed --with-${library} to a file. Let's try parse it with pkg-config.
      if test -n "${PKG_CONFIG}"; then
        if "${PKG_CONFIG}" "${with_library}"; then
          LIBRARY_CPPFLAGS=$("${PKG_CONFIG}" --cflags-only-other "${with_library}")
          LIBRARY_INCLUDEDIR=$("${PKG_CONFIG}" --cflags-only-I "${with_library}")
          LIBRARY_LIBS=$("${PKG_CONFIG}" --libs "${with_library}")
          LIBRARY_REPO=$("${PKG_CONFIG}" --variable=SR_REPO_PATH "${with_library}")
          # LIBRARY_INCLUDEDIR="${LIBRARY_INCLUDEDIR} -I${LIBRARY_CONFIG}/include"
          # LIBRARY_LIBS="${LIBRARY_LIBS} -Wl,-rpath=${LIBRARY_CONFIG}/lib"
          library_found=true
        else
          AC_MSG_ERROR(["pkg-config ${with_library}" doesn't work properly. It seems like a bad pkg-config file.])
        fi
      else
        AC_MSG_ERROR([--with-${library} seems to point to a pkg-config file, but pkg-config is not available])
      fi
    elif test -d "${with_library}"; then

      # User has pointed --with-${library} to a directory.
      # Let's try to find a ${library}.pc first.
      library_pc="${LIBRARY_CONFIG}/lib/pkgconfig/${library}.pc"
      if test -f "${library_pc}"; then
        if test -n "${PKG_CONFIG}"; then
          if "${PKG_CONFIG}" "${library_pc}"; then
            LIBRARY_CPPFLAGS=$("${PKG_CONFIG}" --cflags-only-other "${with_library}")
            LIBRARY_INCLUDEDIR=$("${PKG_CONFIG}" --cflags-only-I "${with_library}")
            LIBRARY_LIBS=$("${PKG_CONFIG}" --libs "${with_library}")
            LIBRARY_REPO=$(cat "${with_library}/lib/pkgconfig/${library}.pc" | grep -F 'SR_REPO_PATH=' | cut -d '=' -f 2)
            LIBRARY_VERSION=$("${PKG_CONFIG}" --modversion "${with_library}")
            # LIBRARY_INCLUDEDIR="${LIBRARY_INCLUDEDIR} -I${LIBRARY_CONFIG}/include"
            # LIBRARY_LIBS="${LIBRARY_LIBS} -Wl,-rpath=${LIBRARY_CONFIG}/lib"
            library_found=true
          else
            AC_MSG_WARN(["pkg-config ${library_pc}" doesn't work properly. It seems like a bad pkg-config file.])
          fi
        else
          AC_MSG_WARN([pkg-config file found at ${library_pc}, but pkg-config is not available])
        fi
      else
          AC_MSG_WARN([pkg-config file not found at ${library_pc}])
      fi
    else
      AC_MSG_ERROR([--with-${library} doesn't point to the sysrepo.pc file or to the sysrepo installation directory])
    fi
  else

    # No parameter given. Try pkg-config first.
    for i in /usr usr/local; do
      if test -n "${PKG_CONFIG}"; then
        if test -f "${i}/include/sysrepo.h" && test -f "${i}/lib/libsysrepo.so"; then
          LIBRARY_CPPFLAGS=
          LIBRARY_INCLUDEDIR="-I${i}/include"
          LIBRARY_LIBS="-L${i}/lib -lsysrepo -lsysrepo-cpp"
          LIBRARY_REPO=$(cat "${i}/lib/pkgconfig/sysrepo.pc" | grep -F 'SR_REPO_PATH=' | cut -d '=' -f 2)
          LIBRARY_VERSION=$(cat "${i}/include/sysrepo/version.h" | grep -F '#define SR_VERSION ' | cut -d '"' -f 2)
          library_found=true
          break
        fi
      fi
    done

    # If not found, then search in usual paths for header and libraries.
    if ! "${library_found}"; then
      for i in /usr usr/local; do
        if test -f "${i}/include/sysrepo.h" && test -f "${i}/lib/libsysrepo.so"; then
          LIBRARY_CPPFLAGS=
          LIBRARY_INCLUDEDIR="-I${i}/include"
          LIBRARY_LIBS=$(-L"${i}/lib" -lsysrepo -lsysrepo-cpp)
          LIBRARY_REPO=$(cat "${i}/lib/pkgconfig/sysrepo.pc" | grep -F 'SR_REPO_PATH=' | cut -d '=' -f 2)
          LIBRARY_VERSION=$(cat "${i}/include/sysrepo/version.h" | grep -F '#define SR_VERSION ' | cut -d '"' -f 2)
          library_found=true
          break
        else
          AC_MSG_WARN([sysrepo not found in ${i}])
        fi
      done
    fi
  fi

  dnl TODO:
    dnl Now get the environment for C++ bindings for Sysrepo.
    dnl SYSREPOCPP_INCLUDEDIR=$("${LIBRARY_CONFIG}" --cflags-only-I libsysrepo-cpp)
    dnl SYSREPOCPP_CPPFLAGS="${LIBRARY_INCLUDEDIR} $("${LIBRARY_CONFIG}" --cflags-only-other libsysrepo-cpp)"
    dnl SYSREPOCPP_LIBS=$("${LIBRARY_CONFIG}" --libs libsysrepo-cpp)
    dnl SYSREPOCPP_VERSION=$("${LIBRARY_CONFIG}" --modversion libsysrepo-cpp)

    dnl If include paths are equal, there's no need to include both. But if they're different,
    dnl we need both.
    dnl if test "${LIBRARY_INCLUDEDIR}" != "${SYSREPOCPP_INCLUDEDIR}"; then
    dnl    LIBRARY_INCLUDEDIR="${LIBRARY_INCLUDEDIR} ${SYSREPOCPP_INCLUDEDIR}"
    dnl fi

    dnl if test "${LIBRARY_CPPFLAGS}" != "${SYSREPOCPP_CPPFLAGS}"; then
    dnl    LIBRARY_CPPFLAGS="${LIBRARY_CPPFLAGS} ${SYSREPOCPP_CPPFLAGS}"
    dnl fi

    dnl if test "${LIBRARY_LIBS}" != "${SYSREPOCPP_LIBS}"; then
    dnl    LIBRARY_LIBS="${LIBRARY_LIBS} ${SYSREPOCPP_LIBS}"
    dnl fi
])
