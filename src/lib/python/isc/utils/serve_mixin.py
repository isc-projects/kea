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

class ServeMixIn:
    '''Mix-In class to override the function serve_forever()
    and shutdown() in class socketserver. 
    '''
    _serving = False
    _is_shut_down = threading.Event()
    _read_sock, _write_sock = socket.socketpair()

    def serve_forever(self, poll_interval=0.5):
        ''' Override the serve_forever() in class BaseServer.
        use one socket pair to wake up the select when shutdown()
        is called in anther thread.
        '''        
        self._serving = True
        self._is_shut_down.clear()
        while self._serving:
            # block until the self.socket or self._read_sock is readable 
            try:
                r, w, e = select.select([self, self._read_sock], [], [])
            except select.error as err:
                if err.args[0] != EINTR:
                    raise
                else:
                    continue
            if r:
                if self._read_sock in r:
                    break
                else:
                    self._handle_request_noblock()

        self._is_shut_down.set()

    def shutdown(self):
        '''Stops the serve_forever loop.
        Blocks until the loop has finished, the function should be called
        in another thread when serve_forever is running, or it will block.
        '''
        self._serving = False
        self._write_sock.send(b'anydata') # make self._read_sock readable.
        self._is_shut_down.wait()

