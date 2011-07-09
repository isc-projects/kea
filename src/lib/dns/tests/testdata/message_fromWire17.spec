#
# A simple DNS query message with TSIG signed
#

[custom]
sections: header:question:tsig
[header]
id: 0x22c2
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
time_signed: 0x4e179212
mac_size: 16
mac: 0x8214b04634e32323d651ac60b08e6388
original_id: 0x22c2
