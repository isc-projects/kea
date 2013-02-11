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

from isc.bind10.component import Component, BaseComponent
import isc.bind10.sockcreator
from bind10_config import LIBEXECPATH
import os
import isc.log

class SockCreator(BaseComponent):
    """
    The socket creator component. Will start and stop the socket creator
    accordingly.

    Note: _creator shouldn't be reset explicitly once created.  The
    underlying Popen object would then wait() the child process internally,
    which breaks the assumption of b10-init, who is expecting to see
    the process die in waitpid().
    """
    def __init__(self, process, b10_init, kind, address=None, params=None):
        BaseComponent.__init__(self, b10_init, kind)
        self.__creator = None

    def _start_internal(self):
        self._b10_init.curproc = 'b10-sockcreator'
        self.__creator = isc.bind10.sockcreator.Creator(LIBEXECPATH + ':' +
                                                        os.environ['PATH'])
        self._b10_init.register_process(self.pid(), self)
        self._b10_init.set_creator(self.__creator)
        self._b10_init.log_started(self.pid())

        # We are now ready for switching user.
        self._b10_init.change_user()

    def _stop_internal(self):
        self.__creator.terminate()

    def name(self):
        return "Socket creator"

    def pid(self):
        """
        Pid of the socket creator. It is provided differently from a usual
        component.
        """
        return self.__creator.pid() if self.__creator else None

    def kill(self, forceful=False):
        # We don't really care about forceful here
        if self.__creator:
            self.__creator.kill()

class Msgq(Component):
    """
    The message queue. Starting is passed to b10-init, stopping is not
    supported and we leave b10-init kill it by signal.
    """
    def __init__(self, process, b10_init, kind, address=None, params=None):
        Component.__init__(self, process, b10_init, kind, None, None,
                           b10_init.start_msgq)

    def _stop_internal(self):
        """
        We can't really stop the message queue, as many processes may need
        it for their shutdown and it doesn't have a shutdown command anyway.
        But as it is stateless, it's OK to kill it.

        So we disable this method (as the only time it could be called is
        during shutdown) and wait for b10-init to kill it in the next shutdown
        step.

        This actually breaks the recommendation at Component we shouldn't
        override its methods one by one. This is a special case, because
        we don't provide a different implementation, we completely disable
        the method by providing an empty one. This can't hurt the internals.
        """
        pass

class CfgMgr(Component):
    def __init__(self, process, b10_init, kind, address=None, params=None):
        Component.__init__(self, process, b10_init, kind, 'ConfigManager',
                           None, b10_init.start_cfgmgr)

class Auth(Component):
    def __init__(self, process, b10_init, kind, address=None, params=None):
        Component.__init__(self, process, b10_init, kind, 'Auth', None,
                           b10_init.start_auth)

class Resolver(Component):
    def __init__(self, process, b10_init, kind, address=None, params=None):
        Component.__init__(self, process, b10_init, kind, 'Resolver', None,
                           b10_init.start_resolver)

class CmdCtl(Component):
    def __init__(self, process, b10_init, kind, address=None, params=None):
        Component.__init__(self, process, b10_init, kind, 'Cmdctl', None,
                           b10_init.start_cmdctl)
def get_specials():
    """
    List of specially started components. Each one should be the class than can
    be created for that component.
    """
    return {
        'sockcreator': SockCreator,
        'msgq': Msgq,
        'cfgmgr': CfgMgr,
        # TODO: Should these be replaced by configuration in config manager only?
        # They should not have any parameters anyway
        'auth': Auth,
        'resolver': Resolver,
        'cmdctl': CmdCtl
    }
