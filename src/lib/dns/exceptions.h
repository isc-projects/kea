// Copyright (C) 2010-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

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

class Exception : public isc::Exception {
public:
    Exception(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) {}
};

///
/// \brief Base class for all sorts of text parse errors.
///
class DNSTextError : public isc::dns::Exception {
public:
    DNSTextError(const char* file, size_t line, const char* what) :
        isc::dns::Exception(file, line, what) {}
};

///
/// \brief Base class for name parser exceptions.
///
class NameParserException : public DNSTextError {
public:
    NameParserException(const char* file, size_t line, const char* what) :
        DNSTextError(file, line, what) {}
};

class DNSProtocolError : public isc::dns::Exception {
public:
    DNSProtocolError(const char* file, size_t line, const char* what) :
        isc::dns::Exception(file, line, what) {}
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
