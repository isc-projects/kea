from moduleinfo  import *
from bigtool import *


def _prepare_fake_data(bigtool):
    add_cmd = CommandInfo(name = "add", desc = "add one zone")
    remove_cmd = CommandInfo(name = 'remove', desc = 'remove one zone')
    list_cmd = CommandInfo(name = 'list', desc = 'list all zones', need_inst_param = False)

    zone_module = ModuleInfo(name = "zone", 
                             inst_name = "zone_name", 
                             inst_type = STRING_TYPE, 
                             inst_desc = "the name of one zone",
                             desc = "manage all the zones")

    zone_module.add_command(add_cmd)
    zone_module.add_command(remove_cmd)
    zone_module.add_command(list_cmd)
    bigtool.add_module_info(zone_module)
    

if __name__ == '__main__':
    tool = BigTool()
    _prepare_fake_data(tool)   
    tool.cmdloop()

