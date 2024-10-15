SUBDIRS = .

if FUZZING

fuzzdir = "${datarootdir}/${PACKAGE_NAME}/fuzz"

nobase_dist_fuzz_DATA  =
nobase_dist_fuzz_DATA += fuzz-config-kea-dhcp4/empty
nobase_dist_fuzz_DATA += fuzz-config-kea-dhcp4/one-byte
nobase_dist_fuzz_DATA += fuzz-config-kea-dhcp6/empty
nobase_dist_fuzz_DATA += fuzz-config-kea-dhcp6/one-byte
nobase_dist_fuzz_DATA += fuzz-http-endpoint/config-get
nobase_dist_fuzz_DATA += fuzz-http-endpoint/config-get-with-service
nobase_dist_fuzz_DATA += fuzz-http-endpoint/empty
nobase_dist_fuzz_DATA += fuzz-http-endpoint/empty-json-map
nobase_dist_fuzz_DATA += fuzz-http-endpoint/one-byte
nobase_dist_fuzz_DATA += fuzz-http-endpoint/one-entry-json-map
nobase_dist_fuzz_DATA += fuzz-packets-kea-dhcp4/dhcp-payload-only
nobase_dist_fuzz_DATA += fuzz-packets-kea-dhcp4/empty
nobase_dist_fuzz_DATA += fuzz-packets-kea-dhcp4/full-dhcp-packet
nobase_dist_fuzz_DATA += fuzz-packets-kea-dhcp4/one-byte
nobase_dist_fuzz_DATA += fuzz-packets-kea-dhcp4/udp-header
nobase_dist_fuzz_DATA += fuzz-packets-kea-dhcp6/dhcp-payload-only
nobase_dist_fuzz_DATA += fuzz-packets-kea-dhcp6/empty
nobase_dist_fuzz_DATA += fuzz-packets-kea-dhcp6/full-dhcp-packet
nobase_dist_fuzz_DATA += fuzz-packets-kea-dhcp6/one-byte
nobase_dist_fuzz_DATA += fuzz-packets-kea-dhcp6/udp-header
nobase_dist_fuzz_DATA += fuzz-unix-socket-kea-dhcp4/config-get
nobase_dist_fuzz_DATA += fuzz-unix-socket-kea-dhcp4/config-get-with-service
nobase_dist_fuzz_DATA += fuzz-unix-socket-kea-dhcp4/empty
nobase_dist_fuzz_DATA += fuzz-unix-socket-kea-dhcp4/empty-json-map
nobase_dist_fuzz_DATA += fuzz-unix-socket-kea-dhcp4/one-byte
nobase_dist_fuzz_DATA += fuzz-unix-socket-kea-dhcp4/one-entry-json-map
nobase_dist_fuzz_DATA += fuzz-unix-socket-kea-dhcp6/config-get
nobase_dist_fuzz_DATA += fuzz-unix-socket-kea-dhcp6/config-get-with-service
nobase_dist_fuzz_DATA += fuzz-unix-socket-kea-dhcp6/empty
nobase_dist_fuzz_DATA += fuzz-unix-socket-kea-dhcp6/empty-json-map
nobase_dist_fuzz_DATA += fuzz-unix-socket-kea-dhcp6/one-byte
nobase_dist_fuzz_DATA += fuzz-unix-socket-kea-dhcp6/one-entry-json-map
nobase_dist_fuzz_DATA += kea-dhcp4.conf
nobase_dist_fuzz_DATA += kea-dhcp6.conf

endif  # FUZZING
