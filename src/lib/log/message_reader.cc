// Copyright (C) 2011, 2015  Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <cassert>
#include <errno.h>
#include <string.h>
#include <iostream>

#include <iostream>
#include <fstream>

#include <log/log_messages.h>
#include <log/message_exception.h>
#include <log/message_reader.h>
#include <util/strutil.h>

using namespace std;

namespace {
const char DIRECTIVE_FLAG = '$';    // Starts each directive
const char MESSAGE_FLAG = '%';      // Starts each message
}


namespace isc {
namespace log {

// Read the file.

void
MessageReader::readFile(const string& file, MessageReader::Mode mode) {

    // Ensure the non-added collection is empty: we could be re-using this
    // object.
    not_added_.clear();

    // Open the file.
    ifstream infile(file.c_str());
    if (infile.fail()) {
        isc_throw_4(MessageException, "Failed to open message file",
                    LOG_INPUT_OPEN_FAIL, file, strerror(errno), 0);
    }

    // Loop round reading it.  As we process the file one line at a time,
    // keep a track of line number of aid diagnosis of problems.
    string line;
    getline(infile, line);
    lineno_ = 0;

    while (infile.good()) {
        ++lineno_;
        processLine(line, mode);
        getline(infile, line);
    }

    // Why did the loop terminate?
    if (!infile.eof()) {
        isc_throw_4(MessageException, "Error reading message file",
                    LOG_READ_ERROR, file, strerror(errno), 0);
    }
    infile.close();
}

// Parse a line of the file.

void
MessageReader::processLine(const string& line, MessageReader::Mode mode) {

    // Get rid of leading and trailing spaces
    string text = isc::util::str::trim(line);

    if (text.empty()) {
        ;                           // Ignore blank lines

    } else if (text[0] == DIRECTIVE_FLAG) {
        parseDirective(text);       // Process directives


    } else if (text[0] == MESSAGE_FLAG) {
        parseMessage(text, mode);   // Process message definition line

    } else {
        ;                           // Other lines are extended message
                                    // description so are ignored
    }
}

// Process directive

void
MessageReader::parseDirective(const std::string& text) {


    // Break into tokens
    vector<string> tokens = isc::util::str::tokens(text);

    // Uppercase directive and branch on valid ones
    isc::util::str::uppercase(tokens[0]);
    if (tokens[0] == string("$PREFIX")) {
        parsePrefix(tokens);

    } else if (tokens[0] == string("$NAMESPACE")) {
        parseNamespace(tokens);

    } else {

        // Unrecognized directive
        isc_throw_3(MessageException, "Unrecognized directive",
                    LOG_UNRECOGNIZED_DIRECTIVE, tokens[0],
                    lineno_);
    }
}

// Process $PREFIX
void
MessageReader::parsePrefix(const vector<string>& tokens) {

    // Should not get here unless there is something in the tokens array.
    assert(!tokens.empty());

    // Process $PREFIX.  With no arguments, the prefix is set to the empty
    // string.  One argument sets the prefix to the to its value and more than
    // one argument is invalid.
    if (tokens.size() == 1) {
        prefix_ = "";

    } else if (tokens.size() == 2) {
        prefix_ = tokens[1];

        // Token is potentially valid providing it only contains alphabetic
        // and numeric characters (and underscores) and does not start with a
        // digit.
        if (invalidSymbol(prefix_)) {
            isc_throw_3(MessageException, "Invalid prefix",
                        LOG_PREFIX_INVALID_ARG, prefix_, lineno_);
        }

    } else {

        // Too many arguments
        isc_throw_2(MessageException, "Too many arguments",
                    LOG_PREFIX_EXTRA_ARGS, lineno_);
    }
}

// Check if string is an invalid C++ symbol.  It is valid if comprises only
// alphanumeric characters and underscores, and does not start with a digit.
// (Owing to the logic of the rest of the code, we check for its invalidity,
// not its validity.)
bool
MessageReader::invalidSymbol(const string& symbol) {
    static const string valid_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                      "abcdefghijklmnopqrstuvwxyz"
                                      "0123456789_";
    return ( symbol.empty() ||
            (symbol.find_first_not_of(valid_chars) != string::npos) ||
            (std::isdigit(symbol[0])));
}

// Process $NAMESPACE.  A lot of the processing is similar to that of $PREFIX,
// except that only limited checks will be done on the namespace (to avoid a
// lot of parsing and separating out of the namespace components.)  Also, unlike
// $PREFIX, there can only be one $NAMESPACE in a file.

void
MessageReader::parseNamespace(const vector<string>& tokens) {

    // Check argument count
    if (tokens.size() < 2) {
        isc_throw_2(MessageException, "No arguments", LOG_NAMESPACE_NO_ARGS,
                    lineno_);

    } else if (tokens.size() > 2) {
        isc_throw_2(MessageException, "Too many arguments",
                    LOG_NAMESPACE_EXTRA_ARGS, lineno_);

    }

    // Token is potentially valid providing it only contains alphabetic
    // and numeric characters (and underscores and colons).  As noted above,
    // we won't be exhaustive - after all, and code containing the resultant
    // namespace will have to be compiled, and the compiler will catch errors.
    static const string valid_chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
                                      "abcdefghijklmnopqrstuvwxyz"
                                      "0123456789_:";
    if (tokens[1].find_first_not_of(valid_chars) != string::npos) {
        isc_throw_3(MessageException, "Invalid argument",
                    LOG_NAMESPACE_INVALID_ARG, tokens[1], lineno_);
    }

    // All OK - unless the namespace has already been set.
    if (ns_.size() != 0) {
        isc_throw_2(MessageException, "Duplicate namespace",
                    LOG_DUPLICATE_NAMESPACE, lineno_);
    }

    // Prefix has not been set, so set it and return success.
    ns_ = tokens[1];
}

// Process message.  By the time this method is called, the line has been
// stripped of leading and trailing spaces.  The first character of the string
// is the message introducer, so we can get rid of that.  The remainder is
// a line defining a message.
//
// The first token on the line, when concatenated to the prefix and converted to
// upper-case, is the message ID.  The first of the line from the next token
// on is the message text.

void
MessageReader::parseMessage(const std::string& text, MessageReader::Mode mode) {

    static string delimiters("\t\n ");   // Delimiters

    // The line passed should be at least one character long and start with the
    // message introducer (else we should not have got here).
    assert((text.size() >= 1) && (text[0] == MESSAGE_FLAG));

    // A line comprising just the message introducer is not valid.
    if (text.size() == 1) {
        isc_throw_3(MessageException, "No message ID", LOG_NO_MESSAGE_ID,
                    text, lineno_);
    }

    // Strip off the introducer and any leading space after that.
    string message_line = isc::util::str::trim(text.substr(1));

    // Look for the first delimiter.
    size_t first_delim = message_line.find_first_of(delimiters);
    if (first_delim == string::npos) {

        // Just a single token in the line - this is not valid
        isc_throw_3(MessageException, "No message text", LOG_NO_MESSAGE_TEXT,
                    message_line, lineno_);
    }

    // Extract the first token into the message ID, preceding it with the
    // current prefix, then convert to upper-case.  If the prefix is not set,
    // perform the valid character check now - the string will become a C++
    // symbol so we may as well identify problems early.
    string ident = prefix_ + message_line.substr(0, first_delim);
    if (prefix_.empty()) {
        if (invalidSymbol(ident)) {
            isc_throw_3(MessageException, "Invalid message ID",
                        LOG_INVALID_MESSAGE_ID, ident, lineno_);
        }
    }
    isc::util::str::uppercase(ident);

    // Locate the start of the message text
    size_t first_text = message_line.find_first_not_of(delimiters, first_delim);
    if (first_text == string::npos) {

        // ?? This happens if there are trailing delimiters, which should not
        // occur as we have stripped trailing spaces off the line.  Just treat
        // this as a single-token error for simplicity's sake.
        isc_throw_3(MessageException, "No message text", LOG_NO_MESSAGE_TEXT,
                    message_line, lineno_);
    }

    // Add the result to the dictionary and to the non-added list if the add to
    // the dictionary fails.
    bool added;
    if (mode == ADD) {
        added = dictionary_->add(ident, message_line.substr(first_text));
    }
    else {
        added = dictionary_->replace(ident, message_line.substr(first_text));
    }
    if (!added) {
        not_added_.push_back(ident);
    }
}

} // namespace log
} // namespace isc
