// Copyright (C) 2012-2014 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <dhcp/hwaddr.h>
#include <dhcp/dhcp4.h>
#include <exceptions/exceptions.h>
#include <util/encode/hex.h>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/constants.hpp>
#include <boost/algorithm/string/split.hpp>
#include <iomanip>
#include <sstream>
#include <vector>
#include <string.h>

namespace isc {
namespace dhcp {

const uint32_t HWAddr::HWADDR_SOURCE_ANY = 0xffffffff;
const uint32_t HWAddr::HWADDR_SOURCE_UNKNOWN = 0x00000000;
const uint32_t HWAddr::HWADDR_SOURCE_RAW = 0x00000001;
const uint32_t HWAddr::HWADDR_SOURCE_DUID = 0x00000002;
const uint32_t HWAddr::HWADDR_SOURCE_IPV6_LINK_LOCAL = 0x00000004;
const uint32_t HWAddr::HWADDR_SOURCE_CLIENT_ADDR_RELAY_OPTION = 0x00000008;
const uint32_t HWAddr::HWADDR_SOURCE_REMOTE_ID = 0x00000010;
const uint32_t HWAddr::HWADDR_SOURCE_SUBSCRIBER_ID = 0x00000020;
const uint32_t HWAddr::HWADDR_SOURCE_DOCSIS_CMTS = 0x00000040;
const uint32_t HWAddr::HWADDR_SOURCE_DOCSIS_MODEM = 0x00000080;

HWAddr::HWAddr()
    :htype_(HTYPE_ETHER), source_(0) {
}

HWAddr::HWAddr(const uint8_t* hwaddr, size_t len, uint16_t htype)
    :hwaddr_(hwaddr, hwaddr + len), htype_(htype), source_(0) {
    if (len > MAX_HWADDR_LEN) {
        isc_throw(isc::BadValue, "hwaddr length exceeds MAX_HWADDR_LEN");
    }
}

HWAddr::HWAddr(const std::vector<uint8_t>& hwaddr, uint16_t htype)
    :hwaddr_(hwaddr), htype_(htype), source_(0) {
    if (hwaddr.size() > MAX_HWADDR_LEN) {
        isc_throw(isc::BadValue,
            "address vector size exceeds MAX_HWADDR_LEN");
    }
}

std::string HWAddr::toText(bool include_htype) const {
    std::stringstream tmp;
    if (include_htype) {
        tmp << "hwtype=" << static_cast<unsigned int>(htype_) << " ";
    }
    tmp << std::hex;
    bool delim = false;
    for (std::vector<uint8_t>::const_iterator it = hwaddr_.begin();
         it != hwaddr_.end(); ++it) {
        if (delim) {
            tmp << ":";
        }
        tmp << std::setw(2) << std::setfill('0') << static_cast<unsigned int>(*it);
        delim = true;
    }
    return (tmp.str());
}

HWAddr
HWAddr::fromText(const std::string& text, const uint16_t htype) {
    /// @todo optimize stream operations here.
    std::vector<std::string> split_text;
    boost::split(split_text, text, boost::is_any_of(":"),
                 boost::algorithm::token_compress_off);

    std::ostringstream s;
    for (size_t i = 0; i < split_text.size(); ++i) {
        // If there are multiple tokens and the current one is empty, it
        // means that two consecutive colons were specified. This is not
        // allowed for hardware address.
        if ((split_text.size() > 1) && split_text[i].empty()) {
            isc_throw(isc::BadValue, "failed to create hardware address"
                      " from text '" << text << "': tokens of the hardware"
                      " address must be separated with a single colon");

        } else  if (split_text[i].size() == 1) {
            s << "0";

        } else if (split_text[i].size() > 2) {
            isc_throw(isc::BadValue, "invalid hwaddr '" << text << "'");
        }
        s << split_text[i];
    }

    std::vector<uint8_t> binary;
    try {
        util::encode::decodeHex(s.str(), binary);
    } catch (const Exception& ex) {
        isc_throw(isc::BadValue, "failed to create hwaddr from text '"
                  << text << "': " << ex.what());
    }
    return (HWAddr(binary, htype));
}

bool HWAddr::operator==(const HWAddr& other) const {
    return ((this->htype_  == other.htype_) &&
            (this->hwaddr_ == other.hwaddr_));
}

bool HWAddr::operator!=(const HWAddr& other) const {
    return !(*this == other);
}

}; // end of isc::dhcp namespace
}; // end of isc namespace
