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
import os
import threading
import bind10_config

import isc.cc.message

class ProtocolError(Exception): pass
class NetworkError(Exception): pass
class SessionError(Exception): pass

class Session:
    def __init__(self, socket_file=None):
        self._socket = None
        # store the current timeout value in seconds (the way
        # settimeout() wants them, our API takes milliseconds
        # so that it is consistent with the C++ version)
        self._socket_timeout = 4;
        self._lname = None
        self._recvbuffer = bytearray()
        self._recvlength = 0
        self._sequence = 1
        self._closed = False
        self._queue = []
        self._lock = threading.RLock()

        if socket_file is None:
            if "BIND10_MSGQ_SOCKET_FILE" in os.environ:
                self.socket_file = os.environ["BIND10_MSGQ_SOCKET_FILE"]
            else:
                self.socket_file = bind10_config.BIND10_MSGQ_SOCKET_FILE
        else:
            self.socket_file = socket_file

        try:
            self._socket = socket.socket(socket.AF_UNIX, socket.SOCK_STREAM)
            self._socket.connect(self.socket_file)
            self.sendmsg({ "type": "getlname" })
            env, msg = self.recvmsg(False)
            if not env:
                raise ProtocolError("Could not get local name")
            self._lname = msg["lname"]
            if not self._lname:
                raise ProtocolError("Could not get local name")
        except socket.error as se:
                raise SessionError(se)

    @property
    def lname(self):
        return self._lname

    def close(self):
        self._socket.close()
        self._lname = None
        self._closed = True

    def sendmsg(self, env, msg = None):
        with self._lock:
            if self._closed:
                raise SessionError("Session has been closed.")
            if type(env) == dict:
                env = isc.cc.message.to_wire(env)
            if type(msg) == dict:
                msg = isc.cc.message.to_wire(msg)
            self._socket.setblocking(1)
            length = 2 + len(env);
            if msg:
                length += len(msg)
            self._socket.send(struct.pack("!I", length))
            self._socket.send(struct.pack("!H", len(env)))
            self._socket.send(env)
            if msg:
                self._socket.send(msg)

    def recvmsg(self, nonblock = True, seq = None):
        with self._lock:
            if len(self._queue) > 0:
                i = 0;
                for env, msg in self._queue:
                    if seq != None and "reply" in env and seq == env["reply"]:
                        return self._queue.pop(i)
                    elif seq == None and "reply" not in env:
                        return self._queue.pop(i)
                    else:
                        i = i + 1
            if self._closed:
                raise SessionError("Session has been closed.")
            data = self._receive_full_buffer(nonblock)
            if data and len(data) > 2:
                header_length = struct.unpack('>H', data[0:2])[0]
                data_length = len(data) - 2 - header_length
                if data_length > 0:
                    env = isc.cc.message.from_wire(data[2:header_length+2])
                    msg = isc.cc.message.from_wire(data[header_length + 2:])
                    if (seq == None and "reply" not in env) or (seq != None and "reply" in env and seq == env["reply"]):
                        return env, msg
                    else:
                        tmp = None
                        if "reply" in env:
                            tmp = env["reply"]
                        self._queue.append((env,msg))
                        return self.recvmsg(nonblock, seq)
                else:
                    return isc.cc.message.from_wire(data[2:header_length+2]), None
            return None, None

    def _receive_full_buffer(self, nonblock):
        if nonblock:
            self._socket.setblocking(0)
        else:
            self._socket.setblocking(1)
            if self._socket_timeout == 0.0:
                self._socket.settimeout(None)
            else:
                self._socket.settimeout(self._socket_timeout)

        if self._recvlength == 0:
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
        self._recvlength = 0
        return (data)

    def _next_sequence(self):
        self._sequence += 1
        return self._sequence

    def group_subscribe(self, group, instance = "*"):
        self.sendmsg({
            "type": "subscribe",
            "group": group,
            "instance": instance,
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
        }, isc.cc.message.to_wire(msg))
        return seq

    def has_queued_msgs(self):
        return len(self._queue) > 0

    def group_recvmsg(self, nonblock = True, seq = None):
        env, msg  = self.recvmsg(nonblock, seq)
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
        }, isc.cc.message.to_wire(msg))
        return seq

    def set_timeout(self, milliseconds):
        """Sets the socket timeout for blocking reads to the given
           number of milliseconds"""
        self._socket_timeout = milliseconds / 1000.0

    def get_timeout(self):
        """Returns the current timeout for blocking reads (in milliseconds)"""
        return self._socket_timeout * 1000.0

if __name__ == "__main__":
    import doctest
    doctest.testmod()
