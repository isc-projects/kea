// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <yang/translator_control_socket.h>
#include <yang/yang_models.h>
#include <yang/tests/sysrepo_setup.h>

#include <gtest/gtest.h>

using namespace std;
using namespace isc;
using namespace isc::data;
using namespace isc::yang;
using namespace isc::yang::test;
#ifndef HAVE_OLD_SYSREPO
using namespace sysrepo;
#endif

namespace {

/// @brief Translator name.
extern char const control_socket[] = "control socket";

/// @brief Test fixture class for @ref TranslatorControlSocket.
class TranslatorControlSocketTest :
    public GenericTranslatorTest<control_socket, TranslatorControlSocket> {
public:

    /// Constructor.
    TranslatorControlSocketTest() { }

    /// Destructor (does nothing).
    virtual ~TranslatorControlSocketTest() { }
};

// This test verifies that an empty control socket can be properly
// translated from YANG to JSON.
TEST_F(TranslatorControlSocketTest, getEmpty) {
    useModel(KEA_DHCP4_SERVER);

    // Get empty.
    const string& xpath = "/kea-dhcp4-server:config/control-socket";
    ConstElementPtr sock;
    EXPECT_NO_THROW(sock = t_obj_->getControlSocket(xpath));
    EXPECT_FALSE(sock);
}

// This test verifies that a not empty control socket can be properly
// translated from YANG to JSON.
TEST_F(TranslatorControlSocketTest, get) {
    useModel(KEA_DHCP6_SERVER);

    // Set a value.
    const string& xpath = "/kea-dhcp6-server:config/control-socket";
    const string& xname = xpath + "/socket-name";
    const string& xtype = xpath + "/socket-type";
    const string& xcontext = xpath + "/user-context";
    S_Val s_name(new Val("/tmp/kea.sock"));
    EXPECT_NO_THROW(sess_->set_item(xname.c_str(), s_name));
    S_Val s_type(new Val("unix", SR_ENUM_T));
    EXPECT_NO_THROW(sess_->set_item(xtype.c_str(), s_type));
    S_Val s_context(new Val("{ \"foo\": 1 }"));
    EXPECT_NO_THROW(sess_->set_item(xcontext.c_str(), s_context));

    // Get it.
    ConstElementPtr sock;
    EXPECT_NO_THROW(sock = t_obj_->getControlSocket(xpath));
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

// This test verifies that a not empty control socket can be properly
// translated from JSON to YANG.
TEST_F(TranslatorControlSocketTest, set) {
    useModel(KEA_CTRL_AGENT);

    // Set a value.
    const string& xpath =
        "/kea-ctrl-agent:config/control-sockets/socket[server-type='dhcp4']/control-socket";
    ElementPtr sock = Element::createMap();
    sock->set("socket-name", Element::create(string("/tmp/kea.sock")));
    sock->set("socket-type", Element::create(string("unix")));
    sock->set("comment", Element::create(string("a comment")));
    try {
        t_obj_->setControlSocket(xpath, sock);
    } catch (const std::exception& ex) {
        cerr << "setControlSocket fail with " << ex.what() << endl;
    }
    ASSERT_NO_THROW(t_obj_->setControlSocket(xpath, sock));

    // Get it back.
    ConstElementPtr got;
    EXPECT_NO_THROW(got = t_obj_->getControlSocket(xpath));
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

    // Check it validates.
    EXPECT_NO_THROW(sess_->validate());
}

// This test verifies that an empty control socket can be properly
// translated from JSON to YANG.
TEST_F(TranslatorControlSocketTest, setEmpty) {
    useModel(KEA_DHCP4_SERVER);

    // Set a value.
    const string& xpath = "/kea-dhcp4-server:config/control-socket";
    const string& xname = xpath + "/socket-name";
    const string& xtype = xpath + "/socket-type";
    const string& xcontext = xpath + "/user-context";
    S_Val s_name(new Val("/tmp/kea.sock"));
    EXPECT_NO_THROW(sess_->set_item(xname.c_str(), s_name));
    S_Val s_type(new Val("unix", SR_ENUM_T));
    EXPECT_NO_THROW(sess_->set_item(xtype.c_str(), s_type));
    S_Val s_context(new Val("{ \"foo\": 1 }"));
    EXPECT_NO_THROW(sess_->set_item(xcontext.c_str(), s_context));

    // Reset to empty.
    ASSERT_NO_THROW(t_obj_->setControlSocket(xpath, ConstElementPtr()));

    // Get it back.
    ConstElementPtr sock;
    EXPECT_NO_THROW(sock = t_obj_->getControlSocket(xpath));
    EXPECT_FALSE(sock);
}

}; // end of anonymous namespace
