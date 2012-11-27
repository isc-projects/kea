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

int
OptionDataTypeUtil::getDataTypeLen(const OptionDataType data_type) {
    switch (data_type) {
    case OPT_BOOLEAN_TYPE:
    case OPT_INT8_TYPE:
    case OPT_UINT8_TYPE:
        return (1);
    case OPT_INT16_TYPE:
    case OPT_UINT16_TYPE:
        return (2);
    case OPT_INT32_TYPE:
    case OPT_UINT32_TYPE:
        return (4);
    case OPT_IPV4_ADDRESS_TYPE:
        return (asiolink::V4ADDRESS_LEN);
    case OPT_IPV6_ADDRESS_TYPE:
        return (asiolink::V6ADDRESS_LEN);
    default:
        ;
    }
    return (0);
}

void
OptionDataTypeUtil::readAddress(const std::vector<uint8_t>& buf,
                            const short family,
                            asiolink::IOAddress& address) {
    using namespace isc::asiolink;
    if (family == AF_INET) {
        if (buf.size() < V4ADDRESS_LEN) {
            isc_throw(BadDataTypeCast, "unable to read data from the buffer as"
                      << " IPv4 address. Invalid buffer size: " << buf.size());
        }
        address = IOAddress::fromBytes(AF_INET, &buf[0]);
    } else if (buf.size() == V6ADDRESS_LEN) {
        if (buf.size() < V6ADDRESS_LEN) {
            isc_throw(BadDataTypeCast, "unable to read data from the buffer as"
                      << " IPv6 address. Invalid buffer size: " << buf.size());
        }
        address = IOAddress::fromBytes(AF_INET6, &buf[0]);
    } else {
        isc_throw(BadDataTypeCast, "unable to read data from the buffer as"
                  "IP address. Invalid family: " << family);
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

bool
OptionDataTypeUtil::readBool(const std::vector<uint8_t>& buf) {
    if (buf.size() < 1) {
        isc_throw(BadDataTypeCast, "unable to read the buffer as boolean"
                  << " value. Invalid buffer size " << buf.size());
    }
    if (buf[0] == 1) {
        return (true);
    } else if (buf[0] == 0) {
        return (false);
    }
    isc_throw(BadDataTypeCast, "unable to read the buffer as boolean"
              << " value. Inavlid value " << static_cast<int>(buf[0]));
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
OptionDataTypeUtil::readString(const std::vector<uint8_t>& buf,
                               std::string& value) {
    value.insert(value.end(), buf.begin(), buf.end());
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
