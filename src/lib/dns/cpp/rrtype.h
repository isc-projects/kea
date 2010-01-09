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

// $Id$

#ifndef __RRTYPE_H
#define __RRTYPE_H 1

#include "exceptions.h"

namespace isc {
namespace dns {

// forward declarations
class OutputBuffer;
class MessageRenderer;

///
/// \brief TBD
///
class InvalidRRType : public Exception {
public:
    InvalidRRType(const char* file, size_t line, const char* what) :
        isc::dns::Exception(file, line, what) {}
};

class RRType {
public:
    ///
    /// \name Constructors and Destructor
    ///
    //@{
    explicit RRType(uint16_t typecode) : typecode_(typecode) {}
    explicit RRType(const std::string& typestr);
    ///
    /// We use the default copy constructor intentionally.
    //@}
    /// We use the default copy assignment operator intentionally.
    ///
    const std::string toText() const;
    void toWire(OutputBuffer& buffer) const;
    void toWire(MessageRenderer& renderer) const;
    uint16_t getCode() const { return (typecode_); }
    bool operator==(const RRType& other) const
    { return (typecode_ == other.typecode_); }
    bool operator!=(const RRType& other) const
    { return (typecode_ != other.typecode_); }
    ///
    /// We define this so that RRTypes can be stored in STL containers.
    ///
    bool operator<(const RRType& other) const
    { return (typecode_ < other.typecode_); }

    // (Some) Well-known RRtype constants
    static const RRType& A();
    static const RRType& NS();
    static const RRType& SOA();
    static const RRType& MX();
    static const RRType& TXT();
    static const RRType& AAAA();

private:
    uint16_t typecode_;
};

// We'll probably auto generate this code.  But in this preliminary version
// we simply hard code some selected types.
inline const RRType&
RRType::A()
{
    static RRType rrtype(1);

    return (rrtype);
}

std::ostream&
operator<<(std::ostream& os, const RRType& rrtype);
}
}
#endif  // __RRTYPE_H

// Local Variables: 
// mode: c++
// End: 
