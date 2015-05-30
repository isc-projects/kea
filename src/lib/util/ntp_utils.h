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

#ifndef KEA_NTP_UTILS_H
#define KEA_NTP_UTILS_H

#include <string>
#include <vector>

#include <stdint.h>
#include <sys/time.h>

#include <boost/date_time/posix_time/posix_time.hpp>

namespace isc {
namespace util {

///
/// \brief NTP (RFC 5905) time
///
/// External representation: uint64_t seconds, uint16_t fractional
/// Network representation: 48+16 bit unsigned fixed point
struct Ntp {
    // \brief seconds sinec 1900
    uint64_t ntp_sec_;

    // \brief 1/65536th of seconds
    uint16_t ntp_fraction_;

    // \brief Test if the object got a value
    bool is_zero() const;

    // \brief Default constructor
    Ntp();

    // \brief Standard constructor
    Ntp(uint64_t sec, uint16_t fraction);

    // \brief Conversion from timeval
    Ntp(const struct timeval* tv);

    // \brief Conversion from boost posix_time
    Ntp(const boost::posix_time::ptime pt);

    // \brief Conversion from based double
    Ntp(double secs, time_t base);

    // \brief Conversion from network
    bool from_binary(const std::vector<uint8_t> binary);

    // \brief Conversion to network
    std::vector<uint8_t> to_binary() const;

    // \brief Conversion to based double
    double secs(time_t base) const;

    // \brief Verify a timestamp without cache
    static bool verify_new(const Ntp& rd_new, const Ntp& ts_new);

    // \brief Verify a timestamp with cache
    static bool verify(const Ntp& rd_new, const Ntp& ts_new,
                       const Ntp& rd_last, const Ntp& ts_last,
                       bool* to_update);
};

} // end of isc::util namespace
} // end of isc namespace

#endif // KEA_NTP_UTILS_H
