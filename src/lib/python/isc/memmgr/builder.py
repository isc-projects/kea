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
        """ The constructor takes the following arguments:

            sock: A socket using which this builder object notifies the
                  main thread that it has a response waiting for it.

            cv: A condition variable object that is used by the main
                thread to tell this builder object that new commands are
                available to it.

            lock: A lock object which should be acquired before using or
                  modifying the contents of command_queue and
                  response_queue.

            command_queue: A list of commands sent by the main thread to
                           this object. Commands should be executed
                           sequentially in the given order by this
                           object.

            response_queue: A list of responses sent by this object to
                            the main thread. The format of this is
                            currently not strictly defined. Future
                            tickets will be able to define it based on
                            how it's used.
        """

        self._sock = sock
        self._cv = cv
        self._lock = lock
        self._command_queue = command_queue
        self._response_queue = response_queue
        self._shutdown = False

    def run(self):
        """ This is the method invoked when the builder thread is
            started.  In this thread, be careful when modifying
            variables passed-by-reference in the constructor. If they are
            reassigned, they will not refer to the main thread's objects
            any longer. Any use of command_queue and response_queue must
            be synchronized by acquiring the lock. This method must
            normally terminate only when the 'shutdown' command is sent
            to it.
        """

        # Acquire the condition variable while running the loop.
        with self._cv:
            while not self._shutdown:
                while len(self._command_queue) == 0:
                    self._cv.wait()
                # Move the queue content to a local queue. Be careful of
                # not making assignments to reference variables.
                with self._lock:
                    local_command_queue = self._command_queue.copy()
                    self._command_queue.clear()

                # Run commands passed in the command queue sequentially
                # in the given order.  For now, it only supports the
                # "shutdown" command, which just exits the thread.
                for command in local_command_queue:
                    if command == 'shutdown':
                        self._shutdown = True
                        # When the shutdown command is received, we do
                        # not process any further commands.
                        break
                    else:
                        # A bad command was received. Raising an
                        # exception is not useful in this case as we are
                        # likely running in a different thread from the
                        # main thread which would need to be
                        # notified. Instead return this in the response
                        # queue.
                        with self._lock:
                            self._response_queue.append('bad_command')
                            # In this case, we do not notify the main
                            # thread about a response on the socket, as
                            # we quit the main loop here anyway (and any
                            # enclosing thread).
                            self._shutdown = True
                            break
