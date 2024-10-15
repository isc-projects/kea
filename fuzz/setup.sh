#!/bin/sh

# Copyright (C) 2024 Internet Systems Consortium, Inc. ("ISC")
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.

# shellcheck disable=all

# Disable this script altogether for now.
exit 0

# Disable this script if the interface and address are used from environment variables.
if test -n "${KEA_DHCP4_FUZZING_INTERFACE+x}" ||
   test -n "${KEA_DHCP4_FUZZING_ADDRESS+x}" ||
   test -n "${KEA_DHCP6_FUZZING_INTERFACE+x}" ||
   test -n "${KEA_DHCP6_FUZZING_ADDRESS+x}"; then
  printf 'Environment variables set. Will use those. Abandoning.\n'
  exit 0
fi

script_path=$(cd "$(dirname "${0}")" && pwd)

cd "${script_path}" > /dev/null

# Add sudo to the fuzzers.
sudo='if ! sudo -n true; then exec sudo -- "${0}" "${@}"; fi'
for i in fuzz-*-kea-dhcp[46]; do
  continue  # Disable this loop for now.
  if ! grep -F "${sudo}" "${i}" > /dev/null; then
    sed -i "2i${sudo}" "${i}"
  fi
done

# Create kea-dhcp{v}-fuzz-* wrapper scripts which adds the afl-fuzz command prefix to kea-dhcp{v}.
for v in 4 6; do
  continue  # Disable this loop for now.
  executable="../src/bin/dhcp${v}/kea-dhcp${v}"

  for f in config packets unix-socket; do
    fuzzed_executable="${executable}-fuzz-${f}"
    cp "${executable}" "${fuzzed_executable}"
    mkdir -p "output/config/kea-dhcp${v}"
    sed -i "s# *exec \"\$progdir/\$program\"#\n\
      export AFL_DEBUG='1'\n\
      export AFL_DEBUG_CHILD='1'\n\
      export AFL_LLVM_MAP_ADDR='true'\n\
      export AFL_MAP_SIZE='10000000'\n\
      export KEA_AFL_ADDRESS='10.1.0.1'\n\
      export KEA_AFL_INTERFACE='vethclient'\n\
      export KEA_AFL_LOOP_MAX=2\n\
      exec afl-fuzz -M fuzzer1 -t 20000+ -m 50000 -i 'seeds/${f}' -o 'output/config/kea-dhcp${v}' -x /opt/dict.dat -- \"\$progdir/\$program\"\
    #g" "${fuzzed_executable}"
    sed -i "2i${sudo}" "${fuzzed_executable}"
  done
done

cd - > /dev/null

# Run again as root.
if ! sudo -n true; then
  exec sudo -- "${0}" "${@}"
fi

# afl-fuzz says:
# To avoid having crashes misinterpreted as timeouts, please log in as root
# and temporarily modify /proc/sys/kernel/core_pattern, like so:
echo core > /proc/sys/kernel/core_pattern

# afl-fuzz says:
# Whoops, your system uses on-demand CPU frequency scaling, adjusted
# between 781 and 4882 MHz. Unfortunately, the scaling algorithm in the
# kernel is imperfect and can miss the short-lived processes spawned by
# afl-fuzz. To keep things moving, run these commands as root:
echo performance | tee /sys/devices/system/cpu/cpu*/cpufreq/scaling_governor > /dev/null

ulimit -Sd 41932800

ulimit -c unlimited

# Create a virtual interface for the server to start listening on.
if ip link show vethclient > /dev/null 2>&1; then
  ip link delete vethclient
fi
if ip link show vethserver > /dev/null 2>&1; then
  ip link delete vethserver
fi
ip link add vethclient type veth peer name vethserver
ip -4 addr add 10.1.0.1/24 dev vethclient
ip -6 addr add 2001:db8:1::1/64 dev vethclient
ip link set dev vethclient up
ip link set lo up
ip -4 addr add 10.1.0.2/24 dev vethserver
ip -6 addr add 2001:db8:1::2/64 dev vethserver
ip link set dev vethserver up
ip link set lo up

# Wait for duplicate address detection to be finished so that the
# interfaces are ready.
while true; do
  interface_status=$(
    ip a s vethserver | grep -E 'inet6.*tentative'
    ip a s vethclient | grep -E 'inet6.*tentative'
  )
  if test -n "${interface_status}"; then
    printf 'Waiting for the following addresses to be assigned to their interfaces:\n%s\n' "${interface_status}"
    sleep 1
  else
    break
  fi
done
