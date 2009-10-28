import ISC

class ConfigData:
    def __init__(self):
        self.zones = {}

    def add_zone(self, zone_name, zone_file):
        self.zones[zone_name] = zone_file

    def remove_zone(self, zone_name):
        del self.zones[zone_name]

class ConfigManager:
    def __init__(self):
        self.cc = ISC.CC.Session()
        self.cc.group_subscribe("ConfigManager")
        self.config = ConfigData()

    def notify_boss(self):
        self.cc.group_sendmsg({"Running": "ConfigManager"}, "Boss")

    def read_config(self, filename):
        pass

    def write_config(self, filename):
        pass

    def run(self):
        while (True):
            env, msg = self.cc.group_recvmsg(False)
            print "message: "
            print msg
            pass

if __name__ == "__main__":
    print "Hello, BIND10 world!"
    try:
        cm = ConfigManager()
        # do loading here if necessary
        cm.notify_boss()
        cm.run()
    except ISC.CC.SessionError, se:
        print "Error creating config manager, "\
              "is the command channel daemon running?"
