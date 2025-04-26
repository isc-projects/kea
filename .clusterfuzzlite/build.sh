#!/bin/bash

# SC2156 (warning): Injecting filenames is fragile and insecure. Use parameters.
# shellcheck disable=SC2156

set -eu

script_path="$(dirname "$(readlink -f "${0}")")"
cd "${script_path}/.."

# Use a wrapper function to allow "return 1" instead of "exit 1" which may have
# unforeseen consequences in case this script is sourced.
install_kea() {
  # ccache
  export CCACHE_DIR=/cache
  export PATH="/usr/lib/ccache:$PATH"
  export KEA_BUILD_DIR="${KEA_BUILD_DIR-/builds/isc-projects/kea}"

  cxxflags='-gdwarf-4'
  export CXX='g++'
  export CXXFLAGS="${cxxflags}"
  export LDFLAGS="${cxxflags}"
  if ! meson setup build --prefix "${OUT}" -D b_lundef=false -D "b_sanitize=${SANITIZER}" -D fuzz=enabled -D tests=enabled; then
    printf 'meson setup failed. Here is meson-log.txt:\n'
    cat build/meson-logs/meson-log.txt
    return 1
  fi
  meson compile -C build
  meson install -C build

  echo "${OUT}/lib" | sudo tee /etc/ld.so.conf.d/kea.conf
  echo "${OUT}/lib/x86_64-linux-gnu" | sudo tee /etc/ld.so.conf.d/kea.conf
  ldconfig
  sudo ldconfig

  # Copy internal libraries.
  find "${OUT}/lib/" -name 'libkea-*.so*'
  find "${OUT}/lib/" -name 'libkea-*.so*' -exec sh -c "cp {} ${KEA_BUILD_DIR}" ';'
  find "${OUT}/lib/" -name 'libkea-*.so*' -exec sh -c "cp {} ${OUT}" ';'
  find "${OUT}/lib/" -name 'libkea-*.so*' -exec sh -c "cp {} /lib/x86_64-linux-gnu/" ';'

  # Copy the binaries.
  for fuzzer in fuzz_config_kea_dhcp4 fuzz_http_endpoint_kea_dhcp4 fuzz_packets_kea_dhcp4 fuzz_unix_socket_kea_dhcp4 \
                fuzz_config_kea_dhcp6 fuzz_http_endpoint_kea_dhcp6 fuzz_packets_kea_dhcp6 fuzz_unix_socket_kea_dhcp6 \
      ; do
    cp "${OUT}/sbin/${fuzzer}" "${OUT}/${fuzzer}"

    # Display some information for debugging.
    ldd "${OUT}/${fuzzer}"
    readelf -d "${OUT}/${fuzzer}" | grep -Ei 'R.*PATH' || true

    # Copy all required libraries, although we want to specifically target external libraries.
    for i in $(ldd "${OUT}/${fuzzer}" | cut -f 2 | cut -d ' ' -f 3); do
      cp "${i}" "${KEA_BUILD_DIR}"
      cp "${i}" "${OUT}"
    done
  done
}

install_kea
