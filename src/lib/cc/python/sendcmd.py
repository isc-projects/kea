#!/usr/bin/python3
import ISC, sys

cc = ISC.CC.Session()
if len(sys.argv) < 3:
    sys.stderr.write('Usage: ' + sys.argv[0] + ' <channel> <command> [arg]\n')
    sys.exit(1)

channel = sys.argv[1]
command = sys.argv[2]
if len(sys.argv) >= 4:
    argument = sys.argv[3]
else:
    argument = ""

cmd = { "command": [ command, argument ] }

cc.group_subscribe(channel)
print("Sending:")
print(cmd)
cc.group_sendmsg(cmd, channel)
