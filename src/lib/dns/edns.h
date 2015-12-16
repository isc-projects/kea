// Copyright (C) 2010-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef EDNS_H
#define EDNS_H 1

#include <stdint.h>

#include <boost/shared_ptr.hpp>

#include <ostream>

#include <dns/rdata.h>

namespace isc {
namespace util {
class OutputBuffer;
}

namespace dns {

class EDNS;
class Name;
class AbstractMessageRenderer;
class RRClass;
class RRTTL;
class RRType;
class Rcode;

/// \brief A pointer-like type pointing to an \c EDNS object.
typedef boost::shared_ptr<EDNS> EDNSPtr;

/// \brief A pointer-like type pointing to an immutable \c EDNS object.
typedef boost::shared_ptr<const EDNS> ConstEDNSPtr;

/// The \c EDNS class represents the %EDNS OPT RR defined in RFC2671.
///
/// This class encapsulates various optional features of %EDNS such as
/// the UDP payload size or the DNSSEC DO bit, and provides interfaces
/// to manage these features.  It is also responsible for conversion
/// to and from wire-format OPT RR.
/// One important exception is about the extended RCODE:
/// The \c EDNS class is only responsible for extracting the 8-bit part
/// of the 12-bit extended RCODE from the OPT RR's TTL field of an
/// incoming message, and for setting the 8-bit part into the OPT RR TTL
/// of an outgoing message.  It's not supposed to know how to construct the
/// complete RCODE, much less maintain the RCODE in it.
/// It is the caller's responsibility (typically the \c Message class).
///
/// When converting wire-format OPT RR into an \c EDNS object, it normalizes
/// the information, i.e., unknown flags will be ignored on construction.
///
/// This class is also supposed to support %EDNS options such as NSID,
/// but the initial implementation does not include it.  This is a near term
/// TODO item.
///
/// <b>Notes to developers</b>
///
/// The rest of the description is for developers who need to or want to
/// understand the design of this API.
///
/// Representing %EDNS is tricky.  An OPT RR is no different from other RRs
/// in terms of the wire format syntax, and in that sense we could use the
/// generic \c RRset class to represent an OPT RR (BIND 9 adopts this
/// approach).  But the resulting interface would be inconvenient for
/// developers.  For example, the developer would need to know that the
/// UDP size is encoded in the RR Class field.  It's better to provide
/// a more abstract interface along with the special semantics of OPT RR.
///
/// Another approach would be to realize each optional feature of EDNS
/// as an attribute of the DNS message.
/// NLnet Labs' ldns takes this approach.
/// This way an operation for specifying the UDP size would be written
/// like this:
/// \code message->setUDPSize(4096); \endcode
/// which should be more intuitive.
/// A drawback of this approach is that OPT RR is itself optional and the
/// separate parameters may not necessarily indicate whether to include an
/// OPT RR per se.
/// For example, consider what should be done with this code:
/// \code message->setUDPSize(512); \endcode
/// Since the payload size of 512 is the default, it may mean the OPT RR
/// should be skipped.  But it might also mean the caller intentionally
/// (for some reason) wants to insert an OPT RR specifying the default UDP
/// size explicitly.
///
/// So, we use a separate class that encapsulates the EDNS semantics and
/// knows the mapping between the semantics and the wire format representation.
/// This way the interface can be semantics-based and is intuitive:
/// \code edns->setUDPSize(4096); \endcode
/// while we can explicitly specify whether to include an OPT RR by setting
/// (or not setting) an \c EDNS object in a message:
/// \code message->setEDNS(edns); // unless we do this OPT RR is skipped
/// \endcode
///
/// There is still a non trivial point: How to manage extended RCODEs.
/// An OPT RR encodes the upper 8 bits of extended 12-bit RCODE.
/// In general, it would be better to provide a unified interface to get
/// access to RCODEs whether or not they are traditional 4 bit codes or
/// extended ones that have non 0 upper bits.
/// However, since an OPT RR may not appear in a message the RCODE cannot be
/// maintained in the \c EDNS class.
/// But it would not be desirable to maintain the extended RCODEs completely
/// in the \c Message class, either, because we wanted to hide the mapping
/// between %EDNS semantics and its wire format representation within the
///  \c EDNS class; if we moved the responsibility about RCODEs to the
/// \c Message class, it would have to parse and render the upper 8 bits of
/// the RCODEs, dealing with wire representation of OPT RR.
/// This is suboptimal in the sense of encapsulation.
///
/// As a compromise, our decision is to separate the knowledge about the
/// relationship with RCODE from the knowledge about the wire format as
/// noted in the beginning of this description.
///
/// This decoupling is based on the observation that the extended RCODE
/// is a very special case where %EDNS only has partial information.
/// If a future version of the %EDNS protocol introduces further relationship
/// between the message and the %EDNS, we might reconsider the interface,
/// probably with higher abstraction.
class EDNS {
public:
    ///
    /// \name Constructors and Destructor
    ///
    /// We use the default copy constructor, default copy assignment operator,
    /// and default destructors intentionally.
    ///
    /// Note about copyability: This version of this class is copyable,
    /// but we may want to change it once we support EDNS options, when
    /// we want to revise this class using the pimpl idiom.
    /// But we should be careful about that: the python binding currently
    /// assumes this class is copyable.
    //@{
    /// Constructor with the EDNS version.
    /// An application would use this constructor to specify EDNS parameters
    /// and/or options for outgoing DNS messages.
    ///
    /// All other parameters than the version number will be initialized to
    /// reasonable defaults.
    /// Specifically, the UDP payload size is set to
    /// \c Message::DEFAULT_MAX_UDPSIZE, and DNSSEC is assumed to be not
    /// supported.
    /// These parameters can be altered via setter methods of this class.
    /// Note, however, that the version number cannot be changed once
    /// constructed.
    ///
    /// The version number parameter can be omitted, in which case the highest
    /// supported version in this implementation will be assumed.
    /// When specified, if it is larger than the highest supported version,
    /// an exception of class \c isc::InvalidParameter will be thrown.
    ///
    /// This constructor throws no other exception.
    ///
    /// \param version The version number of the EDNS to be constructed.
    explicit EDNS(const uint8_t version = SUPPORTED_VERSION);

    /// \brief Constructor from resource record (RR) parameters.
    ///
    /// This constructor is intended to be used to construct an EDNS object
    /// from an OPT RR contained in an incoming DNS message.
    ///
    /// Unlike many other constructors for this purpose, this constructor
    /// does not take the bare wire-format %data in the form of an
    /// \c InputBuffer object.  This is because parsing incoming EDNS is
    /// highly context dependent and it's not feasible to handle it in a
    /// completely polymorphic way.  For example, a DNS message parser would
    /// have to check an OPT RR appears at most once in the message, and if
    /// it appears it should be in the additional section.  So, the parser
    /// needs to have an explicit check to see if an RR is of type OPT, and
    /// then (if other conditions are met) construct a corresponding \c EDNS
    /// object.  At that point the parser would have already converted the
    /// wire %data into corresponding objects of \c Name, \c RRClass,
    /// \c RRType, etc, and it makes more sense to pass them directly to the
    /// constructor.
    ///
    /// In practice, top level applications rarely need to use this
    /// constructor directly.  It should normally suffice to have a higher
    /// level class such as \c Message do that job.
    ///
    /// This constructor checks the passed parameters to see if they are
    /// valid in terms of the EDNS protocol specification.
    /// \c name must be the root name ("."); otherwise, an exception of
    /// class \c DNSMessageFORMERR will be thrown.
    /// \c rrtype must specify the OPT RR type; otherwise, an exception of
    /// class \c isc::InvalidParameter will be thrown.
    /// The ENDS version number is extracted from \c rrttl.  If it is larger
    /// than the higher supported version, an exception of class
    /// \c DNSMessageBADVERS will be thrown.  Note that this is different from
    /// the case of the same error in the other constructor.
    /// This is intentional, so that the application can transparently convert
    /// the exception to a response RCODE according to the protocol
    /// specification.
    ///
    /// This initial implementation does not support EDNS options at all,
    /// and \c rdata is simply ignored.  Future versions will support
    /// options, and may throw exceptions while validating the given parameter.
    ///
    /// \b Note: since no other type than OPT for \c rrtype is allowed, this
    /// parameter could actually have been omitted.  But it is intentionally
    /// included as a parameter so that invalid usage of the construction
    /// can be detected.  As noted above the caller should normally have
    /// the corresponding \c RRType object at the time of call to this
    /// constructor, so the overhead of having the additional parameter
    /// should be marginal.
    ///
    /// \param name The owner name of the OPT RR.  This must be the root name.
    /// \param rrclass The RR class of the OPT RR.
    /// \param rrtype This must specify the OPT RR type.
    /// \param ttl The TTL of the OPT RR.
    /// \param rdata The RDATA of the OPT RR.
    EDNS(const Name& name, const RRClass& rrclass, const RRType& rrtype,
         const RRTTL& ttl, const rdata::Rdata& rdata);
    //@}

    ///
    /// \name Getter and Setter Methods
    ///
    //@{
    /// \brief Returns the version of EDNS.
    ///
    /// This method never throws an exception.
    uint8_t getVersion() const { return (version_); }

    /// \brief Returns the maximum payload size of UDP messages for the sender
    /// of the message containing this \c EDNS.
    ///
    /// This method never throws an exception.
    uint16_t getUDPSize() const { return (udp_size_); }

    /// \brief Specify the maximum payload size of UDP messages that use
    /// this EDNS.
    ///
    /// Unless explicitly specified, \c DEFAULT_MAX_UDPSIZE will be assumed
    /// for the maximum payload size, regardless of whether EDNS OPT RR is
    /// included or not.  This means if an application wants to send a message
    /// with an EDNS OPT RR for specifying a larger UDP size, it must
    /// explicitly specify the value using this method.
    ///
    /// This method never throws an exception.
    ///
    /// \param udp_size The maximum payload size of UDP messages for the sender
    /// of the message containing this \c EDNS.
    void setUDPSize(const uint16_t udp_size) { udp_size_ = udp_size; }

    /// \brief Returns whether the message sender is DNSSEC aware.
    ///
    /// This method never throws an exception.
    ///
    /// \return true if DNSSEC is supported; otherwise false.
    bool getDNSSECAwareness() const { return (dnssec_aware_); }

    /// \brief Specifies whether the sender of the message containing this
    /// \c EDNS is DNSSEC aware.
    ///
    /// If the parameter is true, a subsequent call to \c toWire() will
    /// set the DNSSEC DO bit on for the corresponding OPT RR.
    ///
    /// This method never throws an exception.
    ///
    /// \param is_aware \c true if DNSSEC is supported; \c false otherwise.
    void setDNSSECAwareness(const bool is_aware) { dnssec_aware_ = is_aware; }
    //@}

    ///
    /// \name Converter Methods
    ///
    //@{
    /// \brief Render the \c EDNS in the wire format.
    ///
    /// This method renders the \c EDNS object as a form of DNS OPT RR
    /// via \c renderer, which encapsulates output buffer and other rendering
    /// contexts.
    /// Since the \c EDNS object does not maintain the extended RCODE
    /// information, a separate parameter \c extended_rcode must be passed to
    /// this method.
    ///
    /// If by adding the OPT RR the message size would exceed the limit
    /// maintained in \c renderer, this method skips rendering the RR
    /// and returns 0; otherwise it returns 1, which is the number of RR
    /// rendered.
    ///
    /// In the current implementation the return value is either 0 or 1, but
    /// the return type is <code>unsigned int</code> to be consistent with
    /// \c RRset::toWire().  In any case the caller shouldn't assume these are
    /// only possible return values from this method.
    ///
    /// This method is mostly exception free, but it requires memory
    /// allocation and if it fails a corresponding standard exception will be
    /// thrown.
    ///
    /// In practice, top level applications rarely need to use this
    /// method directly.  It should normally suffice to have a higher
    /// level class such as \c Message do that job.
    ///
    /// <b>Note to developer:</b> the current implementation constructs an
    /// \c RRset object for the OPT RR and calls its \c toWire() method,
    /// which is inefficient.  In future, we may want to optimize this method
    /// by caching the rendered image and having the application reuse the
    /// same \c EDNS object when possible.
    ///
    /// \param renderer DNS message rendering context that encapsulates the
    /// output buffer and name compression information.
    /// \param extended_rcode Upper 8 bits of extended RCODE to be rendered as
    /// part of the EDNS OPT RR.
    /// \return 1 if the OPT RR fits in the message size limit; otherwise 0.
    unsigned int toWire(AbstractMessageRenderer& renderer,
                        const uint8_t extended_rcode) const;

    /// \brief Render the \c EDNS in the wire format.
    ///
    /// This method is same as \c toWire(MessageRenderer&,uint8_t)const
    /// except it renders the OPT RR in an \c OutputBuffer and therefore
    /// does not care about message size limit.
    /// As a consequence it always returns 1.
    unsigned int toWire(isc::util::OutputBuffer& buffer,
                        const uint8_t extended_rcode) const;

    /// \brief Convert the EDNS to a string.
    ///
    /// The format of the resulting string is as follows:
    /// \code ; EDNS: version: <version>, flags: <edns flags>; udp: <udp size>
    /// \endcode
    /// where
    ///  - \em version is the EDNS version number (integer).
    ///  - <em>edns flags</em> is a sequence of EDNS flag bits.  The only
    ///    possible flag is the "DNSSEC OK", which is represented as "do".
    ///  - <em>udp size</em> is sender's UDP payload size in bytes.
    ///
    /// The string will be terminated with a trailing newline character.
    ///
    /// When EDNS options are supported the output of this method will be
    /// extended.
    ///
    /// This method is mostly exception free, but it may require memory
    /// allocation and if it fails a corresponding standard exception will be
    /// thrown.
    ///
    /// \return A string representation of \c EDNS.  See above for the format.
    std::string toText() const;
    //@}

    // TBD: This method is currently not implemented.  We'll eventually need
    // something like this.
    //void addOption();

public:
    /// \brief The highest EDNS version this implementation supports.
    static const uint8_t SUPPORTED_VERSION = 0;
private:
    // We may eventually want to migrate to pimpl, especially when we support
    // EDNS options.  In this initial implementation, we keep it simple.
    const uint8_t version_;
    uint16_t udp_size_;
    bool dnssec_aware_;
};

/// \brief Create a new \c EDNS object from a set of RR parameters, also
/// providing the extended RCODE value.
///
/// This function is similar to the EDNS class constructor
/// \c EDNS::EDNS(const Name&, const RRClass&, const RRType&, const RRTTL&, const rdata::Rdata&)
/// but is different in that
/// - It dynamically creates a new object
/// - It returns (via a reference argument) the topmost 8 bits of the extended
/// RCODE encoded in the \c ttl.
///
/// On success, \c extended_rcode will be updated with the 8-bit part of
/// the extended RCODE encoded in the TTL of the OPT RR.
///
/// The intended usage of this function is to parse an OPT RR of an incoming
/// DNS message, while updating the RCODE of the message.
/// One common usage pattern is as follows:
///
/// \code Message msg;
/// ...
/// uint8_t extended_rcode;
/// ConstEDNSPtr edns = ConstEDNSPtr(createEDNSFromRR(..., extended_rcode));
/// rcode = Rcode(msg.getRcode().getCode(), extended_rcode);
/// \endcode
/// (although, like the \c EDNS constructor, normal applications wouldn't have
/// to use this function directly).
///
/// This function provides the strong exception guarantee: Unless an
/// exception is thrown \c extended_code won't be modified.
///
/// This function validates the given parameters and throws exceptions on
/// failure in the same way as the \c EDNS class constructor.
/// In addition, if memory allocation for the new object fails it throws the
/// corresponding standard exception.
///
/// Note that this function returns a bare pointer to the newly allocated
/// object, not a shared pointer object enclosing the pointer.
/// The caller is responsible for deleting the object after the use of it
/// (typically, the caller would immediately encapsulate the returned pointer
/// in a shared pointer object, \c EDNSPtr or \c ConstEDNSPtr).
/// It returns a bare pointer so that it can be used where the use of a shared
/// pointer is impossible or not desirable.
///
/// Note to developers: there is no strong technical reason why this function
/// cannot be a constructor of the \c EDNS class or even integrated into the
/// constructor.  But we decided to make it a separate free function so that
/// constructors will be free from side effects (which is in itself a matter
/// of preference).
///
/// \param name The owner name of the OPT RR.  This must be the root name.
/// \param rrclass The RR class of the OPT RR.
/// \param rrtype This must specify the OPT RR type.
/// \param ttl The TTL of the OPT RR.
/// \param rdata The RDATA of the OPT RR.
/// \param extended_rcode A placeholder to store the topmost 8 bits of the
/// extended Rcode.
/// \return A pointer to the created \c EDNS object.
EDNS* createEDNSFromRR(const Name& name, const RRClass& rrclass,
                       const RRType& rrtype, const RRTTL& ttl,
                       const rdata::Rdata& rdata, uint8_t& extended_rcode);

/// \brief Insert the \c EDNS as a string into stream.
///
/// This method convert \c edns into a string and inserts it into the
/// output stream \c os.
///
/// \param os A \c std::ostream object on which the insertion operation is
/// performed.
/// \param edns A reference to an \c EDNS object output by the operation.
/// \return A reference to the same \c std::ostream object referenced by
/// parameter \c os after the insertion operation.
std::ostream& operator<<(std::ostream& os, const EDNS& edns);
}
}
#endif  // EDNS_H

// Local Variables: 
// mode: c++
// End: 
