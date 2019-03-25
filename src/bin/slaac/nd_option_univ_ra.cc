// Copyright (C) 2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <slaac/nd.h>
#include <slaac/nd_option_univ_ra.h>
#include <exceptions/exceptions.h>

#include <iomanip>
#include <sstream>

#include <stdint.h>
#include <string.h>

using namespace std;
using namespace isc::util;

namespace isc {
namespace slaac {

OptionUnivRa::OptionUnivRa()
    : Option(ND_UNIVERSAL_RA) {
}

OptionUnivRa::OptionUnivRa(const OptionBuffer& data)
    : Option(ND_UNIVERSAL_RA, data) {
}

OptionUnivRa::OptionUnivRa(OptionBufferConstIter first,
                           OptionBufferConstIter last)
    : Option(ND_UNIVERSAL_RA, first, last) {
}

string OptionUnivRa::toText(int indent) const {
    stringstream output;
    output << headerToText(indent, "UnivRA") << ": ";

    for (unsigned int i = 0; i < data_.size(); i++) {
        if (i) {
            output << ":";
        }
        output << setfill('0') << setw(2) << hex
            << static_cast<unsigned short>(data_[i]);
    }

    return (output.str());
}

OptionUnivRa::~OptionUnivRa() {

}

} // end of isc::slaac namespace
} // end of isc namespace
