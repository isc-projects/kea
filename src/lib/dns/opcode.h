/*
 * Copyright (C) 2010-2015 Internet Systems Consortium, Inc. ("ISC")
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include <stdint.h>

#include <ostream>

#ifndef OPCODE_H
#define OPCODE_H 1

namespace isc {
namespace dns {

/// \brief The \c Opcode class objects represent standard OPCODEs
/// of the header section of DNS messages as defined in RFC1035.
///
/// This is a straightforward value class encapsulating the OPCODE code
/// values.  Since OPCODEs are 4-bit integers that are used in limited
/// places and it's unlikely that new code values will be assigned, we could
/// represent them as simple integers (via constant variables or enums).
/// However, we define a separate class so that we can benefit from C++
/// type safety as much as possible.  For convenience we also provide
/// an enum type for standard OPCDE values, but it is generally advisable
/// to handle OPCODEs through this class.  In fact, public interfaces of
/// this library uses this class to pass or return OPCODEs instead of the
/// bare code values.
class Opcode {
public:
    /// Constants for standard OPCODE values.
    enum CodeValue {
        QUERY_CODE = 0,         ///< 0: Standard query (RFC1035)
        IQUERY_CODE = 1,        ///< 1: Inverse query (RFC1035)
        STATUS_CODE = 2,        ///< 2: Server status request (RFC1035)
        RESERVED3_CODE = 3,     ///< 3: Reserved for future use (RFC1035)
        NOTIFY_CODE = 4,        ///< 4: Notify (RFC1996)
        UPDATE_CODE = 5,        ///< 5: Dynamic update (RFC2136)
        RESERVED6_CODE = 6,     ///< 6: Reserved for future use (RFC1035)
        RESERVED7_CODE = 7,     ///< 7: Reserved for future use (RFC1035)
        RESERVED8_CODE = 8,     ///< 8: Reserved for future use (RFC1035)
        RESERVED9_CODE = 9,     ///< 9: Reserved for future use (RFC1035)
        RESERVED10_CODE = 10,   ///< 10: Reserved for future use (RFC1035)
        RESERVED11_CODE = 11,   ///< 11: Reserved for future use (RFC1035)
        RESERVED12_CODE = 12,   ///< 12: Reserved for future use (RFC1035)
        RESERVED13_CODE = 13,   ///< 13: Reserved for future use (RFC1035)
        RESERVED14_CODE = 14,   ///< 14: Reserved for future use (RFC1035)
        RESERVED15_CODE = 15    ///< 15: Reserved for future use (RFC1035)
    };

    /// \name Constructors and Destructor
    ///
    /// We use the default versions of destructor, copy constructor,
    /// and assignment operator.
    ///
    /// The default constructor is hidden as a result of defining the other
    /// constructors.  This is intentional; we don't want to allow an
    /// \c Opcode object to be constructed with an invalid state.
    //@{
    /// \brief Constructor from the code value.
    ///
    /// Since OPCODEs are 4-bit values, parameters larger than 15 are invalid.
    /// If \c code is larger than 15 an exception of class \c isc::OutOfRange
    /// will be thrown.
    ///
    /// \param code The underlying code value of the \c Opcode.
    explicit Opcode(const uint8_t code);
    //@}

    /// \brief Returns the \c Opcode code value.
    ///
    /// This method never throws an exception.
    ///
    /// \return The underlying code value corresponding to the \c Opcode.
    CodeValue getCode() const { return (code_); }

    /// \brief Return true iff two Opcodes are equal.
    ///
    /// Two Opcodes are equal iff their type codes are equal.
    ///
    /// This method never throws an exception.
    ///
    /// \param other the \c Opcode object to compare against.
    /// \return true if the two Opcodes are equal; otherwise false.
    bool equals(const Opcode& other) const
    { return (code_ == other.code_); }

    /// \brief Same as \c equals().
    bool operator==(const Opcode& other) const { return (equals(other)); }
    
    /// \brief Return true iff two Opcodes are not equal.
    ///
    /// This method never throws an exception.
    ///
    /// \param other the \c Opcode object to compare against.
    /// \return true if the two Opcodes are not equal; otherwise false.
    bool nequals(const Opcode& other) const
    { return (code_ != other.code_); }

    /// \brief Same as \c nequals().
    bool operator!=(const Opcode& other) const { return (nequals(other)); }

    /// \brief Convert the \c Opcode to a string.
    ///
    /// This method returns a string representation of the "mnemonic' used
    /// for the enum and constant objects.  For example, the string for
    /// code value 0 is "QUERY", etc.
    ///
    /// If resource allocation for the string fails, a corresponding standard
    /// exception will be thrown.
    ///
    /// \return A string representation of the \c Opcode.
    std::string toText() const;

    /// A constant object for the QUERY Opcode.
    static const Opcode& QUERY();

    /// A constant object for the IQUERY Opcode.
    static const Opcode& IQUERY();

    /// A constant object for the STATUS Opcode.
    static const Opcode& STATUS();

    /// A constant object for a reserved (code 3) Opcode.
    static const Opcode& RESERVED3();

    /// A constant object for the NOTIFY Opcode.
    static const Opcode& NOTIFY();

    /// A constant object for the UPDATE Opcode.
    static const Opcode& UPDATE();

    /// A constant object for a reserved (code 6) Opcode.
    static const Opcode& RESERVED6();

    /// A constant object for a reserved (code 7) Opcode.
    static const Opcode& RESERVED7();

    /// A constant object for a reserved (code 8) Opcode.
    static const Opcode& RESERVED8();

    /// A constant object for a reserved (code 9) Opcode.
    static const Opcode& RESERVED9();

    /// A constant object for a reserved (code 10) Opcode.
    static const Opcode& RESERVED10();

    /// A constant object for a reserved (code 11) Opcode.
    static const Opcode& RESERVED11();

    /// A constant object for a reserved (code 12) Opcode.
    static const Opcode& RESERVED12();

    /// A constant object for a reserved (code 13) Opcode.
    static const Opcode& RESERVED13();

    /// A constant object for a reserved (code 14) Opcode.
    static const Opcode& RESERVED14();

    /// A constant object for a reserved (code 15) Opcode.
    static const Opcode& RESERVED15();
private:
    CodeValue code_;
};

inline const Opcode&
Opcode::QUERY() {
    static Opcode c(0);
    return (c);
}

inline const Opcode&
Opcode::IQUERY() {
    static Opcode c(1);
    return (c);
}

inline const Opcode&
Opcode::STATUS() {
    static Opcode c(2);
    return (c);
}

inline const Opcode&
Opcode::RESERVED3() {
    static Opcode c(3);
    return (c);
}

inline const Opcode&
Opcode::NOTIFY() {
    static Opcode c(4);
    return (c);
}

inline const Opcode&
Opcode::UPDATE() {
    static Opcode c(5);
    return (c);
}

inline const Opcode&
Opcode::RESERVED6() {
    static Opcode c(6);
    return (c);
}

inline const Opcode&
Opcode::RESERVED7() {
    static Opcode c(7);
    return (c);
}

inline const Opcode&
Opcode::RESERVED8() {
    static Opcode c(8);
    return (c);
}

inline const Opcode&
Opcode::RESERVED9() {
    static Opcode c(9);
    return (c);
}

inline const Opcode&
Opcode::RESERVED10() {
    static Opcode c(10);
    return (c);
}

inline const Opcode&
Opcode::RESERVED11() {
    static Opcode c(11);
    return (c);
}

inline const Opcode&
Opcode::RESERVED12() {
    static Opcode c(12);
    return (c);
}

inline const Opcode&
Opcode::RESERVED13() {
    static Opcode c(13);
    return (c);
}

inline const Opcode&
Opcode::RESERVED14() {
    static Opcode c(14);
    return (c);
}

inline const Opcode&
Opcode::RESERVED15() {
    static Opcode c(15);
    return (c);
}

/// \brief Insert the \c Opcode as a string into stream.
///
/// This method convert \c opcode into a string and inserts it into the
/// output stream \c os.
///
/// \param os A \c std::ostream object on which the insertion operation is
/// performed.
/// \param opcode A reference to an \c Opcode object output by the operation.
/// \return A reference to the same \c std::ostream object referenced by
/// parameter \c os after the insertion operation.
std::ostream& operator<<(std::ostream& os, const Opcode& opcode);
}
}
#endif  // OPCODE_H

// Local Variables: 
// mode: c++
// End: 
