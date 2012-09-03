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

'''Tests for isc.statistics.counter'''

import unittest
import threading
import isc.config
import xfrout

TEST_ZONE_NAME_STR = "example.com."

from isc.statistics import counter

class TestCounter(unittest.TestCase):

    def setUp(self):
        module_spec = isc.config.module_spec_from_file(\
            xfrout.SPECFILE_LOCATION)
        self.counter = counter.Counter(module_spec)

    def test_clear_counters(self):
        self.counter._statistics_data = {'counter': 1}
        self.counter.clear_counters()
        self.assertEqual(self.counter._statistics_data,
                         {})

    def test_enablediable(self):
        self.assertFalse(self.counter._disabled)
        self.counter.disable()
        self.assertTrue(self.counter._disabled)
        self.counter.enable()
        self.assertFalse(self.counter._disabled)

class TestXfroutCounter(unittest.TestCase):
    _number = 3 # number of the threads
    _cycle = 10000 # number of counting per thread

    def setUp(self):
        self._module_spec = isc.config.module_spec_from_file(\
            xfrout.SPECFILE_LOCATION)
        self._statistics_spec = \
            self._module_spec.get_statistics_spec()
        self.xfrout_counter = \
            counter.init(xfrout.SPECFILE_LOCATION)
        self._entire_server    = self.xfrout_counter._entire_server
        self._perzone_prefix   = self.xfrout_counter._perzone_prefix
        self._xfrrunning_names = self.xfrout_counter._xfrrunning_names
        self._unixsocket_names = self.xfrout_counter._unixsocket_names
        self._started = threading.Event()

    def test_dump_default_statistics(self):
        self.assertTrue(\
            self._module_spec.validate_statistics(\
                True,
                counter.dump_default_statistics(),
                )
            )

    def setup_functor(self, incrementer, *args):
        self._started.wait()
        for i in range(self._cycle): incrementer(*args)

    def start_functor(self, incrementer, *args):
        threads = []
        for i in range(self._number):
            threads.append(threading.Thread(\
                    target=self.setup_functor, \
                        args=(incrementer,) + args \
                        ))
        for th in threads: th.start()
        self._started.set()
        for th in threads: th.join()

    def get_count(self, zone_name, counter_name):
        return isc.cc.data.find(\
            counter.dump_statistics(),\
                '%s/%s/%s' % (self._perzone_prefix,\
                                  zone_name, counter_name))

    def test_functors(self):
        # for per-zone counters
        result = { self._entire_server: {},
                   TEST_ZONE_NAME_STR: {} }
        self._perzone_counters = isc.config.spec_name_list(\
            isc.config.find_spec_part(\
                self._statistics_spec, self._perzone_prefix)\
                ['named_set_item_spec']['map_item_spec'])
        for counter_name in self._perzone_counters:
            incrementer = getattr(counter,'inc_%s' % counter_name)
            self.start_functor(incrementer, TEST_ZONE_NAME_STR)
            getter = getattr(counter,'get_%s' % counter_name)
            self.assertEqual(getter(TEST_ZONE_NAME_STR),
                             self._number * self._cycle)
            self.assertEqual(self.get_count(self._entire_server,
                        counter_name), self._number * self._cycle)
            # checks disable/enable
            counter.disable()
            incrementer(TEST_ZONE_NAME_STR)
            self.assertEqual(getter(TEST_ZONE_NAME_STR),
                             self._number * self._cycle)
            counter.enable()
            incrementer(TEST_ZONE_NAME_STR)
            self.assertEqual(getter(TEST_ZONE_NAME_STR),
                             self._number * self._cycle + 1)
            result[self._entire_server][counter_name] = \
                result[TEST_ZONE_NAME_STR][counter_name] = \
                self._number * self._cycle + 1

        statistics_data = {self._perzone_prefix: result}

        # for {a|i}xfrrunning counters
        for counter_name in self._xfrrunning_names:
            incrementer = getattr(counter,'inc_%s' % counter_name)
            self.start_functor(incrementer)
            getter = getattr(counter,'get_%s' % counter_name)
            self.assertEqual(getter(), self._number * self._cycle)
            decrementer = getattr(counter,'dec_%s' % counter_name)
            self.start_functor(decrementer)
            self.assertEqual(getter(), 0)
            # checks disable/enable
            counter.disable()
            incrementer()
            self.assertEqual(getter(), 0)
            counter.enable()
            incrementer()
            self.assertGreater(getter(), 0)
            counter.disable()
            decrementer()
            self.assertGreater(getter(), 0)
            counter.enable()
            decrementer()
            self.assertEqual(getter(), 0)
            statistics_data[counter_name] = 0

        # for unixsocket counters
        statistics_data.update({'socket': {'unixdomain': {}}})
        for counter_name in self._unixsocket_names:
            incrementer = getattr(counter, 'inc_unixsocket_%s' % counter_name)
            self.start_functor(incrementer)
            getter = getattr(counter, 'get_unixsocket_%s' % counter_name)
            self.assertEqual(getter(), self._number * self._cycle)
            # checks disable/enable
            counter.disable()
            incrementer()
            self.assertEqual(getter(), self._number * self._cycle)
            counter.enable()
            incrementer()
            self.assertEqual(getter(), self._number * self._cycle + 1)
            statistics_data['socket']['unixdomain'][counter_name] = \
                self._number * self._cycle + 1

        # totally chacking
        self.assertEqual(counter.dump_statistics(), statistics_data)
        self.assertTrue(self._module_spec.validate_statistics(\
                True, statistics_data))

if __name__== "__main__":
    unittest.main()
