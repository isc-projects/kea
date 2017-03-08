# Copyright (C) 2017 Internet Systems Consortium, Inc. ("ISC")
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.

import unittest

from kea_conn import CARequest

class CARequestUnitTest(unittest.TestCase):
    """
    This class is dedicated to testing CARequest class. That class
    is responsible for generation of the body and headers.
    """

    def setUp(self):
        """
        This method is called before each test. Currently it does nothing.
        """
        pass

    def test_bodyWithoutParams(self):
        """
        This test verifies if the CARequest object generates the request
        content properly when there are no parameters.
        """

        x = CARequest()
        x.command = "foo"
        x.generateBody()
        self.assertEqual(x.content, '{ "command": "foo" }')

    def test_bodyWithParams(self):
        """
        This test verifies if the CARequest object generates the request
        content properly when there are parameters.
        """

        x = CARequest()
        x.command = "foo"
        x.params = '"bar": "baz"'
        x.generateBody()
        self.assertEqual(x.content, '{ "command": "foo", "parameters": { "bar": "baz" } }')

    def checkHeader(self, headers, header_name, value):
        """
        Checks if headers array contains an entry specified by header_name and that
        its value matches specified value
        """

        if header_name in headers:
            if (headers[header_name] == value):
                return True
            else:
                print ("Expected value: " + value + " does not match actual value: "
                       + headers[header_name])
            return ()
        else:
            print ("Expected header: " + header_name + " missing")
            return (false)

    def test_headers(self):
        """
        This test checks if the headers are generated properly. Note that since
        the content is not specified, it is 0. Therefore Content-Length is 0.
        """
        x = CARequest()
        x.generateHeaders()

        self.assertTrue(self.checkHeader(x.headers, 'Content-Type', 'application/json'))
        self.assertTrue(self.checkHeader(x.headers, 'Accept', '*/*'))
        self.assertTrue(self.checkHeader(x.headers, 'Content-Length', "0"))

    def test_headerLength(self):
        """
        This test checks if the headers are generated properly. In this test there
        is specific content of non-zero length, and its size should be reflected
        in the header.
        """
        x = CARequest()
        x.content = '{ "command": "foo" }'
        x.generateHeaders()

        self.assertTrue(self.checkHeader(x.headers, 'Content-Length', str(len(x.content))))

    def test_headerVersion(self):
        """
        This test checks if the version reported in HTTP headers is generated properly.
        """
        x = CARequest()
        x.version = "1.2.3"
        x.generateHeaders()
        self.assertTrue(self.checkHeader(x.headers, 'User-Agent', 'Kea-shell/1.2.3'))

    def tearDown(self):
        """
        This method is called after each test. Currently it does nothing.
        """
        pass


if __name__ == '__main__':
    unittest.main()
