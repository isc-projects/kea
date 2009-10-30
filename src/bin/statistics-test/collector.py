#!/usr/bin/python
#
# This program collects "counter" from "statistics" channel.
# It accepts one command: "Boss" group "shutdown"

import ISC
import time
import select
import sys
import os

step_time = 1
statgroup = "statistics"

cc = ISC.CC.Session()
# print (cc.lname)
cc.group_subscribe(statgroup)
cc.group_subscribe("Boss")

f = open('statistics.out', 'a')
sys.stdout = f

server_by_name = {}
server_by_id = []
counter = []
timestamp = []
servers = 0
delta_sum = 0
received = 0
output_time = -1
output_delta = -1

sent = -1
last_sent = -1
loop = 0
while 1:
    wait = sent + step_time - time.time()
    if wait <= 0:
        sent = time.time();
        command = { "command": "getstat", "sent":time.time() }
        #print ("loop=", loop, "    SEND: ", command)
        cc.group_sendmsg(command, "statistics")
        wait = last_sent + step_time - time.time()
        if wait < 0:
            wait = step_time
        loop += 1
        delta_sum = -1
        received = 0
    r,w,e = select.select([cc._socket],[],[], wait)
    for sock in r:
        if sock == cc._socket:
            data,envelope = cc.group_recvmsg(False)
            if (envelope["group"] == "Boss"):
                if ("shutdown" in data):
                    exit()
            if (envelope["group"] == statgroup):
                if (envelope["from"] in server_by_name):
                    id = server_by_name[envelope["from"]]
                    delta_t = float(data["sent"]) - float(timestamp[id])
                    delta_c = float(data["counter"]) - float(counter[id])
                    print ("server",id,"  time=",data["sent"], end=" "),
                    print ("counter=", data["counter"], end=" ")
                    print ("dT=", delta_t, "  dC=", delta_c)
                    sys.stdout.flush()
                    timestamp[id] = data["sent"]
                    counter[id] = data["counter"]
#
                    if (timestamp[id] == sent):
                        received += 1
                else:
                    print ("server ", servers, " name ", envelope["from"])
                    server_by_id.append(envelope["from"])
                    server_by_name[envelope["from"]] = len(server_by_id) - 1
                    counter.append(data["counter"])
                    timestamp.append(data["sent"])
                    servers += 1
