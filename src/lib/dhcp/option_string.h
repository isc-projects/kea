// Copyright (C) 2013 Internet Systems Consortium, Inc. ("ISC")
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

#ifndef OPTION_STRING_H
#define OPTION_STRING_H

#include <dhcp/option.h>
#include <util/buffer.h>

#include <boost/shared_ptr.hpp>
#include <string>

namespace isc {
namespace dhcp {

/// @brief Class which represents an option carrying a single string value.
///
/// This class represents an option carrying a single string value.
/// Currently this class imposes that the minimal length of the carried
/// string is 1.
class OptionString : public Option {
public:

    /// @brief Constructor, used to create options to be sent.
    ///
    /// This constructor creates an instance of option which carries a
    /// string value specified as constructor's parameter. This constructor
    /// is most often used to create an instance of an option which will
    /// be sent in the outgoing packet.
    ///
    /// @param u universe (V4 or V6).
    /// @param type option code.
    /// @param value a string value to be carried by the option.
    ///
    /// @throw isc::OutOfRange if provided string is empty.
    OptionString(const Option::Universe u, const uint16_t type,
                 const std::string& value);

    /// @brief Constructor, used for receiving options.
    ///
    /// This constructor creates an instance of the option from the provided
    /// chunk of buffer. This buffer may hold the data received on the wire.
    ///
    /// @param u universe (V4 or V6).
    /// @param type option code.
    /// @param begin iterator pointing to the first byte of the buffer chunk.
    /// @param end iterator pointing to the last byte of the buffer chunk.
    ///
    /// @throw isc::OutOfRange if provided buffer is truncated.
    OptionString(const Option::Universe u, const uint16_t type,
                 OptionBufferConstIter begin, OptionBufferConstIter end);

    /// @brief Returns length of the whole option, including header.
    ///
    /// @return length of the whole option.
    virtual uint16_t len();

    /// @brief Returns the string value held by the option.
    ///
    /// @return string value held by the option.
    std::string getValue() const {
        return (value_);
    }

    /// @brief Sets the string value to be held by the option.
    void setValue(const std::string& value) {
        value_ = value;
    }

    /// @brief Creates on-wire format of the option.
    ///
    /// This function creates on-wire format of the option and appends it to
    /// the data existing in the provided buffer. The internal buffer's pointer
    /// is moved to the end of stored data.
    ///
    /// @param [out] buf output buffer where the option will be stored.
    virtual void pack(isc::util::OutputBuffer& buf);

    /// @brief Decodes option data from the provided buffer.
    ///
    /// This function decodes option data from the provided buffer. Note that
    /// it does not decode the option code and length, so the iterators must
    /// point to the begining and end of the option payload respectively.
    /// The size of the decoded payload must be at least 1 byte.
    ///
    /// @param begin the iterator pointing to the option payload.
    /// @param end the iterator pointing to the end of the option payload.
    ///
    /// @throw isc::OutOfRange if provided buffer is truncated.
    virtual void unpack(OptionBufferConstIter begin, OptionBufferConstIter end);

private:
    /// String value being held by the option.
    std::string value_;

    // Change scope of the getData function to private as we want
    // getValue is called instead.
    using Option::getData;

};

/// Pointer to the OptionString object.
typedef boost::shared_ptr<OptionString> OptionStringPtr;

} // namespace isc::dhcp
} // namespace isc

#endif // OPTION_STRING_H
