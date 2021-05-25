#
# An artificial TKEY RDATA for toWire test.
#
[custom]
sections: tkey
[tkey]
algorithm: GSS-TSIG
error: 16
key_len: 12
# 0x1402... would be FAKEFAKE... if encoded in BASE64
key: 0x140284140284140284140284
