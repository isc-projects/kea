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

# Constants representing zone types
ZONE_NOTFOUND = -1              # Zone isn't found in find_zone()
ZONE_PRIMARY = 0                # Primary zone
ZONE_SECONDARY = 1              # Secondary zone

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
    def __init__(self, secondaries):
        self.__secondaries = {}
        for (zname, zclass) in secondaries:
            self.__secondaries[(zname, zclass)] = True

    def find_zone(self, zone_name, zone_class):
        '''Return the type and accessor client object for given zone.'''
        # Right now, the client is not used, so we simply return None.
        if (zone_name, zone_class) in self.__secondaries:
            return ZONE_SECONDARY, None
        return ZONE_PRIMARY, None
