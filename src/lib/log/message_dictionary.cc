// Copyright (C) 2011  Internet Systems Consortium, Inc. ("ISC")
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES WITH
// REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS.  IN NO EVENT SHALL ISC BE LIABLE FOR ANY SPECIAL, DIRECT,
// INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
// LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
// OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
// PERFORMANCE OF THIS SOFTWARE.

// $Id$

#include <cstddef>
#include <log/message_dictionary.h>
#include <log/message_types.h>

using namespace std;

namespace isc {
namespace log {

// (Virtual) Destructor

MessageDictionary::~MessageDictionary() {
}

// Add message and note if ID already exists

bool MessageDictionary::add(const MessageID& ident, const std::string& text)
{
    map<MessageID, string>::iterator i = dictionary_.find(ident);

    if (i == dictionary_.end()) {

        // Not found, so add it
        dictionary_[ident] = text;
        return true;
    }
    else {

        // Exists, so add the ID to the overflow vector.
        overflow_.push_back(ident);
        return false;
    }
}

// Add message and note if ID does not already exist

bool MessageDictionary::replace(const MessageID& ident, const std::string& text)
{
    map<MessageID, string>::iterator i = dictionary_.find(ident);

    if (i != dictionary_.end()) {

        // Exists, so replace it.
        dictionary_[ident] = text;
        return true;
    }
    else {

        // Not found, so add to the overflow vector.
        overflow_.push_back(ident);
        return false;
    }
}

// Load a set of messages

void MessageDictionary::load(const char* messages[]) {
    int i = 0;
    while (messages[i]) {
        MessageID ident(messages[i]);
        ++i;
        if (messages[i]) {
            string text(messages[i]);
            add(ident, text);
            ++i;
        }
    }
}

// Return message text or blank string

string MessageDictionary::getText(const MessageID& ident) const {
    map<MessageID, string>::const_iterator i = dictionary_.find(ident);
    if (i == dictionary_.end()) {
        return string("");
    }
    else {
        return i->second;
    }
}

// Return global dictionary

MessageDictionary* MessageDictionary::globalDictionary() {
    static MessageDictionary* global = NULL;

    if (global == NULL) {
        global = new MessageDictionary();
    }
    return global;
}




} // namspace log
} // namespace isc
