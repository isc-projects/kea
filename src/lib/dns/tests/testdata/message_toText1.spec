#
# A standard DNS message (taken from an invocation of dig)
#

[custom]
sections: header:question:a/1:ns:a/2
[header]
id: 29174
qr: 1
aa: 1
ancount: 1
nscount: 1
arcount: 1
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
