// Copyright (C) 2011, 2014  Internet Systems Consortium, Inc. ("ISC")
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

#include <string>
#include <vector>

#include <boost/lexical_cast.hpp>

#include <gtest/gtest.h>

#include <util/encode/hex.h>

#include <cryptolink/cryptolink.h>
#include <cryptolink/crypto_hmac.h>

#include <util/buffer.h>
#include <exceptions/exceptions.h>

#include <boost/shared_ptr.hpp>

using boost::lexical_cast;
using namespace isc::util;
using namespace isc::util::encode;
using namespace isc::cryptolink;

namespace {
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

    /// @brief Sign and verify with the convenience functions
    /// See @ref doHMACTest for parameters
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

    /// @brief Sign and verify with an instantiation of an HMAC object
    /// See @ref doHMACTest for parameters
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

    /// @brief Sign and verify with vector representation of signature
    /// See @ref doHMACTest for parameters
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

    /// @brief Sign and verify with array representation of signature
    /// See @ref doHMACTest for parameters
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

    /// @brief Sign and verify using all variants
    /// @param data Input value
    /// @param secret Secret value
    /// @param secret_len Secret value length
    /// @param hash_algorithm Hash algorithm enum
    /// @param expected_hmac Expected value
    /// @param hmac_len Expected value length
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
TEST(HMACTest, HMAC_MD5_RFC2202_SIGN) {
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

TEST(HMACTest, HMAC_MD5_RFC2202_SIGN_TRUNCATED) {
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
TEST(HMACTest, HMAC_SHA1_RFC2202_SIGN) {
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

TEST(HMACTest, HMAC_SHA1_RFC2202_SIGN_TRUNCATED) {
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
//  Test data from RFC4231, including secret key
//  and source data, they are common for sha224/256/384/512
//  so put them together within the separate function.
void
doRFC4231Tests(HashAlgorithm hash_algorithm,
               const std::vector<std::vector<uint8_t> >& hmac_list)
{
    std::vector<std::string> data_list;
    std::vector<std::string> secret_list;

    data_list.push_back("Hi There");
    data_list.push_back("what do ya want for nothing?");
    data_list.push_back(std::string(50, 0xdd));
    data_list.push_back(std::string(50, 0xcd));
    data_list.push_back("Test With Truncation");
    data_list.push_back("Test Using Larger Than Block-Size Key - "
                        "Hash Key First");
    data_list.push_back("This is a test using a larger than block-size "
                        "key and a larger than block-size data. The key "
                        "needs to be hashed before being used by the HMAC "
                        "algorithm.");

    secret_list.push_back(std::string(20, 0x0b));
    secret_list.push_back("Jefe");
    secret_list.push_back(std::string(20, 0xaa));
    const uint8_t secret_array[] = {
        0x01, 0x02, 0x03, 0x04, 0x05, 0x06,
        0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c,
        0x0d, 0x0e, 0x0f, 0x10, 0x11, 0x12,
        0x13, 0x14, 0x15, 0x16, 0x17, 0x18,
        0x19 
    };
    secret_list.push_back(std::string(secret_array,
                                      secret_array + sizeof(secret_array)));
    secret_list.push_back(std::string(20, 0x0c));
    secret_list.push_back(std::string(131, 0xaa));
    secret_list.push_back(std::string(131, 0xaa));

    // Make sure we provide a consistent size of test data
    ASSERT_EQ(secret_list.size(), data_list.size());
    ASSERT_EQ(secret_list.size(), hmac_list.size());

    for (std::vector<std::string>::size_type i = 0;
         i < data_list.size(); ++i) {
        SCOPED_TRACE("RFC4231 HMAC test for algorithm ID: " +
                     lexical_cast<std::string>(hash_algorithm) +
                     ", data ID: " + lexical_cast<std::string>(i));
        // Until #920 is resolved we have to skip truncation cases.
        if (data_list[i] == "Test With Truncation") {
            continue;
        }
        doHMACTest(data_list[i], secret_list[i].c_str(), secret_list[i].size(),
                   hash_algorithm, &hmac_list[i][0], hmac_list[i].size());
    }
}

TEST(HMACTest, HMAC_SHA256_RFC4231_SIGN) {
    std::vector<std::vector<uint8_t> > hmac_expected_list(7);

    int i = 0;
    decodeHex(
        "b0344c61d8db38535ca8afceaf0bf12b881dc200c9833da726e9376c2e32cff7",
        hmac_expected_list[i++]);
    decodeHex(
        "5bdcc146bf60754e6a042426089575c75a003f089d2739839dec58b964ec3843",
        hmac_expected_list[i++]);
    decodeHex(
        "773ea91e36800e46854db8ebd09181a72959098b3ef8c122d9635514ced565fe",
        hmac_expected_list[i++]);
    decodeHex(
        "82558a389a443c0ea4cc819899f2083a85f0faa3e578f8077a2e3ff46729665b",
        hmac_expected_list[i++]);
    decodeHex("a3b6167473100ee06e0c796c2955552b", hmac_expected_list[i++]);
    decodeHex(
        "60e431591ee0b67f0d8a26aacbf5b77f8e0bc6213728c5140546040f0ee37f54",
        hmac_expected_list[i++]);
    decodeHex(
        "9b09ffa71b942fcb27635fbcd5b0e944bfdc63644f0713938a7f51535c3a35e2",
        hmac_expected_list[i++]);

    doRFC4231Tests(SHA256, hmac_expected_list);
}

//
// Test values taken from RFC 4231, test optional algorithm 224,384,512
//
TEST(HMACTest, HMAC_SHA224_RFC4231_SIGN) {
    std::vector<std::vector<uint8_t> > hmac_expected_list(7);

    int i = 0;
    decodeHex("896fb1128abbdf196832107cd49df33f47b4b1169912ba4f53684b22",
              hmac_expected_list[i++]);
    decodeHex("a30e01098bc6dbbf45690f3a7e9e6d0f8bbea2a39e6148008fd05e44",
              hmac_expected_list[i++]);
    decodeHex("7fb3cb3588c6c1f6ffa9694d7d6ad2649365b0c1f65d69d1ec8333ea",
              hmac_expected_list[i++]);
    decodeHex("6c11506874013cac6a2abc1bb382627cec6a90d86efc012de7afec5a",
              hmac_expected_list[i++]);
    decodeHex("0e2aea68a90c8d37c988bcdb9fca6fa8", hmac_expected_list[i++]);
    decodeHex("95e9a0db962095adaebe9b2d6f0dbce2d499f112f2d2b7273fa6870e",
              hmac_expected_list[i++]);
    decodeHex("3a854166ac5d9f023f54d517d0b39dbd946770db9c2b95c9f6f565d1",
              hmac_expected_list[i++]);

    doRFC4231Tests(SHA224, hmac_expected_list);
}

TEST(HMACTest, HMAC_SHA384_RFC4231_SIGN) {
    std::vector<std::vector<uint8_t> > hmac_expected_list(7);

    int i = 0;
    decodeHex("afd03944d84895626b0825f4ab46907f15f9dadbe4101ec682aa034c7cebc5"
              "9cfaea9ea9076ede7f4af152e8b2fa9cb6", hmac_expected_list[i++]);
    decodeHex("af45d2e376484031617f78d2b58a6b1b9c7ef464f5a01b47e42ec373632244"
              "5e8e2240ca5e69e2c78b3239ecfab21649", hmac_expected_list[i++]);
    decodeHex("88062608d3e6ad8a0aa2ace014c8a86f0aa635d947ac9febe83ef4e5596614"
              "4b2a5ab39dc13814b94e3ab6e101a34f27", hmac_expected_list[i++]);
    decodeHex("3e8a69b7783c25851933ab6290af6ca77a9981480850009cc5577c6e1f573b"
              "4e6801dd23c4a7d679ccf8a386c674cffb", hmac_expected_list[i++]);
    decodeHex("3abf34c3503b2a23a46efc619baef897", hmac_expected_list[i++]);
    decodeHex("4ece084485813e9088d2c63a041bc5b44f9ef1012a2b588f3cd11f05033ac4"
              "c60c2ef6ab4030fe8296248df163f44952", hmac_expected_list[i++]);
    decodeHex("6617178e941f020d351e2f254e8fd32c602420feb0b8fb9adccebb82461e99"
              "c5a678cc31e799176d3860e6110c46523e", hmac_expected_list[i++]);

    doRFC4231Tests(SHA384, hmac_expected_list);
}

TEST(HMACTest, HMAC_SHA512_RFC4231_SIGN) {
    std::vector<std::vector<uint8_t> > hmac_expected_list(7);

    int i = 0;
    decodeHex("87aa7cdea5ef619d4ff0b4241a1d6cb02379f4e2ce4ec2787ad0b30545e17c"
              "dedaa833b7d6b8a702038b274eaea3f4e4be9d914eeb61f1702e696c203a12"
              "6854", hmac_expected_list[i++]);
    decodeHex("164b7a7bfcf819e2e395fbe73b56e0a387bd64222e831fd610270cd7ea2505"
              "549758bf75c05a994a6d034f65f8f0e6fdcaeab1a34d4a6b4b636e070a38bc"
              "e737", hmac_expected_list[i++]);
    decodeHex("fa73b0089d56a284efb0f0756c890be9b1b5dbdd8ee81a3655f83e33b2279d"
              "39bf3e848279a722c806b485a47e67c807b946a337bee8942674278859e132"
              "92fb", hmac_expected_list[i++]);
    decodeHex("b0ba465637458c6990e5a8c5f61d4af7e576d97ff94b872de76f8050361ee3"
              "dba91ca5c11aa25eb4d679275cc5788063a5f19741120c4f2de2adebeb10a2"
              "98dd", hmac_expected_list[i++]);
    decodeHex("415fad6271580a531d4179bc891d87a6", hmac_expected_list[i++]);
    decodeHex("80b24263c7c1a3ebb71493c1dd7be8b49b46d1f41b4aeec1121b013783f8f3"
              "526b56d037e05f2598bd0fd2215d6a1e5295e64f73f63f0aec8b915a985d78"
              "6598", hmac_expected_list[i++]);
    decodeHex("e37b6a775dc87dbaa4dfa9f96e5e3ffddebd71f8867289865df5a32d20cdc9"
              "44b6022cac3c4982b10d5eeb55c3e4de15134676fb6de0446065c97440fa8c"
              "6a58", hmac_expected_list[i++]);

    doRFC4231Tests(SHA512, hmac_expected_list);
}

TEST(HMACTest, HMAC_SHA256_RFC2202_SIGN_TRUNCATED) {
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
    /// @brief Compute the vector signature length
    /// @param alg Hash algorithm enum
    /// @param len Wanted length
    /// @return Effective length
    size_t
    sigVectorLength(HashAlgorithm alg, size_t len) {
        boost::shared_ptr<HMAC> hmac_sign(
            CryptoLink::getCryptoLink().createHMAC("asdf", 4, alg),
            deleteHMAC);
        hmac_sign->update("asdf", 4);
        const std::vector<uint8_t> sig = hmac_sign->sign(len);
        return (sig.size());
    }

    /// @brief Compute the buffer signature length
    /// @param alg Hash algorithm enum
    /// @param len Wanted length
    /// @return Effective length
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

    // There is no equivalent for array signature because it is copied
    // in place
}

TEST(HMACTest, HMACSigLengthArgument) {
    std::vector<uint8_t> sig;

    EXPECT_EQ(8, sigVectorLength(MD5, 8));
    EXPECT_EQ(16, sigVectorLength(MD5, 16));
    EXPECT_EQ(16, sigVectorLength(MD5, 40));
    EXPECT_EQ(16, sigVectorLength(MD5, 2000));

    EXPECT_EQ(8, sigBufferLength(SHA1, 8));
    EXPECT_EQ(20, sigBufferLength(SHA1, 20));
    EXPECT_EQ(20, sigBufferLength(SHA1, 40));
    EXPECT_EQ(20, sigBufferLength(SHA1, 2000));

    EXPECT_EQ(8, sigBufferLength(SHA256, 8));
    EXPECT_EQ(32, sigBufferLength(SHA256, 32));
    EXPECT_EQ(32, sigBufferLength(SHA256, 40));
    EXPECT_EQ(32, sigBufferLength(SHA256, 3200));

    EXPECT_EQ(8, sigBufferLength(MD5, 8));
    EXPECT_EQ(16, sigBufferLength(MD5, 16));
    EXPECT_EQ(16, sigBufferLength(MD5, 40));
    EXPECT_EQ(16, sigBufferLength(MD5, 2000));

    EXPECT_EQ(8, sigBufferLength(SHA1, 8));
    EXPECT_EQ(20, sigBufferLength(SHA1, 20));
    EXPECT_EQ(20, sigBufferLength(SHA1, 40));
    EXPECT_EQ(20, sigBufferLength(SHA1, 2000));

    EXPECT_EQ(8, sigBufferLength(SHA256, 8));
    EXPECT_EQ(32, sigBufferLength(SHA256, 32));
    EXPECT_EQ(32, sigBufferLength(SHA256, 40));
    EXPECT_EQ(32, sigBufferLength(SHA256, 3200));
}

// Error cases (not only BadKey)
TEST(HMACTest, BadKey) {
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
