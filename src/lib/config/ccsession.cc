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

#include "config.h"

#include <stdexcept>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <cerrno>

#ifdef HAVE_BOOST_SYSTEM
#include <boost/bind.hpp>
#endif
#include <boost/foreach.hpp>

#include <cc/data.h>
#include <module_spec.h>
#include <cc/session.h>
#include <exceptions/exceptions.h>

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
createAnswer()
{
    ElementPtr answer = Element::createFromString("{\"result\": [] }");
    ElementPtr answer_content = answer->get("result");
    answer_content->add(Element::create(0));
    return answer;
}

ElementPtr
createAnswer(const int rcode, const ElementPtr arg)
{
    if (rcode != 0 && (!arg || arg->getType() != Element::string)) {
        isc_throw(CCSessionError, "Bad or no argument for rcode != 0");
    }
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
    if (msg &&
        msg->getType() == Element::map &&
        msg->contains("result")) {
        ElementPtr result = msg->get("result");
        if (result->getType() != Element::list) {
            isc_throw(CCSessionError, "Result element in answer message is not a list");
        } else if (result->get(0)->getType() != Element::integer) {
            isc_throw(CCSessionError, "First element of result is not an rcode in answer message");
        }
        rcode = result->get(0)->intValue();
        if (result->size() > 1) {
            if (rcode == 0 || result->get(1)->getType() == Element::string) {
                return result->get(1);
            } else {
                isc_throw(CCSessionError, "Error description in result with rcode != 0 is not a string");
            }
        } else {
            if (rcode == 0) {
                return ElementPtr();
            } else {
                isc_throw(CCSessionError, "Result with rcode != 0 does not have an error description");
            }
        }
    } else {
        isc_throw(CCSessionError, "No result part in answer message");
    }
}

ElementPtr
createCommand(const std::string& command)
{
    return createCommand(command, ElementPtr());
}

ElementPtr
createCommand(const std::string& command, ElementPtr arg)
{
    ElementPtr cmd = Element::createFromString("{}");
    ElementPtr cmd_parts = Element::createFromString("[]");
    cmd_parts->add(Element::create(command));
    if (arg) {
        cmd_parts->add(arg);
    }
    cmd->set("command", cmd_parts);
    return cmd;
}

/// Returns "" and empty ElementPtr() if this does not
/// look like a command
const std::string
parseCommand(ElementPtr& arg, const ElementPtr command)
{
    if (command &&
        command->getType() == Element::map &&
        command->contains("command")) {
        ElementPtr cmd = command->get("command");
        if (cmd->getType() == Element::list &&
            cmd->size() > 0 &&
            cmd->get(0)->getType() == Element::string) {
            if (cmd->size() > 1) {
                arg = cmd->get(1);
            } else {
                arg = ElementPtr();
            }
            return cmd->get(0)->stringValue();
        } else {
            isc_throw(CCSessionError, "Command part in command message missing, empty, or not a list");
        }
    } else {
        isc_throw(CCSessionError, "Command Element empty or not a map with \"command\"");
    }
}

ModuleSpec
ModuleCCSession::readModuleSpecification(const std::string& filename) {
    std::ifstream file;
    ModuleSpec module_spec;
    
    // this file should be declared in a @something@ directive
    file.open(filename.c_str());
    if (!file) {
        cout << "error opening " << filename << ": " << strerror(errno) << endl;
        exit(1);
    }

    try {
        module_spec = moduleSpecFromFile(file, true);
    } catch (ParseError pe) {
        cout << "Error parsing module specification file: " << pe.what() << endl;
        exit(1);
    } catch (ModuleSpecError dde) {
        cout << "Error reading module specification file: " << dde.what() << endl;
        exit(1);
    }
    file.close();
    return module_spec;
}

#ifdef HAVE_BOOST_SYSTEM
void
ModuleCCSession::startCheck() {
    // data available on the command channel.  process it in the synchronous
    // mode.
    checkCommand();

    // start asynchronous read again.
    session_.startRead(boost::bind(&ModuleCCSession::startCheck, this));
}

ModuleCCSession::ModuleCCSession(
    std::string spec_file_name,
    boost::asio::io_service& io_service,
    isc::data::ElementPtr(*config_handler)(isc::data::ElementPtr new_config),
    isc::data::ElementPtr(*command_handler)(
        const std::string& command, const isc::data::ElementPtr args)
    ) throw (isc::cc::SessionError) :
    session_(io_service)
{
    init(spec_file_name, config_handler, command_handler);

    // register callback for asynchronous read
    session_.startRead(boost::bind(&ModuleCCSession::startCheck, this));
}
#endif

ModuleCCSession::ModuleCCSession(
    std::string spec_file_name,
    isc::data::ElementPtr(*config_handler)(isc::data::ElementPtr new_config),
    isc::data::ElementPtr(*command_handler)(
        const std::string& command, const isc::data::ElementPtr args)
    ) throw (isc::cc::SessionError)
{
    init(spec_file_name, config_handler, command_handler);
}

void
ModuleCCSession::init(
    std::string spec_file_name,
    isc::data::ElementPtr(*config_handler)(isc::data::ElementPtr new_config),
    isc::data::ElementPtr(*command_handler)(
        const std::string& command, const isc::data::ElementPtr args)
    ) throw (isc::cc::SessionError)
{
    module_specification_ = readModuleSpecification(spec_file_name);
    setModuleSpec(module_specification_);

    module_name_ = module_specification_.getFullSpec()->get("module_name")->stringValue();
    config_handler_ = config_handler;
    command_handler_ = command_handler;

    ElementPtr answer, env;

    session_.establish();
    session_.subscribe(module_name_, "*");
    //session_.subscribe("Boss", "*");
    //session_.subscribe("statistics", "*");
    // send the data specification
    ElementPtr spec_msg = createCommand("module_spec", module_specification_.getFullSpec());
    session_.group_sendmsg(spec_msg, "ConfigManager");
    session_.group_recvmsg(env, answer, false);
    int rcode;
    ElementPtr err = parseAnswer(rcode, answer);
    if (rcode != 0) {
        std::cerr << "[" << module_name_ << "] Error in specification: " << answer << std::endl;
    }
    
    setLocalConfig(Element::createFromString("{}"));
    // get any stored configuration from the manager
    if (config_handler_) {
        ElementPtr cmd = Element::createFromString("{ \"command\": [\"get_config\", {\"module_name\":\"" + module_name_ + "\"} ] }");
        session_.group_sendmsg(cmd, "ConfigManager");
        session_.group_recvmsg(env, answer, false);
        ElementPtr new_config = parseAnswer(rcode, answer);
        if (rcode == 0) {
            handleConfigUpdate(new_config);
        } else {
            std::cerr << "[" << module_name_ << "] Error getting config: " << new_config << std::endl;
        }
    }
}

/// Validates the new config values, if they are correct,
/// call the config handler with the values that have changed
/// If that results in success, store the new config
ElementPtr
ModuleCCSession::handleConfigUpdate(ElementPtr new_config)
{
    ElementPtr answer;
    ElementPtr errors = Element::createFromString("[]");
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
        // remove the values that have not changed
        isc::data::removeIdentical(new_config, getLocalConfig());
        // handle config update
        answer = config_handler_(new_config);
        int rcode;
        parseAnswer(rcode, answer);
        if (rcode == 0) {
            ElementPtr local_config = getLocalConfig();
            isc::data::merge(local_config, new_config);
            setLocalConfig(local_config);
        }
    }
    return answer;
}

int
ModuleCCSession::getSocket()
{
    return (session_.getSocket());
}

int
ModuleCCSession::checkCommand()
{
    ElementPtr cmd, routing, data;
    if (session_.group_recvmsg(routing, data, true)) {
        
        /* ignore result messages (in case we're out of sync, to prevent
         * pingpongs */
        if (data->getType() != Element::map || data->contains("result")) {
            return 0;
        }
        ElementPtr arg;
        ElementPtr answer;
        try {
            std::string cmd_str = parseCommand(arg, data);
            if (cmd_str == "config_update") {
                std::string target_module = routing->get("group")->stringValue();
                if (target_module == module_name_) {
                    answer = handleConfigUpdate(arg);
                } else {
                    // ok this update is not for us, if we have this module
                    // in our remote config list, update that
                    updateRemoteConfig(target_module, arg);
                    // we're not supposed to answer to this, so return
                    return 0;
                }
            } else {
                if (command_handler_) {
                    answer = command_handler_(cmd_str, arg);
                } else {
                    answer = createAnswer(1, "Command given but no command handler for module");
                }
            }
        } catch (CCSessionError re) {
            answer = createAnswer(1, re.what());
        }
        session_.reply(routing, answer);
    }
    
    return 0;
}

std::string
ModuleCCSession::addRemoteConfig(const std::string& spec_file_name)
{
    ModuleSpec rmod_spec = readModuleSpecification(spec_file_name);
    std::string module_name = rmod_spec.getFullSpec()->get("module_name")->stringValue();
    ConfigData rmod_config = ConfigData(rmod_spec);
    session_.subscribe(module_name);

    // Get the current configuration values for that module
    ElementPtr cmd = Element::createFromString("{ \"command\": [\"get_config\", {\"module_name\":\"" + module_name + "\"} ] }");
    ElementPtr env, answer;
    int rcode;
    
    session_.group_sendmsg(cmd, "ConfigManager");
    session_.group_recvmsg(env, answer, false);
    ElementPtr new_config = parseAnswer(rcode, answer);
    if (rcode == 0) {
        rmod_config.setLocalConfig(new_config);
    } else {
        isc_throw(CCSessionError, "Error getting config for " + module_name + ": " + answer->str());
    }

    // all ok, add it
    remote_module_configs_[module_name] = rmod_config;
    return module_name;
}

void
ModuleCCSession::removeRemoteConfig(const std::string& module_name)
{
    std::map<std::string, ConfigData>::iterator it;

    it = remote_module_configs_.find(module_name);
    if (it != remote_module_configs_.end()) {
        remote_module_configs_.erase(it);
        session_.unsubscribe(module_name);
    }
}

ElementPtr
ModuleCCSession::getRemoteConfigValue(const std::string& module_name, const std::string& identifier)
{
    std::map<std::string, ConfigData>::iterator it;

    it = remote_module_configs_.find(module_name);
    if (it != remote_module_configs_.end()) {
        return remote_module_configs_[module_name].getValue(identifier);
    } else {
        isc_throw(CCSessionError, "Remote module " + module_name + " not found.");
    }
}

void
ModuleCCSession::updateRemoteConfig(const std::string& module_name, ElementPtr new_config)
{
    std::map<std::string, ConfigData>::iterator it;

    it = remote_module_configs_.find(module_name);
    if (it != remote_module_configs_.end()) {
        ElementPtr rconf = (*it).second.getLocalConfig();
        isc::data::merge(rconf, new_config);
    }
}

}
}
