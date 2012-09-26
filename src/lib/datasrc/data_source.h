// Copyright (C) 2009  Internet Systems Consortium, Inc. ("ISC")
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

#ifndef __DATA_SOURCE_H
#define __DATA_SOURCE_H

#include <stdint.h>

#include <vector>

#include <boost/shared_ptr.hpp>

#include <exceptions/exceptions.h>

#include <dns/name.h>
#include <dns/rrclass.h>
#include <cc/data.h>

namespace isc {

namespace dns {
class Name;
class RRType;
class RRset;
class RRsetList;
}

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

}
}

#endif

// Local Variables:
// mode: c++
// End:
