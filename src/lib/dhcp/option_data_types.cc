// Copyright (C) 2012 Internet Systems Consortium, Inc. ("ISC")
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

#include <dhcp/option_data_types.h>
#include <util/encode/hex.h>

namespace isc {
namespace dhcp {

void
OptionDataTypeUtil::writeBinary(const std::string& hex_str,
                                std::vector<uint8_t>& buf) {
    // Binary value means that the value is encoded as a string
    // of hexadecimal deigits. We need to decode this string
    // to the binary format here.
    OptionBuffer binary;
    try {
        util::encode::decodeHex(hex_str, binary);
    } catch (const Exception& ex) {
        isc_throw(BadDataTypeCast, "unable to cast " << hex_str
                  << " to binary data type: " << ex.what());
    }
    // Decode was successful so append decoded binary value
    // to the buffer.
    buf.insert(buf.end(), binary.begin(), binary.end());
}

void
OptionDataTypeUtil::writeBool(const bool value,
                              std::vector<uint8_t>& buf) {
    if (value) {
        buf.push_back(static_cast<uint8_t>(1));
    } else {
        buf.push_back(static_cast<uint8_t>(0));
    }
}

void
OptionDataTypeUtil::writeAddress(const asiolink::IOAddress& address,
                                 std::vector<uint8_t>& buf) {
    if (address.getAddress().is_v4()) {
        asio::ip::address_v4::bytes_type addr_bytes =
            address.getAddress().to_v4().to_bytes();
        // Increase the buffer size by the size of IPv4 address.
        buf.resize(buf.size() + addr_bytes.size());
        std::copy_backward(addr_bytes.begin(), addr_bytes.end(),
                           buf.end());
    } else if (address.getAddress().is_v6()) {
        asio::ip::address_v6::bytes_type addr_bytes =
            address.getAddress().to_v6().to_bytes();
        // Incresase the buffer size by the size of IPv6 address.
        buf.resize(buf.size() + addr_bytes.size());
        std::copy_backward(addr_bytes.begin(), addr_bytes.end(),
                           buf.end());
    } else {
        isc_throw(BadDataTypeCast, "the address " << address.toText()
                  << " is neither valid IPv4 not IPv6 address.");
    }
}

void
OptionDataTypeUtil::writeString(const std::string& value,
                                std::vector<uint8_t>& buf) {
    if (value.size() > 0) {
        // Increase the size of the storage by the size of the string.
        buf.resize(buf.size() + value.size());
        // Assuming that the string is already UTF8 encoded.
        std::copy_backward(value.c_str(), value.c_str() + value.size(),
                           buf.end());
    }
}

} // end of isc::dhcp namespace
} // end of isc namespace
