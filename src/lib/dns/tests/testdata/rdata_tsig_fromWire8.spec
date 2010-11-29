#
# TSIG-like RDATA but MAC size is bogus
#
[custom]
sections: tsig
[tsig]
mac_size: 65535
mac: "dummy data"
