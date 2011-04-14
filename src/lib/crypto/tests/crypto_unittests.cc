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

#include <crypto/crypto.h>
#include <dns/buffer.h>
#include <dns/name.h>
#include <exceptions/exceptions.h>

using namespace isc::dns;
using namespace isc::crypto;

namespace {
    void checkBuffer(const OutputBuffer& buf, uint8_t *data, size_t len) {
        ASSERT_EQ(buf.getLength(), len);
        const uint8_t* buf_d = static_cast<const uint8_t*>(buf.getData());
        for (size_t i = 0; i < len; ++i) {
            ASSERT_EQ(buf_d[i], data[i]);
        }
    }

    // Sign and verify with the convenience functions
    void doHMACTestConv(std::string data, std::string key_str,
                        uint8_t* expected_hmac, size_t hmac_len) {
        OutputBuffer data_buf(data.size());
        data_buf.writeData(data.c_str(), data.size());
        OutputBuffer hmac_sig(1);

        TSIGKey key(key_str);

        // Sign it
        signHMAC(data_buf.getData(), data_buf.getLength(), key,
                 hmac_sig);

        // Check if the signature is what we expect
        checkBuffer(hmac_sig, expected_hmac, hmac_len);

        // Check whether we can verify it ourselves
        EXPECT_TRUE(verifyHMAC(data_buf.getData(), data_buf.getLength(),
                               key, hmac_sig.getData(),
                               hmac_sig.getLength()));

        // Change the sig by flipping the first octet, and check
        // whether verification fails then
        hmac_sig.writeUint8At(~hmac_sig[0], 0);
        EXPECT_FALSE(verifyHMAC(data_buf.getData(), data_buf.getLength(),
                               key, hmac_sig.getData(),
                               hmac_sig.getLength()));
    }

    // Sign and verify with an instantiation of an HMAC object
    void doHMACTestDirect(std::string data, std::string key_str,
                          uint8_t* expected_hmac, size_t hmac_len) {
        OutputBuffer data_buf(data.size());
        data_buf.writeData(data.c_str(), data.size());
        OutputBuffer hmac_sig(1);

        TSIGKey key(key_str);

        // Sign it
        HMAC hmac_sign(key);
        hmac_sign.update(data_buf.getData(), data_buf.getLength());
        hmac_sign.sign(hmac_sig);

        // Check if the signature is what we expect
        checkBuffer(hmac_sig, expected_hmac, hmac_len);

        // Check whether we can verify it ourselves
        HMAC hmac_verify(key);
        hmac_verify.update(data_buf.getData(), data_buf.getLength());
        EXPECT_TRUE(hmac_verify.verify(hmac_sig.getData(),
                                       hmac_sig.getLength()));

        // Change the sig by flipping the first octet, and check
        // whether verification fails then
        hmac_sig.writeUint8At(~hmac_sig[0], 0);
        EXPECT_FALSE(hmac_verify.verify(hmac_sig.getData(),
                                        hmac_sig.getLength()));
    }

    void doHMACTest(std::string data, std::string key_str,
                    uint8_t* expected_hmac, size_t hmac_len) {
        doHMACTestConv(data, key_str, expected_hmac, hmac_len);
        doHMACTestDirect(data, key_str, expected_hmac, hmac_len);
    }
}

//
// Test values taken from RFC 2202
//
TEST(CryptoTest, HMAC_MD5_RFC2202_SIGN) {
    uint8_t hmac_expected[] = { 0x92, 0x94, 0x72, 0x7a, 0x36, 0x38,
                                0xbb, 0x1c, 0x13, 0xf4, 0x8e, 0xf8,
                                0x15, 0x8b, 0xfc, 0x9d };
    doHMACTest("Hi There",
               "test.example:CwsLCwsLCwsLCwsLCwsLCw==:hmac-md5.sig-alg.reg.int",
               hmac_expected, 16);
    uint8_t hmac_expected2[] = { 0x75, 0x0c, 0x78, 0x3e, 0x6a, 0xb0,
                                 0xb5, 0x03, 0xea, 0xa8, 0x6e, 0x31,
                                 0x0a, 0x5d, 0xb7, 0x38 };
    doHMACTest("what do ya want for nothing?",
               "test.example:SmVmZQ==:hmac-md5.sig-alg.reg.int",
               hmac_expected2, 16);

    std::string data3;
    for (int i = 0; i < 50; ++i) {
        data3.push_back(0xdd);
    }
    uint8_t hmac_expected3[] = { 0x56, 0xbe, 0x34, 0x52, 0x1d, 0x14,
                                 0x4c, 0x88, 0xdb, 0xb8, 0xc7, 0x33,
                                 0xf0, 0xe8, 0xb3, 0xf6};
    doHMACTest(data3,
               "test.example:qqqqqqqqqqqqqqqqqqqqqg==:hmac-md5.sig-alg.reg.int",
               hmac_expected3, 16);

    std::string data4;
    for (int i = 0; i < 50; ++i) {
        data4.push_back(0xcd);
    }
    uint8_t hmac_expected4[] = { 0x69, 0x7e, 0xaf, 0x0a, 0xca, 0x3a,
                                 0x3a, 0xea, 0x3a, 0x75, 0x16, 0x47,
                                 0x46, 0xff, 0xaa, 0x79 };
    doHMACTest(data4,
               "test.example:AQIDBAUGBwgJCgsMDQ4PEBESExQVFhcYGQ==:hmac-md5.sig-alg.reg.int",
               hmac_expected4, 16);

    uint8_t hmac_expected5[] = { 0x56, 0x46, 0x1e, 0xf2, 0x34, 0x2e,
                                 0xdc, 0x00, 0xf9, 0xba, 0xb9, 0x95,
                                 0x69, 0x0e, 0xfd, 0x4c };
    doHMACTest("Test With Truncation",
               "test.example:DAwMDAwMDAwMDAwMDAwMDA==:hmac-md5.sig-alg.reg.int",
               hmac_expected5, 16);

    uint8_t hmac_expected6[] = { 0x6b, 0x1a, 0xb7, 0xfe, 0x4b, 0xd7,
                                 0xbf, 0x8f, 0x0b, 0x62, 0xe6, 0xce,
                                 0x61, 0xb9, 0xd0, 0xcd };
    doHMACTest("Test Using Larger Than Block-Size Key - Hash Key First",
               "test.example:qqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqq"
               "qqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqq"
               "qqqqqqqqqo=:hmac-md5.sig-alg.reg.int",
               hmac_expected6, 16);

    uint8_t hmac_expected7[] = { 0x6f, 0x63, 0x0f, 0xad, 0x67, 0xcd,
                                 0xa0, 0xee, 0x1f, 0xb1, 0xf5, 0x62,
                                 0xdb, 0x3a, 0xa5, 0x3e };
    doHMACTest("Test Using Larger Than Block-Size Key and Larger Than "
               "One Block-Size Data",
               "test.example:qqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqq"
               "qqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqq"
               "qqqqqqqqqo=:hmac-md5.sig-alg.reg.int",
               hmac_expected7, 16);

}

//
// Test values taken from RFC 2202
//
TEST(CryptoTest, HMAC_SHA1_RFC2202_SIGN) {
    uint8_t hmac_expected[] = { 0xb6, 0x17, 0x31, 0x86, 0x55, 0x05,
                                0x72, 0x64, 0xe2, 0x8b, 0xc0, 0xb6,
                                0xfb, 0x37, 0x8c, 0x8e, 0xf1, 0x46,
                                0xbe, 0x00 };
    doHMACTest("Hi There",
               "test.example:CwsLCwsLCwsLCwsLCwsLCwsLCws=:hmac-sha1",
               hmac_expected, 20);

    uint8_t hmac_expected2[] = { 0xef, 0xfc, 0xdf, 0x6a, 0xe5, 0xeb,
                                 0x2f, 0xa2, 0xd2, 0x74, 0x16, 0xd5,
                                 0xf1, 0x84, 0xdf, 0x9c, 0x25, 0x9a,
                                 0x7c, 0x79 };
    doHMACTest("what do ya want for nothing?",
               "test.example:SmVmZQ==:hmac-sha1",
               hmac_expected2, 20);

    std::string data3;
    for (int i = 0; i < 50; ++i) {
        data3.push_back(0xdd);
    }
    uint8_t hmac_expected3[] = { 0x12, 0x5d, 0x73, 0x42, 0xb9, 0xac,
                                 0x11, 0xcd, 0x91, 0xa3, 0x9a, 0xf4,
                                 0x8a, 0xa1, 0x7b, 0x4f, 0x63, 0xf1,
                                 0x75, 0xd3 };
    doHMACTest(data3,
               "test.example:qqqqqqqqqqqqqqqqqqqqqqqqqqo=:hmac-sha1",
               hmac_expected3, 20);

    std::string data4;
    for (int i = 0; i < 50; ++i) {
        data4.push_back(0xcd);
    }
    uint8_t hmac_expected4[] = { 0x4c, 0x90, 0x07, 0xf4, 0x02, 0x62,
                                 0x50, 0xc6, 0xbc, 0x84, 0x14, 0xf9,
                                 0xbf, 0x50, 0xc8, 0x6c, 0x2d, 0x72,
                                 0x35, 0xda };
    doHMACTest(data4,
               "test.example:AQIDBAUGBwgJCgsMDQ4PEBESExQVFhcYGQ==:hmac-sha1",
               hmac_expected4, 20);

    uint8_t hmac_expected5[] = { 0x4c, 0x1a, 0x03, 0x42, 0x4b, 0x55,
                                 0xe0, 0x7f, 0xe7, 0xf2, 0x7b, 0xe1,
                                 0xd5, 0x8b, 0xb9, 0x32, 0x4a, 0x9a,
                                 0x5a, 0x04 };
    doHMACTest("Test With Truncation",
               "test.example:DAwMDAwMDAwMDAwMDAwMDAwMDAw=:hmac-sha1",
               hmac_expected5, 20);

    uint8_t hmac_expected6[] = { 0xaa, 0x4a, 0xe5, 0xe1, 0x52, 0x72,
                                 0xd0, 0x0e, 0x95, 0x70, 0x56, 0x37,
                                 0xce, 0x8a, 0x3b, 0x55, 0xed, 0x40,
                                 0x21, 0x12 };
    doHMACTest("Test Using Larger Than Block-Size Key - Hash Key First",
               "test.example:qqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqq"
               "qqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqq"
               "qqqqqqqqqo=:hmac-sha1",
               hmac_expected6, 20);

    uint8_t hmac_expected7[] = { 0xe8, 0xe9, 0x9d, 0x0f, 0x45, 0x23,
                                 0x7d, 0x78, 0x6d, 0x6b, 0xba, 0xa7,
                                 0x96, 0x5c, 0x78, 0x08, 0xbb, 0xff,
                                 0x1a, 0x91 };
    doHMACTest("Test Using Larger Than Block-Size Key and Larger Than "
               "One Block-Size Data",
               "test.example:qqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqq"
               "qqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqq"
               "qqqqqqqqqo=:hmac-sha1",
               hmac_expected7, 20);
}

//
// Test values taken from RFC 4231
//
TEST(CryptoTest, HMAC_SHA256_RFC2202_SIGN) {
    uint8_t hmac_expected[] = { 0xb0, 0x34, 0x4c, 0x61, 0xd8, 0xdb,
                                0x38, 0x53, 0x5c, 0xa8, 0xaf, 0xce,
                                0xaf, 0x0b, 0xf1, 0x2b, 0x88, 0x1d,
                                0xc2, 0x00, 0xc9, 0x83, 0x3d, 0xa7,
                                0x26, 0xe9, 0x37, 0x6c, 0x2e, 0x32,
                                0xcf, 0xf7 };
    doHMACTest("Hi There",
               "test.example:CwsLCwsLCwsLCwsLCwsLCwsLCws=:hmac-sha256",
               hmac_expected, 32);

    uint8_t hmac_expected2[] = { 0x5b, 0xdc, 0xc1, 0x46, 0xbf, 0x60,
                                 0x75, 0x4e, 0x6a, 0x04, 0x24, 0x26,
                                 0x08, 0x95, 0x75, 0xc7, 0x5a, 0x00,
                                 0x3f, 0x08, 0x9d, 0x27, 0x39, 0x83,
                                 0x9d, 0xec, 0x58, 0xb9, 0x64, 0xec,
                                 0x38, 0x43 };
    doHMACTest("what do ya want for nothing?",
               "test.example:SmVmZQ==:hmac-sha256",
               hmac_expected2, 32);

    std::string data3;
    for (int i = 0; i < 50; ++i) {
        data3.push_back(0xdd);
    }
    uint8_t hmac_expected3[] = { 0x77, 0x3e, 0xa9, 0x1e, 0x36, 0x80,
                                 0x0e, 0x46, 0x85, 0x4d, 0xb8, 0xeb,
                                 0xd0, 0x91, 0x81, 0xa7, 0x29, 0x59,
                                 0x09, 0x8b, 0x3e, 0xf8, 0xc1, 0x22,
                                 0xd9, 0x63, 0x55, 0x14, 0xce, 0xd5,
                                 0x65, 0xfe };
    doHMACTest(data3,
               "test.example:qqqqqqqqqqqqqqqqqqqqqqqqqqo=:hmac-sha256",
               hmac_expected3, 32);

    std::string data4;
    for (int i = 0; i < 50; ++i) {
        data4.push_back(0xcd);
    }
    uint8_t hmac_expected4[] = { 0x82, 0x55, 0x8a, 0x38, 0x9a, 0x44,
                                 0x3c, 0x0e, 0xa4, 0xcc, 0x81, 0x98,
                                 0x99, 0xf2, 0x08, 0x3a, 0x85, 0xf0,
                                 0xfa, 0xa3, 0xe5, 0x78, 0xf8, 0x07,
                                 0x7a, 0x2e, 0x3f, 0xf4, 0x67, 0x29,
                                 0x66, 0x5b };
    doHMACTest(data4,
               "test.example:AQIDBAUGBwgJCgsMDQ4PEBESExQVFhcYGQ==:hmac-sha256",
               hmac_expected4, 32);

    uint8_t hmac_expected6[] = { 0x60, 0xe4, 0x31, 0x59, 0x1e, 0xe0,
                                 0xb6, 0x7f, 0x0d, 0x8a, 0x26, 0xaa,
                                 0xcb, 0xf5, 0xb7, 0x7f, 0x8e, 0x0b,
                                 0xc6, 0x21, 0x37, 0x28, 0xc5, 0x14,
                                 0x05, 0x46, 0x04, 0x0f, 0x0e, 0xe3,
                                 0x7f, 0x54 };
    doHMACTest("Test Using Larger Than Block-Size Key - Hash Key First",
               "test.example:qqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqq"
               "qqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqq"
               "qqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqq"
               "qqqqqqqqqqqqqqqqqqqqqqo=:hmac-sha256",
               hmac_expected6, 32);

    uint8_t hmac_expected7[] = { 0x9b, 0x09, 0xff, 0xa7, 0x1b, 0x94,
                                 0x2f, 0xcb, 0x27, 0x63, 0x5f, 0xbc,
                                 0xd5, 0xb0, 0xe9, 0x44, 0xbf, 0xdc,
                                 0x63, 0x64, 0x4f, 0x07, 0x13, 0x93,
                                 0x8a, 0x7f, 0x51, 0x53, 0x5c, 0x3a,
                                 0x35, 0xe2 };
    doHMACTest("This is a test using a larger than block-size key and a"
               " larger than block-size data. The key needs to be hashe"
               "d before being used by the HMAC algorithm.",
               "test.example:qqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqq"
               "qqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqq"
               "qqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqq"
               "qqqqqqqqqqqqqqqqqqqqqqo=:hmac-sha256",
               hmac_expected7, 32);
}

TEST(CryptoTest, BadKey) {
    TSIGKey bad_key = TSIGKey(Name("test.example."), Name("hmac-sha1."),
                              NULL, 0);

    OutputBuffer data_buf(0);
    OutputBuffer hmac_sig(1);

    EXPECT_THROW(signHMAC(data_buf.getData(), data_buf.getLength(),
                          bad_key, hmac_sig), BadKey);
    EXPECT_THROW(verifyHMAC(data_buf.getData(), data_buf.getLength(),
                            bad_key, hmac_sig.getData(),
                            hmac_sig.getLength()), BadKey);
}
