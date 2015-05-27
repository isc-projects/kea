// Copyright (C) 2014, 2015  Internet Systems Consortium, Inc. ("ISC")
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

#include <openssl/evp.h>
#include <openssl/pem.h>
#include <openssl/rsa.h>
#include <openssl/x509.h>

#include <util/encode/base64.h>
#include <cryptolink/openssl_common.h>

#include <cstdio>
#include <cstring>

namespace isc {
namespace cryptolink {

/// @brief OpenSSL implementation of asymmetrical cryptography (Asym).
// Each method is the counterpart of the Asym corresponding method.
class AsymImpl {
public:
    /// @brief Constructor from a key, asym and hash algorithm,
    ///        key kind and key binary format
    ///
    /// See constructor of the @ref isc::cryptolink::Asym class for details.
    ///
    /// @param key            The key to sign/verify with
    /// @param len            The length of the key
    /// @param asym_algorithm The asymmetrical cryptography algorithm
    /// @param hash_algorithm The hash algorithm
    /// @param key_kind       The key kind
    /// @param key_format     The key binary format
    explicit AsymImpl(const void* key, size_t key_len,
                      const AsymAlgorithm asym_algorithm,
                      const HashAlgorithm hash_algorithm,
                      const AsymKeyKind key_kind,
                      const AsymFormat key_format) {
        algo_ = asym_algorithm;
        hash_ = hash_algorithm;
        kind_ = key_kind;
        pkey_ = NULL;
        x509_ = NULL;
        if (algo_ != RSA_) {
            isc_throw(UnsupportedAlgorithm,
                      "Unknown asym algorithm: " <<
                      static_cast<int>(algo_));
        }
        const EVP_MD* md = ossl::getHashAlgorithm(hash_);
        if (md == 0) {
            isc_throw(UnsupportedAlgorithm,
                      "Unknown hash algorithm: " <<
                      static_cast<int>(hash_));
        }
        if (key_len == 0) {
            isc_throw(BadKey, "Bad RSA " <<
                      (kind_ != CERT ? "key" : "cert") <<
                      " length: 0");
        }

        if ((kind_ == PRIVATE) && (key_format == BASIC)) {
            // PKCS#1 Private Key
            const unsigned char* p =
                reinterpret_cast<const unsigned char*>(key);
            RSA* rsa = d2i_RSAPrivateKey(NULL, &p,
                                         static_cast<long>(key_len));
            if (!rsa) {
                isc_throw(BadKey, "d2i_RSAPrivateKey");
            }
            pkey_ = EVP_PKEY_new();
            if (!pkey_) {
                RSA_free(rsa);
                throw std::bad_alloc();
            }
            if (!EVP_PKEY_set1_RSA(pkey_, rsa)) {
                RSA_free(rsa);
                EVP_PKEY_free(pkey_);
                pkey_ = NULL;
                isc_throw(LibraryError, "EVP_PKEY_set1_RSA");
            }
            // set1 bumped the reference counter
            RSA_free(rsa);
        } else if (kind_ == PRIVATE) {
            isc_throw(UnsupportedAlgorithm,
                      "Unknown RSA Private Key format: " <<
                      static_cast<int>(key_format));
        } else if ((kind_ == PUBLIC) && (key_format == BASIC)) {
            // PKCS#1 Public Key
            const unsigned char* p =
                reinterpret_cast<const unsigned char*>(key);
            RSA* rsa = d2i_RSAPublicKey(NULL, &p,
                                        static_cast<long>(key_len));
            if (!rsa) {
                isc_throw(BadKey, "d2i_RSAPublicKey");
            }
            pkey_ = EVP_PKEY_new();
            if (!pkey_) {
                RSA_free(rsa);
                throw std::bad_alloc();
            }
            if (!EVP_PKEY_set1_RSA(pkey_, rsa)) {
                RSA_free(rsa);
                EVP_PKEY_free(pkey_);
                pkey_ = NULL;
                isc_throw(LibraryError, "EVP_PKEY_set1_RSA");
            }
            // set1 bumped the reference counter
            RSA_free(rsa);
        } else if ((kind_ == PUBLIC) && (key_format == ASN1)) {
            // SubjectPublicKeyInfo
            const unsigned char* p =
              reinterpret_cast<const unsigned char*>(key);
            RSA* rsa = d2i_RSA_PUBKEY(NULL, &p, static_cast<long>(key_len));
            if (!rsa) {
                isc_throw(BadKey, "d2i_RSA_PUBKEY");
            }
            pkey_ = EVP_PKEY_new();
            if (!pkey_) {
                RSA_free(rsa);
                throw std::bad_alloc();
            }
            if (!EVP_PKEY_set1_RSA(pkey_, rsa)) {
                RSA_free(rsa);
                EVP_PKEY_free(pkey_);
                pkey_ = NULL;
                isc_throw(LibraryError, "EVP_PKEY_set1_RSA");
            }
            // set1 bumped the reference counter
            RSA_free(rsa);
        } else if ((kind_ == PUBLIC) && (key_format == DNS)) {
            // RFC 3110 DNS wire format
            // key_len == 0 was already checked
            const uint8_t* p =
                reinterpret_cast<const uint8_t*>(key);
            unsigned int e_bytes = *p++;
            --key_len;
            if (e_bytes == 0) {
                if (key_len < 2) {
                    isc_throw(BadKey,
                              "Bad RSA Public Key: short exponent length");
                }
                e_bytes = (*p++) << 8;
                e_bytes += *p++;
                key_len -= 2;
            }
            if (key_len < e_bytes) {
                isc_throw(BadKey, "Bad RSA Public Key: short exponent");
            }
            if ((key_len - e_bytes) < 64) {
                isc_throw(BadKey, "Bad RSA Public Key: too short: " <<
                          (key_len - e_bytes) * 8);
            }
            if ((key_len - e_bytes) > 512) {
                isc_throw(BadKey, "Bad RSA Public Key: too large: " <<
                          (key_len - e_bytes) * 8);
            }
            RSA* rsa = RSA_new();
            if (!rsa) {
                throw std::bad_alloc();
            }
            rsa->e = BN_bin2bn(p, e_bytes, NULL);
            p += e_bytes;
            key_len -= e_bytes;
            rsa->n = BN_bin2bn(p, key_len, NULL);
            if (!rsa->e || !rsa->n) {
                RSA_free(rsa);
                throw std::bad_alloc();
            }
            pkey_ = EVP_PKEY_new();
            if (!pkey_) {
                RSA_free(rsa);
                throw std::bad_alloc();
            }
            if (!EVP_PKEY_set1_RSA(pkey_, rsa)) {
                RSA_free(rsa);
                EVP_PKEY_free(pkey_);
                pkey_ = NULL;
                isc_throw(LibraryError, "EVP_PKEY_set1_RSA");
            }
            // set1 bumped the reference counter
            RSA_free(rsa);
        } else if (kind_ == PUBLIC) {
            isc_throw(UnsupportedAlgorithm,
                      "Unknown RSA Public Key format: " <<
                      static_cast<int>(key_format));
        } else if ((kind_ == CERT) && (key_format == ASN1)) {
            // X.509 Public Key Certificate
            const unsigned char* p =
                reinterpret_cast<const unsigned char*>(key);
            x509_ = d2i_X509(NULL, &p, static_cast<long>(key_len));
            if (!x509_) {
                isc_throw(BadKey, "d2i_X509");
            }
            int sig_nid = OBJ_obj2nid(x509_->sig_alg->algorithm);
            if (hash_ == MD5) {
                if (sig_nid != OBJ_txt2nid("1.2.840.113549.1.1.4")) {
                    X509_free(x509_);
                    x509_ = NULL;
                    isc_throw(BadKey, "Require a RSA MD5 certificate");
                }
            } else if (hash_ == SHA1) {
                if (sig_nid != OBJ_txt2nid("1.2.840.113549.1.1.5")) {
                    X509_free(x509_);
                    x509_ = NULL;
                    isc_throw(BadKey, "Require a RSA SHA1 certificate");
                }
            } else if (hash_ == SHA224) {
                if (sig_nid != OBJ_txt2nid("1.2.840.113549.1.1.14")) {
                    X509_free(x509_);
                    x509_ = NULL;
                    isc_throw(BadKey, "Require a RSA SHA224 certificate");
                }
            } else if (hash_ == SHA256) {
                if (sig_nid != OBJ_txt2nid("1.2.840.113549.1.1.11")) {
                    X509_free(x509_);
                    x509_ = NULL;
                    isc_throw(BadKey, "Require a RSA SHA256 certificate");
                }
            } else if (hash_ == SHA384) {
                if (sig_nid != OBJ_txt2nid("1.2.840.113549.1.1.12")) {
                    X509_free(x509_);
                    x509_ = NULL;
                    isc_throw(BadKey, "Require a RSA SHA384 certificate");
                }
            } else if (hash_ == SHA512) {
                if (sig_nid != OBJ_txt2nid("1.2.840.113549.1.1.13")) {
                    X509_free(x509_);
                    x509_ = NULL;
                    isc_throw(BadKey, "Require a RSA SHA512 certificate");
                }
            } else {
                X509_free(x509_);
                x509_ = NULL;
                isc_throw(UnsupportedAlgorithm,
                          "Bad hash algorithm for certificate: " <<
                          static_cast<int>(hash_));
            }
            pkey_ = X509_get_pubkey(x509_);
            if (!pkey_) {
                X509_free(x509_);
                x509_ = NULL;
                isc_throw(BadKey, "X509_get_pubkey");
            }
            if (pkey_->type != EVP_PKEY_RSA) {
                EVP_PKEY_free(pkey_);
                pkey_ = NULL;
                X509_free(x509_);
                x509_ = NULL;
                isc_throw(BadKey, "not a RSA Public Key");
            }
        } else if (kind_ == CERT) {
            isc_throw(UnsupportedAlgorithm,
                      "Unknown Certificate format: " <<
                      static_cast<int>(key_format));
        } else {
            isc_throw(UnsupportedAlgorithm,
                      "Unknown RSA Key kind: " <<
                      static_cast<int>(kind_));
        }

        mdctx_.reset(new EVP_MD_CTX);
        EVP_MD_CTX_init(mdctx_.get());

        if (!EVP_DigestInit_ex(mdctx_.get(), md, NULL)) {
            EVP_MD_CTX_cleanup(mdctx_.get());
            EVP_PKEY_free(pkey_);
            pkey_ =NULL;
            isc_throw(LibraryError, "EVP_DigestInit_ex");
        }
    }

    /// @brief Constructor from a key file with password,
    ///        asym and hash algorithm, key kind and key binary format
    ///
    /// See constructor of the @ref isc::cryptolink::Asym class for details.
    ///
    /// @param filename       The key file name/path
    /// @param password       The PKCS#8 password
    /// @param asym_algorithm The asymmetrical cryptography algorithm
    /// @param hash_algorithm The hash algorithm
    /// @param key_kind       The key kind
    /// @param key_format     The key binary format
    explicit AsymImpl(const std::string& filename,
                      const std::string& password,
                      const AsymAlgorithm asym_algorithm,
                      const HashAlgorithm hash_algorithm,
                      const AsymKeyKind key_kind,
                      const AsymFormat key_format) {
        algo_ = asym_algorithm;
        hash_ = hash_algorithm;
        kind_ = key_kind;
        pkey_ = NULL;
        x509_ = NULL;
        if (algo_ != RSA_) {
            isc_throw(UnsupportedAlgorithm,
                      "Unknown asym algorithm: " <<
                      static_cast<int>(algo_));
        }
        const EVP_MD* md = ossl::getHashAlgorithm(hash_);
        if (md == 0) {
            isc_throw(UnsupportedAlgorithm,
                      "Unknown hash algorithm: " <<
                      static_cast<int>(hash_));
        }

        if ((kind_ == PRIVATE) &&
            ((key_format == BASIC) || (key_format == ASN1))) {
            // PKCS#1 or PKCS#8 Private Key PEM file
            FILE* fp = fopen(filename.c_str(), "r");
            if (!fp) {
                isc_throw(BadKey, "Can't open file: " << filename);
            }
            char* pwd = NULL;
            if (!password.empty()) {
                pwd = const_cast<char*>(password.c_str());
            }
            pkey_ = PEM_read_PrivateKey(fp, NULL, 0, pwd);
            fclose(fp);
            if (!pkey_) {
                isc_throw(BadKey, "PEM_read_PrivateKey");
            }
            if (pkey_->type != EVP_PKEY_RSA) {
                EVP_PKEY_free(pkey_);
                pkey_ = NULL;
                isc_throw(BadKey, "not a RSA Private Key");
            }
        } else if ((kind_ == PRIVATE) && (key_format == DNS)) {
            // bind9 .private file
            // warn when password not empty
            if ((hash_ != MD5) && (hash_ != SHA1) &&
                (hash_ != SHA256) && (hash_ != SHA512)) {
                isc_throw(UnsupportedAlgorithm,
                          "Not compatible hash algorithm: " <<
                          static_cast<int>(hash_));
            }
            FILE* fp = fopen(filename.c_str(), "r");
            if (!fp) {
                isc_throw(BadKey, "Can't open file: " << filename);
            }
            bool got_algorithm = false;
            bool got_modulus = false;
            bool got_pub_exponent = false;
            bool got_priv_exponent = false;
            bool got_prime1 = false;
            bool got_prime2 = false;
            bool got_exponent1 = false;
            bool got_exponent2 = false;
            bool got_coefficient = false;
            RSA* rsa = RSA_new();
            char line[4096];
            while (fgets(line, sizeof(line), fp)) {
                if (strncmp(line, "Algorithm:", strlen("Algorithm:")) == 0) {
                    if (got_algorithm) {
                        RSA_free(rsa);
                        fclose(fp);
                        isc_throw(BadKey, "Two Algorithm entries");
                    }
                    got_algorithm = true;
                    std::string value(line + strlen("Algorithm:") + 1);
                    int alg = std::atoi(value.c_str());
                    if (alg == 1) {
                        // RSAMD5
                        if (hash_ != MD5) {
                            RSA_free(rsa);
                            fclose(fp);
                            isc_throw(BadKey, "Require a RSA MD5 key");
                        }
                    } else if ((alg == 5) || (alg == 7)) {
                        // RSASHA1 or RSASHA1-NSEC3-SHA1
                        if (hash_ != SHA1) {
                            RSA_free(rsa);
                            fclose(fp);
                            isc_throw(BadKey, "Require a RSA SHA1 key");
                        }
                    } else if (alg == 8) {
                        // RSASHA256
                        if (hash_ != SHA256) {
                            RSA_free(rsa);
                            fclose(fp);
                            isc_throw(BadKey, "Require a RSA SHA256 key");
                        }
                    } else if (alg == 10) {
                        // RSASHA512
                        if (hash_ != SHA512) {
                            RSA_free(rsa);
                            fclose(fp);
                            isc_throw(BadKey, "Require a RSA SHA512 key");
                        }
                    } else {
                        RSA_free(rsa);
                        fclose(fp);
                        isc_throw(BadKey, "Bad Algorithm: " << alg);
                    }
                } else if (strncmp(line, "Modulus:",
                                   strlen("Modulus:")) == 0) {
                    if (got_modulus) {
                        RSA_free(rsa);
                        fclose(fp);
                        isc_throw(BadKey, "Two Modulus entries");
                    }
                    got_modulus = true;
                    std::string value(line + strlen("Modulus:") + 1);
                    std::vector<uint8_t> bin;
                    try {
                        isc::util::encode::decodeBase64(value, bin);
                    } catch (const BadValue& exc) {
                        RSA_free(rsa);
                        fclose(fp);
                        isc_throw(BadKey, "Modulus: " << exc.what());
                    }
                    int len = static_cast<int>(bin.size());
                    rsa->n = BN_bin2bn(&bin[0], len, NULL);
              } else if (strncmp(line, "PublicExponent:",
                                 strlen("PublicExponent:")) == 0) {
                    if (got_pub_exponent) {
                        RSA_free(rsa);
                        fclose(fp);
                        isc_throw(BadKey, "Two PublicExponent entries");
                    }
                    got_pub_exponent = true;
                    std::string value(line + strlen("PublicExponent:") + 1);
                    std::vector<uint8_t> bin;
                    try {
                        isc::util::encode::decodeBase64(value, bin);
                    } catch (const BadValue& exc) {
                        RSA_free(rsa);
                        fclose(fp);
                        isc_throw(BadKey, "PublicExponent: " << exc.what());
                    }
                    int len = static_cast<int>(bin.size());
                    rsa->e = BN_bin2bn(&bin[0], len, NULL);
                } else if (strncmp(line, "PrivateExponent:",
                                   strlen("PrivateExponent:")) == 0) {
                    if (got_priv_exponent) {
                        RSA_free(rsa);
                        fclose(fp);
                        isc_throw(BadKey, "Two PrivateExponent entries");
                    }
                    got_priv_exponent = true;
                    std::string value(line + strlen("PrivateExponent:") + 1);
                    std::vector<uint8_t> bin;
                    try {
                        isc::util::encode::decodeBase64(value, bin);
                    } catch (const BadValue& exc) {
                        RSA_free(rsa);
                        fclose(fp);
                        isc_throw(BadKey, "PrivateExponent: " << exc.what());
                    }
                    int len = static_cast<int>(bin.size());
                    rsa->d = BN_bin2bn(&bin[0], len, NULL);
                } else if (strncmp(line, "Prime1:", strlen("Prime1:")) == 0) {
                    if (got_prime1) {
                        RSA_free(rsa);
                        fclose(fp);
                        isc_throw(BadKey, "Two Prime1 entries");
                    }
                    got_prime1 = true;
                    std::string value(line + strlen("Prime1:") + 1);
                    std::vector<uint8_t> bin;
                    try {
                        isc::util::encode::decodeBase64(value, bin);
                    } catch (const BadValue& exc) {
                        RSA_free(rsa);
                        fclose(fp);
                        isc_throw(BadKey, "Prime1: " << exc.what());
                    }
                    int len = static_cast<int>(bin.size());
                    rsa->p = BN_bin2bn(&bin[0], len, NULL);
                } else if (strncmp(line, "Prime2:", strlen("Prime2:")) == 0) {
                    if (got_prime2) {
                        RSA_free(rsa);
                        fclose(fp);
                        isc_throw(BadKey, "Two Prime2 entries");
                    }
                    got_prime2 = true;
                    std::string value(line + strlen("Prime2:") + 1);
                    std::vector<uint8_t> bin;
                    try {
                        isc::util::encode::decodeBase64(value, bin);
                    } catch (const BadValue& exc) {
                        RSA_free(rsa);
                        fclose(fp);
                        isc_throw(BadKey, "Prime2: " << exc.what());
                    }
                    int len = static_cast<int>(bin.size());
                    rsa->q = BN_bin2bn(&bin[0], len, NULL);
                } else if (strncmp(line, "Exponent1:",
                                   strlen("Exponent1:")) == 0) {
                    if (got_exponent1) {
                        RSA_free(rsa);
                        fclose(fp);
                        isc_throw(BadKey, "Two Exponent1 entries");
                    }
                    got_exponent1 = true;
                    std::string value(line + strlen("Exponent1:") + 1);
                    std::vector<uint8_t> bin;
                    try {
                        isc::util::encode::decodeBase64(value, bin);
                    } catch (const BadValue& exc) {
                        RSA_free(rsa);
                        fclose(fp);
                        isc_throw(BadKey, "Exponent1: " << exc.what());
                    }
                    int len = static_cast<int>(bin.size());
                    rsa->dmp1 = BN_bin2bn(&bin[0], len, NULL);
                } else if (strncmp(line, "Exponent2:",
                                   strlen("Exponent2:")) == 0) {
                    if (got_exponent2) {
                        RSA_free(rsa);
                        fclose(fp);
                        isc_throw(BadKey, "Two Exponent2 entries");
                    }
                    got_exponent2 = true;
                    std::string value(line + strlen("Exponent2:") + 1);
                    std::vector<uint8_t> bin;
                    try {
                        isc::util::encode::decodeBase64(value, bin);
                    } catch (const BadValue& exc) {
                        RSA_free(rsa);
                        fclose(fp);
                        isc_throw(BadKey, "Exponent2: " << exc.what());
                    }
                    int len = static_cast<int>(bin.size());
                    rsa->dmq1 = BN_bin2bn(&bin[0], len, NULL);
                } else if (strncmp(line, "Coefficient:",
                                   strlen("Coefficient:")) == 0) {
                    if (got_coefficient) {
                        RSA_free(rsa);
                        fclose(fp);
                        isc_throw(BadKey, "Two Coefficient entries");
                    }
                    got_coefficient = true;
                    std::string value(line + strlen("Coefficient:") + 1);
                    std::vector<uint8_t> bin;
                    try {
                        isc::util::encode::decodeBase64(value, bin);
                    } catch (const BadValue& exc) {
                        RSA_free(rsa);
                        fclose(fp);
                        isc_throw(BadKey, "Coefficient: " << exc.what());
                    }
                    int len = static_cast<int>(bin.size());
                    rsa->iqmp = BN_bin2bn(&bin[0], len, NULL);
                }
            }
            fclose(fp);
            if (!got_algorithm) {
                RSA_free(rsa);
                isc_throw(BadKey, "Missing Algorithm entry");
            }
            if (!got_modulus) {
                RSA_free(rsa);
                isc_throw(BadKey, "Missing Modulus entry");
            }
            if (!got_pub_exponent) {
                RSA_free(rsa);
                isc_throw(BadKey, "Missing PublicExponent entry");
            }
            if (!got_priv_exponent) {
                RSA_free(rsa);
                isc_throw(BadKey, "Missing PrivateExponent entry");
            }
            if (!got_prime1) {
                RSA_free(rsa);
                isc_throw(BadKey, "Missing Prime1 entry");
            }
            if (!got_prime2) {
                RSA_free(rsa);
                isc_throw(BadKey, "Missing Prime2 entry");
            }
            if (!got_exponent1) {
                RSA_free(rsa);
                isc_throw(BadKey, "Missing Exponent1 entry");
            }
            if (!got_exponent2) {
                RSA_free(rsa);
                isc_throw(BadKey, "Missing Exponent2 entry");
            }
            if (!got_coefficient) {
                RSA_free(rsa);
                isc_throw(BadKey, "Missing Coefficient entry");
            }
            pkey_ = EVP_PKEY_new();
            if (!pkey_) {
                RSA_free(rsa);
                throw std::bad_alloc();
            }
            if (!EVP_PKEY_set1_RSA(pkey_, rsa)) {
                RSA_free(rsa);
                EVP_PKEY_free(pkey_);
                pkey_ = NULL;
                isc_throw(LibraryError, "EVP_PKEY_set1_RSA");
            }
            // set1 bumped the reference counter
            RSA_free(rsa);
        } else if ((kind_ == PUBLIC) && (key_format == BASIC)) {
            // PKCS#1 PEM file
            // warn when password not empty
            FILE* fp = fopen(filename.c_str(), "r");
            if (!fp) {
                isc_throw(BadKey, "Can't open file: " << filename);
            }
            RSA* rsa = PEM_read_RSAPublicKey(fp, NULL, 0, NULL);
            fclose(fp);
            if (!rsa) {
                isc_throw(BadKey, "PEM_read_RSAPublicKey");
            }
            pkey_ = EVP_PKEY_new();
            if (!pkey_) {
                RSA_free(rsa);
                throw std::bad_alloc();
            }
            if (!EVP_PKEY_set1_RSA(pkey_, rsa)) {
                RSA_free(rsa);
                EVP_PKEY_free(pkey_);
                pkey_ = NULL;
                isc_throw(LibraryError, "EVP_PKEY_set1_RSA");
            }
            // set1 bumped the reference counter
            RSA_free(rsa);
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
            pkey_ = PEM_read_PUBKEY(fp, NULL, 0, pwd);
            fclose(fp);
            if (!pkey_) {
                isc_throw(BadKey, "PEM_read_PUBKEY");
            }
            if (pkey_->type != EVP_PKEY_RSA) {
                EVP_PKEY_free(pkey_);
                pkey_ = NULL;
                isc_throw(BadKey, "not a RSA Public Key");
            }
        } else if ((kind_ == PUBLIC) && (key_format == DNS)) {
            // bind9 .key file (RDATA)
            // warn when password not empty
            if ((hash_ != MD5) && (hash_ != SHA1) &&
                (hash_ != SHA256) && (hash_ != SHA512)) {
                isc_throw(UnsupportedAlgorithm,
                          "Not compatible hash algorithm: " <<
                          static_cast<int>(hash_));
            }
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
            size_t key_len = bin.size();
            const uint8_t* p = &bin[0];
            unsigned int e_bytes = *p++;
            --key_len;
            if (e_bytes == 0) {
                if (key_len < 2) {
                    isc_throw(BadKey,
                              "Bad RSA Public Key: short exponent length");
                }
                e_bytes = (*p++) << 8;
                e_bytes += *p++;
                key_len -= 2;
            }
            if (key_len < e_bytes) {
                isc_throw(BadKey, "Bad RSA Public Key: short exponent");
            }
            if ((key_len - e_bytes) < 64) {
                isc_throw(BadKey, "Bad RSA Public Key: too short: " <<
                          (key_len - e_bytes) * 8);
            }
            if ((key_len - e_bytes) > 512) {
                isc_throw(BadKey, "Bad RSA Public Key: too large: " <<
                          (key_len - e_bytes) * 8);
            }
            RSA* rsa = RSA_new();
            if (!rsa) {
                throw std::bad_alloc();
            }
            rsa->e = BN_bin2bn(p, e_bytes, NULL);
            p += e_bytes;
            key_len -= e_bytes;
            rsa->n = BN_bin2bn(p, key_len, NULL);
            if (!rsa->e || !rsa->n) {
                RSA_free(rsa);
                throw std::bad_alloc();
            }
            pkey_ = EVP_PKEY_new();
            if (!pkey_) {
                RSA_free(rsa);
                throw std::bad_alloc();
            }
            if (!EVP_PKEY_set1_RSA(pkey_, rsa)) {
                RSA_free(rsa);
                EVP_PKEY_free(pkey_);
                pkey_ = NULL;
                isc_throw(LibraryError, "EVP_PKEY_set1_RSA");
            }
            // set1 bumped the reference counter
            RSA_free(rsa);
        } else if (kind_ == PUBLIC) {
            isc_throw(UnsupportedAlgorithm,
                      "Unknown RSA Public Key format: " <<
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
            if (hash_ == MD5) {
                if (sig_nid != OBJ_txt2nid("1.2.840.113549.1.1.4")) {
                    X509_free(x509_);
                    x509_ = NULL;
                    isc_throw(BadKey, "Require a RSA MD5 certificate");
                }
            } else if (hash_ == SHA1) {
                if (sig_nid != OBJ_txt2nid("1.2.840.113549.1.1.5")) {
                    X509_free(x509_);
                    x509_ = NULL;
                    isc_throw(BadKey, "Require a RSA SHA1 certificate");
                }
            } else if (hash_ == SHA224) {
                if (sig_nid != OBJ_txt2nid("1.2.840.113549.1.1.14")) {
                    X509_free(x509_);
                    x509_ = NULL;
                    isc_throw(BadKey, "Require a RSA SHA224 certificate");
                }
            } else if (hash_ == SHA256) {
                if (sig_nid != OBJ_txt2nid("1.2.840.113549.1.1.11")) {
                    X509_free(x509_);
                    x509_ = NULL;
                    isc_throw(BadKey, "Require a RSA SHA256 certificate");
                }
            } else if (hash_ == SHA384) {
                if (sig_nid != OBJ_txt2nid("1.2.840.113549.1.1.12")) {
                    X509_free(x509_);
                    x509_ = NULL;
                    isc_throw(BadKey, "Require a RSA SHA384 certificate");
                }
            } else if (hash_ == SHA512) {
                if (sig_nid != OBJ_txt2nid("1.2.840.113549.1.1.13")) {
                    X509_free(x509_);
                    x509_ = NULL;
                    isc_throw(BadKey, "Require a RSA SHA512 certificate");
                }
            } else {
                X509_free(x509_);
                x509_ = NULL;
                isc_throw(UnsupportedAlgorithm,
                          "Bad hash algorithm for certificate: " <<
                          static_cast<int>(hash_));
            }
            pkey_ = X509_get_pubkey(x509_);
            if (!pkey_) {
                X509_free(x509_);
                x509_ = NULL;
                isc_throw(BadKey, "X509_get_pubkey");
            }
            if (pkey_->type != EVP_PKEY_RSA) {
                EVP_PKEY_free(pkey_);
                pkey_ = NULL;
                X509_free(x509_);
                x509_ = NULL;
                isc_throw(BadKey, "not a RSA Public Key");
            }
        } else if (kind_ == CERT) {
            isc_throw(UnsupportedAlgorithm,
                      "Unknown Public Key Certificate format: " <<
                      static_cast<int>(key_format));
        } else {
            isc_throw(UnsupportedAlgorithm,
                      "Unknown RSA Key kind: " <<
                      static_cast<int>(kind_));
        }
        mdctx_.reset(new EVP_MD_CTX);
        EVP_MD_CTX_init(mdctx_.get());

        if (!EVP_DigestInit_ex(mdctx_.get(), md, NULL)) {
            EVP_MD_CTX_cleanup(mdctx_.get());
            EVP_PKEY_free(pkey_);
            pkey_ =NULL;
            isc_throw(LibraryError, "EVP_DigestInit_ex");
        }
    }

    /// @brief Destructor
    ~AsymImpl() {
        if (mdctx_) {
            EVP_MD_CTX_cleanup(mdctx_.get());
        }
        if (pkey_) {
            EVP_PKEY_free(pkey_);
            pkey_ = NULL;
        }
        if (x509_) {
            X509_free(x509_);
            x509_ = NULL;
        }
    }

    /// @brief Returns the key size in bits
    ///
    size_t getKeySize() const {
        return (static_cast<size_t>(EVP_PKEY_bits(pkey_)));
    }

    /// @brief Returns the output size of the signature
    ///
    /// \param sig_format The signature binary format
    size_t getSignatureLength(const AsymFormat sig_format) const {
        switch (algo_) {
        case RSA_:
            switch (sig_format) {
            case BASIC:
            case ASN1:
            case DNS:
                // In all cases a big integer of the size of n
                return (static_cast<size_t>(EVP_PKEY_size(pkey_)));
            default:
                isc_throw(UnsupportedAlgorithm,
                          "Unknown RSA Signature format: " <<
                          static_cast<int>(sig_format));
            }
        default:
            isc_throw(UnsupportedAlgorithm,
                      "Unknown asym algorithm: " <<
                      static_cast<int>(algo_));
        }
    }           

    /// @brief Add data to digest
    ///
    /// See @ref isc::cryptolink::Asym::update() for details.
    void update(const void* data, const size_t len) {
        if (!EVP_DigestUpdate(mdctx_.get(), data, len)) {
            isc_throw(LibraryError, "EVP_DigestUpdate");
        }
    }

    /// @brief Calculate the final signature
    ///
    /// See @ref isc::cryptolink::Asym::sign() for details.
    void sign(isc::util::OutputBuffer& result, size_t len,
              const AsymFormat sig_format) {
        unsigned int size = getSignatureLength(sig_format);
        ossl::SecBuf<unsigned char> sig(size);
        if (!EVP_SignFinal(mdctx_.get(), &sig[0], &size, pkey_)) {
            isc_throw(LibraryError, "EVP_SignFinal");
        }
        if (len > size) {
            len = size;
        }
        result.writeData(&sig[0], len);
    }

    /// @brief Calculate the final signature
    ///
    /// See @ref isc::cryptolink::Asym::sign() for details.
    void sign(void* result, size_t len, const AsymFormat sig_format) {
        unsigned int size = getSignatureLength(sig_format);
        ossl::SecBuf<unsigned char> sig(size);
        if (!EVP_SignFinal(mdctx_.get(), &sig[0], &size, pkey_)) {
            isc_throw(LibraryError, "EVP_SignFinal");
        }
        if (len > size) {
            len = size;
        }
        std::memcpy(result, &sig[0], len);
    }

    /// @brief Calculate the final signature
    ///
    /// See @ref isc::cryptolink::Asym::sign() for details.
    std::vector<uint8_t> sign(size_t len, const AsymFormat sig_format) {
        unsigned int size = getSignatureLength(sig_format);
        ossl::SecBuf<unsigned char> sig(size);
        if (!EVP_SignFinal(mdctx_.get(), &sig[0], &size, pkey_)) {
            isc_throw(LibraryError, "EVP_SignFinal");
        }
        // resize to min(len, size)
        sig.resize(len < size ? len : size);
        return (std::vector<uint8_t>(sig.begin(), sig.end()));
    }  

    /// @brief Verify an existing signature
    ///
    /// See @ref isc::cryptolink::Asym::verify() for details.
    bool verify(const void* sig, size_t len, const AsymFormat sig_format) {
        size_t size = getSignatureLength(sig_format);
        if (len != size) {
            return false;
        }
        unsigned char* sigbuf =
            reinterpret_cast<unsigned char*>(const_cast<void*>(sig));
        unsigned int siglen = static_cast<unsigned int>(len);
        int status = EVP_VerifyFinal(mdctx_.get(), sigbuf, siglen, pkey_);
        switch (status) {
        case 1:
            return true;
        case 0:
            return false;
        case -1:
        default:
            isc_throw(LibraryError, "EVP_VerifyFinal");
        }
    }

    /// @brief Export the key value (binary)
    ///
    /// See @ref isc::cryptolink::Asym::exportkey() for details
    std::vector<uint8_t> exportkey(const AsymKeyKind key_kind,
                                   const AsymFormat key_format) const {
        if ((key_kind == PRIVATE) && (key_format == BASIC)) {
            // PKCS#1 Private Key
            if (kind_ != PRIVATE) {
                isc_throw(UnsupportedAlgorithm, "Have no RSA Private Key");
            }
            RSA* rsa = EVP_PKEY_get1_RSA(pkey_);
            if (!rsa) {
                isc_throw(LibraryError, "EVP_PKEY_get1_RSA");
            }
            int len = i2d_RSAPrivateKey(rsa, NULL);
            if (len < 0) {
                RSA_free(rsa);
                isc_throw(LibraryError, "i2d_RSAPrivateKey 0");
            }
            std::vector<uint8_t> der(static_cast<size_t>(len));
            unsigned char* p = &der[0];
            len = i2d_RSAPrivateKey(rsa, &p);
            RSA_free(rsa);
            if (len != static_cast<int>(der.size())) {
                isc_throw(LibraryError, "i2d_RSAPrivateKey");
            }
            return der;
        } else if (key_kind == PRIVATE) {
            isc_throw(UnsupportedAlgorithm,
                      "Unknown RSA Private Key format: " <<
                      static_cast<int>(key_format));
        } else if ((key_kind == PUBLIC) && (key_format == BASIC)) {
            // PKCS#1 Public Key
            RSA* rsa = EVP_PKEY_get1_RSA(pkey_);
            if (!rsa) {
                isc_throw(LibraryError, "EVP_PKEY_get1_RSA");
            }
            int len = i2d_RSAPublicKey(rsa, NULL);
            if (len < 0) {
                RSA_free(rsa);
                isc_throw(LibraryError, "i2d_RSAPublicKey 0");
            }
            std::vector<uint8_t> der(static_cast<size_t>(len));
            unsigned char* p = &der[0];
            len = i2d_RSAPublicKey(rsa, &p);
            RSA_free(rsa);
            if (len != static_cast<int>(der.size())) {
                isc_throw(LibraryError, "i2d_RSAPublicKey");
            }
            return der;
        } else if ((key_kind == PUBLIC) && (key_format == ASN1)) {
            // SubjectPublicKeyInfo
            RSA* rsa = EVP_PKEY_get1_RSA(pkey_);
            if (!rsa) {
                isc_throw(LibraryError, "EVP_PKEY_get1_RSA");
            }
            int len = i2d_RSA_PUBKEY(rsa, NULL);
            if (len < 0) {
                RSA_free(rsa);
                isc_throw(LibraryError, "i2d_RSA_PUBKEY 0");
            }
            std::vector<uint8_t> der(static_cast<size_t>(len));
            unsigned char* p = &der[0];
            len = i2d_RSA_PUBKEY(rsa, &p);
            RSA_free(rsa);
            if (len != static_cast<int>(der.size())) {
                isc_throw(LibraryError, "i2d_RSA_PUBKEY");
            }
            return der;
        } else if ((key_kind == PUBLIC) && (key_format == DNS)) {
            // RFC 3110 DNS wire format
            RSA* rsa = EVP_PKEY_get1_RSA(pkey_);
            if (!rsa) {
                isc_throw(LibraryError, "EVP_PKEY_get1_RSA");
            }
            size_t e_bytes = BN_num_bytes(rsa->e);
            size_t mod_bytes = BN_num_bytes(rsa->n);
            size_t x_bytes = 1;
            if (e_bytes >= 256) {
                x_bytes += 2;
            }
            std::vector<uint8_t> rdata(x_bytes + e_bytes + mod_bytes);
            if (e_bytes < 256) {
                rdata[0] = e_bytes;
            } else {
                rdata[0] = 0;
                rdata[1] = (e_bytes >> 8) & 0xff;
                rdata[2] = e_bytes & 0xff;
            }
            BN_bn2bin(rsa->e, &rdata[x_bytes]);
            BN_bn2bin(rsa->n, &rdata[x_bytes + e_bytes]);
            RSA_free(rsa);
            return rdata;
        } else if (key_kind == PUBLIC) {
            isc_throw(UnsupportedAlgorithm,
                      "Unknown RSA Public Key format: " <<
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
                      "Unknown RSA Key kind: " <<
                      static_cast<int>(key_kind));
        }
    }

    /// @brief Export the key value (file)
    ///
    /// See @ref isc::cryptolink::Asym::exportkey() for details
    void exportkey(const std::string& filename,
                   const std::string& password,
                   const AsymKeyKind key_kind,
                   const AsymFormat key_format) const {
        if ((key_kind == PRIVATE) && (key_format == ASN1)) {
            // PKCS#8 Private Key PEM file
            if (kind_ != PRIVATE) {
                isc_throw(UnsupportedAlgorithm, "Have no RSA Private Key");
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
            if (!PEM_write_PKCS8PrivateKey(fp, pkey_, enc, pwd,
                                           static_cast<int>(password.size()),
                                           0, NULL)) {
                fclose(fp);
                isc_throw(LibraryError, "PEM_write_PKCS8PrivateKey");
            }
            fclose(fp);
        } else if ((key_kind == PRIVATE) && (key_format == DNS)) {
            //  bind9 .private file
            if (kind_ != PRIVATE) {
                isc_throw(UnsupportedAlgorithm, "Have no RSA Private Key");
            }
            if ((hash_ != MD5) && (hash_ != SHA1) &&
                (hash_ != SHA256) && (hash_ != SHA512)) {
                isc_throw(UnsupportedAlgorithm,
                          "Not compatible hash algorithm: " <<
                          static_cast<int>(hash_));
            }
            FILE* fp = fopen(filename.c_str(), "w");
            if (!fp) {
                isc_throw(BadKey, "Can't open file: " << filename);
            }
            RSA* rsa = EVP_PKEY_get1_RSA(pkey_);
            if (!rsa) {
                fclose(fp);
                isc_throw(LibraryError, "EVP_PKEY_get1_RSA");
            }
            fprintf(fp, "Private-key-format: v1.2\n");
            if (hash_ == MD5) {
                fprintf(fp, "Algorithm: 1 (RSA)\n");
            } else if (hash_ == SHA1) {
                fprintf(fp, "Algorithm: 5 (RSASHA1)\n");
            } else if (hash_ == SHA256) {
                fprintf(fp, "Algorithm: 8 (RSASHA256)\n");
            } else if (hash_ == SHA512) {
                fprintf(fp, "Algorithm: 10 (RSASHA512)\n");
            }
            std::vector<uint8_t> bin;
            bin.resize(BN_num_bytes(rsa->n));
            BN_bn2bin(rsa->n, &bin[0]);
            fprintf(fp, "Modulus: %s\n",
                    util::encode::encodeBase64(bin).c_str());
            bin.resize(BN_num_bytes(rsa->e));
            BN_bn2bin(rsa->e, &bin[0]);
            fprintf(fp, "PublicExponent: %s\n",
                    util::encode::encodeBase64(bin).c_str());
            bin.resize(BN_num_bytes(rsa->d));
            BN_bn2bin(rsa->d, &bin[0]);
            fprintf(fp, "PrivateExponent: %s\n",
                    util::encode::encodeBase64(bin).c_str());
            bin.resize(BN_num_bytes(rsa->p));
            BN_bn2bin(rsa->p, &bin[0]);
            fprintf(fp, "Prime1: %s\n",
                    util::encode::encodeBase64(bin).c_str());
            bin.resize(BN_num_bytes(rsa->q));
            BN_bn2bin(rsa->q, &bin[0]);
            fprintf(fp, "Prime2: %s\n",
                    util::encode::encodeBase64(bin).c_str());
            bin.resize(BN_num_bytes(rsa->dmp1));
            BN_bn2bin(rsa->dmp1, &bin[0]);
            fprintf(fp, "Exponent1: %s\n",
                    util::encode::encodeBase64(bin).c_str());
            bin.resize(BN_num_bytes(rsa->dmq1));
            BN_bn2bin(rsa->dmq1, &bin[0]);
            fprintf(fp, "Exponent2: %s\n",
                    util::encode::encodeBase64(bin).c_str());
            bin.resize(BN_num_bytes(rsa->iqmp));
            BN_bn2bin(rsa->iqmp, &bin[0]);
            fprintf(fp, "Coefficient: %s\n",
                    util::encode::encodeBase64(bin).c_str());
            fclose(fp);
            RSA_free(rsa);
        } else if (key_kind == PRIVATE) {
            if (kind_ != PRIVATE) {
                isc_throw(UnsupportedAlgorithm, "Have no RSA Private Key");
            }
            isc_throw(UnsupportedAlgorithm,
                      "Unknown RSA Private Key format: " <<
                      static_cast<int>(key_format));
        } else if ((key_kind == PUBLIC) && (key_format == BASIC)) {
            // PKCS#1 PEM file
            // warn when password not empty
            FILE* fp = fopen(filename.c_str(), "w");
            if (!fp) {
                isc_throw(BadKey, "Can't open file: " << filename);
            }
            RSA* rsa = EVP_PKEY_get1_RSA(pkey_);
            if (!rsa) {
                fclose(fp);
                isc_throw(LibraryError, "EVP_PKEY_get1_RSA");
            }
            if (!PEM_write_RSAPublicKey(fp, rsa)) {
                fclose(fp);
                RSA_free(rsa);
                isc_throw(LibraryError, "PEM_write_RSAPublicKey");
            }
            fclose(fp);
            RSA_free(rsa);
        } else if ((key_kind == PUBLIC) && (key_format == ASN1)) {
            // SubjectPublicKeyInfo PEM file
            // warn when password not empty
            FILE* fp = fopen(filename.c_str(), "w");
            if (!fp) {
                isc_throw(BadKey, "Can't open file: " << filename);
            }
            if (!PEM_write_PUBKEY(fp, pkey_)) {
                fclose(fp);
                isc_throw(LibraryError, "PEM_write_PUBKEY");
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
                      "Unknown RSA Public Key format: " <<
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
                      "Unknown RSA Key kind: " <<
                      static_cast<int>(key_kind));
        }
    }

    /// @brief Check the validity
    ///
    /// See @ref isc::cryptolink::Asym::validate() for details
    bool validate() const {
        RSA* rsa;
        X509_STORE* store;
        X509_STORE_CTX* ctx;
        int status;
        switch (kind_) {
        case PUBLIC:
            // what to do?
            return true;
        case PRIVATE:
            rsa = EVP_PKEY_get1_RSA(pkey_);
            if (!rsa) {
                return false;
            }
            status = RSA_check_key(rsa);
            RSA_free(rsa);
            return (status == 1);
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
    ///
    /// See @ref isc::cryptolink::Asym::compare() for details
    bool compare(const AsymImpl* other, const AsymKeyKind key_kind) const {
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
            // For all other cases just compare public keys
            // Falls into
        case PUBLIC:
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
            status = EVP_PKEY_cmp(pkey_, other->pkey_);
            switch (status) {
            case 1:
                // match
                return true;
            case 0:
                // don't match
                return false;
            case -1:
                // different types
                return false;
            case -2:
                // not supported
                return false;
            }
            return false;
        case PRIVATE:
            if ((kind_ != PRIVATE) || (other->kind_ != PRIVATE)) {
                return false;
            }
            // If public keys match so private too
            status = EVP_PKEY_cmp(pkey_, other->pkey_);
            switch (status) {
            case 1:
                // match
                return true;
            case 0:
                // don't match
                return false;
            case -1:
                // different types
                return false;
            case -2:
                // not supported
                return false;
            }
            return false;
        default:
            return false;
        }
    }

private:
    /// @brief The asymmetrical cryptography algorithm
    AsymAlgorithm algo_;
    /// @brief The hash algorithm
    HashAlgorithm hash_;
    /// @brief The key kind
    AsymKeyKind kind_;
    /// @brief The protected pointer to the OpenSSL EVP_MD_CTX structure
    boost::scoped_ptr<EVP_MD_CTX> mdctx_;
    /// @brief The raw pointer to the OpenSSL EVP_PKEY structure
    /// There is no EVP_PKEY_init() or EVP_PKEY_cleanup() so
    /// a smart pointer cannot be used.
    EVP_PKEY* pkey_;
    /// @brief The raw pointer to the OpenSSL X509 structure
    /// There is no X509_init() or X509_cleanup() so
    /// a smart pointer cannot be used.
    X509* x509_;
};

Asym::Asym(const void* key, size_t key_len,
           const AsymAlgorithm asym_algorithm,
           const HashAlgorithm hash_algorithm,
           const AsymKeyKind key_kind,
           const AsymFormat key_format)
{
    impl_ = new AsymImpl(key, key_len,
                         asym_algorithm, hash_algorithm,
                         key_kind, key_format);
}

Asym::Asym(const std::vector<uint8_t> key,
           const AsymAlgorithm asym_algorithm,
           const HashAlgorithm hash_algorithm,
           const AsymKeyKind key_kind,
           const AsymFormat key_format)
{
    impl_ = new AsymImpl(&key[0], key.size(),
                         asym_algorithm, hash_algorithm,
                         key_kind, key_format);
}

Asym::Asym(const std::string& filename,
           const std::string& password,
           const AsymAlgorithm asym_algorithm,
           const HashAlgorithm hash_algorithm,
           const AsymKeyKind key_kind,
           const AsymFormat key_format)
{
    impl_ = new AsymImpl(filename, password,
                         asym_algorithm, hash_algorithm,
                         key_kind, key_format);
}

Asym::~Asym() {
    delete impl_;
}

size_t
Asym::getKeySize() const {
    return (impl_->getKeySize());
}

size_t
Asym::getSignatureLength(const AsymFormat sig_format) const {
    return (impl_->getSignatureLength(sig_format));
}

void
Asym::update(const void* data, const size_t len) {
    impl_->update(data, len);
}

void
Asym::sign(isc::util::OutputBuffer& result, size_t len,
           const AsymFormat sig_format) {
    impl_->sign(result, len, sig_format);
}

void
Asym::sign(void* result, size_t len, const AsymFormat sig_format) {
    impl_->sign(result, len, sig_format);
}

std::vector<uint8_t>
Asym::sign(size_t len, const AsymFormat sig_format) {
    return (impl_->sign(len, sig_format));
}

bool
Asym::verify(const void* sig, size_t len, const AsymFormat sig_format) {
    return (impl_->verify(sig, len, sig_format));
}

std::vector<uint8_t>
Asym::exportkey(const AsymKeyKind key_kind,
                const AsymFormat key_format) const {
    return (impl_->exportkey(key_kind, key_format));
}

void
Asym::exportkey(const std::string& filename,
                const std::string& password,
                const AsymKeyKind key_kind,
                const AsymFormat key_format) const {
    impl_->exportkey(filename, password, key_kind, key_format);
}

bool
Asym::validate() const {
    return (impl_->validate());
}

bool
Asym::compare(const Asym* other, const AsymKeyKind key_kind) const {
    return (impl_->compare(other->impl_, key_kind));
}

} // namespace cryptolink
} // namespace isc
