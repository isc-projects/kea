######################### public functions ##########################

# input:
#   * value of --with-library
#   * list of headers to check
#   * list of libraries to check
#   * list of variables to retrieve with pkg-config
#   * additional parameters to pass to pkg-config, useful e.g. when --with-path
#       is needed to point to a dependency of the checked library
# output:
#   * LIBRARY_FOUND
#   * LIBRARY_CPPFLAGS
#   * LIBRARY_INCLUDEDIR
#   * LIBRARY_LIBS
#   * LIBRARY_PREFIX
AC_DEFUN([AX_FIND_LIBRARY], [
  library=$1
  with_library=$2
  list_of_headers=$3
  list_of_libraries=$4
  list_of_variables=$5
  pkg_config_paths=$6

  LIBRARY_FOUND=false
  if test -z "${with_library}"; then
    # library not requested, nothing to do
    :
  elif test "${with_library}" = 'no'; then
    # library specifically disabled, nothing to do
    :
  elif test "${with_library}" != 'yes'; then
    # library enabled and has custom --with parameter

    if test -f "${with_library}"; then
      # User has pointed --with-library to a file.
      # It might be a .pc file.
      AX_FIND_LIBRARY_WITH_PKG_CONFIG(["${with_library}"], ["${list_of_variables}"], ["${pkg_config_paths}"])

    elif test -d "${with_library}"; then
      # User has pointed --with-library to a directory.
      # Let's try to find a library.pc first inside that directory.
      library_pc="${with_library}/lib/pkgconfig/${library}.pc"

      if test -f "${library_pc}"; then
        if test -n "${PKG_CONFIG}"; then
          # The check was inadequate. We need to run pkg-config with the actual .pc file and use it. Otherwise
          # pkg-config always returns 1 (invalid usage), regardless if the file exists or not. Let's use a flag
          # that should work everywhere (--modversion asks for package version). We don't care about the version
          # at this stage, just want to make sure the .pc file is not garbage.
          ignore_me=$("${PKG_CONFIG}" --modversion "${library_pc}")
          exit_code=$?
          if test "${exit_code}" -eq 0; then
            AX_FIND_LIBRARY_WITH_PKG_CONFIG("${library_pc}", ["${list_of_variables}"], ["${pkg_config_paths}"])
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
      AC_MSG_ERROR(["${with_library}" needs to point to a .pc file or to the installation directory, but points to none of those])
    fi

  else
    # No parameter given. Try pkg-config first.
    if test -n "${PKG_CONFIG}"; then
      AX_FIND_LIBRARY_WITH_PKG_CONFIG("${library}", ["${list_of_variables}"], ["${pkg_config_paths}"])
    fi

    # If not found, then search in usual paths for a .pc file.
    if ! "${LIBRARY_FOUND}"; then
      for p in /usr /usr/local; do
        library_pc="${p}/lib/pkgconfig/${library}.pc"
        if test -f "${library_pc}"; then
          AX_FIND_LIBRARY_WITH_PKG_CONFIG("${library_pc}", ["${list_of_variables}"], ["${pkg_config_paths}"])
          if "${LIBRARY_FOUND}"; then
            break
          fi
        fi
      done
    fi

    # If not found, then search in usual paths for header and libraries.
    if ! "${LIBRARY_FOUND}"; then
      for p in /usr /usr/local; do
        headers_found=true
        libraries_found=true
        for i in ${list_of_headers}; do
          if test ! -f "${p}/include/${i}"; then
            AC_MSG_WARN(["${library}" headers not found in "${p}"])
            headers_found=false
            break
          fi
        done
        if "${headers_found}"; then
          LIBRARY_CPPFLAGS=
          LIBRARY_INCLUDEDIR="-I${p}/include"
        fi

        LIBRARY_LIBS="-L${p}/lib -Wl,-rpath=${p}/lib"
        for i in ${list_of_libraries}; do
          if test ! -f "${p}/lib/${i}"; then
            AC_MSG_WARN(["${library}" libraries not found in "${p}"])
            libraries_found=false
            break
          fi
          l=$(printf '%s' "${i}" | sed 's/^lib//g;s/.so$//g')
          LIBRARY_LIBS="${LIBRARY_LIBS} -l${l}"
        done

        if "${headers_found}" && "${libraries_found}"; then
          LIBRARY_FOUND=true
          break
        fi

      done
    fi
  fi

  # Remove leading and trailing spaces.
  if "${LIBRARY_FOUND}"; then
    LIBRARY_CPPFLAGS="$(printf '%s' "${LIBRARY_CPPFLAGS}" | sed 's/^ *//g;s/ *$//g')"
    LIBRARY_INCLUDEDIR="$(printf '%s' "${LIBRARY_INCLUDEDIR}" | sed 's/^ *//g;s/ *$//g')"
    LIBRARY_LIBS="$(printf '%s' "${LIBRARY_LIBS}" | sed 's/^ *//g;s/ *$//g')"
  fi
])

######################### private functions #########################

# input:
#   * value of --with-library
#   * list of variables to retrieve with pkg-config
#   * additional paths to pass to pkg-config, for when a .pc file has
#       a dependency
# output:
#   * LIBRARY_FOUND
#   * LIBRARY_CPPFLAGS
#   * LIBRARY_INCLUDEDIR
#   * LIBRARY_LIBS
#   * LIBRARY_PREFIX
AC_DEFUN([AX_FIND_LIBRARY_WITH_PKG_CONFIG], [
  library_pc_or_name=$1
  list_of_variables=$2
  pkg_config_paths=$3

  LIBRARY_FOUND=false
  # Check that we have pkg-config installed on the system.
  if test -n "${PKG_CONFIG}"; then
    # Check that pkg-config is able to interpret the file.
    ignore_me=$("${PKG_CONFIG}" --modversion "${library_pc}")
    exit_code=$?
    if test "${exit_code}" -eq 0; then
      # Save the previous PKG_CONFIG_PATH.
      save_pkg_config_path="${PKG_CONFIG_PATH}"

      # Append the requested paths.
      export PKG_CONFIG_PATH="${PKG_CONFIG_PATH}:${pkg_config_paths}"

      # Get the flags.
      LIBRARY_CPPFLAGS=$("${PKG_CONFIG}" --cflags-only-other "${library_pc_or_name}")
      LIBRARY_INCLUDEDIR=$("${PKG_CONFIG}" --cflags-only-I "${library_pc_or_name}")
      LIBRARY_LIBS=$("${PKG_CONFIG}" --libs "${library_pc_or_name}")
      LIBRARY_VERSION=$("${PKG_CONFIG}" --modversion "${library_pc_or_name}")
      LIBRARY_PREFIX=$("${PKG_CONFIG}" --variable=prefix "${library_pc_or_name}")

      # Get the variables.
      for i in $(printf '%s' "${list_of_variables}" | sed 's/,/ /g'); do
        # The export is not strictly required here, but we need a way to
        # dynamically assign values to "${i}". And export is nicer than eval.
        export "${i}"="$("${PKG_CONFIG}" --variable="${i}" "${library_pc_or_name}")"
      done

      # Restore the previous PKG_CONFIG_PATH.
      PKG_CONFIG_PATH="${save_pkg_config_path}"

      # Mark that we have the required flags for our library.
      LIBRARY_FOUND=true
    fi
  fi
])
