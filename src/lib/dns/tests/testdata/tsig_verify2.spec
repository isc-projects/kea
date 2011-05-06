#
# An example of signed AXFR response
#

[custom]
sections: header:question:soa:tsig
[header]
id: 0x3410
aa: 1
qr: 1
ancount: 1
arcount: 1
[question]
rrtype: AXFR
[soa]
# note that names are compressed in this RR
as_rr: True
rr_name: ptr=12
mname: ns.ptr=12
rname: root.ptr=12
serial: 2011041503
refresh: 7200
retry: 3600
expire: 2592000
[tsig]
as_rr: True
rr_name: www.example.com
algorithm: hmac-md5
time_signed: 0x4da8e951
mac_size: 16
mac: 0xbdd612cd2c7f9e0648bd6dc23713e83c
original_id: 0x3410
