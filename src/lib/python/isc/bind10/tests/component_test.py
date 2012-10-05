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
Tests for the isc.bind10.component module and the
isc.bind10.special_component module.
"""

import unittest
import isc.log
import time
import copy
from isc.bind10.component import Component, Configurator, BaseComponent
import isc.bind10.special_component

class TestError(Exception):
    """
    Just a private exception not known to anybody we use for our tests.
    """
    pass

class BossUtils:
    """
    A class that brings some utilities for pretending we're Boss.
    This is expected to be inherited by the testcases themselves.
    """
    def setUp(self):
        """
        Part of setup. Should be called by descendant's setUp.
        """
        self._shutdown = False
        self._exitcode = None
        # Back up the time function, we may want to replace it with something
        self.__orig_time = isc.bind10.component.time.time

    def tearDown(self):
        """
        Clean up after tests. If the descendant implements a tearDown, it
        should call this method internally.
        """
        # Return the original time function
        isc.bind10.component.time.time = self.__orig_time

    def component_shutdown(self, exitcode=0):
        """
        Mock function to shut down. We just note we were asked to do so.
        """
        self._shutdown = True
        self._exitcode = exitcode

    def _timeskip(self):
        """
        Skip in time to future some 30s. Implemented by replacing the
        time.time function in the tested module with function that returns
        current time increased by 30.
        """
        tm = time.time()
        isc.bind10.component.time.time = lambda: tm + 30

    # Few functions that pretend to start something. Part of pretending of
    # being boss.
    def start_msgq(self):
        pass

    def start_cfgmgr(self):
        pass

    def start_auth(self):
        pass

    def start_resolver(self):
        pass

    def start_cmdctl(self):
        pass

class ComponentTests(BossUtils, unittest.TestCase):
    """
    Tests for the bind10.component.Component class
    """
    def setUp(self):
        """
        Pretend a newly started system.
        """
        BossUtils.setUp(self)
        self._shutdown = False
        self._exitcode = None
        self.__start_called = False
        self.__stop_called = False
        self.__failed_called = False
        self.__registered_processes = {}
        self.__stop_process_params = None
        self.__start_simple_params = None
        # Pretending to be boss
        self.gid = None
        self.__gid_set = None
        self.uid = None
        self.__uid_set = None

    def __start(self):
        """
        Mock function, installed into the component into _start_internal.
        This only notes the component was "started".
        """
        self.__start_called = True

    def __stop(self):
        """
        Mock function, installed into the component into _stop_internal.
        This only notes the component was "stopped".
        """
        self.__stop_called = True

    def __fail(self):
        """
        Mock function, installed into the component into _failed_internal.
        This only notes the component called the method.
        """
        self.__failed_called = True

    def __fail_to_start(self):
        """
        Mock function. It can be installed into the component's _start_internal
        to simulate a component that fails to start by raising an exception.
        """
        orig_started = self.__start_called
        self.__start_called = True
        if not orig_started:
            # This one is from restart. Avoid infinite recursion for now.
            # FIXME: We should use the restart scheduler to avoid it, not this.
            raise TestError("Test error")

    def __create_component(self, kind):
        """
        Convenience function that creates a component of given kind
        and installs the mock functions into it so we can hook up into
        its behaviour.

        The process used is some nonsense, as this isn't used in this
        kind of tests and we pretend to be the boss.
        """
        component = Component('No process', self, kind, 'homeless', [])
        component._start_internal = self.__start
        component._stop_internal = self.__stop
        component._failed_internal = self.__fail
        return component

    def test_name(self):
        """
        Test the name provides whatever we passed to the constructor as process.
        """
        component = self.__create_component('core')
        self.assertEqual('No process', component.name())

    def test_address(self):
        """
        Test the address provides whatever we passed to the constructor as process.
        """
        component = self.__create_component('core')
        self.assertEqual("homeless", component.address())

    def test_guts(self):
        """
        Test the correct data are stored inside the component.
        """
        component = self.__create_component('core')
        self.assertEqual(self, component._boss)
        self.assertEqual("No process", component._process)
        self.assertEqual(None, component._start_func)
        self.assertEqual("homeless", component._address)
        self.assertEqual([], component._params)

    def __check_startup(self, component):
        """
        Check that nothing was called yet. A newly created component should
        not get started right away, so this should pass after the creation.
        """
        self.assertFalse(self._shutdown)
        self.assertFalse(self.__start_called)
        self.assertFalse(self.__stop_called)
        self.assertFalse(self.__failed_called)
        self.assertFalse(component.running())
        self.assertFalse(component.is_failed())
        # We can't stop or fail the component yet
        self.assertRaises(ValueError, component.stop)
        self.assertRaises(ValueError, component.failed, 1)

    def __check_started(self, component):
        """
        Check the component was started, but not stopped anyhow yet.
        """
        self.assertFalse(self._shutdown)
        self.assertTrue(self.__start_called)
        self.assertFalse(self.__stop_called)
        self.assertFalse(self.__failed_called)
        self.assertTrue(component.running())
        self.assertFalse(component.is_failed())

    def __check_dead(self, component):
        """
        Check the component is completely dead, and the server too.
        """
        self.assertTrue(self._shutdown)
        self.assertTrue(self.__start_called)
        self.assertFalse(self.__stop_called)
        self.assertTrue(self.__failed_called)
        self.assertEqual(1, self._exitcode)
        self.assertFalse(component.running())
        self.assertFalse(component.is_failed())
        # Surely it can't be stopped when already dead
        self.assertRaises(ValueError, component.stop)
        # Nor started
        self.assertRaises(ValueError, component.start)
        # Nor it can fail again
        self.assertRaises(ValueError, component.failed, 1)

    def __check_restarted(self, component):
        """
        Check the component restarted successfully.

        Reset the self.__start_called to False before calling the function when
        the component should fail.
        """
        self.assertFalse(self._shutdown)
        self.assertTrue(self.__start_called)
        self.assertFalse(self.__stop_called)
        self.assertTrue(self.__failed_called)
        self.assertTrue(component.running())
        self.assertFalse(component.is_failed())
        # Check it can't be started again
        self.assertRaises(ValueError, component.start)

    def __check_not_restarted(self, component):
        """
        Check the component has not (yet) restarted successfully.
        """
        self.assertFalse(self._shutdown)
        self.assertTrue(self.__start_called)
        self.assertFalse(self.__stop_called)
        self.assertTrue(self.__failed_called)
        self.assertFalse(component.running())
        self.assertTrue(component.is_failed())

    def __do_start_stop(self, kind):
        """
        This is a body of a test. It creates a component of given kind,
        then starts it and stops it. It checks correct functions are called
        and the component's status is correct.

        It also checks the component can't be started/stopped twice.
        """
        # Create it and check it did not do any funny stuff yet
        component = self.__create_component(kind)
        self.__check_startup(component)
        # Start it and check it called the correct starting functions
        component.start()
        self.__check_started(component)
        # Check it can't be started twice
        self.assertRaises(ValueError, component.start)
        # Stop it again and check
        component.stop()
        self.assertFalse(self._shutdown)
        self.assertTrue(self.__start_called)
        self.assertTrue(self.__stop_called)
        self.assertFalse(self.__failed_called)
        self.assertFalse(component.running())
        self.assertFalse(component.is_failed())
        # Check it can't be stopped twice
        self.assertRaises(ValueError, component.stop)
        # Or failed
        self.assertRaises(ValueError, component.failed, 1)
        # But it can be started again if it is stopped
        # (no more checking here, just it doesn't crash)
        component.start()

    def test_start_stop_core(self):
        """
        A start-stop test for core component. See do_start_stop.
        """
        self.__do_start_stop('core')

    def test_start_stop_needed(self):
        """
        A start-stop test for needed component. See do_start_stop.
        """
        self.__do_start_stop('needed')

    def test_start_stop_dispensable(self):
        """
        A start-stop test for dispensable component. See do_start_stop.
        """
        self.__do_start_stop('dispensable')

    def test_start_fail_core(self):
        """
        Start and then fail a core component. It should stop the whole server.
        """
        # Just ordinary startup
        component = self.__create_component('core')
        self.__check_startup(component)
        component.start()
        self.__check_started(component)
        # Pretend the component died
        restarted = component.failed(1)
        # Since it is a core component, it should not be restarted
        self.assertFalse(restarted)
        # It should bring down the whole server
        self.__check_dead(component)

    def test_start_fail_core_later(self):
        """
        Start and then fail a core component, but let it be running for longer time.
        It should still stop the whole server.
        """
        # Just ordinary startup
        component = self.__create_component('core')
        self.__check_startup(component)
        component.start()
        self.__check_started(component)
        self._timeskip()
        # Pretend the component died some time later
        restarted = component.failed(1)
        # Should not be restarted
        self.assertFalse(restarted)
        # Check the component is still dead
        self.__check_dead(component)

    def test_start_fail_needed(self):
        """
        Start and then fail a needed component. As this happens really soon after
        being started, it is considered failure to start and should bring down the
        whole server.
        """
        # Just ordinary startup
        component = self.__create_component('needed')
        self.__check_startup(component)
        component.start()
        self.__check_started(component)
        # Make it fail right away.
        restarted = component.failed(1)
        # Should not have restarted
        self.assertFalse(restarted)
        self.__check_dead(component)

    def test_start_fail_needed_later(self):
        """
        Start and then fail a needed component. But the failure is later on, so
        we just restart it and will be happy.
        """
        # Just ordinary startup
        component = self.__create_component('needed')
        self.__check_startup(component)
        component.start()
        self.__check_started(component)
        # Make it fail later on
        self.__start_called = False
        self._timeskip()
        restarted = component.failed(1)
        # Should have restarted
        self.assertTrue(restarted)
        self.__check_restarted(component)

    def test_start_fail_dispensable(self):
        """
        Start and then fail a dispensable component. Should not get restarted.
        """
        # Just ordinary startup
        component = self.__create_component('dispensable')
        self.__check_startup(component)
        component.start()
        self.__check_started(component)
        # Make it fail right away
        restarted = component.failed(1)
        # Should signal that it did not restart
        self.assertFalse(restarted)
        self.__check_not_restarted(component)

    def test_start_fail_dispensable_later(self):
        """
        Start and then later on fail a dispensable component. Should just get
        restarted.
        """
        # Just ordinary startup
        component = self.__create_component('dispensable')
        self.__check_startup(component)
        component.start()
        self.__check_started(component)
        # Make it fail later on
        self._timeskip()
        restarted = component.failed(1)
        # should signal that it restarted
        self.assertTrue(restarted)
        # and check if it really did
        self.__check_restarted(component)

    def test_start_fail_dispensable_restart_later(self):
        """
        Start and then fail a dispensable component, wait a bit and try to
        restart. Should get restarted after the wait.
        """
        # Just ordinary startup
        component = self.__create_component('dispensable')
        self.__check_startup(component)
        component.start()
        self.__check_started(component)
        # Make it fail immediately
        restarted = component.failed(1)
        # should signal that it did not restart
        self.assertFalse(restarted)
        self.__check_not_restarted(component)
        self._timeskip()
        # try to restart again
        restarted = component.restart()
        # should signal that it restarted
        self.assertTrue(restarted)
        # and check if it really did
        self.__check_restarted(component)

    def test_fail_core(self):
        """
        Failure to start a core component. Should bring the system down
        and the exception should get through.
        """
        component = self.__create_component('core')
        self.__check_startup(component)
        component._start_internal = self.__fail_to_start
        self.assertRaises(TestError, component.start)
        self.__check_dead(component)

    def test_fail_needed(self):
        """
        Failure to start a needed component. Should bring the system down
        and the exception should get through.
        """
        component = self.__create_component('needed')
        self.__check_startup(component)
        component._start_internal = self.__fail_to_start
        self.assertRaises(TestError, component.start)
        self.__check_dead(component)

    def test_fail_dispensable(self):
        """
        Failure to start a dispensable component. The exception should get
        through, but it should be restarted after a time skip.
        """
        component = self.__create_component('dispensable')
        self.__check_startup(component)
        component._start_internal = self.__fail_to_start
        self.assertRaises(TestError, component.start)
        # tell it to see if it must restart
        restarted = component.restart()
        # should not have restarted yet
        self.assertFalse(restarted)
        self.__check_not_restarted(component)
        self._timeskip()
        # tell it to see if it must restart and do so, with our vision of time
        restarted = component.restart()
        # should have restarted now
        self.assertTrue(restarted)
        self.__check_restarted(component)

    def test_component_start_time(self):
        """
        Check that original start time is set initially, and remains the same
        after a restart, while the internal __start_time does change
        """
        # Just ordinary startup
        component = self.__create_component('dispensable')
        self.__check_startup(component)
        self.assertIsNone(component._original_start_time)
        component.start()
        self.__check_started(component)

        self.assertIsNotNone(component._original_start_time)
        self.assertIsNotNone(component._BaseComponent__start_time)
        original_start_time = component._original_start_time
        start_time = component._BaseComponent__start_time
        # Not restarted yet, so they should be the same
        self.assertEqual(original_start_time, start_time)

        self._timeskip()
        # Make it fail
        restarted = component.failed(1)
        # should signal that it restarted
        self.assertTrue(restarted)
        # and check if it really did
        self.__check_restarted(component)

        # original start time should not have changed
        self.assertEqual(original_start_time, component._original_start_time)
        # but actual start time should
        self.assertNotEqual(start_time, component._BaseComponent__start_time)

    def test_bad_kind(self):
        """
        Test the component rejects nonsensical kinds. This includes bad
        capitalization.
        """
        for kind in ['Core', 'CORE', 'nonsense', 'need ed', 'required']:
            self.assertRaises(ValueError, Component, 'No process', self, kind)

    def test_pid_not_running(self):
        """
        Test that a componet that is not yet started doesn't have a PID.
        But it won't fail if asked for and return None.
        """
        for component_type in [Component,
                               isc.bind10.special_component.SockCreator,
                               isc.bind10.special_component.Msgq,
                               isc.bind10.special_component.CfgMgr,
                               isc.bind10.special_component.Auth,
                               isc.bind10.special_component.Resolver,
                               isc.bind10.special_component.CmdCtl]:
            component = component_type('none', self, 'needed')
            self.assertIsNone(component.pid())

    def test_kill_unstarted(self):
        """
        Try to kill the component if it's not started. Should not fail.

        We do not try to kill a running component, as we should not start
        it during unit tests.
        """
        component = Component('component', self, 'needed')
        component.kill()
        component.kill(True)

    def register_process(self, pid, process):
        """
        Part of pretending to be a boss
        """
        self.__registered_processes[pid] = process

    def test_component_attributes(self):
        """
        Test the default attributes of Component (not BaseComponent) and
        some of the methods we might be allowed to call.
        """
        class TestProcInfo:
            def __init__(self):
                self.pid = 42
        component = Component('component', self, 'needed', 'Address',
                              ['hello'], TestProcInfo)
        self.assertEqual('component', component._process)
        self.assertEqual('component', component.name())
        self.assertIsNone(component._procinfo)
        self.assertIsNone(component.pid())
        self.assertEqual(['hello'], component._params)
        self.assertEqual('Address', component._address)
        self.assertFalse(component.running())
        self.assertEqual({}, self.__registered_processes)
        component.start()
        self.assertTrue(component.running())
        # Some versions of unittest miss assertIsInstance
        self.assertTrue(isinstance(component._procinfo, TestProcInfo))
        self.assertEqual(42, component.pid())
        self.assertEqual(component, self.__registered_processes.get(42))

    def stop_process(self, process, address, pid):
        """
        Part of pretending to be boss.
        """
        self.__stop_process_params = (process, address, pid)

    def start_simple(self, process):
        """
        Part of pretending to be boss.
        """
        self.__start_simple_params = process

    def test_component_start_stop_internal(self):
        """
        Test the behavior of _stop_internal and _start_internal.
        """
        component = Component('component', self, 'needed', 'Address')
        component.start()
        self.assertTrue(component.running())
        self.assertEqual('component', self.__start_simple_params)
        component.pid = lambda: 42
        component.stop()
        self.assertFalse(component.running())
        self.assertEqual(('component', 'Address', 42),
                         self.__stop_process_params)

    def test_component_kill(self):
        """
        Check the kill is propagated. The case when component wasn't started
        yet is already tested elsewhere.
        """
        class Process:
            def __init__(self):
                self.killed = False
                self.terminated = False
            def kill(self):
                self.killed = True
            def terminate(self):
                self.terminated = True
        process = Process()
        class ProcInfo:
            def __init__(self):
                self.process = process
                self.pid = 42
        component = Component('component', self, 'needed', 'Address',
                              [], ProcInfo)
        component.start()
        self.assertTrue(component.running())
        component.kill()
        self.assertTrue(process.terminated)
        self.assertFalse(process.killed)
        process.terminated = False
        component.kill(True)
        self.assertTrue(process.killed)
        self.assertFalse(process.terminated)

    def setgid(self, gid):
        self.__gid_set = gid

    def setuid(self, uid):
        self.__uid_set = uid

    class FakeCreator:
        def pid(self):
            return 42
        def terminate(self): pass
        def kill(self): pass

    def set_creator(self, creator):
        """
        Part of faking being the boss. Check the creator (faked as well)
        is passed here.
        """
        self.assertTrue(isinstance(creator, self.FakeCreator))

    def log_started(self, pid):
        """
        Part of faking the boss. Check the pid is the one of the fake creator.
        """
        self.assertEqual(42, pid)

    def test_creator(self):
        """
        Some tests around the SockCreator component.
        """
        component = isc.bind10.special_component.SockCreator(None, self,
                                                             'needed', None)
        orig_setgid = isc.bind10.special_component.posix.setgid
        orig_setuid = isc.bind10.special_component.posix.setuid
        isc.bind10.special_component.posix.setgid = self.setgid
        isc.bind10.special_component.posix.setuid = self.setuid
        orig_creator = \
            isc.bind10.special_component.isc.bind10.sockcreator.Creator
        # Just ignore the creator call
        isc.bind10.special_component.isc.bind10.sockcreator.Creator = \
            lambda path: self.FakeCreator()
        component.start()
        # No gid/uid set in boss, nothing called.
        self.assertIsNone(self.__gid_set)
        self.assertIsNone(self.__uid_set)
        # Doesn't do anything, but doesn't crash
        component.stop()
        component.kill()
        component.kill(True)
        self.gid = 4200
        self.uid = 42
        component = isc.bind10.special_component.SockCreator(None, self,
                                                             'needed', None)
        component.start()
        # This time, it get's called
        self.assertEqual(4200, self.__gid_set)
        self.assertEqual(42, self.__uid_set)
        isc.bind10.special_component.posix.setgid = orig_setgid
        isc.bind10.special_component.posix.setuid = orig_setuid
        isc.bind10.special_component.isc.bind10.sockcreator.Creator = \
            orig_creator

class TestComponent(BaseComponent):
    """
    A test component. It does not start any processes or so, it just logs
    information about what happens.
    """
    def __init__(self, owner, name, kind, address=None, params=None):
        """
        Initializes the component. The owner is the test that started the
        component. The logging will happen into it.

        The process is used as a name for the logging.
        """
        BaseComponent.__init__(self, owner, kind)
        self.__owner = owner
        self.__name = name
        self.log('init')
        self.log(kind)
        self._address = address
        self._params = params

    def log(self, event):
        """
        Log an event into the owner. The owner can then check the correct
        order of events that happened.
        """
        self.__owner.log.append((self.__name, event))

    def _start_internal(self):
        self.log('start')

    def _stop_internal(self):
        self.log('stop')

    def _failed_internal(self):
        self.log('failed')

    def kill(self, forceful=False):
        self.log('killed')

class FailComponent(BaseComponent):
    """
    A mock component that fails whenever it is started.
    """
    def __init__(self, name, boss, kind, address=None, params=None):
        BaseComponent.__init__(self, boss, kind)

    def _start_internal(self):
        raise TestError("test error")

class ConfiguratorTest(BossUtils, unittest.TestCase):
    """
    Tests for the configurator.
    """
    def setUp(self):
        """
        Prepare some test data for the tests.
        """
        BossUtils.setUp(self)
        self.log = []
        # The core "hardcoded" configuration
        self.__core = {
            'core1': {
                'priority': 5,
                'process': 'core1',
                'special': 'test',
                'kind': 'core'
            },
            'core2': {
                'process': 'core2',
                'special': 'test',
                'kind': 'core'
            },
            'core3': {
                'process': 'core3',
                'priority': 3,
                'special': 'test',
                'kind': 'core'
            }
        }
        # How they should be started. They are created in the order they are
        # found in the dict, but then they should be started by priority.
        # This expects that the same dict returns its keys in the same order
        # every time
        self.__core_log_create = []
        for core in self.__core.keys():
            self.__core_log_create.append((core, 'init'))
            self.__core_log_create.append((core, 'core'))
        self.__core_log_start = [('core1', 'start'), ('core3', 'start'),
                                 ('core2', 'start')]
        self.__core_log = self.__core_log_create + self.__core_log_start
        self.__specials = { 'test': self.__component_test }

    def __component_test(self, process, boss, kind, address=None, params=None):
        """
        Create a test component. It will log events to us.
        """
        self.assertEqual(self, boss)
        return TestComponent(self, process, kind, address, params)

    def test_init(self):
        """
        Tests the configurator can be created and it does not create
        any components yet, nor does it remember anything.
        """
        configurator = Configurator(self, self.__specials)
        self.assertEqual([], self.log)
        self.assertEqual({}, configurator._components)
        self.assertFalse(configurator.running())

    def test_run_plan(self):
        """
        Test the internal function of running plans. Just see it can handle
        the commands in the given order. We see that by the log.

        Also includes one that raises, so we see it just stops there.
        """
        # Prepare the configurator and the plan
        configurator = Configurator(self, self.__specials)
        started = self.__component_test('second', self, 'dispensable')
        started.start()
        stopped = self.__component_test('first', self, 'core')
        configurator._components = {'second': started}
        plan = [
            {
                'component': stopped,
                'command': 'start',
                'name': 'first',
                'config': {'a': 1}
            },
            {
                'component': started,
                'command': 'stop',
                'name': 'second',
                'config': {}
            },
            {
                'component': FailComponent('third', self, 'needed'),
                'command': 'start',
                'name': 'third',
                'config': {}
            },
            {
                'component': self.__component_test('fourth', self, 'core'),
                'command': 'start',
                'name': 'fourth',
                'config': {}
            }
        ]
        # Don't include the preparation into the log
        self.log = []
        # The error from the third component is propagated
        self.assertRaises(TestError, configurator._run_plan, plan)
        # The first two were handled, the rest not, due to the exception
        self.assertEqual([('first', 'start'), ('second', 'stop')], self.log)
        self.assertEqual({'first': ({'a': 1}, stopped)},
                         configurator._components)

    def __build_components(self, config):
        """
        Insert the components into the configuration to specify possible
        Configurator._components.

        Actually, the components are None, but we need something to be there.
        """
        result = {}
        for name in config.keys():
            result[name] = (config[name], None)
        return result

    def test_build_plan(self):
        """
        Test building the plan correctly. Not complete yet, this grows as we
        add more ways of changing the plan.
        """
        configurator = Configurator(self, self.__specials)
        plan = configurator._build_plan({}, self.__core)
        # This should have created the components
        self.assertEqual(self.__core_log_create, self.log)
        self.assertEqual(3, len(plan))
        for (task, name) in zip(plan, ['core1', 'core3', 'core2']):
            self.assertTrue('component' in task)
            self.assertEqual('start', task['command'])
            self.assertEqual(name, task['name'])
            component = task['component']
            self.assertIsNone(component._address)
            self.assertIsNone(component._params)

        # A plan to go from older state to newer one containing more components
        bigger = copy.copy(self.__core)
        bigger['additional'] = {
            'priority': 6,
            'special': 'test',
            'process': 'additional',
            'kind': 'dispensable' # need to be dispensable so it could restart
        }
        self.log = []
        plan = configurator._build_plan(self.__build_components(self.__core),
                                        bigger)
        self.assertEqual([('additional', 'init'),
                          ('additional', 'dispensable')],
                         self.log)
        self.assertEqual(1, len(plan))
        self.assertTrue('component' in plan[0])
        component = plan[0]['component']
        self.assertEqual('start', plan[0]['command'])
        self.assertEqual('additional', plan[0]['name'])

        # Now remove the one component again
        # We run the plan so the component is wired into internal structures
        configurator._run_plan(plan)
        # We should have the 'additional' component in the configurator.
        self.assertTrue('additional' in configurator._components)
        for count in [0, 1]:    # repeat two times, see below
            self.log = []
            plan = configurator._build_plan(self.__build_components(bigger),
                                            self.__core)
            self.assertEqual([], self.log)
            self.assertEqual([{
                        'command': 'stop',
                        'name': 'additional',
                        'component': component
                        }], plan)

            if count is 0:
                # We then emulate unexpected failure of the component (but
                # before it restarts).  It shouldn't confuse the
                # configurator in the second phase of the test
                component.failed(0)
        # Run the plan, confirm the specified component is gone.
        configurator._run_plan(plan)
        self.assertFalse('additional' in configurator._components)

        # We want to switch a component. So, prepare the configurator so it
        # holds one
        configurator._run_plan(configurator._build_plan(
             self.__build_components(self.__core), bigger))
        # Get a different configuration with a different component
        different = copy.copy(self.__core)
        different['another'] = {
            'special': 'test',
            'process': 'another',
            'kind': 'dispensable'
        }
        self.log = []
        plan = configurator._build_plan(self.__build_components(bigger),
                                        different)
        self.assertEqual([('another', 'init'), ('another', 'dispensable')],
                         self.log)
        self.assertEqual(2, len(plan))
        self.assertEqual('stop', plan[0]['command'])
        self.assertEqual('additional', plan[0]['name'])
        self.assertTrue('component' in plan[0])
        self.assertEqual('start', plan[1]['command'])
        self.assertEqual('another', plan[1]['name'])
        self.assertTrue('component' in plan[1])

        # Some slightly insane plans, like missing process, having parameters,
        # no special, etc
        plan = configurator._build_plan({}, {
            'component': {
                'kind': 'needed',
                'params': ["1", "2"],
                'address': 'address'
            }
        })
        self.assertEqual(1, len(plan))
        self.assertEqual('start', plan[0]['command'])
        self.assertEqual('component', plan[0]['name'])
        component = plan[0]['component']
        self.assertEqual('component', component.name())
        self.assertEqual(["1", "2"], component._params)
        self.assertEqual('address', component._address)
        self.assertEqual('needed', component._kind)
        # We don't use isinstance on purpose, it would allow a descendant
        self.assertTrue(type(component) is Component)
        plan = configurator._build_plan({}, {
            'component': { 'kind': 'dispensable' }
        })
        self.assertEqual(1, len(plan))
        self.assertEqual('start', plan[0]['command'])
        self.assertEqual('component', plan[0]['name'])
        component = plan[0]['component']
        self.assertEqual('component', component.name())
        self.assertIsNone(component._params)
        self.assertIsNone(component._address)
        self.assertEqual('dispensable', component._kind)

    def __do_switch(self, option, value):
        """
        Start it with some component and then switch the configuration of the
        component. This will probably raise, as it is not yet supported.
        """
        configurator = Configurator(self, self.__specials)
        compconfig = {
            'special': 'test',
            'process': 'process',
            'priority': 13,
            'kind': 'core'
        }
        modifiedconfig = copy.copy(compconfig)
        modifiedconfig[option] = value
        return configurator._build_plan({'comp': (compconfig, None)},
                                        {'comp': modifiedconfig})

    def test_change_config_plan(self):
        """
        Test changing a configuration of one component. This is not yet
        implemented and should therefore throw.
        """
        self.assertRaises(NotImplementedError, self.__do_switch, 'kind',
                          'dispensable')
        self.assertRaises(NotImplementedError, self.__do_switch, 'special',
                          'not_a_test')
        self.assertRaises(NotImplementedError, self.__do_switch, 'process',
                          'different')
        self.assertRaises(NotImplementedError, self.__do_switch, 'address',
                          'different')
        self.assertRaises(NotImplementedError, self.__do_switch, 'params',
                          ['different'])
        # This does not change anything on running component, so no need to
        # raise
        self.assertEqual([], self.__do_switch('priority', 5))
        # Check against false positive, if the data are the same, but different
        # instance
        self.assertEqual([], self.__do_switch('special', 'test'))

    def __check_shutdown_log(self):
        """
        Checks the log for shutting down from the core configuration.
        """
        # We know everything must be stopped, we know what it is.
        # But we don't know the order, so we check everything is exactly
        # once in the log
        components = set(self.__core.keys())
        for (name, command) in self.log:
            self.assertEqual('stop', command)
            self.assertTrue(name in components)
            components.remove(name)
        self.assertEqual(set([]), components, "Some component wasn't stopped")

    def test_run(self):
        """
        Passes some configuration to the startup method and sees if
        the components are started up. Then it reconfigures it with
        empty configuration, the original configuration again and shuts
        down.

        It also checks the components are kept inside the configurator.
        """
        configurator = Configurator(self, self.__specials)
        # Can't reconfigure nor stop yet
        self.assertRaises(ValueError, configurator.reconfigure, self.__core)
        self.assertRaises(ValueError, configurator.shutdown)
        self.assertFalse(configurator.running())
        # Start it
        configurator.startup(self.__core)
        self.assertEqual(self.__core_log, self.log)
        for core in self.__core.keys():
            self.assertTrue(core in configurator._components)
            self.assertEqual(self.__core[core],
                             configurator._components[core][0])
        self.assertEqual(set(self.__core), set(configurator._components))
        self.assertTrue(configurator.running())
        # It can't be started twice
        self.assertRaises(ValueError, configurator.startup, self.__core)

        self.log = []
        # Reconfigure - stop everything
        configurator.reconfigure({})
        self.assertEqual({}, configurator._components)
        self.assertTrue(configurator.running())
        self.__check_shutdown_log()

        # Start it again
        self.log = []
        configurator.reconfigure(self.__core)
        self.assertEqual(self.__core_log, self.log)
        for core in self.__core.keys():
            self.assertTrue(core in configurator._components)
            self.assertEqual(self.__core[core],
                             configurator._components[core][0])
        self.assertEqual(set(self.__core), set(configurator._components))
        self.assertTrue(configurator.running())

        # Do a shutdown
        self.log = []
        configurator.shutdown()
        self.assertEqual({}, configurator._components)
        self.assertFalse(configurator.running())
        self.__check_shutdown_log()

        # It can't be stopped twice
        self.assertRaises(ValueError, configurator.shutdown)

    def test_sort_no_prio(self):
        """
        There was a bug if there were two things with the same priority
        (or without priority), it failed as it couldn't compare the dicts
        there. This tests it doesn't crash.
        """
        configurator = Configurator(self, self.__specials)
        configurator._build_plan({}, {
                                         "c1": { 'kind': 'dispensable'},
                                         "c2": { 'kind': 'dispensable'}
                                     })

if __name__ == '__main__':
    isc.log.init("bind10") # FIXME Should this be needed?
    isc.log.resetUnitTestRootLogger()
    unittest.main()
