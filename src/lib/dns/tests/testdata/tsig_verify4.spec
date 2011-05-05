#
# An example of signed DNS response with bogus MAC
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
# bogus MAC
mac: 0xdeadbeefdeadbeefdeadbeefdeadbeef
original_id: 0x2d65
