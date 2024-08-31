// Copyright (C) 2010-2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef TSIGKEY_H
#define TSIGKEY_H

#include <cryptolink/cryptolink.h>

namespace isc {
namespace dns {

class Name;

/// @brief TSIG key.
///
/// This class holds a TSIG key along with some related attributes as
/// defined in RFC2845.
///
/// A TSIG key consists of the following attributes:
/// - Key name
/// - Hash algorithm
/// - Digest bits
/// - Shared secret
///
/// <b>Implementation Notes</b>
///
/// We may add more attributes in future versions.  For example, if and when
/// we support the TKEY protocol (RFC2930), we may need to introduce the
/// notion of inception and expiration times.
/// At that point we may also have to introduce a class hierarchy to handle
/// different types of keys in a polymorphic way.
/// At the moment we use the straightforward value-type class with minimal
/// attributes.
///
/// In the TSIG protocol, hash algorithms are represented in the form of
/// domain name.
/// Our interfaces provide direct translation of this concept; for example,
/// the constructor from parameters take a @ref Name object to specify the
/// algorithm.
/// On one hand, this may be counter intuitive.
/// An API user would rather specify "hmac-md5" instead of
/// <code>Name("hmac-md5.sig-alg.reg.int")</code>.
/// On the other hand, it may be more convenient for some kind of applications
/// if we maintain the algorithm as the expected representation for
/// protocol operations (such as sign and very a message).
/// Considering these points, we adopt the interface closer to the protocol
/// specification for now.
/// To minimize the burden for API users, we also define a set of constants
/// for commonly used algorithm names so that the users don't have to
/// remember the actual domain names defined in the protocol specification.
/// We may also have to add conversion routines between domain names
/// and more intuitive representations (e.g. strings) for algorithms.
class TSIGKey {
public:
    ///
    /// @brief Constructors, Assignment Operator and Destructor.
    ///
    //@{
    /// @brief Constructor from key parameters.
    ///
    /// The algorithm_name should generally be a known algorithm to this
    /// implementation, which are defined via the
    /// <code>static const</code> member functions.
    ///
    /// Other names are still accepted as long as the secret is empty
    /// (secret is null and secret_len is 0), however; in some cases
    /// we might want to treat just the pair of key name and algorithm name
    /// opaquely, e.g., when generating a response TSIG with a BADKEY error
    /// because the algorithm is unknown as specified in Section 3.2 of
    /// RFC2845 (in which case the algorithm name would be copied from the
    /// request to the response, and for that purpose it would be convenient
    /// if a TSIGKey object can hold a name for an "unknown" algorithm).
    ///
    /// @note RFC2845 does not specify which algorithm name should be used
    /// in such a BADKEY response.  The behavior of using the same algorithm
    /// is derived from the BIND 9 implementation.
    ///
    /// It is unlikely that a TSIG key with an unknown algorithm is of any
    /// use with actual crypto operation, so care must be taken when dealing
    /// with such keys. (The restriction for the secret will prevent
    /// accidental creation of such a dangerous key, e.g., due to misspelling
    /// in a configuration file).
    /// If the given algorithm name is unknown and non empty secret is
    /// specified, an exception of type InvalidParameter will be thrown.
    ///
    /// secret and secret_len must be consistent in that the latter
    /// is 0 if and only if the former is null;
    /// otherwise an exception of type InvalidParameter will be thrown.
    ///
    /// digestbits is the truncated length in bits or 0 which means no
    /// truncation and is the default. Constraints for non-zero value
    /// are in RFC 4635 section 3.1: minimum 80 or the half of the
    /// full (i.e., not truncated) length, integral number of octets
    /// (i.e., multiple of 8), and maximum the full length.
    ///
    /// This constructor internally involves resource allocation, and if
    /// it fails, a corresponding standard exception will be thrown.
    ///
    /// @param key_name The name of the key as a domain name.
    /// @param algorithm_name The hash algorithm used for this key in the
    /// form of domain name.  For example, it can be
    /// TSIGKey::HMACSHA256_NAME() for HMAC-SHA256.
    /// @param secret Point to a binary sequence of the shared secret to be
    /// used for this key, or null if the secret is empty.
    /// @param secret_len The size of the binary %data (secret) in bytes.
    /// @param digestbits The number of bits to include in the digest
    /// (0 means to include all).
    TSIGKey(const Name& key_name, const Name& algorithm_name,
            const void* secret, size_t secret_len, size_t digestbits = 0);

    /// @brief Constructor from an input string
    ///
    /// The string must be of the form:
    /// name:secret[:algorithm][:digestbits]
    /// Where "name" is a domain name for the key, "secret" is a
    /// base64 representation of the key secret, and the optional
    /// "algorithm" is an algorithm identifier as specified in RFC 4635.
    /// The default algorithm is hmac-md5.sig-alg.reg.int.
    /// "digestbits" is the minimum truncated length in bits.
    /// The default digestbits value is 0 and means truncation is forbidden.
    ///
    /// The same restriction about the algorithm name (and secret) as that
    /// for the other constructor applies.
    ///
    /// Since ':' is used as a separator here, it is not possible to
    /// use this constructor to create keys with a ':' character in
    /// their name.
    ///
    /// @throw InvalidParameter exception if the input string is
    /// invalid.
    ///
    /// @param str The string to make a TSIGKey from
    explicit TSIGKey(const std::string& str);

    /// @brief The copy constructor.
    ///
    /// It internally allocates a resource, and if it fails a corresponding
    /// standard exception will be thrown.
    /// This constructor never throws an exception otherwise.
    TSIGKey(const TSIGKey& source);

    /// @brief Assignment operator.
    ///
    /// It internally allocates a resource, and if it fails a corresponding
    /// standard exception will be thrown.
    /// This operator never throws an exception otherwise.
    ///
    /// This operator provides the strong exception guarantee: When an
    /// exception is thrown the content of the assignment target will be
    /// intact.
    TSIGKey& operator=(const TSIGKey& source);

    /// @brief The destructor.
    virtual ~TSIGKey();
    //@}

    ///
    /// @brief Getter Methods
    ///
    /// These methods never throw an exception.
    //@{
    /// @brief Return the key name.
    const Name& getKeyName() const;

    /// @brief Return the algorithm name.
    const Name& getAlgorithmName() const;

    /// @brief Return the hash algorithm name in the form of cryptolink::HashAlgorithm
    isc::cryptolink::HashAlgorithm getAlgorithm() const;

    /// @brief Return the minimum truncated length.
    size_t getDigestbits() const;

    /// @brief Return the length of the TSIG secret in bytes.
    size_t getSecretLength() const;

    /// @brief Return the value of the TSIG secret.
    ///
    /// If it returns a non null pointer, the memory region beginning at the
    /// address returned by this method is valid up to the bytes specified
    /// by the return value of getSecretLength().
    ///
    /// The memory region is only valid while the corresponding TSIGKey
    /// object is valid.  The caller must hold the TSIGKey object while
    /// it needs to refer to the region or it must make a local copy of the
    /// region.
    const void* getSecret() const;
    //@}

    /// @brief Converts the TSIGKey to a string value
    ///
    /// The resulting string will be of the form
    /// name:secret:algorithm[:digestbits].
    /// Where "name" is a domain name for the key, "secret" is a
    /// base64 representation of the key secret, and "algorithm" is
    /// an algorithm identifier as specified in RFC 4635.
    /// When not zero, digestbits is appended.
    ///
    /// @return The string representation of the given TSIGKey.
    std::string toText() const;

    /// @brief Well known algorithm names as defined in RFC2845 and RFC4635.
    ///
    /// Note: we begin with the "mandatory" algorithms defined in RFC4635
    /// as a minimal initial set.
    /// We'll add others as we see the need for them.
    //@{
    static const Name& HMACMD5_NAME();    // HMAC-MD5 (RFC2845)
    static const Name& HMACMD5_SHORT_NAME();
    static const Name& HMACSHA1_NAME();   // HMAC-SHA1 (RFC4635)
    static const Name& HMACSHA256_NAME(); // HMAC-SHA256 (RFC4635)
    static const Name& HMACSHA224_NAME(); // HMAC-SHA256 (RFC4635)
    static const Name& HMACSHA384_NAME(); // HMAC-SHA256 (RFC4635)
    static const Name& HMACSHA512_NAME(); // HMAC-SHA256 (RFC4635)
    static const Name& GSSTSIG_NAME();    // GSS-TSIG (RFC3645)
    //@}

private:
    struct TSIGKeyImpl;
    boost::shared_ptr<TSIGKeyImpl> impl_;
};

/// @brief A simple repository of a set of TSIGKey objects.
///
/// This is a "key ring" to maintain TSIG keys (TSIGKey objects) and
/// provides trivial operations such as add, remove, and find.
///
/// The keys are identified by their key names.
/// So, for example, two or more keys of the same key name but of different
/// algorithms are considered to be the same, and cannot be stored in the
/// key ring at the same time.
///
/// <b>Implementation Note:</b>
/// For simplicity the initial implementation requests the application make
/// a copy of keys stored in the key ring if it needs to use the keys for
/// a long period (during which some of the keys may be removed).
/// This is based on the observations that a single server will not hold
/// a huge number of keys nor use keys in many different contexts (such as
/// in different DNS transactions).
/// If this assumption does not hold and memory consumption becomes an issue
/// we may have to revisit the design.
class TSIGKeyRing {
public:
    /// Result codes of various public methods of TSIGKeyRing
    enum Result {
        SUCCESS = 0,    // The operation is successful.
        EXIST = 1,      // A key is already stored in TSIGKeyRing.
        NOTFOUND = 2    // The specified key is not found in TSIGKeyRing.
    };

    /// @brief A helper structure to represent the search result of
    /// <code>TSIGKeyRing::find()</code>.
    ///
    /// This is a straightforward pair of the result code and a pointer
    /// to the found key to represent the result of find().
    /// We use this in order to avoid overloading the return value for both
    /// the result code ("success" or "not found") and the found object,
    /// i.e., avoid using null to mean "not found", etc.
    ///
    /// This is a simple value class with no internal state, so for
    /// convenience we allow the applications to refer to the members
    /// directly.
    ///
    /// See the description of find() for the semantics of the member
    /// variables.
    struct FindResult {
        FindResult(Result param_code, const TSIGKey* param_key) :
            code(param_code), key(param_key) {
        }
        const Result code;
        const TSIGKey* const key;
    };

    ///
    /// @brief Constructors and Destructor.
    ///
    /// @note The copy constructor and the assignment operator are
    /// intentionally defined as private, making this class non copyable.
    /// There is no technical reason why this class cannot be copied,
    /// but since the key ring can potentially have a large number of keys,
    /// a naive copy operation may cause unexpected overhead.
    /// It's generally expected for an application to share the same
    /// instance of key ring and share it throughout the program via
    /// references, so we prevent the copy operation explicitly to avoid
    /// unexpected copy operations.
    //@{
private:
    TSIGKeyRing(const TSIGKeyRing& source);
    TSIGKeyRing& operator=(const TSIGKeyRing& source);
public:
    /// @brief The default constructor.
    ///
    /// This constructor never throws an exception.
    TSIGKeyRing();

    /// @brief The destructor.
    ~TSIGKeyRing();
    //@}

    /// @brief Return the number of keys stored in the TSIGKeyRing.
    ///
    /// This method never throws an exception.
    unsigned int size() const;

    /// @brief Add a TSIGKey to the TSIGKeyRing.
    ///
    /// This method will create a local copy of the given key, so the caller
    /// does not have to keep owning it.
    ///
    /// If internal resource allocation fails, a corresponding standard
    /// exception will be thrown.
    /// This method never throws an exception otherwise.
    ///
    /// @param key A TSIGKey to be added.
    /// @return SUCCESS if the key is successfully added to the key ring or
    /// EXIST if the key ring already stores a key whose name is identical to
    /// that of key.
    Result add(const TSIGKey& key);

    /// Remove a TSIGKey for the given name from the TSIGKeyRing.
    ///
    /// This method never throws an exception.
    ///
    /// @param key_name The name of the key to be removed.
    /// @return SUCCESS if the key is successfully removed from the key
    /// ring or NOTFOUND  if the key ring does not store the key that matches
    /// key_name.
    Result remove(const Name& key_name);

    /// Find a TSIGKey for the given name in the TSIGKeyRing.
    ///
    /// It searches the internal storage for a TSIGKey whose name is
    /// key_name.
    /// It returns the result in the form of a FindResult
    /// object as follows:
    /// - code: SUCCESS if a key is found; otherwise NOTFOUND.
    /// - key: A pointer to the found TSIGKey object if one is found;
    /// otherwise null.
    ///
    /// The pointer returned in the FindResult object is only valid until
    /// the corresponding key is removed from the key ring.
    /// The caller must ensure that the key is held in the key ring while
    /// it needs to refer to it, or it must make a local copy of the key.
    ///
    /// This method never throws an exception.
    ///
    /// @param key_name The name of the key to be found.
    /// @return A FindResult object enclosing the search result (see above).
    FindResult find(const Name& key_name) const;

    /// Find a TSIGKey for the given name in the TSIGKeyRing.
    ///
    /// It searches the internal storage for a TSIGKey whose name is
    /// key_name and that uses the hash algorithm identified by
    /// algorithm_name.
    /// It returns the result in the form of a FindResult
    /// object as follows:
    /// - code: SUCCESS if a key is found; otherwise NOTFOUND.
    /// - key: A pointer to the found TSIGKey object if one is found;
    /// otherwise null.
    ///
    /// The pointer returned in the FindResult object is only valid until
    /// the corresponding key is removed from the key ring.
    /// The caller must ensure that the key is held in the key ring while
    /// it needs to refer to it, or it must make a local copy of the key.
    ///
    /// This method never throws an exception.
    ///
    /// @param key_name The name of the key to be found.
    /// @param algorithm_name The name of the algorithm of the found key.
    /// @return A FindResult object enclosing the search result (see above).
    FindResult find(const Name& key_name, const Name& algorithm_name) const;

private:
    struct TSIGKeyRingImpl;
    boost::shared_ptr<TSIGKeyRingImpl> impl_;
};
}
}

#endif  // TSIGKEY_H
