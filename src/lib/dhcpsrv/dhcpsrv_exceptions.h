// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef DHCPSRV_EXCEPTIONS_H
#define DHCPSRV_EXCEPTIONS_H

#include <exceptions/exceptions.h>

namespace isc {
namespace dhcp {

/// @brief Attempt to update lease that was not there
class NoSuchLease : public Exception {
public:
    NoSuchLease(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) {}
};


} // end of namespace isc::dhcp
} // end of namespace isc

#endif // DHCPSRV_EXCEPTIONS_H
