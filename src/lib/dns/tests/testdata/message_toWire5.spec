#
# A longest possible (without EDNS) DNS response with TSIG, i.e. total
# length should be 512 bytes.
#

[custom]
sections: header:question:txt/1:txt/2:tsig
[header]
id: 0xd6e2
rd: 1
qr: 1
aa: 1
ancount: 2
arcount: 1
[question]
name: www.example.com
rrtype: TXT
[txt/1]
as_rr: True
# QNAME is fully compressed
rr_name: ptr=12
string: 0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcde
[txt/2]
as_rr: True
# QNAME is fully compressed
rr_name: ptr=12
string: 0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0123456789abcdef0
[tsig]
as_rr: True
# TSIG QNAME won't be compressed
rr_name: www.example.com
algorithm: hmac-md5
time_signed: 0x4e17b38d
mac_size: 16
mac: 0xbe2ba477373d2496891e2fda240ee4ec
original_id: 0xd6e2
