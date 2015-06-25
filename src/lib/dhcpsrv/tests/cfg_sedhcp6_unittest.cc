// Copyright (C) 2015 Internet Systems Consortium, Inc. ("ISC")
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

#include <dhcp/dhcp6.h>
#include <dhcpsrv/cfg_sedhcp6.h>
#include <cryptolink/crypto_asym.h>

#include <gtest/gtest.h>

using namespace isc;
using namespace isc::dhcp;
using namespace isc::cryptolink;

namespace {

// This test checks the default values
TEST(CfgSeDhcp6Test, defaults) {
    CfgSeDhcp6 state;

    EXPECT_FALSE(state.getSignAnswers());
    EXPECT_FALSE(state.getTimestampAnswers());
    EXPECT_FALSE(state.getCheckSignatures());
    EXPECT_FALSE(state.getCheckAuthorizations());
    EXPECT_FALSE(state.getCheckTimestamps());
    EXPECT_FALSE(state.getOnlineValidation());
    EXPECT_FALSE(state.getPrivateKey());
    EXPECT_FALSE(state.getCredential());
}

// This test checks the sign-answer flag
TEST(CfgSeDhcp6Test, signAnswers) {
    CfgSeDhcp6 state(true, false, false, false, false, false);

    EXPECT_TRUE(state.getSignAnswers());
    EXPECT_FALSE(state.getTimestampAnswers());
    EXPECT_FALSE(state.getCheckSignatures());
    EXPECT_FALSE(state.getCheckAuthorizations());
    EXPECT_FALSE(state.getCheckTimestamps());
    EXPECT_FALSE(state.getOnlineValidation());
    EXPECT_FALSE(state.getPrivateKey());
    EXPECT_FALSE(state.getCredential());
}

// This test checks the timestamp-answers flag
TEST(CfgSeDhcp6Test, timestampAnswers) {
    CfgSeDhcp6 state(false, true, false, false, false, false);

    EXPECT_FALSE(state.getSignAnswers());
    EXPECT_TRUE(state.getTimestampAnswers());
    EXPECT_FALSE(state.getCheckSignatures());
    EXPECT_FALSE(state.getCheckAuthorizations());
    EXPECT_FALSE(state.getCheckTimestamps());
    EXPECT_FALSE(state.getOnlineValidation());
    EXPECT_FALSE(state.getPrivateKey());
    EXPECT_FALSE(state.getCredential());
}

// This test checks the check-signatures flag
TEST(CfgSeDhcp6Test, checkSignatures) {
    CfgSeDhcp6 state(false, false, true, false, false, false);

    EXPECT_FALSE(state.getSignAnswers());
    EXPECT_FALSE(state.getTimestampAnswers());
    EXPECT_TRUE(state.getCheckSignatures());
    EXPECT_FALSE(state.getCheckAuthorizations());
    EXPECT_FALSE(state.getCheckTimestamps());
    EXPECT_FALSE(state.getOnlineValidation());
    EXPECT_FALSE(state.getPrivateKey());
    EXPECT_FALSE(state.getCredential());
}

// This test checks the check-authorizations flag
TEST(CfgSeDhcp6Test, checkAuthorizations) {
    CfgSeDhcp6 state(false, false, false, true, false, false);

    EXPECT_FALSE(state.getSignAnswers());
    EXPECT_FALSE(state.getTimestampAnswers());
    EXPECT_FALSE(state.getCheckSignatures());
    EXPECT_TRUE(state.getCheckAuthorizations());
    EXPECT_FALSE(state.getCheckTimestamps());
    EXPECT_FALSE(state.getOnlineValidation());
    EXPECT_FALSE(state.getPrivateKey());
    EXPECT_FALSE(state.getCredential());
}

// This test checks the check-timestamps flag
TEST(CfgSeDhcp6Test, checkTimestamps) {
    CfgSeDhcp6 state(false, false, false, false, true, false);

    EXPECT_FALSE(state.getSignAnswers());
    EXPECT_FALSE(state.getTimestampAnswers());
    EXPECT_FALSE(state.getCheckSignatures());
    EXPECT_FALSE(state.getCheckAuthorizations());
    EXPECT_TRUE(state.getCheckTimestamps());
    EXPECT_FALSE(state.getOnlineValidation());
    EXPECT_FALSE(state.getPrivateKey());
    EXPECT_FALSE(state.getCredential());
}

// This test checks the online-validation flag
TEST(CfgSeDhcp6Test, onlineValidation) {
    CfgSeDhcp6 state(false, false, false, false, false, true);

    EXPECT_FALSE(state.getSignAnswers());
    EXPECT_FALSE(state.getTimestampAnswers());
    EXPECT_FALSE(state.getCheckSignatures());
    EXPECT_FALSE(state.getCheckAuthorizations());
    EXPECT_FALSE(state.getCheckTimestamps());
    EXPECT_TRUE(state.getOnlineValidation());
    EXPECT_FALSE(state.getPrivateKey());
    EXPECT_FALSE(state.getCredential());
}

// This test checks the private key value
TEST(CfgSeDhcp6Test, privateKey) {
    const std::string privfile = SEDHCP6_DATA_DIR "/priv.pem";
    CryptoLink& crypto = CryptoLink::getCryptoLink();
    CfgSeDhcp6::AsymPtr priv_key(crypto.createAsym(privfile,
                                                   "",
                                                   RSA_,
                                                   SHA256,
                                                   PRIVATE,
                                                   ASN1),
                                 deleteAsym);
    CfgSeDhcp6 state(false, false, false, false, false, false,
                     priv_key);

    EXPECT_FALSE(state.getSignAnswers());
    EXPECT_FALSE(state.getTimestampAnswers());
    EXPECT_FALSE(state.getCheckSignatures());
    EXPECT_FALSE(state.getCheckAuthorizations());
    EXPECT_FALSE(state.getCheckTimestamps());
    EXPECT_FALSE(state.getOnlineValidation());
    EXPECT_TRUE(state.getPrivateKey() == priv_key);
    EXPECT_FALSE(state.getCredential());
}

// This test checks the credential value
TEST(CfgSeDhcp6Test, credential) {
    const std::string pubfile = SEDHCP6_DATA_DIR "/pub.pem";
    CryptoLink& crypto = CryptoLink::getCryptoLink();
    CfgSeDhcp6::AsymPtr priv_key;
    CfgSeDhcp6::AsymPtr pub_key(crypto.createAsym(pubfile,
                                                  "",
                                                  RSA_,
                                                  SHA256,
                                                  PUBLIC,
                                                  ASN1),
                                deleteAsym);
    CfgSeDhcp6 state(false, false, false, false, false,false,
                     priv_key, pub_key);

    EXPECT_FALSE(state.getSignAnswers());
    EXPECT_FALSE(state.getTimestampAnswers());
    EXPECT_FALSE(state.getCheckSignatures());
    EXPECT_FALSE(state.getCheckAuthorizations());
    EXPECT_FALSE(state.getCheckTimestamps());
    EXPECT_FALSE(state.getOnlineValidation());
    EXPECT_FALSE(state.getPrivateKey());
    EXPECT_TRUE(state.getCredential() == pub_key);
}

} // end of anonymous namespace
