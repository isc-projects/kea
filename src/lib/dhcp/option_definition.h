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

#ifndef OPTION_DEFINITION_H
#define OPTION_DEFINITION_H

#include <dhcp/option.h>
#include <dhcp/option_data_types.h>

#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/mem_fun.hpp>
#include <boost/multi_index/sequenced_index.hpp>
#include <boost/multi_index_container.hpp>
#include <boost/shared_ptr.hpp>

namespace isc {
namespace dhcp {

/// @brief Forward declaration to OptionDefinition.
class OptionDefinition;

/// @brief Pointer to option definition object.
typedef boost::shared_ptr<OptionDefinition> OptionDefinitionPtr;

/// @brief Forward declaration to Option6Int.
///
/// This forward declaration is needed to access Option6Int class
/// without having to include option6_int.h header. This is because
/// this header includes libdhcp++.h and this causes circular
/// inclusion between libdhcp++.h, option_definition.h and
/// option6_int.h.
template<typename T>
class Option6Int;

/// @brief Forward declaration to Option6IntArray.
///
/// This forward declaration is needed to access Option6IntArray class
/// without having to include option6_int_array.h header. This is because
/// this header includes libdhcp++.h and this causes circular
/// inclusion between libdhcp++.h, option_definition.h and
/// option6_int_array.h.
template<typename T>
class Option6IntArray;

/// @brief Base class representing a DHCP option definition.
///
/// This is a base class representing a DHCP option definition, which describes
/// the format of the option. In particular, it defines:
/// - option name,
/// - option code,
/// - data fields order and their types,
/// - sub options space that the particular option encapsulates.
///
/// The option type specifies the data type(s) which an option conveys.  If
/// this is a single value the option type points to the data type of the
/// value. For example, DHCPv6 option 8 comprises a two-byte option code, a
/// two-byte option length and two-byte field that carries a uint16 value
/// (RFC 3315 - http://ietf.org/rfc/rfc3315.txt).  In such a case, the option
/// type is defined as "uint16".
///
/// When the option has a more complex structure, the option type may be
/// defined as "array", "record" or even "array of records".
///
/// Array types should be used when the option contains multiple contiguous
/// data values of the same type laid. For example, DHCPv6 option 6 includes
/// multiple fields holding uint16 codes of requested DHCPv6 options (RFC 3315).
/// Such an option can be represented with this class by setting the option
/// type to "uint16" and the array indicator (array_type) to true.  The number
/// of elements in the array is effectively unlimited (although it is actually
/// limited by the maximal DHCPv6 option length).
///
/// Should the option comprise data fields of different types, the "record"
/// option type is used. In such cases the data field types within the record
/// are specified using \ref OptioDefinition::addRecordField.
///
/// When the OptionDefinition object has been sucessfully created, it can be
/// queried to return the appropriate option factory function for the specified
/// specified option format. There are a number of "standard" factory functions
/// that cover well known (common) formats.  If the particular format does not
/// match any common format the generic factory function is returned.
///
/// The following data type strings are supported:
/// - "empty" (option does not contain data fields)
/// - "boolean"
/// - "int8"
/// - "int16"
/// - "int32"
/// - "uint8"
/// - "uint16"
/// - "uint32"
/// - "ipv4-address" (IPv4 Address)
/// - "ipv6-address" (IPV6 Address)
/// - "string"
/// - "fqdn" (fully qualified name)
/// - "record" (set of data fields of different types)
///
/// @todo Extend the comment to describe "generic factories".
/// @todo Extend this class to use custom namespaces.
/// @todo Extend this class with more factory functions.
class OptionDefinition {
public:

    /// Data types of DHCP option fields.
    enum DataType {
        EMPTY_TYPE,
        BINARY_TYPE,
        BOOLEAN_TYPE,
        INT8_TYPE,
        INT16_TYPE,
        INT32_TYPE,
        UINT8_TYPE,
        UINT16_TYPE,
        UINT32_TYPE,
        IPV4_ADDRESS_TYPE,
        IPV6_ADDRESS_TYPE,
        STRING_TYPE,
        FQDN_TYPE,
        RECORD_TYPE,
        UNKNOWN_TYPE
    };

    /// List of fields within the record.
    typedef std::vector<DataType> RecordFieldsCollection;
    /// Const iterator for record data fields.
    typedef std::vector<DataType>::const_iterator RecordFieldsConstIter;

private:

    /// @brief Utility class for operations on DataTypes.
    ///
    /// This class is implemented as the singleton because the list of
    /// supported data types need only be loaded only once into memory as it
    /// can persist for all option definitions.
    ///
    /// @todo This class can be extended to return the string value
    /// representing the data type from the enum value.
    class DataTypeUtil {
    public:

        /// @brief Return the sole instance of this class.
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
        /// @brief Private constructor.
        ///
        /// Constructor initializes the internal data structures, e.g.
        /// mapping between data type name and the corresponding enum.
        /// This constructor is private to ensure that exactly one
        /// instance of this class can be created using \ref instance
        /// function.
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
    /// @param array_type array indicator, if true it indicates that the
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
    /// @param array_type array indicator, if true it indicates that the
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
    /// The method returns the bool value to indicate whether the option is a
    /// a single value or an array of values.
    ///
    /// @return true if option comprises an array of values.
    bool getArrayType() const { return (array_type_); }

    /// @brief Return option code.
    ///
    /// @return option code.
    uint16_t getCode() const { return (code_); }

    /// @brief Return factory function for the given definition.
    ///
    /// @throw isc::OutOfRange if \ref validate returns it.
    /// @throw isc::BadValue if \ref validate returns it.
    /// @return pointer to a factory function.
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

    /// @brief Check if the option definition is valid.
    ///
    /// @throw isc::OutOfRange if invalid option type was specified.
    /// @throw isc::BadValue if invalid option name was specified,
    /// e.g. empty or containing spaces.
    void validate() const;

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
    ///
    /// @throw isc::OutOfRange if length of the provided option buffer
    /// is not multiple of IPV4 address length.
    static OptionPtr factoryAddrList4(Option::Universe u, uint16_t type,
                                      const OptionBuffer& buf);

    /// @brief Factory to create option with address list.
    ///
    /// @param u universe (must be V6).
    /// @param type option type.
    /// @param buf option buffer with a list of IPv6 addresses.
    ///
    /// @throw isc::OutOfaRange if length of provided option buffer
    /// is not multiple of IPV6 address length.
    static OptionPtr factoryAddrList6(Option::Universe u, uint16_t type,
                                      const OptionBuffer& buf);

    /// @brief Empty option factory.
    ///
    /// @param u universe (V6 or V4).
    /// @param type option type.
    /// @param buf option buffer (must be empty).
    static OptionPtr factoryEmpty(Option::Universe u, uint16_t type,
                                  const OptionBuffer& buf);

    /// @brief Factory to create generic option.
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
    /// @param type option type.
    /// @param buf option buffer.
    /// @tparam T type of the data field (must be one of the uintX_t or intX_t).
    ///
    /// @throw isc::OutOfRange if provided option buffer length is invalid.
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
    /// @param type option type.
    /// @param buf option buffer.
    /// @tparam T type of the data field (must be one of the uintX_t or intX_t).
    ///
    /// @throw isc::OutOfRange if provided option buffer length is invalid.
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

    /// @brief Check if specified option format is a record with 3 fields
    /// where first one is custom, and two others are uint32.
    ///
    /// This is a helper function for functions that detect IA_NA and IAAddr
    /// option formats.
    ///
    /// @param first_type type of the first data field.
    ///
    /// @return true if actual option format matches expected format.
    bool haveIAx6Format(const OptionDefinition::DataType first_type) const;

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


/// @brief Multi index container for DHCP option definitions.
///
/// This container allows to search for DHCP option definition
/// using two indexes:
/// - sequenced: used to access elements in the order they have
/// been added to the container
/// - option code: used to search defintions of options
/// with a specified option code (aka option type).
/// Note that this container can hold multiple options with the
/// same code. For this reason, the latter index can be used to
/// obtain a range of options for a particular option code.
/// 
/// @todo: need an index to search options using option space name
/// once option spaces are implemented.
typedef boost::multi_index_container<
    // Container comprises elements of OptionDefinition type.
    OptionDefinitionPtr,
    // Here we start enumerating various indexes.
    boost::multi_index::indexed_by<
        // Sequenced index allows accessing elements in the same way
        // as elements in std::list. Sequenced is an index #0.
        boost::multi_index::sequenced<>,
        // Start definition of index #1.
        boost::multi_index::hashed_non_unique<
            // Use option type as the index key. The type is held
            // in OptionDefinition object so we have to call
            // OptionDefinition::getCode to retrieve this key
            // for each element. The option code is non-unique so
            // multiple elements with the same option code can
            // be returned by this index.
            boost::multi_index::const_mem_fun<
                OptionDefinition,
                uint16_t,
                &OptionDefinition::getCode
            >
        >
    >
> OptionDefContainer;

/// Type of the index #1 - option type.
typedef OptionDefContainer::nth_index<1>::type OptionDefContainerTypeIndex;
/// Pair of iterators to represent the range of options definitions
///  having the same option type value. The first element in this pair
///  represents the begining of the range, the second element
///  represents the end.
typedef std::pair<OptionDefContainerTypeIndex::const_iterator,
                  OptionDefContainerTypeIndex::const_iterator> OptionDefContainerTypeRange;


} // namespace isc::dhcp
} // namespace isc

#endif // OPTION_DEFINITION_H
