// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <yang/translator_option_data.h>

#include <boost/scoped_ptr.hpp>
#include <gtest/gtest.h>
#include <sstream>

using namespace std;
using namespace isc;
using namespace isc::data;
using namespace isc::yang;

namespace {

// Test get empty option data list.
TEST(TranslatorOptionDataListTest, getEmpty) {
    // Get a translator option data list object to play with.
    S_Connection conn(new Connection("translator option data list unittests"));
    S_Session sess(new Session(conn, SR_DS_CANDIDATE));
    boost::scoped_ptr<TranslatorOptionDataList> todl_obj;

    // Use the ad hoc model.
    const string& model = "kea-dhcp4-server";
    EXPECT_NO_THROW(todl_obj.reset(new TranslatorOptionDataList(sess, model)));

    // Get the option data list and checks it is empty.
    const string& xpath = "/kea-dhcp4-server:config/option-data-list";
    ConstElementPtr options;
    EXPECT_NO_THROW(options = todl_obj->getOptionDataList(xpath));
    ASSERT_TRUE(options);
    ASSERT_EQ(Element::list, options->getType());
    EXPECT_EQ(0, options->size());
}

// Test get one option data.
TEST(TranslatorOptionDataListTest, get) {
    // Get a translator option data list object to play with.
    S_Connection conn(new Connection("translator option data list unittests"));
    S_Session sess(new Session(conn, SR_DS_CANDIDATE));
    boost::scoped_ptr<TranslatorOptionDataList> todl_obj;

    // Use the ad hoc model.
    const string& model = "kea-dhcp6-server";
    EXPECT_NO_THROW(todl_obj.reset(new TranslatorOptionDataList(sess, model)));

    // Create the option code 100.
    const string& xpath = "/kea-dhcp6-server:config/option-data-list";
    const string& xoption = xpath + "/option-data[code='100'][space='dns']";
    const string& xformat = xoption + "/csv-format";
    const string& xdata = xoption + "/data";
    const string& xsend = xoption + "/always-send";
    S_Val s_false(new Val(false));
    ASSERT_NO_THROW(sess->set_item(xformat.c_str(), s_false));
    S_Val s_data(new Val("12121212"));
    ASSERT_NO_THROW(sess->set_item(xdata.c_str(), s_data));
    ASSERT_NO_THROW(sess->set_item(xsend.c_str(), s_false));
    
    // Get the option data.
    ConstElementPtr option;
    EXPECT_NO_THROW(option = todl_obj->getOptionData(xoption));
    ASSERT_TRUE(option);
    EXPECT_EQ("{ \"always-send\": false, \"code\": 100, \"csv-format\": false, \"data\": \"12121212\", \"space\": \"dns\" }",
              option->str());

    // Get the option data list.
    ConstElementPtr options;
    EXPECT_NO_THROW(options = todl_obj->getOptionDataList(xpath));
    ASSERT_TRUE(options);
    ASSERT_EQ(Element::list, options->getType());
    EXPECT_EQ(1, options->size());
    EXPECT_TRUE(option->equals(*options->get(0)));
}

// Test set empty option data list.
TEST(TranslatorOptionDataListTest, setEmpty) {
    // Get a translator option data list object to play with.
    S_Connection conn(new Connection("translator option data list unittests"));
    S_Session sess(new Session(conn, SR_DS_CANDIDATE));
    boost::scoped_ptr<TranslatorOptionDataList> todl_obj;

    // Use the ad hoc model.
    const string& model = "kea-dhcp4-server";
    EXPECT_NO_THROW(todl_obj.reset(new TranslatorOptionDataList(sess, model)));

    // Set empty list.
    const string& xpath = "/kea-dhcp4-server:config/option-data-list";
    ConstElementPtr options = Element::createList();
    EXPECT_NO_THROW(todl_obj->setOptionDataList(xpath, options));

    // Get it back.
    options.reset();
    EXPECT_NO_THROW(options = todl_obj->getOptionDataList(xpath));
    ASSERT_TRUE(options);
    EXPECT_EQ(0, options->size());
}

// Test set an option data.
TEST(TranslatorOptionDataListTest, set) {
    // Get a translator option data list object to play with.
    S_Connection conn(new Connection("translator option data list unittests"));
    S_Session sess(new Session(conn, SR_DS_CANDIDATE));
    boost::scoped_ptr<TranslatorOptionDataList> todl_obj;

    // Use the ad hoc model.
    const string& model = "kea-dhcp6-server";
    EXPECT_NO_THROW(todl_obj.reset(new TranslatorOptionDataList(sess, model)));

    // Set one option data.
    const string& xpath = "/kea-dhcp6-server:config/option-data-list";
    ElementPtr options = Element::createList();
    ElementPtr option = Element::createMap();
    option->set("code", Element::create(100));
    option->set("space", Element::create(string("dns")));
    option->set("csv-format", Element::create(false));
    option->set("data", Element::create(string("12121212")));
    option->set("always-send", Element::create(false));
    options->add(option);
    EXPECT_NO_THROW(todl_obj->setOptionDataList(xpath, options));

    // Get it back.
    ConstElementPtr got;
    EXPECT_NO_THROW(got = todl_obj->getOptionDataList(xpath));
    ASSERT_TRUE(got);
    ASSERT_EQ(1, got->size());
    EXPECT_TRUE(option->equals(*got->get(0)));

    // Check the tree representation.
    S_Tree tree;
    EXPECT_NO_THROW(tree = sess->get_subtree("/kea-dhcp6-server:config"));
    ASSERT_TRUE(tree);
    string expected =
        "kea-dhcp6-server:config (container)\n"
        " |\n"
        " -- option-data-list (container)\n"
        "     |\n"
        "     -- option-data (list instance)\n"
        "         |\n"
        "         -- code = 100\n"
        "         |\n"
        "         -- space = dns\n"
        "         |\n"
        "         -- data = 12121212\n"
        "         |\n"
        "         -- csv-format = false\n"
        "         |\n"
        "         -- always-send = false\n";
    EXPECT_EQ(expected, tree->to_string(100));
}

}; // end of anonymous namespace
