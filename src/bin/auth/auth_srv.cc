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
#include <dns/edns.h>
#include <dns/exceptions.h>
#include <dns/messagerenderer.h>
#include <dns/name.h>
#include <dns/question.h>
#include <dns/opcode.h>
#include <dns/rcode.h>
#include <dns/rrset.h>
#include <dns/rrttl.h>
#include <dns/message.h>

#include <datasrc/query.h>
#include <datasrc/data_source.h>
#include <datasrc/static_datasrc.h>
#include <datasrc/sqlite3_datasrc.h>

#include <xfr/xfrout_client.h>

#include <auth/common.h>
#include <auth/auth_srv.h>

using namespace std;

using namespace isc;
using namespace isc::cc;
using namespace isc::datasrc;
using namespace isc::dns;
using namespace isc::dns::rdata;
using namespace isc::data;
using namespace isc::config;
using namespace isc::xfr;
using namespace asiolink;

class AuthSrvImpl {
private:
    // prohibit copy
    AuthSrvImpl(const AuthSrvImpl& source);
    AuthSrvImpl& operator=(const AuthSrvImpl& source);
public:
    AuthSrvImpl(const bool use_cache, AbstractXfroutClient& xfrout_client);
    ~AuthSrvImpl();
    isc::data::ConstElementPtr setDbFile(isc::data::ConstElementPtr config);

    bool processNormalQuery(const IOMessage& io_message, MessagePtr message,
                            OutputBufferPtr buffer);
    bool processAxfrQuery(const IOMessage& io_message, MessagePtr message,
                          OutputBufferPtr buffer);
    bool processNotify(const IOMessage& io_message, MessagePtr message,
                       OutputBufferPtr buffer);

    /// Currently non-configurable, but will be.
    static const uint16_t DEFAULT_LOCAL_UDPSIZE = 4096;

    /// These members are public because AuthSrv accesses them directly.
    ModuleCCSession* config_session_;
    bool verbose_mode_;
    AbstractSession* xfrin_session_;

    /// Hot spot cache
    isc::datasrc::HotCache cache_;
private:
    std::string db_file_;

    MetaDataSrc data_sources_;
    /// We keep a pointer to the currently running sqlite datasource
    /// so that we can specifically remove that one should the database
    /// file change
    ConstDataSrcPtr cur_datasrc_;

    bool xfrout_connected_;
    AbstractXfroutClient& xfrout_client_;
};

AuthSrvImpl::AuthSrvImpl(const bool use_cache,
                         AbstractXfroutClient& xfrout_client) :
    config_session_(NULL), verbose_mode_(false),
    xfrin_session_(NULL),
    xfrout_connected_(false),
    xfrout_client_(xfrout_client)
{
    // cur_datasrc_ is automatically initialized by the default constructor,
    // effectively being an empty (sqlite) data source.  once ccsession is up
    // the datasource will be set by the configuration setting

    // add static data source
    data_sources_.addDataSrc(ConstDataSrcPtr(new StaticDataSrc));

    // enable or disable the cache
    cache_.setEnabled(use_cache);
}

AuthSrvImpl::~AuthSrvImpl() {
    if (xfrout_connected_) {
        xfrout_client_.disconnect();
        xfrout_connected_ = false;
    }
}

// This is a derived class of \c DNSLookup, to serve as a
// callback in the asiolink module.  It calls
// AuthSrv::processMessage() on a single DNS message.
class MessageLookup : public DNSLookup {
public:
    MessageLookup(AuthSrv* srv) : server_(srv) {}
    virtual void operator()(const IOMessage& io_message, MessagePtr message,
                            OutputBufferPtr buffer, DNSServer* server) const
    {
        server_->processMessage(io_message, message, buffer, server);
    }
private:
    AuthSrv* server_;
};

// This is a derived class of \c DNSAnswer, to serve as a
// callback in the asiolink module.  It takes a completed
// set of answer data from the DNS lookup and assembles it
// into a wire-format response.
class MessageAnswer : public DNSAnswer {
public:
    MessageAnswer(AuthSrv* srv) : server_(srv) {}
    virtual void operator()(const IOMessage& io_message, MessagePtr message,
                            OutputBufferPtr buffer) const
    {
        MessageRenderer renderer(*buffer);
        if (io_message.getSocket().getProtocol() == IPPROTO_UDP) {
            ConstEDNSPtr edns(message->getEDNS());
            renderer.setLengthLimit(edns ? edns->getUDPSize() :
                Message::DEFAULT_MAX_UDPSIZE);
        } else {
            renderer.setLengthLimit(65535);
        }
        message->toWire(renderer);
        if (server_->getVerbose()) {
            cerr << "[b10-auth] sending a response (" << renderer.getLength()
                 << " bytes):\n" << message->toText() << endl;
        }
    }

private:
    AuthSrv* server_;
};

// This is a derived class of \c SimpleCallback, to serve
// as a callback in the asiolink module.  It checks for queued
// configuration messages, and executes them if found.
class ConfigChecker : public SimpleCallback {
public:
    ConfigChecker(AuthSrv* srv) : server_(srv) {}
    virtual void operator()(const IOMessage&) const {
        if (server_->getConfigSession()->hasQueuedMsgs()) {
            server_->getConfigSession()->checkCommand();
        }
    }
private:
    AuthSrv* server_;
};

AuthSrv::AuthSrv(const bool use_cache, AbstractXfroutClient& xfrout_client) :
    impl_(new AuthSrvImpl(use_cache, xfrout_client)),
    checkin_(new ConfigChecker(this)),
    dns_lookup_(new MessageLookup(this)),
    dns_answer_(new MessageAnswer(this))
{}

AuthSrv::~AuthSrv() {
    delete impl_;
    delete checkin_;
    delete dns_lookup_;
    delete dns_answer_;
}

namespace {
class QuestionInserter {
public:
    QuestionInserter(MessagePtr message) : message_(message) {}
    void operator()(const QuestionPtr question) {
        message_->addQuestion(question);
    }
    MessagePtr message_;
};

void
makeErrorMessage(MessagePtr message, OutputBufferPtr buffer,
                 const Rcode& rcode, const bool verbose_mode)
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

    if (verbose_mode) {
        cerr << "[b10-auth] sending an error response (" <<
            renderer.getLength() << " bytes):\n" << message->toText() << endl;
    }
}
}

void
AuthSrv::setVerbose(const bool on) {
    impl_->verbose_mode_ = on;
}

bool
AuthSrv::getVerbose() const {
    return (impl_->verbose_mode_);
}

void
AuthSrv::setCacheSlots(const size_t slots) {
    impl_->cache_.setSlots(slots);
}

size_t
AuthSrv::getCacheSlots() const {
    return (impl_->cache_.getSlots());
}

void
AuthSrv::setXfrinSession(AbstractSession* xfrin_session) {
    impl_->xfrin_session_ = xfrin_session;
}

void
AuthSrv::setConfigSession(ModuleCCSession* config_session) {
    impl_->config_session_ = config_session;
}

ModuleCCSession*
AuthSrv::getConfigSession() const {
    return (impl_->config_session_);
}

void
AuthSrv::processMessage(const IOMessage& io_message, MessagePtr message,
                        OutputBufferPtr buffer, DNSServer* server)
{
    InputBuffer request_buffer(io_message.getData(), io_message.getDataSize());

    // First, check the header part.  If we fail even for the base header,
    // just drop the message.
    try {
        message->parseHeader(request_buffer);

        // Ignore all responses.
        if (message->getHeaderFlag(Message::HEADERFLAG_QR)) {
            if (impl_->verbose_mode_) {
                cerr << "[b10-auth] received unexpected response, ignoring"
                     << endl;
            }
            server->resume(false);
            return;
        }
    } catch (const Exception& ex) {
        if (impl_->verbose_mode_) {
            cerr << "[b10-auth] DNS packet exception: " << ex.what() << endl;
        }
        server->resume(false);
        return;
    }

    try {
        // Parse the message.
        message->fromWire(request_buffer);
    } catch (const DNSProtocolError& error) {
        if (impl_->verbose_mode_) {
            cerr << "[b10-auth] returning " <<  error.getRcode().toText()
                 << ": " << error.what() << endl;
        }
        makeErrorMessage(message, buffer, error.getRcode(),
                         impl_->verbose_mode_);
        server->resume(true);
        return;
    } catch (const Exception& ex) {
        if (impl_->verbose_mode_) {
            cerr << "[b10-auth] returning SERVFAIL: " << ex.what() << endl;
        }
        makeErrorMessage(message, buffer, Rcode::SERVFAIL(),
                         impl_->verbose_mode_);
        server->resume(true);
        return;
    } // other exceptions will be handled at a higher layer.

    if (impl_->verbose_mode_) {
        cerr << "[b10-auth] received a message:\n" << message->toText() << endl;
    }

    // Perform further protocol-level validation.

    bool sendAnswer = true;
    if (message->getOpcode() == Opcode::NOTIFY()) {
        sendAnswer = impl_->processNotify(io_message, message, buffer);
    } else if (message->getOpcode() != Opcode::QUERY()) {
        if (impl_->verbose_mode_) {
            cerr << "[b10-auth] unsupported opcode" << endl;
        }
        makeErrorMessage(message, buffer, Rcode::NOTIMP(),
                         impl_->verbose_mode_);
    } else if (message->getRRCount(Message::SECTION_QUESTION) != 1) {
        makeErrorMessage(message, buffer, Rcode::FORMERR(),
                         impl_->verbose_mode_);
    } else {
        ConstQuestionPtr question = *message->beginQuestion();
        const RRType &qtype = question->getType();
        if (qtype == RRType::AXFR()) {
            sendAnswer = impl_->processAxfrQuery(io_message, message, buffer);
        } else if (qtype == RRType::IXFR()) {
            makeErrorMessage(message, buffer, Rcode::NOTIMP(),
                             impl_->verbose_mode_);
        } else {
            sendAnswer = impl_->processNormalQuery(io_message, message, buffer);
        }
    }

    server->resume(sendAnswer);
}

bool
AuthSrvImpl::processNormalQuery(const IOMessage& io_message, MessagePtr message,
                                OutputBufferPtr buffer)
{
    ConstEDNSPtr remote_edns = message->getEDNS();
    const bool dnssec_ok = remote_edns && remote_edns->getDNSSECAwareness();
    const uint16_t remote_bufsize = remote_edns ? remote_edns->getUDPSize() :
        Message::DEFAULT_MAX_UDPSIZE;

    message->makeResponse();
    message->setHeaderFlag(Message::HEADERFLAG_AA);
    message->setRcode(Rcode::NOERROR());

    if (remote_edns) {
        EDNSPtr local_edns = EDNSPtr(new EDNS());
        local_edns->setDNSSECAwareness(dnssec_ok);
        local_edns->setUDPSize(AuthSrvImpl::DEFAULT_LOCAL_UDPSIZE);
        message->setEDNS(local_edns);
    }

    try {
        Query query(*message, cache_, dnssec_ok);
        data_sources_.doQuery(query);
    } catch (const Exception& ex) {
        if (verbose_mode_) {
            cerr << "[b10-auth] Internal error, returning SERVFAIL: " <<
                ex.what() << endl;
        }
        makeErrorMessage(message, buffer, Rcode::SERVFAIL(), verbose_mode_);
        return (true);
    }


    MessageRenderer renderer(*buffer);
    const bool udp_buffer =
        (io_message.getSocket().getProtocol() == IPPROTO_UDP);
    renderer.setLengthLimit(udp_buffer ? remote_bufsize : 65535);
    message->toWire(renderer);

    if (verbose_mode_) {
        cerr << "[b10-auth] sending a response ("
             << renderer.getLength()
             << " bytes):\n" << message->toText() << endl;
    }

    return (true);
}

bool
AuthSrvImpl::processAxfrQuery(const IOMessage& io_message, MessagePtr message,
                              OutputBufferPtr buffer)
{
    if (io_message.getSocket().getProtocol() == IPPROTO_UDP) {
        if (verbose_mode_) {
            cerr << "[b10-auth] AXFR query over UDP isn't allowed" << endl;
        }
        makeErrorMessage(message, buffer, Rcode::FORMERR(), verbose_mode_);
        return (true);
    }

    try {
        if (!xfrout_connected_) {
            xfrout_client_.connect();
            xfrout_connected_ = true;
        }
        xfrout_client_.sendXfroutRequestInfo(
            io_message.getSocket().getNative(),
            io_message.getData(),
            io_message.getDataSize());
    } catch (const XfroutError& err) {
        if (xfrout_connected_) {
            // disconnect() may trigger an exception, but since we try it
            // only if we've successfully opened it, it shouldn't happen in
            // normal condition.  Should this occur, we'll propagate it to the
            // upper layer.
            xfrout_client_.disconnect();
            xfrout_connected_ = false;
        }

        if (verbose_mode_) {
            cerr << "[b10-auth] Error in handling XFR request: " << err.what()
                 << endl;
        }
        makeErrorMessage(message, buffer, Rcode::SERVFAIL(), verbose_mode_);
        return (true);
    }

    return (false);
}

bool
AuthSrvImpl::processNotify(const IOMessage& io_message, MessagePtr message, 
                           OutputBufferPtr buffer)
{
    // The incoming notify must contain exactly one question for SOA of the
    // zone name.
    if (message->getRRCount(Message::SECTION_QUESTION) != 1) {
        if (verbose_mode_) {
                cerr << "[b10-auth] invalid number of questions in notify: "
                     << message->getRRCount(Message::SECTION_QUESTION) << endl;
        }
        makeErrorMessage(message, buffer, Rcode::FORMERR(), verbose_mode_);
        return (true);
    }
    ConstQuestionPtr question = *message->beginQuestion();
    if (question->getType() != RRType::SOA()) {
        if (verbose_mode_) {
                cerr << "[b10-auth] invalid question RR type in notify: "
                     << question->getType() << endl;
        }
        makeErrorMessage(message, buffer, Rcode::FORMERR(), verbose_mode_);
        return (true);
    }

    // According to RFC 1996, rcode should be "no error" and AA bit should be
    // on, but we don't check these conditions.  This behavior is compatible
    // with BIND 9.

    // TODO check with the conf-mgr whether current server is the auth of the
    // zone

    // In the code that follows, we simply ignore the notify if any internal
    // error happens rather than returning (e.g.) SERVFAIL.  RFC 1996 is
    // silent about such cases, but there doesn't seem to be anything we can
    // improve at the primary server side by sending an error anyway.
    if (xfrin_session_ == NULL) {
        if (verbose_mode_) {
            cerr << "[b10-auth] "
                "session interface for xfrin is not available" << endl;
        }
        return (false);
    }

    const string remote_ip_address =
        io_message.getRemoteEndpoint().getAddress().toText();
    static const string command_template_start =
        "{\"command\": [\"notify\", {\"zone_name\" : \"";
    static const string command_template_master = "\", \"master\" : \"";
    static const string command_template_rrclass = "\", \"zone_class\" : \"";
    static const string command_template_end = "\"}]}";

    try {
        ConstElementPtr notify_command = Element::fromJSON(
                command_template_start + question->getName().toText() +
                command_template_master + remote_ip_address +
                command_template_rrclass + question->getClass().toText() +
                command_template_end);
        const unsigned int seq =
            xfrin_session_->group_sendmsg(notify_command, "Zonemgr",
                                          "*", "*");
        ConstElementPtr env, answer, parsed_answer;
        xfrin_session_->group_recvmsg(env, answer, false, seq);
        int rcode;
        parsed_answer = parseAnswer(rcode, answer);
        if (rcode != 0) {
            if (verbose_mode_) {
                cerr << "[b10-auth] failed to notify Zonemgr: "
                     << parsed_answer->str() << endl;
            }
            return (false);
        }
    } catch (const Exception& ex) {
        if (verbose_mode_) {
            cerr << "[b10-auth] failed to notify Zonemgr: " << ex.what() << endl;
        }
        return (false);
    }

    message->makeResponse();
    message->setHeaderFlag(Message::HEADERFLAG_AA);
    message->setRcode(Rcode::NOERROR());

    MessageRenderer renderer(*buffer);
    message->toWire(renderer);
    return (true);
}

ConstElementPtr
AuthSrvImpl::setDbFile(ConstElementPtr config) {
    ConstElementPtr answer = isc::config::createAnswer();

    if (config && config->contains("database_file")) {
        db_file_ = config->get("database_file")->stringValue();
    } else if (config_session_ != NULL) {
        bool is_default;
        string item("database_file");
        ConstElementPtr value = config_session_->getValue(is_default, item);
        ElementPtr final = Element::createMap();

        // If the value is the default, and we are running from
        // a specific directory ('from build'), we need to use
        // a different value than the default (which may not exist)
        // (btw, this should not be done here in the end, i think
        //  the from-source script should have a check for this,
        //  but for that we need offline access to config, so for
        //  now this is a decent solution)
        if (is_default && getenv("B10_FROM_BUILD")) {
            value = Element::create(string(getenv("B10_FROM_BUILD")) +
                                    "/bind10_zones.sqlite3");
        }
        final->set(item, value);
        config = final;

        db_file_ = value->stringValue();
    } else {
        return (answer);
    }

    if (verbose_mode_) {
        cerr << "[b10-auth] Data source database file: " << db_file_ << endl;
    }

    // create SQL data source
    // Note: the following step is tricky to be exception-safe and to ensure
    // exception guarantee: We first need to perform all operations that can
    // fail, while acquiring resources in the RAII manner.  We then perform
    // delete and swap operations which should not fail.
    DataSrcPtr datasrc_ptr(DataSrcPtr(new Sqlite3DataSrc));
    datasrc_ptr->init(config);
    data_sources_.addDataSrc(datasrc_ptr);

    // The following code should be exception free.
    if (cur_datasrc_ != NULL) {
        data_sources_.removeDataSrc(cur_datasrc_);
    }
    cur_datasrc_ = datasrc_ptr;

    return (answer);
}

ConstElementPtr
AuthSrv::updateConfig(ConstElementPtr new_config) {
    try {
        // the ModuleCCSession has already checked if we have
        // the correct ElementPtr type as specified in our .spec file
        return (impl_->setDbFile(new_config));
    } catch (const isc::Exception& error) {
        if (impl_->verbose_mode_) {
            cerr << "[b10-auth] error: " << error.what() << endl;
        }
        return (isc::config::createAnswer(1, error.what()));
    }
}
