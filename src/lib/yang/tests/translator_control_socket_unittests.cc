// Copyright (C) 2018-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <gtest/gtest.h>

#include <yang/tests/sysrepo_setup.h>
#include <yang/translator_control_socket.h>
#include <yang/yang_models.h>

using namespace std;
using namespace isc;
using namespace isc::data;
using namespace isc::yang;
using namespace isc::yang::test;
using namespace libyang;
using namespace sysrepo;

namespace {

/// @brief Translator name.
extern char const control_socket[] = "control socket";

/// @brief Test fixture class for @ref TranslatorControlSocket.
class TranslatorControlSocketTestv4 :
    public GenericTranslatorTest<control_socket, TranslatorControlSocket> {
public:
    /// @brief Constructor
    TranslatorControlSocketTestv4() {
        model_ = KEA_DHCP4_SERVER;
    }

    virtual ~TranslatorControlSocketTestv4() = default;
};  // TranslatorControlSocketTestv4

class TranslatorControlSocketTestv6 :
    public GenericTranslatorTest<control_socket, TranslatorControlSocket> {
public:
    /// @brief Constructor
    TranslatorControlSocketTestv6() {
        model_ = KEA_DHCP6_SERVER;
    }

    virtual ~TranslatorControlSocketTestv6() = default;
};  // TranslatorControlSocketTestv6

class TranslatorControlSocketTestCtrlAgent :
    public GenericTranslatorTest<control_socket, TranslatorControlSocket> {
public:
    /// @brief Constructor
    TranslatorControlSocketTestCtrlAgent() {
        model_ = KEA_CTRL_AGENT;
    }

    virtual ~TranslatorControlSocketTestCtrlAgent() = default;
};  // TranslatorControlSocketTestCtrlAgent

// This test verifies that an empty control socket can be properly
// translated from YANG to JSON.
TEST_F(TranslatorControlSocketTestv4, getEmpty) {
    // Get empty.
    const string& xpath = "/kea-dhcp4-server:config/control-socket";
    ConstElementPtr sock;
    EXPECT_NO_THROW_LOG(sock = translator_->getControlSocketFromAbsoluteXpath(xpath));
    EXPECT_FALSE(sock);
}

// This test verifies that a not empty control socket can be properly
// translated from YANG to JSON.
TEST_F(TranslatorControlSocketTestv6, get) {
    // Set a value.
    const string& xpath = "/kea-dhcp6-server:config/control-socket";
    const string& xname = xpath + "/socket-name";
    const string& xtype = xpath + "/socket-type";
    const string& xcontext = xpath + "/user-context";
    string const s_name("/tmp/kea.sock");
    EXPECT_NO_THROW_LOG(sess_->setItem(xname, s_name));
    string const s_type("unix");
    EXPECT_NO_THROW_LOG(sess_->setItem(xtype, s_type));
    string const s_context("{ \"foo\": 1 }");
    EXPECT_NO_THROW_LOG(sess_->setItem(xcontext, s_context));
    sess_->applyChanges();

    // Get it.
    ConstElementPtr sock;
    EXPECT_NO_THROW_LOG(sock = translator_->getControlSocketFromAbsoluteXpath(xpath));
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
TEST_F(TranslatorControlSocketTestCtrlAgent, set) {
    // Set a value.
    const string& xpath =
        "/kea-ctrl-agent:config/control-sockets/socket[server-type='dhcp4']/control-socket";
    ElementPtr sock = Element::createMap();
    sock->set("socket-name", Element::create("/tmp/kea.sock"));
    sock->set("socket-type", Element::create("unix"));
    sock->set("comment", Element::create("a comment"));
    try {
        translator_->setControlSocket(xpath, sock);
    } catch (exception const& ex) {
        cerr << "setControlSocket fail with " << ex.what() << endl;
    }
    ASSERT_NO_THROW_LOG(translator_->setControlSocket(xpath, sock));

    // Get it back.
    ConstElementPtr got;
    EXPECT_NO_THROW_LOG(got = translator_->getControlSocketFromAbsoluteXpath(xpath));
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

// This test verifies that an empty control socket can be properly
// translated from JSON to YANG.
TEST_F(TranslatorControlSocketTestv4, setEmpty) {
    // Set a value.
    const string& xpath = "/kea-dhcp4-server:config/control-socket";
    const string& xname = xpath + "/socket-name";
    const string& xtype = xpath + "/socket-type";
    const string& xcontext = xpath + "/user-context";
    string const s_name("/tmp/kea.sock");
    EXPECT_NO_THROW_LOG(sess_->setItem(xname, s_name));
    string const s_type("unix");
    EXPECT_NO_THROW_LOG(sess_->setItem(xtype, s_type));
    string const s_context("{ \"foo\": 1 }");
    EXPECT_NO_THROW_LOG(sess_->setItem(xcontext, s_context));
    sess_->applyChanges();

    // Get it back.
    ConstElementPtr sock;
    EXPECT_NO_THROW_LOG(sock = translator_->getControlSocketFromAbsoluteXpath(xpath));
    ASSERT_TRUE(sock);
    EXPECT_EQ(sock->str(),
        R"({ "socket-name": "/tmp/kea.sock", "socket-type": "unix", "user-context": { "foo": 1 } })");

    // Reset to empty.
    EXPECT_NO_THROW_LOG(translator_->setControlSocket(xpath, ConstElementPtr()));

    // Get it back.
    EXPECT_NO_THROW_LOG(sock = translator_->getControlSocketFromAbsoluteXpath(xpath));
    EXPECT_FALSE(sock);
}

}  // namespace
