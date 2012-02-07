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

/// \brief Factory class of NSEC3Hash.
///
/// This class is an abstract base class that provides the creation interfaces
/// of \c NSEC3Hash objects.  By defining a specific derived class of the
/// creator, normally with a different specific class of \c NSEC3Hash,
/// the application can use a customized implementation of \c NSEC3Hash
/// without changing the library itself.  The intended primary application of
/// such customization is tests (it would be convenient for a test to produce
/// a faked hash value regardless of the input so it doesn't have to identify
/// a specific input value to produce a particular hash).  Another possibility
/// would be an experimental extension for a newer hash algorithm or
/// implementation.
///
/// The two main methods named \c create() correspond to the static factory
/// methods of \c NSEC3Hash of the same name.
///
/// By default, the library uses a builtin creator implementation.  The
/// \c setNSEC3HashCreator() function can be used to replace it with a user
/// defined version.
///
/// The creator objects are generally expected to be stateless; they will
/// only encapsulate the factory logic.  The \c create() methods are declared
/// as const member functions for this reason.  But if we see the need for
/// having a customized creator that benefits from its own state in future,
/// this condition can be loosened.
class NSEC3HashCreator {
protected:
    /// \brief The default constructor.
    ///
    /// Make very sure this isn't directly instantiated by making it protected
    /// even if this class is modified to lose all pure virtual methods.
    NSEC3HashCreator() {}

public:
    /// \brief The destructor.
    ///
    /// This does nothing; defined only for allowing derived classes to
    /// specialize its behavior.
    virtual ~NSEC3HashCreator() {}

    /// \brief Factory method of NSECHash from NSEC3PARAM RDATA.
    ///
    /// See
    /// <code>NSEC3Hash::create(const rdata::generic::NSEC3PARAM& param)</code>
    virtual NSEC3Hash* create(const rdata::generic::NSEC3PARAM& nsec3param)
        const = 0;

    /// \brief Factory method of NSECHash from NSEC3 RDATA.
    ///
    /// See
    /// <code>NSEC3Hash::create(const rdata::generic::NSEC3& param)</code>
    virtual NSEC3Hash* create(const rdata::generic::NSEC3& nsec3)
        const = 0;
};

/// \brief The registrar of \c NSEC3HashCreator.
///
/// This function sets or resets the system-wide \c NSEC3HashCreator that
/// is used by \c NSEC3Hash::create().
///
/// If \c new_creator is non NULL, the given creator object will replace
/// any existing creator.  If it's NULL, the default builtin creator will be
/// used again from that point.
///
/// When \c new_creator is non NULL, the caller is responsible for keeping
/// the referenced object valid as long as it can be used via
/// \c NSEC3Hash::create().
///
/// \exception None
/// \param new_creator A pointer to the new creator object or NULL.
void setNSEC3HashCreator(const NSEC3HashCreator* new_creator);

}
}
#endif  // __NSEC3HASH_H

// Local Variables:
// mode: c++
// End:
