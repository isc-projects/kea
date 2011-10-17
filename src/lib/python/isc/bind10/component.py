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

import isc.bind10.sockcreator
import isc.log
from isc.log_messages.bind10_messages import *
import time
from bind10_config import LIBEXECDIR
import os

logger = isc.log.Logger("boss")
DBG_TRACE_DATA = 20
DBG_TRACE_DETAILED = 80

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
        self.__running = False
        # Dead like really dead. No resurrection possible.
        self.__dead = False
        self._kind = kind
        self._boss = boss
        self._process = process
        self._start_func = None
        self._address = address
        self._params = params

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
        logger.info(BIND10_COMPONENT_START, self.name())
        self.__running = True
        self.__start_time = time.time()
        try:
            self.start_internal()
        except Exception as e:
            logger.error(BIND10_COMPONENT_START_EXCEPTION, self.name(), e)
            self.failed()
            raise

    def start_internal(self):
        """
        This method does the actual starting of a process. If you need to
        change the way the component is started, replace this method.
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
        stopped, do not replace this method, but stop_internal. This one
        does some more bookkeeping.

        If you try to stop a component that is not running, it raises
        ValueError.
        """
        # This is not tested. It talks with the outher world, which is out
        # of scope of unittests.
        if not self.running():
            raise ValueError("Can't stop a component which is not running")
        logger.info(BIND10_COMPONENT_STOP, self.name())
        self.__running = False
        self.stop_internal()

    def stop_internal(self):
        """
        This is the method that does the actual stopping of a component.
        You can replace this method if you want a different way to do it.
        """
        self._boss.stop_process(self._process, self._address)

    def failed(self):
        """
        Notify the component it crashed. This will be called from boss object.

        If you try to call failed on a component that is not running,
        a ValueError is raised.
        """
        if not self.running():
            raise ValueError("Can't fail component that isn't running")
        self.__running = False
        self.failed_internal()
        # If it is a core component or the needed component failed to start
        # (including it stopped really soon)
        if self._kind == 'core' or \
            (self._kind == 'needed' and time.time() - 10 < self.__start_time):
            self.__dead = True
            logger.fatal(BIND10_COMPONENT_UNSATISFIED, self.name())
            self._boss.component_shutdown(1)
        # This means we want to restart
        else:
            logger.warn(BIND10_COMPONENT_RESTART, self.name())
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

    def name(self):
        """
        Returns human-readable name of the component. This is usually the
        name of the executable, but it might be something different in a
        derived class.
        """
        return self._process

    def pid(self):
        """
        Provides a PID of a process, if the component is real running process.
        This implementation expects it to be a real process, but derived class
        may return None in case the component is something else.
        """
        return self._procinfo.pid

# These are specialized components. Some of them are components which need
# special care (like the message queue or socket creator) or they need
# some parameters constructed from Boss's command line. They are not tested
# currently, because it is not clear what to test on them anyway and they just
# delegate the work for the boss
class SockCreator(Component):
    """
    The socket creator component. Will start and stop the socket creator
    accordingly.
    """
    def start_internal(self):
        self._boss.curproc = 'b10-sockcreator'
        self.__creator = isc.bind10.sockcreator.Creator(LIBEXECDIR + ':' +
                                                        os.environ['PATH'])
        self._boss.register_process(self.pid(), self)

    def stop_internal(self):
        if self.__creator is None:
            return
        self.__creator.terminate()
        self.__creator = None

    def pid(self):
        """
        Pid of the socket creator. It is provided differently from a usual
        component.
        """
        return self.__creator.pid()

class Msgq(Component):
    """
    The message queue. Starting is passed to boss, stopping is not supported
    and we leave the boss kill it by signal.
    """
    def __init__(self, process, boss, kind, address, params):
        Component.__init__(self, process, boss, kind)
        self._start_func = boss.start_msgq

    def stop_internal(self):
        pass # Wait for the boss to actually kill it. There's no stop command.

class CfgMgr(Component):
    def __init__(self, process, boss, kind, address, params):
        Component.__init__(self, process, boss, kind)
        self._start_func = boss.start_cfgmgr
        self._address = 'ConfigManager'

class Auth(Component):
    def __init__(self, process, boss, kind, address, params):
        Component.__init__(self, process, boss, kind)
        self._start_func = boss.start_auth
        self._address = 'Auth'

class Resolver(Component):
    def __init__(self, process, boss, kind, address, params):
        Component.__init__(self, process, boss, kind)
        self._start_func = boss.start_resolver
        self._address = 'Resolver'

class CmdCtl(Component):
    def __init__(self, process, boss, kind, address, params):
        Component.__init__(self, process, boss, kind)
        self._start_func = boss.start_cmdctl
        self._address = 'Cmdctl'

specials = {
    'sockcreator': SockCreator,
    'msgq': Msgq,
    'cfgmgr': CfgMgr,
    # TODO: Should these be replaced by configuration in config manager only?
    # They should not have any parameters anyway
    'auth': Auth,
    'resolver': Resolver,
    'cmdctl': CmdCtl
}
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
        starts and stops all the components as needed.
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
                        'command': 'stop',
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
                params = new[cname]
                creator = Component
                if 'special' in params:
                    # TODO: Better error handling
                    creator = specials[params['special']]
                component = creator(params.get('process', cname), self.__boss,
                                    params.get('kind', 'dispensable'),
                                    params.get('address'),
                                    params.get('params'))
                priority = params.get('priority', 0)
                # We store tuples, priority first, so we can easily sort
                plan_add.append((priority, {
                    'component': component,
                    'command': 'start',
                    'name': cname,
                }))
        # Push the starts there sorted by priority
        plan.extend([command for (_, command) in sorted(plan_add,
                                                        reverse=True,
                                                        key=lambda command:
                                                            command[0])])
        return plan

    def running(self):
        return self._running

    def _run_plan(self, plan):
        """
        Run a plan, created beforehead by _build_plan.

        With the start and stop commands, it also adds and removes components
        in _components.

        Currently implemented commands are:
        * start
        * stop
        """
        done = 0
        try:
            logger.debug(DBG_TRACE_DATA, BIND10_CONFIGURATOR_RUN, len(plan))
            for task in plan:
                component = task['component']
                command = task['command']
                logger.debug(DBG_TRACE_DETAILED, BIND10_CONFIGURATOR_TASK, command,
                             component.name())
                if command == 'start':
                    component.start()
                    self._components[task['name']] = component
                elif command == 'stop':
                    if component.running():
                        component.stop()
                    del self._components[task['name']]
                else:
                    # Can Not Happen (as the plans are generated by ourself).
                    # Therefore not tested.
                    raise NotImplementedError("Command unknown: " + command)
                done += 1
        except:
            logger.error(BIND10_CONFIGURATOR_PLAN_INTERRUPTED, done, len(plan))
            raise
