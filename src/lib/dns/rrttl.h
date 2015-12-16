// Copyright (C) 2010-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef RRTTL_H
#define RRTTL_H 1

#include <dns/exceptions.h>

#include <boost/optional.hpp>

#include <stdint.h>

namespace isc {
namespace util {
class InputBuffer;
class OutputBuffer;
}

namespace dns {

// forward declarations
class AbstractMessageRenderer;

///
/// \brief A standard DNS module exception that is thrown if an RRTTL object
/// is being constructed from an unrecognized string.
///
class InvalidRRTTL : public DNSTextError {
public:
    InvalidRRTTL(const char* file, size_t line, const char* what) :
        DNSTextError(file, line, what) {}
};

///
/// \brief A standard DNS module exception that is thrown if an RRTTL object
/// is being constructed from a incomplete (too short) wire-format data.
///
class IncompleteRRTTL : public isc::dns::Exception {
public:
    IncompleteRRTTL(const char* file, size_t line, const char* what) :
        isc::dns::Exception(file, line, what) {}
};

///
/// The \c RRTTL class encapsulates TTLs used in DNS resource records.
///
/// This is a straightforward class; an \c RRTTL object simply maintains a
/// 32-bit unsigned integer corresponding to the TTL value.  The main purpose
/// of this class is to provide convenient interfaces to convert a textual
/// representation into the integer TTL value and vice versa, and to handle
/// wire-format representations.
class RRTTL {
public:
    ///
    /// \name Constructors, Factory and Destructor
    ///
    /// Note: We use the default copy constructor and the default copy
    /// assignment operator intentionally.
    //@{
    /// Constructor from an integer TTL value.
    ///
    /// This constructor never throws an exception.
    ///
    /// \param ttlval An 32-bit integer of the RRTTL.
    explicit RRTTL(uint32_t ttlval) : ttlval_(ttlval) {}

    /// Constructor from a string.
    ///
    /// It accepts either a decimal number, specifying number of seconds. Or,
    /// it can be given a sequence of numbers and units, like "2H" (meaning
    /// two hours), "1W3D" (one week and 3 days). The allowed units are W
    /// (week), D (day), H (hour), M (minute) and S (second). They can be also
    /// specified in lower-case. No further restrictions are checked (so they
    /// can be specified in arbitrary order and even things like "1D1D" can
    /// be used to specify two days).
    ///
    /// \param ttlstr A string representation of the \c RRTTL.
    ///
    /// \throw InvalidRRTTL in case the string is not recognized as valid
    ///     TTL representation.
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
    explicit RRTTL(isc::util::InputBuffer& buffer);

    /// A separate factory of RRTTL from text.
    ///
    /// This static method is similar to the constructor that takes a string
    /// object, but works as a factory and reports parsing failure in the
    /// form of the return value.  Normally the constructor version should
    /// suffice, but in some cases the caller may have to expect mixture of
    /// valid and invalid input, and may want to minimize the overhead of
    /// possible exception handling.   This version is provided for such
    /// purpose.
    ///
    /// If the given text represents a valid RRTTL, it returns a pointer
    /// to a new RRTTL object. If the given text does not represent a
    /// valid RRTTL, it returns \c NULL..
    ///
    /// One main purpose of this function is to minimize the overhead
    /// when the given text does not represent a valid RR TTL.  For this
    /// reason this function intentionally omits the capability of delivering
    /// a detailed reason for the parse failure, such as in the \c want()
    /// string when exception is thrown from the constructor (it will
    /// internally require a creation of string object, which is relatively
    /// expensive).  If such detailed information is necessary, the constructor
    /// version should be used to catch the resulting exception.
    ///
    /// This function never throws the \c InvalidRRTTL exception.
    ///
    /// \param ttlstr A string representation of the \c RRTTL.
    /// \return A new RRTTL object for the given text or a \c NULL value.
    static RRTTL* createFromText(const std::string& ttlstr);
    ///
    //@}

    ///
    /// \name Converter methods
    ///
    //@{
    /// \brief Convert the \c RRTTL to a string.
    ///
    /// This version of implementation simply converts the TTL value into the
    /// numeric textual representation.  We may introduce more human-readable
    /// format depending on the context in future versions.
    ///
    /// If resource allocation in rendering process fails, a corresponding
    /// standard exception will be thrown.
    ///
    /// \return A string representation of the \c RRTTL.
    const std::string toText() const;
    /// \brief Render the \c RRTTL in the wire format.
    ///
    /// This method renders the TTL value in network byte order via \c renderer,
    /// which encapsulates output buffer and other rendering contexts.
    ///
    /// If resource allocation in rendering process fails, a corresponding
    /// standard exception will be thrown.
    ///
    /// \param renderer DNS message rendering context that encapsulates the
    /// output buffer in which the RRTTL is to be stored.
    void toWire(AbstractMessageRenderer& renderer) const;
    /// \brief Render the \c RRTTL in the wire format.
    ///
    /// This method renders the TTL value in network byte order into the
    /// \c buffer.
    ///
    /// If resource allocation in rendering process fails, a corresponding
    /// standard exception will be thrown.
    ///
    /// \param buffer An output buffer to store the wire data.
    void toWire(isc::util::OutputBuffer& buffer) const;
    //@}

    ///
    /// \name Getter Methods
    ///
    //@{
    /// \brief Returns the TTL value as a 32-bit unsigned integer.
    ///
    /// This method never throws an exception.
    ///
    /// \return An 32-bit integer corresponding to the RRTTL.
    uint32_t getValue() const { return (ttlval_); }
    //@}

    ///
    /// \name Comparison methods
    ///
    /// Comparison between two \c RRTTL objects is performed in a
    /// straightforward way, that is, comparing the corresponding TTL values
    /// (which is the result of the \c getValue() method) as 32-bit unsigned
    /// integers.
    //@{
    /// \brief Return true iff two RRTTLs are equal.
    ///
    /// This method never throws an exception.
    ///
    /// \param other the \c RRTTL object to compare against.
    bool equals(const RRTTL& other) const
    { return (ttlval_ == other.ttlval_); }
    /// \brief Same as \c equals().
    bool operator==(const RRTTL& other) const
    { return (ttlval_ == other.ttlval_); }
    /// \brief Return true iff two RRTTLs are not equal.
    ///
    /// This method never throws an exception.
    ///
    /// \param other the \c RRTTL object to compare against.
    bool nequals(const RRTTL& other) const
    { return (ttlval_ != other.ttlval_); }
    /// \brief Same as \c nequals().
    bool operator!=(const RRTTL& other) const
    { return (ttlval_ != other.ttlval_); }
    /// \brief Less-than or equal comparison for RRTTL against \c other.
    ///
    /// This method never throws an exception.
    ///
    /// \param other the \c RRTTL object to compare against.
    /// \return true if \c this RRTTL is less than or equal to the \c other;
    /// otherwise false.
    bool leq(const RRTTL& other) const
    { return (ttlval_ <= other.ttlval_); }

    /// Same as \c leq()
    bool operator<=(const RRTTL& other) const
    { return (ttlval_ <= other.ttlval_); }

    /// \brief Greater-than or equal comparison for RRTTL against \c other.
    ///
    /// This method never throws an exception.
    ///
    /// \param other the \c RRTTL object to compare against.
    /// \return true if \c this RRTTL is greater than or equal to the \c other;
    /// otherwise false.
    bool geq(const RRTTL& other) const
    { return (ttlval_ >= other.ttlval_); }

    /// Same as \c geq()
    bool operator>=(const RRTTL& other) const
    { return (ttlval_ >= other.ttlval_); }

    /// \brief Less-than comparison for RRTTL against \c other.
    ///
    /// This method never throws an exception.
    ///
    /// \param other the \c RRTTL object to compare against.
    /// \return true if \c this RRTTL is less than the \c other;
    /// otherwise false.
    bool lthan(const RRTTL& other) const
    { return (ttlval_ < other.ttlval_); }

    /// Same as \c lthan()
    bool operator<(const RRTTL& other) const
    { return (ttlval_ < other.ttlval_); }

    /// \brief Greater-than comparison for RRTTL against \c other.
    ///
    /// This method never throws an exception.
    ///
    /// \param other the \c RRTTL object to compare against.
    /// \return true if \c this RRTTL is greater than the \c other;
    /// otherwise false.
    bool gthan(const RRTTL& other) const
    { return (ttlval_ > other.ttlval_); }

    /// Same as \c gthan()
    bool operator>(const RRTTL& other) const
    { return (ttlval_ > other.ttlval_); }
    //@}

    ///
    /// \name Protocol constants
    ///
    //@{
    /// \brief The TTL of the max allowable value, per RFC2181 Section 8.
    ///
    /// The max value is the largest unsigned 31 bit integer, 2^31-1.
    ///
    /// \note At the moment an RRTTL object can have a value larger than
    /// this limit.  We may revisit it in a future version.
    static const RRTTL& MAX_TTL() {
        static const RRTTL max_ttl(0x7fffffff);
        return (max_ttl);
    }
    //@}

private:
    uint32_t ttlval_;
};

///
/// \brief Insert the \c RRTTL as a string into stream.
///
/// This method convert the \c rrttl into a string and inserts it into the
/// output stream \c os.
///
/// This function overloads the global operator<< to behave as described in
/// ostream::operator<< but applied to \c RRTTL objects.
///
/// \param os A \c std::ostream object on which the insertion operation is
/// performed.
/// \param rrttl The \c RRTTL object output by the operation.
/// \return A reference to the same \c std::ostream object referenced by
/// parameter \c os after the insertion operation.
std::ostream&
operator<<(std::ostream& os, const RRTTL& rrttl);
}
}
#endif  // RRTTL_H

// Local Variables: 
// mode: c++
// End: 
