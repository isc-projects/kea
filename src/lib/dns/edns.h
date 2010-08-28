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

#ifndef __EDNS_H
#define __EDNS_H 1

#include <stdint.h>

#include <boost/shared_ptr.hpp>

#include <ostream>

#include <dns/rdata.h>

namespace isc {
namespace dns {

class EDNS;
class Name;
class MessageRenderer;
class RRClass;
class RRTTL;
class RRType;
class Rcode;

/// \brief A pointer-like type pointing to an \c EDNS object.
typedef boost::shared_ptr<EDNS> EDNSPtr;

/// \brief A pointer-like type pointing to an immutable \c EDNS object.
typedef boost::shared_ptr<const EDNS> ConstEDNSPtr;

/// Document why this is separated from \c Message.
///
/// Stores normalized information: unknown flags will be ignored on
/// construction.
///
/// Decision: separate the knowledge about the relationship with rcode and
/// the wire format.  EDNS is only responsible for the 8-bit part of the
/// 12-bit extended RCODE.
///
/// note: extended Rcode is handled in the Message class.  We may want to
/// generalize this by passing the whole Message and letting the \c EDNS
/// object modify or refer to it based on the EDNS protocol.  But it would
/// couple the \c Message and \c EDNS more tightly.  Right now, the decision
/// is to consider \c Rcode is a special case; if a future version of the EDNS
/// protocol introduces further relationship between the message and the EDNS,
/// we might reconsider the interface, probably with higher abstraction.
///
/// MEMO: performance consideration: toWire() can be optimized by caching
/// the rendered image and reuse EDNS
///
/// This version of this class is copyable, but we may want to change it
/// once we support EDNS options.
/// (Note to ourselves: the python binding assumes this class is copyable).
///
/// TBD: how to manage options is an open issue.
class EDNS {
public:
    ///
    /// \name Constructors and Destructor
    ///
    /// We use the default copy constructor, default copy assignment operator,
    /// and default destructors intentionally.
    ///
    //@{
    /// Constructor with the EDNS version.
    /// An application would use this constructor to specify EDNS parameters
    /// and/or options for outgoing DNS messages.
    ///
    /// All other parameters than the version number will be initialized to
    /// reasonable defaults.
    /// Specifically, the UDP buffer size is set to
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
    /// In this initial implementation does not support EDNS options at all,
    /// and \c rdata is simply ignored.  Future versions will support
    /// options, and may throw exceptions while validating the given parameter.
    ///
    /// Note: since no other type than OPT for \c rrtype is allowed, this
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
    /// \param rrttl The TTL of the OPT RR.
    /// \param rdata The RDATA of the OPT RR.
    EDNS(const Name& name, const RRClass& rrclass, const RRType& rrtype,
         const RRTTL& ttl, const rdata::Rdata& rdata);
    //@}

    ///
    /// \name Getter and Setter Methods
    ///
    //@{
    /// \brief Returns the version of EDNS.
    uint8_t getVersion() const { return (version_); }

    /// \brief Return the maximum buffer size of UDP messages for the sender
    /// of the message.
    uint16_t getUDPSize() const { return (udp_size_); }

    /// \brief Specify the maximum buffer size of UDP messages that use
    /// this EDNS.
    ///
    /// Unless explicitly specified, \c DEFAULT_MAX_UDPSIZE will be assumed
    /// for the maximum buffer size, regardless of whether EDNS OPT RR is
    /// included or not.  This means if an application wants to send a message
    /// with an EDNS OPT RR for specifying a larger UDP size, it must
    /// explicitly specify the value using this method.
    void setUDPSize(const uint16_t udp_size) { udp_size_ = udp_size; }

    /// \brief Return whether the message sender indicates DNSSEC is supported.
    ///
    /// \return true if the 
    bool isDNSSECSupported() const { return (dnssec_ok_); }

    /// \brief Specify whether DNSSEC is supported in the message.
    void setDNSSECSupported(const bool on) { dnssec_ok_ = on; }
    //@}

    ///
    /// \name Converter Methods
    ///
    //@{
    /// \brief
    ///
    /// In the current implementation the return value is either 0 or 1, but
    /// the return type is <code>unsigned int</code> to be consistent with
    /// RRset::toWire().  In any case the caller shouldn't assume these are
    /// only possible return values from this method.
    unsigned int toWire(MessageRenderer& renderer,
                        const uint8_t extended_rcode) const;
    unsigned int toWire(OutputBuffer& buffer,
                        const uint8_t extended_rcode) const;

    /// \brief Convert the EDNS to a string.
    std::string toText() const;
    //@}

    // TBD: This method is currently not implemented.  We'll eventually need
    // something like this.
    //void addOption();

private:
    /// Helper method to define unified implementation for the public versions
    /// of toWire().
    template <typename Output>
    int toWire(Output& output, const uint8_t extended_rcode) const;

public:
    /// \brief The highest EDNS version this implementation supports.
    static const uint8_t SUPPORTED_VERSION = 0;
private:
    // We may want to use pimpl, especially when we support EDNS options.
    const uint8_t version_;
    uint16_t udp_size_;
    bool dnssec_ok_;
};

/// \brief Create a new EDNS object from a set of RR parameters, also providing
/// the extended RCODE value.
///
/// Document why this function isn't a constructor.
/// Document why this function does two things: create an EDNS and adjust
/// Rcode.
///
/// This function provides the strong exception guarantee: Unless an
/// exception is thrown \c extended_code won't be modified.
EDNS* createEDNSFromRR(const Name& name, const RRClass& rrclass,
                       const RRType& rrtype, const RRTTL& ttl,
                       const rdata::Rdata& rdata, uint8_t& extended_rcode);

/// \brief
std::ostream& operator<<(std::ostream& os, const EDNS& edns);
}
}
#endif  // __EDNS_H

// Local Variables: 
// mode: c++
// End: 
