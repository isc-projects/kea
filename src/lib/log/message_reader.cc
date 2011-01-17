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

#include <errno.h>
#include <string.h>

#include <iostream>
#include <fstream>

#include <log/message_exception.h>
#include <log/messagedef.h>
#include <log/message_reader.h>
#include <log/strutil.h>

using namespace std;

namespace isc {
namespace log {

// Virtual destructor.
MessageReader::~MessageReader() {
}


// Read the file.

void
MessageReader::readFile(const string& file, MessageReader::Mode mode) {

    // Ensure the non-added collection is empty: this object might be
    // being reused.
    not_added_.clear();

    // Open the file
    ifstream infile(file.c_str());
    if (infile.fail()) {
        throw MessageException(MSG_OPENIN, file, strerror(errno));
    }

    // Loop round reading it.
    string line;
    getline(infile, line);
    while (infile.good()) {
        processLine(line, mode);
        getline(infile, line);
    }

    // Why did the loop terminate?
    if (! infile.eof()) {
        throw MessageException(MSG_READERR, file, strerror(errno));
    }
    infile.close();
}

// Parse a line of the file

void
MessageReader::processLine(const string& line, MessageReader::Mode mode) {

    // Get rid of leading and trailing spaces
    string text = isc::strutil::trim(line);

    if (text.empty()) {
        ;                           // Ignore blank lines

    } else if ((text[0] == '#') || (text[0] == '+')) {
        ;                           // Ignore comments or descriptions

    } else if (text[0] == '$') {
        parseDirective(text);       // Process directives

    } else {
        parseMessage(text, mode);   // Process other lines

    }
}

// Process directive

void
MessageReader::parseDirective(const std::string& text) {

    static string valid = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_";

    // Regardless of what happens, all prefixes will be uppercase (as will
    // all symbols).
    string line = text;
    isc::strutil::uppercase(line);
    vector<string> tokens = isc::strutil::tokens(line);

    // Only $PREFIX is recognised so far, so we'll handle it here.
    if (tokens[0] != string("$PREFIX")) {
        throw MessageException(MSG_UNRECDIR, tokens[0]);

    } else if (tokens.size() < 2) {
        throw MessageException(MSG_PRFNOARG);

    } else if (tokens.size() > 2) {
        throw MessageException(MSG_PRFEXTRARG);

    }

    // Token is potentially valid providing it only contains alphabetic
    // and numeric characters (and underscores) and does not start with a
    // digit.
    
    if ((tokens[1].find_first_not_of(valid) != string::npos) ||
        (std::isdigit(tokens[1][0]))) {

        // Invalid character in string or it starts with a digit.
        throw MessageException(MSG_PRFINVARG, tokens[1]);
    }

    // All OK - unless the prefix has already been set.

    if (prefix_.size() != 0) {
        throw MessageException(MSG_DUPLPRFX);
    }

    // Prefix has not been set, so set it and return success.

    prefix_ = tokens[1];
}

// Process message.  By the time this method is called, the line has been
// stripped of leading and trailing spaces, and we believe that it is a line
// defining a message.  The first token on the line is convered to uppercase
// and becomes the message ID; the rest of the line is the message text.

void
MessageReader::parseMessage(const std::string& text, MessageReader::Mode mode) {

    static string delimiters("\t\n ");   // Delimiters

    // Look for the first delimiter.
    size_t first_delim = text.find_first_of(delimiters);
    if (first_delim == string::npos) {

        // Just a single token in the line - this is not valid
        throw MessageException(MSG_ONETOKEN, text);
    }

    // Extract the first token into the message ID
    MessageID ident = text.substr(0, first_delim);

    // Locate the start of the message text
    size_t first_text = text.find_first_not_of(delimiters, first_delim);
    if (first_text == string::npos) {

        // ?? This happens if there are trailing delimiters, which should not
        // occur as we have stripped trailing spaces off the line.  Just treat
        // this as a single-token error for simplicity's sake.
        throw MessageException(MSG_ONETOKEN, text);
    }

    // Add the result to the dictionary and to the non-added list if the add to
    // the dictionary fails.
    bool added;
    if (mode == ADD) {
        added = dictionary_->add(ident, text.substr(first_text));
    }
    else {
        added = dictionary_->replace(ident, text.substr(first_text));
    }
    if (! added) {
        not_added_.push_back(ident);
    }
}

} // namespace log
} // namespace isc
