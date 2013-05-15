# Copyright (C) 2010  Internet Systems Consortium.
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

import threading
import socket
import select

SOCK_DATA = b'somedata'
class NoPollMixIn:
    '''This is a mix-in class to override the function serve_forever()
    and shutdown() in class socketserver.BaseServer.

    As commented in the module source code,  serve_forever() in
    socketserver.BaseServer uses polling for a shutdown request, which
    "reduces the responsiveness to a shutdown request and wastes cpu at
    all other times."

    This class fixes this problem by introducing internal message
    passing via a separate socket. Note, however, that according to
    the module documentation serve_forever() and shutdown() are not
    categorized as functions that can be overridden via mix-ins.  So
    this mix-in class may not be compatible with future versions of
    socketserver.  It should be considered a short term workaround
    until the original implementation is fixed.

    The NoPollMixIn class should be used together with
    socketserver.BaseServer or some derived classes of it, and it must
    be placed before the corresponding socketserver class.  In
    addition, the constructor of this mix-in must be called
    explicitly in the derived class.  For example, a basic TCP server
    without the problem of polling is created as follows:

       class MyServer(NoPollMixIn, socketserver.TCPServer):
           def __init__(...):
               ...
               NoPollMixIn.__init__(self)
               ...

    To shutdown the server correctly, the serve_forever() method must
    be run in a separate thread, and shutdown() must be called from
    some other thread.
    '''
    def __init__(self):
        self.__read_sock, self.__write_sock = socket.socketpair()
        self._is_shut_down = threading.Event()

    def serve_forever(self, poll_interval=None):
        ''' Overrides the serve_forever([poll_interval]) in class
        socketserver.BaseServer.

        It uses a socketpair to wake up the select when shutdown() is
        called in anther thread.  Note, parameter 'poll_interval' is
        just used for interface compatibility; it's never used in this
        function.
        '''
        while True:
            # block until the self.socket or self.__read_sock is readable
            try:
                r, w, e = select.select([self, self.__read_sock], [], [])
            except select.error as err:
                if err.args[0] == EINTR:
                    continue
                else:
                    break

            if self.__read_sock in r:
                break
            else:
                self._handle_request_noblock();

        self._is_shut_down.set()

    def shutdown(self):
        '''Stops the serve_forever loop.

        Blocks until the loop has finished, the function should be called
        in another thread when serve_forever is running, or it will block.
        '''
        self.__write_sock.send(SOCK_DATA) # make self.__read_sock readable.
        self._is_shut_down.wait()  # wait until the serve thread terminate
