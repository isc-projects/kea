// Copyright (C) 2012-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <dhcp/dhcp4.h>
#include <dhcp/dhcp6.h>
#include <dhcp/option4_addrlst.h>
#include <dhcp/option4_client_fqdn.h>
#include <dhcp/option6_addrlst.h>
#include <dhcp/option6_ia.h>
#include <dhcp/option6_iaaddr.h>
#include <dhcp/option6_iaprefix.h>
#include <dhcp/option6_client_fqdn.h>
#include <dhcp/option6_status_code.h>
#include <dhcp/option_custom.h>
#include <dhcp/option_definition.h>
#include <dhcp/option_int.h>
#include <dhcp/option_int_array.h>
#include <dhcp/option_opaque_data_tuples.h>
#include <dhcp/option_space.h>
#include <dhcp/option_string.h>
#include <dhcp/option_vendor.h>
#include <dhcp/option_vendor_class.h>
#include <util/encode/hex.h>
#include <util/strutil.h>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/predicate.hpp>

using namespace std;
using namespace isc::util;

namespace isc {
namespace dhcp {


OptionDefinition::OptionDefinition(const std::string& name,
                                 const uint16_t code,
                                 const std::string& type,
                                 const bool array_type /* = false */)
    : name_(name),
      code_(code),
      type_(OPT_UNKNOWN_TYPE),
      array_type_(array_type),
      encapsulated_space_("") {
    // Data type is held as enum value by this class.
    // Use the provided option type string to get the
    // corresponding enum value.
    type_ = OptionDataTypeUtil::getDataType(type);
}

OptionDefinition::OptionDefinition(const std::string& name,
                                   const uint16_t code,
                                   const OptionDataType type,
                                   const bool array_type /* = false */)
    : name_(name),
      code_(code),
      type_(type),
      array_type_(array_type),
      encapsulated_space_("") {
}

OptionDefinition::OptionDefinition(const std::string& name,
                                   const uint16_t code,
                                   const std::string& type,
                                   const char* encapsulated_space)
    : name_(name),
      code_(code),
      // Data type is held as enum value by this class.
      // Use the provided option type string to get the
      // corresponding enum value.
      type_(OptionDataTypeUtil::getDataType(type)),
      array_type_(false),
      encapsulated_space_(encapsulated_space) {
}

OptionDefinition::OptionDefinition(const std::string& name,
                                   const uint16_t code,
                                   const OptionDataType type,
                                   const char* encapsulated_space)
    : name_(name),
      code_(code),
      type_(type),
      array_type_(false),
      encapsulated_space_(encapsulated_space) {
}

bool
OptionDefinition::equals(const OptionDefinition& other) const {
    return (name_ == other.name_ &&
            code_ == other.code_ &&
            type_ == other.type_ &&
            array_type_ == other.array_type_ &&
            encapsulated_space_ == other.encapsulated_space_ &&
            record_fields_ == other.record_fields_);
}

void
OptionDefinition::addRecordField(const std::string& data_type_name) {
    OptionDataType data_type = OptionDataTypeUtil::getDataType(data_type_name);
    addRecordField(data_type);
}

void
OptionDefinition::addRecordField(const OptionDataType data_type) {
    if (type_ != OPT_RECORD_TYPE) {
        isc_throw(isc::InvalidOperation, "'record' option type must be used"
                  " to add data fields to the record");
    }
    if (data_type >= OPT_RECORD_TYPE ||
        data_type == OPT_ANY_ADDRESS_TYPE ||
        data_type == OPT_EMPTY_TYPE) {
        isc_throw(isc::BadValue,
                  "attempted to add invalid data type to the record.");
    }
    record_fields_.push_back(data_type);
}

OptionPtr
OptionDefinition::optionFactory(Option::Universe u, uint16_t type,
                                OptionBufferConstIter begin,
                                OptionBufferConstIter end,
                                UnpackOptionsCallback callback) const {

    try {
        // Some of the options are represented by the specialized classes derived
        // from Option class (e.g. IA_NA, IAADDR). Although, they can be also
        // represented by the generic classes, we want the object of the specialized
        // type to be returned. Therefore, we first check that if we are dealing
        // with such an option. If the instance is returned we just exit at this
        // point. If not, we will search for a generic option type to return.
        OptionPtr option = factorySpecialFormatOption(u, begin, end, callback);
        if (option) {
            return (option);
        }

        switch(type_) {
        case OPT_EMPTY_TYPE:
            if (getEncapsulatedSpace().empty()) {
                    return (factoryEmpty(u, type));
            } else {
                return (OptionPtr(new OptionCustom(*this, u, begin, end)));
            }

        case OPT_BINARY_TYPE:
            return (factoryGeneric(u, type, begin, end));

        case OPT_UINT8_TYPE:
            return (array_type_ ?
                    factoryIntegerArray<uint8_t>(u, type, begin, end) :
                    factoryInteger<uint8_t>(u, type, getEncapsulatedSpace(),
                                            begin, end, callback));

        case OPT_INT8_TYPE:
            return (array_type_ ?
                    factoryIntegerArray<int8_t>(u, type, begin, end) :
                    factoryInteger<int8_t>(u, type, getEncapsulatedSpace(),
                                           begin, end, callback));

        case OPT_UINT16_TYPE:
            return (array_type_ ?
                    factoryIntegerArray<uint16_t>(u, type, begin, end) :
                    factoryInteger<uint16_t>(u, type, getEncapsulatedSpace(),
                                             begin, end, callback));

        case OPT_INT16_TYPE:
            return (array_type_ ?
                    factoryIntegerArray<uint16_t>(u, type, begin, end) :
                    factoryInteger<int16_t>(u, type, getEncapsulatedSpace(),
                                            begin, end, callback));

        case OPT_UINT32_TYPE:
            return (array_type_ ?
                    factoryIntegerArray<uint32_t>(u, type, begin, end) :
                    factoryInteger<uint32_t>(u, type, getEncapsulatedSpace(),
                                             begin, end, callback));

        case OPT_INT32_TYPE:
            return (array_type_ ?
                    factoryIntegerArray<uint32_t>(u, type, begin, end) :
                    factoryInteger<int32_t>(u, type, getEncapsulatedSpace(),
                                            begin, end, callback));

        case OPT_IPV4_ADDRESS_TYPE:
            // If definition specifies that an option is an array
            // of IPv4 addresses we return an instance of specialized
            // class (OptionAddrLst4). For non-array types there is no
            // specialized class yet implemented so we drop through
            // to return an instance of OptionCustom.
            if (array_type_) {
                return (factoryAddrList4(type, begin, end));
            }
            break;

        case OPT_IPV6_ADDRESS_TYPE:
            // Handle array type only here (see comments for
            // OPT_IPV4_ADDRESS_TYPE case).
            if (array_type_) {
                return (factoryAddrList6(type, begin, end));
            }
            break;

        case OPT_STRING_TYPE:
            return (OptionPtr(new OptionString(u, type, begin, end)));

        default:
            // Do nothing. We will return generic option a few lines down.
            ;
        }
        return (OptionPtr(new OptionCustom(*this, u, begin, end)));
    } catch (const Exception& ex) {
        isc_throw(InvalidOptionValue, ex.what());
    }
}

OptionPtr
OptionDefinition::optionFactory(Option::Universe u, uint16_t type,
                                const OptionBuffer& buf,
                                UnpackOptionsCallback callback) const {
    return (optionFactory(u, type, buf.begin(), buf.end(), callback));
}

OptionPtr
OptionDefinition::optionFactory(Option::Universe u, uint16_t type,
                                const std::vector<std::string>& values) const {
    OptionBuffer buf;
    if (!array_type_ && type_ != OPT_RECORD_TYPE) {
        if (values.empty()) {
            isc_throw(InvalidOptionValue, "no option value specified");
        }
        writeToBuffer(util::str::trim(values[0]), type_, buf);
    } else if (array_type_ && type_ != OPT_RECORD_TYPE) {
        for (size_t i = 0; i < values.size(); ++i) {
            writeToBuffer(util::str::trim(values[i]), type_, buf);
        }
    } else if (type_ == OPT_RECORD_TYPE) {
        const RecordFieldsCollection& records = getRecordFields();
        if (records.size() > values.size()) {
            isc_throw(InvalidOptionValue, "number of data fields for the option"
                      << " type '" <<  getCode() << "' is greater than number"
                      << " of values provided.");
        }
        for (size_t i = 0; i < records.size(); ++i) {
            writeToBuffer(util::str::trim(values[i]),
                          records[i], buf);
        }
    }
    return (optionFactory(u, type, buf.begin(), buf.end()));
}

void
OptionDefinition::validate() const {

    using namespace boost::algorithm;

    std::ostringstream err_str;

    // Allowed characters in the option name are: lower or
    // upper case letters, digits, underscores and hyphens.
    // Empty option spaces are not allowed.
    if (!all(name_, boost::is_from_range('a', 'z') ||
             boost::is_from_range('A', 'Z') ||
             boost::is_digit() ||
             boost::is_any_of(std::string("-_"))) ||
        name_.empty() ||
        // Hyphens and underscores are not allowed at the beginning
        // and at the end of the option name.
        all(find_head(name_, 1), boost::is_any_of(std::string("-_"))) ||
        all(find_tail(name_, 1), boost::is_any_of(std::string("-_")))) {
        err_str << "invalid option name '" << name_ << "'";

    } else if (!encapsulated_space_.empty() &&
               !OptionSpace::validateName(encapsulated_space_)) {
        err_str << "invalid encapsulated option space name: '"
                << encapsulated_space_ << "'";

    } else if (type_ >= OPT_UNKNOWN_TYPE) {
        // Option definition must be of a known type.
        err_str << "option type " << type_ << " not supported.";

    } else if (array_type_) {
        if (type_ == OPT_STRING_TYPE) {
            // Array of strings is not allowed because there is no way
            // to determine the size of a particular string and thus there
            // it no way to tell when other data fields begin.
            err_str << "array of strings is not a valid option definition.";
        } else if (type_ == OPT_BINARY_TYPE) {
            err_str << "array of binary values is not"
                    << " a valid option definition.";

        } else if (type_ == OPT_EMPTY_TYPE) {
            err_str << "array of empty value is not"
                    << " a valid option definition.";

        }

    } else if (type_ == OPT_RECORD_TYPE) {
        // At least two data fields should be added to the record. Otherwise
        // non-record option definition could be used.
        if (getRecordFields().size() < 2) {
            err_str << "invalid number of data fields: "
                    << getRecordFields().size()
                    << " specified for the option of type 'record'. Expected at"
                    << " least 2 fields.";

        } else {
            // If the number of fields is valid we have to check if their order
            // is valid too. We check that string or binary data fields are not
            // laid before other fields. But we allow that they are laid at the
            // end of an option.
            const RecordFieldsCollection& fields = getRecordFields();
            for (RecordFieldsConstIter it = fields.begin();
                 it != fields.end(); ++it) {
                if (*it == OPT_STRING_TYPE &&
                    it < fields.end() - 1) {
                    err_str << "string data field can't be laid before data"
                            << " fields of other types.";
                    break;
                }
                if (*it == OPT_BINARY_TYPE &&
                    it < fields.end() - 1) {
                    err_str << "binary data field can't be laid before data"
                            << " fields of other types.";
                }
                /// Empty type is not allowed within a record.
                if (*it == OPT_EMPTY_TYPE) {
                    err_str << "empty data type can't be stored as a field in"
                            << " an option record.";
                    break;
                }
            }
        }

    }

    // Non-empty error string means that we have hit the error. We throw
    // exception and include error string.
    if (!err_str.str().empty()) {
        isc_throw(MalformedOptionDefinition, err_str.str());
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

bool
OptionDefinition::haveIAPrefix6Format() const {
    return (haveType(OPT_RECORD_TYPE) &&
            record_fields_.size() == 4 &&
            record_fields_[0] == OPT_UINT32_TYPE &&
            record_fields_[1] == OPT_UINT32_TYPE &&
            record_fields_[2] == OPT_UINT8_TYPE &&
            record_fields_[3] == OPT_IPV6_ADDRESS_TYPE);
}

bool
OptionDefinition::haveFqdn4Format() const {
    return (haveType(OPT_RECORD_TYPE) &&
            record_fields_.size() == 4 &&
            record_fields_[0] == OPT_UINT8_TYPE &&
            record_fields_[1] == OPT_UINT8_TYPE &&
            record_fields_[2] == OPT_UINT8_TYPE &&
            record_fields_[3] == OPT_FQDN_TYPE);
}

bool
OptionDefinition::haveClientFqdnFormat() const {
    return (haveType(OPT_RECORD_TYPE) &&
            (record_fields_.size() == 2) &&
            (record_fields_[0] == OPT_UINT8_TYPE) &&
            (record_fields_[1] == OPT_FQDN_TYPE));
}

bool
OptionDefinition::haveVendor4Format() const {
    return (true);
}

bool
OptionDefinition::haveVendor6Format() const {
    return  (getType() == OPT_UINT32_TYPE && !getEncapsulatedSpace().empty());
}

bool
OptionDefinition::haveVendorClass4Format() const {
    return (haveType(OPT_RECORD_TYPE) &&
            (record_fields_.size() == 2) &&
            (record_fields_[0] == OPT_UINT32_TYPE) &&
            (record_fields_[1] == OPT_BINARY_TYPE));
}

bool
OptionDefinition::haveVendorClass6Format() const {
    return (haveType(OPT_RECORD_TYPE) &&
            (record_fields_.size() == 2) &&
            (record_fields_[0] == OPT_UINT32_TYPE) &&
            (record_fields_[1] == OPT_BINARY_TYPE));
}

bool
OptionDefinition::haveStatusCodeFormat() const {
    return (haveType(OPT_RECORD_TYPE) &&
            (record_fields_.size() == 2) &&
            (record_fields_[0] == OPT_UINT16_TYPE) &&
            (record_fields_[1] == OPT_STRING_TYPE));
}

bool
OptionDefinition::haveOpaqueDataTuplesFormat() const {
    return (getType() == OPT_BINARY_TYPE);
}

bool
OptionDefinition::convertToBool(const std::string& value_str) const {
    // Case insensitve check that the input is one of: "true" or "false".
    if (boost::iequals(value_str, "true")) {
        return (true);

    } else if (boost::iequals(value_str, "false")) {
        return (false);

    }

    // The input string is neither "true" nor "false", so let's check
    // if it is not an integer wrapped in a string.
    int result;
    try {
       result = boost::lexical_cast<int>(value_str);

    } catch (const boost::bad_lexical_cast&) {
        isc_throw(BadDataTypeCast, "unable to covert the value '"
                  << value_str << "' to boolean data type");
    }
    // The boolean value is encoded in DHCP option as 0 or 1. Therefore,
    // we only allow a user to specify those values for options which
    // have boolean fields.
    if (result != 1 && result != 0) {
        isc_throw(BadDataTypeCast, "unable to convert '" << value_str
                  << "' to boolean data type");
    }
    return (static_cast<bool>(result));
}

template<typename T>
T
OptionDefinition::lexicalCastWithRangeCheck(const std::string& value_str)
    const {
    // The lexical cast should be attempted when converting to an integer
    // value only.
    if (!OptionDataTypeTraits<T>::integer_type) {
        isc_throw(BadDataTypeCast,
                  "must not convert '" << value_str
                  << "' to non-integer data type");
    }

    // We use the 64-bit value here because it has wider range than
    // any other type we use here and it allows to detect out of
    // bounds conditions e.g. negative value specified for uintX_t
    // data type. Obviously if the value exceeds the limits of int64
    // this function will not handle that properly.
    int64_t result = 0;
    try {
        result = boost::lexical_cast<int64_t>(value_str);

    } catch (const boost::bad_lexical_cast&) {
        isc_throw(BadDataTypeCast, "unable to convert the value '"
                  << value_str << "' to integer data type");
    }
    // Perform range checks.
    if (OptionDataTypeTraits<T>::integer_type) {
        if (result > numeric_limits<T>::max() ||
            result < numeric_limits<T>::min()) {
            isc_throw(BadDataTypeCast, "unable to convert '"
                      << value_str << "' to numeric type. This value is "
                      " expected to be in the range of "
                      << numeric_limits<T>::min()
                      << ".." << numeric_limits<T>::max());
        }
    }
    return (static_cast<T>(result));
}

void
OptionDefinition::writeToBuffer(const std::string& value,
                                const OptionDataType type,
                                OptionBuffer& buf) const {
    // We are going to write value given by value argument to the buffer.
    // The actual type of the value is given by second argument. Check
    // this argument to determine how to write this value to the buffer.
    switch (type) {
    case OPT_BINARY_TYPE:
        OptionDataTypeUtil::writeBinary(value, buf);
        return;
    case OPT_BOOLEAN_TYPE:
        // We encode the true value as 1 and false as 0 on 8 bits.
        // That way we actually waste 7 bits but it seems to be the
        // simpler way to encode boolean.
        // @todo Consider if any other encode methods can be used.
        OptionDataTypeUtil::writeBool(convertToBool(value), buf);
        return;
    case OPT_INT8_TYPE:
        OptionDataTypeUtil::writeInt<uint8_t>
            (lexicalCastWithRangeCheck<int8_t>(value),
                                              buf);
        return;
    case OPT_INT16_TYPE:
        OptionDataTypeUtil::writeInt<uint16_t>
            (lexicalCastWithRangeCheck<int16_t>(value),
                                               buf);
        return;
    case OPT_INT32_TYPE:
        OptionDataTypeUtil::writeInt<uint32_t>
            (lexicalCastWithRangeCheck<int32_t>(value),
                                               buf);
        return;
    case OPT_UINT8_TYPE:
        OptionDataTypeUtil::writeInt<uint8_t>
            (lexicalCastWithRangeCheck<uint8_t>(value),
                                              buf);
        return;
    case OPT_UINT16_TYPE:
        OptionDataTypeUtil::writeInt<uint16_t>
            (lexicalCastWithRangeCheck<uint16_t>(value),
                                               buf);
        return;
    case OPT_UINT32_TYPE:
        OptionDataTypeUtil::writeInt<uint32_t>
            (lexicalCastWithRangeCheck<uint32_t>(value),
                                               buf);
        return;
    case OPT_IPV4_ADDRESS_TYPE:
    case OPT_IPV6_ADDRESS_TYPE:
        {
            asiolink::IOAddress address(value);
            if (!address.isV4() && !address.isV6()) {
                isc_throw(BadDataTypeCast, "provided address "
                          << address
                          << " is not a valid IPv4 or IPv6 address.");
            }
            OptionDataTypeUtil::writeAddress(address, buf);
            return;
        }
    case OPT_STRING_TYPE:
        OptionDataTypeUtil::writeString(value, buf);
        return;
    case OPT_FQDN_TYPE:
        OptionDataTypeUtil::writeFqdn(value, buf);
        return;
    default:
        // We hit this point because invalid option data type has been specified
        // This may be the case because 'empty' or 'record' data type has been
        // specified. We don't throw exception here because it will be thrown
        // at the exit point from this function.
        ;
    }
    isc_throw(isc::BadValue, "attempt to write invalid option data field type"
              " into the option buffer: " << type);

}

OptionPtr
OptionDefinition::factoryAddrList4(uint16_t type,
                                  OptionBufferConstIter begin,
                                  OptionBufferConstIter end) {
    boost::shared_ptr<Option4AddrLst> option(new Option4AddrLst(type, begin,
                                                                end));
    return (option);
}

OptionPtr
OptionDefinition::factoryAddrList6(uint16_t type,
                                   OptionBufferConstIter begin,
                                   OptionBufferConstIter end) {
    boost::shared_ptr<Option6AddrLst> option(new Option6AddrLst(type, begin,
                                                                end));
    return (option);
}


OptionPtr
OptionDefinition::factoryEmpty(Option::Universe u, uint16_t type) {
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
OptionDefinition::factoryIA6(uint16_t type,
                             OptionBufferConstIter begin,
                             OptionBufferConstIter end) {
    if (std::distance(begin, end) < Option6IA::OPTION6_IA_LEN) {
        isc_throw(isc::OutOfRange, "input option buffer has invalid size,"
                  << " expected at least " << Option6IA::OPTION6_IA_LEN
                  << " bytes");
    }
    boost::shared_ptr<Option6IA> option(new Option6IA(type, begin, end));
    return (option);
}

OptionPtr
OptionDefinition::factoryIAAddr6(uint16_t type,
                                 OptionBufferConstIter begin,
                                 OptionBufferConstIter end) {
    if (std::distance(begin, end) < Option6IAAddr::OPTION6_IAADDR_LEN) {
        isc_throw(isc::OutOfRange,
                  "input option buffer has invalid size, expected at least "
                  << Option6IAAddr::OPTION6_IAADDR_LEN << " bytes");
    }
    boost::shared_ptr<Option6IAAddr> option(new Option6IAAddr(type, begin,
                                                              end));
    return (option);
}

OptionPtr
OptionDefinition::factoryIAPrefix6(uint16_t type,
                                 OptionBufferConstIter begin,
                                 OptionBufferConstIter end) {
    if (std::distance(begin, end) < Option6IAPrefix::OPTION6_IAPREFIX_LEN) {
        isc_throw(isc::OutOfRange,
                  "input option buffer has invalid size, expected at least "
                  << Option6IAPrefix::OPTION6_IAPREFIX_LEN << " bytes");
    }
    boost::shared_ptr<Option6IAPrefix> option(new Option6IAPrefix(type, begin,
                                                                  end));
    return (option);
}

OptionPtr
OptionDefinition::factorySpecialFormatOption(Option::Universe u,
                                             OptionBufferConstIter begin,
                                             OptionBufferConstIter end,
                                             UnpackOptionsCallback) const {
    if (u == Option::V6) {
        if ((getCode() == D6O_IA_NA || getCode() == D6O_IA_PD) &&
            haveIA6Format()) {
            // Return Option6IA instance for IA_PD and IA_NA option
            // types only. We don't want to return Option6IA for other
            // options that comprise 3 UINT32 data fields because
            // Option6IA accessors' and modifiers' names are derived
            // from the IA_NA and IA_PD options' field names: IAID,
            // T1, T2. Using functions such as getIAID, getT1 etc. for
            // options other than IA_NA and IA_PD would be bad practice
            // and cause confusion.
            return (factoryIA6(getCode(), begin, end));

        } else if (getCode() == D6O_IAADDR && haveIAAddr6Format()) {
            // Rerurn Option6IAAddr option instance for the IAADDR
            // option only for the same reasons as described in
            // for IA_NA and IA_PD above.
            return (factoryIAAddr6(getCode(), begin, end));
        } else if (getCode() == D6O_IAPREFIX && haveIAPrefix6Format()) {
            return (factoryIAPrefix6(getCode(), begin, end));
        } else if (getCode() == D6O_CLIENT_FQDN && haveClientFqdnFormat()) {
            // FQDN option requires special processing. Thus, there is
            // a specialized class to handle it.
            return (OptionPtr(new Option6ClientFqdn(begin, end)));
        } else if (getCode() == D6O_VENDOR_OPTS && haveVendor6Format()) {
            // Vendor-Specific Information (option code 17)
            return (OptionPtr(new OptionVendor(Option::V6, begin, end)));
        } else if (getCode() == D6O_VENDOR_CLASS && haveVendorClass6Format()) {
            // Vendor Class (option code 16).
            return (OptionPtr(new OptionVendorClass(Option::V6, begin, end)));
        } else if (getCode() == D6O_STATUS_CODE && haveStatusCodeFormat()) {
            // Status Code (option code 13)
            return (OptionPtr(new Option6StatusCode(begin, end)));
        } else if (getCode() == D6O_BOOTFILE_PARAM && haveOpaqueDataTuplesFormat()) {
            // Bootfile params (option code 60)
            return (OptionPtr(new OptionOpaqueDataTuples(Option::V6, getCode(), begin, end)));
        }
    } else {
        if ((getCode() == DHO_FQDN) && haveFqdn4Format()) {
            return (OptionPtr(new Option4ClientFqdn(begin, end)));
        } else if ((getCode() == DHO_VIVCO_SUBOPTIONS) &&
                   haveVendorClass4Format()) {
            // V-I Vendor Class (option code 124).
            return (OptionPtr(new OptionVendorClass(Option::V4, begin, end)));
        } else if (getCode() == DHO_VIVSO_SUBOPTIONS && haveVendor4Format()) {
            // Vendor-Specific Information (option code 125).
            return (OptionPtr(new OptionVendor(Option::V4, begin, end)));

        }
    }
    return (OptionPtr());
}

} // end of isc::dhcp namespace
} // end of isc namespace
