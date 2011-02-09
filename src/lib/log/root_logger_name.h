// Copyright (C) 2010  Internet Systems Consortium, Inc. ("ISC")
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

#ifndef __ROOT_LOGGER_NAME_H
#define __ROOT_LOGGER_NAME_H

#include <string>

/// \brief Define Name of Root Logger
///
/// In the log4cxx system, the root logger is ".".  The definition for the
/// BIND-10 system is that the root logger of a program has the name of the
/// program.  This (trivial) class stores the name of the program in a
/// location accessible to the logger classes.

namespace isc {
namespace log {

class RootLoggerName {
public:

    /// \brief Constructor
    ///
    /// Sets the root logger name.  Although the name is static, setting the
    /// name in the constructor allows static initialization of the name by
    /// declaring an external instance of the class in the main execution unit.
    RootLoggerName(const std::string& name) {
        setName(name);
    } 

    /// \brief Set Root Logger Name
    ///
    /// \param name Name of the root logger.  This should be the program
    /// name.
    static void setName(const std::string& name) {
        rootName() = name;
    }

    /// \brief Get Root Logger Name
    ///
    /// \return Name of the root logger.
    static std::string getName() {
        return (rootName());
    }
    
private:
    /// \brief Store Root Logger Name
    ///
    /// Access the singleton root logger name.  This is stored as a static
    /// variable inside a method to avoid the "static initialization fiasco";
    /// when accessed by another class during initialization, the name will be
    /// instantiated. (Else it will be only by chance that it is instantiated
    /// before the cassling class.)
    ///
    /// \return Name addisnged to the root logger.
    static std::string& rootName();
};

}
}

#endif // __ROOT_LOGGER_NAME_H
