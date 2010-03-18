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

#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

#include <exceptions/exceptions.h>

#include <dns/buffer.h>
#include <dns/exceptions.h>
#include <dns/messagerenderer.h>
#include <dns/name.h>
#include <dns/question.h>
#include <dns/rrset.h>
#include <dns/rrttl.h>
#include <dns/message.h>
#include <config/ccsession.h>
#include <cc/data.h>
#include <exceptions/exceptions.h>

#include <auth/query.h>
#include <auth/data_source.h>
#include <auth/static_datasrc.h>
#include <auth/sqlite3_datasrc.h>

#include <cc/data.h>

#include "common.h"
#include "auth_srv.h"

#include <boost/lexical_cast.hpp>

using namespace std;

using namespace isc;
using namespace isc::auth;
using namespace isc::dns;
using namespace isc::dns::rdata;
using namespace isc::data;
using namespace isc::config;

class AuthSrvImpl {
private:
    // prohibit copy
    AuthSrvImpl(const AuthSrvImpl& source);
    AuthSrvImpl& operator=(const AuthSrvImpl& source);
public:
    AuthSrvImpl();

    isc::data::ElementPtr setDbFile(const isc::data::ElementPtr config);

    std::string db_file_;
    ModuleCCSession* cs_;
    MetaDataSrc data_sources_;
    /// We keep a pointer to the currently running sqlite datasource
    /// so that we can specifically remove that one should the database
    /// file change
    ConstDataSrcPtr cur_datasrc_;

    bool verbose_mode_;

    /// Currently non-configurable, but will be.
    static const uint16_t DEFAULT_LOCAL_UDPSIZE = 4096;
};

AuthSrvImpl::AuthSrvImpl() : cs_(NULL), verbose_mode_(false)
{
    // cur_datasrc_ is automatically initialized by the default constructor,
    // effectively being an empty (sqlite) data source.  once ccsession is up
    // the datasource will be set by the configuration setting

    // add static data source
    data_sources_.addDataSrc(ConstDataSrcPtr(new StaticDataSrc));
}

AuthSrv::AuthSrv() : impl_(new AuthSrvImpl) {
}

AuthSrv::~AuthSrv() {
    delete impl_;
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

    // If this is an error to a query, we should also copy the question section.
    if (opcode == Opcode::QUERY()) {
        questions.assign(message.beginQuestion(), message.endQuestion());
    }

    message.clear(Message::RENDER);
    message.setQid(qid);
    message.setOpcode(opcode);
    message.setHeaderFlag(MessageFlag::QR());
    message.setUDPSize(AuthSrvImpl::DEFAULT_LOCAL_UDPSIZE);
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
        cerr << "sending an error response (" <<
            boost::lexical_cast<string>(renderer.getLength())
             << " bytes):\n" << message.toText() << endl;
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
AuthSrv::setConfigSession(ModuleCCSession* cs) {
    impl_->cs_ = cs;
}

ModuleCCSession*
AuthSrv::configSession() const {
    return (impl_->cs_);
}

bool
AuthSrv::processMessage(InputBuffer& request_buffer, Message& message,
                        MessageRenderer& response_renderer,
                        const bool udp_buffer)
{
    // First, check the header part.  If we fail even for the base header,
    // just drop the message.
    try {
        message.parseHeader(request_buffer);

        // Ignore all responses.
        if (message.getHeaderFlag(MessageFlag::QR())) {
            if (impl_->verbose_mode_) {
                cerr << "received unexpected response, ignoring" << endl;
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
            cerr << "returning " <<  error.getRcode().toText() << ": "
                 << error.what() << endl;
        }
        makeErrorMessage(message, response_renderer, error.getRcode(),
                         impl_->verbose_mode_);
        return (true);
    } catch (const Exception& ex) {
        if (impl_->verbose_mode_) {
            cerr << "returning SERVFAIL: " << ex.what() << endl;
        }
        makeErrorMessage(message, response_renderer, Rcode::SERVFAIL(),
                         impl_->verbose_mode_);
        return (true);
    } // other exceptions will be handled at a higher layer.

    if (impl_->verbose_mode_) {
        cerr << "[AuthSrv] received a message:\n" << message.toText() << endl;
    }

    // Perform further protocol-level validation.

    // In this implementation, we only support normal queries
    if (message.getOpcode() != Opcode::QUERY()) {
        if (impl_->verbose_mode_) {
            cerr << "unsupported opcode" << endl;
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

    const bool dnssec_ok = message.isDNSSECSupported();
    const uint16_t remote_bufsize = message.getUDPSize();

    message.makeResponse();
    message.setHeaderFlag(MessageFlag::AA());
    message.setRcode(Rcode::NOERROR());
    message.setDNSSECSupported(dnssec_ok);
    message.setUDPSize(AuthSrvImpl::DEFAULT_LOCAL_UDPSIZE);

    try {
        Query query(message, dnssec_ok);
        impl_->data_sources_.doQuery(query);
    } catch (const Exception& ex) {
        if (impl_->verbose_mode_) {
            cerr << "Internal error, returning SERVFAIL: " << ex.what() << endl;
        }
        makeErrorMessage(message, response_renderer, Rcode::SERVFAIL(),
                         impl_->verbose_mode_);
        return (true);
    }

    response_renderer.setLengthLimit(udp_buffer ? remote_bufsize : 65535);
    message.toWire(response_renderer);
    if (impl_->verbose_mode_) {
        cerr << "sending a response (" <<
            boost::lexical_cast<string>(response_renderer.getLength())
             << " bytes):\n" << message.toText() << endl;
    }

    return (true);
}

ElementPtr
AuthSrvImpl::setDbFile(const isc::data::ElementPtr config) {
    ElementPtr answer = isc::config::createAnswer();
    ElementPtr final;

    if (config && config->contains("database_file")) {
        db_file_ = config->get("database_file")->stringValue();
        final = config;
    } else if (cs_ != NULL) {
        bool is_default;
        string item("database_file");
        ElementPtr value = cs_->getValue(is_default, item);
        db_file_ = value->stringValue();
        final = Element::createFromString("{}");
        final->set(item, value);
    } else {
        return (answer);
    }

    if (verbose_mode_) {
        cerr << "[AuthSrv] Data source database file: " << db_file_ << endl;
    }

    // create SQL data source
    // Note: the following step is tricky to be exception-safe and to ensure
    // exception guarantee: We first need to perform all operations that can
    // fail, while acquiring resources in the RAII manner.  We then perform
    // delete and swap operations which should not fail.
    DataSrcPtr datasrc_ptr(DataSrcPtr(new Sqlite3DataSrc));
    datasrc_ptr->init(final);
    data_sources_.addDataSrc(datasrc_ptr);

    // The following code should be exception free.
    if (cur_datasrc_ != NULL) {
        data_sources_.removeDataSrc(cur_datasrc_);
    }
    cur_datasrc_ = datasrc_ptr;

    return (answer);
}

ElementPtr
AuthSrv::updateConfig(isc::data::ElementPtr new_config) {
    try {
        // the ModuleCCSession has already checked if we have
        // the correct ElementPtr type as specified in our .spec file
        ElementPtr answer = isc::config::createAnswer();
        answer = impl_->setDbFile(new_config);

        return answer;
    } catch (const isc::Exception& error) {
        if (impl_->verbose_mode_) {
            cerr << "[AuthSrv] error: " << error.what() << endl;
        }
        return isc::config::createAnswer(1, error.what());
    }
}
