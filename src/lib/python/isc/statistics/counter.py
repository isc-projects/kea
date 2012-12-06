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

"""BIND 10 Statistics counter module

This module handles the statistics counters for BIND 10 modules.  For
using the module `counter.py`, firstly the init() method should be
invoked in each module like b10-xfrin or b10-xfrout after importing
this module.

  from isc.statistics import Counter
  Counter.init(SPECFILE_LOCATION)

The first argument of Counter.init() is required, which is the
location of the specification file like src/bin/xfrout/xfrout.spec. If
this initial preparation is done, statistics counters can be accessed
from each module. For example, in case that the item `xfrreqdone` is
defined in statistics_spec in xfrout.spec, the following methods can
be dynamically created: Counter.inc_xfrreqdone(),
Counter.get_xfrreqdone(). Since these methods requires the string of
the zone name in the first argument, in the b10-xfrout,

  Counter.inc_xfrreqdone(zone_name)

then the xfrreqdone counter corresponding to zone_name was
incremented. For getting the current number of this counter, we can do
this,

  number = Counter.get_xfrreqdone(zone_name)

then the current number was obtained and set in the above variable
`number`. Such a getter method would be mainly used for unittesting.
In other example, regarding the item `axfr_running`,
the decrementer method is also created:
Counter.dec_axfr_running(). This method is used for decrementing the
counter number.  Regarding the item `axfr_running`, an argument like
zone name is not required.

  Counter.dec_axfr_running()

These accessors are effective in other module. For example, in case
that this module `counter.py` is once imported in such a main module
as b10-xfrout, Regarding the item `notifyoutv4`, the incrementer
inc_notifyoutv4() can be invoked via other module like notify_out.py,
which is firstly imported in the main module.

  Counter.inc_notifyoutv4(zone_name)

In this example this is for incrementing the counter of the item
notifyoutv4. Thus, such statement can be also written in the other
library like isc.notify.notify_out. If this module `counter.py` isn't
imported in the main module but imported in such a library module as
isc.notify.notify_out, in this example, empty methods would be
invoked, which is directly defined in `counter.py`.

Other accessors can be also defined in such individual class in
future. For adding or modifying such accessor, we need to implement in
`counter.py`.
"""
import threading
import isc.config
from datetime import datetime

# static internal functions
def _add_counter(element, spec, identifier):
    """Returns value of the identifier if the identifier is in the
    element. Otherwise, sets a default value from the spec then
    returns it. If the top-level type of the identifier is named_set
    and the second-level type is map, it sets a set of default values
    under the level and then returns the default value of the
    identifier. Raises DataNotFoundError if the element is invalid for
    spec."""
    try:
        return isc.cc.data.find(element, identifier)
    except isc.cc.data.DataNotFoundError:
        pass
    try:
        isc.config.find_spec_part(spec, identifier)
    except isc.cc.data.DataNotFoundError:
        # spec or identifier is wrong
        raise
    # examine spec of the top-level item first
    spec_ = isc.config.find_spec_part(
        spec, '%s' % identifier.split('/')[0])
    if spec_['item_type'] == 'named_set' and \
            spec_['named_set_item_spec']['item_type'] ==  'map':
        map_spec = spec_['named_set_item_spec']['map_item_spec']
        for name in isc.config.spec_name_list(map_spec):
            spec_ = isc.config.find_spec_part(map_spec, name)
            id_str = '%s/%s/%s' % \
                tuple(identifier.split('/')[0:2] + [name])
            isc.cc.data.set(element, id_str, spec_['item_default'])
    else:
        spec_ = isc.config.find_spec_part(spec, identifier)
        isc.cc.data.set(element, identifier, spec_['item_default'])
    return isc.cc.data.find(element, identifier)

def _set_counter(element, spec, identifier, value):
    """Invokes _add_counter() for checking whether the identifier is
    in the element. If not, it creates a new identifier in the element
    and set the default value from the spec. After that, it sets the
    value specified in the arguments."""
    _add_counter(element, spec, identifier)
    isc.cc.data.set(element, identifier, value)

def _get_counter(element, identifier):
    """Returns the value of the identifier in the element"""
    return isc.cc.data.find(element, identifier)

def _inc_counter(element, spec, identifier, step=1):
    """Increments the value of the identifier in the element to the
    step from the current value. If the identifier isn't in the
    element, it creates a new identifier in the element."""
    isc.cc.data.set(element, identifier,
                    _add_counter(element, spec, identifier) + step)

def _start_timer():
    """Returns the current datetime as a datetime object."""
    return datetime.now()

def _stop_timer(start_time, element, spec, identifier):
    """Sets duration time in seconds as a value of the identifier in
    the element, which is in seconds between start_time and the
    current time and is float-type."""
    delta = datetime.now() - start_time
    sec = round(delta.days * 86400 + delta.seconds + \
                    delta.microseconds * 1E-6, 6)
    _set_counter(element, spec, identifier, sec)

class _Counter():
    """A module for holding all statistics counters of modules. The
    counter numbers can be accessed by the accesseers defined
    according to a spec file. In this class, the structure of per-zone
    counters is assumed to be like this:

        zones/example.com./notifyoutv4
        zones/example.com./notifyoutv6
        zones/example.com./xfrrej
        zones/example.com./xfrreqdone
        zones/example.com./soaoutv4
        zones/example.com./soaoutv6
        zones/example.com./axfrreqv4
        zones/example.com./axfrreqv6
        zones/example.com./ixfrreqv4
        zones/example.com./ixfrreqv6
        zones/example.com./xfrsuccess
        zones/example.com./xfrfail
        zones/example.com./time_to_ixfr
        zones/example.com./time_to_axfr
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
        # for exporting to the global scope
        self._to_global = {}
        self._statistics_spec = {}
        self._statistics_data = {}
        self._zones_item_list = []
        self._xfrrunning_names = []
        self._unixsocket_names = []
        self._start_time = {}
        self._disabled = False
        self._rlock = threading.RLock()
        self._module_spec = \
            isc.config.module_spec_from_file(spec_file_name)
        self._statistics_spec = \
            self._module_spec.get_statistics_spec()
        self._parse_stats_spec()
        self._create_perzone_functors()
        self._create_perzone_timer_functors()
        self._create_xfrrunning_functors()
        self._create_unixsocket_functors()
        self._create_ipsocket_functors()
        self._to_global['clear_counters'] = self.clear_counters
        self._to_global['disable'] = self.disable
        self._to_global['enable'] = self.enable
        self._to_global['dump_statistics'] = self.dump_statistics
        if self._perzone_prefix in \
                isc.config.spec_name_list(self._statistics_spec):
            self._zones_item_list = isc.config.spec_name_list(
                isc.config.find_spec_part(
                    self._statistics_spec, self._perzone_prefix)\
                    ['named_set_item_spec']['map_item_spec'])

    def clear_counters(self):
        """clears all statistics data"""
        with self._rlock:
            self._statistics_data = {}

    def disable(self):
        """disables incrementing/decrementing counters"""
        self._disabled = True

    def enable(self):
        """enables incrementing/decrementing counters"""
        self._disabled = False

    def _incrementer(self, identifier, step=1):
        """A per-zone incrementer for counter_name. Locks the
        thread because it is considered to be invoked by a
        multi-threading caller."""
        if self._disabled: return
        with self._rlock:
            _inc_counter(self._statistics_data,
                         self._statistics_spec,
                         identifier, step)

    def _decrementer(self, identifier, step=-1):
        """A decrementer for axfr or ixfr running. Locks the
        thread because it is considered to be invoked by a
        multi-threading caller."""
        self._incrementer(identifier, step)

    def _getter(self, identifier):
        """A getter method for perzone counters"""
        return _get_counter(self._statistics_data, identifier)

    def _starttimer(self, identifier):
        """Sets the value returned from _start_timer() as a value of
        the identifier in the self._start_time which is dict-type"""
        isc.cc.data.set(self._start_time, identifier, _start_timer())

    def _stoptimer(self, identifier):
        """Sets duration time between corresponding time in
        self._start_time and current time into the value of the
        identifier. It deletes corresponding time in self._start_time
        after setting is successfully done. If DataNotFoundError is
        raised while invoking _stop_timer(), it stops setting and
        ignores the exception."""
        try:
            _stop_timer(
                isc.cc.data.find(self._start_time, identifier),
                self._statistics_data,
                self._statistics_spec,
                identifier)
            del isc.cc.data.find(
                self._start_time,
                '/'.join(identifier.split('/')[0:-1]))\
                [identifier.split('/')[-1]]
        except isc.cc.data.DataNotFoundError:
            # do not set end time if it's not started
            pass

    def dump_statistics(self):
        """Calculates an entire server counts, and returns statistics
        data format to send out the stats module including each
        counter. If there is no counts, then it returns an empty
        dictionary."""
        # entire copy
        statistics_data = self._statistics_data.copy()
        # If self.statistics_data contains nothing of zone name, it
        # returns an empty dict.
        if self._perzone_prefix not in statistics_data:
            return statistics_data
        zones = statistics_data[self._perzone_prefix]
        # Start calculation for '_SERVER_' counts
        zones_spec = isc.config.find_spec_part(self._statistics_spec,
                                               self._perzone_prefix)
        zones_attrs = zones_spec['item_default'][self._entire_server]
        zones_data = {}
        for attr in zones_attrs:
            id_str = '%s/%s' % (self._entire_server, attr)
            sum_ = 0
            for name in zones:
                if attr in zones[name]:
                    sum_ += zones[name][attr]
            if  sum_ > 0:
                _set_counter(zones_data, zones_spec,
                             id_str, sum_)
        # insert entire-sever counts
        statistics_data[self._perzone_prefix] = dict(
            statistics_data[self._perzone_prefix],
            **zones_data)
        return statistics_data

