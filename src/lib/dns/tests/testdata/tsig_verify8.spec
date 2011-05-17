#
# DNS query message with TSIG that has empty MAC + BADKEY error
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
mac_size: 0
mac: ''
# 17: BADKEY
error: 17
original_id: 0x2d65
