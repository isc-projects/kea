// Copyright (C) 2015-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef DB_EXCEPTIONS_H
#define DB_EXCEPTIONS_H

#include <exceptions/exceptions.h>

namespace isc {
namespace db {

/// @brief Multiple lease records found where one expected
class MultipleRecords : public Exception {
public:
    MultipleRecords(const char* file, size_t line, const char* what) :
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

/// @brief Key is NULL but was specified NOT NULL
class NullKeyError : public Exception {
public:
    NullKeyError(const char* file, size_t line, const char* what) :
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

/// @brief Thrown when it is expected that some rows are affected,
/// usually during a DELETE or an UPDATE, but none are.
class NoRowsAffected : public Exception {
public:
    NoRowsAffected(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) {}
};

}  // namespace isc
}  // namespace db

#endif
