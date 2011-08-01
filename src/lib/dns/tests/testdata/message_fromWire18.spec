#
# Another simple DNS query message with TSIG signed.  Only ID and time signed
# (and MAC as a result) are different.
#

[custom]
sections: header:question:tsig
[header]
id: 0xd6e2
rd: 1
arcount: 1
[question]
name: www.example.com
rrtype: TXT
[tsig]
as_rr: True
# TSIG QNAME won't be compressed
rr_name: www.example.com
algorithm: hmac-md5
time_signed: 0x4e17b38d
mac_size: 16
mac: 0x903b5b194a799b03a37718820c2404f2
original_id: 0xd6e2
