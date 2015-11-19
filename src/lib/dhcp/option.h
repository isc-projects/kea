// Copyright (C) 2011-2015 Internet Systems Consortium, Inc. ("ISC")
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

#ifndef OPTION_H
#define OPTION_H

#include <util/buffer.h>

#include <boost/function.hpp>
#include <boost/shared_ptr.hpp>

#include <map>
#include <string>
#include <vector>

namespace isc {
namespace dhcp {

/// @brief buffer types used in DHCP code.
///
/// Dereferencing OptionBuffer iterator will point out to contiguous memory.
typedef std::vector<uint8_t> OptionBuffer;

/// iterator for walking over OptionBuffer
typedef OptionBuffer::iterator OptionBufferIter;

/// const_iterator for walking over OptionBuffer
typedef OptionBuffer::const_iterator OptionBufferConstIter;

/// pointer to a DHCP buffer
typedef boost::shared_ptr<OptionBuffer> OptionBufferPtr;

/// shared pointer to Option object
class Option;
typedef boost::shared_ptr<Option> OptionPtr;

/// A collection of DHCP (v4 or v6) options
typedef std::multimap<unsigned int, OptionPtr> OptionCollection;
/// A pointer to an OptionCollection
typedef boost::shared_ptr<OptionCollection> OptionCollectionPtr;

/// @brief This type describes a callback function to parse options from buffer.
///
/// @note The last two parameters should be specified in the callback function
/// parameters list only if DHCPv6 options are parsed. Exclude these parameters
/// from the callback function defined to parse DHCPv4 options.
///
/// @param buffer A buffer holding options to be parsed.
/// @param encapsulated_space A name of the option space to which options being
/// parsed belong.
/// @param [out] options A container to which parsed options should be appended.
/// @param relay_msg_offset A pointer to a size_t value. It indicates the
/// offset to beginning of relay_msg option. This parameter should be specified
/// for DHCPv6 options only.
/// @param relay_msg_len A pointer to a size_t value. It holds the length of
/// of the relay_msg option. This parameter should be specified for DHCPv6
/// options only.
///
/// @return An offset to the first byte after last parsed option.
typedef boost::function< size_t(const OptionBuffer& buffer,
                                const std::string encapsulated_space,
                                OptionCollection& options,
                                size_t* relay_msg_offset,
                                size_t* relay_msg_len)
                         > UnpackOptionsCallback;


class Option {
public:
    /// length of the usual DHCPv4 option header (there are exceptions)
    const static size_t OPTION4_HDR_LEN = 2;

    /// length of any DHCPv6 option header
    const static size_t OPTION6_HDR_LEN = 4;

    /// defines option universe DHCPv4 or DHCPv6
    enum Universe { V4, V6 };


    /// @brief a factory function prototype
    ///
    /// @param u option universe (DHCPv4 or DHCPv6)
    /// @param type option type
    /// @param buf pointer to a buffer
    ///
    /// @todo Passing a separate buffer for each option means that a copy
    ///       was done. We can avoid it by passing 2 iterators.
    ///
    /// @return a pointer to a created option object
    typedef OptionPtr Factory(Option::Universe u, uint16_t type, const OptionBuffer& buf);

    /// @brief Factory function to create instance of option.
    ///
    /// Factory method creates instance of specified option. The option
    /// to be created has to have corresponding factory function
    /// registered with \ref LibDHCP::OptionFactoryRegister.
    ///
    /// @param u universe of the option (V4 or V6)
    /// @param type option-type
    /// @param buf option-buffer
    ///
    /// @return instance of option.
    ///
    /// @throw isc::InvalidOperation if there is no factory function
    ///        registered for specified option type.
    static OptionPtr factory(Option::Universe u,
                             uint16_t type,
                             const OptionBuffer& buf);

    /// @brief Factory function to create instance of option.
    ///
    /// Factory method creates instance of specified option. The option
    /// to be created has to have corresponding factory function
    /// registered with \ref LibDHCP::OptionFactoryRegister.
    /// This method creates empty \ref OptionBuffer object. Use this
    /// factory function if it is not needed to pass custom buffer.
    ///
    /// @param u universe of the option (V4 or V6)
    /// @param type option-type
    ///
    /// @return instance of option.
    ///
    /// @throw isc::InvalidOperation if there is no factory function
    ///        registered for specified option type.
    static OptionPtr factory(Option::Universe u, uint16_t type) {
        return factory(u, type, OptionBuffer());
    }

    /// @brief ctor, used for options constructed, usually during transmission
    ///
    /// @param u option universe (DHCPv4 or DHCPv6)
    /// @param type option type
    Option(Universe u, uint16_t type);

    /// @brief Constructor, used for received options.
    ///
    /// This constructor takes vector<uint8_t>& which is used in cases
    /// when content of the option will be copied and stored within
    /// option object. V4 Options follow that approach already.
    /// @todo Migrate V6 options to that approach.
    ///
    /// @param u specifies universe (V4 or V6)
    /// @param type option type (0-255 for V4 and 0-65535 for V6)
    /// @param data content of the option
    Option(Universe u, uint16_t type, const OptionBuffer& data);

    /// @brief Constructor, used for received options.
    ///
    /// This constructor is similar to the previous one, but it does not take
    /// the whole vector<uint8_t>, but rather subset of it.
    ///
    /// @todo This can be templated to use different containers, not just
    /// vector. Prototype should look like this:
    /// template<typename InputIterator> Option(Universe u, uint16_t type,
    /// InputIterator first, InputIterator last);
    ///
    /// vector<int8_t> myData;
    /// Example usage: new Option(V4, 123, myData.begin()+1, myData.end()-1)
    /// This will create DHCPv4 option of type 123 that contains data from
    /// trimmed (first and last byte removed) myData vector.
    ///
    /// @param u specifies universe (V4 or V6)
    /// @param type option type (0-255 for V4 and 0-65535 for V6)
    /// @param first iterator to the first element that should be copied
    /// @param last iterator to the next element after the last one
    ///        to be copied.
    Option(Universe u, uint16_t type, OptionBufferConstIter first,
           OptionBufferConstIter last);

    /// @brief returns option universe (V4 or V6)
    ///
    /// @return universe type
    Universe  getUniverse() const { return universe_; };

    /// @brief Writes option in wire-format to a buffer.
    ///
    /// Writes option in wire-format to buffer, returns pointer to first unused
    /// byte after stored option (that is useful for writing options one after
    /// another).
    ///
    /// @param buf pointer to a buffer
    ///
    /// @throw BadValue Universe of the option is neither V4 nor V6.
    virtual void pack(isc::util::OutputBuffer& buf);

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
    virtual std::string toText(int indent = 0);

    /// @brief Returns string representation of the value
    ///
    /// This is terse repesentation used in cases where client classification
    /// refers to a specific option.
    ///
    /// @return string that represents the value of the option.
    virtual std::string toString();

    /// @brief Returns string containing hexadecimal representation of option.
    ///
    /// @param include_header Boolean flag which indicates if the output should
    /// also contain header fields. The default is that it shouldn't include
    /// header fields.
    ///
    /// @return String containing hexadecimal representation of the option.
    virtual std::string toHexString(const bool include_header = false);

    /// Returns option type (0-255 for DHCPv4, 0-65535 for DHCPv6)
    ///
    /// @return option type
    uint16_t getType() const { return (type_); }

    /// Returns length of the complete option (data length + DHCPv4/DHCPv6
    /// option header)
    ///
    /// @return length of the option
    virtual uint16_t len();

    /// @brief Returns length of header (2 for v4, 4 for v6)
    ///
    /// @return length of option header
    virtual uint16_t getHeaderLen();

    /// returns if option is valid (e.g. option may be truncated)
    ///
    /// @return true, if option is valid
    virtual bool valid();

    /// Returns pointer to actual data.
    ///
    /// @return pointer to actual data (or reference to an empty vector
    ///         if there is no data)
    virtual const OptionBuffer& getData() const { return (data_); }

    /// Adds a sub-option.
    ///
    /// Some DHCPv6 options can have suboptions. This method allows adding
    /// options within options.
    ///
    /// Note: option is passed by value. That is very convenient as it allows
    /// downcasting from any derived classes, e.g. shared_ptr<Option6_IA> type
    /// can be passed directly, without any casts. That would not be possible
    /// with passing by reference. addOption() is expected to be used in
    /// many places. Requiring casting is not feasible.
    ///
    /// @param opt shared pointer to a suboption that is going to be added.
    void addOption(OptionPtr opt);

    /// Returns shared_ptr to suboption of specific type
    ///
    /// @param type type of requested suboption
    ///
    /// @return shared_ptr to requested suoption
    OptionPtr getOption(uint16_t type);

    /// @brief Returns all encapsulated options.
    ///
    /// @warning This function returns a reference to the container holding
    /// encapsulated options, which is valid as long as the object which
    /// returned it exists.
    const OptionCollection& getOptions() const {
        return (options_);
    }

    /// Attempts to delete first suboption of requested type
    ///
    /// @param type Type of option to be deleted.
    ///
    /// @return true if option was deleted, false if no such option existed
    bool delOption(uint16_t type);

    /// @brief Returns content of first byte.
    ///
    /// @throw isc::OutOfRange Thrown if the option has a length of 0.
    ///
    /// @return value of the first byte
    uint8_t getUint8();

    /// @brief Returns content of first word.
    ///
    /// @throw isc::OutOfRange Thrown if the option has a length less than 2.
    ///
    /// @return uint16_t value stored on first two bytes
    uint16_t getUint16();

    /// @brief Returns content of first double word.
    ///
    /// @throw isc::OutOfRange Thrown if the option has a length less than 4.
    ///
    /// @return uint32_t value stored on first four bytes
    uint32_t getUint32();

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

    /// @brief Sets the name of the option space encapsulated by this option.
    ///
    /// @param encapsulated_space name of the option space encapsulated by
    /// this option.
    void setEncapsulatedSpace(const std::string& encapsulated_space) {
        encapsulated_space_ = encapsulated_space;
    }

    /// @brief Returns the name of the option space encapsulated by this option.
    ///
    /// @return name of the option space encapsulated by this option.
    std::string getEncapsulatedSpace() const {
        return (encapsulated_space_);
    }

    /// @brief Set callback function to be used to parse options.
    ///
    /// @param callback An instance of the callback function or NULL to
    /// uninstall callback.
    void setCallback(UnpackOptionsCallback callback) {
        callback_ = callback;
    }

    /// just to force that every option has virtual dtor
    virtual ~Option();

    /// @brief Checks if options are equal.
    ///
    /// This method calls a virtual @c equals function to compare objects.
    /// This method is not meant to be overriden in the derived classes.
    /// Instead, the other @c equals function must be overriden.
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
    /// on-wire format. The universe set for the particular option
    /// is used to determine whether option code and length are
    /// stored as 2-byte (for DHCPv6) or single-byte (for DHCPv4)
    /// values. For DHCPv4 options, this method checks if the
    /// length does not exceed 255 bytes and throws exception if
    /// it does.
    /// This method is used by derived classes to pack option's
    /// header into a buffer. This method should not be called
    /// directly by other classes.
    ///
    /// @param [out] buf output buffer.
    void packHeader(isc::util::OutputBuffer& buf);

    /// @brief Store sub options in a buffer.
    ///
    /// This method stores all sub-options defined for a particular
    /// option in a on-wire format in output buffer provided.
    /// This function is called by pack function in this class or
    /// derived classes that override pack.
    ///
    /// @param [out] buf output buffer.
    ///
    /// @todo The set of exceptions thrown by this function depend on
    /// exceptions thrown by pack methods invoked on objects
    /// representing sub options. We should consider whether to aggregate
    /// those into one exception which can be documented here.
    void packOptions(isc::util::OutputBuffer& buf);

    /// @brief Builds a collection of sub options from the buffer.
    ///
    /// This method parses the provided buffer and builds a collection
    /// of objects representing sub options. This function may throw
    /// different exceptions when option assembly fails.
    ///
    /// @param buf buffer to be parsed.
    ///
    /// @todo The set of exceptions thrown by this function depend on
    /// exceptions thrown by unpack methods invoked on objects
    /// representing sub options. We should consider whether to aggregate
    /// those into one exception which can be documented here.
    void unpackOptions(const OptionBuffer& buf);

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
                             const std::string& type_name = "");

    /// @brief Returns collection of suboptions in the textual format.
    ///
    /// This protected method should be called by the derived classes
    /// in their respective @c toText implementations to append the
    /// suboptions held by this option. Note that there are some
    /// option types which don't have suboptions because they contain
    /// variable length fields. For such options this method is not
    /// called.
    ///
    /// @param indent Number of spaces to insert before the text.
    ///
    //// @return Suboptions in the textual format.
    std::string suboptionsToText(const int indent = 0) const;

    /// @brief A protected method used for option correctness.
    ///
    /// It is used in constructors. In there are any problems detected
    /// (like specifying type > 255 for DHCPv4 option), it will throw
    /// BadValue or OutOfRange exceptions.
    void check();

    /// option universe (V4 or V6)
    Universe universe_;

    /// option type (0-255 for DHCPv4, 0-65535 for DHCPv6)
    uint16_t type_;

    /// contains content of this data
    OptionBuffer data_;

    /// collection for storing suboptions
    OptionCollection options_;

    /// Name of the option space being encapsulated by this option.
    std::string encapsulated_space_;

    /// A callback to be called to unpack options from the packet.
    UnpackOptionsCallback callback_;

    /// @todo probably 2 different containers have to be used for v4 (unique
    /// options) and v6 (options with the same type can repeat)
};

} // namespace isc::dhcp
} // namespace isc

#endif // OPTION_H
