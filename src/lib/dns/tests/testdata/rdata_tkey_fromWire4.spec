#
# A simplest form of TKEY, but the algorithm name is compressed (quite
# pathological, but we accept it)
#
[custom]
sections: name:tkey
[name]
name: gss-tsig
[tkey]
algorithm: ptr=0
key_len: 32
