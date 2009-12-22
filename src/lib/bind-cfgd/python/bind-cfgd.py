import ISC
import signal
import ast
import pprint
import os
from ISC.CC import data

class ConfigManagerData:
    CONFIG_VERSION = 1
    DB_FILENAME = "/tmp/parkinglot.db"
    
    def __init__(self):
        self.data = {}
        self.data['version'] = ConfigManagerData.CONFIG_VERSION

    def set_data_definition(self, module_name, module_data_definition):
        self.zones[module_name] = module_data_definition
        self.data_definitions[module_name] = module_data_definition

    def read_from_file():
        config = ConfigManagerData()
        try:
            file = open(ConfigManagerData.DB_FILENAME, 'r')
            file_config = ast.literal_eval(file.read())
            if 'version' in file_config and \
                file_config['version'] == ConfigManagerData.CONFIG_VERSION:
                config.data = file_config
            else:
                # of course we can put in a migration path here for old data
                print("[bind-cfgd] Old version of data found, starting with empty configuration")
            file.close()
        except IOError as ioe:
            print("No config file found, starting with empty config")
        except EOFError as eofe:
            print("Config file empty, starting with empty config")

        return config
        
    def write_to_file(self):
        try:
            tmp_filename = self.DB_FILENAME + ".tmp"
            file = open(tmp_filename, 'w');
            pp = pprint.PrettyPrinter(indent=4)
            s = pp.pformat(self.data)
            file.write(s)
            file.write("\n")
            file.close()
            os.rename(tmp_filename, self.DB_FILENAME)
        except IOError as ioe:
            print("Unable to write config file; configuration not stored")

class ConfigManager:
    def __init__(self):
        self.commands = {}
        self.data_definitions = {}
        self.config = ConfigManagerData()
        self.cc = ISC.CC.Session()
        self.cc.group_subscribe("ConfigManager")
        self.cc.group_subscribe("Boss", "ConfigManager")
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

    def read_config(self):
        print("Reading config")
        self.config = ConfigManagerData.read_from_file()
        
    def write_config(self):
        print("Writing config")
        self.config.write_to_file()

    def handle_msg(self, msg):
        """return answer message"""
        answer = {}
        if "command" in msg:
            cmd = msg["command"]
            try:
                if cmd[0] == "get_commands":
                    answer["result"] = [ 0, self.commands ]
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
                    if conf_part:
                        answer["result"] = [ 0, conf_part ]
                    else:
                        answer["result"] = [ 0 ]
                elif cmd[0] == "set_config":
                    if len(cmd) == 3:
                        # todo: use api (and check types?)
                        if cmd[1] != "":
                            conf_part = data.find_no_exc(self.config.data, cmd[1])
                            if not conf_part:
                                conf_part = data.set(self.config.data, cmd[1], "")
                        else:
                            conf_part = self.config.data
                        data.merge(conf_part, cmd[2])
                        print("[XX bind-cfgd] new config (part):")
                        print(conf_part)
                        # send out changed info
                        self.cc.group_sendmsg({ "config_update": conf_part }, cmd[1])
                        answer["result"] = [ 0 ]
                    elif len(cmd) == 2:
                        print("[XX bind-cfgd] old config:")
                        print(self.config.data)
                        print("[XX bind-cfgd] updating with:")
                        print(cmd[1])
                        data.merge(self.config.data, cmd[1])
                        print("[XX bind-cfgd] new config:")
                        print(self.config.data)
                        # send out changed info
                        for module in self.config.data:
                            self.cc.group_sendmsg({ "config_update": self.config.data[module] }, module)
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
                    answer["result"]     = []#list(self.config.zones.keys())
                elif len(cmd) > 1 and cmd[1] == "shutdown":
                    print("Received shutdown command")
                    self.running = False
                else:
                    print("unknown command: " + str(cmd))
                    answer["result"] = [ 1, "Unknown command: " + str(cmd) ]
            except IndexError as ie:
                print("missing argument")
                answer["result"] = [ 1, "Missing argument in command: " + str(ie) ]
                raise ie
        elif "data_specification" in msg:
            # todo: validate? (no direct access to spec as
            spec = msg["data_specification"]
            if "config_data" in spec:
                self.set_config(spec["module_name"], spec["config_data"])
                self.cc.group_sendmsg({ "specification_update": [ spec["module_name"], spec["config_data"] ] }, "BigTool")
            if "commands" in spec:
                self.set_commands(spec["module_name"], spec["commands"])
                self.cc.group_sendmsg({ "commands_update": [ spec["module_name"], spec["commands"] ] }, "BigTool")
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
                answer = self.handle_msg(msg);
                self.cc.group_reply(env, answer)
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
    
        
