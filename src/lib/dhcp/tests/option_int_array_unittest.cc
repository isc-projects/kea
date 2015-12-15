// Copyright (C) 2012, 2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <dhcp/dhcp6.h>
#include <dhcp/option.h>
#include <dhcp/option6_iaaddr.h>
#include <dhcp/option_int_array.h>
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

/// @brief OptionIntArray test class.
class OptionIntArrayTest : public ::testing::Test {
public:
    /// @brief Constructor.
    ///
    /// Initializes the option buffer with some data.
    OptionIntArrayTest(): buf_(255), out_buf_(255) {
        for (unsigned i = 0; i < 255; i++) {
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

        EXPECT_EQ(u, opt->getUniverse());
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

        // Check if pack worked properly:
        InputBuffer out(out_buf_.getData(), out_buf_.getLength());

        if (u == Option::V4) {
            // The total length is 10 bytes for data and 2 bytes for a header.
            ASSERT_EQ(12, out_buf_.getLength());
            // if option type is correct
            EXPECT_EQ(opt_code, out.readUint8());
            // if option length is correct
            EXPECT_EQ(10, out.readUint8());
        } else {
            // The total length is 10 bytes for data and 4 bytes for a header.
            ASSERT_EQ(14, out_buf_.getLength());
            // if option type is correct
            EXPECT_EQ(opt_code, out.readUint16());
            // if option length is correct
            EXPECT_EQ(10, out.readUint16());
        }

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

        // Check if pack worked properly:
        InputBuffer out(out_buf_.getData(), out_buf_.getLength());

        if (u == Option::V4) {
            // The total length is 20 bytes for data and 2 bytes for a header.
            ASSERT_EQ(22, out_buf_.getLength());
            // if option type is correct
            EXPECT_EQ(opt_code, out.readUint8());
            // if option length is correct
            EXPECT_EQ(20, out.readUint8());
        } else {
            // The total length is 20 bytes for data and 4 bytes for a header.
            ASSERT_EQ(24, out_buf_.getLength());
            // if option type is correct
            EXPECT_EQ(opt_code, out.readUint16());
            // if option length is correct
            EXPECT_EQ(20, out.readUint16());
        }
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

        // Check if pack worked properly:
        InputBuffer out(out_buf_.getData(), out_buf_.getLength());

        if (u == Option::V4) {
            // The total length is 40 bytes for data and 2 bytes for a header.
            ASSERT_EQ(42, out_buf_.getLength());
            // if option type is correct
            EXPECT_EQ(opt_code, out.readUint8());
            // if option length is correct
            EXPECT_EQ(40, out.readUint8());
        } else {
            // The total length is 40 bytes for data and 4 bytes for a header.
            ASSERT_EQ(44, out_buf_.getLength());
            // if option type is correct
            EXPECT_EQ(opt_code, out.readUint16());
            // if option length is correct
            EXPECT_EQ(40, out.readUint16());
        }

        // if data is correct
        std::vector<uint8_t> out_data;
        ASSERT_NO_THROW(out.readVector(out_data, opt_len));
        ASSERT_EQ(opt_len, out_data.size());
        EXPECT_TRUE(std::equal(buf_.begin(), buf_.begin() + opt_len, out_data.begin()));;
    }

    /// @brief Test ability to set all values.
    ///
    /// @tparam T numeric type to perform the test for.
    template<typename T>
    void setValuesTest() {
        const uint16_t opt_code = 100;
        // Create option with empty vector of values.
        boost::shared_ptr<OptionIntArray<T> >
            opt(new OptionIntArray<T>(Option::V6, opt_code));
        // Initialize vector with some data and pass to the option.
        std::vector<T> values;
        for (int i = 0; i < 10; ++i) {
            values.push_back(numeric_limits<uint8_t>::max() - i);
        }
        opt->setValues(values);

        // Check if universe, option type and data was set correctly.
        EXPECT_EQ(Option::V6, opt->getUniverse());
        EXPECT_EQ(opt_code, opt->getType());
        std::vector<T> returned_values = opt->getValues();
        EXPECT_TRUE(std::equal(values.begin(), values.end(), returned_values.begin()));
    }

    /// @brief Test ability to add values one by one.
    ///
    /// @tparam T numeric type to perform the test for.
    template<typename T>
    void addValuesTest() {
        const uint16_t opt_code = 100;
        // Create option with empty vector of values.
        boost::shared_ptr<OptionIntArray<T> >
            opt(new OptionIntArray<T>(Option::V6, opt_code));
        // Initialize vector with some data and add the same data
        // to the option.
        std::vector<T> values;
        for (int i = 0; i < 10; ++i) {
            values.push_back(numeric_limits<T>::max() - i);
            opt->addValue(numeric_limits<T>::max() - i);
        }

        // Check if universe, option type and data was set correctly.
        EXPECT_EQ(Option::V6, opt->getUniverse());
        EXPECT_EQ(opt_code, opt->getType());
        std::vector<T> returned_values = opt->getValues();
        EXPECT_TRUE(std::equal(values.begin(), values.end(), returned_values.begin()));
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

TEST_F(OptionIntArrayTest, bufferToUint8V4) {
    bufferToIntTest8<uint8_t>(Option::V4);
}

TEST_F(OptionIntArrayTest, bufferToUint8V6) {
    bufferToIntTest8<uint8_t>(Option::V6);
}

TEST_F(OptionIntArrayTest, bufferToInt8V4) {
    bufferToIntTest8<int8_t>(Option::V4);
}

TEST_F(OptionIntArrayTest, bufferToInt8V6) {
    bufferToIntTest8<int8_t>(Option::V6);
}

TEST_F(OptionIntArrayTest, bufferToUint16V4) {
    bufferToIntTest16<uint16_t>(Option::V4);
}

TEST_F(OptionIntArrayTest, bufferToUint16V6) {
    bufferToIntTest16<uint16_t>(Option::V6);
}

TEST_F(OptionIntArrayTest, bufferToInt16V4) {
    bufferToIntTest16<int16_t>(Option::V4);
}

TEST_F(OptionIntArrayTest, bufferToInt16V6) {
    bufferToIntTest16<int16_t>(Option::V6);
}

TEST_F(OptionIntArrayTest, bufferToUint32V4) {
    bufferToIntTest32<uint32_t>(Option::V4);
}

TEST_F(OptionIntArrayTest, bufferToUint32V6) {
    bufferToIntTest32<uint32_t>(Option::V6);
}

TEST_F(OptionIntArrayTest, bufferToInt32V4) {
    bufferToIntTest32<int32_t>(Option::V4);
}

TEST_F(OptionIntArrayTest, bufferToInt32V6) {
    bufferToIntTest32<int32_t>(Option::V6);
}

TEST_F(OptionIntArrayTest, setValuesUint8) {
    setValuesTest<uint8_t>();
}

TEST_F(OptionIntArrayTest, setValuesInt8) {
    setValuesTest<int8_t>();
}

TEST_F(OptionIntArrayTest, setValuesUint16) {
    setValuesTest<uint16_t>();
}

TEST_F(OptionIntArrayTest, setValuesInt16) {
    setValuesTest<int16_t>();
}

TEST_F(OptionIntArrayTest, setValuesUint32) {
    setValuesTest<uint16_t>();
}

TEST_F(OptionIntArrayTest, setValuesInt32) {
    setValuesTest<int16_t>();
}

TEST_F(OptionIntArrayTest, addValuesUint8) {
    addValuesTest<uint8_t>();
}

TEST_F(OptionIntArrayTest, addValuesInt8) {
    addValuesTest<int8_t>();
}

TEST_F(OptionIntArrayTest, addValuesUint16) {
    addValuesTest<uint16_t>();
}

TEST_F(OptionIntArrayTest, addValuesInt16) {
    addValuesTest<int16_t>();
}

TEST_F(OptionIntArrayTest, addValuesUint32) {
    addValuesTest<uint16_t>();
}

TEST_F(OptionIntArrayTest, addValuesInt32) {
    addValuesTest<int16_t>();
}

// This test checks that the option is correctly converted into
// the textual format.
TEST_F(OptionIntArrayTest, toText) {
    OptionUint32Array option(Option::V4, 128);
    option.addValue(1);
    option.addValue(32);
    option.addValue(324);

    EXPECT_EQ("type=128, len=012: 1(uint32) 32(uint32) 324(uint32)",
              option.toText());
}

// This test checks that the option holding multiple uint8 values
// is correctly converted to the textual format.
TEST_F(OptionIntArrayTest, toTextUint8) {
    OptionUint8Array option(Option::V4, 128);
    option.addValue(1);
    option.addValue(7);
    option.addValue(15);

    EXPECT_EQ("type=128, len=003: 1(uint8) 7(uint8) 15(uint8)",
              option.toText());
}



} // anonymous namespace
