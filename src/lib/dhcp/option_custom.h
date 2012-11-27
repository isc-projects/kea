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

    class OptionFieldBuffer {
    public:
        OptionFieldBuffer(OptionDataType type,
                          const OptionBuffer& buf)
            : type_(type), buf_(buf) {
        }

        const OptionBuffer& getBuffer() const {
            return (buf_);
        }

        OptionDataType getType() const {
            return (type_);
        }

    private:
        OptionDataType type_;
        OptionBuffer buf_;
    };

    /// @brief Constructor, used for options to be sent.
    ///
    /// @param u specifies universe (V4 or V6).
    /// @param def option definition.
    /// @param data content of the option.
    OptionCustom(const OptionDefinition& def, Universe u, const OptionBuffer& data);

    /// @brief Constructor, used for received options.
    ///
    /// @param u specifies universe (V4 or V6).
    /// @param def option definition.
    /// @param first iterator to the first element that should be copied.
    /// @param last iterator to the next element after the last one
    /// to be copied.
    OptionCustom(const OptionDefinition& def, Universe u,
                 OptionBufferConstIter first, OptionBufferConstIter last);

    void readAddress(const uint32_t index, asiolink::IOAddress& address) const;

    const OptionBuffer& readBinary(const uint32_t index) const;

    bool readBoolean(const uint32_t index) const;

    template<typename T>
    T readInteger(const uint32_t index) const {
        checkIndex(index);

        if (!OptionDataTypeTraits<T>::integer_type) {
            isc_throw(isc::dhcp::InvalidDataType, "specified data type to be returned"
                      " by readInteger is not supported integer type");
        }

        OptionDataType data_type = definition_.getType();
        if (data_type == OPT_RECORD_TYPE) {
            const OptionDefinition::RecordFieldsCollection& record_fields =
                definition_.getRecordFields();
            assert(index < record_fields.size());
            data_type = record_fields[index];
        }

        if (OptionDataTypeTraits<T>::type != data_type) {
            isc_throw(isc::dhcp::InvalidDataType,
                      "unable to read option field with index " << index
                      << " as integer value. The field's data type"
                      << data_type << " does not match the integer type"
                      << "returned by the readInteger function.");
        }
        assert(buffers_[index].size() == OptionDataTypeTraits<T>::len);
        return (OptionDataTypeUtil::readInt<T>(buffers_[index]));
    }

    void readString(const uint32_t index, std::string& value) const;

    /// @brief Parses received buffer.
    ///
    /// @param begin iterator to first byte of option data
    /// @param end iterator to end of option data (first byte after option end)
    virtual void unpack(OptionBufferConstIter begin,
                        OptionBufferConstIter end);

    /// Returns string representation of the option.
    ///
    /// @param indent number of spaces before printed text.
    ///
    /// @return string with text representation.
    virtual std::string toText(int indent = 0);

    /// Returns length of the complete option (data length + DHCPv4/DHCPv6
    /// option header)
    ///
    /// @return length of the option
    virtual uint16_t len();

    /// Check if option is valid.
    ///
    /// @return true, if option is valid.
    virtual bool valid();

    /// Returns pointer to actual data.
    ///
    /// @return pointer to actual data (or reference to an empty vector
    /// if there is no data).
    virtual const OptionBuffer& getData() { return (data_); }

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
    /// @throw isc::OutOfRange if index is out of range.
    void checkIndex(const uint32_t index) const;

    /// @brief Create collection of buffers representing data field values.
    void createBuffers();

    OptionDefinition definition_;

    std::vector<OptionBuffer> buffers_;
};

} // namespace isc::dhcp
} // namespace isc

#endif // OPTION_CUSTOM_H
