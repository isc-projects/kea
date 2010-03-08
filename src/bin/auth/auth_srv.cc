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

#include <auth/query.h>
#include <auth/data_source.h>
#include <auth/data_source_static.h>
#include <auth/data_source_sqlite3.h>

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
    std::string _db_file;
    isc::auth::MetaDataSrc data_sources;
};

AuthSrvImpl::AuthSrvImpl() {
    // add static data source
    data_sources.addDataSrc(ConstDataSrcPtr(new StaticDataSrc));

    // add SQL data source
    Sqlite3DataSrc* sd = new Sqlite3DataSrc;
    sd->init();
    data_sources.addDataSrc(ConstDataSrcPtr(sd));
}

AuthSrv::AuthSrv()
{
    impl_ = new AuthSrvImpl;
}

AuthSrv::~AuthSrv()
{
    delete impl_;
}

int
AuthSrv::processMessage(InputBuffer& request_buffer,
                        Message& message,
                        MessageRenderer& response_renderer,
                        const bool udp_buffer)
{
    try {
        message.fromWire(request_buffer);
    } catch (...) {
        cerr << "[AuthSrv] parse failed" << endl;
        return (-1);
    }

    cout << "[AuthSrv] received a message:\n" << message.toText() << endl;

    if (message.getRRCount(Section::QUESTION()) != 1) {
        return (-1);
    }

    bool dnssec_ok = message.isDNSSECSupported();
    // unused for now.  should set this to renderer for truncation
    uint16_t remote_bufsize = message.getUDPSize();

    message.makeResponse();
    message.setHeaderFlag(MessageFlag::AA());
    message.setRcode(Rcode::NOERROR());
    message.setDNSSECSupported(dnssec_ok);
    message.setUDPSize(4096);   // XXX: hardcoding

    Query query(message, dnssec_ok);
    impl_->data_sources.doQuery(query);

    response_renderer.setLengthLimit(udp_buffer ? remote_bufsize : 65535);
    message.toWire(response_renderer);
    cout << "sending a response (" <<
        boost::lexical_cast<string>(response_renderer.getLength())
         << " bytes):\n" << message.toText() << endl;

    return (0);
}

void
AuthSrv::setDbFile(const std::string& db_file)
{
    cout << "Change data source file, call our data source's function to now read " << db_file << endl;
    impl_->_db_file = db_file;
}

ElementPtr
AuthSrv::updateConfig(isc::data::ElementPtr new_config)
{
    if (new_config) {
        // the ModuleCCSession has already checked if we have
        // the correct ElementPtr type as specified in our .spec file
        if (new_config->contains("database_file")) {
            // We only get this if the value has actually changed.
            setDbFile(new_config->get("database_file")->stringValue());
        }
    }
    
    return isc::config::createAnswer(0);
}
