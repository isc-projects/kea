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

#include <stdexcept>
#include <string.h>

#include <cc/cpp/data.h>
#include <cc/cpp/session.h>

using std::string;

class SessionManager {
public:
    SessionManager();
private:
    ISC::CC::Session session_;
};

SessionManager::SessionManager() :
    session_(ISC::CC::Session())
{
    try {
        session_.establish();
        session_.subscribe("ParkingLot");
        session_.subscribe("Boss");
    } catch (...) {
        throw std::runtime_error("SessionManager: failed to open sessions");
    }
}

std::pair<string, string>
getCommand(ISC::CC::Session& session)
{
    ISC::Data::ElementPtr ep, routing, data;

    session.group_recvmsg(routing, data, false);
    ep = data->get("zone_added");
    if (ep != NULL) {
        return std::pair<string, string>("zone_added", ep->string_value());
    }
    ep = data->get("zone_deleted");
    if (ep != NULL) {
        return std::pair<string, string>("zone_deleted", ep->string_value());
    }
    ep = data->get("shutdown");
    if (ep != NULL) {
        return std::pair<string, string>("shutdown", "");
    }
}
