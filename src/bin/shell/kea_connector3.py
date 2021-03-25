# Copyright (C) 2017-2021 Internet Systems Consortium, Inc. ("ISC")
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.

"""
This is PYTHON 3.x version of HTTP connection establishment
"""

import urllib.request
import ssl
import os

from kea_conn import CAResponse # CARequest

def send_to_control_agent(params):
    """ Sends a request to Control Agent, receives a response and returns it."""

    # First, create the URL
    url = params.scheme + "://" + params.http_host + ":"
    url += str(params.http_port) + str(params.path)

    # Now prepare the request (URL, headers and body)
    req = urllib.request.Request(url=url,
                                 data=str.encode(params.content),
                                 headers=params.headers)

    # Set up the SSL context.
    ssl_ctx = None
    capath = None
    cafile = None
    if params.ca:
        ssl_ctx = ssl.create_default_context(ssl.Purpose.SERVER_AUTH)
        if os.path.isdir(params.ca):
            capath = params.ca
        else:
            cafile = params.ca
        ssl_ctx.load_verify_locations(cafile, capath)
        if params.cert and params.key:
            ssl_ctx.load_cert_chain(params.cert, params.key)

    # Establish connection, send the request.
    resp = urllib.request.urlopen(req, context=ssl_ctx)

    # Now get the response details, put it in CAResponse and return it
    result = CAResponse(resp.getcode(), resp.reason,
                        resp.read().decode("utf-8"))

    return result
