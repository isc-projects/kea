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

#
# This file contains a number of common steps that are general and may be used
# By a lot of feature files.
#

from lettuce import *
import os

@step('stop process (\w+)')
def stop_a_named_process(step, process_name):
    """
    Stop the process with the given name.
    Parameters:
    process_name ('process <name>'): Name of the process to stop.
    """
    world.processes.stop_process(process_name)

@step('wait for (new )?(\w+) stderr message (\w+)(?: not (\w+))?')
def wait_for_message(step, new, process_name, message, not_message):
    """
    Block until the given message is printed to the given process's stderr
    output.
    Parameter:
    new: (' new', optional): Only check the output printed since last time
                             this step was used for this process.
    process_name ('<name> stderr'): Name of the process to check the output of.
    message ('message <message>'): Output (part) to wait for.
    not_message ('not <message>'): Output (part) to wait for, and fail
    Fails if the message is not found after 10 seconds.
    """
    strings = [message]
    if not_message is not None:
        strings.append(not_message)
    (found, line) = world.processes.wait_for_stderr_str(process_name, strings, new)
    if not_message is not None:
        assert found != not_message, line

@step('wait for (new )?(\w+) stdout message (\w+)(?: not (\w+))?')
def wait_for_message(step, process_name, message, not_message):
    """
    Block until the given message is printed to the given process's stdout
    output.
    Parameter:
    new: (' new', optional): Only check the output printed since last time
                             this step was used for this process.
    process_name ('<name> stderr'): Name of the process to check the output of.
    message ('message <message>'): Output (part) to wait for, and succeed.
    not_message ('not <message>'): Output (part) to wait for, and fail
    Fails if the message is not found after 10 seconds.
    """
    strings = [message]
    if not_message is not None:
        strings.append(not_message)
    (found, line) = world.processes.wait_for_stdout_str(process_name, strings, new)
    if not_message is not None:
        assert found != not_message, line

@step('the file (\S+) should (not )?exist')
def check_existence(step, file_name, should_not_exist):
    """
    Check the existence of the given file.
    Parameters:
    file_name ('file <name>'): File to check existence of.
    should_not_exist ('not', optional): Whether it should or should not exist.
    Fails if the file should exist and does not, or vice versa.
    """
    if should_not_exist is None:
        assert os.path.exists(file_name), file_name + " does not exist"
    else:
        assert not os.path.exists(file_name), file_name + " exists"
