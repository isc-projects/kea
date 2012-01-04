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

#include <server_common/socket_request.h>
#include <server_common/portconfig.h>

#include <asiodns/asiodns.h>

#include <gtest/gtest.h>
#include <boost/lexical_cast.hpp>

#include <vector>
#include <string>

namespace isc {
namespace server_common {
namespace portconfig {
// Access the private hidden flag
extern bool test_mode;
}
}

namespace testutils {

/// \brief A testcase part for faking the SocketRequestor in tests
///
/// It's awkward to request real sockets from the real socket creator
/// during tests (for one, because it would have to be running, for
/// another, we need to block real ports). If you inherit this class,
/// the socket requestor will be initialized to a test one which handles
/// fake socket FDs and stores what was requested, etc. Make sure to
/// call the inherited SetUp and TearDown if you define your own (eg.
/// chain them instead of override).
///
/// Furthermore, you can check if the code requested or released the correct
/// list of sockets.
///
/// \note This class breaks many recommendations about "clean" object
///     design. It is mostly because the recommendations are too paranoid
///     and we better use the powerful tools we have, when we have a reason.
///     We inherit both the testing::Test and SocketRequestor, so we can
///     access both the testing macros and store the requests conveniently.
///     The virtual inheritance is necessary, because some tests need more
///     than one such "component" to be build from.
class TestSocketRequestor : public isc::server_common::SocketRequestor,
    virtual public ::testing::Test {
protected:
    /// \brief Constructor
    ///
    /// \param dnss The DNS service. It is expected this gets initialized
    ///     after the TestSocketRequestor constructor is called, as the
    ///     TestSocketRequestor should be a base class and the service only
    ///     a member.
    /// \param store Address store used when cleaning up.
    /// \param expect_port The port which is expected to be requested. If
    ///     the application requests a different port, it is considered
    ///     a failure.
    TestSocketRequestor(asiodns::DNSService& dnss,
                        server_common::portconfig::AddressList& store,
                        uint16_t expect_port) :
        last_token_(0), break_rollback_(false), dnss_(dnss), store_(store),
        expect_port_(expect_port)
    {}

    /// \brief Destructor
    virtual ~ TestSocketRequestor() {}

    /// \brief Tokens released by releaseSocket
    ///
    /// They are stored here by this class and you can examine them.
    std::vector<std::string> released_tokens_;

    /// \brief Tokens returned from requestSocket
    ///
    /// They are stored here by this class and you can examine them.
    std::vector<std::string> given_tokens_;
private:
    // Last token number and fd given out
    size_t last_token_;
protected:
    /// \brief Support a broken rollback case
    ///
    /// If this is set to true, the requestSocket will throw when the
    /// ::1 address is requested.
    bool break_rollback_;

    /// \brief Release a socket
    ///
    /// This only stores the token passed.
    /// \param token The socket to release
    void releaseSocket(const std::string& token) {
        released_tokens_.push_back(token);
    }

    /// \brief Request a socket
    ///
    /// This creates a new token and fakes a new socket and returns it.
    /// The token is stored.
    ///
    /// In case the address is 192.0.2.2 or if the break_rollback_ is true
    /// and address is ::1, it throws.
    ///
    /// The tokens produced are in form of protocol:address:port:fd. The fds
    /// start at 1 and increase by each successfull call.
    ///
    /// \param protocol The protocol to request
    /// \param address to bind to
    /// \param port to bind to
    /// \param mode checked to be DONT_SHARE for now
    /// \param name checked to be dummy_app for now
    /// \return The token and FD
    /// \throw SocketError as described above, to test error handling
    SocketID requestSocket(Protocol protocol, const std::string& address,
                           uint16_t port, ShareMode mode,
                           const std::string& name)
    {
        if (address == "192.0.2.2") {
            isc_throw(SocketError, "This address is not allowed");
        }
        if (address == "::1" && break_rollback_) {
            // This is valid address, but in case we need to break the
            // rollback, it needs to be busy or whatever
            //
            // We break the second address to see the first one was
            // allocated and then returned
            isc_throw(SocketError,
                      "This address is available, but not for you");
        }
        const std::string proto(protocol == TCP ? "TCP" : "UDP");
        const size_t number = ++ last_token_;
        EXPECT_EQ(expect_port_, port);
        EXPECT_EQ(DONT_SHARE, mode);
        EXPECT_EQ("dummy_app", name);
        const std::string token(proto + ":" + address + ":" +
                                boost::lexical_cast<std::string>(port) + ":" +
                                boost::lexical_cast<std::string>(number));
        given_tokens_.push_back(token);
        return (SocketID(number, token));
    }

    /// \brief Initialize the test
    ///
    /// It installs itself as the socket requestor. It also turns on portconfig
    /// test mode where it doesn't really put the sockets into ASIO (as the FDs
    /// are fake ones and would get closed).
    ///
    /// Make sure you call it in case you need to define your own SetUp.
    void SetUp() {
        // Prepare the requestor (us) for the test
        SocketRequestor::initTest(this);
        // Don't manipulate the real sockets
        server_common::portconfig::test_mode = true;
    }

    /// \brief Cleanup after the test
    ///
    /// Removes the addresses (if any) installed by installListenAddresses,
    /// resets the socket requestor to uninitialized state and turns off
    /// the portconfig test mode.
    ///
    /// Make sure you call it in case you need to define your own TearDown.
    void TearDown() {
        // Make sure no sockets are left inside (if installListenAddresses
        // wasn't used, this is NOP, so it won't hurt).
        server_common::portconfig::AddressList list;
        server_common::portconfig::installListenAddresses(list, store_, dnss_);
        // Don't leave invalid pointers here
        SocketRequestor::initTest(NULL);
        // And return the mode
        server_common::portconfig::test_mode = false;
    }

    /// \brief Check the list of tokens is as expected
    ///
    /// Compares the expected and real tokens.
    ///
    /// \param expected List of the expected tokens, as NULL-terminated array
    ///     of C strings (it is more convenient to type as a constant than to
    ///     manually push_back all the strings to a vector).
    /// \param real The token list that was produced by this class (usually
    ///     either given_tokens_ or released_tokens_).
    /// \param scope Human readable identifier of which checkTokens call it is.
    ///     It is printed as a part of failure message.
    void checkTokens(const char** expected,
                     const std::vector<std::string>& real,
                     const char* scope) const
    {
        SCOPED_TRACE(scope);
        size_t position(0);
        while (expected[position] != NULL) {
            ASSERT_LT(position, real.size());
            EXPECT_EQ(expected[position], real[position]) << position;
            position ++;
        }
        EXPECT_EQ(position, real.size());
    }

private:
    asiodns::DNSService& dnss_;
    server_common::portconfig::AddressList& store_;
    const uint16_t expect_port_;
};

}
}
