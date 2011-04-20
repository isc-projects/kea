
#include <crypto.h>

#include <boost/scoped_ptr.hpp>

#include <botan/botan.h>
#include <botan/hmac.h>
#include <botan/hash.h>
#include <botan/types.h>

namespace {
const char*
getBotanHashAlgorithmName(isc::cryptolink::HMAC::HashAlgorithm algorithm) {
    switch (algorithm) {
    case isc::cryptolink::HMAC::MD5:
        return ("MD5");
        break;
    case isc::cryptolink::HMAC::SHA1:
        return ("SHA-1");
        break;
    case isc::cryptolink::HMAC::SHA256:
        return ("SHA-256");
        break;
    case isc::cryptolink::HMAC::UNKNOWN:
        return ("Unknown");
        break;
    }
    // compiler should have prevented us to reach this, since we have
    // no default. But we need a return value anyway
    return ("Unknown");
}

} // local namespace


namespace isc {
namespace cryptolink {

class HMACImpl {
public:
    explicit HMACImpl(const void* secret, size_t secret_len,
                      const HMAC::HashAlgorithm hash_algorithm) {
        Botan::HashFunction* hash;
        try {
            hash = Botan::get_hash(
                getBotanHashAlgorithmName(hash_algorithm));
        } catch (const Botan::Algorithm_Not_Found&) {
            isc_throw(isc::cryptolink::UnsupportedAlgorithm,
                      "Unknown hash algorithm: " + hash_algorithm);
        }

        hmac_.reset(new Botan::HMAC::HMAC(hash));

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
            isc_throw(BadKey, ikl.what());
        }
    }

    ~HMACImpl() { }

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
            return (std::vector<uint8_t>(b_result.begin(), b_result.end()));
        } else {
            return (std::vector<uint8_t>(b_result.begin(), &b_result[len]));
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
    boost::scoped_ptr<Botan::HMAC> hmac_;
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

} // namespace cryptolink
} // namespace isc
