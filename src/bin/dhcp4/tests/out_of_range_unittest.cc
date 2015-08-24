// Copyright (C) 2015 Internet Systems Consortium, Inc. ("ISC")
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
#include <dhcp_ddns/ncr_msg.h>
#include <dhcp/tests/iface_mgr_test_config.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/host.h>
#include <dhcpsrv/host_mgr.h>
#include <dhcpsrv/subnet_id.h>
#include <dhcp4/tests/dhcp4_test_utils.h>
#include <dhcp4/tests/dhcp4_client.h>
#include <boost/shared_ptr.hpp>

using namespace isc;
using namespace isc::asiolink;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::dhcp::test;

namespace {

/// @brief Set of JSON configurations used throughout the out of range
///  tests.
///
/// - Configuration 0 - Reference configuration, all tests start with the
///   server configured with this configuration:
///   - 1 subnet: 10.0.0.0/24
///   - with one pool  10.0.0.10 - 10.0.0.100
///   - 1 address reservation (fixed host) for HW address:
///     ff:ff:ff:ff:ff:01
///   - 1 hostname reservation (dynamic host) for HW address:
///     dd:dd:dd:dd:dd:01,
///   - DDNS enabled
/// - Configuration 1:
///   - Same as configuration 1 but with a different pool range
/// - Configuration 2 - same subnet as reference, different pool,
///       no reservations
/// - Configuration 3 - different subnet with reservations
/// - Configuration 4 - different subnet with no reservations
/// - Configuration 5 - same as reference, no reservations
///
const char* OOR_CONFIGS[] = {
// Configuration 0 - reference configuration
    "{ \"interfaces-config\": {"
        "      \"interfaces\": [ \"*\" ]"
        "},"
        "\"valid-lifetime\": 600,"
        "\"subnet4\": [ { "
        "    \"subnet\": \"10.0.0.0/24\", "
        "    \"pools\": [ { \"pool\": \"10.0.0.10-10.0.0.100\" } ],"
        "    \"reservations\": [ "
        "       {"
        "         \"hw-address\": \"ff:ff:ff:ff:ff:01\","
        "         \"ip-address\": \"10.0.0.7\""
        "       },"
        "       {"
        "         \"hw-address\": \"dd:dd:dd:dd:dd:01\","
        "         \"hostname\": \"reserved.example.com\""
        "       }"
        "    ]"
        "} ],"
        "\"dhcp-ddns\": {"
        "     \"enable-updates\": true,"
        "     \"qualifying-suffix\": \"\""
        "}"
    "}",

// Configuration 1 - same subnet as reference, different pool
    "{ \"interfaces-config\": {"
        "      \"interfaces\": [ \"*\" ]"
        "},"
        "\"valid-lifetime\": 600,"
        "\"subnet4\": [ { "
        "    \"subnet\": \"10.0.0.0/24\", "
        "    \"pools\": [ { \"pool\": \"10.0.0.101-10.0.0.200\" } ],"
        "    \"reservations\": [ "
        "       {"
        "         \"hw-address\": \"ff:ff:ff:ff:ff:01\","
        "         \"ip-address\": \"10.0.0.7\""
        "       },"
        "       {"
        "         \"hw-address\": \"dd:dd:dd:dd:dd:01\","
        "         \"hostname\": \"reserved.example.com\""
        "       }"
        "    ]"
        "} ],"
        "\"dhcp-ddns\": {"
        "     \"enable-updates\": true,"
        "     \"qualifying-suffix\": \"\""
        "}"
    "}",

// Configuration 2 - same subnet as reference, different pool, no reservations
    "{ \"interfaces-config\": {"
        "      \"interfaces\": [ \"*\" ]"
        "},"
        "\"valid-lifetime\": 600,"
        "\"subnet4\": [ { "
        "    \"subnet\": \"10.0.0.0/24\", "
        "    \"pools\": [ { \"pool\": \"10.0.0.101-10.0.0.200\" } ],"
        "} ],"
        "\"dhcp-ddns\": {"
        "     \"enable-updates\": true,"
        "     \"qualifying-suffix\": \"\""
        "}"
    "}",


// Configuration 3 - different subnet with reservations
    "{ \"interfaces-config\": {"
        "      \"interfaces\": [ \"*\" ]"
        "},"
        "\"valid-lifetime\": 600,"
        "\"subnet4\": [ { "
        "    \"subnet\": \"192.0.2.0/24\", "
        "    \"pools\": [ { \"pool\": \"192.0.2.101-192.0.2.200\" } ],"
        "    \"reservations\": [ "
        "       {"
        "         \"hw-address\": \"ff:ff:ff:ff:ff:01\","
        "         \"ip-address\": \"192.0.2.7\""
        "       },"
        "       {"
        "         \"hw-address\": \"dd:dd:dd:dd:dd:01\","
        "         \"hostname\": \"reserved.example.com\""
        "       }"
        "    ]"
        "} ],"
        "\"dhcp-ddns\": {"
        "     \"enable-updates\": true,"
        "     \"qualifying-suffix\": \"\""
        "}"
    "}",

// Configuration 4 - different subnet with no reservations
    "{ \"interfaces-config\": {"
        "      \"interfaces\": [ \"*\" ]"
        "},"
        "\"valid-lifetime\": 600,"
        "\"subnet4\": [ { "
        "    \"subnet\": \"192.0.2.0/24\", "
        "    \"pools\": [ { \"pool\": \"192.0.2.101-192.0.2.200\" } ]"
        "} ],"
        "\"dhcp-ddns\": {"
        "     \"enable-updates\": true,"
        "     \"qualifying-suffix\": \"\""
        "}"
    "}",

// Configuration 5 - same as reference, no reservations
    "{ \"interfaces-config\": {"
        "      \"interfaces\": [ \"*\" ]"
        "},"
        "\"valid-lifetime\": 600,"
        "\"subnet4\": [ { "
        "    \"subnet\": \"10.0.0.0/24\", "
        "    \"pools\": [ { \"pool\": \"10.0.0.10-10.0.0.100\" } ],"
        "} ],"
        "\"dhcp-ddns\": {"
        "     \"enable-updates\": true,"
        "     \"qualifying-suffix\": \"\""
        "}"
    "}",

};

/// @brief Enum for indexing into the array of configurations.
/// These were created to make the test cases easier to follow.
enum CfgIndex {
    REF_CFG = 0,
    DIFF_POOL,
    DIFF_POOL_NO_HR,
    DIFF_SUBNET,
    DIFF_SUBNET_NO_HR,
    NO_HR = 4
};

/// @brief Enum for specifying expected response to client renewal attempt
enum RenewOutcome {
    DOES_RENEW,
    DOES_NOT_RENEW
};

/// @brief Enum for specifying expected response to client release attempt
enum ReleaseOutcome {
    DOES_RELEASE,
    DOES_NOT_RELEASE
};

/// @brief Test fixture class for testing various exchanges when the client's
/// leased address is out of range due to configuration changes.
class OutOfRangeTest : public Dhcpv4SrvTest {
public:
    D2ClientMgr& d2_mgr_;

    /// @brief Constructor.
    ///
    /// Sets up fake interfaces.
    OutOfRangeTest()
        : Dhcpv4SrvTest(),
          d2_mgr_(CfgMgr::instance().getD2ClientMgr()),
          iface_mgr_test_config_(true) {
        IfaceMgr::instance().openSockets4();
    }

    /// @brief Desctructor.
    ///
    /// Cleans up statistics after the test.
    ~OutOfRangeTest() {
    }

    void configure(const std::string& config, Dhcp4Client& client) {
        NakedDhcpv4Srv& server = *client.getServer();
        ASSERT_NO_FATAL_FAILURE(Dhcpv4SrvTest::configure(config, server));
        if (d2_mgr_.ddnsEnabled()) {
            ASSERT_NO_THROW(server.startD2());
        }
    }

    /// @briefVerify that a NameChangeRequest has been queued
    ///
    /// Checks that a NCR of a given type (ADD or REMOVE) for a given
    /// ip address has been queued.  If the NCR exits, it is processed
    /// off the queue.  Note the function expects there to be 1 and only
    /// 1 NCR queued.
    ///
    /// @param type - NCR type exepcted, either CHG_ADD or CHG_REMOVE
    /// @param addr - string containing the ip address expected in the NCR
    void verifyNameChangeRequest(const isc::dhcp_ddns::NameChangeType type,
                                 const std::string& addr) {
        ASSERT_EQ(1, d2_mgr_.getQueueSize());

        isc::dhcp_ddns::NameChangeRequestPtr ncr;
        ASSERT_NO_THROW(ncr = d2_mgr_.peekAt(0));
        ASSERT_TRUE(ncr);

        EXPECT_EQ(type, ncr->getChangeType());
        EXPECT_EQ(addr, ncr->getIpAddress());

        // Process the message off the queue
        ASSERT_NO_THROW(d2_mgr_.runReadyIO());
        ASSERT_EQ(0, d2_mgr_.getQueueSize());
    }

    /// @brief Conducts a single out-of-range test scenario
    ///
    /// Each test cycles consists of a the following two stages, the first is
    /// a set-up stage during which the server is configured with an initial,
    /// reference, configuration and a client then verifies that it can aquire
    /// and renew a lease.  The second stage verifies that the server, having
    /// been reconfigured such that the original lease is now "out-of-range",
    /// responds correctly to the same client first attempting to renew the
    /// lease and then attempting to release the lease.
    ///
    /// The test also expects the configuration to enable DDNS, and verifies
    /// that a DNS add is done during stage one, and a DNS remove is done
    /// in stage two as part of the release request processing.
    ///
    /// @param cfg_idx - index of the "replacement" configuration used to
    /// reconfigure the server during stage two
    /// @param hwaddress - text value, if not empty, to use as the hardware
    /// address.  This is used for host reservation tests.
    /// in client queries
    /// @param expected_address - text value of the expected address.  If not
    /// empty the test will fail if the server responds with a different lease
    /// address
    /// @param renew_outcome - expected server reaction in response to the
    /// client's stage two renewal attempt.
    /// @param release_outcome - expected server reaction in response to the
    /// client's stage two release attempt.  Currently defaults to DOES_RELEASE
    /// as no cases have been identified which do otherwise.
    void oorRenewReleaseTest(enum CfgIndex cfg_idx,
                             const std::string& hwaddress,
                             const std::string& expected_address,
                             enum RenewOutcome renew_outcome,
                             enum ReleaseOutcome release_outcome = DOES_RELEASE);

    /// @brief Interface Manager's fake configuration control.
    IfaceMgrTestConfig iface_mgr_test_config_;

};

void
OutOfRangeTest::oorRenewReleaseTest(enum CfgIndex cfg_idx,
                             const std::string& hwaddress,
                             const std::string& expected_address,
                             enum RenewOutcome renew_outcome,
                             enum ReleaseOutcome release_outcome) {
    // STAGE ONE:

    // Step 1 is to acquire the lease
    Dhcp4Client client(Dhcp4Client::SELECTING);

    // Configure DHCP server.
    configure(OOR_CONFIGS[REF_CFG], client);

    // Set the host name so DNS updates will be performed
    client.includeHostname("test.example.com");

    // Set the hw address if given one
    if (!hwaddress.empty()) {
        client.setHWAddress(hwaddress);
    }

    // Aquire the lease via DORA
    ASSERT_NO_THROW(client.doDORA());

    // Make sure that the server responded.
    ASSERT_TRUE(client.getContext().response_);
    Pkt4Ptr resp = client.getContext().response_;

    // Make sure that the server has responded with DHCPACK.
    ASSERT_EQ(DHCPACK, static_cast<int>(resp->getType()));

    // Verify a lease was created
    IOAddress leased_address = client.config_.lease_.addr_;
    Lease4Ptr lease = LeaseMgrFactory::instance().getLease4(leased_address);
    ASSERT_TRUE(lease);

    // Check the expected address if given
    if (!expected_address.empty()) {
        ASSERT_EQ(leased_address, expected_address);
    }

    // Verify that a DNS add was requested
    verifyNameChangeRequest(isc::dhcp_ddns::CHG_ADD, leased_address.toText());

    // The address is still valid, let's verify the lease can be renewed
    // Set the unicast destination address to indicate that it is a renewal.
    client.setState(Dhcp4Client::RENEWING);
    client.setDestAddress(IOAddress("10.0.0.1"));
    ASSERT_NO_THROW(client.doRequest());

    // Verify that we received an ACK to our renewal
    resp = client.getContext().response_;
    ASSERT_EQ(DHCPACK, static_cast<int>(resp->getType()));

    // STAGE TWO:

    // Now reconfigure which should render our leased address out-of-range
    configure(OOR_CONFIGS[cfg_idx], client);

    // Try to renew after the configuration change..
    ASSERT_NO_THROW(client.doRequest());
    resp = client.getContext().response_;

    // Verify we got ACK'd or NAK'd as expected
    ASSERT_EQ((renew_outcome == DOES_RENEW ? DHCPACK : DHCPNAK),
              static_cast<int>(resp->getType()));

    // Verify that the lease still exists in the database as it has not
    // been explicitly released.
    lease = LeaseMgrFactory::instance().getLease4(leased_address);
    ASSERT_TRUE(lease);

    // Recreate the client lease info, a preceding NAK will have wiped it out
    client.createLease(leased_address, lease->valid_lft_);

    // Send the release. The server should remove it from the DB and
    // request DNS remove.
    ASSERT_NO_THROW(client.doRelease());

    lease = LeaseMgrFactory::instance().getLease4(leased_address);

    if (release_outcome == DOES_RELEASE) {
        EXPECT_FALSE(lease);
        // Verify the DNS remove was queued.
        verifyNameChangeRequest(isc::dhcp_ddns::CHG_REMOVE,
                                leased_address.toText());
    } else {
        // Lease should still exist, and no NCR should be queued.
        EXPECT_TRUE(lease);
        EXPECT_EQ(0, d2_mgr_.getQueueSize());
    }
}


// Verifies that once-valid lease, whose address is no longer
// within the subnet's pool:
//
// a: Is NAKed upon a renewal attempt
// b: Is released properly upon release, including DNS removal
//
TEST_F(OutOfRangeTest, dynamicOutOfPool) {

    std::string hwaddress = "";
    std::string expected_address = "";

    oorRenewReleaseTest(DIFF_POOL, hwaddress, expected_address,
                        DOES_NOT_RENEW);

}

// Verifies that once-valid lease whose address is no longer
// within any configured subnet:
//
// a: Is NAKed upon a renewal attempt
// b: Is released properly upon release, including DNS removal
//
TEST_F(OutOfRangeTest, dynamicOutOfSubnet) {

    std::string hwaddress = "";
    std::string expected_address = "";

    oorRenewReleaseTest(DIFF_SUBNET, hwaddress, expected_address,
                        DOES_NOT_RENEW);
}

// Test verifies that once-valid dynamic address host reserveration,
// whose address is no longer within the subnet's pool:
//
// a: Is NAKed upon a renewal attempt
// b: Is released properly upon release, including DNS removal
//
TEST_F(OutOfRangeTest, dynamicHostOutOfPool) {
    std::string hwaddress = "dd:dd:dd:dd:dd:01";
    std::string expected_address = "";

    oorRenewReleaseTest(DIFF_POOL, hwaddress, expected_address, DOES_NOT_RENEW);
}

// Test verifies that once-valid dynamic address host reserveration,
// whose address is no longer within any configured subnet:
//
// a: Is NAKed upon a renewal attempt
// b: Is released properly upon release, including DNS removal
//
TEST_F(OutOfRangeTest, dynamicHostOutOfSubnet) {
    std::string hwaddress = "dd:dd:dd:dd:dd:01";
    std::string expected_address = "";

    oorRenewReleaseTest(DIFF_SUBNET, hwaddress, expected_address,
                        DOES_NOT_RENEW);
}

// Test verifies that once-valid dynamic address host reserveration,
// whose address is within the configured subnet, but whose
// reservation has been removed:
//
// a: Is NAKed upon a renewal attempt
// b: Is released properly upon release, including DNS removal
//
TEST_F(OutOfRangeTest, dynamicHostReservationRemoved) {
    Dhcp4Client client(Dhcp4Client::SELECTING);

    std::string hwaddress = "dd:dd:dd:dd:dd:01";
    std::string expected_address = "";

    oorRenewReleaseTest(NO_HR, hwaddress, expected_address, DOES_NOT_RENEW);
}

// Test verifies that once-valid dynamic address host reserveration,
// whose address is no longer within any configured subnet, and which
// no longer has reservation defined:
//
// a: Is NAKed upon a renewal attempt
// b: Is released properly upon release, including DNS removal
//
TEST_F(OutOfRangeTest, dynamicHostOutOfSubnetReservationRemoved) {
    Dhcp4Client client(Dhcp4Client::SELECTING);

    std::string hwaddress = "dd:dd:dd:dd:dd:01";
    std::string expected_address = "";

    oorRenewReleaseTest(DIFF_SUBNET_NO_HR, hwaddress, expected_address,
                        DOES_NOT_RENEW);
}

// Test verifies that once-valid in-subnet fixed-address host reserveration,
// after the subnet pool changes:
//
// a: Is NAK'd upon a renewal attempt
// b: Is released properly upon release, including DNS removal
//
TEST_F(OutOfRangeTest, fixedHostOutOfSubnet) {
    std::string hwaddress = "ff:ff:ff:ff:ff:01";
    std::string expected_address = "10.0.0.7";

    oorRenewReleaseTest(DIFF_SUBNET, hwaddress, expected_address,
                        DOES_NOT_RENEW);
}


// Test verifies that once-valid in-subnet fixed-address host reserveration,
// after the subnet pool is changed:
//
// a: Is ACK'd upon a renewal attempt
// b: Is released properly upon release, including DNS removal
//
TEST_F(OutOfRangeTest, fixedHostDifferentPool) {
    std::string hwaddress = "ff:ff:ff:ff:ff:01";
    std::string expected_address = "10.0.0.7";

    oorRenewReleaseTest(DIFF_POOL, hwaddress, expected_address, DOES_RENEW);
}

// Test verifies that once-valid in-subnet fixed-address host reserveration,
// whose reservation has been removed from the configuration
//
// a: Is NAK'd upon a renewal attempt
// b: Is released properly upon release, including DNS removal
//
TEST_F(OutOfRangeTest, fixedHostReservationRemoved) {
    std::string hwaddress = "ff:ff:ff:ff:ff:01";
    std::string expected_address = "10.0.0.7";

    oorRenewReleaseTest(NO_HR, hwaddress, expected_address, DOES_NOT_RENEW);
}

// Test verifies that once-valid fixed address host reserveration,
// whose address is no longer within any configured subnet
//
// a: Is NAKed upon a renewal attempt
// b: Is released properly upon release, including DNS removal
//
TEST_F(OutOfRangeTest, fixedHostOutOfSubnetReservationRemoved) {
    std::string hwaddress = "ff:ff:ff:ff:ff:01";
    std::string expected_address = "10.0.0.7";

    oorRenewReleaseTest(DIFF_SUBNET_NO_HR, hwaddress, expected_address,
                        DOES_NOT_RENEW);
}

} // end of anonymous namespace
