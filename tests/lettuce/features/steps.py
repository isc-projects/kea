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

@step('Given I have no database')
def given_i_have_no_database(step):
    if os.path.exists("test.db"):
        os.remove("test.db")

@step('I should see a database file')
def i_should_see_a_database_file(step):
    assert os.path.exists("test.db")
    os.remove("test.db")
