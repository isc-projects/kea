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

#include <map>
#include <utility>
#include <vector>
#include <sstream>

#include <exceptions/exceptions.h>

#include <cryptolink/cryptolink.h>

#include <dns/name.h>
#include <util/encode/base64.h>
#include <dns/tsigkey.h>

using namespace std;
using namespace isc::cryptolink;

namespace isc {
namespace dns {
namespace {
    HashAlgorithm
    convertAlgorithmName(const isc::dns::Name& name) {
        if (name == TSIGKey::HMACMD5_NAME()) {
            return (isc::cryptolink::MD5);
        }
        if (name == TSIGKey::HMACSHA1_NAME()) {
            return (isc::cryptolink::SHA1);
        }
        if (name == TSIGKey::HMACSHA256_NAME()) {
            return (isc::cryptolink::SHA256);
        }
        isc_throw(InvalidParameter,
                  "Unknown TSIG algorithm is specified: " << name);
    }
}

struct
TSIGKey::TSIGKeyImpl {
    TSIGKeyImpl(const Name& key_name, const Name& algorithm_name,
                isc::cryptolink::HashAlgorithm algorithm,
                const void* secret, size_t secret_len) :
        key_name_(key_name), algorithm_name_(algorithm_name),
        algorithm_(algorithm),
        secret_(static_cast<const uint8_t*>(secret),
                static_cast<const uint8_t*>(secret) + secret_len)
    {
        // Convert the key and algorithm names to the canonical form.
        key_name_.downcase();
        algorithm_name_.downcase();
    }
    Name key_name_;
    Name algorithm_name_;
    const isc::cryptolink::HashAlgorithm algorithm_;
    const vector<uint8_t> secret_;
};

TSIGKey::TSIGKey(const Name& key_name, const Name& algorithm_name,
                 const void* secret, size_t secret_len) : impl_(NULL)
{
    const HashAlgorithm algorithm = convertAlgorithmName(algorithm_name);
    if ((secret != NULL && secret_len == 0) ||
        (secret == NULL && secret_len != 0)) {
        isc_throw(InvalidParameter,
                  "TSIGKey secret and its length are inconsistent");
    }
    impl_ = new TSIGKeyImpl(key_name, algorithm_name, algorithm, secret,
                            secret_len);
}

TSIGKey::TSIGKey(const std::string& str) : impl_(NULL) {
    try {
        istringstream iss(str);

        string keyname_str;
        getline(iss, keyname_str, ':');
        if (iss.fail() || iss.bad() || iss.eof()) {
            isc_throw(InvalidParameter, "Invalid TSIG key string: " << str);
        }

        string secret_str;
        getline(iss, secret_str, ':');
        if (iss.fail() || iss.bad()) {
            isc_throw(InvalidParameter, "Invalid TSIG key string: " << str);
        }

        string algo_str;
        if (!iss.eof()) {
            getline(iss, algo_str);
        }
        if (iss.fail() || iss.bad()) {
            isc_throw(InvalidParameter, "Invalid TSIG key string: " << str);
        }

        const Name algo_name(algo_str.empty() ? "hmac-md5.sig-alg.reg.int" :
                             algo_str);
        const HashAlgorithm algorithm = convertAlgorithmName(algo_name);

        vector<uint8_t> secret;
        isc::util::encode::decodeBase64(secret_str, secret);

        impl_ = new TSIGKeyImpl(Name(keyname_str), algo_name, algorithm,
                                &secret[0], secret.size());
    } catch (const Exception& e) {
        // 'reduce' the several types of exceptions name parsing and
        // Base64 decoding can throw to just the InvalidParameter
        isc_throw(InvalidParameter, e.what());
    }
}


TSIGKey::TSIGKey(const TSIGKey& source) : impl_(new TSIGKeyImpl(*source.impl_))
{}

TSIGKey&
TSIGKey::operator=(const TSIGKey& source) {
    if (impl_ == source.impl_) {
        return (*this);
    }

    TSIGKeyImpl* newimpl = new TSIGKeyImpl(*source.impl_);
    delete impl_;
    impl_ = newimpl;

    return (*this);
}

TSIGKey::~TSIGKey() {
    delete impl_;
}

const Name&
TSIGKey::getKeyName() const {
    return (impl_->key_name_);
}

const Name&
TSIGKey::getAlgorithmName() const {
    return (impl_->algorithm_name_);
}

isc::cryptolink::HashAlgorithm
TSIGKey::getAlgorithm() const {
    return (impl_->algorithm_);
}

const void*
TSIGKey::getSecret() const {
    return ((impl_->secret_.size() > 0) ? &impl_->secret_[0] : NULL);
}

size_t
TSIGKey::getSecretLength() const {
    return (impl_->secret_.size());
}

std::string
TSIGKey::toText() const {
    const vector<uint8_t> secret_v(static_cast<const uint8_t*>(getSecret()),
                                   static_cast<const uint8_t*>(getSecret()) +
                                   getSecretLength());
    std::string secret_str = isc::util::encode::encodeBase64(secret_v);

    return (getKeyName().toText() + ":" + secret_str + ":" +
            getAlgorithmName().toText());
}

const
Name& TSIGKey::HMACMD5_NAME() {
    static Name alg_name("hmac-md5.sig-alg.reg.int");
    return (alg_name);
}

const
Name& TSIGKey::HMACSHA1_NAME() {
    static Name alg_name("hmac-sha1");
    return (alg_name);
}

const
Name& TSIGKey::HMACSHA256_NAME() {
    static Name alg_name("hmac-sha256");
    return (alg_name);
}

struct TSIGKeyRing::TSIGKeyRingImpl {
    typedef map<Name, TSIGKey> TSIGKeyMap;
    typedef pair<Name, TSIGKey> NameAndKey;
    TSIGKeyMap keys;
};

TSIGKeyRing::TSIGKeyRing() : impl_(new TSIGKeyRingImpl) {
}

TSIGKeyRing::~TSIGKeyRing() {
    delete impl_;
}

unsigned int
TSIGKeyRing::size() const {
    return (impl_->keys.size());
}

TSIGKeyRing::Result
TSIGKeyRing::add(const TSIGKey& key) {
    if (impl_->keys.insert(
                TSIGKeyRingImpl::NameAndKey(key.getKeyName(), key)).second
        == true) {
        return (SUCCESS);
    } else {
        return (EXIST);
    }
}

TSIGKeyRing::Result
TSIGKeyRing::remove(const Name& key_name) {
    return (impl_->keys.erase(key_name) == 1 ? SUCCESS : NOTFOUND);
}

TSIGKeyRing::FindResult
TSIGKeyRing::find(const Name& key_name, const Name& algorithm_name) {
    TSIGKeyRingImpl::TSIGKeyMap::const_iterator found =
        impl_->keys.find(key_name);
    if (found == impl_->keys.end() ||
        (*found).second.getAlgorithmName() != algorithm_name) {
        return (FindResult(NOTFOUND, NULL));
    }
    return (FindResult(SUCCESS, &((*found).second)));
}

} // namespace dns
} // namespace isc
