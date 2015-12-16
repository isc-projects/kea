// Copyright (C) 2009-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef TIME_UTILITIES_H
#define TIME_UTILITIES_H 1

#include <string>

#include <sys/types.h>
#include <stdint.h>

#include <exceptions/exceptions.h>

//
// Note: this helper module isn't specific to the DNS protocol per se.
// We should probably move this to somewhere else, possibly in some common
// utility area.
//

namespace isc {
namespace util {

///
/// \brief A standard DNS (or ISC) module exception that is thrown if
/// a time conversion function encounters bad input
///
class InvalidTime : public Exception {
public:
    InvalidTime(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) {}
};

namespace detail {
/// Return the current time in seconds
///
/// This function returns the "current" time in seconds from epoch
/// (00:00:00 January 1, 1970) as a 64-bit signed integer.  The return
/// value can represent a point of time before epoch as a negative number.
///
/// This function is provided to help test time conscious implementations
/// such as DNSSEC and TSIG signatures.  It is difficult to test them with
/// an unusual or a specifically chosen "current" via system-provided
/// library functions to get time.  This function acts as a straightforward
/// wrapper of such a library function, but provides test code with a hook
/// to return an arbitrary time value: if \c isc::util::detail::gettimeFunction
/// is set to a pointer of function that returns 64-bit signed integer,
/// \c gettimeWrapper() calls that function instead of the system library.
///
/// This hook variable is specifically intended for testing purposes, so,
/// even if it's visible outside of this library, it's not even declared in a
/// header file.
///
/// If the implementation doesn't need to be tested with faked current time,
/// it should simply use the system supplied library function instead of
/// this one.
int64_t gettimeWrapper();
}

///
/// \name DNSSEC time conversion functions.
///
/// These functions convert between times represented in seconds (in integer)
/// since epoch and those in the textual form used in the RRSIG records.
/// For integers we provide both 32-bit and 64-bit versions.
/// The RRSIG expiration and inception fields are both 32-bit unsigned
/// integers, so 32-bit versions would be more useful for protocol operations.
/// However, with 32-bit integers we need to take into account wrap-around
/// points and compare values using the serial number arithmetic as specified
/// in RFC4034, which would be more error prone.  We therefore provide 64-bit
/// versions, too.
///
/// The timezone is always UTC for these functions.
//@{
/// Convert textual DNSSEC time to integer, 64-bit version.
///
/// The textual form must only consist of digits and be in the form of
/// YYYYMMDDHHmmSS, where:
/// - YYYY must be between 1970 and 9999
/// - MM must be between 01 and 12
/// - DD must be between 01 and 31 and must be a valid day for the month
///   represented in 'MM'.  For example, if MM is 04, DD cannot be 31.
///   DD can be 29 when MM is 02 only when YYYY is a leap year.
/// - HH must be between 00 and 23
/// - mm must be between 00 and 59
/// - SS must be between 00 and 60
///
/// For all fields the range includes the begin and end values.  Note that
/// 60 is allowed for 'SS', intending a leap second, although in real operation
/// it's unlikely to be specified.
///
/// If the given text is valid, this function converts it to an unsigned
/// 64-bit number of seconds since epoch (1 January 1970 00:00:00) and returns
/// the converted value.  64 bits are sufficient to represent all possible
/// values for the valid format uniquely, so there is no overflow.
///
/// \note RFC4034 also defines the textual form of an unsigned decimal integer
/// for the corresponding time in seconds.  This function doesn't support
/// this form, and if given it throws an exception of class \c InvalidTime.
///
/// \exception InvalidTime The given textual representation is invalid.
///
/// \param time_txt Textual time in the form of YYYYMMDDHHmmSS
/// \return Seconds since epoch corresponding to \c time_txt
uint64_t
timeFromText64(const std::string& time_txt);

/// Convert textual DNSSEC time to integer, 32-bit version.
///
/// This version is the same as \c timeFromText64() except that the return
/// value is wrapped around to an unsigned 32-bit integer, simply dropping
/// the upper 32 bits.
uint32_t
timeFromText32(const std::string& time_txt);

/// Convert integral DNSSEC time to textual form, 64-bit version.
///
/// This function takes an integer that would be seconds since epoch and
/// converts it in the form of YYYYMMDDHHmmSS.  For example, if \c value is
/// 0, it returns "19700101000000".  If the value corresponds to a point
/// of time on and after year 10,000, which cannot be represented in the
/// YYYY... form, an exception of class \c InvalidTime will be thrown.
///
/// \exception InvalidTime The given time specifies on or after year 10,000.
/// \exception Other A standard exception, if resource allocation for the
/// returned text fails.
///
/// \param value Seconds since epoch to be converted.
/// \return Textual representation of \c value in the form of YYYYMMDDHHmmSS.
std::string
timeToText64(uint64_t value);

/// Convert integral DNSSEC time to textual form, 32-bit version.
///
/// This version is the same as \c timeToText64(), but the time value
/// is expected to be the lower 32 bits of the full 64-bit value.
/// These two will be different on and after a certain point of time
/// in year 2106, so this function internally resolves the ambiguity
/// using the current system time at the time of function call;
/// it first identifies the range of [N*2^32 - 2^31, N*2^32 + 2^31)
/// that contains the current time, and interprets \c value in the context
/// of that range.  It then applies the same process as \c timeToText64().
///
/// There is one important exception in this processing, however.
/// Until 19 Jan 2038 03:14:08 (2^31 seconds since epoch), this range
/// would contain time before epoch.  In order to ensure the returned
/// value is also a valid input to \c timeFromText, this function uses
/// a special range [0, 2^32) until that time.  As a result, all upper
/// half of the 32-bit values are treated as a future time.  For example,
/// 2^32-1 (the highest value in 32-bit unsigned integers) will be converted
/// to "21060207062815", instead of "19691231235959".
std::string
timeToText32(const uint32_t value);

//@}
}
}

#endif  // TIME_UTILITIES_H

// Local Variables:
// mode: c++
// End:
