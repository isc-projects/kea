#!/usr/bin/python

import isc
cc = isc.cc.Session()
cc.group_subscribe("Boss")
cc.group_sendmsg({ "command":"shutdown"},"Boss")
