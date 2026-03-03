// Copyright (C) 2025 Ada Logics Ltd.
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
////////////////////////////////////////////////////////////////////////////////
#include <config.h>
#include <fuzzer/FuzzedDataProvider.h>

#include <exceptions/exceptions.h>
#include <cryptolink/cryptolink.h>
#include <cryptolink/crypto_hash.h>
#include <cryptolink/crypto_hmac.h>
#include <cryptolink/crypto_rng.h>

#include <string>
#include <vector>
#include <cstddef>

using namespace isc::cryptolink;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
    if (size < 3) {
        return 0;
    }

    FuzzedDataProvider fdp(data, size);
    
    // Choose which crypto operation to test
    uint8_t path = fdp.ConsumeIntegralInRange<uint8_t>(0, 9);
    
    // Pick a hash algorithm
    HashAlgorithm hash_alg = fdp.PickValueInArray({
        HashAlgorithm::MD5,
        HashAlgorithm::SHA1,
        HashAlgorithm::SHA224,
        HashAlgorithm::SHA256,
        HashAlgorithm::SHA384,
        HashAlgorithm::SHA512
    });
    
    try {
        switch (path) {
            case 0: {
                // Test Hash creation and update
                Hash* hash = CryptoLink::getCryptoLink().createHash(hash_alg);
                if (hash) {
                    std::vector<uint8_t> input_data = fdp.ConsumeRemainingBytes<uint8_t>();
                    if (!input_data.empty()) {
                        hash->update(input_data.data(), input_data.size());
                    }
                    std::vector<uint8_t> digest = hash->final(hash->getOutputLength());
                    delete hash;
                }
                break;
            }
            
            case 1: {
                // Test Hash with multiple updates
                Hash* hash = CryptoLink::getCryptoLink().createHash(hash_alg);
                if (hash) {
                    size_t num_updates = fdp.ConsumeIntegralInRange<size_t>(1, 10);
                    for (size_t i = 0; i < num_updates && fdp.remaining_bytes() > 0; i++) {
                        size_t chunk_size = fdp.ConsumeIntegralInRange<size_t>(0, fdp.remaining_bytes());
                        std::vector<uint8_t> chunk = fdp.ConsumeBytes<uint8_t>(chunk_size);
                        if (!chunk.empty()) {
                            hash->update(chunk.data(), chunk.size());
                        }
                    }
                    std::vector<uint8_t> digest = hash->final(hash->getOutputLength());
                    delete hash;
                }
                break;
            }
            
            case 2: {
                // Test Hash with OutputBuffer
                Hash* hash = CryptoLink::getCryptoLink().createHash(hash_alg);
                if (hash) {
                    std::vector<uint8_t> input_data = fdp.ConsumeBytes<uint8_t>(
                        fdp.ConsumeIntegralInRange<size_t>(0, size)
                    );
                    if (!input_data.empty()) {
                        hash->update(input_data.data(), input_data.size());
                    }
                    isc::util::OutputBuffer result(hash->getOutputLength());
                    size_t len = fdp.ConsumeIntegralInRange<size_t>(0, hash->getOutputLength() * 2);
                    hash->final(result, len);
                    delete hash;
                }
                break;
            }
            
            case 3: {
                // Test Hash with void* result
                Hash* hash = CryptoLink::getCryptoLink().createHash(hash_alg);
                if (hash) {
                    std::vector<uint8_t> input_data = fdp.ConsumeBytes<uint8_t>(
                        fdp.ConsumeIntegralInRange<size_t>(0, size)
                    );
                    if (!input_data.empty()) {
                        hash->update(input_data.data(), input_data.size());
                    }
                    std::vector<uint8_t> result(hash->getOutputLength() * 2);
                    size_t len = fdp.ConsumeIntegralInRange<size_t>(0, result.size());
                    hash->final(result.data(), len);
                    delete hash;
                }
                break;
            }
            
            case 4: {
                // Test HMAC creation and signing
                size_t secret_len = fdp.ConsumeIntegralInRange<size_t>(1, 256);
                std::vector<uint8_t> secret = fdp.ConsumeBytes<uint8_t>(secret_len);
                if (secret.empty()) {
                    secret.push_back(0);  // Ensure non-empty secret
                }
                
                HMAC* hmac = CryptoLink::getCryptoLink().createHMAC(
                    secret.data(), secret.size(), hash_alg
                );
                if (hmac) {
                    std::vector<uint8_t> input_data = fdp.ConsumeRemainingBytes<uint8_t>();
                    if (!input_data.empty()) {
                        hmac->update(input_data.data(), input_data.size());
                    }
                    std::vector<uint8_t> signature = hmac->sign(hmac->getOutputLength());
                    delete hmac;
                }
                break;
            }
            
            case 5: {
                // Test HMAC with multiple updates
                size_t secret_len = fdp.ConsumeIntegralInRange<size_t>(1, 256);
                std::vector<uint8_t> secret = fdp.ConsumeBytes<uint8_t>(secret_len);
                if (secret.empty()) {
                    secret.push_back(0);
                }
                
                HMAC* hmac = CryptoLink::getCryptoLink().createHMAC(
                    secret.data(), secret.size(), hash_alg
                );
                if (hmac) {
                    size_t num_updates = fdp.ConsumeIntegralInRange<size_t>(1, 10);
                    for (size_t i = 0; i < num_updates && fdp.remaining_bytes() > 0; i++) {
                        size_t chunk_size = fdp.ConsumeIntegralInRange<size_t>(0, fdp.remaining_bytes());
                        std::vector<uint8_t> chunk = fdp.ConsumeBytes<uint8_t>(chunk_size);
                        if (!chunk.empty()) {
                            hmac->update(chunk.data(), chunk.size());
                        }
                    }
                    std::vector<uint8_t> signature = hmac->sign(hmac->getOutputLength());
                    delete hmac;
                }
                break;
            }
            
            case 6: {
                // Test HMAC with OutputBuffer
                size_t secret_len = fdp.ConsumeIntegralInRange<size_t>(1, 256);
                std::vector<uint8_t> secret = fdp.ConsumeBytes<uint8_t>(secret_len);
                if (secret.empty()) {
                    secret.push_back(0);
                }
                
                HMAC* hmac = CryptoLink::getCryptoLink().createHMAC(
                    secret.data(), secret.size(), hash_alg
                );
                if (hmac) {
                    std::vector<uint8_t> input_data = fdp.ConsumeBytes<uint8_t>(
                        fdp.ConsumeIntegralInRange<size_t>(0, size)
                    );
                    if (!input_data.empty()) {
                        hmac->update(input_data.data(), input_data.size());
                    }
                    isc::util::OutputBuffer result(hmac->getOutputLength());
                    size_t len = fdp.ConsumeIntegralInRange<size_t>(0, hmac->getOutputLength() * 2);
                    hmac->sign(result, len);
                    delete hmac;
                }
                break;
            }
            
            case 7: {
                // Test HMAC verification
                size_t secret_len = fdp.ConsumeIntegralInRange<size_t>(1, 256);
                std::vector<uint8_t> secret = fdp.ConsumeBytes<uint8_t>(secret_len);
                if (secret.empty()) {
                    secret.push_back(0);
                }
                
                HMAC* hmac = CryptoLink::getCryptoLink().createHMAC(
                    secret.data(), secret.size(), hash_alg
                );
                if (hmac) {
                    std::vector<uint8_t> input_data = fdp.ConsumeBytes<uint8_t>(
                        fdp.ConsumeIntegralInRange<size_t>(0, size)
                    );
                    if (!input_data.empty()) {
                        hmac->update(input_data.data(), input_data.size());
                    }
                    
                    // Generate signature
                    std::vector<uint8_t> signature = hmac->sign(hmac->getOutputLength());
                    
                    // Verify with same data (should succeed)
                    HMAC* verify_hmac = CryptoLink::getCryptoLink().createHMAC(
                        secret.data(), secret.size(), hash_alg
                    );
                    if (verify_hmac) {
                        if (!input_data.empty()) {
                            verify_hmac->update(input_data.data(), input_data.size());
                        }
                        verify_hmac->verify(signature.data(), signature.size());
                        delete verify_hmac;
                    }
                    delete hmac;
                }
                break;
            }
            
            case 8: {
                // Test HMAC with long secret (should be hashed)
                size_t secret_len = fdp.ConsumeIntegralInRange<size_t>(256, 1024);
                std::vector<uint8_t> secret = fdp.ConsumeBytes<uint8_t>(secret_len);
                if (secret.size() < 64) {
                    secret.resize(64, 0x42);  // Pad to ensure long secret
                }
                
                HMAC* hmac = CryptoLink::getCryptoLink().createHMAC(
                    secret.data(), secret.size(), hash_alg
                );
                if (hmac) {
                    std::vector<uint8_t> input_data = fdp.ConsumeRemainingBytes<uint8_t>();
                    if (!input_data.empty()) {
                        hmac->update(input_data.data(), input_data.size());
                    }
                    std::vector<uint8_t> signature = hmac->sign(hmac->getOutputLength());
                    delete hmac;
                }
                break;
            }
            
            case 9: {
                // Test RNG generation
                size_t rng_len = fdp.ConsumeIntegralInRange<size_t>(0, 1024);
                std::vector<uint8_t> random_data = isc::cryptolink::random(rng_len);
                
                // Test Qid generation
                uint16_t qid = isc::cryptolink::generateQid();
                (void)qid;  // Use the variable
                break;
            }
        }
    } catch (const isc::Exception&) {
        // Expected for invalid algorithms, key lengths, etc.
    } catch (const std::exception&) {
        // Catch any standard library exceptions
    }
    
    return 0;
}
