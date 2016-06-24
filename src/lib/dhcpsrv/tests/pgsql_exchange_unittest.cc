// Copyright (C) 2016 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <dhcpsrv/pgsql_exchange.h>

#include <boost/lexical_cast.hpp>

#include <gtest/gtest.h>

using namespace isc;
using namespace isc::dhcp;

namespace {

/// @brief Converts a time_t into a string matching our Postgres input format
///
/// @param time_val Time value to convert
/// @retrun A string containing the converted time
std::string timeToDbString(const time_t time_val) {
    struct tm tinfo;
    char buffer[20];

    localtime_r(&time_val, &tinfo);
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", &tinfo);
    return(std::string(buffer));
}

/// @brief Basic checks on time conversion functions in PgSqlExchange
/// We input timestamps as date/time strings and we output them as
/// an integer string of seconds since the epoch.  There is no meangingful
/// way to test them round-trip without Postgres involved.
TEST(PgSqlExchangeTest, convertTimeTest) {
    // Get a reference time and time string
    time_t ref_time;
    time(&ref_time);

    std::string ref_time_str(timeToDbString(ref_time));

    // Verify convertToDatabaseTime gives us the expected localtime string
    std::string time_str = PgSqlExchange::convertToDatabaseTime(ref_time);
    EXPECT_EQ(time_str, ref_time_str);

    // Verify convertToDatabaseTime with valid_lifetime = 0  gives us the
    // expected localtime string
    time_str = PgSqlExchange::convertToDatabaseTime(ref_time, 0);
    EXPECT_EQ(time_str, ref_time_str);

    // Verify we can add time by adding a day.
    ref_time_str = timeToDbString(ref_time + (24*3600));
    ASSERT_NO_THROW(time_str = PgSqlExchange::convertToDatabaseTime(ref_time,
                                                                    24*3600));
    EXPECT_EQ(time_str, ref_time_str);

    // Verify too large of a value is detected.
    ASSERT_THROW(PgSqlExchange::convertToDatabaseTime(DatabaseConnection::
                                                      MAX_DB_TIME - 1,
                                                      24*3600),
                 isc::BadValue);

    // Make sure Conversion "from" database time functions
    std::string ref_secs_str = boost::lexical_cast<std::string>(ref_time);
    time_t from_time = PgSqlExchange::convertFromDatabaseTime(ref_secs_str);
    from_time = PgSqlExchange::convertFromDatabaseTime(ref_secs_str);
    EXPECT_EQ(ref_time, from_time);
}

TEST(PsqlBindArray, basicOperation) {
    
    PsqlBindArray b;

    uint8_t small_int = 25;
    b.add(small_int);

    int reg_int = 376;
    b.add(reg_int);

    uint64_t big_int = 86749032;
    b.add(big_int);

    b.add((bool)(1));
    b.add((bool)(0));

    b.add(isc::asiolink::IOAddress("192.2.15.34"));
    b.add(isc::asiolink::IOAddress("3001::1"));

    std::string str("just a string");
    b.add(str);

    std::vector<uint8_t> bytes;
    for (int i = 0; i < 10; i++) {
        bytes.push_back(i+1);
    }

    b.add(bytes);

    std::string expected = 
        "0 : \"25\"\n"
        "1 : \"376\"\n"
        "2 : \"86749032\"\n"
        "3 : \"TRUE\"\n"
        "4 : \"FALSE\"\n"
        "5 : \"3221360418\"\n"
        "6 : \"3001::1\"\n"
        "7 : \"just a string\"\n"
        "8 : 0x0102030405060708090a\n";

    EXPECT_EQ(expected, b.toText());
}

}; // namespace

