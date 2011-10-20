#
# This is the 'terrain' in which the lettuce lives. By convention, this is
# where global setup and teardown is defined.
#
# We declare some attributes of the global 'world' variables here, so the
# tests can safely assume they are present.
#
# We also use it to provide scenario invariants, such as resetting data.
#
from lettuce import *
import subprocess
import os.path
import shutil

# This is a list of files that are freshly copied before each scenario
# The first element is the original, the second is the target that will be
# used by the tests that need them
copylist = [
["configurations/example.org.config.orig", "configurations/example.org.config"]
]

@before.each_scenario
def initialize(feature):
    # just make sure our cleanup won't fail if we never did
    # run the bind10 instance
    world.processes = {}
    world.processes_stdout = {}
    world.processes_stderr = {}
    world.last_query_result = None

    # Some tests can modify the settings. If the tests fail half-way, or
    # don't clean up, this can leave configurations or data in a bad state,
    # so we copy them from originals before each scenario
    for item in copylist:
        shutil.copy(item[0], item[1])

@after.each_scenario
def cleanup(feature):
    # Stop any running processes we may have had around
    for name in world.processes:
        world.processes[name].terminate()
        world.processes[name].wait()
        world.processes_stdout[name] = []
        world.processes_stderr[name] = []

@world.absorb
def stop_process(process_name):
    if process_name in world.processes:
        p = world.processes[process_name]
        p.terminate()
        p.wait()
        del world.processes[process_name]
