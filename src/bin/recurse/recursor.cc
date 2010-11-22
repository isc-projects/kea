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
#include <asiolink/ioaddress.h>

#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>

#include <config/ccsession.h>

#include <exceptions/exceptions.h>

#include <dns/opcode.h>
#include <dns/rcode.h>
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

typedef pair<string, uint16_t> addr_t;

class RecursorImpl {
private:
    // prohibit copy
    RecursorImpl(const RecursorImpl& source);
    RecursorImpl& operator=(const RecursorImpl& source);
public:
    RecursorImpl() :
        config_session_(NULL),
        rec_query_()
    {}

    ~RecursorImpl() {
        queryShutdown();
    }

    void querySetup(DNSService& dnss) {
        dlog("Query setup");
        rec_query_ = new RecursiveQuery(dnss, upstream_);
    }

    void queryShutdown() {
        dlog("Query shutdown");
        delete rec_query_;
        rec_query_ = NULL;
    }

    void setForwardAddresses(const vector<addr_t>& upstream,
        DNSService *dnss)
    {
        queryShutdown();
        upstream_ = upstream;
        if (dnss) {
            if (upstream_.empty()) {
                dlog("Asked to do full recursive, but not implemented yet. "
                    "I'll do nothing.");
            } else {
                dlog("Setting forward addresses:");
                BOOST_FOREACH(const addr_t& address, upstream) {
                    dlog(" " + address.first + ":" +
                        boost::lexical_cast<string>(address.second));
                }
                querySetup(*dnss);
            }
        }
    }

    void processNormalQuery(const Question& question, MessagePtr message,
                            OutputBufferPtr buffer,
                            DNSServer* server);

    /// Currently non-configurable, but will be.
    static const uint16_t DEFAULT_LOCAL_UDPSIZE = 4096;

    /// These members are public because Recursor accesses them directly.
    ModuleCCSession* config_session_;
    /// Addresses of the forward nameserver
    vector<addr_t> upstream_;
    /// Addresses we listen on
    vector<addr_t> listen_;

private:

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
    SectionInserter(MessagePtr message, const Message::Section sect,
        bool sign) :
        message_(message), section_(sect), sign_(sign)
    {}
    void operator()(const RRsetPtr rrset) {
        dlog("Adding RRSet to message section " +
            boost::lexical_cast<string>(section_));
        message_->addRRset(section_, rrset, true);
    }
    MessagePtr message_;
    const Message::Section section_;
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
    const bool rd = message->getHeaderFlag(Message::HEADERFLAG_RD);
    const bool cd = message->getHeaderFlag(Message::HEADERFLAG_CD);
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
    message->setHeaderFlag(Message::HEADERFLAG_QR);
    if (rd) {
        message->setHeaderFlag(Message::HEADERFLAG_RD);
    }
    if (cd) {
        message->setHeaderFlag(Message::HEADERFLAG_CD);
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
        const bool rd = message->getHeaderFlag(Message::HEADERFLAG_RD);
        const bool cd = message->getHeaderFlag(Message::HEADERFLAG_CD);
        const Opcode& opcode = message->getOpcode();
        const Rcode& rcode = message->getRcode();
        vector<QuestionPtr> questions;
        questions.assign(message->beginQuestion(), message->endQuestion());

        message->clear(Message::RENDER);
        message->setQid(qid);
        message->setOpcode(opcode);
        message->setRcode(rcode);

        message->setHeaderFlag(Message::HEADERFLAG_QR);
        message->setHeaderFlag(Message::HEADERFLAG_RA);
        if (rd) {
            message->setHeaderFlag(Message::HEADERFLAG_RD);
        }
        if (cd) {
            message->setHeaderFlag(Message::HEADERFLAG_CD);
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
                for_each(incoming.beginSection(Message::SECTION_ANSWER),
                         incoming.endSection(Message::SECTION_ANSWER),
                         SectionInserter(message, Message::SECTION_ANSWER,
                         true));
                for_each(incoming.beginSection(Message::SECTION_ADDITIONAL),
                         incoming.endSection(Message::SECTION_ADDITIONAL),
                         SectionInserter(message, Message::SECTION_ADDITIONAL,
                         true));
                for_each(incoming.beginSection(Message::SECTION_AUTHORITY),
                         incoming.endSection(Message::SECTION_ADDITIONAL),
                         SectionInserter(message, Message::SECTION_AUTHORITY,
                         true));
            } catch (const Exception& ex) {
                // Incoming message couldn't be read, we just SERVFAIL
                message->setRcode(Rcode::SERVFAIL());
            }

        }

        // Now we can clear the buffer and render the new message into it
        buffer->clear();
        MessageRenderer renderer(*buffer);

        if (io_message.getSocket().getProtocol() == IPPROTO_UDP) {
            ConstEDNSPtr edns(message->getEDNS());
            renderer.setLengthLimit(edns ? edns->getUDPSize() :
                Message::DEFAULT_MAX_UDPSIZE);
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
    virtual void operator()(const IOMessage&) const {
        if (server_->getConfigSession()->hasQueuedMsgs()) {
            server_->getConfigSession()->checkCommand();
        }
    }
private:
    Recursor* server_;
};

Recursor::Recursor() :
    impl_(new RecursorImpl()),
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
        if (message->getHeaderFlag(Message::HEADERFLAG_QR)) {
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
        dlog("Notify arrived, but we are not authoritative");
    } else if (message->getOpcode() != Opcode::QUERY()) {
        dlog("Unsupported opcode (got: " + message->getOpcode().toText() +
            ", expected: " + Opcode::QUERY().toText());
        makeErrorMessage(message, buffer, Rcode::NOTIMP());
    } else if (message->getRRCount(Message::SECTION_QUESTION) != 1) {
        dlog("The query contained " +
            boost::lexical_cast<string>(message->getRRCount(
            Message::SECTION_QUESTION) + " questions, exactly one expected"));
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
    ConstEDNSPtr edns(message->getEDNS());
    const bool dnssec_ok = edns && edns->getDNSSECAwareness();

    message->makeResponse();
    message->setHeaderFlag(Message::HEADERFLAG_RA);
    message->setRcode(Rcode::NOERROR());
    if (edns) {
        EDNSPtr edns_response(new EDNS());
        edns_response->setDNSSECAwareness(dnssec_ok);
        edns_response->setUDPSize(RecursorImpl::DEFAULT_LOCAL_UDPSIZE);
        message->setEDNS(edns_response);
    }
    rec_query_->sendQuery(question, buffer, server);
}

namespace {

vector<addr_t>
parseAddresses(ConstElementPtr addresses) {
    vector<addr_t> result;
    if (addresses) {
        if (addresses->getType() == Element::list) {
            for (size_t i(0); i < addresses->size(); ++ i) {
                ConstElementPtr addrPair(addresses->get(i));
                ConstElementPtr addr(addrPair->get("address"));
                ConstElementPtr port(addrPair->get("port"));
                if (!addr || ! port) {
                    isc_throw(BadValue, "Address must contain both the IP"
                        "address and port");
                }
                try {
                    IOAddress(addr->stringValue());
                    if (port->intValue() < 0 ||
                        port->intValue() > 0xffff) {
                        isc_throw(BadValue, "Bad port value (" <<
                            port->intValue() << ")");
                    }
                    result.push_back(addr_t(addr->stringValue(),
                        port->intValue()));
                }
                catch (const TypeError &e) { // Better error message
                    isc_throw(TypeError,
                        "Address must be a string and port an integer");
                }
            }
        } else if (addresses->getType() != Element::null) {
            isc_throw(TypeError,
                "forward_addresses config element must be a list");
        }
    }
    return (result);
}

}

ConstElementPtr
Recursor::updateConfig(ConstElementPtr config) {
    dlog("New config comes: " + config->toWire());

    try {
        // Parse forward_addresses
        ConstElementPtr forwardAddressesE(config->get("forward_addresses"));
        vector<addr_t> forwardAddresses(parseAddresses(forwardAddressesE));
        ConstElementPtr listenAddressesE(config->get("listen_on"));
        vector<addr_t> listenAddresses(parseAddresses(listenAddressesE));
        // Everything OK, so commit the changes
        // listenAddresses can fail to bind, so try them first
        if (listenAddressesE) {
            setListenAddresses(listenAddresses);
        }
        if (forwardAddressesE) {
            setForwardAddresses(forwardAddresses);
        }
        return (isc::config::createAnswer());
    } catch (const isc::Exception& error) {
        dlog(string("error in config: ") + error.what());
        return (isc::config::createAnswer(1, error.what()));
    }
}

void
Recursor::setForwardAddresses(const vector<addr_t>& addresses)
{
    impl_->setForwardAddresses(addresses, dnss_);
}

bool
Recursor::isForwarding() const {
    return (!impl_->upstream_.empty());
}

vector<addr_t>
Recursor::getForwardAddresses() const {
    return (impl_->upstream_);
}

namespace {

void
setAddresses(DNSService *service, const vector<addr_t>& addresses) {
    service->clearServers();
    BOOST_FOREACH(const addr_t &address, addresses) {
        service->addServer(address.second, address.first);
    }
}

}

void
Recursor::setListenAddresses(const vector<addr_t>& addresses) {
    try {
        dlog("Setting listen addresses:");
        BOOST_FOREACH(const addr_t& addr, addresses) {
            dlog(" " + addr.first + boost::lexical_cast<string>(addr.second));
        }
        setAddresses(dnss_, addresses);
        impl_->listen_ = addresses;
    }
    catch (const exception& e) {
        /*
         * We couldn't set it. So return it back. If that fails as well,
         * we have a problem.
         *
         * If that fails, bad luck, but we are useless anyway, so just die
         * and let boss start us again.
         */
        try {
            setAddresses(dnss_, impl_->listen_);
        }
        catch (const exception& e2) {
            dlog(string("Unable to recover from error: ") + e.what() +
                " Rollback failed with: " + e2.what());
            abort();
        }
        throw e; // Let it fly a little bit further
    }
}

vector<addr_t>
Recursor::getListenAddresses() const {
    return (impl_->listen_);
}
