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

// $Id$

#ifndef __FILENAME_H
#define __FILENAME_H

#include <string>

#include <strutil.h>

namespace isc {
namespace log {

/// \brief Class to Manipulate Filenames
///
/// This is a utility class to manipulate filenames.  It repeats some of the
/// features found in the Boost filename class, but is self-contained so avoids
/// the need to link in the Boost library.
///
/// A Unix-style filename comprises three parts:
///
/// Directory - everything up to and including the last "/".  If there is no
/// "/" in the string, there is no directory component.  Note that the
/// requirement of a trailing slash eliminates the ambiguity of whether a
/// component is a directory or not, e.g. in /alpha/beta", "beta" could be the
/// name of a directory or is could be a file.  The interpretation here is that
/// "beta" is the name of a file (although that file could be a directory).
///
/// Note: Under Windows, the drive letter is considered to be part of the
/// directory specification.  Unless this class becomes more widely-used on
/// Windows, there is no point in adding redundant code.
///
/// Name - everthing from the character after the last "/" up to but not
/// including the last ".".
///
/// Extension - everthing from the right-most "." (after the right-most "/") to
/// the end of the string.  If there is no "." after the last "/", there is
/// no file extension.
///
/// (Note that on Windows, this function will replace all "\" characters
/// with "/" characters on input strings.)
///
/// This class provides functions for extracting the components and for
/// substituting components.


class Filename {
public:

    /// \brief Constructor
    Filename(const std::string& name) :
        full_name_(""), directory_(""), name_(""), extension_("")
    {
        setName(name);
    }

    /// \brief Sets Stored Filename
    ///
    /// \param name New name to replaced currently stored name
    void setName(const std::string& name) {
        full_name_ = isc::strutil::trim(name);
#ifdef WIN32
        isc::strutil::normalizeSlash(full_name_);
#endif
        split(full_name_, directory_, name_, extension_);
    }

    /// \return Stored Filename
    std::string fullName() const {
        return full_name_;
    }

    /// \return Directory of Given File Name
    std::string directory() const {
        return directory_;
    }

    /// \return Name of Given File Name
    std::string name() const {
        return name_;
    }

    /// \return Extension of Given File Name
    std::string extension() const {
        return extension_;
    }

    /// \brief Expand Name with Default
    ///
    /// A default file specified is supplied and used to fill in any missing
    /// fields.  For example, if the name stored is "/a/b" and the supplied
    /// name is "c.d", the result is "/a/b.d": the only field missing from the
    /// stored name is the extension, which is supplied by the default.
    /// Another example would be to store "a.b" and to supply a default of
    /// "/c/d/" - the result is "/c/d/a.b".  (Note that if the supplied default
    /// was "/c/d", the result would be "/c/a.b", even if "/c/d" were actually
    /// a directory.)
    ///
    /// \param defname Default name
    ///
    /// \return Name expanded with defname.
    std::string expandWithDefault(const std::string& defname) const;

    /// \brief Use as Default and Substitute into String
    ///
    /// Does essentially the inverse of expand(); that filled in the stored
    /// name with a default and returned the result.  This treats the stored
    /// name as the default and uses it to fill in a given name.  In essence,
    /// the code:
    /// \code
    ///       Filename f("/a/b");
    ///       result = f.expandWithdefault("c.d");
    /// \endcode
    /// gives as a result "/a/b.d".  This is the same as:
    /// \code
    ///       Filename f("c.d");
    ///       result = f.useAsDefault("/a/b");
    /// \endcode
    ///
    /// \param name Name to expand
    ///
    /// \return Name expanded with stored name
    std::string useAsDefault(const std::string&) const;

private:
    /// \brief Split Name into Components
    ///
    /// Splits the file name into the directory, name and extension parts.
    /// The name is assumed to have had back slashes replaced by forward
    /// slashes (if appropriate).
    ///
    /// \param full_name Name to split
    /// \param directory Returned directory part
    /// \param name Returned name part
    /// \param extension Returned extension part
    void split(const std::string& full_name, std::string& directory,
       std::string& name, std::string& extension) const;

    // Members

    std::string full_name_;     ///< Given name
    std::string directory_;     ///< Directory part
    std::string name_;          ///< Name part
    std::string extension_;     ///< Extension part
};

} // namespace log
} // namespace isc

#endif // __FILENAME_H
