// Copyright (C) 2013-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

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
/// string is 1.  Per RFC 2132, Sec 2 trailing NULLs are trimmed during
/// either construction or unpacking.
///
/// @todo In the future this class may be extended with some more string
/// content checks and encoding methods if required.
class OptionString : public Option {
public:

    /// @brief Constructor, used to create options to be sent.
    ///
    /// This constructor creates an instance of option which carries a
    /// string value specified as constructor's parameter. This constructor
    /// is most often used to create an instance of an option which will
    /// be sent in the outgoing packet.  Trailing NULLs will be trimmed.
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
    /// Trailing NULLs will be trimmed.
    ///
    /// @param u universe (V4 or V6).
    /// @param type option code.
    /// @param begin iterator pointing to the first byte of the buffer chunk.
    /// @param end iterator pointing to the last byte of the buffer chunk.
    ///
    /// @throw isc::OutOfRange if provided buffer is truncated.
    OptionString(const Option::Universe u, const uint16_t type,
                 OptionBufferConstIter begin, OptionBufferConstIter end);

    /// @brief Copies this option and returns a pointer to the copy.
    OptionPtr clone() const;

    /// @brief Returns length of the whole option, including header.
    ///
    /// @return length of the whole option.
    virtual uint16_t len() const;

    /// @brief Returns the string value held by the option.
    ///
    /// @return string value held by the option.
    std::string getValue() const;

    /// @brief Sets the string value to be held by the option.
    ///
    /// Trailing NULLs will be trimmed.
    ///
    /// @param value string value to be set.
    ///
    /// @throw isc::OutOfRange if a string value to be set is empty.
    void setValue(const std::string& value);

    /// @brief Creates on-wire format of the option.
    ///
    /// This function creates on-wire format of the option and appends it to
    /// the data existing in the provided buffer. The internal buffer's pointer
    /// is moved to the end of stored data.
    ///
    /// @param [out] buf output buffer where the option will be stored.
    /// @param check if set to false, allows options larger than 255 for v4
    virtual void pack(isc::util::OutputBuffer& buf, bool check = true) const;

    /// @brief Decodes option data from the provided buffer.
    ///
    /// This function decodes option data from the provided buffer. Note that
    /// it does not decode the option code and length, so the iterators must
    /// point to the beginning and end of the option payload respectively.
    /// The size of the decoded payload must be at least 1 byte.
    /// Trailing NULLs will be trimmed.
    ///
    /// @param begin the iterator pointing to the option payload.
    /// @param end the iterator pointing to the end of the option payload.
    ///
    /// @throw isc::OutOfRange if provided buffer is truncated.
    virtual void unpack(OptionBufferConstIter begin, OptionBufferConstIter end);

    /// @brief Returns option information in the textual format.
    ///
    /// @param indent Number of space characters to be inserted before
    /// the text.
    ///
    /// @return Option information in the textual format.
    virtual std::string toText(int indent = 0) const;

    /// @brief Returns actual value of the option in string format.
    ///
    /// This method is used in client classification.
    /// @return Content of the option.
    virtual std::string toString() const;
};

/// Pointer to the OptionString object.
typedef boost::shared_ptr<OptionString> OptionStringPtr;

} // namespace isc::dhcp
} // namespace isc

#endif // OPTION_STRING_H
