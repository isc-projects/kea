// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <config/config_ctl_info.h>
#include <exceptions/exceptions.h>

#include <gtest/gtest.h>

#include <sstream>
#include <iostream>

using namespace isc::config;
using namespace isc::data;

// Verifies initializing via an access string and unparsing into elements
// We just test basic unparsing, as more rigorous testing is done in
// libkea-db testing which ConfibDBInfo uses.
TEST(ConfigDbInfo, basicOperation) {
    ConfigDbInfo db;
    std::string access = "type=mysql user=tom password=terrific";
    std::string access_json = "{\n"
        " \"type\":\"mysql\", \n"
        " \"user\":\"tom\", \n"
        " \"password\":\"terrific\" \n"
        "} \n";

    // Convert the above configuration into Elements for comparison.
    ElementPtr exp_elems;
    ASSERT_NO_THROW(exp_elems = Element::fromJSON(access_json))
        << "test is broken";

    // Initialize the db from an the access string
    db.setAccessString(access);
    EXPECT_EQ(access, db.getAccessString());

    // Convert the db into Elements and make sure they are as expected.
    ElementPtr db_elems;
    ASSERT_NO_THROW(db_elems = db.toElement());
    EXPECT_TRUE(db_elems->equals(*exp_elems));
}

// Verify that db parameter values may be retrieved.
TEST(ConfigDbInfo, getParameterValue) {
    ConfigDbInfo db1;
    std::string access1 = "type=mysql name=keatest port=33 readonly=false";
    db1.setAccessString(access1);

    std::string value;
    bool found = false;

    // Should find "type"
    ASSERT_NO_THROW(found = db1.getParameterValue("type", value));
    EXPECT_TRUE(found);
    EXPECT_EQ("mysql", value);

    // Should find "name"
    ASSERT_NO_THROW(found = db1.getParameterValue("name", value));
    EXPECT_TRUE(found);
    EXPECT_EQ("keatest", value);

    // Should find "port"
    ASSERT_NO_THROW(found = db1.getParameterValue("port", value));
    EXPECT_TRUE(found);
    EXPECT_EQ("33", value);

    // Should find "readonly"
    ASSERT_NO_THROW(found = db1.getParameterValue("readonly", value));
    EXPECT_TRUE(found);
    EXPECT_EQ("false", value);

    // Should not find "bogus"
    ASSERT_NO_THROW(found = db1.getParameterValue("bogus", value));
    EXPECT_FALSE(found);
}

// Verify that db equality operators work correctly.
TEST(ConfigDbInfo, equalityOperators) {
    ConfigDbInfo db1;
    std::string access1 = "type=mysql user=tom password=terrific";
    ASSERT_NO_THROW(db1.setAccessString(access1));

    ConfigDbInfo db2;
    std::string access2 = "type=postgresql user=tom password=terrific";
    ASSERT_NO_THROW(db2.setAccessString(access2));

    // Verify that the two unequal dbs are in fact not equal.
    EXPECT_FALSE(db1.equals(db2));
    EXPECT_FALSE(db1 == db2);
    EXPECT_TRUE(db1 != db2);

    // Verify that the two equal dbs are in fact equal.
    db2.setAccessString(access1);
    EXPECT_TRUE(db1.equals(db2));
    EXPECT_TRUE(db1 == db2);
    EXPECT_FALSE(db1 != db2);
}

// Verifies the basic operations of ConfigControlInfo
TEST(ConfigControlInfo, basicOperation) {

    ConfigControlInfo ctl;
    // We should have no dbs in the list.
    EXPECT_EQ(0, ctl.getConfigDatabases().size());

    // We should be able to add two distinct, valid dbs
    std::string access_str1 = "type=mysql host=machine1.org";
    ASSERT_NO_THROW(ctl.addConfigDatabase(access_str1));

    std::string access_str2 = "type=postgresql host=machine2.org";
    ASSERT_NO_THROW(ctl.addConfigDatabase(access_str2));

    // We should fail on a duplicate db.
    ASSERT_THROW(ctl.addConfigDatabase(access_str1), isc::BadValue);

    // We should have two dbs in the list.
    const ConfigDbInfoList& db_list = ctl.getConfigDatabases();
    EXPECT_EQ(2, db_list.size());

    // Verify the dbs in the list are as we expect them to be.
    EXPECT_EQ (access_str1, db_list[0].getAccessString());
    EXPECT_EQ (access_str2, db_list[1].getAccessString());

    // Verify we can find dbs based on a property values.
    const ConfigDbInfo& db_info = ctl.findConfigDb("type", "mysql");
    EXPECT_FALSE(db_info == ConfigControlInfo::EMPTY_DB());
    EXPECT_EQ (access_str1, db_info.getAccessString());

    const ConfigDbInfo& db_info2 = ctl.findConfigDb("host", "machine2.org");
    EXPECT_FALSE(db_info2 == ConfigControlInfo::EMPTY_DB());
    EXPECT_EQ (access_str2, db_info2.getAccessString());

    // Verify not finding a db reutrns EMPTY_DB().
    const ConfigDbInfo& db_info3 = ctl.findConfigDb("type", "bogus");
    EXPECT_TRUE(db_info3 == ConfigControlInfo::EMPTY_DB());

    // Verify we can clear the list of dbs.
    ctl.clear();
    EXPECT_EQ(0, ctl.getConfigDatabases().size());
}
