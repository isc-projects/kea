#!/usr/bin/python

from kea_conn import CARequest, CAResponse

import urllib.request

class KeaConnector:
    def sendCA(self, params):
        # Estalbish HTTP connection first.
        url = "http://" + params.http_host + ":" + str(params.http_port) + str(params.path)
        
        req = urllib.request.Request(url = url, data = str.encode(params.content),
                                     headers = params.headers)
        resp = urllib.request.urlopen(req)

        # Now get the response details, put it in CAResponse and
        # return it
        x = CAResponse(resp.getcode(), resp.reason, resp.read().decode("utf-8"))

        return (x)
