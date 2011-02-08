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

#ifndef __MESSAGE_DICTIONARY_H
#define __MESSAGE_DICTIONARY_H

#include <cstddef>
#include <string>
#include <map>
#include <vector>

#include <log/message_types.h>

namespace isc {
namespace log {

/// \brief Message Dictionary
///
/// The message dictionary is a wrapper around a std::map object, and allows
/// message text to be retrieved given the string identification.
///
/// Adding text occurs in two modes:
///
/// Through the "Add" method, ID/text mappings are added to the dictionary
/// unless the ID already exists.  This is designed for use during program
/// initialization, where a local message may supplant a compiled-in message.
///
/// Through the "Replace" method, ID/text mappings are added to the dictionary
/// only if the ID already exists.  This is for use when a message file is
/// supplied to replace messages provided with the program.
///
/// Although the class can be used stand-alone, it does supply a static method
/// to return a particular instance - the "global" dictionary.

class MessageDictionary {
public:

    // Default constructor and assignment operator are OK for this class

    /// \brief Virtual Destructor
    virtual ~MessageDictionary();

    /// \brief Add Message
    ///
    /// Adds a message to the dictionary.  If the ID already exists, the ID is
    /// added to the overflow vector.
    ///
    /// \param ident Identification of the message to add
    /// \param text Message text
    ///
    /// \return true if the message was added to the dictionary, false if the
    /// message existed and it was not added.
    virtual bool add(const MessageID& ident, const std::string& text);


    /// \brief Replace Message
    ///
    /// Replaces a message in the dictionary.  If the ID does not exist, it is
    /// added to the overflow vector.
    ///
    /// \param ident Identification of the message to replace
    /// \param text Message text
    ///
    /// \return true if the message was added to the dictionary, false if the
    /// message did not exist and it was not added.
    virtual bool replace(const MessageID& ident, const std::string& text);


    /// \brief Load Dictionary
    ///
    /// Designed to be used during the initialization of programs, this
    /// accepts a set of (ID, text) pairs as a one-dimensional array of
    /// const char* and adds them to the dictionary.  The messages are added
    /// using "Add".
    ///
    /// \param elements null-terminated array of const char* alternating ID and
    /// message text.  This should be an odd number of elements long, the last
    /// elemnent being NULL.  If it is an even number of elements long, the
    /// last ID is ignored.
    ///
    /// \return Vector of message IDs that were not loaded because an ID of the
    /// same name already existing in the dictionary.  This vector may be
    /// empty.
    virtual std::vector<MessageID> load(const char* elements[]);


    /// \brief Get Message Text
    ///
    /// Given an ID, retrieve associated message text.
    ///
    /// \param ident Message identification
    ///
    /// \return Text associated with message or empty string if the ID is not
    /// recognised.  (Note: this precludes an ID being associated with an empty
    /// string.)
    virtual std::string getText(const MessageID& ident) const;


    /// \brief Number of Items in Dictionary
    ///
    /// \return Number of items in the dictionary
    virtual size_t size() const {
        return dictionary_.size();
    }


    // Allow access to the internal map structure, but don't allow alteration.
    typedef std::map<MessageID, std::string>::const_iterator const_iterator;


    /// \brief Return begin() iterator of internal map
    const_iterator begin() const {
        return dictionary_.begin();
    }


    /// \brief Return end() iterator of internal map
    const_iterator end() const {
        return dictionary_.end();
    }


    /// \brief Return Global Dictionary
    ///
    /// Returns a pointer to the singleton global dictionary.
    ///
    /// \return Pointer to global dictionary.
    static MessageDictionary* globalDictionary();

private:
    std::map<MessageID, std::string>  dictionary_;
};

} // namespace log
} // namespace isc

#endif // __MESSAGE_DICTIONARY_H
