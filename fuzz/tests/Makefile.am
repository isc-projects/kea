SUBDIRS = .

if FUZZING

check_SCRIPTS  =
check_SCRIPTS += test-fuzz-config-kea-dhcp4.sh
check_SCRIPTS += test-fuzz-config-kea-dhcp6.sh
check_SCRIPTS += test-fuzz-http-endpoint.sh
check_SCRIPTS += test-fuzz-packets-kea-dhcp4.sh
check_SCRIPTS += test-fuzz-packets-kea-dhcp6.sh
check_SCRIPTS += test-fuzz-unix-socket-kea-dhcp4.sh
check_SCRIPTS += test-fuzz-unix-socket-kea-dhcp6.sh

TESTS = $(check_SCRIPTS)

endif  # FUZZING
