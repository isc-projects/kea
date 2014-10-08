// Copyright (C) 2012-2014 Internet Systems Consortium, Inc. ("ISC")
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

HWAddr::HWAddr()
    :htype_(HTYPE_ETHER) {
}

HWAddr::HWAddr(const uint8_t* hwaddr, size_t len, uint16_t htype)
    :hwaddr_(hwaddr, hwaddr + len), htype_(htype) {
    if (len > MAX_HWADDR_LEN) {
        isc_throw(InvalidParameter, "hwaddr length exceeds MAX_HWADDR_LEN");
    }
}

HWAddr::HWAddr(const std::vector<uint8_t>& hwaddr, uint16_t htype)
    :hwaddr_(hwaddr), htype_(htype) {
    if (hwaddr.size() > MAX_HWADDR_LEN) {
        isc_throw(InvalidParameter,
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
