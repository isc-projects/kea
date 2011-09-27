# Copyright (C) 2011  Internet Systems Consortium, Inc. ("ISC")
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

"""
Tests for the bind10.component module
"""

import unittest
import isc.log
import time
from isc.bind10.component import Component

class ComponentTests(unittest.TestCase):
    """
    Tests for the bind10.component.Component class
    """
    def setUp(self):
        """
        Pretend a newly started system
        """
        self.__shutdown = False
        self.__exitcode = None
        self.__start_called = False
        self.__stop_called = False
        self.__failed_called = False
        # Back up the time function, we may want to replace it with something
        self.__orig_time = isc.bind10.component.time.time

    def shutdown(self, exitcode=0):
        """
        Mock function to shut down. We just note we were asked to do so.
        """
        self.__shutdown = True
        self.__exitcode = None
        # Return the original time function
        isc.bind10.component.time.time = self.__orig_time

    def timeskip(self):
        """
        Skip in time to future some 30s. Implemented by replacing the
        time.time function in the tested module with function that returns
        current time increased by 30.
        """
        tm = time.time()
        isc.bind10.component.time.time = lambda: tm + 30

    def start(self):
        """
        Mock function, installed into the component into start_internal.
        This only notes the component was "started".
        """
        self.__start_called = True

    def stop(self):
        """
        Mock function, installed into the component into stop_internal.
        This only notes the component was "stopped".
        """
        self.__stop_called = True

    def fail(self):
        """
        Mock function, installed into the component into failed_internal.
        This only notes the component called the method.
        """
        self.__failed_called = True

    def create_component(self, kind):
        """
        Convenience function that creates a component of given kind
        and installs the mock functions into it so we can hook up into
        its behaviour.

        The process used is some nonsense, as this isn't used in this
        kind of tests and we pretend to be the boss.
        """
        component = Component('No process', self, kind)
        component.start_internal = self.start
        component.stop_internal = self.stop
        component.failed_internal = self.fail
        return component

    def check_startup(self, component):
        """
        Check that nothing was called yet. A newly created component should
        not get started right away, so this should pass after the creation.
        """
        self.assertFalse(self.__shutdown)
        self.assertFalse(self.__start_called)
        self.assertFalse(self.__stop_called)
        self.assertFalse(self.__failed_called)
        self.assertFalse(component.running())
        # We can't stop or fail the component yet
        self.assertRaises(ValueError, component.stop)
        self.assertRaises(ValueError, component.failed)

    def check_started(self, component):
        """
        Check the component was started, but not stopped anyhow yet.
        """
        self.assertFalse(self.__shutdown)
        self.assertTrue(self.__start_called)
        self.assertFalse(self.__stop_called)
        self.assertFalse(self.__failed_called)
        self.assertTrue(component.running())

    def check_dead(self, component):
        """
        Check the component is completely dead, and the server too.
        """
        self.assertTrue(self.__shutdown)
        self.assertTrue(self.__start_called)
        self.assertFalse(self.__stop_called)
        self.assertTrue(self.__failed_called)
        self.assertNotEqual(0, self.__exitcode)
        self.assertFalse(component.running())
        # Surely it can't be stopped again
        self.assertRaises(ValueError, component.stop)
        # Nor started
        self.assertRaises(ValueError, component.start)

    def check_restarted(self, component):
        """
        Check the component restarted successfully.

        Currently, it is implemented as starting it again right away. This will
        change, it will register itself into the restart schedule in boss. But
        as the integration with boss is not clear yet, we don't know how
        exactly that will happen.

        Reset the self.__start_called to False before calling the function when
        the component should fail.
        """
        self.assertFalse(self.__shutdown)
        self.assertTrue(self.__start_called)
        self.assertFalse(self.__stop_called)
        self.assertTrue(self.__failed_called)
        self.assertTrue(component.running())
        # Check it can't be started again
        self.assertRaises(ValueError, component.start)

    def do_start_stop(self, kind):
        """
        This is a body of a test. It creates a componend of given kind,
        then starts it and stops it. It checks correct functions are called
        and the component's status is correct.

        It also checks the component can't be started/stopped twice.
        """
        # Create it and check it did not do any funny stuff yet
        component = self.create_component(kind)
        self.check_startup(component)
        # Start it and check it called the correct starting functions
        component.start()
        self.check_started(component)
        # Check it can't be started twice
        self.assertRaises(ValueError, component.start)
        # Stop it again and check
        component.stop()
        self.assertFalse(self.__shutdown)
        self.assertTrue(self.__start_called)
        self.assertTrue(self.__stop_called)
        self.assertFalse(self.__failed_called)
        self.assertFalse(component.running())
        # Check it can't be stopped twice
        self.assertRaises(ValueError, component.stop)
        # Or failed
        self.assertRaises(ValueError, component.failed)
        # But it can be started again if it is stopped
        # (no more checking here, just it doesn't crash)
        component.start()

    def test_start_stop_core(self):
        """
        A start-stop test for core component. See do_start_stop.
        """
        self.do_start_stop('core')
    def test_start_stop_needed(self):
        """
        A start-stop test for needed component. See do_start_stop.
        """
        self.do_start_stop('needed')
    def test_start_stop_dispensable(self):
        """
        A start-stop test for dispensable component. See do_start_stop.
        """
        self.do_start_stop('dispensable')

    def test_start_fail_core(self):
        """
        Start and then fail a core component. It should stop the whole server.
        """
        # Just ordinary startup
        component = self.create_component('core')
        self.check_startup(component)
        component.start()
        self.check_started(component)
        # Pretend the component died
        component.failed()
        # It should bring down the whole server
        self.check_dead(component)

    def test_start_fail_core_later(self):
        """
        Start and then fail a core component, but let it be running for longer time.
        It should still stop the whole server.
        """
        # Just ordinary startup
        component = self.create_component('core')
        self.check_startup(component)
        component.start()
        self.check_started(component)
        self.timeskip()
        # Pretend the componend died some time later
        component.failed()
        # Check the component is still dead
        self.check_dead(component)

    def test_start_fail_needed(self):
        """
        Start and then fail a needed component. As this happens really soon after
        being started, it is considered failure to start and should bring down the
        whole server.
        """
        # Just ordinary startup
        component = self.create_component('needed')
        self.check_startup(component)
        component.start()
        self.check_started(component)
        # Make it fail right away.
        component.failed()
        self.check_dead(component)

    def test_start_fail_needed_later(self):
        """
        Start and then fail a needed component. But the failure is later on, so
        we just restart it and will be happy.
        """
        # Just ordinary startup
        component = self.create_component('needed')
        self.check_startup(component)
        component.start()
        self.check_started(component)
        # Make it fail later on
        self.__start_called = False
        self.timeskip()
        component.failed()
        self.check_restarted(component)

    def test_start_fail_dispensable(self):
        """
        Start and then fail a dispensable component. Should just get restarted.
        """
        # Just ordinary startup
        component = self.create_component('needed')
        self.check_startup(component)
        component.start()
        self.check_started(component)
        # Make it fail right away
        self.__start_called = False
        component.failed()
        self.check_restarted(component)

    def test_start_fail_dispensable(self):
        """
        Start and then later on fail a dispensable component. Should just get
        restarted.
        """
        # Just ordinary startup
        component = self.create_component('needed')
        self.check_startup(component)
        component.start()
        self.check_started(component)
        # Make it fail later on
        self.__start_called = False
        self.timeskip()
        component.failed()
        self.check_restarted(component)

if __name__ == '__main__':
    isc.log.init("bind10") # FIXME Should this be needed?
    isc.log.resetUnitTestRootLogger()
    unittest.main()
