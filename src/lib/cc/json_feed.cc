// Copyright (C) 2017-2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <cc/data.h>
#include <cc/json_feed.h>
#include <boost/bind.hpp>

using namespace isc::data;
using namespace isc::util;

namespace isc {
namespace config {

const int JSONFeed::RECEIVE_START_ST;
const int JSONFeed::WHITESPACE_BEFORE_JSON_ST;
const int JSONFeed::JSON_START_ST;
const int JSONFeed::INNER_JSON_ST;
const int JSONFeed::STRING_JSON_ST;
const int JSONFeed::ESCAPE_JSON_ST;
const int JSONFeed::JSON_END_ST;
const int JSONFeed::FEED_OK_ST;
const int JSONFeed::FEED_FAILED_ST;

const int JSONFeed::DATA_READ_OK_EVT;
const int JSONFeed::NEED_MORE_DATA_EVT;
const int JSONFeed::MORE_DATA_PROVIDED_EVT;
const int JSONFeed::FEED_OK_EVT;
const int JSONFeed::FEED_FAILED_EVT;

JSONFeed::JSONFeed()
    : StateModel(), buffer_(), error_message_(), open_scopes_(0),
      output_() {
}

void
JSONFeed::initModel() {
    // Initialize dictionaries of events and states.
    initDictionaries();

    // Set the current state to starting state and enter the run loop.
    setState(RECEIVE_START_ST);

    // Parsing starts from here.
    postNextEvent(START_EVT);
}

void
JSONFeed::poll() {
    try {
        // Process the input data until no more data is available or until
        // JSON feed ends with matching closing brace.
        do {
            getState(getCurrState())->run();

        } while (!isModelDone() && (getNextEvent() != NOP_EVT) &&
                 (getNextEvent() != NEED_MORE_DATA_EVT));
    } catch (const std::exception& ex) {
        abortModel(ex.what());
    }
}

bool
JSONFeed::needData() const {
    return ((getNextEvent() == NEED_MORE_DATA_EVT) ||
            (getNextEvent() == START_EVT));
}

bool
JSONFeed::feedOk() const {
    return ((getNextEvent() == END_EVT) &&
            (getLastEvent() == FEED_OK_EVT));
}

ElementPtr
JSONFeed::toElement() const {
    if (needData()) {
        isc_throw(JSONFeedError, "unable to retrieve the data form the"
                  " JSON feed while parsing hasn't finished");
    }
    try {
        return (Element::fromWire(output_));

    } catch (const std::exception& ex) {
        isc_throw(JSONFeedError, ex.what());
    }
}

void
JSONFeed::postBuffer(const void* buf, const size_t buf_size) {
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

void
JSONFeed::defineEvents() {
    StateModel::defineEvents();

    // Define JSONFeed specific events.
    defineEvent(DATA_READ_OK_EVT, "DATA_READ_OK_EVT");
    defineEvent(NEED_MORE_DATA_EVT, "NEED_MORE_DATA_EVT");
    defineEvent(MORE_DATA_PROVIDED_EVT, "MORE_DATA_PROVIDED_EVT");
    defineEvent(FEED_OK_EVT, "FEED_OK_EVT");
    defineEvent(FEED_FAILED_EVT, "FEED_FAILED_EVT");
}

void
JSONFeed::verifyEvents() {
    StateModel::verifyEvents();

    getEvent(DATA_READ_OK_EVT);
    getEvent(NEED_MORE_DATA_EVT);
    getEvent(MORE_DATA_PROVIDED_EVT);
    getEvent(FEED_OK_EVT);
    getEvent(FEED_FAILED_EVT);
}

void
JSONFeed::defineStates() {
    // Call parent class implementation first.
    StateModel::defineStates();

    defineState(RECEIVE_START_ST, "RECEIVE_START_ST",
                boost::bind(&JSONFeed::receiveStartHandler, this));
    defineState(WHITESPACE_BEFORE_JSON_ST, "WHITESPACE_BEFORE_JSON_ST",
                boost::bind(&JSONFeed::whiteSpaceBeforeJSONHandler, this));
    defineState(INNER_JSON_ST, "INNER_JSON_ST",
                boost::bind(&JSONFeed::innerJSONHandler, this));
    defineState(STRING_JSON_ST, "STRING_JSON_ST",
                boost::bind(&JSONFeed::stringJSONHandler, this));
    defineState(ESCAPE_JSON_ST, "ESCAPE_JSON_ST",
                boost::bind(&JSONFeed::escapeJSONHandler, this));
    defineState(JSON_END_ST, "JSON_END_ST",
                boost::bind(&JSONFeed::endJSONHandler, this));
}

void
JSONFeed::feedFailure(const std::string& error_msg) {
    error_message_ = error_msg;
    transition(FEED_FAILED_ST, FEED_FAILED_EVT);
}

void
JSONFeed::onModelFailure(const std::string& explanation) {
    if (error_message_.empty()) {
        error_message_ = explanation;
    }
}

bool
JSONFeed::popNextFromBuffer(char& next) {
    // If there are any characters in the buffer, pop next.
    if (!buffer_.empty()) {
        next = buffer_.front();
        buffer_.pop_front();
        return (true);
    }
    return (false);
}

char
JSONFeed::getNextFromBuffer() {
    unsigned int ev = getNextEvent();
    char c = '\0';
    // The caller should always provide additional data when the
    // NEED_MORE_DATA_EVT occurs. If the next event is still
    // NEED_MORE_DATA_EVT it indicates that the caller hasn't provided
    // the data.
    if (ev == NEED_MORE_DATA_EVT) {
        isc_throw(JSONFeedError,
                  "JSONFeed requires new data to progress, but no data"
                  " have been provided. The transaction is aborted to avoid"
                  " a deadlock.");

    } else {
        // Try to pop next character from the buffer.
        const bool data_exist = popNextFromBuffer(c);
        if (!data_exist) {
            // There is no more data so it is really not possible that we're
            // at MORE_DATA_PROVIDED_EVT.
            if (ev == MORE_DATA_PROVIDED_EVT) {
                isc_throw(JSONFeedError,
                          "JSONFeed state indicates that new data have been"
                          " provided to be parsed, but the transaction buffer"
                          " contains no new data.");

            } else {
                // If there is no more data we should set NEED_MORE_DATA_EVT
                // event to indicate that new data should be provided.
                transition(getCurrState(), NEED_MORE_DATA_EVT);
            }
        }
    }
    return (c);
}

void
JSONFeed::invalidEventError(const std::string& handler_name,
                            const unsigned int event) {
    isc_throw(JSONFeedError, handler_name << ": "
              << " invalid event " << getEventLabel(static_cast<int>(event)));
}

void
JSONFeed::receiveStartHandler() {
    char c = getNextFromBuffer();
    if (getNextEvent() != NEED_MORE_DATA_EVT) {
        switch (getNextEvent()) {
        case START_EVT:
            switch (c) {
            case '\t':
            case '\n':
            case '\r':
            case ' ':
                transition(WHITESPACE_BEFORE_JSON_ST, DATA_READ_OK_EVT);
                return;

            case '{':
            case '[':
                output_.push_back(c);
                ++open_scopes_;
                transition(INNER_JSON_ST, DATA_READ_OK_EVT);
                return;

            // Cannot start by a string
            case '"':
            default:
                feedFailure("invalid first character " + std::string(1, c));
                break;
            }
            break;

        default:
            invalidEventError("receiveStartHandler", getNextEvent());
        }
    }
}

void
JSONFeed::whiteSpaceBeforeJSONHandler() {
    char c = getNextFromBuffer();
    if (getNextEvent() != NEED_MORE_DATA_EVT) {
        switch (c) {
        case '\t':
        case '\n':
        case '\r':
        case ' ':
            transition(getCurrState(), DATA_READ_OK_EVT);
            break;

        case '{':
        case '[':
            output_.push_back(c);
            ++open_scopes_;
            transition(INNER_JSON_ST, DATA_READ_OK_EVT);
            break;

        // Cannot start by a string
        case '"':
        default:
            feedFailure("invalid character " + std::string(1, c));
        }
    }
}

void
JSONFeed::innerJSONHandler() {
    char c = getNextFromBuffer();
    if (getNextEvent() != NEED_MORE_DATA_EVT) {
        output_.push_back(c);

        switch(c) {
        case '{':
        case '[':
            transition(getCurrState(), DATA_READ_OK_EVT);
            ++open_scopes_;
            break;

        case '}':
        case ']':
            if (--open_scopes_ == 0) {
                transition(JSON_END_ST, FEED_OK_EVT);

            } else {
                transition(getCurrState(), DATA_READ_OK_EVT);
            }
            break;

        case '"':
            transition(STRING_JSON_ST, DATA_READ_OK_EVT);
            break;

        default:
            transition(getCurrState(), DATA_READ_OK_EVT);
        }
    }
}

void
JSONFeed::stringJSONHandler() {
    char c = getNextFromBuffer();
    if (getNextEvent() != NEED_MORE_DATA_EVT) {
        output_.push_back(c);

        switch(c) {
        case '"':
            transition(INNER_JSON_ST, DATA_READ_OK_EVT);
            break;

        case '\\':
            transition(ESCAPE_JSON_ST, DATA_READ_OK_EVT);
            break;

        default:
            transition(getCurrState(), DATA_READ_OK_EVT);
        }
    }
}

void
JSONFeed::escapeJSONHandler() {
    char c = getNextFromBuffer();
    if (getNextEvent() != NEED_MORE_DATA_EVT) {
        output_.push_back(c);

        transition(STRING_JSON_ST, DATA_READ_OK_EVT);
    }
}

void
JSONFeed::endJSONHandler() {
    switch (getNextEvent()) {
    case FEED_OK_EVT:
        transition(END_ST, END_EVT);
        break;

    case FEED_FAILED_EVT:
        abortModel("reading into JSON feed failed");
        break;

    default:
        invalidEventError("endJSONHandler", getNextEvent());
    }
}


} // end of namespace config
} // end of namespace isc
