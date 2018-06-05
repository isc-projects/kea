// Copyright (C) 2016-2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <http/request_parser.h>
#include <boost/bind.hpp>
#include <iostream>

using namespace isc::util;

namespace isc {
namespace http {

const int HttpRequestParser::RECEIVE_START_ST;
const int HttpRequestParser::HTTP_METHOD_ST;
const int HttpRequestParser::HTTP_URI_ST;
const int HttpRequestParser::HTTP_VERSION_H_ST;
const int HttpRequestParser::HTTP_VERSION_T1_ST;
const int HttpRequestParser::HTTP_VERSION_T2_ST;
const int HttpRequestParser::HTTP_VERSION_P_ST;
const int HttpRequestParser::HTTP_VERSION_SLASH_ST;
const int HttpRequestParser::HTTP_VERSION_MAJOR_START_ST;
const int HttpRequestParser::HTTP_VERSION_MAJOR_ST;
const int HttpRequestParser::HTTP_VERSION_MINOR_START_ST;
const int HttpRequestParser::HTTP_VERSION_MINOR_ST;
const int HttpRequestParser::EXPECTING_NEW_LINE1_ST;
const int HttpRequestParser::HEADER_LINE_START_ST;
const int HttpRequestParser::HEADER_LWS_ST;
const int HttpRequestParser::HEADER_NAME_ST;
const int HttpRequestParser::SPACE_BEFORE_HEADER_VALUE_ST;
const int HttpRequestParser::HEADER_VALUE_ST;
const int HttpRequestParser::EXPECTING_NEW_LINE2_ST;
const int HttpRequestParser::EXPECTING_NEW_LINE3_ST;
const int HttpRequestParser::HTTP_BODY_ST;

HttpRequestParser::HttpRequestParser(HttpRequest& request)
    : HttpMessageParserBase(request), request_(request),
      context_(request_.context()) {
}

void
HttpRequestParser::initModel() {
    // Initialize dictionaries of events and states.
    initDictionaries();

    // Set the current state to starting state and enter the run loop.
    setState(RECEIVE_START_ST);

    // Parsing starts from here.
    postNextEvent(START_EVT);
}

void
HttpRequestParser::defineStates() {
    // Call parent class implementation first.
    HttpMessageParserBase::defineStates();

    // Define HTTP parser specific states.
    defineState(RECEIVE_START_ST, "RECEIVE_START_ST",
                boost::bind(&HttpRequestParser::receiveStartHandler, this));

    defineState(HTTP_METHOD_ST, "HTTP_METHOD_ST",
                boost::bind(&HttpRequestParser::httpMethodHandler, this));

    defineState(HTTP_URI_ST, "HTTP_URI_ST",
                boost::bind(&HttpRequestParser::uriHandler, this));

    defineState(HTTP_VERSION_H_ST, "HTTP_VERSION_H_ST",
                boost::bind(&HttpRequestParser::versionHTTPHandler, this, 'H',
                            HTTP_VERSION_T1_ST));

    defineState(HTTP_VERSION_T1_ST, "HTTP_VERSION_T1_ST",
                boost::bind(&HttpRequestParser::versionHTTPHandler, this, 'T',
                            HTTP_VERSION_T2_ST));

    defineState(HTTP_VERSION_T2_ST, "HTTP_VERSION_T2_ST",
                boost::bind(&HttpRequestParser::versionHTTPHandler, this, 'T',
                            HTTP_VERSION_P_ST));

    defineState(HTTP_VERSION_P_ST, "HTTP_VERSION_P_ST",
                boost::bind(&HttpRequestParser::versionHTTPHandler, this, 'P',
                            HTTP_VERSION_SLASH_ST));

    defineState(HTTP_VERSION_SLASH_ST, "HTTP_VERSION_SLASH_ST",
                boost::bind(&HttpRequestParser::versionHTTPHandler, this, '/',
                            HTTP_VERSION_MAJOR_ST));

    defineState(HTTP_VERSION_MAJOR_START_ST, "HTTP_VERSION_MAJOR_START_ST",
                boost::bind(&HttpRequestParser::versionNumberStartHandler, this,
                            HTTP_VERSION_MAJOR_ST,
                            &context_->http_version_major_));

    defineState(HTTP_VERSION_MAJOR_ST, "HTTP_VERSION_MAJOR_ST",
                boost::bind(&HttpRequestParser::versionNumberHandler, this,
                            '.', HTTP_VERSION_MINOR_START_ST,
                            &context_->http_version_major_));

    defineState(HTTP_VERSION_MINOR_START_ST, "HTTP_VERSION_MINOR_START_ST",
                boost::bind(&HttpRequestParser::versionNumberStartHandler, this,
                            HTTP_VERSION_MINOR_ST,
                            &context_->http_version_minor_));

    defineState(HTTP_VERSION_MINOR_ST, "HTTP_VERSION_MINOR_ST",
                boost::bind(&HttpRequestParser::versionNumberHandler, this,
                            '\r', EXPECTING_NEW_LINE1_ST,
                            &context_->http_version_minor_));

    defineState(EXPECTING_NEW_LINE1_ST, "EXPECTING_NEW_LINE1_ST",
                boost::bind(&HttpRequestParser::expectingNewLineHandler, this,
                            HEADER_LINE_START_ST));

    defineState(HEADER_LINE_START_ST, "HEADER_LINE_START_ST",
                boost::bind(&HttpRequestParser::headerLineStartHandler, this));

    defineState(HEADER_LWS_ST, "HEADER_LWS_ST",
                boost::bind(&HttpRequestParser::headerLwsHandler, this));

    defineState(HEADER_NAME_ST, "HEADER_NAME_ST",
                boost::bind(&HttpRequestParser::headerNameHandler, this));

    defineState(SPACE_BEFORE_HEADER_VALUE_ST, "SPACE_BEFORE_HEADER_VALUE_ST",
                boost::bind(&HttpRequestParser::spaceBeforeHeaderValueHandler, this));

    defineState(HEADER_VALUE_ST, "HEADER_VALUE_ST",
                boost::bind(&HttpRequestParser::headerValueHandler, this));

    defineState(EXPECTING_NEW_LINE2_ST, "EXPECTING_NEW_LINE2",
                boost::bind(&HttpRequestParser::expectingNewLineHandler, this,
                            HEADER_LINE_START_ST));

    defineState(EXPECTING_NEW_LINE3_ST, "EXPECTING_NEW_LINE3_ST",
                boost::bind(&HttpRequestParser::expectingNewLineHandler, this,
                            HTTP_PARSE_OK_ST));

    defineState(HTTP_BODY_ST, "HTTP_BODY_ST",
                boost::bind(&HttpRequestParser::bodyHandler, this));
}

void
HttpRequestParser::receiveStartHandler() {
    char c = getNextFromBuffer();
    if (getNextEvent() != NEED_MORE_DATA_EVT) {
        switch(getNextEvent()) {
        case START_EVT:
            // The first byte should contain a first character of the
            // HTTP method name.
            if (!isChar(c) || isCtl(c) || isSpecial(c)) {
                parseFailure("invalid first character " + std::string(1, c) +
                             " in HTTP method name");

            } else {
                context_->method_.push_back(c);
                transition(HTTP_METHOD_ST, DATA_READ_OK_EVT);
            }
            break;

        default:
            invalidEventError("receiveStartHandler", getNextEvent());
        }
    }
}

void
HttpRequestParser::httpMethodHandler() {
    stateWithReadHandler("httpMethodHandler", [this](const char c) {
        // Space character terminates the HTTP method name. Next thing
        // is the URI.
        if (c == ' ') {
            transition(HTTP_URI_ST, DATA_READ_OK_EVT);

        } else if (!isChar(c) || isCtl(c) || isSpecial(c)) {
            parseFailure("invalid character " + std::string(1, c) +
                         " in HTTP method name");

        } else {
            // Still parsing the method. Append the next character to the
            // method name.
            context_->method_.push_back(c);
            transition(getCurrState(), DATA_READ_OK_EVT);
        }
    });
}

void
HttpRequestParser::uriHandler() {
    stateWithReadHandler("uriHandler", [this](const char c) {
        // Space character terminates the URI.
        if (c == ' ') {
            transition(HTTP_VERSION_H_ST, DATA_READ_OK_EVT);

        } else if (isCtl(c)) {
            parseFailure("control character found in HTTP URI");

        } else {
            // Still parsing the URI. Append the next character to the
            // method name.
            context_->uri_.push_back(c);
            transition(HTTP_URI_ST, DATA_READ_OK_EVT);
        }
    });
}

void
HttpRequestParser::versionHTTPHandler(const char expected_letter,
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
HttpRequestParser::versionNumberStartHandler(const unsigned int next_state,
                                             unsigned int* storage) {
    stateWithReadHandler("versionNumberStartHandler",
                         [this, next_state, storage](const char c) mutable {
        // HTTP version number must be a digit.
        if (isdigit(c)) {
            // Update the version number using new digit being parsed.
            *storage = *storage * 10 + c - '0';
            transition(next_state, DATA_READ_OK_EVT);

        } else {
            parseFailure("expected digit in HTTP version, found " +
                         std::string(1, c));
        }
    });
}

void
HttpRequestParser::versionNumberHandler(const char following_character,
                                        const unsigned int next_state,
                                        unsigned int* const storage) {
    stateWithReadHandler("versionNumberHandler",
                         [this, following_character, next_state, storage](const char c)
                         mutable {
        // We're getting to the end of the version number, let's transition
        // to next state.
        if (c == following_character) {
            transition(next_state, DATA_READ_OK_EVT);

        } else if (isdigit(c)) {
            // Current character is a digit, so update the version number.
            *storage = *storage * 10 + c - '0';

        } else {
            parseFailure("expected digit in HTTP version, found " +
                         std::string(1, c));
        }
    });
}

void
HttpRequestParser::expectingNewLineHandler(const unsigned int next_state) {
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
                request_.create();
                try {
                    // This will throw exception if there is no Content-Length.
                    uint64_t content_length =
                        request_.getHeaderValueAsUint64("Content-Length");
                    if (content_length > 0) {
                        // There is body in this request, so let's parse it.
                        transition(HTTP_BODY_ST, DATA_READ_OK_EVT);
                    }
                } catch (const std::exception& ex) {
                    // There is no body in this message. If the body is required
                    // parsing fails.
                    if (request_.requiresBody()) {
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
HttpRequestParser::headerLineStartHandler() {
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
            // Update header name with the parse letter.
            context_->headers_.push_back(HttpHeaderContext());
            context_->headers_.back().name_.push_back(c);
            transition(HEADER_NAME_ST, DATA_READ_OK_EVT);
        }
    });
}

void
HttpRequestParser::headerLwsHandler() {
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
HttpRequestParser::headerNameHandler() {
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
HttpRequestParser::spaceBeforeHeaderValueHandler() {
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
HttpRequestParser::headerValueHandler() {
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
HttpRequestParser::bodyHandler() {
    stateWithReadHandler("bodyHandler", [this](const char c) {
        // We don't validate the body at this stage. Simply record the
        // number of characters specified within "Content-Length".
        context_->body_.push_back(c);
        if (context_->body_.length() <
            request_.getHeaderValueAsUint64("Content-Length")) {
            transition(HTTP_BODY_ST, DATA_READ_OK_EVT);
        } else {
            transition(HTTP_PARSE_OK_ST, HTTP_PARSE_OK_EVT);
        }
    });
}

} // namespace http
} // namespace isc
