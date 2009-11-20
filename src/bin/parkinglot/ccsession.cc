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
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#include <iostream>
#include <sstream>

#include <boost/foreach.hpp>

#include <cc/cpp/data.h>
#include <cc/cpp/session.h>

#include "common.h"
#include "ccsession.h"

using namespace std;

using ISC::Data::Element;
using ISC::Data::ElementPtr;

CommandSession::CommandSession() :
    session_(ISC::CC::Session())
{
    try {
        session_.establish();
        session_.subscribe("ParkingLot", "*");
        session_.subscribe("Boss", "ParkingLot");
        session_.subscribe("ConfigManager", "*", "meonly");
        session_.subscribe("statistics", "*", "meonly");
    } catch (...) {
        throw std::runtime_error("SessionManager: failed to open sessions");
    }
}

int
CommandSession::getSocket()
{
    return (session_.getSocket());
}

std::pair<std::string, std::string>
CommandSession::getCommand(int counter) {
    ElementPtr cmd, routing, data, ep;
    string s;

    session_.group_recvmsg(routing, data, false);
    string channel = routing->get("group")->string_value();

    if (channel == "statistics") {
        cmd = data->get("command");
        if (cmd != NULL && cmd->string_value() == "getstat") {
            struct timeval now;
            ElementPtr resp = Element::create(std::map<std::string,
                                              ElementPtr>());
            gettimeofday(&now, NULL);
            resp->set("sent", Element::create(now.tv_sec +
                                              (double)now.tv_usec / 1000000));
            resp->set("counter", Element::create(counter));
            session_.group_sendmsg(resp, "statistics");
        }
    } else {
        cmd = data->get("zone_added");
        if (cmd != NULL)
            return std::pair<string, string>("addzone", cmd->string_value());
        cmd = data->get("zone_deleted");
        if (cmd != NULL) {
            return std::pair<string, string>("delzone", cmd->string_value());
        }
        cmd = data->get("command");
        if (cmd != NULL) {
            if (cmd->get_type() == Element::string && cmd->string_value() == "shutdown") {
                return std::pair<string, string>("shutdown", "");
            }
        }
    }

    return std::pair<string, string>("unknown", "");
}

std::vector<std::string>
CommandSession::getZones() {
    ElementPtr cmd, result, env;
    std::vector<std::string> zone_names;
    cmd = Element::create_from_string("{ \"command\": [ \"zone\", \"list\" ] }");
    sleep(1);
    session_.group_sendmsg(cmd, "ConfigManager");
    session_.group_recvmsg(env, result, false);
    BOOST_FOREACH(ElementPtr zone_name, result->get("result")->list_value()) {
        zone_names.push_back(zone_name->string_value());
    }
    return zone_names;
}
