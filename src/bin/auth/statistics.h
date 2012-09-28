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

#include <dns/opcode.h>
#include <dns/rcode.h>
#include <cc/session.h>
#include <cc/data.h>

#include <stdint.h>
#include <boost/scoped_ptr.hpp>

class AuthCountersImpl;

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
/// to \c AuthCountersImpl directly.
friend class AuthCountersImpl;
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
    inline QRAttributes();
    /// The destructor.
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
    /// \brief Set if the answer has sent.
    /// \throw None
    inline void answerWasSent();
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
QRAttributes::answerWasSent() {
    answer_sent_ = true;
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

} // namespace statistics
} // namespace auth
} // namespace isc

/// \brief Set of query counters.
///
/// \c AuthCounters is set of query counters class. It holds query counters
/// and provides an interface to increment the counter of specified type
/// (e.g. UDP query, TCP query).
///
/// This class also provides a function to send statistics information to
/// statistics module.
///
/// This class is designed to be a part of \c AuthSrv.
/// Call \c inc() to increment a counter for specific type of query in
/// the query processing function. use \c enum \c CounterType to specify
/// the type of query.
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
/// \todo Consider overhead of \c AuthCounters::inc()
class AuthCounters {
private:
    boost::scoped_ptr<AuthCountersImpl> impl_;
public:
    // Enum for the type of counter
    enum ServerCounterType {
        SERVER_UDP_QUERY,       ///< SERVER_UDP_QUERY: counter for UDP queries
        SERVER_TCP_QUERY,       ///< SERVER_TCP_QUERY: counter for TCP queries
        SERVER_COUNTER_TYPES    ///< The number of defined counters
    };
    enum PerZoneCounterType {
        ZONE_UDP_QUERY,         ///< ZONE_UDP_QUERY: counter for UDP queries
        ZONE_TCP_QUERY,         ///< ZONE_TCP_QUERY: counter for TCP queries
        PER_ZONE_COUNTER_TYPES  ///< The number of defined counters
    };
    /// The constructor.
    ///
    /// This constructor is mostly exception free. But it may still throw
    /// a standard exception if memory allocation fails inside the method.
    ///
    AuthCounters();
    /// The destructor.
    ///
    /// This method never throws an exception.
    ///
    ~AuthCounters();

    /// \brief Increment the counter specified by the parameter.
    ///
    /// \param type Type of a counter to increment.
    ///
    /// \throw std::out_of_range \a type is unknown.
    ///
    /// usage: counter.inc(AuthCounters::SERVER_UDP_QUERY);
    /// 
    void inc(const ServerCounterType type);

    /// \brief Increment the counter of a per opcode counter.
    ///
    /// \note This is a tentative interface.  See \c getCounter().
    ///
    /// \param opcode The opcode of the counter to increment.
    ///
    /// \throw None
    void inc(const isc::dns::Opcode opcode);

    /// \brief Increment the counter of a per rcode counter.
    ///
    /// \note This is a tentative interface.  See \c getCounter().
    ///
    /// \param rcode The rcode of the counter to increment.
    ///
    /// \throw None
    void inc(const isc::dns::Rcode rcode);

    /// \brief Answers statistics counters to statistics module.
    ///
    /// This method is mostly exception free (error conditions are
    /// represented via the return value). But it may still throw
    /// a standard exception if memory allocation fails inside the method.
    ///
    /// \return statistics data
    ///
    isc::data::ConstElementPtr getStatistics() const;

    /// \brief Get the value of a counter in the AuthCounters.
    ///
    /// This function returns a value of the counter specified by \a type.
    /// This method never throws an exception.
    ///
    /// Note: Currently this function is for testing purpose only.
    ///
    /// \param type Type of a counter to get the value of
    ///
    /// \return the value of the counter specified by \a type.
    uint64_t getCounter(const AuthCounters::ServerCounterType type) const;

    /// \brief Get the value of a per opcode counter.
    ///
    /// This method returns the value of the per opcode counter for the
    /// specified \c opcode.
    ///
    /// \note This is a tentative interface as an attempt of experimentally
    /// supporting more statistics counters.  This should eventually be more
    /// generalized.  In any case, this method is mainly for testing.
    ///
    /// \throw None
    /// \param opcode The opcode of the counter to get the value of
    /// \return the value of the counter.
    uint64_t getCounter(const isc::dns::Opcode opcode) const;

    /// \brief Get the value of a per rcode counter.
    ///
    /// This method returns the value of the per rcode counter for the
    /// specified \c rcode.
    ///
    /// \note As mentioned in getCounter(const isc::dns::Opcode opcode),
    /// This is a tentative interface as an attempt of experimentally
    /// supporting more statistics counters.  This should eventually be more
    /// generalized.  In any case, this method is mainly for testing.
    ///
    /// \throw None
    /// \param rcode The rcode of the counter to get the value of
    /// \return the value of the counter.
    uint64_t getCounter(const isc::dns::Rcode rcode) const;

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
    /// function for AuthCounters.
    ///
    /// This method never throws an exception.
    ///
    /// \param validator A function type of the validation of
    /// statistics specification.
    ///
    void registerStatisticsValidator(AuthCounters::validator_type validator) const;
};

#endif // __STATISTICS_H

// Local Variables:
// mode: c++
// End:
