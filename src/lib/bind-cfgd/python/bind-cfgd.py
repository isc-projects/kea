import ISC
import pickle
    
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
        print("Reading config")
        try:
            file = open(filename, 'rb');
            self.config = pickle.load(file)
        except IOError as ioe:
            print("No config file found, starting with empty config")
        except EOFError as eofe:
            print("Config file empty, starting with empty config")

    def write_config(self, filename):
        print("Writing config")
        file = open(filename, 'wb');
        pickle.dump(self.config, file)

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
                    answer["result"] = list(self.config.zones.keys())
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
        msg = 1
        while (msg):
            msg, env = self.cc.group_recvmsg(False)
            if msg:
                print("received message: ")
                print(msg)
                answer = self.handle_msg(msg);
                print("sending answer: ")
                print(answer)
                self.cc.group_reply(env, answer)
                print("answer sent")
            
                
if __name__ == "__main__":
    print("Hello, BIND10 world!")
    db_file = "/tmp/parkinglot.db"
    try:
        cm = ConfigManager()
        cm.read_config(db_file)
        # do loading here if necessary
        cm.notify_boss()
        cm.run()
        cm.write_config(db_file)
    except ISC.CC.SessionError as se:
        print("Error creating config manager, "
              "is the command channel daemon running?")
    except KeyboardInterrupt as kie:
        print("Got ctrl-c, save config and exit")
        cm.write_config(db_file)
    
        
