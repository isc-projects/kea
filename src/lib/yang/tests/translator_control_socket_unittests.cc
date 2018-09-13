// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <yang/translator_control_socket.h>

#include <boost/scoped_ptr.hpp>
#include <gtest/gtest.h>

using namespace std;
using namespace isc;
using namespace isc::data;
using namespace isc::yang;

namespace {

// Test get empty control socket using the Kea ad hoc model.
TEST(TranslatorControlSocketTest, getEmpty) {
    // Get a translator control socket object to play with.
    S_Connection conn(new Connection("translator control socket unittests"));
    S_Session sess(new Session(conn, SR_DS_CANDIDATE));
    boost::scoped_ptr<TranslatorControlSocket> tcs_obj;

    // Use the ad hoc model.
    const string& model = "kea-dhcp4";
    EXPECT_NO_THROW(tcs_obj.reset(new TranslatorControlSocket(sess, model)));

    // Get empty.
    const string& xpath = "/kea-dhcp4:config/control-socket";
    ConstElementPtr sock;
    EXPECT_NO_THROW(sock = tcs_obj->getControlSocket(xpath));
    EXPECT_FALSE(sock);
}
    
// Test get not empty control socket using the Kea ad hoc model.
TEST(TranslatorControlSocketTest, get) {
    // Get a translator control socket object to play with.
    S_Connection conn(new Connection("translator control socket unittests"));
    S_Session sess(new Session(conn, SR_DS_CANDIDATE));
    boost::scoped_ptr<TranslatorControlSocket> tcs_obj;

    // Use the ad hoc model.
    const string& model = "kea-dhcp6";
    EXPECT_NO_THROW(tcs_obj.reset(new TranslatorControlSocket(sess, model)));

    // Set a value.
    const string& xpath = "/kea-dhcp6:config/control-socket";
    const string& xname = xpath + "/socket-name";
    const string& xtype = xpath + "/socket-type";
    const string& xcontext = xpath + "/user-context";
    S_Val s_name(new Val("/tmp/kea.sock"));
    EXPECT_NO_THROW(sess->set_item(xname.c_str(), s_name));
    S_Val s_type(new Val("unix", SR_ENUM_T));
    EXPECT_NO_THROW(sess->set_item(xtype.c_str(), s_type));
    S_Val s_context(new Val("{ \"foo\": 1 }"));
    EXPECT_NO_THROW(sess->set_item(xcontext.c_str(), s_context));

    // Get it.
    ConstElementPtr sock;
    EXPECT_NO_THROW(sock = tcs_obj->getControlSocket(xpath));
    ASSERT_TRUE(sock);
    ASSERT_EQ(Element::map, sock->getType());
    EXPECT_EQ(3, sock->size());
    ConstElementPtr type = sock->get("socket-type");
    ASSERT_TRUE(type);
    ASSERT_EQ(Element::string, type->getType());
    EXPECT_EQ("unix", type->stringValue());
    ConstElementPtr name = sock->get("socket-name");
    ASSERT_TRUE(name);
    ASSERT_EQ(Element::string, name->getType());
    EXPECT_EQ("/tmp/kea.sock", name->stringValue());
    ConstElementPtr context = sock->get("user-context");
    ASSERT_TRUE(context);
    EXPECT_EQ("{ \"foo\": 1 }", context->str());
}

// Test set not empty control socket using the Kea ad hoc model.
TEST(TranslatorControlSocketTest, set) {
    // Get a translator control socket object to play with.
    S_Connection conn(new Connection("translator control socket unittests"));
    S_Session sess(new Session(conn, SR_DS_CANDIDATE));
    boost::scoped_ptr<TranslatorControlSocket> tcs_obj;

    // Use the ad hoc model.
    const string& model = "kea-control-agent";
    EXPECT_NO_THROW(tcs_obj.reset(new TranslatorControlSocket(sess, model)));

    // Set a value.
    const string& xpath =
        "/kea-control-agent:config/control-sockets/socket[server-type='dhcp4']/control-socket";
    ElementPtr sock = Element::createMap();
    sock->set("socket-name", Element::create(string("/tmp/kea.sock")));
    sock->set("socket-type", Element::create(string("unix")));
    sock->set("comment", Element::create(string("a comment")));
    try {
        tcs_obj->setControlSocket(xpath, sock);
    } catch (const std::exception& ex) {
        cerr << "setControlSocket fail with " << ex.what() << endl;
    }
    ASSERT_NO_THROW(tcs_obj->setControlSocket(xpath, sock));

    // Get it back.
    ConstElementPtr got;
    EXPECT_NO_THROW(got = tcs_obj->getControlSocket(xpath));
    ASSERT_TRUE(got);
    ASSERT_EQ(Element::map, got->getType());
    EXPECT_EQ(3, got->size());
    ConstElementPtr name = got->get("socket-name");
    ASSERT_TRUE(name);
    ASSERT_EQ(Element::string, name->getType());
    EXPECT_EQ("/tmp/kea.sock", name->stringValue());
    ConstElementPtr type = got->get("socket-type");
    ASSERT_TRUE(type);
    ASSERT_EQ(Element::string, type->getType());
    EXPECT_EQ("unix", type->stringValue());
    ConstElementPtr context = got->get("user-context");
    ASSERT_TRUE(context);
    EXPECT_EQ("{ \"comment\": \"a comment\" }", context->str());
}

// Test set empty control socket using the Kea ad hoc model.
TEST(TranslatorControlSocketTest, setEmpty) {
    // Get a translator control socket object to play with.
    S_Connection conn(new Connection("translator control socket unittests"));
    S_Session sess(new Session(conn, SR_DS_CANDIDATE));
    boost::scoped_ptr<TranslatorControlSocket> tcs_obj;

    // Use the ad hoc model.
    const string& model = "kea-dhcp4";
    EXPECT_NO_THROW(tcs_obj.reset(new TranslatorControlSocket(sess, model)));

    // Set a value.
    const string& xpath = "/kea-dhcp4:config/control-socket";
    const string& xname = xpath + "/socket-name";
    const string& xtype = xpath + "/socket-type";
    const string& xcontext = xpath + "/user-context";
    S_Val s_name(new Val("/tmp/kea.sock"));
    EXPECT_NO_THROW(sess->set_item(xname.c_str(), s_name));
    S_Val s_type(new Val("unix", SR_ENUM_T));
    EXPECT_NO_THROW(sess->set_item(xtype.c_str(), s_type));
    S_Val s_context(new Val("{ \"foo\": 1 }"));
    EXPECT_NO_THROW(sess->set_item(xcontext.c_str(), s_context));

    // Reset to empty.
    ASSERT_NO_THROW(tcs_obj->setControlSocket(xpath, ConstElementPtr()));

    // Get it back.
    ConstElementPtr sock;
    EXPECT_NO_THROW(sock = tcs_obj->getControlSocket(xpath));
    EXPECT_FALSE(sock);
}

}; // end of anonymous namespace
