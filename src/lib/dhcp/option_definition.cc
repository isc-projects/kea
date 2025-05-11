// Copyright (C) 2012-2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <dhcp/dhcp4.h>
#include <dhcp/dhcp6.h>
#include <dhcp/option4_addrlst.h>
#include <dhcp/option4_client_fqdn.h>
#include <dhcp/option4_dnr.h>
#include <dhcp/option6_addrlst.h>
#include <dhcp/option6_client_fqdn.h>
#include <dhcp/option6_dnr.h>
#include <dhcp/option6_ia.h>
#include <dhcp/option6_iaaddr.h>
#include <dhcp/option6_iaprefix.h>
#include <dhcp/option6_pdexclude.h>
#include <dhcp/option6_status_code.h>
#include <dhcp/option_custom.h>
#include <dhcp/option_definition.h>
#include <dhcp/option_int.h>
#include <dhcp/option_int_array.h>
#include <dhcp/option_opaque_data_tuples.h>
#include <dhcp/option_classless_static_route.h>
#include <dhcp/option_string.h>
#include <dhcp/option_vendor.h>
#include <dhcp/option_vendor_class.h>
#include <util/encode/encode.h>
#include <dns/labelsequence.h>
#include <dns/name.h>
#include <util/str.h>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/algorithm/string/replace.hpp>
#include <boost/dynamic_bitset.hpp>
#include <boost/make_shared.hpp>
#include <sstream>

using namespace std;
using namespace isc::util;

namespace isc {
namespace dhcp {

OptionDefinition::OptionDefinition(const std::string& name,
                                   const uint16_t code,
                                   const std::string& space,
                                   const std::string& type,
                                   const bool array_type /* = false */)
    : name_(name),
      code_(code),
      type_(OPT_UNKNOWN_TYPE),
      array_type_(array_type),
      encapsulated_space_(""),
      record_fields_(),
      user_context_(),
      option_space_name_(space) {
    // Data type is held as enum value by this class.
    // Use the provided option type string to get the
    // corresponding enum value.
    type_ = OptionDataTypeUtil::getDataType(type);
}

OptionDefinition::OptionDefinition(const std::string& name,
                                   const uint16_t code,
                                   const std::string& space,
                                   const OptionDataType type,
                                   const bool array_type /* = false */)
    : name_(name),
      code_(code),
      type_(type),
      array_type_(array_type),
      encapsulated_space_(""),
      option_space_name_(space){
}

OptionDefinition::OptionDefinition(const std::string& name,
                                   const uint16_t code,
                                   const std::string& space,
                                   const std::string& type,
                                   const char* encapsulated_space)
    : name_(name),
      code_(code),
      // Data type is held as enum value by this class.
      // Use the provided option type string to get the
      // corresponding enum value.
      type_(OptionDataTypeUtil::getDataType(type)),
      array_type_(false),
      encapsulated_space_(encapsulated_space),
      record_fields_(),
      user_context_(),
      option_space_name_(space) {
}

OptionDefinition::OptionDefinition(const std::string& name,
                                   const uint16_t code,
                                   const std::string& space,
                                   const OptionDataType type,
                                   const char* encapsulated_space)
    : name_(name),
      code_(code),
      type_(type),
      array_type_(false),
      encapsulated_space_(encapsulated_space),
      record_fields_(),
      user_context_(),
      option_space_name_(space) {
}

OptionDefinitionPtr
OptionDefinition::create(const std::string& name,
                         const uint16_t code,
                         const std::string& space,
                         const std::string& type,
                         const bool array_type) {
    return (boost::make_shared<OptionDefinition>(name, code, space, type, array_type));
}

OptionDefinitionPtr
OptionDefinition::create(const std::string& name,
                         const uint16_t code,
                         const std::string& space,
                         const OptionDataType type,
                         const bool array_type) {
    return (boost::make_shared<OptionDefinition>(name, code, space, type, array_type));
}

OptionDefinitionPtr
OptionDefinition::create(const std::string& name,
                         const uint16_t code,
                         const std::string& space,
                         const std::string& type,
                         const char* encapsulated_space) {
    return (boost::make_shared<OptionDefinition>(name, code, space, type, encapsulated_space));
}

OptionDefinitionPtr
OptionDefinition::create(const std::string& name,
                         const uint16_t code,
                         const std::string& space,
                         const OptionDataType type,
                         const char* encapsulated_space) {
    return (boost::make_shared<OptionDefinition>(name, code, space, type, encapsulated_space));
}

bool
OptionDefinition::equals(const OptionDefinition& other) const {
    return (name_ == other.name_ &&
            code_ == other.code_ &&
            type_ == other.type_ &&
            array_type_ == other.array_type_ &&
            encapsulated_space_ == other.encapsulated_space_ &&
            record_fields_ == other.record_fields_ &&
            option_space_name_ == other.option_space_name_);
}

void
OptionDefinition::addRecordField(const std::string& data_type_name) {
    OptionDataType data_type = OptionDataTypeUtil::getDataType(data_type_name);
    addRecordField(data_type);
}

void
OptionDefinition::addRecordField(const OptionDataType data_type) {
    if (type_ != OPT_RECORD_TYPE) {
        isc_throw(isc::InvalidOperation,
                  "'record' option type must be used instead of '"
                      << OptionDataTypeUtil::getDataTypeName(type_)
                      << "' to add data fields to the record");
    }
    if (data_type >= OPT_RECORD_TYPE ||
        data_type == OPT_ANY_ADDRESS_TYPE ||
        data_type == OPT_EMPTY_TYPE) {
        isc_throw(isc::BadValue,
                  "attempted to add invalid data type '"
                      << OptionDataTypeUtil::getDataTypeName(data_type)
                      << "' to the record.");
    }
    record_fields_.push_back(data_type);
}

OptionPtr
OptionDefinition::optionFactory(Option::Universe u,
                                uint16_t type,
                                OptionBufferConstIter begin,
                                OptionBufferConstIter end,
                                bool convenient_notation) const {

    try {
        // Some of the options are represented by the specialized classes derived
        // from Option class (e.g. IA_NA, IAADDR). Although, they can be also
        // represented by the generic classes, we want the object of the specialized
        // type to be returned. Therefore, we first check that if we are dealing
        // with such an option. If the instance is returned we just exit at this
        // point. If not, we will search for a generic option type to return.
        OptionPtr option = factorySpecialFormatOption(u, begin, end, convenient_notation);
        if (option) {
            return (option);
        }

        switch (type_) {
        case OPT_EMPTY_TYPE:
            if (getEncapsulatedSpace().empty()) {
                return (factoryEmpty(u, type));
            } else {
                return (OptionPtr(new OptionCustom(*this, u, begin, end)));
            }

        case OPT_BINARY_TYPE:
        // If this is Internal type, and it wasn't handled by factorySpecialFormatOption() before,
        // let's treat it like normal Binary type.
        case OPT_INTERNAL_TYPE:
            return (factoryGeneric(u, type, begin, end));

        case OPT_UINT8_TYPE:
            return (array_type_ ?
                    factoryIntegerArray<uint8_t>(u, type, begin, end) :
                    factoryInteger<uint8_t>(u, type, getEncapsulatedSpace(),
                                            begin, end));

        case OPT_INT8_TYPE:
            return (array_type_ ?
                    factoryIntegerArray<int8_t>(u, type, begin, end) :
                    factoryInteger<int8_t>(u, type, getEncapsulatedSpace(),
                                           begin, end));

        case OPT_UINT16_TYPE:
            return (array_type_ ?
                    factoryIntegerArray<uint16_t>(u, type, begin, end) :
                    factoryInteger<uint16_t>(u, type, getEncapsulatedSpace(),
                                             begin, end));

        case OPT_INT16_TYPE:
            return (array_type_ ?
                    factoryIntegerArray<uint16_t>(u, type, begin, end) :
                    factoryInteger<int16_t>(u, type, getEncapsulatedSpace(),
                                            begin, end));

        case OPT_UINT32_TYPE:
            return (array_type_ ?
                    factoryIntegerArray<uint32_t>(u, type, begin, end) :
                    factoryInteger<uint32_t>(u, type, getEncapsulatedSpace(),
                                             begin, end));

        case OPT_INT32_TYPE:
            return (array_type_ ?
                    factoryIntegerArray<uint32_t>(u, type, begin, end) :
                    factoryInteger<int32_t>(u, type, getEncapsulatedSpace(),
                                            begin, end));

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

        case OPT_TUPLE_TYPE:
            // Handle array type only here (see comments for
            // OPT_IPV4_ADDRESS_TYPE case).
            if (array_type_) {
                return (factoryOpaqueDataTuples(u, type, begin, end));
            }
            break;

        default:
            // Do nothing. We will return generic option a few lines down.
            ;
        }
        return (OptionPtr(new OptionCustom(*this, u, begin, end)));
    } catch (const SkipThisOptionError&) {
        // We need to throw this one as is.
        throw;
    } catch (const SkipRemainingOptionsError&) {
        // We need to throw this one as is.
        throw;
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
    OptionBuffer buf;
    if (!array_type_ && type_ != OPT_RECORD_TYPE) {
        if (values.empty()) {
            if (type_ != OPT_EMPTY_TYPE) {
                isc_throw(InvalidOptionValue, "no option value specified");
            }
        } else if (type_ == OPT_INTERNAL_TYPE) {
            // If an Option of type Internal is configured using csv-format=true, it means it is
            // convenient notation option config that needs special parsing. Let's treat it like
            // String type. optionFactory() will be called with convenient_notation flag set to
            // true, so that the factory will have a chance to handle it in a special way.

            // At this stage any escape backslash chars were lost during last call of
            // isc::util::str::tokens() inside of
            // OptionDataParser::createOption(ConstElementPtr option_data), so we must
            // restore them. Some INTERNAL options may use escaped delimiters, e.g. DNR options.
            // Values are concatenated back to comma separated format and will be written to
            // the OptionBuffer as one String type option.
            std::ostringstream stream;
            bool first = true;
            for (auto val : values) {
                boost::algorithm::replace_all(val, ",", "\\,");
                if (first) {
                    first = false;
                } else {
                    stream << ",";
                }

                stream << val;
            }

            writeToBuffer(u, stream.str(), OPT_STRING_TYPE, buf);
        } else {
            writeToBuffer(u, util::str::trim(values[0]), type_, buf);
        }
    } else if (array_type_ && type_ != OPT_RECORD_TYPE) {
        for (size_t i = 0; i < values.size(); ++i) {
            writeToBuffer(u, util::str::trim(values[i]), type_, buf);
        }
    } else if (type_ == OPT_RECORD_TYPE) {
        const RecordFieldsCollection& records = getRecordFields();
        if (records.size() > values.size()) {
            isc_throw(InvalidOptionValue, "number of data fields for the option"
                      << " type '" <<  getCode() << "' is greater than number"
                      << " of values provided.");
        }
        for (size_t i = 0; i < records.size(); ++i) {
            writeToBuffer(u, util::str::trim(values[i]), records[i], buf);
        }
        if (array_type_ && (values.size() > records.size())) {
            for (size_t i = records.size(); i < values.size(); ++i) {
                writeToBuffer(u, util::str::trim(values[i]),
                              records.back(), buf);
            }
        }
    }
    return (optionFactory(u, type, buf.begin(), buf.end(), (type_ == OPT_INTERNAL_TYPE)));
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

    } else if (!OptionSpace::validateName(option_space_name_)) {
        err_str << "invalid option space name: '"
                << option_space_name_ << "'";

    } else if (!encapsulated_space_.empty() &&
               !OptionSpace::validateName(encapsulated_space_)) {
        err_str << "invalid encapsulated option space name: '"
                << encapsulated_space_ << "'";

    } else if (type_ >= OPT_UNKNOWN_TYPE) {
        // Option definition must be of a known type.
        err_str << "option type " << type_ << " not supported.";

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
                    break;
                }
                // Empty type is not allowed within a record.
                if (*it == OPT_EMPTY_TYPE) {
                    err_str << "empty data type can't be stored as a field in"
                            << " an option record.";
                    break;
                }
                // Internal type is not allowed within a record.
                if (*it == OPT_INTERNAL_TYPE) {
                    err_str << "internal data type can't be stored as a field in"
                            << " an option record.";
                    break;
                }
            }
            // If the array flag is set the last field is an array.
            if (err_str.str().empty() && array_type_) {
                const OptionDataType& last_type = fields.back();
                if (last_type == OPT_STRING_TYPE) {
                    err_str
                        << "array of strings is not a valid option definition.";
                } else if (last_type == OPT_BINARY_TYPE) {
                    err_str << "array of binary values is not a valid option "
                               "definition.";
                }
                // Empty type was already checked.
            }
        }

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

        } else if (type_ == OPT_INTERNAL_TYPE) {
            err_str << "array of internal type value is not"
                    << " a valid option definition.";

        }
    }

    // Non-empty error string means that we have hit the error. We throw
    // exception and include error string.
    if (!err_str.str().empty()) {
        isc_throw(MalformedOptionDefinition, err_str.str());
    }
}

bool
OptionDefinition::haveCompressedFqdnListFormat() const {
    return (haveType(OPT_FQDN_TYPE) && getArrayType());
}

bool
OptionDefinition::convertToBool(const std::string& value_str) const {
    // Case-insensitive check that the input is one of: "true" or "false".
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
        // boost::lexical_cast does not handle hexadecimal
        // but stringstream does so do it the hard way.
        std::stringstream ss;
        ss << std::hex << value_str;
        ss >> result;
        if (ss.fail() || !ss.eof()) {
            isc_throw(BadDataTypeCast, "unable to convert the value '"
                      << value_str << "' to integer data type");
        }
    }
    // Perform range checks.
    if (OptionDataTypeTraits<T>::integer_type) {
        if (result > numeric_limits<T>::max() ||
            result < numeric_limits<T>::min()) {
            isc_throw(BadDataTypeCast, "unable to convert '"
                      << value_str << "' to numeric type. This value is "
                         "expected to be in the range of "
                      << +numeric_limits<T>::min() << ".."
                      << +numeric_limits<T>::max());
        }
    }
    return (static_cast<T>(result));
}

void
OptionDefinition::writeToBuffer(Option::Universe u,
                                const std::string& value,
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
    case OPT_IPV6_PREFIX_TYPE:
        {
            std::string txt = value;

            // first let's remove any whitespaces
            boost::erase_all(txt, " "); // space
            boost::erase_all(txt, "\t"); // tabulation

            // Is this prefix/len notation?
            size_t pos = txt.find("/");

            if (pos == string::npos) {
                isc_throw(BadDataTypeCast, "provided address/prefix "
                          << value
                          << " is not valid.");
            }

            std::string txt_address = txt.substr(0, pos);
            isc::asiolink::IOAddress address = isc::asiolink::IOAddress(txt_address);
            if (!address.isV6()) {
                isc_throw(BadDataTypeCast, "provided address "
                          << txt_address
                          << " is not a valid IPv4 or IPv6 address.");
            }

            std::string txt_prefix = txt.substr(pos + 1);
            uint8_t len = 0;
            try {
                // start with the first character after /
                len = lexicalCastWithRangeCheck<uint8_t>(txt_prefix);
            } catch (...)  {
                isc_throw(BadDataTypeCast, "provided prefix "
                          << txt_prefix
                          << " is not valid.");
            }

            // Write a prefix.
            OptionDataTypeUtil::writePrefix(PrefixLen(len), address, buf);

            return;
        }
    case OPT_PSID_TYPE:
        {
        std::string txt = value;

        // first let's remove any whitespaces
        boost::erase_all(txt, " "); // space
        boost::erase_all(txt, "\t"); // tabulation

        // Is this prefix/len notation?
        size_t pos = txt.find("/");

        if (pos == string::npos) {
            isc_throw(BadDataTypeCast, "provided PSID value "
                      << value << " is not valid");
        }

        const std::string txt_psid = txt.substr(0, pos);
        const std::string txt_psid_len = txt.substr(pos + 1);

        uint16_t psid = 0;
        uint8_t psid_len = 0;

        try {
            psid = lexicalCastWithRangeCheck<uint16_t>(txt_psid);
        } catch (...)  {
            isc_throw(BadDataTypeCast, "provided PSID "
                      << txt_psid << " is not valid");
        }

        try {
            psid_len = lexicalCastWithRangeCheck<uint8_t>(txt_psid_len);
        } catch (...)  {
            isc_throw(BadDataTypeCast, "provided PSID length "
                      << txt_psid_len << " is not valid");
        }

        OptionDataTypeUtil::writePsid(PSIDLen(psid_len), PSID(psid), buf);
        return;
    }
    case OPT_STRING_TYPE:
        OptionDataTypeUtil::writeString(value, buf);
        return;
    case OPT_FQDN_TYPE:
        OptionDataTypeUtil::writeFqdn(value, buf);
        return;
    case OPT_TUPLE_TYPE:
    {
        // In case of V4_SZTP_REDIRECT option #143, bootstrap-server-list is formatted
        // as a list of tuples "uri-length;URI" where uri-length is coded on 2 octets,
        // which is not typical for V4 Universe.
        OpaqueDataTuple::LengthFieldType lft = getCode() == DHO_V4_SZTP_REDIRECT
                                                   ? OpaqueDataTuple::LENGTH_2_BYTES
                                                   : OptionDataTypeUtil::getTupleLenFieldType(u);
        OptionDataTypeUtil::writeTuple(value, lft, buf);
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
    if (static_cast<size_t>(std::distance(begin, end)) < Option6IA::OPTION6_IA_LEN) {
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
    if (static_cast<size_t>(std::distance(begin, end)) < Option6IAAddr::OPTION6_IAADDR_LEN) {
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
    if (static_cast<size_t>(std::distance(begin, end)) < Option6IAPrefix::OPTION6_IAPREFIX_LEN) {
        isc_throw(isc::OutOfRange,
                  "input option buffer has invalid size, expected at least "
                  << Option6IAPrefix::OPTION6_IAPREFIX_LEN << " bytes");
    }
    boost::shared_ptr<Option6IAPrefix> option(new Option6IAPrefix(type, begin,
                                                                  end));
    return (option);
}

OptionPtr
OptionDefinition::factoryOpaqueDataTuples(Option::Universe u,
                                          uint16_t type,
                                          OptionBufferConstIter begin,
                                          OptionBufferConstIter end) {
    boost::shared_ptr<OptionOpaqueDataTuples>
        option(new OptionOpaqueDataTuples(u, type, begin, end));

    return (option);
}

OptionPtr
OptionDefinition::factoryOpaqueDataTuples(Option::Universe u,
                                          uint16_t type,
                                          OptionBufferConstIter begin,
                                          OptionBufferConstIter end,
                                          OpaqueDataTuple::LengthFieldType length_field_type) {
    boost::shared_ptr<OptionOpaqueDataTuples>
        option(new OptionOpaqueDataTuples(u, type, begin, end, length_field_type));

    return (option);
}

OptionPtr
OptionDefinition::factoryFqdnList(Option::Universe u,
                                  OptionBufferConstIter begin,
                                  OptionBufferConstIter end) const {

    const std::vector<uint8_t> data(begin, end);
    if (data.empty()) {
        isc_throw(InvalidOptionValue, "FQDN list option has invalid length of 0");
    }
    InputBuffer in_buf(static_cast<const void*>(&data[0]), data.size());
    std::vector<uint8_t> out_buf;
    out_buf.reserve(data.size());
    while (in_buf.getPosition() < in_buf.getLength()) {
        // Reuse readFqdn and writeFqdn code but on the whole buffer
        // so the DNS name code handles compression for us.
        try {
            isc::dns::Name name(in_buf);
            isc::dns::LabelSequence labels(name);
            if (labels.getDataLength() > 0) {
                size_t read_len = 0;
                const uint8_t* label = labels.getData(&read_len);
                out_buf.insert(out_buf.end(), label, label + read_len);
            }
        } catch (const isc::Exception& ex) {
            if (Option::lenient_parsing_) {
                    isc_throw(SkipThisOptionError,
                              "invalid FQDN list content: " << ex.what());
            }

            isc_throw(InvalidOptionValue, ex.what());
        }
    }
    return OptionPtr(new OptionCustom(*this, u,
                                      out_buf.begin(), out_buf.end()));
}

OptionPtr
OptionDefinition::factorySpecialFormatOption(Option::Universe u,
                                             OptionBufferConstIter begin,
                                             OptionBufferConstIter end,
                                             bool convenient_notation) const {
    if ((u == Option::V6) && haveSpace(DHCP6_OPTION_SPACE)) {
        switch (getCode()) {
        case D6O_IA_NA:
        case D6O_IA_PD:
            // Record of 3 uint32, no array.
            return (factoryIA6(getCode(), begin, end));

        case D6O_IAADDR:
            // Record of an IPv6 address followed by 2 uint32, no array.
            return (factoryIAAddr6(getCode(), begin, end));

        case D6O_IAPREFIX:
            // Record of 2 uint32, one uint8 and an IPv6 address, no array.
            return (factoryIAPrefix6(getCode(), begin, end));

        case D6O_CLIENT_FQDN:
            // Record of one uint8 and one FQDN, no array.
            return (OptionPtr(new Option6ClientFqdn(begin, end)));

        case D6O_VENDOR_OPTS:
            // Type uint32.
            // Vendor-Specific Information (option code 17).
            return (OptionPtr(new OptionVendor(Option::V6, begin, end)));

        case D6O_VENDOR_CLASS:
            // Record of one uint32 and one string.
            // Vendor Class (option code 16).
            return (OptionPtr(new OptionVendorClass(Option::V6, begin, end)));

        case D6O_STATUS_CODE:
            // Record of one uint16 and one string.
            // Status Code (option code 13).
            return (OptionPtr(new Option6StatusCode(begin, end)));

        case D6O_BOOTFILE_PARAM:
            // Array of tuples.
            // Bootfile params (option code 60).
            return (factoryOpaqueDataTuples(Option::V6, getCode(), begin, end));

        case D6O_PD_EXCLUDE:
            // Type IPv6 prefix.
            // Prefix Exclude (option code 67),
            return (OptionPtr(new Option6PDExclude(begin, end)));

        case D6O_V6_DNR:
            return (OptionPtr(new Option6Dnr(begin, end, convenient_notation)));

        default:
            break;
        }
    } else if ((u == Option::V4) && haveSpace(DHCP4_OPTION_SPACE)) {
        switch (getCode()) {
        case DHO_SERVICE_SCOPE:
            // Record of a boolean and a string.
            return (OptionPtr(new Option4SlpServiceScope(begin, end)));

        case DHO_FQDN:
            // Record of 3 uint8 and a FQDN, no array.
            return (OptionPtr(new Option4ClientFqdn(begin, end)));

        case DHO_CLASSLESS_STATIC_ROUTE:
            return (OptionPtr(new OptionClasslessStaticRoute(begin, end, convenient_notation)));

        case DHO_VIVCO_SUBOPTIONS:
            // Record of uint32 followed by binary.
            // V-I Vendor Class (option code 124).
            return (OptionPtr(new OptionVendorClass(Option::V4, begin, end)));

        case DHO_VIVSO_SUBOPTIONS:
            // Type uint32.
            // Vendor-Specific Information (option code 125).
            return (OptionPtr(new OptionVendor(Option::V4, begin, end)));

        case DHO_V4_SZTP_REDIRECT:
            // Array of tuples.
            // DHCPv4 SZTP Redirect Option (option code 143).
            return (factoryOpaqueDataTuples(Option::V4, getCode(), begin, end, OpaqueDataTuple::LENGTH_2_BYTES));

        case DHO_V4_DNR:
            return (OptionPtr(new Option4Dnr(begin, end, convenient_notation)));

        default:
            break;
        }
    }
    if ((u == Option::V4) && haveCompressedFqdnListFormat()) {
        return (factoryFqdnList(Option::V4, begin, end));
    }
    return (OptionPtr());
}

} // end of isc::dhcp namespace
} // end of isc namespace
