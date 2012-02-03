# Copyright (C) 2011  Internet Systems Consortium.
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

from lettuce import *
import subprocess
import re

@step('start bind10(?: with configuration (\S+))?' +\
      '(?: with cmdctl port (\d+))?' +\
      '(?: with msgq socket file (\S+))?' +\
      '(?: as (\S+))?')
def start_bind10(step, config_file, cmdctl_port, msgq_sockfile, process_name):
    """
    Start BIND 10 with the given optional config file, cmdctl port, and
    store the running process in world with the given process name.
    Parameters:
    config_file ('with configuration <file>', optional): this configuration
                will be used. The path is relative to the base lettuce
                directory.
    cmdctl_port ('with cmdctl port <portnr>', optional): The port on which
                b10-cmdctl listens for bindctl commands. Defaults to 47805.
    msgq_sockfile ('with msgq socket file', optional): The msgq socket file
                that will be used for internal communication
    process_name ('as <name>', optional). This is the name that can be used
                 in the following steps of the scenario to refer to this
                 BIND 10 instance. Defaults to 'bind10'.
    This call will block until BIND10_STARTUP_COMPLETE or BIND10_STARTUP_ERROR
    is logged. In the case of the latter, or if it times out, the step (and
    scenario) will fail.
    It will also fail if there is a running process with the given process_name
    already.
    """
    args = [ 'bind10', '-v' ]
    if config_file is not None:
        args.append('-p')
        args.append("configurations/")
        args.append('-c')
        args.append(config_file)
    if cmdctl_port is None:
        args.append('--cmdctl-port=47805')
    else:
        args.append('--cmdctl-port=' + cmdctl_port)
    if process_name is None:
        process_name = "bind10"
    else:
        args.append('-m')
        args.append(process_name + '_msgq.socket')

    world.processes.add_process(step, process_name, args)

    # check output to know when startup has been completed
    (message, line) = world.processes.wait_for_stderr_str(process_name,
                                                     ["BIND10_STARTUP_COMPLETE",
                                                      "BIND10_STARTUP_ERROR"])
    assert message == "BIND10_STARTUP_COMPLETE", "Got: " + str(line)

@step('wait for bind10 auth (?:of (\w+) )?to start')
def wait_for_auth(step, process_name):
    """Wait for b10-auth to run. This is done by blocking until the message
       AUTH_SERVER_STARTED is logged.
       Parameters:
       process_name ('of <name', optional): The name of the BIND 10 instance
                    to wait for. Defaults to 'bind10'.
    """
    if process_name is None:
        process_name = "bind10"
    world.processes.wait_for_stderr_str(process_name, ['AUTH_SERVER_STARTED'],
                                        False)

@step('wait for bind10 xfrout (?:of (\w+) )?to start')
def wait_for_xfrout(step, process_name):
    """Wait for b10-xfrout to run. This is done by blocking until the message
       XFROUT_NEW_CONFIG_DONE is logged.
       Parameters:
       process_name ('of <name', optional): The name of the BIND 10 instance
                    to wait for. Defaults to 'bind10'.
    """
    if process_name is None:
        process_name = "bind10"
    world.processes.wait_for_stderr_str(process_name,
                                        ['XFROUT_NEW_CONFIG_DONE'],
                                        False)

@step('have bind10 running(?: with configuration ([\S]+))?' +\
      '(?: with cmdctl port (\d+))?' +\
      '(?: as ([\S]+))?')
def have_bind10_running(step, config_file, cmdctl_port, process_name):
    """
    Compound convenience step for running bind10, which consists of
    start_bind10 and wait_for_auth.
    Currently only supports the 'with configuration' option.
    """
    start_step = 'start bind10 with configuration ' + config_file
    wait_step = 'wait for bind10 auth to start'
    if cmdctl_port is not None:
        start_step += ' with cmdctl port ' + str(cmdctl_port)
    if process_name is not None:
        start_step += ' as ' + process_name
        wait_step = 'wait for bind10 auth of ' + process_name + ' to start'
    step.given(start_step)
    step.given(wait_step)

# function to send lines to bindctl, and store the result
def run_bindctl(commands, cmdctl_port=47805):
    """Run bindctl.
       Parameters:
       commands: a sequence of strings which will be sent.
       cmdctl_port: a port number on which cmdctl is listening, is converted
                    to string if necessary. If not provided, or None, defaults
                    to 47805

       bindctl's stdout and stderr streams are stored (as one multiline string
       in world.last_bindctl_stdout/stderr.
       Fails if the return code is not 0
    """
    if cmdctl_port is None:
        cmdctl_port = 47805
    args = ['bindctl', '-p', str(cmdctl_port)]
    bindctl = subprocess.Popen(args, 1, None, subprocess.PIPE,
                               subprocess.PIPE, None)
    for line in commands:
        bindctl.stdin.write(line + "\n")
    (stdout, stderr) = bindctl.communicate()
    result = bindctl.returncode
    world.last_bindctl_stdout = stdout
    world.last_bindctl_stderr = stderr
    assert result == 0, "bindctl exit code: " + str(result) +\
                        "\nstdout:\n" + str(stdout) +\
                        "stderr:\n" + str(stderr)


@step('last bindctl( stderr)? output should( not)? contain (\S+)')
def check_bindctl_output(step, stderr, notv, string):
    """Checks the stdout (or stderr) stream of the last run of bindctl,
       fails if the given string is not found in it (or fails if 'not' was
       set and it is found
       Parameters:
       stderr ('stderr'): Check stderr instead of stdout output
       notv ('not'): reverse the check (fail if string is found)
       string ('contain <string>') string to look for
    """
    if stderr is None:
        output = world.last_bindctl_stdout
    else:
        output = world.last_bindctl_stderr
    found = False
    if string in output:
        found = True
    if notv is None:
        assert found == True, "'" + string +\
                              "' was not found in bindctl output:\n" +\
                              output
    else:
        assert not found, "'" + string +\
                          "' was found in bindctl output:\n" +\
                          output

@step('set bind10 configuration (\S+) to (.*)(?: with cmdctl port (\d+))?')
def config_set_command(step, name, value, cmdctl_port):
    """
    Run bindctl, set the given configuration to the given value, and commit it.
    Parameters:
    name ('configuration <name>'): Identifier of the configuration to set
    value ('to <value>'): value to set it to.
    cmdctl_port ('with cmdctl port <portnr>', optional): cmdctl port to send
                the command to. Defaults to 47805.
    Fails if cmdctl does not exit with status code 0.
    """
    commands = ["config set " + name + " " + value,
                "config commit",
                "quit"]
    run_bindctl(commands, cmdctl_port)

@step('remove bind10 configuration (\S+)(?: value (\S+))?(?: with cmdctl port (\d+))?')
def config_remove_command(step, name, value, cmdctl_port):
    """
    Run bindctl, remove the given configuration item, and commit it.
    Parameters:
    name ('configuration <name>'): Identifier of the configuration to remove
    value ('value <value>'): if name is a named set, use value to identify
                             item to remove
    cmdctl_port ('with cmdctl port <portnr>', optional): cmdctl port to send
                the command to. Defaults to 47805.
    Fails if cmdctl does not exit with status code 0.
    """
    cmd = "config remove " + name
    if value is not None:
        cmd = cmd + " " + value
    commands = [cmd,
                "config commit",
                "quit"]
    run_bindctl(commands, cmdctl_port)

@step('send bind10 the command (.+)(?: with cmdctl port (\d+))?')
def send_command(step, command, cmdctl_port):
    """
    Run bindctl, send the given command, and exit bindctl.
    Parameters:
    command ('the command <command>'): The command to send.
    cmdctl_port ('with cmdctl port <portnr>', optional): cmdctl port to send
                the command to. Defaults to 47805.
    Fails if cmdctl does not exit with status code 0.
    """
    commands = [command,
                "quit"]
    run_bindctl(commands, cmdctl_port)

@step('bind10 module (\S+) should( not)? be running')
def module_is_running(step, name, not_str):
    """
    Convenience step to check if a module is running; can only work with
    default cmdctl port; sends a 'help' command with bindctl, then
    checks if the output contains the given name.
    Parameters:
    name ('module <name>'): The name of the module (case sensitive!)
    not ('not'): Reverse the check (fail if it is running)
    """
    if not_str is None:
        not_str = ""
    step.given('send bind10 the command help')
    step.given('last bindctl output should' + not_str + ' contain ' + name)
