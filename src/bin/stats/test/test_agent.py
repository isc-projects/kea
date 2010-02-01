#!/usr/bin/python

# This program acts statistics agent.
# It has pseudo counters which is incremented each 10 second and
# sends data to "statistics" channel periodically.
# One command is available
#   "Boss"       group: "shutdown"

import isc
import time
import select
import random

step_time = 10
statgroup = "statistics"

cc = isc.cc.Session()
print (cc.lname)
#cc.group_subscribe(statgroup)
cc.group_subscribe("Boss")

# counters

NSSTATDESC={}
NSSTATDESC["counterid"] = 0
NSSTATDESC["requestv4"] = 0
NSSTATDESC["requestv6"] = 0
NSSTATDESC["edns0in"] = 0
NSSTATDESC["badednsver"] = 0
NSSTATDESC["tsigin"] = 0
NSSTATDESC["sig0in"] = 0
NSSTATDESC["invalidsig"] = 0
NSSTATDESC["tcp"] = 0
NSSTATDESC["authrej"] = 0
NSSTATDESC["recurserej"] = 0
NSSTATDESC["xfrrej"] = 0
NSSTATDESC["updaterej"] = 0
NSSTATDESC["response"] = 0
NSSTATDESC["truncatedresp"] = 0
NSSTATDESC["edns0out"] = 0
NSSTATDESC["tsigout"] = 0
NSSTATDESC["sig0out"] = 0
NSSTATDESC["success"] = 0
NSSTATDESC["authans"] = 0
NSSTATDESC["nonauthans"] = 0
NSSTATDESC["referral"] = 0
NSSTATDESC["nxrrset"] = 0
NSSTATDESC["servfail"] = 0
NSSTATDESC["formerr"] = 0
NSSTATDESC["nxdomain"] = 0
NSSTATDESC["recursion"] = 0
NSSTATDESC["duplicate"] = 0
NSSTATDESC["dropped"] = 0
NSSTATDESC["failure"] = 0
NSSTATDESC["xfrdone"] = 0
NSSTATDESC["updatereqfwd"] = 0
NSSTATDESC["updaterespfwd"] = 0
NSSTATDESC["updatefwdfail"] = 0
NSSTATDESC["updatedone"] = 0
NSSTATDESC["updatefail"] = 0
NSSTATDESC["updatebadprereq"] = 0
RESSTATDESC={}
RESSTATDESC["counterid"] = 0
RESSTATDESC["queryv4"] = 0
RESSTATDESC["queryv6"] = 0
RESSTATDESC["responsev4"] = 0
RESSTATDESC["responsev6"] = 0
RESSTATDESC["nxdomain"] = 0
RESSTATDESC["servfail"] = 0
RESSTATDESC["formerr"] = 0
RESSTATDESC["othererror"] = 0
RESSTATDESC["edns0fail"] = 0
RESSTATDESC["mismatch"] = 0
RESSTATDESC["truncated"] = 0
RESSTATDESC["lame"] = 0
RESSTATDESC["retry"] = 0
RESSTATDESC["dispabort"] = 0
RESSTATDESC["dispsockfail"] = 0
RESSTATDESC["querytimeout"] = 0
RESSTATDESC["gluefetchv4"] = 0
RESSTATDESC["gluefetchv6"] = 0
RESSTATDESC["gluefetchv4fail"] = 0
RESSTATDESC["gluefetchv6fail"] = 0
RESSTATDESC["val"] = 0
RESSTATDESC["valsuccess"] = 0
RESSTATDESC["valnegsuccess"] = 0
RESSTATDESC["valfail"] = 0
RESSTATDESC["queryrtt0"] = 0
RESSTATDESC["queryrtt1"] = 0
RESSTATDESC["queryrtt2"] = 0
RESSTATDESC["queryrtt3"] = 0
RESSTATDESC["queryrtt4"] = 0
RESSTATDESC["queryrtt5"] = 0
SOCKSTATDESC={}
SOCKSTATDESC["counterid"] = 0
SOCKSTATDESC["udp4open"] = 0
SOCKSTATDESC["udp6open"] = 0
SOCKSTATDESC["tcp4open"] = 0
SOCKSTATDESC["tcp6open"] = 0
SOCKSTATDESC["unixopen"] = 0
SOCKSTATDESC["udp4openfail"] = 0
SOCKSTATDESC["udp6openfail"] = 0
SOCKSTATDESC["tcp4openfail"] = 0
SOCKSTATDESC["tcp6openfail"] = 0
SOCKSTATDESC["unixopenfail"] = 0
SOCKSTATDESC["udp4close"] = 0
SOCKSTATDESC["udp6close"] = 0
SOCKSTATDESC["tcp4close"] = 0
SOCKSTATDESC["tcp6close"] = 0
SOCKSTATDESC["unixclose"] = 0
SOCKSTATDESC["fdwatchclose"] = 0
SOCKSTATDESC["udp4bindfail"] = 0
SOCKSTATDESC["udp6bindfail"] = 0
SOCKSTATDESC["tcp4bindfail"] = 0
SOCKSTATDESC["tcp6bindfail"] = 0
SOCKSTATDESC["unixbindfail"] = 0
SOCKSTATDESC["fdwatchbindfail"] = 0
SOCKSTATDESC["udp4connectfail"] = 0
SOCKSTATDESC["udp6connectfail"] = 0
SOCKSTATDESC["tcp4connectfail"] = 0
SOCKSTATDESC["tcp6connectfail"] = 0
SOCKSTATDESC["unixconnectfail"] = 0
SOCKSTATDESC["fdwatchconnectfail"] = 0
SOCKSTATDESC["udp4connect"] = 0
SOCKSTATDESC["udp6connect"] = 0
SOCKSTATDESC["tcp4connect"] = 0
SOCKSTATDESC["tcp6connect"] = 0
SOCKSTATDESC["unixconnect"] = 0
SOCKSTATDESC["fdwatchconnect"] = 0
SOCKSTATDESC["tcp4acceptfail"] = 0
SOCKSTATDESC["tcp6acceptfail"] = 0
SOCKSTATDESC["unixacceptfail"] = 0
SOCKSTATDESC["tcp4accept"] = 0
SOCKSTATDESC["tcp6accept"] = 0
SOCKSTATDESC["unixaccept"] = 0
SOCKSTATDESC["udp4sendfail"] = 0
SOCKSTATDESC["udp6sendfail"] = 0
SOCKSTATDESC["tcp4sendfail"] = 0
SOCKSTATDESC["tcp6sendfail"] = 0
SOCKSTATDESC["unixsendfail"] = 0
SOCKSTATDESC["fdwatchsendfail"] = 0
SOCKSTATDESC["udp4recvfail"] = 0
SOCKSTATDESC["udp6recvfail"] = 0
SOCKSTATDESC["tcp4recvfail"] = 0
SOCKSTATDESC["tcp6recvfail"] = 0
SOCKSTATDESC["unixrecvfail"] = 0
SOCKSTATDESC["fdwatchrecvfail"] = 0
SYSSTATDESC={}
SYSSTATDESC['sockets'] = 0
SYSSTATDESC['memory'] = 0

sent = -1
last_sent = -1
loop = 0

while 1:
    NSSTATDESC["requestv4"] += random.randint(1,1000)
    wait = sent + step_time - time.time()
    if wait <= 0:
        last_sent = sent;
        sent = time.time();
        msg = {'component':'auth', 'version':1, 'timestamp':time.time(),'stats':{'NSSTATDESC':NSSTATDESC,'RESSTATDESC':RESSTATDESC,'SOCKSTATDESC':SOCKSTATDESC,'SYSSTATDESC':SYSSTATDESC}}
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
