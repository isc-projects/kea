// Copyright (C) 2017-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.com/MPL/2.0/.

#include <config.h>
#include <gtest/gtest.h>
#include <cc/data.h>
#include <d2/tests/parser_unittest.h>
#include <d2srv/d2_simple_parser.h>
#include <testutils/test_to_element.h>

#include <boost/lexical_cast.hpp>

using namespace isc;
using namespace isc::data;
using namespace isc::d2;
using namespace isc::test;

namespace {

/// @brief Checks if specified element matches the given integer default
///
/// @param element defaulted element to check
/// @param deflt SimpleDefault which supplied the default value
void checkIntegerValue(const ConstElementPtr& element,
                       const SimpleDefault& deflt)  {
    ASSERT_TRUE(element);

    // Verify it is an integer.
    ASSERT_EQ(Element::integer, element->getType());

    // Turn default value string into an int.
    int64_t default_value = 0;
    ASSERT_NO_THROW(default_value = boost::lexical_cast<int64_t>(deflt.value_));

    // Verify it has the expected value.
    EXPECT_EQ(default_value, element->intValue());
}

/// @brief Checks if specified element matches the given boolean default
///
/// @param element defaulted element to check
/// @param deflt SimpleDefault which supplied the default value
void checkBooleanValue(const ConstElementPtr& element,
                       const SimpleDefault& deflt)  {
    ASSERT_TRUE(element);

    // Verify it is a bool.
    ASSERT_EQ(Element::boolean, element->getType());

    // Turn default value string into a bool.
    bool default_value = false;
    ASSERT_NO_THROW(boost::lexical_cast<bool>(deflt.value_));

    // Verify it has the expected value.
    EXPECT_EQ(default_value, element->boolValue());
}

/// @brief Checks if specified element matches the given string default
///
/// @param element defaulted element to check
/// @param deflt SimpleDefault which supplied the default value
void checkStringValue(const ConstElementPtr& element,
                      const SimpleDefault& deflt)  {
    ASSERT_TRUE(element);

    // Verify it's a string
    ASSERT_EQ(Element::string, element->getType());

    // Verify it has the expected value
        EXPECT_EQ(deflt.value_, element->stringValue());
    }

/// TSIGKeyInfo against the given set of values, and that the TSIGKey
/// member points to a key.
///
/// @param key is a pointer to the TSIGKeyInfo instance to verify
/// @param name is the value to compare against key's name_.
/// @param algorithm is the string value to compare against key's algorithm.
/// @param secret is the value to compare against key's secret.
///
/// @return returns true if there is a match across the board, otherwise it
/// returns false.
bool checkKey(TSIGKeyInfoPtr key, const std::string& name,
              const std::string& algorithm, const std::string& secret,
              uint32_t digestbits = 0) {
    // Return value, assume its a match.
    return (((key) &&
        (key->getName() == name) &&
        (key->getAlgorithm() == algorithm)  &&
        (key->getDigestbits() == digestbits) &&
        (key->getSecret() ==  secret)  &&
        (key->getTSIGKey())));
}

/// @brief Convenience function which compares the contents of the given
/// DnsServerInfo against the given set of values.
///
/// It is structured in such a way that each value is checked, and output
/// is generated for all that do not match.
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

/// @brief Base class test fixture for testing JSON and element parsing
/// for D2 configuration elements.  It combines the three phases of
/// configuration parsing normally orchestrated by D2CfgMgr:
/// 1. Submit the JSON text to the JSON parser
/// 2. Add defaults to the element tree produced by the JSON parser
/// 3. Pass the element tree into the appropriate SimpleParser derivation
/// to parse the element tree into D2 objects.
class D2SimpleParserTest : public ::testing::Test {
public:
    /// @brief Constructor
    ///
    /// @param parser_type specifies the parsing starting point at which
    /// the JSON parser should begin. It defaults to PARSER_JSON. See @c
    /// D2ParserContext::ParserType for all possible values.
    D2SimpleParserTest(const D2ParserContext::ParserType&
                       parser_type = D2ParserContext::PARSER_JSON)
        : parser_type_(parser_type) {
        reset();
    }

    /// @brief Destructor
    virtual ~D2SimpleParserTest() {
        reset();
    }

    /// @brief Parses JSON text and compares the results against an expected
    /// outcome.
    ///
    /// The JSON text is submitted to the D2ParserContext for parsing. Any
    /// errors emitted here are caught and compared against the expected
    /// error or flagged as unexpected.
    /// Next, the virtual method, setDefaults()is invoked. his method should
    /// be used by derivations to add default values to the element tree
    /// produced by the JSON parser.
    /// Lastly, it passes the element tree into the virtual method,
    /// parseElement().  This method should be used by derivations to create
    /// the appropriate element parser to parse the element tree into the
    /// appropriate D2 object(s).
    ///
    /// @param json JSON text to parse
    /// @param exp_error exact text of the error message expected or ""
    /// if parsing should succeed.
    ::testing::AssertionResult parseOrFail(const std::string& json,
                                           const std::string& exp_error) {
        try {
            // Free up objects created by previous invocation
            reset();

            // Submit JSON text to JSON parser.  We convert the result to
            // a mutable element tree to allow defaults to be added.
            D2ParserContext context;
            data::ElementPtr elem = boost::const_pointer_cast<Element>
                                    (context.parseString(json, parser_type_));
            // Add any defaults
            setDefaults(elem);

            // Now parse the element tree into object(s).
            parseElement(elem);
        } catch (const std::exception& ex) {
            std::string caught_error = ex.what();
            if (exp_error.empty()) {
                return ::testing::AssertionFailure()
                        << "Unexpected error: " << caught_error
                        << "\n json: [" << json << "]";
            }

            if (exp_error != caught_error) {
                return ::testing::AssertionFailure()
                                << "Wrong error detected, expected: "
                                << exp_error << ", got: " << caught_error
                                << "\n json: [" << json << "]";
            }
            return ::testing::AssertionSuccess();
        }

        if (!exp_error.empty()) {
            return ::testing::AssertionFailure()
                       << "Unexpected parsing success "
                       << exp_error << "\n json: [" << json << "]";
        }

        return ::testing::AssertionSuccess();
    }


protected:
    /// @brief Free up objects created by element parsing
    /// This method is invoked at the beginning of @c parseOrFail() to
    /// ensure any D2 object(s) that were created by a prior invocation are
    /// destroyed. This permits parsing to be conducted more than once
    /// in the same test.
    virtual void reset(){};

    /// @brief Adds default values to the given element tree
    ///
    /// Derivations are expected to use the appropriate methods in
    /// D2SimpleParser to add defaults values.
    ///
    /// @param config element tree in which defaults should be added
    /// @return the number of default items added to the tree
    virtual size_t setDefaults(data::ElementPtr config) {
        static_cast<void>(config);
        return (0);
    }

    /// @brief Parses a given element tree into D2 object(s)
    ///
    /// Derivations are expected to create the appropriate element
    /// parser and pass it the element tree for parsing.  Any object(s)
    /// created should likely be saved for content verification
    /// outside of this method.
    ///
    /// @param config element tree to parse
    virtual void parseElement(data::ConstElementPtr config) {
        static_cast<void>(config);
    }

    D2ParserContext::ParserType parser_type_;
};

/// @brief Convenience macros for calling parseOrFail
#define PARSE_OK(a) EXPECT_TRUE((parseOrFail(a, "")))
#define PARSE_FAIL(a,b) EXPECT_TRUE((parseOrFail(a, b)))

// This test checks if global defaults are properly set for D2.
TEST_F(D2SimpleParserTest, globalD2Defaults) {

    ElementPtr empty = isc::d2::test::parseJSON("{ }");
    size_t num = 0;

    EXPECT_NO_THROW(num = D2SimpleParser::setAllDefaults(empty));

    // We expect 5 parameters to be inserted.
    EXPECT_EQ(num, 8);

    // Let's go over all parameters we have defaults for.
    BOOST_FOREACH(SimpleDefault deflt, D2SimpleParser::D2_GLOBAL_DEFAULTS) {
        ConstElementPtr x;
        ASSERT_NO_THROW(x = empty->get(deflt.name_));

        EXPECT_TRUE(x);
        if (x) {
            if (deflt.type_ == Element::integer) {
                checkIntegerValue(x, deflt);
            } else if (deflt.type_ == Element::boolean) {
                checkBooleanValue(x, deflt);
            } else if (deflt.type_ == Element::string) {
                checkStringValue(x, deflt);
            } else {
                // add them if we need to. Like what do you if it's a map?
                ADD_FAILURE() << "default type not supported:" << deflt.name_
                            << " ,type: " << deflt.type_;
            }
        }
    }
}

/// @brief Test fixture class for testing TSIGKeyInfo parsing.
class TSIGKeyInfoParserTest : public D2SimpleParserTest {
public:
    /// @brief Constructor
    TSIGKeyInfoParserTest()
        : D2SimpleParserTest(D2ParserContext::PARSER_TSIG_KEY) {
    }

    /// @brief Free up the keys created by parsing
    virtual void reset() {
        key_.reset();
    };

    /// @brief Destructor
    virtual ~TSIGKeyInfoParserTest() {
        reset();
    };

    /// @brief Adds TSIG Key default values to the given TSIG Key element
    ///
    /// @param config TSIG Key element to which defaults should be added
    ///
    /// @return the number of default items added to the tree
    size_t setDefaults(data::ElementPtr config) {
        return (SimpleParser::setDefaults(config, D2SimpleParser::
                TSIG_KEY_DEFAULTS));
    }

    /// @brief Attempts to parse the given element into a TSIGKeyInfo
    ///
    /// Assumes the given element is a Map containing the attributes for
    /// a TSIG Key. If parsing is successful the new TSIGKeyInfo instance
    /// is retained in the member, key_;
    ///
    /// @param config element to parse
    void parseElement(data::ConstElementPtr config) {
        TSIGKeyInfoParser parser;
        key_ = parser.parse(config);
    }

    /// @brief Retains the TSIGKeyInfo created by a successful parsing
    TSIGKeyInfoPtr key_;
};


/// @brief Test fixture class for testing TSIGKeyInfo list parsing.
class TSIGKeyInfoListParserTest : public D2SimpleParserTest {
public:
    /// @brief Constructor
    TSIGKeyInfoListParserTest()
        : D2SimpleParserTest(D2ParserContext::PARSER_TSIG_KEYS) {
    }

    /// @brief Destructor
    virtual ~TSIGKeyInfoListParserTest() {
        reset();
    }

    /// @brief Free up the keys created by parsing
    virtual void reset() {
        keys_.reset();
    };

    /// @brief Adds TSIG Key default values to a list of TSIG Key elements
    ///
    /// @param config list of TSIG Key elements to which defaults should be
    /// added
    ///
    /// @return the number of default items added to the tree
    size_t setDefaults(data::ElementPtr config) {
        return (SimpleParser::setListDefaults(config, D2SimpleParser::
                                                      TSIG_KEY_DEFAULTS));
    }

    /// @brief Attempts to parse the given element into a list of TSIGKeyInfos
    ///
    /// Assumes the given element is a list containing one or more TSIG Keys
    /// elements.  If parsing is successful the list of TSIGKeyInfo instances
    /// is retained in the member, keys_;
    ///
    /// @param config element to parse
    void parseElement(data::ConstElementPtr config) {
        TSIGKeyInfoListParser parser;
        keys_ = parser.parse(config);
    }

    /// @brief Retains the TSIGKeyInfos created by a successful parsing
    TSIGKeyInfoMapPtr keys_;
};

/// @brief Test fixture class for testing DnsServerInfo parsing.
class DnsServerInfoParserTest : public D2SimpleParserTest {
public:
    /// @brief Constructor
    DnsServerInfoParserTest()
        : D2SimpleParserTest(D2ParserContext::PARSER_DNS_SERVER) {
    }

    /// @brief Destructor
    virtual ~DnsServerInfoParserTest() {
        reset();
    }

    /// @brief Free up the server created by parsing
    virtual void reset() {
        server_.reset();
    }

    /// @brief Adds DNS Server default values to the given DNS Server element
    ///
    /// @param config DNS Server element to which defaults should be added
    ///
    /// @return the number of default items added to the tree
    virtual size_t setDefaults(data::ElementPtr config) {
        return (SimpleParser::setDefaults(config, D2SimpleParser::
                                                  DNS_SERVER_DEFAULTS));
    }

    /// @brief Attempts to parse the given element into a DnsServerInfo
    ///
    /// Assumes the given element is a map containing the attributes for
    /// a DNS Server. If parsing is successful the new DnsServerInfo instance
    /// is retained in the member, server_;
    ///
    /// @param config element to parse
    virtual void parseElement(data::ConstElementPtr config) {
        DnsServerInfoParser parser;
        std::string domain = "{ \"key-name\": \"\" }";
        server_ = parser.parse(config, Element::fromJSON(domain), {});
    }

    /// @brief Retains the DnsServerInfo created by a successful parsing
    DnsServerInfoPtr server_;
};

/// @brief Test fixture class for testing DnsServerInfoList parsing.
class DnsServerInfoListParserTest : public D2SimpleParserTest {
public:
    /// @brief Constructor
    DnsServerInfoListParserTest()
        : D2SimpleParserTest(D2ParserContext::PARSER_DNS_SERVERS) {
    }

    /// @brief Destructor
    virtual ~DnsServerInfoListParserTest() {
        reset();
    }

    /// @brief Free up the servers created by parsing
    virtual void reset() {
        servers_.reset();
    }

    /// @brief Adds DNS Server default values to a list of DNS Server elements
    ///
    /// @param config list of DNS Server elements to which defaults should be
    /// added
    ///
    /// @return the number of default items added to the tree
    virtual size_t setDefaults(data::ElementPtr config) {
        return (SimpleParser::setListDefaults(config, D2SimpleParser::
                                                      DNS_SERVER_DEFAULTS));
    }

    /// @brief Attempts to parse the given element into a list of DnsServerInfos
    ///
    /// Assumes the given element is a list containing one or more DNS Servers
    /// elements.  If parsing is successful the list of DnsServerInfo instances
    /// is retained in the member, keys_;
    ///
    /// @param config element to parse
    virtual void parseElement(data::ConstElementPtr config) {
        DnsServerInfoListParser parser;
        std::string domain = "{ \"key-name\": \"\" }";
        servers_ = parser.parse(config, Element::fromJSON(domain), {});
    }

    /// @brief Retains the DnsServerInfos created by a successful parsing
    DnsServerInfoStoragePtr servers_;
};


/// @brief Test fixture class for testing DDnsDomain parsing.
class DdnsDomainParserTest : public D2SimpleParserTest {
public:

    /// @brief Constructor
    DdnsDomainParserTest(const D2ParserContext::ParserType& parser_type
                         = D2ParserContext::PARSER_DDNS_DOMAIN)
        : D2SimpleParserTest(parser_type), keys_(new TSIGKeyInfoMap())  {
    }

    /// @brief Destructor
    virtual ~DdnsDomainParserTest() {
        reset();
    }

    /// @brief Free up the domain created by parsing
    virtual void reset() {
        domain_.reset();
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

    /// @brief Adds DDNS Domain values to the given DDNS Domain element
    ///
    /// @param config DDNS Domain element to which defaults should be added
    ///
    /// @return the number of default items added to the tree
    virtual size_t setDefaults(data::ElementPtr config) {
        return (D2SimpleParser::setDdnsDomainDefaults(config, D2SimpleParser::
                                                      DDNS_DOMAIN_DEFAULTS));
    }

    /// @brief Attempts to parse the given element into a DdnsDomain
    ///
    /// Assumes the given element is a map containing the attributes for
    /// a DDNS Domain. If parsing is successful the new DdnsDomain instance
    /// is retained in the member, server_;
    ///
    /// @param config element to parse
    virtual void parseElement(data::ConstElementPtr config) {
        DdnsDomainParser parser;
        domain_ = parser.parse(config, keys_);
    }

    /// @brief Retains the DdnsDomain created by a successful parsing
    DdnsDomainPtr domain_;

    /// @brief Storage for TSIGKeys, used by DdnsDomainParser to validate
    /// domain keys
    TSIGKeyInfoMapPtr keys_;
};

class DdnsDomainListParserTest : public DdnsDomainParserTest {
public:
    /// @brief Constructor
    DdnsDomainListParserTest()
        // We need the list context type to parse lists correctly
        : DdnsDomainParserTest(D2ParserContext::PARSER_DDNS_DOMAINS) {
    }

    /// @brief Destructor
    virtual ~DdnsDomainListParserTest() {
        reset();
    }

    /// @brief Free up domains created by parsing
    virtual void reset() {
        domains_.reset();
    }

    /// @brief Adds DDNS Domain default values to a list of DDNS Domain elements
    ///
    /// @param config list of DDNS Domain elements to which defaults should be
    /// added
    ///
    /// @return the number of default items added to the tree
    virtual size_t setDefaults(data::ElementPtr config) {
        size_t cnt = 0;
        // We don't use SimpleParser::setListDefaults() as this does
        // not handle sub-lists or sub-maps
        BOOST_FOREACH(ElementPtr domain, config->listValue()) {
            cnt += D2SimpleParser::
                   setDdnsDomainDefaults(domain, D2SimpleParser::
                                                 DDNS_DOMAIN_DEFAULTS);
        }

        return (cnt);
    }

    /// @brief Attempts to parse the given element into a list of DdnsDomains
    ///
    /// Assumes the given element is a list containing one or more DDNS Domains
    /// elements.  If parsing is successful the list of DdnsDomain instances
    /// is retained in the member, keys_;
    ///
    /// @param config element to parse
    virtual void parseElement(data::ConstElementPtr config) {
        DdnsDomainListParser parser;
        domains_ = parser.parse(config, keys_);
    }

    /// @brief Retains the DdnsDomains created by a successful parsing
    DdnsDomainMapPtr domains_;
};

/// @brief Tests the enforcement of data validation when parsing TSIGKeyInfos.
/// It verifies that:
/// 1. Name cannot be blank.
/// 2. Algorithm cannot be blank.
/// 3. Secret cannot be blank.
TEST_F(TSIGKeyInfoParserTest, invalidEntry) {

    // Name cannot be blank.
    std::string config = "{"
                         " \"name\": \"\" , "
                         " \"algorithm\": \"HMAC-MD5\" , "
                         " \"secret\": \"LSWXnfkKZjdPJI5QxlpnfQ==\" "
                         "}";
    PARSE_FAIL(config, "<string>:1.9: TSIG key name cannot be blank");

    // Algorithm cannot be be blank.
    config = "{"
              " \"name\": \"d2_key_one\" , "
              " \"algorithm\": \"\" , "
              "   \"secret\": \"LSWXnfkKZjdPJI5QxlpnfQ==\" "
              "}";
    PARSE_FAIL(config, "<string>:1.38: TSIG key algorithm cannot be blank");

    // Algorithm must be a valid algorithm
    config = "{"
              " \"name\": \"d2_key_one\" , "
              " \"algorithm\": \"bogus\" , "
              "   \"secret\": \"LSWXnfkKZjdPJI5QxlpnfQ==\" "
              "}";
    PARSE_FAIL(config, "tsig-key : Unknown TSIG Key algorithm:"
                       " bogus (<string>:1:40)");

    // Secret cannot be blank
    config = "{"
              " \"name\": \"d2_key_one\" , "
              " \"algorithm\": \"HMAC-MD5\" , "
              " \"secret\": \"\" "
              "}";
    PARSE_FAIL(config, "<string>:1.62: TSIG key secret cannot be blank");

    // Secret must be valid for algorithm
    config = "{"
              " \"name\": \"d2_key_one\" , "
              " \"algorithm\": \"HMAC-MD5\" , "
              " \"digest-bits\": 120 , "
              " \"secret\": \"bogus\" "
              "}";
    PARSE_FAIL(config, "Cannot make D2TsigKey: Incomplete input for base64:"
                       " bogus (<string>:1:1)");
}


/// @brief Verifies that TSIGKeyInfo parsing creates a proper TSIGKeyInfo
/// when given a valid combination of entries.
TEST_F(TSIGKeyInfoParserTest, validEntry) {
    // Valid entries for TSIG key, all items are required.
    std::string config = "{"
                         " \"name\": \"d2_key_one\" , "
                         " \"algorithm\": \"HMAC-MD5\" , "
                         " \"digest-bits\": 120 , "
                         " \"secret\": \"dGhpcyBrZXkgd2lsbCBtYXRjaA==\" "
                         "}";
    // Verify that it parses.
    PARSE_OK(config);
    ASSERT_TRUE(key_);

    // Verify the key contents.
    EXPECT_TRUE(checkKey(key_, "d2_key_one", "HMAC-MD5",
                         "dGhpcyBrZXkgd2lsbCBtYXRjaA==", 120));

    // Verify unparsing.
    runToElementTest<TSIGKeyInfo>(config, *key_);
}

/// @brief Verifies that attempting to parse an invalid list of TSIGKeyInfo
/// entries is detected.
TEST_F(TSIGKeyInfoListParserTest, invalidTSIGKeyList) {
    // Construct a list of keys with an invalid key entry.
    std::string config = "["
                         " { \"name\": \"key1\" , "
                         "   \"algorithm\": \"HMAC-MD5\" ,"
                         "   \"digest-bits\": 120 , "
                         "   \"secret\": \"GWG/Xfbju4O2iXGqkSu4PQ==\" "
                         " },"
                         // this entry has an invalid algorithm
                         " { \"name\": \"key2\" , "
                         "   \"algorithm\": \"\" ,"
                         "   \"digest-bits\": 120 , "
                         "   \"secret\": \"GWG/Xfbju4O2iXGqkSu4PQ==\" "
                         " },"
                         " { \"name\": \"key3\" , "
                         "   \"algorithm\": \"HMAC-MD5\" ,"
                         "   \"secret\": \"GWG/Xfbju4O2iXGqkSu4PQ==\" "
                         " }"
                         " ]";

    PARSE_FAIL(config, "<string>:1.151: TSIG key algorithm cannot be blank");
}

/// @brief Verifies that attempting to parse an invalid list of TSIGKeyInfo
/// entries is detected.
TEST_F(TSIGKeyInfoListParserTest, duplicateTSIGKey) {
    // Construct a list of keys with an invalid key entry.
    std::string config = "["
                         " { \"name\": \"key1\" , "
                         "   \"algorithm\": \"HMAC-MD5\" ,"
                         " \"digest-bits\": 120 , "
                         "   \"secret\": \"GWG/Xfbju4O2iXGqkSu4PQ==\" "
                         " },"
                         " { \"name\": \"key2\" , "
                         "   \"algorithm\": \"HMAC-MD5\" ,"
                         " \"digest-bits\": 120 , "
                         "   \"secret\": \"GWG/Xfbju4O2iXGqkSu4PQ==\" "
                         " },"
                         " { \"name\": \"key1\" , "
                         "   \"algorithm\": \"HMAC-MD5\" ,"
                         "   \"secret\": \"GWG/Xfbju4O2iXGqkSu4PQ==\" "
                         " }"
                         " ]";

    PARSE_FAIL(config,
               "Duplicate TSIG key name specified : key1 (<string>:1:239)");
}

/// @brief Verifies a valid list of TSIG Keys parses correctly.
/// Also verifies that all of the supported algorithm names work.
TEST_F(TSIGKeyInfoListParserTest, validTSIGKeyList) {
    // Construct a valid list of keys.
    std::string config = "["
                         " { \"name\": \"key1\" , "
                         "   \"algorithm\": \"HMAC-MD5\" ,"
                         " \"digest-bits\": 80 , "
                         "  \"secret\": \"dGhpcyBrZXkgd2lsbCBtYXRjaA==\" "
                         " },"
                         " { \"name\": \"key2\" , "
                         "   \"algorithm\": \"HMAC-SHA1\" ,"
                         " \"digest-bits\": 80 , "
                         "  \"secret\": \"dGhpcyBrZXkgd2lsbCBtYXRjaA==\" "
                         " },"
                         " { \"name\": \"key3\" , "
                         "   \"algorithm\": \"HMAC-SHA256\" ,"
                         " \"digest-bits\": 128 , "
                         "  \"secret\": \"dGhpcyBrZXkgd2lsbCBtYXRjaA==\" "
                         " },"
                         " { \"name\": \"key4\" , "
                         "   \"algorithm\": \"HMAC-SHA224\" ,"
                         " \"digest-bits\": 112 , "
                         "  \"secret\": \"dGhpcyBrZXkgd2lsbCBtYXRjaA==\" "
                         " },"
                         " { \"name\": \"key5\" , "
                         "   \"algorithm\": \"HMAC-SHA384\" ,"
                         " \"digest-bits\": 192 , "
                         "  \"secret\": \"dGhpcyBrZXkgd2lsbCBtYXRjaA==\" "
                         " },"
                         " { \"name\": \"key6\" , "
                         "   \"algorithm\": \"HMAC-SHA512\" ,"
                         " \"digest-bits\": 256 , "
                         "   \"secret\": \"dGhpcyBrZXkgd2lsbCBtYXRjaA==\" "
                         " }"
                         " ]";

    PARSE_OK(config);
    ASSERT_TRUE(keys_);

    std::string ref_secret = "dGhpcyBrZXkgd2lsbCBtYXRjaA==";
    // Verify the correct number of keys are present
    int count =  keys_->size();
    ASSERT_EQ(6, count);

    // Find the 1st key and retrieve it.
    TSIGKeyInfoMap::iterator gotit = keys_->find("key1");
    ASSERT_TRUE(gotit != keys_->end());
    TSIGKeyInfoPtr& key = gotit->second;

    // Verify the key contents.
    EXPECT_TRUE(checkKey(key, "key1", TSIGKeyInfo::HMAC_MD5_STR,
                         ref_secret, 80));

    // Find the 2nd key and retrieve it.
    gotit = keys_->find("key2");
    ASSERT_TRUE(gotit != keys_->end());
    key = gotit->second;

    // Verify the key contents.
    EXPECT_TRUE(checkKey(key, "key2", TSIGKeyInfo::HMAC_SHA1_STR,
                         ref_secret, 80));

    // Find the 3rd key and retrieve it.
    gotit = keys_->find("key3");
    ASSERT_TRUE(gotit != keys_->end());
    key = gotit->second;

    // Verify the key contents.
    EXPECT_TRUE(checkKey(key, "key3", TSIGKeyInfo::HMAC_SHA256_STR,
                         ref_secret, 128));

    // Find the 4th key and retrieve it.
    gotit = keys_->find("key4");
    ASSERT_TRUE(gotit != keys_->end());
    key = gotit->second;

    // Verify the key contents.
    EXPECT_TRUE(checkKey(key, "key4", TSIGKeyInfo::HMAC_SHA224_STR,
                         ref_secret, 112));

    // Find the 5th key and retrieve it.
    gotit = keys_->find("key5");
    ASSERT_TRUE(gotit != keys_->end());
    key = gotit->second;

    // Verify the key contents.
    EXPECT_TRUE(checkKey(key, "key5", TSIGKeyInfo::HMAC_SHA384_STR,
                         ref_secret, 192));

    // Find the 6th key and retrieve it.
    gotit = keys_->find("key6");
    ASSERT_TRUE(gotit != keys_->end());
    key = gotit->second;

    // Verify the key contents.
    EXPECT_TRUE(checkKey(key, "key6", TSIGKeyInfo::HMAC_SHA512_STR,
                         ref_secret, 256));
}

/// @brief Tests the enforcement of data validation when parsing DnsServerInfos.
/// It verifies that:
/// 1. Specifying both a hostname and an ip address is not allowed.
/// 2. Specifying both blank a hostname and blank ip address is not allowed.
/// 3. Specifying a negative port number is not allowed.

TEST_F(DnsServerInfoParserTest, invalidEntry) {
    // Create a config in which both host and ip address are supplied.
    // Verify that parsing fails.
    std::string config = "{ \"hostname\": \"pegasus.example\", "
                         "  \"ip-address\": \"127.0.0.1\", "
                         "  \"port\": 100} ";
    PARSE_FAIL(config, "<string>:1.13: hostname is not yet supported");


    // Neither host nor ip address supplied
    // Verify that builds fails.
    config = "{ \"hostname\": \"\", "
             "  \"ip-address\": \"\", "
             "  \"port\": 100} ";
    PARSE_FAIL(config, "Dns Server must specify one or the other"
                          " of hostname or IP address (<string>:1:1)");

    // Create a config with a negative port number.
    // Verify that build fails.
    config = "{ \"hostname\": \"\", "
             "  \"ip-address\": \"192.168.5.6\" ,"
             "  \"port\": -100 }";
    PARSE_FAIL(config, "<string>:1.60-63: port must be greater than zero but less than 65536");
}


/// @brief Verifies that DnsServerInfo parsing creates a proper DnsServerInfo
/// when given a valid combination of entries.
/// It verifies that:
/// 1. A DnsServerInfo entry is correctly made, when given only a hostname.
/// 2. A DnsServerInfo entry is correctly made, when given ip address and port.
/// 3. A DnsServerInfo entry is correctly made, when given only an ip address.
TEST_F(DnsServerInfoParserTest, validEntry) {
    /// @todo When resolvable hostname is supported you'll need this test.
    /// // Valid entries for dynamic host
    /// std::string config = "{ \"hostname\": \"pegasus.example\" }";
    /// ASSERT_TRUE(fromJSON(config));

    /// // Verify that it builds and commits without throwing.
    /// ASSERT_NO_THROW(parser_->build(config_set_));
    /// ASSERT_NO_THROW(parser_->commit());

    /// //Verify the correct number of servers are present
    /// int count =  servers_->size();
    /// EXPECT_EQ(1, count);

    /// Verify the server exists and has the correct values.
    /// DnsServerInfoPtr server = (*servers_)[0];
    /// EXPECT_TRUE(checkServer(server, "pegasus.example",
    ///                         DnsServerInfo::EMPTY_IP_STR,
    ///                         DnsServerInfo::STANDARD_DNS_PORT));

    /// // Start over for a new test.
    /// reset();

    // Valid entries for static ip
    std::string config = " { \"hostname\" : \"\", "
                         "  \"ip-address\": \"127.0.0.1\" , "
                         "  \"port\": 100 }";
    PARSE_OK(config);
    ASSERT_TRUE(server_);
    EXPECT_TRUE(checkServer(server_, "", "127.0.0.1", 100));

    // Verify unparsing.
    runToElementTest<DnsServerInfo>(config, *server_);

    // Valid entries for static ip, no port
    // This will fail without invoking set defaults
    config = " { \"ip-address\": \"192.168.2.5\" }";
    PARSE_OK(config);
    ASSERT_TRUE(server_);
    EXPECT_TRUE(checkServer(server_, "", "192.168.2.5",
                            DnsServerInfo::STANDARD_DNS_PORT));
}

/// @brief Verifies that attempting to parse an invalid list of DnsServerInfo
/// entries is detected.
TEST_F(DnsServerInfoListParserTest, invalidServerList) {
    // Construct a list of servers with an invalid server entry.
    std::string config = "[ { \"ip-address\": \"127.0.0.1\" }, "
                        "{ \"ip-address\": \"\" }, "
                        "{ \"ip-address\": \"127.0.0.2\" } ]";
    PARSE_FAIL(config, "Dns Server must specify one or the other"
                          " of hostname or IP address (<string>:1:34)");
    ASSERT_FALSE(servers_);
}

/// @brief Verifies that a list of DnsServerInfo entries parses correctly given
/// a valid configuration.
TEST_F(DnsServerInfoListParserTest, validServerList) {
    // Create a valid list of servers.
    std::string config = "[ { \"ip-address\": \"127.0.0.1\" }, "
                        "{ \"ip-address\": \"127.0.0.2\" }, "
                        "{ \"ip-address\": \"127.0.0.3\" } ]";
    PARSE_OK(config);

    // Verify that the server storage contains the correct number of servers.
    ASSERT_EQ(3, servers_->size());

    // Verify the first server exists and has the correct values.
    DnsServerInfoPtr server = (*servers_)[0];
    EXPECT_TRUE(checkServer(server, "", "127.0.0.1",
                            DnsServerInfo::STANDARD_DNS_PORT));

    // Verify the second server exists and has the correct values.
    server = (*servers_)[1];
    EXPECT_TRUE(checkServer(server, "", "127.0.0.2",
                            DnsServerInfo::STANDARD_DNS_PORT));

    // Verify the third server exists and has the correct values.
    server = (*servers_)[2];
    EXPECT_TRUE(checkServer(server, "", "127.0.0.3",
                            DnsServerInfo::STANDARD_DNS_PORT));
}

/// @brief Tests the enforcement of data validation when parsing DdnsDomains.
/// It verifies that:
/// 1. Domain storage cannot be null when constructing a DdnsDomainParser.
/// 2. The name entry is not optional.
/// 3. The server list may not be empty.
/// 4. That a mal-formed server entry is detected.
/// 5. That an undefined key name is detected.
TEST_F(DdnsDomainParserTest, invalidDomain) {
    // Create a domain configuration without a name
    std::string config = "{  \"key-name\": \"d2_key.example.com\" , "
                         "  \"dns-servers\" : [ "
                         "  {  \"ip-address\": \"127.0.0.1\" , "
                         "    \"port\": 100 },"
                         "  { \"ip-address\": \"127.0.0.2\" , "
                         "    \"port\": 200 },"
                         "  {  \"ip-address\": \"127.0.0.3\" , "
                         "    \"port\": 300 } ] } ";
    PARSE_FAIL(config, "missing parameter 'name' (<string>:1:1)");

    // Create a domain configuration with an empty server list.
    config = "{ \"name\": \"example.com\" , "
             "  \"key-name\": \"\" , "
             "  \"dns-servers\" : [ "
             "   ] } ";
    PARSE_FAIL(config, "<string>:1.69: syntax error, unexpected ], expecting {");

    // Create a domain configuration with a mal-formed server entry.
    config = "{ \"name\": \"example.com\" , "
             "  \"key-name\": \"\" , "
             "  \"dns-servers\" : [ "
             "  {  \"ip-address\": \"127.0.0.3\" , "
             "    \"port\": -1 } ] } ";
    PARSE_FAIL(config, "<string>:1.111-112: port must be greater than zero but less than 65536");

    // Create a domain configuration without an defined key name
    config = "{ \"name\": \"example.com\" , "
             "  \"key-name\": \"d2_key.example.com\" , "
             "  \"dns-servers\" : [ "
             "  {  \"ip-address\": \"127.0.0.3\" , "
             "    \"port\": 300 } ] } ";
    PARSE_FAIL(config, "DdnsDomain : specifies"
                " an undefined key: d2_key.example.com (<string>:1:41)");
}

/// @brief Verifies the basics of parsing of a DdnsDomain.
TEST_F(DdnsDomainParserTest, validDomain) {
    // Add a TSIG key to the test key map, so key validation will pass.
    addKey("d2_key.example.com", "HMAC-MD5", "GWG/Xfbju4O2iXGqkSu4PQ==");

    // Create a valid domain configuration entry containing three valid
    // servers.
    std::string config =
                        "{ \"name\": \"example.com\" , "
                        "  \"key-name\": \"d2_key.example.com\" , "
                        "  \"dns-servers\" : [ "
                        "  {  \"ip-address\": \"127.0.0.1\" , "
                        "    \"port\": 100 },"
                        "  { \"ip-address\": \"127.0.0.2\" , "
                        "    \"port\": 200 },"
                        "  {  \"ip-address\": \"127.0.0.3\" , "
                        "    \"port\": 300 } ] } ";
    PARSE_OK(config);

    // Domain should exist
    ASSERT_TRUE(domain_);

    // Verify the name and key_name values.
    EXPECT_EQ("example.com", domain_->getName());
    EXPECT_EQ("d2_key.example.com", domain_->getKeyName());

    // Verify that the server list exists and contains the correct number of
    // servers.
    const DnsServerInfoStoragePtr& servers = domain_->getServers();
    ASSERT_TRUE(servers);
    EXPECT_EQ(3, servers->size());

    // Fetch each server and verify its contents.
    DnsServerInfoPtr server = (*servers)[0];
    ASSERT_TRUE(server);

    EXPECT_TRUE(checkServer(server, "", "127.0.0.1", 100));
    ASSERT_TRUE(server->getTSIGKeyInfo());
    EXPECT_TRUE(server->getTSIGKeyInfo()->getTSIGKey());

    server = (*servers)[1];
    ASSERT_TRUE(server);

    EXPECT_TRUE(checkServer(server, "", "127.0.0.2", 200));
    ASSERT_TRUE(server->getTSIGKeyInfo());
    EXPECT_TRUE(server->getTSIGKeyInfo()->getTSIGKey());

    server = (*servers)[2];
    ASSERT_TRUE(server);

    EXPECT_TRUE(checkServer(server, "", "127.0.0.3", 300));
    ASSERT_TRUE(server->getTSIGKeyInfo());
    EXPECT_TRUE(server->getTSIGKeyInfo()->getTSIGKey());

    // Verify unparsing.
    ElementPtr json;
    ASSERT_NO_THROW(json = Element::fromJSON(config));
    ConstElementPtr servers_json;
    ASSERT_NO_THROW(servers_json = json->get("dns-servers"));
    ASSERT_TRUE(servers_json);
    ASSERT_EQ(Element::list, servers_json->getType());
    for (size_t i = 0; i < servers_json->size(); ++i) {
        ElementPtr server_json;
        ASSERT_NO_THROW(server_json = servers_json->getNonConst(i));
        ASSERT_NO_THROW(server_json->set("hostname",
                                         Element::create(std::string())));
    }
    runToElementTest<DdnsDomain>(json, *domain_);
}

/// @brief Tests the fundamentals of parsing DdnsDomain lists.
/// This test verifies that given a valid domain list configuration
/// it will accurately parse and populate each domain in the list.
TEST_F(DdnsDomainListParserTest, validList) {
    // Add keys to key map so key validation passes.
    addKey("d2_key.example.com", "HMAC-MD5", "GWG/Xfbju4O2iXGqkSu4PQ==");
    addKey("d2_key.billcat.net", "HMAC-MD5", "GWG/Xfbju4O2iXGqkSu4PQ==");

    // Create a valid domain list configuration, with two domains
    // that have three servers each.
    std::string config =
                        "[ "
                        "{ \"name\": \"example.com\" , "
                        "  \"key-name\": \"d2_key.example.com\" , "
                        "  \"dns-servers\" : [ "
                        "  { \"ip-address\": \"127.0.0.1\" , "
                        "    \"port\": 100 },"
                        "  { \"ip-address\": \"127.0.0.2\" , "
                        "    \"port\": 200 },"
                        "  { \"ip-address\": \"127.0.0.3\" , "
                        "    \"port\": 300 } ] } "
                        ", "
                        "{ \"name\": \"billcat.net\" , "
                        "  \"key-name\": \"d2_key.billcat.net\" , "
                        "  \"dns-servers\" : [ "
                        "  { \"ip-address\": \"127.0.0.4\" , "
                        "    \"port\": 400 },"
                        "  { \"ip-address\": \"127.0.0.5\" , "
                        "    \"port\": 500 },"
                        "  { \"ip-address\": \"127.0.0.6\" , "
                        "    \"port\": 600 } ] } "
                        "] ";

    // Verify that the domain list parses without error.
    PARSE_OK(config);
    ASSERT_TRUE(domains_);
    EXPECT_EQ(2, domains_->size());

    // Verify that the first domain exists and can be retrieved.
    DdnsDomainMap::iterator gotit = domains_->find("example.com");
    ASSERT_TRUE(gotit != domains_->end());
    DdnsDomainPtr& domain = gotit->second;

    // Verify the name and key_name values of the first domain.
    EXPECT_EQ("example.com", domain->getName());
    EXPECT_EQ("d2_key.example.com", domain->getKeyName());

    // Verify the each of the first domain's servers
    DnsServerInfoStoragePtr servers = domain->getServers();
    ASSERT_TRUE(servers);
    EXPECT_EQ(3, servers->size());

    DnsServerInfoPtr server = (*servers)[0];
    ASSERT_TRUE(server);
    EXPECT_TRUE(checkServer(server, "", "127.0.0.1", 100));

    // Verify the TSIGKeyInfo name and that the actual key was created
    ASSERT_TRUE(server->getTSIGKeyInfo());
    EXPECT_EQ(domain->getKeyName(), server->getKeyName());
    EXPECT_EQ(domain->getKeyName(), server->getTSIGKeyInfo()->getName());
    EXPECT_TRUE(server->getTSIGKeyInfo()->getTSIGKey());

    server = (*servers)[1];
    ASSERT_TRUE(server);
    EXPECT_TRUE(checkServer(server, "", "127.0.0.2", 200));
    ASSERT_TRUE(server->getTSIGKeyInfo());
    EXPECT_EQ(domain->getKeyName(), server->getKeyName());
    EXPECT_EQ(domain->getKeyName(), server->getTSIGKeyInfo()->getName());
    EXPECT_TRUE(server->getTSIGKeyInfo()->getTSIGKey());

    server = (*servers)[2];
    ASSERT_TRUE(server);
    EXPECT_TRUE(checkServer(server, "", "127.0.0.3", 300));
    ASSERT_TRUE(server->getTSIGKeyInfo());
    EXPECT_EQ(domain->getKeyName(), server->getKeyName());
    EXPECT_EQ(domain->getKeyName(), server->getTSIGKeyInfo()->getName());
    EXPECT_TRUE(server->getTSIGKeyInfo()->getTSIGKey());

    // Verify second domain
    gotit = domains_->find("billcat.net");
    ASSERT_TRUE(gotit != domains_->end());
    domain = gotit->second;

    // Verify the name and key_name values of the second domain.
    EXPECT_EQ("billcat.net", domain->getName());
    EXPECT_EQ("d2_key.billcat.net", domain->getKeyName());

    // Verify the each of second domain's servers
    servers = domain->getServers();
    ASSERT_TRUE(servers);
    EXPECT_EQ(3, servers->size());

    server = (*servers)[0];
    ASSERT_TRUE(server);
    EXPECT_TRUE(checkServer(server, "", "127.0.0.4", 400));
    ASSERT_TRUE(server->getTSIGKeyInfo());
    EXPECT_EQ(domain->getKeyName(), server->getKeyName());
    EXPECT_EQ(domain->getKeyName(), server->getTSIGKeyInfo()->getName());
    EXPECT_TRUE(server->getTSIGKeyInfo()->getTSIGKey());

    server = (*servers)[1];
    ASSERT_TRUE(server);
    EXPECT_TRUE(checkServer(server, "", "127.0.0.5", 500));
    ASSERT_TRUE(server->getTSIGKeyInfo());
    EXPECT_EQ(domain->getKeyName(), server->getKeyName());
    EXPECT_EQ(domain->getKeyName(), server->getTSIGKeyInfo()->getName());
    EXPECT_TRUE(server->getTSIGKeyInfo()->getTSIGKey());

    server = (*servers)[2];
    ASSERT_TRUE(server);
    EXPECT_TRUE(checkServer(server, "", "127.0.0.6", 600));
    ASSERT_TRUE(server->getTSIGKeyInfo());
    EXPECT_EQ(domain->getKeyName(), server->getKeyName());
    EXPECT_EQ(domain->getKeyName(), server->getTSIGKeyInfo()->getName());
    EXPECT_TRUE(server->getTSIGKeyInfo()->getTSIGKey());
}

/// @brief Tests that a domain list configuration cannot contain duplicates.
TEST_F(DdnsDomainListParserTest, duplicateDomain) {
    // Create a domain list configuration that contains two domains with
    // the same name.
    std::string config =
                        "[ "
                        "{ \"name\": \"example.com\" , "
                        "  \"dns-servers\" : [ "
                        "  { \"ip-address\": \"127.0.0.3\" , "
                        "    \"port\": 300 } ] } "
                        ", "
                        "{ \"name\": \"example.com\" , "
                        "  \"dns-servers\" : [ "
                        "  { \"ip-address\": \"127.0.0.3\" , "
                        "    \"port\": 300 } ] } "
                        "] ";
    // Verify that the parsing fails.
    PARSE_FAIL(config,
               "Duplicate domain specified:example.com (<string>:1:115)");
}

}
