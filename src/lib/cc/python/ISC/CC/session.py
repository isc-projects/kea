# Copyright (C) 2009  Internet Systems Consortium.
#
# Permission to use, copy, modify, and distribute this software for any
# purpose with or without fee is hereby granted, provided that the above
# copyright notice and this permission notice appear in all copies.
#
# THE SOFTWARE IS PROVIDED "AS IS" AND INTERNET SYSTEMS CONSORTIUM
# DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL
# INTERNET SYSTEMS CONSORTIUM BE LIABLE FOR ANY SPECIAL, DIRECT,
# INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING
# FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT,
# NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION
# WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

import sys
import socket
import struct

import Message

class ProtocolError(Exception): pass
class NetworkError(Exception): pass
class SessionError(Exception): pass

class Session:
    def __init__(self):
        self._socket = None
        self._lname = None
        self._recvbuffer = ""
        self._recvlength = None
        self._sendbuffer = ""
        self._sequence = 1

        try:
            self._socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            self._socket.connect(tuple(['127.0.0.1', 9912]))

            self.sendmsg({ "type": "getlname" })
            msg = self.recvmsg(False)
            self._lname = msg["lname"]
            if not self._lname:
                raise ProtocolError("Could not get local name")
        except socket.error, se:
                raise SessionError(se)

    @property
    def lname(self):
        return self._lname

    def sendmsg(self, msg):
        if type(msg) == dict:
            msg = Message.to_wire(msg)
        self._socket.setblocking(1)
        self._socket.send(struct.pack("!I", len(msg)))
        self._socket.send(msg)

    def recvmsg(self, nonblock = True):
        data = self._receive_full_buffer(nonblock)
        if data:
            return Message.from_wire(data)
        return None

    def _receive_full_buffer(self, nonblock):
        if nonblock:
            self._socket.setblocking(0)
        else:
            self._socket.setblocking(1)

        if self._recvlength == None:
            length = 4
            length -= len(self._recvbuffer)
            try:
                data = self._socket.recv(length)
            except:
                return None
            if data == "": # server closed connection
                raise ProtocolError("Read of 0 bytes: connection closed")

            self._recvbuffer += data
            if len(self._recvbuffer) < 4:
                return None
            self._recvlength = struct.unpack('>I', self._recvbuffer)[0]
            self._recvbuffer = ""

        length = self._recvlength - len(self._recvbuffer)
        while (length > 0):
            try:
                data = self._socket.recv(length)
            except:
                return None
            if data == "": # server closed connection
                raise ProtocolError("Read of 0 bytes: connection closed")
            self._recvbuffer += data
            length -= len(data)
        data = self._recvbuffer
        self._recvbuffer = ""
        self._recvlength = None
        return (data)

    def _next_sequence(self):
        self._sequence += 1
        return self._sequence

    def group_subscribe(self, group, instance = "*", subtype = "normal"):
        self.sendmsg({
            "type": "subscribe",
            "group": group,
            "instance": instance,
            "subtype": subtype,
        })

    def group_unsubscribe(self, group, instance = "*"):
        self.sendmsg({
            "type": "unsubscribe",
            "group": group,
            "instance": instance,
        })

    def group_sendmsg(self, msg, group, instance = "*", to = "*"):
        seq = self._next_sequence()
        self.sendmsg({
            "type": "send",
            "from": self._lname,
            "to": to,
            "group": group,
            "instance": instance,
            "seq": seq,
            "msg": Message.to_wire(msg),
        })
        return seq

    def group_recvmsg(self, nonblock = True):
        msg = self.recvmsg(nonblock)
        if msg == None:
            return None
        data = Message.from_wire(msg["msg"])
        return (data, msg)

    def group_reply(self, routing, msg):
        seq = self._next_sequence()
        self.sendmsg({
            "type": "send",
            "from": self._lname,
            "to": routing["from"],
            "group": routing["group"],
            "instance": routing["instance"],
            "seq": seq,
            "reply": routing["seq"],
            "msg": Message.to_wire(msg),
        })
        return seq

if __name__ == "__main__":
    import doctest
    doctest.testmod()
