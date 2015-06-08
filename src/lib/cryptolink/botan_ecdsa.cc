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

#include <cryptolink.h>
#include <cryptolink/crypto_asym.h>

#include <boost/scoped_ptr.hpp>

#include <botan/version.h>
#include <botan/botan.h>
#include <botan/hash.h>
#include <botan/oids.h>
#include <botan/pubkey.h>
#include <botan/ecdsa.h>
#include <botan/x509stor.h>
#include <botan/der_enc.h>
#include <botan/pem.h>

#include <util/encode/base64.h>
#include <cryptolink/botan_common.h>
#include <cryptolink/botan_ecdsa.h>

#include <cstring>
#include <fstream>

namespace isc {
namespace cryptolink {

/// @brief Constructor from a key, asym and hash algorithm,
///        key kind and key binary format
EcDsaAsymImpl::EcDsaAsymImpl(const void* key, size_t key_len,
                             const HashAlgorithm hash_algorithm,
                             const AsymKeyKind key_kind,
                             const AsymFormat key_format) {
    algo_ = ECDSA_;
    hash_ = hash_algorithm;
    kind_ = key_kind;
    switch (hash_) {
    case SHA256:
        emsa_ = "EMSA1(SHA-256)";
        group_ = Botan::EC_Group("secp256r1");
        break;
    case SHA384:
        emsa_ = "EMSA1(SHA-384)";
        group_ = Botan::EC_Group("secp384r1");
        break;
    default:
        isc_throw(UnsupportedAlgorithm,
                  "Unknown hash algorithm: " << static_cast<int>(hash_));
    }
    if (key_len == 0) {
        isc_throw(BadKey, "Bad ECDSA " <<
                  (kind_ != CERT ? "key" : "cert") << " length: 0");
    }

    if ((kind_ == PRIVATE) && (key_format == BASIC)) {
        // The private key is just a number
        const Botan::byte* keyin = reinterpret_cast<const Botan::byte*>(key);
        Botan::BigInt privkey(keyin, key_len);
        Botan::AutoSeeded_RNG rng;
        try {
            priv_.reset(new Botan::ECDSA_PrivateKey(rng, group_, privkey));
        } catch (const std::exception& exc) {
            isc_throw(BadKey, "ECDSA_PrivateKey: " << exc.what());
        }
    } else if (kind_ == PRIVATE) {
        isc_throw(UnsupportedAlgorithm,
                  "Unknown ECDSA Private Key format: " <<
                  static_cast<int>(key_format));
    } else if ((kind_ == PUBLIC) && (key_format == ASN1)) {
        // SubjectPublicKeyInfo
        const Botan::byte* keyin = reinterpret_cast<const Botan::byte*>(key);
        Botan::DataSource_Memory source(keyin, key_len);
        Botan::Public_Key* key;
        try {
            key = Botan::X509::load_key(source);
        } catch (const std::exception& exc) {
            isc_throw(BadKey, "X509::load_key: " << exc.what());
        }
        if (key->algo_name().compare("ECDSA") != 0) {
            delete key;
            isc_throw(BadKey, "not a ECDSA Public Key");
        }
        pub_.reset(dynamic_cast<Botan::ECDSA_PublicKey*>(key));
        if (!pub_) {
            delete key;
            isc_throw(LibraryError, "dynamic_cast");
        }
        if (pub_->domain() != group_) {
            isc_throw(BadKey, "ECDSA Public Key not for the right curve");
        }
    } else if ((kind_ == PUBLIC) && (key_format == DNS)) {
        // RFC 6605 DNS wire format
        // key_len == 0 was already checked
        size_t len;
        std::string algo_name;
        if (hash_ == SHA256) {
            len = 64;
            algo_name = "ECDSA P256";
        } else {
            len = 96;
            algo_name ="ECDSA P384";
        }
        if (key_len != len) {
            isc_throw(BadKey, "Bad " << algo_name <<
                      "Public Key length: " <<
                      key_len << ", expected " << len);
        }
        Botan::SecureVector<Botan::byte> pubbin(len + 1);
        pubbin[0] = 4;
        std::memcpy(&pubbin[1], key, len);
        try {
            Botan::PointGFp pubkey = Botan::OS2ECP(pubbin, group_.get_curve());
            pub_.reset(new Botan::ECDSA_PublicKey(group_, pubkey));
        } catch (const std::exception& exc) {
            isc_throw(BadKey, "ECDSA_PublicKey: " << exc.what());
        }
    } else if (kind_ == PUBLIC) {
        isc_throw(UnsupportedAlgorithm,
                  "Unknown ECDSA Public Key format: " <<
                  static_cast<int>(key_format));
    } else if ((kind_ == CERT) && (key_format == ASN1)) {
        // X.509 Public Key Certificate
        const Botan::byte* keyin = reinterpret_cast<const Botan::byte*>(key);
        Botan::DataSource_Memory source(keyin, key_len);
        try {
            x509_.reset(new Botan::X509_Certificate(source));
        } catch (const std::exception& exc) {
            isc_throw(BadKey, "X509_Certificate: " << exc.what());
        }
        const Botan::AlgorithmIdentifier
            sig_algo(x509_->signature_algorithm());
        if (hash_ == SHA256) {
            const Botan::AlgorithmIdentifier
                ecdsa_sha256("1.2.840.10045.4.3.2",
                             Botan::AlgorithmIdentifier::USE_NULL_PARAM);
            if (sig_algo != ecdsa_sha256) {
                x509_.reset();
                isc_throw(BadKey, "Require a ECDSA SHA256 certificate");
            }
        } else if (hash_ == SHA384) {
            const Botan::AlgorithmIdentifier
                ecdsa_sha384("1.2.840.10045.4.3.3",
                             Botan::AlgorithmIdentifier::USE_NULL_PARAM);
            if (sig_algo != ecdsa_sha384) {
                x509_.reset();
                isc_throw(BadKey, "Require a ECDSA SHA384 certificate");
            }
        } else {
            x509_.reset();
            isc_throw(UnsupportedAlgorithm,
                      "Bad hash algorithm for certificate: " <<
                      static_cast<int>(hash_));
        }
        Botan::Public_Key* key = x509_->subject_public_key();
        if (key->algo_name().compare("ECDSA") != 0) {
            delete key;
            x509_.reset();
            isc_throw(BadKey, "not a ECDSA Certificate");
        }
        pub_.reset(dynamic_cast<Botan::ECDSA_PublicKey*>(key));
        if (!pub_) {
            delete key;
            x509_.reset();
            isc_throw(LibraryError, "dynamic_cast");
        }
    } else if (kind_ == CERT) {
        isc_throw(UnsupportedAlgorithm,
                  "Unknown Certificate format: " <<
                  static_cast<int>(key_format));
    } else {
        isc_throw(UnsupportedAlgorithm,
                  "Unknown ECDSA Key kind: " << static_cast<int>(kind_));
    }

    if (kind_ == PRIVATE) {
        try {
            if (!pub_) {
                pub_.reset(new Botan::ECDSA_PublicKey(group_,
                                                      priv_->public_point()));
            }
        } catch (const std::exception& exc) {
            isc_throw(BadKey, "priv to pub: " << exc.what());
        }
        try {
            signer_.reset(new Botan::PK_Signer(*priv_, emsa_));
        } catch (const std::exception& exc) {
            isc_throw(BadKey, "PK_Signer: " << exc.what());
        }
    } else {
        try {
            verifier_.reset(new Botan::PK_Verifier(*pub_, emsa_));
        } catch (const std::exception& exc) {
            isc_throw(BadKey, "PK_Verifier: " << exc.what());
        }
    }
}

/// @brief Constructor from a key file with password,
///        asym and hash algorithm, key kind and key binary format
EcDsaAsymImpl::EcDsaAsymImpl(const std::string& filename,
                         const std::string& password,
                         const HashAlgorithm hash_algorithm,
                         const AsymKeyKind key_kind,
                         const AsymFormat key_format) {
    algo_ = ECDSA_;
    hash_ = hash_algorithm;
    kind_ = key_kind;
    switch (hash_) {
    case SHA256:
        emsa_ = "EMSA1(SHA-256)";
        group_ = Botan::EC_Group("secp256r1");
        break;
    case SHA384:
        emsa_ = "EMSA1(SHA-384)";
        group_ = Botan::EC_Group("secp384r1");
        break;
    default:
        isc_throw(UnsupportedAlgorithm,
                  "Unknown hash algorithm: " << static_cast<int>(hash_));
    }

    if ((kind_ == PRIVATE) && (key_format == ASN1)) {
        // PKCS#8 Private Key PEM file
        Botan::Private_Key* key;
        Botan::AutoSeeded_RNG rng;
        try {
            key = Botan::PKCS8::load_key(filename, rng, password);
        } catch (const std::exception& exc) {
            isc_throw(BadKey, "PKCS8::load_key: " << exc.what());
        }
        if (key->algo_name().compare("ECDSA") != 0) {
            delete key;
            isc_throw(BadKey, "not a ECDSA Private Key");
        }
        priv_.reset(dynamic_cast<Botan::ECDSA_PrivateKey*>(key));
        if (!priv_) {
            delete key;
            isc_throw(LibraryError, "dynamic_cast");
        }
        if (priv_->domain() != group_) {
            isc_throw(BadKey, "ECDSA Private Key not for the right curve");
        }
    } else if ((kind_ == PRIVATE) && (key_format == DNS)) {
        // bind9 .private file
        // warn when password not empty
        std::ifstream fp(filename.c_str(), std::ios::in);
        if (!fp.is_open()) {
            isc_throw(BadKey, "Can't open file: " << filename);
        }
        bool got_algorithm = false;
        bool got_privatekey = false;
        Botan::BigInt privkey;
        while (fp.good()) {
            std::string line;
            getline(fp, line);
            if (line.find("Algorithm:") == 0) {
                if (got_algorithm) {
                    fp.close();
                    isc_throw(BadKey, "Two Algorithm entries");
                }
                got_algorithm = true;
                std::string value = line.substr(strlen("Algorithm:") + 1,
                                                std::string::npos);
                int alg = std::atoi(value.c_str());
                if (alg == 13) {
                    // ECDSAP256SHA256
                    if (hash_ != SHA256) {
                        fp.close();
                        isc_throw(BadKey, "Require a ECDSA P256 key");
                    }
                } else if (alg == 14) {
                    // ECDSAP384SHA384
                    if (hash_ != SHA384) {
                        fp.close();
                        isc_throw(BadKey, "Require a ECDSA P384 key");
                    }
                } else {
                    fp.close();
                    isc_throw(BadKey, "Bad Algorithm: " << alg);
                }
            } else if (line.find("PrivateKey:") == 0) {
                if (got_privatekey) {
                    fp.close();
                    isc_throw(BadKey, "Two PrivateKey entries");
                }
                got_privatekey = true;
                std::string value =
                    line.substr(strlen("PrivateKey:") + 1,
                                std::string::npos);
                std::vector<uint8_t> bin;
                try {
                    isc::util::encode::decodeBase64(value, bin);
                } catch (const BadValue& exc) {
                    fp.close();
                    isc_throw(BadKey, "PrivateKey: " << exc.what());
                }
                privkey = Botan::BigInt(&bin[0], bin.size());
            }
        }
        fp.close();
        // Check first the existence of the PrivateKey
        if (!got_privatekey) {
            isc_throw(BadKey, "Missing PrivateKey entry");
        }
        if (!got_algorithm) {
            isc_throw(BadKey, "Missing Algorithm entry");
        }
        Botan::AutoSeeded_RNG rng;
        try {
            priv_.reset(new Botan::ECDSA_PrivateKey(rng, group_, privkey));
        } catch (const std::exception& exc) {
            isc_throw(BadKey, "ECDSA_PrivateKey" << exc.what());
        }
    } else if (kind_ == PRIVATE) {
        isc_throw(UnsupportedAlgorithm,
                  "Unknown ECDSA Private Key format: " <<
                  static_cast<int>(key_format));
    } else if ((kind_ == PUBLIC) && (key_format == ASN1)) {
        // SubjectPublicKeyInfo PEM file
        // warn when password not empty
        Botan::Public_Key* key;
        try {
            key = Botan::X509::load_key(filename);
        } catch (const std::exception& exc) {
            isc_throw(BadKey, "X509::load_key: " << exc.what());
        }
        if (key->algo_name().compare("ECDSA") != 0) {
            delete key;
            isc_throw(BadKey, "not a ECDSA Public Key");
        }
        pub_.reset(dynamic_cast<Botan::ECDSA_PublicKey*>(key));
        if (!pub_) {
            delete key;
            isc_throw(LibraryError, "dynamic_cast");
        }
        if (pub_->domain() != group_) {
            isc_throw(BadKey, "ECDSA Public Key not for the right curve");
        }
    } else if ((kind_ == PUBLIC) && (key_format == DNS)) {
        // bind9 .key file (RDATA)
        // warn when password not empty
        std::ifstream fp(filename.c_str(), std::ios::in);
        if (!fp.is_open()) {
            isc_throw(BadKey, "Can't open file: " << filename);
        }
        std::string line;
        bool found = false;
        while (fp.good()) {
            getline(fp, line);
            if (line.empty() || (line[0] == ';')) {
                continue;
            }
            if (line.find("DNSKEY") == std::string::npos) {
                continue;
            }
            found = true;
            if (line[line.size() - 1] == '\n') {
                line.erase(line.size() - 1);
            }
            break;
        }
        fp.close();
        if (!found) {
            isc_throw(BadKey, "Can't find a DNSKEY");
        }
        const std::string b64 =
            "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdef"
            "ghijklmnopqrstuvwxyz0123456789+/=";
        const std::string value = line.substr(line.find_last_not_of(b64));
        std::vector<uint8_t> bin;
        try {
            util::encode::decodeBase64(value, bin);
        } catch (const BadValue& exc) {
           isc_throw(BadKey, "Can't decode base64: " << exc.what());
        }
        size_t len;
        std::string algo_name;
        if (hash_ == SHA256) {
            len = 64;
            algo_name = "ECDSA P256";
        } else {
            len = 96;
            algo_name ="ECDSA P384";
        }
        if (bin.size() != len) {
            isc_throw(BadKey, "Bad " << algo_name <<
                      "Public Key length: " <<
                      bin.size() << ", expected " << len);
        }
        Botan::SecureVector<Botan::byte> pubbin(len + 1);
        pubbin[0] = 4;
        std::memcpy(&pubbin[1], &bin[0], len);
        try {
            Botan::PointGFp pubkey = Botan::OS2ECP(pubbin, group_.get_curve());
            pub_.reset(new Botan::ECDSA_PublicKey(group_, pubkey));
        } catch (const std::exception& exc) {
            isc_throw(BadKey, "ECDSA_PublicKey: " << exc.what());
        }
    } else if (kind_ == PUBLIC) {
        isc_throw(UnsupportedAlgorithm,
                  "Unknown ECDSA Public Key format: " <<
                  static_cast<int>(key_format));
    } else if ((kind_ == CERT) && (key_format == ASN1)) {
        // X.509 Public Key Certificate PEM file
        // warn when password not empty
        try {
            x509_.reset(new Botan::X509_Certificate(filename));
        } catch (const std::exception& exc) {
            isc_throw(BadKey, "X509_Certificate: " << exc.what());
        }
        const Botan::AlgorithmIdentifier
            sig_algo(x509_->signature_algorithm());
        if (hash_ == SHA256) {
            const Botan::AlgorithmIdentifier
                ecdsa_sha256("1.2.840.10045.4.3.2",
                             Botan::AlgorithmIdentifier::USE_NULL_PARAM);
            if (sig_algo != ecdsa_sha256) {
                x509_.reset();
                isc_throw(BadKey, "Require a ECDSA SHA256 certificate");
            }
        } else if (hash_ == SHA384) {
            const Botan::AlgorithmIdentifier
                ecdsa_sha384("1.2.840.10045.4.3.3",
                             Botan::AlgorithmIdentifier::USE_NULL_PARAM);
            if (sig_algo != ecdsa_sha384) {
                x509_.reset();
                isc_throw(BadKey, "Require a ECDSA SHA384 certificate");
            }
        } else {
            x509_.reset();
            isc_throw(UnsupportedAlgorithm,
                      "Bad hash algorithm for certificate: " <<
                      static_cast<int>(hash_));
        }
        Botan::Public_Key* key;
        try {
            key = x509_->subject_public_key();
        } catch (const std::exception& exc) {
            x509_.reset();
            isc_throw(BadKey, "subject_public_key: " << exc.what());
        }
        if (key->algo_name().compare("ECDSA") != 0) {
            delete key;
            x509_.reset();
            isc_throw(BadKey, "not a ECDSA Public Key");
        }
        pub_.reset(dynamic_cast<Botan::ECDSA_PublicKey*>(key));
        if (!pub_) {
            delete key;
            x509_.reset();
            isc_throw(LibraryError, "dynamic_cast");
        }
    } else if (kind_ == CERT) {
        isc_throw(UnsupportedAlgorithm,
                  "Unknown Public Key Certificate format: " <<
                  static_cast<int>(key_format));
    } else {
        isc_throw(UnsupportedAlgorithm,
                  "Unknown ECDSA Key kind: " << static_cast<int>(kind_));
    }

    if (kind_ == PRIVATE) {
        try {
            if (!pub_) {
                pub_.reset(new Botan::ECDSA_PublicKey(group_,
                                                      priv_->public_point()));
            }
        } catch (const std::exception& exc) {
            isc_throw(BadKey, "priv to pub: " << exc.what());
        }
        try {
            signer_.reset(new Botan::PK_Signer(*priv_, emsa_));
        } catch (const std::exception& exc) {
            isc_throw(BadKey, "PK_Signer: " << exc.what());
        }
    } else {
        try {
            verifier_.reset(new Botan::PK_Verifier(*pub_, emsa_));
        } catch (const std::exception& exc) {
            isc_throw(BadKey, "PK_Verifier: " << exc.what());
        }
    }
}

/// @brief Destructor
EcDsaAsymImpl::~EcDsaAsymImpl() { }

/// @brief Returns the AsymAlgorithm of the object
AsymAlgorithm EcDsaAsymImpl::getAsymAlgorithm() const {
    return (algo_);
}

/// @brief Returns the HashAlgorithm of the object
HashAlgorithm EcDsaAsymImpl::getHashAlgorithm() const {
    return (hash_);
}

/// @brief Returns the AsymKeyKind of the object
AsymKeyKind EcDsaAsymImpl::getAsymKeyKind() const {
    return (kind_);
}

/// @brief Returns the key size in bits
size_t EcDsaAsymImpl::getKeySize() const {
    return (hash_ == SHA256 ? 256 : 384);
}

/// @brief Returns the output size of the signature
size_t EcDsaAsymImpl::getSignatureLength(const AsymFormat sig_format) const {
    switch (sig_format) {
    case BASIC:
    case DNS:
        // In both cases a pair of big integers
        return (hash_ == SHA256 ? 64 : 96);
    case ASN1:
        // Compute the maximum size of the ASN.1 structure
        return (hash_ == SHA256 ? 64 + 8 : 96 + 8);
    default:
        isc_throw(UnsupportedAlgorithm,
                  "Unknown ECDSA Signature format: " <<
                  static_cast<int>(sig_format));
    }
}           

/// @brief Add data to digest
void EcDsaAsymImpl::update(const void* data, const size_t len) {
    try {
        if (kind_ == PRIVATE) {
            signer_->update(reinterpret_cast<const Botan::byte*>(data), len);
        } else {
            verifier_->update(reinterpret_cast<const Botan::byte*>(data), len);
        }            
    } catch (const std::exception& exc) {
        isc_throw(LibraryError, "update: " << exc.what());
    }
}

/// @brief Calculate the final signature
void EcDsaAsymImpl::sign(isc::util::OutputBuffer& result, size_t len,
                         const AsymFormat sig_format) {
    // Check the signature format
    if ((sig_format != BASIC) &&
        (sig_format != ASN1) &&
        (sig_format != DNS)) {
        isc_throw(UnsupportedAlgorithm,
                  "Unknown Signature format: " <<
                  static_cast<int>(sig_format));
    }
    
    // Get the signature
    Botan::SecureVector<Botan::byte> b_result;
    try {
        Botan::AutoSeeded_RNG rng;
        b_result = signer_->signature(rng);
    } catch (const std::exception& exc) {
        isc_throw(LibraryError, "signature: " << exc.what());
    }

    // Build the result
    if ((sig_format == BASIC) || (sig_format == DNS)) {
        if (len > b_result.size()) {
            len = b_result.size();
        }
        result.writeData(b_result.begin(), len);
    } else {
        std::vector<Botan::BigInt> parts(2);
        if (b_result.size() % 2) {
            isc_throw(LibraryError, "odd signature length");
        }
        size_t part_len = b_result.size() / 2;
        parts[0].binary_decode(&b_result[0], part_len);
        parts[1].binary_decode(&b_result[part_len], part_len);
        Botan::SecureVector<Botan::byte> der =
            Botan::DER_Encoder()
                .start_cons(Botan::SEQUENCE)
                    .encode_list(parts)
                .end_cons()
            .get_contents();
        if (len > der.size()) {
            len = der.size();
        }
        result.writeData(der.begin(), len);
    }
}

/// @brief Calculate the final signature
void EcDsaAsymImpl::sign(void* result, size_t len,
                         const AsymFormat sig_format) {
    // Check the signature format
    if ((sig_format != BASIC) &&
        (sig_format != ASN1) &&
        (sig_format != DNS)) {
        isc_throw(UnsupportedAlgorithm,
                  "Unknown Signature format: " <<
                  static_cast<int>(sig_format));
    }
    
    // Get the signature
    Botan::SecureVector<Botan::byte> b_result;
    try {
        Botan::AutoSeeded_RNG rng;
        b_result = signer_->signature(rng);
    } catch (const std::exception& exc) {
        isc_throw(LibraryError, "signature: " << exc.what());
    }

    // Build the result
    if ((sig_format == BASIC) || (sig_format == DNS)) {
        size_t output_size = getSignatureLength(sig_format);
        if (output_size > len) {
            output_size = len;
        }
        std::memcpy(result, b_result.begin(), output_size);
    } else {
        std::vector<Botan::BigInt> parts(2);
        if (b_result.size() % 2) {
            isc_throw(LibraryError, "odd signature length");
        }
        size_t part_len = b_result.size() / 2;
        parts[0].binary_decode(&b_result[0], part_len);
        parts[1].binary_decode(&b_result[part_len], part_len);
        Botan::SecureVector<Botan::byte> der =
            Botan::DER_Encoder()
                .start_cons(Botan::SEQUENCE)
                    .encode_list(parts)
                .end_cons()
            .get_contents();
        size_t output_size = der.size();
        if (output_size > len) {
            output_size = len;
        }
        std::memcpy(result, der.begin(), output_size);
    }
}

/// @brief Calculate the final signature
std::vector<uint8_t> EcDsaAsymImpl::sign(size_t len,
                                         const AsymFormat sig_format) {
    // Check the signature format
    if ((sig_format != BASIC) &&
        (sig_format != ASN1) &&
        (sig_format != DNS)) {
        isc_throw(UnsupportedAlgorithm,
                  "Unknown Signature format: " <<
                  static_cast<int>(sig_format));
    }
    
    // Get the signature
    Botan::SecureVector<Botan::byte> b_result;
    try {
        Botan::AutoSeeded_RNG rng;
        b_result = signer_->signature(rng);
    } catch (const std::exception& exc) {
        isc_throw(LibraryError, "signature: " << exc.what());
    }

    // Build the result
    if ((sig_format == BASIC) || (sig_format == DNS)) {
        if (len > b_result.size()) {
            return (std::vector<uint8_t>(b_result.begin(), b_result.end()));
        } else {
            return (std::vector<uint8_t>(b_result.begin(), &b_result[len]));
        }
    } else {
        std::vector<Botan::BigInt> parts(2);
        if (b_result.size() % 2) {
            isc_throw(LibraryError, "odd signature length");
        }
        size_t part_len = b_result.size() / 2;
        parts[0].binary_decode(&b_result[0], part_len);
        parts[1].binary_decode(&b_result[part_len], part_len);
        Botan::SecureVector<Botan::byte> der =
            Botan::DER_Encoder()
                .start_cons(Botan::SEQUENCE)
                    .encode_list(parts)
                .end_cons()
            .get_contents();
        size_t sig_size = der.size();
        der.resize(len < sig_size ? len : sig_size);
        return (std::vector<uint8_t>(der.begin(), der.end()));
    }
}

/// @brief Verify an existing signature
bool EcDsaAsymImpl::verify(const void* sig, size_t len,
                           const AsymFormat sig_format) {
    // Handle the signature format
    if ((sig_format == BASIC) || (sig_format == DNS)) {
        verifier_->set_input_format(Botan::IEEE_1363);
        if (len != getSignatureLength(sig_format)) {
            return false;
        }
    } else if (sig_format == ASN1) {
        verifier_->set_input_format(Botan::DER_SEQUENCE);
    } else {
        isc_throw(UnsupportedAlgorithm,
                  "Unknown Signature format: " <<
                  static_cast<int>(sig_format));
    }
    
    // Check the signature
    const Botan::byte* sigbuf = reinterpret_cast<const Botan::byte*>(sig);
    try {
        return verifier_->check_signature(sigbuf, len);
    } catch (const std::exception& exc) {
        isc_throw(LibraryError, "check_signature: " << exc.what());
    }
}

/// \brief Clear the crypto state and go back to the initial state
void EcDsaAsymImpl::clear() {
    if (kind_ == PRIVATE) {
        try {
            signer_.reset(new Botan::PK_Signer(*priv_, emsa_));
        } catch (const std::exception& exc) {
            isc_throw(BadKey, "PK_Signer: " << exc.what());
        }
    } else {
        try {
            verifier_.reset(new Botan::PK_Verifier(*pub_, emsa_));
        } catch (const std::exception& exc) {
            isc_throw(BadKey, "PK_Verifier: " << exc.what());
        }
    }
}

/// @brief Export the key value (binary)
std::vector<uint8_t>
    EcDsaAsymImpl::exportkey(const AsymKeyKind key_kind,
                           const AsymFormat key_format) const {
    if ((key_kind == PRIVATE) && (key_format == BASIC)) {
        // The private key is as just a number
        if (kind_ != PRIVATE) {
            isc_throw(UnsupportedAlgorithm, "Have no ECDSA Private Key");
        }
        Botan::BigInt privkey = priv_->private_value();
        std::vector<uint8_t> val(privkey.bytes());
        privkey.binary_encode(&val[0]);
        return val;
    } else if (key_kind == PRIVATE) {
        isc_throw(UnsupportedAlgorithm,
                  "Unknown ECDSA Private Key format: " <<
                  static_cast<int>(key_format));
    } else if ((key_kind == PUBLIC) && (key_format == ASN1)) {
        // SubjectPublicKeyInfo
        // Expand encoding to force namedCurve and uncompressed
        Botan::MemoryVector<Botan::byte> ber;
        try {
            // ber = Botan::X509::BER_encode(*pub_);
            const Botan::MemoryVector<Botan::byte> parameters =
                pub_->domain().DER_encode(Botan::EC_DOMPAR_ENC_OID);
            const Botan::AlgorithmIdentifier alg_id(pub_->get_oid(),
                                                    parameters);
            const Botan::MemoryVector<Botan::byte> pubkey =
                Botan::EC2OSP(pub_->public_point(),
                              Botan::PointGFp::UNCOMPRESSED);
            ber = Botan::DER_Encoder()
                     .start_cons(Botan::SEQUENCE)
                        .encode(alg_id)
                        .encode(pubkey, Botan::BIT_STRING)
                    .end_cons()
                .get_contents();
        } catch (const std::exception& exc) {
            isc_throw(LibraryError, "X509::BER_encode: " << exc.what());
        }
        return std::vector<uint8_t>(ber.begin(), ber.end());
    } else if ((key_kind == PUBLIC) && (key_format == DNS)) {
        // RFC 6605 DNS wire format
        Botan::PointGFp pubkey = pub_->public_point();
        Botan::SecureVector<Botan::byte> repr =
            Botan::EC2OSP(pubkey, Botan::PointGFp::UNCOMPRESSED);
        return std::vector<uint8_t>(repr.begin() + 1, repr.end());
    } else if (key_kind == PUBLIC) {
        isc_throw(UnsupportedAlgorithm,
                  "Unknown ECDSA Public Key format: " <<
                  static_cast<int>(key_format));
    } else if ((key_kind == CERT) && (key_format == ASN1)) {
        // X.509 Public Key Certificate
        if (kind_ != CERT) {
            isc_throw(UnsupportedAlgorithm, "Have no Certificate");
        }
        Botan::MemoryVector<Botan::byte> ber;
        try {
            ber = x509_->BER_encode();
        } catch (const std::exception& exc) {
            isc_throw(LibraryError, "BER_encode" << exc.what());
        }
        return std::vector<uint8_t>(ber.begin(), ber.end());
    } else if (key_kind == CERT) {
        isc_throw(UnsupportedAlgorithm,
                  "Unknown Certificate format: " <<
                  static_cast<int>(key_format));
    } else {
        isc_throw(UnsupportedAlgorithm,
                  "Unknown ECDSA Key kind: " << static_cast<int>(key_kind));
    }
}

/// @brief Export the key value (file)
void EcDsaAsymImpl::exportkey(const std::string& filename,
                            const std::string& password,
                            const AsymKeyKind key_kind,
                            const AsymFormat key_format) const {
    if ((key_kind == PRIVATE) && (key_format == ASN1)) {
        // PKCS#8 Private Key PEM file
        std::string pem;
        Botan::AutoSeeded_RNG rng;
        try {
            pem = Botan::PKCS8::PEM_encode(*priv_, rng,
                                           password, "AES-128/CBC");
        } catch (const std::exception& exc) {
            isc_throw(LibraryError, "PKCS8::PEM_encode: " << exc.what());
        }
        std::ofstream fp(filename.c_str(),
                         std::ofstream::out | std::ofstream::trunc);
        if (fp.is_open()) {
            fp.write(pem.c_str(), pem.size());
            fp.close();
        } else {
            isc_throw(BadKey, "Can't open file: " << filename);
        }
    } else if ((key_kind == PRIVATE) && (key_format == DNS)) {
        //  bind9 .private file
        if (kind_ != PRIVATE) {
            isc_throw(UnsupportedAlgorithm, "Have no ECDSA Private Key");
        }
        std::ofstream fp(filename.c_str(),
                         std::ofstream::out | std::ofstream::trunc);
        if (!fp.is_open()) {
            isc_throw(BadKey, "Can't open file: " << filename);
        }
        fp << "Private-key-format: v1.2\n";
        if (hash_ == SHA256) {
            fp << "Algorithm: 13 (ECDSAP256SHA256)\n";
        } else if (hash_ == SHA384) {
            fp << "Algorithm: 14 (ECDSAP384SHA384)\n";
        }
        std::vector<uint8_t> bin;
        Botan::BigInt privkey = priv_->private_value();
        bin.resize(privkey.bytes());
        privkey.binary_encode(&bin[0]);
        fp << "PrivateKey: " << util::encode::encodeBase64(bin) << '\n';
        fp.close();
    } else if (key_kind == PRIVATE) {
        if (kind_ != PRIVATE) {
            isc_throw(UnsupportedAlgorithm, "Have no ECDSA Private Key");
        }
        isc_throw(UnsupportedAlgorithm,
                  "Unknown ECDSA Private Key format: " <<
                  static_cast<int>(key_format));
    } else if ((key_kind == PUBLIC) && (key_format == ASN1)) {
        // SubjectPublicKeyInfo PEM file
        // warn when password not empty
        // Expand encoding to force namedCurve
        std::string pem;
        try {
            // pem = Botan::X509::PEM_encode(*pub_);
            Botan::MemoryVector<Botan::byte> ber;
            // ber = Botan::X509::BER_encode(*pub_);
            const Botan::MemoryVector<Botan::byte> parameters =
                pub_->domain().DER_encode(Botan::EC_DOMPAR_ENC_OID);
            const Botan::AlgorithmIdentifier alg_id(pub_->get_oid(),
                                                    parameters);
            const Botan::MemoryVector<Botan::byte> pubkey =
                Botan::EC2OSP(pub_->public_point(),
                              Botan::PointGFp::UNCOMPRESSED);
            ber = Botan::DER_Encoder()
                     .start_cons(Botan::SEQUENCE)
                        .encode(alg_id)
                        .encode(pubkey, Botan::BIT_STRING)
                    .end_cons()
                .get_contents();
            pem = Botan::PEM_Code::encode(ber, "PUBLIC KEY");
        } catch (const std::exception& exc) {
            isc_throw(LibraryError, "X509::PEM_encode: " << exc.what());
        }
        std::ofstream fp(filename.c_str(),
                         std::ofstream::out | std::ofstream::trunc);
        if (fp.is_open()) {
            fp.write(pem.c_str(), pem.size());
            fp.close();
        } else {
            isc_throw(BadKey, "Can't open file: " << filename);
        }
    }  else if ((key_kind == PUBLIC) && (key_format == DNS)) {
        // bind9 .key file (RDATA)
        // warn when password not empty
        std::vector<uint8_t> bin = exportkey(key_kind, key_format);
        std::ofstream fp(filename.c_str(),
                         std::ofstream::out | std::ofstream::trunc);
        if (!fp.is_open()) {
            isc_throw(BadKey, "Can't open file: " << filename);
        }
        fp << "; DNSKEY RDATA: " << util::encode::encodeBase64(bin) << '\n';
        fp.close();
    } else if (key_kind == PUBLIC) {
        isc_throw(UnsupportedAlgorithm,
                  "Unknown ECDSA Public Key format: " <<
                  static_cast<int>(key_format));
    } else if ((key_kind == CERT) && (key_format == ASN1)) {
        // Public Key Certificate PEM file
        // warn when password not empty
        if (!x509_) {
            isc_throw(UnsupportedAlgorithm, "Have no Certificate");
        }
        std::string pem;
        try {
            pem = x509_->PEM_encode();
        } catch (const std::exception& exc) {
            isc_throw(LibraryError, "PEM_encode: " << exc.what());
        }
        std::ofstream fp(filename.c_str(),
                         std::ofstream::out | std::ofstream::trunc);
        if (fp.is_open()) {
            fp.write(pem.c_str(), pem.size());
            fp.close();
        } else {
            isc_throw(BadKey, "Can't open file: " << filename);
        }
    } else if (key_kind == CERT) {
        if (!x509_) {
            isc_throw(UnsupportedAlgorithm, "Have no Certificate");
        }
        isc_throw(UnsupportedAlgorithm,
                  "Unknown Certificate format: " <<
                  static_cast<int>(key_format));
    } else {
        isc_throw(UnsupportedAlgorithm,
                  "Unknown ECDSA Key kind: " << static_cast<int>(key_kind));
    }
}

/// @brief Check the validity
bool EcDsaAsymImpl::validate() const {
    Botan::AutoSeeded_RNG rng;
    Botan::X509_Store store;
    Botan::X509_Code status;
    switch (kind_) {
    case PUBLIC:
        try {
            return pub_->check_key(rng, false);
        } catch (const std::exception& exc) {
            isc_throw(LibraryError, "check_key: " << exc.what());
        }
    case PRIVATE:
        try {
            return priv_->check_key(rng, false);
        } catch (const std::exception& exc) {
            isc_throw(LibraryError, "check_key: " << exc.what());
        }
    case CERT:
        store.add_cert(*x509_, true);
        status = store.validate_cert(*x509_);
        if (status == Botan::VERIFIED) {
            return true;
        }
        return false;
    default:
        return false;
    }
}

/// @brief Compare two keys
bool EcDsaAsymImpl::compare(const EcDsaAsymImpl* other,
                          const AsymKeyKind key_kind) const {
    if (!other || (other->algo_ != ECDSA_)) {
        return false;
    }
    Botan::PointGFp pubkey;
    switch (key_kind) {
    case CERT:
        // Special case for cert - cert
        if ((kind_ == CERT) && (other->kind_ == CERT)) {
            return (*x509_ == *other->x509_);
        }
        // At least one should be a cert
        if ((kind_ != CERT) && (other->kind_ != CERT)) {
            return false;
        }
        goto cmppub;
    case PRIVATE:
        if ((kind_ != PRIVATE) || (other->kind_ != PRIVATE)) {
            return false;
        }
        // If public keys match so private too
        goto cmppub;
    case PUBLIC:
        // Compare curves and public keys
        if ((kind_ != PUBLIC) &&
            (kind_ != PRIVATE) &&
            (kind_ != CERT)) {
            return false;
        }
        if ((other->kind_ != PUBLIC) &&
            (other->kind_ != PRIVATE) &&
            (other->kind_ != CERT)) {
            return false;
        }
    cmppub:
        if (group_ != other->group_) {
            return false;
        }
        if (kind_ == PRIVATE) {
            pubkey = priv_->public_point();
        } else if ((kind_ == PUBLIC) || (kind_ == CERT)) {
            pubkey = pub_->public_point();
        } else {
            return false;
        }
        if (other->kind_ == PRIVATE) {
            return (pubkey == other->priv_->public_point());
        } else if ((other->kind_ == PUBLIC) || (other->kind_ == CERT)) {
            return (pubkey == other->pub_->public_point());
        } else {
            return false;
        }
    default:
        return false;
    }
}

} // namespace cryptolink
} // namespace isc
