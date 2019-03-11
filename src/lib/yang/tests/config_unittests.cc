// Copyright (C) 2018-2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <testutils/io_utils.h>
#include <testutils/user_context_utils.h>
#include <yang/translator_config.h>
#include <yang/yang_models.h>
#include <yang/tests/yang_configs.h>
#include <yang/tests/json_configs.h>
#include <boost/algorithm/string.hpp>
#include <gtest/gtest.h>
#include <iostream>

using namespace std;
using namespace isc;
using namespace isc::data;
using namespace isc::yang;
using namespace isc::yang::test;
#ifndef HAVE_PRE_0_7_6_SYSREPO
using namespace sysrepo;
#endif

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
std::string generateDiff(std::string left, std::string right) {
    std::vector<std::string> left_lines;
    boost::split(left_lines, left, boost::is_any_of("\n"));
    std::vector<std::string> right_lines;
    boost::split(right_lines, right, boost::is_any_of("\n"));
    using namespace testing::internal;
    return (edit_distance::CreateUnifiedDiff(left_lines, right_lines));
}
#else
std::string generateDiff(std::string, std::string) {
    return ("");
}
#endif


/// @brief Test Fixture class for Yang <-> JSON configs.
class ConfigTest : public ::testing::Test {
public:

    /// @brief Constructor.
    ConfigTest() {
        createSession();
    }

    /// @brief Virtual destructor.
    virtual ~ConfigTest() {
        session_.reset();
        connection_.reset();
        model_.clear();
    }

    /// @brief Set model.
    ///
    /// @param model The model name.
    void setModel(const string model) {
        model_ = model;
    }

    /// @brief Create session.
    void createSession() {
        connection_.reset(new Connection("configs unittests"));
        session_.reset(new Session(connection_, SR_DS_CANDIDATE));
    }

    /// @brief Reset session.
    void resetSession() {
        session_.reset(new Session(connection_, SR_DS_CANDIDATE));
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
    void load(ConstElementPtr json) {
        TranslatorConfig tc(session_, model_);
        tc.setConfig(json);
    }

    /// @brief Load a cofiguration from a string containing JSON.
    ///
    /// @param config The JSON tree to load in textual format.
    void load(const string& config) {
        ConstElementPtr json;
        ASSERT_NO_THROW(json = Element::fromJSON(config));
        load(json);
    }

    /// @brief Load a configuration from JSON file.
    ///
    /// @param filename The name of the JSON file to load,
    ConstElementPtr loadFile(const string& filename) {
        string decommented = isc::test::decommentJSONfile(filename);
        ConstElementPtr json = Element::fromJSONFile(decommented, true);
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
        expected= Element::fromJSON(config);
        return (verify(expected));
    }

    /// @brief Validate.
    ///
    /// @note A tree must be loaded first.
    ///
    bool validate() {
        YangRepr repr(model_);
        return (repr.validate(session_, cerr));
    }

    /// @brief The model.
    string model_;

    /// @brief The sysrepo connection.
    S_Connection connection_;

    /// @brief The sysrepo session.
    S_Session session_;
};

// Check empty config with ietf-dhcpv6-server model.
TEST_F(ConfigTest, emptyIetf6) {
    // First set the model.
    setModel(IETF_DHCPV6_SERVER);

    YRTree tree;
    ASSERT_NO_THROW(load(tree));
    EXPECT_TRUE(verify(tree));

    ConstElementPtr json = Element::fromJSON(emptyJson6);
    EXPECT_TRUE(verify(json));
    ASSERT_NO_THROW(load(json));
    EXPECT_TRUE(verify(emptyJson6));
    EXPECT_TRUE(verify(tree));
}

// Check empty config with kea-dhcp4-server:config model.
TEST_F(ConfigTest, emptyKeaDhcp4) {
    // First set the model.
    setModel(KEA_DHCP4_SERVER);

    YRTree tree;
    ASSERT_NO_THROW(load(tree));
    EXPECT_TRUE(verify(tree));

    ConstElementPtr json = Element::fromJSON(emptyJson4);
    EXPECT_TRUE(verify(json));
    ASSERT_NO_THROW(load(json));
    EXPECT_TRUE(verify(emptyJson4));
    EXPECT_TRUE(verify(tree));
}

// Check empty config with kea-dhcp6-server:config model.
TEST_F(ConfigTest, emptyKeaDhcp6) {
    // First set the model.
    setModel(KEA_DHCP6_SERVER);

    YRTree tree;
    ASSERT_NO_THROW(load(tree));
    EXPECT_TRUE(verify(tree));

    ConstElementPtr json = Element::fromJSON(emptyJson6);
    EXPECT_TRUE(verify(json));
    ASSERT_NO_THROW(load(json));
    EXPECT_TRUE(verify(emptyJson6));
    EXPECT_TRUE(verify(tree));
}

// Check subnet with two pools with ietf-dhcpv6-server model.
// Validation will fail because the current model has a vendor-info
// container with a mandatory ent-num leaf and no presence flag,
// and of course the candidate YANG tree has nothing for this.
TEST_F(ConfigTest, subnetTwoPoolsIetf6) {
    // First set the model.
    setModel(subnetTwoPoolsModelIetf6);

    ASSERT_NO_THROW(load(subnetTwoPoolsTreeIetf6));
    EXPECT_TRUE(verify(subnetTwoPoolsJson6));

    resetSession();

    ASSERT_NO_THROW(load(subnetTwoPoolsJson6));
    EXPECT_TRUE(verify(subnetTwoPoolsTreeIetf6));

    cout << "validation is expected to fail: please ignore messages" << endl;
    EXPECT_FALSE(validate());
}

// Check subnet with a pool and option data lists with
// kea-dhcp4-server:config model.
TEST_F(ConfigTest, subnetOptionsKeaDhcp4) {
    // First set the model.
    setModel(subnetOptionsModelKeaDhcp4);

    ASSERT_NO_THROW(load(subnetOptionsTreeKeaDhcp4));
    EXPECT_TRUE(verify(subnetOptionsJson4));

    resetSession();

    ASSERT_NO_THROW(load(subnetOptionsJson4));
    EXPECT_TRUE(verify(subnetOptionsTreeKeaDhcp4));

    EXPECT_TRUE(validate());
}

// Check subnet with a pool and option data lists with
// kea-dhcp6-server:config model.
TEST_F(ConfigTest, subnetOptionsKeaDhcp6) {
    // First set the model.
    setModel(subnetOptionsModelKeaDhcp6);

    ASSERT_NO_THROW(load(subnetOptionsTreeKeaDhcp6));
    EXPECT_TRUE(verify(subnetOptionsJson6));

    resetSession();

    ASSERT_NO_THROW(load(subnetOptionsJson6));
    EXPECT_TRUE(verify(subnetOptionsTreeKeaDhcp6));

    EXPECT_TRUE(validate());
}

// Check with timers.
TEST_F(ConfigTest, subnetTimersIetf6) {
    // First set the model.
    setModel(subnetTimersModel);

    ASSERT_NO_THROW(load(subnetTimersIetf6));
    EXPECT_TRUE(verify(subnetTimersJson6));

    resetSession();

    ASSERT_NO_THROW(load(subnetTimersJson6));
    EXPECT_TRUE(verify(subnetTimersIetf6));
}

// Check a ietf-dhcpv6-server configuration which validates.
TEST_F(ConfigTest, validateIetf6) {
    // First set the model.
    setModel(validModelIetf6);

    ASSERT_NO_THROW(load(validTreeIetf6));
    EXPECT_TRUE(verify(validTreeIetf6));

    EXPECT_TRUE(validate());
}

// Check Kea4 example files.
TEST_F(ConfigTest, examples4) {
    // First set the model.
    setModel(KEA_DHCP4_SERVER);

    vector<string> examples = {
        "advanced.json",
        "all-keys-stable.json",
        "backends.json",
        "cassandra.json",
        "classify.json",
        "classify2.json",
        "comments.json",
        "dhcpv4-over-dhcpv6.json",
        "global-reservations.json",
        "hooks.json",
        "leases-expiration.json",
        "multiple-options.json",
        "mysql-reservations.json",
        "pgsql-reservations.json",
        "reservations.json",
        "several-subnets.json",
        "shared-network.json",
        "single-subnet.json",
        "with-ddns.json"
    };
    for (string file : examples) {
        resetSession();
        string path = string(CFG_EXAMPLES) + "/kea4/" + file;
        cout << "Testing file " << path << endl;
        ConstElementPtr json;
        ASSERT_NO_THROW(json = loadFile(path));
        json = isc::test::moveComments(json);
        EXPECT_TRUE(verify(json));
        EXPECT_TRUE(validate());
    }
}

// Check Kea6 example files.
TEST_F(ConfigTest, examples6) {
    // First set the model.
    setModel(KEA_DHCP6_SERVER);

    vector<string> examples = {
        "advanced.json",
        "all-keys-stable.json",
        "backends.json",
        "cassandra.json",
        "classify.json",
        "classify2.json",
        "comments.json",
        "dhcpv4-over-dhcpv6.json",
        "duid.json",
        "global-reservations.json",
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
        "with-ddns.json"
    };
    for (string file : examples) {
        resetSession();
        string path = string(CFG_EXAMPLES) + "/kea6/" + file;
        cout << "Testing file " << path << endl;
        ConstElementPtr json;
        ASSERT_NO_THROW(json = loadFile(path));
        json = isc::test::moveComments(json);
        EXPECT_TRUE(verify(json));
        EXPECT_TRUE(validate());
    }
}

// Check the example in the design document.
TEST_F(ConfigTest, designExample) {
    // First set the model.
    setModel(designExampleModel);

    ASSERT_NO_THROW(load(designExampleTree));
    EXPECT_TRUE(verify(designExampleJson));

    resetSession();

    ASSERT_NO_THROW(load(designExampleJson));
    EXPECT_TRUE(verify(designExampleTree));
}

}; // end of anonymous namespace
