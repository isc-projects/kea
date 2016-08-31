// Copyright (C) 2011-2016 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef MESSAGE_DICTIONARY_H
#define MESSAGE_DICTIONARY_H

#include <cstddef>
#include <string>
#include <map>
#include <vector>

#include <boost/lexical_cast.hpp>
#include <boost/shared_ptr.hpp>

#include <log/message_types.h>

namespace isc {
namespace log {

/// \brief Forward declaration of \c MessageDictionary
class MessageDictionary;

/// \brief Shared pointer to the \c MessageDictionary.
typedef boost::shared_ptr<MessageDictionary> MessageDictionaryPtr;

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

    typedef std::map<std::string, std::string> Dictionary;
    typedef Dictionary::const_iterator  const_iterator;

    /// \brief Constructor
    MessageDictionary();

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
    virtual bool add(const MessageID& ident, const std::string& text) {
        return (add(boost::lexical_cast<std::string>(ident), text));
    }

    /// \brief Add Message
    ///
    /// Alternate signature.
    ///
    /// \param ident Identification of the message to add
    /// \param text Message text
    ///
    /// \return true if the message was added to the dictionary, false if the
    /// message existed and it was not added.
    virtual bool add (const std::string& ident, const std::string& text);


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
    virtual bool replace(const MessageID& ident, const std::string& text) {
        return (replace(boost::lexical_cast<std::string>(ident), text));
    }

    /// \brief Replace Message
    ///
    /// Alternate signature.
    ///
    /// \param ident Identification of the message to replace
    /// \param text Message text
    ///
    /// \return true if the message was added to the dictionary, false if the
    /// message did not exist and it was not added.
    virtual bool replace(const std::string& ident, const std::string& text);


    /// \brief Removes the specified message from the dictionary.
    ///
    /// Checks if both the message identifier and the text match the message
    /// in the dictionary before removal. If the text doesn't match it is
    /// an indication that the message which removal is requested is a
    /// duplicate of another message. This may occur when two Kea modules
    /// register messages with the same identifier. When one of the modules
    /// is unloaded and the relevant messages are unregistered, there is a
    /// need to make sure that the message registered by the other module
    /// is not accidentally removed. Hence, the additional check for the
    /// text match is needed.
    ///
    /// \param ident Identification of the message to remove.
    /// \param text Message text
    ///
    /// \return true of the message has been removed, false if the message
    /// couldn't be found.
    virtual bool erase(const std::string& ident, const std::string& text);

    /// \brief Load Dictionary
    ///
    /// Designed to be used during the initialization of programs, this
    /// accepts a set of (ID, text) pairs as a one-dimensional array of
    /// const char* and adds them to the dictionary.  The messages are added
    /// using "Add".
    ///
    /// \param elements null-terminated array of const char* alternating ID and
    /// message text.  This should be an odd number of elements long, the last
    /// element being NULL.  If it is an even number of elements long, the
    /// last ID is ignored.
    ///
    /// \return Vector of message IDs that were not loaded because an ID of the
    /// same name already existing in the dictionary.  This vector may be
    /// empty.
    virtual std::vector<std::string> load(const char* elements[]);

    /// \brief Get Message Text
    ///
    /// Given an ID, retrieve associated message text.
    ///
    /// \param ident Message identification
    ///
    /// \return Text associated with message or empty string if the ID is not
    /// recognized.  (Note: this precludes an ID being associated with an empty
    /// string.)
    virtual const std::string& getText(const MessageID& ident) const {
        return(getText(boost::lexical_cast<std::string>(ident)));
    }


    /// \brief Get Message Text
    ///
    /// Alternate signature.
    ///
    /// \param ident Message identification
    ///
    /// \return Text associated with message or empty string if the ID is not
    /// recognized.  (Note: this precludes an ID being associated with an empty
    /// string.)
    virtual const std::string& getText(const std::string& ident) const;


    /// \brief Number of Items in Dictionary
    ///
    /// \return Number of items in the dictionary
    virtual size_t size() const {
        return (dictionary_.size());
    }


    /// \brief Return begin() iterator of internal map
    const_iterator begin() const {
        return (dictionary_.begin());
    }


    /// \brief Return end() iterator of internal map
    const_iterator end() const {
        return (dictionary_.end());
    }


    /// \brief Return Global Dictionary
    ///
    /// Returns a pointer to the singleton global dictionary.
    ///
    /// \return Pointer to global dictionary.
    static const MessageDictionaryPtr& globalDictionary();

private:
    Dictionary       dictionary_;   ///< Holds the ID to text lookups
    const std::string empty_;       ///< Empty string
};

} // namespace log
} // namespace isc

#endif // MESSAGE_DICTIONARY_H
