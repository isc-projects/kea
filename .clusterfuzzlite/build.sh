#!/bin/bash -eu

# https://reports.kea.isc.org/new-fuzzer.html

script_path="$(dirname "$(readlink -f "${0}")")"
cd "${script_path}/.."

# Use a wrapper function to allow "return 1" instead of "exit 1" which may have
# unforeseen consequences in case this script is sourced.
install_kea() {
  # ccache
  export CCACHE_DIR=/cache
  export PATH="/usr/lib/ccache:$PATH"
  export KEA_BUILD_DIR="${KEA_BUILD_DIR-/builds/isc-projects/kea}"

  cxxflags=
  autoreconf -i
  if test "${SANITIZER}" = 'none'; then
    cxxflags="${cxxflags} -fno-sanitize=all"
    enable_fuzzing='--enable-fuzzing'
  else
    cxxflags="${cxxflags} -fsanitize=${SANITIZER}"
    enable_fuzzing='--enable-fuzzing=ci'
  fi
  export CXXFLAGS="${cxxflags}"
  export LDFLAGS='-L/usr/lib/gcc/x86_64-linux-gnu/9 -lstdc++fs'
  if ! ./configure --enable-boost-headers-only --prefix='/opt/kea' "${enable_fuzzing}" --with-gtest=/usr/src/googletest/googletest; then
    printf './configure failed. Here is config.log:\n'
    cat config.log
    return 1
  fi
  make -j "$(nproc)"
  make install

  # Copy internal libraries.
  # SC2156 (warning): Injecting filenames is fragile and insecure. Use parameters.
  # shellcheck disable=SC2156
  find "/opt/kea/lib" -mindepth 1 -maxdepth 1 -exec sh -c "cp {} ${KEA_BUILD_DIR}" ';'

  # Copy the binaries.
  for fuzzer in fuzz-config-kea-dhcp4 fuzz-packets-kea-dhcp4 fuzz-unix-socket-kea-dhcp4 \
                fuzz-config-kea-dhcp6 fuzz-packets-kea-dhcp6 fuzz-unix-socket-kea-dhcp6 \
                fuzz-http-endpoint \
      ; do
    cp "/opt/kea/sbin/${fuzzer}" "${OUT}/${fuzzer}"
    # copy all required libraries
    echo "ldd ${OUT}/${fuzzer}: "
    ldd "${OUT}/${fuzzer}"
    EXTENDED_PATH=$(readelf -d "${OUT}/${fuzzer}" | grep 'R.*PATH' | cut -d '[' -f 2 | cut -d ']' -f 1)
    patchelf --set-rpath "/usr/lib/x86_64-linux-gnu:/lib/x86_64-linux-gnu:${EXTENDED_PATH}" "${OUT}/${fuzzer}"
    readelf -d "${OUT}/${fuzzer}" | grep 'R.*PATH' || true
    for i in $(ldd "${OUT}/${fuzzer}" | cut -f 2 | cut -d ' ' -f 3); do
      cp "${i}" "${KEA_BUILD_DIR}"
    done
  done
}

install_kea
