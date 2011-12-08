#
# A non realistic DNS response message containing mixed types of RRs in the
# authority section in a mixed order.
#

[custom]
sections: header:question:a/1:aaaa:a/2
[header]
qr: 1
nscount: 3
[question]
name: www.example.com
rrtype: A
[a/1]
as_rr: True
[aaaa]
as_rr: True
[a/2]
as_rr: True
address: 192.0.2.2
