// Copyright (C) 2011,2015 Internet Systems Consortium, Inc. ("ISC")
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

#ifndef MESSAGEINITIALIZER_H
#define MESSAGEINITIALIZER_H

#include <log/message_dictionary.h>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <cstdlib>
#include <list>
#include <string>

namespace isc {
namespace log {

/// @name Type definitions for containers shared among instances of the class.
///
//\{
/// \brief List of pointers to the messages.
typedef std::list<const char**> LoggerValuesList;
/// \brief Shared pointer to the list of pointers to the messages.
typedef boost::shared_ptr<LoggerValuesList> LoggerValuesListPtr;

/// \brief List of duplicated messages.
typedef std::list<std::string> LoggerDuplicatesList;
/// \brief Shared pointer to the list of duplicated messages.
typedef boost::shared_ptr<LoggerDuplicatesList> LoggerDuplicatesListPtr;
//\}

/// \brief Initialize Message Dictionary
///
/// This is a helper class to add a set of message IDs and associated text to
/// the global dictionary.
///
/// It should be declared outside an execution unit and initialized with a
/// an array of values, alternating identifier, associated text and ending with
/// a NULL, e.g.
///
///     static const char* values[] = {
///         "IDENT1", "message for ident 1",
///         "IDENT2", "message for ident 2",
///             :
///         NULL
///     };
///     MessageInitializer xyz(values);
///
/// All that needed is for the module containing the definitions to be
/// included in the execution unit.
///
/// Dynamically loaded modules should call the initializer as well on the
/// moment they are instantiated.
///
/// To avoid static initialization fiasco problems, the containers shared by
/// all instances of this class are dynamically allocated on first use, and
/// held in the smart pointers which are de-allocated only when all instances
/// of the class are destructred. After the object has been created with the
/// constructor, the \c MessageInitializer::loadDictionary static function is
/// called to populate the messages defined in various instances of the
/// \c MessageInitializer class to the global dictionary.
///
/// \note The maximum number of message arrays that can be added to the
/// dictionary in this way is defined by the constant
/// MessageInitializer::MAX_MESSAGE_ARRAYS.  This is set to 256 as a compromise
/// between wasted space and allowing for future expansion, but can be
/// changed (by editing the source file) to any value desired.
///
/// When messages are added to the dictionary, the are added via the
/// MessageDictionary::add() method, so any duplicates are stored in the
/// global dictionary's overflow lince whence they can be retrieved at
/// run-time.

class MessageInitializer : public boost::noncopyable {
public:
    /// Maximum number of message arrays that can be initialized in this way
    static const size_t MAX_MESSAGE_ARRAYS = 256;

    /// \brief Constructor
    ///
    /// Adds a pointer to the array of messages to the global array of
    /// pointers to message arrays.
    ///
    /// \param values NULL-terminated array of alternating identifier strings
    /// and associated message text. N.B. This object stores a pointer to the
    /// passed array; the array MUST remain valid at least until
    /// loadDictionary() has been called.
    MessageInitializer(const char* values[]);

    /// \brief Destructor
    ///
    /// Removes pending messages from the array or loaded messages from the
    /// global dictionary.
    ///
    /// If the messages initialized with the destructed have already been
    /// loaded to the global dictionary the destructor will remove these
    /// messages and preserve messages loaded by other instances of the
    /// \c MessageInitializer. If there are any duplicates, only the instance
    /// of the duplicated message initialized by the destructed object will
    /// be removed.
    ~MessageInitializer();

    /// \brief Obtain pending load count
    ///
    /// Returns the number of message arrays that will be loaded by the next
    /// call to loadDictionary().
    ///
    /// \return Number of registered message arrays.  This is reset to zero
    ///         when loadDictionary() is called.
    static size_t getPendingCount();

    /// \brief Run-Time Initialization
    ///
    /// Loops through the internal array of pointers to message arrays
    /// and adds the messages to the internal dictionary.  This is called
    /// during run-time initialization.
    ///
    /// \param ignore_duplicates If true, duplicate IDs, and IDs already
    ///        loaded, are ignored instead of stored in the global duplicates
    ///        list.
    static void loadDictionary(bool ignore_duplicates = false);

    /// \brief Return Duplicates
    ///
    /// When messages are added to the global dictionary, any duplicates are
    /// recorded.  They can later be output through the logging system.
    ///
    /// \return List of duplicate message IDs when the global dictionary was
    /// loaded.  Note that the duplicates list itself may contain duplicates.
    static const std::list<std::string>& getDuplicates();

    /// \brief Clear the static duplicates list
    ///
    /// Empties the list returned by getDuplicates()
    static void clearDuplicates();

private:

    /// \brief Holds the pointer to the array of messages.
    const char** values_;

    /// \brief Holds the pointer to the global dictionary.
    ///
    /// The \c MessageInitializer instantiates the global dictionary and
    /// keeps the reference to it throughout its lifetime as the global
    /// dictionary is instantiated in the destructor. If the reference is
    /// not held then it is possible that the global dictionary is destroyed
    /// before the \c MessageInitializer destructor is called, causing the
    /// static initialization order fiasco.
    MessageDictionaryPtr global_dictionary_;

    /// \brief Holds the shared pointer to the list of pointers to the
    /// log messages defined by various instances of this class.
    ///
    /// This pointer must be initialized in the constructor and held
    /// throughout the lifetime of the \c MessageInitializer object. This
    /// prevents static deinitialization fiasco when trying to access the
    /// values in the list from the destructor of this class.
    LoggerValuesListPtr global_logger_values_;

    /// \brief Holds the shared pointer to the collection od duplicated
    /// messages.
    ///
    /// This pointer must be initialized in the constructor and held
    /// throughout the lifetime of the \c MessageInitializer object. This
    /// prevents static deinitialization fiasco when trying to access the
    /// values in the list from the destructor of this class.
    LoggerDuplicatesListPtr global_logger_duplicates_;
};

} // namespace log
} // namespace isc

#endif // MESSAGEINITIALIZER_H
