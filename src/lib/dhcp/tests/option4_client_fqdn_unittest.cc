// Copyright (C) 2013-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <dhcp/option4_client_fqdn.h>
#include <dns/name.h>
#include <util/buffer.h>
#include <boost/scoped_ptr.hpp>
#include <gtest/gtest.h>

namespace {

using namespace isc;
using namespace isc::dhcp;

// This test verifies that constructor accepts empty partial domain-name but
// does not accept empty fully qualified domain name.
TEST(Option4ClientFqdnTest, constructEmptyName) {
    // Create an instance of the source option.
    boost::scoped_ptr<Option4ClientFqdn> option;
    ASSERT_NO_THROW(
        option.reset(new Option4ClientFqdn(Option4ClientFqdn::FLAG_S |
                                           Option4ClientFqdn::FLAG_E,
                                           Option4ClientFqdn::RCODE_SERVER(),
                                           "",
                                           Option4ClientFqdn::PARTIAL))
    );
    ASSERT_TRUE(option);
    EXPECT_FALSE(option->getFlag(Option4ClientFqdn::FLAG_O));
    EXPECT_FALSE(option->getFlag(Option4ClientFqdn::FLAG_N));
    EXPECT_TRUE(option->getFlag(Option4ClientFqdn::FLAG_S));
    EXPECT_TRUE(option->getFlag(Option4ClientFqdn::FLAG_E));
    EXPECT_TRUE(option->getDomainName().empty());
    EXPECT_EQ(Option4ClientFqdn::PARTIAL, option->getDomainNameType());

    // Constructor should not accept empty fully qualified domain name.
    EXPECT_THROW(Option4ClientFqdn(Option4ClientFqdn::FLAG_S |
                                   Option4ClientFqdn::FLAG_E,
                                   Option4ClientFqdn::RCODE_CLIENT(),
                                   "",
                                   Option4ClientFqdn::FULL),
                 InvalidOption4FqdnDomainName);
    // This check is similar to previous one, but using domain-name comprising
    // a single space character. This should be treated as empty domain-name.
    EXPECT_THROW(Option4ClientFqdn(Option4ClientFqdn::FLAG_S |
                                   Option4ClientFqdn::FLAG_E,
                                   Option4ClientFqdn::RCODE_CLIENT(),
                                   " ",
                                   Option4ClientFqdn::FULL),
                 InvalidOption4FqdnDomainName);

    // Try different constructor.
    ASSERT_NO_THROW(
        option.reset(new Option4ClientFqdn(Option4ClientFqdn::FLAG_O |
                                           Option4ClientFqdn::FLAG_E,
                                           Option4ClientFqdn::RCODE_SERVER()))
    );
    ASSERT_TRUE(option);
    EXPECT_TRUE(option->getFlag(Option4ClientFqdn::FLAG_O));
    EXPECT_TRUE(option->getFlag(Option4ClientFqdn::FLAG_E));
    EXPECT_FALSE(option->getFlag(Option4ClientFqdn::FLAG_N));
    EXPECT_FALSE(option->getFlag(Option4ClientFqdn::FLAG_S));
    EXPECT_TRUE(option->getDomainName().empty());
    EXPECT_EQ(Option4ClientFqdn::PARTIAL, option->getDomainNameType());
}

// This test verifies that copy constructor makes a copy of the option and
// the source option instance can be deleted (both instances don't share
// any resources).
TEST(Option4ClientFqdnTest, copyConstruct) {
    // Create an instance of the source option.
    boost::scoped_ptr<Option4ClientFqdn> option;
    ASSERT_NO_THROW(
        option.reset(new Option4ClientFqdn(Option4ClientFqdn::FLAG_S |
                                           Option4ClientFqdn::FLAG_E,
                                           Option4ClientFqdn::RCODE_SERVER(),
                                           "myhost.example.com",
                                           Option4ClientFqdn::FULL))
    );
    ASSERT_TRUE(option);

    // Use copy constructor to create a second instance of the option.
    boost::scoped_ptr<Option4ClientFqdn> option_copy;
    ASSERT_NO_THROW(
        option_copy.reset(new Option4ClientFqdn(*option))
    );
    ASSERT_TRUE(option_copy);

    // Copy construction should result in no shared resources between
    // two objects. In particular, pointer to implementation should not
    // be shared. Thus, we can release the source object now.
    option.reset();

    // Verify that all parameters have been copied to the target object.
    EXPECT_TRUE(option_copy->getFlag(Option4ClientFqdn::FLAG_S));
    EXPECT_TRUE(option_copy->getFlag(Option4ClientFqdn::FLAG_E));
    EXPECT_FALSE(option_copy->getFlag(Option4ClientFqdn::FLAG_O));
    EXPECT_FALSE(option_copy->getFlag(Option4ClientFqdn::FLAG_N));
    EXPECT_EQ("myhost.example.com.", option_copy->getDomainName());
    EXPECT_EQ(Option4ClientFqdn::FULL, option_copy->getDomainNameType());

    // Do another test with different parameters to verify that parameters
    // change when copied object is changed.

    // Create an option with different parameters.
    ASSERT_NO_THROW(
        option.reset(new Option4ClientFqdn(Option4ClientFqdn::FLAG_O |
                                           Option4ClientFqdn::FLAG_E,
                                           Option4ClientFqdn::RCODE_SERVER(),
                                           "example",
                                           Option4ClientFqdn::PARTIAL))
    );
    ASSERT_TRUE(option);

    // Call copy-constructor to copy the option.
    ASSERT_NO_THROW(
        option_copy.reset(new Option4ClientFqdn(*option))
    );
    ASSERT_TRUE(option_copy);

    option.reset();

    EXPECT_FALSE(option_copy->getFlag(Option4ClientFqdn::FLAG_S));
    EXPECT_TRUE(option_copy->getFlag(Option4ClientFqdn::FLAG_E));
    EXPECT_TRUE(option_copy->getFlag(Option4ClientFqdn::FLAG_O));
    EXPECT_FALSE(option_copy->getFlag(Option4ClientFqdn::FLAG_N));
    EXPECT_EQ("example", option_copy->getDomainName());
    EXPECT_EQ(Option4ClientFqdn::PARTIAL, option_copy->getDomainNameType());
}

// This test verifies that the option in the on-wire format with the domain-name
// encoded in the canonical format is parsed correctly.
TEST(Option4ClientFqdnTest, constructFromWire) {
    // The E flag sets the domain-name format to canonical.
    const uint8_t in_data[] = {
        Option4ClientFqdn::FLAG_S | Option4ClientFqdn::FLAG_E, // flags
        0,                                                     // RCODE1
        0,                                                     // RCODE2
        6, 109, 121, 104, 111, 115, 116,                       // myhost.
        7, 101, 120, 97, 109, 112, 108, 101,                   // example.
        3, 99, 111, 109, 0                                     // com.
    };
    size_t in_data_size = sizeof(in_data) / sizeof(in_data[0]);
    OptionBuffer in_buf(in_data, in_data + in_data_size);

    // Create option instance. Check that constructor doesn't throw.
    boost::scoped_ptr<Option4ClientFqdn> option;
    ASSERT_NO_THROW(
        option.reset(new Option4ClientFqdn(in_buf.begin(), in_buf.end()))
    );
    ASSERT_TRUE(option);

    EXPECT_TRUE(option->getFlag(Option4ClientFqdn::FLAG_S));
    EXPECT_TRUE(option->getFlag(Option4ClientFqdn::FLAG_E));
    EXPECT_FALSE(option->getFlag(Option4ClientFqdn::FLAG_O));
    EXPECT_FALSE(option->getFlag(Option4ClientFqdn::FLAG_N));
    EXPECT_EQ("myhost.example.com.", option->getDomainName());
    EXPECT_EQ(Option4ClientFqdn::FULL, option->getDomainNameType());
}

// This test verifies that the option in the on-wire format with the domain-name
// encoded in the ASCII format is parsed correctly.
TEST(Option4ClientFqdnTest, constructFromWireASCII) {
    // The E flag is set to zero which indicates that the domain name
    // is encoded in the ASCII format. The "dot" character at the end
    // indicates that the domain-name is fully qualified.
    const uint8_t in_data[] = {
        Option4ClientFqdn::FLAG_S,            // flags
        0,                                    // RCODE1
        0,                                    // RCODE2
        109, 121, 104, 111, 115, 116, 46,     // myhost.
        101, 120, 97, 109, 112, 108, 101, 46, // example.
        99, 111, 109, 46                      // com.
    };
    size_t in_data_size = sizeof(in_data) / sizeof(in_data[0]);
    OptionBuffer in_buf(in_data, in_data + in_data_size);

    // Create option instance. Check that constructor doesn't throw.
    boost::scoped_ptr<Option4ClientFqdn> option;
    ASSERT_NO_THROW(
        option.reset(new Option4ClientFqdn(in_buf.begin(), in_buf.end()))
    );
    ASSERT_TRUE(option);

    EXPECT_TRUE(option->getFlag(Option4ClientFqdn::FLAG_S));
    EXPECT_FALSE(option->getFlag(Option4ClientFqdn::FLAG_E));
    EXPECT_FALSE(option->getFlag(Option4ClientFqdn::FLAG_O));
    EXPECT_FALSE(option->getFlag(Option4ClientFqdn::FLAG_N));
    EXPECT_EQ("myhost.example.com.", option->getDomainName());
    EXPECT_EQ(Option4ClientFqdn::FULL, option->getDomainNameType());
}

// This test verifies that truncated option is rejected.
TEST(Option4ClientFqdnTest, constructFromWireTruncated) {
    // Empty buffer is invalid. It should be at least one octet long.
    OptionBuffer in_buf;
    for (uint8_t i = 0; i < 3; ++i) {
        EXPECT_THROW(Option4ClientFqdn(in_buf.begin(), in_buf.end()),
                     OutOfRange) << "Test of the truncated buffer failed for"
                                 << " buffer length " << static_cast<int>(i);
        in_buf.push_back(0);
    }

    // Buffer is now 3 bytes long, so it should not fail now.
    EXPECT_NO_THROW(Option4ClientFqdn(in_buf.begin(), in_buf.end()));
}

// This test verifies that exception is thrown when invalid domain-name
// in canonical format is carried in the option.
TEST(Option4ClientFqdnTest, constructFromWireInvalidName) {
    const uint8_t in_data[] = {
        Option4ClientFqdn::FLAG_S | Option4ClientFqdn::FLAG_E, // flags
        0,                                                     // RCODE1
        0,                                                     // RCODE2
        6, 109, 121, 104, 111, 115, 116,                       // myhost.
        7, 101, 120, 97, 109, 112, 108, 101,                   // example.
        5, 99, 111, 109, 0                 // com. (invalid label length 5)
    };
    size_t in_data_size = sizeof(in_data) / sizeof(in_data[0]);
    OptionBuffer in_buf(in_data, in_data + in_data_size);

    EXPECT_THROW(Option4ClientFqdn(in_buf.begin(), in_buf.end()),
                 InvalidOption4FqdnDomainName);
}

// This test verifies that exception is thrown when invalid domain-name
// in ASCII format is carried in the option.
TEST(Option4ClientFqdnTest, constructFromWireInvalidASCIIName) {
    const uint8_t in_data[] = {
        Option4ClientFqdn::FLAG_S,            // flags
        0,                                    // RCODE1
        0,                                    // RCODE2
        109, 121, 104, 111, 115, 116, 46, 46, // myhost.. (double dot!)
        101, 120, 97, 109, 112, 108, 101, 46, // example.
        99, 111, 109, 46                      // com.
    };
    size_t in_data_size = sizeof(in_data) / sizeof(in_data[0]);
    OptionBuffer in_buf(in_data, in_data + in_data_size);

    EXPECT_THROW(Option4ClientFqdn(in_buf.begin(), in_buf.end()),
                 InvalidOption4FqdnDomainName);
}

// This test verifies that the option in the on-wire format with partial
// domain-name encoded in canonical format is parsed correctly.
TEST(Option4ClientFqdnTest, constructFromWirePartial) {
    const uint8_t in_data[] = {
        Option4ClientFqdn::FLAG_N | Option4ClientFqdn:: FLAG_E,  // flags
        255,                                                     // RCODE1
        255,                                                     // RCODE2
        6, 109, 121, 104, 111, 115, 116                          // myhost
    };
    size_t in_data_size = sizeof(in_data) / sizeof(in_data[0]);
    OptionBuffer in_buf(in_data, in_data + in_data_size);

    // Create option instance. Check that constructor doesn't throw.
    boost::scoped_ptr<Option4ClientFqdn> option;
    ASSERT_NO_THROW(
        option.reset(new Option4ClientFqdn(in_buf.begin(), in_buf.end()))
    );
    ASSERT_TRUE(option);

    EXPECT_FALSE(option->getFlag(Option4ClientFqdn::FLAG_S));
    EXPECT_TRUE(option->getFlag(Option4ClientFqdn::FLAG_E));
    EXPECT_FALSE(option->getFlag(Option4ClientFqdn::FLAG_O));
    EXPECT_TRUE(option->getFlag(Option4ClientFqdn::FLAG_N));
    EXPECT_EQ("myhost", option->getDomainName());
    EXPECT_EQ(Option4ClientFqdn::PARTIAL, option->getDomainNameType());
}

// This test verifies that the option in the on-wire format with partial
// domain-name encoded in ASCII format is parsed correctly.
TEST(Option4ClientFqdnTest, constructFromWirePartialASCII) {
    // There is no "dot" character at the end, so the domain-name is partial.
    const uint8_t in_data[] = {
        Option4ClientFqdn::FLAG_N,            // flags
        255,                                  // RCODE1
        255,                                  // RCODE2
        109, 121, 104, 111, 115, 116, 46,     // myhost.
        101, 120, 97, 109, 112, 108, 101      // example
    };
    size_t in_data_size = sizeof(in_data) / sizeof(in_data[0]);
    OptionBuffer in_buf(in_data, in_data + in_data_size);

    // Create option instance. Check that constructor doesn't throw.
    boost::scoped_ptr<Option4ClientFqdn> option;
    ASSERT_NO_THROW(
        option.reset(new Option4ClientFqdn(in_buf.begin(), in_buf.end()))
    );
    ASSERT_TRUE(option);

    EXPECT_FALSE(option->getFlag(Option4ClientFqdn::FLAG_S));
    EXPECT_FALSE(option->getFlag(Option4ClientFqdn::FLAG_E));
    EXPECT_FALSE(option->getFlag(Option4ClientFqdn::FLAG_O));
    EXPECT_TRUE(option->getFlag(Option4ClientFqdn::FLAG_N));
    EXPECT_EQ("myhost.example", option->getDomainName());
    EXPECT_EQ(Option4ClientFqdn::PARTIAL, option->getDomainNameType());
}

// This test verifies that the option in the on-wire format with empty
// domain-name is parsed correctly.
TEST(Option4ClientFqdnTest, constructFromWireEmpty) {
    // Initialize the 3-byte long buffer. All bytes initialized to 0:
    // Flags, RCODE1 and RCODE2.
    OptionBuffer in_buf(3, 0);
    // Create option instance. Check that constructor doesn't throw.
    boost::scoped_ptr<Option4ClientFqdn> option;
    ASSERT_NO_THROW(
        option.reset(new Option4ClientFqdn(in_buf.begin(), in_buf.end()))
    );
    ASSERT_TRUE(option);

    // domain-name field should be empty because on-wire data comprised
    // flags field only.
    EXPECT_TRUE(option->getDomainName().empty());
}

// This test verifies that assignment operator can be used to assign one
// instance of the option to another.
TEST(Option4ClientFqdnTest, assignment) {
    // Usually the smart pointer is used to declare options and call
    // constructor within assert. Thanks to this approach, the option instance
    // is in the function scope and only initialization is done within assert.
    // In this particular test we can't use smart pointers because we are
    // testing assignment operator like this:
    //
    //          option2 = option;
    //
    // The two asserts below do not create the instances that we will used to
    // test assignment. They just attempt to create instances of the options
    // with the same parameters as those that will be created for the actual
    // assignment test. If these asserts do not fail, we can create options
    // for the assignment test, do not surround them with asserts and be sure
    // they will not throw.
    ASSERT_NO_THROW(Option4ClientFqdn(Option4ClientFqdn::FLAG_S |
                                      Option4ClientFqdn::FLAG_E,
                                      Option4ClientFqdn::RCODE_SERVER(),
                                      "myhost.example.com",
                                      Option4ClientFqdn::FULL));

    ASSERT_NO_THROW(Option4ClientFqdn(Option4ClientFqdn::FLAG_N |
                                      Option4ClientFqdn::FLAG_E,
                                      Option4ClientFqdn::RCODE_SERVER(),
                                      "myhost",
                                      Option4ClientFqdn::PARTIAL));

    // Create options with the same parameters as tested above.

    // Create first option.
    Option4ClientFqdn option(Option4ClientFqdn::FLAG_S |
                             Option4ClientFqdn::FLAG_E,
                             Option4ClientFqdn::RCODE_SERVER(),
                             "myhost.example.com",
                             Option4ClientFqdn::FULL);

    // Verify that the values have been set correctly.
    ASSERT_TRUE(option.getFlag(Option4ClientFqdn::FLAG_S));
    ASSERT_TRUE(option.getFlag(Option4ClientFqdn::FLAG_E));
    ASSERT_FALSE(option.getFlag(Option4ClientFqdn::FLAG_O));
    ASSERT_FALSE(option.getFlag(Option4ClientFqdn::FLAG_N));
    ASSERT_EQ("myhost.example.com.", option.getDomainName());
    ASSERT_EQ(Option4ClientFqdn::FULL, option.getDomainNameType());

    // Create a second option.
    Option4ClientFqdn option2(Option4ClientFqdn::FLAG_N |
                              Option4ClientFqdn::FLAG_E,
                              Option4ClientFqdn::RCODE_SERVER(),
                              "myhost",
                              Option4ClientFqdn::PARTIAL);

    // Verify tha the values have been set correctly.
    ASSERT_FALSE(option2.getFlag(Option4ClientFqdn::FLAG_S));
    ASSERT_TRUE(option2.getFlag(Option4ClientFqdn::FLAG_E));
    ASSERT_FALSE(option2.getFlag(Option4ClientFqdn::FLAG_O));
    ASSERT_TRUE(option2.getFlag(Option4ClientFqdn::FLAG_N));
    ASSERT_EQ("myhost", option2.getDomainName());
    ASSERT_EQ(Option4ClientFqdn::PARTIAL, option2.getDomainNameType());


    // Make the assignment.
    ASSERT_NO_THROW(option2 = option);

    // Both options should now have the same values.
    EXPECT_TRUE(option2.getFlag(Option4ClientFqdn::FLAG_S));
    EXPECT_TRUE(option2.getFlag(Option4ClientFqdn::FLAG_E));
    EXPECT_FALSE(option2.getFlag(Option4ClientFqdn::FLAG_O));
    EXPECT_FALSE(option2.getFlag(Option4ClientFqdn::FLAG_N));
    EXPECT_EQ(option.getDomainName(), option2.getDomainName());
    EXPECT_EQ(option.getDomainNameType(), option2.getDomainNameType());

    // Make self-assignment.
    ASSERT_NO_THROW(option2 = option2);
    EXPECT_TRUE(option2.getFlag(Option4ClientFqdn::FLAG_S));
    EXPECT_TRUE(option2.getFlag(Option4ClientFqdn::FLAG_E));
    EXPECT_FALSE(option2.getFlag(Option4ClientFqdn::FLAG_O));
    EXPECT_FALSE(option2.getFlag(Option4ClientFqdn::FLAG_N));
    EXPECT_EQ(option.getDomainName(), option2.getDomainName());
    EXPECT_EQ(option.getDomainNameType(), option2.getDomainNameType());
}

// This test verifies that constructor will throw an exception if invalid
// DHCPv6 Client FQDN Option flags are specified.
TEST(Option4ClientFqdnTest, constructInvalidFlags) {
    // First, check that constructor does not throw an exception when
    // valid flags values are provided. That way we eliminate the issue
    // that constructor always throws exception.
    uint8_t flags = 0;
    ASSERT_NO_THROW(Option4ClientFqdn(flags, Option4ClientFqdn::RCODE_CLIENT(),
                                      "myhost.example.com"));

    // Invalid flags: The maximal value is 0xF when all flag bits are set
    // (00001111b). The flag value of 0x18 sets the bit from the Must Be
    // Zero (MBZ) bitset (00011000b).
    flags = 0x18;
    EXPECT_THROW(Option4ClientFqdn(flags, Option4ClientFqdn::RCODE_CLIENT(),
                                   "myhost.example.com"),
                 InvalidOption4FqdnFlags);

    // According to RFC 4702, section 2.1. if the N bit is set the S bit MUST
    // be zero. If both are set, constructor is expected to throw.
    flags = Option4ClientFqdn::FLAG_N | Option4ClientFqdn::FLAG_S;
    EXPECT_THROW(Option4ClientFqdn(flags, Option4ClientFqdn::RCODE_CLIENT(),
                                   "myhost.example.com"),
                 InvalidOption4FqdnFlags);
}

// This test verifies that constructor which parses option from on-wire format
// will throw exception if parsed flags field is invalid.
TEST(Option4ClientFqdnTest, constructFromWireInvalidFlags) {
    // Create a buffer which holds flags field only. Set valid flag field at
    // at first to make sure that constructor doesn't always throw an exception.
    OptionBuffer in_buf(3, 0);
    in_buf[0] = Option4ClientFqdn::FLAG_S;
    ASSERT_NO_THROW(Option4ClientFqdn(in_buf.begin(), in_buf.end()));

    // Replace the flags with invalid value and verify that constructor throws
    // appropriate exception.
    in_buf[0] = Option4ClientFqdn::FLAG_N | Option4ClientFqdn::FLAG_S;
    EXPECT_THROW(Option4ClientFqdn(in_buf.begin(), in_buf.end()),
                 InvalidOption4FqdnFlags);
}

// This test verifies that if invalid domain name is used the constructor
// will throw appropriate exception.
TEST(Option4ClientFqdnTest, constructInvalidName) {
    // First, check that constructor does not throw when valid domain name
    // is specified. That way we eliminate the possibility that constructor
    // always throws exception.
    ASSERT_NO_THROW(Option4ClientFqdn(Option4ClientFqdn::FLAG_E,
                                      Option4ClientFqdn::RCODE_CLIENT(),
                                      "myhost.example.com"));

    // Specify invalid domain name and expect that exception is thrown.
    EXPECT_THROW(Option4ClientFqdn(Option4ClientFqdn::FLAG_E,
                                   Option4ClientFqdn::RCODE_CLIENT(),
                                   "my...host.example.com"),
                 InvalidOption4FqdnDomainName);

    // Do the same test for the domain-name in ASCII format.
    ASSERT_NO_THROW(Option4ClientFqdn(0, Option4ClientFqdn::RCODE_CLIENT(),
                                      "myhost.example.com"));

    EXPECT_THROW(Option4ClientFqdn(0, Option4ClientFqdn::RCODE_CLIENT(),
                                   "my...host.example.com"),
                 InvalidOption4FqdnDomainName);
}

// This test verifies that getFlag throws an exception if flag value other
// than N, E, O, S was specified.
TEST(Option4ClientFqdnTest, getFlag) {
    boost::scoped_ptr<Option4ClientFqdn> option;
    ASSERT_NO_THROW(
        option.reset(new Option4ClientFqdn(Option4ClientFqdn::FLAG_E,
                                           Option4ClientFqdn::RCODE_CLIENT(),
                                           "myhost.example.com"))
    );
    ASSERT_TRUE(option);

    // The value of 0x3 (binary 0011) is invalid because it specifies two bits
    // in the flags field which value is to be checked.
    EXPECT_THROW(option->getFlag(0x3), InvalidOption4FqdnFlags);
}

// This test verifies that flags can be modified and that incorrect flags
// are rejected.
TEST(Option4ClientFqdnTest, setFlag) {
    // Create option instance. Check that constructor doesn't throw.
    boost::scoped_ptr<Option4ClientFqdn> option;
    ASSERT_NO_THROW(
        option.reset(new Option4ClientFqdn(0,
                                           Option4ClientFqdn::RCODE_CLIENT(),
                                           "myhost.example.com"))
    );
    ASSERT_TRUE(option);

    // All flags should be set to 0 initially.
    ASSERT_FALSE(option->getFlag(Option4ClientFqdn::FLAG_N));
    ASSERT_FALSE(option->getFlag(Option4ClientFqdn::FLAG_S));
    ASSERT_FALSE(option->getFlag(Option4ClientFqdn::FLAG_O));
    ASSERT_FALSE(option->getFlag(Option4ClientFqdn::FLAG_E));

    // Set E = 1
    ASSERT_NO_THROW(option->setFlag(Option4ClientFqdn::FLAG_E, true));
    ASSERT_TRUE(option->getFlag(Option4ClientFqdn::FLAG_E));

    // Set N = 1
    ASSERT_NO_THROW(option->setFlag(Option4ClientFqdn::FLAG_N, true));
    ASSERT_TRUE(option->getFlag(Option4ClientFqdn::FLAG_N));

    // Set O = 1
    ASSERT_NO_THROW(option->setFlag(Option4ClientFqdn::FLAG_O, true));
    ASSERT_TRUE(option->getFlag(Option4ClientFqdn::FLAG_O));

    // Set S = 1, this should throw exception because S and N must not
    // be set in the same time.
    ASSERT_THROW(option->setFlag(Option4ClientFqdn::FLAG_S, true),
                 InvalidOption4FqdnFlags);

    // Set E = 0
    ASSERT_NO_THROW(option->setFlag(Option4ClientFqdn::FLAG_N, false));
    ASSERT_FALSE(option->getFlag(Option4ClientFqdn::FLAG_N));

    // Set N = 0
    ASSERT_NO_THROW(option->setFlag(Option4ClientFqdn::FLAG_N, false));
    ASSERT_FALSE(option->getFlag(Option4ClientFqdn::FLAG_N));

    // Set S = 1, this should not result in exception because N has been
    // cleared.
    ASSERT_NO_THROW(option->setFlag(Option4ClientFqdn::FLAG_S, true));
    ASSERT_TRUE(option->getFlag(Option4ClientFqdn::FLAG_S));

    // Set N = 1, this should result in exception because S = 1
    ASSERT_THROW(option->setFlag(Option4ClientFqdn::FLAG_N, true),
                 InvalidOption4FqdnFlags);

    // Set O = 0
    ASSERT_NO_THROW(option->setFlag(Option4ClientFqdn::FLAG_O, false));
    ASSERT_FALSE(option->getFlag(Option4ClientFqdn::FLAG_O));

    // Try out of bounds settings.
    uint8_t flags = 0;
    ASSERT_THROW(option->setFlag(flags, true), InvalidOption4FqdnFlags);

    flags = 0x18;
    ASSERT_THROW(option->setFlag(flags, true), InvalidOption4FqdnFlags);
}

// This test verifies that flags field of the option is set to 0 when resetFlags
// function is called.
TEST(Option4ClientFqdnTest, resetFlags) {
    boost::scoped_ptr<Option4ClientFqdn> option;
    ASSERT_NO_THROW(
        option.reset(new Option4ClientFqdn(Option4ClientFqdn::FLAG_S |
                                           Option4ClientFqdn::FLAG_O |
                                           Option4ClientFqdn::FLAG_E,
                                           Option4ClientFqdn::RCODE_CLIENT(),
                                           "myhost.example.com",
                                           Option4ClientFqdn::FULL))
    );
    ASSERT_TRUE(option);

    // Check that flags we set in the constructor are set.
    ASSERT_TRUE(option->getFlag(Option4ClientFqdn::FLAG_S));
    ASSERT_TRUE(option->getFlag(Option4ClientFqdn::FLAG_O));
    ASSERT_FALSE(option->getFlag(Option4ClientFqdn::FLAG_N));
    ASSERT_TRUE(option->getFlag(Option4ClientFqdn::FLAG_E));

    option->resetFlags();

    // After reset, all flags should be 0.
    EXPECT_FALSE(option->getFlag(Option4ClientFqdn::FLAG_S));
    EXPECT_FALSE(option->getFlag(Option4ClientFqdn::FLAG_O));
    EXPECT_FALSE(option->getFlag(Option4ClientFqdn::FLAG_N));
    EXPECT_FALSE(option->getFlag(Option4ClientFqdn::FLAG_E));
}

// This test verifies that current domain-name can be replaced with a new
// domain-name.
TEST(Option4ClientFqdnTest, setDomainName) {
    boost::scoped_ptr<Option4ClientFqdn> option;
    ASSERT_NO_THROW(
        option.reset(new Option4ClientFqdn(Option4ClientFqdn::FLAG_S |
                                           Option4ClientFqdn::FLAG_E,
                                           Option4ClientFqdn::RCODE_SERVER(),
                                           "myhost.example.com",
                                           Option4ClientFqdn::FULL))
    );
    ASSERT_TRUE(option);
    ASSERT_EQ("myhost.example.com.", option->getDomainName());
    ASSERT_EQ(Option4ClientFqdn::FULL, option->getDomainNameType());

    // Partial domain-name.
    ASSERT_NO_THROW(option->setDomainName("myhost",
                                          Option4ClientFqdn::PARTIAL));
    EXPECT_EQ("myhost", option->getDomainName());
    EXPECT_EQ(Option4ClientFqdn::PARTIAL, option->getDomainNameType());

    // Fully qualified domain-name.
    ASSERT_NO_THROW(option->setDomainName("example.com",
                                          Option4ClientFqdn::FULL));
    EXPECT_EQ("example.com.", option->getDomainName());
    EXPECT_EQ(Option4ClientFqdn::FULL, option->getDomainNameType());

    // Empty domain name (partial). This should be successful.
    ASSERT_NO_THROW(option->setDomainName("", Option4ClientFqdn::PARTIAL));
    EXPECT_TRUE(option->getDomainName().empty());
    EXPECT_EQ(Option4ClientFqdn::PARTIAL, option->getDomainNameType());

    // Fully qualified domain-names must not be empty.
    EXPECT_THROW(option->setDomainName("", Option4ClientFqdn::FULL),
                 InvalidOption4FqdnDomainName);
    EXPECT_THROW(option->setDomainName(" ", Option4ClientFqdn::FULL),
                 InvalidOption4FqdnDomainName);
}

// This test verifies that current domain-name can be reset to empty one.
TEST(Option4ClientFqdnTest, resetDomainName) {
    boost::scoped_ptr<Option4ClientFqdn> option;
    ASSERT_NO_THROW(
        option.reset(new Option4ClientFqdn(Option4ClientFqdn::FLAG_S |
                                           Option4ClientFqdn::FLAG_E,
                                           Option4ClientFqdn::RCODE_CLIENT(),
                                           "myhost.example.com",
                                           Option4ClientFqdn::FULL))
    );
    ASSERT_TRUE(option);
    ASSERT_EQ("myhost.example.com.", option->getDomainName());
    ASSERT_EQ(Option4ClientFqdn::FULL, option->getDomainNameType());

    // Set the domain-name to empty one.
    ASSERT_NO_THROW(option->resetDomainName());
    EXPECT_TRUE(option->getDomainName().empty());
}

// This test verifies on-wire format of the option is correctly created.
TEST(Option4ClientFqdnTest, pack) {
    // Create option instance. Check that constructor doesn't throw.
    const uint8_t flags = Option4ClientFqdn::FLAG_S | Option4ClientFqdn::FLAG_E;
    boost::scoped_ptr<Option4ClientFqdn> option;
    ASSERT_NO_THROW(
        option.reset(new Option4ClientFqdn(flags,
                                           Option4ClientFqdn::RCODE_CLIENT(),
                                           "myhost.example.com"))
    );
    ASSERT_TRUE(option);

    // Prepare on-wire format of the option.
    isc::util::OutputBuffer buf(10);
    ASSERT_NO_THROW(option->pack(buf));

    // Prepare reference data.
    const uint8_t ref_data[] = {
        81, 23,                                                 // header
        Option4ClientFqdn::FLAG_S | Option4ClientFqdn::FLAG_E,  // flags
        0,                                                      // RCODE1
        0,                                                      // RCODE2
        6, 109, 121, 104, 111, 115, 116,                        // myhost.
        7, 101, 120, 97, 109, 112, 108, 101,                    // example.
        3, 99, 111, 109, 0                                      // com.
    };
    size_t ref_data_size = sizeof(ref_data) / sizeof(ref_data[0]);

    // Check if the buffer has the same length as the reference data,
    // so as they can be compared directly.
    ASSERT_EQ(ref_data_size, buf.getLength());
    EXPECT_EQ(0, memcmp(ref_data, buf.getData(), buf.getLength()));
}

TEST(Option4ClientFqdnTest, packASCII) {
    // Create option instance. Check that constructor doesn't throw.
    const uint8_t flags = Option4ClientFqdn::FLAG_S;
    boost::scoped_ptr<Option4ClientFqdn> option;
    ASSERT_NO_THROW(
        option.reset(new Option4ClientFqdn(flags,
                                           Option4ClientFqdn::RCODE_CLIENT(),
                                           "myhost.example.com"))
    );
    ASSERT_TRUE(option);

    // Prepare on-wire format of the option.
    isc::util::OutputBuffer buf(10);
    ASSERT_NO_THROW(option->pack(buf));

    // Prepare reference data.
    const uint8_t ref_data[] = {
        81, 22,                               // header
        Option4ClientFqdn::FLAG_S,            // flags
        0,                                    // RCODE1
        0,                                    // RCODE2
        109, 121, 104, 111, 115, 116, 46,     // myhost.
        101, 120, 97, 109, 112, 108, 101, 46, // example.
        99, 111, 109, 46                      // com.
    };
    size_t ref_data_size = sizeof(ref_data) / sizeof(ref_data[0]);

    // Check if the buffer has the same length as the reference data,
    // so as they can be compared directly.
    ASSERT_EQ(ref_data_size, buf.getLength());
    EXPECT_EQ(0, memcmp(ref_data, buf.getData(), buf.getLength()));

}

// This test verifies on-wire format of the option with partial domain name
// is correctly created.
TEST(Option4ClientFqdnTest, packPartial) {
    // Create option instance. Check that constructor doesn't throw.
    const uint8_t flags = Option4ClientFqdn::FLAG_S | Option4ClientFqdn::FLAG_E;
    boost::scoped_ptr<Option4ClientFqdn> option;
    ASSERT_NO_THROW(
        option.reset(new Option4ClientFqdn(flags,
                                           Option4ClientFqdn::RCODE_CLIENT(),
                                           "myhost",
                                           Option4ClientFqdn::PARTIAL))
    );
    ASSERT_TRUE(option);

    // Prepare on-wire format of the option.
    isc::util::OutputBuffer buf(10);
    ASSERT_NO_THROW(option->pack(buf));

    // Prepare reference data.
    const uint8_t ref_data[] = {
        81, 10,                                                // header
        Option4ClientFqdn::FLAG_S | Option4ClientFqdn::FLAG_E, // flags
        0,                                                     // RCODE1
        0,                                                     // RCODE2
        6, 109, 121, 104, 111, 115, 116                        // myhost
    };
    size_t ref_data_size = sizeof(ref_data) / sizeof(ref_data[0]);

    // Check if the buffer has the same length as the reference data,
    // so as they can be compared directly.
    ASSERT_EQ(ref_data_size, buf.getLength());
    EXPECT_EQ(0, memcmp(ref_data, buf.getData(), buf.getLength()));
}

// This test verifies that it is possible to encode option with empty
// domain-name in the on-wire format.
TEST(Option4ClientFqdnTest, packEmpty) {
    // Create option instance. Check that constructor doesn't throw.
    const uint8_t flags = Option4ClientFqdn::FLAG_S | Option4ClientFqdn::FLAG_E;
    boost::scoped_ptr<Option4ClientFqdn> option;
    ASSERT_NO_THROW(
        option.reset(new Option4ClientFqdn(flags,
                                           Option4ClientFqdn::RCODE_CLIENT()))
    );
    ASSERT_TRUE(option);

    // Prepare on-wire format of the option.
    isc::util::OutputBuffer buf(10);
    ASSERT_NO_THROW(option->pack(buf));

    // Prepare reference data.
    const uint8_t ref_data[] = {
        81, 3,                                                 // header
        Option4ClientFqdn::FLAG_S | Option4ClientFqdn::FLAG_E, // flags
        0,                                                     // RCODE1
        0                                                      // RCODE2
    };
    size_t ref_data_size = sizeof(ref_data) / sizeof(ref_data[0]);

    // Check if the buffer has the same length as the reference data,
    // so as they can be compared directly.
    ASSERT_EQ(ref_data_size, buf.getLength());
    EXPECT_EQ(0, memcmp(ref_data, buf.getData(), buf.getLength()));
}

// This test verifies that on-wire option data holding fully qualified domain
// name is parsed correctly.
TEST(Option4ClientFqdnTest, unpack) {
    // Create option instance. Check that constructor doesn't throw.
    boost::scoped_ptr<Option4ClientFqdn> option;
    ASSERT_NO_THROW(
        option.reset(new Option4ClientFqdn(Option4ClientFqdn::FLAG_O |
                                           Option4ClientFqdn::FLAG_E,
                                           Option4ClientFqdn::RCODE_CLIENT(),
                                           "myhost",
                                           Option4ClientFqdn::PARTIAL))
    );
    ASSERT_TRUE(option);
    // Make sure that the parameters have been set correctly. Later in this
    // test we will check that they will be replaced with new values when
    // unpack is called.
    EXPECT_FALSE(option->getFlag(Option4ClientFqdn::FLAG_S));
    EXPECT_FALSE(option->getFlag(Option4ClientFqdn::FLAG_N));
    EXPECT_TRUE(option->getFlag(Option4ClientFqdn::FLAG_O));
    EXPECT_TRUE(option->getFlag(Option4ClientFqdn::FLAG_E));
    EXPECT_EQ("myhost", option->getDomainName());
    EXPECT_EQ(Option4ClientFqdn::PARTIAL, option->getDomainNameType());

    const uint8_t in_data[] = {
        Option4ClientFqdn::FLAG_S | Option4ClientFqdn::FLAG_E, // flags
        0,                                                     // RCODE1
        0,                                                     // RCODE2
        6, 109, 121, 104, 111, 115, 116,                       // myhost.
        7, 101, 120, 97, 109, 112, 108, 101,                   // example.
        3, 99, 111, 109, 0                                     // com.
    };
    size_t in_data_size = sizeof(in_data) / sizeof(in_data[0]);
    OptionBuffer in_buf(in_data, in_data + in_data_size);

    // Initialize new values from the on-wire format.
    ASSERT_NO_THROW(option->unpack(in_buf.begin(), in_buf.end()));

    // Check that new values are correct.
    EXPECT_TRUE(option->getFlag(Option4ClientFqdn::FLAG_S));
    EXPECT_FALSE(option->getFlag(Option4ClientFqdn::FLAG_N));
    EXPECT_FALSE(option->getFlag(Option4ClientFqdn::FLAG_O));
    EXPECT_TRUE(option->getFlag(Option4ClientFqdn::FLAG_E));
    EXPECT_EQ("myhost.example.com.", option->getDomainName());
    EXPECT_EQ(Option4ClientFqdn::FULL, option->getDomainNameType());
}

// This test verifies that on-wire option data holding partial domain name
// is parsed correctly.
TEST(Option4ClientFqdnTest, unpackPartial) {
    // Create option instance. Check that constructor doesn't throw.
    boost::scoped_ptr<Option4ClientFqdn> option;
    ASSERT_NO_THROW(
        option.reset(new Option4ClientFqdn(Option4ClientFqdn::FLAG_O |
                                           Option4ClientFqdn::FLAG_E,
                                           Option4ClientFqdn::RCODE_CLIENT(),
                                           "myhost.example.com"))
    );
    ASSERT_TRUE(option);
    // Make sure that the parameters have been set correctly. Later in this
    // test we will check that they will be replaced with new values when
    // unpack is called.
    EXPECT_FALSE(option->getFlag(Option4ClientFqdn::FLAG_S));
    EXPECT_FALSE(option->getFlag(Option4ClientFqdn::FLAG_N));
    EXPECT_TRUE(option->getFlag(Option4ClientFqdn::FLAG_O));
    EXPECT_TRUE(option->getFlag(Option4ClientFqdn::FLAG_E));
    EXPECT_EQ("myhost.example.com.", option->getDomainName());
    EXPECT_EQ(Option4ClientFqdn::FULL, option->getDomainNameType());

    const uint8_t in_data[] = {
        Option4ClientFqdn::FLAG_S | Option4ClientFqdn::FLAG_E, // flags
        0,                                                     // RCODE1
        0,                                                     // RCODE2
        6, 109, 121, 104, 111, 115, 116                        // myhost
    };
    size_t in_data_size = sizeof(in_data) / sizeof(in_data[0]);
    OptionBuffer in_buf(in_data, in_data + in_data_size);

    // Initialize new values from the on-wire format.
    ASSERT_NO_THROW(option->unpack(in_buf.begin(), in_buf.end()));

    // Check that new values are correct.
    EXPECT_TRUE(option->getFlag(Option4ClientFqdn::FLAG_S));
    EXPECT_TRUE(option->getFlag(Option4ClientFqdn::FLAG_E));
    EXPECT_FALSE(option->getFlag(Option4ClientFqdn::FLAG_N));
    EXPECT_FALSE(option->getFlag(Option4ClientFqdn::FLAG_O));
    EXPECT_EQ("myhost", option->getDomainName());
    EXPECT_EQ(Option4ClientFqdn::PARTIAL, option->getDomainNameType());
}

// This test verifies that the empty buffer is rejected when decoding an option
// from on-wire format.
TEST(Option4ClientFqdnTest, unpackTruncated) {
    boost::scoped_ptr<Option4ClientFqdn> option;
    ASSERT_NO_THROW(
        option.reset(new Option4ClientFqdn(Option4ClientFqdn::FLAG_O |
                                           Option4ClientFqdn::FLAG_E,
                                           Option4ClientFqdn::RCODE_CLIENT()))
    );
    ASSERT_TRUE(option);

    // Empty buffer is invalid. It should be at least 1 octet long.
    OptionBuffer in_buf;
    EXPECT_THROW(option->unpack(in_buf.begin(), in_buf.end()), OutOfRange);
}

// This test verifies that string representation of the option returned by
// toText method is correctly formatted.
TEST(Option4ClientFqdnTest, toText) {
    // Create option instance. Check that constructor doesn't throw.
    uint8_t flags = Option4ClientFqdn::FLAG_N | Option4ClientFqdn::FLAG_O |
        Option4ClientFqdn::FLAG_E;
    boost::scoped_ptr<Option4ClientFqdn> option;
    ASSERT_NO_THROW(
        option.reset(new Option4ClientFqdn(flags,
                                           Option4ClientFqdn::RCODE_CLIENT(),
                                           "myhost.example.com"))
    );
    ASSERT_TRUE(option);

    // The base indentation of the option will be set to 2. It should appear
    // as follows.
    std::string ref_string =
        "  type=81 (CLIENT_FQDN), flags: (N=1, E=1, O=1, S=0), "
        "domain-name='myhost.example.com.' (full)";
    const int indent = 2;
    EXPECT_EQ(ref_string, option->toText(indent));

    // Create another option with different parameters:
    // - flags set to 0
    // - domain-name is now partial, not fully qualified
    // Also, remove base indentation.
    flags = 0;
    ASSERT_NO_THROW(
        option.reset(new Option4ClientFqdn(flags,
                                           Option4ClientFqdn::RCODE_CLIENT(),
                                           "myhost",
                                           Option4ClientFqdn::PARTIAL))
    );
    ref_string =
        "type=81 (CLIENT_FQDN), flags: (N=0, E=0, O=0, S=0), "
        "domain-name='myhost' (partial)";
    EXPECT_EQ(ref_string, option->toText());
}

// This test verifies that the correct length of the option in on-wire
// format is returned.
TEST(Option4ClientFqdnTest, len) {
    // Create option instance. Check that constructor doesn't throw.
    boost::scoped_ptr<Option4ClientFqdn> option;
    ASSERT_NO_THROW(
        option.reset(new Option4ClientFqdn(Option4ClientFqdn::FLAG_E,
                                           Option4ClientFqdn::RCODE_CLIENT(),
                                           "myhost.example.com"))
    );
    ASSERT_TRUE(option);
    // This option comprises a header (2 octets), flag field (1 octet),
    // RCODE1 and RCODE2 (2 octets) and wire representation of the
    // domain name (length equal to the length of the string representation
    // of the domain name + 1).
    EXPECT_EQ(25, option->len());

    // Let's check that the size will change when domain name of a different
    // size is used.
    ASSERT_NO_THROW(
        option.reset(new Option4ClientFqdn(Option4ClientFqdn::FLAG_E,
                                           Option4ClientFqdn::RCODE_CLIENT(),
                                           "example.com"))
    );
    ASSERT_TRUE(option);
    EXPECT_EQ(18, option->len());

    ASSERT_NO_THROW(
        option.reset(new Option4ClientFqdn(Option4ClientFqdn::FLAG_E,
                                           Option4ClientFqdn::RCODE_CLIENT(),
                                           "myhost",
                                           Option4ClientFqdn::PARTIAL))
    );
    ASSERT_TRUE(option);
    EXPECT_EQ(12, option->len());

    // Another test for partial domain name but this time the domain name
    // contains two labels.
    ASSERT_NO_THROW(
        option.reset(new Option4ClientFqdn(Option4ClientFqdn::FLAG_E,
                                           Option4ClientFqdn::RCODE_CLIENT(),
                                           "myhost.example",
                                           Option4ClientFqdn::PARTIAL))
    );
    ASSERT_TRUE(option);
    EXPECT_EQ(20, option->len());

}

// This test verifies that the correct length of the option in on-wire
// format is returned when ASCII encoding for FQDN is in use.
TEST(Option4ClientFqdnTest, lenAscii) {
    // Create option instance. Check that constructor doesn't throw.
    boost::scoped_ptr<Option4ClientFqdn> option;
    ASSERT_NO_THROW(
        option.reset(new Option4ClientFqdn(0, Option4ClientFqdn::RCODE_CLIENT(),
                                           "myhost.example.com"))
    );
    ASSERT_TRUE(option);

    // This option comprises a header (2 octets), flag field (1 octet),
    // RCODE1 and RCODE2 (2 octets) and the domain name in the ASCII format.
    // The length of the domain name in the ASCII format is 19 - length
    // of the string plus terminating dot.
    EXPECT_EQ(24, option->len());

    // Let's change the domain name and see if the length is different.
    ASSERT_NO_THROW(
        option.reset(new Option4ClientFqdn(0, Option4ClientFqdn::RCODE_CLIENT(),
                                           "example.com"))
    );
    ASSERT_TRUE(option);

    EXPECT_EQ(17, option->len());

    // Let's test the length of the option when the partial domain name is
    // specified.
    ASSERT_NO_THROW(
        option.reset(new Option4ClientFqdn(0, Option4ClientFqdn::RCODE_CLIENT(),
                                           "myhost",
                                           Option4ClientFqdn::PARTIAL))
    );
    ASSERT_TRUE(option);

    // For partial names, there is no terminating dot, so the length of the
    // domain name is equal to the length of the "myhost".
    EXPECT_EQ(11, option->len());

    // Another check for partial domain name but this time the domain name
    // contains two labels.
    ASSERT_NO_THROW(
        option.reset(new Option4ClientFqdn(0, Option4ClientFqdn::RCODE_CLIENT(),
                                           "myhost.example",
                                           Option4ClientFqdn::PARTIAL))
    );
    ASSERT_TRUE(option);

    EXPECT_EQ(19, option->len());


    // A special case is an empty domain name for which the returned length
    // should be a sum of the header length, RCODE1, RCODE2 and flag fields
    // length.
    ASSERT_NO_THROW(
        option.reset(new Option4ClientFqdn(0, Option4ClientFqdn::RCODE_CLIENT(),
                                           "", Option4ClientFqdn::PARTIAL))
    );
    ASSERT_TRUE(option);

    EXPECT_EQ(5, option->len());
}

} // anonymous namespace
