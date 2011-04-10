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

#include "crypto.h"

#include <iostream>
#include <iomanip>

#include "crypto_botan.h"
#include <botan/botan.h>
#include <botan/hmac.h>
#include <botan/types.h>

#include <dns/buffer.h>
#include <dns/name.h>
#include <dns/tsigkey.h>
#include <dns/util/base64.h>

#include <string>

using namespace Botan;
using namespace std;
using namespace isc::dns;

namespace {
HashFunction* getHash(const Name& hash_name) {
	if (hash_name == TSIGKey::HMACMD5_NAME()) {
		return get_hash("MD5");
	} else if (hash_name == TSIGKey::HMACSHA1_NAME()) {
		return get_hash("SHA-1");
	} else if (hash_name == TSIGKey::HMACSHA256_NAME()) {
		return get_hash("SHA-256");
	} else {
		isc_throw(isc::InvalidParameter, "Unknown Hash type");
	}
}

}

namespace isc {
namespace crypto {

/*
class TSIGKeyImpl {
public:
    TSIGKeyImpl(const std::string& str) {
        (void) str;
        name_ = new Name("");
        secret_ = NULL;
        secret_length_ = 0;
    };

    TSIGKeyImpl(const isc::dns::Name& name, TSIGKey::algorithms alg,
                const char* secret, size_t secret_length) :
                    name_(new Name(name)), algorithm_(alg),
                    secret_length_(secret_length)
    {
        secret_ = (char*)malloc(secret_length_);
        memcpy(secret_, secret, secret_length_);
    }
    ~TSIGKeyImpl() { delete secret_; delete name_; };

    TSIGKey::algorithms getAlgorithm() { return algorithm_; }
    const char* getSecret() const { return secret_; }
    size_t getSecretLength() const { return secret_length_; }
    
private:
    isc::dns::Name* name_;
    TSIGKey::algorithms algorithm_;
    char* secret_;
    size_t secret_length_;
};

TSIGKey::TSIGKey(const std::string& str) {
    impl_ = new TSIGKeyImpl(str);
}

TSIGKey::algorithms
TSIGKey::getAlgorithm() {
    return impl_->getAlgorithm();
}

const char*
TSIGKey::getSecret() {
    return impl_->getSecret();
}

size_t
TSIGKey::getSecretLength() {
    return impl_->getSecretLength();
}
*/

void doHMAC(const OutputBuffer& data, TSIGKey key, isc::dns::OutputBuffer& result) {

    // needs to be in global scope; can we make a generalized
    // subclassable singleton? (for hsm we'll need more initialization)
    LibraryInitializer init;

    // not used here, but we'd need a ctx

    // should get algorithm from key, then 'translate' to Botan-specific algo
    HashFunction* hash = getHash(key.getAlgorithmName());
    HMAC::HMAC hmac(hash);

    // Take the 'secret' from the key
    hmac.set_key(static_cast<const byte*>(key.getSecret()), key.getSecretLength());

    // update the data from whatever we get (probably as a buffer)
    hmac.update(static_cast<const byte*>(data.getData()), data.getLength());

    // And generate the mac
    SecureVector<byte> b_result(hmac.final());

    // just some debug
    std::cout << "DATA (" << data.getLength() << "): ";
    const uint8_t *d= static_cast<const uint8_t*>(data.getData());
    for(size_t s = 0; s < data.getLength(); ++s) {
        std::cout << hex << setfill('0') << setw(2) << nouppercase << (unsigned int)d[s] << " ";
    }
    std::cout << std::endl;
    std::cout << "KEY (" << (int)key.getSecretLength() << "): ";
    const uint8_t *k = static_cast<const uint8_t*>(key.getSecret());
    for(size_t s = 0; s < key.getSecretLength(); ++s) {
		std::cout << s << ": ";
        std::cout << hex << setfill('0') << setw(2) << nouppercase << (unsigned int)k[s] << " ";
		std::cout << std::endl;
    }
    std::cout << std::endl;
    std::cout << "HASH: ";
    for(byte* i = b_result.begin(); i != b_result.end(); ++i) {
        std::cout << hex << setfill('0') << setw(2) << nouppercase << (unsigned int)(*i);
    }
    std::cout << std::endl;

    // write mac to result
    result.writeData(b_result.begin(), b_result.size());

    std::cout << "HMAC SIG LEN: " << b_result.size() << std::endl;
    std::cout << "HMAC SIG LEN2: " << result.getLength() << std::endl;
}

bool verifyHMAC(const OutputBuffer& data, TSIGKey key, const isc::dns::OutputBuffer& result) {
    HashFunction* hash = getHash(key.getAlgorithmName());
    HMAC::HMAC hmac(hash);
    hmac.set_key(static_cast<const byte*>(key.getSecret()), key.getSecretLength());
    hmac.update(static_cast<const byte*>(data.getData()), data.getLength());

    return hmac.verify_mac(static_cast<const byte*>(result.getData()), result.getLength());
}

isc::dns::TSIGKey
TSIGKeyFromString(const std::string& str) {
	size_t pos = str.find(':');
	if (pos == 0 || pos == str.npos) {
		// error, TODO: raise
		isc_throw(InvalidParameter, "Invalid TSIG key string");
	}
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

	///*
	std::cout << "[XX] KEY NAME: " << key_name << std::endl;
	std::cout << "[XX] KEY ALGO: " << algo_name << std::endl;
	std::cout << "[XX] SECRET:   " << secret_str << std::endl;
	//*/
	vector<uint8_t> secret;
	decodeBase64(secret_str, secret);
	unsigned char secret_b[secret.size()];
	for (size_t i=0; i < secret.size(); ++i) {
		secret_b[i] = secret[i];
	}
	return isc::dns::TSIGKey(key_name, algo_name, secret_b, secret.size());
}

std::string
TSIGKeyToString(const isc::dns::TSIGKey& key) {
	const uint8_t* secret_b = static_cast<const uint8_t*>(key.getSecret());
	vector<uint8_t> secret_v;
	for (size_t i=0; i < key.getSecretLength(); ++i) {
		secret_v.push_back(secret_b[i]);
	}
	std::string secret_str = encodeBase64(secret_v);
	
	return key.getKeyName().toText() + ":" + secret_str + ":" + key.getAlgorithmName().toText();
}


} // namespace crypto
} // namespace isc

