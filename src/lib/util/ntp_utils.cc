// Copyright (C) 2015 Internet Systems Consortium, Inc. ("ISC")
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
#include <limits.h>
#include <sstream>
#include <exceptions/exceptions.h>
#include <util/ntp_utils.h>
#include <boost/format.hpp>

using namespace boost::posix_time;
using namespace boost::gregorian;

namespace isc {
namespace util {

namespace {

// \brief seconds between 1900 and 1970 epochs
const uint32_t EPOCH_ADJUST = 2208988800UL;

// \brief Allowed delta (300s / 5mn)
const double DELTA = 300.;

// \brief Allowed fuzz factor (1s)
const double FUZZ = 1.;

// \brief Allowed clock drift (.01s)
const double DRIFT = .01;

// \brief Normalized unsigned number of seconds
uint64_t nuns(time_t t) {
    // time_t can be a signed 32 bit integer
    if (sizeof(time_t) == 4) {
        // First/sign bit will be set after 20380118
        uint32_t repr = static_cast<uint32_t>(t);
        return (static_cast<uint64_t>(repr));
    }
    // or time_t is a signed 64 bit integer
    return (static_cast<uint64_t>(t));
}

// \brief Normalized fractional seconds
int64_t nfs(long f) {
    // fractional seconds is a signed integer representing less than 1 second
    return (static_cast<int64_t>(f));
}

}

bool Ntp::is_zero() const {
    return (ntp_sec_ == 0);
}

Ntp::Ntp() : ntp_sec_(0), ntp_fraction_(0)
{
}

Ntp::Ntp(uint64_t sec, uint16_t fraction)
    : ntp_sec_(sec), ntp_fraction_(fraction)
{
}

Ntp::Ntp(const struct timeval* tv)
{
    ntp_sec_ = nuns(tv->tv_sec) + EPOCH_ADJUST;
    int64_t fcvt = (nfs(static_cast<long>(tv->tv_usec)) * 65536) / 1000000;
    ntp_fraction_ = static_cast<uint16_t>(fcvt & 0xffff);
}

Ntp::Ntp(const ptime pt)
{
    ptime epoch(date(1970, Jan, 1));
    time_duration dur(pt - epoch);
    ntp_sec_ = nuns(static_cast<unsigned>(dur.total_seconds())) + EPOCH_ADJUST;
    int64_t fcvt = (nfs(static_cast<long>(dur.fractional_seconds())) * 65536U)
        / time_duration::ticks_per_second();
    ntp_fraction_ = static_cast<uint16_t>(fcvt & 0xffff);
}

Ntp::Ntp(double secs, time_t base)
{
    double intpart;
    double fracpart = std::modf(secs, &intpart);
    ntp_sec_ = static_cast<uint64_t>(intpart) + nuns(base) + EPOCH_ADJUST;
    ntp_fraction_ = static_cast<uint16_t>(floor(fracpart * 65536.));
}

bool Ntp::from_binary(const std::vector<uint8_t> binary)
{
    if (binary.size() != 8) {
        return (false);
    }
    ntp_sec_ = binary[0];
    ntp_sec_ <<= 8;
    ntp_sec_ |= binary[1];
    ntp_sec_ <<= 8;
    ntp_sec_ |= binary[2];
    ntp_sec_ <<= 8;
    ntp_sec_ |= binary[3];
    ntp_sec_ <<= 8;
    ntp_sec_ |= binary[4];
    ntp_sec_ <<= 8;
    ntp_sec_ |= binary[5];
    ntp_fraction_ = binary[6];
    ntp_fraction_ <<= 8;
    ntp_fraction_ |= binary[7];
    return (true);
}

std::vector<uint8_t> Ntp::to_binary() const
{
    std::vector<uint8_t> ret(8);
    ret[0] = static_cast<uint8_t>((ntp_sec_ >> 24) & 0xff);
    ret[1] = static_cast<uint8_t>((ntp_sec_ >> 16) & 0xff);
    ret[2] = static_cast<uint8_t>((ntp_sec_ >> 8) & 0xff);
    ret[3] = static_cast<uint8_t>(ntp_sec_ & 0xff);
    ret[4] = static_cast<uint8_t>((ntp_fraction_ >> 24) & 0xff);
    ret[5] = static_cast<uint8_t>((ntp_fraction_ >> 16) & 0xff);
    ret[6] = static_cast<uint8_t>((ntp_fraction_ >> 8) & 0xff);
    ret[7] = static_cast<uint8_t>(ntp_fraction_ & 0xff);
    return (ret);
}

double Ntp::secs(time_t base) const
{
    double ret = static_cast<double>(ntp_sec_);
    ret -= nuns(base) + EPOCH_ADJUST;
    ret += static_cast<double>(ntp_fraction_) / 65536.;
    return (ret);
}

std::string Ntp::to_text() const
{
    if (is_zero()) {
        return ("1900-01-01 00:00:00.000");
    } else if (ntp_sec_ < EPOCH_ADJUST) {
        isc_throw(isc::BadValue, "NTP timestamp before 1970");
    }
    const uint64_t s = ntp_sec_ - EPOCH_ADJUST;
    if (s > std::numeric_limits<uint32_t>::max()) {
        isc_throw(isc::BadValue, "NTP timestamp after 2106");
    }
    const time_t t = static_cast<const time_t>(s);
    struct tm* tm = std::gmtime(&t);
    boost::format d("%04d-%02d-%02d %02d:%02d:%02d.%03d");
    d % (tm->tm_year + 1900);
    d % (tm->tm_mon + 1);
    d % tm->tm_mday;
    d % tm->tm_hour;
    d % tm->tm_min;
    d % tm->tm_sec;
    d % static_cast<int>(static_cast<double>(ntp_fraction_) / 65.536);
    return (d.str());
}

bool Ntp::verify_new(const Ntp& rd_new, const Ntp& ts_new)
{
    time_t base = time(NULL);
    double drd_new = rd_new.secs(base);
    double dts_new = ts_new.secs(base);
    if (drd_new >= dts_new) {
        if ((drd_new - dts_new) < DELTA) {
            return (true);
        } else {
            return (false);
        }
    } else {
        if ((dts_new - drd_new) < DELTA) {
            return (true);
        } else {
            return (false);
        }
    }
}

bool Ntp::verify(const Ntp& rd_new, const Ntp& ts_new,
                 const Ntp& rd_last, const Ntp& ts_last, bool* to_update)
{
    time_t base = time(NULL);
    double drd_new = rd_new.secs(base);
    double drd_last = rd_last.secs(base);
    if (drd_new < drd_last) {
        return (false);
    }
    double dts_new = ts_new.secs(base);
    double dts_last = ts_last.secs(base);
    double expected = dts_last - FUZZ;
    expected += (drd_new - drd_last) * (1. - DRIFT);
    if (expected >= dts_new + FUZZ) {
        return (false);
    } else {
        if (dts_new > dts_last) {
            *to_update = true;
        }
        return (true);
    }
}

}
}
