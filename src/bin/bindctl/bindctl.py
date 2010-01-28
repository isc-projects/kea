# Copyright (C) 2009  Internet Systems Consortium.
#
# Permission to use, copy, modify, and distribute this software for any
# purpose with or without fee is hereby granted, provided that the above
# copyright notice and this permission notice appear in all copies.
#
# THE SOFTWARE IS PROVIDED "AS IS" AND INTERNET SYSTEMS CONSORTIUM
# DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL
# INTERNET SYSTEMS CONSORTIUM BE LIABLE FOR ANY SPECIAL, DIRECT,
# INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING
# FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT,
# NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION
# WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.


from moduleinfo  import *
from bindcmd import *
import ISC
import pprint


def prepare_config_commands(tool):
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

    tool.add_module_info(module)

if __name__ == '__main__':
    try:
        tool = BindCmdInterpreter("localhost:8080")
        prepare_config_commands(tool)
        tool.run()
    except Exception as e:
        print(e)
        print("Failed to connect with b10-cmdctl module, is it running?")


