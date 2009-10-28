import ISC

class ConfigManager:
    def __init__(self):
        self.cc = ISC.CC.Session()
        self.cc.group_subscribe("ConfigManager")

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
        cm.run()
    except ISC.CC.SessionError, se:
        print "Error creating config manager, "\
              "is the command channel daemon running?"
