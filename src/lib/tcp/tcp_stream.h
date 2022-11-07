// Copyright (C) 2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef TCP_STREAM_H
#define TCP_STREAM_H

#include <tcp/tcp_connection.h>
#include <boost/shared_ptr.hpp>

#include <array>
#include <functional>
#include <string>

namespace isc {
namespace tcp {

/// @brief Implement a simple length:data input stream message.
///
/// This class can be used to receive a single message from a TCP
/// stream where the message consists of a 16-bit unsigned length (in
/// network order), followed by that number of bytes of data.
class TcpStreamRequest : public TcpRequest {
public:
    /// @brief Constructor.
    TcpStreamRequest()
     : expected_size_(0) {};

    /// @brief Destructor
    virtual ~TcpStreamRequest(){};

    /// @brief Adds data to an incomplete request
    ///
    /// @param buf A pointer to the buffer holding the data.
    /// @param nbytes Size of the data within the buffer.
    /// @return number of bytes posted (consumed)
    virtual size_t postBuffer(const void* buf, const size_t nbytes);

    /// @brief Returns true if the request is incomplete.
    ///
    /// @return true if the request is incomplete.
    virtual bool needData() const;

    /// @brief Returns request contents formatted for log output
    ///
    /// @param limit Maximum length of the buffer to be output. If the limit
    /// is 0, the length of the output is unlimited.
    /// @return Textual representation of the input buffer.
    virtual std::string logFormatRequest(const size_t limit = 0) const;

    /// @brief Unpacks the wire data into a string request.
    virtual void unpack();

    /// @brief Fetches the unpacked string request.
    std::string getRequest() const {
        return(request_);
    };

protected:
    /// @brief Unpacked request string.
    std::string request_;

private:
    /// @brief Expected size of the current message.
    size_t expected_size_;
};

/// @brief Pointer to a TcpStreamRequest.
typedef boost::shared_ptr<TcpStreamRequest> TcpStreamRequestPtr;

/// @brief Implements a simple length:data output stream message.
///
/// This class can be used to send a single message on a TCP
/// stream where the message consists of a 16-bit unsigned length (in
/// network order), followed by that number of bytes of data.
class TcpStreamResponse : public TcpResponse {
public:
    /// @brief Constructor.
    TcpStreamResponse() {};

    /// @brief Destructor.
    virtual ~TcpStreamResponse() {};

    /// @brief Replaces the response content.
    ///
    /// @param response New contents for the output buffer.
    virtual void setResponseData(const std::string& response);

    /// @brief Appends data to the response content.
    ///
    /// @param response New contents for the output buffer.
    virtual void appendResponseData(const std::string& response);

    /// @brief Packs the response content into wire data buffer.
    virtual void pack();

private:
    /// @brief Unpacked response data to send.
    std::string response_;
};

/// @brief Pointer to a TcpStreamResponse.
typedef boost::shared_ptr<TcpStreamResponse> TcpStreamResponsePtr;

} // end of namespace isc::tcp
} // end of namespace isc

#endif  // TCP_STREAM_H
