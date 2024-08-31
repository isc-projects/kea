// Copyright (C) 2015-2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <asiolink/addr_utilities.h>
#include <database/database_connection.h>
#include <database/db_exceptions.h>
#include <dhcp/dhcp6.h>
#include <dhcp/docsis3_option_defs.h>
#include <dhcp/libdhcp++.h>
#include <dhcp/option4_addrlst.h>
#include <dhcp/option6_addrlst.h>
#include <dhcp/option_int.h>
#include <dhcp/option_string.h>
#include <dhcp/option_vendor.h>
#include <dhcpsrv/host_data_source_factory.h>
#include <dhcpsrv/testutils/generic_host_data_source_unittest.h>
#include <dhcpsrv/testutils/host_data_source_utils.h>
#include <dhcpsrv/testutils/test_utils.h>
#include <database/testutils/schema.h>
#include <testutils/gtest_utils.h>
#include <util/buffer.h>

#include <boost/algorithm/string/case_conv.hpp>
#include <boost/algorithm/string/replace.hpp>

#include <gtest/gtest.h>

#include <sstream>
#include <string>

using namespace std;
using namespace isc::asiolink;
using namespace isc::db;
using namespace isc::db::test;
using namespace isc::util;
using namespace isc::data;
namespace ph = std::placeholders;

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
                                       true, false, formatted, "my-boot-file");
        desc.setContext(user_context);
        opts->add(desc, DHCP4_OPTION_SPACE);
        opts->add(createOption<OptionUint8>(Option::V4, DHO_DEFAULT_IP_TTL,
                                            false, false, formatted, 64),
                  DHCP4_OPTION_SPACE);
        opts->add(createOption<OptionUint32>(Option::V4, 1, false, false,
                                             formatted, 312131),
                  "vendor-encapsulated-options-space");
        opts->add(createAddressOption<Option4AddrLst>(254, false, false,
                                                      formatted, "192.0.2.3"),
                  DHCP4_OPTION_SPACE);
        opts->add(createEmptyOption(Option::V4, 1, true, false), "isc");
        opts->add(createAddressOption<Option4AddrLst>(2, false, false,
                                                      formatted, "10.0.0.5",
                                                      "10.0.0.3", "10.0.3.4"),
                  "isc");
        auto def = LibDHCP::getLastResortOptionDef(DHCP4_OPTION_SPACE,
                                                   DHO_VENDOR_ENCAPSULATED_OPTIONS);
        opts->add(OptionDescriptor(def->optionFactory(Option::V4,
                                                      DHO_VENDOR_ENCAPSULATED_OPTIONS,
                                                      OptionBuffer()),
                                   true, false), DHCP4_OPTION_SPACE);

        // Add definitions for DHCPv4 non-standard options.
        defs.addItem(OptionDefinitionPtr(new OptionDefinition(
                         "vendor-encapsulated-1", 1,
                         "vendor-encapsulated-options-space", "uint32")));
        defs.addItem(OptionDefinitionPtr(new OptionDefinition(
                         "option-254", 254, DHCP4_OPTION_SPACE,
                         "ipv4-address", true)));
        defs.addItem(OptionDefinitionPtr(new OptionDefinition("isc-1", 1, "isc", "empty")));
        defs.addItem(OptionDefinitionPtr(new OptionDefinition("isc-2", 2, "isc", "ipv4-address", true)));
    }

    if ((added_options == DHCP6_ONLY) || (added_options == DHCP4_AND_DHCP6)) {
        // Add DHCPv6 options.
        CfgOptionPtr opts = host->getCfgOption6();
        OptionDescriptor desc =
            createOption<OptionString>(Option::V6, D6O_BOOTFILE_URL,
                                       true, false, formatted, "my-boot-file");
        desc.setContext(user_context);
        opts->add(desc, DHCP6_OPTION_SPACE);
        opts->add(createOption<OptionUint32>(Option::V6, D6O_INFORMATION_REFRESH_TIME,
                                             false, false, formatted, 3600),
                  DHCP6_OPTION_SPACE);
        opts->add(createVendorOption(Option::V6, false, false, formatted, 2495),
                  DHCP6_OPTION_SPACE);
        opts->add(createAddressOption<Option6AddrLst>(1024, false, false,
                                                      formatted, "2001:db8:1::1"),
                  DHCP6_OPTION_SPACE);
        opts->add(createEmptyOption(Option::V6, 1, true, false), "isc2");
        opts->add(createAddressOption<Option6AddrLst>(2, false, false,
                                                      formatted, "3000::1",
                                                      "3000::2", "3000::3"),
                  "isc2");

        desc = createOption<OptionString>(Option::V6, DOCSIS3_V6_TFTP_SERVERS,
                                          true, false, true, "3000:1::234");
        opts->add(desc, "vendor-4491");

        // Add definitions for DHCPv6 non-standard options.
        defs.addItem(OptionDefinitionPtr(new OptionDefinition(
                         "option-1024", 1024, DHCP6_OPTION_SPACE,
                         "ipv6-address", true)));
        defs.addItem(OptionDefinitionPtr(new OptionDefinition("option-1", 1, "isc2", "empty")));
        defs.addItem(OptionDefinitionPtr(new OptionDefinition("option-2", 2, "isc2", "ipv6-address", true)));
    }

    // Register created "runtime" option definitions. They will be used by a
    // host data source to convert option data into the appropriate option
    // classes when the options are retrieved.
    LibDHCP::setRuntimeOptionDefs(defs);
}

void
GenericHostDataSourceTest::addIPv6Address(const HostPtr& host, const std::string& address) const {
    host->addReservation(IPv6Resrv(IPv6Resrv::TYPE_NA, IOAddress(address)));
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
    ASSERT_NE(hdsptr_->getParameters(), DatabaseConnection::ParameterMap());

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

    HostDataSourceUtils::compareHosts(host1, from_hds[0]);
    HostDataSourceUtils::compareHosts(host2, from_hds[1]);
    HostDataSourceUtils::compareHosts(host3, from_hds[2]);
    HostDataSourceUtils::compareHosts(host4, from_hds[3]);
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

    HostDataSourceUtils::compareHosts(host1, from_hds[0]);
    HostDataSourceUtils::compareHosts(host2, from_hds[1]);
    HostDataSourceUtils::compareHosts(host3, from_hds[2]);
    HostDataSourceUtils::compareHosts(host4, from_hds[3]);
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
    for (auto const& host : from_hds) {
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
                                   true, false, false, "my-boot-file");
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
    for (auto const& host : from_hds) {
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
                                   true, false, true, "my-boot-file");
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
    for (auto const& host : from_hds) {
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
    // the second should return one host.

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
                                       true, false, false, "my-boot-file");
        opts->add(desc, DHCP4_OPTION_SPACE);
        opts->add(createOption<OptionUint8>(Option::V4, DHO_DEFAULT_IP_TTL,
                                            false, true, false, 64 + i),
                  DHCP4_OPTION_SPACE);
        opts->add(createEmptyOption(Option::V4, 1, true, true), "isc");

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
                                       true, false, false, "my-boot-file");
        opts->add(desc, DHCP6_OPTION_SPACE);
        opts->add(createOption<OptionUint32>(Option::V6,
                                             D6O_INFORMATION_REFRESH_TIME,
                                             false, true, false, 3600 + i),
                  DHCP6_OPTION_SPACE);
        opts->add(createAddressOption<Option6AddrLst>(D6O_SIP_SERVERS_ADDR,
                                                      false, false, false,
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
    // MySql and PostgreSql) so the hosts must be sorted by host identifier
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
    // sizes (3, then 2).

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
    // MySql and PostgreSql) so the hosts must be sorted by host identifier
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
    // MySql and PostgreSql) so the hosts must be sorted by host identifier
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
    // sizes (3, then 2).

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
    // MySql and PostgreSql) so the hosts must be sorted by host identifier
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
    // MySql and PostgreSql) so the hosts must be sorted by host identifier
    std::sort(all_pages.begin(), all_pages.end(), compareHostsIdentifier);

    // Verify we got what we expected.
    for (size_t i = 0; i < 5; ++i) {
        HostDataSourceUtils::compareHosts(hosts[i * 2 + 1], all_pages[i]);
    }
}

void
GenericHostDataSourceTest::testGetPage4All() {
    // From the ticket: add one host to subnet1, add one host to subnet2.
    // repeat 4 times. Get all hosts with page size 3.
    // Make sure all hosts are returned and in expected page
    // sizes (3, 3, then 2).

    // Make sure we have a pointer to the host data source.
    ASSERT_TRUE(hdsptr_);

    // Let's create some hosts...
    const Host::IdentifierType& id = Host::IDENT_HWADDR;
    IOAddress addr("192.0.2.0");
    SubnetID subnet4(4);
    SubnetID subnet6(6);
    vector<HostPtr> hosts;
    for (unsigned i = 0; i < 8; ++i) {
        addr = IOAddress::increase(addr);

        HostPtr host = HostDataSourceUtils::initializeHost4(addr.toText(), id);
        host->setIPv4SubnetID(subnet4 + (i & 1));
        host->setIPv6SubnetID(subnet6 + (i & 1));

        ASSERT_NO_THROW(hdsptr_->add(host));
        hosts.push_back(host);
    }

    // Get first page.
    size_t idx(1);
    uint64_t host_id(0);
    HostPageSize page_size(3);
    ConstHostCollection page;
    ConstHostCollection all_pages;
    ASSERT_NO_THROW(page = hdsptr_->getPage4(idx, host_id, page_size));
    ASSERT_EQ(3, page.size());
    host_id = page[2]->getHostId();
    ASSERT_NE(0, host_id);

    std::copy(page.begin(), page.end(), std::back_inserter(all_pages));

    // Get second page.
    ASSERT_NO_THROW(page = hdsptr_->getPage4(idx, host_id, page_size));
    ASSERT_EQ(3, page.size());
    host_id = page[2]->getHostId();

    std::copy(page.begin(), page.end(), std::back_inserter(all_pages));

    // Get last page.
    ASSERT_NO_THROW(page = hdsptr_->getPage4(idx, host_id, page_size));
    ASSERT_EQ(2, page.size());
    host_id = page[1]->getHostId();

    std::copy(page.begin(), page.end(), std::back_inserter(all_pages));

    // Verify we have everything.
    ASSERT_NO_THROW(page = hdsptr_->getPage4(idx, host_id, page_size));
    ASSERT_EQ(0, page.size());

    // hosts are sorted by generated host_id (which is an auto increment for
    // MySql and PostgreSql) so the hosts must be sorted by host identifier
    std::sort(all_pages.begin(), all_pages.end(), compareHostsIdentifier);

    // Verify we got what we expected.
    for (size_t i = 0; i < 8; ++i) {
        HostDataSourceUtils::compareHosts(hosts[i], all_pages[i]);
    }
}

void
GenericHostDataSourceTest::testGetPage6All() {
    // From the ticket: add one host to subnet1, add one host to subnet2.
    // repeat 4 times. Get all hosts with page size 3.
    // Make sure all hosts are returned and in expected page
    // sizes (3, 3, then 2).

    // Make sure we have a pointer to the host data source.
    ASSERT_TRUE(hdsptr_);

    // Let's create some hosts...
    const Host::IdentifierType& id = Host::IDENT_DUID;
    IOAddress addr("2001:db8:1::");
    SubnetID subnet4(4);
    SubnetID subnet6(6);
    vector<HostPtr> hosts;
    for (unsigned i = 0; i < 8; ++i) {
        addr = IOAddress::increase(addr);

        HostPtr host = HostDataSourceUtils::initializeHost6(addr.toText(), id, false);
        host->setIPv4SubnetID(subnet4 + (i & 1));
        host->setIPv6SubnetID(subnet6 + (i & 1));

        ASSERT_NO_THROW(hdsptr_->add(host));
        hosts.push_back(host);
    }

    // Get first page.
    size_t idx(1);
    uint64_t host_id(0);
    HostPageSize page_size(3);
    ConstHostCollection page;
    ConstHostCollection all_pages;
    ASSERT_NO_THROW(page = hdsptr_->getPage6(idx, host_id, page_size));
    ASSERT_EQ(3, page.size());
    host_id = page[2]->getHostId();
    ASSERT_NE(0, host_id);

    std::copy(page.begin(), page.end(), std::back_inserter(all_pages));

    // Get second page.
    ASSERT_NO_THROW(page = hdsptr_->getPage6(idx, host_id, page_size));
    ASSERT_EQ(3, page.size());
    host_id = page[2]->getHostId();

    std::copy(page.begin(), page.end(), std::back_inserter(all_pages));

    // Get last page.
    ASSERT_NO_THROW(page = hdsptr_->getPage6(idx, host_id, page_size));
    ASSERT_EQ(2, page.size());
    host_id = page[1]->getHostId();

    std::copy(page.begin(), page.end(), std::back_inserter(all_pages));

    // Verify we have everything.
    ASSERT_NO_THROW(page = hdsptr_->getPage6(idx, host_id, page_size));
    ASSERT_EQ(0, page.size());

    // hosts are sorted by generated host_id (which is an auto increment for
    // MySql and PostgreSql) so the hosts must be sorted by host identifier
    std::sort(all_pages.begin(), all_pages.end(), compareHostsIdentifier);

    // Verify we got what we expected.
    for (size_t i = 0; i < 8; ++i) {
        HostDataSourceUtils::compareHosts(hosts[i], all_pages[i]);
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
    for (auto const& it : hosts) {
        // Try to add both of the to the host data source.
        ASSERT_NO_THROW(hdsptr_->add(it));
    }

    // And finally retrieve them one by one and check
    // if the hostname was preserved.
    for (auto const& it : hosts) {
        ConstHostPtr from_hds;
        ASSERT_NO_THROW(from_hds = hdsptr_->get4(it->getIPv4SubnetID(),
                                                 it->getIPv4Reservation()));
        ASSERT_TRUE(from_hds);

        EXPECT_EQ(it->getHostname(), from_hds->getHostname());
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
    for (auto const& it : all_by_addr) {
        EXPECT_EQ(IOAddress("192.0.2.1"), it->getIPv4Reservation());
        EXPECT_EQ(1000 + i++, it->getIPv4SubnetID());
    }

    // Finally, check that the hosts can be retrieved by HW address or DUID
    ConstHostCollection all_by_id = hdsptr_->getAll(
        id, &host->getIdentifier()[0], host->getIdentifier().size());
    ASSERT_EQ(subnets, all_by_id.size());

    // Check that the returned values are as expected.
    i = 0;
    for (auto const& it : all_by_id) {
        EXPECT_EQ(IOAddress("192.0.2.1"), it->getIPv4Reservation());
        EXPECT_EQ(1000 + i++, it->getIPv4SubnetID());
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
    IOAddress current_address("2001:db8::");
    ASSERT_LT(subnets, std::numeric_limits<uint16_t>::max()) << "Too many subnets. Broken test?";
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
        current_address = offsetAddress(current_address, (uint128_t(1) << 80));
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
    for (auto const& it : all_by_id) {
        EXPECT_EQ(IOAddress("0.0.0.0"), it->getIPv4Reservation());
        EXPECT_EQ(1000 + i++, it->getIPv6SubnetID());
    }
}

void
GenericHostDataSourceTest::testGetByIPv6(Host::IdentifierType id, bool prefix) {
    // Make sure we have a pointer to the host data source.
    ASSERT_TRUE(hdsptr_);

    // Let's create a couple of hosts...
    HostPtr host1 = HostDataSourceUtils::initializeHost6("2001:db8:1::",
                                                        id, prefix, "key##1");
    HostPtr host2 = HostDataSourceUtils::initializeHost6("2001:db8:2::",
                                                        id, prefix, "key##2");
    HostPtr host3 = HostDataSourceUtils::initializeHost6("2001:db8:3::",
                                                        id, prefix, "key##3");
    HostPtr host4 = HostDataSourceUtils::initializeHost6("2001:db8:4::",
                                                        id, prefix, "key##4");

    // ... and add them to the data source.
    ASSERT_NO_THROW(hdsptr_->add(host1));
    ASSERT_NO_THROW(hdsptr_->add(host2));
    ASSERT_NO_THROW(hdsptr_->add(host3));
    ASSERT_NO_THROW(hdsptr_->add(host4));

    // Are we talking about addresses or prefixes?
    uint8_t len = prefix ? 64 : 128;

    // And then try to retrieve them back.
    ConstHostPtr from_hds1 = hdsptr_->get6(IOAddress("2001:db8:1::"), len);
    ConstHostPtr from_hds2 = hdsptr_->get6(IOAddress("2001:db8:2::"), len);
    ConstHostPtr from_hds3 = hdsptr_->get6(IOAddress("2001:db8:3::"), len);
    ConstHostPtr from_hds4 = hdsptr_->get6(IOAddress("2001:db8:4::"), len);

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
    addIPv6Address(host1, "2001:db8:1::10");
    ASSERT_NO_THROW(addTestOptions(host1, true, DHCP6_ONLY));

    HostPtr host2 = HostDataSourceUtils::initializeHost6("2001:db8:2::", Host::IDENT_DUID, true);
    addIPv6Address(host2, "2001:db8:1::20");
    HostPtr host3 = HostDataSourceUtils::initializeHost6("2001:db8:3::", Host::IDENT_DUID, true);
    addIPv6Address(host3, "2001:db8:1::30");
    HostPtr host4 = HostDataSourceUtils::initializeHost6("2001:db8:4::", Host::IDENT_DUID, true);
    addIPv6Address(host4, "2001:db8:1::40");

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
    HostPtr host = HostDataSourceUtils::initializeHost6("2001:db8:1::", Host::IDENT_DUID, true);

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
    HostPtr host = HostDataSourceUtils::initializeHost6("2001:db8:1::", Host::IDENT_HWADDR, true);

    // Add this reservation once.
    ASSERT_NO_THROW(hdsptr_->add(host));

    // Then try to add it again, it should throw an exception.
    ASSERT_THROW(hdsptr_->add(host), DuplicateEntry);
}

void
GenericHostDataSourceTest::testAddDuplicateIPv6() {
    // Make sure we have the pointer to the host data source.
    ASSERT_TRUE(hdsptr_);

    // Create a host reservation.
    HostPtr host = HostDataSourceUtils::initializeHost6("2001:db8:1::", Host::IDENT_HWADDR, true);

    // Add this reservation once.
    ASSERT_NO_THROW(hdsptr_->add(host));

    // Create a host with a different identifier but the same IPv6 address. An attempt
    // to create the reservation for the same IPv6 address should fail.
    host = HostDataSourceUtils::initializeHost6("2001:db8:1::", Host::IDENT_HWADDR, true);
    EXPECT_THROW(hdsptr_->add(host), DuplicateEntry);
}

void
GenericHostDataSourceTest::testAllowDuplicateIPv6() {
    // Make sure we have the pointer to the host data source.
    ASSERT_TRUE(hdsptr_);
    ASSERT_TRUE(hdsptr_->setIPReservationsUnique(false));

    // Create a host reservations.
    HostPtr host = HostDataSourceUtils::initializeHost6("2001:db8:1::", Host::IDENT_HWADDR, true, true);
    addIPv6Address(host, "2001:db8:2::");
    auto host_id = host->getHostId();
    auto subnet_id = host->getIPv6SubnetID();

    // Add this reservation once.
    ASSERT_NO_THROW(hdsptr_->add(host));

    // Then try to add it again, it should throw an exception because the
    // HWADDR is the same.
    host = HostDataSourceUtils::initializeHost6("2001:db8:1::", Host::IDENT_HWADDR, true, false);
    addIPv6Address(host, "2001:db8:2::");
    host->setHostId(++host_id);
    host->setIPv6SubnetID(subnet_id);
    ASSERT_THROW(hdsptr_->add(host), DuplicateEntry);

    // This time use a different host identifier and try again.
    // This update should succeed because we permitted to create
    // multiple IP reservations for the same IP address but different
    // identifier.
    host = HostDataSourceUtils::initializeHost6("2001:db8:1::", Host::IDENT_HWADDR, true, true);
    host->setHostId(++host_id);
    host->setIPv6SubnetID(subnet_id);
    ASSERT_NO_THROW(hdsptr_->add(host));

    ConstHostCollection returned;
    ASSERT_NO_THROW(returned = hdsptr_->getAll6(host->getIPv6SubnetID(), IOAddress("2001:db8:1::")));
    EXPECT_EQ(2, returned.size());
    EXPECT_NE(returned[0]->getIdentifierAsText(), returned[1]->getIdentifierAsText());

    // Let's now try to delete the hosts by subnet_id and address.
    bool deleted = false;
    ASSERT_NO_THROW(deleted = hdsptr_->del(subnet_id, IOAddress("2001:db8:1::")));
    ASSERT_TRUE(deleted);
    ASSERT_NO_THROW(returned = hdsptr_->getAll6(host->getIPv6SubnetID(), IOAddress("2001:db8:1::")));
    EXPECT_TRUE(returned.empty());
}

void
GenericHostDataSourceTest::testAddDuplicateIPv4() {
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
GenericHostDataSourceTest::testAllowDuplicateIPv4() {
    // Make sure we have the pointer to the host data source.
    ASSERT_TRUE(hdsptr_);
    ASSERT_TRUE(hdsptr_->setIPReservationsUnique(false));

    // Create a host reservations.
    HostPtr host = HostDataSourceUtils::initializeHost4("192.0.2.1", Host::IDENT_DUID, true);
    auto host_id = host->getHostId();
    auto subnet_id = host->getIPv4SubnetID();

    // Add this reservation once.
    ASSERT_NO_THROW(hdsptr_->add(host));

    // Then try to add it again, it should throw an exception because the
    // DUID is the same.
    host = HostDataSourceUtils::initializeHost4("192.0.2.1", Host::IDENT_DUID, false);
    host->setHostId(++host_id);
    host->setIPv4SubnetID(subnet_id);
    ASSERT_THROW(hdsptr_->add(host), DuplicateEntry);

    // This time use a different host identifier and try again.
    // This update should succeed because we permitted to create
    // multiple IP reservations for the same IP address but different
    // identifier.
    host = HostDataSourceUtils::initializeHost4("192.0.2.1", Host::IDENT_DUID, true);
    host->setHostId(++host_id);
    host->setIPv4SubnetID(subnet_id);
    ASSERT_NO_THROW(hdsptr_->add(host));

    ConstHostCollection returned;
    ASSERT_NO_THROW(returned = hdsptr_->getAll4(host->getIPv4SubnetID(), IOAddress("192.0.2.1")));
    EXPECT_EQ(2, returned.size());
    EXPECT_NE(returned[0]->getIdentifierAsText(), returned[1]->getIdentifierAsText());

    // Let's now try to delete the hosts by subnet_id and address.
    bool deleted = false;
    ASSERT_NO_THROW(deleted = hdsptr_->del(subnet_id, IOAddress("192.0.2.1")));
    ASSERT_TRUE(deleted);
    ASSERT_NO_THROW(returned = hdsptr_->getAll4(host->getIPv4SubnetID(), IOAddress("192.0.2.1")));
    EXPECT_TRUE(returned.empty());
}

void
GenericHostDataSourceTest::testDisallowDuplicateIP() {
    // Make sure we have the pointer to the host data source.
    ASSERT_TRUE(hdsptr_);
    // The backend does not support switching to the mode in which multiple
    // reservations for the same address can be created.
    EXPECT_FALSE(hdsptr_->setIPReservationsUnique(false));

    // The default mode still can be used.
    EXPECT_TRUE(hdsptr_->setIPReservationsUnique(true));
}

void
GenericHostDataSourceTest::testAddr6AndPrefix() {
    // Make sure we have the pointer to the host data source.
    ASSERT_TRUE(hdsptr_);

    // Create a host reservations with prefix reservation (prefix = true)
    HostPtr host = HostDataSourceUtils::initializeHost6("2001:db8:1::", Host::IDENT_DUID, true);

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

    auto returned_host = *hosts_by_subnet.begin();
    EXPECT_FALSE(returned_host->getCfgOption4()->isEncapsulated());
    ASSERT_NO_THROW(returned_host->encapsulateOptions());
    auto cfg_option = returned_host->getCfgOption4();

    auto option43 = cfg_option->get(DHCP4_OPTION_SPACE, DHO_VENDOR_ENCAPSULATED_OPTIONS);
    ASSERT_TRUE(option43.option_);

    EXPECT_TRUE(cfg_option->get("vendor-encapsulated-options-space", 1).option_);

    auto option43_1 = option43.option_->getOption(1);
    EXPECT_TRUE(option43_1);

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
    for (auto const& it : hosts) {
        ASSERT_NO_THROW(hdsptr_->add(it));
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
    for (auto const& it : hosts) {
        IPv6ResrvRange range = it->getIPv6Reservations();
        // This get6() call is particularly useful to test because it involves a
        // subquery for MySQL and PostgreSQL.
        ConstHostPtr from_hds =
            hdsptr_->get6(range.first->second.getPrefix(), 128);
        ASSERT_TRUE(from_hds);
        HostDataSourceUtils::compareHosts(it, from_hds);
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
GenericHostDataSourceTest::testDelete2ForIPv6() {
    // Make sure we have a pointer to the host data source.
    ASSERT_TRUE(hdsptr_);

    // Let's create a v6 host...
    IOAddress address1("2001:db8:1::1");
    IOAddress address2("2001:db8:2::2");
    SubnetID subnet_id(42);
    auto ident = HostDataSourceUtils::generateIdentifier(Host::IDENT_DUID);
    HostPtr host = HostPtr(new Host(&ident[0], ident.size(), Host::IDENT_DUID,
                                    SUBNET_ID_UNUSED, subnet_id,
                                    IOAddress::IPV4_ZERO_ADDRESS()));
    host->addReservation(IPv6Resrv(IPv6Resrv::TYPE_NA, address1));
    host->addReservation(IPv6Resrv(IPv6Resrv::TYPE_NA, address2));
    // ... and add it to the data source.
    ASSERT_NO_THROW(hdsptr_->add(host));
    EXPECT_EQ(2, countDBReservations6());

    // Delete the host using its first address.
    EXPECT_TRUE(hdsptr_->del(subnet_id, address1));

    // Check if all addresses were removed.
    EXPECT_EQ(0, countDBReservations6());
    EXPECT_FALSE(hdsptr_->get6(subnet_id, address2));
    EXPECT_FALSE(hdsptr_->del(subnet_id, address2));
}

void
GenericHostDataSourceTest::testDeleteBothForIPv6() {
    // Make sure we have a pointer to the host data source.
    ASSERT_TRUE(hdsptr_);

    // Let's create a v6 host...
    IOAddress address1("2001:db8:1::1");
    IOAddress address2("2001:db8:2::");
    SubnetID subnet_id(42);
    auto ident = HostDataSourceUtils::generateIdentifier(Host::IDENT_DUID);
    HostPtr host = HostPtr(new Host(&ident[0], ident.size(), Host::IDENT_DUID,
                                    SUBNET_ID_UNUSED, subnet_id,
                                    IOAddress::IPV4_ZERO_ADDRESS()));
    host->addReservation(IPv6Resrv(IPv6Resrv::TYPE_NA, address1));
    host->addReservation(IPv6Resrv(IPv6Resrv::TYPE_PD, address2, 64));
    // ... and add it to the data source.
    ASSERT_NO_THROW(hdsptr_->add(host));
    EXPECT_EQ(2, countDBReservations6());

    // Delete the host using its address.
    EXPECT_TRUE(hdsptr_->del(subnet_id, address1));

    // Check if all reservations were removed.
    EXPECT_EQ(0, countDBReservations6());
    EXPECT_FALSE(hdsptr_->get6(subnet_id, address2));
    EXPECT_FALSE(hdsptr_->del(subnet_id, address2));
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

void
HostMgrDbLostCallbackTest::testRetryOpenDbLostAndRecoveredCallback() {
    // Set the connectivity lost callback.
    isc::db::DatabaseConnection::db_lost_callback_ =
        std::bind(&HostMgrDbLostCallbackTest::db_lost_callback, this, ph::_1);

    // Set the connectivity recovered callback.
    isc::db::DatabaseConnection::db_recovered_callback_ =
        std::bind(&HostMgrDbLostCallbackTest::db_recovered_callback, this, ph::_1);

    // Set the connectivity failed callback.
    isc::db::DatabaseConnection::db_failed_callback_ =
        std::bind(&HostMgrDbLostCallbackTest::db_failed_callback, this, ph::_1);

    std::string access = invalidConnectString();
    access += " retry-on-startup=true";
    CfgMgr::instance().getCurrentCfg()->getCfgDbAccess()->setHostDbAccessString(access);

    std::shared_ptr<DbConnectionInitWithRetry> dbr(new DbConnectionInitWithRetry());

    // Create the HostMgr.
    HostMgr::create();

    ASSERT_THROW(HostMgr::addBackend(access), DbOpenErrorWithRetry);

    dbr.reset();

    ASSERT_FALSE(HostMgr::instance().getHostDataSource());

    access = validConnectString();
    access += " retry-on-startup=true";
    CfgMgr::instance().clear();
    CfgMgr::instance().getCurrentCfg()->getCfgDbAccess()->setHostDbAccessString(access);

    io_service_->poll();

    // Our lost and recovered connectivity callback should have been invoked.
    EXPECT_EQ(1, db_lost_callback_called_);
    EXPECT_EQ(1, db_recovered_callback_called_);
    EXPECT_EQ(0, db_failed_callback_called_);

    ASSERT_TRUE(HostMgr::instance().getHostDataSource());
}

void
HostMgrDbLostCallbackTest::testRetryOpenDbLostAndFailedCallback() {
    // Set the connectivity lost callback.
    isc::db::DatabaseConnection::db_lost_callback_ =
        std::bind(&HostMgrDbLostCallbackTest::db_lost_callback, this, ph::_1);

    // Set the connectivity recovered callback.
    isc::db::DatabaseConnection::db_recovered_callback_ =
        std::bind(&HostMgrDbLostCallbackTest::db_recovered_callback, this, ph::_1);

    // Set the connectivity failed callback.
    isc::db::DatabaseConnection::db_failed_callback_ =
        std::bind(&HostMgrDbLostCallbackTest::db_failed_callback, this, ph::_1);

    std::string access = invalidConnectString();
    access += " retry-on-startup=true";
    CfgMgr::instance().getCurrentCfg()->getCfgDbAccess()->setHostDbAccessString(access);

    std::shared_ptr<DbConnectionInitWithRetry> dbr(new DbConnectionInitWithRetry());

    // Create the HostMgr.
    HostMgr::create();

    ASSERT_THROW(HostMgr::addBackend(access), DbOpenErrorWithRetry);

    dbr.reset();

    ASSERT_FALSE(HostMgr::instance().getHostDataSource());

    io_service_->poll();

    // Our lost and failed connectivity callback should have been invoked.
    EXPECT_EQ(1, db_lost_callback_called_);
    EXPECT_EQ(0, db_recovered_callback_called_);
    EXPECT_EQ(1, db_failed_callback_called_);

    ASSERT_FALSE(HostMgr::instance().getHostDataSource());
}

void
HostMgrDbLostCallbackTest::testRetryOpenDbLostAndRecoveredAfterTimeoutCallback() {
    // Set the connectivity lost callback.
    isc::db::DatabaseConnection::db_lost_callback_ =
        std::bind(&HostMgrDbLostCallbackTest::db_lost_callback, this, ph::_1);

    // Set the connectivity recovered callback.
    isc::db::DatabaseConnection::db_recovered_callback_ =
        std::bind(&HostMgrDbLostCallbackTest::db_recovered_callback, this, ph::_1);

    // Set the connectivity failed callback.
    isc::db::DatabaseConnection::db_failed_callback_ =
        std::bind(&HostMgrDbLostCallbackTest::db_failed_callback, this, ph::_1);

    std::string access = invalidConnectString();
    std::string extra = " max-reconnect-tries=3 reconnect-wait-time=1 retry-on-startup=true";
    access += extra;
    CfgMgr::instance().getCurrentCfg()->getCfgDbAccess()->setHostDbAccessString(access);

    std::shared_ptr<DbConnectionInitWithRetry> dbr(new DbConnectionInitWithRetry());

    // Create the HostMgr.
    HostMgr::create();

    ASSERT_THROW(HostMgr::addBackend(access), DbOpenErrorWithRetry);

    dbr.reset();

    ASSERT_FALSE(HostMgr::instance().getHostDataSource());

    io_service_->poll();

    // Our lost connectivity callback should have been invoked.
    EXPECT_EQ(1, db_lost_callback_called_);
    EXPECT_EQ(0, db_recovered_callback_called_);
    EXPECT_EQ(0, db_failed_callback_called_);

    access = validConnectString();
    access += extra;
    CfgMgr::instance().clear();
    CfgMgr::instance().getCurrentCfg()->getCfgDbAccess()->setHostDbAccessString(access);

    sleep(1);

    io_service_->poll();

    // Our lost and recovered connectivity callback should have been invoked.
    EXPECT_EQ(2, db_lost_callback_called_);
    EXPECT_EQ(1, db_recovered_callback_called_);
    EXPECT_EQ(0, db_failed_callback_called_);

    ASSERT_TRUE(HostMgr::instance().getHostDataSource());

    sleep(1);

    io_service_->poll();

    // No callback should have been invoked.
    EXPECT_EQ(2, db_lost_callback_called_);
    EXPECT_EQ(1, db_recovered_callback_called_);
    EXPECT_EQ(0, db_failed_callback_called_);

    ASSERT_TRUE(HostMgr::instance().getHostDataSource());
}

void
HostMgrDbLostCallbackTest::testRetryOpenDbLostAndFailedAfterTimeoutCallback() {
    // Set the connectivity lost callback.
    isc::db::DatabaseConnection::db_lost_callback_ =
        std::bind(&HostMgrDbLostCallbackTest::db_lost_callback, this, ph::_1);

    // Set the connectivity recovered callback.
    isc::db::DatabaseConnection::db_recovered_callback_ =
        std::bind(&HostMgrDbLostCallbackTest::db_recovered_callback, this, ph::_1);

    // Set the connectivity failed callback.
    isc::db::DatabaseConnection::db_failed_callback_ =
        std::bind(&HostMgrDbLostCallbackTest::db_failed_callback, this, ph::_1);

    std::string access = invalidConnectString();
    std::string extra = " max-reconnect-tries=3 reconnect-wait-time=1 retry-on-startup=true";
    access += extra;
    CfgMgr::instance().getCurrentCfg()->getCfgDbAccess()->setHostDbAccessString(access);

    std::shared_ptr<DbConnectionInitWithRetry> dbr(new DbConnectionInitWithRetry());

    // Create the HostMgr.
    HostMgr::create();

    ASSERT_THROW(HostMgr::addBackend(access), DbOpenErrorWithRetry);

    dbr.reset();

    ASSERT_FALSE(HostMgr::instance().getHostDataSource());

    io_service_->poll();

    // Our lost connectivity callback should have been invoked.
    EXPECT_EQ(1, db_lost_callback_called_);
    EXPECT_EQ(0, db_recovered_callback_called_);
    EXPECT_EQ(0, db_failed_callback_called_);

    ASSERT_FALSE(HostMgr::instance().getHostDataSource());

    sleep(1);

    io_service_->poll();

    // Our lost connectivity callback should have been invoked.
    EXPECT_EQ(2, db_lost_callback_called_);
    EXPECT_EQ(0, db_recovered_callback_called_);
    EXPECT_EQ(0, db_failed_callback_called_);

    ASSERT_FALSE(HostMgr::instance().getHostDataSource());

    sleep(1);

    io_service_->poll();

    // Our lost and failed connectivity callback should have been invoked.
    EXPECT_EQ(3, db_lost_callback_called_);
    EXPECT_EQ(0, db_recovered_callback_called_);
    EXPECT_EQ(1, db_failed_callback_called_);

    ASSERT_FALSE(HostMgr::instance().getHostDataSource());
}

void
HostMgrDbLostCallbackTest::testNoCallbackOnOpenFailure() {
    isc::db::DatabaseConnection::db_lost_callback_ =
        std::bind(&HostMgrDbLostCallbackTest::db_lost_callback, this, ph::_1);

    // Set the connectivity recovered callback.
    isc::db::DatabaseConnection::db_recovered_callback_ =
        std::bind(&HostMgrDbLostCallbackTest::db_recovered_callback, this, ph::_1);

    // Set the connectivity failed callback.
    isc::db::DatabaseConnection::db_failed_callback_ =
        std::bind(&HostMgrDbLostCallbackTest::db_failed_callback, this, ph::_1);

    // Connect to the host backend.
    ASSERT_THROW(HostMgr::addBackend(invalidConnectString()), DbOpenError);

    io_service_->poll();

    EXPECT_EQ(0, db_lost_callback_called_);
    EXPECT_EQ(0, db_recovered_callback_called_);
    EXPECT_EQ(0, db_failed_callback_called_);
}

void
HostMgrDbLostCallbackTest::testDbLostAndRecoveredCallback() {
    // Set the connectivity lost callback.
    isc::db::DatabaseConnection::db_lost_callback_ =
        std::bind(&HostMgrDbLostCallbackTest::db_lost_callback, this, ph::_1);

    // Set the connectivity recovered callback.
    isc::db::DatabaseConnection::db_recovered_callback_ =
        std::bind(&HostMgrDbLostCallbackTest::db_recovered_callback, this, ph::_1);

    // Set the connectivity failed callback.
    isc::db::DatabaseConnection::db_failed_callback_ =
        std::bind(&HostMgrDbLostCallbackTest::db_failed_callback, this, ph::_1);

    std::string access = validConnectString();
    CfgMgr::instance().getCurrentCfg()->getCfgDbAccess()->setHostDbAccessString(access);

    // Create the HostMgr.
    HostMgr::create();

    // Find the most recently opened socket. Our SQL client's socket should
    // be the next one.
    int last_open_socket = findLastSocketFd();

    // Fill holes.
    FillFdHoles holes(last_open_socket);

    // Connect to the host backend.
    ASSERT_NO_THROW(HostMgr::addBackend(access));

    // Find the SQL client socket.
    int sql_socket = findLastSocketFd();
    ASSERT_TRUE(sql_socket > last_open_socket);

    // Verify we can execute a query.  We don't care about the answer.
    ConstHostCollection hosts;
    ASSERT_NO_THROW(hosts = HostMgr::instance().getAll4(IOAddress("192.0.2.5")));

    // Now close the sql socket out from under backend client
    ASSERT_EQ(0, close(sql_socket));

    // A query should fail with DbConnectionUnusable.
    ASSERT_THROW(hosts = HostMgr::instance().getAll4(IOAddress("192.0.2.5")),
                 DbConnectionUnusable);

    io_service_->poll();

    // Our lost and recovered connectivity callback should have been invoked.
    EXPECT_EQ(1, db_lost_callback_called_);
    EXPECT_EQ(1, db_recovered_callback_called_);
    EXPECT_EQ(0, db_failed_callback_called_);
}

void
HostMgrDbLostCallbackTest::testDbLostAndFailedCallback() {
    // Set the connectivity lost callback.
    isc::db::DatabaseConnection::db_lost_callback_ =
        std::bind(&HostMgrDbLostCallbackTest::db_lost_callback, this, ph::_1);

    // Set the connectivity recovered callback.
    isc::db::DatabaseConnection::db_recovered_callback_ =
        std::bind(&HostMgrDbLostCallbackTest::db_recovered_callback, this, ph::_1);

    // Set the connectivity failed callback.
    isc::db::DatabaseConnection::db_failed_callback_ =
        std::bind(&HostMgrDbLostCallbackTest::db_failed_callback, this, ph::_1);

    std::string access = validConnectString();
    CfgMgr::instance().getCurrentCfg()->getCfgDbAccess()->setHostDbAccessString(access);

    // Create the HostMgr.
    HostMgr::create();

    // Find the most recently opened socket. Our SQL client's socket should
    // be the next one.
    int last_open_socket = findLastSocketFd();

    // Fill holes.
    FillFdHoles holes(last_open_socket);

    // Connect to the host backend.
    ASSERT_NO_THROW(HostMgr::addBackend(access));

    // Find the SQL client socket.
    int sql_socket = findLastSocketFd();
    ASSERT_TRUE(sql_socket > last_open_socket);

    // Verify we can execute a query.  We don't care about the answer.
    ConstHostCollection hosts;
    ASSERT_NO_THROW(hosts = HostMgr::instance().getAll4(IOAddress("192.0.2.5")));

    access = invalidConnectString();
    CfgMgr::instance().clear();
    // by adding an invalid access will cause the manager factory to throw
    // resulting in failure to recreate the manager
    CfgMgr::instance().getCurrentCfg()->getCfgDbAccess()->setHostDbAccessString(access);

    // Now close the sql socket out from under backend client
    ASSERT_EQ(0, close(sql_socket));

    // A query should fail with DbConnectionUnusable.
    ASSERT_THROW(hosts = HostMgr::instance().getAll4(IOAddress("192.0.2.5")),
                 DbConnectionUnusable);

    io_service_->poll();

    // Our lost and failed connectivity callback should have been invoked.
    EXPECT_EQ(1, db_lost_callback_called_);
    EXPECT_EQ(0, db_recovered_callback_called_);
    EXPECT_EQ(1, db_failed_callback_called_);
}

void
HostMgrDbLostCallbackTest::testDbLostAndRecoveredAfterTimeoutCallback() {
    // Set the connectivity lost callback.
    isc::db::DatabaseConnection::db_lost_callback_ =
        std::bind(&HostMgrDbLostCallbackTest::db_lost_callback, this, ph::_1);

    // Set the connectivity recovered callback.
    isc::db::DatabaseConnection::db_recovered_callback_ =
        std::bind(&HostMgrDbLostCallbackTest::db_recovered_callback, this, ph::_1);

    // Set the connectivity failed callback.
    isc::db::DatabaseConnection::db_failed_callback_ =
        std::bind(&HostMgrDbLostCallbackTest::db_failed_callback, this, ph::_1);

    std::string access = validConnectString();
    std::string extra = " max-reconnect-tries=3 reconnect-wait-time=1";
    access += extra;
    CfgMgr::instance().getCurrentCfg()->getCfgDbAccess()->setHostDbAccessString(access);

    // Create the HostMgr.
    HostMgr::create();

    // Find the most recently opened socket. Our SQL client's socket should
    // be the next one.
    int last_open_socket = findLastSocketFd();

    // Fill holes.
    FillFdHoles holes(last_open_socket);

    // Connect to the host backend.
    ASSERT_NO_THROW(HostMgr::addBackend(access));

    // Find the SQL client socket.
    int sql_socket = findLastSocketFd();
    ASSERT_TRUE(sql_socket > last_open_socket);

    // Verify we can execute a query.  We don't care about the answer.
    ConstHostCollection hosts;
    ASSERT_NO_THROW(hosts = HostMgr::instance().getAll4(IOAddress("192.0.2.5")));

    access = invalidConnectString();
    access += extra;
    CfgMgr::instance().clear();
    // by adding an invalid access will cause the manager factory to throw
    // resulting in failure to recreate the manager
    CfgMgr::instance().getCurrentCfg()->getCfgDbAccess()->setHostDbAccessString(access);

    // Now close the sql socket out from under backend client
    ASSERT_EQ(0, close(sql_socket));

    // A query should fail with DbConnectionUnusable.
    ASSERT_THROW(hosts = HostMgr::instance().getAll4(IOAddress("192.0.2.5")),
                 DbConnectionUnusable);

    io_service_->poll();

    // Our lost connectivity callback should have been invoked.
    EXPECT_EQ(1, db_lost_callback_called_);
    EXPECT_EQ(0, db_recovered_callback_called_);
    EXPECT_EQ(0, db_failed_callback_called_);

    access = validConnectString();
    access += extra;
    CfgMgr::instance().clear();
    CfgMgr::instance().getCurrentCfg()->getCfgDbAccess()->setHostDbAccessString(access);

    sleep(1);

    io_service_->poll();

    // Our lost and recovered connectivity callback should have been invoked.
    EXPECT_EQ(2, db_lost_callback_called_);
    EXPECT_EQ(1, db_recovered_callback_called_);
    EXPECT_EQ(0, db_failed_callback_called_);

    sleep(1);

    io_service_->poll();

    // No callback should have been invoked.
    EXPECT_EQ(2, db_lost_callback_called_);
    EXPECT_EQ(1, db_recovered_callback_called_);
    EXPECT_EQ(0, db_failed_callback_called_);
}

void
HostMgrDbLostCallbackTest::testDbLostAndFailedAfterTimeoutCallback() {
    // Set the connectivity lost callback.
    isc::db::DatabaseConnection::db_lost_callback_ =
        std::bind(&HostMgrDbLostCallbackTest::db_lost_callback, this, ph::_1);

    // Set the connectivity recovered callback.
    isc::db::DatabaseConnection::db_recovered_callback_ =
        std::bind(&HostMgrDbLostCallbackTest::db_recovered_callback, this, ph::_1);

    // Set the connectivity failed callback.
    isc::db::DatabaseConnection::db_failed_callback_ =
        std::bind(&HostMgrDbLostCallbackTest::db_failed_callback, this, ph::_1);

    std::string access = validConnectString();
    std::string extra = " max-reconnect-tries=3 reconnect-wait-time=1";
    access += extra;
    CfgMgr::instance().getCurrentCfg()->getCfgDbAccess()->setHostDbAccessString(access);

    // Create the HostMgr.
    HostMgr::create();

    // Find the most recently opened socket. Our SQL client's socket should
    // be the next one.
    int last_open_socket = findLastSocketFd();

    // Fill holes.
    FillFdHoles holes(last_open_socket);

    // Connect to the host backend.
    ASSERT_NO_THROW(HostMgr::addBackend(access));

    // Find the SQL client socket.
    int sql_socket = findLastSocketFd();
    ASSERT_TRUE(sql_socket > last_open_socket);

    // Verify we can execute a query.  We don't care about the answer.
    ConstHostCollection hosts;
    ASSERT_NO_THROW(hosts = HostMgr::instance().getAll4(IOAddress("192.0.2.5")));

    access = invalidConnectString();
    access += extra;
    CfgMgr::instance().clear();
    // by adding an invalid access will cause the manager factory to throw
    // resulting in failure to recreate the manager
    CfgMgr::instance().getCurrentCfg()->getCfgDbAccess()->setHostDbAccessString(access);

    // Now close the sql socket out from under backend client
    ASSERT_EQ(0, close(sql_socket));

    // A query should fail with DbConnectionUnusable.
    ASSERT_THROW(hosts = HostMgr::instance().getAll4(IOAddress("192.0.2.5")),
                 DbConnectionUnusable);

    io_service_->poll();

    // Our lost connectivity callback should have been invoked.
    EXPECT_EQ(1, db_lost_callback_called_);
    EXPECT_EQ(0, db_recovered_callback_called_);
    EXPECT_EQ(0, db_failed_callback_called_);

    sleep(1);

    io_service_->poll();

    // Our lost connectivity callback should have been invoked.
    EXPECT_EQ(2, db_lost_callback_called_);
    EXPECT_EQ(0, db_recovered_callback_called_);
    EXPECT_EQ(0, db_failed_callback_called_);

    sleep(1);

    io_service_->poll();

    // Our lost and failed connectivity callback should have been invoked.
    EXPECT_EQ(3, db_lost_callback_called_);
    EXPECT_EQ(0, db_recovered_callback_called_);
    EXPECT_EQ(1, db_failed_callback_called_);
}

void
// cppcheck-suppress unusedFunction
HostMgrTest::SetUp() {
    // Remove all configuration which may be dangling from the previous test.
    CfgMgr::instance().clear();
    // Recreate HostMgr instance. It drops any previous state.
    HostMgr::create();
    // Create HW addresses from the template.
    const uint8_t mac_template[] = {
        0x01, 0x02, 0x0A, 0xBB, 0x03, 0x00
    };
    for (uint8_t i = 0; i < 10; ++i) {
        std::vector<uint8_t> vec(mac_template,
                                 mac_template + sizeof(mac_template));
        vec[vec.size() - 1] = i;
        HWAddrPtr hwaddr(new HWAddr(vec, HTYPE_ETHER));
        hwaddrs_.push_back(hwaddr);
    }
    // Create DUIDs from the template.
    const uint8_t duid_template[] = {
        0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x00
    };
    for (uint8_t i = 0; i < 10; ++i) {
        std::vector<uint8_t> vec(duid_template,
                                 duid_template + sizeof(mac_template));
        vec[vec.size() - 1] = i;
        DuidPtr duid(new DUID(vec));
        duids_.push_back(duid);
    }
}

CfgHostsPtr
HostMgrTest::getCfgHosts() const {
    return (CfgMgr::instance().getStagingCfg()->getCfgHosts());
}

void
HostMgrTest::addHost4(BaseHostDataSource& data_source,
                      const HWAddrPtr& hwaddr,
                      const SubnetID& subnet_id,
                      const IOAddress& address) {
    data_source.add(HostPtr(new Host(hwaddr->toText(false),
                                     "hw-address", subnet_id, SUBNET_ID_UNUSED,
                                     address)));
}

void
HostMgrTest::addHost6(BaseHostDataSource& data_source,
                      const DuidPtr& duid,
                      const SubnetID& subnet_id,
                      const IOAddress& address,
                      const uint8_t prefix_len) {
    HostPtr new_host(new Host(duid->toText(), "duid", SubnetID(1),
                              subnet_id, IOAddress::IPV4_ZERO_ADDRESS()));
    new_host->addReservation(IPv6Resrv(prefix_len == 128 ? IPv6Resrv::TYPE_NA :
                                       IPv6Resrv::TYPE_PD,
                                       address, prefix_len));
    data_source.add(new_host);
}

void
HostMgrTest::addHost6(BaseHostDataSource& data_source,
                      const DuidPtr& duid,
                      const SubnetID& subnet_id,
                      const std::vector<IOAddress>& addresses,
                      const uint8_t prefix_len) {
    HostPtr new_host(new Host(duid->toText(), "duid", SubnetID(1),
                              subnet_id, IOAddress::IPV4_ZERO_ADDRESS()));
    for (const IOAddress& address : addresses) {
        new_host->addReservation(IPv6Resrv(prefix_len == 128 ? IPv6Resrv::TYPE_NA :
                                                               IPv6Resrv::TYPE_PD,
                                           address, prefix_len));
    }

    data_source.add(new_host);
}

void
HostMgrTest::testGetAll(BaseHostDataSource& data_source1,
                        BaseHostDataSource& data_source2) {
    // Initially, no reservations should be present.
    ConstHostCollection hosts =
        HostMgr::instance().getAll(Host::IDENT_HWADDR,
                                   &hwaddrs_[1]->hwaddr_[0],
                                   hwaddrs_[1]->hwaddr_.size());
    ASSERT_TRUE(hosts.empty());

    // Add two reservations for the same HW address. They differ by the IP
    // address reserved and the IPv4 subnet.
    addHost4(data_source1, hwaddrs_[0], SubnetID(1), IOAddress("192.0.2.5"));
    addHost4(data_source2, hwaddrs_[0], SubnetID(10), IOAddress("192.0.3.10"));

    CfgMgr::instance().commit();

    // If there non-matching HW address is specified, nothing should be
    // returned.
    hosts = HostMgr::instance().getAll(Host::IDENT_HWADDR,
                                       &hwaddrs_[1]->hwaddr_[0],
                                       hwaddrs_[1]->hwaddr_.size());
    ASSERT_TRUE(hosts.empty());

    // For the correct HW address, there should be two reservations.
    hosts = HostMgr::instance().getAll(Host::IDENT_HWADDR,
                                       &hwaddrs_[0]->hwaddr_[0],
                                       hwaddrs_[0]->hwaddr_.size());
    ASSERT_EQ(2, hosts.size());

    // We don't know the order in which the reservations are returned so
    // we have to match with any of the two reservations returned.

    // Look for the first reservation.
    bool found = false;
    for (unsigned i = 0; i < 2; ++i) {
        if (hosts[i]->getIPv4Reservation() == IOAddress("192.0.2.5")) {
            ASSERT_EQ(1, hosts[i]->getIPv4SubnetID());
            found = true;
        }
    }
    if (!found) {
        ADD_FAILURE() << "Reservation for the IPv4 address 192.0.2.5"
            " not found using getAll method";
    }

    // Look for the second reservation.
    found = false;
    for (unsigned i = 0; i < 2; ++i) {
        if (hosts[i]->getIPv4Reservation() == IOAddress("192.0.3.10")) {
            ASSERT_EQ(10, hosts[i]->getIPv4SubnetID());
            found = true;
        }
    }
    if (!found) {
        ADD_FAILURE() << "Reservation for the IPv4 address 192.0.3.10"
            " not found using getAll method";
    }

    // Check handling of operation target.
    bool is_first_source_primary = isPrimaryDataSource(data_source1);
    bool is_second_source_primary = isPrimaryDataSource(data_source2);
    size_t hosts_in_primary_source = is_first_source_primary + is_second_source_primary;

    // Primary source target.
    hosts = HostMgr::instance().getAll(Host::IDENT_HWADDR,
                                       &hwaddrs_[0]->hwaddr_[0],
                                       hwaddrs_[0]->hwaddr_.size(),
                                       HostMgrOperationTarget::PRIMARY_SOURCE);
    EXPECT_EQ(hosts_in_primary_source, hosts.size());
    if (is_first_source_primary) {
        found = false;
        for (unsigned i = 0; i < hosts.size(); ++i) {
            if (hosts[i]->getIPv4Reservation() == IOAddress("192.0.2.5")) {
                ASSERT_EQ(1, hosts[i]->getIPv4SubnetID());
                found = true;
            }
        }
        if (!found) {
            ADD_FAILURE() << "Reservation for the IPv4 address 192.0.2.5"
                " not found using getAll method with PRIMARY_SOURCE operation"
                " target";
        }
    }
    if (is_second_source_primary) {
        found = false;
        for (unsigned i = 0; i < hosts.size(); ++i) {
            if (hosts[i]->getIPv4Reservation() == IOAddress("192.0.3.10")) {
                ASSERT_EQ(10, hosts[i]->getIPv4SubnetID());
                found = true;
            }
        }
        if (!found) {
            ADD_FAILURE() << "Reservation for the IPv4 address 192.0.3.10"
                " not found using getAll method with PRIMARY_SOURCE operation"
                " target";
        }
    }

    // Alternate sources target.
    hosts = HostMgr::instance().getAll(Host::IDENT_HWADDR,
                                       &hwaddrs_[0]->hwaddr_[0],
                                       hwaddrs_[0]->hwaddr_.size(),
                                       HostMgrOperationTarget::ALTERNATE_SOURCES);
    EXPECT_EQ(2 - hosts_in_primary_source, hosts.size());

    if (!is_first_source_primary) {
        found = false;
        for (unsigned i = 0; i < hosts.size(); ++i) {
            if (hosts[i]->getIPv4Reservation() == IOAddress("192.0.2.5")) {
                ASSERT_EQ(1, hosts[i]->getIPv4SubnetID());
                found = true;
            }
        }
        if (!found) {
            ADD_FAILURE() << "Reservation for the IPv4 address 192.0.2.5"
                " not found using getAll method with PRIMARY_SOURCE operation"
                " target";
        }
    }
    if (!is_second_source_primary) {
        found = false;
        for (unsigned i = 0; i < hosts.size(); ++i) {
            if (hosts[i]->getIPv4Reservation() == IOAddress("192.0.3.10")) {
                ASSERT_EQ(10, hosts[i]->getIPv4SubnetID());
                found = true;
            }
        }
        if (!found) {
            ADD_FAILURE() << "Reservation for the IPv4 address 192.0.3.10"
                " not found using getAll method with PRIMARY_SOURCE operation"
                " target";
        }
    }

    // Unspecified source target.
    hosts = HostMgr::instance().getAll(Host::IDENT_HWADDR,
                                       &hwaddrs_[0]->hwaddr_[0],
                                       hwaddrs_[0]->hwaddr_.size(),
                                       HostMgrOperationTarget::UNSPECIFIED_SOURCE);
    EXPECT_EQ(0, hosts.size());
}

void
HostMgrTest::testGetAll4BySubnet(BaseHostDataSource& data_source1,
                                 BaseHostDataSource& data_source2) {
    // Initially, no reservations should be present.
    ConstHostCollection hosts = HostMgr::instance().getAll4(SubnetID(1));
    ASSERT_TRUE(hosts.empty());

    // Add two reservations for the same subnet.
    addHost4(data_source1, hwaddrs_[0], SubnetID(1), IOAddress("192.0.2.5"));
    addHost4(data_source2, hwaddrs_[1], SubnetID(1), IOAddress("192.0.2.6"));

    CfgMgr::instance().commit();

    // If there non-matching subnet is specified, nothing should be returned.
    hosts = HostMgr::instance().getAll4(SubnetID(100));
    ASSERT_TRUE(hosts.empty());

    // For the correct subnet, there should be two reservations.
    hosts = HostMgr::instance().getAll4(SubnetID(1));
    ASSERT_EQ(2, hosts.size());

    // Make sure that subnet is correct.
    EXPECT_EQ(1, hosts[0]->getIPv4SubnetID());
    EXPECT_EQ(1, hosts[1]->getIPv4SubnetID());

    // Make sure that two different hosts were returned.
    EXPECT_EQ("192.0.2.5", hosts[0]->getIPv4Reservation().toText());
    EXPECT_EQ("192.0.2.6", hosts[1]->getIPv4Reservation().toText());

    // Make sure that the operation target is supported.
    bool is_first_source_primary = isPrimaryDataSource(data_source1);
    bool is_second_source_primary = isPrimaryDataSource(data_source2);
    size_t hosts_in_primary_source = is_first_source_primary + is_second_source_primary;

    // Select hosts only from the primary source.
    hosts = HostMgr::instance().getAll4(SubnetID(1), HostMgrOperationTarget::PRIMARY_SOURCE);
    EXPECT_EQ(hosts_in_primary_source, hosts.size());
    if (is_first_source_primary) {
        EXPECT_EQ("192.0.2.5", hosts[0]->getIPv4Reservation().toText());
    }
    if (is_second_source_primary) {
        EXPECT_EQ("192.0.2.6", hosts[hosts_in_primary_source-1]->getIPv4Reservation().toText());
    }

    // Select hosts only from the alternate sources.
    hosts = HostMgr::instance().getAll4(SubnetID(1), HostMgrOperationTarget::ALTERNATE_SOURCES);
    EXPECT_EQ(2 - hosts_in_primary_source, hosts.size());
    if (!is_first_source_primary) {
        EXPECT_EQ("192.0.2.5", hosts[0]->getIPv4Reservation().toText());
    }
    if (!is_second_source_primary) {
        EXPECT_EQ("192.0.2.6", hosts[2 - hosts_in_primary_source - 1]->getIPv4Reservation().toText());
    }

    // Select hosts for an unspecified source.
    hosts = HostMgr::instance().getAll4(SubnetID(1), HostMgrOperationTarget::UNSPECIFIED_SOURCE);
    EXPECT_EQ(0, hosts.size());
}

void
HostMgrTest::testGetAll6BySubnet(BaseHostDataSource& data_source1,
                                 BaseHostDataSource& data_source2) {
    // Initially, no reservations should be present.
    ConstHostCollection hosts = HostMgr::instance().getAll6(SubnetID(1));
    ASSERT_TRUE(hosts.empty());

    // Add two reservations for the same subnet.
    addHost6(data_source1, duids_[0], SubnetID(1), IOAddress("2001:db8:1::5"));
    addHost6(data_source2, duids_[1], SubnetID(1), IOAddress("2001:db8:1::6"));

    CfgMgr::instance().commit();

    // If there non-matching subnet is specified, nothing should be returned.
    hosts = HostMgr::instance().getAll6(SubnetID(100));
    ASSERT_TRUE(hosts.empty());

    // For the correct subnet, there should be two reservations.
    hosts = HostMgr::instance().getAll6(SubnetID(1));
    ASSERT_EQ(2, hosts.size());

    // Make sure that subnet is correct.
    EXPECT_EQ(1, hosts[0]->getIPv6SubnetID());
    EXPECT_EQ(1, hosts[1]->getIPv6SubnetID());

    // Make sure that two different hosts were returned.
    EXPECT_TRUE(hosts[0]->hasReservation(
                IPv6Resrv(IPv6Resrv::TYPE_NA, IOAddress("2001:db8:1::5"))));
    EXPECT_TRUE(hosts[1]->hasReservation(
                IPv6Resrv(IPv6Resrv::TYPE_NA, IOAddress("2001:db8:1::6"))));

    // Make sure that the operation target is supported.
    bool is_first_source_primary = isPrimaryDataSource(data_source1);
    bool is_second_source_primary = isPrimaryDataSource(data_source2);
    size_t hosts_in_primary_source = is_first_source_primary + is_second_source_primary;

    // Select hosts only from the primary source.
    hosts = HostMgr::instance().getAll6(SubnetID(1), HostMgrOperationTarget::PRIMARY_SOURCE);
    EXPECT_EQ(hosts_in_primary_source, hosts.size());
    if (is_first_source_primary) {
        EXPECT_TRUE(hosts[0]->hasReservation(
                IPv6Resrv(IPv6Resrv::TYPE_NA, IOAddress("2001:db8:1::5"))));
    }
    if (is_second_source_primary) {
        EXPECT_TRUE(hosts[hosts_in_primary_source-1]->hasReservation(
                IPv6Resrv(IPv6Resrv::TYPE_NA, IOAddress("2001:db8:1::6"))));
    }

    // Select hosts only from the alternate sources.
    hosts = HostMgr::instance().getAll6(SubnetID(1), HostMgrOperationTarget::ALTERNATE_SOURCES);
    EXPECT_EQ(2 - hosts_in_primary_source, hosts.size());
    if (!is_first_source_primary) {
        EXPECT_TRUE(hosts[0]->hasReservation(
                IPv6Resrv(IPv6Resrv::TYPE_NA, IOAddress("2001:db8:1::5"))));
    }
    if (!is_second_source_primary) {
        EXPECT_TRUE(hosts[2 - hosts_in_primary_source - 1]->hasReservation(
                IPv6Resrv(IPv6Resrv::TYPE_NA, IOAddress("2001:db8:1::6"))));
    }

    // Select hosts for an unspecified source.
    hosts = HostMgr::instance().getAll6(SubnetID(1), HostMgrOperationTarget::UNSPECIFIED_SOURCE);
    EXPECT_EQ(0, hosts.size());
}

void
HostMgrTest::testGetAllbyHostname(BaseHostDataSource& data_source1,
                                  BaseHostDataSource& data_source2) {
    // Initially, no reservations should be present.
    ConstHostCollection hosts =
        HostMgr::instance().getAllbyHostname("host");
    ASSERT_TRUE(hosts.empty());

    // Add two reservations with the same hostname.
    HostPtr host1(new Host(hwaddrs_[0]->toText(false), "hw-address",
                           SubnetID(1), SUBNET_ID_UNUSED,
                           IOAddress("192.0.2.5")));
    host1->setHostname("Host");
    data_source1.add(host1);
    HostPtr host2(new Host(hwaddrs_[1]->toText(false), "hw-address",
                           SubnetID(10), SUBNET_ID_UNUSED,
                           IOAddress("192.0.3.10")));
    host2->setHostname("hosT");
    data_source2.add(host2);

    CfgMgr::instance().commit();

    // If there non-matching hostname is specified, nothing should be
    // returned.
    hosts = HostMgr::instance().getAllbyHostname("foobar");
    EXPECT_TRUE(hosts.empty());

    // For the correct hostname, there should be two reservations.
    hosts = HostMgr::instance().getAllbyHostname("host");
    ASSERT_EQ(2, hosts.size());

    // Make sure that subnet is correct.
    EXPECT_EQ(1, hosts[0]->getIPv4SubnetID());
    EXPECT_EQ(10, hosts[1]->getIPv4SubnetID());

    // Make sure that hostname is correct including its case.
    EXPECT_EQ("Host", hosts[0]->getHostname());
    EXPECT_EQ("hosT", hosts[1]->getHostname());

    // Make sure that the operation target is supported.
    bool is_first_source_primary = isPrimaryDataSource(data_source1);
    bool is_second_source_primary = isPrimaryDataSource(data_source2);
    size_t hosts_in_primary_source = is_first_source_primary + is_second_source_primary;

    // Select hosts only from the primary source.
    hosts = HostMgr::instance().getAllbyHostname("host", HostMgrOperationTarget::PRIMARY_SOURCE);
    EXPECT_EQ(hosts_in_primary_source, hosts.size());
    if (is_first_source_primary) {
        EXPECT_EQ(1, hosts[0]->getIPv4SubnetID());
    }
    if (is_second_source_primary) {
        EXPECT_EQ(10, hosts[hosts_in_primary_source-1]->getIPv4SubnetID());
    }

    // Select hosts only from the alternate sources.
    hosts = HostMgr::instance().getAllbyHostname("host", HostMgrOperationTarget::ALTERNATE_SOURCES);
    EXPECT_EQ(2 - hosts_in_primary_source, hosts.size());
    if (!is_first_source_primary) {
        EXPECT_EQ(1, hosts[0]->getIPv4SubnetID());
    }
    if (!is_second_source_primary) {
        EXPECT_EQ(10, hosts[2 - hosts_in_primary_source - 1]->getIPv4SubnetID());
    }

    // Select hosts for an unspecified source.
    hosts = HostMgr::instance().getAllbyHostname("host", HostMgrOperationTarget::UNSPECIFIED_SOURCE);
    EXPECT_EQ(0, hosts.size());
}

void
HostMgrTest::testGetAllbyHostnameSubnet4(BaseHostDataSource& data_source1,
                                         BaseHostDataSource& data_source2) {
    // Initially, no reservations should be present.
    ConstHostCollection hosts =
        HostMgr::instance().getAllbyHostname4("host", SubnetID(1));
    ASSERT_TRUE(hosts.empty());

    // Add two reservations with the same hostname.
    HostPtr host1(new Host(hwaddrs_[0]->toText(false), "hw-address",
                           SubnetID(1), SUBNET_ID_UNUSED,
                           IOAddress("192.0.2.5")));
    host1->setHostname("Host");
    data_source1.add(host1);
    HostPtr host2(new Host(hwaddrs_[1]->toText(false), "hw-address",
                           SubnetID(1), SUBNET_ID_UNUSED,
                           IOAddress("192.0.2.6")));
    host2->setHostname("hosT");
    data_source2.add(host2);

    CfgMgr::instance().commit();

    // If there non-matching hostname is specified, nothing should be
    // returned.
    hosts = HostMgr::instance().getAllbyHostname4("foobar", SubnetID(1));
    EXPECT_TRUE(hosts.empty());

    // If there non-matching subnet is specified, nothing should be
    // returned.
    hosts = HostMgr::instance().getAllbyHostname4("host", SubnetID(10));
    EXPECT_TRUE(hosts.empty());

    // For the correct hostname, there should be two reservations.
    hosts = HostMgr::instance().getAllbyHostname4("host", SubnetID(1));
    ASSERT_EQ(2, hosts.size());

    // Make sure that subnet is correct.
    EXPECT_EQ(1, hosts[0]->getIPv4SubnetID());
    EXPECT_EQ(1, hosts[1]->getIPv4SubnetID());

    // Make sure that two different hosts were returned.
    EXPECT_EQ("192.0.2.5", hosts[0]->getIPv4Reservation().toText());
    EXPECT_EQ("192.0.2.6", hosts[1]->getIPv4Reservation().toText());

    // Make sure that hostname is correct including its case.
    EXPECT_EQ("Host", hosts[0]->getHostname());
    EXPECT_EQ("hosT", hosts[1]->getHostname());

    // Make sure that the operation target is supported.
    bool is_first_source_primary = isPrimaryDataSource(data_source1);
    bool is_second_source_primary = isPrimaryDataSource(data_source2);
    size_t hosts_in_primary_source = is_first_source_primary + is_second_source_primary;

    // Select hosts only from the primary source.
    hosts = HostMgr::instance().getAllbyHostname4("host", SubnetID(1), HostMgrOperationTarget::PRIMARY_SOURCE);
    EXPECT_EQ(hosts_in_primary_source, hosts.size());
    if (is_first_source_primary) {
        EXPECT_EQ("Host", hosts[0]->getHostname());
    }
    if (is_second_source_primary) {
        EXPECT_EQ("hosT", hosts[hosts_in_primary_source-1]->getHostname());
    }

    // Select hosts only from the alternate sources.
    hosts = HostMgr::instance().getAllbyHostname4("host", SubnetID(1), HostMgrOperationTarget::ALTERNATE_SOURCES);
    EXPECT_EQ(2 - hosts_in_primary_source, hosts.size());
    if (!is_first_source_primary) {
        EXPECT_EQ("Host", hosts[0]->getHostname());
    }
    if (!is_second_source_primary) {
        EXPECT_EQ("hosT", hosts[2 - hosts_in_primary_source - 1]->getHostname());
    }

    // Select hosts for an unspecified source.
    hosts = HostMgr::instance().getAllbyHostname4("host", SubnetID(1), HostMgrOperationTarget::UNSPECIFIED_SOURCE);
    EXPECT_EQ(0, hosts.size());
}

void
HostMgrTest::testGetAllbyHostnameSubnet6(BaseHostDataSource& data_source1,
                                         BaseHostDataSource& data_source2) {
    // Initially, no reservations should be present.
    ConstHostCollection hosts =
        HostMgr::instance().getAllbyHostname6("host", SubnetID(1));
    ASSERT_TRUE(hosts.empty());

    // Add two reservations with the same hostname.
    HostPtr host1(new Host(duids_[0]->toText(), "duid",
                           SubnetID(1), SubnetID(1),
                           IOAddress::IPV4_ZERO_ADDRESS()));
    host1->addReservation(IPv6Resrv(IPv6Resrv::TYPE_NA,
                                    IOAddress("2001:db8:1::5"), 128));
    host1->setHostname("Host");
    data_source1.add(host1);
    HostPtr host2(new Host(duids_[1]->toText(), "duid",
                           SubnetID(1), SubnetID(1),
                           IOAddress::IPV4_ZERO_ADDRESS()));
    host2->addReservation(IPv6Resrv(IPv6Resrv::TYPE_NA,
                                    IOAddress("2001:db8:1::6"), 128));
    host2->setHostname("hosT");
    data_source2.add(host2);

    CfgMgr::instance().commit();

    // If there non-matching hostname is specified, nothing should be
    // returned.
    hosts = HostMgr::instance().getAllbyHostname6("foobar", SubnetID(1));
    EXPECT_TRUE(hosts.empty());

    // If there non-matching subnet is specified, nothing should be
    // returned.
    hosts = HostMgr::instance().getAllbyHostname6("host", SubnetID(10));
    EXPECT_TRUE(hosts.empty());

    // For the correct hostname, there should be two reservations.
    hosts = HostMgr::instance().getAllbyHostname6("host", SubnetID(1));
    ASSERT_EQ(2, hosts.size());

    // Make sure that subnet is correct.
    EXPECT_EQ(1, hosts[0]->getIPv6SubnetID());
    EXPECT_EQ(1, hosts[1]->getIPv6SubnetID());

    // Make sure that two different hosts were returned.
    EXPECT_TRUE(hosts[0]->hasReservation(
                IPv6Resrv(IPv6Resrv::TYPE_NA, IOAddress("2001:db8:1::5"))));
    EXPECT_TRUE(hosts[1]->hasReservation(
                IPv6Resrv(IPv6Resrv::TYPE_NA, IOAddress("2001:db8:1::6"))));

    // Make sure that hostname is correct including its case.
    EXPECT_EQ("Host", hosts[0]->getHostname());
    EXPECT_EQ("hosT", hosts[1]->getHostname());

    // Make sure that the operation target is supported.
    bool is_first_source_primary = isPrimaryDataSource(data_source1);
    bool is_second_source_primary = isPrimaryDataSource(data_source2);
    size_t hosts_in_primary_source = is_first_source_primary + is_second_source_primary;

    // Select hosts only from the primary source.
    hosts = HostMgr::instance().getAllbyHostname6("host", SubnetID(1), HostMgrOperationTarget::PRIMARY_SOURCE);
    EXPECT_EQ(hosts_in_primary_source, hosts.size());
    if (is_first_source_primary) {
        EXPECT_TRUE(hosts[0]->hasReservation(
                IPv6Resrv(IPv6Resrv::TYPE_NA, IOAddress("2001:db8:1::5"))));
    }
    if (is_second_source_primary) {
        EXPECT_TRUE(hosts[hosts_in_primary_source-1]->hasReservation(
                IPv6Resrv(IPv6Resrv::TYPE_NA, IOAddress("2001:db8:1::6"))));
    }

    // Select hosts only from the alternate sources.
    hosts = HostMgr::instance().getAllbyHostname6("host", SubnetID(1), HostMgrOperationTarget::ALTERNATE_SOURCES);
    EXPECT_EQ(2 - hosts_in_primary_source, hosts.size());
    if (!is_first_source_primary) {
        EXPECT_TRUE(hosts[0]->hasReservation(
                IPv6Resrv(IPv6Resrv::TYPE_NA, IOAddress("2001:db8:1::5"))));
    }
    if (!is_second_source_primary) {
        EXPECT_TRUE(hosts[2 - hosts_in_primary_source - 1]->hasReservation(
                IPv6Resrv(IPv6Resrv::TYPE_NA, IOAddress("2001:db8:1::6"))));
    }

    // Select hosts for an unspecified source.
    hosts = HostMgr::instance().getAllbyHostname6("host", SubnetID(1), HostMgrOperationTarget::UNSPECIFIED_SOURCE);
    EXPECT_EQ(0, hosts.size());
}

void
HostMgrTest::testGetPage4(bool use_database) {
    BaseHostDataSource& data_source1 = *getCfgHosts();
    BaseHostDataSource& data_source2 = HostMgr::instance();

    // Initially, no reservations should be present.
    size_t idx(0);
    HostPageSize page_size(10);
    ConstHostCollection hosts =
        HostMgr::instance().getPage4(SubnetID(1), idx, 0, page_size);
    ASSERT_TRUE(hosts.empty());
    if (use_database) {
        EXPECT_EQ(2, idx);
    } else {
        EXPECT_EQ(1, idx);
    }

    // Add two reservations for the same subnet.
    addHost4(data_source1, hwaddrs_[0], SubnetID(1), IOAddress("192.0.2.5"));
    addHost4(use_database ? data_source2 : data_source1,
             hwaddrs_[1], SubnetID(1), IOAddress("192.0.2.6"));

    CfgMgr::instance().commit();

    // If there non-matching subnet is specified, nothing should be returned.
    idx = 0;
    hosts = HostMgr::instance().getPage4(SubnetID(100), idx, 0, page_size);
    ASSERT_TRUE(hosts.empty());

    // For the correct subnet, there should be two reservations.
    idx = 0;
    hosts = HostMgr::instance().getPage4(SubnetID(1), idx, 0, page_size);
    if (use_database) {
        ASSERT_EQ(1, hosts.size());
    } else {
        ASSERT_EQ(2, hosts.size());
    }

    // Make sure that returned values are correct.
    EXPECT_EQ(1, hosts[0]->getIPv4SubnetID());
    EXPECT_EQ("192.0.2.5", hosts[0]->getIPv4Reservation().toText());
    if (!use_database) {
        EXPECT_EQ(1, hosts[1]->getIPv4SubnetID());
        EXPECT_EQ("192.0.2.6", hosts[1]->getIPv4Reservation().toText());

        // Check it was the last page.
        uint64_t hid = hosts[1]->getHostId();
        hosts = HostMgr::instance().getPage4(SubnetID(1), idx, hid, page_size);
        ASSERT_EQ(0, hosts.size());
        idx = 1;
        hosts = HostMgr::instance().getPage4(SubnetID(1), idx, 0, page_size);
        ASSERT_EQ(0, hosts.size());
    }

    if (use_database) {
        uint64_t hid = hosts[0]->getHostId();
        ASSERT_NE(0, hid);
        ASSERT_EQ(0, idx);
        hosts = HostMgr::instance().getPage4(SubnetID(1), idx, hid, page_size);
        ASSERT_EQ(1, hosts.size());
        ASSERT_NE(0, idx);
        EXPECT_EQ(1, hosts[0]->getIPv4SubnetID());
        EXPECT_EQ("192.0.2.6", hosts[0]->getIPv4Reservation().toText());

        // Alternate way to use the database.
        idx = 1;
        hosts = HostMgr::instance().getPage4(SubnetID(1), idx, 0, page_size);
        ASSERT_EQ(1, hosts.size());
        EXPECT_EQ(1, hosts[0]->getIPv4SubnetID());
        EXPECT_EQ("192.0.2.6", hosts[0]->getIPv4Reservation().toText());

        // Check it was the last page.
        hid = hosts[0]->getHostId();
        ASSERT_NE(0, hid);
        hosts = HostMgr::instance().getPage4(SubnetID(1), idx, hid, page_size);
        ASSERT_EQ(0, hosts.size());
        idx = 2;
        hosts = HostMgr::instance().getPage4(SubnetID(1), idx, 0, page_size);
        ASSERT_EQ(0, hosts.size());
    }
}

void
HostMgrTest::testGetPage6(bool use_database) {
    BaseHostDataSource& data_source1 = *getCfgHosts();
    BaseHostDataSource& data_source2 = HostMgr::instance();

    // Initially, no reservations should be present.
    size_t idx(0);
    HostPageSize page_size(10);
    ConstHostCollection hosts =
        HostMgr::instance().getPage6(SubnetID(1), idx, 0, page_size);
    ASSERT_TRUE(hosts.empty());
    if (use_database) {
        EXPECT_EQ(2, idx);
    } else {
        EXPECT_EQ(1, idx);
    }

    // Add two reservations for the same subnet.
    addHost6(data_source1, duids_[0], SubnetID(1), IOAddress("2001:db8:1::5"));
    addHost6(use_database ? data_source2 : data_source1,
             duids_[1], SubnetID(1), IOAddress("2001:db8:1::6"));

    CfgMgr::instance().commit();

    // If there non-matching subnet is specified, nothing should be returned.
    idx = 0;
    hosts = HostMgr::instance().getPage6(SubnetID(100), idx, 0, page_size);
    ASSERT_TRUE(hosts.empty());

    // For the correct subnet, there should be two reservations.
    idx = 0;
    hosts = HostMgr::instance().getPage6(SubnetID(1), idx, 0, page_size);
    if (use_database) {
        ASSERT_EQ(1, hosts.size());
    } else {
        ASSERT_EQ(2, hosts.size());
    }

    // Make sure that returned values are correct.
    EXPECT_EQ(1, hosts[0]->getIPv6SubnetID());
    EXPECT_TRUE(hosts[0]->hasReservation(
                IPv6Resrv(IPv6Resrv::TYPE_NA, IOAddress("2001:db8:1::5"))));
    if (!use_database) {
        EXPECT_EQ(1, hosts[1]->getIPv6SubnetID());
        EXPECT_TRUE(hosts[1]->hasReservation(
                    IPv6Resrv(IPv6Resrv::TYPE_NA, IOAddress("2001:db8:1::6"))));

        // Check it was the last page.
        uint64_t hid = hosts[1]->getHostId();
        hosts = HostMgr::instance().getPage6(SubnetID(1), idx, hid, page_size);
        ASSERT_EQ(0, hosts.size());
        idx = 1;
        hosts = HostMgr::instance().getPage6(SubnetID(1), idx, 0, page_size);
        ASSERT_EQ(0, hosts.size());
    }

    if (use_database) {
        uint64_t hid = hosts[0]->getHostId();
        ASSERT_NE(0, hid);
        ASSERT_EQ(0, idx);
        hosts = HostMgr::instance().getPage6(SubnetID(1), idx, hid, page_size);
        ASSERT_EQ(1, hosts.size());
        ASSERT_NE(0, idx);
        EXPECT_EQ(1, hosts[0]->getIPv6SubnetID());
        EXPECT_TRUE(hosts[0]->hasReservation(
                    IPv6Resrv(IPv6Resrv::TYPE_NA, IOAddress("2001:db8:1::6"))));

        // Alternate way to use the database.
        idx = 1;
        hosts = HostMgr::instance().getPage6(SubnetID(1), idx, 0, page_size);
        ASSERT_EQ(1, hosts.size());
        EXPECT_EQ(1, hosts[0]->getIPv6SubnetID());
        EXPECT_TRUE(hosts[0]->hasReservation(
                    IPv6Resrv(IPv6Resrv::TYPE_NA, IOAddress("2001:db8:1::6"))));

        // Check it was the last page.
        hid = hosts[0]->getHostId();
        ASSERT_NE(0, hid);
        hosts = HostMgr::instance().getPage6(SubnetID(1), idx, hid, page_size);
        ASSERT_EQ(0, hosts.size());
        idx = 2;
        hosts = HostMgr::instance().getPage6(SubnetID(1), idx, 0, page_size);
        ASSERT_EQ(0, hosts.size());
    }
}

void
HostMgrTest::testGetPage4All(bool use_database) {
    BaseHostDataSource& data_source1 = *getCfgHosts();
    BaseHostDataSource& data_source2 = HostMgr::instance();

    // Initially, no reservations should be present.
    size_t idx(0);
    HostPageSize page_size(10);
    ConstHostCollection hosts =
        HostMgr::instance().getPage4(idx, 0, page_size);
    ASSERT_TRUE(hosts.empty());
    if (use_database) {
        EXPECT_EQ(2, idx);
    } else {
        EXPECT_EQ(1, idx);
    }

    // Add two reservations.
    addHost4(data_source1, hwaddrs_[0], SubnetID(1), IOAddress("192.0.2.5"));
    addHost4(use_database ? data_source2 : data_source1,
             hwaddrs_[1], SubnetID(2), IOAddress("192.0.2.6"));

    CfgMgr::instance().commit();

    // There should be two reservations.
    idx = 0;
    hosts = HostMgr::instance().getPage4(idx, 0, page_size);
    if (use_database) {
        ASSERT_EQ(1, hosts.size());
    } else {
        ASSERT_EQ(2, hosts.size());
    }

    // Make sure that returned values are correct.
    EXPECT_EQ(1, hosts[0]->getIPv4SubnetID());
    EXPECT_EQ("192.0.2.5", hosts[0]->getIPv4Reservation().toText());
    if (!use_database) {
        EXPECT_EQ(2, hosts[1]->getIPv4SubnetID());
        EXPECT_EQ("192.0.2.6", hosts[1]->getIPv4Reservation().toText());

        // Check it was the last page.
        uint64_t hid = hosts[1]->getHostId();
        hosts = HostMgr::instance().getPage4(idx, hid, page_size);
        ASSERT_EQ(0, hosts.size());
        idx = 1;
        hosts = HostMgr::instance().getPage4(idx, 0, page_size);
        ASSERT_EQ(0, hosts.size());
    }

    if (use_database) {
        uint64_t hid = hosts[0]->getHostId();
        ASSERT_NE(0, hid);
        ASSERT_EQ(0, idx);
        hosts = HostMgr::instance().getPage4(idx, hid, page_size);
        ASSERT_EQ(1, hosts.size());
        ASSERT_NE(0, idx);
        EXPECT_EQ(2, hosts[0]->getIPv4SubnetID());
        EXPECT_EQ("192.0.2.6", hosts[0]->getIPv4Reservation().toText());

        // Alternate way to use the database.
        idx = 1;
        hosts = HostMgr::instance().getPage4(idx, 0, page_size);
        ASSERT_EQ(1, hosts.size());
        EXPECT_EQ(2, hosts[0]->getIPv4SubnetID());
        EXPECT_EQ("192.0.2.6", hosts[0]->getIPv4Reservation().toText());

        // Check it was the last page.
        hid = hosts[0]->getHostId();
        ASSERT_NE(0, hid);
        hosts = HostMgr::instance().getPage4(idx, hid, page_size);
        ASSERT_EQ(0, hosts.size());
        idx = 2;
        hosts = HostMgr::instance().getPage4(idx, 0, page_size);
        ASSERT_EQ(0, hosts.size());
    }
}

void
HostMgrTest::testGetPage6All(bool use_database) {
    BaseHostDataSource& data_source1 = *getCfgHosts();
    BaseHostDataSource& data_source2 = HostMgr::instance();

    // Initially, no reservations should be present.
    size_t idx(0);
    HostPageSize page_size(10);
    ConstHostCollection hosts =
        HostMgr::instance().getPage6(idx, 0, page_size);
    ASSERT_TRUE(hosts.empty());
    if (use_database) {
        EXPECT_EQ(2, idx);
    } else {
        EXPECT_EQ(1, idx);
    }

    // Add two reservations.
    addHost6(data_source1, duids_[0], SubnetID(1), IOAddress("2001:db8:1::5"));
    addHost6(use_database ? data_source2 : data_source1,
             duids_[1], SubnetID(2), IOAddress("2001:db8:1::6"));

    CfgMgr::instance().commit();

    // There should be two reservations.
    idx = 0;
    hosts = HostMgr::instance().getPage6(idx, 0, page_size);
    if (use_database) {
        ASSERT_EQ(1, hosts.size());
    } else {
        ASSERT_EQ(2, hosts.size());
    }

    // Make sure that returned values are correct.
    EXPECT_EQ(1, hosts[0]->getIPv6SubnetID());
    EXPECT_TRUE(hosts[0]->hasReservation(
                IPv6Resrv(IPv6Resrv::TYPE_NA, IOAddress("2001:db8:1::5"))));
    if (!use_database) {
        EXPECT_EQ(2, hosts[1]->getIPv6SubnetID());
        EXPECT_TRUE(hosts[1]->hasReservation(
                    IPv6Resrv(IPv6Resrv::TYPE_NA, IOAddress("2001:db8:1::6"))));

        // Check it was the last page.
        uint64_t hid = hosts[1]->getHostId();
        hosts = HostMgr::instance().getPage6(idx, hid, page_size);
        ASSERT_EQ(0, hosts.size());
        idx = 1;
        hosts = HostMgr::instance().getPage6(idx, 0, page_size);
        ASSERT_EQ(0, hosts.size());
    }

    if (use_database) {
        uint64_t hid = hosts[0]->getHostId();
        ASSERT_NE(0, hid);
        ASSERT_EQ(0, idx);
        hosts = HostMgr::instance().getPage6(idx, hid, page_size);
        ASSERT_EQ(1, hosts.size());
        ASSERT_NE(0, idx);
        EXPECT_EQ(2, hosts[0]->getIPv6SubnetID());
        EXPECT_TRUE(hosts[0]->hasReservation(
                    IPv6Resrv(IPv6Resrv::TYPE_NA, IOAddress("2001:db8:1::6"))));

        // Alternate way to use the database.
        idx = 1;
        hosts = HostMgr::instance().getPage6(idx, 0, page_size);
        ASSERT_EQ(1, hosts.size());
        EXPECT_EQ(2, hosts[0]->getIPv6SubnetID());
        EXPECT_TRUE(hosts[0]->hasReservation(
                    IPv6Resrv(IPv6Resrv::TYPE_NA, IOAddress("2001:db8:1::6"))));

        // Check it was the last page.
        hid = hosts[0]->getHostId();
        ASSERT_NE(0, hid);
        hosts = HostMgr::instance().getPage6(idx, hid, page_size);
        ASSERT_EQ(0, hosts.size());
        idx = 2;
        hosts = HostMgr::instance().getPage6(idx, 0, page_size);
        ASSERT_EQ(0, hosts.size());
    }
}

void
HostMgrTest::testGetAll4(BaseHostDataSource& data_source1,
                         BaseHostDataSource& data_source2) {
    // Initially, no hosts should be present.
    ConstHostCollection hosts =
        HostMgr::instance().getAll4(IOAddress("192.0.2.5"));
    ASSERT_TRUE(hosts.empty());

    // Add two hosts to different data sources.
    addHost4(data_source1, hwaddrs_[0], SubnetID(1), IOAddress("192.0.2.5"));
    addHost4(data_source2, hwaddrs_[1], SubnetID(10), IOAddress("192.0.2.5"));

    CfgMgr::instance().commit();

    // Retrieve all hosts, This should return hosts from both sources
    // in a single container.
    hosts = HostMgr::instance().getAll4(IOAddress("192.0.2.5"));
    ASSERT_EQ(2, hosts.size());

    // Make sure that IPv4 address is correct.
    EXPECT_EQ("192.0.2.5", hosts[0]->getIPv4Reservation().toText());
    EXPECT_EQ("192.0.2.5", hosts[1]->getIPv4Reservation().toText());

    // Make sure that two different hosts were returned.
    EXPECT_NE(hosts[0]->getIPv4SubnetID(), hosts[1]->getIPv4SubnetID());

    // Make sure that the operation target is supported.
    bool is_first_source_primary = isPrimaryDataSource(data_source1);
    bool is_second_source_primary = isPrimaryDataSource(data_source2);
    size_t hosts_in_primary_source = is_first_source_primary + is_second_source_primary;

    // Select hosts only from the primary source.
    hosts = HostMgr::instance().getAll4(IOAddress("192.0.2.5"), HostMgrOperationTarget::PRIMARY_SOURCE);
    EXPECT_EQ(hosts_in_primary_source, hosts.size());
    if (is_first_source_primary) {
        EXPECT_EQ("192.0.2.5", hosts[0]->getIPv4Reservation().toText());
    }
    if (is_second_source_primary) {
        EXPECT_EQ("192.0.2.5", hosts[hosts_in_primary_source-1]->getIPv4Reservation().toText());
    }

    // Select hosts only from the alternate sources.
    hosts = HostMgr::instance().getAll4(IOAddress("192.0.2.5"), HostMgrOperationTarget::ALTERNATE_SOURCES);
    EXPECT_EQ(2 - hosts_in_primary_source, hosts.size());
    if (!is_first_source_primary) {
        EXPECT_EQ("192.0.2.5", hosts[0]->getIPv4Reservation().toText());
    }
    if (!is_second_source_primary) {
        EXPECT_EQ("192.0.2.5", hosts[2 - hosts_in_primary_source - 1]->getIPv4Reservation().toText());
    }

    // Select hosts for an unspecified source.
    hosts = HostMgr::instance().getAll4(SubnetID(1), HostMgrOperationTarget::UNSPECIFIED_SOURCE);
    EXPECT_EQ(0, hosts.size());
}

void
HostMgrTest::testGet4(BaseHostDataSource& data_source) {
    // Initially, no host should be present.
    ConstHostPtr host =
        HostMgr::instance().get4(SubnetID(1), Host::IDENT_HWADDR,
                                 &hwaddrs_[0]->hwaddr_[0],
                                 hwaddrs_[0]->hwaddr_.size());
    ASSERT_FALSE(host);

    // Add new host to the database.
    addHost4(data_source, hwaddrs_[0], SubnetID(1), IOAddress("192.0.2.5"));

    CfgMgr::instance().commit();

    // Retrieve the host from the database and expect that the parameters match.
    host = HostMgr::instance().get4(SubnetID(1), Host::IDENT_HWADDR,
                                    &hwaddrs_[0]->hwaddr_[0],
                                    hwaddrs_[0]->hwaddr_.size());
    ASSERT_TRUE(host);
    EXPECT_EQ(1, host->getIPv4SubnetID());
    EXPECT_EQ("192.0.2.5", host->getIPv4Reservation().toText());

    // Make sure that the operation target is supported.
    // Select host by explicit, matched operation target.
    HostMgrOperationTarget operation_target = isPrimaryDataSource(data_source)
                                ? HostMgrOperationTarget::PRIMARY_SOURCE
                                : HostMgrOperationTarget::ALTERNATE_SOURCES;
    host = HostMgr::instance().get4(SubnetID(1), Host::IDENT_HWADDR,
                                    &hwaddrs_[0]->hwaddr_[0],
                                    hwaddrs_[0]->hwaddr_.size(),
                                    operation_target);
    ASSERT_TRUE(host);
    EXPECT_EQ(1, host->getIPv4SubnetID());
    EXPECT_EQ("192.0.2.5", host->getIPv4Reservation().toText());

    // Select host by explicit but unmatched operation target.
    operation_target = isPrimaryDataSource(data_source)
                                ? HostMgrOperationTarget::ALTERNATE_SOURCES
                                : HostMgrOperationTarget::PRIMARY_SOURCE;
    host = HostMgr::instance().get4(SubnetID(1), Host::IDENT_HWADDR,
                                    &hwaddrs_[0]->hwaddr_[0],
                                    hwaddrs_[0]->hwaddr_.size(),
                                    operation_target);
    ASSERT_FALSE(host);

    // Select host for an unspecified operation target.
    host = HostMgr::instance().get4(SubnetID(1), Host::IDENT_HWADDR,
                                    &hwaddrs_[0]->hwaddr_[0],
                                    hwaddrs_[0]->hwaddr_.size(),
                                    HostMgrOperationTarget::UNSPECIFIED_SOURCE);
    ASSERT_FALSE(host);
}

void
HostMgrTest::testGet4Any() {
    // Initially, no host should be present.
    ConstHostPtr host = HostMgr::instance().get4(SubnetID(1), Host::IDENT_DUID,
                                                 &duids_[0]->getDuid()[0],
                                                 duids_[0]->getDuid().size());
    ASSERT_FALSE(host);
    HostMgr::instance().get4Any(SubnetID(1), Host::IDENT_DUID,
                                &duids_[0]->getDuid()[0],
                                duids_[0]->getDuid().size());
    ASSERT_FALSE(host);

    // Add new host to the database.
    HostPtr new_host(new Host(duids_[0]->toText(), "duid", SubnetID(1),
                              SUBNET_ID_UNUSED, IOAddress("192.0.2.5")));
    // Abuse of the server's configuration.
    getCfgHosts()->add(new_host);

    CfgMgr::instance().commit();

    // Retrieve the host from the database and expect that the parameters match.
    host = HostMgr::instance().get4(SubnetID(1), Host::IDENT_DUID,
                                    &duids_[0]->getDuid()[0],
                                    duids_[0]->getDuid().size());
    ASSERT_TRUE(host);
    EXPECT_EQ(1, host->getIPv4SubnetID());
    EXPECT_EQ("192.0.2.5", host->getIPv4Reservation().toText());

    // Set the negative cache flag on the host.
    new_host->setNegative(true);

    // get4 is not supposed to get it.
    host = HostMgr::instance().get4(SubnetID(1), Host::IDENT_DUID,
                                    &duids_[0]->getDuid()[0],
                                    duids_[0]->getDuid().size());
    EXPECT_FALSE(host);

    // But get4Any should.
    host = HostMgr::instance().get4Any(SubnetID(1), Host::IDENT_DUID,
                                       &duids_[0]->getDuid()[0],
                                       duids_[0]->getDuid().size());
    ASSERT_TRUE(host);
    EXPECT_EQ(1, host->getIPv4SubnetID());
    EXPECT_EQ("192.0.2.5", host->getIPv4Reservation().toText());
    EXPECT_TRUE(host->getNegative());

    // To be sure. Note we use the CfgHosts source so only this
    // get4 overload works.
    host = HostMgr::instance().get4(SubnetID(1), Host::IDENT_DUID,
                                    &duids_[0]->getDuid()[0],
                                    duids_[0]->getDuid().size());
    EXPECT_FALSE(host);

    // Make sure that the operation target is supported.
    // Select host by explicit, matched operation target.
    host = HostMgr::instance().get4Any(SubnetID(1), Host::IDENT_DUID,
                                       &duids_[0]->getDuid()[0],
                                       duids_[0]->getDuid().size(),
                                       HostMgrOperationTarget::PRIMARY_SOURCE);
    ASSERT_TRUE(host);
    EXPECT_EQ(1, host->getIPv4SubnetID());
    EXPECT_EQ("192.0.2.5", host->getIPv4Reservation().toText());
    EXPECT_TRUE(host->getNegative());

    // Select host by explicit but unmatched operation target.
    host = HostMgr::instance().get4Any(SubnetID(1), Host::IDENT_DUID,
                                       &duids_[0]->getDuid()[0],
                                       duids_[0]->getDuid().size(),
                                       HostMgrOperationTarget::ALTERNATE_SOURCES);
    ASSERT_FALSE(host);

    // Select host for an unspecified operation target.
    host = HostMgr::instance().get4Any(SubnetID(1), Host::IDENT_DUID,
                                       &duids_[0]->getDuid()[0],
                                       duids_[0]->getDuid().size(),
                                       HostMgrOperationTarget::UNSPECIFIED_SOURCE);
    ASSERT_FALSE(host);
}

void
HostMgrTest::testGet6(BaseHostDataSource& data_source) {
    // Initially, no host should be present.
    ConstHostPtr host =
        HostMgr::instance().get6(SubnetID(2), Host::IDENT_DUID,
                                 &duids_[0]->getDuid()[0],
                                 duids_[0]->getDuid().size());
    ASSERT_FALSE(host);

    // Add new host to the database.
    addHost6(data_source, duids_[0], SubnetID(2), IOAddress("2001:db8:1::1"));

    CfgMgr::instance().commit();

    // Retrieve the host from the database and expect that the parameters match.
    host = HostMgr::instance().get6(SubnetID(2), Host::IDENT_DUID,
                                    &duids_[0]->getDuid()[0],
                                    duids_[0]->getDuid().size());
    ASSERT_TRUE(host);
    EXPECT_EQ(2, host->getIPv6SubnetID());
    EXPECT_TRUE(host->hasReservation(IPv6Resrv(IPv6Resrv::TYPE_NA,
                                               IOAddress("2001:db8:1::1"))));

    // Make sure that the operation target is supported.
    // Select host by explicit, matched operation target.
    HostMgrOperationTarget operation_target = isPrimaryDataSource(data_source)
                                ? HostMgrOperationTarget::PRIMARY_SOURCE
                                : HostMgrOperationTarget::ALTERNATE_SOURCES;
    host = HostMgr::instance().get6(SubnetID(2), Host::IDENT_DUID,
                                    &duids_[0]->getDuid()[0],
                                    duids_[0]->getDuid().size(),
                                    operation_target);
    ASSERT_TRUE(host);
    EXPECT_EQ(2, host->getIPv6SubnetID());
    EXPECT_TRUE(host->hasReservation(IPv6Resrv(IPv6Resrv::TYPE_NA,
                                               IOAddress("2001:db8:1::1"))));

    // Select host by explicit but unmatched operation target.
    operation_target = isPrimaryDataSource(data_source)
                                ? HostMgrOperationTarget::ALTERNATE_SOURCES
                                : HostMgrOperationTarget::PRIMARY_SOURCE;
    host = HostMgr::instance().get6(SubnetID(2), Host::IDENT_DUID,
                                    &duids_[0]->getDuid()[0],
                                    duids_[0]->getDuid().size(),
                                    operation_target);
    ASSERT_FALSE(host);

    // Select host for an unspecified operation target.
    host = HostMgr::instance().get6(SubnetID(2), Host::IDENT_DUID,
                                    &duids_[0]->getDuid()[0],
                                    duids_[0]->getDuid().size(),
                                    HostMgrOperationTarget::UNSPECIFIED_SOURCE);
    ASSERT_FALSE(host);
}

void
HostMgrTest::testGet6Any() {
    // Initially, no host should be present.
    ConstHostPtr host = HostMgr::instance().get6(SubnetID(2),
                                                 Host::IDENT_HWADDR,
                                                 &hwaddrs_[0]->hwaddr_[0],
                                                 hwaddrs_[0]->hwaddr_.size());
    ASSERT_FALSE(host);
    host = HostMgr::instance().get6Any(SubnetID(2), Host::IDENT_HWADDR,
                                       &hwaddrs_[0]->hwaddr_[0],
                                       hwaddrs_[0]->hwaddr_.size());
    ASSERT_FALSE(host);

    // Add new host to the database.
    HostPtr new_host(new Host(hwaddrs_[0]->toText(false), "hw-address",
                              SubnetID(1), SubnetID(2),
                              IOAddress::IPV4_ZERO_ADDRESS()));
    new_host->addReservation(IPv6Resrv(IPv6Resrv::TYPE_NA,
                                       IOAddress("2001:db8:1::1"), 128));
    // Abuse of the server's configuration.
    getCfgHosts()->add(new_host);

    CfgMgr::instance().commit();

    // Retrieve the host from the database and expect that the parameters match.
    host = HostMgr::instance().get6(SubnetID(2), Host::IDENT_HWADDR,
                                    &hwaddrs_[0]->hwaddr_[0],
                                    hwaddrs_[0]->hwaddr_.size());
    ASSERT_TRUE(host);
    EXPECT_EQ(2, host->getIPv6SubnetID());
    EXPECT_TRUE(host->hasReservation(IPv6Resrv(IPv6Resrv::TYPE_NA,
                                               IOAddress("2001:db8:1::1"))));

    // Set the negative cache flag on the host.
    new_host->setNegative(true);

    // get6 is not supposed to get it.
    host = HostMgr::instance().get6(SubnetID(2), Host::IDENT_HWADDR,
                                    &hwaddrs_[0]->hwaddr_[0],
                                    hwaddrs_[0]->hwaddr_.size());
    EXPECT_FALSE(host);

    // But get6Any should.
    host = HostMgr::instance().get6Any(SubnetID(2), Host::IDENT_HWADDR,
                                       &hwaddrs_[0]->hwaddr_[0],
                                       hwaddrs_[0]->hwaddr_.size());
    ASSERT_TRUE(host);
    EXPECT_EQ(2, host->getIPv6SubnetID());
    EXPECT_TRUE(host->hasReservation(IPv6Resrv(IPv6Resrv::TYPE_NA,
                                               IOAddress("2001:db8:1::1"))));
    EXPECT_TRUE(host->getNegative());

    // To be sure. Note we use the CfgHosts source so only this
    // get6 overload works.
    host = HostMgr::instance().get6(SubnetID(2), Host::IDENT_HWADDR,
                                    &hwaddrs_[0]->hwaddr_[0],
                                    hwaddrs_[0]->hwaddr_.size());
    EXPECT_FALSE(host);

    // Make sure that the operation target is supported.
    // Select host by explicit, matched operation target.
    host = HostMgr::instance().get6Any(SubnetID(2), Host::IDENT_HWADDR,
                                       &hwaddrs_[0]->hwaddr_[0],
                                       hwaddrs_[0]->hwaddr_.size(),
                                       HostMgrOperationTarget::PRIMARY_SOURCE);
    ASSERT_TRUE(host);
    EXPECT_EQ(2, host->getIPv6SubnetID());
    EXPECT_TRUE(host->hasReservation(IPv6Resrv(IPv6Resrv::TYPE_NA,
                                               IOAddress("2001:db8:1::1"))));

    // Select host by explicit but unmatched operation target.
    host = HostMgr::instance().get6Any(SubnetID(2), Host::IDENT_HWADDR,
                                       &hwaddrs_[0]->hwaddr_[0],
                                       hwaddrs_[0]->hwaddr_.size(),
                                       HostMgrOperationTarget::ALTERNATE_SOURCES);
    ASSERT_FALSE(host);

    // Select host for an unspecified operation target.
    host = HostMgr::instance().get6Any(SubnetID(2), Host::IDENT_HWADDR,
                                       &hwaddrs_[0]->hwaddr_[0],
                                       hwaddrs_[0]->hwaddr_.size(),
                                       HostMgrOperationTarget::UNSPECIFIED_SOURCE);
    ASSERT_FALSE(host);
}

void
HostMgrTest::testGet6ByPrefix(BaseHostDataSource& data_source1,
                              BaseHostDataSource& data_source2) {
    ConstHostPtr host = HostMgr::instance().get6(IOAddress("2001:db8:1::"), 64);
    ASSERT_FALSE(host);

    // Add a host with a reservation for a prefix 2001:db8:1::/64.
    addHost6(data_source1, duids_[0], SubnetID(2), IOAddress("2001:db8:1::"), 64);

    // Add another host having a reservation for prefix 2001:db8:1:0:6::/72.
    addHost6(data_source2, duids_[1], SubnetID(3), IOAddress("2001:db8:1:0:6::"), 80);

    CfgMgr::instance().commit();

    // Retrieve first reservation.
    host = HostMgr::instance().get6(IOAddress("2001:db8:1::"), 64);
    ASSERT_TRUE(host);
    EXPECT_TRUE(host->hasReservation(IPv6Resrv(IPv6Resrv::TYPE_PD,
                                               IOAddress("2001:db8:1::"), 64)));

    // Make sure the first reservation is not retrieved when the prefix
    // length is incorrect.
    host = HostMgr::instance().get6(IOAddress("2001:db8:1::"), 72);
    EXPECT_FALSE(host);

    // Retrieve second reservation.
    host = HostMgr::instance().get6(IOAddress("2001:db8:1:0:6::"), 80);
    ASSERT_TRUE(host);
    EXPECT_TRUE(host->hasReservation(IPv6Resrv(IPv6Resrv::TYPE_PD,
                                               IOAddress("2001:db8:1:0:6::"), 80)));

    // Make sure the second reservation is not retrieved when the prefix
    // length is incorrect.
    host = HostMgr::instance().get6(IOAddress("2001:db8:1:0:6::"), 64);
    EXPECT_FALSE(host);

    // Make sure that the operation target is supported.
    bool is_first_source_primary = isPrimaryDataSource(data_source1);
    bool is_second_source_primary = isPrimaryDataSource(data_source2);

    // Select host only from the primary source.
    host = HostMgr::instance().get6(IOAddress("2001:db8:1::"), 64, HostMgrOperationTarget::PRIMARY_SOURCE);
    if (is_first_source_primary) {
        EXPECT_TRUE(host);
        EXPECT_TRUE(host->hasReservation(IPv6Resrv(IPv6Resrv::TYPE_PD,
                                               IOAddress("2001:db8:1::"), 64)));
    } else {
        EXPECT_FALSE(host);
    }

    host = HostMgr::instance().get6(IOAddress("2001:db8:1:0:6::"), 80, HostMgrOperationTarget::PRIMARY_SOURCE);
    if (is_second_source_primary) {
        EXPECT_TRUE(host);
        EXPECT_TRUE(host->hasReservation(IPv6Resrv(IPv6Resrv::TYPE_PD,
                                         IOAddress("2001:db8:1:0:6::"), 80)));
    } else {
        EXPECT_FALSE(host);
    }

    // Select hosts only from the alternate sources.
    host = HostMgr::instance().get6(IOAddress("2001:db8:1::"), 64, HostMgrOperationTarget::ALTERNATE_SOURCES);
    if (!is_first_source_primary) {
        EXPECT_TRUE(host);
        EXPECT_TRUE(host->hasReservation(IPv6Resrv(IPv6Resrv::TYPE_PD,
                                               IOAddress("2001:db8:1::"), 64)));
    } else {
        EXPECT_FALSE(host);
    }

    host = HostMgr::instance().get6(IOAddress("2001:db8:1:0:6::"), 80, HostMgrOperationTarget::ALTERNATE_SOURCES);
    if (!is_second_source_primary) {
        EXPECT_TRUE(host);
        EXPECT_TRUE(host->hasReservation(IPv6Resrv(IPv6Resrv::TYPE_PD,
                                         IOAddress("2001:db8:1:0:6::"), 80)));
    } else {
        EXPECT_FALSE(host);
    }

    // Select hosts for an unspecified source.
    host = HostMgr::instance().get6(IOAddress("2001:db8:1:0:6::"), 80, HostMgrOperationTarget::UNSPECIFIED_SOURCE);
    EXPECT_FALSE(host);
}

void
HostMgrTest::testGetAll4BySubnetIP(BaseHostDataSource& data_source1,
                                   BaseHostDataSource& data_source2) {
    // Set the mode of operation with multiple reservations for the same
    // IP address.
    ASSERT_TRUE(HostMgr::instance().setIPReservationsUnique(false));
    CfgMgr::instance().getStagingCfg()->getCfgHosts()->setIPReservationsUnique(false);

    // Initially, no reservations should be present.
    ConstHostCollection hosts = HostMgr::instance().getAll4(SubnetID(1),
                                                            IOAddress("192.0.2.5"));
    ASSERT_TRUE(hosts.empty());

    // Add two reservations for the same subnet and IP address.
    addHost4(data_source1, hwaddrs_[0], SubnetID(1), IOAddress("192.0.2.5"));
    addHost4(data_source2, hwaddrs_[1], SubnetID(1), IOAddress("192.0.2.5"));

    CfgMgr::instance().commit();

    // If there non-matching subnet is specified, nothing should be returned.
    hosts = HostMgr::instance().getAll4(SubnetID(100), IOAddress("192.0.2.5"));
    ASSERT_TRUE(hosts.empty());

    // For the correct subnet, there should be two reservations.
    hosts = HostMgr::instance().getAll4(SubnetID(1), IOAddress("192.0.2.5"));
    ASSERT_EQ(2, hosts.size());

    // Make sure that subnet is correct.
    EXPECT_EQ(1, hosts[0]->getIPv4SubnetID());
    EXPECT_EQ(1, hosts[1]->getIPv4SubnetID());

    // Make sure that two hosts were returned with different identifiers
    // but the same address.
    EXPECT_NE(hosts[0]->getIdentifierAsText(), hosts[1]->getIdentifierAsText());
    EXPECT_EQ("192.0.2.5", hosts[0]->getIPv4Reservation().toText());
    EXPECT_EQ("192.0.2.5", hosts[1]->getIPv4Reservation().toText());

    // Make sure that the operation target is supported.
    bool is_first_source_primary = isPrimaryDataSource(data_source1);
    bool is_second_source_primary = isPrimaryDataSource(data_source2);
    size_t hosts_in_primary_source = is_first_source_primary + is_second_source_primary;

    // Select hosts only from the primary source.
    hosts = HostMgr::instance().getAll4(SubnetID(1), IOAddress("192.0.2.5"), HostMgrOperationTarget::PRIMARY_SOURCE);
    EXPECT_EQ(hosts_in_primary_source, hosts.size());
    if (is_first_source_primary) {
        EXPECT_EQ("192.0.2.5", hosts[0]->getIPv4Reservation().toText());
    }
    if (is_second_source_primary) {
        EXPECT_EQ("192.0.2.5", hosts[hosts_in_primary_source-1]->getIPv4Reservation().toText());
    }

    // Select hosts only from the alternate sources.
    hosts = HostMgr::instance().getAll4(SubnetID(1), IOAddress("192.0.2.5"), HostMgrOperationTarget::ALTERNATE_SOURCES);
    EXPECT_EQ(2 - hosts_in_primary_source, hosts.size());
    if (!is_first_source_primary) {
        EXPECT_EQ("192.0.2.5", hosts[0]->getIPv4Reservation().toText());
    }
    if (!is_second_source_primary) {
        EXPECT_EQ("192.0.2.5", hosts[2 - hosts_in_primary_source - 1]->getIPv4Reservation().toText());
    }

    // Select hosts for an unspecified source.
    hosts = HostMgr::instance().getAll4(SubnetID(1), HostMgrOperationTarget::UNSPECIFIED_SOURCE);
    EXPECT_EQ(0, hosts.size());
}

void
HostMgrTest::testGetAll6BySubnetIP(BaseHostDataSource& data_source1,
                                   BaseHostDataSource& data_source2) {
    // Set the mode of operation with multiple reservations for the same
    // IP address.
    ASSERT_TRUE(HostMgr::instance().setIPReservationsUnique(false));
    CfgMgr::instance().getStagingCfg()->getCfgHosts()->setIPReservationsUnique(false);

    // Initially, no reservations should be present.
    ConstHostCollection hosts = HostMgr::instance().getAll6(SubnetID(1),
                                                            IOAddress("2001:db8:1::5"));
    ASSERT_TRUE(hosts.empty());

    // Add two reservations for the same subnet.
    addHost6(data_source1, duids_[0], SubnetID(1), IOAddress("2001:db8:1::5"));
    addHost6(data_source2, duids_[1], SubnetID(1), IOAddress("2001:db8:1::5"));

    CfgMgr::instance().commit();

    // If there non-matching subnet is specified, nothing should be returned.
    hosts = HostMgr::instance().getAll6(SubnetID(100), IOAddress("2001:db8:1::5"));
    ASSERT_TRUE(hosts.empty());

    // For the correct subnet, there should be two reservations.
    hosts = HostMgr::instance().getAll6(SubnetID(1), IOAddress("2001:db8:1::5"));
    ASSERT_EQ(2, hosts.size());

    // Make sure that subnet is correct.
    EXPECT_EQ(1, hosts[0]->getIPv6SubnetID());
    EXPECT_EQ(1, hosts[1]->getIPv6SubnetID());

    // Make sure that two hosts were returned with different identifiers
    // but the same address.
    EXPECT_NE(hosts[0]->getIdentifierAsText(), hosts[1]->getIdentifierAsText());
    EXPECT_TRUE(hosts[0]->hasReservation(
                IPv6Resrv(IPv6Resrv::TYPE_NA, IOAddress("2001:db8:1::5"))));
    EXPECT_TRUE(hosts[1]->hasReservation(
                IPv6Resrv(IPv6Resrv::TYPE_NA, IOAddress("2001:db8:1::5"))));

    // Make sure that the operation target is supported.
    bool is_first_source_primary = isPrimaryDataSource(data_source1);
    bool is_second_source_primary = isPrimaryDataSource(data_source2);
    size_t hosts_in_primary_source = is_first_source_primary + is_second_source_primary;

    // Select hosts only from the primary source.
    hosts = HostMgr::instance().getAll6(SubnetID(1), IOAddress("2001:db8:1::5"), HostMgrOperationTarget::PRIMARY_SOURCE);
    EXPECT_EQ(hosts_in_primary_source, hosts.size());
    if (is_first_source_primary) {
        EXPECT_TRUE(hosts[0]->hasReservation(
                IPv6Resrv(IPv6Resrv::TYPE_NA, IOAddress("2001:db8:1::5"))));
    }
    if (is_second_source_primary) {
        EXPECT_TRUE(hosts[hosts_in_primary_source - 1]->hasReservation(
                IPv6Resrv(IPv6Resrv::TYPE_NA, IOAddress("2001:db8:1::5"))));
    }

    // Select hosts only from the alternate sources.
    hosts = HostMgr::instance().getAll6(SubnetID(1), IOAddress("2001:db8:1::5"), HostMgrOperationTarget::ALTERNATE_SOURCES);
    EXPECT_EQ(2 - hosts_in_primary_source, hosts.size());
    if (!is_first_source_primary) {
        EXPECT_TRUE(hosts[0]->hasReservation(
                IPv6Resrv(IPv6Resrv::TYPE_NA, IOAddress("2001:db8:1::5"))));
    }
    if (!is_second_source_primary) {
        EXPECT_TRUE(hosts[2 - hosts_in_primary_source - 1]->hasReservation(
                IPv6Resrv(IPv6Resrv::TYPE_NA, IOAddress("2001:db8:1::5"))));
    }

    // Select hosts for an unspecified source.
    hosts = HostMgr::instance().getAll4(SubnetID(1), IOAddress("2001:db8:1::5"), HostMgrOperationTarget::UNSPECIFIED_SOURCE);
    EXPECT_EQ(0, hosts.size());
}

void
HostMgrTest::testGetAll6ByIP(BaseHostDataSource& data_source1, BaseHostDataSource& data_source2) {
    // Set the mode of operation with multiple reservations for the same
    // IP address.
    ASSERT_TRUE(HostMgr::instance().setIPReservationsUnique(false));
    CfgMgr::instance().getStagingCfg()->getCfgHosts()->setIPReservationsUnique(false);

    // Initially, no reservations should be present.
    ConstHostCollection hosts = HostMgr::instance().getAll6(SubnetID(1),
                                                            IOAddress("2001:db8:1::10"));
    ASSERT_TRUE(hosts.empty());

    // Prepare vectors of IPv6 address reservations for new hosts.
    std::vector<IOAddress> addresses1;
    std::vector<IOAddress> addresses2;
    addresses1.push_back(IOAddress("2001:db8:1::5"));
    addresses1.push_back(IOAddress("2001:db8:1::10"));
    addresses2.push_back(IOAddress("2001:db8:1::6"));
    addresses2.push_back(IOAddress("2001:db8:1::10"));

    // Add two hosts for the same subnet with 2 IPv6 addresses reservations per host.
    addHost6(data_source1, duids_[0], SubnetID(1), addresses1);
    addHost6(data_source2, duids_[1], SubnetID(1), addresses2);

    CfgMgr::instance().commit();

    // If a non-matching subnet is specified, nothing should be returned.
    hosts = HostMgr::instance().getAll6(SubnetID(100), IOAddress("2001:db8:1::5"));
    ASSERT_TRUE(hosts.empty());

    // For given IP there should be one reservation.
    hosts = HostMgr::instance().getAll6(IOAddress("2001:db8:1::5"));
    ASSERT_EQ(1, hosts.size());

    // For given IP there should be one reservation.
    hosts = HostMgr::instance().getAll6(IOAddress("2001:db8:1::6"));
    ASSERT_EQ(1, hosts.size());

    // For given IP there should be two reservations.
    hosts = HostMgr::instance().getAll6(IOAddress("2001:db8:1::10"));
    ASSERT_EQ(2, hosts.size());

    // Make sure that subnet is correct.
    EXPECT_EQ(1, hosts[0]->getIPv6SubnetID());
    EXPECT_EQ(1, hosts[1]->getIPv6SubnetID());

    // Make sure that all hosts were returned with different identifiers, and
    // they have expected reservations.
    EXPECT_NE(hosts[0]->getIdentifierAsText(), hosts[1]->getIdentifierAsText());
    EXPECT_TRUE(
        hosts[0]->hasReservation(IPv6Resrv(IPv6Resrv::TYPE_NA, IOAddress("2001:db8:1::10"))));
    EXPECT_TRUE(
        hosts[0]->hasReservation(IPv6Resrv(IPv6Resrv::TYPE_NA, IOAddress("2001:db8:1::5"))));
    EXPECT_TRUE(
        hosts[1]->hasReservation(IPv6Resrv(IPv6Resrv::TYPE_NA, IOAddress("2001:db8:1::10"))));
    EXPECT_TRUE(
        hosts[1]->hasReservation(IPv6Resrv(IPv6Resrv::TYPE_NA, IOAddress("2001:db8:1::6"))));

    // Make sure that the operation target is supported.
    bool is_first_source_primary = isPrimaryDataSource(data_source1);
    bool is_second_source_primary = isPrimaryDataSource(data_source2);
    size_t hosts_in_primary_source = is_first_source_primary + is_second_source_primary;

    // Select hosts only from the primary source.
    hosts = HostMgr::instance().getAll6(IOAddress("2001:db8:1::10"),
                                        HostMgrOperationTarget::PRIMARY_SOURCE);
    EXPECT_EQ(hosts_in_primary_source, hosts.size());
    if (is_first_source_primary) {
        EXPECT_TRUE(
            hosts[0]->hasReservation(IPv6Resrv(IPv6Resrv::TYPE_NA, IOAddress("2001:db8:1::10"))));
        EXPECT_TRUE(
            hosts[0]->hasReservation(IPv6Resrv(IPv6Resrv::TYPE_NA, IOAddress("2001:db8:1::5"))));
    }
    if (is_second_source_primary) {
        EXPECT_TRUE(hosts[hosts_in_primary_source - 1]->hasReservation(
            IPv6Resrv(IPv6Resrv::TYPE_NA, IOAddress("2001:db8:1::10"))));
        EXPECT_TRUE(hosts[hosts_in_primary_source - 1]->hasReservation(
            IPv6Resrv(IPv6Resrv::TYPE_NA, IOAddress("2001:db8:1::6"))));
    }

    // Select hosts only from the alternate sources.
    hosts = HostMgr::instance().getAll6(IOAddress("2001:db8:1::10"),
                                        HostMgrOperationTarget::ALTERNATE_SOURCES);
    EXPECT_EQ(2 - hosts_in_primary_source, hosts.size());
    if (!is_first_source_primary) {
        EXPECT_TRUE(
            hosts[0]->hasReservation(IPv6Resrv(IPv6Resrv::TYPE_NA, IOAddress("2001:db8:1::10"))));
        EXPECT_TRUE(
            hosts[0]->hasReservation(IPv6Resrv(IPv6Resrv::TYPE_NA, IOAddress("2001:db8:1::5"))));
    }
    if (!is_second_source_primary) {
        EXPECT_TRUE(hosts[2 - hosts_in_primary_source - 1]->hasReservation(
            IPv6Resrv(IPv6Resrv::TYPE_NA, IOAddress("2001:db8:1::10"))));
        EXPECT_TRUE(hosts[2 - hosts_in_primary_source - 1]->hasReservation(
            IPv6Resrv(IPv6Resrv::TYPE_NA, IOAddress("2001:db8:1::6"))));
    }

    // Select hosts for an unspecified source.
    hosts = HostMgr::instance().getAll4(IOAddress("2001:db8:1::10"),
                                        HostMgrOperationTarget::UNSPECIFIED_SOURCE);
    EXPECT_EQ(0, hosts.size());
}

void
HostMgrTest::testGetAll6ByIpPrefix(BaseHostDataSource& data_source1,
                                   BaseHostDataSource& data_source2) {
    // Set the mode of operation with multiple reservations for the same
    // IP address.
    ASSERT_TRUE(HostMgr::instance().setIPReservationsUnique(false));
    CfgMgr::instance().getStagingCfg()->getCfgHosts()->setIPReservationsUnique(false);

    // Initially, no reservations should be present.
    ConstHostCollection hosts = HostMgr::instance().getAll6(SubnetID(1),
                                                            IOAddress("2001:db8:1:10::"));
    ASSERT_TRUE(hosts.empty());

    // Prepare vectors of IPv6 prefix reservations for new hosts.
    std::vector<IOAddress> addresses1;
    std::vector<IOAddress> addresses2;
    addresses1.push_back(IOAddress("2001:db8:1:10::"));
    addresses1.push_back(IOAddress("2001:db8:1:11::"));
    addresses2.push_back(IOAddress("2001:db8:1:10::"));
    addresses2.push_back(IOAddress("2001:db8:1:12::"));

    // Add two hosts for the same subnet with 2 IPv6 prefix reservations per host.
    addHost6(data_source1, duids_[0], SubnetID(1), addresses1, 64);
    addHost6(data_source2, duids_[1], SubnetID(1), addresses2, 64);

    CfgMgr::instance().commit();

    // If a non-matching subnet is specified, nothing should be returned.
    hosts = HostMgr::instance().getAll6(SubnetID(100), IOAddress("2001:db8:1:10::"));
    ASSERT_TRUE(hosts.empty());

    // For given IP prefix there should be one reservation.
    hosts = HostMgr::instance().getAll6(IOAddress("2001:db8:1:11::"));
    ASSERT_EQ(1, hosts.size());

    // For given IP prefix there should be one reservation.
    hosts = HostMgr::instance().getAll6(IOAddress("2001:db8:1:12::"));
    ASSERT_EQ(1, hosts.size());

    // For given IP prefix there should be two reservations.
    hosts = HostMgr::instance().getAll6(IOAddress("2001:db8:1:10::"));
    ASSERT_EQ(2, hosts.size());

    // Make sure that subnet is correct.
    EXPECT_EQ(1, hosts[0]->getIPv6SubnetID());
    EXPECT_EQ(1, hosts[1]->getIPv6SubnetID());

    // Make sure that all hosts were returned with different identifiers, and
    // they have expected reservations.
    EXPECT_NE(hosts[0]->getIdentifierAsText(), hosts[1]->getIdentifierAsText());
    EXPECT_TRUE(
        hosts[0]->hasReservation(IPv6Resrv(IPv6Resrv::TYPE_PD, IOAddress("2001:db8:1:10::"), 64)));
    EXPECT_TRUE(
        hosts[0]->hasReservation(IPv6Resrv(IPv6Resrv::TYPE_PD, IOAddress("2001:db8:1:11::"), 64)));
    EXPECT_TRUE(
        hosts[1]->hasReservation(IPv6Resrv(IPv6Resrv::TYPE_PD, IOAddress("2001:db8:1:10::"), 64)));
    EXPECT_TRUE(
        hosts[1]->hasReservation(IPv6Resrv(IPv6Resrv::TYPE_PD, IOAddress("2001:db8:1:12::"), 64)));

    // Make sure that the operation target is supported.
    bool is_first_source_primary = isPrimaryDataSource(data_source1);
    bool is_second_source_primary = isPrimaryDataSource(data_source2);
    size_t hosts_in_primary_source = is_first_source_primary + is_second_source_primary;

    // Select hosts only from the primary source.
    hosts = HostMgr::instance().getAll6(IOAddress("2001:db8:1:10::"),
                                        HostMgrOperationTarget::PRIMARY_SOURCE);
    EXPECT_EQ(hosts_in_primary_source, hosts.size());
    if (is_first_source_primary) {
        EXPECT_TRUE(hosts[0]->hasReservation(
            IPv6Resrv(IPv6Resrv::TYPE_PD, IOAddress("2001:db8:1:10::"), 64)));
        EXPECT_TRUE(hosts[0]->hasReservation(
            IPv6Resrv(IPv6Resrv::TYPE_PD, IOAddress("2001:db8:1:11::"), 64)));
    }
    if (is_second_source_primary) {
        EXPECT_TRUE(hosts[hosts_in_primary_source - 1]->hasReservation(
            IPv6Resrv(IPv6Resrv::TYPE_PD, IOAddress("2001:db8:1:10::"), 64)));
        EXPECT_TRUE(hosts[hosts_in_primary_source - 1]->hasReservation(
            IPv6Resrv(IPv6Resrv::TYPE_PD, IOAddress("2001:db8:1:12::"), 64)));
    }

    // Select hosts only from the alternate sources.
    hosts = HostMgr::instance().getAll6(IOAddress("2001:db8:1:10::"),
                                        HostMgrOperationTarget::ALTERNATE_SOURCES);
    EXPECT_EQ(2 - hosts_in_primary_source, hosts.size());
    if (!is_first_source_primary) {
        EXPECT_TRUE(hosts[0]->hasReservation(
            IPv6Resrv(IPv6Resrv::TYPE_PD, IOAddress("2001:db8:1:10::"), 64)));
        EXPECT_TRUE(hosts[0]->hasReservation(
            IPv6Resrv(IPv6Resrv::TYPE_PD, IOAddress("2001:db8:1:11::"), 64)));
    }
    if (!is_second_source_primary) {
        EXPECT_TRUE(hosts[2 - hosts_in_primary_source - 1]->hasReservation(
            IPv6Resrv(IPv6Resrv::TYPE_PD, IOAddress("2001:db8:1:10::"), 64)));
        EXPECT_TRUE(hosts[2 - hosts_in_primary_source - 1]->hasReservation(
            IPv6Resrv(IPv6Resrv::TYPE_PD, IOAddress("2001:db8:1:11::"), 64)));
    }

    // Select hosts for an unspecified source.
    hosts = HostMgr::instance().getAll4(IOAddress("2001:db8:1:10::"),
                                        HostMgrOperationTarget::UNSPECIFIED_SOURCE);
    EXPECT_EQ(0, hosts.size());
}

void
HostMgrTest::testAdd(BaseHostDataSource& data_source1,
                     BaseHostDataSource& data_source2) {
    bool is_first_source_primary = isPrimaryDataSource(data_source1);
    bool is_second_source_primary = isPrimaryDataSource(data_source2);
    bool has_alternate_source = !is_first_source_primary || !is_second_source_primary;
    // Initially, no reservations should be present.
    ConstHostCollection hosts4 = HostMgr::instance().getAll4(SubnetID(1));
    ConstHostCollection hosts6 = HostMgr::instance().getAll6(SubnetID(1));
    ASSERT_TRUE(hosts4.empty());
    ASSERT_TRUE(hosts6.empty());

    // Add hosts using the implicit operation target.
    auto host = HostPtr(new Host(
        hwaddrs_[0]->toText(false), "hw-address",
        SubnetID(1), SUBNET_ID_UNUSED,
        IOAddress("192.0.2.5")
    ));
    if (has_alternate_source) {
        EXPECT_NO_THROW(HostMgr::instance().add(host));
    } else {
        EXPECT_THROW(HostMgr::instance().add(host), NoHostDataSourceManager);
    }

    host = HostPtr(new Host(
        hwaddrs_[1]->toText(false), "hw-address",
        SUBNET_ID_UNUSED, SubnetID(1),
        IOAddress::IPV4_ZERO_ADDRESS()
    ));
    host->addReservation(IPv6Resrv(IPv6Resrv::TYPE_NA,
                         IOAddress("2001:db8:1::5"), 128));
    if (has_alternate_source) {
        EXPECT_NO_THROW(HostMgr::instance().add(host));
    } else {
        EXPECT_THROW(HostMgr::instance().add(host), NoHostDataSourceManager);
    }

    // Add hosts using the explicit operation target - all data sources.
    host = HostPtr(new Host(
        hwaddrs_[2]->toText(false), "hw-address",
        SubnetID(1), SUBNET_ID_UNUSED,
        IOAddress("192.0.2.6")
    ));
    HostMgr::instance().add(host, HostMgrOperationTarget::ALL_SOURCES);

    host = HostPtr(new Host(
        hwaddrs_[3]->toText(false), "hw-address",
        SUBNET_ID_UNUSED, SubnetID(1),
        IOAddress::IPV4_ZERO_ADDRESS()
    ));
    host->addReservation(IPv6Resrv(IPv6Resrv::TYPE_NA,
                         IOAddress("2001:db8:1::6"), 128));
    HostMgr::instance().add(host, HostMgrOperationTarget::ALL_SOURCES);

    // Add hosts using the explicit operation target - primary data source.
    host = HostPtr(new Host(
        hwaddrs_[4]->toText(false), "hw-address",
        SubnetID(1), SUBNET_ID_UNUSED,
        IOAddress("192.0.2.7")
    ));
    HostMgr::instance().add(host, HostMgrOperationTarget::PRIMARY_SOURCE);

    host = HostPtr(new Host(
        hwaddrs_[5]->toText(false), "hw-address",
        SUBNET_ID_UNUSED, SubnetID(1),
        IOAddress::IPV4_ZERO_ADDRESS()
    ));
    host->addReservation(IPv6Resrv(IPv6Resrv::TYPE_NA,
                         IOAddress("2001:db8:1::7"), 128));
    HostMgr::instance().add(host, HostMgrOperationTarget::PRIMARY_SOURCE);

    // Add hosts using the explicit operation target - alternate data sources.
    host = HostPtr(new Host(
        hwaddrs_[6]->toText(false), "hw-address",
        SubnetID(1), SUBNET_ID_UNUSED,
        IOAddress("192.0.2.8")
    ));
    if (has_alternate_source) {
        EXPECT_NO_THROW(HostMgr::instance().add(host, HostMgrOperationTarget::ALTERNATE_SOURCES));
    } else {
        EXPECT_THROW(HostMgr::instance().add(host, HostMgrOperationTarget::ALTERNATE_SOURCES), NoHostDataSourceManager);
    }

    host = HostPtr(new Host(
        hwaddrs_[7]->toText(false), "hw-address",
        SUBNET_ID_UNUSED, SubnetID(1),
        IOAddress::IPV4_ZERO_ADDRESS()
    ));
    host->addReservation(IPv6Resrv(IPv6Resrv::TYPE_NA,
                         IOAddress("2001:db8:1::8"), 128));
    if (has_alternate_source) {
        EXPECT_NO_THROW(HostMgr::instance().add(host, HostMgrOperationTarget::ALTERNATE_SOURCES));
    } else {
        EXPECT_THROW(HostMgr::instance().add(host, HostMgrOperationTarget::ALTERNATE_SOURCES), NoHostDataSourceManager);
    }

    // Add hosts using the explicit operation target - unspecified data source.
    host = HostPtr(new Host(
        hwaddrs_[8]->toText(false), "hw-address",
        SubnetID(1), SUBNET_ID_UNUSED,
        IOAddress("192.0.2.9")
    ));
    HostMgr::instance().add(host, HostMgrOperationTarget::UNSPECIFIED_SOURCE);

    host = HostPtr(new Host(
        hwaddrs_[9]->toText(false), "hw-address",
        SUBNET_ID_UNUSED, SubnetID(1),
        IOAddress::IPV4_ZERO_ADDRESS()
    ));
    host->addReservation(IPv6Resrv(IPv6Resrv::TYPE_NA,
                         IOAddress("2001:db8:1::9"), 128));
    HostMgr::instance().add(host, HostMgrOperationTarget::UNSPECIFIED_SOURCE);

    // Verify the hosts were added.
    // ALL_SOURCES + PRIMARY_SOURCE targets for IPv4 and IPv6.
    size_t hosts_in_primary_source = 2 * 2 * (is_first_source_primary || is_second_source_primary);
    // Default + ALL_SOURCES + ALTERNATE_SOURCES targets for IPv4 and IPv6.
    size_t hosts_in_alternate_sources = 3 * 2 * (!is_first_source_primary || !is_second_source_primary);

    // Verify primary sources.
    hosts4 = HostMgr::instance().getAll4(SubnetID(1), HostMgrOperationTarget::PRIMARY_SOURCE);
    hosts6 = HostMgr::instance().getAll6(SubnetID(1), HostMgrOperationTarget::PRIMARY_SOURCE);
    EXPECT_EQ(hosts_in_primary_source / 2, hosts4.size());
    EXPECT_EQ(hosts_in_primary_source / 2, hosts6.size());

    // Verify alternate sources.
    hosts4 = HostMgr::instance().getAll4(SubnetID(1), HostMgrOperationTarget::ALTERNATE_SOURCES);
    hosts6 = HostMgr::instance().getAll6(SubnetID(1), HostMgrOperationTarget::ALTERNATE_SOURCES);
    EXPECT_EQ(hosts_in_alternate_sources / 2, hosts4.size());
    EXPECT_EQ(hosts_in_alternate_sources / 2, hosts6.size());
}

void
HostMgrTest::testDeleteByIDAndAddress(BaseHostDataSource& data_source1,
                                      BaseHostDataSource& data_source2) {
    // Set the mode of operation with multiple reservations for the same
    // IP address.
    ASSERT_TRUE(HostMgr::instance().setIPReservationsUnique(false));
    CfgMgr::instance().getStagingCfg()->getCfgHosts()->setIPReservationsUnique(false);

    bool is_first_source_primary = isPrimaryDataSource(data_source1);
    bool is_second_source_primary = isPrimaryDataSource(data_source2);
    bool has_alternate_source = !is_first_source_primary || !is_second_source_primary;
    bool has_primary_source = is_first_source_primary || is_second_source_primary;
    size_t hosts4_in_primary_source = 2 * (is_first_source_primary + is_second_source_primary);
    size_t hosts6_in_primary_source = is_first_source_primary + is_second_source_primary;
    size_t hosts4_in_alternate_sources = 4 - hosts4_in_primary_source;
    size_t hosts6_in_alternate_sources = 2 - hosts6_in_primary_source;

    // Delete from the explicit operation target - all sources.
    addHost4(data_source1, hwaddrs_[0], SubnetID(1), IOAddress("192.0.2.5"));
    addHost4(data_source2, hwaddrs_[1], SubnetID(1), IOAddress("192.0.2.5"));
    addHost6(data_source1, duids_[0], SubnetID(1), IOAddress("2001:db8:1::5"));
    addHost6(data_source2, duids_[1], SubnetID(1), IOAddress("2001:db8:1::5"));
    CfgMgr::instance().commit();
    // 4 IPv4 reservations - 2 sources * 2 addresses.
    ASSERT_EQ(4, HostMgr::instance().getAll4(SubnetID(1)).size());
    // 2 IPv6 reservations - each with 2 reserved addresses.
    ASSERT_EQ(2, HostMgr::instance().getAll6(SubnetID(1)).size());

    EXPECT_TRUE(HostMgr::instance().del(SubnetID(1), IOAddress("192.0.2.5"), HostMgrOperationTarget::ALL_SOURCES));
    EXPECT_TRUE(HostMgr::instance().del(SubnetID(1), IOAddress("2001:db8:1::5"), HostMgrOperationTarget::ALL_SOURCES));

    EXPECT_TRUE(HostMgr::instance().getAll4(SubnetID(1)).empty());
    EXPECT_TRUE(HostMgr::instance().getAll6(SubnetID(1)).empty());

    // Delete from the default operation target.
    addHost4(data_source1, hwaddrs_[2], SubnetID(1), IOAddress("192.0.2.5"));
    addHost4(data_source2, hwaddrs_[3], SubnetID(1), IOAddress("192.0.2.5"));
    addHost6(data_source1, duids_[2], SubnetID(1), IOAddress("2001:db8:1::5"));
    addHost6(data_source2, duids_[3], SubnetID(1), IOAddress("2001:db8:1::5"));
    CfgMgr::instance().commit();
    ASSERT_EQ(4, HostMgr::instance().getAll4(SubnetID(1)).size());
    ASSERT_EQ(2, HostMgr::instance().getAll6(SubnetID(1)).size());

    if (has_alternate_source) {
        EXPECT_TRUE(HostMgr::instance().del(SubnetID(1), IOAddress("192.0.2.5")));
        EXPECT_TRUE(HostMgr::instance().del(SubnetID(1), IOAddress("2001:db8:1::5")));
    } else {
        EXPECT_THROW(HostMgr::instance().del(SubnetID(1), IOAddress("192.0.2.5")), NoHostDataSourceManager);
        EXPECT_THROW(HostMgr::instance().del(SubnetID(1), IOAddress("2001:db8:1::5")), NoHostDataSourceManager);
    }

    EXPECT_EQ(hosts4_in_primary_source, HostMgr::instance().getAll4(SubnetID(1)).size());
    EXPECT_EQ(hosts6_in_primary_source, HostMgr::instance().getAll6(SubnetID(1)).size());

    HostMgr::instance().del(SubnetID(1), IOAddress("192.0.2.5"), HostMgrOperationTarget::ALL_SOURCES);
    HostMgr::instance().del(SubnetID(1), IOAddress("2001:db8:1::5"), HostMgrOperationTarget::ALL_SOURCES);

    // Delete from the explicit operation target - alternate sources.
    addHost4(data_source1, hwaddrs_[4], SubnetID(1), IOAddress("192.0.2.5"));
    addHost4(data_source2, hwaddrs_[5], SubnetID(1), IOAddress("192.0.2.5"));
    addHost6(data_source1, duids_[4], SubnetID(1), IOAddress("2001:db8:1::5"));
    addHost6(data_source2, duids_[5], SubnetID(1), IOAddress("2001:db8:1::5"));
    CfgMgr::instance().commit();

    if (has_alternate_source) {
        EXPECT_TRUE(HostMgr::instance().del(SubnetID(1),
                                                IOAddress("192.0.2.5"),
                                                HostMgrOperationTarget::ALTERNATE_SOURCES));
        EXPECT_TRUE(HostMgr::instance().del(SubnetID(1),
                                                IOAddress("2001:db8:1::5"),
                                                HostMgrOperationTarget::ALTERNATE_SOURCES));
    } else {
        EXPECT_THROW(HostMgr::instance().del(SubnetID(1),
                                             IOAddress("192.0.2.5"),
                                             HostMgrOperationTarget::ALTERNATE_SOURCES),
                     NoHostDataSourceManager);
        EXPECT_THROW(HostMgr::instance().del(SubnetID(1),
                                             IOAddress("2001:db8:1::5"),
                                             HostMgrOperationTarget::ALTERNATE_SOURCES),
                     NoHostDataSourceManager);
    }

    EXPECT_EQ(hosts4_in_primary_source, HostMgr::instance().getAll4(SubnetID(1)).size());
    EXPECT_EQ(hosts6_in_primary_source, HostMgr::instance().getAll6(SubnetID(1)).size());

    HostMgr::instance().del(SubnetID(1), IOAddress("192.0.2.5"), HostMgrOperationTarget::ALL_SOURCES);
    HostMgr::instance().del(SubnetID(1), IOAddress("2001:db8:1::5"), HostMgrOperationTarget::ALL_SOURCES);

    // Delete from the explicit operation target - primary source.
    addHost4(data_source1, hwaddrs_[6], SubnetID(1), IOAddress("192.0.2.5"));
    addHost4(data_source2, hwaddrs_[7], SubnetID(1), IOAddress("192.0.2.5"));
    addHost6(data_source1, duids_[6], SubnetID(1), IOAddress("2001:db8:1::5"));
    addHost6(data_source2, duids_[7], SubnetID(1), IOAddress("2001:db8:1::5"));
    CfgMgr::instance().commit();

    if (has_primary_source) {
        EXPECT_TRUE(HostMgr::instance().del(SubnetID(1), IOAddress("192.0.2.5"), HostMgrOperationTarget::PRIMARY_SOURCE));
        EXPECT_TRUE(HostMgr::instance().del(SubnetID(1), IOAddress("2001:db8:1::5"), HostMgrOperationTarget::PRIMARY_SOURCE));
    } else {
        EXPECT_FALSE(HostMgr::instance().del(SubnetID(1), IOAddress("192.0.2.5"), HostMgrOperationTarget::PRIMARY_SOURCE));
        EXPECT_FALSE(HostMgr::instance().del(SubnetID(1), IOAddress("2001:db8:1::5"), HostMgrOperationTarget::PRIMARY_SOURCE));
    }

    EXPECT_EQ(hosts4_in_alternate_sources, HostMgr::instance().getAll4(SubnetID(1)).size());
    EXPECT_EQ(hosts6_in_alternate_sources, HostMgr::instance().getAll6(SubnetID(1)).size());

    HostMgr::instance().del(SubnetID(1), IOAddress("192.0.2.5"), HostMgrOperationTarget::ALL_SOURCES);
    HostMgr::instance().del(SubnetID(1), IOAddress("2001:db8:1::5"), HostMgrOperationTarget::ALL_SOURCES);

    // Delete from the explicit operation target - unspecified source.
    addHost4(data_source1, hwaddrs_[8], SubnetID(1), IOAddress("192.0.2.5"));
    addHost4(data_source2, hwaddrs_[9], SubnetID(1), IOAddress("192.0.2.5"));
    addHost6(data_source1, duids_[8], SubnetID(1), IOAddress("2001:db8:1::5"));
    addHost6(data_source2, duids_[9], SubnetID(1), IOAddress("2001:db8:1::5"));
    CfgMgr::instance().commit();

    EXPECT_FALSE(HostMgr::instance().del(SubnetID(1), IOAddress("192.0.2.5"), HostMgrOperationTarget::UNSPECIFIED_SOURCE));
    EXPECT_FALSE(HostMgr::instance().del(SubnetID(1), IOAddress("2001:db8:1::5"), HostMgrOperationTarget::UNSPECIFIED_SOURCE));

    EXPECT_EQ(4, HostMgr::instance().getAll4(SubnetID(1)).size());
    EXPECT_EQ(2, HostMgr::instance().getAll6(SubnetID(1)).size());

    HostMgr::instance().del(SubnetID(1), IOAddress("192.0.2.5"), HostMgrOperationTarget::ALL_SOURCES);
    HostMgr::instance().del(SubnetID(1), IOAddress("2001:db8:1::5"), HostMgrOperationTarget::ALL_SOURCES);
}

void
HostMgrTest::testDeleteOneHostByIDAndAddress(BaseHostDataSource& data_source) {
    ASSERT_TRUE(HostMgr::instance().setIPReservationsUnique(false));

    // This test expects alternate data source - MySQL or PostgreSQL hosts DB.
    EXPECT_FALSE(isPrimaryDataSource(data_source));

    // Add 3 IPv4 hosts.
    addHost4(data_source, hwaddrs_[0], SubnetID(1), IOAddress("192.0.2.4"));
    addHost4(data_source, hwaddrs_[1], SubnetID(1), IOAddress("192.0.2.5"));
    addHost4(data_source, hwaddrs_[2], SubnetID(1), IOAddress("192.0.2.6"));

    // Add 3 IPv6 hosts.
    addHost6(data_source, duids_[0], SubnetID(1), IOAddress("2001:db8:1::4"));
    addHost6(data_source, duids_[1], SubnetID(1), IOAddress("2001:db8:1::5"));
    addHost6(data_source, duids_[2], SubnetID(1), IOAddress("2001:db8:1::6"));

    CfgMgr::instance().commit();

    // Delete only one IPv4 host - provide SubnetId and IP address for the host to be deleted.
    EXPECT_TRUE(HostMgr::instance().del(SubnetID(1), IOAddress("192.0.2.4")));

    // Delete only one IPv6 host - provide SubnetId and IP address for the host to be deleted.
    EXPECT_TRUE(HostMgr::instance().del(SubnetID(1), IOAddress("2001:db8:1::4")));

    // Expect other two IPv4 hosts still in reservations.
    EXPECT_EQ(4, HostMgr::instance().getAll4(SubnetID(1)).size());

    // Expect other two IPv6 hosts still in reservations.
    EXPECT_EQ(2, HostMgr::instance().getAll6(SubnetID(1)).size());
}

void
HostMgrTest::testDelete4ByIDAndIdentifier(BaseHostDataSource& data_source1,
                                          BaseHostDataSource& data_source2) {
    // Set the mode of operation with multiple reservations for the same
    // IP address.
    ASSERT_TRUE(HostMgr::instance().setIPReservationsUnique(false));
    CfgMgr::instance().getStagingCfg()->getCfgHosts()->setIPReservationsUnique(false);

    bool is_first_source_primary = isPrimaryDataSource(data_source1);
    bool is_second_source_primary = isPrimaryDataSource(data_source2);

    if (is_first_source_primary && is_second_source_primary) {
        // Two primary data sources - in fact it is a single source.

        // Delete from all sources.
        addHost4(data_source1, hwaddrs_[0], SubnetID(1), IOAddress("192.168.0.2"));
        CfgMgr::instance().commit();
        EXPECT_TRUE(HostMgr::instance().del4(SubnetID(1), Host::IDENT_HWADDR,
                                             &hwaddrs_[0]->hwaddr_[0],
                                             hwaddrs_[0]->hwaddr_.size(),
                                             HostMgrOperationTarget::ALL_SOURCES));
        EXPECT_TRUE(HostMgr::instance().getAll4(SubnetID(1)).empty());

        // Delete from default (alternate) sources.
        addHost4(data_source1, hwaddrs_[0], SubnetID(1), IOAddress("192.168.0.2"));
        CfgMgr::instance().commit();
        EXPECT_THROW(HostMgr::instance().del4(SubnetID(1), Host::IDENT_HWADDR,
                                              &hwaddrs_[0]->hwaddr_[0],
                                              hwaddrs_[0]->hwaddr_.size()),
                     NoHostDataSourceManager);
        EXPECT_EQ(1, HostMgr::instance().getAll4(SubnetID(1)).size());

        // Delete from explicit alternate sources.
        EXPECT_THROW(HostMgr::instance().del4(SubnetID(1), Host::IDENT_HWADDR,
                                              &hwaddrs_[0]->hwaddr_[0],
                                              hwaddrs_[0]->hwaddr_.size(),
                                              HostMgrOperationTarget::ALTERNATE_SOURCES),
                     NoHostDataSourceManager);
        EXPECT_EQ(1, HostMgr::instance().getAll4(SubnetID(1)).size());

        // Delete from unspecified source.
        EXPECT_FALSE(HostMgr::instance().del4(SubnetID(1), Host::IDENT_HWADDR,
                                              &hwaddrs_[0]->hwaddr_[0],
                                              hwaddrs_[0]->hwaddr_.size(),
                                              HostMgrOperationTarget::UNSPECIFIED_SOURCE));
        EXPECT_EQ(1, HostMgr::instance().getAll4(SubnetID(1)).size());

        // Delete from primary source.
        EXPECT_TRUE(HostMgr::instance().del4(SubnetID(1), Host::IDENT_HWADDR,
                                             &hwaddrs_[0]->hwaddr_[0],
                                             hwaddrs_[0]->hwaddr_.size(),
                                             HostMgrOperationTarget::PRIMARY_SOURCE));
        EXPECT_TRUE(HostMgr::instance().getAll4(SubnetID(1)).empty());
    } else if (is_first_source_primary != is_second_source_primary) {
        // One primary data source and one alternate data source.

        // Delete from all sources.
        addHost4(data_source1, hwaddrs_[0], SubnetID(1), IOAddress("192.168.0.2"));
        addHost4(data_source2, hwaddrs_[0], SubnetID(1), IOAddress("192.168.0.2"));
        CfgMgr::instance().commit();
        EXPECT_TRUE(HostMgr::instance().del4(SubnetID(1), Host::IDENT_HWADDR,
                                             &hwaddrs_[0]->hwaddr_[0],
                                             hwaddrs_[0]->hwaddr_.size(),
                                             HostMgrOperationTarget::ALL_SOURCES));
        EXPECT_TRUE(HostMgr::instance().getAll4(SubnetID(1)).empty());

        // Delete from default (alternate) sources.
        addHost4(data_source1, hwaddrs_[0], SubnetID(1), IOAddress("192.168.0.2"));
        addHost4(data_source2, hwaddrs_[0], SubnetID(1), IOAddress("192.168.0.2"));
        CfgMgr::instance().commit();
        EXPECT_TRUE(HostMgr::instance().del4(SubnetID(1), Host::IDENT_HWADDR,
                                             &hwaddrs_[0]->hwaddr_[0],
                                             hwaddrs_[0]->hwaddr_.size()));
        // The host reservation in the primary source still exists.
        EXPECT_EQ(1, HostMgr::instance().getAll4(SubnetID(1)).size());
        // Clean the host reservations.
        HostMgr::instance().del4(SubnetID(1), Host::IDENT_HWADDR,
                                 &hwaddrs_[0]->hwaddr_[0],
                                 hwaddrs_[0]->hwaddr_.size(),
                                 HostMgrOperationTarget::ALL_SOURCES);

        // Delete from explicit alternate sources.
        addHost4(data_source1, hwaddrs_[0], SubnetID(1), IOAddress("192.168.0.2"));
        addHost4(data_source2, hwaddrs_[0], SubnetID(1), IOAddress("192.168.0.2"));
        EXPECT_TRUE(HostMgr::instance().del4(SubnetID(1), Host::IDENT_HWADDR,
                                             &hwaddrs_[0]->hwaddr_[0],
                                             hwaddrs_[0]->hwaddr_.size(),
                                             HostMgrOperationTarget::ALTERNATE_SOURCES));
        // The host reservation in the primary source still exists.
        EXPECT_EQ(1, HostMgr::instance().getAll4(SubnetID(1)).size());
        // Clean the host reservations.
        HostMgr::instance().del4(SubnetID(1), Host::IDENT_HWADDR,
                                 &hwaddrs_[0]->hwaddr_[0],
                                 hwaddrs_[0]->hwaddr_.size(),
                                 HostMgrOperationTarget::ALL_SOURCES);

        // Delete from unspecified source.
        addHost4(data_source1, hwaddrs_[0], SubnetID(1), IOAddress("192.168.0.2"));
        addHost4(data_source2, hwaddrs_[0], SubnetID(1), IOAddress("192.168.0.2"));
        EXPECT_FALSE(HostMgr::instance().del4(SubnetID(1), Host::IDENT_HWADDR,
                                              &hwaddrs_[0]->hwaddr_[0],
                                              hwaddrs_[0]->hwaddr_.size(),
                                              HostMgrOperationTarget::UNSPECIFIED_SOURCE));
        EXPECT_EQ(2, HostMgr::instance().getAll4(SubnetID(1)).size());

        // Delete from primary source.
        EXPECT_TRUE(HostMgr::instance().del4(SubnetID(1), Host::IDENT_HWADDR,
                                             &hwaddrs_[0]->hwaddr_[0],
                                             hwaddrs_[0]->hwaddr_.size(),
                                             HostMgrOperationTarget::PRIMARY_SOURCE));
        // The host reservation in the alternate source still exists.
        EXPECT_EQ(1, HostMgr::instance().getAll4(SubnetID(1)).size());
        // Clean the host reservations.
        HostMgr::instance().del4(SubnetID(1), Host::IDENT_HWADDR,
                                 &hwaddrs_[0]->hwaddr_[0],
                                 hwaddrs_[0]->hwaddr_.size(),
                                 HostMgrOperationTarget::ALL_SOURCES);
    } else {
        // Not defined.
        isc_throw(NotImplemented, "not implemented test case for two alternate sources");
    }
}

void
HostMgrTest::testDelete6ByIDAndIdentifier(BaseHostDataSource& data_source1,
                                          BaseHostDataSource& data_source2) {
    // Set the mode of operation with multiple reservations for the same
    // IP address.
    ASSERT_TRUE(HostMgr::instance().setIPReservationsUnique(false));
    CfgMgr::instance().getStagingCfg()->getCfgHosts()->setIPReservationsUnique(false);

    bool is_first_source_primary = isPrimaryDataSource(data_source1);
    bool is_second_source_primary = isPrimaryDataSource(data_source2);

    if (is_first_source_primary && is_second_source_primary) {
        // Two primary data sources - in fact it is a single source.

        // Delete from all sources.
        addHost6(data_source1, duids_[0], SubnetID(1), IOAddress("2001:db8:1::5"), 128);
        CfgMgr::instance().commit();
        EXPECT_TRUE(HostMgr::instance().del6(SubnetID(1), Host::IDENT_DUID,
                                             &duids_[0]->getDuid()[0],
                                             duids_[0]->getDuid().size(),
                                             HostMgrOperationTarget::ALL_SOURCES));
        EXPECT_TRUE(HostMgr::instance().getAll6(SubnetID(1)).empty());

        // Delete from default (alternate) sources.
        addHost6(data_source1, duids_[0], SubnetID(1), IOAddress("2001:db8:1::5"), 128);
        CfgMgr::instance().commit();
        EXPECT_THROW(HostMgr::instance().del6(SubnetID(1), Host::IDENT_DUID,
                                              &duids_[0]->getDuid()[0],
                                              duids_[0]->getDuid().size()),
                     NoHostDataSourceManager);
        EXPECT_EQ(1, HostMgr::instance().getAll6(SubnetID(1)).size());

        // Delete from explicit alternate sources.
        EXPECT_THROW(HostMgr::instance().del6(SubnetID(1), Host::IDENT_DUID,
                                              &duids_[0]->getDuid()[0],
                                              duids_[0]->getDuid().size(),
                                              HostMgrOperationTarget::ALTERNATE_SOURCES),
                     NoHostDataSourceManager);
        EXPECT_EQ(1, HostMgr::instance().getAll6(SubnetID(1)).size());

        // Delete from unspecified source.
        EXPECT_FALSE(HostMgr::instance().del6(SubnetID(1), Host::IDENT_DUID,
                                              &duids_[0]->getDuid()[0],
                                              duids_[0]->getDuid().size(),
                                              HostMgrOperationTarget::UNSPECIFIED_SOURCE));
        EXPECT_EQ(1, HostMgr::instance().getAll6(SubnetID(1)).size());

        // Delete from primary source.
        EXPECT_TRUE(HostMgr::instance().del6(SubnetID(1), Host::IDENT_DUID,
                                             &duids_[0]->getDuid()[0],
                                             duids_[0]->getDuid().size(),
                                             HostMgrOperationTarget::PRIMARY_SOURCE));
        EXPECT_TRUE(HostMgr::instance().getAll6(SubnetID(1)).empty());
    } else if (is_first_source_primary != is_second_source_primary) {
        // One primary data source and one alternate data source.

        // Delete from all sources.
        addHost6(data_source1, duids_[0], SubnetID(1), IOAddress("2001:db8:1::5"), 128);
        addHost6(data_source2, duids_[0], SubnetID(1), IOAddress("2001:db8:1::5"), 128);
        CfgMgr::instance().commit();
        EXPECT_TRUE(HostMgr::instance().del6(SubnetID(1), Host::IDENT_DUID,
                                             &duids_[0]->getDuid()[0],
                                             duids_[0]->getDuid().size(),
                                             HostMgrOperationTarget::ALL_SOURCES));
        EXPECT_TRUE(HostMgr::instance().getAll6(SubnetID(1)).empty());

        // Delete from default (alternate) sources.
        addHost6(data_source1, duids_[0], SubnetID(1), IOAddress("2001:db8:1::5"), 128);
        addHost6(data_source2, duids_[0], SubnetID(1), IOAddress("2001:db8:1::5"), 128);
        CfgMgr::instance().commit();
        EXPECT_TRUE(HostMgr::instance().del6(SubnetID(1), Host::IDENT_DUID,
                                             &duids_[0]->getDuid()[0],
                                             duids_[0]->getDuid().size()));
        // The host reservation in the primary source still exists.
        EXPECT_EQ(1, HostMgr::instance().getAll6(SubnetID(1)).size());
        // Clean the host reservations.
        HostMgr::instance().del6(SubnetID(1), Host::IDENT_DUID,
                                 &duids_[0]->getDuid()[0],
                                 duids_[0]->getDuid().size(),
                                 HostMgrOperationTarget::ALL_SOURCES);

        // Delete from explicit alternate sources.
        addHost6(data_source1, duids_[0], SubnetID(1), IOAddress("2001:db8:1::5"), 128);
        addHost6(data_source2, duids_[0], SubnetID(1), IOAddress("2001:db8:1::5"), 128);
        EXPECT_TRUE(HostMgr::instance().del6(SubnetID(1), Host::IDENT_DUID,
                                             &duids_[0]->getDuid()[0],
                                             duids_[0]->getDuid().size(),
                                             HostMgrOperationTarget::ALTERNATE_SOURCES));
        // The host reservation in the primary source still exists.
        EXPECT_EQ(1, HostMgr::instance().getAll6(SubnetID(1)).size());
        // Clean the host reservations.
        HostMgr::instance().del6(SubnetID(1), Host::IDENT_DUID,
                                 &duids_[0]->getDuid()[0],
                                 duids_[0]->getDuid().size(),
                                 HostMgrOperationTarget::ALL_SOURCES);

        // Delete from unspecified source.
        addHost6(data_source1, duids_[0], SubnetID(1), IOAddress("2001:db8:1::5"), 128);
        addHost6(data_source2, duids_[0], SubnetID(1), IOAddress("2001:db8:1::5"), 128);
        EXPECT_FALSE(HostMgr::instance().del6(SubnetID(1), Host::IDENT_DUID,
                                              &duids_[0]->getDuid()[0],
                                              duids_[0]->getDuid().size(),
                                              HostMgrOperationTarget::UNSPECIFIED_SOURCE));
        EXPECT_EQ(2, HostMgr::instance().getAll6(SubnetID(1)).size());

        // Delete from primary source.
        EXPECT_TRUE(HostMgr::instance().del6(SubnetID(1), Host::IDENT_DUID,
                                             &duids_[0]->getDuid()[0],
                                             duids_[0]->getDuid().size(),
                                             HostMgrOperationTarget::PRIMARY_SOURCE));
        // The host reservation in the alternate source still exists.
        EXPECT_EQ(1, HostMgr::instance().getAll6(SubnetID(1)).size());
        // Clean the host reservations.
        HostMgr::instance().del6(SubnetID(1), Host::IDENT_DUID,
                                 &duids_[0]->getDuid()[0],
                                 duids_[0]->getDuid().size(),
                                 HostMgrOperationTarget::ALL_SOURCES);
    } else {
        // Not defined.
        isc_throw(NotImplemented, "not implemented test case for two alternate sources");
    }
}

bool HostMgrTest::isPrimaryDataSource(const BaseHostDataSource& data_source) const {
    auto const ptr = dynamic_cast<const CfgHosts*>(&data_source);
    return ptr != nullptr;
}

void
GenericHostDataSourceTest::testUpdate() {
    // Make sure the host data source is initialized.
    ASSERT_TRUE(hdsptr_);

    // Create a host with an IPv4 address reservation.
    HostPtr const host(HostDataSourceUtils::initializeHost4("192.0.2.1", Host::IDENT_HWADDR));
    SubnetID const v4_subnet(host->getIPv4SubnetID());
    SubnetID const v6_subnet(host->getIPv6SubnetID());
    string hwaddr(host->getHWAddress()->toText(false));
    boost::replace_all(hwaddr, ":", "");
    boost::to_upper(hwaddr);

    // Updating a host that doesn't exist should throw.
    EXPECT_THROW_MSG(hdsptr_->update(host), HostNotFound, "Host not updated (not found).");

    // There should be no hosts.
    ConstHostCollection hosts(hdsptr_->getAll4(v4_subnet));
    EXPECT_EQ(0, hosts.size());

    // Add the host.
    EXPECT_NO_THROW(hdsptr_->add(host));

    // The host should be there.
    hosts = hdsptr_->getAll4(v4_subnet);
    EXPECT_EQ(1, hosts.size());
    EXPECT_EQ("hwaddr=" + hwaddr + " ipv4_subnet_id=" + to_string(v4_subnet) +
                  " ipv6_subnet_id=" + to_string(v6_subnet) +
                  " hostname=(empty) "
                  "ipv4_reservation=192.0.2.1 siaddr=(no) sname=(empty) file=(empty) key=(empty) "
                  "ipv6_reservations=(none)",
              hosts[0]->toText());

    // Update the host. Change nothing.
    EXPECT_NO_THROW(hdsptr_->update(host));

    // The same host should be in the data source.
    hosts = hdsptr_->getAll4(v4_subnet);
    EXPECT_EQ(1, hosts.size());
    EXPECT_EQ("hwaddr=" + hwaddr + " ipv4_subnet_id=" + to_string(v4_subnet) +
                  " ipv6_subnet_id=" + to_string(v6_subnet) +
                  " hostname=(empty) "
                  "ipv4_reservation=192.0.2.1 siaddr=(no) sname=(empty) file=(empty) key=(empty) "
                  "ipv6_reservations=(none)",
              hosts[0]->toText());

    // Update the host with new hostname.
    host->setHostname("foo.example.com");
    EXPECT_NO_THROW(hdsptr_->update(host));

    // The change should be reflected in the data source.
    hosts = hdsptr_->getAll4(v4_subnet);
    EXPECT_EQ(1, hosts.size());
    EXPECT_EQ("hwaddr=" + hwaddr + " ipv4_subnet_id=" + to_string(v4_subnet) +
                  " ipv6_subnet_id=" + to_string(v6_subnet) +
                  " hostname=foo.example.com "
                  "ipv4_reservation=192.0.2.1 siaddr=(no) sname=(empty) file=(empty) key=(empty) "
                  "ipv6_reservations=(none)",
              hosts[0]->toText());

    // Remove hostname from host.
    host->setHostname("");
    EXPECT_NO_THROW(hdsptr_->update(host));

    // The change should be reflected in the data source.
    hosts = hdsptr_->getAll4(v4_subnet);
    EXPECT_EQ(1, hosts.size());
    EXPECT_EQ("hwaddr=" + hwaddr + " ipv4_subnet_id=" + to_string(v4_subnet) +
                  " ipv6_subnet_id=" + to_string(v6_subnet) +
                  " hostname=(empty) "
                  "ipv4_reservation=192.0.2.1 siaddr=(no) sname=(empty) file=(empty) key=(empty) "
                  "ipv6_reservations=(none)",
              hosts[0]->toText());
}

}  // namespace test
}  // namespace dhcp
}  // namespace isc
