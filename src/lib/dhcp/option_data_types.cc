// Copyright (C) 2012-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <dhcp/option_data_types.h>
#include <dns/labelsequence.h>
#include <dns/name.h>
#include <util/encode/hex.h>

namespace isc {
namespace dhcp {

OptionDataTypeUtil::OptionDataTypeUtil() {
    data_types_["empty"] = OPT_EMPTY_TYPE;
    data_types_["binary"] = OPT_BINARY_TYPE;
    data_types_["boolean"] = OPT_BOOLEAN_TYPE;
    data_types_["int8"] = OPT_INT8_TYPE;
    data_types_["int16"] = OPT_INT16_TYPE;
    data_types_["int32"] = OPT_INT32_TYPE;
    data_types_["uint8"] = OPT_UINT8_TYPE;
    data_types_["uint16"] = OPT_UINT16_TYPE;
    data_types_["uint32"] = OPT_UINT32_TYPE;
    data_types_["ipv4-address"] = OPT_IPV4_ADDRESS_TYPE;
    data_types_["ipv6-address"] = OPT_IPV6_ADDRESS_TYPE;
    data_types_["string"] = OPT_STRING_TYPE;
    data_types_["fqdn"] = OPT_FQDN_TYPE;
    data_types_["record"] = OPT_RECORD_TYPE;

    data_type_names_[OPT_EMPTY_TYPE] = "empty";
    data_type_names_[OPT_BINARY_TYPE] = "binary";
    data_type_names_[OPT_BOOLEAN_TYPE] = "boolean";
    data_type_names_[OPT_INT8_TYPE] = "int8";
    data_type_names_[OPT_INT16_TYPE] = "int16";
    data_type_names_[OPT_INT32_TYPE] = "int32";
    data_type_names_[OPT_UINT8_TYPE] = "uint8";
    data_type_names_[OPT_UINT16_TYPE] = "uint16";
    data_type_names_[OPT_UINT32_TYPE] = "uint32";
    data_type_names_[OPT_IPV4_ADDRESS_TYPE] = "ipv4-address";
    data_type_names_[OPT_IPV6_ADDRESS_TYPE] = "ipv6-address";
    data_type_names_[OPT_STRING_TYPE] = "string";
    data_type_names_[OPT_FQDN_TYPE] = "fqdn";
    data_type_names_[OPT_RECORD_TYPE] = "record";
    // The "unknown" data type is declared here so as
    // it can be returned by reference by a getDataTypeName
    // function it no other type is suitable. Other than that
    // this is unused.
    data_type_names_[OPT_UNKNOWN_TYPE] = "unknown";
}

OptionDataType
OptionDataTypeUtil::getDataType(const std::string& data_type) {
    return (OptionDataTypeUtil::instance().getDataTypeImpl(data_type));
}

OptionDataType
OptionDataTypeUtil::getDataTypeImpl(const std::string& data_type) const {
    std::map<std::string, OptionDataType>::const_iterator data_type_it =
        data_types_.find(data_type);
    if (data_type_it != data_types_.end()) {
        return (data_type_it->second);
    }
    return (OPT_UNKNOWN_TYPE);
}

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

const std::string&
OptionDataTypeUtil::getDataTypeName(const OptionDataType data_type) {
    return (OptionDataTypeUtil::instance().getDataTypeNameImpl(data_type));
}

const std::string&
OptionDataTypeUtil::getDataTypeNameImpl(const OptionDataType data_type) const {
    std::map<OptionDataType, std::string>::const_iterator data_type_it =
        data_type_names_.find(data_type);
    if (data_type_it != data_type_names_.end()) {
        return (data_type_it->second);
    }
    return (data_type_names_.find(OPT_UNKNOWN_TYPE)->second);
}

OptionDataTypeUtil&
OptionDataTypeUtil::instance() {
    static OptionDataTypeUtil instance;
    return (instance);
}

asiolink::IOAddress
OptionDataTypeUtil::readAddress(const std::vector<uint8_t>& buf,
                                const short family) {
    using namespace isc::asiolink;
    if (family == AF_INET) {
        if (buf.size() < V4ADDRESS_LEN) {
            isc_throw(BadDataTypeCast, "unable to read data from the buffer as"
                      << " IPv4 address. Invalid buffer size: " << buf.size());
        }
        return (IOAddress::fromBytes(AF_INET, &buf[0]));
    } else if (family == AF_INET6) {
        if (buf.size() < V6ADDRESS_LEN) {
            isc_throw(BadDataTypeCast, "unable to read data from the buffer as"
                      << " IPv6 address. Invalid buffer size: " << buf.size());
        }
        return (IOAddress::fromBytes(AF_INET6, &buf[0]));
    } else {
        isc_throw(BadDataTypeCast, "unable to read data from the buffer as"
                  "IP address. Invalid family: " << family);
    }
}

void
OptionDataTypeUtil::writeAddress(const asiolink::IOAddress& address,
                                 std::vector<uint8_t>& buf) {
    const std::vector<uint8_t>& vec = address.toBytes();
    buf.insert(buf.end(), vec.begin(), vec.end());
}

void
OptionDataTypeUtil::writeBinary(const std::string& hex_str,
                                std::vector<uint8_t>& buf) {
    // Binary value means that the value is encoded as a string
    // of hexadecimal digits. We need to decode this string
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
    if (buf.empty()) {
        isc_throw(BadDataTypeCast, "unable to read the buffer as boolean"
                  << " value. Invalid buffer size " << buf.size());
    }
    if (buf[0] == 1) {
        return (true);
    } else if (buf[0] == 0) {
        return (false);
    }
    isc_throw(BadDataTypeCast, "unable to read the buffer as boolean"
              << " value. Invalid value " << static_cast<int>(buf[0]));
}

void
OptionDataTypeUtil::writeBool(const bool value,
                              std::vector<uint8_t>& buf) {
    buf.push_back(static_cast<uint8_t>(value ? 1 : 0));
}

std::string
OptionDataTypeUtil::readFqdn(const std::vector<uint8_t>& buf) {
    // If buffer is empty emit an error.
    if (buf.empty()) {
        isc_throw(BadDataTypeCast, "unable to read FQDN from a buffer."
                  << " The buffer is empty.");
    }
    // Set up an InputBuffer so as we can use isc::dns::Name object to get the FQDN.
    isc::util::InputBuffer in_buf(static_cast<const void*>(&buf[0]), buf.size());
    try {
        // Try to create an object from the buffer. If exception is thrown
        // it means that the buffer doesn't hold a valid domain name (invalid
        // syntax).
        isc::dns::Name name(in_buf);
        return (name.toText());
    } catch (const isc::Exception& ex) {
        // Unable to convert the data in the buffer into FQDN.
        isc_throw(BadDataTypeCast, ex.what());
    }
}

void
OptionDataTypeUtil::writeFqdn(const std::string& fqdn,
                              std::vector<uint8_t>& buf,
                              bool downcase) {
    try {
        isc::dns::Name name(fqdn, downcase);
        isc::dns::LabelSequence labels(name);
        if (labels.getDataLength() > 0) {
            size_t read_len = 0;
            const uint8_t* data = labels.getData(&read_len);
            buf.insert(buf.end(), data, data + read_len);
        }
    } catch (const isc::Exception& ex) {
        isc_throw(BadDataTypeCast, ex.what());
    }
}

unsigned int
OptionDataTypeUtil::getLabelCount(const std::string& text_name) {
    // The isc::dns::Name class doesn't accept empty names. However, in some
    // cases we may be dealing with empty names (e.g. sent by the DHCP clients).
    // Empty names should not be sent as hostnames but if they are, for some
    // reason, we don't want to throw an exception from this function. We
    // rather want to signal empty name by returning 0 number of labels.
    if (text_name.empty()) {
        return (0);
    }
    try {
        isc::dns::Name name(text_name);
        return (name.getLabelCount());
    } catch (const isc::Exception& ex) {
        isc_throw(BadDataTypeCast, ex.what());
    }
}

std::string
OptionDataTypeUtil::readString(const std::vector<uint8_t>& buf) {
    std::string value;
    if (!buf.empty()) {
        value.insert(value.end(), buf.begin(), buf.end());
    }
    return (value);
}

void
OptionDataTypeUtil::writeString(const std::string& value,
                                std::vector<uint8_t>& buf) {
    if (value.size() > 0) {
        buf.insert(buf.end(), value.begin(), value.end());
    }
}

} // end of isc::dhcp namespace
} // end of isc namespace
