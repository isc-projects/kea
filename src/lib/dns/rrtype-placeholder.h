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

// $Id: rrtype.h 534 2010-01-26 23:08:23Z jinmei $

#ifndef __RRTYPE_H
#define __RRTYPE_H 1

#include <stdint.h>

#include <string>
#include <ostream>

#include <exceptions/exceptions.h>

namespace isc {
namespace dns {

// forward declarations
class InputBuffer;
class OutputBuffer;
class MessageRenderer;

///
/// \brief A standard DNS module exception that is thrown if an RRType object
/// is being constructed from an unrecognized string.
///
class InvalidRRType : public Exception {
public:
    InvalidRRType(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) {}
};

///
/// \brief A standard DNS module exception that is thrown if an RRType object
/// is being constructed from a incomplete (too short) wire-format data.
///
class IncompleteRRType : public Exception {
public:
    IncompleteRRType(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) {}
};

///
/// The \c RRType class encapsulates DNS resource record types.
///
/// This class manages the 16-bit integer type codes in quite a straightforward
/// way.  The only non trivial task is to handle textual representations of
/// RR types, such as "A", "AAAA", or "TYPE65534".
///
/// This class consults a helper \c RRParamRegistry class, which is a registry
/// of RR related parameters and has the singleton object.  This registry
/// provides a mapping between RR type codes and their "well-known" textual
/// representations.
/// Parameters of RR types defined by DNS protocol standards are automatically
/// registered at initialization time and are ensured to be always available for
/// applications unless the application explicitly modifies the registry.
///
/// For convenience, this class defines constant class objects corresponding to
/// standard RR types.  These are generally referred to as the form of
/// <code>RRType::{type-text}()</code>.
/// For example, \c RRType::NS() is an \c RRType object corresponding to the NS
/// resource record (type code 2).
/// Note that these constants are used through a "proxy" function.
/// This is because they may be used to initialize another non-local (e.g.
/// global or namespace-scope) static object as follows:
///
/// \code
/// namespace foo {
/// const RRType default_type = RRType::A();
/// } \endcode
///
/// In order to ensure that the constant RRType object has been initialized
/// before the initialization for \c default_type, we need help from
/// the proxy function.
///
/// In the current implementation, the initialization of the well-known
/// static objects is not thread safe.  The same consideration as the
/// \c RRParamRegistry class applies.  We may extend the implementation so
/// that the initialization is ensured to be thread safe in a future version.
///
/// Note to developers: since it's expected that some of these constant
/// \c RRType objects are frequently used in a performance sensitive path,
/// we define these proxy functions as inline.  This makes sense only when
/// the corresponding static objects are defined only once even if they used
/// in different source files.  Sufficiently modern compilers should meet
/// this assumption, but if we encounter memory bloat due to this problem with
/// particular compilers we need to revisit the design or think about
/// workaround.
class RRType {
public:
    ///
    /// \name Constructors and Destructor
    ///
    //@{
    /// Constructor from an integer type code.
    ///
    /// This constructor never throws an exception.
    ///
    /// \param typecode An 16-bit integer code corresponding to the RRType.
    explicit RRType(uint16_t typecode) : typecode_(typecode) {}
    /// Constructor from a string.
    ///
    /// A valid string is one of "well-known" textual type representations
    /// such as "A", "AAAA", or "NS", or in the standard format for "unknown"
    /// RR types as defined in RFC3597, i.e., "TYPEnnnn".
    ///
    /// More precisely, the "well-known" representations are the ones stored
    /// in the \c RRParamRegistry registry (see the class description).
    ///
    /// As for the format of "TYPEnnnn", "nnnn" must represent a valid 16-bit
    /// unsigned integer, which may contain leading 0's as long as it consists
    /// of at most 5 characters (inclusive).
    /// For example, "TYPE1" and "TYPE001" are valid and represent the same
    /// RR type, but "TYPE65536" and "TYPE000001" are invalid.
    /// A "TYPEnnnn" representation is valid even if the corresponding type code
    /// is registered in the \c RRParamRegistry object.  For example, both
    /// "A" and "TYPE1" are valid and represent the same RR type.
    ///
    /// All of these representations are case insensitive; "NS" and "ns", and
    /// "TYPE1" and "type1" are all valid and represent the same RR types,
    /// respectively.
    ///
    /// If the given string is not recognized as a valid representation of
    /// an RR type, an exception of class \c InvalidRRType will be thrown.
    ///
    /// \param typestr A string representation of the \c RRType
    explicit RRType(const std::string& typestr);
    /// Constructor from wire-format data.
    ///
    /// The \c buffer parameter normally stores a complete DNS message
    /// containing the RRType to be constructed.  The current read position of
    /// the buffer points to the head of the type.
    ///
    /// If the given data does not large enough to contain a 16-bit integer,
    /// an exception of class \c IncompleteRRType will be thrown.
    ///
    /// \param buffer A buffer storing the wire format data.
    explicit RRType(InputBuffer& buffer);
    ///
    /// We use the default copy constructor intentionally.
    //@}
    /// We use the default copy assignment operator intentionally.
    ///

    ///
    /// \name Converter methods
    ///
    //@{
    /// \brief Convert the \c RRType to a string.
    ///
    /// If a "well known" textual representation for the type code is registered
    /// in the RR parameter registry (see the class description), that will be
    /// used as the return value of this method.  Otherwise, this method creates
    /// a new string for an "unknown" RR type in the format defined in RFC3597,
    /// i.e., "TYPEnnnn", and returns it.
    ///
    /// If resource allocation for the string fails, a corresponding standard
    /// exception will be thrown.
    ///
    /// \return A string representation of the \c RRType.
    const std::string toText() const;
    /// \brief Render the \c RRType in the wire format.
    ///
    /// This method renders the type code in network byte order via \c renderer,
    /// which encapsulates output buffer and other rendering contexts.
    ///
    /// If resource allocation in rendering process fails, a corresponding
    /// standard exception will be thrown.
    ///
    /// \param buffer An output buffer to store the wire data.
    void toWire(MessageRenderer& renderer) const;
    /// \brief Render the \c RRType in the wire format.
    ///
    /// This method renders the type code in network byte order into the
    /// \c buffer.
    ///
    /// If resource allocation in rendering process fails, a corresponding
    /// standard exception will be thrown.
    ///
    /// \param renderer DNS message rendering context that encapsulates the
    /// output buffer in which the RRType is to be stored.
    void toWire(OutputBuffer& buffer) const;
    //@}

    ///
    /// \name Getter Methods
    ///
    //@{
    /// \brief Returns the RR type code as a 16-bit unsigned integer.
    ///
    /// This method never throws an exception.
    ///
    /// \return An 16-bit integer code corresponding to the RRType.
    uint16_t getCode() const { return (typecode_); }
    //@}

    ///
    /// \name Comparison methods
    ///
    //@{
    /// \brief Return true iff two RRTypes are equal.
    ///
    /// Two RRTypes are equal iff their type codes are equal.
    ///
    /// This method never throws an exception.
    ///
    /// \param other the \c RRType object to compare against.
    /// \return true if the two RRTypes are equal; otherwise false.
    bool equals(const RRType& other) const
    { return (typecode_ == other.typecode_); }
    /// \brief Same as \c equals().
    bool operator==(const RRType& other) const { return (equals(other)); }

    /// \brief Return true iff two RRTypes are equal.
    ///
    /// This method never throws an exception.
    ///
    /// \param other the \c RRType object to compare against.
    /// \return true if the two RRTypes are not equal; otherwise false.
    bool nequals(const RRType& other) const 
    { return (typecode_ != other.typecode_); }
    /// \brief Same as \c nequals().
    bool operator!=(const RRType& other) const { return (nequals(other)); }
 
    /// \brief Less-than comparison for RRType against \c other
    ///
    /// We define the less-than relationship based on their type codes;
    /// one RRType is less than the other iff the code of the former is less
    /// than that of the other as unsigned integers.
    /// The relationship is meaningless in terms of DNS protocol; the only
    /// reason we define this method is that RRType objects can be stored in
    /// STL containers without requiring user-defined less-than relationship.
    /// We therefore don't define other comparison operators.
    ///
    /// This method never throws an exception.
    ///
    /// \param other the \c RRType object to compare against.
    /// \return true if \c this RRType is less than the \c other; otherwise
    /// false.
    bool operator<(const RRType& other) const
    { return (typecode_ < other.typecode_); }
    //@}

    // BEGIN_WELL_KNOWN_TYPE_DECLARATIONS
    // END_WELL_KNOWN_TYPE_DECLARATIONS

    static const RRType& IXFR();
    static const RRType& AXFR();
    static const RRType& ANY();

private:
    // \brief Meta-classes
    // XXX: these should be implemented using rrparamregistry
    enum {
        RRTYPE_IXFR = 251,
        RRTYPE_AXFR = 252,
        RRTYPE_ANY = 255
    };

    uint16_t typecode_;
};

// BEGIN_WELL_KNOWN_TYPE_DEFINITIONS
// END_WELL_KNOWN_TYPE_DEFINITIONS

inline const RRType&
RRType::IXFR()
{
    static RRType rrtype(RRTYPE_IXFR);
    return (rrtype);
}

inline const RRType&
RRType::AXFR()
{
    static RRType rrtype(RRTYPE_AXFR);
    return (rrtype);
}

inline const RRType&
RRType::ANY()
{
    static RRType rrtype(RRTYPE_ANY);
    return (rrtype);
}

///
/// \brief Insert the \c RRType as a string into stream.
///
/// This method convert the \c rrtype into a string and inserts it into the
/// output stream \c os.
///
/// This function overloads the global operator<< to behave as described in
/// ostream::operator<< but applied to \c RRType objects.
///
/// \param os A \c std::ostream object on which the insertion operation is
/// performed.
/// \param rrtype The \c RRType object output by the operation.
/// \return A reference to the same \c std::ostream object referenced by
/// parameter \c os after the insertion operation.
std::ostream&
operator<<(std::ostream& os, const RRType& rrtype);
}
}
#endif  // __RRTYPE_H

// Local Variables: 
// mode: c++
// End: 
