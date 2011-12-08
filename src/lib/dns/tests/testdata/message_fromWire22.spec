#
# A simple DNS message containing one SOA RR in the answer section.  This is
# intended to be trimmed to emulate a bogus message.
#

[custom]
sections: header:question:soa
[header]
qr: 1
ancount: 1
[question]
rrtype: SOA
[soa]
as_rr: True
