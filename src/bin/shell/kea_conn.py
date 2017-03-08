#!/usr/bin/python

# This file contains classes used for communication with Control Agent.

# This class defines the HTTP request to be sent.
# The supported parameters listed are:
# - path (specifies the path on the server, CA uses only /)
# - http_host - hostname of the CA
# - http-port - TCP port of the CA
# - command - specifies the command to send (e.g. list-commands)
# - timeout - timeout (in ms)
# - headers - extra HTTP headers may be added here
# - version - version to be reported in HTTP header
class CARequest:
    path = '/'
    http_host = ''
    http_port = 0
    command = ''
    timeout = 0
    params = ''
    headers = {}
    version = ""

    # Generates the content, out of specified command line
    # and optional content.
    # @todo: Add support for parameters
    # this stores the output in self.content
    def generateBody(self):
        self.content = '{ "command": "' + self.command + '"'
        if (len(self.params)):
            self.content += ', "parameters": { ' + self.params + ' }'
        self.content += ' }'

    # Generate HTTP headers
    #
    # In particular, this method generates Content-Length and its value.
    def generateHeaders(self):
        self.headers['Content-Type'] = 'application/json'
        self.headers['User-Agent'] = "Kea-shell/%s"%(self.version)
        self.headers['Accept'] = '*/*'
        self.headers['Content-Length'] = "%d"%(len(self.content))

    # This is a storage for generated command (input data to be sent over POST)
    content = ''

# This class represents the HTTP response
class CAResponse:

    # Constructor
    #
    # Three mandatory parameters are:
    # status - numerical number the describe the status (e.g. 200 = OK)
    # reason - textual explanation of what happened
    # body - the actual body structure of the response
    def __init__(self, status, reason, body):
        self.status = status
        self.reason = reason
        self.body = body

    status = 0
    reason = ''
    body = ''

    # Used for debugging
    #
    # if defug is true, this prints even more information
    def printResp(self, debug = False):
        if (debug):
            print(self.status)
            print(self.reason)
        print(self.body)
