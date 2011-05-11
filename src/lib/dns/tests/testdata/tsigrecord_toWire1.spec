#
# A simple TSIG RR (some of the parameters are taken from a live example
# and don't have a specific meaning)
#

[custom]
sections: tsig
[tsig]
as_rr: True
# TSIG QNAME won't be compressed
rr_name: www.example.com
algorithm: hmac-md5
time_signed: 0x4da8877a
mac_size: 16
mac: 0xdadadadadadadadadadadadadadadada
original_id: 0x2d65
