// Copyright (C) 2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <slaac/nd.h>
#include <slaac/nd_option_lladdr.h>
#include <exceptions/exceptions.h>

#include <iomanip>
#include <sstream>

#include <stdint.h>
#include <string.h>

using namespace std;
using namespace isc::util;

namespace isc {
namespace slaac {

OptionLLAddr::OptionLLAddr(uint8_t type)
    : Option(type) {
    if ((type != ND_SRC_LL_ADDR) && (type != ND_TGT_LL_ADDR)) {
        isc_throw(BadValue, "illegal type in Link-Layer Address option: "
                  << static_cast<unsigned>(type)
                  << ", expected 1 or 2");
    }
}

OptionLLAddr::OptionLLAddr(uint8_t type, const OptionBuffer& data)
    : Option(type, data) {
    if ((type != ND_SRC_LL_ADDR) && (type != ND_TGT_LL_ADDR)) {
        isc_throw(BadValue, "illegal type in Link-Layer Address option: "
                  << static_cast<unsigned>(type)
                  << ", expected 1 or 2");
    }
}

OptionLLAddr::OptionLLAddr(uint8_t type, OptionBufferConstIter first,
                           OptionBufferConstIter last)
    : Option(type, first, last) {
    if ((type != ND_SRC_LL_ADDR) && (type != ND_TGT_LL_ADDR)) {
        isc_throw(BadValue, "illegal type in Link-Layer Address option: "
                  << static_cast<unsigned>(type)
                  << ", expected 1 or 2");
    }
}

string OptionLLAddr::toText(int indent) const {
    stringstream output;
    string name;
    if (type_ == ND_SRC_LL_ADDR) {
        name = "SrcLLAddr";
    } else if (type_ == ND_TGT_LL_ADDR) {
        name = "TgtLLAddr";
    }
    output << headerToText(indent, name) << ": ";

    for (unsigned int i = 0; i < data_.size(); i++) {
        if (i) {
            output << ":";
        }
        output << setfill('0') << setw(2) << hex
            << static_cast<unsigned short>(data_[i]);
    }

    return (output.str());
}

OptionLLAddr::~OptionLLAddr() {

}

} // end of isc::slaac namespace
} // end of isc namespace
