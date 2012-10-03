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

#include "dhcp/option_definition.h"
#include "dhcp/option4_addrlst.h"
#include "dhcp/option6_addrlst.h"
#include "dhcp/option6_int.h"

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
    return (OptionDefinition::factoryEmpty);
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

} // end of isc::dhcp namespace
} // end of isc namespace
