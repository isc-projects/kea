// Copyright (C) 2018-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// @file This file contains tests which exercise the load and unload
/// functions in the Radius hooks library. In order to test the load
/// function, one must be able to pass it hook library parameters. The
/// the only way to populate these parameters is by actually loading the
/// library via HooksManager::loadLibraries().

#include <config.h>

#include <radius_utils.h>
#include <radius.h>
#include <attribute_test.h>
#include <gtest/gtest.h>

using namespace std;
using namespace isc;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::radius;

namespace {

/// @brief Test fixture for testing utils code.
class UtilsTest : public radius::test::AttributeTest {
public:
    /// @brief Constructor.
    UtilsTest() : test::AttributeTest(), impl_(RadiusImpl::instance()) {
        impl_.reset();
        ElementPtr config = Element::createMap();
        impl_.init(config);
    }

    /// @brief Destructor.
    virtual ~UtilsTest() {
    }

    /// @brief Radius implementation.
    RadiusImpl& impl_;
};

// Verifies the canonize util.
TEST_F(UtilsTest, canonize) {
    EXPECT_EQ("01-02-03-04-05-06", canonize("01:02:03:04:05:06"));
    EXPECT_EQ("07-08-09-0a-0b-0c", canonize("07:08:09:0A:0B:0C"));
    EXPECT_EQ("abcd-effe-00", canonize("ABCD:EFfe-00"));
    EXPECT_EQ("fdJKHJKHdK", canonize("FDJKHJKHdK"));
}

// Verifies the DHCPv4 pop0 util.
TEST_F(UtilsTest, pop0_4) {
    vector<uint8_t> vec = { 0x00, 0x01, 0x02 };
    ClientIdPtr cid;

    // Standard case.
    cid.reset(new ClientId(vec));
    vector<uint8_t> ret = pop0(cid);
    ASSERT_EQ(2, ret.size());
    EXPECT_EQ(0x01, ret[0]);
    EXPECT_EQ(0x02, ret[1]);

    // One element: pop0 does nothing.
    // (vec, 1) throws because MIN_CLIENT_ID_LEN is 2.
    cid.reset(new ClientId(&vec[0], 2));
    vector<uint8_t>& content = const_cast<vector<uint8_t>&>(cid->getClientId());
    content.resize(1);
    ret = pop0(cid);
    ASSERT_EQ(1, ret.size());
    EXPECT_EQ(0x00, ret[0]);

    // Empty: pop0 does nothing.
    cid.reset(new ClientId(&vec[0], 2));
    vector<uint8_t>& content1 = const_cast<vector<uint8_t>&>(cid->getClientId());
    content1.clear();
    ret = pop0(cid);
    EXPECT_TRUE(ret.empty());

    // Not zero: pop0 does nothing.
    vector<uint8_t> vec1 = { 0x01, 0x02, 0x03 };
    cid.reset(new ClientId(vec1));
    ret = pop0(cid);
    ASSERT_EQ(3, ret.size());
    EXPECT_EQ(0x01, ret[0]);
    EXPECT_EQ(0x02, ret[1]);
    EXPECT_EQ(0x03, ret[2]);
}

// Verifies the DHCPv6 pop0 util.
TEST_F(UtilsTest, pop0_6) {
    vector<uint8_t> vec = { 0x00, 0x00, 0x02, 0x03 };
    DuidPtr duid;

    // Standard case.
    duid.reset(new DUID(vec));
    vector<uint8_t> ret = pop0(duid);
    ASSERT_EQ(2, ret.size());
    EXPECT_EQ(0x02, ret[0]);
    EXPECT_EQ(0x03, ret[1]);

    // Not zero: pop0 does nothing.
    vector<uint8_t> vec1 = { 0x00, 0x01, 0x02, 0x03 };
    duid.reset(new DUID(vec1));
    ret = pop0(duid);
    ASSERT_EQ(4, ret.size());
    EXPECT_EQ(0x00, ret[0]);
    EXPECT_EQ(0x01, ret[1]);
    EXPECT_EQ(0x02, ret[2]);
    EXPECT_EQ(0x03, ret[3]);

    vector<uint8_t> vec2 = { 0x01, 0x00, 0x02, 0x03 };
    duid.reset(new DUID(vec2));
    ret = pop0(duid);
    ASSERT_EQ(4, ret.size());
    EXPECT_EQ(0x01, ret[0]);
    EXPECT_EQ(0x00, ret[1]);
    EXPECT_EQ(0x02, ret[2]);
    EXPECT_EQ(0x03, ret[3]);
}

// Verifies the toPrintable util.
TEST_F(UtilsTest, toPrintable) {
    vector<uint8_t> vec = { 0x41, 0x62, 0x63, 0x64 };
    EXPECT_EQ("Abcd", toPrintable(vec));
    vec = { 0x41, 0x62, 0xc3, 0x64 };
    EXPECT_EQ("41:62:c3:64", toPrintable(vec));
    DUID duid(&vec[0], 4);
    EXPECT_EQ("41:62:c3:64", duid.toText());
}

// Verifies the extractDuid util.
TEST_F(UtilsTest, extractDuid) {
    vector<uint8_t> vec = { 0xff, 0x01, 0x02, 0x03, 0x04, 0x41, 0x42, 0x43 };
    ClientIdPtr cid;

    // Standard case.
    cid.reset(new ClientId(vec));
    bool extracted = false;
    vector<uint8_t> ret = extractDuid(cid, extracted);
    EXPECT_TRUE(extracted);
    ASSERT_EQ(3, ret.size());
    EXPECT_EQ(0x41, ret[0]);
    EXPECT_EQ(0x42, ret[1]);
    EXPECT_EQ(0x43, ret[2]);

    // Short case.
    cid.reset(new ClientId(&vec[0], 5));
    extracted = false;
    ret = extractDuid(cid, extracted);
    EXPECT_FALSE(extracted);
    EXPECT_EQ(5, ret.size());
    EXPECT_EQ(vec[0], ret[0]);

    // Not duid case.
    vec[0] = 0x01;
    cid.reset(new ClientId(vec));
    extracted = false;
    ret = extractDuid(cid, extracted);
    EXPECT_FALSE(extracted);
    EXPECT_EQ(vec.size(), ret.size());
    EXPECT_EQ(vec[0], ret[0]);

    vec[0] = 0;
    cid.reset(new ClientId(vec));
    extracted = false;
    ret = extractDuid(cid, extracted);
    EXPECT_FALSE(extracted);
    EXPECT_EQ(vec.size(), ret.size());
    EXPECT_EQ(vec[0], ret[0]);
}

} // end of anonymous namespace
