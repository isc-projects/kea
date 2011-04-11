#
# A simple form of RP: names could be compressed (but MUST NOT).
# rdlen is omitted for the "to wire" test.
#
[custom]
sections: name/1:name/2:rp
[name/1]
name: a.example.com
[name/2]
name: b.example.net
[rp]
rdlen: -1
mailbox: root.example.com
text: rp-text.example.net
