// Copyright (C) 2018-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <testutils/io_utils.h>
#include <testutils/user_context_utils.h>
#include <yang/translator_config.h>
#include <yang/yang_models.h>
#include <yang/tests/json_configs.h>
#include <yang/tests/yang_configs.h>
#include <yang/tests/sysrepo_setup.h>

#include <boost/algorithm/string.hpp>

#include <gtest/gtest.h>

#include <iostream>

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
    virtual ~ConfigTest() = default;

    void SetUp() override {
        SysrepoSetup::cleanSharedMemory();
        connection_ = std::make_shared<Connection>();
        session_.reset(new Session(connection_, SR_DS_CANDIDATE));
        translator_.reset(new TranslatorBasic(session_, model_));
        cleanModelData();
    }

    void TearDown() override {
        cleanModelData();
        translator_.reset();
        session_.reset();
        connection_.reset();
        SysrepoSetup::cleanSharedMemory();
    }

    void cleanModelData() {
        std::string toplevel_node("config");
        if (model_ == IETF_DHCPV6_SERVER) {
            toplevel_node = "server";
        }
        translator_->delItem("/" + model_ + ":" + toplevel_node);
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
    void load(ConstElementPtr json) {
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
        expected = Element::fromJSON(config);
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

    std::unique_ptr<TranslatorBasic> translator_;
};

struct ConfigTestKeaV4 : ConfigTest {
    ConfigTestKeaV4() {
        model_ = KEA_DHCP4_SERVER;
    }
};
struct ConfigTestKeaV6 : ConfigTest {
    ConfigTestKeaV6() {
        model_ = KEA_DHCP6_SERVER;
    }
};
struct ConfigTestIetfV6 : ConfigTest {
    ConfigTestIetfV6() {
        model_ = IETF_DHCPV6_SERVER;
    }
};

// Check empty config with ietf-dhcpv6-server model.
TEST_F(ConfigTestIetfV6, emptyIetf6) {
    YRTree tree;
    ASSERT_NO_THROW_LOG(load(tree));
    EXPECT_TRUE(verify(tree));

    ConstElementPtr json = Element::fromJSON(emptyJson6);
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

    ConstElementPtr json = Element::fromJSON(emptyJson4);
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

    ConstElementPtr json = Element::fromJSON(emptyJson6);
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

    EXPECT_FALSE(validate());
}

// Check subnet with a pool and option data lists with
// kea-dhcp4-server:config model.
TEST_F(ConfigTestKeaV4, subnetOptionsKeaDhcp4) {
    ASSERT_NO_THROW_LOG(load(subnetOptionsTreeKeaDhcp4));
    EXPECT_TRUE(verify(subnetOptionsJson4));

    resetSession();

    ASSERT_NO_THROW_LOG(load(subnetOptionsJson4));
    EXPECT_TRUE(verify(subnetOptionsTreeKeaDhcp4));

    EXPECT_TRUE(validate());
}

// Check subnet with a pool and option data lists with
// kea-dhcp6-server:config model.
TEST_F(ConfigTestKeaV6, subnetOptionsKeaDhcp6) {
    ASSERT_NO_THROW_LOG(load(subnetOptionsTreeKeaDhcp6));
    EXPECT_TRUE(verify(subnetOptionsJson6));

    resetSession();

    ASSERT_NO_THROW_LOG(load(subnetOptionsJson6));
    EXPECT_TRUE(verify(subnetOptionsTreeKeaDhcp6));

    EXPECT_TRUE(validate());
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

    // If this validation fails, make sure you have the model *and its
    // dependencies* are installed. Note when you install ietf-dhcpv6-server
    // module, its dependencies are semi-installed, which is not sufficient.
    // This can be detected in output of sysrepoctl -l.
    // Note the ietf-interfaces module. The conformance status must be
    // "installed". "implemented" (installed as dependency) is not enough.
    EXPECT_TRUE(validate());
}

// Check Kea4 example files.
TEST_F(ConfigTestKeaV4, examples4) {
    vector<string> examples = {
        "advanced.json",
        "all-keys-netconf.json",
        "backends.json",
        "cassandra.json",
        "classify.json",
        "classify2.json",
        "comments.json",
        "config-backend.json",
        "dhcpv4-over-dhcpv6.json",
        // "global-reservations.json" removed for #1405
        "ha-load-balancing-primary.json",
        "hooks.json",
        "hooks-radius.json",
        "leases-expiration.json",
        "multiple-options.json",
        "mysql-reservations.json",
        "pgsql-reservations.json",
        // "reservations.json" removed for #1405
        "several-subnets.json",
        // "shared-network.json" removed for #1405
        "single-subnet.json",
        // "with-ddns.json" removed for #35
    };
    for (string file : examples) {
        resetSession();
        string path = string(CFG_EXAMPLES) + "/kea4/" + file;
        cout << "Testing file " << path << endl;
        ConstElementPtr json;
        ASSERT_NO_THROW_LOG(json = loadFile(path));
        json = isc::test::moveComments(json);
        EXPECT_TRUE(verify(json));
        EXPECT_TRUE(validate());
    }
}

// Check Kea6 example files.
TEST_F(ConfigTestKeaV6, examples6) {
    vector<string> examples = {
        "advanced.json",
        "all-keys-netconf.json",
        "backends.json",
        "cassandra.json",
        "classify.json",
        "classify2.json",
        "comments.json",
        "config-backend.json",
        "dhcpv4-over-dhcpv6.json",
        "duid.json",
        // "global-reservations.json" removed for #1405
        "ha-hot-standby.json",
        "hooks.json",
        "iPXE.json",
        "leases-expiration.json",
        "multiple-options.json",
        "mysql-reservations.json",
        "pgsql-reservations.json",
        // "reservations.json" removed for #1405
        "several-subnets.json",
        // "shared-network.json" removed for #1405
        "simple.json",
        "softwire46.json",
        "stateless.json",
        "tee-times.json",
        // "with-ddns.json" removed for #35
    };
    for (string file : examples) {
        resetSession();
        string path = string(CFG_EXAMPLES) + "/kea6/" + file;
        cout << "Testing file " << path << endl;
        ConstElementPtr json;
        ASSERT_NO_THROW_LOG(json = loadFile(path));
        json = isc::test::moveComments(json);
        EXPECT_TRUE(verify(json));
        EXPECT_TRUE(validate());
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
