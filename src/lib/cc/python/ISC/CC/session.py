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

from ISC.CC import Message

class ProtocolError(Exception): pass
class NetworkError(Exception): pass
class SessionError(Exception): pass

class Session:
    def __init__(self, port=9912):
        self._socket = None
        self._lname = None
        self._recvbuffer = bytearray()
        self._recvlength = None
        self._sendbuffer = bytearray()
        self._sequence = 1

        try:
            self._socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
            self._socket.connect(tuple(['127.0.0.1', port]))

            self.sendmsg({ "type": "getlname" })
            env, msg = self.recvmsg(False)
            self._lname = msg["lname"]
            if not self._lname:
                raise ProtocolError("Could not get local name")
        except socket.error as se:
                raise SessionError(se)

    @property
    def lname(self):
        return self._lname

    def sendmsg(self, env, msg = None):
        if type(env) == dict:
            env = Message.to_wire(env)
        if type(msg) == dict:
            msg = Message.to_wire(msg)
        self._socket.setblocking(1)
        length = 2 + len(env);
        if msg:
            length += len(msg)
        self._socket.send(struct.pack("!I", length))
        self._socket.send(struct.pack("!H", len(env)))
        self._socket.send(env)
        if msg:
            self._socket.send(msg)

    def recvmsg(self, nonblock = True):
        data = self._receive_full_buffer(nonblock)
        if data and len(data) > 2:
            header_length = struct.unpack('>H', data[0:2])[0]
            data_length = len(data) - 2 - header_length
            if data_length > 0:
                return Message.from_wire(data[2:header_length+2]), Message.from_wire(data[header_length + 2:])
            else:
                return Message.from_wire(data[2:header_length+2]), None
        return None, None

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
            self._recvbuffer = bytearray()

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
        self._recvbuffer = bytearray()
        self._recvlength = None
        return (data)

    def _next_sequence(self):
        self._sequence += 1
        return self._sequence

    def group_subscribe(self, group, instance = "*", subtype = "normal"):
        """subtype can be 'normal' or 'meonly'"""
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
        }, Message.to_wire(msg))
        return seq

    def group_recvmsg(self, nonblock = True):
        env, msg  = self.recvmsg(nonblock)
        if env == None:
            # return none twice to match normal return value
            # (so caller won't get a type error on no data)
            return (None, None)
        return (msg, env)

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
        }, Message.to_wire(msg))
        return seq

if __name__ == "__main__":
    import doctest
    doctest.testmod()
