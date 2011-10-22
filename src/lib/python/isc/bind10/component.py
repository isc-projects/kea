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
"""

import isc.log
from isc.log_messages.bind10_messages import *
import time

logger = isc.log.Logger("boss")
DBG_TRACE_DATA = 20
DBG_TRACE_DETAILED = 80

START_CMD = 'start'
STOP_CMD = 'stop'

STARTED_OK_TIME = 10

STATE_DEAD = 'dead'
STATE_STOPPED = 'stopped'
STATE_RUNNING = 'running'

class Component:
    """
    This represents a single component. It has some defaults of behaviour,
    which should be reasonable for majority of ordinary components, but
    it might be inherited and modified for special-purpose components,
    like the core modules with different ways of starting up. Another
    way to tweak only the start of the component (eg. by providing some
    command line parameters) is to set _start_func function from within
    inherited class.

    The methods are marked if it is expected for them to be overridden.


    The component is in one of the three states:
    - Stopped - it is either not started yet or it was explicitly stopped.
      The component is created in this state (it must be asked to start
      explicitly).
    - Running - after start() was called, it started successfully and is
      now running.
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
                    v            |                |
                    +<-----------+                |
                    |                             |
                    |  kind == dispensable or kind|== needed and failed late
                    +-----------------------------+
                    |
                    | kind == core or kind == needed and it failed too soon
                    v
                  Dead
    """
    def __init__(self, process, boss, kind, address=None, params=None):
        """
        Creates the component in not running mode.

        The parameters are:
        - `process` is the name of the process to start.
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
            it is restarted.
          * 'dispensable' means the component should be running, but if it
            doesn't start or crashes for some reason, the system simply tries
            to restart it and keeps running.
        - `address` is the address on message bus. It is used to ask it to
            shut down at the end. If you specialize the class for a component
            that is shut down differently, it might be None.
        - `params` is a list of parameters to pass to the process when it
           starts. It is currently unused and this support is left out for
           now.
        """
        if kind not in ['core', 'needed', 'dispensable']:
            raise ValueError('Component kind can not be ' + kind)
        self.__state = STATE_STOPPED
        self._kind = kind
        self._boss = boss
        self._process = process
        self._start_func = None
        self._address = address
        self._params = params
        self._procinfo = None

    def start(self):
        """
        Start the component for the first time or restart it. If you need to
        modify the way a component is started, do not replace this method,
        but _start_internal. This one does some more bookkeeping around.

        If you try to start an already running component, it raises ValueError.
        """
        if self.__state == STATE_DEAD:
            raise ValueError("Can't resurrect already dead component")
        if self.running():
            raise ValueError("Can't start already running component")
        logger.info(BIND10_COMPONENT_START, self.name())
        self.__state = STATE_RUNNING
        self.__start_time = time.time()
        try:
            self._start_internal()
        except Exception as e:
            logger.error(BIND10_COMPONENT_START_EXCEPTION, self.name(), e)
            self.failed()
            raise

    def _start_internal(self):
        """
        This method does the actual starting of a process. If you need to
        change the way the component is started, replace this method.

        You can change the "core" of this function by setting self._start_func
        to a function without parameters. Such function should start the
        process and return the procinfo object describing the running process.

        If you don't provide the _start_func, the usual startup by calling
        boss.start_simple is performed.

        If you override the method completely, you should consider overriding
        pid and _stop_internal (and possibly _failed_internal and name) as well.
        You should also register any processes started within boss.
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

    def stop(self):
        """
        Stop the component. If you need to modify the way a component is
        stopped, do not replace this method, but _stop_internal. This one
        does some more bookkeeping.

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

    def _stop_internal(self):
        """
        This is the method that does the actual stopping of a component.
        You can replace this method if you want a different way to do it.

        If you're overriding this one, you probably want to replace the
        _start_internal and pid methods (and maybe _failed_internal and
        name as well).
        """
        self._boss.stop_process(self._process, self._address)

    def failed(self):
        """
        Notify the component it crashed. This will be called from boss object.

        If you try to call failed on a component that is not running,
        a ValueError is raised.

        If it is a core component or needed component and it was started only
        recently, the component will become dead and will ask the boss to shut
        down with error exit status. A dead component can't be started again.

        Otherwise the component will try to restart.
        """
        if not self.running():
            raise ValueError("Can't fail component that isn't running")
        self.__state = STATE_STOPPED
        self._failed_internal()
        # If it is a core component or the needed component failed to start
        # (including it stopped really soon)
        if self._kind == 'core' or \
            (self._kind == 'needed' and time.time() - STARTED_OK_TIME <
             self.__start_time):
            self.__state = STATE_DEAD
            logger.fatal(BIND10_COMPONENT_UNSATISFIED, self.name())
            self._boss.component_shutdown(1)
        # This means we want to restart
        else:
            logger.warn(BIND10_COMPONENT_RESTART, self.name())
            self.start()

    def _failed_internal(self):
        """
        This method is called from failed. You can replace it if you need
        some specific behaviour when the component crashes. The default
        implementation is empty.

        Do not raise exceptions from here, please. The propper shutdown
        would have not happened.
        """
        pass

    def running(self):
        """
        Informs if the component is currently running. It assumes the failed
        is called whenever the component really fails and there might be some
        time in between actual failure and the call.

        It is not expected for this method to be overriden.
        """
        return self.__state == STATE_RUNNING

    def name(self):
        """
        Returns human-readable name of the component. This is usually the
        name of the executable, but it might be something different in a
        derived class (in case it is overriden).
        """
        return self._process

    def pid(self):
        """
        Provides a PID of a process, if the component is real running process.
        This implementation expects it to be a real process, but derived class
        may return None in case the component is something else.

        This returns None in case it is not yet running.

        You probably want to override this method if you're providing custom
        _start_internal.
        """
        return self._procinfo.pid if self._procinfo else None

class Configurator:
    """
    This thing keeps track of configuration changes and starts and stops
    components as it goes. It also handles the inital startup and final
    shutdown.

    Note that this will allow you to stop (by invoking reconfigure) a core
    component. There should be some kind of layer protecting users from ever
    doing so (users must not stop the config manager, message queue and stuff
    like that or the system won't start again).

    The parameters are:
    * `boss`: The boss we are managing for.
    * `specials`: Dict of specially started components. Each item is a class
      representing the component.

    The configuration passed to it (by startup() and reconfigure()) is a
    dictionary, each item represents one component that should be running.
    The key is an unique identifier used to reference the component. The
    value is a dictionary describing the component. All items in the
    description is optional and they are as follows:
    * `special` - Some components are started in a special way. If it is
      present, it specifies which class from the specials parameter should
      be used to create the component. In that case, some of the following
      items might be irrelevant, depending on the special component choosen.
      If it is not there, the basic Component class is used.
    * `process` - Name of the executable to start. If it is not present,
      it defaults to the identifier of the component.
    * `kind` - The kind of component, either of 'core', 'needed' and
      'dispensable'. This specifies what happens if the component fails.
      Defaults to despensable.
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
        self._components = {}
        self._old_config = {}
        self._running = False
        self.__specials = specials

    def __reconfigure_internal(self, old, new):
        """
        Does a switch from one configuration to another.
        """
        self._run_plan(self._build_plan(old, new))
        self._old_config = new

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
        self.__reconfigure_internal({}, configuration)
        self._running = True

    def shutdown(self):
        """
        Shuts everything down.
        """
        if not self._running:
            raise ValueError("Trying to shutdown the component " +
                             "configurator while it's not yet running")
        logger.info(BIND10_CONFIGURATOR_STOP)
        self._running = False
        self.__reconfigure_internal(self._old_config, {})

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
        self.__reconfigure_internal(self._old_config, configuration)

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
                component = self._components[cname]
                if component.running():
                    plan.append({
                        'command': STOP_CMD,
                        'component': component,
                        'name': cname
                    })
        # Handle transitions of configuration of what is here
        for cname in new.keys():
            if cname in old:
                for option in ['special', 'process', 'kind']:
                    if new[cname].get(option) != old[cname].get(option):
                        raise NotImplementedError('Changing configuration of' +
                                                  ' a running component is ' +
                                                  'not yet supported. Remove' +
                                                  ' and re-add ' + cname +
                                                  'to get the same effect')
        # Handle introduction of new components
        plan_add = []
        for cname in new.keys():
            if cname not in old:
                component_spec = new[cname]
                creator = Component
                if 'special' in component_spec:
                    # TODO: Better error handling
                    creator = self.__specials[component_spec['special']]
                component = creator(component_spec.get('process', cname),
                                    self.__boss,
                                    component_spec.get('kind', 'dispensable'),
                                    component_spec.get('address'),
                                    component_spec.get('params'))
                priority = component_spec.get('priority', 0)
                # We store tuples, priority first, so we can easily sort
                plan_add.append((priority, {
                    'component': component,
                    'command': START_CMD,
                    'name': cname,
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
        the component as well (the identifier from configuration).
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
                    self._components[task['name']] = component
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
