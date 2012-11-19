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

'''Statistics counter countainer for modules'''

import threading
import isc.config

_COUNTER = None

def init(spec_file_name):
    """A creator method for a counter class. It creates a counter
    object by the module name of the given spec file. An argument is a
    specification file name."""
    module_spec = isc.config.module_spec_from_file(spec_file_name)
    class_name = '%sCounter' % module_spec.get_module_name()
    global _COUNTER
    _COUNTER = globals()[class_name](module_spec)

# These method are dummies for notify_out in case XfroutCounter is not
# loaded.
def inc_notifyoutv4(self, arg): pass
def inc_notifyoutv6(self, arg): pass

class Counter():
    """A basic counter class for concrete classes"""
    _statistics_spec = {}
    _statistics_data = {}
    _disabled = False
    _rlock = threading.RLock()

    def __init__(self, module_spec):
        self._statistics_spec = module_spec.get_statistics_spec()
        global clear_counters
        global disable
        global enable
        clear_counters = self.clear_counters
        enable = self.enable
        disable = self.disable

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

class XfroutCounter(Counter):
    """A module for holding all statistics counters of Xfrout. The
    counter numbers can be accessed by the accesseers defined
    according to a spec file. In this class, the structure of per-zone
    counters is assumed to be like this:

        zones/example.com./notifyoutv4
        zones/example.com./notifyoutv6
        zones/example.com./xfrrej
        zones/example.com./xfrreqdone
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
    """

    # '_SERVER_' is a special zone name representing an entire
    # count. It doesn't mean a specific zone, but it means an
    # entire count in the server.
    _entire_server = '_SERVER_'
    # zone names are contained under this dirname in the spec file.
    _perzone_prefix = 'zones'
    _xfrrunning_names = []
    _unixsocket_names = []

    def __init__(self, module_spec):
        Counter.__init__(self, module_spec)
        self._xfrrunning_names = [ \
            n for n in \
                isc.config.spec_name_list(self._statistics_spec) \
                if 'xfr_running' in n ]
        self._unixsocket_names = [ \
            n.split('/')[-1] for n in \
                isc.config.spec_name_list(\
                self._statistics_spec, "", True) \
                if n.find('socket/unixdomain/') == 0 ]
        self._create_perzone_functors()
        self._create_xfrrunning_functors()
        self._create_unixsocket_functors()
        global dump_default_statistics
        global dump_statistics
        dump_default_statistics = self.dump_default_statistics
        dump_statistics = self.dump_statistics

    def _create_perzone_functors(self):
        """Creates increment method of each per-zone counter based on
        the spec file. Incrementer can be accessed by name
        "inc_${item_name}".Incrementers are passed to the
        XfroutSession and NotifyOut class as counter handlers."""
        # add a new element under the named_set item for the zone
        zones_spec = isc.config.find_spec_part(
            self._statistics_spec, self._perzone_prefix)
        item_list =  isc.config.spec_name_list(\
            zones_spec['named_set_item_spec']['map_item_spec'])
        # can be accessed by the name 'inc_xxx'
        for item in item_list:
            def __incrementer(zone_name, counter_name=item, step=1):
                """A per-zone incrementer for counter_name. Locks the
                thread because it is considered to be invoked by a
                multi-threading caller."""
                if self._disabled: return
                with self._rlock:
                    self._add_perzone_counter(zone_name)
                    self._statistics_data[self._perzone_prefix]\
                        [zone_name][counter_name] += step
            def __getter(zone_name, counter_name=item):
                """A getter method for perzone counters"""
                return isc.cc.data.find(
                    self._statistics_data,
                    '%s/%s/%s' % ( self._perzone_prefix,
                                   zone_name,
                                   counter_name )
                    )
            globals()['inc_%s' % item] = __incrementer
            globals()['get_%s' % item] = __getter

    def _create_xfrrunning_functors(self):
        """Creates increment/decrement method of (a|i)xfr_running
        based on the spec file. Incrementer can be accessed by name
        "inc_${item_name}". Decrementer can be accessed by name
        "dec_${item_name}". Both of them are passed to the
        XfroutSession as counter handlers."""
        # can be accessed by the name 'inc_xxx' or 'dec_xxx'
        for item in self._xfrrunning_names:
            def __incrementer(counter_name=item, step=1):
                """A incrementer for axfr or ixfr running. Locks the
                thread because it is considered to be invoked by a
                multi-threading caller."""
                if self._disabled: return
                with self._rlock:
                    self._add_xfrrunning_counter(counter_name)
                    self._statistics_data[counter_name] += step
            def __decrementer(counter_name=item, step=-1):
                """A decrementer for axfr or ixfr running. Locks the
                thread because it is considered to be invoked by a
                multi-threading caller."""
                if self._disabled: return
                with self._rlock:
                    self._statistics_data[counter_name] += step
            def __getter(counter_name=item):
                """A getter method for xfr_running counters"""
                return isc.cc.data.find(
                        self._statistics_data, counter_name )
            globals()['inc_%s' % item] = __incrementer
            globals()['dec_%s' % item] = __decrementer
            globals()['get_%s' % item] = __getter

    def _create_unixsocket_functors(self):
        """Creates increment/decrement method of (a|i)xfr_running
        based on the spec file. Incrementer can be accessed by name
        "inc_${item_name}". Decrementer can be accessed by name
        "dec_${item_name}". Both of them are passed to the
        XfroutSession as counter handlers."""
        # can be accessed by the name 'inc_xxx' or 'dec_xxx'
        for item in self._unixsocket_names:
            def __incrementer(counter_name=item, step=1):
                """A incrementer for axfr or ixfr running. Locks the
                thread because it is considered to be invoked by a
                multi-threading caller."""
                if self._disabled: return
                with self._rlock:
                    self._add_unixsocket_counter(counter_name)
                    self._statistics_data['socket']['unixdomain']\
                       [counter_name] += step
            def __getter(counter_name=item):
                """A getter method for unixsockets counters"""
                return isc.cc.data.find(
                    self._statistics_data,
                    'socket/unixdomain/%s' % counter_name )
            globals()['inc_unixsocket_%s' % item] = __incrementer
            globals()['get_unixsocket_%s' % item] = __getter

    def _add_perzone_counter(self, zone):
        """Adds a named_set-type counter for each zone name."""
        try:
            self._statistics_data[self._perzone_prefix][zone]
        except KeyError:
            # add a new element under the named_set item for the zone
            map_spec = isc.config.find_spec_part(
                self._statistics_spec, '%s/%s' % \
                    (self._perzone_prefix, zone))['map_item_spec']
            id_list =  isc.config.spec_name_list(map_spec)
            for id_ in id_list:
                spec = isc.config.find_spec_part(map_spec, id_)
                isc.cc.data.set(self._statistics_data,
                                '%s/%s/%s' % \
                                    (self._perzone_prefix, zone, id_),
                                spec['item_default'])

    def _add_xfrrunning_counter(self, counter_name):
        """Adds a counter for counting (a|i)xfr_running"""
        try:
            self._statistics_data[counter_name]
        except KeyError:
            # examines the names of xfer running
            for n in self._xfrrunning_names:
                spec = isc.config.find_spec_part\
                    (self._statistics_spec, n)
                isc.cc.data.set(self._statistics_data, n, \
                                spec['item_default'])

    def _add_unixsocket_counter(self, counter_name):
        """Adds a counter for counting unix sockets"""
        try:
            self._statistics_data['socket']['unixdomain'][counter_name]
        except KeyError:
            # examines the name of unixsocket
            name = 'socket/unixdomain/%s' % counter_name
            spec = isc.config.find_spec_part\
                (self._statistics_spec, name)
            isc.cc.data.set(self._statistics_data, name, \
                                spec['item_default'])

    def dump_default_statistics(self):
        """Returns default statistics data from the spec file"""
        statistics_data = {}
        for id_ in isc.config.spec_name_list(self._statistics_spec):
            spec = isc.config.find_spec_part(\
                self._statistics_spec, id_)
            if 'item_default' in spec:
                statistics_data.update({id_: spec['item_default']})
        return statistics_data

    def dump_statistics(self):
        """Calculates an entire server counts, and returns statistics
        data format to send out the stats module including each
        counter. If there is no counts, then it returns an empty
        dictionary."""
        # If self.statistics_data contains nothing of zone name, it
        # returns an empty dict.
        if len(self._statistics_data) == 0: return {}
        # for per-zone counter
        zones = self._statistics_data[self._perzone_prefix]
        # Start calculation for '_SERVER_' counts
        attrs = self.dump_default_statistics()\
            [self._perzone_prefix][self._entire_server]
        statistics_data = {self._perzone_prefix: {}}
        for attr in attrs:
            sum_ = 0
            for name in zones:
                if name == self._entire_server: continue
                if attr in zones[name]:
                    if  name not in \
                            statistics_data[self._perzone_prefix]:
                        statistics_data[self._perzone_prefix][name]\
                            = {}
                    statistics_data[self._perzone_prefix][name].\
                        update({attr: zones[name][attr]})
                    sum_ += zones[name][attr]
            if  sum_ > 0:
                if self._entire_server not in \
                        statistics_data[self._perzone_prefix]:
                    statistics_data[self._perzone_prefix][self._entire_server]\
                        = {}
                statistics_data[self._perzone_prefix][self._entire_server]\
                    .update({attr:sum_})

        # for xfrrunning incrementer/decrementer
        for name in self._xfrrunning_names:
            if name in self._statistics_data:
                statistics_data[name] = self._statistics_data[name]

        # for unixsocket incrementer/decrementer
        if 'socket' in self._statistics_data:
            statistics_data['socket'] = \
                self._statistics_data['socket']

        return statistics_data

