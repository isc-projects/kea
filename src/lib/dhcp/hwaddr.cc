// Copyright (C) 2012-2016 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <dhcp/hwaddr.h>
#include <dhcp/dhcp4.h>
#include <exceptions/exceptions.h>
#include <util/strutil.h>
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
    std::vector<uint8_t> binary;
    util::str::decodeColonSeparatedHexString(text, binary);
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
