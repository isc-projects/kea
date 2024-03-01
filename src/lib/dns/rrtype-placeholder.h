// Copyright (C) 2010-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef RRTYPE_H
#define RRTYPE_H

#include <stdint.h>

#include <string>
#include <ostream>

#include <dns/exceptions.h>'
#include <util/buffer.h>

// Solaris x86 defines DS in <sys/regset.h>, which gets pulled in by Boost
#if defined(__sun) && defined(DS)
# undef DS
#endif

namespace isc {
namespace dns {

// forward declarations
class AbstractMessageRenderer;
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
    explicit RRType(isc::util::InputBuffer& buffer);
    ///
    /// We use the default copy constructor intentionally.
    //@}
    /// We use the default copy assignment operator intentionally.
    ///
    ///
    /// \name Getter Methods
    ///
    //@{
    /// \brief Returns the RR type code as a 16-bit unsigned integer.
    ///
    /// This method never throws an exception.
    ///
    /// \return An 16-bit integer code corresponding to the RRType.
    uint16_t getCode() const {
        return (typecode_);
    }
    //@}
    // BEGIN_WELL_KNOWN_TYPE_DECLARATIONS
    // END_WELL_KNOWN_TYPE_DECLARATIONS

private:
    uint16_t typecode_;
};

// BEGIN_WELL_KNOWN_TYPE_DEFINITIONS
// END_WELL_KNOWN_TYPE_DEFINITIONS
}
}
#endif  // RRTYPE_H
