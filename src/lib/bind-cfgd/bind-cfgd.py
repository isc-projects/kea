import ISC

class ConfigManager:
    def __init__(self):
        self.cc = ISC.CC.Session()

    def read_config(self, filename):
        pass

    def write_config(self, filename):
        pass

    def run(self):
        while (True):
            pass

if __name__ == "__main__":
    print "Hello, BIND10 world!"
    try:
        cm = ConfigManager()
        cm.run()
    except ISC.CC.SessionError, se:
        print "Error creating config manager, "\
              "is the command channel daemon running?"
