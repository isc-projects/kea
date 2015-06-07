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

#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>

#include <gtest/gtest.h>

#include <util/encode/base64.h>

#include <hooks/hooks_manager.h>
#include <hooks/callout_handle.h>

#include <cryptolink/cryptolink.h>
#include <cryptolink/crypto_asym.h>

#include <exceptions/exceptions.h>

#include <boost/shared_ptr.hpp>

using namespace isc::cryptolink;

namespace {

#define MODULUS \
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

    /// @brief Public Key file (SubjectPublicKeyInfo in PEM)
    const std::string pubfile = TEST_DATA_SRCDIR "/pub.pem";

    /// @brief Private Key file (PKCS#8 in PEM, password '1234')
    const std::string privfile = TEST_DATA_SRCDIR "/pkcs8.pem";

    /// @brief Certificate file (X.509 Public Key Certificate in PEM)
    const std::string certfile = TEST_DATA_SRCDIR "/x509.pem";
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

namespace {

std::string callout_name("");
std::vector<uint8_t> callout_cert;
std::vector<std::string> callout_argument_names;

int
validate_certificate_callout(isc::hooks::CalloutHandle& callout_handle) {
    callout_name = "validate-certificate";
    callout_handle.getArgument("certificate", callout_cert);
    callout_argument_names = callout_handle.getArgumentNames();
    return (0);
}

}

//
// Hooks
//
TEST(AsymTest, callout) {
    using namespace isc::hooks;

    // Initialize Hooks Manager
    std::vector<std::string> libraries; // no libraries
    HooksManager::loadLibraries(libraries);

    // Install validate_certificate_callout
    LibraryHandle& preCLH = HooksManager::preCalloutsLibraryHandle();
    EXPECT_NO_THROW(preCLH.registerCallout("validate_certificate",
                                           validate_certificate_callout));

    // Get a certificate and validate it
    CryptoLink& crypto = CryptoLink::getCryptoLink();
    boost::shared_ptr<Asym> cert(crypto.createAsym(certfile, "",
                                                   RSA_, SHA1,
                                                   CERT, ASN1),
                                 deleteAsym);
    EXPECT_TRUE(cert->validate());

    // Check that callouts were indeed called
    EXPECT_EQ("validate-certificate", callout_name);
    std::vector<uint8_t> bin = cert->exportkey(CERT, ASN1);
    ASSERT_EQ(bin.size(), callout_cert.size());
    EXPECT_TRUE(std::memcmp(&bin[0], &callout_cert[0], bin.size()) == 0);
    ASSERT_EQ(1, callout_argument_names.size());
    EXPECT_TRUE(callout_argument_names[0].compare("certificate") == 0);

    EXPECT_NO_THROW(preCLH.deregisterCallout("validate_certificate",
                                             validate_certificate_callout));
}
