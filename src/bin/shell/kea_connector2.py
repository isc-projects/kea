# Copyright (C) 2017-2021 Internet Systems Consortium, Inc. ("ISC")
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.

"""
This is PYTHON 2.x version of HTTP connection establishment
"""

import httplib

from kea_conn import CAResponse # CARequest

def send_to_control_agent(params):
    """ Sends a request to Control Agent, receives a response and returns it."""

    # No HTTP support.
    if params.scheme == 'https':
        raise NotImplementedError('python2 kea-shell does not support HTTPS')

    # Establish HTTP connection first.
    conn = httplib.HTTPConnection(params.http_host, params.http_port)
    conn.connect()

    # Use POST to send it
    _ = conn.putrequest('POST', params.path)

    # Send the headers first
    for k in params.headers:
        conn.putheader(k, params.headers[k])
    conn.endheaders()

    # Send the body (i.e. the actual content)
    conn.send(params.content)

    # Now get the response
    resp = conn.getresponse()

    # Now get the response details, put it in CAResponse and
    # return it
    result = CAResponse(resp.status, resp.reason, resp.read())
    conn.close()

    return result
