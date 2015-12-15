// Copyright (C) 2010  Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <vector>
#include <sstream>

#include <exceptions/exceptions.h>

#include <dns/rcode.h>

#include <gtest/gtest.h>

using namespace std;
using namespace isc::dns;

namespace {
TEST(RcodeTest, constructFromCode) {
    // Normal cases.  This test also tests getCode()
    EXPECT_EQ(0, Rcode(0).getCode());
    EXPECT_EQ(0xfff, Rcode(0xfff).getCode()); // possible max code

    // should fail on attempt of construction with an out of range code
    EXPECT_THROW(Rcode(0x1000), isc::OutOfRange);
    EXPECT_THROW(Rcode(0xffff), isc::OutOfRange);
}

TEST(RcodeTest, constructFromCodePair) {
    EXPECT_EQ(3, Rcode(Rcode::NXDOMAIN_CODE, 0).getCode());
    EXPECT_EQ(Rcode::BADVERS_CODE, Rcode(0, 1).getCode());
    EXPECT_EQ(0xfff, Rcode(0xf, 0xff).getCode());
    EXPECT_THROW(Rcode(0x10, 0xff), isc::OutOfRange);
}

TEST(RcodeTest, getExtendedCode) {
    EXPECT_EQ(0, Rcode::NOERROR().getExtendedCode());
    EXPECT_EQ(0, Rcode::YXRRSET().getExtendedCode());
    EXPECT_EQ(1, Rcode::BADVERS().getExtendedCode());
    EXPECT_EQ(0xab, Rcode(0xabf).getExtendedCode());
    EXPECT_EQ(0xff, Rcode(0xfff).getExtendedCode());
}

TEST(RcodeTest, constants) {
    // We'll only test arbitrarily chosen subsets of the codes.
    // This class is quite simple, so it should be suffice.

    EXPECT_EQ(Rcode::NOERROR_CODE, Rcode(0).getCode());
    EXPECT_EQ(Rcode::FORMERR_CODE, Rcode(1).getCode());
    EXPECT_EQ(Rcode::NOTIMP_CODE, Rcode(4).getCode());
    EXPECT_EQ(Rcode::REFUSED_CODE, Rcode(5).getCode());
    EXPECT_EQ(Rcode::RESERVED15_CODE, Rcode(15).getCode());
    EXPECT_EQ(Rcode::BADVERS_CODE, Rcode(16).getCode());

    EXPECT_EQ(Rcode::NOERROR_CODE, Rcode::NOERROR().getCode());
    EXPECT_EQ(Rcode::FORMERR_CODE, Rcode::FORMERR().getCode());
    EXPECT_EQ(Rcode::NOTIMP_CODE, Rcode::NOTIMP().getCode());
    EXPECT_EQ(Rcode::REFUSED_CODE, Rcode::REFUSED().getCode());
    EXPECT_EQ(Rcode::RESERVED15_CODE, Rcode::RESERVED15().getCode());
    EXPECT_EQ(Rcode::BADVERS_CODE, Rcode::BADVERS().getCode());
}

TEST(RcodeTest, equal) {
    EXPECT_TRUE(Rcode::NOERROR() == Rcode(Rcode::NOERROR_CODE));
    EXPECT_TRUE(Rcode::NOERROR().equals(Rcode(Rcode::NOERROR_CODE)));
    EXPECT_TRUE(Rcode::FORMERR() == Rcode(Rcode::FORMERR_CODE));
    EXPECT_TRUE(Rcode::FORMERR().equals(Rcode(Rcode::FORMERR_CODE)));
    EXPECT_TRUE(Rcode::NOTIMP() == Rcode(Rcode::NOTIMP_CODE));
    EXPECT_TRUE(Rcode::NOTIMP().equals(Rcode(Rcode::NOTIMP_CODE)));
    EXPECT_TRUE(Rcode::REFUSED() == Rcode(Rcode::REFUSED_CODE));
    EXPECT_TRUE(Rcode::REFUSED().equals(Rcode(Rcode::REFUSED_CODE)));
    EXPECT_TRUE(Rcode::RESERVED15() == Rcode(Rcode::RESERVED15()));
    EXPECT_TRUE(Rcode::RESERVED15().equals(Rcode(Rcode::RESERVED15())));
    EXPECT_TRUE(Rcode::BADVERS() == Rcode(Rcode::BADVERS_CODE));
    EXPECT_TRUE(Rcode::BADVERS().equals(Rcode(Rcode::BADVERS_CODE)));
}

TEST(RcodeTest, nequal) {
    EXPECT_TRUE(Rcode::NOERROR() != Rcode::FORMERR());
    EXPECT_TRUE(Rcode::NOERROR().nequals(Rcode::FORMERR()));
    EXPECT_TRUE(Rcode::NOTIMP() != Rcode(1));
    EXPECT_TRUE(Rcode::NOTIMP().nequals(Rcode(1)));
    EXPECT_TRUE(Rcode(10) != Rcode(11));
    EXPECT_TRUE(Rcode(10).nequals(Rcode(11)));
}

TEST(RcodeTest, toText) {
    vector<const char*> expects;
    expects.resize(Rcode::BADVERS_CODE + 1);
    expects[Rcode::NOERROR_CODE] = "NOERROR";
    expects[Rcode::FORMERR_CODE] = "FORMERR";
    expects[Rcode::SERVFAIL_CODE] = "SERVFAIL";
    expects[Rcode::NXDOMAIN_CODE] = "NXDOMAIN";
    expects[Rcode::NOTIMP_CODE] = "NOTIMP";
    expects[Rcode::REFUSED_CODE] = "REFUSED";
    expects[Rcode::YXDOMAIN_CODE] = "YXDOMAIN";
    expects[Rcode::YXRRSET_CODE] = "YXRRSET";
    expects[Rcode::NXRRSET_CODE] = "NXRRSET";
    expects[Rcode::NOTAUTH_CODE] = "NOTAUTH";
    expects[Rcode::NOTZONE_CODE] = "NOTZONE";
    expects[Rcode::RESERVED11_CODE] = "RESERVED11";
    expects[Rcode::RESERVED12_CODE] = "RESERVED12";
    expects[Rcode::RESERVED13_CODE] = "RESERVED13";
    expects[Rcode::RESERVED14_CODE] = "RESERVED14";
    expects[Rcode::RESERVED15_CODE] = "RESERVED15";
    expects[Rcode::BADVERS_CODE] = "BADVERS";

    for (unsigned int i = 0; i <= Rcode::BADVERS_CODE; ++i) {
        EXPECT_EQ(expects.at(i), Rcode(i).toText());
    }

    // Non well-known Rcodes
    EXPECT_EQ("17", Rcode(Rcode::BADVERS().getCode() + 1).toText());
    EXPECT_EQ("4095", Rcode(Rcode(0xfff)).toText());
}

// test operator<<.  We simply confirm it appends the result of toText().
TEST(RcodeTest, LeftShiftOperator) {
    ostringstream oss;
    oss << Rcode::SERVFAIL();
    EXPECT_EQ(Rcode::SERVFAIL().toText(), oss.str());
}
}
