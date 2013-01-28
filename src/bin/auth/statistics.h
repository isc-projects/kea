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
#include <boost/optional.hpp>

#include <bitset>

#include <stdint.h>

namespace isc {
namespace auth {
namespace statistics {

/// \brief DNS Message attributes for statistics.
///
/// This class holds some attributes related to a DNS message
/// for statistics data collection.
class MessageAttributes {
public:
    /// \brief IP version of DNS message.
    enum IPVersionType {
        IP_VERSION_UNSPEC,          // (initial value; internal use only)
        IP_VERSION_IPV4,            ///< IPv4 message
        IP_VERSION_IPV6             ///< IPv6 message
    };

    /// \brief Transport protocol of DNS message.
    enum TransportProtocolType {
        TRANSPORT_UNSPEC,           // (initial value; internal use only)
        TRANSPORT_UDP,              ///< UDP message
        TRANSPORT_TCP               ///< TCP message
    };
private:
    // request attributes
    IPVersionType req_ip_version_;                  // IP version
    TransportProtocolType req_transport_protocol_;  // Transport layer protocol
    boost::optional<isc::dns::Opcode> req_opcode_;  // OpCode
    enum BitAttributes {
        REQ_WITH_EDNS_0,            // request with EDNS ver.0
        REQ_WITH_DNSSEC_OK,         // DNSSEC OK (DO) bit is set in request
        REQ_TSIG_SIGNED,            // request is signed with valid TSIG
        REQ_BADSIG,                 // request is signed but bad signature
        RES_IS_TRUNCATED,           // response is truncated
        RES_TSIG_SIGNED,            // response is signed with TSIG
        BIT_ATTRIBUTES_TYPES
    };
    std::bitset<BIT_ATTRIBUTES_TYPES> bit_attributes_;
public:
    /// \brief The constructor.
    ///
    /// \throw None
    MessageAttributes() :
        req_ip_version_(IP_VERSION_UNSPEC),
        req_transport_protocol_(TRANSPORT_UNSPEC)
    {}

    /// \brief Return opcode of the request.
    /// \return opcode of the request
    /// \throw isc::InvalidOperation Opcode is not set
    const isc::dns::Opcode& getRequestOpCode() const {
        if (req_opcode_) {
            return (req_opcode_.get());
        } else {
            isc_throw(isc::InvalidOperation, "Opcode is not set");
        }
    }

    /// \brief Set opcode of the request.
    /// \param opcode Opcode of the request
    /// \throw None
    void setRequestOpCode(const isc::dns::Opcode& opcode) {
        req_opcode_ = opcode;
    }

    /// \brief Return IP version carrying the request.
    /// \return IP version carrying the request
    /// \throw None
    IPVersionType getRequestIPVersion() const {
        return (req_ip_version_);
    }

    /// \brief Set IP version carrying the request.
    /// \param ip_version IP version carrying the request
    /// \throw isc::InvalidParameter ip_version is invalid
    void setRequestIPVersion(const IPVersionType ip_version) {
        if (ip_version == IP_VERSION_UNSPEC) {
            isc_throw(isc::InvalidParameter, "Invalid IP version");
        }
        req_ip_version_ = ip_version;
    }

    /// \brief Return transport protocol carrying the request.
    /// \return Transport protocol carrying the request
    /// \throw None
    TransportProtocolType getRequestTransportProtocol() const {
        return (req_transport_protocol_);
    }

    /// \brief Set transport protocol carrying the request.
    /// \param transport_protocol Transport protocol carrying the request
    /// \throw isc::InvalidParameter transport_protocol is invalid
    void setRequestTransportProtocol(
        const TransportProtocolType transport_protocol)
    {
        if (transport_protocol == TRANSPORT_UNSPEC) {
            isc_throw(isc::InvalidParameter, "Invalid transport protocol");
        }
        req_transport_protocol_ = transport_protocol;
    }

    /// \brief Return whether EDNS version of the request is 0 or not.
    /// \return true if EDNS version of the request is 0
    /// \throw None
    bool getRequestEDNS0() const {
        return (bit_attributes_[REQ_WITH_EDNS_0]);
    }

    /// \brief Set whether EDNS version of the request is 0 or not.
    /// \param with_edns_0 true if EDNS version of the request is 0
    /// \throw None
    void setRequestEDNS0(const bool with_edns_0) {
        bit_attributes_[REQ_WITH_EDNS_0] = with_edns_0;
    }

    /// \brief Return DNSSEC OK (DO) bit of the request.
    /// \return true if DNSSEC OK (DO) bit of the request is set
    /// \throw None
    bool getRequestDO() const {
        return (bit_attributes_[REQ_WITH_DNSSEC_OK]);
    }

    /// \brief Set DNSSEC OK (DO) bit of the request.
    /// \param with_dnssec_ok true if DNSSEC OK (DO) bit of the request is set
    /// \throw None
    void setRequestDO(const bool with_dnssec_ok) {
        bit_attributes_[REQ_WITH_DNSSEC_OK] = with_dnssec_ok;
    }

    /// \brief Return whether the request is TSIG signed or not.
    /// \return true if the request is TSIG signed
    /// \throw None
    bool getRequestSigTSIG() const {
        return (bit_attributes_[REQ_TSIG_SIGNED]);
    }

    /// \brief Return whether the signature of the request is bad or not.
    /// \return true if the signature of the request is bad
    /// \throw None
    bool getRequestSigBadSig() const {
        return (bit_attributes_[REQ_BADSIG]);
    }

    /// \brief Set TSIG attributes of the request.
    /// \param signed_tsig true if the request is signed with TSIG
    /// \param badsig true if the signature of the request is bad
    /// \throw None
    void setRequestTSIG(const bool signed_tsig, const bool badsig) {
        assert(!(!signed_tsig && badsig));
        bit_attributes_[REQ_TSIG_SIGNED] = signed_tsig;
        bit_attributes_[REQ_BADSIG] = badsig;
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

    /// \brief Return whether the response is TSIG signed or not.
    /// \return true if the response is signed with TSIG
    /// \throw None
    bool getResponseTSIG() const {
        return (bit_attributes_[RES_TSIG_SIGNED]);
    }

    /// \brief Set whether the response is TSIG signed or not.
    /// \param signed_tsig true if the response is signed with TSIG
    /// \throw None
    void setResponseTSIG(const bool signed_tsig) {
        bit_attributes_[RES_TSIG_SIGNED] = signed_tsig;
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
