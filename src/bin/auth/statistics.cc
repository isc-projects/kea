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

#include <auth/statistics.h>
#include <auth/statistics_items.h>
#include <auth/auth_log.h>

#include <dns/opcode.h>
#include <dns/rcode.h>

#include <cc/data.h>
#include <cc/session.h>

#include <algorithm>
#include <cctype>
#include <cassert>
#include <string>
#include <sstream>
#include <iostream>

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

using namespace isc::dns;
using namespace isc::auth;
using namespace isc::statistics;

namespace {

void
fillNodes(const Counter& counter, const struct CounterTypeTree type_tree[],
          isc::auth::statistics::Counters::ItemTreeType& trees)
{
    using namespace isc::data;

    for (int i = 0; type_tree[i].name != NULL; ++i) {
        if (type_tree[i].sub_tree != NULL) {
            isc::auth::statistics::Counters::ItemTreeType sub_tree =
                Element::createMap();
            trees->set(type_tree[i].name, sub_tree);
            fillNodes(counter, type_tree[i].sub_tree, sub_tree);
        } else {
            trees->set(type_tree[i].name,
                       Element::create(static_cast<long int>(
                           counter.get(type_tree[i].counter_id)))
                       );
        }
    }
}

} // anonymous namespace

namespace isc {
namespace auth {
namespace statistics {

Counters::Counters() :
    // size of server_qr_counter_, zone_qr_counters_: QR_COUNTER_TYPES
    server_qr_counter_(QR_COUNTER_TYPES),
    zone_qr_counters_(QR_COUNTER_TYPES)
{}

Counters::~Counters()
{}

void
Counters::incRequest(const QRAttributes& qrattrs, const Message& response) {
    // protocols carrying request
    if (qrattrs.req_ip_version_ == AF_INET) {
        server_qr_counter_.inc(QR_REQUEST_IPV4);
    } else if (qrattrs.req_ip_version_ == AF_INET6) {
        server_qr_counter_.inc(QR_REQUEST_IPV6);
    }
    if (qrattrs.req_transport_protocol_ == IPPROTO_UDP) {
        server_qr_counter_.inc(QR_REQUEST_UDP);
    } else if (qrattrs.req_transport_protocol_ == IPPROTO_TCP) {
        server_qr_counter_.inc(QR_REQUEST_TCP);
    }

    // query TSIG
    if (qrattrs.req_is_tsig_) {
        server_qr_counter_.inc(QR_REQUEST_TSIG);
    }
    if (qrattrs.req_is_sig0_) {
        server_qr_counter_.inc(QR_REQUEST_SIG0);
    }
    if (qrattrs.req_is_badsig_) {
        server_qr_counter_.inc(QR_REQUEST_BADSIG);
        // If signature validation is failed, no other query attributes are
        // reliable. Skip processing of the rest of query counters.
        return;
    }

    // query EDNS
    if (qrattrs.req_is_edns_0_) {
        server_qr_counter_.inc(QR_REQUEST_EDNS0);
    }
    if (qrattrs.req_is_edns_badver_) {
        server_qr_counter_.inc(QR_REQUEST_BADEDNSVER);
    }

    // query DNSSEC
    if (qrattrs.req_is_dnssec_ok_) {
        server_qr_counter_.inc(QR_REQUEST_DNSSEC_OK);
    }

    // QTYPE
    unsigned int qtype_type = QR_QTYPE_OTHER;
    const QuestionIterator qiter = response.beginQuestion();
    if (qiter != response.endQuestion()) {
        // get the first and only question section
        const QuestionPtr qptr = *qiter;
        if (qptr != NULL) {
            // get the qtype code
            const unsigned int qtype = qptr->getType().getCode();
            if (qtype < 258) {
                // qtype 0..257
                qtype_type = QRQTypeToQRCounterType[qtype];
            } else if (qtype < 32768) {
                // qtype 258..32767
                qtype_type = QR_QTYPE_OTHER;
            } else if (qtype < 32770) {
                // qtype 32768..32769
                qtype_type = QR_QTYPE_TA + (qtype - 32768);
            } else {
                // qtype 32770..65535
                qtype_type = QR_QTYPE_OTHER;
            }
        }
    }
    server_qr_counter_.inc(qtype_type);
    // OPCODE
    server_qr_counter_.inc(QROpCodeToQRCounterType[qrattrs.req_opcode_]);
}

void
Counters::incResponse(const QRAttributes& qrattrs, const Message& response) {
    // responded
    server_qr_counter_.inc(QR_RESPONSE);

    // response truncated
    if (qrattrs.res_is_truncated_) {
        server_qr_counter_.inc(QR_RESPONSE_TRUNCATED);
    }

    // response EDNS
    ConstEDNSPtr response_edns = response.getEDNS();
    if (response_edns != NULL && response_edns->getVersion() == 0) {
        server_qr_counter_.inc(QR_RESPONSE_EDNS0);
    }

    // response TSIG
    if (qrattrs.req_is_tsig_) {
        // assume response is TSIG signed if request is TSIG signed
        server_qr_counter_.inc(QR_RESPONSE_TSIG);
    }

    // response SIG(0) is currently not implemented

    // RCODE
    const unsigned int rcode = response.getRcode().getCode();
    unsigned int rcode_type = QR_RCODE_OTHER;
    if (rcode < 23) {
        // rcode 0..22
        rcode_type = QRRCodeToQRCounterType[rcode];
    } else {
        // opcode larger than 22 is reserved or unassigned
        rcode_type = QR_RCODE_OTHER;
    }
    server_qr_counter_.inc(rcode_type);

    // compound attributes
    const unsigned int answer_rrs =
        response.getRRCount(Message::SECTION_ANSWER);
    const bool is_aa_set = response.getHeaderFlag(Message::HEADERFLAG_AA);

    if (is_aa_set) {
        // QryAuthAns
        server_qr_counter_.inc(QR_QRYAUTHANS);
    } else {
        // QryNoAuthAns
        server_qr_counter_.inc(QR_QRYNOAUTHANS);
    }

    if (rcode == Rcode::NOERROR_CODE) {
        if (answer_rrs > 0) {
            // QrySuccess
            server_qr_counter_.inc(QR_QRYSUCCESS);
        } else {
            if (is_aa_set) {
                // QryNxrrset
                server_qr_counter_.inc(QR_QRYNXRRSET);
            } else {
                // QryReferral
                server_qr_counter_.inc(QR_QRYREFERRAL);
            }
        }
    } else if (rcode == Rcode::REFUSED_CODE) {
        // AuthRej
        server_qr_counter_.inc(QR_QRYREJECT);
    }
}

void
Counters::inc(const QRAttributes& qrattrs, const Message& response) {
    // increment request counters
    incRequest(qrattrs, response);

    if (qrattrs.answer_sent_) {
        // increment response counters if answer was sent
        incResponse(qrattrs, response);
    }
}

Counters::ItemTreeType
Counters::get() const {
    using namespace isc::data;

    Counters::ItemTreeType item_tree = Element::createMap();

    Counters::ItemTreeType zones = Element::createMap();
    item_tree->set("zones", zones);

    Counters::ItemTreeType server = Element::createMap();
    fillNodes(server_qr_counter_, QRCounterTree, server);
    zones->set("_SERVER_", server);

    return (item_tree);
}

} // namespace statistics
} // namespace auth
} // namespace isc
