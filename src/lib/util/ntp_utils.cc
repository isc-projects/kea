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
#include <util/ntp_utils.h>

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
}

Ntp::Ntp() : ntp_sec_(0), ntp_fraction_(0)
{
}

Ntp::Ntp(uint64_t sec, uint16_t fraction)
    : ntp_sec_(sec), ntp_fraction_(fraction)
{
}

Ntp::Ntp(struct timeval tv)
{
    ntp_sec_ = static_cast<uint32_t>(tv.tv_sec) + EPOCH_ADJUST;
    uint32_t fcvt = (tv.tv_usec * 65536U) / 1000000UL;
    ntp_fraction_ = static_cast<uint16_t>(fcvt & 0xffff);
}

Ntp::Ntp(double secs, time_t base)
{
    double intpart;
    double fracpart = std::modf(secs, &intpart);
    ntp_sec_ = static_cast<uint64_t>(intpart) + base + EPOCH_ADJUST;
    ntp_fraction_ = static_cast<uint16_t>(floor(fracpart * 65536.));
}

bool Ntp::from_binary(std::vector<uint8_t> binary)
{
    if (binary.size() != 8) {
        return (false);
    }
    ntp_sec_ = static_cast<uint64_t>(binary[0]) << 40;
    ntp_sec_ |= static_cast<uint64_t>(binary[1]) << 32;
    ntp_sec_ |= binary[2] << 24;
    ntp_sec_ |= binary[3] << 16;
    ntp_sec_ |= binary[4] << 8;
    ntp_sec_ |= binary[5];
    ntp_fraction_ = binary[6] << 8;
    ntp_fraction_ |= binary[7];
    return (true);
}

std::vector<uint8_t> Ntp::to_binary() const
{
    std::vector<uint8_t> ret(8);
    ret[0] = static_cast<uint8_t>((ntp_sec_ >> 40) & 0xff);
    ret[1] = static_cast<uint8_t>((ntp_sec_ >> 32) & 0xff);
    ret[2] = static_cast<uint8_t>((ntp_sec_ >> 24) & 0xff);
    ret[3] = static_cast<uint8_t>((ntp_sec_ >> 16) & 0xff);
    ret[4] = static_cast<uint8_t>((ntp_sec_ >> 8) & 0xff);
    ret[5] = static_cast<uint8_t>(ntp_sec_ & 0xff);
    ret[6] = static_cast<uint8_t>((ntp_fraction_ >> 8) & 0xff);
    ret[7] = static_cast<uint8_t>(ntp_fraction_ & 0xff);
    return (ret);
}

double Ntp::secs(time_t base) const
{
    double ret = static_cast<double>(ntp_sec_ - base - EPOCH_ADJUST);
    ret += static_cast<double>(ntp_fraction_ * (1./65536.));
    return (ret);
}

bool Ntp::verify_new(const Ntp& rd_new, const Ntp& ts_new, time_t base)
{
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
                 const Ntp& rd_last, const Ntp& ts_last,
                 time_t base, bool* to_update)
{
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
