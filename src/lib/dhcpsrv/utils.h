// Copyright (C) 2012-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

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

}; // namespace isc::dhcp
}; // namespace isc

#endif // DHCPSRV_UTILS_H
