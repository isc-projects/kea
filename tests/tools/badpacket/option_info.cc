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

#include "option_info.h"

namespace {

// Define the various options for the command switches.  This includes both the
// long form and short form of the switch.  Unfortunately this means that the
// information is duplicated here and where the long options are specified for
// getopt_long, but this inconvenience is outweighed by the simplified command
// processing.
//
// Fields are:
// * Short option name
// * Long option name
// * Offset of 16-bit word holding datum in DNS message (if applicable)
// * Bit mask for the data (if applicable)
// * Offset of the bit field in the word (if applicable)
// * Default value (this can be ignored if applicable)
// * Minimum value specified on command line
// * Maximum value specified on command line

isc::badpacket::OptionInfo::Parameter option_information[] = {
    {'Q', "qr",  2, 0x8000,  15,  0, 0,      1},
    {'O', "op",  2, 0x7800,  11,  0, 0,     15},
    {'A', "aa",  2, 0x0400,  10,  0, 0,      1},
    {'T', "tc",  2, 0x0200,   9,  0, 0,      1},
    {'D', "rd",  2, 0x0100,   8,  0, 0,      1},
    {'R', "ra",  2, 0x0080,   7,  0, 0,      1},
    {'Z', "z",   2, 0x0040,   6,  0, 0,      1},
    {'U', "ad",  2, 0x0020,   5,  0, 0,      1},
    {'C', "cd",  2, 0x0010,   4,  0, 0,      1},
    {'E', "rc",  2, 0x000F,   0,  0, 0,     15},
    {'Y', "qc",  4,      0,   0,  1, 0, 0xFFFF},
    {'W', "ac",  6,      0,   0,  0, 0, 0xFFFF},
    {'H', "uc",  8,      0,   0,  0, 0, 0xFFFF},
    {'I', "dc", 10,      0,   0,  0, 0, 0xFFFF},
    {'M', "ms",  0,      0,   0,  0, 1,  65536}
};

}   // Anonymous namespace

namespace isc {
namespace badpacket {

// Locate the index of the information in the array from the short switch.
int
OptionInfo::getIndex(int c) {
    for (int i = 0; i < SIZE; ++i) {
        if (option_information[i].short_form == c) {
            return (i);
        }
    }
    isc_throw(isc::BadValue, "unknown option: " << c);
}

// Methods to return values from the array

const char*
OptionInfo::name(int i) {
    checkIndex(i);
    return (option_information[i].long_form);
}

uint16_t
OptionInfo::mask(int i) {
    checkIndex(i);
    return (option_information[i].mask);
}

int
OptionInfo::word(int i) {
    checkIndex(i);
    return (option_information[i].word);
}

int
OptionInfo::offset(int i) {
    checkIndex(i);
    return (option_information[i].offset);
}

uint32_t
OptionInfo::minval(int i) {
    checkIndex(i);
    return (option_information[i].minval);
}

uint32_t
OptionInfo::defval(int i) {
    checkIndex(i);
    return (option_information[i].defval);
}

uint32_t
OptionInfo::maxval(int i) {
    checkIndex(i);
    return (option_information[i].maxval);
}

} // namespace badpacket
} // namespace isc
