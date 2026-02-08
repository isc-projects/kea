// Copyright (C) 2018-2026 Internet Systems Consortium, Inc. ("ISC")
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

#include <radius_parsers.h>
#include <cc/default_credentials.h>
#include <dhcp/pkt4.h>
#include <dhcpsrv/cfgmgr.h>
#include <database/database_connection.h>
#include <dhcpsrv/host_data_source_factory.h>
#include <dhcpsrv/host_mgr.h>
#include <testutils/gtest_utils.h>
#include <testutils/test_to_element.h>
#include <attribute_test.h>
#include <gtest/gtest.h>
#include <limits>
#include <sstream>

using namespace std;
using namespace isc;
using namespace isc::asiolink;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::radius;
using namespace isc::test;

namespace {

/// @brief Test fixture for testing configurations for the radius library.
class ConfigTest : public radius::test::AttributeTest {
public:
    /// @brief Constructor
    ConfigTest() : AttributeTest(), impl_(RadiusImpl::instance()) {
        impl_.reset();
        CfgMgr::instance().clear();
        HostMgr::instance().setDisableSingleQuery(false);
        auto factory = [] (const isc::db::DatabaseConnection::ParameterMap&) {
            return (HostDataSourcePtr());
        };
        HostDataSourceFactory::registerFactory("cache", factory);
    }

    /// @brief Destructor
    virtual ~ConfigTest() {
        impl_.reset();
        HostDataSourceFactory::deregisterFactory("cache");
        static_cast<void>(remove(TEST_FILE));
    }

    /// @brief writes specified content to a file.
    ///
    /// @param file_name name of file to be written.
    /// @param content content to be written to file.
    void writeFile(const std::string& file_name, const std::string& content) {
        static_cast<void>(remove(file_name.c_str()));
        ofstream out(file_name.c_str(), ios::trunc);
        EXPECT_TRUE(out.is_open());
        out << content;
        out.close();
    }

    /// @brief Radius implementation.
    RadiusImpl& impl_;

    /// Name of a dictionary file used during tests.
    static const char* TEST_FILE;
};

const char* ConfigTest::TEST_FILE = "test-dictionary";

// Verify that a configuration must be a map.
TEST_F(ConfigTest, notMap) {
    ElementPtr config = Element::createList();
    EXPECT_THROW_MSG(impl_.init(config), ConfigError,
                     "get(string) called on a non-map Element");
}

// Verify that an empty configuration works.
TEST_F(ConfigTest, empty) {
    ElementPtr config = Element::createMap();
    EXPECT_NO_THROW(impl_.init(config));
}

// Verify that global defaults are set as expected.
TEST_F(ConfigTest, defaults) {
    ElementPtr config = Element::createMap();
    EXPECT_NO_THROW(impl_.init(config));
    string expected = "{ "
        "\"access\": {"
        "   \"enabled\": false,"
        "   \"idle-timer-interval\": 0"
        "}, "
        "\"accounting\": {"
        "   \"enabled\": false,"
        "   \"idle-timer-interval\": 0"
        "}, "
        "\"bindaddr\": \"*\", "
        "\"canonical-mac-address\": false, "
        "\"client-id-pop0\": false, "
        "\"client-id-printable\": false, "
        "\"deadtime\": 0, "
        "\"dictionary\": \"" + string(DICTIONARY) + "\", "
        "\"extract-duid\": true, "
        "\"identifier-type4\": \"client-id\", "
        "\"identifier-type6\": \"duid\", "
        "\"protocol\": \"UDP\", "
        "\"reselect-subnet-address\": false, "
        "\"reselect-subnet-pool\": false, "
        "\"retries\": 3, "
        "\"session-history\": \"\", "
        "\"thread-pool-size\": 0, "
        "\"timeout\": 10"
        " }";
    runToElementTest<RadiusImpl>(expected, impl_);
}

// Verify that global can be set.
TEST_F(ConfigTest, global) {
    ElementPtr config = Element::createMap();
    config->set("bindaddr", Element::create("127.0.0.1"));
    config->set("canonical-mac-address", Element::create(true));
    config->set("client-id-pop0", Element::create(true));
    config->set("client-id-printable", Element::create(true));
    config->set("deadtime", Element::create(10));
    config->set("dictionary", Element::create("/dev/null"));
    config->set("extract-duid", Element::create(false));
    config->set("identifier-type4", Element::create("hw-address"));
    config->set("identifier-type6", Element::create("flex-id"));
    config->set("protocol", Element::create("TLS"));
    config->set("reselect-subnet-address", Element::create(true));
    config->set("reselect-subnet-pool", Element::create(true));
    config->set("retries", Element::create(5));
    config->set("session-history", Element::create("/tmp/foobar"));
    config->set("thread-pool-size", Element::create(8));
    config->set("timeout", Element::create(12));
    EXPECT_NO_THROW(impl_.init(config));
    string expected = "{ "
        "\"access\": {"
        "   \"enabled\": false,"
        "   \"idle-timer-interval\": 0"
        "}, "
        "\"accounting\": {"
        "   \"enabled\": false,"
        "   \"idle-timer-interval\": 0"
        "}, "
        "\"bindaddr\": \"127.0.0.1\", "
        "\"canonical-mac-address\": true, "
        "\"client-id-pop0\": true, "
        "\"client-id-printable\": true, "
        "\"tls\": {"
        "   \"enabled\": false,"
        "   \"idle-timer-interval\": 0"
        "}, "
        "\"deadtime\": 10, "
        "\"dictionary\": \"/dev/null\", "
        "\"extract-duid\": false, "
        "\"identifier-type4\": \"hw-address\", "
        "\"identifier-type6\": \"flex-id\", "
        "\"protocol\": \"TLS\", "
        "\"reselect-subnet-address\": true, "
        "\"reselect-subnet-pool\": true, "
        "\"retries\": 5, "
        "\"session-history\": \"/tmp/foobar\", "
        "\"thread-pool-size\": 8, "
        "\"timeout\": 12"
        " }";
    runToElementTest<RadiusImpl>(expected, impl_);

    // Check state.
    EXPECT_EQ(PW_PROTO_TLS, impl_.proto_);
    EXPECT_EQ("127.0.0.1", impl_.bindaddr_);
    EXPECT_TRUE(impl_.canonical_mac_address_);
    EXPECT_TRUE(impl_.clientid_pop0_);
    EXPECT_TRUE(impl_.clientid_printable_);
    EXPECT_EQ(10, impl_.deadtime_);
    EXPECT_EQ("/dev/null", impl_.dictionary_);
    EXPECT_FALSE(impl_.extract_duid_);
    EXPECT_EQ(Host::IDENT_HWADDR, impl_.id_type4_);
    EXPECT_EQ(Host::IDENT_FLEX, impl_.id_type6_);
    EXPECT_EQ(5, impl_.retries_);
    EXPECT_TRUE(impl_.reselect_subnet_address_);
    EXPECT_TRUE(impl_.reselect_subnet_pool_);
    EXPECT_EQ("/tmp/foobar", impl_.session_history_filename_);
    EXPECT_EQ(8, impl_.thread_pool_size_);
    EXPECT_EQ(12, impl_.timeout_);
    EXPECT_TRUE(impl_.remap_.empty());
}

// Verify that bad dictionary throws.
TEST_F(ConfigTest, badDictionary) {
    // Unload dictionary.
    AttrDefs::instance().clear();

    ElementPtr config = Element::createMap();
    config->set("dictionary", Element::create("/do-not-exist"));
    string expected = "can't read radius dictionary: ";
    expected += "can't open dictionary '/do-not-exist': ";
    expected += "No such file or directory";
    EXPECT_THROW_MSG(impl_.init(config), ConfigError, expected);

    impl_.reset();
    string dict = "BEGIN-VENDOR 1234\n";
    writeFile(TEST_FILE, dict);
    config = Element::createMap();
    config->set("dictionary", Element::create(string(TEST_FILE)));
    expected = "vendor definitions were not properly closed: ";
    expected += "vendor 1234 is still open";
    EXPECT_THROW_MSG(impl_.init(config), ConfigError, expected);

    impl_.reset();
    config = Element::createMap();
    config->set("dictionary", Element::create(string(TEST_DICTIONARY)));
    EXPECT_NO_THROW_LOG(impl_.init(config));
}

// Verify that bad global throws.
TEST_F(ConfigTest, badGlobal) {
    ElementPtr config = Element::createMap();
    config->set("bindaddr", Element::create(0));
    EXPECT_THROW_MSG(impl_.init(config), ConfigError,
                     "stringValue() called on non-string Element");

    impl_.reset();
    config = Element::createMap();
    config->set("canonical-mac-address", Element::create("no"));
    EXPECT_THROW_MSG(impl_.init(config), ConfigError,
                     "boolValue() called on non-Bool Element");

    impl_.reset();
    config = Element::createMap();
    config->set("client-id-pop0", Element::create(2));
    EXPECT_THROW_MSG(impl_.init(config), ConfigError,
                     "boolValue() called on non-Bool Element");

    impl_.reset();
    config = Element::createMap();
    config->set("client-id-printable", Element::create("yes"));
    EXPECT_THROW_MSG(impl_.init(config), ConfigError,
                     "boolValue() called on non-Bool Element");

    impl_.reset();
    config = Element::createMap();
    config->set("deadtime", Element::create("now"));
    EXPECT_THROW_MSG(impl_.init(config), ConfigError,
                     "intValue() called on non-integer Element");

    impl_.reset();
    config = Element::createMap();
    config->set("deadtime", Element::create(-1));
    ostringstream expected;
    expected << "bad deadtime -1 not in [0.."
             << numeric_limits<unsigned>::max() << "]";
    EXPECT_THROW_MSG(impl_.init(config), ConfigError, expected.str());

    impl_.reset();
    config = Element::createMap();
    config->set("deadtime", Element::create(123456789000));
    expected.str("");
    expected << "bad deadtime 123456789000 not in [0.."
             << numeric_limits<unsigned>::max() << "]";
    EXPECT_THROW_MSG(impl_.init(config), ConfigError, expected.str());

    impl_.reset();
    config = Element::createMap();
    config->set("dictionary", Element::create(0));
    EXPECT_THROW_MSG(impl_.init(config), ConfigError,
                     "stringValue() called on non-string Element");

    impl_.reset();
    config = Element::createMap();
    config->set("extract-duid", Element::create(1));
    EXPECT_THROW_MSG(impl_.init(config), ConfigError,
                     "boolValue() called on non-Bool Element");

    impl_.reset();
    config = Element::createMap();
    config->set("identifier-type4", Element::create(1));
    EXPECT_THROW_MSG(impl_.init(config), ConfigError,
                     "stringValue() called on non-string Element");

    impl_.reset();
    config = Element::createMap();
    config->set("identifier-type4", Element::create("hardware-address"));
    EXPECT_THROW_MSG(impl_.init(config), ConfigError,
                     "invalid client identifier type 'hardware-address'");

    impl_.reset();
    config = Element::createMap();
    config->set("identifier-type6", Element::create(2));
    EXPECT_THROW_MSG(impl_.init(config), ConfigError,
                     "stringValue() called on non-string Element");

    impl_.reset();
    config = Element::createMap();
    config->set("identifier-type6", Element::create("flex"));
    EXPECT_THROW_MSG(impl_.init(config), ConfigError,
                     "invalid client identifier type 'flex'");

    impl_.reset();
    config = Element::createMap();
    config->set("nas-ports", Element::create(0));
    EXPECT_THROW_MSG(impl_.init(config), ConfigError,
                     "listValue() called on non-list Element");

    impl_.reset();
    config = Element::createMap();
    config->set("reselect-subnet-address", Element::create(0));
    EXPECT_THROW_MSG(impl_.init(config), ConfigError,
                     "boolValue() called on non-Bool Element");

    impl_.reset();
    config = Element::createMap();
    config->set("reselect-subnet-pool", Element::create("false"));
    EXPECT_THROW_MSG(impl_.init(config), ConfigError,
                     "boolValue() called on non-Bool Element");

    impl_.reset();
    config = Element::createMap();
    config->set("retries", Element::create("no"));
    EXPECT_THROW_MSG(impl_.init(config), ConfigError,
                     "intValue() called on non-integer Element");

    impl_.reset();
    config = Element::createMap();
    config->set("retries", Element::create(-1));
    expected.str("");
    expected << "bad retries -1 not in [0.."
             << numeric_limits<unsigned>::max() << "]";
    EXPECT_THROW_MSG(impl_.init(config), ConfigError, expected.str());

    impl_.reset();
    config = Element::createMap();
    config->set("retries", Element::create(123456789000));
    expected.str("");
    expected << "bad retries 123456789000 not in [0.."
             << numeric_limits<unsigned>::max() << "]";
    EXPECT_THROW_MSG(impl_.init(config), ConfigError, expected.str());

    impl_.reset();
    config = Element::createMap();
    config->set("session-history", Element::create(-1));
    EXPECT_THROW_MSG(impl_.init(config), ConfigError,
                     "stringValue() called on non-string Element");

    config = Element::createMap();
    config->set("thread-pool-size", Element::create("large"));
    EXPECT_THROW_MSG(impl_.init(config), ConfigError,
                     "intValue() called on non-integer Element");

    impl_.reset();
    config = Element::createMap();
    config->set("timeout", Element::create("no"));
    EXPECT_THROW_MSG(impl_.init(config), ConfigError,
                     "intValue() called on non-integer Element");

    impl_.reset();
    config = Element::createMap();
    config->set("timeout", Element::create(-1));
    expected.str("");
    expected << "bad timeout -1 not in [0.."
             << (numeric_limits<long>::max() / 1000) << "]";
    EXPECT_THROW_MSG(impl_.init(config), ConfigError, expected.str());

    impl_.reset();
    config = Element::createMap();
    config->set("timeout", Element::create(10000000000000000));
    expected.str("");
    expected << "bad timeout 10000000000000000 not in [0.."
             << (numeric_limits<long>::max() / 1000) << "]";
    EXPECT_THROW_MSG(impl_.init(config), ConfigError, expected.str());

    impl_.reset();
    config = Element::createMap();
    config->set("access", Element::create(false));
    expected.str("");
    expected << "expected service to be map, but got boolean instead"
             << " (parsing access)";
    EXPECT_THROW_MSG(impl_.init(config), ConfigError, expected.str());

    impl_.reset();
    config = Element::createMap();
    config->set("accounting", Element::create(true));
    expected.str("");
    expected << "expected service to be map, but got boolean instead"
             << " (parsing accounting)";
    EXPECT_THROW_MSG(impl_.init(config), ConfigError, expected.str());
}

// Verify syntax of nas-ports.
TEST_F(ConfigTest, nasPorts) {
    EXPECT_TRUE(impl_.remap_.empty());

    // Nas-ports can be empty.
    ElementPtr config = Element::createMap();
    config->set("nas-ports", Element::createList());
    EXPECT_NO_THROW(impl_.init(config));
    EXPECT_TRUE(impl_.remap_.empty());

    // Default.
    impl_.reset();
    config = Element::createMap();
    ElementPtr ports = Element::createList();
    ElementPtr entry = Element::createMap();
    entry->set("port", Element::create(10));
    ports->add(entry);
    config->set("nas-ports", ports);
    EXPECT_NO_THROW(impl_.init(config));
    EXPECT_EQ(1, impl_.remap_.size());
    EXPECT_EQ(10, impl_.remap_[SUBNET_ID_DEFAULT]);

    // Subnet-id.
    impl_.reset();
    config = Element::createMap();
    ports = Element::createList();
    entry = Element::createMap();
    entry->set("port", Element::create(10));
    entry->set("subnet-id", Element::create(1));
    ports->add(entry);
    config->set("nas-ports", ports);
    EXPECT_NO_THROW(impl_.init(config));
    EXPECT_EQ(1, impl_.remap_.size());
    EXPECT_EQ(10, impl_.remap_[1]);

    // Subnet-prefix - IPv4.
    impl_.reset();
    config = Element::createMap();
    ports = Element::createList();
    entry = Element::createMap();
    entry->set("port", Element::create(10));
    CfgMgr::instance().setFamily(AF_INET);
    Subnet4Ptr subnet4(new Subnet4(IOAddress("192.0.2.0"), 24, 1, 2, 3, 1));
    CfgMgr::instance().getStagingCfg()->getCfgSubnets4()->add(subnet4);
    entry->set("subnet-prefix", Element::create("192.0.2.0/24"));
    ports->add(entry);
    config->set("nas-ports", ports);
    EXPECT_NO_THROW(impl_.init(config));
    EXPECT_EQ(1, impl_.remap_.size());
    EXPECT_EQ(10, impl_.remap_[1]);

    // Subnet-prefix - IPv6.
    impl_.reset();
    config = Element::createMap();
    ports = Element::createList();
    entry = Element::createMap();
    entry->set("port", Element::create(10));
    CfgMgr::instance().setFamily(AF_INET6);
    Subnet6Ptr subnet6(new Subnet6(IOAddress("2001:db8::"),
                                   64, 1, 2, 3, 4, 1));
    CfgMgr::instance().getStagingCfg()->getCfgSubnets6()->add(subnet6);
    entry->set("subnet-prefix", Element::create("2001:db8::/64"));
    ports->add(entry);
    config->set("nas-ports", ports);
    EXPECT_NO_THROW(impl_.init(config));
    EXPECT_EQ(1, impl_.remap_.size());
    EXPECT_EQ(10, impl_.remap_[1]);

    // Shared-network - IPv4.
    impl_.reset();
    config = Element::createMap();
    ports = Element::createList();
    entry = Element::createMap();
    entry->set("port", Element::create(10));
    CfgMgr::instance().setFamily(AF_INET);
    auto networks4 =
        CfgMgr::instance().getStagingCfg()->getCfgSharedNetworks4();
    SharedNetwork4Ptr network4(new SharedNetwork4("frog"));
    networks4->add(network4);
    subnet4.reset(new Subnet4(IOAddress("192.0.2.0"), 25, 1, 2, 3, 1));
    subnet4->setReservationsGlobal(true);
    subnet4->setReservationsInSubnet(false);
    network4->add(subnet4);
    subnet4.reset(new Subnet4(IOAddress("192.0.2.128"), 25, 1, 2, 3, 2));
    subnet4->setReservationsGlobal(true);
    subnet4->setReservationsInSubnet(false);
    network4->add(subnet4);
    entry->set("shared-network-name", Element::create("frog"));
    ports->add(entry);
    config->set("nas-ports", ports);
    EXPECT_NO_THROW(impl_.init(config));
    EXPECT_EQ(2, impl_.remap_.size());
    EXPECT_EQ(10, impl_.remap_[1]);
    EXPECT_EQ(10, impl_.remap_[2]);

    // Shared-network - IPv6.
    impl_.reset();
    config = Element::createMap();
    ports = Element::createList();
    entry = Element::createMap();
    entry->set("port", Element::create(10));
    CfgMgr::instance().setFamily(AF_INET6);
    auto networks6 =
        CfgMgr::instance().getStagingCfg()->getCfgSharedNetworks6();
    SharedNetwork6Ptr network6(new SharedNetwork6("frog"));
    networks6->add(network6);
    subnet6.reset(new Subnet6(IOAddress("2001:db8::"), 64, 1, 2, 3, 4, 1));
    subnet6->setReservationsGlobal(true);
    subnet6->setReservationsInSubnet(false);
    network6->add(subnet6);
    subnet6.reset(new Subnet6(IOAddress("2001:db8:1::"), 64, 1, 2, 3, 4, 2));
    subnet6->setReservationsGlobal(true);
    subnet6->setReservationsInSubnet(false);
    network6->add(subnet6);
    entry->set("shared-network-name", Element::create("frog"));
    ports->add(entry);
    config->set("nas-ports", ports);
    EXPECT_NO_THROW(impl_.init(config));
    EXPECT_EQ(2, impl_.remap_.size());
    EXPECT_EQ(10, impl_.remap_[1]);
    EXPECT_EQ(10, impl_.remap_[2]);

    // Error cases.
    CfgMgr::instance().clear();

    // Not a list.
    impl_.reset();
    config = Element::createMap();
    ports = Element::createMap();
    config->set("nas-ports", ports);
    EXPECT_THROW_MSG(impl_.init(config), ConfigError,
                     "listValue() called on non-list Element");
    EXPECT_TRUE(impl_.remap_.empty());

    // Not a map.
    impl_.reset();
    config = Element::createMap();
    ports = Element::createList();
    entry = Element::createList();
    ports->add(entry);
    config->set("nas-ports", ports);
    EXPECT_THROW_MSG(impl_.init(config), ConfigError,
                     "get(string) called on a non-map Element");
    EXPECT_TRUE(impl_.remap_.empty());

    // Empty map.
    impl_.reset();
    config = Element::createMap();
    ports = Element::createList();
    entry = Element::createMap();
    ports->add(entry);
    config->set("nas-ports", ports);
    string expected = "missing port in nas-ports entry: ";
    expected += entry->str();
    EXPECT_THROW_MSG(impl_.init(config), ConfigError, expected);
    EXPECT_TRUE(impl_.remap_.empty());

    // No value.
    impl_.reset();
    config = Element::createMap();
    ports = Element::createList();
    entry = Element::createMap();
    entry->set("subnet-id", Element::create(1));
    ports->add(entry);
    config->set("nas-ports", ports);
    expected = "missing port in nas-ports entry: ";
    expected += entry->str();
    EXPECT_THROW_MSG(impl_.init(config), ConfigError, expected);
    EXPECT_TRUE(impl_.remap_.empty());

    // Unknown selector.
    impl_.reset();
    config = Element::createMap();
    ports = Element::createList();
    entry = Element::createMap();
    entry->set("port", Element::create(10));
    entry->set("id", Element::create(1));
    ports->add(entry);
    config->set("nas-ports", ports);
    expected = "unknown selector in ";
    expected += entry->str();
    EXPECT_THROW_MSG(impl_.init(config), ConfigError, expected);
    EXPECT_TRUE(impl_.remap_.empty());

    // Can't find prefix.
    impl_.reset();
    config = Element::createMap();
    ports = Element::createList();
    entry = Element::createMap();
    entry->set("port", Element::create(10));
    entry->set("subnet-prefix", Element::create("192.0.2.0/24"));
    ports->add(entry);
    config->set("nas-ports", ports);
    expected = "can't find subnet for ";
    expected += entry->str();
    EXPECT_THROW_MSG(impl_.init(config), ConfigError, expected);
    EXPECT_TRUE(impl_.remap_.empty());

    // Can't find name.
    impl_.reset();
    config = Element::createMap();
    ports = Element::createList();
    entry = Element::createMap();
    entry->set("port", Element::create(10));
    entry->set("shared-network-name", Element::create("frog"));
    ports->add(entry);
    config->set("nas-ports", ports);
    expected = "can't find shared network for ";
    expected += entry->str();
    EXPECT_THROW_MSG(impl_.init(config), ConfigError, expected);
    EXPECT_TRUE(impl_.remap_.empty());
}

// Verify syntax of services.
TEST_F(ConfigTest, services) {
    // Services can be empty.
    ElementPtr config = Element::createMap();
    config->set("access", Element::createMap());
    config->set("accounting", Element::createMap());
    EXPECT_NO_THROW(impl_.init(config));

    // Simple attribute.
    impl_.reset();
    config = Element::createMap();
    ElementPtr access = Element::createMap();
    config->set("access", access);
    ElementPtr attrs = Element::createList();
    access->set("attributes", attrs);
    ElementPtr attr = Element::createMap();
    attrs->add(attr);
    attr->set("name", Element::create("User-Name"));
    attr->set("type", Element::create(1));
    attr->set("data", Element::create("foobar"));
    EXPECT_NO_THROW(impl_.init(config));

    string expected = "{ "
        "\"attributes\": [ {"
        "   \"name\": \"User-Name\", "
        "   \"type\": 1, "
        "   \"data\": \"foobar\" "
        "} ],"
        "\"enabled\": false,"
        "\"idle-timer-interval\": 0"
        "}";
    runToElementTest<RadiusService>(expected, *impl_.auth_);

    // Needs a server to be enabled.
    EXPECT_FALSE(impl_.tls_->enabled_);
    EXPECT_FALSE(impl_.auth_->enabled_);
    EXPECT_FALSE(impl_.acct_->enabled_);
    config = Element::createMap();
    ElementPtr acct = Element::createMap();
    config->set("accounting", acct);
    ElementPtr servers = Element::createList();
    acct->set("servers", servers);
    ElementPtr server1 = Element::createMap();
    servers->add(server1);
    impl_.reset();
    // Name and secret are required.
    server1->set("port", Element::create(16460));
    EXPECT_THROW_MSG(impl_.init(config), ConfigError,
                     "missing parameter 'name' (:0:0) (parsing accounting)");
    impl_.reset();
    server1->set("name", Element::create("127.0.0.1"));
    EXPECT_THROW_MSG(impl_.init(config), ConfigError,
                     "missing parameter 'secret' (:0:0) (parsing accounting)");
    impl_.reset();
    // Default secret is refused.
    server1->set("secret", Element::create("1234"));
    EXPECT_THROW_MSG(impl_.init(config), ConfigError,
                     "illegal use of a default secret (parsing accounting)");
    impl_.reset();
    server1->set("secret", Element::create("1111"));
    ElementPtr server2 = Element::createMap();
    servers->add(server2);
    server2->set("secret", Element::create("22222"));
    impl_.reset();
    EXPECT_THROW_MSG(impl_.init(config), ConfigError,
                     "missing parameter 'name' (:0:0) (parsing accounting)");
    impl_.reset();
    server2->set("name", Element::create("::1"));
    EXPECT_NO_THROW(impl_.init(config));

    expected = "{ "
        "\"enabled\": true,"
        "\"idle-timer-interval\": 0,"
        "\"servers\": [ {"
        "   \"deadtime\": 0, "
        "   \"local-address\": \"127.0.0.1\", "
        "   \"peer-address\": \"127.0.0.1\", "
        "   \"peer-port\": 16460, "
        "   \"secret\": \"1111\", "
        "   \"timeout\": 10 "
        "},{"
        "   \"deadtime\": 0, "
        "   \"local-address\": \"::1\", "
        "   \"peer-address\": \"::1\", "
        "   \"peer-port\": 1813, "
        "   \"secret\": \"22222\", "
        "   \"timeout\": 10 "
        "} ] }";
    runToElementTest<RadiusService>(expected, *impl_.acct_);

    // A server means enabled.
    EXPECT_TRUE(impl_.acct_->enabled_);

    // Check state.
    Servers srvs = impl_.acct_->servers_;
    ASSERT_EQ(2, srvs.size());
    ServerPtr srv = srvs[0];
    ASSERT_TRUE(srv);
    EXPECT_EQ("127.0.0.1", srv->getPeerAddress().toText());
    EXPECT_EQ(16460, srv->getPeerPort());

    // Add auth too.
    ElementPtr auth = Element::createMap();
    config->set("access", auth);
    ElementPtr auth_servers = Element::createList();
    auth->set("servers", auth_servers);
    ElementPtr auth_server1 = Element::createMap();
    auth_servers->add(auth_server1);
    impl_.reset();
    // Name and secret are required.
    auth_server1->set("port", Element::create(16450));
    EXPECT_THROW_MSG(impl_.init(config), ConfigError,
                     "missing parameter 'name' (:0:0) (parsing access)");
    impl_.reset();
    auth_server1->set("name", Element::create("127.0.0.1"));
    EXPECT_THROW_MSG(impl_.init(config), ConfigError,
                     "missing parameter 'secret' (:0:0) (parsing access)");
    impl_.reset();
    auth_server1->set("secret", Element::create("1111"));
    ElementPtr auth_server2 = Element::createMap();
    auth_servers->add(auth_server2);
    auth_server2->set("secret", Element::create("22222"));
    impl_.reset();
    EXPECT_THROW_MSG(impl_.init(config), ConfigError,
                     "missing parameter 'name' (:0:0) (parsing access)");
    impl_.reset();
    auth_server2->set("name", Element::create("::1"));
    EXPECT_NO_THROW(impl_.init(config));

    expected = "{ "
        "\"enabled\": true,"
        "\"idle-timer-interval\": 0,"
        "\"servers\": [ {"
        "   \"deadtime\": 0, "
        "   \"local-address\": \"127.0.0.1\", "
        "   \"peer-address\": \"127.0.0.1\", "
        "   \"peer-port\": 16450, "
        "   \"secret\": \"1111\", "
        "   \"timeout\": 10 "
        "},{"
        "   \"deadtime\": 0, "
        "   \"local-address\": \"::1\", "
        "   \"peer-address\": \"::1\", "
        "   \"peer-port\": 1812, "
        "   \"secret\": \"22222\", "
        "   \"timeout\": 10 "
        "} ] }";
    runToElementTest<RadiusService>(expected, *impl_.auth_);

    // A server means enabled.
    EXPECT_TRUE(impl_.auth_->enabled_);

    // Check state.
    srvs = impl_.auth_->servers_;
    ASSERT_EQ(2, srvs.size());
    srv = srvs[0];
    ASSERT_TRUE(srv);
    EXPECT_EQ("127.0.0.1", srv->getPeerAddress().toText());
    EXPECT_EQ(16450, srv->getPeerPort());
}

// Verify syntax of tls service.
TEST_F(ConfigTest, tls) {
    // TCP is not implemented.
    ElementPtr config = Element::createMap();
    config->set("protocol", Element::create(string("TCP")));
    string expected = "protocol 'TCP' is not supported";
    EXPECT_THROW_MSG(impl_.init(config), ConfigError, expected);
    config->set("protocol", Element::create(string("UDP")));
    EXPECT_NO_THROW(impl_.init(config));

    // Services can be empty.
    ElementPtr tls = Element::createMap();
    ElementPtr access = Element::createMap();
    ElementPtr accounting = Element::createMap();
    config->set("tls", tls);
    config->set("access", access);
    config->set("accounting", accounting);
    expected = "'tls' service can't be configured when protocol ";
    expected += "is not 'TLS'";
    EXPECT_THROW_MSG(impl_.init(config), ConfigError, expected);
    config->set("protocol", Element::create(string("TLS")));
    EXPECT_NO_THROW(impl_.init(config));
    EXPECT_FALSE(impl_.tls_->enabled_);
    EXPECT_TRUE(impl_.auth_->enabled_);
    EXPECT_TRUE(impl_.acct_->enabled_);

    // Can't set enabled in tls.
    tls->set("enabled", Element::create(true));
    expected = "can't set enabled in 'tls' (parsing tls)";
    EXPECT_THROW_MSG(impl_.init(config), ConfigError, expected);

    // Overwrite enabled.
    tls = Element::createMap();
    config->set("tls", tls);
    accounting->set("enabled", Element::create(false));
    EXPECT_NO_THROW(impl_.init(config));
    EXPECT_FALSE(impl_.tls_->enabled_);
    EXPECT_TRUE(impl_.auth_->enabled_);
    EXPECT_FALSE(impl_.acct_->enabled_);

    accounting = Element::createMap();
    config->set("accounting", accounting);
    access->set("enabled", Element::create(false));
    EXPECT_NO_THROW(impl_.init(config));
    EXPECT_FALSE(impl_.tls_->enabled_);
    EXPECT_FALSE(impl_.auth_->enabled_);
    EXPECT_TRUE(impl_.acct_->enabled_);

    // Servers is forbidden outside tls.
    tls = Element::createMap();
    access = Element::createMap();
    accounting = Element::createMap();
    config->set("tls", tls);
    config->set("access", access);
    config->set("accounting", accounting);
    access->set("servers", Element::createList());
    expected = "can't have servers entry in 'access' with TLS ";
    expected += "(parsing access)";
    EXPECT_THROW_MSG(impl_.init(config), ConfigError, expected);
    access = Element::createMap();
    config->set("access", access);
    accounting->set("servers", Element::createList());
    expected = "can't have servers entry in 'accounting' with TLS ";
    expected += "(parsing accounting)";
    EXPECT_THROW_MSG(impl_.init(config), ConfigError, expected);

    // Idle timer interval is forbidden outside tls.
    tls = Element::createMap();
    access = Element::createMap();
    accounting = Element::createMap();
    config->set("tls", tls);
    config->set("access", access);
    config->set("accounting", accounting);
    access->set("idle-timer-interval", Element::create(60));
    expected = "can't have idle-timer-interval entry in 'access' with TLS ";
    expected += "(parsing access)";
    EXPECT_THROW_MSG(impl_.init(config), ConfigError, expected);
    access = Element::createMap();
    config->set("access", access);
    accounting->set("idle-timer-interval", Element::create(60));
    expected = "can't have idle-timer-interval entry in 'accounting' with TLS ";
    expected += "(parsing accounting)";
    EXPECT_THROW_MSG(impl_.init(config), ConfigError, expected);

    // Attribute is forbidden in tls.
    tls = Element::createMap();
    access = Element::createMap();
    accounting = Element::createMap();
    config->set("tls", tls);
    config->set("access", access);
    config->set("accounting", accounting);
    tls->set("attributes", Element::createList());
    expected = "can't define attributes in 'tls' (parsing tls)";
    EXPECT_THROW_MSG(impl_.init(config), ConfigError, expected);

    // Set idle timer interval in tls.
    tls = Element::createMap();
    config->set("tls", tls);
    tls->set("idle-timer-interval", Element::create(60));
    EXPECT_NO_THROW(impl_.init(config));
    EXPECT_EQ(60, impl_.tls_->idle_timer_interval_);
    EXPECT_EQ(0, impl_.auth_->idle_timer_interval_);
    EXPECT_EQ(0, impl_.acct_->idle_timer_interval_);

    // Servers for tls require TLS.
    ElementPtr servers = Element::createList();
    ElementPtr server = Element::createMap();
    server->set("name", Element::create("127.0.0.1"));
    // Secret is not required with TLS as it defaults to "radsec".
    servers->add(server);
    tls->set("servers", servers);
    expected = "missing parameter 'trust-anchor' (:0:0) (parsing tls)";
    EXPECT_THROW_MSG(impl_.init(config), ConfigError, expected);
    string trust_anchor = TEST_CA_DIR;
    server->set("trust-anchor", Element::create(trust_anchor));
    string cert_file = TEST_CA_DIR "/kea-client.crt";
    server->set("cert-file", Element::create(cert_file));
    string key_file = TEST_CA_DIR "/kea-client.key";
    server->set("key-file", Element::create(key_file));
    EXPECT_NO_THROW(impl_.init(config));
    expected = "{ "
        "\"access\": {"
        "   \"enabled\": true,"
        "   \"idle-timer-interval\": 0"
        "}, "
        "\"accounting\": {"
        "   \"enabled\": true,"
        "   \"idle-timer-interval\": 0"
        "}, "
        "\"bindaddr\": \"*\", "
        "\"canonical-mac-address\": false, "
        "\"client-id-pop0\": false, "
        "\"client-id-printable\": false, "
        "\"tls\": {"
        "   \"enabled\": true,"
        "   \"idle-timer-interval\": 60, "
        "   \"servers\": [ {"
        "     \"deadtime\": 0, "
        "     \"local-address\": \"127.0.0.1\", "
        "     \"peer-address\": \"127.0.0.1\", "
        "     \"peer-port\": 2083, "
        "     \"secret\": \"radsec\", "
        "     \"timeout\": 10, "
        "     \"tls-context\": true "
        "} ] }, "
        "\"deadtime\": 0, "
        "\"dictionary\": \"" + string(DICTIONARY) + "\", "
        "\"extract-duid\": true, "
        "\"identifier-type4\": \"client-id\", "
        "\"identifier-type6\": \"duid\", "
        "\"protocol\": \"TLS\", "
        "\"reselect-subnet-address\": false, "
        "\"reselect-subnet-pool\": false, "
        "\"retries\": 3, "
        "\"session-history\": \"\", "
        "\"thread-pool-size\": 0, "
        "\"timeout\": 10"
        " }";
    runToElementTest<RadiusImpl>(expected, impl_);
}

// Verify parsing of attributes.
TEST_F(ConfigTest, attribute) {
    // Need the dictionary.
    ElementPtr config = Element::createMap();
    EXPECT_NO_THROW(impl_.init(config));

    // Add vendor too.
    IntCstDefPtr cstv(new IntCstDef(PW_VENDOR_SPECIFIC, "DSL-Forum", 3561));
    ASSERT_NO_THROW(AttrDefs::instance().add(cstv));
    AttrDefPtr defv(new AttrDef(1, "Agent-Circuit-Id", PW_TYPE_STRING, 3561));
    ASSERT_NO_THROW(AttrDefs::instance().add(defv));

    RadiusServicePtr srv(new RadiusService("test"));
    ASSERT_TRUE(srv);
    RadiusAttributeParser parser;

    // Attribute must be a map.
    ElementPtr attr = Element::createList();
    EXPECT_THROW_MSG(parser.parse(srv, attr), TypeError,
                     "get(string) called on a non-map Element");
    EXPECT_TRUE(srv->attributes_.empty());

    // Vendor must be a string.
    attr = Element::createMap();
    attr->set("vendor", Element::create(1234));
    EXPECT_THROW_MSG(parser.parse(srv, attr), TypeError,
                     "vendor parameter must be a string");

    // Named vendor must be known.
    attr->set("vendor", Element::create("foobar"));
    EXPECT_THROW_MSG(parser.parse(srv, attr), ConfigError,
                     "can't parse vendor 'foobar'");

    // Name or type is required.
    attr = Element::createMap();
    attr->set("data", Element::create("foobar"));
    EXPECT_THROW_MSG(parser.parse(srv, attr), ConfigError,
                     "name or type are required");
    EXPECT_TRUE(srv->attributes_.empty());

    // Name must be known.
    attr->set("name", Element::create("No-Such-Attribute"));
    EXPECT_THROW_MSG(parser.parse(srv, attr), ConfigError,
                     "attribute 'No-Such-Attribute' is unknown");

    attr->set("name", Element::create("User-Name"));
    attr->set("vendor", Element::create("DSL-Forum"));
    EXPECT_THROW_MSG(parser.parse(srv, attr), ConfigError,
                     "attribute 'User-Name' in vendor 'DSL-Forum' is unknown");
    attr->set("vendor", Element::create("1234"));
    EXPECT_THROW_MSG(parser.parse(srv, attr), ConfigError,
                     "attribute 'User-Name' in vendor '1234' is unknown");
    attr->set("vendor", Element::create(""));

    // Type and name must match.
    attr->set("name", Element::create("User-Name"));
    attr->set("type", Element::create(123));
    EXPECT_THROW_MSG(parser.parse(srv, attr), ConfigError,
                     "'User-Name' attribute has type 1, not 123");

    attr->set("name", Element::create("Agent-Circuit-Id"));
    attr->set("vendor", Element::create("DSL-Forum"));
    string expected = "'Agent-Circuit-Id' attribute in vendor 'DSL-Forum' ";
    expected += "has type 1, not 123";
    EXPECT_THROW_MSG(parser.parse(srv, attr), ConfigError, expected);
    attr->set("vendor", Element::create("3561"));
    expected = "'Agent-Circuit-Id' attribute in vendor '3561' ";
    expected += "has type 1, not 123";
    EXPECT_THROW_MSG(parser.parse(srv, attr), ConfigError, expected);
    attr->set("name", Element::create("User-Name"));
    attr->set("vendor", Element::create(""));

    // Type must be between 0 and 255.
    attr = Element::createMap();
    attr->set("data", Element::create("foobar"));
    attr->set("type", Element::create(-1));
    EXPECT_THROW_MSG(parser.parse(srv, attr), ConfigError,
                     "out of range attribute type -1");

    attr = Element::createMap();
    attr->set("data", Element::create("foobar"));
    attr->set("type", Element::create(256));
    EXPECT_THROW_MSG(parser.parse(srv, attr), ConfigError,
                     "out of range attribute type 256");

    // Type must be known too.
    attr = Element::createMap();
    attr->set("data", Element::create("foobar"));
    attr->set("type", Element::create(234));
    EXPECT_THROW_MSG(parser.parse(srv, attr), ConfigError,
                     "attribute type 234 is unknown");
    attr->set("vendor", Element::create("DSL-Forum"));
    EXPECT_THROW_MSG(parser.parse(srv, attr), ConfigError,
                     "attribute type 234 in vendor 'DSL-Forum' is unknown");
    attr->set("vendor", Element::create("1234"));
    EXPECT_THROW_MSG(parser.parse(srv, attr), ConfigError,
                     "attribute type 234 in vendor '1234' is unknown");

    // Set a type.
    attr = Element::createMap();
    attr->set("data", Element::create("foobar"));
    attr->set("type", Element::create(1));
    EXPECT_NO_THROW(parser.parse(srv, attr));

    // Get the option to look at into.
    EXPECT_FALSE(srv->attributes_.empty());
    EXPECT_EQ(1, srv->attributes_.size());
    EXPECT_TRUE(srv->attributes_.getDef(1));
    EXPECT_FALSE(srv->attributes_.getExpr(1));
    EXPECT_EQ("", srv->attributes_.getTest(1));
    ConstAttributePtr got = srv->attributes_.get(1);
    ASSERT_TRUE(got);
    EXPECT_EQ("User-Name='foobar'", got->toText());

    // Another way to check.
    expected = "[ { "
        " \"name\": \"User-Name\", "
        " \"type\": 1, "
        " \"data\": \"foobar\" } ]";
    runToElementTest<CfgAttributes>(expected, srv->attributes_);

    // Check with a vendor.
    srv->attributes_.clear();
    attr = Element::createMap();
    attr->set("vendor", Element::create("DSL-Forum"));
    attr->set("data", Element::create("foobar"));
    attr->set("type", Element::create(1));
    EXPECT_NO_THROW(parser.parse(srv, attr));
    EXPECT_FALSE(srv->attributes_.empty());
    EXPECT_EQ(1, srv->attributes_.size());
    EXPECT_TRUE(srv->attributes_.getDef(1, 3561));
    EXPECT_FALSE(srv->attributes_.getExpr(1, 3561));
    EXPECT_EQ("", srv->attributes_.getTest(1, 3561));
    got = srv->attributes_.get(1, 3561);
    ASSERT_TRUE(got);
    EXPECT_EQ("Vendor-Specific=[3561]0x0108666F6F626172", got->toText());
    expected = "[ { "
        " \"name\": \"Vendor-Specific\", "
        " \"type\": 26, "
        " \"vendor\": \"3561\", "
        " \"vsa-raw\": \"0108666F6F626172\" } ]";
    runToElementTest<CfgAttributes>(expected, srv->attributes_);

    // Vendor-Specific (26) does not support textual data.
    srv->attributes_.clear();
    attr = Element::createMap();
    attr->set("data", Element::create("foobar"));
    attr->set("type", Element::create(26));
    expected = "can't create Vendor-Specific attribute from [foobar]: ";
    expected += "can't decode vsa from text";
    EXPECT_THROW_MSG(parser.parse(srv, attr), ConfigError, expected);

    // One of expr, data, raw
    srv->attributes_.clear();
    attr = Element::createMap();
    attr->set("data", Element::create("foobar"));
    attr->set("type", Element::create(1));
    attr->set("expr", Element::create("option[1].hex"));
    EXPECT_THROW_MSG(parser.parse(srv, attr), ConfigError,
                     "data, raw and expr are exclusive");

    attr = Element::createMap();
    attr->set("type", Element::create(1));
    attr->set("expr", Element::create("option[1].hex"));
    attr->set("raw", Element::create("01ef"));
    EXPECT_THROW_MSG(parser.parse(srv, attr), ConfigError,
                     "data, raw and expr are exclusive");

    attr = Element::createMap();
    attr->set("type", Element::create(1));
    attr->set("data", Element::create("foobar"));
    attr->set("raw", Element::create("01ef"));
    EXPECT_THROW_MSG(parser.parse(srv, attr), ConfigError,
                     "data and raw are exclusive");

    // Check with raw.
    srv->attributes_.clear();
    attr = Element::createMap();
    attr->set("type", Element::create(1));
    // Raw is in hexadecimal.
    attr->set("raw", Element::create("gaga"));
    EXPECT_THROW_MSG(parser.parse(srv, attr), ConfigError,
                     "can't decode raw: [gaga] for User-Name attribute");
    // Odd number of hexadecimal digits works.
    attr->set("raw", Element::create("1ac"));
    EXPECT_NO_THROW(parser.parse(srv, attr));

    // Try the raw version of User-Name f\001\0002bar.
    srv->attributes_.clear();
    attr->set("raw", Element::create("660102626172"));
    EXPECT_NO_THROW(parser.parse(srv, attr));
    EXPECT_EQ(1, srv->attributes_.getAll().size());
    EXPECT_FALSE(srv->attributes_.getExpr(1));
    EXPECT_EQ("", srv->attributes_.getTest(1));
    const ConstAttributePtr& firstr = srv->attributes_.get(1);
    ASSERT_TRUE(firstr);
    EXPECT_EQ("User-Name=0x660102626172", firstr->toText());
    expected = "[ { "
        " \"name\": \"User-Name\", "
        " \"type\": 1, "
        " \"raw\": \"660102626172\" } ]";
    runToElementTest<CfgAttributes>(expected, srv->attributes_);

    // Try the raw version of DSL-Forum (3561) Agent-Circuit-Id (1).
    srv->attributes_.clear();
    attr = Element::createMap();
    attr->set("vendor", Element::create("DSL-Forum"));
    attr->set("raw", Element::create("660102626172"));
    attr->set("type", Element::create(1));
    EXPECT_NO_THROW(parser.parse(srv, attr));
    EXPECT_FALSE(srv->attributes_.empty());
    EXPECT_EQ(1, srv->attributes_.size());
    EXPECT_TRUE(srv->attributes_.getDef(1, 3561));
    EXPECT_FALSE(srv->attributes_.getExpr(1, 3561));
    EXPECT_EQ("", srv->attributes_.getTest(1, 3561));
    got = srv->attributes_.get(1, 3561);
    ASSERT_TRUE(got);
    EXPECT_EQ("Vendor-Specific=[3561]0x0108660102626172", got->toText());
    expected = "[ { "
        " \"name\": \"Vendor-Specific\", "
        " \"type\": 26, "
        " \"vendor\": \"3561\", "
        " \"vsa-raw\": \"0108660102626172\" } ]";
    runToElementTest<CfgAttributes>(expected, srv->attributes_);

    // Check with expr.
    srv->attributes_.clear();
    attr = Element::createMap();
    attr->set("type", Element::create(1));
    // The expression must follow the eval syntax for strings.
    attr->set("expr", Element::create("'foobar"));
    expected = "expression: ['foobar] error: ";
    expected += "<string>:1.1: Invalid character: '";
    expected += " for User-Name attribute";
    EXPECT_THROW_MSG(parser.parse(srv, attr), ConfigError, expected);

    attr = Element::createMap();
    attr->set("type", Element::create(1));
    attr->set("expr", Element::create("option[1].exists"));
    expected = "expression: [option[1].exists] error: ";
    expected += "<string>:1.11-16: syntax error, unexpected exists, ";
    expected += "expecting option or text or hex";
    expected += " for User-Name attribute";
    EXPECT_THROW_MSG(parser.parse(srv, attr), ConfigError, expected);

    // Try the 'foobar' expression.
    attr->set("expr", Element::create("'foobar'"));
    EXPECT_NO_THROW(parser.parse(srv, attr));
    EXPECT_EQ(1, srv->attributes_.size());
    EXPECT_TRUE(srv->attributes_.getAll().empty());
    ExpressionPtr expr = srv->attributes_.getExpr(1);
    ASSERT_TRUE(expr);
    ASSERT_EQ(1, expr->size());
    TokenPtr token = (*expr)[0];
    boost::shared_ptr<TokenString> tokstr =
        boost::dynamic_pointer_cast<TokenString>(token);
    EXPECT_TRUE(tokstr);
    // No way to get the string from the token without evaluating it.

    EXPECT_EQ("'foobar'", srv->attributes_.getTest(1));
    expected = "[ { "
        " \"name\": \"User-Name\", "
        " \"type\": 1, "
        " \"expr\": \"'foobar'\" } ]";
    runToElementTest<CfgAttributes>(expected, srv->attributes_);

    // Try with vendor.
    srv->attributes_.clear();
    attr = Element::createMap();
    attr->set("vendor", Element::create("3561"));
    attr->set("type", Element::create(1));
    attr->set("expr", Element::create("'foobar'"));
    EXPECT_NO_THROW(parser.parse(srv, attr));
    EXPECT_EQ(1, srv->attributes_.size());
    EXPECT_TRUE(srv->attributes_.getDef(1, 3561));
    EXPECT_FALSE(srv->attributes_.get(1, 3561));
    EXPECT_TRUE(srv->attributes_.getAll().empty());
    expr = srv->attributes_.getExpr(1, 3561);
    ASSERT_TRUE(expr);
    ASSERT_EQ(1, expr->size());
    token = (*expr)[0];
    tokstr = boost::dynamic_pointer_cast<TokenString>(token);
    EXPECT_TRUE(tokstr);
    EXPECT_EQ("'foobar'", srv->attributes_.getTest(1, 3561));
    expected = "[ { "
      " \"name\": \"Agent-Circuit-Id\", "
      " \"type\": 1, "
      " \"vendor\": \"3561\", "
      " \"expr\": \"'foobar'\" } ]";
    runToElementTest<CfgAttributes>(expected, srv->attributes_);

    // Evaluate.
    Pkt4Ptr query(new Pkt4(DHCPDISCOVER, 12345));
    Attributes evaluated;
    EXPECT_NO_THROW_LOG(evaluated = srv->attributes_.getEvalAll(*query));
    EXPECT_EQ(1, evaluated.size());
    expected = "[ { "
        " \"name\": \"Vendor-Specific\", "
        " \"type\": 26, "
        " \"vendor\": \"3561\", "
        " \"vsa-raw\": \"0108666F6F626172\" } ]";
    runToElementTest<Attributes>(expected, evaluated);
}

// Verify checkAttributes sanity check.
TEST_F(ConfigTest, checkAttributes) {
    // Need the dictionary.
    ElementPtr config = Element::createMap();
    EXPECT_NO_THROW(impl_.init(config));

    // Enable services.
    impl_.auth_->enabled_ = true;
    impl_.acct_->enabled_ = true;

    // Build an attribute using an expression.
    ElementPtr srv_cfg = Element::createMap();
    RadiusServiceParser parser;
    ElementPtr attrs = Element::createList();
    srv_cfg->set("attributes", attrs);
    ElementPtr attr = Element::createMap();
    attrs->add(attr);
    attr->set("name", Element::create("User-Name"));
    attr->set("type", Element::create(1));
    attr->set("expr", Element::create("option[1].hex"));

    // Works with access.
    ASSERT_NO_THROW(parser.parse(impl_.auth_, srv_cfg));
    ASSERT_NO_THROW(parser.checkAttributes(impl_.auth_));

    // Throws with accounting,
    ASSERT_NO_THROW(parser.parse(impl_.acct_, srv_cfg));
    EXPECT_THROW(parser.checkAttributes(impl_.acct_), ConfigError);
}

// Verify checkEarlyGlobalResvLookup (vs. hook configuration).
TEST_F(ConfigTest, checkEarlyGlobalResvLookup) {
    CfgMgr::instance().setFamily(AF_INET);
    ElementPtr config = Element::createMap();
    EXPECT_NO_THROW(impl_.init(config));
    EXPECT_FALSE(HostMgr::instance().getDisableSingleQuery());
    impl_.reset();

    // Set the flag in the staging config.
    CfgMgr::instance().getStagingCfg()->
        addConfiguredGlobal("early-global-reservations-lookup", Element::create(true));
    EXPECT_THROW(impl_.init(config), ConfigError);
}

// Verify checkSharedNetworks server configuration (vs. hook configuration)
// checks for IPv4.
TEST_F(ConfigTest, checkSharedNetworks4) {
    CfgMgr::instance().setFamily(AF_INET);
    ElementPtr config = Element::createMap();
    EXPECT_NO_THROW(impl_.init(config));
    EXPECT_FALSE(HostMgr::instance().getDisableSingleQuery());
    impl_.reset();

    // Create a shared network.
    auto networks = CfgMgr::instance().getStagingCfg()->getCfgSharedNetworks4();
    SharedNetwork4Ptr network(new SharedNetwork4("frog"));
    ASSERT_NO_THROW(networks->add(network));

    // Retry: the disable single query should change.
    EXPECT_NO_THROW(impl_.init(config));
    EXPECT_TRUE(HostMgr::instance().getDisableSingleQuery());
    impl_.reset();

    // Add a subnet: a shared network with at most one subnet is ignored.
    Subnet4Ptr subnet1(new Subnet4(IOAddress("192.0.2.0"), 25, 1, 2, 3, 1));
    EXPECT_NO_THROW(network->add(subnet1));
    EXPECT_NO_THROW(impl_.init(config));
    impl_.reset();

    // Add a second subnet.
    Subnet4Ptr subnet2(new Subnet4(IOAddress("192.0.2.128"), 25, 1, 2, 3, 2));
    EXPECT_NO_THROW(network->add(subnet2));
    EXPECT_THROW(impl_.init(config), ConfigError);
    impl_.reset();

    // Set global HR mode.
    subnet1->setReservationsGlobal(true);
    subnet1->setReservationsInSubnet(false);
    subnet2->setReservationsGlobal(true);
    subnet2->setReservationsInSubnet(false);
    EXPECT_NO_THROW(impl_.init(config));
}

// Verify checkSharedNetworks server configuration (vs. hook configuration)
// checks for IPv4 using parent inheritance.
TEST_F(ConfigTest, parentCheckSharedNetworks4) {
    CfgMgr::instance().setFamily(AF_INET);
    ElementPtr config = Element::createMap();

    // Create a shared network.
    auto networks = CfgMgr::instance().getStagingCfg()->getCfgSharedNetworks4();
    SharedNetwork4Ptr network(new SharedNetwork4("frog"));
    ASSERT_NO_THROW(networks->add(network));

    // Add two subnets.
    Subnet4Ptr subnet1(new Subnet4(IOAddress("192.0.2.0"), 25, 1, 2, 3, 1));
    Subnet4Ptr subnet2(new Subnet4(IOAddress("192.0.2.128"), 25, 1, 2, 3, 2));
    EXPECT_NO_THROW(network->add(subnet1));
    EXPECT_NO_THROW(network->add(subnet2));
    EXPECT_THROW(impl_.init(config), ConfigError);
    impl_.reset();

    // Set global HR mode on the parent.
    network->setReservationsGlobal(true);
    network->setReservationsInSubnet(false);
    EXPECT_NO_THROW(impl_.init(config));
}

// Verify checkSharedNetworks server configuration (vs. hook configuration)
// checks for IPv4 using *staging* global inheritance.
TEST_F(ConfigTest, globalCheckSharedNetworks4) {
    CfgMgr::instance().setFamily(AF_INET);
    ElementPtr config = Element::createMap();

    // Create a shared network.
    auto networks = CfgMgr::instance().getStagingCfg()->getCfgSharedNetworks4();
    SharedNetwork4Ptr network(new SharedNetwork4("frog"));
    ASSERT_NO_THROW(networks->add(network));

    // Add two subnets.
    Subnet4Ptr subnet1(new Subnet4(IOAddress("192.0.2.0"), 25, 1, 2, 3, 1));
    Subnet4Ptr subnet2(new Subnet4(IOAddress("192.0.2.128"), 25, 1, 2, 3, 2));
    EXPECT_NO_THROW(network->add(subnet1));
    EXPECT_NO_THROW(network->add(subnet2));
    EXPECT_THROW(impl_.init(config), ConfigError);
    impl_.reset();

    // Set global HR mode at global scope in current config.
    CfgMgr::instance().getCurrentCfg()->
        addConfiguredGlobal("reservations-global", Element::create(true));
    CfgMgr::instance().getCurrentCfg()->
        addConfiguredGlobal("reservations-in-subnet", Element::create(false));
    EXPECT_THROW(impl_.init(config), ConfigError);
    impl_.reset();

    // Set global HR mode at global scope in staging config.
    CfgMgr::instance().getStagingCfg()->
        addConfiguredGlobal("reservations-global", Element::create(true));
    CfgMgr::instance().getStagingCfg()->
        addConfiguredGlobal("reservations-in-subnet", Element::create(false));
    EXPECT_NO_THROW(impl_.init(config));
}

// Verify checkSharedNetworks server configuration (vs. hook configuration)
// checks for IPv6.
TEST_F(ConfigTest, checkSharedNetworks6) {
    CfgMgr::instance().setFamily(AF_INET6);
    ElementPtr config = Element::createMap();
    EXPECT_NO_THROW(impl_.init(config));
    EXPECT_FALSE(HostMgr::instance().getDisableSingleQuery());
    impl_.reset();

    // Create a shared network.
    auto networks = CfgMgr::instance().getStagingCfg()->getCfgSharedNetworks6();
    SharedNetwork6Ptr network(new SharedNetwork6("frog"));
    ASSERT_NO_THROW(networks->add(network));

    // Retry: the disable single query should change.
    EXPECT_NO_THROW(impl_.init(config));
    EXPECT_TRUE(HostMgr::instance().getDisableSingleQuery());
    impl_.reset();

    // Add a subnet: a shared network with at most one subnet is ignored.
    Subnet6Ptr subnet1(new Subnet6(IOAddress("2001:db8:0:1::"),
                                   64, 1, 2, 3, 4, 1));
    EXPECT_NO_THROW(network->add(subnet1));
    EXPECT_NO_THROW(impl_.init(config));
    impl_.reset();

    // Add a second subnet.
    Subnet6Ptr subnet2(new Subnet6(IOAddress("2001:db8:0:2::"),
                                   64, 1, 2, 3, 4, 2));
    EXPECT_NO_THROW(network->add(subnet2));
    EXPECT_THROW(impl_.init(config), ConfigError);
    impl_.reset();

    // Set global HR mode.
    subnet1->setReservationsGlobal(true);
    subnet1->setReservationsInSubnet(false);
    subnet2->setReservationsGlobal(true);
    subnet2->setReservationsInSubnet(false);
    EXPECT_NO_THROW(impl_.init(config));
}

// Verify checkSharedNetworks server configuration (vs. hook configuration)
// checks for IPv6 using parent inheritance.
TEST_F(ConfigTest, parentCheckSharedNetworks6) {
    CfgMgr::instance().setFamily(AF_INET6);
    ElementPtr config = Element::createMap();

    // Create a shared network.
    auto networks = CfgMgr::instance().getStagingCfg()->getCfgSharedNetworks6();
    SharedNetwork6Ptr network(new SharedNetwork6("frog"));
    ASSERT_NO_THROW(networks->add(network));

    // Add two subnets.
    Subnet6Ptr subnet1(new Subnet6(IOAddress("2001:db8:0:1::"),
                                   64, 1, 2, 3, 4, 1));
    Subnet6Ptr subnet2(new Subnet6(IOAddress("2001:db8:0:2::"),
                                   64, 1, 2, 3, 4, 2));
    EXPECT_NO_THROW(network->add(subnet1));
    EXPECT_NO_THROW(network->add(subnet2));
    EXPECT_THROW(impl_.init(config), ConfigError);
    impl_.reset();

    // Set global HR mode on the parent.
    network->setReservationsGlobal(true);
    network->setReservationsInSubnet(false);
    EXPECT_NO_THROW(impl_.init(config));
}

// Verify checkSharedNetworks server configuration (vs. hook configuration)
// checks for IPv6 using *staging* global inheritance.
TEST_F(ConfigTest, globalCheckSharedNetworks6) {
    CfgMgr::instance().setFamily(AF_INET6);
    ElementPtr config = Element::createMap();

    // Create a shared network.
    auto networks = CfgMgr::instance().getStagingCfg()->getCfgSharedNetworks6();
    SharedNetwork6Ptr network(new SharedNetwork6("frog"));
    ASSERT_NO_THROW(networks->add(network));

    // Add two subnets.
    Subnet6Ptr subnet1(new Subnet6(IOAddress("2001:db8:0:1::"),
                                   64, 1, 2, 3, 4, 1));
    Subnet6Ptr subnet2(new Subnet6(IOAddress("2001:db8:0:2::"),
                                   64, 1, 2, 3, 4, 2));
    EXPECT_NO_THROW(network->add(subnet1));
    EXPECT_NO_THROW(network->add(subnet2));
    EXPECT_THROW(impl_.init(config), ConfigError);
    impl_.reset();

    // Set global HR mode at global scope in current config.
    CfgMgr::instance().getCurrentCfg()->
        addConfiguredGlobal("reservations-global", Element::create(true));
    CfgMgr::instance().getCurrentCfg()->
        addConfiguredGlobal("reservations-in-subnet", Element::create(false));
    EXPECT_THROW(impl_.init(config), ConfigError);
    impl_.reset();

    // Set global HR mode at global scope in staging config.
    CfgMgr::instance().getStagingCfg()->
        addConfiguredGlobal("reservations-global", Element::create(true));
    CfgMgr::instance().getStagingCfg()->
        addConfiguredGlobal("reservations-in-subnet", Element::create(false));
    EXPECT_NO_THROW(impl_.init(config));
}

// Verify that peer-updates can be configured and that proper errors are
// reported in negative cases.
TEST_F(ConfigTest, peerUpdates) {
    ElementPtr config;

    config = Element::fromJSON(R"({
        "access": {
            "peer-updates": false
        }
    })");
    EXPECT_THROW_MSG(impl_.init(config), ConfigError,
                     "peer-updates configured for the access service, but "
                     "it is only supported for the accounting service "
                     "(parsing access)");
    EXPECT_NO_THROW_LOG(impl_.reset());

    config = Element::fromJSON(R"({
        "access": {
            "peer-updates": true
        }
    })");
    EXPECT_THROW_MSG(impl_.init(config), ConfigError,
                     "peer-updates configured for the access service, but "
                     "it is only supported for the accounting service "
                     "(parsing access)");
    EXPECT_NO_THROW_LOG(impl_.reset());

    config = Element::fromJSON(R"({
        "access": {
            "peer-updates": 0
        }
    })");
    EXPECT_THROW_MSG(impl_.init(config), ConfigError,
                     "peer-updates configured for the access service, but "
                     "it is only supported for the accounting service "
                     "(parsing access)");
    EXPECT_NO_THROW_LOG(impl_.reset());

    config = Element::fromJSON(R"({
        "accounting": {
            "peer-updates": false
        }
    })");
    EXPECT_NO_THROW_LOG(impl_.init(config));
    ASSERT_TRUE(impl_.acct_);
    EXPECT_FALSE(impl_.acct_->peer_updates_);
    EXPECT_NO_THROW_LOG(impl_.reset());

    config = Element::fromJSON(R"({
        "accounting": {
            "peer-updates": true
        }
    })");
    EXPECT_NO_THROW_LOG(impl_.init(config));
    ASSERT_TRUE(impl_.acct_);
    EXPECT_TRUE(impl_.acct_->peer_updates_);
    EXPECT_NO_THROW_LOG(impl_.reset());

    config = Element::fromJSON(R"({
        "accounting": {
            "peer-updates": 0
        }
    })");
    EXPECT_THROW_MSG(impl_.init(config), ConfigError,
                     "expected peer-updates to be boolean, but got integer "
                     "instead (parsing accounting)");
    EXPECT_NO_THROW_LOG(impl_.reset());
}

// Verify that max-pending-requests can be configured and that proper errors
// are reported in negative cases.
TEST_F(ConfigTest, maxPendingRequests) {
    ElementPtr config;

    config = Element::fromJSON(R"({
        "accounting": {
            "max-pending-requests": 10
        }
    })");
    EXPECT_THROW_MSG(impl_.init(config), ConfigError,
                     "max-pending-requests configured for the accounting "
                     "service, but it is only supported for the access "
                     "service (parsing accounting)");
    EXPECT_NO_THROW_LOG(impl_.reset());

    config = Element::fromJSON(R"({
        "access": {
            "max-pending-requests": -1
        }
    })");
    EXPECT_THROW_MSG(impl_.init(config), ConfigError,
                     "expected max-pending-requests to be positive, but got "
                     "-1 instead (parsing access)");
    EXPECT_NO_THROW_LOG(impl_.reset());

    config = Element::fromJSON(R"({
        "access": {
            "max-pending-requests": false
        }
    })");
    EXPECT_THROW_MSG(impl_.init(config), ConfigError,
                     "expected max-pending-requests to be integer, but got "
                     "boolean instead (parsing access)");
    EXPECT_NO_THROW_LOG(impl_.reset());

    config = Element::fromJSON(R"({
        "access": {
            "max-pending-requests": 10
        }
    })");
    EXPECT_NO_THROW_LOG(impl_.init(config));
    ASSERT_TRUE(impl_.auth_);
    EXPECT_EQ(10, impl_.auth_->max_pending_requests_);
    EXPECT_NO_THROW_LOG(impl_.reset());

    config = Element::createMap();
    EXPECT_NO_THROW_LOG(impl_.init(config));
    ASSERT_TRUE(impl_.auth_);
    EXPECT_EQ(0, impl_.auth_->max_pending_requests_);
    EXPECT_NO_THROW_LOG(impl_.reset());

    config = Element::fromJSON(R"({
        "access": {
            "max-pending-request": 10
        }
    })");
    EXPECT_THROW_MSG(impl_.init(config), ConfigError,
                     "unknown service parameter: max-pending-request "
                     "(parsing access)");
    EXPECT_NO_THROW_LOG(impl_.reset());
}

// Verify that idle-timer-interval can be configured and that proper errors
// are reported in negative cases.
TEST_F(ConfigTest, idleTimerInterval) {
    ElementPtr config;

    config = Element::fromJSON(R"({
        "access": {
            "idle-timer-interval": -1
        }
    })");
    EXPECT_THROW_MSG(impl_.init(config), ConfigError,
                     "expected idle-timer-interval to be positive, but got "
                     "-1 instead (parsing access)");
    EXPECT_NO_THROW_LOG(impl_.reset());

    config = Element::fromJSON(R"({
        "accounting": {
            "idle-timer-interval": false
        }
    })");
    EXPECT_THROW_MSG(impl_.init(config), ConfigError,
                     "expected idle-timer-interval to be integer, but got "
                     "boolean instead (parsing accounting)");
    EXPECT_NO_THROW_LOG(impl_.reset());

    config = Element::fromJSON(R"({
        "access": {
            "idle-timer-interval": 10
        }
    })");
    EXPECT_NO_THROW_LOG(impl_.init(config));
    ASSERT_TRUE(impl_.auth_);
    EXPECT_EQ(10, impl_.auth_->idle_timer_interval_);
    EXPECT_NO_THROW_LOG(impl_.reset());

    config = Element::createMap();
    EXPECT_NO_THROW_LOG(impl_.init(config));
    ASSERT_TRUE(impl_.auth_);
    EXPECT_EQ(0, impl_.auth_->idle_timer_interval_);
    EXPECT_NO_THROW_LOG(impl_.reset());
}

} // end of anonymous namespace
