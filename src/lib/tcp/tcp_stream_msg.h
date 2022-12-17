// Copyright (C) 2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef TCP_STREAM_MSG_H
#define TCP_STREAM_MSG_H

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
    TcpStreamRequest() : expected_size_(0) {
    }

    /// @brief Destructor
    virtual ~TcpStreamRequest() {
    }

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

    /// @brief Returns size of the unpacked request.
    size_t getRequestSize() const {
        return (request_.size());
    }

    /// @brief Returns pointer to the first byte of the unpacked request data.
    ///
    /// @return Constant raw pointer to the data.
    /// @throw InvalidOperation if request data is empty (i.e. getRequestSize() == 0).
    const uint8_t* getRequest() const {
        if (request_.empty()) {
            isc_throw(InvalidOperation, "TcpStreamRequest::getRequest()"
                                        " - cannot access empty request");
        }

        return (request_.data());
    }

    /// @brief Fetches the unpacked request as a string.
    ///
    /// @return String containing the unpacked contents.
    std::string getRequestString() const {
        return (std::string(request_.begin(), request_.end()));
    };

protected:
    /// @brief Unpacked request content
    std::vector<uint8_t> request_;

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

    /// @brief Replaces the response content .
    ///
    /// @param data New contents for the output buffer.
    /// @param length Length of the contents to add.
    virtual void setResponseData(const uint8_t* data, size_t length);

    /// @brief Appends a data to the response content.
    ///
    /// @param data Data to append to the response.
    /// @param length Length of the contents to add.
    virtual void appendResponseData(const uint8_t* data, size_t length);

    /// @brief Replaces the response content from a string.
    ///
    /// @param str New contents for the output buffer.
    virtual void setResponseData(const std::string& str);

    /// @brief Appends a string to the response content.
    ///
    /// @param str contents to add to the output buffer.
    virtual void appendResponseData(const std::string& str);

    /// @brief Packs the response content into wire data buffer.
    virtual void pack();

    /// @brief Fetches the unpacked response as a string.
    ///
    /// @return String containing the unpacked contents.
    std::string getResponseString() const {
        return (std::string(response_.begin(), response_.end()));
    };

private:
    /// @brief Unpacked response data to send.
    std::vector<uint8_t> response_;

};

/// @brief Pointer to a TcpStreamResponse.
typedef boost::shared_ptr<TcpStreamResponse> TcpStreamResponsePtr;

} // end of namespace isc::tcp
} // end of namespace isc

#endif  // TCP_STREAM_MSG_H
