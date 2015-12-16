// Copyright (C) 2010-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <string>

#include <gtest/gtest.h>

#include <exceptions/exceptions.h>

#include <cryptolink/cryptolink.h>

#include <dns/tsigkey.h>

#include <dns/tests/unittest_util.h>
#include <util/unittests/wiredata.h>

using namespace std;
using namespace isc::dns;
using isc::UnitTestUtil;
using isc::util::unittests::matchWireData;

namespace {
class TSIGKeyTest : public ::testing::Test {
protected:
    TSIGKeyTest() : secret("someRandomData"), key_name("example.com") {}
    string secret;
    const Name key_name;
};

TEST_F(TSIGKeyTest, algorithmNames) {
    EXPECT_EQ(Name("hmac-md5.sig-alg.reg.int"), TSIGKey::HMACMD5_NAME());
    EXPECT_EQ(Name("hmac-md5"), TSIGKey::HMACMD5_SHORT_NAME());
    EXPECT_EQ(Name("hmac-sha1"), TSIGKey::HMACSHA1_NAME());
    EXPECT_EQ(Name("hmac-sha256"), TSIGKey::HMACSHA256_NAME());
    EXPECT_EQ(Name("hmac-sha224"), TSIGKey::HMACSHA224_NAME());
    EXPECT_EQ(Name("hmac-sha384"), TSIGKey::HMACSHA384_NAME());
    EXPECT_EQ(Name("hmac-sha512"), TSIGKey::HMACSHA512_NAME());

    // Also check conversion to cryptolink definitions
    EXPECT_EQ(isc::cryptolink::MD5, TSIGKey(key_name, TSIGKey::HMACMD5_NAME(),
                                            NULL, 0).getAlgorithm());
    EXPECT_EQ(isc::cryptolink::MD5,
              TSIGKey(key_name, TSIGKey::HMACMD5_SHORT_NAME(),
                      NULL, 0).getAlgorithm());
    EXPECT_EQ(isc::cryptolink::SHA1, TSIGKey(key_name, TSIGKey::HMACSHA1_NAME(),
                                             NULL, 0).getAlgorithm());
    EXPECT_EQ(isc::cryptolink::SHA256, TSIGKey(key_name,
                                               TSIGKey::HMACSHA256_NAME(),
                                               NULL, 0).getAlgorithm());
    EXPECT_EQ(isc::cryptolink::SHA224, TSIGKey(key_name,
                                               TSIGKey::HMACSHA224_NAME(),
                                               NULL, 0).getAlgorithm());
    EXPECT_EQ(isc::cryptolink::SHA384, TSIGKey(key_name,
                                               TSIGKey::HMACSHA384_NAME(),
                                               NULL, 0).getAlgorithm());
    EXPECT_EQ(isc::cryptolink::SHA512, TSIGKey(key_name,
                                               TSIGKey::HMACSHA512_NAME(),
                                               NULL, 0).getAlgorithm());
}

TEST_F(TSIGKeyTest, construct) {
    TSIGKey key(key_name, TSIGKey::HMACMD5_NAME(),
                secret.c_str(), secret.size());
    EXPECT_EQ(key_name, key.getKeyName());
    EXPECT_EQ(Name("hmac-md5.sig-alg.reg.int"), key.getAlgorithmName());
    matchWireData(secret.c_str(), secret.size(),
                  key.getSecret(), key.getSecretLength());

    TSIGKey key_short_md5(key_name, TSIGKey::HMACMD5_SHORT_NAME(),
                          secret.c_str(), secret.size());
    EXPECT_EQ(key_name, key_short_md5.getKeyName());
    EXPECT_EQ(Name("hmac-md5.sig-alg.reg.int"),
              key_short_md5.getAlgorithmName());
    matchWireData(secret.c_str(), secret.size(),
                  key_short_md5.getSecret(), key_short_md5.getSecretLength());

    // "unknown" algorithm is only accepted with empty secret.
    EXPECT_THROW(TSIGKey(key_name, Name("unknown-alg"),
                         secret.c_str(), secret.size()),
                 isc::InvalidParameter);
    TSIGKey key2(key_name, Name("unknown-alg"), NULL, 0);
    EXPECT_EQ(key_name, key2.getKeyName());
    EXPECT_EQ(Name("unknown-alg"), key2.getAlgorithmName());

    // The algorithm name should be converted to the canonical form.
    EXPECT_EQ("hmac-sha1.",
              TSIGKey(key_name, Name("HMAC-sha1"),
                      secret.c_str(),
                      secret.size()).getAlgorithmName().toText());

    // Same for key name
    EXPECT_EQ("example.com.",
              TSIGKey(Name("EXAMPLE.CoM."), TSIGKey::HMACSHA256_NAME(),
                      secret.c_str(),
                      secret.size()).getKeyName().toText());

    // Check digestbits
    EXPECT_EQ(key.getDigestbits(), 0);
    TSIGKey key_trunc(key_name, TSIGKey::HMACMD5_NAME(),
                      secret.c_str(), secret.size(), 120);
    EXPECT_EQ(key_trunc.getDigestbits(), 120);

    // Invalid combinations of secret and secret_len:
    EXPECT_THROW(TSIGKey(key_name, TSIGKey::HMACSHA1_NAME(), secret.c_str(), 0),
                 isc::InvalidParameter);
    EXPECT_THROW(TSIGKey(key_name, TSIGKey::HMACSHA256_NAME(), NULL, 16),
                 isc::InvalidParameter);

    // Empty secret
    TSIGKey keye = TSIGKey(key_name, TSIGKey::HMACSHA256_NAME(), NULL, 0);
    EXPECT_EQ(keye.getSecretLength(), 0);
    EXPECT_EQ(keye.getSecret(), (const void*)0);
}

void
compareTSIGKeys(const TSIGKey& expect, const TSIGKey& actual) {
    EXPECT_EQ(expect.getKeyName(), actual.getKeyName());
    EXPECT_EQ(expect.getAlgorithmName(), actual.getAlgorithmName());
    EXPECT_EQ(expect.getDigestbits(), actual.getDigestbits());
    matchWireData(expect.getSecret(), expect.getSecretLength(),
                  actual.getSecret(), actual.getSecretLength());
}

TEST_F(TSIGKeyTest, copyConstruct) {
    const TSIGKey original(key_name, TSIGKey::HMACSHA256_NAME(),
                           secret.c_str(), secret.size(), 128);
    const TSIGKey copy(original);
    compareTSIGKeys(original, copy);

    // Check the copied data is valid even after the original is deleted
    TSIGKey* copy2 = new TSIGKey(original);
    TSIGKey copy3(*copy2);
    delete copy2;
    compareTSIGKeys(original, copy3);
}

TEST_F(TSIGKeyTest, assignment) {
    const TSIGKey original(key_name, TSIGKey::HMACSHA256_NAME(),
                           secret.c_str(), secret.size(), 200);
    TSIGKey copy = original;
    compareTSIGKeys(original, copy);

    // Check if the copied data is valid even after the original is deleted
    TSIGKey* copy2 = new TSIGKey(original);
    TSIGKey copy3(original);
    copy3 = *copy2;
    delete copy2;
    compareTSIGKeys(original, copy3);

    // self assignment
    copy = copy;
    compareTSIGKeys(original, copy);
}

class TSIGKeyRingTest : public ::testing::Test {
protected:
    TSIGKeyRingTest() :
        key_name("example.com"),
        md5_name("hmac-md5.sig-alg.reg.int"),
        sha1_name("hmac-sha1"),
        sha256_name("hmac-sha256"),
        secretstring("anotherRandomData"),
        secret(secretstring.c_str()),
        secret_len(secretstring.size())
    {}
    TSIGKeyRing keyring;
    const Name key_name;
    const Name md5_name;
    const Name sha1_name;
    const Name sha256_name;
private:
    const string secretstring;
protected:
    const char* secret;
    size_t secret_len;
};

TEST_F(TSIGKeyRingTest, init) {
    EXPECT_EQ(0, keyring.size());
}

TEST_F(TSIGKeyRingTest, add) {
    EXPECT_EQ(TSIGKeyRing::SUCCESS, keyring.add(
                  TSIGKey(key_name, TSIGKey::HMACSHA256_NAME(),
                          secret, secret_len)));
    EXPECT_EQ(1, keyring.size());
    EXPECT_EQ(TSIGKeyRing::EXIST, keyring.add(
                  TSIGKey(key_name, TSIGKey::HMACSHA256_NAME(),
                          secret, secret_len)));
    // keys are identified by their names, the same name of key with a
    // different algorithm would be considered a duplicate.
    EXPECT_EQ(TSIGKeyRing::EXIST, keyring.add(
                  TSIGKey(Name("example.com"), TSIGKey::HMACSHA1_NAME(),
                          secret, secret_len)));
    // names are compared in a case insensitive manner.
    EXPECT_EQ(TSIGKeyRing::EXIST, keyring.add(
                  TSIGKey(Name("EXAMPLE.COM"), TSIGKey::HMACSHA1_NAME(),
                          secret, secret_len)));
    EXPECT_EQ(1, keyring.size());
}

TEST_F(TSIGKeyRingTest, addMore) {
    // essentially the same test, but try adding more than 1
    EXPECT_EQ(TSIGKeyRing::SUCCESS, keyring.add(
                  TSIGKey(key_name, TSIGKey::HMACSHA256_NAME(),
                          secret, secret_len)));
    EXPECT_EQ(TSIGKeyRing::SUCCESS, keyring.add(
                  TSIGKey(Name("another.example"), TSIGKey::HMACMD5_NAME(),
                          secret, secret_len)));
    EXPECT_EQ(TSIGKeyRing::SUCCESS, keyring.add(
                  TSIGKey(Name("more.example"), TSIGKey::HMACSHA1_NAME(),
                          secret, secret_len)));
    EXPECT_EQ(3, keyring.size());
}

TEST_F(TSIGKeyRingTest, remove) {
    EXPECT_EQ(TSIGKeyRing::SUCCESS, keyring.add(
                  TSIGKey(key_name, TSIGKey::HMACSHA256_NAME(),
                          secret, secret_len)));
    EXPECT_EQ(TSIGKeyRing::SUCCESS, keyring.remove(key_name));
    EXPECT_EQ(TSIGKeyRing::NOTFOUND, keyring.remove(key_name));
}

TEST_F(TSIGKeyRingTest, removeFromSome) {
    // essentially the same test, but try removing from a larger set

    EXPECT_EQ(TSIGKeyRing::SUCCESS, keyring.add(
                  TSIGKey(key_name, TSIGKey::HMACSHA256_NAME(),
                          secret, secret_len)));
    EXPECT_EQ(TSIGKeyRing::SUCCESS, keyring.add(
                  TSIGKey(Name("another.example"), TSIGKey::HMACMD5_NAME(),
                          secret, secret_len)));
    EXPECT_EQ(TSIGKeyRing::SUCCESS, keyring.add(
                  TSIGKey(Name("more.example"), TSIGKey::HMACSHA1_NAME(),
                          secret, secret_len)));

    EXPECT_EQ(TSIGKeyRing::SUCCESS, keyring.remove(Name("another.example")));
    EXPECT_EQ(TSIGKeyRing::NOTFOUND, keyring.remove(Name("noexist.example")));
    EXPECT_EQ(2, keyring.size());
}

TEST_F(TSIGKeyRingTest, find) {
    // If the keyring is empty the search should fail.
    EXPECT_EQ(TSIGKeyRing::NOTFOUND, keyring.find(key_name, md5_name).code);
    EXPECT_EQ(static_cast<const TSIGKey*>(NULL),
              keyring.find(key_name, md5_name).key);

    // Add a key and try to find it.  Should succeed.
    EXPECT_EQ(TSIGKeyRing::SUCCESS, keyring.add(TSIGKey(key_name, sha256_name,
                                                        secret, secret_len)));
    const TSIGKeyRing::FindResult result1(keyring.find(key_name, sha256_name));
    EXPECT_EQ(TSIGKeyRing::SUCCESS, result1.code);
    EXPECT_EQ(key_name, result1.key->getKeyName());
    EXPECT_EQ(TSIGKey::HMACSHA256_NAME(), result1.key->getAlgorithmName());
    matchWireData(secret, secret_len,
                  result1.key->getSecret(), result1.key->getSecretLength());

    // If either key name or algorithm doesn't match, search should fail.
    const TSIGKeyRing::FindResult result2 =
        keyring.find(Name("different-key.example"), sha256_name);
    EXPECT_EQ(TSIGKeyRing::NOTFOUND, result2.code);
    EXPECT_EQ(static_cast<const TSIGKey*>(NULL), result2.key);

    const TSIGKeyRing::FindResult result3 = keyring.find(key_name, md5_name);
    EXPECT_EQ(TSIGKeyRing::NOTFOUND, result3.code);
    EXPECT_EQ(static_cast<const TSIGKey*>(NULL), result3.key);

    // But with just the name it should work
    const TSIGKeyRing::FindResult result4(keyring.find(key_name));
    EXPECT_EQ(TSIGKeyRing::SUCCESS, result4.code);
    EXPECT_EQ(key_name, result4.key->getKeyName());
    EXPECT_EQ(TSIGKey::HMACSHA256_NAME(), result4.key->getAlgorithmName());
    matchWireData(secret, secret_len,
                  result4.key->getSecret(), result4.key->getSecretLength());
}

TEST_F(TSIGKeyRingTest, findFromSome) {
    // essentially the same test, but search a larger set

    EXPECT_EQ(TSIGKeyRing::SUCCESS, keyring.add(TSIGKey(key_name, sha256_name,
                                                        secret, secret_len)));
    EXPECT_EQ(TSIGKeyRing::SUCCESS, keyring.add(TSIGKey(Name("another.example"),
                                                        md5_name,
                                                        secret, secret_len)));
    EXPECT_EQ(TSIGKeyRing::SUCCESS, keyring.add(TSIGKey(Name("more.example"),
                                                        sha1_name,
                                                        secret, secret_len)));

    const TSIGKeyRing::FindResult result(
        keyring.find(Name("another.example"), md5_name));
    EXPECT_EQ(TSIGKeyRing::SUCCESS, result.code);
    EXPECT_EQ(Name("another.example"), result.key->getKeyName());
    EXPECT_EQ(TSIGKey::HMACMD5_NAME(), result.key->getAlgorithmName());

    EXPECT_EQ(TSIGKeyRing::NOTFOUND,
              keyring.find(Name("noexist.example"), sha1_name).code);
    EXPECT_EQ(static_cast<const TSIGKey*>(NULL),
              keyring.find(Name("noexist.example"), sha256_name).key);

    EXPECT_EQ(TSIGKeyRing::NOTFOUND,
              keyring.find(Name("another.example"), sha1_name).code);
    EXPECT_EQ(static_cast<const TSIGKey*>(NULL),
              keyring.find(Name("another.example"), sha256_name).key);
}

TEST(TSIGStringTest, TSIGKeyFromToString) {
    TSIGKey k1 = TSIGKey("test.example:MSG6Ng==:hmac-md5.sig-alg.reg.int");
    TSIGKey k2 = TSIGKey("test.example.:MSG6Ng==:hmac-md5.sig-alg.reg.int.");
    TSIGKey k3 = TSIGKey("test.example:MSG6Ng==");
    TSIGKey k4 = TSIGKey("test.example.:MSG6Ng==:hmac-md5.sig-alg.reg.int.:120");
    TSIGKey k5 = TSIGKey(Name("test.example."), Name("hmac-sha1."), NULL, 0);
    // "Unknown" key with empty secret is okay
    TSIGKey k6 = TSIGKey("test.example.::unknown");

    EXPECT_EQ("test.example.:MSG6Ng==:hmac-md5.sig-alg.reg.int.",
              k1.toText());
    EXPECT_EQ("test.example.:MSG6Ng==:hmac-md5.sig-alg.reg.int.",
              k2.toText());
    EXPECT_EQ("test.example.:MSG6Ng==:hmac-md5.sig-alg.reg.int.",
              k3.toText());
    EXPECT_EQ("test.example.:MSG6Ng==:hmac-md5.sig-alg.reg.int.:120",
              k4.toText());
    EXPECT_EQ(120, k4.getDigestbits());
    EXPECT_EQ("test.example.::hmac-sha1.", k5.toText());
    EXPECT_EQ(Name("test.example."), k6.getKeyName());
    EXPECT_EQ(Name("unknown"), k6.getAlgorithmName());

    EXPECT_THROW(TSIGKey(""), isc::InvalidParameter);
    EXPECT_THROW(TSIGKey(":"), isc::InvalidParameter);
    EXPECT_THROW(TSIGKey("::"), isc::InvalidParameter);
    EXPECT_THROW(TSIGKey("..:aa:"), isc::InvalidParameter);
    EXPECT_THROW(TSIGKey("test.example:xxxx:"), isc::InvalidParameter);
    EXPECT_THROW(TSIGKey("test.example.::"), isc::InvalidParameter);
    EXPECT_THROW(TSIGKey("test.example.:"), isc::InvalidParameter);
    EXPECT_THROW(TSIGKey("test.example.:MSG6Ng==:"), isc::InvalidParameter);
    EXPECT_THROW(TSIGKey("test.example.:MSG6Ng==:unknown"), isc::InvalidParameter);
    EXPECT_THROW(TSIGKey("test.example.:MSG6Ng==:hmac-md5.sig-alg.reg.int.:"),
                 isc::InvalidParameter);
    EXPECT_THROW(TSIGKey("test.example.:MSG6Ng==:hmac-md5.sig-alg.reg.int.:xxx"),
                 isc::InvalidParameter);
}


} // end namespace
