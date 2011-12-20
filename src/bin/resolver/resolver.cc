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

#include <config.h>

#include <stdint.h>
#include <netinet/in.h>

#include <algorithm>
#include <vector>
#include <cassert>

#include <boost/shared_ptr.hpp>
#include <boost/foreach.hpp>

#include <exceptions/exceptions.h>

#include <acl/dns.h>
#include <acl/loader.h>

#include <asiodns/asiodns.h>
#include <asiolink/asiolink.h>

#include <config/ccsession.h>

#include <exceptions/exceptions.h>

#include <util/buffer.h>

#include <dns/opcode.h>
#include <dns/rcode.h>
#include <dns/exceptions.h>
#include <dns/name.h>
#include <dns/question.h>
#include <dns/rrset.h>
#include <dns/rrttl.h>
#include <dns/message.h>
#include <dns/messagerenderer.h>

#include <server_common/client.h>
#include <server_common/portconfig.h>

#include <resolve/recursive_query.h>

#include "resolver.h"
#include "resolver_log.h"

using namespace std;
using namespace isc;
using namespace isc::util;
using namespace isc::acl;
using isc::acl::dns::RequestACL;
using namespace isc::dns;
using namespace isc::data;
using namespace isc::config;
using namespace isc::asiodns;
using namespace isc::asiolink;
using namespace isc::server_common;
using namespace isc::server_common::portconfig;

class ResolverImpl {
private:
    // prohibit copy
    ResolverImpl(const ResolverImpl& source);
    ResolverImpl& operator=(const ResolverImpl& source);
public:
    ResolverImpl() :
        config_session_(NULL),
        query_timeout_(2000),
        client_timeout_(4000),
        lookup_timeout_(30000),
        retries_(3),
        // we apply "reject all" (implicit default of the loader) ACL by
        // default:
        query_acl_(acl::dns::getRequestLoader().load(Element::fromJSON("[]"))),
        rec_query_(NULL)
    {}

    ~ResolverImpl() {
        queryShutdown();
    }

    void querySetup(DNSService& dnss,
                    isc::nsas::NameserverAddressStore& nsas,
                    isc::cache::ResolverCache& cache)
    {
        assert(!rec_query_); // queryShutdown must be called first
        LOG_DEBUG(resolver_logger, RESOLVER_DBG_INIT, RESOLVER_QUERY_SETUP);
        rec_query_ = new RecursiveQuery(dnss, 
                                        nsas, cache,
                                        upstream_,
                                        upstream_root_,
                                        query_timeout_,
                                        client_timeout_,
                                        lookup_timeout_,
                                        retries_);
    }

    void queryShutdown() {
        // only shut down if we have actually called querySetup before
        // (this is not a safety check, just to prevent logging of
        // actions that are not performed
        if (rec_query_) {
            LOG_DEBUG(resolver_logger, RESOLVER_DBG_INIT,
                      RESOLVER_QUERY_SHUTDOWN);
            delete rec_query_;
            rec_query_ = NULL;
        }
    }

    void setForwardAddresses(const AddressList& upstream,
        DNSService *dnss)
    {
        upstream_ = upstream;
        if (dnss) {
            if (!upstream_.empty()) {
                BOOST_FOREACH(const AddressPair& address, upstream) {
                    LOG_INFO(resolver_logger, RESOLVER_FORWARD_ADDRESS)
                             .arg(address.first).arg(address.second);
                }
            } else {
                LOG_INFO(resolver_logger, RESOLVER_RECURSIVE);
            }
        }
    }

    void setRootAddresses(const AddressList& upstream_root,
                          DNSService *dnss)
    {
        upstream_root_ = upstream_root;
        if (dnss) {
            if (!upstream_root_.empty()) {
                BOOST_FOREACH(const AddressPair& address, upstream_root) {
                    LOG_INFO(resolver_logger, RESOLVER_SET_ROOT_ADDRESS)
                             .arg(address.first).arg(address.second);
                }
            } else {
                LOG_WARN(resolver_logger, RESOLVER_NO_ROOT_ADDRESS);
            }
        }
    }
    
    void resolve(const isc::dns::QuestionPtr& question,
        const isc::resolve::ResolverInterface::CallbackPtr& callback);

    enum NormalQueryResult { RECURSION, DROPPED, ERROR };
    NormalQueryResult processNormalQuery(const IOMessage& io_message,
                                         MessagePtr query_message,
                                         MessagePtr answer_message,
                                         OutputBufferPtr buffer,
                                         DNSServer* server);

    const RequestACL& getQueryACL() const {
        return (*query_acl_);
    }

    void setQueryACL(boost::shared_ptr<const RequestACL> new_acl) {
        query_acl_ = new_acl;
    }

    /// Currently non-configurable, but will be.
    static const uint16_t DEFAULT_LOCAL_UDPSIZE = 4096;

    /// These members are public because Resolver accesses them directly.
    ModuleCCSession* config_session_;
    /// Addresses of the root nameserver(s)
    AddressList upstream_root_;
    /// Addresses of the forward nameserver
    AddressList upstream_;
    /// Addresses we listen on
    AddressList listen_;

    /// Timeout for outgoing queries in milliseconds
    int query_timeout_;
    /// Timeout for incoming client queries in milliseconds
    int client_timeout_;
    /// Timeout for lookup processing in milliseconds
    int lookup_timeout_;
    
    /// Number of retries after timeout
    unsigned retries_;

private:
    /// ACL on incoming queries
    boost::shared_ptr<const RequestACL> query_acl_;

    /// Object to handle upstream queries
    RecursiveQuery* rec_query_;
};

/*
 * std::for_each has a broken interface. It makes no sense in a language
 * without lambda functions/closures. These two classes emulate the lambda
 * functions so for_each can be used.
 */
class QuestionInserter {
public:
    QuestionInserter(MessagePtr message) : message_(message) {}
    void operator()(const QuestionPtr question) {
        message_->addQuestion(question);
    }
    MessagePtr message_;
};


// TODO: REMOVE, USE isc::resolve::MakeErrorMessage?
void
makeErrorMessage(MessagePtr message, MessagePtr answer_message,
                 OutputBufferPtr buffer, const Rcode& rcode)
{
    // extract the parameters that should be kept.
    // XXX: with the current implementation, it's not easy to set EDNS0
    // depending on whether the query had it.  So we'll simply omit it.
    const qid_t qid = message->getQid();
    const bool rd = message->getHeaderFlag(Message::HEADERFLAG_RD);
    const bool cd = message->getHeaderFlag(Message::HEADERFLAG_CD);
    const Opcode& opcode = message->getOpcode();
    vector<QuestionPtr> questions;

    // answer_message is actually ignored right now,
    // see the comment in #607
    answer_message->setRcode(rcode);
    answer_message->setOpcode(opcode);
    answer_message->setQid(qid);

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
}

// This is a derived class of \c DNSLookup, to serve as a
// callback in the asiolink module.  It calls
// Resolver::processMessage() on a single DNS message.
class MessageLookup : public DNSLookup {
public:
    MessageLookup(Resolver* srv) : server_(srv) {}

    // \brief Handle the DNS Lookup
    virtual void operator()(const IOMessage& io_message,
                            MessagePtr query_message,
                            MessagePtr answer_message,
                            OutputBufferPtr buffer,
                            DNSServer* server) const
    {
        server_->processMessage(io_message, query_message,
                                answer_message, buffer, server);
    }
private:
    Resolver* server_;
};

// This is a derived class of \c DNSAnswer, to serve as a
// callback in the asiolink module.  It takes a completed
// set of answer data from the DNS lookup and assembles it
// into a wire-format response.
class MessageAnswer : public DNSAnswer {
public:
    virtual void operator()(const IOMessage& io_message,
                            MessagePtr query_message,
                            MessagePtr answer_message,
                            OutputBufferPtr buffer) const
    {
        const qid_t qid = query_message->getQid();
        const bool rd = query_message->getHeaderFlag(Message::HEADERFLAG_RD);
        const bool cd = query_message->getHeaderFlag(Message::HEADERFLAG_CD);
        
        // The opcode and question section should have already been set,
        // fill in the final details of the answer message
        answer_message->setQid(qid);

        answer_message->setHeaderFlag(Message::HEADERFLAG_QR);
        answer_message->setHeaderFlag(Message::HEADERFLAG_RA);
        answer_message->setHeaderFlag(Message::HEADERFLAG_RD, rd);
        answer_message->setHeaderFlag(Message::HEADERFLAG_CD, cd);

        // Now we can clear the buffer and render the new message into it
        buffer->clear();
        MessageRenderer renderer(*buffer);

        ConstEDNSPtr edns(query_message->getEDNS());
        const bool dnssec_ok = edns && edns->getDNSSECAwareness();
        if (edns) {
            EDNSPtr edns_response(new EDNS());
            edns_response->setDNSSECAwareness(dnssec_ok);

            // TODO: We should make our own edns bufsize length configurable
            edns_response->setUDPSize(Message::DEFAULT_MAX_EDNS0_UDPSIZE);
            answer_message->setEDNS(edns_response);
        }

        if (io_message.getSocket().getProtocol() == IPPROTO_UDP) {
            if (edns) {
                renderer.setLengthLimit(edns->getUDPSize());
            } else {
                renderer.setLengthLimit(Message::DEFAULT_MAX_UDPSIZE);
            }
        } else {
            renderer.setLengthLimit(65535);
        }

        answer_message->toWire(renderer);

        LOG_DEBUG(resolver_logger, RESOLVER_DBG_DETAIL,
                  RESOLVER_DNS_MESSAGE_SENT)
                  .arg(renderer.getLength()).arg(*answer_message);
    }
};

// This is a derived class of \c SimpleCallback, to serve
// as a callback in the asiolink module.  It checks for queued
// configuration messages, and executes them if found.
class ConfigCheck : public SimpleCallback {
public:
    ConfigCheck(Resolver* srv) : server_(srv) {}
    virtual void operator()(const IOMessage&) const {
        if (server_->getConfigSession()->hasQueuedMsgs()) {
            server_->getConfigSession()->checkCommand();
        }
    }
private:
    Resolver* server_;
};

Resolver::Resolver() :
    impl_(new ResolverImpl()),
    dnss_(NULL),
    checkin_(NULL),
    dns_lookup_(NULL),
    dns_answer_(new MessageAnswer),
    nsas_(NULL),
    cache_(NULL),
    configured_(false)
{
    // Operations referring to "this" must be done in the constructor body
    // (some compilers will issue warnings if "this" is referred to in the
    // initialization list).
    checkin_ = new ConfigCheck(this);
    dns_lookup_ = new MessageLookup(this);
}

Resolver::~Resolver() {
    delete impl_;
    delete checkin_;
    delete dns_lookup_;
    delete dns_answer_;
}

void
Resolver::setDNSService(isc::asiodns::DNSService& dnss) {
    dnss_ = &dnss;
}

void
Resolver::setNameserverAddressStore(isc::nsas::NameserverAddressStore& nsas)
{
    nsas_ = &nsas;
}

void
Resolver::setCache(isc::cache::ResolverCache& cache)
{
    cache_ = &cache;
}


void
Resolver::setConfigSession(ModuleCCSession* config_session) {
    impl_->config_session_ = config_session;
}

ModuleCCSession*
Resolver::getConfigSession() const {
    return (impl_->config_session_);
}

void
Resolver::resolve(const isc::dns::QuestionPtr& question,
    const isc::resolve::ResolverInterface::CallbackPtr& callback)
{
    impl_->resolve(question, callback);
}


void
Resolver::processMessage(const IOMessage& io_message,
                         MessagePtr query_message,
                         MessagePtr answer_message,
                         OutputBufferPtr buffer,
                         DNSServer* server)
{
    InputBuffer request_buffer(io_message.getData(), io_message.getDataSize());
    // First, check the header part.  If we fail even for the base header,
    // just drop the message.

    // In the following code, the debug output is such that there should only be
    // one debug message if packet processing failed.  There could be two if
    // it succeeded.
    try {
        query_message->parseHeader(request_buffer);

        // Ignore all responses.
        if (query_message->getHeaderFlag(Message::HEADERFLAG_QR)) {
            LOG_DEBUG(resolver_logger, RESOLVER_DBG_IO, RESOLVER_UNEXPECTED_RESPONSE);
            server->resume(false);
            return;
        }
    } catch (const Exception& ex) {
        LOG_DEBUG(resolver_logger, RESOLVER_DBG_IO, RESOLVER_HEADER_ERROR)
                  .arg(ex.what());
        server->resume(false);
        return;
    }

    // Parse the message.  On failure, return an appropriate error.
    try {
        query_message->fromWire(request_buffer);
    } catch (const DNSProtocolError& error) {
        LOG_DEBUG(resolver_logger, RESOLVER_DBG_IO, RESOLVER_PROTOCOL_ERROR)
                  .arg(error.what()).arg(error.getRcode());
        makeErrorMessage(query_message, answer_message,
                         buffer, error.getRcode());
        server->resume(true);
        return;
    } catch (const Exception& ex) {
        LOG_DEBUG(resolver_logger, RESOLVER_DBG_IO, RESOLVER_MESSAGE_ERROR)
                  .arg(ex.what()).arg(Rcode::SERVFAIL());
        makeErrorMessage(query_message, answer_message,
                         buffer, Rcode::SERVFAIL());
        server->resume(true);
        return;
    } // Other exceptions will be handled at a higher layer.

    // Note:  there appears to be no LOG_DEBUG for a successfully-received
    // message.  This is not an oversight - it is handled below.  In the
    // meantime, output the full message for debug purposes (if requested).
    LOG_DEBUG(resolver_logger, RESOLVER_DBG_DETAIL,
              RESOLVER_DNS_MESSAGE_RECEIVED).arg(*query_message);

    // Perform further protocol-level validation.
    bool send_answer = true;
    if (query_message->getOpcode() == Opcode::NOTIFY()) {

        makeErrorMessage(query_message, answer_message,
                         buffer, Rcode::NOTAUTH());
        // Notify arrived, but we are not authoritative.
        LOG_DEBUG(resolver_logger, RESOLVER_DBG_PROCESS,
                  RESOLVER_NOTIFY_RECEIVED);
    } else if (query_message->getOpcode() != Opcode::QUERY()) {
        // Unsupported opcode.
        LOG_DEBUG(resolver_logger, RESOLVER_DBG_PROCESS,
                  RESOLVER_UNSUPPORTED_OPCODE).arg(query_message->getOpcode());
        makeErrorMessage(query_message, answer_message,
                         buffer, Rcode::NOTIMP());
    } else if (query_message->getRRCount(Message::SECTION_QUESTION) != 1) {
        // Not one question
        LOG_DEBUG(resolver_logger, RESOLVER_DBG_PROCESS,
                  RESOLVER_NOT_ONE_QUESTION)
                  .arg(query_message->getRRCount(Message::SECTION_QUESTION));
        makeErrorMessage(query_message, answer_message, buffer,
                         Rcode::FORMERR());
    } else {
        const ResolverImpl::NormalQueryResult result =
            impl_->processNormalQuery(io_message, query_message,
                                      answer_message, buffer, server);
        if (result == ResolverImpl::RECURSION) {
            // The RecursiveQuery object will post the "resume" event to the
            // DNSServer when an answer arrives, so we don't have to do it now.
            return;
        } else if (result == ResolverImpl::DROPPED) {
            send_answer = false;
        }
    }

    server->resume(send_answer);
}

void
ResolverImpl::resolve(const QuestionPtr& question,
    const isc::resolve::ResolverInterface::CallbackPtr& callback)
{
    rec_query_->resolve(question, callback);
}

ResolverImpl::NormalQueryResult
ResolverImpl::processNormalQuery(const IOMessage& io_message,
                                 MessagePtr query_message,
                                 MessagePtr answer_message,
                                 OutputBufferPtr buffer,
                                 DNSServer* server)
{
    const ConstQuestionPtr question = *query_message->beginQuestion();
    const RRType qtype = question->getType();
    const RRClass qclass = question->getClass();

    // Apply query ACL
    const Client client(io_message);
    const BasicAction query_action(
        getQueryACL().execute(acl::dns::RequestContext(
                                  client.getRequestSourceIPAddress(),
                                  query_message->getTSIGRecord())));
    if (query_action == isc::acl::REJECT) {
        LOG_INFO(resolver_logger, RESOLVER_QUERY_REJECTED)
            .arg(question->getName()).arg(qtype).arg(qclass).arg(client);
        makeErrorMessage(query_message, answer_message, buffer,
                         Rcode::REFUSED());
        return (ERROR);
    } else if (query_action == isc::acl::DROP) {
        LOG_INFO(resolver_logger, RESOLVER_QUERY_DROPPED)
            .arg(question->getName()).arg(qtype).arg(qclass).arg(client);
        return (DROPPED);
    }
    LOG_DEBUG(resolver_logger, RESOLVER_DBG_IO, RESOLVER_QUERY_ACCEPTED)
        .arg(question->getName()).arg(qtype).arg(question->getClass())
        .arg(client);

    // ACL passed.  Reject inappropriate queries for the resolver.
    if (qtype == RRType::AXFR()) {
        if (io_message.getSocket().getProtocol() == IPPROTO_UDP) {
            // Can't process AXFR request received over UDP
            LOG_DEBUG(resolver_logger, RESOLVER_DBG_PROCESS, RESOLVER_AXFR_UDP);
            makeErrorMessage(query_message, answer_message, buffer,
                             Rcode::FORMERR());
        } else {
            // ... or over TCP for that matter
            LOG_DEBUG(resolver_logger, RESOLVER_DBG_PROCESS, RESOLVER_AXFR_TCP);
            makeErrorMessage(query_message, answer_message, buffer,
                             Rcode::NOTIMP());
        }
        return (ERROR);
    } else if (qtype == RRType::IXFR()) {
        // Can't process IXFR request
        LOG_DEBUG(resolver_logger, RESOLVER_DBG_PROCESS, RESOLVER_IXFR);
        makeErrorMessage(query_message, answer_message, buffer,
                         Rcode::NOTIMP());
        return (ERROR);
    } else if (qclass != RRClass::IN()) {
        // Non-IN message received, refuse it.
        LOG_DEBUG(resolver_logger, RESOLVER_DBG_PROCESS, RESOLVER_NON_IN_PACKET)
            .arg(question->getClass());
        makeErrorMessage(query_message, answer_message, buffer,
                         Rcode::REFUSED());
        return (ERROR);
    }

    // Everything is okay.  Start resolver.
    if (upstream_.empty()) {
        // Processing normal query
        LOG_DEBUG(resolver_logger, RESOLVER_DBG_IO, RESOLVER_NORMAL_QUERY);
        rec_query_->resolve(*question, answer_message, buffer, server);
    } else {
        // Processing forward query
        LOG_DEBUG(resolver_logger, RESOLVER_DBG_IO, RESOLVER_FORWARD_QUERY);
        rec_query_->forward(query_message, answer_message, buffer, server);
    }

    return (RECURSION);
}

ConstElementPtr
Resolver::updateConfig(ConstElementPtr config) {
    LOG_DEBUG(resolver_logger, RESOLVER_DBG_CONFIG, RESOLVER_CONFIG_UPDATED)
              .arg(*config);

    try {
        // Parse forward_addresses
        ConstElementPtr rootAddressesE(config->get("root_addresses"));
        AddressList rootAddresses(parseAddresses(rootAddressesE,
                                                    "root_addresses"));
        ConstElementPtr forwardAddressesE(config->get("forward_addresses"));
        AddressList forwardAddresses(parseAddresses(forwardAddressesE,
                                                       "forward_addresses"));
        ConstElementPtr listenAddressesE(config->get("listen_on"));
        AddressList listenAddresses(parseAddresses(listenAddressesE,
                                                      "listen_on"));
        const ConstElementPtr query_acl_cfg(config->get("query_acl"));
        const boost::shared_ptr<const RequestACL> query_acl =
            query_acl_cfg ? acl::dns::getRequestLoader().load(query_acl_cfg) :
            boost::shared_ptr<RequestACL>();
        bool set_timeouts(false);
        int qtimeout = impl_->query_timeout_;
        int ctimeout = impl_->client_timeout_;
        int ltimeout = impl_->lookup_timeout_;
        unsigned retries = impl_->retries_;
        ConstElementPtr qtimeoutE(config->get("timeout_query")),
                        ctimeoutE(config->get("timeout_client")),
                        ltimeoutE(config->get("timeout_lookup")),
                        retriesE(config->get("retries"));
        if (qtimeoutE) {
            // It should be safe to just get it, the config manager should
            // check for us
            qtimeout = qtimeoutE->intValue();
            if (qtimeout < -1) {
                LOG_ERROR(resolver_logger, RESOLVER_QUERY_TIME_SMALL)
                          .arg(qtimeout);
                isc_throw(BadValue, "Query timeout too small");
            }
            set_timeouts = true;
        }
        if (ctimeoutE) {
            ctimeout = ctimeoutE->intValue();
            if (ctimeout < -1) {
                LOG_ERROR(resolver_logger, RESOLVER_CLIENT_TIME_SMALL)
                          .arg(ctimeout);
                isc_throw(BadValue, "Client timeout too small");
            }
            set_timeouts = true;
        }
        if (ltimeoutE) {
            ltimeout = ltimeoutE->intValue();
            if (ltimeout < -1) {
                LOG_ERROR(resolver_logger, RESOLVER_LOOKUP_TIME_SMALL)
                          .arg(ltimeout);
                isc_throw(BadValue, "Lookup timeout too small");
            }
            set_timeouts = true;
        }
        if (retriesE) {
            // Do the assignment from "retriesE->intValue()" to "retries"
            // _after_ the comparison (as opposed to before it for the timeouts)
            // because "retries" is unsigned.
            if (retriesE->intValue() < 0) {
                LOG_ERROR(resolver_logger, RESOLVER_NEGATIVE_RETRIES)
                          .arg(retriesE->intValue());
                isc_throw(BadValue, "Negative number of retries");
            }
            retries = retriesE->intValue();
            set_timeouts = true;
        }
        // Everything OK, so commit the changes
        // listenAddresses can fail to bind, so try them first
        bool need_query_restart = false;
        
        if (listenAddressesE) {
            setListenAddresses(listenAddresses);
            need_query_restart = true;
        }
        if (forwardAddressesE) {
            setForwardAddresses(forwardAddresses);
            need_query_restart = true;
        }
        if (rootAddressesE) {
            setRootAddresses(rootAddresses);
            need_query_restart = true;
        }
        if (set_timeouts) {
            setTimeouts(qtimeout, ctimeout, ltimeout, retries);
            need_query_restart = true;
        }
        if (query_acl) {
            setQueryACL(query_acl);
        }

        if (need_query_restart) {
            impl_->queryShutdown();
            impl_->querySetup(*dnss_, *nsas_, *cache_);
        }
        setConfigured();
        return (isc::config::createAnswer());

    } catch (const isc::Exception& error) {

        // Configuration error
        LOG_ERROR(resolver_logger, RESOLVER_CONFIG_ERROR).arg(error.what());
        return (isc::config::createAnswer(1, error.what()));
    }
}

void
Resolver::setForwardAddresses(const AddressList& addresses)
{
    impl_->setForwardAddresses(addresses, dnss_);
}

void
Resolver::setRootAddresses(const AddressList& addresses)
{
    impl_->setRootAddresses(addresses, dnss_);
}

bool
Resolver::isForwarding() const {
    return (!impl_->upstream_.empty());
}

AddressList
Resolver::getForwardAddresses() const {
    return (impl_->upstream_);
}

AddressList
Resolver::getRootAddresses() const {
    return (impl_->upstream_root_);
}

void
Resolver::setListenAddresses(const AddressList& addresses) {
    installListenAddresses(addresses, impl_->listen_, *dnss_);
}

void
Resolver::setTimeouts(int query_timeout, int client_timeout,
                      int lookup_timeout, unsigned retries) {
    LOG_DEBUG(resolver_logger, RESOLVER_DBG_CONFIG, RESOLVER_SET_PARAMS)
              .arg(query_timeout).arg(client_timeout).arg(lookup_timeout)
              .arg(retries);

    impl_->query_timeout_ = query_timeout;
    impl_->client_timeout_ = client_timeout;
    impl_->lookup_timeout_ = lookup_timeout;
    impl_->retries_ = retries;
}

int
Resolver::getQueryTimeout() const {
    return impl_->query_timeout_;
}

int
Resolver::getClientTimeout() const {
    return impl_->client_timeout_;
}

int
Resolver::getLookupTimeout() const {
    return impl_->lookup_timeout_;
}

int
Resolver::getRetries() const {
    return impl_->retries_;
}

AddressList
Resolver::getListenAddresses() const {
    return (impl_->listen_);
}

const RequestACL&
Resolver::getQueryACL() const {
    return (impl_->getQueryACL());
}

void
Resolver::setQueryACL(boost::shared_ptr<const RequestACL> new_acl) {
    if (!new_acl) {
        isc_throw(InvalidParameter, "NULL pointer is passed to setQueryACL");
    }

    LOG_INFO(resolver_logger, RESOLVER_SET_QUERY_ACL);
    impl_->setQueryACL(new_acl);
}
