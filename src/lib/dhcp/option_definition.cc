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

#include "dhcp/dhcp6.h"
#include "dhcp/option_definition.h"
#include "dhcp/option4_addrlst.h"
#include "dhcp/option6_addrlst.h"
#include "dhcp/option6_ia.h"
#include "dhcp/option6_iaaddr.h"
#include "dhcp/option6_int.h"
#include "dhcp/option6_int_array.h"

using namespace std;
using namespace isc::util;

namespace isc {
namespace dhcp {

OptionDefinition::DataTypeUtil::DataTypeUtil() {
    data_types_["empty"] = EMPTY_TYPE;
    data_types_["boolean"] = BOOLEAN_TYPE;
    data_types_["int8"] = INT8_TYPE;
    data_types_["int16"] = INT16_TYPE;
    data_types_["int32"] = INT32_TYPE;
    data_types_["uint8"] = UINT8_TYPE;
    data_types_["uint16"] = UINT16_TYPE;
    data_types_["uint32"] = UINT32_TYPE;
    data_types_["ipv4-address"] = IPV4_ADDRESS_TYPE;
    data_types_["ipv6-address"] = IPV6_ADDRESS_TYPE;
    data_types_["string"] = STRING_TYPE;
    data_types_["fqdn"] = FQDN_TYPE;
    data_types_["record"] = RECORD_TYPE;
}

OptionDefinition::DataType
OptionDefinition::DataTypeUtil::getDataType(const std::string& data_type) {
    std::map<std::string, DataType>::const_iterator data_type_it =
        data_types_.find(data_type);
    if (data_type_it != data_types_.end()) {
        return (data_type_it->second);
    }
    return UNKNOWN_TYPE;
}

OptionDefinition::OptionDefinition(const std::string& name,
                                 const uint16_t code,
                                 const std::string& type,
                                 const bool array_type /* = false */)
    : name_(name),
      code_(code),
      type_(UNKNOWN_TYPE),
      array_type_(array_type) {
    // Data type is held as enum value by this class.
    // Use the provided option type string to get the
    // corresponding enum value.
    type_ = DataTypeUtil::instance().getDataType(type);
}

OptionDefinition::OptionDefinition(const std::string& name,
                                   const uint16_t code,
                                   const DataType type,
                                   const bool array_type /* = false */)
    : name_(name),
      code_(code),
      type_(type),
      array_type_(array_type) {
}

void
OptionDefinition::addRecordField(const std::string& data_type_name) {
    DataType data_type = DataTypeUtil::instance().getDataType(data_type_name);
    addRecordField(data_type);
}

void
OptionDefinition::addRecordField(const DataType data_type) {
    if (type_ != RECORD_TYPE) {
        isc_throw(isc::InvalidOperation, "'record' option type must be used"
                  " to add data fields to the record");
    }
    if (data_type >= UNKNOWN_TYPE) {
        isc_throw(isc::BadValue, "attempted to add invalid data type to the record");
    }
    record_fields_.push_back(data_type);
}

Option::Factory*
OptionDefinition::getFactory() const {
    if (type_ == IPV6_ADDRESS_TYPE && array_type_) {
        return (factoryAddrList6);
    } else if (type_ == IPV4_ADDRESS_TYPE && array_type_) {
        return (factoryAddrList4);
    } else if (type_ == EMPTY_TYPE) {
        return (factoryEmpty);
    } else if (code_ == D6O_IA_NA && haveIA6Format()) {
        return (factoryIA6);
    } else if (code_ == D6O_IAADDR && haveIAAddr6Format()) {
        return (factoryIAAddr6);
    } else if (type_ == UINT8_TYPE) {
        if (array_type_) {
            return (factoryGeneric);
        } else {
            return (factoryInteger<uint8_t>);
        }
    } else if (type_ == UINT16_TYPE) {
        if (array_type_) {
            return (factoryIntegerArray<uint16_t>);
        } else {
            return (factoryInteger<uint16_t>);
        }
    } else if (type_ == UINT32_TYPE) {
        if (array_type_) {
            return (factoryIntegerArray<uint32_t>);
        } else {
            return (factoryInteger<uint32_t>);
        }
    }
    return (factoryGeneric);
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
    if (type_ >= UNKNOWN_TYPE) {
        isc_throw(isc::OutOfRange, "option type value " << type_
                  << " is out of range");
    }
}

bool
OptionDefinition::haveIA6Format() const {
    // Expect that IA_NA option format is defined as record.
    // Although it consists of 3 elements of the same (uint32)
    // type it can't be defined as array of uint32 elements because
    // arrays do not impose limitations on number of elements in
    // the array while this limitation is needed for IA_NA - need
    // exactly 3 elements.
    if (haveType(RECORD_TYPE)) {
        if (record_fields_.size() == 3) {
            for (RecordFieldsConstIter it = record_fields_.begin();
                 it != record_fields_.end(); ++it) {
                if (*it != UINT32_TYPE) {
                    return (false);
                }
            }
            return (true);
        }
    }
    return (false);
}

bool
OptionDefinition::haveIAAddr6Format() const {
    if (haveType(RECORD_TYPE)) {
        if (record_fields_.size() == 3) {
            if (record_fields_[0] == IPV6_ADDRESS_TYPE &&
                record_fields_[1] == UINT32_TYPE &&
                record_fields_[2] == UINT32_TYPE) {
                return (true);
            }
        }
    }
    return (false);
}

OptionPtr
OptionDefinition::factoryAddrList4(Option::Universe u, uint16_t type,
                                   const OptionBuffer& buf) {
    sanityCheckUniverse(u, Option::V4);
    boost::shared_ptr<Option4AddrLst> option(new Option4AddrLst(type, buf.begin(),
                                                                buf.begin() + buf.size()));
    return (option);
}

OptionPtr
OptionDefinition::factoryAddrList6(Option::Universe u, uint16_t type,
                                   const OptionBuffer& buf) {
    sanityCheckUniverse(u, Option::V6);
    boost::shared_ptr<Option6AddrLst> option(new Option6AddrLst(type, buf.begin(),
                                                                buf.begin() + buf.size()));
    return (option);
}


OptionPtr
OptionDefinition::factoryEmpty(Option::Universe u, uint16_t type, const OptionBuffer& buf) {
    if (buf.size() > 0) {
        isc_throw(isc::BadValue, "input option buffer must be empty"
                  " when creating empty option instance");
    }
    OptionPtr option(new Option(u, type));
    return (option);
}

OptionPtr
OptionDefinition::factoryGeneric(Option::Universe u, uint16_t type, const OptionBuffer& buf) {
    OptionPtr option(new Option(u, type, buf));
    return (option);
}

OptionPtr
OptionDefinition::factoryIA6(Option::Universe u, uint16_t type, const OptionBuffer& buf) {
    sanityCheckUniverse(u, Option::V6);
    if (buf.size() != Option6IA::OPTION6_IA_LEN) {
        isc_throw(isc::OutOfRange, "input option buffer has invalid size, expeted "
                  << Option6IA::OPTION6_IA_LEN << " bytes");
    }
    boost::shared_ptr<Option6IA> option(new Option6IA(type, buf.begin(),
                                                      buf.begin() + buf.size()));
    return (option);
}

OptionPtr
OptionDefinition::factoryIAAddr6(Option::Universe u, uint16_t type, const OptionBuffer& buf) {
    sanityCheckUniverse(u, Option::V6);
    if (buf.size() != Option6IAAddr::OPTION6_IAADDR_LEN) {
        isc_throw(isc::OutOfRange, "input option buffer has invalid size, expeted "
                  << Option6IAAddr::OPTION6_IAADDR_LEN << " bytes");
    }
    boost::shared_ptr<Option6IAAddr> option(new Option6IAAddr(type, buf.begin(),
                                                      buf.begin() + buf.size()));
    return (option);
}


} // end of isc::dhcp namespace
} // end of isc namespace
