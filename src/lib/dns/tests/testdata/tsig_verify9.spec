#
# A simple DNS query message with TSIG signed, but TSIG key and algorithm
# names have upper case characters (unusual)
#

[custom]
sections: header:question:tsig
[header]
id: 0x2d65
rd: 1
arcount: 1
[question]
name: www.example.com
[tsig]
as_rr: True
rr_name: WWW.EXAMPLE.COM
algorithm: HMAC-MD5.SIG-ALG.REG.INT
time_signed: 0x4da8877a
mac_size: 16
mac: 0x227026ad297beee721ce6c6fff1e9ef3
original_id: 0x2d65
