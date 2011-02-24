# Copyright (C) 2011  Internet Systems Consortium, Inc. ("ISC")
#
# Permission to use, copy, modify, and/or distribute this software for any
# purpose with or without fee is hereby granted, provided that the above
# copyright notice and this permission notice appear in all copies.
#
# THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES WITH
# REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
# AND FITNESS.  IN NO EVENT SHALL ISC BE LIABLE FOR ANY SPECIAL, DIRECT,
# INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
# LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
# OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
# PERFORMANCE OF THIS SOFTWARE.

$PREFIX ASIO_
$NAMESPACE asiolink

FETCHCOMP   upstream fetch to %s has now completed
+ A debug message, this records the the upstream fetch (a query made by the
+ resolver on behalf of its client) to the specified address has completed.

FETCHSTOP   upstream fetch to %s has been stopped
+ An external component has requested the halting of an upstream fetch.  This
+ is an allowed operation, and the message should only appear if debug is
+ enabled.

OPENSOCK    error %d opening %s socket to %s
+ The asynchronous I/O code encountered an error when trying to open a socket
+ of the specified protocol in order to send a message to the target address.
+ The the number of the system error that cause the problem is given in the
+ message.

RECVSOCK    error %d reading data from %s via a %s socket
+ The asynchronous I/O code encountered an error when trying read data from
+ the specified address on the given protocol.  The the number of the system
+ error that cause the problem is given in the message.

SENDSOCK    error %d sending data to %s via a %s socket
+ The asynchronous I/O code encountered an error when trying send data to
+ the specified address on the given protocol.  The the number of the system
+ error that cause the problem is given in the message.

RECVTMO     receive timeout while waiting for data from %s
+ An upstream fetch from the specified address timed out.  This may happen for
+ any number of reasons and is most probably a problem at the remote server
+ or a problem on the network.  The message will only appear if debug is
+ enabled.

UNKORIGIN  unknown origin for ASIO error code %d (protocol: %s, address %s)
+ This message should not appear and indicates an internal error if it does.
+ Please enter a bug report.

UNKRESULT  unknown result (%d) when IOFetch::stop() was executed for I/O to %s
+ The termination method of the resolver's upstream fetch class was called with
+ an unknown result code (which is given in the message).  This message should
+ not appear and may indicate an internal error.  Please enter a bug report.
