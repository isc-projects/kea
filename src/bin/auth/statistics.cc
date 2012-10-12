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

#include <statistics/counter.h>
#include <statistics/counter_dict.h>

#include <algorithm>
#include <cctype>
#include <cassert>
#include <string>
#include <sstream>
#include <iostream>

#include <boost/noncopyable.hpp>

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

using namespace isc::dns;
using namespace isc::auth;
using namespace isc::statistics;

namespace isc {
namespace auth {
namespace statistics {

// TODO: Make use of wrappers like isc::dns::Opcode
// for counter item type.

class CountersImpl : boost::noncopyable {
public:
    CountersImpl();
    ~CountersImpl();
    void inc(const QRAttributes& qrattrs, const Message& response);
    isc::data::ConstElementPtr getStatistics() const;
    void registerStatisticsValidator(Counters::validator_type validator);
private:
    // counter for query/response
    Counter server_qr_counter_;
    // set of counters for zones
    CounterDictionary zone_qr_counters_;
    // validator
    Counters::validator_type validator_;
};

CountersImpl::CountersImpl() :
    // size of server_qr_counter_, zone_qr_counters_: QR_COUNTER_TYPES
    server_qr_counter_(QR_COUNTER_TYPES),
    zone_qr_counters_(QR_COUNTER_TYPES),
    validator_()
{}

CountersImpl::~CountersImpl()
{}

void
CountersImpl::inc(const QRAttributes& qrattrs, const Message& response) {
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
        // If signature validation is failed, no other attributes are reliable
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
        // get the first and only question section and
        // get the qtype code
        const unsigned int qtype = (*qiter)->getType().getCode();
        if (qtype < 258) {
            // qtype 0..257: lookup qtype-countertype table
            qtype_type = QRQTypeToQRCounterType[qtype];
        } else if (qtype < 32768) {
            // qtype 258..32767: (Unassigned)
            qtype_type = QR_QTYPE_OTHER;
        } else if (qtype < 32770) {
            // qtype 32768..32769: TA and DLV
            qtype_type = QR_QTYPE_TA + (qtype - 32768);
        } else {
            // qtype 32770..65535: (Unassigned, Private use, Reserved)
            qtype_type = QR_QTYPE_OTHER;
        }
    }
    server_qr_counter_.inc(qtype_type);
    // OPCODE
    server_qr_counter_.inc(QROpCodeToQRCounterType[qrattrs.req_opcode_]);

    // response
    if (qrattrs.answer_sent_) {
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
            // rcode 0..22: lookup rcode-countertype table
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
}

isc::data::ConstElementPtr
CountersImpl::getStatistics() const {
    std::stringstream statistics_string;
    statistics_string << "{ \"queries.udp\": "
                      << server_qr_counter_.get(QR_REQUEST_UDP)
                      << ", \"queries.tcp\": "
                      << server_qr_counter_.get(QR_REQUEST_TCP);
    // Insert non 0 Opcode counters.
    for (int i = QR_OPCODE_QUERY; i <= QR_OPCODE_OTHER; ++i) {
        const Counter::Type counter = server_qr_counter_.get(i);
        if (counter != 0) {
            statistics_string << ", \"" << "opcode." <<
                                 QRCounterOpcode[i - QR_OPCODE_QUERY].name <<
                                 "\": " << counter;
        }
    }
    // Insert non 0 Rcode counters.
    for (int i = QR_RCODE_NOERROR; i <= QR_RCODE_OTHER; ++i) {
        const Counter::Type counter = server_qr_counter_.get(i);
        if (counter != 0) {
            statistics_string << ", \"" << "rcode." <<
                                 QRCounterRcode[i - QR_RCODE_NOERROR].name <<
                                 "\": " << counter;
        }
    }
    statistics_string << "}";

    isc::data::ConstElementPtr statistics_element =
        isc::data::Element::fromJSON(statistics_string);
    // validate the statistics data before send
    if (validator_) {
        if (!validator_(statistics_element)) {
            LOG_ERROR(auth_logger, AUTH_INVALID_STATISTICS_DATA);
            return (isc::data::ElementPtr());
        }
    }
    return (statistics_element);
}

void
CountersImpl::registerStatisticsValidator
    (Counters::validator_type validator)
{
    validator_ = validator;
}

Counters::Counters() : impl_(new CountersImpl())
{}

Counters::~Counters() {}

void
Counters::inc(const QRAttributes& qrattrs, const Message& response) {
    impl_->inc(qrattrs, response);
}

isc::data::ConstElementPtr
Counters::getStatistics() const {
    return (impl_->getStatistics());
}

void
Counters::registerStatisticsValidator
    (Counters::validator_type validator) const
{
    return (impl_->registerStatisticsValidator(validator));
}

} // namespace statistics
} // namespace auth
} // namespace isc
