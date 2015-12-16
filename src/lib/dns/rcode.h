/*
 * Copyright (C) 2010-2015 Internet Systems Consortium, Inc. ("ISC")
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include <stdint.h>

#include <ostream>

#ifndef RCODE_H
#define RCODE_H 1

namespace isc {
namespace dns {

/// \brief DNS Response Codes (RCODEs) class.
///
/// The \c Rcode class objects represent standard Response Codes
/// (RCODEs) of the header section of DNS messages, and extended response
/// codes as defined in the EDNS specification.
///
/// Originally RCODEs were defined as 4-bit integers (RFC1035), and then
/// extended to 12 bits as part of the %EDNS specification (RFC2671).
/// This API uses the 12-bit version of the definition from the beginning;
/// applications don't have to aware of the original definition except when
/// dealing with the wire-format representation of the %EDNS OPT RR
/// (which is rare).
///
/// Like the \c Opcode class, Rcodes could be represented as bare integers,
/// but we define a separate class to benefit from C++ type safety.
///
/// For convenience we also provide
/// an enum type for pre-defined RCODE values, but it is generally advisable
/// to handle RCODEs through this class.  In fact, public interfaces of
/// this library uses this class to pass or return RCODEs instead of the
/// bare code values.
class Rcode {
public:
    /// Constants for pre-defined RCODE values.
    enum CodeValue {
        NOERROR_CODE = 0,       ///< 0: No error (RFC1035)
        FORMERR_CODE = 1,       ///< 1: Format error (RFC1035)
        SERVFAIL_CODE = 2,      ///< 2: Server failure (RFC1035)
        NXDOMAIN_CODE = 3,      ///< 3: Name Error (RFC1035)
        NOTIMP_CODE = 4,        ///< 4: Not Implemented (RFC1035)
        REFUSED_CODE = 5,       ///< 5: Refused (RFC1035)
        YXDOMAIN_CODE = 6,      ///< 6: Name unexpectedly exists (RFC2136)
        YXRRSET_CODE = 7,       ///< 7: RRset unexpectedly exists (RFC2136)
        NXRRSET_CODE = 8,       ///< 8: RRset should exist but not (RFC2136)
        NOTAUTH_CODE = 9,       ///< 9: Server isn't authoritative (RFC2136)
        NOTZONE_CODE = 10,      ///< 10: Name is not within the zone (RFC2136)
        RESERVED11_CODE = 11,   ///< 11: Reserved for future use (RFC1035)
        RESERVED12_CODE = 12,   ///< 12: Reserved for future use (RFC1035)
        RESERVED13_CODE = 13,   ///< 13: Reserved for future use (RFC1035)
        RESERVED14_CODE = 14,   ///< 14: Reserved for future use (RFC1035)
        RESERVED15_CODE = 15,   ///< 15: Reserved for future use (RFC1035)
        BADVERS_CODE = 16       ///< 16: EDNS version not implemented (RFC2671)
    };

    /// \name Constructors and Destructor
    ///
    /// We use the default versions of destructor, copy constructor,
    /// and assignment operator.
    ///
    /// The default constructor is hidden as a result of defining the other
    /// constructors.  This is intentional; we don't want to allow an
    /// \c Rcode object to be constructed with an invalid state.
    //@{
    /// \brief Constructor from the code value.
    ///
    /// Since RCODEs are 12-bit values, parameters larger than 0xfff are
    /// invalid.
    /// If \c code is larger than 0xfff an exception of class
    /// \c isc::OutOfRange will be thrown.
    ///
    /// \param code The underlying 12-bit code value of the \c Rcode.
    explicit Rcode(const uint16_t code);

    /// \brief Constructor from a pair of base and extended parts of code.
    ///
    /// This constructor takes two parameters, one for the lower 4 bits of
    /// the code value, the other for the upper 8 bits, and combines them
    /// to build a complete 12-bit code value.
    ///
    /// The first parameter, \c code, is the lower 4 bits, and therefore must
    /// not exceed 15.  Otherwise, an exception of class
    /// \c isc::OutOfRange will be thrown.
    ///
    /// This version of constructor is provided specifically for constructing
    /// an Rcode from a DNS header and an %EDNS OPT RR.  Normal applications
    /// won't have to use this constructor.
    ///
    /// \param code The lower 4 bits of the underlying code value.
    /// \param extended_code The upper 8 bits of the underlying code value.
    Rcode(const uint8_t code, const uint8_t extended_code);
    //@}

    /// \brief Returns the \c Rcode code value.
    ///
    /// This method never throws an exception.
    ///
    /// \return The underlying code value corresponding to the \c Rcode.
    uint16_t getCode() const { return (code_); }

    /// \brief Returns the upper 8-bit of the \c Rcode code value.
    ///
    /// Normal applications won't have to use this method.  This is provided
    /// in case the upper 8 bits are necessary for the EDNS protocol
    /// processing.
    ///
    /// This method never throws an exception.
    ///
    /// \return The upper 8-bit of the underlying code value.
    uint8_t getExtendedCode() const;

    /// \brief Return true iff two Rcodes are equal.
    ///
    /// Two Rcodes are equal iff their type codes are equal.
    ///
    /// This method never throws an exception.
    ///
    /// \param other the \c Rcode object to compare against.
    /// \return true if the two Rcodes are equal; otherwise false.
    bool equals(const Rcode& other) const
    { return (code_ == other.code_); }

    /// \brief Same as \c equals().
    bool operator==(const Rcode& other) const { return (equals(other)); }

    /// \brief Return true iff two Rcodes are not equal.
    ///
    /// This method never throws an exception.
    ///
    /// \param other the \c Rcode object to compare against.
    /// \return true if the two Rcodes are not equal; otherwise false.
    bool nequals(const Rcode& other) const
    { return (code_ != other.code_); }

    /// \brief Same as \c nequals().
    bool operator!=(const Rcode& other) const { return (nequals(other)); }

    /// \brief Convert the \c Rcode to a string.
    ///
    /// For pre-defined code values (see Rcode::CodeValue),
    /// this method returns a string representation of the "mnemonic' used
    /// for the enum and constant objects.  For example, the string for
    /// code value 0 is "NOERROR", etc.
    /// For other code values it returns a string representation of the decimal
    /// number of the value, e.g. "32", "100", etc.
    ///
    /// If resource allocation for the string fails, a corresponding standard
    /// exception will be thrown.
    ///
    /// \return A string representation of the \c Rcode.
    std::string toText() const;

    /// A constant object for the NOERROR Rcode (see \c Rcode::NOERROR_CODE).
    static const Rcode& NOERROR();

    /// A constant object for the FORMERR Rcode (see \c Rcode::FORMERR_CODE).
    static const Rcode& FORMERR();

    /// A constant object for the SERVFAIL Rcode (see \c Rcode::SERVFAIL_CODE).
    static const Rcode& SERVFAIL();

    /// A constant object for the NXDOMAIN Rcode (see \c Rcode::NXDOMAIN_CODE).
    static const Rcode& NXDOMAIN();

    /// A constant object for the NOTIMP Rcode (see \c Rcode::NOTIMP_CODE).
    static const Rcode& NOTIMP();

    /// A constant object for the REFUSED Rcode (see \c Rcode::REFUSED_CODE).
    static const Rcode& REFUSED();

    /// A constant object for the YXDOMAIN Rcode (see \c Rcode::YXDOMAIN_CODE).
    static const Rcode& YXDOMAIN();

    /// A constant object for the YXRRSET Rcode (see \c Rcode::YXRRSET_CODE).
    static const Rcode& YXRRSET();

    /// A constant object for the NXRRSET Rcode (see \c Rcode::NXRRSET_CODE).
    static const Rcode& NXRRSET();

    /// A constant object for the NOTAUTH Rcode (see \c Rcode::NOTAUTH_CODE).
    static const Rcode& NOTAUTH();

    /// A constant object for the NOTZONE Rcode (see \c Rcode::NOTZONE_CODE).
    static const Rcode& NOTZONE();

    /// A constant object for a reserved (code 11) Rcode.
    /// (see \c Rcode::RESERVED11_CODE).
    static const Rcode& RESERVED11();

    /// A constant object for a reserved (code 12) Rcode.
    /// (see \c Rcode::RESERVED12_CODE).
    static const Rcode& RESERVED12();

    /// A constant object for a reserved (code 13) Rcode.
    /// (see \c Rcode::RESERVED13_CODE).
    static const Rcode& RESERVED13();

    /// A constant object for a reserved (code 14) Rcode.
    /// (see \c Rcode::RESERVED14_CODE).
    static const Rcode& RESERVED14();

    /// A constant object for a reserved (code 15) Rcode.
    /// (see \c Rcode::RESERVED15_CODE).
    static const Rcode& RESERVED15();

    /// A constant object for the BADVERS Rcode (see \c Rcode::BADVERS_CODE).
    static const Rcode& BADVERS();
private:
    uint16_t code_;
};

inline const Rcode&
Rcode::NOERROR() {
    static Rcode c(0);
    return (c);
}

inline const Rcode&
Rcode::FORMERR() {
    static Rcode c(1);
    return (c);
}

inline const Rcode&
Rcode::SERVFAIL() {
    static Rcode c(2);
    return (c);
}

inline const Rcode&
Rcode::NXDOMAIN() {
    static Rcode c(3);
    return (c);
}

inline const Rcode&
Rcode::NOTIMP() {
    static Rcode c(4);
    return (c);
}

inline const Rcode&
Rcode::REFUSED() {
    static Rcode c(5);
    return (c);
}

inline const Rcode&
Rcode::YXDOMAIN() {
    static Rcode c(6);
    return (c);
}

inline const Rcode&
Rcode::YXRRSET() {
    static Rcode c(7);
    return (c);
}

inline const Rcode&
Rcode::NXRRSET() {
    static Rcode c(8);
    return (c);
}

inline const Rcode&
Rcode::NOTAUTH() {
    static Rcode c(9);
    return (c);
}

inline const Rcode&
Rcode::NOTZONE() {
    static Rcode c(10);
    return (c);
}

inline const Rcode&
Rcode::RESERVED11() {
    static Rcode c(11);
    return (c);
}

inline const Rcode&
Rcode::RESERVED12() {
    static Rcode c(12);
    return (c);
}

inline const Rcode&
Rcode::RESERVED13() {
    static Rcode c(13);
    return (c);
}

inline const Rcode&
Rcode::RESERVED14() {
    static Rcode c(14);
    return (c);
}

inline const Rcode&
Rcode::RESERVED15() {
    static Rcode c(15);
    return (c);
}

inline const Rcode&
Rcode::BADVERS() {
    static Rcode c(16);
    return (c);
}

/// \brief Insert the \c Rcode as a string into stream.
///
/// This method convert \c rcode into a string and inserts it into the
/// output stream \c os.
///
/// \param os A \c std::ostream object on which the insertion operation is
/// performed.
/// \param rcode A reference to an \c Rcode object output by the operation.
/// \return A reference to the same \c std::ostream object referenced by
/// parameter \c os after the insertion operation.
std::ostream& operator<<(std::ostream& os, const Rcode& rcode);
}
}
#endif  // RCODE_H

// Local Variables: 
// mode: c++
// End: 
