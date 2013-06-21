# Copyright (C) 2013  Internet Systems Consortium.
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

class MemorySegmentBuilder:
    """The builder runs in a different thread in the memory manager. It
    waits for commands from the memory manager, and then executes them
    in the given order sequentially.
    """

    def __init__(self, sock, cv, lock, command_queue, response_queue):
        self._sock = sock
        self._cv = cv
        self._lock = lock
        self._command_queue = command_queue
        self._response_queue = response_queue
        self._shutdown = False

    def run(self):
        with self._cv:
            while not self._shutdown:
                while len(self._command_queue) == 0:
                    self._cv.wait()
                # move the queue content to a local queue
                with self._lock:
                    local_command_queue = self._command_queue.copy()
                    self._command_queue.clear()

                # run commands in the queue in the given order.  For
                # now, it only supports the "shutdown" command, which
                # just exits the thread.
                for command in local_command_queue:
                    if command == 'shutdown':
                        self._shutdown = True
                        break
                    raise Exception('Unknown command passed to ' +
                                    'MemorySegmentBuilder: ' + command)
