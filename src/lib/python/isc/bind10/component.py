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
Module for managing components (abstraction of process). It allows starting
them in given order, handling when they crash (what happens depends on kind
of component) and shutting down. It also handles the configuration of this.

Dependencies between them are not yet handled. It might turn out they are
needed, in that case they will be added sometime in future.

This framework allows for a single process to be started multiple times (by
specifying multiple components with the same configuration). We might want
to add a more convenient support (like providing a count argument to the
configuration). This is yet to be designed.
"""

import isc.log
from isc.log_messages.bind10_messages import *
import time
import os
import signal

logger = isc.log.Logger("boss")
DBG_TRACE_DATA = 20
DBG_TRACE_DETAILED = 80

START_CMD = 'start'
STOP_CMD = 'stop'

STARTED_OK_TIME = 10
COMPONENT_RESTART_DELAY = 10

STATE_DEAD = 'dead'
STATE_STOPPED = 'stopped'
STATE_FAILED = 'failed'
STATE_RUNNING = 'running'

def get_signame(signal_number):
    """Return the symbolic name for a signal."""
    for sig in dir(signal):
        if sig.startswith("SIG") and sig[3].isalnum():
            if getattr(signal, sig) == signal_number:
                return sig
    return "unknown signal"

class BaseComponent:
    """
    This represents a single component. This one is an abstract base class.
    There are some methods which should be left untouched, but there are
    others which define the interface only and should be overriden in
    concrete implementations.

    The component is in one of the three states:
    - Stopped - it is either not started yet or it was explicitly stopped.
      The component is created in this state (it must be asked to start
      explicitly).
    - Running - after start() was called, it started successfully and is
      now running.
    - Failed - the component failed (crashed) and is waiting for a restart
    - Dead - it failed and can not be resurrected.

    Init
      |            stop()
      |  +-----------------------+
      |  |                       |
      v  |  start()  success     |
    Stopped --------+--------> Running <----------+
                    |            |                |
                    |failure     | failed()       |
                    |            |                |
                    v            |                | start()/restart()
                    +<-----------+                |
                    |                             |
                    |  kind == dispensable or kind|== needed and failed late
                    +-----------------------> Failed
                    |
                    | kind == core or kind == needed and it failed too soon
                    v
                  Dead

    Note that there are still situations which are not handled properly here.
    We don't recognize a component that is starting up, but not ready yet, one
    that is already shutting down, impossible to stop, etc. We need to add more
    states in future to handle it properly.
    """
    def __init__(self, boss, kind):
        """
        Creates the component in not running mode.

        The parameters are:
        - `boss` the boss object to plug into. The component needs to plug
          into it to know when it failed, etc.
        - `kind` is the kind of component. It may be one of:
          * 'core' means the system can't run without it and it can't be
            safely restarted. If it does not start, the system is brought
            down. If it crashes, the system is turned off as well (with
            non-zero exit status).
          * 'needed' means the system is able to restart the component,
            but it is vital part of the service (like auth server). If
            it fails to start or crashes in less than 10s after the first
            startup, the system is brought down. If it crashes later on,
            it is restarted (see below).
          * 'dispensable' means the component should be running, but if it
            doesn't start or crashes for some reason, the system simply tries
            to restart it and keeps running.

        For components that are restarted, the restarts are not always
        immediate; if the component has run for more than
        COMPONENT_RESTART_DELAY (10) seconds, they are restarted right
        away. If the component has not run that long, the system waits
        until that time has passed (since the last start) until the
        component is restarted.

        Note that the __init__ method of child class should have these
        parameters:

        __init__(self, process, boss, kind, address=None, params=None)

        The extra parameters are:
        - `process` - which program should be started.
        - `address` - the address on message bus, used to talk to the
           component.
        - `params` - parameters to the program.

        The methods you should not override are:
        - start
        - stop
        - failed
        - running

        You should override:
        - _start_internal
        - _stop_internal
        - _failed_internal (if you like, the empty default might be suitable)
        - name
        - pid
        - kill
        """
        if kind not in ['core', 'needed', 'dispensable']:
            raise ValueError('Component kind can not be ' + kind)
        self.__state = STATE_STOPPED
        self._kind = kind
        self._boss = boss
        self._original_start_time = None

    def start(self):
        """
        Start the component for the first time or restart it. It runs
        _start_internal to actually start the component.

        If you try to start an already running component, it raises ValueError.
        """
        if self.__state == STATE_DEAD:
            raise ValueError("Can't resurrect already dead component")
        if self.running():
            raise ValueError("Can't start already running component")
        logger.info(BIND10_COMPONENT_START, self.name())
        self.__state = STATE_RUNNING
        self.__start_time = time.time()
        if self._original_start_time is None:
            self._original_start_time = self.__start_time
        self._restart_time = None
        try:
            self._start_internal()
        except Exception as e:
            logger.error(BIND10_COMPONENT_START_EXCEPTION, self.name(), e)
            self.failed(None)
            raise

    def stop(self):
        """
        Stop the component. It calls _stop_internal to do the actual
        stopping.

        If you try to stop a component that is not running, it raises
        ValueError.
        """
        # This is not tested. It talks with the outher world, which is out
        # of scope of unittests.
        if not self.running():
            raise ValueError("Can't stop a component which is not running")
        logger.info(BIND10_COMPONENT_STOP, self.name())
        self.__state = STATE_STOPPED
        self._stop_internal()

    def failed(self, exit_code):
        """
        Notify the component it crashed. This will be called from boss object.

        If you try to call failed on a component that is not running,
        a ValueError is raised.

        If it is a core component or needed component and it was started only
        recently, the component will become dead and will ask the boss to shut
        down with error exit status. A dead component can't be started again.

        Otherwise the component will try to restart.

        The exit code is used for logging. It might be None.

        It calls _failed_internal internally.

        Returns True if the process was immediately restarted, returns
                False is the process was not restarted, either because
                it is considered a core or needed component, or because
                the component is to be restarted later.
        """

        if exit_code is not None:
            if os.WIFEXITED(exit_code):
                exit_str = "process exited normally with exit status %d" % (exit_code)
            elif os.WIFSIGNALED(exit_code):
                sig = os.WTERMSIG(exit_code)
                signame = get_signame(sig)
                if os.WCOREDUMP(exit_code):
                    exit_str = "process dumped core with exit status %d (killed by signal %d: %s)" % (exit_code, sig, signame)
                else:
                    exit_str = "process terminated with exit status %d (killed by signal %d: %s)" % (exit_code, sig, signame)
            else:
                exit_str = "unknown condition with exit status %d" % (exit_code)
        else:
            exit_str = "unknown condition"

        logger.error(BIND10_COMPONENT_FAILED, self.name(), self.pid(),
                     exit_str)
        if not self.running():
            raise ValueError("Can't fail component that isn't running")
        self.__state = STATE_FAILED
        self._failed_internal()
        # If it is a core component or the needed component failed to start
        # (including it stopped really soon)
        if self._kind == 'core' or \
            (self._kind == 'needed' and time.time() - STARTED_OK_TIME <
             self._original_start_time):
            self.__state = STATE_DEAD
            logger.fatal(BIND10_COMPONENT_UNSATISFIED, self.name())
            self._boss.component_shutdown(1)
            return False
        # This means we want to restart
        else:
            # if the component was only running for a short time, don't
            # restart right away, but set a time it wants to restarted,
            # and return that it wants to be restarted later
            self.set_restart_time()
            return self.restart()

    def set_restart_time(self):
        """Calculates and sets the time this component should be restarted.
           Currently, it uses a very basic algorithm; start time +
           RESTART_DELAY (10 seconds). This algorithm may be improved upon
           in the future.
        """
        self._restart_at = self.__start_time + COMPONENT_RESTART_DELAY

    def get_restart_time(self):
        """Returns the time at which this component should be restarted."""
        return self._restart_at

    def restart(self, now = None):
        """Restarts the component if it has a restart_time and if the value
           of the restart_time is smaller than 'now'.

           If the parameter 'now' is given, its value will be used instead
           of calling time.time().

           Returns True if the component is restarted, False if not."""
        if now is None:
            now = time.time()
        if self.get_restart_time() is not None and\
           self.get_restart_time() < now:
            self.start()
            return True
        else:
            return False

    def running(self):
        """
        Informs if the component is currently running. It assumes the failed
        is called whenever the component really fails and there might be some
        time in between actual failure and the call, so this might be
        inaccurate (it corresponds to the thing the object thinks is true, not
        to the real "external" state).

        It is not expected for this method to be overriden.
        """
        return self.__state == STATE_RUNNING

    def is_failed(self):
        """Informs if the component has failed and is waiting for a restart.

        Unlike the case of running(), if this returns True it always means
        the corresponding process has died and not yet restarted.

        """
        return self.__state == STATE_FAILED

    def _start_internal(self):
        """
        This method does the actual starting of a process. You need to override
        this method to do the actual starting.

        The ability to override this method presents some flexibility. It
        allows processes started in a strange way, as well as components that
        have no processes at all or components with multiple processes (in case
        of multiple processes, care should be taken to make their
        started/stopped state in sync and all the processes that can fail
        should be registered).

        You should register all the processes created by calling
        self._boss.register_process.
        """
        pass

    def _stop_internal(self):
        """
        This is the method that does the actual stopping of a component.
        You need to provide it in a concrete implementation.

        Also, note that it is a bad idea to raise exceptions from here.
        Under such circumstance, the component will be considered stopped,
        and the exception propagated, but we can't be sure it really is
        dead.
        """
        pass

    def _failed_internal(self):
        """
        This method is called from failed. You can replace it if you need
        some specific behaviour when the component crashes. The default
        implementation is empty.

        Do not raise exceptions from here, please. The propper shutdown
        would have not happened.
        """
        pass

    def name(self):
        """
        Provides human readable name of the component, for logging and similar
        purposes.

        You need to provide this method in a concrete implementation.
        """
        pass

    def pid(self):
        """
        Provides a PID of a process, if the component is real running process.
        This may return None in cases when there's no process involved with the
        component or in case the component is not started yet.

        However, it is expected the component preserves the pid after it was
        stopped, to ensure we can log it when we ask it to be killed (in case
        the process refused to stop willingly).

        You need to provide this method in a concrete implementation.
        """
        pass

    def kill(self, forceful=False):
        """
        Kills the component.

        If forcefull is true, it should do it in more direct and aggressive way
        (for example by using SIGKILL or some equivalent). If it is false, more
        peaceful way should be used (SIGTERM or equivalent).

        You need to provide this method in a concrete implementation.
        """
        pass

    def address(self):
        """
        Provides the name of the address used on the message bus

        You need to provide this method in a concrete implementation.
        """
        pass

class Component(BaseComponent):
    """
    The most common implementation of a component. It can be used either
    directly, and it will just start the process without anything special,
    or slightly customised by passing a start_func hook to the __init__
    to change the way it starts.

    If such customisation isn't enough, you should inherit BaseComponent
    directly. It is not recommended to override methods of this class
    on one-by-one basis.
    """
    def __init__(self, process, boss, kind, address=None, params=None,
                 start_func=None):
        """
        Creates the component in not running mode.

        The parameters are:
        - `process` is the name of the process to start.
        - `boss` the boss object to plug into. The component needs to plug
          into it to know when it failed, etc.
        - `kind` is the kind of component. Refer to the documentation of
          BaseComponent for details.
        - `address` is the address on message bus. It is used to ask it to
            shut down at the end. If you specialize the class for a component
            that is shut down differently, it might be None.
        - `params` is a list of parameters to pass to the process when it
           starts. It is currently unused and this support is left out for
           now.
        - `start_func` is a function called when it is started. It is supposed
           to start up the process and return a ProcInfo object describing it.
           There's a sensible default if not provided, which just launches
           the program without any special care.
        """
        BaseComponent.__init__(self, boss, kind)
        self._process = process
        self._start_func = start_func
        self._address = address
        self._params = params
        self._procinfo = None

    def _start_internal(self):
        """
        You can change the "core" of this function by setting self._start_func
        to a function without parameters. Such function should start the
        process and return the procinfo object describing the running process.

        If you don't provide the _start_func, the usual startup by calling
        boss.start_simple is performed.
        """
        # This one is not tested. For one, it starts a real process
        # which is out of scope of unit tests, for another, it just
        # delegates the starting to other function in boss (if a derived
        # class does not provide an override function), which is tested
        # by use.
        if self._start_func is not None:
            procinfo = self._start_func()
        else:
            # TODO Handle params, etc
            procinfo = self._boss.start_simple(self._process)
        self._procinfo = procinfo
        self._boss.register_process(self.pid(), self)

    def _stop_internal(self):
        self._boss.stop_process(self._process, self._address, self.pid())
        # TODO Some way to wait for the process that doesn't want to
        # terminate and kill it would prove nice (or add it to boss somewhere?)

    def name(self):
        """
        Returns the name, derived from the process name.
        """
        return self._process

    def pid(self):
        return self._procinfo.pid if self._procinfo is not None else None

    def kill(self, forcefull=False):
        if self._procinfo is not None:
            if forcefull:
                self._procinfo.process.kill()
            else:
                self._procinfo.process.terminate()

    def address(self):
        """
        Returns the name of the address used on the message bus
        """
        return self._address

class Configurator:
    """
    This thing keeps track of configuration changes and starts and stops
    components as it goes. It also handles the inital startup and final
    shutdown.

    Note that this will allow you to stop (by invoking reconfigure) a core
    component. There should be some kind of layer protecting users from ever
    doing so (users must not stop the config manager, message queue and stuff
    like that or the system won't start again). However, if a user specifies
    b10-auth as core, it is safe to stop that one.

    The parameters are:
    * `boss`: The boss we are managing for.
    * `specials`: Dict of specially started components. Each item is a class
      representing the component.

    The configuration passed to it (by startup() and reconfigure()) is a
    dictionary, each item represents one component that should be running.
    The key is an unique identifier used to reference the component. The
    value is a dictionary describing the component. All items in the
    description is optional unless told otherwise and they are as follows:
    * `special` - Some components are started in a special way. If it is
      present, it specifies which class from the specials parameter should
      be used to create the component. In that case, some of the following
      items might be irrelevant, depending on the special component chosen.
      If it is not there, the basic Component class is used.
    * `process` - Name of the executable to start. If it is not present,
      it defaults to the identifier of the component.
    * `kind` - The kind of component, either of 'core', 'needed' and
      'dispensable'. This specifies what happens if the component fails.
      This one is required.
    * `address` - The address of the component on message bus. It is used
      to shut down the component. All special components currently either
      know their own address or don't need one and ignore it. The common
      components should provide this.
    * `params` - The command line parameters of the executable. Defaults
      to no parameters. It is currently unused.
    * `priority` - When starting the component, the components with higher
      priority are started before the ones with lower priority. If it is
      not present, it defaults to 0.
    """
    def __init__(self, boss, specials = {}):
        """
        Initializes the configurator, but nothing is started yet.

        The boss parameter is the boss object used to start and stop processes.
        """
        self.__boss = boss
        # These could be __private, but as we access them from within unittest,
        # it's more comfortable to have them just _protected.

        # They are tuples (configuration, component)
        self._components = {}
        self._running = False
        self.__specials = specials

    def __reconfigure_internal(self, old, new):
        """
        Does a switch from one configuration to another.
        """
        self._run_plan(self._build_plan(old, new))

    def startup(self, configuration):
        """
        Starts the first set of processes. This configuration is expected
        to be hardcoded from the boss itself to start the configuration
        manager and other similar things.
        """
        if self._running:
            raise ValueError("Trying to start the component configurator " +
                             "twice")
        logger.info(BIND10_CONFIGURATOR_START)
        self.__reconfigure_internal(self._components, configuration)
        self._running = True

    def shutdown(self):
        """
        Shuts everything down.

        It is not expected that anyone would want to shutdown and then start
        the configurator again, so we don't explicitly make sure that would
        work. However, we are not aware of anything that would make it not
        work either.
        """
        if not self._running:
            raise ValueError("Trying to shutdown the component " +
                             "configurator while it's not yet running")
        logger.info(BIND10_CONFIGURATOR_STOP)
        self._running = False
        self.__reconfigure_internal(self._components, {})

    def has_component(self, component):
        '''Return if a specified component is configured.'''
        return component in map(lambda x: x[1], self._components.values())

    def reconfigure(self, configuration):
        """
        Changes configuration from the current one to the provided. It
        starts and stops all the components as needed (eg. if there's
        a component that was not in the original configuration, it is
        started, any component that was in the old and is not in the
        new one is stopped).
        """
        if not self._running:
            raise ValueError("Trying to reconfigure the component " +
                             "configurator while it's not yet running")
        logger.info(BIND10_CONFIGURATOR_RECONFIGURE)
        self.__reconfigure_internal(self._components, configuration)

    def _build_plan(self, old, new):
        """
        Builds a plan how to transfer from the old configuration to the new
        one. It'll be sorted by priority and it will contain the components
        (already created, but not started). Each command in the plan is a dict,
        so it can be extended any time in future to include whatever
        parameters each operation might need.

        Any configuration problems are expected to be handled here, so the
        plan is not yet run.
        """
        logger.debug(DBG_TRACE_DATA, BIND10_CONFIGURATOR_BUILD, old, new)
        plan = []
        # Handle removals of old components
        for cname in old.keys():
            if cname not in new:
                component = self._components[cname][1]
                if component.running() or component.is_failed():
                    plan.append({
                        'command': STOP_CMD,
                        'component': component,
                        'name': cname
                    })
        # Handle transitions of configuration of what is here
        for cname in new.keys():
            if cname in old:
                for option in ['special', 'process', 'kind', 'address',
                               'params']:
                    if new[cname].get(option) != old[cname][0].get(option):
                        raise NotImplementedError('Changing configuration of' +
                                                  ' a running component is ' +
                                                  'not yet supported. Remove' +
                                                  ' and re-add ' + cname +
                                                  ' to get the same effect')
        # Handle introduction of new components
        plan_add = []
        for cname in new.keys():
            if cname not in old:
                component_config = new[cname]
                creator = Component
                if 'special' in component_config:
                    # TODO: Better error handling
                    creator = self.__specials[component_config['special']]
                component = creator(component_config.get('process', cname),
                                    self.__boss, component_config['kind'],
                                    component_config.get('address'),
                                    component_config.get('params'))
                priority = component_config.get('priority', 0)
                # We store tuples, priority first, so we can easily sort
                plan_add.append((priority, {
                    'component': component,
                    'command': START_CMD,
                    'name': cname,
                    'config': component_config
                }))
        # Push the starts there sorted by priority
        plan.extend([command for (_, command) in sorted(plan_add,
                                                        reverse=True,
                                                        key=lambda command:
                                                            command[0])])
        return plan

    def running(self):
        """
        Returns if the configurator is running (eg. was started by startup and
        not yet stopped by shutdown).
        """
        return self._running

    def _run_plan(self, plan):
        """
        Run a plan, created beforehand by _build_plan.

        With the start and stop commands, it also adds and removes components
        in _components.

        Currently implemented commands are:
        * start
        * stop

        The plan is a list of tasks, each task is a dictionary. It must contain
        at last 'component' (a component object to work with) and 'command'
        (the command to do). Currently, both existing commands need 'name' of
        the component as well (the identifier from configuration). The 'start'
        one needs the 'config' to be there, which is the configuration description
        of the component.
        """
        done = 0
        try:
            logger.debug(DBG_TRACE_DATA, BIND10_CONFIGURATOR_RUN, len(plan))
            for task in plan:
                component = task['component']
                command = task['command']
                logger.debug(DBG_TRACE_DETAILED, BIND10_CONFIGURATOR_TASK,
                             command, component.name())
                if command == START_CMD:
                    component.start()
                    self._components[task['name']] = (task['config'],
                                                      component)
                elif command == STOP_CMD:
                    if component.running():
                        component.stop()
                    del self._components[task['name']]
                else:
                    # Can Not Happen (as the plans are generated by ourselves).
                    # Therefore not tested.
                    raise NotImplementedError("Command unknown: " + command)
                done += 1
        except:
            logger.error(BIND10_CONFIGURATOR_PLAN_INTERRUPTED, done, len(plan))
            raise
