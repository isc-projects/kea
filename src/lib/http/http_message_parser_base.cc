// Copyright (C) 2017-2020 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <http/http_message_parser_base.h>
#include <functional>
#include <sstream>

using namespace isc::util;

namespace isc {
namespace http {

const int HttpMessageParserBase::HTTP_PARSE_OK_ST;
const int HttpMessageParserBase::HTTP_PARSE_FAILED_ST;

const int HttpMessageParserBase::DATA_READ_OK_EVT;
const int HttpMessageParserBase::NEED_MORE_DATA_EVT;
const int HttpMessageParserBase::MORE_DATA_PROVIDED_EVT;
const int HttpMessageParserBase::HTTP_PARSE_OK_EVT;
const int HttpMessageParserBase::HTTP_PARSE_FAILED_EVT;


HttpMessageParserBase::HttpMessageParserBase(HttpMessage& message)
    : StateModel(), message_(message), buffer_(), buffer_pos_(0),
      error_message_() {
}

void
HttpMessageParserBase::poll() {
    try {
        // Run the parser until it runs out of input data or until
        // parsing completes.
        do {
            getState(getCurrState())->run();

        } while (!isModelDone() && (getNextEvent() != NOP_EVT) &&
                 (getNextEvent() != NEED_MORE_DATA_EVT));
    } catch (const std::exception& ex) {
        abortModel(ex.what());
    }
}

bool
HttpMessageParserBase::needData() const {
    return ((getNextEvent() == NEED_MORE_DATA_EVT) ||
            (getNextEvent() == START_EVT));
}

bool
HttpMessageParserBase::httpParseOk() const {
    return ((getNextEvent() == END_EVT) &&
            (getLastEvent() == HTTP_PARSE_OK_EVT));
}

void
HttpMessageParserBase::postBuffer(const void* buf, const size_t buf_size) {
    if (buf_size > 0) {
        // The next event is NEED_MORE_DATA_EVT when the parser wants to
        // signal that more data is needed. This method is called to supply
        // more data and thus it should change the next event to
        // MORE_DATA_PROVIDED_EVT.
        if (getNextEvent() == NEED_MORE_DATA_EVT) {
            transition(getCurrState(), MORE_DATA_PROVIDED_EVT);
        }
        buffer_.insert(buffer_.end(), static_cast<const char*>(buf),
                       static_cast<const char*>(buf) + buf_size);
    }
}

std::string
HttpMessageParserBase::getBufferAsString(const size_t limit) const {
    std::string message(buffer_.begin(), buffer_.end());
    return (logFormatHttpMessage(message, limit));
}

std::string
HttpMessageParserBase::logFormatHttpMessage(const std::string& message,
                                            const size_t limit) {
    if ((limit > 0) && !message.empty()) {
        if (limit < message.size()) {
            std::ostringstream s;
            s << message.substr(0, limit)
              << ".........\n(truncating HTTP message larger than "
              << limit << " characters)\n";
            return (s.str());
        }
    }

    // Return original message if it is empty or does not exceed the
    // limit.
    return (message);
}


void
HttpMessageParserBase::defineEvents() {
    StateModel::defineEvents();

    // Define HTTP parser specific events.
    defineEvent(DATA_READ_OK_EVT, "DATA_READ_OK_EVT");
    defineEvent(NEED_MORE_DATA_EVT, "NEED_MORE_DATA_EVT");
    defineEvent(MORE_DATA_PROVIDED_EVT, "MORE_DATA_PROVIDED_EVT");
    defineEvent(HTTP_PARSE_OK_EVT, "HTTP_PARSE_OK_EVT");
    defineEvent(HTTP_PARSE_FAILED_EVT, "HTTP_PARSE_FAILED_EVT");
}

void
HttpMessageParserBase::verifyEvents() {
    StateModel::verifyEvents();

    getEvent(DATA_READ_OK_EVT);
    getEvent(NEED_MORE_DATA_EVT);
    getEvent(MORE_DATA_PROVIDED_EVT);
    getEvent(HTTP_PARSE_OK_EVT);
    getEvent(HTTP_PARSE_FAILED_EVT);
}

void
HttpMessageParserBase::defineStates() {
    // Call parent class implementation first.
    StateModel::defineStates();

    defineState(HTTP_PARSE_OK_ST, "HTTP_PARSE_OK_ST",
                std::bind(&HttpMessageParserBase::parseEndedHandler, this));

    defineState(HTTP_PARSE_FAILED_ST, "HTTP_PARSE_FAILED_ST",
                std::bind(&HttpMessageParserBase::parseEndedHandler, this));
}

void
HttpMessageParserBase::stateWithReadHandler(const std::string& handler_name,
                                            std::function<void(const char c)>
                                            after_read_logic) {
    std::string bytes;
    getNextFromBuffer(bytes);
    // Do nothing if we reached the end of buffer.
    if (getNextEvent() != NEED_MORE_DATA_EVT) {
        switch(getNextEvent()) {
        case DATA_READ_OK_EVT:
        case MORE_DATA_PROVIDED_EVT:
            after_read_logic(bytes[0]);
            break;
        default:
            invalidEventError(handler_name, getNextEvent());
        }
    }
}

void
HttpMessageParserBase::stateWithMultiReadHandler(const std::string& handler_name,
                                                 std::function<void(const std::string&)>
                                                 after_read_logic) {
    std::string bytes;
    getNextFromBuffer(bytes, 0);
    // Do nothing if we reached the end of buffer.
    if (getNextEvent() != NEED_MORE_DATA_EVT) {
        switch(getNextEvent()) {
        case DATA_READ_OK_EVT:
        case MORE_DATA_PROVIDED_EVT:
            after_read_logic(bytes);
            break;
        default:
            invalidEventError(handler_name, getNextEvent());
        }
    }
}

void
HttpMessageParserBase::parseFailure(const std::string& error_msg) {
    error_message_ = error_msg + " : " + getContextStr();
    transition(HTTP_PARSE_FAILED_ST, HTTP_PARSE_FAILED_EVT);
}

void
HttpMessageParserBase::onModelFailure(const std::string& explanation) {
    if (error_message_.empty()) {
        error_message_ = explanation;
    }
}

void
HttpMessageParserBase::getNextFromBuffer(std::string& bytes, const size_t limit) {
    unsigned int ev = getNextEvent();
    bytes = "\0";
    // The caller should always provide additional data when the
    // NEED_MORE_DATA_EVT occurs. If the next event is still
    // NEED_MORE_DATA_EVT it indicates that the caller hasn't provided
    // the data.
    if (ev == NEED_MORE_DATA_EVT) {
        isc_throw(HttpParseError,
                  "HTTP request parser requires new data to progress, but no data"
                  " have been provided. The transaction is aborted to avoid"
                  " a deadlock. This is a Kea HTTP server logic error!");

    } else {
        // Try to retrieve characters from the buffer.
        const bool data_exist = popNextFromBuffer(bytes, limit);
        if (!data_exist) {
            // There is no more data so it is really not possible that we're
            // at MORE_DATA_PROVIDED_EVT.
            if (ev == MORE_DATA_PROVIDED_EVT) {
                isc_throw(HttpParseError,
                          "HTTP server state indicates that new data have been"
                          " provided to be parsed, but the transaction buffer"
                          " contains no new data. This is a Kea HTTP server logic"
                          " error!");

            } else {
                // If there is no more data we should set NEED_MORE_DATA_EVT
                // event to indicate that new data should be provided.
                postNextEvent(NEED_MORE_DATA_EVT);
            }
        }
    }
}

void
HttpMessageParserBase::invalidEventError(const std::string& handler_name,
                                         const unsigned int event) {
    isc_throw(HttpParseError, handler_name << ": invalid event "
              << getEventLabel(static_cast<int>(event)));
}

void
HttpMessageParserBase::parseEndedHandler() {
    switch(getNextEvent()) {
    case HTTP_PARSE_OK_EVT:
        message_.finalize();
        transition(END_ST, END_EVT);
        break;
    case HTTP_PARSE_FAILED_EVT:
        abortModel("HTTP message parsing failed");
        break;

    default:
        invalidEventError("parseEndedHandler", getNextEvent());
    }
}

bool
HttpMessageParserBase::popNextFromBuffer(std::string& next, const size_t limit) {
    // If there are any characters in the buffer, pop next.
    if (buffer_pos_ < buffer_.size()) {
        next = buffer_.substr(buffer_pos_, limit == 0 ? std::string::npos : limit);

        if (limit > 0) {
            buffer_pos_ += limit;
        }

        if ((buffer_pos_ > buffer_.size()) || (limit == 0)) {
            buffer_pos_ = buffer_.size();
        }
        return (true);
    }
    return (false);
}

bool
HttpMessageParserBase::isChar(const char c) const {
    // was (c >= 0) && (c <= 127)
    return (c >= 0);
}

bool
HttpMessageParserBase::isCtl(const char c) const {
    return (((c >= 0) && (c <= 31)) || (c == 127));
}

bool
HttpMessageParserBase::isSpecial(const char c) const {
    switch (c) {
    case '(':
    case ')':
    case '<':
    case '>':
    case '@':
    case ',':
    case ';':
    case ':':
    case '\\':
    case '"':
    case '/':
    case '[':
    case ']':
    case '?':
    case '=':
    case '{':
    case '}':
    case ' ':
    case '\t':
        return true;

    default:
        ;
    }

    return false;
}


} // end of namespace isc::http
} // end of namespace isc
