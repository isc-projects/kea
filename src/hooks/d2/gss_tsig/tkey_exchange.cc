// Copyright (C) 2021-2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <d2srv/d2_log.h>
#include <dns/messagerenderer.h>
#include <dns/opcode.h>
#include <dns/rdataclass.h>
#include <stats/stats_mgr.h>
#include <gss_tsig_context.h>
#include <gss_tsig_key.h>
#include <gss_tsig_log.h>
#include <tkey_exchange.h>
#include <limits>
#include <sstream>

namespace isc {
namespace gss_tsig {

namespace {

// OutputBuffer objects are pre-allocated before data is written to them.
// This is a default number of bytes for the buffers we create within
// TKeyExchange class.
const size_t DEFAULT_BUFFER_SIZE = 4096;

}

using namespace isc::asiolink;
using namespace isc::asiodns;
using namespace isc::dns;
using namespace isc::dns::rdata;
using namespace isc::dns::rdata::generic;
using namespace isc::log;
using namespace isc::stats;
using namespace isc::util;
using namespace std;

string
TKeyExchange::statusToText(Status status) {
    switch (status) {
    case SUCCESS:
        return ("response received and is ok");
    case TIMEOUT:
        return ("no response, timeout");
    case IO_STOPPED:
        return ("IO was stopped");
    case INVALID_RESPONSE:
        return ("response received but invalid");
    case UNSIGNED_RESPONSE:
        return ("response received but not signed");
    case BAD_CREDENTIALS:
        return ("bad client credentials");
    default:
        return ("other, unclassified error");
    }
}

// This class provides the implementation for the TKeyExchange. This allows for
// the separation of the TKeyExchange interface from the implementation details.
// Currently, implementation uses IOFetch object to handle asynchronous
// communication with the DNS. This design may be revisited in the future. If
// implementation is changed, the TKeyExchange API will remain unchanged thanks
// to this separation.
class TKeyExchangeImpl : public IOFetch::Callback {
public:
    /// @brief The TKEY exchange state.
    enum State {
        NONE,     ///< Initial state: no action has been initiated.
        STARTED,  ///< The TKEY exchange has been started.
        STOPPED,  ///< The TKEY exchange has been canceled.
        SUCCESS,  ///< The TKEY exchange has succeeded.
        FAILURE,  ///< The TKEY exchange has failed.
    };

    /// @brief Constructor.
    ///
    /// @param io_service The IOService which handles IO operations.
    /// @param server The server for which the TKEY exchange is performed.
    /// @param key The TKEY being updated.
    /// @param callback Pointer to an object implementing @c TKeyExchange::Callback
    /// class. This object will be called when DNS message exchange completes or
    /// if an error occurs. NULL value disables callback invocation.
    /// @param timeout The timeout for the IO operations.
    /// @param flags The flags used for the TKEY exchange.
    /// @throw BadValue if io_service is null.
    /// @throw BadValue if key's security context has already been used.
    TKeyExchangeImpl(const IOServicePtr& io_service, const DnsServerPtr& server,
                     const GssTsigKeyPtr& key, TKeyExchange::Callback* callback,
                     uint32_t timeout, OM_uint32 flags);

    /// @brief Destructor.
    virtual ~TKeyExchangeImpl();

    /// @brief This internal callback is called when the DNS update message
    /// exchange is complete. It further invokes the external callback provided
    /// by a caller.
    ///
    /// @param result The result of the IOFetch operation.
    virtual void operator()(IOFetch::Result result);

    /// @brief This function handles the repeated communication with the DNS
    /// server trying to complete the TKEY exchange.
    void doExchange();

    /// @brief This function cancels the started TKEY exchange.
    void cancel();

    /// @brief Gets IO service.
    ///
    /// @return IOService object, used for all ASIO operations.
    isc::asiolink::IOServicePtr getIOService() {
        return (io_service_);
    }

    /// @brief Sets IO service.
    ///
    /// @param io_service IOService object, used for all ASIO operations.
    void setIOService(const isc::asiolink::IOServicePtr& io_service) {
        io_service_ = io_service;
    }

private:
    /// @brief Internal exchange function which handles all remaining steps of
    /// the key exchange.
    ///
    /// @Note If an error occurs, or the exchange succeeds, the internal status
    /// is updated and the user callback is called with appropriate value.
    ///
    /// @param intoken The buffer used to continue the key exchange.
    void doExchangeInternal(GssApiBufferPtr intoken);

    /// @brief Call the user callback with the current internal status.
    ///
    /// @param status The status of the TKEY exchange.
    void callCallback(TKeyExchange::Status status);

    /// @brief Acquire credentials.
    void acquireCredentials();

    /// @brief Read the TKEY received from the DNS server.
    ///
    /// @param outbuf The buffer used to read the TKEY value.
    /// @return The buffer containing the TKEY value.
    GssApiBufferPtr readTKey(const OutputBufferPtr& outbuf);

    /// @brief Verify the received TKEY.
    ///
    /// @return true if the TKEY passes validation, false otherwise.
    bool verifyTKey();

    /// @brief Create DNS request for the TKEY.
    ///
    /// @param outtoken The buffer containing the TKEY used to create the DNS
    /// request.
    void createTKeyRequest(const GssApiBufferPtr& outtoken);

    /// @brief Update statistics.
    ///
    /// @param stat The statistics name.
    void incrStats(const string& stat);

    /// @brief The IOService which handles IO operations.
    IOServicePtr io_service_;

    /// @brief The state of the TKEY exchange.
    State state_;

    /// @brief A buffer holding response from a DNS.
    OutputBufferPtr in_buf_;

    /// @brief A buffer holding request for a DNS.
    OutputBufferPtr out_buf_;

    /// @brief A caller-supplied external callback which is invoked when DNS
    /// message exchange is complete or interrupted.
    TKeyExchange::Callback* callback_;

    /// @brief The DNS server which requires TKEY exchange.
    DnsServerPtr server_;

    /// @brief The GSS-TSIG key.
    GssTsigKeyPtr key_;

    /// @brief The GSS-TSIG flags used for the TKEY exchange.
    OM_uint32 flags_;

    /// @brief The credentials.
    GssApiCredPtr cred_;

    /// @brief The DNS message used to communicate with the DNS server.
    MessagePtr msg_;

    /// @brief The timeout for the IO operations.
    uint32_t timeout_;

    /// @brief The IOFetch used to do the TKEY exchange.
    IOFetchPtr io_fetch_;
};

TKeyExchangeImpl::TKeyExchangeImpl(const IOServicePtr& io_service,
                                   const DnsServerPtr& server,
                                   const GssTsigKeyPtr& key,
                                   TKeyExchange::Callback* callback,
                                   uint32_t timeout, OM_uint32 flags)
    : io_service_(io_service), state_(NONE), in_buf_(), out_buf_(),
      callback_(callback), server_(server), key_(key), flags_(flags), cred_(),
      msg_(), timeout_(timeout) {
    if (!io_service) {
        isc_throw(BadValue, "null IOService");
    }
    if (key->getSecCtx().get() != GSS_C_NO_CONTEXT) {
        isc_throw(BadValue, "wrong security context state");
    }
}

TKeyExchangeImpl::~TKeyExchangeImpl() {
    cancel();
}

void
TKeyExchangeImpl::operator()(IOFetch::Result result) {
    // Get the status from IO. If no success, we just call user's callback
    // and pass the status code.
    GssApiBufferPtr intoken;
    switch (result) {
    case IOFetch::SUCCESS:
        intoken = readTKey(out_buf_);
        if (!intoken || intoken->empty()) {
            LOG_ERROR(gss_tsig_logger, TKEY_EXCHANGE_FAIL_EMPTY_IN_TOKEN);
            incrStats("tkey-error");
            callCallback(TKeyExchange::INVALID_RESPONSE);
        } else {
            // The TKEY payload from the server response is used for
            // the GSS-API security context establishment.

            doExchangeInternal(intoken);
        }
        return;

    case IOFetch::TIME_OUT:
        LOG_ERROR(gss_tsig_logger, TKEY_EXCHANGE_FAIL_IO_TIMEOUT);
        incrStats("tkey-timeout");
        callCallback(TKeyExchange::TIMEOUT);
        return;

    case IOFetch::STOPPED:
        LOG_ERROR(gss_tsig_logger, TKEY_EXCHANGE_FAIL_IO_STOPPED);
        incrStats("tkey-error");
        callCallback(TKeyExchange::IO_STOPPED);
        return;

    default:
        LOG_ERROR(gss_tsig_logger, TKEY_EXCHANGE_FAIL_IO_ERROR)
            .arg(result);
        incrStats("tkey-error");
        callCallback(TKeyExchange::OTHER);
        return;
    }
}

void
TKeyExchangeImpl::acquireCredentials() {
    const string& cred_princ = server_->getClientPrincipal();
    if (cred_princ.empty()) {
        return;
    }

    OM_uint32 lifetime(0);
    GssApiName cname(cred_princ);
    cred_.reset(new GssApiCred(cname, GSS_C_INITIATE, lifetime));
    if (lifetime == 0) {
        isc_throw(GssCredExpired, "credentials expired for " << cred_princ);
    }
}

bool
TKeyExchangeImpl::verifyTKey() {
    // The last TKEY response must be signed.
    const TSIGRecord* tsig = msg_->getTSIGRecord();
    if (!tsig) {
        LOG_ERROR(gss_tsig_logger, TKEY_EXCHANGE_FAIL_NOT_SIGNED);
        return (false);
    }
    GssTsigContextPtr tkey_ctx(new GssTsigContext(*key_));
    tkey_ctx->setState(TSIGContext::SENT_REQUEST);
    TSIGError error = tkey_ctx->verify(tsig, out_buf_->getData(),
                                       out_buf_->getLength());
    if (error != TSIGError::NOERROR()) {
        LOG_ERROR(gss_tsig_logger, TKEY_EXCHANGE_FAILED_TO_VERIFY);
        return (false);
    }

    LOG_DEBUG(gss_tsig_logger, DBGLVL_TRACE_BASIC, TKEY_EXCHANGE_VERIFIED);

    return (true);
}

void
TKeyExchangeImpl::createTKeyRequest(const GssApiBufferPtr& outtoken) {
    // Create a TKEY request.
    msg_.reset(new Message(Message::RENDER));
    // QID is added by IOFetch using the cryptolink::generateQid.
    msg_->setOpcode(Opcode::QUERY());
    msg_->setRcode(Rcode::NOERROR());
    msg_->setHeaderFlag(Message::HEADERFLAG_QR, false);
    msg_->setHeaderFlag(Message::HEADERFLAG_RD, false);

    msg_->addQuestion(Question(key_->getKeyName(), RRClass::ANY(),
                               RRType::TKEY()));

    // Create the TKEY Resource Record.
    RRsetPtr tkey_rrset(new RRset(key_->getKeyName(), RRClass::ANY(),
                                  RRType::TKEY(), RRTTL(0)));
    Name algorithm("gss-tsig.");
    uint32_t inception = key_->getInception32();
    uint32_t expire = key_->getExpire32();
    uint16_t mode = TKEY::GSS_API_MODE;
    uint16_t error = Rcode::NOERROR().getCode();
    size_t key_length = outtoken->getLength();
    if (key_length > std::numeric_limits<uint16_t>::max()) {
        isc_throw(BadValue, "TKEY value too long: " << key_length);
    }
    uint16_t key_len = static_cast<uint16_t>(key_length);
    ConstRdataPtr tkey_rdata(new TKEY(algorithm, inception, expire, mode, error,
                                      key_len, outtoken->getValue(), 0, 0));
    tkey_rrset->addRdata(tkey_rdata);
    msg_->addRRset(Message::SECTION_ADDITIONAL, tkey_rrset);

    // Encode the TKEY request.
    MessageRenderer renderer;
    in_buf_.reset(new OutputBuffer(DEFAULT_BUFFER_SIZE));
    renderer.setBuffer(in_buf_.get());
    renderer.setLengthLimit(DEFAULT_BUFFER_SIZE);
    msg_->toWire(renderer);
}

void
TKeyExchangeImpl::callCallback(TKeyExchange::Status status) {
    // Once we are done with internal business, let's call a callback supplied
    // by a caller.
    if (callback_) {
        (*callback_)(status);
    }
    if (status == TKeyExchange::SUCCESS) {
        state_ = SUCCESS;
    } else {
        state_ = FAILURE;
    }
}

void
TKeyExchangeImpl::doExchangeInternal(GssApiBufferPtr intoken) {
    GssApiName named_gname(server_->getServerPrincipal());

    GssApiBufferPtr outtoken(new GssApiBuffer());
    OM_uint32 lifetime(0);
    bool ret;
    try {
        ret = key_->getSecCtx().init(cred_, named_gname, flags_, *intoken,
                                     *outtoken, lifetime);
    } catch (const isc::Exception& ex) {
        LOG_ERROR(gss_tsig_logger, TKEY_EXCHANGE_FAIL_TO_INIT)
            .arg(ex.what());
        incrStats("tkey-error");
        callCallback(TKeyExchange::OTHER);
        return;
    }
    if (ret) {
        // Established.
        if (!outtoken->empty()) {
            // The RFC is not consistent about this case because it specifies it
            // and at the same time requires the server to sign the last response
            // so the first security context to be established is the server one
            // and any further exchange does not make sense...
            LOG_DEBUG(gss_tsig_logger, DBGLVL_TRACE_BASIC, TKEY_EXCHANGE_OUT_TOKEN_NOT_EMPTY);
        }
        lifetime = key_->getSecCtx().getLifetime();
        if (lifetime < server_->getKeyLifetime()) {
            ostringstream msg;
            msg << "too short credential lifetime: " << lifetime
                << " < " << server_->getKeyLifetime();
            LOG_ERROR(gss_tsig_logger, BAD_CLIENT_CREDENTIALS)
                .arg(msg.str());
            incrStats("tkey-error");
            callCallback(TKeyExchange::BAD_CREDENTIALS);
            return;
        }
        LOG_DEBUG(gss_tsig_logger, DBGLVL_TRACE_BASIC, TKEY_EXCHANGE_VALID)
            .arg(key_->getSecCtx().getLifetime());

        if (verifyTKey()) {
            incrStats("tkey-success");
            callCallback(TKeyExchange::SUCCESS);
        } else {
            incrStats("tkey-error");
            callCallback(TKeyExchange::UNSIGNED_RESPONSE);
        }

        return;
    }

    if (outtoken->empty()) {
        LOG_ERROR(gss_tsig_logger, TKEY_EXCHANGE_FAIL_EMPTY_OUT_TOKEN);
        incrStats("tkey-error");
        callCallback(TKeyExchange::INVALID_RESPONSE);
        return;
    }

    createTKeyRequest(outtoken);
    LOG_DEBUG(gss_tsig_logger, DBGLVL_TRACE_BASIC, TKEY_EXCHANGE_SEND_MESSAGE)
        .arg(in_buf_->getLength());
    incrStats("tkey-sent");

    // Send the TKEY request.
    IOAddress io_addr = server_->getIpAddress();
    out_buf_.reset(new OutputBuffer(DEFAULT_BUFFER_SIZE));

    // Do not use msg because IOFetch code will mess it!
    io_fetch_.reset(new IOFetch(server_->getKeyProto(), io_service_, in_buf_,
                                io_addr, server_->getPort(), out_buf_,
                                this, static_cast<int>(timeout_)));
    io_service_->post(*io_fetch_);
}

void
TKeyExchangeImpl::doExchange() {
    if (state_ != NONE) {
        isc_throw(InvalidOperation, "initiating exchange from invalid state");
    }

    state_ = STARTED;

    // start acquire credentials
    try {
        acquireCredentials();
    } catch (const isc::Exception& ex) {
        LOG_ERROR(gss_tsig_logger, BAD_CLIENT_CREDENTIALS)
            .arg(ex.what());
        incrStats("tkey-error");
        callCallback(TKeyExchange::BAD_CREDENTIALS);
        return;
    }

    GssApiBufferPtr intoken(new GssApiBuffer());
    doExchangeInternal(intoken);
}

void
TKeyExchangeImpl::cancel() {
    if (io_fetch_) {
        io_fetch_->stop();
    }
    state_ = STOPPED;
}

GssApiBufferPtr
TKeyExchangeImpl::readTKey(const OutputBufferPtr& outbuf) {
    // Decode the TKEY response.
    size_t msg_len = outbuf->getLength();
    if (msg_len == 0) {
        LOG_ERROR(gss_tsig_logger, TKEY_EXCHANGE_FAIL_EMPTY_RESPONSE);
        return (GssApiBufferPtr());
    }
    const void* msg_buf = outbuf->getData();
    if (!msg_buf) {
        LOG_ERROR(gss_tsig_logger, TKEY_EXCHANGE_FAIL_NULL_RESPONSE);
        return (GssApiBufferPtr());
    }

    LOG_DEBUG(gss_tsig_logger, DBGLVL_TRACE_BASIC, TKEY_EXCHANGE_RECEIVE_MESSAGE)
        .arg(msg_len);

    msg_.reset(new Message(Message::PARSE));
    InputBuffer recv_buf(msg_buf, msg_len);
    msg_->fromWire(recv_buf);

    // Validate the TKEY response.
    if (!msg_->getHeaderFlag(Message::HEADERFLAG_QR)) {
        LOG_DEBUG(gss_tsig_logger, DBGLVL_TRACE_BASIC, TKEY_EXCHANGE_NOT_A_RESPONSE);
    }
    if (msg_->getRcode() != Rcode::NOERROR()) {
        LOG_ERROR(gss_tsig_logger, TKEY_EXCHANGE_FAIL_RESPONSE_ERROR)
            .arg(msg_->getRcode().toText());
        return (GssApiBufferPtr());
    }
    if (msg_->getOpcode() != Opcode::QUERY()) {
        LOG_ERROR(gss_tsig_logger, TKEY_EXCHANGE_FAIL_WRONG_RESPONSE_OPCODE)
            .arg(msg_->getOpcode());
        return (GssApiBufferPtr());
    }
    // According to RFC3645, the TKEY is found in the ANSWER section.
    if (msg_->getRRCount(Message::SECTION_ANSWER) != 1) {
        LOG_ERROR(gss_tsig_logger, TKEY_EXCHANGE_FAIL_WRONG_RESPONSE_ANSWER_COUNT)
            .arg(msg_->getRRCount(Message::SECTION_ANSWER));
        return (GssApiBufferPtr());
    }
    RRsetPtr rrset = *msg_->beginSection(Message::SECTION_ANSWER);
    if (!rrset) {
        LOG_ERROR(gss_tsig_logger, TKEY_EXCHANGE_FAIL_NO_RESPONSE_ANSWER);
        return (GssApiBufferPtr());
    }
    if (rrset->getClass() != RRClass::ANY()) {
        LOG_DEBUG(gss_tsig_logger, DBGLVL_TRACE_BASIC, TKEY_EXCHANGE_ANSWER_CLASS)
            .arg(rrset->getClass().toText());
    }
    if (rrset->getType() != RRType::TKEY()) {
        LOG_ERROR(gss_tsig_logger, TKEY_EXCHANGE_FAIL_WRONG_RESPONSE_ANSWER_TYPE)
            .arg(rrset->getType().toText());
        return (GssApiBufferPtr());
    }
    if (rrset->getTTL() != RRTTL(0)) {
        LOG_DEBUG(gss_tsig_logger, DBGLVL_TRACE_BASIC, TKEY_EXCHANGE_RESPONSE_TTL)
            .arg(rrset->getTTL().toText());
    }
    if (rrset->getRdataCount() != 1) {
        LOG_DEBUG(gss_tsig_logger, DBGLVL_TRACE_BASIC, TKEY_EXCHANGE_RDATA_COUNT)
            .arg(rrset->getRdataCount());
        if (rrset->getRdataCount() == 0) {
            LOG_ERROR(gss_tsig_logger, TKEY_EXCHANGE_FAIL_NO_RDATA);
            return (GssApiBufferPtr());
        }
    }
    auto rdata_it = rrset->getRdataIterator();
    const TKEY& tkey = dynamic_cast<const TKEY&>(rdata_it->getCurrent());
    if (tkey.getError() != Rcode::NOERROR_CODE) {
        LOG_ERROR(gss_tsig_logger, TKEY_EXCHANGE_FAIL_TKEY_ERROR)
            .arg(tkey.getError());
        return (GssApiBufferPtr());
    }
    return (GssApiBufferPtr(new GssApiBuffer(tkey.getKeyLen(), tkey.getKey())));
}

void
TKeyExchangeImpl::incrStats(const string& stat) {
    StatsMgr& mgr = StatsMgr::instance();
    mgr.addValue(stat, static_cast<int64_t>(1));
    if (server_) {
        mgr.addValue(StatsMgr::generateName("server", server_->getID(), stat),
                     static_cast<int64_t>(1));
    }
}

const OM_uint32 TKeyExchange::TKEY_EXCHANGE_FLAGS = (GSS_C_REPLAY_FLAG | GSS_C_MUTUAL_FLAG | GSS_C_INTEG_FLAG);
const uint32_t TKeyExchange::TKEY_EXCHANGE_IO_TIMEOUT = 3000;

TKeyExchange::TKeyExchange(const IOServicePtr& io_service,
                           const DnsServerPtr& server, const GssTsigKeyPtr& key,
                           Callback* callback, uint32_t timeout, OM_uint32 flags)
    : impl_(new TKeyExchangeImpl(io_service, server, key, callback, timeout, flags)) {
}

TKeyExchange::~TKeyExchange() {
    cancel();
}

void
TKeyExchange::doExchange() {
    impl_->doExchange();
}

void
TKeyExchange::cancel() {
    impl_->cancel();
}

IOServicePtr
TKeyExchange::getIOService() {
    return (impl_->getIOService());
}

void
TKeyExchange::setIOService(const IOServicePtr io_service) {
    impl_->setIOService(io_service);
}

} // namespace gss_tsig
} // namespace isc
