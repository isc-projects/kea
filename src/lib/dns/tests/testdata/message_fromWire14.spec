#
# Invalid TSIG: not in the additional section.
#

[custom]
sections: header:question:tsig
[header]
id: 0x2d65
rd: 1
# TSIG goes to the answer section
ancount: 1
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
