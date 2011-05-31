// Copyright (C) 2011  Internet Systems Consortium, Inc. ("ISC")
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
#include <gtest/gtest.h>

#include <cryptolink/cryptolink.h>
#include <cryptolink/crypto_hmac.h>

#include <util/buffer.h>
#include <exceptions/exceptions.h>

#include <boost/shared_ptr.hpp>

using namespace isc::util;
using namespace isc::cryptolink;

namespace {
    void checkData(const uint8_t* data, const uint8_t* expected,
                   size_t len) {
        for (size_t i = 0; i < len; ++i) {
            ASSERT_EQ(expected[i], data[i]);
        }
    }

    void checkBuffer(const OutputBuffer& buf, const uint8_t* expected,
                     size_t len)
    {
        ASSERT_EQ(len, buf.getLength());
        checkData(static_cast<const uint8_t*>(buf.getData()), expected,
                  len);
    }

    // Sign and verify with the convenience functions
    void doHMACTestConv(const std::string& data,
                        const void* secret,
                        size_t secret_len,
                        const HashAlgorithm hash_algorithm,
                        const uint8_t* expected_hmac,
                        size_t hmac_len) {
        OutputBuffer data_buf(data.size());
        data_buf.writeData(data.c_str(), data.size());
        OutputBuffer hmac_sig(0);

        // Sign it
        signHMAC(data_buf.getData(), data_buf.getLength(),
                 secret, secret_len, hash_algorithm, hmac_sig, hmac_len);

        // Check if the signature is what we expect
        checkBuffer(hmac_sig, expected_hmac, hmac_len);

        // Check whether we can verify it ourselves
        EXPECT_TRUE(verifyHMAC(data_buf.getData(), data_buf.getLength(),
                               secret, secret_len, hash_algorithm,
                               hmac_sig.getData(),
                               hmac_sig.getLength()));

        // Change the sig by flipping the first octet, and check
        // whether verification fails then
        hmac_sig.writeUint8At(~hmac_sig[0], 0);
        EXPECT_FALSE(verifyHMAC(data_buf.getData(), data_buf.getLength(),
                               secret, secret_len, hash_algorithm,
                               hmac_sig.getData(),
                               hmac_sig.getLength()));
    }

    // Sign and verify with an instantiation of an HMAC object
    void doHMACTestDirect(const std::string& data,
                          const void* secret,
                          size_t secret_len,
                          const HashAlgorithm hash_algorithm,
                          const uint8_t* expected_hmac,
                          size_t hmac_len) {
        OutputBuffer data_buf(data.size());
        data_buf.writeData(data.c_str(), data.size());
        OutputBuffer hmac_sig(1);
        CryptoLink& crypto = CryptoLink::getCryptoLink();

        // Sign it
        boost::shared_ptr<HMAC> hmac_sign(crypto.createHMAC(secret,
                                                            secret_len,
                                                            hash_algorithm),
                                          deleteHMAC);
        hmac_sign->update(data_buf.getData(), data_buf.getLength());
        hmac_sign->sign(hmac_sig, hmac_len);

        // Check if the signature is what we expect
        checkBuffer(hmac_sig, expected_hmac, hmac_len);

        // Check whether we can verify it ourselves
        boost::shared_ptr<HMAC> hmac_verify(crypto.createHMAC(secret,
                                                              secret_len,
                                                              hash_algorithm),
                                            deleteHMAC);
        hmac_verify->update(data_buf.getData(), data_buf.getLength());
        EXPECT_TRUE(hmac_verify->verify(hmac_sig.getData(),
                                        hmac_sig.getLength()));

        // Change the sig by flipping the first octet, and check
        // whether verification fails then
        hmac_sig.writeUint8At(~hmac_sig[0], 0);
        EXPECT_FALSE(hmac_verify->verify(hmac_sig.getData(),
                                         hmac_sig.getLength()));
    }

    void doHMACTestVector(const std::string& data,
                          const void* secret,
                          size_t secret_len,
                          const HashAlgorithm hash_algorithm,
                          const uint8_t* expected_hmac,
                          size_t hmac_len) {
        CryptoLink& crypto = CryptoLink::getCryptoLink();
        boost::shared_ptr<HMAC> hmac_sign(crypto.createHMAC(secret,
                                                            secret_len,
                                                            hash_algorithm),
                                          deleteHMAC);
        hmac_sign->update(data.c_str(), data.size());
        std::vector<uint8_t> sig = hmac_sign->sign(hmac_len);
        ASSERT_EQ(hmac_len, sig.size());
        checkData(&sig[0], expected_hmac, hmac_len);

        boost::shared_ptr<HMAC> hmac_verify(crypto.createHMAC(secret,
                                                              secret_len,
                                                              hash_algorithm),
                                            deleteHMAC);
        hmac_verify->update(data.c_str(), data.size());
        EXPECT_TRUE(hmac_verify->verify(&sig[0], sig.size()));

        sig[0] = ~sig[0];
        EXPECT_FALSE(hmac_verify->verify(&sig[0], sig.size()));
    }

    void doHMACTestArray(const std::string& data,
                         const void* secret,
                         size_t secret_len,
                         const HashAlgorithm hash_algorithm,
                         const uint8_t* expected_hmac,
                         size_t hmac_len) {
        CryptoLink& crypto = CryptoLink::getCryptoLink();
        boost::shared_ptr<HMAC> hmac_sign(crypto.createHMAC(secret,
                                                            secret_len,
                                                            hash_algorithm),
                                          deleteHMAC);
        hmac_sign->update(data.c_str(), data.size());

        // note: this is not exception-safe, and can leak, but
        // if there is an unexpected exception in the code below we
        // have more important things to fix.
        uint8_t* sig = new uint8_t[hmac_len];

        hmac_sign->sign(sig, hmac_len);
        checkData(sig, expected_hmac, hmac_len);

        boost::shared_ptr<HMAC> hmac_verify(crypto.createHMAC(secret,
                                                              secret_len,
                                                              hash_algorithm),
                                            deleteHMAC);
        hmac_verify->update(data.c_str(), data.size());
        EXPECT_TRUE(hmac_verify->verify(sig, hmac_len));

        sig[0] = ~sig[0];
        EXPECT_FALSE(hmac_verify->verify(sig, hmac_len));

        delete[] sig;
    }

    void doHMACTest(const std::string& data,
                    const void* secret,
                    size_t secret_len,
                    const HashAlgorithm hash_algorithm,
                    const uint8_t* expected_hmac,
                    size_t hmac_len) {
        doHMACTestConv(data, secret, secret_len, hash_algorithm,
                       expected_hmac, hmac_len);
        doHMACTestDirect(data, secret, secret_len, hash_algorithm,
                         expected_hmac, hmac_len);
        doHMACTestVector(data, secret, secret_len, hash_algorithm,
                         expected_hmac, hmac_len);
        doHMACTestArray(data, secret, secret_len, hash_algorithm,
                        expected_hmac, hmac_len);
    }
}

//
// Test values taken from RFC 2202
//
TEST(CryptoLinkTest, HMAC_MD5_RFC2202_SIGN) {
    const uint8_t secret[] = { 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b,
                               0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b,
                               0x0b, 0x0b };
    const uint8_t hmac_expected[] = { 0x92, 0x94, 0x72, 0x7a, 0x36,
                                      0x38, 0xbb, 0x1c, 0x13, 0xf4,
                                      0x8e, 0xf8, 0x15, 0x8b, 0xfc,
                                      0x9d };
    doHMACTest("Hi There", secret, 16, MD5, hmac_expected, 16);

    const uint8_t hmac_expected2[] = { 0x75, 0x0c, 0x78, 0x3e, 0x6a,
                                       0xb0, 0xb5, 0x03, 0xea, 0xa8,
                                       0x6e, 0x31, 0x0a, 0x5d, 0xb7,
                                       0x38 };
    doHMACTest("what do ya want for nothing?", "Jefe", 4, MD5,
               hmac_expected2, 16);

    const uint8_t secret3[] = { 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,
                                0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,
                                0xaa, 0xaa, 0xaa, 0xaa };
    const uint8_t hmac_expected3[] = { 0x56, 0xbe, 0x34, 0x52, 0x1d,
                                       0x14, 0x4c, 0x88, 0xdb, 0xb8,
                                       0xc7, 0x33, 0xf0, 0xe8, 0xb3,
                                       0xf6};
    doHMACTest(std::string(50, 0xdd), secret3, 16, MD5, hmac_expected3, 16);

    const std::string data4(50, 0xcd);
    const uint8_t secret4[] = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06,
                                0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c,
                                0x0d, 0x0e, 0x0f, 0x10, 0x11, 0x12,
                                0x13, 0x14, 0x15, 0x16, 0x17, 0x18,
                                0x19 };
    const uint8_t hmac_expected4[] = { 0x69, 0x7e, 0xaf, 0x0a, 0xca,
                                       0x3a, 0x3a, 0xea, 0x3a, 0x75,
                                       0x16, 0x47, 0x46, 0xff, 0xaa,
                                       0x79 };
    doHMACTest(data4, secret4, 25, MD5, hmac_expected4, 16);

    const uint8_t hmac_expected6[] = { 0x6b, 0x1a, 0xb7, 0xfe, 0x4b,
                                       0xd7, 0xbf, 0x8f, 0x0b, 0x62,
                                       0xe6, 0xce, 0x61, 0xb9, 0xd0,
                                       0xcd };
    doHMACTest("Test Using Larger Than Block-Size Key - Hash Key First",
               std::string(80, 0xaa).c_str(), 80, MD5, hmac_expected6, 16);

    const uint8_t hmac_expected7[] = { 0x6f, 0x63, 0x0f, 0xad, 0x67,
                                       0xcd, 0xa0, 0xee, 0x1f, 0xb1,
                                       0xf5, 0x62, 0xdb, 0x3a, 0xa5,
                                       0x3e };
    doHMACTest("Test Using Larger Than Block-Size Key and Larger Than "
               "One Block-Size Data",
               std::string(80, 0xaa).c_str(), 80, MD5, hmac_expected7, 16);
}

// Temporarily disabled
TEST(CryptoLinkTest, DISABLED_HMAC_MD5_RFC2202_SIGN_TRUNCATED) {
    const uint8_t secret5[] = { 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c,
                                0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c,
                                0x0c, 0x0c, 0x0c, 0x0c };
    const uint8_t hmac_expected5[] = { 0x56, 0x46, 0x1e, 0xf2, 0x34,
                                       0x2e, 0xdc, 0x00, 0xf9, 0xba,
                                       0xb9, 0x95, 0x69, 0x0e, 0xfd,
                                       0x4c };
    doHMACTest("Test With Truncation", secret5, 16, MD5,
               hmac_expected5, 16);
    doHMACTest("Test With Truncation", secret5, 16, MD5,
               hmac_expected5, 12);
}

//
// Test values taken from RFC 2202
//
TEST(CryptoLinkTest, HMAC_SHA1_RFC2202_SIGN) {
    const uint8_t secret[] = { 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b,
                               0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b,
                               0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b };
    const uint8_t hmac_expected[] = { 0xb6, 0x17, 0x31, 0x86, 0x55,
                                      0x05, 0x72, 0x64, 0xe2, 0x8b,
                                      0xc0, 0xb6, 0xfb, 0x37, 0x8c,
                                      0x8e, 0xf1, 0x46, 0xbe, 0x00 };
    doHMACTest("Hi There", secret, 20, SHA1, hmac_expected, 20);

    const uint8_t hmac_expected2[] = { 0xef, 0xfc, 0xdf, 0x6a, 0xe5,
                                       0xeb, 0x2f, 0xa2, 0xd2, 0x74,
                                       0x16, 0xd5, 0xf1, 0x84, 0xdf,
                                       0x9c, 0x25, 0x9a, 0x7c, 0x79 };
    doHMACTest("what do ya want for nothing?", "Jefe", 4, SHA1,
               hmac_expected2, 20);

    const uint8_t secret3[] = { 0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,
                                0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,
                                0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,
                                0xaa, 0xaa };
    const uint8_t hmac_expected3[] = { 0x12, 0x5d, 0x73, 0x42, 0xb9,
                                       0xac, 0x11, 0xcd, 0x91, 0xa3,
                                       0x9a, 0xf4, 0x8a, 0xa1, 0x7b,
                                       0x4f, 0x63, 0xf1, 0x75, 0xd3 };
    doHMACTest(std::string(50, 0xdd), secret3, 20, SHA1, hmac_expected3, 20);

    const uint8_t secret4[] = { 0x01, 0x02, 0x03, 0x04, 0x05, 0x06,
                                0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c,
                                0x0d, 0x0e, 0x0f, 0x10, 0x11, 0x12,
                                0x13, 0x14, 0x15, 0x16, 0x17, 0x18,
                                0x19 };
    const uint8_t hmac_expected4[] = { 0x4c, 0x90, 0x07, 0xf4, 0x02,
                                       0x62, 0x50, 0xc6, 0xbc, 0x84,
                                       0x14, 0xf9, 0xbf, 0x50, 0xc8,
                                       0x6c, 0x2d, 0x72, 0x35, 0xda };
    doHMACTest(std::string(50, 0xcd), secret4, 25, SHA1, hmac_expected4, 20);

    const uint8_t hmac_expected6[] = { 0xaa, 0x4a, 0xe5, 0xe1, 0x52,
                                       0x72, 0xd0, 0x0e, 0x95, 0x70,
                                       0x56, 0x37, 0xce, 0x8a, 0x3b,
                                       0x55, 0xed, 0x40, 0x21, 0x12 };
    doHMACTest("Test Using Larger Than Block-Size Key - Hash Key First",
               std::string(80, 0xaa).c_str(), 80, SHA1, hmac_expected6, 20);

    const uint8_t hmac_expected7[] = { 0xe8, 0xe9, 0x9d, 0x0f, 0x45,
                                       0x23, 0x7d, 0x78, 0x6d, 0x6b,
                                       0xba, 0xa7, 0x96, 0x5c, 0x78,
                                       0x08, 0xbb, 0xff, 0x1a, 0x91 };
    doHMACTest("Test Using Larger Than Block-Size Key and Larger Than "
               "One Block-Size Data",
               std::string(80, 0xaa).c_str(), 80, SHA1, hmac_expected7, 20);
}

// Temporarily disabled
TEST(CryptoLinkTest, DISABLED_HMAC_SHA1_RFC2202_SIGN_TRUNCATED) {
    const uint8_t secret5[] = { 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c,
                                0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c,
                                0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c,
                                0x0c, 0x0c };
    const uint8_t hmac_expected5[] = { 0x4c, 0x1a, 0x03, 0x42, 0x4b,
                                       0x55, 0xe0, 0x7f, 0xe7, 0xf2,
                                       0x7b, 0xe1, 0xd5, 0x8b, 0xb9,
                                       0x32, 0x4a, 0x9a, 0x5a, 0x04 };
    doHMACTest("Test With Truncation", secret5, 20, SHA1,
               hmac_expected5, 20);
    doHMACTest("Test With Truncation", secret5, 20, SHA1,
               hmac_expected5, 12);
}

//
// Test values taken from RFC 4231
//
//
//  Test data from RFC4231, including secret key
//  and source data, they are common for sha224/256/384/512
//  so put them together in seperate space
namespace {
    static const uint8_t secret1[] = { 
        0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 
        0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b,
        0x0b, 0x0b, 0x0b, 0x0b, 0x0b, 0x0b 
    };

    static const uint8_t secret2[] = "Jefe";
    static const uint8_t secret3[] = { 
        0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,
        0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,
        0xaa, 0xaa, 0xaa, 0xaa, 0xaa, 0xaa,
        0xaa, 0xaa 
    };
    static  const uint8_t secret4[] = { 
        0x01, 0x02, 0x03, 0x04, 0x05, 0x06,
        0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c,
        0x0d, 0x0e, 0x0f, 0x10, 0x11, 0x12,
        0x13, 0x14, 0x15, 0x16, 0x17, 0x18,
        0x19 
    };
    static const uint8_t secret5[] = { 
        0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c,
        0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c,
        0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c,
        0x0c, 0x0c 
    };

    static uint8_t secret6[131]; 
    static uint8_t secret7[131]; 

    static const std::string data1("Hi There");
    static const std::string data2("what do ya want for nothing?");
    static const std::string data3(std::string(50, 0xdd));
    static const std::string data4(std::string(50, 0xcd));
    static const std::string data5("Test With Truncation");
    static const std::string data6("Test Using Larger Than Block-Size Key - Hash Key First");
    static const std::string data7("This is a test using a larger than block-size key and a"
            " larger than block-size data. The key needs to be hashe"
            "d before being used by the HMAC algorithm.");
#define SECRECT(n) secret##n
#define DATA(n) data##n
#define HMAC_EXPECTED(n) hmac_expected##n

#define RUN_NTH_TEST_CASE_FOR_ALG(index, hash_algorithm) do {\
                doHMACTest(DATA(index), \
                           SECRECT(index), sizeof(SECRECT(index)), \
                           (hash_algorithm), HMAC_EXPECTED(index), \
                           sizeof(HMAC_EXPECTED(index)));\
            }while(0)

#define RUN_TEST_CASES_FOR_ALG(alg) do {\
        memcpy(secret6, std::string(131, 0xaa).c_str(), 131); \
        memcpy(secret7, std::string(131, 0xaa).c_str(), 131); \
        RUN_NTH_TEST_CASE_FOR_ALG(1, alg); \
        RUN_NTH_TEST_CASE_FOR_ALG(2, alg); \
        RUN_NTH_TEST_CASE_FOR_ALG(3, alg); \
        RUN_NTH_TEST_CASE_FOR_ALG(4, alg); \
        RUN_NTH_TEST_CASE_FOR_ALG(5, alg); \
        RUN_NTH_TEST_CASE_FOR_ALG(6, alg); \
        RUN_NTH_TEST_CASE_FOR_ALG(7, alg); \
    }while(0)


};

TEST(CryptoLinkTest, HMAC_SHA256_RFC4231_SIGN) {
    const uint8_t hmac_expected1[] = { 0xb0, 0x34, 0x4c, 0x61, 0xd8,
                                      0xdb, 0x38, 0x53, 0x5c, 0xa8,
                                      0xaf, 0xce, 0xaf, 0x0b, 0xf1,
                                      0x2b, 0x88, 0x1d, 0xc2, 0x00,
                                      0xc9, 0x83, 0x3d, 0xa7, 0x26,
                                      0xe9, 0x37, 0x6c, 0x2e, 0x32,
                                      0xcf, 0xf7 };
    const uint8_t hmac_expected2[] = { 0x5b, 0xdc, 0xc1, 0x46, 0xbf,
                                       0x60, 0x75, 0x4e, 0x6a, 0x04,
                                       0x24, 0x26, 0x08, 0x95, 0x75,
                                       0xc7, 0x5a, 0x00, 0x3f, 0x08,
                                       0x9d, 0x27, 0x39, 0x83, 0x9d,
                                       0xec, 0x58, 0xb9, 0x64, 0xec,
                                       0x38, 0x43 };
    const uint8_t hmac_expected3[] = { 0x77, 0x3e, 0xa9, 0x1e, 0x36,
                                       0x80, 0x0e, 0x46, 0x85, 0x4d,
                                       0xb8, 0xeb, 0xd0, 0x91, 0x81,
                                       0xa7, 0x29, 0x59, 0x09, 0x8b,
                                       0x3e, 0xf8, 0xc1, 0x22, 0xd9,
                                       0x63, 0x55, 0x14, 0xce, 0xd5,
                                       0x65, 0xfe };
    const uint8_t hmac_expected4[] = { 0x82, 0x55, 0x8a, 0x38, 0x9a,
                                       0x44, 0x3c, 0x0e, 0xa4, 0xcc,
                                       0x81, 0x98, 0x99, 0xf2, 0x08,
                                       0x3a, 0x85, 0xf0, 0xfa, 0xa3,
                                       0xe5, 0x78, 0xf8, 0x07, 0x7a,
                                       0x2e, 0x3f, 0xf4, 0x67, 0x29,
                                       0x66, 0x5b };
//    const uint8_t hmac_expected5[] = { 0xa3, 0xb6, 0x16, 0x74, 0x73,
//                                       0x10, 0x0e, 0xe0, 0x6e, 0x0c,
//                                       0x79, 0x6c, 0x29, 0x55, 0x55,
//                                       0x2b };
    const uint8_t hmac_expected6[] = { 0x60, 0xe4, 0x31, 0x59, 0x1e,
                                       0xe0, 0xb6, 0x7f, 0x0d, 0x8a,
                                       0x26, 0xaa, 0xcb, 0xf5, 0xb7,
                                       0x7f, 0x8e, 0x0b, 0xc6, 0x21,
                                       0x37, 0x28, 0xc5, 0x14, 0x05,
                                       0x46, 0x04, 0x0f, 0x0e, 0xe3,
                                       0x7f, 0x54 };
    const uint8_t hmac_expected7[] = { 0x9b, 0x09, 0xff, 0xa7, 0x1b,
                                       0x94, 0x2f, 0xcb, 0x27, 0x63,
                                       0x5f, 0xbc, 0xd5, 0xb0, 0xe9,
                                       0x44, 0xbf, 0xdc, 0x63, 0x64,
                                       0x4f, 0x07, 0x13, 0x93, 0x8a,
                                       0x7f, 0x51, 0x53, 0x5c, 0x3a,
                                       0x35, 0xe2 };

    memcpy(secret6, std::string(131, 0xaa).c_str(), 131); 
    memcpy(secret7, std::string(131, 0xaa).c_str(), 131); 
    RUN_NTH_TEST_CASE_FOR_ALG(1, SHA256); 
    RUN_NTH_TEST_CASE_FOR_ALG(2, SHA256); 
    RUN_NTH_TEST_CASE_FOR_ALG(3, SHA256);
    RUN_NTH_TEST_CASE_FOR_ALG(4, SHA256); 
    RUN_NTH_TEST_CASE_FOR_ALG(6, SHA256); 
    RUN_NTH_TEST_CASE_FOR_ALG(7, SHA256); 
 
}


//
// Test values taken from RFC 4231, test optional algorithm 224,384,512
//
TEST(CryptoLinkTest, HMAC_SHA224_RFC4231_SIGN) {
    const uint8_t hmac_expected1[] = { 
        0x89,0x6f,0xb1,0x12,0x8a,0xbb,0xdf,0x19,0x68,0x32,0x10,0x7c,
        0xd4,0x9d,0xf3,0x3f,0x47,0xb4,0xb1,0x16,0x99,0x12,0xba,0x4f,
        0x53,0x68,0x4b,0x22
    };
    const uint8_t hmac_expected2[] = { 
        0xa3,0x0e,0x01,0x09,0x8b,0xc6,0xdb,0xbf,0x45,0x69,0x0f,0x3a,
        0x7e,0x9e,0x6d,0x0f,0x8b,0xbe,0xa2,0xa3,0x9e,0x61,0x48,0x00,
        0x8f,0xd0,0x5e,0x44
    };
 
    const uint8_t hmac_expected3[] = {
        0x7f,0xb3,0xcb,0x35,0x88,0xc6,0xc1,0xf6,0xff,0xa9,0x69,0x4d,
        0x7d,0x6a,0xd2,0x64,0x93,0x65,0xb0,0xc1,0xf6,0x5d,0x69,0xd1,
        0xec,0x83,0x33,0xea
    };

    const uint8_t hmac_expected4[] = {
        0x6c,0x11,0x50,0x68,0x74,0x01,0x3c,0xac,0x6a,0x2a,0xbc,0x1b,
        0xb3,0x82,0x62,0x7c,0xec,0x6a,0x90,0xd8,0x6e,0xfc,0x01,0x2d,
        0xe7,0xaf,0xec,0x5a
    };
 
//    const uint8_t hmac_expected5[] = {
//        0x0e,0x2a,0xea,0x68,0xa9,0x0c,0x8d,0x37,0xc9,0x88,0xbc,0xdb,0x9f,
//        0xca,0x6f,0xa8
//    };

    const uint8_t hmac_expected6[] = {
        0x95,0xe9,0xa0,0xdb,0x96,0x20,0x95,0xad,0xae,0xbe,0x9b,0x2d,0x6f,
        0x0d,0xbc,0xe2,0xd4,0x99,0xf1,0x12,0xf2,0xd2,0xb7,0x27,0x3f,0xa6,
        0x87,0x0e
    };

    const uint8_t hmac_expected7[] = {
        0x3a,0x85,0x41,0x66,0xac,0x5d,0x9f,0x02,0x3f,0x54,0xd5,0x17,0xd0,
        0xb3,0x9d,0xbd,0x94,0x67,0x70,0xdb,0x9c,0x2b,0x95,0xc9,0xf6,0xf5,
        0x65,0xd1
    };
 
    memcpy(secret6, std::string(131, 0xaa).c_str(), 131); 
    memcpy(secret7, std::string(131, 0xaa).c_str(), 131); 
    RUN_NTH_TEST_CASE_FOR_ALG(1, SHA224); 
    RUN_NTH_TEST_CASE_FOR_ALG(2, SHA224); 
    RUN_NTH_TEST_CASE_FOR_ALG(3, SHA224);
    RUN_NTH_TEST_CASE_FOR_ALG(4, SHA224); 
    RUN_NTH_TEST_CASE_FOR_ALG(6, SHA224); 
    RUN_NTH_TEST_CASE_FOR_ALG(7, SHA224); 
}

        
TEST(CryptoLinkTest, HMAC_SHA384_RFC4231_SIGN) {
    const uint8_t hmac_expected1[] = { 
        0xaf,0xd0,0x39,0x44,0xd8,0x48,0x95,0x62,0x6b,0x08,0x25,0xf4,
        0xab,0x46,0x90,0x7f,0x15,0xf9,0xda,0xdb,0xe4,0x10,0x1e,0xc6,
        0x82,0xaa,0x03,0x4c,0x7c,0xeb,0xc5,0x9c,0xfa,0xea,0x9e,0xa9,
        0x07,0x6e,0xde,0x7f,0x4a,0xf1,0x52,0xe8,0xb2,0xfa,0x9c,0xb6
    };

    const uint8_t hmac_expected2[] = {
        0xaf,0x45,0xd2,0xe3,0x76,0x48,0x40,0x31,0x61,0x7f,0x78,0xd2,
        0xb5,0x8a,0x6b,0x1b,0x9c,0x7e,0xf4,0x64,0xf5,0xa0,0x1b,0x47,
        0xe4,0x2e,0xc3,0x73,0x63,0x22,0x44,0x5e,0x8e,0x22,0x40,0xca,
        0x5e,0x69,0xe2,0xc7,0x8b,0x32,0x39,0xec,0xfa,0xb2,0x16,0x49
    };
 
    const uint8_t hmac_expected3[] = {
        0x88,0x06,0x26,0x08,0xd3,0xe6,0xad,0x8a,0x0a,0xa2,0xac,0xe0,
        0x14,0xc8,0xa8,0x6f,0x0a,0xa6,0x35,0xd9,0x47,0xac,0x9f,0xeb,
        0xe8,0x3e,0xf4,0xe5,0x59,0x66,0x14,0x4b,0x2a,0x5a,0xb3,0x9d,
        0xc1,0x38,0x14,0xb9,0x4e,0x3a,0xb6,0xe1,0x01,0xa3,0x4f,0x27
    };
 
    const uint8_t hmac_expected4[] = {
        0x3e,0x8a,0x69,0xb7,0x78,0x3c,0x25,0x85,0x19,0x33,0xab,0x62,
        0x90,0xaf,0x6c,0xa7,0x7a,0x99,0x81,0x48,0x08,0x50,0x00,0x9c,
        0xc5,0x57,0x7c,0x6e,0x1f,0x57,0x3b,0x4e,0x68,0x01,0xdd,0x23,
        0xc4,0xa7,0xd6,0x79,0xcc,0xf8,0xa3,0x86,0xc6,0x74,0xcf,0xfb,
    };
   
//    const uint8_t hmac_expected5[] = {
//        0x3a,0xbf,0x34,0xc3,0x50,0x3b,0x2a,0x23,0xa4,0x6e,0xfc,0x61,0x9b,
//        0xae,0xf8,0x97,
//   };
 
    const uint8_t hmac_expected6[] = {
        0x4e,0xce,0x08,0x44,0x85,0x81,0x3e,0x90,0x88,0xd2,0xc6,0x3a,0x04,
        0x1b,0xc5,0xb4,0x4f,0x9e,0xf1,0x01,0x2a,0x2b,0x58,0x8f,0x3c,0xd1,
        0x1f,0x05,0x03,0x3a,0xc4,0xc6,0x0c,0x2e,0xf6,0xab,0x40,0x30,0xfe,
        0x82,0x96,0x24,0x8d,0xf1,0x63,0xf4,0x49,0x52
    };
 
    const uint8_t hmac_expected7[] = {
        0x66,0x17,0x17,0x8e,0x94,0x1f,0x02,0x0d,0x35,0x1e,0x2f,0x25,0x4e,
        0x8f,0xd3,0x2c,0x60,0x24,0x20,0xfe,0xb0,0xb8,0xfb,0x9a,0xdc,0xce,
        0xbb,0x82,0x46,0x1e,0x99,0xc5,0xa6,0x78,0xcc,0x31,0xe7,0x99,0x17,
        0x6d,0x38,0x60,0xe6,0x11,0x0c,0x46,0x52,0x3e
    };
   
    memcpy(secret6, std::string(131, 0xaa).c_str(), 131); 
    memcpy(secret7, std::string(131, 0xaa).c_str(), 131); 
    RUN_NTH_TEST_CASE_FOR_ALG(1, SHA384); 
    RUN_NTH_TEST_CASE_FOR_ALG(2, SHA384); 
    RUN_NTH_TEST_CASE_FOR_ALG(3, SHA384);
    RUN_NTH_TEST_CASE_FOR_ALG(4, SHA384); 
    RUN_NTH_TEST_CASE_FOR_ALG(6, SHA384); 
    RUN_NTH_TEST_CASE_FOR_ALG(7, SHA384); 
}

TEST(CryptoLinkTest, HMAC_SHA512_RFC4231_SIGN) {
    const uint8_t hmac_expected1[] = { 
        0x87,0xaa,0x7c,0xde,0xa5,0xef,0x61,0x9d,0x4f,0xf0,0xb4,0x24,
        0x1a,0x1d,0x6c,0xb0,0x23,0x79,0xf4,0xe2,0xce,0x4e,0xc2,0x78,
        0x7a,0xd0,0xb3,0x05,0x45,0xe1,0x7c,0xde,0xda,0xa8,0x33,0xb7,
        0xd6,0xb8,0xa7,0x02,0x03,0x8b,0x27,0x4e,0xae,0xa3,0xf4,0xe4,
        0xbe,0x9d,0x91,0x4e,0xeb,0x61,0xf1,0x70,0x2e,0x69,0x6c,0x20,
        0x3a,0x12,0x68,0x54
    };
   const uint8_t hmac_expected2[] = {
        0x16,0x4b,0x7a,0x7b,0xfc,0xf8,0x19,0xe2,0xe3,0x95,0xfb,0xe7,
        0x3b,0x56,0xe0,0xa3,0x87,0xbd,0x64,0x22,0x2e,0x83,0x1f,0xd6,
        0x10,0x27,0x0c,0xd7,0xea,0x25,0x05,0x54,0x97,0x58,0xbf,0x75,
        0xc0,0x5a,0x99,0x4a,0x6d,0x03,0x4f,0x65,0xf8,0xf0,0xe6,0xfd,
        0xca,0xea,0xb1,0xa3,0x4d,0x4a,0x6b,0x4b,0x63,0x6e,0x07,0x0a,
        0x38,0xbc,0xe7,0x37
    }; 
 
   const uint8_t hmac_expected3[] = {
        0xfa,0x73,0xb0,0x08,0x9d,0x56,0xa2,0x84,0xef,0xb0,0xf0,0x75,
        0x6c,0x89,0x0b,0xe9,0xb1,0xb5,0xdb,0xdd,0x8e,0xe8,0x1a,0x36,
        0x55,0xf8,0x3e,0x33,0xb2,0x27,0x9d,0x39,0xbf,0x3e,0x84,0x82,
        0x79,0xa7,0x22,0xc8,0x06,0xb4,0x85,0xa4,0x7e,0x67,0xc8,0x07,
        0xb9,0x46,0xa3,0x37,0xbe,0xe8,0x94,0x26,0x74,0x27,0x88,0x59,
        0xe1,0x32,0x92,0xfb
    };

   const uint8_t hmac_expected4[] = {
        0xb0,0xba,0x46,0x56,0x37,0x45,0x8c,0x69,0x90,0xe5,0xa8,0xc5,
        0xf6,0x1d,0x4a,0xf7,0xe5,0x76,0xd9,0x7f,0xf9,0x4b,0x87,0x2d,
        0xe7,0x6f,0x80,0x50,0x36,0x1e,0xe3,0xdb,0xa9,0x1c,0xa5,0xc1,
        0x1a,0xa2,0x5e,0xb4,0xd6,0x79,0x27,0x5c,0xc5,0x78,0x80,0x63,
        0xa5,0xf1,0x97,0x41,0x12,0x0c,0x4f,0x2d,0xe2,0xad,0xeb,0xeb,
        0x10,0xa2,0x98,0xdd
    };
 
//    const uint8_t hmac_expected5[] = {
//        0x41,0x5f,0xad,0x62,0x71,0x58,0x0a,0x53,0x1d,0x41,0x79,0xbc,0x89,
//        0x1d,0x87,0xa6,
//    };
 
    const uint8_t hmac_expected6[] = {
        0x80,0xb2,0x42,0x63,0xc7,0xc1,0xa3,0xeb,0xb7,0x14,0x93,0xc1,0xdd,
        0x7b,0xe8,0xb4,0x9b,0x46,0xd1,0xf4,0x1b,0x4a,0xee,0xc1,0x12,0x1b,
        0x01,0x37,0x83,0xf8,0xf3,0x52,0x6b,0x56,0xd0,0x37,0xe0,0x5f,0x25,
        0x98,0xbd,0x0f,0xd2,0x21,0x5d,0x6a,0x1e,0x52,0x95,0xe6,0x4f,0x73,
        0xf6,0x3f,0x0a,0xec,0x8b,0x91,0x5a,0x98,0x5d,0x78,0x65,0x98
    };

    const uint8_t hmac_expected7[] = {
        0xe3,0x7b,0x6a,0x77,0x5d,0xc8,0x7d,0xba,0xa4,0xdf,0xa9,0xf9,0x6e,
        0x5e,0x3f,0xfd,0xde,0xbd,0x71,0xf8,0x86,0x72,0x89,0x86,0x5d,0xf5,
        0xa3,0x2d,0x20,0xcd,0xc9,0x44,0xb6,0x02,0x2c,0xac,0x3c,0x49,0x82,
        0xb1,0x0d,0x5e,0xeb,0x55,0xc3,0xe4,0xde,0x15,0x13,0x46,0x76,0xfb,
        0x6d,0xe0,0x44,0x60,0x65,0xc9,0x74,0x40,0xfa,0x8c,0x6a,0x58
    };
 
    memcpy(secret6, std::string(131, 0xaa).c_str(), 131); 
    memcpy(secret7, std::string(131, 0xaa).c_str(), 131); 
    RUN_NTH_TEST_CASE_FOR_ALG(1, SHA512); 
    RUN_NTH_TEST_CASE_FOR_ALG(2, SHA512); 
    RUN_NTH_TEST_CASE_FOR_ALG(3, SHA512);
    RUN_NTH_TEST_CASE_FOR_ALG(4, SHA512); 
    RUN_NTH_TEST_CASE_FOR_ALG(6, SHA512); 
    RUN_NTH_TEST_CASE_FOR_ALG(7, SHA512); 
}

TEST(CryptoLinkTest, DISABLED_HMAC_SHA256_RFC2202_SIGN_TRUNCATED) {
    const uint8_t secret5[] = { 0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c,
                                0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c,
                                0x0c, 0x0c, 0x0c, 0x0c, 0x0c, 0x0c,
                                0x0c, 0x0c };
    const uint8_t hmac_expected5[] = { 0xa3, 0xb6, 0x16, 0x74, 0x73,
                                       0x10, 0x0e, 0xe0, 0x6e, 0x0c,
                                       0x79, 0x6c, 0x29, 0x55, 0x55,
                                       0x2b };
    doHMACTest("Test With Truncation", secret5, 20, SHA256,
               hmac_expected5, 16);
}

namespace {
    size_t
    sigVectorLength(HashAlgorithm alg, size_t len) {
        boost::shared_ptr<HMAC> hmac_sign(
            CryptoLink::getCryptoLink().createHMAC("asdf", 4, alg),
            deleteHMAC);
        hmac_sign->update("asdf", 4);
        const std::vector<uint8_t> sig = hmac_sign->sign(len);
        return (sig.size());
    }

    size_t
    sigBufferLength(HashAlgorithm alg, size_t len) {
        boost::shared_ptr<HMAC> hmac_sign(
            CryptoLink::getCryptoLink().createHMAC("asdf", 4, alg),
            deleteHMAC);
        hmac_sign->update("asdf", 4);
        OutputBuffer sig(0);
        hmac_sign->sign(sig, len);
        return (sig.getLength());
    }
}

TEST(CryptoLinkTest, HMACSigLengthArgument) {
    std::vector<uint8_t> sig;

    EXPECT_EQ(16, sigVectorLength(MD5, 0));
    EXPECT_EQ(8, sigVectorLength(MD5, 8));
    EXPECT_EQ(16, sigVectorLength(MD5, 16));
    EXPECT_EQ(16, sigVectorLength(MD5, 40));
    EXPECT_EQ(16, sigVectorLength(MD5, 2000));

    EXPECT_EQ(20, sigBufferLength(SHA1, 0));
    EXPECT_EQ(8, sigBufferLength(SHA1, 8));
    EXPECT_EQ(20, sigBufferLength(SHA1, 20));
    EXPECT_EQ(20, sigBufferLength(SHA1, 40));
    EXPECT_EQ(20, sigBufferLength(SHA1, 2000));

    EXPECT_EQ(32, sigBufferLength(SHA256, 0));
    EXPECT_EQ(8, sigBufferLength(SHA256, 8));
    EXPECT_EQ(32, sigBufferLength(SHA256, 32));
    EXPECT_EQ(32, sigBufferLength(SHA256, 40));
    EXPECT_EQ(32, sigBufferLength(SHA256, 3200));

    EXPECT_EQ(16, sigBufferLength(MD5, 0));
    EXPECT_EQ(8, sigBufferLength(MD5, 8));
    EXPECT_EQ(16, sigBufferLength(MD5, 16));
    EXPECT_EQ(16, sigBufferLength(MD5, 40));
    EXPECT_EQ(16, sigBufferLength(MD5, 2000));

    EXPECT_EQ(20, sigBufferLength(SHA1, 0));
    EXPECT_EQ(8, sigBufferLength(SHA1, 8));
    EXPECT_EQ(20, sigBufferLength(SHA1, 20));
    EXPECT_EQ(20, sigBufferLength(SHA1, 40));
    EXPECT_EQ(20, sigBufferLength(SHA1, 2000));

    EXPECT_EQ(32, sigBufferLength(SHA256, 0));
    EXPECT_EQ(8, sigBufferLength(SHA256, 8));
    EXPECT_EQ(32, sigBufferLength(SHA256, 32));
    EXPECT_EQ(32, sigBufferLength(SHA256, 40));
    EXPECT_EQ(32, sigBufferLength(SHA256, 3200));
}

TEST(CryptoLinkTest, BadKey) {
    OutputBuffer data_buf(0);
    OutputBuffer hmac_sig(0);
    CryptoLink& crypto = CryptoLink::getCryptoLink();

    EXPECT_THROW(crypto.createHMAC(NULL, 0, MD5), BadKey);
    EXPECT_THROW(crypto.createHMAC(NULL, 0, UNKNOWN_HASH), UnsupportedAlgorithm);

    EXPECT_THROW(signHMAC(data_buf.getData(), data_buf.getLength(),
                          NULL, 0, MD5, hmac_sig), BadKey);
    EXPECT_THROW(signHMAC(data_buf.getData(), data_buf.getLength(),
                          NULL, 0, UNKNOWN_HASH, hmac_sig),
                          UnsupportedAlgorithm);

    EXPECT_THROW(verifyHMAC(data_buf.getData(), data_buf.getLength(),
                            NULL, 0, MD5, hmac_sig.getData(),
                            hmac_sig.getLength()), BadKey);
    EXPECT_THROW(verifyHMAC(data_buf.getData(), data_buf.getLength(),
                            NULL, 0, UNKNOWN_HASH, hmac_sig.getData(),
                            hmac_sig.getLength()),
                            UnsupportedAlgorithm);
}

TEST(CryptoLinkTest, Singleton) {
    const CryptoLink& c1 = CryptoLink::getCryptoLink();
    const CryptoLink& c2 = CryptoLink::getCryptoLink();
    ASSERT_EQ(&c1, &c2);
}
