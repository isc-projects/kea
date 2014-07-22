// Copyright (C) 2014 Internet Systems Consortium, Inc. ("ISC")
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
#include <asiolink/io_address.h>
#include <cc/data.h>
#include <dhcp/dhcp4.h>
#include <dhcp/tests/iface_mgr_test_config.h>
#include <dhcp4/tests/dhcp4_test_utils.h>
#include <dhcp4/tests/dhcp4_client.h>
#include <boost/shared_ptr.hpp>

using namespace isc;
using namespace isc::asiolink;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::dhcp::test;

namespace {

/// @brief Set of JSON configurations used throughout the DORA tests.
///
/// - Configuration 0:
///   - Used for testing direct traffic
///   - 1 subnet: 10.0.0.0/24
///   - 1 pool: 10.0.0.10-10.0.0.100
///   - Router option present: 10.0.0.200 and 10.0.0.201
///   - Domain Name Server option present: 10.0.0.202, 10.0.0.203.
///   - Log Servers option present: 192.0.2.200 and 192.0.2.201
///   - Quotes Servers option present: 192.0.2.202, 192.0.2.203.
///
/// - Configuration 1:
///   - Use for testing relayed messages
///   - 1 subnet: 192.0.2.0/24
///   - Router option present: 192.0.2.200 and 192.0.2.201
///   - Domain Name Server option present: 192.0.2.202, 192.0.2.203.
///   - Log Servers option present: 192.0.2.200 and 192.0.2.201
///   - Quotes Servers option present: 192.0.2.202, 192.0.2.203.
const char* DORA_CONFIGS[] = {
// Configuration 0
    "{ \"interfaces\": [ \"all\" ],"
        "\"valid-lifetime\": 600,"
        "\"subnet4\": [ { "
        "    \"subnet\": \"10.0.0.0/24\", "
        "    \"pool\": [ \"10.0.0.10-10.0.0.100\" ],"
        "    \"option-data\": [ {"
        "        \"name\": \"routers\","
        "        \"code\": 3,"
        "        \"data\": \"10.0.0.200,10.0.0.201\","
        "        \"csv-format\": true,"
        "        \"space\": \"dhcp4\""
        "    },"
        "    {"
        "        \"name\": \"domain-name-servers\","
        "        \"code\": 6,"
        "        \"data\": \"10.0.0.202,10.0.0.203\","
        "        \"csv-format\": true,"
        "        \"space\": \"dhcp4\""
        "    },"
        "    {"
        "        \"name\": \"log-servers\","
        "        \"code\": 7,"
        "        \"data\": \"10.0.0.200,10.0.0.201\","
        "        \"csv-format\": true,"
        "        \"space\": \"dhcp4\""
        "    },"
        "    {"
        "        \"name\": \"cookie-servers\","
        "        \"code\": 8,"
        "        \"data\": \"10.0.0.202,10.0.0.203\","
        "        \"csv-format\": true,"
        "        \"space\": \"dhcp4\""
        "    } ]"
        " } ]"
    "}",

// Configuration 1
    "{ \"interfaces\": [ \"all\" ],"
        "\"valid-lifetime\": 600,"
        "\"subnet4\": [ { "
        "    \"subnet\": \"192.0.2.0/24\", "
        "    \"option-data\": [ {"
        "        \"name\": \"routers\","
        "        \"code\": 3,"
        "        \"data\": \"192.0.2.200,192.0.2.201\","
        "        \"csv-format\": true,"
        "        \"space\": \"dhcp4\""
        "    },"
        "    {"
        "        \"name\": \"domain-name-servers\","
        "        \"code\": 6,"
        "        \"data\": \"192.0.2.202,192.0.2.203\","
        "        \"csv-format\": true,"
        "        \"space\": \"dhcp4\""
        "    },"
        "    {"
        "        \"name\": \"log-servers\","
        "        \"code\": 7,"
        "        \"data\": \"10.0.0.200,10.0.0.201\","
        "        \"csv-format\": true,"
        "        \"space\": \"dhcp4\""
        "    },"
        "    {"
        "        \"name\": \"cookie-servers\","
        "        \"code\": 8,"
        "        \"data\": \"10.0.0.202,10.0.0.203\","
        "        \"csv-format\": true,"
        "        \"space\": \"dhcp4\""
        "    } ]"
        " } ]"
    "}"
};

/// @brief Test fixture class for testing 4-way (DORA) exchanges.
class DORATest : public Dhcpv4SrvTest {
public:

    /// @brief Constructor.
    ///
    /// Sets up fake interfaces.
    DORATest()
        : Dhcpv4SrvTest(),
          iface_mgr_test_config_(true) {
        IfaceMgr::instance().openSockets4();
    }

    /// @brief Interface Manager's fake configuration control.
    IfaceMgrTestConfig iface_mgr_test_config_;

};

/// This test verifies that the client in the SELECTING state can get
/// an address when it doesn't request any specific address in the
/// DHCPDISCOVER message.
TEST_F(DORATest, selectingDoNotRequestAddress) {
    Dhcp4Client client(Dhcp4Client::SELECTING);
    // Configure DHCP server.
    configure(DORA_CONFIGS[0], *client.getServer());

    // Perform 4-way exchange with the server but to not request any
    // specific address in the DHCPDISCOVER message.
    ASSERT_NO_THROW(client.doDORA());

    // Make sure that the server responded.
    ASSERT_TRUE(client.getContext().response_);
    Pkt4Ptr resp = client.getContext().response_;
    // Make sure that the server has responded with DHCPACK.
    ASSERT_EQ(DHCPACK, static_cast<int>(resp->getType()));
    // Response must not be relayed.
    EXPECT_FALSE(resp->isRelayed());
    // Make sure that the server id is present.
    EXPECT_EQ("10.0.0.1", client.config_.serverid_.toText());
    // Make sure that the client has got the lease with the requested address.
    ASSERT_NE(client.config_.lease_.addr_.toText(), "0.0.0.0");
}

// This test verifies that the client in a SELECTING state can request
// a specific address and that this address will be assigned when
// available. It also tests that if the client requests an address which
// is in use the client will get a different address.
TEST_F(DORATest, selectingRequestAddress) {
    Dhcp4Client client(Dhcp4Client::SELECTING);
    // Configure DHCP server.
    configure(DORA_CONFIGS[0], *client.getServer());

    // Perform 4-way exchange with the server.
    ASSERT_NO_THROW(client.doDORA(boost::shared_ptr<
                                  IOAddress>(new IOAddress("10.0.0.50"))));

    // Make sure that the server responded.
    ASSERT_TRUE(client.getContext().response_);
    Pkt4Ptr resp = client.getContext().response_;
    // Make sure that the server has responded with DHCPACK.
    ASSERT_EQ(DHCPACK, static_cast<int>(resp->getType()));
    // Response must not be relayed.
    EXPECT_FALSE(resp->isRelayed());
    // Make sure that the server id is present.
    EXPECT_EQ("10.0.0.1", client.config_.serverid_.toText());
    // Make sure that the client has got the lease with the requested address.
    ASSERT_EQ("10.0.0.50", client.config_.lease_.addr_.toText());

    // Simulate different client requesting the same address.
    client.modifyHWAddr();
    ASSERT_NO_THROW(client.doDORA(boost::shared_ptr<
                                  IOAddress>(new IOAddress("10.0.0.50"))));
    resp = client.getContext().response_;
    // Make sure that the server responded.
    ASSERT_TRUE(resp);
    // Make sure that the server has responded with DHCPACK.    
    ASSERT_EQ(DHCPACK, static_cast<int>(resp->getType()));
    // Response must not be relayed.
    EXPECT_FALSE(resp->isRelayed());
    // Make sure that the server id is present.
    EXPECT_EQ("10.0.0.1", client.config_.serverid_.toText());
    // Make sure that the client has got some address.
    EXPECT_NE(client.config_.lease_.addr_.toText(), "0.0.0.0");
    // Make sure that the client has got a different address than requested
    // as the requested one is already in use.
    EXPECT_NE(client.config_.lease_.addr_.toText(), "10.0.0.50");
}

// This test verifies that the client will get the address that it has
// been allocated when the client requests a different address.
TEST_F(DORATest, selectingRequestNonMatchingAddress) {
    Dhcp4Client client(Dhcp4Client::SELECTING);
    // Configure DHCP server.
    configure(DORA_CONFIGS[0], *client.getServer());

    // Perform 4-way exchange with the server.
    ASSERT_NO_THROW(client.doDORA(boost::shared_ptr<
                                  IOAddress>(new IOAddress("10.0.0.50"))));

    // Make sure that the server responded.
    ASSERT_TRUE(client.getContext().response_);
    Pkt4Ptr resp = client.getContext().response_;
    // Make sure that the server has responded with DHCPACK.
    ASSERT_EQ(DHCPACK, static_cast<int>(resp->getType()));
    // Response must not be relayed.
    EXPECT_FALSE(resp->isRelayed());
    // Make sure that the server id is present.
    EXPECT_EQ("10.0.0.1", client.config_.serverid_.toText());
    // Make sure that the client has got the lease with the requested address.
    ASSERT_EQ("10.0.0.50", client.config_.lease_.addr_.toText());

    // Let's request a different address. The server should respond with
    // the one that the client already has allocated.
    ASSERT_NO_THROW(client.doDORA(boost::shared_ptr<
                                  IOAddress>(new IOAddress("10.0.0.80"))));
    // Make sure that the server responded.
    ASSERT_TRUE(client.getContext().response_);
    resp = client.getContext().response_;
    // Make sure that the server has responded with DHCPACK.
    ASSERT_EQ(DHCPACK, static_cast<int>(resp->getType()));
    // Response must not be relayed.
    EXPECT_FALSE(resp->isRelayed());
    // Make sure that the server id is present.
    EXPECT_EQ("10.0.0.1", client.config_.serverid_.toText());
    // Make sure that the client has got the lease with the address that
    // the client has recorded in the lease database.
    EXPECT_EQ("10.0.0.50", client.config_.lease_.addr_.toText());
}

// Test that the client in the INIT-REBOOT state can request the IP
// address it has and the address is returned. Also, check that if
// if the client requests in valid address the server sends a DHCPNAK.
TEST_F(DORATest, InitRebootRequest) {
    Dhcp4Client client(Dhcp4Client::SELECTING);
    // Configure DHCP server.
    configure(DORA_CONFIGS[0], *client.getServer());
    // Obtain a lease from the server using the 4-way exchange.
    ASSERT_NO_THROW(client.doDORA(boost::shared_ptr<
                                  IOAddress>(new IOAddress("10.0.0.50"))));
    // Make sure that the server responded.
    ASSERT_TRUE(client.getContext().response_);
    Pkt4Ptr resp = client.getContext().response_;
    // Make sure that the server has responded with DHCPACK.
    ASSERT_EQ(DHCPACK, static_cast<int>(resp->getType()));
    // Response must not be relayed.
    EXPECT_FALSE(resp->isRelayed());
    // Make sure that the server id is present.
    EXPECT_EQ("10.0.0.1", client.config_.serverid_.toText());
    // Make sure that the client has got the lease with the requested address.
    ASSERT_EQ("10.0.0.50", client.config_.lease_.addr_.toText());

    // Client has a lease in the database. Let's transition the client
    // to the INIT_REBOOT state so as the client can request the cached
    // lease using the DHCPREQUEST message.
    client.setState(Dhcp4Client::INIT_REBOOT);
    ASSERT_NO_THROW(client.doRequest(boost::shared_ptr<
                                     IOAddress>(new IOAddress("10.0.0.50"))));

    // Make sure that the server responded.
    ASSERT_TRUE(client.getContext().response_);
    resp = client.getContext().response_;
    // Make sure that the server has responded with DHCPACK.
    ASSERT_EQ(DHCPACK, static_cast<int>(resp->getType()));
    // Response must not be relayed.
    EXPECT_FALSE(resp->isRelayed());
    // Make sure that the server id is present.
    EXPECT_EQ("10.0.0.1", client.config_.serverid_.toText());
    // Make sure that the client has got the lease with the requested address.
    ASSERT_EQ("10.0.0.50", client.config_.lease_.addr_.toText());

    // Try to request a different address than the client has. The server
    // should respond with DHCPNAK.
    client.config_.lease_.addr_ = IOAddress("10.0.0.30");
    ASSERT_NO_THROW(client.doRequest(boost::shared_ptr<
                                     IOAddress>(new IOAddress("10.0.0.50"))));
    // Make sure that the server responded.
    ASSERT_TRUE(client.getContext().response_);
    resp = client.getContext().response_;
    EXPECT_EQ(DHCPNAK, static_cast<int>(resp->getType()));
}

} // end of anonymous namespace
