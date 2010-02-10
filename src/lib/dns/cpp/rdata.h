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

#ifndef __RDATA_H
#define __RDATA_H 1

#include <stdint.h>

#include <boost/shared_ptr.hpp>

#include "name.h"

namespace isc {
namespace dns {
class InputBuffer;
class OutputBuffer;
class MessageRenderer;
class RRType;
class RRClass;
class Name;

namespace rdata {

///
/// \brief A standard DNS module exception that is thrown if RDATA parser
/// encounters an invalid or inconsistent data length.
///
class InvalidRdataLength : public Exception {
public:
    InvalidRdataLength(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) {}
};

///
/// \brief A standard DNS module exception that is thrown if RDATA parser
/// fails to recognize a given textual representation.
///
class InvalidRdataText : public Exception {
public:
    InvalidRdataText(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) {}
};

///
/// \brief A standard DNS module exception that is thrown if ...TBD
///
class CharStringTooLong : public Exception {
public:
    CharStringTooLong(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) {}
};

class Rdata;
typedef boost::shared_ptr<Rdata> RdataPtr;

/// \brief Possible maximum length of RDATA, which is the maximum unsigned
/// 16 bit value.
const size_t MAX_RDLENGTH = 65535;

/// Abstract RDATA class
class Rdata {
protected:
    Rdata() {}
private:
    /// Copy constructor is intentionally private.  Concrete classes should
    /// generally specialize their own versions of copy constructor.
    Rdata(const Rdata& source);
    void operator=(const Rdata& source);
public:
    virtual ~Rdata() {};

    ///
    /// \name Getter Methods
    //
    // need generic method for getting n-th field? c.f. ldns
    // e.g. string getField(int n);
    ///
    //@{
    // It's not yet clear if we really need to contain the RR type (and/or
    // RR class) in RDATA.
    //virtual const RRType& getType() const = 0;
    //@}

    ///
    /// \name Converter methods
    ///
    //@{
    virtual std::string toText() const = 0;
    virtual void toWire(OutputBuffer& buffer) const = 0;
    virtual void toWire(MessageRenderer& renderer) const = 0;
    //@}

    /// Note about implementation choice: the current implementation relies on
    /// dynamic_cast to ensure that the \c other is the same concrete Rdata
    /// class as \c this object.  Alternatively, we could first convert the
    /// data into wire-format and compare the pair as opaque data.  This would
    /// be more polymorphic, but might involve significant overhead, especially
    /// for a large size of RDATA.
    virtual int compare(const Rdata& other) const = 0;
};

namespace generic {
struct GenericImpl;

class Generic : public Rdata {
public:
    explicit Generic(const std::string& rdata_string);
    explicit Generic(InputBuffer& buffer, size_t rdata_len);
    Generic(const Generic& source);
    Generic& operator=(const Generic& source);
    virtual std::string toText() const;
    virtual void toWire(OutputBuffer& buffer) const;
    virtual void toWire(MessageRenderer& renderer) const;
    ///
    /// Note: the comparison is RR type/class agnostic: this method doesn't
    /// check whether the two Rdata objects to compare are of the comparable
    /// RR type/class.  The caller must ensure this condition.
    ///
    virtual int compare(const Rdata& other) const;
private:
    GenericImpl* impl_;
};

std::ostream&
operator<<(std::ostream& os, const Generic& rdata);
} // end of namespace "generic"

///
/// Non class-member functions related to Rdata
///
/// TBD: document them
RdataPtr createRdata(const RRType& rrtype, const RRClass& rrclass,
                     const std::string& rdata_string);
RdataPtr createRdata(const RRType& rrtype, const RRClass& rrclass,
                     InputBuffer& buffer, size_t len);
RdataPtr createRdata(const RRType& rrtype, const RRClass& rrclass,
                     const Rdata& source);

///
/// \brief Gives relative ordering of two names in terms of DNSSEC RDATA
/// ordering.
///
/// This method compares two names as defined in Sections 6.2 and 6.3 of
/// RFC4034: Comparing two names in their canonical form
/// (i.e., converting upper case ASCII characters to lower ones) and
/// as a left-justified unsigned octet sequence.  Note that the ordering is
/// different from that for owner names.  For example, "a.example" should be
/// sorted before "example" as RDATA, but the ordering is the opposite when
/// compared as owner names.
///
/// Normally, applications would not need this function directly.
/// This is mostly an internal helper function for \c Rdata related classes
/// to implement their \c compare() method.
/// This function is publicly open, however, for the convenience of
/// external developers who want to implement new or experimental RR types.
///
/// Additional note about applicability: In fact, BIND9's similar function,
/// \c dns_name_rdatacompare(), is only used in rdata implementations and
/// for testing purposes.
///
/// \param n1,n2 \c Name class objects to compare.
/// \return -1 if \c n1 would be sorted before \c n2.
/// \return 0 if \c n1 is identical to \c n2 in terms of sorting order.
/// \return 1 if \c n1 would be sorted after \c n2.
///
int
compareNames(const Name& n1, const Name& n2);

} // end of namespace "rdata"
}
}
#endif  // __RDATA_H

// Local Variables: 
// mode: c++
// End: 
