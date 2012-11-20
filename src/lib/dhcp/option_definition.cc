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

#include <dhcp/dhcp6.h>
#include <dhcp/option4_addrlst.h>
#include <dhcp/option6_addrlst.h>
#include <dhcp/option6_ia.h>
#include <dhcp/option6_iaaddr.h>
#include <dhcp/option6_int.h>
#include <dhcp/option6_int_array.h>
#include <dhcp/option_definition.h>
#include <util/encode/hex.h>

using namespace std;
using namespace isc::util;

namespace isc {
namespace dhcp {

OptionDefinition::DataTypeUtil::DataTypeUtil() {
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
}

OptionDataType
OptionDefinition::DataTypeUtil::getOptionDataType(const std::string& data_type) {
    std::map<std::string, OptionDataType>::const_iterator data_type_it =
        data_types_.find(data_type);
    if (data_type_it != data_types_.end()) {
        return (data_type_it->second);
    }
    return (OPT_UNKNOWN_TYPE);
}

template<typename T>
T OptionDefinition::DataTypeUtil::lexicalCastWithRangeCheck(const std::string& value_str) const {
    if (!OptionDataTypeTraits<T>::integer_type &&
        OptionDataTypeTraits<T>::type != OPT_BOOLEAN_TYPE) {
        isc_throw(BadDataTypeCast, "unable to do lexical cast to non-integer and"
                  << " non-boolean data type");
    }
    int64_t result = 0;
    try {
        result = boost::lexical_cast<int64_t>(value_str);
    } catch (const boost::bad_lexical_cast& ex) {
        std::string data_type_str = "boolean";
        if (OptionDataTypeTraits<T>::integer_type) {
            data_type_str = "integer";
        }
        isc_throw(BadDataTypeCast, "unable to do lexical cast to " << data_type_str
                  << " data type for value " << value_str << ": " << ex.what());
    }
    if (OptionDataTypeTraits<T>::integer_type) {
        if (result > numeric_limits<T>::max() ||
            result < numeric_limits<T>::min()) {
            isc_throw(BadDataTypeCast, "unable to do lexical cast for value "
                      << value_str << ". This value is expected to be in the range of "
                      << numeric_limits<T>::min() << ".." << numeric_limits<T>::max());
        }
    }
    return (static_cast<T>(result));
}

void
OptionDefinition::DataTypeUtil::writeToBuffer(const std::string& value, uint16_t type,
                                              OptionBuffer& buf) {
    switch (type) {
    case OPT_BINARY_TYPE:
        {
            OptionBuffer binary;
            try {
                util::encode::decodeHex(value, binary);
            } catch (const Exception& ex) {
                isc_throw(BadDataTypeCast, "unable to cast " << value
                          << " to binary data type: " << ex.what());
            }
            buf.insert(buf.end(), binary.begin(), binary.end());
            return;
        }
    case OPT_BOOLEAN_TYPE:
        {
            bool bool_value = lexicalCastWithRangeCheck<bool>(value);
            if (bool_value) {
                buf.push_back(static_cast<uint8_t>(1));
            } else {
                buf.push_back(static_cast<uint8_t>(0));
            }
            return;
        }
    case OPT_INT8_TYPE:
        {
            buf.push_back(static_cast<uint8_t>(lexicalCastWithRangeCheck<int8_t>(value)));
            return;
        }
    case OPT_INT16_TYPE:
        {
            int16_t int_value = lexicalCastWithRangeCheck<int16_t>(value);
            buf.resize(buf.size() + 2);
            writeUint16(static_cast<uint16_t>(int_value), &buf[buf.size() - 2]);
            return;
        }
    case OPT_INT32_TYPE:
        {
            int32_t int_value = lexicalCastWithRangeCheck<int32_t>(value);
            buf.resize(buf.size() + 4);
            writeUint32(static_cast<uint32_t>(int_value), &buf[buf.size() - 4]);
            return;
        }
    case OPT_UINT8_TYPE:
        {
            buf.push_back(lexicalCastWithRangeCheck<int8_t>(value));
            return;
        }
    case OPT_UINT16_TYPE:
        {
            uint16_t uint_value = lexicalCastWithRangeCheck<uint16_t>(value);
            buf.resize(buf.size() + 2);
            writeUint16(uint_value, &buf[buf.size() - 2]);
            return;
        }
    case OPT_UINT32_TYPE:
        {
            uint32_t uint_value = lexicalCastWithRangeCheck<uint32_t>(value);
            buf.resize(buf.size() + 4);
            writeUint32(uint_value, &buf[buf.size() - 4]);
            return;
        }
    case OPT_IPV4_ADDRESS_TYPE:
        {
            asiolink::IOAddress address(value);
            if (!address.getAddress().is_v4()) {
                isc_throw(BadDataTypeCast, "provided address " << address.toText()
                          << " is not a valid IPV4 address");
            }
            asio::ip::address_v4::bytes_type addr_bytes =
                address.getAddress().to_v4().to_bytes();
            buf.resize(buf.size() + addr_bytes.size());
            std::copy_backward(addr_bytes.begin(), addr_bytes.end(),
                               buf.end());
            return;
        }
    case OPT_IPV6_ADDRESS_TYPE:
        {
            asiolink::IOAddress address(value);
            if (!address.getAddress().is_v6()) {
                isc_throw(BadDataTypeCast, "provided address " << address.toText()
                          << " is not a valid IPV6 address");
            }
            asio::ip::address_v6::bytes_type addr_bytes =
                address.getAddress().to_v6().to_bytes();
            buf.resize(buf.size() + addr_bytes.size());
            std::copy_backward(addr_bytes.begin(), addr_bytes.end(),
                               buf.end());
            return;
        }
    default:
        ;
    }
    isc_throw(isc::NotImplemented, "write of string, FQDN record into option buffer"
              " is not supported yet");

}

OptionDefinition::OptionDefinition(const std::string& name,
                                 const uint16_t code,
                                 const std::string& type,
                                 const bool array_type /* = false */)
    : name_(name),
      code_(code),
      type_(OPT_UNKNOWN_TYPE),
      array_type_(array_type) {
    // Data type is held as enum value by this class.
    // Use the provided option type string to get the
    // corresponding enum value.
    type_ = DataTypeUtil::instance().getOptionDataType(type);
}

OptionDefinition::OptionDefinition(const std::string& name,
                                   const uint16_t code,
                                   const OptionDataType type,
                                   const bool array_type /* = false */)
    : name_(name),
      code_(code),
      type_(type),
      array_type_(array_type) {
}

void
OptionDefinition::addRecordField(const std::string& data_type_name) {
    OptionDataType data_type = DataTypeUtil::instance().getOptionDataType(data_type_name);
    addRecordField(data_type);
}

void
OptionDefinition::addRecordField(const OptionDataType data_type) {
    if (type_ != OPT_RECORD_TYPE) {
        isc_throw(isc::InvalidOperation, "'record' option type must be used"
                  " to add data fields to the record");
    }
    if (data_type >= OPT_UNKNOWN_TYPE) {
        isc_throw(isc::BadValue, "attempted to add invalid data type to the record");
    }
    record_fields_.push_back(data_type);
}

OptionPtr
OptionDefinition::optionFactory(Option::Universe u, uint16_t type,
                                OptionBufferConstIter begin,
                                OptionBufferConstIter end) const {
    validate();
    
    if (type_ == OPT_BINARY_TYPE) {
        return (factoryGeneric(u, type, begin, end));
    } else if (type_ == OPT_IPV6_ADDRESS_TYPE && array_type_) {
        return (factoryAddrList6(u, type, begin, end));
    } else if (type_ == OPT_IPV4_ADDRESS_TYPE && array_type_) {
        return (factoryAddrList4(u, type, begin, end));
    } else if (type_ == OPT_EMPTY_TYPE) {
        return (factoryEmpty(u, type, begin, end));
    } else if (code_ == D6O_IA_NA && haveIA6Format()) {
        return (factoryIA6(u, type, begin, end));
    } else if (code_ == D6O_IAADDR && haveIAAddr6Format()) {
        return (factoryIAAddr6(u, type, begin, end));
    } else if (type_ == OPT_UINT8_TYPE) {
        if (array_type_) {
            return (factoryGeneric(u, type, begin, end));
        } else {
            return (factoryInteger<uint8_t>(u, type, begin, end));
        }
    } else if (type_ == OPT_UINT16_TYPE) {
        if (array_type_) {
            return (factoryIntegerArray<uint16_t>(u, type, begin, end));
        } else {
            return (factoryInteger<uint16_t>(u, type, begin, end));
        }
    } else if (type_ == OPT_UINT32_TYPE) {
        if (array_type_) {
            return (factoryIntegerArray<uint32_t>(u, type, begin, end));
        } else {
            return (factoryInteger<uint32_t>(u, type, begin, end));
        }
    }
    return (factoryGeneric(u, type, begin, end));
}

OptionPtr
OptionDefinition::optionFactory(Option::Universe u, uint16_t type,
                                const OptionBuffer& buf) const {
    return (optionFactory(u, type, buf.begin(), buf.end()));
}

OptionPtr
OptionDefinition::optionFactory(Option::Universe u, uint16_t type,
                                const std::vector<std::string>& values) const {
    validate();

    OptionBuffer buf;
    if (!array_type_ && type_ != OPT_RECORD_TYPE) {
        if (values.size() == 0) {
            isc_throw(InvalidOptionValue, "no option value specified");
        }
        DataTypeUtil::instance().writeToBuffer(values[0], type_, buf);
    } else if (array_type_ && type_ != OPT_RECORD_TYPE) {
        for (size_t i = 0; i < values.size(); ++i) {
            DataTypeUtil::instance().writeToBuffer(values[i], type_, buf);
        }
    } else if (type_ == OPT_RECORD_TYPE) {
        const RecordFieldsCollection& records = getRecordFields();
        if (records.size() > values.size()) {
            isc_throw(InvalidOptionValue, "number of data fields for the option"
                      << " type " << type_ << " is greater than number of values"
                      << " provided.");
        }
        for (size_t i = 0; i < records.size(); ++i) {
            DataTypeUtil::instance().writeToBuffer(values[i], records[i], buf);
        }
    }
    return (optionFactory(u, type, buf.begin(), buf.end()));
}

void
OptionDefinition::sanityCheckUniverse(const Option::Universe expected_universe,
                                      const Option::Universe actual_universe) {
    if (expected_universe != actual_universe) {
        isc_throw(isc::BadValue, "invalid universe specified for the option");
    }
}

void
OptionDefinition::validate() const {
    // Option name must not be empty.
    if (name_.empty()) {
        isc_throw(isc::BadValue, "option name must not be empty");
    }
    // Option name must not contain spaces.
    if (name_.find(" ") != string::npos) {
        isc_throw(isc::BadValue, "option name must not contain spaces");
    }
    // Unsupported option types are not allowed.
    if (type_ >= OPT_UNKNOWN_TYPE) {
        isc_throw(isc::OutOfRange, "option type value " << type_
                  << " is out of range");
    }
}

bool
OptionDefinition::haveIAx6Format(OptionDataType first_type) const {
   return (haveType(OPT_RECORD_TYPE) &&
           record_fields_.size() == 3 &&
           record_fields_[0] == first_type &&
           record_fields_[1] == OPT_UINT32_TYPE &&
           record_fields_[2] == OPT_UINT32_TYPE);
}

bool
OptionDefinition::haveIA6Format() const {
    // Expect that IA_NA option format is defined as record.
    // Although it consists of 3 elements of the same (uint32)
    // type it can't be defined as array of uint32 elements because
    // arrays do not impose limitations on number of elements in
    // the array while this limitation is needed for IA_NA - need
    // exactly 3 elements.
    return (haveIAx6Format(OPT_UINT32_TYPE));
}

bool
OptionDefinition::haveIAAddr6Format() const {
    return (haveIAx6Format(OPT_IPV6_ADDRESS_TYPE));
}

OptionPtr
OptionDefinition::factoryAddrList4(Option::Universe u, uint16_t type,
                                  OptionBufferConstIter begin,
                                  OptionBufferConstIter end) {
    sanityCheckUniverse(u, Option::V4);
    boost::shared_ptr<Option4AddrLst> option(new Option4AddrLst(type, begin, end));
    return (option);
}

OptionPtr
OptionDefinition::factoryAddrList6(Option::Universe u, uint16_t type,
                                   OptionBufferConstIter begin,
                                   OptionBufferConstIter end) {
    sanityCheckUniverse(u, Option::V6);
    boost::shared_ptr<Option6AddrLst> option(new Option6AddrLst(type, begin, end));
    return (option);
}


OptionPtr
OptionDefinition::factoryEmpty(Option::Universe u, uint16_t type,
                               OptionBufferConstIter,
                               OptionBufferConstIter) {
    OptionPtr option(new Option(u, type));
    return (option);
}

OptionPtr
OptionDefinition::factoryGeneric(Option::Universe u, uint16_t type,
                                 OptionBufferConstIter begin,
                                 OptionBufferConstIter end) {
    OptionPtr option(new Option(u, type, begin, end));
    return (option);
}

OptionPtr
OptionDefinition::factoryIA6(Option::Universe u, uint16_t type,
                             OptionBufferConstIter begin,
                             OptionBufferConstIter end) {
    sanityCheckUniverse(u, Option::V6);
    if (std::distance(begin, end) < Option6IA::OPTION6_IA_LEN) {
        isc_throw(isc::OutOfRange, "input option buffer has invalid size, expected "
                  "at least " << Option6IA::OPTION6_IA_LEN << " bytes");
    }
    boost::shared_ptr<Option6IA> option(new Option6IA(type, begin, end));
    return (option);
}

OptionPtr
OptionDefinition::factoryIAAddr6(Option::Universe u, uint16_t type,
                                 OptionBufferConstIter begin,
                                 OptionBufferConstIter end) {
    sanityCheckUniverse(u, Option::V6);
    if (std::distance(begin, end) < Option6IAAddr::OPTION6_IAADDR_LEN) {
        isc_throw(isc::OutOfRange, "input option buffer has invalid size, expected "
                  " at least " << Option6IAAddr::OPTION6_IAADDR_LEN << " bytes");
    }
    boost::shared_ptr<Option6IAAddr> option(new Option6IAAddr(type, begin, end));
    return (option);
}


} // end of isc::dhcp namespace
} // end of isc namespace
