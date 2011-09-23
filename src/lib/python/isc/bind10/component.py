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
        pass
    def start(self):
        """
        Start the component for the first time or restart it. If you need to
        modify the way a component is started, do not replace this method,
        but start_internal. This one does some more bookkeeping around.

        If you try to start an already running component, it raises ValueError.
        """
        pass
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
        pass
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
        pass
    def failed_internal(self):
        """
        This method is called from failed. You can replace it if you need
        some specific behaviour when the component crashes. The default
        implementation is empty.
        """
        pass
    def running(self):
        """
        Informs if the component is currently running. It assumes the failed
        is called whenever the component really fails and there might be some
        time in between actual failure and the call.
        """
        pass
