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

#ifndef __RESPONSE_SCRUBBER_H
#define __RESPONSE_SCRUBBER_H

/// \page DataScrubbing Data Scrubbing
/// \section DataScrubbingIntro Introduction
/// When a response is received from an authoritative server, it needs to be
/// checked to ensure that the data contained in it is valid.  If all the data
/// is signed, this is not a problem - validating the signatures is a sufficient
/// check.  But an unsigned response is more of a problem. How do we check
/// that the response from the server to which we sent it?  And if we pass that
/// hurdle, how do we know that the information is correct and that the server
/// is not attempting to spoof us?
///
/// The part of the code that checks for this is the "Data Scrubbing" module.
/// Although it includes the checking of IP addresses and ports, it is called
/// "Scrubbing" because it "scrubs" the returned message and removes doubtful
/// information.
///
/// \section DataScrubbingBasic Basic Checks
/// The first part - how do we know that the response comes from the correct
/// server - is relatively trivial, albeit not foolproof (which is why DNSSEC
/// came about).  The following are checked:
///
/// # The IP address from which the response was received is the same as the
///   one to which the query was sent.
/// # The port on which the response was received is the same as the one from
///   which the query was sent.
/// # The QID in the response message is the same as the QID in the query
///   message sent.
///
/// (The first two tests are not done for a TCP connection - if data is received
/// over the TCP stream, it is assumed that it comes from the address and port
/// to which a connection was made.)
///
/// If the conditions are met, then the data - in all three response sections -
/// is scanned and out of bailiwick data is removed ("scrubbed").
///
/// \section DataScrubbingBailiwick Bailiwick
/// Bailiwick means "district or jurisdiction of bailie or bailiff" (Concise
/// Oxford Dictionary, 7th Edition).  It is not a term mentioned in any RFC
/// (or at least, any RFC up to RFC 5997), but in the context of DNS is taken
/// to mean the data for which a DNS server has authority.
///
/// What this really means is, given a record returned from that server, could
/// a properly configured server _really_ have returned it?  And if so, is the
/// server authoritiative for that data?  The only answer that satisfies both
/// criteria is a resource record where the QNAME is the same as or a subdomain
/// of the domain of the nameservers being queried.
///
/// Some examples should make this clear: they all use the notation
/// Qu = Question, Zo = Zone being asked, An = Answer, Au = Authority,
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
/// Au(2): example.com NS ns1.example.netipCheck
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
/// An: <nothing>
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

#include <config.h>
#include <asio.hpp>
#include <dns/message.h>

/// \brief Response Data Scrubbing
///
/// This is the class that implements the data scrubbing.  Given a response
/// message and some additional information, it checks the information using
/// the rules given in \ref DataScrubbing and either rejects the packet or
/// modifies it to remove non-conforming RRsets.

class ResponseScrubber {
public:

    /// \brief Response Code for Address Check
    enum Category {
        SUCCESS = 0,            ///< Packet is OK

        // Error categories

        ADDRESS,                ///< Mismatching IP address
        PORT                    ///< Mismatching port
    };

    /// \brief Check IP Address
    ///
    /// Compares the address to which the query was sent and the port it was
    /// sent from with the address from which the query was received and the
    /// port it was sent to.
    ///
    /// This is only required of a UDP connection - it is assumed that data that
    /// data received on a TCP stream is received from the system to which the
    /// connection was made.
    ///
    /// \param to Endpoint representing the address to which the query was sent.
    /// \param from Endpoint from which the response was received.
    static Category addressPortCheck(const asio::ip::udp::endpoint& to,
        const asio::ip::udp::endpoint& from);

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

    /// \brief Scrub Message Section
    ///
    /// Scrubs the message section by removing all RRsets that are not in the
    /// bailiwick of the authoritative server from the message.
    ///
    /// \param zone Name of the zone whose authoritative servers were queried.
    /// \param section Section of the message to be scrubbed
    /// \param message Message to be scrubbed.
    ///
    /// \return Count of the number of RRsets removed from the section.
    static unsigned int scrubSection(const isc::dns::Name& bailiwick,
        isc::dns::Message& message, const isc::dns::Message::Section section);

    /// \brief Scrub Message
    ///
    /// Scrubs each of the answer, authority and additional sections of the
    /// message.
    ///
    /// No distinction is made between RRsets legitimately in the message (e.g.
    /// glue for authorities that are not in bailiwick) and onces that could be
    /// considered as attempts of spoofing (e.g. non-bailiwick RRsets in the
    /// additional section that are not related to the query).
    ///
    /// The resultant packet returned to the caller may be invalid.  If so, it
    /// is up to the caller to detect that.
    ///
    /// \param zone Name of the zone whose authoritative servers were queried.
    /// \param message Message to be scrubbed.
    ///
    /// \return Count of the number of RRsets removed from the section.
    static unsigned int scrub(const isc::dns::Name& bailiwick,
        isc::dns::Message& message);
};

#endif // __RESPONSE_SCRUBBER_H
