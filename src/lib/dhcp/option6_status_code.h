// Copyright (C) 2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef OPTION6_STATUS_CODE_H
#define OPTION6_STATUS_CODE_H

#include <dhcp/option.h>
#include <boost/shared_ptr.hpp>
#include <stdint.h>
#include <string>

namespace isc {
namespace dhcp {

class Option6StatusCode;

/// @brief Pointer to the @c isc::dhcp::Option6StatusCode.
typedef boost::shared_ptr<Option6StatusCode> Option6StatusCodePtr;

/// @brief This class represents Status Code option (13) from RFC3315.
class Option6StatusCode: public Option {
public:
    /// @brief Constructor, used for options constructed (during transmission).
    ///
    /// @param status_code Numeric status code, e.g. STATUS_NoAddrsAvail.
    /// @param status_message Textual message for the statuscode.
    Option6StatusCode(const uint16_t status_code, const std::string& status_message);

    /// @brief Constructor, used for received options.
    ///
    /// @throw OutOfRange if specified option is truncated
    ///
    /// @param begin Iterator to first byte of option data
    /// @param end Iterator to end of option data (first byte after option end).
    Option6StatusCode(OptionBufferConstIter begin, OptionBufferConstIter end);

    /// @brief Writes option in wire-format.
    ///
    /// Writes option in wire-format to buf, returns pointer to first unused
    /// byte after stored option.
    ///
    /// @param [out] buf Pointer to the output buffer.
    virtual void pack(isc::util::OutputBuffer& buf);

    /// @brief Parses received buffer.
    ///
    /// @param begin Iterator to first byte of option data
    /// @param end Iterator to end of option data (first byte after option end)
    virtual void unpack(OptionBufferConstIter begin, OptionBufferConstIter end);

    /// @brief Returns total length of the option.
    ///
    /// The returned length is a sum of the option header and data fields.
    virtual uint16_t len();

    /// @brief Returns textual representation of the option.
    ///
    /// @param indent Number of spaces before printing text.
    virtual std::string toText(int indent = 0);

    /// @brief Returns textual representation of the option data.
    ///
    /// This method returns only the status code and the status
    /// message. It excludes the option header.
    std::string dataToText() const;

    /// @brief Returns numeric status code.
    uint16_t getStatusCode() const {
        return (status_code_);        
    }

    /// @brief Returns the name of the status code.
    std::string getStatusCodeName() const;

    /// @brief Sets new numeric status code.
    ///
    /// @param status_code New numeric status code.
    void setStatusCode(const uint16_t status_code) {
        status_code_ = status_code;
    }

    /// @brief Returns status message.
    const std::string& getStatusMessage() const {
        return (status_message_);
    }

    /// @brief Sets new status message.
    ///
    /// @param status_message New status message (empty string is allowed).
    void setStatusMessage(const std::string& status_message) {
        status_message_ = status_message;
    }

private:

    /// @brief Numeric status code.
    uint16_t status_code_;

    /// @brief Textual message.
    std::string status_message_;

};

} // isc::dhcp namespace
} // isc namespace

#endif // OPTION6_STATUS_CODE_H
