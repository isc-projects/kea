#
# Truncated DNS response with TSIG signed
# This is expected to be a response to "fromWire17"
#

[custom]
sections: header:question:tsig
[header]
id: 0x22c2
rd: 1
qr: 1
aa: 1
# It's "truncated":
tc: 1
arcount: 1
[question]
name: www.example.com
rrtype: TXT
[tsig]
as_rr: True
# TSIG QNAME won't be compressed
rr_name: www.example.com
algorithm: hmac-md5
time_signed: 0x4e179212
mac_size: 16
mac: 0x88adc3811d1d6bec7c684438906fc694
original_id: 0x22c2
