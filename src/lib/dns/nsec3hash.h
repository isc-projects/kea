// Copyright (C) 2012  Internet Systems Consortium, Inc. ("ISC")
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

#ifndef __NSEC3HASH_H
#define __NSEC3HASH_H 1

#include <string>

#include <exceptions/exceptions.h>

namespace isc {
namespace dns {
class Name;

namespace rdata {
namespace generic {
class NSEC3;
class NSEC3PARAM;
}
}

/// \brief An exception that is thrown for when an \c NSEC3Hash object is
/// constructed with an unknown hash algorithm.
///
/// A specific exception class is used so that the caller can selectively
/// catch this exception, e.g., while loading a zone, and handle it
/// accordingly.
class UnknownNSEC3HashAlgorithm : public isc::Exception {
public:
    UnknownNSEC3HashAlgorithm(const char* file, size_t line,
                              const char* what) :
        isc::Exception(file, line, what) {}
};

/// \brief A calculator of NSEC3 hashes.
///
/// This is an abstract base class that defines a simple interface to
/// calculating NSEC3 hash values as defined in RFC5155.
///
/// (Derived classes of) this class is designed to be "stateless" in that it
/// basically doesn't hold mutable state once constructed, and hash
/// calculation solely depends on the parameters given on construction and
/// input to the \c calculate() method.  In that sense this could be a
/// single free function rather than  a class, but we decided to provide the
/// functionality as a class for two reasons: NSEC3 hash calculations would
/// often take place more than one time in a single query or validation
/// process, so it would be more efficient if we could hold some internal
/// resources used for the calculation and reuse it over multiple calls to
/// \c calculate() (a concrete implementation in this library actually does
/// this); Second, we may want to customize the hash calculation logic for
/// testing purposes or for other future extensions.  For example, we may
/// want to use a fake calculator for tests that returns pre-defined hash
/// values (so a slight change to the test input wouldn't affect the test
/// result).  Using classes from this base would make it possible more
/// transparently to the application.
///
/// A specific derived class instance must be created by the factory method,
/// \c create().
///
/// There can be several ways to extend this class in future.  Those include:
/// - Allow customizing the factory method so the application change the
///   behavior dynamically.
/// - Allow to construct the class from a tuple of parameters, that is,
///   integers for algorithm, iterations and flags, and opaque salt data.
///   For example, we might want to use that version for validators.
/// - Allow producing hash value as binary data
/// - Allow updating NSEC3 parameters of a class object so we can still reuse
///   the internal resources for different sets of parameters.
class NSEC3Hash {
protected:
    /// \brief The default constructor.
    ///
    /// This is defined as protected to prevent this class from being directly
    /// instantiated even if the class definition is modified (accidentally
    /// or intentionally) to have no pure virtual methods.
    NSEC3Hash() {}

public:
    /// \brief Factory method of NSECHash from NSEC3PARAM RDATA.
    ///
    /// The hash algorithm given via \c param must be known to the
    /// implementation.  Otherwise \c UnknownNSEC3HashAlgorithm exception
    /// will be thrown.
    ///
    /// This method creates an \c NSEC3Hash object using \c new.  The caller
    /// is responsible for releasing it with \c delete that is compatible to
    /// the one used in this library.  In practice, the application would
    /// generally need to store the returned pointer in some form of smart
    /// pointer; otherwise the resulting code will be quite fragile against
    /// exceptions (and in this case the application doesn't have to worry
    /// about explicit \c delete).
    ///
    /// \throw UnknownNSEC3HashAlgorithm The specified algorithm in \c param
    /// is unknown.
    /// \throw std::bad_alloc Internal resource allocation failure.
    ///
    /// \param param NSEC3 parameters used for subsequent calculation.
    /// \return A pointer to a concrete derived object of \c NSEC3Hash.
    static NSEC3Hash* create(const rdata::generic::NSEC3PARAM& param);

    /// \brief Factory method of NSECHash from NSEC3 RDATA.
    ///
    /// This is similar to the other version, but extracts the parameters
    /// for hash calculation from an NSEC3 RDATA object.
    static NSEC3Hash* create(const rdata::generic::NSEC3& nsec3);

    /// \brief The destructor.
    virtual ~NSEC3Hash() {}

    /// \brief Calculate the NSEC3 hash.
    ///
    /// This method calculates the NSEC3 hash value for the given \c name
    /// with the hash parameters (algorithm, iterations and salt) given at
    /// construction, and returns the value as a base32hex-encoded string
    /// (without containing any white spaces).  All US-ASCII letters in the
    /// string will be upper cased.
    ///
    /// \param name The domain name for which the hash value is to be
    /// calculated.
    /// \return Base32hex-encoded string of the hash value.
    virtual std::string calculate(const Name& name) const = 0;

    /// \brief Match given NSEC3 parameters with that of the hash.
    ///
    /// This method compares NSEC3 parameters used for hash calculation
    /// in the object with those in the given NSEC3 RDATA, and return
    /// true iff they completely match.  In the current implementation
    /// only the algorithm, iterations and salt are compared; the flags
    /// are ignored (as they don't affect hash calculation per RFC5155).
    ///
    /// \throw None
    ///
    /// \param nsec3 An NSEC3 RDATA object whose hash parameters are to be
    /// matched
    /// \return true If the given parameters match the local ones; false
    /// otherwise.
    virtual bool match(const rdata::generic::NSEC3& nsec3) const = 0;

    /// \brief Match given NSEC3PARAM parameters with that of the hash.
    ///
    /// This is similar to the other version, but extracts the parameters
    /// to compare from an NSEC3PARAM RDATA object.
    virtual bool match(const rdata::generic::NSEC3PARAM& nsec3param) const = 0;
};

}
}
#endif  // __NSEC3HASH_H

// Local Variables:
// mode: c++
// End:
