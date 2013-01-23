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

from lettuce import *
import urllib

# Basic request
@step('request the URL (.*)')
def request_url(step, url):
    """
    Performs one basic HTTP GET request. The resulting HTTPResponse object
    will we placed in world.last_http_response
    Parameters:
    url: the full URL to query
    """
    world.last_http_response = urllib.urlopen(url)

@step('last http response status code should be ([0-9]+)')
def check_last_response_code(step, code):
    assert world.last_http_response != None, "No HTTP request made yet"
    assert int(code) == world.last_http_response.getcode(),\
                        code + " != " +\
                        str(world.last_http_response.getcode())
