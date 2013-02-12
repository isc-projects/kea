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

#ifndef RRCLASS_H
#define RRCLASS_H 1

#include <stdint.h>

#include <string>
#include <ostream>

#include <exceptions/exceptions.h>

#include <boost/optional.hpp>

namespace isc {
namespace util {
class InputBuffer;
class OutputBuffer;
}

namespace dns {

// forward declarations
class AbstractMessageRenderer;

class RRClass; // forward declaration to define MaybeRRClass.

/// \brief A shortcut for a compound type to represent RRClass-or-not.
///
/// A value of this type can be interpreted in a boolean context, whose
/// value is \c true if and only if it contains a valid RRClass object.
/// And, if it contains a valid RRClass object, its value is accessible
/// using \c operator*, just like a bare pointer to \c RRClass.
typedef boost::optional<RRClass> MaybeRRClass;

///
/// \brief A standard DNS module exception that is thrown if an RRClass object
/// is being constructed from an unrecognized string.
///
class InvalidRRClass : public Exception {
public:
    InvalidRRClass(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) {}
};

///
/// \brief A standard DNS module exception that is thrown if an RRClass object
/// is being constructed from a incomplete (too short) wire-format data.
///
class IncompleteRRClass : public Exception {
public:
    IncompleteRRClass(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) {}
};

///
/// The \c RRClass class encapsulates DNS resource record classes.
///
/// This class manages the 16-bit integer class codes in quite a straightforward
/// way.  The only non trivial task is to handle textual representations of
/// RR classes, such as "IN", "CH", or "CLASS65534".
///
/// This class consults a helper \c RRParamRegistry class, which is a registry
/// of RR related parameters and has the singleton object.  This registry
/// provides a mapping between RR class codes and their "well-known" textual
/// representations.
/// Parameters of RR classes defined by DNS protocol standards are automatically
/// registered at initialization time and are ensured to be always available for
/// applications unless the application explicitly modifies the registry.
///
/// For convenience, this class defines constant class objects corresponding to
/// standard RR classes.  These are generally referred to as the form of
/// <code>RRClass::{class-text}()</code>.
/// For example, \c RRClass::IN() is an \c RRClass object corresponding to the
/// IN class (class code 1).
/// Note that these constants are used through a "proxy" function.
/// This is because they may be used to initialize another non-local (e.g.
/// global or namespace-scope) static object as follows:
///
/// \code
/// namespace foo {
/// const RRClass default_class = RRClass::IN();
/// } \endcode
///
/// In order to ensure that the constant RRClass object has been initialized
/// before the initialization for \c default_class, we need help from
/// the proxy function.
///
/// Note to developers: same note as \c RRType applies.
class RRClass {
public:
    ///
    /// \name Constructors and Destructor
    ///
    //@{
    /// Constructor from an integer class code.
    ///
    /// This constructor never throws an exception.
    ///
    /// \param classcode An 16-bit integer code corresponding to the RRClass.
    explicit RRClass(uint16_t classcode) : classcode_(classcode) {}
    ///
    /// A valid string is one of "well-known" textual class representations
    /// such as "IN" or "CH", or in the standard format for "unknown"
    /// classes as defined in RFC3597, i.e., "CLASSnnnn".
    ///
    /// More precisely, the "well-known" representations are the ones stored
    /// in the \c RRParamRegistry registry (see the class description).
    ///
    /// As for the format of "CLASSnnnn", "nnnn" must represent a valid 16-bit
    /// unsigned integer, which may contain leading 0's as long as it consists
    /// of at most 5 characters (inclusive).
    /// For example, "CLASS1" and "CLASSS001" are valid and represent the same
    /// class, but "CLASS65536" and "CLASS000001" are invalid.
    /// A "CLASSnnnn" representation is valid even if the corresponding class
    /// code is registered in the \c RRParamRegistry object.  For example, both
    /// "IN" and "CLASS1" are valid and represent the same class.
    ///
    /// All of these representations are case insensitive; "IN" and "in", and
    /// "CLASS1" and "class1" are all valid and represent the same classes,
    /// respectively.
    ///
    /// If the given string is not recognized as a valid representation of
    /// an RR class, an exception of class \c InvalidRRClass will be thrown.
    ///
    /// \param class_str A string representation of the \c RRClass
    explicit RRClass(const std::string& class_str);
    /// Constructor from wire-format data.
    ///
    /// The \c buffer parameter normally stores a complete DNS message
    /// containing the RRClass to be constructed.  The current read position of
    /// the buffer points to the head of the class.
    ///
    /// If the given data does not large enough to contain a 16-bit integer,
    /// an exception of class \c IncompleteRRClass will be thrown.
    ///
    /// \param buffer A buffer storing the wire format data.
    explicit RRClass(isc::util::InputBuffer& buffer);

    /// A separate factory of RRClass from text.
    ///
    /// This static method is similar to the constructor that takes a
    /// string object, but works as a factory and reports parsing
    /// failure in the form of the return value.  Normally the
    /// constructor version should suffice, but in some cases the caller
    /// may have to expect mixture of valid and invalid input, and may
    /// want to minimize the overhead of possible exception handling.
    /// This version is provided for such purpose.
    ///
    /// For the format of the \c class_str argument, see the
    /// <code>RRClass(const std::string&)</code> constructor.
    ///
    /// If the given text represents a valid RRClass, it returns a
    /// \c MaybeRRClass object that stores a corresponding \c RRClass
    /// object, which is accessible via \c operator*().  In this case
    /// the returned object will be interpreted as \c true in a boolean
    /// context.  If the given text does not represent a valid RRClass,
    /// it returns a \c MaybeRRClass object which is interpreted as
    /// \c false in a boolean context.
    ///
    /// One main purpose of this function is to minimize the overhead
    /// when the given text does not represent a valid RR class.  For
    /// this reason this function intentionally omits the capability of
    /// delivering a detailed reason for the parse failure, such as in the
    /// \c want() string when exception is thrown from the constructor
    /// (it will internally require a creation of string object, which
    /// is relatively expensive).  If such detailed information is
    /// necessary, the constructor version should be used to catch the
    /// resulting exception.
    ///
    /// This function never throws the \c InvalidRRClass exception.
    ///
    /// \param class_str A string representation of the \c RRClass.
    /// \return A MaybeRRClass object either storing an RRClass object
    /// for the given text or a \c false value.
    static MaybeRRClass createFromText(const std::string& class_str);

    ///
    /// We use the default copy constructor intentionally.
    //@}
    /// We use the default copy assignment operator intentionally.
    ///

    ///
    /// \name Converter methods
    ///
    //@{
    /// \brief Convert the \c RRClass to a string.
    ///
    /// If a "well known" textual representation for the class code is
    /// registered in the RR parameter registry (see the class description),
    /// that will be used as the return value of this method.  Otherwise, this
    /// method creates a new string for an "unknown" class in the format defined
    /// in RFC3597, i.e., "CLASSnnnn", and returns it.
    ///
    /// If resource allocation for the string fails, a corresponding standard
    /// exception will be thrown.
    ///
    /// \return A string representation of the \c RRClass.
    const std::string toText() const;
    /// \brief Render the \c RRClass in the wire format.
    ///
    /// This method renders the class code in network byte order via
    /// \c renderer, which encapsulates output buffer and other rendering
    /// contexts.
    ///
    /// If resource allocation in rendering process fails, a corresponding
    /// standard exception will be thrown.
    ///
    /// \param buffer An output buffer to store the wire data.
    void toWire(AbstractMessageRenderer& renderer) const;
    /// \brief Render the \c RRClass in the wire format.
    ///
    /// This method renders the class code in network byte order into the
    /// \c buffer.
    ///
    /// If resource allocation in rendering process fails, a corresponding
    /// standard exception will be thrown.
    ///
    /// \param renderer DNS message rendering context that encapsulates the
    /// output buffer in which the RRClass is to be stored.
    void toWire(isc::util::OutputBuffer& buffer) const;
    //@}

    ///
    /// \name Getter Methods
    ///
    //@{
    /// \brief Returns the RR class code as a 16-bit unsigned integer.
    ///
    /// This method never throws an exception.
    ///
    /// \return An 16-bit integer code corresponding to the RRClass.
    uint16_t getCode() const { return (classcode_); }
    //@}

    ///
    /// \name Comparison methods
    ///
    //@{
    /// \brief Return true iff two RRClasses are equal.
    ///
    /// Two RRClasses are equal iff their class codes are equal.
    ///
    /// This method never throws an exception.
    ///
    /// \param other the \c RRClass object to compare against.
    /// \return true if the two RRClasses are equal; otherwise false.
    bool equals(const RRClass& other) const
    { return (classcode_ == other.classcode_); }
    /// \brief Same as \c equals().
    bool operator==(const RRClass& other) const { return (equals(other)); }

    /// \brief Return true iff two RRClasses are not equal.
    ///
    /// This method never throws an exception.
    ///
    /// \param other the \c RRClass object to compare against.
    /// \return true if the two RRClasses are not equal; otherwise false.
    bool nequals(const RRClass& other) const
    { return (classcode_ != other.classcode_); }
    /// \brief Same as \c nequals().
    bool operator!=(const RRClass& other) const { return (nequals(other)); } 

    /// \brief Less-than comparison for RRClass against \c other
    ///
    /// We define the less-than relationship based on their class codes;
    /// one RRClass is less than the other iff the code of the former is less
    /// than that of the other as unsigned integers.
    /// The relationship is meaningless in terms of DNS protocol; the only
    /// reason we define this method is that RRClass objects can be stored in
    /// STL containers without requiring user-defined less-than relationship.
    /// We therefore don't define other comparison operators.
    ///
    /// This method never throws an exception.
    ///
    /// \param other the \c RRClass object to compare against.
    /// \return true if \c this RRClass is less than the \c other; otherwise
    /// false.
    bool operator<(const RRClass& other) const
    { return (classcode_ < other.classcode_); }

    // BEGIN_WELL_KNOWN_CLASS_DECLARATIONS
    // END_WELL_KNOWN_CLASS_DECLARATIONS

private:
    uint16_t classcode_;
};

// BEGIN_WELL_KNOWN_CLASS_DEFINITIONS
// END_WELL_KNOWN_CLASS_DEFINITIONS

///
/// \brief Insert the \c RRClass as a string into stream.
///
/// This method convert the \c rrclass into a string and inserts it into the
/// output stream \c os.
///
/// This function overloads the global operator<< to behave as described in
/// ostream::operator<< but applied to \c RRClass objects.
///
/// \param os A \c std::ostream object on which the insertion operation is
/// performed.
/// \param rrclass The \c RRClass object output by the operation.
/// \return A reference to the same \c std::ostream object referenced by
/// parameter \c os after the insertion operation.
std::ostream&
operator<<(std::ostream& os, const RRClass& rrclass);
}
}
#endif  // RRCLASS_H

// Local Variables: 
// mode: c++
// End: 
