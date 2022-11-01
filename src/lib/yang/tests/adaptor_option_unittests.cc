// Copyright (C) 2018-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <gtest/gtest.h>

#include <dhcp/dhcp4.h>
#include <dhcp/dhcp6.h>
#include <dhcp/option_data_types.h>
#include <dhcp/option_space.h>
#include <testutils/gtest_utils.h>
#include <yang/adaptor_option.h>
#include <yang/netconf_error.h>

using namespace std;
using namespace isc;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::yang;

namespace {

// Verifies that setSpace adds a space to an option without this entry.
TEST(AdaptorOptionTest, setSpaceNoSpace) {
    string config = "{\n"
        "}";
    ElementPtr json;
    ASSERT_NO_THROW_LOG(json = Element::fromJSON(config));
    ConstElementPtr copied = copy(json);
    EXPECT_NO_THROW_LOG(AdaptorOption::setSpace(json, "foo"));
    EXPECT_FALSE(copied->equals(*json));
    ConstElementPtr space = json->get("space");
    ASSERT_TRUE(space);
    ASSERT_EQ(Element::string, space->getType());
    EXPECT_EQ("foo", space->stringValue());
}

// Verifies that setSpace does not change to an option with space.
TEST(AdaptorOptionTest, setSpace) {
    string config = "{\n"
        " \"space\": \"dhcp4\"\n"
        "}";
    ElementPtr json;
    ASSERT_NO_THROW_LOG(json = Element::fromJSON(config));
    ConstElementPtr copied = copy(json);
    EXPECT_NO_THROW_LOG(AdaptorOption::setSpace(json, "foo"));
    EXPECT_TRUE(copied->equals(*json));
}

// Verifies that checkType accepts an option with type.
TEST(AdaptorOptionTest, checkType) {
    string config = "{\n"
        " \"type\": \"string\"\n"
        "}";
    ConstElementPtr json;
    ASSERT_NO_THROW_LOG(json = Element::fromJSON(config));
    EXPECT_NO_THROW_LOG(AdaptorOption::checkType(json));
}

// Verifies that checkType does not accept an option without type.
TEST(AdaptorOptionTest, checkTypeNoType) {
    string config = "{\n"
        "}";
    ConstElementPtr json;
    ASSERT_NO_THROW_LOG(json = Element::fromJSON(config));
    EXPECT_THROW_MSG(AdaptorOption::checkType(json), MissingKey,
                     "missing type in option definition {  }");
}

// Verifies that checkCode accepts an option with code.
TEST(AdaptorOptionTest, checkCode) {
    string config = "{\n"
        " \"code\": 123\n"
        "}";
    ConstElementPtr json;
    ASSERT_NO_THROW_LOG(json = Element::fromJSON(config));
    EXPECT_NO_THROW_LOG(AdaptorOption::checkCode(json));
}

// Verifies that checkCode does not accept an option without code.
TEST(AdaptorOptionTest, checkCodeNoCode) {
    string config = "{\n"
        "}";
    ConstElementPtr json;
    ASSERT_NO_THROW_LOG(json = Element::fromJSON(config));
    EXPECT_THROW_MSG(AdaptorOption::checkCode(json), MissingKey, "missing code in option {  }");
}

// Verifies that collect works as expected.
TEST(AdaptorOptionTest, collect) {
    string config = "{\n"
        " \"code\": 123,\n"
        " \"name\": \"foo\",\n"
        " \"space\": \"bar\"\n"
        "}";
    ConstElementPtr json;
    ASSERT_NO_THROW_LOG(json = Element::fromJSON(config));
    OptionCodes codes;
    ASSERT_NO_THROW_LOG(AdaptorOption::collect(json, codes));
    EXPECT_EQ(1, codes.size());
    EXPECT_EQ(123, codes["bar@foo"]);
    EXPECT_FALSE(codes.contains("foo@bar"));
}

// Verifies that collect skips an already known option definition.
TEST(AdaptorOptionTest, collectKnown) {
    string config = "{\n"
        " \"code\": 123,\n"
        " \"name\": \"foo\",\n"
        " \"space\": \"bar\"\n"
        "}";
    ConstElementPtr json;
    ASSERT_NO_THROW_LOG(json = Element::fromJSON(config));
    OptionCodes codes = { { "bar@foo", 111 } };
    ASSERT_NO_THROW_LOG(AdaptorOption::collect(json, codes));
    EXPECT_EQ(1, codes.size());
    EXPECT_EQ(111, codes["bar@foo"]);
}

// Verifies that setCode adds a code to an option without this entry
// when the code is available in the map.
TEST(AdaptorOptionTest, setCodeNoCode) {
    string config = "{\n"
        " \"name\": \"foo\",\n"
        " \"space\": \"bar\"\n"
        "}";
    ElementPtr json;
    ASSERT_NO_THROW_LOG(json = Element::fromJSON(config));
    ConstElementPtr copied = copy(json);
    OptionCodes codes = { { "bar@foo", 123 } };
    EXPECT_NO_THROW_LOG(AdaptorOption::setCode(json, codes));
    EXPECT_FALSE(copied->equals(*json));
    ConstElementPtr code = json->get("code");
    ASSERT_TRUE(code);
    ASSERT_EQ(Element::integer, code->getType());
    EXPECT_EQ(123, code->intValue());
}

// Verifies that setCode does not change to an option with code.
TEST(AdaptorOptionTest, setCode) {
    string config = "{\n"
        " \"code\": \"dhcp4\"\n"
        "}";
    ElementPtr json;
    ASSERT_NO_THROW_LOG(json = Element::fromJSON(config));
    ConstElementPtr copied = copy(json);
    OptionCodes codes;
    EXPECT_NO_THROW_LOG(AdaptorOption::setCode(json, codes));
    EXPECT_TRUE(copied->equals(*json));
}

// Verifies that setCode raises an error on option without name and code.
TEST(AdaptorOptionTest, setCodeNoName) {
    string config = "{\n"
        " \"space\": \"bar\"\n"
        "}";
    ElementPtr json;
    ASSERT_NO_THROW_LOG(json = Element::fromJSON(config));
    OptionCodes codes;
    EXPECT_THROW_MSG(AdaptorOption::setCode(json, codes), MissingKey,
                     "missing name and code in option { \"space\": \"bar\" }");
}

// Note the code assumes there is a space, i.e. setSpace was called.

// Verifies that setCode raises an error on option without code but
// the code is not available in the map.
TEST(AdaptorOptionTest, setCodeNotInMap) {
    string config = "{\n"
        " \"name\": \"foo\",\n"
        " \"space\": \"bar\"\n"
        "}";
    ElementPtr json;
    ASSERT_NO_THROW_LOG(json = Element::fromJSON(config));
    OptionCodes codes;
    EXPECT_THROW_MSG(AdaptorOption::setCode(json, codes), MissingKey,
                     "can't get code from option { \"name\": \"foo\", \"space\": \"bar\" }");
}

/// @brief Test class to make initCodes public.
class TestAdaptorOption : public AdaptorOption {
public:
    using AdaptorOption::initCodesInternal;
};  // TestAdaptorOption

// Verifies that initCodesInternal works as expected.
TEST(AdaptorOptionTest, initCodesInternal) {
    const OptionDefParams DEFS[] = {
        { "subnet-mask", DHO_SUBNET_MASK, DHCP4_OPTION_SPACE,
          OPT_IPV4_ADDRESS_TYPE, false, 0, 0, "" },
        { "time-offset", DHO_TIME_OFFSET, DHCP4_OPTION_SPACE, OPT_INT32_TYPE,
          false, 0, 0, "" }
    };
    const size_t DEFS_SIZE = sizeof(DEFS) / sizeof(DEFS[0]);
    OptionCodes codes;
    ASSERT_NO_THROW_LOG(TestAdaptorOption::initCodesInternal(codes,
                                                         DHCP4_OPTION_SPACE,
                                                         DEFS,
                                                         DEFS_SIZE));
    ASSERT_EQ(2, codes.size());
    EXPECT_EQ(DHO_SUBNET_MASK, codes["dhcp4@subnet-mask"]);
    EXPECT_EQ(DHO_TIME_OFFSET, codes["dhcp4@time-offset"]);
}

// Verifies that initCodes works as expected with DHCPv4.
TEST(AdaptorOptionTest, initCodes4) {
    OptionCodes codes;
    ASSERT_NO_THROW_LOG(AdaptorOption::initCodes(codes, DHCP4_OPTION_SPACE));
    EXPECT_EQ(DHO_SUBNET_MASK, codes["dhcp4@subnet-mask"]);
    EXPECT_EQ(DHO_TIME_OFFSET, codes["dhcp4@time-offset"]);
    EXPECT_FALSE(codes.contains("dhcp6@clientid"));

    // initCodes loads last resort too.
    EXPECT_EQ(DHO_VENDOR_ENCAPSULATED_OPTIONS,
              codes["dhcp4@vendor-encapsulated-options"]);

    // and DOCSIS3.
    EXPECT_EQ(2, codes["vendor-4491@tftp-servers"]);
}

// Verifies that initCodes works as expected with DHCPv6.
TEST(AdaptorOptionTest, initCodes6) {
    OptionCodes codes;
    ASSERT_NO_THROW_LOG(AdaptorOption::initCodes(codes, DHCP6_OPTION_SPACE));
    EXPECT_EQ(D6O_CLIENTID, codes["dhcp6@clientid"]);
    EXPECT_EQ(D6O_SERVERID, codes["dhcp6@serverid"]);
    EXPECT_FALSE(codes.contains("dhcp4@subnet-mask"));

    // initCodes loads DOCSIS3 too.
    EXPECT_EQ(32, codes["vendor-4491@tftp-servers"]);

    // Various MAP suboptions.
    EXPECT_EQ(D6O_S46_BR, codes["s46-cont-mape-options@s46-br"]);
    EXPECT_EQ(D6O_S46_V4V6BIND, codes["s46-cont-lw-options@s46-v4v6bind"]);
    EXPECT_EQ(D6O_S46_PORTPARAMS, codes["s46-v4v6bind-options@s46-portparams"]);

    // And ISC space.
    EXPECT_EQ(ISC_V6_4O6_INTERFACE, codes["vendor-2495@4o6-interface"]);
}

}  //anonymous namespace
