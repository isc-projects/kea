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
#include <crypto/crypto_botan.h>
#include <dns/buffer.h>
#include <exceptions/exceptions.h>

using namespace isc::dns;
using namespace isc::crypto;

namespace {
	void checkBuffer(const OutputBuffer& buf, uint8_t *data, size_t len) {
		ASSERT_EQ(buf.getLength(), len);
		const uint8_t* buf_d = static_cast<const uint8_t*>(buf.getData());
		for (size_t i = 0; i < len; ++i) {
			//std::cout << "[XX] I: " << i << ", buf: " << buf_d[i] << ", dat: " << data[i] << std::endl;
			ASSERT_EQ(buf_d[i], data[i]);
		}
	}
	
	void doHMACTest(std::string data, std::string key_str,
	                uint8_t* expected_hmac, size_t hmac_len) {
	    OutputBuffer data_buf(data.size());
	    data_buf.writeData(data.c_str(), data.size());
	    OutputBuffer hmac_sig(1);
	    
	    TSIGKey key = TSIGKeyFromString(key_str);
	    
	    signHMAC(data_buf, key, hmac_sig);
	    checkBuffer(hmac_sig, expected_hmac, hmac_len);
	}
}

// Test values taken from RFC 2202
TEST(CryptoTest, HMAC_MD5_RFC2202_SIGN) {
	// 0x0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b0b = CwsLCwsLCwsLCwsLCwsLCw==
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
	           "test.example:qqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqo=:hmac-md5.sig-alg.reg.int",
	           hmac_expected6, 16);

	uint8_t hmac_expected7[] = { 0x6f, 0x63, 0x0f, 0xad, 0x67, 0xcd,
	                             0xa0, 0xee, 0x1f, 0xb1, 0xf5, 0x62,
	                             0xdb, 0x3a, 0xa5, 0x3e };
	doHMACTest("Test Using Larger Than Block-Size Key and Larger Than One Block-Size Data",
	           "test.example:qqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqo=:hmac-md5.sig-alg.reg.int",
	           hmac_expected7, 16);

}

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
	           "test.example:qqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqo=:hmac-sha1",
	           hmac_expected6, 20);

	uint8_t hmac_expected7[] = { 0xe8, 0xe9, 0x9d, 0x0f, 0x45, 0x23,
	                             0x7d, 0x78, 0x6d, 0x6b, 0xba, 0xa7,
	                             0x96, 0x5c, 0x78, 0x08, 0xbb, 0xff,
	                             0x1a, 0x91 };
	doHMACTest("Test Using Larger Than Block-Size Key and Larger Than One Block-Size Data",
	           "test.example:qqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqo=:hmac-sha1",
	           hmac_expected7, 20);
}

TEST(CryptoText, TSIGKeyFromString) {
	TSIGKey k1 = TSIGKeyFromString("test.example:MSG6Ng==:hmac-md5.sig-alg.reg.int");
	TSIGKey k2 = TSIGKeyFromString("test.example.:MSG6Ng==:hmac-md5.sig-alg.reg.int.");
	TSIGKey k3 = TSIGKeyFromString("test.example:MSG6Ng==");
	
	EXPECT_EQ("test.example.:MSG6Ng==:hmac-md5.sig-alg.reg.int.",
	          TSIGKeyToString(k1));
	EXPECT_EQ("test.example.:MSG6Ng==:hmac-md5.sig-alg.reg.int.",
	          TSIGKeyToString(k2));
	EXPECT_EQ("test.example.:MSG6Ng==:hmac-md5.sig-alg.reg.int.",
	          TSIGKeyToString(k3));

	EXPECT_THROW(TSIGKeyFromString(""), isc::InvalidParameter);
	EXPECT_THROW(TSIGKeyFromString("::"), isc::InvalidParameter);
	EXPECT_THROW(TSIGKeyFromString("test.example.::"), isc::InvalidParameter);
	EXPECT_THROW(TSIGKeyFromString("test.example.:MSG6Ng==:unknown"), isc::InvalidParameter);
}
