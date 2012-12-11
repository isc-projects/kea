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
#include <dhcp/option6_iaaddr.h>
#include <dhcp/option_int_array.h>
#include <util/buffer.h>

#include <boost/pointer_cast.hpp>
#include <gtest/gtest.h>

using namespace std;
using namespace isc;
using namespace isc::dhcp;
using namespace isc::asiolink;
using namespace isc::util;

namespace {

/// @brief OptionIntArray test class.
class OptionIntArrayTest : public ::testing::Test {
public:
    /// @brief Constructor.
    ///
    /// Initializes the option buffer with some data.
    OptionIntArrayTest(): buf_(255), out_buf_(255) {
        for (int i = 0; i < 255; i++) {
            buf_[i] = 255 - i;
        }
    }

    /// @brief Test parsing buffer into array of int8_t or uint8_t values.
    ///
    /// @warning this function does not perform type check. Make
    /// sure that only int8_t or uint8_t type is used.
    ///
    /// @param u universe (v4 or V6).
    /// @tparam T int8_t or uint8_t.
    template<typename T>
    void bufferToIntTest8(const Option::Universe u) {
        // Create option that conveys array of multiple uint8_t or int8_t values.
        // In fact there is no need to use this template class for array
        // of uint8_t values because Option class is sufficient - it
        // returns the buffer which is actually the array of uint8_t.
        // However, since we allow using uint8_t types with this template
        // class we have to test it here.
        boost::shared_ptr<OptionIntArray<T> > opt;
        const int opt_len = 10;
        const uint16_t opt_code = 80;

        // Constructor throws exception if provided buffer is empty.
        EXPECT_THROW(
            OptionIntArray<T>(u, opt_code, buf_.begin(), buf_.begin()),
            isc::OutOfRange
        );

        // Provided buffer is not empty so it should not throw exception.
        ASSERT_NO_THROW(
            opt = boost::shared_ptr<
                OptionIntArray<T> >(new OptionIntArray<T>(u, opt_code, buf_.begin(),
                                                          buf_.begin() + opt_len))
        );

        EXPECT_EQ(Option::V6, opt->getUniverse());
        EXPECT_EQ(opt_code, opt->getType());
        // Option should return the collection of int8_t or uint8_t values that
        // we can match with the buffer we used to create the option.
        std::vector<T> values = opt->getValues();
        // We need to copy values from the buffer to apply sign if signed
        // type is used.
        std::vector<T> reference_values;
        for (int i = 0; i < opt_len; ++i) {
            // Values have been read from the buffer in network
            // byte order. We put them back in the same order here.
            reference_values.push_back(static_cast<T>(buf_[i]));
        }

        // Compare the values against the reference buffer.
        ASSERT_EQ(opt_len, values.size());
        EXPECT_TRUE(std::equal(reference_values.begin(), reference_values.begin()
                               + opt_len, values.begin()));

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

    /// @brief Test parsing buffer into array of int16_t or uint16_t values.
    ///
    /// @warning this function does not perform type check. Make
    /// sure that only int16_t or uint16_t type is used.
    ///
    /// @param u universe (V4 or V6).
    /// @tparam T int16_t or uint16_t.
    template<typename T>
    void bufferToIntTest16(const Option::Universe u) {
        // Create option that conveys array of multiple uint16_t or int16_t values.
        boost::shared_ptr<OptionIntArray<T> > opt;
        const int opt_len = 20;
        const uint16_t opt_code = 81;

        // Constructor throws exception if provided buffer is empty.
        EXPECT_THROW(
            OptionIntArray<T>(u, opt_code, buf_.begin(), buf_.begin()),
            isc::OutOfRange
        );

        // Constructor throws exception if provided buffer's length is not
        // multiple of 2-bytes.
        EXPECT_THROW(
            OptionIntArray<T>(u, opt_code, buf_.begin(), buf_.begin() + 5),
            isc::OutOfRange
        );

        // Now the buffer length is correct.
        ASSERT_NO_THROW(
            opt = boost::shared_ptr<
                OptionIntArray<T> >(new OptionIntArray<T>(u, opt_code, buf_.begin(),
                                                          buf_.begin() + opt_len))
        );

        EXPECT_EQ(u, opt->getUniverse());
        EXPECT_EQ(opt_code, opt->getType());
        // Option should return vector of uint16_t values which should be
        // constructed from the buffer we provided.
        std::vector<T> values = opt->getValues();
        ASSERT_EQ(opt_len, values.size() * sizeof(T));
        // Create reference values from the buffer so as we can
        // simply compare two vectors.
        std::vector<T> reference_values;
        for (int i = 0; i < opt_len; i += 2) {
            reference_values.push_back((buf_[i] << 8) |
                                       buf_[i + 1]);
        }
        EXPECT_TRUE(std::equal(reference_values.begin(), reference_values.end(),
                               values.begin()));

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

    /// @brief Test parsing buffer into array of int32_t or uint32_t values.
    ///
    /// @warning this function does not perform type check. Make
    /// sure that only int32_t or uint32_t type is used.
    ///
    /// @param u universe (V4 or V6)
    /// @tparam T int32_t or uint32_t.
    template<typename T>
    void bufferToIntTest32(const Option::Universe u) {
        // Create option that conveys array of multiple uint16_t values.
        boost::shared_ptr<OptionIntArray<T> > opt;
        const int opt_len = 40;
        const uint16_t opt_code = 82;

        // Constructor throws exception if provided buffer is empty.
        EXPECT_THROW(
            OptionIntArray<T>(u, opt_code, buf_.begin(), buf_.begin()),
            isc::OutOfRange
        );

        // Constructor throws exception if provided buffer's length is not
        // multiple of 4-bytes.
        EXPECT_THROW(
            OptionIntArray<T>(u, opt_code, buf_.begin(), buf_.begin() + 9),
            isc::OutOfRange
        );

        // Now the buffer length is correct.
        ASSERT_NO_THROW(
            opt = boost::shared_ptr<
                OptionIntArray<T> >(new OptionIntArray<T>(u, opt_code, buf_.begin(),
                                                          buf_.begin() + opt_len))
        );

        EXPECT_EQ(u, opt->getUniverse());
        EXPECT_EQ(opt_code, opt->getType());
        // Option should return vector of uint32_t values which should be
        // constructed from the buffer we provided.
        std::vector<T> values = opt->getValues();
        ASSERT_EQ(opt_len, values.size() * sizeof(T));
        // Create reference values from the buffer so as we can
        // simply compare two vectors.
        std::vector<T> reference_values;
        for (int i = 0; i < opt_len; i += 4) {
            reference_values.push_back((buf_[i] << 24) |
                                       (buf_[i + 1] << 16 & 0x00FF0000) |
                                       (buf_[i + 2] << 8 & 0xFF00) |
                                       (buf_[i + 3] & 0xFF));
        }
        EXPECT_TRUE(std::equal(reference_values.begin(), reference_values.end(),
                               values.begin()));

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


    OptionBuffer buf_;     ///< Option buffer
    OutputBuffer out_buf_; ///< Output buffer
};

/// @todo: below, there is a bunch of tests for options that
/// convey unsigned values. We should maybe extend these tests for
/// signed types too.

TEST_F(OptionIntArrayTest, useInvalidType) {
    const uint16_t opt_code = 80;
    EXPECT_THROW(
        boost::scoped_ptr<
            OptionIntArray<bool> >(new OptionIntArray<bool>(Option::V6, opt_code,
                                                            OptionBuffer(5))),
        InvalidDataType
    );

    EXPECT_THROW(
        boost::scoped_ptr<
            OptionIntArray<int64_t> >(new OptionIntArray<int64_t>(Option::V6,
                                                                  opt_code,
                                                                  OptionBuffer(10))),
        InvalidDataType
    );

}

TEST_F(OptionIntArrayTest, bufferToUint8V6) {
    bufferToIntTest8<uint8_t>(Option::V6);
}

TEST_F(OptionIntArrayTest, bufferToInt8V6) {
    bufferToIntTest8<int8_t>(Option::V6);
}

TEST_F(OptionIntArrayTest, bufferToUint16V6) {
    bufferToIntTest16<uint16_t>(Option::V6);
}

TEST_F(OptionIntArrayTest, bufferToInt16V6) {
    bufferToIntTest16<int16_t>(Option::V6);
}

TEST_F(OptionIntArrayTest, bufferToUint32V6) {
    bufferToIntTest32<uint32_t>(Option::V6);
}

TEST_F(OptionIntArrayTest, bufferToInt32V6) {
    bufferToIntTest32<int32_t>(Option::V6);
}

TEST_F(OptionIntArrayTest, setValuesUint8) {
    const uint16_t opt_code = 100;
    // Create option with empty vector of values.
    boost::shared_ptr<OptionIntArray<uint8_t> >
        opt(new OptionIntArray<uint8_t>(Option::V6, opt_code));
    // Initialize vector with some data and pass to the option.
    std::vector<uint8_t> values;
    for (int i = 0; i < 10; ++i) {
        values.push_back(numeric_limits<uint8_t>::max() - i);
    }
    opt->setValues(values);

    // Check if universe, option type and data was set correctly.
    EXPECT_EQ(Option::V6, opt->getUniverse());
    EXPECT_EQ(opt_code, opt->getType());
    std::vector<uint8_t> returned_values = opt->getValues();
    EXPECT_TRUE(std::equal(values.begin(), values.end(), returned_values.begin()));
}

TEST_F(OptionIntArrayTest, setValuesInt8) {
    const uint16_t opt_code = 100;
    // Create option with empty vector of values.
    boost::shared_ptr<OptionIntArray<int8_t> >
        opt(new OptionIntArray<int8_t>(Option::V6, opt_code));
    // Initialize vector with some data and pass to the option.
    std::vector<int8_t> values;
    for (int i = 0; i < 10; ++i) {
        values.push_back(numeric_limits<int8_t>::min() + i);
    }
    opt->setValues(values);

    // Check if universe, option type and data was set correctly.
    EXPECT_EQ(Option::V6, opt->getUniverse());
    EXPECT_EQ(opt_code, opt->getType());
    std::vector<int8_t> returned_values = opt->getValues();
    EXPECT_TRUE(std::equal(values.begin(), values.end(), returned_values.begin()));
}

TEST_F(OptionIntArrayTest, setValuesUint16) {
    const uint16_t opt_code = 101;
    // Create option with empty vector of values.
    boost::shared_ptr<OptionIntArray<uint16_t> >
        opt(new OptionIntArray<uint16_t>(Option::V6, opt_code));
    // Initialize vector with some data and pass to the option.
    std::vector<uint16_t> values;
    for (int i = 0; i < 10; ++i) {
        values.push_back(numeric_limits<uint16_t>::max() - i);
    }
    opt->setValues(values);

    // Check if universe, option type and data was set correctly.
    EXPECT_EQ(Option::V6, opt->getUniverse());
    EXPECT_EQ(opt_code, opt->getType());
    std::vector<uint16_t> returned_values = opt->getValues();
    EXPECT_TRUE(std::equal(values.begin(), values.end(), returned_values.begin()));
}

TEST_F(OptionIntArrayTest, setValuesInt16) {
    const uint16_t opt_code = 101;
    // Create option with empty vector of values.
    boost::shared_ptr<OptionIntArray<int16_t> >
        opt(new OptionIntArray<int16_t>(Option::V6, opt_code));
    // Initialize vector with some data and pass to the option.
    std::vector<int16_t> values;
    for (int i = 0; i < 10; ++i) {
        values.push_back(numeric_limits<int16_t>::min() + i);
    }
    opt->setValues(values);

    // Check if universe, option type and data was set correctly.
    EXPECT_EQ(Option::V6, opt->getUniverse());
    EXPECT_EQ(opt_code, opt->getType());
    std::vector<int16_t> returned_values = opt->getValues();
    EXPECT_TRUE(std::equal(values.begin(), values.end(), returned_values.begin()));
}

TEST_F(OptionIntArrayTest, setValuesUint32) {
    const uint32_t opt_code = 101;
    // Create option with empty vector of values.
    boost::shared_ptr<OptionIntArray<uint32_t> >
        opt(new OptionIntArray<uint32_t>(Option::V6, opt_code));
    // Initialize vector with some data and pass to the option.
    std::vector<uint32_t> values;
    for (int i = 0; i < 10; ++i) {
        values.push_back(numeric_limits<uint32_t>::max() - i);
    }
    opt->setValues(values);

    // Check if universe, option type and data was set correctly.
    EXPECT_EQ(Option::V6, opt->getUniverse());
    EXPECT_EQ(opt_code, opt->getType());
    std::vector<uint32_t> returned_values = opt->getValues();
    EXPECT_TRUE(std::equal(values.begin(), values.end(), returned_values.begin()));
}

TEST_F(OptionIntArrayTest, setValuesInt32) {
    const uint32_t opt_code = 101;
    // Create option with empty vector of values.
    boost::shared_ptr<OptionIntArray<int32_t> >
        opt(new OptionIntArray<int32_t>(Option::V6, opt_code));
    // Initialize vector with some data and pass to the option.
    std::vector<int32_t> values;
    for (int i = 0; i < 10; ++i) {
        values.push_back(numeric_limits<int32_t>::min() + i);
    }
    opt->setValues(values);

    // Check if universe, option type and data was set correctly.
    EXPECT_EQ(Option::V6, opt->getUniverse());
    EXPECT_EQ(opt_code, opt->getType());
    std::vector<int32_t> returned_values = opt->getValues();
    EXPECT_TRUE(std::equal(values.begin(), values.end(), returned_values.begin()));
}


} // anonymous namespace
