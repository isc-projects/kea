// Copyright (C) 2010  Internet Systems Consortium, Inc. ("ISC")
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

// $Id$

#ifndef __MESSAGE_H
#define __MESSAGE_H

/// \brief Log Message
///
/// This class represents a message in which information about a logging event
/// is encoded.  This is invisible to the author of code doing logging unless
/// they are planning on writing an Appender.

class Message {
public:

    // The following is a placeholder.  It will be replaced with a finer-
    // grained time definition during implementation.
    typedef time_t  Time;   ///< To be replaced with a finer-grained time later

    // Constructor/destructor stll to be determined

    /// \brief Return Timestamp
    ///
    /// \return Timestamp associated with the message.
    Time getTimestamp() const;

    /// \brief Return Source
    ///
    /// \return Returns the source of the message.  This is a "."-separated
    /// string containing the hierarchy of the logger than generated this
    /// message.
    std::string getSource() const;

    /// \brief Return ID
    ///
    /// \return Returns the ID of the message, a 32-bit integer.
    uint32_t getId() const;

    /// \brief Return Parameters
    ///
    /// \return The parameters of the message in the form of a vector of
    /// strings.  Numeric parameters have been converted to strings and
    /// included in the message.
    std::vector<std::string> getParameters() const;

    /// \brief Return Encoded Message
    ///
    /// The contents of the message are encoded as a string in the form
    ///
    /// <message ID><'\0'><param 1><'\0'>...
    ///
    /// Some Appenders may find this format useful, so the ability to retrieve
    /// it directly is provided.
    std::string getRawMessage() const;
};



#endif // __MESSAGE_H
