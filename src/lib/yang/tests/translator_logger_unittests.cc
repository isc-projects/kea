// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <yang/translator_logger.h>

#include <boost/scoped_ptr.hpp>
#include <gtest/gtest.h>

using namespace std;
using namespace isc;
using namespace isc::data;
using namespace isc::yang;

namespace {

// Test get empty loggers.
TEST(TranslatorLoggersTest, getEmpty) {
    // Get a translator loggers object to play with.
    S_Connection conn(new Connection("translator loggeres unittests"));
    S_Session sess(new Session(conn, SR_DS_CANDIDATE));
    boost::scoped_ptr<TranslatorLoggers> tls_obj;

    // Use the ad hoc model.
    const string& model = "kea-dhcp4-server";
    EXPECT_NO_THROW(tls_obj.reset(new TranslatorLoggers(sess, model)));

    // Get empty.
    const string& xpath = "/kea-dhcp4-server:logging/loggers";
    ConstElementPtr loggers;
    EXPECT_NO_THROW(loggers = tls_obj->getLoggers(xpath));
    ASSERT_TRUE(loggers);
    EXPECT_EQ(0, loggers->size());
}

// Test get loggers.
TEST(TranslatorLoggersTest, get) {
    // Get a translator loggers object to play with.
    S_Connection conn(new Connection("translator loggeres unittests"));
    S_Session sess(new Session(conn, SR_DS_CANDIDATE));
    boost::scoped_ptr<TranslatorLoggers> tls_obj;

    // Use the ad hoc model.
    const string& model = "kea-dhcp6-server";
    EXPECT_NO_THROW(tls_obj.reset(new TranslatorLoggers(sess, model)));

    // Set a value.
    const string& xpath = "/kea-dhcp6-server:logging/loggers";
    const string& xlogger = xpath + "/logger[name='foo']";
    const string& xseverity = xlogger + "/severity";
    const string& xoption = xlogger + "/output-options/option[output='/bar']";
    const string& xmaxver = xoption + "/maxver";
    S_Val s_severity(new Val("WARN", SR_ENUM_T));
    EXPECT_NO_THROW(sess->set_item(xseverity.c_str(), s_severity));
    uint32_t max_ver = 10;
    S_Val s_maxver(new Val(max_ver, SR_UINT32_T));
    EXPECT_NO_THROW(sess->set_item(xmaxver.c_str(), s_maxver));

    // Get empty.
    ConstElementPtr loggers;
    EXPECT_NO_THROW(loggers = tls_obj->getLoggers(xpath));
    ASSERT_TRUE(loggers);
    ASSERT_EQ(1, loggers->size());
    ConstElementPtr logger = loggers->get(0);
    ASSERT_TRUE(logger);
    EXPECT_EQ(3, logger->size());
    ConstElementPtr name = logger->get("name");
    ASSERT_TRUE(name);
    ASSERT_EQ(Element::string, name->getType());
    EXPECT_EQ("foo", name->stringValue());
    ConstElementPtr severity = logger->get("severity");
    ASSERT_TRUE(severity);
    ASSERT_EQ(Element::string, severity->getType());
    EXPECT_EQ("WARN", severity->stringValue());
    ConstElementPtr options = logger->get("output_options");
    ASSERT_TRUE(options);
    ASSERT_EQ(1, options->size());
    ConstElementPtr option = options->get(0);
    ASSERT_TRUE(option);
    EXPECT_EQ(2, option->size());
    ConstElementPtr output = option->get("output");
    ASSERT_TRUE(output);
    ASSERT_EQ(Element::string, output->getType());
    EXPECT_EQ("/bar", output->stringValue());
    ConstElementPtr maxver = option->get("maxver");
    ASSERT_TRUE(maxver);
    ASSERT_EQ(Element::integer, maxver->getType());
    EXPECT_EQ(max_ver, maxver->intValue());
}

// Test set loggers.
TEST(TranslatorLoggersTest, set) {
    // Get a translator loggers object to play with.
    S_Connection conn(new Connection("translator loggeres unittests"));
    S_Session sess(new Session(conn, SR_DS_CANDIDATE));
    boost::scoped_ptr<TranslatorLoggers> tls_obj;

    // Use the ad hoc model.
    const string& model = "kea-dhcp4-server";
    EXPECT_NO_THROW(tls_obj.reset(new TranslatorLoggers(sess, model)));

    // Set a value.
    const string& xpath = "/kea-dhcp4-server:logging/loggers";
    ElementPtr option = Element::createMap();
    option->set("output", Element::create(string("/bar")));
    option->set("maxver", Element::create(10));
    ElementPtr options = Element::createList();
    options->add(option);
    ElementPtr logger = Element::createMap();
    logger->set("name", Element::create(string("foo")));
    logger->set("severity", Element::create(string("WARN")));
    logger->set("output_options", options);
    ElementPtr loggers = Element::createList();
    loggers->add(logger);
    ASSERT_NO_THROW(tls_obj->setLoggers(xpath, loggers));

    // Get it back.
    ConstElementPtr gots;
    EXPECT_NO_THROW(gots = tls_obj->getLoggers(xpath));
    ASSERT_TRUE(gots);
    ASSERT_EQ(1, gots->size());
    ConstElementPtr got = gots->get(0);
    ASSERT_TRUE(got);
    EXPECT_EQ(3, got->size());
    ConstElementPtr name = got->get("name");
    ASSERT_TRUE(name);
    ASSERT_EQ(Element::string, name->getType());
    EXPECT_EQ("foo", name->stringValue());
    ConstElementPtr severity = logger->get("severity");
    ASSERT_TRUE(severity);
    ASSERT_EQ(Element::string, severity->getType());
    EXPECT_EQ("WARN", severity->stringValue());
    ConstElementPtr got_os = logger->get("output_options");
    ASSERT_TRUE(got_os);
    ASSERT_EQ(1, got_os->size());
    ConstElementPtr got_o = got_os->get(0);
    ASSERT_TRUE(got_o);
    EXPECT_EQ(2, got_o->size());
    ConstElementPtr output = got_o->get("output");
    ASSERT_TRUE(output);
    ASSERT_EQ(Element::string, output->getType());
    EXPECT_EQ("/bar", output->stringValue());
    ConstElementPtr maxver = got_o->get("maxver");
    ASSERT_TRUE(maxver);
    ASSERT_EQ(Element::integer, maxver->getType());
    EXPECT_EQ(10, maxver->intValue());

    // Check the tree representation.
    S_Tree tree;
    EXPECT_NO_THROW(tree = sess->get_subtree("/kea-dhcp4-server:logging"));
    ASSERT_TRUE(tree);
    string expected =
        "kea-dhcp4-server:logging (container)\n"
        " |\n"
        " -- loggers (container)\n"
        "     |\n"
        "     -- logger (list instance)\n"
        "         |\n"
        "         -- name = foo\n"
        "         |\n"
        "         -- output-options (container)\n"
        "         |   |\n"
        "         |   -- option (list instance)\n"
        "         |       |\n"
        "         |       -- output = /bar\n"
        "         |       |\n"
        "         |       -- maxver = 10\n"
        "         |\n"
        "         -- severity = WARN\n";
    EXPECT_EQ(expected, tree->to_string(100));
}

}; // end of anonymous namespace
