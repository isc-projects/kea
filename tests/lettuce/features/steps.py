from lettuce import *
import os

@step('Given I have no database')
def given_i_have_no_database(step):
    if os.path.exists("test.db"):
        os.remove("test.db")

@step('I should see a database file')
def i_should_see_a_database_file(step):
    assert os.path.exists("test.db")
    os.remove("test.db")
