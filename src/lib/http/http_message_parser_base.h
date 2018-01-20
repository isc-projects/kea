// Copyright (C) 2017-2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef HTTP_MESSAGE_PARSER_BASE_H
#define HTTP_MESSAGE_PARSER_BASE_H

#include <exceptions/exceptions.h>
#include <http/http_message.h>
#include <util/state_model.h>
#include <boost/function.hpp>
#include <list>
#include <string>

namespace isc {
namespace http {

/// @brief Exception thrown when an error during parsing HTTP message
/// has occurred.
///
/// The most common errors are due to receiving malformed requests.
class HttpParseError : public Exception {
public:
    HttpParseError(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) { };
};

/// @brief Base class for the HTTP message parsers.
///
/// This is a base class for @c HttpRequestParser and @c HttpResponseParser
/// classes. It provides common states, events and functionality for processing
/// the received HTTP messages.
///
/// This class must not be used directly. Instead, an instance of the
/// derived class should be used.
///
/// HTTP uses TCP as a transport which is asynchronous in nature, i.e. the
/// HTTP message is received in chunks and multiple TCP connections can be
/// established at the same time. Multiplexing between these connections
/// requires providing a separate state machine per connection to "remember"
/// the state of each transaction when the parser is waiting for asynchronous
/// data to be delivered. While the parser is waiting for the data, it can
/// parse requests received over other connections. This class provides means
/// for parsing partial data received over the specific connection and
/// interrupting data parsing to switch to a different context.
///
/// A new method @ref HttpMessageParserBase::poll has been created to run the
/// parser's state machine as long as there are unparsed data in the parser's
/// internal buffer. This method returns control to the caller when the parser
/// runs out of data in this buffer. The caller must feed the buffer by calling
/// @ref HttpMessageParserBase::postBuffer and then run
/// @ref HttpMessageParserBase::poll again.
///
/// In case, the caller provides more data than indicated by the "Content-Length"
/// header the parser will return from @c poll() after parsing the data which
/// constitute the HTTP request and not parse the extraneous data. The caller
/// should test the @ref HttpMessageParserBase::needData and
/// @ref HttpMessageParserBase::httpParseOk to determine whether parsing has
/// completed.
///
/// The @ref util::StateModel::runModel must not be used to run the parser
/// state machine, thus it is made private method.
class HttpMessageParserBase : public util::StateModel {
public:

    /// @name States supported by the HttpMessageParserBase.
    ///
    //@{

    /// @brief Parsing successfully completed.
    static const int HTTP_PARSE_OK_ST = SM_DERIVED_STATE_MIN + 1000;

    /// @brief Parsing failed.
    static const int HTTP_PARSE_FAILED_ST = SM_DERIVED_STATE_MIN + 1001;

    //@}

    /// @name Events used during HTTP message parsing.
    ///
    //@{

    /// @brief Chunk of data successfully read and parsed.
    static const int DATA_READ_OK_EVT = SM_DERIVED_EVENT_MIN + 1;

    /// @brief Unable to proceed with parsing until new data is provided.
    static const int NEED_MORE_DATA_EVT = SM_DERIVED_EVENT_MIN + 2;

    /// @brief New data provided and parsing should continue.
    static const int MORE_DATA_PROVIDED_EVT = SM_DERIVED_EVENT_MIN + 3;

    /// @brief Parsing HTTP request successful.
    static const int HTTP_PARSE_OK_EVT = SM_DERIVED_EVENT_MIN + 1000;

    /// @brief Parsing HTTP request failed.
    static const int HTTP_PARSE_FAILED_EVT = SM_DERIVED_EVENT_MIN + 1001;

    //@}

    /// @brief Constructor.
    ///
    /// @param message Reference to the HTTP request or response message.
    HttpMessageParserBase(HttpMessage& message);

    /// @brief Run the parser as long as the amount of data is sufficient.
    ///
    /// The data to be parsed should be provided by calling
    /// @ref HttpMessageParserBase::postBuffer. When the parser reaches the end
    /// of the data buffer the @ref HttpMessageParserBase::poll sets the next
    /// event to @ref NEED_MORE_DATA_EVT and returns. The caller should then invoke
    /// @ref HttpMessageParserBase::postBuffer again to provide more data to the
    /// parser, and call @ref HttpMessageParserBase::poll to continue parsing.
    ///
    /// This method also returns when parsing completes or fails. The last
    /// event can be examined to check whether parsing was successful or not.
    void poll();

    /// @brief Returns true if the parser needs more data to continue.
    ///
    /// @return true if the next event is NEED_MORE_DATA_EVT.
    bool needData() const;

    /// @brief Returns true if the message has been parsed successfully.
    bool httpParseOk() const;

    /// @brief Returns error message.
    std::string getErrorMessage() const {
        return (error_message_);
    }

    /// @brief Provides more input data to the parser.
    ///
    /// This method must be called prior to calling @ref HttpMessageParserBase::poll
    /// to deliver data to be parsed. HTTP messages are received over TCP and
    /// multiple reads may be necessary to retrieve the entire request. There is
    /// no need to accumulate the entire request to start parsing it. A chunk
    /// of data can be provided to the parser using this method and parsed right
    /// away using @ref HttpMessageParserBase::poll.
    ///
    /// @param buf A pointer to the buffer holding the data.
    /// @param buf_size Size of the data within the buffer.
    void postBuffer(const void* buf, const size_t buf_size);

private:

    /// @brief Make @ref runModel private to make sure that the caller uses
    /// @ref poll method instead.
    using StateModel::runModel;

protected:

    /// @brief Define events used by the parser.
    virtual void defineEvents();

    /// @brief Verifies events used by the parser.
    virtual void verifyEvents();

    /// @brief Defines states of the parser.
    virtual void defineStates();

    /// @brief Generic parser handler which reads a single byte of data and
    /// parses it using specified callback function.
    ///
    /// This generic handler is used in most of the parser states to parse a
    /// single byte of input data. If there is no more data it simply returns.
    /// Otherwise, if the next event is DATA_READ_OK_EVT or
    /// MORE_DATA_PROVIDED_EVT, it calls the provided callback function to
    /// parse the new byte of data. For all other states it throws an exception.
    ///
    /// @param handler_name Name of the handler function which called this
    /// method.
    /// @param after_read_logic Callback function to parse the byte of data.
    /// This callback function implements state specific logic.
    ///
    /// @throw HttpRequestParserError when invalid event occurred.
    void stateWithReadHandler(const std::string& handler_name,
                              boost::function<void(const char c)>
                              after_read_logic);

    /// @brief Transition parser to failure state.
    ///
    /// This method transitions the parser to @ref HTTP_PARSE_FAILED_ST and
    /// sets next event to HTTP_PARSE_FAILED_EVT.
    ///
    /// @param error_msg Error message explaining the failure.
    void parseFailure(const std::string& error_msg);

    /// @brief A method called when parsing fails.
    ///
    /// @param explanation Error message explaining the reason for parsing
    /// failure.
    virtual void onModelFailure(const std::string& explanation);

    /// @brief Retrieves next byte of data from the buffer.
    ///
    /// During normal operation, when there is no more data in the buffer,
    /// the parser sets NEED_MORE_DATA_EVT as next event to signal the need for
    /// calling @ref HttpMessageParserBase::postBuffer.
    ///
    /// @throw HttpMessageParserBaseError If current event is already set to
    /// NEED_MORE_DATA_EVT or MORE_DATA_PROVIDED_EVT. In the former case, it
    /// indicates that the caller failed to provide new data using
    /// @ref HttpMessageParserBase::postBuffer. The latter case is highly unlikely
    /// as it indicates that no new data were provided but the state of the
    /// parser was changed from NEED_MORE_DATA_EVT or the data were provided
    /// but the data buffer is empty. In both cases, it is an internal server
    /// error.
    char getNextFromBuffer();

    /// @brief This method is called when invalid event occurred in a particular
    /// parser state.
    ///
    /// This method simply throws @ref HttpParseError informing about invalid
    /// event occurring for the particular parser state. The error message
    /// includes the name of the handler in which the exception has been
    /// thrown. It also includes the event which caused the exception.
    ///
    /// @param handler_name Name of the handler in which the exception is
    /// thrown.
    /// @param event An event which caused the exception.
    ///
    /// @throw HttpMessageParserBaseError.
    void invalidEventError(const std::string& handler_name,
                           const unsigned int event);

    /// @brief Handler for HTTP_PARSE_OK_ST and HTTP_PARSE_FAILED_ST.
    ///
    /// If parsing is successful, it calls @ref HttpRequest::create to validate
    /// the HTTP request. In both cases it transitions the parser to the END_ST.
    void parseEndedHandler();

    /// @brief Tries to read next byte from buffer.
    ///
    /// @param [out] next A reference to the variable where read data should be
    /// stored.
    ///
    /// @return true if character was successfully read, false otherwise.
    bool popNextFromBuffer(char& next);

    /// @brief Checks if specified value is a character.
    ///
    /// @return true, if specified value is a character.
    bool isChar(const char c) const;

    /// @brief Checks if specified value is a control value.
    ///
    /// @return true, if specified value is a control value.
    bool isCtl(const char c) const;

    /// @brief Checks if specified value is a special character.
    ///
    /// @return true, if specified value is a special character.
    bool isSpecial(const char c) const;

    /// @brief Reference to the parsed HTTP message.
    HttpMessage& message_;

    /// @brief Internal buffer from which parser reads data.
    std::list<char> buffer_;

    /// @brief Error message set by @ref onModelFailure.
    std::string error_message_;
};

} // end of namespace isc::http
} // end of namespace isc

#endif
