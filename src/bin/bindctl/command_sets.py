# Copyright (C) 2012  Internet Systems Consortium.
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

# This file provides a built-in set of 'execute' commands, for common
# functions, such as adding an initial auth server.
# By calling the function prepare_execute_commands, the
# commands in the command_sets map are added to the virtual
# component called 'execute'. This is done in bindctl_main.

from bindctl.moduleinfo import *
# The name of the 'virtual' command set execution module in bindctl
EXECUTE_MODULE_NAME = 'execute'

# This is a map of command names to lists
# Each element in the set should itself be a dict containing:
# 'description': A string with a description of the command set
# 'commands': A list of bindctl commands
command_sets = {
    'init_authoritative_server': {
        'description':
            'Configure and run a basic Authoritative server, with default '+
            'SQLite3 backend, and xfrin and xfrout functionality',
        'commands':
            [
            '!echo adding Authoritative server component',
            'config add /Init/components b10-auth',
            'config set /Init/components/b10-auth/kind needed',
            'config set /Init/components/b10-auth/special auth',
            '!echo adding Xfrin component',
            'config add /Init/components b10-xfrin',
            'config set /Init/components/b10-xfrin/address Xfrin',
            'config set /Init/components/b10-xfrin/kind dispensable',
            '!echo adding Xfrout component',
            'config add /Init/components b10-xfrout',
            'config set /Init/components/b10-xfrout/address Xfrout',
            'config set /Init/components/b10-xfrout/kind dispensable',
            '!echo adding Zone Manager component',
            'config add /Init/components b10-zonemgr',
            'config set /Init/components/b10-zonemgr/address Zonemgr',
            'config set /Init/components/b10-zonemgr/kind dispensable',
            '!echo Components added. Please enter "config commit" to',
            '!echo finalize initial setup and run the components.'
            ]
    }
}

def has_command_set(name):
    return name in command_sets

def get_commands(name):
    return command_sets[name]['commands']

def get_description(name):
    return command_sets[name]['description']

# For each
def prepare_execute_commands(tool):
    """This function is called by bindctl_main, and sets up the commands
       defined here for use in bindctl."""
    # common parameter
    param_show = ParamInfo(name="show", type="string", optional=True,
        desc="Show the list of commands without executing them")

    # The command module
    module = ModuleInfo(name=EXECUTE_MODULE_NAME,
                        desc="Execute a given set of commands")

    # Command to execute a file
    cmd = CommandInfo(name="file", desc="Read commands from file")
    param = ParamInfo(name="filename", type="string", optional=False,
                      desc="File to read the set of commands from.")
    cmd.add_param(param)
    cmd.add_param(param_show)
    module.add_command(cmd)

    # and loop through all command sets defined above
    for name in command_sets:
        cmd = CommandInfo(name=name, desc=get_description(name))
        cmd.add_param(param_show)
        module.add_command(cmd)

    tool.add_module_info(module)
