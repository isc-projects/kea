// Copyright (C) 2011, 2015  Internet Systems Consortium, Inc. ("ISC")
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

#define KEA_LOG_EXPORT

#include <config.h>
#include <log/message_dictionary.h>
#include <log/message_initializer.h>
#include <boost/array.hpp>
#include <algorithm>
#include <cassert>
#include <cstdlib>


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

/// Type definition for the list of pointers to messages.
typedef std::list<const char**> LoggerValuesList;

/// Return reference to the list of log messages.
LoggerValuesList& getNonConstLoggerValues() {
    static LoggerValuesList logger_values;
    return (logger_values);
}

// Return the duplicates singleton version (non-const for local use)
std::list<std::string>&
getNonConstDuplicates() {
    static std::list<std::string> duplicates;
    return (duplicates);
}
} // end unnamed namespace


namespace isc {
namespace log {

// Constructor.  Add the pointer to the message array to the global array.
// This method will trigger an assertion failure if the array overflows.

MessageInitializer::MessageInitializer(const char* values[])
    : values_(values),
      global_dictionary_(MessageDictionary::globalDictionary()) {
    assert(getNonConstLoggerValues().size() < MAX_MESSAGE_ARRAYS);
    getNonConstLoggerValues().push_back(values);
}

MessageInitializer::~MessageInitializer() {
    LoggerValuesList& logger_values = getNonConstLoggerValues();

    // Search for the pointer to pending messages belonging to our instance.
    LoggerValuesList::iterator my_messages = std::find(logger_values.begin(),
                                                       logger_values.end(),
                                                       values_);
    bool pending = (my_messages != logger_values.end());
    // Our messages are still pending, so let's remove them from the list
    // of pending messages.
    if (pending) {
        logger_values.erase(my_messages);

    } else {
        // Our messages are not pending, so they might have been loaded to
        // the dictionary and/or duplicates.
        int i = 0;
        while (values_[i]) {
            getNonConstDuplicates().remove(values_[i]);
            global_dictionary_->erase(values_[i], values_[i + 1]);
            i += 2;
        }
    }
}

// Return the number of arrays registered but not yet loaded.

size_t
MessageInitializer::getPendingCount() {
    return (getNonConstLoggerValues().size());
}

// Load the messages in the arrays registered in the logger_values array
// into the global dictionary.

void
MessageInitializer::loadDictionary(bool ignore_duplicates) {
    const MessageDictionaryPtr& global = MessageDictionary::globalDictionary();
    LoggerValuesList& logger_values = getNonConstLoggerValues(); 

    for (LoggerValuesList::const_iterator values = logger_values.begin();
         values != logger_values.end(); ++values) {
        std::vector<std::string> repeats = global->load(*values);

        // Append the IDs in the list just loaded (the "repeats") to the
        // global list of duplicate IDs.
        if (!ignore_duplicates && !repeats.empty()) {
            std::list<std::string>& duplicates = getNonConstDuplicates();
            duplicates.insert(duplicates.end(), repeats.begin(),
                              repeats.end());
        }
    }

    // ... and mark that the messages have been loaded.  (This avoids a lot
    // of "duplicate message ID" messages in some of the unit tests where the
    // logging initialization code may be called multiple times.)
    logger_values.clear();
}

// Return reference to duplicates vector
const std::list<std::string>&
MessageInitializer::getDuplicates() {
    return (getNonConstDuplicates());
}

// Clear the duplicates vector
void
MessageInitializer::clearDuplicates() {
    getNonConstDuplicates().clear();
}

} // namespace log
} // namespace isc
