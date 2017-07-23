# Copyright (C) 2017 Internet Systems Consortium, Inc. ("ISC")
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.

"""
This is PYTHON 3.x version of HTTP connection establishment
"""

import urllib.request

from kea_conn import CAResponse # CARequest

def send_to_control_agent(params):
    """ Sends a request to Control Agent, receives a response and returns it."""

    # First, create the URL
    url = "http://" + params.http_host + ":"
    url += str(params.http_port) + str(params.path)

    # Now prepare the request (URL, headers and body)
    req = urllib.request.Request(url=url,
                                 data=str.encode(params.content),
                                 headers=params.headers)

    # Establish connection, send the request.
    resp = urllib.request.urlopen(req)

    # Now get the response details, put it in CAResponse and return it
    result = CAResponse(resp.getcode(), resp.reason,
                        resp.read().decode("utf-8"))

    return result
