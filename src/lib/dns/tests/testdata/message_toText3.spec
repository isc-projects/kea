#
# A standard DNS message with TSIG (taken from an invocation of dig)
#

[custom]
sections: header:question:a/1:ns:a/2:tsig
[header]
id: 10140
qr: 1
aa: 1
ancount: 1
nscount: 1
arcount: 2
[question]
name: www.example.com
[a/1]
as_rr: True
rr_name: www.example.com
address: 192.0.2.80
[ns]
as_rr: True
[a/2]
as_rr: True
rr_name: ns.example.com
[tsig]
as_rr: True
rr_name: www.example.com
algorithm: hmac-md5
time_signed: 1304384318
original_id: 10140
mac: 0x5257c80396f2fa95b20c77ae9a652fb2
