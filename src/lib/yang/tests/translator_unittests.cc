// Copyright (C) 2018-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <testutils/gtest_utils.h>
#include <yang/translator.h>
#include <yang/tests/sysrepo_setup.h>

#include <gtest/gtest.h>

using namespace std;
using namespace isc;
using namespace isc::data;
using namespace isc::yang;
using namespace isc::yang::test;
using namespace libyang;
using namespace sysrepo;

struct TranslatorBasicTest : ::testing::Test {
    void SetUp() override {
        SysrepoSetup::cleanSharedMemory();
        cleanUp();
    }

    void TearDown() override {
        cleanUp();
        SysrepoSetup::cleanSharedMemory();
    }

private:
    void cleanUp() {
        Session session(sysrepo::Connection{}.sessionStart());
        session.switchDatastore(sysrepo::Datastore::Candidate);
        session.deleteItem("/keatest-module:container");
        session.deleteItem("/keatest-module:kernel-modules");
        session.deleteItem("/keatest-module:list");
        session.deleteItem("/keatest-module:main");
        session.deleteItem("/keatest-module:presence-container");
        session.applyChanges();
    }
};  // TranslatorBasicTest

namespace {

// Test constructor.
TEST_F(TranslatorBasicTest, constructor) {
    // Get a session.
    Session sess(Connection{}.sessionStart());
    sess.switchDatastore(sysrepo::Datastore::Candidate);
    // Get a translator object.
    std::unique_ptr<TranslatorBasic> t_obj;
    EXPECT_NO_THROW_LOG(t_obj.reset(new TranslatorBasic(sess, "")));
}

// Test basic YANG to JSON value conversion using sysrepo test models.
TEST_F(TranslatorBasicTest, getItem) {
    // Get a translator object to play with.
    Session sess(Connection{}.sessionStart());
    sess.switchDatastore(sysrepo::Datastore::Candidate);
    std::unique_ptr<TranslatorBasic> t_obj;
    ASSERT_NO_THROW_LOG(t_obj.reset(new TranslatorBasic(sess, "")));
    string value;
    ConstElementPtr elem;
    string xpath;

    // String.
    xpath = "/keatest-module:main/string";
    value = "str";
    EXPECT_NO_THROW_LOG(sess.setItem(xpath, value));
    EXPECT_NO_THROW_LOG(elem = t_obj->getItem(xpath));
    ASSERT_TRUE(elem);
    ASSERT_EQ(Element::string, elem->getType());
    EXPECT_EQ("str", elem->stringValue());
    elem.reset();

    // Bool.
    xpath = "/keatest-module:main/boolean";
    value = "true";
    EXPECT_NO_THROW_LOG(sess.setItem(xpath, value));
    EXPECT_NO_THROW_LOG(elem = t_obj->getItem(xpath));
    ASSERT_TRUE(elem);
    ASSERT_EQ(Element::boolean, elem->getType());
    EXPECT_TRUE(elem->boolValue());
    elem.reset();

    // Unsigned 8 bit integer.
    xpath = "/keatest-module:main/ui8";
    uint8_t u8(8);
    value = to_string(u8);
    EXPECT_NO_THROW_LOG(sess.setItem(xpath, value));
    EXPECT_NO_THROW_LOG(elem = t_obj->getItem(xpath));
    ASSERT_TRUE(elem);
    ASSERT_EQ(Element::integer, elem->getType());
    EXPECT_EQ(8, elem->intValue());
    elem.reset();

    // Unsigned 16 bit integer.
    xpath = "/keatest-module:main/ui16";
    uint16_t u16(16);
    value = to_string(u16);
    EXPECT_NO_THROW_LOG(sess.setItem(xpath, value));
    EXPECT_NO_THROW_LOG(elem = t_obj->getItem(xpath));
    ASSERT_TRUE(elem);
    ASSERT_EQ(Element::integer, elem->getType());
    EXPECT_EQ(16, elem->intValue());
    elem.reset();

    // Unsigned 32 bit integer.
    xpath = "/keatest-module:main/ui32";
    uint32_t u32(32);
    value = to_string(u32);
    EXPECT_NO_THROW_LOG(sess.setItem(xpath, value));
    EXPECT_NO_THROW_LOG(elem = t_obj->getItem(xpath));
    ASSERT_TRUE(elem);
    ASSERT_EQ(Element::integer, elem->getType());
    EXPECT_EQ(32, elem->intValue());
    elem.reset();

    // Signed 8 bit integer.
    xpath = "/keatest-module:main/i8";
    int8_t s8(8);
    value = to_string(s8);
    EXPECT_NO_THROW_LOG(sess.setItem(xpath, value));
    EXPECT_NO_THROW_LOG(elem = t_obj->getItem(xpath));
    ASSERT_TRUE(elem);
    ASSERT_EQ(Element::integer, elem->getType());
    EXPECT_EQ(8, elem->intValue());
    elem.reset();

    // Signed 16 bit integer.
    xpath = "/keatest-module:main/i16";
    int16_t s16(16);
    value = to_string(s16);
    EXPECT_NO_THROW_LOG(sess.setItem(xpath, value));
    EXPECT_NO_THROW_LOG(elem = t_obj->getItem(xpath));
    ASSERT_TRUE(elem);
    ASSERT_EQ(Element::integer, elem->getType());
    EXPECT_EQ(16, elem->intValue());
    elem.reset();

    // Signed 32 bit integer.
    xpath = "/keatest-module:main/i32";
    int32_t s32(32);
    value = to_string(s32);
    EXPECT_NO_THROW_LOG(sess.setItem(xpath, value));
    EXPECT_NO_THROW_LOG(elem = t_obj->getItem(xpath));
    ASSERT_TRUE(elem);
    ASSERT_EQ(Element::integer, elem->getType());
    EXPECT_EQ(32, elem->intValue());
    elem.reset();

    // Identity reference.
    xpath = "/keatest-module:main/id_ref";
    value = "keatest-module:id_1";
    EXPECT_NO_THROW_LOG(sess.setItem(xpath, value));
    EXPECT_NO_THROW_LOG(elem = t_obj->getItem(xpath));
    ASSERT_TRUE(elem);
    ASSERT_EQ(Element::string, elem->getType());
    EXPECT_EQ("keatest-module:id_1", elem->stringValue());
    elem.reset();

    // Enumeration item.
    xpath = "/keatest-module:main/enum";
    value = "maybe";
    EXPECT_NO_THROW_LOG(sess.setItem(xpath, value));
    EXPECT_NO_THROW_LOG(elem = t_obj->getItem(xpath));
    ASSERT_TRUE(elem);
    ASSERT_EQ(Element::string, elem->getType());
    EXPECT_EQ("maybe", elem->stringValue());
    elem.reset();

    // Binary.
    xpath = "/keatest-module:main/raw";
    value = "Zm9vYmFy";
    EXPECT_NO_THROW_LOG(sess.setItem(xpath, value));
    EXPECT_NO_THROW_LOG(elem = t_obj->getItem(xpath));
    ASSERT_TRUE(elem);
    ASSERT_EQ(Element::string, elem->getType());
    EXPECT_EQ("foobar", elem->stringValue());
    elem.reset();

    // Leaf-list: not yet exist.
    xpath = "/keatest-module:main/numbers";
    EXPECT_NO_THROW_LOG(elem = t_obj->getItem(xpath));
    EXPECT_FALSE(elem);
    elem.reset();

    // No easy way to create it empty.

    // Leaf-list: 1, 2 and 3.
    u8 = 1;
    value = to_string(u8);
    EXPECT_NO_THROW_LOG(sess.setItem(xpath, value));
    u8 = 2;
    value = to_string(u8);
    EXPECT_NO_THROW_LOG(sess.setItem(xpath, value));
    u8 = 3;
    value = to_string(u8);
    EXPECT_NO_THROW_LOG(sess.setItem(xpath, value));
    EXPECT_NO_THROW_LOG(elem = t_obj->getItem(xpath));
    ASSERT_TRUE(elem);
    ASSERT_EQ(Element::list, elem->getType());
    EXPECT_EQ(3, elem->size());
    EXPECT_EQ("[ 1, 2, 3 ]", elem->str());
    elem.reset();

    // Unknown / unsupported.
    xpath = "/keatest-module:main/dec64";
    value = to_string(9.85);
    EXPECT_NO_THROW_LOG(sess.setItem(xpath, value));
    EXPECT_NO_THROW_LOG(elem = t_obj->getItem(xpath));
    ASSERT_TRUE(elem);
    ASSERT_EQ(Element::real, elem->getType());
    EXPECT_EQ("9.85", elem->str());
    elem.reset();

    // Not found.
    xpath = "/keatest-module:main/no_such_string";
    EXPECT_THROW_MSG(t_obj->deleteItem(xpath), NetconfError,
                     "sysrepo error getting item at '/keatest-module:main/no_such_string': "
                     "Couldn't find schema node: /keatest-module:main/no_such_string");
    EXPECT_THROW_MSG(elem = t_obj->getItem(xpath), NetconfError,
                     "sysrepo error getting item at '/keatest-module:main/no_such_string': "
                     "Couldn't find schema node: /keatest-module:main/no_such_string");
    EXPECT_FALSE(elem);
    elem.reset();

    // Check error.
    xpath = "null";
    EXPECT_THROW_MSG(elem = t_obj->getItem(xpath), NetconfError,
                     "sysrepo error getting item at 'null': Couldn't find schema node: null");
    EXPECT_FALSE(elem);
}

// Test JSON to basic YANG value conversion using the static method.
TEST_F(TranslatorBasicTest, valueTo) {
    optional<string> value;

    // Null.
    ConstElementPtr elem;
    EXPECT_NO_THROW_LOG(value = TranslatorBasic::translate(elem, LeafBaseType::String));
    EXPECT_EQ(nullopt, value);
    EXPECT_FALSE(elem);

    // Container.
    elem = Element::createMap();
    EXPECT_THROW_MSG(TranslatorBasic::translate(elem, LeafBaseType::Unknown), NotImplemented,
                     "TranslatorBasic::value(): map element");

    // List.
    elem = Element::createList();
    EXPECT_THROW_MSG(TranslatorBasic::translate(elem, LeafBaseType::Unknown), NotImplemented,
                     "TranslatorBasic::value(): list element");

    // String.
    string str("foo");
    elem = Element::create(str);
    EXPECT_NO_THROW_LOG(value = TranslatorBasic::translate(elem, LeafBaseType::String));
    EXPECT_EQ(elem->stringValue(), value);

    // Bool.
    elem = Element::create(false);
    EXPECT_NO_THROW_LOG(value = TranslatorBasic::translate(elem, LeafBaseType::Bool));
    EXPECT_EQ(elem->str(), value);

    // Unsigned 8 bit integer.
    elem = Element::create(123);
    EXPECT_NO_THROW_LOG(value = TranslatorBasic::translate(elem, LeafBaseType::Uint8));
    EXPECT_EQ(elem->str(), value);
    elem.reset();

    // Unsigned 16 bit integer.
    elem = Element::create(12345);
    EXPECT_NO_THROW_LOG(value = TranslatorBasic::translate(elem, LeafBaseType::Uint16));
    EXPECT_EQ(elem->str(), value);
    elem.reset();

    // Unsigned 32 bit integer.
    elem = Element::create(123456789);
    EXPECT_NO_THROW_LOG(value = TranslatorBasic::translate(elem, LeafBaseType::Uint32));
    EXPECT_EQ(elem->str(), value);
    elem.reset();

    // Signed 8 bit integer.
    elem = Element::create(-123);
    EXPECT_NO_THROW_LOG(value = TranslatorBasic::translate(elem, LeafBaseType::Int8));
    EXPECT_EQ(elem->str(), value);
    elem.reset();

    // Signed 16 bit integer.
    elem = Element::create(-12345);
    EXPECT_NO_THROW_LOG(value = TranslatorBasic::translate(elem, LeafBaseType::Int16));
    EXPECT_EQ(elem->str(), value);
    elem.reset();

    // Signed 32 bit integer.
    elem = Element::create(-123456789);
    EXPECT_NO_THROW_LOG(value = TranslatorBasic::translate(elem, LeafBaseType::Int32));
    EXPECT_EQ(elem->str(), value);
    elem.reset();

    // Identity reference.
    elem = Element::create(str);
    EXPECT_NO_THROW_LOG(value = TranslatorBasic::translate(elem, LeafBaseType::IdentityRef));
    EXPECT_EQ(elem->stringValue(), value);

    // Enumeration item.
    EXPECT_NO_THROW_LOG(value = TranslatorBasic::translate(elem, LeafBaseType::Enum));
    EXPECT_EQ(elem->stringValue(), value);

    // Binary.
    elem = Element::create(string("foobar"));
    EXPECT_NO_THROW_LOG(value = TranslatorBasic::translate(elem, LeafBaseType::Binary));
    EXPECT_EQ("Zm9vYmFy", value);

    // Decimal 64.
    double d64(.1234);
    elem = Element::create(d64);
    EXPECT_NO_THROW_LOG(value = TranslatorBasic::translate(elem, LeafBaseType::Dec64));
    EXPECT_EQ(elem->str(), value);
}

// Test JSON to basic YANG value conversion using sysrepo test models.
TEST_F(TranslatorBasicTest, setItem) {
    // Get a translator object to play with.
    Session sess(Connection{}.sessionStart());
    sess.switchDatastore(sysrepo::Datastore::Candidate);
    std::unique_ptr<TranslatorBasic> t_obj;
    ASSERT_NO_THROW_LOG(t_obj.reset(new TranslatorBasic(sess, "")));

    ElementPtr elem;
    string xpath;

    // String.
    optional<DataNode> data_node;
    xpath = "/keatest-module:main/string";
    elem = Element::create(string("str"));
    EXPECT_NO_THROW_LOG(t_obj->setItem(xpath, elem, LeafBaseType::String));
    EXPECT_NO_THROW_LOG(data_node = sess.getData(xpath));
    ASSERT_TRUE(data_node);
    EXPECT_NO_THROW_LOG(data_node = data_node->findPath(xpath));
    ASSERT_TRUE(data_node);
    ASSERT_EQ(LeafBaseType::String, data_node->schema().asLeaf().valueType().base());
    EXPECT_EQ(elem->stringValue(), string(data_node->asTerm().valueStr()));

    // Bool.
    xpath = "/keatest-module:main/boolean";
    elem = Element::create(true);
    EXPECT_NO_THROW_LOG(t_obj->setItem(xpath, elem, LeafBaseType::Bool));
    EXPECT_NO_THROW_LOG(data_node = sess.getData(xpath));
    ASSERT_TRUE(data_node);
    EXPECT_NO_THROW_LOG(data_node = data_node->findPath(xpath));
    ASSERT_TRUE(data_node);
    ASSERT_EQ(LeafBaseType::Bool, data_node->schema().asLeaf().valueType().base());
    EXPECT_EQ(elem->str(), string(data_node->asTerm().valueStr()));

    // Unsigned 8 bit integer.
    xpath = "/keatest-module:main/ui8";
    elem = Element::create(8);
    EXPECT_NO_THROW_LOG(t_obj->setItem(xpath, elem, LeafBaseType::Uint8));
    EXPECT_NO_THROW_LOG(data_node = sess.getData(xpath));
    ASSERT_TRUE(data_node);
    EXPECT_NO_THROW_LOG(data_node = data_node->findPath(xpath));
    ASSERT_TRUE(data_node);
    ASSERT_EQ(LeafBaseType::Uint8, data_node->schema().asLeaf().valueType().base());
    EXPECT_EQ(elem->str(), string(data_node->asTerm().valueStr()));

    // Unsigned 16 bit integer.
    xpath = "/keatest-module:main/ui16";
    elem = Element::create(16);
    EXPECT_NO_THROW_LOG(t_obj->setItem(xpath, elem, LeafBaseType::Uint16));
    EXPECT_NO_THROW_LOG(data_node = sess.getData(xpath));
    ASSERT_TRUE(data_node);
    EXPECT_NO_THROW_LOG(data_node = data_node->findPath(xpath));
    ASSERT_TRUE(data_node);
    ASSERT_EQ(LeafBaseType::Uint16, data_node->schema().asLeaf().valueType().base());
    EXPECT_EQ(elem->str(), string(data_node->asTerm().valueStr()));

    // Unsigned 32 bit integer.
    xpath = "/keatest-module:main/ui32";
    elem = Element::create(32);
    EXPECT_NO_THROW_LOG(t_obj->setItem(xpath, elem, LeafBaseType::Uint32));
    EXPECT_NO_THROW_LOG(data_node = sess.getData(xpath));
    ASSERT_TRUE(data_node);
    EXPECT_NO_THROW_LOG(data_node = data_node->findPath(xpath));
    ASSERT_TRUE(data_node);
    ASSERT_EQ(LeafBaseType::Uint32, data_node->schema().asLeaf().valueType().base());
    EXPECT_EQ(elem->str(), string(data_node->asTerm().valueStr()));

    // Signed 8 bit integer.
    xpath = "/keatest-module:main/i8";
    elem = Element::create(8);
    EXPECT_NO_THROW_LOG(t_obj->setItem(xpath, elem, LeafBaseType::Int8));
    EXPECT_NO_THROW_LOG(data_node = sess.getData(xpath));
    ASSERT_TRUE(data_node);
    EXPECT_NO_THROW_LOG(data_node = data_node->findPath(xpath));
    ASSERT_TRUE(data_node);
    ASSERT_EQ(LeafBaseType::Int8, data_node->schema().asLeaf().valueType().base());
    EXPECT_EQ(elem->str(), string(data_node->asTerm().valueStr()));

    // Signed 16 bit integer.
    xpath = "/keatest-module:main/i16";
    elem = Element::create(16);
    EXPECT_NO_THROW_LOG(t_obj->setItem(xpath, elem, LeafBaseType::Int16));
    EXPECT_NO_THROW_LOG(data_node = sess.getData(xpath));
    ASSERT_TRUE(data_node);
    EXPECT_NO_THROW_LOG(data_node = data_node->findPath(xpath));
    ASSERT_TRUE(data_node);
    ASSERT_EQ(LeafBaseType::Int16, data_node->schema().asLeaf().valueType().base());
    EXPECT_EQ(elem->str(), string(data_node->asTerm().valueStr()));

    // Signed 32 bit integer.
    xpath = "/keatest-module:main/i32";
    elem = Element::create(32);
    EXPECT_NO_THROW_LOG(t_obj->setItem(xpath, elem, LeafBaseType::Int32));
    EXPECT_NO_THROW_LOG(data_node = sess.getData(xpath));
    ASSERT_TRUE(data_node);
    EXPECT_NO_THROW_LOG(data_node = data_node->findPath(xpath));
    ASSERT_TRUE(data_node);
    ASSERT_EQ(LeafBaseType::Int32, data_node->schema().asLeaf().valueType().base());
    EXPECT_EQ(elem->str(), string(data_node->asTerm().valueStr()));

    // Identity reference.
    xpath = "/keatest-module:main/id_ref";
    elem = Element::create(string("keatest-module:id_1"));
    EXPECT_NO_THROW_LOG(t_obj->setItem(xpath, elem, LeafBaseType::IdentityRef));
    EXPECT_NO_THROW_LOG(data_node = sess.getData(xpath));
    ASSERT_TRUE(data_node);
    EXPECT_NO_THROW_LOG(data_node = data_node->findPath(xpath));
    ASSERT_TRUE(data_node);
    ASSERT_EQ(LeafBaseType::IdentityRef, data_node->schema().asLeaf().valueType().base());
    EXPECT_EQ(elem->stringValue(), string(data_node->asTerm().valueStr()));

    // Enumeration item.
    xpath = "/keatest-module:main/enum";
    elem = Element::create(string("maybe"));
    EXPECT_NO_THROW_LOG(t_obj->setItem(xpath, elem, LeafBaseType::Enum));
    EXPECT_NO_THROW_LOG(data_node = sess.getData(xpath));
    ASSERT_TRUE(data_node);
    EXPECT_NO_THROW_LOG(data_node = data_node->findPath(xpath));
    ASSERT_TRUE(data_node);
    ASSERT_EQ(LeafBaseType::Enum, data_node->schema().asLeaf().valueType().base());
    EXPECT_EQ(elem->stringValue(), string(data_node->asTerm().valueStr()));

    // Binary.
    xpath = "/keatest-module:main/raw";
    elem = Element::create(string("foobar"));
    EXPECT_NO_THROW_LOG(t_obj->setItem(xpath, elem, LeafBaseType::Binary));
    EXPECT_NO_THROW_LOG(data_node = sess.getData(xpath));
    ASSERT_TRUE(data_node);
    EXPECT_NO_THROW_LOG(data_node = data_node->findPath(xpath));
    ASSERT_TRUE(data_node);
    ASSERT_EQ(LeafBaseType::Binary, data_node->schema().asLeaf().valueType().base());
    EXPECT_EQ("Zm9vYmFy", string(data_node->asTerm().valueStr()));

    // Decimal 64.
    xpath = "/keatest-module:main/dec64";
    double d64(9.85);
    elem = Element::create(d64);
    EXPECT_NO_THROW_LOG(t_obj->setItem(xpath, elem, LeafBaseType::Dec64));
    EXPECT_NO_THROW_LOG(data_node = sess.getData(xpath));
    ASSERT_TRUE(data_node);
    EXPECT_NO_THROW_LOG(data_node = data_node->findPath(xpath));
    ASSERT_TRUE(data_node);
    ASSERT_EQ(LeafBaseType::Dec64, data_node->schema().asLeaf().valueType().base());
    EXPECT_EQ(elem->str(), string(data_node->asTerm().valueStr()));

    // Leaf-list.
    xpath = "/keatest-module:main/numbers";
    EXPECT_NO_THROW_LOG(t_obj->setItem(xpath, Element::fromJSON("1"), LeafBaseType::Uint8));
    EXPECT_NO_THROW_LOG(t_obj->setItem(xpath, Element::fromJSON("2"), LeafBaseType::Uint8));
    EXPECT_NO_THROW_LOG(t_obj->setItem(xpath, Element::fromJSON("3"), LeafBaseType::Uint8));
    ElementPtr got(t_obj->getItem(xpath));
    ASSERT_EQ(LeafBaseType::Dec64, data_node->schema().asLeaf().valueType().base());
    EXPECT_EQ("[ 1, 2, 3 ]", got->str());

    // Clean it.
    EXPECT_NO_THROW_LOG(t_obj->deleteItem(xpath));
    EXPECT_NO_THROW_LOG(data_node = sess.getData(xpath));
    EXPECT_FALSE(data_node);
    data_node.reset();

    // Bad xpath.
    xpath = "/keatest-module:main/no_such_string";
    elem = Element::create(string("str"));
    EXPECT_THROW_MSG(t_obj->setItem(xpath, elem, LeafBaseType::String), NetconfError,
                     "sysrepo error setting item '\"str\"' at '" + xpath +
                     "': Session::setItem: Couldn't set "
                     "'/keatest-module:main/no_such_string' to 'str': SR_ERR_INVAL_ARG");

    // Bad type.
    xpath = "/keatest-module:main/string";
    elem = Element::create(true);
    EXPECT_NO_THROW_LOG(t_obj->setItem(xpath, elem, LeafBaseType::Bool));

    elem = t_obj->getItem(xpath);
    ASSERT_TRUE(elem);
    EXPECT_EQ(elem->getType(), Element::string);
    EXPECT_EQ(elem->str(), "\"true\"");

    // Delete (twice).
    xpath = "/keatest-module:main/string";
    EXPECT_NO_THROW_LOG(data_node = sess.getData(xpath));
    EXPECT_TRUE(data_node);
    EXPECT_NO_THROW_LOG(data_node = data_node->findPath(xpath));
    EXPECT_TRUE(data_node);
    ASSERT_TRUE(NodeType::Leaf == data_node->schema().nodeType());
    EXPECT_EQ("true", data_node->asTerm().valueStr());
    EXPECT_NO_THROW_LOG(t_obj->deleteItem(xpath));
    EXPECT_NO_THROW_LOG(data_node = sess.getData(xpath));
    EXPECT_FALSE(data_node);
    EXPECT_NO_THROW_LOG(t_obj->deleteItem(xpath));
    EXPECT_NO_THROW_LOG(data_node = sess.getData(xpath));
    EXPECT_FALSE(data_node);
}

// Test YANG list item retrieval.
TEST_F(TranslatorBasicTest, list) {
    // Get a translator object to play with.
    Session sess(Connection{}.sessionStart());
    sess.switchDatastore(sysrepo::Datastore::Candidate);
    std::unique_ptr<TranslatorBasic> t_obj;
    ASSERT_NO_THROW_LOG(t_obj.reset(new TranslatorBasic(sess, "")));
    string xpath;

    // Empty list.
    ElementPtr element;
    EXPECT_NO_THROW_LOG(element = t_obj->getItem("/keatest-module:container/list"));
    EXPECT_FALSE(element);
    element.reset();

    // Retried with a filled list.
    xpath = "/keatest-module:container/list[key1='key1'][key2='key2']/leaf";
    element = Element::create("Leaf value");
    EXPECT_NO_THROW_LOG(t_obj->setItem(xpath, element, LeafBaseType::String));
    EXPECT_NO_THROW_LOG(element = t_obj->getItem("/keatest-module:container/list"));
    EXPECT_FALSE(element);
    EXPECT_NO_THROW_LOG(element = t_obj->getItem("/keatest-module:container/list[key1='key1'][key2='key2']"));
    EXPECT_FALSE(element);
}

}  // anonymous namespace
