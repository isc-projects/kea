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

#ifndef __RRTTL_H
#define __RRTTL_H 1

#include "exceptions.h"

namespace isc {
namespace dns {

// forward declarations
class InputBuffer;
class OutputBuffer;
class MessageRenderer;

///
/// \brief TBD
///
class InvalidRRTTL : public Exception {
public:
    InvalidRRTTL(const char* file, size_t line, const char* what) :
        isc::dns::Exception(file, line, what) {}
};

///
/// \brief A standard DNS module exception that is thrown if an RRTTL object
/// is being constructed from a incomplete (too short) wire-format data.
///
class IncompleteRRTTL : public Exception {
public:
    IncompleteRRTTL(const char* file, size_t line, const char* what) :
        isc::dns::Exception(file, line, what) {}
};

class RRTTL {
public:
    ///
    /// \name Constructors and Destructor
    ///
    //@{
    explicit RRTTL(uint32_t ttlval) : ttlval_(ttlval) {}
    ///
    /// TODO: this version only accepts decimal TTL values.  We'll extend
    /// it so that we can accept more convenient ones such as "2H" or "1D".
    explicit RRTTL(const std::string& ttlstr);
    /// Constructor from wire-format data.
    ///
    /// The \c buffer parameter normally stores a complete DNS message
    /// containing the RRTTL to be constructed.  The current read position of
    /// the buffer points to the head of the type.
    ///
    /// If the given data does not large enough to contain a 16-bit integer,
    /// an exception of class \c IncompleteRRTTL will be thrown.
    ///
    /// \param buffer A buffer storing the wire format data.
    explicit RRTTL(InputBuffer& buffer);
    ///
    /// We use the default copy constructor intentionally.
    //@}
    /// We use the default copy assignment operator intentionally.
    ///
    const std::string toText() const;
    void toWire(OutputBuffer& buffer) const;
    void toWire(MessageRenderer& renderer) const;
    uint32_t getValue() const { return (ttlval_); }

    ///
    /// \name Comparison methods
    ///
    //@{
    bool equals(const RRTTL& other) const
    { return (ttlval_ == other.ttlval_); }
    bool operator==(const RRTTL& other) const
    { return (ttlval_ == other.ttlval_); }
    bool nequals(const RRTTL& other) const
    { return (ttlval_ != other.ttlval_); }
    bool operator!=(const RRTTL& other) const
    { return (ttlval_ != other.ttlval_); }
    bool leq(const RRTTL& other) const
    { return (ttlval_ <= other.ttlval_); }
    bool geq(const RRTTL& other) const
    { return (ttlval_ >= other.ttlval_); }
    bool operator>=(const RRTTL& other) const
    { return (ttlval_ >= other.ttlval_); }
    bool operator<=(const RRTTL& other) const
    { return (ttlval_ <= other.ttlval_); }
    bool lthan(const RRTTL& other) const
    { return (ttlval_ < other.ttlval_); }
    bool operator<(const RRTTL& other) const
    { return (ttlval_ < other.ttlval_); }
    bool gthan(const RRTTL& other) const
    { return (ttlval_ > other.ttlval_); }
    bool operator>(const RRTTL& other) const
    { return (ttlval_ > other.ttlval_); }
    //@}

private:
    uint32_t ttlval_;
};

std::ostream&
operator<<(std::ostream& os, const RRTTL& rrtype);
}
}
#endif  // __RRTTL_H

// Local Variables: 
// mode: c++
// End: 
