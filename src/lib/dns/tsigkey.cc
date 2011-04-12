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

#include <exceptions/exceptions.h>

#include <dns/name.h>
#include <dns/util/base64.h>
#include <dns/tsigkey.h>

using namespace std;

namespace isc {
namespace dns {
struct
TSIGKey::TSIGKeyImpl {
    TSIGKeyImpl(const Name& key_name, const Name& algorithm_name,
                const void* secret, size_t secret_len) :
        key_name_(key_name), algorithm_name_(algorithm_name),
        secret_(static_cast<const uint8_t*>(secret),
                static_cast<const uint8_t*>(secret) + secret_len)
    {
        // Convert the name to the canonical form.
        algorithm_name_.downcase();
    }
    const Name key_name_;
    Name algorithm_name_;
    const vector<uint8_t> secret_;
};

TSIGKey::TSIGKey(const Name& key_name, const Name& algorithm_name,
                 const void* secret, size_t secret_len) : impl_(NULL)
{
    if (algorithm_name != HMACMD5_NAME() &&
        algorithm_name != HMACSHA1_NAME() &&
        algorithm_name != HMACSHA256_NAME()) {
        isc_throw(InvalidParameter, "Unknown TSIG algorithm is specified: " <<
                  algorithm_name);
    }
    if ((secret != NULL && secret_len == 0) ||
        (secret == NULL && secret_len != 0)) {
        isc_throw(InvalidParameter,
                  "TSIGKey secret and its length are inconsistent");
    }

    impl_ = new TSIGKeyImpl(key_name, algorithm_name, secret, secret_len);
}

TSIGKey::TSIGKey(const std::string& str) : impl_(NULL) {
    size_t pos = str.find(':');
    if (pos == 0 || pos == str.npos) {
        // error
        isc_throw(InvalidParameter, "Invalid TSIG key string");
    }
    try {
        Name key_name(str.substr(0, pos));
        Name algo_name("hmac-md5.sig-alg.reg.int");

        // optional algorithm part
        size_t pos2 = str.find(':', pos+1);
        if (pos2 != str.npos) {
            if (pos2 == pos + 1) {
                isc_throw(InvalidParameter, "Invalid TSIG key string");
            }
            algo_name = Name(str.substr(pos2+1));
        } else {
            pos2 = str.size() - pos;
        }

        std::string secret_str = str.substr(pos + 1, pos2 - pos - 1);

        vector<uint8_t> secret;
        decodeBase64(secret_str, secret);
        unsigned char secret_b[secret.size()];
        for (size_t i=0; i < secret.size(); ++i) {
            secret_b[i] = secret[i];
        }

        if (algo_name != HMACMD5_NAME() &&
            algo_name != HMACSHA1_NAME() &&
            algo_name != HMACSHA256_NAME()) {
            isc_throw(InvalidParameter, "Unknown TSIG algorithm is specified: " <<
                      algo_name);
        }

        impl_ = new TSIGKeyImpl(key_name, algo_name, secret_b,
                                secret.size());
    } catch (Exception e) {
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
    const uint8_t* secret_b = static_cast<const uint8_t*>(getSecret());
    vector<uint8_t> secret_v;
    for (size_t i=0; i < getSecretLength(); ++i) {
        secret_v.push_back(secret_b[i]);
    }
    std::string secret_str = encodeBase64(secret_v);

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
TSIGKeyRing::find(const Name& key_name) {
    TSIGKeyRingImpl::TSIGKeyMap::const_iterator found =
        impl_->keys.find(key_name);
    if (found == impl_->keys.end()) {
        return (FindResult(NOTFOUND, NULL));
    }
    return (FindResult(SUCCESS, &((*found).second)));
}

} // namespace dns
} // namespace isc
