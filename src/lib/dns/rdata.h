// Copyright (C) 2010-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef RDATA_H
#define RDATA_H 1

#include <dns/master_lexer.h>
#include <dns/master_loader.h>
#include <dns/master_loader_callbacks.h>

#include <dns/exceptions.h>

#include <boost/shared_ptr.hpp>

#include <stdint.h>

namespace isc {
namespace util {
class InputBuffer;
class OutputBuffer;
}
namespace dns {
class AbstractMessageRenderer;
class RRType;
class RRClass;
class Name;

namespace rdata {

///
/// \brief A standard DNS module exception that is thrown if RDATA parser
/// encounters an invalid or inconsistent data length.
///
class InvalidRdataLength : public DNSTextError {
public:
    InvalidRdataLength(const char* file, size_t line, const char* what) :
        DNSTextError(file, line, what) {}
};

///
/// \brief A standard DNS module exception that is thrown if RDATA parser
/// fails to recognize a given textual representation.
///
class InvalidRdataText : public DNSTextError {
public:
    InvalidRdataText(const char* file, size_t line, const char* what) :
        DNSTextError(file, line, what) {}
};

///
/// \brief A standard DNS module exception that is thrown if RDATA parser
/// encounters a character-string (as defined in RFC1035) exceeding
/// the maximum allowable length (\c MAX_CHARSTRING_LEN).
///
class CharStringTooLong : public DNSTextError {
public:
    CharStringTooLong(const char* file, size_t line, const char* what) :
        DNSTextError(file, line, what) {}
};

// Forward declaration to define RdataPtr.
class Rdata;

///
/// The \c RdataPtr type is a pointer-like type, pointing to an
/// object of some concrete derived class of \c Rdata.
///
typedef boost::shared_ptr<Rdata> RdataPtr;
typedef boost::shared_ptr<const Rdata> ConstRdataPtr;

/// \brief Possible maximum length of RDATA, which is the maximum unsigned
/// 16 bit value.
const size_t MAX_RDLENGTH = 65535;

/// \brief The maximum allowable length of character-string containing in
/// RDATA as defined in RFC1035, not including the 1-byte length field.
const unsigned int MAX_CHARSTRING_LEN = 255;

/// \brief The \c Rdata class is an abstract base class that provides
/// a set of common interfaces to manipulate concrete RDATA objects.
///
/// Generally, a separate derived class directly inherited from the base
/// \c Rdata class is defined for each well known RDATA.
/// Each of such classes will define the common logic based on the
/// corresponding protocol standard.
///
/// Since some types of RRs are class specific and the corresponding RDATA
/// may have different semantics (e.g. type A for class IN and type A for
/// class CH have different representations and semantics), we separate
/// \c Rdata derived classes for such RR types in different namespaces.
/// The namespace of types specific to a class is named the lower-cased class
/// name; for example, RDATA of class IN-specific types are defined in the
/// \c in namespace, and RDATA of class CH-specific types are defined in
/// the \c ch namespace, and so on.
/// The derived classes are named using the RR type name (upper cased) such as
/// \c A or \c AAAA.
/// Thus RDATA of type A RR for class IN and CH are defined as \c in::A and
/// \c ch::A, respectively.
/// Many other RR types are class independent; the derived \c Rdata classes
/// for such RR types are defined in the \c generic namespace.  Examples are
/// \c generic::NS and \c generic::SOA.
///
/// If applications need to refer to these derived classes, it is generally
/// recommended to prepend at least some part of the namespace because the
/// same class name can be used in different namespaces.
/// So, instead of doing
/// \code using namespace isc::dns::rdata::in;
/// A& rdata_type_a; \endcode
/// it is advisable to prepend at least \c in from the namespace:
/// \code using namespace isc::dns::rdata;
/// in::A& rdata_type_a; \endcode
///
/// In many cases, however, an application doesn't have to care about such
/// derived classes.
/// For instance, to parse an incoming DNS message an application wouldn't
/// have to perform type specific operation unless the application is
/// specifically concerned about a particular type.
/// So, this API generally handles \c Rdata in a polymorphic way through
/// a pointer or reference to this base abstract class.
class Rdata {
    ///
    /// \name Constructors and Destructor
    ///
    /// Note: The copy constructor and the assignment operator are intentionally
    /// defined as private.  Concrete classes should generally specialize their
    /// own versions of these methods.
    //@{
protected:
    /// The default constructor.
    ///
    /// This is intentionally defined as \c protected as this base class should
    /// never be instantiated (except as part of a derived class).  In many
    /// cases, the derived class wouldn't define a public default constructor
    /// either, because an \c Rdata object without concrete data isn't
    /// meaningful.
    Rdata() {}
private:
    Rdata(const Rdata& source);
    void operator=(const Rdata& source);
public:
    /// The destructor.
    virtual ~Rdata() {};
    //@}

    ///
    /// \name Converter methods
    ///
    //@{
    /// \brief Convert an \c Rdata to a string.
    ///
    /// This method returns a \c std::string object representing the \c Rdata.
    ///
    /// This is a pure virtual method without the definition; the actual
    /// representation is specific to each derived concrete class and
    /// should be explicitly defined in the derived class.
    ///
    /// \return A string representation of \c Rdata.
    virtual std::string toText() const = 0;

    /// \brief Render the \c Rdata in the wire format into a buffer.
    ///
    /// This is a pure virtual method without the definition; the actual
    /// conversion is specific to each derived concrete class and
    /// should be explicitly defined in the derived class.
    ///
    /// \param buffer An output buffer to store the wire data.
    virtual void toWire(isc::util::OutputBuffer& buffer) const = 0;

    /// \brief Render the \c Rdata in the wire format into a
    /// \c MessageRenderer object.
    ///
    /// This is a pure virtual method without the definition; the actual
    /// conversion is specific to each derived concrete class and
    /// should be explicitly defined in the derived class.
    ///
    /// \param renderer DNS message rendering context that encapsulates the
    /// output buffer in which the \c Rdata is to be stored.
    virtual void toWire(AbstractMessageRenderer& renderer) const = 0;
    //@}

    ///
    /// \name Comparison method
    ///
    //@{
    /// \brief Compare two instances of \c Rdata.
    ///
    /// This method compares \c this and the \c other Rdata objects
    /// in terms of the DNSSEC sorting order as defined in RFC4034, and returns
    /// the result as an integer.
    ///
    /// This is a pure virtual method without the definition; the actual
    /// comparison logic is specific to each derived concrete class and
    /// should be explicitly defined in the derived class.
    ///
    /// Specific implementations of this method must confirm that \c this
    /// and the \c other are objects of the same concrete derived class of
    /// \c Rdata.  This is normally done by \c dynamic_cast in the
    /// implementation.  It also means if the assumption isn't met
    /// an exception of class \c std::bad_cast will be thrown.
    ///
    /// Here is an implementation choice: instead of relying on
    /// \c dynamic_cast, we could first convert the data into wire-format
    /// and compare the pair as opaque data.  This would be more polymorphic,
    /// but might involve significant overhead, especially for a large size
    /// of RDATA.
    ///
    /// \param other the right-hand operand to compare against.
    /// \return < 0 if \c this would be sorted before \c other.
    /// \return 0 if \c this is identical to \c other in terms of sorting order.
    /// \return > 0 if \c this would be sorted after \c other.
    virtual int compare(const Rdata& other) const = 0;
    //@}

    /// \brief Get the wire format length of an Rdata.
    ///
    /// IMPLEMENTATION NOTE: Currently this base class implementation is
    /// non-optimal as it renders the wire data to a buffer and returns
    /// the buffer's length. What would perform better is to add
    /// implementations of \c getLength() method to every RDATA
    /// type. This is why this method is virtual. Once all Rdata types
    /// have \c getLength() implementations, this base class
    /// implementation must be removed and the method should become a
    /// pure interface.
    ///
    /// \return The length of the wire format representation of the
    /// RDATA.
    virtual uint16_t getLength() const;
};

namespace generic {

/// \brief The \c GenericImpl class is the actual implementation of the
/// \c generic::Generic class.
///
/// The implementation is hidden from applications.  This approach requires
/// dynamic memory allocation on construction, copy, or assignment, but
/// we believe it should be acceptable as "unknown" RDATA should be pretty
/// rare.
struct GenericImpl;

/// \brief The \c generic::Generic class represents generic "unknown" RDATA.
///
/// This class is used as a placeholder for all non well-known type of RDATA.
/// By definition, the stored data is regarded as opaque binary without
/// assuming any structure.
class Generic : public Rdata {
public:
    ///
    /// \name Constructors, Assignment Operator and Destructor.
    ///
    //@{
    /// \brief Constructor from a string.
    ///
    /// This method constructs a \c generic::Generic object from a textual
    /// representation as defined in RFC3597.
    ///
    /// If \c rdata_string isn't a valid textual representation of this type
    /// of RDATA, an exception of class \c InvalidRdataText or
    /// \c InvalidRdataLength will be thrown.
    /// If resource allocation to store the data fails, a corresponding standard
    /// exception will be thrown.
    ///
    /// \param rdata_string A string of textual representation of generic
    /// RDATA.
    explicit Generic(const std::string& rdata_string);

    ///
    /// \brief Constructor from wire-format data.
    ///
    /// The \c buffer parameter normally stores a complete DNS message
    /// containing the generic RDATA to be constructed.
    /// The current read position of the buffer points to the head of the
    /// data.
    ///
    /// This method reads \c rdata_len bytes from the \c buffer, and internally
    /// stores the data as an opaque byte sequence.
    ///
    /// \c rdata_len must not exceed \c MAX_RDLENGTH; otherwise, an exception
    /// of class \c InvalidRdataLength will be thrown.
    /// If resource allocation to hold the data fails, a corresponding standard
    /// exception will be thrown; if the \c buffer doesn't contain \c rdata_len
    /// bytes of unread data, an exception of class \c InvalidBufferPosition
    /// will be thrown.
    ///
    /// \param buffer A reference to an \c InputBuffer object storing the
    /// \c Rdata to parse.
    /// \param rdata_len The length in buffer of the \c Rdata.  In bytes.
    Generic(isc::util::InputBuffer& buffer, size_t rdata_len);

    /// \brief Constructor from master lexer.
    ///
    Generic(MasterLexer& lexer, const Name* name,
            MasterLoader::Options options, MasterLoaderCallbacks& callbacks);

    ///
    /// \brief The destructor.
    virtual ~Generic();
    ///
    /// \brief The copy constructor.
    ///
    /// If resource allocation to copy the data fails, a corresponding standard
    /// exception will be thrown.
    ///
    /// \param source A reference to a \c generic::Generic object to copy from.
    Generic(const Generic& source);

    ///
    /// \brief The assignment operator.
    ///
    /// If resource allocation to copy the data fails, a corresponding standard
    /// exception will be thrown.
    ///
    /// \param source A reference to a \c generic::Generic object to copy from.
    Generic& operator=(const Generic& source);
    //@}

    ///
    /// \name Converter methods
    ///
    //@{
    /// \brief Convert an \c generic::Generic object to a string.
    ///
    /// This method converts a generic "unknown" RDATA object into a textual
    /// representation of such unknown data as defined in RFC3597.
    ///
    /// If resource allocation to copy the data fails, a corresponding standard
    /// exception will be thrown.
    ///
    /// \return A string representation of \c generic::Generic.
    virtual std::string toText() const;

    ///
    /// \brief Render the \c generic::Generic in the wire format into a buffer.
    ///
    /// This will require \c rdata_len bytes of remaining capacity in the
    /// \c buffer.  If this is not the case and resource allocation for the
    /// necessary memory space fails, a corresponding standard exception will
    /// be thrown.
    ///
    /// \param buffer An output buffer to store the wire data.
    virtual void toWire(isc::util::OutputBuffer& buffer) const;

    /// \brief Render the \c generic::Generic in the wire format into a
    /// \c MessageRenderer object.
    ///
    /// This will require \c rdata_len bytes of remaining capacity in the
    /// \c buffer.  If this is not the case and resource allocation for the
    /// necessary memory space fails, a corresponding standard exception will
    /// be thrown.
    ///
    /// \param renderer DNS message rendering context that encapsulates the
    /// output buffer in which the \c Generic object is to be stored.
    virtual void toWire(AbstractMessageRenderer& renderer) const;
    //@}

    ///
    /// \name Comparison method
    ///
    //@{
    /// \brief Compare two instances of \c generic::Generic objects.
    ///
    /// As defined in RFC4034, this method simply compares the wire-format
    /// representations of the two objects as left-justified unsigned octet
    /// sequences.
    ///
    /// The object referenced by \c other must have been instantiated as
    /// a c generic::Generic class object; otherwise, an exception of class
    /// \c std::bad_cast will be thrown.
    /// Note that the comparison is RR type/class agnostic: this method doesn't
    /// check whether the two \c Rdata objects to compare are of the comparable
    /// RR type/class.  For example, \c this object may come from an \c RRset
    /// of \c RRType x, and the \c other may come from a different \c RRset
    /// of \c RRType y (where x != y).  This situation would be considered a
    /// bug, but this method cannot detect this type of error.
    /// The caller must ensure this condition.
    ///
    /// \param other the right-hand operand to compare against.
    /// \return < 0 if \c this would be sorted before \c other.
    /// \return 0 if \c this is identical to \c other in terms of sorting order.
    /// \return > 0 if \c this would be sorted after \c other.
    virtual int compare(const Rdata& other) const;
    //@}

private:
    GenericImpl* constructFromLexer(MasterLexer& lexer);

    GenericImpl* impl_;
};

///
/// \brief Insert the name as a string into stream.
///
/// This method convert the \c rdata into a string and inserts it into the
/// output stream \c os.
///
/// This function overloads the global \c operator<< to behave as described in
/// \c ostream::operator<< but applied to \c generic::Generic Rdata objects.
///
/// \param os A \c std::ostream object on which the insertion operation is
/// performed.
/// \param rdata The \c Generic object output by the operation.
/// \return A reference to the same \c std::ostream object referenced by
/// parameter \c os after the insertion operation.
std::ostream& operator<<(std::ostream& os, const Generic& rdata);
} // end of namespace "generic"

//
// Non class-member functions related to Rdata
//

///
/// \name Parameterized Polymorphic RDATA Factories
///
/// This set of global functions provide a unified interface to create an
/// \c Rdata object in a parameterized polymorphic way,
/// that is, these functions take a pair of \c RRType and \c RRClass
/// objects and data specific to that pair, and create an object of
/// the corresponding concrete derived class of \c Rdata.
///
/// These will be useful when parsing/constructing a DNS message or
/// parsing a master file, where information for a specific type of RDATA
/// is given but the resulting object, once created, should better be used
/// in a polymorphic way.
///
/// For example, if a master file parser encounters an NS RR
/// \verbatim example.com. 3600 IN NS ns.example.com.\endverbatim
/// it stores the text fragments "IN", "NS", and "ns.example.com." in
/// \c std::string objects \c class_txt, \c type_txt, and \c nsname_txt,
/// respectively, then it would create a new \c RdataPtr object as follows:
/// \code RdataPtr rdata = createRdata(RRType(type_txt), RRClass(class_txt),
///                              nsname_txt); \endcode
/// On success, \c rdata will point to an object of the \c generic::NS class
/// that internally holds a domain name of "ns.example.com."
///
/// Internally, these functions uses the corresponding
/// \c RRParamRegistry::createRdata methods of the \c RRParamRegistry.
/// See also the description on these methods for related notes.
//@{
/// \brief Create RDATA of a given pair of RR type and class from a string.
///
/// This method creates from a string an \c Rdata object of the given pair
/// of RR type and class.
///
/// \param rrtype An \c RRType object specifying the type/class pair.
/// \param rrclass An \c RRClass object specifying the type/class pair.
/// \param rdata_string A string of textual representation of the \c Rdata.
/// \return An \c RdataPtr object pointing to the created \c Rdata
/// object.
RdataPtr createRdata(const RRType& rrtype, const RRClass& rrclass,
                     const std::string& rdata_string);

/// \brief Create RDATA of a given pair of RR type and class from
/// wire-format data.
///
/// This method creates from wire-format binary data an \c Rdata object
/// of the given pair of RR type and class.
///
/// \c len must not exceed the protocol defined maximum value, \c MAX_RDLENGTH;
/// otherwise, an exception of class \c InvalidRdataLength will be thrown.
///
/// In some cases, the length of the RDATA is determined without the
/// information of \c len.  For example, the RDATA length of an IN/A RR
/// must always be 4.  If \c len is not equal to the actual length in such
/// cases, an exception of class InvalidRdataLength will be thrown.
///
/// \param rrtype An \c RRType object specifying the type/class pair.
/// \param rrclass An \c RRClass object specifying the type/class pair.
/// \param buffer A reference to an \c InputBuffer object storing the
/// \c Rdata to parse.
/// \param len The length in buffer of the \c Rdata.  In bytes.
/// \return An \c RdataPtr object pointing to the created \c Rdata
/// object.
RdataPtr createRdata(const RRType& rrtype, const RRClass& rrclass,
                     isc::util::InputBuffer& buffer, size_t len);

/// \brief Create RDATA of a given pair of RR type and class, copying
/// of another RDATA of same kind.
///
/// This method creates an \c Rdata object of the given pair of
/// RR type and class, copying the  content of the given \c Rdata,
/// \c source.
///
/// \param rrtype An \c RRType object specifying the type/class pair.
/// \param rrclass An \c RRClass object specifying the type/class pair.
/// \param source A reference to an \c Rdata object whose content
/// is to be copied to the created \c Rdata object.
/// \return An \c RdataPtr object pointing to the created
/// \c Rdata object.
RdataPtr createRdata(const RRType& rrtype, const RRClass& rrclass,
                     const Rdata& source);

/// \brief Create RDATA of a given pair of RR type and class using the
/// master lexer.
///
/// This is a more generic form of factory from textual RDATA, and is mainly
/// intended to be used internally by the master file parser (\c MasterLoader)
/// of this library.
///
/// The \c lexer is expected to be at the beginning of textual RDATA of the
/// specified type and class.  This function (and its underlying Rdata
/// implementations) extracts necessary tokens from the lexer and constructs
/// the RDATA from them.
///
/// Due to the intended usage of this version, this function handles error
/// cases quite differently from other versions.  It internally catches
/// most of syntax and semantics errors of the input (reported as exceptions),
/// calls the corresponding callback specified by the \c callbacks parameters,
/// and returns a NULL smart pointer.  If the caller rather wants to get
/// an exception in these cases, it can pass a callback that internally
/// throws on error.  Some critical exceptions such as \c std::bad_alloc are
/// still propagated to the upper layer as it doesn't make sense to try
/// recovery from such a situation within this function.
///
/// Whether or not the creation succeeds, this function updates the lexer
/// until it reaches either the end of line or file, starting from the end of
/// the RDATA text (or the point of failure if the parsing fails in the
/// middle of it).  The caller can therefore assume it's ready for reading
/// the next data (which is normally a subsequent RR in the zone file) on
/// return, whether or not this function succeeds.
///
/// \param rrtype An \c RRType object specifying the type/class pair.
/// \param rrclass An \c RRClass object specifying the type/class pair.
/// \param lexer A \c MasterLexer object parsing a master file for the
/// RDATA to be created
/// \param origin If non NULL, specifies the origin of any domain name fields
/// of the RDATA that are non absolute.
/// \param options Master loader options controlling how to deal with errors
/// or non critical issues in the parsed RDATA.
/// \param callbacks Callback to be called when an error or non critical issue
/// is found.
/// \return An \c RdataPtr object pointing to the created
/// \c Rdata object.  Will be NULL if parsing fails.
RdataPtr createRdata(const RRType& rrtype, const RRClass& rrclass,
                     MasterLexer& lexer, const Name* origin,
                     MasterLoader::Options options,
                     MasterLoaderCallbacks& callbacks);

//@}

///
/// \brief Gives relative ordering of two names in terms of DNSSEC RDATA
/// ordering.
///
/// This method compares two names as defined in Sections 6.2 and 6.3 of
/// RFC4034: Comparing two names in their canonical form
/// (i.e., converting upper case ASCII characters to lower ones) and
/// as a left-justified unsigned octet sequence.  Note that the ordering is
/// different from that for owner names.  For example, "a.example" should be
/// sorted before "example" as RDATA, but the ordering is the opposite when
/// compared as owner names.
///
/// Normally, applications would not need this function directly.
/// This is mostly an internal helper function for \c Rdata related classes
/// to implement their \c compare() method.
/// This function is publicly open, however, for the convenience of
/// external developers who want to implement new or experimental RR types.
///
/// This function never throws an exception as long as the given names are
/// valid \c Name objects.
///
/// Additional note about applicability: In fact, BIND9's similar function,
/// \c dns_name_rdatacompare(), is only used in rdata implementations and
/// for testing purposes.
///
/// \param n1,n2 \c Name class objects to compare.
/// \return -1 if \c n1 would be sorted before \c n2.
/// \return 0 if \c n1 is identical to \c n2 in terms of sorting order.
/// \return 1 if \c n1 would be sorted after \c n2.
///
int compareNames(const Name& n1, const Name& n2);

} // end of namespace "rdata"
}
}
#endif  // RDATA_H

// Local Variables:
// mode: c++
// End:
