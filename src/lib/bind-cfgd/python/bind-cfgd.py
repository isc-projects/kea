import ISC
import pickle
import signal
from ISC.CC import data

class ConfigData:
    def __init__(self):
        self.zones = {}
        self.data = {}

    def add_zone(self, zone_name, zone_file):
        self.zones[zone_name] = zone_file

    def remove_zone(self, zone_name):
        del self.zones[zone_name]

    def set_data_definition(self, module_name, module_data_definition):
        print ("[XX] set datadef for module " + module_name)
        print ("[XX]")
        print (self.zones)
        self.zones[module_name] = module_data_definition
        print (self.data_definitions)
        self.data_definitions[module_name] = module_data_definition

class ConfigManager:
    def __init__(self):
        self.commands = {}
        self.data_definitions = {}
        self.config = ConfigData()
        self.cc = ISC.CC.Session()
        self.cc.group_subscribe("ConfigManager")
        self.cc.group_subscribe("Boss", "ConfigManager")
        self.db_filename = "/tmp/parkinglot.db"
        self.running = False

    def notify_boss(self):
        self.cc.group_sendmsg({"running": "configmanager"}, "Boss")

    def set_config(self, module_name, data_specification):
        self.data_definitions[module_name] = data_specification
        
    def remove_config(self, module_name):
        self.data_definitions[module_name]

    def set_commands(self, module_name, commands):
        self.commands[module_name] = commands

    def remove_commands(self, module_name):
        del self.commands[module_name]

    def add_zone(self, zone_name):
        self.config.add_zone(zone_name, "todo")
        self.write_config()
        print("sending update zone add")
        self.cc.group_sendmsg({"zone_added": zone_name }, "ParkingLot")

    def remove_zone(self, zone_name):
        self.config.remove_zone(zone_name)
        print("sending update zone del")
        self.cc.group_sendmsg({"zone_deleted": zone_name }, "ParkingLot")

    def read_config(self):
        print("Reading config")
        try:
            file = open(self.db_filename, 'rb');
            self.config = pickle.load(file)
            file.close()
        except IOError as ioe:
            print("No config file found, starting with empty config")
        except EOFError as eofe:
            print("Config file empty, starting with empty config")

    def write_config(self):
        print("Writing config")
        try:
            file = open(self.db_filename, 'wb');
            pickle.dump(self.config, file)
            file.close()
        except IOError as ioe:
            print("Unable to write config file; configuration not stored")

    def handle_msg(self, msg):
        """return answer message"""
        answer = {}
        if "command" in msg:
            cmd = msg["command"]
            try:
                if cmd[0] == "get_commands":
                    answer["result"] = self.commands
                elif cmd[0] == "get_data_spec":
                    if len(cmd) > 1 and cmd[1] != "":
                        try:
                            answer["result"] = [0, self.data_definitions[cmd[1]]]
                        except KeyError as ke:
                            answer["result"] = [1, "No specification for module " + cmd[1]]
                    else:
                        answer["result"] = [0, self.data_definitions]
                elif cmd[0] == "get_config":
                    # we may not have any configuration here
                    conf_part = None
                    if len(cmd) > 1:
                        try:
                            conf_part = data.find(self.config.data, cmd[1])
                        except data.DataNotFoundError as dnfe:
                            pass
                    else:
                        conf_part = self.config.data
                    answer["result"] = [ 0, conf_part ]
                elif cmd[0] == "set_config":
                    print("[XX] cmd len: " + str(len(cmd)))
                    print("[XX] cmd 0: " + str(cmd[0]))
                    print("[XX] cmd 1: " + str(cmd[1]))
                    print("[XX] cmd 2: " + str(cmd[2]))
                    if len(cmd) == 3:
                        # todo: use api (and check types?)
                        if cmd[1] != "":
                            conf_part = data.find_no_exc(self.config.data, cmd[1])
                            if not conf_part:
                                conf_part = data.set(self.config.data, cmd[1], "")
                        else:
                            conf_part = self.config.data
                        conf_part.update(cmd[2])
                        # send out changed info
                        answer["result"] = [ 0 ]
                    elif len(cmd) == 2:
                        self.config.data.update(cmd[1])
                        # send out changed info
                        answer["result"] = [ 0 ]
                    else:
                        answer["result"] = [ 1, "Wrong number of arguments" ]
                elif cmd[0] == "zone" and cmd[1] == "add":
                    self.add_zone(cmd[2])
                    answer["result"] = [ 0 ]
                elif cmd[0] == "zone" and cmd[1] == "remove":
                    self.remove_zone(cmd[2])
                    answer["result"] = [ 0 ]
                elif cmd[0] == "zone" and cmd[1] == "list":
                    answer["result"]     = list(self.config.zones.keys())
                elif len(cmd) > 1 and cmd[1] == "shutdown":
                    print("Received shutdown command")
                    self.running = False
                else:
                    print("unknown command: " + str(cmd))
                    answer["result"] = [ 1, "Unknown command: " + str(cmd) ]
            except IndexError as ie:
                print("missing argument")
                answer["result"] = [ 1, "Missing argument in command: " + str(ie) ]
        elif "data_specification" in msg:
            # todo: validate? (no direct access to spec as
            spec = msg["data_specification"]
            if "config_data" in spec:
                self.set_config(spec["module_name"], spec["config_data"])
            if "commands" in spec:
                self.set_commands(spec["module_name"], spec["commands"])
            answer["result"] = [ 0 ]
        else:
            print("unknown message: " + str(msg))
            answer["result"] = [ 1, "Unknown module: " + str(msg) ]
        return answer
        
    def run(self):
        self.running = True
        while (self.running):
            msg, env = self.cc.group_recvmsg(False)
            if msg:
                print("received message: ")
                print(msg)
                answer = self.handle_msg(msg);
                print("sending answer: ")
                print(answer)
                self.cc.group_reply(env, answer)
                print("answer sent")
            else:
                self.running = False

cm = None

def signal_handler(signal, frame):
    global cm
    if cm:
        cm.running = False

if __name__ == "__main__":
    print("Hello, BIND10 world!")
    try:
        cm = ConfigManager()
        signal.signal(signal.SIGINT, signal_handler)
        signal.signal(signal.SIGTERM, signal_handler)
        cm.read_config()
        cm.notify_boss()
        cm.run()
        cm.write_config()
    except ISC.CC.SessionError as se:
        print("Error creating config manager, "
              "is the command channel daemon running?")
    except KeyboardInterrupt as kie:
        print("Got ctrl-c, save config and exit")
        cm.write_config()
    
        
