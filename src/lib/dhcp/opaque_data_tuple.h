// Copyright (C) 2014-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef OPAQUE_DATA_TUPLE_H
#define OPAQUE_DATA_TUPLE_H

#include <dhcp/option.h>
#include <util/buffer.h>
#include <util/io_utilities.h>

#include <iostream>
#include <iterator>
#include <string>
#include <vector>

namespace isc {
namespace dhcp {

/// @brief Exception to be thrown when the operation on @c OpaqueDataTuple
/// object results in an error.
class OpaqueDataTupleError : public Exception {
public:
    OpaqueDataTupleError(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) { };
};


/// @brief Represents a single instance of the opaque data preceded by length.
///
/// Some of the DHCP options, such as Vendor Class option (16) in DHCPv6 or
/// V-I Vendor Class option (124) in DHCPv4 may carry multiple pairs of
/// opaque-data preceded by its length. Such pairs are called tuples. This class
/// represents a single instance of the tuple in the DHCPv4 or DHCPv6 option.
///
/// Although, the primary purpose of this class is to represent data tuples in
/// Vendor Class options, there may be other options defined in the future that
/// may have similar structure and this class can be used to represent the data
/// tuples in these new options too.
///
/// This class exposes a set of convenience methods to assign and retrieve the
/// opaque data from the tuple. It also implements a method to render the tuple
/// data into a wire format, as well as a method to create an instance of the
/// tuple from the wire format.
class OpaqueDataTuple {
public:

    /// @brief Size of the length field in the tuple.
    ///
    /// In the wire format, the tuple consists of the two fields: one holding
    /// a length of the opaque data size, second holding opaque data. The first
    /// field's size may be equal to 1 or 2 bytes. Usually, the tuples carried
    /// in the DHCPv6 options have 2 byte long length fields, the tuples carried
    /// in DHCPv4 options have 1 byte long length fields.
    enum LengthFieldType {
        LENGTH_EMPTY = -1,
        LENGTH_1_BYTE,
        LENGTH_2_BYTES
    };

    /// @brief Defines a type of the data buffer used to hold the opaque data.
    using Buffer = std::vector<uint8_t>;
    using InputIterator = Buffer::const_iterator;

    /// @brief Default constructor.
    ///
    /// @param length_field_type Indicates a length of the field which holds
    /// the size of the tuple.
    OpaqueDataTuple(LengthFieldType length_field_type);

    /// @brief Constructor
    ///
    /// Creates a tuple from on-wire data. It calls @c OpaqueDataTuple::unpack
    /// internally.
    ///
    /// @param length_field_type Indicates the length of the field holding the
    /// opaque data size.
    /// @param begin Iterator pointing to the beginning of the buffer holding
    /// wire data.
    /// @param end Iterator pointing to the end of the buffer holding wire data.
    /// @throw It may throw an exception if the @c unpack throws.
    OpaqueDataTuple(LengthFieldType length_field_type,
                    InputIterator begin,
                    InputIterator end)
        : length_field_type_(length_field_type) {
        unpack(begin, end);
    }

    /// @brief Appends data to the tuple.
    ///
    /// This function appends the data of the specified length to the tuple.
    /// If the specified buffer length is greater than the size of the buffer,
    /// the behavior of this function is undefined.
    ///
    /// @param data Iterator pointing to the beginning of the buffer being
    /// appended. The source buffer may be an STL object or an array of
    /// characters. In the latter case, the pointer to the beginning of this
    /// array should be passed.
    /// @param len Length of the source buffer.
    /// @tparam InputIterator Type of the iterator pointing to the beginning of
    /// the source buffer.
    void append(const char* data, const size_t len) {
        data_.insert(data_.end(), data, data + len);
    }
    void append(InputIterator data, const size_t len) {
        data_.insert(data_.end(), data, data + len);
    }

    /// @brief Appends string to the tuple.
    ///
    /// In most cases, the tuple will carry a string. This function appends the
    /// string to the tuple.
    ///
    /// @param text String to be appended in the tuple.
    void append(const std::string& text);

    /// @brief Assigns data to the tuple.
    ///
    /// This function replaces existing data in the tuple with the new data.
    /// If the specified buffer length is greater than the size of the buffer,
    /// the behavior of this function is undefined.
    /// @param data Iterator pointing to the beginning of the buffer being
    /// assigned. The source buffer may be an STL object or an array of
    /// characters. In the latter case, the pointer to the beginning of this
    /// array should be passed.
    /// @param len Length of the source buffer.
    void assign(const char* data, const size_t len) {
        data_.assign(data, data + len);
    }
    void assign(InputIterator data, const size_t len) {
        data_.assign(data, data + len);
    }

    /// @brief Assigns string data to the tuple.
    ///
    /// In most cases, the tuple will carry a string. This function sets the
    /// string to the tuple.
    ///
    /// @param text String to be assigned to the tuple.
    void assign(const std::string& text);

    /// @brief Removes the contents of the tuple.
    void clear();

    /// @brief Checks if the data carried in the tuple match the string.
    ///
    /// @param other String to compare tuple data against.
    bool equals(const std::string& other) const;

    /// @brief Returns tuple length data field type.
    LengthFieldType getLengthFieldType() const {
        return (length_field_type_);
    }

    /// @brief Returns the length of the data in the tuple.
    size_t getLength() const {
        return (data_.size());
    }

    /// @brief Returns a total size of the tuple, including length field.
    size_t getTotalLength() const {
        return (getDataFieldSize() + getLength());
    }

    /// @brief Returns a reference to the buffer holding tuple data.
    ///
    /// @warning The returned reference is valid only within the lifetime
    /// of the object which returned it. The use of the returned reference
    /// after the object has been destroyed yelds undefined behavior.
    const Buffer& getData() const {
        return (data_);
    }

    /// @brief Return the tuple data in the textual format.
    std::string getText() const;

    /// @brief Renders the tuple to a buffer in the wire format.
    ///
    /// This function creates the following wire representation of the tuple:
    /// - 1 or 2 bytes holding a length of the data.
    /// - variable number of bytes holding data.
    /// and writes it to the specified buffer. The new are appended to the
    /// buffer, so as data existing in the buffer is preserved.
    ///
    /// The tuple is considered malformed if one of the following occurs:
    /// - the size of the data is 0 (tuple is empty),
    /// - the size of the data is greater than 255 and the size of the length
    /// field is 1 byte (see @c LengthFieldType).
    /// - the size of the data is greater than 65535 and the size of the length
    /// field is 2 bytes (see @c LengthFieldType).
    ///
    /// Function will throw an exception if trying to render malformed tuple.
    ///
    /// @param [out] buf Buffer to which the data is rendered.
    ///
    /// @throw OpaqueDataTupleError if failed to render the data to the
    /// buffer because the tuple is malformed.
    void pack(isc::util::OutputBuffer& buf) const;

    /// @brief Parses wire data and creates a tuple from it.
    ///
    /// This function parses on-wire data stored in the provided buffer and
    /// stores it in the tuple object. The wire data must include at least the
    /// data field of the length matching the specified @c LengthFieldType.
    /// The remaining buffer length (excluding the length field) must be equal
    /// or greater than the length carried in the length field. If any of these
    /// two conditions is not met, an exception is thrown.
    ///
    /// This function allows opaque data with the length of 0.
    ///
    /// @param begin Iterator pointing to the beginning of the buffer holding
    /// wire data.
    /// @param end Iterator pointing to the end of the buffer holding wire data.
    /// @tparam InputIterator Type of the iterators passed to this function.
    void unpack(InputIterator begin, InputIterator end);

    /// @name Assignment and comparison operators.
    //{@

    /// @brief Assignment operator.
    ///
    /// This operator assigns the string data to the tuple.
    ///
    /// @param other string to be assigned to the tuple.
    /// @return Tuple object after assignment.
    OpaqueDataTuple& operator=(const std::string& other);

    /// @brief Equality operator.
    ///
    /// This operator compares the string given as an argument to the data
    /// carried in the tuple in the textual format.
    ///
    /// @param other String to compare the tuple against.
    /// @return true if data carried in the tuple is equal to the string.
    bool operator==(const std::string& other) const;

    /// @brief Inequality operator.
    ///
    /// This operator compares the string given as an argument to the data
    /// carried in the tuple for inequality.
    ///
    /// @param other String to compare the tuple against.
    /// @return true if the data carried in the tuple is unequal the given
    /// string.
    bool operator!=(const std::string& other);
    //@}

    /// @brief Returns the size of the tuple length field.
    ///
    /// The returned value depends on the @c LengthFieldType set for the tuple.
    int getDataFieldSize() const;

private:

    /// @brief Buffer which holds the opaque tuple data.
    Buffer data_;

    /// @brief Holds a type of tuple size field (1 byte long or 2 bytes long).
    LengthFieldType length_field_type_;
};

/// @brief Pointer to the @c OpaqueDataTuple object.
typedef boost::shared_ptr<OpaqueDataTuple> OpaqueDataTuplePtr;

/// @brief Inserts the @c OpaqueDataTuple as a string into stream.
///
/// This operator gets the tuple data in the textual format and inserts it
/// into the output stream.
///
/// @param os Stream object on which insertion is performed.
/// @param tuple Object encapsulating a tuple which data in the textual format
/// is inserted into the stream.
/// @return Reference to the same stream but after insertion operation.
std::ostream& operator<<(std::ostream& os, const OpaqueDataTuple& tuple);

/// @brief Inserts data carried in the stream into the tuple.
///
/// this operator inserts data carried in the input stream and inserts it to
/// the @c OpaqueDataTuple object. The existing data is replaced with new data.
///
/// @param is Input stream from which the data will be inserted.
/// @param tuple @c OpaqueDataTuple object to which the data will be inserted.
/// @return Input stream after insertion to the tuple is performed.
std::istream& operator>>(std::istream& is, OpaqueDataTuple& tuple);

} // namespace isc::dhcp
} // namespace isc

#endif
