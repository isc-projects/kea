// Copyright (C) 2012-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef OPTION_CUSTOM_H
#define OPTION_CUSTOM_H

#include <asiolink/io_address.h>
#include <dhcp/option.h>
#include <dhcp/option_definition.h>
#include <exceptions/isc_assert.h>
#include <util/io_utilities.h>

namespace isc {
namespace dhcp {

/// @brief Option with defined data fields represented as buffers that can
/// be accessed using data field index.
///
/// This class represents an option which has defined structure: data fields
/// of specific types and order. Those fields can be accessed using indexes,
/// where index 0 represents first data field within an option. The last
/// field can be accessed using index equal to 'number of fields' - 1.
/// Internally, the option data is stored as a collection of OptionBuffer
/// objects, each representing data for a particular data field. This data
/// can be converted to the actual data type using methods implemented
/// within this class. This class is used to represent those options that
/// can't be represented by any other specialized class (this excludes the
/// Option class which is generic and can be used to represent any option).
class OptionCustom : public Option {
public:

    /// @brief Constructor, used for options to be sent.
    ///
    /// This constructor creates an instance of an option with default
    /// data set for all data fields. The option buffers are allocated
    /// according to data size being stored in particular data fields.
    /// For variable size data empty buffers are created.
    ///
    /// @param def option definition.
    /// @param u specifies universe (V4 or V6)
    OptionCustom(const OptionDefinition& def, Universe u);

    /// @brief Constructor, used for options to be sent.
    ///
    /// This constructor creates an instance of an option from the whole
    /// supplied buffer. This constructor is mainly used to create an
    /// instances of options to be stored in outgoing DHCP packets.
    /// The buffer used to create the instance of an option can be
    /// created from the option data specified in server's configuration.
    ///
    /// @param def option definition.
    /// @param u specifies universe (V4 or V6).
    /// @param data content of the option.
    ///
    /// @throw OutOfRange if option buffer is truncated.
    ///
    /// @todo list all exceptions thrown by ctor.
    OptionCustom(const OptionDefinition& def, Universe u, const OptionBuffer& data);

    /// @brief Constructor, used for received options.
    ///
    /// This constructor creates an instance an option from the portion
    /// of the buffer specified by iterators. This is mainly useful when
    /// parsing received packets. Such packets are represented by a single
    /// buffer holding option data and all sub options. Methods that are
    /// parsing a packet, supply relevant portions of the packet buffer
    /// to this constructor to create option instances out of it.
    ///
    /// @param def option definition.
    /// @param u specifies universe (V4 or V6).
    /// @param first iterator to the first element that should be copied.
    /// @param last iterator to the next element after the last one
    /// to be copied.
    ///
    /// @throw OutOfRange if option buffer is truncated.
    ///
    /// @todo list all exceptions thrown by ctor.
    OptionCustom(const OptionDefinition& def, Universe u,
                 OptionBufferConstIter first, OptionBufferConstIter last);

    /// @brief Copies this option and returns a pointer to the copy.
    virtual OptionPtr clone() const;

    /// @brief Create new buffer and set its value as an IP address.
    ///
    /// @param address IPv4 or IPv6 address to be written to
    /// a buffer being created.
    void addArrayDataField(const asiolink::IOAddress& address);

    /// @brief Create new buffer and store boolean value in it.
    ///
    /// @param value value to be stored in the created buffer.
    void addArrayDataField(const bool value);

    /// @brief Create new buffer and store integer value in it.
    ///
    /// @param value value to be stored in the created buffer.
    /// @tparam T integer type of the value being stored.
    template<typename T>
    void addArrayDataField(const T value) {
        checkArrayType();
        OptionDataType data_type = definition_.getType();
        // Handle record last field.
        if (data_type == OPT_RECORD_TYPE) {
            data_type = definition_.getRecordFields().back();
        }
        if (OptionDataTypeTraits<T>::type != data_type) {
            isc_throw(isc::dhcp::InvalidDataType,
                      "specified data type " << data_type << " does not"
                      " match the data type in an option definition");
        }

        OptionBuffer buf;
        OptionDataTypeUtil::writeInt<T>(value, buf);
        buffers_.push_back(buf);
    }

    /// @brief Create new buffer and store tuple value in it
    ///
    /// @param value value to be stored as a tuple in the created buffer.
    void addArrayDataField(const std::string& value);

    /// @brief Create new buffer and store tuple value in it
    ///
    /// @param value value to be stored as a tuple in the created buffer.
    void addArrayDataField(const OpaqueDataTuple& value);

    /// @brief Create new buffer and store variable length prefix in it.
    ///
    /// @param prefix_len Prefix length.
    /// @param prefix Prefix.
    void addArrayDataField(const PrefixLen& prefix_len,
                           const asiolink::IOAddress& prefix);

    /// @brief Create new buffer and store PSID length / value in it.
    ///
    /// @param psid_len PSID length.
    /// @param psid PSID.
    void addArrayDataField(const PSIDLen& psid_len, const PSID& psid);

    /// @brief Return a number of the data fields.
    ///
    /// @return number of data fields held by the option.
    uint32_t getDataFieldsNum() const { return (buffers_.size()); }

    /// @brief Read a buffer as IP address.
    ///
    /// @param index buffer index.
    ///
    /// @return IP address read from a buffer.
    /// @throw isc::OutOfRange if index is out of range.
    asiolink::IOAddress readAddress(const uint32_t index = 0) const;

    /// @brief Write an IP address into a buffer.
    ///
    /// @param address IP address being written.
    /// @param index buffer index.
    ///
    /// @throw isc::OutOfRange if index is out of range.
    /// @throw isc::dhcp::BadDataTypeCast if IP address is invalid.
    void writeAddress(const asiolink::IOAddress& address,
                      const uint32_t index = 0);

    /// @brief Read a buffer as binary data.
    ///
    /// @param index buffer index.
    ///
    /// @throw isc::OutOfRange if index is out of range.
    /// @return read buffer holding binary data.
    const OptionBuffer& readBinary(const uint32_t index = 0) const;

    /// @brief Write binary data into a buffer.
    ///
    /// @param buf buffer holding binary data to be written.
    /// @param index buffer index.
    void writeBinary(const OptionBuffer& buf, const uint32_t index = 0);

    /// @brief Read a buffer as length and string tuple.
    ///
    /// @param index buffer index.
    ///
    /// @throw isc::OutOfRange if index is out of range.
    /// @return string read from a buffer.
    std::string readTuple(const uint32_t index = 0) const;

    /// @brief Read a buffer into a length and string tuple.
    ///
    /// @param tuple tuple to fill.
    /// @param index buffer index.
    ///
    /// @throw isc::OutOfRange if index is out of range.
    void readTuple(OpaqueDataTuple& tuple, const uint32_t index = 0) const;

    /// @brief Write a length and string tuple into a buffer.
    ///
    /// @param value value to be written.
    /// @param index buffer index.
    void writeTuple(const std::string& value, const uint32_t index = 0);

    /// @brief Write a length and string tuple into a buffer.
    ///
    /// @param value value to be written.
    /// @param index buffer index.
    void writeTuple(const OpaqueDataTuple& value, const uint32_t index = 0);

    /// @brief Read a buffer as boolean value.
    ///
    /// @param index buffer index.
    ///
    /// @throw isc::OutOfRange if index is out of range.
    /// @return read boolean value.
    bool readBoolean(const uint32_t index = 0) const;

    /// @brief Write a boolean value into a buffer.
    ///
    /// @param value boolean value to be written.
    /// @param index buffer index.
    ///
    /// @throw isc::OutOfRange if index is out of range.
    void writeBoolean(const bool value, const uint32_t index = 0);

    /// @brief Read a buffer as FQDN.
    ///
    /// @param index buffer index.
    ///
    /// @throw isc::OutOfRange if buffer index is out of range.
    /// @throw isc::dhcp::BadDataTypeCast if a buffer being read
    /// does not hold a valid FQDN.
    /// @return string representation if FQDN.
    std::string readFqdn(const uint32_t index = 0) const;

    /// @brief Write an FQDN into a buffer.
    ///
    /// @param fqdn text representation of FQDN.
    /// @param index buffer index.
    ///
    /// @throw isc::OutOfRange if index is out of range.
    void writeFqdn(const std::string& fqdn, const uint32_t index = 0);

    /// @brief Read a buffer as integer value.
    ///
    /// @param index buffer index.
    /// @tparam integer type of a value being returned.
    ///
    /// @throw isc::OutOfRange if index is out of range.
    /// @throw isc::dhcp::InvalidDataType if T is invalid.
    /// @return read integer value.
    template<typename T>
    T readInteger(const uint32_t index = 0) const {
        // Check that the index is not out of range.
        checkIndex(index);
        // Check that T points to a valid integer type and this type
        // is consistent with an option definition.
        checkDataType<T>(index);
        // When we created the buffer we have checked that it has a
        // valid size so this condition here should be always fulfilled.
        isc_throw_assert(buffers_[index].size() == OptionDataTypeTraits<T>::len);
        // Read an integer value.
        return (OptionDataTypeUtil::readInt<T>(buffers_[index]));
    }

    /// @brief Write an integer value into a buffer.
    ///
    /// @param value integer value to be written.
    /// @param index buffer index.
    /// @tparam T integer type of a value being written.
    ///
    /// @throw isc::OutOfRange if index is out of range.
    /// @throw isc::dhcp::InvalidDataType if T is invalid.
    template<typename T>
    void writeInteger(const T value, const uint32_t index = 0) {
        // Check that the index is not out of range.
        checkIndex(index);
        // Check that T points to a valid integer type and this type
        // is consistent with an option definition.
        checkDataType<T>(index);
        // Get some temporary buffer.
        OptionBuffer buf;
        // Try to write to the buffer.
        OptionDataTypeUtil::writeInt<T>(value, buf);
        // If successful, replace the old buffer with new one.
        std::swap(buffers_[index], buf);
    }

    /// @brief Read a buffer as variable length prefix.
    ///
    /// @param index buffer index.
    ///
    /// @return Prefix length / value tuple.
    /// @throw isc::OutOfRange of index is out of range.
    PrefixTuple readPrefix(const uint32_t index = 0) const;

    /// @brief Write prefix length and value into a buffer.
    ///
    /// @param prefix_len Prefix length.
    /// @param prefix Prefix value.
    /// @param index Buffer index.
    ///
    /// @throw isc::OutOfRange if index is out of range.
    void writePrefix(const PrefixLen& prefix_len,
                     const asiolink::IOAddress& prefix,
                     const uint32_t index = 0);

    /// @brief Read a buffer as a PSID length / value tuple.
    ///
    /// @param index buffer index.
    ///
    /// @return PSID length / value tuple.
    /// @throw isc::OutOfRange of index is out of range.
    PSIDTuple readPsid(const uint32_t index = 0) const;

    /// @brief Write PSID length / value into a buffer.
    ///
    /// @param psid_len PSID length value.
    /// @param psid PSID value in the range of 0 .. 2^(PSID length).
    /// @param index buffer index.
    ///
    /// @throw isc::dhcp::BadDataTypeCast if PSID length or value is
    /// invalid.
    /// @throw isc::OutOfRange if index is out of range.
    void writePsid(const PSIDLen& psid_len, const PSID& psid,
                   const uint32_t index = 0);

    /// @brief Read a buffer as string value.
    ///
    /// @param index buffer index.
    ///
    /// @return string value read from buffer.
    /// @throw isc::OutOfRange if index is out of range.
    std::string readString(const uint32_t index = 0) const;

    /// @brief Write a string value into a buffer.
    ///
    /// @param text the string value to be written.
    /// @param index buffer index.
    void writeString(const std::string& text,
                     const uint32_t index = 0);

    /// @brief Writes DHCP option in a wire format to a buffer.
    ///
    /// @param buf output buffer (option will be stored there).
    /// @param check if set to false, allows options larger than 255 for v4
    virtual void pack(isc::util::OutputBuffer& buf, bool check = true) const;

    /// @brief Parses received buffer.
    ///
    /// @param begin iterator to first byte of option data
    /// @param end iterator to end of option data (first byte after option end)
    virtual void unpack(OptionBufferConstIter begin,
                        OptionBufferConstIter end);

    /// @brief Returns string representation of the option.
    ///
    /// @param indent number of spaces before printed text.
    ///
    /// @return string with text representation.
    virtual std::string toText(int indent = 0) const;

    /// @brief Returns length of the complete option (data length +
    ///        DHCPv4/DHCPv6 option header)
    ///
    /// @return length of the option
    virtual uint16_t len() const;

    /// @brief Sets content of this option from buffer.
    ///
    /// Option will be resized to length of buffer.
    ///
    /// @param first iterator pointing to beginning of buffer to copy.
    /// @param last iterator pointing to end of buffer to copy.
    void initialize(const OptionBufferConstIter first,
                    const OptionBufferConstIter last);

private:

    /// @brief Verify that the option comprises an array of values.
    ///
    /// This helper function is used by createArrayEntry functions
    /// and throws an exception if the particular option is not
    /// an array.
    ///
    /// @throw isc::InvalidOperation if option is not an array.
    inline void checkArrayType() const {
        if (!definition_.getArrayType()) {
            isc_throw(InvalidOperation, "failed to add new array entry to an"
                      << " option. The option is not an array.");
        }
    }

    /// @brief Verify that the integer type is consistent with option
    /// field type.
    ///
    /// This convenience function checks that the data type specified as T
    /// is consistent with a type of a data field identified by index.
    ///
    /// @param index data field index.
    /// @tparam data type to be validated.
    ///
    /// @throw isc::dhcp::InvalidDataType if the type is invalid.
    template<typename T>
    // cppcheck-suppress unusedPrivateFunction
    void checkDataType(const uint32_t index) const;

    /// @brief Check if data field index is valid.
    ///
    /// @param index Data field index to check.
    ///
    /// @throw isc::OutOfRange if index is out of range.
    void checkIndex(const uint32_t index) const;

    /// @brief Create a non initialized buffer.
    ///
    /// @param buffer buffer to update.
    /// @param data_type data type of buffer.
    void createBuffer(OptionBuffer& buffer,
                      const OptionDataType data_type) const;

    /// @brief Create a collection of non initialized buffers.
    void createBuffers();

    /// @brief Return length of a buffer.
    ///
    /// @param data_type data type of buffer.
    /// @param in_array true is called from the array case
    /// @param begin iterator to first byte of input data.
    /// @param end iterator to end of input data.
    ///
    /// @return size of data to copy to the buffer.
    /// @throw isc::OutOfRange if option buffer is truncated.
    size_t bufferLength(const OptionDataType data_type, bool in_array,
                        OptionBuffer::const_iterator begin,
                        OptionBuffer::const_iterator end) const;

    /// @brief Create collection of buffers representing data field values.
    ///
    /// @param data_buf a buffer to be parsed.
    void createBuffers(const OptionBuffer& data_buf);

    /// @brief Return a text representation of a data field.
    ///
    /// @param data_type data type of a field.
    /// @param index data field buffer index within a custom option.
    ///
    /// @return text representation of a data field.
    std::string dataFieldToText(const OptionDataType data_type,
                                const uint32_t index) const;

    /// Make this function private as we don't want it to be invoked
    /// on OptionCustom object. We rather want that initialize to
    /// be called instead.
    using Option::setData;

    /// Option definition used to create an option.
    OptionDefinition definition_;

    /// The collection of buffers holding data for option fields.
    /// The order of buffers corresponds to the order of option
    /// fields.
    std::vector<OptionBuffer> buffers_;
};

/// A pointer to the OptionCustom object.
typedef boost::shared_ptr<OptionCustom> OptionCustomPtr;

template<typename T>
void
OptionCustom::checkDataType(const uint32_t index) const {
    // Check that the requested return type is a supported integer.
    if (!OptionDataTypeTraits<T>::integer_type) {
        isc_throw(isc::dhcp::InvalidDataType, "specified data type"
                  " is not a supported integer type.");
    }

    // Get the option definition type.
    OptionDataType data_type = definition_.getType();
    if (data_type == OPT_RECORD_TYPE) {
        const OptionDefinition::RecordFieldsCollection& record_fields =
            definition_.getRecordFields();
        if (definition_.getArrayType()) {
            // If the array flag is set the last record field is an array.
            if (index < record_fields.size()) {
                // Get the data type to be returned.
                data_type = record_fields[index];
            } else {
                // Get the data type to be returned from the last record field.
                data_type = record_fields.back();
            }
        } else {
            // When we initialized buffers we have already checked that
            // the number of these buffers is equal to number of option
            // fields in the record so the condition below should be met.
            isc_throw_assert(index < record_fields.size());
            // Get the data type to be returned.
            data_type = record_fields[index];
        }
    }

    if (OptionDataTypeTraits<T>::type != data_type) {
        isc_throw(isc::dhcp::InvalidDataType,
                  "specified data type " << data_type << " does not"
                  " match the data type in an option definition for field"
                  " index " << index);
    }
}
} // namespace isc::dhcp
} // namespace isc

#endif // OPTION_CUSTOM_H
