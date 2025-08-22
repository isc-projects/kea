// Copyright (C) 2020-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// @file This file contains tests which exercise the attribute,
/// attribute collection and config attribute collection classes.

#include <config.h>

#include <client_attribute.h>
#include <radius_parsers.h>
#include <attribute_test.h>
#include <testutils/gtest_utils.h>
#include <testutils/test_to_element.h>
#include <gtest/gtest.h>
#include <glob.h>

using namespace std;
using namespace isc;
using namespace isc::asiolink;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::radius;
using namespace isc::radius::test;
using namespace isc::test;

namespace {

// Verify error cases for factory fromText with definition.
TEST_F(AttributeTest, defFromText) {
    AttrDefPtr def;
    EXPECT_THROW_MSG(Attribute::fromText(def, "foobar"), BadValue,
                     "null attribute definition");
    def = AttrDefs::instance().getByType(PW_USER_NAME);
    ASSERT_TRUE(def);
    EXPECT_THROW_MSG(Attribute::fromText(def, ""), BadValue,
                     "empty attribute value");
}

// Verify error cases for generic factory fromBytes.
TEST_F(AttributeTest, fromBytes) {
    vector<uint8_t> bytes;
    EXPECT_THROW_MSG(Attribute::fromBytes(bytes), BadValue,
                     "too short byte argument");
    bytes.push_back(PW_USER_NAME);
    EXPECT_THROW_MSG(Attribute::fromBytes(bytes), BadValue,
                     "too short byte argument");
    bytes.push_back(3);
    EXPECT_THROW_MSG(Attribute::fromBytes(bytes), BadValue,
                     "bad byte argument length 2 != 3");
    bytes.push_back(2);
    bytes.push_back(3);
    EXPECT_THROW_MSG(Attribute::fromBytes(bytes), BadValue,
                     "bad byte argument length 4 != 3");

    // Return null on unknown attribute.
    bytes = { 111, 3, 1 };
    AttributePtr attr;
    EXPECT_NO_THROW(attr = Attribute::fromBytes(bytes));
    EXPECT_FALSE(attr);
}

// Verify error cases for factory fromBytes with def.
TEST_F(AttributeTest, defFromBytes) {
    AttrDefPtr def;
    vector<uint8_t> bytes;
    EXPECT_THROW_MSG(Attribute::fromBytes(def, bytes), BadValue,
                     "null attribute definition");
    def = AttrDefs::instance().getByType(PW_USER_NAME);
    ASSERT_TRUE(def);
    EXPECT_THROW_MSG(Attribute::fromBytes(def, bytes), BadValue,
                     "empty attribute value");
}

// Verifies string attribute.
TEST_F(AttributeTest, attrString) {
    // Using User-Name (1) string attribute.
    AttrDefPtr def = AttrDefs::instance().getByType(PW_USER_NAME);
    ASSERT_TRUE(def);
    EXPECT_EQ(1, def->type_);
    EXPECT_EQ(PW_TYPE_STRING, def->value_type_);

    AttributePtr attr;
    ASSERT_NO_THROW(attr = Attribute::fromString(PW_USER_NAME, "foobar"));
    ASSERT_TRUE(attr);

    EXPECT_EQ(1, attr->getType());
    EXPECT_EQ(PW_TYPE_STRING, attr->getValueType());
    string to_string;
    EXPECT_NO_THROW_LOG(to_string = attr->toString());
    EXPECT_EQ("foobar", to_string);
    EXPECT_EQ("User-Name='foobar'", attr->toText());
    vector<uint8_t> binary = { 1, 8, 0x66, 0x6f, 0x6f, 0x62, 0x61, 0x72 };
    EXPECT_EQ(binary, attr->toBytes());
    string expected = "{ \"type\": 1, \"name\": \"User-Name\", ";
    expected += " \"data\": \"foobar\" }";
    runToElementTest<Attribute>(expected, *attr);

    AttributePtr from_bytes = Attribute::fromBytes(binary);
    ASSERT_TRUE(from_bytes);
    EXPECT_TRUE(compare(from_bytes, attr))
        << from_bytes->toText() << " != " << attr->toText();

    AttributePtr def_text = Attribute::fromText(def, "foobar");
    ASSERT_TRUE(def_text);
    EXPECT_TRUE(compare(def_text, attr))
        << def_text->toText() << " != " << attr->toText();

    vector<uint8_t> value = { 0x66, 0x6f, 0x6f, 0x62, 0x61, 0x72 };
    AttributePtr def_bytes = Attribute::fromBytes(def, value);
    ASSERT_TRUE(def_bytes);
    EXPECT_TRUE(compare(def_bytes, attr))
        << def_bytes->toText() << " != " << attr->toText();

    AttributePtr from_binary = Attribute::fromBinary(PW_USER_NAME, value);
    ASSERT_TRUE(from_binary);
    EXPECT_TRUE(compare(from_binary, attr))
        << from_binary->toText() << " != " << attr->toText();

    vector<uint8_t> to_binary;
    EXPECT_NO_THROW_LOG(to_binary = attr->toBinary());
    EXPECT_EQ(value, to_binary);

    EXPECT_THROW_MSG(Attribute::fromString(PW_USER_NAME, ""), BadValue,
                     "empty attribute value");

    vector<uint8_t> empty;
    EXPECT_THROW_MSG(Attribute::fromBinary(PW_USER_NAME, empty), BadValue,
                     "empty attribute value");

    string big_text(MAX_STRING_LEN, 'x');
    EXPECT_NO_THROW_LOG(Attribute::fromString(PW_USER_NAME, big_text));

    vector<uint8_t> big_binary(MAX_STRING_LEN, 0x78);
    EXPECT_NO_THROW_LOG(Attribute::fromBinary(PW_USER_NAME, big_binary));

    string too_big_text(MAX_STRING_LEN + 1, 'x');
    EXPECT_THROW_MSG(Attribute::fromString(PW_USER_NAME, too_big_text),
                     BadValue, "value is too large 254 > 253");

    vector<uint8_t> too_big_binary(MAX_STRING_LEN + 1, 0x78);
    EXPECT_THROW_MSG(Attribute::fromBinary(PW_USER_NAME, too_big_binary),
                     BadValue, "value is too large 254 > 253");

    EXPECT_THROW_MSG(attr->toInt(), TypeError,
                     "the attribute value type must be integer, not string");
    EXPECT_THROW_MSG(attr->toIpAddr(), TypeError,
                     "the attribute value type must be ipaddr, not string");
    EXPECT_THROW_MSG(attr->toIpv6Addr(), TypeError,
                     "the attribute value type must be ipv6addr, not string");
    EXPECT_THROW_MSG(attr->toIpv6Prefix(), TypeError,
                     "the attribute value type must be ipv6prefix, not string");
    EXPECT_THROW_MSG(attr->toIpv6PrefixLen(), TypeError,
                     "the attribute value type must be ipv6prefix, not string");
    EXPECT_THROW_MSG(attr->toVendorId(), TypeError,
                     "the attribute value type must be vsa, not string");
    EXPECT_THROW_MSG(attr->toVsaData(), TypeError,
                     "the attribute value type must be vsa, not string");
}

// Verifies raw string attribute.
TEST_F(AttributeTest, rawAttrString) {
    AttributePtr attr;
    ASSERT_NO_THROW(attr = Attribute::fromString(PW_USER_NAME, "\x01\x02\x03"));
    ASSERT_TRUE(attr);

    EXPECT_EQ(1, attr->getType());
    EXPECT_EQ(PW_TYPE_STRING, attr->getValueType());
    string to_string;
    EXPECT_NO_THROW_LOG(to_string = attr->toString());
    EXPECT_EQ("\x01\x02\x03", to_string);
    EXPECT_EQ("User-Name=0x010203", attr->toText());
    vector<uint8_t> binary = { 1, 5, 1, 2, 3 };
    EXPECT_EQ(binary, attr->toBytes());
    string expected = "{ \"type\": 1, \"name\": \"User-Name\", ";
    expected += " \"raw\": \"010203\" }";
    runToElementTest<Attribute>(expected, *attr);

    AttributePtr from_bytes = Attribute::fromBytes(binary);
    ASSERT_TRUE(from_bytes);
    EXPECT_TRUE(compare(from_bytes, attr))
        << from_bytes->toText() << " != " << attr->toText();
}

// Verifies integer attribute.
TEST_F(AttributeTest, attrInt) {
    // Using NAS-Port-Type (61) integer attribute.
    AttrDefPtr def = AttrDefs::instance().getByType(PW_NAS_PORT_TYPE);
    ASSERT_TRUE(def);
    EXPECT_EQ(61, def->type_);
    EXPECT_EQ(PW_TYPE_INTEGER, def->value_type_);

    AttributePtr attr;
    ASSERT_NO_THROW(attr = Attribute::fromInt(61, 15));
    ASSERT_TRUE(attr);

    EXPECT_EQ(61, attr->getType());
    EXPECT_EQ(PW_TYPE_INTEGER, attr->getValueType());
    uint32_t to_int;
    EXPECT_NO_THROW_LOG(to_int = attr->toInt());
    EXPECT_EQ(15, to_int);
    EXPECT_EQ("NAS-Port-Type=Ethernet", attr->toText());
    vector<uint8_t> binary = { 61, 6, 0, 0, 0, 15 };
    EXPECT_EQ(binary, attr->toBytes());
    string expected = "{ \"type\": 61, \"name\": \"NAS-Port-Type\", ";
    expected += " \"data\": \"15\" }";
    runToElementTest<Attribute>(expected, *attr);

    AttributePtr from_bytes = Attribute::fromBytes(binary);
    ASSERT_TRUE(from_bytes);
    EXPECT_TRUE(compare(from_bytes, attr))
        << from_bytes->toText() << " != " << attr->toText();

    vector<uint8_t> short_binary = { 61, 5, 0, 0, 15 };
    EXPECT_THROW_MSG(Attribute::fromBytes(short_binary), BadValue,
                     "bad value length 3 != 4");

    vector<uint8_t> long_binary = { 61, 7, 0, 0, 0, 0, 15 };
    EXPECT_THROW_MSG(Attribute::fromBytes(long_binary), BadValue,
                     "bad value length 5 != 4");

    AttributePtr def_text = Attribute::fromText(def, "15");
    ASSERT_TRUE(def_text);
    EXPECT_TRUE(compare(def_text, attr))
        << def_text->toText() << " != " << attr->toText();

    vector<uint8_t> value = { 0, 0, 0, 15 };
    AttributePtr def_bytes = Attribute::fromBytes(def, value);
    ASSERT_TRUE(def_bytes);
    EXPECT_TRUE(compare(def_bytes, attr))
        << def_bytes->toText() << " != " << attr->toText();

    EXPECT_THROW_MSG(attr->toString(), TypeError,
                     "the attribute value type must be string, not integer");
    EXPECT_THROW_MSG(attr->toBinary(), TypeError,
                     "the attribute value type must be string, not integer");
    EXPECT_THROW_MSG(attr->toIpAddr(), TypeError,
                     "the attribute value type must be ipaddr, not integer");
    EXPECT_THROW_MSG(attr->toIpv6Addr(), TypeError,
                     "the attribute value type must be ipv6addr, not integer");
    EXPECT_THROW_MSG(attr->toIpv6Prefix(), TypeError,
                     "the attribute value type must be ipv6prefix, not integer");
    EXPECT_THROW_MSG(attr->toIpv6PrefixLen(), TypeError,
                     "the attribute value type must be ipv6prefix, not integer"
);
    EXPECT_THROW_MSG(attr->toVendorId(), TypeError,
                     "the attribute value type must be vsa, not integer");
    EXPECT_THROW_MSG(attr->toVsaData(), TypeError,
                     "the attribute value type must be vsa, not integer");
}

// Verifies vendor integer attribute.
TEST_F(AttributeTest, vendorAttrInt) {
    // Attibute.
    AttrDefPtr def(new AttrDef(1, "My-Int", PW_TYPE_INTEGER, 2495));
    ASSERT_NO_THROW(AttrDefs::instance().add(def));
    // Integer constant.
    IntCstDefPtr cst(new IntCstDef(1, "My-Cst", 144, 2495));
    ASSERT_NO_THROW(AttrDefs::instance().add(cst));
    AttributePtr attr;
    ASSERT_NO_THROW(attr = Attribute::fromText(def, "My-Cst"));
    ASSERT_TRUE(attr);
    EXPECT_EQ("Vendor-Specific=[2495]0x010600000090", attr->toText());
}

// Verifies IP address attribute.
TEST_F(AttributeTest, attrIpAddr) {
    // Using Framed-IP-Address (8) IP address attribute.
    AttrDefPtr def = AttrDefs::instance().getByType(PW_FRAMED_IP_ADDRESS);
    ASSERT_TRUE(def);
    EXPECT_EQ(8, def->type_);
    EXPECT_EQ(PW_TYPE_IPADDR, def->value_type_);

    AttributePtr attr;
    ASSERT_NO_THROW(attr = Attribute::fromIpAddr(8, IOAddress("192.0.2.1")));
    ASSERT_TRUE(attr);

    EXPECT_EQ(8, attr->getType());
    EXPECT_EQ(PW_TYPE_IPADDR, attr->getValueType());
    IOAddress addr("0.0.0.0");
    EXPECT_NO_THROW_LOG(addr = attr->toIpAddr());
    EXPECT_EQ("192.0.2.1", addr.toText());
    EXPECT_EQ("Framed-IP-Address=192.0.2.1", attr->toText());
    vector<uint8_t> binary = { 8, 6, 192, 0, 2, 1 };
    EXPECT_EQ(binary, attr->toBytes());
    string expected = "{ \"type\": 8, \"name\": \"Framed-IP-Address\", ";
    expected += " \"data\": \"192.0.2.1\" }";
    runToElementTest<Attribute>(expected, *attr);

    EXPECT_THROW_MSG(Attribute::fromIpAddr(8, IOAddress("2001:db8::1235")),
                     BadValue, "not v4 address 2001:db8::1235");

    AttributePtr def_text = Attribute::fromText(def, "192.0.2.1");
    ASSERT_TRUE(def_text);
    EXPECT_TRUE(compare(def_text, attr))
        << def_text->toText() << " != " << attr->toText();

    AttributePtr from_bytes = Attribute::fromBytes(binary);
    ASSERT_TRUE(from_bytes);
    EXPECT_TRUE(compare(from_bytes, attr))
        << from_bytes->toText() << " != " << attr->toText();

    vector<uint8_t> short_binary = { 8, 5, 192, 0, 2 };
    EXPECT_THROW_MSG(Attribute::fromBytes(short_binary), BadValue,
                     "bad value length 3 != 4");

    vector<uint8_t> long_binary = { 8, 7, 192, 0, 2, 1, 0 };
    EXPECT_THROW_MSG(Attribute::fromBytes(long_binary), BadValue,
                     "bad value length 5 != 4");

    vector<uint8_t> value = { 192, 0, 2, 1 };
    AttributePtr def_bytes = Attribute::fromBytes(def, value);
    ASSERT_TRUE(def_bytes);
    EXPECT_TRUE(compare(def_bytes, attr))
        << def_bytes->toText() << " != " << attr->toText();

    EXPECT_THROW_MSG(attr->toString(), TypeError,
                     "the attribute value type must be string, not ipaddr");
    EXPECT_THROW_MSG(attr->toBinary(), TypeError,
                     "the attribute value type must be string, not ipaddr");
    EXPECT_THROW_MSG(attr->toInt(), TypeError,
                     "the attribute value type must be integer, not ipaddr");
    EXPECT_THROW_MSG(attr->toIpv6Addr(), TypeError,
                     "the attribute value type must be ipv6addr, not ipaddr");
    EXPECT_THROW_MSG(attr->toIpv6Prefix(), TypeError,
                     "the attribute value type must be ipv6prefix, not ipaddr");
    EXPECT_THROW_MSG(attr->toIpv6PrefixLen(), TypeError,
                     "the attribute value type must be ipv6prefix, not ipaddr");
    EXPECT_THROW_MSG(attr->toVendorId(), TypeError,
                     "the attribute value type must be vsa, not ipaddr");
    EXPECT_THROW_MSG(attr->toVsaData(), TypeError,
                     "the attribute value type must be vsa, not ipaddr");
}

// Verifies IPv6 address attribute.
TEST_F(AttributeTest, attrIpv6Addr) {
    // Using Framed-IPv6-Address (168) IPv6 address attribute.
    AttrDefPtr def = AttrDefs::instance().getByType(PW_FRAMED_IPV6_ADDRESS);
    ASSERT_TRUE(def);
    EXPECT_EQ(168, def->type_);
    EXPECT_EQ(PW_TYPE_IPV6ADDR, def->value_type_);

    AttributePtr attr;
    ASSERT_NO_THROW(attr = Attribute::fromIpv6Addr(168,
                                                IOAddress("2001:db8::1235")));
    ASSERT_TRUE(attr);
    EXPECT_EQ(168, attr->getType());
    EXPECT_EQ(PW_TYPE_IPV6ADDR, attr->getValueType());
    IOAddress addr("::");
    EXPECT_NO_THROW_LOG(addr = attr->toIpv6Addr());
    EXPECT_EQ("2001:db8::1235", addr.toText());
    EXPECT_EQ("Framed-IPv6-Address=2001:db8::1235", attr->toText());
    vector<uint8_t> binary = { 168, 18,
        0x20, 0x01, 0x0d, 0xb8, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x12, 0x35 };
    EXPECT_EQ(binary, attr->toBytes());
    string expected = "{ \"type\": 168, \"name\": \"Framed-IPv6-Address\", ";
    expected += " \"data\": \"2001:db8::1235\" }";
    runToElementTest<Attribute>(expected, *attr);

    EXPECT_THROW_MSG(Attribute::fromIpv6Addr(168, IOAddress("192.0.2.1")),
                     BadValue, "not v6 address 192.0.2.1");

    AttributePtr def_text = Attribute::fromText(def, "2001:db8::1235");
    ASSERT_TRUE(def_text);
    EXPECT_TRUE(compare(def_text, attr))
        << def_text->toText() << " != " << attr->toText();

    AttributePtr from_bytes = Attribute::fromBytes(binary);
    ASSERT_TRUE(from_bytes);
    EXPECT_TRUE(compare(from_bytes, attr))
        << from_bytes->toText() << " != " << attr->toText();

    vector<uint8_t> short_binary = { 168, 6, 192, 0, 2, 1 };
    EXPECT_THROW_MSG(Attribute::fromBytes(short_binary), BadValue,
                     "bad value length 4 != 16");

    vector<uint8_t> long_binary = { 168, 19,
        0x20, 0x01, 0x0d, 0xb8, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x12, 0x35, 0 };
    EXPECT_THROW_MSG(Attribute::fromBytes(long_binary), BadValue,
                     "bad value length 17 != 16");

    vector<uint8_t> value = {
        0x20, 0x01, 0x0d, 0xb8, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x12, 0x35 };
    AttributePtr def_bytes = Attribute::fromBytes(def, value);
    ASSERT_TRUE(def_bytes);
    EXPECT_TRUE(compare(def_bytes, attr))
        << def_bytes->toText() << " != " << attr->toText();

    EXPECT_THROW_MSG(attr->toString(), TypeError,
                     "the attribute value type must be string, not ipv6addr");
    EXPECT_THROW_MSG(attr->toBinary(), TypeError,
                     "the attribute value type must be string, not ipv6addr");
    EXPECT_THROW_MSG(attr->toInt(), TypeError,
                     "the attribute value type must be integer, not ipv6addr");
    EXPECT_THROW_MSG(attr->toIpAddr(), TypeError,
                     "the attribute value type must be ipaddr, not ipv6addr");
    EXPECT_THROW_MSG(attr->toIpv6Prefix(), TypeError,
                     "the attribute value type must be ipv6prefix, not ipv6addr");
    EXPECT_THROW_MSG(attr->toIpv6PrefixLen(), TypeError,
                     "the attribute value type must be ipv6prefix, not ipv6addr");
    EXPECT_THROW_MSG(attr->toVendorId(), TypeError,
                     "the attribute value type must be vsa, not ipv6addr");
    EXPECT_THROW_MSG(attr->toVsaData(), TypeError,
                     "the attribute value type must be vsa, not ipv6addr");
}

// Verifies IPv6 prefix attribute.
TEST_F(AttributeTest, attrIpv6Prefix) {
    // Using Delegated-IPv6-Prefix (123) IPv6 prefix attribute.
    AttrDefPtr def = AttrDefs::instance().getByType(PW_DELEGATED_IPV6_PREFIX);
    ASSERT_TRUE(def);
    EXPECT_EQ(123, def->type_);
    EXPECT_EQ(PW_TYPE_IPV6PREFIX, def->value_type_);

    AttributePtr attr;
    ASSERT_NO_THROW(attr = Attribute::fromIpv6Prefix(123, 128,
                                                IOAddress("2001:db8::1235")));
    ASSERT_TRUE(attr);
    EXPECT_EQ(123, attr->getType());
    EXPECT_EQ(PW_TYPE_IPV6PREFIX, attr->getValueType());
    IOAddress addr("::");
    EXPECT_NO_THROW_LOG(addr = attr->toIpv6Prefix());
    EXPECT_EQ("2001:db8::1235", addr.toText());
    uint8_t len = 0;
    EXPECT_NO_THROW_LOG(len = attr->toIpv6PrefixLen());
    EXPECT_EQ(128, len);
    EXPECT_EQ("Delegated-IPv6-Prefix=2001:db8::1235/128", attr->toText());
    vector<uint8_t> binary = { 123, 20, 0, 128,
        0x20, 0x01, 0x0d, 0xb8, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x12, 0x35 };
    EXPECT_EQ(binary, attr->toBytes());
    string expected = "{ \"type\": 123, \"name\": \"Delegated-IPv6-Prefix\", ";
    expected += " \"data\": \"2001:db8::1235/128\" }";
    runToElementTest<Attribute>(expected, *attr);

    AttributePtr def_text;
    EXPECT_NO_THROW_LOG(def_text = Attribute::fromText(def, "2001:db8::1235/128"));
    ASSERT_TRUE(def_text);
    EXPECT_TRUE(compare(def_text, attr))
        << def_text->toText() << " != " << attr->toText();

    AttributePtr from_bytes;
    EXPECT_NO_THROW_LOG(from_bytes = Attribute::fromBytes(binary));
    ASSERT_TRUE(from_bytes);
    EXPECT_TRUE(compare(from_bytes, attr))
        << from_bytes->toText() << " != " << attr->toText();

    // IPv6 prefix can be truncated...
    vector<uint8_t> short_binary = { 123, 8, 0, 32, 192, 0, 2, 1 };
    AttributePtr short_bytes;
    EXPECT_NO_THROW_LOG(short_bytes = Attribute::fromBytes(short_binary));
    EXPECT_TRUE(short_bytes);

    // But the prefix length is required.
    vector<uint8_t> too_short_binary = { 123, 2 };
    EXPECT_THROW_MSG(Attribute::fromBytes(too_short_binary), BadValue,
                     "empty attribute value");

    too_short_binary = { 123, 3, 0 };
    EXPECT_THROW_MSG(Attribute::fromBytes(too_short_binary), BadValue,
                     "bad value length 1 < 2");

    vector<uint8_t> long_binary = { 123, 21, 0, 128,
        0x20, 0x01, 0x0d, 0xb8, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x12, 0x35, 0 };
    EXPECT_THROW_MSG(Attribute::fromBytes(long_binary), BadValue,
                     "bad value length 19 > 18");

    // Bad prefix length.
    vector<uint8_t> bad_plen = { 0, 129,
        0x20, 0x01, 0x0d, 0xb8, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x12, 0x35 };
    EXPECT_THROW_MSG(Attribute::fromBytes(def, bad_plen), BadValue,
                     "bad prefix length 129 > 128");

    vector<uint8_t> value = { 0, 128,
        0x20, 0x01, 0x0d, 0xb8, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x12, 0x35 };
    AttributePtr def_bytes;
    EXPECT_NO_THROW_LOG(def_bytes = Attribute::fromBytes(def, value));
    ASSERT_TRUE(def_bytes);
    EXPECT_TRUE(compare(def_bytes, attr))
        << def_bytes->toText() << " != " << attr->toText();

    EXPECT_THROW_MSG(attr->toString(), TypeError,
                     "the attribute value type must be string, not ipv6prefix");
    EXPECT_THROW_MSG(attr->toBinary(), TypeError,
                     "the attribute value type must be string, not ipv6prefix");
    EXPECT_THROW_MSG(attr->toInt(), TypeError,
                     "the attribute value type must be integer, not ipv6prefix");
    EXPECT_THROW_MSG(attr->toIpAddr(), TypeError,
                     "the attribute value type must be ipaddr, not ipv6prefix");
    EXPECT_THROW_MSG(attr->toIpv6Addr(), TypeError,
                     "the attribute value type must be ipv6addr, not ipv6prefix");
    EXPECT_THROW_MSG(attr->toVendorId(), TypeError,
                     "the attribute value type must be vsa, not ipv6prefix");
    EXPECT_THROW_MSG(attr->toVsaData(), TypeError,
                     "the attribute value type must be vsa, not ipv6prefix");
}

// Verifies vsa attribute.
TEST_F(AttributeTest, attrVsa) {
    // Using Vector-Specific (26) *only* vsa attribute.
    AttrDefPtr def = AttrDefs::instance().getByType(PW_VENDOR_SPECIFIC);
    ASSERT_TRUE(def);
    EXPECT_EQ(26, def->type_);
    EXPECT_EQ(PW_TYPE_VSA, def->value_type_);

    AttributePtr attr;
    ASSERT_NO_THROW(attr = Attribute::fromVsa(PW_VENDOR_SPECIFIC,
                                              1234, "foobar"));
    ASSERT_TRUE(attr);

    EXPECT_EQ(26, attr->getType());
    EXPECT_EQ(PW_TYPE_VSA, attr->getValueType());
    uint32_t vendor = 0;
    ASSERT_NO_THROW(vendor = attr->toVendorId());
    EXPECT_EQ(1234, vendor);
    EXPECT_EQ("Vendor-Specific=[1234]0x666F6F626172", attr->toText());
    vector<uint8_t> binary = { 26, 12, 0, 0, 0x04, 0xd2,
                               0x66, 0x6f, 0x6f, 0x62, 0x61, 0x72 };
    EXPECT_EQ(binary, attr->toBytes());
    string expected = "{ \"type\": 26, \"name\": \"Vendor-Specific\", ";
    expected += " \"vendor\": \"1234\", \"vsa-raw\": \"666F6F626172\" }";
    runToElementTest<Attribute>(expected, *attr);

    AttributePtr from_bytes = Attribute::fromBytes(binary);
    ASSERT_TRUE(from_bytes);
    EXPECT_TRUE(compare(from_bytes, attr))
        << from_bytes->toText() << " != " << attr->toText();

    vector<uint8_t> value = { 0x66, 0x6f, 0x6f, 0x62, 0x61, 0x72 };
    AttributePtr def_value = Attribute::fromVsa(PW_VENDOR_SPECIFIC,
                                                1234, value);
    ASSERT_TRUE(def_value);
    EXPECT_TRUE(compare(def_value, attr))
        << def_value->toText() << " != " << attr->toText();

    vector<uint8_t> bytes = { 0, 0, 0x04, 0xd2,
                              0x66, 0x6f, 0x6f, 0x62, 0x61, 0x72 };
    AttributePtr def_bytes = Attribute::fromBytes(def, bytes);
    ASSERT_TRUE(def_bytes);
    EXPECT_TRUE(compare(def_bytes, attr))
        << def_bytes->toText() << " != " << attr->toText();

    EXPECT_THROW_MSG(Attribute::fromVsa(PW_VENDOR_SPECIFIC, 1234, ""),
                     BadValue, "value is empty");

    vector<uint8_t> empty;
    EXPECT_THROW_MSG(Attribute::fromVsa(PW_VENDOR_SPECIFIC, 1234, empty),
                     BadValue, "value is empty");

    vector<uint8_t> small = { 26, 6, 0, 0, 0x4, 0xd2 };
    EXPECT_THROW_MSG(Attribute::fromBytes(small), BadValue,
                     "value is too small 4 < 5");

    vector<uint8_t> small2 = { 0, 0, 0x4, 0xd2 };
    EXPECT_THROW_MSG(Attribute::fromBytes(def, small2), BadValue,
                     "value is too small 4 < 5");

    string big_text(MAX_VSA_DATA_LEN, 'x');
    EXPECT_NO_THROW_LOG(Attribute::fromVsa(PW_VENDOR_SPECIFIC,
                                           1234, big_text));

    vector<uint8_t> big_binary(MAX_VSA_DATA_LEN, 0x78);
    EXPECT_NO_THROW_LOG(Attribute::fromVsa(PW_VENDOR_SPECIFIC,
                                           1234, big_binary));

    vector<uint8_t> big_value(MAX_STRING_LEN, 0x87);
    EXPECT_NO_THROW_LOG(Attribute::fromBytes(def, big_value));

    string too_big_text(MAX_VSA_DATA_LEN + 1, 'x');
    EXPECT_THROW_MSG(Attribute::fromVsa(PW_VENDOR_SPECIFIC, 1234,
                                        too_big_text), BadValue,
                     "value is too large 250 > 249");

    vector<uint8_t> too_big_binary(MAX_VSA_DATA_LEN + 1, 0x87);
    EXPECT_THROW_MSG(Attribute::fromVsa(PW_VENDOR_SPECIFIC, 1234,
                                        too_big_binary), BadValue,
                     "value is too large 250 > 249");

    vector<uint8_t> too_bigvalue(MAX_STRING_LEN + 1, 0x87);
    EXPECT_THROW_MSG(Attribute::fromBytes(def, too_bigvalue), BadValue,
                     "value is too large 254 > 253");

    EXPECT_THROW_MSG(attr->toString(), TypeError,
                     "the attribute value type must be string, not vsa");
    EXPECT_THROW_MSG(attr->toBinary(), TypeError,
                     "the attribute value type must be string, not vsa");
    EXPECT_THROW_MSG(attr->toInt(), TypeError,
                     "the attribute value type must be integer, not vsa");
    EXPECT_THROW_MSG(attr->toIpAddr(), TypeError,
                     "the attribute value type must be ipaddr, not vsa");
    EXPECT_THROW_MSG(attr->toIpv6Addr(), TypeError,
                     "the attribute value type must be ipv6addr, not vsa");
    EXPECT_THROW_MSG(attr->toIpv6Prefix(), TypeError,
                     "the attribute value type must be ipv6prefix, not vsa");
    EXPECT_THROW_MSG(attr->toIpv6PrefixLen(), TypeError,
                     "the attribute value type must be ipv6prefix, not vsa");
}

// Verifies vendor fromText.
TEST_F(AttributeTest, vendorFromText) {
    // Using DSL-Forum (3561) Agent-Circuit-Id (1),
    AttrDefPtr def(new AttrDef(1, "Agent-Circuit-Id", PW_TYPE_STRING, 3561));
    AttributePtr attr;
    ASSERT_NO_THROW(attr = Attribute::fromText(def, "foobar"));
    ASSERT_TRUE(attr);
    EXPECT_EQ(PW_VENDOR_SPECIFIC, attr->getType());
    EXPECT_EQ(PW_TYPE_VSA, attr->getValueType());
    EXPECT_EQ(3561, attr->toVendorId());
    EXPECT_EQ(12, attr->getValueLen());
    vector<uint8_t> vsa_data = { 1, 8, 0x66, 0x6f, 0x6f, 0x62, 0x61, 0x72 };
    EXPECT_EQ(vsa_data, attr->toVsaData());
}

// Verifies vendor fromBytes.
TEST_F(AttributeTest, vendorFromBytes) {
    // Using DSL-Forum (3561) Access-Loop-Encapsulation (144),
    AttrDefPtr def(new AttrDef(144, "Access-Loop-Encapsulation",
                               PW_TYPE_STRING, 3561));
    AttributePtr attr;
    vector<uint8_t> value = { 2, 0, 0 };
    ASSERT_NO_THROW(attr = Attribute::fromBytes(def, value));
    ASSERT_TRUE(attr);
    EXPECT_EQ(PW_VENDOR_SPECIFIC, attr->getType());
    EXPECT_EQ(PW_TYPE_VSA, attr->getValueType());
    EXPECT_EQ(3561, attr->toVendorId());
    EXPECT_EQ(9, attr->getValueLen());
    vector<uint8_t> vsa_data = { 144, 5, 2, 0, 0 };
    EXPECT_EQ(vsa_data, attr->toVsaData());
}

// Verifies basic methods for attribute collection.
TEST_F(AttributeTest, attributesBasic) {
    Attributes attrs;
    EXPECT_TRUE(attrs.empty());
    EXPECT_EQ(0, attrs.size());

    // Add a string attribute.
    ASSERT_NO_THROW(attrs.add(Attribute::fromString(1, "foobar")));
    EXPECT_FALSE(attrs.empty());
    EXPECT_EQ(1, attrs.size());

    // Add an integer attribute.
    ASSERT_NO_THROW(attrs.add(Attribute::fromInt(6, 2)));
    EXPECT_FALSE(attrs.empty());
    EXPECT_EQ(2, attrs.size());

    // Clear.
    attrs.clear();
    EXPECT_TRUE(attrs.empty());
    EXPECT_EQ(0, attrs.size());
}

// Verifies attributes can be added and deleted.
TEST_F(AttributeTest, attributesAddDel) {
    Attributes attrs;
    EXPECT_TRUE(attrs.empty());
    EXPECT_EQ(0, attrs.size());

    // Add 3 User-Name and a Service-Type.
    ASSERT_NO_THROW(attrs.add(Attribute::fromString(PW_USER_NAME, "foobar")));
    ASSERT_NO_THROW(attrs.add(Attribute::fromString(PW_USER_NAME, "foo")));
    ASSERT_NO_THROW(attrs.add(Attribute::fromInt(PW_SERVICE_TYPE, 20)));
    ASSERT_NO_THROW(attrs.add(Attribute::fromString(PW_USER_NAME, "bar")));

    // Verify counts.
    EXPECT_EQ(4, attrs.size());
    EXPECT_EQ(3, attrs.count(PW_USER_NAME));
    EXPECT_EQ(1, attrs.count(PW_SERVICE_TYPE));
    EXPECT_EQ(0, attrs.count(PW_FRAMED_IP_ADDRESS));

    // Gets.
    ConstAttributePtr attr;
    ASSERT_NO_THROW(attr = attrs.get(PW_USER_NAME));
    ASSERT_TRUE(attr);
    EXPECT_EQ(PW_USER_NAME, attr->getType());
    EXPECT_EQ(PW_TYPE_STRING, attr->getValueType());
    attr.reset();
    ASSERT_NO_THROW(attr = attrs.get(PW_SERVICE_TYPE));
    ASSERT_TRUE(attr);
    EXPECT_EQ(PW_SERVICE_TYPE, attr->getType());
    EXPECT_EQ(PW_TYPE_INTEGER, attr->getValueType());
    EXPECT_EQ(20, attr->toInt());
    attr.reset();
    ASSERT_NO_THROW(attr = attrs.get(PW_FRAMED_IP_ADDRESS));
    EXPECT_FALSE(attr);
    attr.reset();

    // toText.
    string expected = "User-Name='foobar',\nUser-Name='foo',\n";
    expected += "Service-Type=20,\nUser-Name='bar'";
    string got;
    ASSERT_NO_THROW(got = attrs.toText());
    EXPECT_EQ(expected, got) << expected << "\n" << got << "\n";

    // toElement.
    expected = "[ { \"type\": 1, \"name\": \"User-Name\", \"data\": ";
    expected += "\"foobar\" }, { \"type\": 1, \"name\": \"User-Name\", ";
    expected += "\"data\": \"foo\" }, { \"type\": 6, \"name\": ";
    expected += "\"Service-Type\", \"data\": \"20\" }, { \"type\": 1, ";
    expected += "\"name\": \"User-Name\", \"data\": \"bar\" } ]";
    runToElementTest<Attributes>(expected, attrs);

    // Check order: third item is the Service-Type.
    size_t cnt = 0;
    for (auto const& it : attrs) {
        ++cnt;
        if (cnt == 3) {
            attr = it;
        }
    }
    ASSERT_TRUE(attr);
    EXPECT_EQ(PW_SERVICE_TYPE, attr->getType());

    // Deletes.
    EXPECT_TRUE(attrs.del(PW_USER_NAME));
    EXPECT_TRUE(attrs.del(PW_SERVICE_TYPE));
    EXPECT_TRUE(attrs.del(PW_USER_NAME));
    EXPECT_FALSE(attrs.del(PW_SERVICE_TYPE));
    EXPECT_EQ(1, attrs.count(PW_USER_NAME));
    EXPECT_TRUE(attrs.del(PW_USER_NAME));
    EXPECT_FALSE(attrs.del(PW_USER_NAME));
    EXPECT_TRUE(attrs.empty());
    EXPECT_EQ(0, attrs.size());
}

// Verifies append.
TEST_F(AttributeTest, attributesAppend) {
    Attributes attrs;
    attrs.add(Attribute::fromString(PW_USER_NAME, "foobar"));
    attrs.add(Attribute::fromInt(PW_SERVICE_TYPE, 2));
    Attributes attrs1;
    attrs1.add(Attribute::fromInt(PW_NAS_PORT, 123));
    attrs1.add(Attribute::fromString(PW_USER_NAME, "me"));
    EXPECT_EQ(2, attrs.size());
    EXPECT_EQ(2, attrs1.size());
    ASSERT_NO_THROW(attrs.append(attrs1));
    EXPECT_EQ(4, attrs.size());
    EXPECT_EQ(2, attrs1.size());
    EXPECT_EQ(2, attrs.count(PW_USER_NAME));
}

// Verifies parse and unparse.
TEST_F(AttributeTest, attributesElement) {
    Attributes attrs;
    ASSERT_NO_THROW(attrs.add(Attribute::fromString(PW_USER_NAME, "foobar")));
    vector<uint8_t> binary = { 1, 2, 3 };
    ASSERT_NO_THROW(attrs.add(Attribute::fromBinary(PW_USER_NAME, binary)));
    ASSERT_NO_THROW(attrs.add(Attribute::fromInt(PW_SERVICE_TYPE, 2)));
    EXPECT_EQ(3, attrs.size());

    // toElement.
    string expected = "[ { \"type\": 1, \"name\": \"User-Name\", \"data\": ";
    expected += "\"foobar\" }, { \"type\": 1, \"name\": \"User-Name\", ";
    expected += "\"raw\": \"010203\" }, { \"type\": 6, \"name\": ";
    expected += "\"Service-Type\", \"data\": \"2\" } ]";
    runToElementTest<Attributes>(expected, attrs);

    // fromElement.
    Attributes got_attrs = Attributes::fromElement(attrs.toElement());
    EXPECT_TRUE(compare(got_attrs, attrs))
        << got_attrs.toText() << "\n" << attrs.toText();
}

} // end of anonymous namespace
