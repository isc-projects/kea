/*
 * Copyright (C) 2010  Internet Systems Consortium, Inc. ("ISC")
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES WITH
 * REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS.  IN NO EVENT SHALL ISC BE LIABLE FOR ANY SPECIAL, DIRECT,
 * INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
 * LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
 * OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 */

/* $Id$ */

#include <ostream>

#ifndef __OPCODE_H
#define __OPCODE_H 1

namespace isc {
namespace dns {

/// \brief The \c Opcode class objects represent standard OPCODEs
/// of the header section of DNS messages as defined in RFC1035.
///
/// Note: since there are only 15 possible values, it may make more sense to
/// simply define an enum type to represent these values.
///
/// Constant objects are defined for standard flags.
class Opcode {
public:
    enum CodeValue {
        QUERY_CODE = 0,
        IQUERY_CODE = 1,
        STATUS_CODE = 2,
        RESERVED3_CODE = 3,
        NOTIFY_CODE = 4,
        UPDATE_CODE = 5,
        RESERVED6_CODE = 6,
        RESERVED7_CODE = 7,
        RESERVED8_CODE = 8,
        RESERVED9_CODE = 9,
        RESERVED10_CODE = 10,
        RESERVED11_CODE = 11,
        RESERVED12_CODE = 12,
        RESERVED13_CODE = 13,
        RESERVED14_CODE = 14,
        RESERVED15_CODE = 15,
        MAX_CODE = 15
    };
    explicit Opcode(const uint16_t code);
    CodeValue getCode() const { return (code_); }

    bool equals(const Opcode& other) const
    { return (code_ == other.code_); }

    bool operator==(const Opcode& other) const { return (equals(other)); }

    bool nequals(const Opcode& other) const
    { return (code_ != other.code_); }

    bool operator!=(const Opcode& other) const { return (nequals(other)); }

    std::string toText() const;

    static const Opcode& QUERY();
    static const Opcode& IQUERY();
    static const Opcode& STATUS();
    static const Opcode& RESERVED3();
    static const Opcode& NOTIFY();
    static const Opcode& UPDATE();
    static const Opcode& RESERVED6();
    static const Opcode& RESERVED7();
    static const Opcode& RESERVED8();
    static const Opcode& RESERVED9();
    static const Opcode& RESERVED10();
    static const Opcode& RESERVED11();
    static const Opcode& RESERVED12();
    static const Opcode& RESERVED13();
    static const Opcode& RESERVED14();
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
/// This method convert \c edns into a string and inserts it into the
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
