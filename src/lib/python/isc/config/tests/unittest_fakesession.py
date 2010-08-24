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

#
# We can probably use a more general version of this
#
class FakeModuleCCSession:
    def __init__(self):
        self.subscriptions = {}
        # each entry is of the form [ channel, instance, message ]
        self.message_queue = []
        self._socket = "ok we just need something not-None here atm"

    def group_subscribe(self, group_name, instance_name = None):
        if not group_name in self.subscriptions:
            self.subscriptions[group_name] = []
        if instance_name:
            self.subscriptions[group_name].append(instance_name)
            
    def group_unsubscribe(self, group_name, instance_name = None):
        if group_name in self.subscriptions:
            if instance_name:
                if len(self.subscriptions[group_name]) > 1:
                    del self.subscriptions[group_name][instance_name]
                else:
                    del self.subscriptions[group_name]
            else:
                del self.subscriptions[group_name]
            

    def has_subscription(self, group_name, instance_name = None):
        if group_name in self.subscriptions:
            if instance_name:
                return instance_name in self.subscriptions[group_name]
            else:
                return True
        else:
            return False

    def group_sendmsg(self, msg, channel, target = None):
        self.message_queue.append([ channel, target, msg ])

    def group_reply(self, env, msg):
        if 'group' in env:
            self.message_queue.append([ env['group'], None, msg])

    def group_recvmsg(self, blocking, seq = None):
        for qm in self.message_queue:
            if qm[0] in self.subscriptions and (qm[1] == None or qm[1] in self.subscriptions[qm[0]]):
                self.message_queue.remove(qm)
                return qm[2], {'group': qm[0], 'from': qm[1]}
        return None, None

    def get_message(self, channel, target = None):
        for qm in self.message_queue:
            if qm[0] == channel and qm[1] == target:
                self.message_queue.remove(qm)
                return qm[2]
        return None

    def close(self):
        # need to pass along somehow that this function has been called,
        self._socket = "closed"
        pass
