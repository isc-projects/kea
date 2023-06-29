// Copyright (C) 2017-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef HTTP_RESPONSE_PARSER_H
#define HTTP_RESPONSE_PARSER_H

#include <http/http_message_parser_base.h>
#include <http/response.h>
#include <boost/shared_ptr.hpp>

namespace isc {
namespace http {

class HttpResponseParser;

/// @brief Pointer to the @ref HttpResponseParser.
typedef boost::shared_ptr<HttpResponseParser> HttpResponseParserPtr;

/// @brief A generic parser for HTTP responses.
///
/// This class implements a parser for HTTP responses. The parser derives
/// from the @ref HttpMessageParserBase class and implements its own state
/// machine on top of it. The states of the parser reflect various parts of
/// the HTTP message being parsed, e.g. parsing HTTP version, status code,
/// message body etc. The descriptions of all parser states are provided
/// below together with the constants defining these states.
///
/// The response parser validates the syntax of the received message as it
/// progresses with parsing the data. Though, it doesn't interpret the
/// received data until the whole message is parsed. In most cases we want
/// to apply some restrictions on the message content, e.g. responses to
/// control commands include JSON body. The parser doesn't verify if the
/// message meets such restrictions until the whole message is parsed,
/// i.e. stored in the @ref HttpResponseContext object. This object is
/// associated with @ref HttpResponse object (or its derivation). When
/// the parsing is completed, the @ref HttpResponse::create method is
/// called to retrieve and interpret the data from the context. In
/// particular, the @ref HttpResponse or its derivation checks if the
/// received message meets the desired restrictions.
class HttpResponseParser : public HttpMessageParserBase {
public:

    /// @name States supported by the HttpResponseParser.
    ///
    //@{

    /// @brief State indicating a beginning of parsing.
    static const int RECEIVE_START_ST = SM_DERIVED_STATE_MIN + 101;

    /// @brief Parsing letter "H" of "HTTP".
    static const int HTTP_VERSION_H_ST = SM_DERIVED_STATE_MIN + 102;

    /// @brief Parsing first occurrence of "T" in "HTTP".
    static const int HTTP_VERSION_T1_ST = SM_DERIVED_STATE_MIN + 103;

    /// @brief Parsing second occurrence of "T" in "HTTP".
    static const int HTTP_VERSION_T2_ST = SM_DERIVED_STATE_MIN + 104;

    /// @brief Parsing letter "P" in "HTTP".
    static const int HTTP_VERSION_P_ST = SM_DERIVED_STATE_MIN + 105;

    /// @brief Parsing slash character in "HTTP/Y.X"
    static const int HTTP_VERSION_SLASH_ST = SM_DERIVED_STATE_MIN + 106;

    /// @brief Starting to parse major HTTP version number.
    static const int HTTP_VERSION_MAJOR_START_ST = SM_DERIVED_STATE_MIN + 107;

    /// @brief Parsing major HTTP version number.
    static const int HTTP_VERSION_MAJOR_ST = SM_DERIVED_STATE_MIN + 108;

    /// @brief Starting to parse minor HTTP version number.
    static const int HTTP_VERSION_MINOR_START_ST = SM_DERIVED_STATE_MIN + 109;

    /// @brief Parsing minor HTTP version number.
    static const int HTTP_VERSION_MINOR_ST = SM_DERIVED_STATE_MIN + 110;

    /// @brief Starting to parse HTTP status code.
    static const int HTTP_STATUS_CODE_START_ST = SM_DERIVED_STATE_MIN + 111;

    /// @brief Parsing HTTP status code.
    static const int HTTP_STATUS_CODE_ST = SM_DERIVED_STATE_MIN + 112;

    /// @brief Starting to parse HTTP status phrase.
    static const int HTTP_PHRASE_START_ST = SM_DERIVED_STATE_MIN + 113;

    /// @brief Parsing HTTP status phrase.
    static const int HTTP_PHRASE_ST = SM_DERIVED_STATE_MIN + 114;

    /// @brief Parsing first new line (after HTTP status phrase).
    static const int EXPECTING_NEW_LINE1_ST = SM_DERIVED_STATE_MIN + 115;

    static const int HEADER_LINE_START_ST = SM_DERIVED_STATE_MIN + 116;

    /// @brief Parsing LWS (Linear White Space), i.e. new line with a space
    /// or tab character while parsing a HTTP header.
    static const int HEADER_LWS_ST = SM_DERIVED_STATE_MIN + 117;

    /// @brief Parsing header name.
    static const int HEADER_NAME_ST = SM_DERIVED_STATE_MIN + 118;

    /// @brief Parsing space before header value.
    static const int SPACE_BEFORE_HEADER_VALUE_ST = SM_DERIVED_STATE_MIN + 119;

    /// @brief Parsing header value.
    static const int HEADER_VALUE_ST = SM_DERIVED_STATE_MIN + 120;

    /// @brief Expecting new line after parsing header value.
    static const int EXPECTING_NEW_LINE2_ST = SM_DERIVED_STATE_MIN + 121;

    /// @brief Expecting second new line marking end of HTTP headers.
    static const int EXPECTING_NEW_LINE3_ST = SM_DERIVED_STATE_MIN + 122;

    /// @brief Parsing body of a HTTP message.
    static const int HTTP_BODY_ST = SM_DERIVED_STATE_MIN + 123;

    //@}

    /// @brief Constructor.
    ///
    /// Creates new instance of the parser.
    ///
    /// @param response Reference to the @ref HttpResponse object or its
    /// derivation that should be used to validate the parsed response and
    /// to be used as a container for the parsed response.
    explicit HttpResponseParser(HttpResponse& response);

    /// @brief Initialize the state model for parsing.
    ///
    /// This method must be called before parsing the response, i.e. before
    /// calling @ref HttpResponseParser::poll. It initializes dictionaries of
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

    /// @brief Handler for states parsing "HTTP" string within the first line
    /// of the HTTP request.
    ///
    /// @param expected_letter One of the 'H', 'T', 'P'.
    /// @param next_state A state to which the parser should transition after
    /// parsing the character.
    void versionHTTPHandler(const char expected_letter,
                            const unsigned int next_state);

    /// @brief Handler for states in which parser begins to read numeric values.
    ///
    /// This handler calculates version number using the following equation:
    /// @code
    ///     storage = storage * 10 + c - '0';
    /// @endcode
    ///
    /// @param next_state State to which the parser should transition.
    /// @param number_name Name of the parsed numeric value, e.g. HTTP version or
    /// HTTP status code (used for error logging).
    /// @param [out] storage Reference to a number holding current product of
    /// parsing major or minor version number.
    void numberStartHandler(const unsigned int next_state,
                            const std::string& number_name,
                            unsigned int* const storage);

    /// @brief Handler for states in which parser reads numeric values.
    ///
    /// This handler calculates version number using the following equation:
    /// @code
    ///     storage = storage * 10 + c - '0';
    /// @endcode
    ///
    /// @param following_character Character following the version number, i.e.
    /// '.' for major version, \r for minor version.
    /// @param next_state State to which the parser should transition.
    /// @param number_name Name of the parsed numeric value, e.g. HTTP version or
    /// HTTP status code (used for error logging).
    /// @param [out] storage Pointer to a number holding current product of
    /// parsing major or minor version number.
    void numberHandler(const char following_character,
                       const unsigned int next_state,
                       const std::string& number_name,
                       unsigned int* const storage);

    /// @brief Handler for HTTP_PHRASE_START_ST.
    void phraseStartHandler();

    /// @brief Handler for HTTP_PHRASE_ST.
    void phraseHandler();

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

    /// @brief Reference to the response object specified in the constructor.
    HttpResponse& response_;

    /// @brief Pointer to the internal context of the @ref HttpResponse object.
    HttpResponseContextPtr context_;
};

} // end of namespace isc::http
} // end of namespace isc

#endif
