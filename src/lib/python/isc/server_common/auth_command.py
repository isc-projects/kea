# Copyright (C) 2012  Internet Systems Consortium, Inc. ("ISC")
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

'''This module is a utility to create some intermodule command(s) for Auth.'''

from isc.dns import *
import isc.log
from isc.config.ccsession import create_command
from isc.log_messages.server_common_messages import *
from isc.server_common.logger import logger

AUTH_MODULE_NAME = 'Auth'

def auth_loadzone_command(module_cc, zone_name, zone_class):
    '''Create a 'loadzone' command with a given zone for Auth server.

    This function generates an inter-module command for Auth
    to force it to reload the zone.

    Parameters:
    module_cc (CCSession): a CC session that can get access to auth module
      configuration as a remote configuration
    zone_name (isc.dns.Name): the zone name to be possibly reloaded
    zone_class (isc.dns.RRClass): the RR class of the zone to be possibly
      reloaded.

    Return: a CC command message for the reload.
    '''
    # Note: this function was originally a dedicated subroutine of xfrin,
    # but was moved here so it can be shared by some other modules
    # (specifically, by ddns).  It's expected that we'll soon fundamentally
    # revisit the whole data source related configuration, at which point
    # this function should be substantially modified if not completely
    # deprecated (which is a more likely scenario).  For this reason, the
    # corresponding tests were still kept in xfrin.

    # Note: The function got very simplified by #1976. There's plan to move
    # to notification-driven approach, at which point the function would
    # be changed a lot.

    param = {
        "origin": zone_name.to_text(),
        "class": zone_class.to_text()
    }
    return create_command("loadzone", param)
