// Copyright (C) 2011  Internet Systems Consortium, Inc. ("ISC")
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
#include <iostream>
#include <sstream>
#include <arpa/inet.h>
#include <gtest/gtest.h>
#include <exceptions/exceptions.h>
#include <boost/scoped_ptr.hpp>
#include <dhcp/duid.h>

using namespace std;
using namespace isc;
using namespace isc::dhcp;

// don't import the entire boost namespace.  It will unexpectedly hide uint8_t
// for some systems.
using boost::scoped_ptr;

namespace {

TEST(DuidTest, constructor) {

    uint8_t data1[] = {0, 1, 2, 3, 4, 5, 6};

    vector<uint8_t> data2(data1, data1 + sizeof(data1));

    scoped_ptr<DUID> duid1(new DUID(data1, sizeof(data1)));
    scoped_ptr<DUID> duid2(new DUID(data2));

    vector<uint8_t> vecdata = duid1->getDuid();
    EXPECT_EQ(data2, vecdata);
    EXPECT_EQ(DUID::DUID_LLT, duid1->getType());

    vecdata = duid2->getDuid();
    EXPECT_EQ(data2, vecdata);

    EXPECT_EQ(DUID::DUID_LLT, duid2->getType());
}

TEST(DuidTest, size) {
    const int MAX_DUID_SIZE = 128;
    uint8_t data[MAX_DUID_SIZE + 1];
    vector<uint8_t> data2;
    for (uint8_t i = 0; i < MAX_DUID_SIZE + 1; ++i) {
        data[i] = i;
        if (i < MAX_DUID_SIZE)
            data2.push_back(i);
    }
    ASSERT_EQ(data2.size(), MAX_DUID_SIZE);

    scoped_ptr<DUID> duidmaxsize1(new DUID(data, MAX_DUID_SIZE));
    scoped_ptr<DUID> duidmaxsize2(new DUID(data2));

    EXPECT_THROW(
        scoped_ptr<DUID> toolarge1(new DUID(data, MAX_DUID_SIZE + 1)),
        OutOfRange);

    // that's one too much
    data2.push_back(128);

    EXPECT_THROW(
        scoped_ptr<DUID> toolarge2(new DUID(data2)),
        OutOfRange);
}

TEST(DuidTest, getType) {
    uint8_t llt[] =     {0, 1, 2, 3, 4, 5, 6};
    uint8_t en[] =      {0, 2, 2, 3, 4, 5, 6};
    uint8_t ll[] =      {0, 3, 2, 3, 4, 5, 6};
    uint8_t uuid[] =    {0, 4, 2, 3, 4, 5, 6};
    uint8_t invalid[] = {0,55, 2, 3, 4, 5, 6};

    scoped_ptr<DUID> duid_llt(new DUID(llt, sizeof(llt)));
    scoped_ptr<DUID> duid_en(new DUID(en, sizeof(en)));
    scoped_ptr<DUID> duid_ll(new DUID(ll, sizeof(ll)));
    scoped_ptr<DUID> duid_uuid(new DUID(uuid, sizeof(uuid)));
    scoped_ptr<DUID> duid_invalid(new DUID(invalid, sizeof(invalid)));

    EXPECT_EQ(DUID::DUID_LLT,     duid_llt->getType());
    EXPECT_EQ(DUID::DUID_EN,      duid_en->getType());
    EXPECT_EQ(DUID::DUID_LL,      duid_ll->getType());
    EXPECT_EQ(DUID::DUID_UUID,    duid_uuid->getType());
    EXPECT_EQ(DUID::DUID_UNKNOWN, duid_invalid->getType());
}

TEST(DuidTest, operators) {
    uint8_t data1[] = {0, 1, 2, 3, 4, 5, 6};
    uint8_t data2[] = {0, 1, 2, 3, 4};
    uint8_t data3[] = {0, 1, 2, 3, 4, 5, 7}; // last digit different
    uint8_t data4[] = {0, 1, 2, 3, 4, 5, 6}; // the same as 1

    scoped_ptr<DUID> duid1(new DUID(data1, sizeof(data1)));
    scoped_ptr<DUID> duid2(new DUID(data2, sizeof(data2)));
    scoped_ptr<DUID> duid3(new DUID(data3, sizeof(data3)));
    scoped_ptr<DUID> duid4(new DUID(data4, sizeof(data4)));

    EXPECT_TRUE(*duid1 == *duid4);
    EXPECT_FALSE(*duid1 == *duid2);
    EXPECT_FALSE(*duid1 == *duid3);

    EXPECT_FALSE(*duid1 != *duid4);
    EXPECT_TRUE(*duid1 != *duid2);
    EXPECT_TRUE(*duid1 != *duid3);
}



} // end of anonymous namespace
