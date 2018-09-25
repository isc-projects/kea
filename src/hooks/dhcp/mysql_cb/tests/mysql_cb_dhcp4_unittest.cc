// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <dhcp/dhcp6.h>
#include <dhcpsrv/pool.h>
#include <dhcpsrv/subnet.h>
#include <mysql_cb_dhcp4.h>
#include <mysql/testutils/mysql_schema.h>
#include <boost/shared_ptr.hpp>
#include <gtest/gtest.h>
#include <map>

using namespace isc::asiolink;
using namespace isc::db;
using namespace isc::db::test;
using namespace isc::data;
using namespace isc::dhcp;

namespace {

/// @brief Test fixture class for @c MySqlConfigBackendDHCPv4.
class MySqlConfigBackendDHCPv4Test : public ::testing::Test {
public:

    /// @brief Constructor.
    MySqlConfigBackendDHCPv4Test()
        : test_subnets_(), timestamps_() {
        // Recreate database schema.
        destroyMySQLSchema();
        createMySQLSchema();

        try {
            // Create MySQL connection and use it to start the backend.
            DatabaseConnection::ParameterMap params =
                DatabaseConnection::parse(validMySQLConnectionString());
            cbptr_.reset(new MySqlConfigBackendDHCPv4(params));

        } catch (...) {
            std::cerr << "*** ERROR: unable to open database. The test\n"
                         "*** environment is broken and must be fixed before\n"
                         "*** the MySQL tests will run correctly.\n"
                         "*** The reason for the problem is described in the\n"
                         "*** accompanying exception output.\n";
            throw;
        }

        // Create test data.
        initTestSubnets();
        initTimestamps();
    }

    /// @brief Destructor.
    virtual ~MySqlConfigBackendDHCPv4Test() {
        cbptr_.reset();
        destroyMySQLSchema();
    }

    /// @brief Creates several subnets used in tests.
    void initTestSubnets() {
        // First subnet includes all parameters.
        std::string interface_id_text = "whale";
        OptionBuffer interface_id(interface_id_text.begin(), interface_id_text.end());
        ElementPtr user_context = Element::createMap();
        user_context->set("foo", Element::create("bar"));

        Subnet4Ptr subnet(new Subnet4(IOAddress("192.0.2.0"), 24, 30, 40, 60, 1024));
        subnet->get4o6().setIface4o6("eth0");
        subnet->get4o6().setInterfaceId(OptionPtr(new Option(Option::V6, D6O_INTERFACE_ID,
                                                         interface_id)));
        subnet->get4o6().setSubnet4o6(IOAddress("2001:db8:1::"), 64);
        subnet->setFilename("/tmp/filename");
        subnet->allowClientClass("home");
        subnet->setIface("eth1");
        subnet->setMatchClientId(false);
        subnet->setSiaddr(IOAddress("10.1.2.3"));
        subnet->setT2(323212);
        subnet->addRelayAddress(IOAddress("10.2.3.4"));
        subnet->addRelayAddress(IOAddress("10.5.6.7"));
        subnet->setT1(1234);
        subnet->requireClientClass("required-class1");
        subnet->requireClientClass("required-class2");
        subnet->setHostReservationMode(Subnet4::HR_DISABLED);
        subnet->setSname("server-hostname");
        subnet->setContext(user_context);
        // shared-network?
        subnet->setValid(555555);

        Pool4Ptr pool1(new Pool4(IOAddress("192.0.2.10"), IOAddress("192.0.2.20")));
        subnet->addPool(pool1);

        Pool4Ptr pool2(new Pool4(IOAddress("192.0.2.50"), IOAddress("192.0.2.60")));
        subnet->addPool(pool2);

        test_subnets_.push_back(subnet);

        // Other subnets include mostly null values except for mandatory parameters.
        subnet.reset(new Subnet4(IOAddress("10.0.0.0"), 8, 20, 30, 40, 1024));

        pool1.reset(new Pool4(IOAddress("10.0.0.10"), IOAddress("10.0.0.20")));
        subnet->addPool(pool1);

        pool2.reset(new Pool4(IOAddress("10.0.0.50"), IOAddress("10.0.0.60")));
        subnet->addPool(pool2);

        test_subnets_.push_back(subnet);

        subnet.reset(new Subnet4(IOAddress("192.0.3.0"), 24, 20, 30, 40, 2048));
        test_subnets_.push_back(subnet);

        subnet.reset(new Subnet4(IOAddress("192.0.4.0"), 24, 30, 40, 60, 4096));
        test_subnets_.push_back(subnet);
    }

    /// @brief Initialize posix time values used in tests.
    void initTimestamps() {
        // Current time minus 1 hour to make sure it is in the past.
        timestamps_["today"] = boost::posix_time::second_clock::universal_time()
            - boost::posix_time::hours(1);
        // Yesterday.
        timestamps_["yesterday"] = timestamps_["today"] - boost::posix_time::hours(24);
        // Tomorrow.
        timestamps_["tomorrow"] = timestamps_["today"] + boost::posix_time::hours(24);
    }

    /// @brief Holds pointers to subnets used in tests.
    std::vector<Subnet4Ptr> test_subnets_;

    /// @brief Holds timestamp values used in tests.
    std::map<std::string, boost::posix_time::ptime> timestamps_;

    /// @brief Holds pointer to the backend.
    boost::shared_ptr<ConfigBackendDHCPv4> cbptr_;
};

// Test that subnet can be inserted, fetched, updated and then fetched again.
TEST_F(MySqlConfigBackendDHCPv4Test, getSubnet4) {
    // Insert new subnet.
    Subnet4Ptr subnet = test_subnets_[0];
    cbptr_->createUpdateSubnet4(ServerSelector::UNASSIGNED(), subnet);

    // Fetch this subnet by subnet identifier.
    Subnet4Ptr returned_subnet = cbptr_->getSubnet4(ServerSelector::UNASSIGNED(),
                                                    test_subnets_[0]->getID());
    ASSERT_TRUE(returned_subnet);

    // The easiest way to verify whether the returned subnet matches the inserted
    // subnet is to convert both to text.
    EXPECT_EQ(subnet->toElement()->str(), returned_subnet->toElement()->str());

    // Update the subnet in the database (both use the same ID).
    Subnet4Ptr subnet2 = test_subnets_[1];
    cbptr_->createUpdateSubnet4(ServerSelector::UNASSIGNED(), subnet2);

    // Fetch updated subnet and see if it matches.
    returned_subnet = cbptr_->getSubnet4(ServerSelector::UNASSIGNED(),
                                         SubnetID(1024));
    EXPECT_EQ(subnet2->toElement()->str(), returned_subnet->toElement()->str());
}

// Test that subnet can be fetched by prefix.
TEST_F(MySqlConfigBackendDHCPv4Test, getSubnet4ByPrefix) {
    // Insert subnet to the database.
    Subnet4Ptr subnet = test_subnets_[0];
    cbptr_->createUpdateSubnet4(ServerSelector::UNASSIGNED(), subnet);

    // Fetch the subnet by prefix.
    Subnet4Ptr returned_subnet = cbptr_->getSubnet4(ServerSelector::UNASSIGNED(),
                                                    "192.0.2.0/24");
    ASSERT_TRUE(returned_subnet);

    // Verify subnet contents.
    EXPECT_EQ(subnet->toElement()->str(), returned_subnet->toElement()->str());
}

// Test that all subnets can be fetched.
TEST_F(MySqlConfigBackendDHCPv4Test, getAllSubnets4) {
    // Insert test subnets into the database. Note that the second subnet will
    // overwrite the first subnet as they use the same ID.
    for (auto subnet : test_subnets_) {
        cbptr_->createUpdateSubnet4(ServerSelector::UNASSIGNED(), subnet);
    }

    // Fetch all subnets.
    Subnet4Collection subnets = cbptr_->getAllSubnets4(ServerSelector::UNASSIGNED());
    ASSERT_EQ(test_subnets_.size() - 1, subnets.size());

    // See if the subnets are returned ok.
    for (auto i = 0; i < subnets.size(); ++i) {
        EXPECT_EQ(test_subnets_[i + 1]->toElement()->str(),
                  subnets[i]->toElement()->str());
    }
}

// Test that subnets modified after given time can be fetched.
TEST_F(MySqlConfigBackendDHCPv4Test, getModifiedSubnets4) {
    // Explicitly set timestamps of subnets. First subnet has a timestamp
    // pointing to the future. Second subnet has timestamp pointing to the
    // past (yesterday). Third subnet has a timestamp pointing to the
    // past (an hour ago).
    test_subnets_[1]->setModificationTime(timestamps_["tomorrow"]);
    test_subnets_[2]->setModificationTime(timestamps_["yesterday"]);
    test_subnets_[3]->setModificationTime(timestamps_["today"]);

    // Insert subnets into the database.
    for (int i = 1; i < test_subnets_.size(); ++i) {
        cbptr_->createUpdateSubnet4(ServerSelector::UNASSIGNED(),
                                    test_subnets_[i]);
    }

    // Fetch subnets with timestamp later than today. Only one subnet
    // should be returned.
    Subnet4Collection
        subnets = cbptr_->getModifiedSubnets4(ServerSelector::UNASSIGNED(),
                                              timestamps_["today"]);
    ASSERT_EQ(1, subnets.size());

    // Fetch subnets with timestamp later than yesterday. We should get
    // two subnets.
    subnets = cbptr_->getModifiedSubnets4(ServerSelector::UNASSIGNED(),
                                          timestamps_["yesterday"]);
    ASSERT_EQ(2, subnets.size());

    // Fetch subnets with timestamp later than tomorrow. Nothing should
    // be returned.
    subnets = cbptr_->getModifiedSubnets4(ServerSelector::UNASSIGNED(),
                                          timestamps_["tomorrow"]);
    ASSERT_TRUE(subnets.empty());
}

}
