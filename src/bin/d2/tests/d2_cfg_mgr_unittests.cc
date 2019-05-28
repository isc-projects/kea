// Copyright (C) 2013-2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <d2/d2_config.h>
#include <d2/d2_cfg_mgr.h>
#include <d2/d2_simple_parser.h>
#include <d2/parser_context.h>
#include <d2/tests/parser_unittest.h>
#include <dhcpsrv/testutils/config_result_check.h>
#include <process/testutils/d_test_stubs.h>
#include <test_data_files_config.h>
#include <util/encode/base64.h>

#include <boost/foreach.hpp>
#include <boost/scoped_ptr.hpp>
#include <gtest/gtest.h>

using namespace std;
using namespace isc;
using namespace isc::d2;
using namespace isc::process;

namespace {

/// @brief Function to create full path to test data file
///
/// The full path is dependent upon the value of D2_TEST_DATA_DIR which
/// whose value is generated from test_data_files_config.h.in
///
/// @param name file name to which the path should be prepended
std::string testDataFile(const std::string& name) {
    return (std::string(D2_TEST_DATA_DIR) + "/" + name);
}

/// @brief Test fixture class for testing D2CfgMgr class.
/// It maintains an member instance of D2CfgMgr and provides methods for
/// converting JSON strings to configuration element sets, checking parse
/// results, and accessing the configuration context.
class D2CfgMgrTest : public ConfigParseTest {
public:

    /// @brief Constructor
    D2CfgMgrTest():cfg_mgr_(new D2CfgMgr()), d2_params_() {
    }

    /// @brief Destructor
    ~D2CfgMgrTest() {
    }

    /// @brief Configuration manager instance.
    D2CfgMgrPtr cfg_mgr_;

    /// @brief Build JSON configuration string for a D2Params element
    ///
    /// Constructs a JSON string for "params" element using replaceable
    /// parameters.
    ///
    /// @param ip_address string to insert as ip_address value
    /// @param port integer to insert as port value
    /// @param dns_server_timeout integer to insert as dns_server_timeout value
    /// @param ncr_protocol string to insert as ncr_protocol value
    /// @param ncr_format string to insert as ncr_format value
    ///
    /// @return std::string containing the JSON configuration text
    std::string makeParamsConfigString(const std::string& ip_address,
                                       const int port,
                                       const int dns_server_timeout,
                                       const std::string& ncr_protocol,
                                       const std::string& ncr_format) {
        std::ostringstream config;
        config <<
            "{"
            " \"ip-address\": \"" << ip_address << "\" , "
            " \"port\": " << port << " , "
            " \"dns-server-timeout\": " << dns_server_timeout << " , "
            " \"ncr-protocol\": \"" << ncr_protocol << "\" , "
            " \"ncr-format\": \"" << ncr_format << "\", "
            " \"tsig-keys\": [], "
            " \"forward-ddns\" : {}, "
            " \"reverse-ddns\" : {} "
            "}";

        return (config.str());
    }

    /// @brief Enumeration to select between expected configuration outcomes
    enum RunConfigMode {
        NO_ERROR,
        SYNTAX_ERROR,
        LOGIC_ERROR
    };

    /// @brief Parses a configuration string and tests against a given outcome
    ///
    /// Convenience method which accepts JSON text and an expected pass or fail
    /// outcome.  It uses the D2ParserContext to parse the text under the
    /// PARSE_SUB_DHCPDDNS context, then adds the D2 defaults to the resultant
    /// element tree. Assuming that's successful the element tree is passed
    /// to D2CfgMgr::parseConfig() method.
    ///
    /// @param config_str the JSON configuration text to parse
    /// @param error_type  indicates the type error expected, NONE, SYNTAX,
    /// or LOGIC. SYNTAX errors are emitted by JSON parser, logic errors
    /// are emitted by element parser(s).
    /// @param exp_error exact text of the error message expected
    /// defaults to SHOULD_PASS.
    ///
    /// @return AssertionSuccess if test passes, AssertionFailure otherwise
    ::testing::AssertionResult runConfigOrFail(const std::string& json,
                                               const RunConfigMode mode,
                                               const std::string& exp_error) {

        try {
            // Invoke the JSON parser, casting the returned element tree
            // into mutable form.
            D2ParserContext parser_context;
            data::ElementPtr elem =
                boost::const_pointer_cast<Element>
                (parser_context.parseString(json, D2ParserContext::
                                                  PARSER_SUB_DHCPDDNS));

            // If parsing succeeded when we expected a syntax error, then fail.
            if (mode == SYNTAX_ERROR) {
               return ::testing::AssertionFailure()
                             << "Unexpected  JSON parsing success"
                             << "\njson: [" << json << " ]";
            }

            // JSON parsed ok, so add the defaults to the element tree it produced.
            D2SimpleParser::setAllDefaults(elem);
            config_set_ = elem;
        } catch (const std::exception& ex) {
            // JSON Parsing failed
            if (exp_error.empty()) {
                // We did not expect an error, so fail.
                return ::testing::AssertionFailure()
                          << "Unexpected syntax error:" << ex.what()
                          << "\njson: [" << json << " ]";
            }

            if (ex.what() != exp_error) {
                // Expected an error not the one we got, so fail
                return ::testing::AssertionFailure()
                          << "Wrong syntax error detected, expected: "
                          << exp_error << ", got: " << ex.what()
                          << "\njson: [" << json << " ]";
            }

            // We go the syntax error we expected, so return success
            return ::testing::AssertionSuccess();
        }

        // The JSON parsed ok and we've added the defaults, pass the config
        // into the Element parser and check for the expected outcome.
        data::ConstElementPtr answer;
        answer = cfg_mgr_->simpleParseConfig(config_set_, false);

        // Extract the result and error text from the answer.
        int rcode = 0;
        isc::data::ConstElementPtr comment;
        comment = isc::config::parseAnswer(rcode, answer);

        if (rcode != 0) {
            // Element Parsing failed.
            if (exp_error.empty()) {
                // We didn't expect it to, fail the test.
                return ::testing::AssertionFailure()
                              << "Unexpected logic error: " << *comment
                              << "\njson: [" << json << " ]";
            }

            if (comment->stringValue() != exp_error) {
                // We 't expect a different error, fail the test.
                return ::testing::AssertionFailure()
                              << "Wrong logic error detected, expected: "
                              << exp_error << ", got: " << *comment
                              << "\njson: [" << json << " ]";
            }
        } else {
            // Element parsing succeeded.
            if (!exp_error.empty()) {
                // It was supposed to fail, so fail the test.
                return ::testing::AssertionFailure()
                              << "Unexpected logic success, expected error:"
                              << exp_error
                              << "\njson: [" << json << " ]";
            }
        }

        // Verify that the D2 context can be retrieved and is not null.
        D2CfgContextPtr context;
        context = cfg_mgr_->getD2CfgContext();
        if (!context) {
            return ::testing::AssertionFailure() << "D2CfgContext is null";
        }

        // Verify that the global scalar container has been created.
        d2_params_ = context->getD2Params();
        if (!d2_params_) {
            return ::testing::AssertionFailure() << "D2Params is null";
        }

        return ::testing::AssertionSuccess();
    }


    /// @brief Pointer the D2Params most recently parsed.
    D2ParamsPtr d2_params_;
};

/// @brief Convenience macros for invoking runOrConfig()
#define RUN_CONFIG_OK(a) (runConfigOrFail(a, NO_ERROR, ""))
#define SYNTAX_ERROR(a,b) ASSERT_TRUE(runConfigOrFail(a,SYNTAX_ERROR,b))
#define LOGIC_ERROR(a,b) ASSERT_TRUE(runConfigOrFail(a,LOGIC_ERROR,b))

/// @brief Tests a basic valid configuration for D2Param.
TEST_F(D2CfgMgrTest, validParamsEntry) {
    // Verify that ip_address can be valid v4 address.
    std::string config = makeParamsConfigString ("192.0.0.1", 777, 333,
                                           "UDP", "JSON");
    RUN_CONFIG_OK(config);

    EXPECT_EQ(isc::asiolink::IOAddress("192.0.0.1"),
              d2_params_->getIpAddress());
    EXPECT_EQ(777, d2_params_->getPort());
    EXPECT_EQ(333, d2_params_->getDnsServerTimeout());
    EXPECT_EQ(dhcp_ddns::NCR_UDP, d2_params_->getNcrProtocol());
    EXPECT_EQ(dhcp_ddns::FMT_JSON, d2_params_->getNcrFormat());

    // Verify that ip_address can be valid v6 address.
    config = makeParamsConfigString ("3001::5", 777, 333, "UDP", "JSON");
    RUN_CONFIG_OK(config);

    // Verify that the global scalars have the proper values.
    EXPECT_EQ(isc::asiolink::IOAddress("3001::5"),
              d2_params_->getIpAddress());

    // Verify the configuration summary.
    EXPECT_EQ("listening on 3001::5, port 777, using UDP",
              d2_params_->getConfigSummary());
}

/// @brief Tests default values for D2Params.
/// It verifies that D2Params is populated with default value for optional
/// parameter if not supplied in the configuration.
/// Currently they are all optional.
TEST_F(D2CfgMgrTest, defaultValues) {

    ElementPtr defaults = isc::d2::test::parseJSON("{ }");
    ASSERT_NO_THROW(D2SimpleParser::setAllDefaults(defaults));

    // Check that omitting ip_address gets you its default
    std::string config =
            "{"
            " \"port\": 777 , "
            " \"dns-server-timeout\": 333 , "
            " \"ncr-protocol\": \"UDP\" , "
            " \"ncr-format\": \"JSON\", "
            " \"tsig-keys\": [], "
            " \"forward-ddns\" : {}, "
            " \"reverse-ddns\" : {} "
            "}";

    RUN_CONFIG_OK(config);
    ConstElementPtr deflt;
    ASSERT_NO_THROW(deflt = defaults->get("ip-address"));
    ASSERT_TRUE(deflt);
    EXPECT_EQ(deflt->stringValue(), d2_params_->getIpAddress().toText());

    // Check that omitting port gets you its default
    config =
            "{"
            " \"ip-address\": \"192.0.0.1\" , "
            " \"dns-server-timeout\": 333 , "
            " \"ncr-protocol\": \"UDP\" , "
            " \"ncr-format\": \"JSON\", "
            " \"tsig-keys\": [], "
            " \"forward-ddns\" : {}, "
            " \"reverse-ddns\" : {} "
            "}";

    RUN_CONFIG_OK(config);
    ASSERT_NO_THROW(deflt = defaults->get("port"));
    ASSERT_TRUE(deflt);
    EXPECT_EQ(deflt->intValue(), d2_params_->getPort());

    // Check that omitting timeout gets you its default
    config =
            "{"
            " \"ip-address\": \"192.0.0.1\" , "
            " \"port\": 777 , "
            " \"ncr-protocol\": \"UDP\" , "
            " \"ncr-format\": \"JSON\", "
            " \"tsig-keys\": [], "
            " \"forward-ddns\" : {}, "
            " \"reverse-ddns\" : {} "
            "}";

    RUN_CONFIG_OK(config);
    ASSERT_NO_THROW(deflt = defaults->get("dns-server-timeout"));
    ASSERT_TRUE(deflt);
    EXPECT_EQ(deflt->intValue(), d2_params_->getDnsServerTimeout());

    // Check that omitting protocol gets you its default
    config =
            "{"
            " \"ip-address\": \"192.0.0.1\" , "
            " \"port\": 777 , "
            " \"dns-server-timeout\": 333 , "
            " \"ncr-format\": \"JSON\", "
            " \"tsig-keys\": [], "
            " \"forward-ddns\" : {}, "
            " \"reverse-ddns\" : {} "
            "}";

    RUN_CONFIG_OK(config);
    ASSERT_NO_THROW(deflt = defaults->get("ncr-protocol"));
    ASSERT_TRUE(deflt);
    EXPECT_EQ(dhcp_ddns::stringToNcrProtocol(deflt->stringValue()),
              d2_params_->getNcrProtocol());

    // Check that omitting format gets you its default
    config =
            "{"
            " \"ip-address\": \"192.0.0.1\" , "
            " \"port\": 777 , "
            " \"dns-server-timeout\": 333 , "
            " \"ncr-protocol\": \"UDP\", "
            " \"tsig-keys\": [], "
            " \"forward-ddns\" : {}, "
            " \"reverse-ddns\" : {} "
            "}";

    RUN_CONFIG_OK(config);
    ASSERT_NO_THROW(deflt = defaults->get("ncr-format"));
    ASSERT_TRUE(deflt);
    EXPECT_EQ(dhcp_ddns::stringToNcrFormat(deflt->stringValue()),
              d2_params_->getNcrFormat());
}

/// @brief Tests the unsupported scalar parameters and objects are detected.
TEST_F(D2CfgMgrTest, unsupportedTopLevelItems) {
    // Check that an unsupported top level parameter fails.
    std::string config =
            "{"
            " \"ip-address\": \"127.0.0.1\", "
            " \"port\": 777 , "
            " \"dns-server-timeout\": 333 , "
            " \"ncr-protocol\": \"UDP\" , "
            " \"ncr-format\": \"JSON\", "
            " \"tsig-keys\": [], "
            " \"forward-ddns\" : {}, "
            " \"reverse-ddns\" : {}, "
            " \"bogus-param\" : true "
            "}";

    SYNTAX_ERROR(config, "<string>:1.185-197: got unexpected "
                         "keyword \"bogus-param\" in DhcpDdns map.");

    // Check that unsupported top level objects fails.  For
    // D2 these fail as they are not in the parse order.
    config =
            "{"
            " \"ip-address\": \"127.0.0.1\", "
            " \"port\": 777 , "
            " \"dns-server-timeout\": 333 , "
            " \"ncr-protocol\": \"UDP\" , "
            " \"ncr-format\": \"JSON\", "
            " \"tsig-keys\": [], "
            " \"bogus-object-one\" : {}, "
            " \"forward-ddns\" : {}, "
            " \"reverse-ddns\" : {}, "
            " \"bogus-object-two\" : {} "
            "}";

    SYNTAX_ERROR(config, "<string>:1.141-158: got unexpected"
                         " keyword \"bogus-object-one\" in DhcpDdns map.");
}


/// @brief Tests the enforcement of data validation when parsing D2Params.
/// It verifies that:
/// -# ip_address cannot be "0.0.0.0"
/// -# ip_address cannot be "::"
/// -# port cannot be 0
/// -# dns_server_timeout cannot be 0
/// -# ncr_protocol must be valid
/// -# ncr_format must be valid
TEST_F(D2CfgMgrTest, invalidEntry) {
    // Cannot use IPv4 ANY address
    std::string config = makeParamsConfigString ("0.0.0.0", 777, 333,
                                           "UDP", "JSON");
    LOGIC_ERROR(config, "IP address cannot be \"0.0.0.0\" (<string>:1:17)");

    // Cannot use IPv6 ANY address
    config = makeParamsConfigString ("::", 777, 333, "UDP", "JSON");
    LOGIC_ERROR(config, "IP address cannot be \"::\" (<string>:1:17)");

    // Cannot use port  0
    config = makeParamsConfigString ("127.0.0.1", 0, 333, "UDP", "JSON");
    SYNTAX_ERROR(config, "<string>:1.40: port must be greater than zero but less than 65536");

    // Cannot use dns server timeout of 0
    config = makeParamsConfigString ("127.0.0.1", 777, 0, "UDP", "JSON");
    SYNTAX_ERROR(config, "<string>:1.69: dns-server-timeout"
                         " must be greater than zero");

    // Invalid protocol
    config = makeParamsConfigString ("127.0.0.1", 777, 333, "BOGUS", "JSON");
    SYNTAX_ERROR(config, "<string>:1.92-98: syntax error,"
                         " unexpected constant string, expecting UDP or TCP");

    // Unsupported protocol
    config = makeParamsConfigString ("127.0.0.1", 777, 333, "TCP", "JSON");
    LOGIC_ERROR(config, "ncr-protocol : TCP is not yet supported"
                        "  (<string>:1:92)");

    // Invalid format
    config = makeParamsConfigString ("127.0.0.1", 777, 333, "UDP", "BOGUS");
    SYNTAX_ERROR(config, "<string>:1.115-121: syntax error,"
                         " unexpected constant string, expecting JSON");
}

// Control socket tests in d2_process_unittests.cc

// DdnsDomainList and TSIGKey tests moved to d2_simple_parser_unittest.cc

/// @brief Tests construction of D2CfgMgr
/// This test verifies that a D2CfgMgr constructs properly.
TEST(D2CfgMgr, construction) {
    boost::scoped_ptr<D2CfgMgr> cfg_mgr;

    // Verify that configuration manager constructions without error.
    ASSERT_NO_THROW(cfg_mgr.reset(new D2CfgMgr()));

    // Verify that the context can be retrieved and is not null.
    D2CfgContextPtr context;
    ASSERT_NO_THROW(context = cfg_mgr->getD2CfgContext());
    EXPECT_TRUE(context);

    // Verify that the forward manager can be retrieved and is not null.
    EXPECT_TRUE(context->getForwardMgr());

    // Verify that the reverse manager can be retrieved and is not null.
    EXPECT_TRUE(context->getReverseMgr());

    // Verify that the manager can be destructed without error.
    EXPECT_NO_THROW(cfg_mgr.reset());
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
                        "\"ip-address\" : \"192.168.1.33\" , "
                        "\"port\" : 88 , "
                        "\"dns-server-timeout\": 333 , "
                        "\"ncr-protocol\": \"UDP\" , "
                        "\"ncr-format\": \"JSON\", "
                        "\"control-socket\" : {"
                        " \"socket-type\" : \"unix\" ,"
                        " \"socket-name\" : \"/tmp/d2-ctrl-channel\" "
                        "},"
                        "\"tsig-keys\": ["
                        "{"
                        "  \"name\": \"d2_key.example.com\" , "
                        "  \"algorithm\": \"hmac-md5\" , "
                        "   \"secret\": \"LSWXnfkKZjdPJI5QxlpnfQ==\" "
                        "},"
                        "{"
                        "  \"name\": \"d2_key.billcat.net\" , "
                        "  \"algorithm\": \"hmac-md5\" , "
                        " \"digest-bits\": 120 , "
                        "   \"secret\": \"LSWXnfkKZjdPJI5QxlpnfQ==\" "
                        "}"
                        "],"
                        "\"forward-ddns\" : {"
                        "\"ddns-domains\": [ "
                        "{ \"name\": \"example.com\" , "
                        "  \"key-name\": \"d2_key.example.com\" , "
                        "  \"dns-servers\" : [ "
                        "  { \"ip-address\": \"127.0.0.1\" } , "
                        "  { \"ip-address\": \"127.0.0.2\" } , "
                        "  { \"ip-address\": \"127.0.0.3\"} "
                        "  ] } "
                        ", "
                        "{ \"name\": \"billcat.net\" , "
                        "  \"key-name\": \"d2_key.billcat.net\" , "
                        "  \"dns-servers\" : [ "
                        "  { \"ip-address\": \"127.0.0.4\" } , "
                        "  { \"ip-address\": \"127.0.0.5\" } , "
                        "  { \"ip-address\": \"127.0.0.6\" } "
                        "  ] } "
                        "] },"
                        "\"reverse-ddns\" : {"
                        "\"ddns-domains\": [ "
                        "{ \"name\": \" 0.168.192.in.addr.arpa.\" , "
                        "  \"key-name\": \"d2_key.example.com\" , "
                        "  \"dns-servers\" : [ "
                        "  { \"ip-address\": \"127.0.1.1\" } , "
                        "  { \"ip-address\": \"127.0.2.1\" } , "
                        "  { \"ip-address\": \"127.0.3.1\" } "
                        "  ] } "
                        ", "
                        "{ \"name\": \" 0.247.106.in.addr.arpa.\" , "
                        "  \"key-name\": \"d2_key.billcat.net\" , "
                        "  \"dns-servers\" : [ "
                        "  { \"ip-address\": \"127.0.4.1\" }, "
                        "  { \"ip-address\": \"127.0.5.1\" } , "
                        "  { \"ip-address\": \"127.0.6.1\" } "
                        "  ] } "
                        "] } }";

    // Should parse without error.
    RUN_CONFIG_OK(config);

    // Verify that the D2 context can be retrieved and is not null.
    D2CfgContextPtr context;
    ASSERT_NO_THROW(context = cfg_mgr_->getD2CfgContext());

    // Verify that the global scalars have the proper values.
    D2ParamsPtr& d2_params = context->getD2Params();
    ASSERT_TRUE(d2_params);

    EXPECT_EQ(isc::asiolink::IOAddress("192.168.1.33"),
              d2_params->getIpAddress());
    EXPECT_EQ(88, d2_params->getPort());
    EXPECT_EQ(333, d2_params->getDnsServerTimeout());
    EXPECT_EQ(dhcp_ddns::NCR_UDP, d2_params->getNcrProtocol());
    EXPECT_EQ(dhcp_ddns::FMT_JSON, d2_params->getNcrFormat());

    // Verify that the control socket can be retrieved.
    ConstElementPtr ctrl_sock = context->getControlSocketInfo();
    ASSERT_TRUE(ctrl_sock);
    ASSERT_EQ(Element::map, ctrl_sock->getType());
    EXPECT_EQ(2, ctrl_sock->size());
    ASSERT_TRUE(ctrl_sock->get("socket-type"));
    EXPECT_EQ("\"unix\"", ctrl_sock->get("socket-type")->str());
    ASSERT_TRUE(ctrl_sock->get("socket-name"));
    EXPECT_EQ("\"/tmp/d2-ctrl-channel\"", ctrl_sock->get("socket-name")->str());

    // Verify that the forward manager can be retrieved.
    DdnsDomainListMgrPtr mgr = context->getForwardMgr();
    ASSERT_TRUE(mgr);
    EXPECT_EQ("forward-ddns", mgr->getName());

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
    EXPECT_EQ("reverse-ddns", mgr->getName());

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
    answer_ = cfg_mgr_->simpleParseConfig(config_set_, false);
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
                        "\"ip-address\" : \"192.168.1.33\" , "
                        "\"port\" : 88 , "
                        "\"tsig-keys\": [] ,"
                        "\"forward-ddns\" : {"
                        "\"ddns-domains\": [ "
                        "{ \"name\": \"example.com\" , "
                        "  \"dns-servers\" : [ "
                        "  { \"ip-address\": \"127.0.0.1\" } "
                        "  ] } "
                        ", "
                        "{ \"name\": \"one.example.com\" , "
                        "  \"dns-servers\" : [ "
                        "  { \"ip-address\": \"127.0.0.2\" } "
                        "  ] } "
                        ", "
                        "{ \"name\": \"*\" , "
                        "  \"dns-servers\" : [ "
                        "  { \"ip-address\": \"127.0.0.3\" } "
                        "  ] } "
                        "] }, "
                        "\"reverse-ddns\" : {} "
                        "}";

    // Verify that we can parse the configuration.
    RUN_CONFIG_OK(config);

    // Verify that the D2 context can be retrieved and is not null.
    D2CfgContextPtr context;
    ASSERT_NO_THROW(context = cfg_mgr_->getD2CfgContext());

    // Test directional update flags.
    EXPECT_TRUE(cfg_mgr_->forwardUpdatesEnabled());
    EXPECT_FALSE(cfg_mgr_->reverseUpdatesEnabled());

    DdnsDomainPtr match;
    // Verify that an exact match works.
    EXPECT_TRUE(cfg_mgr_->matchForward("example.com", match));
    EXPECT_EQ("example.com", match->getName());

    // Verify that search is case insensitive.
    EXPECT_TRUE(cfg_mgr_->matchForward("EXAMPLE.COM", match));
    EXPECT_EQ("example.com", match->getName());

    // Verify that an exact match works.
    EXPECT_TRUE(cfg_mgr_->matchForward("one.example.com", match));
    EXPECT_EQ("one.example.com", match->getName());

    // Verify that a FQDN for sub-domain matches.
    EXPECT_TRUE(cfg_mgr_->matchForward("blue.example.com", match));
    EXPECT_EQ("example.com", match->getName());

    // Verify that a FQDN for sub-domain matches.
    EXPECT_TRUE(cfg_mgr_->matchForward("red.one.example.com", match));
    EXPECT_EQ("one.example.com", match->getName());

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
                        "\"ip-address\" : \"192.168.1.33\" , "
                        "\"port\" : 88 , "
                        "\"tsig-keys\": [] ,"
                        "\"forward-ddns\" : {"
                        "\"ddns-domains\": [ "
                        "{ \"name\": \"example.com\" , "
                        "  \"dns-servers\" : [ "
                        "  { \"ip-address\": \"127.0.0.1\" } "
                        "  ] } "
                        ", "
                        "{ \"name\": \"one.example.com\" , "
                        "  \"dns-servers\" : [ "
                        "  { \"ip-address\": \"127.0.0.2\" } "
                        "  ] } "
                        "] }, "
                        "\"reverse-ddns\" : {} "
                        " }";

    // Verify that we can parse the configuration.
    RUN_CONFIG_OK(config);

    // Verify that the D2 context can be retrieved and is not null.
    D2CfgContextPtr context;
    ASSERT_NO_THROW(context = cfg_mgr_->getD2CfgContext());

    DdnsDomainPtr match;
    // Verify that full or partial matches, still match.
    EXPECT_TRUE(cfg_mgr_->matchForward("example.com", match));
    EXPECT_EQ("example.com", match->getName());

    EXPECT_TRUE(cfg_mgr_->matchForward("blue.example.com", match));
    EXPECT_EQ("example.com", match->getName());

    EXPECT_TRUE(cfg_mgr_->matchForward("red.one.example.com", match));
    EXPECT_EQ("one.example.com", match->getName());

    // Verify that a FQDN with no match, fails to match.
    EXPECT_FALSE(cfg_mgr_->matchForward("shouldbe.wildcard", match));
}

/// @brief Tests domain matching when there is ONLY a wild card domain.
/// This test verifies that any FQDN matches the wild card.
TEST_F(D2CfgMgrTest, matchAll) {
    std::string config = "{ "
                        "\"ip-address\" : \"192.168.1.33\" , "
                        "\"port\" : 88 , "
                        "\"tsig-keys\": [] ,"
                        "\"forward-ddns\" : {"
                        "\"ddns-domains\": [ "
                        "{ \"name\": \"*\" , "
                        "  \"dns-servers\" : [ "
                        "  { \"ip-address\": \"127.0.0.1\" } "
                        "  ] } "
                        "] }, "
                        "\"reverse-ddns\" : {} "
                        "}";

    // Verify that we can parse the configuration.
    RUN_CONFIG_OK(config);

    // Verify that the D2 context can be retrieved and is not null.
    D2CfgContextPtr context;
    ASSERT_NO_THROW(context = cfg_mgr_->getD2CfgContext());

    // Verify that wild card domain is returned for any FQDN.
    DdnsDomainPtr match;
    EXPECT_TRUE(cfg_mgr_->matchForward("example.com", match));
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
                        "\"ip-address\" : \"192.168.1.33\" , "
                        "\"port\" : 88 , "
                        "\"tsig-keys\": [] ,"
                        "\"forward-ddns\" : {}, "
                        "\"reverse-ddns\" : {"
                        "\"ddns-domains\": [ "
                        "{ \"name\": \"5.100.168.192.in-addr.arpa.\" , "
                        "  \"dns-servers\" : [ "
                        "  { \"ip-address\": \"127.0.0.1\" } "
                        "  ] }, "
                        "{ \"name\": \"100.200.192.in-addr.arpa.\" , "
                        "  \"dns-servers\" : [ "
                        "  { \"ip-address\": \"127.0.0.1\" } "
                        "  ] }, "
                        "{ \"name\": \"170.192.in-addr.arpa.\" , "
                        "  \"dns-servers\" : [ "
                        "  { \"ip-address\": \"127.0.0.1\" } "
                        "  ] }, "
                        // Note mixed case to test case insensitivity.
                        "{ \"name\": \"2.0.3.0.8.b.d.0.1.0.0.2.IP6.ARPA.\" , "
                        "  \"dns-servers\" : [ "
                        "  { \"ip-address\": \"127.0.0.1\" } "
                        "  ] },"
                        "{ \"name\": \"*\" , "
                        "  \"dns-servers\" : [ "
                        "  { \"ip-address\": \"127.0.0.1\" } "
                        "  ] } "
                        "] } }";

    // Verify that we can parse the configuration.
    RUN_CONFIG_OK(config);

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

/// @brief Tests D2 config parsing against a wide range of config permutations.
///
/// It tests for both syntax errors that the JSON parsing (D2ParserContext)
/// should detect as well as post-JSON parsing logic errors generated by
/// the Element parsers (i.e...SimpleParser/DhcpParser derivations)
///
///
/// It iterates over all of the test configurations described in given file.
/// The file content is JSON specialized to this test. The format of the file
/// is:
///
/// @code
/// # The file must open with a list. It's name is arbitrary.
///
/// { "test_list" :
/// [
///
/// #    Test one starts here:
///      {
///
/// #    Each test has:
/// #      1. description - optional text description
/// #      2. syntax-error - error JSON parser should emit (omit if none)
/// #      3. logic-error - error element parser(s) should emit (omit if none)
/// #      4. data - configuration text to parse
/// #
///      "description" : "<text describing test>",
///      "syntax-error" : "<exact text from JSON parser including position>" ,
///      "logic-error" : "<exact text from element parser including position>" ,
///      "data" :
///          {
/// #        configuration elements here
///          "bool_val" : false,
///          "some_map" :  {}
/// #         :
///          }
///      }
///
/// #    Next test would start here
///      ,
///      {
///      }
///
/// ]}
///
/// @endcode
///
/// (The file supports comments per Element::fromJSONFile())
///
TEST_F(D2CfgMgrTest, configPermutations) {
    std::string test_file = testDataFile("d2_cfg_tests.json");
    isc::data::ConstElementPtr tests;

    // Read contents of the file and parse it as JSON. Note it must contain
    // all valid JSON, we aren't testing JSON parsing.
    try {
        tests = isc::data::Element::fromJSONFile(test_file, true);
    } catch (const std::exception& ex) {
        FAIL() << "ERROR parsing file : " << test_file << " : " << ex.what();
    }

    // Read in each test For each test, read:
    //
    //  1. description - optional text description
    //  2. syntax-error or logic-error or neither
    //  3. data - configuration text to parse
    //  4. convert data into JSON text
    //  5. submit JSON for parsing
    isc::data::ConstElementPtr test;
    ASSERT_TRUE(tests->get("test-list"));
    BOOST_FOREACH(test, tests->get("test-list")->listValue()) {
        // Grab the description.
        std::string description = "<no desc>";
        isc::data::ConstElementPtr elem = test->get("description");
        if (elem) {
            elem->getValue(description);
        }

        // Grab the expected error message, if there is one.
        std::string expected_error = "";
        RunConfigMode mode = NO_ERROR;
        elem = test->get("syntax-error");
        if (elem) {
            elem->getValue(expected_error);
            mode = SYNTAX_ERROR;
        } else {
            elem = test->get("logic-error");
            if (elem) {
                elem->getValue(expected_error);
                mode = LOGIC_ERROR;
            }
        }

        // Grab the test's configuration data.
        isc::data::ConstElementPtr data = test->get("data");
        ASSERT_TRUE(data) << "No data for test: "
                          << " : " << test->getPosition();

        // Convert the test data back to JSON text, then submit it for parsing.
        stringstream os;
        data->toJSON(os);
        EXPECT_TRUE(runConfigOrFail(os.str(), mode, expected_error))
            << " failed for test: " << test->getPosition() << std::endl;
    }
}

/// @brief Tests comments.
TEST_F(D2CfgMgrTest, comments) {
    std::string config = "{ "
                        "\"comment\": \"D2 config\" , "
                        "\"ip-address\" : \"192.168.1.33\" , "
                        "\"port\" : 88 , "
                        "\"control-socket\": {"
                        " \"comment\": \"Control channel\" , "
                        " \"socket-type\": \"unix\" ,"
                        " \"socket-name\": \"/tmp/d2-ctrl-channel\" "
                        "},"
                        "\"tsig-keys\": ["
                        "{"
                        "  \"user-context\": { "
                        "    \"comment\": \"Indirect comment\" } , "
                        "  \"name\": \"d2_key.example.com\" , "
                        "  \"algorithm\": \"hmac-md5\" , "
                        "  \"secret\": \"LSWXnfkKZjdPJI5QxlpnfQ==\" "
                        "}"
                        "],"
                        "\"forward-ddns\" : {"
                        "\"ddns-domains\": [ "
                        "{ \"comment\": \"A DDNS domain\" , "
                        "  \"name\": \"example.com\" , "
                        "  \"key-name\": \"d2_key.example.com\" , "
                        "  \"dns-servers\" : [ "
                        "  { \"ip-address\": \"127.0.0.1\" , "
                        "    \"user-context\": { \"version\": 1 } } "
                        "  ] } "
                        "] } }";

    // Should parse without error.
    RUN_CONFIG_OK(config);

    // Check the D2 context.
    D2CfgContextPtr d2_context;
    ASSERT_NO_THROW(d2_context = cfg_mgr_->getD2CfgContext());
    ASSERT_TRUE(d2_context);

    // Check global user context.
    ConstElementPtr ctx = d2_context->getContext();
    ASSERT_TRUE(ctx);
    ASSERT_EQ(1, ctx->size());
    ASSERT_TRUE(ctx->get("comment"));
    EXPECT_EQ("\"D2 config\"", ctx->get("comment")->str());

    // Check control socket.
    ConstElementPtr ctrl_sock = d2_context->getControlSocketInfo();
    ASSERT_TRUE(ctrl_sock);
    ASSERT_TRUE(ctrl_sock->get("user-context"));
    EXPECT_EQ("{ \"comment\": \"Control channel\" }",
              ctrl_sock->get("user-context")->str());

    // Check TSIG keys.
    TSIGKeyInfoMapPtr keys = d2_context->getKeys();
    ASSERT_TRUE(keys);
    ASSERT_EQ(1, keys->size());

    // Check the TSIG key.
    TSIGKeyInfoMap::iterator gotkey = keys->find("d2_key.example.com");
    ASSERT_TRUE(gotkey != keys->end());
    TSIGKeyInfoPtr key = gotkey->second;
    ASSERT_TRUE(key);

    // Check the TSIG key user context.
    ConstElementPtr key_ctx = key->getContext();
    ASSERT_TRUE(key_ctx);
    ASSERT_EQ(1, key_ctx->size());
    ASSERT_TRUE(key_ctx->get("comment"));
    EXPECT_EQ("\"Indirect comment\"", key_ctx->get("comment")->str());

    // Check the forward manager.
    DdnsDomainListMgrPtr mgr = d2_context->getForwardMgr();
    ASSERT_TRUE(mgr);
    EXPECT_EQ("forward-ddns", mgr->getName());
    DdnsDomainMapPtr domains = mgr->getDomains();
    ASSERT_TRUE(domains);
    ASSERT_EQ(1, domains->size());

    // Check the DDNS domain.
    DdnsDomainMap::iterator gotdns = domains->find("example.com");
    ASSERT_TRUE(gotdns != domains->end());
    DdnsDomainPtr domain = gotdns->second;
    ASSERT_TRUE(domain);

    // Check the DNS server.
    DnsServerInfoStoragePtr servers = domain->getServers();
    ASSERT_TRUE(servers);
    ASSERT_EQ(1, servers->size());
    DnsServerInfoPtr server = (*servers)[0];
    ASSERT_TRUE(server);

    // Check the DNS server user context.
    ConstElementPtr srv_ctx = server->getContext();
    ASSERT_TRUE(srv_ctx);
    ASSERT_EQ(1, srv_ctx->size());
    ASSERT_TRUE(srv_ctx->get("version"));
    EXPECT_EQ("1", srv_ctx->get("version")->str());
}

} // end of anonymous namespace
