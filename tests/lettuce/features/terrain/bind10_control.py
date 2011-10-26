from lettuce import *
import subprocess
import re

def check_lines(output, lines):
    for line in lines:
        if output.find(line) != -1:
            return line

@step('start bind10(?: with configuration (\S+))?' +\
      '(?: with cmdctl port (\d+))?(?: as (\S+))?')
def start_bind10(step, config_file, cmdctl_port, process_name):
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
    # TODO what to do on failure?
    message = world.processes.wait_for_stderr_str(process_name,
                                                  ["BIND10_STARTUP_COMPLETE",
                                                   "BIND10_STARTUP_ERROR"])
    assert message == "BIND10_STARTUP_COMPLETE", "Got: " + str(message)

@step('wait for bind10 auth (?:of (\w+) )?to start')
def wait_for_auth(step, process_name):
    if process_name is None:
        process_name = "bind10"
    world.processes.wait_for_stderr_str(process_name, ['AUTH_SERVER_STARTED'],
                                        False)

@step('have bind10 running(?: with configuration ([\w.]+))?')
def have_bind10_running(step, config_file):
    step.given('start bind10 with configuration ' + config_file)
    step.given('wait for bind10 auth to start')

@step('set bind10 configuration (\S+) to (.*)')
def set_config_command(step, name, value):
    args = ['bindctl', '-p', '47805']
    bindctl = subprocess.Popen(args, 1, None, subprocess.PIPE,
                               subprocess.PIPE, None)
    bindctl.stdin.write("config set " + name + " " + value + "\n")
    bindctl.stdin.write("config commit\n")
    bindctl.stdin.write("quit\n")
    result = bindctl.wait()
    assert result == 0, "bindctl exit code: " + str(result)


