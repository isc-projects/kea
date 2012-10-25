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

#include <string>

#include <stdint.h>
#include <boost/scoped_ptr.hpp>

namespace isc {
namespace auth {
namespace statistics {

class CountersImpl;

class QRAttributes {
/// \brief Query/Response attributes for statistics.
///
/// This class holds some attributes related to a query/response
/// for statistics data collection.
///
/// This class does not have getter methods since it exposes private members
/// to \c CountersImpl directly.
friend class CountersImpl;
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
    /// The constructor.
    ///
    /// This constructor is mostly exception free. But it may still throw
    /// a standard exception if memory allocation fails inside the method.
    ///
    QRAttributes() :
    req_ip_version_(0), req_transport_protocol_(0),
    req_opcode_(0),
    req_is_edns_0_(false), req_is_edns_badver_(false),
    req_is_dnssec_ok_(false),
    req_is_tsig_(false), req_is_sig0_(false), req_is_badsig_(false),
    zone_origin_(),
    answer_sent_(false),
    res_is_truncated_(false)
    {};

    /// The destructor.
    ///
    /// This method never throws an exception.
    ///
    ~QRAttributes() {};
    /// \brief Set query opcode.
    /// \throw None
    void setQueryOpCode(const int opcode) {
        req_opcode_ = opcode;
    };
    /// \brief Set IP version carrying a query.
    /// \throw None
    void setQueryIPVersion(const int ip_version) {
        req_ip_version_ = ip_version;
    };
    /// \brief Set transport protocol carrying a query.
    /// \throw None
    void setQueryTransportProtocol(const int transport_protocol) {
        req_transport_protocol_ = transport_protocol;
    };
    /// \brief Set query EDNS attributes.
    /// \throw None
    void setQueryEDNS(const bool is_edns_0, const bool is_edns_badver) {
        req_is_edns_0_ = is_edns_0;
        req_is_edns_badver_ = is_edns_badver;
    };
    /// \brief Set query DO bit.
    /// \throw None
    void setQueryDO(const bool is_dnssec_ok) {
        req_is_dnssec_ok_ = is_dnssec_ok;
    };
    /// \brief Set query TSIG attributes.
    /// \throw None
    void setQuerySig(const bool is_tsig, const bool is_sig0,
                            const bool is_badsig)
    {
        req_is_tsig_ = is_tsig;
        req_is_sig0_ = is_sig0;
        req_is_badsig_ = is_badsig;
    };
    /// \brief Set zone origin.
    /// \throw None
    void setOrigin(const std::string& origin) {
        zone_origin_ = origin;
    };
    /// \brief Set if the answer was sent.
    /// \throw None
    void answerWasSent() {
        answer_sent_ = true;
    };
    /// \brief Set if the response is truncated.
    /// \throw None
    void setResponseTruncated(const bool is_truncated) {
        res_is_truncated_ = is_truncated;
    };
    /// \brief Reset attributes.
    /// \throw None
    void reset() {
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
    };
};

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
class Counters {
private:
    boost::scoped_ptr<CountersImpl> impl_;
public:
    /// The constructor.
    ///
    /// This constructor is mostly exception free. But it may still throw
    /// a standard exception if memory allocation fails inside the method.
    ///
    Counters();
    /// The destructor.
    ///
    /// This method never throws an exception.
    ///
    ~Counters();

    /// \brief Increment counters according to the parameters.
    ///
    /// \param qrattrs Query/Response attributes.
    /// \param response DNS response message.
    ///
    /// \throw None
    ///
    void inc(const QRAttributes& qrattrs, const isc::dns::Message& response);

    /// \brief Answers statistics counters to statistics module.
    ///
    /// This method is mostly exception free (error conditions are
    /// represented via the return value). But it may still throw
    /// a standard exception if memory allocation fails inside the method.
    ///
    /// \return statistics data
    ///
    isc::data::ConstElementPtr getStatistics() const;

    /// \brief A type of validation function for the specification in
    /// isc::config::ModuleSpec.
    ///
    /// This type might be useful for not only statistics
    /// specificatoin but also for config_data specification and for
    /// commnad.
    ///
    typedef boost::function<bool(const isc::data::ConstElementPtr&)>
    validator_type;

    /// \brief Register a function type of the statistics validation
    /// function for Counters.
    ///
    /// This method never throws an exception.
    ///
    /// \param validator A function type of the validation of
    /// statistics specification.
    ///
    void registerStatisticsValidator(Counters::validator_type validator) const;
};

} // namespace statistics
} // namespace auth
} // namespace isc

#endif // __STATISTICS_H

// Local Variables:
// mode: c++
// End:
