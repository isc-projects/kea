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

#ifndef ISC_TESTUTILS_SRVTEST_H
#define ISC_TESTUTILS_SRVTEST_H 1

#include <util/buffer.h>
#include <dns/name.h>
#include <dns/message.h>
#include <dns/messagerenderer.h>
#include <dns/opcode.h>
#include <dns/rcode.h>
#include <dns/rrclass.h>
#include <dns/rrtype.h>

#include "mockups.h"
#include <boost/scoped_ptr.hpp>

namespace asiolink {
class IOSocket;
class IOMessage;
class IOEndpoint;
}

namespace isc {
namespace testutils {
extern const char* const DEFAULT_REMOTE_ADDRESS;
extern const uint16_t DEFAULT_REMOTE_PORT;

// These are flags to indicate whether the corresponding flag bit of the
// DNS header is to be set in the test cases.  (The flag values
// is irrelevant to their wire-format values)
extern const unsigned int QR_FLAG;
extern const unsigned int AA_FLAG;
extern const unsigned int TC_FLAG;
extern const unsigned int RD_FLAG;
extern const unsigned int RA_FLAG;
extern const unsigned int AD_FLAG;
extern const unsigned int CD_FLAG;

/// \brief The base class for Auth and Recurse test case
class SrvTestBase : public ::testing::Test {
protected:
    SrvTestBase();

    /// Let the server process a DNS message.
    ///
    /// The derived class implementation is expected to pass \c io_message,
    /// \c parse_message, \c response_obuffer, and \c dnsserv to the server
    /// implementation it is testing.
    virtual void processMessage() = 0;

    /// The following methods implement server independent test logic using
    /// the template method pattern.  Each test calls \c processMessage()
    /// to delegate the server-dependent behavior to the actual implementation
    /// classes.
    void unsupportedRequest();
    void multiQuestion();
    void shortMessage();
    void response();
    void shortQuestion();
    void shortAnswer();
    void ednsBadVers();
    void axfrOverUDP();

    /// Create DNS packet data from a file.
    ///
    /// It constructs wire-format DNS packet data from \c datafile in the
    /// form of \c IOMessage in \c io_message.
    /// The existing content of \c io_message, if any, will be deleted.
    void createDataFromFile(const char* const datafile,
                            int protocol = IPPROTO_UDP);

    ///  Create DNS packet data from a message.
    ///
    /// It constructs wire-format DNS packet data from \c message in the
    /// form of \c IOMessage in \c io_message.
    /// The existing content of \c io_message, if any, will be deleted.
    void createRequestPacket(isc::dns::Message& message,
                             const int protocol = IPPROTO_UDP,
                             isc::dns::TSIGContext* context = NULL,
                             const char* const address = DEFAULT_REMOTE_ADDRESS,
                             uint16_t port = DEFAULT_REMOTE_PORT);

    MockServer dnsserv;
    isc::dns::Message request_message;
    isc::dns::MessagePtr parse_message;
    isc::dns::MessagePtr response_message;
    const isc::dns::qid_t default_qid;
    const isc::dns::Opcode opcode;
    const isc::dns::Name qname;
    const isc::dns::RRClass qclass;
    const isc::dns::RRType qtype;
    asiolink::IOSocket* io_sock;
    boost::scoped_ptr<asiolink::IOMessage> io_message;
    boost::scoped_ptr<const asiolink::IOEndpoint> endpoint;
    isc::dns::MessageRenderer request_renderer;
    isc::util::OutputBufferPtr response_obuffer;
    std::vector<uint8_t> data;
};
} // end of namespace testutils
} // end of namespace isc
#endif  // ISC_TESTUTILS_SRVTEST_H

// Local Variables:
// mode: c++
// End:
