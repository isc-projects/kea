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
class ServeMixIn:
    '''Mix-In class to override the function serve_forever()
    and shutdown() in class socketserver::TCPServer.
      serve_forever() in socketserver.TCPServer use polling
    for checking request, which reduces the responsiveness to
    the shutdown request and wastes cpu at all other times.
      ServeMixIn should be used together with socketserver.TCPServer
    or some derived classes of it, and ServeMixIn must be the first
    base class in multiple inheritance, eg. MyClass(ServeMixIn,
    socketserver.TCPServer). ServeMixIn.__init__() should be called
    explicitely in derived class.
    '''
    def __init__(self):
        self.__read_sock, self.__write_sock = socket.socketpair()
        self.__is_shut_down = threading.Event()

    def serve_forever(self, poll_interval=None):
        ''' Override the serve_forever([poll_interval]) in class
        socketserver.TCPServer. use the socketpair to wake up
        the select when shutdown() is called in anther thread.
          Note, parameter 'poll_interval' is just used to keep the
        interface, it's never used in this function.
        '''        
        while True:
            # block until the self.socket or self.__read_sock is readable
            try:
                r, w, e = select.select([self, self.__read_sock], [], [])
            except select.error as err:
                if err.args[0] == EINTR:
                    continue
                else:
                    sys.stderr.write("Error with select(), %s\n", err)
                    break
            
            if self.__read_sock in r:
                break
            else:
                self._handle_request_noblock()

        self.__is_shut_down.set()                

    def shutdown(self):
        '''Stops the serve_forever loop.
        Blocks until the loop has finished, the function should be called
        in another thread when serve_forever is running, or it will block.
        '''
        self.__write_sock.send(SOCK_DATA) # make self.__read_sock readable.
        self.__is_shut_down.wait()  # wait until the serve thread terminate

