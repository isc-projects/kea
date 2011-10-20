from lettuce import *
import subprocess

def check_lines(output, lines):
    for line in lines:
        if output.find(line) != -1:
            return line

@world.absorb
def wait_for_output_lines_stdout(process_name, lines, examine_past = True):
    assert process_name in world.processes
    if examine_past:
        for output in world.processes_stdout[process_name]:
            for line in lines:
                if output.find(line) != -1:
                    return line
    found = False
    while not found:
        output = world.processes[process_name].stdout.readline()
        # store any line, for examine_skipped
        world.processes_stdout[process_name].append(output)
        for line in lines:
            if output.find(line) != -1:
                return line

@world.absorb
def wait_for_output_lines_stderr(process_name, lines, examine_past = True):
    assert process_name in world.processes,\
        "No process named '" + process_name + "' known"
    if examine_past:
        for output in world.processes_stderr[process_name]:
            for line in lines:
                if output.find(line) != -1:
                    return line
    found = False
    while not found:
        output = world.processes[process_name].stderr.readline()
        # store any line, for examine_skipped
        world.processes_stderr[process_name].append(output)
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

    assert process_name not in world.processes,\
        "There already seems to be a process named " + process_name
    world.processes[process_name] = subprocess.Popen(args, 1, None,
                                                     subprocess.PIPE,
                                                     subprocess.PIPE,
                                                     subprocess.PIPE)
    world.processes_stdout[process_name] = []
    world.processes_stderr[process_name] = []
    # check output to know when startup has been completed
    # TODO what to do on failure?
    message = world.wait_for_output_lines_stderr(process_name,
                                                 ["BIND10_STARTUP_COMPLETE",
                                                  "BIND10_STARTUP_ERROR"])
    assert message == "BIND10_STARTUP_COMPLETE", "Got: " + message

@step('wait for bind10 auth (?:of (\w+) )?to start')
def wait_for_auth(step, process_name):
    if process_name is None:
        process_name = "bind10"
    world.wait_for_output_lines_stderr(process_name, ['AUTH_SERVER_STARTED'])

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


