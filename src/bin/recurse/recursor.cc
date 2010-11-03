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
#include <asiolink/ioaddress.h>

#include <boost/foreach.hpp>

#include <config/ccsession.h>

#include <cc/data.h>

#include <exceptions/exceptions.h>

#include <dns/buffer.h>
#include <dns/exceptions.h>
#include <dns/name.h>
#include <dns/question.h>
#include <dns/rrset.h>
#include <dns/rrttl.h>
#include <dns/message.h>
#include <dns/messagerenderer.h>

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

typedef pair<string, uint16_t> addr_t;

class RecursorImpl {
private:
    // prohibit copy
    RecursorImpl(const RecursorImpl& source);
    RecursorImpl& operator=(const RecursorImpl& source);
public:
    RecursorImpl() :
        config_session_(NULL),
        verbose_mode_(false),
        rec_query_()
    {}

    ~RecursorImpl() {
        queryShutdown();
    }

    void querySetup(DNSService& dnss) {
        rec_query_ = new RecursiveQuery(dnss, upstream_);
    }

    void queryShutdown() {
        delete rec_query_;
        rec_query_ = NULL;
    }

    void setForwardAddresses(const vector<addr_t>& upstream,
        IOService* ios)
    {
        queryShutdown();
        upstream_ = upstream;
        if (ios) {
            if (upstream_.empty()) {
                cerr << "[b10-recurse] Asked to do full recursive," << endl <<
                    "but not implemented yet. I'll do nothing." << endl;
            } else {
                querySetup(*ios);
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
    bool verbose_mode_;
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
        message_->addRRset(section_, rrset, true);
    }
    MessagePtr message_;
    const Section& section_;
    bool sign_;
};

void
makeErrorMessage(MessagePtr message, OutputBufferPtr buffer,
                 const Rcode& rcode, const bool verbose_mode)
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

    if (verbose_mode) {
        cerr << "[b10-recurse] sending an error response (" <<
            renderer.getLength() << " bytes):\n" << message->toText() << endl;
    }
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

        if (server_->getVerbose()) {
            cerr << "[b10-recurse] sending a response ("
                 << renderer.getLength() << " bytes):\n"
                 << message->toText() << endl;
        }
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
}

void
Recursor::setDNSService(asiolink::DNSService& dnss) {
    impl_->queryShutdown();
    impl_->querySetup(dnss);
    dnss_ = &dnss;
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
Recursor::getConfigSession() const {
    return (impl_->config_session_);
}

void
Recursor::processMessage(const IOMessage& io_message, MessagePtr message,
                        OutputBufferPtr buffer, DNSServer* server)
{
    InputBuffer request_buffer(io_message.getData(), io_message.getDataSize());
    // First, check the header part.  If we fail even for the base header,
    // just drop the message.
    try {
        message->parseHeader(request_buffer);

        // Ignore all responses.
        if (message->getHeaderFlag(MessageFlag::QR())) {
            if (impl_->verbose_mode_) {
                cerr << "[b10-recurse] received unexpected response, ignoring"
                     << endl;
            }
            server->resume(false);
            return;
        }
    } catch (const Exception& ex) {
        if (impl_->verbose_mode_) {
            cerr << "[b10-recurse] DNS packet exception: " << ex.what() << endl;
        }
        server->resume(false);
        return;
    }

    // Parse the message.  On failure, return an appropriate error.
    try {
        message->fromWire(request_buffer);
    } catch (const DNSProtocolError& error) {
        if (impl_->verbose_mode_) {
            cerr << "[b10-recurse] returning " <<  error.getRcode().toText()
                 << ": " << error.what() << endl;
        }
        makeErrorMessage(message, buffer, error.getRcode(),
                         impl_->verbose_mode_);
        server->resume(true);
        return;
    } catch (const Exception& ex) {
        if (impl_->verbose_mode_) {
            cerr << "[b10-recurse] returning SERVFAIL: " << ex.what() << endl;
        }
        makeErrorMessage(message, buffer, Rcode::SERVFAIL(),
                         impl_->verbose_mode_);
        server->resume(true);
        return;
    } // other exceptions will be handled at a higher layer.

    if (impl_->verbose_mode_) {
        cerr << "[b10-recurse] received a message:\n"
             << message->toText() << endl;
    }

    // Perform further protocol-level validation.
    bool sendAnswer = true;
    if (message->getOpcode() == Opcode::NOTIFY()) {
        makeErrorMessage(message, buffer, Rcode::NOTAUTH(),
                         impl_->verbose_mode_);
    } else if (message->getOpcode() != Opcode::QUERY()) {
        if (impl_->verbose_mode_) {
            cerr << "[b10-recurse] unsupported opcode" << endl;
        }
        makeErrorMessage(message, buffer, Rcode::NOTIMP(),
                         impl_->verbose_mode_);
    } else if (message->getRRCount(Section::QUESTION()) != 1) {
        makeErrorMessage(message, buffer, Rcode::FORMERR(),
                         impl_->verbose_mode_);
    } else {
        ConstQuestionPtr question = *message->beginQuestion();
        const RRType &qtype = question->getType();
        if (qtype == RRType::AXFR()) {
            if (io_message.getSocket().getProtocol() == IPPROTO_UDP) {
                makeErrorMessage(message, buffer, Rcode::FORMERR(),
                                 impl_->verbose_mode_);
            } else {
                makeErrorMessage(message, buffer, Rcode::NOTIMP(),
                                 impl_->verbose_mode_);
            }
        } else if (qtype == RRType::IXFR()) {
            makeErrorMessage(message, buffer, Rcode::NOTIMP(),
                         impl_->verbose_mode_);
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
    const bool dnssec_ok = message->isDNSSECSupported();

    message->makeResponse();
    message->setHeaderFlag(MessageFlag::RA());
    message->setRcode(Rcode::NOERROR());
    message->setDNSSECSupported(dnssec_ok);
    message->setUDPSize(RecursorImpl::DEFAULT_LOCAL_UDPSIZE);
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
    if (impl_->verbose_mode_) {
        cout << "[b10-recurse] Update with config: " << config->str() << endl;
    }
    try {
        // Parse forward_addresses
        // FIXME Once the config parser is fixed, remove the slashes. They
        // appear only on the default/startup value and shouldn't be here.
        // See ticket #384
        ConstElementPtr forwardAddressesE(config->get("forward_addresses/"));
        vector<addr_t> forwardAddresses(parseAddresses(forwardAddressesE));
        ConstElementPtr listenAddressesE(config->get("listen_on/"));
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
        if (impl_->verbose_mode_) {
            cerr << "[b10-recurse] error: " << error.what() << endl;
        }
        return (isc::config::createAnswer(1, error.what()));
    }
}

void
Recursor::setForwardAddresses(const vector<addr_t>& addresses)
{
    impl_->setForwardAddresses(addresses, io_);
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
setAddresses(IOService *service, const vector<addr_t>& addresses) {
    service->clearServers();
    BOOST_FOREACH(const addr_t &address, addresses) {
        service->addServer(address.second, address.first);
    }
}

}

void
Recursor::setListenAddresses(const vector<addr_t>& addresses) {
    try {
        setAddresses(io_, addresses);
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
            setAddresses(io_, impl_->listen_);
        }
        catch (const exception& e2) {
            cerr << "[b10-recurse] Unable to recover from error: " << e.what()
                << endl << "Rollback failed with: " << e2.what() << endl;
            abort();
        }
        throw e; // Let it fly a little bit further
    }
}

vector<addr_t>
Recursor::getListenAddresses() const {
    return (impl_->listen_);
}
