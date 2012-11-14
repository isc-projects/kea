# Copyright (C) 2012  Internet Systems Consortium.
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

# Note: the main code is in C++, but what we are mostly testing is
# options and behaviour (output/file creation, etc), which is easier
# to test in python.

import unittest
import os
from subprocess import call
import subprocess
import ssl

def run(command):
    """
    Small helper function that returns a tuple of (rcode, stdout, stderr) after
    running the given command (an array of command and arguments, as passed on
    to subprocess).
    """
    subp = subprocess.Popen(command, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    (stdout, stderr) = subp.communicate()
    return (subp.returncode, stdout, stderr)

class FileDeleterContext:
    """
    Simple Context Manager that deletes a given set of files when the context
    is left.
    """
    def __init__(self, files):
        self.files = files

    def __enter__(self):
        pass

    def __exit__(self, type, value, traceback):
        for f in self.files:
            if os.path.exists(f):
                os.unlink(f)

def read_file_data(filename):
    """
    Simple text file reader that returns its contents as an array
    """
    with open(filename) as f:
        return f.readlines()

class TestCertGenTool(unittest.TestCase):
    TOOL = '../b10-certgen'

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

    def validate_certificate(self, expected_result, certfile):
        """
        Validate a certificate, using the quiet option of the tool; it runs
        the check option (-c) for the given base name of the certificate (-f
        <certfile>), and compares the return code to the given
        expected_result value
        """
        self.run_check(expected_result, '', '',
                       [self.TOOL, '-q', '-c', certfile])
        # Same with long options
        self.run_check(expected_result, '', '',
                       [self.TOOL, '--quiet', '--certfile', certfile])


    def test_basic_creation(self):
        """
        Tests whether basic creation with no arguments (except output
        file name) successfully creates a key and certificate
        """
        keyfile = 'test-keyfile.pem'
        certfile = 'test-certfile.pem'
        command = [ self.TOOL, '-q', '-w', '-c', certfile, '-k', keyfile ]
        self.creation_helper(command, certfile, keyfile)
        # Do same with long options
        command = [ self.TOOL, '--quiet', '--write', '--certfile=' + certfile, '--keyfile=' + keyfile ]
        self.creation_helper(command, certfile, keyfile)

    def creation_helper(self, command, certfile, keyfile):
        """
        Helper method for test_basic_creation.
        Performs the actual checks
        """
        with FileDeleterContext([keyfile, certfile]):
            self.assertFalse(os.path.exists(keyfile))
            self.assertFalse(os.path.exists(certfile))
            self.run_check(0, '', '', command)
            self.assertTrue(os.path.exists(keyfile))
            self.assertTrue(os.path.exists(certfile))

            # Validate the certificate that was just created
            self.validate_certificate(0, certfile)

            # When run with the same options, it should *not* create it again,
            # as the current certificate should still be valid
            certdata = read_file_data(certfile)
            keydata = read_file_data(keyfile)

            self.run_check(0, '', '', command)

            self.assertEqual(certdata, read_file_data(certfile))
            self.assertEqual(keydata, read_file_data(keyfile))

            # but if we add -f, it should force a new creation
            command.append('-f')
            self.run_check(0, '', '', command)
            self.assertNotEqual(certdata, read_file_data(certfile))
            self.assertNotEqual(keydata, read_file_data(keyfile))

    def test_check_bad_certificates(self):
        """
        Tests a few pre-created certificates with the -c option
        """
        self.validate_certificate(10, 'testdata/expired-certfile.pem')
        self.validate_certificate(100, 'testdata/mangled-certfile.pem')
        self.validate_certificate(17, 'testdata/noca-certfile.pem')

    def test_bad_options(self):
        """
        Tests some combinations of commands that should fail.
        """
        # specify -c but not -k
        self.run_check(101,
                       'Error: keyfile and certfile must both be specified '
                       'if one of them is when calling b10-certgen in write '
                       'mode.\n',
                       '', [self.TOOL, '-w', '-c', 'foo'])
        self.run_check(101,
                       'Error: keyfile and certfile must both be specified '
                       'if one of them is when calling b10-certgen in write '
                       'mode.\n',
                       '', [self.TOOL, '-w', '-k', 'foo'])
        self.run_check(101,
                       'Error: keyfile is not used when not in write mode\n',
                       '', [self.TOOL, '-k', 'foo'])
        # Extraneous argument
        self.run_check(101, None, None, [self.TOOL, 'foo'])
        # No such file
        self.run_check(105, None, None, [self.TOOL, '-c', 'foo'])

if __name__== '__main__':
    unittest.main()

