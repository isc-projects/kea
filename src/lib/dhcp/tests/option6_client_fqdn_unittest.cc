// Copyright (C) 2013 Internet Systems Consortium, Inc. ("ISC")
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES WITH
// REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS.  IN NO EVENT SHALL ISC BE LIABLE FOR ANY SPECIAL, DIRECT,
// INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
// LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
// OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
// PERFORMANCE OF THIS SOFTWARE.

#include <config.h>
#include <dhcp/option6_client_fqdn.h>
#include <dns/name.h>
#include <util/buffer.h>
#include <boost/scoped_ptr.hpp>
#include <gtest/gtest.h>

namespace {

using namespace isc;
using namespace isc::dhcp;

// Redefine option flags here as uint8_t. They will be used to initialize
// elements of the arrays that are used in tests below. Note that use of
// enum values defined in Option6ClientFqdn class may cause compilation issues
// during uint8_t arrays initialization. That is because the underlying
// integral type used to represent enums is larger than one byte.
const uint8_t FLAG_S = 0x01;
const uint8_t FLAG_O = 0x02;
const uint8_t FLAG_N = 0x04;

// This test verifies that constructor accepts empty partial domain-name but
// does not accept empty fully qualified domain name.
TEST(Option6ClientFqdnTest, constructEmptyName) {
    // Create an instance of the source option.
    boost::scoped_ptr<Option6ClientFqdn> option;
    ASSERT_NO_THROW(
        option.reset(new Option6ClientFqdn(Option6ClientFqdn::FLAG_S, "",
                                           Option6ClientFqdn::PARTIAL))
    );
    ASSERT_TRUE(option);
    EXPECT_FALSE(option->getFlag(Option6ClientFqdn::FLAG_O));
    EXPECT_FALSE(option->getFlag(Option6ClientFqdn::FLAG_N));
    EXPECT_TRUE(option->getFlag(Option6ClientFqdn::FLAG_S));
    EXPECT_TRUE(option->getDomainName().empty());
    EXPECT_EQ(Option6ClientFqdn::PARTIAL, option->getDomainNameType());

    // Constructor should not accept empty fully qualified domain name.
    EXPECT_THROW(Option6ClientFqdn(Option6ClientFqdn::FLAG_S, "",
                                   Option6ClientFqdn::FULL),
                 InvalidFqdnOptionDomainName);
    // This check is similar to previous one, but using domain-name comprising
    // a single space character. This should be treated as empty domain-name.
    EXPECT_THROW(Option6ClientFqdn(Option6ClientFqdn::FLAG_S, " ",
                                   Option6ClientFqdn::FULL),
                 InvalidFqdnOptionDomainName);

    // Try different constructor.
    ASSERT_NO_THROW(
        option.reset(new Option6ClientFqdn(Option6ClientFqdn::FLAG_O))
    );
    ASSERT_TRUE(option);
    EXPECT_TRUE(option->getFlag(Option6ClientFqdn::FLAG_O));
    EXPECT_FALSE(option->getFlag(Option6ClientFqdn::FLAG_N));
    EXPECT_FALSE(option->getFlag(Option6ClientFqdn::FLAG_S));
    EXPECT_TRUE(option->getDomainName().empty());
    EXPECT_EQ(Option6ClientFqdn::PARTIAL, option->getDomainNameType());
}

// This test verifies that copy constructor makes a copy of the option and
// the source option instance can be deleted (both instances don't share
// any resources).
TEST(Option6ClientFqdnTest, copyConstruct) {
    // Create an instance of the source option.
    boost::scoped_ptr<Option6ClientFqdn> option;
    ASSERT_NO_THROW(
        option.reset(new Option6ClientFqdn(Option6ClientFqdn::FLAG_S,
                                           "myhost.example.com",
                                           Option6ClientFqdn::FULL))
    );
    ASSERT_TRUE(option);

    // Use copy constructor to create a second instance of the option.
    boost::scoped_ptr<Option6ClientFqdn> option_copy;
    ASSERT_NO_THROW(
        option_copy.reset(new Option6ClientFqdn(*option))
    );
    ASSERT_TRUE(option_copy);

    // Copy construction should result in no shared resources between
    // two objects. In particular, pointer to implementation should not
    // be shared. Thus, we can release the source object now.
    option.reset();

    // Verify that all parameters have been copied to the target object.
    EXPECT_TRUE(option_copy->getFlag(Option6ClientFqdn::FLAG_S));
    EXPECT_FALSE(option_copy->getFlag(Option6ClientFqdn::FLAG_O));
    EXPECT_FALSE(option_copy->getFlag(Option6ClientFqdn::FLAG_N));
    EXPECT_EQ("myhost.example.com.", option_copy->getDomainName());
    EXPECT_EQ(Option6ClientFqdn::FULL, option_copy->getDomainNameType());

    // Do another test with different parameters to verify that parameters
    // change when copied object is changed.

    // Create an option with different parameters.
    ASSERT_NO_THROW(
        option.reset(new Option6ClientFqdn(Option6ClientFqdn::FLAG_O,
                                           "example",
                                           Option6ClientFqdn::PARTIAL))
    );
    ASSERT_TRUE(option);

    // Call copy-constructor to copy the option.
    ASSERT_NO_THROW(
        option_copy.reset(new Option6ClientFqdn(*option))
    );
    ASSERT_TRUE(option_copy);

    option.reset();

    EXPECT_FALSE(option_copy->getFlag(Option6ClientFqdn::FLAG_S));
    EXPECT_TRUE(option_copy->getFlag(Option6ClientFqdn::FLAG_O));
    EXPECT_FALSE(option_copy->getFlag(Option6ClientFqdn::FLAG_N));
    EXPECT_EQ("example", option_copy->getDomainName());
    EXPECT_EQ(Option6ClientFqdn::PARTIAL, option_copy->getDomainNameType());
}

// This test verifies that the option in the on-wire format is parsed correctly.
TEST(Option6ClientFqdnTest, constructFromWire) {
    const uint8_t in_data[] = {
        FLAG_S,                              // flags
        6, 109, 121, 104, 111, 115, 116,     // myhost.
        7, 101, 120, 97, 109, 112, 108, 101, // example.
        3, 99, 111, 109, 0                   // com.
    };
    size_t in_data_size = sizeof(in_data) / sizeof(in_data[0]);
    OptionBuffer in_buf(in_data, in_data + in_data_size);

    // Create option instance. Check that constructor doesn't throw.
    boost::scoped_ptr<Option6ClientFqdn> option;
    ASSERT_NO_THROW(
        option.reset(new Option6ClientFqdn(in_buf.begin(), in_buf.end()))
    );
    ASSERT_TRUE(option);

    EXPECT_TRUE(option->getFlag(Option6ClientFqdn::FLAG_S));
    EXPECT_FALSE(option->getFlag(Option6ClientFqdn::FLAG_O));
    EXPECT_FALSE(option->getFlag(Option6ClientFqdn::FLAG_N));
    EXPECT_EQ("myhost.example.com.", option->getDomainName());
    EXPECT_EQ(Option6ClientFqdn::FULL, option->getDomainNameType());
}

// This test verifies that truncated option is rejected.
TEST(Option6ClientFqdnTest, constructFromWireTruncated) {
    // Empty buffer is invalid. It should be at least one octet long.
    OptionBuffer in_buf;
    ASSERT_THROW(Option6ClientFqdn(in_buf.begin(), in_buf.end()),
                 OutOfRange);
}

// This test verifies that the option in the on-wire format with partial
// domain-name is parsed correctly.
TEST(Option6ClientFqdnTest, constructFromWirePartial) {
    const uint8_t in_data[] = {
        FLAG_N,                              // flags
        6, 109, 121, 104, 111, 115, 116      // myhost
    };
    size_t in_data_size = sizeof(in_data) / sizeof(in_data[0]);
    OptionBuffer in_buf(in_data, in_data + in_data_size);

    // Create option instance. Check that constructor doesn't throw.
    boost::scoped_ptr<Option6ClientFqdn> option;
    ASSERT_NO_THROW(
        option.reset(new Option6ClientFqdn(in_buf.begin(), in_buf.end()))
    );
    ASSERT_TRUE(option);

    EXPECT_FALSE(option->getFlag(Option6ClientFqdn::FLAG_S));
    EXPECT_FALSE(option->getFlag(Option6ClientFqdn::FLAG_O));
    EXPECT_TRUE(option->getFlag(Option6ClientFqdn::FLAG_N));
    EXPECT_EQ("myhost", option->getDomainName());
    EXPECT_EQ(Option6ClientFqdn::PARTIAL, option->getDomainNameType());
}

// This test verifies that the option in the on-wire format with empty
// domain-name is parsed correctly.
TEST(Option6ClientFqdnTest, constructFromWireEmpty) {
    OptionBuffer in_buf(FLAG_S);
    // Create option instance. Check that constructor doesn't throw.
    boost::scoped_ptr<Option6ClientFqdn> option;
    ASSERT_NO_THROW(
        option.reset(new Option6ClientFqdn(in_buf.begin(), in_buf.end()))
    );
    ASSERT_TRUE(option);

    // domain-name field should be empty because on-wire data comprised
    // flags field only.
    EXPECT_TRUE(option->getDomainName().empty());
}

// This test verifies that assignment operator can be used to assign one
// instance of the option to another.
TEST(Option6ClientFqdnTest, assignment) {
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
    ASSERT_NO_THROW(Option6ClientFqdn(Option6ClientFqdn::FLAG_S,
                                      "myhost.example.com",
                                      Option6ClientFqdn::FULL));

    ASSERT_NO_THROW(Option6ClientFqdn(Option6ClientFqdn::FLAG_N,
                                      "myhost",
                                      Option6ClientFqdn::PARTIAL));

    // Create options with the same parameters as tested above.

    // Create first option.
    Option6ClientFqdn option(Option6ClientFqdn::FLAG_S,
                             "myhost.example.com",
                             Option6ClientFqdn::FULL);

    // Verify that the values have been set correctly.
    ASSERT_TRUE(option.getFlag(Option6ClientFqdn::FLAG_S));
    ASSERT_FALSE(option.getFlag(Option6ClientFqdn::FLAG_O));
    ASSERT_FALSE(option.getFlag(Option6ClientFqdn::FLAG_N));
    ASSERT_EQ("myhost.example.com.", option.getDomainName());
    ASSERT_EQ(Option6ClientFqdn::FULL, option.getDomainNameType());

    // Create a second option.
    Option6ClientFqdn option2(Option6ClientFqdn::FLAG_N,
                              "myhost",
                              Option6ClientFqdn::PARTIAL);

    // Verify tha the values have been set correctly.
    ASSERT_FALSE(option2.getFlag(Option6ClientFqdn::FLAG_S));
    ASSERT_FALSE(option2.getFlag(Option6ClientFqdn::FLAG_O));
    ASSERT_TRUE(option2.getFlag(Option6ClientFqdn::FLAG_N));
    ASSERT_EQ("myhost", option2.getDomainName());
    ASSERT_EQ(Option6ClientFqdn::PARTIAL, option2.getDomainNameType());


    // Make the assignment.
    ASSERT_NO_THROW(option2 = option);

    // Both options should now have the same values.
    EXPECT_TRUE(option2.getFlag(Option6ClientFqdn::FLAG_S));
    EXPECT_FALSE(option2.getFlag(Option6ClientFqdn::FLAG_O));
    EXPECT_FALSE(option2.getFlag(Option6ClientFqdn::FLAG_N));
    EXPECT_EQ(option.getDomainName(), option2.getDomainName());
    EXPECT_EQ(option.getDomainNameType(), option2.getDomainNameType());
}

// This test verifies that constructor will throw an exception if invalid
// DHCPv6 Client FQDN Option flags are specified.
TEST(Option6ClientFqdnTest, constructInvalidFlags) {
    // First, check that constructor does not throw an exception when
    // valid flags values are provided. That way we eliminate the issue
    // that constructor always throws exception.
    uint8_t flags = 0;
    ASSERT_NO_THROW(Option6ClientFqdn(flags, "myhost.example.com"));

    // Invalid flags: The maximal value is 0x7 when all flag bits are set
    // (00000111b). The flag value of 0x14 sets the bit from the Must Be
    // Zero (MBZ) bitset (00001100b).
    flags = 0x14;
    EXPECT_THROW(Option6ClientFqdn(flags, "myhost.example.com"),
                 InvalidFqdnOptionFlags);

    // According to RFC 4704, section 4.1. if the N bit is set the S bit MUST
    // be zero. If both are set, constructor is expected to throw.
    flags = Option6ClientFqdn::FLAG_N | Option6ClientFqdn::FLAG_S;
    EXPECT_THROW(Option6ClientFqdn(flags, "myhost.example.com"),
                 InvalidFqdnOptionFlags);
}

// This test verifies that constructor which parses option from on-wire format
// will throw exception if parsed flags field is invalid.
TEST(Option6ClientFqdnTest, constructFromWireInvalidFlags) {
    // Create a buffer which holds flags field only. Set valid flag field at
    // at first to make sure that constructor doesn't always throw an exception.
    OptionBuffer in_buf(FLAG_N);
    ASSERT_NO_THROW(Option6ClientFqdn(in_buf.begin(), in_buf.end()));

    // Replace the flags with invalid value and verify that constructor throws
    // appropriate exception.
    in_buf[0] = FLAG_N | FLAG_S;
    EXPECT_THROW(Option6ClientFqdn(in_buf.begin(), in_buf.end()),
                 InvalidFqdnOptionFlags);
}

// This test verifies that if invalid domain name is used the constructor
// will throw appropriate exception.
TEST(Option6ClientFqdnTest, constructInvalidName) {
    // First, check that constructor does not throw when valid domain name
    // is specified. That way we eliminate the possibility that constructor
    // always throws exception.
    ASSERT_NO_THROW(Option6ClientFqdn(0, "myhost.example.com"));

    // Specify invalid domain name and expect that exception is thrown.
    EXPECT_THROW(Option6ClientFqdn(0, "my...host.example.com"),
                 InvalidFqdnOptionDomainName);
}

// This test verifies that getFlag throws an exception if flag value of 0x3
// is specified.This test does not verify other invalid values, e.g. 0x5,
// 0x6 etc. because conversion of int values which do not belong to the range
// between the lowest and highest enumerator will give an undefined
// result.
TEST(Option6ClientFqdnTest, getFlag) {
    boost::scoped_ptr<Option6ClientFqdn> option;
    ASSERT_NO_THROW(
        option.reset(new Option6ClientFqdn(0, "myhost.example.com"))
    );
    ASSERT_TRUE(option);

    // The 0x3 is a valid enumerator value (even though it is not explicitly
    // included in the Option6ClientFqdn::Flag definition). The getFlag()
    // function should not accept it. Only explicit values are accepted.
    EXPECT_THROW(option->getFlag(static_cast<Option6ClientFqdn::Flag>(0x3)),
                                 InvalidFqdnOptionFlags);
}

// This test verifies that flags can be modified and that incorrect flags
// are rejected.
TEST(Option6ClientFqdnTest, setFlag) {
    // Create option instance. Check that constructor doesn't throw.
    boost::scoped_ptr<Option6ClientFqdn> option;
    ASSERT_NO_THROW(
        option.reset(new Option6ClientFqdn(0, "myhost.example.com"))
    );
    ASSERT_TRUE(option);

    // All flags should be set to 0 initially.
    ASSERT_FALSE(option->getFlag(Option6ClientFqdn::FLAG_N));
    ASSERT_FALSE(option->getFlag(Option6ClientFqdn::FLAG_S));
    ASSERT_FALSE(option->getFlag(Option6ClientFqdn::FLAG_O));

    // Set N = 1
    ASSERT_NO_THROW(option->setFlag(Option6ClientFqdn::FLAG_N, true));
    ASSERT_TRUE(option->getFlag(Option6ClientFqdn::FLAG_N));

    // Set O = 1
    ASSERT_NO_THROW(option->setFlag(Option6ClientFqdn::FLAG_O, true));
    ASSERT_TRUE(option->getFlag(Option6ClientFqdn::FLAG_O));

    // Set S = 1, this should throw exception because S and N must not
    // be set in the same time.
    ASSERT_THROW(option->setFlag(Option6ClientFqdn::FLAG_S, true),
                 InvalidFqdnOptionFlags);

    // Set N = 0
    ASSERT_NO_THROW(option->setFlag(Option6ClientFqdn::FLAG_N, false));
    ASSERT_FALSE(option->getFlag(Option6ClientFqdn::FLAG_N));

    // Set S = 1, this should not result in exception because N has been
    // cleared.
    ASSERT_NO_THROW(option->setFlag(Option6ClientFqdn::FLAG_S, true));
    ASSERT_TRUE(option->getFlag(Option6ClientFqdn::FLAG_S));

    // Set N = 1, this should result in exception because S = 1
    ASSERT_THROW(option->setFlag(Option6ClientFqdn::FLAG_N, true),
                 InvalidFqdnOptionFlags);

    // Set O = 0
    ASSERT_NO_THROW(option->setFlag(Option6ClientFqdn::FLAG_O, false));
    ASSERT_FALSE(option->getFlag(Option6ClientFqdn::FLAG_O));

    // Try out of bounds settings.
    uint8_t flags = 0;
    ASSERT_THROW(option->setFlag(static_cast<Option6ClientFqdn::Flag>(flags),
                                 true),
                 InvalidFqdnOptionFlags);

    flags = 0x14;
    ASSERT_THROW(option->setFlag(static_cast<Option6ClientFqdn::Flag>(flags),
                                 true),
                 InvalidFqdnOptionFlags);
}

// This test verifies that current domain-name can be replaced with a new
// domain-name.
TEST(Option6ClientFqdnTest, setDomainName) {
    boost::scoped_ptr<Option6ClientFqdn> option;
    ASSERT_NO_THROW(
        option.reset(new Option6ClientFqdn(Option6ClientFqdn::FLAG_S,
                                           "myhost.example.com",
                                           Option6ClientFqdn::FULL))
    );
    ASSERT_TRUE(option);
    ASSERT_EQ("myhost.example.com.", option->getDomainName());
    ASSERT_EQ(Option6ClientFqdn::FULL, option->getDomainNameType());

    // Partial domain-name.
    ASSERT_NO_THROW(option->setDomainName("myhost",
                                          Option6ClientFqdn::PARTIAL));
    EXPECT_EQ("myhost", option->getDomainName());
    EXPECT_EQ(Option6ClientFqdn::PARTIAL, option->getDomainNameType());

    // Fully qualified domain-name.
    ASSERT_NO_THROW(option->setDomainName("example.com",
                                          Option6ClientFqdn::FULL));
    EXPECT_EQ("example.com.", option->getDomainName());
    EXPECT_EQ(Option6ClientFqdn::FULL, option->getDomainNameType());

    // Empty domain name (partial). This should be successful.
    ASSERT_NO_THROW(option->setDomainName("", Option6ClientFqdn::PARTIAL));
    EXPECT_TRUE(option->getDomainName().empty());

    // Fully qualified domain-names must not be empty.
    EXPECT_THROW(option->setDomainName("", Option6ClientFqdn::FULL),
                 InvalidFqdnOptionDomainName);
    EXPECT_THROW(option->setDomainName(" ", Option6ClientFqdn::FULL),
                 InvalidFqdnOptionDomainName);
}

// This test verifies that current domain-name can be reset to empty one.
TEST(Option6ClientFqdnTest, resetDomainName) {
    boost::scoped_ptr<Option6ClientFqdn> option;
    ASSERT_NO_THROW(
        option.reset(new Option6ClientFqdn(Option6ClientFqdn::FLAG_S,
                                           "myhost.example.com",
                                           Option6ClientFqdn::FULL))
    );
    ASSERT_TRUE(option);
    ASSERT_EQ("myhost.example.com.", option->getDomainName());
    ASSERT_EQ(Option6ClientFqdn::FULL, option->getDomainNameType());

    // Set the domain-name to empty one.
    ASSERT_NO_THROW(option->resetDomainName());
    EXPECT_TRUE(option->getDomainName().empty());
}

// This test verifies on-wire format of the option is correctly created.
TEST(Option6ClientFqdnTest, pack) {
    // Create option instance. Check that constructor doesn't throw.
    const uint8_t flags = Option6ClientFqdn::FLAG_S;
    boost::scoped_ptr<Option6ClientFqdn> option;
    ASSERT_NO_THROW(
        option.reset(new Option6ClientFqdn(flags, "myhost.example.com"))
    );
    ASSERT_TRUE(option);

    // Prepare on-wire format of the option.
    isc::util::OutputBuffer buf(10);
    ASSERT_NO_THROW(option->pack(buf));

    // Prepare reference data.
    const uint8_t ref_data[] = {
        0, 39, 0, 21,                        // header
        FLAG_S,                              // flags
        6, 109, 121, 104, 111, 115, 116,     // myhost.
        7, 101, 120, 97, 109, 112, 108, 101, // example.
        3, 99, 111, 109, 0                   // com.
    };
    size_t ref_data_size = sizeof(ref_data) / sizeof(ref_data[0]);

    // Check if the buffer has the same length as the reference data,
    // so as they can be compared directly.
    ASSERT_EQ(ref_data_size, buf.getLength());
    EXPECT_EQ(0, memcmp(ref_data, buf.getData(), buf.getLength()));
}

// This test verifies on-wire format of the option with partial domain name
// is correctly created.
TEST(Option6ClientFqdnTest, packPartial) {
    // Create option instance. Check that constructor doesn't throw.
    const uint8_t flags = Option6ClientFqdn::FLAG_S;
    boost::scoped_ptr<Option6ClientFqdn> option;
    ASSERT_NO_THROW(
        option.reset(new Option6ClientFqdn(flags, "myhost",
                                           Option6ClientFqdn::PARTIAL))
    );
    ASSERT_TRUE(option);

    // Prepare on-wire format of the option.
    isc::util::OutputBuffer buf(10);
    ASSERT_NO_THROW(option->pack(buf));

    // Prepare reference data.
    const uint8_t ref_data[] = {
        0, 39, 0, 8,                         // header
        FLAG_S,                              // flags
        6, 109, 121, 104, 111, 115, 116      // myhost
    };
    size_t ref_data_size = sizeof(ref_data) / sizeof(ref_data[0]);

    // Check if the buffer has the same length as the reference data,
    // so as they can be compared directly.
    ASSERT_EQ(ref_data_size, buf.getLength());
    EXPECT_EQ(0, memcmp(ref_data, buf.getData(), buf.getLength()));
}

// This test verifies that on-wire option data holding fully qualified domain
// name is parsed correctly.
TEST(Option6ClientFqdnTest, unpack) {
    // Create option instance. Check that constructor doesn't throw.
    boost::scoped_ptr<Option6ClientFqdn> option;
    ASSERT_NO_THROW(
        option.reset(new Option6ClientFqdn(Option6ClientFqdn::FLAG_O,
                                           "myhost",
                                           Option6ClientFqdn::PARTIAL))
    );
    ASSERT_TRUE(option);
    // Make sure that the parameters have been set correctly. Later in this
    // test we will check that they will be replaced with new values when
    // unpack is called.
    EXPECT_FALSE(option->getFlag(Option6ClientFqdn::FLAG_S));
    EXPECT_FALSE(option->getFlag(Option6ClientFqdn::FLAG_N));
    EXPECT_TRUE(option->getFlag(Option6ClientFqdn::FLAG_O));
    EXPECT_EQ("myhost", option->getDomainName());
    EXPECT_EQ(Option6ClientFqdn::PARTIAL, option->getDomainNameType());

    const uint8_t in_data[] = {
        FLAG_S,                              // flags
        6, 109, 121, 104, 111, 115, 116,     // myhost.
        7, 101, 120, 97, 109, 112, 108, 101, // example.
        3, 99, 111, 109, 0                   // com.
    };
    size_t in_data_size = sizeof(in_data) / sizeof(in_data[0]);
    OptionBuffer in_buf(in_data, in_data + in_data_size);

    // Initialize new values from the on-wire format.
    ASSERT_NO_THROW(option->unpack(in_buf.begin(), in_buf.end()));

    // Check that new values are correct.
    EXPECT_TRUE(option->getFlag(Option6ClientFqdn::FLAG_S));
    EXPECT_FALSE(option->getFlag(Option6ClientFqdn::FLAG_N));
    EXPECT_FALSE(option->getFlag(Option6ClientFqdn::FLAG_O));
    EXPECT_EQ("myhost.example.com.", option->getDomainName());
    EXPECT_EQ(Option6ClientFqdn::FULL, option->getDomainNameType());
}

// This test verifies that on-wire option data holding partial domain name
// is parsed correctly.
TEST(Option6ClientFqdnTest, unpackPartial) {
    // Create option instance. Check that constructor doesn't throw.
    boost::scoped_ptr<Option6ClientFqdn> option;
    ASSERT_NO_THROW(
        option.reset(new Option6ClientFqdn(Option6ClientFqdn::FLAG_O,
                                           "myhost.example.com"))
    );
    ASSERT_TRUE(option);
    // Make sure that the parameters have been set correctly. Later in this
    // test we will check that they will be replaced with new values when
    // unpack is called.
    EXPECT_FALSE(option->getFlag(Option6ClientFqdn::FLAG_S));
    EXPECT_FALSE(option->getFlag(Option6ClientFqdn::FLAG_N));
    EXPECT_TRUE(option->getFlag(Option6ClientFqdn::FLAG_O));
    EXPECT_EQ("myhost.example.com.", option->getDomainName());
    EXPECT_EQ(Option6ClientFqdn::FULL, option->getDomainNameType());

    const uint8_t in_data[] = {
        FLAG_S,                              // flags
        6, 109, 121, 104, 111, 115, 116      // myhost
    };
    size_t in_data_size = sizeof(in_data) / sizeof(in_data[0]);
    OptionBuffer in_buf(in_data, in_data + in_data_size);

    // Initialize new values from the on-wire format.
    ASSERT_NO_THROW(option->unpack(in_buf.begin(), in_buf.end()));

    // Check that new values are correct.
    EXPECT_TRUE(option->getFlag(Option6ClientFqdn::FLAG_S));
    EXPECT_FALSE(option->getFlag(Option6ClientFqdn::FLAG_N));
    EXPECT_FALSE(option->getFlag(Option6ClientFqdn::FLAG_O));
    EXPECT_EQ("myhost", option->getDomainName());
    EXPECT_EQ(Option6ClientFqdn::PARTIAL, option->getDomainNameType());
}

// This test verifies that the empty buffer is rejected when decoding an option
// from on-wire format.
TEST(Option6ClientFqdnTest, unpackTruncated) {
    boost::scoped_ptr<Option6ClientFqdn> option;
    ASSERT_NO_THROW(
        option.reset(new Option6ClientFqdn(Option6ClientFqdn::FLAG_O))
    );
    ASSERT_TRUE(option);

    // Empty buffer is invalid. It should be at least 1 octet long.
    OptionBuffer in_buf;
    EXPECT_THROW(option->unpack(in_buf.begin(), in_buf.end()), OutOfRange);
}

// This test verifies that string representation of the option returned by
// toText method is correctly formatted.
TEST(Option6ClientFqdnTest, toText) {
    // Create option instance. Check that constructor doesn't throw.
    uint8_t flags = Option6ClientFqdn::FLAG_N | Option6ClientFqdn::FLAG_O;
    boost::scoped_ptr<Option6ClientFqdn> option;
    ASSERT_NO_THROW(
        option.reset(new Option6ClientFqdn(flags,
                                           "myhost.example.com"))
    );
    ASSERT_TRUE(option);

    // The base indentation of the option will be set to 2. It should appear
    // as follows.
    std::string ref_string =
        "  type=39(CLIENT_FQDN)\n"
        "  flags:\n"
        "    N=1\n"
        "    O=1\n"
        "    S=0\n"
        "  domain-name='myhost.example.com.' (full)\n";
    const int indent = 2;
    EXPECT_EQ(ref_string, option->toText(indent));

    // Create another option with different parameters:
    // - flags set to 0
    // - domain-name is now partial, not fully qualified
    // Also, remove base indentation.
    flags = 0;
    ASSERT_NO_THROW(
        option.reset(new Option6ClientFqdn(flags, "myhost",
                                           Option6ClientFqdn::PARTIAL))
    );
    ref_string =
        "type=39(CLIENT_FQDN)\n"
        "flags:\n"
        "  N=0\n"
        "  O=0\n"
        "  S=0\n"
        "domain-name='myhost' (partial)\n";
    EXPECT_EQ(ref_string, option->toText());
}

// This test verifies that the correct length of the option in on-wire
// format is returned.
TEST(Option6ClientFqdnTest, len) {
    // Create option instance. Check that constructor doesn't throw.
    boost::scoped_ptr<Option6ClientFqdn> option;
    ASSERT_NO_THROW(
        option.reset(new Option6ClientFqdn(0, "myhost.example.com"))
    );
    ASSERT_TRUE(option);
    // This option comprises a header (4 octets), flag field (1 octet),
    // and wire representation of the domain name (length equal to the
    // length of the string representation of the domain name + 1).
    EXPECT_EQ(25, option->len());

    // Let's check that the size will change when domain name of a different
    // size is used.
    ASSERT_NO_THROW(
        option.reset(new Option6ClientFqdn(0, "example.com"))
    );
    ASSERT_TRUE(option);
    EXPECT_EQ(18, option->len());

    ASSERT_NO_THROW(
        option.reset(new Option6ClientFqdn(0, "myhost",
                                           Option6ClientFqdn::PARTIAL))
    );
    ASSERT_TRUE(option);
    EXPECT_EQ(12, option->len());
}

} // anonymous namespace
