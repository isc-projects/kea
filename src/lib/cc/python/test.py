import ISC

ss = { "list": [ 1, 2, 3 ],
       "hash": { "hash1": 1, "hash2": 2 },
       "none": None,
       "string": "samplestring" }

s = ISC.CC.Message.to_wire(ss)
ISC.Util.hexdump(s)

print(ISC.CC.Message.from_wire(s))

tcp = ISC.CC.Session()
print(tcp.lname)

tcp.group_subscribe("test")

counter = 0
while counter < 10000:
    tcp.group_sendmsg({ "counter": counter }, "test", "foo")
    routing, data = tcp.group_recvmsg(False)
    counter += 1
