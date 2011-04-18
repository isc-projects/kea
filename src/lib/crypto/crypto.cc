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

#include <botan/botan.h>
#include <botan/hmac.h>
#include <botan/hash.h>
#include <botan/types.h>

#include <dns/buffer.h>
#include <dns/name.h>
#include <dns/util/base64.h>

#include <string>

using namespace std;
using namespace isc::dns;

namespace {
const char*
getBotanHashAlgorithmName(isc::crypto::HMAC::HashAlgorithm algorithm) {
    switch (algorithm) {
    case isc::crypto::HMAC::MD5:
        return ("MD5");
        break;
    case isc::crypto::HMAC::SHA1:
        return ("SHA-1");
        break;
    case isc::crypto::HMAC::SHA256:
        return ("SHA-256");
        break;
    case isc::crypto::HMAC::UNKNOWN:
        return ("Unknown");
        break;
    }
    // compiler should have prevented us to reach this, since we have
    // no default. But we need a return value anyway
    return ("Unknown");
}

} // local namespace

namespace isc {
namespace crypto {

// For Botan, we use the Crypto class object in RAII style
class CryptoImpl {
public:
    CryptoImpl() {}
    ~CryptoImpl() {};

private:
    Botan::LibraryInitializer _botan_init;
};

Crypto::Crypto() {
    try {
        impl_ = new CryptoImpl();
    } catch (const Botan::Exception& ex) {
        isc_throw(InitializationError, ex.what());
    }
}

Crypto::~Crypto() {
    delete impl_;
}


class HMACImpl {
public:
    explicit HMACImpl(const void* secret, size_t secret_len,
                      const HMAC::HashAlgorithm hash_algorithm) {
        Botan::HashFunction* hash;
        try {
            hash = Botan::get_hash(
                getBotanHashAlgorithmName(hash_algorithm));
        } catch (const Botan::Algorithm_Not_Found&) {
            isc_throw(isc::crypto::UnsupportedAlgorithm,
                      "Unknown hash algorithm: " + hash_algorithm);
        }

        hmac_ = new Botan::HMAC::HMAC(hash);

        // If the key length is larger than the block size, we hash the
        // key itself first.
        try {
            if (secret_len > hash->HASH_BLOCK_SIZE) {
                Botan::SecureVector<Botan::byte> hashed_key =
                    hash->process(static_cast<const Botan::byte*>(secret),
                                  secret_len);
                hmac_->set_key(hashed_key.begin(), hashed_key.size());
            } else {
                hmac_->set_key(static_cast<const Botan::byte*>(secret),
                               secret_len);
            }
        } catch (const Botan::Invalid_Key_Length& ikl) {
            delete hmac_;
            isc_throw(BadKey, ikl.what());
        }
    }

    ~HMACImpl() { delete hmac_; }

    size_t getOutputLength() const {
        return (hmac_->OUTPUT_LENGTH);
    }

    void update(const void* data, const size_t len) {
        hmac_->update(static_cast<const Botan::byte*>(data), len);
    }

    void sign(isc::dns::OutputBuffer& result, size_t len) {
        Botan::SecureVector<Botan::byte> b_result(hmac_->final());

        if (len == 0 || len > b_result.size()) {
            len = b_result.size();
        }
        result.writeData(b_result.begin(), len);
    }

    void sign(void* result, size_t len) {
        Botan::SecureVector<Botan::byte> b_result(hmac_->final());
        size_t output_size = getOutputLength();
        if (output_size > len) {
            output_size = len;
        }
        memcpy(result, b_result.begin(), output_size);
    }

    std::vector<uint8_t> sign(size_t len) {
        Botan::SecureVector<Botan::byte> b_result(hmac_->final());
        if (len == 0 || len > b_result.size()) {
            return(std::vector<uint8_t>(b_result.begin(), b_result.end()));
        } else {
            return(std::vector<uint8_t>(b_result.begin(), &b_result[len]));
        }
    }


    bool verify(const void* sig, size_t len) {
        // Botan's verify_mac checks if len matches the output_length,
        // which causes it to fail for truncated signatures, so we do
        // the check ourselves
        Botan::SecureVector<Botan::byte> our_mac = hmac_->final();
        if (len == 0 || len > getOutputLength()) {
            len = getOutputLength();
        }
        return (Botan::same_mem(&our_mac[0],
                                static_cast<const unsigned char*>(sig),
                                len));
    }

private:
    Botan::HMAC* hmac_;
};

HMAC::HMAC(const void* secret, size_t secret_length,
           const HashAlgorithm hash_algorithm)
{
    impl_ = new HMACImpl(secret, secret_length, hash_algorithm);
}

HMAC::~HMAC() {
    delete impl_;
}

size_t
HMAC::getOutputLength() const {
    return (impl_->getOutputLength());
}

void
HMAC::update(const void* data, const size_t len) {
    impl_->update(data, len);
}

void
HMAC::sign(isc::dns::OutputBuffer& result, size_t len) {
    impl_->sign(result, len);
}

void
HMAC::sign(void* result, size_t len) {
    impl_->sign(result, len);
}

std::vector<uint8_t>
HMAC::sign(size_t len) {
    return impl_->sign(len);
}

bool
HMAC::verify(const void* sig, const size_t len) {
    return (impl_->verify(sig, len));
}

void
signHMAC(const void* data, size_t data_len, const void* secret,
         size_t secret_len, const HMAC::HashAlgorithm hash_algorithm,
         isc::dns::OutputBuffer& result, size_t len)
{
    HMAC hmac(secret, secret_len, hash_algorithm);
    hmac.update(data, data_len);
    hmac.sign(result, len);
}


bool
verifyHMAC(const void* data, const size_t data_len, const void* secret,
           size_t secret_len, const HMAC::HashAlgorithm hash_algorithm,
           const void* sig, const size_t sig_len)
{
    HMAC hmac(secret, secret_len, hash_algorithm);
    hmac.update(data, data_len);
    return (hmac.verify(sig, sig_len));
}

} // namespace crypto
} // namespace isc

