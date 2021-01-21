// Copyright (C) 2016-2018,2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef HTTP_REQUEST_PARSER_H
#define HTTP_REQUEST_PARSER_H

#include <http/http_message_parser_base.h>
#include <http/request.h>
#include <boost/shared_ptr.hpp>

namespace isc {
namespace http {

class HttpRequestParser;

/// @brief Pointer to the @ref HttpRequestParser.
typedef boost::shared_ptr<HttpRequestParser> HttpRequestParserPtr;

/// @brief A generic parser for HTTP requests.
///
/// This class implements a parser for HTTP requests. The parser derives from
/// @ref HttpMessageParserBase class and implements its own state machine on
/// top of it. The states of the parser reflect various parts of the HTTP
/// message being parsed, e.g. parsing HTTP method, parsing URI, parsing
/// message body etc. The descriptions of all parser states are provided
/// below together with the constants defining these states.
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
class HttpRequestParser : public HttpMessageParserBase {
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

    //@}


    /// @brief Constructor.
    ///
    /// Creates new instance of the parser.
    ///
    /// @param request Reference to the @ref HttpRequest object or its
    /// derivation that should be used to validate the parsed request and
    /// to be used as a container for the parsed request.
    explicit HttpRequestParser(HttpRequest& request);

    /// @brief Initialize the state model for parsing.
    ///
    /// This method must be called before parsing the request, i.e. before
    /// calling @ref HttpRequestParser::poll. It initializes dictionaries of
    /// states and events, and sets the initial model state to RECEIVE_START_ST.
    void initModel();

private:

    /// @brief Defines states of the parser.
    virtual void defineStates();

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
    /// (excluding body). The handler then reads the "Content-Length" header to
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

    //@}

    /// @brief Reference to the request object specified in the constructor.
    HttpRequest& request_;

    /// @brief Pointer to the internal context of the @ref HttpRequest object.
    HttpRequestContextPtr context_;
};

} // namespace http
} // namespace isc

#endif // HTTP_REQUEST_PARSER_H

