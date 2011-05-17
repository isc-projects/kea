#
# An example of signed DNS response
#

[custom]
sections: header:question:a:tsig
[header]
id: 0x2d65
aa: 1
qr: 1
rd: 1
ancount: 1
arcount: 1
[question]
name: www.example.com
[a]
as_rr: True
rr_name: ptr=12
[tsig]
as_rr: True
rr_name: www.example.com
algorithm: hmac-md5
time_signed: 0x4da8877a
mac_size: 16
mac: 0x8fcda66a7cd1a3b9948eb1869d384a9f
original_id: 0x2d65
