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

// TODO Docs

class TestSocketRequestor : public isc::server_common::SocketRequestor,
    virtual public ::testing::Test {
protected:
    TestSocketRequestor(asiodns::DNSService& dnss,
                        server_common::portconfig::AddressList& store,
                        uint16_t expect_port) :
        last_token_(0), break_rollback_(false), dnss_(dnss), store_(store),
        expect_port_(expect_port)
    {}
    virtual ~ TestSocketRequestor() {}
    // Store the tokens as they go in and out
    std::vector<std::string> released_tokens_;
    std::vector<std::string> given_tokens_;
    // Last token number and fd given out
    size_t last_token_;
    // Should we break the rollback?
    bool break_rollback_;
    void releaseSocket(const std::string& token) {
        released_tokens_.push_back(token);
    }
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
        size_t number = ++ last_token_;
        EXPECT_EQ(expect_port_, port);
        EXPECT_EQ(DONT_SHARE, mode);
        EXPECT_EQ("dummy_app", name);
        const std::string token(proto + ":" + address + ":" +
                                boost::lexical_cast<std::string>(port) + ":" +
                                boost::lexical_cast<std::string>(number));
        given_tokens_.push_back(token);
        return (SocketID(number, token));
    }
    void SetUp() {
        // Prepare the requestor (us) for the test
        SocketRequestor::initTest(this);
        // Don't manipulate the real sockets
        server_common::portconfig::test_mode = true;
    }
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
    // This checks the set of tokens is the same
    void checkTokens(const char** expected,
                     const std::vector<std::string>& real,
                     const char* scope)
    {
        SCOPED_TRACE(scope);
        size_t position(0);
        while (expected[position]) {
            ASSERT_LT(position, real.size());
            EXPECT_EQ(expected[position], real[position]) << position;
            position ++;
        }
        EXPECT_EQ(position, real.size());
    }
private:
    asiodns::DNSService& dnss_;
    server_common::portconfig::AddressList& store_;
    uint16_t expect_port_;
};

}
}
