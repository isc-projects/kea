// Copyright (C) 2011-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef MESSAGE_READER_H
#define MESSAGE_READER_H

#include <map>
#include <string>
#include <vector>

#include <log/message_dictionary.h>
#include <log/message_types.h>

namespace isc {
namespace log {

/// \brief Read Message File
///
/// Reads a message file and creates a map of identifier against the text of the
/// message.  This map can be retrieved for subsequent processing.

class MessageReader {
public:

    /// \brief Read Mode
    ///
    /// If ADD, messages are added to the dictionary if the ID does not exist
    /// there.  If it does, the ID is added to the dictionary's overflow
    /// vector.
    ///
    /// If REPLACE, the dictionary is only modified if the message ID already
    /// exists in it.  New message IDs are added to the overflow vector.
    typedef enum {
        ADD,
        REPLACE
    } Mode;

    /// \brief Visible collection types
    typedef std::vector<std::string>   MessageIDCollection;

    /// \brief Constructor
    ///
    /// Default constructor.  All work is done in the main readFile code (so
    /// that a status return can be returned instead of needing to throw an
    /// exception).
    ///
    /// \param dictionary Dictionary to which messages read read from the file
    /// are added.  (This should be a local dictionary when the class is used in
    /// the message compiler, and the global dictionary when used in a server.
    /// The ownership of the dictionary object is not transferred - the caller
    /// is responsible for managing the lifetime of the dictionary.
    MessageReader(MessageDictionary* dictionary = NULL) :
        dictionary_(dictionary), lineno_(0)
    {}

    /// \brief Virtual Destructor
    virtual ~MessageReader()
    {}

    /// \brief Get Dictionary
    ///
    /// Returns the pointer to the dictionary object.  Note that ownership is
    /// not transferred - the caller should not delete it.
    ///
    /// \return Pointer to current dictionary object
    MessageDictionary* getDictionary() const {
        return (dictionary_);
    }


    /// \brief Set Dictionary
    ///
    /// Sets the current dictionary object.
    ///
    /// \param dictionary New dictionary object. The ownership of the dictionary
    /// object is not transferred - the caller is responsible for managing the
    /// lifetime of the dictionary.
    void setDictionary(MessageDictionary* dictionary) {
        dictionary_ = dictionary;
    }


    /// \brief Read File
    ///
    /// This is the main method of the class and reads in the file, parses it,
    /// and stores the result in the message dictionary.
    ///
    /// \param file Name of the message file.
    /// \param mode Addition mode.  See the description of the "Mode" enum.
    virtual void readFile(const std::string& file, Mode mode = ADD);


    /// \brief Process Line
    ///
    /// Parses a text line and adds it to the message map.  Although this is
    /// for use in readFile, it can also be used to add individual messages
    /// to the message map.
    ///
    /// \param line Line of text to process
    /// \param mode If a message line, how to add the message to the dictionary.
    virtual void processLine(const std::string& line, Mode mode = ADD);


    /// \brief Get Namespace
    ///
    /// \return Argument to the $NAMESPACE directive (if present)
    virtual std::string getNamespace() const {
        return (ns_);
    }


    /// \brief Clear Namespace
    ///
    /// Clears the current namespace.
    virtual void clearNamespace() {
        ns_ = "";
    }


    /// \brief Get Prefix
    ///
    /// \return Argument to the $PREFIX directive (if present)
    virtual std::string getPrefix() const {
        return (prefix_);
    }


    /// \brief Clear Prefix
    ///
    /// Clears the current prefix.
    virtual void clearPrefix() {
        prefix_ = "";
    }


    /// \brief Get Not-Added List
    ///
    /// Returns the list of IDs that were not added during the last
    /// read of the file.
    ///
    /// \return Collection of messages not added
    MessageIDCollection getNotAdded() const {
        return (not_added_);
    }

private:

    /// \brief Handle a Message Definition
    ///
    /// Passed a line that should contain a message, this processes that line
    /// and adds it to the dictionary according to the mode setting.
    ///
    /// \param line Line of text
    /// \param ADD or REPLACE depending on how the reader is operating.  (See
    /// the description of the Mode typedef for details.)
    void parseMessage(const std::string& line, Mode mode);


    /// \brief Handle Directive
    ///
    /// Passed a line starting with a "$", this handles the processing of
    /// directives.
    ///
    /// \param line Line of text that starts with "$",
    void parseDirective(const std::string& line);


    /// \brief Parse $PREFIX line
    ///
    /// \param tokens $PREFIX line split into tokens
    void parsePrefix(const std::vector<std::string>& tokens);


    /// \brief Parse $NAMESPACE line
    ///
    /// \param tokens $NAMESPACE line split into tokens
    void parseNamespace(const std::vector<std::string>& tokens);

    /// \brief Check for invalid C++ symbol name
    ///
    /// The message ID (or concatenation of prefix and message ID) will be used
    /// as the name of a symbol in C++ code.  This function checks if the name
    /// is invalid (contains anything other than alphanumeric characters or
    /// underscores, or starts with a digit).
    ///
    /// \param symbol name to check to see if it is an invalid C++ symbol.
    ///
    /// \return true if the name is invalid, false if it is valid.
    bool invalidSymbol(const std::string& symbol);



    /// Attributes
    MessageDictionary*  dictionary_;    ///< Dictionary to add messages to
    MessageIDCollection not_added_;     ///< List of IDs not added
    int                 lineno_;        ///< Number of last line read
    std::string         prefix_;        ///< Argument of $PREFIX statement
    std::string         ns_;            ///< Argument of $NAMESPACE statement
};

} // namespace log
} // namespace isc

#endif // MESSAGE_READER_H
