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

#include <algorithm>
#include <set>
#include <iostream>

#include <dns/cpp/buffer.h>
#include <dns/cpp/messagerenderer.h>
#include <dns/cpp/name.h>
#include <dns/cpp/question.h>
#include <dns/cpp/rrset.h>
#include <dns/cpp/rrttl.h>
#include <dns/cpp/message.h>

#include <cc/cpp/data.h>

#include "common.h"
#include "auth_srv.h"

#include <boost/lexical_cast.hpp>
#include <boost/foreach.hpp>

using namespace std;

using namespace isc::dns;
using namespace isc::dns::rdata;
using namespace isc::data;

AuthSrv::AuthSrv(int port) {
    int s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (s < 0)
        throw FatalError("failed to open socket");

    struct sockaddr_in sin;
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons(port);

    socklen_t sa_len = sizeof(sin);
#ifdef HAVE_SIN_LEN
    sin.sin_len = sa_len;
#endif

    if (bind(s, (struct sockaddr *)&sin, sa_len) < 0)
        throw FatalError("could not bind socket");

    sock = s;
}

void
AuthSrv::processMessage() {
    struct sockaddr_storage ss;
    socklen_t sa_len = sizeof(ss);
    struct sockaddr* sa = static_cast<struct sockaddr*>((void*)&ss);
    int s = sock;
    Message msg;
    char recvbuf[4096];
    int cc;

    if ((cc = recvfrom(s, recvbuf, sizeof(recvbuf), 0, sa, &sa_len)) > 0) {
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

        QuestionPtr query = *msg.beginQuestion();

        msg.makeResponse();
        msg.setHeaderFlag(MessageFlag::AA());
        msg.setRcode(Rcode::NOERROR());

        // do the DataSource call here
        Query q = Query(msg, false);
        data_src.runQuery(q);

        OutputBuffer obuffer(4096);
        MessageRenderer renderer(obuffer);
        msg.toWire(renderer);
        cout << "sending a response (" <<
            boost::lexical_cast<string>(obuffer.getLength())
                  << " bytes):\n" << msg.toText() << endl;
        sendto(s, obuffer.getData(), obuffer.getLength(), 0, sa, sa_len);
    }
}

ElementPtr
AuthSrv::updateConfig(isc::data::ElementPtr config) {
    //if (config->contains("port")) {
        // todo: what to do with port change. restart automatically?
        // ignore atm
    //}
    return isc::data::Element::createFromString("{ \"result\": [0] }");
}
