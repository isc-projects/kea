// Copyright (C) 2012 Internet Systems Consortium, Inc. ("ISC")
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

#ifndef DHCPSRV_UTILS_H
#define DHCPSRV_UTILS_H

#include <exceptions/exceptions.h>

namespace isc {
namespace dhcp {

/// An exception that is thrown if a DHCPv6 protocol violation occurs while
/// processing a message (e.g. a mandatory option is missing)
class RFCViolation : public isc::Exception {
public:

/// @brief constructor
///
/// @param file name of the file, where exception occurred
/// @param line line of the file, where exception occurred
/// @param what text description of the issue that caused exception
RFCViolation(const char* file, size_t line, const char* what) :
    isc::Exception(file, line, what) {}
};

class ServerID_mismatch : public isc::Exception {
public:

/// @brief constructor
///
/// @param file name of the file, where exception occurred
/// @param line line of the file, where exception occurred
/// @param what text description of the issue that caused exception
ServerID_mismatch(const char* file, size_t line, const char* what) :
    isc::Exception(file, line, what) {}
};




}; // namespace isc::dhcp
}; // namespace isc

#endif // DHCPSRV_UTILS_H
