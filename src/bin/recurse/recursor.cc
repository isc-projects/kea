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
#include <vector>

#include <asiolink/asiolink.h>

#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>

#include <config/ccsession.h>

#include <exceptions/exceptions.h>

#include <dns/buffer.h>
#include <dns/exceptions.h>
#include <dns/name.h>
#include <dns/question.h>
#include <dns/rrset.h>
#include <dns/rrttl.h>
#include <dns/message.h>
#include <dns/messagerenderer.h>

#include <log/dummylog.h>

#include <recurse/recursor.h>

using namespace std;

using namespace isc;
using namespace isc::dns;
using namespace isc::data;
using namespace isc::config;
using isc::log::dlog;
using namespace asiolink;

class RecursorImpl {
private:
    // prohibit copy
    RecursorImpl(const RecursorImpl& source);
    RecursorImpl& operator=(const RecursorImpl& source);
public:
    RecursorImpl(const char& forward) :
        config_session_(NULL),
        forward_(forward), rec_query_()
    {}

    ~RecursorImpl() {
        queryShutdown();
    }

    void querySetup(DNSService& dnss) {
        dlog("Query setup");
        rec_query_ = new RecursiveQuery(dnss, forward_);
    }

    void queryShutdown() {
        dlog("Query shutdown");
        if (rec_query_) {
            delete rec_query_;
        }
    }

    void processNormalQuery(const Question& question, MessagePtr message,
                            OutputBufferPtr buffer,
                            DNSServer* server);

    /// Currently non-configurable, but will be.
    static const uint16_t DEFAULT_LOCAL_UDPSIZE = 4096;

    /// These members are public because Recursor accesses them directly.
    ModuleCCSession* config_session_;

private:
    /// Address of the forward nameserver
    const char& forward_;

    /// Object to handle upstream queries
    RecursiveQuery* rec_query_;
};

class QuestionInserter {
public:
    QuestionInserter(MessagePtr message) : message_(message) {}
    void operator()(const QuestionPtr question) {
        dlog(string("Adding question ") + question->getName().toText() +
            " to message");
        message_->addQuestion(question);
    }
    MessagePtr message_;
};

class SectionInserter {
public:
    SectionInserter(MessagePtr message, const Section& sect, bool sign) :
        message_(message), section_(sect), sign_(sign)
    {}
    void operator()(const RRsetPtr rrset) {
        dlog("Adding RRSet to message");
        message_->addRRset(section_, rrset, true);
    }
    MessagePtr message_;
    const Section& section_;
    bool sign_;
};

void
makeErrorMessage(MessagePtr message, OutputBufferPtr buffer,
                 const Rcode& rcode)
{
    // extract the parameters that should be kept.
    // XXX: with the current implementation, it's not easy to set EDNS0
    // depending on whether the query had it.  So we'll simply omit it.
    const qid_t qid = message->getQid();
    const bool rd = message->getHeaderFlag(MessageFlag::RD());
    const bool cd = message->getHeaderFlag(MessageFlag::CD());
    const Opcode& opcode = message->getOpcode();
    vector<QuestionPtr> questions;

    // If this is an error to a query or notify, we should also copy the
    // question section.
    if (opcode == Opcode::QUERY() || opcode == Opcode::NOTIFY()) {
        questions.assign(message->beginQuestion(), message->endQuestion());
    }

    message->clear(Message::RENDER);
    message->setQid(qid);
    message->setOpcode(opcode);
    message->setHeaderFlag(MessageFlag::QR());
    message->setUDPSize(RecursorImpl::DEFAULT_LOCAL_UDPSIZE);
    if (rd) {
        message->setHeaderFlag(MessageFlag::RD());
    }
    if (cd) {
        message->setHeaderFlag(MessageFlag::CD());
    }
    for_each(questions.begin(), questions.end(), QuestionInserter(message));
    message->setRcode(rcode);
    MessageRenderer renderer(*buffer);
    message->toWire(renderer);

    dlog(string("Sending an error response (") +
        boost::lexical_cast<string>(renderer.getLength()) + " bytes):\n" +
        message->toText());
}

// This is a derived class of \c DNSLookup, to serve as a
// callback in the asiolink module.  It calls
// Recursor::processMessage() on a single DNS message.
class MessageLookup : public DNSLookup {
public:
    MessageLookup(Recursor* srv) : server_(srv) {}

    // \brief Handle the DNS Lookup
    virtual void operator()(const IOMessage& io_message, MessagePtr message,
                            OutputBufferPtr buffer, DNSServer* server) const
    {
        server_->processMessage(io_message, message, buffer, server);
    }
private:
    Recursor* server_;
};

// This is a derived class of \c DNSAnswer, to serve as a
// callback in the asiolink module.  It takes a completed
// set of answer data from the DNS lookup and assembles it
// into a wire-format response.
class MessageAnswer : public DNSAnswer {
public:
    MessageAnswer(Recursor* srv) : server_(srv) {}
    virtual void operator()(const IOMessage& io_message,
                            MessagePtr message,
                            OutputBufferPtr buffer) const
    {
        const qid_t qid = message->getQid();
        const bool rd = message->getHeaderFlag(MessageFlag::RD());
        const bool cd = message->getHeaderFlag(MessageFlag::CD());
        const Opcode& opcode = message->getOpcode();
        const Rcode& rcode = message->getRcode();
        vector<QuestionPtr> questions;
        questions.assign(message->beginQuestion(), message->endQuestion());

        message->clear(Message::RENDER);
        message->setQid(qid);
        message->setOpcode(opcode);
        message->setRcode(rcode);
        message->setUDPSize(RecursorImpl::DEFAULT_LOCAL_UDPSIZE);

        message->setHeaderFlag(MessageFlag::QR());
        message->setHeaderFlag(MessageFlag::RA());
        if (rd) {
            message->setHeaderFlag(MessageFlag::RD());
        }
        if (cd) {
            message->setHeaderFlag(MessageFlag::CD());
        }


        // Copy the question section.
        for_each(questions.begin(), questions.end(), QuestionInserter(message));

        // If the buffer already has an answer in it, copy RRsets from
        // that into the new message, then clear the buffer and render
        // the new message into it.
        if (buffer->getLength() != 0) {
            try {
                Message incoming(Message::PARSE);
                InputBuffer ibuf(buffer->getData(), buffer->getLength());
                incoming.fromWire(ibuf);
                for_each(incoming.beginSection(Section::ANSWER()), 
                         incoming.endSection(Section::ANSWER()),
                         SectionInserter(message, Section::ANSWER(), true));
                for_each(incoming.beginSection(Section::ADDITIONAL()), 
                         incoming.endSection(Section::ADDITIONAL()),
                         SectionInserter(message, Section::ADDITIONAL(), true));
                for_each(incoming.beginSection(Section::AUTHORITY()), 
                         incoming.endSection(Section::AUTHORITY()),
                         SectionInserter(message, Section::AUTHORITY(), true));
            } catch (const Exception& ex) {
                // Incoming message couldn't be read, we just SERVFAIL
                message->setRcode(Rcode::SERVFAIL());
            }

        }

        // Now we can clear the buffer and render the new message into it
        buffer->clear();
        MessageRenderer renderer(*buffer);

        if (io_message.getSocket().getProtocol() == IPPROTO_UDP) {
            renderer.setLengthLimit(message->getUDPSize());
        } else {
            renderer.setLengthLimit(65535);
        }

        message->toWire(renderer);

        dlog(string("sending a response (") +
            boost::lexical_cast<string>(renderer.getLength()) + "bytes): \n" +
            message->toText());
    }

private:
    Recursor* server_;
};

// This is a derived class of \c SimpleCallback, to serve
// as a callback in the asiolink module.  It checks for queued
// configuration messages, and executes them if found.
class ConfigCheck : public SimpleCallback {
public:
    ConfigCheck(Recursor* srv) : server_(srv) {}
    virtual void operator()(const IOMessage& io_message UNUSED_PARAM) const {
        if (server_->getConfigSession()->hasQueuedMsgs()) {
            server_->getConfigSession()->checkCommand();
        }
    }
private:
    Recursor* server_;
};

Recursor::Recursor(const char& forward) :
    impl_(new RecursorImpl(forward)),
    checkin_(new ConfigCheck(this)),
    dns_lookup_(new MessageLookup(this)),
    dns_answer_(new MessageAnswer(this))
{}

Recursor::~Recursor() {
    delete impl_;
    delete checkin_;
    delete dns_lookup_;
    delete dns_answer_;
    dlog("Deleting the Recursor");
}

void
Recursor::setDNSService(asiolink::DNSService& dnss) {
    impl_->queryShutdown();
    impl_->querySetup(dnss);
    dnss_ = &dnss;
}

void
Recursor::setConfigSession(ModuleCCSession* config_session) {
    impl_->config_session_ = config_session;
}

ModuleCCSession*
Recursor::getConfigSession() const {
    return (impl_->config_session_);
}

void
Recursor::processMessage(const IOMessage& io_message, MessagePtr message,
                        OutputBufferPtr buffer, DNSServer* server)
{
    dlog("Got a DNS message");
    InputBuffer request_buffer(io_message.getData(), io_message.getDataSize());
    // First, check the header part.  If we fail even for the base header,
    // just drop the message.
    try {
        message->parseHeader(request_buffer);

        // Ignore all responses.
        if (message->getHeaderFlag(MessageFlag::QR())) {
            dlog("Received unexpected response, ignoring");
            server->resume(false);
            return;
        }
    } catch (const Exception& ex) {
        dlog(string("DNS packet exception: ") + ex.what());
        server->resume(false);
        return;
    }

    // Parse the message.  On failure, return an appropriate error.
    try {
        message->fromWire(request_buffer);
    } catch (const DNSProtocolError& error) {
        dlog(string("returning ") + error.getRcode().toText() + ": " + 
            error.what());
        makeErrorMessage(message, buffer, error.getRcode());
        server->resume(true);
        return;
    } catch (const Exception& ex) {
        dlog(string("returning SERVFAIL: ") + ex.what());
        makeErrorMessage(message, buffer, Rcode::SERVFAIL());
        server->resume(true);
        return;
    } // other exceptions will be handled at a higher layer.

    dlog("received a message:\n" + message->toText());

    // Perform further protocol-level validation.
    bool sendAnswer = true;
    if (message->getOpcode() == Opcode::NOTIFY()) {
        makeErrorMessage(message, buffer, Rcode::NOTAUTH());
    } else if (message->getOpcode() != Opcode::QUERY()) {
        dlog("unsupported opcode");
        makeErrorMessage(message, buffer, Rcode::NOTIMP());
    } else if (message->getRRCount(Section::QUESTION()) != 1) {
        makeErrorMessage(message, buffer, Rcode::FORMERR());
    } else {
        ConstQuestionPtr question = *message->beginQuestion();
        const RRType &qtype = question->getType();
        if (qtype == RRType::AXFR()) {
            if (io_message.getSocket().getProtocol() == IPPROTO_UDP) {
                makeErrorMessage(message, buffer, Rcode::FORMERR());
            } else {
                makeErrorMessage(message, buffer, Rcode::NOTIMP());
            }
        } else if (qtype == RRType::IXFR()) {
            makeErrorMessage(message, buffer, Rcode::NOTIMP());
        } else {
            // The RecursiveQuery object will post the "resume" event to the
            // DNSServer when an answer arrives, so we don't have to do it now.
            sendAnswer = false;
            impl_->processNormalQuery(*question, message, buffer, server);
        }
    }

    if (sendAnswer) {
        server->resume(true);
    }
}

void
RecursorImpl::processNormalQuery(const Question& question, MessagePtr message,
                                 OutputBufferPtr buffer, DNSServer* server)
{
    dlog("Processing normal query");
    const bool dnssec_ok = message->isDNSSECSupported();

    message->makeResponse();
    message->setHeaderFlag(MessageFlag::RA());
    message->setRcode(Rcode::NOERROR());
    message->setDNSSECSupported(dnssec_ok);
    message->setUDPSize(RecursorImpl::DEFAULT_LOCAL_UDPSIZE);
    rec_query_->sendQuery(question, buffer, server);
}

ConstElementPtr
Recursor::updateConfig(ConstElementPtr new_config) {
    dlog("New config comes: " + new_config->toWire());
    try {
        // We will do configuration updates here.  None are presently
        // defined, so we just return an empty answer.
        return (isc::config::createAnswer());
    } catch (const isc::Exception& error) {
        dlog(string("error in config: ") + error.what());
        return (isc::config::createAnswer(1, error.what()));
    }
}
