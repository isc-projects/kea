/*
 * Copyright (C) 2010  Internet Systems Consortium, Inc. ("ISC")
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES WITH
 * REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS.  IN NO EVENT SHALL ISC BE LIABLE FOR ANY SPECIAL, DIRECT,
 * INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
 * LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
 * OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 */

#include <exceptions/exceptions.h>
#include <datasrc/zone.h>

namespace isc {
namespace dns {
class Message;
class Name;
class RRType;
class RRset;
}

namespace datasrc {
class DataSourceClient;
}

namespace auth {

/// The \c Query class represents a standard DNS query that encapsulates
/// processing logic to answer the query.
///
/// Many of the design details for this class are still in flux.
/// We'll revisit and update them as we add more functionality, for example:
/// - as a related point, we may have to pass the RR class of the query.
///   in the initial implementation the RR class is an attribute of
///   datasource and omitted.  It's not clear if this assumption holds with
///   generic data sources.  On the other hand, it will help keep
///   implementation simpler, and we might rather want to modify the design
///   of the data source on this point.
/// - return value of process().  rather than or in addition to setting the
///   Rcode, we might use it as a return value of \c process().
/// - we'll have to be able to specify whether DNSSEC is requested.
///   It's an open question whether it should be in the constructor or via a
///   separate attribute setter.
/// - likewise, we'll eventually need to do per zone access control, for which
///   we need querier's information such as its IP address.
/// - datasrc_client and response may better be parameters to process() instead
///   of the constructor.
///
/// <b>Note:</b> The class name is intentionally the same as the one used in
/// the datasrc library.  This is because the plan is to eventually merge
/// the two classes.  We could give it a different name such as "AuthQuery"
/// to avoid possible ambiguity, but it may sound redundant in that it's
/// obvious that this class is for authoritative queries.
/// Since the interfaces are very different for now and it's less
/// likely to misuse one of the classes instead of the other
/// accidentally, and since it's considered a temporary development state,
/// we keep this name at the moment.
class Query {
private:

    /// \brief Adds a SOA.
    ///
    /// Adds a SOA of the zone into the authority zone of response_.
    /// Can throw NoSOA.
    ///
    void putSOA(isc::datasrc::ZoneFinder& zone) const;

    /// \brief Look up additional data (i.e., address records for the names
    /// included in NS or MX records).
    ///
    /// Note: Any additional data which has already been provided in the
    /// answer section (i.e., if the original query happend to be for the
    /// address of the DNS server), it should be omitted from the additional.
    ///
    /// This method may throw a exception because its underlying methods may
    /// throw exceptions.
    ///
    /// \param zone The ZoneFinder through which the additional data for the
    /// query is to be found.
    /// \param rrset The RRset (i.e., NS or MX rrset) which require additional
    /// processing.
    void getAdditional(isc::datasrc::ZoneFinder& zone,
                       const isc::dns::RRset& rrset) const;

    /// \brief Find address records for a specified name.
    ///
    /// Search the specified zone for AAAA/A RRs of each of the NS/MX RDATA
    /// (domain name), and insert the found ones into the additional section
    /// if address records are available. By default the search will stop
    /// once it encounters a zone cut.
    ///
    /// Note: we need to perform the search in the "GLUE OK" mode for NS RDATA,
    /// which means that we should include A/AAAA RRs under a zone cut.
    /// The glue records must exactly match the name in the NS RDATA, without
    /// CNAME or wildcard processing.
    ///
    /// \param zone The \c ZoneFinder through which the address records is to
    /// be found.
    /// \param qname The name in rrset RDATA.
    /// \param options The search options.
    void findAddrs(isc::datasrc::ZoneFinder& zone,
                   const isc::dns::Name& qname,
                   const isc::datasrc::ZoneFinder::FindOptions options
                   = isc::datasrc::ZoneFinder::FIND_DEFAULT) const;

    /// \brief Look up a zone's NS RRset and their address records for an
    /// authoritative answer.
    ///
    /// On returning an authoritative answer, insert a zone's NS into the
    /// authority section and AAAA/A RRs of each of the NS RDATA into the
    /// additional section.
    ///
    /// <b>Notes to developer:</b>
    ///
    /// We should omit address records which has already been provided in the
    /// answer section from the additional.
    ///
    /// For now, in order to optimize the additional section processing, we
    /// include AAAA/A RRs under a zone cut in additional section. (BIND 9
    /// excludes under-cut RRs; NSD include them.)
    ///
    /// \param zone The \c ZoneFinder through which the NS and additional data
    /// for the query are to be found.
    void getAuthAdditional(isc::datasrc::ZoneFinder& zone) const;

public:
    /// Constructor from query parameters.
    ///
    /// This constructor never throws an exception.
    ///
    /// \param datasrc_client The datasource wherein the answer to the query is
    /// to be found.
    /// \param qname The query name
    /// \param qtype The RR type of the query
    /// \param response The response message to store the answer to the query.
    Query(const isc::datasrc::DataSourceClient& datasrc_client,
          const isc::dns::Name& qname, const isc::dns::RRType& qtype,
          isc::dns::Message& response) :
        datasrc_client_(datasrc_client), qname_(qname), qtype_(qtype),
        response_(response)
    {}

    /// Process the query.
    ///
    /// This method first identifies the zone that best matches the query
    /// name (and in some cases RR type when the search is dependent on the
    /// type) and then searches the zone for an entry that best matches the
    /// query name.
    /// It then updates the response message accordingly; for example, a
    /// successful search would result in adding a corresponding RRset to
    /// the answer section of the response.
    ///
    /// If no matching zone is found in the datasource, the RCODE of
    /// SERVFAIL will be set in the response.
    /// <b>Note:</b> this is different from the error code that BIND 9 returns
    /// by default when it's configured as an authoritative-only server (and
    /// from the behavior of the BIND 10 datasrc library, which was implemented
    /// to be compatible with BIND 9).
    /// The difference comes from the fact that BIND 9 returns REFUSED as a
    /// result of access control check on the use of its cache.
    /// Since BIND 10's authoritative server doesn't have the notion of cache
    /// by design, it doesn't make sense to return REFUSED.  On the other hand,
    /// providing compatible behavior may have its own benefit, so this point
    /// should be revisited later.
    ///
    /// This might throw BadZone or any of its specific subclasses, but that
    /// shouldn't happen in real-life (as BadZone means wrong data, it should
    /// have been rejected upon loading).
    void process() const;

    /// \short Bad zone data encountered.
    ///
    /// This is thrown when process encounteres misconfigured zone in a way
    /// it can't continue. This throws, not sets the Rcode, because such
    /// misconfigured zone should not be present in the data source and
    /// should have been rejected sooner.
    struct BadZone : public isc::Exception {
        BadZone(const char* file, size_t line, const char* what) :
            Exception(file, line, what)
        {}
    };

    /// \short Zone is missing its SOA record.
    ///
    /// We tried to add a SOA into the authoritative section, but the zone
    /// does not contain one.
    struct NoSOA : public BadZone {
        NoSOA(const char* file, size_t line, const char* what) :
            BadZone(file, line, what)
        {}
    };

    /// \short Zone is missing its apex NS records.
    ///
    /// We tried to add apex NS records into the authority section, but the
    /// zone does not contain any.
    struct NoApexNS: public BadZone {
        NoApexNS(const char* file, size_t line, const char* what) :
            BadZone(file, line, what)
        {}
    };

private:
    const isc::datasrc::DataSourceClient& datasrc_client_;
    const isc::dns::Name& qname_;
    const isc::dns::RRType& qtype_;
    isc::dns::Message& response_;
};

}
}

// Local Variables:
// mode: c++
// End:
