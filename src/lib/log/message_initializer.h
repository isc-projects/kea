// Copyright (C) 2011-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef MESSAGEINITIALIZER_H
#define MESSAGEINITIALIZER_H

#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <cstdlib>
#include <list>
#include <string>

namespace isc {
namespace log {

// Declare the MessageDictionary class to allow a pointer to it to be defined.
class MessageDictionary;

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
/// It should be declared outside an execution unit and initialized with
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
/// of the class are destructed. After the object has been created with the
/// constructor, the \c MessageInitializer::loadDictionary static function is
/// called to populate the messages defined in various instances of the
/// \c MessageInitializer class to the global dictionary.
///
/// When messages are added to the dictionary, the are added via the
/// MessageDictionary::add() method, so any duplicates are stored in the
/// global dictionary's overflow lince whence they can be retrieved at
/// run-time.

class MessageInitializer : public boost::noncopyable {
public:

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
    /// One or more instances of \c MessageInitializer are created statically,
    /// the \c MessageDictionary being created by the first one to run. As the
    /// \c MessageDictionary is also accessed by the \c MessageInitializer
    /// destructor, a smart pointer to it is kept.  This avoids the possibility
    /// that, during shutdown, the \c MessageDictionary is destroyed before all
    /// instances of \c MessageInitializer.
    boost::shared_ptr<MessageDictionary> global_dictionary_;

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
