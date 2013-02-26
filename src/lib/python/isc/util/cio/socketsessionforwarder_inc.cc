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
// Modifications:
//  reference to the module description (instead of "utility")
//  exception description
const char* const SocketSessionForwarder_doc = "\
The forwarder of socket sessions.\n\
\n\
An object of this class maintains a UNIX domain socket (normally\n\
expected to be connected to a SocketSessionReceiver object) and\n\
forwards socket sessions to the receiver.\n\
\n\
See the description of socketsession module for other details of how\n\
the session forwarding works.\n\
\n\
SocketSessionForwarder(unix_file)\n\
\n\
    The constructor.\n\
\n\
    It's constructed with path information of the intended receiver,\n\
    but does not immediately establish a connection to the receiver;\n\
    connect_to_receiver() must be called to establish it. These are\n\
    separated so that an object of class can be initialized (possibly\n\
    as an attribute of a higher level application class object)\n\
    without knowing the receiver is ready for accepting new\n\
    forwarders. The separate connect interface allows the object to be\n\
    reused when it detects connection failure and tries to re-\n\
    establish it after closing the failed one.\n\
\n\
    On construction, it also installs a signal filter for SIGPIPE to\n\
    ignore it. Since this class uses a stream-type connected UNIX\n\
    domain socket, if the receiver (abruptly) closes the connection a\n\
    subsequent write operation on the socket would trigger a SIGPIPE\n\
    signal, which kills the caller process by default. This behavior\n\
    would be undesirable in many cases, so this implementation always\n\
    disables the signal.\n\
\n\
    This approach has some drawbacks, however; first, since signal\n\
    handling is process (or thread) wide, ignoring it may not what the\n\
    application wants. On the other hand, if the application changes\n\
    how the signal is handled after instantiating this class, the new\n\
    behavior affects the class operation. Secondly, even if ignoring\n\
    the signal is the desired operation, it's a waste to set the\n\
    filter every time this class object is constructed. It's\n\
    sufficient to do it once. We still adopt this behavior based on\n\
    the observation that in most cases applications would like to\n\
    ignore SIGPIPE (or simply doesn't care about it) and that this\n\
    class is not instantiated so often (so the wasteful setting\n\
    overhead should be marginal). On the other hand, doing it every\n\
    time is beneficial if the application is threaded and different\n\
    threads create different forwarder objects (and if signals work\n\
    per thread).\n\
\n\
    Exceptions:\n\
      SocketSessionError unix_file is invalid as a path name of a UNIX\n\
                 domain socket or error happens in setting a filter for\n\
                 SIGPIPE (see above)\n\
      SystemError Unexpected errors such as resource allocation failure\n\
\n\
    Parameters:\n\
      unix_file  Path name of the receiver.\n\
\n\
";

// Modifications:
//  exception description
const char* const SocketSessionForwarder_connectToReceiver_doc = "\
connect_to_receiver()\n\
\n\
Establish a connection to the receiver.\n\
\n\
This method establishes a connection to the receiver at the path given\n\
on construction. It makes the underlying UNIX domain socket non\n\
blocking, so this method (or subsequent push() calls) does not block.\n\
\n\
Exceptions:\n\
  TypeError  The method is called while an already established\n\
             connection is still active.\n\
  SocketSessionError A system error in socket operation.\n\
  SystemError Unexpected errors such as resource allocation failure\n\
\n\
";

// Modifications:
//  bullet description
//  parameters
//  exception description
const char* const SocketSessionForwarder_push_doc = "\
push(sock, family, type, protocol, local_end, remote_end, data)\n\
\n\
Forward a socket session to the receiver.\n\
\n\
This method takes a set of parameters that represent a single socket\n\
session, renders them in the \"wire\" format according to the internal\n\
protocol (see socketsession module) and forwards them to the\n\
receiver through the UNIX domain connection.\n\
\n\
The connection must have been established by connect_to_receiver().\n\
\n\
For simplicity and for the convenience of detecting application\n\
errors, this method imposes some restrictions on the parameters:\n\
\n\
- Socket family must be either AF_INET or AF_INET6\n\
- The address family (sa_family) member of the local and remote end\n\
  points must be equal to the family parameter\n\
- Socket session data must not be empty\n\
- Data length must not exceed 65535\n\
\n\
These are not architectural limitation, and might be loosened in future\n\
versions as we see the need for flexibility.\n\
\n\
Since the underlying UNIX domain socket is non blocking (see the\n\
description for the constructor), a call to this method should either\n\
return immediately or result in exception (in case of \"would\n\
block\").\n\
\n\
Exceptions:\n\
  TypeError  The method is called before establishing a connection or\n\
             given parameters are invalid, or the given socket address\n\
             is valid.\n\
  SocketSessionError A system error in socket operation, including the\n\
             case where the write operation would block.\n\
\n\
Parameters:\n\
  sock       (int) The socket file descriptor\n\
  family     (int) The address family (such as socket.AF_INET6) of the\n\
             socket\n\
  type       (int) The socket type (such as socket.SOCK_DGRAM) of the\n\
             socket\n\
  protocol   (int) The transport protocol (such as socket.IPPROTO_UDP)\n\
             of the socket\n\
  local_end  (socket address) The local end point of the session\n\
  remote_end (socket address) The remote end point of the session\n\
  data       (byte) the session data\n\
\n\
";
} // unnamed namespace
