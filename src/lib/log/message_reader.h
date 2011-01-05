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

#ifndef __MESSAGE_READER_H
#define __MESSAGE_READER_H

#include <iostream>
#include <map>
#include <string>
#include <vector>

namespace isc {
namespace log {

/// \brief Read Message File
///
/// Reads a message file and creates a map of identifier against the text of the
/// message.  This map can be retrieved for subsequent processing.

class MessageReader {
public:

    /// \brief Status Returns
    ///
    /// It may seem odd that a class devoted to reading logfile messages does
    /// not have its own set of messages.  The reason is that this class is
    /// used in both the server and in the message compiler.  The latter is
    /// a stand-along program used to create message files, so at the time this
    /// file is compiled, there is nothing to build an associated message file.
    typedef enum {
        SUCCESS,                // Success, all OK.
        DUPLPRFX,               // Error, duplicate prefix found
        OPENIN,                 // Error openinin input file
        PRFXEXTRARG,            // Error, $PREFIX directive has extra arguments
        PRFXINVARG,             // Error, $PREFIX has invalid argument
        PRFXNOARG,              // Error, $PREFIX directive has no arguments
        UNRECDIR                // Error, unrecognised directive

    } Status;                   // Status code

    /// \brief Other Types
    typedef std::map<std::string, std::string>  MessageMap;
    typedef std::vector<std::string>            MessageDuplicates;

    /// \brief Constructor
    ///
    /// Default constructor.  All work is done in the main readFile code (so
    /// that a status return can be returned instead of needing to throw an
    /// exception).
    MessageReader() : messages_(), duplicates_()
    {}

    /// \brief Virtual Destructor
    virtual ~MessageReader();

    /// \brief Return Error Text
    ///
    /// Returns the message associated with the error code
    ///
    /// \param status Status code for which a message is required
    ///
    /// \return Text of the error.
    virtual std::string errorText(Status status);


    /// \brief Read File
    ///
    /// This is the main method of the class and reads in the file, parses it,
    /// and stores the result in the message map.
    ///
    /// \param file Name of the message file.
    ///
    /// \return Status return.  Should be SUCCESS, else an error has occurred.
    virtual Status readFile(const std::string& file);


    /// \brief Clears Message Mapgit find new files
    ///
    /// In the event of an instance of the class needing to be reused, this
    /// method will clear the message map and the list of duplicated.
    virtual void clear();


    /// \brief Process Line
    ///
    /// Parses a text line and adds it to the message map.  Although this is
    /// for use in readFile, it can also be used to add individual messages
    /// to the message map.
    ///
    /// \param line Line of text to process
    ///
    /// \return Status return
    virtual Status processLine(const std::string& line);


    /// \brief Return Message Map
    ///
    /// Returns the message map.
    ///
    /// \return Returns a copy of the internal map.
    /// TODO: Usse a reference?
    virtual MessageMap getMessageMap() const {
        return messages_;
    }

    /// \brief Return Message Duplicates
    ///
    /// Returns a copy of the duplicates vector.
    ///
    /// \return Copy of the duplicates vector
    virtual MessageDuplicates getMessageDuplicates() {
        return duplicates_;
    }

    /// \brief Get Prefix
    ///
    /// \return Argument to the $PREFIX directive (if present)
    virtual std::string getPrefix() const {
        return prefix_;
    }

private:

    /// \brief Handle Directive
    ///
    /// Passed a line starting with a "$", this handles the processing of
    /// directives.
    ///
    /// \param line Line of text that starts with "$",
    ///
    /// \return Status return code.  NORMAL implies success
    Status directive(const std::string& line);

    /// Attributes
    MessageMap          messages_;      // Message map
    MessageDuplicates   duplicates_;    // Duplicate messages
    std::string         prefix_;        // Input of $PREFIX statement
};

} // namespace log
} // namespace isc

#endif // __MESSAGE_READER_H
