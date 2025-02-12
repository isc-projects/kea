// Copyright (C) 2023-2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <host_data_parser.h>
#include <cc/data.h>
#include <dhcp/dhcp4.h>
#include <dhcp/std_option_defs.h>
#include <gtest/gtest.h>

using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::host_cmds;

namespace {

// This test verifies that a host holding an option with suboption
// can be parsed but the returned options are not encapsulated.
TEST(HostDataParserTest, parseWithoutEncapsulation) {
    HostDataParser4 parser;

    auto host_data = Element::fromJSON("{"
        "\"subnet-id\": 1,"
        "\"hw-address\": \"01:02:03:04:05:06\","
        "\"ip-address\": \"192.0.2.1\","
        "\"option-data\": ["
            "{"
                 "\"name\": \"vendor-encapsulated-options\""
            "},"
            "{"
                 "\"name\": \"foo\","
                 "\"code\": 1,"
                 "\"space\": \"vendor-encapsulated-options-space\""
            "}"
        "]"
    "}");
    auto host = parser.parseWithSubnet(host_data);
    ASSERT_TRUE(host);

    auto option43 = host->getCfgOption4()->get(DHCP4_OPTION_SPACE,
                                               DHO_VENDOR_ENCAPSULATED_OPTIONS);

    ASSERT_TRUE(option43.option_);

    // Ensure that the option 43 is not encapsulated with its sub option.
    EXPECT_FALSE(option43.option_->getOption(1));

    // However, the option 1 should exist in the container.
    auto option1 = host->getCfgOption4()->get(VENDOR_ENCAPSULATED_OPTION_SPACE, 1);
    EXPECT_TRUE(option1.option_);
}

} // namespace
