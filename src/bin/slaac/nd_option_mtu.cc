// Copyright (C) 2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <slaac/nd.h>
#include <slaac/nd_option_mtu.h>
#include <exceptions/exceptions.h>

#include <iomanip>
#include <sstream>

#include <stdint.h>
#include <string.h>

using namespace std;
using namespace isc::util;

namespace isc {
namespace slaac {

OptionMtu::OptionMtu()
    : Option(ND_MTU), mtu_(0) {
}

OptionMtu::OptionMtu(const OptionBuffer& data)
    : Option(ND_MTU, data) {
    mtu_ = getUint32();
}

OptionMtu::OptionMtu(OptionBufferConstIter first, OptionBufferConstIter last)
    : Option(ND_MTU, first, last) {
    mtu_ = getUint32();
}

void OptionMtu::pack(isc::util::OutputBuffer& buf) const {
    // Write a header.
    packHeader(buf);
    if (!data_.empty()) {
        // Write data.
        buf.writeData(&data_[0], data_.size());
    } else {
        // Write MTU.
        buf.writeUint32(mtu_);
        // Pad to 8 bytes.
        buf.writeUint16(0);
    }
}

void OptionMtu::unpack(OptionBufferConstIter begin,
                       OptionBufferConstIter end) {
    setData(begin, end);
    mtu_ = getUint32();
}

string OptionMtu::toText(int indent) const {
    stringstream output;
    output << headerToText(indent, "MTU") << ": ";

    for (unsigned int i = 0; i < data_.size(); i++) {
        if (i) {
            output << ":";
        }
        output << setfill('0') << setw(2) << hex
            << static_cast<unsigned short>(data_[i]);
    }

    return (output.str());
}

OptionMtu::~OptionMtu() {

}

} // end of isc::slaac namespace
} // end of isc namespace
