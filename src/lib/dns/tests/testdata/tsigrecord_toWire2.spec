#
# TSIG RR after some names that could (unexpectedly) cause name compression
#

[custom]
sections: name/1:name/2:tsig
[name/1]
name: hmac-md5.sig-alg.reg.int
[name/2]
name: foo.example.com
[tsig]
as_rr: True
# TSIG QNAME won't be compressed
rr_name: www.example.com
algorithm: hmac-md5
time_signed: 0x4da8877a
mac_size: 16
mac: 0xdadadadadadadadadadadadadadadada
original_id: 0x2d65
