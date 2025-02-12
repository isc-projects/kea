// Copyright (C) 2020-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// @file This file contains tests which exercise the load and unload
/// functions in the Radius hooks library. In order to test the load
/// function, one must be able to pass it hook library parameters. The
/// the only way to populate these parameters is by actually loading the
/// library via HooksManager::loadLibraries().

#include <config.h>

#include <dhcpsrv/testutils/host_data_source_utils.h>
#include <radius.h>
#include <radius_backend.h>
#include <attribute_test.h>
#include <gtest/gtest.h>

using namespace std;
using namespace isc;
using namespace isc::asiolink;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::dhcp::test;
using namespace isc::radius;

namespace {

/// @brief Test fixture for testing backend code.
class BackendTest : public radius::test::AttributeTest {
public:
    /// @brief Constructor.
    BackendTest()
        : radius::test::AttributeTest(),
          impl_(RadiusImpl::instance()),
          back_(new RadiusBackend()) {
        impl_.reset();
        ElementPtr config = Element::createMap();
        impl_.init(config);
    }

    /// @brief Destructor.
    virtual ~BackendTest() {
        impl_.reset();
    }

    /// @brief Radius implementation.
    RadiusImpl& impl_;

    /// @brief Radius backend.
    RadiusBackendPtr back_;
};

/// Verify that getAll by id returns empty collection.
TEST_F(BackendTest, getAllId) {
    vector<uint8_t> id = { 0x01, 0x02, 0x03, 0x04 };
    ConstHostCollection hosts;
    EXPECT_NO_THROW(hosts =
                    back_->getAll(Host::IDENT_HWADDR, &id[0], id.size()));
    EXPECT_TRUE(hosts.empty());
    EXPECT_NO_THROW(hosts =
                    back_->getAll(Host::IDENT_DUID, &id[0], id.size()));
    EXPECT_TRUE(hosts.empty());
    EXPECT_NO_THROW(hosts =
                    back_->getAll(Host::IDENT_CIRCUIT_ID, &id[0], id.size()));
    EXPECT_TRUE(hosts.empty());
    EXPECT_NO_THROW(hosts =
                    back_->getAll(Host::IDENT_CLIENT_ID, &id[0], id.size()));
    EXPECT_TRUE(hosts.empty());
    EXPECT_NO_THROW(hosts =
                    back_->getAll(Host::IDENT_FLEX, &id[0], id.size()));
    EXPECT_TRUE(hosts.empty());
    EXPECT_EQ(0, back_->getUnexpected4());
    EXPECT_EQ(0, back_->getUnexpected6());
}

/// Verify that reservation-get-all* returns an empty collection.
TEST_F(BackendTest, getAllAPI) {
    ConstHostCollection hosts;
    EXPECT_NO_THROW(hosts = back_->getAll4(SubnetID(1)));
    EXPECT_TRUE(hosts.empty());
    EXPECT_NO_THROW(hosts = back_->getAll6(SubnetID(1)));
    EXPECT_TRUE(hosts.empty());
    size_t source_index = 2;
    HostPageSize page_size(10);
    EXPECT_NO_THROW(hosts =
                    back_->getPage4(SubnetID(1), source_index, 0, page_size));
    EXPECT_TRUE(hosts.empty());
    EXPECT_NO_THROW(hosts =
                    back_->getPage6(SubnetID(1), source_index, 0, page_size));
    EXPECT_TRUE(hosts.empty());
    EXPECT_NO_THROW(hosts = back_->getPage4(source_index, 0, page_size));
    EXPECT_TRUE(hosts.empty());
    EXPECT_NO_THROW(hosts = back_->getPage6(source_index, 0, page_size));
    EXPECT_TRUE(hosts.empty());
}

/// Verify that getAll4 returns empty collection.
TEST_F(BackendTest, getAll4) {
    IOAddress addr = IOAddress("192.0.2.1");
    ConstHostCollection hosts;
    EXPECT_NO_THROW(hosts = back_->getAll4(addr));
    EXPECT_TRUE(hosts.empty());
    addr = IOAddress("2001:db8::1235");
    EXPECT_NO_THROW(hosts = back_->getAll4(addr));
    EXPECT_TRUE(hosts.empty());
    EXPECT_EQ(0, back_->getUnexpected4());
    EXPECT_EQ(0, back_->getUnexpected6());
}

/// Verify that get4 by subnet and address return null host.
TEST_F(BackendTest, get4SA) {
    IOAddress addr = IOAddress("192.0.2.1");
    ConstHostPtr host;
    EXPECT_NO_THROW(host = back_->get4(0, addr));
    EXPECT_FALSE(host);
    EXPECT_NO_THROW(host = back_->get4(1, addr));
    EXPECT_FALSE(host);
    addr = IOAddress("2001:db8::1235");
    EXPECT_NO_THROW(host = back_->get4(1, addr));
    EXPECT_FALSE(host);
    EXPECT_EQ(0, back_->getUnexpected4());
    EXPECT_EQ(0, back_->getUnexpected6());
}

/// Verify that get6 by prefix and length return null host.
TEST_F(BackendTest, get6PL) {
    IOAddress addr = IOAddress("2001:db8::1235");
    ConstHostPtr host;
    EXPECT_NO_THROW(host = back_->get6(addr, 64));
    EXPECT_FALSE(host);
    EXPECT_NO_THROW(host = back_->get6(addr, 128));
    EXPECT_FALSE(host);
    EXPECT_NO_THROW(host = back_->get6(addr, 250));
    EXPECT_FALSE(host);
    addr = IOAddress("192.0.2.1");
    EXPECT_NO_THROW(host = back_->get6(addr, 24));
    EXPECT_FALSE(host);
    EXPECT_EQ(0, back_->getUnexpected4());
    EXPECT_EQ(0, back_->getUnexpected6());
}

/// Verify that get6 by subnet and address return null host.
TEST_F(BackendTest, get6SA) {
    IOAddress addr = IOAddress("2001:db8::1235");
    ConstHostPtr host;
    EXPECT_NO_THROW(host = back_->get6(0, addr));
    EXPECT_FALSE(host);
    EXPECT_NO_THROW(host = back_->get6(1, addr));
    EXPECT_FALSE(host);
    addr = IOAddress("192.0.2.1");
    EXPECT_NO_THROW(host = back_->get6(1, addr));
    EXPECT_FALSE(host);
    EXPECT_EQ(0, back_->getUnexpected4());
    EXPECT_EQ(0, back_->getUnexpected6());
}

/// Verify that add does nothing.
TEST_F(BackendTest, add) {
    HostPtr host = HostDataSourceUtils::initializeHost4("192.0.2.1",
                                                        Host::IDENT_HWADDR);
    ASSERT_TRUE(host);
    EXPECT_NO_THROW(back_->add(host));
    host = HostDataSourceUtils::initializeHost6("2001:db8::1235",
                                                Host::IDENT_DUID, false);
    ASSERT_TRUE(host);
    EXPECT_NO_THROW(back_->add(host));
    host = HostDataSourceUtils::initializeHost6("2001:db8:1235::",
                                                Host::IDENT_DUID, true);
    ASSERT_TRUE(host);
    EXPECT_NO_THROW(back_->add(host));
    EXPECT_EQ(0, back_->getUnexpected4());
    EXPECT_EQ(0, back_->getUnexpected6());
}

/// Verify that del always return false.
TEST_F(BackendTest, del) {
    IOAddress addr = IOAddress("192.0.2.1");
    bool result = true;
    EXPECT_NO_THROW(result = back_->del(0, addr));
    EXPECT_FALSE(result);
    EXPECT_NO_THROW(result = back_->del(1, addr));
    EXPECT_FALSE(result);
    addr = IOAddress("2001:db8::1235");
    EXPECT_NO_THROW(result = back_->del(0, addr));
    EXPECT_FALSE(result);
    EXPECT_NO_THROW(result = back_->del(1, addr));
    EXPECT_FALSE(result);
    EXPECT_EQ(0, back_->getUnexpected4());
    EXPECT_EQ(0, back_->getUnexpected6());
}

/// Verify that del4 always return false.
TEST_F(BackendTest, del4) {
    vector<uint8_t> id = { 0x01, 0x02, 0x03, 0x04 };
    bool result = true;
    EXPECT_NO_THROW(result =
                    back_->del4(0, Host::IDENT_HWADDR, &id[0], id.size()));
    EXPECT_FALSE(result);
    EXPECT_NO_THROW(result =
                    back_->del4(1, Host::IDENT_HWADDR, &id[0], id.size()));
    EXPECT_FALSE(result);
    EXPECT_NO_THROW(result =
                    back_->del4(0, Host::IDENT_DUID, &id[0], id.size()));
    EXPECT_FALSE(result);
    EXPECT_NO_THROW(result =
                    back_->del4(1, Host::IDENT_DUID, &id[0], id.size()));
    EXPECT_FALSE(result);
    EXPECT_NO_THROW(result =
                    back_->del4(0, Host::IDENT_CIRCUIT_ID, &id[0], id.size()));
    EXPECT_FALSE(result);
    EXPECT_NO_THROW(result =
                    back_->del4(1, Host::IDENT_CIRCUIT_ID, &id[0], id.size()));
    EXPECT_FALSE(result);
    EXPECT_NO_THROW(result =
                    back_->del4(0, Host::IDENT_CLIENT_ID, &id[0], id.size()));
    EXPECT_FALSE(result);
    EXPECT_NO_THROW(result =
                    back_->del4(1, Host::IDENT_CLIENT_ID, &id[0], id.size()));
    EXPECT_FALSE(result);
    EXPECT_NO_THROW(result =
                    back_->del4(0, Host::IDENT_FLEX, &id[0], id.size()));
    EXPECT_FALSE(result);
    EXPECT_NO_THROW(result =
                    back_->del4(1, Host::IDENT_FLEX, &id[0], id.size()));
    EXPECT_FALSE(result);
    EXPECT_EQ(0, back_->getUnexpected4());
    EXPECT_EQ(0, back_->getUnexpected6());
}

/// Verify that del6 always return false.
TEST_F(BackendTest, del6) {
    vector<uint8_t> id = { 0x01, 0x02, 0x03, 0x04 };
    bool result = true;
    EXPECT_NO_THROW(result =
                    back_->del6(0, Host::IDENT_HWADDR, &id[0], id.size()));
    EXPECT_FALSE(result);
    EXPECT_NO_THROW(result =
                    back_->del6(1, Host::IDENT_HWADDR, &id[0], id.size()));
    EXPECT_FALSE(result);
    EXPECT_NO_THROW(result =
                    back_->del6(0, Host::IDENT_DUID, &id[0], id.size()));
    EXPECT_FALSE(result);
    EXPECT_NO_THROW(result =
                    back_->del6(1, Host::IDENT_DUID, &id[0], id.size()));
    EXPECT_FALSE(result);
    EXPECT_NO_THROW(result =
                    back_->del6(0, Host::IDENT_CIRCUIT_ID, &id[0], id.size()));
    EXPECT_FALSE(result);
    EXPECT_NO_THROW(result =
                    back_->del6(1, Host::IDENT_CIRCUIT_ID, &id[0], id.size()));
    EXPECT_FALSE(result);
    EXPECT_NO_THROW(result =
                    back_->del6(0, Host::IDENT_CLIENT_ID, &id[0], id.size()));
    EXPECT_FALSE(result);
    EXPECT_NO_THROW(result =
                    back_->del6(1, Host::IDENT_CLIENT_ID, &id[0], id.size()));
    EXPECT_FALSE(result);
    EXPECT_NO_THROW(result =
                    back_->del6(0, Host::IDENT_FLEX, &id[0], id.size()));
    EXPECT_FALSE(result);
    EXPECT_NO_THROW(result =
                    back_->del6(1, Host::IDENT_FLEX, &id[0], id.size()));
    EXPECT_FALSE(result);
    EXPECT_EQ(0, back_->getUnexpected4());
    EXPECT_EQ(0, back_->getUnexpected6());
}

/// Verify the backend type.
TEST_F(BackendTest, type) {
    EXPECT_EQ("radius", back_->getType());
}

/// Verify get4 by subnet and id with a different type than the radius one.
/// There are 30 combinations so check only 3.
TEST_F(BackendTest, get4SIdDifferent) {
    vector<uint8_t> id = { 0x01, 0x02, 0x03, 0x04 };
    ConstHostPtr host;
    impl_.id_type4_ = Host::IDENT_HWADDR;
    EXPECT_NO_THROW(host =
                    back_->get4(0, Host::IDENT_FLEX, &id[0], id.size()));
    EXPECT_FALSE(host);
    EXPECT_NO_THROW(host =
                    back_->get4(1, Host::IDENT_FLEX, &id[0], id.size()));
    EXPECT_FALSE(host);
    EXPECT_NO_THROW(host =
                    back_->get4(1, Host::IDENT_DUID, &id[0], id.size()));
    EXPECT_FALSE(host);
    impl_.id_type4_ = Host::IDENT_FLEX;
    EXPECT_NO_THROW(host =
                    back_->get4(1, Host::IDENT_HWADDR, &id[0], id.size()));
    EXPECT_FALSE(host);
    EXPECT_EQ(0, back_->getUnexpected4());
    EXPECT_EQ(0, back_->getUnexpected6());
}

/// Verify get6 by subnet and id with a different type than the radius one.
/// There are 30 combinations so check only 3.
TEST_F(BackendTest, get6SIdDifferent) {
    vector<uint8_t> id = { 0x01, 0x02, 0x03, 0x04 };
    ConstHostPtr host;
    impl_.id_type6_ = Host::IDENT_HWADDR;
    EXPECT_NO_THROW(host =
                    back_->get6(0, Host::IDENT_FLEX, &id[0], id.size()));
    EXPECT_FALSE(host);
    EXPECT_NO_THROW(host =
                    back_->get6(1, Host::IDENT_FLEX, &id[0], id.size()));
    EXPECT_FALSE(host);
    EXPECT_NO_THROW(host =
                    back_->get6(1, Host::IDENT_DUID, &id[0], id.size()));
    EXPECT_FALSE(host);
    impl_.id_type6_ = Host::IDENT_FLEX;
    EXPECT_NO_THROW(host =
                    back_->get6(1, Host::IDENT_HWADDR, &id[0], id.size()));
    EXPECT_FALSE(host);
    EXPECT_EQ(0, back_->getUnexpected4());
    EXPECT_EQ(0, back_->getUnexpected6());
}

/// Verify get4 by subnet and id called from the hook.
TEST_F(BackendTest, get4SIdHook) {
    InHook in_hook;
    EXPECT_TRUE(InHook::check());

    vector<uint8_t> id = { 0x01, 0x02, 0x03, 0x04 };
    ConstHostPtr host;
    impl_.id_type4_ = Host::IDENT_HWADDR;
    EXPECT_NO_THROW(host =
                    back_->get4(1, Host::IDENT_HWADDR, &id[0], id.size()));
    EXPECT_FALSE(host);
    impl_.id_type4_ = Host::IDENT_DUID;
    EXPECT_NO_THROW(host =
                    back_->get4(1, Host::IDENT_DUID, &id[0], id.size()));
    EXPECT_FALSE(host);
    EXPECT_EQ(0, back_->getUnexpected4());
    EXPECT_EQ(0, back_->getUnexpected6());
}

/// Verify get6 by subnet and id called from the hook.
TEST_F(BackendTest, get6SIdHook) {
    InHook in_hook;
    EXPECT_TRUE(InHook::check());

    vector<uint8_t> id = { 0x01, 0x02, 0x03, 0x04 };
    ConstHostPtr host;
    impl_.id_type6_ = Host::IDENT_HWADDR;
    EXPECT_NO_THROW(host =
                    back_->get6(1, Host::IDENT_HWADDR, &id[0], id.size()));
    EXPECT_FALSE(host);
    impl_.id_type6_ = Host::IDENT_DUID;
    EXPECT_NO_THROW(host =
                    back_->get6(1, Host::IDENT_DUID, &id[0], id.size()));
    EXPECT_FALSE(host);
    EXPECT_EQ(0, back_->getUnexpected4());
    EXPECT_EQ(0, back_->getUnexpected6());
}

/// Verify get4 by subnet and id called in an unexpected way, i.e.,
/// same identifier type and outside the hook.
TEST_F(BackendTest, get4SIdUnexpected) {
    ASSERT_FALSE(InHook::check());
    vector<uint8_t> id = { 0x01, 0x02, 0x03, 0x04 };
    ConstHostPtr host;
    impl_.id_type4_ = Host::IDENT_HWADDR;
    EXPECT_NO_THROW(host =
                    back_->get4(1, Host::IDENT_HWADDR, &id[0], id.size()));
    EXPECT_FALSE(host);
    impl_.id_type4_ = Host::IDENT_DUID;
    EXPECT_NO_THROW(host =
                    back_->get4(1, Host::IDENT_DUID, &id[0], id.size()));
    EXPECT_FALSE(host);
    EXPECT_EQ(2, back_->getUnexpected4());
    EXPECT_EQ(0, back_->getUnexpected6());
}

/// Verify get6 by subnet and id called in an unexpected way, i.e.,
/// same identifier type and outside the hook.
TEST_F(BackendTest, get6SIdUnexpected) {
    ASSERT_FALSE(InHook::check());
    vector<uint8_t> id = { 0x01, 0x02, 0x03, 0x04 };
    ConstHostPtr host;
    impl_.id_type6_ = Host::IDENT_HWADDR;
    EXPECT_NO_THROW(host =
                    back_->get6(1, Host::IDENT_HWADDR, &id[0], id.size()));
    EXPECT_FALSE(host);
    impl_.id_type6_ = Host::IDENT_DUID;
    EXPECT_NO_THROW(host =
                    back_->get6(1, Host::IDENT_DUID, &id[0], id.size()));
    EXPECT_FALSE(host);
    EXPECT_EQ(0, back_->getUnexpected4());
    EXPECT_EQ(2, back_->getUnexpected6());
}

/// Verify that the Radius backend does not support using non-unique
/// IP addresses between multiple reservations.
TEST_F(BackendTest, disallowDuplicateIP) {
    // The backend does not support switching to the mode in which multiple
    // reservations for the same address can be created.
    EXPECT_FALSE(back_->setIPReservationsUnique(false));

    // The default mode still can be used.
    EXPECT_TRUE(back_->setIPReservationsUnique(true));
}

// Verify that an attempt to get all hosts for a given IPv4 address and subnet
// returns empty set.
TEST_F(BackendTest, getAll4BySubnetAddress) {
    EXPECT_TRUE(back_->getAll4(SubnetID(1), IOAddress("192.0.2.0")).empty());
}

// Verify that an attempt to get all hosts for a given IPv6 address and subnet
// returns empty set.
TEST_F(BackendTest, getAll6BySubnetAddress) {
    EXPECT_TRUE(back_->getAll6(SubnetID(1), IOAddress("2001:db8:1::1")).empty());
}

} // end of anonymous namespace
