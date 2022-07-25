// Copyright (C) 2018-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef ISC_SYSREPO_ERROR_H
#define ISC_SYSREPO_ERROR_H 1

#include <exceptions/exceptions.h>

namespace isc {
namespace yang {

/// @brief Sysrepo error.
class SysrepoError : public isc::Exception {
public:
    SysrepoError(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what)
    {}
};

}  // end of namespace isc::yang
}  // end of namespace isc

#endif // ISC_SYSREPO_ERROR_H
