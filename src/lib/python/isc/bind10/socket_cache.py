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
Here's the cache for sockets from socket creator.
"""

import os
import random
import isc.bind10.sockcreator
from copy import copy

class SocketError(Exception):
    """
    Exception raised when the socket creator is unable to create requested
    socket. Possible reasons might be the address it should be bound to
    is already taken, the permissions are insufficient, the address family
    is not supported on this computer and many more.

    The errno, if not None, is passed from the socket creator.
    """
    def __init__(self, message, errno):
        Exception.__init__(self, message)
        self.errno = errno

class ShareError(Exception):
    """
    The requested socket is already taken by other component and the sharing
    parameters don't allow sharing with the new request.
    """
    pass

class Socket:
    """
    This represents one socket cached by the cache program. This should never
    be used directly by a user, it is used internally by the Cache. Therefore
    many member variables are used directly instead of by a accessor method.

    Be warned that this object implements the __del__ method. It closes the
    socket held inside in it. But this poses various problems with garbage
    collector. In short, do not make reference cycles with this and generally
    leave this class alone to live peacefully.
    """
    def __init__(self, protocol, address, port, fileno):
        """
        Creates the socket.

        The protocol, address and port are preserved for the information.
        """
        self.protocol = protocol
        self.address = address
        self.port = port
        self.fileno = fileno
        # Mapping from token -> application
        self.active_tokens = {}
        # The tokens which were not yet picked up
        self.waiting_tokens = set()
        # Share modes and names by the tokens (token -> (mode, name))
        self.shares = {}

    def __del__(self):
        """
        Closes the file descriptor.
        """
        os.close(self.fileno)

    def share_compatible(self, mode, name):
        """
        Checks if the given share mode and name is compatible with the ones
        already installed here.

        The allowed values for mode are listed in the Cache.get_token
        function.
        """
        if mode not in ['NO', 'SAMEAPP', 'ANY']:
            raise ValueError("Mode " + mode + " is invalid")

        # Go through the existing ones
        for (emode, ename) in self.shares.values():
            if emode == 'NO' or mode == 'NO':
                # One of them can't live together with anything
                return False
            if (emode == 'SAMEAPP' or mode == 'SAMEAPP') and \
                ename != name:
                # One of them can't live together with someone of different
                # name
                return False
            # else both are ANY or SAMEAPP with the same name, which is OK
        # No problem found, so we consider it OK
        return True

class Cache:
    """
    This is the cache for sockets from socket creator. The purpose of cache
    is to hold the sockets that were requested, until they are no longer
    needed. One reason is, the socket is created before it is sent over the
    unix domain socket in boss, so we need to keep it somewhere for a while.

    The other reason is, a single socket might be requested multiple times.
    So we keep it here in case someone else might ask for it.

    Each socket kept here has a reference count and when it drops to zero,
    it is removed from cache and closed.

    This is expected to be part of Boss, it is not a general utility class.

    It is not expected to be subclassed. The methods and members are named
    as protected so tests are easier access into them.
    """
    def __init__(self, creator):
        """
        Initialization. The creator is the socket creator object
        (isc.bind10.sockcreator.Creator) which will be used to create yet
        uncached sockets.
        """
        self._creator = creator
        # The sockets we have live here, these dicts are various ways how
        # to get them. Each of them contains the Socket objects somehow

        # This one is dict of token: socket for the ones that were not yet
        # picked up by an application.
        self._waiting_tokens = {}
        # This format is the same as above, but for the tokens that were
        # already picked up by the application and not yet released.
        self._active_tokens = {}
        # This is a dict from applications to set of tokens used by the
        # application, for the sockets already picked up by an application
        self._active_apps = {}
        # The sockets live here to be indexed by protocol, address and
        # subsequently by port
        self._sockets = {}
        # These are just the tokens actually in use, so we don't generate
        # dupes. If one is dropped, it can be potentially reclaimed.
        self._live_tokens = set()

    def get_token(self, protocol, address, port, share_mode, share_name):
        """
        This requests a token representing a socket. The socket is either
        found in the cache already or requested from the creator at this time
        (and cached for later time).

        The parameters are:
        - protocol: either 'UDP' or 'TCP'
        - address: the IPAddr object representing the address to bind to
        - port: integer saying which port to bind to
        - share_mode: either 'NO', 'SAMEAPP' or 'ANY', specifying how the
          socket can be shared with others. See bin/bind10/creatorapi.txt
          for details.
        - share_name: the name of application, in case of 'SAMEAPP' share
          mode. Only requests with the same name can share the socket.

        If the call is successful, it returns a string token which can be
        used to pick up the socket later. The socket is created with reference
        count zero and if it isn't picked up soon enough (the time yet has to
        be set), it will be removed and the token is invalid.

        It can fail in various ways. Explicitly listed exceptions are:
        - SocketError: this one is thrown if the socket creator couldn't provide
          the socket and it is not yet cached (it belongs to other application,
          for example).
        - ShareError: the socket is already in the cache, but it can't be
          shared due to share_mode and share_name combination (both the request
          restrictions and of all copies of socket handed out are considered,
          so it can be raised even if you call it with share_mode 'ANY').
        - isc.bind10.sockcreator.CreatorError: fatal creator errors are
          propagated. Thay should cause the boss to exit if ever encountered.

        Note that it isn't guaranteed the tokens would be unique and they
        should be used as an opaque handle only.
        """
        addr_str = str(address)
        try:
            socket = self._sockets[protocol][addr_str][port]
        except KeyError:
            # Something in the dicts is not there, so socket is to be
            # created
            try:
                fileno = self._creator.get_socket(address, port, protocol)
            except isc.bind10.sockcreator.CreatorError as ce:
                if ce.fatal:
                    raise
                else:
                    raise SocketError(str(ce), ce.errno)
            socket = Socket(protocol, address, port, fileno)
            # And cache it
            if protocol not in self._sockets:
                self._sockets[protocol] = {}
            if addr_str not in self._sockets[protocol]:
                self._sockets[protocol][addr_str] = {}
            self._sockets[protocol][addr_str][port] = socket
        # Now we get the token, check it is compatible
        if not socket.share_compatible(share_mode, share_name):
            raise ShareError("Cached socket not compatible with mode " +
                             share_mode + " and name " + share_name)
        # Grab yet unused token
        token = 't' + str(random.randint(0, 2 ** 32-1))
        while token in self._live_tokens:
            token = 't' + str(random.randint(0, 2 ** 32-1))
        self._waiting_tokens[token] = socket
        self._live_tokens.add(token)
        socket.shares[token] = (share_mode, share_name)
        socket.waiting_tokens.add(token)
        return token

    def get_socket(self, token, application):
        """
        This returns the socket created by get_token. The token should be the
        one returned from previous call from get_token. The token can be used
        only once to receive the socket.

        The application is a token representing the application that requested
        it. Currently, boss uses the file descriptor of connection from the
        application, but anything which can be a key in a dict is OK from the
        cache's point of view. You just need to use the same thing in
        drop_application.

        In case the token is considered invalid (it doesn't come from the
        get_token, it was already used, the socket wasn't picked up soon
        enough, ...), it raises ValueError.
        """
        try:
            socket = self._waiting_tokens[token]
        except KeyError:
            raise ValueError("Token " + token +
                             " isn't waiting to be picked up")
        del self._waiting_tokens[token]
        self._active_tokens[token] = socket
        if application not in self._active_apps:
            self._active_apps[application] = set()
        self._active_apps[application].add(token)
        socket.waiting_tokens.remove(token)
        socket.active_tokens[token] = application
        return socket.fileno

    def drop_socket(self, token):
        """
        This signals the application no longer uses the socket which was
        requested by the given token. It decreases the reference count for
        the socket and closes and removes the cached copy if it was the last
        one.

        It raises ValueError if the token doesn't exist.
        """
        try:
            socket = self._active_tokens[token]
        except KeyError:
            raise ValueError("Token " + token + " doesn't represent an " +
                             "active socket")
        # Now, remove everything from the bookkeeping
        del socket.shares[token]
        app = socket.active_tokens[token]
        del socket.active_tokens[token]
        del self._active_tokens[token]
        self._active_apps[app].remove(token)
        if len(self._active_apps[app]) == 0:
            del self._active_apps[app]
        self._live_tokens.remove(token)
        # The socket is not used by anything now, so remove it
        if len(socket.active_tokens) == 0 and len(socket.waiting_tokens) == 0:
            addr = str(socket.address)
            port = socket.port
            proto = socket.protocol
            del self._sockets[proto][addr][port]
            # Clean up empty branches of the structure
            if len(self._sockets[proto][addr]) == 0:
                del self._sockets[proto][addr]
            if len(self._sockets[proto]) == 0:
                del self._sockets[proto]

    def drop_application(self, application):
        """
        This signals the application terminated and all sockets it picked up
        should be considered unused by it now. It effectively calls drop_socket
        on each of the sockets the application picked up and didn't drop yet.

        If the application is invalid (no get_socket was successful with this
        value of application), it raises ValueError.
        """
        try:
            # Get a copy. Who knows how iteration works through sets if we
            # delete from it during the time, so we'll just have our own copy
            # to iterate
            to_drop = copy(self._active_apps[application])
        except KeyError:
            raise ValueError("Application " + str(application) +
                             " doesn't hold any sockets")
        for token in to_drop:
            self.drop_socket(token)
        # We don't call del now. The last drop_socket should have
        # removed the application key as well.
