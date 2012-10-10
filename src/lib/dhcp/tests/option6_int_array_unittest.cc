// Copyright (C) 2012 Internet Systems Consortium, Inc. ("ISC")
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
#include <dhcp/option6_int_array.h>
#include <dhcp/option6_iaaddr.h>
#include <util/buffer.h>

#include <boost/pointer_cast.hpp>
#include <gtest/gtest.h>

using namespace std;
using namespace isc;
using namespace isc::dhcp;
using namespace isc::asiolink;
using namespace isc::util;

namespace {

/// @brief Option6IntArray test class.
class Option6IntArrayTest : public ::testing::Test {
public:
    /// @brief Constructor.
    ///
    /// Initializes the option buffer with some data.
    Option6IntArrayTest(): buf_(255), out_buf_(255) {
        for (int i = 0; i < 255; i++) {
            buf_[i] = 255 - i;
        }
    }

    OptionBuffer buf_;     ///< Option buffer
    OutputBuffer out_buf_; ///< Output buffer
};

/// @todo: below, there is a bunch of tests for options that
/// convey unsigned values. We should maybe extend these tests for
/// signed types too.

TEST_F(Option6IntArrayTest, useInvalidType) {
    const uint16_t opt_code = 80;
    EXPECT_THROW(
        boost::scoped_ptr<
            Option6IntArray<bool> >(new Option6IntArray<bool>(opt_code, OptionBuffer(5))),
        InvalidDataType
    );

    EXPECT_THROW(
        boost::scoped_ptr<
            Option6IntArray<int64_t> >(new Option6IntArray<int64_t>(opt_code,
                                                                    OptionBuffer(10))),
        InvalidDataType
    );

}

TEST_F(Option6IntArrayTest, bufferToUint8) {
    // Create option that conveys array of multiple uint8_t values.
    // In fact there is no need to use this template class for array
    // of uint8_t values because Option class is sufficient - it
    // returns the buffer which is actually the array of uint8_t.
    // However, since we allow using uint8_t types with this template
    // class we have to test it here.
    boost::shared_ptr<Option6IntArray<uint8_t> > opt;
    const int opt_len = 10;
    const uint16_t opt_code = 80;
    // Constructor may throw in case provided buffer is too short.
    ASSERT_NO_THROW(
        opt = boost::shared_ptr<
            Option6IntArray<uint8_t> >(new Option6IntArray<uint8_t>(opt_code, buf_.begin(),
                                                                    buf_.begin() + opt_len))
    );

    EXPECT_EQ(Option::V6, opt->getUniverse());
    EXPECT_EQ(opt_code, opt->getType());
    // Option should return the same value that we initialized the first
    // byte of the buffer with.
    std::vector<uint8_t> values = opt->getValues();
    ASSERT_EQ(opt_len, values.size());
    EXPECT_TRUE(std::equal(buf_.begin(), buf_.begin() + opt_len, values.begin()));

    // test for pack()
    opt->pack(out_buf_);

    // Data length is 10 bytes.
    EXPECT_EQ(10, opt->len() - opt->getHeaderLen());
    EXPECT_EQ(opt_code, opt->getType());
    // The total length is 10 bytes for data and 4 bytes for header.
    ASSERT_EQ(14, out_buf_.getLength());

    // Check if pack worked properly:
    InputBuffer out(out_buf_.getData(), out_buf_.getLength());
    // if option type is correct
    EXPECT_EQ(opt_code, out.readUint16());
    // if option length is correct
    EXPECT_EQ(10, out.readUint16());
    // if data is correct
    std::vector<uint8_t> out_data;
    ASSERT_NO_THROW(out.readVector(out_data, opt_len));
    ASSERT_EQ(opt_len, out_data.size());
    EXPECT_TRUE(std::equal(buf_.begin(), buf_.begin() + opt_len, out_data.begin()));;
}

TEST_F(Option6IntArrayTest, bufferToUint16) {
    // Create option that conveys array of multiple uint16_t values.
    boost::shared_ptr<Option6IntArray<uint16_t> > opt;
    const int opt_len = 20;
    const uint16_t opt_code = 81;
    // Constructor may throw in case provided buffer is too short.
    ASSERT_NO_THROW(
        opt = boost::shared_ptr<
            Option6IntArray<uint16_t> >(new Option6IntArray<uint16_t>(opt_code, buf_.begin(),
                                                                      buf_.begin() + opt_len))
    );

    EXPECT_EQ(Option::V6, opt->getUniverse());
    EXPECT_EQ(opt_code, opt->getType());
    // Option should return vector of uint16_t values which should be
    // constructed from the buffer we provided.
    std::vector<uint16_t> values = opt->getValues();
    // Let's pack the values back into some uint8_t buffer to compare
    // it later with the reference data.
    std::vector<uint8_t> values_buf;
    for (int i = 0; i < values.size(); ++i) {
        // Values have been read from the buffer in network
        // byte order. We put them back in the same order here.
        values_buf.push_back(values[i] >> 8);
        values_buf.push_back(values[i] & 0xFF);
    }
    ASSERT_EQ(opt_len, values_buf.size());
    EXPECT_TRUE(std::equal(buf_.begin(), buf_.begin() + opt_len, values_buf.begin()));

    // Test for pack()
    opt->pack(out_buf_);

    // Data length is 20 bytes.
    EXPECT_EQ(20, opt->len() - opt->getHeaderLen());
    EXPECT_EQ(opt_code, opt->getType());
    // The total length is 20 bytes for data and 4 bytes for header.
    ASSERT_EQ(24, out_buf_.getLength());

    // Check if pack worked properly:
    InputBuffer out(out_buf_.getData(), out_buf_.getLength());
    // if option type is correct
    EXPECT_EQ(opt_code, out.readUint16());
    // if option length is correct
    EXPECT_EQ(20, out.readUint16());
    // if data is correct
    std::vector<uint8_t> out_data;
    ASSERT_NO_THROW(out.readVector(out_data, opt_len));
    ASSERT_EQ(opt_len, out_data.size());
    EXPECT_TRUE(std::equal(buf_.begin(), buf_.begin() + opt_len, out_data.begin()));;
}

TEST_F(Option6IntArrayTest, bufferToUint32) {
    // Create option that conveys array of multiple uint16_t values.
    boost::shared_ptr<Option6IntArray<uint32_t> > opt;
    const int opt_len = 40;
    const uint16_t opt_code = 82;
    // Constructor may throw in case provided buffer is too short.
    ASSERT_NO_THROW(
        opt = boost::shared_ptr<
            Option6IntArray<uint32_t> >(new Option6IntArray<uint32_t>(opt_code, buf_.begin(),
                                                                      buf_.begin() + opt_len))
    );

    EXPECT_EQ(Option::V6, opt->getUniverse());
    EXPECT_EQ(opt_code, opt->getType());
    // Option should return vector of uint32_t values which should be
    // constructed from the buffer we provided.
    std::vector<uint32_t> values = opt->getValues();
    // Let's pack the values back into some uint8_t buffer to compare
    // it later with the reference data.
    std::vector<uint8_t> values_buf;
    for (int i = 0; i < values.size(); ++i) {
        // Values have been read from the buffer in network
        // byte order. We put them back in the same order here.
        values_buf.push_back(values[i] >> 24);
        values_buf.push_back(values[i] >> 16 & 0xFF);
        values_buf.push_back(values[i] >> 8 & 0xFF);
        values_buf.push_back(values[i] & 0xFF);
    }
    ASSERT_EQ(opt_len, values_buf.size());
    EXPECT_TRUE(std::equal(buf_.begin(), buf_.begin() + opt_len, values_buf.begin()));

    // Test for pack()
    opt->pack(out_buf_);

    // Data length is 40 bytes.
    EXPECT_EQ(40, opt->len() - opt->getHeaderLen());
    EXPECT_EQ(opt_code, opt->getType());
    // The total length is 40 bytes for data and 4 bytes for header.
    ASSERT_EQ(44, out_buf_.getLength());

    // Check if pack worked properly:
    InputBuffer out(out_buf_.getData(), out_buf_.getLength());
    // if option type is correct
    EXPECT_EQ(opt_code, out.readUint16());
    // if option length is correct
    EXPECT_EQ(40, out.readUint16());
    // if data is correct
    std::vector<uint8_t> out_data;
    ASSERT_NO_THROW(out.readVector(out_data, opt_len));
    ASSERT_EQ(opt_len, out_data.size());
    EXPECT_TRUE(std::equal(buf_.begin(), buf_.begin() + opt_len, out_data.begin()));;
}


TEST_F(Option6IntArrayTest, setValuesUint8) {
    const uint16_t opt_code = 100;
    // Create option with empty vector of values.
    boost::shared_ptr<Option6IntArray<uint8_t> > opt(new Option6IntArray<uint8_t>(opt_code));
    // Initialize vector with some data and pass to the option.
    std::vector<uint8_t> values;
    for (int i = 0; i < 10; ++i) {
        values.push_back(255 - i);
    }
    opt->setValues(values);

    // Check if universe, option type and data was set correctly.
    EXPECT_EQ(Option::V6, opt->getUniverse());
    EXPECT_EQ(opt_code, opt->getType());
    std::vector<uint8_t> returned_values = opt->getValues();
    EXPECT_TRUE(std::equal(values.begin(), values.end(), returned_values.begin()));
}

TEST_F(Option6IntArrayTest, setValuesUint16) {
    const uint16_t opt_code = 101;
    // Create option with empty vector of values.
    boost::shared_ptr<Option6IntArray<uint16_t> > opt(new Option6IntArray<uint16_t>(opt_code));
    // Initialize vector with some data and pass to the option.
    std::vector<uint16_t> values;
    for (int i = 0; i < 10; ++i) {
        values.push_back(0xFFFF - i);
    }
    opt->setValues(values);

    // Check if universe, option type and data was set correctly.
    EXPECT_EQ(Option::V6, opt->getUniverse());
    EXPECT_EQ(opt_code, opt->getType());
    std::vector<uint16_t> returned_values = opt->getValues();
    EXPECT_TRUE(std::equal(values.begin(), values.end(), returned_values.begin()));
}

TEST_F(Option6IntArrayTest, setValuesUint32) {
    const uint32_t opt_code = 101;
    // Create option with empty vector of values.
    boost::shared_ptr<Option6IntArray<uint32_t> > opt(new Option6IntArray<uint32_t>(opt_code));
    // Initialize vector with some data and pass to the option.
    std::vector<uint32_t> values;
    for (int i = 0; i < 10; ++i) {
        values.push_back(0xFFFFFFFF - i);
    }
    opt->setValues(values);

    // Check if universe, option type and data was set correctly.
    EXPECT_EQ(Option::V6, opt->getUniverse());
    EXPECT_EQ(opt_code, opt->getType());
    std::vector<uint32_t> returned_values = opt->getValues();
    EXPECT_TRUE(std::equal(values.begin(), values.end(), returned_values.begin()));
}

} // anonymous namespace
