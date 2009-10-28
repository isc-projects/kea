#!/usr/bin/python

# This program acts statistics respondent.
# It has pseudo "counter" which is incremented each 0.3 second and C-channel query.
# Two command is available
#   "whoareyou"
#   "getstat"

import ISC
import socket
import select
import time

statgroup = "statistics"

cc = ISC.CC.Session()
print cc.lname
cc.group_subscribe(statgroup)

counter = 0

while 1:
    r,w,e = select.select([cc._socket],[],[],0.3)
    counter += 1
    for sock in r:
        if sock == cc._socket:
            data,envelope = cc.group_recvmsg(False);
            if (envelope["group"] == statgroup):
                print data["command"]
                if (data["command"] == "whoareyou"):
                    cc.group_reply(envelope, {"name": cc.lname })
                elif (data["command"] == "getstat"):
                    cc.group_reply(envelope, {"timestamp": time.time(), "counter":counter})
            # Do another group
         # Do another socket
    # Do main work
