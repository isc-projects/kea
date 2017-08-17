// Copyright (C) 2016-2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef HTTP_REQUEST_PARSER_H
#define HTTP_REQUEST_PARSER_H

#include <exceptions/exceptions.h>
#include <http/request.h>
#include <util/state_model.h>
#include <boost/function.hpp>
#include <boost/shared_ptr.hpp>
#include <list>
#include <stdint.h>
#include <string>

namespace isc {
namespace http {

/// @brief Exception thrown when an error during parsing HTTP request
/// has occurred.
///
/// The most common errors are due to receiving malformed requests.
class HttpRequestParserError : public Exception {
public:
    HttpRequestParserError(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) { };
};

class HttpRequestParser;

/// @brief Pointer to the @ref HttpRequestParser.
typedef boost::shared_ptr<HttpRequestParser> HttpRequestParserPtr;

/// @brief A generic parser for HTTP requests.
///
/// This class implements a parser for HTTP requests. The parser derives from
/// @ref isc::util::StateModel class and implements its own state machine on
/// top of it. The states of the parser reflect various parts of the HTTP
/// message being parsed, e.g. parsing HTTP method, parsing URI, parsing
/// message body etc. The descriptions of all parser states are provided
/// below together with the constants defining these states.
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
/// The request parser validates the syntax of the received message as it
/// progresses with parsing the data. Though, it doesn't interpret the received
/// data until the whole message is parsed. In most cases we want to apply some
/// restrictions on the message content, e.g. Kea Control API requires that
/// commands are sent using HTTP POST, with a JSON command being carried in a
/// message body. The parser doesn't verify if the message meets these
/// restrictions until the whole message is parsed, i.e. stored in the
/// @ref HttpRequestContext object. This object is associated with a
/// @ref HttpRequest object (or its derivation). When the parsing is completed,
/// the @ref HttpRequest::create method is called to retrieve the data from
/// the @ref HttpRequestContext and interpret the data. In particular, the
/// @ref HttpRequest or its derivation checks if the received message meets
/// desired restrictions.
///
/// Kea Control API uses @ref PostHttpRequestJson class (which derives from the
/// @ref HttpRequest) to interpret received request. This class requires
/// that the HTTP request uses POST method and contains the following headers:
/// - Content-Type: application/json,
/// - Content-Length
///
/// If any of these restrictions is not met in the received message, an
/// exception will be thrown, thereby @ref HttpRequestParser will fail parsing
/// the message.
///
/// A new method @ref HttpRequestParser::poll has been created to run the
/// parser's state machine as long as there are unparsed data in the parser's
/// internal buffer. This method returns control to the caller when the parser
/// runs out of data in this buffer. The caller must feed the buffer by calling
/// @ref HttpRequestParser::postBuffer and then run @ref HttpRequestParser::poll
/// again.
///
/// In case the caller provides more data than indicated by the "Content-Length"
/// header the parser will return from poll() after parsing the data which
/// constitute the HTTP request and not parse the extraneous data. The caller
/// should test the @ref HttpRequestParser::needData and
/// @ref HttpRequestParser::httpParseOk to determine whether parsing has
/// completed.
///
/// The @ref util::StateModel::runModel must not be used to run the
/// @ref HttpRequestParser state machine, thus it is made private method.
class HttpRequestParser : public util::StateModel {
public:

    /// @name States supported by the HttpRequestParser.
    ///
    //@{

    /// @brief State indicating a beginning of parsing.
    static const int RECEIVE_START_ST = SM_DERIVED_STATE_MIN + 1;

    /// @brief Parsing HTTP method, e.g. GET, POST etc.
    static const int HTTP_METHOD_ST = SM_DERIVED_STATE_MIN + 2;

    /// @brief Parsing URI.
    static const int HTTP_URI_ST = SM_DERIVED_STATE_MIN + 3;

    /// @brief Parsing letter "H" of "HTTP".
    static const int HTTP_VERSION_H_ST = SM_DERIVED_STATE_MIN + 4;

    /// @brief Parsing first occurrence of "T" in "HTTP".
    static const int HTTP_VERSION_T1_ST = SM_DERIVED_STATE_MIN + 5;

    /// @brief Parsing second occurrence of "T" in "HTTP".
    static const int HTTP_VERSION_T2_ST = SM_DERIVED_STATE_MIN + 6;

    /// @brief Parsing letter "P" in "HTTP".
    static const int HTTP_VERSION_P_ST = SM_DERIVED_STATE_MIN + 7;

    /// @brief Parsing slash character in "HTTP/Y.X"
    static const int HTTP_VERSION_SLASH_ST = SM_DERIVED_STATE_MIN + 8;

    /// @brief Starting to parse major HTTP version number.
    static const int HTTP_VERSION_MAJOR_START_ST = SM_DERIVED_STATE_MIN + 9;

    /// @brief Parsing major HTTP version number.
    static const int HTTP_VERSION_MAJOR_ST = SM_DERIVED_STATE_MIN + 10;

    /// @brief Starting to parse minor HTTP version number.
    static const int HTTP_VERSION_MINOR_START_ST = SM_DERIVED_STATE_MIN + 11;

    /// @brief Parsing minor HTTP version number.
    static const int HTTP_VERSION_MINOR_ST = SM_DERIVED_STATE_MIN + 12;

    /// @brief Parsing first new line (after HTTP version number).
    static const int EXPECTING_NEW_LINE1_ST = SM_DERIVED_STATE_MIN + 13;

    /// @brief Starting to parse a header line.
    static const int HEADER_LINE_START_ST = SM_DERIVED_STATE_MIN + 14;

    /// @brief Parsing LWS (Linear White Space), i.e. new line with a space
    /// or tab character while parsing a HTTP header.
    static const int HEADER_LWS_ST = SM_DERIVED_STATE_MIN + 15;

    /// @brief Parsing header name.
    static const int HEADER_NAME_ST = SM_DERIVED_STATE_MIN + 16;

    /// @brief Parsing space before header value.
    static const int SPACE_BEFORE_HEADER_VALUE_ST = SM_DERIVED_STATE_MIN + 17;

    /// @brief Parsing header value.
    static const int HEADER_VALUE_ST = SM_DERIVED_STATE_MIN + 18;

    /// @brief Expecting new line after parsing header value.
    static const int EXPECTING_NEW_LINE2_ST = SM_DERIVED_STATE_MIN + 19;

    /// @brief Expecting second new line marking end of HTTP headers.
    static const int EXPECTING_NEW_LINE3_ST = SM_DERIVED_STATE_MIN + 20;

    /// @brief Parsing body of a HTTP message.
    static const int HTTP_BODY_ST = SM_DERIVED_STATE_MIN + 21;

    /// @brief Parsing successfully completed.
    static const int HTTP_PARSE_OK_ST = SM_DERIVED_STATE_MIN + 100;

    /// @brief Parsing failed.
    static const int HTTP_PARSE_FAILED_ST = SM_DERIVED_STATE_MIN + 101;

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
    static const int HTTP_PARSE_OK_EVT = SM_DERIVED_EVENT_MIN + 100;

    /// @brief Parsing HTTP request failed.
    static const int HTTP_PARSE_FAILED_EVT = SM_DERIVED_EVENT_MIN + 101;

    //@}

    /// @brief Constructor.
    ///
    /// Creates new instance of the parser.
    ///
    /// @param request Reference to the @ref HttpRequest object or its
    /// derivation that should be used to validate the parsed request and
    /// to be used as a container for the parsed request.
    HttpRequestParser(HttpRequest& request);

    /// @brief Initialize the state model for parsing.
    ///
    /// This method must be called before parsing the request, i.e. before
    /// calling @ref HttpRequestParser::poll. It initializes dictionaries of
    /// states and events, and sets the initial model state to RECEIVE_START_ST.
    void initModel();

    /// @brief Run the parser as long as the amount of data is sufficient.
    ///
    /// The data to be parsed should be provided by calling
    /// @ref HttpRequestParser::postBuffer. When the parser reaches the end of
    /// the data buffer the @ref HttpRequestParser::poll sets the next event to
    /// @ref NEED_MORE_DATA_EVT and returns. The caller should then invoke
    /// @ref HttpRequestParser::postBuffer again to provide more data to the
    /// parser, and call @ref HttpRequestParser::poll to continue parsing.
    ///
    /// This method also returns when parsing completes or fails. The last
    /// event can be examined to check whether parsing was successful or not.
    void poll();

    /// @brief Returns true if the parser needs more data to continue.
    ///
    /// @return true if the next event is NEED_MORE_DATA_EVT.
    bool needData() const;

    /// @brief Returns true if a request has been parsed successfully.
    bool httpParseOk() const;

    /// @brief Returns error message.
    std::string getErrorMessage() const {
        return (error_message_);
    }

    /// @brief Provides more input data to the parser.
    ///
    /// This method must be called prior to calling @ref HttpRequestParser::poll
    /// to deliver data to be parsed. HTTP requests are received over TCP and
    /// multiple reads may be necessary to retrieve the entire request. There is
    /// no need to accumulate the entire request to start parsing it. A chunk
    /// of data can be provided to the parser using this method and parsed right
    /// away using @ref HttpRequestParser::poll.
    ///
    /// @param buf A pointer to the buffer holding the data.
    /// @param buf_size Size of the data within the buffer.
    void postBuffer(const void* buf, const size_t buf_size);

private:

    /// @brief Make @ref runModel private to make sure that the caller uses
    /// @ref poll method instead.
    using StateModel::runModel;

    /// @brief Define events used by the parser.
    virtual void defineEvents();

    /// @brief Verifies events used by the parser.
    virtual void verifyEvents();

    /// @brief Defines states of the parser.
    virtual void defineStates();

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
    /// calling @ref HttpRequestParser::postBuffer.
    ///
    /// @throw HttpRequestParserError If current event is already set to
    /// NEED_MORE_DATA_EVT or MORE_DATA_PROVIDED_EVT. In the former case, it
    /// indicates that the caller failed to provide new data using
    /// @ref HttpRequestParser::postBuffer. The latter case is highly unlikely
    /// as it indicates that no new data were provided but the state of the
    /// parser was changed from NEED_MORE_DATA_EVT or the data were provided
    /// but the data buffer is empty. In both cases, it is an internal server
    /// error.
    char getNextFromBuffer();

    /// @brief This method is called when invalid event occurred in a particular
    /// parser state.
    ///
    /// This method simply throws @ref HttpRequestParserError informing about
    /// invalid event occurring for the particular parser state. The error
    /// message includes the name of the handler in which the exception
    /// has been thrown. It also includes the event which caused the
    /// exception.
    ///
    /// @param handler_name Name of the handler in which the exception is
    /// thrown.
    /// @param event An event which caused the exception.
    ///
    /// @throw HttpRequestParserError.
    void invalidEventError(const std::string& handler_name,
                           const unsigned int event);

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

    /// @name State handlers.
    ///
    //@{

    /// @brief Handler for RECEIVE_START_ST.
    void receiveStartHandler();

    /// @brief Handler for HTTP_METHOD_ST.
    void httpMethodHandler();

    /// @brief Handler for HTTP_URI_ST.
    void uriHandler();

    /// @brief Handler for states parsing "HTTP" string within the first line
    /// of the HTTP request.
    ///
    /// @param expected_letter One of the 'H', 'T', 'P'.
    /// @param next_state A state to which the parser should transition after
    /// parsing the character.
    void versionHTTPHandler(const char expected_letter,
                            const unsigned int next_state);

    /// @brief Handler for HTTP_VERSION_MAJOR_START_ST and
    /// HTTP_VERSION_MINOR_START_ST.
    ///
    /// This handler calculates version number using the following equation:
    /// @code
    ///     storage = storage * 10 + c - '0';
    /// @endcode
    ///
    /// @param next_state State to which the parser should transition.
    /// @param [out] storage Reference to a number holding current product of
    /// parsing major or minor version number.
    void versionNumberStartHandler(const unsigned int next_state,
                                   unsigned int* storage);

    /// @brief Handler for HTTP_VERSION_MAJOR_ST and HTTP_VERSION_MINOR_ST.
    ///
    /// This handler calculates version number using the following equation:
    /// @code
    ///     storage = storage * 10 + c - '0';
    /// @endcode
    ///
    /// @param following_character Character following the version number, i.e.
    /// '.' for major version, \r for minor version.
    /// @param next_state State to which the parser should transition.
    /// @param [out] storage Pointer to a number holding current product of
    /// parsing major or minor version number.
    void versionNumberHandler(const char following_character,
                              const unsigned int next_state,
                              unsigned int* const storage);

    /// @brief Handler for states related to new lines.
    ///
    /// If the next_state is HTTP_PARSE_OK_ST it indicates that the parsed
    /// value is a 3rd new line within request HTTP message. In this case the
    /// handler calls @ref HttpRequest::create to validate the received message
    /// (excluding body). The hander then reads the "Content-Length" header to
    /// check if the request contains a body. If the "Content-Length" is greater
    /// than zero, the parser transitions to HTTP_BODY_ST. If the
    /// "Content-Length" doesn't exist the parser transitions to
    /// HTTP_PARSE_OK_ST.
    ///
    /// @param next_state A state to which parser should transition.
    void expectingNewLineHandler(const unsigned int next_state);

    /// @brief Handler for HEADER_LINE_START_ST.
    void headerLineStartHandler();

    /// @brief Handler for HEADER_LWS_ST.
    void headerLwsHandler();

    /// @brief Handler for HEADER_NAME_ST.
    void headerNameHandler();

    /// @brief Handler for SPACE_BEFORE_HEADER_VALUE_ST.
    void spaceBeforeHeaderValueHandler();

    /// @brief Handler for HEADER_VALUE_ST.
    void headerValueHandler();

    /// @brief Handler for HTTP_BODY_ST.
    void bodyHandler();

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

    /// @brief Internal buffer from which parser reads data.
    std::list<char> buffer_;

    /// @brief Reference to the request object specified in the constructor.
    HttpRequest& request_;

    /// @brief Pointer to the internal context of the @ref HttpRequest object.
    HttpRequestContextPtr context_;

    /// @brief Error message set by @ref onModelFailure.
    std::string error_message_;
};

} // namespace http
} // namespace isc

#endif // HTTP_REQUEST_PARSER_H

