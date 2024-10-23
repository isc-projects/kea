SUBDIRS = .

if FUZZING

check_SCRIPTS  =
check_SCRIPTS += test_fuzz_config_kea_dhcp4.sh
check_SCRIPTS += test_fuzz_config_kea_dhcp6.sh
check_SCRIPTS += test_fuzz_http_endpoint_kea_dhcp4.sh
check_SCRIPTS += test_fuzz_http_endpoint_kea_dhcp6.sh
check_SCRIPTS += test_fuzz_packets_kea_dhcp4.sh
check_SCRIPTS += test_fuzz_packets_kea_dhcp6.sh
check_SCRIPTS += test_fuzz_unix_socket_kea_dhcp4.sh
check_SCRIPTS += test_fuzz_unix_socket_kea_dhcp6.sh

TESTS = $(check_SCRIPTS)

endif  # FUZZING
