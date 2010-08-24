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
/// couple the \c Message and \c EDNS more tightly.  Right now, our decision
/// is to consider \c Rcode is a special case; if a future version of the EDNS
/// protocol introduces further relationship between the message and the EDNS,
/// we might reconsider the interface, probably with higher abstraction.
///
/// MEMO: performance consideration: toWire() can be optimized by caching
/// the rendered image and reuse EDNS
///
///TBD: how to manage options is an open issue.
class EDNS {
public:
    explicit EDNS(const uint8_t version = SUPPORTED_VERSION);

    EDNS(const Name& name, const RRClass& rrclass, const RRType& rrtype,
         const RRTTL& ttl, const rdata::Rdata& rdata);

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
    /// \return TBD
    bool isDNSSECSupported() const { return (dnssec_ok_); }

    /// \brief Specify whether DNSSEC is supported in the message.
    void setDNSSECSupported(const bool on) { dnssec_ok_ = on; }

    // In the current implementation the return value is either 0 or 1, but
    // the return type is <code>unsigned int</code> to be consistent with
    // RRset::toWire().  In any case the caller shouldn't assume these are
    // only possible return values from this method.
    unsigned int toWire(MessageRenderer& renderer,
                        const uint8_t extended_rcode) const;
    unsigned int toWire(OutputBuffer& buffer,
                        const uint8_t extended_rcode) const;

    /// TBD
    std::string toText() const;

    // TBD: currently not implemented.
    void addOption();

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
                       const rdata::Rdata& rdata,
                       uint8_t& extended_rcode);

/// Should we define this?
std::ostream& operator<<(std::ostream& os, const EDNS& edns);
}
}
#endif  // __EDNS_H

// Local Variables: 
// mode: c++
// End: 
