from lettuce import *
import subprocess

@world.absorb
def shutdown_server():
    if world.bind10 is not None:
        world.bind10.terminate()
        world.bind10.wait()
        world.bind10 = None

def check_lines(output, lines):
    for line in lines:
        if output.find(line) != -1:
            return line

@world.absorb
def wait_for_output_lines(lines, examine_past = True):
    assert world.bind10 is not None
    if examine_past:
        for output in world.bind10_output:
            for line in lines:
                if output.find(line) != -1:
                    return line
    found = False
    while not found:
        output = world.bind10.stderr.readline()
        # store any line, for examine_skipped
        world.bind10_output.append(output)
        for line in lines:
            if output.find(line) != -1:
                return line

@step(u'start bind10(?: with configuration ([\w.]+))?')
def start_bind10(step, config_file):
    args = [ 'bind10', '-v' ]
    if config_file is not None:
        args.append('-p')
        args.append("configurations/")
        args.append('-c')
        args.append(config_file)

    world.bind10 = subprocess.Popen(args, 1, None, subprocess.PIPE,
                                    subprocess.PIPE, subprocess.PIPE)
    # check output to know when startup has been completed
    # TODO what to do on failure?
    message = world.wait_for_output_lines(["BIND10_STARTUP_COMPLETE",
                                           "BIND10_STARTUP_ERROR"])
    assert message == "BIND10_STARTUP_COMPLETE"

@step(u'wait for bind10 auth to start')
def wait_for_auth(step):
    world.wait_for_output_lines(['AUTH_SERVER_STARTED'])

@step(u'wait for log message (\w+)')
def wait_for_message(step, message):
    world.wait_for_output_lines([message], False)

@step(u'stop bind10')
def stop_the_server(step):
    world.shutdown_server()

@step(u'set bind10 configuration (\S+) to (.*)')
def set_config_command(step, name, value):
    bindctl = subprocess.Popen(['bindctl'], 1, None, subprocess.PIPE,
                               subprocess.PIPE, None)
    bindctl.stdin.write("config set " + name + " " + value + "\n")
    bindctl.stdin.write("config commit\n")
    bindctl.stdin.write("quit\n")
    result = bindctl.wait()
    assert result == 0, "bindctl exit code: " + str(result)


