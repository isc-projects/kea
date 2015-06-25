// Copyright (C) 2015  Internet Systems Consortium, Inc. ("ISC")
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

#include <cmath>
#include <util/ntp_utils.h>

#include <gtest/gtest.h>

using namespace isc;
using namespace isc::util;
using namespace std;
using namespace boost::posix_time;
using namespace boost::gregorian;

namespace {

const ptime epoch(date(1970, Jan, 1));

bool eq(Ntp ntpa, Ntp ntpb) {
    return ((ntpa.ntp_sec_ == ntpb.ntp_sec_) &&
            (ntpa.ntp_fraction_ == ntpb.ntp_fraction_));
}

}

TEST(NtpUtilsTest, zero) {
    Ntp ntp;
    EXPECT_TRUE(ntp.is_zero());
    ntp.ntp_fraction_ = 1;
    EXPECT_TRUE(ntp.is_zero());
    ntp.ntp_sec_ = 1;
    ntp.ntp_fraction_ = 0;
    EXPECT_FALSE(ntp.is_zero());
}

TEST(NtpUtilsTest, timeval) {
    struct timeval tv0;
    tv0.tv_sec = 1234;
    tv0.tv_usec = 5665;
    Ntp ntp0(&tv0);
    Ntp expected0(2208990034ULL, uint16_t(371U));
    EXPECT_TRUE(eq(ntp0, expected0));

    ptime ptime1(date(2015, May, 1), hours(13) + minutes(13) + seconds(13));
    time_duration td1(ptime1 - epoch);
    struct timeval tv1;
    tv1.tv_sec = td1.total_seconds();
    tv1.tv_usec = 150;
    Ntp ntp1(&tv1);
    Ntp expected1(3639474793ULL, uint16_t(9U));
    EXPECT_TRUE(eq(ntp1, expected1));

    ptime ptime2(date(2045, May, 1), hours(13) + minutes(13) + seconds(13));
    time_duration td2(ptime2 - epoch);
    struct timeval tv2;
    tv2.tv_sec =
        static_cast<time_t>(static_cast<unsigned>(td2.total_seconds()));
    tv2.tv_usec = 150;
    Ntp ntp2(&tv2);
    Ntp expected2(4586245993ULL, uint16_t(9U));
    EXPECT_TRUE(eq(ntp2, expected2));
}

TEST(NtpUtilsTest, posixTime) {
    Ntp ntp0(epoch);
    Ntp expected0(2208988800ULL, uint16_t(0));
    EXPECT_TRUE(eq(ntp0, expected0));

    ptime ptime1(date(2015, May, 1),
                 hours(13) + minutes(13) + seconds(13) + milliseconds(150));
    Ntp ntp1(ptime1);
    Ntp expected1(3639474793ULL, uint16_t(9830U));
    EXPECT_TRUE(eq(ntp1, expected1));

    ptime ptime2(date(2045, May, 1),
                 hours(13) + minutes(13) + seconds(13) + milliseconds(150));
    Ntp ntp2(ptime2);
    Ntp expected2(4586245993ULL, uint16_t(9830U));
    EXPECT_TRUE(eq(ntp2, expected2));
}

TEST(NtpUtilsTest, fromBinary) {
    const uint8_t data[] = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08 };
    vector<uint8_t> bin(8);
    memcpy(&bin[0], data, 8);
    vector<uint8_t> too_short = bin;
    too_short.resize(7);
    Ntp ntp;
    EXPECT_FALSE(ntp.from_binary(too_short));
    vector<uint8_t> too_long = bin;
    too_long.push_back(0x08);
    EXPECT_FALSE(ntp.from_binary(too_long));
    EXPECT_TRUE(ntp.is_zero());
    EXPECT_TRUE(ntp.from_binary(bin));
    Ntp expected(0x10203040506ULL, uint16_t(0x708U));
    EXPECT_TRUE(eq(ntp, expected));
}

TEST(NtpUtilsTest, toBinary) {
    const uint8_t expected[] = { 0x01, 0x02, 0x03, 0x04,
                                 0x05, 0x06, 0x07, 0x08 };
    Ntp ntp(0x10203040506ULL, uint16_t(0x708U));
    vector<uint8_t> bin(ntp.to_binary());
    ASSERT_EQ(8, bin.size());
    EXPECT_TRUE(memcmp(&bin[0], expected, 8) == 0);
}

TEST(NtpUtilsTest, double) {
    struct timeval tv;
    EXPECT_EQ(0, gettimeofday(&tv, 0));
    Ntp ntp(&tv);
    double d(ntp.secs(tv.tv_sec));
    EXPECT_GE(d, 0.);
    EXPECT_LT(d, 1.);

    double d1(123.456);
    Ntp tmp(d1, tv.tv_sec);
    double d2(tmp.secs(tv.tv_sec));
    EXPECT_LE(fabs(d2 - d1), 0.0001);
}

TEST(NtpUtilsTest, verifyNew) {
    struct timeval tv;
    EXPECT_EQ(0, gettimeofday(&tv, 0));
    Ntp rd_new(&tv);
    Ntp ts_new(&tv);
    EXPECT_TRUE(Ntp::verify_new(rd_new, ts_new));
    ts_new.ntp_sec_ -= 200;
    EXPECT_TRUE(Ntp::verify_new(rd_new,ts_new));
    ts_new.ntp_sec_ -= 200;
    EXPECT_FALSE(Ntp::verify_new(rd_new,ts_new));
    ts_new = rd_new;
    ts_new.ntp_sec_ += 200;
    EXPECT_TRUE(Ntp::verify_new(rd_new,ts_new));
    ts_new.ntp_sec_ += 200;
    EXPECT_FALSE(Ntp::verify_new(rd_new,ts_new));
}

TEST(NtpUtilsTest, verify) {
    struct timeval tv;
    EXPECT_EQ(0, gettimeofday(&tv, 0));
    Ntp rd_new(&tv);
    Ntp ts_new(&tv);
    Ntp rd_last(&tv);
    rd_last.ntp_sec_ -= 1000;
    Ntp ts_last(&tv);
    ts_last.ntp_sec_ -= 1000;
    bool to_update0 = false;
    EXPECT_TRUE(Ntp::verify(rd_new, ts_new, rd_last, ts_last, &to_update0));
    EXPECT_TRUE(to_update0);
    bool to_update1 = false;
    Ntp next1(&tv);
    next1.ntp_sec_ += 1;
    EXPECT_TRUE(Ntp::verify(rd_new, ts_new, rd_new, next1, &to_update1));
    EXPECT_FALSE(to_update1);
    bool to_update2 = false;
    EXPECT_FALSE(Ntp::verify(rd_new, ts_new, next1, next1, &to_update2));
    EXPECT_FALSE(to_update2);
    ts_new.ntp_sec_ -= 10;
    bool to_update3 = false;
    EXPECT_TRUE(Ntp::verify(rd_new, ts_new, rd_last, ts_last, &to_update3));
    EXPECT_TRUE(to_update3);
    ts_new.ntp_sec_ -= 10;
    bool to_update4 = false;
    EXPECT_FALSE(Ntp::verify(rd_new, ts_new, rd_last, ts_last, &to_update4));
    EXPECT_FALSE(to_update4);
}
