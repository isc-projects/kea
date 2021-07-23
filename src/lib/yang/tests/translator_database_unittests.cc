// Copyright (C) 2018-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <yang/translator_database.h>
#include <yang/yang_models.h>
#include <yang/tests/sysrepo_setup.h>

#include <gtest/gtest.h>

using namespace std;
using namespace isc;
using namespace isc::data;
using namespace isc::yang;
using namespace isc::yang::test;
using namespace sysrepo;

namespace {

/// @brief Translator name.
extern char const database_access[] = "database access";

/// @brief Test fixture class for @ref TranslatorDatabase.
class TranslatorDatabaseTestv4 :
    public GenericTranslatorTest<database_access, TranslatorDatabase> {
public:
    TranslatorDatabaseTestv4() {
        model_ = KEA_DHCP4_SERVER;
    }

    virtual ~TranslatorDatabaseTestv4() = default;
};

class TranslatorDatabaseTestv6 :
    public GenericTranslatorTest<database_access, TranslatorDatabase> {
public:
    TranslatorDatabaseTestv6() {
        model_ = KEA_DHCP6_SERVER;
    }

    virtual ~TranslatorDatabaseTestv6() = default;
};

// This test verifies that an empty database can be properly
// translated from YANG to JSON.
TEST_F(TranslatorDatabaseTestv4, getEmpty) {
    // Get empty.
    const string& xpath = "/kea-dhcp4-server:config/lease-database";
    ConstElementPtr database;
    EXPECT_NO_THROW(database = t_obj_->getDatabase(xpath));
    EXPECT_FALSE(database);
}

// This test verifies that a database can be properly
// translated from YANG to JSON.
TEST_F(TranslatorDatabaseTestv4, get) {
    // Set a value.
    const string& xpath = "/kea-dhcp4-server:config/lease-database";
    const string& xtype = xpath + "/database-type";
    const string& xinterval = xpath + "/lfc-interval";
    S_Val s_type(new Val("memfile"));
    EXPECT_NO_THROW(sess_->set_item(xtype.c_str(), s_type));
    uint32_t li = 3600;
    S_Val s_interval(new Val(li));
    EXPECT_NO_THROW(sess_->set_item(xinterval.c_str(), s_interval));

    // Get empty.
    ConstElementPtr database;
    EXPECT_NO_THROW(database = t_obj_->getDatabase(xpath));
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

// This test verifies that a database can be properly
// translated from JSON to YANG.
TEST_F(TranslatorDatabaseTestv4, set) {
    // Set a value.
    const string& xpath = "/kea-dhcp4-server:config/lease-database";
    ElementPtr database = Element::createMap();
    database->set("type", Element::create(string("memfile")));
    database->set("lfc-interval", Element::create(3600));
    ASSERT_NO_THROW_LOG(t_obj_->setDatabase(xpath, database));

    // Get it back.
    ConstElementPtr got;
    EXPECT_NO_THROW(got = t_obj_->getDatabase(xpath));
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

// This test verifies that an empty database can be properly
// translated from JSON to YANG.
TEST_F(TranslatorDatabaseTestv4, setEmpty) {
    // Set a value.
    const string& xpath = "/kea-dhcp4-server:config/lease-database";
    const string& xtype = xpath + "/database-type";
    const string& xinterval = xpath + "/lfc-interval";
    S_Val s_type(new Val("memfile"));
    EXPECT_NO_THROW(sess_->set_item(xtype.c_str(), s_type));
    uint32_t li = 3600;
    S_Val s_interval(new Val(li));
    EXPECT_NO_THROW(sess_->set_item(xinterval.c_str(), s_interval));
    sess_->apply_changes();

    // Reset to empty.
    ASSERT_NO_THROW_LOG(t_obj_->setDatabase(xpath, ConstElementPtr()));

    // Get it back.
    ConstElementPtr database;
    EXPECT_NO_THROW(database = t_obj_->getDatabase(xpath));
    EXPECT_FALSE(database);
}

/// @brief Translator name.
extern char const database_accesses[] = "database accesses";

/// @brief Test fixture class for @ref TranslatorDatabases.
class TranslatorDatabasesTestv4 :
    public GenericTranslatorTest<database_accesses, TranslatorDatabases> {
public:

    /// Constructor.
    TranslatorDatabasesTestv4() {
        model_ = KEA_DHCP4_SERVER;
    }
};

class TranslatorDatabasesTestv6 :
    public GenericTranslatorTest<database_accesses, TranslatorDatabases> {
public:

    /// Constructor.
    TranslatorDatabasesTestv6() {
        model_ = KEA_DHCP6_SERVER;
    }
};

// This test verifies that an empty database list can be properly
// translated from YANG to JSON.
TEST_F(TranslatorDatabasesTestv6, getEmpty) {
    // Get empty.
    const string& xpath = "/kea-dhcp6-server:config/hosts-database";
    ConstElementPtr databases;
    EXPECT_NO_THROW(databases = t_obj_->getDatabases(xpath));
    EXPECT_FALSE(databases);
}

// This test verifies that a database list can be properly
// translated from YANG to JSON.
TEST_F(TranslatorDatabasesTestv4, get) {
    // Set a value.
    const string& xpath = "/kea-dhcp4-server:config/hosts-database";
    const string& xdatabase = xpath + "[database-type='mysql']";
    const string& xname = xdatabase + "/name";
    const string& xuser = xdatabase + "/user";
    const string& xpassword = xdatabase + "/password";
    const string& xhost = xdatabase + "/host";
    const string& xport = xdatabase + "/port";
    S_Val s_name(new Val("kea"));
    EXPECT_NO_THROW(sess_->set_item(xname.c_str(), s_name));
    S_Val s_user(new Val("kea"));
    EXPECT_NO_THROW(sess_->set_item(xuser.c_str(), s_user));
    S_Val s_password(new Val("kea"));
    EXPECT_NO_THROW(sess_->set_item(xpassword.c_str(), s_password));
    S_Val s_host(new Val("localhost"));
    EXPECT_NO_THROW(sess_->set_item(xhost.c_str(), s_host));
    uint16_t mport = 3306;
    S_Val s_port(new Val(mport));
    EXPECT_NO_THROW(sess_->set_item(xport.c_str(), s_port));

    // Get empty.
    ConstElementPtr databases;
    EXPECT_NO_THROW(databases = t_obj_->getDatabases(xpath));
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

// This test verifies that a database list can be properly
// translated from JSON to YANG.
TEST_F(TranslatorDatabasesTestv6, set) {
    // Set a value.
    const string& xpath = "/kea-dhcp6-server:config/hosts-database";
    ElementPtr database = Element::createMap();
    database->set("type", Element::create(string("memfile")));
    database->set("lfc-interval", Element::create(3600));
    ElementPtr databases = Element::createList();
    databases->add(database);
    ASSERT_NO_THROW_LOG(t_obj_->setDatabases(xpath, databases));

    // Get it back.
    ConstElementPtr gots;
    EXPECT_NO_THROW(gots = t_obj_->getDatabases(xpath));
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

    // Check it validates.
    EXPECT_NO_THROW(sess_->validate());
}

// This test verifies that an emptied database list can be properly
// translated from JSON to YANG.
TEST_F(TranslatorDatabasesTestv4, setEmpty) {
    // Set a value.
    const string& xpath = "/kea-dhcp4-server:config/hosts-database";
    const string& xdatabase = xpath + "[database-type='mysql']";
    const string& xname = xdatabase + "/name";
    const string& xuser = xdatabase + "/user";
    const string& xpassword = xdatabase + "/password";
    const string& xhost = xdatabase + "/host";
    const string& xport = xdatabase + "/port";
    S_Val s_name(new Val("kea"));
    EXPECT_NO_THROW(sess_->set_item(xname.c_str(), s_name));
    S_Val s_user(new Val("kea"));
    EXPECT_NO_THROW(sess_->set_item(xuser.c_str(), s_user));
    S_Val s_password(new Val("kea"));
    EXPECT_NO_THROW(sess_->set_item(xpassword.c_str(), s_password));
    S_Val s_host(new Val("localhost"));
    EXPECT_NO_THROW(sess_->set_item(xhost.c_str(), s_host));
    uint16_t mport = 3306;
    S_Val s_port(new Val(mport));
    EXPECT_NO_THROW(sess_->set_item(xport.c_str(), s_port));
    sess_->apply_changes();

    // Reset to empty.
    EXPECT_NO_THROW(t_obj_->setDatabase(xdatabase, ConstElementPtr()));

    // Get empty.
    ConstElementPtr databases;
    EXPECT_NO_THROW(databases = t_obj_->getDatabases(xpath));
    EXPECT_FALSE(databases);
}

// This test verifies that an empty database list can be properly
// translated from JSON to YANG.
TEST_F(TranslatorDatabasesTestv4, setEmpties) {
    // Set a value.
    const string& xpath = "/kea-dhcp4-server:config/hosts-database";
    const string& xdatabase = xpath + "[database-type='mysql']";
    const string& xname = xdatabase + "/name";
    const string& xuser = xdatabase + "/user";
    const string& xpassword = xdatabase + "/password";
    const string& xhost = xdatabase + "/host";
    const string& xport = xdatabase + "/port";
    S_Val s_name(new Val("kea"));
    EXPECT_NO_THROW(sess_->set_item(xname.c_str(), s_name));
    S_Val s_user(new Val("kea"));
    EXPECT_NO_THROW(sess_->set_item(xuser.c_str(), s_user));
    S_Val s_password(new Val("kea"));
    EXPECT_NO_THROW(sess_->set_item(xpassword.c_str(), s_password));
    S_Val s_host(new Val("localhost"));
    EXPECT_NO_THROW(sess_->set_item(xhost.c_str(), s_host));
    uint16_t mport = 3306;
    S_Val s_port(new Val(mport));
    EXPECT_NO_THROW(sess_->set_item(xport.c_str(), s_port));
    sess_->apply_changes();

    // Reset to empty.
    EXPECT_NO_THROW(t_obj_->setDatabases(xdatabase, ConstElementPtr()));

    // Get empty.
    ConstElementPtr databases;
    EXPECT_NO_THROW(databases = t_obj_->getDatabases(xpath));
    EXPECT_FALSE(databases);
}

}  // namespace
