#
# A simplest form of TSIG, but the algorithm name is compressed (quite
# pathological, but we accept it)
#
[custom]
sections: name:tsig
[name]
name: hmac-sha256
[tsig]
algorithm: ptr=0
mac_size: 32
