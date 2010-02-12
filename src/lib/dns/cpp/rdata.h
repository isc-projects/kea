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
/// \brief A standard DNS module exception that is thrown if RDATA parser
/// parser encounters a character-string (as defined in RFC1035) exceeding
/// the maximum allowable length (\c MAX_CHARSTRING_LEN).
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

/// \brief The maximum allowable length of character-string containing in
/// RDATA as defined in RFC1035, not including the 1-byte length field.
const unsigned int MAX_CHARSTRING_LEN = 255;

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
    virtual ~Generic();
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

///
/// \brief Insert the name as a string into stream.
///
/// This method convert the \c rdata into a string and inserts it into the
/// output stream \c os.
///
/// This function overloads the global \c operator<< to behave as described in
/// \c ostream::operator<< but applied to \c generic::Generic Rdata objects.
///
/// \param os A \c std::ostream object on which the insertion operation is
/// performed.
/// \param rdata The \c Generic object output by the operation.
/// \return A reference to the same \c std::ostream object referenced by
/// parameter \c os after the insertion operation.
std::ostream&
operator<<(std::ostream& os, const Generic& rdata);
} // end of namespace "generic"

//
// Non class-member functions related to Rdata
//

///
/// \name Parameterized Polymorphic RDATA Factories
///
/// This set of global functions provide a unified interface to create an
/// \c Rdata object in a parameterized polymorphic way,
/// that is, these functions take a pair of \c RRType and \c RRClass
/// objects and data specific to that pair, and create an object of
/// the corresponding concrete derived class of \c Rdata.
///
/// These will be useful when parsing/constructing a DNS message or
/// parsing a master file, where information for a specific type of RDATA
/// is given but the resulting object, once created, should better be used
/// in a polymorphic way.
///
/// For example, if a master file parser encounters an NS RR
/// \verbatim example.com. 3600 IN NS ns.example.com.\endverbatim
/// it stores the text fragments "IN", "NS", and "ns.example.com." in
/// \c std::string objects \c class_txt, \c type_txt, and \c nsname_txt,
/// respectively, then it would create a new \c RdataPtr object as follows:
/// \code RdataPtr rdata = createRdata(RRType(type_txt), RRClass(class_txt),
///                              nsname_txt); \endcode
///
/// Internally, these functions uses the corresponding
/// \c RRParamRegistry::createRdata methods of the \c RRParamRegistry.
/// See also the description of about these methods for related notes.
//@{
/// \brief Create RDATA of a given pair of RR type and class from a string.
///
/// This method creates from a string an \c Rdata object of the given pair
/// of RR type and class.
///
/// \param rrtype An \c RRType object specifying the type/class pair.
/// \param rrclass An \c RRClass object specifying the type/class pair.
/// \param rdata_string A string of textual representation of the \c Rdata.
/// \return An \c RdataPtr object pointing to the created \c Rdata
/// object.
RdataPtr createRdata(const RRType& rrtype, const RRClass& rrclass,
                     const std::string& rdata_string);
/// \brief Create RDATA of a given pair of RR type and class from
/// wire-format data.
///
/// This method creates from wire-format binary data an \c Rdata object
/// of the given pair of RR type and class.
///
/// \c len must not exceed the protocol defined maximum value, \c MAX_RDLENGTH;
/// otherwise, an exception of class \c InvalidRdataLength will be thrown.
///
/// In some cases, the length of the RDATA is determined without the
/// information of \c len.  For example, the RDATA length of an IN/A RR
/// must always be 4.  If \c len is not equal to the actual length in such
/// cases, an exception of class InvalidRdataLength will be thrown.
///
/// \param rrtype An \c RRType object specifying the type/class pair.
/// \param rrclass An \c RRClass object specifying the type/class pair.
/// \param buffer A reference to an \c InputBuffer object storing the
/// \c Rdata to parse.
/// \param len The length in buffer of the \c Rdata.  In bytes.
/// \return An \c RdataPtr object pointing to the created \c Rdata
/// object.
RdataPtr createRdata(const RRType& rrtype, const RRClass& rrclass,
                     InputBuffer& buffer, size_t len);
/// \brief Create RDATA of a given pair of RR type and class, copying
/// of another RDATA of same kind.
///
/// This method creates an \c Rdata object of the given pair of
/// RR type and class, copying the  content of the given \c Rdata,
/// \c source.
///
/// \param rrtype An \c RRType object specifying the type/class pair.
/// \param rrclass An \c RRClass object specifying the type/class pair.
/// \param source A reference to an \c Rdata object whose content
/// is to be copied to the created \c Rdata object.
/// \return An \c RdataPtr object pointing to the created
/// \c Rdata object.
RdataPtr createRdata(const RRType& rrtype, const RRClass& rrclass,
                     const Rdata& source);
//@}

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
/// This function never throws an exception as long as the given names are
/// valid \c Name objects.
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
int compareNames(const Name& n1, const Name& n2);

} // end of namespace "rdata"
}
}
#endif  // __RDATA_H

// Local Variables: 
// mode: c++
// End: 
