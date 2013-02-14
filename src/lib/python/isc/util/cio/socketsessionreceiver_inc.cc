// Copyright (C) 2012  Internet Systems Consortium, Inc. ("ISC")
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES WITH
// REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS.  IN NO EVENT SHALL ISC BE LIABLE FOR ANY SPECIAL, DIRECT,
// INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
// LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
// OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
// PERFORMANCE OF THIS SOFTWARE.

namespace {
// Modifications
//   - about return value
//   - socket session "utility" => module
const char* const SocketSessionReceiver_doc = "\
The receiver of socket sessions.\n\
\n\
An object of this class holds a UNIX domain socket for an established\n\
connection, receives socket sessions from the remote forwarder, and\n\
provides the session to the application as a tuple of corresponding\n\
elements.\n\
\n\
Note that this class is instantiated with an already connected socket;\n\
it's not a listening socket that is accepting connection requests from\n\
forwarders. It's application's responsibility to create the listening\n\
socket, listen on it and accept connections. Once the connection is\n\
established, the application would construct a SocketSessionReceiver\n\
object with the socket for the newly established connection. This\n\
behavior is based on the design decision that the application should\n\
decide when it performs (possibly) blocking operations (see\n\
socketsession module for more details).\n\
\n\
See the description of socketsession module for other details of how\n\
the session forwarding works.\n\
\n\
SocketSessionReceiver(socket)\n\
\n\
    The constructor.\n\
\n\
    Exceptions:\n\
      TypeError  The given parameter is not a valid socket object\n\
      SocketSessionError Any error on an operation that is performed\n\
                 on the given socket as part of initialization.\n\
      SystemError Unexpected errors such as resource allocation failure\n\
\n\
    Parameters:\n\
      socket     A python socket object of a UNIX domain family for an\n\
                 established connection with a forwarder.\n\
\n\
";

// Modifications
//  - socket session utility -> module
//  - return value (not a SocketSession object, but a Python tuple)
//  - remove the validity note (we copy it here, so there's no such
//    restriction)
//  - caller's responsibility: only responsible for closing the socket.
//  - text around the bullets
//  - exception
const char* const SocketSessionReceiver_pop_doc = "\
pop() -> (socket, socket address, socket address, byte)\n\
\n\
Receive a socket session from the forwarder.\n\
\n\
This method receives wire-format data (see socketsession module) for\n\
a socket session on the UNIX domain socket, performs some validation\n\
on the data, and returns the session information as a tuple.\n\
\n\
The caller is responsible for closing the received socket.\n\
\n\
It ensures the following:\n\
\n\
- The socket's address family is either AF_INET or AF_INET6\n\
- The family element of the socket addresses for the local and remote\n\
  end points must be equal to the socket's address family\n\
- The socket session data is not empty and does not exceed 65535\n\
  bytes.\n\
\n\
If the validation fails or an unexpected system error happens\n\
(including a connection close in the meddle of reception), it throws\n\
an SocketSessionError exception. When this happens, it's very\n\
unlikely that a subsequent call to this method succeeds, so in\n\
reality the application is expected to destruct it and close the\n\
socket in such a case.\n\
\n\
Exceptions:\n\
  SocketSessionError Invalid data is received or a system error on\n\
             socket operation happens.\n\
  SystemError Unexpected errors such as resource allocation failure\n\
\n\
Return Value(s): A tuple corresponding to the extracted socket session:\n\
  socket     A Python socket object corresponding to the socket passed\n\
             by the forwarder\n\
  socket address A Python socket address (which is a tuple) for the local\n\
             end point\n\
  socket address A Python socket address for the remote endpoint\n\
  data       A Python byte object that stores the session data\n\
";
} // unnamed namespace
