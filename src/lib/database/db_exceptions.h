// Copyright (C) 2015-2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef DB_EXCEPTIONS_H
#define DB_EXCEPTIONS_H

#include <exceptions/exceptions.h>

namespace isc {
namespace db {

/// @brief Database statement not applied
///
/// Cassandra have a concept of mutation (any statement that does change the
/// data, like INSERT, UPDATE or DELETE). Under certain conditions it may be
/// possible that those statements may fail to apply.
struct StatementNotApplied : public Exception {
    StatementNotApplied(const char* file, size_t line, const char* what)
        : Exception(file, line, what) {
    }
};

/// @brief Zero or multiple records found where one expected
struct SingleRecordException : public Exception {
    SingleRecordException(const char* file, size_t line, const char* what)
        : Exception(file, line, what) {
    }
};

/// @brief Zero records found where one expected
struct ZeroRecords : public SingleRecordException {
    ZeroRecords(const char* file, size_t line, const char* what)
        : SingleRecordException(file, line, what) {
    }
};

/// @brief Multiple records found where one expected
struct MultipleRecords : public SingleRecordException {
    MultipleRecords(const char* file, size_t line, const char* what)
        : SingleRecordException(file, line, what) {
    }
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

/// @brief Invalid address family used as input to Lease Manager.
class InvalidAddressFamily : public Exception {
public:
    InvalidAddressFamily(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) {}
};

/// @brief Error detected in the database configuration.
class DbConfigError : public Exception {
public:
    DbConfigError(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) {}
};

/// @brief Error when specified database could not be found in the server
/// configuration.
class NoSuchDatabase :  public Exception {
public:
    NoSuchDatabase(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) {}
};

/// @brief Specification of the database backend to be used yields
/// multiple results.
class AmbiguousDatabase :  public Exception {
public:
    AmbiguousDatabase(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) {}
};

}  // namespace isc
}  // namespace db

#endif
