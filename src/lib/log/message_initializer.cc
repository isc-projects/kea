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

#include <cassert>
#include <cstdlib>
#include <log/message_dictionary.h>
#include <log/message_initializer.h>


// As explained in the header file, initialization of the message dictionary
// is a two-stage process:
// 1) In the MessageInitializer constructor, a pointer to the array of
//    messages is stored in a pre-defined array.  Since the MessageInitializers
//    are declared statically outside a program unit, this takes place before
//    main() is called.  As no heap storage is allocated in this process, we
//    should avoid the static initialization fiasco in cases where
//    initialization of system libraries is also carried out at the same time.
// 2) After main() starts executing, loadDictionary() is called.
//
//

namespace {

// Declare the array of pointers to value arrays.
const char** logger_values[isc::log::MessageInitializer::MAX_MESSAGE_ARRAYS];

// Declare the index used to access the array.  As this needs to be initialized
// at first used, it is accessed it via a function.
size_t& getIndex() {
    static size_t index = 0;
    return (index);
}

}


namespace isc {
namespace log {

// Constructor.  Add the pointer to the message array to the global array.
// This method will trigger an assertion failure if the array overflows.

MessageInitializer::MessageInitializer(const char* values[]) {
    assert(getIndex() < MAX_MESSAGE_ARRAYS);
    logger_values[getIndex()++] = values;
}

// Return the number of arrays registered but not yet loaded.

size_t
MessageInitializer::getPendingCount() {
    return (getIndex());
}

// Load the messages in the arrays registered in the logger_values array
// into the global dictionary.

void
MessageInitializer::loadDictionary() {
    MessageDictionary& global = MessageDictionary::globalDictionary();

    for (size_t i = 0; i < getIndex(); ++i) {
        std::vector<std::string> repeats = global.load(logger_values[i]);

        // Append the IDs in the list just loaded (the "repeats") to the
        // global list of duplicate IDs.
        if (!repeats.empty()) {
            std::vector<std::string>& duplicates = getDuplicates();
            duplicates.insert(duplicates.end(), repeats.begin(),
                              repeats.end());
        }
    }

    // ... and mark that the messages have been loaded.  (This avoids a lot
    // of "duplicate message ID" messages in some of the unit tests where the
    // logging initialization code may be called multiple times.)
    getIndex() = 0;
}

// Return reference to duplicate array

std::vector<std::string>& MessageInitializer::getDuplicates() {
    static std::vector<std::string> duplicates;
    return (duplicates);
}

} // namespace log
} // namespace isc
