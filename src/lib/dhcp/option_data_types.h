// Copyright (C) 2012-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef OPTION_DATA_TYPES_H
#define OPTION_DATA_TYPES_H

#include <asiolink/io_address.h>
#include <dhcp/opaque_data_tuple.h>
#include <dhcp/option.h>
#include <exceptions/exceptions.h>
#include <util/io_utilities.h>

#include <stdint.h>
#include <utility>

namespace isc {
namespace dhcp {

/// @brief Exception to be thrown when invalid type specified as template parameter.
class InvalidDataType : public Exception {
public:
    InvalidDataType(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) { };
};

/// @brief Exception to be thrown when cast to the data type was unsuccessful.
class BadDataTypeCast : public Exception {
public:
    BadDataTypeCast(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) { };
};

/// @brief Data types of DHCP option fields.
///
/// @warning The order of data types matters: OPT_UNKNOWN_TYPE
/// must always be the last position. Also, OPT_RECORD_TYPE
/// must be at last but one position. This is because some
/// functions perform sanity checks on data type values using
/// '>' operators, assuming that all values beyond the
/// OPT_RECORD_TYPE are invalid.
enum OptionDataType {
    OPT_EMPTY_TYPE,
    OPT_BINARY_TYPE,
    OPT_BOOLEAN_TYPE,
    OPT_INT8_TYPE,
    OPT_INT16_TYPE,
    OPT_INT32_TYPE,
    OPT_UINT8_TYPE,
    OPT_UINT16_TYPE,
    OPT_UINT32_TYPE,
    OPT_ANY_ADDRESS_TYPE,
    OPT_IPV4_ADDRESS_TYPE,
    OPT_IPV6_ADDRESS_TYPE,
    OPT_IPV6_PREFIX_TYPE,
    OPT_PSID_TYPE,
    OPT_STRING_TYPE,
    OPT_TUPLE_TYPE,
    OPT_FQDN_TYPE,
    OPT_RECORD_TYPE,
    OPT_UNKNOWN_TYPE
};

/// @brief Parameters being used to make up an option definition.
struct OptionDefParams {
    const char*             name;           // option name
    uint16_t                code;           // option code
    const char*             space;          // option space
    OptionDataType          type;           // data type
    bool                    array;          // is array
    const OptionDataType*   records;        // record fields
    size_t                  records_size;   // number of fields in a record
    const char*             encapsulates;   // option space encapsulated by the
                                            // particular option.
};

/// @brief Encapsulation of option definition parameters and the structure size.
struct OptionDefParamsEncapsulation {
    const struct OptionDefParams*   optionDefParams;    // parameters structure
    const int                       size;               // structure size
    const char*                     space;              // option space
};

/// @brief Trait class for data types supported in DHCP option definitions.
///
/// This is useful to check whether the type specified as template parameter
/// is supported by classes like OptionInt, OptionIntArray and some template
/// factory functions in OptionDefinition class.
template<typename T>
struct OptionDataTypeTraits {
    static const bool valid = false;
    static const int len = 0;
    static const bool integer_type = false;
    static const OptionDataType type = OPT_UNKNOWN_TYPE;
};

/// binary type is supported
template<>
struct OptionDataTypeTraits<OptionBuffer> {
    static const bool valid = true;
    static const int len = 0;
    static const bool integer_type = false;
    static const OptionDataType type = OPT_BINARY_TYPE;
};

/// bool type is supported
template<>
struct OptionDataTypeTraits<bool> {
    static const bool valid = true;
    static const int len = sizeof(uint8_t);
    static const bool integer_type = false;
    static const OptionDataType type = OPT_BOOLEAN_TYPE;
};

/// int8_t type is supported.
template<>
struct OptionDataTypeTraits<int8_t> {
    static const bool valid = true;
    static const int len = 1;
    static const bool integer_type = true;
    static const OptionDataType type = OPT_INT8_TYPE;
};

/// int16_t type is supported.
template<>
struct OptionDataTypeTraits<int16_t> {
    static const bool valid = true;
    static const int len = 2;
    static const bool integer_type = true;
    static const OptionDataType type = OPT_INT16_TYPE;
};

/// int32_t type is supported.
template<>
struct OptionDataTypeTraits<int32_t> {
    static const bool valid = true;
    static const int len = 4;
    static const bool integer_type = true;
    static const OptionDataType type = OPT_INT32_TYPE;
};

/// uint8_t type is supported.
template<>
struct OptionDataTypeTraits<uint8_t> {
    static const bool valid = true;
    static const int len = 1;
    static const bool integer_type = true;
    static const OptionDataType type = OPT_UINT8_TYPE;
};

/// uint16_t type is supported.
template<>
struct OptionDataTypeTraits<uint16_t> {
    static const bool valid = true;
    static const int len = 2;
    static const bool integer_type = true;
    static const OptionDataType type = OPT_UINT16_TYPE;
};

/// uint32_t type is supported.
template<>
struct OptionDataTypeTraits<uint32_t> {
    static const bool valid = true;
    static const int len = 4;
    static const bool integer_type = true;
    static const OptionDataType type = OPT_UINT32_TYPE;
};

/// IPv4 and IPv6 address type is supported
template<>
struct OptionDataTypeTraits<asiolink::IOAddress> {
    static const bool valid = true;
    // The len value is used to determine the size of the data
    // to be written to an option buffer. IOAddress object may
    // either represent an IPv4 or IPv6 addresses which have
    // different lengths. Thus we can't put fixed value here.
    // The length of a data to be written into an option buffer
    // have to be determined in the runtime for a particular
    // IOAddress object. Thus setting len to zero.
    static const int len = 0;
    static const bool integer_type = false;
    static const OptionDataType type = OPT_ANY_ADDRESS_TYPE;
};

/// string type is supported
template<>
struct OptionDataTypeTraits<std::string> {
    static const bool valid = true;
    // The len value is used to determine the size of the data
    // to be written to an option buffer. For strings this
    // size is unknown until we actually deal with the particular
    // string to be written. Thus setting it to zero.
    static const int len = 0;
    static const bool integer_type = false;
    static const OptionDataType type = OPT_STRING_TYPE;
};

/// @brief Encapsulates PSID length.
class PSIDLen {
public:

    /// @brief Default constructor.
    PSIDLen() : psid_len_(0) { }

    /// @brief Constructor.
    ///
    /// It checks that the specified value is not greater than
    /// 16, which is a maximum value for the PSID length.
    ///
    /// @param psid_len PSID length.
    /// @throw isc::OutOfRange If specified PSID length is greater than 16.
    explicit PSIDLen(const uint8_t psid_len)
        : psid_len_(psid_len) {
        if (psid_len_ > sizeof(uint16_t) * 8) {
            isc_throw(isc::OutOfRange, "invalid value "
                      << asUnsigned() << " of PSID length");
        }
    }

    /// @brief Returns PSID length as uint8_t value.
    uint8_t asUint8() const {
        return (psid_len_);
    }

    /// @brief Returns PSID length as unsigned int.
    ///
    /// This is useful to convert the value to a numeric type which
    /// can be logged directly. Note that the uint8_t value has to
    /// be cast to an integer value to be logged as a number. This
    /// is because the uint8_t is often implemented as char, in which
    /// case directly logging an uint8_t value prints a character rather
    /// than a number.
    unsigned int asUnsigned() const {
        return (static_cast<unsigned>(psid_len_));
    }

private:

    /// @brief PSID length.
    uint8_t psid_len_;
};

/// @brief Encapsulates PSID value.
class PSID {
public:

    /// @brief Default constructor.
    PSID() : psid_(0) { }

    /// @brief Constructor.
    ///
    /// This constructor doesn't perform any checks on the input data.
    ///
    /// @param psid PSID value.
    explicit PSID(const uint16_t psid)
        : psid_(psid) {
    }

    /// @brief Returns PSID value as a number.
    uint16_t asUint16() const {
        return (psid_);
    }

private:

    /// @brief PSID value.
    uint16_t psid_;

};

/// @brief Defines a pair of PSID length / value.
typedef std::pair<PSIDLen, PSID> PSIDTuple;

/// @brief Encapsulates prefix length.
class PrefixLen {
public:

    /// @brief Default constructor.
    PrefixLen() : prefix_len_(0) { }

    /// @brief Constructor.
    ///
    /// This constructor checks if the specified prefix length is
    /// in the range of 0 to 128.
    ///
    /// @param prefix_len Prefix length value.
    /// @throw isc::OutOfRange If specified prefix length is greater than 128.
    explicit PrefixLen(const uint8_t prefix_len)
        : prefix_len_(prefix_len) {
    }

    /// @brief Returns prefix length as uint8_t value.
    uint8_t asUint8() const {
        return (prefix_len_);
    }

    /// @brief Returns prefix length as unsigned int.
    ///
    /// This is useful to convert the value to a numeric type which
    /// can be logged directly. See @ref PSIDLen::asUnsigned for the
    /// use cases of this accessor.
    unsigned int asUnsigned() const {
        return (static_cast<unsigned>(prefix_len_));
    }

private:

    /// @brief Prefix length.
    uint8_t prefix_len_;
};

/// @brief Defines a pair of prefix length / value.
typedef std::pair<PrefixLen, asiolink::IOAddress> PrefixTuple;

/// @brief Utility class for option data types.
///
/// This class provides a set of utility functions to operate on
/// supported DHCP option data types. It includes conversion
/// between enumerator values representing data types and data
/// type names. It also includes a set of functions that write
/// data into option buffers and read data from option buffers.
/// The data being written and read are converted from/to actual
/// data types.
/// @note This is a singleton class but it can be accessed via
/// static methods only.
class OptionDataTypeUtil {
public:

    /// @brief Return option data type from its name.
    ///
    /// @param data_type data type name.
    /// @return option data type.
    static OptionDataType getDataType(const std::string& data_type);

    /// @brief Return option data type name from the data type enumerator.
    ///
    /// @param data_type option data type.
    /// @return option data type name.
    static const std::string& getDataTypeName(const OptionDataType data_type);

    /// @brief Get data type buffer length.
    ///
    /// This function returns the size of a particular data type.
    /// Values returned by this function correspond to the data type
    /// sizes defined in OptionDataTypeTraits (IPV4_ADDRESS_TYPE and
    /// IPV6_ADDRESS_TYPE are exceptions here) so they rather indicate
    /// the fixed length of the data being written into the buffer,
    /// not the size of the particular data type. Thus for data types
    /// such as string, binary etc. for which the buffer length can't
    /// be determined this function returns 0.
    /// In addition, this function returns the data sizes for
    /// IPV4_ADDRESS_TYPE and IPV6_ADDRESS_TYPE as their buffer
    /// representations have fixed data lengths: 4 and 16 respectively.
    ///
    /// @param data_type data type which size is to be returned.
    /// @return data type size or zero for variable length types.
    static int getDataTypeLen(const OptionDataType data_type);

    /// @brief Read IPv4 or IPv6 address from a buffer.
    ///
    /// @param buf input buffer.
    /// @param family address family: AF_INET or AF_INET6.
    ///
    /// @throw isc::dhcp::BadDataTypeCast when the data being read
    /// is truncated.
    /// @return address being read.
    static asiolink::IOAddress readAddress(const std::vector<uint8_t>& buf,
                                           const short family);

    /// @brief Append IPv4 or IPv6 address to a buffer.
    ///
    /// @param address IPv4 or IPv6 address.
    /// @param [out] buf output buffer.
    static void writeAddress(const asiolink::IOAddress& address,
                             std::vector<uint8_t>& buf);

    /// @brief Append hex-encoded binary values to a buffer.
    ///
    /// @param hex_str string representing a binary value encoded
    /// with hexadecimal digits (without 0x prefix).
    /// @param [out] buf output buffer.
    static void writeBinary(const std::string& hex_str,
                            std::vector<uint8_t>& buf);

    /// @brief Read length and string tuple from a buffer.
    ///
    /// @param buf input buffer.
    /// @param lengthfieldtype LENGTH_1_BYTE (DHCPv4) or LENGTH_2_BYTES (DHCPv6)
    /// @throw isc::dhcp::BadDataTypeCast when the data being read
    /// is truncated.
    /// @return string being read.
    static std::string readTuple(const std::vector<uint8_t>& buf,
                                 OpaqueDataTuple::LengthFieldType lengthfieldtype);

    /// @brief Read length and string tuple from a buffer.
    ///
    /// @param buf input buffer.
    /// @param tuple reference of the tuple to read into
    /// @throw isc::dhcp::BadDataTypeCast when the data being read
    /// is truncated.
    static void readTuple(const std::vector<uint8_t>& buf,
                          OpaqueDataTuple& tuple);

    /// @brief Append length and string tuple to a buffer
    ///
    /// @param value length and string tuple
    /// @param lengthfieldtype LENGTH_1_BYTE (DHCPv4) or LENGTH_2_BYTES (DHCPv6)
    /// @param [out] buf output buffer.
    static void writeTuple(const std::string& value,
                           OpaqueDataTuple::LengthFieldType lengthfieldtype,
                           std::vector<uint8_t>& buf);

    /// @brief Append length and string tuple to a buffer
    ///
    /// @param tuple length and string tuple
    /// @param [out] buf output buffer.
    static void writeTuple(const OpaqueDataTuple& tuple,
                           std::vector<uint8_t>& buf);

    /// @brief Returns Length Field Type for a tuple.
    ///
    /// Returns Length Field Type for a tuple basing on the given
    /// Option v4/v6 Universe.
    ///
    /// @param u specifies universe (V4 or V6)
    /// @return By default 1 octet Length Field Type for V4 option
    /// or 2 octets Length Field Type for V6 option
    static OpaqueDataTuple::LengthFieldType getTupleLenFieldType(Option::Universe u);

    /// @brief Read boolean value from a buffer.
    ///
    /// @param buf input buffer.
    ///
    /// @throw isc::dhcp::BadDataTypeCast when the data being read
    /// is truncated or the value is invalid (neither 1 nor 0).
    /// @return boolean value read from a buffer.
    static bool readBool(const std::vector<uint8_t>& buf);

    /// @brief Append boolean value into a buffer.
    ///
    /// The bool value is encoded in a buffer in such a way that
    /// "1" means "true" and "0" means "false".
    ///
    /// @param value boolean value to be written.
    /// @param [out] buf output buffer.
    static void writeBool(const bool value, std::vector<uint8_t>& buf);

    /// @brief Read integer value from a buffer.
    ///
    /// @param buf input buffer.
    /// @tparam integer type of the returned value.
    ///
    /// @throw isc::dhcp::BadDataTypeCast when the data in the buffer
    /// is truncated.
    /// @return integer value being read.
    template<typename T>
    static T readInt(const std::vector<uint8_t>& buf) {
        if (!OptionDataTypeTraits<T>::integer_type) {
            isc_throw(isc::dhcp::InvalidDataType, "specified data type to be returned"
                      " by readInteger is unsupported integer type");
        }

        if (buf.size() < OptionDataTypeTraits<T>::len) {
            isc_throw(isc::dhcp::BadDataTypeCast,
                      "failed to read an integer value from a buffer"
                      << " - buffer is truncated.");
        }

        T value;
        switch (OptionDataTypeTraits<T>::len) {
        case 1:
            value = *(buf.begin());
            break;
        case 2:
            // Calling readUint16 works either for unsigned
            // or signed types.
            value = isc::util::readUint16(&(*buf.begin()), buf.size());
            break;
        case 4:
            // Calling readUint32 works either for unsigned
            // or signed types.
            value = isc::util::readUint32(&(*buf.begin()), buf.size());
            break;
        default:
            // This should not happen because we made checks on data types
            // but it does not hurt to keep throw statement here.
            isc_throw(isc::dhcp::InvalidDataType,
                      "invalid size of the data type to be read as integer.");
        }
        return (value);
    }

    /// @brief Append integer or unsigned integer value to a buffer.
    ///
    /// @param value an integer value to be written into a buffer.
    /// @param [out] buf output buffer.
    /// @tparam data type of the value.
    template<typename T>
    static void writeInt(const T value,
                         std::vector<uint8_t>& buf) {
        if (!OptionDataTypeTraits<T>::integer_type) {
            isc_throw(InvalidDataType, "provided data type is not the supported.");
        }
        switch (OptionDataTypeTraits<T>::len) {
        case 1:
            buf.push_back(static_cast<uint8_t>(value));
            break;
        case 2:
            buf.resize(buf.size() + 2);
            isc::util::writeUint16(static_cast<uint16_t>(value), &buf[buf.size() - 2], 2);
            break;
        case 4:
            buf.resize(buf.size() + 4);
            isc::util::writeUint32(static_cast<uint32_t>(value), &buf[buf.size() - 4], 4);
            break;
        default:
            // The cases above cover whole range of possible data lengths because
            // we check at the beginning of this function that given data type is
            // a supported integer type which can be only 1,2 or 4 bytes long.
            ;
        }
    }

    /// @brief Read FQDN from a buffer as a string value.
    ///
    /// The format of an FQDN within a buffer complies with RFC1035,
    /// section 3.1.
    ///
    /// @param buf input buffer holding a FQDN.
    ///
    /// @throw BadDataTypeCast if a FQDN stored within a buffer is
    /// invalid (e.g. empty, contains invalid characters, truncated).
    /// @return fully qualified domain name in a text form.
    static std::string readFqdn(const std::vector<uint8_t>& buf);

    /// @brief Append FQDN into a buffer.
    ///
    /// This method appends the Fully Qualified Domain Name (FQDN)
    /// represented as string value into a buffer. The format of
    /// the FQDN being stored into a buffer complies with RFC1035,
    /// section 3.1.
    ///
    /// @param fqdn fully qualified domain name to be written.
    /// @param [out] buf output buffer.
    /// @param downcase indicates if the FQDN should be converted to lower
    /// case (if true). By default it is not converted.
    ///
    /// @throw isc::dhcp::BadDataTypeCast if provided FQDN
    /// is invalid.
    static void writeFqdn(const std::string& fqdn,
                          std::vector<uint8_t>& buf,
                          const bool downcase = false);

    /// @brief Return the number of labels in the Name.
    ///
    /// If the specified name is empty the 0 is returned.
    ///
    /// @param text_name A text representation of the name.
    ///
    /// @return A number of labels in the provided name or 0 if the
    /// name string is empty.
    /// @throw isc::dhcp::BadDataTypeCast if provided name is malformed.
    static unsigned int getLabelCount(const std::string& text_name);

    /// @brief Read prefix from a buffer.
    ///
    /// This method reads prefix length and a prefix value from a buffer.
    /// The prefix value has variable length and this length is determined
    /// from the first byte of the buffer. If the length is not divisible
    /// by 8, the prefix is padded with zeros to the next byte boundary.
    ///
    /// @param buf input buffer holding a prefix length / prefix tuple.
    ///
    /// @return Prefix length and value.
    static PrefixTuple readPrefix(const std::vector<uint8_t>& buf);

    /// @brief Append prefix into a buffer.
    ///
    /// This method writes prefix length (1 byte) followed by a variable
    /// length prefix.
    ///
    /// @param prefix_len Prefix length in bits (0 to 128).
    /// @param prefix Prefix value.
    /// @param [out] buf Output buffer.
    static void writePrefix(const PrefixLen& prefix_len,
                            const asiolink::IOAddress& prefix,
                            std::vector<uint8_t>& buf);

    /// @brief Read PSID length / value tuple from a buffer.
    ///
    /// This method reads three bytes from a buffer. The first byte
    /// holds a PSID length value. The remaining two bytes contain a
    /// zero padded PSID value.
    ///
    /// @return PSID length / value tuple.
    /// @throw isc::dhcp::BadDataTypeCast if PSID length or value held
    /// in the buffer is incorrect or the buffer is truncated.
    static PSIDTuple readPsid(const std::vector<uint8_t>& buf);

    /// @brief Append PSID length/value into a buffer.
    ///
    /// This method appends 1 byte of PSID length and 2 bytes of PSID
    /// value into a buffer. The PSID value contains a PSID length
    /// number of significant bits, followed by 16 - PSID length
    /// zero bits.
    ///
    /// @param psid_len PSID length in the range of 0 to 16 holding the
    /// number of significant bits within the PSID value.
    /// @param psid PSID value, where the lowest value is 0, and the
    /// highest value is 2^(PSID length)-1.
    /// @param [out] buf output buffer.
    ///
    /// @throw isc::dhcp::BadDataTypeCast if specified psid_len or
    /// psid value is incorrect.
    static void writePsid(const PSIDLen& psid_len, const PSID& psid,
                          std::vector<uint8_t>& buf);

    /// @brief Read string value from a buffer.
    ///
    /// To be compliant with RFC 2132, Sec. 2, trailing NULLs are trimmed.
    /// @param buf input buffer.
    ///
    /// @return string value being read.
    /// @throw isc::dhcp::OutOfRange is the payload contains only NULLs.
    static std::string readString(const std::vector<uint8_t>& buf);

    /// @brief Write UTF8-encoded string into a buffer.
    ///
    /// @param value string value to be written into a buffer.
    /// @param [out] buf output buffer.
    static void writeString(const std::string& value,
                            std::vector<uint8_t>& buf);
private:

    /// The container holding mapping of data type names to
    /// data types enumerator.
    std::map<std::string, OptionDataType> data_types_;

    /// The container holding mapping of data types to data
    /// type names.
    std::map<OptionDataType, std::string> data_type_names_;

    /// @brief Private constructor.
    ///
    /// This constructor is private because this class should
    /// be used as singleton (through static public functions).
    OptionDataTypeUtil();

    /// @brief Return instance of OptionDataTypeUtil
    ///
    /// This function is used by some of the public static functions
    /// to create an instance of OptionDataTypeUtil class.
    /// When this instance is called it calls the classes constructor
    /// and initializes some of the private data members.
    ///
    /// @return instance of OptionDataTypeUtil singleton.
    static OptionDataTypeUtil& instance();

    /// @brief Return option data type from its name.
    ///
    /// @param data_type data type name.
    /// @return option data type.
    OptionDataType getDataTypeImpl(const std::string& data_type) const;

    /// @brief Return option data type name from the data type enumerator.
    ///
    /// @param data_type option data type.
    /// @return option data type name.
    const std::string& getDataTypeNameImpl(const OptionDataType data_type) const;
};


} // isc::dhcp namespace
} // isc namespace

#endif // OPTION_DATA_TYPES_H
