// Copyright (C) 2011  Internet Systems Consortium, Inc. ("ISC")
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

#ifndef RESPONSE_SCRUBBER_H
#define RESPONSE_SCRUBBER_H

/// \page DataScrubbing Data Scrubbing
/// \section DataScrubbingIntro Introduction
/// When a response is received from an authoritative server, it should be
/// checked to ensure that the data contained in it is valid.  Signed data is
/// not a problem - validating the signatures is a sufficient check.  But
/// unsigned data in a response is more of a problem. (Note that even data from
/// signed zones may be not be signed, e.g. delegations are not signed.) In
/// particular, how do we know that the server from which the response was
/// received was authoritive for the data it returned?
///
/// The part of the code that checks for this is the "Data Scrubbing" module.
/// Although it includes the checking of IP addresses and ports, it is called
/// "Scrubbing" because it "scrubs" the returned message and removes doubtful
/// information.
///
/// \section DataScrubbingBasic Basic Checks
/// The first part - how do we know that the response comes from the correct
/// server - is relatively trivial, albeit not foolproof (which is why DNSSEC
/// was developed).  The following are checked:
///
/// - The IP address from which the response was received is the same as the
///   one to which the query was sent.
/// - The port on which the response was received is the same as the one from
///   which the query was sent.
///
/// (These tests need not not done for a TCP connection - if data is received
/// over the TCP stream, it is assumed that it comes from the address and port
/// to which a connection was made.)
///
/// - The protocol used to send the question is the same as the protocol on
///   which an answer was received.
///
/// (Strictly speaking, if this check fails it is a programming error - the
/// code should not mix up UPD and TCP messages.)
///
/// - The QID in the response message is the same as the QID in the query
///   message sent.
///
/// If the conditions are met, then the data - in all three response sections -
/// is scanned and out of bailiwick data is removed ("scrubbed").
///
/// \section DataScrubbingBailiwick Bailiwick
/// Bailiwick means "district or jurisdiction of bailie or bailiff" (Concise
/// Oxford Dictionary, 7th Edition).  It is not a term mentioned in any RFC
/// (or at least, any RFC up to RFC 5997) but is widely used in DNS literature.
/// In this context it is taken to mean the data for which a DNS server has
/// authority.  So when we speak of the information being "in bailiwick", we
/// mean that the the server is the ultimate source of authority for that data.
///
/// In practice, determining this from the response alone is difficult.  In
/// particular, as a server may be authoritative for many zones, it could in
/// theory be authoritative for any combination of RRsets that appear in a
/// response.
///
/// For this reason, bailiwick is dependent on the query.  If, for example, a
/// query for www.example.com is sent to the nameservers for example.com
/// (because of a referral of from the com. servers), the bailiwick for the
/// query is example.com.  This means that any information returned on domains
/// other than example.com may not be authoritative.  More exactly, it may be
/// authoritative (because the server is also authoritative for the zone
/// concerned), but based on the information available (in this example, that
/// the response originated from a nameserver for the zone example.com) it is
/// not possible to be certain.
///
/// Ideally, out of bailiwick data should be excluded from further processing
/// as it may be incorrect and corrupt the cache.  In practice, there are
/// two cases to consider:
///
/// The first is when the data has a qname that is not example.com or a
/// subdomain of it (e.g. xyz.com, www.example.net).  In this case the data can
/// be retrieved by an independent query - no path from the root zone to the
/// data goes through the current bailiwick, so there is no chance of ending up
/// in a loop.  In this case, data that appears to be out of bailiwick can be
/// dropped from the response.
///
/// The second case is when the QNAME of the data is a subdomain of the
/// bailiwick.  Here the server may or may not be authoritative for the data.
/// For example, if the name queried for were www.sub.example.com and the
/// example.com nameservers supplied an answer:
///
/// - The answer could be authoritative - www.sub.example.com could be
///   in the example.com zone.
/// - The answer might not be authoritative - the zone sub.example.com may have
///   been delegated, so the authoritative answer should come from
///   sub.example.com's nameservers.
/// - The answer might be authoritative even though zone sub.example.com has
///   been delegated, because the nameserver for example.com is the same as
///   that for sub.example.com.
///
/// Unlike the previous case, it is not possible to err on the side of caution
/// and drop such data.  Any independent query for it will pass through the
/// current bailiwick and the same question will be asked again.  For this
/// reason, any data in the response that has a QNAME equal to a subdomain of
/// the bailiwick has to be accepted.
///
/// In summary then, data in a response that has a QNAME equal to or a subdomain
/// of the bailiwick is considered in-bailiwick.  Anything else is out of of
/// bailiwick.
///
/// \subsection DataScrubbingCrossSection Cross-Section Scrubbing
/// Even with the bailiwick checks above, there are some additional cleaning
/// that can be done with the packet.  In particular:
///
/// - The QNAMEs of the RRsets in the authority section must be equal to or
///   superdomains of a QNAME of an RRset in the answer.  Any that are not
///   should be removed.
/// - If there is no answer section, the QNAMES of RRsets in the authority
///   section must be equal to or superdomains of the QNAME of the RRset in the
///   question.
///
/// Although previous checks should have removed some inconsistencies, it
/// will not trap obscure cases (e.g. bailiwick: "example.com", answer:
/// "www.example.com", authority: sub.example.com).  These checks do just that.
///
/// (Note that not included here is QNAME of question not equal to or a
/// superdomain of the answer; that check is made in the ResponseClassifier
/// class.)
///
/// \section DataScrubbingExample Examples
/// Some examples should make this clear: they all use the notation
/// Qu = Question, Zo = Zone being queried, An = Answer, Au = Authority,
/// Ad = Additional.
///
/// \subsection DataScrubbingEx1 Example 1: Simple Query
/// Querying a nameserver for the zone "example.com" for www.example.com and
/// receiving the answer "www.example.com A 1.2.3.4" with two nameservers quoted
/// as authority and both their addresses in the additional section:
///
/// Qu: www.example.com\n
/// Zo: example.com
///
/// An: www.example.com A 192.0.2.1
///
/// Au(1): example.com NS ns0.example.com\n
/// Au(2): example.com NS ns1.example.net
///
/// Ad(1): ns0.example.com A 192.0.2.100\n
/// Ad(2): ns1.example.net A 192.0.2.200
///
/// This answer could be returned by a properly configured server.  All resource
/// records in the answer - with the exception of Ad(2) - are in bailiwick
/// because the QNAME is equal to or a subdomain of the zone being queried.
///
/// It is permissible for Ad(2) to be returned by a properly configured server
/// as a hint to resolvers.  However the example.com nameservers are not
/// authoritative for addresses of domains in example.net; that record could
/// be out of date or incorrect.  Indeed, it might even be a deliberate attempt
/// at a spoof by getting us to cache an invalid address for ns1.example.net.
/// The safest thing to do is to drop the A record and to get the address of
/// ns1.example.net by querying for that name through the .net nameservers.
///
/// \subsection DataScrubbingEx2 Example 2: Multiple Zones on Same Nameserver
/// Assume now that example.com and sub.example.com are hosted on the same
/// nameserver and that from the .com zone the resolver has received a referral
/// to example.com.  Suppose that the query is for www.sub.example.com and that
/// the following response is received:
///
/// Qu: www.sub.example.com\n
/// Zo: example.com
///
/// An: (nothing)
///
/// Au(1): sub.example.com NS ns0.sub.example.com\n
/// Au(2): sub.example.com NS ns1.example.net
///
/// Ad(1): ns0.sub.example.com A 192.0.2.101\n
/// Ad(2): ns1.example.net A 192.0.2.201
///
/// Although we asked the example.com nameservers for information, we got the
/// nameservers for sub.example.com in the authority section.  This is valid
/// because if BIND-10 hosts multiple zones, it will look up the data in the
/// zone that most closely matches the query.
///
/// Using the criteria above, the data in the additional section can therefore
/// be regarded as in bailiwick because sub.example.com is a subdomain of
/// example.com.  As before though, the address for ns1.example.net in the
/// additional section is not in bailiwick because ns1.example.net is now a
/// subdomain of example.com.
///
/// \subsection DataScrubbingEx3 Example 3: Deliberate Spoof Attempt
/// Qu: www.example.com\n
/// Zo: example.com
///
/// An: www.example.com A 192.0.2.1
///
/// Au(1): com NS ns0.example.com\n
/// Au(2): com NS ns1.example.net
///
/// Ad(1): ns0.example.com A 192.0.2.100\n
/// Ad(2): ns1.example.net A 192.0.2.200
///
/// This is a deliberately invalid response.  The query is being sent to the
/// nameservers for example.com (presumably because a referral to example.com
/// was received from the com nameservers), but the response is an attempt
/// to get the specified nameservers cached as the nameservers for com - for
/// which example.com is not authoritative.
///
/// Note though that this response is only invalid because, due to the previous
/// referral, the query was sent to the example.com nameservers.  Had the
/// referral been to the com nameservers, it would be a valid response; the com
/// zone could well be serving all the data for example.com.  Having said that,
/// the A record for ns1.example.net would still be regarded as being out of
/// bailiwick becase the nameserver is not authoritative for the .net zone.
///
/// \subsection DataScrubbingEx4 Example 4: Inconsistent Answer Section
/// Qu: www.example.com\n
/// Zo: example.com
///
/// An: www.example.com A 192.0.2.1
///
/// Au(1): alpha.example.com NS ns0.example.com\n
/// Au(2): alpha.example.com NS ns1.example.net
///
/// Ad(1): ns0.example.com A 192.0.2.100\n
/// Ad(2): ns1.example.net A 192.0.2.200
///
/// Here, everything in the answer and authority sections is in bailiwick for
/// the example.com server. And although the zone example.com was queried, it
/// is permissible for the authority section to contain nameservers with a
/// qname that is a subdomain of example.com (e.g. see \ref DataScrubbingEx2).
/// However, only servers with a qname that is equal to or a superdomain of
/// the answer are authoritative for the answer.  So in this case, both
/// Au(1) and Au(2) (as well as Ad(2), for reasons given earlier) will be
/// scrubbed.

#include <config.h>
#include <asiolink/io_endpoint.h>
#include <dns/message.h>
#include <dns/name.h>

/// \brief Response Data Scrubbing
///
/// This is the class that implements the data scrubbing.  Given a response
/// message and some additional information, it checks the information using
/// the rules given in \ref DataScrubbing and either rejects the packet or
/// modifies it to remove non-conforming RRsets.
///
/// TODO: Examine the additional records and remove all cases where the
/// QNAME does not match the RDATA of records in the authority section.

class ResponseScrubber {
public:

    /// \brief Response Code for Address Check
    enum Category {
        SUCCESS = 0,            ///< Packet is OK

        // Error categories

        ADDRESS = 1,            ///< Mismatching IP address
        PORT = 2,               ///< Mismatching port
        PROTOCOL = 3            ///< Mismatching protocol
    };

    /// \brief Check IP Address
    ///
    /// Compares the address to which the query was sent, the port it was
    /// sent from, and the protocol used for communication with the (address,
    /// port, protocol) from which the response was received.
    ///
    /// \param to Endpoint representing the address to which the query was sent.
    /// \param from Endpoint from which the response was received.
    ///
    /// \return SUCCESS if the two endpoints match, otherwise an error status
    /// indicating what was incorrect.
    static Category addressCheck(const isc::asiolink::IOEndpoint& to,
        const isc::asiolink::IOEndpoint& from);

    /// \brief Check QID
    ///
    /// Compares the QID in the sent message with the QID in the response.
    ///
    /// \param sent Message sent to the authoritative server
    /// \param received Message received from the authoritative server
    ///
    /// \return true if the QIDs match, false otherwise.
    static bool qidCheck(const isc::dns::Message& sent,
        const isc::dns::Message& received) {
        return (sent.getQid() == received.getQid());
    }

    /// \brief Generalised Scrub Message Section
    ///
    /// When scrubbing a message given the bailiwick of the server, RRsets are
    /// retained in the message section if the QNAME is equal to or a subdomain
    /// of the bailiwick.  However, when checking QNAME of RRsets in the
    /// authority section against the QNAME of the question or answers, RRsets
    /// are retained only if their QNAME is equal to or a superdomain of the
    /// name in question.
    ///
    /// This method provides the generalised scrubbing whereby the RRsets in
    /// a section are tested against a given name, and RRsets kept if their
    /// QNAME is equal to or in the supplied relationship with the given name.
    ///
    /// \param section Section of the message to be scrubbed.
    /// \param names Names against which RRsets should be checked.  Note that
    /// this is a vector of pointers to Name objects; they are assumed to
    /// independently exist, and the caller retains ownership of them and is
    /// assumed to destroy them when needed.
    /// \param connection Relationship required for retention, i.e. the QNAME of
    /// an RRset in the specified section must be equal to or a "connection"
    /// (SUPERDOMAIN/SUBDOMAIN) of "name" for the RRset to be retained.
    /// \param message Message to be scrubbed.
    ///
    /// \return Count of the number of RRsets removed from the section.
    static unsigned int scrubSection(isc::dns::Message& message,
        const std::vector<const isc::dns::Name*>& names,
        const isc::dns::NameComparisonResult::NameRelation connection,
        const isc::dns::Message::Section section);

    /// \brief Scrub All Sections of a Message
    ///
    /// Scrubs each of the answer, authority and additional sections of the
    /// message.
    ///
    /// No distinction is made between RRsets legitimately in the message (e.g.
    /// glue for authorities that are not in bailiwick) and ones that could be
    /// considered as attempts of spoofing (e.g. non-bailiwick RRsets in the
    /// additional section that are not related to the query).
    ///
    /// The resultant packet returned to the caller may be invalid.  If so, it
    /// is up to the caller to detect that.
    ///
    /// \param message Message to be scrubbed.
    /// \param bailiwick Name of the zone whose authoritative servers were
    /// queried.
    ///
    /// \return Count of the number of RRsets removed from the message.
    static unsigned int scrubAllSections(isc::dns::Message& message,
        const isc::dns::Name& bailiwick);

    /// \brief Scrub Across Message Sections
    ///
    /// Does some cross-section comparisons and removes inconsistent RRs.  In
    /// particular it:
    ///
    /// - If an answer is present, checks that the qname of the authority RRs
    ///   are equal to or superdomain of the qname answer RRsets.  Any that are
    ///   not are removed.
    /// - If an answer is not present, checks that the authority RRs are
    ///   equal to or superdomains of the question.  If not, the authority RRs
    ///   are removed.
    ///
    /// Note that the scrubbing does not check:
    ///
    /// - that the question is in the bailiwick of the server; that check is
    ///   assumed to have been done prior to the query being sent (else why
    ///   was the query sent there in the first place?)
    /// - that the qname of one of the RRsets in the answer (if present) is
    ///   equal to the qname of the question (that check is done in the
    ///   response classification code).
    ///
    /// \param message Message to be scrubbed.
    ///
    /// \return Count of the number of RRsets removed from the section.
    static unsigned int scrubCrossSections(isc::dns::Message& message);
    
    /// \brief Main Scrubbing Entry Point
    ///
    /// The single entry point to the module to sanitise the message.  All
    /// it does is call the various other scrubbing methods.
    ///
    /// \param message Pointer to the message to be scrubbed. (This is a
    /// pointer - as opposed to a Message as in other methods in this class -
    /// as the external code is expected to be mainly using message pointers
    /// to access messages.)
    /// \param bailiwick Name of the zone whose authoritative servers were
    /// queried.
    ///
    /// \return Count of the number of RRsets removed from the message.
    static unsigned int scrub(const isc::dns::MessagePtr& message,
        const isc::dns::Name& bailiwick);

    /// \brief Comparison Function for Sorting Name Pointers
    ///
    /// Utility method called to sorts pointers to names in lexical order.
    ///
    /// \param n1 Pointer to first Name object
    /// \param n2 Pointer to second Name object
    ///
    /// \return true if n1 is less than n2, false otherwise.
    static bool compareNameLt(const isc::dns::Name* n1,
        const isc::dns::Name* n2)
    {
        return (*n1 < *n2);
    }

    /// \brief Function for Comparing Name Pointers
    ///
    /// Utility method called to sorts pointers to names in lexical order.
    ///
    /// \param n1 Pointer to first Name object
    /// \param n2 Pointer to second Name object
    ///
    /// \return true if n1 is equal to n2, false otherwise.
    static bool compareNameEq(const isc::dns::Name* n1,
        const isc::dns::Name* n2)
    {
        return (*n1 == *n2);
    }
};

#endif // RESPONSE_SCRUBBER_H
