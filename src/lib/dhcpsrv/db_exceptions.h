// Copyright (C) 2015-2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef DB_EXCEPTIONS_H
#define DB_EXCEPTIONS_H

#include <exceptions/exceptions.h>

namespace isc {
namespace dhcp {

/// @brief Database statement not applied
///
/// Cassandra have a concept of mutation (any statement that does change the
/// data, like INSERT, UPDATE or DELETE). Under certain conditions it may be
/// possible that those statesments may fail to apply.
class StatementNotApplied : public Exception {
public:
    StatementNotApplied(const char* file, size_t line, const char* what)
        : isc::Exception(file, line, what) {
    }
};

/// @brief Multiple lease records found where one expected
class MultipleRecords : public Exception {
public:
    MultipleRecords(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) {}
};

/// @brief Attempt to update lease that was not there
class NoSuchLease : public Exception {
public:
    NoSuchLease(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) {}
};

/// @brief Data is truncated
class DataTruncated : public Exception {
public:
    DataTruncated(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) {}
};

/// @brief Database duplicate entry error
class DuplicateEntry : public Exception {
public:
    DuplicateEntry(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) {}
};

/// @brief Attempt to modify data in read-only database.
class ReadOnlyDb : public Exception {
public:
    ReadOnlyDb(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) {}
};

/// @brief Upper bound address is lower than lower bound address while
/// retrieving a range of leases.
class InvalidRange : public Exception {
public:
    InvalidRange(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) {}
};

}  // namespace isc
}  // namespace dhcp

#endif
