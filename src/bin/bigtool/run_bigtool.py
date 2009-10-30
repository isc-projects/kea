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
    

if __name__ == '__main__':
    try:
        cc = ISC.CC.Session()
        cc.group_subscribe("BigTool")
        cc.group_subscribe("ConfigManager")
        cc.group_subscribe("Boss")

        tool = BigTool(cc)
        _prepare_fake_data(tool)   
        tool.cmdloop()
    except ISC.CC.SessionError:
        print("Failed to create cchannel session, "
              "is the command channel daemon running?")


