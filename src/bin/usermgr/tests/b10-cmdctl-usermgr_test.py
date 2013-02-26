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
import imp
import os
import subprocess
import stat
import unittest
from bind10_config import SYSCONFPATH

def run(command):
    """
    Small helper function that returns a tuple of (rcode, stdout, stderr)
    after running the given command (an array of command and arguments, as
    passed on to subprocess).
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

    def tearDown(self):
        self.delete_output_file()

    def delete_output_file(self):
        if os.path.exists(self.OUTPUT_FILE):
            os.remove(self.OUTPUT_FILE)

    def check_output_file(self, expected_content):
        self.assertTrue(os.path.exists(self.OUTPUT_FILE))

        csv_entries = []
        with open(self.OUTPUT_FILE) as csvfile:
            reader = csv.reader(csvfile)
            for row in reader:
                csv_entries.append(row)

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
prompt for them.

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
        Only checks the internal variable, as we don't want to overwrite
        the actual file here
        """
        # Hardcoded path .. should be ok since this is run from make check
        usermgr = imp.load_source('usermgr', '../b10-cmdctl-usermgr.py')
        self.assertEqual(SYSCONFPATH + '/cmdctl-accounts.csv',
                         usermgr.DEFAULT_FILE)

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


if __name__== '__main__':
    unittest.main()

