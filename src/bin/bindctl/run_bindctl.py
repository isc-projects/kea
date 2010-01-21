from moduleinfo  import *
from bindctl import *
import ISC
import pprint


def prepare_config_commands(bindctl):
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

    bindctl.add_module_info(module)
    
def prepare_boss_command(tool):
    # Prepare the command 'shutdown' for Boss, this is one 'hardcode' exception.
    shutdown_cmd = CommandInfo(name = 'shutdown', desc = "stop one module",
                               need_inst_param = False)
    boss_module = ModuleInfo(name = "Boss", desc = "boss of bind10")
    boss_module.add_command(shutdown_cmd)               
    tool.add_module_info(boss_module)



if __name__ == '__main__':
    try:
        tool = BindCtl("localhost:8080")
        prepare_config_commands(tool)
        prepare_boss_command(tool)
        tool.run()
    except Exception as e:
        print(e)
        print("Failed to connect with cmd-ctrld module, is it running?")


