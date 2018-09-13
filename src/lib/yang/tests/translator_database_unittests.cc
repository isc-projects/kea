// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <yang/translator_database.h>

#include <boost/scoped_ptr.hpp>
#include <gtest/gtest.h>

using namespace std;
using namespace isc;
using namespace isc::data;
using namespace isc::yang;

namespace {

// Test get empty database using the ad hoc model.
TEST(TranslatorDatabaseTest, getEmpty) {
    // Get a translator database object to play with.
    S_Connection conn(new Connection("translator database access unittests"));
    S_Session sess(new Session(conn, SR_DS_CANDIDATE));
    boost::scoped_ptr<TranslatorDatabase> td_obj;

    // Use the ad hoc model.
    const string& model = "kea-dhcp4";
    EXPECT_NO_THROW(td_obj.reset(new TranslatorDatabase(sess, model)));

    // Get empty.
    const string& xpath = "/kea-dhcp4:config/lease-database";
    ConstElementPtr database;
    EXPECT_NO_THROW(database = td_obj->getDatabase(xpath));
    EXPECT_FALSE(database);
}

// Test get a database using the ad hoc model.
TEST(TranslatorDatabaseTest, get) {
    // Get a translator database object to play with.
    S_Connection conn(new Connection("translator database access unittests"));
    S_Session sess(new Session(conn, SR_DS_CANDIDATE));
    boost::scoped_ptr<TranslatorDatabase> td_obj;

    // Use the ad hoc model.
    const string& model = "kea-dhcp4";
    EXPECT_NO_THROW(td_obj.reset(new TranslatorDatabase(sess, model)));

    // Set a value.
    const string& xpath = "/kea-dhcp4:config/lease-database";
    const string& xtype = xpath + "/database-type";
    const string& xinterval = xpath + "/lfc-interval";
    S_Val s_type(new Val("memfile"));
    EXPECT_NO_THROW(sess->set_item(xtype.c_str(), s_type));
    uint32_t li = 3600;
    S_Val s_interval(new Val(li, SR_UINT32_T));
    EXPECT_NO_THROW(sess->set_item(xinterval.c_str(), s_interval));

    // Get empty.
    ConstElementPtr database;
    EXPECT_NO_THROW(database = td_obj->getDatabase(xpath));
    ASSERT_TRUE(database);
    EXPECT_EQ(2, database->size());
    ConstElementPtr type = database->get("type");
    ASSERT_TRUE(type);
    ASSERT_EQ(Element::string, type->getType());
    EXPECT_EQ("memfile", type->stringValue());
    ConstElementPtr interval = database->get("lfc-interval");
    ASSERT_TRUE(interval);
    ASSERT_EQ(Element::integer, interval->getType());
    EXPECT_EQ(li, interval->intValue());
}

// Test set a database using the ad hoc model.
TEST(TranslatorDatabaseTest, set) {
    // Get a translator database object to play with.
    S_Connection conn(new Connection("translator database access unittests"));
    S_Session sess(new Session(conn, SR_DS_CANDIDATE));
    boost::scoped_ptr<TranslatorDatabase> td_obj;

    // Use the ad hoc model.
    const string& model = "kea-dhcp4";
    EXPECT_NO_THROW(td_obj.reset(new TranslatorDatabase(sess, model)));

    // Set a value.
    const string& xpath = "/kea-dhcp4:config/lease-database";
    ElementPtr database = Element::createMap();
    database->set("type", Element::create(string("memfile")));
    database->set("lfc-interval", Element::create(3600));
    ASSERT_NO_THROW(td_obj->setDatabase(xpath, database));

    // Get it back.
    ConstElementPtr got;
    EXPECT_NO_THROW(got = td_obj->getDatabase(xpath));
    ASSERT_TRUE(got);
    ASSERT_EQ(Element::map, got->getType());
    EXPECT_EQ(2, got->size());
    ConstElementPtr type = got->get("type");
    ASSERT_TRUE(type);
    ASSERT_EQ(Element::string, type->getType());
    EXPECT_EQ("memfile", type->stringValue());
    ConstElementPtr interval = database->get("lfc-interval");
    ASSERT_TRUE(interval);
    ASSERT_EQ(Element::integer, interval->getType());
    EXPECT_EQ(3600, interval->intValue());
}

// Test set empty database using the ad hoc model.
TEST(TranslatorDatabaseTest, setEmpty) {
    // Get a translator database object to play with.
    S_Connection conn(new Connection("translator database access unittests"));
    S_Session sess(new Session(conn, SR_DS_CANDIDATE));
    boost::scoped_ptr<TranslatorDatabase> td_obj;

    // Use the ad hoc model.
    const string& model = "kea-dhcp4";
    EXPECT_NO_THROW(td_obj.reset(new TranslatorDatabase(sess, model)));

    // Set a value.
    const string& xpath = "/kea-dhcp4:config/lease-database";
    const string& xtype = xpath + "/database-type";
    const string& xinterval = xpath + "/lfc-interval";
    S_Val s_type(new Val("memfile"));
    EXPECT_NO_THROW(sess->set_item(xtype.c_str(), s_type));
    uint32_t li = 3600;
    S_Val s_interval(new Val(li, SR_UINT32_T));
    EXPECT_NO_THROW(sess->set_item(xinterval.c_str(), s_interval));

    // Reset to empty.
    ASSERT_NO_THROW(td_obj->setDatabase(xpath, ConstElementPtr()));

    // Get it back.
    ConstElementPtr database;
    EXPECT_NO_THROW(database = td_obj->getDatabase(xpath));
    EXPECT_FALSE(database);
}

// Test get empty databases.
TEST(TranslatorDatabasesTest, getEmpty) {
    // Get a translator databases object to play with.
    S_Connection conn(new Connection("translator database accesses unittests"));
    S_Session sess(new Session(conn, SR_DS_CANDIDATE));
    boost::scoped_ptr<TranslatorDatabases> tds_obj;

    // Use the ad hoc model.
    const string& model = "kea-dhcp6";
    EXPECT_NO_THROW(tds_obj.reset(new TranslatorDatabases(sess, model)));

    // Get empty.
    const string& xpath = "/kea-dhcp6:config/hosts-databases";
    ConstElementPtr databases;
    EXPECT_NO_THROW(databases = tds_obj->getDatabases(xpath));
    EXPECT_FALSE(databases);
}

// Test get databases.
TEST(TranslatorDatabasesTest, get) {
    // Get a translator databases object to play with.
    S_Connection conn(new Connection("translator database accesses unittests"));
    S_Session sess(new Session(conn, SR_DS_CANDIDATE));
    boost::scoped_ptr<TranslatorDatabases> tds_obj;

    // Use the ad hoc model.
    const string& model = "kea-dhcp4";
    EXPECT_NO_THROW(tds_obj.reset(new TranslatorDatabases(sess, model)));

    // Set a value.
    const string& xpath = "/kea-dhcp4:config/hosts-databases";
    const string& xdatabase =
        xpath + "/hosts-database[database-type='mysql']";
    const string& xname = xdatabase + "/name";
    const string& xuser = xdatabase + "/user";
    const string& xpassword = xdatabase + "/password";
    const string& xhost = xdatabase + "/host";
    const string& xport = xdatabase + "/port";
    S_Val s_name(new Val("kea"));
    EXPECT_NO_THROW(sess->set_item(xname.c_str(), s_name));
    S_Val s_user(new Val("kea"));
    EXPECT_NO_THROW(sess->set_item(xuser.c_str(), s_user));
    S_Val s_password(new Val("kea"));
    EXPECT_NO_THROW(sess->set_item(xpassword.c_str(), s_password));
    S_Val s_host(new Val("localhost"));
    EXPECT_NO_THROW(sess->set_item(xhost.c_str(), s_host));
    uint16_t mport = 3306;
    S_Val s_port(new Val(mport, SR_UINT16_T));
    EXPECT_NO_THROW(sess->set_item(xport.c_str(), s_port));

    // Get empty.
    ConstElementPtr databases;
    EXPECT_NO_THROW(databases = tds_obj->getDatabases(xpath));
    ASSERT_TRUE(databases);
    ASSERT_EQ(1, databases->size());
    ConstElementPtr database = databases->get(0);
    ASSERT_TRUE(database);
    EXPECT_EQ(6, database->size());
    ConstElementPtr type = database->get("type");
    ASSERT_TRUE(type);
    ASSERT_EQ(Element::string, type->getType());
    EXPECT_EQ("mysql", type->stringValue());
    ConstElementPtr name = database->get("name");
    ASSERT_TRUE(name);
    ASSERT_EQ(Element::string, name->getType());
    EXPECT_EQ("kea", name->stringValue());
    ConstElementPtr user = database->get("user");
    ASSERT_TRUE(user);
    ASSERT_EQ(Element::string, user->getType());
    EXPECT_EQ("kea", user->stringValue());
    ConstElementPtr password = database->get("password");
    ASSERT_TRUE(password);
    ASSERT_EQ(Element::string, password->getType());
    EXPECT_EQ("kea", password->stringValue());
    ConstElementPtr host = database->get("host");
    ASSERT_TRUE(host);
    ASSERT_EQ(Element::string, host->getType());
    EXPECT_EQ("localhost", host->stringValue());
    ConstElementPtr port = database->get("port");
    ASSERT_TRUE(port);
    ASSERT_EQ(Element::integer, port->getType());
    EXPECT_EQ(mport, port->intValue());
}

// Test set databases.
TEST(TranslatorDatabasesTest, set) {
    // Get a translator databases object to play with.
    S_Connection conn(new Connection("translator database accesses unittests"));
    S_Session sess(new Session(conn, SR_DS_CANDIDATE));
    boost::scoped_ptr<TranslatorDatabases> tds_obj;

    // Use the ad hoc model.
    const string& model = "kea-dhcp6";
    EXPECT_NO_THROW(tds_obj.reset(new TranslatorDatabases(sess, model)));

    // Set a value.
    const string& xpath = "/kea-dhcp6:config/hosts-databases";
    ElementPtr database = Element::createMap();
    database->set("type", Element::create(string("memfile")));
    database->set("lfc-interval", Element::create(3600));
    ElementPtr databases = Element::createList();
    databases->add(database);
    ASSERT_NO_THROW(tds_obj->setDatabases(xpath, databases));

    // Get it back.
    ConstElementPtr gots;
    EXPECT_NO_THROW(gots = tds_obj->getDatabases(xpath));
    ASSERT_TRUE(gots);
    ASSERT_EQ(Element::list, gots->getType());
    ASSERT_EQ(1, gots->size());
    ConstElementPtr got = gots->get(0);
    ASSERT_TRUE(got);
    ASSERT_EQ(Element::map, got->getType());
    EXPECT_EQ(2, got->size());
    ConstElementPtr type = got->get("type");
    ASSERT_TRUE(type);
    ASSERT_EQ(Element::string, type->getType());
    EXPECT_EQ("memfile", type->stringValue());
    ConstElementPtr interval = database->get("lfc-interval");
    ASSERT_TRUE(interval);
    ASSERT_EQ(Element::integer, interval->getType());
    EXPECT_EQ(3600, interval->intValue());
}

// Test set empty database.
TEST(TranslatorDatabasesTest, setEmpty) {
    // Get a translator databases object to play with.
    S_Connection conn(new Connection("translator database accesses unittests"));
    S_Session sess(new Session(conn, SR_DS_CANDIDATE));
    boost::scoped_ptr<TranslatorDatabases> tds_obj;
    boost::scoped_ptr<TranslatorDatabase> td_obj;

    // Use the ad hoc model.
    const string& model = "kea-dhcp4";
    EXPECT_NO_THROW(tds_obj.reset(new TranslatorDatabases(sess, model)));
    EXPECT_NO_THROW(td_obj.reset(new TranslatorDatabase(sess, model)));

    // Set a value.
    const string& xpath = "/kea-dhcp4:config/hosts-databases";
    const string& xdatabase =
        xpath + "/hosts-database[database-type='mysql']";
    const string& xname = xdatabase + "/name";
    const string& xuser = xdatabase + "/user";
    const string& xpassword = xdatabase + "/password";
    const string& xhost = xdatabase + "/host";
    const string& xport = xdatabase + "/port";
    S_Val s_name(new Val("kea"));
    EXPECT_NO_THROW(sess->set_item(xname.c_str(), s_name));
    S_Val s_user(new Val("kea"));
    EXPECT_NO_THROW(sess->set_item(xuser.c_str(), s_user));
    S_Val s_password(new Val("kea"));
    EXPECT_NO_THROW(sess->set_item(xpassword.c_str(), s_password));
    S_Val s_host(new Val("localhost"));
    EXPECT_NO_THROW(sess->set_item(xhost.c_str(), s_host));
    uint16_t mport = 3306;
    S_Val s_port(new Val(mport, SR_UINT16_T));
    EXPECT_NO_THROW(sess->set_item(xport.c_str(), s_port));

    // Reset to empty.
    ASSERT_NO_THROW(td_obj->setDatabase(xdatabase, ConstElementPtr()));

    // Get empty.
    ConstElementPtr databases;
    EXPECT_NO_THROW(databases = tds_obj->getDatabases(xpath));
    EXPECT_FALSE(databases);
}

// Test set empty databases.
TEST(TranslatorDatabasesTest, setEmpties) {
    // Get a translator databases object to play with.
    S_Connection conn(new Connection("translator database accesses unittests"));
    S_Session sess(new Session(conn, SR_DS_CANDIDATE));
    boost::scoped_ptr<TranslatorDatabases> tds_obj;

    // Use the ad hoc model.
    const string& model = "kea-dhcp4";
    EXPECT_NO_THROW(tds_obj.reset(new TranslatorDatabases(sess, model)));

    // Set a value.
    const string& xpath = "/kea-dhcp4:config/hosts-databases";
    const string& xdatabase =
        xpath + "/hosts-database[database-type='mysql']";
    const string& xname = xdatabase + "/name";
    const string& xuser = xdatabase + "/user";
    const string& xpassword = xdatabase + "/password";
    const string& xhost = xdatabase + "/host";
    const string& xport = xdatabase + "/port";
    S_Val s_name(new Val("kea"));
    EXPECT_NO_THROW(sess->set_item(xname.c_str(), s_name));
    S_Val s_user(new Val("kea"));
    EXPECT_NO_THROW(sess->set_item(xuser.c_str(), s_user));
    S_Val s_password(new Val("kea"));
    EXPECT_NO_THROW(sess->set_item(xpassword.c_str(), s_password));
    S_Val s_host(new Val("localhost"));
    EXPECT_NO_THROW(sess->set_item(xhost.c_str(), s_host));
    uint16_t mport = 3306;
    S_Val s_port(new Val(mport, SR_UINT16_T));
    EXPECT_NO_THROW(sess->set_item(xport.c_str(), s_port));

    // Reset to empty.
    ASSERT_NO_THROW(tds_obj->setDatabases(xdatabase, ConstElementPtr()));

    // Get empty.
    ConstElementPtr databases;
    EXPECT_NO_THROW(databases = tds_obj->getDatabases(xpath));
    EXPECT_FALSE(databases);
}

}; // end of anonymous namespace
