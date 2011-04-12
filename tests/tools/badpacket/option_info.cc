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

// Define the various options for the command switches


namespace {

    isc::badpacket::OptionInfo::Parameter option_information[] = {
    {"qr", 0x8000, 15, 0,  1},
    {"op", 0x7800, 11, 0, 15},
    {"aa", 0x0400, 10, 0,  1},
    {"tc", 0x0200,  9, 0,  1},
    {"rd", 0x0100,  8, 0,  1},
    {"ra", 0x0080,  7, 0,  1},
    {"z",  0x0040,  6, 0,  1},
    {"ad", 0x0020,  5, 0,  1},
    {"cd", 0x0010,  4, 0,  1},
    {"rc", 0x000F,  0, 0, 15}
};

}   // Anonymous namespace

namespace isc {
namespace badpacket {

// Methods to return values from the array

const char*
OptionInfo::name(OptionInfo::Index i) {
    checkIndex(i);
    return (option_information[i].long_form);
}

uint16_t
OptionInfo::mask(OptionInfo::Index i) {
    checkIndex(i);
    return (option_information[i].mask);
}

int
OptionInfo::offset(OptionInfo::Index i) {
    checkIndex(i);
    return (option_information[i].offset);
}

uint32_t
OptionInfo::minval(OptionInfo::Index i) {
    checkIndex(i);
    return (option_information[i].minval);
}

uint32_t
OptionInfo::maxval(OptionInfo::Index i) {
    checkIndex(i);
    return (option_information[i].maxval);
}

} // namespace badpacket
} // namespace isc
