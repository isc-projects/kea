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

#ifndef OPTION_DEFINITION_H_
#define OPTION_DEFINITION_H_

#include "dhcp/option_data_types.h"
#include "dhcp/option6_int.h"
#include "dhcp/option6_int_array.h"
#include "dhcp/option.h"

namespace isc {
namespace dhcp {

/// @brief Base class representing DHCP option definitions.
///
/// This is a base class representing DHCP options definitions.
/// The definition describes the format of the option. In particular
/// it defines:
/// - option name,
/// - option code,
/// - data fields order and their types,
/// - sub options space that the particular option encapsulates.
///
/// The option type specifies the data type(s) which option conveys.
/// If it is to convey single value the option type points to the
/// data type of this value. For example, DHCPv6 option 8 comprises
/// 2-byte option code, 2-byte option length and 2-byte field that
/// carries uint16 value (http://ietf.org/rfc/rfc3315.txt).
/// In such case option type is defined as "uint16". In case when
/// the particular option has more complex structure the option type
/// may be defined as "array", "record" or even "array of records".
/// Array types should be used when the option contains multiple
/// data fields of the same type laid successively. For example,
/// DHCPv6 option 6 includes multiple fields holding uint16 codes
/// of requested DHCPv6 options (http://ietf.org/rfc/rfc3315.txt).
/// Such option can be represented with this class by setting
/// option type to "uint16" and array indicator (array_type) to true.
/// The number of elements in the array is unlimited (actually it is
/// limited by the maximal DHCPv6 option length).
/// Should option comprise data fields of different types the "record"
/// option type is used. In such cases the data field types within the
/// record are specified using \ref OptionDefinition::AddRecordField.
/// When OptionDefinition object has been sucessfully created it
/// can be queried to return the appropriate option factory function
/// for the specified option format. There is a number of "standard"
/// factory functions that cover well known (common) formats.
/// If the particular format does not match any common format the generic
/// factory function is returned.
///
/// The following data type strings are supported:
/// - "empty" - option does not contain data fields
/// - "boolean"
/// - "int8"
/// - "int16"
/// - "int32"
/// - "uint8"
/// - "uint16"
/// - "uint32"
/// - "ipv4-address" - IPv4 Address
/// - "ipv6-address" - IPV6 Address
/// - "string"
/// - "fqdn" - fully qualified name
/// - "record" - set of data fields of different types
///
/// @todo Extend the comment to describe "generic factories".
/// @todo Extend this class to use custom namespaces.
class OptionDefinition {
public:

    /// Data types of DHCP option fields.
    enum DataType {
        EMPTY_TYPE = 0,
        BOOLEAN_TYPE = 1,
        INT8_TYPE = 2,
        INT16_TYPE = 3,
        INT32_TYPE = 4,
        UINT8_TYPE = 5,
        UINT16_TYPE = 6,
        UINT32_TYPE = 7,
        IPV4_ADDRESS_TYPE = 8,
        IPV6_ADDRESS_TYPE = 9,
        STRING_TYPE = 10,
        FQDN_TYPE = 11,
        RECORD_TYPE = 12,
        UNKNOWN_TYPE = RECORD_TYPE + 1
    };

    /// List of fields within the record.
    typedef std::vector<DataType> RecordFieldsCollection;
    /// Const iterator for record data fields.
    typedef std::vector<DataType>::const_iterator RecordFieldsConstIter;

private:

    /// @brief Utility class for operations on DataTypes.
    class DataTypeUtil {
    public:

        /// @brief Return sole instance of this class.
        ///
        /// @return instance of this class.
        static DataTypeUtil& instance() {
            static DataTypeUtil instance;
            return (instance);
        }

        /// @brief Convert type given as string value to option data type.
        ///
        /// @param data_type_name data type string.
        ///
        /// @return option data type.
        DataType getDataType(const std::string& data_type_name);

    private:
        /// @brief Constructor.
        ///
        /// Constructor initializes the internal data structures, e.g.
        /// mapping between data type name and the corresponding enum.
        DataTypeUtil();

        /// Map of data types, maps name of the type to enum value.
        std::map<std::string, DataType> data_types_;
    };

public:
    /// @brief Constructor.
    ///
    /// @param name option name.
    /// @param code option code.
    /// @param type option data type as string.
    /// @param array_type array indicator, if true it indicates that
    /// option fields are the array.
    OptionDefinition(const std::string& name,
                     const uint16_t code,
                     const std::string& type,
                     const bool array_type = false);

    /// @brief Constructor.
    ///
    /// @param name option name.
    /// @param code option code.
    /// @param type option data type.
    /// @param array_type array indicator, if true it indicates that
    /// option fields are the array.
    OptionDefinition(const std::string& name,
                     const uint16_t code,
                     const DataType type,
                     const bool array_type = false);

    /// @brief Adds data field to the record.
    ///
    /// @param data_type_name name of the data type for the field.
    ///
    /// @throw isc::InvalidOperation if option type is not set to RECORD_TYPE.
    /// @throw isc::BadValue if specified invalid data type.
    void addRecordField(const std::string& data_type_name);

    /// @brief Adds data field to the record.
    ///
    /// @param data_type data type for the field.
    ///
    /// @throw isc::InvalidOperation if option type is not set to RECORD_TYPE.
    /// @throw isc::BadValue if specified invalid data type.
    void addRecordField(const DataType data_type);

    /// @brief Return array type indicator.
    ///
    /// The method returns the bool value to indicate wheter
    /// option is single value or array of values.
    ///
    /// @return true if option comprises an array of values.
    bool getArrayType() const { return (array_type_); }

    /// @brief Return option code.
    ///
    /// @return option code.
    uint16_t getCode() const { return (code_); }

    /// @brief Return factory function for the given definition.
    ///
    /// @return pointer to factory function.
    Option::Factory* getFactory() const;

    /// @brief Return option name.
    ///
    /// @return option name.
    const std::string& getName() const { return (name_); }

    /// @brief Return list of record fields.
    ///
    /// @return list of record fields.
    const RecordFieldsCollection& getRecordFields() const { return (record_fields_); }

    /// @brief Return option data type.
    ///
    /// @return option data type.
    DataType getType() const { return (type_); };

    /// @brief Check if specified format is IA_NA option format.
    ///
    /// @return true if specified format is IA_NA option format.
    bool haveIA6Format() const;

    /// @brief Check if specified format is IAADDR option format.
    ///
    /// @return true if specified format is IAADDR option format.
    bool haveIAAddr6Format() const;

    /// @brief Factory to create option with address list.
    ///
    /// @param u universe (must be V4).
    /// @param type option type.
    /// @param buf option buffer with a list of IPv4 addresses.
    static OptionPtr factoryAddrList4(Option::Universe u, uint16_t type,
                                      const OptionBuffer& buf);

    /// @brief Factory to create option with address list.
    ///
    /// @param u universe (must be V6).
    /// @param type option type.
    /// @param buf option buffer with a list of IPv6 addresses.
    static OptionPtr factoryAddrList6(Option::Universe u, uint16_t type,
                                      const OptionBuffer& buf);

    /// @brief Empty option factory.
    ///
    /// @param u universe (V6 or V4).
    /// @param type option type.
    /// @param buf option buffer (must be empty).
    static OptionPtr factoryEmpty(Option::Universe u, uint16_t type,
                                  const OptionBuffer& buf);

    /// @brief Factory to create generic option..
    ///
    /// @param u universe (V6 or V4).
    /// @param type option type.
    /// @param buf option buffer.
    static OptionPtr factoryGeneric(Option::Universe u, uint16_t type,
                                    const OptionBuffer& buf);

    /// @brief Factory for IA-type of option.
    ///
    /// @param u universe (must be V6).
    /// @param type option type.
    /// @param buf option buffer.
    ///
    /// @throw isc::OutOfRange if provided option buffer is too short or
    /// too long. Expected size is 12 bytes.
    /// @throw isc::BadValue if specified universe value is not V6.
    static OptionPtr factoryIA6(Option::Universe u, uint16_t type,
                                const OptionBuffer& buf);

    /// @brief Factory for IAADDR-type of option.
    ///
    /// @param u universe (must be V6).
    /// @param type option type.
    /// @param buf option buffer.
    ///
    /// @throw isc::OutOfRange if provided option buffer is too short or
    /// too long. Expected size is 24 bytes.
    /// @throw isc::BadValue if specified universe value is not V6.
    static OptionPtr factoryIAAddr6(Option::Universe u, uint16_t type,
                                const OptionBuffer& buf);

    /// @brief Factory function to create option with integer value.
    ///
    /// @param u universe (V6 or V4).
    /// @param type option type.
    /// @param buf option buffer.
    /// @param T type of the data field (must be one of the uintX_t or intX_t).
    template<typename T>
    static OptionPtr factoryInteger(Option::Universe, uint16_t type, const OptionBuffer& buf) {
        if (buf.size() > sizeof(T)) {
            isc_throw(isc::OutOfRange, "provided option buffer is too large, expected: "
                      << sizeof(T) << " bytes");
        }
        OptionPtr option(new Option6Int<T>(type, buf.begin(), buf.end()));
        return (option);
    }

    /// @brief Factory function to create option with array of integer values.
    ///
    /// @param u universe (V6 or V4).
    /// @param type option type.
    /// @param buf option buffer.
    /// @param T type of the data field (must be one of the uintX_t or intX_t).
    template<typename T>
    static OptionPtr factoryIntegerArray(Option::Universe, uint16_t type, const OptionBuffer& buf) {
        if (buf.size() == 0) {
            isc_throw(isc::OutOfRange, "option buffer length must be greater than zero");
        } else if (buf.size() % OptionDataTypes<T>::len != 0) {
            isc_throw(isc::OutOfRange, "option buffer length must be multiple of "
                      << OptionDataTypes<T>::len << " bytes");
        }
        OptionPtr option(new Option6IntArray<T>(type, buf.begin(), buf.end()));
        return (option);
    }

private:

    /// @brief Check if specified type matches option definition type.
    ///
    /// @return true if specified type matches option definition type.
    inline bool haveType(const DataType type) const {
        return (type == type_);
    }

    /// @brief Sanity check universe value.
    ///
    /// @param expected_universe expected universe value.
    /// @param actual_universe actual universe value.
    ///
    /// @throw isc::BadValue if expected universe and actual universe don't match.
    static inline void sanityCheckUniverse(const Option::Universe expected_universe,
                                           const Option::Universe actual_universe); 

    /// @brief Check if the option definition is valid.
    ///
    /// @todo: list exceptions it throws.
    void validate() const;

    /// Option name.
    std::string name_;
    /// Option code.
    uint16_t code_;
    /// Option data type.
    DataType type_;
    /// Indicates wheter option is a single value or array.
    bool array_type_;
    /// Collection of data fields within the record.
    RecordFieldsCollection record_fields_;
};


} // namespace isc::dhcp
} // namespace isc

#endif
