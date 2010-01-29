#!/usr/bin/python

# This program acts statistics agent.
# It has pseudo counters which is incremented each 10 second and
# sends data to "statistics" channel periodically.
# One command is available
#   "Boss"       group: "shutdown"

import ISC
import time
import select
import random

step_time = 10
statgroup = "statistics"

cc = ISC.CC.Session()
print (cc.lname)
#cc.group_subscribe(statgroup)
cc.group_subscribe("Boss")

# counters

AUTH={}
AUTH['counterid'] = 0
AUTH['requestv4'] = 2
AUTH['requestv6'] = 1
SYS={}
SYS['sockets'] = 0
SYS['memory'] = 0

sent = -1
last_sent = -1
loop = 0

while 1:
    wait = sent + step_time - time.time()
    if wait <= 0:
        last_sent = sent;
        sent = time.time();
        msg = {'component':'auth', 'version':1, 'timestamp':time.time(),'stats':{'AUTH':AUTH,'SYS':SYS}}
        print (msg)
        print (cc.group_sendmsg(msg, statgroup))
        wait = last_sent + step_time - time.time()
        if wait < 0:
            wait = step_time
        loop += 1
    r,w,e = select.select([cc._socket],[],[], wait)
    for sock in r:
        if sock == cc._socket:
            data,envelope = cc.group_recvmsg(False)
            print (data)
            if (envelope["group"] == "Boss"):
                if ("shutdown" in data):
                    exit()
            else:
                print ("Unknown data: ", envelope,data)
