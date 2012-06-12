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

def run_nsupdate(commands, zone="example.org.", update_address="127.0.0.1",
                 update_port="47806"):
    """Run nsupdate.
       Parameters:
       commands: a sequence of strings which will be sent.
       update_address: adress to send the update to
       update_port: port to send the update to
       zone: zone to update

       Automatically adds the command to set server
       Appends 'send' as a final command.

       nsupdate's stdout and stderr streams are stored (as one multiline string
       in world.last_nsupdate_stdout/stderr.
       Fails if the return code is not 0

    """
    #commands.insert(0, "server " + update_address + " " + update_port)
    #commands.insert(0, "zone " + zone)
    commands.append('send')
    commands.append('quit')
    args = ['nsupdate' ]
    nsupdate = subprocess.Popen(args, 1, None, subprocess.PIPE,
                                subprocess.PIPE, subprocess.PIPE)
    for line in commands:
        nsupdate.stdin.write(line + "\n")
    (stdout, stderr) = nsupdate.communicate()
    world.last_nsupdate_returncode = nsupdate.returncode
    world.last_nsupdate_stdout = stdout
    world.last_nsupdate_stderr = stderr
    #assert result == 0, "nsupdate exit code: " + str(result) +\
    #                    "\nstdout:\n" + str(stdout) +\
    #                    "stderr:\n" + str(stderr)


@step('send a DDNS update for (\S+) with the following commands:')
def send_multiple_commands(step, zone):
    """
    Run nsupdate, and send it the given multiline set of commands.
    A quit command is always appended.
    cmdctl_port ('with cmdctl port <portnr>', optional): cmdctl port to send
                the command to. Defaults to 47805.
    Fails if cmdctl does not exit with status code 0.
    """
    commands = step.multiline.split("\n")
    run_nsupdate(commands, zone)

@step('DDNS response should be ([A-Z]+)')
def check_ddns_response(step, response):
    # For success, nsupdate is silent, only check result code 0
    if response == "SUCCESS":
        assert 0 == world.last_nsupdate_returncode,\
               "nsupdate exit code: " + str(world.last_nsupdate_returncode) +\
               "\nstdout:\n" + str(world.last_nsupdate_stdout) +\
               "stderr:\n" + str(world.last_nsupdate_stderr)
    else:
        found = False
        for line in world.last_nsupdate_stderr.split('\n'):
            if line == "update failed: " + response:
                found = True
        assert found and (2 == world.last_nsupdate_returncode),\
               "Response " + response + " not found in nsupdate output\n" +\
               "nsupdate exit code: " + str(world.last_nsupdate_returncode) +\
               "\nstdout:\n" + str(world.last_nsupdate_stdout) +\
               "stderr:\n" + str(world.last_nsupdate_stderr)


# Individual steps to create a DDNS update packet through nsupdate
@step('Prepare a DDNS update(?: for (\S+))?(?: to (\S+)(?: port ([0-9]+)))?')
def prepare_update(step, zone, server, port):
    '''
    Prepares an nsupdate command that sets up an update to a server
    for a zone. The update is not sent yet, but the commands
    are stored in world.nsupdate_commands
    '''
    commands = []
    if server is not None:
        commands.append("server " + server)
    else:
        commands.append("server 127.0.0.1")
    if port is not None:
        commands[0] = commands[0] + " " + port
    else:
        commands[0] = commands[0] + " 47806"
    if zone is not None:
        commands.append("zone " + zone)
    world.nsupdate_commands = commands

@step('Add to the DDNS update: (.*)')
def add_line_to_ddns_update(step, line):
    world.nsupdate_commands.append(line)

@step('Add the following lines to the DDNS update:')
def add_lines_to_ddns_update(step, line):
    world.nsupdate_commands.extend(step.multiline.split('\n'))

@step('Run the DDNS update')
def run_ddns_update(step):
    '''
    Executes nsupdate as prepared by the previous steps
    '''
    run_nsupdate(world.nsupdate_commands)

@step('use DDNS to set the SOA SERIAL to ([0-9]+)')
def set_serial_to(step, new_serial):
    '''
    Convenience compound step; prepare an update for example.org,
    which sets the SERIAL to the given value
    '''
    step.given('Prepare a DDNS update')
    step.given('add to the DDNS update: update add example.org 3600 IN SOA ns1.example.org. admin.example.org. ' + new_serial + ' 3600 1800 2419200 7200')
    step.given('Run the DDNS update')

@step('Configure BIND10 to run DDNS')
def configure_ddns_on(step):
    step.behave_as("""
    When I send bind10 the following commands
        \"\"\"
        config add Boss/components b10-ddns
        config set Boss/components/b10-ddns/kind dispensable
        config set Boss/components/b10-ddns/address DDNS
        config commit
        \"\"\"
    """)

@step('Configure BIND10 to stop running DDNS')
def configure_ddns_on(step):
    step.behave_as("""
    When I send bind10 the following commands
        \"\"\"
        config remove Boss/components b10-ddns
        config commit
        \"\"\"
    """)

