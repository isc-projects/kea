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
in each module like b10-foo after importing this module. A spec file can
be specified as an argument when creating the counters object:

  from isc.statistics import Counters
  self.counters = Counters("/path/to/foo.spec")

The first argument of Counters() can be specified, which is the location
of the specification file. If Counters is constructed this way,
statistics counters can be accessed from each module. For example, in
case that the item `counter1` is defined in statistics_spec in foo.spec,
the following methods are callable.

  self.counters.inc('counter1')

Then the counter for `counter1` is incremented. For getting the current
number of this counter, we can use the following code:

  number = self.counters.get('counter1')

Then the current count is obtained and set in the variable
`number`. Such a getter method would be mainly used for unit-testing.
The decrementer method is also callable.  This method is used for
decrementing a counter as well as inc().

  self.counters.dec('counter2')

Some other methods accessible to a counter are provided by this
module."""

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

    # Note: If there is a named_set type item in the statistics spec
    # and if there are map type items under it, all of items under the
    # map type item need to be added. For example, we're assuming that
    # this method is now adding a counter whose identifier is like
    # dir1/dir2/dir3/counter1. If both of dir1 and dir2 are named_set
    # types, and if dir3 is a map type, and if counter1, counter2, and
    # counter3 are defined as items under dir3 by the statistics spec,
    # this method would add other two counters:
    #
    #   dir1/dir2/dir3/counter2
    #   dir1/dir2/dir3/counter3
    #
    # Otherwise this method just adds the only counter
    # dir1/dir2/dir3/counter1.

    # examine spec from the top-level item and know whether
    # has_named_set, and check whether spec and identifier are correct
    pidr = ''
    has_named_set = False
    for idr in identifier.split('/'):
        if len(pidr) > 0:
            idr = pidr + '/' + idr
        spec_ = isc.config.find_spec_part(spec, idr)
        if isc.config.spec_part_is_named_set(spec_):
            has_named_set = True
            break
        pidr = idr
    # add all elements in map type if has_named_set
    has_map = False
    if has_named_set:
        p_idr = identifier.rsplit('/', 1)[0]
        p_spec = isc.config.find_spec_part(spec, p_idr)
        if isc.config.spec_part_is_map(p_spec):
            has_map = True
            for name in isc.config.spec_name_list(p_spec['map_item_spec']):
                idr_ = p_idr + '/' + name
                spc_ = isc.config.find_spec_part(spec, idr_)
                isc.cc.data.set(element, idr_, spc_['item_default'])
    # otherwise add a specific element
    if not has_map:
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
    """Statistics data set. This class will be remove in the future
    release."""
    # default statistics data
    _data = {}
    # default statistics spec used in case the specfile is omitted when
    # constructing a Counters() object
    _spec = []

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
    not changed even if methods to update them are invoked."""

    # default statistics data set
    _statistics = _Statistics()

    def __init__(self, spec_file_name=None):
        """A constructor for the Counters class. A path to the spec file
        can be specified in spec_file_name. Statistics data based on
        statistics spec can be accumulated if spec_file_name is
        specified. If omitted, a default statistics spec is used. The
        default statistics spec is defined in a hidden class named
        _Statistics(). But the hidden class won't be used and
        spec_file_name will be required in the future release.
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
        """Returns statistics data in a format to send out to the
        stats module, including each counter. If nothing is counted
        yet, then it returns an empty dictionary."""
        # entire copy
        statistics_data = self._statistics._data.copy()
        return statistics_data
