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

#include <iostream>

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

bool
MessageDictionary::add(const string& ident, const string& text) {
    Dictionary::iterator i = dictionary_.find(ident);
    bool not_found = (i == dictionary_.end());
    if (not_found) {

        // Message not already in the dictionary, so add it.
        dictionary_[ident] = text;
    }
    
    return (not_found);
}

// Add message and note if ID does not already exist

bool
MessageDictionary::replace(const string& ident, const string& text) {
    Dictionary::iterator i = dictionary_.find(ident);
    bool found = (i != dictionary_.end());
    if (found) {

        // Exists, so replace it.
        dictionary_[ident] = text;
    }
    
    return (found);
}

// Load a set of messages

vector<std::string>
MessageDictionary::load(const char* messages[]) {
    vector<std::string> duplicates;
    int i = 0;
    while (messages[i]) {

        // ID present, so note it and point to text.
        const MessageID ident(messages[i++]);
        if (messages[i]) {

            // Text not null, note it and point to next ident. 
            string text(messages[i++]);

            // Add ID and text to message dictionary, noting if the ID was
            // already present.
            bool added = add(ident, text);
            if (!added) {
                duplicates.push_back(boost::lexical_cast<string>(ident));
            }
        }
    }
    return (duplicates);
}

// Return message text or blank string

string
MessageDictionary::getText(const string& ident) const {
    Dictionary::const_iterator i = dictionary_.find(ident);
    if (i == dictionary_.end()) {
        return (string(""));
    }
    else {
        return (i->second);
    }
}

// Return global dictionary

MessageDictionary*
MessageDictionary::globalDictionary() {
    static MessageDictionary global;
    return (&global);
}




} // namspace log
} // namespace isc
