// Copyright (C) 2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef DB_EXCEPTIONS_H
#define DB_EXCEPTIONS_H

#include <exceptions/exceptions.h>

namespace isc {
namespace dhcp {

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

};
};

#endif
