// Copyright (C) 2011-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <asiolink/io_address.h>
#include <dhcp/duid.h>
#include <exceptions/exceptions.h>

#include <boost/scoped_ptr.hpp>
#include <gtest/gtest.h>

#include <iostream>
#include <sstream>

#include <arpa/inet.h>

using namespace std;
using namespace isc;
using namespace isc::dhcp;
using namespace isc::asiolink;

// don't import the entire boost namespace.  It will unexpectedly hide uint8_t
// for some systems.
using boost::scoped_ptr;

namespace {

// This is a workaround for strange linking problems with gtest:
// libdhcp___unittests-duid_unittest.o: In function `Compare<long unsigned int, long unsigned int>':
// ~/gtest-1.6.0/include/gtest/gtest.h:1353: undefined reference to `isc::dhcp::ClientId::MAX_CLIENT_ID_LE'N
// collect2: ld returned 1 exit status

const size_t MAX_DUID_LEN = DUID::MAX_DUID_LEN;
const size_t MAX_CLIENT_ID_LEN = DUID::MAX_DUID_LEN;


// This test verifies if the constructors are working as expected
// and process passed parameters.
TEST(DuidTest, constructor) {

    uint8_t data1[] = {0, 1, 2, 3, 4, 5, 6};

    vector<uint8_t> data2(data1, data1 + sizeof(data1));

    scoped_ptr<DUID> duid1(new DUID(data1, sizeof(data1)));
    scoped_ptr<DUID> duid2(new DUID(data2));

    vector<uint8_t> vecdata = duid1->getDuid();
    EXPECT_TRUE(data2 == vecdata);
    EXPECT_EQ(DUID::DUID_LLT, duid1->getType());

    vecdata = duid2->getDuid();
    EXPECT_TRUE(data2 == vecdata);

    EXPECT_EQ(DUID::DUID_LLT, duid2->getType());
}

// This test verifies if DUID size restrictions are implemented
// properly.
TEST(DuidTest, size) {
    uint8_t data[MAX_DUID_LEN + 1];
    vector<uint8_t> data2;
    for (uint8_t i = 0; i < MAX_DUID_LEN + 1; ++i) {
        data[i] = i;
        if (i < MAX_DUID_LEN)
            data2.push_back(i);
    }
    ASSERT_EQ(data2.size(), MAX_DUID_LEN);

    scoped_ptr<DUID> duidmaxsize1(new DUID(data, MAX_DUID_LEN));
    scoped_ptr<DUID> duidmaxsize2(new DUID(data2));

    EXPECT_THROW(
        scoped_ptr<DUID> toolarge1(new DUID(data, MAX_DUID_LEN + 1)),
        BadValue);

    // that's one too much
    data2.push_back(128);

    EXPECT_THROW(
        scoped_ptr<DUID> toolarge2(new DUID(data2)),
        BadValue);

    // empty duids are not allowed
    vector<uint8_t> empty;
    EXPECT_THROW(
        scoped_ptr<DUID> emptyDuid(new DUID(empty)),
        BadValue);

    EXPECT_THROW(
        scoped_ptr<DUID> emptyDuid2(new DUID(data, 0)),
        BadValue);
}

// This test verifies if the implementation supports all defined
// DUID types.
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

// This test checks that the DUID instance can be created from the textual
// format and that error is reported if the textual format is invalid.
TEST(DuidTest, fromText) {
    scoped_ptr<DUID> duid;
    // DUID with only decimal digits.
    ASSERT_NO_THROW(
        duid.reset(new DUID(DUID::fromText("00:01:02:03:04:05:06")))
    );
    EXPECT_EQ("00:01:02:03:04:05:06", duid->toText());
    // DUID with some hexadecimal digits (upper case and lower case).
    ASSERT_NO_THROW(
        duid.reset(new DUID(DUID::fromText("00:aa:bb:CD:ee:EF:ab")))
    );
    EXPECT_EQ("00:aa:bb:cd:ee:ef:ab", duid->toText());
    // DUID with one digit for a particular byte.
    ASSERT_NO_THROW(
        duid.reset(new DUID(DUID::fromText("00:a:bb:D:ee:EF:ab")))
    );
    EXPECT_EQ("00:0a:bb:0d:ee:ef:ab", duid->toText());
    // Repeated colon sign is not allowed.
    EXPECT_THROW(
        duid.reset(new DUID(DUID::fromText("00::bb:D:ee:EF:ab"))),
        isc::BadValue
    );
    // DUID with excessive number of digits for one of the bytes.
    EXPECT_THROW(
       duid.reset(new DUID(DUID::fromText("00:01:021:03:04:05:06"))),
       isc::BadValue
    );
}

// Test checks if the toText() returns valid texual representation
TEST(DuidTest, toText) {
    uint8_t data1[] = {0, 1, 2, 3, 4, 0xff, 0xfe};

    DUID duid(data1, sizeof(data1));
    EXPECT_EQ("00:01:02:03:04:ff:fe", duid.toText());
}

// This test verifies that empty DUID returns proper value
TEST(DuidTest, empty) {
    DuidPtr empty;
    EXPECT_NO_THROW(empty = DUID::generateEmpty());

    // This method must return something
    ASSERT_TRUE(empty);

    // Ok, technically empty is not really empty, it's just a single
    // byte with value of 0.
    EXPECT_EQ("00", empty->toText());
}

// This test checks if the comparison operators are sane.
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

// This test verifies if the ClientId constructors are working properly
// and passed parameters are used
TEST(ClientIdTest, constructor) {
    IOAddress addr2("192.0.2.1");
    IOAddress addr3("2001:db8:1::1");

    uint8_t data1[] = {0, 1, 2, 3, 4, 5, 6};
    vector<uint8_t> data2(data1, data1 + sizeof(data1));

    // checks for C-style constructor (uint8_t * + len)
    scoped_ptr<ClientId> id1(new ClientId(data1, sizeof(data1)));
    vector<uint8_t> vecdata = id1->getClientId();
    EXPECT_TRUE(data2 == vecdata);

    // checks for vector-based constructor
    scoped_ptr<ClientId> id2(new ClientId(data2));
    vecdata = id2->getClientId();
    EXPECT_TRUE(data2 == vecdata);
}

// Check that client-id sizes are reasonable
TEST(ClientIdTest, size) {
    uint8_t data[MAX_CLIENT_ID_LEN + 1];
    vector<uint8_t> data2;
    for (uint8_t i = 0; i < MAX_CLIENT_ID_LEN + 1; ++i) {
        data[i] = i;
        if (i < MAX_CLIENT_ID_LEN)
            data2.push_back(i);
    }
    ASSERT_EQ(data2.size(), MAX_CLIENT_ID_LEN);

    scoped_ptr<ClientId> duidmaxsize1(new ClientId(data, MAX_CLIENT_ID_LEN));
    scoped_ptr<ClientId> duidmaxsize2(new ClientId(data2));

    EXPECT_THROW(
        scoped_ptr<ClientId> toolarge1(new ClientId(data, MAX_CLIENT_ID_LEN + 1)),
        BadValue);

    // that's one too much
    data2.push_back(128);

    EXPECT_THROW(
        scoped_ptr<ClientId> toolarge2(new ClientId(data2)),
        BadValue);

    // empty client-ids are not allowed
    vector<uint8_t> empty;
    EXPECT_THROW(
        scoped_ptr<ClientId> empty_client_id1(new ClientId(empty)),
        BadValue);

    EXPECT_THROW(
        scoped_ptr<ClientId> empty_client_id2(new ClientId(data, 0)),
        BadValue);

    // client-id must be at least 2 bytes long
    vector<uint8_t> shorty(1,17); // just a single byte with value 17
    EXPECT_THROW(
        scoped_ptr<ClientId> too_short_client_id1(new ClientId(shorty)),
        BadValue);
    EXPECT_THROW(
        scoped_ptr<ClientId> too_short_client_id1(new ClientId(data, 1)),
        BadValue);
}

// This test checks if the comparison operators are sane.
TEST(ClientIdTest, operators) {
    uint8_t data1[] = {0, 1, 2, 3, 4, 5, 6};
    uint8_t data2[] = {0, 1, 2, 3, 4};
    uint8_t data3[] = {0, 1, 2, 3, 4, 5, 7}; // last digit different
    uint8_t data4[] = {0, 1, 2, 3, 4, 5, 6}; // the same as 1

    scoped_ptr<ClientId> id1(new ClientId(data1, sizeof(data1)));
    scoped_ptr<ClientId> id2(new ClientId(data2, sizeof(data2)));
    scoped_ptr<ClientId> id3(new ClientId(data3, sizeof(data3)));
    scoped_ptr<ClientId> id4(new ClientId(data4, sizeof(data4)));

    EXPECT_TRUE(*id1 == *id4);
    EXPECT_FALSE(*id1 == *id2);
    EXPECT_FALSE(*id1 == *id3);

    EXPECT_FALSE(*id1 != *id4);
    EXPECT_TRUE(*id1 != *id2);
    EXPECT_TRUE(*id1 != *id3);
}

// Test checks if the toText() returns valid texual representation
TEST(ClientIdTest, toText) {
    uint8_t data1[] = {0, 1, 2, 3, 4, 0xff, 0xfe};

    ClientId clientid(data1, sizeof(data1));
    EXPECT_EQ("00:01:02:03:04:ff:fe", clientid.toText());
}

// This test checks that the ClientId instance can be created from the textual
// format and that error is reported if the textual format is invalid.
TEST(ClientIdTest, fromText) {
    ClientIdPtr cid;
    // ClientId with only decimal digits.
    ASSERT_NO_THROW(
        cid = ClientId::fromText("00:01:02:03:04:05:06")
    );
    EXPECT_EQ("00:01:02:03:04:05:06", cid->toText());
    // ClientId with some hexadecimal digits (upper case and lower case).
    ASSERT_NO_THROW(
        cid = ClientId::fromText("00:aa:bb:CD:ee:EF:ab")
    );
    EXPECT_EQ("00:aa:bb:cd:ee:ef:ab", cid->toText());
    // ClientId with one digit for a particular byte.
    ASSERT_NO_THROW(
        cid = ClientId::fromText("00:a:bb:D:ee:EF:ab")
    );
    EXPECT_EQ("00:0a:bb:0d:ee:ef:ab", cid->toText());
    // ClientId without any colons is allowed.
    ASSERT_NO_THROW(
        cid = ClientId::fromText("0010abcdee");
    );
    EXPECT_EQ("00:10:ab:cd:ee", cid->toText());
    // Repeated colon sign in the ClientId is not allowed.
    EXPECT_THROW(
        ClientId::fromText("00::bb:D:ee:EF:ab"),
        isc::BadValue

    );
    // ClientId with excessive number of digits for one of the bytes.
    EXPECT_THROW(
        ClientId::fromText("00:01:021:03:04:05:06"),
        isc::BadValue
    );
    // ClientId  with two spaces between the colons should not be allowed.
    EXPECT_THROW(
        ClientId::fromText("00:01:  :03:04:05:06"),
        isc::BadValue
    );

    // ClientId  with one space between the colons should not be allowed.
    EXPECT_THROW(
        ClientId::fromText("00:01: :03:04:05:06"),
        isc::BadValue
    );

    // ClientId  with three spaces between the colons should not be allowed.
    EXPECT_THROW(
        ClientId::fromText("00:01:   :03:04:05:06"),
        isc::BadValue
    );
}


} // end of anonymous namespace
