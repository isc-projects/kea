#
# A simple DNS query message with TSIG signed whose MAC is too short
# (only 1 byte)
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
algorithm: hmac-md5
time_signed: 0x4da8877a
mac_size: 1
mac: 0x22
original_id: 0x2d65
