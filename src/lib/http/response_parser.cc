// Copyright (C) 2017-2020 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <http/response_parser.h>
#include <functional>

using namespace isc::util;

namespace isc {
namespace http {

const int HttpResponseParser::RECEIVE_START_ST;
const int HttpResponseParser::HTTP_VERSION_H_ST;
const int HttpResponseParser::HTTP_VERSION_T1_ST;
const int HttpResponseParser::HTTP_VERSION_T2_ST;
const int HttpResponseParser::HTTP_VERSION_P_ST;
const int HttpResponseParser::HTTP_VERSION_SLASH_ST;
const int HttpResponseParser::HTTP_VERSION_MAJOR_START_ST;
const int HttpResponseParser::HTTP_VERSION_MAJOR_ST;
const int HttpResponseParser::HTTP_VERSION_MINOR_START_ST;
const int HttpResponseParser::HTTP_VERSION_MINOR_ST;
const int HttpResponseParser::HTTP_STATUS_CODE_START_ST;
const int HttpResponseParser::HTTP_STATUS_CODE_ST;
const int HttpResponseParser::HTTP_PHRASE_START_ST;
const int HttpResponseParser::HTTP_PHRASE_ST;
const int HttpResponseParser::EXPECTING_NEW_LINE1_ST;
const int HttpResponseParser::HEADER_LINE_START_ST;
const int HttpResponseParser::HEADER_LWS_ST;
const int HttpResponseParser::HEADER_NAME_ST;
const int HttpResponseParser::SPACE_BEFORE_HEADER_VALUE_ST;
const int HttpResponseParser::HEADER_VALUE_ST;
const int HttpResponseParser::EXPECTING_NEW_LINE2_ST;
const int HttpResponseParser::EXPECTING_NEW_LINE3_ST;
const int HttpResponseParser::HTTP_BODY_ST;

HttpResponseParser::HttpResponseParser(HttpResponse& response)
    : HttpMessageParserBase(response), response_(response),
      context_(response.context()) {
}

void
HttpResponseParser::initModel() {
    // Initialize dictionaries of events and states.
    initDictionaries();

    // Set the current state to starting state and enter the run loop.
    setState(RECEIVE_START_ST);

    // Parsing starts from here.
    postNextEvent(START_EVT);
}

void
HttpResponseParser::defineStates() {
    // Call parent class implementation first.
    HttpMessageParserBase::defineStates();

    // Define HTTP parser specific states.
    defineState(RECEIVE_START_ST, "RECEIVE_START_ST",
                std::bind(&HttpResponseParser::receiveStartHandler, this));

    defineState(HTTP_VERSION_T1_ST, "HTTP_VERSION_T1_ST",
                std::bind(&HttpResponseParser::versionHTTPHandler, this, 'T',
                          HTTP_VERSION_T2_ST));

    defineState(HTTP_VERSION_T2_ST, "HTTP_VERSION_T2_ST",
                std::bind(&HttpResponseParser::versionHTTPHandler, this, 'T',
                          HTTP_VERSION_P_ST));

    defineState(HTTP_VERSION_P_ST, "HTTP_VERSION_P_ST",
                std::bind(&HttpResponseParser::versionHTTPHandler, this, 'P',
                          HTTP_VERSION_SLASH_ST));

    defineState(HTTP_VERSION_SLASH_ST, "HTTP_VERSION_SLASH_ST",
                std::bind(&HttpResponseParser::versionHTTPHandler, this, '/',
                          HTTP_VERSION_MAJOR_ST));

    defineState(HTTP_VERSION_MAJOR_START_ST, "HTTP_VERSION_MAJOR_START_ST",
                std::bind(&HttpResponseParser::numberStartHandler, this,
                          HTTP_VERSION_MAJOR_ST,
                          "HTTP version",
                          &context_->http_version_major_));

    defineState(HTTP_VERSION_MAJOR_ST, "HTTP_VERSION_MAJOR_ST",
                std::bind(&HttpResponseParser::numberHandler, this,
                          '.', HTTP_VERSION_MINOR_START_ST,
                          "HTTP version",
                          &context_->http_version_major_));

    defineState(HTTP_VERSION_MINOR_START_ST, "HTTP_VERSION_MINOR_START_ST",
                std::bind(&HttpResponseParser::numberStartHandler, this,
                          HTTP_VERSION_MINOR_ST,
                          "HTTP version",
                          &context_->http_version_minor_));

    defineState(HTTP_VERSION_MINOR_ST, "HTTP_VERSION_MINOR_ST",
                std::bind(&HttpResponseParser::numberHandler, this,
                          ' ', HTTP_STATUS_CODE_START_ST,
                          "HTTP version",
                          &context_->http_version_minor_));

    defineState(HTTP_STATUS_CODE_START_ST, "HTTP_STATUS_CODE_START_ST",
                std::bind(&HttpResponseParser::numberStartHandler, this,
                          HTTP_STATUS_CODE_ST,
                          "HTTP status code",
                          &context_->status_code_));

    defineState(HTTP_STATUS_CODE_ST, "HTTP_STATUS_CODE_ST",
                std::bind(&HttpResponseParser::numberHandler, this,
                          ' ', HTTP_PHRASE_START_ST,
                          "HTTP status code",
                          &context_->status_code_));

    defineState(HTTP_PHRASE_START_ST, "HTTP_PHRASE_START_ST",
                std::bind(&HttpResponseParser::phraseStartHandler, this));

    defineState(HTTP_PHRASE_ST, "HTTP_PHRASE_ST",
                std::bind(&HttpResponseParser::phraseHandler, this));

    defineState(EXPECTING_NEW_LINE1_ST, "EXPECTING_NEW_LINE1_ST",
                std::bind(&HttpResponseParser::expectingNewLineHandler, this,
                          HEADER_LINE_START_ST));

    defineState(HEADER_LINE_START_ST, "HEADER_LINE_START_ST",
                std::bind(&HttpResponseParser::headerLineStartHandler, this));

    defineState(HEADER_LWS_ST, "HEADER_LWS_ST",
                std::bind(&HttpResponseParser::headerLwsHandler, this));

    defineState(HEADER_NAME_ST, "HEADER_NAME_ST",
                std::bind(&HttpResponseParser::headerNameHandler, this));

    defineState(SPACE_BEFORE_HEADER_VALUE_ST, "SPACE_BEFORE_HEADER_VALUE_ST",
                std::bind(&HttpResponseParser::spaceBeforeHeaderValueHandler, this));

    defineState(HEADER_VALUE_ST, "HEADER_VALUE_ST",
                std::bind(&HttpResponseParser::headerValueHandler, this));

    defineState(EXPECTING_NEW_LINE2_ST, "EXPECTING_NEW_LINE2",
                std::bind(&HttpResponseParser::expectingNewLineHandler, this,
                          HEADER_LINE_START_ST));

    defineState(EXPECTING_NEW_LINE3_ST, "EXPECTING_NEW_LINE3_ST",
                std::bind(&HttpResponseParser::expectingNewLineHandler, this,
                          HTTP_PARSE_OK_ST));

    defineState(HTTP_BODY_ST, "HTTP_BODY_ST",
                std::bind(&HttpResponseParser::bodyHandler, this));
}

void
HttpResponseParser::receiveStartHandler() {
    std::string bytes;
    getNextFromBuffer(bytes);
    if (getNextEvent() != NEED_MORE_DATA_EVT) {
        switch(getNextEvent()) {
        case START_EVT:
            if (bytes[0] == 'H') {
                transition(HTTP_VERSION_T1_ST, DATA_READ_OK_EVT);

            } else {
                parseFailure("unexpected first character " + std::string(1, bytes[0]) +
                             ": expected \'H\'");
            }
            break;

        default:
            invalidEventError("receiveStartHandler", getNextEvent());
        }
    }
}

void
HttpResponseParser::versionHTTPHandler(const char expected_letter,
                                       const unsigned int next_state) {
    stateWithReadHandler("versionHTTPHandler",
                         [this, expected_letter, next_state](const char c) {
        // We're handling one of the letters: 'H', 'T' or 'P'.
        if (c == expected_letter) {
            // The HTTP version is specified as "HTTP/X.Y". If the current
            // character is a slash we're starting to parse major HTTP version
            // number. Let's reset the version numbers.
            if (c == '/') {
                context_->http_version_major_ = 0;
                context_->http_version_minor_ = 0;
            }
            // In all cases, let's transition to next specified state.
            transition(next_state, DATA_READ_OK_EVT);

        } else {
            // Unexpected character found. Parsing fails.
            parseFailure("unexpected character " + std::string(1, c) +
                         " in HTTP version string");
        }
    });
}

void
HttpResponseParser::numberStartHandler(const unsigned int next_state,
                                       const std::string& number_name,
                                       unsigned int* storage) {
    stateWithReadHandler("numberStartHandler",
                         [this, next_state, number_name, storage](const char c) mutable {
        // HTTP version number must be a digit.
        if (isdigit(c)) {
            // Update the version number using new digit being parsed.
            *storage = *storage * 10 + c - '0';
            transition(next_state, DATA_READ_OK_EVT);

        } else {
            parseFailure("expected digit in " + number_name + ", found " +
                         std::string(1, c));
        }
    });
}

void
HttpResponseParser::numberHandler(const char following_character,
                                  const unsigned int next_state,
                                  const std::string& number_name,
                                  unsigned int* const storage) {
    stateWithReadHandler("numberHandler",
                         [this, following_character, number_name, next_state, storage](const char c)
                         mutable {
        // We're getting to the end of the version number, let's transition
        // to next state.
        if (c == following_character) {
            transition(next_state, DATA_READ_OK_EVT);

        } else if (isdigit(c)) {
            // Current character is a digit, so update the version number.
            *storage = *storage * 10 + c - '0';

        } else {
            parseFailure("expected digit in " + number_name + ", found " +
                         std::string(1, c));
        }
    });
}

void
HttpResponseParser::phraseStartHandler() {
    stateWithReadHandler("phraseStartHandler", [this](const char c) {
        if (!isChar(c) || isCtl(c)) {
            parseFailure("invalid first character " + std::string(1, c) +
                         " in HTTP phrase");
        } else {
            context_->phrase_.push_back(c);
            transition(HTTP_PHRASE_ST, DATA_READ_OK_EVT);
        }
    });
}

void
HttpResponseParser::phraseHandler() {
    stateWithReadHandler("phraseHandler", [this](const char c) {
        if (c == '\r') {
            transition(EXPECTING_NEW_LINE1_ST, DATA_READ_OK_EVT);

        } else if (!isChar(c) || isCtl(c)) {
            parseFailure("invalid character " + std::string(1, c) +
                         " in HTTP phrase");

        } else {
            context_->phrase_.push_back(c);
            transition(HTTP_PHRASE_ST, DATA_READ_OK_EVT);
        }
    });
}

void
HttpResponseParser::expectingNewLineHandler(const unsigned int next_state) {
    stateWithReadHandler("expectingNewLineHandler", [this, next_state](const char c) {
        // Only a new line character is allowed in this state.
        if (c == '\n') {
            // If next state is HTTP_PARSE_OK_ST it means that we're
            // parsing 3rd new line in the HTTP request message. This
            // terminates the HTTP request (if there is no body) or marks the
            // beginning of the body.
            if (next_state == HTTP_PARSE_OK_ST) {
                // Whether there is a body in this message or not, we should
                // parse the HTTP headers to validate it and to check if there
                // is "Content-Length" specified. The "Content-Length" is
                // required for parsing body.
                response_.create();
                try {
                    // This will throw exception if there is no Content-Length.
                    uint64_t content_length =
                        response_.getHeaderValueAsUint64("Content-Length");
                    if (content_length > 0) {
                        // There is body in this request, so let's parse it.
                        transition(HTTP_BODY_ST, DATA_READ_OK_EVT);
                    } else {
                        transition(HTTP_PARSE_OK_ST, HTTP_PARSE_OK_EVT);
                    }
                } catch (const std::exception& ex) {
                    // There is no body in this message. If the body is required
                    // parsing fails.
                    if (response_.requiresBody()) {
                        parseFailure("HTTP message lacks a body");

                    } else {
                        // Body not required so simply terminate parsing.
                        transition(HTTP_PARSE_OK_ST, HTTP_PARSE_OK_EVT);
                    }
                }

            } else {
                // This is 1st or 2nd new line, so let's transition to the
                // next state required by this handler.
                transition(next_state, DATA_READ_OK_EVT);
            }
        } else {
            parseFailure("expecting new line after CR, found " +
                         std::string(1, c));
        }
    });
}

void
HttpResponseParser::headerLineStartHandler() {
    stateWithReadHandler("headerLineStartHandler", [this](const char c) {
        // If we're parsing HTTP headers and we found CR it marks the
        // end of headers section.
        if (c == '\r') {
            transition(EXPECTING_NEW_LINE3_ST, DATA_READ_OK_EVT);

        } else if (!context_->headers_.empty() && ((c == ' ') || (c == '\t'))) {
            // New line in headers section followed by space or tab is an LWS,
            // a line break within header value.
            transition(HEADER_LWS_ST, DATA_READ_OK_EVT);

        } else if (!isChar(c) || isCtl(c) || isSpecial(c)) {
            parseFailure("invalid character " + std::string(1, c) +
                         " in header name");

        } else {
            // Update header name with the parsed letter.
            context_->headers_.push_back(HttpHeaderContext());
            context_->headers_.back().name_.push_back(c);
            transition(HEADER_NAME_ST, DATA_READ_OK_EVT);
        }
    });
}

void
HttpResponseParser::headerLwsHandler() {
    stateWithReadHandler("headerLwsHandler", [this](const char c) {
        if (c == '\r') {
            // Found CR during parsing a header value. Next value
            // should be new line.
            transition(EXPECTING_NEW_LINE2_ST, DATA_READ_OK_EVT);

        } else if ((c == ' ') || (c == '\t')) {
            // Space and tab is used to mark LWS. Simply swallow
            // this character.
            transition(getCurrState(), DATA_READ_OK_EVT);

        } else if (isCtl(c)) {
            parseFailure("control character found in the HTTP header " +
                        context_->headers_.back().name_);

        } else {
            // We're parsing header value, so let's update it.
            context_->headers_.back().value_.push_back(c);
            transition(HEADER_VALUE_ST, DATA_READ_OK_EVT);
        }
    });
}

void
HttpResponseParser::headerNameHandler() {
    stateWithReadHandler("headerNameHandler", [this](const char c) {
            // Colon follows header name and it has its own state.
        if (c == ':') {
            transition(SPACE_BEFORE_HEADER_VALUE_ST, DATA_READ_OK_EVT);

        } else if (!isChar(c) || isCtl(c) || isSpecial(c)) {
            parseFailure("invalid character " + std::string(1, c) +
                         " found in the HTTP header name");

        } else {
            // Parsing a header name, so update it.
            context_->headers_.back().name_.push_back(c);
            transition(getCurrState(), DATA_READ_OK_EVT);
        }
    });
}

void
HttpResponseParser::spaceBeforeHeaderValueHandler() {
    stateWithReadHandler("spaceBeforeHeaderValueHandler", [this](const char c) {
        if (c == ' ') {
            // Remove leading whitespace from the header value.
            transition(getCurrState(), DATA_READ_OK_EVT);

        } else if (c == '\r') {
            // If CR found during parsing header value, it marks the end
            // of this value.
            transition(EXPECTING_NEW_LINE2_ST, DATA_READ_OK_EVT);

        } else if (isCtl(c)) {
            parseFailure("control character found in the HTTP header "
                         + context_->headers_.back().name_);

        } else {
            // Still parsing the value, so let's update it.
            context_->headers_.back().value_.push_back(c);
            transition(HEADER_VALUE_ST, DATA_READ_OK_EVT);
        }
    });
}

void
HttpResponseParser::headerValueHandler() {
    stateWithReadHandler("headerValueHandler", [this](const char c) {
        // If CR found during parsing header value, it marks the end
        // of this value.
        if (c == '\r') {
            transition(EXPECTING_NEW_LINE2_ST, DATA_READ_OK_EVT);

        } else if (isCtl(c)) {
            parseFailure("control character found in the HTTP header "
                         + context_->headers_.back().name_);

        } else {
            // Still parsing the value, so let's update it.
            context_->headers_.back().value_.push_back(c);
            transition(HEADER_VALUE_ST, DATA_READ_OK_EVT);
        }
    });
}

void
HttpResponseParser::bodyHandler() {
    stateWithMultiReadHandler("bodyHandler", [this](const std::string& body) {
        // We don't validate the body at this stage. Simply record the
        // number of characters specified within "Content-Length".
        context_->body_ += body;
        size_t content_length = response_.getHeaderValueAsUint64("Content-Length");
        if (context_->body_.length() < content_length) {
            transition(HTTP_BODY_ST, DATA_READ_OK_EVT);

        } else {
            // If there was some extraneous data, ignore it.
            if (context_->body_.length() > content_length) {
                context_->body_.resize(content_length);
            }
            transition(HTTP_PARSE_OK_ST, HTTP_PARSE_OK_EVT);
        }
    });
}


} // end of namespace isc::http
} // end of namespace isc
