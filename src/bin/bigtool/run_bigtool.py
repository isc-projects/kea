from moduleinfo  import *
from bigtool import *
import ISC


def _prepare_fake_data(bigtool):
    add_cmd = CommandInfo(name = "add", desc = "add one zone")
    remove_cmd = CommandInfo(name = 'remove', desc = 'remove one zone')
    list_cmd = CommandInfo(name = 'list', desc = 'list all zones', 
                           need_inst_param = False)                                                                                           

    zone_module = ModuleInfo(name = "zone", 
                             inst_name = "zone_name", 
                             inst_type = STRING_TYPE, 
                             inst_desc = "the name of one zone",
                             desc = "manage all the zones")
    zone_module.add_command(add_cmd)
    zone_module.add_command(remove_cmd)
    zone_module.add_command(list_cmd)

    shutdown_param = ParamInfo(name = "module_name", desc = "the name of module")
    shutdown_cmd = CommandInfo(name = 'shutdown', desc = "stop bind10",
                               need_inst_param = False)
    shutdown_cmd.add_param(shutdown_param)
    boss_module = ModuleInfo(name = "boss", desc = "boss of bind10")
    boss_module.add_command(shutdown_cmd)               

    bigtool.add_module_info(zone_module)
    bigtool.add_module_info(boss_module)

def prepare_data_module(bigtool, module_name, module_commands):
    module = ModuleInfo(name = module_name,
                        desc = "same here")
    for command in module_commands:
        cmd = CommandInfo(name = command["command_name"],
                          desc = "todo2",
                          need_inst_param = False)
        for arg in command["command_args"]:
            param = ParamInfo(name = arg["item_name"],
                              type = arg["item_type"],
                              optional = bool(arg["item_optional"]))
            if ("item_default" in arg):
                param.default = arg["item_default"]
            cmd.add_param(param)
        module.add_command(cmd)
    bigtool.add_module_info(module)

def prepare_data(bigtool, command_spec):
    for module_name in command_spec.keys():
        prepare_data_module(bigtool, module_name, command_spec[module_name])
    
if __name__ == '__main__':
    try:
        cc = ISC.CC.Session()
        cc.group_subscribe("BigTool", "*", "meonly")
        cc.group_subscribe("ConfigManager", "*", "meonly")
        cc.group_subscribe("Boss", "*", "meonly")

        tool = BigTool(cc)
        cc.group_sendmsg({ "command": ["get_commands"] }, "ConfigManager")
        command_spec, env =  cc.group_recvmsg(False)
        prepare_data(tool, command_spec["result"])
        _prepare_fake_data(tool)   
        tool.cmdloop()
    except ISC.CC.SessionError:
        print("Failed to create cchannel session, "
              "is the command channel daemon running?")


