#
# This file contains a number of common steps that are general and may be used
# By a lot of feature files.
#

from lettuce import *
import os

@step('stop process (\w+)')
def stop_a_named_process(step, process_name):
    world.processes.stop_process(process_name)

@step('wait for (new )?(\w+) stderr message (\w+)')
def wait_for_message(step, new, process_name, message):
    world.processes.wait_for_stderr_str(process_name, [message], new)

@step('wait for (new )?(\w+) stdout message (\w+)')
def wait_for_message(step, process_name, message):
    world.processes.wait_for_stdout_str(process_name, [message], new)

@step('the file (\S+) should (not )?exist')
def check_existence(step, file_name, should_not_exist):
    if should_not_exist is None:
        assert os.path.exists(file_name), file_name + " does not exist"
    else:
        assert not os.path.exists(file_name), file_name + " exists"
