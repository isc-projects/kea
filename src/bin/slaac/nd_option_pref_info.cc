// Copyright (C) 2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <slaac/nd.h>
#include <slaac/nd_option_pref_info.h>
#include <asiolink/addr_utilities.h>
#include <exceptions/exceptions.h>

#include <iomanip>
#include <sstream>

#include <stdint.h>
#include <string.h>

using namespace std;
using namespace isc::asiolink;
using namespace isc::util;

namespace isc {
namespace slaac {

OptionPrefInfo::OptionPrefInfo()
    : Option(ND_PREFIX_INFO), prefix_length_(128), on_link_flag_(false),
      addr_config_flag_(false), valid_lifetime_(0), preferred_lifetime_(0),
      prefix_(IOAddress::IPV6_ZERO_ADDRESS()) {
}

OptionPrefInfo::OptionPrefInfo(const OptionBuffer& data)
    : Option(ND_PREFIX_INFO, data), prefix_length_(128), on_link_flag_(false),
      addr_config_flag_(false), valid_lifetime_(0), preferred_lifetime_(0),
      prefix_(IOAddress::IPV6_ZERO_ADDRESS()) {
    unpack();
}

OptionPrefInfo::OptionPrefInfo(OptionBufferConstIter first, OptionBufferConstIter last)
    : Option(ND_PREFIX_INFO, first, last), prefix_length_(128),
      on_link_flag_(false), addr_config_flag_(false),
      valid_lifetime_(0), preferred_lifetime_(0),
      prefix_(IOAddress::IPV6_ZERO_ADDRESS()) {
    unpack();
}

void OptionPrefInfo::pack(OutputBuffer& buf) const {
    // Write a header.
    packHeader(buf);

    // Write prefix length.
    buf.writeUint8(prefix_length_);

    // Write flags.
    uint8_t flags = 0;
    if (on_link_flag_) {
        flags |= ON_LINK_FLAG;
    }
    if (addr_config_flag_) {
        flags |= ADDR_CONFIG_FLAG;
    }
    buf.writeUint8(flags);

    // Write valid lifetime.
    buf.writeUint32(valid_lifetime_);

    // Write preferred lifetime.
    buf.writeUint32(preferred_lifetime_);

    // Write reserved2.
    buf.writeUint32(0);

    // Write prefix.
    buf.writeData(&(prefix_.toBytes()[0]), V6ADDRESS_LEN);
}

void OptionPrefInfo::unpack(OptionBufferConstIter begin,
                            OptionBufferConstIter end) {
    Option::unpack(begin, end);
    unpack();
}

void OptionPrefInfo::unpack() {
    // Check length.
    if (data_.size() < PREFIX_INFO_LEN) {
        isc_throw(BadValue, "Truncate Prefix Info option: size "
                  << (data_.size() + OPTION_HDR_LEN)
                  << ", expected " << (PREFIX_INFO_LEN + OPTION_HDR_LEN));
    }

    // Input buffer (used to parse the option content).
    InputBuffer buffer(&data_[0], PREFIX_INFO_LEN - V6ADDRESS_LEN);

    // Get the prefix length.
    uint8_t plen = buffer.readUint8();
    if (plen > 128) {
        isc_throw(BadValue, "Invalid prefix length in Prefix Info option: "
                  << static_cast<unsigned>(plen)
                  << ", valid range is from 0 to 128");
    }
    prefix_length_ = plen;

    // Get flags.
    uint8_t flags = buffer.readUint8();
    on_link_flag_ = ((flags & ON_LINK_FLAG) != 0);
    addr_config_flag_ = ((flags & ADDR_CONFIG_FLAG) != 0);

    // Valid lifetime.
    valid_lifetime_ = buffer.readUint32();

    // Preferred lifetime.
    preferred_lifetime_ = buffer.readUint32();

    // Skip reserved2,
    static_cast<void>(buffer.readUint32());

    // Get prefix.
    const IOAddress& pref =
        IOAddress::fromBytes(AF_INET6, &data_[PREFIX_INFO_LEN - V6ADDRESS_LEN]);
    checkPrefix(pref);
    prefix_ = pref;
}

string OptionPrefInfo::toText(int indent) const {
    stringstream output;
    output << headerToText(indent, "PrefInfo") << ": "
           << "flags=" << (on_link_flag_ ? "L" : "")
           << (addr_config_flag_ ? "A" : "")
           << ", prefix-" << prefix_.toText() << "/"
           << static_cast<unsigned>(prefix_length_) << endl;

    for (int i = 0; i < indent; i++) {
        output << " ";
    }

    output << "valid-lifetime=" << valid_lifetime_
           << ", preferred-lifetime="<< preferred_lifetime_;

    return (output.str());
}

OptionPrefInfo::~OptionPrefInfo() {

}

void OptionPrefInfo::checkPrefix(const IOAddress& pref) {
    const IOAddress& first = dhcp::firstAddrInPrefix(pref, prefix_length_);
    if (first != pref) {
        isc_throw(BadValue, "bad prefix " << pref.toText() << "/"
                  << static_cast<unsigned>(prefix_length_)
                  << ": its first adderess is " << first.toText());
    }
}

} // end of isc::slaac namespace
} // end of isc namespace
