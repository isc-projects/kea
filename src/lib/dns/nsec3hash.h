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

#include <boost/noncopyable.hpp>

#include <exceptions/exceptions.h>

namespace isc {
namespace dns {
class Name;

namespace rdata {
namespace generic {
class NSEC3PARAM;
}
}

/// An exception that is thrown for when an \c NSEC3Hash object is constructed
/// with an unknown hash algorithm.
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

/// A calculator of NSEC3 hashes.
///
/// This is a simple class that encapsulates the algorithm of calculating
/// NSEC3 hash values as defined in RFC5155.
///
/// This class is designed to be "stateless" in that it basically doesn't
/// hold mutable state once constructed, and hash calculation solely depends
/// on the parameters given on construction and input to the \c calculate()
/// method.  In that sense this could be a single free function rather than
/// a class, but we decided to provide the functionality as a class for
/// two reasons: NSEC3 hash calculations would often take place more than one
/// time in a single query or validation process, so it would be more
/// efficient if we could hold some internal resources used for the
/// calculation and reuse it over multiple calls to \c calculate() (this
/// implementation actually does this); Second, for testing purposes we may
/// want to use a fake calculator that returns pre-defined hash values
/// (so a slight change to the test input wouldn't affect the test result).
/// Using a class would make it possible by introducing a common base class
/// and having the application depend on that base class (then the fake
/// calculator will be defined as a separate subclass of the base).
///
/// The initial implementation makes this class non copyable as it wouldn't
/// used be passed from one place to another, especially if and when it's
/// used via a base class abstraction.  But there's no fundamental reason
/// this cannot be copied, so if we see a specific need for it, this
/// restriction can be revisited.
///
/// There can be several ways to extend this class in future.  Those include:
/// - Introduce a base class and make it derived from it (mainly for testing
///   purposes as noted above)
/// - Allow to construct the class from a tuple of parameters, that is,
///   integers for algorithm, iterations and flags, and opaque salt data.
///   For example, we might want to use that version for validators.
/// - Allow producing hash value as binary data
/// - Allow updating NSEC3 parameters of a class object so we can still reuse
///   the internal resources for different sets of parameters.
class NSEC3Hash : public boost::noncopyable {
public:
    /// Constructor from NSEC3PARAM RDATA.
    ///
    /// The hash algorithm given via \c param must be known to the
    /// implementation.  Otherwise \c UnknownNSEC3HashAlgorithm exception
    /// will be thrown.
    ///
    /// \throw UnknownNSEC3HashAlgorithm The specified algorithm in \c param
    /// is unknown.
    /// \throw std::bad_alloc Internal resource allocation failure.
    ///
    /// \param param NSEC3 parameters used for subsequent calculation.
    NSEC3Hash(const rdata::generic::NSEC3PARAM& param);

    /// The destructor.
    ~NSEC3Hash();

    /// Calculate the NSEC3 hash.
    ///
    /// This method calculates the NSEC3 hash value for the given \c name
    /// with the hash parameters (algorithm, iterations and salt) given at
    /// construction, and returns the value in a base32hex-encoded string
    /// (without containing any white spaces).  All alphabets in the string
    /// will be upper cased.
    ///
    /// \param name The domain name for which the hash value is to be
    /// calculated.
    /// \return Base32hex-encoded string of the hash value.
    std::string calculate(const Name& name) const;

private:
    struct NSEC3HashImpl;
    NSEC3HashImpl* impl_;
};
}
}
#endif  // __NSEC3HASH_H

// Local Variables:
// mode: c++
// End:
