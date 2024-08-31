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

/// @brief Missing node error
struct MissingNode : public Exception {
    MissingNode(const char* file, size_t line, const char* what) :
        Exception(file, line, what)
    {}
};  // MissingNode

/// @brief Missing key error
struct MissingKey : public MissingNode {
    MissingKey(const char* file, size_t line, const char* what) :
        MissingNode(file, line, what)
    {}
};  // MissingKey

/// @brief Generic NETCONF error
struct NetconfError : public Exception {
    NetconfError(const char* file, size_t line, const char* what) :
        Exception(file, line, what)
    {}
};  // NetconfError

}  // namespace yang
}  // namespace isc

#endif  // ISC_SYSREPO_ERROR_H
