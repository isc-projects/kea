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

#include <config.h>

#include <string>
#include <vector>

#include <boost/lexical_cast.hpp>

#include <gtest/gtest.h>

#include <util/encode/hex.h>

#include <cryptolink/cryptolink.h>
#include <cryptolink/crypto_hash.h>

#include <util/buffer.h>
#include <exceptions/exceptions.h>

#include <boost/scoped_array.hpp>
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

    /// @brief Hash with the convenience functions
    /// See @ref doHashTest for parameters
    void doHashTestConv(const std::string& data,
                        const HashAlgorithm hash_algorithm,
                        const uint8_t* expected_hash,
                        size_t hash_len) {
        OutputBuffer data_buf(data.size());
        data_buf.writeData(data.c_str(), data.size());
        OutputBuffer hash_digest(0);

        // Sign it
        digest(data_buf.getData(), data_buf.getLength(),
               hash_algorithm, hash_digest, hash_len);

        // Check if the signature is what we expect
        checkBuffer(hash_digest, expected_hash, hash_len);
    }

    /// @brief Hash with an instantiation of a Hash object
    /// See @ref doHashTest for parameters
    void doHashTestDirect(const std::string& data,
                          const HashAlgorithm hash_algorithm,
                          const uint8_t* expected_hash,
                          size_t hash_len) {
        OutputBuffer data_buf(data.size());
        data_buf.writeData(data.c_str(), data.size());
        OutputBuffer result(1);
        CryptoLink& crypto = CryptoLink::getCryptoLink();

        // Do it
        boost::shared_ptr<Hash> hash_digest(crypto.createHash(hash_algorithm),
                                            deleteHash);
        hash_digest->update(data_buf.getData(), data_buf.getLength());
        hash_digest->final(result, hash_len);

        // Check if the digest is what we expect
        checkBuffer(result, expected_hash, hash_len);
    }

    /// @brief Hash with a vector representation
    /// See @ref doHashTest for parameters
    void doHashTestVector(const std::string& data,
                          const HashAlgorithm hash_algorithm,
                          const uint8_t* expected_hash,
                          size_t hash_len) {
        CryptoLink& crypto = CryptoLink::getCryptoLink();
        boost::shared_ptr<Hash> hash_digest(crypto.createHash(hash_algorithm),
                                            deleteHash);
        hash_digest->update(data.c_str(), data.size());
        std::vector<uint8_t> result = hash_digest->final(hash_len);
        ASSERT_EQ(hash_len, result.size());
        checkData(&result[0], expected_hash, hash_len);
    }

    /// @brief Hash with an array representation
    /// See @ref doHashTest for parameters
    void doHashTestArray(const std::string& data,
                         const HashAlgorithm hash_algorithm,
                         const uint8_t* expected_hash,
                         size_t hash_len) {
        CryptoLink& crypto = CryptoLink::getCryptoLink();
        boost::shared_ptr<Hash> hash_digest(crypto.createHash(hash_algorithm),
                                            deleteHash);
        hash_digest->update(data.c_str(), data.size());

        // note: this is not exception-safe, and can leak, but
        // if there is an unexpected exception in the code below we
        // have more important things to fix.
        boost::scoped_array<uint8_t> result(new uint8_t[hash_len]);

        hash_digest->final(result.get(), hash_len);
        checkData(result.get(), expected_hash, hash_len);
    }

    /// @brief Hash using all variants
    /// @param data Input value
    /// @param hash_algorithm Hash algorithm enum
    /// @param expected_hash Expected value
    /// @param hash_len Expected value length
    void doHashTest(const std::string& data,
                    const HashAlgorithm hash_algorithm,
                    const uint8_t* expected_hash,
                    size_t hash_len) {
        doHashTestConv(data, hash_algorithm, expected_hash, hash_len);
        doHashTestDirect(data, hash_algorithm, expected_hash, hash_len);
        doHashTestVector(data, hash_algorithm, expected_hash, hash_len);
        doHashTestArray(data, hash_algorithm, expected_hash, hash_len);
    }
}

//
// Test values taken from RFC 1321
//
TEST(HashTest, MD5_RFC1321) {
    const uint8_t hash_expected[] = { 0xd4, 0x1d, 0x8c, 0xd9, 0x8f,
                                      0x00, 0xb2, 0x04, 0xe9, 0x80,
                                      0x09, 0x98, 0xec, 0xf8, 0x42,
                                      0x7e };
    doHashTest("", MD5, hash_expected, 16);

    const uint8_t hash_expected2[] = { 0x0c, 0xc1, 0x75, 0xb9, 0xc0,
                                       0xf1, 0xb6, 0xa8, 0x31, 0xc3,
                                       0x99, 0xe2, 0x69, 0x77, 0x26,
                                       0x61 };
    doHashTest("a", MD5, hash_expected2, 16);

    const uint8_t hash_expected3[] = { 0x90, 0x01, 0x50, 0x98, 0x3c,
                                       0xd2, 0x4f, 0xb0, 0xd6, 0x96,
                                       0x3f, 0x7d, 0x28, 0xe1, 0x7f,
                                       0x72 };
    doHashTest("abc", MD5, hash_expected3, 16);

    const uint8_t hash_expected4[] = { 0xf9, 0x6b, 0x69, 0x7d, 0x7c,
                                       0xb7, 0x93, 0x8d, 0x52, 0x5a,
                                       0x2f, 0x31, 0xaa, 0xf1, 0x61,
                                       0xd0 };
    doHashTest("message digest", MD5, hash_expected4, 16);

    const uint8_t hash_expected6[] = { 0xc3, 0xfc, 0xd3, 0xd7, 0x61,
                                       0x92, 0xe4, 0x00, 0x7d, 0xfb,
                                       0x49, 0x6c, 0xca, 0x67, 0xe1,
                                       0x3b };
    doHashTest("abcdefghijklmnopqrstuvwxyz", MD5, hash_expected6, 16);

    const uint8_t hash_expected7[] = { 0xd1, 0x74, 0xab, 0x98, 0xd2,
                                       0x77, 0xd9, 0xf5, 0xa5, 0x61,
                                       0x1c, 0x2c, 0x9f, 0x41, 0x9d,
                                       0x9f };
    doHashTest("ABCDEFGHIJKLMNOPQRSTUVWXYZabcd"
               "efghijklmnopqrstuvwxyz0123456789",
               MD5, hash_expected7, 16);

    const uint8_t hash_expected8[] = { 0x57, 0xed, 0xf4, 0xa2, 0x2b,
                                       0xe3, 0xc9, 0x55, 0xac, 0x49,
                                       0xda, 0x2e, 0x21, 0x07, 0xb6,
                                       0x7a };
    doHashTest("1234567890123456789012345678901234567890"
               "1234567890123456789012345678901234567890",
               MD5, hash_expected8, 16);
}

//
// Test values taken from RFC 3174
//
TEST(HashTest, SHA1_RFC3174) {
    const uint8_t hash_expected[] = { 0xa9, 0x99, 0x3e, 0x36, 0x47,
                                      0x06, 0x81, 0x6a, 0xba, 0x3e,
                                      0x25, 0x71, 0x78, 0x50, 0xc2,
                                      0x6c, 0x9c, 0xd0, 0xd8, 0x9d };
    doHashTest("abc", SHA1, hash_expected, 20);

    const uint8_t hash_expected2[] = { 0x84, 0x98, 0x3e, 0x44, 0x1c,
                                       0x3b, 0xd2, 0x6e, 0xba, 0xae,
                                       0x4a, 0xa1, 0xf9, 0x51, 0x29,
                                       0xe5, 0xe5, 0x46, 0x70, 0xf1 };
    doHashTest("abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq",
               SHA1, hash_expected2, 20);

    const uint8_t hash_expected3[] = { 0x34, 0xaa, 0x97, 0x3c, 0xd4,
                                       0xc4, 0xda, 0xa4, 0xf6, 0x1e,
                                       0xeb, 0x2b, 0xdb, 0xad, 0x27,
                                       0x31, 0x65, 0x34, 0x01, 0x6f };
    doHashTest(std::string(1000000, 0x61), SHA1, hash_expected3, 20);

    const uint8_t hash_expected4[] = { 0xde, 0xa3, 0x56, 0xa2, 0xcd,
                                       0xdd, 0x90, 0xc7, 0xa7, 0xec,
                                       0xed, 0xc5, 0xeb, 0xb5, 0x63,
                                       0x93, 0x4f, 0x46, 0x04, 0x52 };
    doHashTest("01234567012345670123456701234567"
               "01234567012345670123456701234567"
               "01234567012345670123456701234567"
               "01234567012345670123456701234567"
               "01234567012345670123456701234567"
               "01234567012345670123456701234567"
               "01234567012345670123456701234567"
               "01234567012345670123456701234567"
               "01234567012345670123456701234567"
               "01234567012345670123456701234567"
               "01234567012345670123456701234567"
               "01234567012345670123456701234567"
               "01234567012345670123456701234567"
               "01234567012345670123456701234567"
               "01234567012345670123456701234567"
               "01234567012345670123456701234567"
               "01234567012345670123456701234567"
               "01234567012345670123456701234567"
               "01234567012345670123456701234567"
               "01234567012345670123456701234567",
               SHA1, hash_expected4, 20);
}

//
// Test values taken from RFC 6234
//
TEST(HashTest, SHA224_RFC6234) {
    const uint8_t hash_expected[] = { 0x23, 0x09, 0x7d, 0x22, 0x34,
                                      0x05, 0xd8, 0x22, 0x86, 0x42,
                                      0xa4, 0x77, 0xbd, 0xa2, 0x55,
                                      0xb3, 0x2a, 0xad, 0xbc, 0xe4,
                                      0xbd, 0xa0, 0xb3, 0xf7, 0xe3,
                                      0x6c, 0x9d, 0xa7 };
    doHashTest("abc", SHA224, hash_expected, 28);

    const uint8_t hash_expected2[] = { 0x75, 0x38, 0x8b, 0x16, 0x51,
                                       0x27, 0x76, 0xcc, 0x5d, 0xba,
                                       0x5d, 0xa1, 0xfd, 0x89, 0x01,
                                       0x50, 0xb0, 0xc6, 0x45, 0x5c,
                                       0xb4, 0xf5, 0x8b, 0x19, 0x52,
                                       0x52, 0x25, 0x25 };
    doHashTest("abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq",
               SHA224, hash_expected2, 28);

    const uint8_t hash_expected3[] = { 0x20, 0x79, 0x46, 0x55, 0x98,
                                       0x0c, 0x91, 0xd8, 0xbb, 0xb4,
                                       0xc1, 0xea, 0x97, 0x61, 0x8a,
                                       0x4b, 0xf0, 0x3f, 0x42, 0x58,
                                       0x19, 0x48, 0xb2, 0xee, 0x4e,
                                       0xe7, 0xad, 0x67 };
    doHashTest(std::string(1000000, 0x61), SHA224, hash_expected3, 28);

    const uint8_t hash_expected4[] = { 0x56, 0x7f, 0x69, 0xf1, 0x68,
                                       0xcd, 0x78, 0x44, 0xe6, 0x52,
                                       0x59, 0xce, 0x65, 0x8f, 0xe7,
                                       0xaa, 0xdf, 0xa2, 0x52, 0x16,
                                       0xe6, 0x8e, 0xca, 0x0e, 0xb7,
                                       0xab, 0x82, 0x62 };
    doHashTest("01234567012345670123456701234567"
               "01234567012345670123456701234567"
               "01234567012345670123456701234567"
               "01234567012345670123456701234567"
               "01234567012345670123456701234567"
               "01234567012345670123456701234567"
               "01234567012345670123456701234567"
               "01234567012345670123456701234567"
               "01234567012345670123456701234567"
               "01234567012345670123456701234567"
               "01234567012345670123456701234567"
               "01234567012345670123456701234567"
               "01234567012345670123456701234567"
               "01234567012345670123456701234567"
               "01234567012345670123456701234567"
               "01234567012345670123456701234567"
               "01234567012345670123456701234567"
               "01234567012345670123456701234567"
               "01234567012345670123456701234567"
               "01234567012345670123456701234567",
               SHA224, hash_expected4, 28);
}

TEST(HashTest, SHA256_RFC6234) {
    const uint8_t hash_expected[] = { 0xba, 0x78, 0x16, 0xbf, 0x8f,
                                      0x01, 0xcf, 0xea, 0x41, 0x41,
                                      0x40, 0xde, 0x5d, 0xae, 0x22,
                                      0x23, 0xb0, 0x03, 0x61, 0xa3,
                                      0x96, 0x17, 0x7a, 0x9c, 0xb4,
                                      0x10, 0xff, 0x61, 0xf2, 0x00,
                                      0x15, 0xad };
    doHashTest("abc", SHA256, hash_expected, 32);

    const uint8_t hash_expected2[] = { 0x24, 0x8d, 0x6a, 0x61, 0xd2,
                                       0x06, 0x38, 0xb8, 0xe5, 0xc0,
                                       0x26, 0x93, 0x0c, 0x3e, 0x60,
                                       0x39, 0xa3, 0x3c, 0xe4, 0x59,
                                       0x64, 0xff, 0x21, 0x67, 0xf6,
                                       0xec, 0xed, 0xd4, 0x19, 0xdb,
                                       0x06, 0xc1 };
    doHashTest("abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq",
               SHA256, hash_expected2, 32);

    const uint8_t hash_expected3[] = { 0xcd, 0xc7, 0x6e, 0x5c, 0x99,
                                       0x14, 0xfb, 0x92, 0x81, 0xa1,
                                       0xc7, 0xe2, 0x84, 0xd7, 0x3e,
                                       0x67, 0xf1, 0x80, 0x9a, 0x48,
                                       0xa4, 0x97, 0x20, 0x0e, 0x04,
                                       0x6d, 0x39, 0xcc, 0xc7, 0x11,
                                       0x2c, 0xd0 };
    doHashTest(std::string(1000000, 0x61), SHA256, hash_expected3, 32);

    const uint8_t hash_expected4[] = { 0x59, 0x48, 0x47, 0x32, 0x84,
                                       0x51, 0xbd, 0xfa, 0x85, 0x05,
                                       0x62, 0x25, 0x46, 0x2c, 0xc1,
                                       0xd8, 0x67, 0xd8, 0x77, 0xfb,
                                       0x38, 0x8d, 0xf0, 0xce, 0x35,
                                       0xf2, 0x5a, 0xb5, 0x56, 0x2b,
                                       0xfb, 0xb5 };
    doHashTest("01234567012345670123456701234567"
               "01234567012345670123456701234567"
               "01234567012345670123456701234567"
               "01234567012345670123456701234567"
               "01234567012345670123456701234567"
               "01234567012345670123456701234567"
               "01234567012345670123456701234567"
               "01234567012345670123456701234567"
               "01234567012345670123456701234567"
               "01234567012345670123456701234567"
               "01234567012345670123456701234567"
               "01234567012345670123456701234567"
               "01234567012345670123456701234567"
               "01234567012345670123456701234567"
               "01234567012345670123456701234567"
               "01234567012345670123456701234567"
               "01234567012345670123456701234567"
               "01234567012345670123456701234567"
               "01234567012345670123456701234567"
               "01234567012345670123456701234567",
               SHA256, hash_expected4, 32);
}

TEST(HashTest, SHA384_RFC6234) {
    const uint8_t hash_expected[] = { 0xcb, 0x00, 0x75, 0x3f, 0x45,
                                      0xa3, 0x5e, 0x8b, 0xb5, 0xa0,
                                      0x3d, 0x69, 0x9a, 0xc6, 0x50,
                                      0x07, 0x27, 0x2c, 0x32, 0xab,
                                      0x0e, 0xde, 0xd1, 0x63, 0x1a,
                                      0x8b, 0x60, 0x5a, 0x43, 0xff,
                                      0x5b, 0xed, 0x80, 0x86, 0x07,
                                      0x2b, 0xa1, 0xe7, 0xcc, 0x23,
                                      0x58, 0xba, 0xec, 0xa1, 0x34,
                                      0xc8, 0x25, 0xa7 };
    doHashTest("abc", SHA384, hash_expected, 48);

    const uint8_t hash_expected2[] = { 0x09, 0x33, 0x0c, 0x33, 0xf7,
                                       0x11, 0x47, 0xe8, 0x3d, 0x19,
                                       0x2f, 0xc7, 0x82, 0xcd, 0x1b,
                                       0x47, 0x53, 0x11, 0x1b, 0x17,
                                       0x3b, 0x3b, 0x05, 0xd2, 0x2f,
                                       0xa0, 0x80, 0x86, 0xe3, 0xb0,
                                       0xf7, 0x12, 0xfc, 0xc7, 0xc7,
                                       0x1a, 0x55, 0x7e, 0x2d, 0xb9,
                                       0x66, 0xc3, 0xe9, 0xfa, 0x91,
                                       0x74, 0x60, 0x39 };
    doHashTest("abcdefghbcdefghicdefghijdefghijkefghijklfghijklmghijklmn"
               "hijklmnoijklmnopjklmnopqklmnopqrlmnopqrsmnopqrstnopqrstu",
               SHA384, hash_expected2, 48);

    const uint8_t hash_expected3[] = { 0x9d, 0x0e, 0x18, 0x09, 0x71,
                                       0x64, 0x74, 0xcb, 0x08, 0x6e,
                                       0x83, 0x4e, 0x31, 0x0a, 0x4a,
                                       0x1c, 0xed, 0x14, 0x9e, 0x9c,
                                       0x00, 0xf2, 0x48, 0x52, 0x79,
                                       0x72, 0xce, 0xc5, 0x70, 0x4c,
                                       0x2a, 0x5b, 0x07, 0xb8, 0xb3,
                                       0xdc, 0x38, 0xec, 0xc4, 0xeb,
                                       0xae, 0x97, 0xdd, 0xd8, 0x7f,
                                       0x3d, 0x89, 0x85 };
    doHashTest(std::string(1000000, 0x61), SHA384, hash_expected3, 48);

    const uint8_t hash_expected4[] = { 0x2f, 0xc6, 0x4a, 0x4f, 0x50,
                                       0x0d, 0xdb, 0x68, 0x28, 0xf6,
                                       0xa3, 0x43, 0x0b, 0x8d, 0xd7,
                                       0x2a, 0x36, 0x8e, 0xb7, 0xf3,
                                       0xa8, 0x32, 0x2a, 0x70, 0xbc,
                                       0x84, 0x27, 0x5b, 0x9c, 0x0b,
                                       0x3a, 0xb0, 0x0d, 0x27, 0xa5,
                                       0xcc, 0x3c, 0x2d, 0x22, 0x4a,
                                       0xa6, 0xb6, 0x1a, 0x0d, 0x79,
                                       0xfb, 0x45, 0x96 };
    doHashTest("01234567012345670123456701234567"
               "01234567012345670123456701234567"
               "01234567012345670123456701234567"
               "01234567012345670123456701234567"
               "01234567012345670123456701234567"
               "01234567012345670123456701234567"
               "01234567012345670123456701234567"
               "01234567012345670123456701234567"
               "01234567012345670123456701234567"
               "01234567012345670123456701234567"
               "01234567012345670123456701234567"
               "01234567012345670123456701234567"
               "01234567012345670123456701234567"
               "01234567012345670123456701234567"
               "01234567012345670123456701234567"
               "01234567012345670123456701234567"
               "01234567012345670123456701234567"
               "01234567012345670123456701234567"
               "01234567012345670123456701234567"
               "01234567012345670123456701234567",
               SHA384, hash_expected4, 48);
}

TEST(HashTest, SHA512_RFC6234) {
    const uint8_t hash_expected[] = { 0xdd, 0xaf, 0x35, 0xa1, 0x93,
                                      0x61, 0x7a, 0xba, 0xcc, 0x41,
                                      0x73, 0x49, 0xae, 0x20, 0x41,
                                      0x31, 0x12, 0xe6, 0xfa, 0x4e,
                                      0x89, 0xa9, 0x7e, 0xa2, 0x0a,
                                      0x9e, 0xee, 0xe6, 0x4b, 0x55,
                                      0xd3, 0x9a, 0x21, 0x92, 0x99,
                                      0x2a, 0x27, 0x4f, 0xc1, 0xa8,
                                      0x36, 0xba, 0x3c, 0x23, 0xa3,
                                      0xfe, 0xeb, 0xbd, 0x45, 0x4d,
                                      0x44, 0x23, 0x64, 0x3c, 0xe8,
                                      0x0e, 0x2a, 0x9a, 0xc9, 0x4f,
                                      0xa5, 0x4c, 0xa4, 0x9f };
    doHashTest("abc", SHA512, hash_expected, 64);

    const uint8_t hash_expected2[] = { 0x8e, 0x95, 0x9b, 0x75, 0xda,
                                       0xe3, 0x13, 0xda, 0x8c, 0xf4,
                                       0xf7, 0x28, 0x14, 0xfc, 0x14,
                                       0x3f, 0x8f, 0x77, 0x79, 0xc6,
                                       0xeb, 0x9f, 0x7f, 0xa1, 0x72,
                                       0x99, 0xae, 0xad, 0xb6, 0x88,
                                       0x90, 0x18, 0x50, 0x1d, 0x28,
                                       0x9e, 0x49, 0x00, 0xf7, 0xe4,
                                       0x33, 0x1b, 0x99, 0xde, 0xc4,
                                       0xb5, 0x43, 0x3a, 0xc7, 0xd3,
                                       0x29, 0xee, 0xb6, 0xdd, 0x26,
                                       0x54, 0x5e, 0x96, 0xe5, 0x5b,
                                       0x87, 0x4b, 0xe9, 0x09 };
    doHashTest("abcdefghbcdefghicdefghijdefghijkefghijklfghijklmghijklmn"
               "hijklmnoijklmnopjklmnopqklmnopqrlmnopqrsmnopqrstnopqrstu",
               SHA512, hash_expected2, 64);

    const uint8_t hash_expected3[] = { 0xe7, 0x18, 0x48, 0x3d, 0x0c,
                                       0xe7, 0x69, 0x64, 0x4e, 0x2e,
                                       0x42, 0xc7, 0xbc, 0x15, 0xb4,
                                       0x63, 0x8e, 0x1f, 0x98, 0xb1,
                                       0x3b, 0x20, 0x44, 0x28, 0x56,
                                       0x32, 0xa8, 0x03, 0xaf, 0xa9,
                                       0x73, 0xeb, 0xde, 0x0f, 0xf2,
                                       0x44, 0x87, 0x7e, 0xa6, 0x0a,
                                       0x4c, 0xb0, 0x43, 0x2c, 0xe5,
                                       0x77, 0xc3, 0x1b, 0xeb, 0x00,
                                       0x9c, 0x5c, 0x2c, 0x49, 0xaa,
                                       0x2e, 0x4e, 0xad, 0xb2, 0x17,
                                       0xad, 0x8c, 0xc0, 0x9b };
    doHashTest(std::string(1000000, 0x61), SHA512, hash_expected3, 64);

    const uint8_t hash_expected4[] = { 0x89, 0xd0, 0x5b, 0xa6, 0x32,
                                       0xc6, 0x99, 0xc3, 0x12, 0x31,
                                       0xde, 0xd4, 0xff, 0xc1, 0x27,
                                       0xd5, 0xa8, 0x94, 0xda, 0xd4,
                                       0x12, 0xc0, 0xe0, 0x24, 0xdb,
                                       0x87, 0x2d, 0x1a, 0xbd, 0x2b,
                                       0xa8, 0x14, 0x1a, 0x0f, 0x85,
                                       0x07, 0x2a, 0x9b, 0xe1, 0xe2,
                                       0xaa, 0x04, 0xcf, 0x33, 0xc7,
                                       0x65, 0xcb, 0x51, 0x08, 0x13,
                                       0xa3, 0x9c, 0xd5, 0xa8, 0x4c,
                                       0x4a, 0xca, 0xa6, 0x4d, 0x3f,
                                       0x3f, 0xb7, 0xba, 0xe9 };
    doHashTest("01234567012345670123456701234567"
               "01234567012345670123456701234567"
               "01234567012345670123456701234567"
               "01234567012345670123456701234567"
               "01234567012345670123456701234567"
               "01234567012345670123456701234567"
               "01234567012345670123456701234567"
               "01234567012345670123456701234567"
               "01234567012345670123456701234567"
               "01234567012345670123456701234567"
               "01234567012345670123456701234567"
               "01234567012345670123456701234567"
               "01234567012345670123456701234567"
               "01234567012345670123456701234567"
               "01234567012345670123456701234567"
               "01234567012345670123456701234567"
               "01234567012345670123456701234567"
               "01234567012345670123456701234567"
               "01234567012345670123456701234567"
               "01234567012345670123456701234567",
               SHA512, hash_expected4, 64);
}

namespace {
    /// @brief Get the hash algorithm
    /// @param alg Hash algorithm enum
    /// @return Hash algorithm enum
    HashAlgorithm
    digestHashAlgorithm(HashAlgorithm alg) {
        boost::shared_ptr<Hash> hash_digest(
            CryptoLink::getCryptoLink().createHash(alg),
            deleteHash);
        return (hash_digest->getHashAlgorithm());
    }
}

TEST(HashTest, HashAlgorithm) {
    EXPECT_EQ(MD5, digestHashAlgorithm(MD5));
    EXPECT_EQ(SHA1, digestHashAlgorithm(SHA1));
    EXPECT_EQ(SHA256, digestHashAlgorithm(SHA256));
    EXPECT_EQ(SHA224, digestHashAlgorithm(SHA224));
    EXPECT_EQ(SHA384, digestHashAlgorithm(SHA384));
    EXPECT_EQ(SHA512, digestHashAlgorithm(SHA512));
}

namespace {
    /// @brief Compute the vector digest length
    /// @param alg Hash algorithm enum
    /// @param len Wanted length
    /// @return Effective length
    size_t
    digestVectorLength(HashAlgorithm alg, size_t len) {
        boost::shared_ptr<Hash> hash_digest(
            CryptoLink::getCryptoLink().createHash(alg),
            deleteHash);
        hash_digest->update("asdf", 4);
        const std::vector<uint8_t> result = hash_digest->final(len);
        return (result.size());
    }

    /// @brief Compute the buffer digest length
    /// @param alg Hash algorithm enum
    /// @param len Wanted length
    /// @return Effective length
    size_t
    digestBufferLength(HashAlgorithm alg, size_t len) {
        boost::shared_ptr<Hash> hash_digest(
            CryptoLink::getCryptoLink().createHash(alg),
            deleteHash);
        hash_digest->update("asdf", 4);
        OutputBuffer result(0);
        hash_digest->final(result, len);
        return (result.getLength());
    }
    // There is no equivalent for array digest because it is copied
    // in place
}

TEST(HashTest, HashLength) {
    std::vector<uint8_t> result;

    EXPECT_EQ(8, digestVectorLength(MD5, 8));
    EXPECT_EQ(16, digestVectorLength(MD5, 16));
    EXPECT_EQ(16, digestVectorLength(MD5, 40));
    EXPECT_EQ(16, digestVectorLength(MD5, 2000));

    EXPECT_EQ(8, digestBufferLength(SHA1, 8));
    EXPECT_EQ(20, digestBufferLength(SHA1, 20));
    EXPECT_EQ(20, digestBufferLength(SHA1, 40));
    EXPECT_EQ(20, digestBufferLength(SHA1, 2000));

    EXPECT_EQ(8, digestBufferLength(SHA256, 8));
    EXPECT_EQ(32, digestBufferLength(SHA256, 32));
    EXPECT_EQ(32, digestBufferLength(SHA256, 40));
    EXPECT_EQ(32, digestBufferLength(SHA256, 3200));

    EXPECT_EQ(8, digestBufferLength(MD5, 8));
    EXPECT_EQ(16, digestBufferLength(MD5, 16));
    EXPECT_EQ(16, digestBufferLength(MD5, 40));
    EXPECT_EQ(16, digestBufferLength(MD5, 2000));

    EXPECT_EQ(8, digestBufferLength(SHA1, 8));
    EXPECT_EQ(20, digestBufferLength(SHA1, 20));
    EXPECT_EQ(20, digestBufferLength(SHA1, 40));
    EXPECT_EQ(20, digestBufferLength(SHA1, 2000));

    EXPECT_EQ(8, digestBufferLength(SHA256, 8));
    EXPECT_EQ(32, digestBufferLength(SHA256, 32));
    EXPECT_EQ(32, digestBufferLength(SHA256, 40));
    EXPECT_EQ(32, digestBufferLength(SHA256, 3200));
}

// @todo Error cases?
