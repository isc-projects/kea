// Copyright (C) 2010  Internet Systems Consortium, Inc. ("ISC")
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

// $Id: rrtype_unittest.cc 476 2010-01-19 00:29:28Z jinmei $

#include <string>

#include <gtest/gtest.h>

#include <exceptions/exceptions.h>

#include <dns/tsig.h>

#include <dns/tests/unittest_util.h>

using namespace std;
using namespace isc::dns;
using isc::UnitTestUtil;

namespace {
class TSIGKeyTest : public ::testing::Test {
protected:
    TSIGKeyTest() : secret("someRandomData"), key_name("example.com") {}
    string secret;
    Name key_name;
};

TEST_F(TSIGKeyTest, algorithmNames) {
    EXPECT_EQ(Name("hmac-md5.sig-alg.reg.int"), TSIGKey::HMACMD5_NAME());
    EXPECT_EQ(Name("hmac-sha1"), TSIGKey::HMACSHA1_NAME());
    EXPECT_EQ(Name("hmac-sha256"), TSIGKey::HMACSHA256_NAME());
}

TEST_F(TSIGKeyTest, construct) {
    TSIGKey key(key_name, TSIGKey::HMACMD5_NAME(),
                secret.c_str(), secret.size());
    EXPECT_EQ(key_name, key.getKeyName());
    EXPECT_EQ(Name("hmac-md5.sig-alg.reg.int"), key.getAlgorithmName());
    EXPECT_PRED_FORMAT4(UnitTestUtil::matchWireData, secret.c_str(),
                        secret.size(), key.getSecret(), key.getSecretLength());

    EXPECT_THROW(TSIGKey(key_name, Name("unknown-alg"),
                         secret.c_str(), secret.size()),
                 isc::InvalidParameter);

    // The algorithm name should be converted to the canonical form.
    EXPECT_EQ("hmac-sha1.",
              TSIGKey(key_name, Name("HMAC-sha1"),
                      secret.c_str(),
                      secret.size()).getAlgorithmName().toText());

    // Invalid combinations of secret and secret_len:
    EXPECT_THROW(TSIGKey(key_name, TSIGKey::HMACSHA1_NAME(), secret.c_str(), 0),
                 isc::InvalidParameter);
    EXPECT_THROW(TSIGKey(key_name, TSIGKey::HMACSHA256_NAME(), NULL, 16),
                 isc::InvalidParameter);
}

void
compareTSIGKeys(const TSIGKey& expect, const TSIGKey& actual) {
    EXPECT_EQ(expect.getKeyName(), actual.getKeyName());
    EXPECT_EQ(expect.getAlgorithmName(), actual.getAlgorithmName());
    EXPECT_PRED_FORMAT4(UnitTestUtil::matchWireData,
                        expect.getSecret(), expect.getSecretLength(),
                        actual.getSecret(), actual.getSecretLength());
}

TEST_F(TSIGKeyTest, copyConstruct) {
    const TSIGKey original(key_name, TSIGKey::HMACSHA256_NAME(),
                           secret.c_str(), secret.size());
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
                           secret.c_str(), secret.size());
    TSIGKey copy = original;
    compareTSIGKeys(original, copy);

    // Check if the copied data is valid even after the original is deleted
    TSIGKey* copy2 = new TSIGKey(original);
    TSIGKey copy3 = *copy2;
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
        secretstring("anotherRandomData"),
        secret(secretstring.c_str()),
        secret_len(secretstring.size())
    {}
    TSIGKeyRing keyring;
    Name key_name;
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
    // keys are identified their names, the same name of key with a different
    // algorithm would be considered a duplicate.
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
    EXPECT_EQ(TSIGKeyRing::NOTFOUND, keyring.find(key_name).code);
    EXPECT_EQ(static_cast<const TSIGKey*>(NULL), keyring.find(key_name).key);

    EXPECT_EQ(TSIGKeyRing::SUCCESS, keyring.add(
                  TSIGKey(key_name, TSIGKey::HMACSHA256_NAME(),
                          secret, secret_len)));
    const TSIGKeyRing::FindResult result(keyring.find(key_name));
    EXPECT_EQ(TSIGKeyRing::SUCCESS, result.code);
    EXPECT_EQ(key_name, result.key->getKeyName());
    EXPECT_EQ(TSIGKey::HMACSHA256_NAME(), result.key->getAlgorithmName());
    EXPECT_PRED_FORMAT4(UnitTestUtil::matchWireData, secret, secret_len,
                        result.key->getSecret(),
                        result.key->getSecretLength());
}

TEST_F(TSIGKeyRingTest, findFromSome) {
    // essentially the same test, but search a larger set

    EXPECT_EQ(TSIGKeyRing::SUCCESS, keyring.add(
                  TSIGKey(key_name, TSIGKey::HMACSHA256_NAME(),
                          secret, secret_len)));
    EXPECT_EQ(TSIGKeyRing::SUCCESS, keyring.add(
                  TSIGKey(Name("another.example"), TSIGKey::HMACMD5_NAME(),
                          secret, secret_len)));
    EXPECT_EQ(TSIGKeyRing::SUCCESS, keyring.add(
                  TSIGKey(Name("more.example"), TSIGKey::HMACSHA1_NAME(),
                          secret, secret_len)));

    const TSIGKeyRing::FindResult result(
        keyring.find(Name("another.example")));
    EXPECT_EQ(TSIGKeyRing::SUCCESS, result.code);
    EXPECT_EQ(Name("another.example"), result.key->getKeyName());
    EXPECT_EQ(TSIGKey::HMACMD5_NAME(), result.key->getAlgorithmName());

    EXPECT_EQ(TSIGKeyRing::NOTFOUND,
              keyring.find(Name("noexist.example")).code);
    EXPECT_EQ(static_cast<const TSIGKey*>(NULL),
              keyring.find(Name("noexist.example")).key);
}

} // end namespace
