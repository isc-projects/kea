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

class SocketError(Exception):
    """
    Exception raised when the socket creator is unable to create requested
    socket. Possible reasons might be the address it should be bound to
    is already taken, the permissions are insufficient, the address family
    is not supported on this computer and many more.
    """
    pass

class ShareError(Exception):
    """
    The requested socket is already taken by other component and the sharing
    parameters don't allow sharing with the new request.
    """
    pass

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
    """
    def __init__(self, creator):
        """
        Initialization. The creator is the socket creator object
        (isc.bind10.sockcreator.Creator) which will be used to create yet
        uncached sockets.
        """
        # Full implementation and tests are in #1427. This is just because
        # of a boss test.
        self._creator = creator

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
        pass

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
        pass

    def drop_socket(self, token):
        """
        This signals the application no longer uses the socket which was
        requested by the given token. It decreases the reference count for
        the socket and closes and removes the cached copy if it was the last
        one.

        It raises ValueError if the token doesn't exist.
        """
        pass

    def drop_application(self, application):
        """
        This signals the application terminated and all socket it picked up
        should be considered unused by it now. It effectively calls drop_socket
        on each of the sockets the application picked up and didn't drop yet.

        If the application is invalid (no get_socket was successful with this
        value of application), it raises ValueError.
        """
        pass
