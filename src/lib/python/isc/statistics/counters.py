# Copyright (C) 2012-2013  Internet Systems Consortium.
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

"""BIND 10 statistics counters module

This module handles the statistics counters for BIND 10 modules.  For
using the module `counter.py`, first a counters object should be created
in each module (like b10-xfrin or b10-xfrout) after importing this
module. A spec file can be specified as an argument when creating the
counters object:

  from isc.statistics import Counters
  self.counters = Counters("/path/to/foo.spec")

The first argument of Counters() can be specified, which is the location
of the specification file (like src/bin/xfrout/xfrout.spec). If Counters
is constructed this way, statistics counters can be accessed from each
module. For example, in case that the item `xfrreqdone` is defined in
statistics_spec in xfrout.spec, the following methods are
callable. Since these methods require the string of the zone name in the
first argument, if we have the following code in b10-xfrout:

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
this module `counter.py` is once imported in a main module such as
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
"""

import threading
import isc.config
from datetime import datetime

# static internal functions
def _add_counter(element, spec, identifier):
    """Returns value of the identifier if the identifier is in the
    element. Otherwise, sets a default value from the spec and
    returns it. If the top-level type of the identifier is named_set
    and the second-level type is map, it sets a set of default values
    under the level and then returns the default value of the
    identifier. This method raises DataNotFoundError if the element is
    invalid for spec."""
    try:
        return isc.cc.data.find(element, identifier)
    except isc.cc.data.DataNotFoundError:
        pass
    # check whether spec and identifier are correct
    isc.config.find_spec_part(spec, identifier)
    # examine spec of the top-level item first
    spec_ = isc.config.find_spec_part(spec, identifier.split('/')[0])
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
    # FIXME: The following statement can be replaced by:
    # sec = delta.total_seconds()
    # but total_seconds() is not available in Python 3.1. Please update
    # this code when we depend on Python 3.2.
    sec = round(delta.days * 86400 + delta.seconds + \
                    delta.microseconds * 1E-6, 6)
    _set_counter(element, spec, identifier, sec)

def _concat(*args, sep='/'):
    """A helper function that is used to generate an identifier for
    statistics item names. It concatenates words in args with a
    separator('/')
    """
    return sep.join(args)

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
          "item_title": "Class name",
          "item_description": "Class name",
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

class Counters():
    """A class for holding and manipulating all statistics counters
    for a module.  A Counters object may be created by specifying a spec
    file of the module in argument.  According to statistics
    specification in the spec file, a counter value can be incremented,
    decremented or obtained. Methods such as inc(), dec() and get() are
    useful for this.  Counters objects also have timer functionality.
    The timer can be started and stopped, and the duration between
    start and stop can be obtained. Methods such as start_timer(),
    stop_timer() and get() are useful for this. Saved counters can be
    cleared by the method clear_all(). Manipulating counters and
    timers can be temporarily disabled.  If disabled, counter values are
    not changed even if methods to update them are invoked.  Including
    per-zone counters, a list of counters which can be handled in the
    class are like the following:

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
        """A constructor for the Counters class. A path to the spec file
        can be specified in spec_file_name. Statistics data based on
        statistics spec can be accumulated if spec_file_name is
        specified. If omitted, a default statistics spec is used. The
        default statistics spec is defined in a hidden class named
        _Statistics().
        """
        self._zones_item_list = []
        self._start_time = {}
        self._disabled = False
        self._rlock = threading.RLock()
        if not spec_file_name: return
        # change the default statistics spec
        self._statistics._spec = \
            isc.config.module_spec_from_file(spec_file_name).\
            get_statistics_spec()
        if self._perzone_prefix in \
                isc.config.spec_name_list(self._statistics._spec):
            self._zones_item_list = isc.config.spec_name_list(
                isc.config.find_spec_part(
                    self._statistics._spec,
                    '%s/%s/%s' % (self._perzone_prefix,
                                  '_CLASS_', self._entire_server)))

    def clear_all(self):
        """clears all statistics data"""
        with self._rlock:
            self._statistics._data = {}

    def disable(self):
        """disables incrementing/decrementing counters"""
        with self._rlock:
            self._disabled = True

    def enable(self):
        """enables incrementing/decrementing counters"""
        with self._rlock:
            self._disabled = False

    def _incdec(self, *args, step=1):
        """A common helper function for incrementing or decrementing a
        counter. It acquires a lock to support multi-threaded
        use. isc.cc.data.DataNotFoundError is raised when incrementing
        the counter of the item undefined in the spec file."""
        identifier = _concat(*args)
        with self._rlock:
            if self._disabled: return
            _inc_counter(self._statistics._data,
                         self._statistics._spec,
                         identifier, step)

    def inc(self, *args):
        """An incrementer for a counter. It acquires a lock to support
        multi-threaded use. isc.cc.data.DataNotFoundError is raised when
        incrementing the counter of the item undefined in the spec file."""
        return self._incdec(*args)

    def dec(self, *args):
        """A decrementer for a counter. It acquires a lock to support
        multi-threaded use. isc.cc.data.DataNotFoundError is raised when
        decrementing the counter of the item undefined in the spec file."""
        return self._incdec(*args, step=-1)

    def get(self, *args):
        """A getter method for counters. It returns the current number
        of the specified counter.  isc.cc.data.DataNotFoundError is
        raised when the counter doesn't have a number yet."""
        identifier = _concat(*args)
        return _get_counter(self._statistics._data, identifier)

    def start_timer(self, *args):
        """Starts a timer which is identified by args and keeps it
        running until stop_timer() is called. It acquires a lock to
        support multi-threaded use. If the specified timer is already
        started but not yet stopped, the last start time is
        overwritten."""
        identifier = _concat(*args)
        with self._rlock:
            if self._disabled: return
            isc.cc.data.set(self._start_time, identifier, _start_timer())

    def stop_timer(self, *args):
        """Stops a timer which is identified by args. It acquires a lock
        to support multi-threaded use. If the timer isn't started by
        start_timer() yet, it raises no exception. However if args
        aren't defined in the spec file, it raises DataNotFoundError.
        """
        identifier = _concat(*args)
        with self._rlock:
            if self._disabled: return
            try:
                start_time = isc.cc.data.find(self._start_time,
                                              identifier)
            except isc.cc.data.DataNotFoundError:
                # do not set the end time if the timer isn't started
                return
            # set the end time
            _stop_timer(
                start_time,
                self._statistics._data,
                self._statistics._spec,
                identifier)
            # A datetime value of once used timer should be deleted
            # for a future use.
            # Here, names of branch and leaf are obtained from a
            # string of identifier. The branch name is equivalent to
            # the position of datetime to be deleted and the leaf name
            # is equivalent to the value of datetime to be deleted.
            (branch, leaf) = identifier.rsplit('/', 1)
            # Then map of branch is obtained from self._start_time by
            # using isc.cc.data.find().
            branch_map = isc.cc.data.find(self._start_time, branch)
            # Finally a value of the leaf name is deleted from the
            # map.
            del branch_map[leaf]

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
        zones_attrs = zones_spec['item_default'][self._entire_server]
        zones_data = {}
        for attr in zones_attrs:
            id_str = '%s/%s' % (self._entire_server, attr)
            sum_ = 0
            for name in zones:
                if attr in zones[name]:
                    sum_ += zones[name][attr]
            _set_counter(zones_data, zones_spec, id_str, sum_)
        # insert entire-server counts
        statistics_data[self._perzone_prefix] = dict(
            statistics_data[self._perzone_prefix],
            **zones_data)
        return statistics_data
