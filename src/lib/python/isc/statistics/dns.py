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

"""BIND 10 statistics counters module for DNS

This module basically inherits the class in isc.statistics.counters.
It handles DNS-specific information. For a DNS purpose, each BIND 10
module uses this module instead of the parent module
(isc.statistics.counters). Also see isc.statistics.counters.__doc__
for details."""

import isc.config
from isc.statistics import counters

class _Statistics():
    """Statistics data set"""
    # default statistics data
    _data = {}
    # default statistics spec used in case the specfile is omitted when
    # constructing a Counters() object
    _spec = [
      {
        "item_name": "zones",
        "item_type": "named_set",
        "item_optional": False,
        "item_default": {
          "_SERVER_" : {
            "notifyoutv4" : 0,
            "notifyoutv6" : 0
          }
        },
        "item_title": "Zone names",
        "item_description": "Zone names",
        "named_set_item_spec": {
          "item_name": "classname",
          "item_type": "named_set",
          "item_optional": False,
          "item_default": {},
          "item_title": "RR class name",
          "item_description": "RR class name",
          "named_set_item_spec": {
            "item_name": "zonename",
            "item_type": "map",
            "item_optional": False,
            "item_default": {},
            "item_title": "Zone name",
            "item_description": "Zone name",
            "map_item_spec": [
              {
                "item_name": "notifyoutv4",
                "item_type": "integer",
                "item_optional": False,
                "item_default": 0,
                "item_title": "IPv4 notifies",
                "item_description": "Number of IPv4 notifies per zone name sent out"
              },
              {
                "item_name": "notifyoutv6",
                "item_type": "integer",
                "item_optional": False,
                "item_default": 0,
                "item_title": "IPv6 notifies",
                "item_description": "Number of IPv6 notifies per zone name sent out"
              }
            ]
          }
        }
      }
    ]

class Counters(counters.Counters):
    """A list of counters which can be handled in the class are like
    the following. Also see counters.Counters.__doc__ for details.

        zones/IN/example.com./notifyoutv4
        zones/IN/example.com./notifyoutv6
        zones/IN/example.com./xfrrej
        zones/IN/example.com./xfrreqdone
        zones/IN/example.com./soaoutv4
        zones/IN/example.com./soaoutv6
        zones/IN/example.com./axfrreqv4
        zones/IN/example.com./axfrreqv6
        zones/IN/example.com./ixfrreqv4
        zones/IN/example.com./ixfrreqv6
        zones/IN/example.com./xfrsuccess
        zones/IN/example.com./xfrfail
        zones/IN/example.com./last_ixfr_duration
        zones/IN/example.com./last_axfr_duration
        ixfr_running
        axfr_running
        socket/unixdomain/open
        socket/unixdomain/openfail
        socket/unixdomain/close
        socket/unixdomain/bindfail
        socket/unixdomain/acceptfail
        socket/unixdomain/accept
        socket/unixdomain/senderr
        socket/unixdomain/recverr
        socket/ipv4/tcp/open
        socket/ipv4/tcp/openfail
        socket/ipv4/tcp/close
        socket/ipv4/tcp/connfail
        socket/ipv4/tcp/conn
        socket/ipv4/tcp/senderr
        socket/ipv4/tcp/recverr
        socket/ipv6/tcp/open
        socket/ipv6/tcp/openfail
        socket/ipv6/tcp/close
        socket/ipv6/tcp/connfail
        socket/ipv6/tcp/conn
        socket/ipv6/tcp/senderr
        socket/ipv6/tcp/recverr
    """
    # '_SERVER_' is a special zone name representing an entire
    # count. It doesn't mean a specific zone, but it means an
    # entire count in the server.
    _entire_server = '_SERVER_'
    # zone names are contained under this dirname in the spec file.
    _perzone_prefix = 'zones'
    # default statistics data set
    _statistics = _Statistics()

    def __init__(self, spec_file_name=None):
        """If the spec file has 'zones', it obtains a list of counter
        names under it when initiating.  For behaviors other than
        this, see isc.statistics.counters.Counters.__init__.__doc__."""
        counters.Counters.__init__(self, spec_file_name)
        if self._perzone_prefix in \
                isc.config.spec_name_list(self._statistics._spec):
            self._zones_item_list = isc.config.spec_name_list(
                isc.config.find_spec_part(
                    self._statistics._spec,
                    '%s/%s/%s' % (self._perzone_prefix,
                                  '_CLASS_', self._entire_server)))

    def get_statistics(self):
        """Calculates an entire server's counts, and returns statistics
        data in a format to send out to the stats module, including each
        counter. If nothing is counted yet, then it returns an empty
        dictionary."""
        # entire copy
        statistics_data = self._statistics._data.copy()
        # If there is no 'zones' found in statistics_data,
        # i.e. statistics_data contains no per-zone counter, it just
        # returns statistics_data because calculating total counts
        # across the zone names isn't necessary.
        if self._perzone_prefix not in statistics_data:
            return statistics_data
        zones = statistics_data[self._perzone_prefix]
        # Start calculation for '_SERVER_' counts
        zones_spec = isc.config.find_spec_part(self._statistics._spec,
                                               self._perzone_prefix)
        zones_data = {}
        for cls in zones.keys():
            for zone in zones[cls].keys():
                for (attr, val) in zones[cls][zone].items():
                    id_str1 = '%s/%s/%s' % (cls, zone, attr)
                    id_str2 = '%s/%s/%s' % (cls, self._entire_server, attr)
                    counters._set_counter(zones_data, zones_spec, id_str1, val)
                    counters._inc_counter(zones_data, zones_spec, id_str2, val)
        # insert entire-server counts
        statistics_data[self._perzone_prefix] = dict(
            statistics_data[self._perzone_prefix],
            **zones_data)
        return statistics_data
