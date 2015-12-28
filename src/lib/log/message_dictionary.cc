// Copyright (C) 2011-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

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
MessageDictionary::add(const std::string& ident, const std::string& text) {
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
MessageDictionary::replace(const std::string& ident, const std::string& text) {
    Dictionary::iterator i = dictionary_.find(ident);
    bool found = (i != dictionary_.end());
    if (found) {

        // Exists, so replace it.
        dictionary_[ident] = text;
    }

    return (found);
}

bool
MessageDictionary::erase(const std::string& ident, const std::string& text) {
    Dictionary::iterator mes = dictionary_.find(ident);
    // Both the ID and the text must match.
    bool found = (mes != dictionary_.end() && (mes->second == text));
    if (found) {
        dictionary_.erase(mes);
    }
    return (found);
}

// Load a set of messages

vector<std::string>
MessageDictionary::load(const char* messages[]) {
    vector<std::string> duplicates;
    int i = 0;
    while (messages[i]) {
        // ID present, so point to text.
        ++i;
        if (messages[i]) {
            const MessageID ident(messages[i - 1]);
            // Text not null, note it and point to next ident.
            const std::string text(messages[i]);
            ++i;

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

// Return message text or blank string.  A reference is returned to a string
// in the dictionary - this is fine, as the string is immediately used for
// output.

const string&
MessageDictionary::getText(const std::string& ident) const {
    static const string empty("");
    Dictionary::const_iterator i = dictionary_.find(ident);
    if (i == dictionary_.end()) {
        return (empty);
    }
    else {
        return (i->second);
    }
}

// Return global dictionary

const MessageDictionaryPtr&
MessageDictionary::globalDictionary() {
    static MessageDictionaryPtr global(new MessageDictionary());
    return (global);
}




} // namespace log
} // namespace isc
