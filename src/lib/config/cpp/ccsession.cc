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
#include <cerrno>

#include <boost/foreach.hpp>

#include <cc/data.h>
#include <module_spec.h>
#include <cc/session.h>
#include <exceptions/exceptions.h>

//#include "common.h"
#include "ccsession.h"
#include "config.h"

using namespace std;

using isc::data::Element;
using isc::data::ElementPtr;
using isc::data::ParseError;

namespace isc {
namespace config {

/// Creates a standard config/command protocol answer message
ElementPtr
createAnswer(const int rcode)
{
    ElementPtr answer = Element::createFromString("{\"result\": [] }");
    ElementPtr answer_content = answer->get("result");
    answer_content->add(Element::create(rcode));
    return answer;
}

ElementPtr
createAnswer(const int rcode, const ElementPtr arg)
{
    ElementPtr answer = Element::createFromString("{\"result\": [] }");
    ElementPtr answer_content = answer->get("result");
    answer_content->add(Element::create(rcode));
    answer_content->add(arg);
    return answer;
}

ElementPtr
createAnswer(const int rcode, const std::string& arg)
{
    ElementPtr answer = Element::createFromString("{\"result\": [] }");
    ElementPtr answer_content = answer->get("result");
    answer_content->add(Element::create(rcode));
    answer_content->add(Element::create(arg));
    return answer;
}

ElementPtr
parseAnswer(int &rcode, const ElementPtr msg)
{
    if (!msg->contains("result")) {
        // TODO: raise CCSessionError exception
        dns_throw(CCSessionError, "No result in answer message");
    } else {
        ElementPtr result = msg->get("result");
        if (result->get(0)->getType() != Element::integer) {
            dns_throw(CCSessionError, "First element of result is not an rcode in answer message");
        } else if (result->get(0)->intValue() != 0 && result->get(1)->getType() != Element::string) {
            dns_throw(CCSessionError, "Rcode in answer message is non-zero, but other argument is not a StringElement");
        }
        rcode = result->get(0)->intValue();
        if (result->size() > 1) {
            return result->get(1);
        } else {
            return ElementPtr();
        }
    }
}

void
ModuleCCSession::read_module_specification(const std::string& filename) {
    std::ifstream file;

    // this file should be declared in a @something@ directive
    file.open(filename.c_str());
    if (!file) {
        cout << "error opening " << filename << ": " << strerror(errno) << endl;
        exit(1);
    }

    try {
        module_specification_ = moduleSpecFromFile(file, true);
    } catch (ParseError pe) {
        cout << "Error parsing module specification file: " << pe.what() << endl;
        exit(1);
    } catch (ModuleSpecError dde) {
        cout << "Error reading module specification file: " << dde.what() << endl;
        exit(1);
    }
    file.close();
}

ModuleCCSession::ModuleCCSession(std::string spec_file_name,
                               isc::data::ElementPtr(*config_handler)(isc::data::ElementPtr new_config),
                               isc::data::ElementPtr(*command_handler)(isc::data::ElementPtr command)
                              ) throw (isc::cc::SessionError):
    session_(isc::cc::Session())
{
    read_module_specification(spec_file_name);
    sleep(1);

    module_name_ = module_specification_.getFullSpec()->get("module_name")->stringValue();
    config_handler_ = config_handler;
    command_handler_ = command_handler;

    // todo: workaround, let boss wait until msgq is started
    // and remove sleep here
    sleep(1);

    ElementPtr answer, env;

    session_.establish();
    session_.subscribe(module_name_, "*");
    //session_.subscribe("Boss", "*");
    //session_.subscribe("statistics", "*");
    // send the data specification
    ElementPtr spec_msg = Element::createFromString("{}");
    spec_msg->set("module_spec", module_specification_.getFullSpec());
    session_.group_sendmsg(spec_msg, "ConfigManager");
    session_.group_recvmsg(env, answer, false);
    
    // get any stored configuration from the manager
    if (config_handler_) {
        ElementPtr cmd = Element::createFromString("{ \"command\": [\"get_config\", {\"module_name\":\"" + module_name_ + "\"} ] }");
        session_.group_sendmsg(cmd, "ConfigManager");
        session_.group_recvmsg(env, answer, false);
        cout << "[XX] got config: " << endl << answer->str() << endl;
        int rcode;
        ElementPtr new_config = parseAnswer(rcode, answer);
        handleConfigUpdate(new_config);
    }
}

/// Validates the new config values, if they are correct,
/// call the config handler
/// If that results in success, store the new config
ElementPtr
ModuleCCSession::handleConfigUpdate(ElementPtr new_config)
{
    ElementPtr answer;
    ElementPtr errors = Element::createFromString("[]");
    std::cout << "handleConfigUpdate " << new_config << std::endl;
    if (!config_handler_) {
        answer = createAnswer(1, module_name_ + " does not have a config handler");
    } else if (!module_specification_.validate_config(new_config, false, errors)) {
        std::stringstream ss;
        ss << "Error in config validation: ";
        BOOST_FOREACH(ElementPtr error, errors->listValue()) {
            ss << error->stringValue();
        }
        answer = createAnswer(2, ss.str());
    } else {
        // handle config update
        std::cout << "handleConfigUpdate " << new_config << std::endl;
        answer = config_handler_(new_config);
        int rcode;
        parseAnswer(rcode, answer);
        if (rcode == 0) {
            config_ = new_config;
        }
    }
    std::cout << "end handleConfigUpdate " << new_config << std::endl;
    return answer;
}

int
ModuleCCSession::getSocket()
{
    return (session_.getSocket());
}

int
ModuleCCSession::check_command()
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
            ElementPtr new_config = data->get("config_update");
            answer = handleConfigUpdate(new_config);
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

}
}
