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

import unittest
import subprocess

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
        self.assertEqual(expected_returncode, returncode, " ".join(command))
        if expected_stdout is not None:
            self.assertEqual(expected_stdout, stdout.decode())
        if expected_stderr is not None:
            self.assertEqual(expected_stderr, stderr.decode())

    def test_bad_options(self):
        self.run_check(2,
                       'option -a not recognized\n'
                       'Usage: usermgr [options]\n'
                       '           -h, --help 	 Show this help message and exit\n'
                       '           -f, --file 	 Specify the file to append user name and password\n'
                       '           -v, --version	 Get version number\n'
                       '           \n',
                       '', [self.TOOL, '-a'])


if __name__== '__main__':
    unittest.main()

