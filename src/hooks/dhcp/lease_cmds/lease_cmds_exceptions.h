// Copyright (C) 2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <exceptions/exceptions.h>

#ifndef LEASE_CMDS_EXCEPTIONS_H
#define LEASE_CMDS_EXCEPTIONS_H

/// @brief Exception thrown when a command failed due to a conflict.
///
/// It is thrown in a situation when a command is well-formed but cannot
/// be processed because its arguments are in conflict with the current
/// server configuration or state. A conflict can occur for a particular
/// lease, or for many leases (e.g., wrong subnet identifier used by the
/// caller).
class LeaseCmdsConflict : public isc::Exception {
public:
    LeaseCmdsConflict(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) { };
};

#endif // LEASE_CMDS_EXCEPTIONS_H
