#!/usr/bin/python

# This program acts statistics respondent.
# It has pseudo "counter" which is incremented each 0.3 second and C-channel query.
# Two command is available
#   "statistics" group: "getstat"
#   "Boss"       group: "shutdown"

import ISC
import select
import random

statgroup = "statistics"

cc = ISC.CC.Session()
print (cc.lname)
cc.group_subscribe(statgroup)
cc.group_subscribe("Boss")

counter = 0

while 1:
    r,w,e = select.select([cc._socket],[],[])
    for sock in r:
        if sock == cc._socket:
            data,envelope = cc.group_recvmsg(False);
            if (envelope["group"] == statgroup):
                if (data["command"] == "getstat"):
                    cc.group_reply(envelope,
                                   {
                                    "response":data["command"],
                                    "sent": data["sent"],
                                    "counter":counter
                                   })
                # Do another statistics command
            elif (envelope["group"] == "Boss"):
                if (data["command"] == "shutdown"):
                    exit()
            # Do another group
         # Do another socket
    # Do main work
    counter += random.randrange(1,100)
