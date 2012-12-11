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

#ifndef __STATISTICS_H
#define __STATISTICS_H 1

#include <cc/data.h>

#include <dns/message.h>
#include <dns/opcode.h>

#include <statistics/counter.h>

#include <boost/noncopyable.hpp>

#include <bitset>

#include <stdint.h>

namespace isc {
namespace auth {
namespace statistics {

using isc::dns::Opcode;

/// \brief DNS Message attributes for statistics.
///
/// This class holds some attributes related to a DNS message
/// for statistics data collection.
class MessageAttributes {
public:
    /// \brief IP version of DNS message.
    enum IPVersion {
        IP_VERSION_UNSPEC,          // (initial value; internal use only)
        IP_VERSION_IPV4,            ///< IPv4 message
        IP_VERSION_IPV6             ///< IPv6 message
    };

    /// \brief Transport protocol of DNS message.
    enum TransportProtocol {
        TRANSPORT_UNSPEC,           // (initial value; internal use only)
        TRANSPORT_UDP,              ///< UDP message
        TRANSPORT_TCP               ///< TCP message
    };
private:
    // request attributes
    IPVersion req_ip_version_;                 // IP version
    TransportProtocol req_transport_protocol_; // Transport layer protocol
    Opcode req_opcode_;                        // OpCode
    enum BitAttributes {
        REQ_IS_EDNS_0,              // EDNS ver.0
        REQ_IS_DNSSEC_OK,           // DNSSEC OK (DO) bit is set
        REQ_IS_TSIG,                // signed with valid TSIG
        REQ_IS_BADSIG,              // signed but bad signature
        RES_IS_TRUNCATED,           // DNS message is truncated
        BIT_ATTRIBUTES_TYPES
    };
    std::bitset<BIT_ATTRIBUTES_TYPES> bit_attributes_;
public:
    /// \brief The constructor.
    ///
    /// \throw None
    MessageAttributes() : req_ip_version_(IP_VERSION_UNSPEC),
                          req_transport_protocol_(TRANSPORT_UNSPEC),
                          req_opcode_(Opcode::RESERVED15_CODE),
                          bit_attributes_()
    {}

    /// \brief Return request opcode.
    /// \return opcode of the request
    /// \throw None
    const Opcode& getRequestOpCode() const {
        return (req_opcode_);
    }

    /// \brief Set request opcode.
    /// \param opcode Opcode of the request
    /// \throw None
    void setRequestOpCode(const Opcode& opcode) {
        req_opcode_ = opcode;
    }

    /// \brief Return IP version carrying the request.
    /// \return IP version carrying the request
    /// \throw None
    IPVersion getRequestIPVersion() const {
        return (req_ip_version_);
    }

    /// \brief Set IP version carrying the request.
    /// \param ip_version IP version carrying the request
    /// \throw None
    void setRequestIPVersion(const IPVersion ip_version) {
        assert(ip_version != IP_VERSION_UNSPEC);
        req_ip_version_ = ip_version;
    }

    /// \brief Return transport protocol carrying the request.
    /// \return Transport protocol carrying the request
    /// \throw None
    TransportProtocol getRequestTransportProtocol() const {
        return (req_transport_protocol_);
    }

    /// \brief Set transport protocol carrying the request.
    /// \param transport_protocol Transport protocol carrying the request
    /// \throw None
    void setRequestTransportProtocol(
        const TransportProtocol transport_protocol)
    {
        assert(transport_protocol != TRANSPORT_UNSPEC);
        req_transport_protocol_ = transport_protocol;
    }

    /// \brief Return EDNS attribute of the request.
    /// \return true if EDNS version of the request is 0
    /// \throw None
    bool getRequestEDNS0() const {
        return (bit_attributes_[REQ_IS_EDNS_0]);
    }

    /// \brief Set EDNS attribute of the request.
    /// \param is_edns_0 true if EDNS version of the request is 0
    /// \throw None
    void setRequestEDNS0(const bool is_edns_0) {
        bit_attributes_[REQ_IS_EDNS_0] = is_edns_0;
    }

    /// \brief Return DNSSEC OK (DO) bit of the request.
    /// \return true if DNSSEC OK (DO) bit of the request is set
    /// \throw None
    bool getRequestDO() const {
        return (bit_attributes_[REQ_IS_DNSSEC_OK]);
    }

    /// \brief Set DNSSEC OK (DO) bit of the request.
    /// \param is_dnssec_ok true if DNSSEC OK (DO) bit of the request is set
    /// \throw None
    void setRequestDO(const bool is_dnssec_ok) {
        bit_attributes_[REQ_IS_DNSSEC_OK] = is_dnssec_ok;
    }

    /// \brief Return TSIG attribute of the request.
    /// \return true if the request is TSIG signed
    /// \throw None
    bool getRequestSigTSIG() const {
        return (bit_attributes_[REQ_IS_TSIG]);
    }

    /// \brief Return the status of the signature of the request.
    /// \return true if the signature of the request is bad
    /// \throw None
    bool getRequestSigBadSig() const {
        return (bit_attributes_[REQ_IS_BADSIG]);
    }

    /// \brief Set TSIG attributes of the request.
    /// \param is_tsig true if the request is TSIG signed
    /// \param is_badsig true if the signature of the request is bad
    /// \throw None
    void setRequestSig(const bool is_tsig, const bool is_badsig) {
        assert(!(!is_tsig && is_badsig));
        bit_attributes_[REQ_IS_TSIG] = is_tsig;
        bit_attributes_[REQ_IS_BADSIG] = is_badsig;
    }

    /// \brief Return TC (truncated) bit of the response.
    /// \return true if the response is truncated
    /// \throw None
    bool getResponseTruncated() const {
        return (bit_attributes_[RES_IS_TRUNCATED]);
    }

    /// \brief Set TC (truncated) bit of the response.
    /// \param is_truncated true if the response is truncated
    /// \throw None
    void setResponseTruncated(const bool is_truncated) {
        bit_attributes_[RES_IS_TRUNCATED] = is_truncated;
    }
};

/// \brief Set of DNS message counters.
///
/// \c Counters is a set of DNS message counters class. It holds DNS message
/// counters and provides an interface to increment the counter of specified
/// type (e.g. UDP message, TCP message).
///
/// This class is designed to be a part of \c AuthSrv.
/// Call \c inc() to increment a counter for the message.
/// Call \c get() to get a set of DNS message counters.
///
/// We may eventually want to change the structure to hold values that are
/// not counters (such as concurrent TCP connections), or seperate generic
/// part to src/lib to share with the other modules.
///
/// This class is constructed on startup of the server, so
/// construction overhead of this approach should be acceptable.
///
/// \todo Consider overhead of \c Counters::inc()
class Counters : boost::noncopyable {
private:
    // counter for DNS message attributes
    isc::statistics::Counter server_msg_counter_;

    void incRequest(const MessageAttributes& msgattrs);
    void incResponse(const MessageAttributes& msgattrs,
                     const isc::dns::Message& response);
public:
    /// \brief A type of statistics item tree in isc::data::MapElement.
    /// \verbatim
    ///        {
    ///          zone_name => {
    ///                         item_name => item_value,
    ///                         item_name => item_value, ...
    ///                       },
    ///          ...
    ///        }
    ///        item_name is a string seperated by '.'.
    ///        item_value is an integer.
    /// \endverbatim
    ///
    typedef isc::data::ConstElementPtr ConstItemTreePtr;

    /// \brief The constructor.
    ///
    /// This constructor is mostly exception free. But it may still throw
    /// a standard exception if memory allocation fails inside the method.
    ///
    Counters();

    /// \brief Increment counters according to the parameters.
    ///
    /// This method is mostly exception free. But it may still throw a
    /// standard exception if memory allocation fails inside the method.
    ///
    /// \param msgattrs DNS message attributes.
    /// \param response DNS response message.
    /// \param done DNS response was sent to the client.
    ///
    /// \throw std::bad_alloc Internal resource allocation fails
    ///
    void inc(const MessageAttributes& msgattrs,
             const isc::dns::Message& response, const bool done);

    /// \brief Get statistics counters.
    ///
    /// This method is mostly exception free. But it may still throw a
    /// standard exception if memory allocation fails inside the method.
    ///
    /// \return statistics data
    ///
    /// \throw std::bad_alloc Internal resource allocation fails
    ///
    ConstItemTreePtr get() const;
};

} // namespace statistics
} // namespace auth
} // namespace isc

#endif // __STATISTICS_H

// Local Variables:
// mode: c++
// End:
