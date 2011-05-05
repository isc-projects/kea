#
# An example of signed AXFR response (continued)
#

[custom]
sections: header:ns:tsig
[header]
id: 0x3410
aa: 1
qr: 1
qdcount: 0
ancount: 1
arcount: 1
[ns]
# note that names are compressed in this RR
as_rr: True
rr_name: example.com.
nsname: ns.ptr=12
[tsig]
as_rr: True
rr_name: www.example.com
algorithm: hmac-md5
time_signed: 0x4da8e951
mac_size: 16
mac: 0x102458f7f62ddd7d638d746034130968
original_id: 0x3410
