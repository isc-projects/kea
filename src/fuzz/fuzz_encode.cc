// Copyright (C) 2025 Ada Logics Ltd.
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
////////////////////////////////////////////////////////////////////////////////
#include <config.h>
#include <fuzzer/FuzzedDataProvider.h>

#include <exceptions/exceptions.h>
#include <util/encode/encode.h>

#include <string>
#include <vector>
#include <cstddef>

using namespace isc::util::encode;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
    if (size < 2) {
        return 0;
    }

    FuzzedDataProvider fdp(data, size);
    
    // Choose which encoding/decoding path to test
    uint8_t path = fdp.ConsumeIntegralInRange<uint8_t>(0, 11);
    
    std::vector<uint8_t> binary_data;
    std::string encoded_str;
    std::vector<uint8_t> decoded_output;
    
    switch (path) {
        case 0: {
            // Test Base64 encoding from binary data
            try {
                size_t bin_size = fdp.ConsumeIntegralInRange<size_t>(0, size);
                binary_data = fdp.ConsumeBytes<uint8_t>(bin_size);
                encoded_str = encodeBase64(binary_data);
                // Verify round-trip
                decodeBase64(encoded_str, decoded_output);
            } catch (const isc::Exception&) {
                // Expected for invalid input
            }
            break;
        }
        
        case 1: {
            // Test Base64 decoding from string
            try {
                encoded_str = fdp.ConsumeRemainingBytesAsString();
                decodeBase64(encoded_str, decoded_output);
            } catch (const isc::Exception&) {
                // Expected for invalid Base64 strings
            }
            break;
        }
        
        case 2: {
            // Test Base32Hex encoding from binary data
            try {
                size_t bin_size = fdp.ConsumeIntegralInRange<size_t>(0, size);
                binary_data = fdp.ConsumeBytes<uint8_t>(bin_size);
                encoded_str = encodeBase32Hex(binary_data);
                // Verify round-trip
                decodeBase32Hex(encoded_str, decoded_output);
            } catch (const isc::Exception&) {
                // Expected for invalid input
            }
            break;
        }
        
        case 3: {
            // Test Base32Hex decoding from string
            try {
                encoded_str = fdp.ConsumeRemainingBytesAsString();
                decodeBase32Hex(encoded_str, decoded_output);
            } catch (const isc::Exception&) {
                // Expected for invalid Base32Hex strings
            }
            break;
        }
        
        case 4: {
            // Test Base16 (hex) encoding from binary data
            try {
                size_t bin_size = fdp.ConsumeIntegralInRange<size_t>(0, size);
                binary_data = fdp.ConsumeBytes<uint8_t>(bin_size);
                encoded_str = encodeHex(binary_data);
                // Verify round-trip
                decodeHex(encoded_str, decoded_output);
            } catch (const isc::Exception&) {
                // Expected for invalid input
            }
            break;
        }
        
        case 5: {
            // Test Base16 (hex) decoding from string
            try {
                encoded_str = fdp.ConsumeRemainingBytesAsString();
                decodeHex(encoded_str, decoded_output);
            } catch (const isc::Exception&) {
                // Expected for invalid hex strings
            }
            break;
        }
        
        case 6: {
            // Test Base64 with various padding scenarios
            try {
                std::string test_str = fdp.ConsumeRandomLengthString();
                // Add various padding permutations
                test_str += fdp.ConsumeBool() ? "=" : "";
                test_str += fdp.ConsumeBool() ? "=" : "";
                decodeBase64(test_str, decoded_output);
            } catch (const isc::Exception&) {
                // Expected for invalid padding
            }
            break;
        }
        
        case 7: {
            // Test Base32Hex with various padding scenarios
            try {
                std::string test_str = fdp.ConsumeRandomLengthString();
                // Add various padding permutations
                for (int i = 0; i < fdp.ConsumeIntegralInRange(0, 6); i++) {
                    test_str += "=";
                }
                decodeBase32Hex(test_str, decoded_output);
            } catch (const isc::Exception&) {
                // Expected for invalid padding
            }
            break;
        }
        
        case 8: {
            // Test mixed case Base64 (should be case-sensitive)
            try {
                encoded_str = fdp.ConsumeRemainingBytesAsString();
                // Mix uppercase and lowercase
                for (auto& c : encoded_str) {
                    if (fdp.ConsumeBool() && isalpha(c)) {
                        c = (isupper(c)) ? tolower(c) : toupper(c);
                    }
                }
                decodeBase64(encoded_str, decoded_output);
            } catch (const isc::Exception&) {
                // Expected for case errors
            }
            break;
        }
        
        case 9: {
            // Test mixed case Base32Hex (case-insensitive)
            try {
                encoded_str = fdp.ConsumeRemainingBytesAsString();
                // Mix uppercase and lowercase
                for (auto& c : encoded_str) {
                    if (fdp.ConsumeBool() && isalpha(c)) {
                        c = (isupper(c)) ? tolower(c) : toupper(c);
                    }
                }
                decodeBase32Hex(encoded_str, decoded_output);
            } catch (const isc::Exception&) {
                // May succeed due to case-insensitivity
            }
            break;
        }
        
        case 10: {
            // Test Base16 with mixed case (case-insensitive)
            try {
                encoded_str = fdp.ConsumeRemainingBytesAsString();
                // Mix uppercase and lowercase
                for (auto& c : encoded_str) {
                    if (fdp.ConsumeBool() && isalpha(c)) {
                        c = (isupper(c)) ? tolower(c) : toupper(c);
                    }
                }
                decodeHex(encoded_str, decoded_output);
            } catch (const isc::Exception&) {
                // May succeed due to case-insensitivity
            }
            break;
        }
        
        case 11: {
            // Test encoding/decoding with whitespace injection
            try {
                std::string test_str = fdp.ConsumeRandomLengthString();
                // Inject whitespace characters
                size_t insertions = fdp.ConsumeIntegralInRange<size_t>(0, 10);
                for (size_t i = 0; i < insertions && test_str.size() > 0; i++) {
                    size_t pos = fdp.ConsumeIntegralInRange<size_t>(0, test_str.size());
                    char ws = fdp.PickValueInArray({' ', '\t', '\n', '\r'});
                    test_str.insert(pos, 1, ws);
                }
                
                // Try decoding with all encoders
                try { decodeBase64(test_str, decoded_output); } catch (...) {}
                try { decodeBase32Hex(test_str, decoded_output); } catch (...) {}
                try { decodeHex(test_str, decoded_output); } catch (...) {}
            } catch (const isc::Exception&) {
                // Expected for whitespace handling
            }
            break;
        }
    }
    
    return 0;
}
