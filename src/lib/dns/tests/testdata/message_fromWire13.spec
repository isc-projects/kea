#
# Invalid TSIG: containing 2 TSIG RRs.
#

[custom]
sections: header:question:tsig:tsig
[header]
id: 0x2d65
rd: 1
arcount: 2
[question]
name: www.example.com
[tsig]
as_rr: True
rr_name: www.example.com
algorithm: hmac-md5
time_signed: 0x4da8877a
mac_size: 16
mac: 0x227026ad297beee721ce6c6fff1e9ef3
original_id: 0x2d65
