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

This module handles the statistics counters for BIND 10 modules for a
DNS-specific purpose.  For using the module `counter.py`, first a
counters object should be created in each module (like b10-xfrin or
b10-xfrout) after importing this module. A spec file can be specified as
an argument when creating the counters object:

  from isc.statistics.dns import Counters
  self.counters = Counters("/path/to/xfrout/xfrout.spec")

The first argument of Counters() can be specified, which is the location
of the specification file. If Counters is constructed this way,
statistics counters can be accessed from each module. For example, in
case that the item `xfrreqdone` is defined in statistics_spec in
xfrout.spec, the following methods are callable. Since these methods
require the string of the zone name in the first argument, if we have
the following code in b10-xfrout:

  self.counters.inc('zones', zone_name, 'xfrreqdone')

then the counter for xfrreqdone corresponding to zone_name is
incremented. For getting the current number of this counter, we can use
the following code:

  number = self.counters.get('zones', zone_name, 'xfrreqdone')

then the current count is obtained and set in the variable
`number`. Such a getter method would be mainly used for unit-testing.
As other example, for the item `axfr_running`, the decrementer method is
also callable.  This method is used for decrementing a counter.  For the
item `axfr_running`, an argument like zone name is not required:

  self.counters.dec('axfr_running')

These methods are effective in other modules. For example, in case that
this module `counters.py` is once imported in a main module such as
b10-xfrout, then for the item `notifyoutv4`, the `inc()` method can be
invoked in another module such as notify_out.py, which is firstly
imported in the main module.

  self.counters.inc('zones', zone_name, 'notifyoutv4')

In this example this is for incrementing the counter of the item
`notifyoutv4`. Thus, such statement can be also written in another
library like isc.notify.notify_out. If this module `counter.py` isn't
imported in the main module but imported in such a library module as
isc.notify.notify_out, in this example, empty methods would be invoked,
which is directly defined in `counter.py`.

This module basically inherits isc.statistics.counters.  Also see
documentation for isc.statistics.counters for details."""

import isc.config
from isc.statistics import counters

class Counters(counters.Counters):
    """A list of counters which can be handled in the class are like
    the following. Also see documentation for
    isc.statistics.counters.Counters for details.

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

    def __init__(self, spec_file_name):
        """If the item `zones` is defined in the spec file, it obtains a
        list of counter names under it when initiating.  For behaviors
        other than this, see documentation for
        isc.statistics.counters.Counters.__init__()"""
        counters.Counters.__init__(self, spec_file_name)
        if self._perzone_prefix in \
                isc.config.spec_name_list(self._statistics_spec):
            self._zones_item_list = isc.config.spec_name_list(
                isc.config.find_spec_part(
                    self._statistics_spec,
                    '%s/%s/%s' % (self._perzone_prefix,
                                  '_CLASS_', self._entire_server)))

    def get_statistics(self):
        """Calculates an entire server's counts, and returns statistics
        data in a format to send out to the stats module, including each
        counter. If nothing is counted yet, then it returns an empty
        dictionary."""
        # entire copy
        statistics_data = self._statistics_data.copy()
        # If there is no 'zones' found in statistics_data,
        # i.e. statistics_data contains no per-zone counter, it just
        # returns statistics_data because calculating total counts
        # across the zone names isn't necessary.
        if self._perzone_prefix not in statistics_data:
            return statistics_data
        zones = statistics_data[self._perzone_prefix]
        # Start calculation for '_SERVER_' counts
        zones_spec = isc.config.find_spec_part(self._statistics_spec,
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
