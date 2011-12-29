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
                                    ElementPtr(new ListElement)),
                            specfile(std::string(TEST_DATA_PATH) +
                                     "/spec.spec")
    {
        session.getMessages()->add(createAnswer());
        cc_session.reset(new ModuleCCSession(specfile, session, NULL, NULL,
                                             false, false));
        initSocketReqeustor(*cc_session);
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
    boost::scoped_ptr<ModuleCCSession> cc_session;
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
    ASSERT_THROW(socketRequestor().requestSocket(SocketRequestor::UDP,
                                   "192.0.2.1", 12345,
                                   SocketRequestor::DONT_SHARE,
                                   "test"),
                 CCSessionError);
    ASSERT_EQ(1, session.getMsgQueue()->size());
    ASSERT_EQ(*expected_request, *(session.getMsgQueue()->get(0)));

    clearMsgQueue();
    expected_request = createExpectedRequest("192.0.2.2", 1, "TCP",
                                             "ANY", "test2");
    ASSERT_THROW(socketRequestor().requestSocket(SocketRequestor::TCP,
                                   "192.0.2.2", 1,
                                   SocketRequestor::SHARE_ANY,
                                   "test2"),
                 CCSessionError);
    ASSERT_EQ(1, session.getMsgQueue()->size());
    ASSERT_EQ(*expected_request, *(session.getMsgQueue()->get(0)));

    clearMsgQueue();
    expected_request = createExpectedRequest("::1", 2, "UDP",
                                             "SAMEAPP", "test3");
    ASSERT_THROW(socketRequestor().requestSocket(SocketRequestor::UDP,
                                   "::1", 2,
                                   SocketRequestor::SHARE_SAME,
                                   "test3"),
                 CCSessionError);
    ASSERT_EQ(1, session.getMsgQueue()->size());
    ASSERT_EQ(*expected_request, *(session.getMsgQueue()->get(0)));
}

TEST_F(SocketRequestorTest, testBadRequestAnswers) {
    // Test various scenarios where the requestor gets back bad answers

    // Should raise CCSessionError if there is no answer
    ASSERT_THROW(doRequest(), CCSessionError);

    // Also if the answer does not match the format
    session.getMessages()->add(createAnswer());
    ASSERT_THROW(doRequest(), CCSessionError);

    // Now a 'real' answer, should fail on socket connect (no such file)
    addAnswer("foo", "/does/not/exist");
    ASSERT_THROW(doRequest(), SocketRequestor::SocketError);

    // Another failure (domain socket path too long)
    addAnswer("foo", std::string(1000, 'x'));
    ASSERT_THROW(doRequest(), SocketRequestor::SocketError);

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
        ASSERT_EQ(std::string::npos, std::string(se.what()).find("too long"));
    }

    const std::string too_long(sizeof(sock_un.sun_path), 'x');
    addAnswer("foo", too_long);
    // The failure SHOULD contain 'too long'
    try {
        doRequest();
        FAIL() << "doRequest did not throw an exception";
    } catch (const SocketRequestor::SocketError& se) {
        ASSERT_NE(std::string::npos, std::string(se.what()).find("too long"));
    }

    // Send back an error response
    session.getMessages()->add(createAnswer(1, "error"));
    ASSERT_THROW(doRequest(), CCSessionError);
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

    return (packet);
}

TEST_F(SocketRequestorTest, testSocketReleaseMessages) {
    ConstElementPtr expected_release;

    session.getMessages()->add(createAnswer());

    clearMsgQueue();
    expected_release = createExpectedRelease("foo");
    socketRequestor().releaseSocket("foo");
    ASSERT_EQ(1, session.getMsgQueue()->size());
    ASSERT_EQ(*expected_release, *(session.getMsgQueue()->get(0)));

    session.getMessages()->add(createAnswer());
    clearMsgQueue();
    expected_release = createExpectedRelease("bar");
    socketRequestor().releaseSocket("bar");
    ASSERT_EQ(1, session.getMsgQueue()->size());
    ASSERT_EQ(*expected_release, *(session.getMsgQueue()->get(0)));
}

TEST_F(SocketRequestorTest, testBadSocketReleaseAnswers) {
    // Should fail if there is no answer at all
    ASSERT_THROW(socketRequestor().releaseSocket("bar"),
                 CCSessionError);

    // Should also fail if the answer is an error
    session.getMessages()->add(createAnswer(1, "error"));
    ASSERT_THROW(socketRequestor().releaseSocket("bar"),
                 SocketRequestor::SocketError);
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
        free(path_);
        if (fd_ != -1) {
            close(fd_);
            fd_ = -1;
        }
    }

    // Returns the path used for the socket
    const char* getPath() const {
        return (path_);
    }

    // create socket, fork, and serve if child (child will exit when done)
    void run(const std::vector<int>& data) {
        try {
            create();
            const int child_pid = fork();
            if (child_pid == 0) {
                serve(data);
                exit(0);
            } else {
                // parent does not need fd anymore
                close(fd_);
                fd_ = -1;
            }
        } catch (const std::exception&) {
            cleanup();
            throw;
        }
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

    // Accept one connection, then send all values from the vector using
    // send_fd() (prepended by a status code 'ok').
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
    serve(const std::vector<int>& data) {
        const int client_fd = accept(fd_, NULL, NULL);
        if (client_fd == -1) {
            isc_throw(Exception, "Error in accept(): " << strerror(errno));
        }
        BOOST_FOREACH(int cur_data, data) {
            bool result;
            if (cur_data == -1) {
                // send 'CREATOR_SOCKET_UNAVAILABLE'
                result = isc::util::io::write_data(client_fd, "0\n", 2);
            } else if (cur_data == -2) {
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
                    if (isc::util::io::send_fd(client_fd, cur_data) != 0) {
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
    std::vector<int> data;
    data.push_back(1);
    data.push_back(2);
    data.push_back(3);
    data.push_back(-1);
    data.push_back(-2);
    data.push_back(1);
    ts.run(data);

    // 1 should be ok
    addAnswer("foo", ts.getPath());
    SocketRequestor::SocketID socket_id = doRequest();
    ASSERT_EQ("foo", socket_id.second);
    ASSERT_EQ(0, close(socket_id.first));

    // 2 should be ok too
    addAnswer("bar", ts.getPath());
    socket_id = doRequest();
    ASSERT_EQ("bar", socket_id.second);
    ASSERT_EQ(0, close(socket_id.first));

    // 3 should be ok too (reuse earlier token)
    addAnswer("foo", ts.getPath());
    socket_id = doRequest();
    ASSERT_EQ("foo", socket_id.second);
    ASSERT_EQ(0, close(socket_id.first));

    // -1 should not
    addAnswer("foo", ts.getPath());
    ASSERT_THROW(doRequest(), SocketRequestor::SocketError);

    // -2 should not
    addAnswer("foo", ts.getPath());
    ASSERT_THROW(doRequest(), SocketRequestor::SocketError);

    // Create a second socket server, to test that multiple different
    // domains sockets would work as well (even though we don't actually
    // use that feature)
    TestSocket ts2;
    std::vector<int> data2;
    data2.push_back(1);
    ts2.run(data2);
    // 1 should be ok
    addAnswer("foo", ts2.getPath());
    socket_id = doRequest();
    ASSERT_EQ("foo", socket_id.second);
    ASSERT_EQ(0, close(socket_id.first));

    // Now use first socket again
    addAnswer("foo", ts.getPath());
    socket_id = doRequest();
    ASSERT_EQ("foo", socket_id.second);
    ASSERT_EQ(0, close(socket_id.first));

    // Vector is of first socket is now empty, so the socket should be gone
    addAnswer("foo", ts.getPath());
    ASSERT_THROW(doRequest(), SocketRequestor::SocketError);

    // Vector is of second socket is now empty too, so the socket should be
    // gone
    addAnswer("foo", ts2.getPath());
    ASSERT_THROW(doRequest(), SocketRequestor::SocketError);
}


}
