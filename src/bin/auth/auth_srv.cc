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

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>

#include <cassert>
#include <iostream>

#include <dns/buffer.h>
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
    std::string db_file_;
    isc::auth::MetaDataSrc data_sources_;
    /// We keep a pointer to the currently running sqlite datasource
    /// so that we can specifically remove that one should the database
    /// file change
    isc::auth::ConstDataSrcPtr cur_datasrc_;
};

AuthSrvImpl::AuthSrvImpl() {
}

AuthSrv::AuthSrv() {
    impl_ = new AuthSrvImpl;
    // set empty (sqlite) data source, once ccsession is up
    // the datasource will be set by the configuration setting
    // (or the default one if none is set)
    impl_->cur_datasrc_ = ConstDataSrcPtr();
    // add static data source
    impl_->data_sources_.addDataSrc(ConstDataSrcPtr(new StaticDataSrc));
}

AuthSrv::~AuthSrv()
{
    delete impl_;
}

int
AuthSrv::processMessage(InputBuffer& request_buffer,
                        Message& message,
                        MessageRenderer& response_renderer,
                        const bool udp_buffer, const bool verbose_mode)
{
    try {
        message.fromWire(request_buffer);
    } catch (...) {
        cerr << "[AuthSrv] parse failed" << endl;
        return (-1);
    }

    if (verbose_mode) {
        cerr << "[AuthSrv] received a message:\n" << message.toText() << endl;
    }

    if (message.getRRCount(Section::QUESTION()) != 1) {
        return (-1);
    }

    const bool dnssec_ok = message.isDNSSECSupported();
    const uint16_t remote_bufsize = message.getUDPSize();

    message.makeResponse();
    message.setHeaderFlag(MessageFlag::AA());
    message.setRcode(Rcode::NOERROR());
    message.setDNSSECSupported(dnssec_ok);
    message.setUDPSize(4096);   // XXX: hardcoding

    Query query(message, dnssec_ok);
    impl_->data_sources_.doQuery(query);

    response_renderer.setLengthLimit(udp_buffer ? remote_bufsize : 65535);
    message.toWire(response_renderer);
    if (verbose_mode) {
        cerr << "sending a response (" <<
            boost::lexical_cast<string>(response_renderer.getLength())
             << " bytes):\n" << message.toText() << endl;
    }

    return (0);
}

ElementPtr
AuthSrv::setDbFile(const isc::data::ElementPtr config) {
    if (config) {
        impl_->db_file_ = config->get("database_file")->stringValue();
        cout << "[AuthSrv] Data source database file: " << impl_->db_file_
             << endl;
    }

    try {
        // create SQL data source
        // config may be empty here; in that case it will load the default
        // database file
        Sqlite3DataSrc* sd = new Sqlite3DataSrc;
        sd->init(config);

        if (impl_->cur_datasrc_) {
            impl_->data_sources_.removeDataSrc(impl_->cur_datasrc_);
        }

        ConstDataSrcPtr csd = ConstDataSrcPtr(sd);
        impl_->data_sources_.addDataSrc(csd);
        impl_->cur_datasrc_ = csd;

        return isc::config::createAnswer(0);
    } catch (isc::Exception error) {
        cout << "[AuthSrv] error: " << error.what() << endl;
        return isc::config::createAnswer(1, error.what());
    }
}

ElementPtr
AuthSrv::updateConfig(isc::data::ElementPtr new_config) {
    ElementPtr answer = isc::config::createAnswer(0);
    if (new_config) {
        // the ModuleCCSession has already checked if we have
        // the correct ElementPtr type as specified in our .spec file
        if (new_config->contains("database_file")) {
            answer = setDbFile(new_config);
        }
    }

    // if we have no sqlite3 data source, use the default
    if (impl_->cur_datasrc_ == NULL) {
        setDbFile(ElementPtr());
    }
    
    return answer;
}
