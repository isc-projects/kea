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

#include "common.h"
#include "auth_srv.h"

#include <boost/lexical_cast.hpp>

using namespace std;

using namespace isc::auth;
using namespace isc::dns;
using namespace isc::dns::rdata;
using namespace isc::data;
using namespace isc::config;

AuthSrv::AuthSrv(int port)
{
    int s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (s < 0) {
        throw FatalError("failed to open socket");
    }

    struct sockaddr_in sin;
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons(port);

    socklen_t sa_len = sizeof(sin);
#ifdef HAVE_SIN_LEN
    sin.sin_len = sa_len;
#endif

    if (bind(s, (struct sockaddr *)&sin, sa_len) < 0) {
        throw FatalError("could not bind socket");
    }

    sock = s;

    // add static data source
    data_src.addDataSrc(new StaticDataSrc);

    // add SQL data source
    Sqlite3DataSrc* sd = new Sqlite3DataSrc;
    sd->init();
    data_src.addDataSrc(sd);
}

void
AuthSrv::processMessage()
{
    struct sockaddr_storage ss;
    socklen_t sa_len = sizeof(ss);
    struct sockaddr* sa = static_cast<struct sockaddr*>((void*)&ss);
    int s = sock;
    char recvbuf[4096];
    int cc;

    if ((cc = recvfrom(s, recvbuf, sizeof(recvbuf), 0, sa, &sa_len)) > 0) {
        Message msg(Message::PARSE);
        InputBuffer buffer(recvbuf, cc);

        try {
            msg.fromWire(buffer);
        } catch (...) {
            cerr << "[AuthSrv] parse failed" << endl;
            return;
        }

        cout << "[AuthSrv] received a message:\n" << msg.toText() << endl;

        if (msg.getRRCount(Section::QUESTION()) != 1) {
            return;
        }

        bool dnssec_ok = msg.isDNSSECSupported();
        uint16_t remote_bufsize = msg.getUDPSize();

        msg.makeResponse();
        msg.setHeaderFlag(MessageFlag::AA());
        msg.setRcode(Rcode::NOERROR());
        msg.setDNSSECSupported(dnssec_ok);
        msg.setUDPSize(sizeof(recvbuf));

        // do the DataSource call here
        data_src.doQuery(Query(msg, dnssec_ok));

        OutputBuffer obuffer(remote_bufsize);
        MessageRenderer renderer(obuffer);
        msg.toWire(renderer);
        cout << "sending a response (" <<
            boost::lexical_cast<string>(obuffer.getLength())
                  << " bytes):\n" << msg.toText() << endl;
        sendto(s, obuffer.getData(), obuffer.getLength(), 0, sa, sa_len);
    }
}

void
AuthSrv::setDbFile(const std::string& db_file)
{
    cout << "Change data source file, call our data source's function to now read " << db_file << endl;
    _db_file = db_file;
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
