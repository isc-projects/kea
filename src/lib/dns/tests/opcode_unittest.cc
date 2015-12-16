// Copyright (C) 2010-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <vector>
#include <sstream>

#include <exceptions/exceptions.h>

#include <dns/opcode.h>

#include <gtest/gtest.h>

using namespace std;
using namespace isc::dns;

namespace {
TEST(OpcodeTest, construct) {
    // This test also tests getCode()
    EXPECT_EQ(0, Opcode(0).getCode());
    EXPECT_EQ(15, Opcode(Opcode::RESERVED15_CODE).getCode());

    EXPECT_THROW(Opcode(16), isc::OutOfRange);
}

TEST(OpcodeTest, constants) {
    // We'll only test arbitrarily chosen subsets of the codes.
    // This class is quite simple, so it should be suffice.

    EXPECT_EQ(Opcode::QUERY_CODE, Opcode(0).getCode());
    EXPECT_EQ(Opcode::IQUERY_CODE, Opcode(1).getCode());
    EXPECT_EQ(Opcode::NOTIFY_CODE, Opcode(4).getCode());
    EXPECT_EQ(Opcode::UPDATE_CODE, Opcode(5).getCode());
    EXPECT_EQ(Opcode::RESERVED15_CODE, Opcode(15).getCode());

    EXPECT_EQ(Opcode::QUERY_CODE, Opcode::QUERY().getCode());
    EXPECT_EQ(Opcode::IQUERY_CODE, Opcode::IQUERY().getCode());
    EXPECT_EQ(Opcode::NOTIFY_CODE, Opcode::NOTIFY().getCode());
    EXPECT_EQ(Opcode::UPDATE_CODE, Opcode::UPDATE().getCode());
    EXPECT_EQ(Opcode::RESERVED15_CODE, Opcode::RESERVED15().getCode());
}

TEST(OpcodeTest, equal) {
    EXPECT_TRUE(Opcode::QUERY() == Opcode(Opcode::QUERY_CODE));
    EXPECT_TRUE(Opcode::QUERY().equals(Opcode(Opcode::QUERY_CODE)));
    EXPECT_TRUE(Opcode::IQUERY() == Opcode(Opcode::IQUERY_CODE));
    EXPECT_TRUE(Opcode::IQUERY().equals(Opcode(Opcode::IQUERY_CODE)));
    EXPECT_TRUE(Opcode::NOTIFY() == Opcode(Opcode::NOTIFY_CODE));
    EXPECT_TRUE(Opcode::NOTIFY().equals(Opcode(Opcode::NOTIFY_CODE)));
    EXPECT_TRUE(Opcode::UPDATE() == Opcode(Opcode::UPDATE_CODE));
    EXPECT_TRUE(Opcode::UPDATE().equals(Opcode(Opcode::UPDATE_CODE)));
    EXPECT_TRUE(Opcode::RESERVED15() == Opcode(Opcode::RESERVED15()));
    EXPECT_TRUE(Opcode::RESERVED15().equals(Opcode(Opcode::RESERVED15())));
}

TEST(OpcodeTest, nequal) {
    EXPECT_TRUE(Opcode::QUERY() != Opcode::IQUERY());
    EXPECT_TRUE(Opcode::QUERY().nequals(Opcode::IQUERY()));
    EXPECT_TRUE(Opcode::NOTIFY() != Opcode(1));
    EXPECT_TRUE(Opcode::NOTIFY().nequals(Opcode(1)));
    EXPECT_TRUE(Opcode(10) != Opcode(11));
    EXPECT_TRUE(Opcode(10).nequals(Opcode(11)));
}

TEST(OpcodeTest, toText) {
    vector<const char*> expects;
    expects.resize(Opcode::RESERVED15_CODE + 1);
    expects[Opcode::QUERY_CODE] = "QUERY";
    expects[Opcode::IQUERY_CODE] = "IQUERY";
    expects[Opcode::STATUS_CODE] = "STATUS";
    expects[Opcode::RESERVED3_CODE] = "RESERVED3";
    expects[Opcode::NOTIFY_CODE] = "NOTIFY";
    expects[Opcode::UPDATE_CODE] = "UPDATE";
    expects[Opcode::RESERVED6_CODE] = "RESERVED6";
    expects[Opcode::RESERVED7_CODE] = "RESERVED7";
    expects[Opcode::RESERVED8_CODE] = "RESERVED8";
    expects[Opcode::RESERVED9_CODE] = "RESERVED9";
    expects[Opcode::RESERVED10_CODE] = "RESERVED10";
    expects[Opcode::RESERVED11_CODE] = "RESERVED11";
    expects[Opcode::RESERVED12_CODE] = "RESERVED12";
    expects[Opcode::RESERVED13_CODE] = "RESERVED13";
    expects[Opcode::RESERVED14_CODE] = "RESERVED14";
    expects[Opcode::RESERVED15_CODE] = "RESERVED15";

    for (unsigned int i = 0; i <= Opcode::RESERVED15_CODE; ++i) {
        EXPECT_EQ(expects.at(i), Opcode(i).toText());
    }
}

// test operator<<.  We simply confirm it appends the result of toText().
TEST(OpcodeTest, LeftShiftOperator) {
    ostringstream oss;
    oss << Opcode::NOTIFY();
    EXPECT_EQ(Opcode::NOTIFY().toText(), oss.str());
}
}
