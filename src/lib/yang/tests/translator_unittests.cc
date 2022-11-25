// Copyright (C) 2018-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <gtest/gtest.h>

#include <testutils/gtest_utils.h>
#include <yang/tests/sysrepo_setup.h>
#include <yang/translator.h>

using namespace std;
using namespace isc;
using namespace isc::data;
using namespace isc::yang;
using namespace isc::yang::test;
using namespace libyang;
using namespace sysrepo;

struct TranslatorTest : ::testing::Test {
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
};  // TranslatorTest

namespace {

// Test constructor.
TEST_F(TranslatorTest, constructor) {
    // Get a session.
    Session sess(Connection{}.sessionStart());
    sess.switchDatastore(sysrepo::Datastore::Candidate);
    // Get a translator object.
    unique_ptr<Translator> translator;
    EXPECT_NO_THROW_LOG(translator.reset(new Translator(sess, "")));
}

// Test basic YANG to JSON value conversion using sysrepo test models.
TEST_F(TranslatorTest, getItem) {
    // Get a translator object to play with.
    Session sess(Connection{}.sessionStart());
    sess.switchDatastore(sysrepo::Datastore::Candidate);
    unique_ptr<Translator> translator;
    ASSERT_NO_THROW_LOG(translator.reset(new Translator(sess, "")));
    string value;
    ConstElementPtr element;
    string xpath;

    // String.
    xpath = "/keatest-module:main/string";
    value = "str";
    EXPECT_NO_THROW_LOG(sess.setItem(xpath, value));
    sess.applyChanges();
    EXPECT_NO_THROW_LOG(element = translator->getItemFromAbsoluteXpath(xpath));
    ASSERT_TRUE(element);
    ASSERT_EQ(Element::string, element->getType());
    EXPECT_EQ("str", element->stringValue());
    element.reset();

    // Bool.
    xpath = "/keatest-module:main/boolean";
    value = "true";
    EXPECT_NO_THROW_LOG(sess.setItem(xpath, value));
    sess.applyChanges();
    EXPECT_NO_THROW_LOG(element = translator->getItemFromAbsoluteXpath(xpath));
    ASSERT_TRUE(element);
    ASSERT_EQ(Element::boolean, element->getType());
    EXPECT_TRUE(element->boolValue());
    element.reset();

    // Unsigned 8 bit integer.
    xpath = "/keatest-module:main/ui8";
    uint8_t u8(8);
    value = to_string(u8);
    EXPECT_NO_THROW_LOG(sess.setItem(xpath, value));
    sess.applyChanges();
    EXPECT_NO_THROW_LOG(element = translator->getItemFromAbsoluteXpath(xpath));
    ASSERT_TRUE(element);
    ASSERT_EQ(Element::integer, element->getType());
    EXPECT_EQ(8, element->intValue());
    element.reset();

    // Unsigned 16 bit integer.
    xpath = "/keatest-module:main/ui16";
    uint16_t u16(16);
    value = to_string(u16);
    EXPECT_NO_THROW_LOG(sess.setItem(xpath, value));
    sess.applyChanges();
    EXPECT_NO_THROW_LOG(element = translator->getItemFromAbsoluteXpath(xpath));
    ASSERT_TRUE(element);
    ASSERT_EQ(Element::integer, element->getType());
    EXPECT_EQ(16, element->intValue());
    element.reset();

    // Unsigned 32 bit integer.
    xpath = "/keatest-module:main/ui32";
    uint32_t u32(32);
    value = to_string(u32);
    EXPECT_NO_THROW_LOG(sess.setItem(xpath, value));
    sess.applyChanges();
    EXPECT_NO_THROW_LOG(element = translator->getItemFromAbsoluteXpath(xpath));
    ASSERT_TRUE(element);
    ASSERT_EQ(Element::integer, element->getType());
    EXPECT_EQ(32, element->intValue());
    element.reset();

    // Unsigned 64 bit integer.
    xpath = "/keatest-module:main/ui64";
    uint64_t u64(64);
    value = to_string(u64);
    EXPECT_NO_THROW_LOG(sess.setItem(xpath, value));
    sess.applyChanges();
    EXPECT_NO_THROW_LOG(element = translator->getItemFromAbsoluteXpath(xpath));
    ASSERT_TRUE(element);
    ASSERT_EQ(Element::integer, element->getType());
    EXPECT_EQ(64, element->intValue());
    element.reset();

    // Empty.
    xpath = "/keatest-module:main/empty";
    value = string();
    EXPECT_NO_THROW_LOG(sess.setItem(xpath, value));
    sess.applyChanges();
    EXPECT_NO_THROW_LOG(element = translator->getItemFromAbsoluteXpath(xpath));
    ASSERT_TRUE(element);
    ASSERT_EQ(Element::string, element->getType());
    EXPECT_EQ(string(), element->stringValue());
    element.reset();

    // Signed 8 bit integer.
    xpath = "/keatest-module:main/i8";
    int8_t s8(8);
    value = to_string(s8);
    EXPECT_NO_THROW_LOG(sess.setItem(xpath, value));
    sess.applyChanges();
    EXPECT_NO_THROW_LOG(element = translator->getItemFromAbsoluteXpath(xpath));
    ASSERT_TRUE(element);
    ASSERT_EQ(Element::integer, element->getType());
    EXPECT_EQ(8, element->intValue());
    element.reset();

    // Signed 16 bit integer.
    xpath = "/keatest-module:main/i16";
    int16_t s16(16);
    value = to_string(s16);
    EXPECT_NO_THROW_LOG(sess.setItem(xpath, value));
    sess.applyChanges();
    EXPECT_NO_THROW_LOG(element = translator->getItemFromAbsoluteXpath(xpath));
    ASSERT_TRUE(element);
    ASSERT_EQ(Element::integer, element->getType());
    EXPECT_EQ(16, element->intValue());
    element.reset();

    // Signed 32 bit integer.
    xpath = "/keatest-module:main/i32";
    int32_t s32(32);
    value = to_string(s32);
    EXPECT_NO_THROW_LOG(sess.setItem(xpath, value));
    sess.applyChanges();
    EXPECT_NO_THROW_LOG(element = translator->getItemFromAbsoluteXpath(xpath));
    ASSERT_TRUE(element);
    ASSERT_EQ(Element::integer, element->getType());
    EXPECT_EQ(32, element->intValue());
    element.reset();

    // Signed 64 bit integer.
    xpath = "/keatest-module:main/i64";
    int64_t s64(64);
    value = to_string(s64);
    EXPECT_NO_THROW_LOG(sess.setItem(xpath, value));
    sess.applyChanges();
    EXPECT_NO_THROW_LOG(element = translator->getItemFromAbsoluteXpath(xpath));
    ASSERT_TRUE(element);
    ASSERT_EQ(Element::integer, element->getType());
    EXPECT_EQ(64, element->intValue());
    element.reset();

    // Identity reference.
    xpath = "/keatest-module:main/id_ref";
    value = "keatest-module:id_1";
    EXPECT_NO_THROW_LOG(sess.setItem(xpath, value));
    sess.applyChanges();
    EXPECT_NO_THROW_LOG(element = translator->getItemFromAbsoluteXpath(xpath));
    ASSERT_TRUE(element);
    ASSERT_EQ(Element::string, element->getType());
    EXPECT_EQ("keatest-module:id_1", element->stringValue());
    element.reset();

    // Enumeration item.
    xpath = "/keatest-module:main/enum";
    value = "maybe";
    EXPECT_NO_THROW_LOG(sess.setItem(xpath, value));
    sess.applyChanges();
    EXPECT_NO_THROW_LOG(element = translator->getItemFromAbsoluteXpath(xpath));
    ASSERT_TRUE(element);
    ASSERT_EQ(Element::string, element->getType());
    EXPECT_EQ("maybe", element->stringValue());
    element.reset();

    // Bits.
    xpath = "/keatest-module:main/options";
    value = "strict recursive logging";
    EXPECT_NO_THROW_LOG(sess.setItem(xpath, value));
    sess.applyChanges();
    EXPECT_NO_THROW_LOG(element = translator->getItemFromAbsoluteXpath(xpath));
    ASSERT_TRUE(element);
    ASSERT_EQ(Element::string, element->getType());
    EXPECT_EQ("strict recursive logging", element->stringValue());
    element.reset();

    // Binary.
    xpath = "/keatest-module:main/raw";
    value = "Zm9vYmFy";
    EXPECT_NO_THROW_LOG(sess.setItem(xpath, value));
    sess.applyChanges();
    EXPECT_NO_THROW_LOG(element = translator->getItemFromAbsoluteXpath(xpath));
    ASSERT_TRUE(element);
    ASSERT_EQ(Element::string, element->getType());
    EXPECT_EQ("foobar", element->stringValue());
    element.reset();

    // Leaf-list: not yet exist.
    xpath = "/keatest-module:main/numbers";
    EXPECT_NO_THROW_LOG(element = translator->getItemFromAbsoluteXpath(xpath));
    EXPECT_FALSE(element);
    element.reset();

    // No easy way to create it empty.

    // Leaf-list: 1, 2 and 3.
    u8 = 1;
    value = to_string(u8);
    EXPECT_NO_THROW_LOG(sess.setItem(xpath, value));
    sess.applyChanges();
    u8 = 2;
    value = to_string(u8);
    EXPECT_NO_THROW_LOG(sess.setItem(xpath, value));
    sess.applyChanges();
    u8 = 3;
    value = to_string(u8);
    EXPECT_NO_THROW_LOG(sess.setItem(xpath, value));
    sess.applyChanges();
    EXPECT_NO_THROW_LOG(element = translator->getItemFromAbsoluteXpath(xpath));
    ASSERT_TRUE(element);
    ASSERT_EQ(Element::list, element->getType());
    EXPECT_EQ(3, element->size());
    EXPECT_EQ("[ 1, 2, 3 ]", element->str());
    element.reset();

    // Instance identifier.
    xpath = "/keatest-module:main/instance_id";
    value = "/keatest-module:main/numbers[.='1']";
    EXPECT_NO_THROW_LOG(sess.setItem(xpath, value));
    sess.applyChanges();
    EXPECT_NO_THROW_LOG(element = translator->getItemFromAbsoluteXpath(xpath));
    ASSERT_TRUE(element);
    ASSERT_EQ(Element::string, element->getType());
    EXPECT_EQ(value, element->stringValue());
    element.reset();

    // Union.
    xpath = "/keatest-module:main/union";
    value = "8";
    EXPECT_NO_THROW_LOG(sess.setItem(xpath, value));
    sess.applyChanges();
    EXPECT_NO_THROW_LOG(element = translator->getItemFromAbsoluteXpath(xpath));
    ASSERT_TRUE(element);
    ASSERT_EQ(Element::string, element->getType());
    EXPECT_EQ(value, element->stringValue());
    element.reset();
    value = "infinity";
    EXPECT_NO_THROW_LOG(sess.setItem(xpath, value));
    sess.applyChanges();
    EXPECT_NO_THROW_LOG(element = translator->getItemFromAbsoluteXpath(xpath));
    ASSERT_TRUE(element);
    ASSERT_EQ(Element::string, element->getType());
    EXPECT_EQ(value, element->stringValue());
    element.reset();

    // Leafref.
    xpath = "/keatest-module:main/leafref-i8";
    value = "9";
    EXPECT_NO_THROW_LOG(sess.setItem(xpath, value));
    sess.applyChanges();
    EXPECT_NO_THROW_LOG(element = translator->getItemFromAbsoluteXpath(xpath));
    ASSERT_TRUE(element);
    ASSERT_EQ(Element::string, element->getType());
    EXPECT_EQ(value, element->stringValue());
    element.reset();

    // Leafref.
    xpath = "/keatest-module:main/leafref-raw";
    value = "ff012345";
    EXPECT_NO_THROW_LOG(sess.setItem(xpath, value));
    sess.applyChanges();
    EXPECT_NO_THROW_LOG(element = translator->getItemFromAbsoluteXpath(xpath));
    ASSERT_TRUE(element);
    ASSERT_EQ(Element::string, element->getType());
    EXPECT_EQ(value, element->stringValue());
    element.reset();

    // Leafref.
    xpath = "/keatest-module:main/leafref-string";
    value = "string through leafref";
    EXPECT_NO_THROW_LOG(sess.setItem(xpath, value));
    sess.applyChanges();
    EXPECT_NO_THROW_LOG(element = translator->getItemFromAbsoluteXpath(xpath));
    ASSERT_TRUE(element);
    ASSERT_EQ(Element::string, element->getType());
    EXPECT_EQ(value, element->stringValue());
    element.reset();

    // Decimal 64.
    xpath = "/keatest-module:main/dec64";
    value = to_string(9.85);
    EXPECT_NO_THROW_LOG(sess.setItem(xpath, value));
    sess.applyChanges();
    EXPECT_NO_THROW_LOG(element = translator->getItemFromAbsoluteXpath(xpath));
    ASSERT_TRUE(element);
    ASSERT_EQ(Element::real, element->getType());
    EXPECT_EQ("9.85", element->str());
    element.reset();

    // Not existing.
    xpath = "/keatest-module:main/no_such_node";
    EXPECT_NO_THROW_LOG(element = translator->getItemFromAbsoluteXpath(xpath));
    EXPECT_FALSE(element);
    element.reset();

    // Check error.
    xpath = "null";
    EXPECT_NO_THROW_LOG(element = translator->getItemFromAbsoluteXpath(xpath));
    EXPECT_FALSE(element);
}

// Check the Translator::deleteItem function.
TEST_F(TranslatorTest, deleteItem) {
    ElementPtr got;
    string xpath;

    // Get a translator object to play with.
    Translator translator(Connection{}.sessionStart(), "keatest-module");

    // Missing schema node
    EXPECT_NO_THROW_LOG(translator.deleteItem("/keatest-module:main/no_such_node"));

    // Existing schema node, but no data
    xpath = "/keatest-module:main/string";
    EXPECT_NO_THROW_LOG(translator.deleteItem(xpath));
    EXPECT_NO_THROW_LOG(got = translator.getItemFromAbsoluteXpath(xpath));
    EXPECT_FALSE(got);
    got.reset();

    // Existing schema node, existing data
    translator.setItem(xpath, Element::create("value"), LeafBaseType::String);
    EXPECT_NO_THROW_LOG(translator.deleteItem(xpath));
    EXPECT_NO_THROW_LOG(got = translator.getItemFromAbsoluteXpath(xpath));
    EXPECT_FALSE(got);
    got.reset();

    // Container schema node, no data
    EXPECT_NO_THROW_LOG(translator.deleteItem("/keatest-module:main"));
    EXPECT_NO_THROW_LOG(got = translator.getItemFromAbsoluteXpath(xpath));
    EXPECT_FALSE(got);
    got.reset();

    // Container schema node, existing data
    translator.setItem(xpath, Element::create("value"), LeafBaseType::String);
    EXPECT_NO_THROW_LOG(translator.deleteItem("/keatest-module:main"));
    EXPECT_NO_THROW_LOG(got = translator.getItemFromAbsoluteXpath(xpath));
    EXPECT_FALSE(got);
    got.reset();
}

// Test JSON to basic YANG value conversion using the static method.
TEST_F(TranslatorTest, valueTo) {
    optional<string> value;

    // Null.
    ConstElementPtr element;
    EXPECT_NO_THROW_LOG(value = Translator::translateToYang(element, LeafBaseType::String));
    EXPECT_EQ(nullopt, value);
    EXPECT_FALSE(element);

    // Container.
    element = Element::createMap();
    EXPECT_THROW_MSG(Translator::translateToYang(element, LeafBaseType::Unknown), NotImplemented,
                     "Translator::value(): map element");

    // List.
    element = Element::createList();
    EXPECT_THROW_MSG(Translator::translateToYang(element, LeafBaseType::Unknown), NotImplemented,
                     "Translator::value(): list element");

    // String.
    string str("foo");
    element = Element::create(str);
    EXPECT_NO_THROW_LOG(value = Translator::translateToYang(element, LeafBaseType::String));
    EXPECT_EQ(element->stringValue(), value);

    // Bool.
    element = Element::create(false);
    EXPECT_NO_THROW_LOG(value = Translator::translateToYang(element, LeafBaseType::Bool));
    EXPECT_EQ(element->str(), value);

    // Unsigned 8 bit integer.
    element = Element::create(123);
    EXPECT_NO_THROW_LOG(value = Translator::translateToYang(element, LeafBaseType::Uint8));
    EXPECT_EQ(element->str(), value);
    element.reset();

    // Unsigned 16 bit integer.
    element = Element::create(12345);
    EXPECT_NO_THROW_LOG(value = Translator::translateToYang(element, LeafBaseType::Uint16));
    EXPECT_EQ(element->str(), value);
    element.reset();

    // Unsigned 32 bit integer.
    element = Element::create(123456789);
    EXPECT_NO_THROW_LOG(value = Translator::translateToYang(element, LeafBaseType::Uint32));
    EXPECT_EQ(element->str(), value);
    element.reset();

    // Unsigned 64 bit integer.
    element = Element::create(int64_t(1234567890123456));
    EXPECT_NO_THROW_LOG(value = Translator::translateToYang(element, LeafBaseType::Uint64));
    EXPECT_EQ("1234567890123456", value);
    element.reset();

    // Signed 8 bit integer.
    element = Element::create(-123);
    EXPECT_NO_THROW_LOG(value = Translator::translateToYang(element, LeafBaseType::Int8));
    EXPECT_EQ(element->str(), value);
    element.reset();

    // Signed 16 bit integer.
    element = Element::create(-12345);
    EXPECT_NO_THROW_LOG(value = Translator::translateToYang(element, LeafBaseType::Int16));
    EXPECT_EQ(element->str(), value);
    element.reset();

    // Signed 32 bit integer.
    element = Element::create(-123456789);
    EXPECT_NO_THROW_LOG(value = Translator::translateToYang(element, LeafBaseType::Int32));
    EXPECT_EQ(element->str(), value);
    element.reset();

    // Signed 64 bit integer.
    element = Element::create(int64_t(-1234567890123456));
    EXPECT_NO_THROW_LOG(value = Translator::translateToYang(element, LeafBaseType::Int64));
    EXPECT_EQ("-1234567890123456", value);
    element.reset();

    // Identity reference.
    element = Element::create(str);
    EXPECT_NO_THROW_LOG(value = Translator::translateToYang(element, LeafBaseType::IdentityRef));
    EXPECT_EQ(element->stringValue(), value);

    // Enumeration item.
    EXPECT_NO_THROW_LOG(value = Translator::translateToYang(element, LeafBaseType::Enum));
    EXPECT_EQ(element->stringValue(), value);

    // Binary.
    element = Element::create("foobar");
    EXPECT_NO_THROW_LOG(value = Translator::translateToYang(element, LeafBaseType::Binary));
    EXPECT_EQ("Zm9vYmFy", value);

    // Bits.
    element = Element::create("foobar");
    EXPECT_NO_THROW_LOG(value = Translator::translateToYang(element, LeafBaseType::Bits));
    EXPECT_EQ(element->stringValue(), value);

    // Decimal 64.
    double d64(.1234);
    element = Element::create(d64);
    EXPECT_NO_THROW_LOG(value = Translator::translateToYang(element, LeafBaseType::Dec64));
    EXPECT_EQ(element->str(), value);

    // Empty.
    element = Element::create(string());
    EXPECT_NO_THROW_LOG(value = Translator::translateToYang(element, LeafBaseType::Empty));
    EXPECT_EQ(element->stringValue(), value);

    // Leafref.
    element = Element::create("leafref");
    EXPECT_NO_THROW_LOG(value = Translator::translateToYang(element, LeafBaseType::Leafref));
    EXPECT_EQ(element->stringValue(), value);

    // Union.
    element = Element::create("union");
    EXPECT_NO_THROW_LOG(value = Translator::translateToYang(element, LeafBaseType::Union));
    EXPECT_EQ(element->stringValue(), value);
}

// Test JSON to basic YANG value conversion using sysrepo test models.
TEST_F(TranslatorTest, setItem) {
    // Get a translator object to play with.
    Session sess(Connection{}.sessionStart());
    sess.switchDatastore(sysrepo::Datastore::Candidate);
    unique_ptr<Translator> translator;
    ASSERT_NO_THROW_LOG(translator.reset(new Translator(sess, "keatest-module")));

    ElementPtr element;
    string xpath;

    // String.
    optional<DataNode> data_node;
    xpath = "/keatest-module:main/string";
    element = Element::create("str");
    EXPECT_NO_THROW_LOG(translator->setItem(xpath, element, LeafBaseType::String));
    EXPECT_NO_THROW_LOG(data_node = sess.getData(xpath));
    ASSERT_TRUE(data_node);
    EXPECT_NO_THROW_LOG(data_node = data_node->findPath(xpath));
    ASSERT_TRUE(data_node);
    ASSERT_EQ(LeafBaseType::String, data_node->schema().asLeaf().valueType().base());
    EXPECT_EQ(element->stringValue(), string(data_node->asTerm().valueStr()));

    // Bool.
    xpath = "/keatest-module:main/boolean";
    element = Element::create(true);
    EXPECT_NO_THROW_LOG(translator->setItem(xpath, element, LeafBaseType::Bool));
    EXPECT_NO_THROW_LOG(data_node = sess.getData(xpath));
    ASSERT_TRUE(data_node);
    EXPECT_NO_THROW_LOG(data_node = data_node->findPath(xpath));
    ASSERT_TRUE(data_node);
    ASSERT_EQ(LeafBaseType::Bool, data_node->schema().asLeaf().valueType().base());
    EXPECT_EQ(element->str(), string(data_node->asTerm().valueStr()));

    // Unsigned 8 bit integer.
    xpath = "/keatest-module:main/ui8";
    element = Element::create(8);
    EXPECT_NO_THROW_LOG(translator->setItem(xpath, element, LeafBaseType::Uint8));
    EXPECT_NO_THROW_LOG(data_node = sess.getData(xpath));
    ASSERT_TRUE(data_node);
    EXPECT_NO_THROW_LOG(data_node = data_node->findPath(xpath));
    ASSERT_TRUE(data_node);
    ASSERT_EQ(LeafBaseType::Uint8, data_node->schema().asLeaf().valueType().base());
    EXPECT_EQ(element->str(), string(data_node->asTerm().valueStr()));

    // Unsigned 16 bit integer.
    xpath = "/keatest-module:main/ui16";
    element = Element::create(16);
    EXPECT_NO_THROW_LOG(translator->setItem(xpath, element, LeafBaseType::Uint16));
    EXPECT_NO_THROW_LOG(data_node = sess.getData(xpath));
    ASSERT_TRUE(data_node);
    EXPECT_NO_THROW_LOG(data_node = data_node->findPath(xpath));
    ASSERT_TRUE(data_node);
    ASSERT_EQ(LeafBaseType::Uint16, data_node->schema().asLeaf().valueType().base());
    EXPECT_EQ(element->str(), string(data_node->asTerm().valueStr()));

    // Unsigned 32 bit integer.
    xpath = "/keatest-module:main/ui32";
    element = Element::create(32);
    EXPECT_NO_THROW_LOG(translator->setItem(xpath, element, LeafBaseType::Uint32));
    EXPECT_NO_THROW_LOG(data_node = sess.getData(xpath));
    ASSERT_TRUE(data_node);
    EXPECT_NO_THROW_LOG(data_node = data_node->findPath(xpath));
    ASSERT_TRUE(data_node);
    ASSERT_EQ(LeafBaseType::Uint32, data_node->schema().asLeaf().valueType().base());
    EXPECT_EQ(element->str(), string(data_node->asTerm().valueStr()));

    // Unsigned 64 bit integer.
    xpath = "/keatest-module:main/ui64";
    element = Element::create(64);
    EXPECT_NO_THROW_LOG(translator->setItem(xpath, element, LeafBaseType::Uint64));
    EXPECT_NO_THROW_LOG(data_node = sess.getData(xpath));
    ASSERT_TRUE(data_node);
    EXPECT_NO_THROW_LOG(data_node = data_node->findPath(xpath));
    ASSERT_TRUE(data_node);
    ASSERT_EQ(LeafBaseType::Uint64, data_node->schema().asLeaf().valueType().base());
    EXPECT_EQ(element->str(), string(data_node->asTerm().valueStr()));

    // Empty.
    xpath = "/keatest-module:main/empty";
    element = Element::create(string());
    EXPECT_NO_THROW_LOG(translator->setItem(xpath, element, LeafBaseType::Empty));
    EXPECT_NO_THROW_LOG(data_node = sess.getData(xpath));
    ASSERT_TRUE(data_node);
    EXPECT_NO_THROW_LOG(data_node = data_node->findPath(xpath));
    ASSERT_TRUE(data_node);
    ASSERT_EQ(LeafBaseType::Empty, data_node->schema().asLeaf().valueType().base());
    EXPECT_EQ(element->stringValue(), string(data_node->asTerm().valueStr()));

    // Signed 8 bit integer.
    xpath = "/keatest-module:main/i8";
    element = Element::create(8);
    EXPECT_NO_THROW_LOG(translator->setItem(xpath, element, LeafBaseType::Int8));
    EXPECT_NO_THROW_LOG(data_node = sess.getData(xpath));
    ASSERT_TRUE(data_node);
    EXPECT_NO_THROW_LOG(data_node = data_node->findPath(xpath));
    ASSERT_TRUE(data_node);
    ASSERT_EQ(LeafBaseType::Int8, data_node->schema().asLeaf().valueType().base());
    EXPECT_EQ(element->str(), string(data_node->asTerm().valueStr()));

    // Signed 16 bit integer.
    xpath = "/keatest-module:main/i16";
    element = Element::create(16);
    EXPECT_NO_THROW_LOG(translator->setItem(xpath, element, LeafBaseType::Int16));
    EXPECT_NO_THROW_LOG(data_node = sess.getData(xpath));
    ASSERT_TRUE(data_node);
    EXPECT_NO_THROW_LOG(data_node = data_node->findPath(xpath));
    ASSERT_TRUE(data_node);
    ASSERT_EQ(LeafBaseType::Int16, data_node->schema().asLeaf().valueType().base());
    EXPECT_EQ(element->str(), string(data_node->asTerm().valueStr()));

    // Signed 32 bit integer.
    xpath = "/keatest-module:main/i32";
    element = Element::create(32);
    EXPECT_NO_THROW_LOG(translator->setItem(xpath, element, LeafBaseType::Int32));
    EXPECT_NO_THROW_LOG(data_node = sess.getData(xpath));
    ASSERT_TRUE(data_node);
    EXPECT_NO_THROW_LOG(data_node = data_node->findPath(xpath));
    ASSERT_TRUE(data_node);
    ASSERT_EQ(LeafBaseType::Int32, data_node->schema().asLeaf().valueType().base());
    EXPECT_EQ(element->str(), string(data_node->asTerm().valueStr()));

    // Signed 64 bit integer.
    xpath = "/keatest-module:main/i64";
    element = Element::create(64);
    EXPECT_NO_THROW_LOG(translator->setItem(xpath, element, LeafBaseType::Int64));
    EXPECT_NO_THROW_LOG(data_node = sess.getData(xpath));
    ASSERT_TRUE(data_node);
    EXPECT_NO_THROW_LOG(data_node = data_node->findPath(xpath));
    ASSERT_TRUE(data_node);
    ASSERT_EQ(LeafBaseType::Int64, data_node->schema().asLeaf().valueType().base());
    EXPECT_EQ(element->str(), string(data_node->asTerm().valueStr()));

    // Identity reference.
    xpath = "/keatest-module:main/id_ref";
    element = Element::create("keatest-module:id_1");
    EXPECT_NO_THROW_LOG(translator->setItem(xpath, element, LeafBaseType::IdentityRef));
    EXPECT_NO_THROW_LOG(data_node = sess.getData(xpath));
    ASSERT_TRUE(data_node);
    EXPECT_NO_THROW_LOG(data_node = data_node->findPath(xpath));
    ASSERT_TRUE(data_node);
    ASSERT_EQ(LeafBaseType::IdentityRef, data_node->schema().asLeaf().valueType().base());
    EXPECT_EQ(element->stringValue(), string(data_node->asTerm().valueStr()));

    // Enumeration item.
    xpath = "/keatest-module:main/enum";
    element = Element::create("maybe");
    EXPECT_NO_THROW_LOG(translator->setItem(xpath, element, LeafBaseType::Enum));
    EXPECT_NO_THROW_LOG(data_node = sess.getData(xpath));
    ASSERT_TRUE(data_node);
    EXPECT_NO_THROW_LOG(data_node = data_node->findPath(xpath));
    ASSERT_TRUE(data_node);
    ASSERT_EQ(LeafBaseType::Enum, data_node->schema().asLeaf().valueType().base());
    EXPECT_EQ(element->stringValue(), string(data_node->asTerm().valueStr()));

    // Binary.
    xpath = "/keatest-module:main/raw";
    element = Element::create("foobar");
    EXPECT_NO_THROW_LOG(translator->setItem(xpath, element, LeafBaseType::Binary));
    EXPECT_NO_THROW_LOG(data_node = sess.getData(xpath));
    ASSERT_TRUE(data_node);
    EXPECT_NO_THROW_LOG(data_node = data_node->findPath(xpath));
    ASSERT_TRUE(data_node);
    ASSERT_EQ(LeafBaseType::Binary, data_node->schema().asLeaf().valueType().base());
    EXPECT_EQ("Zm9vYmFy", string(data_node->asTerm().valueStr()));

    // Bits.
    xpath = "/keatest-module:main/options";
    element = Element::create("strict recursive logging");
    EXPECT_NO_THROW_LOG(translator->setItem(xpath, element, LeafBaseType::Bits));
    EXPECT_NO_THROW_LOG(data_node = sess.getData(xpath));
    ASSERT_TRUE(data_node);
    EXPECT_NO_THROW_LOG(data_node = data_node->findPath(xpath));
    ASSERT_TRUE(data_node);
    ASSERT_EQ(LeafBaseType::Bits, data_node->schema().asLeaf().valueType().base());
    EXPECT_EQ(element->stringValue(), string(data_node->asTerm().valueStr()));

    // Decimal 64.
    xpath = "/keatest-module:main/dec64";
    double d64(9.85);
    element = Element::create(d64);
    EXPECT_NO_THROW_LOG(translator->setItem(xpath, element, LeafBaseType::Dec64));
    EXPECT_NO_THROW_LOG(data_node = sess.getData(xpath));
    ASSERT_TRUE(data_node);
    EXPECT_NO_THROW_LOG(data_node = data_node->findPath(xpath));
    ASSERT_TRUE(data_node);
    ASSERT_EQ(LeafBaseType::Dec64, data_node->schema().asLeaf().valueType().base());
    EXPECT_EQ(element->str(), string(data_node->asTerm().valueStr()));

    // Leaf-list.
    xpath = "/keatest-module:main/numbers";
    EXPECT_NO_THROW_LOG(translator->setItem(xpath, Element::fromJSON("1"), LeafBaseType::Uint8));
    EXPECT_NO_THROW_LOG(translator->setItem(xpath, Element::fromJSON("2"), LeafBaseType::Uint8));
    EXPECT_NO_THROW_LOG(translator->setItem(xpath, Element::fromJSON("3"), LeafBaseType::Uint8));
    ElementPtr got(translator->getItemFromAbsoluteXpath(xpath));
    ASSERT_EQ(LeafBaseType::Dec64, data_node->schema().asLeaf().valueType().base());
    EXPECT_EQ("[ 1, 2, 3 ]", got->str());

    // Clean the leaf-list.
    EXPECT_NO_THROW_LOG(translator->deleteItem(xpath));
    EXPECT_NO_THROW_LOG(data_node = sess.getData(xpath));
    EXPECT_FALSE(data_node);
    data_node.reset();

    // Instance identifier.
    xpath = "/keatest-module:main/instance_id";
    element = Element::create("/keatest-module:main/numbers[.='1']");
    EXPECT_NO_THROW_LOG(translator->setItem(xpath, element, LeafBaseType::InstanceIdentifier));
    EXPECT_NO_THROW_LOG(data_node = sess.getData(xpath));
    ASSERT_TRUE(data_node);
    EXPECT_NO_THROW_LOG(data_node = data_node->findPath(xpath));
    ASSERT_TRUE(data_node);
    ASSERT_EQ(LeafBaseType::InstanceIdentifier, data_node->schema().asLeaf().valueType().base());
    EXPECT_EQ(element->stringValue(), string(data_node->asTerm().valueStr()));

    // Union.
    xpath = "/keatest-module:main/union";
    element = Element::create("8");
    EXPECT_NO_THROW_LOG(translator->setItem(xpath, element, LeafBaseType::Union));
    EXPECT_NO_THROW_LOG(data_node = sess.getData(xpath));
    ASSERT_TRUE(data_node);
    EXPECT_NO_THROW_LOG(data_node = data_node->findPath(xpath));
    ASSERT_TRUE(data_node);
    ASSERT_EQ(LeafBaseType::Union, data_node->schema().asLeaf().valueType().base());
    EXPECT_EQ(element->stringValue(), string(data_node->asTerm().valueStr()));
    element = Element::create("infinity");
    EXPECT_NO_THROW_LOG(translator->setItem(xpath, element, LeafBaseType::Union));
    EXPECT_NO_THROW_LOG(data_node = sess.getData(xpath));
    ASSERT_TRUE(data_node);
    EXPECT_NO_THROW_LOG(data_node = data_node->findPath(xpath));
    ASSERT_TRUE(data_node);
    ASSERT_EQ(LeafBaseType::Union, data_node->schema().asLeaf().valueType().base());
    EXPECT_EQ(element->stringValue(), string(data_node->asTerm().valueStr()));

    // Leafref.
    xpath = "/keatest-module:main/leafref-i8";
    element = Element::create("9");
    EXPECT_NO_THROW_LOG(translator->setItem(xpath, element, LeafBaseType::Leafref));
    EXPECT_NO_THROW_LOG(data_node = sess.getData(xpath));
    ASSERT_TRUE(data_node);
    EXPECT_NO_THROW_LOG(data_node = data_node->findPath(xpath));
    ASSERT_TRUE(data_node);
    ASSERT_EQ(LeafBaseType::Leafref, data_node->schema().asLeaf().valueType().base());
    EXPECT_EQ(element->stringValue(), string(data_node->asTerm().valueStr()));

    // Leafref.
    xpath = "/keatest-module:main/leafref-raw";
    element = Element::create("ff012345");
    EXPECT_NO_THROW_LOG(translator->setItem(xpath, element, LeafBaseType::Leafref));
    EXPECT_NO_THROW_LOG(data_node = sess.getData(xpath));
    ASSERT_TRUE(data_node);
    EXPECT_NO_THROW_LOG(data_node = data_node->findPath(xpath));
    ASSERT_TRUE(data_node);
    ASSERT_EQ(LeafBaseType::Leafref, data_node->schema().asLeaf().valueType().base());
    EXPECT_EQ(element->stringValue(), string(data_node->asTerm().valueStr()));

    // Leafref.
    xpath = "/keatest-module:main/leafref-string";
    element = Element::create("string through");
    EXPECT_NO_THROW_LOG(translator->setItem(xpath, element, LeafBaseType::Leafref));
    EXPECT_NO_THROW_LOG(data_node = sess.getData(xpath));
    ASSERT_TRUE(data_node);
    EXPECT_NO_THROW_LOG(data_node = data_node->findPath(xpath));
    ASSERT_TRUE(data_node);
    ASSERT_EQ(LeafBaseType::Leafref, data_node->schema().asLeaf().valueType().base());
    EXPECT_EQ(element->stringValue(), string(data_node->asTerm().valueStr()));

    // Bad xpath.
    xpath = "/keatest-module:main/no_such_node";
    element = Element::create("str");
    EXPECT_THROW_MSG(translator->setItem(xpath, element, LeafBaseType::String), NetconfError,
                     "setting item '\"str\"' at '" + xpath +
                     "': Session::setItem: Couldn't set "
                     "'/keatest-module:main/no_such_node' to 'str': SR_ERR_INVAL_ARG");

    // Bad type.
    xpath = "/keatest-module:main/string";
    element = Element::create(true);
    EXPECT_NO_THROW_LOG(translator->setItem(xpath, element, LeafBaseType::Bool));

    element = translator->getItemFromAbsoluteXpath(xpath);
    ASSERT_TRUE(element);
    EXPECT_EQ(element->getType(), Element::string);
    EXPECT_EQ(element->str(), "\"true\"");

    // Delete (twice).
    xpath = "/keatest-module:main/string";
    EXPECT_NO_THROW_LOG(data_node = sess.getData(xpath));
    EXPECT_TRUE(data_node);
    EXPECT_NO_THROW_LOG(data_node = data_node->findPath(xpath));
    EXPECT_TRUE(data_node);
    ASSERT_TRUE(NodeType::Leaf == data_node->schema().nodeType());
    EXPECT_EQ("true", data_node->asTerm().valueStr());
    EXPECT_NO_THROW_LOG(translator->deleteItem(xpath));
    EXPECT_NO_THROW_LOG(data_node = sess.getData(xpath));
    EXPECT_FALSE(data_node);
    EXPECT_NO_THROW_LOG(translator->deleteItem(xpath));
    EXPECT_NO_THROW_LOG(data_node = sess.getData(xpath));
    EXPECT_FALSE(data_node);
}

// Test YANG container retrieval.
TEST_F(TranslatorTest, container) {
    ElementPtr element;

    // Get a translator object to play with.
    Translator translator(Connection{}.sessionStart(), "keatest-module");

    // Container with no data apparently throws.
    EXPECT_THROW_MSG(element = translator.getItemFromAbsoluteXpath("/keatest-module:container"), NotImplemented,
                     "getting node of type 1 not supported, xpath is '/keatest-module:container'");
    EXPECT_FALSE(element);
    element.reset();

    EXPECT_NO_THROW_LOG(
        translator.setItem("/keatest-module:container",
                           ElementPtr(), LeafBaseType::Unknown));

    // Container with data filled in throws when retrieving the container itself.
    element = Element::create("Leaf value");
    EXPECT_NO_THROW_LOG(
        translator.setItem("/keatest-module:container/list[key1='key1'][key2='key2']/leaf",
                           element, LeafBaseType::String));
    element.reset();
    EXPECT_THROW_MSG(
        element = translator.getItemFromAbsoluteXpath("/keatest-module:container"), NotImplemented,
        "getting node of type 1 not supported, xpath is '/keatest-module:container'");
    EXPECT_FALSE(element);
    element.reset();
    EXPECT_NO_THROW_LOG(
        element = translator.getItemFromAbsoluteXpath("/keatest-module:container[key1='key1'][key2='key2']"));
    EXPECT_FALSE(element);
}

// Test YANG list retrieval.
TEST_F(TranslatorTest, list) {
    ElementPtr element;

    // Get a translator to play with.
    Translator translator(Connection{}.sessionStart(), "keatest-module");

    // List with no data does not throw and returns a null ElementPtr by default.
    EXPECT_NO_THROW_LOG(
        element = translator.getItemFromAbsoluteXpath("/keatest-module:container/list"));
    EXPECT_FALSE(element);
    element.reset();

    // List with data filled in throws when retrieving the list itself.
    element = Element::create("Leaf value");
    EXPECT_NO_THROW_LOG(
        translator.setItem("/keatest-module:container/list[key1='key1'][key2='key2']/leaf", element,
                           LeafBaseType::String));
    element.reset();
    EXPECT_THROW_MSG(
        element = translator.getItemFromAbsoluteXpath("/keatest-module:container/list"), NotImplemented,
        "getting node of type 16 not supported, xpath is '/keatest-module:container/list'");
    EXPECT_FALSE(element);
    element.reset();
    EXPECT_THROW_MSG(element = translator.getItemFromAbsoluteXpath(
                         "/keatest-module:container/list[key1='key1'][key2='key2']"), NotImplemented,
                     "getting node of type 16 not supported, xpath is "
                     "'/keatest-module:container/list[key1='key1'][key2='key2']'");
    EXPECT_FALSE(element);
}

// Test that we can check if a schema node exists.
TEST_F(TranslatorTest, schemaNodeExists) {
    // Get a translator to play with.
    Translator translator(Connection{}.sessionStart(), "keatest-module");

    EXPECT_FALSE(translator.schemaNodeExists("/keatest-module:main/no_such_node"));
    EXPECT_TRUE(translator.schemaNodeExists("/keatest-module:main"));
    EXPECT_TRUE(translator.schemaNodeExists("/keatest-module:main/string"));
    EXPECT_TRUE(translator.schemaNodeExists("/keatest-module:container/list"));
}

}  // anonymous namespace
