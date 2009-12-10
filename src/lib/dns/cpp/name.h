// Copyright (C) 2009  Internet Systems Consortium, Inc. ("ISC")
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

#ifndef __NAME_H
#define __NAME_H 1

#include <string>
#include <vector>

#include "exceptions.h"

namespace isc {
namespace dns {
class InputBuffer;
class OutputBuffer;
class MessageRenderer;
class NameDecompressor;

///
/// \brief A standard DNS module exception that is thrown if the name parser
/// encounters an empty label in the middle of a name.
///
class EmptyLabel : public Exception {
public:
    EmptyLabel(const char* file, size_t line, const char* what) :
        isc::dns::Exception(file, line, what) {}
};

///
/// \brief A standard DNS module exception that is thrown if the name parser
/// encounters too long a name.
///
class TooLongName : public Exception {
public:
    TooLongName(const char* file, size_t line, const char* what) :
        isc::dns::Exception(file, line, what) {}
};

///
/// \brief A standard DNS module exception that is thrown if the name parser
/// encounters too long a label.
///
class TooLongLabel : public Exception {
public:
    TooLongLabel(const char* file, size_t line, const char* what) :
        isc::dns::Exception(file, line, what) {}
};

///
/// \brief A standard DNS module exception that is thrown if the name parser
/// encounters an obsolete or incomplete label type.  In effect "obsolete" only
/// applies to bitstring labels, which would begin with "\[".  Incomplete cases
/// include an incomplete escaped sequence such as "\12".
///
class BadLabelType : public Exception {
public:
    BadLabelType(const char* file, size_t line, const char* what) :
        isc::dns::Exception(file, line, what) {}
};

///
/// \brief A standard DNS module exception that is thrown if the name parser
/// fails to decode a "\"-escaped sequence.
///
class BadEscape : public Exception {
public:
    BadEscape(const char* file, size_t line, const char* what) :
        isc::dns::Exception(file, line, what) {}
};

///
/// \brief A standard DNS module exception that is thrown if the wire-format
/// name contains an invalid compression pointer.
///
class BadPointer : public Exception {
public:
    BadPointer(const char* file, size_t line, const char* what) :
        isc::dns::Exception(file, line, what) {}
};

///
/// \brief A standard DNS module exception that is thrown if the wire-format
/// name is not a complete domain name.
///
class IncompleteName : public Exception {
public:
    IncompleteName(const char* file, size_t line, const char* what) :
        isc::dns::Exception(file, line, what) {}
};

///
/// This is a supplemental class used only as a return value of Name::compare().
/// It encapsulate a tuple of the comparison: ordering, number of common labels,
/// and relationship as follows:
/// - ordering: relative ordering under the DNSSEC order relation
/// - labels: the number of common significant labels of the two names being
///   compared
/// - relationship: see NameComparisonResult::NameRelation
///
class NameComparisonResult {
public:
    /// The relation of two names under comparison.
    /// Its semantics for the case of
    /// <code>name1->compare(name2)</code> (where name1 and name2 are instances
    /// of the Name class) is as follows:
    ///    - SUPERDOMAIN: name1 properly contains name2; name2 is a proper
    ///      subdomain of name1
    ///    - SUBDOMAIN: name1 is a proper subdomain of name2
    ///    - EQUAL: name1 and name2 are equal
    ///    - COMMONANCESTOR: name1 and name2 share a common ancestor
    ///
    /// Note that in our implementation there's always a hierarchical
    /// relationship between any two names since all names are absolute and
    /// they at least share the trailing empty label.
    /// So, for example, the relationship between "com." and "net." is
    /// "commonancestor", even though it may be counter intuitive.
    enum NameRelation {
        SUPERDOMAIN = 0,
        SUBDOMAIN = 1,
        EQUAL = 2,
        COMMONANCESTOR = 3
    };

    ///
    /// \name Constructors and Destructor
    ///
    //@{
    /// \brief Constructor from a comparison tuple
    ///
    /// This constructor simply initializes the object in the straightforward
    /// way.
    explicit NameComparisonResult(int order, unsigned int nlabels,
                                  NameRelation relation) :
        order_(order), nlabels_(nlabels), relation_(relation) {}
    //@}

    ///
    /// \name Getter Methods
    ///
    //@{
    /// Returns the ordering of the comparison result
    int getOrder() const { return (order_); }
    /// Returns the number of common labels of the comparison result
    unsigned int getCommonLabels() const { return (nlabels_); }
    /// Returns the NameRelation of the comparison result
    NameRelation getRelation() const { return (relation_); }
    //@}
private:
    int order_;
    unsigned int nlabels_;
    NameRelation relation_;
};

///
/// The \c Name class encapsulates DNS names. It provides interfaces
/// to construct a name from string or wire-format data, transform a name into
/// a string or wire-format data, compare two names, get access to attributes.
///
/// Note that while many other DNS APIs introduce an "absolute or relative"
/// attribute of names as defined in RFC1035, names are always "absolute" in
/// the initial design of this API.
/// In fact, separating absolute and relative would confuse API users
/// unnecessarily.  For example, it's not so intuitive to consider the
/// comparison result of an absolute name with a relative name.
/// We've looked into how the concept of absolute names is used in BIND9,
/// and found that in many cases names are generally absolute.
/// The only reasonable case of separating absolute and relative is in a master
/// file parser, where a relative name must be a complete name with an "origin"
/// name, which must be absolute.  So, in this initial design, we chose a
/// simpler approach: the API generally handles names as absolute; when we
/// introduce a parser of master files, we'll introduce the notion of relative
/// names as a special case.
///
class Name {
public:
    ///
    /// \name Constructors and Destructor
    ///
    //@{
    /// The default constructor
    Name() : length_(0), labels_(0) {}
    /// Constructor from a string
    ///
    /// \param namestr A string representation of the name to be constructed.
    /// \param downcase Whether to convert upper case alphabets to lower case.
    explicit Name(const std::string& namestr, bool downcase = false);
    /// Constructor from wire-format data.
    ///
    /// The \c buffer parameter normally stores a complete DNS message
    /// containing the name to be constructed.  The current read position of
    /// the buffer points to the head of the name.
    ///
    /// The input data may or may not be compressed; if it's compressed, this
    /// method will automatically decompress it.
    ///
    /// \param buffer A buffer storing the wire format data.
    /// \param downcase Whether to convert upper case alphabets to lower case.
    explicit Name(InputBuffer& buffer, bool downcase = false);
    //@}

    ///
    /// \name Getter Methods
    ///
    //@{
    /// \brief Gets the length of the <code>Name</code> in its wire format.
    ///
    /// \return the length of the <code>Name</code>
    size_t getLength() const { return (length_); }

    /// \brief Returns the number of labels contained in the <code>Name</code>.
    ///
    /// Note that an empty label (corresponding to a trailing '.') is counted
    /// as a single label, so the return value of this method must be >0.
    ///
    /// \return the number of labels
    unsigned int getLabels() const { return (labels_); }
    //@}

    ///
    /// \name Converter methods
    ///
    //@{
    /// \brief Convert the Name to a string.
    ///
    /// This method returns a <code>std::string</code> object representing the
    /// Name as a string.  Unless <code>omit_final_dot</code> is
    /// <code>true</code>, the returned string ends with a dot '.'; the default
    /// is <code>false</code>.  The default value of this parameter is
    /// <code>true</code>; converted names will have a trailing dot by default.
    ///
    /// This function assumes the name is in proper uncompressed wire format.
    /// If it finds an unexpected label character including compression pointer,
    /// an exception of class \c isc::dns::BadLabelType will be thrown.
    //
    /// \param omit_final_dot whether to omit the trailing dot in the output.
    /// \return a string representation of the <code>Name</code>.
    std::string toText(bool omit_final_dot = false) const;

    /// \brief Render the <code>Name</code> in the wire format with compression.
    ///
    /// This method dumps the Name in wire format with help of \c renderer,
    /// which encapsulates output buffer and name compression algorithm to
    /// render the name.
    ///
    /// \param renderer DNS message rendering context that encapsulates the
    /// output buffer and name compression information.
    void toWire(MessageRenderer& renderer) const;

    /// \brief Render the <code>Name</code> in the wire format without
    /// compression.
    ///
    void toWire(OutputBuffer& buffer) const;
    //@}

    ///
    /// \name Comparison methods
    ///
    //@{
    /// \brief Compare two <code>Name</code>s.
    ///
    /// This method compares the <code>Name</code> and <code>other</code> and
    /// returns the result in the form of a <code>NameComparisonResult</code>
    /// object.
    ///
    /// Note that this is a case-insensitive comparison.
    ///
    /// \param other the right-hand operand to compare against.
    /// \return a <code>NameComparisonResult</code> object representing the
    /// comparison result.
    NameComparisonResult compare(const Name& other) const;

    /// \brief Return true iff two names are equal.
    ///
    /// The comparison is based on the result of the compare() method.
    /// \param other the <code>Name</code> object to compare against.
    /// \return true if <code>compare(other).get_order()</code> is 0;
    /// otherwise false.
    bool equals(const Name& other) const;

    /// Same as equals()
    bool operator==(const Name& other) const;

    /// \brief Return true iff two names are not equal.
    ///
    /// The comparison is based on the result of the compare() method.
    /// \param other the <code>Name</code> object to compare against.
    /// \return true if <code>compare(other).get_order()</code> is non 0;
    /// otherwise false.
    bool nequals(const Name& other) const;

    /// Same as nequals()
    bool operator!=(const Name& other) const { return (!(*this == other)); }

    /// \brief Less-than or equal comparison for Name against <code>other</code>
    ///
    /// The comparison is based on the result of the compare() method.
    /// \param other the <code>Name</code> object to compare against.
    /// \return true if <code>compare(other).get_order() <= 0</code>;
    /// otherwise false.
    bool leq(const Name& other) const;

    /// Same as leq()
    bool operator<=(const Name& other) const;

    /// \brief Greater-than or equal comparison for Name against
    /// <code>other</code>
    ///
    /// The comparison is based on the result of the compare() method.
    /// \param other the <code>Name</code> object to compare against.
    /// \return true if <code>compare(other).get_order() >= 0</code>;
    /// otherwise false.
    bool geq(const Name& other) const;

    /// Same as geq()
    bool operator>=(const Name& other) const;

    /// \brief Less-than comparison for Name against <code>other</code>
    ///
    /// The comparison is based on the result of the compare() method.
    /// \param other the <code>Name</code> object to compare against.
    /// \return true if <code>compare(other).get_order() < 0</code>;
    /// otherwise false.
    bool lthan(const Name& other) const;

    /// Same as lthan()
    bool operator<(const Name& other) const;

    /// \brief Greater-than comparison for Name against <code>other</code>
    ///
    /// The comparison is based on the result of the compare() method.
    /// \param other the <code>Name</code> object to compare against.
    /// \return true if <code>compare(other).get_order() > 0</code>;
    /// otherwise false.
    bool gthan(const Name& other) const;

    /// Same as gthan()
    bool operator>(const Name& other) const;
    //@}

    ///
    /// \name Transformer methods
    ///
    //@{
    /// \brief Extract a specified subpart of Name.
    ///
    /// Note: we may want to have different versions (signatures) of this
    /// method.  For example, we want to split the Name based on a given suffix
    /// name.
    ///
    /// \param first the start position of the extracted name
    /// \param n number of labels of the extracted name
    /// \return a new Name object based on the Name containing <code>n</code>
    /// labels including and following the <code>first</code> label.  
    Name split(unsigned int first, unsigned int n) const;

    /// \brief Concatenate two names
    ///
    /// This method appends \c suffix to \c this Name.
    ///
    /// \param suffix a Name object to be appended to the Name.
    /// \return a new Name object concatenating \c suffix to \c this Name.
    Name concatenate(const Name& suffix) const;
    //@}

    ///
    /// \name Testing methods
    ///
    //@{
    /// \brief Test if this is a wildcard name.
    ///
    /// \return \c true if the least significant label of this Name is
    /// <code>'*'</code>; otherwise \c false.
    bool isWildcard() const;
    //@}

    ///
    /// \name Protocol constants
    ///
    //@{
    /// \brief Max allowable length of domain names.
    static const size_t MAX_WIRE = 255;

    /// \brief Max allowable length of labels of a domain name.
    static const size_t MAX_LABELLEN = 63;
    //@}

private:
    std::string ndata_;
    std::vector<char> offsets_;
    unsigned int length_;
    unsigned int labels_;

    void fromString(const std::string& namestr);
};

std::ostream& operator<<(std::ostream& os, const Name& name);
}
}
#endif // __NAME_H

// Local Variables: 
// mode: c++
// End: 
