// Copyright (C) 2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <exceptions/exceptions.h>
#include <exceptions/isc_assert.h>
#include <util/encode/encode.h>

#include <iostream>
#include <stdint.h>
#include <stdexcept>
#include <string>
#include <cstring>
#include <vector>

using namespace std;

namespace isc {
namespace util {
namespace encode {

BaseNEncoder::BaseNEncoder(const std::string& algorithm,
                           const char* digit_set,
                           const std::vector<uint8_t>& bits_table,
                           size_t bits_per_digit,
                           size_t digits_per_group,
                           const char pad_char,
                           size_t max_pad,
                           bool case_sensitive)
     : algorithm_(algorithm),
       digit_set_(digit_set),
       bits_table_(bits_table),
       bits_per_digit_(bits_per_digit),
       digits_per_group_(digits_per_group),
       pad_char_(pad_char),
       max_pad_(max_pad),
       case_sensitive_(case_sensitive),
       max_bits_to_digit_(strlen(digit_set) - 1),
       max_digit_to_bits_(bits_table_.size() - 1) {
}

char
BaseNEncoder::bitsToDigit(uint8_t bits) {
    if (bits > max_bits_to_digit_) {
        isc_throw(BadValue, "Digit bits : "
                  << static_cast<uint16_t>(bits) << " invalid for " << algorithm_);
    }

    return (digit_set_[bits]);
}

uint8_t
BaseNEncoder::digitToBits(uint8_t digit) {
    if (digit > max_digit_to_bits_) {
        isc_throw(BadValue, "Digit exceeds look up table: "
                  << static_cast<uint16_t>(digit) << " for " << algorithm_);
    }

    return (bits_table_[digit]);
}

std::string
BaseNEncoder::encode(const std::vector<uint8_t>& input) {
    std::string encoded_output;
    if (input.empty()) {
        return (encoded_output);
    }

    // Iterate over the input bytes as a bit stream.  We add input bits
    // to a digit set index value until we have enough (bits_per_digit).  We
    // look up a digit in the digit set add it to the encoded output and start over
    // on the next index value.  When we have exhausted the bits in the current
    // byte, get the next byte from input and continue.  In other words, we pull bits
    // from the left side of the input bit stream and push them into the right side of
    // the index value.  Each time we have done bits_per_digit bits we look up
    // the digit and start the index value over.

    int digit_idx = 0;          // Digit index we are currently constructing.
    size_t cnt = 0;             // How many bits we have in the current digit idx
    int cur_byte = 0;           // Current input byte.
    uint8_t cur_bit_mask = 0x0; // Bitmask of the current bit in the current byte.
    auto bytes = input.begin(); // Start with the first byte.
    while (1) {
        // If the current bitmask is zero, it's time for the next input byte.
        if (!cur_bit_mask) {
            if (bytes == input.end()) {
                break;
            }

            // Grab the next byte.
            cur_byte = *bytes;
            // Start at the bitmask at the left-most bit.
            cur_bit_mask = 0x80;
            // Bump the iterator.
            ++bytes;
        }

        // Do we need more bits in this digit index?
        if (cnt < bits_per_digit_) {
            // Yes, so shift the index over to make room for the next bit.
            digit_idx <<= 1;
        } else {
            // No, the index is complete, lookup its digit and add it to the
            // output. Start over for the next index.
            encoded_output.push_back(bitsToDigit(digit_idx));
            digit_idx = 0;
            cnt = 0;
        }

        // If the current bit in the current byte is set,
        // set the right-most digit index bit to 1 (otherwise
        // its left as zero).
        if (cur_byte & cur_bit_mask) {
            digit_idx |= 1;
        }

        // Shift the cur_bit mask to select the next input bit and
        // bump the number of bits in the current index.
        cur_bit_mask >>= 1;
        ++cnt;
    }

    // We've exhausted the input bits but have bits in the
    // digit index.  This means the remaining bits in our
    // last index are zeros (pad bits).  Shift "in" the
    // required number of bits and add the corresponding
    // digit.
    digit_idx <<= (bits_per_digit_ - cnt);
    encoded_output.push_back(bitsToDigit(digit_idx));

    // Add padding as needed.
    if (digits_per_group_) {
        auto rem = encoded_output.size() % digits_per_group_;
        if (rem) {
            auto need = digits_per_group_ - rem;
            while (need--) {
                encoded_output.push_back(pad_char_);
            }
        }
    }

    return (encoded_output);
}

void
BaseNEncoder::decode(const std::string& encoded_str, std::vector<uint8_t>& output) {

    // Mechanics are essentially the same as encode(). We iterate over the encoded
    // string's digits, discarding whitespaces. We lookup the digit's binary value
    // in the lookup table, keeping only binary value's right-most, bits_per_digit bits.
    // The remaining bits are then shifted out from the left of binary value into the
    // right of the currently accumulating output byte until the byte is complete
    // (8 bits) or the value's bits are exhausted.  Completed bytes are added to the
    // output buffer.  We continue building bytes until we've exhausted the encoded
    // string.

    output.clear();
    size_t dig_cnt = 0;                       // Tracks how many encoded digits we see.
    size_t pad_cnt = 0;                       // Tracks how many pad characters we see.
    size_t shift_bits = 8 - bits_per_digit_;  // Number of unused bits in digit data values.
    uint8_t cur_byte = 0;                     // Current output byte.
    size_t cur_bit_cnt = 0;                   // How man bits we have added to the current byte.

    for (const auto enc_digit : encoded_str) {
        // If it's a pad char, count it and go on.
        if (pad_char_ && enc_digit == pad_char_) {
           pad_cnt++;
           continue;
        }

        // Translate the encoded digit to its binary bits.
        uint8_t dig_bits = digitToBits(enc_digit);

        // Skip whitespace. The choice of 0xee to signify white-space was arbitrary.
        if (dig_bits == 0xee) {
            continue;
        }

        // Error on invalid characters.
        if (dig_bits == 0xff) {
            isc_throw(isc::BadValue, "attempt to decode a value not in "
                      << algorithm_ << " char set" << ": " << encoded_str);
        }

        // Error if pad characters occur in the middle.
        if (pad_cnt) {
            isc_throw(isc::BadValue, "pad mixed with digits in "
                      << algorithm_ << ": " << encoded_str);
        }

        // Bump the valid character count.
        dig_cnt++;

        // Shift off the unused bits.
        dig_bits <<= shift_bits;

        // Add digit's decoded bits to current byte.
        for (size_t i = 0; i < bits_per_digit_; ++i) {
            if (cur_bit_cnt < 8) {
                // Shift contents over one to make room for next bit.
                cur_byte <<= 1;
            } else {
                // Add the completed byte to the output.
                output.push_back(cur_byte);
                cur_byte = 0;
                cur_bit_cnt = 0;
            }

            // Add the next bit if its set.
            if (dig_bits & 0x80) {
                cur_byte |= 1;
            }

            // Shift the decoded bits over.
            dig_bits <<= 1;

            // Update the current byte bit count.
            ++cur_bit_cnt;
        }
    }

    if (cur_bit_cnt == 8) {
        // Whole one left to add.
        output.push_back(cur_byte);
    } else if (cur_bit_cnt && cur_byte) {
        // Left over bits that are not zero.
        isc_throw(BadValue, "non-zero bits left over " << encoded_str);
    }

    if (pad_char_) {
        // Check for too many pad characters.
        if (pad_cnt > max_pad_) {
            isc_throw(isc::BadValue, "too many pad characters for "
                      << algorithm_ << ": " << encoded_str);
        }

        // Check for an invalid number of pad bits.
        // Calculate the number of pad bits corresponding to the pad
        // characters.  In general, the pad bits consist of all-zero
        // trailing bits of the last encoded character plus the zero bits
        // represented by each pad character.
        // 1st pad  2nd pad  3rd pad...
        // +++===== =======  ===...    (+: from encoded chars, =: from pad chars)
        // 0000...0 0......0 000...
        // 0      7 8     15 16.... (bits)
        // The number of bits for the '==...' part is padchars * BitsPerChunk.
        // So the total number of pad bits is the smallest multiple of 8
        // that is >= padchars * BitsPerChunk.
        // (Below, note the common idiom of the bitwise AND with ~0x7.  It clears the
        // lowest three bits, so has the effect of rounding the result down to the
        // nearest multiple of 8)
        const size_t padbits = ((pad_cnt * bits_per_digit_) + 7) & ~0x7;
        if (padbits > bits_per_digit_ * (pad_cnt + 1)) {
            isc_throw(isc::BadValue, "Invalid padding for "
                      << algorithm_ << ": " << encoded_str);
        }
    }

    // Check for an invalid total of encoded characters.
    if ((pad_cnt + dig_cnt) % digits_per_group_) {
        isc_throw (isc::BadValue, "Incomplete input for "
                   << algorithm_ << ": " << encoded_str);
    }
}

const char* Base64Encoder::DIGIT_SET = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                       "abcdefghijklmnopqrstuvwxyz"
                                       "0123456789"
                                       "+/";

const std::vector<uint8_t> Base64Encoder::BITS_TABLE = {
    0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xee,0xee,0xee,0xee,0xee,0xff,0xff, // 00-0f
    0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff, // 10-1f
    0xee,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,62,0xff,0xff,0xff,63,     // 20-2f
    52,53,54,55,56,57,58,59,60,61,0xff,0xff,0xff, 0,0xff,0xff,                       // 30-3f
    0xff, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,                               // 40-4f
    15,16,17,18,19,20,21,22,23,24,25,0xff,0xff,0xff,0xff,0xff,                       // 50-5f
    0xff,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,                               // 60-6f
    41,42,43,44,45,46,47,48,49,50,51,0xff,0xff,0xff,0xff,0xff,                       // 70-7f
    0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff, // 80-8f
    0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff, // 90-9f
    0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff, // a0-af
    0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff, // b0-bf
    0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff, // c0-cf
    0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff, // d0-df
    0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff, // e0-ef
    0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff  // f0-ff,
};

const char* Base32HexEncoder::DIGIT_SET = "0123456789ABCDEFGHIJKLMNOPQRSTUV";

const std::vector<uint8_t> Base32HexEncoder::BITS_TABLE = {
    0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xee,0xee,0xee,0xee,0xee,0xff,0xff, // 00-0f
    0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff, // 10-1f
    0xee,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff, // 20-2f
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9,0xff,0xff,0xff,0xff,0xff,0xff,                      // 30-3f
    0xff,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,                               // 40-4f
    25,26,27,28,29,30,31,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,               // 50-5f
    0xff,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,                               // 60-6f
    25,26,27,28,29,30,31,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,               // 70-7f
    0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff, // 80-8f
    0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff, // 90-9f
    0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff, // a0-af
    0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff, // b0-bf
    0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff, // c0-cf
    0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff, // d0-df
    0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff, // e0-ef
    0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff  // f0-ff
};

const char* Base16Encoder::DIGIT_SET = "0123456789ABCDEF";

const std::vector<uint8_t> Base16Encoder::BITS_TABLE = {
    0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xee,0xee,0xee,0xee,0xee,0xff,0xff, // 00-0f
    0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff, // 10-1f
    0xee,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff, // 20-2f
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9,0xff,0xff,0xff,0xff,0xff,0xff,                      // 30-3f
    0xff,10,11,12,13,14,15,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,             // 40-4f
    0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff, // 50-5f
    0xff,10,11,12,13,14,15,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,             // 60-6f
    0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff, // 70-7f
    0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff, // 80-8f
    0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff, // 90-9f
    0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff, // a0-af
    0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff, // b0-bf
    0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff, // c0-cf
    0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff, // d0-df
    0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff, // e0-ef
    0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff  // f0-ff
};

string
encodeBase64(const vector<uint8_t>& binary) {
    static Base64Encoder encoder;
    return (encoder.encode(binary));
}

void
decodeBase64 (const std::string& encoded_str, std::vector<uint8_t>& output) {
    static Base64Encoder encoder;
    encoder.decode(encoded_str, output);
}

string
encodeBase32Hex(const vector<uint8_t>& binary) {
    static Base32HexEncoder encoder;
    return (encoder.encode(binary));
}

void
decodeBase32Hex(const std::string& encoded_str, std::vector<uint8_t>& output) {
    static Base32HexEncoder encoder;
    encoder.decode(encoded_str, output);
}

string
encodeHex(const vector<uint8_t>& binary) {
    static Base16Encoder encoder;
    return (encoder.encode(binary));
}

void
decodeHex(const string& encoded_str, vector<uint8_t>& output) {
    static Base16Encoder encoder;
    encoder.decode(encoded_str, output);
}

} // namespace encode
} // namespace util
} // namespace isc
