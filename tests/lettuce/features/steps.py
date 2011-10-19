from lettuce import *
import subprocess
import os.path
import shutil

copylist = [
["configurations/example.org.config.orig", "configurations/example.org.config"]
]

@before.each_scenario
def initialize(feature):
    # just make sure our cleanup won't fail if we never did
    # run the bind10 instance
    world.bind10 = None
    world.bind10_output = []

    # Some tests can modify the settings. If the tests fail half-way, or
    # don't clean up, this can leave configurations or data in a bad state,
    # so we copy them from originals before each scenario
    for item in copylist:
        shutil.copy(item[0], item[1])

@after.each_scenario
def cleanup(feature):
    world.shutdown_server()
    world.bind10_output = []

@step(u'Given I have no database')
def given_i_have_no_database(step):
    if os.path.exists("test.db"):
        os.remove("test.db")

@step(u'I should see a database file')
def i_should_see_a_database_file(step):
    assert os.path.exists("test.db")
    os.remove("test.db")
