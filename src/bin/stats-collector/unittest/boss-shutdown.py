#!/usr/bin/python

import ISC
cc = ISC.CC.Session()
cc.group_subscribe("Boss")
cc.group_sendmsg({ "command":"shutdown"},"Boss")
