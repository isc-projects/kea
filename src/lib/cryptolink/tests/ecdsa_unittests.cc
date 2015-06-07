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

#include <config.h>

#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>

#include <boost/lexical_cast.hpp>

#include <gtest/gtest.h>

#include <util/encode/base64.h>

#include <hooks/hooks_manager.h>
#include <hooks/callout_handle.h>

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

#define P256_OBJ_ID \
0x06, 0x08, 0x2a, 0x86, 0x48, 0xce, 0x3d, 0x03, \
0x01, 0x07

#define P384_OBJ_ID \
0x06, 0x05, 0x2b, 0x81, 0x04, 0x00, 0x22

#define PRIVATE_KEY \
0xdc, 0x51, 0xd3, 0x86, 0x6a, 0x15, 0xba, 0xcd, \
0xe3, 0x3d, 0x96, 0xf9, 0x92, 0xfc, 0xa9, 0x9d, \
0xa7, 0xe6, 0xef, 0x09, 0x34, 0xe7, 0x09, 0x75, \
0x59, 0xc2, 0x7f, 0x16, 0x14, 0xc8, 0x8a, 0x7f

#define PUBLIC_KEY \
0x24, 0x42, 0xa5, 0xcc, 0x0e, 0xcd, 0x01, 0x5f, \
0xa3, 0xca, 0x31, 0xdc, 0x8e, 0x2b, 0xbc, 0x70, \
0xbf, 0x42, 0xd6, 0x0c, 0xbc, 0xa2, 0x00, 0x85, \
0xe0, 0x82, 0x2c, 0xb0, 0x42, 0x35, 0xe9, 0x70, \
0x6f, 0xc9, 0x8b, 0xd7, 0xe5, 0x02, 0x11, 0xa4, \
0xa2, 0x71, 0x02, 0xfa, 0x35, 0x49, 0xdf, 0x79, \
0xeb, 0xcb, 0x4b, 0xf2, 0x46, 0xb8, 0x09, 0x45, \
0xcd, 0xdf, 0xe7, 0xd5, 0x09, 0xbb, 0xfd, 0x7d

#define TBS_DATA \
0x61, 0x62, 0x63

#define SIGNATURE_R \
0xcb, 0x28, 0xe0, 0x99, 0x9b, 0x9c, 0x77, 0x15, \
0xfd, 0x0a, 0x80, 0xd8, 0xe4, 0x7a, 0x77, 0x07, \
0x97, 0x16, 0xcb, 0xbf, 0x91, 0x7d, 0xd7, 0x2e, \
0x97, 0x56, 0x6e, 0xa1, 0xc0, 0x66, 0x95, 0x7c

#define SIGNATURE_S \
0x86, 0xfa, 0x3b, 0xb4, 0xe2, 0x6c, 0xad, 0x5b, \
0xf9, 0x0b, 0x7f, 0x81, 0x89, 0x92, 0x56, 0xce, \
0x75, 0x94, 0xbb, 0x1e, 0xa0, 0xc8, 0x92, 0x12, \
0x74, 0x8b, 0xff, 0x3b, 0x3d, 0x5b, 0x03, 0x15

    /// @brief Public Key in SubjectPublicKeyInfo format
    const uint8_t pubspki[] = {
        0x30, // tag=SEQUENCE (SubjectPublicKeyInfo)
        0x59, // length=89
         0x30, // tag=SEQUENCE (algorithm : AlgorithmIdentifier)
          0x13, // length=19
          0x06, // tag=OBJECTID (algorithm)
          0x07, // length=7
           0x2a, 0x86, 0x48, 0xce, 0x3d, 0x02, 0x01, // id-ecPublicKey
          0x06, // tag=OBJECTID (namedCurve)
          0x08, // length=8
           0x2a, 0x86, 0x48, 0xce, 0x3d, 0x03, 0x01, 0x07, // X9_62_prime256v1
         0x03, // tag=BIT STRING
        0x42, // length=66
         0x00, 0x04, PUBLIC_KEY
    };
    size_t pubspkilen = 91;

    /// @brief Public Key in DNSSEC format (length 132)
    const uint8_t pubdns[] = {
        PUBLIC_KEY
    };
    size_t pubdnslen = 64;

    /// @brief ASN.1 ECDSA Signature layout
    const uint8_t asn1sig[] = {
        0x30, // tag=SEQUENCE
        0x46, // length=70
         0x02, // tag=INTEGER
         0x21, // length=33
          0x00, SIGNATURE_R,
         0x02, // tag=INTEGER
         0x21, // length=33
        0x00, SIGNATURE_S
    };
    size_t asn1siglen = 72;

    /// @brief Public Key file (SubjectPublicKeyInfo in PEM)
    const std::string pubfile = TEST_DATA_SRCDIR "/ecpub.pem";

    /// @brief Private Key file (PKCS#8 in PEM, password '1234')
    const std::string privfile = TEST_DATA_SRCDIR "/ecpkcs8.pem";

    /// @brief Certificate file (X.509 Public Key Certificate in PEM)
    const std::string certfile = TEST_DATA_SRCDIR "/ecx509.pem";

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
    /// See @ref doEcDsaTest for parameters
    void doEcDsaTestDirect(const std::string& data,
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
        boost::shared_ptr<Asym> ecdsa_sign(crypto.createAsym(privfilename,
                                                             password,
                                                             asym_algorithm,
                                                             hash_algorithm,
                                                             PRIVATE,
                                                             ASN1),
                                           deleteAsym);
        ecdsa_sign->update(data_buf.getData(), data_buf.getLength());
        ecdsa_sign->sign(sig, sig_len, sig_format);

        // Check whether we can verify it ourselves
        boost::shared_ptr<Asym> ecdsa_verify(crypto.createAsym(pubfilename,
                                                               "",
                                                               asym_algorithm,
                                                               hash_algorithm,
                                                               PUBLIC,
                                                               ASN1),
                                             deleteAsym);
        ecdsa_verify->update(data_buf.getData(), data_buf.getLength());
        EXPECT_TRUE(ecdsa_verify->verify(sig.getData(),
                                         sig.getLength(),
                                         sig_format));

        // Check if the signature we expect can verify
        // (beware we can't compare signature as they are random)
        EXPECT_TRUE(ecdsa_verify->verify(expected_sig,
                                         sig_len,
                                         sig_format));

        // Change the length and check whether verification fails then
        // Relies on the fact the length is checked first
        EXPECT_FALSE(ecdsa_verify->verify(sig.getData(),
                                          sig.getLength() - 1,
                                          sig_format));
        EXPECT_FALSE(ecdsa_verify->verify(sig.getData(),
                                          sig.getLength() + 1,
                                          sig_format));

        // Change the sig by flipping the first octet, and check
        // whether verification fails then
        sig.writeUint8At(~sig[0], 0);
        EXPECT_FALSE(ecdsa_verify->verify(sig.getData(),
                                          sig.getLength(),
                                          sig_format));
    }

    /// @brief Sign and verify with vector representation of signature
    /// cryptography object
    /// See @ref doEcDsaTest for parameters
    void doEcDsaTestVector(const std::string& data,
                           const std::string& privfilename,
                           const std::string& password,
                           const std::string& pubfilename,
                           const AsymAlgorithm asym_algorithm,
                           const HashAlgorithm hash_algorithm,
                           const AsymFormat sig_format,
                           const uint8_t* expected_sig,
                           size_t sig_len) {
        CryptoLink& crypto = CryptoLink::getCryptoLink();
        boost::shared_ptr<Asym> ecdsa_sign(crypto.createAsym(privfilename,
                                                             password,
                                                             asym_algorithm,
                                                             hash_algorithm,
                                                             PRIVATE,
                                                             ASN1),
                                           deleteAsym);
        ecdsa_sign->update(data.c_str(), data.size());
        std::vector<uint8_t> sig = ecdsa_sign->sign(sig_len, sig_format);
        ASSERT_EQ(sig_len, sig.size());

        boost::shared_ptr<Asym> ecdsa_verify(crypto.createAsym(pubfilename,
                                                               "",
                                                               asym_algorithm,
                                                               hash_algorithm,
                                                               PUBLIC,
                                                               ASN1),
                                             deleteAsym);
        ecdsa_verify->update(data.c_str(), data.size());
        EXPECT_TRUE(ecdsa_verify->verify(&sig[0], sig.size(), sig_format));

        EXPECT_TRUE(ecdsa_verify->verify(expected_sig,
                                         sig_len,
                                         sig_format));

        EXPECT_FALSE(ecdsa_verify->verify(&sig[0],
                                          sig.size() - 1,
                                          sig_format));
        EXPECT_FALSE(ecdsa_verify->verify(&sig[0],
                                          sig.size() + 1,
                                          sig_format));

        sig[0] = ~sig[0];
        EXPECT_FALSE(ecdsa_verify->verify(&sig[0], sig.size(), sig_format));
    }

    /// @brief Sign and verify with array representation of signature
    /// cryptography object
    /// See @ref doEcDsaTest for parameters
    void doEcDsaTestArray(const std::string& data,
                          const std::string& privfilename,
                          const std::string& password,
                          const std::string& pubfilename,
                          const AsymAlgorithm asym_algorithm,
                          const HashAlgorithm hash_algorithm,
                          const AsymFormat sig_format,
                          const uint8_t* expected_sig,
                          size_t sig_len) {
        CryptoLink& crypto = CryptoLink::getCryptoLink();
        boost::shared_ptr<Asym> ecdsa_sign(crypto.createAsym(privfilename,
                                                             password,
                                                             asym_algorithm,
                                                             hash_algorithm,
                                                             PRIVATE,
                                                             ASN1),
                                           deleteAsym);
        ecdsa_sign->update(data.c_str(), data.size());

        // note: this is not exception-safe, and can leak, but
        // if there is an unexpected exception in the code below we
        // have more important things to fix.
        uint8_t* sig = new uint8_t[sig_len];

        ecdsa_sign->sign(sig, sig_len, sig_format);

        boost::shared_ptr<Asym> ecdsa_verify(crypto.createAsym(pubfilename,
                                                               "",
                                                               asym_algorithm,
                                                               hash_algorithm,
                                                               PUBLIC,
                                                               ASN1),
                                             deleteAsym);
        ecdsa_verify->update(data.c_str(), data.size());
        EXPECT_TRUE(ecdsa_verify->verify(sig, sig_len, sig_format));

        EXPECT_TRUE(ecdsa_verify->verify(expected_sig, sig_len, sig_format));

        EXPECT_FALSE(ecdsa_verify->verify(sig, sig_len - 1, sig_format));
        EXPECT_FALSE(ecdsa_verify->verify(sig, sig_len + 1, sig_format));

        sig[0] = ~sig[0];
        EXPECT_FALSE(ecdsa_verify->verify(sig, sig_len, sig_format));

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
    void doEcDsaTest(const std::string& data,
                     const std::string& privfilename,
                     const std::string& password,
                     const std::string& pubfilename,
                     const AsymAlgorithm asym_algorithm,
                     const HashAlgorithm hash_algorithm,
                     const AsymFormat sig_format,
                     const uint8_t* expected_sig,
                     size_t sig_len) {
        doEcDsaTestDirect(data, privfilename, password, pubfilename,
                          asym_algorithm, hash_algorithm, sig_format,
                          expected_sig, sig_len);
        doEcDsaTestVector(data, privfilename, password, pubfilename,
                          asym_algorithm, hash_algorithm, sig_format,
                          expected_sig, sig_len);
        doEcDsaTestArray(data, privfilename, password, pubfilename,
                         asym_algorithm, hash_algorithm, sig_format,
                         expected_sig, sig_len);
    }
}

//
// Test values
//
TEST(EcDSATest, SHA256) {
    uint8_t privkey[] = {
        PRIVATE_KEY
    };
    size_t privkeylen = 32;
    uint8_t pubkey[] = {
        PUBLIC_KEY
    };
    size_t pubkeylen = 64;
    uint8_t data[] = {
        TBS_DATA
    };
    size_t datalen = 3;
    uint8_t sig[] = {
        SIGNATURE_R,
        SIGNATURE_S
    };
    size_t siglen = 64;
    CryptoLink& crypto = CryptoLink::getCryptoLink();
    boost::shared_ptr<Asym> ecdsa_sign(crypto.createAsym(privkey,
                                                         privkeylen,
                                                         ECDSA_,
                                                         SHA256,
                                                         PRIVATE,
                                                         BASIC),
                                       deleteAsym);
    ASSERT_TRUE(ecdsa_sign);
    EXPECT_EQ(ECDSA_, ecdsa_sign->getAsymAlgorithm());
    EXPECT_EQ(SHA256, ecdsa_sign->getHashAlgorithm());
    EXPECT_EQ(PRIVATE, ecdsa_sign->getAsymKeyKind());
    EXPECT_EQ(256, ecdsa_sign->getKeySize());
    EXPECT_EQ(64, ecdsa_sign->getSignatureLength(BASIC));
    EXPECT_EQ(72, ecdsa_sign->getSignatureLength(ASN1));
    EXPECT_EQ(64, ecdsa_sign->getSignatureLength(DNS));

    std::vector<uint8_t> basicprivkey = ecdsa_sign->exportkey(PRIVATE, BASIC);
    ASSERT_EQ(32, basicprivkey.size());
    EXPECT_TRUE(std::memcmp(privkey, &basicprivkey[0], privkeylen) == 0);
    std::vector<uint8_t> ans1pubkey = ecdsa_sign->exportkey(PUBLIC, ASN1);
    ASSERT_EQ(pubspkilen, ans1pubkey.size());
    EXPECT_TRUE(std::memcmp(pubspki, &ans1pubkey[0], pubspkilen) == 0);
    std::vector<uint8_t> dnspubkey = ecdsa_sign->exportkey(PUBLIC, DNS);
    ASSERT_EQ(64, dnspubkey.size());
    EXPECT_TRUE(std::memcmp(pubkey, &dnspubkey[0], pubkeylen) == 0);

    ecdsa_sign->update(data, datalen);
    OutputBuffer nsig(1);
    size_t nsig_len = ecdsa_sign->getSignatureLength(BASIC);
    ecdsa_sign->sign(nsig, nsig_len, BASIC);

    boost::shared_ptr<Asym> ecdsa_verify(crypto.createAsym(pubkey,
                                                           pubkeylen,
                                                           ECDSA_,
                                                           SHA256,
                                                           PUBLIC,
                                                           DNS),
                                         deleteAsym);
    ASSERT_TRUE(ecdsa_verify);

    ecdsa_verify->update(data, datalen);
    EXPECT_TRUE(ecdsa_verify->verify(nsig.getData(), nsig.getLength(), BASIC));

    EXPECT_TRUE(ecdsa_verify->verify(sig, siglen, DNS));

    EXPECT_TRUE(ecdsa_verify->verify(asn1sig, asn1siglen, ASN1));
}

//
// Multiple signatures
//
TEST(EcDsaTest, doubleSign) {
    std::string data = "Kea provides DHCPv4 and DHCPv6 servers";
    OutputBuffer data_buf(data.size());
    data_buf.writeData(data.c_str(), data.size());
    CryptoLink& crypto = CryptoLink::getCryptoLink();

    // Sign it
    boost::shared_ptr<Asym> ecdsa_sign(crypto.createAsym(privfile, "1234",
                                                         ECDSA_, SHA256,
                                                         PRIVATE, ASN1),
                                       deleteAsym);
    ASSERT_TRUE(ecdsa_sign);

    OutputBuffer sig1(1);
    size_t sig1_len = ecdsa_sign->getSignatureLength(BASIC);
    EXPECT_EQ(64, sig1_len);
    ecdsa_sign->update(data_buf.getData(), data_buf.getLength());
    ecdsa_sign->sign(sig1, sig1_len, BASIC);
    ASSERT_EQ(sig1_len, sig1.getLength());

    // Clear state
    ecdsa_sign->clear();

    // Sign it again
    OutputBuffer sig2(1);
    size_t sig2_len = ecdsa_sign->getSignatureLength(BASIC);
    EXPECT_EQ(64, sig2_len);
    ecdsa_sign->update(data_buf.getData(), data_buf.getLength());
    ecdsa_sign->sign(sig2, sig2_len, BASIC);
    EXPECT_EQ(sig2_len, sig2.getLength());

    // Compare
    ASSERT_EQ(sig1_len, sig2_len);

    // Verify
    boost::shared_ptr<Asym> ecdsa_verify(crypto.createAsym(pubfile, "",
                                                           ECDSA_, SHA256,
                                                           PUBLIC, ASN1),
                                         deleteAsym);
    ASSERT_TRUE(ecdsa_verify);

    ecdsa_verify->update(data_buf.getData(), data_buf.getLength());
    EXPECT_TRUE(ecdsa_verify->verify(sig1.getData(), sig1.getLength(), BASIC));
    EXPECT_TRUE(ecdsa_verify->verify(sig2.getData(), sig2.getLength(), BASIC));

}

//
// Multiple verifies
//
TEST(EcdsaTest, doubleVerify) {
    std::string data = "Kea provides DHCPv4 and DHCPv6 servers";
    OutputBuffer data_buf(data.size());
    data_buf.writeData(data.c_str(), data.size());
    CryptoLink& crypto = CryptoLink::getCryptoLink();

    // Sign it
    boost::shared_ptr<Asym> ecdsa_sign(crypto.createAsym(privfile, "1234",
                                                         ECDSA_, SHA256,
                                                         PRIVATE, ASN1),
                                       deleteAsym);
    ASSERT_TRUE(ecdsa_sign);

    OutputBuffer sig(1);
    size_t sig_len = ecdsa_sign->getSignatureLength(BASIC);
    EXPECT_EQ(64, sig_len);
    ecdsa_sign->update(data_buf.getData(), data_buf.getLength());
    ecdsa_sign->sign(sig, sig_len, BASIC);
    EXPECT_EQ(sig_len, sig.getLength());

    // Verify
    boost::shared_ptr<Asym> ecdsa_verify(crypto.createAsym(pubfile, "",
                                                           ECDSA_, SHA256,
                                                           PUBLIC, ASN1),
                                         deleteAsym);
    ASSERT_TRUE(ecdsa_verify);

    ecdsa_verify->update(data_buf.getData(), data_buf.getLength());
    EXPECT_TRUE(ecdsa_verify->verify(sig.getData(), sig.getLength(), BASIC));

    // Clear state
    ecdsa_verify->clear();

    // Verify again
    ecdsa_verify->update(data_buf.getData(), data_buf.getLength());
    EXPECT_TRUE(ecdsa_verify->verify(sig.getData(), sig.getLength(), BASIC));
}
