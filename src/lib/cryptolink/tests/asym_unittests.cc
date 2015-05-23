// Copyright (C) 2014  Internet Systems Consortium, Inc. ("ISC")
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

#include <config.h>

#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>

#include <boost/lexical_cast.hpp>

#include <gtest/gtest.h>

#include <util/encode/base64.h>

#include <cryptolink/cryptolink.h>
#include <cryptolink/crypto_asym.h>

#include <util/buffer.h>
#include <exceptions/exceptions.h>

#include <boost/shared_ptr.hpp>

using boost::lexical_cast;
using namespace isc::util;
using namespace isc::util::encode;
using namespace isc::cryptolink;

namespace {

#define MODULUS	\
0xb3, 0x25, 0xc2, 0x01, 0xee, 0x8c, 0x91, 0x5d, \
0xa3, 0xea, 0x55, 0x90, 0xa2, 0x2c, 0xb3, 0xb1, \
0x35, 0x18, 0x7b, 0xa1, 0x00, 0x80, 0x4f, 0x21, \
0x32, 0x94, 0xd1, 0xa2, 0xc3, 0x1a, 0xbc, 0x0a, \
0xee, 0xcd, 0x7f, 0x23, 0x12, 0x5d, 0xf8, 0x92, \
0xcb, 0x87, 0x69, 0xfd, 0x85, 0x0f, 0x25, 0x57, \
0x88, 0x69, 0x4b, 0x5e, 0x93, 0x12, 0x3a, 0x93, \
0xa9, 0x23, 0x64, 0x0f, 0x7c, 0xaa, 0x20, 0xca, \
0x56, 0x93, 0x81, 0xe9, 0x64, 0xb2, 0x20, 0xad, \
0x55, 0x25, 0x87, 0xb1, 0x85, 0xc8, 0xd6, 0xfe, \
0x5f, 0xa9, 0xcd, 0x53, 0x2e, 0xaf, 0x9e, 0x53, \
0xa4, 0xfb, 0xba, 0xef, 0x30, 0x53, 0x9d, 0x01, \
0xee, 0xb7, 0xff, 0xaa, 0xde, 0x7a, 0xfa, 0x57, \
0xfb, 0xdf, 0x63, 0xf3, 0x9c, 0x77, 0x2e, 0xa4, \
0x97, 0x10, 0x30, 0xc1, 0x15, 0x48, 0x6b, 0x01, \
0x1e, 0x57, 0x8d, 0x5d, 0xeb, 0xfc, 0x42, 0xe1

#define PUBLIC_EXPONENT 0x01, 0x00, 0x01

#define PUBLIC_KEY \
0x30, 0x81, 0x89, \
0x02, 0x81, 0x81, 0x00, MODULUS, \
0x02, 0x03, PUBLIC_EXPONENT

#define PRIVATE_EXPONENT \
0xa8, 0xc9, 0x93, 0x5f, 0xe4, 0x94, 0xf6, 0x45, \
0x26, 0xb2, 0x1b, 0x8a, 0x18, 0xf2, 0x4b, 0x1f, \
0x54, 0x2a, 0x4c, 0x18, 0xe6, 0x72, 0xfd, 0x9b, \
0x06, 0xa0, 0x26, 0x5f, 0xd6, 0xb9, 0x32, 0xa0, \
0x8e, 0x5c, 0x79, 0x43, 0xdf, 0x03, 0x40, 0xb7, \
0x76, 0x21, 0x90, 0xa0, 0x37, 0x24, 0x8d, 0x07, \
0x4a, 0xd4, 0x02, 0x1a, 0x0a, 0x31, 0x6b, 0x95, \
0x42, 0x0f, 0xc1, 0x2f, 0xc2, 0x42, 0x3c, 0x7f, \
0x33, 0xb3, 0x54, 0x2f, 0x83, 0xf8, 0x5d, 0x7f, \
0x86, 0xa5, 0xe8, 0xbe, 0xae, 0x40, 0x41, 0x20, \
0x5d, 0xa2, 0x66, 0x9a, 0x82, 0x66, 0x03, 0xfc, \
0xf0, 0x62, 0x24, 0x08, 0x25, 0x99, 0xc6, 0x2b, \
0xef, 0x9d, 0x79, 0x54, 0x21, 0x91, 0x62, 0x76, \
0xe5, 0x0b, 0x30, 0xe7, 0x96, 0x9c, 0xfa, 0x45, \
0xf1, 0x6f, 0xa7, 0x6b, 0x94, 0xa2, 0x70, 0x3d, \
0xdd, 0x74, 0x6d, 0x4c, 0x8e, 0x8e, 0xe7, 0x01

#define PRIME1 \
0xda, 0x36, 0xde, 0xd3, 0x0a, 0x15, 0x20, 0xac, \
0x79, 0xa7, 0xe0, 0xa6, 0x55, 0x69, 0xea, 0xcd, \
0xf7, 0xe7, 0xf3, 0xda, 0xf6, 0xeb, 0xdc, 0xdb, \
0x7c, 0xdd, 0x13, 0x6c, 0xaa, 0xfd, 0x6e, 0x98, \
0x7b, 0x54, 0x25, 0xc0, 0x3b, 0x7d, 0xf9, 0xb5, \
0x5b, 0x97, 0x2f, 0xe6, 0xc1, 0x4d, 0x7d, 0x5e, \
0x3b, 0x51, 0x9c, 0xc6, 0xb3, 0xd4, 0x23, 0x43, \
0xbf, 0x42, 0x98, 0x50, 0x03, 0xfb, 0x0b, 0x51

#define PRIME2 \
0xd2, 0x2b, 0x1c, 0x29, 0x83, 0x01, 0xfd, 0x41, \
0x49, 0xfb, 0x95, 0x89, 0x7c, 0xaf, 0x81, 0x81, \
0xce, 0xd1, 0x77, 0x5f, 0x65, 0x61, 0x61, 0x07, \
0xd5, 0x45, 0x58, 0xc5, 0xdd, 0x73, 0x6b, 0x63, \
0x3a, 0x82, 0x92, 0xad, 0xa6, 0x71, 0xa1, 0xcf, \
0xe3, 0xb5, 0x10, 0x52, 0x42, 0xe5, 0x76, 0x8a, \
0x1b, 0xca, 0x6a, 0x52, 0x9d, 0x54, 0x78, 0x07, \
0xcf, 0x1e, 0xed, 0xe4, 0xf2, 0xf2, 0xba, 0x91

#define EXPONENT1 \
0x6e, 0xf6, 0xa4, 0x0c, 0x90, 0xfd, 0xf9, 0x65, \
0x7b, 0x5f, 0xa0, 0xdf, 0x34, 0x63, 0xed, 0xe0, \
0xdb, 0x05, 0x7a, 0x7d, 0x88, 0x3e, 0x9c, 0x4a, \
0x88, 0x8e, 0x2b, 0x08, 0x81, 0x52, 0xea, 0x60, \
0x63, 0xa6, 0x80, 0xa3, 0xe6, 0x1c, 0xc3, 0x54, \
0x33, 0xc5, 0x07, 0xb8, 0xc1, 0xe7, 0x53, 0xaf, \
0x0d, 0x5f, 0x0c, 0xe8, 0x06, 0x1e, 0x03, 0xe8, \
0xb9, 0x63, 0x75, 0xec, 0x8a, 0x79, 0xa8, 0x61

#define EXPONENT2 \
0x7c, 0x6d, 0x29, 0x6f, 0x2a, 0x30, 0xb3, 0x4f, \
0x44, 0x0d, 0xbe, 0xaa, 0x77, 0x37, 0x30, 0xe5, \
0x39, 0x1c, 0xaa, 0x1f, 0xc0, 0x55, 0xb6, 0xac, \
0x7c, 0x87, 0x61, 0xd7, 0x43, 0x14, 0x62, 0x2f, \
0x8d, 0x24, 0x60, 0xd2, 0x8e, 0x08, 0x18, 0x54, \
0x8b, 0xeb, 0x56, 0x8e, 0x5d, 0x2c, 0x9c, 0xd1, \
0x87, 0x42, 0x7f, 0x50, 0x09, 0xf5, 0x48, 0x5a, \
0xd7, 0x34, 0xe8, 0x82, 0xf3, 0x92, 0xe1, 0x01

#define COEFFICIENT \
0x13, 0x5f, 0x97, 0x80, 0x10, 0x66, 0x54, 0x05, \
0x55, 0x05, 0x03, 0x37, 0x96, 0xe0, 0xc0, 0xa7, \
0x25, 0x7b, 0x70, 0x4a, 0xd2, 0x0e, 0xce, 0x82, \
0x42, 0x3e, 0xb9, 0x5a, 0x2d, 0x87, 0xca, 0xfa, \
0xaa, 0x82, 0xe4, 0xed, 0xdb, 0xbf, 0xbf, 0x26, \
0x9b, 0x50, 0x84, 0x9e, 0xb0, 0xd0, 0x10, 0xb4, \
0x79, 0x56, 0x1c, 0xd1, 0x49, 0xa1, 0x4f, 0xf8, \
0x52, 0x6e, 0xb4, 0x1b, 0x1a, 0x5f, 0x48, 0x0c

#define PRIVATE_KEY \
0x30, 0x82, 0x02, 0x5c, 0x02, 0x01, 0x00, \
0x02, 0x81, 0x81, 0x00, MODULUS, \
0x02, 0x03, PUBLIC_EXPONENT, \
0x02, 0x81, 0x81, 0x00, PRIVATE_EXPONENT, \
0x02, 0x41, 0x00, PRIME1, \
0x02, 0x41, 0x00, PRIME2, \
0x02, 0x40, EXPONENT1, \
0x02, 0x40, EXPONENT2, \
0x02, 0x40, COEFFICIENT

    /// @brief Public Key in PKCS#1 format
    const uint8_t pubpkcs1[] = {
        0x30, // tag=SEQUENCE (RSAPublicKey)
        0x81, 0x89, // length=137
         0x02, // tag=INTEGER (modulus -- n)
         0x81, 0x81, // length=129
          0x00, MODULUS,
         0x02, // tag=INTEGER (publicExponent -- e)
         0x03, // length=3
          PUBLIC_EXPONENT
    };
    size_t pubpkcs1len = 140;

    /// @brief Public Key in SubjectPublicKeyInfo format
    const uint8_t pubspki[] = {
        0x30, // tag=SEQUENCE (SubjectPublicKeyInfo)
        0x81, 0x9f, // length=159
         0x30, // tag=SEQUENCE (algorithm : AlgorithmIdentifier)
         0x0d, // length=13
          0x06, // tag=OBJECTID (algorithm)
          0x09, // length=9
           0x2a, 0x86, 0x48, 0x86,
           0xf7, 0x0d, 0x01, 0x01,
           0x01, // value=rsaEncryption
          0x05, // tag=NULL (parameter)
          0x00, // length=00
         0x03, // tag=BIT STRING (subjectPublicKey)
        0x81, 0x8d, // length=141
         0x00, PUBLIC_KEY
    };
    size_t pubspkilen = 162;

    /// @brief Public Key in DNSSEC format (length 132)
    const uint8_t pubdns[] = {
        0x03, // length=3
        PUBLIC_EXPONENT,
        MODULUS
    };
    size_t pubdnslen = 132;

    /// @brief Private Key in PKCS#1 format
    const uint8_t privpkcs1[] = {
        0x30, // tag=SEQUENCE (RSAPrivateKey)
        0x82, 0x02, 0x5c, // length=604
         0x02, // tag=INTEGER (version : Version)
         0x01, // length=1
          0x00, // value=0
         0x02, // tag=INTEGER (modulus -- n)
         0x81, 0x81, // length=129
          0x00, MODULUS,
         0x02, // tag=INTEGER (publicExponent -- e)
         0x03, // length=3
          PUBLIC_EXPONENT,
         0x02, // tag=INTEGER (privateExponent -- d)
         0x81, 0x81, // length=129
          0x00, PRIVATE_EXPONENT,
         0x02, // tag=INTEGER (prime1 -- p)
         0x41, // length=65
          0x00, PRIME1,
         0x02, // tag=INTEGER (prime2 -- q)
         0x41, // length=65
          0x00, PRIME2,
         0x02, // tag=INTEGER (exponent1 -- d mod (p-1))
         0x40, // length=64
          EXPONENT1,
         0x02, // tag=INTEGER (exponent2 -- d mod (q-1))
         0x40, // length=64
          EXPONENT2,
         0x02, // tag=INTEGER (coefficient -- 1/q mod p)
         0x40, // length=64
          COEFFICIENT
    };
    size_t privpkcs1len = 608;

    /// @brief Public Key file (SubjectPublicKeyInfo in PEM)
    const std::string pubfile = TEST_DATA_SRCDIR "/pub.pem";

    /// @brief Private Key file (PKCS#8 in PEM, password '1234')
    const std::string privfile = TEST_DATA_SRCDIR "/pkcs8.pem";

    /// @brief Certificate file (X.509 Public Key Certificate in PEM)
    const std::string certfile = TEST_DATA_SRCDIR "/x509.pem";

    /// @brief Compare data with expected value
    /// @param data Value to compare
    /// @param expected Expected value
    /// @param len Length of the expected value
    void checkData(const uint8_t* data, const uint8_t* expected,
                   size_t len) {
        for (size_t i = 0; i < len; ++i) {
            ASSERT_EQ(expected[i], data[i]);
        }
    }

    /// @brief Compare OutputBuffer with expected value
    /// encapsulated checkData()
    /// @param buf buffer to compare
    /// @param expected Expected value
    /// @param len Length of the expected value
    void checkBuffer(const OutputBuffer& buf, const uint8_t* expected,
                     size_t len)
    {
        ASSERT_EQ(len, buf.getLength());
        checkData(static_cast<const uint8_t*>(buf.getData()), expected,
                  len);
    }

    /// @brief Sign and verify with an instantiation of an asymmetrical
    /// cryptography object
    /// See @ref doAsymTest for parameters
    void doAsymTestDirect(const std::string& data,
                          const std::string& privfilename,
                          const std::string& password,
                          const std::string& pubfilename,
                          const AsymAlgorithm asym_algorithm,
                          const HashAlgorithm hash_algorithm,
                          const AsymFormat sig_format,
                          const uint8_t* expected_sig,
                          size_t sig_len) {
        OutputBuffer data_buf(data.size());
        data_buf.writeData(data.c_str(), data.size());
        OutputBuffer sig(1);
        CryptoLink& crypto = CryptoLink::getCryptoLink();

        // Sign it
        boost::shared_ptr<Asym> rsa_sign(crypto.createAsym(privfilename,
                                                           password,
                                                           asym_algorithm,
                                                           hash_algorithm,
                                                           PRIVATE,
                                                           ASN1),
                                         deleteAsym);
        rsa_sign->update(data_buf.getData(), data_buf.getLength());
        rsa_sign->sign(sig, sig_len, sig_format);

        // Check if the signature is what we expect
        checkBuffer(sig, expected_sig, sig_len);

        // Check whether we can verify it ourselves
        boost::shared_ptr<Asym> rsa_verify(crypto.createAsym(pubfilename,
                                                             "",
                                                             asym_algorithm,
                                                             hash_algorithm,
                                                             PUBLIC,
                                                             ASN1),
                                           deleteAsym);
        rsa_verify->update(data_buf.getData(), data_buf.getLength());
        EXPECT_TRUE(rsa_verify->verify(sig.getData(),
                                       sig.getLength(),
                                       sig_format));

        // Change the length and check whether verification fails then
        // Relies on the fact the length is checked first
        EXPECT_FALSE(rsa_verify->verify(sig.getData(),
                                        sig.getLength() - 1,
                                        sig_format));
        EXPECT_FALSE(rsa_verify->verify(sig.getData(),
                                        sig.getLength() + 1,
                                        sig_format));

        // Change the sig by flipping the first octet, and check
        // whether verification fails then
        sig.writeUint8At(~sig[0], 0);
        EXPECT_FALSE(rsa_verify->verify(sig.getData(),
                                        sig.getLength(),
                                        sig_format));
    }

    /// @brief Sign and verify with vector representation of signature
    /// cryptography object
    /// See @ref doAsymTest for parameters
    void doAsymTestVector(const std::string& data,
                          const std::string& privfilename,
                          const std::string& password,
                          const std::string& pubfilename,
                          const AsymAlgorithm asym_algorithm,
                          const HashAlgorithm hash_algorithm,
                          const AsymFormat sig_format,
                          const uint8_t* expected_sig,
                          size_t sig_len) {
        CryptoLink& crypto = CryptoLink::getCryptoLink();
        boost::shared_ptr<Asym> rsa_sign(crypto.createAsym(privfilename,
                                                           password,
                                                           asym_algorithm,
                                                           hash_algorithm,
                                                           PRIVATE,
                                                           ASN1),
                                         deleteAsym);
        rsa_sign->update(data.c_str(), data.size());
        std::vector<uint8_t> sig = rsa_sign->sign(sig_len, sig_format);
        ASSERT_EQ(sig_len, sig.size());
        checkData(&sig[0], expected_sig, sig_len);

        boost::shared_ptr<Asym> rsa_verify(crypto.createAsym(pubfilename,
                                                             "",
                                                             asym_algorithm,
                                                             hash_algorithm,
                                                             PUBLIC,
                                                             ASN1),
                                           deleteAsym);
        rsa_verify->update(data.c_str(), data.size());
        EXPECT_TRUE(rsa_verify->verify(&sig[0], sig.size(), sig_format));

        EXPECT_FALSE(rsa_verify->verify(&sig[0], sig.size() - 1, sig_format));
        EXPECT_FALSE(rsa_verify->verify(&sig[0], sig.size() + 1, sig_format));

        sig[0] = ~sig[0];
        EXPECT_FALSE(rsa_verify->verify(&sig[0], sig.size(), sig_format));
    }

    /// @brief Sign and verify with array representation of signature
    /// cryptography object
    /// See @ref doAsymTest for parameters
    void doAsymTestArray(const std::string& data,
                         const std::string& privfilename,
                         const std::string& password,
                         const std::string& pubfilename,
                         const AsymAlgorithm asym_algorithm,
                         const HashAlgorithm hash_algorithm,
                         const AsymFormat sig_format,
                         const uint8_t* expected_sig,
                          size_t sig_len) {
        CryptoLink& crypto = CryptoLink::getCryptoLink();
        boost::shared_ptr<Asym> rsa_sign(crypto.createAsym(privfilename,
                                                           password,
                                                           asym_algorithm,
                                                           hash_algorithm,
                                                           PRIVATE,
                                                           ASN1),
                                         deleteAsym);
        rsa_sign->update(data.c_str(), data.size());

        // note: this is not exception-safe, and can leak, but
        // if there is an unexpected exception in the code below we
        // have more important things to fix.
        uint8_t* sig = new uint8_t[sig_len];

        rsa_sign->sign(sig, sig_len, sig_format);
        checkData(sig, expected_sig, sig_len);

        boost::shared_ptr<Asym> rsa_verify(crypto.createAsym(pubfilename,
                                                             "",
                                                             asym_algorithm,
                                                             hash_algorithm,
                                                             PUBLIC,
                                                             ASN1),
                                           deleteAsym);
        rsa_verify->update(data.c_str(), data.size());
        EXPECT_TRUE(rsa_verify->verify(sig, sig_len, sig_format));

        EXPECT_FALSE(rsa_verify->verify(sig, sig_len - 1, sig_format));
        EXPECT_FALSE(rsa_verify->verify(sig, sig_len + 1, sig_format));

        sig[0] = ~sig[0];
        EXPECT_FALSE(rsa_verify->verify(sig, sig_len, sig_format));

        delete[] sig;
    }

    /// @brief Sign and verify using all variants
    /// @param data Input value
    /// @param privfilename Private key file name
    /// @param password Private key password
    /// @param pubfilename Public key file name
    /// @param asym_algorithm Asym algorithm enum
    /// @param hash_algorithm Hash algorithm enum
    /// @param sig_format Signature format enum
    /// @param expected_sig Expected value
    /// @param sig_len Expected value length
    void doAsymTest(const std::string& data,
                    const std::string& privfilename,
                    const std::string& password,
                    const std::string& pubfilename,
                    const AsymAlgorithm asym_algorithm,
                    const HashAlgorithm hash_algorithm,
                    const AsymFormat sig_format,
                    const uint8_t* expected_sig,
                    size_t sig_len) {
        doAsymTestDirect(data, privfilename, password, pubfilename,
                         asym_algorithm, hash_algorithm, sig_format,
                         expected_sig, sig_len);
        doAsymTestVector(data, privfilename, password, pubfilename,
                         asym_algorithm, hash_algorithm, sig_format,
                         expected_sig, sig_len);
        doAsymTestArray(data, privfilename, password, pubfilename,
                        asym_algorithm, hash_algorithm, sig_format,
                        expected_sig, sig_len);
    }
}

//
// Test values
//
TEST(AsymTest, RSA_SHA1) {
    const uint8_t sig_expected[] = {
        0x16, 0xaa, 0xd3, 0x27, 0x5b, 0x22, 0xff, 0x2b,
        0x74, 0x77, 0x7a, 0x20, 0x6c, 0xdc, 0xa6, 0xb1,
        0x88, 0x1a, 0xb3, 0xc6, 0x5a, 0xae, 0x35, 0x3a,
        0x04, 0x8d, 0x7f, 0x81, 0x5b, 0xef, 0xd6, 0xe2,
        0x07, 0xee, 0xec, 0x1e, 0xf4, 0x89, 0x82, 0x6c,
        0x2c, 0x0c, 0x25, 0x8a, 0xf0, 0x8a, 0xde, 0x6c,
        0xf7, 0x66, 0x9d, 0xa6, 0xd5, 0x69, 0x1e, 0x47,
        0x76, 0xf3, 0xe7, 0x47, 0x12, 0xd5, 0x92, 0x45,
        0xb5, 0xc6, 0x50, 0x32, 0xe1, 0x25, 0xd9, 0xa1,
        0x23, 0xd1, 0x12, 0x6d, 0x1f, 0xa8, 0x9e, 0xc3,
        0xdb, 0x41, 0xb3, 0x13, 0x0b, 0x7a, 0xea, 0x72,
        0xa7, 0x60, 0xc8, 0xfd, 0x89, 0xee, 0x36, 0xe4,
        0x5c, 0xa8, 0xfa, 0x86, 0x4b, 0xcc, 0x15, 0x7d,
        0xcb, 0x79, 0x90, 0x51, 0xa2, 0x62, 0x43, 0xc7,
        0xe1, 0x04, 0x08, 0x13, 0x68, 0x6d, 0x7b, 0x4d,
        0x45, 0xca, 0x3e, 0x6c, 0xba, 0x62, 0x90, 0x0a,
        // pad
        0x00 
    };
    const size_t sig_len = 128;
    doAsymTest("Permission to use, copy, modify, and/or "
               "distribute this software\n",
               privfile, "1234", pubfile, RSA_, SHA1, BASIC,
               sig_expected, sig_len);
}

//
// Constructor
//
TEST(AsymTest, BAD_ALGO) {
    CryptoLink& crypto = CryptoLink::getCryptoLink();
    EXPECT_THROW(crypto.createAsym(pubpkcs1, pubpkcs1len,
                                   DSA_, SHA1, PUBLIC, BASIC),
                 UnsupportedAlgorithm);
    EXPECT_THROW(crypto.createAsym(pubpkcs1, pubpkcs1len,
                                   ECDSA_, SHA1, PUBLIC, BASIC),
                 UnsupportedAlgorithm);

    EXPECT_THROW(crypto.createAsym(pubfile, "", DSA_, SHA1, PUBLIC, ASN1),
                 UnsupportedAlgorithm);
    EXPECT_THROW(crypto.createAsym(pubfile, "", ECDSA_, SHA1, PUBLIC, ASN1),
                 UnsupportedAlgorithm);

    EXPECT_THROW(crypto.createAsym(pubpkcs1, pubpkcs1len,
                                   RSA_, UNKNOWN_HASH, PUBLIC, BASIC),
                 UnsupportedAlgorithm);

    EXPECT_THROW(crypto.createAsym(pubfile, "", RSA_, UNKNOWN_HASH,
                                   PUBLIC, ASN1),
                 UnsupportedAlgorithm);
}

TEST(AsymTest, RSA_PUB_PKCS1) {
    CryptoLink& crypto = CryptoLink::getCryptoLink();
    boost::shared_ptr<Asym> pub_key(crypto.createAsym(pubpkcs1, pubpkcs1len,
                                                      RSA_, SHA1,
                                                      PUBLIC, BASIC),
                                    deleteAsym);
    ASSERT_TRUE(pub_key.get()->validate());
    EXPECT_EQ(1024, pub_key.get()->getKeySize());
    EXPECT_EQ(128, pub_key.get()->getSignatureLength(BASIC));
    EXPECT_EQ(128, pub_key.get()->getSignatureLength(ASN1));
    EXPECT_EQ(128, pub_key.get()->getSignatureLength(DNS));

    EXPECT_THROW(crypto.createAsym(pubpkcs1, pubpkcs1len - 1,
                                   RSA_, SHA1, PUBLIC, BASIC),
                 BadKey);

    boost::shared_ptr<Asym> ref_key(crypto.createAsym(pubfile, "",
                                                      RSA_, SHA1,
                                                      PUBLIC, ASN1),
                                    deleteAsym);
    EXPECT_TRUE(pub_key.get()->compare(ref_key.get(), PUBLIC));
    EXPECT_TRUE(ref_key.get()->compare(pub_key.get(), PUBLIC));
    EXPECT_FALSE(pub_key.get()->compare(ref_key.get(), PRIVATE));
    EXPECT_FALSE(pub_key.get()->compare(ref_key.get(), CERT));

    const std::vector<uint8_t> pubbin =
        ref_key.get()->exportkey(PUBLIC, BASIC);
    checkData(&pubbin[0], pubpkcs1, pubpkcs1len);
}

TEST(AsymTest, RSA_PUB_SPKI) {
    CryptoLink& crypto = CryptoLink::getCryptoLink();
    boost::shared_ptr<Asym> pub_key(crypto.createAsym(pubspki, pubspkilen,
                                                      RSA_, SHA1,
                                                      PUBLIC, ASN1),
                                    deleteAsym);
    ASSERT_TRUE(pub_key.get()->validate());
    EXPECT_EQ(1024, pub_key.get()->getKeySize());

    EXPECT_THROW(crypto.createAsym(pubspki, pubspkilen - 1,
                                   RSA_, SHA1, PUBLIC, ASN1),
                 BadKey);
    EXPECT_THROW(crypto.createAsym(pubspki, pubspkilen,
                                   RSA_, SHA1, PUBLIC, BASIC),
                 BadKey);

    boost::shared_ptr<Asym> ref_key(crypto.createAsym(pubfile, "",
                                                      RSA_, SHA1,
                                                      PUBLIC, ASN1),
                                    deleteAsym);
    EXPECT_TRUE(pub_key.get()->compare(ref_key.get(), PUBLIC));
    EXPECT_TRUE(ref_key.get()->compare(pub_key.get(), PUBLIC));
    EXPECT_FALSE(pub_key.get()->compare(ref_key.get(), PRIVATE));
    EXPECT_FALSE(pub_key.get()->compare(ref_key.get(), CERT));

    const std::vector<uint8_t> pubbin =
        ref_key.get()->exportkey(PUBLIC, ASN1);
    checkData(&pubbin[0], pubspki, pubspkilen);
}

TEST(AsymTest, RSA_PUB_DNS) {
    CryptoLink& crypto = CryptoLink::getCryptoLink();
    boost::shared_ptr<Asym> pub_key(crypto.createAsym(pubdns, pubdnslen,
                                                      RSA_, SHA1,
                                                      PUBLIC, DNS),
                                    deleteAsym);
    ASSERT_TRUE(pub_key.get()->validate());
    EXPECT_EQ(1024, pub_key.get()->getKeySize());

    boost::shared_ptr<Asym> ref_key(crypto.createAsym(pubfile, "",
                                                      RSA_, SHA1,
                                                      PUBLIC, ASN1),
                                    deleteAsym);
    EXPECT_TRUE(pub_key.get()->compare(ref_key.get(), PUBLIC));
    EXPECT_TRUE(ref_key.get()->compare(pub_key.get(), PUBLIC));
    EXPECT_FALSE(pub_key.get()->compare(ref_key.get(), PRIVATE));
    EXPECT_FALSE(pub_key.get()->compare(ref_key.get(), CERT));

    const std::vector<uint8_t> pubbin =
        ref_key.get()->exportkey(PUBLIC, DNS);
    EXPECT_EQ(pubbin.size(), pubdnslen);
    checkData(&pubbin[0], pubdns, pubdnslen);

    const std::string keystr =
       "AwEAAbMlwgHujJFdo+pVkKIss7E1GHuhAIBPITKU0aLDGrwK7s1/IxJd+JLLh2n"
       "9hQ8lV4hpS16TEjqTqSNkD3yqIMpWk4HpZLIgrVUlh7GFyNb+X6nNUy6vnlOk+7r"
       "vMFOdAe63/6reevpX+99j85x3LqSXEDDBFUhrAR5XjV3r/ELh";
    std::vector<uint8_t> keybin;
    decodeBase64(keystr, keybin);
    EXPECT_EQ(keybin.size(), pubdnslen);
    checkData(&keybin[0], pubdns, pubdnslen);

    const std::string dnsfile = TEST_DATA_SRCDIR "/Kexample.+005+18330.key";
    boost::shared_ptr<Asym> dns_key(crypto.createAsym(dnsfile, "",
						      RSA_, SHA1,
						      PUBLIC, DNS),
				    deleteAsym);
    EXPECT_TRUE(dns_key.get()->compare(ref_key.get(), PUBLIC));
    EXPECT_TRUE(ref_key.get()->compare(dns_key.get(), PUBLIC));
}

TEST(AsymTest, RSA_PRIV_PKCS1) {
    CryptoLink& crypto = CryptoLink::getCryptoLink();
    boost::shared_ptr<Asym> priv_key(crypto.createAsym(privpkcs1, privpkcs1len,
                                                      RSA_, SHA1,
                                                      PRIVATE, BASIC),
                                    deleteAsym);
    ASSERT_TRUE(priv_key.get()->validate());
    EXPECT_EQ(1024, priv_key.get()->getKeySize());
    EXPECT_EQ(128, priv_key.get()->getSignatureLength(BASIC));
    EXPECT_EQ(128, priv_key.get()->getSignatureLength(ASN1));
    EXPECT_EQ(128, priv_key.get()->getSignatureLength(DNS));

    EXPECT_THROW(crypto.createAsym(privpkcs1, privpkcs1len - 1,
                                   RSA_, SHA1, PRIVATE, BASIC),
                 BadKey);

    boost::shared_ptr<Asym> ref_key(crypto.createAsym(privfile, "1234",
                                                      RSA_, SHA1,
                                                      PRIVATE, ASN1),
                                    deleteAsym);
    EXPECT_TRUE(priv_key.get()->compare(ref_key.get(), PRIVATE));
    EXPECT_TRUE(ref_key.get()->compare(priv_key.get(), PRIVATE));
    EXPECT_TRUE(priv_key.get()->compare(ref_key.get(), PUBLIC));
    EXPECT_FALSE(priv_key.get()->compare(ref_key.get(), CERT));

    const std::vector<uint8_t> privbin =
        ref_key.get()->exportkey(PRIVATE, BASIC);
    checkData(&privbin[0], privpkcs1, privpkcs1len);

    boost::shared_ptr<Asym> pub_key(crypto.createAsym(pubfile, "",
                                                      RSA_, SHA1,
                                                      PUBLIC, ASN1),
                                    deleteAsym);
    EXPECT_TRUE(priv_key.get()->compare(pub_key.get(), PUBLIC));
    EXPECT_TRUE(pub_key.get()->compare(priv_key.get(), PUBLIC));
}

TEST(AsymTest, RSA_PRIV_PKCS) {
    CryptoLink& crypto = CryptoLink::getCryptoLink();
    boost::shared_ptr<Asym> ref_key(crypto.createAsym(privfile, "1234",
                                                      RSA_, SHA1,
                                                      PRIVATE, ASN1),
                                    deleteAsym);
#ifndef WITH_BOTAN
    const std::string pkcs1file = TEST_DATA_SRCDIR "/priv.pem";
    boost::shared_ptr<Asym> pkcs1_key(crypto.createAsym(pkcs1file, "",
                                                        RSA_, SHA1,
                                                        PRIVATE, BASIC),
                                    deleteAsym);
    EXPECT_TRUE(pkcs1_key.get()->validate());
    EXPECT_TRUE(pkcs1_key.get()->compare(ref_key.get(), PRIVATE));
    EXPECT_TRUE(ref_key.get()->compare(pkcs1_key.get(), PRIVATE));
#endif

    // PKCS#8 without encryption
    const std::string nefile = TEST_DATA_SRCDIR "/pkcs8ne.pem";
    boost::shared_ptr<Asym> ne_key(crypto.createAsym(nefile, "",
                                                     RSA_, SHA1,
                                                     PRIVATE, ASN1),
                                   deleteAsym);
    EXPECT_TRUE(ne_key.get()->validate());
    EXPECT_TRUE(ne_key.get()->compare(ref_key.get(), PRIVATE));
    EXPECT_TRUE(ref_key.get()->compare(ne_key.get(), PRIVATE));
}

TEST(AsymTest, RSA_PRIV_DNS) {
    CryptoLink& crypto = CryptoLink::getCryptoLink();
    const std::string privdnsfile =
        TEST_DATA_SRCDIR "/Kexample.+005+18330.private";
    boost::shared_ptr<Asym> dns_key(crypto.createAsym(privdnsfile, "",
                                                      RSA_, SHA1,
                                                      PRIVATE, DNS),
                                    deleteAsym);
    EXPECT_TRUE(dns_key.get()->validate());
    EXPECT_EQ(1024, dns_key.get()->getKeySize());

#ifndef WITH_BOTAN
    EXPECT_THROW(crypto.createAsym(privdnsfile, "",
                                   RSA_, SHA1, PRIVATE, BASIC),
                 BadKey);
#endif
    EXPECT_THROW(crypto.createAsym(privdnsfile, "",
                                   RSA_, SHA1, PRIVATE, ASN1),
                 BadKey);
    EXPECT_THROW(crypto.createAsym(privdnsfile, "",
                                   RSA_, MD5, PRIVATE, DNS),
                 BadKey);
    EXPECT_THROW(crypto.createAsym(privdnsfile, "",
                                   RSA_, SHA256, PRIVATE, DNS),
                 BadKey);
    EXPECT_THROW(crypto.createAsym(privdnsfile, "",
                                   RSA_, SHA512, PRIVATE, DNS),
                 BadKey);
    EXPECT_THROW(crypto.createAsym(privdnsfile, "",
                                   RSA_, SHA224, PRIVATE, DNS),
                 UnsupportedAlgorithm);
    EXPECT_THROW(crypto.createAsym(privdnsfile, "",
                                   RSA_, SHA384, PRIVATE, DNS),
                 UnsupportedAlgorithm);

    boost::shared_ptr<Asym> ref_key(crypto.createAsym(privfile, "1234",
                                                      RSA_, SHA1,
                                                      PRIVATE, ASN1),
                                    deleteAsym);
    EXPECT_TRUE(dns_key.get()->compare(ref_key.get(), PRIVATE));
    EXPECT_TRUE(ref_key.get()->compare(dns_key.get(), PRIVATE));
    EXPECT_TRUE(dns_key.get()->compare(ref_key.get(), PUBLIC));
    EXPECT_FALSE(dns_key.get()->compare(ref_key.get(), CERT));

    char tempname[] = "/tmp/privateXXXXXX";
    const std::string testfile = mktemp(tempname);
    ref_key.get()->exportkey(testfile, "", PRIVATE, DNS);
    FILE* fp;
    fp = fopen(testfile.c_str(), "r");
    ASSERT_TRUE(fp != NULL);
    std::vector<char> testbuf(1024);
    size_t tcc = fread(&testbuf[0], 1024, 1, fp);
    testbuf.resize(tcc);
    fclose(fp);
    fp = fopen(privdnsfile.c_str(), "r");
    ASSERT_TRUE(fp != NULL);
    std::vector<char> refbuf(1024);
    int rcc = fread(&refbuf[0], 1024, 1, fp);
    refbuf.resize(rcc);
    fclose(fp);
    EXPECT_EQ(rcc, tcc);
    EXPECT_TRUE(testbuf == refbuf);
    unlink(testfile.c_str());
}

TEST(AsymTest, CERTIFICATE) {
    CryptoLink& crypto = CryptoLink::getCryptoLink();
    boost::shared_ptr<Asym> from_file(crypto.createAsym(certfile, "",
                                                        RSA_, SHA1,
                                                        CERT, ASN1),
                                      deleteAsym);
    EXPECT_TRUE(from_file.get()->validate());
    EXPECT_EQ(1024, from_file.get()->getKeySize());

    EXPECT_THROW(crypto.createAsym(certfile, "", RSA_, SHA1, PUBLIC, ASN1),
                 BadKey);
    EXPECT_THROW(crypto.createAsym(certfile, "", RSA_, SHA1, PRIVATE, ASN1),
                 BadKey);
    EXPECT_THROW(crypto.createAsym(certfile, "", RSA_, SHA1, CERT, BASIC),
                 UnsupportedAlgorithm);
    EXPECT_THROW(crypto.createAsym(certfile, "", RSA_, SHA1, CERT, DNS),
                 UnsupportedAlgorithm);
    EXPECT_THROW(crypto.createAsym(certfile, "", RSA_, MD5, CERT, ASN1),
                 BadKey);
    EXPECT_THROW(crypto.createAsym(certfile, "", RSA_, SHA224, CERT, ASN1),
                 BadKey);
    EXPECT_THROW(crypto.createAsym(certfile, "", RSA_, SHA256, CERT, ASN1),
                 BadKey);
    EXPECT_THROW(crypto.createAsym(certfile, "", RSA_, SHA384, CERT, ASN1),
                 BadKey);
    EXPECT_THROW(crypto.createAsym(certfile, "", RSA_, SHA512, CERT, ASN1),
                 BadKey);

    boost::shared_ptr<Asym> pub_key(crypto.createAsym(pubfile, "",
                                                      RSA_, SHA1,
                                                      PUBLIC, ASN1),
                                    deleteAsym);
    EXPECT_TRUE(from_file.get()->compare(pub_key.get(), PUBLIC));
    EXPECT_TRUE(pub_key.get()->compare(from_file.get(), PUBLIC));
    EXPECT_FALSE(from_file.get()->compare(pub_key.get(), PRIVATE));
    EXPECT_FALSE(pub_key.get()->compare(from_file.get(), PRIVATE));

    std::vector<uint8_t> certbin = from_file.get()->exportkey(CERT, ASN1);
    boost::shared_ptr<Asym> from_bin(crypto.createAsym(&certbin[0],
                                                       certbin.size(),
                                                       RSA_, SHA1,
                                                       CERT, ASN1),
                                     deleteAsym);
    EXPECT_TRUE(from_bin.get()->validate());
    EXPECT_TRUE(from_file.get()->compare(from_bin.get(), PUBLIC));
    EXPECT_TRUE(from_bin.get()->compare(from_file.get(), PUBLIC));
    EXPECT_TRUE(from_file.get()->compare(from_bin.get(), CERT));
    EXPECT_TRUE(from_bin.get()->compare(from_file.get(), CERT));

    EXPECT_THROW(crypto.createAsym(&certbin[0], certbin.size() - 1,
                                   RSA_, SHA1, CERT, ASN1),
                 BadKey);
    EXPECT_THROW(crypto.createAsym(&certbin[0], certbin.size(),
                                   RSA_, SHA1, CERT, BASIC),
                 UnsupportedAlgorithm);
    EXPECT_THROW(crypto.createAsym(&certbin[0], certbin.size(),
                                   RSA_, SHA1, CERT, DNS),
                 UnsupportedAlgorithm);
    EXPECT_THROW(crypto.createAsym(&certbin[0], certbin.size(),
                                   RSA_, MD5, CERT, ASN1),
                 BadKey);
    EXPECT_THROW(crypto.createAsym(&certbin[0], certbin.size(),
                                   RSA_, SHA224, CERT, ASN1),
                 BadKey);
    EXPECT_THROW(crypto.createAsym(&certbin[0], certbin.size(),
                                   RSA_, SHA256, CERT, ASN1),
                 BadKey);
    EXPECT_THROW(crypto.createAsym(&certbin[0], certbin.size(),
                                   RSA_, SHA384, CERT, ASN1),
                 BadKey);
    EXPECT_THROW(crypto.createAsym(&certbin[0], certbin.size(),
                                   RSA_, SHA512, CERT, ASN1),
                 BadKey);

    certbin[certbin.size() - 1]  = ~certbin[certbin.size() - 1];
    boost::shared_ptr<Asym> bad_bin(crypto.createAsym(&certbin[0],
                                                      certbin.size(),
                                                      RSA_, SHA1,
                                                      CERT, ASN1),
                                    deleteAsym);
    EXPECT_FALSE(bad_bin.get()->validate());
}
