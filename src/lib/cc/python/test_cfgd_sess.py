import ISC

cc = ISC.CC.Session()

cc.group_subscribe("ConfigManager")

cmd = { "command": [ "zone", "add", "vix.com" ] }
print("Sending:")
print(cmd)
cc.group_sendmsg(cmd, "ConfigManager")
data, routing = cc.group_recvmsg(False)
print("Answer:")
print(data)

cmd = { "command": [ "zone", "add", "tjeb.nl" ] }
print("Sending:")
print(cmd)
cc.group_sendmsg(cmd, "ConfigManager")
data, routing = cc.group_recvmsg(False)
print("Answer:")
print(data)

cmd = { "command": [ "zone", "add", "flame.org" ] }
print("Sending:")
print(cmd)
cc.group_sendmsg(cmd, "ConfigManager")
data, routing = cc.group_recvmsg(False)
print("Answer:")
print(data)

cmd = { "command": [ "zone", "list" ] }
print("Sending:")
print(cmd)
cc.group_sendmsg(cmd, "ConfigManager")
data, routing = cc.group_recvmsg(False)
print("Answer:")
print(data)

cmd = { "command": [ "zone", "remove", "flame.org" ] }
print("Sending:")
print(cmd)
cc.group_sendmsg(cmd, "ConfigManager")
data, routing = cc.group_recvmsg(False)
print("Answer:")
print(data)

cmd = { "command": [ "zone", "list" ] }
print("Sending:")
print(cmd)
cc.group_sendmsg(cmd, "ConfigManager")
data, routing = cc.group_recvmsg(False)
print("Answer:")
print(data)

cmd = { "command": [ "zone", "bad_command", "foo" ] }
print("Sending:")
print(cmd)
cc.group_sendmsg(cmd, "ConfigManager")
data, routing = cc.group_recvmsg(False)
print("Answer:")
print(data)

cmd = { "command": [ "bad_module", "bad_command", "foo" ] }
print("Sending:")
print(cmd)
cc.group_sendmsg(cmd, "ConfigManager")
data, routing = cc.group_recvmsg(False)
print("Answer:")
print(data)

