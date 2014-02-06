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

from lettuce import *
import subprocess
import re

def run_nsupdate(commands):
    """Run nsupdate.
       Parameters:
       commands: a sequence of strings which will be sent.
       update_address: address to send the update to
       update_port: port to send the update to
       zone: zone to update

       Appends 'send' and 'quit' as final commands.

       nsupdate's stdout and stderr streams are stored (as one multiline string
       in world.last_nsupdate_stdout/stderr.

       The return code is stored in world.last_nsupdate_returncode
       (it is not checked here, since a number of tests intentionally
       result in a non-zero return code).
    """
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

@step('send a DDNS update for (\S+) with the following commands:')
def send_multiple_commands(step, zone):
    """
    Run nsupdate, and send it the given multiline set of commands.
    A send and quit command is always appended.

    This is the most 'raw' wrapper around the nsupdate call; every
    command except the final send needs to be specified. Intended
    for those tests that have unique properties.
    """
    commands = step.multiline.split("\n")
    run_nsupdate(commands, zone)

@step('DDNS response should be ([A-Z]+)')
def check_ddns_response(step, response):
    """
    Checks the result of the last call to nsupdate.

    If the given response argument is SUCCESS, it simply checks whether
    the return code from nsupdate is 0 (there is no output in that case).
    If not, it checks whether it is not 0, and if the given response string
    matches a line 'update failed: <response>' in the stderr output of
    nsupdate.

    Prints exit code, stdout and stderr streams of nsupdate if it fails.
    """
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
        assert found and (0 != world.last_nsupdate_returncode),\
               "Response " + response + " not found in nsupdate output\n" +\
               "nsupdate exit code: " + str(world.last_nsupdate_returncode) +\
               "\nstdout:\n" + str(world.last_nsupdate_stdout) +\
               "stderr:\n" + str(world.last_nsupdate_stderr)


# Individual steps to create a DDNS update packet through nsupdate
@step('Prepare a DDNS update(?: for (\S+))?(?: to (\S+)(?: port ([0-9]+)))?')
def prepare_update(step, zone, server, port):
    """
    Prepares an nsupdate command that sets up an update to a server
    for a zone. The update is not sent yet, but the commands
    are stored in world.nsupdate_commands.
    """
    commands = []
    if server is not None:
        commands.append("server " + server)
    else:
        commands.append("server 127.0.0.1")
    if port is not None:
        commands[0] = commands[0] + " " + port
    else:
        commands[0] = commands[0] + " 56176"
    if zone is not None:
        commands.append("zone " + zone)
    world.nsupdate_commands = commands

@step('Add to the DDNS update: (.*)')
def add_line_to_ddns_update(step, line):
    """
    Adds a single line to the prepared nsupdate. It is not sent yet.
    The line must conform to nsupdate syntax.
    """
    world.nsupdate_commands.append(line)

@step('Add the following lines to the DDNS update:')
def add_lines_to_ddns_update(step, line):
    """
    Adds multiple lines to the prepared nsupdate. It is not sent yet.
    The lines must conform to nsupdate syntax.
    """
    world.nsupdate_commands.extend(step.multiline.split('\n'))

@step('Send the DDNS update')
def run_ddns_update(step):
    """
    Runs the prepared nsupdate, see run_nsupdate() for more information.
    """
    run_nsupdate(world.nsupdate_commands)

@step('use DDNS to set the SOA SERIAL to ([0-9]+)')
def set_serial_to(step, new_serial):
    """
    Convenience compound step; prepare an update for example.org,
    which sets the SERIAL to the given value, and send it.
    It makes no other changes, and has hardcoded values for the other
    SOA rdata fields.
    """
    step.given('Prepare a DDNS update')
    step.given('add to the DDNS update: update add example.org 3600 IN SOA ns1.example.org. admin.example.org. ' + new_serial + ' 3600 1800 2419200 7200')
    step.given('Send the DDNS update')

@step('use DDNS to add a record (.*)')
def add_record(step, new_record):
    """
    Convenience compound step; prepare an update for example.org,
    which adds one record, then send it.
    Apart from the update addition, the update will not contain anything else.
    """
    step.given('Prepare a DDNS update')
    step.given('add to the DDNS update: update add ' + new_record)
    step.given('Send the DDNS update')

@step('set DDNS ACL ([0-9]+) for ([0-9.]+) to ([A-Z]+)')
def set_ddns_acl_to(step, nr, address, action):
    """
    Convenience step to update a single ACL for DDNS.
    Replaces the ACL at the given index for the given
    address, to the given action
    """
    step.given('set bind10 configuration DDNS/zones[' + nr + ']/update_acl to [{"action": "' + action + '", "from": "' + address + '"}]')
    step.given('last bindctl output should not contain Error')
