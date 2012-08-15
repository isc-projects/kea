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
#include <dns/rrset.h>
#include <datasrc/zone.h>

#include <boost/noncopyable.hpp>

#include <functional>
#include <vector>

namespace isc {
namespace dns {
class Message;
class Name;
class RRType;
class RRset;
}

namespace datasrc {
class ClientList;
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
class Query : boost::noncopyable {
private:
    /// \brief Initial reserved size for the vectors in Query
    ///
    /// The value is larger than we expect the vectors to even become, and
    /// has been chosen arbitrarily. The reason to set them quite high is
    /// to prevent reallocation on addition.
    static const size_t RESERVE_RRSETS = 64;

    /// \brief Adds a SOA.
    ///
    /// Adds a SOA of the zone into the authority zone of response_.
    /// Can throw NoSOA.
    ///
    void addSOA(isc::datasrc::ZoneFinder& finder);

    /// \brief Adds the DS rrset for the given name, if available
    ///
    /// This is intended to be called when returning a delegation, and
    /// if DNSSEC data is requested. If the DS record is not found
    /// (signaled by find() returning NXRRSET), and the zone is signed
    /// with NSEC, an NSEC denial of existence proof is added.
    ///
    /// \exception BadDS raised if find() returns anything other than
    ///                  SUCCESS or NXRRSET when searching for the DS
    ///                  record.
    /// \param finder The ZoneFinder where the delegation was found
    /// \param ds_name The name of the delegation RRset
    void addDS(isc::datasrc::ZoneFinder& finder,
               const isc::dns::Name& ds_name);

    /// \brief Adds NSEC(3) denial proof for the given NXRRset result
    ///
    /// If available, NSEC or NSEC3 records are added to the authority
    /// section (depending on whether isNSECSigned() or isNSEC3Signed()
    /// returns true).
    ///
    /// \param finder The ZoneFinder that was used to search for the missing
    ///               data
    /// \param db_result The ZoneFinder::FindResult returned by find()
    void addNXRRsetProof(isc::datasrc::ZoneFinder& finder,
                         const isc::datasrc::ZoneFinder::Context& db_context);

    /// Add NSEC RRs that prove an NXDOMAIN result.
    ///
    /// This corresponds to Section 3.1.3.2 of RFC 4035.
    void addNXDOMAINProofByNSEC(isc::datasrc::ZoneFinder& finder,
                                isc::dns::ConstRRsetPtr nsec);

    /// Add NSEC3 RRs that prove an NXDOMAIN result.
    ///
    /// This corresponds to Section 7.2.2 of RFC 5155.
    void addNXDOMAINProofByNSEC3(isc::datasrc::ZoneFinder& finder);

    /// Add NSEC or NSEC3 RRs that prove a wildcard answer is the best one.
    ///
    /// This corresponds to Section 3.1.3.3 of RFC 4035 and Section 7.2.6
    /// of RFC5155.
    void addWildcardProof(
        isc::datasrc::ZoneFinder& finder,
        const isc::datasrc::ZoneFinder::Context& db_context);

    /// \brief Adds one NSEC RR proved no matched QNAME,one NSEC RR proved no
    /// matched <QNAME,QTYPE> through wildcard extension.
    ///
    /// Add NSEC RRs that prove an WILDCARD_NXRRSET result.
    /// This corresponds to Section 3.1.3.4 of RFC 4035.
    /// \param finder The ZoneFinder through which the authority data for the
    /// query is to be found.
    /// \param nsec The RRset (NSEC RR) which proved that there is no matched 
    /// <QNAME,QTTYPE>.
    void addWildcardNXRRSETProof(isc::datasrc::ZoneFinder& finder,
                                 isc::dns::ConstRRsetPtr nsec);

    /// \brief Look up a zone's NS RRset and their address records for an
    /// authoritative answer, and add them to the additional section.
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
    /// \param finder The \c ZoneFinder through which the NS and additional
    /// data for the query are to be found.
    void addAuthAdditional(isc::datasrc::ZoneFinder& finder,
                           std::vector<isc::dns::ConstRRsetPtr>& additionals);

    /// \brief Process a DS query possible at the child side of zone cut.
    ///
    /// This private method is a subroutine of process(), and is called if
    /// there's a possibility that this server has authority for the child
    /// side of the DS's owner name (and it's detected that the server at
    /// least doesn't have authority at the parent side).  This method
    /// first checks if it has authority for the child, and if does,
    /// just build a "no data" response with SOA for the zone origin
    /// (possibly with a proof for the no data) as specified in Section
    /// 2.2.1.1 of RFC3658.
    ///
    /// It returns true if this server has authority of the child; otherwise
    /// it returns false.  In the former case, the caller is expected to
    /// terminate the query processing, because it should have been completed
    /// within this method.
    bool processDSAtChild();

    /// \brief Add NSEC3 to the response for a closest encloser proof for a
    /// given name.
    ///
    /// This method calls \c findNSEC3() of the given zone finder for the
    /// given name in the recursive mode, and adds the returned NSEC3(s) to
    /// the authority section of the response message associated with the
    /// \c Query object.
    ///
    /// It returns the number of labels of the closest encloser (returned via
    /// the \c findNSEC3() call) in case the caller needs to use that value
    /// for subsequent processing, i.e, constructing the best possible wildcard
    /// name that (would) match the query name.
    ///
    /// Unless \c exact_ok is true, \c name is expected to be non existent,
    /// in which case findNSEC3() in the recursive mode must return both
    /// closest and next proofs.  If the latter is NULL, it means a run time
    /// collision (or the zone is broken in other way), and this method throws
    /// a BadNSEC3 exception.
    ///
    /// If \c exact_ok is true, this method takes into account the case
    /// where the name exists and may or may not be at a zone cut to an
    /// optout zone.  In this case, depending on whether the zone is optout
    /// or not, findNSEC3() may return non-NULL or NULL next_proof
    /// (respectively).  This method adds the next proof if and only if
    /// findNSEC3() returns non NULL value for it.  The Opt-Out flag
    /// must be set or cleared accordingly, but this method doesn't check that
    /// in this level (as long as the zone is signed validly and findNSEC3()
    /// for the data source is implemented as documented, the condition
    /// should be met; otherwise we'd let the validator detect the error).
    ///
    /// By default this method always adds the closest proof.
    /// If \c add_closest is false, it only adds the next proof to the message.
    /// This correspond to the case of "wildcard answer responses" as described
    /// in Section 7.2.6 of RFC5155.
    uint8_t addClosestEncloserProof(isc::datasrc::ZoneFinder& finder,
                                    const isc::dns::Name& name, bool exact_ok,
                                    bool add_closest = true);

    /// \brief Add matching or covering NSEC3 to the response for a give name.
    ///
    /// This method calls \c findNSEC3() of the given zone finder for the
    /// given name in the non recursive mode, and adds the returned NSEC3 to
    /// the authority section of the response message associated with the
    /// \c Query object.
    ///
    /// Depending on the caller's context, the returned NSEC3 is one and
    /// only one of matching or covering NSEC3.  If \c match is true the
    /// returned NSEC3 must be a matching one; otherwise it must be a covering
    /// one.  If this assumption isn't met this method throws a BadNSEC3
    /// exception (if it must be a matching NSEC3 but is not, it means a broken
    /// zone, maybe with incorrect optout NSEC3s; if it must be a covering
    /// NSEC3 but is not, it means a run time collision; or the \c findNSEC3()
    /// implementation is broken for both cases.)
    void addNSEC3ForName(isc::datasrc::ZoneFinder& finder,
                         const isc::dns::Name& name, bool match);

    /// Set up the Query object for a new query lookup
    ///
    /// This is the first step of the process() method, and initializes
    /// the member data
    ///
    /// \param client_list The datasource list wherein the answer to the query
    /// is to be found.
    /// \param qname The query name
    /// \param qtype The RR type of the query
    /// \param response The response message to store the answer to the query.
    /// \param dnssec If the answer should include signatures and NSEC/NSEC3 if
    ///     possible.
    void initialize(datasrc::ClientList& client_list,
                    const isc::dns::Name& qname, const isc::dns::RRType& qtype,
                    isc::dns::Message& response, bool dnssec = false);

    /// \brief Resets any partly built response data, and internal pointers
    ///
    /// Called by the QueryCleaner object upon its destruction
    void reset();

    /// \brief Internal class used for cleanup of Query members
    ///
    /// The process() call creates an object of this class, which
    /// upon its destruction, calls Query::reset(), so that outside
    /// of single calls to process(), the query state is always clean.
    class QueryCleaner {
    public:
        QueryCleaner(isc::auth::Query& query) : query_(query) {}
        ~QueryCleaner() { query_.reset(); }
    private:
        isc::auth::Query& query_;
    };

protected:
    // Following methods declared protected so they can be accessed
    // by unit tests.

    void createResponse();

public:
    /// Default constructor.
    ///
    /// Query parameters will be set by the call to process()
    ///
    Query() :
        client_list_(NULL), qname_(NULL), qtype_(NULL),
        dnssec_(false), dnssec_opt_(isc::datasrc::ZoneFinder::FIND_DEFAULT),
        response_(NULL)
    {
        answers_.reserve(RESERVE_RRSETS);
        authorities_.reserve(RESERVE_RRSETS);
        additionals_.reserve(RESERVE_RRSETS);
    }


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
    ///
    /// \param client_list The datasource list wherein the answer to the query
    /// is to be found.
    /// \param qname The query name
    /// \param qtype The RR type of the query
    /// \param response The response message to store the answer to the query.
    /// \param dnssec If the answer should include signatures and NSEC/NSEC3 if
    ///     possible.
    void process(datasrc::ClientList& client_list,
                 const isc::dns::Name& qname, const isc::dns::RRType& qtype,
                 isc::dns::Message& response, bool dnssec = false);

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

    /// An invalid result is given when a valid NSEC is expected
    ///
    /// This can only happen when the underlying data source implementation or
    /// the zone is broken.  By throwing an exception we treat such cases
    /// as SERVFAIL.
    struct BadNSEC : public BadZone {
        BadNSEC(const char* file, size_t line, const char* what) :
            BadZone(file, line, what)
        {}
    };

    /// An invalid result is given when a valid NSEC3 is expected
    ///
    /// This can only happen when the underlying data source implementation or
    /// the zone is broken.  By throwing an exception we treat such cases
    /// as SERVFAIL.
    struct BadNSEC3 : public BadZone {
        BadNSEC3(const char* file, size_t line, const char* what) :
            BadZone(file, line, what)
        {}
    };

    /// An invalid result is given when a valid DS records (or NXRRSET) is
    /// expected
    ///
    /// This can only happen when the underlying data source implementation
    /// or the zone is broken. A DS query for a known delegation point should
    /// either result in SUCCESS (if available) or NXRRSET
    struct BadDS : public BadZone {
        BadDS(const char* file, size_t line, const char* what) :
            BadZone(file, line, what)
        {}
    };

    /// \brief Response Creator Class
    ///
    /// This is a helper class of Query, and is expected to be used during the
    /// construction of the response message. This class performs the
    /// duplicate RRset detection check.  It keeps a list of RRsets added
    /// to the message and does not add an RRset if it is the same as one
    /// already added.
    ///
    /// This class is essentially private to Query, but is visible to public
    /// for testing purposes.  It's not expected to be used from a normal
    /// application.
    class ResponseCreator {
    public:
        /// \brief Constructor
        ///
        /// Reserves space for the list of RRsets.  Although the
        /// ResponseCreator will be used to create a message from the
        /// contents of the Query object's answers_, authorities_ and
        /// additionals_ elements, and each of these are sized to
        /// RESERVE_RRSETS, it is _extremely_ unlikely that all three will be
        /// filled to capacity.  So we reserve more elements than in each of
        /// these components, but not three times the amount.
        ///
        /// As with the answers_, authorities_ and additionals_ elements, the
        /// reservation is made in the constructor to avoid dynamic allocation
        /// of memory.  The ResponseCreator is a member variable of the Query
        /// object so is constructed once and lasts as long as that object.
        /// Internal state is cleared through the clear() method.
        ResponseCreator() {
            added_.reserve(2 * RESERVE_RRSETS);
        }

        /// \brief Reset internal state
        void clear() {
            added_.clear();
        }

        /// \brief Complete the response message with filling in the
        /// response sections.
        ///
        /// This is the final step of the Query::process() method, and within
        /// that method, it should be called before it returns (if any
        /// response data is to be added)
        ///
        /// This will take a message to build and each RRsets for the answer,
        /// authority, and additional sections, and add them to their
        /// corresponding sections in the given message.  The RRsets are
        /// filtered such that a particular RRset appears only once in the
        /// message. Any RRSIGs attached to the RRsets will be included
        /// when they are rendered.
        void create(
            isc::dns::Message& message,
            const std::vector<isc::dns::ConstRRsetPtr>& answers_,
            const std::vector<isc::dns::ConstRRsetPtr>& authorities_,
            const std::vector<isc::dns::ConstRRsetPtr>& additionals_);

    private:
        // \brief RRset comparison functor.
        struct IsSameKind : public std::binary_function<
                            const isc::dns::AbstractRRset*,
                            const isc::dns::AbstractRRset*,
                            bool> {
            bool operator()(const isc::dns::AbstractRRset* r1,
                            const isc::dns::AbstractRRset* r2) const {
                return (r1->isSameKind(*r2));
            }
        };

        /// Insertion operation
        ///
        /// \param message Message to which the RRset is to be added
        /// \param section Section of the message in which the RRset is put
        /// \param rrset Pointer to RRset to be added to the message
        void addRRset(isc::dns::Message& message,
                      const isc::dns::Message::Section section,
                      const isc::dns::ConstRRsetPtr& rrset);


    private:
        /// List of RRsets already added to the message
        std::vector<const isc::dns::AbstractRRset*> added_;
    };

private:
    const isc::datasrc::ClientList* client_list_;
    const isc::dns::Name* qname_;
    const isc::dns::RRType* qtype_;
    bool dnssec_;
    isc::datasrc::ZoneFinder::FindOptions dnssec_opt_;
    ResponseCreator response_creator_;

    isc::dns::Message* response_;
    std::vector<isc::dns::ConstRRsetPtr> answers_;
    std::vector<isc::dns::ConstRRsetPtr> authorities_;
    std::vector<isc::dns::ConstRRsetPtr> additionals_;
};

}
}

// Local Variables:
// mode: c++
// End:
