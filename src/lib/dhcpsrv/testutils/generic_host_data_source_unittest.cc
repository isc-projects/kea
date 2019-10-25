// Copyright (C) 2015-2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <database/database_connection.h>
#include <database/db_exceptions.h>
#include <dhcp/dhcp6.h>
#include <dhcp/libdhcp++.h>
#include <dhcp/option4_addrlst.h>
#include <dhcp/option6_addrlst.h>
#include <dhcp/option_int.h>
#include <dhcp/option_string.h>
#include <dhcp/option_vendor.h>
#include <dhcpsrv/host_mgr.h>
#include <dhcpsrv/host_data_source_factory.h>
#include <dhcpsrv/testutils/generic_host_data_source_unittest.h>
#include <dhcpsrv/testutils/host_data_source_utils.h>
#include <database/testutils/schema.h>
#include <util/buffer.h>

#include <boost/foreach.hpp>
#include <gtest/gtest.h>

#include <chrono>
#include <cstring>
#include <list>
#include <sstream>
#include <string>
#include <typeinfo>

using namespace std;
using namespace isc::asiolink;
using namespace isc::db;
using namespace isc::db::test;
using namespace isc::util;
using namespace isc::data;

namespace isc {
namespace dhcp {
namespace test {

GenericHostDataSourceTest::GenericHostDataSourceTest()
    : GenericBackendTest(), hdsptr_() {
}

GenericHostDataSourceTest::~GenericHostDataSourceTest() {
    hdsptr_.reset();
}

bool
GenericHostDataSourceTest::compareHostsForSort4(const ConstHostPtr& host1,
                                                const ConstHostPtr& host2) {
    if (host1->getIPv4SubnetID() < host2->getIPv4SubnetID()) {
        return true;
    }
    return false;
}

bool
GenericHostDataSourceTest::compareHostsForSort6(const ConstHostPtr& host1,
                                                const ConstHostPtr& host2) {
    if (host1->getIPv6SubnetID() < host2->getIPv6SubnetID()) {
        return true;
    }
    return false;
}

bool
GenericHostDataSourceTest::compareHostsIdentifier(const ConstHostPtr& host1,
                                                  const ConstHostPtr& host2) {
    auto host1_i = host1->getIdentifier();
    auto host2_i = host2->getIdentifier();
    auto count1 = host1_i.size();
    auto count2 = host2_i.size();
    if (count1 > count2) {
        count1 = count2;
    }
    for (uint8_t i = 0; i < count1; ++i) {
        if (host1_i[i] != host2_i[i]) {
            return (host1_i[i] < host2_i[i]);
        }
    }
    return false;
}

DuidPtr
GenericHostDataSourceTest::HWAddrToDuid(const HWAddrPtr& hwaddr) {
    if (!hwaddr) {
        return (DuidPtr());
    }

    return (DuidPtr(new DUID(hwaddr->hwaddr_)));
}

HWAddrPtr
GenericHostDataSourceTest::DuidToHWAddr(const DuidPtr& duid) {
    if (!duid) {
        return (HWAddrPtr());
    }

    return (HWAddrPtr(new HWAddr(duid->getDuid(), HTYPE_ETHER)));
}

void
GenericHostDataSourceTest::addTestOptions(const HostPtr& host,
                                          const bool formatted,
                                          const AddedOptions& added_options,
                                          ConstElementPtr user_context) const {

    OptionDefSpaceContainer defs;

    if ((added_options == DHCP4_ONLY) || (added_options == DHCP4_AND_DHCP6)) {
        // Add DHCPv4 options.
        CfgOptionPtr opts = host->getCfgOption4();
        OptionDescriptor desc =
            createOption<OptionString>(Option::V4, DHO_BOOT_FILE_NAME,
                                       true, formatted, "my-boot-file");
        desc.setContext(user_context);
        opts->add(desc, DHCP4_OPTION_SPACE);
        opts->add(createOption<OptionUint8>(Option::V4, DHO_DEFAULT_IP_TTL,
                                            false, formatted, 64),
                  DHCP4_OPTION_SPACE);
        opts->add(createOption<OptionUint32>(Option::V4, 1, false, formatted, 312131),
                  "vendor-encapsulated-options");
        opts->add(createAddressOption<Option4AddrLst>(254, false, formatted,
                                                      "192.0.2.3"), DHCP4_OPTION_SPACE);
        opts->add(createEmptyOption(Option::V4, 1, true), "isc");
        opts->add(createAddressOption<Option4AddrLst>(2, false, formatted, "10.0.0.5",
                                                      "10.0.0.3", "10.0.3.4"), "isc");

        // Add definitions for DHCPv4 non-standard options.
        defs.addItem(OptionDefinitionPtr(new OptionDefinition(
                         "vendor-encapsulated-1", 1, "uint32")),
                     "vendor-encapsulated-options");
        defs.addItem(OptionDefinitionPtr(new OptionDefinition(
                         "option-254", 254, "ipv4-address", true)),
                     DHCP4_OPTION_SPACE);
        defs.addItem(OptionDefinitionPtr(new OptionDefinition("isc-1", 1, "empty")), "isc");
        defs.addItem(OptionDefinitionPtr(new OptionDefinition("isc-2", 2, "ipv4-address", true)),
                     "isc");
    }

    if ((added_options == DHCP6_ONLY) || (added_options == DHCP4_AND_DHCP6)) {
        // Add DHCPv6 options.
        CfgOptionPtr opts = host->getCfgOption6();
        OptionDescriptor desc =
            createOption<OptionString>(Option::V6, D6O_BOOTFILE_URL,
                                       true, formatted, "my-boot-file");
        desc.setContext(user_context);
        opts->add(desc, DHCP6_OPTION_SPACE);
        opts->add(createOption<OptionUint32>(Option::V6, D6O_INFORMATION_REFRESH_TIME,
                                             false, formatted, 3600),
                  DHCP6_OPTION_SPACE);
        opts->add(createVendorOption(Option::V6, false, formatted, 2495),
                  DHCP6_OPTION_SPACE);
        opts->add(createAddressOption<Option6AddrLst>(1024, false, formatted,
                                                      "2001:db8:1::1"),
                  DHCP6_OPTION_SPACE);
        opts->add(createEmptyOption(Option::V6, 1, true), "isc2");
        opts->add(createAddressOption<Option6AddrLst>(2, false, formatted, "3000::1",
                                                      "3000::2", "3000::3"), "isc2");

        // Add definitions for DHCPv6 non-standard options.
        defs.addItem(OptionDefinitionPtr(new OptionDefinition(
                         "option-1024", 1024, "ipv6-address", true)),
                     DHCP6_OPTION_SPACE);
        defs.addItem(OptionDefinitionPtr(new OptionDefinition("option-1", 1, "empty")), "isc2");
        defs.addItem(OptionDefinitionPtr(new OptionDefinition("option-2", 2, "ipv6-address", true)),
                     "isc2");
    }

    // Register created "runtime" option definitions. They will be used by a
    // host data source to convert option data into the appropriate option
    // classes when the options are retrieved.
    LibDHCP::setRuntimeOptionDefs(defs);
}

void
GenericHostDataSourceTest::testReadOnlyDatabase(const char* valid_db_type) {
    ASSERT_TRUE(hdsptr_);

    // The database is initially opened in "read-write" mode. We can
    // insert some data to the database.
    HostPtr host = HostDataSourceUtils::initializeHost6("2001:db8::1", Host::IDENT_DUID, false);
    ASSERT_TRUE(host);
    ASSERT_NO_THROW(hdsptr_->add(host));

    // Subnet id will be used in queries to the database.
    SubnetID subnet_id = host->getIPv6SubnetID();

    // Make sure that the host has been inserted and that the data can be
    // retrieved.
    ConstHostPtr host_by_id =
        hdsptr_->get6(subnet_id, host->getIdentifierType(),
                      &host->getIdentifier()[0], host->getIdentifier().size());
    ASSERT_TRUE(host_by_id);
    ASSERT_NO_FATAL_FAILURE(HostDataSourceUtils::compareHosts(host, host_by_id));

    // Close the database connection and reopen in "read-only" mode as
    // specified by the "VALID_READONLY_DB" parameter.
    HostMgr::create();
    HostMgr::addBackend(connectionString(
        valid_db_type, VALID_NAME, VALID_HOST, VALID_READONLY_USER,
        VALID_PASSWORD, VALID_READONLY_DB));

    hdsptr_ = HostMgr::instance().getHostDataSource();

    // Check that an attempt to insert new host would result in
    // exception.
    HostPtr host2 = HostDataSourceUtils::initializeHost6("2001:db8::2", Host::IDENT_DUID, false);
    ASSERT_TRUE(host2);
    ASSERT_THROW(hdsptr_->add(host2), ReadOnlyDb);
    ASSERT_THROW(hdsptr_->commit(), ReadOnlyDb);
    ASSERT_THROW(hdsptr_->rollback(), ReadOnlyDb);

    // Reading from the database should still be possible, though.
    host_by_id =
        hdsptr_->get6(subnet_id, host->getIdentifierType(),
                      &host->getIdentifier()[0], host->getIdentifier().size());
    ASSERT_TRUE(host_by_id);
    ASSERT_NO_FATAL_FAILURE(HostDataSourceUtils::compareHosts(host, host_by_id));
}

void
GenericHostDataSourceTest::testBasic4(const Host::IdentifierType& id) {
    // Make sure we have the pointer to the host data source.
    ASSERT_TRUE(hdsptr_);

    // Create a host reservation.
    HostPtr host = HostDataSourceUtils::initializeHost4("192.0.2.1", id);
    ASSERT_TRUE(host);  // Make sure the host is generate properly.
    SubnetID subnet = host->getIPv4SubnetID();

    // Try to add it to the host data source.
    ASSERT_NO_THROW(hdsptr_->add(host));

    // This should not return anything
    ConstHostPtr from_hds = hdsptr_->get4(subnet, IOAddress("10.10.10.10"));
    ASSERT_FALSE(from_hds);

    // This time it should return a host
    from_hds = hdsptr_->get4(subnet, IOAddress("192.0.2.1"));
    ASSERT_TRUE(from_hds);

    // Finally, let's check if what we got makes any sense.
    HostDataSourceUtils::compareHosts(host, from_hds);
}

void
GenericHostDataSourceTest::testGlobalSubnetId4() {
    std::vector<uint8_t> ident;

    ident = HostDataSourceUtils::generateIdentifier();
    SubnetID subnet_id4 = SUBNET_ID_GLOBAL;
    HostPtr host(new Host(&ident[0], ident.size(), Host::IDENT_DUID,
                          subnet_id4, SUBNET_ID_UNUSED, IOAddress("0.0.0.0")));

    ASSERT_NO_THROW(addTestOptions(host, true, DHCP4_ONLY));
    (hdsptr_->add(host));
    //ASSERT_NO_THROW(hdsptr_->add(host));

    // get4(subnet_id, identifier_type, identifier, identifier_size)
    ConstHostPtr host_by_id = hdsptr_->get4(subnet_id4,
                                            host->getIdentifierType(),
                                            &host->getIdentifier()[0],
                                            host->getIdentifier().size());

    ASSERT_NO_FATAL_FAILURE(HostDataSourceUtils::compareHosts(host, host_by_id));

    // Now try to delete it: del4(subnet4-id, identifier-type, identifier)
    EXPECT_TRUE(hdsptr_->del4(subnet_id4, Host::IDENT_DUID, &ident[0],
                              ident.size()));

    host_by_id = hdsptr_->get4(subnet_id4, host->getIdentifierType(),
                               &host->getIdentifier()[0],
                               host->getIdentifier().size());

    EXPECT_FALSE(host_by_id);
}

void GenericHostDataSourceTest::testGlobalSubnetId6() {
    std::vector<uint8_t> ident;

    ident = HostDataSourceUtils::generateIdentifier();
    SubnetID subnet_id6 = SUBNET_ID_GLOBAL;
    HostPtr host(new Host(&ident[0], ident.size(), Host::IDENT_DUID,
                          SUBNET_ID_UNUSED, subnet_id6, IOAddress("0.0.0.0")));

    ASSERT_NO_THROW(addTestOptions(host, true, DHCP6_ONLY));
    ASSERT_NO_THROW(hdsptr_->add(host));

    // get6(subnet_id, identifier_type, identifier, identifier_size)
    ConstHostPtr host_by_id = hdsptr_->get6(subnet_id6,
                                            host->getIdentifierType(),
                                            &host->getIdentifier()[0],
                                            host->getIdentifier().size());

    ASSERT_NO_FATAL_FAILURE(HostDataSourceUtils::compareHosts(host, host_by_id));

    // Now try to delete it: del6(subnet6-id, identifier-type, identifier)
    EXPECT_TRUE(hdsptr_->del6(subnet_id6, Host::IDENT_DUID, &ident[0],
                              ident.size()));

    host_by_id = hdsptr_->get4(subnet_id6, host->getIdentifierType(),
                               &host->getIdentifier()[0],
                               host->getIdentifier().size());

    EXPECT_FALSE(host_by_id);
}


void
GenericHostDataSourceTest::testMaxSubnetId4() {
    std::vector<uint8_t> ident;

    ident = HostDataSourceUtils::generateIdentifier();
    SubnetID subnet_id4 = SUBNET_ID_MAX;
    HostPtr host(new Host(&ident[0], ident.size(), Host::IDENT_DUID,
                          subnet_id4, SUBNET_ID_UNUSED, IOAddress("0.0.0.0")));

    ASSERT_NO_THROW(addTestOptions(host, true, DHCP4_ONLY));
    ASSERT_NO_THROW(hdsptr_->add(host));

    // get4(subnet_id, identifier_type, identifier, identifier_size)
    ConstHostPtr host_by_id = hdsptr_->get4(subnet_id4,
                                            host->getIdentifierType(),
                                            &host->getIdentifier()[0],
                                            host->getIdentifier().size());

    ASSERT_NO_FATAL_FAILURE(HostDataSourceUtils::compareHosts(host, host_by_id));

    // Now try to delete it: del4(subnet4-id, identifier-type, identifier)
    EXPECT_TRUE(hdsptr_->del4(subnet_id4, Host::IDENT_DUID, &ident[0],
                              ident.size()));

    host_by_id = hdsptr_->get4(subnet_id4, host->getIdentifierType(),
                               &host->getIdentifier()[0],
                               host->getIdentifier().size());

    EXPECT_FALSE(host_by_id);
}

void
GenericHostDataSourceTest::testMaxSubnetId6() {
    std::vector<uint8_t> ident;

    ident = HostDataSourceUtils::generateIdentifier();
    SubnetID subnet_id6 = SUBNET_ID_MAX;
    HostPtr host(new Host(&ident[0], ident.size(), Host::IDENT_DUID,
                          SUBNET_ID_UNUSED, subnet_id6, IOAddress("0.0.0.0")));

    ASSERT_NO_THROW(addTestOptions(host, true, DHCP6_ONLY));
    ASSERT_NO_THROW(hdsptr_->add(host));

    // get6(subnet_id, identifier_type, identifier, identifier_size)
    ConstHostPtr host_by_id = hdsptr_->get6(subnet_id6,
                                            host->getIdentifierType(),
                                            &host->getIdentifier()[0],
                                            host->getIdentifier().size());

    ASSERT_NO_FATAL_FAILURE(HostDataSourceUtils::compareHosts(host, host_by_id));

    // Now try to delete it: del6(subnet6-id, identifier-type, identifier)
    EXPECT_TRUE(hdsptr_->del6(subnet_id6, Host::IDENT_DUID, &ident[0],
                              ident.size()));

    host_by_id = hdsptr_->get4(subnet_id6, host->getIdentifierType(),
                               &host->getIdentifier()[0],
                               host->getIdentifier().size());

    EXPECT_FALSE(host_by_id);
}

void
GenericHostDataSourceTest::testGetAll4() {
    // Make sure we have a pointer to the host data source.
    ASSERT_TRUE(hdsptr_);

    // Let's create a couple of hosts...
    const Host::IdentifierType& id = Host::IDENT_HWADDR;
    HostPtr host1 = HostDataSourceUtils::initializeHost4("192.0.2.1", id);
    HostPtr host2 = HostDataSourceUtils::initializeHost4("192.0.2.2", id);
    HostPtr host3 = HostDataSourceUtils::initializeHost4("192.0.2.3", id);
    HostPtr host4 = HostDataSourceUtils::initializeHost4("192.0.2.4", id);

    // Set them in the same subnets.
    SubnetID subnet4 = host1->getIPv4SubnetID();
    host2->setIPv4SubnetID(subnet4);
    host3->setIPv4SubnetID(subnet4);
    host4->setIPv4SubnetID(subnet4);
    SubnetID subnet6 = host1->getIPv6SubnetID();
    host2->setIPv6SubnetID(subnet6);
    host3->setIPv6SubnetID(subnet6);
    host4->setIPv6SubnetID(subnet6);

    // ... and add them to the data source.
    ASSERT_NO_THROW(hdsptr_->add(host1));
    ASSERT_NO_THROW(hdsptr_->add(host2));
    ASSERT_NO_THROW(hdsptr_->add(host3));
    ASSERT_NO_THROW(hdsptr_->add(host4));

    // And then try to retrieve them back.
    ConstHostCollection from_hds = hdsptr_->getAll4(subnet4);

    // Make sure we got something back.
    ASSERT_EQ(4, from_hds.size());

    // Then let's check that what we got seems correct.
    // There is no ORDER BY in Cassandra so skip it.
    if (hdsptr_->getType() != "cql") {
        HostDataSourceUtils::compareHosts(host1, from_hds[0]);
        HostDataSourceUtils::compareHosts(host2, from_hds[1]);
        HostDataSourceUtils::compareHosts(host3, from_hds[2]);
        HostDataSourceUtils::compareHosts(host4, from_hds[3]);
    }
}

void
GenericHostDataSourceTest::testGetAll6() {
    // Make sure we have a pointer to the host data source.
    ASSERT_TRUE(hdsptr_);

    // Let's create a couple of hosts...
    const Host::IdentifierType& id = Host::IDENT_DUID;
    HostPtr host1 = HostDataSourceUtils::initializeHost6("2001:db8::1", id, false);
    HostPtr host2 = HostDataSourceUtils::initializeHost6("2001:db8::2", id, false);
    HostPtr host3 = HostDataSourceUtils::initializeHost6("2001:db8::3", id, false);
    HostPtr host4 = HostDataSourceUtils::initializeHost6("2001:db8::4", id, false);

    // Set them in the same subnets.
    SubnetID subnet4 = host1->getIPv4SubnetID();
    host2->setIPv4SubnetID(subnet4);
    host3->setIPv4SubnetID(subnet4);
    host4->setIPv4SubnetID(subnet4);
    SubnetID subnet6 = host1->getIPv6SubnetID();
    host2->setIPv6SubnetID(subnet6);
    host3->setIPv6SubnetID(subnet6);
    host4->setIPv6SubnetID(subnet6);

    // ... and add them to the data source.
    ASSERT_NO_THROW(hdsptr_->add(host1));
    ASSERT_NO_THROW(hdsptr_->add(host2));
    ASSERT_NO_THROW(hdsptr_->add(host3));
    ASSERT_NO_THROW(hdsptr_->add(host4));

    // And then try to retrieve them back.
    ConstHostCollection from_hds = hdsptr_->getAll6(subnet6);

    // Make sure we got something back.
    ASSERT_EQ(4, from_hds.size());

    // Then let's check that what we got seems correct.
    // There is no ORDER BY in Cassandra so skip it.
    if (hdsptr_->getType() != "cql") {
        HostDataSourceUtils::compareHosts(host1, from_hds[0]);
        HostDataSourceUtils::compareHosts(host2, from_hds[1]);
        HostDataSourceUtils::compareHosts(host3, from_hds[2]);
        HostDataSourceUtils::compareHosts(host4, from_hds[3]);
    }
}

void
GenericHostDataSourceTest::testGetAllbyHostname() {
    // Make sure we have a pointer to the host data source.
    ASSERT_TRUE(hdsptr_);

    // Let's create some hosts...
    Host::IdentifierType id = Host::IDENT_HWADDR;
    HostPtr host1 = HostDataSourceUtils::initializeHost4("192.0.2.1", id);
    host1->setHostname("host");

    id = Host::IDENT_DUID;
    HostPtr host2 = HostDataSourceUtils::initializeHost4("192.0.2.2", id);
    host2->setHostname("Host");

    HostPtr host3 = HostDataSourceUtils::initializeHost6("2001:db8::1", id, false);
    host3->setHostname("hOSt");

    HostPtr host4 = HostDataSourceUtils::initializeHost6("2001:db8::2", id, false);
    host4->setHostname("host.example.com");

    // Now add them all to the host data source.
    ASSERT_NO_THROW(hdsptr_->add(host1));
    ASSERT_NO_THROW(hdsptr_->add(host2));
    ASSERT_NO_THROW(hdsptr_->add(host3));
    ASSERT_NO_THROW(hdsptr_->add(host4));

    // Retrieve unknown name.
    ConstHostCollection from_hds = hdsptr_->getAllbyHostname("foo");
    EXPECT_TRUE(from_hds.empty());

    // Retrieve one reservation.
    from_hds = hdsptr_->getAllbyHostname("host.example.com");
    ASSERT_EQ(1, from_hds.size());
    HostDataSourceUtils::compareHosts(host4, from_hds[0]);

    // Retrieve all reservations with host hostname.
    from_hds = hdsptr_->getAllbyHostname("host");
    EXPECT_EQ(3, from_hds.size());
    bool got1 = false;
    bool got2 = false;
    bool got3 = false;
    for (auto host : from_hds) {
        if (host->getIdentifierType() == Host::IDENT_HWADDR) {
            EXPECT_FALSE(got1);
            got1 = true;
            HostDataSourceUtils::compareHosts(host1, host);
        } else if (host->getIPv4Reservation().isV4Zero()) {
            EXPECT_FALSE(got3);
            got3 = true;
            HostDataSourceUtils::compareHosts(host3, host);
        } else {
            EXPECT_FALSE(got2);
            got2 = true;
            HostDataSourceUtils::compareHosts(host2, host);
        }
    }
    EXPECT_TRUE(got1);
    EXPECT_TRUE(got2);
    EXPECT_TRUE(got3);
}

void
GenericHostDataSourceTest::testGetAllbyHostnameSubnet4() {
    // Make sure we have a pointer to the host data source.
    ASSERT_TRUE(hdsptr_);

    // Let's create some hosts...
    Host::IdentifierType id = Host::IDENT_HWADDR;
    HostPtr host1 = HostDataSourceUtils::initializeHost4("192.0.2.1", id);
    host1->setHostname("host");

    id = Host::IDENT_DUID;
    HostPtr host2 = HostDataSourceUtils::initializeHost4("192.0.2.2", id);
    host2->setHostname("Host");
    CfgOptionPtr opts = host2->getCfgOption4();
    OptionDescriptor desc =
        createOption<OptionString>(Option::V4, DHO_BOOT_FILE_NAME,
                                   true, false, "my-boot-file");
    opts->add(desc, DHCP4_OPTION_SPACE);

    HostPtr host3 = HostDataSourceUtils::initializeHost4("192.0.2.3", id);
    host3->setHostname("hOSt");

    HostPtr host4 = HostDataSourceUtils::initializeHost4("192.0.2.4", id);
    host4->setHostname("host.example.com");

    HostPtr host5 = HostDataSourceUtils::initializeHost4("192.0.2.5", id);

    // Set them in the same subnet at the exception of host5.
    SubnetID subnet4 = host1->getIPv4SubnetID();
    host2->setIPv4SubnetID(subnet4);
    host3->setIPv4SubnetID(subnet4);
    host4->setIPv4SubnetID(subnet4);
    SubnetID subnet6 = host1->getIPv6SubnetID();
    host2->setIPv6SubnetID(subnet6);
    host3->setIPv6SubnetID(subnet6);
    host4->setIPv6SubnetID(subnet6);

    // Now add them all to the host data source.
    ASSERT_NO_THROW(hdsptr_->add(host1));
    ASSERT_NO_THROW(hdsptr_->add(host2));
    ASSERT_NO_THROW(hdsptr_->add(host3));
    ASSERT_NO_THROW(hdsptr_->add(host4));
    ASSERT_NO_THROW(hdsptr_->add(host5));

    // Retrieve unknown name.
    ConstHostCollection from_hds = hdsptr_->getAllbyHostname4("foo", subnet4);
    EXPECT_TRUE(from_hds.empty());

    // Retrieve one reservation.
    from_hds = hdsptr_->getAllbyHostname4("host.example.com", subnet4);
    ASSERT_EQ(1, from_hds.size());
    HostDataSourceUtils::compareHosts(host4, from_hds[0]);

    // Check that the subnet is checked.
    from_hds = hdsptr_->getAllbyHostname4("host.example.com", subnet4 + 1);
    EXPECT_TRUE(from_hds.empty());

    // Retrieve all reservations with host hostname.
    from_hds = hdsptr_->getAllbyHostname4("host", subnet4);
    EXPECT_EQ(3, from_hds.size());
    bool got1 = false;
    bool got2 = false;
    bool got3 = false;
    for (auto host : from_hds) {
        if (host->getIdentifierType() == Host::IDENT_HWADDR) {
            EXPECT_FALSE(got1);
            got1 = true;
            HostDataSourceUtils::compareHosts(host1, host);
        } else if (!host->getCfgOption4()->empty()) {
            EXPECT_FALSE(got2);
            got2 = true;
            HostDataSourceUtils::compareHosts(host2, host);
        } else {
            EXPECT_FALSE(got3);
            got3 = true;
            HostDataSourceUtils::compareHosts(host3, host);
        }
    }
    EXPECT_TRUE(got1);
    EXPECT_TRUE(got2);
    EXPECT_TRUE(got3);
}

void
GenericHostDataSourceTest::testGetAllbyHostnameSubnet6() {
    // Make sure we have a pointer to the host data source.
    ASSERT_TRUE(hdsptr_);

    // Let's create some hosts...
    Host::IdentifierType id = Host::IDENT_HWADDR;
    HostPtr host1 = HostDataSourceUtils::initializeHost6("2001:db8::1", id, false);
    host1->setHostname("host");

    id = Host::IDENT_DUID;
    HostPtr host2 = HostDataSourceUtils::initializeHost6("2001:db8::2", id, false);
    host2->setHostname("Host");
    CfgOptionPtr opts = host2->getCfgOption6();
    OptionDescriptor desc =
        createOption<OptionString>(Option::V6, D6O_BOOTFILE_URL,
                                   true, true, "my-boot-file");
    opts->add(desc, DHCP6_OPTION_SPACE);

    HostPtr host3 = HostDataSourceUtils::initializeHost6("2001:db8::3", id, false);
    host3->setHostname("hOSt");

    HostPtr host4 = HostDataSourceUtils::initializeHost6("2001:db8::4", id, false);
    host4->setHostname("host.example.com");

    HostPtr host5 = HostDataSourceUtils::initializeHost6("2001:db8::5", id, false);

    // Set them in the same subnet at the exception of host5.
    SubnetID subnet4 = host1->getIPv4SubnetID();
    host2->setIPv4SubnetID(subnet4);
    host3->setIPv4SubnetID(subnet4);
    host4->setIPv4SubnetID(subnet4);
    SubnetID subnet6 = host1->getIPv6SubnetID();
    host2->setIPv6SubnetID(subnet6);
    host3->setIPv6SubnetID(subnet6);
    host4->setIPv6SubnetID(subnet6);

    // Now add them all to the host data source.
    ASSERT_NO_THROW(hdsptr_->add(host1));
    ASSERT_NO_THROW(hdsptr_->add(host2));
    ASSERT_NO_THROW(hdsptr_->add(host3));
    ASSERT_NO_THROW(hdsptr_->add(host4));
    ASSERT_NO_THROW(hdsptr_->add(host5));

    // Retrieve unknown name.
    ConstHostCollection from_hds = hdsptr_->getAllbyHostname6("foo", subnet6);
    EXPECT_TRUE(from_hds.empty());

    // Retrieve one reservation.
    from_hds = hdsptr_->getAllbyHostname6("host.example.com", subnet6);
    ASSERT_EQ(1, from_hds.size());
    HostDataSourceUtils::compareHosts(host4, from_hds[0]);

    // Check that the subnet is checked.
    from_hds = hdsptr_->getAllbyHostname6("host.example.com", subnet6 + 1);
    EXPECT_TRUE(from_hds.empty());

    // Retrieve all reservations with host hostname.
    from_hds = hdsptr_->getAllbyHostname6("host", subnet6);
    EXPECT_EQ(3, from_hds.size());
    bool got1 = false;
    bool got2 = false;
    bool got3 = false;
    for (auto host : from_hds) {
        if (host->getIdentifierType() == Host::IDENT_HWADDR) {
            EXPECT_FALSE(got1);
            got1 = true;
            HostDataSourceUtils::compareHosts(host1, host);
        } else if (!host->getCfgOption6()->empty()) {
            EXPECT_FALSE(got2);
            got2 = true;
            HostDataSourceUtils::compareHosts(host2, host);
        } else {
            EXPECT_FALSE(got3);
            got3 = true;
            HostDataSourceUtils::compareHosts(host3, host);
        }
    }
    EXPECT_TRUE(got1);
    EXPECT_TRUE(got2);
    EXPECT_TRUE(got3);
}

void
GenericHostDataSourceTest::testGetPage4() {
    // Make sure we have a pointer to the host data source.
    ASSERT_TRUE(hdsptr_);

    // Let's create some hosts...
    IOAddress addr("192.0.2.0");
    SubnetID subnet4(4);
    SubnetID subnet6(6);
    const Host::IdentifierType& id = Host::IDENT_DUID;
    for (unsigned i = 0; i < 25; ++i) {
        addr = IOAddress::increase(addr);

        HostPtr host = HostDataSourceUtils::initializeHost4(addr.toText(), id);
        host->setIPv4SubnetID(subnet4);
        host->setIPv6SubnetID(subnet6);

        ASSERT_NO_THROW(hdsptr_->add(host));
    }

    // Get first page.
    size_t idx(1);
    uint64_t host_id(0);
    HostPageSize page_size(10);
    ConstHostCollection page;
    ASSERT_NO_THROW(page = hdsptr_->getPage4(subnet4, idx, host_id, page_size));
    ASSERT_EQ(10, page.size());
    host_id = page[9]->getHostId();
    ASSERT_NE(0, host_id);

    // Get second and last pages.
    ASSERT_NO_THROW(page = hdsptr_->getPage4(subnet4, idx, host_id, page_size));
    ASSERT_EQ(10, page.size());
    host_id = page[9]->getHostId();
    ASSERT_NO_THROW(page = hdsptr_->getPage4(subnet4, idx, host_id, page_size));
    ASSERT_EQ(5, page.size());
    host_id = page[4]->getHostId();

    // Verify we have everything.
    ASSERT_NO_THROW(page = hdsptr_->getPage4(subnet4, idx, host_id, page_size));
    ASSERT_EQ(0, page.size());
    host_id = 0;

    // Other subnets are empty.
    ASSERT_NO_THROW(page = hdsptr_->getPage4(subnet6, idx, host_id, page_size));
    ASSERT_EQ(0, page.size());
}

void
GenericHostDataSourceTest::testGetPage6() {
    // Make sure we have a pointer to the host data source.
    ASSERT_TRUE(hdsptr_);

    // Let's create some hosts...
    IOAddress addr("2001:db8:1::");
    SubnetID subnet4(4);
    SubnetID subnet6(6);
    const Host::IdentifierType& id = Host::IDENT_HWADDR;
    for (unsigned i = 0; i < 25; ++i) {
        addr = IOAddress::increase(addr);

        HostPtr host = HostDataSourceUtils::initializeHost6(addr.toText(), id, false);
        host->setIPv4SubnetID(subnet4);
        host->setIPv6SubnetID(subnet6);

        ASSERT_NO_THROW(hdsptr_->add(host));
    }

    // Get first page.
    size_t idx(1);
    uint64_t host_id(0);
    HostPageSize page_size(10);
    ConstHostCollection page;
    ASSERT_NO_THROW(page = hdsptr_->getPage6(subnet6, idx, host_id, page_size));
    ASSERT_EQ(10, page.size());
    host_id = page[9]->getHostId();
    ASSERT_NE(0, host_id);

    // Get second and last pages.
    ASSERT_NO_THROW(page = hdsptr_->getPage6(subnet6, idx, host_id, page_size));
    ASSERT_EQ(10, page.size());
    host_id = page[9]->getHostId();
    ASSERT_NO_THROW(page = hdsptr_->getPage6(subnet6, idx, host_id, page_size));
    ASSERT_EQ(5, page.size());
    host_id = page[4]->getHostId();

    // Verify we have everything.
    ASSERT_NO_THROW(page = hdsptr_->getPage6(subnet6, idx, host_id, page_size));
    ASSERT_EQ(0, page.size());
    host_id = 0;

    // Other subnets are empty.
    ASSERT_NO_THROW(page = hdsptr_->getPage6(subnet4, idx, host_id, page_size));
    ASSERT_EQ(0, page.size());
}

void
GenericHostDataSourceTest::testGetPageLimit4(const Host::IdentifierType& id) {
    // From the ticket: add 5 hosts each with 3 options.
    // call getPage4 with limit of 4.
    // The first page should return 4 hosts,
    // the second should return one host.b

    // Make sure we have a pointer to the host data source.
    ASSERT_TRUE(hdsptr_);

    // Let's create some hosts...
    IOAddress addr("192.0.2.0");
    SubnetID subnet4(4);
    SubnetID subnet6(6);
    for (unsigned i = 0; i < 5; ++i) {
        addr = IOAddress::increase(addr);

        HostPtr host = HostDataSourceUtils::initializeHost4(addr.toText(), id);
        host->setIPv4SubnetID(subnet4);
        host->setIPv6SubnetID(subnet6);

        // Add DHCPv4 options.
        CfgOptionPtr opts = host->getCfgOption4();
        OptionDescriptor desc =
            createOption<OptionString>(Option::V4, DHO_BOOT_FILE_NAME,
                                       true, false, "my-boot-file");
        opts->add(desc, DHCP4_OPTION_SPACE);
        opts->add(createOption<OptionUint8>(Option::V4, DHO_DEFAULT_IP_TTL,
                                            false, false, 64 + i),
                  DHCP4_OPTION_SPACE);
        opts->add(createEmptyOption(Option::V4, 1, true), "isc");

        ASSERT_NO_THROW(hdsptr_->add(host));
    }

    // Get first page.
    size_t idx(1);
    uint64_t host_id(0);
    HostPageSize page_size(4);
    ConstHostCollection page;
    ASSERT_NO_THROW(page = hdsptr_->getPage4(subnet4, idx, host_id, page_size));
    ASSERT_EQ(4, page.size());
    host_id = page[3]->getHostId();
    ASSERT_NE(0, host_id);

    // Get second and last pages.
    ASSERT_NO_THROW(page = hdsptr_->getPage4(subnet4, idx, host_id, page_size));
    ASSERT_EQ(1, page.size());
    host_id = page[0]->getHostId();

    // Verify we have everything.
    ASSERT_NO_THROW(page = hdsptr_->getPage4(subnet4, idx, host_id, page_size));
    ASSERT_EQ(0, page.size());
}

void
GenericHostDataSourceTest::testGetPageLimit6(const Host::IdentifierType& id) {
    // From the ticket: add several v6 hosts with multiple address/prefix
    // reservations and multiple options.
    // Get hosts by page with page size 1.
    // Make sure all address/prefix reservations are returned.
    // Make sure all options are returned as expected.

    // Make sure we have a pointer to the host data source.
    ASSERT_TRUE(hdsptr_);

    // Let's create some hosts...
    IOAddress addr("2001:db8:1::");
    SubnetID subnet4(4);
    SubnetID subnet6(6);

    vector<HostPtr> hosts;

    for (unsigned i = 0; i < 5; ++i) {
        addr = IOAddress::increase(addr);
        ostringstream pref;
        pref << "2001:db8:2:" << 10 + i << "::";

        HostPtr host = HostDataSourceUtils::initializeHost6(addr.toText(), id, false);
        host->setIPv4SubnetID(subnet4);
        host->setIPv6SubnetID(subnet6);

        // Add address/prefix.
        addr = IOAddress::increase(addr);
        IPv6Resrv resva(IPv6Resrv::TYPE_NA, addr, 128);
        host->addReservation(resva);
        IPv6Resrv resvp(IPv6Resrv::TYPE_PD, IOAddress(pref.str()), 64);
        host->addReservation(resvp);

        // Add DHCPv6 options.
        CfgOptionPtr opts = host->getCfgOption6();
        OptionDescriptor desc =
            createOption<OptionString>(Option::V6, D6O_BOOTFILE_URL,
                                       true, false, "my-boot-file");
        opts->add(desc, DHCP6_OPTION_SPACE);
        opts->add(createOption<OptionUint32>(Option::V6,
                                             D6O_INFORMATION_REFRESH_TIME,
                                             false, false, 3600 + i),
                  DHCP6_OPTION_SPACE);
        opts->add(createAddressOption<Option6AddrLst>(D6O_SIP_SERVERS_ADDR,
                                                      false, false,
                                                      addr.toText()),
                  DHCP6_OPTION_SPACE);

        ASSERT_NO_THROW(hdsptr_->add(host));
        hosts.push_back(host);
    }

    // Get first page.
    size_t idx(1);
    uint64_t host_id(0);
    HostPageSize page_size(4);
    ConstHostCollection page;
    ConstHostCollection all_pages;
    ASSERT_NO_THROW(page = hdsptr_->getPage6(subnet6, idx, host_id, page_size));
    ASSERT_EQ(4, page.size());
    host_id = page[3]->getHostId();
    ASSERT_NE(0, host_id);

    std::copy(page.begin(), page.end(), std::back_inserter(all_pages));

    // Get second and last pages.
    ASSERT_NO_THROW(page = hdsptr_->getPage6(subnet6, idx, host_id, page_size));
    ASSERT_EQ(1, page.size());
    host_id = page[0]->getHostId();

    std::copy(page.begin(), page.end(), std::back_inserter(all_pages));

    // Verify we have everything.
    ASSERT_NO_THROW(page = hdsptr_->getPage6(subnet6, idx, host_id, page_size));
    ASSERT_EQ(0, page.size());

    // hosts are sorted by generated host_id (which is an auto increment for
    // MySql and PostgreSql and a hash for Cassandra) so the hosts must be
    // sorted by host identifier
    std::sort(all_pages.begin(), all_pages.end(), compareHostsIdentifier);

    // Verify we got what we expected.
    for (size_t i = 0; i < 5; ++i) {
        HostDataSourceUtils::compareHosts(hosts[i], all_pages[i]);
    }
}

void
GenericHostDataSourceTest::testGetPage4Subnets() {
    // From the ticket: add one host to subnet1, add one host to subnet2.
    // repeat 5 times. Get hosts from subnet1 with page size 3.
    // Make sure the right hosts are returned and in expected page
    //sizes (3, then 2).

    // Make sure we have a pointer to the host data source.
    ASSERT_TRUE(hdsptr_);

    // Let's create some hosts...
    const Host::IdentifierType& id = Host::IDENT_HWADDR;
    IOAddress addr("192.0.2.0");
    SubnetID subnet4(4);
    SubnetID subnet6(6);
    vector<HostPtr> hosts;
    for (unsigned i = 0; i < 10; ++i) {
        addr = IOAddress::increase(addr);

        HostPtr host = HostDataSourceUtils::initializeHost4(addr.toText(), id);
        host->setIPv4SubnetID(subnet4 + (i & 1));
        host->setIPv6SubnetID(subnet6 + (i & 1));

        ASSERT_NO_THROW(hdsptr_->add(host));
        hosts.push_back(host);
    }

    // First subnet.

    // Get first page.
    size_t idx(1);
    uint64_t host_id(0);
    HostPageSize page_size(3);
    ConstHostCollection page;
    ConstHostCollection all_pages;
    ASSERT_NO_THROW(page = hdsptr_->getPage4(subnet4, idx, host_id, page_size));
    ASSERT_EQ(3, page.size());
    host_id = page[2]->getHostId();
    ASSERT_NE(0, host_id);

    std::copy(page.begin(), page.end(), std::back_inserter(all_pages));

    // Get second and last pages.
    ASSERT_NO_THROW(page = hdsptr_->getPage4(subnet4, idx, host_id, page_size));
    ASSERT_EQ(2, page.size());
    host_id = page[1]->getHostId();

    std::copy(page.begin(), page.end(), std::back_inserter(all_pages));

    // Verify we have everything.
    ASSERT_NO_THROW(page = hdsptr_->getPage4(subnet4, idx, host_id, page_size));
    ASSERT_EQ(0, page.size());

    // hosts are sorted by generated host_id (which is an auto increment for
    // MySql and PostgreSql and a hash for Cassandra) so the hosts must be
    // sorted by host identifier
    std::sort(all_pages.begin(), all_pages.end(), compareHostsIdentifier);

    // Verify we got what we expected.
    for (size_t i = 0; i < 5; ++i) {
        HostDataSourceUtils::compareHosts(hosts[i * 2], all_pages[i]);
    }

    all_pages.clear();

    // Second subnet.
    ++subnet4;

    // Get first page.
    idx = 0;
    host_id = 0;
    ASSERT_NO_THROW(page = hdsptr_->getPage4(subnet4, idx, host_id, page_size));
    ASSERT_EQ(3, page.size());
    host_id = page[2]->getHostId();
    ASSERT_NE(0, host_id);

    std::copy(page.begin(), page.end(), std::back_inserter(all_pages));

    // Get second and last pages.
    ASSERT_NO_THROW(page = hdsptr_->getPage4(subnet4, idx, host_id, page_size));
    ASSERT_EQ(2, page.size());
    host_id = page[1]->getHostId();

    std::copy(page.begin(), page.end(), std::back_inserter(all_pages));

    // Verify we have everything.
    ASSERT_NO_THROW(page = hdsptr_->getPage4(subnet4, idx, host_id, page_size));
    ASSERT_EQ(0, page.size());

    // hosts are sorted by generated host_id (which is an auto increment for
    // MySql and PostgreSql and a hash for Cassandra) so the hosts must be
    // sorted by host identifier
    std::sort(all_pages.begin(), all_pages.end(), compareHostsIdentifier);

    // Verify we got what we expected.
    for (size_t i = 0; i < 5; ++i) {
        HostDataSourceUtils::compareHosts(hosts[i * 2 + 1], all_pages[i]);
    }
}

void
GenericHostDataSourceTest::testGetPage6Subnets() {
    // From the ticket: add one host to subnet1, add one host to subnet2.
    // repeat 5 times. Get hosts from subnet1 with page size 3.
    // Make sure the right hosts are returned and in expected page
    //sizes (3, then 2).

    // Make sure we have a pointer to the host data source.
    ASSERT_TRUE(hdsptr_);

    // Let's create some hosts...
    const Host::IdentifierType& id = Host::IDENT_DUID;
    IOAddress addr("2001:db8:1::");
    SubnetID subnet4(4);
    SubnetID subnet6(6);
    vector<HostPtr> hosts;
    for (unsigned i = 0; i < 10; ++i) {
        addr = IOAddress::increase(addr);

        HostPtr host = HostDataSourceUtils::initializeHost6(addr.toText(), id, false);
        host->setIPv4SubnetID(subnet4 + (i & 1));
        host->setIPv6SubnetID(subnet6 + (i & 1));

        ASSERT_NO_THROW(hdsptr_->add(host));
        hosts.push_back(host);
    }

    // First subnet.

    // Get first page.
    size_t idx(1);
    uint64_t host_id(0);
    HostPageSize page_size(3);
    ConstHostCollection page;
    ConstHostCollection all_pages;
    ASSERT_NO_THROW(page = hdsptr_->getPage6(subnet6, idx, host_id, page_size));
    ASSERT_EQ(3, page.size());
    host_id = page[2]->getHostId();
    ASSERT_NE(0, host_id);

    std::copy(page.begin(), page.end(), std::back_inserter(all_pages));

    // Get second and last pages.
    ASSERT_NO_THROW(page = hdsptr_->getPage6(subnet6, idx, host_id, page_size));
    ASSERT_EQ(2, page.size());
    host_id = page[1]->getHostId();

    std::copy(page.begin(), page.end(), std::back_inserter(all_pages));

    // Verify we have everything.
    ASSERT_NO_THROW(page = hdsptr_->getPage6(subnet6, idx, host_id, page_size));
    ASSERT_EQ(0, page.size());

    // hosts are sorted by generated host_id (which is an auto increment for
    // MySql and PostgreSql and a hash for Cassandra) so the hosts must be
    // sorted by host identifier
    std::sort(all_pages.begin(), all_pages.end(), compareHostsIdentifier);

    // Verify we got what we expected.
    for (size_t i = 0; i < 5; ++i) {
        HostDataSourceUtils::compareHosts(hosts[i * 2], all_pages[i]);
    }

    all_pages.clear();

    // Second subnet.
    ++subnet6;

    // Get first page.
    idx = 0;
    host_id = 0;
    ASSERT_NO_THROW(page = hdsptr_->getPage6(subnet6, idx, host_id, page_size));
    ASSERT_EQ(3, page.size());
    host_id = page[2]->getHostId();
    ASSERT_NE(0, host_id);

    std::copy(page.begin(), page.end(), std::back_inserter(all_pages));

    // Get second and last pages.
    ASSERT_NO_THROW(page = hdsptr_->getPage6(subnet6, idx, host_id, page_size));
    ASSERT_EQ(2, page.size());
    host_id = page[1]->getHostId();

    std::copy(page.begin(), page.end(), std::back_inserter(all_pages));

    // Verify we have everything.
    ASSERT_NO_THROW(page = hdsptr_->getPage6(subnet6, idx, host_id, page_size));
    ASSERT_EQ(0, page.size());

    // hosts are sorted by generated host_id (which is an auto increment for
    // MySql and PostgreSql and a hash for Cassandra) so the hosts must be
    // sorted by host identifier
    std::sort(all_pages.begin(), all_pages.end(), compareHostsIdentifier);

    // Verify we got what we expected.
    for (size_t i = 0; i < 5; ++i) {
        HostDataSourceUtils::compareHosts(hosts[i * 2 + 1], all_pages[i]);
    }
}

void
GenericHostDataSourceTest::testGetByIPv4(const Host::IdentifierType& id) {
    // Make sure we have a pointer to the host data source.
    ASSERT_TRUE(hdsptr_);

    // Let's create a couple of hosts...
    HostPtr host1 = HostDataSourceUtils::initializeHost4("192.0.2.1", id);
    HostPtr host2 = HostDataSourceUtils::initializeHost4("192.0.2.2", id);
    HostPtr host3 = HostDataSourceUtils::initializeHost4("192.0.2.3", id);
    HostPtr host4 = HostDataSourceUtils::initializeHost4("192.0.2.4", id);

    // ... and add them to the data source.
    ASSERT_NO_THROW(hdsptr_->add(host1));
    ASSERT_NO_THROW(hdsptr_->add(host2));
    ASSERT_NO_THROW(hdsptr_->add(host3));
    ASSERT_NO_THROW(hdsptr_->add(host4));

    SubnetID subnet1 = host1->getIPv4SubnetID();
    SubnetID subnet2 = host2->getIPv4SubnetID();
    SubnetID subnet3 = host3->getIPv4SubnetID();
    SubnetID subnet4 = host4->getIPv4SubnetID();

    // And then try to retrieve them back.
    ConstHostPtr from_hds1 = hdsptr_->get4(subnet1, IOAddress("192.0.2.1"));
    ConstHostPtr from_hds2 = hdsptr_->get4(subnet2, IOAddress("192.0.2.2"));
    ConstHostPtr from_hds3 = hdsptr_->get4(subnet3, IOAddress("192.0.2.3"));
    ConstHostPtr from_hds4 = hdsptr_->get4(subnet4, IOAddress("192.0.2.4"));

    // Make sure we got something back.
    ASSERT_TRUE(from_hds1);
    ASSERT_TRUE(from_hds2);
    ASSERT_TRUE(from_hds3);
    ASSERT_TRUE(from_hds4);

    // Then let's check that what we got seems correct.
    HostDataSourceUtils::compareHosts(host1, from_hds1);
    HostDataSourceUtils::compareHosts(host2, from_hds2);
    HostDataSourceUtils::compareHosts(host3, from_hds3);
    HostDataSourceUtils::compareHosts(host4, from_hds4);

    // Ok, finally let's check that getting by a different address
    // will not work.
    EXPECT_FALSE(hdsptr_->get4(subnet1, IOAddress("192.0.1.5")));
}

void
GenericHostDataSourceTest::testGet4ByIdentifier(
    const Host::IdentifierType& identifier_type) {
    // Make sure we have a pointer to the host data source.
    ASSERT_TRUE(hdsptr_);

    HostPtr host1 = HostDataSourceUtils::initializeHost4("192.0.2.1", identifier_type);
    HostPtr host2 = HostDataSourceUtils::initializeHost4("192.0.2.2", identifier_type);

    // Sanity check: make sure the hosts have different identifiers..
    ASSERT_FALSE(host1->getIdentifier() == host2->getIdentifier());

    // Try to add both of them to the host data source.
    ASSERT_NO_THROW(hdsptr_->add(host1));
    ASSERT_NO_THROW(hdsptr_->add(host2));

    SubnetID subnet1 = host1->getIPv4SubnetID();
    SubnetID subnet2 = host2->getIPv4SubnetID();

    ConstHostPtr from_hds1 =
        hdsptr_->get4(subnet1, identifier_type, &host1->getIdentifier()[0],
                      host1->getIdentifier().size());

    ConstHostPtr from_hds2 =
        hdsptr_->get4(subnet2, identifier_type, &host2->getIdentifier()[0],
                      host2->getIdentifier().size());

    // Now let's check if we got what we expected.
    ASSERT_TRUE(from_hds1);
    ASSERT_TRUE(from_hds2);
    HostDataSourceUtils::compareHosts(host1, from_hds1);
    HostDataSourceUtils::compareHosts(host2, from_hds2);
}

void
GenericHostDataSourceTest::testHWAddrNotClientId() {
    // Make sure we have a pointer to the host data source.
    ASSERT_TRUE(hdsptr_);

    // Create a host with HW address
    HostPtr host = HostDataSourceUtils::initializeHost4("192.0.2.1", Host::IDENT_HWADDR);
    ASSERT_TRUE(host->getHWAddress());
    ASSERT_FALSE(host->getDuid());

    // Try to add it to the host data source.
    ASSERT_NO_THROW(hdsptr_->add(host));

    SubnetID subnet = host->getIPv4SubnetID();

    DuidPtr duid = HWAddrToDuid(host->getHWAddress());

    // Get the host by HW address (should succeed)
    ConstHostPtr by_hwaddr =
        hdsptr_->get4(subnet, Host::IDENT_HWADDR, &host->getIdentifier()[0],
                      host->getIdentifier().size());

    // Get the host by DUID (should fail)
    ConstHostPtr by_duid =
        hdsptr_->get4(subnet, Host::IDENT_DUID, &host->getIdentifier()[0],
                      host->getIdentifier().size());

    // Now let's check if we got what we expected.
    EXPECT_TRUE(by_hwaddr);
    EXPECT_FALSE(by_duid);
}

void
GenericHostDataSourceTest::testClientIdNotHWAddr() {
    // Make sure we have a pointer to the host data source.
    ASSERT_TRUE(hdsptr_);

    // Create a host with client-id
    HostPtr host = HostDataSourceUtils::initializeHost4("192.0.2.1", Host::IDENT_DUID);
    ASSERT_FALSE(host->getHWAddress());
    ASSERT_TRUE(host->getDuid());

    // Try to add it to the host data source.
    ASSERT_NO_THROW(hdsptr_->add(host));

    SubnetID subnet = host->getIPv4SubnetID();

    HWAddrPtr hwaddr = DuidToHWAddr(host->getDuid());

    // Get the host by DUID (should succeed)
    ConstHostPtr by_duid =
        hdsptr_->get4(subnet, Host::IDENT_DUID, &host->getIdentifier()[0],
                      host->getIdentifier().size());

    // Get the host by HW address (should fail)
    ConstHostPtr by_hwaddr =
        hdsptr_->get4(subnet, Host::IDENT_HWADDR, &host->getIdentifier()[0],
                      host->getIdentifier().size());

    // Now let's check if we got what we expected.
    EXPECT_TRUE(by_duid);
    EXPECT_FALSE(by_hwaddr);
}

void
GenericHostDataSourceTest::testHostname(std::string name, int num) {
    // Make sure we have a pointer to the host data source.
    ASSERT_TRUE(hdsptr_);

    // Initialize the address to 192.0.2.0 (this will be bumped
    // up to 192.0.2.1 in the first iteration)
    IOAddress addr("192.0.2.0");

    vector<HostPtr> hosts;

    // Prepare a vector of hosts with unique hostnames
    for (int i = 0; i < num; ++i) {
        addr = IOAddress::increase(addr);

        HostPtr host = HostDataSourceUtils::initializeHost4(addr.toText(), Host::IDENT_DUID);

        stringstream hostname;
        hostname.str("");
        if (num > 1) {
            hostname << i;
        }
        hostname << name;
        host->setHostname(hostname.str());

        hosts.push_back(host);
    }

    // Now add them all to the host data source.
    for (vector<HostPtr>::const_iterator it = hosts.begin(); it != hosts.end();
         ++it) {
        // Try to add both of the to the host data source.
        ASSERT_NO_THROW(hdsptr_->add(*it));
    }

    // And finally retrieve them one by one and check
    // if the hostname was preserved.
    for (vector<HostPtr>::const_iterator it = hosts.begin(); it != hosts.end();
         ++it) {
        ConstHostPtr from_hds;
        ASSERT_NO_THROW(from_hds = hdsptr_->get4((*it)->getIPv4SubnetID(),
                                                 (*it)->getIPv4Reservation()));
        ASSERT_TRUE(from_hds);

        EXPECT_EQ((*it)->getHostname(), from_hds->getHostname());
    }
}

void
GenericHostDataSourceTest::testUserContext(ConstElementPtr user_context) {

    // Make sure we have a pointer to the host data source.
    ASSERT_TRUE(hdsptr_);

    // Create a host reservation.
    HostPtr host = HostDataSourceUtils::initializeHost4("192.0.2.1", Host::IDENT_DUID);
    ASSERT_TRUE(host); // Make sure the host is generated properly.
    host->setContext(user_context);
    SubnetID subnet = host->getIPv4SubnetID();

    // Try to add it to the host data source.
    ASSERT_NO_THROW(hdsptr_->add(host));

    // Retrieve it.
    ConstHostPtr from_hds = hdsptr_->get4(subnet, IOAddress("192.0.2.1"));
    ASSERT_TRUE(from_hds);

    // Finally, let's check if what we got makes any sense.
    HostDataSourceUtils::compareHosts(host, from_hds);

    // Retry with IPv6
    host = HostDataSourceUtils::initializeHost6("2001:db8::1", Host::IDENT_HWADDR, false);
    ASSERT_TRUE(host);
    ASSERT_TRUE(host->getHWAddress());
    host->setContext(user_context);
    host->setHostname("foo.example.com");
    subnet = host->getIPv6SubnetID();

    ASSERT_NO_THROW(hdsptr_->add(host));

    from_hds = hdsptr_->get6(subnet, Host::IDENT_HWADDR,
                             &host->getIdentifier()[0],
                             host->getIdentifier().size());
    ASSERT_TRUE(from_hds);

    HostDataSourceUtils::compareHosts(host, from_hds);
}

void
GenericHostDataSourceTest::testMultipleSubnets(int subnets,
                                               const Host::IdentifierType& id) {
    // Make sure we have a pointer to the host data source.
    ASSERT_TRUE(hdsptr_);

    HostPtr host = HostDataSourceUtils::initializeHost4("192.0.2.1", id);
    host->setIPv6SubnetID(SUBNET_ID_UNUSED);

    for (int i = 0; i < subnets; ++i) {
        host->setIPv4SubnetID(i + 1000);
        ASSERT_NO_THROW(hdsptr_->add(host));
    }

    // Now check that the reservations can be retrieved by IPv4 address from
    // each subnet separately.
    for (int i = 0; i < subnets; ++i) {
        // Try to retrieve the host by IPv4 address.
        ConstHostPtr from_hds =
            hdsptr_->get4(i + 1000, host->getIPv4Reservation());

        ASSERT_TRUE(from_hds);
        EXPECT_EQ(i + 1000, from_hds->getIPv4SubnetID());

        // Try to retrieve the host by either HW address of client-id
        from_hds = hdsptr_->get4(i + 1000, id, &host->getIdentifier()[0],
                                 host->getIdentifier().size());
        ASSERT_TRUE(from_hds);
        EXPECT_EQ(i + 1000, from_hds->getIPv4SubnetID());
    }

    // Now check that they can be retrieved all at once, by IPv4 address.
    ConstHostCollection all_by_addr = hdsptr_->getAll4(IOAddress("192.0.2.1"));
    ASSERT_EQ(subnets, all_by_addr.size());

    // Verify that the values returned are proper.
    int i = 0;
    if (hdsptr_->getType() == "cql") {
        // There is no ORDER BY in Cassandra. Order here. Remove this if entries
        // are eventually implemented as ordered in the Cassandra host data
        // source.
        std::sort(all_by_addr.begin(), all_by_addr.end(), compareHostsForSort4);
    }
    for (ConstHostCollection::const_iterator it = all_by_addr.begin();
         it != all_by_addr.end(); ++it) {
        EXPECT_EQ(IOAddress("192.0.2.1"), (*it)->getIPv4Reservation());
        EXPECT_EQ(1000 + i++, (*it)->getIPv4SubnetID());
    }

    // Finally, check that the hosts can be retrieved by HW address or DUID
    ConstHostCollection all_by_id = hdsptr_->getAll(
        id, &host->getIdentifier()[0], host->getIdentifier().size());
    ASSERT_EQ(subnets, all_by_id.size());

    // Check that the returned values are as expected.
    i = 0;
    if (hdsptr_->getType() == "cql") {
        // There is no ORDER BY in Cassandra. Order here. Remove this if entries
        // are eventually implemented as ordered in the Cassandra host data
        // source.
        std::sort(all_by_id.begin(), all_by_id.end(), compareHostsForSort4);
    }
    for (ConstHostCollection::const_iterator it = all_by_id.begin();
         it != all_by_id.end(); ++it) {
        EXPECT_EQ(IOAddress("192.0.2.1"), (*it)->getIPv4Reservation());
        EXPECT_EQ(1000 + i++, (*it)->getIPv4SubnetID());
    }
}

void
GenericHostDataSourceTest::testGet6ByHWAddr() {
    // Make sure we have the pointer to the host data source.
    ASSERT_TRUE(hdsptr_);

    // Create a host reservations.
    HostPtr host1 = HostDataSourceUtils::initializeHost6("2001:db8::1", Host::IDENT_HWADDR, false);
    HostPtr host2 = HostDataSourceUtils::initializeHost6("2001:db8::2", Host::IDENT_HWADDR, false);

    // Sanity check: make sure the hosts have different HW addresses.
    ASSERT_TRUE(host1->getHWAddress());
    ASSERT_TRUE(host2->getHWAddress());

    HostDataSourceUtils::compareHwaddrs(host1, host2, false);

    // Try to add both of them to the host data source.
    ASSERT_NO_THROW(hdsptr_->add(host1));
    ASSERT_NO_THROW(hdsptr_->add(host2));

    SubnetID subnet1 = host1->getIPv6SubnetID();
    SubnetID subnet2 = host2->getIPv6SubnetID();

    ConstHostPtr from_hds1 = hdsptr_->get6(subnet1, Host::IDENT_HWADDR,
                                           &host1->getIdentifier()[0],
                                           host1->getIdentifier().size());

    ConstHostPtr from_hds2 = hdsptr_->get6(subnet2, Host::IDENT_HWADDR,
                                           &host2->getIdentifier()[0],
                                           host2->getIdentifier().size());

    // Now let's check if we got what we expected.
    ASSERT_TRUE(from_hds1);
    ASSERT_TRUE(from_hds2);
    HostDataSourceUtils::compareHosts(host1, from_hds1);
    HostDataSourceUtils::compareHosts(host2, from_hds2);
}

void
GenericHostDataSourceTest::testGet6ByClientId() {
    // Make sure we have the pointer to the host data source.
    ASSERT_TRUE(hdsptr_);

    // Create a host reservations.
    HostPtr host1 = HostDataSourceUtils::initializeHost6("2001:db8::1", Host::IDENT_DUID, false);
    HostPtr host2 = HostDataSourceUtils::initializeHost6("2001:db8::2", Host::IDENT_DUID, false);

    // Sanity check: make sure the hosts have different HW addresses.
    ASSERT_TRUE(host1->getDuid());
    ASSERT_TRUE(host2->getDuid());

    HostDataSourceUtils::compareDuids(host1, host2, false);

    // Try to add both of them to the host data source.
    ASSERT_NO_THROW(hdsptr_->add(host1));
    ASSERT_NO_THROW(hdsptr_->add(host2));

    SubnetID subnet1 = host1->getIPv6SubnetID();
    SubnetID subnet2 = host2->getIPv6SubnetID();

    ConstHostPtr from_hds1 = hdsptr_->get6(subnet1, Host::IDENT_DUID,
                                           &host1->getIdentifier()[0],
                                           host1->getIdentifier().size());

    ConstHostPtr from_hds2 = hdsptr_->get6(subnet2, Host::IDENT_DUID,
                                           &host2->getIdentifier()[0],
                                           host2->getIdentifier().size());

    // Now let's check if we got what we expected.
    ASSERT_TRUE(from_hds1);
    ASSERT_TRUE(from_hds2);
    HostDataSourceUtils::compareHosts(host1, from_hds1);
    HostDataSourceUtils::compareHosts(host2, from_hds2);
}

void
GenericHostDataSourceTest::testSubnetId6(int subnets, Host::IdentifierType id) {
    // Make sure we have a pointer to the host data source.
    ASSERT_TRUE(hdsptr_);

    HostPtr host;
    IOAddress current_address("2001:db8::0");
    for (int i = 0; i < subnets; ++i) {
        // Last boolean value set to false indicates that the same identifier
        // must be used for each generated host.
        host = HostDataSourceUtils::initializeHost6(current_address.toText(),
                                                    id, true, false, "");

        host->setIPv4SubnetID(i + 1000);
        host->setIPv6SubnetID(i + 1000);

        // Check that the same host can have reservations in multiple subnets.
        EXPECT_NO_THROW(hdsptr_->add(host));

        // Increase address to make sure we don't assign the same address
        // in different subnets.
        current_address = IOAddress::increase(current_address);
    }

    // Check that the reservations can be retrieved from each subnet separately.
    for (int i = 0; i < subnets; ++i) {
        // Try to retrieve the host
        ConstHostPtr from_hds = hdsptr_->get6(i + 1000, id, &host->getIdentifier()[0],
                                              host->getIdentifier().size());

        ASSERT_TRUE(from_hds) << "failed for i=" << i;
        EXPECT_EQ(i + 1000, from_hds->getIPv6SubnetID());
    }

    // Check that the hosts can all be retrieved by HW address or DUID
    ConstHostCollection all_by_id = hdsptr_->getAll(id, &host->getIdentifier()[0],
                                                    host->getIdentifier().size());
    ASSERT_EQ(subnets, all_by_id.size());

    // Check that the returned values are as expected.
    int i = 0;
    if (hdsptr_->getType() == "cql") {
        // There is no ORDER BY in Cassandra. Order here. Remove this if entries
        // are eventually implemented as ordered in the Cassandra host data
        // source.
        std::sort(all_by_id.begin(), all_by_id.end(), compareHostsForSort6);
    }
    for (ConstHostCollection::const_iterator it = all_by_id.begin();
         it != all_by_id.end(); ++it) {
        EXPECT_EQ(IOAddress("0.0.0.0"), (*it)->getIPv4Reservation());
        EXPECT_EQ(1000 + i++, (*it)->getIPv6SubnetID());
    }
}

void
GenericHostDataSourceTest::testGetByIPv6(Host::IdentifierType id, bool prefix) {
    // Make sure we have a pointer to the host data source.
    ASSERT_TRUE(hdsptr_);

    // Let's create a couple of hosts...
    HostPtr host1 = HostDataSourceUtils::initializeHost6("2001:db8::1",
                                                        id, prefix, "key##1");
    HostPtr host2 = HostDataSourceUtils::initializeHost6("2001:db8::2",
                                                        id, prefix, "key##2");
    HostPtr host3 = HostDataSourceUtils::initializeHost6("2001:db8::3",
                                                        id, prefix, "key##3");
    HostPtr host4 = HostDataSourceUtils::initializeHost6("2001:db8::4",
                                                        id, prefix, "key##4");

    // ... and add them to the data source.
    ASSERT_NO_THROW(hdsptr_->add(host1));
    ASSERT_NO_THROW(hdsptr_->add(host2));
    ASSERT_NO_THROW(hdsptr_->add(host3));
    ASSERT_NO_THROW(hdsptr_->add(host4));

    // Are we talking about addresses or prefixes?
    uint8_t len = prefix ? 64 : 128;

    // And then try to retrieve them back.
    ConstHostPtr from_hds1 = hdsptr_->get6(IOAddress("2001:db8::1"), len);
    ConstHostPtr from_hds2 = hdsptr_->get6(IOAddress("2001:db8::2"), len);
    ConstHostPtr from_hds3 = hdsptr_->get6(IOAddress("2001:db8::3"), len);
    ConstHostPtr from_hds4 = hdsptr_->get6(IOAddress("2001:db8::4"), len);

    // Make sure we got something back.
    ASSERT_TRUE(from_hds1);
    ASSERT_TRUE(from_hds2);
    ASSERT_TRUE(from_hds3);
    ASSERT_TRUE(from_hds4);

    // Then let's check that what we got seems correct.
    HostDataSourceUtils::compareHosts(host1, from_hds1);
    HostDataSourceUtils::compareHosts(host2, from_hds2);
    HostDataSourceUtils::compareHosts(host3, from_hds3);
    HostDataSourceUtils::compareHosts(host4, from_hds4);

    // Ok, finally let's check that getting by a different address
    // will not work.
    EXPECT_FALSE(hdsptr_->get6(IOAddress("2001:db8::5"), len));
}

void
GenericHostDataSourceTest::testGetBySubnetIPv6() {
    // Make sure we have a pointer to the host data source.
    ASSERT_TRUE(hdsptr_);

    // Let's create a couple of hosts...
    HostPtr host1 = HostDataSourceUtils::initializeHost6("2001:db8:1::", Host::IDENT_DUID, true);
    HostPtr host2 = HostDataSourceUtils::initializeHost6("2001:db8:2::", Host::IDENT_DUID, true);
    HostPtr host3 = HostDataSourceUtils::initializeHost6("2001:db8:3::", Host::IDENT_DUID, true);
    HostPtr host4 = HostDataSourceUtils::initializeHost6("2001:db8:4::", Host::IDENT_DUID, true);

    // ... and add them to the data source.
    ASSERT_NO_THROW(hdsptr_->add(host1));
    ASSERT_NO_THROW(hdsptr_->add(host2));
    ASSERT_NO_THROW(hdsptr_->add(host3));
    ASSERT_NO_THROW(hdsptr_->add(host4));

    // And then try to retrieve them back.
    ConstHostPtr from_hds1 = hdsptr_->get6(host1->getIPv6SubnetID(), IOAddress("2001:db8:1::"));
    ConstHostPtr from_hds2 = hdsptr_->get6(host2->getIPv6SubnetID(), IOAddress("2001:db8:2::"));
    ConstHostPtr from_hds3 = hdsptr_->get6(host3->getIPv6SubnetID(), IOAddress("2001:db8:3::"));
    ConstHostPtr from_hds4 = hdsptr_->get6(host4->getIPv6SubnetID(), IOAddress("2001:db8:4::"));

    // Make sure we got something back.
    ASSERT_TRUE(from_hds1);
    ASSERT_TRUE(from_hds2);
    ASSERT_TRUE(from_hds3);
    ASSERT_TRUE(from_hds4);

    // Then let's check that what we got seems correct.
    HostDataSourceUtils::compareHosts(host1, from_hds1);
    HostDataSourceUtils::compareHosts(host2, from_hds2);
    HostDataSourceUtils::compareHosts(host3, from_hds3);
    HostDataSourceUtils::compareHosts(host4, from_hds4);
}

void
GenericHostDataSourceTest::testAddDuplicate6WithSameDUID() {
    // Make sure we have the pointer to the host data source.
    ASSERT_TRUE(hdsptr_);

    // Create a host reservations.
    HostPtr host = HostDataSourceUtils::initializeHost6("2001:db8::1", Host::IDENT_DUID, true);

    // Add this reservation once.
    ASSERT_NO_THROW(hdsptr_->add(host));

    // Then try to add it again, it should throw an exception.
    ASSERT_THROW(hdsptr_->add(host), DuplicateEntry);
}

void
GenericHostDataSourceTest::testAddDuplicate6WithSameHWAddr() {
    // Make sure we have the pointer to the host data source.
    ASSERT_TRUE(hdsptr_);

    // Create a host reservations.
    HostPtr host = HostDataSourceUtils::initializeHost6("2001:db8::1", Host::IDENT_HWADDR, true);

    // Add this reservation once.
    ASSERT_NO_THROW(hdsptr_->add(host));

    // Then try to add it again, it should throw an exception.
    ASSERT_THROW(hdsptr_->add(host), DuplicateEntry);
}

void
GenericHostDataSourceTest::testAddDuplicate4() {
    // Make sure we have the pointer to the host data source.
    ASSERT_TRUE(hdsptr_);

    // Create a host reservations.
    HostPtr host = HostDataSourceUtils::initializeHost4("192.0.2.1", Host::IDENT_DUID);

    // Add this reservation once.
    ASSERT_NO_THROW(hdsptr_->add(host));

    // Then try to add it again, it should throw an exception.
    ASSERT_THROW(hdsptr_->add(host), DuplicateEntry);

    // This time use a different host identifier and try again.
    // This update should be rejected because of duplicated
    // address.
    ASSERT_NO_THROW(host->setIdentifier("01:02:03:04:05:06", "hw-address"));
    ASSERT_THROW(hdsptr_->add(host), DuplicateEntry);

    // Modify address to avoid its duplication and make sure
    // we can now add the host.
    ASSERT_NO_THROW(host->setIPv4Reservation(IOAddress("192.0.2.3")));
    EXPECT_NO_THROW(hdsptr_->add(host));
}

void
GenericHostDataSourceTest::testAddr6AndPrefix() {
    // Make sure we have the pointer to the host data source.
    ASSERT_TRUE(hdsptr_);

    // Create a host reservations with prefix reservation (prefix = true)
    HostPtr host = HostDataSourceUtils::initializeHost6("2001:db8::1", Host::IDENT_DUID, true);

    // Create IPv6 reservation (for an address) and add it to the host
    IPv6Resrv resv(IPv6Resrv::TYPE_NA, IOAddress("2001:db8::2"), 128);
    host->addReservation(resv);

    // Add this reservation
    ASSERT_NO_THROW(hdsptr_->add(host));

    // Get this host by DUID
    ConstHostPtr from_hds =
        hdsptr_->get6(host->getIPv6SubnetID(), Host::IDENT_DUID,
                      &host->getIdentifier()[0], host->getIdentifier().size());

    // Make sure we got something back
    ASSERT_TRUE(from_hds);

    // Check if reservations are the same
    HostDataSourceUtils::compareReservations6(host->getIPv6Reservations(),
                         from_hds->getIPv6Reservations());
}

void
GenericHostDataSourceTest::testMultipleReservations() {
    // Make sure we have the pointer to the host data source.
    ASSERT_TRUE(hdsptr_);
    uint8_t len = 128;

    HostPtr host = HostDataSourceUtils::initializeHost6("2001:db8::1", Host::IDENT_DUID, false);

    // Add some reservations
    IPv6Resrv resv1(IPv6Resrv::TYPE_NA, IOAddress("2001:db8::6"), len);
    IPv6Resrv resv2(IPv6Resrv::TYPE_NA, IOAddress("2001:db8::7"), len);
    IPv6Resrv resv3(IPv6Resrv::TYPE_NA, IOAddress("2001:db8::8"), len);
    IPv6Resrv resv4(IPv6Resrv::TYPE_NA, IOAddress("2001:db8::9"), len);

    host->addReservation(resv1);
    host->addReservation(resv2);
    host->addReservation(resv3);
    host->addReservation(resv4);

    ASSERT_NO_THROW(hdsptr_->add(host));

    ConstHostPtr from_hds = hdsptr_->get6(IOAddress("2001:db8::1"), len);

    // Make sure we got something back
    ASSERT_TRUE(from_hds);

    // Check if hosts are the same
    HostDataSourceUtils::compareHosts(host, from_hds);
}

void
GenericHostDataSourceTest::testMultipleReservationsDifferentOrder() {
    // Make sure we have the pointer to the host data source.
    ASSERT_TRUE(hdsptr_);
    uint8_t len = 128;

    HostPtr host1 = HostDataSourceUtils::initializeHost6("2001:db8::1",
                                         Host::IDENT_DUID, false, "key##1");
    HostPtr host2 = HostDataSourceUtils::initializeHost6("2001:db8::1",
                                         Host::IDENT_DUID, false, "key##1");

    // Add some reservations
    IPv6Resrv resv1(IPv6Resrv::TYPE_NA, IOAddress("2001:db8::6"), len);
    IPv6Resrv resv2(IPv6Resrv::TYPE_NA, IOAddress("2001:db8::7"), len);
    IPv6Resrv resv3(IPv6Resrv::TYPE_NA, IOAddress("2001:db8::8"), len);
    IPv6Resrv resv4(IPv6Resrv::TYPE_NA, IOAddress("2001:db8::9"), len);

    host1->addReservation(resv1);
    host1->addReservation(resv2);
    host1->addReservation(resv3);
    host1->addReservation(resv4);

    host2->addReservation(resv4);
    host2->addReservation(resv3);
    host2->addReservation(resv2);
    host2->addReservation(resv1);

    // Check if reservations are the same
    HostDataSourceUtils::compareReservations6(host1->getIPv6Reservations(),
                                              host2->getIPv6Reservations());
}

void
GenericHostDataSourceTest::testOptionsReservations4(const bool formatted,
                                                    ConstElementPtr user_context) {
    HostPtr host = HostDataSourceUtils::initializeHost4("192.0.2.5", Host::IDENT_HWADDR);
    // Add a bunch of DHCPv4 and DHCPv6 options for the host.
    ASSERT_NO_THROW(addTestOptions(host, formatted, DHCP4_ONLY, user_context));
    // Insert host and the options into respective tables.
    ASSERT_NO_THROW(hdsptr_->add(host));
    // Subnet id will be used in queries to the database.
    SubnetID subnet_id = host->getIPv4SubnetID();

    // getAll4(subnet_id)
    ConstHostCollection hosts_by_subnet = hdsptr_->getAll4(subnet_id);
    ASSERT_EQ(1, hosts_by_subnet.size());
    ASSERT_NO_FATAL_FAILURE(HostDataSourceUtils::compareHosts(host, *hosts_by_subnet.begin()));

    // getAll4(address)
    ConstHostCollection hosts_by_addr =
        hdsptr_->getAll4(host->getIPv4Reservation());
    ASSERT_EQ(1, hosts_by_addr.size());
    ASSERT_NO_FATAL_FAILURE(HostDataSourceUtils::compareHosts(host, *hosts_by_addr.begin()));

    // get4(subnet_id, identifier_type, identifier, identifier_size)
    ConstHostPtr host_by_id =
        hdsptr_->get4(subnet_id, host->getIdentifierType(),
                      &host->getIdentifier()[0], host->getIdentifier().size());
    ASSERT_NO_FATAL_FAILURE(HostDataSourceUtils::compareHosts(host, host_by_id));

    // get4(subnet_id, address)
    ConstHostPtr host_by_addr =
        hdsptr_->get4(subnet_id, IOAddress("192.0.2.5"));
    ASSERT_NO_FATAL_FAILURE(HostDataSourceUtils::compareHosts(host, host_by_addr));
}

void
GenericHostDataSourceTest::testOptionsReservations6(const bool formatted,
                                                    ConstElementPtr user_context) {
    HostPtr host = HostDataSourceUtils::initializeHost6("2001:db8::1", Host::IDENT_DUID, false);
    // Add a bunch of DHCPv4 and DHCPv6 options for the host.
    ASSERT_NO_THROW(addTestOptions(host, formatted, DHCP6_ONLY, user_context));
    // Insert host, options and IPv6 reservations into respective tables.
    ASSERT_NO_THROW(hdsptr_->add(host));
    // Subnet id will be used in queries to the database.
    SubnetID subnet_id = host->getIPv6SubnetID();

    // get6(subnet_id, identifier_type, identifier, identifier_size)
    ConstHostPtr host_by_id =
        hdsptr_->get6(subnet_id, host->getIdentifierType(),
                      &host->getIdentifier()[0], host->getIdentifier().size());
    ASSERT_NO_FATAL_FAILURE(HostDataSourceUtils::compareHosts(host, host_by_id));

    // get6(address, prefix_len)
    ConstHostPtr host_by_addr = hdsptr_->get6(IOAddress("2001:db8::1"), 128);
    ASSERT_NO_FATAL_FAILURE(HostDataSourceUtils::compareHosts(host, host_by_addr));
}

void
GenericHostDataSourceTest::testOptionsReservations46(const bool formatted) {
    HostPtr host = HostDataSourceUtils::initializeHost6("2001:db8::1", Host::IDENT_HWADDR, false);

    // Add a bunch of DHCPv4 and DHCPv6 options for the host.
    ASSERT_NO_THROW(addTestOptions(host, formatted, DHCP4_AND_DHCP6));
    // Insert host, options and IPv6 reservations into respective tables.
    ASSERT_NO_THROW(hdsptr_->add(host));
    // Subnet id will be used in queries to the database.
    SubnetID subnet_id = host->getIPv6SubnetID();

    // getAll6(subnet_id)
    ConstHostCollection hosts_by_subnet = hdsptr_->getAll6(subnet_id);
    EXPECT_EQ(1, hosts_by_subnet.size());
    // Don't compare as getAll6() returns the v6 part only.

    // getAll(identifier_type, identifier, identifier_size)
    ConstHostCollection hosts_by_id =
        hdsptr_->getAll(host->getIdentifierType(), &host->getIdentifier()[0],
                        host->getIdentifier().size());
    ASSERT_EQ(1, hosts_by_id.size());
    ASSERT_NO_FATAL_FAILURE(HostDataSourceUtils::compareHosts(host, *hosts_by_id.begin()));
}

void
GenericHostDataSourceTest::testMultipleClientClasses4() {
    ASSERT_TRUE(hdsptr_);

    // Create the Host object.
    HostPtr host = HostDataSourceUtils::initializeHost4("192.0.2.5", Host::IDENT_HWADDR);

    // Add v4 classes to the host.
    for (int i = 0; i < 4; ++i) {
        std::ostringstream os;
        os << "class4_" << i;
        host->addClientClass4(os.str());
    }

    // Add the host.
    ASSERT_NO_THROW(hdsptr_->add(host));

    // Subnet id will be used in queries to the database.
    SubnetID subnet_id = host->getIPv4SubnetID();

    // Fetch the host via:
    // getAll(const Host::IdentifierType, const uint8_t* identifier_begin,
    //       const size_t identifier_len) const;
    ConstHostCollection hosts_by_id =
        hdsptr_->getAll(host->getIdentifierType(), &host->getIdentifier()[0],
                        host->getIdentifier().size());
    ASSERT_EQ(1, hosts_by_id.size());
    ASSERT_NO_FATAL_FAILURE(HostDataSourceUtils::compareHosts(host, *hosts_by_id.begin()));

    // Fetch the host via
    // getAll4(const asiolink::IOAddress& address) const;
    hosts_by_id = hdsptr_->getAll4(IOAddress("192.0.2.5"));
    ASSERT_EQ(1, hosts_by_id.size());
    ASSERT_NO_FATAL_FAILURE(HostDataSourceUtils::compareHosts(host, *hosts_by_id.begin()));

    // Fetch the host via
    // get4(const SubnetID& subnet_id, const Host::IdentifierType&
    // identifier_type,
    //     const uint8_t* identifier_begin, const size_t identifier_len) const;
    ConstHostPtr from_hds =
        hdsptr_->get4(subnet_id, host->getIdentifierType(),
                      &host->getIdentifier()[0], host->getIdentifier().size());
    ASSERT_TRUE(from_hds);
    ASSERT_NO_FATAL_FAILURE(HostDataSourceUtils::compareHosts(host, from_hds));

    // Fetch the host via:
    // get4(const SubnetID& subnet_id, const asiolink::IOAddress& address) const;
    from_hds = hdsptr_->get4(subnet_id, IOAddress("192.0.2.5"));
    ASSERT_TRUE(from_hds);
    ASSERT_NO_FATAL_FAILURE(HostDataSourceUtils::compareHosts(host, from_hds));
}

void
GenericHostDataSourceTest::testMultipleClientClasses6() {
    ASSERT_TRUE(hdsptr_);

    // Create the Host object.
    HostPtr host = HostDataSourceUtils::initializeHost6("2001:db8::1", Host::IDENT_HWADDR, false);

    // Add v6 classes to the host.
    for (int i = 0; i < 4; ++i) {
        std::ostringstream os;
        os << "class6_" << i;
        host->addClientClass6(os.str());
    }

    // Add the host.
    ASSERT_NO_THROW(hdsptr_->add(host));

    // Subnet id will be used in queries to the database.
    SubnetID subnet_id = host->getIPv6SubnetID();

    // getAll(const Host::IdentifierType& identifier_type,
    //        const uint8_t* identifier_begin,
    //        const size_t identifier_len) const;
    ConstHostCollection hosts_by_id =
        hdsptr_->getAll(host->getIdentifierType(), &host->getIdentifier()[0],
                        host->getIdentifier().size());
    ASSERT_EQ(1, hosts_by_id.size());
    ASSERT_NO_FATAL_FAILURE(HostDataSourceUtils::compareHosts(host, *hosts_by_id.begin()));

    // Fetch the host via:
    // get6(const SubnetID& subnet_id, const Host::IdentifierType&
    // identifier_type,
    //     const uint8_t* identifier_begin, const size_t identifier_len) const;
    ConstHostPtr from_hds =
        hdsptr_->get6(subnet_id, Host::IDENT_HWADDR, &host->getIdentifier()[0],
                      host->getIdentifier().size());
    ASSERT_TRUE(from_hds);
    ASSERT_NO_FATAL_FAILURE(HostDataSourceUtils::compareHosts(host, from_hds));

    // Fetch the host via:
    // get6(const asiolink::IOAddress& prefix, const uint8_t prefix_len) const;
    from_hds = hdsptr_->get6(IOAddress("2001:db8::1"), 128);
    ASSERT_TRUE(from_hds);
    ASSERT_NO_FATAL_FAILURE(HostDataSourceUtils::compareHosts(host, from_hds));
}

void
GenericHostDataSourceTest::testMultipleClientClassesBoth() {
    /// Add host reservation with a multiple v4 and v6 client-classes,
    /// retrieve it and make sure that all client classes are retrieved
    /// properly.
    ASSERT_TRUE(hdsptr_);

    // Create the Host object.
    HostPtr host = HostDataSourceUtils::initializeHost6("2001:db8::1", Host::IDENT_HWADDR, false);

    // Add v4 classes to the host.
    for (int i = 0; i < 4; ++i) {
        std::ostringstream os;
        os << "class4_" << i;
        host->addClientClass4(os.str());
    }

    // Add v6 classes to the host.
    for (int i = 0; i < 4; ++i) {
        std::ostringstream os;
        os << "class6_" << i;
        host->addClientClass6(os.str());
    }

    // Add the host.
    ASSERT_NO_THROW(hdsptr_->add(host));

    // Subnet id will be used in queries to the database.
    SubnetID subnet_id = host->getIPv6SubnetID();

    // Fetch the host from the source.
    ConstHostPtr from_hds =
        hdsptr_->get6(subnet_id, Host::IDENT_HWADDR, &host->getIdentifier()[0],
                      host->getIdentifier().size());
    ASSERT_TRUE(from_hds);

    // Verify they match.
    ASSERT_NO_FATAL_FAILURE(HostDataSourceUtils::compareHosts(host, from_hds));
}

void
GenericHostDataSourceTest::testMessageFields4() {
    ASSERT_TRUE(hdsptr_);

    // Create the Host object.
    HostPtr host = HostDataSourceUtils::initializeHost4("192.0.2.5", Host::IDENT_HWADDR);
    // And assign values for DHCPv4 message fields.
    ASSERT_NO_THROW({
        host->setNextServer(IOAddress("10.1.1.1"));
        host->setServerHostname("server-name.example.org");
        host->setBootFileName("bootfile.efi");
    });

    // Add the host.
    ASSERT_NO_THROW(hdsptr_->add(host));

    // Subnet id will be used in queries to the database.
    SubnetID subnet_id = host->getIPv4SubnetID();

    // Fetch the host via:
    // getAll(const Host::IdentifierType, const uint8_t* identifier_begin,
    //       const size_t identifier_len) const;
    ConstHostCollection hosts_by_id =
        hdsptr_->getAll(host->getIdentifierType(), &host->getIdentifier()[0],
                        host->getIdentifier().size());
    ASSERT_EQ(1, hosts_by_id.size());
    ASSERT_NO_FATAL_FAILURE(HostDataSourceUtils::compareHosts(host, *hosts_by_id.begin()));

    // Fetch the host via
    // getAll4(const asiolink::IOAddress& address) const;
    hosts_by_id = hdsptr_->getAll4(IOAddress("192.0.2.5"));
    ASSERT_EQ(1, hosts_by_id.size());
    ASSERT_NO_FATAL_FAILURE(HostDataSourceUtils::compareHosts(host, *hosts_by_id.begin()));

    // Fetch the host via
    // get4(const SubnetID& subnet_id, const Host::IdentifierType&
    // identifier_type,
    //     const uint8_t* identifier_begin, const size_t identifier_len) const;
    ConstHostPtr from_hds =
        hdsptr_->get4(subnet_id, host->getIdentifierType(),
                      &host->getIdentifier()[0], host->getIdentifier().size());
    ASSERT_TRUE(from_hds);
    ASSERT_NO_FATAL_FAILURE(HostDataSourceUtils::compareHosts(host, from_hds));

    // Fetch the host via:
    // get4(const SubnetID& subnet_id, const asiolink::IOAddress& address) const;
    from_hds = hdsptr_->get4(subnet_id, IOAddress("192.0.2.5"));
    ASSERT_TRUE(from_hds);
    ASSERT_NO_FATAL_FAILURE(HostDataSourceUtils::compareHosts(host, from_hds));
}

void
GenericHostDataSourceTest::stressTest(unsigned int nOfHosts /* = 0xfffdU */) {
    // Make sure we have a pointer to the host data source.
    ASSERT_TRUE(hdsptr_);

    // Make sure the variable part of the generated address fits in a 16-bit
    // field.
    ASSERT_LE(nOfHosts, 0xfffdU);

    // Create hosts.
    std::vector<HostPtr> hosts;
    hosts.reserve(nOfHosts);
    for (unsigned int i = 0x0001U; i < 0x0001U + nOfHosts; ++i) {
        /// @todo: Check if this is written in hexadecimal format.
        std::stringstream ss;
        std::string n_host;
        ss << std::hex << i;
        ss >> n_host;

        const std::string prefix = std::string("2001:db8::") + n_host;
        hosts.push_back(HostDataSourceUtils::initializeHost6(prefix,
                        Host::IDENT_HWADDR, false, "key##1"));

        IPv6ResrvRange range = hosts.back()->getIPv6Reservations();
        ASSERT_EQ(1, std::distance(range.first, range.second));
        EXPECT_TRUE(HostDataSourceUtils::reservationExists
                    (IPv6Resrv(IPv6Resrv::TYPE_NA, IOAddress(prefix)), range));
    }
    const size_t hosts_size = hosts.size();

    std::cout << "Starting to add hosts..." << std::endl;
    struct timespec start, end;
    start = (struct timespec){0, 0};
    end = (struct timespec){0, 0};
    clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
    for (std::vector<HostPtr>::const_iterator it = hosts.begin();
         it != hosts.end(); it++) {
        ASSERT_NO_THROW(hdsptr_->add(*it));
    }
    clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
    double s = static_cast<double>(end.tv_sec - start.tv_sec) +
               static_cast<double>(end.tv_nsec - start.tv_nsec) / 1e9;
    std::cout << "Adding " << hosts_size
              << (hosts_size == 1 ? " host" : " hosts") << " took "
              << std::fixed << std::setprecision(2) << s << " seconds."
              << std::endl;

    // And then try to retrieve them back.
    std::cout << "Starting to retrieve hosts..." << std::endl;
    start = (struct timespec){0, 0};
    end = (struct timespec){0, 0};
    clock_gettime(CLOCK_THREAD_CPUTIME_ID, &start);
    for (std::vector<HostPtr>::const_iterator it = hosts.begin();
         it != hosts.end(); it++) {
        IPv6ResrvRange range = (*it)->getIPv6Reservations();
        // This get6() call is particularly useful to test because it involves a
        // subquery for MySQL and PostgreSQL and two separate queries for
        // Cassandra.
        ConstHostPtr from_hds =
            hdsptr_->get6(range.first->second.getPrefix(), 128);
        ASSERT_TRUE(from_hds);
        HostDataSourceUtils::compareHosts(*it, from_hds);
    }
    clock_gettime(CLOCK_THREAD_CPUTIME_ID, &end);
    s = static_cast<double>(end.tv_sec - start.tv_sec) +
        static_cast<double>(end.tv_nsec - start.tv_nsec) / 1e9;
    std::cout << "Retrieving " << hosts_size
              << (hosts_size == 1 ? " host" : " hosts") << " took "
              << std::fixed << std::setprecision(2) << s << " seconds."
              << std::endl;
}

void
GenericHostDataSourceTest::testDeleteByAddr4() {
    // Make sure we have a pointer to the host data source.
    ASSERT_TRUE(hdsptr_);

    // Let's create a v4 host...
    HostPtr host1 = HostDataSourceUtils::initializeHost4("192.0.2.1", Host::IDENT_HWADDR);
    SubnetID subnet1 = host1->getIPv4SubnetID();

    // ... and add it to the data source.
    ASSERT_NO_THROW(hdsptr_->add(host1));

    // And then try to retrieve it back.
    ConstHostPtr before = hdsptr_->get4(subnet1, IOAddress("192.0.2.1"));

    // Now try to delete it: del(subnet-id, addr4)
    EXPECT_TRUE(hdsptr_->del(subnet1, IOAddress("192.0.2.1")));

    // Check if it's still there.
    ConstHostPtr after = hdsptr_->get4(subnet1, IOAddress("192.0.2.1"));

    // Make sure the host was there before...
    EXPECT_TRUE(before);

    // ... and that it's gone after deletion.
    EXPECT_FALSE(after);

    // An attempt to delete it should not cause an exception. It
    // should return false.
    bool result = false;
    EXPECT_NO_THROW(result = hdsptr_->del(subnet1, IOAddress("192.0.2.1")));
    EXPECT_FALSE(result);
}

void
GenericHostDataSourceTest::testDeleteById4() {
    // Make sure we have a pointer to the host data source.
    ASSERT_TRUE(hdsptr_);

    // Let's create a v4 host...
    HostPtr host1 = HostDataSourceUtils::initializeHost4("192.0.2.1", Host::IDENT_HWADDR);
    SubnetID subnet1 = host1->getIPv4SubnetID();

    // ... and add it to the data source.
    ASSERT_NO_THROW(hdsptr_->add(host1));

    // And then try to retrieve it back.
    ConstHostPtr before = hdsptr_->get4(subnet1,
                                        host1->getIdentifierType(),
                                        &host1->getIdentifier()[0],
                                        host1->getIdentifier().size());

    // Now try to delete it: del4(subnet4-id, identifier-type, identifier)
    EXPECT_TRUE(hdsptr_->del4(subnet1, host1->getIdentifierType(),
                              &host1->getIdentifier()[0],
                              host1->getIdentifier().size()));

    // Check if it's still there.
    ConstHostPtr after = hdsptr_->get4(subnet1,
                                       host1->getIdentifierType(),
                                       &host1->getIdentifier()[0],
                                       host1->getIdentifier().size());

    // Make sure the host was there before...
    EXPECT_TRUE(before);

    // ... and that it's gone after deletion.
    EXPECT_FALSE(after);

    // An attempt to delete it should not cause an exception. It
    // should return false.
    bool result = false;
    EXPECT_NO_THROW(result = hdsptr_->del4(subnet1, host1->getIdentifierType(),
                                           &host1->getIdentifier()[0],
                                           host1->getIdentifier().size()));
    EXPECT_FALSE(result);
}

// Test checks when a IPv4 host with options is deleted that the options are
// deleted as well.
void
GenericHostDataSourceTest::testDeleteById4Options() {
    // Make sure we have a pointer to the host data source.
    ASSERT_TRUE(hdsptr_);

    // Let's create a v4 host...
    HostPtr host1 = HostDataSourceUtils::initializeHost4("192.0.2.1", Host::IDENT_HWADDR);
    // Add a bunch of DHCPv4 and DHCPv6 options for the host.
    ASSERT_NO_THROW(addTestOptions(host1, true, DHCP4_ONLY));
    // Insert host and the options into respective tables.

    SubnetID subnet1 = host1->getIPv4SubnetID();

    // ... and add it to the data source.
    ASSERT_NO_THROW(hdsptr_->add(host1));

    // There must be some options
    EXPECT_NE(0, countDBOptions4());

    // And then try to retrieve it back.
    ConstHostPtr before = hdsptr_->get4(subnet1,
                                        host1->getIdentifierType(),
                                        &host1->getIdentifier()[0],
                                        host1->getIdentifier().size());

    // Now try to delete it: del4(subnet4-id, identifier-type, identifier)
    EXPECT_TRUE(hdsptr_->del4(subnet1, host1->getIdentifierType(),
                              &host1->getIdentifier()[0],
                              host1->getIdentifier().size()));

    // Check if it's still there.
    ConstHostPtr after = hdsptr_->get4(subnet1,
                                       host1->getIdentifierType(),
                                       &host1->getIdentifier()[0],
                                       host1->getIdentifier().size());

    // Make sure the host was there before...
    EXPECT_TRUE(before);

    // ... and that it's gone after deletion.
    EXPECT_FALSE(after);

    // Check the options are indeed gone.
    EXPECT_EQ(0, countDBOptions4());

    // An attempt to delete it should not cause an exception. It
    // should return false.
    bool result = false;
    EXPECT_NO_THROW(result = hdsptr_->del4(subnet1, host1->getIdentifierType(),
                                           &host1->getIdentifier()[0],
                                           host1->getIdentifier().size()));
    EXPECT_FALSE(result);
}

void
GenericHostDataSourceTest::testDeleteById6() {
    // Make sure we have a pointer to the host data source.
    ASSERT_TRUE(hdsptr_);

    // Let's create a v6 host...
    HostPtr host1 = HostDataSourceUtils::initializeHost6("2001:db8::1",
                                         Host::IDENT_DUID, false, "key##1");
    SubnetID subnet1 = host1->getIPv6SubnetID();

    // ... and add it to the data source.
    ASSERT_NO_THROW(hdsptr_->add(host1));

    // And then try to retrieve it back.
    ConstHostPtr before = hdsptr_->get6(subnet1,
                                        host1->getIdentifierType(),
                                        &host1->getIdentifier()[0],
                                        host1->getIdentifier().size());

    // Now try to delete it: del4(subnet4-id, identifier-type, identifier)
    EXPECT_TRUE(hdsptr_->del6(subnet1, host1->getIdentifierType(),
                              &host1->getIdentifier()[0],
                              host1->getIdentifier().size()));

    // Check if it's still there.
    ConstHostPtr after = hdsptr_->get6(subnet1,
                                       host1->getIdentifierType(),
                                       &host1->getIdentifier()[0],
                                       host1->getIdentifier().size());

    // Make sure the host was there before...
    EXPECT_TRUE(before);

    // ... and that it's gone after deletion.
    EXPECT_FALSE(after);

    // An attempt to delete it should not cause an exception. It
    // should return false.
    bool result = false;
    EXPECT_NO_THROW(result = hdsptr_->del6(subnet1, host1->getIdentifierType(),
                                           &host1->getIdentifier()[0],
                                           host1->getIdentifier().size()));
    EXPECT_FALSE(result);
}

void
GenericHostDataSourceTest::testDeleteById6Options() {
    // Make sure we have a pointer to the host data source.
    ASSERT_TRUE(hdsptr_);

    // Let's create a v6 host...
    HostPtr host1 = HostDataSourceUtils::initializeHost6("2001:db8::1", Host::IDENT_DUID, false);
    SubnetID subnet1 = host1->getIPv6SubnetID();
    ASSERT_NO_THROW(addTestOptions(host1, true, DHCP6_ONLY));

    // ... and add it to the data source.
    ASSERT_NO_THROW(hdsptr_->add(host1));

    // Check that the options are stored...
    EXPECT_NE(0, countDBOptions6());

    // ... and so are v6 reservations.
    EXPECT_NE(0, countDBReservations6());

    // And then try to retrieve it back.
    ConstHostPtr before = hdsptr_->get6(subnet1,
                                        host1->getIdentifierType(),
                                        &host1->getIdentifier()[0],
                                        host1->getIdentifier().size());

    // Now try to delete it: del4(subnet4-id, identifier-type, identifier)
    EXPECT_TRUE(hdsptr_->del6(subnet1, host1->getIdentifierType(),
                              &host1->getIdentifier()[0],
                              host1->getIdentifier().size()));

    // Check if it's still there.
    ConstHostPtr after = hdsptr_->get6(subnet1,
                                       host1->getIdentifierType(),
                                       &host1->getIdentifier()[0],
                                       host1->getIdentifier().size());

    // Make sure the host was there before...
    EXPECT_TRUE(before);

    // ... and that it's gone after deletion.
    EXPECT_FALSE(after);

    // Check the options are indeed gone.
    EXPECT_EQ(0, countDBOptions6());

    // Check the options are indeed gone.
    EXPECT_EQ(0, countDBReservations6());

    // An attempt to delete it should not cause an exception. It
    // should return false.
    bool result = false;
    EXPECT_NO_THROW(result = hdsptr_->del6(subnet1, host1->getIdentifierType(),
                                           &host1->getIdentifier()[0],
                                           host1->getIdentifier().size()));
    EXPECT_FALSE(result);
}

void
GenericHostDataSourceTest::testMultipleHostsNoAddress4() {
    // Make sure we have a pointer to the host data source.
    ASSERT_TRUE(hdsptr_);

    // Create a host with zero IPv4 address.
    HostPtr host1 = HostDataSourceUtils::initializeHost4("0.0.0.0", Host::IDENT_HWADDR);
    host1->setIPv4SubnetID(1);
    host1->setIPv6SubnetID(SUBNET_ID_UNUSED);
    // Add the host to the database.
    ASSERT_NO_THROW(hdsptr_->add(host1));

    // An attempt to add this host again should fail due to client identifier
    // duplication.
    ASSERT_THROW(hdsptr_->add(host1), DuplicateEntry);

    // Create another host with zero IPv4 address. Adding this host to the
    // database should be successful because zero addresses are not counted
    // in the unique index.
    HostPtr host2 = HostDataSourceUtils::initializeHost4("0.0.0.0", Host::IDENT_HWADDR);
    host2->setIPv4SubnetID(1);
    host2->setIPv6SubnetID(SUBNET_ID_UNUSED);
    ASSERT_NO_THROW(hdsptr_->add(host2));
}

void
GenericHostDataSourceTest::testMultipleHosts6() {
    // Make sure we have a pointer to the host data source.
    ASSERT_TRUE(hdsptr_);

    // Create first host.
    HostPtr host1 = HostDataSourceUtils::initializeHost6("2001:db8::1", Host::IDENT_DUID, false);
    host1->setIPv4SubnetID(SUBNET_ID_UNUSED);
    host1->setIPv6SubnetID(1);
    // Add the host to the database.
    ASSERT_NO_THROW(hdsptr_->add(host1));

    // An attempt to add this host again should fail due to client identifier
    // duplication.
    ASSERT_THROW(hdsptr_->add(host1), DuplicateEntry);

    HostPtr host2 = HostDataSourceUtils::initializeHost6("2001:db8::2", Host::IDENT_DUID, false);
    host2->setIPv4SubnetID(SUBNET_ID_UNUSED);
    host2->setIPv6SubnetID(1);
    // Add the host to the database.
    ASSERT_NO_THROW(hdsptr_->add(host2));
}

}  // namespace test
}  // namespace dhcp
}  // namespace isc
