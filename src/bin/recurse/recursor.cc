// Copyright (C) 2009  Internet Systems Consortium, Inc. ("ISC")
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

#include <config.h>

#include <netinet/in.h>

#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

#include <asiolink/asiolink.h>

#include <config/ccsession.h>

#include <cc/data.h>

#include <exceptions/exceptions.h>

#include <dns/buffer.h>
#include <dns/exceptions.h>
#include <dns/messagerenderer.h>
#include <dns/name.h>
#include <dns/question.h>
#include <dns/rrset.h>
#include <dns/rrttl.h>
#include <dns/message.h>

#include <xfr/xfrout_client.h>

#include <recurse/recursor.h>

using namespace std;

using namespace isc;
using namespace isc::cc;
using namespace isc::dns;
using namespace isc::dns::rdata;
using namespace isc::data;
using namespace isc::config;
using namespace isc::xfr;
using namespace asiolink;

class RecursorImpl {
private:
    // prohibit copy
    RecursorImpl(const RecursorImpl& source);
    RecursorImpl& operator=(const RecursorImpl& source);
public:
    RecursorImpl();
    bool processNormalQuery(const IOMessage& io_message, Message& message,
                            MessageRenderer& response_renderer);
    ModuleCCSession* config_session_;

    bool verbose_mode_;

    /// Currently non-configurable, but will be.
    static const uint16_t DEFAULT_LOCAL_UDPSIZE = 4096;
};

RecursorImpl::RecursorImpl() : config_session_(NULL), verbose_mode_(false) {}

// This is a derived class of \c DNSProvider, to serve as a
// callback in the asiolink module.  It calls
// Recursor::processMessage() on a single DNS message.
class MessageProcessor : public DNSProvider {
public:
    MessageProcessor(Recursor* srv) : server_(srv) {}
    virtual bool operator()(const IOMessage& io_message,
                            isc::dns::Message& dns_message,
                            isc::dns::MessageRenderer& renderer) const {
        return (server_->processMessage(io_message, dns_message, renderer));
    }
private:
    Recursor* server_;
};

// This is a derived class of \c CheckinProvider, to serve
// as a callback in the asiolink module.  It checks for queued
// configuration messages, and executes them if found.
class ConfigChecker : public CheckinProvider {
public:
    ConfigChecker(Recursor* srv) : server_(srv) {}
    virtual void operator()(void) const {
        if (server_->configSession()->hasQueuedMsgs()) {
            server_->configSession()->checkCommand();
        }
    }
private:
    Recursor* server_;
};

Recursor::Recursor() :
    impl_(new RecursorImpl()),
    checkin_provider_(new ConfigChecker(this)),
    dns_provider_(new MessageProcessor(this))
{}

Recursor::~Recursor() {
    delete impl_;
    delete checkin_provider_;
    delete dns_provider_;
}

namespace {
class QuestionInserter {
public:
    QuestionInserter(Message* message) : message_(message) {}
    void operator()(const QuestionPtr question) {
        message_->addQuestion(question);
    }
    Message* message_;
};

void
makeErrorMessage(Message& message, MessageRenderer& renderer,
                 const Rcode& rcode, const bool verbose_mode)
{
    // extract the parameters that should be kept.
    // XXX: with the current implementation, it's not easy to set EDNS0
    // depending on whether the query had it.  So we'll simply omit it.
    const qid_t qid = message.getQid();
    const bool rd = message.getHeaderFlag(MessageFlag::RD());
    const bool cd = message.getHeaderFlag(MessageFlag::CD());
    const Opcode& opcode = message.getOpcode();
    vector<QuestionPtr> questions;

    // If this is an error to a query or notify, we should also copy the
    // question section.
    if (opcode == Opcode::QUERY() || opcode == Opcode::NOTIFY()) {
        questions.assign(message.beginQuestion(), message.endQuestion());
    }

    message.clear(Message::RENDER);
    message.setQid(qid);
    message.setOpcode(opcode);
    message.setHeaderFlag(MessageFlag::QR());
    message.setUDPSize(RecursorImpl::DEFAULT_LOCAL_UDPSIZE);
    if (rd) {
        message.setHeaderFlag(MessageFlag::RD());
    }
    if (cd) {
        message.setHeaderFlag(MessageFlag::CD());
    }
    for_each(questions.begin(), questions.end(), QuestionInserter(&message));
    message.setRcode(rcode);
    message.toWire(renderer);

    if (verbose_mode) {
        cerr << "[b10-recurse] sending an error response (" <<
            renderer.getLength() << " bytes):\n" << message.toText() << endl;
    }
}
}

void
Recursor::setVerbose(const bool on) {
    impl_->verbose_mode_ = on;
}

bool
Recursor::getVerbose() const {
    return (impl_->verbose_mode_);
}

void
Recursor::setConfigSession(ModuleCCSession* config_session) {
    impl_->config_session_ = config_session;
}

ModuleCCSession*
Recursor::configSession() const {
    return (impl_->config_session_);
}

bool
Recursor::processMessage(const IOMessage& io_message, Message& message,
                        MessageRenderer& response_renderer)
{
    InputBuffer request_buffer(io_message.getData(), io_message.getDataSize());

    // First, check the header part.  If we fail even for the base header,
    // just drop the message.
    try {
        message.parseHeader(request_buffer);

        // Ignore all responses.
        if (message.getHeaderFlag(MessageFlag::QR())) {
            if (impl_->verbose_mode_) {
                cerr << "[b10-recurse] received unexpected response, ignoring"
                     << endl;
            }
            return (false);
        }
    } catch (const Exception& ex) {
        return (false);
    }

    // Parse the message.  On failure, return an appropriate error.
    try {
        message.fromWire(request_buffer);
    } catch (const DNSProtocolError& error) {
        if (impl_->verbose_mode_) {
            cerr << "[b10-recurse] returning " <<  error.getRcode().toText()
                 << ": " << error.what() << endl;
        }
        makeErrorMessage(message, response_renderer, error.getRcode(),
                         impl_->verbose_mode_);
        return (true);
    } catch (const Exception& ex) {
        if (impl_->verbose_mode_) {
            cerr << "[b10-recurse] returning SERVFAIL: " << ex.what() << endl;
        }
        makeErrorMessage(message, response_renderer, Rcode::SERVFAIL(),
                         impl_->verbose_mode_);
        return (true);
    } // other exceptions will be handled at a higher layer.

    if (impl_->verbose_mode_) {
        cerr << "[b10-recurse] received a message:\n"
             << message.toText() << endl;
    }

    // Perform further protocol-level validation.
    if (message.getOpcode() == Opcode::NOTIFY()) {
        makeErrorMessage(message, response_renderer, Rcode::NOTAUTH(),
                         impl_->verbose_mode_);
        return (true);
    } else if (message.getOpcode() != Opcode::QUERY()) {
        if (impl_->verbose_mode_) {
            cerr << "[b10-recurse] unsupported opcode" << endl;
        }
        makeErrorMessage(message, response_renderer, Rcode::NOTIMP(),
                         impl_->verbose_mode_);
        return (true);
    }

    if (message.getRRCount(Section::QUESTION()) != 1) {
        makeErrorMessage(message, response_renderer, Rcode::FORMERR(),
                         impl_->verbose_mode_);
        return (true);
    }

    ConstQuestionPtr question = *message.beginQuestion();
    const RRType &qtype = question->getType();
    if (qtype == RRType::AXFR()) {
        if (io_message.getSocket().getProtocol() == IPPROTO_UDP) {
            makeErrorMessage(message, response_renderer, Rcode::FORMERR(),
                             impl_->verbose_mode_);
        } else {
            makeErrorMessage(message, response_renderer, Rcode::NOTIMP(),
                             impl_->verbose_mode_);
        }
        return (true);
    } else if (qtype == RRType::IXFR()) {
        makeErrorMessage(message, response_renderer, Rcode::NOTIMP(),
                         impl_->verbose_mode_);
        return (true);
    } else {
        return (impl_->processNormalQuery(io_message, message,
                                          response_renderer));
    }
}

bool
RecursorImpl::processNormalQuery(const IOMessage& io_message, Message& message,
                                MessageRenderer& response_renderer)
{
    const bool dnssec_ok = message.isDNSSECSupported();
    const uint16_t remote_bufsize = message.getUDPSize();

    message.makeResponse();
    message.setRcode(Rcode::NOERROR());
    message.setDNSSECSupported(dnssec_ok);
    message.setUDPSize(RecursorImpl::DEFAULT_LOCAL_UDPSIZE);

    try {
        // HERE: initiate forward query, construct a reply
    } catch (const Exception& ex) {
        if (verbose_mode_) {
            cerr << "[b10-recurse] Internal error, returning SERVFAIL: " <<
                ex.what() << endl;
        }
        makeErrorMessage(message, response_renderer, Rcode::SERVFAIL(),
                         verbose_mode_);
        return (true);
    }

    const bool udp_buffer =
        (io_message.getSocket().getProtocol() == IPPROTO_UDP);
    response_renderer.setLengthLimit(udp_buffer ? remote_bufsize : 65535);
    message.toWire(response_renderer);
    if (verbose_mode_) {
        cerr << "[b10-recurse] sending a response ("
             << response_renderer.getLength()
             << " bytes):\n" << message.toText() << endl;
    }

    return (true);
}

ConstElementPtr
Recursor::updateConfig(ConstElementPtr new_config UNUSED_PARAM) {
    try {
        // We will do configuration updates here.  None are presently
        // defined, so we just return an empty answer.
        return (isc::config::createAnswer());
    } catch (const isc::Exception& error) {
        if (impl_->verbose_mode_) {
            cerr << "[b10-recurse] error: " << error.what() << endl;
        }
        return (isc::config::createAnswer(1, error.what()));
    }
}
