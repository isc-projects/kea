# Copyright (C) 2010  Internet Systems Consortium.
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

# $Id$
# This module is a mock-up class of isc.cc.session

__version__ = "$Revision$"

import sys

# set a dummy lname
_TEST_LNAME = '123abc@xxxx'

class Queue():
    def __init__(self, msg=None, env={}):
        self.msg = msg
        self.env = env

    def dump(self):
        return { 'msg': self.msg, 'env': self.env }
               
class SessionError(Exception):
    pass

class Session:
    def __init__(self, socket_file=None, verbose=False):
        self._lname = _TEST_LNAME
        self.message_queue = []
        self.old_message_queue = []
        self._socket = True
        self.verbose = verbose

    @property
    def lname(self):
        return self._lname

    def close(self):
        self._socket = False

    def _next_sequence(self, que=None):
        return len(self.message_queue)

    def enqueue(self, msg=None, env={}):
        if not self._socket:
            raise SessionError("Session has been closed.")
        seq = self._next_sequence()
        env.update({"seq": 0}) # fixed here
        que = Queue(msg=msg, env=env)
        self.message_queue.append(que)
        if self.verbose:
            sys.stdout.write("[Session] enqueue: " + str(que.dump()) + "\n")
        return seq

    def dequeue(self, seq=0):
        if not self._socket:
            raise SessionError("Session has been closed.")
        que = None
        try:
            que = self.message_queue.pop(seq)
            self.old_message_queue.append(que)
        except IndexError:
            que = Queue()
        if self.verbose:
            sys.stdout.write("[Session] dequeue: " + str(que.dump()) + "\n")
        return que

    def get_queue(self, seq=None):
        if not self._socket:
            raise SessionError("Session has been closed.")
        if seq is None:
            seq = len(self.message_queue) - 1
        que = None
        try:
            que = self.message_queue[seq]
        except IndexError:
            raise IndexError
            que = Queue()
        if self.verbose:
            sys.stdout.write("[Session] get_queue: " + str(que.dump()) + "\n")
        return que

    def group_sendmsg(self, msg, group, instance="*", to="*"):
        return self.enqueue(msg=msg, env={
                "type": "send",
                "from": self._lname,
                "to": to,
                "group": group,
                "instance": instance })

    def group_recvmsg(self, nonblock=True, seq=0):
        que = self.dequeue(seq)
        return que.msg, que.env
        
    def group_reply(self, routing, msg):
        return self.enqueue(msg=msg, env={
                "type": "send",
                "from": self._lname,
                "to": routing["from"],
                "group": routing["group"],
                "instance": routing["instance"],
                "reply": routing["seq"] })

    def get_message(self, group, to='*'):
        if not self._socket:
            raise SessionError("Session has been closed.")
        que = Queue()
        for q in self.message_queue:
            if q.env['group'] == group:
                self.message_queue.remove(q)
                self.old_message_queue.append(q)
                que = q
        if self.verbose:
            sys.stdout.write("[Session] get_message: " + str(que.dump()) + "\n")
        return q.msg

