// Copyright (C) 2026 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <perfdhcp/pkt_transform.h>

#include <gtest/gtest.h>

using namespace std;
using namespace isc;
using namespace isc::dhcp;
using namespace isc::perfdhcp;

namespace {

/// @brief Test Fixture Class
///
/// This test fixture class is used to perform
/// unit tests on perfdhcp PerfSocketTest class.
/// Limited to trivial sanity checks.
class PktTransformTest : public virtual ::testing::Test
{
public:
    PktTransformTest() { }
};

// Verify that pack does not work on too small input.
TEST_F(PktTransformTest, pack) {
    OptionBuffer in_buffer;
    OptionCollection options;
    util::OutputBuffer out_buffer(10);
    // Throw on empty in_buffer.
    EXPECT_THROW(PktTransform::pack(Option::V4, in_buffer, options,
                                    0, 1234, out_buffer),
                 Unexpected);
    in_buffer.resize(4);
    // Return false on transid offset == 0.
    bool ret = PktTransform::pack(Option::V4, in_buffer, options,
                                  0, 1234, out_buffer);
    ASSERT_FALSE(ret);
    // Return false on not place for the transaction id.
    ret = PktTransform::pack(Option::V4, in_buffer, options,
                             1, 1234, out_buffer);
    ASSERT_FALSE(ret);
    in_buffer.resize(8);
    ret = PktTransform::pack(Option::V4, in_buffer, options,
                             1, 1234, out_buffer);
    EXPECT_TRUE(ret);
}

// Verify that writeAt checks its arguments.
TEST_F(PktTransformTest, writeAt) {
    OptionBuffer in_buffer;
    OptionBuffer data;
    // Empty data does nothing.
    EXPECT_EQ(0, std::distance(data.begin(), data.end()));
    ASSERT_NO_THROW(PktTransform::writeAt(in_buffer, 0,
                                          data.begin(), data.end()));
    data.resize(1);
    data[0] = 0x12;
    // Swapped iterators do nothing.
    EXPECT_EQ(-1, std::distance(data.end(), data.begin()));
    ASSERT_NO_THROW(PktTransform::writeAt(in_buffer, 0,
                                          data.end(), data.begin()));
    // No room in the input buffer.
    ASSERT_THROW(PktTransform::writeAt(in_buffer, 0,
                                       data.begin(), data.end()),
                 OutOfRange);
    in_buffer.resize(1);
    ASSERT_THROW(PktTransform::writeAt(in_buffer, 1,
                                       data.begin(), data.end()),
                 OutOfRange);

    EXPECT_NO_THROW(PktTransform::writeAt(in_buffer, 0,
                                          data.begin(), data.end()));
    ASSERT_FALSE(in_buffer.empty());
    EXPECT_EQ(0x12, in_buffer[0]);
}

// Verify that writeValueAt checks its arguments.
TEST_F(PktTransformTest, writeValueAt) {
    OptionBuffer in_buffer;
    uint16_t value = 0x1234;
    // No room in the input buffer.
    ASSERT_THROW(PktTransform::writeValueAt(in_buffer, 0, value), OutOfRange);
    in_buffer.resize(2);
    ASSERT_THROW(PktTransform::writeValueAt(in_buffer, 1, value), OutOfRange);
    EXPECT_NO_THROW(PktTransform::writeValueAt(in_buffer, 0, value));
    ASSERT_EQ(2U, in_buffer.size());
    EXPECT_EQ(0x12, in_buffer[0]);
    EXPECT_EQ(0x34, in_buffer[1]);
}

}
