// Copyright (C) 2012, 2015 Internet Systems Consortium, Inc. ("ISC")
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

#include <dhcp/dhcp6.h>
#include <dhcp/option.h>
#include <dhcp/option6_iaaddr.h>
#include <dhcp/option_int.h>
#include <util/buffer.h>

#include <boost/pointer_cast.hpp>
#include <boost/scoped_ptr.hpp>
#include <gtest/gtest.h>

using namespace std;
using namespace isc;
using namespace isc::dhcp;
using namespace isc::asiolink;
using namespace isc::util;

namespace {

/// Option code being used in many test cases.
const uint16_t TEST_OPT_CODE = 232;

/// @brief OptionInt test class.
class OptionIntTest : public ::testing::Test {
public:
    /// @brief Constructor.
    ///
    /// Initializes the option buffer with some data.
    OptionIntTest(): buf_(255), out_buf_(255) {
        for (unsigned i = 0; i < 255; i++) {
            buf_[i] = 255 - i;
        }
    }

    /// @brief Basic test for int8 and uint8 types.
    ///
    /// @note this function does not perform type check. Make
    /// sure that only int8_t or uint8_t type is used.
    ///
    /// @param u universe (V4 or V6).
    /// @tparam T int8_t or uint8_t.
    template<typename T>
    void basicTest8(const Option::Universe u) {
        // Create option that conveys single 8 bit integer value.
        boost::shared_ptr<OptionInt<T> > opt;
        // Initialize buffer with this value.
        buf_[0] = 0xa1;
        // Constructor may throw in case provided buffer is too short.
        ASSERT_NO_THROW(
            opt = boost::shared_ptr<OptionInt<T> >(new OptionInt<T>(u,
                                                                    TEST_OPT_CODE,
                                                                    buf_.begin(),
                                                                    buf_.begin() + 1))
        );

        EXPECT_EQ(u, opt->getUniverse());
        EXPECT_EQ(TEST_OPT_CODE, opt->getType());
        // Option should return the same value that we initialized the first
        // byte of the buffer with.
        EXPECT_EQ(static_cast<T>(0xa1), opt->getValue());

        // test for pack()
        opt->pack(out_buf_);

        // Data length is 1 byte.
        EXPECT_EQ(1, opt->len() - opt->getHeaderLen());
        EXPECT_EQ(TEST_OPT_CODE, opt->getType());
        // The total length is 1 byte for data and 2 bytes or 4 bytes
        // for option code and option length.
        if (u == Option::V4) {
            EXPECT_EQ(3, out_buf_.getLength());
        } else {
            EXPECT_EQ(5, out_buf_.getLength());
        }

        // Check if pack worked properly:
        InputBuffer out(out_buf_.getData(), out_buf_.getLength());
        if (u == Option::V4) {
            // if option type is correct
            EXPECT_EQ(TEST_OPT_CODE, out.readUint8());
            // if option length is correct
            EXPECT_EQ(1, out.readUint8());
        } else {
            // if option type is correct
            EXPECT_EQ(TEST_OPT_CODE, out.readUint16());
            // if option length is correct
            EXPECT_EQ(1, out.readUint16());
        }
        // if data is correct
        EXPECT_EQ(0xa1, out.readUint8() );
    }

    /// @brief Basic test for int16 and uint16 types.
    ///
    /// @note this function does not perform type check. Make
    /// sure that only int16_t or uint16_t type is used.
    ///
    /// @param u universe (V4 or V6)
    /// @tparam T int16_t or uint16_t.
    template<typename T>
    void basicTest16(const Option::Universe u) {
        // Create option that conveys single 16-bit integer value.
        boost::shared_ptr<OptionInt<T> > opt;
        // Initialize buffer with uint16_t value.
        buf_[0] = 0xa1;
        buf_[1] = 0xa2;
        // Constructor may throw in case provided buffer is too short.
        ASSERT_NO_THROW(
            opt = boost::shared_ptr<OptionInt<T> >(new OptionInt<T>(u,
                                                                    TEST_OPT_CODE,
                                                                    buf_.begin(),
                                                                    buf_.begin() + 2))
        );

        EXPECT_EQ(u, opt->getUniverse());
        EXPECT_EQ(TEST_OPT_CODE, opt->getType());
        // Option should return the value equal to the contents of first
        // and second byte of the buffer.
        EXPECT_EQ(static_cast<T>(0xa1a2), opt->getValue());

        // Test for pack()
        opt->pack(out_buf_);

        // Data length is 2 bytes.
        EXPECT_EQ(2, opt->len() - opt->getHeaderLen());
        EXPECT_EQ(TEST_OPT_CODE, opt->getType());
        // The total length is 2 bytes for data and 2 or 4 bytes for aheader.
        if (u == Option::V4) {
            EXPECT_EQ(4, out_buf_.getLength());
        } else {
            EXPECT_EQ(6, out_buf_.getLength());
        }

        // Check if pack worked properly:
        InputBuffer out(out_buf_.getData(), out_buf_.getLength());
        if (u == Option::V4) {
            // if option type is correct
            EXPECT_EQ(TEST_OPT_CODE, out.readUint8());
            // if option length is correct
            EXPECT_EQ(2, out.readUint8());
        } else {
            // if option type is correct
            EXPECT_EQ(TEST_OPT_CODE, out.readUint16());
            // if option length is correct
            EXPECT_EQ(2, out.readUint16());
        }
        // if data is correct
        EXPECT_EQ(0xa1a2, out.readUint16() );
    }

    /// @brief Basic test for int32 and uint32 types.
    ///
    /// @note this function does not perform type check. Make
    /// sure that only int32_t or uint32_t type is used.
    ///
    /// @param u universe (V4 or V6).
    /// @tparam T int32_t or uint32_t.
    template<typename T>
    void basicTest32(const Option::Universe u) {
        // Create option that conveys single 32-bit integer value.
        boost::shared_ptr<OptionInt<T> > opt;
        // Initialize buffer with 32-bit integer value.
        buf_[0] = 0xa1;
        buf_[1] = 0xa2;
        buf_[2] = 0xa3;
        buf_[3] = 0xa4;
        // Constructor may throw in case provided buffer is too short.
        ASSERT_NO_THROW(
            opt = boost::shared_ptr<OptionInt<T> >(new OptionInt<T>(u,
                                                                    TEST_OPT_CODE,
                                                                    buf_.begin(),
                                                                    buf_.begin() + 4))
        );

        EXPECT_EQ(u, opt->getUniverse());
        EXPECT_EQ(TEST_OPT_CODE, opt->getType());
        // Option should return the value equal to the value made of
        // first 4 bytes of the buffer.
        EXPECT_EQ(static_cast<T>(0xa1a2a3a4), opt->getValue());

        // Test for pack()
        opt->pack(out_buf_);

        // Data length is 4 bytes.
        EXPECT_EQ(4, opt->len() - opt->getHeaderLen());
        EXPECT_EQ(TEST_OPT_CODE, opt->getType());
        // The total length is 4 bytes for data and 2 or 4 bytes for a header.
        if (u == Option::V4) {
            EXPECT_EQ(6, out_buf_.getLength());
        } else {
            EXPECT_EQ(8, out_buf_.getLength());
        }

        // Check if pack worked properly:
        InputBuffer out(out_buf_.getData(), out_buf_.getLength());
        if (u == Option::V4) {
            // if option type is correct
            EXPECT_EQ(TEST_OPT_CODE, out.readUint8());
            // if option length is correct
            EXPECT_EQ(4, out.readUint8());
        } else {
            // if option type is correct
            EXPECT_EQ(TEST_OPT_CODE, out.readUint16());
            // if option length is correct
            EXPECT_EQ(4, out.readUint16());
        }
        // if data is correct
        EXPECT_EQ(0xa1a2a3a4, out.readUint32());
    }

    OptionBuffer buf_;     ///< Option buffer
    OutputBuffer out_buf_; ///< Output buffer
};

/// @todo: below, there is a bunch of tests for options that
/// convey unsigned value. We should maybe extend these tests for
/// signed types too.

TEST_F(OptionIntTest, useInvalidType) {
    EXPECT_THROW(
        boost::scoped_ptr<OptionInt<bool> >(new OptionInt<bool>(Option::V6,
                                                                D6O_ELAPSED_TIME, 10)),
        InvalidDataType
    );

    EXPECT_THROW(
        boost::scoped_ptr<OptionInt<int64_t> >(new OptionInt<int64_t>(Option::V6,
                                                                      D6O_ELAPSED_TIME, 10)),
        InvalidDataType
    );

}

TEST_F(OptionIntTest, basicUint8V4) {
    basicTest8<uint8_t>(Option::V4);
}

TEST_F(OptionIntTest, basicUint8V6) {
    basicTest8<uint8_t>(Option::V6);
}

TEST_F(OptionIntTest, basicUint16V4) {
    basicTest16<uint16_t>(Option::V4);
}

TEST_F(OptionIntTest, basicUint16V6) {
    basicTest16<uint16_t>(Option::V6);
}

TEST_F(OptionIntTest, basicUint32V4) {
    basicTest32<uint32_t>(Option::V4);
}

TEST_F(OptionIntTest, basicUint32V6) {
    basicTest32<uint32_t>(Option::V6);
}

TEST_F(OptionIntTest, basicInt8V4) {
    basicTest8<int8_t>(Option::V4);
}

TEST_F(OptionIntTest, basicInt8V6) {
    basicTest8<int8_t>(Option::V6);
}

TEST_F(OptionIntTest, basicInt16V4) {
    basicTest16<int16_t>(Option::V4);
}

TEST_F(OptionIntTest, basicInt16V6) {
    basicTest16<int16_t>(Option::V6);
}

TEST_F(OptionIntTest, basicInt32V4) {
    basicTest32<int32_t>(Option::V4);
}

TEST_F(OptionIntTest, basicInt32V6) {
    basicTest32<int32_t>(Option::V6);
}

TEST_F(OptionIntTest, setValueUint8) {
    boost::shared_ptr<OptionInt<uint8_t> > opt(new OptionInt<uint8_t>(Option::V6,
                                                                      D6O_PREFERENCE, 123));
    // Check if constructor initialized the option value correctly.
    EXPECT_EQ(123, opt->getValue());
    // Override the value.
    opt->setValue(111);

    EXPECT_EQ(Option::V6, opt->getUniverse());
    EXPECT_EQ(D6O_PREFERENCE, opt->getType());
    // Check if the value has been overriden.
    EXPECT_EQ(111, opt->getValue());
}

TEST_F(OptionIntTest, setValueInt8) {
    boost::shared_ptr<OptionInt<int8_t> > opt(new OptionInt<int8_t>(Option::V6,
                                                                    D6O_PREFERENCE, -123));
    // Check if constructor initialized the option value correctly.
    EXPECT_EQ(-123, opt->getValue());
    // Override the value.
    opt->setValue(-111);

    EXPECT_EQ(Option::V6, opt->getUniverse());
    EXPECT_EQ(D6O_PREFERENCE, opt->getType());
    // Check if the value has been overriden.
    EXPECT_EQ(-111, opt->getValue());
}


TEST_F(OptionIntTest, setValueUint16) {
    boost::shared_ptr<OptionInt<uint16_t> > opt(new OptionInt<uint16_t>(Option::V6,
                                                                        D6O_ELAPSED_TIME, 123));
    // Check if constructor initialized the option value correctly.
    EXPECT_EQ(123, opt->getValue());
    // Override the value.
    opt->setValue(0x0102);

    EXPECT_EQ(Option::V6, opt->getUniverse());
    EXPECT_EQ(D6O_ELAPSED_TIME, opt->getType());
    // Check if the value has been overriden.
    EXPECT_EQ(0x0102, opt->getValue());
}

TEST_F(OptionIntTest, setValueInt16) {
    boost::shared_ptr<OptionInt<int16_t> > opt(new OptionInt<int16_t>(Option::V6,
                                                                      D6O_ELAPSED_TIME, -16500));
    // Check if constructor initialized the option value correctly.
    EXPECT_EQ(-16500, opt->getValue());
    // Override the value.
    opt->setValue(-20100);

    EXPECT_EQ(Option::V6, opt->getUniverse());
    EXPECT_EQ(D6O_ELAPSED_TIME, opt->getType());
    // Check if the value has been overriden.
    EXPECT_EQ(-20100, opt->getValue());
}

TEST_F(OptionIntTest, setValueUint32) {
    boost::shared_ptr<OptionInt<uint32_t> > opt(new OptionInt<uint32_t>(Option::V6,
                                                                        D6O_CLT_TIME, 123));
    // Check if constructor initialized the option value correctly.
    EXPECT_EQ(123, opt->getValue());
    // Override the value.
    opt->setValue(0x01020304);

    EXPECT_EQ(Option::V6, opt->getUniverse());
    EXPECT_EQ(D6O_CLT_TIME, opt->getType());
    // Check if the value has been overriden.
    EXPECT_EQ(0x01020304, opt->getValue());
}

TEST_F(OptionIntTest, setValueInt32) {
    boost::shared_ptr<OptionInt<int32_t> > opt(new OptionInt<int32_t>(Option::V6,
                                                                      D6O_CLT_TIME, -120100));
    // Check if constructor initialized the option value correctly.
    EXPECT_EQ(-120100, opt->getValue());
    // Override the value.
    opt->setValue(-125000);

    EXPECT_EQ(Option::V6, opt->getUniverse());
    EXPECT_EQ(D6O_CLT_TIME, opt->getType());
    // Check if the value has been overriden.
    EXPECT_EQ(-125000, opt->getValue());
}

TEST_F(OptionIntTest, packSuboptions4) {
    boost::shared_ptr<OptionInt<uint16_t> > opt(new OptionInt<uint16_t>(Option::V4,
                                                                        TEST_OPT_CODE,
                                                                        0x0102));
    // Add sub option with some 4 bytes of data (each byte set to 1)
    OptionPtr sub1(new Option(Option::V4, TEST_OPT_CODE + 1, OptionBuffer(4, 1)));
    // Add sub option with some 5 bytes of data (each byte set to 2)
    OptionPtr sub2(new Option(Option::V4, TEST_OPT_CODE + 2, OptionBuffer(5, 2)));

    // Add suboptions.
    opt->addOption(sub1);
    opt->addOption(sub2);

    // Prepare reference data: option + suoptions in wire format.
    uint8_t expected[] = {
        TEST_OPT_CODE, 15, // option header
        0x01, 0x02,        // data, uint16_t value = 0x0102
        TEST_OPT_CODE + 1, 0x04, 0x01, 0x01, 0x01, 0x01, // sub1
        TEST_OPT_CODE + 2, 0x05, 0x02, 0x02, 0x02, 0x02, 0x02 // sub2
    };

    // Create on-wire format of option and suboptions.
    opt->pack(out_buf_);
    // Compare the on-wire data with the reference buffer.
    ASSERT_EQ(sizeof(expected), out_buf_.getLength());
    EXPECT_EQ(0, memcmp(out_buf_.getData(), expected, sizeof(expected)));
}

TEST_F(OptionIntTest, packSuboptions6) {
    // option code is really uint16_t, but using uint8_t
    // for easier conversion to uint8_t array.
    uint8_t opt_code = 80;

    boost::shared_ptr<OptionInt<uint32_t> > opt(new OptionInt<uint32_t>(Option::V6,
                                                                        opt_code, 0x01020304));
    OptionPtr sub1(new Option(Option::V6, 0xcafe));

    boost::shared_ptr<Option6IAAddr> addr1(
        new Option6IAAddr(D6O_IAADDR, IOAddress("2001:db8:1234:5678::abcd"), 0x5000, 0x7000));

    opt->addOption(sub1);
    opt->addOption(addr1);

    ASSERT_EQ(28, addr1->len());
    ASSERT_EQ(4, sub1->len());
    ASSERT_EQ(40, opt->len());

    uint8_t expected[] = {
        0, opt_code, // type
        0, 36, // length
        0x01, 0x02, 0x03, 0x04, // uint32_t value

        // iaaddr suboption
        D6O_IAADDR / 256, D6O_IAADDR % 256, // type
        0, 24, // len
        0x20, 0x01, 0xd, 0xb8, 0x12,0x34, 0x56, 0x78,
        0, 0, 0, 0, 0, 0, 0xab, 0xcd, // IP address
        0, 0, 0x50, 0, // preferred-lifetime
        0, 0, 0x70, 0, // valid-lifetime

        // suboption
        0xca, 0xfe, // type
        0, 0 // len
    };

    // Create on-wire format of option and suboptions.
    opt->pack(out_buf_);
    // Compare the on-wire data with the reference buffer.
    ASSERT_EQ(40, out_buf_.getLength());
    EXPECT_EQ(0, memcmp(out_buf_.getData(), expected, 40));
}

TEST_F(OptionIntTest, unpackSuboptions4) {
    // Prepare reference data.
    const uint8_t expected[] = {
        TEST_OPT_CODE, 0x0A, // option code and length
        0x01, 0x02, 0x03, 0x04, // data, uint32_t value = 0x01020304
        TEST_OPT_CODE + 1, 0x4, 0x01, 0x01, 0x01, 0x01 // suboption
    };
    // Make sure that the buffer size is sufficient to copy the
    // elements from the array.
    ASSERT_GE(buf_.size(), sizeof(expected));
    // Copy the data to a vector so as we can pass it to the
    // OptionInt's constructor.
    memcpy(&buf_[0], expected, sizeof(expected));

    // Create an option.
    boost::shared_ptr<OptionInt<uint32_t> > opt;
    EXPECT_NO_THROW(
        opt = boost::shared_ptr<
            OptionInt<uint32_t> >(new OptionInt<uint32_t>(Option::V4, TEST_OPT_CODE,
                                                          buf_.begin() + 2,
                                                          buf_.begin() + sizeof(expected)));
    );
    ASSERT_TRUE(opt);

    // Verify that it has expected type and data.
    EXPECT_EQ(TEST_OPT_CODE, opt->getType());
    EXPECT_EQ(0x01020304, opt->getValue());

    // Expect that there is the sub option with the particular
    // option code added.
    OptionPtr subopt = opt->getOption(TEST_OPT_CODE + 1);
    ASSERT_TRUE(subopt);
    // Check that this option has correct universe and code.
    EXPECT_EQ(Option::V4, subopt->getUniverse());
    EXPECT_EQ(TEST_OPT_CODE + 1, subopt->getType());
    // Check the sub option's data.
    OptionBuffer subopt_buf = subopt->getData();
    ASSERT_EQ(4, subopt_buf.size());
    // The data in the input buffer starts at offset 8.
    EXPECT_TRUE(std::equal(subopt_buf.begin(), subopt_buf.end(), buf_.begin() + 8));
}

TEST_F(OptionIntTest, unpackSuboptions6) {
    // option code is really uint16_t, but using uint8_t
    // for easier conversion to uint8_t array.
    const uint8_t opt_code = 80;
    // Prepare reference data.
    uint8_t expected[] = {
        0, opt_code, // type
        0, 34, // length
        0x01, 0x02, // uint16_t value

        // iaaddr suboption
        D6O_IAADDR / 256, D6O_IAADDR % 256, // type
        0, 24, // len
        0x20, 0x01, 0xd, 0xb8, 0x12,0x34, 0x56, 0x78,
        0, 0, 0, 0, 0, 0, 0xab, 0xcd, // IP address
        0, 0, 0x50, 0, // preferred-lifetime
        0, 0, 0x70, 0, // valid-lifetime

        // suboption
        0xca, 0xfe, // type
        0, 0 // len
    };
    ASSERT_EQ(38, sizeof(expected));

    // Make sure that the buffer's size is sufficient to
    // copy the elements from the array.
    ASSERT_GE(buf_.size(), sizeof(expected));
    memcpy(&buf_[0], expected, sizeof(expected));

    boost::shared_ptr<OptionInt<uint16_t> > opt;
    EXPECT_NO_THROW(
        opt = boost::shared_ptr<
            OptionInt<uint16_t> >(new OptionInt<uint16_t>(Option::V6, opt_code,
                                                          buf_.begin() + 4,
                                                          buf_.begin() + sizeof(expected)));
    );
    ASSERT_TRUE(opt);

    EXPECT_EQ(opt_code, opt->getType());
    EXPECT_EQ(0x0102, opt->getValue());

    // Checks for address option
    OptionPtr subopt = opt->getOption(D6O_IAADDR);
    ASSERT_TRUE(subopt);
    boost::shared_ptr<Option6IAAddr> addr(boost::dynamic_pointer_cast<Option6IAAddr>(subopt));
    ASSERT_TRUE(addr);

    EXPECT_EQ(D6O_IAADDR, addr->getType());
    EXPECT_EQ(28, addr->len());
    EXPECT_EQ(0x5000, addr->getPreferred());
    EXPECT_EQ(0x7000, addr->getValid());
    EXPECT_EQ("2001:db8:1234:5678::abcd", addr->getAddress().toText());

    // Checks for dummy option
    subopt = opt->getOption(0xcafe);
    ASSERT_TRUE(subopt); // should be non-NULL

    EXPECT_EQ(0xcafe, subopt->getType());
    EXPECT_EQ(4, subopt->len());
    // There should be no data at all
    EXPECT_EQ(0, subopt->getData().size());

    // Try to get non-existent option.
    subopt = opt->getOption(1);
    // Expecting NULL which means that option does not exist.
    ASSERT_FALSE(subopt);
}

// This test checks that the toText function returns the option in the
// textual format correctly.
TEST_F(OptionIntTest, toText) {
    OptionUint32 option(Option::V4, 128, 345678);
    EXPECT_EQ("type=128, len=004: 345678 (uint32)", option.toText());

    option.addOption(OptionPtr(new OptionUint16(Option::V4, 1, 234)));
    option.addOption(OptionPtr(new OptionUint8(Option::V4, 3, 22)));
    EXPECT_EQ("type=128, len=011: 345678 (uint32),\n"
              "options:\n"
              "  type=001, len=002: 234 (uint16)\n"
              "  type=003, len=001: 22 (uint8)",
              option.toText());
}

} // anonymous namespace
