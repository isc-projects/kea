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

#ifndef ISC_TESTUTILS_SOCKETREQUEST_H
#define ISC_TESTUTILS_SOCKETREQUEST_H 1

#include <server_common/socket_request.h>
#include <server_common/portconfig.h>

#include <asiodns/asiodns.h>

#include <gtest/gtest.h>
#include <boost/lexical_cast.hpp>

#include <vector>
#include <string>

namespace isc {
namespace testutils {

/// \brief A testcase part for faking the SocketRequestor in tests
///
/// It's awkward to request real sockets from the real socket creator
/// during tests (for one, because it would have to be running, for
/// another, we need to block real ports).  If you instantiate this class in
/// a test case, the socket requestor will be initialized to a test one which
/// handles fake socket FDs and stores what was requested, etc.
///
/// Furthermore, you can check if the code requested or released the correct
/// list of sockets using the checkTokens() method.
///
/// Some member variables are intentionally made public so that test cases
/// can easily check the value of them.  We prefer convenience for tests over
/// class integrity here.
class TestSocketRequestor : public isc::server_common::SocketRequestor {
public:
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
    /// \param expected_app The share name for which all the requests should
    ///     be made. This is not the usual app_name - the requestSocket does
    ///     not fall back to this value if its share_name is left empty, if
    ///     you want to check the code relies on the requestor to use the
    ///     app name, you set this to empty string.
    TestSocketRequestor(asiodns::DNSServiceBase& dnss,
                        server_common::portconfig::AddressList& store,
                        uint16_t expect_port,
                        const std::string& expected_app) :
        last_token_(0), break_rollback_(false), break_release_(false),
        dnss_(dnss), store_(store), expect_port_(expect_port),
        expected_app_(expected_app)
    {
        // Prepare the requestor (us) for the test
        server_common::initTestSocketRequestor(this);
    }

    /// \brief Destructor
    ///
    /// Removes the addresses (if any) installed by installListenAddresses,
    /// resets the socket requestor to uninitialized state and turns off
    /// the portconfig test mode.
    virtual ~TestSocketRequestor() {
        // Make sure no sockets are left inside (if installListenAddresses
        // wasn't used, this is NOP, so it won't hurt).
        server_common::portconfig::AddressList list;
        server_common::portconfig::installListenAddresses(list, store_, dnss_);
        // Don't leave invalid pointers here
        server_common::initTestSocketRequestor(NULL);
    }

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
public:
    /// \brief Support a broken rollback case
    ///
    /// If this is set to true, the requestSocket will throw when the
    /// ::1 address is requested.
    bool break_rollback_;

    /// \brief Throw on releaseSocket
    ///
    /// If this is set to true, the releaseSocket will throw SocketError.
    /// Defaults to false.
    bool break_release_;

    /// \brief Release a socket
    ///
    /// This only stores the token passed.
    /// \param token The socket to release
    ///
    /// \throw SocketError in case the break_release_ is set to true. This is
    ///     to test exception handling.
    void releaseSocket(const std::string& token) {
        if (break_release_) {
            isc_throw(SocketError, "Fatal test socket error");
        }
        released_tokens_.push_back(token);
    }

    /// \brief Request a socket
    ///
    /// This creates a new token and fakes a new socket and returns it.
    /// The token is stored.
    ///
    /// In case the address is 192.0.2.2, it throws SocketAllocateError
    /// or if the break_rollback_ is true and address is ::1, it throws
    /// ShareError. If the address is 192.0.2.3, it throws SocketError.
    ///
    /// The tokens produced are in form of protocol:address:port:fd. The fds
    /// start at 1 and increase by each successfull call.
    ///
    /// \param protocol The protocol to request
    /// \param address to bind to
    /// \param port to bind to
    /// \param mode checked to be SHARE_SAME for now
    /// \param name checked to be the same as expected_app parameter of the
    ///      constructor. Note that this class does not provide the fallback
    ///      to an app_name if this is empty string. To check the code relies
    ///      on the fallback (wants to use the app_name instead of providing
    ///      its own share name), you need to create this class with empty
    ///      expected_app.
    /// \return The token and FD
    /// \throw SocketAllocateError as described above, to test error handling
    /// \throw ShareError as described above, to test error handling
    /// \throw SocketError as described above, to test error handling
    SocketID requestSocket(Protocol protocol, const std::string& address,
                           uint16_t port, ShareMode mode,
                           const std::string& name)
    {
        if (address == "192.0.2.2") {
            isc_throw(SocketAllocateError, "This address is not allowed");
        }
        if (address == "192.0.2.3") {
            isc_throw(SocketError, "Fatal test error");
        }
        if (address == "::1" && break_rollback_) {
            // This is valid address, but in case we need to break the
            // rollback, it needs to be busy or whatever
            //
            // We break the second address to see the first one was
            // allocated and then returned
            isc_throw(ShareError,
                      "This address is available, but not for you");
        }
        const std::string proto(protocol == TCP ? "TCP" : "UDP");
        const size_t number = ++ last_token_;
        EXPECT_EQ(expect_port_, port);
        EXPECT_EQ(SHARE_SAME, mode);
        EXPECT_EQ(expected_app_, name);
        const std::string token(proto + ":" + address + ":" +
                                boost::lexical_cast<std::string>(port) + ":" +
                                boost::lexical_cast<std::string>(number));
        given_tokens_.push_back(token);
        return (SocketID(number, token));
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
    asiodns::DNSServiceBase& dnss_;
    server_common::portconfig::AddressList& store_;
    const uint16_t expect_port_;
    const std::string expected_app_;
};

}
}
#endif  // ISC_TESTUTILS_SOCKETREQUEST_H
