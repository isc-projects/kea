// Copyright (C) 2011-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef TSIGERROR_H
#define TSIGERROR_H 1

#include <ostream>
#include <string>

#include <dns/rcode.h>

namespace isc {
namespace dns {
/// TSIG errors
///
/// The \c TSIGError class objects represent standard errors related to
/// TSIG protocol operations as defined in related specifications, mainly
/// in RFC2845, RFC2930 and RFC4635.
class TSIGError {
public:
    /// Constants for pre-defined TSIG error values.
    ///
    /// Code values from 0 through 15 (inclusive) are derived from those of
    /// RCODE and are not defined here.  See the \c Rcode class.
    ///
    /// \note Unfortunately some systems define "BADSIG" as a macro in a public
    /// header file.  To avoid conflict with it we add an underscore to our
    /// definitions.
    enum CodeValue {
        BAD_SIG_CODE = 16,  ///< 16: TSIG verification failure
        BAD_KEY_CODE = 17,  ///< 17: TSIG key is not recognized
        BAD_TIME_CODE = 18, ///< 18: Current time and time signed are too different
        BAD_MODE_CODE = 19, ///< 19: Bad TKEY mode
        BAD_NAME_CODE = 20, ///< 20: Duplicate TKEY name
        BAD_ALG_CODE = 21,  ///< 21: TKEY algorithm not supported
        BAD_TRUNC_CODE = 22 ///< 22: Bad truncation
    };

    /// \name Constructors
    ///
    /// We use the default versions of destructor, copy constructor,
    /// and assignment operator.
    //@{
    /// Constructor from the code value.
    ///
    /// \exception None
    ///
    /// \param error_code The underlying 16-bit error code value of the \c TSIGError.
    explicit TSIGError(uint16_t error_code) : code_(error_code) {}

    /// Constructor from \c Rcode.
    ///
    /// As defined in RFC2845, error code values from 0 to 15 (inclusive) are
    /// derived from the DNS RCODEs, which are represented via the \c Rcode
    /// class in this library.  This constructor works as a converter from
    /// these RCODEs to corresponding TSIGError objects.
    ///
    /// \exception isc::OutOfRange Given rcode is not convertible to
    /// TSIGErrors.
    ///
    /// \param rcode the \c Rcode from which the TSIGError should be derived.
    explicit TSIGError(Rcode rcode);
    //@}

    /// \brief Returns the \c TSIGCode error code value.
    ///
    /// \exception None
    ///
    /// \return The underlying code value corresponding to the \c TSIGError.
    uint16_t getCode() const { return (code_); }

    /// \brief Return true iff two \c TSIGError objects are equal.
    ///
    /// Two TSIGError objects are equal iff their error codes are equal.
    ///
    /// \exception None
    ///
    /// \param other the \c TSIGError object to compare against.
    /// \return true if the two TSIGError are equal; otherwise false.
    bool equals(const TSIGError& other) const
    { return (code_ == other.code_); }

    /// \brief Same as \c equals().
    bool operator==(const TSIGError& other) const { return (equals(other)); }

    /// \brief Return true iff two \c TSIGError objects are not equal.
    ///
    /// \exception None
    ///
    /// \param other the \c TSIGError object to compare against.
    /// \return true if the two TSIGError objects are not equal;
    /// otherwise false.
    bool nequals(const TSIGError& other) const
    { return (code_ != other.code_); }

    /// \brief Same as \c nequals().
    bool operator!=(const TSIGError& other) const { return (nequals(other)); }

    /// \brief Convert the \c TSIGError to a string.
    ///
    /// For codes derived from RCODEs up to 15, this method returns the
    /// same string as \c Rcode::toText() for the corresponding code.
    /// For other pre-defined code values (see TSIGError::CodeValue),
    /// this method returns a string representation of the "mnemonic' used
    /// for the enum and constant objects as defined in RFC2845.
    /// For example, the string for code value 16 is "BADSIG", etc.
    /// For other code values it returns a string representation of the decimal
    /// number of the value, e.g. "32", "100", etc.
    ///
    /// \exception std::bad_alloc Resource allocation for the string fails
    ///
    /// \return A string representation of the \c TSIGError.
    std::string toText() const;

    /// \brief Convert the \c TSIGError to a \c Rcode
    ///
    /// This method returns an \c Rcode object that is corresponding to
    /// the TSIG error.  The returned \c Rcode is expected to be used
    /// by a verifying server to specify the RCODE of a response when
    /// TSIG verification fails.
    ///
    /// Specifically, this method returns \c Rcode::NOTAUTH() for the
    /// TSIG specific errors, BADSIG, BADKEY, BADTIME, as described in
    /// RFC2845.  For errors derived from the standard Rcode (code 0-15),
    /// it returns the corresponding \c Rcode.  For others, this method
    /// returns \c Rcode::SERVFAIL() as a last resort.
    ///
    /// \exception None
    Rcode toRcode() const;

    /// A constant TSIG error object derived from \c Rcode::NOERROR()
    static const TSIGError& NOERROR();

    /// A constant TSIG error object derived from \c Rcode::FORMERR()
    static const TSIGError& FORMERR();

    /// A constant TSIG error object derived from \c Rcode::SERVFAIL()
    static const TSIGError& SERVFAIL();

    /// A constant TSIG error object derived from \c Rcode::NXDOMAIN()
    static const TSIGError& NXDOMAIN();

    /// A constant TSIG error object derived from \c Rcode::NOTIMP()
    static const TSIGError& NOTIMP();

    /// A constant TSIG error object derived from \c Rcode::REFUSED()
    static const TSIGError& REFUSED();

    /// A constant TSIG error object derived from \c Rcode::YXDOMAIN()
    static const TSIGError& YXDOMAIN();

    /// A constant TSIG error object derived from \c Rcode::YXRRSET()
    static const TSIGError& YXRRSET();

    /// A constant TSIG error object derived from \c Rcode::NXRRSET()
    static const TSIGError& NXRRSET();

    /// A constant TSIG error object derived from \c Rcode::NOTAUTH()
    static const TSIGError& NOTAUTH();

    /// A constant TSIG error object derived from \c Rcode::NOTZONE()
    static const TSIGError& NOTZONE();

    /// A constant TSIG error object derived from \c Rcode::RESERVED11()
    static const TSIGError& RESERVED11();

    /// A constant TSIG error object derived from \c Rcode::RESERVED12()
    static const TSIGError& RESERVED12();

    /// A constant TSIG error object derived from \c Rcode::RESERVED13()
    static const TSIGError& RESERVED13();

    /// A constant TSIG error object derived from \c Rcode::RESERVED14()
    static const TSIGError& RESERVED14();

    /// A constant TSIG error object derived from \c Rcode::RESERVED15()
    static const TSIGError& RESERVED15();

    /// A constant TSIG error object for the BADSIG code
    /// (see \c TSIGError::BAD_SIG_CODE).
    static const TSIGError& BAD_SIG();

    /// A constant TSIG error object for the BADKEY code
    /// (see \c TSIGError::BAD_KEY_CODE).
    static const TSIGError& BAD_KEY();

    /// A constant TSIG error object for the BADTIME code
    /// (see \c TSIGError::BAD_TIME_CODE).
    static const TSIGError& BAD_TIME();

    /// A constant TSIG error object for the BADMODE code
    /// (see \c TSIGError::BAD_MODE_CODE).
    static const TSIGError& BAD_MODE();

    /// A constant TSIG error object for the BADNAME code
    /// (see \c TSIGError::BAD_NAME_CODE).
    static const TSIGError& BAD_NAME();

    /// A constant TSIG error object for the BADALG code
    /// (see \c TSIGError::BAD_ALG_CODE).
    static const TSIGError& BAD_ALG();

    /// A constant TSIG error object for the BADTRUNC code
    /// (see \c TSIGError::BAD_TRUNC_CODE).
    static const TSIGError& BAD_TRUNC();

private:
    // This is internally used to specify the maximum possible RCODE value
    // that can be convertible to TSIGErrors.
    static const int MAX_RCODE_FOR_TSIGERROR = 15;

    uint16_t code_;
};

inline const TSIGError&
TSIGError::NOERROR() {
    static TSIGError e(Rcode::NOERROR());
    return (e);
}

inline const TSIGError&
TSIGError::FORMERR() {
    static TSIGError e(Rcode::FORMERR());
    return (e);
}

inline const TSIGError&
TSIGError::SERVFAIL() {
    static TSIGError e(Rcode::SERVFAIL());
    return (e);
}

inline const TSIGError&
TSIGError::NXDOMAIN() {
    static TSIGError e(Rcode::NXDOMAIN());
    return (e);
}

inline const TSIGError&
TSIGError::NOTIMP() {
    static TSIGError e(Rcode::NOTIMP());
    return (e);
}

inline const TSIGError&
TSIGError::REFUSED() {
    static TSIGError e(Rcode::REFUSED());
    return (e);
}

inline const TSIGError&
TSIGError::YXDOMAIN() {
    static TSIGError e(Rcode::YXDOMAIN());
    return (e);
}

inline const TSIGError&
TSIGError::YXRRSET() {
    static TSIGError e(Rcode::YXRRSET());
    return (e);
}

inline const TSIGError&
TSIGError::NXRRSET() {
    static TSIGError e(Rcode::NXRRSET());
    return (e);
}

inline const TSIGError&
TSIGError::NOTAUTH() {
    static TSIGError e(Rcode::NOTAUTH());
    return (e);
}

inline const TSIGError&
TSIGError::NOTZONE() {
    static TSIGError e(Rcode::NOTZONE());
    return (e);
}

inline const TSIGError&
TSIGError::RESERVED11() {
    static TSIGError e(Rcode::RESERVED11());
    return (e);
}

inline const TSIGError&
TSIGError::RESERVED12() {
    static TSIGError e(Rcode::RESERVED12());
    return (e);
}

inline const TSIGError&
TSIGError::RESERVED13() {
    static TSIGError e(Rcode::RESERVED13());
    return (e);
}

inline const TSIGError&
TSIGError::RESERVED14() {
    static TSIGError e(Rcode::RESERVED14());
    return (e);
}

inline const TSIGError&
TSIGError::RESERVED15() {
    static TSIGError e(Rcode::RESERVED15());
    return (e);
}

inline const TSIGError&
TSIGError::BAD_SIG() {
    static TSIGError e(BAD_SIG_CODE);
    return (e);
}

inline const TSIGError&
TSIGError::BAD_KEY() {
    static TSIGError e(BAD_KEY_CODE);
    return (e);
}

inline const TSIGError&
TSIGError::BAD_TIME() {
    static TSIGError e(BAD_TIME_CODE);
    return (e);
}

inline const TSIGError&
TSIGError::BAD_MODE() {
    static TSIGError e(BAD_MODE_CODE);
    return (e);
}

inline const TSIGError&
TSIGError::BAD_NAME() {
    static TSIGError e(BAD_NAME_CODE);
    return (e);
}

inline const TSIGError&
TSIGError::BAD_ALG() {
    static TSIGError e(BAD_ALG_CODE);
    return (e);
}

inline const TSIGError&
TSIGError::BAD_TRUNC() {
    static TSIGError e(BAD_TRUNC_CODE);
    return (e);
}

/// Insert the \c TSIGError as a string into stream.
///
/// This method convert \c tsig_error into a string and inserts it into the
/// output stream \c os.
///
/// \param os A \c std::ostream object on which the insertion operation is
/// performed.
/// \param tsig_error An \c TSIGError object output by the operation.
/// \return A reference to the same \c std::ostream object referenced by
/// parameter \c os after the insertion operation.
std::ostream& operator<<(std::ostream& os, const TSIGError& tsig_error);
}
}

#endif  // TSIGERROR_H

// Local Variables:
// mode: c++
// End:
