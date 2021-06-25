// Copyright (C) 2012-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <dhcp/option_data_types.h>
#include <dns/labelsequence.h>
#include <dns/name.h>
#include <util/strutil.h>
#include <util/encode/hex.h>
#include <algorithm>
#include <limits>

using namespace isc::asiolink;

namespace {
/// @brief Bit mask used to compute PSID value.
///
/// The mask represents the useful bits of the PSID. The value 0 is a special
/// case because the RFC explicitly specifies that PSID value should be ignored
/// if psid_len is 0.
std::vector<uint16_t> psid_bitmask = { 0xffff,
    0x8000, 0xc000, 0xe000, 0xf000,
    0xf800, 0xfc00, 0xfe00, 0xff00,
    0xff80, 0xffc0, 0xffe0, 0xfff0,
    0xfff8, 0xfffc, 0xfffe, 0xffff
};
}

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
    data_types_["ipv6-prefix"] = OPT_IPV6_PREFIX_TYPE;
    data_types_["psid"] = OPT_PSID_TYPE;
    data_types_["string"] = OPT_STRING_TYPE;
    data_types_["tuple"] = OPT_TUPLE_TYPE;
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
    data_type_names_[OPT_IPV6_PREFIX_TYPE] = "ipv6-prefix";
    data_type_names_[OPT_PSID_TYPE] = "psid";
    data_type_names_[OPT_STRING_TYPE] = "string";
    data_type_names_[OPT_TUPLE_TYPE] = "tuple";
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

    case OPT_PSID_TYPE:
        return (3);

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
                  << " IP address. Invalid family: " << family);
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

std::string
OptionDataTypeUtil::readTuple(const std::vector<uint8_t>& buf,
                              OpaqueDataTuple::LengthFieldType lengthfieldtype) {
    if (lengthfieldtype == OpaqueDataTuple::LENGTH_1_BYTE) {
        if (buf.size() < 1) {
            isc_throw(BadDataTypeCast, "unable to read data from the buffer as"
                      << " tuple (length). Invalid buffer size: "
                      << buf.size());
        }
        uint8_t len = buf[0];
        if (buf.size() < 1 + len) {
            isc_throw(BadDataTypeCast, "unable to read data from the buffer as"
                      << " tuple (length " << static_cast<unsigned>(len)
                      << "). Invalid buffer size: " << buf.size());
        }
        std::string value;
        value.resize(len);
        std::memcpy(&value[0], &buf[1], len);
        return (value);
    } else if (lengthfieldtype == OpaqueDataTuple::LENGTH_2_BYTES) {
        if (buf.size() < 2) {
            isc_throw(BadDataTypeCast, "unable to read data from the buffer as"
                      << " tuple (length). Invalid buffer size: "
                      << buf.size());
        }
        uint16_t len = isc::util::readUint16(&buf[0], 2);
        if (buf.size() < 2 + len) {
            isc_throw(BadDataTypeCast, "unable to read data from the buffer as"
                      << " tuple (length " << len
                      << "). Invalid buffer size: " << buf.size());
        }
        std::string value;
        value.resize(len);
        std::memcpy(&value[0], &buf[2], len);
        return (value);
    } else {
        isc_throw(BadDataTypeCast, "unable to read data from the buffer as"
                  << " tuple. Invalid length type field: "
                  << static_cast<unsigned>(lengthfieldtype));
    }
}

void
OptionDataTypeUtil::readTuple(const std::vector<uint8_t>& buf,
                              OpaqueDataTuple& tuple) {
    try {
        tuple.unpack(buf.begin(), buf.end());
    } catch (const OpaqueDataTupleError& ex) {
        isc_throw(BadDataTypeCast, ex.what());
    }
}

void
OptionDataTypeUtil::writeTuple(const std::string& value,
                               OpaqueDataTuple::LengthFieldType lengthfieldtype,
                               std::vector<uint8_t>& buf) {
    if (lengthfieldtype == OpaqueDataTuple::LENGTH_1_BYTE) {
        if (value.size() > std::numeric_limits<uint8_t>::max()) {
            isc_throw(BadDataTypeCast, "invalid tuple value (size "
                      << value.size() << " larger than "
                      << +std::numeric_limits<uint8_t>::max() << ")");
        }
        buf.push_back(static_cast<uint8_t>(value.size()));

    } else if (lengthfieldtype == OpaqueDataTuple::LENGTH_2_BYTES) {
        if (value.size() > std::numeric_limits<uint16_t>::max()) {
            isc_throw(BadDataTypeCast, "invalid tuple value (size "
                      << value.size() << " larger than "
                      << std::numeric_limits<uint16_t>::max() << ")");
        }
        buf.resize(buf.size() + 2);
        isc::util::writeUint16(static_cast<uint16_t>(value.size()),
                               &buf[buf.size() - 2], 2);
    } else {
        isc_throw(BadDataTypeCast, "unable to write data to the buffer as"
                  << " tuple. Invalid length type field: "
                  << static_cast<unsigned>(lengthfieldtype));
    }
    buf.insert(buf.end(), value.begin(), value.end());
}

void
OptionDataTypeUtil::writeTuple(const OpaqueDataTuple& tuple,
                               std::vector<uint8_t>& buf) {
    if (tuple.getLength() == 0) {
        isc_throw(BadDataTypeCast, "invalid empty tuple value");
    }
    if (tuple.getLengthFieldType() == OpaqueDataTuple::LENGTH_1_BYTE) {
        if (tuple.getLength() > std::numeric_limits<uint8_t>::max()) {
            isc_throw(BadDataTypeCast, "invalid tuple value (size "
                      << tuple.getLength() << " larger than "
                      << +std::numeric_limits<uint8_t>::max() << ")");
        }
        buf.push_back(static_cast<uint8_t>(tuple.getLength()));

    } else if (tuple.getLengthFieldType() == OpaqueDataTuple::LENGTH_2_BYTES) {
        if (tuple.getLength() > std::numeric_limits<uint16_t>::max()) {
            isc_throw(BadDataTypeCast, "invalid tuple value (size "
                      << tuple.getLength() << " larger than "
                      << std::numeric_limits<uint16_t>::max() << ")");
        }
        buf.resize(buf.size() + 2);
        isc::util::writeUint16(static_cast<uint16_t>(tuple.getLength()),
                               &buf[buf.size() - 2], 2);
    } else {
        isc_throw(BadDataTypeCast, "unable to write data to the buffer as"
                  << " tuple. Invalid length type field: "
                  << tuple.getLengthFieldType());
    }
    buf.insert(buf.end(), tuple.getData().begin(), tuple.getData().end());
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

PrefixTuple
OptionDataTypeUtil::readPrefix(const std::vector<uint8_t>& buf) {
    // Prefix typically consists of the prefix length and the
    // actual value. If prefix length is 0, the buffer length should
    // be at least 1 byte to hold this length value.
    if (buf.empty()) {
        isc_throw(BadDataTypeCast, "unable to read prefix length from "
                  "a truncated buffer");
    }

    // Surround everything with try-catch to unify exceptions being
    // thrown by various functions and constructors.
    try {
        // Try to create PrefixLen object from the prefix length held
        // in the buffer. This may cause an exception if the length is
        // invalid (greater than 128).
        PrefixLen prefix_len(buf.at(0));

        // Convert prefix length to bytes, because we operate on bytes,
        // rather than bits.
        uint8_t prefix_len_bytes = (prefix_len.asUint8() / 8);
        // Check if we need to zero pad any bits. This is the case when
        // the prefix length is not divisible by 8 (bits per byte). The
        // calculations below may require some explanations. We first
        // perform prefix_len % 8 to get the number of useful bits beyond
        // the current prefix_len_bytes value. By substracting it from 8
        // we get the number of zero padded bits, but with the special
        // case of 8 when the result of substraction is 0. The value of
        // 8 really means no padding so we make a modulo division once
        // again to turn 8s to 0s.
        const uint8_t zero_padded_bits =
            static_cast<uint8_t>((8 - (prefix_len.asUint8() % 8)) % 8);
        // If there are zero padded bits, it means that we need an extra
        // byte to be retrieved from the buffer.
        if (zero_padded_bits > 0) {
            ++prefix_len_bytes;
        }

        // Make sure that the buffer is long enough. We substract 1 to
        // also account for the fact that the buffer includes a prefix
        // length besides a prefix.
        if ((buf.size() - 1) < prefix_len_bytes) {
            isc_throw(BadDataTypeCast, "unable to read a prefix having length of "
                      << prefix_len.asUnsigned() << " from a truncated buffer");
        }

        // It is possible for a prefix to be zero if the prefix length
        // is zero.
        IOAddress prefix(IOAddress::IPV6_ZERO_ADDRESS());

        // If there is anything more than prefix length is this buffer
        // we need to read it.
        if (buf.size() > 1) {
            // Buffer has to be copied, because we will modify its
            // contents by setting certain bits to 0, if necessary.
            std::vector<uint8_t> prefix_buf(buf.begin() + 1, buf.end());
            // All further conversions require that the buffer length is
            // 16 bytes.
            if (prefix_buf.size() < V6ADDRESS_LEN) {
                prefix_buf.resize(V6ADDRESS_LEN);
                if (prefix_len_bytes < prefix_buf.size()) {
                    // Zero all bits in the buffer beyond prefix length
                    // position.
                    std::fill(prefix_buf.begin() + prefix_len_bytes,
                              prefix_buf.end(), 0);

                    if (zero_padded_bits) {
                        // There is a byte that require zero padding. We
                        // achieve that by shifting the value of that byte
                        // back and forth by the number of zeroed bits.
                        prefix_buf.at(prefix_len_bytes - 1) =
                            (prefix_buf.at(prefix_len_bytes - 1)
                             >> zero_padded_bits)
                            << zero_padded_bits;
                    }
                }
            }
            // Convert the buffer to the IOAddress object.
            prefix = IOAddress::fromBytes(AF_INET6, &prefix_buf[0]);
        }

        return (std::make_pair(prefix_len, prefix));

    } catch (const BadDataTypeCast& ex) {
        // Pass through the BadDataTypeCast exceptions.
        throw;

    } catch (const std::exception& ex) {
        // If an exception of a different type has been thrown, insert
        // a text that indicates that the failure occurred during reading
        // the prefix and modify exception type to BadDataTypeCast.
        isc_throw(BadDataTypeCast, "unable to read a prefix from a buffer: "
                  << ex.what());
    }
}

void
OptionDataTypeUtil::writePrefix(const PrefixLen& prefix_len,
                                const IOAddress& prefix,
                                std::vector<uint8_t>& buf) {
    // Prefix must be an IPv6 prefix.
    if (!prefix.isV6()) {
        isc_throw(BadDataTypeCast, "illegal prefix value "
                  << prefix);
    }

    // We don't need to validate the prefix_len value, because it is
    // already validated by the PrefixLen class.
    buf.push_back(prefix_len.asUint8());

    // Convert the prefix length to a number of bytes.
    uint8_t prefix_len_bytes = prefix_len.asUint8() / 8;
    // Check if there are any bits that require zero padding. See the
    // commentary in readPrefix to see how this is calculated.
    const uint8_t zero_padded_bits =
        static_cast<uint8_t>((8 - (prefix_len.asUint8() % 8)) % 8);
    // If zero padding is needed it means that we need to extend the
    // buffer to hold the "partially occupied" byte.
    if (zero_padded_bits > 0) {
        ++prefix_len_bytes;
    }

    // Convert the prefix to byte representation and append it to
    // our output buffer.
    std::vector<uint8_t> prefix_bytes = prefix.toBytes();
    buf.insert(buf.end(), prefix_bytes.begin(),
               prefix_bytes.begin() + prefix_len_bytes);
    // If the last byte requires zero padding we achieve that by shifting
    // bits back and forth by the number of insignificant bits.
    if (zero_padded_bits) {
        *buf.rbegin() = (*buf.rbegin() >> zero_padded_bits) << zero_padded_bits;
    }
}

PSIDTuple
OptionDataTypeUtil::readPsid(const std::vector<uint8_t>& buf) {
    if (buf.size() < 3) {
        isc_throw(BadDataTypeCast, "unable to read PSID from the buffer."
                  << " Invalid buffer size " << buf.size()
                  << ". Expected 3 bytes (PSID length and PSID value)");
    }

    // Read PSID length.
    uint8_t psid_len = buf[0];

    // PSID length must not be greater than 16 bits.
    if (psid_len > (sizeof(uint16_t) * 8)) {
        isc_throw(BadDataTypeCast, "invalid PSID length value "
                  << static_cast<unsigned>(psid_len)
                  << ", this value is expected to be in range of 0 to 16");
    }

    // Read two bytes of PSID value.
    uint16_t psid = isc::util::readUint16(&buf[1], 2);

    // We need to check that the PSID value does not exceed the maximum value
    // for a specified PSID length. That means that all bits placed further than
    // psid_len from the left must be set to 0.
    // The value 0 is a special case because the RFC explicitly says that the
    // PSID value should be ignored if psid_len is 0.
    if ((psid & ~psid_bitmask[psid_len]) != 0) {
        isc_throw(BadDataTypeCast, "invalid PSID value " << psid
                  << " for a specified PSID length "
                  << static_cast<unsigned>(psid_len));
    }

    // All is good, so we can convert the PSID value read from the buffer to
    // the port set number.
    if (psid_len == 0) {
        // Shift by 16 always gives zero (CID 1398333)
        psid = 0;
    } else {
        psid >>= (sizeof(psid) * 8 - psid_len);
    }
    return (std::make_pair(PSIDLen(psid_len), PSID(psid)));
}

void
OptionDataTypeUtil::writePsid(const PSIDLen& psid_len, const PSID& psid,
                              std::vector<uint8_t>& buf) {
    if (psid_len.asUint8() > (sizeof(psid) * 8)) {
        isc_throw(BadDataTypeCast, "invalid PSID length value "
                  << psid_len.asUnsigned()
                  << ", this value is expected to be in range of 0 to 16");
    }

    if ((psid_len.asUint8() > 0) &&
        (psid.asUint16() > (0xFFFF >> (sizeof(uint16_t) * 8 - psid_len.asUint8())))) {
        isc_throw(BadDataTypeCast, "invalid PSID value " << psid.asUint16()
                  << " for a specified PSID length "
                  << psid_len.asUnsigned());
    }

    buf.resize(buf.size() + 3);
    buf.at(buf.size() - 3) = psid_len.asUint8();
    isc::util::writeUint16(static_cast<uint16_t>
                           (psid.asUint16() << (sizeof(uint16_t) * 8 - psid_len.asUint8())),
                           &buf[buf.size() - 2], 2);
}

std::string
OptionDataTypeUtil::readString(const std::vector<uint8_t>& buf) {
    std::string value;
    if (!buf.empty()) {
        // Per RFC 2132, section 2 we need to drop trailing NULLs
        auto begin = buf.begin();
        auto end = util::str::seekTrimmed(begin, buf.end(), 0x0);
        if (std::distance(begin, end) == 0) {
            isc_throw(isc::OutOfRange, "string value carried by the option "
                                       "contained only NULLs");
        }

        value.insert(value.end(), begin, end);
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
