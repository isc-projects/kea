# Copyright (C) 2013  Internet Systems Consortium.
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
# FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN COMMAND OF CONTRACT,
# NEGLIGENCE OR OTHER TORTIOUS COMMAND, ARISING OUT OF OR IN CONNECTION
# WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

import csv
from hashlib import sha1
import getpass
import imp
import os
import subprocess
import stat
import sys
import unittest
from bind10_config import SYSCONFPATH

class PrintCatcher:
    def __init__(self):
        self.stdout_lines = []

    def __enter__(self):
        self.__orig_stdout_write = sys.stdout.write
        def new_write(line):
            self.stdout_lines.append(line)

        sys.stdout.write = new_write
        return self

    def __exit__(self, type, value, traceback):
        sys.stdout.write = self.__orig_stdout_write

class OverrideGetpass:
    def __init__(self, new_getpass):
        self.__new_getpass = new_getpass
        self.__orig_getpass = getpass.getpass

    def __enter__(self):
        getpass.getpass = self.__new_getpass
        return self

    def __exit__(self, type, value, traceback):
        getpass.getpass = self.__orig_getpass

# input() is a built-in function and not easily overridable
# so this one uses usermgr for that
class OverrideInput:
    def __init__(self, usermgr, new_getpass):
        self.__usermgr = usermgr
        self.__new_input = new_getpass
        self.__orig_input = usermgr._input

    def __enter__(self):
        self.__usermgr._input = self.__new_input
        return self

    def __exit__(self, type, value, traceback):
        self.__usermgr._input = self.__orig_input

def run(command):
    """
    Small helper function that returns a tuple of (rcode, stdout, stderr)
    after running the given command (an array of command and arguments, as
    passed on to subprocess).
    Parameters:
    command: an array of command and argument strings, which will be
             passed to subprocess.Popen()
    """
    subp = subprocess.Popen(command, stdout=subprocess.PIPE,
                            stderr=subprocess.PIPE)
    (stdout, stderr) = subp.communicate()
    return (subp.returncode, stdout, stderr)

class TestUserMgr(unittest.TestCase):
    TOOL = '../b10-cmdctl-usermgr'
    OUTPUT_FILE = 'test_users.csv'

    def setUp(self):
        self.delete_output_file()
        # For access to the actual module, we load it directly
        self.usermgr_module = imp.load_source('usermgr',
                                              '../b10-cmdctl-usermgr.py')
        # And instantiate 1 instance (with fake options/args)
        self.usermgr = self.usermgr_module.UserManager(object(), object())

    def tearDown(self):
        self.delete_output_file()

    def delete_output_file(self):
        if os.path.exists(self.OUTPUT_FILE):
            os.remove(self.OUTPUT_FILE)

    def check_output_file(self, expected_content):
        self.assertTrue(os.path.exists(self.OUTPUT_FILE))

        csv_entries = []
        with open(self.OUTPUT_FILE, newline='') as csvfile:
            reader = csv.reader(csvfile)
            csv_entries = [row for row in reader]

        self.assertEqual(len(expected_content), len(csv_entries))
        csv_entries.reverse()
        for expected_entry in expected_content:
            expected_name = expected_entry[0]
            expected_pass = expected_entry[1]

            csv_entry = csv_entries.pop()
            entry_name = csv_entry[0]
            entry_salt = csv_entry[2]
            entry_hash = csv_entry[1]

            self.assertEqual(expected_name, entry_name)
            expected_hash =\
                sha1((expected_pass + entry_salt).encode()).hexdigest()
            self.assertEqual(expected_hash, entry_hash)

    def run_check(self, expected_returncode, expected_stdout, expected_stderr,
                  command):
        """
        Runs the given command, and checks return code, and outputs (if provided).
        Arguments:
        expected_returncode, return code of the command
        expected_stdout, (multiline) string that is checked against stdout.
                         May be None, in which case the check is skipped.
        expected_stderr, (multiline) string that is checked against stderr.
                         May be None, in which case the check is skipped.
        """
        (returncode, stdout, stderr) = run(command)
        if expected_stderr is not None:
            self.assertEqual(expected_stderr, stderr.decode())
        if expected_stdout is not None:
            self.assertEqual(expected_stdout, stdout.decode())
        self.assertEqual(expected_returncode, returncode, " ".join(command))

    def test_help(self):
        self.run_check(0,
'''Usage: b10-cmdctl-usermgr [options] <command> [username] [password]

Arguments:
  command		either 'add' or 'delete'
  username		the username to add or delete
  password		the password to set for the added user

If username or password are not specified, b10-cmdctl-usermgr will
prompt for them. It is recommended practice to let the
tool prompt for the password, as command-line
arguments can be visible through history or process
viewers.

Options:
  --version             show program's version number and exit
  -h, --help            show this help message and exit
  -f OUTPUT_FILE, --file=OUTPUT_FILE
                        Accounts file to modify
  -q, --quiet           Quiet mode, don't print any output
''',
                       '',
                       [self.TOOL, '-h'])

    def test_add_delete_users_ok(self):
        """
        Test that a file is created, and users are added.
        Also tests quiet mode for adding a user to an existing file.
        """
        # content is a list of (user, pass) tuples
        expected_content = []

        # Creating a file
        self.run_check(0,
                       'Using accounts file: test_users.csv\n',
                       '',
                       [ self.TOOL,
                         '-f', self.OUTPUT_FILE,
                         'add', 'user1', 'pass1'
                       ])
        expected_content.append(('user1', 'pass1'))
        self.check_output_file(expected_content)

        # Add to existing file
        self.run_check(0,
                       'Using accounts file: test_users.csv\n',
                       '',
                       [ self.TOOL,
                         '-f', self.OUTPUT_FILE,
                         'add', 'user2', 'pass2'
                       ])
        expected_content.append(('user2', 'pass2'))
        self.check_output_file(expected_content)

        # Quiet mode
        self.run_check(0,
                       '',
                       '',
                       [ self.TOOL, '-q',
                         '-f', self.OUTPUT_FILE,
                         'add', 'user3', 'pass3'
                       ])
        expected_content.append(('user3', 'pass3'))
        self.check_output_file(expected_content)

        # Delete a user (let's pick the middle one)
        self.run_check(0,
                       '',
                       '',
                       [ self.TOOL, '-q',
                         '-f', self.OUTPUT_FILE,
                         'delete', 'user2'
                       ])
        del expected_content[1]
        self.check_output_file(expected_content)

    def test_add_delete_users_bad(self):
        """
        More add/delete tests, this time for some error scenarios
        """
        # content is a list of (user, pass) tuples
        expected_content = []
        # First add one
        self.run_check(0, None, None,
                       [ self.TOOL,
                         '-f', self.OUTPUT_FILE,
                         'add', 'user', 'pass'
                       ])
        expected_content.append(('user', 'pass'))
        self.check_output_file(expected_content)

        # Adding it again should error
        self.run_check(3,
                       'Using accounts file: test_users.csv\n'
                       'Error: username exists\n',
                       '',
                       [ self.TOOL,
                         '-f', self.OUTPUT_FILE,
                         'add', 'user', 'pass'
                       ])
        self.check_output_file(expected_content)

        # Deleting a non-existent one should fail too
        self.run_check(4,
                       'Using accounts file: test_users.csv\n'
                       'Error: username does not exist\n',
                       '',
                       [ self.TOOL,
                         '-f', self.OUTPUT_FILE,
                         'delete', 'nosuchuser'
                       ])
        self.check_output_file(expected_content)

    def test_bad_arguments(self):
        """
        Assorted tests with bad command-line arguments
        """
        self.run_check(1,
                       'Error: no command specified\n',
                       '',
                       [ self.TOOL ])
        self.run_check(1,
                       'Error: command must be either add or delete\n',
                       '',
                       [ self.TOOL, 'foo' ])
        self.run_check(1,
                       'Error: extraneous arguments\n',
                       '',
                       [ self.TOOL, 'add', 'user', 'pass', 'toomuch' ])
        self.run_check(1,
                       'Error: delete only needs username, not a password\n',
                       '',
                       [ self.TOOL, 'delete', 'user', 'pass' ])

    def test_default_file(self):
        """
        Check the default file is the correct one.
        """
        # Hardcoded path .. should be ok since this is run from make check
        self.assertEqual(SYSCONFPATH + '/cmdctl-accounts.csv',
                         self.usermgr_module.DEFAULT_FILE)

    def test_prompt_for_password_different(self):
        """
        Check that the method that prompts for a password verifies that
        the same value is entered twice
        """
        # returns a different string (the representation of the number
        # of times it has been called), until it has been called
        # over 10 times, in which case it will always return "11"
        getpass_different_called = 0
        def getpass_different(question):
            nonlocal getpass_different_called
            getpass_different_called += 1
            if getpass_different_called > 10:
                return "11"
            else:
                return str(getpass_different_called)

        with PrintCatcher() as pc:
            with OverrideGetpass(getpass_different):
                pwd = self.usermgr._prompt_for_password()
                self.assertEqual(12, getpass_different_called)
                self.assertEqual("11", pwd)
                # stdout should be 5 times the no match string;
                expected_output = "passwords do not match, try again\n"*5
                self.assertEqual(expected_output, ''.join(pc.stdout_lines))

    def test_prompt_for_password_empty(self):
        """
        Check that the method that prompts for a password verifies that
        the value entered is not empty
        """
        # returns an empty string until it has been called over 10
        # times
        getpass_empty_called = 0
        def getpass_empty(prompt):
            nonlocal getpass_empty_called
            getpass_empty_called += 1
            if getpass_empty_called > 10:
                return "nonempty"
            else:
                return ""

        with PrintCatcher() as pc:
            with OverrideGetpass(getpass_empty):
                pwd = self.usermgr._prompt_for_password()
                self.assertEqual("nonempty", pwd)
                self.assertEqual(12, getpass_empty_called)
                # stdout should be 10 times the 'cannot be empty' string
                expected_output = "Error: password cannot be empty\n"*10
                self.assertEqual(expected_output, ''.join(pc.stdout_lines))

    def test_prompt_for_user(self):
        """
        Test that the method that prompts for a username verifies that
        is not empty, and that it exists (or does not, depending on the
        action that is specified)
        """
        new_input_called = 0
        input_results = [ '', '', 'existinguser', 'nonexistinguser',
                          '', '', 'nonexistinguser', 'existinguser' ]
        def new_input(prompt):
            nonlocal new_input_called

            if new_input_called < len(input_results):
                result = input_results[new_input_called]
            else:
                result = 'empty'
            new_input_called += 1
            return result

        # add fake user (value doesn't matter, method only checks for key)
        self.usermgr.user_info = { 'existinguser': None }

        expected_output = ''

        with PrintCatcher() as pc:
            with OverrideInput(self.usermgr, new_input):
                # should skip the first three since empty or existing
                # are not allowed, then return 'nonexistinguser'
                username = self.usermgr._prompt_for_username(
                                self.usermgr_module.COMMAND_ADD)
                self.assertEqual('nonexistinguser', username)
                expected_output += "Error username can't be empty\n"*2
                expected_output += "user already exists\n"
                self.assertEqual(expected_output, ''.join(pc.stdout_lines))

                # For delete, should again not accept empty (in a while true
                # loop), and this time should not accept nonexisting users
                username = self.usermgr._prompt_for_username(
                                self.usermgr_module.COMMAND_DELETE)
                self.assertEqual('existinguser', username)
                expected_output += "Error username can't be empty\n"*2
                expected_output += "user does not exist\n"
                self.assertEqual(expected_output, ''.join(pc.stdout_lines))

    def test_bad_file(self):
        """
        Check for graceful handling of bad file argument
        """
        self.run_check(2,
                       'Using accounts file: /\n'
                       'Error accessing /: Is a directory\n',
                       '',
                       [ self.TOOL, '-f', '/', 'add', 'user', 'pass' ])

        # Make sure we can initially write to the test file
        self.run_check(0, None, None,
                       [ self.TOOL,
                         '-f', self.OUTPUT_FILE,
                         'add', 'user1', 'pass1'
                       ])

        # Make it non-writable (don't worry about cleanup, the
        # file should be deleted after each test anyway
        os.chmod(self.OUTPUT_FILE, stat.S_IRUSR)
        self.run_check(2,
                       'Using accounts file: test_users.csv\n'
                       'Error accessing test_users.csv: Permission denied\n',
                       '',
                       [ self.TOOL,
                         '-f', self.OUTPUT_FILE,
                         'add', 'user2', 'pass1'
                       ])

        self.run_check(2,
                       'Using accounts file: test_users.csv\n'
                       'Error accessing test_users.csv: Permission denied\n',
                       '',
                       [ self.TOOL,
                         '-f', self.OUTPUT_FILE,
                         'delete', 'user1'
                       ])

        # Making it write-only should have the same effect
        os.chmod(self.OUTPUT_FILE, stat.S_IWUSR)
        self.run_check(2,
                       'Using accounts file: test_users.csv\n'
                       'Error accessing test_users.csv: Permission denied\n',
                       '',
                       [ self.TOOL,
                         '-f', self.OUTPUT_FILE,
                         'add', 'user2', 'pass1'
                       ])

        self.run_check(2,
                       'Using accounts file: test_users.csv\n'
                       'Error accessing test_users.csv: Permission denied\n',
                       '',
                       [ self.TOOL,
                         '-f', self.OUTPUT_FILE,
                         'delete', 'user1'
                       ])

    def test_missing_fields(self):
        """
        Test that an invalid csv file is handled gracefully
        """
        # Valid but incomplete csv; should be handled
        # correctly
        with open(self.OUTPUT_FILE, 'w', newline='') as f:
            f.write('onlyuserfield\n')
            f.write('userfield,saltfield\n')
            f.write(',emptyuserfield,passwordfield\n')

        self.run_check(0, None, None,
                       [ self.TOOL,
                         '-f', self.OUTPUT_FILE,
                         'add', 'user1', 'pass1'
                       ])
        self.run_check(0, None, None,
                       [ self.TOOL,
                         '-f', self.OUTPUT_FILE,
                         'delete', 'onlyuserfield'
                       ])
        self.run_check(0, None, None,
                       [ self.TOOL,
                         '-f', self.OUTPUT_FILE,
                         'delete', ''
                       ])

    def test_bad_data(self):
        # I can only think of one invalid format, an unclosed string
        with open(self.OUTPUT_FILE, 'w', newline='') as f:
            f.write('a,"\n')
        self.run_check(2,
                       'Using accounts file: test_users.csv\n'
                       'Error parsing csv file: newline inside string\n',
                       '',
                       [ self.TOOL,
                         '-f', self.OUTPUT_FILE,
                         'add', 'user1', 'pass1'
                       ])


if __name__== '__main__':
    unittest.main()

