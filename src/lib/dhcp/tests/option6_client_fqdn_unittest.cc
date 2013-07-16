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

class Option6ClientFqdnTest : public ::testing::Test {
public:

    Option6ClientFqdnTest() { }

    virtual ~Option6ClientFqdnTest() { }
};

TEST_F(Option6ClientFqdnTest, ctorInvalidFlags) {
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

// This test verifies that if invalid domain name is used the constructor
// will throw appropriate exception.
TEST_F(Option6ClientFqdnTest, ctorInvalidName) {
    // First, check that constructor does not throw when valid domain name
    // is specified. That way we eliminate the possibility that constructor
    // always throws exception.
    ASSERT_NO_THROW(Option6ClientFqdn(0, "myhost.example.com"));

    // Specify invalid domain name and expect that exception is thrown.
    EXPECT_THROW(Option6ClientFqdn(0, "my...host.example.com"),
                 InvalidFqdnOptionDomainName);
}

// This test verifies that getFlag throws an exception if flag value of 0x3
// is specified.TThis test does not verify other invalid values, e.g. 0x5,
// 0x6 etc. because conversion of int values which do not belong to the range
// between the lowest and highest enumerator will give an undefined
// result.
TEST_F(Option6ClientFqdnTest, getFlag) {
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
TEST_F(Option6ClientFqdnTest, setFlag) {
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

// This test verifies on-wire format of the option is correctly created.
TEST_F(Option6ClientFqdnTest, pack) {
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
        Option6ClientFqdn::FLAG_S,           // flags
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
TEST_F(Option6ClientFqdnTest, packPartial) {
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
        Option6ClientFqdn::FLAG_S,           // flags
        6, 109, 121, 104, 111, 115, 116      // myhost
    };
    size_t ref_data_size = sizeof(ref_data) / sizeof(ref_data[0]);

    // Check if the buffer has the same length as the reference data,
    // so as they can be compared directly.
    ASSERT_EQ(ref_data_size, buf.getLength());
    EXPECT_EQ(0, memcmp(ref_data, buf.getData(), buf.getLength()));
}

// This test verifies that the correct length of the option in on-wire
// format is returned.
TEST_F(Option6ClientFqdnTest, len) {
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
