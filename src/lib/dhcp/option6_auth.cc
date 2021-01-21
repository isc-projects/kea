// Copyright (C) 2018,2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <dhcp/dhcp6.h>
#include <dhcp/libdhcp++.h>
#include <dhcp/option6_auth.h>
#include <dhcp/option_space.h>
#include <exceptions/exceptions.h>
#include <util/io_utilities.h>
#include <util/encode/hex.h>

#include <sstream>
#include <stdint.h>

using namespace std;
using namespace isc::util;

namespace isc {
namespace dhcp {

    Option6Auth::Option6Auth(const uint8_t proto, const uint8_t algo,
                             const uint8_t method, const uint64_t rdm,
                             const std::vector<uint8_t>& info)
    : Option(Option::V6, D6O_AUTH),
      protocol_(proto), algorithm_(algo),
      rdm_method_(method), rdm_value_(rdm),
      auth_info_(info) {
}

OptionPtr
Option6Auth::clone() const {
    return (cloneInternal<Option6Auth>());
}

void
Option6Auth::pack(isc::util::OutputBuffer& buf) const {
    if (buf.getCapacity() < (OPTION6_AUTH_MIN_LEN + OPTION6_HASH_MSG_LEN + OPTION6_HDR)) {
       isc_throw(OutOfRange, "Option " << type_ << "Buffer too small for"
               "packing data");
    }

    //header = option code + length
    buf.writeUint16(type_);
    // length = 11 bytes fixed field length+ length of auth information
    buf.writeUint16(11 + uint16_t(auth_info_.size()));
    // protocol 1 byte
    buf.writeUint8(protocol_);
    // algorithm 1 byte
    buf.writeUint8(algorithm_);
    // replay detection method
    buf.writeUint8(rdm_method_);
    // replay detection value
    buf.writeUint64( rdm_value_);
    // authentication information for reconfig msg
    // should have zero

    for (auto i : auth_info_) {
        buf.writeUint8(i);
    }
}

void
Option6Auth::packHashInput(isc::util::OutputBuffer& buf) const {
    if (buf.getCapacity() < (OPTION6_AUTH_MIN_LEN + OPTION6_HASH_MSG_LEN + OPTION6_HDR)) {
       isc_throw(OutOfRange, "Option " << type_ << "Buffer too small for"
               "computing hash input");
    }

    //header = option code + length
    buf.writeUint16(type_);
    // length = 11 bytes fixed field length+ length of auth information
    buf.writeUint16(OPTION6_AUTH_MIN_LEN + OPTION6_HASH_MSG_LEN);
    // protocol 1 byte
    buf.writeUint8(protocol_);
    // algorithm 1 byte
    buf.writeUint8(algorithm_);
    // replay detection method
    buf.writeUint8(rdm_method_);
    // replay detection value
    buf.writeUint64(rdm_value_);
    // authentication information for reconfig msg
    // should have zero
    for (uint8_t i = 0; i < OPTION6_HASH_MSG_LEN; i++) {
        buf.writeUint8(0);
    }
}

void
Option6Auth::unpack(OptionBufferConstIter begin,
                     OptionBufferConstIter end) {
   // throw if it contains length less than minimum size of the auth option
   if (distance(begin, end) < Option6Auth::OPTION6_AUTH_MIN_LEN) {
       isc_throw(OutOfRange, "Option " << type_ << " truncated");
   }

   protocol_ = *begin;
   begin += sizeof(uint8_t);

   algorithm_ = *begin;
   begin += sizeof(uint8_t);

   rdm_method_ = *begin;
   begin += sizeof(uint8_t);

   rdm_value_ =  isc::util::readUint64(&(*begin), sizeof(uint64_t));
   begin += sizeof(uint64_t);

   auth_info_.erase(auth_info_.begin(), auth_info_.end());
   std::for_each(begin, end, [this](uint8_t msgdata)
                {  auth_info_.push_back(msgdata); });
}

std::string
Option6Auth::toText(int indent) const {
    stringstream output;
    std::string in(indent, ' '); //base indent

    output << in << "protocol=" << static_cast<int>(protocol_)
           << ", algorithm=" << static_cast<int>(algorithm_)
           << ", rdm method=" << static_cast<int>(rdm_method_)
           << ", rdm value=" << rdm_value_
           << ", value=" << isc::util::encode::encodeHex(auth_info_);

    return output.str();
}

} // end  namespace dhcp
} // end namespace isc
