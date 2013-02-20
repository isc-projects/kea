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
# FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT,
# NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION
# WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

import csv
from hashlib import sha1
import imp
import os
import subprocess
import unittest

def run(command):
    """
    Small helper function that returns a tuple of (rcode, stdout, stderr) after
    running the given command (an array of command and arguments, as passed on
    to subprocess).
    """
    subp = subprocess.Popen(command, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
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

    def run_check(self, expected_returncode, expected_stdout, expected_stderr, command):
        """
        Runs the given command, and checks return code, and outputs (if provided).
        Arguments:
        expected_returncode, return code of the command
        expected_stdout, (multiline) string that is checked agains stdout.
                         May be None, in which case the check is skipped.
        expected_stderr, (multiline) string that is checked agains stderr.
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
'''Usage: b10-cmdctl-usermgr [options]

Options:
  --version             show program's version number and exit
  -h, --help            show this help message and exit
  -f OUTPUT_FILE, --file=OUTPUT_FILE
                        Specify the file to append user name and password
  -u USERNAME, --username=USERNAME
                        Specify username to add
  -p PASSWORD, --password=PASSWORD
                        Specify password to add
  -q, --quiet           Quiet mode, don't print any output
''',
                       '',
                       [self.TOOL, '-h'])

    def test_create_users(self):
        """
        Test that a file is created, and users are added.
        Also tests quiet mode for adding a user to an existing file.
        """
        # content is a list of (user, pass) tuples
        expected_content = []

        # Creating a file
        self.run_check(0,
                       'Using accounts file: test_users.csv\n'
                       'User added\n\n',
                       '',
                       [ self.TOOL,
                         '-f', self.OUTPUT_FILE,
                         '-u', 'user1',
                         '-p', 'pass1' ])
        expected_content.append(('user1', 'pass1'))
        self.check_output_file(expected_content)

        # Add to existing file
        self.run_check(0,
                       'Using accounts file: test_users.csv\n'
                       'User added\n\n',
                       '',
                       [ self.TOOL,
                         '-f', self.OUTPUT_FILE,
                         '-u', 'user2',
                         '-p', 'pass2' ])
        expected_content.append(('user2', 'pass2'))
        self.check_output_file(expected_content)

        # Quiet mode
        self.run_check(0,
                       '',
                       '',
                       [ self.TOOL, '-q',
                         '-f', self.OUTPUT_FILE,
                         '-u', 'user3',
                         '-p', 'pass3' ])
        expected_content.append(('user3', 'pass3'))
        self.check_output_file(expected_content)

    def test_default_file(self):
        """
        Check the default file is the correct one.
        Only checks the internal variable, as we don't want to overwrite
        the actual file here
        """
        # Hardcoded path .. should be ok since this is run from make check
        usermgr = imp.load_source('usermgr', '../b10-cmdctl-usermgr.py')
        self.assertEqual('cmdctl-accounts.csv', usermgr.DEFAULT_FILE)

if __name__== '__main__':
    unittest.main()

