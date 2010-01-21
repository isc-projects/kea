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

// 
// todo: generalize this and make it into a specific API for all modules
//       to use (i.e. connect to cc, send config and commands, get config,
//               react on config change announcements)
//


#include <stdexcept>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#include <iostream>
#include <fstream>
#include <sstream>

#include <boost/foreach.hpp>

#include <cc/cpp/data.h>
#include <cc/cpp/data_def.h>
#include <cc/cpp/session.h>

#include "common.h"
#include "ccsession.h"
#include "config.h"

using namespace std;

using isc::data::Element;
using isc::data::ElementPtr;
using isc::data::DataDefinition;
using isc::data::ParseError;
using isc::data::DataDefinitionError;

void
CommandSession::read_data_definition(const std::string& filename) {
    std::ifstream file;

    // this file should be declared in a @something@ directive
    file.open(PARKINGLOT_SPECFILE_LOCATION);
    if (!file) {
        cout << "error opening " << PARKINGLOT_SPECFILE_LOCATION << endl;
        exit(1);
    }

    try {
        data_definition_ = DataDefinition(file, true);
    } catch (ParseError pe) {
        cout << "Error parsing definition file: " << pe.what() << endl;
        exit(1);
    } catch (DataDefinitionError dde) {
        cout << "Error reading definition file: " << dde.what() << endl;
        exit(1);
    }
    file.close();
}

CommandSession::CommandSession(std::string module_name,
                               std::string spec_file_name,
                               isc::data::ElementPtr(*config_handler)(isc::data::ElementPtr new_config),
                               isc::data::ElementPtr(*command_handler)(isc::data::ElementPtr command)
                              ) throw (isc::cc::SessionError):
    module_name_(module_name),
    session_(isc::cc::Session())
{
    config_handler_ = config_handler;
    command_handler_ = command_handler;

    // todo: workaround, let boss wait until msgq is started
    // and remove sleep here
    sleep(1);

    ElementPtr answer, env;

    session_.establish();
    session_.subscribe(module_name, "*");
    session_.subscribe("Boss", "*");
    session_.subscribe("statistics", "*");
    read_data_definition(spec_file_name);
    sleep(1);
    // send the data specification
    session_.group_sendmsg(data_definition_.getDefinition(), "ConfigManager");
    session_.group_recvmsg(env, answer, false);
    
    // get any stored configuration from the manager
    if (config_handler_) {
        ElementPtr cmd = Element::createFromString("{ \"command\": [\"get_config\", {\"module_name\":\"" + module_name + "\"} ] }");
        session_.group_sendmsg(cmd, "ConfigManager");
        session_.group_recvmsg(env, answer, false);
        cout << "[XX] got config: " << endl << answer->str() << endl;
        if (answer->contains("result") &&
            answer->get("result")->get(0)->intValue() == 0 &&
            answer->get("result")->size() > 1) {
            config_handler(answer->get("result")->get(1));
        } else {
            cout << "[XX] no result in answer" << endl;
        }
    }
}

int
CommandSession::getSocket()
{
    return (session_.getSocket());
}

int
CommandSession::check_command()
{
    cout << "[XX] check for command" << endl;
    ElementPtr cmd, routing, data;
    if (session_.group_recvmsg(routing, data, true)) {
        /* ignore result messages (in case we're out of sync, to prevent
         * pingpongs */
        if (!data->getType() == Element::map || data->contains("result")) {
            return 0;
        }
        cout << "[XX] got something!" << endl << data->str() << endl;
        ElementPtr answer;
        if (data->contains("config_update")) {
            if (config_handler_) {
                // handle config update
                answer = config_handler_(data->get("config_update"));
            } else {
                answer = Element::createFromString("{ \"result\": [0] }");
            }
        }
        if (data->contains("command")) {
            if (command_handler_) {
                answer = command_handler_(data->get("command"));
            } else {
                answer = Element::createFromString("{ \"result\": [0] }");
            }
        }
        session_.reply(routing, answer);
    }
    
    return 0;
}

