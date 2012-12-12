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

#include <datasrc/client.h>

#include <exceptions/exceptions.h>

/// This file defines a few default implementations for methods.
///
/// While some of the detail of the API are worked out, we define
/// default implementations to ease development for some of the
/// more tentative methods (those that are not (yet) pure virtual)
/// They should all throw NotImplemented

namespace isc {
namespace datasrc {

ZoneIteratorPtr
DataSourceClient::getIterator(const isc::dns::Name&, bool) const {
    isc_throw(isc::NotImplemented,
              "Data source doesn't support iteration");
}

unsigned int
DataSourceClient::getZoneCount() const {
    isc_throw(isc::NotImplemented,
              "Data source doesn't support getZoneCount");
}

bool
DataSourceClient::createZone(const dns::Name&) {
    isc_throw(isc::NotImplemented,
              "Data source doesn't support addZone");
}


} // end namespace datasrc
} // end namespace isc
