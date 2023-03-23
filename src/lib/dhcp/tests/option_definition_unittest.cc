// Copyright (C) 2012-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <asiolink/io_address.h>
#include <dhcp/dhcp4.h>
#include <dhcp/dhcp6.h>
#include <dhcp/option4_addrlst.h>
#include <dhcp/option6_addrlst.h>
#include <dhcp/option6_ia.h>
#include <dhcp/option6_iaaddr.h>
#include <dhcp/option_custom.h>
#include <dhcp/option_definition.h>
#include <dhcp/option_int.h>
#include <dhcp/option_int_array.h>
#include <dhcp/option_string.h>
#include <dhcp/option_opaque_data_tuples.h>
#include <exceptions/exceptions.h>

#include <boost/pointer_cast.hpp>
#include <boost/shared_ptr.hpp>
#include <gtest/gtest.h>

using namespace std;
using namespace isc;
using namespace isc::dhcp;
using namespace isc::util;

namespace {

/// @brief OptionDefinition test class.
///
/// This class does not do anything useful but we keep
/// it around for the future.
class OptionDefinitionTest : public ::testing::Test {
public:
    /// @brief Constructor
    OptionDefinitionTest() { }

};

// The purpose of this test is to verify that OptionDefinition
// constructor initializes its members correctly.
TEST_F(OptionDefinitionTest, constructor) {
    // Specify the option data type as string. This should get converted
    // to enum value returned by getType().
    OptionDefinition opt_def1("OPTION_CLIENTID", D6O_CLIENTID,
                              DHCP6_OPTION_SPACE, "string");
    EXPECT_EQ("OPTION_CLIENTID", opt_def1.getName());
    EXPECT_EQ(1, opt_def1.getCode());
    EXPECT_EQ(DHCP6_OPTION_SPACE, opt_def1.getOptionSpaceName());
    EXPECT_EQ(OPT_STRING_TYPE, opt_def1.getType());
    EXPECT_FALSE(opt_def1.getArrayType());
    EXPECT_TRUE(opt_def1.getEncapsulatedSpace().empty());
    EXPECT_NO_THROW(opt_def1.validate());

    // Specify the option data type as an enum value.
    OptionDefinition opt_def2("OPTION_RAPID_COMMIT", D6O_RAPID_COMMIT,
                              DHCP6_OPTION_SPACE, OPT_EMPTY_TYPE);
    EXPECT_EQ("OPTION_RAPID_COMMIT", opt_def2.getName());
    EXPECT_EQ(14, opt_def2.getCode());
    EXPECT_EQ(DHCP6_OPTION_SPACE, opt_def2.getOptionSpaceName());
    EXPECT_EQ(OPT_EMPTY_TYPE, opt_def2.getType());
    EXPECT_FALSE(opt_def2.getArrayType());
    EXPECT_TRUE(opt_def2.getEncapsulatedSpace().empty());
    EXPECT_NO_THROW(opt_def2.validate());

    // Specify encapsulated option space name and option data type
    // as enum value.
    OptionDefinition opt_def3("OPTION_VENDOR_OPTS", D6O_VENDOR_OPTS,
                              DHCP6_OPTION_SPACE, OPT_UINT32_TYPE, "isc");
    EXPECT_EQ("OPTION_VENDOR_OPTS", opt_def3.getName());
    EXPECT_EQ(D6O_VENDOR_OPTS, opt_def3.getCode());
    EXPECT_EQ(DHCP6_OPTION_SPACE, opt_def3.getOptionSpaceName());
    EXPECT_EQ(OPT_UINT32_TYPE, opt_def3.getType());
    EXPECT_FALSE(opt_def3.getArrayType());
    EXPECT_EQ("isc", opt_def3.getEncapsulatedSpace());
    EXPECT_NO_THROW(opt_def3.validate());

    // Specify encapsulated option space name and option data type
    // as string value.
    OptionDefinition opt_def4("OPTION_VENDOR_OPTS", D6O_VENDOR_OPTS,
                              DHCP6_OPTION_SPACE, "uint32", "isc");
    EXPECT_EQ("OPTION_VENDOR_OPTS", opt_def4.getName());
    EXPECT_EQ(D6O_VENDOR_OPTS, opt_def4.getCode());
    EXPECT_EQ(DHCP6_OPTION_SPACE, opt_def4.getOptionSpaceName());
    EXPECT_EQ(OPT_UINT32_TYPE, opt_def4.getType());
    EXPECT_FALSE(opt_def4.getArrayType());
    EXPECT_EQ("isc", opt_def4.getEncapsulatedSpace());
    EXPECT_NO_THROW(opt_def4.validate());

    // Check if it is possible to set that option is an array.
    OptionDefinition opt_def5("OPTION_NIS_SERVERS", 27,
                              DHCP6_OPTION_SPACE,
                              OPT_IPV6_ADDRESS_TYPE,
                              true);
    EXPECT_EQ("OPTION_NIS_SERVERS", opt_def5.getName());
    EXPECT_EQ(27, opt_def5.getCode());
    EXPECT_EQ(DHCP6_OPTION_SPACE, opt_def5.getOptionSpaceName());
    EXPECT_EQ(OPT_IPV6_ADDRESS_TYPE, opt_def5.getType());
    EXPECT_TRUE(opt_def5.getArrayType());
    EXPECT_NO_THROW(opt_def5.validate());

    // The created object is invalid if invalid data type is specified but
    // constructor shouldn't throw exception. The object is validated after
    // it has been created.
    EXPECT_NO_THROW(
        OptionDefinition opt_def6("OPTION_SERVERID",
                                  OPT_UNKNOWN_TYPE + 10,
                                  DHCP6_OPTION_SPACE,
                                  OPT_STRING_TYPE);
    );
}

// This test checks that the copy constructor works properly.
TEST_F(OptionDefinitionTest, copyConstructor) {
    OptionDefinition opt_def("option-foo", 27, "my-space", "record", true);
    ASSERT_NO_THROW(opt_def.addRecordField("uint16"));
    ASSERT_NO_THROW(opt_def.addRecordField("string"));

    OptionDefinition opt_def_copy(opt_def);
    EXPECT_EQ("option-foo", opt_def_copy.getName());
    EXPECT_EQ(27, opt_def_copy.getCode());
    EXPECT_EQ("my-space", opt_def_copy.getOptionSpaceName());
    EXPECT_TRUE(opt_def_copy.getArrayType());
    EXPECT_TRUE(opt_def_copy.getEncapsulatedSpace().empty());
    ASSERT_EQ(OPT_RECORD_TYPE, opt_def_copy.getType());
    const OptionDefinition::RecordFieldsCollection fields =
        opt_def_copy.getRecordFields();
    ASSERT_EQ(2, fields.size());
    EXPECT_EQ(OPT_UINT16_TYPE, fields[0]);
    EXPECT_EQ(OPT_STRING_TYPE, fields[1]);

    // Let's make another test to check if encapsulated option space is
    // copied properly.
    OptionDefinition opt_def2("option-bar", 30, "my-space", "uint32", "isc");
    OptionDefinition opt_def_copy2(opt_def2);
    EXPECT_EQ("option-bar", opt_def_copy2.getName());
    EXPECT_EQ(30, opt_def_copy2.getCode());
    EXPECT_EQ("my-space", opt_def_copy2.getOptionSpaceName());
    EXPECT_FALSE(opt_def_copy2.getArrayType());
    EXPECT_EQ(OPT_UINT32_TYPE, opt_def_copy2.getType());
    EXPECT_EQ("isc", opt_def_copy2.getEncapsulatedSpace());
}

// This test checks that the factory function taking string option
// data type as argument creates a valid instance.
TEST_F(OptionDefinitionTest, createStringType) {
    auto def = OptionDefinition::create("option-foo", 123, "my-space",
                                        "uint16", "isc");
    ASSERT_TRUE(def);

    EXPECT_EQ("option-foo", def->getName());
    EXPECT_EQ(123, def->getCode());
    EXPECT_EQ("my-space", def->getOptionSpaceName());
    EXPECT_EQ(OPT_UINT16_TYPE, def->getType());
    EXPECT_FALSE(def->getArrayType());
    EXPECT_EQ("isc", def->getEncapsulatedSpace());
}

// This test checks that the factory function taking enum option
// data type as argument creates a valid instance.
TEST_F(OptionDefinitionTest, createEnumType) {
    auto def = OptionDefinition::create("option-foo", 123, "my-space",
                                        OPT_UINT16_TYPE, "isc");
    ASSERT_TRUE(def);

    EXPECT_EQ("option-foo", def->getName());
    EXPECT_EQ(123, def->getCode());
    EXPECT_EQ("my-space", def->getOptionSpaceName());
    EXPECT_EQ(OPT_UINT16_TYPE, def->getType());
    EXPECT_FALSE(def->getArrayType());
    EXPECT_EQ("isc", def->getEncapsulatedSpace());
}

// This test checks that the factory function creating an array and
// taking string option data type as argument creates a valid instance.
TEST_F(OptionDefinitionTest, createStringTypeArray) {
    auto def = OptionDefinition::create("option-foo", 123, "my-space",
                                        "uint16", true);
    ASSERT_TRUE(def);

    EXPECT_EQ("option-foo", def->getName());
    EXPECT_EQ(123, def->getCode());
    EXPECT_EQ("my-space", def->getOptionSpaceName());
    EXPECT_EQ(OPT_UINT16_TYPE, def->getType());
    EXPECT_TRUE(def->getArrayType());
    EXPECT_TRUE(def->getEncapsulatedSpace().empty());
}

// This test checks that the factory function creating an array and
// taking enum option data type as argument creates a valid instance.
TEST_F(OptionDefinitionTest, createEnumTypeArray) {
    auto def = OptionDefinition::create("option-foo", 123, "my-space",
                                        OPT_UINT16_TYPE, true);
    ASSERT_TRUE(def);

    EXPECT_EQ("option-foo", def->getName());
    EXPECT_EQ(123, def->getCode());
    EXPECT_EQ("my-space", def->getOptionSpaceName());
    EXPECT_EQ(OPT_UINT16_TYPE, def->getType());
    EXPECT_TRUE(def->getArrayType());
    EXPECT_TRUE(def->getEncapsulatedSpace().empty());
}

// This test checks that two option definitions may be compared for equality.
TEST_F(OptionDefinitionTest, equality) {
    // Equal definitions.
    EXPECT_TRUE(OptionDefinition("option-foo", 5, "my-space", "uint16", false)
                == OptionDefinition("option-foo", 5, "my-space", "uint16", false));
    EXPECT_FALSE(OptionDefinition("option-foo", 5, "my-space", "uint16", false)
                 != OptionDefinition("option-foo", 5, "my-space", "uint16", false));

    // Differ by name.
    EXPECT_FALSE(OptionDefinition("option-foo", 5, "my-space", "uint16", false)
                 == OptionDefinition("option-foobar", 5, "my-space", "uint16", false));
    EXPECT_FALSE(OptionDefinition("option-bar", 5, "my-space", "uint16", false)
                == OptionDefinition("option-foo", 5, "my-space", "uint16", false));
    EXPECT_TRUE(OptionDefinition("option-bar", 5, "my-space", "uint16", false)
                 != OptionDefinition("option-foo", 5, "my-space", "uint16", false));

    // Differ by option code.
    EXPECT_FALSE(OptionDefinition("option-foo", 5, "my-space", "uint16", false)
                == OptionDefinition("option-foo", 6, "my-space", "uint16", false));
    EXPECT_TRUE(OptionDefinition("option-foo", 5, "my-space", "uint16", false)
                 != OptionDefinition("option-foo", 6, "my-space", "uint16", false));

    // Differ by option space name.
    EXPECT_FALSE(OptionDefinition("option-foo", 5, "my-space", "uint16", false)
                == OptionDefinition("option-foo", 5, "mi-space", "uint16", false));
    EXPECT_TRUE(OptionDefinition("option-foo", 5, "my-space", "uint16", false)
                 != OptionDefinition("option-foo", 5, "mi-space", "uint16", false));

    // Differ by type of the data.
    EXPECT_FALSE(OptionDefinition("option-foo", 5, "my-space", "uint16", false)
                == OptionDefinition("option-foo", 5, "my-space", "uint32", false));
    EXPECT_TRUE(OptionDefinition("option-foo", 5, "my-space", "uint16", false)
                 != OptionDefinition("option-foo", 5, "my-space", "uint32", false));

    // Differ by array-type property.
    EXPECT_FALSE(OptionDefinition("option-foo", 5, "my-space", "uint16", false)
                == OptionDefinition("option-foo", 5, "my-space", "uint16", true));
    EXPECT_TRUE(OptionDefinition("option-foo", 5, "my-space", "uint16", false)
                 != OptionDefinition("option-foo", 5, "my-space", "uint16", true));

    // Differ by record fields.
    OptionDefinition def1("option-foo", 5, "my-space", "record");
    OptionDefinition def2("option-foo", 5, "my-space", "record");

    // There are no record fields specified yet, so initially they have
    // to be equal.
    ASSERT_TRUE(def1 == def2);
    ASSERT_FALSE(def1 != def2);

    // Add some record fields.
    ASSERT_NO_THROW(def1.addRecordField("uint16"));
    ASSERT_NO_THROW(def2.addRecordField("uint16"));

    // Definitions should still remain equal.
    ASSERT_TRUE(def1 == def2);
    ASSERT_FALSE(def1 != def2);

    // Add additional record field to one of the definitions but not the
    // other. They should now be unequal.
    ASSERT_NO_THROW(def1.addRecordField("string"));
    ASSERT_FALSE(def1 == def2);
    ASSERT_TRUE(def1 != def2);

    // Add the same record field to the other definition. They should now
    // be equal again.
    ASSERT_NO_THROW(def2.addRecordField("string"));
    EXPECT_TRUE(def1 == def2);
    EXPECT_FALSE(def1 != def2);
}

// The purpose of this test is to verify that various data fields
// can be specified for an option definition when this definition
// is marked as 'record' and that fields can't be added if option
// definition is not marked as 'record'.
TEST_F(OptionDefinitionTest, addRecordField) {
    // We can only add fields to record if the option type has been
    // specified as 'record'. We try all other types but 'record'
    // here and expect exception to be thrown.
    for (int i = 0; i < OPT_UNKNOWN_TYPE; ++i) {
        // Do not try for 'record' type because this is the only
        // type for which adding record will succeed.
        if (i == OPT_RECORD_TYPE) {
            continue;
        }
        OptionDefinition opt_def("OPTION_IAADDR", 5, DHCP6_OPTION_SPACE,
                                 static_cast<OptionDataType>(i));
        EXPECT_THROW(opt_def.addRecordField("uint8"), isc::InvalidOperation);
    }

    // Positive scenario starts here.
    OptionDefinition opt_def("OPTION_IAADDR", 5, DHCP6_OPTION_SPACE, "record");
    EXPECT_NO_THROW(opt_def.addRecordField("ipv6-address"));
    EXPECT_NO_THROW(opt_def.addRecordField("uint32"));
    // It should not matter if we specify field type by its name or using enum.
    EXPECT_NO_THROW(opt_def.addRecordField(OPT_UINT32_TYPE));

    // Check what we have actually added.
    OptionDefinition::RecordFieldsCollection fields = opt_def.getRecordFields();
    ASSERT_EQ(3, fields.size());
    EXPECT_EQ(OPT_IPV6_ADDRESS_TYPE, fields[0]);
    EXPECT_EQ(OPT_UINT32_TYPE, fields[1]);
    EXPECT_EQ(OPT_UINT32_TYPE, fields[2]);

    // Let's try some more negative scenarios: use invalid data types.
    EXPECT_THROW(opt_def.addRecordField("unknown_type_xyz"), isc::BadValue);
    OptionDataType invalid_type =
        static_cast<OptionDataType>(OPT_UNKNOWN_TYPE + 10);
    EXPECT_THROW(opt_def.addRecordField(invalid_type), isc::BadValue);

    // It is bad if we use 'record' option type but don't specify
    // at least two fields.
    OptionDefinition opt_def2("OPTION_EMPTY_RECORD", 100, "my-space", "record");
    EXPECT_THROW(opt_def2.validate(), MalformedOptionDefinition);
    opt_def2.addRecordField("uint8");
    EXPECT_THROW(opt_def2.validate(), MalformedOptionDefinition);
    opt_def2.addRecordField("uint32");
    EXPECT_NO_THROW(opt_def2.validate());
}

// The purpose of this test is to check that validate() function
// reports errors for invalid option definitions.
TEST_F(OptionDefinitionTest, validate) {
    // Not supported option type string is not allowed.
    OptionDefinition opt_def1("OPTION_CLIENTID", D6O_CLIENTID,
                              DHCP6_OPTION_SPACE, "non-existent-type");
    EXPECT_THROW(opt_def1.validate(), MalformedOptionDefinition);

    // Not supported option type enum value is not allowed.
    OptionDefinition opt_def2("OPTION_CLIENTID", D6O_CLIENTID,
                              DHCP6_OPTION_SPACE, OPT_UNKNOWN_TYPE);
    EXPECT_THROW(opt_def2.validate(), MalformedOptionDefinition);

    OptionDefinition opt_def3("OPTION_CLIENTID", D6O_CLIENTID,
                              DHCP6_OPTION_SPACE,
                              static_cast<OptionDataType>(OPT_UNKNOWN_TYPE
                                                                      + 2));
    EXPECT_THROW(opt_def3.validate(), MalformedOptionDefinition);

    // Empty option name is not allowed.
    OptionDefinition opt_def4("", D6O_CLIENTID, DHCP6_OPTION_SPACE, "string");
    EXPECT_THROW(opt_def4.validate(), MalformedOptionDefinition);

    // Option name must not contain spaces.
    OptionDefinition opt_def5(" OPTION_CLIENTID", D6O_CLIENTID,
                              DHCP6_OPTION_SPACE, "string");
    EXPECT_THROW(opt_def5.validate(), MalformedOptionDefinition);

    // Option name must not contain spaces.
    OptionDefinition opt_def6("OPTION CLIENTID", D6O_CLIENTID,
                              DHCP6_OPTION_SPACE, "string");
    EXPECT_THROW(opt_def6.validate(), MalformedOptionDefinition);

    // Option name may contain lower case letters.
    OptionDefinition opt_def7("option_clientid", D6O_CLIENTID,
                              DHCP6_OPTION_SPACE, "string");
    EXPECT_NO_THROW(opt_def7.validate());

    // Using digits in option name is legal.
    OptionDefinition opt_def8("option_123", D6O_CLIENTID, DHCP6_OPTION_SPACE,
                              "string");
    EXPECT_NO_THROW(opt_def8.validate());

    // Using hyphen is legal.
    OptionDefinition opt_def9("option-clientid", D6O_CLIENTID,
                              DHCP6_OPTION_SPACE, "string");
    EXPECT_NO_THROW(opt_def9.validate());

    // Using hyphen or underscore at the beginning or at the end
    // of the option name is not allowed.
    OptionDefinition opt_def10("-option-clientid", D6O_CLIENTID,
                               DHCP6_OPTION_SPACE, "string");
    EXPECT_THROW(opt_def10.validate(), MalformedOptionDefinition);

    OptionDefinition opt_def11("_option-clientid", D6O_CLIENTID,
                               DHCP6_OPTION_SPACE, "string");
    EXPECT_THROW(opt_def11.validate(), MalformedOptionDefinition);

    OptionDefinition opt_def12("option-clientid_", D6O_CLIENTID,
                               DHCP6_OPTION_SPACE, "string");
    EXPECT_THROW(opt_def12.validate(), MalformedOptionDefinition);

    OptionDefinition opt_def13("option-clientid-", D6O_CLIENTID,
                               DHCP6_OPTION_SPACE, "string");
    EXPECT_THROW(opt_def13.validate(), MalformedOptionDefinition);

    // Empty option space name is not allowed.
    OptionDefinition opt_def14("OPTION_CLIENTID", D6O_CLIENTID, "", "string");
    EXPECT_THROW(opt_def14.validate(), MalformedOptionDefinition);

    // Option name must not contain spaces.
    OptionDefinition opt_def15("OPTION_CLIENTID", D6O_CLIENTID, " space",
                               "string");
    EXPECT_THROW(opt_def15.validate(), MalformedOptionDefinition);

    // Option name must not contain spaces.
    OptionDefinition opt_def16("OPTION_CLIENTID", D6O_CLIENTID, "my space",
                               "string");
    EXPECT_THROW(opt_def16.validate(), MalformedOptionDefinition);

    // Option name may contain upper case letters.
    OptionDefinition opt_def17("OPTION_CLIENTID", D6O_CLIENTID, "SPACE",
                               "string");
    EXPECT_NO_THROW(opt_def17.validate());

    // Using digits in option name is legal.
    OptionDefinition opt_def18("OPTION_CLIENTID", D6O_CLIENTID, "space_123",
                               "string");
    EXPECT_NO_THROW(opt_def18.validate());

    // Using hyphen is legal.
    OptionDefinition opt_def19("OPTION_CLIENTID", D6O_CLIENTID, "my-space",
                               "string");
    EXPECT_NO_THROW(opt_def19.validate());

    // Using hyphen or underscore at the beginning or at the end
    // of the option name is not allowed.
    OptionDefinition opt_def20("OPTION_CLIENTID", D6O_CLIENTID, "-space",
                               "string");
    EXPECT_THROW(opt_def20.validate(), MalformedOptionDefinition);

    OptionDefinition opt_def21("OPTION_CLIENTID", D6O_CLIENTID, "_space",
                               "string");
    EXPECT_THROW(opt_def21.validate(), MalformedOptionDefinition);

    OptionDefinition opt_def22("OPTION_CLIENTID", D6O_CLIENTID, "space_",
                               "string");
    EXPECT_THROW(opt_def22.validate(), MalformedOptionDefinition);

    OptionDefinition opt_def23("OPTION_CLIENTID", D6O_CLIENTID, "space-",
                               "string");
    EXPECT_THROW(opt_def23.validate(), MalformedOptionDefinition);

    // Having array of strings does not make sense because there is no way
    // to determine string's length.
    OptionDefinition opt_def24("OPTION_CLIENTID", D6O_CLIENTID,
                               DHCP6_OPTION_SPACE, "string", true);
    EXPECT_THROW(opt_def24.validate(), MalformedOptionDefinition);

    // It does not make sense to have string field within the record before
    // other fields because there is no way to determine the length of this
    // string and thus there is no way to determine where the other field
    // begins.
    OptionDefinition opt_def25("OPTION_STATUS_CODE", D6O_STATUS_CODE,
                               DHCP6_OPTION_SPACE, "record");
    opt_def25.addRecordField("string");
    opt_def25.addRecordField("uint16");
    EXPECT_THROW(opt_def25.validate(), MalformedOptionDefinition);

    // ... but it is ok if the string value is the last one.
    OptionDefinition opt_def26("OPTION_STATUS_CODE", D6O_STATUS_CODE,
                               DHCP6_OPTION_SPACE, "record");
    opt_def26.addRecordField("uint8");
    opt_def26.addRecordField("string");
    EXPECT_NO_THROW(opt_def26.validate());

    // ... at least if it is not an array.
    OptionDefinition opt_def27("OPTION_STATUS_CODE", D6O_STATUS_CODE,
                               DHCP6_OPTION_SPACE, "record", true);
    opt_def27.addRecordField("uint8");
    opt_def27.addRecordField("string");
    EXPECT_THROW(opt_def27.validate(), MalformedOptionDefinition);

    // Check invalid encapsulated option space name.
    OptionDefinition opt_def28("OPTION_VENDOR_OPTS", D6O_VENDOR_OPTS,
                               DHCP6_OPTION_SPACE, "uint32",
                               "invalid%space%name");
    EXPECT_THROW(opt_def28.validate(), MalformedOptionDefinition);
}


// The purpose of this test is to verify that option definition
// that comprises array of IPv6 addresses will return an instance
// of option with a list of IPv6 addresses.
TEST_F(OptionDefinitionTest, ipv6AddressArray) {
    OptionDefinition opt_def("OPTION_NIS_SERVERS", D6O_NIS_SERVERS,
                             DHCP6_OPTION_SPACE, "ipv6-address", true);

    // Create a list of some V6 addresses.
    std::vector<asiolink::IOAddress> addrs;
    addrs.push_back(asiolink::IOAddress("2001:0db8::ff00:0042:8329"));
    addrs.push_back(asiolink::IOAddress("2001:0db8::ff00:0042:2319"));
    addrs.push_back(asiolink::IOAddress("::1"));
    addrs.push_back(asiolink::IOAddress("::2"));

    // Write addresses to the buffer.
    OptionBuffer buf(addrs.size() * asiolink::V6ADDRESS_LEN);
    for (size_t i = 0; i < addrs.size(); ++i) {
        const std::vector<uint8_t>& vec = addrs[i].toBytes();
        ASSERT_EQ(asiolink::V6ADDRESS_LEN, vec.size());
        std::copy(vec.begin(), vec.end(),
                  buf.begin() + i * asiolink::V6ADDRESS_LEN);
    }
    // Create DHCPv6 option from this buffer. Once option is created it is
    // supposed to have internal list of addresses that it parses out from
    // the provided buffer.
    OptionPtr option_v6;
    ASSERT_NO_THROW(
        option_v6 = opt_def.optionFactory(Option::V6, D6O_NIS_SERVERS, buf);
    );
    const Option* optptr = option_v6.get();
    ASSERT_TRUE(optptr);
    ASSERT_TRUE(typeid(*optptr) == typeid(Option6AddrLst));
    boost::shared_ptr<Option6AddrLst> option_cast_v6 =
        boost::static_pointer_cast<Option6AddrLst>(option_v6);
    ASSERT_TRUE(option_cast_v6);
    // Get the list of parsed addresses from the option object.
    std::vector<asiolink::IOAddress> addrs_returned =
        option_cast_v6->getAddresses();
    // The list of addresses must exactly match addresses that we
    // stored in the buffer to create the option from it.
    EXPECT_TRUE(std::equal(addrs.begin(), addrs.end(), addrs_returned.begin()));

    // The provided buffer's length must be a multiple of V6 address length.
    // Let's extend the buffer by one byte so as this condition is not
    // fulfilled anymore.
    buf.insert(buf.end(), 1, 1);
    // It should throw exception then.
    EXPECT_THROW(
        opt_def.optionFactory(Option::V6, D6O_NIS_SERVERS, buf),
        InvalidOptionValue
    );
}

// The purpose of this test is to verify that option definition
// that comprises array of IPv6 addresses will return an instance
// of option with a list of IPv6 addresses. Array of IPv6 addresses
// is specified as a vector of strings (each string represents single
// IPv6 address).
TEST_F(OptionDefinitionTest, ipv6AddressArrayTokenized) {
    OptionDefinition opt_def("OPTION_NIS_SERVERS", D6O_NIS_SERVERS,
                             DHCP6_OPTION_SPACE, "ipv6-address", true);

    // Create a vector of some V6 addresses.
    std::vector<asiolink::IOAddress> addrs;
    addrs.push_back(asiolink::IOAddress("2001:0db8::ff00:0042:8329"));
    addrs.push_back(asiolink::IOAddress("2001:0db8::ff00:0042:2319"));
    addrs.push_back(asiolink::IOAddress("::1"));
    addrs.push_back(asiolink::IOAddress("::2"));

    // Create a vector of strings representing addresses given above.
    std::vector<std::string> addrs_str;
    for (std::vector<asiolink::IOAddress>::const_iterator it = addrs.begin();
         it != addrs.end(); ++it) {
        addrs_str.push_back(it->toText());
    }

    // Create DHCPv6 option using the list of IPv6 addresses given in the
    // string form.
    OptionPtr option_v6;
    ASSERT_NO_THROW(
        option_v6 = opt_def.optionFactory(Option::V6, D6O_NIS_SERVERS,
                                          addrs_str);
    );
    // Non-null pointer option is supposed to be returned and it
    // should have Option6AddrLst type.
    ASSERT_TRUE(option_v6);
    const Option* optptr = option_v6.get();
    ASSERT_TRUE(optptr);
    ASSERT_TRUE(typeid(*optptr) == typeid(Option6AddrLst));
    // Cast to the actual option type to get IPv6 addresses from it.
    boost::shared_ptr<Option6AddrLst> option_cast_v6 =
        boost::static_pointer_cast<Option6AddrLst>(option_v6);
    // Check that cast was successful.
    ASSERT_TRUE(option_cast_v6);
    // Get the list of parsed addresses from the option object.
    std::vector<asiolink::IOAddress> addrs_returned =
        option_cast_v6->getAddresses();
    // Returned addresses must match the addresses that have been used to create
    // the option instance.
    EXPECT_TRUE(std::equal(addrs.begin(), addrs.end(), addrs_returned.begin()));
}

// The purpose of this test is to verify that option definition
// that comprises array of IPv4 addresses will return an instance
// of option with a list of IPv4 addresses.
TEST_F(OptionDefinitionTest, ipv4AddressArray) {
    OptionDefinition opt_def("OPTION_NAME_SERVERS", D6O_NIS_SERVERS,
                             DHCP6_OPTION_SPACE, "ipv4-address", true);

    // Create a list of some V6 addresses.
    std::vector<asiolink::IOAddress> addrs;
    addrs.push_back(asiolink::IOAddress("192.168.0.1"));
    addrs.push_back(asiolink::IOAddress("172.16.1.1"));
    addrs.push_back(asiolink::IOAddress("127.0.0.1"));
    addrs.push_back(asiolink::IOAddress("213.41.23.12"));

    // Write addresses to the buffer.
    OptionBuffer buf(addrs.size() * asiolink::V4ADDRESS_LEN);
    for (size_t i = 0; i < addrs.size(); ++i) {
        const std::vector<uint8_t> vec = addrs[i].toBytes();
        ASSERT_EQ(asiolink::V4ADDRESS_LEN, vec.size());
        std::copy(vec.begin(), vec.end(),
                  buf.begin() + i * asiolink::V4ADDRESS_LEN);
    }
    // Create DHCPv6 option from this buffer. Once option is created it is
    // supposed to have internal list of addresses that it parses out from
    // the provided buffer.
    OptionPtr option_v4;
    ASSERT_NO_THROW(
        option_v4 = opt_def.optionFactory(Option::V4, DHO_NAME_SERVERS, buf)
    );
    const Option* optptr = option_v4.get();
    ASSERT_TRUE(optptr);
    ASSERT_TRUE(typeid(*optptr) == typeid(Option4AddrLst));
    // Get the list of parsed addresses from the option object.
    boost::shared_ptr<Option4AddrLst> option_cast_v4 =
        boost::static_pointer_cast<Option4AddrLst>(option_v4);
    std::vector<asiolink::IOAddress> addrs_returned =
        option_cast_v4->getAddresses();
    // The list of addresses must exactly match addresses that we
    // stored in the buffer to create the option from it.
    EXPECT_TRUE(std::equal(addrs.begin(), addrs.end(), addrs_returned.begin()));

    // The provided buffer's length must be a multiple of V4 address length.
    // Let's extend the buffer by one byte so as this condition is not
    // fulfilled anymore.
    buf.insert(buf.end(), 1, 1);
    // It should throw exception then.
    EXPECT_THROW(opt_def.optionFactory(Option::V4, DHO_NIS_SERVERS, buf),
                 InvalidOptionValue);
}

// The purpose of this test is to verify that option definition
// that comprises array of IPv4 addresses will return an instance
// of option with a list of IPv4 addresses. The array of IPv4 addresses
// is specified as a vector of strings (each string represents single
// IPv4 address).
TEST_F(OptionDefinitionTest, ipv4AddressArrayTokenized) {
    OptionDefinition opt_def("OPTION_NIS_SERVERS", DHO_NIS_SERVERS,
                             DHCP4_OPTION_SPACE, "ipv4-address", true);

    // Create a vector of some V6 addresses.
    std::vector<asiolink::IOAddress> addrs;
    addrs.push_back(asiolink::IOAddress("192.168.0.1"));
    addrs.push_back(asiolink::IOAddress("172.16.1.1"));
    addrs.push_back(asiolink::IOAddress("127.0.0.1"));
    addrs.push_back(asiolink::IOAddress("213.41.23.12"));

    // Create a vector of strings representing addresses given above.
    std::vector<std::string> addrs_str;
    for (std::vector<asiolink::IOAddress>::const_iterator it = addrs.begin();
         it != addrs.end(); ++it) {
        addrs_str.push_back(it->toText());
    }

    // Create DHCPv4 option using the list of IPv4 addresses given in the
    // string form.
    OptionPtr option_v4;
    ASSERT_NO_THROW(
        option_v4 = opt_def.optionFactory(Option::V4, DHO_NIS_SERVERS,
                                          addrs_str);
    );
    // Non-null pointer option is supposed to be returned and it
    // should have Option6AddrLst type.
    ASSERT_TRUE(option_v4);
    const Option* optptr = option_v4.get();
    ASSERT_TRUE(optptr);
    ASSERT_TRUE(typeid(*optptr) == typeid(Option4AddrLst));
    // Cast to the actual option type to get IPv4 addresses from it.
    boost::shared_ptr<Option4AddrLst> option_cast_v4 =
        boost::static_pointer_cast<Option4AddrLst>(option_v4);
    // Check that cast was successful.
    ASSERT_TRUE(option_cast_v4);
    // Get the list of parsed addresses from the option object.
    std::vector<asiolink::IOAddress> addrs_returned =
        option_cast_v4->getAddresses();
    // Returned addresses must match the addresses that have been used to create
    // the option instance.
    EXPECT_TRUE(std::equal(addrs.begin(), addrs.end(), addrs_returned.begin()));
}

// The purpose of this test is to verify that option definition for
// 'empty' option can be created and that it returns 'empty' option.
TEST_F(OptionDefinitionTest, empty) {
    OptionDefinition opt_def("OPTION_RAPID_COMMIT", D6O_RAPID_COMMIT,
                             DHCP6_OPTION_SPACE, "empty");

    // Create option instance and provide empty buffer as expected.
    OptionPtr option_v6;
    ASSERT_NO_THROW(
        option_v6 = opt_def.optionFactory(Option::V6, D6O_RAPID_COMMIT, OptionBuffer())
    );
    const Option* optptr = option_v6.get();
    ASSERT_TRUE(optptr);
    ASSERT_TRUE(typeid(*optptr) == typeid(Option));
    // Expect 'empty' DHCPv6 option.
    EXPECT_EQ(Option::V6, option_v6->getUniverse());
    EXPECT_EQ(4, option_v6->getHeaderLen());
    EXPECT_EQ(0, option_v6->getData().size());

    // Repeat the same test scenario for DHCPv4 option.
    OptionPtr option_v4;
    ASSERT_NO_THROW(option_v4 = opt_def.optionFactory(Option::V4, 214, OptionBuffer()));
    // Expect 'empty' DHCPv4 option.
    EXPECT_EQ(Option::V4, option_v4->getUniverse());
    EXPECT_EQ(2, option_v4->getHeaderLen());
    EXPECT_EQ(0, option_v4->getData().size());
}

// The purpose of this test is to verify that when the empty option encapsulates
// some option space, an instance of the OptionCustom is returned and its
// suboptions are decoded.
TEST_F(OptionDefinitionTest, emptyWithSuboptions) {
    // Create an instance of the 'empty' option definition. This option
    // encapsulates 'option-foo-space' so when we create a new option
    // with this definition the OptionCustom should be returned. The
    // Option Custom is generic option which support variety of formats
    // and supports decoding suboptions.
    OptionDefinition opt_def("option-foo", 1024, "my-space", "empty",
                             "option-foo-space");
    // Define a suboption.
    const uint8_t subopt_data[] = {
        0x04, 0x01,  // Option code 1025
        0x00, 0x04,  // Option len = 4
        0x01, 0x02, 0x03, 0x04 // Option data
    };

    // Create an option, having option code 1024 from the definition. Pass
    // the option buffer containing suboption.
    OptionPtr option_v6;
    ASSERT_NO_THROW(
        option_v6 = opt_def.optionFactory(Option::V6, 1024,
                                          OptionBuffer(subopt_data,
                                                       subopt_data +
                                                       sizeof(subopt_data)))
    );
    // Returned option should be of the OptionCustom type.
    const Option* optptr = option_v6.get();
    ASSERT_TRUE(optptr);
    ASSERT_TRUE(typeid(*optptr) == typeid(OptionCustom));
    // Sanity-check length, universe etc.
    EXPECT_EQ(Option::V6, option_v6->getUniverse());
    EXPECT_EQ(4, option_v6->getHeaderLen());
    // This option should have one suboption with the code of 1025.
    OptionPtr subopt_v6 = option_v6->getOption(1025);
    EXPECT_TRUE(subopt_v6);
    // Check that this suboption holds valid data.
    EXPECT_EQ(1025, subopt_v6->getType());
    EXPECT_EQ(Option::V6, subopt_v6->getUniverse());
    EXPECT_EQ(0, memcmp(&subopt_v6->getData()[0], subopt_data + 4, 4));

    // @todo consider having a similar test for V4.
}

// The purpose of this test is to verify that definition can be
// creates for the option that holds binary data.
TEST_F(OptionDefinitionTest, binary) {
    // Binary option is the one that is represented by the generic
    // Option class. In fact all options can be represented by this
    // class but for some of them it is just natural. The SERVERID
    // option consists of the option code, length and binary data so
    // this one was picked for this test.
    OptionDefinition opt_def("OPTION_SERVERID", D6O_SERVERID,
                             DHCP6_OPTION_SPACE, "binary");

    // Prepare some dummy data (serverid): 0, 1, 2 etc.
    OptionBuffer buf(14);
    for (unsigned i = 0; i < 14; ++i) {
        buf[i] = i;
    }
    // Create option instance with the factory function.
    // If the OptionDefinition code works properly than
    // object of the type Option should be returned.
    OptionPtr option_v6;
    ASSERT_NO_THROW(
        option_v6 = opt_def.optionFactory(Option::V6, D6O_SERVERID, buf);
    );
    // Expect base option type returned.
    const Option* optptr = option_v6.get();
    ASSERT_TRUE(optptr);
    ASSERT_TRUE(typeid(*optptr) == typeid(Option));
    // Sanity check on universe, length and size. These are
    // the basic parameters identifying any option.
    EXPECT_EQ(Option::V6, option_v6->getUniverse());
    EXPECT_EQ(4, option_v6->getHeaderLen());
    ASSERT_EQ(buf.size(), option_v6->getData().size());

    // Get the server id data from the option and compare
    // against reference buffer. They are expected to match.
    EXPECT_TRUE(std::equal(option_v6->getData().begin(),
                           option_v6->getData().end(),
                           buf.begin()));

    // Repeat the same test scenario for DHCPv4 option.
    OptionPtr option_v4;
    ASSERT_NO_THROW(option_v4 = opt_def.optionFactory(Option::V4, 214, buf));
    // Expect 'empty' DHCPv4 option.
    EXPECT_EQ(Option::V4, option_v4->getUniverse());
    EXPECT_EQ(2, option_v4->getHeaderLen());
    ASSERT_EQ(buf.size(), option_v4->getData().size());

    EXPECT_TRUE(std::equal(option_v6->getData().begin(),
                           option_v6->getData().end(),
                           buf.begin()));
}

// The purpose of this test is to verify that definition can be created
// for option that comprises record of data. In this particular test
// the IA_NA option is used. This option comprises three uint32 fields.
TEST_F(OptionDefinitionTest, recordIA6) {
    // This option consists of IAID, T1 and T2 fields (each 4 bytes long).
    const int option6_ia_len = 12;

    // Get the factory function pointer.
    OptionDefinition opt_def("OPTION_IA_NA", D6O_IA_NA, DHCP6_OPTION_SPACE,
                             "record", false);
    // Each data field is uint32.
    for (int i = 0; i < 3; ++i) {
        EXPECT_NO_THROW(opt_def.addRecordField("uint32"));
    }

    // Check the positive scenario.
    OptionBuffer buf(12);
    for (size_t i = 0; i < buf.size(); ++i) {
        buf[i] = i;
    }
    OptionPtr option_v6;
    ASSERT_NO_THROW(option_v6 = opt_def.optionFactory(Option::V6, D6O_IA_NA, buf));
    const Option* optptr = option_v6.get();
    ASSERT_TRUE(optptr);
    ASSERT_TRUE(typeid(*optptr) == typeid(Option6IA));
    boost::shared_ptr<Option6IA> option_cast_v6 =
        boost::static_pointer_cast<Option6IA>(option_v6);
    EXPECT_EQ(0x00010203, option_cast_v6->getIAID());
    EXPECT_EQ(0x04050607, option_cast_v6->getT1());
    EXPECT_EQ(0x08090A0B, option_cast_v6->getT2());

    // The length of the buffer must be at least 12 bytes.
    // Check too short buffer.
    EXPECT_THROW(
        opt_def.optionFactory(Option::V6, D6O_IA_NA, OptionBuffer(option6_ia_len - 1)),
        InvalidOptionValue
     );
}

// The purpose of this test is to verify that definition can be created
// for option that comprises record of data. In this particular test
// the IAADDR option is used.
TEST_F(OptionDefinitionTest, recordIAAddr6) {
    // This option consists of IPV6 Address (16 bytes) and preferred-lifetime and
    // valid-lifetime fields (each 4 bytes long).
    const int option6_iaaddr_len = 24;

    OptionDefinition opt_def("OPTION_IAADDR", D6O_IAADDR, DHCP6_OPTION_SPACE,
                             "record");
    ASSERT_NO_THROW(opt_def.addRecordField("ipv6-address"));
    ASSERT_NO_THROW(opt_def.addRecordField("uint32"));
    ASSERT_NO_THROW(opt_def.addRecordField("uint32"));

    // Check the positive scenario.
    OptionPtr option_v6;
    asiolink::IOAddress addr_v6("2001:0db8::ff00:0042:8329");
    OptionBuffer buf(asiolink::V6ADDRESS_LEN);
    ASSERT_TRUE(addr_v6.isV6());
    const std::vector<uint8_t>& vec = addr_v6.toBytes();
    ASSERT_EQ(asiolink::V6ADDRESS_LEN, vec.size());
    std::copy(vec.begin(), vec.end(), buf.begin());

    for (unsigned i = 0;
         i < option6_iaaddr_len - asiolink::V6ADDRESS_LEN;
         ++i) {
        buf.push_back(i);
    }
    ASSERT_NO_THROW(option_v6 = opt_def.optionFactory(Option::V6, D6O_IAADDR, buf));
    const Option* optptr = option_v6.get();
    ASSERT_TRUE(optptr);
    ASSERT_TRUE(typeid(*optptr) == typeid(Option6IAAddr));
    boost::shared_ptr<Option6IAAddr> option_cast_v6 =
        boost::static_pointer_cast<Option6IAAddr>(option_v6);
    EXPECT_EQ(addr_v6, option_cast_v6->getAddress());
    EXPECT_EQ(0x00010203, option_cast_v6->getPreferred());
    EXPECT_EQ(0x04050607, option_cast_v6->getValid());

    // The length of the buffer must be at least 12 bytes.
    // Check too short buffer.
    EXPECT_THROW(
        opt_def.optionFactory(Option::V6, D6O_IAADDR, OptionBuffer(option6_iaaddr_len - 1)),
        InvalidOptionValue
     );
}

// The purpose of this test is to verify that definition can be created
// for option that comprises record of data. In this particular test
// the IAADDR option is used. The data for the option is specified as
// a vector of strings. Each string carries the data for the corresponding
// data field.
TEST_F(OptionDefinitionTest, recordIAAddr6Tokenized) {
    // This option consists of IPV6 Address (16 bytes) and preferred-lifetime and
    // valid-lifetime fields (each 4 bytes long).
    OptionDefinition opt_def("OPTION_IAADDR", D6O_IAADDR, DHCP6_OPTION_SPACE,
                             "record");
    ASSERT_NO_THROW(opt_def.addRecordField("ipv6-address"));
    ASSERT_NO_THROW(opt_def.addRecordField("uint32"));
    ASSERT_NO_THROW(opt_def.addRecordField("uint32"));

    // Check the positive scenario.
    std::vector<std::string> data_field_values;
    data_field_values.push_back("2001:0db8::ff00:0042:8329");
    data_field_values.push_back("1234");
    data_field_values.push_back("5678");

    OptionPtr option_v6;
    ASSERT_NO_THROW(option_v6 = opt_def.optionFactory(Option::V6, D6O_IAADDR,
                                                      data_field_values));
    const Option* optptr = option_v6.get();
    ASSERT_TRUE(optptr);
    ASSERT_TRUE(typeid(*optptr) == typeid(Option6IAAddr));
    boost::shared_ptr<Option6IAAddr> option_cast_v6 =
        boost::static_pointer_cast<Option6IAAddr>(option_v6);
    EXPECT_EQ("2001:db8::ff00:42:8329", option_cast_v6->getAddress().toText());
    EXPECT_EQ(1234, option_cast_v6->getPreferred());
    EXPECT_EQ(5678, option_cast_v6->getValid());
}

// The purpose of this test is to verify that the definition for option
// that comprises a boolean value can be created and that this definition
// can be used to create and option with a single boolean value.
TEST_F(OptionDefinitionTest, boolValue) {
    // The IP Forwarding option comprises one boolean value.
    OptionDefinition opt_def("ip-forwarding", DHO_IP_FORWARDING,
                             DHCP4_OPTION_SPACE, "boolean");

    OptionPtr option_v4;
    // Use an option buffer which holds one value of 1 (true).
    ASSERT_NO_THROW(
        option_v4 = opt_def.optionFactory(Option::V4, DHO_IP_FORWARDING,
                                          OptionBuffer(1, 1));
    );
    const Option* optptr = option_v4.get();
    ASSERT_TRUE(optptr);
    ASSERT_TRUE(typeid(*optptr) == typeid(OptionCustom));
    // Validate parsed value in the received option.
    boost::shared_ptr<OptionCustom> option_cast_v4 =
        boost::static_pointer_cast<OptionCustom>(option_v4);
    EXPECT_TRUE(option_cast_v4->readBoolean());

    // Repeat the test above, but set the value to 0 (false).
    ASSERT_NO_THROW(
        option_v4 = opt_def.optionFactory(Option::V4, DHO_IP_FORWARDING,
                                          OptionBuffer(1, 0));
    );
    option_cast_v4 = boost::static_pointer_cast<OptionCustom>(option_v4);
    EXPECT_FALSE(option_cast_v4->readBoolean());

    // Try to provide zero-length buffer. Expect exception.
    EXPECT_THROW(
        opt_def.optionFactory(Option::V4, DHO_IP_FORWARDING, OptionBuffer()),
        InvalidOptionValue
    );

}

// The purpose of this test is to verify that definition for option that
// comprises single boolean value can be created and that this definition
// can be used to create an option holding a single boolean value. The
// boolean value is converted from a string which is expected to hold
// the following values: "true", "false", "1" or "0". For all other
// values exception should be thrown.
TEST_F(OptionDefinitionTest, boolTokenized) {
    OptionDefinition opt_def("ip-forwarding", DHO_IP_FORWARDING,
                             DHCP6_OPTION_SPACE, "boolean");

    OptionPtr option_v4;
    std::vector<std::string> values;
    // Specify a value for the option instance being created.
    values.push_back("true");
    ASSERT_NO_THROW(
        option_v4 = opt_def.optionFactory(Option::V4, DHO_IP_FORWARDING,
                                          values);
    );
    const Option* optptr = option_v4.get();
    ASSERT_TRUE(optptr);
    ASSERT_TRUE(typeid(*optptr) == typeid(OptionCustom));
    // Validate the value.
    OptionCustomPtr option_cast_v4 =
        boost::static_pointer_cast<OptionCustom>(option_v4);
    EXPECT_TRUE(option_cast_v4->readBoolean());

    // Repeat the test but for "false" value this time.
    values[0] = "false";
    ASSERT_NO_THROW(
        option_v4 = opt_def.optionFactory(Option::V4, DHO_IP_FORWARDING,
                                          values);
    );
    optptr = option_v4.get();
    ASSERT_TRUE(optptr);
    ASSERT_TRUE(typeid(*optptr) == typeid(OptionCustom));
    // Validate the value.
    option_cast_v4 = boost::static_pointer_cast<OptionCustom>(option_v4);
    EXPECT_FALSE(option_cast_v4->readBoolean());

    // Check if that will work for numeric values.
    values[0] = "0";
    ASSERT_NO_THROW(
        option_v4 = opt_def.optionFactory(Option::V4, DHO_IP_FORWARDING,
                                          values);
    );
    optptr = option_v4.get();
    ASSERT_TRUE(optptr);
    ASSERT_TRUE(typeid(*optptr) == typeid(OptionCustom));
    // Validate the value.
    option_cast_v4 = boost::static_pointer_cast<OptionCustom>(option_v4);
    EXPECT_FALSE(option_cast_v4->readBoolean());

    // Swap numeric values and test if it works for "true" case.
    values[0] = "1";
    ASSERT_NO_THROW(
        option_v4 = opt_def.optionFactory(Option::V4, DHO_IP_FORWARDING,
                                          values);
    );
    optptr = option_v4.get();
    ASSERT_TRUE(optptr);
    ASSERT_TRUE(typeid(*optptr) == typeid(OptionCustom));
    // Validate the value.
    option_cast_v4 = boost::static_pointer_cast<OptionCustom>(option_v4);
    EXPECT_TRUE(option_cast_v4->readBoolean());

    // A conversion of non-numeric value to boolean should fail if
    // this value is neither "true" nor "false".
    values[0] = "garbage";
    EXPECT_THROW(opt_def.optionFactory(Option::V4, DHO_IP_FORWARDING, values),
      isc::dhcp::BadDataTypeCast);

    // A conversion of numeric value to boolean should fail if this value
    // is neither "0" nor "1".
    values[0] = "2";
    EXPECT_THROW(opt_def.optionFactory(Option::V4, DHO_IP_FORWARDING, values),
      isc::dhcp::BadDataTypeCast);

}

// The purpose of this test is to verify that definition for option that
// comprises single uint8 value can be created and that this definition
// can be used to create an option with single uint8 value.
TEST_F(OptionDefinitionTest, uint8) {
    OptionDefinition opt_def("OPTION_PREFERENCE", D6O_PREFERENCE,
                             DHCP6_OPTION_SPACE, "uint8");

    OptionPtr option_v6;
    // Try to use correct buffer length = 1 byte.
    ASSERT_NO_THROW(
        option_v6 = opt_def.optionFactory(Option::V6, D6O_PREFERENCE,
                                          OptionBuffer(1, 1));
    );
    const Option* optptr = option_v6.get();
    ASSERT_TRUE(optptr);
    ASSERT_TRUE(typeid(*optptr) == typeid(OptionInt<uint8_t>));
    // Validate the value.
    boost::shared_ptr<OptionInt<uint8_t> > option_cast_v6 =
        boost::static_pointer_cast<OptionInt<uint8_t> >(option_v6);
    EXPECT_EQ(1, option_cast_v6->getValue());

    // Try to provide zero-length buffer. Expect exception.
    EXPECT_THROW(
        option_v6 = opt_def.optionFactory(Option::V6, D6O_PREFERENCE, OptionBuffer()),
        InvalidOptionValue
    );

    // @todo Add more cases for DHCPv4
}

// The purpose of this test is to verify that definition for option that
// comprises single uint8 value can be created and that this definition
// can be used to create an option with single uint8 value.
TEST_F(OptionDefinitionTest, uint8Tokenized) {
    OptionDefinition opt_def("OPTION_PREFERENCE", D6O_PREFERENCE,
                             DHCP6_OPTION_SPACE, "uint8");

    OptionPtr option_v6;
    std::vector<std::string> values;
    values.push_back("123");
    values.push_back("456");
    ASSERT_NO_THROW(
        option_v6 = opt_def.optionFactory(Option::V6, D6O_PREFERENCE, values);
    );
    const Option* optptr = option_v6.get();
    ASSERT_TRUE(optptr);
    ASSERT_TRUE(typeid(*optptr) == typeid(OptionInt<uint8_t>));
    // Validate the value.
    boost::shared_ptr<OptionInt<uint8_t> > option_cast_v6 =
        boost::static_pointer_cast<OptionInt<uint8_t> >(option_v6);
    EXPECT_EQ(123, option_cast_v6->getValue());

    // @todo Add more cases for DHCPv4
}

// The purpose of this test is to verify that definition for option that
// comprises single uint16 value can be created and that this definition
// can be used to create an option with single uint16 value.
TEST_F(OptionDefinitionTest, uint16) {
    OptionDefinition opt_def("OPTION_ELAPSED_TIME", D6O_ELAPSED_TIME,
                             DHCP6_OPTION_SPACE, "uint16");

    OptionPtr option_v6;
    // Try to use correct buffer length = 2 bytes.
    OptionBuffer buf;
    buf.push_back(1);
    buf.push_back(2);
    ASSERT_NO_THROW(
        option_v6 = opt_def.optionFactory(Option::V6, D6O_ELAPSED_TIME, buf);
    );
    const Option* optptr = option_v6.get();
    ASSERT_TRUE(optptr);
    ASSERT_TRUE(typeid(*optptr) == typeid(OptionInt<uint16_t>));
    // Validate the value.
    boost::shared_ptr<OptionInt<uint16_t> > option_cast_v6 =
        boost::static_pointer_cast<OptionInt<uint16_t> >(option_v6);
    EXPECT_EQ(0x0102, option_cast_v6->getValue());

    // Try to provide zero-length buffer. Expect exception.
    EXPECT_THROW(
        option_v6 = opt_def.optionFactory(Option::V6, D6O_ELAPSED_TIME, OptionBuffer(1)),
        InvalidOptionValue
    );

    // @todo Add more cases for DHCPv4
}

// The purpose of this test is to verify that definition for option that
// comprises single uint16 value can be created and that this definition
// can be used to create an option with single uint16 value.
TEST_F(OptionDefinitionTest, uint16Tokenized) {
    OptionDefinition opt_def("OPTION_ELAPSED_TIME", D6O_ELAPSED_TIME,
                             DHCP6_OPTION_SPACE, "uint16");

    OptionPtr option_v6;

    std::vector<std::string> values;
    values.push_back("1234");
    values.push_back("5678");
    ASSERT_NO_THROW(
        option_v6 = opt_def.optionFactory(Option::V6, D6O_ELAPSED_TIME, values);
    );
    const Option* optptr = option_v6.get();
    ASSERT_TRUE(optptr);
    ASSERT_TRUE(typeid(*optptr) == typeid(OptionInt<uint16_t>));
    // Validate the value.
    boost::shared_ptr<OptionInt<uint16_t> > option_cast_v6 =
        boost::static_pointer_cast<OptionInt<uint16_t> >(option_v6);
    EXPECT_EQ(1234, option_cast_v6->getValue());

    // @todo Add more cases for DHCPv4

}

// The purpose of this test is to verify that definition for option that
// comprises single uint32 value can be created and that this definition
// can be used to create an option with single uint32 value.
TEST_F(OptionDefinitionTest, uint32) {
    OptionDefinition opt_def("OPTION_CLT_TIME", D6O_CLT_TIME,
                             DHCP6_OPTION_SPACE, "uint32");

    OptionPtr option_v6;
    OptionBuffer buf;
    buf.push_back(1);
    buf.push_back(2);
    buf.push_back(3);
    buf.push_back(4);
    ASSERT_NO_THROW(
        option_v6 = opt_def.optionFactory(Option::V6, D6O_CLT_TIME, buf);
    );
    const Option* optptr = option_v6.get();
    ASSERT_TRUE(optptr);
    ASSERT_TRUE(typeid(*optptr) == typeid(OptionInt<uint32_t>));
    // Validate the value.
    boost::shared_ptr<OptionInt<uint32_t> > option_cast_v6 =
        boost::static_pointer_cast<OptionInt<uint32_t> >(option_v6);
    EXPECT_EQ(0x01020304, option_cast_v6->getValue());

    // Try to provide too short buffer. Expect exception.
    EXPECT_THROW(
        option_v6 = opt_def.optionFactory(Option::V6, D6O_CLT_TIME, OptionBuffer(2)),
        InvalidOptionValue
    );

    // @todo Add more cases for DHCPv4
}

// The purpose of this test is to verify that definition for option that
// comprises single uint32 value can be created and that this definition
// can be used to create an option with single uint32 value.
TEST_F(OptionDefinitionTest, uint32Tokenized) {
    OptionDefinition opt_def("OPTION_CLT_TIME", D6O_CLT_TIME,
                             DHCP6_OPTION_SPACE, "uint32");

    OptionPtr option_v6;
    std::vector<std::string> values;
    values.push_back("123456");
    values.push_back("789");
    ASSERT_NO_THROW(
        option_v6 = opt_def.optionFactory(Option::V6, D6O_CLT_TIME, values);
    );
    const Option* optptr = option_v6.get();
    ASSERT_TRUE(optptr);
    ASSERT_TRUE(typeid(*optptr) == typeid(OptionInt<uint32_t>));
    // Validate the value.
    boost::shared_ptr<OptionInt<uint32_t> > option_cast_v6 =
        boost::static_pointer_cast<OptionInt<uint32_t> >(option_v6);
    EXPECT_EQ(123456, option_cast_v6->getValue());

    // @todo Add more cases for DHCPv4
}

// The purpose of this test is to verify that definition for option that
// comprises array of uint16 values can be created and that this definition
// can be used to create option with an array of uint16 values.
TEST_F(OptionDefinitionTest, uint16Array) {
    // Let's define some dummy option.
    const uint16_t opt_code = 79;
    OptionDefinition opt_def("OPTION_UINT16_ARRAY", opt_code, "my-space",
                             "uint16", true);

    OptionPtr option_v6;
    // Positive scenario, initiate the buffer with length being
    // multiple of uint16_t size.
    // buffer elements will be: 0x112233.
    OptionBuffer buf(6);
    for (unsigned i = 0; i < 6; ++i) {
        buf[i] = i / 2;
    }
    // Constructor should succeed because buffer has correct size.
    EXPECT_NO_THROW(
        option_v6 = opt_def.optionFactory(Option::V6, opt_code, buf);
    );
    const Option* optptr = option_v6.get();
    ASSERT_TRUE(optptr);
    ASSERT_TRUE(typeid(*optptr) == typeid(OptionIntArray<uint16_t>));
    boost::shared_ptr<OptionIntArray<uint16_t> > option_cast_v6 =
        boost::static_pointer_cast<OptionIntArray<uint16_t> >(option_v6);
    // Get the values from the initiated options and validate.
    std::vector<uint16_t> values = option_cast_v6->getValues();
    for (size_t i = 0; i < values.size(); ++i) {
        // Expected value is calculated using on the same pattern
        // as the one we used to initiate buffer:
        // for i=0, expected = 0x00, for i = 1, expected == 0x11 etc.
        uint16_t expected = (i << 8) | i;
        EXPECT_EQ(expected, values[i]);
    }

    // Provided buffer size must be greater than zero. Check if we
    // get exception if we provide zero-length buffer.
    EXPECT_THROW(
        option_v6 = opt_def.optionFactory(Option::V6, opt_code, OptionBuffer()),
        InvalidOptionValue
    );
    // Buffer length must be multiple of data type size.
    EXPECT_THROW(
        option_v6 = opt_def.optionFactory(Option::V6, opt_code, OptionBuffer(5)),
        InvalidOptionValue
    );
}

// The purpose of this test is to verify that definition for option that
// comprises array of uint16 values can be created and that this definition
// can be used to create option with an array of uint16 values.
TEST_F(OptionDefinitionTest, uint16ArrayTokenized) {
    // Let's define some dummy option.
    const uint16_t opt_code = 79;
    OptionDefinition opt_def("OPTION_UINT16_ARRAY", opt_code, "my-space",
                             "uint16", true);

    OptionPtr option_v6;
    std::vector<std::string> str_values;
    str_values.push_back("12345");
    str_values.push_back("5679");
    str_values.push_back("12");
    EXPECT_NO_THROW(
        option_v6 = opt_def.optionFactory(Option::V6, opt_code, str_values);
    );
    const Option* optptr = option_v6.get();
    ASSERT_TRUE(optptr);
    ASSERT_TRUE(typeid(*optptr) == typeid(OptionIntArray<uint16_t>));
    boost::shared_ptr<OptionIntArray<uint16_t> > option_cast_v6 =
        boost::static_pointer_cast<OptionIntArray<uint16_t> >(option_v6);
    // Get the values from the initiated options and validate.
    std::vector<uint16_t> values = option_cast_v6->getValues();
    EXPECT_EQ(12345, values[0]);
    EXPECT_EQ(5679, values[1]);
    EXPECT_EQ(12, values[2]);
}

// The purpose of this test is to verify that definition for option that
// comprises array of uint32 values can be created and that this definition
// can be used to create option with an array of uint32 values.
TEST_F(OptionDefinitionTest, uint32Array) {
    // Let's define some dummy option.
    const uint16_t opt_code = 80;

    OptionDefinition opt_def("OPTION_UINT32_ARRAY", opt_code, "my-space",
                             "uint32", true);

    OptionPtr option_v6;
    // Positive scenario, initiate the buffer with length being
    // multiple of uint16_t size.
    // buffer elements will be: 0x111122223333.
    OptionBuffer buf(12);
    for (size_t i = 0; i < buf.size(); ++i) {
        buf[i] = i / 4;
    }
    // Constructor should succeed because buffer has correct size.
    EXPECT_NO_THROW(
        option_v6 = opt_def.optionFactory(Option::V6, opt_code, buf);
    );
    const Option* optptr = option_v6.get();
    ASSERT_TRUE(optptr);
    ASSERT_TRUE(typeid(*optptr) == typeid(OptionIntArray<uint32_t>));
    boost::shared_ptr<OptionIntArray<uint32_t> > option_cast_v6 =
        boost::static_pointer_cast<OptionIntArray<uint32_t> >(option_v6);
    // Get the values from the initiated options and validate.
    std::vector<uint32_t> values = option_cast_v6->getValues();
    for (size_t i = 0; i < values.size(); ++i) {
        // Expected value is calculated using on the same pattern
        // as the one we used to initiate buffer:
        // for i=0, expected = 0x0000, for i = 1, expected == 0x1111 etc.
        uint32_t expected = 0x01010101 * i;
        EXPECT_EQ(expected, values[i]);
    }

    // Provided buffer size must be greater than zero. Check if we
    // get exception if we provide zero-length buffer.
    EXPECT_THROW(
        option_v6 = opt_def.optionFactory(Option::V6, opt_code, OptionBuffer()),
        InvalidOptionValue
    );
    // Buffer length must be multiple of data type size.
    EXPECT_THROW(
        option_v6 = opt_def.optionFactory(Option::V6, opt_code, OptionBuffer(5)),
        InvalidOptionValue
    );
}

// The purpose of this test is to verify that definition for option that
// comprises array of uint32 values can be created and that this definition
// can be used to create option with an array of uint32 values.
TEST_F(OptionDefinitionTest, uint32ArrayTokenized) {
    // Let's define some dummy option.
    const uint16_t opt_code = 80;

    OptionDefinition opt_def("OPTION_UINT32_ARRAY", opt_code, "my-space",
                             "uint32", true);

    OptionPtr option_v6;
    std::vector<std::string> str_values;
    str_values.push_back("123456");
    // Try with hexadecimal
    str_values.push_back("0x7");
    str_values.push_back("256");
    str_values.push_back("1111");

    EXPECT_NO_THROW(
        option_v6 = opt_def.optionFactory(Option::V6, opt_code, str_values);
    );
    const Option* optptr = option_v6.get();
    ASSERT_TRUE(optptr);
    ASSERT_TRUE(typeid(*optptr) == typeid(OptionIntArray<uint32_t>));
    boost::shared_ptr<OptionIntArray<uint32_t> > option_cast_v6 =
        boost::static_pointer_cast<OptionIntArray<uint32_t> >(option_v6);
    // Get the values from the initiated options and validate.
    std::vector<uint32_t> values = option_cast_v6->getValues();
    EXPECT_EQ(123456, values[0]);
    EXPECT_EQ(7, values[1]);
    EXPECT_EQ(256, values[2]);
    EXPECT_EQ(1111, values[3]);
}

// The purpose of this test is to verify that the definition can be created
// for the option that comprises string value in the UTF8 format.
TEST_F(OptionDefinitionTest, utf8StringTokenized) {
    // Let's create some dummy option.
    const uint16_t opt_code = 80;
    OptionDefinition opt_def("OPTION_WITH_STRING", opt_code, "my-space",
                             "string");

    std::vector<std::string> values;
    values.push_back("Hello World");
    values.push_back("this string should not be included in the option");
    OptionPtr option_v6;
    EXPECT_NO_THROW(
        option_v6 = opt_def.optionFactory(Option::V6, opt_code, values);
    );
    ASSERT_TRUE(option_v6);
    const Option* optptr = option_v6.get();
    ASSERT_TRUE(optptr);
    ASSERT_TRUE(typeid(*optptr) == typeid(OptionString));
    OptionStringPtr option_v6_string =
        boost::static_pointer_cast<OptionString>(option_v6);
    EXPECT_TRUE(values[0] == option_v6_string->getValue());
}

// The purpose of this test is to check that non-integer data type can't
// be used for factoryInteger function.
TEST_F(OptionDefinitionTest, integerInvalidType) {
    // The template function factoryInteger<> accepts integer values only
    // as template typename. Here we try passing different type and
    // see if it rejects it.
    OptionBuffer buf(1);
    EXPECT_THROW(
        OptionDefinition::factoryInteger<bool>(Option::V6, D6O_PREFERENCE, DHCP6_OPTION_SPACE,
                                               buf.begin(), buf.end()),
        isc::dhcp::InvalidDataType
    );
}

// This test verifies that a definition of an option with a single IPv6
// prefix can be created and used to create an instance of the option.
TEST_F(OptionDefinitionTest, prefix) {
    OptionDefinition opt_def("option-prefix", 1000, "my-space", "ipv6-prefix");

    // Create a buffer holding a prefix.
    OptionBuffer buf;
    buf.push_back(32);
    buf.push_back(0x30);
    buf.push_back(0x00);
    buf.resize(5);

    OptionPtr option_v6;

    // Create an instance of this option from the definition.
    ASSERT_NO_THROW(
        option_v6 = opt_def.optionFactory(Option::V6, 1000, buf);
    );

    // Make sure that the returned option class is correct.
    const Option* optptr = option_v6.get();
    ASSERT_TRUE(optptr);
    ASSERT_TRUE(typeid(*optptr) == typeid(OptionCustom));

    // Validate the value.
    OptionCustomPtr option_cast_v6 =
        boost::dynamic_pointer_cast<OptionCustom>(option_v6);
    ASSERT_EQ(1, option_cast_v6->getDataFieldsNum());
    PrefixTuple prefix = option_cast_v6->readPrefix();
    EXPECT_EQ(32, prefix.first.asUnsigned());
    EXPECT_EQ("3000::", prefix.second.toText());
}

// This test verifies that a definition of an option with a single IPv6
// prefix can be created and that the instance of this option can be
// created by specifying the prefix in the textual format.
TEST_F(OptionDefinitionTest, prefixTokenized) {
    OptionDefinition opt_def("option-prefix", 1000, "my-space", "ipv6-prefix");

    OptionPtr option_v6;
    // Specify a single prefix.
    std::vector<std::string> values(1, "2001:db8:1::/64");

    // Create an instance of the option using the definition.
    ASSERT_NO_THROW(
        option_v6 = opt_def.optionFactory(Option::V6, 1000, values);
    );

    // Make sure that the returned option class is correct.
    const Option* optptr = option_v6.get();
    ASSERT_TRUE(optptr);
    ASSERT_TRUE(typeid(*optptr) == typeid(OptionCustom));

    // Validate the value.
    OptionCustomPtr option_cast_v6 =
        boost::dynamic_pointer_cast<OptionCustom>(option_v6);
    ASSERT_EQ(1, option_cast_v6->getDataFieldsNum());
    PrefixTuple prefix = option_cast_v6->readPrefix();
    EXPECT_EQ(64, prefix.first.asUnsigned());
    EXPECT_EQ("2001:db8:1::", prefix.second.toText());
}

// This test verifies that a definition of an option with an array
// of IPv6 prefixes can be created and that the instance of this
// option can be created by specifying multiple prefixes in the
// textual format.
TEST_F(OptionDefinitionTest, prefixArrayTokenized) {
    OptionDefinition opt_def("option-prefix", 1000, "my-space",
                             "ipv6-prefix", true);

    OptionPtr option_v6;

    // Specify 3 prefixes
    std::vector<std::string> values;
    values.push_back("2001:db8:1:: /64");
    values.push_back("3000::/ 32");
    values.push_back("3001:1:: /  48");

    // Create an instance of an option using the definition.
    ASSERT_NO_THROW(
        option_v6 = opt_def.optionFactory(Option::V6, 1000, values);
    );

    // Make sure that the option class returned is correct.
    const Option* optptr = option_v6.get();
    ASSERT_TRUE(optptr);
    ASSERT_TRUE(typeid(*optptr) == typeid(OptionCustom));

    OptionCustomPtr option_cast_v6 =
        boost::dynamic_pointer_cast<OptionCustom>(option_v6);

    // There should be 3 prefixes in this option.
    ASSERT_EQ(3, option_cast_v6->getDataFieldsNum());

    ASSERT_NO_THROW({
        PrefixTuple prefix0 = option_cast_v6->readPrefix(0);
        EXPECT_EQ(64, prefix0.first.asUnsigned());
        EXPECT_EQ("2001:db8:1::", prefix0.second.toText());
    });

    ASSERT_NO_THROW({
        PrefixTuple prefix1 = option_cast_v6->readPrefix(1);
        EXPECT_EQ(32, prefix1.first.asUnsigned());
        EXPECT_EQ("3000::", prefix1.second.toText());
    });

    ASSERT_NO_THROW({
        PrefixTuple prefix2 = option_cast_v6->readPrefix(2);
        EXPECT_EQ(48, prefix2.first.asUnsigned());
        EXPECT_EQ("3001:1::", prefix2.second.toText());
    });
}

// This test verifies that a definition of an option with a single PSID
// value can be created and used to create an instance of the option.
TEST_F(OptionDefinitionTest, psid) {
    OptionDefinition opt_def("option-psid", 1000, "my-space", "psid");

    OptionPtr option_v6;

    // Create a buffer holding PSID.
    OptionBuffer buf;
    buf.push_back(6);
    buf.push_back(0x4);
    buf.push_back(0x0);

    // Create an instance of this option from the definition.
    ASSERT_NO_THROW(
        option_v6 = opt_def.optionFactory(Option::V6, 1000, buf);
    );

    // Make sure that the returned option class is correct.
    const Option* optptr = option_v6.get();
    ASSERT_TRUE(optptr);
    ASSERT_TRUE(typeid(*optptr) == typeid(OptionCustom));

    // Validate the value.
    OptionCustomPtr option_cast_v6 =
        boost::dynamic_pointer_cast<OptionCustom>(option_v6);
    ASSERT_EQ(1, option_cast_v6->getDataFieldsNum());
    PSIDTuple psid = option_cast_v6->readPsid();
    EXPECT_EQ(6, psid.first.asUnsigned());
    EXPECT_EQ(1, psid.second.asUint16());
}

// This test verifies that a definition of an option with a single PSID
// value can be created and that the instance of this option can be
// created by specifying PSID length and value in the textual format.
TEST_F(OptionDefinitionTest, psidTokenized) {
    OptionDefinition opt_def("option-psid", 1000, "my-space", "psid");

    OptionPtr option_v6;
    // Specify a single PSID with a length of 6 and value of 3.
    std::vector<std::string> values(1, "3 / 6");

    // Create an instance of the option using the definition.
    ASSERT_NO_THROW(
        option_v6 = opt_def.optionFactory(Option::V6, 1000, values);
    );

    // Make sure that the returned option class is correct.
    const Option* optptr = option_v6.get();
    ASSERT_TRUE(optptr);
    ASSERT_TRUE(typeid(*optptr) == typeid(OptionCustom));

    // Validate the value.
    OptionCustomPtr option_cast_v6 =
        boost::dynamic_pointer_cast<OptionCustom>(option_v6);
    ASSERT_EQ(1, option_cast_v6->getDataFieldsNum());
    PSIDTuple psid = option_cast_v6->readPsid();
    EXPECT_EQ(6, psid.first.asUnsigned());
    EXPECT_EQ(3, psid.second.asUint16());
}

// This test verifies that a definition of an option with an array
// of PSIDs can be created and that the instance of this option can be
// created by specifying multiple PSIDs in the textual format.
TEST_F(OptionDefinitionTest, psidArrayTokenized) {
    OptionDefinition opt_def("option-psid", 1000, "my-space", "psid", true);

    OptionPtr option_v6;

    // Specify 3 PSIDs.
    std::vector<std::string> values;
    values.push_back("3 / 6");
    values.push_back("0/1");
    values.push_back("7     /   3");

    // Create an instance of an option using the definition.
    ASSERT_NO_THROW(
        option_v6 = opt_def.optionFactory(Option::V6, 1000, values);
    );

    // Make sure that the option class returned is correct.
    const Option* optptr = option_v6.get();
    ASSERT_TRUE(optptr);
    ASSERT_TRUE(typeid(*optptr) == typeid(OptionCustom));

    OptionCustomPtr option_cast_v6 =
        boost::dynamic_pointer_cast<OptionCustom>(option_v6);

    // There should be 3 PSIDs in this option.
    ASSERT_EQ(3, option_cast_v6->getDataFieldsNum());

    // Check their values.
    PSIDTuple psid0;
    PSIDTuple psid1;
    PSIDTuple psid2;

    psid0 = option_cast_v6->readPsid(0);
    EXPECT_EQ(6, psid0.first.asUnsigned());
    EXPECT_EQ(3, psid0.second.asUint16());

    psid1 = option_cast_v6->readPsid(1);
    EXPECT_EQ(1, psid1.first.asUnsigned());
    EXPECT_EQ(0, psid1.second.asUint16());

    psid2 = option_cast_v6->readPsid(2);
    EXPECT_EQ(3, psid2.first.asUnsigned());
    EXPECT_EQ(7, psid2.second.asUint16());
}

// This test verifies that a definition of an option with a single DHCPv4
// tuple can be created and used to create an instance of the option.
TEST_F(OptionDefinitionTest, tuple4) {
    OptionDefinition opt_def("option-tuple", 232, "my-space", "tuple");

    OptionPtr option;

    // Create a buffer holding tuple
    const char data[] = {
        6, 102, 111, 111, 98, 97, 114 // "foobar"
    };
    OptionBuffer buf(data, data + sizeof(data));

    // Create an instance of this option from the definition.
    ASSERT_NO_THROW(
        option = opt_def.optionFactory(Option::V4, 232, buf);
    );

    // Make sure that the returned option class is correct.
    const Option* optptr = option.get();
    ASSERT_TRUE(optptr);
    ASSERT_TRUE(typeid(*optptr) == typeid(OptionCustom));

    // Validate the value.
    OptionCustomPtr option_cast =
        boost::dynamic_pointer_cast<OptionCustom>(option);
    ASSERT_EQ(1, option_cast->getDataFieldsNum());
    OpaqueDataTuple tuple(OpaqueDataTuple::LENGTH_1_BYTE);
    ASSERT_NO_THROW(option_cast->readTuple(tuple));
    EXPECT_EQ("foobar", tuple.getText());
}

// This test verifies that a definition of an option with a single DHCPv6
// tuple can be created and used to create an instance of the option.
TEST_F(OptionDefinitionTest, tuple6) {
    OptionDefinition opt_def("option-tuple", 1000, "my-space", "tuple");

    OptionPtr option;

    // Create a buffer holding tuple
    const char data[] = {
        0, 6, 102, 111, 111, 98, 97, 114 // "foobar"
    };
    OptionBuffer buf(data, data + sizeof(data));

    // Create an instance of this option from the definition.
    ASSERT_NO_THROW(
        option = opt_def.optionFactory(Option::V6, 1000, buf);
    );

    // Make sure that the returned option class is correct.
    const Option* optptr = option.get();
    ASSERT_TRUE(optptr);
    ASSERT_TRUE(typeid(*optptr) == typeid(OptionCustom));

    // Validate the value.
    OptionCustomPtr option_cast =
        boost::dynamic_pointer_cast<OptionCustom>(option);
    ASSERT_EQ(1, option_cast->getDataFieldsNum());
    OpaqueDataTuple tuple(OpaqueDataTuple::LENGTH_2_BYTES);
    ASSERT_NO_THROW(option_cast->readTuple(tuple));
    EXPECT_EQ("foobar", tuple.getText());
}

// This test verifies that a definition of an option with a single DHCPv4
// tuple can be created and that the instance of this option can be
// created by specifying tuple value in the textual format.
TEST_F(OptionDefinitionTest, tuple4Tokenized) {
    OptionDefinition opt_def("option-tuple", 232, "my-space", "tuple");

    OptionPtr option;
    // Specify a single tuple with "foobar" content.
    std::vector<std::string> values(1, "foobar");

    // Create an instance of this option using the definition.
    ASSERT_NO_THROW(
        option = opt_def.optionFactory(Option::V4, 232, values);
    );

    // Make sure that the returned option class is correct.
    const Option* optptr = option.get();
    ASSERT_TRUE(optptr);
    ASSERT_TRUE(typeid(*optptr) == typeid(OptionCustom));

    // Validate the value.
    OptionCustomPtr option_cast =
        boost::dynamic_pointer_cast<OptionCustom>(option);
    ASSERT_EQ(1, option_cast->getDataFieldsNum());
    OpaqueDataTuple tuple(OpaqueDataTuple::LENGTH_1_BYTE);
    ASSERT_NO_THROW(option_cast->readTuple(tuple));
    EXPECT_EQ("foobar", tuple.getText());
}

// This test verifies that a definition of an option with a single DHCPv6
// tuple can be created and that the instance of this option can be
// created by specifying tuple value in the textual format.
TEST_F(OptionDefinitionTest, tuple6Tokenized) {
    OptionDefinition opt_def("option-tuple", 1000, "my-space", "tuple");

    OptionPtr option;
    // Specify a single tuple with "foobar" content.
    std::vector<std::string> values(1, "foobar");

    // Create an instance of this option using the definition.
    ASSERT_NO_THROW(
        option = opt_def.optionFactory(Option::V6, 1000, values);
    );

    // Make sure that the returned option class is correct.
    const Option* optptr = option.get();
    ASSERT_TRUE(optptr);
    ASSERT_TRUE(typeid(*optptr) == typeid(OptionCustom));

    // Validate the value.
    OptionCustomPtr option_cast =
        boost::dynamic_pointer_cast<OptionCustom>(option);
    ASSERT_EQ(1, option_cast->getDataFieldsNum());
    OpaqueDataTuple tuple(OpaqueDataTuple::LENGTH_2_BYTES);
    ASSERT_NO_THROW(option_cast->readTuple(tuple));
    EXPECT_EQ("foobar", tuple.getText());
}

// This test verifies that a definition of an option with an array
// of DHCPv4 tuples can be created and that the instance of this option
// can be created by specifying multiple DHCPv4 tuples in the textual format.
TEST_F(OptionDefinitionTest, tuple4ArrayTokenized) {
    OptionDefinition opt_def("option-tuple", 232, "my-space", "tuple", true);

    OptionPtr option;

    // Specify 3 tuples.
    std::vector<std::string> values;
    values.push_back("hello");
    values.push_back("the");
    values.push_back("world");

    // Create an instance of this option using the definition.
    ASSERT_NO_THROW(
        option = opt_def.optionFactory(Option::V4, 232, values);
    );

    // Make sure that the returned option class is correct.
    const Option* optptr = option.get();
    ASSERT_TRUE(optptr);
    ASSERT_TRUE(typeid(*optptr) == typeid(OptionOpaqueDataTuples));

    // Validate the value.
    OptionOpaqueDataTuplesPtr option_cast =
        boost::dynamic_pointer_cast<OptionOpaqueDataTuples>(option);

    // There should be 3 tuples in this option.
    ASSERT_EQ(3, option_cast->getTuplesNum());

    // Check their values.
    OpaqueDataTuple tuple0 = option_cast->getTuple(0);
    EXPECT_EQ("hello", tuple0.getText());

    OpaqueDataTuple tuple1 = option_cast->getTuple(1);
    EXPECT_EQ("the", tuple1.getText());

    OpaqueDataTuple tuple2 = option_cast->getTuple(2);
    EXPECT_EQ("world", tuple2.getText());
}

// This test verifies that a definition of an option with an array
// of DHCPv4 tuples can be created and that the instance of this option
// can be created by specifying multiple DHCPv4 tuples in the textual format.
// This test also verifies specific v4 Option #143 where tuple's string length
// is coded on 2 octets instead of 1 as usual.
TEST_F(OptionDefinitionTest, tuple4ArrayOption143) {
    OptionDefinition opt_def("option-tuple", DHO_V4_SZTP_REDIRECT, DHCP4_OPTION_SPACE, "tuple", true);

    OptionPtr option;

    // Specify 3 tuples.
    std::vector<std::string> values;
    values.push_back("hello");
    values.push_back("the");
    values.push_back("world");

    // Create an instance of this option using the definition.
    ASSERT_NO_THROW(
        option = opt_def.optionFactory(Option::V4, DHO_V4_SZTP_REDIRECT, values);
    );

    // Make sure that the returned option class is correct.
    const Option* optptr = option.get();
    ASSERT_TRUE(optptr);
    ASSERT_TRUE(typeid(*optptr) == typeid(OptionOpaqueDataTuples));

    // Validate the value.
    OptionOpaqueDataTuplesPtr option_cast =
        boost::dynamic_pointer_cast<OptionOpaqueDataTuples>(option);

    // There should be 3 tuples in this option.
    ASSERT_EQ(3, option_cast->getTuplesNum());

    // Check their values.
    OpaqueDataTuple tuple0 = option_cast->getTuple(0);
    EXPECT_EQ("hello", tuple0.getText());

    OpaqueDataTuple tuple1 = option_cast->getTuple(1);
    EXPECT_EQ("the", tuple1.getText());

    OpaqueDataTuple tuple2 = option_cast->getTuple(2);
    EXPECT_EQ("world", tuple2.getText());
}

// This test verifies that a definition of an option with an array
// of DHCPv6 tuples can be created and that the instance of this option
// can be created by specifying multiple DHCPv6 tuples in the textual format.
TEST_F(OptionDefinitionTest, tuple6ArrayTokenized) {
    OptionDefinition opt_def("option-tuple", 1000, "my-space", "tuple", true);

    OptionPtr option;

    // Specify 3 tuples.
    std::vector<std::string> values;
    values.push_back("hello");
    values.push_back("the");
    values.push_back("world");

    // Create an instance of this option using the definition.
    ASSERT_NO_THROW(
        option = opt_def.optionFactory(Option::V6, 1000, values);
    );

    // Make sure that the returned option class is correct.
    const Option* optptr = option.get();
    ASSERT_TRUE(optptr);
    ASSERT_TRUE(typeid(*optptr) == typeid(OptionOpaqueDataTuples));

    // Validate the value.
    OptionOpaqueDataTuplesPtr option_cast =
        boost::dynamic_pointer_cast<OptionOpaqueDataTuples>(option);

    // There should be 3 tuples in this option.
    ASSERT_EQ(3, option_cast->getTuplesNum());

    // Check their values.
    OpaqueDataTuple tuple0 = option_cast->getTuple(0);
    EXPECT_EQ("hello", tuple0.getText());

    OpaqueDataTuple tuple1 = option_cast->getTuple(1);
    EXPECT_EQ("the", tuple1.getText());

    OpaqueDataTuple tuple2 = option_cast->getTuple(2);
    EXPECT_EQ("world", tuple2.getText());
}

} // anonymous namespace
