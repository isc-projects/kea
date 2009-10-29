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
        self.cc.group_sendmsg({"running": "configmanager"}, "Boss")

    def add_zone(self, zone_name):
        self.config.add_zone(zone_name, "todo")
        print("sending update zone add")
        self.cc.group_sendmsg({"zone_added": zone_name }, "ParkingLot")

    def remove_zone(self, zone_name):
        self.config.remove_zone(zone_name)
        print("sending update zone del")
        self.cc.group_sendmsg({"zone_deleted": zone_name }, "ParkingLot")

    def read_config(self, filename):
        pass

    def write_config(self, filename):
        pass

    def handle_msg(self, msg):
        """return answer message"""
        answer = {}
        try:
            cmd = msg["command"]
            if cmd:
                if cmd[0] == "zone" and cmd[1] == "add":
                    self.add_zone(cmd[2])
                    answer["result"] = [ 0 ]
                elif cmd[0] == "zone" and cmd[1] == "remove":
                    self.remove_zone(cmd[2])
                    answer["result"] = [ 0 ]
                elif cmd[0] == "zone" and cmd[1] == "list":
                    answer["result"] = self.config.zones.keys()
                else:
                    print("unknown command: " + str(cmd))
                    answer["result"] = [ 1, "Unknown command: " + str(cmd) ]
        except KeyError as ke:
            print("unknown module: " + str(msg))
            answer["result"] = [ 1, "Unknown module: " + str(msg) ]
        except IndexError as ie:
            print("missing argument")
            answer["result"] = [ 1, "Missing argument in command" ]
        return answer
        
    def run(self):
        while (True):
            msg, env = self.cc.group_recvmsg(False)
            print("received message: ")
            print(msg)
            answer = self.handle_msg(msg);
            print("sending answer: ")
            print(answer)
            self.cc.group_reply(env, answer)
            print("answer sent")
            pass

if __name__ == "__main__":
    print("Hello, BIND10 world!")
    try:
        cm = ConfigManager()
        # do loading here if necessary
        cm.notify_boss()
        cm.run()
    except ISC.CC.SessionError as se:
        print("Error creating config manager, "
              "is the command channel daemon running?")
