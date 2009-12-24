from moduleinfo  import *
from bigtool import *
import ISC


def _prepare_fake_data(bigtool):
    shutdown_param = ParamInfo(name = "module_name", desc = "the name of module")
    shutdown_cmd = CommandInfo(name = 'shutdown', desc = "stop bind10",
                               need_inst_param = False)
    shutdown_cmd.add_param(shutdown_param)
    boss_module = ModuleInfo(name = "boss", desc = "boss of bind10")
    boss_module.add_command(shutdown_cmd)               

    bigtool.add_module_info(boss_module)

def prepare_commands(bigtool, command_spec):
    for module_name in command_spec.keys():
        bigtool.prepare_module_commands(module_name, command_spec[module_name])

def prepare_config_commands(bigtool):
    module = ModuleInfo(name = "config", desc = "Configuration commands")
    cmd = CommandInfo(name = "show", desc = "Show configuration", need_inst_param = False)
    param = ParamInfo(name = "identifier", type = "string", optional=True)
    cmd.add_param(param)
    module.add_command(cmd)

    cmd = CommandInfo(name = "add", desc = "Add entry to configuration list", need_inst_param = False)
    param = ParamInfo(name = "identifier", type = "string", optional=True)
    cmd.add_param(param)
    param = ParamInfo(name = "value", type = "string", optional=False)
    cmd.add_param(param)
    module.add_command(cmd)

    cmd = CommandInfo(name = "remove", desc = "Remove entry from configuration list", need_inst_param = False)
    param = ParamInfo(name = "identifier", type = "string", optional=True)
    cmd.add_param(param)
    param = ParamInfo(name = "value", type = "string", optional=False)
    cmd.add_param(param)
    module.add_command(cmd)

    cmd = CommandInfo(name = "set", desc = "Set a configuration value", need_inst_param = False)
    param = ParamInfo(name = "identifier", type = "string", optional=True)
    cmd.add_param(param)
    param = ParamInfo(name = "value", type = "string", optional=False)
    cmd.add_param(param)
    module.add_command(cmd)

    cmd = CommandInfo(name = "unset", desc = "Unset a configuration value", need_inst_param = False)
    param = ParamInfo(name = "identifier", type = "string", optional=False)
    cmd.add_param(param)
    module.add_command(cmd)

    cmd = CommandInfo(name = "revert", desc = "Revert all local changes", need_inst_param = False)
    module.add_command(cmd)

    cmd = CommandInfo(name = "commit", desc = "Commit all local changes", need_inst_param = False)
    module.add_command(cmd)

    cmd = CommandInfo(name = "go", desc = "Go to a specific configuration part", need_inst_param = False)
    param = ParamInfo(name = "identifier", type="string", optional=False)
    cmd.add_param(param)
    module.add_command(cmd)

    bigtool.add_module_info(module)
    

if __name__ == '__main__':
    try:
        cc = ISC.CC.Session()
        cc.group_subscribe("BigTool", "*")
        cc.group_subscribe("Boss", "*")

        tool = BigTool(cc)
        cc.group_sendmsg({ "command": ["get_commands"] }, "ConfigManager")
        command_spec, env =  cc.group_recvmsg(False)
        prepare_commands(tool, command_spec["result"][1])
        prepare_config_commands(tool)
        _prepare_fake_data(tool)   
        tool.cmdloop()
    except ISC.CC.SessionError:
        print("Failed to create cchannel session, "
              "is the command channel daemon running?")


