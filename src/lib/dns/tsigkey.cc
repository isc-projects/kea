// Copyright (C) 2010-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <map>
#include <utility>
#include <vector>
#include <sstream>

#include <exceptions/exceptions.h>

#include <cryptolink/cryptolink.h>

#include <dns/name.h>
#include <util/encode/base64.h>
#include <dns/tsigkey.h>

#include <boost/lexical_cast.hpp>

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
        if (name == TSIGKey::HMACMD5_SHORT_NAME()) {
            return (isc::cryptolink::MD5);
        }
        if (name == TSIGKey::HMACSHA1_NAME()) {
            return (isc::cryptolink::SHA1);
        }
        if (name == TSIGKey::HMACSHA256_NAME()) {
            return (isc::cryptolink::SHA256);
        }
        if (name == TSIGKey::HMACSHA224_NAME()) {
            return (isc::cryptolink::SHA224);
        }
        if (name == TSIGKey::HMACSHA384_NAME()) {
            return (isc::cryptolink::SHA384);
        }
        if (name == TSIGKey::HMACSHA512_NAME()) {
            return (isc::cryptolink::SHA512);
        }

        return (isc::cryptolink::UNKNOWN_HASH);
    }
}

struct
TSIGKey::TSIGKeyImpl {
    TSIGKeyImpl(const Name& key_name, const Name& algorithm_name,
                isc::cryptolink::HashAlgorithm algorithm,
                size_t digestbits) :

        key_name_(key_name), algorithm_name_(algorithm_name),
        algorithm_(algorithm), digestbits_(digestbits),
        secret_()
    {
        // Convert the key and algorithm names to the canonical form.
        key_name_.downcase();
        if (algorithm == isc::cryptolink::MD5) {
            algorithm_name_ = TSIGKey::HMACMD5_NAME();
        }
        algorithm_name_.downcase();
    }
    TSIGKeyImpl(const Name& key_name, const Name& algorithm_name,
                isc::cryptolink::HashAlgorithm algorithm,
                size_t digestbits,
                const void* secret, size_t secret_len) :

        key_name_(key_name), algorithm_name_(algorithm_name),
        algorithm_(algorithm), digestbits_(digestbits),
        secret_(static_cast<const uint8_t*>(secret),
                static_cast<const uint8_t*>(secret) + secret_len)
    {
        // Convert the key and algorithm names to the canonical form.
        key_name_.downcase();
        if (algorithm == isc::cryptolink::MD5) {
            algorithm_name_ = TSIGKey::HMACMD5_NAME();
        }
        algorithm_name_.downcase();
    }
    Name key_name_;
    Name algorithm_name_;
    const isc::cryptolink::HashAlgorithm algorithm_;
    size_t digestbits_;
    const vector<uint8_t> secret_;
};

TSIGKey::TSIGKey(const Name& key_name, const Name& algorithm_name,
                 const void* secret, size_t secret_len,
                 size_t digestbits /*= 0*/) : impl_(NULL)
{
    const HashAlgorithm algorithm = convertAlgorithmName(algorithm_name);
    if ((secret != NULL && secret_len == 0) ||
        (secret == NULL && secret_len != 0)) {
        isc_throw(InvalidParameter,
                  "TSIGKey secret and its length are inconsistent: " <<
                  key_name << ":" << algorithm_name);
    }
    if (algorithm == isc::cryptolink::UNKNOWN_HASH && secret_len != 0) {
        isc_throw(InvalidParameter,
                  "TSIGKey with unknown algorithm has non empty secret: " <<
                  key_name << ":" << algorithm_name);
    }
    if (secret == NULL) {
        impl_ = new TSIGKeyImpl(key_name, algorithm_name, algorithm,
                                digestbits);
    } else {
        impl_ = new TSIGKeyImpl(key_name, algorithm_name, algorithm,
                                digestbits, secret, secret_len);
    }
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
            getline(iss, algo_str, ':');
        }
        if (iss.fail() || iss.bad()) {
            isc_throw(InvalidParameter, "Invalid TSIG key string: " << str);
        }

        string dgstbt_str;
        if (!iss.eof()) {
            getline(iss, dgstbt_str);
        }
        if (iss.fail() || iss.bad()) {
            isc_throw(InvalidParameter, "Invalid TSIG key string: " << str);
        }

        const Name algo_name(algo_str.empty() ? "hmac-md5.sig-alg.reg.int" :
                             algo_str);
        const HashAlgorithm algorithm = convertAlgorithmName(algo_name);
        size_t digestbits = 0;
        try {
            if (!dgstbt_str.empty()) {
                digestbits = boost::lexical_cast<size_t>(dgstbt_str);
            }
        } catch (const boost::bad_lexical_cast&) {
            isc_throw(InvalidParameter,
                      "TSIG key with non-numeric digestbits: " << dgstbt_str);
        }

        vector<uint8_t> secret;
        isc::util::encode::decodeBase64(secret_str, secret);

        if (algorithm == isc::cryptolink::UNKNOWN_HASH && !secret.empty()) {
            isc_throw(InvalidParameter,
                      "TSIG key with unknown algorithm has non empty secret: "
                      << str);
        }

        if (secret.empty()) {
            impl_ = new TSIGKeyImpl(Name(keyname_str), algo_name, algorithm,
                                    digestbits);
        } else {
            impl_ = new TSIGKeyImpl(Name(keyname_str), algo_name, algorithm,
                                    digestbits, &secret[0], secret.size());
        }
    } catch (const isc::Exception& e) {
        // 'reduce' the several types of exceptions name parsing and
        // Base64 decoding can throw to just the InvalidParameter
        isc_throw(InvalidParameter, e.what());
    }
}


TSIGKey::TSIGKey(const TSIGKey& source) : impl_(new TSIGKeyImpl(*source.impl_))
{}

TSIGKey&
TSIGKey::operator=(const TSIGKey& source) {
    if (this == &source) {
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

size_t
TSIGKey::getDigestbits() const {
    return (impl_->digestbits_);
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
    size_t digestbits = getDigestbits();
    const vector<uint8_t> secret_v(static_cast<const uint8_t*>(getSecret()),
                                   static_cast<const uint8_t*>(getSecret()) +
                                   getSecretLength());
    std::string secret_str = isc::util::encode::encodeBase64(secret_v);

    if (digestbits) {
        std::string dgstbt_str = boost::lexical_cast<std::string>(static_cast<int>(digestbits));
        return (getKeyName().toText() + ":" + secret_str + ":" +
                getAlgorithmName().toText() + ":" + dgstbt_str);
    } else {
        return (getKeyName().toText() + ":" + secret_str + ":" +
                getAlgorithmName().toText());
    }
}

const
Name& TSIGKey::HMACMD5_NAME() {
    static Name alg_name("hmac-md5.sig-alg.reg.int");
    return (alg_name);
}

const
Name& TSIGKey::HMACMD5_SHORT_NAME() {
    static Name alg_name("hmac-md5");
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

const
Name& TSIGKey::HMACSHA224_NAME() {
    static Name alg_name("hmac-sha224");
    return (alg_name);
}

const
Name& TSIGKey::HMACSHA384_NAME() {
    static Name alg_name("hmac-sha384");
    return (alg_name);
}

const
Name& TSIGKey::HMACSHA512_NAME() {
    static Name alg_name("hmac-sha512");
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
TSIGKeyRing::find(const Name& key_name) const {
    TSIGKeyRingImpl::TSIGKeyMap::const_iterator found =
        impl_->keys.find(key_name);
    if (found == impl_->keys.end()) {
        return (FindResult(NOTFOUND, NULL));
    }
    return (FindResult(SUCCESS, &((*found).second)));
}

TSIGKeyRing::FindResult
TSIGKeyRing::find(const Name& key_name, const Name& algorithm_name) const {
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
