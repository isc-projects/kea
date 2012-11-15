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

#include <cc/session.h>
#include <cc/data.h>

#include <dns/message.h>

#include <statistics/counter.h>
#include <statistics/counter_dict.h>

#include <boost/noncopyable.hpp>

#include <string>

#include <stdint.h>

namespace isc {
namespace auth {
namespace statistics {

class QRAttributes {
/// \brief Query/Response attributes for statistics.
///
/// This class holds some attributes related to a query/response
/// for statistics data collection.
///
/// This class does not have getter methods since it exposes private members
/// to \c Counters directly.
friend class Counters;
private:
    // request attributes
    int req_ip_version_;            // IP version
    int req_transport_protocol_;    // Transport layer protocol
    int req_opcode_;                // OpCode
    bool req_is_edns_0_;            // EDNS ver.0
    bool req_is_edns_badver_;       // other EDNS version
    bool req_is_dnssec_ok_;         // DO bit
    bool req_is_tsig_;              // signed with valid TSIG
    bool req_is_sig0_;              // signed with valid SIG(0)
    bool req_is_badsig_;            // signed but bad signature
    // zone origin
    std::string zone_origin_;       // zone origin
    // response attributes
    bool answer_sent_;              // DNS message has sent
    bool res_is_truncated_;         // DNS message is truncated
public:
    /// \brief The constructor.
    ///
    /// This constructor is mostly exception free. But it may still throw
    /// a standard exception if memory allocation fails inside the method.
    ///
    inline QRAttributes();

    /// \brief The destructor.
    ///
    /// This method never throws an exception.
    ///
    inline ~QRAttributes();

    /// \brief Set query opcode.
    /// \throw None
    inline void setQueryOpCode(const int opcode);

    /// \brief Set IP version carrying a query.
    /// \throw None
    inline void setQueryIPVersion(const int ip_version);

    /// \brief Set transport protocol carrying a query.
    /// \throw None
    inline void setQueryTransportProtocol(const int transport_protocol);

    /// \brief Set query EDNS attributes.
    /// \throw None
    inline void setQueryEDNS(const bool is_edns_0, const bool is_edns_badver);

    /// \brief Set query DO bit.
    /// \throw None
    inline void setQueryDO(const bool is_dnssec_ok);

    /// \brief Set query TSIG attributes.
    /// \throw None
    inline void setQuerySig(const bool is_tsig, const bool is_sig0,
                            const bool is_badsig);

    /// \brief Set zone origin.
    /// \throw None
    inline void setOrigin(const std::string& origin);

    /// \brief Set if the response is truncated.
    /// \throw None
    inline void setResponseTruncated(const bool is_truncated);

    /// \brief Reset attributes.
    /// \throw None
    inline void reset();
};

inline QRAttributes::QRAttributes() :
    req_ip_version_(0), req_transport_protocol_(0),
    req_opcode_(0),
    req_is_edns_0_(false), req_is_edns_badver_(false),
    req_is_dnssec_ok_(false),
    req_is_tsig_(false), req_is_sig0_(false), req_is_badsig_(false),
    zone_origin_(),
    answer_sent_(false),
    res_is_truncated_(false)
{}

inline QRAttributes::~QRAttributes()
{}

inline void
QRAttributes::setQueryIPVersion(const int ip_version) {
    req_ip_version_ = ip_version;
}

inline void
QRAttributes::setQueryTransportProtocol(const int transport_protocol) {
    req_transport_protocol_ = transport_protocol;
}

inline void
QRAttributes::setQueryOpCode(const int opcode) {
    req_opcode_ = opcode;
}

inline void
QRAttributes::setQueryEDNS(const bool is_edns_0, const bool is_edns_badver) {
    req_is_edns_0_ = is_edns_0;
    req_is_edns_badver_ = is_edns_badver;
}

inline void
QRAttributes::setQueryDO(const bool is_dnssec_ok) {
    req_is_dnssec_ok_ = is_dnssec_ok;
}

inline void
QRAttributes::setQuerySig(const bool is_tsig, const bool is_sig0,
                          const bool is_badsig)
{
    req_is_tsig_ = is_tsig;
    req_is_sig0_ = is_sig0;
    req_is_badsig_ = is_badsig;
}

inline void
QRAttributes::setResponseTruncated(const bool is_truncated) {
    res_is_truncated_ = is_truncated;
}

inline void
QRAttributes::reset() {
    req_ip_version_ = 0;
    req_transport_protocol_ = 0;
    req_opcode_ = 0;
    req_is_edns_0_ = false;
    req_is_edns_badver_ = false;
    req_is_dnssec_ok_ = false;
    req_is_tsig_ = false;
    req_is_sig0_ = false;
    req_is_badsig_ = false;
    zone_origin_.clear();
    answer_sent_ = false;
    res_is_truncated_ = false;
}

/// \brief Set of query counters.
///
/// \c Counters is set of query counters class. It holds query counters
/// and provides an interface to increment the counter of specified type
/// (e.g. UDP query, TCP query).
///
/// This class also provides a function to send statistics information to
/// statistics module.
///
/// This class is designed to be a part of \c AuthSrv.
/// Call \c inc() to increment a counter for the query.
/// Call \c getStatistics() to answer statistics information to statistics
/// module with statistics_session, when the command \c getstats is received.
///
/// We may eventually want to change the structure to hold values that are
/// not counters (such as concurrent TCP connections), or seperate generic
/// part to src/lib to share with the other modules.
///
/// This class uses pimpl idiom and hides detailed implementation.
/// This class is constructed on startup of the server, so
/// construction overhead of this approach should be acceptable.
///
/// \todo Hold counters for each query types (Notify, Axfr, Ixfr, Normal)
/// \todo Consider overhead of \c Counters::inc()
class Counters : boost::noncopyable {
private:
    // counter for query/response
    isc::statistics::Counter server_qr_counter_;
    // set of counters for zones
    isc::statistics::CounterDictionary zone_qr_counters_;
    void incRequest(const QRAttributes& qrattrs);
    void incResponse(const QRAttributes& qrattrs,
                     const isc::dns::Message& response);
public:
    /// \brief A type of statistics item tree in isc::data::MapElement.
    ///        {
    ///          zone_name => {
    ///                         item_name => item_value,
    ///                         item_name => item_value, ...
    ///                       },
    ///          ...
    ///        }
    ///        item_name is a string seperated by '.'.
    ///        item_value is an integer.
    ///
    typedef isc::data::ElementPtr ItemTreeType;

    /// \brief The constructor.
    ///
    /// This constructor is mostly exception free. But it may still throw
    /// a standard exception if memory allocation fails inside the method.
    ///
    Counters();

    /// \brief The destructor.
    ///
    /// This method never throws an exception.
    ///
    ~Counters();

    /// \brief Increment counters according to the parameters.
    ///
    /// This constructor is mostly exception free. But it may still throw
    /// a standard exception if memory allocation fails inside the method.
    ///
    /// \param qrattrs Query/Response attributes.
    /// \param response DNS response message.
    /// \param done DNS response was sent to the client.
    ///
    /// \throw std::bad_alloc Internal resource allocation fails
    ///
    void inc(const QRAttributes& qrattrs, const isc::dns::Message& response,
             const bool done);

    /// \brief Get statistics counters.
    ///
    /// This method is mostly exception free. But it may still throw
    /// a standard exception if memory allocation fails inside the method.
    ///
    /// \return statistics data
    ///
    /// \throw std::bad_alloc Internal resource allocation fails
    ///
    ItemTreeType get() const;
};

} // namespace statistics
} // namespace auth
} // namespace isc

#endif // __STATISTICS_H

// Local Variables:
// mode: c++
// End:
