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

#include <openssl/pem.h>
#include <openssl/objects.h>
#include <openssl/ec.h>
#include <openssl/ecdsa.h>
#include <openssl/x509.h>

#include <util/encode/base64.h>
#include <cryptolink/openssl_common.h>
#include <cryptolink/openssl_ecdsa.h>

#include <cstdio>
#include <cstring>

#ifndef NID_X9_62_prime256v1
#error "P-256 group is not known (NID_X9_62_prime256v1)"
#endif
#ifndef NID_secp384r1
#error "P-384 group is not known (NID_secp384r1)"
#endif

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
    eckey_ = NULL;
    x509_ = NULL;
    int curve_nid = 0;
    switch (hash_) {
    case SHA256:
        curve_nid = NID_X9_62_prime256v1;
        break;
    case SHA384:
        curve_nid = NID_secp384r1;
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
        const unsigned char* p = reinterpret_cast<const unsigned char*>(key);
        BIGNUM* privkey = BN_bin2bn(p, static_cast<int>(key_len), NULL);
        if (!privkey) {
            throw std::bad_alloc();
        }
        eckey_ = EC_KEY_new_by_curve_name(curve_nid);
        if (!eckey_) {
            BN_clear_free(privkey);
            isc_throw(LibraryError, "EC_KEY_new_by_curve_name");
        }
        EC_KEY_set_asn1_flag(eckey_, OPENSSL_EC_NAMED_CURVE);
        if (!EC_KEY_set_private_key(eckey_, privkey)) {
            BN_clear_free(privkey);
            EC_KEY_free(eckey_);
            eckey_ = NULL;
            isc_throw(LibraryError, "EC_KEY_set_private_key");
        }
        // Compute the public key
        const EC_GROUP* grp = EC_KEY_get0_group(eckey_);
        EC_POINT* pubkey = EC_POINT_new(grp);
        if (!pubkey) {
            BN_clear_free(privkey);
            throw std::bad_alloc();
        }
        if (!EC_POINT_mul(grp, pubkey, privkey, NULL, NULL, NULL)) {
            EC_POINT_free(pubkey);
            BN_clear_free(privkey);
            EC_KEY_free(eckey_);
            eckey_ = NULL;
            isc_throw(LibraryError, "EC_POINT_mul");
        }
        if (!EC_KEY_set_public_key(eckey_, pubkey)) {
            EC_POINT_free(pubkey);
            BN_clear_free(privkey);
            EC_KEY_free(eckey_);
            eckey_ = NULL;
            isc_throw(BadKey, "EC_KEY_set_public_key");
        }
        EC_POINT_free(pubkey);
        BN_clear_free(privkey);
    } else if (kind_ == PRIVATE) {
        isc_throw(UnsupportedAlgorithm,
                  "Unknown ECDSA Private Key format: " <<
                  static_cast<int>(key_format));
    } else if ((kind_ == PUBLIC) && (key_format == ASN1)) {
        // SubjectPublicKeyInfo
        const unsigned char* p = reinterpret_cast<const unsigned char*>(key);
        eckey_ = d2i_EC_PUBKEY(NULL, &p, static_cast<long>(key_len));
        if (!eckey_) {
            isc_throw(BadKey, "d2i_EC_PUBKEY");
        }
        if (EC_KEY_check_key(eckey_) != 1) {
            EC_KEY_free(eckey_);
            eckey_ = NULL;
            isc_throw(BadKey, "EC_KEY_check_key");
        }
        EC_GROUP* wanted = EC_GROUP_new_by_curve_name(curve_nid);
        if (!wanted) {
            EC_KEY_free(eckey_);
            eckey_ = NULL;
            isc_throw(LibraryError, "EC_GROUP_new_by_curve_name");
        }
        const int status =
            EC_GROUP_cmp(EC_KEY_get0_group(eckey_), wanted, NULL);
        EC_GROUP_free(wanted);
        if (status < 0) {
            EC_KEY_free(eckey_);
            eckey_ = NULL;
            isc_throw(LibraryError, "EC_GROUP_cmp");
        } else if (status != 0) {
            EC_KEY_free(eckey_);
            eckey_ = NULL;
            isc_throw(BadKey, "EC_GROUP_cmp");
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
        std::vector<uint8_t> pubbin(len + 1);
        pubbin[0] = POINT_CONVERSION_UNCOMPRESSED;
        std::memcpy(&pubbin[1], key, len);
        const uint8_t* p = &pubbin[0];
        eckey_ = EC_KEY_new_by_curve_name(curve_nid);
        if (!eckey_) {
            isc_throw(LibraryError, "EC_KEY_new_by_curve_name");
        }
        EC_KEY_set_asn1_flag(eckey_, OPENSSL_EC_NAMED_CURVE);
        if (o2i_ECPublicKey(&eckey_, &p,
                            static_cast<long>(len + 1)) == NULL) {
            EC_KEY_free(eckey_);
            eckey_ = NULL;
            isc_throw(BadKey, "o2i_ECPublicKey");
        }
        if (!EC_KEY_check_key(eckey_)) {
            EC_KEY_free(eckey_);
            eckey_ = NULL;
            isc_throw(BadKey, "EC_KEY_check_key");
        }
    } else if (kind_ == PUBLIC) {
        isc_throw(UnsupportedAlgorithm,
                  "Unknown ECDSA Public Key format: " <<
                  static_cast<int>(key_format));
    } else if ((kind_ == CERT) && (key_format == ASN1)) {
        // X.509 Public Key Certificate
        const unsigned char* p = reinterpret_cast<const unsigned char*>(key);
        x509_ = d2i_X509(NULL, &p, static_cast<long>(key_len));
        if (!x509_) {
            isc_throw(BadKey, "d2i_X509");
        }
        int sig_nid = OBJ_obj2nid(x509_->sig_alg->algorithm);
        if (hash_ == SHA256) {
            if (sig_nid != OBJ_txt2nid("1.2.840.10045.4.3.2")) {
                X509_free(x509_);
                x509_ = NULL;
                isc_throw(BadKey, "Require an ECDSA P256 certificate");
            }
        } else {
            if (sig_nid != OBJ_txt2nid("1.2.840.10045.4.3.3")) {
                X509_free(x509_);
                x509_ = NULL;
                isc_throw(BadKey, "Require an ECDSA P256 certificate");
            }
        }
        EVP_PKEY* pkey = X509_get_pubkey(x509_);
        if (!pkey) {
                X509_free(x509_);
                x509_ = NULL;
                isc_throw(BadKey, "X509_get_pubkey");
        }
        eckey_ = EVP_PKEY_get1_EC_KEY(pkey);
        EVP_PKEY_free(pkey);
        if (!eckey_) {
                X509_free(x509_);
                x509_ = NULL;
                isc_throw(BadKey, "EVP_PKEY_get1_EC_KEY");
        }
    } else if (kind_ == CERT) {
        isc_throw(UnsupportedAlgorithm,
                  "Unknown Certificate format: " <<
                  static_cast<int>(key_format));
    } else {
        isc_throw(UnsupportedAlgorithm,
                  "Unknown ECDSA Key kind: " << static_cast<int>(kind_));
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
    eckey_ = NULL;
    x509_ = NULL;
    int curve_nid = 0;
    switch (hash_) {
    case SHA256:
        curve_nid = NID_X9_62_prime256v1;
        break;
    case SHA384:
        curve_nid = NID_secp384r1;
        break;
    default:
        isc_throw(UnsupportedAlgorithm,
                  "Unknown hash algorithm: " << static_cast<int>(hash_));
    }

    if ((kind_ == PRIVATE) && (key_format == ASN1)) {
        // PKCS#8 Private Key PEM file
        FILE* fp = fopen(filename.c_str(), "r");
        if (!fp) {
            isc_throw(BadKey, "Can't open file: " << filename);
        }
        char* pwd = NULL;
        if (!password.empty()) {
            pwd = const_cast<char*>(password.c_str());
        }
        eckey_ = PEM_read_ECPrivateKey(fp, NULL, 0, pwd);
        fclose(fp);
        if (!eckey_) {
            isc_throw(BadKey, "PEM_read_ECPrivateKey");
        }
        if (!EC_KEY_get0_public_key(eckey_)) {
            // Compute the public key as a side effect
            const EC_GROUP* grp = EC_KEY_get0_group(eckey_);
            const BIGNUM* privkey = EC_KEY_get0_private_key(eckey_);
            EC_POINT* pubkey = EC_POINT_new(grp);
            if (!pubkey) {
                throw std::bad_alloc();
            }
            if (!EC_POINT_mul(grp, pubkey, privkey, NULL, NULL, NULL)) {
                EC_POINT_free(pubkey);
                EC_KEY_free(eckey_);
                eckey_ = NULL;
                isc_throw(LibraryError, "EC_POINT_mul");
            }
            if (!EC_KEY_set_public_key(eckey_, pubkey)) {
                EC_POINT_free(pubkey);
                EC_KEY_free(eckey_);
                eckey_ = NULL;
                isc_throw(BadKey, "EC_KEY_set_public_key");
            }
            EC_POINT_free(pubkey);
        }
        if (EC_KEY_check_key(eckey_) != 1) {
            EC_KEY_free(eckey_);
            eckey_ = NULL;
            isc_throw(BadKey, "EC_KEY_check_key");
        }
        EC_GROUP* wanted = EC_GROUP_new_by_curve_name(curve_nid);
        if (!wanted) {
            EC_KEY_free(eckey_);
            eckey_ = NULL;
            isc_throw(LibraryError, "EC_GROUP_new_by_curve_name");
        }
        const int status =
            EC_GROUP_cmp(EC_KEY_get0_group(eckey_), wanted, NULL);
        EC_GROUP_free(wanted);
        if (status < 0) {
            EC_KEY_free(eckey_);
            eckey_ = NULL;
            isc_throw(LibraryError, "EC_GROUP_cmp");
        } else if (status != 0) {
            EC_KEY_free(eckey_);
            eckey_ = NULL;
            isc_throw(BadKey, "EC_GROUP_cmp");
        }
    } else if ((kind_ == PRIVATE) && (key_format == DNS)) {
        // bind9 .private file
        // warn when password not empty
        FILE* fp = fopen(filename.c_str(), "r");
        if (!fp) {
            isc_throw(BadKey, "Can't open file: " << filename);
        }
        bool got_algorithm = false;
        bool got_privatekey = false;
        BIGNUM* privkey = NULL;
        char line[4096];
        while (fgets(line, sizeof(line), fp)) {
            if (strncmp(line, "Algorithm:", strlen("Algorithm:")) == 0) {
                if (got_algorithm) {
                    fclose(fp);
                    isc_throw(BadKey, "Two Algorithm entries");
                }
                got_algorithm = true;
                std::string value(line + strlen("Algorithm:") + 1);
                int alg = std::atoi(value.c_str());
                if (alg == 13) {
                    // ECDSAP256SHA256
                    if (hash_ != SHA256) {
                        fclose(fp);
                        isc_throw(BadKey, "Require an ECDSA P256 key");
                    }
                } else if (alg == 14) {
                    // ECDSAP384SHA384
                    if (hash_ != SHA384) {
                        fclose(fp);
                        isc_throw(BadKey, "Require an ECDSA SHA384 key");
                    }
                } else {
                    fclose(fp);
                    isc_throw(BadKey, "Bad Algorithm: " << alg);
                }
            } else if (strncmp(line, "PrivateKey:",
                               strlen("PrivateKey:")) == 0) {
                if (got_privatekey) {
                    fclose(fp);
                    isc_throw(BadKey, "Two PrivateKey entries");
                }
                got_privatekey = true;
                std::string value(line + strlen("PrivateKey:") + 1);
                std::vector<uint8_t> bin;
                try {
                    isc::util::encode::decodeBase64(value, bin);
                } catch (const BadValue& exc) {
                    fclose(fp);
                    isc_throw(BadKey, "PrivateKey: " << exc.what());
                }
                int len = static_cast<int>(bin.size());
                privkey = BN_bin2bn(&bin[0], len, NULL);
            }
        }
        fclose(fp);
        // Check first the existence of the PrivateKey
        if (!got_privatekey) {
            isc_throw(BadKey, "Missing PrivateExponent entry");
        }
        if (!got_algorithm) {
            BN_clear_free(privkey);
            isc_throw(BadKey, "Missing Algorithm entry");
        }
        eckey_ = EC_KEY_new_by_curve_name(curve_nid);
        if (!eckey_) {
            BN_clear_free(privkey);
            isc_throw(LibraryError, "EC_KEY_new_by_curve_name");
        }
        EC_KEY_set_asn1_flag(eckey_, OPENSSL_EC_NAMED_CURVE);
        if (!EC_KEY_set_private_key(eckey_, privkey)) {
            BN_clear_free(privkey);
            EC_KEY_free(eckey_);
            eckey_ = NULL;
            isc_throw(LibraryError, "EC_KEY_set_private_key");
        }
        BN_clear_free(privkey);
        // Compute the public key as a side effect
        if (!EC_KEY_generate_key(eckey_)) {
            EC_KEY_free(eckey_);
            eckey_ = NULL;
            isc_throw(BadKey, "EC_KEY_generate_key");
        }
    } else if ((kind_ == PUBLIC) && (key_format == ASN1)) {
        // SubjectPublicKeyInfo PEM file
        // warn when password not empty
        FILE* fp = fopen(filename.c_str(), "r");
        if (!fp) {
            isc_throw(BadKey, "Can't open file: " << filename);
        }
        char* pwd = NULL;
        if (!password.empty()) {
            pwd = const_cast<char*>(password.c_str());
        }
        eckey_ = PEM_read_EC_PUBKEY(fp, NULL, 0, pwd);
        fclose(fp);
        if (!eckey_) {
            isc_throw(BadKey, "PEM_read_EC_PUBKEY");
        }
        if (EC_KEY_check_key(eckey_) != 1) {
            EC_KEY_free(eckey_);
            eckey_ = NULL;
            isc_throw(BadKey, "EC_KEY_check_key");
        }
        EC_GROUP* wanted = EC_GROUP_new_by_curve_name(curve_nid);
        if (!wanted) {
            EC_KEY_free(eckey_);
            eckey_ = NULL;
            isc_throw(LibraryError, "EC_GROUP_new_by_curve_name");
        }
        const int status =
            EC_GROUP_cmp(EC_KEY_get0_group(eckey_), wanted, NULL);
        EC_GROUP_free(wanted);
        if (status < 0) {
            EC_KEY_free(eckey_);
            eckey_ = NULL;
            isc_throw(LibraryError, "EC_GROUP_cmp");
        } else if (status != 0) {
            EC_KEY_free(eckey_);
            eckey_ = NULL;
            isc_throw(BadKey, "EC_GROUP_cmp");
        }
    } else if ((kind_ == PUBLIC) && (key_format == DNS)) {
        // bind9 .key file (RDATA)
        // warn when password not empty
        FILE* fp = fopen(filename.c_str(), "r");
        if (!fp) {
            isc_throw(BadKey, "Can't open file: " << filename);
        }
        char line[4096];
        bool found = false;
        while (fgets(line, sizeof(line), fp)) {
            if ((line[0] == '\0') || (line[0] == ';')) {
                continue;
            }
            if (strstr(line, "DNSKEY") == NULL) {
                continue;
            }
            found = true;
            if (line[strlen(line) - 1] == '\n') {
                line[strlen(line) - 1] = 0;
            }
            break;
        }
        fclose(fp);
        if (!found) {
            isc_throw(BadKey, "Can't find a DNSKEY");
        }
        const char b64[] =
            "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdef"
            "ghijklmnopqrstuvwxyz0123456789+/=";
        size_t last = strlen(line) - 1;
        while (strchr(b64, static_cast<int>(line[last])) != NULL) {
            --last;
        }
        const std::string value(line + last + 1);
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
        bin.insert(bin.begin(), POINT_CONVERSION_UNCOMPRESSED);
        const uint8_t* p = &bin[0];
        eckey_ = EC_KEY_new_by_curve_name(curve_nid);
        if (!eckey_) {
            isc_throw(LibraryError, "EC_KEY_new_by_curve_name");
        }
        EC_KEY_set_asn1_flag(eckey_, OPENSSL_EC_NAMED_CURVE);
        if (o2i_ECPublicKey(&eckey_, &p,
                            static_cast<long>(len + 1)) == NULL) {
            EC_KEY_free(eckey_);
            eckey_ = NULL;
            isc_throw(BadKey, "o2i_ECPublicKey");
        }
        if (!EC_KEY_check_key(eckey_)) {
            EC_KEY_free(eckey_);
            eckey_ = NULL;
            isc_throw(BadKey, "EC_KEY_check_key");
        }
    } else if (kind_ == PUBLIC) {
        isc_throw(UnsupportedAlgorithm,
                  "Unknown ECDSA Public Key format: " <<
                  static_cast<int>(key_format));
    } else if ((kind_ == CERT) && (key_format == ASN1)) {
        // Public Key Certificate PEM file
        // warn when password not empty
        FILE* fp = fopen(filename.c_str(), "r");
        if (!fp) {
            isc_throw(BadKey, "Can't open file: " << filename);
        }
        x509_ = PEM_read_X509(fp, NULL, 0, NULL);
        fclose(fp);
        if (!x509_) {
            isc_throw(BadKey, "PEM_read_X509");
        }
        int sig_nid = OBJ_obj2nid(x509_->sig_alg->algorithm);
        if (hash_ == SHA256) {
            if (sig_nid != OBJ_txt2nid("1.2.840.10045.4.3.2")) {
                X509_free(x509_);
                x509_ = NULL;
                isc_throw(BadKey, "Require an ECDSA P256 certificate");
            }
        } else {
            if (sig_nid != OBJ_txt2nid("1.2.840.10045.4.3.3")) {
                X509_free(x509_);
                x509_ = NULL;
                isc_throw(BadKey, "Require an ECDSA P256 certificate");
            }
        }
        EVP_PKEY* pkey = X509_get_pubkey(x509_);
        if (!pkey) {
                X509_free(x509_);
                x509_ = NULL;
                isc_throw(BadKey, "X509_get_pubkey");
        }
        eckey_ = EVP_PKEY_get1_EC_KEY(pkey);
        EVP_PKEY_free(pkey);
        if (!eckey_) {
                X509_free(x509_);
                x509_ = NULL;
                isc_throw(BadKey, "EVP_PKEY_get1_EC_KEY");
        }
    } else if (kind_ == CERT) {
        isc_throw(UnsupportedAlgorithm,
                  "Unknown Public Key Certificate format: " <<
                  static_cast<int>(key_format));
    } else {
        isc_throw(UnsupportedAlgorithm,
                  "Unknown ECDSA Key kind: " << static_cast<int>(kind_));
    }
}

/// @brief Destructor
EcDsaAsymImpl::~EcDsaAsymImpl() {
    tbs_.clear();
    if (eckey_) {
        EC_KEY_free(eckey_);
        eckey_ = NULL;
    }
    if (x509_) {
        X509_free(x509_);
        x509_ = NULL;
    }
}

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
    const size_t old = tbs_.size();
    tbs_.resize(old + len);
    std::memcpy(&tbs_[old], data, len);
}

/// @brief Calculate the final signature
void EcDsaAsymImpl::sign(isc::util::OutputBuffer& result, size_t len,
                         const AsymFormat sig_format) {
    if ((sig_format != BASIC) &&
        (sig_format != ASN1) &&
        (sig_format != DNS)) {
        isc_throw(UnsupportedAlgorithm,
                  "Unknown Signature format: " <<
                  static_cast<int>(sig_format));
    }
    size_t size = getSignatureLength(sig_format);
    ossl::SecBuf<uint8_t> buf(size);
    ECDSA_SIG* sig = ECDSA_do_sign(&tbs_[0],
                                   static_cast<int>(tbs_.size()),
                                   eckey_);
    if (!sig) {
        isc_throw(LibraryError, "ECDSA_do_sign");
    }
    if ((sig_format == BASIC) || (sig_format == DNS)) {
        // Store the 2 integers with padding
        BN_bn2bin(sig->r, &buf[(size / 2) - BN_num_bytes(sig->r)]);
        BN_bn2bin(sig->s, &buf[size - BN_num_bytes(sig->s)]);
        ECDSA_SIG_free(sig);
        if (len > size) {
            len = size;
        }
    } else {
        // Store the ECDSA_SIG structure in DER
        int sig_len = i2d_ECDSA_SIG(sig, NULL);
        if (sig_len < 0) {
            ECDSA_SIG_free(sig);
            isc_throw(LibraryError, "i2d_ECDSA_SIG 0");
        }
        buf.resize(sig_len);
        uint8_t* p = &buf[0];
        sig_len = i2d_ECDSA_SIG(sig, &p);
        ECDSA_SIG_free(sig);
        if (sig_len != static_cast<int>(buf.size())) {
            isc_throw(LibraryError, "i2d_ECDSA_SIG");
        }
        size_t sig_size = static_cast<size_t>(sig_len);
        if (len > sig_size) {
            len = sig_size;
        }
    }
    result.writeData(&buf[0], len);
}

/// @brief Calculate the final signature
void EcDsaAsymImpl::sign(void* result, size_t len,
                         const AsymFormat sig_format) {
    if ((sig_format != BASIC) &&
        (sig_format != ASN1) &&
        (sig_format != DNS)) {
        isc_throw(UnsupportedAlgorithm,
                  "Unknown Signature format: " <<
                  static_cast<int>(sig_format));
    }
    size_t size = getSignatureLength(sig_format);
    ossl::SecBuf<uint8_t> buf(size);
    ECDSA_SIG* sig = ECDSA_do_sign(&tbs_[0],
                                   static_cast<int>(tbs_.size()),
                                   eckey_);
    if (!sig) {
        isc_throw(LibraryError, "ECDSA_do_sign");
    }
    if ((sig_format == BASIC) || (sig_format == DNS)) {
        // Store the 2 integers with padding
        BN_bn2bin(sig->r, &buf[(size / 2) - BN_num_bytes(sig->r)]);
        BN_bn2bin(sig->s, &buf[size - BN_num_bytes(sig->s)]);
        ECDSA_SIG_free(sig);
        if (len > size) {
            len = size;
        }
    } else {
        // Store the ECDSA_SIG structure in DER
        int sig_len = i2d_ECDSA_SIG(sig, NULL);
        if (sig_len < 0) {
            ECDSA_SIG_free(sig);
            isc_throw(LibraryError, "i2d_ECDSA_SIG 0");
        }
        buf.resize(sig_len);
        uint8_t* p = &buf[0];
        sig_len = i2d_ECDSA_SIG(sig, &p);
        ECDSA_SIG_free(sig);
        if (sig_len != static_cast<int>(buf.size())) {
            isc_throw(LibraryError, "i2d_ECDSA_SIG");
        }
        size_t sig_size = static_cast<size_t>(sig_len);
        if (len > sig_size) {
            len = sig_size;
        }
    }
    std::memcpy(result, &buf[0], len);
}

/// @brief Calculate the final signature
std::vector<uint8_t> EcDsaAsymImpl::sign(size_t len,
                                         const AsymFormat sig_format) {
    if ((sig_format != BASIC) &&
        (sig_format != ASN1) &&
        (sig_format != DNS)) {
        isc_throw(UnsupportedAlgorithm,
                  "Unknown Signature format: " <<
                  static_cast<int>(sig_format));
    }
    size_t size = getSignatureLength(sig_format);
    ossl::SecBuf<uint8_t> buf(size);
    ECDSA_SIG* sig = ECDSA_do_sign(&tbs_[0],
                                   static_cast<int>(tbs_.size()),
                                   eckey_);
    if (!sig) {
        isc_throw(LibraryError, "ECDSA_do_sign");
    }
    if ((sig_format == BASIC) || (sig_format == DNS)) {
        // Store the 2 integers with padding
        BN_bn2bin(sig->r, &buf[(size / 2) - BN_num_bytes(sig->r)]);
        BN_bn2bin(sig->s, &buf[size - BN_num_bytes(sig->s)]);
        ECDSA_SIG_free(sig);
        // resize to min(len, size)
        buf.resize(len < size ? len : size);
    } else {
        // Store the ECDSA_SIG structure in DER
        int sig_len = i2d_ECDSA_SIG(sig, NULL);
        if (sig_len < 0) {
            ECDSA_SIG_free(sig);
            isc_throw(LibraryError, "i2d_ECDSA_SIG 0");
        }
        buf.resize(sig_len);
        uint8_t* p = &buf[0];
        sig_len = i2d_ECDSA_SIG(sig, &p);
        ECDSA_SIG_free(sig);
        if (sig_len != static_cast<int>(buf.size())) {
            isc_throw(LibraryError, "i2d_ECDSA_SIG");
        }
        // resize to min(len, sig_len)
        size_t sig_size = static_cast<size_t>(sig_len);
        buf.resize(len < sig_size ? len : sig_size);
    }
    return (std::vector<uint8_t>(buf.begin(), buf.end()));
}  

/// @brief Verify an existing signature
bool EcDsaAsymImpl::verify(const void* sig, size_t len,
                           const AsymFormat sig_format) {
    if ((sig_format != BASIC) &&
        (sig_format != ASN1) &&
        (sig_format != DNS)) {
        isc_throw(UnsupportedAlgorithm,
                  "Unknown Signature format: " <<
                  static_cast<int>(sig_format));
    }
    ECDSA_SIG* asn_sig;
    const uint8_t* sigbuf =
        reinterpret_cast<const uint8_t*>(const_cast<void*>(sig));
    if ((sig_format == BASIC) || (sig_format == DNS)) {
        size_t size = getSignatureLength(sig_format);
        if (len != size) {
            return false;
        }
        asn_sig = ECDSA_SIG_new();
        if (!asn_sig) {
            throw std::bad_alloc();
        }
        if (asn_sig->r) {
            BN_clear_free(asn_sig->r);
        }
        asn_sig->r = BN_bin2bn(sigbuf, size / 2, NULL);
        if (!asn_sig->r) {
            ECDSA_SIG_free(asn_sig);
            throw std::bad_alloc();
        }
        if (asn_sig->s) {
            BN_clear_free(asn_sig->s);
        }
        asn_sig->s = BN_bin2bn(sigbuf + size / 2, size / 2, NULL);
        if (!asn_sig->s) {
            ECDSA_SIG_free(asn_sig);
            throw std::bad_alloc();
        }
    } else {
        asn_sig = d2i_ECDSA_SIG(NULL, &sigbuf, static_cast<long>(len));
        if (!asn_sig) {
            // Don't throw: just return false
            return false;
        }
    }
    int status = ECDSA_do_verify(&tbs_[0], static_cast<int>(tbs_.size()),
                                 asn_sig, eckey_);
    ECDSA_SIG_free(asn_sig);
    switch (status) {
    case 1:
        return true;
    case 0:
        return false;
    case -1:
    default:
        isc_throw(LibraryError, "ECDSA_do_verify");
    }
}

/// @brief Clear the crypto state and go back to the initial state
void EcDsaAsymImpl::clear() {
    tbs_.clear();
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
        const BIGNUM* privkey = EC_KEY_get0_private_key(eckey_);
        if (!privkey) {
            isc_throw(LibraryError, "EC_KEY_get0_private_key");
        }
        int len = BN_num_bytes(privkey);
        std::vector<uint8_t> bin(static_cast<size_t>(len));
        len = BN_bn2bin(privkey, &bin[0]);
        if (len != static_cast<int>(bin.size())) {
            isc_throw(LibraryError, "BN_bn2bin");
        }
        return bin;
    } else if (key_kind == PRIVATE) {
        isc_throw(UnsupportedAlgorithm,
                  "Unknown ECDSA Private Key format: " <<
                  static_cast<int>(key_format));
    } else if ((key_kind == PUBLIC) && (key_format == ASN1)) {
        // SubjectPublicKeyInfo
        int len = i2d_EC_PUBKEY(eckey_, NULL);
        if (len < 0) {
            isc_throw(LibraryError, "i2d_EC_PUBKEY 0");
        }
        std::vector<uint8_t> der(static_cast<size_t>(len));
        unsigned char* p = &der[0];
        len = i2d_EC_PUBKEY(eckey_, &p);
        if (len != static_cast<int>(der.size())) {
            isc_throw(LibraryError, "i2d_EC_PUBKEY");
        }
        return der;
    } else if ((key_kind == PUBLIC) && (key_format == DNS)) {
        // RFC 6605 DNS wire format
        int len = i2o_ECPublicKey(eckey_, NULL);
        if (len < 1) {
            isc_throw(LibraryError, "i2o_ECPublicKey 0");
        }
        std::vector<uint8_t> pubkey(static_cast<size_t>(len));
        uint8_t* p = &pubkey[0];
        len = i2o_ECPublicKey(eckey_, &p);
        if (len != static_cast<int>(pubkey.size())) {
            isc_throw(LibraryError, "i2o_ECPublicKey");
        }
        return std::vector<uint8_t>(pubkey.begin() + 1, pubkey.end());
    } else if (key_kind == PUBLIC) {
        isc_throw(UnsupportedAlgorithm,
                  "Unknown ECDSA Public Key format: " <<
                  static_cast<int>(key_format));
    } else if ((key_kind == CERT) && (key_format == ASN1)) {
        // X.509 Public Key Certificate
        if (kind_ != CERT) {
            isc_throw(UnsupportedAlgorithm, "Have no Certificate");
        }
        int len = i2d_X509(x509_, NULL);
        if (len < 0) {
            isc_throw(LibraryError, "i2d_X509 0");
        }
        std::vector<uint8_t> ber(static_cast<size_t>(len));
        unsigned char* p = &ber[0];
        len = i2d_X509(x509_, &p);
        if (len != static_cast<int>(ber.size())) {
            isc_throw(LibraryError, "i2d_X509");
        }
        return ber;
    } else if (key_kind == CERT) {
        isc_throw(UnsupportedAlgorithm,
                  "Unknown Certificate format: " <<
                  static_cast<int>(key_format));
    } else {
        isc_throw(UnsupportedAlgorithm,
                  "Unknown ECDSA Key kind: " <<
                  static_cast<int>(key_kind));
    }
}

/// @brief Export the key value (file)
void EcDsaAsymImpl::exportkey(const std::string& filename,
                            const std::string& password,
                            const AsymKeyKind key_kind,
                            const AsymFormat key_format) const {
    if ((key_kind == PRIVATE) && (key_format == ASN1)) {
        // PKCS#8 Private Key PEM file
        if (kind_ != PRIVATE) {
            isc_throw(UnsupportedAlgorithm, "Have no ECDSA Private Key");
        }
        char* pwd = NULL;
        const EVP_CIPHER* enc = NULL;
        if (!password.empty()) {
            pwd = const_cast<char*>(password.c_str());
            enc = EVP_des_ede3_cbc();
            if (!enc) {
                isc_throw(LibraryError, "EVP_des_ede3_cbc");
            }
        }
        FILE* fp = fopen(filename.c_str(), "w");
        if (!fp) {
            isc_throw(BadKey, "Can't open file: " << filename);
        }
        EVP_PKEY* pkey = EVP_PKEY_new();
        if (!pkey) {
            fclose(fp);
            throw std::bad_alloc();
        }
        if (!EVP_PKEY_set1_EC_KEY(pkey, eckey_)) {
            EVP_PKEY_free(pkey);
            fclose(fp);
            isc_throw(LibraryError, "EVP_PKEY_set1_EC_KEY");
        }
        if (!PEM_write_PKCS8PrivateKey(fp, pkey, enc, pwd,
                                       static_cast<int>(password.size()),
                                       0, NULL)) {
            EVP_PKEY_free(pkey);
            fclose(fp);
            isc_throw(LibraryError, "PEM_write_PKCS8PrivateKey");
        }
        EVP_PKEY_free(pkey);
        fclose(fp);
    } else if ((key_kind == PRIVATE) && (key_format == DNS)) {
        //  bind9 .private file
        if (kind_ != PRIVATE) {
            isc_throw(UnsupportedAlgorithm, "Have no ECDSA Private Key");
        }
        FILE* fp = fopen(filename.c_str(), "w");
        if (!fp) {
            isc_throw(BadKey, "Can't open file: " << filename);
        }
        const BIGNUM* privkey = EC_KEY_get0_private_key(eckey_);
        if (!privkey) {
            fclose(fp);
            isc_throw(LibraryError, "EC_KEY_get0_private_key");
        }
        fprintf(fp, "Private-key-format: v1.2\n");
        if (hash_ == SHA256) {
            fprintf(fp, "Algorithm: 13 (ECDSAP256SHA256)\n");
        } else if (hash_ == SHA256) {
            fprintf(fp, "Algorithm: 1 (ECDSAP384SHA384)\n");
        }
        std::vector<uint8_t> bin;
        bin.resize(BN_num_bytes(privkey));
        BN_bn2bin(privkey, &bin[0]);
        fprintf(fp, "PrivateKey: %s\n",
                util::encode::encodeBase64(bin).c_str());
        fclose(fp);
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
        FILE* fp = fopen(filename.c_str(), "w");
        if (!fp) {
            isc_throw(BadKey, "Can't open file: " << filename);
        }
        if (!PEM_write_EC_PUBKEY(fp, eckey_)) {
            fclose(fp);
            isc_throw(LibraryError, "PEM_write_EC_PUBKEY");
        }
        fclose(fp);
    }  else if ((key_kind == PUBLIC) && (key_format == DNS)) {
        // bind9 .key file (RDATA)
        // warn when password not empty
        std::vector<uint8_t> bin = exportkey(key_kind, key_format);
        FILE* fp = fopen(filename.c_str(), "w");
        if (!fp) {
            isc_throw(BadKey, "Can't open file: " << filename);
        }
        fprintf(fp, "; DNSKEY RDATA: %s\n",
                util::encode::encodeBase64(bin).c_str());
        fclose(fp);
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
        FILE* fp = fopen(filename.c_str(), "w");
        if (!fp) {
            isc_throw(BadKey, "Can't open file: " << filename);
        }
        if (!PEM_write_X509(fp, x509_)) {
            fclose(fp);
            isc_throw(LibraryError, "PEM_write_X509");
        }
        fclose(fp);
    } else if (key_kind == CERT) {
        if (!x509_) {
            isc_throw(UnsupportedAlgorithm, "Have no Certificate");
        }
        isc_throw(UnsupportedAlgorithm,
                  "Unknown Certificate format: " <<
                  static_cast<int>(key_format));
    } else {
        isc_throw(UnsupportedAlgorithm,
                  "Unknown ECDSA Key kind: " <<
                  static_cast<int>(key_kind));
    }
}

/// @brief Check the validity
bool EcDsaAsymImpl::validate() const {
    X509_STORE* store;
    X509_STORE_CTX* ctx;
    int status;
    switch (kind_) {
    case PUBLIC:
    case PRIVATE:
        return (EC_KEY_check_key(eckey_) == 1);
    case CERT:
        store = X509_STORE_new();
        if (!store) {
            return false;
        }
        if (!X509_STORE_add_cert(store, x509_)) {
            X509_STORE_free(store);
            store = NULL;
            return false;
        }
        ctx = X509_STORE_CTX_new();
        if (!ctx) {
            X509_STORE_free(store);
            store = NULL;
            return false;
        }
        if (!X509_STORE_CTX_init(ctx, store, x509_, NULL)) {
            X509_STORE_CTX_free(ctx);
            ctx = NULL;
            X509_STORE_free(store);
            store = NULL;
            return false;
        }
        // By default OpenSSL skips self-signatures
        X509_STORE_CTX_set_flags(ctx, X509_V_FLAG_CHECK_SS_SIGNATURE);
        status = X509_verify_cert(ctx);
        // text version of status available by
        // X509_verify_cert_error_string(X509_STORE_CTX_get_error(ctx))
        X509_STORE_CTX_free(ctx);
        ctx = NULL;
        X509_STORE_free(store);
        store = NULL;
        if (status == 1) {
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
    const EC_GROUP* grp = EC_KEY_get0_group(eckey_);
    const EC_GROUP* ogrp = EC_KEY_get0_group(other->eckey_);
    const EC_POINT* pub = EC_KEY_get0_public_key(eckey_);
    const EC_POINT* opub = EC_KEY_get0_public_key(other->eckey_);
    int status;
    switch (key_kind) {
    case CERT:
        // Special case for cert - cert
        if ((kind_ == CERT) && (other->kind_ == CERT)) {
            return (X509_cmp(x509_, other->x509_) == 0);
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
        status = EC_GROUP_cmp(grp, ogrp, NULL);
        switch (status) {
        case 0:
            // match but not finished
            break;
        case 1:
            // don't match
            return false;
        default:
            // errors
            return false;
        }
        status = EC_POINT_cmp(grp, pub, opub, NULL);
        switch (status) {
        case 0:
            // match
            return true;
        case 1:
            // don't match
            return false;
        default:
            // errors
            return false;
        }
    default:
        return false;
    }
}

} // namespace cryptolink
} // namespace isc
