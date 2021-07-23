// Copyright (C) 2018-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <testutils/gtest_utils.h>
#include <yang/translator.h>

#include <boost/scoped_ptr.hpp>

#include <gtest/gtest.h>

using namespace std;
using namespace isc;
using namespace isc::data;
using namespace isc::yang;
using namespace sysrepo;

using libyang::S_Data_Node;

namespace {

// Test constructor.
TEST(TranslatorBasicTest, constructor) {
    // Get a connection.
    S_Connection conn(std::make_shared<Connection>());
    // Get a session.
    S_Session sess(new Session(conn, SR_DS_CANDIDATE));
    // Get a translator object.
    boost::scoped_ptr<TranslatorBasic> t_obj;
    EXPECT_NO_THROW(t_obj.reset(new TranslatorBasic(sess, "")));
}

// Test basic yang value to JSON using the static method.
TEST(TranslatorBasicTest, valueFrom) {
    S_Val s_val;
    ConstElementPtr elem;

    // Null.
    EXPECT_THROW(TranslatorBasic::value(s_val), BadValue);

    // No easy and direct way to build a container or a list...

    // String.
    string str("foo");
    s_val.reset(new Val(str.c_str(), SR_STRING_T));
    EXPECT_NO_THROW(elem = TranslatorBasic::value(s_val));
    ASSERT_TRUE(elem);
    ASSERT_EQ(Element::string, elem->getType());
    EXPECT_EQ(str, elem->stringValue());
    elem.reset();

    // Bool.
    s_val.reset(new Val(false, SR_BOOL_T));
    EXPECT_NO_THROW(elem = TranslatorBasic::value(s_val));
    ASSERT_TRUE(elem);
    ASSERT_EQ(Element::boolean, elem->getType());
    EXPECT_FALSE(elem->boolValue());
    elem.reset();

    // Unsigned 8 bit integer.
    uint8_t u8(123);
    s_val.reset(new Val(u8));
    EXPECT_NO_THROW(elem = TranslatorBasic::value(s_val));
    ASSERT_TRUE(elem);
    ASSERT_EQ(Element::integer, elem->getType());
    EXPECT_EQ(u8, elem->intValue());
    elem.reset();

    // Unsigned 16 bit integer.
    uint16_t u16(12345);
    s_val.reset(new Val(u16));
    EXPECT_NO_THROW(elem = TranslatorBasic::value(s_val));
    ASSERT_TRUE(elem);
    ASSERT_EQ(Element::integer, elem->getType());
    EXPECT_EQ(u16, elem->intValue());
    elem.reset();

    // Unsigned 32 bit integer.
    uint32_t u32(123456789);
    s_val.reset(new Val(u32));
    EXPECT_NO_THROW(elem = TranslatorBasic::value(s_val));
    ASSERT_TRUE(elem);
    ASSERT_EQ(Element::integer, elem->getType());
    EXPECT_EQ(u32, elem->intValue());
    elem.reset();

    // Signed 8 bit integer.
    int8_t s8(-123);
    s_val.reset(new Val(s8));
    EXPECT_NO_THROW(elem = TranslatorBasic::value(s_val));
    ASSERT_TRUE(elem);
    ASSERT_EQ(Element::integer, elem->getType());
    EXPECT_EQ(s8, elem->intValue());
    elem.reset();

    // Signed 16 bit integer.
    int16_t s16(-12345);
    s_val.reset(new Val(s16));
    EXPECT_NO_THROW(elem = TranslatorBasic::value(s_val));
    ASSERT_TRUE(elem);
    ASSERT_EQ(Element::integer, elem->getType());
    EXPECT_EQ(s16, elem->intValue());
    elem.reset();

    // Signed 32 bit integer.
    int32_t s32(-123456789);
    s_val.reset(new Val(s32));
    EXPECT_NO_THROW(elem = TranslatorBasic::value(s_val));
    ASSERT_TRUE(elem);
    ASSERT_EQ(Element::integer, elem->getType());
    EXPECT_EQ(s32, elem->intValue());
    elem.reset();

    // Identity reference.
    s_val.reset(new Val(str.c_str(), SR_IDENTITYREF_T));
    EXPECT_NO_THROW(elem = TranslatorBasic::value(s_val));
    ASSERT_TRUE(elem);
    ASSERT_EQ(Element::string, elem->getType());
    EXPECT_EQ(str, elem->stringValue());
    elem.reset();

    // Enumeration item.
    s_val.reset(new Val(str.c_str(), SR_ENUM_T));
    EXPECT_NO_THROW(elem = TranslatorBasic::value(s_val));
    ASSERT_TRUE(elem);
    ASSERT_EQ(Element::string, elem->getType());
    EXPECT_EQ(str, elem->stringValue());
    elem.reset();

    // Binary.
    string binary("Zm9vYmFy");
    s_val.reset(new Val(binary.c_str(), SR_BINARY_T));
    EXPECT_NO_THROW(elem = TranslatorBasic::value(s_val));
    ASSERT_TRUE(elem);
    ASSERT_EQ(Element::string, elem->getType());
    EXPECT_EQ("foobar", elem->stringValue());
    elem.reset();

    // Decimal 64.
    double d64(.1234);
    s_val.reset(new Val(d64));
    EXPECT_NO_THROW(elem = TranslatorBasic::value(s_val));
    ASSERT_TRUE(elem);
    ASSERT_EQ(Element::real, elem->getType());
    EXPECT_DOUBLE_EQ(d64, elem->doubleValue());
}

// Test basic yang value to JSON using sysrepo test models.
TEST(TranslatorBasicTest, getItem) {
    // Get a translator object to play with.
    S_Connection conn(std::make_shared<Connection>());
    S_Session sess(new Session(conn, SR_DS_CANDIDATE));
    boost::scoped_ptr<TranslatorBasic> t_obj;
    ASSERT_NO_THROW_LOG(t_obj.reset(new TranslatorBasic(sess, "")));
    S_Val s_val;
    ConstElementPtr elem;
    string xpath;

    // String.
    xpath = "/keatest-module:main/string";
    s_val.reset(new Val("str", SR_STRING_T));
    EXPECT_NO_THROW(sess->set_item(xpath.c_str(), s_val));
    EXPECT_NO_THROW(elem = t_obj->getItem(xpath));
    ASSERT_TRUE(elem);
    ASSERT_EQ(Element::string, elem->getType());
    EXPECT_EQ("str", elem->stringValue());
    elem.reset();

    // Bool.
    xpath = "/keatest-module:main/boolean";
    s_val.reset(new Val(true, SR_BOOL_T));
    EXPECT_NO_THROW(sess->set_item(xpath.c_str(), s_val));
    EXPECT_NO_THROW(elem = t_obj->getItem(xpath));
    ASSERT_TRUE(elem);
    ASSERT_EQ(Element::boolean, elem->getType());
    EXPECT_TRUE(elem->boolValue());
    elem.reset();

    // Unsigned 8 bit integer.
    xpath = "/keatest-module:main/ui8";
    uint8_t u8(8);
    s_val.reset(new Val(u8));
    EXPECT_NO_THROW(sess->set_item(xpath.c_str(), s_val));
    EXPECT_NO_THROW(elem = t_obj->getItem(xpath));
    ASSERT_TRUE(elem);
    ASSERT_EQ(Element::integer, elem->getType());
    EXPECT_EQ(8, elem->intValue());
    elem.reset();

    // Unsigned 16 bit integer.
    xpath = "/keatest-module:main/ui16";
    uint16_t u16(16);
    s_val.reset(new Val(u16));
    EXPECT_NO_THROW(sess->set_item(xpath.c_str(), s_val));
    EXPECT_NO_THROW(elem = t_obj->getItem(xpath));
    ASSERT_TRUE(elem);
    ASSERT_EQ(Element::integer, elem->getType());
    EXPECT_EQ(16, elem->intValue());
    elem.reset();

    // Unsigned 32 bit integer.
    xpath = "/keatest-module:main/ui32";
    uint32_t u32(32);
    s_val.reset(new Val(u32));
    EXPECT_NO_THROW(sess->set_item(xpath.c_str(), s_val));
    EXPECT_NO_THROW(elem = t_obj->getItem(xpath));
    ASSERT_TRUE(elem);
    ASSERT_EQ(Element::integer, elem->getType());
    EXPECT_EQ(32, elem->intValue());
    elem.reset();

    // Signed 8 bit integer.
    xpath = "/keatest-module:main/i8";
    int8_t s8(8);
    s_val.reset(new Val(s8));
    EXPECT_NO_THROW(sess->set_item(xpath.c_str(), s_val));
    EXPECT_NO_THROW(elem = t_obj->getItem(xpath));
    ASSERT_TRUE(elem);
    ASSERT_EQ(Element::integer, elem->getType());
    EXPECT_EQ(8, elem->intValue());
    elem.reset();

    // Signed 16 bit integer.
    xpath = "/keatest-module:main/i16";
    int16_t s16(16);
    s_val.reset(new Val(s16));
    EXPECT_NO_THROW(sess->set_item(xpath.c_str(), s_val));
    EXPECT_NO_THROW(elem = t_obj->getItem(xpath));
    ASSERT_TRUE(elem);
    ASSERT_EQ(Element::integer, elem->getType());
    EXPECT_EQ(16, elem->intValue());
    elem.reset();

    // Signed 32 bit integer.
    xpath = "/keatest-module:main/i32";
    int32_t s32(32);
    s_val.reset(new Val(s32));
    EXPECT_NO_THROW(sess->set_item(xpath.c_str(), s_val));
    EXPECT_NO_THROW(elem = t_obj->getItem(xpath));
    ASSERT_TRUE(elem);
    ASSERT_EQ(Element::integer, elem->getType());
    EXPECT_EQ(32, elem->intValue());
    elem.reset();

    // Identity reference.
    xpath = "/keatest-module:main/id_ref";
    s_val.reset(new Val("keatest-module:id_1", SR_IDENTITYREF_T));
    EXPECT_NO_THROW(sess->set_item(xpath.c_str(), s_val));
    EXPECT_NO_THROW(elem = t_obj->getItem(xpath));
    ASSERT_TRUE(elem);
    ASSERT_EQ(Element::string, elem->getType());
    EXPECT_EQ("keatest-module:id_1", elem->stringValue());
    elem.reset();

    // Enumeration item.
    xpath = "/keatest-module:main/enum";
    s_val.reset(new Val("maybe", SR_ENUM_T));
    EXPECT_NO_THROW(sess->set_item(xpath.c_str(), s_val));
    EXPECT_NO_THROW(elem = t_obj->getItem(xpath));
    ASSERT_TRUE(elem);
    ASSERT_EQ(Element::string, elem->getType());
    EXPECT_EQ("maybe", elem->stringValue());
    elem.reset();

    // Binary.
    xpath = "/keatest-module:main/raw";
    s_val.reset(new Val("Zm9vYmFy", SR_BINARY_T));
    EXPECT_NO_THROW(sess->set_item(xpath.c_str(), s_val));
    EXPECT_NO_THROW(elem = t_obj->getItem(xpath));
    ASSERT_TRUE(elem);
    ASSERT_EQ(Element::string, elem->getType());
    EXPECT_EQ("foobar", elem->stringValue());
    elem.reset();

    // Leaf-list: not yet exist.
    xpath = "/keatest-module:main/numbers";
    EXPECT_NO_THROW(elem = t_obj->getItem(xpath));
    EXPECT_FALSE(elem);
    elem.reset();

    // No easy way to create it empty.

    // Leaf-list: 1, 2 and 3.
    u8 = 1;
    s_val.reset(new Val(u8));
    EXPECT_NO_THROW(sess->set_item(xpath.c_str(), s_val));
    u8 = 2;
    s_val.reset(new Val(u8));
    EXPECT_NO_THROW(sess->set_item(xpath.c_str(), s_val));
    u8 = 3;
    s_val.reset(new Val(u8));
    EXPECT_NO_THROW(sess->set_item(xpath.c_str(), s_val));
    EXPECT_NO_THROW(elem = t_obj->getItems(xpath));
    ASSERT_TRUE(elem);
    ASSERT_EQ(Element::list, elem->getType());
    EXPECT_EQ(3, elem->size());
    EXPECT_EQ("[ 1, 2, 3 ]", elem->str());
    elem.reset();

    // Unknown / unsupported.
    xpath = "/keatest-module:main/dec64";
    s_val.reset(new Val(9.85));
    EXPECT_NO_THROW(sess->set_item(xpath.c_str(), s_val));
    EXPECT_NO_THROW(elem = t_obj->getItem(xpath));
    ASSERT_TRUE(elem);
    ASSERT_EQ(Element::real, elem->getType());
    EXPECT_EQ("9.85", elem->str());
    elem.reset();

    // Not found.
    xpath = "/keatest-module:main/no_such_string";

    // sysrepo_exception: "Invalid argument"
    EXPECT_THROW(sess->delete_item(xpath.c_str()), sysrepo_exception);
    EXPECT_THROW(elem = t_obj->getItem(xpath), SysrepoError);
    EXPECT_FALSE(elem);
    elem.reset();

    // Check error.
    xpath = "null";
    try {
        elem = t_obj->getItem(xpath);
        ADD_FAILURE() << "expected exception";
    } catch (const SysrepoError& ex) {
        EXPECT_EQ("sysrepo error getting item at 'null': libyang error",
                  string(ex.what()));
    } catch (const std::exception& ex) {
        ADD_FAILURE() << "unexpected exception with: " << ex.what();
    }
}

// Test JSON to basic yang value using the static method.
TEST(TranslatorBasicTest, valueTo) {

    // Null.
    ConstElementPtr elem;
    EXPECT_THROW(TranslatorBasic::value(elem, SR_STRING_T), BadValue);

    // Container.
    elem = Element::createMap();
    EXPECT_THROW(TranslatorBasic::value(elem, SR_CONTAINER_T), NotImplemented);
    EXPECT_THROW(TranslatorBasic::value(elem, SR_CONTAINER_PRESENCE_T), NotImplemented);

    // List.
    elem = Element::createList();
    S_Val s_val;
    EXPECT_NO_THROW(s_val = TranslatorBasic::value(elem, SR_LIST_T));
    EXPECT_FALSE(s_val);
    s_val.reset();

    // String.
    string str("foo");
    elem = Element::create(str);
    EXPECT_NO_THROW(s_val = TranslatorBasic::value(elem, SR_STRING_T));
    ASSERT_TRUE(s_val);
    ASSERT_EQ(SR_STRING_T, s_val->type());
    EXPECT_EQ(str, string(s_val->data()->get_string()));
    s_val.reset();

    // Bool.
    elem = Element::create(false);
    EXPECT_NO_THROW(s_val = TranslatorBasic::value(elem, SR_BOOL_T));
    ASSERT_TRUE(s_val);
    ASSERT_EQ(SR_BOOL_T, s_val->type());
    EXPECT_FALSE(s_val->data()->get_bool());
    s_val.reset();

    // Unsigned 8 bit integer.
    elem = Element::create(123);
    EXPECT_NO_THROW(s_val = TranslatorBasic::value(elem, SR_UINT8_T));
    ASSERT_TRUE(s_val);
    ASSERT_EQ(SR_UINT8_T, s_val->type());
    EXPECT_EQ(123, s_val->data()->get_uint8());
    elem.reset();

    // Unsigned 16 bit integer.
    elem = Element::create(12345);
    EXPECT_NO_THROW(s_val = TranslatorBasic::value(elem, SR_UINT16_T));
    ASSERT_TRUE(s_val);
    ASSERT_EQ(SR_UINT16_T, s_val->type());
    EXPECT_EQ(12345, s_val->data()->get_uint16());
    elem.reset();

    // Unsigned 32 bit integer.
    elem = Element::create(123456789);
    EXPECT_NO_THROW(s_val = TranslatorBasic::value(elem, SR_UINT32_T));
    ASSERT_TRUE(s_val);
    ASSERT_EQ(SR_UINT32_T, s_val->type());
    EXPECT_EQ(123456789, s_val->data()->get_uint32());
    elem.reset();

    // Signed 8 bit integer.
    elem = Element::create(-123);
    EXPECT_NO_THROW(s_val = TranslatorBasic::value(elem, SR_INT8_T));
    ASSERT_TRUE(s_val);
    ASSERT_EQ(SR_INT8_T, s_val->type());
    EXPECT_EQ(-123, s_val->data()->get_int8());
    elem.reset();

    // Signed 16 bit integer.
    elem = Element::create(-12345);
    EXPECT_NO_THROW(s_val = TranslatorBasic::value(elem, SR_INT16_T));
    ASSERT_TRUE(s_val);
    ASSERT_EQ(SR_INT16_T, s_val->type());
    EXPECT_EQ(-12345, s_val->data()->get_int16());
    elem.reset();

    // Signed 32 bit integer.
    elem = Element::create(-123456789);
    EXPECT_NO_THROW(s_val = TranslatorBasic::value(elem, SR_INT32_T));
    ASSERT_TRUE(s_val);
    ASSERT_EQ(SR_INT32_T, s_val->type());
    EXPECT_EQ(-123456789, s_val->data()->get_int32());
    elem.reset();

    // Identity reference.
    elem = Element::create(str);
    EXPECT_NO_THROW(s_val = TranslatorBasic::value(elem, SR_IDENTITYREF_T));
    ASSERT_TRUE(s_val);
    ASSERT_EQ(SR_IDENTITYREF_T, s_val->type());
    EXPECT_EQ(str, string(s_val->data()->get_identityref()));
    s_val.reset();

    // Enumeration item.
    EXPECT_NO_THROW(s_val = TranslatorBasic::value(elem, SR_ENUM_T));
    ASSERT_TRUE(s_val);
    EXPECT_EQ(str, string(s_val->data()->get_enum()));
    s_val.reset();

    // Binary.
    elem = Element::create(string("foobar"));
    EXPECT_NO_THROW(s_val = TranslatorBasic::value(elem, SR_BINARY_T));
    ASSERT_TRUE(s_val);
    EXPECT_EQ("Zm9vYmFy", string(s_val->data()->get_binary()));
    s_val.reset();

    // Decimal 64.
    double d64(.1234);
    elem = Element::create(d64);
    EXPECT_NO_THROW(s_val = TranslatorBasic::value(elem, SR_DECIMAL64_T));
    ASSERT_TRUE(s_val);
    EXPECT_DOUBLE_EQ(d64, s_val->data()->get_decimal64());
    s_val.reset();
}

// Test JSON to  basic yang value using sysrepo test models.
TEST(TranslatorBasicTest, setItem) {
    // Get a translator object to play with.
    S_Connection conn(std::make_shared<Connection>());
    S_Session sess(new Session(conn, SR_DS_CANDIDATE));
    boost::scoped_ptr<TranslatorBasic> t_obj;
    ASSERT_NO_THROW_LOG(t_obj.reset(new TranslatorBasic(sess, "")));

    // Container.
    string xpath = "/keatest-module:container";
    ConstElementPtr elem = Element::createMap();
    EXPECT_THROW(t_obj->setItem(xpath, elem, SR_CONTAINER_T), NotImplemented);
    EXPECT_THROW(t_obj->setItem(xpath, elem, SR_CONTAINER_PRESENCE_T),
                 NotImplemented);

    // String.
    S_Val s_val;
    xpath = "/keatest-module:main/string";
    elem = Element::create(string("str"));
    EXPECT_NO_THROW(t_obj->setItem(xpath, elem, SR_STRING_T));
    EXPECT_NO_THROW(s_val = sess->get_item(xpath.c_str()));
    ASSERT_TRUE(s_val);
    ASSERT_EQ(SR_STRING_T, s_val->type());
    EXPECT_EQ("str", string(s_val->data()->get_string()));
    s_val.reset();

    // Bool.
    xpath = "/keatest-module:main/boolean";
    elem = Element::create(true);
    EXPECT_NO_THROW(t_obj->setItem(xpath, elem, SR_BOOL_T));
    EXPECT_NO_THROW(s_val = sess->get_item(xpath.c_str()));
    ASSERT_TRUE(s_val);
    ASSERT_EQ(SR_BOOL_T, s_val->type());
    EXPECT_TRUE(s_val->data()->get_bool());
    s_val.reset();

    // Unsigned 8 bit integer.
    xpath = "/keatest-module:main/ui8";
    elem = Element::create(8);
    EXPECT_NO_THROW(t_obj->setItem(xpath, elem, SR_UINT8_T));
    EXPECT_NO_THROW(s_val = sess->get_item(xpath.c_str()));
    ASSERT_TRUE(s_val);
    ASSERT_EQ(SR_UINT8_T, s_val->type());
    EXPECT_EQ(8, s_val->data()->get_uint8());
    s_val.reset();

    // Unsigned 16 bit integer.
    xpath = "/keatest-module:main/ui16";
    elem = Element::create(16);
    EXPECT_NO_THROW(t_obj->setItem(xpath, elem, SR_UINT16_T));
    EXPECT_NO_THROW(s_val = sess->get_item(xpath.c_str()));
    ASSERT_TRUE(s_val);
    ASSERT_EQ(SR_UINT16_T, s_val->type());
    EXPECT_EQ(16, s_val->data()->get_uint16());
    s_val.reset();

    // Unsigned 32 bit integer.
    xpath = "/keatest-module:main/ui32";
    elem = Element::create(32);
    EXPECT_NO_THROW(t_obj->setItem(xpath, elem, SR_UINT32_T));
    EXPECT_NO_THROW(s_val = sess->get_item(xpath.c_str()));
    ASSERT_TRUE(s_val);
    ASSERT_EQ(SR_UINT32_T, s_val->type());
    EXPECT_EQ(32, s_val->data()->get_uint32());
    s_val.reset();

    // Signed 8 bit integer.
    xpath = "/keatest-module:main/i8";
    elem = Element::create(8);
    EXPECT_NO_THROW(t_obj->setItem(xpath, elem, SR_INT8_T));
    EXPECT_NO_THROW(s_val = sess->get_item(xpath.c_str()));
    ASSERT_TRUE(s_val);
    ASSERT_EQ(SR_INT8_T, s_val->type());
    EXPECT_EQ(8, s_val->data()->get_int8());
    s_val.reset();

    // Signed 16 bit integer.
    xpath = "/keatest-module:main/i16";
    elem = Element::create(16);
    EXPECT_NO_THROW(t_obj->setItem(xpath, elem, SR_INT16_T));
    EXPECT_NO_THROW(s_val = sess->get_item(xpath.c_str()));
    ASSERT_TRUE(s_val);
    ASSERT_EQ(SR_INT16_T, s_val->type());
    EXPECT_EQ(16, s_val->data()->get_int16());
    s_val.reset();

    // Signed 32 bit integer.
    xpath = "/keatest-module:main/i32";
    elem = Element::create(32);
    EXPECT_NO_THROW(t_obj->setItem(xpath, elem, SR_INT32_T));
    EXPECT_NO_THROW(s_val = sess->get_item(xpath.c_str()));
    ASSERT_TRUE(s_val);
    ASSERT_EQ(SR_INT32_T, s_val->type());
    EXPECT_EQ(32, s_val->data()->get_int32());
    s_val.reset();

    // Identity reference.
    xpath = "/keatest-module:main/id_ref";
    elem = Element::create(string("keatest-module:id_1"));
    EXPECT_NO_THROW(t_obj->setItem(xpath, elem, SR_IDENTITYREF_T));
    EXPECT_NO_THROW(s_val = sess->get_item(xpath.c_str()));
    ASSERT_TRUE(s_val);
    ASSERT_EQ(SR_IDENTITYREF_T, s_val->type());
    EXPECT_EQ("keatest-module:id_1", string(s_val->data()->get_identityref()));
    s_val.reset();

    // Enumeration item.
    xpath = "/keatest-module:main/enum";
    elem = Element::create(string("maybe"));
    EXPECT_NO_THROW(t_obj->setItem(xpath, elem, SR_ENUM_T));
    EXPECT_NO_THROW(s_val = sess->get_item(xpath.c_str()));
    ASSERT_TRUE(s_val);
    ASSERT_EQ(SR_ENUM_T, s_val->type());
    EXPECT_EQ("maybe", string(s_val->data()->get_enum()));
    s_val.reset();

    // Binary.
    xpath = "/keatest-module:main/raw";
    elem = Element::create(string("foobar"));
    EXPECT_NO_THROW(t_obj->setItem(xpath, elem, SR_BINARY_T));
    EXPECT_NO_THROW(s_val = sess->get_item(xpath.c_str()));
    ASSERT_TRUE(s_val);
    ASSERT_EQ(SR_BINARY_T, s_val->type());
    EXPECT_EQ("Zm9vYmFy", string(s_val->data()->get_binary()));
    s_val.reset();

    // Decimal 64.
    xpath = "/keatest-module:main/dec64";
    double d64(9.85);
    elem = Element::create(d64);
    EXPECT_NO_THROW(t_obj->setItem(xpath, elem, SR_DECIMAL64_T));
    EXPECT_NO_THROW(s_val = sess->get_item(xpath.c_str()));
    ASSERT_TRUE(s_val);
    ASSERT_EQ(SR_DECIMAL64_T, s_val->type());
    EXPECT_DOUBLE_EQ(d64, s_val->data()->get_decimal64());
    s_val.reset();

    // Leaf-list.
    xpath = "/keatest-module:main/numbers";
    S_Data_Node data_node;
    EXPECT_NO_THROW(data_node = sess->get_subtree(xpath.c_str()));
    EXPECT_FALSE(data_node);
    data_node.reset();

    // Fill it.
    sess->set_item_str(xpath.c_str(), "1");
    sess->set_item_str(xpath.c_str(), "2");
    sess->set_item_str(xpath.c_str(), "3");
    sess->apply_changes();

    // sysrepo_exception: "Invalid argument"
    EXPECT_THROW(data_node = sess->get_subtree(xpath.c_str()),
        sysrepo_exception);
    EXPECT_FALSE(data_node);
    data_node.reset();

    // Clean it.
    EXPECT_NO_THROW(t_obj->delItem(xpath));
    EXPECT_NO_THROW(data_node = sess->get_subtree(xpath.c_str()));
    EXPECT_FALSE(data_node);
    data_node.reset();

    // Bad xpath.
    xpath = "/keatest-module:main/no_such_string";
    elem = Element::create(string("str"));
    try {
        t_obj->setItem(xpath, elem, SR_STRING_T);
        ADD_FAILURE() << "expected exception";
    } catch (const SysrepoError& ex) {
        string expected = "sysrepo error setting item '\"str\"' at '" +
            xpath + "': Invalid argument";
        EXPECT_EQ(expected, string(ex.what()));
    } catch (const std::exception& ex) {
        ADD_FAILURE() << "unexpected exception with: " << ex.what();
    }

    // Bad type.
    xpath = "/keatest-module:main/string";
    elem = Element::create(true);
    try {
        t_obj->setItem(xpath, elem, SR_BOOL_T);
    } catch (const SysrepoError& ex) {
        ADD_FAILURE() << "unexpected exception with: " << ex.what();
    } catch (const std::exception& ex) {
        ADD_FAILURE() << "unexpected exception with: " << ex.what();
    }

    // In sysrepo 1.x, set_item() is based on set_item_str() which sets the
    // value in textual format. After setting a value with SR_BOOL_T, it's value
    // is now "true". :)
    elem = t_obj->getItem(xpath);
    ASSERT_TRUE(elem);
    EXPECT_EQ(elem->getType(), Element::string);
    EXPECT_EQ(elem->str(), "\"true\"");

    // Delete (twice).
    xpath = "/keatest-module:main/string";
    EXPECT_NO_THROW(s_val = sess->get_item(xpath.c_str()));
    EXPECT_TRUE(s_val);
    s_val.reset();
    EXPECT_NO_THROW(t_obj->delItem(xpath));

    // sysrepo_exception: "Item not found"
    EXPECT_THROW(s_val = sess->get_item(xpath.c_str()), sysrepo_exception);
    EXPECT_FALSE(s_val);
    EXPECT_NO_THROW(t_obj->delItem(xpath));
}

// Test yang list item retrieval.
TEST(TranslatorBasicTest, list) {
    // Get a translator object to play with.
    S_Connection conn(std::make_shared<Connection>());
    S_Session sess(new Session(conn, SR_DS_CANDIDATE));
    boost::scoped_ptr<TranslatorBasic> t_obj;
    ASSERT_NO_THROW_LOG(t_obj.reset(new TranslatorBasic(sess, "")));
    string xpath;

    // Empty list.
    ElementPtr element;
    EXPECT_NO_THROW(element = t_obj->getItem("/keatest-module:container/list"));
    EXPECT_FALSE(element);
    element.reset();

    // Retried with a filled list.
    xpath = "/keatest-module:container/list[key1='key1'][key2='key2']/leaf";
    S_Val s_val(new Val("Leaf value"));
    EXPECT_NO_THROW(sess->set_item(xpath.c_str(), s_val));
    EXPECT_NO_THROW(element = t_obj->getItem("/keatest-module:container/list"));
    ASSERT_TRUE(element);
    EXPECT_NO_THROW(element = t_obj->getItem("/keatest-module:container/list[key1='key1'][key2='key2']"));
    ASSERT_TRUE(element);
}

} // anonymous namespace
