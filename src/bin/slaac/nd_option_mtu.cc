// Copyright (C) 2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <slaac/nd.h>
#include <slaac/nd_option_mtu.h>
#include <exceptions/exceptions.h>
#include <util/io_utilities.h>

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
    unpack();
}

OptionMtu::OptionMtu(OptionBufferConstIter first, OptionBufferConstIter last)
    : Option(ND_MTU, first, last) {
    unpack();
}

void OptionMtu::pack(OutputBuffer& buf) const {
    // Write a header.
    packHeader(buf);

    // Write reserved.
    buf.writeUint16(0);

    // Write MTU.
    buf.writeUint32(mtu_);
}

void OptionMtu::unpack(OptionBufferConstIter begin,
                       OptionBufferConstIter end) {
    Option::unpack(begin, end);
    unpack();
}

void OptionMtu::unpack() {
    mtu_ = readUint32(&data_[2], data_.size() - 2);
}

string OptionMtu::toText(int indent) const {
    stringstream output;
    output << headerToText(indent, "MTU") << ": " << mtu_ << endl;

    return (output.str());
}

OptionMtu::~OptionMtu() {

}

} // end of isc::slaac namespace
} // end of isc namespace
