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

namespace isc {
namespace dns {
class Message;
class Name;
class RRType;
class RRset;
}

namespace datasrc {
class MemoryDataSrc;
class Zone;
}

namespace auth {

/// The \c Query class represents a standard DNS query that encapsulates
/// processing logic to answer the query.
///
/// Many of the design details for this class are still in flux.
/// We'll revisit and update them as we add more functionality, for example:
/// - memory_datasrc parameter of the constructor.  It is a data source that
///   uses in memory dedicated backend.
/// - as a related point, we may have to pass the RR class of the query.
///   in the initial implementation the RR class is an attribute of memory
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
/// - memory_datasrc and response may better be parameters to process() instead
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
public:
    /// Constructor from query parameters.
    ///
    /// This constructor never throws an exception.
    ///
    /// \param memory_datasrc The memory datasource wherein the answer to the query is
    /// to be found.
    /// \param qname The query name
    /// \param qtype The RR type of the query
    /// \param response The response message to store the answer to the query.
    Query(const isc::datasrc::MemoryDataSrc& memory_datasrc,
          const isc::dns::Name& qname, const isc::dns::RRType& qtype,
          isc::dns::Message& response) :
        memory_datasrc_(memory_datasrc), qname_(qname), qtype_(qtype),
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
    /// If no matching zone is found in the memory datasource, the RCODE of
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
    /// Right now this method never throws an exception, but it may in a
    /// future version.
    void process() const;

private:
    /// Look up additional data (i.e., address records for the names included
    /// in NS or MX records).
    ///
    /// This method may throw a exception because its underlying methods may
    /// throw exceptions.
    ///
    /// \param zone The Zone wherein the additional data to the query is bo be
    /// found.
    /// \param rrset The RRset (i.e., NS or MX rrset) which require additional
    /// processing.
    void getAdditional(const isc::datasrc::Zone& zone,
                       const isc::dns::RRset& rrset) const;

    /// Find address records for a specified name.
    ///
    /// Search the specified zone for AAAA/A RRs of each of the NS/MX RDATA
    /// (domain name), and insert the found ones into the additional section
    /// if address records are available.
    ///
    /// Note: we need to perform the search in the "GLUE OK" mode for NS RDATA,
    /// which means that we should include A/AAAA RRs under a zone cut.
    /// The glue records must exactly match the name in the NS RDATA, without
    /// CNAME or wildcard processing.
    ///
    /// \param zone The Zone wherein the address records is to be found.
    /// \param qname The name in rrset RDATA.
    void findAddrs(const isc::datasrc::Zone& zone,
                   const isc::dns::Name& qname) const;

    const isc::datasrc::MemoryDataSrc& memory_datasrc_;
    const isc::dns::Name& qname_;
    const isc::dns::RRType& qtype_;
    isc::dns::Message& response_;
};

}
}

// Local Variables:
// mode: c++
// End:
