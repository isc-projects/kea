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

    This function checks the Auth module configuration to see if it
    servers a given zone via an in-memory data source on top of SQLite3
    data source, and, if so, generate an inter-module command for Auth
    to force it to reload the zone.

    Parameters:
    module_cc (CCSession): a CC session that can get access to auth module
      configuration as a remote configuration
    zone_name (isc.dns.Name): the zone name to be possibly reloaded
    zone_class (isc.dns.RRClass): the RR class of the zone to be possibly
      reloaded.

    Return: a CC command message for the reload if the zone is found;
      otherwise None.

    '''
    # Note: this function was originally a dedicated subroutine of xfrin,
    # but was moved here so it can be shared by some other modules
    # (specifically, by ddns).  It's expected that we'll soon fundamentally
    # revisit the whole data source related configuration, at which point
    # this function should be substantially modified if not completely
    # deprecated (which is a more likely scenario).  For this reason, the
    # corresponding tests were still kept in xfrin.

    datasources, is_default =\
        module_cc.get_remote_config_value(AUTH_MODULE_NAME, "datasources")
    if is_default:
        return None
    for d in datasources:
        if "type" not in d:
            continue
        try:
            if "class" in d:
                dclass = RRClass(d["class"])
            else:
                dclass = RRClass("IN")
        except InvalidRRClass as err:
            logger.info(PYSERVER_COMMON_AUTH_CONFIG_RRCLASS_ERROR, err)
            continue

        if d["type"].lower() == "memory" and dclass == zone_class:
            for zone in d["zones"]:
                if "filetype" not in zone:
                    continue
                if "origin" not in zone:
                    continue
                if "filetype" not in zone:
                    continue
                try:
                    name = Name(zone["origin"])
                except (EmptyLabel, TooLongLabel, BadLabelType, BadEscape,
                        TooLongName, IncompleteName):
                    logger.info(PYSERVER_COMMON_AUTH_CONFIG_NAME_PARSER_ERROR,
                                err)
                    continue

                if zone["filetype"].lower() == "sqlite3" and name == zone_name:
                    param = {"origin": zone_name.to_text(),
                             "class": zone_class.to_text(),
                             "datasrc": d["type"]}
                    return create_command("loadzone", param)
    return None
