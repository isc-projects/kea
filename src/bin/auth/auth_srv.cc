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

#include <util/io/socketsession.h>

#include <asiolink/asiolink.h>
#include <asiolink/io_endpoint.h>

#include <config/ccsession.h>

#include <cc/data.h>

#include <exceptions/exceptions.h>

#include <util/buffer.h>

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
#include <dns/tsig.h>

#include <asiodns/dns_service.h>

#include <datasrc/query.h>
#include <datasrc/data_source.h>
#include <datasrc/static_datasrc.h>
#include <datasrc/sqlite3_datasrc.h>
#include <datasrc/client_list.h>

#include <xfr/xfrout_client.h>

#include <auth/common.h>
#include <auth/auth_config.h>
#include <auth/auth_srv.h>
#include <auth/query.h>
#include <auth/statistics.h>
#include <auth/auth_log.h>

#include <boost/bind.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/scoped_ptr.hpp>

#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>
#include <memory>

#include <sys/types.h>
#include <netinet/in.h>

using namespace std;

using namespace isc;
using namespace isc::cc;
using namespace isc::datasrc;
using namespace isc::dns;
using namespace isc::util;
using namespace isc::util::io;
using namespace isc::auth;
using namespace isc::dns::rdata;
using namespace isc::data;
using namespace isc::config;
using namespace isc::xfr;
using namespace isc::asiolink;
using namespace isc::asiodns;
using namespace isc::server_common::portconfig;

namespace {
// A helper class for cleaning up message renderer.
//
// A temporary object of this class is expected to be created before starting
// response message rendering.  On construction, it (re)initialize the given
// message renderer with the given buffer.  On destruction, it releases
// the previously set buffer and then release any internal resource in the
// renderer, no matter what happened during the rendering, especially even
// when it resulted in an exception.
//
// Note: if we need this helper in many other places we might consider making
// it visible to other modules.  As of this implementation this is the only
// user of this class, so we hide it within the implementation.
class RendererHolder {
public:
    RendererHolder(MessageRenderer& renderer, OutputBuffer* buffer) :
        renderer_(renderer)
    {
        renderer.setBuffer(buffer);
    }
    ~RendererHolder() {
        renderer_.setBuffer(NULL);
        renderer_.clear();
    }
private:
    MessageRenderer& renderer_;
};

// Similar to Renderer holder, this is a very basic RAII-style class
// that calls clear(Message::PARSE) on the given Message upon destruction
class MessageHolder {
public:
    MessageHolder(Message& message) : message_(message) {}
    ~MessageHolder() {
        message_.clear(Message::PARSE);
    }
private:
    Message& message_;
};

// A helper container of socket session forwarder.
//
// This class provides a simple wrapper interface to SocketSessionForwarder
// so that the caller doesn't have to worry about connection management,
// exception handling or parameter building.
//
// It internally maintains whether the underlying forwarder establishes a
// connection to the receiver.  On a forwarding request, if the connection
// hasn't been established yet, it automatically opens a new one, then
// pushes the session over it.  It also closes the connection on destruction,
// or a non-recoverable error happens, automatically.  So the only thing
// the application has to do is to create this object and push any session
// to be forwarded.
class SocketSessionForwarderHolder {
public:
    /// \brief The constructor.
    ///
    /// \param message_name Any string that can identify the type of messages
    /// to be forwarded via this session.  It will be only used as part of
    /// log message, so it can be anything, but in practice something like
    /// "update" or "xfr" is expected.
    /// \param forwarder The underlying socket session forwarder.
    SocketSessionForwarderHolder(const string& message_name,
                                 BaseSocketSessionForwarder& forwarder) :
        message_name_(message_name), forwarder_(forwarder), connected_(false)
    {}

    ~SocketSessionForwarderHolder() {
        if (connected_) {
            forwarder_.close();
        }
    }

    /// \brief Push a socket session corresponding to given IOMessage.
    ///
    /// If the connection with the receiver process hasn't been established,
    /// it automatically establishes one, then push the session over it.
    ///
    /// If either connect or push fails, the underlying forwarder object should
    /// throw an exception.  This method logs the event, and propagates the
    /// exception to the caller, which will eventually result in SERVFAIL.
    /// The connection, if established, is automatically closed, so the next
    /// forward request will trigger reopening a new connection.
    ///
    /// \note: Right now, there's no API to retrieve the local address from
    /// the IOMessage.  Until it's added, we pass the remote address as
    /// local.
    ///
    /// \param io_message The request message to be forwarded as a socket
    /// session.  It will be converted to the parameters that the underlying
    /// SocketSessionForwarder expects.
    void push(const IOMessage& io_message) {
        const IOEndpoint& remote_ep = io_message.getRemoteEndpoint();
        const int protocol = remote_ep.getProtocol();
        const int sock_type = getSocketType(protocol);
        try {
            connect();
            forwarder_.push(io_message.getSocket().getNative(),
                            remote_ep.getFamily(), sock_type, protocol,
                            remote_ep.getSockAddr(), remote_ep.getSockAddr(),
                            io_message.getData(), io_message.getDataSize());
        } catch (const SocketSessionError& ex) {
            LOG_ERROR(auth_logger, AUTH_MESSAGE_FORWARD_ERROR).
                arg(message_name_).arg(remote_ep).arg(ex.what());
            close();
            throw;
        }
    }

private:
    const string message_name_;
    BaseSocketSessionForwarder& forwarder_;
    bool connected_;

    void connect() {
        if (!connected_) {
            forwarder_.connectToReceiver();
            connected_ = true;
        }
    }

    void close() {
        if (connected_) {
            forwarder_.close();
            connected_ = false;
        }
    }

    static int getSocketType(int protocol) {
        switch (protocol) {
        case IPPROTO_UDP:
            return (SOCK_DGRAM);
        case IPPROTO_TCP:
            return (SOCK_STREAM);
        default:
            isc_throw(isc::InvalidParameter,
                      "Unexpected socket address family: " << protocol);
        }
    }
};
}

class AuthSrvImpl {
private:
    // prohibit copy
    AuthSrvImpl(const AuthSrvImpl& source);
    AuthSrvImpl& operator=(const AuthSrvImpl& source);
public:
    AuthSrvImpl(AbstractXfroutClient& xfrout_client,
                BaseSocketSessionForwarder& ddns_forwarder);
    ~AuthSrvImpl();

    bool processNormalQuery(const IOMessage& io_message, Message& message,
                            OutputBuffer& buffer,
                            auto_ptr<TSIGContext> tsig_context);
    bool processXfrQuery(const IOMessage& io_message, Message& message,
                         OutputBuffer& buffer,
                         auto_ptr<TSIGContext> tsig_context);
    bool processNotify(const IOMessage& io_message, Message& message,
                       OutputBuffer& buffer,
                       auto_ptr<TSIGContext> tsig_context);
    bool processUpdate(const IOMessage& io_message);

    IOService io_service_;

    MessageRenderer renderer_;
    /// Currently non-configurable, but will be.
    static const uint16_t DEFAULT_LOCAL_UDPSIZE = 4096;

    /// These members are public because AuthSrv accesses them directly.
    ModuleCCSession* config_session_;
    AbstractSession* xfrin_session_;

    /// Query counters for statistics
    AuthCounters counters_;

    /// Addresses we listen on
    AddressList listen_addresses_;

    /// The TSIG keyring
    const boost::shared_ptr<TSIGKeyRing>* keyring_;

    /// The client list
    std::map<RRClass, boost::shared_ptr<ConfigurableClientList> >
        client_lists_;

    boost::shared_ptr<ConfigurableClientList> getClientList(const RRClass&
                                                            rrclass)
    {
        const std::map<RRClass, boost::shared_ptr<ConfigurableClientList> >::
            const_iterator it(client_lists_.find(rrclass));
        if (it == client_lists_.end()) {
            return (boost::shared_ptr<ConfigurableClientList>());
        } else {
            return (it->second);
        }
    }

    /// Bind the ModuleSpec object in config_session_ with
    /// isc:config::ModuleSpec::validateStatistics.
    void registerStatisticsValidator();

    /// Socket session forwarder for dynamic update requests
    BaseSocketSessionForwarder& ddns_base_forwarder_;

    /// Holder for the DDNS Forwarder, which is used to send
    /// DDNS messages to b10-ddns, but can be set to empty if
    /// b10-ddns is not running
    boost::scoped_ptr<SocketSessionForwarderHolder> ddns_forwarder_;

    /// \brief Resume the server
    ///
    /// This is a wrapper call for DNSServer::resume(done), if 'done' is true,
    /// the Rcode set in the given Message is counted in the statistics
    /// counter.
    ///
    /// This method is expected to be called by processMessage()
    ///
    /// \param server The DNSServer as passed to processMessage()
    /// \param message The response as constructed by processMessage()
    /// \param done If true, the Rcode from the given message is counted,
    ///             this value is then passed to server->resume(bool)
    void resumeServer(isc::asiodns::DNSServer* server,
                      isc::dns::Message& message,
                      bool done);

private:
    bool xfrout_connected_;
    AbstractXfroutClient& xfrout_client_;

    /// Increment query counter
    void incCounter(const int protocol);

    // validateStatistics
    bool validateStatistics(isc::data::ConstElementPtr data) const;

    auth::Query query_;
};

AuthSrvImpl::AuthSrvImpl(AbstractXfroutClient& xfrout_client,
                         BaseSocketSessionForwarder& ddns_forwarder) :
    config_session_(NULL),
    xfrin_session_(NULL),
    counters_(),
    keyring_(NULL),
    ddns_base_forwarder_(ddns_forwarder),
    ddns_forwarder_(NULL),
    xfrout_connected_(false),
    xfrout_client_(xfrout_client)
{}

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
    virtual void operator()(const IOMessage& io_message,
                            MessagePtr message,
                            MessagePtr, // Not used here
                            OutputBufferPtr buffer,
                            DNSServer* server) const
    {
        // Keep a holder on the message, so that it is automatically
        // cleared if processMessage() is done
        // This is not done in processMessage itself (which would be
        // equivalent), to allow tests to inspect the message handling.
        MessageHolder message_holder(*message);
        server_->processMessage(io_message, *message, *buffer, server);
    }
private:
    AuthSrv* server_;
};

// This is a derived class of \c DNSAnswer, to serve as a callback in the
// asiolink module.  We actually shouldn't do anything in this class because
// we build complete response messages in the process methods; otherwise
// the response message will contain trailing garbage.  In future, we should
// probably even drop the reliance on DNSAnswer.  We don't need the coroutine
// tricks provided in that framework, and its overhead would be significant
// in terms of performance consideration for the authoritative server
// implementation.
class MessageAnswer : public DNSAnswer {
public:
    MessageAnswer(AuthSrv*) {}
    virtual void operator()(const IOMessage&, MessagePtr,
                            MessagePtr, OutputBufferPtr) const
    {}
};

// This is a derived class of \c SimpleCallback, to serve
// as a callback in the asiolink module.  It checks for queued
// configuration messages, and executes them if found.
class ConfigChecker : public SimpleCallback {
public:
    ConfigChecker(AuthSrv* srv) : server_(srv) {}
    virtual void operator()(const IOMessage&) const {
        ModuleCCSession* cfg_session = server_->getConfigSession();
        if (cfg_session != NULL && cfg_session->hasQueuedMsgs()) {
            cfg_session->checkCommand();
        }
    }
private:
    AuthSrv* server_;
};

AuthSrv::AuthSrv(isc::xfr::AbstractXfroutClient& xfrout_client,
                 isc::util::io::BaseSocketSessionForwarder& ddns_forwarder)
{
    impl_ = new AuthSrvImpl(xfrout_client, ddns_forwarder);
    checkin_ = new ConfigChecker(this);
    dns_lookup_ = new MessageLookup(this);
    dns_answer_ = new MessageAnswer(this);
}

void
AuthSrv::stop() {
    impl_->io_service_.stop();
}

AuthSrv::~AuthSrv() {
    delete impl_;
    delete checkin_;
    delete dns_lookup_;
    delete dns_answer_;
}

namespace {
class QuestionInserter {
public:
    QuestionInserter(Message& message) : message_(message) {}
    void operator()(const QuestionPtr question) {
        message_.addQuestion(question);
    }
    Message& message_;
};

void
makeErrorMessage(MessageRenderer& renderer, Message& message,
                 OutputBuffer& buffer, const Rcode& rcode,
                 std::auto_ptr<TSIGContext> tsig_context =
                 std::auto_ptr<TSIGContext>())
{
    // extract the parameters that should be kept.
    // XXX: with the current implementation, it's not easy to set EDNS0
    // depending on whether the query had it.  So we'll simply omit it.
    const qid_t qid = message.getQid();
    const bool rd = message.getHeaderFlag(Message::HEADERFLAG_RD);
    const bool cd = message.getHeaderFlag(Message::HEADERFLAG_CD);
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
    message.setHeaderFlag(Message::HEADERFLAG_QR);
    if (rd) {
        message.setHeaderFlag(Message::HEADERFLAG_RD);
    }
    if (cd) {
        message.setHeaderFlag(Message::HEADERFLAG_CD);
    }
    for_each(questions.begin(), questions.end(), QuestionInserter(message));

    message.setRcode(rcode);

    RendererHolder holder(renderer, &buffer);
    if (tsig_context.get() != NULL) {
        message.toWire(renderer, *tsig_context);
    } else {
        message.toWire(renderer);
    }
    LOG_DEBUG(auth_logger, DBG_AUTH_MESSAGES, AUTH_SEND_ERROR_RESPONSE)
              .arg(renderer.getLength()).arg(message);
}
}

IOService&
AuthSrv::getIOService() {
    return (impl_->io_service_);
}

void
AuthSrv::setXfrinSession(AbstractSession* xfrin_session) {
    impl_->xfrin_session_ = xfrin_session;
}

void
AuthSrv::setConfigSession(ModuleCCSession* config_session) {
    impl_->config_session_ = config_session;
    impl_->registerStatisticsValidator();
}

ModuleCCSession*
AuthSrv::getConfigSession() const {
    return (impl_->config_session_);
}

void
AuthSrv::processMessage(const IOMessage& io_message, Message& message,
                        OutputBuffer& buffer, DNSServer* server)
{
    InputBuffer request_buffer(io_message.getData(), io_message.getDataSize());

    // First, check the header part.  If we fail even for the base header,
    // just drop the message.
    try {
        message.parseHeader(request_buffer);

        // Ignore all responses.
        if (message.getHeaderFlag(Message::HEADERFLAG_QR)) {
            LOG_DEBUG(auth_logger, DBG_AUTH_DETAIL, AUTH_RESPONSE_RECEIVED);
            impl_->resumeServer(server, message, false);
            return;
        }
    } catch (const Exception& ex) {
        LOG_DEBUG(auth_logger, DBG_AUTH_DETAIL, AUTH_HEADER_PARSE_FAIL)
                  .arg(ex.what());
        impl_->resumeServer(server, message, false);
        return;
    }

    try {
        // Parse the message.
        message.fromWire(request_buffer);
    } catch (const DNSProtocolError& error) {
        LOG_DEBUG(auth_logger, DBG_AUTH_DETAIL, AUTH_PACKET_PROTOCOL_ERROR)
                  .arg(error.getRcode().toText()).arg(error.what());
        makeErrorMessage(impl_->renderer_, message, buffer, error.getRcode());
        impl_->resumeServer(server, message, true);
        return;
    } catch (const Exception& ex) {
        LOG_DEBUG(auth_logger, DBG_AUTH_DETAIL, AUTH_PACKET_PARSE_ERROR)
                  .arg(ex.what());
        makeErrorMessage(impl_->renderer_, message, buffer, Rcode::SERVFAIL());
        impl_->resumeServer(server, message, true);
        return;
    } // other exceptions will be handled at a higher layer.

    LOG_DEBUG(auth_logger, DBG_AUTH_MESSAGES, AUTH_PACKET_RECEIVED)
              .arg(message);

    // Perform further protocol-level validation.
    // TSIG first
    // If this is set to something, we know we need to answer with TSIG as well
    std::auto_ptr<TSIGContext> tsig_context;
    const TSIGRecord* tsig_record(message.getTSIGRecord());
    TSIGError tsig_error(TSIGError::NOERROR());

    // Do we do TSIG?
    // The keyring can be null if we're in test
    if (impl_->keyring_ != NULL && tsig_record != NULL) {
        tsig_context.reset(new TSIGContext(tsig_record->getName(),
                                           tsig_record->getRdata().
                                                getAlgorithm(),
                                           **impl_->keyring_));
        tsig_error = tsig_context->verify(tsig_record, io_message.getData(),
                                          io_message.getDataSize());
    }

    if (tsig_error != TSIGError::NOERROR()) {
        makeErrorMessage(impl_->renderer_, message, buffer,
                         tsig_error.toRcode(), tsig_context);
        impl_->resumeServer(server, message, true);
        return;
    }

    const Opcode opcode = message.getOpcode();
    bool send_answer = true;
    try {
        // update per opcode statistics counter.  This can only be reliable
        // after TSIG check succeeds.
        impl_->counters_.inc(message.getOpcode());

        if (opcode == Opcode::NOTIFY()) {
            send_answer = impl_->processNotify(io_message, message, buffer,
                                               tsig_context);
        } else if (opcode == Opcode::UPDATE()) {
            if (impl_->ddns_forwarder_) {
                send_answer = impl_->processUpdate(io_message);
            } else {
                makeErrorMessage(impl_->renderer_, message, buffer,
                                 Rcode::NOTIMP(), tsig_context);
            }
        } else if (opcode != Opcode::QUERY()) {
            LOG_DEBUG(auth_logger, DBG_AUTH_DETAIL, AUTH_UNSUPPORTED_OPCODE)
                      .arg(message.getOpcode().toText());
            makeErrorMessage(impl_->renderer_, message, buffer,
                             Rcode::NOTIMP(), tsig_context);
        } else if (message.getRRCount(Message::SECTION_QUESTION) != 1) {
            makeErrorMessage(impl_->renderer_, message, buffer,
                             Rcode::FORMERR(), tsig_context);
        } else {
            ConstQuestionPtr question = *message.beginQuestion();
            const RRType& qtype = question->getType();
            if (qtype == RRType::AXFR()) {
                send_answer = impl_->processXfrQuery(io_message, message,
                                                     buffer, tsig_context);
            } else if (qtype == RRType::IXFR()) {
                send_answer = impl_->processXfrQuery(io_message, message,
                                                     buffer, tsig_context);
            } else {
                send_answer = impl_->processNormalQuery(io_message, message,
                                                        buffer, tsig_context);
            }
        }
    } catch (const std::exception& ex) {
        LOG_DEBUG(auth_logger, DBG_AUTH_DETAIL, AUTH_RESPONSE_FAILURE)
                  .arg(ex.what());
        makeErrorMessage(impl_->renderer_, message, buffer, Rcode::SERVFAIL());
    } catch (...) {
        LOG_DEBUG(auth_logger, DBG_AUTH_DETAIL, AUTH_RESPONSE_FAILURE_UNKNOWN);
        makeErrorMessage(impl_->renderer_, message, buffer, Rcode::SERVFAIL());
    }
    impl_->resumeServer(server, message, send_answer);
}

bool
AuthSrvImpl::processNormalQuery(const IOMessage& io_message, Message& message,
                                OutputBuffer& buffer,
                                auto_ptr<TSIGContext> tsig_context)
{
    ConstEDNSPtr remote_edns = message.getEDNS();
    const bool dnssec_ok = remote_edns && remote_edns->getDNSSECAwareness();
    const uint16_t remote_bufsize = remote_edns ? remote_edns->getUDPSize() :
        Message::DEFAULT_MAX_UDPSIZE;

    message.makeResponse();
    message.setHeaderFlag(Message::HEADERFLAG_AA);
    message.setRcode(Rcode::NOERROR());

    // Increment query counter.
    incCounter(io_message.getSocket().getProtocol());

    if (remote_edns) {
        EDNSPtr local_edns = EDNSPtr(new EDNS());
        local_edns->setDNSSECAwareness(dnssec_ok);
        local_edns->setUDPSize(AuthSrvImpl::DEFAULT_LOCAL_UDPSIZE);
        message.setEDNS(local_edns);
    }

    try {
        const ConstQuestionPtr question = *message.beginQuestion();
        const boost::shared_ptr<datasrc::ClientList>
            list(getClientList(question->getClass()));
        if (list) {
            const RRType& qtype = question->getType();
            const Name& qname = question->getName();
            query_.process(*list, qname, qtype, message, dnssec_ok);
        } else {
            makeErrorMessage(renderer_, message, buffer, Rcode::REFUSED());
            return (true);
        }
    } catch (const Exception& ex) {
        LOG_ERROR(auth_logger, AUTH_PROCESS_FAIL).arg(ex.what());
        makeErrorMessage(renderer_, message, buffer, Rcode::SERVFAIL());
        return (true);
    }

    RendererHolder holder(renderer_, &buffer);
    const bool udp_buffer =
        (io_message.getSocket().getProtocol() == IPPROTO_UDP);
    renderer_.setLengthLimit(udp_buffer ? remote_bufsize : 65535);
    if (tsig_context.get() != NULL) {
        message.toWire(renderer_, *tsig_context);
    } else {
        message.toWire(renderer_);
    }
    LOG_DEBUG(auth_logger, DBG_AUTH_MESSAGES, AUTH_SEND_NORMAL_RESPONSE)
              .arg(renderer_.getLength()).arg(message);
    return (true);
}

bool
AuthSrvImpl::processXfrQuery(const IOMessage& io_message, Message& message,
                             OutputBuffer& buffer,
                             auto_ptr<TSIGContext> tsig_context)
{
    // Increment query counter.
    incCounter(io_message.getSocket().getProtocol());

    if (io_message.getSocket().getProtocol() == IPPROTO_UDP) {
        LOG_DEBUG(auth_logger, DBG_AUTH_DETAIL, AUTH_AXFR_UDP);
        makeErrorMessage(renderer_, message, buffer, Rcode::FORMERR(),
                         tsig_context);
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

        LOG_DEBUG(auth_logger, DBG_AUTH_DETAIL, AUTH_AXFR_ERROR)
                  .arg(err.what());
        makeErrorMessage(renderer_, message, buffer, Rcode::SERVFAIL(),
                         tsig_context);
        return (true);
    }

    return (false);
}

bool
AuthSrvImpl::processNotify(const IOMessage& io_message, Message& message,
                           OutputBuffer& buffer,
                           std::auto_ptr<TSIGContext> tsig_context)
{
    // The incoming notify must contain exactly one question for SOA of the
    // zone name.
    if (message.getRRCount(Message::SECTION_QUESTION) != 1) {
        LOG_DEBUG(auth_logger, DBG_AUTH_DETAIL, AUTH_NOTIFY_QUESTIONS)
                  .arg(message.getRRCount(Message::SECTION_QUESTION));
        makeErrorMessage(renderer_, message, buffer, Rcode::FORMERR(),
                         tsig_context);
        return (true);
    }
    ConstQuestionPtr question = *message.beginQuestion();
    if (question->getType() != RRType::SOA()) {
        LOG_DEBUG(auth_logger, DBG_AUTH_DETAIL, AUTH_NOTIFY_RRTYPE)
                  .arg(question->getType().toText());
        makeErrorMessage(renderer_, message, buffer, Rcode::FORMERR(),
                         tsig_context);
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
        LOG_DEBUG(auth_logger, DBG_AUTH_DETAIL, AUTH_NO_XFRIN);
        return (false);
    }

    LOG_DEBUG(auth_logger, DBG_AUTH_DETAIL, AUTH_RECEIVED_NOTIFY)
      .arg(question->getName()).arg(question->getClass());

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
            LOG_ERROR(auth_logger, AUTH_ZONEMGR_ERROR)
                      .arg(parsed_answer->str());
            return (false);
        }
    } catch (const Exception& ex) {
        LOG_ERROR(auth_logger, AUTH_ZONEMGR_COMMS).arg(ex.what());
        return (false);
    }

    message.makeResponse();
    message.setHeaderFlag(Message::HEADERFLAG_AA);
    message.setRcode(Rcode::NOERROR());

    RendererHolder holder(renderer_, &buffer);
    if (tsig_context.get() != NULL) {
        message.toWire(renderer_, *tsig_context);
    } else {
        message.toWire(renderer_);
    }
    return (true);
}

bool
AuthSrvImpl::processUpdate(const IOMessage& io_message) {
    // Push the update request to a separate process via the forwarder.
    // On successful push, the request shouldn't be responded from b10-auth,
    // so we return false.
    ddns_forwarder_->push(io_message);
    return (false);
}

void
AuthSrvImpl::incCounter(const int protocol) {
    // Increment query counter.
    if (protocol == IPPROTO_UDP) {
        counters_.inc(AuthCounters::SERVER_UDP_QUERY);
    } else if (protocol == IPPROTO_TCP) {
        counters_.inc(AuthCounters::SERVER_TCP_QUERY);
    } else {
        // unknown protocol
        isc_throw(Unexpected, "Unknown protocol: " << protocol);
    }
}

void
AuthSrvImpl::registerStatisticsValidator() {
    counters_.registerStatisticsValidator(
        boost::bind(&AuthSrvImpl::validateStatistics, this, _1));
}

bool
AuthSrvImpl::validateStatistics(isc::data::ConstElementPtr data) const {
    if (config_session_ == NULL) {
        return (false);
    }
    return (
        config_session_->getModuleSpec().validateStatistics(
            data, true));
}

void
AuthSrvImpl::resumeServer(DNSServer* server, Message& message, bool done) {
    if (done) {
        counters_.inc(message.getRcode());
    }
    server->resume(done);
}

ConstElementPtr
AuthSrv::updateConfig(ConstElementPtr new_config) {
    try {
        // the ModuleCCSession has already checked if we have
        // the correct ElementPtr type as specified in our .spec file
        if (new_config) {
            configureAuthServer(*this, new_config);
        }
        return (isc::config::createAnswer());
    } catch (const isc::Exception& error) {
        LOG_ERROR(auth_logger, AUTH_CONFIG_UPDATE_FAIL).arg(error.what());
        return (isc::config::createAnswer(1, error.what()));
    }
}

ConstElementPtr AuthSrv::getStatistics() const {
    return (impl_->counters_.getStatistics());
}

uint64_t
AuthSrv::getCounter(const AuthCounters::ServerCounterType type) const {
    return (impl_->counters_.getCounter(type));
}

uint64_t
AuthSrv::getCounter(const Opcode opcode) const {
    return (impl_->counters_.getCounter(opcode));
}

uint64_t
AuthSrv::getCounter(const Rcode rcode) const {
    return (impl_->counters_.getCounter(rcode));
}

const AddressList&
AuthSrv::getListenAddresses() const {
    return (impl_->listen_addresses_);
}

void
AuthSrv::setListenAddresses(const AddressList& addresses) {
    // For UDP servers we specify the "SYNC_OK" option because in our usage
    // it can act in the synchronous mode.
    installListenAddresses(addresses, impl_->listen_addresses_, *dnss_,
                           DNSService::SERVER_SYNC_OK);
}

void
AuthSrv::setDNSService(isc::asiodns::DNSServiceBase& dnss) {
    dnss_ = &dnss;
}

void
AuthSrv::setTSIGKeyRing(const boost::shared_ptr<TSIGKeyRing>* keyring) {
    impl_->keyring_ = keyring;
}

void
AuthSrv::createDDNSForwarder() {
    LOG_DEBUG(auth_logger, DBG_AUTH_OPS, AUTH_START_DDNS_FORWARDER);
    impl_->ddns_forwarder_.reset(
        new SocketSessionForwarderHolder("update", impl_->ddns_base_forwarder_));
}

void
AuthSrv::destroyDDNSForwarder() {
    if (impl_->ddns_forwarder_) {
        LOG_DEBUG(auth_logger, DBG_AUTH_OPS, AUTH_STOP_DDNS_FORWARDER);
        impl_->ddns_forwarder_.reset();
    }
}

void
AuthSrv::setClientList(const RRClass& rrclass,
                       const boost::shared_ptr<ConfigurableClientList>& list) {
    if (list) {
        impl_->client_lists_[rrclass] = list;
    } else {
        impl_->client_lists_.erase(rrclass);
    }
}
boost::shared_ptr<ConfigurableClientList>
AuthSrv::getClientList(const RRClass& rrclass) {
    return (impl_->getClientList(rrclass));
}

vector<RRClass>
AuthSrv::getClientListClasses() const {
    vector<RRClass> result;
    for (std::map<RRClass, boost::shared_ptr<ConfigurableClientList> >::
         const_iterator it(impl_->client_lists_.begin());
         it != impl_->client_lists_.end(); ++it) {
        result.push_back(it->first);
    }
    return (result);
}
