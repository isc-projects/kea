SUBDIRS = .

if FUZZING

fuzzdir = "${datarootdir}/${PACKAGE_NAME}/fuzz"

nobase_dist_fuzz_DATA  =
nobase_dist_fuzz_DATA += fuzz_config_kea_dhcp4/empty
nobase_dist_fuzz_DATA += fuzz_config_kea_dhcp4/one-byte
nobase_dist_fuzz_DATA += fuzz_config_kea_dhcp6/empty
nobase_dist_fuzz_DATA += fuzz_config_kea_dhcp6/one-byte
nobase_dist_fuzz_DATA += fuzz_http_endpoint_kea_dhcp4/config-get
nobase_dist_fuzz_DATA += fuzz_http_endpoint_kea_dhcp4/config-get-with-service
nobase_dist_fuzz_DATA += fuzz_http_endpoint_kea_dhcp4/empty
nobase_dist_fuzz_DATA += fuzz_http_endpoint_kea_dhcp4/empty-json-map
nobase_dist_fuzz_DATA += fuzz_http_endpoint_kea_dhcp4/one-byte
nobase_dist_fuzz_DATA += fuzz_http_endpoint_kea_dhcp4/one-entry-json-map
nobase_dist_fuzz_DATA += fuzz_http_endpoint_kea_dhcp6/config-get
nobase_dist_fuzz_DATA += fuzz_http_endpoint_kea_dhcp6/config-get-with-service
nobase_dist_fuzz_DATA += fuzz_http_endpoint_kea_dhcp6/empty
nobase_dist_fuzz_DATA += fuzz_http_endpoint_kea_dhcp6/empty-json-map
nobase_dist_fuzz_DATA += fuzz_http_endpoint_kea_dhcp6/one-byte
nobase_dist_fuzz_DATA += fuzz_http_endpoint_kea_dhcp6/one-entry-json-map
nobase_dist_fuzz_DATA += fuzz_packets_kea_dhcp4/dhcp-payload-only
nobase_dist_fuzz_DATA += fuzz_packets_kea_dhcp4/empty
nobase_dist_fuzz_DATA += fuzz_packets_kea_dhcp4/full-dhcp-packet
nobase_dist_fuzz_DATA += fuzz_packets_kea_dhcp4/one-byte
nobase_dist_fuzz_DATA += fuzz_packets_kea_dhcp4/udp-header
nobase_dist_fuzz_DATA += fuzz_packets_kea_dhcp6/dhcp-payload-only
nobase_dist_fuzz_DATA += fuzz_packets_kea_dhcp6/empty
nobase_dist_fuzz_DATA += fuzz_packets_kea_dhcp6/full-dhcp-packet
nobase_dist_fuzz_DATA += fuzz_packets_kea_dhcp6/one-byte
nobase_dist_fuzz_DATA += fuzz_packets_kea_dhcp6/udp-header
nobase_dist_fuzz_DATA += fuzz_unix_socket_kea_dhcp4/config-get
nobase_dist_fuzz_DATA += fuzz_unix_socket_kea_dhcp4/config-get-with-service
nobase_dist_fuzz_DATA += fuzz_unix_socket_kea_dhcp4/empty
nobase_dist_fuzz_DATA += fuzz_unix_socket_kea_dhcp4/empty-json-map
nobase_dist_fuzz_DATA += fuzz_unix_socket_kea_dhcp4/one-byte
nobase_dist_fuzz_DATA += fuzz_unix_socket_kea_dhcp4/one-entry-json-map
nobase_dist_fuzz_DATA += fuzz_unix_socket_kea_dhcp6/config-get
nobase_dist_fuzz_DATA += fuzz_unix_socket_kea_dhcp6/config-get-with-service
nobase_dist_fuzz_DATA += fuzz_unix_socket_kea_dhcp6/empty
nobase_dist_fuzz_DATA += fuzz_unix_socket_kea_dhcp6/empty-json-map
nobase_dist_fuzz_DATA += fuzz_unix_socket_kea_dhcp6/one-byte
nobase_dist_fuzz_DATA += fuzz_unix_socket_kea_dhcp6/one-entry-json-map
nobase_dist_fuzz_DATA += kea-dhcp4.conf
nobase_dist_fuzz_DATA += kea-dhcp6.conf

endif  # FUZZING
