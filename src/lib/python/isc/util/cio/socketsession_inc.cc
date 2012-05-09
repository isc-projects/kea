namespace {
const char* const socketsession_doc = "\
This module defines a set of classes that support forwarding a\n\
\"socket session\" from one process to another.  A socket session is a\n\
conceptual tuple of the following elements:\n\
\n\
- A network socket\n\
- The local and remote endpoints of a (IP) communication taking place\n\
  on the socket. In practice an endpoint is a pair of an IP address\n\
  and TCP or UDP port number.\n\
- Some amount of data sent from the remote endpoint and received on\n\
  the socket. We call it (socket) session data in this documentation.\n\
\n\
Note that this is a conceptual definition. Depending on the underlying\n\
implementation and/or the network protocol, some of the elements could\n\
be part of others; for example, if it's an established TCP connection,\n\
the local and remote endpoints would be able to be retrieved from the\n\
socket using the standard getsockname() and getpeername() system\n\
calls. But in this definition we separate these to be more generic.\n\
Also, as a matter of fact our intended usage includes non-connected\n\
UDP communications, in which case at least the remote endpoint should\n\
be provided separately from the socket.\n\
\n\
In the actual implementation we represent a socket as a Python socket\n\
object, which contains the information of the address family\n\
(e.g. AF_INET6), socket type (e.g. SOCK_STREAM), and protocol\n\
(e.g. IPPROTO_TCP).\n\
\n\
We use the Python socket address tuple to represent endpoints.\n\
\n\
Socket session data is an opaque blob in the form of a Python byte\n\
object.\n\
\n\
To forward a socket session between processes, we use connected UNIX\n\
domain sockets established between the processes. The file descriptor\n\
will be forwarded through the sockets as an ancillary data item of\n\
type SCM_RIGHTS. Other elements of the session will be transferred as\n\
normal data over the connection.\n\
\n\
We provide two classes to help applications forward socket sessions:\n\
SocketSessionForwarder is the sender of the UNIX domain connection,\n\
while SocketSessionReceiver is the receiver (this interface assumes\n\
one direction of forwarding).\n\
\n\
Note: this paragraph and following discussions on the internal\n\
protocol are for reference purposes only; it's not necessary to\n\
understand how to use the API.\n\
SocketSessionForwarder and SocketSessionReceiver objects (internally)\n\
use a straightforward protocol to pass elements of socket sessions.\n\
Once the connection is established, the forwarder object first forwards\n\
the file descriptor with 1-byte dummy data.  It then forwards a\n\
\"(socket) session header\", which contains all other elements of\n\
the session except the file descriptor (already forwarded) and session\n\
data.  The wire format of the header is as follows:\n\
\n\
- The length of the header (16-bit unsigned integer)\n\
- Address family\n\
- Socket type\n\
- Protocol\n\
- Size of the local endpoint in bytes\n\
- Local endpoint (a copy of the memory image of the corresponding\n\
  sockaddr)\n\
- Size of the remote endpoint in bytes\n\
- Remote endpoint (same as local endpoint)\n\
- Size of session data in bytes\n\
\n\
The type of the fields is 32-bit unsigned integer unless explicitly\n\
noted, and all fields are formatted in the network byte order.\n\
\n\
The socket session data immediately follows the session header.\n\
\n\
Note that the fields do not necessarily be in the network byte order\n\
because they are expected to be exchanged on the same machine.\n\
Likewise, integer elements such as address family do not necessarily\n\
be represented as an fixed-size value (i.e., 32-bit). But fixed size\n\
fields are used in order to ensure maximum portability in such a\n\
(rare) case where the forwarder and the receiver are built with\n\
different compilers that have different definitions of int. Also,\n\
since sockaddr fields are generally formatted in the network byte\n\
order, other fields are defined so to be consistent.\n\
\n\
One basic assumption in the API of this module is socket sessions\n\
should be forwarded without blocking, thus eliminating the need for\n\
incremental read/write or blocking other important services such as\n\
responding to requests from the application's clients. This assumption\n\
should be held as long as both the forwarder and receiver have\n\
sufficient resources to handle the forwarding process since the\n\
communication is local. But a forward attempt could still block if the\n\
receiver is busy (or even hang up) and cannot keep up with the volume\n\
of incoming sessions.\n\
\n\
So, in this implementation, the forwarder uses non blocking writes to\n\
forward sessions. If a write attempt could block, it immediately gives\n\
up the operation with an exception. The corresponding application is\n\
expected to catch it, close the connection, and perform any necessary\n\
recovery for that application (that would normally be re-establish the\n\
connection with a new receiver, possibly after confirming the\n\
receiving side is still alive). On the other hand, the receiver\n\
implementation assumes it's possible that it only receive incomplete\n\
elements of a session (such as in the case where the forwarder writes\n\
part of the entire session and gives up the connection). The receiver\n\
implementation throws an exception when it encounters an incomplete\n\
session. Like the case of the forwarder application, the receiver\n\
application is expected to catch it, close the connection, and perform\n\
any necessary recovery steps.\n\
\n\
Note that the receiver implementation uses blocking read. So it's\n\
application's responsibility to ensure that there's at least some data\n\
in the connection when the receiver object is requested to receive a\n\
session (unless this operation can be blocking, e.g., by the use of a\n\
separate thread). Also, if the forwarder implementation or application\n\
is malicious or extremely buggy and intentionally sends partial\n\
session and keeps the connection, the receiver could block in\n\
receiving a session. In general, we assume the forwarder doesn't do\n\
intentional blocking as it's a local node and is generally a module of\n\
the same (BIND 10) system. The minimum requirement for the forwarder\n\
implementation (and application) is to make sure the connection is\n\
closed once it detects an error on it. Even a naive implementation\n\
that simply dies due to the exception will meet this requirement.\n\
\n\
";
} // unnamed namespace
