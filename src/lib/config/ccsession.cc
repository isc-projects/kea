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

#include <config.h>

#include <stdexcept>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#include <iostream>
#include <fstream>
#include <sstream>
#include <cerrno>

#include <boost/bind.hpp>
#include <boost/foreach.hpp>

#include <cc/data.h>
#include <module_spec.h>
#include <cc/session.h>
#include <exceptions/exceptions.h>

#include <config/config_log.h>
#include <config/ccsession.h>

#include <log/logger_support.h>
#include <log/logger_specification.h>
#include <log/logger_manager.h>

using namespace std;

using isc::data::Element;
using isc::data::ConstElementPtr;
using isc::data::ElementPtr;
using isc::data::JSONError;

namespace isc {
namespace config {

/// Creates a standard config/command protocol answer message
ConstElementPtr
createAnswer() {
    ElementPtr answer = Element::fromJSON("{\"result\": [] }");
    ElementPtr answer_content = Element::createList();
    answer_content->add(Element::create(0));
    answer->set("result", answer_content);

    return (answer);
}

ConstElementPtr
createAnswer(const int rcode, ConstElementPtr arg) {
    if (rcode != 0 && (!arg || arg->getType() != Element::string)) {
        isc_throw(CCSessionError, "Bad or no argument for rcode != 0");
    }
    ElementPtr answer = Element::fromJSON("{\"result\": [] }");
    ElementPtr answer_content = Element::createList();
    answer_content->add(Element::create(rcode));
    answer_content->add(arg);
    answer->set("result", answer_content);

    return (answer);
}

ConstElementPtr
createAnswer(const int rcode, const std::string& arg) {
    ElementPtr answer = Element::fromJSON("{\"result\": [] }");
    ElementPtr answer_content = Element::createList();
    answer_content->add(Element::create(rcode));
    answer_content->add(Element::create(arg));
    answer->set("result", answer_content);

    return (answer);
}

ConstElementPtr
parseAnswer(int &rcode, ConstElementPtr msg) {
    if (msg &&
        msg->getType() == Element::map &&
        msg->contains("result")) {
        ConstElementPtr result = msg->get("result");
        if (result->getType() != Element::list) {
            isc_throw(CCSessionError, "Result element in answer message is not a list");
        } else if (result->get(0)->getType() != Element::integer) {
            isc_throw(CCSessionError, "First element of result is not an rcode in answer message");
        }
        rcode = result->get(0)->intValue();
        if (result->size() > 1) {
            if (rcode == 0 || result->get(1)->getType() == Element::string) {
                return (result->get(1));
            } else {
                isc_throw(CCSessionError, "Error description in result with rcode != 0 is not a string");
            }
        } else {
            if (rcode == 0) {
                return (ElementPtr());
            } else {
                isc_throw(CCSessionError, "Result with rcode != 0 does not have an error description");
            }
        }
    } else {
        isc_throw(CCSessionError, "No result part in answer message");
    }
}

ConstElementPtr
createCommand(const std::string& command) {
    return (createCommand(command, ElementPtr()));
}

ConstElementPtr
createCommand(const std::string& command, ConstElementPtr arg) {
    ElementPtr cmd = Element::createMap();
    ElementPtr cmd_parts = Element::createList();
    cmd_parts->add(Element::create(command));
    if (arg) {
        cmd_parts->add(arg);
    }
    cmd->set("command", cmd_parts);
    return (cmd);
}

std::string
parseCommand(ConstElementPtr& arg, ConstElementPtr command) {
    if (command &&
        command->getType() == Element::map &&
        command->contains("command")) {
        ConstElementPtr cmd = command->get("command");
        if (cmd->getType() == Element::list &&
            cmd->size() > 0 &&
            cmd->get(0)->getType() == Element::string) {
            if (cmd->size() > 1) {
                arg = cmd->get(1);
            } else {
                arg = Element::createMap();
            }
            return (cmd->get(0)->stringValue());
        } else {
            isc_throw(CCSessionError, "Command part in command message missing, empty, or not a list");
        }
    } else {
        isc_throw(CCSessionError, "Command Element empty or not a map with \"command\"");
    }
}

namespace {
// Temporary workaround functions for missing functionality in
// getValue() (main problem described in ticket #993)
// This returns either the value set for the given relative id,
// or its default value
// (intentially defined here so this interface does not get
// included in ConfigData as it is)
ConstElementPtr getValueOrDefault(ConstElementPtr config_part,
                                  const std::string& relative_id,
                                  const ConfigData& config_data,
                                  const std::string& full_id) {
    if (config_part->contains(relative_id)) {
        return config_part->get(relative_id);
    } else {
        return config_data.getDefaultValue(full_id);
    }
}

// Reads a output_option subelement of a logger configuration,
// and sets the values thereing to the given OutputOption struct,
// or defaults values if they are not provided (from config_data).
void
readOutputOptionConf(isc::log::OutputOption& output_option,
                     ConstElementPtr output_option_el,
                     const ConfigData& config_data)
{
    ConstElementPtr destination_el = getValueOrDefault(output_option_el,
                                    "destination", config_data,
                                    "loggers/output_options/destination");
    output_option.destination = isc::log::getDestination(destination_el->stringValue());
    ConstElementPtr output_el = getValueOrDefault(output_option_el,
                                    "output", config_data,
                                    "loggers/output_options/output");
    if (output_option.destination == isc::log::OutputOption::DEST_CONSOLE) {
        output_option.stream = isc::log::getStream(output_el->stringValue());
    } else if (output_option.destination == isc::log::OutputOption::DEST_FILE) {
        output_option.filename = output_el->stringValue();
    } else if (output_option.destination == isc::log::OutputOption::DEST_SYSLOG) {
        output_option.facility = output_el->stringValue();
    }
    output_option.flush = getValueOrDefault(output_option_el,
                              "flush", config_data,
                              "loggers/output_options/flush")->boolValue();
    output_option.maxsize = getValueOrDefault(output_option_el,
                                "maxsize", config_data,
                                "loggers/output_options/maxsize")->intValue();
    output_option.maxver = getValueOrDefault(output_option_el,
                               "maxver", config_data,
                               "loggers/output_options/maxver")->intValue();
}

// Reads a full 'loggers' configuration, and adds the loggers therein
// to the given vector, fills in blanks with defaults from config_data
void
readLoggersConf(std::vector<isc::log::LoggerSpecification>& specs,
                ConstElementPtr logger,
                const ConfigData& config_data)
{
    const std::string lname = logger->get("name")->stringValue();
    ConstElementPtr severity_el = getValueOrDefault(logger,
                                      "severity", config_data,
                                      "loggers/severity");
    isc::log::Severity severity = isc::log::getSeverity(
                                      severity_el->stringValue());
    int dbg_level = getValueOrDefault(logger, "debuglevel",
                                      config_data,
                                      "loggers/debuglevel")->intValue();
    bool additive = getValueOrDefault(logger, "additive", config_data,
                                      "loggers/additive")->boolValue();

    isc::log::LoggerSpecification logger_spec(
        lname, severity, dbg_level, additive
    );

    if (logger->contains("output_options")) {
        BOOST_FOREACH(ConstElementPtr output_option_el,
                      logger->get("output_options")->listValue()) {
            // create outputoptions
            isc::log::OutputOption output_option;
            readOutputOptionConf(output_option,
                                 output_option_el,
                                 config_data);
            logger_spec.addOutputOption(output_option);
        }
    }

    specs.push_back(logger_spec);
}

} // end anonymous namespace

void
default_logconfig_handler(const std::string& module_name,
                          ConstElementPtr new_config,
                          const ConfigData& config_data) {
    config_data.getModuleSpec().validateConfig(new_config, true);

    std::vector<isc::log::LoggerSpecification> specs;

    if (new_config->contains("loggers")) {
        BOOST_FOREACH(ConstElementPtr logger,
                      new_config->get("loggers")->listValue()) {
            readLoggersConf(specs, logger, config_data);
        }
    }

    isc::log::LoggerManager logger_manager;
    logger_manager.process(specs.begin(), specs.end());
}


ModuleSpec
ModuleCCSession::readModuleSpecification(const std::string& filename) {
    std::ifstream file;
    ModuleSpec module_spec;
    
    // this file should be declared in a @something@ directive
    file.open(filename.c_str());
    if (!file) {
        LOG_ERROR(config_logger, CONFIG_OPEN_FAIL).arg(filename).arg(strerror(errno));
        isc_throw(CCSessionInitError, strerror(errno));
    }

    try {
        module_spec = moduleSpecFromFile(file, true);
    } catch (const JSONError& pe) {
        LOG_ERROR(config_logger, CONFIG_JSON_PARSE).arg(filename).arg(pe.what());
        isc_throw(CCSessionInitError, pe.what());
    } catch (const ModuleSpecError& dde) {
        LOG_ERROR(config_logger, CONFIG_MOD_SPEC_FORMAT).arg(filename).arg(dde.what());
        isc_throw(CCSessionInitError, dde.what());
    }
    file.close();
    return (module_spec);
}

void
ModuleCCSession::startCheck() {
    // data available on the command channel.  process it in the synchronous
    // mode.
    checkCommand();

    // start asynchronous read again.
    session_.startRead(boost::bind(&ModuleCCSession::startCheck, this));
}

ModuleCCSession::ModuleCCSession(
    const std::string& spec_file_name,
    isc::cc::AbstractSession& session,
    isc::data::ConstElementPtr(*config_handler)(
        isc::data::ConstElementPtr new_config),
    isc::data::ConstElementPtr(*command_handler)(
        const std::string& command, isc::data::ConstElementPtr args),
    bool start_immediately,
    bool handle_logging
    ) :
    started_(false),
    session_(session)
{
    module_specification_ = readModuleSpecification(spec_file_name);
    setModuleSpec(module_specification_);

    module_name_ = module_specification_.getFullSpec()->get("module_name")->stringValue();
    config_handler_ = config_handler;
    command_handler_ = command_handler;

    session_.establish(NULL);
    session_.subscribe(module_name_, "*");

    // send the data specification
    ConstElementPtr spec_msg = createCommand("module_spec",
                                             module_specification_.getFullSpec());
    unsigned int seq = session_.group_sendmsg(spec_msg, "ConfigManager");

    ConstElementPtr answer, env;
    session_.group_recvmsg(env, answer, false, seq);
    int rcode;
    ConstElementPtr err = parseAnswer(rcode, answer);
    if (rcode != 0) {
        LOG_ERROR(config_logger, CONFIG_MOD_SPEC_REJECT).arg(answer->str());
        isc_throw(CCSessionInitError, answer->str());
    }
    
    setLocalConfig(Element::fromJSON("{}"));
    // get any stored configuration from the manager
    if (config_handler_) {
        ConstElementPtr cmd = Element::fromJSON("{ \"command\": [\"get_config\", {\"module_name\":\"" + module_name_ + "\"} ] }");
        seq = session_.group_sendmsg(cmd, "ConfigManager");
        session_.group_recvmsg(env, answer, false, seq);
        ConstElementPtr new_config = parseAnswer(rcode, answer);
        if (rcode == 0) {
            handleConfigUpdate(new_config);
        } else {
            LOG_ERROR(config_logger, CONFIG_GET_FAIL).arg(new_config->str());
            isc_throw(CCSessionInitError, answer->str());
        }
    }

    // Keep track of logging settings automatically
    if (handle_logging) {
        addRemoteConfig("Logging", default_logconfig_handler, false);
    }

    if (start_immediately) {
        start();
    }

}

void
ModuleCCSession::start() {
    if (started_) {
        isc_throw(CCSessionError, "Module CC session already started");
    }

    // register callback for asynchronous read
    session_.startRead(boost::bind(&ModuleCCSession::startCheck, this));

    started_ = true;
}

/// Validates the new config values, if they are correct,
/// call the config handler with the values that have changed
/// If that results in success, store the new config
ConstElementPtr
ModuleCCSession::handleConfigUpdate(ConstElementPtr new_config) {
    ConstElementPtr answer;
    ElementPtr errors = Element::createList();
    if (!config_handler_) {
        answer = createAnswer(1, module_name_ + " does not have a config handler");
    } else if (!module_specification_.validateConfig(new_config, false,
                                                      errors)) {
        std::stringstream ss;
        ss << "Error in config validation: ";
        BOOST_FOREACH(ConstElementPtr error, errors->listValue()) {
            ss << error->stringValue();
        }
        answer = createAnswer(2, ss.str());
    } else {
        // remove the values that have not changed
        ConstElementPtr diff = removeIdentical(new_config, getLocalConfig());
        // handle config update
        answer = config_handler_(diff);
        int rcode;
        parseAnswer(rcode, answer);
        if (rcode == 0) {
            ElementPtr local_config = getLocalConfig();
            isc::data::merge(local_config, diff);
            setLocalConfig(local_config);
        }
    }
    return (answer);
}

bool
ModuleCCSession::hasQueuedMsgs() const {
    return (session_.hasQueuedMsgs());
}

ConstElementPtr
ModuleCCSession::checkConfigUpdateCommand(const std::string& target_module,
                                          ConstElementPtr arg)
{
    if (target_module == module_name_) {
        return (handleConfigUpdate(arg));
    } else {
        // ok this update is not for us, if we have this module
        // in our remote config list, update that
        updateRemoteConfig(target_module, arg);
        // we're not supposed to answer to this, so return
        return (ElementPtr());
    }
}

ConstElementPtr
ModuleCCSession::checkModuleCommand(const std::string& cmd_str,
                                    const std::string& target_module,
                                    ConstElementPtr arg) const
{
    if (target_module == module_name_) {
        if (command_handler_) {
            ElementPtr errors = Element::createList();
            if (module_specification_.validateCommand(cmd_str,
                                                       arg,
                                                       errors)) {
                return (command_handler_(cmd_str, arg));
            } else {
                std::stringstream ss;
                ss << "Error in command validation: ";
                BOOST_FOREACH(ConstElementPtr error,
                              errors->listValue()) {
                    ss << error->stringValue();
                }
                return (createAnswer(3, ss.str()));
            }
        } else {
            return (createAnswer(1,
                                 "Command given but no "
                                 "command handler for module"));
        }
    }
    return (ElementPtr());
}

int
ModuleCCSession::checkCommand() {
    ConstElementPtr cmd, routing, data;
    if (session_.group_recvmsg(routing, data, true)) {
        
        /* ignore result messages (in case we're out of sync, to prevent
         * pingpongs */
        if (data->getType() != Element::map || data->contains("result")) {
            return (0);
        }
        ConstElementPtr arg;
        ConstElementPtr answer;
        try {
            std::string cmd_str = parseCommand(arg, data);
            std::string target_module = routing->get("group")->stringValue();
            if (cmd_str == "config_update") {
                answer = checkConfigUpdateCommand(target_module, arg);
            } else {
                answer = checkModuleCommand(cmd_str, target_module, arg);
            }
        } catch (const CCSessionError& re) {
            LOG_ERROR(config_logger, CONFIG_CCSESSION_MSG).arg(re.what());
        } catch (const std::exception& stde) {
            // No matter what unexpected error happens, we do not want
            // to crash because of an incoming event, so we log the
            // exception and continue to run
            LOG_ERROR(config_logger, CONFIG_CCSESSION_MSG_INTERNAL).arg(stde.what());
        }
        if (!isNull(answer)) {
            session_.reply(routing, answer);
        }
    }

    return (0);
}

ModuleSpec
ModuleCCSession::fetchRemoteSpec(const std::string& module, bool is_filename) {
    if (is_filename) {
        // It is a filename, simply load it.
        return (readModuleSpecification(module));
    } else {
        // It's module name, request it from config manager

        // Send the command
        ConstElementPtr cmd(createCommand("get_module_spec",
                            Element::fromJSON("{\"module_name\": \"" + module +
                                              "\"}")));
        unsigned int seq = session_.group_sendmsg(cmd, "ConfigManager");
        ConstElementPtr env, answer;
        session_.group_recvmsg(env, answer, false, seq);
        int rcode;
        ConstElementPtr spec_data = parseAnswer(rcode, answer);
        if (rcode == 0 && spec_data) {
            // received OK, construct the spec out of it
            ModuleSpec spec = ModuleSpec(spec_data);
            if (module != spec.getModuleName()) {
                // It's a different module!
                isc_throw(CCSessionError, "Module name mismatch");
            }
            return (spec);
        } else {
            isc_throw(CCSessionError, "Error getting config for " +
                      module + ": " + answer->str());
        }
    }
}

std::string
ModuleCCSession::addRemoteConfig(const std::string& spec_name,
                                 void (*handler)(const std::string& module,
                                                 ConstElementPtr,
                                                 const ConfigData&),
                                 bool spec_is_filename)
{
    // First get the module name, specification and default config
    const ModuleSpec rmod_spec(fetchRemoteSpec(spec_name, spec_is_filename));
    const std::string module_name(rmod_spec.getModuleName());
    ConfigData rmod_config(rmod_spec);

    // Get the current configuration values from config manager
    ConstElementPtr cmd(createCommand("get_config",
                        Element::fromJSON("{\"module_name\": \"" +
                                          module_name + "\"}")));
    const unsigned int seq = session_.group_sendmsg(cmd, "ConfigManager");

    ConstElementPtr env, answer;
    session_.group_recvmsg(env, answer, false, seq);
    int rcode;
    ConstElementPtr new_config = parseAnswer(rcode, answer);
    ElementPtr local_config;
    if (rcode == 0 && new_config) {
        // Merge the received config into existing local config
        local_config = rmod_config.getLocalConfig();
        isc::data::merge(local_config, new_config);
        rmod_config.setLocalConfig(local_config);
    } else {
        isc_throw(CCSessionError, "Error getting config for " + module_name + ": " + answer->str());
    }

    // all ok, add it
    remote_module_configs_[module_name] = rmod_config;
    if (handler) {
        remote_module_handlers_[module_name] = handler;
        handler(module_name, local_config, rmod_config);
    }

    // Make sure we get updates in future
    session_.subscribe(module_name);
    return (module_name);
}

void
ModuleCCSession::removeRemoteConfig(const std::string& module_name) {
    std::map<std::string, ConfigData>::iterator it;

    it = remote_module_configs_.find(module_name);
    if (it != remote_module_configs_.end()) {
        remote_module_configs_.erase(it);
        remote_module_handlers_.erase(module_name);
        session_.unsubscribe(module_name);
    }
}

ConstElementPtr
ModuleCCSession::getRemoteConfigValue(const std::string& module_name,
                                      const std::string& identifier) const
{
    std::map<std::string, ConfigData>::const_iterator it =
        remote_module_configs_.find(module_name);

    if (it != remote_module_configs_.end()) {
        return ((*it).second.getValue(identifier));
    } else {
        isc_throw(CCSessionError,
                  "Remote module " + module_name + " not found.");
    }
}

void
ModuleCCSession::updateRemoteConfig(const std::string& module_name,
                                    ConstElementPtr new_config)
{
    std::map<std::string, ConfigData>::iterator it;

    it = remote_module_configs_.find(module_name);
    if (it != remote_module_configs_.end()) {
        ElementPtr rconf = (*it).second.getLocalConfig();
        isc::data::merge(rconf, new_config);
        std::map<std::string, RemoteHandler>::iterator hit =
            remote_module_handlers_.find(module_name);
        if (hit != remote_module_handlers_.end()) {
            hit->second(module_name, new_config, it->second);
        }
    }
}

}
}
