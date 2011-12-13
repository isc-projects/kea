// Copyright (C) 2011  Internet Systems Consortium, Inc. ("ISC")
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

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <netdb.h>
#include <unistd.h>

#include <string>
#include <utility>
#include <vector>

#include <boost/noncopyable.hpp>

#include <gtest/gtest.h>

#include <exceptions/exceptions.h>

#include <util/io/socketsession.h>
#include <util/io/sockaddr_util.h>

using namespace std;
using namespace isc;
using namespace isc::util::io;
using namespace isc::util::io::internal;

namespace {

const char* const TEST_UNIX_FILE = TEST_DATA_BUILDDIR "/test.unix";
const char* const TEST_PORT = "53535";
const char TEST_DATA[] = "BIND10 test";

// A simple helper structure to automatically close test sockets on return
// or exception in a RAII manner.  non copyable to prevent duplicate close.
struct ScopedSocket : boost::noncopyable {
    ScopedSocket() : fd(-1) {}
    ScopedSocket(int sock) : fd(sock) {}
    ~ScopedSocket() {
        closeSocket();
    }
    void reset(int sock) {
        closeSocket();
        fd = sock;
    }
    int fd;
private:
    void closeSocket() {
        if (fd >= 0) {
            close(fd);
        }
    }
};

// A helper function that makes a test socket non block so that a certain
// kind of test failure (such as missing send) won't cause hangup.
void
setNonBlock(int s, bool on) {
    int fcntl_flags = fcntl(s, F_GETFL, 0);
    if (on) {
        fcntl_flags |= O_NONBLOCK;
    } else {
        fcntl_flags &= ~O_NONBLOCK;
    }
    if (fcntl(s, F_SETFL, fcntl_flags) == -1) {
        isc_throw(isc::Unexpected, "fcntl(O_NONBLOCK) failed: " <<
                  strerror(errno));
    }
}

// A helper to impose some reasonable amount of wait on recv(from)
// if possible.  It returns an option flag to be set for the system call
// (when necessary).
int
setRecvDelay(int s) {
    const struct timeval timeo = { 10, 0 };
    if (setsockopt(s, SOL_SOCKET, SO_RCVTIMEO, &timeo, sizeof(timeo)) == -1) {
        if (errno == ENOPROTOOPT) {
            // Workaround for Solaris: see recursive_query_unittest
            return (MSG_DONTWAIT);
        } else {
            isc_throw(isc::Unexpected, "set RCVTIMEO failed: " <<
                      strerror(errno));
        }
    }
    return (0);
}

// A shortcut type that is convenient to be used for socket related
// system calls, which generally require this pair
typedef pair<const struct sockaddr*, socklen_t> SockAddrInfo;

// A helper class to convert textual representation of IP address and port
// to a pair of sockaddr and its length (in the form of a SockAddrInfo
// pair).  Its get method uses getaddrinfo(3) for the conversion and stores
// the result in the addrinfo_list_ vector until the object is destructed.
// The allocated resources will be automatically freed in an RAII manner.
class SockAddrCreator {
public:
    ~SockAddrCreator() {
        vector<struct addrinfo*>::const_iterator it;
        for (it = addrinfo_list_.begin(); it != addrinfo_list_.end(); ++it) {
            freeaddrinfo(*it);
        }
    }
    SockAddrInfo get(const string& addr_str, const string& port_str) {
        struct addrinfo hints, *res;
        memset(&hints, 0, sizeof(hints));
        hints.ai_flags = AI_NUMERICHOST | AI_NUMERICSERV;
        hints.ai_family = AF_UNSPEC;
        hints.ai_socktype = SOCK_DGRAM; // could be either DGRAM or STREAM here
        const int error = getaddrinfo(addr_str.c_str(), port_str.c_str(),
                                      &hints, &res);
        if (error != 0) {
            isc_throw(isc::Unexpected, "getaddrinfo failed for " <<
                      addr_str << ", " << port_str << ": " <<
                      gai_strerror(error));
        }

        // Technically, this is not entirely exception safe; if push_back
        // throws, the resources allocated for 'res' will leak.  We prefer
        // brevity here and ignore the minor failure mode.
        addrinfo_list_.push_back(res);

        return (SockAddrInfo(res->ai_addr, res->ai_addrlen));
    }
private:
    vector<struct addrinfo*> addrinfo_list_;
};

class ForwarderTest : public ::testing::Test {
protected:
    ForwarderTest() : listen_fd_(-1), forwarder_(TEST_UNIX_FILE),
                      large_text_(65535, 'a'),
                      test_un_len_(2 + strlen(TEST_UNIX_FILE))
    {
        unlink(TEST_UNIX_FILE);
        test_un_.sun_family = AF_UNIX;
        strncpy(test_un_.sun_path, TEST_UNIX_FILE, sizeof(test_un_.sun_path));
#ifdef HAVE_SA_LEN
        test_un_.sun_len = test_un_len_;
#endif
    }

    ~ForwarderTest() {
        if (listen_fd_ != -1) {
            close(listen_fd_);
        }
        unlink(TEST_UNIX_FILE);
    }

    // Start an internal "socket session server".
    void startListen() {
        if (listen_fd_ != -1) {
            isc_throw(isc::Unexpected, "duplicate call to startListen()");
        }
        listen_fd_ = socket(AF_UNIX, SOCK_STREAM, 0);
        if (listen_fd_ == -1) {
            isc_throw(isc::Unexpected, "failed to create UNIX domain socket" <<
                      strerror(errno));
        }
        if (bind(listen_fd_, convertSockAddr(&test_un_), test_un_len_) == -1) {
            isc_throw(isc::Unexpected, "failed to bind UNIX domain socket" <<
                      strerror(errno));
        }
        // 10 is an arbitrary choice, should be sufficient for a single test
        if (listen(listen_fd_, 10) == -1) {
            isc_throw(isc::Unexpected, "failed to listen on UNIX domain socket"
                      << strerror(errno));
        }
    }

    // Accept a new connection from a SocketSessionForwarder and return
    // the socket FD of the new connection.  This assumes startListen()
    // has been called.
    int acceptForwarder() {
        setNonBlock(listen_fd_, true); // prevent the test from hanging up
        struct sockaddr_un from;
        socklen_t from_len = sizeof(from);
        const int s = accept(listen_fd_, convertSockAddr(&from), &from_len);
        if (s == -1) {
            isc_throw(isc::Unexpected, "accept failed: " << strerror(errno));
        }
        return (s);
    }

    // A convenient shortcut for the namespace-scope version of getSockAddr
    SockAddrInfo getSockAddr(const string& addr_str, const string& port_str) {
        return (addr_creator_.get(addr_str, port_str));
    }

    // A helper method that creates a specified type of socket that is
    // supposed to be passed via a SocketSessionForwarder.  It will bound
    // to the specified address and port in sainfo.  If do_listen is true
    // and it's a TCP socket, it will also start listening to new connection
    // requests.
    int createSocket(int family, int type, int protocol,
                     const SockAddrInfo& sainfo, bool do_listen) 
    {
        int s = socket(family, type, protocol);
        if (s < 0) {
            isc_throw(isc::Unexpected, "socket(2) failed: " <<
                      strerror(errno));
        }
        const int on = 1;
        if (setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) == -1) {
            isc_throw(isc::Unexpected, "setsockopt(SO_REUSEADDR) failed: " <<
                      strerror(errno));
        }
        if (bind(s, sainfo.first, sainfo.second) < 0) {
            close(s);
            isc_throw(isc::Unexpected, "bind(2) failed: " <<
                      strerror(errno));
        }
        if (do_listen && protocol == IPPROTO_TCP) {
            if (listen(s, 1) == -1) {
                isc_throw(isc::Unexpected, "listen(2) failed: " <<
                          strerror(errno));
            }
        }
        return (s);
    }

    // See below
    void checkPushAndPop(int family, int type, int protocoal,
                         const SockAddrInfo& local,
                         const SockAddrInfo& remote, const void* const data,
                         size_t data_len, bool new_connection);

protected:
    int listen_fd_;
    SocketSessionForwarder forwarder_;
    ScopedSocket accept_sock_;
    const string large_text_;

private:
    struct sockaddr_un test_un_;
    const socklen_t test_un_len_;
    SockAddrCreator addr_creator_;
};

TEST_F(ForwarderTest, construct) {
    // On construction the existence of the file doesn't matter.
    SocketSessionForwarder("some_file");

    // But too long a path should be rejected
    struct sockaddr_un s;     // can't be const; some compiler complains
    EXPECT_THROW(SocketSessionForwarder(string(sizeof(s.sun_path), 'x')),
                 SocketSessionError);
    // If it's one byte shorter it should be okay
    SocketSessionForwarder(string(sizeof(s.sun_path) - 1, 'x'));
}

TEST_F(ForwarderTest, connect) {
    // File doesn't exist (we assume the file "no_such_file" doesn't exist)
    SocketSessionForwarder forwarder("no_such_file");
    EXPECT_THROW(forwarder.connectToReceptor(), SocketSessionError);
    // The socket should be closed internally, so close() should result in
    // error.
    EXPECT_THROW(forwarder.close(), SocketSessionError);

    // Set up the receptor and connect.  It should succeed.
    SocketSessionForwarder forwarder2(TEST_UNIX_FILE);
    startListen();
    forwarder2.connectToReceptor();
    // And it can be closed successfully.
    forwarder2.close();
    // Duplicate close should fail
    EXPECT_THROW(forwarder2.close(), SocketSessionError);
    // Once closed, reconnect is okay.
    forwarder2.connectToReceptor();
    forwarder2.close();

    // Duplicate connect should be rejected
    forwarder2.connectToReceptor();
    EXPECT_THROW(forwarder2.connectToReceptor(), SocketSessionError);

    // Connect then destroy.  Should be internally closed, but unfortunately
    // it's not easy to test it directly.  We only check no disruption happens.
    SocketSessionForwarder* forwarderp =
        new SocketSessionForwarder(TEST_UNIX_FILE);
    forwarderp->connectToReceptor();
    delete forwarderp;
}

TEST_F(ForwarderTest, close) {
    // can't close before connect
    EXPECT_THROW(SocketSessionForwarder(TEST_UNIX_FILE).close(),
                 SocketSessionError);
}

void
checkSockAddrs(const sockaddr& expected, const sockaddr& actual) {
    char hbuf_expected[NI_MAXHOST], sbuf_expected[NI_MAXSERV],
        hbuf_actual[NI_MAXHOST], sbuf_actual[NI_MAXSERV];
    EXPECT_EQ(0, getnameinfo(&expected, getSALength(expected),
                             hbuf_expected, sizeof(hbuf_expected),
                             sbuf_expected, sizeof(sbuf_expected),
                             NI_NUMERICHOST | NI_NUMERICSERV));
    EXPECT_EQ(0, getnameinfo(&actual, getSALength(actual),
                             hbuf_actual, sizeof(hbuf_actual),
                             sbuf_actual, sizeof(sbuf_actual),
                             NI_NUMERICHOST | NI_NUMERICSERV));
    EXPECT_EQ(string(hbuf_expected), string(hbuf_actual));
    EXPECT_EQ(string(sbuf_expected), string(sbuf_actual));
}

// This is a commonly used test case that confirms normal behavior of
// session passing.  It first creates a "local" socket (which is supposed
// to act as a "server") bound to the 'local' parameter.  It then forwards
// the descriptor of the FD of the local socket along with given data.
// Next, it creates an Receptor object to receive the forwarded FD itself,
// receives the FD, and sends test data from the received FD.  The
// test finally checks if it can receive the test data from the local socket
// at the Forwarder side.  In the case of TCP it's a bit complicated because
// it first needs to establish a new connection, but essentially the test
// scenario is the same.  See the diagram below for more details.
//
// UDP:
//   Forwarder          Receptor
//   sock -- (pass) --> passed_sock
//   (check)  <-------- send TEST_DATA
//
// TCP:
//   Forwarder               Receptor
//   server_sock---(pass)--->passed_sock
//     ^                        |
//     |(connect)               |
//   client_sock                |
//      (check)<---------send TEST_DATA
void
ForwarderTest::checkPushAndPop(int family, int type, int protocol,
                               const SockAddrInfo& local,
                               const SockAddrInfo& remote,
                               const void* const data,
                               size_t data_len, bool new_connection)
{
    // Create an original socket to be passed
    const ScopedSocket sock(createSocket(family, type, protocol, local, true));
    int fwd_fd = sock.fd;       // default FD to be forwarded
    ScopedSocket client_sock;   // for TCP test we need a separate "client"..
    ScopedSocket server_sock;   // ..and a separate socket for the connection
    if (protocol == IPPROTO_TCP) {
        // Use unspecified port for the "client" to avoid bind(2) failure
        const SockAddrInfo client_addr = getSockAddr(family == AF_INET6 ?
                                                     "::1" : "127.0.0.1", "0");
        client_sock.reset(createSocket(family, type, protocol, client_addr,
                                       false));
        setNonBlock(client_sock.fd, true);
        // This connect would "fail" due to EINPROGRESS.  Ignore it for now.
        connect(client_sock.fd, local.first, local.second);
        sockaddr_storage ss;
        socklen_t salen = sizeof(ss);
        server_sock.reset(accept(sock.fd, convertSockAddr(&ss), &salen));
        if (server_sock.fd == -1) {
            isc_throw(isc::Unexpected, "internal accept failed: " <<
                      strerror(errno));
        }
        fwd_fd = server_sock.fd;
    }

    // If a new connection is required, start the "server", have the
    // internal forwarder connect to it, and then internally accept it.
    if (new_connection) {
        startListen();
        forwarder_.connectToReceptor();
        accept_sock_.reset(acceptForwarder());

        // Make sure the socket is *blocking*.  We may pass large data, through
        // it, and apparently non blocking read could cause some unexpected
        // partial read on some systems.
        setNonBlock(accept_sock_.fd, false);
    }

    // Then push one socket session via the forwarder.
    forwarder_.push(fwd_fd, family, type, protocol, *local.first,
                    *remote.first, data, data_len);

    // Pop the socket session we just pushed from a local receptor, and
    // check the content.  Since we do blocking read on the receptor's socket,
    // we set up an alarm to prevent hangup in case there's a bug that really
    // makes the blocking happen.
    SocketSessionReceptor receptor(accept_sock_.fd);
    alarm(1);                   // set up 1-sec timer, an arbitrary choice.
    const SocketSession sock_session = receptor.pop();
    alarm(0);                   // then cancel it.
    const ScopedSocket passed_sock(sock_session.getSocket());
    EXPECT_LE(0, passed_sock.fd);
    // The passed FD should be different from the original FD
    EXPECT_NE(fwd_fd, passed_sock.fd);
    EXPECT_EQ(family, sock_session.getFamily());
    EXPECT_EQ(type, sock_session.getType());
    EXPECT_EQ(protocol, sock_session.getProtocol());
    checkSockAddrs(*local.first, sock_session.getLocalEndpoint());
    checkSockAddrs(*remote.first, sock_session.getRemoteEndpoint());
    ASSERT_EQ(data_len, sock_session.getDataLength());
    EXPECT_EQ(0, memcmp(data, sock_session.getData(), data_len));

    // Check if the passed FD is usable by sending some data from it.
    setNonBlock(passed_sock.fd, false);
    if (protocol == IPPROTO_UDP) {
        EXPECT_EQ(sizeof(TEST_DATA),
                  sendto(passed_sock.fd, TEST_DATA, sizeof(TEST_DATA), 0,
                         convertSockAddr(local.first), local.second));
    } else {
        server_sock.reset(-1);
        EXPECT_EQ(sizeof(TEST_DATA),
                  send(passed_sock.fd, TEST_DATA, sizeof(TEST_DATA), 0));
    }
    // We don't use non blocking read below as it doesn't seem to be always
    // reliable.  Instead we impose some reasonably large upper time limit of
    // blocking (normally it shouldn't even block at all; the limit is to
    // force the test to stop even if there's some bug and recv fails).
    char recvbuf[sizeof(TEST_DATA)];
    sockaddr_storage ss;
    socklen_t sa_len = sizeof(ss);
    if (protocol == IPPROTO_UDP) {
        EXPECT_EQ(sizeof(recvbuf),
                  recvfrom(fwd_fd, recvbuf, sizeof(recvbuf),
                           setRecvDelay(fwd_fd), convertSockAddr(&ss),
                           &sa_len));
    } else {
        setNonBlock(client_sock.fd, false);
        EXPECT_EQ(sizeof(recvbuf),
                  recv(client_sock.fd, recvbuf, sizeof(recvbuf),
                       setRecvDelay(client_sock.fd)));
    }
    EXPECT_EQ(string(TEST_DATA), string(recvbuf));
}

TEST_F(ForwarderTest, pushAndPop) {
    // Pass a UDP/IPv6 session.
    const SockAddrInfo sai_local6(getSockAddr("::1", TEST_PORT));
    const SockAddrInfo sai_remote6(getSockAddr("2001:db8::1", "5300"));
    {
        SCOPED_TRACE("Passing UDP/IPv6 session");
        checkPushAndPop(AF_INET6, SOCK_DGRAM, IPPROTO_UDP, sai_local6,
                        sai_remote6, TEST_DATA, sizeof(TEST_DATA), true);
    }
    // Pass a TCP/IPv6 session.
    {
        SCOPED_TRACE("Passing TCP/IPv6 session");
        checkPushAndPop(AF_INET6, SOCK_STREAM, IPPROTO_TCP, sai_local6,
                        sai_remote6, TEST_DATA, sizeof(TEST_DATA), false);
    }

    // Pass a UDP/IPv4 session.  This reuses the same pair of forwarder and
    // receptor, which should be usable for multiple attempts of passing,
    // regardless of family of the passed session
    const SockAddrInfo sai_local4(getSockAddr("127.0.0.1", TEST_PORT));
    const SockAddrInfo sai_remote4(getSockAddr("192.0.2.2", "5300"));
    {
        SCOPED_TRACE("Passing UDP/IPv4 session");
        checkPushAndPop(AF_INET, SOCK_DGRAM, IPPROTO_UDP, sai_local4,
                        sai_remote4, TEST_DATA, sizeof(TEST_DATA), false);
    }
    // Pass a TCP/IPv4 session.
    {
        SCOPED_TRACE("Passing TCP/IPv4 session");
        checkPushAndPop(AF_INET, SOCK_STREAM, IPPROTO_TCP, sai_local4,
                        sai_remote4, TEST_DATA, sizeof(TEST_DATA), false);
    }

    // Also try large data
    {
        SCOPED_TRACE("Passing UDP/IPv6 session with large data");
        checkPushAndPop(AF_INET6, SOCK_DGRAM, IPPROTO_UDP, sai_local6,
                        sai_remote6, large_text_.c_str(), large_text_.length(),
                        false);
    }
    {
        SCOPED_TRACE("Passing TCP/IPv6 session with large data");
        checkPushAndPop(AF_INET6, SOCK_STREAM, IPPROTO_TCP, sai_local6,
                        sai_remote6, large_text_.c_str(), large_text_.length(),
                        false);
    }
    {
        SCOPED_TRACE("Passing UDP/IPv4 session with large data");
        checkPushAndPop(AF_INET, SOCK_DGRAM, IPPROTO_UDP, sai_local4,
                        sai_remote4, large_text_.c_str(), large_text_.length(),
                        false);
    }
    {
        SCOPED_TRACE("Passing TCP/IPv4 session with large data");
        checkPushAndPop(AF_INET, SOCK_STREAM, IPPROTO_TCP, sai_local4,
                        sai_remote4, large_text_.c_str(), large_text_.length(),
                        false);
    }
}

TEST_F(ForwarderTest, badPush) {
    // push before connect
    EXPECT_THROW(forwarder_.push(1, AF_INET, SOCK_DGRAM, IPPROTO_UDP,
                                 *getSockAddr("192.0.2.1", "53").first,
                                 *getSockAddr("192.0.2.2", "53").first,
                                 TEST_DATA, sizeof(TEST_DATA)),
                 SocketSessionError);

    // Now connect the forwarder for the rest of tests
    startListen();
    forwarder_.connectToReceptor();

    // Invalid address family
    struct sockaddr sockaddr_unspec;
    sockaddr_unspec.sa_family = AF_UNSPEC;
    EXPECT_THROW(forwarder_.push(1, AF_INET, SOCK_DGRAM, IPPROTO_UDP,
                                 sockaddr_unspec,
                                 *getSockAddr("192.0.2.2", "53").first,
                                 TEST_DATA, sizeof(TEST_DATA)),
                 SocketSessionError);
    EXPECT_THROW(forwarder_.push(1, AF_INET, SOCK_DGRAM, IPPROTO_UDP,
                                 *getSockAddr("192.0.2.2", "53").first,
                                 sockaddr_unspec, TEST_DATA,
                                 sizeof(TEST_DATA)),
                 SocketSessionError);

    // Inconsistent address family
    EXPECT_THROW(forwarder_.push(1, AF_INET, SOCK_DGRAM, IPPROTO_UDP,
                                 *getSockAddr("2001:db8::1", "53").first,
                                 *getSockAddr("192.0.2.2", "53").first,
                                 TEST_DATA, sizeof(TEST_DATA)),
                 SocketSessionError);
    EXPECT_THROW(forwarder_.push(1, AF_INET6, SOCK_DGRAM, IPPROTO_UDP,
                                 *getSockAddr("2001:db8::1", "53").first,
                                 *getSockAddr("192.0.2.2", "53").first,
                                 TEST_DATA, sizeof(TEST_DATA)),
                 SocketSessionError);

    // Empty data: we reject them at least for now
    EXPECT_THROW(forwarder_.push(1, AF_INET, SOCK_DGRAM, IPPROTO_UDP,
                                 *getSockAddr("192.0.2.1", "53").first,
                                 *getSockAddr("192.0.2.2", "53").first,
                                 TEST_DATA, 0),
                 SocketSessionError);
    EXPECT_THROW(forwarder_.push(1, AF_INET, SOCK_DGRAM, IPPROTO_UDP,
                                 *getSockAddr("192.0.2.1", "53").first,
                                 *getSockAddr("192.0.2.2", "53").first,
                                 NULL, sizeof(TEST_DATA)),
                 SocketSessionError);

    // Close the receptor before push.  It will result in SIGPIPE (should be
    // ignored) and EPIPE, which will be converted to SocketSessionError.
    const int receptor_fd = acceptForwarder();
    close(receptor_fd);
    EXPECT_THROW(forwarder_.push(1, AF_INET, SOCK_DGRAM, IPPROTO_UDP,
                                 *getSockAddr("192.0.2.1", "53").first,
                                 *getSockAddr("192.0.2.2", "53").first,
                                 TEST_DATA, sizeof(TEST_DATA)),
                 SocketSessionError);
}

// A subroutine for pushTooFast.  Due to the fixed configuration of the
// send buffer size, we shouldn't be able to forward 3 full-size DNS messages
// without receiving them.  Exactly how many we can forward depends on the
// internal system implementation, so we'll at least confirm we can't do for 3.
void
multiPush(SocketSessionForwarder& forwarder, const struct sockaddr& sa,
          const void* data, size_t data_len)
{
    for (int i = 0; i < 3; ++i) {
        forwarder.push(1, AF_INET, SOCK_DGRAM, IPPROTO_UDP, sa, sa,
                       data, data_len);
    }
}

TEST_F(ForwarderTest, pushTooFast) {
    // Emulate the situation where the forwarder is pushing sessions too fast.
    // It should eventually fail without blocking.
    startListen();
    forwarder_.connectToReceptor();
    EXPECT_THROW(multiPush(forwarder_, *getSockAddr("192.0.2.1", "53").first,
                           large_text_.c_str(), large_text_.length()),
                 SocketSessionError);
}

TEST(SocketSession, badValue) {
    // normal cases are confirmed in ForwarderTest.  We only check some
    // abnormal cases here.

    SockAddrCreator addr_creator;

    EXPECT_THROW(SocketSession(42, AF_INET, SOCK_DGRAM, IPPROTO_UDP, NULL,
                               addr_creator.get("192.0.2.1", "53").first,
                               sizeof(TEST_DATA), TEST_DATA),
                 BadValue);
    EXPECT_THROW(SocketSession(42, AF_INET6, SOCK_STREAM, IPPROTO_TCP,
                               addr_creator.get("2001:db8::1", "53").first,
                               NULL, sizeof(TEST_DATA), TEST_DATA), BadValue);
    EXPECT_THROW(SocketSession(42, AF_INET, SOCK_DGRAM, IPPROTO_UDP,
                               addr_creator.get("192.0.2.1", "53").first,
                               addr_creator.get("192.0.2.2", "5300").first,
                               0, TEST_DATA), BadValue);
    EXPECT_THROW(SocketSession(42, AF_INET, SOCK_DGRAM, IPPROTO_UDP,
                               addr_creator.get("192.0.2.1", "53").first,
                               addr_creator.get("192.0.2.2", "5300").first,
                               sizeof(TEST_DATA), NULL), BadValue);
}
}
