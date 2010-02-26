

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
        pass

    def group_recvmsg(self, blocking):
        for qm in self.message_queue:
            if qm[0] in self.subscriptions and (qm[1] == None or qm[1] in self.subscriptions[qm[0]]):
                self.message_queue.remove(qm)
                return qm[2], {}
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
