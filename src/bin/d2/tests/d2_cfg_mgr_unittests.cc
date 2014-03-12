// Copyright (C) 2013-2014 Internet Systems Consortium, Inc. ("ISC")
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

#include <config/module_spec.h>
#include <d2/d2_config.h>
#include <d2/d2_cfg_mgr.h>
#include <d_test_stubs.h>
#include <test_data_files_config.h>

#include <boost/foreach.hpp>
#include <gtest/gtest.h>

using namespace std;
using namespace isc;
using namespace isc::d2;

namespace {

std::string specfile(const std::string& name) {
    return (std::string(D2_SRC_DIR) + "/" + name);
}

/// @brief Test fixture class for testing D2CfgMgr class.
/// It maintains an member instance of D2CfgMgr and provides methods for
/// converting JSON strings to configuration element sets, checking parse
/// results, and accessing the configuration context.
class D2CfgMgrTest : public ConfigParseTest {
public:

    /// @brief Constructor
    D2CfgMgrTest():cfg_mgr_(new D2CfgMgr) {
    }

    /// @brief Destructor
    ~D2CfgMgrTest() {
    }

    /// @brief Configuration manager instance.
    D2CfgMgrPtr cfg_mgr_;
};

/// @brief Tests that the spec file is valid.
/// Verifies that the BIND10 DHCP-DDNS configuration specification file
//  is valid.
TEST(D2SpecTest, basicSpec) {
    ASSERT_NO_THROW(isc::config::
                    moduleSpecFromFile(specfile("dhcp-ddns.spec")));
}

/// @brief Convenience function which compares the contents of the given
/// DnsServerInfo against the given set of values.
///
/// It is structured in such a way that each value is checked, and output
/// is generate for all that do not match.
///
/// @param server is a pointer to the server to check against.
/// @param hostname is the value to compare against server's hostname_.
/// @param ip_address is the string value to compare against server's
/// ip_address_.
/// @param port is the value to compare against server's port.
///
/// @return returns true if there is a match across the board, otherwise it
/// returns false.
bool checkServer(DnsServerInfoPtr server, const char* hostname,
                 const char *ip_address, uint32_t port)
{
    // Return value, assume its a match.
    bool result = true;

    if (!server) {
        EXPECT_TRUE(server);
        return false;
    }

    // Check hostname.
    if (server->getHostname() != hostname) {
        EXPECT_EQ(hostname, server->getHostname());
        result = false;
    }

    // Check IP address.
    if (server->getIpAddress().toText() != ip_address) {
        EXPECT_EQ(ip_address, server->getIpAddress().toText());
        result = false;
    }

    // Check port.
    if (server->getPort() !=  port) {
        EXPECT_EQ (port, server->getPort());
        result = false;
    }

    return (result);
}

/// @brief Convenience function which compares the contents of the given
/// TSIGKeyInfo against the given set of values.
///
/// It is structured in such a way that each value is checked, and output
/// is generate for all that do not match.
///
/// @param key is a pointer to the key to check against.
/// @param name is the value to compare against key's name_.
/// @param algorithm is the string value to compare against key's algorithm.
/// @param secret is the value to compare against key's secret.
///
/// @return returns true if there is a match across the board, otherwise it
/// returns false.
bool checkKey(TSIGKeyInfoPtr key, const char* name,
                 const char *algorithm, const char* secret)
{
    // Return value, assume its a match.
    bool result = true;
    if (!key) {
        EXPECT_TRUE(key);
        return false;
    }

    // Check name.
    if (key->getName() != name) {
        EXPECT_EQ(name, key->getName());
        result = false;
    }

    // Check algorithm.
    if (key->getAlgorithm() != algorithm) {
        EXPECT_EQ(algorithm, key->getAlgorithm());
        result = false;
    }

    // Check secret.
    if (key->getSecret() !=  secret) {
        EXPECT_EQ (secret, key->getSecret());
        result = false;
    }

    return (result);
}

/// @brief Test fixture class for testing DnsServerInfo parsing.
class TSIGKeyInfoTest : public ConfigParseTest {
public:

    /// @brief Constructor
    TSIGKeyInfoTest() {
        reset();
    }

    /// @brief Destructor
    ~TSIGKeyInfoTest() {
    }

    /// @brief Wipe out the current storage and parser and replace
    /// them with new ones.
    void reset() {
        keys_.reset(new TSIGKeyInfoMap());
        parser_.reset(new TSIGKeyInfoParser("test", keys_));
    }

    /// @brief Storage for "committing" keys.
    TSIGKeyInfoMapPtr keys_;

    /// @brief Pointer to the current parser instance.
    isc::dhcp::ParserPtr parser_;
};

/// @brief Test fixture class for testing DnsServerInfo parsing.
class DnsServerInfoTest : public ConfigParseTest {
public:

    /// @brief Constructor
    DnsServerInfoTest() {
        reset();
    }

    /// @brief Destructor
    ~DnsServerInfoTest() {
    }

    /// @brief Wipe out the current storage and parser and replace
    /// them with new ones.
    void reset() {
        servers_.reset(new DnsServerInfoStorage());
        parser_.reset(new DnsServerInfoParser("test", servers_));
    }

    /// @brief Storage for "committing" servers.
    DnsServerInfoStoragePtr servers_;

    /// @brief Pointer to the current parser instance.
    isc::dhcp::ParserPtr parser_;
};


/// @brief Test fixture class for testing DDnsDomain parsing.
class DdnsDomainTest : public ConfigParseTest {
public:

    /// @brief Constructor
    DdnsDomainTest() {
        reset();
    }

    /// @brief Destructor
    ~DdnsDomainTest() {
    }

    /// @brief Wipe out the current storage and parser and replace
    /// them with new ones.
    void reset() {
        keys_.reset(new TSIGKeyInfoMap());
        domains_.reset(new DdnsDomainMap());
        parser_.reset(new DdnsDomainParser("test", domains_, keys_));
    }

    /// @brief Add TSIGKeyInfos to the key map
    ///
    /// @param name the name of the key
    /// @param algorithm the algorithm of the key
    /// @param secret the secret value of the key
    void addKey(const std::string& name, const std::string& algorithm,
                const std::string& secret) {
        TSIGKeyInfoPtr key_info(new TSIGKeyInfo(name, algorithm, secret));
        (*keys_)[name]=key_info;
    }

    /// @brief Storage for "committing" domains.
    DdnsDomainMapPtr domains_;

    /// @brief Storage for TSIGKeys
    TSIGKeyInfoMapPtr keys_;

    /// @brief Pointer to the current parser instance.
    isc::dhcp::ParserPtr parser_;
};

/// @brief Tests the enforcement of data validation when parsing TSIGKeyInfos.
/// It verifies that:
/// 1. Name cannot be blank.
/// 2. Algorithm cannot be blank.
/// 3. Secret cannot be blank.
/// @TODO TSIG keys are not fully functional. Only basic validation is
/// currently supported. This test will need to expand as they evolve.
TEST_F(TSIGKeyInfoTest, invalidEntry) {
    // Config with a blank name entry.
    std::string config = "{"
                         " \"name\": \"\" , "
                         " \"algorithm\": \"md5\" , "
                         " \"secret\": \"0123456789\" "
                         "}";
    ASSERT_TRUE(fromJSON(config));

    // Verify that build succeeds but commit fails on blank name.
    EXPECT_NO_THROW(parser_->build(config_set_));
    EXPECT_THROW(parser_->commit(), D2CfgError);

    // Config with a blank algorithm entry.
    config = "{"
                         " \"name\": \"d2_key_one\" , "
                         " \"algorithm\": \"\" , "
                         " \"secret\": \"0123456789\" "
                         "}";

    ASSERT_TRUE(fromJSON(config));

    // Verify that build succeeds but commit fails on blank algorithm.
    EXPECT_NO_THROW(parser_->build(config_set_));
    EXPECT_THROW(parser_->commit(), D2CfgError);

    // Config with a blank secret entry.
    config = "{"
                         " \"name\": \"d2_key_one\" , "
                         " \"algorithm\": \"md5\" , "
                         " \"secret\": \"\" "
                         "}";

    ASSERT_TRUE(fromJSON(config));

    // Verify that build succeeds but commit fails on blank secret.
    EXPECT_NO_THROW(parser_->build(config_set_));
    EXPECT_THROW(parser_->commit(), D2CfgError);
}

/// @brief Verifies that TSIGKeyInfo parsing creates a proper TSIGKeyInfo
/// when given a valid combination of entries.
TEST_F(TSIGKeyInfoTest, validEntry) {
    // Valid entries for TSIG key, all items are required.
    std::string config = "{"
                         " \"name\": \"d2_key_one\" , "
                         " \"algorithm\": \"md5\" , "
                         " \"secret\": \"0123456789\" "
                         "}";
    ASSERT_TRUE(fromJSON(config));

    // Verify that it builds and commits without throwing.
    ASSERT_NO_THROW(parser_->build(config_set_));
    ASSERT_NO_THROW(parser_->commit());

    // Verify the correct number of keys are present
    int count =  keys_->size();
    EXPECT_EQ(1, count);

    // Find the key and retrieve it.
    TSIGKeyInfoMap::iterator gotit = keys_->find("d2_key_one");
    ASSERT_TRUE(gotit != keys_->end());
    TSIGKeyInfoPtr& key = gotit->second;

    // Verify the key contents.
    EXPECT_TRUE(checkKey(key, "d2_key_one", "md5", "0123456789"));
}

/// @brief Verifies that attempting to parse an invalid list of TSIGKeyInfo
/// entries is detected.
TEST_F(TSIGKeyInfoTest, invalidTSIGKeyList) {
    // Construct a list of keys with an invalid key entry.
    std::string config = "["

                         " { \"name\": \"key1\" , "
                         "   \"algorithm\": \"algo1\" ,"
                         "   \"secret\": \"secret11\" "
                         " },"
                         " { \"name\": \"key2\" , "
                         "   \"algorithm\": \"\" ,"
                         "   \"secret\": \"secret12\" "
                         " },"
                         " { \"name\": \"key3\" , "
                         "   \"algorithm\": \"algo3\" ,"
                         "   \"secret\": \"secret13\" "
                         " }"
                         " ]";

    ASSERT_TRUE(fromJSON(config));

    // Create the list parser.
    isc::dhcp::ParserPtr parser;
    ASSERT_NO_THROW(parser.reset(new TSIGKeyInfoListParser("test", keys_)));

    // Verify that the list builds without errors.
    ASSERT_NO_THROW(parser->build(config_set_));

    // Verify that the list commit fails.
    EXPECT_THROW(parser->commit(), D2CfgError);
}

/// @brief Verifies that attempting to parse an invalid list of TSIGKeyInfo
/// entries is detected.
TEST_F(TSIGKeyInfoTest, duplicateTSIGKey) {
    // Construct a list of keys with an invalid key entry.
    std::string config = "["

                         " { \"name\": \"key1\" , "
                         "   \"algorithm\": \"algo1\" ,"
                         "   \"secret\": \"secret11\" "
                         " },"
                         " { \"name\": \"key2\" , "
                         "   \"algorithm\": \"algo2\" ,"
                         "   \"secret\": \"secret12\" "
                         " },"
                         " { \"name\": \"key1\" , "
                         "   \"algorithm\": \"algo3\" ,"
                         "   \"secret\": \"secret13\" "
                         " }"
                         " ]";

    ASSERT_TRUE(fromJSON(config));

    // Create the list parser.
    isc::dhcp::ParserPtr parser;
    ASSERT_NO_THROW(parser.reset(new TSIGKeyInfoListParser("test", keys_)));

    // Verify that the list builds without errors.
    ASSERT_NO_THROW(parser->build(config_set_));

    // Verify that the list commit fails.
    EXPECT_THROW(parser->commit(), D2CfgError);
}

/// @brief Verifies a valid list of TSIG Keys parses correctly.
TEST_F(TSIGKeyInfoTest, validTSIGKeyList) {
    // Construct a valid list of keys.
    std::string config = "["

                         " { \"name\": \"key1\" , "
                         "   \"algorithm\": \"algo1\" ,"
                         "   \"secret\": \"secret1\" "
                         " },"
                         " { \"name\": \"key2\" , "
                         "   \"algorithm\": \"algo2\" ,"
                         "   \"secret\": \"secret2\" "
                         " },"
                         " { \"name\": \"key3\" , "
                         "   \"algorithm\": \"algo3\" ,"
                         "   \"secret\": \"secret3\" "
                         " }"
                         " ]";

    ASSERT_TRUE(fromJSON(config));

    // Verify that the list builds and commits without errors.
    // Create the list parser.
    isc::dhcp::ParserPtr parser;
    ASSERT_NO_THROW(parser.reset(new TSIGKeyInfoListParser("test", keys_)));
    ASSERT_NO_THROW(parser->build(config_set_));
    ASSERT_NO_THROW(parser->commit());

    // Verify the correct number of keys are present
    int count =  keys_->size();
    ASSERT_EQ(3, count);

    // Find the 1st key and retrieve it.
    TSIGKeyInfoMap::iterator gotit = keys_->find("key1");
    ASSERT_TRUE(gotit != keys_->end());
    TSIGKeyInfoPtr& key = gotit->second;

    // Verify the key contents.
    EXPECT_TRUE(checkKey(key, "key1", "algo1", "secret1"));

    // Find the 2nd key and retrieve it.
    gotit = keys_->find("key2");
    ASSERT_TRUE(gotit != keys_->end());
    key = gotit->second;

    // Verify the key contents.
    EXPECT_TRUE(checkKey(key, "key2", "algo2", "secret2"));

    // Find the 3rd key and retrieve it.
    gotit = keys_->find("key3");
    ASSERT_TRUE(gotit != keys_->end());
    key = gotit->second;

    // Verify the key contents.
    EXPECT_TRUE(checkKey(key, "key3", "algo3", "secret3"));
}

/// @brief Tests the enforcement of data validation when parsing DnsServerInfos.
/// It verifies that:
/// 1. Specifying both a hostname and an ip address is not allowed.
/// 2. Specifying both blank a hostname and blank ip address is not allowed.
/// 3. Specifying a negative port number is not allowed.
TEST_F(DnsServerInfoTest, invalidEntry) {
    // Create a config in which both host and ip address are supplied.
    // Verify that it builds without throwing but commit fails.
    std::string config = "{ \"hostname\": \"pegasus.tmark\", "
                         "  \"ip_address\": \"127.0.0.1\" } ";
    ASSERT_TRUE(fromJSON(config));
    EXPECT_NO_THROW(parser_->build(config_set_));
    EXPECT_THROW(parser_->commit(), D2CfgError);

    // Neither host nor ip address supplied
    // Verify that it builds without throwing but commit fails.
    config = "{ \"hostname\": \"\", "
             "  \"ip_address\": \"\" } ";
    ASSERT_TRUE(fromJSON(config));
    EXPECT_NO_THROW(parser_->build(config_set_));
    EXPECT_THROW(parser_->commit(), D2CfgError);

    // Create a config with a negative port number.
    // Verify that build fails.
    config = "{ \"ip_address\": \"192.168.5.6\" ,"
             "  \"port\": -100 }";
    ASSERT_TRUE(fromJSON(config));
    EXPECT_THROW (parser_->build(config_set_), isc::BadValue);
}


/// @brief Verifies that DnsServerInfo parsing creates a proper DnsServerInfo
/// when given a valid combination of entries.
/// It verifies that:
/// 1. A DnsServerInfo entry is correctly made, when given only a hostname.
/// 2. A DnsServerInfo entry is correctly made, when given ip address and port.
/// 3. A DnsServerInfo entry is correctly made, when given only an ip address.
TEST_F(DnsServerInfoTest, validEntry) {
    // Valid entries for dynamic host
    std::string config = "{ \"hostname\": \"pegasus.tmark\" }";
    ASSERT_TRUE(fromJSON(config));

    // Verify that it builds and commits without throwing.
    ASSERT_NO_THROW(parser_->build(config_set_));
    ASSERT_NO_THROW(parser_->commit());

    // Verify the correct number of servers are present
    int count =  servers_->size();
    EXPECT_EQ(1, count);

    // Verify the server exists and has the correct values.
    DnsServerInfoPtr server = (*servers_)[0];
    EXPECT_TRUE(checkServer(server, "pegasus.tmark",
                            DnsServerInfo::EMPTY_IP_STR,
                            DnsServerInfo::STANDARD_DNS_PORT));

    // Start over for a new test.
    reset();

    // Valid entries for static ip
    config = " { \"ip_address\": \"127.0.0.1\" , "
             "  \"port\": 100 }";
    ASSERT_TRUE(fromJSON(config));

    // Verify that it builds and commits without throwing.
    ASSERT_NO_THROW(parser_->build(config_set_));
    ASSERT_NO_THROW(parser_->commit());

    // Verify the correct number of servers are present
    count =  servers_->size();
    EXPECT_EQ(1, count);

    // Verify the server exists and has the correct values.
    server = (*servers_)[0];
    EXPECT_TRUE(checkServer(server, "", "127.0.0.1", 100));

    // Start over for a new test.
    reset();

    // Valid entries for static ip, no port
    config = " { \"ip_address\": \"192.168.2.5\" }";
    ASSERT_TRUE(fromJSON(config));

    // Verify that it builds and commits without throwing.
    ASSERT_NO_THROW(parser_->build(config_set_));
    ASSERT_NO_THROW(parser_->commit());

    // Verify the correct number of servers are present
    count =  servers_->size();
    EXPECT_EQ(1, count);

    // Verify the server exists and has the correct values.
    server = (*servers_)[0];
    EXPECT_TRUE(checkServer(server, "", "192.168.2.5",
                            DnsServerInfo::STANDARD_DNS_PORT));
}

/// @brief Verifies that attempting to parse an invalid list of DnsServerInfo
/// entries is detected.
TEST_F(ConfigParseTest, invalidServerList) {
    // Construct a list of servers with an invalid server entry.
    std::string config = "[ { \"hostname\": \"one.tmark\" }, "
                        "{ \"hostname\": \"\" }, "
                        "{ \"hostname\": \"three.tmark\" } ]";
    ASSERT_TRUE(fromJSON(config));

    // Create the server storage and list parser.
    DnsServerInfoStoragePtr servers(new DnsServerInfoStorage());
    isc::dhcp::ParserPtr parser;
    ASSERT_NO_THROW(parser.reset(new DnsServerInfoListParser("test", servers)));

    // Verify that the list builds without errors.
    ASSERT_NO_THROW(parser->build(config_set_));

    // Verify that the list commit fails.
    EXPECT_THROW(parser->commit(), D2CfgError);
}

/// @brief Verifies that a list of DnsServerInfo entries parses correctly given
/// a valid configuration.
TEST_F(ConfigParseTest, validServerList) {
    // Create a valid list of servers.
    std::string config = "[ { \"hostname\": \"one.tmark\" }, "
                        "{ \"hostname\": \"two.tmark\" }, "
                        "{ \"hostname\": \"three.tmark\" } ]";
    ASSERT_TRUE(fromJSON(config));

    // Create the server storage and list parser.
    DnsServerInfoStoragePtr servers(new DnsServerInfoStorage());
    isc::dhcp::ParserPtr parser;
    ASSERT_NO_THROW(parser.reset(new DnsServerInfoListParser("test", servers)));

    // Verfiy that the list builds and commits without error.
    ASSERT_NO_THROW(parser->build(config_set_));
    ASSERT_NO_THROW(parser->commit());

    // Verify that the server storage contains the correct number of servers.
    int count =  servers->size();
    EXPECT_EQ(3, count);

    // Verify the first server exists and has the correct values.
    DnsServerInfoPtr server = (*servers)[0];
    EXPECT_TRUE(checkServer(server, "one.tmark", DnsServerInfo::EMPTY_IP_STR,
                            DnsServerInfo::STANDARD_DNS_PORT));

    // Verify the second server exists and has the correct values.
    server = (*servers)[1];
    EXPECT_TRUE(checkServer(server, "two.tmark", DnsServerInfo::EMPTY_IP_STR,
                            DnsServerInfo::STANDARD_DNS_PORT));

    // Verify the third server exists and has the correct values.
    server = (*servers)[2];
    EXPECT_TRUE(checkServer(server, "three.tmark", DnsServerInfo::EMPTY_IP_STR,
                            DnsServerInfo::STANDARD_DNS_PORT));
}

/// @brief Tests the enforcement of data validation when parsing DdnsDomains.
/// It verifies that:
/// 1. Domain storage cannot be null when constructing a DdnsDomainParser.
/// 2. The name entry is not optional.
/// 3. The server list man not be empty.
/// 4. That a mal-formed server entry is detected.
/// 5. That an undefined key name is detected.
TEST_F(DdnsDomainTest, invalidDdnsDomainEntry) {
    // Verify that attempting to construct the parser with null storage fails.
    DdnsDomainMapPtr domains;
    ASSERT_THROW(isc::dhcp::ParserPtr(
                 new DdnsDomainParser("test", domains, keys_)), D2CfgError);

    // Create a domain configuration without a name
    std::string config = "{  \"key_name\": \"d2_key.tmark.org\" , "
                         "  \"dns_servers\" : [ "
                         "  {  \"ip_address\": \"127.0.0.1\" , "
                         "    \"port\": 100 },"
                         "  { \"ip_address\": \"127.0.0.2\" , "
                         "    \"port\": 200 },"
                         "  {  \"ip_address\": \"127.0.0.3\" , "
                         "    \"port\": 300 } ] } ";
    ASSERT_TRUE(fromJSON(config));

    // Verify that the domain configuration builds but commit fails.
    ASSERT_NO_THROW(parser_->build(config_set_));
    ASSERT_THROW(parser_->commit(), isc::dhcp::DhcpConfigError);

    // Create a domain configuration with an empty server list.
    config = "{ \"name\": \"tmark.org\" , "
             "  \"key_name\": \"d2_key.tmark.org\" , "
             "  \"dns_servers\" : [ "
             "   ] } ";
    ASSERT_TRUE(fromJSON(config));

    // Verify that the domain configuration build fails.
    ASSERT_THROW(parser_->build(config_set_), D2CfgError);

    // Create a domain configuration with a mal-formed server entry.
    config = "{ \"name\": \"tmark.org\" , "
             "  \"key_name\": \"d2_key.tmark.org\" , "
             "  \"dns_servers\" : [ "
             "  {  \"ip_address\": \"127.0.0.3\" , "
             "    \"port\": -1 } ] } ";
    ASSERT_TRUE(fromJSON(config));

    // Verify that the domain configuration build fails.
    ASSERT_THROW(parser_->build(config_set_), isc::BadValue);

    // Create a domain configuration without an defined key name
    config = "{ \"name\": \"tmark.org\" , "
             "  \"key_name\": \"d2_key.tmark.org\" , "
             "  \"dns_servers\" : [ "
             "  {  \"ip_address\": \"127.0.0.3\" , "
             "    \"port\": 300 } ] } ";
    ASSERT_TRUE(fromJSON(config));

    // Verify that the domain configuration build succeeds but commit fails.
    ASSERT_NO_THROW(parser_->build(config_set_));
    ASSERT_THROW(parser_->commit(), D2CfgError);
}

/// @brief Verifies the basics of parsing DdnsDomains.
/// It verifies that:
/// 1. Valid construction of DdnsDomainParser functions.
/// 2. Given a valid, configuration entry, DdnsDomainParser parses
/// correctly.
/// (It indirectly verifies the operation of DdnsDomainMap).
TEST_F(DdnsDomainTest, ddnsDomainParsing) {
    // Create a valid domain configuration entry containing three valid
    // servers.
    std::string config =
                        "{ \"name\": \"tmark.org\" , "
                        "  \"key_name\": \"d2_key.tmark.org\" , "
                        "  \"dns_servers\" : [ "
                        "  {  \"ip_address\": \"127.0.0.1\" , "
                        "    \"port\": 100 },"
                        "  { \"ip_address\": \"127.0.0.2\" , "
                        "    \"port\": 200 },"
                        "  {  \"ip_address\": \"127.0.0.3\" , "
                        "    \"port\": 300 } ] } ";
    ASSERT_TRUE(fromJSON(config));

    // Add a TSIG key to the test key map, so key validation will pass.
    addKey("d2_key.tmark.org", "md5", "0123456789");

    // Verify that the domain configuration builds and commits without error.
    ASSERT_NO_THROW(parser_->build(config_set_));
    ASSERT_NO_THROW(parser_->commit());

    // Verify that the domain storage contains the correct number of domains.
    int count =  domains_->size();
    EXPECT_EQ(1, count);

    // Verify that the expected domain exists and can be retrieved from
    // the storage.
    DdnsDomainMap::iterator gotit = domains_->find("tmark.org");
    ASSERT_TRUE(gotit != domains_->end());
    DdnsDomainPtr& domain = gotit->second;

    // Verify the name and key_name values.
    EXPECT_EQ("tmark.org", domain->getName());
    EXPECT_EQ("d2_key.tmark.org", domain->getKeyName());

    // Verify that the server list exists and contains the correct number of
    // servers.
    const DnsServerInfoStoragePtr& servers = domain->getServers();
    EXPECT_TRUE(servers);
    count =  servers->size();
    EXPECT_EQ(3, count);

    // Fetch each server and verify its contents.
    DnsServerInfoPtr server = (*servers)[0];
    EXPECT_TRUE(server);

    EXPECT_TRUE(checkServer(server, "", "127.0.0.1", 100));

    server = (*servers)[1];
    EXPECT_TRUE(server);

    EXPECT_TRUE(checkServer(server, "", "127.0.0.2", 200));

    server = (*servers)[2];
    EXPECT_TRUE(server);

    EXPECT_TRUE(checkServer(server, "", "127.0.0.3", 300));
}

/// @brief Tests the fundamentals of parsing DdnsDomain lists.
/// This test verifies that given a valid domain list configuration
/// it will accurately parse and populate each domain in the list.
TEST_F(DdnsDomainTest, DdnsDomainListParsing) {
    // Create a valid domain list configuration, with two domains
    // that have three servers each.
    std::string config =
                        "[ "
                        "{ \"name\": \"tmark.org\" , "
                        "  \"key_name\": \"d2_key.tmark.org\" , "
                        "  \"dns_servers\" : [ "
                        "  { \"ip_address\": \"127.0.0.1\" , "
                        "    \"port\": 100 },"
                        "  { \"ip_address\": \"127.0.0.2\" , "
                        "    \"port\": 200 },"
                        "  { \"ip_address\": \"127.0.0.3\" , "
                        "    \"port\": 300 } ] } "
                        ", "
                        "{ \"name\": \"billcat.net\" , "
                        "  \"key_name\": \"d2_key.billcat.net\" , "
                        "  \"dns_servers\" : [ "
                        "  { \"ip_address\": \"127.0.0.4\" , "
                        "    \"port\": 400 },"
                        "  { \"ip_address\": \"127.0.0.5\" , "
                        "    \"port\": 500 },"
                        "  { \"ip_address\": \"127.0.0.6\" , "
                        "    \"port\": 600 } ] } "
                        "] ";

    ASSERT_TRUE(fromJSON(config));

    // Add keys to key map so key validation passes.
    addKey("d2_key.tmark.org", "algo1", "secret1");
    addKey("d2_key.billcat.net", "algo2", "secret2");

    // Create the list parser
    isc::dhcp::ParserPtr list_parser;
    ASSERT_NO_THROW(list_parser.reset(
                    new DdnsDomainListParser("test", domains_, keys_)));

    // Verify that the domain configuration builds and commits without error.
    ASSERT_NO_THROW(list_parser->build(config_set_));
    ASSERT_NO_THROW(list_parser->commit());

    // Verify that the domain storage contains the correct number of domains.
    int count =  domains_->size();
    EXPECT_EQ(2, count);

    // Verify that the first domain exists and can be retrieved.
    DdnsDomainMap::iterator gotit = domains_->find("tmark.org");
    ASSERT_TRUE(gotit != domains_->end());
    DdnsDomainPtr& domain = gotit->second;

    // Verify the name and key_name values of the first domain.
    EXPECT_EQ("tmark.org", domain->getName());
    EXPECT_EQ("d2_key.tmark.org", domain->getKeyName());

    // Verify the each of the first domain's servers
    DnsServerInfoStoragePtr servers = domain->getServers();
    EXPECT_TRUE(servers);
    count =  servers->size();
    EXPECT_EQ(3, count);

    DnsServerInfoPtr server = (*servers)[0];
    EXPECT_TRUE(server);
    EXPECT_TRUE(checkServer(server, "", "127.0.0.1", 100));

    server = (*servers)[1];
    EXPECT_TRUE(server);
    EXPECT_TRUE(checkServer(server, "", "127.0.0.2", 200));

    server = (*servers)[2];
    EXPECT_TRUE(server);
    EXPECT_TRUE(checkServer(server, "", "127.0.0.3", 300));

    // Verify second domain
    gotit = domains_->find("billcat.net");
    ASSERT_TRUE(gotit != domains_->end());
    domain = gotit->second;

    // Verify the name and key_name values of the second domain.
    EXPECT_EQ("billcat.net", domain->getName());
    EXPECT_EQ("d2_key.billcat.net", domain->getKeyName());

    // Verify the each of second domain's servers
    servers = domain->getServers();
    EXPECT_TRUE(servers);
    count =  servers->size();
    EXPECT_EQ(3, count);

    server = (*servers)[0];
    EXPECT_TRUE(server);
    EXPECT_TRUE(checkServer(server, "", "127.0.0.4", 400));

    server = (*servers)[1];
    EXPECT_TRUE(server);
    EXPECT_TRUE(checkServer(server, "", "127.0.0.5", 500));

    server = (*servers)[2];
    EXPECT_TRUE(server);
    EXPECT_TRUE(checkServer(server, "", "127.0.0.6", 600));
}

/// @brief Tests that a domain list configuration cannot contain duplicates.
TEST_F(DdnsDomainTest, duplicateDomain) {
    // Create a domain list configuration that contains two domains with
    // the same name.
    std::string config =
                        "[ "
                        "{ \"name\": \"tmark.org\" , "
                        "  \"dns_servers\" : [ "
                        "  { \"ip_address\": \"127.0.0.3\" , "
                        "    \"port\": 300 } ] } "
                        ", "
                        "{ \"name\": \"tmark.org\" , "
                        "  \"dns_servers\" : [ "
                        "  { \"ip_address\": \"127.0.0.3\" , "
                        "    \"port\": 300 } ] } "
                        "] ";
    ASSERT_TRUE(fromJSON(config));

    // Create the list parser
    isc::dhcp::ParserPtr list_parser;
    ASSERT_NO_THROW(list_parser.reset(
                    new DdnsDomainListParser("test", domains_, keys_)));

    // Verify that the parse build succeeds but the commit fails.
    ASSERT_NO_THROW(list_parser->build(config_set_));
    ASSERT_THROW(list_parser->commit(), D2CfgError);
}

/// @brief Tests construction of D2CfgMgr
/// This test verifies that a D2CfgMgr constructs properly.
TEST(D2CfgMgr, construction) {
    D2CfgMgr *cfg_mgr = NULL;

    // Verify that configuration manager constructions without error.
    ASSERT_NO_THROW(cfg_mgr = new D2CfgMgr());

    // Verify that the context can be retrieved and is not null.
    D2CfgContextPtr context;
    ASSERT_NO_THROW(context = cfg_mgr->getD2CfgContext());
    EXPECT_TRUE(context);

    // Verify that the forward manager can be retrieved and is not null.
    EXPECT_TRUE(context->getForwardMgr());

    // Verify that the reverse manager can be retrieved and is not null.
    EXPECT_TRUE(context->getReverseMgr());

    // Verify that the manager can be destructed without error.
    EXPECT_NO_THROW(delete cfg_mgr);
}

/// @brief Tests the parsing of a complete, valid DHCP-DDNS configuration.
/// This tests passes the configuration into an instance of D2CfgMgr just
/// as it would be done by d2_process in response to a configuration update
/// event.
TEST_F(D2CfgMgrTest, fullConfig) {
    // Create a configuration with all of application level parameters, plus
    // both the forward and reverse ddns managers.  Both managers have two
    // domains with three servers per domain.
    std::string config = "{ "
                        "\"interface\" : \"eth1\" , "
                        "\"ip_address\" : \"192.168.1.33\" , "
                        "\"port\" : 88 , "
                        "\"tsig_keys\": ["
                        "{"
                        "  \"name\": \"d2_key.tmark.org\" , "
                        "  \"algorithm\": \"md5\" , "
                        "  \"secret\": \"ssh-dont-tell\"  "
                        "},"
                        "{"
                        "  \"name\": \"d2_key.billcat.net\" , "
                        "  \"algorithm\": \"md5\" , "
                        "  \"secret\": \"ollie-ollie-in-free\"  "
                        "}"
                        "],"
                        "\"forward_ddns\" : {"
                        "\"ddns_domains\": [ "
                        "{ \"name\": \"tmark.org\" , "
                        "  \"key_name\": \"d2_key.tmark.org\" , "
                        "  \"dns_servers\" : [ "
                        "  { \"hostname\": \"one.tmark\" } , "
                        "  { \"hostname\": \"two.tmark\" } , "
                        "  { \"hostname\": \"three.tmark\"} "
                        "  ] } "
                        ", "
                        "{ \"name\": \"billcat.net\" , "
                        "  \"key_name\": \"d2_key.billcat.net\" , "
                        "  \"dns_servers\" : [ "
                        "  { \"hostname\": \"four.billcat\" } , "
                        "  { \"hostname\": \"five.billcat\" } , "
                        "  { \"hostname\": \"six.billcat\" } "
                        "  ] } "
                        "] },"
                        "\"reverse_ddns\" : {"
                        "\"ddns_domains\": [ "
                        "{ \"name\": \" 0.168.192.in.addr.arpa.\" , "
                        "  \"key_name\": \"d2_key.tmark.org\" , "
                        "  \"dns_servers\" : [ "
                        "  { \"hostname\": \"one.rev\" } , "
                        "  { \"hostname\": \"two.rev\" } , "
                        "  { \"hostname\": \"three.rev\" } "
                        "  ] } "
                        ", "
                        "{ \"name\": \" 0.247.106.in.addr.arpa.\" , "
                        "  \"key_name\": \"d2_key.billcat.net\" , "
                        "  \"dns_servers\" : [ "
                        "  { \"hostname\": \"four.rev\" }, "
                        "  { \"hostname\": \"five.rev\" } , "
                        "  { \"hostname\": \"six.rev\" } "
                        "  ] } "
                        "] } }";
    ASSERT_TRUE(fromJSON(config));

    // Verify that we can parse the configuration.
    answer_ = cfg_mgr_->parseConfig(config_set_);
    ASSERT_TRUE(checkAnswer(0));

    // Verify that the D2 context can be retrieved and is not null.
    D2CfgContextPtr context;
    ASSERT_NO_THROW(context = cfg_mgr_->getD2CfgContext());

    // Verify that the application level scalars have the proper values.
    std::string interface;
    EXPECT_NO_THROW (context->getParam("interface", interface));
    EXPECT_EQ("eth1", interface);

    std::string ip_address;
    EXPECT_NO_THROW (context->getParam("ip_address", ip_address));
    EXPECT_EQ("192.168.1.33", ip_address);

    uint32_t port = 0;
    EXPECT_NO_THROW (context->getParam("port", port));
    EXPECT_EQ(88, port);

    // Verify that the forward manager can be retrieved.
    DdnsDomainListMgrPtr mgr = context->getForwardMgr();
    ASSERT_TRUE(mgr);

    // Verify that the forward manager has the correct number of domains.
    DdnsDomainMapPtr domains = mgr->getDomains();
    ASSERT_TRUE(domains);
    int count =  domains->size();
    EXPECT_EQ(2, count);

    // Verify that the server count in each of the forward manager domains.
    // NOTE that since prior tests have validated server parsing, we are are
    // assuming that the servers did in fact parse correctly if the correct
    // number of them are there.
    DdnsDomainMapPair domain_pair;
    BOOST_FOREACH(domain_pair, (*domains)) {
        DdnsDomainPtr domain = domain_pair.second;
        DnsServerInfoStoragePtr servers = domain->getServers();
        count = servers->size();
        EXPECT_TRUE(servers);
        EXPECT_EQ(3, count);
    }

    // Verify that the reverse manager can be retrieved.
    mgr = context->getReverseMgr();
    ASSERT_TRUE(mgr);

    // Verify that the reverse manager has the correct number of domains.
    domains = mgr->getDomains();
    count =  domains->size();
    EXPECT_EQ(2, count);

    // Verify that the server count in each of the reverse manager domains.
    // NOTE that since prior tests have validated server parsing, we are are
    // assuming that the servers did in fact parse correctly if the correct
    // number of them are there.
    BOOST_FOREACH(domain_pair, (*domains)) {
        DdnsDomainPtr domain = domain_pair.second;
        DnsServerInfoStoragePtr servers = domain->getServers();
        count = servers->size();
        EXPECT_TRUE(servers);
        EXPECT_EQ(3, count);
    }

    // Test directional update flags.
    EXPECT_TRUE(cfg_mgr_->forwardUpdatesEnabled());
    EXPECT_TRUE(cfg_mgr_->reverseUpdatesEnabled());

    // Verify that parsing the exact same configuration a second time
    // does not cause a duplicate value errors. 
    answer_ = cfg_mgr_->parseConfig(config_set_);
    ASSERT_TRUE(checkAnswer(0));
}

/// @brief Tests the basics of the D2CfgMgr FQDN-domain matching
/// This test uses a valid configuration to exercise the D2CfgMgr
/// forward FQDN-to-domain matching.
/// It verifies that:
/// 1. Given an FQDN which exactly matches a domain's name, that domain is
/// returned as match.
/// 2. Given a FQDN for sub-domain in the list, returns the proper match.
/// 3. Given a FQDN that matches no domain name, returns the wild card domain
/// as a match.
TEST_F(D2CfgMgrTest, forwardMatch) {
    // Create  configuration with one domain, one sub domain, and the wild
    // card.
    std::string config = "{ "
                        "\"interface\" : \"eth1\" , "
                        "\"ip_address\" : \"192.168.1.33\" , "
                        "\"port\" : 88 , "
                        "\"tsig_keys\": [] ,"
                        "\"forward_ddns\" : {"
                        "\"ddns_domains\": [ "
                        "{ \"name\": \"tmark.org\" , "
                        "  \"dns_servers\" : [ "
                        "  { \"ip_address\": \"127.0.0.1\" } "
                        "  ] } "
                        ", "
                        "{ \"name\": \"one.tmark.org\" , "
                        "  \"dns_servers\" : [ "
                        "  { \"ip_address\": \"127.0.0.2\" } "
                        "  ] } "
                        ", "
                        "{ \"name\": \"*\" , "
                        "  \"dns_servers\" : [ "
                        "  { \"hostname\": \"global.net\" } "
                        "  ] } "
                        "] }, "
                        "\"reverse_ddns\" : {} "
                        "}";


    ASSERT_TRUE(fromJSON(config));
    // Verify that we can parse the configuration.
    answer_ = cfg_mgr_->parseConfig(config_set_);
    ASSERT_TRUE(checkAnswer(0));

    // Verify that the D2 context can be retrieved and is not null.
    D2CfgContextPtr context;
    ASSERT_NO_THROW(context = cfg_mgr_->getD2CfgContext());

    // Test directional update flags.
    EXPECT_TRUE(cfg_mgr_->forwardUpdatesEnabled());
    EXPECT_FALSE(cfg_mgr_->reverseUpdatesEnabled());

    DdnsDomainPtr match;
    // Verify that an exact match works.
    EXPECT_TRUE(cfg_mgr_->matchForward("tmark.org", match));
    EXPECT_EQ("tmark.org", match->getName());

    // Verify that search is case insensisitive.
    EXPECT_TRUE(cfg_mgr_->matchForward("TMARK.ORG", match));
    EXPECT_EQ("tmark.org", match->getName());

    // Verify that an exact match works.
    EXPECT_TRUE(cfg_mgr_->matchForward("one.tmark.org", match));
    EXPECT_EQ("one.tmark.org", match->getName());

    // Verify that a FQDN for sub-domain matches.
    EXPECT_TRUE(cfg_mgr_->matchForward("blue.tmark.org", match));
    EXPECT_EQ("tmark.org", match->getName());

    // Verify that a FQDN for sub-domain matches.
    EXPECT_TRUE(cfg_mgr_->matchForward("red.one.tmark.org", match));
    EXPECT_EQ("one.tmark.org", match->getName());

    // Verify that an FQDN with no match, returns the wild card domain.
    EXPECT_TRUE(cfg_mgr_->matchForward("shouldbe.wildcard", match));
    EXPECT_EQ("*", match->getName());

    // Verify that an attempt to match an empty FQDN throws.
    ASSERT_THROW(cfg_mgr_->matchForward("", match), D2CfgError);
}

/// @brief Tests domain matching when there is no wild card domain.
/// This test verifies that matches are found only for FQDNs that match
/// some or all of a domain name.  FQDNs without matches should not return
/// a match.
TEST_F(D2CfgMgrTest, matchNoWildcard) {
    // Create a configuration with one domain, one sub-domain, and NO wild card.
    std::string config = "{ "
                        "\"interface\" : \"eth1\" , "
                        "\"ip_address\" : \"192.168.1.33\" , "
                        "\"port\" : 88 , "
                        "\"tsig_keys\": [] ,"
                        "\"forward_ddns\" : {"
                        "\"ddns_domains\": [ "
                        "{ \"name\": \"tmark.org\" , "
                        "  \"dns_servers\" : [ "
                        "  { \"ip_address\": \"127.0.0.1\" } "
                        "  ] } "
                        ", "
                        "{ \"name\": \"one.tmark.org\" , "
                        "  \"dns_servers\" : [ "
                        "  { \"ip_address\": \"127.0.0.2\" } "
                        "  ] } "
                        "] }, "
                        "\"reverse_ddns\" : {} "
                        " }";

    ASSERT_TRUE(fromJSON(config));

    // Verify that we can parse the configuration.
    answer_ = cfg_mgr_->parseConfig(config_set_);
    ASSERT_TRUE(checkAnswer(0));

    // Verify that the D2 context can be retrieved and is not null.
    D2CfgContextPtr context;
    ASSERT_NO_THROW(context = cfg_mgr_->getD2CfgContext());

    DdnsDomainPtr match;
    // Verify that full or partial matches, still match.
    EXPECT_TRUE(cfg_mgr_->matchForward("tmark.org", match));
    EXPECT_EQ("tmark.org", match->getName());

    EXPECT_TRUE(cfg_mgr_->matchForward("blue.tmark.org", match));
    EXPECT_EQ("tmark.org", match->getName());

    EXPECT_TRUE(cfg_mgr_->matchForward("red.one.tmark.org", match));
    EXPECT_EQ("one.tmark.org", match->getName());

    // Verify that a FQDN with no match, fails to match.
    EXPECT_FALSE(cfg_mgr_->matchForward("shouldbe.wildcard", match));
}

/// @brief Tests domain matching when there is ONLY a wild card domain.
/// This test verifies that any FQDN matches the wild card.
TEST_F(D2CfgMgrTest, matchAll) {
    std::string config = "{ "
                        "\"interface\" : \"eth1\" , "
                        "\"ip_address\" : \"192.168.1.33\" , "
                        "\"port\" : 88 , "
                        "\"tsig_keys\": [] ,"
                        "\"forward_ddns\" : {"
                        "\"ddns_domains\": [ "
                        "{ \"name\": \"*\" , "
                        "  \"dns_servers\" : [ "
                        "  { \"ip_address\": \"127.0.0.1\" } "
                        "  ] } "
                        "] }, "
                        "\"reverse_ddns\" : {} "
                        "}";

    ASSERT_TRUE(fromJSON(config));

    // Verify that we can parse the configuration.
    answer_ = cfg_mgr_->parseConfig(config_set_);
    ASSERT_TRUE(checkAnswer(0));

    // Verify that the D2 context can be retrieved and is not null.
    D2CfgContextPtr context;
    ASSERT_NO_THROW(context = cfg_mgr_->getD2CfgContext());

    // Verify that wild card domain is returned for any FQDN.
    DdnsDomainPtr match;
    EXPECT_TRUE(cfg_mgr_->matchForward("tmark.org", match));
    EXPECT_EQ("*", match->getName());
    EXPECT_TRUE(cfg_mgr_->matchForward("shouldbe.wildcard", match));
    EXPECT_EQ("*", match->getName());

    // Verify that an attempt to match an empty FQDN still throws.
    ASSERT_THROW(cfg_mgr_->matchReverse("", match), D2CfgError);

}

/// @brief Tests the basics of the D2CfgMgr reverse FQDN-domain matching
/// This test uses a valid configuration to exercise the D2CfgMgr's
/// reverse FQDN-to-domain matching.
/// It verifies that:
/// 1. Given an FQDN which exactly matches a domain's name, that domain is
/// returned as match.
/// 2. Given a FQDN for sub-domain in the list, returns the proper match.
/// 3. Given a FQDN that matches no domain name, returns the wild card domain
/// as a match.
TEST_F(D2CfgMgrTest, matchReverse) {
    std::string config = "{ "
                        "\"interface\" : \"eth1\" , "
                        "\"ip_address\" : \"192.168.1.33\" , "
                        "\"port\" : 88 , "
                        "\"tsig_keys\": [] ,"
                        "\"forward_ddns\" : {}, "
                        "\"reverse_ddns\" : {"
                        "\"ddns_domains\": [ "
                        "{ \"name\": \"5.100.168.192.in-addr.arpa.\" , "
                        "  \"dns_servers\" : [ "
                        "  { \"ip_address\": \"127.0.0.1\" } "
                        "  ] }, "
                        "{ \"name\": \"100.200.192.in-addr.arpa.\" , "
                        "  \"dns_servers\" : [ "
                        "  { \"ip_address\": \"127.0.0.1\" } "
                        "  ] }, "
                        "{ \"name\": \"170.192.in-addr.arpa.\" , "
                        "  \"dns_servers\" : [ "
                        "  { \"ip_address\": \"127.0.0.1\" } "
                        "  ] }, "
                        // Note mixed case to test case insensitivity.
                        "{ \"name\": \"2.0.3.0.8.b.d.0.1.0.0.2.IP6.ARPA.\" , "
                        "  \"dns_servers\" : [ "
                        "  { \"ip_address\": \"127.0.0.1\" } "
                        "  ] },"
                        "{ \"name\": \"*\" , "
                        "  \"dns_servers\" : [ "
                        "  { \"ip_address\": \"127.0.0.1\" } "
                        "  ] } "
                        "] } }";

    ASSERT_TRUE(fromJSON(config));

    // Verify that we can parse the configuration.
    answer_ = cfg_mgr_->parseConfig(config_set_);
    ASSERT_TRUE(checkAnswer(0));

    // Verify that the D2 context can be retrieved and is not null.
    D2CfgContextPtr context;
    ASSERT_NO_THROW(context = cfg_mgr_->getD2CfgContext());

    // Test directional update flags.
    EXPECT_FALSE(cfg_mgr_->forwardUpdatesEnabled());
    EXPECT_TRUE(cfg_mgr_->reverseUpdatesEnabled());

    DdnsDomainPtr match;

    // Verify an exact match.
    EXPECT_TRUE(cfg_mgr_->matchReverse("192.168.100.5", match));
    EXPECT_EQ("5.100.168.192.in-addr.arpa.", match->getName());

    // Verify a sub-domain match.
    EXPECT_TRUE(cfg_mgr_->matchReverse("192.200.100.27", match));
    EXPECT_EQ("100.200.192.in-addr.arpa.", match->getName());

    // Verify a sub-domain match.
    EXPECT_TRUE(cfg_mgr_->matchReverse("192.170.50.30", match));
    EXPECT_EQ("170.192.in-addr.arpa.", match->getName());

    // Verify a wild card match.
    EXPECT_TRUE(cfg_mgr_->matchReverse("1.1.1.1", match));
    EXPECT_EQ("*", match->getName());

    // Verify a IPv6 match.
    EXPECT_TRUE(cfg_mgr_->matchReverse("2001:db8:302:99::",match));
    EXPECT_EQ("2.0.3.0.8.b.d.0.1.0.0.2.IP6.ARPA.", match->getName());

    // Verify a IPv6 wild card match.
    EXPECT_TRUE(cfg_mgr_->matchReverse("2001:db8:99:302::",match));
    EXPECT_EQ("*", match->getName());

    // Verify that an attempt to match an invalid IP address throws.
    ASSERT_THROW(cfg_mgr_->matchReverse("", match), D2CfgError);
}

} // end of anonymous namespace
