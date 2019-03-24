// Copyright (C) 2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef ND_OPTION_H
#define ND_OPTION_H

#include <util/buffer.h>

#include <boost/function.hpp>
#include <boost/shared_ptr.hpp>

#include <map>
#include <string>
#include <vector>

namespace isc {
namespace slaac {

/// @brief buffer types used in ND code.
///
/// Dereferencing OptionBuffer iterator will point out to contiguous memory.
typedef std::vector<uint8_t> OptionBuffer;

/// iterator for walking over OptionBuffer
typedef OptionBuffer::iterator OptionBufferIter;

/// const_iterator for walking over OptionBuffer
typedef OptionBuffer::const_iterator OptionBufferConstIter;

/// pointer to a ND buffer
typedef boost::shared_ptr<OptionBuffer> OptionBufferPtr;

/// shared pointer to Option object
class Option;
typedef boost::shared_ptr<Option> OptionPtr;

/// A collection of ND options
typedef std::multimap<unsigned int, OptionPtr> OptionCollection;

/// A pointer to an OptionCollection
typedef boost::shared_ptr<OptionCollection> OptionCollectionPtr;

class Option {
public:
    /// length of the usual ND option header (there are exceptions)
    const static size_t OPTION_HDR_LEN = 2;

    /// @brief ctor, used for options constructed, usually during transmission
    ///
    /// @param type option type
    Option(uint8_t type);

    /// @brief Constructor, used for received options.
    ///
    /// This constructor takes vector<uint8_t>& which is used in cases
    /// when content of the option will be copied and stored within
    /// option object. V4 Options follow that approach already.
    /// @todo Migrate V6 options to that approach.
    ///
    /// @param type option type (0-255 for V4 and 0-65535 for V6)
    /// @param data content of the option
    Option(uint8_t type, const OptionBuffer& data);

    /// @brief Constructor, used for received options.
    ///
    /// This constructor is similar to the previous one, but it does not take
    /// the whole vector<uint8_t>, but rather subset of it.
    ///
    /// @todo This can be templated to use different containers, not just
    /// vector. Prototype should look like this:
    /// template<typename InputIterator> Option(uint8_t type,
    /// InputIterator first, InputIterator last);
    ///
    /// vector<int8_t> myData;
    /// Example usage: new Option(123, myData.begin()+1, myData.end()-1)
    /// This will create ND option of type 123 that contains data from
    /// trimmed (first and last byte removed) myData vector.
    ///
    /// @param type option type
    /// @param first iterator to the first element that should be copied
    /// @param last iterator to the next element after the last one
    ///        to be copied.
    Option(uint8_t type, OptionBufferConstIter first,
           OptionBufferConstIter last);

    /// @brief Copy constructor.
    ///
    /// This constructor makes a deep copy of the option and all of the
    /// suboptions. It calls @ref getOptionsCopy to deep copy suboptions.
    ///
    /// @param source Option to be copied.
    Option(const Option& source);

    /// @brief Assignment operator.
    ///
    /// The assignment operator performs a deep copy of the option and
    /// its suboptions. It calls @ref getOptionsCopy to deep copy
    /// suboptions.
    ///
    /// @param rhs Option to be assigned.
    Option& operator=(const Option& rhs);

    /// @brief Writes option in wire-format to a buffer.
    ///
    /// Writes option in wire-format to buffer, returns pointer to first unused
    /// byte after stored option (that is useful for writing options one after
    /// another).
    ///
    /// @param buf pointer to a buffer
    virtual void pack(isc::util::OutputBuffer& buf) const;

    /// @brief Parses received buffer.
    ///
    /// @param begin iterator to first byte of option data
    /// @param end iterator to end of option data (first byte after option end)
    virtual void unpack(OptionBufferConstIter begin,
                        OptionBufferConstIter end);

    /// Returns string representation of the option.
    ///
    /// @param indent number of spaces before printing text
    ///
    /// @return string with text representation.
    virtual std::string toText(int indent = 0) const;

    /// @brief Returns binary representation of the option.
    ///
    /// @param include_header Boolean flag which indicates if the output should
    /// also contain header fields. The default is that it shouldn't include
    /// header fields.
    ///
    /// @return Vector holding binary representation of the option.
    virtual std::vector<uint8_t> toBinary(const bool include_header = false) const;

    /// @brief Returns string containing hexadecimal representation of option.
    ///
    /// @param include_header Boolean flag which indicates if the output should
    /// also contain header fields. The default is that it shouldn't include
    /// header fields.
    ///
    /// @return String containing hexadecimal representation of the option.
    virtual std::string toHexString(const bool include_header = false) const;

    /// Returns option type
    ///
    /// @return option type
    uint8_t getType() const { return (type_); }

    /// Returns length of the complete option
    ///
    /// @return length of the option
    virtual size_t len() const;

    /// @brief Returns length of header (2 for ND)
    ///
    /// @return length of option header
    virtual size_t getHeaderLen() const;

    /// returns if option is valid (e.g. option may be truncated)
    ///
    /// @return true, if option is valid
    virtual bool valid() const;

    /// Returns pointer to actual data.
    ///
    /// @return pointer to actual data (or reference to an empty vector
    ///         if there is no data)
    virtual const OptionBuffer& getData() const { return (data_); }

    /// @brief Returns content of first byte.
    ///
    /// @throw isc::OutOfRange Thrown if the option has a length of 0.
    ///
    /// @return value of the first byte
    uint8_t getUint8() const;

    /// @brief Returns content of first word.
    ///
    /// @throw isc::OutOfRange Thrown if the option has a length less than 2.
    ///
    /// @return uint16_t value stored on first two bytes
    uint16_t getUint16() const;

    /// @brief Returns content of first double word.
    ///
    /// @throw isc::OutOfRange Thrown if the option has a length less than 4.
    ///
    /// @return uint32_t value stored on first four bytes
    uint32_t getUint32() const;

    /// @brief Sets content of this option to singe uint8 value.
    ///
    /// Option it resized appropriately (to length of 1 octet).
    ///
    /// @param value value to be set
    void setUint8(uint8_t value);

    /// @brief Sets content of this option to singe uint16 value.
    ///
    /// Option it resized appropriately (to length of 2 octets).
    ///
    /// @param value value to be set
    void setUint16(uint16_t value);

    /// @brief Sets content of this option to singe uint32 value.
    ///
    /// Option it resized appropriately (to length of 4 octets).
    ///
    /// @param value value to be set
    void setUint32(uint32_t value);

    /// @brief Sets content of this option from buffer.
    ///
    /// Option will be resized to length of buffer.
    ///
    /// @param first iterator pointing to beginning of buffer to copy.
    /// @param last iterator pointing to end of buffer to copy.
    ///
    /// @tparam InputIterator type of the iterator representing the
    /// limits of the buffer to be assigned to a data_ buffer.
    template<typename InputIterator>
    void setData(InputIterator first, InputIterator last) {
        data_.assign(first, last);
    }

    /// just to force that every option has virtual dtor
    virtual ~Option();

    /// @brief Checks if options are equal.
    ///
    /// This method calls a virtual @c equals function to compare objects.
    /// This method is not meant to be overridden in the derived classes.
    /// Instead, the other @c equals function must be overridden.
    ///
    /// @param other Pointer to the option to compare this option to.
    /// @return true if both options are equal, false otherwise.
    bool equals(const OptionPtr& other) const;

    /// @brief Checks if two options are equal.
    ///
    /// Equality verifies option type and option content. Care should
    /// be taken when using this method. Implementation for derived
    /// classes should be provided when this method is expected to be
    /// used. It is safe in general, as the first check (different types)
    /// will detect differences between base Option and derived
    /// objects.
    ///
    /// @param other Instance of the option to compare to.
    ///
    /// @return true if options are equal, false otherwise.
    virtual bool equals(const Option& other) const;

protected:

    /// @brief Store option's header in a buffer.
    ///
    /// This method writes option's header into a buffer in the
    /// on-wire format.
    /// This method is used by derived classes to pack option's
    /// header into a buffer. This method should not be called
    /// directly by other classes.
    ///
    /// @param [out] buf output buffer.
    void packHeader(isc::util::OutputBuffer& buf) const;

    /// @brief Returns option header in the textual format.
    ///
    /// This protected method should be called by the derived classes in
    /// their respective @c toText implementations.
    ///
    /// @param indent Number of spaces to insert before the text.
    /// @param type_name Option type name. If empty, the option name
    /// is omitted.
    ///
    /// @return Option header in the textual format.
    std::string headerToText(const int indent = 0,
                             const std::string& type_name = "") const;

    /// @brief A protected method used for option correctness.
    ///
    /// It is used in constructors. In there are any problems detected
    /// it will throw BadValue or OutOfRange exceptions.
    void check() const;

    /// option type (0-255 for ND)
    uint8_t type_;

    /// contains content of this data
    OptionBuffer data_;
};

} // namespace isc::slaac
} // namespace isc

#endif // ND_OPTION_H
