import ISC
import time
import select

timeout = 1

tcp = ISC.CC.Session()
print tcp.lname

tcp.group_subscribe("statistics")

sent = time.time()
tcp.group_sendmsg({ "command": "whoareyou"}, "statistics")

print "SEND: whoareyou"
while (sent + timeout - time.time()) > 0:
    wait = sent + timeout - time.time()
    print "wait=",wait
    r,w,e = select.select([tcp._socket],[],[], wait)
    for sock in r:
        if sock == tcp._socket:
            data,envelope = tcp.group_recvmsg(False); 
            print "data:", data

print ""

loop = 0
while loop < 10000:
    print "loop=", loop, "    SEND: getstat"
    sent = time.time();
    tcp.group_sendmsg({ "command": "getstat"}, "statistics")
    while (sent + timeout - time.time()) > 0:
        wait = sent + timeout - time.time()
        r,w,e = select.select([tcp._socket],[],[], wait)
        for sock in r:
            if sock == tcp._socket:
                data,envelope = tcp.group_recvmsg(False); 
                print envelope["from"], " : ", data
    loop += 1
