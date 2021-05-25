#
# An artificial TKEY RDATA for toWire test.
#
[custom]
sections: tkey
[tkey]
algorithm: gss.tsig
error: 16
key_len: 12
# 0x1402... would be FAKEFAKE... if encoded in BASE64
key: 0x140284140284140284140284
other_len: 6
other_data: 0x140284140284
