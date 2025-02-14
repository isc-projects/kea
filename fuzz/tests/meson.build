foreach i : [
    'test_fuzz_http_endpoint_kea_dhcp4.sh',
    'test_fuzz_packets_kea_dhcp6.sh',
    'test_fuzz_config_kea_dhcp4.sh',
    'test_fuzz_packets_kea_dhcp4.sh',
    'test_fuzz_unix_socket_kea_dhcp6.sh',
    'test_fuzz_config_kea_dhcp6.sh',
    'test_fuzz_unix_socket_kea_dhcp4.sh',
    'test_fuzz_http_endpoint_kea_dhcp6.sh',
]
    t = configure_file(input: i, output: i, copy: true)
    test(i, t)
endforeach
