# Copyright (C) 2012  Internet Systems Consortium.
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

from isc.acl.dns import REQUEST_LOADER
import isc.dns
from isc.datasrc import DataSourceClient

# Constants representing zone types
ZONE_NOTFOUND = -1              # Zone isn't found in find_zone()
ZONE_PRIMARY = 0                # Primary zone
ZONE_SECONDARY = 1              # Secondary zone

# The default ACL if unspecifed on construction of ZoneConfig.
DEFAULT_ACL = REQUEST_LOADER.load([{"action": "REJECT"}])

class ZoneConfig:
    '''A temporary helper class to encapsulate zone related configuration.

    Its find_zone method will search the conceptual configuration for a
    given zone, and return a tuple of zone type (primary or secondary) and
    the client object to access the data source stroing the zone.
    It's very likely that details of zone related configurations like this
    will change in near future, so the main purpose of this class is to
    provide an independent interface for the main DDNS session module
    until the details are fixed.

    '''
    def __init__(self, secondaries, datasrc_class, datasrc_client, acl_map={}):
        '''Constructor.

        Parameters:
        - secondaries: a set of 2-element tuples.  Each element is a pair
          of isc.dns.Name and isc.dns.RRClass, and identifies a single
          secondary zone.
        - datasrc_class: isc.dns.RRClass object.  Specifies the RR class
          of datasrc_client.
        - datasrc_client: isc.dns.DataSourceClient object.  A data source
          class for the RR class of datasrc_class.  It's expected to contain
          a zone that is eventually updated in the ddns package.
        - acl_map: a dictionary that maps a tuple of
          (isc.dns.Name, isc.dns.RRClass) to an isc.dns.dns.RequestACL
          object.  It defines an ACL to be applied to the zone defined
          by the tuple.  If unspecified, or the map is empty, the default
          ACL will be applied to all zones, which is to reject any requests.

        '''
        self.__secondaries = secondaries
        self.__datasrc_class = datasrc_class
        self.__datasrc_client = datasrc_client
        self.__default_acl = DEFAULT_ACL
        self.__acl_map = acl_map

    def find_zone(self, zone_name, zone_class):
        '''Return the type and accessor client object for given zone.'''
        if self.__datasrc_class == zone_class and \
                self.__datasrc_client.find_zone(zone_name)[0] == \
                DataSourceClient.SUCCESS:
            if (zone_name, zone_class) in self.__secondaries:
                return ZONE_SECONDARY, None
            return ZONE_PRIMARY, self.__datasrc_client
        return ZONE_NOTFOUND, None

    def get_update_acl(self, zone_name, zone_class):
        '''Return the update ACL for the given zone.

        This method searches the internally stored ACL map to see if
        there's an ACL to be applied to the given zone.  If found, that
        ACL will be returned; otherwise the default ACL (see the constructor
        description) will be returned.

        Parameters:
        zone_name (isc.dns.Name): The zone name.
        zone_class (isc.dns.RRClass): The zone class.
        '''
        acl = self.__acl_map.get((zone_name, zone_class))
        if acl is not None:
            return acl
        return self.__default_acl

    def set_update_acl_map(self, new_map):
        '''Set a new ACL map.

        This replaces any stored ACL map, either at construction or
        by a previous call to this method, with the given new one.

        Parameter:
        new_map: same as the acl_map parameter of the constructor.

        '''
        self.__acl_map = new_map
