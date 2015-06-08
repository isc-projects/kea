// Copyright (C) 2015  Internet Systems Consortium, Inc. ("ISC")
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

namespace isc {
namespace cryptolink {

/// @brief Botan implementation of asymmetrical cryptography (Asym).          
// Each method is the counterpart of the Asym corresponding method.
// ECDSA
class EcDsaAsymImpl : public AsymImpl {
public:
    /// @brief Constructor from a key, asym and hash algorithm,
    ///        key kind and key binary format
    ///
    /// See constructor of the @ref isc::cryptolink::Asym class for details.
    ///
    /// @param key            The key to sign/verify with
    /// @param len            The length of the key
    /// @param hash_algorithm The hash algorithm
    /// @param key_kind       The key kind
    /// @param key_format     The key binary format
    EcDsaAsymImpl(const void* key, size_t key_len,
                  const HashAlgorithm hash_algorithm,
                  const AsymKeyKind key_kind,
                  const AsymFormat key_format);

    /// @brief Constructor from a key file with password,
    ///        asym and hash algorithm, key kind and key binary format
    ///
    /// See constructor of the @ref isc::cryptolink::Asym class for details.
    ///
    /// @param filename       The key file name/path
    /// @param password       The PKCS#8 password
    /// @param hash_algorithm The hash algorithm
    /// @param key_kind       The key kind
    /// @param key_format     The key binary format
    EcDsaAsymImpl(const std::string& filename,
                  const std::string& password,
                  const HashAlgorithm hash_algorithm,
                  const AsymKeyKind key_kind,
                  const AsymFormat key_format);

    /// @brief Destructor
    ~EcDsaAsymImpl();

    /// @brief Returns the AsymAlgorithm of the object
    AsymAlgorithm getAsymAlgorithm() const;

    /// @brief Returns the HashAlgorithm of the object
    HashAlgorithm getHashAlgorithm() const;

    /// @brief Returns the AsymKeyKind of the object
    AsymKeyKind getAsymKeyKind() const;

    /// @brief Returns the key size in bits
    size_t getKeySize() const;

    /// @brief Returns the output size of the signature
    ///
    /// \param sig_format The signature binary format
    size_t getSignatureLength(const AsymFormat sig_format) const;

    /// @brief Add data to digest
    ///
    /// See @ref isc::cryptolink::AsymBase::update() for details.
    void update(const void* data, const size_t len);

    /// @brief Calculate the final signature
    ///
    /// See @ref isc::cryptolink::AsymBase::sign() for details.
    void sign(isc::util::OutputBuffer& result, size_t len, const AsymFormat);

    /// @brief Calculate the final signature
    ///
    /// See @ref isc::cryptolink::AsymBase::sign() for details.
    void sign(void* result, size_t len, const AsymFormat sig_format);

    /// @brief Calculate the final signature
    ///
    /// See @ref isc::cryptolink::AsymBase::sign() for details.
    std::vector<uint8_t> sign(size_t len, const AsymFormat);

    /// @brief Verify an existing signature
    ///
    /// See @ref isc::cryptolink::AsymBase::verify() for details.
    bool verify(const void* sig, size_t len, const AsymFormat sig_format);

    /// \brief Clear the crypto state and go back to the initial state
    /// (must be called before reusing an Asym object)
    void clear();

    /// @brief Export the key value (binary)
    ///
    /// See @ref isc::cryptolink::AsymBase::exportkey() for details
    std::vector<uint8_t> exportkey(const AsymKeyKind key_kind,
                                   const AsymFormat key_format) const;

    /// @brief Export the key value (file)
    ///
    /// See @ref isc::cryptolink::AsymBase::exportkey() for details
    void exportkey(const std::string& filename,
                   const std::string& password,
                   const AsymKeyKind key_kind,
                   const AsymFormat key_format) const;

    /// @brief Check the validity
    ///
    /// See @ref isc::cryptolink::AsymBase::validate() for details
    bool validate() const;

    /// @brief Compare two keys
    ///
    /// See @ref isc::cryptolink::Asym::compare() for details
    bool compare(const EcDsaAsymImpl* other, const AsymKeyKind key_kind) const;

private:
    /// @brief The asymmetrical cryptography algorithm
    AsymAlgorithm algo_;
    /// @brief The hash algorithm
    HashAlgorithm hash_;
    /// @brief The key kind
    AsymKeyKind kind_;
    /// @brief The encoding method for signature with appendix
    std::string emsa_;
    /// @brief The curve/group
    Botan::EC_Group group_;
    /// @brief The protected pointer to the Botan private key
    boost::scoped_ptr<Botan::ECDSA_PrivateKey> priv_;
    /// @brief The protected pointer to the Botan public key
    boost::scoped_ptr<Botan::ECDSA_PublicKey> pub_;
    /// @brief The protected pointer to the Botan certificate
    boost::scoped_ptr<Botan::X509_Certificate> x509_;
    /// @brief The protected pointer to the Botan signer
    boost::scoped_ptr<Botan::PK_Signer> signer_;
    /// @brief The protected pointer to the Botan verifier
    boost::scoped_ptr<Botan::PK_Verifier> verifier_;
};

} // namespace cryptolink
} // namespace isc
