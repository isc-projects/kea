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
}

namespace datasrc {
class ZoneTable;
}

namespace auth {

/// The \c Query class represents a standard DNS query that encapsulates
/// processing logic to answer the query.
///
/// Many of the design details for this class are still in flux.
/// We'll revisit and update them as we add more functionality, for example:
/// - zone_table parameter of the constructor.  This will eventually be
///   replaced with a generic DataSrc object, or perhaps a notion of "view".
/// - as a related point, we may have to pass the RR class of the query.
///   in the initial implementation the RR class is an attribute of zone
///   table and omitted.  It's not clear if this assumption holds with
///   generic data sources.  On the other hand, it will help keep
///   implementation simpler, and we might rather want to modify the design
///   of the data source on this point.
/// - return value of process().  rather than setting the Rcode, we might use
///   it as a return value of \c process().
/// - we'll have to be able to specify whether DNSSEC is requested.
///   It's an open question whether it should be in the constructor or via a
///   separate attribute setter.
/// - likewise, we'll eventually need to do per zone access control, for which
///   we need querier's information such as its IP address.
/// - zone_table (or DataSrc eventually) and response may better be parameters
///   to process() instead of the constructor.
class Query {
public:
    /// Constructor from query parameters.
    ///
    /// This constructor never throws an exception.
    ///
    /// \param zone_table The zone table wherein the answer to the query is
    /// to be found.
    /// \param qname The query name
    /// \param qtype The RR type of the query
    /// \param response The response message to store the answer to the query.
    Query(const isc::datasrc::ZoneTable& zone_table,
          const isc::dns::Name& qname, const isc::dns::RRType& qtype,
          isc::dns::Message& response) :
        zone_table_(zone_table), qname_(qname), qtype_(qtype),
        response_(response)
    {}

    /// Process the query.
    ///
    /// This method first identifies the zone that best matches the query
    /// name (and in some cases RR type when the search is dependent on the
    /// type) and then searches the zone that best matches the query name.
    /// It then updates the response message accordingly; for example, a
    /// successful search would result in adding a corresponding RRset to
    /// the answer section of the response.
    ///
    /// If no matching zone is found in the zone table, the \c Rcode of
    /// SERVFAIL will be set in the response.
    ///
    /// Right now this method never throws an exception, but it may in a
    /// future version.
    void process() const;
private:
    const isc::datasrc::ZoneTable& zone_table_;
    const isc::dns::Name& qname_;
    const isc::dns::RRType& qtype_;
    isc::dns::Message& response_;
};

}
}

// Local Variables:
// mode: c++
// End:
