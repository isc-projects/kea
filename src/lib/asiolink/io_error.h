// Copyright (C) 2011-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.


#ifndef IO_ERROR_H
#define IO_ERROR_H

#include <exceptions/exceptions.h>

namespace isc {
namespace asiolink {

/// \brief An exception that is thrown if an error occurs within the IO
/// module.  This is mainly intended to be a wrapper exception class for
/// ASIO specific exceptions.
class IOError : public isc::Exception {
public:
    IOError(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) {}
};


} // namespace asiolink
} // namespace isc

#endif // IO_ERROR_H
