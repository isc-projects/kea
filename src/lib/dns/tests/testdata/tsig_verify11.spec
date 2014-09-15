#
# A simple DNS query message with TSIG signed with truncated MAC
# using common HMAC-SHA512-256
#

[custom]
sections: header:question:tsig
[header]
id: 0x2d65
rd: 1
arcount: 1
[question]
name: www.example.com
[tsig]
as_rr: True
# TSIG QNAME won't be compressed
rr_name: www.example.com
algorithm: hmac-sha512
time_signed: 0x4da8877a
#mac_size: 64
mac_size: 32
#mac: 0xc4bc4053572d62dd1b26998111565c18056be773dedc6ecea60dff31db2f25966e5d9bafbaaed56efbd5ee2d7e2a12ede4caad630ddf69846c980409724da34e
mac: 0xc4bc4053572d62dd1b26998111565c18056be773dedc6ecea60dff31db2f2596
original_id: 0x2d65
