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

    virtual void unpack();

    std::string getRequest() const {
        return(request_);
    };

protected:
    std::string request_;

private:
    /// @brief Expected size of the current message.
    size_t expected_size_;
};

typedef boost::shared_ptr<TcpStreamRequest> TcpStreamRequestPtr;

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
    std::string response_;
};

typedef boost::shared_ptr<TcpStreamResponse> TcpStreamResponsePtr;

} // end of namespace isc::tcp
} // end of namespace isc

#endif  // TCP_STREAM_H
