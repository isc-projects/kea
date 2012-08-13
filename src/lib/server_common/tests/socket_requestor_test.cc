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

#include <config.h>

#include <server_common/socket_request.h>

#include <gtest/gtest.h>

#include <config/tests/fake_session.h>
#include <config/ccsession.h>
#include <exceptions/exceptions.h>

#include <server_common/tests/data_path.h>

#include <cstdlib>
#include <cstddef>
#include <cerrno>
#include <sys/socket.h>
#include <sys/un.h>

#include <boost/foreach.hpp>
#include <boost/scoped_ptr.hpp>

#include <util/io/fd.h>
#include <util/io/fd_share.h>

using namespace isc::data;
using namespace isc::config;
using namespace isc::server_common;
using namespace isc;

namespace {

// Check it throws an exception when it is not initialized
TEST(SocketRequestorAccess, unitialized) {
    // Make sure it is not initialized
    initTestSocketRequestor(NULL);
    EXPECT_THROW(socketRequestor(), InvalidOperation);
}

// It returns whatever it is initialized to
TEST(SocketRequestorAccess, initialized) {
    // A concrete implementation that does nothing, just can exist
    class DummyRequestor : public SocketRequestor {
    public:
        DummyRequestor() : SocketRequestor() {}
        virtual void releaseSocket(const std::string&) {}
        virtual SocketID requestSocket(Protocol, const std::string&, uint16_t,
                                       ShareMode, const std::string&)
        {
            return (SocketID(0, "")); // Just to silence warnings
        }
    };
    DummyRequestor requestor;
    // Make sure it is initialized (the test way, of course)
    initTestSocketRequestor(&requestor);
    // It returs the same "pointer" as inserted
    // The casts are there as the template system seemed to get confused
    // without them, the types should be correct even without them, but
    // the EXPECT_EQ wanted to use long long int instead of pointers.
    EXPECT_EQ(static_cast<const SocketRequestor*>(&requestor),
              static_cast<const SocketRequestor*>(&socketRequestor()));
    // Just that we don't have an invalid pointer anyway
    initTestSocketRequestor(NULL);
}

// This class contains a fake (module)ccsession to emulate answers from Boss
class SocketRequestorTest : public ::testing::Test {
public:
    SocketRequestorTest() : session(ElementPtr(new ListElement),
                                    ElementPtr(new ListElement),
                                    ElementPtr(new ListElement))
    {
        initSocketRequestor(session, "tests");
    }

    ~SocketRequestorTest() {
        cleanupSocketRequestor();
    }

    // Do a standard request with some default values
    SocketRequestor::SocketID
    doRequest() {
        return (socketRequestor().requestSocket(SocketRequestor::UDP,
                                                "192.0.2.1", 12345,
                                                SocketRequestor::DONT_SHARE,
                                                "test"));
    }

    // Creates a valid socket request answer, as it would be sent by
    // Boss. 'valid' in terms of format, not values
    void
    addAnswer(const std::string& token, const std::string& path) {
        ElementPtr answer_part = Element::createMap();
        answer_part->set("token", Element::create(token));
        answer_part->set("path", Element::create(path));
        session.getMessages()->add(createAnswer(0, answer_part));
    }

    // Clears the messages the client sent so far on the fake msgq
    // (for easier access to new messages later)
    void
    clearMsgQueue() {
        while (session.getMsgQueue()->size() > 0) {
            session.getMsgQueue()->remove(0);
        }
    }

    isc::cc::FakeSession session;
    const std::string specfile;
};

// helper function to create the request packet as we expect the
// socket requestor to send
ConstElementPtr
createExpectedRequest(const std::string& address,
                      int port,
                      const std::string& protocol,
                      const std::string& share_mode,
                      const std::string& share_name)
{
    // create command arguments
    const ElementPtr command_args = Element::createMap();
    command_args->set("address", Element::create(address));
    command_args->set("port", Element::create(port));
    command_args->set("protocol", Element::create(protocol));
    command_args->set("share_mode", Element::create(share_mode));
    command_args->set("share_name", Element::create(share_name));

    // create the envelope
    const ElementPtr packet = Element::createList();
    packet->add(Element::create("Boss"));
    packet->add(Element::create("*"));
    packet->add(createCommand("get_socket", command_args));
    packet->add(Element::create(-1));

    return (packet);
}

TEST_F(SocketRequestorTest, testSocketRequestMessages) {
    // For each request, it will raise CCSessionError, since we don't
    // answer here.
    // We are only testing the request messages that are sent,
    // so for this test that is no problem
    clearMsgQueue();
    ConstElementPtr expected_request;

    expected_request = createExpectedRequest("192.0.2.1", 12345, "UDP",
                                             "NO", "test");
    EXPECT_THROW(socketRequestor().requestSocket(SocketRequestor::UDP,
                                                 "192.0.2.1", 12345,
                                                 SocketRequestor::DONT_SHARE,
                                                 "test"),
                 CCSessionError);
    ASSERT_EQ(1, session.getMsgQueue()->size());
    EXPECT_EQ(*expected_request, *(session.getMsgQueue()->get(0)));

    clearMsgQueue();
    expected_request = createExpectedRequest("192.0.2.2", 1, "TCP",
                                             "ANY", "test2");
    EXPECT_THROW(socketRequestor().requestSocket(SocketRequestor::TCP,
                                                 "192.0.2.2", 1,
                                                 SocketRequestor::SHARE_ANY,
                                                 "test2"),
                 CCSessionError);
    ASSERT_EQ(1, session.getMsgQueue()->size());
    EXPECT_EQ(*expected_request, *(session.getMsgQueue()->get(0)));

    clearMsgQueue();
    expected_request = createExpectedRequest("::1", 2, "UDP",
                                             "SAMEAPP", "test3");
    EXPECT_THROW(socketRequestor().requestSocket(SocketRequestor::UDP,
                                                 "::1", 2,
                                                 SocketRequestor::SHARE_SAME,
                                                 "test3"),
                 CCSessionError);
    ASSERT_EQ(1, session.getMsgQueue()->size());
    EXPECT_EQ(*expected_request, *(session.getMsgQueue()->get(0)));

    // A default share name equal to the app name passed on construction
    clearMsgQueue();
    expected_request = createExpectedRequest("::1", 2, "UDP",
                                             "SAMEAPP", "tests");
    EXPECT_THROW(socketRequestor().requestSocket(SocketRequestor::UDP,
                                                 "::1", 2,
                                   SocketRequestor::SHARE_SAME),
                 CCSessionError);
    ASSERT_EQ(1, session.getMsgQueue()->size());
    EXPECT_EQ(*expected_request, *(session.getMsgQueue()->get(0)));
}

TEST_F(SocketRequestorTest, invalidParameterForSocketRequest) {
    // Bad protocol
    EXPECT_THROW(socketRequestor().
                 requestSocket(static_cast<SocketRequestor::Protocol>(2),
                               "192.0.2.1", 12345,
                               SocketRequestor::DONT_SHARE,
                               "test"),
                 InvalidParameter);

    // Bad share mode
    EXPECT_THROW(socketRequestor().
                 requestSocket(SocketRequestor::UDP,
                               "192.0.2.1", 12345,
                               static_cast<SocketRequestor::ShareMode>(3),
                               "test"),
                 InvalidParameter);
}

TEST_F(SocketRequestorTest, testBadRequestAnswers) {
    // Test various scenarios where the requestor gets back bad answers

    // Should raise CCSessionError if there is no answer
    EXPECT_THROW(doRequest(), CCSessionError);

    // Also if the answer does not match the format
    session.getMessages()->add(createAnswer());
    EXPECT_THROW(doRequest(), CCSessionError);

    // Now a 'real' answer, should fail on socket connect (no such file)
    addAnswer("foo", "/does/not/exist");
    EXPECT_THROW(doRequest(), SocketRequestor::SocketError);

    // Another failure (domain socket path too long)
    addAnswer("foo", std::string(1000, 'x'));
    EXPECT_THROW(doRequest(), SocketRequestor::SocketError);

    // Test values around path boundary
    struct sockaddr_un sock_un;
    const std::string max_len(sizeof(sock_un.sun_path) - 1, 'x');
    addAnswer("foo", max_len);
    // The failure should NOT contain 'too long'
    // (explicitly checking for existance of nonexistence of 'too long',
    // as opposed to the actual error, since 'too long' is a value we set).
    try {
        doRequest();
        FAIL() << "doRequest did not throw an exception";
    } catch (const SocketRequestor::SocketError& se) {
        EXPECT_EQ(std::string::npos, std::string(se.what()).find("too long"));
    }

    const std::string too_long(sizeof(sock_un.sun_path), 'x');
    addAnswer("foo", too_long);
    // The failure SHOULD contain 'too long'
    try {
        doRequest();
        FAIL() << "doRequest did not throw an exception";
    } catch (const SocketRequestor::SocketError& se) {
        EXPECT_NE(std::string::npos, std::string(se.what()).find("too long"));
    }

    // Send back an error response
    // A generic one first
    session.getMessages()->add(createAnswer(1, "error"));
    EXPECT_THROW(doRequest(), CCSessionError);
    // Now some with specific exceptions
    session.getMessages()->add(createAnswer(2, "error"));
    EXPECT_THROW(doRequest(), SocketRequestor::SocketAllocateError);
    session.getMessages()->add(createAnswer(3, "error"));
    EXPECT_THROW(doRequest(), SocketRequestor::ShareError);
}

// Helper function to create the release commands as we expect
// them to be sent by the SocketRequestor class
ConstElementPtr
createExpectedRelease(const std::string& token) {
    // create command arguments
    const ElementPtr command_args = Element::createMap();
    command_args->set("token", Element::create(token));

    // create the envelope
    const ElementPtr packet = Element::createList();
    packet->add(Element::create("Boss"));
    packet->add(Element::create("*"));
    packet->add(createCommand("drop_socket", command_args));
    packet->add(Element::create(-1));

    return (packet);
}

TEST_F(SocketRequestorTest, testSocketReleaseMessages) {
    ConstElementPtr expected_release;

    session.getMessages()->add(createAnswer());

    clearMsgQueue();
    expected_release = createExpectedRelease("foo");
    socketRequestor().releaseSocket("foo");
    ASSERT_EQ(1, session.getMsgQueue()->size());
    EXPECT_EQ(*expected_release, *(session.getMsgQueue()->get(0)));

    session.getMessages()->add(createAnswer());
    clearMsgQueue();
    expected_release = createExpectedRelease("bar");
    socketRequestor().releaseSocket("bar");
    ASSERT_EQ(1, session.getMsgQueue()->size());
    EXPECT_EQ(*expected_release, *(session.getMsgQueue()->get(0)));
}

TEST_F(SocketRequestorTest, testBadSocketReleaseAnswers) {
    // Should fail if there is no answer at all
    EXPECT_THROW(socketRequestor().releaseSocket("bar"),
                 CCSessionError);

    // Should also fail if the answer is an error
    session.getMessages()->add(createAnswer(1, "error"));
    EXPECT_THROW(socketRequestor().releaseSocket("bar"),
                 SocketRequestor::SocketError);
}

// A helper function to impose a read timeout for the server socket
// in order to avoid deadlock when the client side has a bug and doesn't
// send expected data.
// It returns true when the timeout is set successfully; otherwise false.
bool
setRecvTimo(int s) {
    const struct timeval timeo = { 10, 0 }; // 10sec, arbitrary choice
    if (setsockopt(s, SOL_SOCKET, SO_RCVTIMEO, &timeo, sizeof(timeo)) == 0) {
        return (true);
    }
    if (errno == ENOPROTOOPT) { // deviant OS, give up using it.
        return (false);
    }
    isc_throw(isc::Unexpected, "set RCVTIMEO failed: " << strerror(errno));
}

// Helper test class that creates a randomly named domain socket
// Upon init, it will only reserve the name (and place an empty file in its
// place).
// When run() is called, it creates the socket, forks, and the child will
// listen for a connection, then send all the data passed to run to that
// connection, and then close the socket
class TestSocket {
public:
    TestSocket() : fd_(-1) {
        path_ = strdup("test_socket.XXXXXX");
        // Misuse mkstemp to generate a file name.
        const int f = mkstemp(path_);
        if (f == -1) {
            isc_throw(Unexpected, "mkstemp failed: " << strerror(errno));
        }
        // Just need the name, so immediately close
        close(f);
    }

    ~TestSocket() {
        cleanup();
    }

    void
    cleanup() {
        unlink(path_);
        if (path_ != NULL) {
            free(path_);
            path_ = NULL;
        }
        if (fd_ != -1) {
            close(fd_);
            fd_ = -1;
        }
    }

    // Returns the path used for the socket
    const char* getPath() const {
        return (path_);
    }

    // create socket, fork, and serve if child (child will exit when done).
    // If the underlying system doesn't allow to set read timeout, tell the
    // caller that via a false return value so that the caller can avoid
    // performing tests that could result in a dead lock.
    bool run(const std::vector<std::pair<std::string, int> >& data) {
        create();
        const bool timo_ok = setRecvTimo(fd_);
        const int child_pid = fork();
        if (child_pid == 0) {
            serve(data);
            exit(0);
        } else {
            // parent does not need fd anymore
            close(fd_);
            fd_ = -1;
        }
        return (timo_ok);
    }
private:
    // Actually create the socket and listen on it
    void
    create() {
        fd_ = socket(AF_UNIX, SOCK_STREAM, 0);
        if (fd_ == -1) {
            isc_throw(Unexpected, "Unable to create socket");
        }
        struct sockaddr_un socket_address;
        socket_address.sun_family = AF_UNIX;
        socklen_t len = strlen(path_);
        if (len > sizeof(socket_address.sun_path)) {
            isc_throw(Unexpected,
                      "mkstemp() created a filename too long for sun_path");
        }
        strncpy(socket_address.sun_path, path_, len);
#ifdef HAVE_SA_LEN
        socket_address.sun_len = len;
#endif

        len += offsetof(struct sockaddr_un, sun_path);
        // Remove the random file we created so we can reuse it for
        // a domain socket connection. This contains a minor race condition
        // but for the purposes of this test it should be small enough
        unlink(path_);
        if (bind(fd_, (const struct sockaddr*)&socket_address, len) == -1) {
            isc_throw(Unexpected,
                      "unable to bind to test domain socket " << path_ <<
                      ": " << strerror(errno));
        }

        if (listen(fd_, 1) == -1) {
            isc_throw(Unexpected,
                      "unable to listen on test domain socket " << path_ <<
                      ": " << strerror(errno));
        }
    }

    // Accept one connection, then for each value of the vector,
    // read the socket token from the connection and match the string
    // part of the vector element, and send the integer part of the element
    // using send_fd() (prepended by a status code 'ok').  For simplicity
    // we assume the tokens are 4 bytes long; if the test case uses a
    // different size of token the test will fail.
    //
    // There are a few specific exceptions;
    // when the value is -1, it will send back an error value (signaling
    // CREATOR_SOCKET_UNAVAILABLE)
    // when the value is -2, it will send a byte signaling CREATOR_SOCKET_OK
    // first, and then one byte from some string (i.e. bad data, not using
    // send_fd())
    //
    // NOTE: client_fd could leak on exception.  This should be cleaned up.
    // See the note about SocketSessionReceiver in socket_request.cc.
    void
    serve(const std::vector<std::pair<std::string, int> >& data) {
        const int client_fd = accept(fd_, NULL, NULL);
        if (client_fd == -1) {
            isc_throw(Unexpected, "Error in accept(): " << strerror(errno));
        }
        if (!setRecvTimo(client_fd)) {
            // In the loop below we do blocking read.  To avoid deadlock
            // when the parent is buggy we'll skip it unless we can
            // set a read timeout on the socket.
            return;
        }
        typedef std::pair<std::string, int> DataPair;
        BOOST_FOREACH(DataPair cur_data, data) {
            char buf[5];
            memset(buf, 0, 5);
            if (isc::util::io::read_data(client_fd, buf, 4) != 4) {
                isc_throw(Unexpected, "unable to receive socket token");
            }
            if (cur_data.first != buf) {
                isc_throw(Unexpected, "socket token mismatch: expected="
                          << cur_data.first << ", actual=" << buf);
            }

            bool result;
            if (cur_data.second == -1) {
                // send 'CREATOR_SOCKET_UNAVAILABLE'
                result = isc::util::io::write_data(client_fd, "0\n", 2);
            } else if (cur_data.second == -2) {
                // send 'CREATOR_SOCKET_OK' first
                result = isc::util::io::write_data(client_fd, "1\n", 2);
                if (result) {
                    if (send(client_fd, "a", 1, 0) != 1) {
                        result = false;
                    }
                }
            } else {
                // send 'CREATOR_SOCKET_OK' first
                result = isc::util::io::write_data(client_fd, "1\n", 2);
                if (result) {
                    if (isc::util::io::send_fd(client_fd,
                                               cur_data.second) != 0) {
                        result = false;
                    }
                }
            }
            if (!result) {
                isc_throw(Exception, "Error in send_fd(): " <<
                          strerror(errno));
            }
        }
        close(client_fd);
    }

    int fd_;
    char* path_;
};

TEST_F(SocketRequestorTest, testSocketPassing) {
    TestSocket ts;
    std::vector<std::pair<std::string, int> > data;
    data.push_back(std::pair<std::string, int>("foo\n", 1));
    data.push_back(std::pair<std::string, int>("bar\n", 2));
    data.push_back(std::pair<std::string, int>("foo\n", 3));
    data.push_back(std::pair<std::string, int>("foo\n", 1));
    data.push_back(std::pair<std::string, int>("foo\n", -1));
    data.push_back(std::pair<std::string, int>("foo\n", -2));

    // run() returns true iff we can specify read timeout so we avoid a
    // deadlock.  Unless there's a bug the test should succeed even without the
    // timeout, but we don't want to make the test hang up in case with an
    // unexpected bug, so we'd rather skip most of the tests in that case.
    const bool timo_ok = ts.run(data);
    SocketRequestor::SocketID socket_id;
    if (timo_ok) {
        // 1 should be ok
        addAnswer("foo", ts.getPath());
        socket_id = doRequest();
        EXPECT_EQ("foo", socket_id.second);
        EXPECT_EQ(0, close(socket_id.first));

        // 2 should be ok too
        addAnswer("bar", ts.getPath());
        socket_id = doRequest();
        EXPECT_EQ("bar", socket_id.second);
        EXPECT_EQ(0, close(socket_id.first));

        // 3 should be ok too (reuse earlier token)
        addAnswer("foo", ts.getPath());
        socket_id = doRequest();
        EXPECT_EQ("foo", socket_id.second);
        EXPECT_EQ(0, close(socket_id.first));
    }

    // Create a second socket server, to test that multiple different
    // domains sockets would work as well (even though we don't actually
    // use that feature)
    TestSocket ts2;
    std::vector<std::pair<std::string, int> > data2;
    data2.push_back(std::pair<std::string, int>("foo\n", 1));
    const bool timo_ok2 = ts2.run(data2);

    if (timo_ok2) {
        // 1 should be ok
        addAnswer("foo", ts2.getPath());
        socket_id = doRequest();
        EXPECT_EQ("foo", socket_id.second);
        EXPECT_EQ(0, close(socket_id.first));
    }

    if (timo_ok) {
        // Now use first socket again
        addAnswer("foo", ts.getPath());
        socket_id = doRequest();
        EXPECT_EQ("foo", socket_id.second);
        EXPECT_EQ(0, close(socket_id.first));

        // -1 is a "normal" error
        addAnswer("foo", ts.getPath());
        EXPECT_THROW(doRequest(), SocketRequestor::SocketError);

        // -2 is an unexpected error.  After this point it's not guaranteed the
        // connection works as intended.
        addAnswer("foo", ts.getPath());
        EXPECT_THROW(doRequest(), SocketRequestor::SocketError);
    }

    // Vector is of first socket is now empty, so the socket should be gone
    addAnswer("foo", ts.getPath());
    EXPECT_THROW(doRequest(), SocketRequestor::SocketError);

    // Vector is of second socket is now empty too, so the socket should be
    // gone
    addAnswer("foo", ts2.getPath());
    EXPECT_THROW(doRequest(), SocketRequestor::SocketError);
}

}
