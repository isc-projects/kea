// Copyright (C) 2012  Internet Systems Consortium, Inc. ("ISC")
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES WITH
// REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS.  IN NO EVENT SHALL ISC BE LIABLE FOR ANY SPECIAL, DIRECT,
// INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
// LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
// OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
// PERFORMANCE OF THIS SOFTWARE.

#ifndef DATASRC_EXCEPTIONS_H
#define DATASRC_EXCEPTIONS_H 1

#include <exceptions/exceptions.h>

namespace isc {
namespace datasrc {

/// This exception represents Backend-independent errors relating to
/// data source operations.
class DataSourceError : public Exception {
public:
    DataSourceError(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) {}
};

/// \brief No such serial number when obtaining difference iterator
///
/// Thrown if either the zone/start serial number or zone/end serial number
/// combination does not exist in the differences table.  (Note that this
/// includes the case where the differences table contains no records related
/// to that zone.)
class NoSuchSerial : public DataSourceError {
public:
    NoSuchSerial(const char* file, size_t line, const char* what) :
        DataSourceError(file, line, what) {}
};

/// Base class for a number of exceptions that are thrown while working
/// with zones.
struct ZoneException : public Exception {
    ZoneException(const char* file, size_t line, const char* what) :
        Exception(file, line, what)
    {}
};

/// Base class for a number of exceptions that are thrown when zones are
/// being loaded. This is a recoverable exception. It should be possible
/// to skip the bad zone and continue loading/serving other zones.
struct ZoneLoaderException : public ZoneException {
    ZoneLoaderException(const char* file, size_t line, const char* what) :
        ZoneException(file, line, what)
    {}
};

} // namespace datasrc
} // namespace isc

#endif // DATASRC_EXCEPTIONS

// Local Variables:
// mode: c++
// End:
