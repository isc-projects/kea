// Copyright (C) 2013-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <asiolink/io_address.h>
#include <dhcp/duid.h>
#include <dhcpsrv/lease.h>
#include <util/pointer_util.h>
#include <testutils/test_to_element.h>
#include <cc/data.h>
#include <gtest/gtest.h>
#include <vector>
#include <sstream>

using namespace isc;
using namespace isc::asiolink;
using namespace isc::dhcp;
using namespace isc::data;
using namespace isc::test;

namespace {

/// Hardware address used by different tests.
const uint8_t HWADDR[] = {0x08, 0x00, 0x2b, 0x02, 0x3f, 0x4e};
/// Client id used by different tests.
const uint8_t CLIENTID[] = {0x17, 0x34, 0xe2, 0xff, 0x09, 0x92, 0x54};
/// Valid lifetime value used by different tests.
const uint32_t VALID_LIFETIME = 500;
/// Subnet ID used by different tests.
const uint32_t SUBNET_ID = 42;
/// IAID value used by different tests.
const uint32_t IAID = 7;

/// @brief Creates an instance of the lease with certain FQDN data.
///
/// @param hostname Hostname.
/// @param fqdn_fwd Forward FQDN update setting for a created lease.
/// @param fqdn_rev Reverse FQDN update setting for a created lease.
///
/// @return Instance of the created lease.
Lease4 createLease4(const std::string& hostname, const bool fqdn_fwd,
                    const bool fqdn_rev) {
    Lease4 lease;
    lease.hostname_ = hostname;
    lease.fqdn_fwd_ = fqdn_fwd;
    lease.fqdn_rev_ = fqdn_rev;
    return (lease);
}

/// @brief Tests that an exception is thrown when one of the lease
/// parameters is missing or invalid during lease parsing.
///
/// If the tested parameter is mandatory the test first removes the
/// specified parameter from the JSON structure and tries to re-create
/// the lease, expecting an error.
/// Next, the test sets invalid value for this parameter and also
/// expected an error.
///
/// @tparam LeaseType @c Lease4 or @c Lease6.
/// @tparam ValueType type of the invalid value to be used for the
/// specified parameter.
/// @param lease_as_json a string contains lease in a JSON format.
/// @param parameter_name name of the lease parameter to be tested.
/// @param invalid_value invalid parameter value.
/// @param mandatory boolean value indicating if the parameter is
/// mandatory.
template<typename LeaseType, typename ValueType>
void testInvalidElement(const std::string& lease_as_json,
                        const std::string& parameter_name,
                        ValueType invalid_value,
                        const bool mandatory = true) {
    ElementPtr lease;

    // If the parameter is mandatory, check that the exception is
    // thrown if it is missing.
    if (mandatory) {
        ASSERT_NO_THROW(lease = Element::fromJSON(lease_as_json));
        lease->remove(parameter_name);
        EXPECT_THROW(LeaseType::fromElement(lease), BadValue)
            << "test failed for " << parameter_name;
    }

    // Set invalid value and expect an error.
    ASSERT_NO_THROW(lease = Element::fromJSON(lease_as_json));
    lease->set(parameter_name, Element::create(invalid_value));
    EXPECT_THROW(LeaseType::fromElement(lease), BadValue)
        << "test failed for " << parameter_name
        << " and invalid value " << invalid_value;
}

/// @brief Fixture class used in Lease4 testing.
class Lease4Test : public ::testing::Test {
public:

    /// @brief Default constructor
    ///
    /// Currently it only initializes hardware address.
    Lease4Test() {
        hwaddr_.reset(new HWAddr(HWADDR, sizeof(HWADDR), HTYPE_ETHER));
        clientid_.reset(new ClientId(CLIENTID, sizeof(CLIENTID)));
    }

    /// Hardware address, used by tests.
    HWAddrPtr hwaddr_;

    /// Pointer to the client identifier used by tests.
    ClientIdPtr clientid_;
};

// This test checks if the Lease4 structure can be instantiated correctly.
TEST_F(Lease4Test, constructor) {
     // Get current time for the use in Lease.
    const time_t current_time = time(NULL);

    // We want to check that various addresses work, so let's iterate over
    // these.
    const uint32_t ADDRESS[] = {
        0x00000000, 0x01020304, 0x7fffffff, 0x80000000, 0x80000001, 0xffffffff
    };

    for (int i = 0; i < sizeof(ADDRESS) / sizeof(ADDRESS[0]); ++i) {

        // Create the lease
        Lease4 lease(ADDRESS[i], hwaddr_, clientid_, VALID_LIFETIME,
                     current_time, SUBNET_ID, true, true,
                     "Hostname.Example.Com.");

        EXPECT_EQ(ADDRESS[i], lease.addr_.toUint32());
        EXPECT_TRUE(util::equalValues(hwaddr_, lease.hwaddr_));
        EXPECT_TRUE(util::equalValues(clientid_, lease.client_id_));
        EXPECT_EQ(VALID_LIFETIME, lease.valid_lft_);
        EXPECT_EQ(current_time, lease.cltt_);
        EXPECT_EQ(SUBNET_ID, lease.subnet_id_);
        EXPECT_EQ("hostname.example.com.", lease.hostname_);
        EXPECT_TRUE(lease.fqdn_fwd_);
        EXPECT_TRUE(lease.fqdn_rev_);
        EXPECT_EQ(Lease::STATE_DEFAULT, lease.state_);
        EXPECT_FALSE(lease.getContext());
    }
}

// This test verifies that copy constructor copies Lease4 fields correctly.
TEST_F(Lease4Test, copyConstructor) {

    // Get current time for the use in Lease4.
    const time_t current_time = time(NULL);

    // Create the lease
    Lease4 lease(0xffffffff, hwaddr_, clientid_, VALID_LIFETIME, current_time,
                 SUBNET_ID);

    // Declined is a non-default state. We'll see if the state will be copied
    // or the default state will be set for the copied lease.
    lease.state_ = Lease::STATE_DECLINED;

    // Set an user context.
    lease.setContext(Element::fromJSON("{ \"foobar\": 1234 }"));

    // Use copy constructor to copy the lease.
    Lease4 copied_lease(lease);

    // Both leases should be now equal. When doing this check we assume that
    // the equality operator works correctly.
    EXPECT_TRUE(lease == copied_lease);
    // Client IDs are equal, but they should be in two distinct pointers.
    EXPECT_FALSE(lease.client_id_ == copied_lease.client_id_);

    // User context are equal and point to the same object.
    ASSERT_TRUE(copied_lease.getContext());
    EXPECT_TRUE(lease.getContext() == copied_lease.getContext());
    EXPECT_TRUE(*lease.getContext() == *copied_lease.getContext());

    // Hardware addresses are equal, but they should point to two objects,
    // each holding the same data. The content should be equal...
    EXPECT_TRUE(*lease.hwaddr_ == *copied_lease.hwaddr_);

    // ... but it should point to different objects.
    EXPECT_FALSE(lease.hwaddr_ == copied_lease.hwaddr_);

    // Now let's check that the hwaddr pointer is copied even if it's NULL:
    lease.hwaddr_.reset();
    Lease4 copied_lease2(lease);
    EXPECT_TRUE(lease == copied_lease2);
}

// This test verifies that the assignment operator copies all Lease4 fields
// correctly.
TEST_F(Lease4Test, operatorAssign) {

    // Get the current time for the use in Lease4.
    const time_t current_time = time(NULL);

    // Create the lease
    Lease4 lease(0xffffffff, hwaddr_, clientid_, VALID_LIFETIME, current_time,
                 SUBNET_ID);

    // Declined is a non-default state. We'll see if the state will be copied
    // or the default state will be set for the copied lease.
    lease.state_ = Lease::STATE_DECLINED;

    // Set an user context.
    lease.setContext(Element::fromJSON("{ \"foobar\": 1234 }"));

    // Create a default lease.
    Lease4 copied_lease;
    // Use assignment operator to assign new lease.
    copied_lease = lease;

    // Both leases should be now equal. When doing this check we assume that
    // the equality operator works correctly.
    EXPECT_TRUE(lease == copied_lease);
    // Client IDs are equal, but they should be in two distinct pointers.
    EXPECT_FALSE(lease.client_id_ == copied_lease.client_id_);

    // User context are equal and point to the same object.
    ASSERT_TRUE(copied_lease.getContext());
    EXPECT_TRUE(lease.getContext() == copied_lease.getContext());
    EXPECT_TRUE(*lease.getContext() == *copied_lease.getContext());

    // Hardware addresses are equal, but they should point to two objects,
    // each holding the same data. The content should be equal...
    EXPECT_TRUE(*lease.hwaddr_ == *copied_lease.hwaddr_);

    // ... but it should point to different objects.
    EXPECT_FALSE(lease.hwaddr_ == copied_lease.hwaddr_);

    // Now let's check that the hwaddr pointer is copied even if it's NULL:
    lease.hwaddr_.reset();
    copied_lease = lease;
    EXPECT_TRUE(lease == copied_lease);
}

// This test verifies that it is correctly determined when the lease
// belongs to the particular client identified by the client identifier
// and hw address.
TEST_F(Lease4Test, leaseBelongsToClient) {
    // Client identifier that matches the one in the lease.
    ClientIdPtr matching_client_id = ClientId::fromText("01:02:03:04");
    // Client identifier that doesn't match the one in the lease.
    ClientIdPtr diff_client_id = ClientId::fromText("01:02:03:05");
    // Null (no) client identifier.
    ClientIdPtr null_client_id;

    // HW Address that matches the one in the lease.
    HWAddrPtr matching_hw(new HWAddr(HWAddr::fromText("00:01:02:03:04:05",
                                                      HTYPE_ETHER)));
    // HW Address that doesn't match the one in the lease.
    HWAddrPtr diff_hw(new HWAddr(HWAddr::fromText("00:01:02:03:04:06",
                                                  HTYPE_ETHER)));
    // Null HW Address.
    HWAddrPtr null_hw;

    // Create the lease with MAC address and Client Identifier.
    Lease4 lease(IOAddress("192.0.2.1"), matching_hw, matching_client_id,
                 60, time(NULL), 0, 0, 1);

    // Verify cases for lease that has both hw address and client identifier.
    EXPECT_TRUE(lease.belongsToClient(matching_hw, matching_client_id));
    EXPECT_FALSE(lease.belongsToClient(matching_hw, diff_client_id));
    EXPECT_TRUE(lease.belongsToClient(matching_hw, null_client_id));
    EXPECT_TRUE(lease.belongsToClient(diff_hw, matching_client_id));
    EXPECT_FALSE(lease.belongsToClient(diff_hw, diff_client_id));
    EXPECT_FALSE(lease.belongsToClient(diff_hw, null_client_id));
    EXPECT_TRUE(lease.belongsToClient(null_hw, matching_client_id));
    EXPECT_FALSE(lease.belongsToClient(null_hw, diff_client_id));
    EXPECT_FALSE(lease.belongsToClient(null_hw, null_client_id));


    // Verify cases for lease that has only HW address.
    lease.client_id_ = null_client_id;
    EXPECT_TRUE(lease.belongsToClient(matching_hw, matching_client_id));
    EXPECT_TRUE(lease.belongsToClient(matching_hw, diff_client_id));
    EXPECT_TRUE(lease.belongsToClient(matching_hw, null_client_id));
    EXPECT_FALSE(lease.belongsToClient(diff_hw, matching_client_id));
    EXPECT_FALSE(lease.belongsToClient(diff_hw, diff_client_id));
    EXPECT_FALSE(lease.belongsToClient(diff_hw, null_client_id));
    EXPECT_FALSE(lease.belongsToClient(null_hw, matching_client_id));
    EXPECT_FALSE(lease.belongsToClient(null_hw, diff_client_id));
    EXPECT_FALSE(lease.belongsToClient(null_hw, null_client_id));

    // Verify cases for lease that has only client identifier.
    lease.client_id_ = matching_client_id;
    lease.hwaddr_ = null_hw;
    EXPECT_TRUE(lease.belongsToClient(matching_hw, matching_client_id));
    EXPECT_FALSE(lease.belongsToClient(matching_hw, diff_client_id));
    EXPECT_FALSE(lease.belongsToClient(matching_hw, null_client_id));
    EXPECT_TRUE(lease.belongsToClient(diff_hw, matching_client_id));
    EXPECT_FALSE(lease.belongsToClient(diff_hw, diff_client_id));
    EXPECT_FALSE(lease.belongsToClient(diff_hw, null_client_id));
    EXPECT_TRUE(lease.belongsToClient(null_hw, matching_client_id));
    EXPECT_FALSE(lease.belongsToClient(null_hw, diff_client_id));
    EXPECT_FALSE(lease.belongsToClient(null_hw, null_client_id));
}

/// @brief Lease4 Equality Test
///
/// Checks that the operator==() correctly compares two leases for equality.
/// As operator!=() is also defined for this class, every check on operator==()
/// is followed by the reverse check on operator!=().
TEST_F(Lease4Test, operatorEquals) {

    // Random values for the tests
    const uint32_t ADDRESS = 0x01020304;
    const time_t current_time = time(NULL);

    // Check when the leases are equal.
    Lease4 lease1(ADDRESS, hwaddr_, clientid_, VALID_LIFETIME, current_time,
                  SUBNET_ID);
    lease1.setContext(Element::fromJSON("{ \"foobar\": 1234 }"));

    // We need to make an explicit copy. Otherwise the second lease will just
    // store a pointer and we'll have two leases pointing to a single HWAddr
    // or client. That would make modifications to only one impossible.
    HWAddrPtr hwcopy(new HWAddr(*hwaddr_));
    ClientIdPtr clientid_copy(new ClientId(*clientid_));

    Lease4 lease2(ADDRESS, hwcopy, clientid_copy, VALID_LIFETIME, current_time,
                  SUBNET_ID);
    lease2.setContext(Element::fromJSON("{ \"foobar\": 1234 }"));
    EXPECT_TRUE(lease1 == lease2);
    EXPECT_FALSE(lease1 != lease2);

    // Now vary individual fields in a lease and check that the leases compare
    // not equal in every case.
    lease1.addr_ = IOAddress(ADDRESS + 1);
    EXPECT_FALSE(lease1 == lease2);
    EXPECT_TRUE(lease1 != lease2);
    lease1.addr_ = lease2.addr_;
    EXPECT_TRUE(lease1 == lease2);  // Check that the reversion has made the
    EXPECT_FALSE(lease1 != lease2); // ... leases equal

    ++lease1.hwaddr_->hwaddr_[0];
    EXPECT_FALSE(lease1 == lease2);
    EXPECT_TRUE(lease1 != lease2);
    lease1.hwaddr_ = lease2.hwaddr_;
    EXPECT_TRUE(lease1 == lease2);  // Check that the reversion has made the
    EXPECT_FALSE(lease1 != lease2); // ... leases equal

    std::vector<uint8_t> clientid_vec = clientid_->getClientId();
    ++clientid_vec[0];
    lease1.client_id_.reset(new ClientId(clientid_vec));
    EXPECT_FALSE(lease1 == lease2);
    EXPECT_TRUE(lease1 != lease2);
    --clientid_vec[0];
    lease1.client_id_.reset(new ClientId(clientid_vec));
    EXPECT_TRUE(lease1 == lease2);  // Check that the reversion has made the
    EXPECT_FALSE(lease1 != lease2); // ... leases equal

    ++lease1.valid_lft_;
    EXPECT_FALSE(lease1 == lease2);
    EXPECT_TRUE(lease1 != lease2);
    lease1.valid_lft_ = lease2.valid_lft_;
    EXPECT_TRUE(lease1 == lease2);  // Check that the reversion has made the
    EXPECT_FALSE(lease1 != lease2); // ... leases equal

    ++lease1.cltt_;
    EXPECT_FALSE(lease1 == lease2);
    EXPECT_TRUE(lease1 != lease2);
    lease1.cltt_ = lease2.cltt_;
    EXPECT_TRUE(lease1 == lease2);  // Check that the reversion has made the
    EXPECT_FALSE(lease1 != lease2); // ... leases equal

    ++lease1.subnet_id_;
    EXPECT_FALSE(lease1 == lease2);
    EXPECT_TRUE(lease1 != lease2);
    lease1.subnet_id_ = lease2.subnet_id_;
    EXPECT_TRUE(lease1 == lease2);  // Check that the reversion has made the
    EXPECT_FALSE(lease1 != lease2); // ... leases equal

    lease1.hostname_ += std::string("something random");
    EXPECT_FALSE(lease1 == lease2);
    EXPECT_TRUE(lease1 != lease2);
    lease1.hostname_ = lease2.hostname_;
    EXPECT_TRUE(lease1 == lease2);  // Check that the reversion has made the
    EXPECT_FALSE(lease1 != lease2); // ... leases equal

    lease1.fqdn_fwd_ = !lease1.fqdn_fwd_;
    EXPECT_FALSE(lease1 == lease2);
    EXPECT_TRUE(lease1 != lease2);
    lease1.fqdn_fwd_ = lease2.fqdn_fwd_;
    EXPECT_TRUE(lease1 == lease2);  // Check that the reversion has made the
    EXPECT_FALSE(lease1 != lease2); // ... leases equal

    lease1.fqdn_rev_ = !lease1.fqdn_rev_;
    EXPECT_FALSE(lease1 == lease2);
    EXPECT_TRUE(lease1 != lease2);
    lease1.fqdn_rev_ = lease2.fqdn_rev_;
    EXPECT_TRUE(lease1 == lease2);  // Check that the reversion has made the
    EXPECT_FALSE(lease1 != lease2); // ... leases equal

    lease1.state_  += 1;
    EXPECT_FALSE(lease1 == lease2);
    EXPECT_TRUE(lease1 != lease2);
    lease2.state_ += 1;
    EXPECT_TRUE(lease1 == lease2);  // Check that the reversion has made the
    EXPECT_FALSE(lease1 != lease2); // ... leases equal

    lease1.setContext(Element::fromJSON("{ \"foobar\": 5678 }"));
    EXPECT_FALSE(lease1 == lease2);
    EXPECT_TRUE(lease1 != lease2);
    lease1.setContext(Element::fromJSON("{ \"foobar\": 1234 }"));
    EXPECT_TRUE(lease1 == lease2);  // Check that the reversion has made the
    EXPECT_FALSE(lease1 != lease2); // ... leases equal

    lease1.setContext(ConstElementPtr());
    EXPECT_FALSE(lease1 == lease2);
    EXPECT_TRUE(lease1 != lease2);
    lease2.setContext(ConstElementPtr());
    EXPECT_TRUE(lease1 == lease2);  // Check that no user context has mase the
    EXPECT_FALSE(lease1 != lease2); // ... leases equal
}

// Verify that the client id can be returned as a vector object and if client
// id is NULL the empty vector is returned.
TEST_F(Lease4Test, getClientIdVector) {
    // Create a lease.
    Lease4 lease;
    // By default, the lease should have client id set to NULL. If it doesn't,
    // continuing the test makes no sense.
    ASSERT_FALSE(lease.client_id_);
    // When client id is NULL the vector returned should be empty.
    EXPECT_TRUE(lease.getClientIdVector().empty());

    // Initialize client identifier to non-null value.
    lease.client_id_ = clientid_;
    // Check that the returned vector, encapsulating client id is equal to
    // the one that has been used to set the client id for the lease.
    std::vector<uint8_t> returned_vec = lease.getClientIdVector();
    EXPECT_TRUE(returned_vec == clientid_->getClientId());
}

// Verify the behavior of the function which checks FQDN data for equality.
TEST_F(Lease4Test, hasIdenticalFqdn) {
    Lease4 lease = createLease4("myhost.example.com.", true, true);
    EXPECT_TRUE(lease.hasIdenticalFqdn(createLease4("myhost.example.com.",
                                                     true, true)));
    // Case insensitive comparison.
    EXPECT_TRUE(lease.hasIdenticalFqdn(createLease4("myHOst.ExamplE.coM.",
                                                     true, true)));
    EXPECT_FALSE(lease.hasIdenticalFqdn(createLease4("other.example.com.",
                                                     true, true)));
    EXPECT_FALSE(lease.hasIdenticalFqdn(createLease4("myhost.example.com.",
                                                     false, true)));
    EXPECT_FALSE(lease.hasIdenticalFqdn(createLease4("myhost.example.com.",
                                                     true, false)));
    EXPECT_FALSE(lease.hasIdenticalFqdn(createLease4("myhost.example.com.",
                                                     false, false)));
    EXPECT_FALSE(lease.hasIdenticalFqdn(createLease4("other.example.com.",
                                                     false, false)));
}

// Verify that toText() method reports Lease4 structure properly.
TEST_F(Lease4Test, toText) {

    const time_t current_time = 12345678;
    Lease4 lease(IOAddress("192.0.2.3"), hwaddr_, clientid_, 3600,
                 current_time, 789);
    lease.setContext(Element::fromJSON("{ \"foobar\": 1234 }"));

    std::stringstream expected;
    expected << "Address:       192.0.2.3\n"
             << "Valid life:    3600\n"
             << "Cltt:          12345678\n"
             << "Hardware addr: " << hwaddr_->toText(false) << "\n"
             << "Client id:     " << clientid_->toText() << "\n"
             << "Subnet ID:     789\n"
             << "State:         default\n"
             << "User context:  { \"foobar\": 1234 }\n";

    EXPECT_EQ(expected.str(), lease.toText());

    // Now let's try with a lease without hardware address, client identifier
    // and user context.
    lease.hwaddr_.reset();
    lease.client_id_.reset();
    lease.setContext(ConstElementPtr());
    expected.str("");
    expected << "Address:       192.0.2.3\n"
             << "Valid life:    3600\n"
             << "Cltt:          12345678\n"
             << "Hardware addr: (none)\n"
             << "Client id:     (none)\n"
             << "Subnet ID:     789\n"
             << "State:         default\n";
    EXPECT_EQ(expected.str(), lease.toText());
}

// Verify that Lease4 structure can be converted to JSON properly.
TEST_F(Lease4Test, toElement) {

    const time_t current_time = 12345678;
    Lease4 lease(IOAddress("192.0.2.3"), hwaddr_, clientid_, 3600,
                 current_time, 789, true, true, "URANIA.example.org");
    lease.setContext(Element::fromJSON("{ \"foobar\": 1234 }"));

    std::string expected = "{"
        "\"client-id\": \"17:34:e2:ff:09:92:54\","
        "\"cltt\": 12345678,"
        "\"fqdn-fwd\": true,"
        "\"fqdn-rev\": true,"
        "\"hostname\": \"urania.example.org\","
        "\"hw-address\": \"08:00:2b:02:3f:4e\","
        "\"ip-address\": \"192.0.2.3\","
        "\"state\": 0,"
        "\"subnet-id\": 789,"
        "\"user-context\": { \"foobar\": 1234 },"
        "\"valid-lft\": 3600 "
        "}";

    runToElementTest<Lease4>(expected, lease);

    // Now let's try with a lease without client-id and user context.
    lease.client_id_.reset();
    lease.setContext(ConstElementPtr());

    expected = "{"
        "\"cltt\": 12345678,"
        "\"fqdn-fwd\": true,"
        "\"fqdn-rev\": true,"
        "\"hostname\": \"urania.example.org\","
        "\"hw-address\": \"08:00:2b:02:3f:4e\","
        "\"ip-address\": \"192.0.2.3\","
        "\"state\": 0,"
        "\"subnet-id\": 789,"
        "\"valid-lft\": 3600 "
        "}";

    runToElementTest<Lease4>(expected, lease);

    // And to finish try with a comment.
    lease.setContext(Element::fromJSON("{ \"comment\": \"a comment\" }"));

    expected = "{"
        "\"cltt\": 12345678,"
        "\"user-context\": { \"comment\": \"a comment\" },"
        "\"fqdn-fwd\": true,"
        "\"fqdn-rev\": true,"
        "\"hostname\": \"urania.example.org\","
        "\"hw-address\": \"08:00:2b:02:3f:4e\","
        "\"ip-address\": \"192.0.2.3\","
        "\"state\": 0,"
        "\"subnet-id\": 789,"
        "\"valid-lft\": 3600 "
        "}";

    runToElementTest<Lease4>(expected, lease);
}

// Verify that the Lease4 can be created from JSON.
TEST_F(Lease4Test, fromElement) {
    std::string json = "{"
        "\"client-id\": \"17:34:e2:ff:09:92:54\","
        "\"cltt\": 12345678,"
        "\"fqdn-fwd\": true,"
        "\"fqdn-rev\": true,"
        "\"hostname\": \"urania.example.ORG\","
        "\"hw-address\": \"08:00:2b:02:3f:4e\","
        "\"ip-address\": \"192.0.2.3\","
        "\"state\": 0,"
        "\"subnet-id\": 789,"
        "\"user-context\": { \"foo\": \"bar\" },"
        "\"valid-lft\": 3600 "
        "}";

    Lease4Ptr lease;
    ASSERT_NO_THROW(lease = Lease4::fromElement(Element::fromJSON(json)));

    ASSERT_TRUE(lease);

    EXPECT_EQ("192.0.2.3", lease->addr_.toText());
    EXPECT_EQ(789, static_cast<uint32_t>(lease->subnet_id_));
    ASSERT_TRUE(lease->hwaddr_);
    EXPECT_EQ("hwtype=1 08:00:2b:02:3f:4e", lease->hwaddr_->toText());
    ASSERT_TRUE(lease->client_id_);
    EXPECT_EQ("17:34:e2:ff:09:92:54", lease->client_id_->toText());
    EXPECT_EQ(12345678, lease->cltt_);
    EXPECT_EQ(lease->cltt_, lease->current_cltt_);
    EXPECT_EQ(3600, lease->valid_lft_);
    EXPECT_EQ(lease->valid_lft_, lease->current_valid_lft_);
    EXPECT_TRUE(lease->fqdn_fwd_);
    EXPECT_TRUE(lease->fqdn_rev_);
    EXPECT_EQ("urania.example.org", lease->hostname_);
    EXPECT_EQ(Lease::STATE_DEFAULT, lease->state_);
    ASSERT_TRUE(lease->getContext());
    EXPECT_EQ("{ \"foo\": \"bar\" }", lease->getContext()->str());
}

// Test that specifying invalid values for a lease or not specifying
// mandatory lease parameters causes an error while parsing the lease.
TEST_F(Lease4Test, fromElementInvalidValues) {
    // Create valid configuration. We use it as a base from which we will
    // be removing some of the parameters and some values will be selectively
    // modified.
    std::string json = "{"
        "\"client-id\": \"17:34:e2:ff:09:92:54\","
        "\"cltt\": 12345678,"
        "\"fqdn-fwd\": true,"
        "\"fqdn-rev\": true,"
        "\"hostname\": \"urania.example.org\","
        "\"hw-address\": \"08:00:2b:02:3f:4e\","
        "\"ip-address\": \"192.0.2.3\","
        "\"state\": 0,"
        "\"subnet-id\": 789,"
        "\"valid-lft\": 3600 "
        "}";

    // Test invalid parameter values and missing parameters.
    testInvalidElement<Lease4>(json, "client-id", std::string("rock"), false);
    testInvalidElement<Lease4>(json, "cltt", std::string("xyz"));
    testInvalidElement<Lease4>(json, "cltt", -1, false);
    testInvalidElement<Lease4>(json, "fqdn-fwd", 123);
    testInvalidElement<Lease4>(json, "fqdn-rev", std::string("foo"));
    testInvalidElement<Lease4, bool>(json, "hostname", true);
    testInvalidElement<Lease4>(json, "hw-address", "01::00::");
    testInvalidElement<Lease4>(json, "hw-address", 1234, false);
    testInvalidElement<Lease4, long int>(json, "ip-address", 0xFF000201);
    testInvalidElement<Lease4>(json, "ip-address", "2001:db8:1::1", false);
    testInvalidElement<Lease4>(json, "state", std::string("xyz"));
    testInvalidElement<Lease4>(json, "state", 1234, false);
    testInvalidElement<Lease4>(json, "subnet-id", std::string("xyz"));
    testInvalidElement<Lease4>(json, "subnet-id", -5, false);
    testInvalidElement<Lease4>(json, "subnet-id", 0x100000000, false);
    testInvalidElement<Lease4>(json, "valid-lft", std::string("xyz"));
    testInvalidElement<Lease4>(json, "valid-lft", -3, false);
    testInvalidElement<Lease4>(json, "user-context", "[ ]", false);
    testInvalidElement<Lease4>(json, "user-context", 1234, false);
    testInvalidElement<Lease4>(json, "user-context", false, false);
    testInvalidElement<Lease4>(json, "user-context", "foo", false);
}

// Verify that decline() method properly clears up specific fields.
TEST_F(Lease4Test, decline) {

    const time_t current_time = 12345678;
    Lease4 lease(IOAddress("192.0.2.3"), hwaddr_, clientid_, 3600,
                 current_time, 789);
    lease.hostname_ = "foo.example.org";
    lease.fqdn_fwd_ = true;
    lease.fqdn_rev_ = true;

    time_t now = time(NULL);

    // Move lease to declined state and set its valid-lifetime to 123 seconds
    lease.decline(123);
    ASSERT_TRUE(lease.hwaddr_);
    EXPECT_EQ("", lease.hwaddr_->toText(false));
    EXPECT_FALSE(lease.client_id_);

    EXPECT_TRUE(now <= lease.cltt_);
    EXPECT_TRUE(lease.cltt_ <= now + 1);
    EXPECT_EQ("", lease.hostname_);
    EXPECT_FALSE(lease.fqdn_fwd_);
    EXPECT_FALSE(lease.fqdn_rev_);
    EXPECT_EQ(Lease::STATE_DECLINED, lease.state_);
    EXPECT_EQ(123, lease.valid_lft_);
    EXPECT_FALSE(lease.getContext());
}

// Verify that the lease states are correctly returned in the textual format.
TEST_F(Lease4Test, stateToText) {
    EXPECT_EQ("default", Lease4::statesToText(Lease::STATE_DEFAULT));
    EXPECT_EQ("declined", Lease4::statesToText(Lease::STATE_DECLINED));
    EXPECT_EQ("expired-reclaimed", Lease4::statesToText(Lease::STATE_EXPIRED_RECLAIMED));
}

/// @brief Creates an instance of the lease with certain FQDN data.
///
/// @param hostname Hostname.
/// @param fqdn_fwd Forward FQDN update setting for a created lease.
/// @param fqdn_rev Reverse FQDN update setting for a created lease.
///
/// @return Instance of the created lease.
Lease6 createLease6(const std::string& hostname, const bool fqdn_fwd,
                    const bool fqdn_rev) {
    Lease6 lease;
    lease.hostname_ = hostname;
    lease.fqdn_fwd_ = fqdn_fwd;
    lease.fqdn_rev_ = fqdn_rev;
    return (lease);
}

// Lease6 is also defined in lease_mgr.h, so is tested in this file as well.
// This test checks if the Lease6 structure can be instantiated correctly
TEST(Lease6Test, Lease6ConstructorDefault) {

    // check a variety of addresses with different bits set.
    const char* ADDRESS[] = {
        "::", "::1", "2001:db8:1::456",
        "7fff:ffff:ffff:ffff:ffff:ffff:ffff:ffff",
        "8000::", "8000::1",
        "ffff:ffff:ffff:ffff:ffff:ffff:ffff:ffff"
    };

    // Other values
    uint8_t llt[] = {0, 1, 2, 3, 4, 5, 6, 0xa, 0xb, 0xc, 0xd, 0xe, 0xf};
    DuidPtr duid(new DUID(llt, sizeof(llt)));
    uint32_t iaid = IAID;   // Just a number
    SubnetID subnet_id = 8; // Just another number

    for (int i = 0; i < sizeof(ADDRESS) / sizeof(ADDRESS[0]); ++i) {
        IOAddress addr(ADDRESS[i]);
        Lease6Ptr lease(new Lease6(Lease::TYPE_NA, addr,
                               duid, iaid, 100, 200,
                               subnet_id));

        EXPECT_TRUE(lease->addr_ == addr);
        EXPECT_TRUE(*lease->duid_ == *duid);
        EXPECT_TRUE(lease->iaid_ == iaid);
        EXPECT_TRUE(lease->subnet_id_ == subnet_id);
        EXPECT_TRUE(lease->type_ == Lease::TYPE_NA);
        EXPECT_TRUE(lease->preferred_lft_ == 100);
        EXPECT_TRUE(lease->valid_lft_ == 200);
        EXPECT_FALSE(lease->fqdn_fwd_);
        EXPECT_FALSE(lease->fqdn_rev_);
        EXPECT_TRUE(lease->hostname_.empty());
        EXPECT_FALSE(lease->getContext());
    }

    // Lease6 must be instantiated with a DUID, not with NULL pointer
    IOAddress addr(ADDRESS[0]);
    Lease6Ptr lease2;
    EXPECT_THROW(lease2.reset(new Lease6(Lease::TYPE_NA, addr,
                                         DuidPtr(), iaid, 100, 200,
                                         subnet_id)), InvalidOperation);
}

// This test verifies that the Lease6 constructor which accepts FQDN data,
// sets the data correctly for the lease.
TEST(Lease6Test, Lease6ConstructorWithFQDN) {

    // check a variety of addresses with different bits set.
    const char* ADDRESS[] = {
        "::", "::1", "2001:db8:1::456",
        "7fff:ffff:ffff:ffff:ffff:ffff:ffff:ffff",
        "8000::", "8000::1",
        "ffff:ffff:ffff:ffff:ffff:ffff:ffff:ffff"
    };

    // Other values
    uint8_t llt[] = {0, 1, 2, 3, 4, 5, 6, 0xa, 0xb, 0xc, 0xd, 0xe, 0xf};
    DuidPtr duid(new DUID(llt, sizeof(llt)));
    uint32_t iaid = IAID;   // Just a number
    SubnetID subnet_id = 8; // Just another number

    for (int i = 0; i < sizeof(ADDRESS) / sizeof(ADDRESS[0]); ++i) {
        IOAddress addr(ADDRESS[i]);
        Lease6Ptr lease(new Lease6(Lease::TYPE_NA, addr,
                                   duid, iaid, 100, 200, subnet_id,
                                   true, true, "Host.Example.Com."));

        EXPECT_TRUE(lease->addr_ == addr);
        EXPECT_TRUE(*lease->duid_ == *duid);
        EXPECT_TRUE(lease->iaid_ == iaid);
        EXPECT_TRUE(lease->subnet_id_ == subnet_id);
        EXPECT_TRUE(lease->type_ == Lease::TYPE_NA);
        EXPECT_TRUE(lease->preferred_lft_ == 100);
        EXPECT_TRUE(lease->valid_lft_ == 200);
        EXPECT_TRUE(lease->fqdn_fwd_);
        EXPECT_TRUE(lease->fqdn_rev_);
        EXPECT_EQ("host.example.com.", lease->hostname_);
    }

    // Lease6 must be instantiated with a DUID, not with NULL pointer
    IOAddress addr(ADDRESS[0]);
    Lease6Ptr lease2;
    EXPECT_THROW(lease2.reset(new Lease6(Lease::TYPE_NA, addr,
                                         DuidPtr(), iaid, 100, 200,
                                         subnet_id)), InvalidOperation);
}

/// @brief Lease6 Equality Test
///
/// Checks that the operator==() correctly compares two leases for equality.
/// As operator!=() is also defined for this class, every check on operator==()
/// is followed by the reverse check on operator!=().
TEST(Lease6Test, operatorEquals) {

    // check a variety of addresses with different bits set.
    const IOAddress addr("2001:db8:1::456");
    uint8_t duid_array[] = {0, 1, 2, 3, 4, 5, 6, 0xa, 0xb, 0xc, 0xd, 0xe, 0xf};
    DuidPtr duid(new DUID(duid_array, sizeof(duid_array)));
    uint32_t iaid = IAID;   // just a number
    SubnetID subnet_id = 8; // just another number

    // Check for equality.
    Lease6 lease1(Lease::TYPE_NA, addr, duid, iaid, 100, 200, subnet_id);
    Lease6 lease2(Lease::TYPE_NA, addr, duid, iaid, 100, 200, subnet_id);

    lease1.setContext(Element::fromJSON("{ \"foobar\": 1234 }"));
    lease2.setContext(Element::fromJSON("{ \"foobar\": 1234 }"));

    // cltt_ constructs with time(NULL), make sure they are always equal
    lease1.cltt_ = lease2.cltt_;

    EXPECT_TRUE(lease1 == lease2);
    EXPECT_FALSE(lease1 != lease2);

    // Go through and alter all the fields one by one

    lease1.addr_ = IOAddress("::1");
    EXPECT_FALSE(lease1 == lease2);
    EXPECT_TRUE(lease1 != lease2);
    lease1.addr_ = lease2.addr_;
    EXPECT_TRUE(lease1 == lease2);  // Check that the reversion has made the
    EXPECT_FALSE(lease1 != lease2); // ... leases equal

    lease1.type_ = Lease::TYPE_PD;
    EXPECT_FALSE(lease1 == lease2);
    EXPECT_TRUE(lease1 != lease2);
    lease1.type_ = lease2.type_;
    EXPECT_TRUE(lease1 == lease2);  // Check that the reversion has made the
    EXPECT_FALSE(lease1 != lease2); // ... leases equal

    ++lease1.prefixlen_;
    EXPECT_FALSE(lease1 == lease2);
    EXPECT_TRUE(lease1 != lease2);
    lease1.prefixlen_ = lease2.prefixlen_;
    EXPECT_TRUE(lease1 == lease2);  // Check that the reversion has made the
    EXPECT_FALSE(lease1 != lease2); // ... leases equal

    ++lease1.iaid_;
    EXPECT_FALSE(lease1 == lease2);
    EXPECT_TRUE(lease1 != lease2);
    lease1.iaid_ = lease2.iaid_;
    EXPECT_TRUE(lease1 == lease2);  // Check that the reversion has made the
    EXPECT_FALSE(lease1 != lease2); // ... leases equal

    ++duid_array[0];
    lease1.duid_.reset(new DUID(duid_array, sizeof(duid_array)));
    EXPECT_FALSE(lease1 == lease2);
    EXPECT_TRUE(lease1 != lease2);
    --duid_array[0];
    lease1.duid_.reset(new DUID(duid_array, sizeof(duid_array)));
    EXPECT_TRUE(lease1 == lease2);  // Check that the reversion has made the
    EXPECT_FALSE(lease1 != lease2); // ... leases equal

    ++lease1.preferred_lft_;
    EXPECT_FALSE(lease1 == lease2);
    EXPECT_TRUE(lease1 != lease2);
    lease1.preferred_lft_ = lease2.preferred_lft_;
    EXPECT_TRUE(lease1 == lease2);  // Check that the reversion has made the
    EXPECT_FALSE(lease1 != lease2); // ... leases equal

    ++lease1.valid_lft_;
    EXPECT_FALSE(lease1 == lease2);
    EXPECT_TRUE(lease1 != lease2);
    lease1.valid_lft_ = lease2.valid_lft_;
    EXPECT_TRUE(lease1 == lease2);  // Check that the reversion has made the
    EXPECT_FALSE(lease1 != lease2); // ... leases equal

    ++lease1.cltt_;
    EXPECT_FALSE(lease1 == lease2);
    EXPECT_TRUE(lease1 != lease2);
    lease1.cltt_ = lease2.cltt_;
    EXPECT_TRUE(lease1 == lease2);  // Check that the reversion has made the
    EXPECT_FALSE(lease1 != lease2); // ... leases equal

    ++lease1.subnet_id_;
    EXPECT_FALSE(lease1 == lease2);
    EXPECT_TRUE(lease1 != lease2);
    lease1.subnet_id_ = lease2.subnet_id_;
    EXPECT_TRUE(lease1 == lease2);  // Check that the reversion has made the
    EXPECT_FALSE(lease1 != lease2); // ... leases equal

    lease1.hostname_ += std::string("something random");
    EXPECT_FALSE(lease1 == lease2);
    EXPECT_TRUE(lease1 != lease2);
    lease1.hostname_ = lease2.hostname_;
    EXPECT_TRUE(lease1 == lease2);  // Check that the reversion has made the
    EXPECT_FALSE(lease1 != lease2); // ... leases equal

    lease1.fqdn_fwd_ = !lease1.fqdn_fwd_;
    EXPECT_FALSE(lease1 == lease2);
    EXPECT_TRUE(lease1 != lease2);
    lease1.fqdn_fwd_ = lease2.fqdn_fwd_;
    EXPECT_TRUE(lease1 == lease2);  // Check that the reversion has made the
    EXPECT_FALSE(lease1 != lease2); // ... leases equal

    lease1.fqdn_rev_ = !lease1.fqdn_rev_;
    EXPECT_FALSE(lease1 == lease2);
    EXPECT_TRUE(lease1 != lease2);
    lease1.fqdn_rev_ = lease2.fqdn_rev_;
    EXPECT_TRUE(lease1 == lease2);  // Check that the reversion has made the
    EXPECT_FALSE(lease1 != lease2); // ... leases equal

    lease1.state_  += 1;
    EXPECT_FALSE(lease1 == lease2);
    EXPECT_TRUE(lease1 != lease2);
    lease2.state_ += 1;
    EXPECT_TRUE(lease1 == lease2);  // Check that the reversion has made the
    EXPECT_FALSE(lease1 != lease2); // ... leases equal

    lease1.setContext(Element::fromJSON("{ \"foobar\": 5678 }"));
    EXPECT_FALSE(lease1 == lease2);
    EXPECT_TRUE(lease1 != lease2);
    lease1.setContext(Element::fromJSON("{ \"foobar\": 1234 }"));
    EXPECT_TRUE(lease1 == lease2);  // Check that the reversion has made the
    EXPECT_FALSE(lease1 != lease2); // ... leases equal

    lease1.setContext(ConstElementPtr());
    EXPECT_FALSE(lease1 == lease2);
    EXPECT_TRUE(lease1 != lease2);
    lease2.setContext(ConstElementPtr());
    EXPECT_TRUE(lease1 == lease2);  // Check that no user context has mase the
    EXPECT_FALSE(lease1 != lease2); // ... leases equal
}

// Checks if lease expiration is calculated properly
TEST(Lease6Test, Lease6Expired) {
    const IOAddress addr("2001:db8:1::456");
    const uint8_t duid_array[] = {0, 1, 2, 3, 4, 5, 6, 0xa, 0xb, 0xc, 0xd, 0xe, 0xf};
    const DuidPtr duid(new DUID(duid_array, sizeof(duid_array)));
    const uint32_t iaid = IAID;     // Just a number
    const SubnetID subnet_id = 8;   // Just another number
    Lease6 lease(Lease::TYPE_NA, addr, duid, iaid, 100, 200, subnet_id);

    // Case 1: a second before expiration
    lease.cltt_ = time(NULL) - 100;
    lease.valid_lft_ = 101;
    EXPECT_FALSE(lease.expired());

    // Case 2: the lease will expire after this second is concluded
    lease.cltt_ = time(NULL) - 101;
    EXPECT_FALSE(lease.expired());

    // Case 3: the lease is expired
    lease.cltt_ = time(NULL) - 102;
    EXPECT_TRUE(lease.expired());

    // Case 4: the lease is static
    lease.cltt_ = 1;
    lease.valid_lft_ = Lease::INFINITY_LFT;
    EXPECT_FALSE(lease.expired());
}

// Verify that the DUID can be returned as a vector object and if DUID is NULL
// the empty vector is returned.
TEST(Lease6Test, getDuidVector) {
    // Create a lease.
    Lease6 lease;
    // By default, the lease should have client id set to NULL. If it doesn't,
    // continuing the test makes no sense.
    ASSERT_FALSE(lease.duid_);
    // When client id is NULL the vector returned should be empty.
    EXPECT_TRUE(lease.getDuidVector().empty());
    // Now, let's set the non NULL DUID. Fill it with the 8 bytes, each
    // holding a value of 0x42.
    std::vector<uint8_t> duid_vec(8, 0x42);
    lease.duid_ = DuidPtr(new DUID(duid_vec));
    // Check that the returned vector, encapsulating DUID is equal to
    // the one that has been used to set the DUID for the lease.
    std::vector<uint8_t> returned_vec = lease.getDuidVector();
    EXPECT_TRUE(returned_vec == duid_vec);
}

// Verify that decline() method properly clears up specific fields.
TEST(Lease6Test, decline) {

    uint8_t llt[] = {0, 1, 2, 3, 4, 5, 6, 0xa, 0xb, 0xc, 0xd, 0xe, 0xf};
    DuidPtr duid(new DUID(llt, sizeof(llt)));

    HWAddrPtr hwaddr(new HWAddr(HWADDR, sizeof(HWADDR), HTYPE_ETHER));

    // Let's create a lease for 2001:db8::1, DUID, iaid=1234,
    // pref=3000, valid=4000, subnet-id = 1
    Lease6 lease(Lease::TYPE_NA, IOAddress("2001:db8::1"), duid,
                 1234, 3000, 4000, 1, hwaddr);
    lease.cltt_ = 12345678;
    lease.hostname_ = "foo.example.org";
    lease.fqdn_fwd_ = true;
    lease.fqdn_rev_ = true;

    time_t now = time(NULL);

    // Move the lease to declined state and set probation-period to 123 seconds
    lease.decline(123);

    ASSERT_TRUE(lease.duid_);
    ASSERT_EQ("00", lease.duid_->toText());
    ASSERT_FALSE(lease.hwaddr_);
    EXPECT_EQ(0, lease.preferred_lft_);

    EXPECT_TRUE(now <= lease.cltt_);
    EXPECT_TRUE(lease.cltt_ <= now + 1);
    EXPECT_EQ("", lease.hostname_);
    EXPECT_FALSE(lease.fqdn_fwd_);
    EXPECT_FALSE(lease.fqdn_rev_);
    EXPECT_EQ(Lease::STATE_DECLINED, lease.state_);
    EXPECT_EQ(123, lease.valid_lft_);
    EXPECT_FALSE(lease.getContext());
}

// Verify the behavior of the function which checks FQDN data for equality.
TEST(Lease6Test, hasIdenticalFqdn) {
    Lease6 lease = createLease6("myhost.example.com.", true, true);
    EXPECT_TRUE(lease.hasIdenticalFqdn(createLease6("myhost.example.com.",
                                                    true, true)));
    // Case insensitive comparison.
    EXPECT_TRUE(lease.hasIdenticalFqdn(createLease6("myHOst.ExamplE.coM.",
                                                    true, true)));
    EXPECT_FALSE(lease.hasIdenticalFqdn(createLease6("other.example.com.",
                                                     true, true)));
    EXPECT_FALSE(lease.hasIdenticalFqdn(createLease6("myhost.example.com.",
                                                     false, true)));
    EXPECT_FALSE(lease.hasIdenticalFqdn(createLease6("myhost.example.com.",
                                                     true, false)));
    EXPECT_FALSE(lease.hasIdenticalFqdn(createLease6("myhost.example.com.",
                                                     false, false)));
    EXPECT_FALSE(lease.hasIdenticalFqdn(createLease6("other.example.com.",
                                                     false, false)));
}

// Verify that toText() method reports Lease6 structure properly.
TEST(Lease6Test, toText) {

    HWAddrPtr hwaddr(new HWAddr(HWADDR, sizeof(HWADDR), HTYPE_ETHER));

    uint8_t llt[] = {0, 1, 2, 3, 4, 5, 6, 0xa, 0xb, 0xc, 0xd, 0xe, 0xf};
    DuidPtr duid(new DUID(llt, sizeof(llt)));

    Lease6 lease(Lease::TYPE_NA, IOAddress("2001:db8::1"), duid, 123456,
                 400, 800, 5678, hwaddr, 128);
    lease.cltt_ = 12345678;
    lease.state_ = Lease::STATE_DECLINED;
    lease.setContext(Element::fromJSON("{ \"foobar\": 1234 }"));

    std::stringstream expected;
    expected << "Type:          IA_NA(" << static_cast<int>(Lease::TYPE_NA) << ")\n"
             << "Address:       2001:db8::1\n"
             << "Prefix length: 128\n"
             << "IAID:          123456\n"
             << "Pref life:     400\n"
             << "Valid life:    800\n"
             << "Cltt:          12345678\n"
             << "DUID:          00:01:02:03:04:05:06:0a:0b:0c:0d:0e:0f\n"
             << "Hardware addr: " << hwaddr->toText(false) << "\n"
             << "Subnet ID:     5678\n"
             << "State:         declined\n"
             << "User context:  { \"foobar\": 1234 }\n";

    EXPECT_EQ(expected.str(), lease.toText());

    // Now let's try with a lease without hardware address and user context.
    lease.hwaddr_.reset();
    lease.setContext(ConstElementPtr());
    expected.str("");
    expected << "Type:          IA_NA(" << static_cast<int>(Lease::TYPE_NA) << ")\n"
             << "Address:       2001:db8::1\n"
             << "Prefix length: 128\n"
             << "IAID:          123456\n"
             << "Pref life:     400\n"
             << "Valid life:    800\n"
             << "Cltt:          12345678\n"
             << "DUID:          00:01:02:03:04:05:06:0a:0b:0c:0d:0e:0f\n"
             << "Hardware addr: (none)\n"
             << "Subnet ID:     5678\n"
             << "State:         declined\n";
    EXPECT_EQ(expected.str(), lease.toText());
}

// Verify that Lease6 structure can be converted to JSON properly.
// This tests an address lease conversion.
TEST(Lease6Test, toElementAddress) {

    HWAddrPtr hwaddr(new HWAddr(HWADDR, sizeof(HWADDR), HTYPE_ETHER));

    uint8_t llt[] = {0, 1, 2, 3, 4, 5, 6, 0xa, 0xb, 0xc, 0xd, 0xe, 0xf};
    DuidPtr duid(new DUID(llt, sizeof(llt)));

    Lease6 lease(Lease::TYPE_NA, IOAddress("2001:db8::1"), duid, 123456,
                 400, 800, 5678, hwaddr, 128);
    lease.cltt_ = 12345678;
    lease.state_ = Lease::STATE_DECLINED;
    lease.hostname_ = "urania.example.org";
    lease.setContext(Element::fromJSON("{ \"foobar\": 1234 }"));

    std::string expected = "{"
        "\"cltt\": 12345678,"
        "\"duid\": \"00:01:02:03:04:05:06:0a:0b:0c:0d:0e:0f\","
        "\"fqdn-fwd\": false,"
        "\"fqdn-rev\": false,"
        "\"hostname\": \"urania.example.org\","
        "\"hw-address\": \"08:00:2b:02:3f:4e\","
        "\"iaid\": 123456,"
        "\"ip-address\": \"2001:db8::1\","
        "\"preferred-lft\": 400,"
        "\"state\": 1,"
        "\"subnet-id\": 5678,"
        "\"type\": \"IA_NA\","
        "\"user-context\": { \"foobar\": 1234 },"
        "\"valid-lft\": 800"
        "}";

    runToElementTest<Lease6>(expected, lease);

    // Now let's try with a lease without hardware address and user context.
    lease.hwaddr_.reset();
    lease.setContext(ConstElementPtr());

    expected = "{"
        "\"cltt\": 12345678,"
        "\"duid\": \"00:01:02:03:04:05:06:0a:0b:0c:0d:0e:0f\","
        "\"fqdn-fwd\": false,"
        "\"fqdn-rev\": false,"
        "\"hostname\": \"urania.example.org\","
        "\"iaid\": 123456,"
        "\"ip-address\": \"2001:db8::1\","
        "\"preferred-lft\": 400,"
        "\"state\": 1,"
        "\"subnet-id\": 5678,"
        "\"type\": \"IA_NA\","
        "\"valid-lft\": 800"
        "}";

    runToElementTest<Lease6>(expected, lease);

    // And to finish try with a comment.
    lease.setContext(Element::fromJSON("{ \"comment\": \"a comment\" }"));

    expected = "{"
        "\"cltt\": 12345678,"
        "\"user-context\": { \"comment\": \"a comment\" },"
        "\"duid\": \"00:01:02:03:04:05:06:0a:0b:0c:0d:0e:0f\","
        "\"fqdn-fwd\": false,"
        "\"fqdn-rev\": false,"
        "\"hostname\": \"urania.example.org\","
        "\"iaid\": 123456,"
        "\"ip-address\": \"2001:db8::1\","
        "\"preferred-lft\": 400,"
        "\"state\": 1,"
        "\"subnet-id\": 5678,"
        "\"type\": \"IA_NA\","
        "\"valid-lft\": 800"
        "}";

    runToElementTest<Lease6>(expected, lease);
}

// Verify that Lease6 structure can be converted to JSON properly.
// This tests an address lease conversion.
TEST(Lease6Test, toElementPrefix) {

    HWAddrPtr hwaddr(new HWAddr(HWADDR, sizeof(HWADDR), HTYPE_ETHER));

    uint8_t llt[] = {0, 1, 2, 3, 4, 5, 6, 0xa, 0xb, 0xc, 0xd, 0xe, 0xf};
    DuidPtr duid(new DUID(llt, sizeof(llt)));

    Lease6 lease(Lease::TYPE_PD, IOAddress("2001:db8::"), duid, 123456,
                 400, 800, 5678, hwaddr, 56);
    lease.cltt_ = 12345678;
    lease.state_ = Lease::STATE_DEFAULT;
    lease.hostname_ = "urania.example.org";
    lease.setContext(Element::fromJSON("{ \"foobar\": 1234 }"));

    ElementPtr l = lease.toElement();

    ASSERT_TRUE(l);

    ASSERT_TRUE(l->contains("ip-address"));
    EXPECT_EQ("2001:db8::", l->get("ip-address")->stringValue());

    ASSERT_TRUE(l->contains("type"));
    EXPECT_EQ("IA_PD", l->get("type")->stringValue());

    // This is a prefix lease, it must have a prefix length.
    ASSERT_TRUE(l->contains("prefix-len"));
    EXPECT_EQ(56, l->get("prefix-len")->intValue());

    ASSERT_TRUE(l->contains("iaid"));
    EXPECT_EQ(123456, l->get("iaid")->intValue());

    ASSERT_TRUE(l->contains("preferred-lft"));
    EXPECT_EQ(400, l->get("preferred-lft")->intValue());

    ASSERT_TRUE(l->contains("valid-lft"));
    EXPECT_EQ(800, l->get("valid-lft")->intValue());

    ASSERT_TRUE(l->contains("duid"));
    EXPECT_EQ("00:01:02:03:04:05:06:0a:0b:0c:0d:0e:0f",
              l->get("duid")->stringValue());

    ASSERT_TRUE(l->contains("hw-address"));
    EXPECT_EQ(hwaddr->toText(false), l->get("hw-address")->stringValue());

    ASSERT_TRUE(l->contains("subnet-id"));
    EXPECT_EQ(5678, l->get("subnet-id")->intValue());

    ASSERT_TRUE(l->contains("state"));
    EXPECT_EQ(static_cast<int>(Lease::STATE_DEFAULT),
              l->get("state")->intValue());

    ASSERT_TRUE(l->contains("fqdn-fwd"));
    EXPECT_FALSE(l->get("fqdn-fwd")->boolValue());

    ASSERT_TRUE(l->contains("fqdn-rev"));
    EXPECT_FALSE(l->get("fqdn-rev")->boolValue());

    ASSERT_TRUE(l->contains("hostname"));
    EXPECT_EQ("urania.example.org", l->get("hostname")->stringValue());

    ASSERT_TRUE(l->contains("user-context"));
    EXPECT_EQ("{ \"foobar\": 1234 }", l->get("user-context")->str());

    // Now let's try with a lease without hardware address or user context.
    lease.hwaddr_.reset();
    lease.setContext(ConstElementPtr());
    l = lease.toElement();
    EXPECT_FALSE(l->contains("hw-address"));
    EXPECT_FALSE(l->contains("user-context"));

    // And to finish try with a comment.
    lease.setContext(Element::fromJSON("{ \"comment\": \"a comment\" }"));
    l = lease.toElement();
    EXPECT_FALSE(l->contains("hw-address"));
    ConstElementPtr ctx = l->get("user-context");
    ASSERT_TRUE(ctx);
    ASSERT_EQ(Element::map, ctx->getType());
    EXPECT_EQ(1, ctx->size());
    ASSERT_TRUE(ctx->contains("comment"));
    EXPECT_EQ("a comment", ctx->get("comment")->stringValue());
}

// Verify that the IA_NA can be created from JSON.
TEST(Lease6Test, fromElementNA) {
    std::string json = "{"
        "\"cltt\": 12345678,"
        "\"duid\": \"00:01:02:03:04:05:06:0a:0b:0c:0d:0e:0f\","
        "\"fqdn-fwd\": false,"
        "\"fqdn-rev\": false,"
        "\"hostname\": \"urania.EXAMPLE.org\","
        "\"hw-address\": \"08:00:2b:02:3f:4e\","
        "\"iaid\": 123456,"
        "\"ip-address\": \"2001:db8::1\","
        "\"preferred-lft\": 400,"
        "\"state\": 1,"
        "\"subnet-id\": 5678,"
        "\"type\": \"IA_NA\","
        "\"user-context\": { \"foobar\": 1234 },"
        "\"valid-lft\": 800"
        "}";

    Lease6Ptr lease;
    ASSERT_NO_THROW(lease = Lease6::fromElement(Element::fromJSON(json)));

    ASSERT_TRUE(lease);

    EXPECT_EQ("2001:db8::1", lease->addr_.toText());
    EXPECT_EQ(5678, static_cast<uint32_t>(lease->subnet_id_));
    ASSERT_TRUE(lease->hwaddr_);
    EXPECT_EQ("hwtype=1 08:00:2b:02:3f:4e", lease->hwaddr_->toText());
    EXPECT_EQ(12345678, lease->cltt_);
    EXPECT_EQ(lease->cltt_, lease->current_cltt_);
    EXPECT_EQ(800, lease->valid_lft_);
    EXPECT_EQ(lease->valid_lft_, lease->current_valid_lft_);
    EXPECT_FALSE(lease->fqdn_fwd_);
    EXPECT_FALSE(lease->fqdn_rev_);
    EXPECT_EQ("urania.example.org", lease->hostname_);
    EXPECT_EQ(Lease::STATE_DECLINED, lease->state_);
    ASSERT_TRUE(lease->getContext());
    EXPECT_EQ("{ \"foobar\": 1234 }", lease->getContext()->str());

    // IPv6 specific properties.
    EXPECT_EQ(Lease::TYPE_NA, lease->type_);
    EXPECT_EQ(0, lease->prefixlen_);
    EXPECT_EQ(123456, lease->iaid_);
    ASSERT_TRUE(lease->duid_);
    EXPECT_EQ("00:01:02:03:04:05:06:0a:0b:0c:0d:0e:0f", lease->duid_->toText());
    EXPECT_EQ(400, lease->preferred_lft_);
}

// Verify that the IA_PD can be created from JSON.
TEST(Lease6Test, fromElementPD) {
    std::string json = "{"
        "\"cltt\": 12345678,"
        "\"duid\": \"00:01:02:03:04:05:06:0a:0b:0c:0d:0e:0f\","
        "\"fqdn-fwd\": false,"
        "\"fqdn-rev\": false,"
        "\"hostname\": \"uraniA.exaMple.orG\","
        "\"hw-address\": \"08:00:2b:02:3f:4e\","
        "\"iaid\": 123456,"
        "\"ip-address\": \"3000::\","
        "\"preferred-lft\": 400,"
        "\"prefix-len\": 32,"
        "\"state\": 0,"
        "\"subnet-id\": 1234,"
        "\"type\": \"IA_PD\","
        "\"valid-lft\": 600"
        "}";

    Lease6Ptr lease;
    ASSERT_NO_THROW(lease = Lease6::fromElement(Element::fromJSON(json)));

    ASSERT_TRUE(lease);

    EXPECT_EQ("3000::", lease->addr_.toText());
    EXPECT_EQ(1234, static_cast<uint32_t>(lease->subnet_id_));
    ASSERT_TRUE(lease->hwaddr_);
    EXPECT_EQ("hwtype=1 08:00:2b:02:3f:4e", lease->hwaddr_->toText());
    EXPECT_EQ(12345678, lease->cltt_);
    EXPECT_EQ(lease->cltt_, lease->current_cltt_);
    EXPECT_EQ(600, lease->valid_lft_);
    EXPECT_EQ(lease->valid_lft_, lease->current_valid_lft_);
    EXPECT_FALSE(lease->fqdn_fwd_);
    EXPECT_FALSE(lease->fqdn_rev_);
    EXPECT_EQ("urania.example.org", lease->hostname_);
    EXPECT_EQ(Lease::STATE_DEFAULT , lease->state_);
    EXPECT_FALSE(lease->getContext());

    // IPv6 specific properties.
    EXPECT_EQ(Lease::TYPE_PD, lease->type_);
    EXPECT_EQ(32, static_cast<int>(lease->prefixlen_));
    EXPECT_EQ(123456, lease->iaid_);
    ASSERT_TRUE(lease->duid_);
    EXPECT_EQ("00:01:02:03:04:05:06:0a:0b:0c:0d:0e:0f", lease->duid_->toText());
    EXPECT_EQ(400, lease->preferred_lft_);
}

// Test that specifying invalid values for a lease or not specifying
// mandatory lease parameters causes an error while parsing the lease.
TEST(Lease6Test, fromElementInvalidValues) {
    // Create valid configuration. We use it as a base from which we will
    // be removing some of the parameters and some values will be selectively
    // modified.
    std::string json = "{"
        "\"cltt\": 12345678,"
        "\"duid\": \"00:01:02:03:04:05:06:0a:0b:0c:0d:0e:0f\","
        "\"fqdn-fwd\": false,"
        "\"fqdn-rev\": false,"
        "\"hostname\": \"urania.example.org\","
        "\"hw-address\": \"08:00:2b:02:3f:4e\","
        "\"iaid\": 123456,"
        "\"ip-address\": \"3000::\","
        "\"preferred-lft\": 400,"
        "\"prefix-len\": 32,"
        "\"state\": 0,"
        "\"subnet-id\": 1234,"
        "\"type\": \"IA_PD\","
        "\"valid-lft\": 600"
        "}";

    // Test invalid parameter values and missing parameters.
    testInvalidElement<Lease6>(json, "cltt", std::string("xyz"));
    testInvalidElement<Lease6>(json, "cltt", -1, false);
    testInvalidElement<Lease6>(json, "duid", "01::00::");
    testInvalidElement<Lease6>(json, "duid", 1234, false);
    testInvalidElement<Lease6>(json, "fqdn-fwd", 123);
    testInvalidElement<Lease6>(json, "fqdn-rev", std::string("foo"));
    testInvalidElement<Lease6, bool>(json, "hostname", true);
    testInvalidElement<Lease6>(json, "hw-address", "01::00::", false);
    testInvalidElement<Lease6>(json, "hw-address", 1234, false);
    testInvalidElement<Lease6>(json, "iaid", std::string("1234"));
    testInvalidElement<Lease6>(json, "iaid", -1);
    testInvalidElement<Lease6, long int>(json, "ip-address", 0xFF000201);
    testInvalidElement<Lease6>(json, "ip-address", "192.0.2.0", false);
    testInvalidElement<Lease6>(json, "preferred-lft", std::string("1234"));
    testInvalidElement<Lease6>(json, "preferred-lft", -1, false);
    testInvalidElement<Lease6>(json, "prefix-len", std::string("1234"));
    testInvalidElement<Lease6>(json, "prefix-len", 130);
    testInvalidElement<Lease6>(json, "state", std::string("xyz"));
    testInvalidElement<Lease6>(json, "state", 1234, false);
    testInvalidElement<Lease6>(json, "subnet-id", std::string("xyz"));
    testInvalidElement<Lease6>(json, "subnet-id", -5, false);
    testInvalidElement<Lease6>(json, "subnet-id", 0x100000000, false);
    testInvalidElement<Lease6>(json, "type", std::string("IA_XY"));
    testInvalidElement<Lease6>(json, "type", -3, false);
    testInvalidElement<Lease6>(json, "valid-lft", std::string("xyz"));
    testInvalidElement<Lease6>(json, "valid-lft", -3, false);
    testInvalidElement<Lease6>(json, "user-context", "[ ]", false);
    testInvalidElement<Lease6>(json, "user-context", 1234, false);
    testInvalidElement<Lease6>(json, "user-context", false, false);
    testInvalidElement<Lease6>(json, "user-context", "foo", false);
}

// Verify that the lease states are correctly returned in the textual format.
TEST(Lease6Test, stateToText) {
    EXPECT_EQ("default", Lease6::statesToText(Lease::STATE_DEFAULT));
    EXPECT_EQ("declined", Lease6::statesToText(Lease::STATE_DECLINED));
    EXPECT_EQ("expired-reclaimed", Lease6::statesToText(Lease::STATE_EXPIRED_RECLAIMED));
}


}; // end of anonymous namespace
