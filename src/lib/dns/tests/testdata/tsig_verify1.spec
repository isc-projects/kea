#
# An example of signed AXFR request
#

[custom]
sections: header:question:tsig
[header]
id: 0x3410
arcount: 1
[question]
rrtype: AXFR
[tsig]
as_rr: True
rr_name: www.example.com
algorithm: hmac-md5
time_signed: 0x4da8e951
mac_size: 16
mac: 0x35b2fd08268781634400c7c8a5533b13
original_id: 0x3410
