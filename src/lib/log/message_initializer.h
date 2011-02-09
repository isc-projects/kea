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

#ifndef __MESSAGEINITIALIZER_H
#define __MESSAGEINITIALIZER_H

#include <log/message_dictionary.h>

namespace isc {
namespace log {

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
///     MessageDictionaryHelper xyz(values);
///
/// This will automatically add the message ID/text pairs to the global
/// dictionary during initialization - all that is required is that the module
/// containing the definition is included into the final executable.
///
/// Messages are added via the MessageDictionary::add() method, so any
/// duplicates are stored in the the global dictionary's overflow vector whence
/// they can be retrieved at run-time.

class MessageInitializer {
public:

    /// \brief Constructor
    ///
    /// The only method in the class, this adds the array of values to the
    /// global dictionary.
    MessageInitializer(const char* values[]);
};

/// \brief Instantiate Message Initializer
///
/// A problem with the MessageInitializer class is that an instance of it is
/// created in an external file and initialization of a set of messages requires
/// that that file be included in the link.  Unfortunately, if there is no
/// reference to the MessageInitializer object, we cannot guarantee that that
/// will be the case.\n
/// \n
/// The MessageInitializer object is created as a global object, so in theory
/// an "extern" reference to it should work.  However, that reference may well
/// be optimised away.  To overcome this, the MessageInstantiator class is
/// used.\n
/// \n
/// In the message header file, an instance of MessageInstantiator is created
/// that takes the extern reference to the MessageInitializer as its constructor
/// argument.  The constructor - declared in another file - is a no-op.  But as
/// the linker doesn't know, it must resolve the reference, hence pulling in the
/// file containing the MessageInitializer.
///\n
/// Note that there is no problem about the static initialization fiasco here -
/// a pointer to the MessageInitializer is passed to the MessageInstantiator,
/// not the object itself; at the MessageInstantiator does nothing with the
/// pointer and does not touch the MessageInitializer.  So it doesn't matter
/// whether or not the MessageInitializer's constructor has been called when the
/// MessageInstantiator runs.

class MessageInstantiator {
public:
    MessageInstantiator(MessageInitializer* dummy);
};

} // namespace log
} // namespace isc

#endif // __MESSAGEINITIALIZER_H
