# Copyright (C) 2017 Internet Systems Consortium, Inc. ("ISC")
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.

"""
This file contains classes used for communication with Control Agent.
"""

class CARequest:
    """
    This class defines the HTTP request to be sent.
    The supported parameters listed are:
     - path (specifies the path on the server, CA uses only /)
     - http_host - hostname of the CA
     - http-port - TCP port of the CA
     - command - specifies the command to send (e.g. list-commands)
     - service - specifies service that is target for the command (e.g. dhcp4)
     - timeout - timeout (in ms)
     - args - extra arguments my be added here
     - headers - extra HTTP headers may be added here
     - version - version to be reported in HTTP header
    """
    path = '/'
    http_host = ''
    http_port = 0
    command = ''
    service = ''
    timeout = 0
    args = ''
    headers = {}
    version = ""
    # This is a storage for generated command (input data to be sent over POST)
    content = ''

    def generate_body(self):
        """
        Generates the content, out of specified command line
        and optional content.
        this stores the output in self.content
        """
        self.content = '{ "command": "' + self.command + '"'
        if self.service is not None:
            self.service = [x for x in self.service if x]
            if len(self.service) > 0:
                self.content += ', "service": ["' +  '","'.join(self.service) + '"]'
        if len(self.args) > 1:
            self.content += ', "arguments": { ' + self.args + ' }'
        self.content += ' }'

    def generate_headers(self):
        """
        Generate HTTP headers

        In particular, this method generates Content-Length and its value.
        """
        self.headers['Content-Type'] = 'application/json'
        self.headers['User-Agent'] = "Kea-shell/%s"%(self.version)
        self.headers['Accept'] = '*/*'
        self.headers['Content-Length'] = "%d"%(len(self.content))


class CAResponse:
    """
    This class represents the HTTP response
    """

    def __init__(self, status, reason, body):
        """
        Constructor

        Three mandatory parameters are:
         status - numerical number the describe the status (e.g. 200 = OK)
         reason - textual explanation of what happened
         body - the actual body structure of the response
        """
        self.status = status
        self.reason = reason
        self.body = body

    status = 0
    reason = ''
    body = ''

    def print_response(self, debug=False):
        """
        Used for debugging

        if debug is true, this prints even more information
        """
        if debug:
            print(self.status)
            print(self.reason)
        print(self.body)
