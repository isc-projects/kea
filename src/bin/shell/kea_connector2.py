#!/usr/bin/python

# This is PYTHON 2.x version of HTTP connection establishment

from kea_conn import CARequest, CAResponse

import httplib

class KeaConnector:
    def sendCA(self, params):
        # Estalbish HTTP connection first.
        conn = httplib.HTTPConnection(params.http_host, params.http_port)
        conn.connect()

        # Use POST to send it
        request = conn.putrequest('POST', params.path)

        # Send the headers first
        for k in params.headers:
            conn.putheader(k, params.headers[k])
        conn.endheaders()

        # Send the content
        conn.send(params.content)

        # Now get the response
        resp = conn.getresponse()

        # Now get the response details, put it in CAResponse and
        # return it
        x = CAResponse(resp.status, resp.reason, resp.read())
        conn.close()

        return (x)
