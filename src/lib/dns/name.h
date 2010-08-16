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

#include <stdint.h>

#include <string>
#include <vector>

#include <exceptions/exceptions.h>

namespace isc {
namespace dns {
class InputBuffer;
class OutputBuffer;
class MessageRenderer;

///
/// \brief A standard DNS module exception that is thrown if the name parser
/// encounters an empty label in the middle of a name.
///
class EmptyLabel : public Exception {
public:
    EmptyLabel(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) {}
};

///
/// \brief A standard DNS module exception that is thrown if the name parser
/// encounters too long a name.
///
class TooLongName : public Exception {
public:
    TooLongName(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) {}
};

///
/// \brief A standard DNS module exception that is thrown if the name parser
/// encounters too long a label.
///
class TooLongLabel : public Exception {
public:
    TooLongLabel(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) {}
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
        isc::Exception(file, line, what) {}
};

///
/// \brief A standard DNS module exception that is thrown if the name parser
/// fails to decode a "\"-escaped sequence.
///
class BadEscape : public Exception {
public:
    BadEscape(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) {}
};

///
/// \brief A standard DNS module exception that is thrown if the name parser
/// finds the input (string or wire-format %data) is incomplete.
///
/// An attempt of constructing a name from an empty string will trigger this
/// exception.
///
class IncompleteName : public Exception {
public:
    IncompleteName(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) {}
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
    /// "commonancestor".  This may be counter intuitive and inconvenient, but
    /// we'll keep this design at the moment until we decide whether and how to
    /// handle "non absolute" names (see the description of the \c Name class).
    /// If we want to (re)introduce the notion of non absolute names, we'll
    /// want to distinguish "com" and "com.", and the current definition would
    /// be more compatible for that purpose.
    /// If, on the other hand, we finally decide we really don't need that
    /// notion, we'll probably reconsider the design here, too. 
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
/// The \c Name class encapsulates DNS names.
///
/// It provides interfaces to construct a name from string or wire-format %data,
/// transform a name into a string or wire-format %data, compare two names, get
/// access to various properties of a name, etc.
///
/// Notes to developers: Internally, a name object maintains the name %data
/// in wire format as an instance of \c std::string.  Since many string
/// implementations adopt copy-on-write %data sharing, we expect this approach
/// will make copying a name less expensive in typical cases.  If this is
/// found to be a significant performance bottleneck later, we may reconsider
/// the internal representation or perhaps the API.
///
/// A name object also maintains a vector of offsets (\c offsets_ member),
/// each of which is the offset to a label of the name: The n-th element of
/// the vector specifies the offset to the n-th label.  For example, if the
/// object represents "www.example.com", the elements of the offsets vector
/// are 0, 4, 12, and 16.  Note that the offset to the trailing dot (16) is
/// included.  In the BIND9 DNS library from which this implementation is
/// derived, the offsets are optional, probably due to performance
/// considerations (in fact, offsets can always be calculated from the name
/// %data, and in that sense are redundant).  In our implementation, however,
/// we always build and maintain the offsets.  We believe we need more low
/// level, specialized %data structure and interface where we really need to
/// pursue performance, and would rather keep this generic API and
/// implementation simpler.
///
/// While many other DNS APIs introduce an "absolute or relative"
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
    ///
    /// \name Constructors and Destructor
    ///
    //@{
private:
    /// The default constructor
    ///
    /// This is used internally in the class implementation, but at least at
    /// the moment defined as private because it will construct an incomplete
    /// object in that it doesn't have any labels.  We may reconsider this
    /// design choice as we see more applications of the class.
    Name() : length_(0), labelcount_(0) {}
public:
    /// Constructor from a string
    ///
    /// If the given string does not represent a valid DNS name, an exception
    /// of class \c EmptyLabel, \c TooLongLabel, \c BadLabelType, \c BadEscape,
    /// \c TooLongName, or \c IncompleteName will be thrown.
    /// In addition, if resource allocation for the new name fails, a
    /// corresponding standard exception will be thrown.
    ///
    /// \param namestr A string representation of the name to be constructed.
    /// \param downcase Whether to convert upper case alphabets to lower case.
    explicit Name(const std::string& namestr, bool downcase = false);
    /// Constructor from wire-format %data.
    ///
    /// The \c buffer parameter normally stores a complete DNS message
    /// containing the name to be constructed.  The current read position of
    /// the buffer points to the head of the name.
    ///
    /// The input %data may or may not be compressed; if it's compressed, this
    /// method will automatically decompress it.
    ///
    /// If the given %data does not represent a valid DNS name, an exception
    /// of class \c DNSMessageFORMERR will be thrown.
    /// In addition, if resource allocation for the new name fails, a
    /// corresponding standard exception will be thrown.
    ///
    /// \param buffer A buffer storing the wire format %data.
    /// \param downcase Whether to convert upper case alphabets to lower case.
    explicit Name(InputBuffer& buffer, bool downcase = false);
    ///
    /// We use the default copy constructor intentionally.
    //@}
    /// We use the default copy assignment operator intentionally.
    ///

    ///
    /// \name Getter Methods
    ///
    //@{
    /// \brief Provides one-byte name %data in wire format at the specified
    /// position.
    ///
    /// This method returns the unsigned 8-bit value of wire-format \c Name
    /// %data at the given position from the head.
    ///
    /// For example, if \c n is a \c Name object for "example.com",
    /// \c n.at(3) would return \c 'a', and \c n.at(7) would return \c 'e'.
    /// Note that \c n.at(0) would be 7 (decimal), the label length of
    /// "example", instead of \c 'e', because it returns a %data portion
    /// in wire-format.  Likewise, \c n.at(8) would return 3 (decimal)
    /// instead of <code>'.'</code>
    ///
    /// This method would be useful for an application to examine the
    /// wire-format name %data without dumping the %data into a buffer,
    /// which would involve %data copies and would be less efficient.
    /// One common usage of this method would be something like this:
    /// \code for (size_t i = 0; i < name.getLength(); ++i) {
    ///     uint8_t c = name.at(i);
    ///     // do something with c
    /// } \endcode
    ///
    /// Parameter \c pos must be in the valid range of the name %data, that is,
    /// must be less than \c Name.getLength().  Otherwise, an exception of
    /// class \c OutOfRange will be thrown.
    /// This method never throws an exception in other ways.
    ///
    /// \param pos The position in the wire format name %data to be returned.
    /// \return An unsigned 8-bit integer corresponding to the name %data
    /// at the position of \c pos.
    uint8_t at(size_t pos) const
    {
        if (pos >= length_) {
            isc_throw(OutOfRange, "Out of range access in Name::at()");
        }
        return (ndata_[pos]);
    }
    /// \brief Gets the length of the <code>Name</code> in its wire format.
    ///
    /// This method never throws an exception.
    ///
    /// \return the length (the number of octets in wire format) of the
    /// <code>Name</code>
    size_t getLength() const { return (length_); }

    /// \brief Returns the number of labels contained in the <code>Name</code>.
    ///
    /// Note that an empty label (corresponding to a trailing '.') is counted
    /// as a single label, so the return value of this method must be >0.
    ///
    /// This method never throws an exception.
    ///
    /// \return the number of labels
    unsigned int getLabelCount() const { return (labelcount_); }
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
    /// an exception of class \c BadLabelType will be thrown.
    /// In addition, if resource allocation for the result string fails, a
    /// corresponding standard exception will be thrown.
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
    /// If resource allocation in rendering process fails, a corresponding
    /// standard exception will be thrown.
    ///
    /// \param renderer DNS message rendering context that encapsulates the
    /// output buffer and name compression information.
    void toWire(MessageRenderer& renderer) const;

    /// \brief Render the <code>Name</code> in the wire format without
    /// compression.
    ///
    /// If resource allocation in rendering process fails, a corresponding
    /// standard exception will be thrown.  This can be avoided by preallocating
    /// a sufficient size of \c buffer.  Specifically, if
    /// <code>buffer.getCapacity() - buffer.getLength() >= Name::MAX_WIRE</code>
    /// then this method should not throw an exception.
    ///
    /// \param buffer An output buffer to store the wire %data.
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
    /// Note that this is case-insensitive comparison.
    ///
    /// This method never throws an exception.
    ///
    /// \param other the right-hand operand to compare against.
    /// \return a <code>NameComparisonResult</code> object representing the
    /// comparison result.
    NameComparisonResult compare(const Name& other) const;

    /// \brief Return true iff two names are equal.
    ///
    /// Semantically this could be implemented based on the result of the
    /// \c compare() method, but the actual implementation uses different code
    /// that simply performs character-by-character comparison (case
    /// insensitive for the name label parts) on the two names.  This is because
    /// it would be much faster and the simple equality check would be pretty
    /// common.
    ///
    /// This method never throws an exception.
    ///
    /// \param other the <code>Name</code> object to compare against.
    /// \return true if the two names are equal; otherwise false.
    bool equals(const Name& other) const;

    /// Same as equals()
    bool operator==(const Name& other) const { return (equals(other)); }

    /// \brief Return true iff two names are not equal.
    ///
    /// This method simply negates the result of \c equal() method, and in that
    /// sense it's redundant.  The separate method is provided just for
    /// convenience.
    bool nequals(const Name& other) const { return (!(equals(other))); }

    /// Same as nequals()
    bool operator!=(const Name& other) const { return (nequals(other)); }

    /// \brief Less-than or equal comparison for Name against <code>other</code>
    ///
    /// The comparison is based on the result of the \c compare() method.
    ///
    /// This method never throws an exception.
    ///
    /// \param other the <code>Name</code> object to compare against.
    /// \return true if <code>compare(other).getOrder() <= 0</code>;
    /// otherwise false.
    bool leq(const Name& other) const;

    /// Same as leq()
    bool operator<=(const Name& other) const { return (leq(other)); }

    /// \brief Greater-than or equal comparison for Name against
    /// <code>other</code>
    ///
    /// The comparison is based on the result of the \c compare() method.
    ///
    /// This method never throws an exception.
    ///
    /// \param other the <code>Name</code> object to compare against.
    /// \return true if <code>compare(other).getOrder() >= 0</code>;
    /// otherwise false.
    bool geq(const Name& other) const;

    /// Same as geq()
    bool operator>=(const Name& other) const { return (geq(other)); }

    /// \brief Less-than comparison for Name against <code>other</code>
    ///
    /// The comparison is based on the result of the \c compare() method.
    ///
    /// This method never throws an exception.
    ///
    /// \param other the <code>Name</code> object to compare against.
    /// \return true if <code>compare(other).getOrder() < 0</code>;
    /// otherwise false.
    bool lthan(const Name& other) const;

    /// Same as lthan()
    bool operator<(const Name& other) const { return (lthan(other)); }

    /// \brief Greater-than comparison for Name against <code>other</code>
    ///
    /// The comparison is based on the result of the \c compare() method.
    ////
    /// This method never throws an exception.
    ///
    /// \param other the <code>Name</code> object to compare against.
    /// \return true if <code>compare(other).getOrder() > 0</code>;
    /// otherwise false.
    bool gthan(const Name& other) const;

    /// Same as gthan()
    bool operator>(const Name& other) const { return (gthan(other)); }
    //@}

    ///
    /// \name Transformer methods
    ///
    //@{
    /// \brief Extract a specified subpart of Name.
    ///
    /// <code>name.split(first, n)</code> constructs a new name starting from
    /// the <code>first</code>-th label of the \c name, and subsequent \c n
    /// labels including the \c first one.  Since names in this current
    /// implementation are always "absolute", if the specified range doesn't
    /// contain the trailing dot of the original \c name, then a dot will be
    /// appended to the resulting name.  As a result, the number of labels
    /// will be <code>n + 1</code>, rather than \c n.  For example,
    /// when \c n is <code>Name("www.example.com")</code>,
    /// both <code>n.split(1, 2)</code> and <code>n.split(1, 3)</code>
    /// will produce a name corresponding to "example.com.", which has 3 labels.
    /// Note also that labels are counted from 0, and so <code>first = 1</code>
    /// in this example specified the label "example", not "www".
    ///
    /// Parameter \c n must be larger than 0, and the range specified by
    /// \c first and \c n must not exceed the valid range of the original name;
    /// otherwise, an exception of class \c OutOfRange will be thrown.
    ///
    /// Note to developers: we may want to have different versions (signatures)
    /// of this method.  For example, we want to split the Name based on a given
    /// suffix name.
    ///
    /// \param first The start position (in labels) of the extracted name
    /// \param n Number of labels of the extracted name
    /// \return A new Name object based on the Name containing <code>n</code>
    /// labels including and following the <code>first</code> label.  
    Name split(unsigned int first, unsigned int n) const;

    /// \brief Extract a specified super domain name of Name.
    ///
    /// This function constructs a new \c Name object that is a super domain
    /// of \c this name.
    /// The new name is \c level labels upper than \c this name.
    /// For example, when \c name is www.example.com,
    /// <code>name.split(1)</code> will return a \c Name object for example.com.
    /// \c level can be 0, in which case this method returns a copy of
    /// \c this name.
    /// The possible maximum value for \c level is
    /// <code>this->getLabelCount()-1</code>, in which case this method
    /// returns a root name.
    ///
    /// One common expected usage of this method is to iterate over super
    /// domains of a given name, label by label, as shown in the following
    /// sample code:
    /// \code // if name is www.example.com...
    /// for (int i = 0; i < name.getLabelCount(); ++i) {
    ///     Name upper_name(name.split(i));
    ///     // upper_name'll be www.example.com., example.com., com., and then .
    /// }
    /// \endcode
    ///
    /// \c level must be smaller than the number of labels of \c this name;
    /// otherwise an exception of class \c OutOfRange will be thrown.
    /// In addition, if resource allocation for the new name fails, a
    /// corresponding standard exception will be thrown.
    ///
    /// Note to developers: probably as easily imagined, this method is a
    /// simple wrapper to one usage of the other
    /// <code>split(unsigned int, unsigned int) const</code> method and is
    /// redundant in some sense.
    /// We provide the "redundant" method for convenience, however, because
    /// the expected usage shown above seems to be common, and the parameters
    /// to the other \c split(unsigned int, unsigned int) const to implement
    /// it may not be very intuitive.
    ///
    /// We are also aware that it is generally discouraged to add a public
    /// member function that could be implemented using other member functions.
    /// We considered making it a non member function, but we could not come
    /// up with an intuitive function name to represent the specific service.
    /// Some other BIND 10 developers argued, probably partly because of the
    /// counter intuitive function name, a different signature of \c split
    /// would be better to improve code readability.
    /// While that may be a matter of personal preference, we accepted the
    /// argument.  One major goal of public APIs like this is wider acceptance
    /// from internal/external developers, so unless there is a clear advantage
    /// it would be better to respect the preference of the API users.
    ///
    /// Since this method doesn't have to be a member function in other way,
    /// it is intentionally implemented only using public interfaces of the
    /// \c Name class; it doesn't refer to private members of the class even if
    /// it could.
    /// This way we hope we can avoid damaging the class encapsulation,
    /// which is a major drawback of public member functions.
    /// As such if and when this "method" has to be extended, it should be
    /// implemented without the privilege of being a member function unless
    /// there is a very strong reason to do so.  In particular a minor
    /// performance advantage shouldn't justify that approach.
    ///
    /// \param level The number of labels to be removed from \c this name to
    /// create the super domain name.
    /// (0 <= \c level < <code>this->getLabelCount()</code>)
    /// \return A new \c Name object to be created.
    Name split(unsigned int level) const;

    /// \brief Reverse the labels of a name
    ///
    /// This method reverses the labels of a name.  For example, if
    /// \c this is "www.example.com.", this method will return 
    /// "com.example.www."  (This is useful because DNSSEC sort order
    /// is equivalent to a lexical sort of label-reversed names.)
    Name reverse() const;

    /// \brief Concatenate two names.
    ///
    /// This method appends \c suffix to \c this Name.  The trailing dot of
    /// \c this Name will be removed.  For example, if \c this is "www."
    /// and \c suffix is "example.com.", a successful return of this method
    /// will be a name of "www.example.com."
    ///
    ///The resulting length of the concatenated name must not exceed
    /// \c Name::MAX_WIRE; otherwise an exception of class
    /// \c TooLongName will be thrown.
    ///
    /// \param suffix a Name object to be appended to the Name.
    /// \return a new Name object concatenating \c suffix to \c this Name.
    Name concatenate(const Name& suffix) const;

    /// \brief Downcase all upper case alphabet characters in the name.
    ///
    /// This method modifies the calling object so that it can perform the
    /// conversion as fast as possible and can be exception free.
    ///
    /// The return value of this version of \c downcase() is a reference to
    /// the calling object (i.e., \c *this) so that the caller can use the
    /// result of downcasing in a single line.  For example, if variable
    /// \c n is a \c Name class object possibly containing upper case
    /// characters, and \c b is an \c OutputBuffer class object, then the
    /// following code will dump the name in wire format to \c b with
    /// downcasing upper case characters:
    ///
    /// \code n.downcase().toWire(b); \endcode
    ///
    /// Since this method modifies the calling object, a \c const name object
    /// cannot call it.  If \c n is a \c const Name class object, it must first
    /// be copied to a different object and the latter must be used for the
    /// downcase modification.
    ///
    /// \return A reference to the calling object with being downcased.
    Name& downcase();
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

    /// \brief Max allowable labels of domain names.
    ///
    /// This is <code>ceil(MAX_WIRE / 2)</code>, and is equal to the number of
    /// labels of name "a.a.a.a....a." (127 "a"'s and trailing dot).
    static const size_t MAX_LABELS = 128;

    /// \brief Max allowable length of labels of a domain name.
    static const size_t MAX_LABELLEN = 63;

    /// \brief Max possible pointer value for name compression.
    ///
    /// This is the highest number of 14-bit unsigned integer.  Name compression
    /// pointers are identified as a 2-byte value starting with the upper two
    /// bit being 11.
    static const uint16_t MAX_COMPRESS_POINTER = 0x3fff;
    /// \brief A 8-bit masked value indicating a start of compression pointer.
    static const uint16_t COMPRESS_POINTER_MARK8 = 0xc0;
    /// \brief A 16-bit masked value indicating a start of compression pointer.
    static const uint16_t COMPRESS_POINTER_MARK16 = 0xc000;
    //@}

    ///
    /// \name Well-known name constants
    ///
    //@{
    /// \brief Root name (i.e. ".").
    static const Name& ROOT_NAME();
    //@}

private:
    std::string ndata_;
    std::vector<unsigned char> offsets_;
    unsigned int length_;
    unsigned int labelcount_;
};

inline const Name&
Name::ROOT_NAME() {
    static Name root_name(".");
    return (root_name);
}

///
/// \brief Insert the name as a string into stream.
///
/// This method convert the \c name into a string and inserts it into the
/// output stream \c os.
///
/// This function overloads the global operator<< to behave as described in
/// ostream::operator<< but applied to \c Name objects.
///
/// \param os A \c std::ostream object on which the insertion operation is
/// performed.
/// \param name The \c Name object output by the operation.
/// \return A reference to the same \c std::ostream object referenced by
/// parameter \c os after the insertion operation.
std::ostream&
operator<<(std::ostream& os, const Name& name);
}
}
#endif // __NAME_H

// Local Variables: 
// mode: c++
// End: 
