#
# A simple DNS query message with EDNS and TSIG
#

[custom]
sections: header:question:edns:tsig
[header]
id: 0x06cd
rd: 1
arcount: 2
[question]
name: www.example.com
[edns]
[tsig]
as_rr: True
# TSIG QNAME won't be compressed
rr_name: www.example.com
algorithm: hmac-md5
time_signed: 0x4db60d1f
mac_size: 16
mac: 0x93444053881c83d7eb120e86f25b369e
original_id: 0x06cd
