// Copyright (C) 2010  Internet Systems Consortium, Inc. ("ISC")
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

// XXX: we have another exceptions.h, so we need to use a prefix "DNS_" in
// the include guard.  More preferably, we should define a consistent naming
// style for the header guide (e.g. module-name_file-name_H) throughout the
// package.

#ifndef DNS_EXCEPTIONS_H
#define DNS_EXCEPTIONS_H 1

#include <exceptions/exceptions.h>

namespace isc {
namespace dns {

///
/// \brief A standard DNS module exception ...[TBD]
///
class Rcode;                    // forward declaration

class DNSProtocolError : public isc::Exception {
public:
    DNSProtocolError(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) {}
    virtual const Rcode& getRcode() const = 0;
};

class DNSMessageFORMERR : public DNSProtocolError {
public:
    DNSMessageFORMERR(const char* file, size_t line, const char* what) :
        DNSProtocolError(file, line, what) {}
    virtual const Rcode& getRcode() const;
};

class DNSMessageBADVERS : public DNSProtocolError {
public:
    DNSMessageBADVERS(const char* file, size_t line, const char* what) :
        DNSProtocolError(file, line, what) {}
    virtual const Rcode& getRcode() const;
};
}
}
#endif  // DNS_EXCEPTIONS_H

// Local Variables: 
// mode: c++
// End: 
