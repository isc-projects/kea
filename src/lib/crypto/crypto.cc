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
#include <string>

using namespace Botan;
using namespace std;
using namespace isc::dns;

namespace isc {
namespace crypto {

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

} // namespace crypto
} // namespace isc

void doHMAC(const OutputBuffer& data, char* key, isc::dns::OutputBuffer& result) {

    // needs to be in global scope; can we make a generalized
    // subclassable singleton? (for hsm we'll need more initialization)
    LibraryInitializer init;

    // not used here, but we'd need a ctx

    // should get algorithm from key, then 'translate' to Botan-specific algo
    HashFunction* hash = get_hash("SHA-256");
    HMAC::HMAC hmac(hash);

    // update the data from whatever we get (probably as a buffer)
    hmac.update(reinterpret_cast<const byte*>(data.getData()), data.getLength());

    // Take the 'secret' from the key
    hmac.set_key(reinterpret_cast<byte*>(key), 3);

    // And generate the mac
    SecureVector<byte> b_result(hmac.final());

    // just some debug
    for(byte* i = b_result.begin(); i != b_result.end(); ++i) {
        std::cout << hex << setfill('0') << setw(2) << nouppercase << (unsigned int)(*i);
    }
    std::cout << std::endl;

    // write mac to result
    result.writeData(b_result.begin(), b_result.size());

    std::cout << "HMAC SIG LEN: " << b_result.size() << std::endl;
    std::cout << "HMAC SIG LEN2: " << result.getLength() << std::endl;
}

bool verifyHMAC(const OutputBuffer& data, char* key, const isc::dns::OutputBuffer& result) {
    HashFunction* hash = get_hash("SHA-256");
    HMAC::HMAC hmac(hash);
    hmac.update(reinterpret_cast<const byte*>(data.getData()), data.getLength());
    hmac.set_key(reinterpret_cast<byte*>(key), 3);

    SecureVector<byte> b_result(hmac.final());
    for(byte* i = b_result.begin(); i != b_result.end(); ++i) {
        std::cout << hex << setfill('0') << setw(2) << nouppercase << (unsigned int)(*i);
    }
    std::cout << std::endl;

    std::cout << "HMAC SIG LEN3: " << result.getLength() << std::endl;
    return hmac.verify_mac(reinterpret_cast<const byte*>(result.getData()), result.getLength());
}
