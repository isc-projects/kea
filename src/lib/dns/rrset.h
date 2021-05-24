// Copyright (C) 2010-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef RRSET_H
#define RRSET_H 1

#include <iostream>
#include <string>

#include <boost/shared_ptr.hpp>

#include <dns/exceptions.h>

#include <dns/rdata.h>
#include <dns/rrtype.h>

namespace isc {
namespace util {
class OututBuffer;
}

namespace dns {

///
/// \brief A standard DNS module exception that is thrown if an RRset object
/// does not contain any RDATA where required.
///
class EmptyRRset : public isc::dns::Exception {
public:
    EmptyRRset(const char* file, size_t line, const char* what) :
        isc::dns::Exception(file, line, what) {}
};

// forward declarations
class Name;
class RRType;
class RRClass;
class RRTTL;
class AbstractMessageRenderer;
class AbstractRRset;
class BasicRRset;
class RdataIterator;
class BasicRRsetImpl;
class RRset;

/// \brief A pointer-like type pointing to an \c RRset object.
///
/// This type is commonly used as an argument of various functions defined
/// in this library in order to handle RRsets in a polymorphic manner.
typedef boost::shared_ptr<AbstractRRset> RRsetPtr;

/// \brief A pointer-like type pointing to an (immutable) \c RRset
/// object.
///
/// This type is commonly used as an argument of various functions defined
/// in this library in order to handle RRsets in a polymorphic manner.
typedef boost::shared_ptr<const AbstractRRset> ConstRRsetPtr;

/// \brief A pointer-like type point to an \c RdataIterator object.
typedef boost::shared_ptr<RdataIterator> RdataIteratorPtr;

/// \brief The \c AbstractRRset class is an abstract base class that
/// models a DNS RRset.
///
/// An object of (a specific derived class of) \c AbstractRRset
/// models an RRset as described in the DNS standard:
/// A set of DNS resource records (RRs) of the same type and class.
/// The standard requires the TTL of all RRs in an RRset be the same;
/// this class follows that requirement.

/// Note about duplicate RDATA: RFC2181 states that it's meaningless that an
/// RRset contains two identical RRs and that name servers should suppress
/// such duplicates.
/// This class is not responsible for ensuring this requirement: For example,
/// \c addRdata() method doesn't check if there's already RDATA identical
/// to the one being added.
/// This is because such checks can be expensive, and it's often easy to
/// ensure the uniqueness requirement at the %data preparation phase
/// (e.g. when loading a zone).
/// When parsing an incoming DNS message, the uniqueness may not be guaranteed,
/// so the application needs to detect and ignore any duplicate RDATA
/// (the \c Message class of this library should provide this responsibility).
///
/// Another point to note is that \c AbstractRRset and its derived classes
/// allow an object to have an empty set of RDATA.
/// Even though there's no corresponding notion in the protocol specification,
/// it would be more intuitive for a container-like %data structure
/// to allow an empty set.
///
/// Since \c AbstractRRset is an abstract class, it is generally used
/// via a pointer (or pointer like object) or a reference.
/// In particular, \c RRsetPtr, a pointer like type for \c AbstractRRset,
/// is used for polymorphic RRset operations throughout this library.
///
/// The \c AbstractRRset class is also intended to be a major customization
/// point.  For example, a high performance server implementation may want
/// to define an optimized "pre-compiled" RRset and provide an optimized
/// implementation of the \c toWire() method.
///
/// Note about design choice: In BIND9, a set of RDATA with a common tuple
/// of RR class, RR type, and TTL was represented in a structure named
/// \c rdataset.  Unlike the RRset classes, an \c rdataset did not contain
/// the information of the owner name.
/// This might be advantageous if we want to handle "RRsets", that is,
/// a set of different types of RRset for the same owner name, because
/// a single "name" structure can be used for multiple RRsets, minimizing
/// %data copy and memory footprint.
/// On the other hand, it's inconvenient for API users since in many cases
/// a pair of name and an \c rdataset must be maintained.  It's also counter
/// intuitive in implementing protocol operations as an RRset is often used
/// as an atomic entity in DNS protocols while an \c rdataset is a component
/// of an RRset.
///
/// We have therefore defined the notion of RRset explicitly in our initial
/// API design.  We believe memory footprint is not a big concern because
/// RRsets are generally expected to be used as temporary objects, e.g.
/// while parsing or constructing a DNS message, or searching a DNS %data
/// source; for longer term purposes such as in-memory %data source entries,
/// the corresponding %data would be represented in a different, memory
/// optimized format.  As for the concern about %data copy, we believe
/// it can be mitigated by using copy-efficient implementation for the
/// \c Name class implementation, such as reference counted objects.
/// Later, We plan to perform benchmark tests later to see if this assumption
/// is valid and to revisit the design if necessary.
///
/// Note about terminology: there has been a discussion at the IETF
/// namedroppers ML about RRset vs RRSet (case of "s")
/// [http://ops.ietf.org/lists/namedroppers/namedroppers.2009/msg02737.html].
/// While RFC2181 uses the latter, many other RFCs use the former,
/// and most of the list members who showed their opinion seem to prefer
/// "RRset".  We follow that preference in this implementation.
///
/// The current design of \c AbstractRRset is still in flux.
/// There are many open questions in design details:
///   - support more set-like operations, e.g, merge two RRsets of the same
///     type?
///   - more convenient methods or non member utility functions, e.g.
///      "sort" and "search(find)" method?
///   - what about comparing two RRsets of the same type?  If we need this,
///     should it compare rdata's as a set or as a list (i.e. compare
///     each rdata one by one or as a whole)?  c.f. NLnet Labs' ldns
///     (http://www.nlnetlabs.nl/projects/ldns/doc/index.html)
///     has \c ldns_rr_list_compare(), which takes the latter approach
///     (seemingly assuming the caller sorts the lists beforehand).
///   - BIND9 libdns has some special DNSSEC-related methods
///     such as \c addnoqname() or \c addclosest().  Do we need these?
///     (Probably not.  We wouldn't want to make the class design too
///     monolithic.)
///   - Do we need to allow the user to remove specific Rdata?
///     Probably not, according to the current usage of the BIND9 code.
class AbstractRRset {
    ///
    /// \name Constructors and Destructor
    ///
    /// Note: The copy constructor and the assignment operator are intentionally
    /// defined as private to make it explicit that this is a pure base class.
    //@{
private:
    AbstractRRset(const AbstractRRset& source);
    AbstractRRset& operator=(const AbstractRRset& source);
protected:
    /// \brief The default constructor.
    ///
    /// This is intentionally defined as \c protected as this base class should
    /// never be instantiated (except as part of a derived class).
    AbstractRRset() {}
public:
    /// The destructor.
    virtual ~AbstractRRset() {}
    //@}

    ///
    /// \name Getter and Setter Methods
    ///
    /// These methods are generally expected to be exception free, but it's
    /// not guaranteed at the interface level;
    /// for example, some performance optimized derived class may manage
    /// the information corresponding to the class "attributes" to get or set,
    /// and may require dynamic memory allocation to execute the method.
    /// Consult the derived class description to see if a specific derived
    /// \c RRset class may throw an exception from these methods.
    ///
    /// Note that setter methods are not provided for \c RRClass and
    /// \c RRType.  This is intentional.  Since the format and semantics of
    /// \c Rdata are dependent on the RR type (and RR class for some RR types),
    /// allowing dynamically modify these attributes can easily lead to a
    /// bug where the RDATA and type and/or class become inconsistent.
    /// We want to avoid that situation by restricting the access.
    //@{
    /// \brief Returns the number of \c Rdata objects contained in the \c RRset.
    ///
    /// Note that an \c RRset with an empty set of \c Rdata can exist, so
    /// this method may return 0.
    ///
    /// \return The number of \c Rdata objects contained.
    virtual unsigned int getRdataCount() const = 0;

    /// \brief Get the wire format length of the \c AbstractRRset.
    ///
    /// This method returns the wire format length of the
    /// \c AbstractRRset, which is calculated by summing the individual
    /// lengths of the various fields that make up each RR.
    ///
    /// NOTE: When including name lengths, the allocation for
    /// uncompressed name wire format representation is used.
    ///
    /// \return The length of the wire format representation of the
    /// \c AbstractRRset.
    /// \throw EmptyRRset if the \c AbstractRRset is empty.
    virtual uint16_t getLength() const = 0;

    /// \brief Returns the owner name of the \c RRset.
    ///
    /// \return A reference to a \c Name class object corresponding to the
    /// \c RRset owner name.
    virtual const Name& getName() const = 0;

    /// \brief Returns the RR Class of the \c RRset.
    ///
    /// \return A reference to a \c RRClass class object corresponding to the
    /// RR class of the \c RRset.
    virtual const RRClass& getClass() const = 0;

    /// \brief Returns the RR Type of the \c RRset.
    ///
    /// \return A reference to a \c RRType class object corresponding to the
    /// RR type of the \c RRset.
    virtual const RRType& getType() const = 0;

    /// \brief Returns the TTL of the RRset.
    ///
    /// \return A reference to a \c RRTTL class object corresponding to the
    /// TTL of the \c RRset.
    virtual const RRTTL& getTTL() const = 0;

    /// \brief Updates the TTL of the \c RRset.
    ///
    /// \param ttl A reference to a \c RRTTL class object to be copied as the
    /// new TTL.
    virtual void setTTL(const RRTTL& ttl) = 0;
    //@}

    ///
    /// \name Converter Methods
    ///
    /// These methods have the default implementation that can be reused by
    /// derived classes.
    /// Since they are defined as pure virtual, derived classes
    /// that want to reuse the default implementation must explicitly
    /// invoke their base class version (see the description for
    /// <code>addRdata(const rdata::Rdata&)</code>).
    ///
    /// Design Note: the default implementations are defined only using
    /// other public methods of the \c AbstractRRset class, and could be
    /// implemented as non member functions (as some C++ textbooks suggest).
    /// However, since derived classes may want to provide customized versions
    /// (especially of the \c toWire() method for performance reasons)
    /// we chose to define them as virtual functions, and, as a result,
    /// member functions.
    //@{
    /// \brief Convert the RRset to a string.
    ///
    /// Unlike other similar methods of this library, this method terminates
    /// the resulting string with a trailing newline character.
    /// (following the BIND9 convention)
    ///
    /// If any RRSIGs are associated with the RRset, they are also
    /// appended to the returned string.
    ///
    /// If the class is not ANY or NONE, the RRset must contain some RDATA;
    /// otherwise, an exception of class \c EmptyRRset will be thrown.
    /// If resource allocation fails, a corresponding standard exception
    /// will be thrown.
    /// The default implementation may throw other exceptions if the
    /// \c toText() method of the RDATA objects throws.
    /// If a derived class of \c AbstractRRset overrides the default
    /// implementation, the derived version may throw its own exceptions.
    ///
    /// Open issue: We may want to support multiple output formats as
    /// BIND9 does.  For example, we might want to allow omitting the owner
    /// name when possible in the context of zone dump.  This is a future
    /// TODO item.
    ///
    /// \return A string representation of the RRset.
    virtual std::string toText() const = 0;

    /// \brief Render the RRset in the wire format with name compression and
    /// truncation handling.
    ///
    /// This method compresses the owner name of the RRset and domain names
    /// used in RDATA that should be compressed.
    /// In addition, this method detects the case where rendering the entire
    /// RRset would cause truncation, and handles the case appropriately
    /// (this is a TODO item, and not implemented in this version).
    ///
    /// If any RRSIGs are associated with the RRset, they are also rendered.
    ///
    /// Note: perhaps we may want to add more arguments to convey optional
    /// information such as an "rrset-order" policy or how to handle truncation
    /// case.  This is a TODO item.
    ///
    /// If resource allocation fails, a corresponding standard exception
    /// will be thrown.
    /// If the class is not ANY or NONE, the RRset must contain some RDATA;
    /// otherwise, an exception of class \c EmptyRRset will be thrown.
    /// The default implementation may throw other exceptions if the
    /// \c toWire() method of the RDATA objects throws.
    /// If a derived class of \c AbstractRRset overrides the default
    /// implementation, the derived version may throw its own exceptions.
    ///
    /// \param renderer DNS message rendering context that encapsulates the
    /// output buffer and name compression information.
    /// \return The number of RRs rendered.  If the truncation is necessary
    /// this value may be different from the number of RDATA objects contained
    /// in the RRset.
    virtual unsigned int toWire(AbstractMessageRenderer& renderer) const = 0;

    /// \brief Render the RRset in the wire format without any compression.
    ///
    /// See the other toWire() description about possible exceptions.
    ///
    /// \param buffer An output buffer to store the wire data.
    /// \return The number of RRs rendered.
    virtual unsigned int toWire(isc::util::OutputBuffer& buffer) const = 0;
    //@}

    ///
    /// \name RDATA Manipulation Methods
    ///
    //@{
    /// \brief Add an RDATA to the RRset (pointer version).
    ///
    /// This method adds the given RDATA (as a pointer-like type to a
    /// derived class object of \c rdata::Rdata) to the \c RRset.
    ///
    /// \param rdata A pointer (like) type of \c rdata::RdataPtr to be added
    /// to the \c RRset.
    virtual void addRdata(rdata::ConstRdataPtr rdata) = 0;

    /// \brief Add an RDATA to the RRset (reference version).
    ///
    /// This method adds the given RDATA (as a reference to a
    /// derived class object of \c rdata::Rdata) to the \c RRset.
    ///
    /// This method has the default implementation that can be reused by
    /// derived classes.
    /// Since this method is defined as pure virtual, derived classes
    /// that want to reuse the default implementation must explicitly
    /// invoke this base class version.
    /// For example, if the class \c CustomizedRRset, a derived class of
    /// \c AbstractRRset, wants to reuse the default implementation of
    /// \c %addRdata() (reference version), it would be defined as follows:
    /// \code void
    /// CustomizedRRset::addRdata(const rdata::Rdata& rdata)
    /// {
    ///     AbstractRRset::addRdata(rdata);
    /// }
    /// \endcode
    ///
    /// This method is more strictly typed than the pointer version:
    /// If \c rdata does not refer to the appropriate derived
    /// \c Rdata class
    /// for the \c RRType for this \c RRset, it throws an exception of class
    /// \c std::bad_cast.
    /// If resource allocation fails, a corresponding standard exception
    /// will be thrown.
    /// The RRset must contain some RDATA; otherwise, an exception of class
    /// \c EmptyRRset will be thrown.
    /// The default implementation may throw other exceptions if the
    /// \c toWire() method of the RDATA objects throws.
    /// If a derived class of \c AbstractRRset overrides the default
    /// implementation, the derived version may throw its own exceptions.
    ///
    /// The default implementation simply constructs an \c rdata::RdataPtr
    /// object from a newly allocated RDATA object copying from parameter
    /// \c rdata, and calls the other version of
    /// \c addRdata(const rdata::RdataPtr).
    /// So it is inherently less efficient than the other version.
    /// Still, this version would offer a more intuitive interface and is
    /// provided as such.
    ///
    /// NOTE: Because a new Rdata object is constructed, this method can
    /// throw a std::bad_cast exception if this RRset's class is NONE,
    /// or if some other error occurs. If you want to be able to add
    /// RDATA to an RRset whose class is NONE, please use the other
    /// variant of \c addRdata() which accepts a \c ConstRdataPtr
    /// argument.
    ///
    /// \param rdata A reference to a \c rdata::RdataPtr (derived) class
    /// object, a copy of which is to be added to the \c RRset.
    virtual void addRdata(const rdata::Rdata& rdata) = 0;

    /// \brief Add an RDATA to the RRset (string version).
    ///
    /// This method constructs an Rdata object from the given
    /// \c rdata_str in presentation format and adds it to the \c RRset.
    ///
    /// \param rdata_str RDATA string in presentation format.
    /// \throw InvalidRdataText if the \c rdata_str is invalid for this
    /// \c RRset.
    virtual void addRdata(const std::string& rdata_str) = 0;

    /// \brief Return an iterator to go through all RDATA stored in the
    /// \c RRset.
    ///
    /// The rdata cursor of the returned iterator will point to the first
    /// RDATA, that is, it effectively calls \c RdataIterator::first()
    /// internally.
    ///
    /// Using the design pattern terminology, \c getRdataIterator()
    /// is an example of a <em>factory method</em>.
    ///
    /// Whether this method throws an exception depends on the actual
    /// implementation of the derived \c AbstractRRset class, but in general
    /// it will involve resource allocation and can throw a standard exception
    /// if it fails.
    ///
    /// \return A pointer-like object pointing to the derived \c RdataIterator
    /// object.
    virtual RdataIteratorPtr getRdataIterator() const = 0;
    //@}

    ///
    /// \name Associated RRSIG methods
    ///
    /// These methods access an "associated" RRset, that containing the DNSSEC
    /// signatures for this RRset.  It can be argued that this is not a
    /// fundamental part of the RRset abstraction, since RFC 2181 defined an
    /// RRset as a group of records with the same label, class and type but
    /// different data.  However, BIND 10 had to deal with DNSSEC and in
    /// practice, including the information at the AbstractRRset level makes
    /// implementation easier.  (If a class is ever needed that must be
    /// ignorant of the idea of an associated RRSIG RRset - e.g. a specialised
    /// RRSIG RRset class - these methods can just throw a "NotImplemented"
    /// exception.) DNSSEC is unlikely to be ever needed in Kea, but it does
    /// not make sense to redesign the abstract RRSet class now.
    //@{
    /// \brief Return pointer to this RRset's RRSIG RRset
    ///
    /// \return Pointer to the associated RRSIG RRset or null if there is none.
    virtual RRsetPtr getRRsig() const = 0;

    /// \brief Returns the number of \c RRSIG records associated with
    /// the \c RRset.
    ///
    /// Note that an \c RRset with no RRSIG records may exist, so this
    /// method may return 0.
    ///
    /// \return The number of \c RRSIG records associated.
    virtual unsigned int getRRsigDataCount() const = 0;

    /// \brief Adds RRSIG RRset RRs to the associated RRSIG RRset
    ///
    /// Adds the (assumed) RRSIG rdata the RRSIG RRset associated with this
    /// RRset.  If one does not exist, it is created using the data given.
    ///
    /// \param rdata Pointer to RRSIG rdata to be added.
    virtual void addRRsig(const rdata::ConstRdataPtr& rdata) = 0;

    /// \brief Adds RRSIG RRset RRs to the associated RRSIG RRset
    ///
    /// Adds the (assumed) RRSIG rdata the RRSIG RRset associated with this
    /// RRset.  If one does not exist, it is created using the data given.
    ///
    /// (This overload is for an older version of boost that doesn't support
    /// conversion from shared_ptr<X> to shared_ptr<const X>.)
    ///
    /// \param rdata Pointer to RRSIG rdata to be added.
    virtual void addRRsig(const rdata::RdataPtr& rdata) = 0;

    /// \brief Adds RRSIG RRset RRs to the associated RRSIG RRset
    ///
    /// Adds the signatures in the given (assumed) RRSIG RRset to the RRSIG
    /// RRset associated with this RRset.  If one does not exist, it is created
    /// using the data given.
    ///
    /// \param sigs RRSIG RRset containing signatures to be added to the
    ///             RRSIG RRset associated with this class.
    virtual void addRRsig(const AbstractRRset& sigs) = 0;

    /// \brief Adds RRSIG RRset RRs to the associated RRSIG RRset
    ///
    /// Adds the signatures in the given (assumed) RRSIG RRset to the RRSIG
    /// RRset associated with this RRset.  If one does not exist, it is created
    /// using the data given.
    ///
    /// \param sigs Pointer to a RRSIG RRset containing signatures to be added
    ///             to the RRSIG RRset associated with this class.
    virtual void addRRsig(const ConstRRsetPtr& sigs) = 0;

    /// \brief Adds RRSIG RRset RRs to the associated RRSIG RRset
    ///
    /// Adds the signatures in the given (assumed) RRSIG RRset to the RRSIG
    /// RRset associated with this RRset.  If one does not exist, it is created
    /// using the data given.
    ///
    /// (This overload is for an older version of boost that doesn't support
    /// conversion from shared_ptr<X> to shared_ptr<const X>.)
    ///
    /// \param sigs Pointer to a RRSIG RRset containing signatures to be added
    ///             to the RRSIG RRset associated with this class.
    virtual void addRRsig(const RRsetPtr& sigs) = 0;

    /// \brief Clear the RRSIGs for this RRset
    virtual void removeRRsig() = 0;

    /// \brief Check whether two RRsets are of the same kind
    ///
    /// Checks if two RRsets have the same name, RR type, and RR class.
    ///
    /// \param other Pointer to another AbstractRRset to compare
    ///              against.
    virtual bool isSameKind(const AbstractRRset& other) const;
    //@}

};

/// \brief The \c RdataIterator class is an abstract base class that
/// provides an interface for accessing RDATA objects stored in an RRset.
///
/// While different derived classes of \c AbstractRRset may maintain the RDATA
/// objects in different ways, the \c RdataIterator class provides a
/// unified interface to iterate over the RDATA objects in a polymorphic
/// manner.
///
/// Each derived class of \c AbstractRRset is expected to provide a concrete
/// derived class of \c RdataIterator, and each derived \c RdataIterator
/// class implements the unified interface in a way specific to the
/// implementation of the corresponding derived \c AbstractRRset class.
/// Using the design pattern terminology, this is a typical example of
/// the \e Iterator pattern.
///
/// The RDATA objects stored in the \c RRset are considered to form
/// a unidirectional list from the \c RdataIterator point of view (while
/// the actual implementation in the derived \c RRset may not use a list).
/// We call this unidirectional list the <em>rdata list</em>.
///
/// An \c RdataIterator object internally (and conceptually) holds a
/// <em>rdata cursor</em>, which points to a specific item of the rdata list.
///
/// Note about design choice: as is clear from the interface, \c RdataIterator
/// is not compatible with the standard iterator classes.
/// Although it would be useful (for example, we could then use STL algorithms)
/// and is not necessarily impossible, it would make the iterator implementation
/// much more complicated.
/// For instance, any standard iterator must be assignable and
/// copy-constructible.
/// So we'd need to implement \c RdataIterator::operator=() in a polymorphic
/// way.  This will require non-trivial implementation tricks.
/// We believe the simplified iterator interface as provided by the
/// \c RdataIterator class is sufficient in practice:
/// Most applications will simply go through the RDATA objects contained in
/// an RRset, examining (and possibly using) each object, as one path
/// operation.
class RdataIterator {
    ///
    /// \name Constructors and Destructor
    ///
    /// Note: The copy constructor and the assignment operator are intentionally
    /// defined as private to make it explicit that this is a pure base class.
    //@{
protected:
    /// \brief The default constructor.
    ///
    /// This is intentionally defined as \c protected as this base class should
    /// never be instantiated (except as part of a derived class).
    RdataIterator() {}
public:
    /// \brief Destructor
    virtual ~RdataIterator() {}
private:
    RdataIterator(const RdataIterator& source);
    RdataIterator& operator=(const RdataIterator& source);
    //@}

public:
    /// \brief Move the rdata cursor to the first RDATA in the rdata list
    /// (if any).
    ///
    /// This method can safely be called multiple times, even after moving
    /// the rdata cursor forward by the \c next() method.
    ///
    /// This method should never throw an exception.
    virtual void first() = 0;

    /// \brief Move the rdata cursor to the next RDATA in the rdata list
    /// (if any).
    ///
    /// This method should never throw an exception.
    virtual void next() = 0;

    /// \brief Return the current \c Rdata corresponding to the rdata cursor.
    ///
    /// \return A reference to an \c rdata::Rdata object corresponding
    /// to the rdata cursor.
    virtual const rdata::Rdata& getCurrent() const = 0;

    /// \brief Return true iff the rdata cursor has reached the end of the
    /// rdata list.
    ///
    /// Once this method returns \c true, the behavior of any subsequent
    /// call to \c next() or \c getCurrent() is undefined.
    /// Likewise, the result of \c isLast() call followed by such undefined
    /// operations is also undefined.
    ///
    /// This method should never throw an exception.
    ///
    /// \return \c true if the rdata cursor has reached the end of the
    /// rdata list; otherwise \c false.
    virtual bool isLast() const = 0;
};

/// \brief The \c BasicRRset class is a concrete derived class of
/// \c AbstractRRset that defines a straightforward RRset implementation.
///
/// This class is designed to be as portable as possible, and so it adopts
/// the Pimpl idiom to hide as many details as possible.
/// Performance is a secondary concern for this class.
///
/// This class is intended to be used by applications that only need
/// moderate level of performance with full functionality provided by
/// the \c AbstractRRset interfaces.
/// Highly performance-sensitive applications, such as a large scale
/// authoritative or caching name servers will implement and use a customized
/// version of derived \c AbstractRRset class.
class BasicRRset : public AbstractRRset {
    ///
    /// \name Constructors and Destructor
    ///
    /// Note: The copy constructor and the assignment operator are intentionally
    /// defined as private.  The intended use case wouldn't require copies of
    /// a \c BasicRRset object; once created, it would normally be used
    /// as a \c const object (via references).
    //@{
private:
    BasicRRset(const BasicRRset& source);
    BasicRRset& operator=(const BasicRRset& source);
public:
    /// \brief Constructor from (mostly) fixed parameters of the RRset.
    ///
    /// This constructor is normally expected to be exception free, but
    /// copying the name may involve resource allocation, and if it fails
    /// the corresponding standard exception will be thrown.
    ///
    /// \param name The owner name of the RRset.
    /// \param rrclass The RR class of the RRset.
    /// \param rrtype The RR type of the RRset.
    /// \param ttl The TTL of the RRset.
    BasicRRset(const Name& name, const RRClass& rrclass,
               const RRType& rrtype, const RRTTL& ttl);
    /// \brief The destructor.
    virtual ~BasicRRset();
    //@}

    ///
    /// \name Getter and Setter Methods
    ///
    //@{
    /// \brief Returns the number of \c Rdata objects contained in the \c RRset.
    ///
    /// This method never throws an exception.
    ///
    /// \return The number of \c Rdata objects contained.
    virtual unsigned int getRdataCount() const;

    /// \brief Get the wire format length of the \c BasicRRset.
    ///
    /// \return The length of the wire format representation of the
    /// \c BasicRRset.
    /// \throw EmptyRRset if the \c BasicRRset is empty.
    virtual uint16_t getLength() const;

    /// \brief Returns the owner name of the \c RRset.
    ///
    /// This method never throws an exception.
    ///
    /// \return A reference to a \c Name class object corresponding to the
    /// \c RRset owner name.
    virtual const Name& getName() const;

    /// \brief Returns the RR Class of the \c RRset.
    ///
    /// This method never throws an exception.
    ///
    /// \return A reference to a \c RRClass class object corresponding to the
    /// RR class of the \c RRset.
    virtual const RRClass& getClass() const;

    /// \brief Returns the RR Type of the \c RRset.
    ///
    /// This method never throws an exception.
    ///
    /// \return A reference to a \c RRType class object corresponding to the
    /// RR type of the \c RRset.
    virtual const RRType& getType() const;

    /// \brief Returns the TTL of the \c RRset.
    ///
    /// This method never throws an exception.
    ///
    /// \return A reference to a \c RRTTL class object corresponding to the
    /// TTL of the \c RRset.
    virtual const RRTTL& getTTL() const;

    /// \brief Updates the TTL of the \c RRset.
    ///
    /// This method never throws an exception.
    ///
    /// \param ttl A reference to a \c RRTTL class object to be copied as the
    /// new TTL.
    virtual void setTTL(const RRTTL& ttl);
    //@}

    ///
    /// \name Converter Methods
    ///
    //@{
    /// \brief Convert the RRset to a string.
    ///
    /// This method simply uses the default implementation.
    /// See \c AbstractRRset::toText().
    virtual std::string toText() const;

    /// \brief Render the RRset in the wire format with name compression and
    /// truncation handling.
    ///
    /// This method simply uses the default implementation.
    /// See \c AbstractRRset::toWire(MessageRenderer&)const.
    virtual unsigned int toWire(AbstractMessageRenderer& renderer) const;

    /// \brief Render the RRset in the wire format without any compression.
    ///
    /// This method simply uses the default implementation.
    /// See \c AbstractRRset::toWire(OutputBuffer&)const.
    virtual unsigned int toWire(isc::util::OutputBuffer& buffer) const;
    //@}

    ///
    /// \name RDATA manipulation methods
    ///
    //@{
    /// \brief Add an RDATA to the RRset (pointer version).
    ///
    /// This method is normally expected to be exception free, but it may
    /// involve resource allocation, and if it fails the corresponding
    /// standard exception will be thrown.
    ///
    /// \param rdata A pointer (like) type of \c rdata::RdataPtr to be added
    /// to the \c BasicRRset.
    virtual void addRdata(rdata::ConstRdataPtr rdata);

    /// \brief Add an RDATA to the RRset (reference version).
    ///
    /// This method simply uses the default implementation.
    /// See \c AbstractRRset::addRdata(const rdata::Rdata&).
    virtual void addRdata(const rdata::Rdata& rdata);

    /// \brief Add an RDATA to the RRset (string version).
    ///
    /// \param rdata_str RDATA string in presentation format.
    /// \throw InvalidRdataText if the \c rdata_str is invalid for this
    /// \c RRset.
    virtual void addRdata(const std::string& rdata_str);

    /// \brief Return an iterator to go through all RDATA stored in the
    /// \c BasicRRset.
    ///
    /// This is a concrete derived implementation of
    /// \c AbstractRRset::getRdataIterator().
    ///
    /// This method dynamically allocates resources.  If it fails it will
    /// throw the corresponding standard exception.
    /// The iterator methods for the \c BasicRRset class are exception free.
    ///
    /// \return A pointer-like object pointing to the derived \c RdataIterator
    /// object for the \c BasicRRset class.
    virtual RdataIteratorPtr getRdataIterator() const;
    //@}

    ///
    /// \name Associated RRSIG methods
    ///
    /// The associated RRSIG RRset is not supported in BasicRRset.  For
    /// ease of use, getRRsig() returns a null pointer (indicating no RRset).
    /// The addRRsig()/removeRRsig() methods throw a "NotImplemented"
    /// exception - if you are using a BasicRRset, you should not be trying
    /// to modify signatures on it.
    //@{
    /// \brief Return pointer to this RRset's RRSIG RRset
    ///
    /// \return Null pointer, as this class does not support RRSIG records.
    virtual RRsetPtr getRRsig() const {
        return (RRsetPtr());
    }

    /// \brief Returns the number of \c RRSIG records associated with
    /// the \c RRset.
    ///
    /// \return Always returns 0. Associated RRSIG RRsets are not
    ///         supported in this class.
    virtual unsigned int getRRsigDataCount() const {
        return (0);
    }

    virtual void addRRsig(const rdata::ConstRdataPtr&) {
        isc_throw(NotImplemented,
                  "BasicRRset does not implement the addRRsig() method");
    }

    virtual void addRRsig(const rdata::RdataPtr&) {
        isc_throw(NotImplemented,
                  "BasicRRset does not implement the addRRsig() method");
    }

    virtual void addRRsig(const AbstractRRset&) {
        isc_throw(NotImplemented,
                  "BasicRRset does not implement the addRRsig() method");
    }

    virtual void addRRsig(const ConstRRsetPtr&) {
        isc_throw(NotImplemented,
                  "BasicRRset does not implement the addRRsig() method");
    }

    virtual void addRRsig(const RRsetPtr&) {
        isc_throw(NotImplemented,
                  "BasicRRset does not implement the addRRsig() method");
    }

    virtual void removeRRsig() {
        isc_throw(NotImplemented,
                  "BasicRRset does not implement the removeRRsig() method");
    }
    //@}
private:
    BasicRRsetImpl* impl_;
};

/// \brief The \c RRset class is a concrete derived class of
/// \c BasicRRset which contains a pointer to an additional RRset
/// containing associated RRSIG records.  This allows DNSSEC aware
/// applications to treat data associated with a particular
/// QNAME/QTYPE/QCLASS as a single object.
class RRset : public BasicRRset {
public:
    RRset(const Name& name, const RRClass& rrclass,
          const RRType& rrtype, const RRTTL& ttl);

    virtual ~RRset();

    /// \brief Get the wire format length of the \c RRset.
    ///
    /// \return The length of the wire format representation of the
    /// \c RRset.
    /// \throw EmptyRRset if the \c RRset is empty.
    virtual uint16_t getLength() const;

    /// \brief Render the RRset in the wire format with name compression and
    /// truncation handling.
    ///
    /// See \c AbstractRRset::toWire(MessageRenderer&)const.
    virtual unsigned int toWire(AbstractMessageRenderer& renderer) const;

    /// \brief Render the RRset in the wire format without any compression.
    ///
    /// See \c AbstractRRset::toWire(OutputBuffer&)const.
    virtual unsigned int toWire(isc::util::OutputBuffer& buffer) const;

    /// \brief Updates the owner name of the \c RRset, including RRSIGs if any
    virtual void setTTL(const RRTTL& ttl) {
        BasicRRset::setTTL(ttl);
        if (rrsig_) {
            rrsig_->setTTL(ttl);
        }
    }

    /// \brief Adds an RRSIG RR to this RRset's signatures
    virtual void addRRsig(const rdata::ConstRdataPtr& rdata) {
        if (!rrsig_) {
            rrsig_ = RRsetPtr(new RRset(getName(), getClass(),
                                        RRType::RRSIG(), getTTL()));
        }
        rrsig_->addRdata(rdata);
    }

    // Workaround for older versions of boost: some don't support implicit
    // conversion from shared_ptr<X> to shared_ptr<const X>.  Note: we should
    // revisit the interface of managing RRset signatures, at which point this
    // problem may go away.
    virtual void addRRsig(const rdata::RdataPtr& rdata) {
        // Don't try to convert as a reference here.  SunStudio will reject it.
        addRRsig(static_cast<const rdata::ConstRdataPtr>(rdata));
    }

    /// \brief Adds an RRSIG RRset to this RRset
    virtual void addRRsig(const AbstractRRset& sigs) {
        RdataIteratorPtr it = sigs.getRdataIterator();

        if (!rrsig_) {
            rrsig_ = RRsetPtr(new RRset(getName(), getClass(),
                                        RRType::RRSIG(), getTTL()));
        }

        for (it->first(); !it->isLast(); it->next()) {
            rrsig_->addRdata(it->getCurrent());
        }
    }

    virtual void addRRsig(const ConstRRsetPtr& sigs) { addRRsig(*sigs); }

    // Another workaround for older boost (see above)
    virtual void addRRsig(const RRsetPtr& sigs) { addRRsig(*sigs); }

    /// \brief Clear the RRSIGs for this RRset
    virtual void removeRRsig() { rrsig_ = RRsetPtr(); }

    /// \brief Return a pointer to this RRset's RRSIG RRset
    virtual RRsetPtr getRRsig() const { return (rrsig_); }

    /// \brief Returns the number of \c RRSIG records associated with
    /// the \c RRset.
    ///
    /// Note that an \c RRset with no RRSIG records may exist, so this
    /// method may return 0.
    ///
    /// \return The number of \c RRSIG records associated.
    virtual unsigned int getRRsigDataCount() const;

private:
    RRsetPtr rrsig_;
};


/// \brief Insert the \c RRset as a string into stream.
///
/// This method convert the \c rrset into a string and inserts it into the
/// output stream \c os.
///
/// This function overloads the global \c operator<< to behave as described in
/// \c %ostream::%operator<< but applied to RRset objects.
///
/// \param os A \c std::ostream object on which the insertion operation is
/// performed.
/// \param rrset A reference to a (derived class of) \c AbstractRRset object
/// output by the operation.
/// \return A reference to the same \c std::ostream object referenced by
/// parameter \c os after the insertion operation.
std::ostream& operator<<(std::ostream& os, const AbstractRRset& rrset);
} // end of namespace dns
} // end of namespace isc
#endif  // RRSET_H

// Local Variables: 
// mode: c++
// End: 
