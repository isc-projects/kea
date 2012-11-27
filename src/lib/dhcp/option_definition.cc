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
    type_ = OptionDataTypeUtil::getDataType(type);
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
        isc_throw(isc::BadValue, "attempted to add invalid data type to the record.");
    }
    record_fields_.push_back(data_type);
}

OptionPtr
OptionDefinition::optionFactory(Option::Universe u, uint16_t type,
                                OptionBufferConstIter begin,
                                OptionBufferConstIter end) const {
    validate();
    
    try {
        if (type_ == OPT_BINARY_TYPE) {
            return (factoryGeneric(u, type, begin, end));

        } else if (type_ == OPT_IPV6_ADDRESS_TYPE && array_type_) {
            return (factoryAddrList6(type, begin, end));

        } else if (type_ == OPT_IPV4_ADDRESS_TYPE && array_type_) {
            return (factoryAddrList4(type, begin, end));

        } else if (type_ == OPT_EMPTY_TYPE) {
            return (factoryEmpty(u, type));

        } else if (u == Option::V6 &&
                   code_ == D6O_IA_NA &&
                   haveIA6Format()) {
            return (factoryIA6(type, begin, end));

        } else if (u == Option::V6 &&
                   code_ == D6O_IAADDR &&
                   haveIAAddr6Format()) {
            return (factoryIAAddr6(type, begin, end));

        } else if (type_ == OPT_UINT8_TYPE) {
            if (array_type_) {
                return (factoryGeneric(u, type, begin, end));
            } else {
                return (factoryInteger<uint8_t>(u, type, begin, end));
            }

        } else if (type_ == OPT_UINT16_TYPE) {
            if (array_type_) {
                return (factoryIntegerArray<uint16_t>(type, begin, end));
            } else {
                return (factoryInteger<uint16_t>(u, type, begin, end));
            }

        } else if (type_ == OPT_UINT32_TYPE) {
            if (array_type_) {
                return (factoryIntegerArray<uint32_t>(type, begin, end));
            } else {
                return (factoryInteger<uint32_t>(u, type, begin, end));
            }

        }
        return (factoryGeneric(u, type, begin, end));

    } catch (const Exception& ex) {
        isc_throw(InvalidOptionValue, ex.what());
    }
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
        writeToBuffer(values[0], type_, buf);
    } else if (array_type_ && type_ != OPT_RECORD_TYPE) {
        for (size_t i = 0; i < values.size(); ++i) {
            writeToBuffer(values[i], type_, buf);
        }
    } else if (type_ == OPT_RECORD_TYPE) {
        const RecordFieldsCollection& records = getRecordFields();
        if (records.size() > values.size()) {
            isc_throw(InvalidOptionValue, "number of data fields for the option"
                      << " type " << type_ << " is greater than number of values"
                      << " provided.");
        }
        for (size_t i = 0; i < records.size(); ++i) {
            writeToBuffer(values[i], records[i], buf);
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
    std::ostringstream err_str;
    if (name_.empty()) {
        // Option name must not be empty.
        err_str << "option name must not be empty.";
    } else if (name_.find(" ") != string::npos) {
        // Option name must not contain spaces.
        err_str << "option name must not contain spaces.";
    } else if (type_ >= OPT_UNKNOWN_TYPE) {
        // Option definition must be of a known type.
        err_str << "option type value " << type_ << " is out of range.";
    } else if (array_type_) {
        if (type_ == OPT_STRING_TYPE) {
            // Array of strings is not allowed because there is no way
            // to determine the size of a particular string and thus there
            // it no way to tell when other data fields begin.
            err_str << "array of strings is not a valid option definition.";
        } else if (type_ == OPT_BINARY_TYPE) {
            err_str << "array of binary values is not a valid option definition.";
        } else if (type_ == OPT_EMPTY_TYPE) {
            err_str << "array of empty value is not a valid option definition.";
        }
    } else if (type_ == OPT_RECORD_TYPE) {
        // At least two data fields should be added to the record. Otherwise
        // non-record option definition could be used.
        if (getRecordFields().size() < 2) {
            err_str << "invalid number of data fields: " << getRecordFields().size()
                    << " specified for the option of type 'record'. Expected at"
                    << " least 2 fields.";
        } else {
            // If the number of fields is valid we have to check if their order
            // is valid too. We check that string or binary data fields are not
            // laid before other fields. But we allow that they are laid at the end of
            // an option.
            const RecordFieldsCollection& fields = getRecordFields();
            for (RecordFieldsConstIter it = fields.begin();
                 it != fields.end(); ++it) {
                if (*it == OPT_STRING_TYPE &&
                    it < fields.end() - 1) {
                    err_str << "string data field can't be laid before data fields"
                            << " of other types.";
                    break;
                }
                if (*it == OPT_BINARY_TYPE &&
                    it < fields.end() - 1) {
                    err_str << "binary data field can't be laid before data fields"
                            << " of other types.";
                }
                /// Empty typy is not allowed within a record.
                if (*it == OPT_EMPTY_TYPE) {
                    err_str << "empty data type can't be stored as a field in an"
                            << " option record.";
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

template<typename T>
T OptionDefinition::lexicalCastWithRangeCheck(const std::string& value_str) const {
    // Lexical cast in case of our data types make sense only
    // for uintX_t, intX_t and bool type.
    if (!OptionDataTypeTraits<T>::integer_type &&
        OptionDataTypeTraits<T>::type != OPT_BOOLEAN_TYPE) {
        isc_throw(BadDataTypeCast, "unable to do lexical cast to non-integer and"
                  << " non-boolean data type");
    }
    // We use the 64-bit value here because it has wider range than
    // any other type we use here and it allows to detect out of
    // bounds conditions e.g. negative value specified for uintX_t
    // data type. Obviously if the value exceeds the limits of int64
    // this function will not handle that properly.
    int64_t result = 0;
    try {
        result = boost::lexical_cast<int64_t>(value_str);
    } catch (const boost::bad_lexical_cast& ex) {
        // Prepare error message here.
        std::string data_type_str = "boolean";
        if (OptionDataTypeTraits<T>::integer_type) {
            data_type_str = "integer";
        }
        isc_throw(BadDataTypeCast, "unable to do lexical cast to " << data_type_str
                  << " data type for value " << value_str << ": " << ex.what());
    }
    // Perform range checks for integer values only (exclude bool values).
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
        OptionDataTypeUtil::writeBool(lexicalCastWithRangeCheck<bool>(value), buf);
        return;
    case OPT_INT8_TYPE:
        OptionDataTypeUtil::writeInt<uint8_t>(lexicalCastWithRangeCheck<int8_t>(value),
                                              buf);
        return;
    case OPT_INT16_TYPE:
        OptionDataTypeUtil::writeInt<uint16_t>(lexicalCastWithRangeCheck<int16_t>(value),
                                               buf);
        return;
    case OPT_INT32_TYPE:
        OptionDataTypeUtil::writeInt<uint32_t>(lexicalCastWithRangeCheck<int32_t>(value),
                                               buf);
        return;
    case OPT_UINT8_TYPE:
        OptionDataTypeUtil::writeInt<uint8_t>(lexicalCastWithRangeCheck<uint8_t>(value),
                                              buf);
        return;
    case OPT_UINT16_TYPE:
        OptionDataTypeUtil::writeInt<uint16_t>(lexicalCastWithRangeCheck<uint16_t>(value),
                                               buf);
        return;
    case OPT_UINT32_TYPE:
        OptionDataTypeUtil::writeInt<uint32_t>(lexicalCastWithRangeCheck<uint32_t>(value),
                                               buf);
        return;
    case OPT_IPV4_ADDRESS_TYPE:
    case OPT_IPV6_ADDRESS_TYPE:
        {
            asiolink::IOAddress address(value);
            if (!address.getAddress().is_v4() &&
                !address.getAddress().is_v6()) {
                isc_throw(BadDataTypeCast, "provided address " << address.toText()
                          << " is not a valid "
                          << (address.getAddress().is_v4() ? "IPv4" : "IPv6")
                          << " address");
            }
            OptionDataTypeUtil::writeAddress(address, buf);
            return;
        }
    case OPT_STRING_TYPE:
        OptionDataTypeUtil::writeString(value, buf);
        return;
    case OPT_FQDN_TYPE:
        {
            // FQDN implementation is not terribly complicated but will require
            // creation of some additional logic (maybe object) that will parse
            // the fqdn into labels.
            isc_throw(isc::NotImplemented, "write of FQDN record into option buffer"
                      " is not supported yet");
            return;
        }
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
    boost::shared_ptr<Option4AddrLst> option(new Option4AddrLst(type, begin, end));
    return (option);
}

OptionPtr
OptionDefinition::factoryAddrList6(uint16_t type,
                                   OptionBufferConstIter begin,
                                   OptionBufferConstIter end) {
    boost::shared_ptr<Option6AddrLst> option(new Option6AddrLst(type, begin, end));
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
        isc_throw(isc::OutOfRange, "input option buffer has invalid size, expected "
                  "at least " << Option6IA::OPTION6_IA_LEN << " bytes");
    }
    boost::shared_ptr<Option6IA> option(new Option6IA(type, begin, end));
    return (option);
}

OptionPtr
OptionDefinition::factoryIAAddr6(uint16_t type,
                                 OptionBufferConstIter begin,
                                 OptionBufferConstIter end) {
    if (std::distance(begin, end) < Option6IAAddr::OPTION6_IAADDR_LEN) {
        isc_throw(isc::OutOfRange, "input option buffer has invalid size, expected "
                  " at least " << Option6IAAddr::OPTION6_IAADDR_LEN << " bytes");
    }
    boost::shared_ptr<Option6IAAddr> option(new Option6IAAddr(type, begin, end));
    return (option);
}


} // end of isc::dhcp namespace
} // end of isc namespace
