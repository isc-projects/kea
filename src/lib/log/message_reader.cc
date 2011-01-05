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

#include <log/message_reader.h>
#include <log/stringutil.h>

using namespace std;

namespace isc {
namespace log {

// Virtual destructor.
MessageReader::~MessageReader() {
}

// Return error text

string MessageReader::errorText(MessageReader::Status status) {
    switch (status) {
        case SUCCESS:
            return "Success";

        case DUPLPRFX:
            return "Error, duplicate $PREFIX directive found";

        case PRFXEXTRARG:
            return "Error, $PREFIX directive has extra arguments";

        case PRFXINVARG:
            return "Error, $PREFIX directive has an invalid argument";

        case PRFXNOARG:
            return "Error, $PREFIX directive has no arguments";

        case UNRECDIR:
            return "Error, unrecognised directive";

        default:
            return "Unknown message code";
    }
}

// Read the file

MessageReader::Status MessageReader::readFile(const string&) {
    return OPENIN;
}

// Clear the Message Map

void MessageReader::clear() {
}

// Parse a line of the file

MessageReader::Status MessageReader::processLine(const string& line) {

    // Get rid of leading and trailing spaces
    string text = StringUtil::trim(line);

    if (text.empty()) {
        return SUCCESS;             // Ignore blank lines

    } else if ((text[0] == '#') || (text[0] == '+')) {
        return SUCCESS;             // Ignore comments or descriptions

    } else if (text[0] == '$') {
        return directive(text);     // Process directives

    } else {
        return OPENIN;

    }
}

// Process directive

MessageReader::Status MessageReader::directive(const std::string& text) {

    static string valid = "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_";

    // Regardless of what happens, all prefixes will be uppercase (as will
    // all symbols).
    string line = text;
    StringUtil::uppercase(line);
    vector<string> tokens = StringUtil::tokens(line);

    // Only $PREFIX is recognised so far, so we'll handle it here.
    if (tokens[0] != string("$PREFIX")) {
        return UNRECDIR;            // Directive is not prefix

    } else if (tokens.size() < 2) {
        return PRFXNOARG;           // Does not have an argument

    } else if (tokens.size() > 2) {
        return PRFXEXTRARG;         // Too many arguments

    }

    // Token is potentially valid providing it only contains alphabetic
    // and numeric characters (and underscores) and does not start with a
    // digit.
    
    if ((tokens[1].find_first_not_of(valid) != string::npos) ||
        (std::isdigit(tokens[1][0]))) {

        // Invalid character in string opr it starts with a digit.
        return PRFXINVARG;
    }

    // All OK - unless the prefix has already been set.

    if (prefix_.size() != 0) {
        return DUPLPRFX;
    }

    // Prefix has not been set, so set it and return success.

    prefix_ = tokens[1];
    return SUCCESS;
}

} // namespace log
} // namespace isc
