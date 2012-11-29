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

#ifndef OPTION_CUSTOM_H
#define OPTION_CUSTOM_H

#include <dhcp/option.h>
#include <dhcp/option_definition.h>
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
    asiolink::IOAddress readAddress(const uint32_t index) const;

    /// @brief Read a buffer as binary data.
    ///
    /// @param index buffer index.
    ///
    /// @throw isc::OutOfRange if index is out of range.
    /// @return read buffer holding binary data.
    const OptionBuffer& readBinary(const uint32_t index) const;

    /// @brief Read a buffer as boolean value.
    ///
    /// @param index buffer index.
    ///
    /// @throw isc::OutOfRange if index is out of range.
    /// @return read boolean value.
    bool readBoolean(const uint32_t index) const;

    /// @brief Read a buffer as FQDN.
    ///
    /// @param index buffer index.
    /// @param [out] len number of bytes read from a buffer.
    ///
    /// @throw isc::OutOfRange if buffer index is out of range.
    /// @throw isc::dhcp::BadDataTypeCast if a buffer being read
    /// does not hold a valid FQDN.
    /// @return string representation if FQDN.
    std::string readFqdn(const uint32_t index) const;

    /// @brief Read a buffer as integer value.
    ///
    /// @param index buffer index.
    /// @tparam integer type of a value being returned.
    ///
    /// @throw isc::OutOfRange if index is out of range.
    /// @return read integer value.
    template<typename T>
    T readInteger(const uint32_t index) const {
        checkIndex(index);

        // Check that the requested return type is a supported integer.
        if (!OptionDataTypeTraits<T>::integer_type) {
            isc_throw(isc::dhcp::InvalidDataType, "specified data type to be returned"
                      " by readInteger is not supported integer type");
        }

        // Get the option definition type.
        OptionDataType data_type = definition_.getType();
        if (data_type == OPT_RECORD_TYPE) {
            const OptionDefinition::RecordFieldsCollection& record_fields =
                definition_.getRecordFields();
            // When we initialized buffers we have already checked that
            // the number of these buffers is equal to number of option
            // fields in the record so the condition below should be met.
            assert(index < record_fields.size());
            // Get the data type to be returned.
            data_type = record_fields[index];
        }

        // Requested data type must match the data type in a record.
        if (OptionDataTypeTraits<T>::type != data_type) {
            isc_throw(isc::dhcp::InvalidDataType,
                      "unable to read option field with index " << index
                      << " as integer value. The field's data type"
                      << data_type << " does not match the integer type"
                      << "returned by the readInteger function.");
        }
        // When we created the buffer we have checked that it has a
        // valid size so this condition here should be always fulfiled.
        assert(buffers_[index].size() == OptionDataTypeTraits<T>::len);
        // Read an integer value.
        return (OptionDataTypeUtil::readInt<T>(buffers_[index]));
    }

    /// @brief Read a buffer as string value.
    ///
    /// @param index buffer index.
    ///
    /// @return string value read from buffer.
    /// @throw isc::OutOfRange if index is out of range.
    std::string readString(const uint32_t index) const;

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
    virtual std::string toText(int indent = 0);

    /// @brief Returns length of the complete option (data length +
    ///        DHCPv4/DHCPv6 option header)
    ///
    /// @return length of the option
    virtual uint16_t len();

    /// @brief Sets content of this option from buffer.
    ///
    /// Option will be resized to length of buffer.
    ///
    /// @param first iterator pointing begining of buffer to copy.
    /// @param last iterator pointing to end of buffer to copy.
    void setData(const OptionBufferConstIter first,
                 const OptionBufferConstIter last);

protected:

    /// @brief Writes DHCPv4 option in a wire format to a buffer.
    ///
    /// @param buf output buffer (option will be stored there).
    virtual void pack4(isc::util::OutputBuffer& buf);

    /// @brief Writes DHCPv6 option in a wire format to a buffer.
    ///
    /// @param buf output buffer (built options will be stored here)
    virtual void pack6(isc::util::OutputBuffer& buf);

private:

    /// @brief Check if data field index is valid.
    ///
    /// @param index Data field index to check.
    ///
    /// @throw isc::OutOfRange if index is out of range.
    void checkIndex(const uint32_t index) const;

    /// @brief Create collection of buffers representing data field values.
    void createBuffers();

    /// @brief Return a text representation of a data field.
    ///
    /// @param data_type data type of a field.
    /// @param index data field buffer index within a custom option.
    ///
    /// @return text representation of a data field.
    std::string dataFieldToText(const OptionDataType data_type,
                                const uint32_t index) const;

    /// Option definition used to create an option.
    OptionDefinition definition_;

    /// The collection of buffers holding data for option fields.
    /// The order of buffers corresponds to the order of option
    /// fields.
    std::vector<OptionBuffer> buffers_;
};

} // namespace isc::dhcp
} // namespace isc

#endif // OPTION_CUSTOM_H
