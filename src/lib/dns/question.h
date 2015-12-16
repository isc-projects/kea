// Copyright (C) 2010-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef QUESTION_H
#define QUESTION_H 1

#include <iostream>
#include <string>

#include <boost/shared_ptr.hpp>

#include <dns/name.h>
#include <dns/rrclass.h>
#include <dns/rrtype.h>

namespace isc {
namespace util {
class InputBuffer;
class OutputBuffer;
}

namespace dns {

class AbstractMessageRenderer;
class Question;

/// \brief A pointer-like type pointing to an \c Question object.
typedef boost::shared_ptr<Question> QuestionPtr;

/// \brief A pointer-like type pointing to an (immutable) \c Question object.
typedef boost::shared_ptr<const Question> ConstQuestionPtr;

/// \brief The \c Question class encapsulates the common search key of DNS
/// lookup, consisting of owner name, RR type and RR class.
///
/// The primarily intended use case of this class is an entry of the question
/// section of DNS messages.
/// This could also be used as a general purpose lookup key, e.g., in a
/// custom implementation of DNS database.
///
/// In this initial implementation, the \c Question class is defined as
/// a <em>concrete class</em>; it's not expected to be inherited by
/// a user-defined customized class.
/// It may be worth noting that it's different from the design of the
/// RRset classes (\c AbstractRRset and its derived classes).
/// The RRset classes form an inheritance hierarchy from the base abstract
/// class.
/// This may look odd in that an "RRset" and "Question" are similar from the
/// protocol point of view: Both are used as a semantics unit of DNS messages;
/// both share the same set of components (name, RR type and RR class).
///
/// In fact, BIND9 didn't introduce a separate data structure for Questions,
/// and use the same \c "rdataset" structure for both RRsets and Questions.
/// We could take the same approach, but chose to adopt the different design.
/// One reason for that is because a Question and an RRset are still
/// different, and a Question might not be cleanly defined, e.g., if it were
/// a derived class of some "RRset-like" class.
/// For example, we couldn't give a reasonable semantics for \c %getTTL() or
/// \c %setTTL() methods for a Question, since it's not associated with the
/// TTL.
/// In fact, the BIND9 implementation ended up often separating the case where
/// a \c "rdataset" is from the Question section of a DNS message and the
/// case where it comes from other sections.
/// If we cannot treat them completely transparently anyway, separating the
/// class (type) would make more sense because we can exploit compilation
/// time type checks.
///
/// On the other hand, we do not expect a strong need for customizing the
/// \c Question class, unlike the RRset.
/// Handling the "Question" section of a DNS message is relatively a
/// simple work comparing to RRset-involved operations, so a unified
/// straightforward implementation should suffice for any use cases
/// including performance sensitive ones.
///
/// We may, however, still want to have a customized version of Question
/// for, e.g, highly optimized behavior, and may revisit this design choice
/// as we have more experience with this implementation.
///
/// One disadvantage of defining RRsets and Questions as unrelated classes
/// is that we cannot handle them in a polymorphic way.
/// For example, we might want to iterate over DNS message sections and
/// render the data in the wire format, whether it's an RRset or a Question.
/// If a \c Question were a derived class of some common RRset-like class,
/// we could do this by calling <code>rrset_or_question->%toWire()</code>.
/// But the actual design doesn't allow this approach, which may require
/// duplicate code for almost the same operation.
/// To mitigate this problem, we intentionally used the same names
/// with the same signature for some common methods of \c Question and
/// \c AbstractRRset such as \c %getName() or \c %toWire().
/// So the user class may use a template function that is applicable to both
/// \c Question and \c RRset to avoid writing duplicate code logic.
class Question {
    ///
    /// \name Constructors and Destructor
    ///
    /// We use the default versions of destructor, copy constructor,
    /// and assignment operator.
    ///
    /// The default constructor is hidden as a result of defining the other
    /// constructors.  This is intentional; we don't want to allow a
    /// \c Question object to be constructed with an invalid state.
    //@{
public:
    /// \brief Constructor from wire-format data.
    ///
    /// It simply constructs a set of \c Name, \c RRType, and \c RRClass
    /// object from the \c buffer in this order, and constructs a
    /// \c Question object in a straightforward way.
    ///
    /// It may throw an exception if the construction of these component
    /// classes fails.
    ///
    /// \param buffer A buffer storing the wire format data.
    Question(isc::util::InputBuffer& buffer);

    /// \brief Constructor from fixed parameters of the \c Question.
    ///
    /// This constructor is basically expected to be exception free, but
    /// copying the name may involve resource allocation, and if it fails
    /// the corresponding standard exception will be thrown.
    ///
    /// \param name The owner name of the \c Question.
    /// \param rrclass The RR class of the \c Question.
    /// \param rrtype The RR type of the \c Question.
    Question(const Name& name, const RRClass& rrclass, const RRType& rrtype) :
        name_(name), rrtype_(rrtype), rrclass_(rrclass)
    {}
    //@}

    ///
    /// \name Getter Methods
    ///
    //@{
    /// \brief Returns the owner name of the \c Question.
    ///
    /// This method never throws an exception.
    ///
    /// \return A reference to a \c Name class object corresponding to the
    /// \c Question owner name.
    const Name& getName() const { return (name_); }

    /// \brief Returns the RR Class of the \c Question.
    ///
    /// This method never throws an exception.
    ///
    /// \return A reference to a \c RRClass class object corresponding to the
    /// RR class of the \c Question.
    const RRType& getType() const { return (rrtype_); }

    /// \brief Returns the RR Type of the \c Question.
    ///
    /// This method never throws an exception.
    ///
    /// \return A reference to a \c RRType class object corresponding to the
    /// RR type of the \c Question.
    const RRClass& getClass() const { return (rrclass_); }
    //@}

    ///
    /// \name Converter Methods
    ///
    //@{
    /// \brief Convert the Question to a string.
    ///
    /// When \c newline argument is \c true, this method terminates the
    /// resulting string with a trailing newline character (following
    /// the BIND9 convention).
    ///
    /// This method simply calls the \c %toText() methods of the corresponding
    /// \c Name, \c RRType and \c RRClass classes for this \c Question, and
    /// these methods may throw an exception.
    /// In particular, if resource allocation fails, a corresponding standard
    /// exception will be thrown.
    ///
    /// \param newline Whether to add a trailing newline. If true, a
    /// trailing newline is added. If false, no trailing newline is
    /// added.
    ///
    /// \return A string representation of the \c Question.
    std::string toText(bool newline = false) const;

    /// \brief Render the Question in the wire format with name compression.
    ///
    /// This method simply calls the \c %toWire() methods of the corresponding
    /// \c Name, \c RRType and \c RRClass classes for this \c Question, and
    /// these methods may throw an exception.
    /// In particular, if resource allocation fails, a corresponding standard
    /// exception will be thrown.
    ///
    /// This method returns 1, which is the number of "questions" contained
    /// in the \c Question.
    /// This is a meaningless value, but is provided to be consistent with
    /// the corresponding method of \c AbstractRRset (see the detailed
    /// class description).
    ///
    /// The owner name will be compressed if possible, although it's an
    /// unlikely event in practice because the Question section a DNS
    /// message normally doesn't contain multiple question entries and
    /// it's located right after the Header section.
    /// Nevertheless, \c renderer records the information of the owner name
    /// so that it can be pointed by other RRs in other sections (which is
    /// more likely to happen).
    ///
    /// It could be possible, though very rare in practice, that
    /// an attempt to render a Question may cause truncation
    /// (when the Question section contains a large number of entries).
    /// In such a case this method avoid the rendering and indicate the
    /// truncation in the \c renderer.  This method returns 0 in this case.
    ///
    /// \param renderer DNS message rendering context that encapsulates the
    /// output buffer and name compression information.
    ///
    /// \return 1 on success; 0 if it causes truncation
    unsigned int toWire(AbstractMessageRenderer& renderer) const;

    /// \brief Render the Question in the wire format without name compression.
    ///
    /// This method behaves like the render version except it doesn't compress
    /// the owner name.
    /// See \c toWire(AbstractMessageRenderer& renderer)const.
    ///
    /// \param buffer An output buffer to store the wire data.
    /// \return 1
    unsigned int toWire(isc::util::OutputBuffer& buffer) const;
    //@}

    ///
    /// \name Comparison Operators
    ///
    //@{
    /// A "less than" operator is needed for this class so it can
    /// function as an index to std::map.
    bool operator <(const Question& rhs) const {
        return (rrclass_ < rhs.rrclass_ ||
                (rrclass_ == rhs.rrclass_ &&
                 (rrtype_ < rhs.rrtype_ ||
                  (rrtype_ == rhs.rrtype_ && (name_ < rhs.name_)))));
    }

    /// Equality operator.  Primarily used to compare the question section in
    /// a response to that in the query.
    ///
    /// \param rhs Question to compare against
    /// \return true if name, class and type are equal, false otherwise
    bool operator==(const Question& rhs) const {
        return ((rrclass_ == rhs.rrclass_) && (rrtype_ == rhs.rrtype_) &&
                (name_ == rhs.name_));
    }

    /// Inequality operator.  Primarily used to compare the question section in
    /// a response to that in the query.
    ///
    /// \param rhs Question to compare against
    /// \return true if one or more of the name, class and type do not match,
    /// false otherwise.
    bool operator!=(const Question& rhs) const {
        return (!operator==(rhs));
    }
    //@}

private:
    Name name_;
    RRType rrtype_;
    RRClass rrclass_;
};

/// \brief Insert the \c Question as a string into stream.
///
/// This method convert the \c question into a string and inserts it into the
/// output stream \c os.
///
/// This function overloads the global \c operator<< to behave as described in
/// \c %ostream::%operator<< but applied to Question objects.
///
/// \param os A \c std::ostream object on which the insertion operation is
/// performed.
/// \param question A reference to a \c Question object output by the
/// operation.
/// \return A reference to the same \c std::ostream object referenced by
/// parameter \c os after the insertion operation.
std::ostream& operator<<(std::ostream& os, const Question& question);
} // end of namespace dns
} // end of namespace isc
#endif  // QUESTION_H

// Local Variables: 
// mode: c++
// End: 
