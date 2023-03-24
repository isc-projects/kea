// Copyright (C) 2018-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <gtest/gtest.h>

#include <testutils/io_utils.h>
#include <testutils/user_context_utils.h>
#include <yang/tests/json_configs.h>
#include <yang/tests/sysrepo_setup.h>
#include <yang/tests/yang_configs.h>
#include <yang/translator_config.h>
#include <yang/yang_models.h>

#include <iostream>
#include <vector>

#include <boost/algorithm/string.hpp>

using namespace std;
using namespace isc;
using namespace isc::data;
using namespace isc::yang;
using namespace isc::yang::test;
using namespace sysrepo;

namespace {

/// @brief Return the difference between two strings
///
/// Use the gtest >= 1.8.0 tool which builds the difference between
/// two vectors of lines.
///
/// @param left left string
/// @param right right string
/// @return the unified diff between left and right
#ifdef HAVE_CREATE_UNIFIED_DIFF
string generateDiff(string left, string right) {
    vector<string> left_lines;
    boost::split(left_lines, left, boost::is_any_of("\n"));
    vector<string> right_lines;
    boost::split(right_lines, right, boost::is_any_of("\n"));
    using namespace testing::internal;
    return (edit_distance::CreateUnifiedDiff(left_lines, right_lines));
}
#else
string generateDiff(string, string) {
    return ("");
}
#endif

/// @brief Test Fixture class for Yang <-> JSON configs.
class ConfigTest : public ::testing::Test {
public:
    ConfigTest() : session_(Connection{}.sessionStart()) {
        session_.switchDatastore(Datastore::Candidate);
    }
    virtual ~ConfigTest() = default;

    void SetUp() override {
        translator_.reset(new Translator(session_, model_));
        cleanModelData();
    }

    void TearDown() override {
        cleanModelData();
        translator_.reset();
        SysrepoSetup::cleanSharedMemory();
    }

    void cleanModelData() {
        string toplevel_node("config");
        if (model_ == IETF_DHCPV6_SERVER) {
            toplevel_node = "server";
        }
        translator_->deleteItem("/" + model_ + ":" + toplevel_node);
    }

    /// @brief Reset session.
    void resetSession() {
        SetUp();
    }

    /// @brief Loads YANG configuration from specified tree.
    ///
    /// @param tree The Yang tree to load.
    void load(const YRTree& tree) {
        YangRepr repr(model_);
        repr.set(tree, session_);
    }

    /// @brief Loads JSON configuration from specified Element tree.
    ///
    /// @param json The JSON tree to load.
    void load(ElementPtr json) {
        TranslatorConfig tc(session_, model_);
        tc.setConfig(json);
    }

    /// @brief Load a cofiguration from a string containing JSON.
    ///
    /// @param config The JSON tree to load in textual format.
    void load(const string& config) {
        ElementPtr json;
        ASSERT_NO_THROW_LOG(json = Element::fromJSON(config));
        load(json);
    }

    /// @brief Load a configuration from JSON file.
    ///
    /// @param filename The name of the JSON file to load,
    ConstElementPtr loadFile(const string& filename) {
        string decommented = isc::test::decommentJSONfile(filename);
        ElementPtr json = Element::fromJSONFile(decommented, true);
        ::remove(decommented.c_str());
        load(json);
        return (json);
    }

    /// @brief Returns YANG tree configuration.
    YRTree getYang() {
        YangRepr repr(model_);
        return (repr.get(session_));
    }

    /// @brief Returns configuration in JSON (translated by TranslatorConfig)
    ConstElementPtr getJSON() {
        TranslatorConfig tc(session_, model_);
        return (tc.getConfig());
    }

    /// @brief Retrieves configuration as text (in pretty JSON format).
    string getText() {
        return (isc::data::prettyPrint(getJSON()));
    }

    /// @brief Verify Yang.
    ///
    /// @param expected The expected Yang tree.
    bool verify(const YRTree& expected) {
        YangRepr repr(model_);
        return (repr.verify(expected, session_, cerr));
    }

    /// @brief Verify JSON.
    ///
    /// @param expected The expected JSON tree.
    bool verify(ConstElementPtr expected) {
        TranslatorConfig tc(session_, model_);
        ConstElementPtr content = tc.getConfig();
        if (isEquivalent(expected, content)) {
            return (true);
        }
        string wanted = prettyPrint(expected);
        string got = prettyPrint(content);
        cerr << "Expected:\n" << wanted << "\n"
             << "Actual:\n" << got
#ifdef HAVE_CREATE_UNIFIED_DIFF
             << "\nDiff:\n" << generateDiff(wanted, got)
#endif
             << "\n";
        return (false);
    }

    /// @brief Verify JSON.
    ///
    /// @param expected The expected JSON tree in textual format.
    bool verify(const string& config) {
        ConstElementPtr expected;
        expected = Element::fromJSON(config);
        return (verify(expected));
    }

    /// @brief The model.
    string model_;

    /// @brief The sysrepo session.
    Session session_;

    unique_ptr<Translator> translator_;
};  // ConfigTest

struct ConfigTestKeaV4 : ConfigTest {
    ConfigTestKeaV4() {
        model_ = KEA_DHCP4_SERVER;
    }
};  // ConfigTestKeaV4
struct ConfigTestKeaV6 : ConfigTest {
    ConfigTestKeaV6() {
        model_ = KEA_DHCP6_SERVER;
    }
};  // ConfigTestKeaV6
struct ConfigTestIetfV6 : ConfigTest {
    ConfigTestIetfV6() {
        model_ = IETF_DHCPV6_SERVER;
    }
};  // ConfigTestIetfV6

// Check empty config with ietf-dhcpv6-server model.
TEST_F(ConfigTestIetfV6, emptyIetf6) {
    YRTree tree;
    ASSERT_NO_THROW_LOG(load(tree));
    EXPECT_TRUE(verify(tree));

    ElementPtr json = Element::fromJSON(emptyJson6);
    EXPECT_TRUE(verify(json));
    ASSERT_NO_THROW_LOG(load(json));
    EXPECT_TRUE(verify(emptyJson6));
    EXPECT_TRUE(verify(tree));
}

// Check empty config with kea-dhcp4-server:config model.
TEST_F(ConfigTestKeaV4, emptyKeaDhcp4) {
    YRTree tree;
    ASSERT_NO_THROW_LOG(load(tree));
    EXPECT_TRUE(verify(emptyTreeKeaDhcp4));

    ElementPtr json = Element::fromJSON(emptyJson4);
    EXPECT_TRUE(verify(json));
    ASSERT_NO_THROW_LOG(load(json));
    EXPECT_TRUE(verify(emptyJson4));
    EXPECT_TRUE(verify(emptyTreeKeaDhcp4));
}

// Check empty config with kea-dhcp6-server:config model.
TEST_F(ConfigTestKeaV6, emptyKeaDhcp6) {
    YRTree tree;
    ASSERT_NO_THROW_LOG(load(tree));
    EXPECT_TRUE(verify(emptyTreeKeaDhcp6));

    ElementPtr json = Element::fromJSON(emptyJson6);
    EXPECT_TRUE(verify(json));
    ASSERT_NO_THROW_LOG(load(json));
    EXPECT_TRUE(verify(emptyJson6));
    EXPECT_TRUE(verify(emptyTreeKeaDhcp6));
}

// Check subnet with two pools with ietf-dhcpv6-server model.
// Validation will fail because the current model has a vendor-info
// container with a mandatory ent-num leaf and no presence flag,
// and of course the candidate YANG tree has nothing for this.
TEST_F(ConfigTestIetfV6, subnetTwoPoolsIetf6) {
    ASSERT_NO_THROW_LOG(load(subnetTwoPoolsTreeIetf6));
    EXPECT_TRUE(verify(subnetTwoPoolsJson6));

    resetSession();

    ASSERT_NO_THROW_LOG(load(subnetTwoPoolsJson6));
    EXPECT_TRUE(verify(subnetTwoPoolsTreeIetf6));
}

// Check subnet with a pool and option data lists with
// kea-dhcp4-server:config model.
TEST_F(ConfigTestKeaV4, subnetOptionsKeaDhcp4) {
    ASSERT_NO_THROW_LOG(load(subnetOptionsTreeKeaDhcp4));
    EXPECT_TRUE(verify(subnetOptionsJson4));

    resetSession();

    ASSERT_NO_THROW_LOG(load(subnetOptionsJson4));
    EXPECT_TRUE(verify(subnetOptionsTreeKeaDhcp4));
}

// Check subnet with a pool and option data lists with
// kea-dhcp6-server:config model.
TEST_F(ConfigTestKeaV6, subnetOptionsKeaDhcp6) {
    ASSERT_NO_THROW_LOG(load(subnetOptionsTreeKeaDhcp6));
    EXPECT_TRUE(verify(subnetOptionsJson6));

    resetSession();

    ASSERT_NO_THROW_LOG(load(subnetOptionsJson6));
    EXPECT_TRUE(verify(subnetOptionsTreeKeaDhcp6));
}

// Check with timers.
TEST_F(ConfigTestIetfV6, subnetTimersIetf6) {
    ASSERT_NO_THROW_LOG(load(subnetTimersIetf6));
    EXPECT_TRUE(verify(subnetTimersJson6));

    resetSession();

    ASSERT_NO_THROW_LOG(load(subnetTimersJson6));
    EXPECT_TRUE(verify(subnetTimersIetf6));
}

// Check a ietf-dhcpv6-server configuration which validates.
TEST_F(ConfigTestIetfV6, validateIetf6) {
    ASSERT_NO_THROW_LOG(load(validTreeIetf6));
    EXPECT_TRUE(verify(validTreeIetf6));
}

// Check Kea4 example files.
TEST_F(ConfigTestKeaV4, examples4) {
    vector<string> examples = {
        "advanced.json",
        "all-keys-netconf.json",
        "all-options.json",
        "backends.json",
        "classify.json",
        "classify2.json",
        "comments.json",
        "config-backend.json",
        "dhcpv4-over-dhcpv6.json",
        "global-reservations.json",
        "ha-load-balancing-server1-mt-with-tls.json",
        "ha-load-balancing-server2-mt.json",
        "hooks.json",
        "hooks-radius.json",
        "leases-expiration.json",
        "multiple-options.json",
        "mysql-reservations.json",
        "pgsql-reservations.json",
        "reservations.json",
        "several-subnets.json",
        "shared-network.json",
        "single-subnet.json",
        "vendor-specific.json",
        "vivso.json",
        // "with-ddns.json", commented out for ddns-ttl-percent
    };
    for (string file : examples) {
        resetSession();
        string path = string(CFG_EXAMPLES) + "/kea4/" + file;
        SCOPED_TRACE("\n* Tested file: " + path);
        ConstElementPtr json;
        ASSERT_NO_THROW_LOG(json = loadFile(path));
        json = isc::test::moveComments(json);
        EXPECT_TRUE(verify(json));
    }
}

// Check Kea6 example files.
TEST_F(ConfigTestKeaV6, examples6) {
    vector<string> examples = {
        "advanced.json",
        "all-keys-netconf.json",
        "all-options.json",
        "backends.json",
        "classify.json",
        "classify2.json",
        "comments.json",
        "config-backend.json",
        "dhcpv4-over-dhcpv6.json",
        "duid.json",
        "global-reservations.json",
        "ha-hot-standby-server1-with-tls.json",
        "ha-hot-standby-server2.json",
        "hooks.json",
        "iPXE.json",
        "leases-expiration.json",
        "multiple-options.json",
        "mysql-reservations.json",
        "pgsql-reservations.json",
        "reservations.json",
        "several-subnets.json",
        "shared-network.json",
        "simple.json",
        "softwire46.json",
        "stateless.json",
        "tee-times.json",
        // "with-ddns.json", commented out for ddns-ttl-percent
    };
    for (string file : examples) {
        resetSession();
        string path = string(CFG_EXAMPLES) + "/kea6/" + file;
        SCOPED_TRACE("\n* Tested file: " + path);
        ConstElementPtr json;
        ASSERT_NO_THROW_LOG(json = loadFile(path));
        json = isc::test::moveComments(json);
        EXPECT_TRUE(verify(json));
    }
}

// Check the example in the design document.
TEST_F(ConfigTestIetfV6, designExample) {
    ASSERT_NO_THROW_LOG(load(designExampleTree));
    EXPECT_TRUE(verify(designExampleJson));

    resetSession();

    ASSERT_NO_THROW_LOG(load(designExampleJson));
    EXPECT_TRUE(verify(designExampleTree));
}

}  // namespace
