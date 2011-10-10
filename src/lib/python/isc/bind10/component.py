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

from isc.log_messages.bind10_messages import *
import time

logger = isc.log.Logger("boss")

"""
Module for managing components (abstraction of process). It allows starting
them in given order, handling when they crash (what happens depends on kind
of component) and shutting down. It also handles the configuration of this.

Dependencies between them are not yet handled. It might turn out they are
needed, in that case they will be added sometime in future.
"""

class Component:
    """
    This represents a single component. It has some defaults of behaviour,
    which should be reasonable for majority of ordinary components, but
    it might be inherited and modified for special-purpose components,
    like the core modules with different ways of starting up.
    """
    def __init__(self, process, boss, kind):
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
        """
        if kind not in ['core', 'needed', 'dispensable']:
            raise ValueError('Component kind can not be ' + kind)
        self.__running = False
        # Dead like really dead. No resurrection possible.
        self.__dead = False
        self.__kind = kind
        self.__boss = boss

    def start(self):
        """
        Start the component for the first time or restart it. If you need to
        modify the way a component is started, do not replace this method,
        but start_internal. This one does some more bookkeeping around.

        If you try to start an already running component, it raises ValueError.
        """
        if self.__dead:
            raise ValueError("Can't resurrect already dead component")
        if self.running():
            raise ValueError("Can't start already running component")
        self.__running = True
        self.__start_time = time.time()
        try:
            self.start_internal()
        except:
            self.failed()
            raise

    def start_internal(self):
        """
        This method does the actual starting of a process. If you need to
        change the way the component is started, replace this method.
        """
        pass

    def stop(self):
        """
        Stop the component. If you need to modify the way a component is
        stopped, do not replace this method, but stop_internal. This one
        does some more bookkeeping.

        If you try to stop a component that is not running, it raises
        ValueError.
        """
        if not self.running():
            raise ValueError("Can't stop a component which is not running")
        self.stop_internal()
        self.__running = False

    def stop_internal(self):
        """
        This is the method that does the actual stopping of a component.
        You can replace this method if you want a different way to do it.
        """
        pass

    def failed(self):
        """
        Notify the component it crashed. This will be called from boss object.

        If you try to call failed on a component that is not running,
        a ValueError is raised.
        """
        if not self.running():
            raise ValueError("Can't fail component that isn't running")
        self.failed_internal()
        self.__running = False
        # If it is a core component or the needed component failed to start
        # (including it stopped really soon)
        if self.__kind == 'core' or \
            (self.__kind == 'needed' and time.time() - 10 < self.__start_time):
            self.__dead = True
            self.__boss.shutdown(1)
        # This means we want to restart
        else:
            self.start()

    def failed_internal(self):
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
        """
        return self.__running

specials = {}
"""
List of specially started components. Each one should be the class than can
be created for that component.
"""

class Configurator:
    """
    This thing keeps track of configuration changes and starts and stops
    components as it goes. It also handles the inital startup and final
    shutdown.

    Note that this will allow you to stop (by invoking reconfigure) a core
    component. There should be some kind of layer protecting users from ever
    doing so (users must not stop the config manager, message queue and stuff
    like that or the system won't start again).
    """
    def __init__(self, boss):
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

    def startup(self, configuration):
        """
        Starts the first set of processes. This configuration is expected
        to be hardcoded from the boss itself to start the configuration
        manager and other similar things.
        """
        if self._running:
            raise ValueError("Trying to start the component configurator " +
                             "twice")
        self._run_plan(self._build_plan({}, configuration))
        self._old_config = configuration
        self._running = True

    def shutdown(self):
        """
        Shuts everything down.
        """
        pass

    def reconfigure(configuration):
        """
        Changes configuration from the current one to the provided. It
        starts and stops all the components as needed.
        """
        pass

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
        plan = []
        # Handle removals of old components
        for cname in old.keys():
            if cname not in new:
                component = self._components[cname]
                if component.running():
                    plan.append({
                        'command': 'stop',
                        'component': component
                    })
        # Handle introduction of new components
        plan_add = []
        for cname in new.keys():
            if cname not in old:
                params = new[cname]
                creator = Component
                if 'special' in params:
                    # TODO: Better error handling
                    creator = specials[params['special']]
                component = creator(params['process'], self.__boss,
                                    params['kind'])
                priority = 0
                if 'priority' in params:
                    priority = params['priority']
                # We store tuples, priority first, so we can easily sort
                plan_add.append((priority, {
                    'component': component,
                    'command': 'start',
                    'name': cname
                }))
        # Push the starts there sorted by priority
        plan.extend([command for (_, command) in sorted(plan_add,
                                                        reverse=True)])
        return plan

    def _run_plan(self, plan):
        """
        Run a plan, created beforehead by _build_plan.

        With the start and stop commands, it also adds and removes components
        in _components.

        Currently implemented commands are:
        * start
        * stop
        """
        for task in plan:
            component = task['component']
            command = task['command']
            if command == 'start':
                component.start()
                self._components[task['name']] = component
            elif command == 'stop':
                component.stop()
                del self._components[task['name']]
            else:
                # Can Not Happen (as the plans are generated by ourself).
                # Therefore not tested.
                raise NotImplementedError("Command unknown: " + command)
