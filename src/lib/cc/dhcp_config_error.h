// Copyright (C) 2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef DHCP_CONFIG_ERROR_H
#define DHCP_CONFIG_ERROR_H

#include <exceptions/exceptions.h>

namespace isc {
namespace dhcp {

/// An exception that is thrown if an error occurs while configuring
/// DHCP server.
class DhcpConfigError : public isc::Exception {
public:

    /// @brief constructor
    ///
    /// @param file name of the file, where exception occurred
    /// @param line line of the file, where exception occurred
    /// @param what text description of the issue that caused exception
    DhcpConfigError(const char* file, size_t line, const char* what)
        : isc::Exception(file, line, what) {}
};

}; // end of isc::dhcp namespace
}; // end of isc namespace

#endif // DHCP_CONFIG_ERROR_H

