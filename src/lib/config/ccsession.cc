// Copyright (C) 2009, 2015  Internet Systems Consortium, Inc. ("ISC")
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
#include <ctype.h>

#include <algorithm>
#include <cerrno>
#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
#include <string>

#include <boost/bind.hpp>
#include <boost/foreach.hpp>

#include <cc/data.h>
#include <config/module_spec.h>
#include <cc/session.h>
#include <exceptions/exceptions.h>

#include <config/config_log.h>
#include <config/ccsession.h>

#include <log/logger_support.h>
#include <log/logger_specification.h>
#include <log/logger_manager.h>
#include <log/logger_name.h>

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
    ElementPtr answer = Element::createMap();
    ElementPtr answer_content = Element::createList();
    answer_content->add(Element::create(isc::cc::CC_REPLY_SUCCESS));
    answer->set(isc::cc::CC_PAYLOAD_RESULT, answer_content);

    return (answer);
}

ConstElementPtr
createAnswer(const int rcode, ConstElementPtr arg) {
    if (rcode != 0 && (!arg || arg->getType() != Element::string)) {
        isc_throw(CCSessionError, "Bad or no argument for rcode != 0");
    }
    ElementPtr answer = Element::createMap();
    ElementPtr answer_content = Element::createList();
    answer_content->add(Element::create(rcode));
    answer_content->add(arg);
    answer->set(isc::cc::CC_PAYLOAD_RESULT, answer_content);

    return (answer);
}

ConstElementPtr
createAnswer(const int rcode, const std::string& arg) {
    ElementPtr answer = Element::createMap();
    ElementPtr answer_content = Element::createList();
    answer_content->add(Element::create(rcode));
    answer_content->add(Element::create(arg));
    answer->set(isc::cc::CC_PAYLOAD_RESULT, answer_content);

    return (answer);
}

ConstElementPtr
parseAnswer(int &rcode, ConstElementPtr msg) {
    if (msg &&
        msg->getType() == Element::map &&
        msg->contains(isc::cc::CC_PAYLOAD_RESULT)) {
        ConstElementPtr result = msg->get(isc::cc::CC_PAYLOAD_RESULT);
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
    cmd->set(isc::cc::CC_PAYLOAD_COMMAND, cmd_parts);
    return (cmd);
}

std::string
parseCommand(ConstElementPtr& arg, ConstElementPtr command) {
    if (command &&
        command->getType() == Element::map &&
        command->contains(isc::cc::CC_PAYLOAD_COMMAND)) {
        ConstElementPtr cmd = command->get(isc::cc::CC_PAYLOAD_COMMAND);
        if (cmd->getType() == Element::list &&
            !cmd->empty() &&
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
// (intentionally defined here so this interface does not get
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

/// @brief Prefix name with "kea-".
///
/// In BIND 10, modules had names taken from the .spec file, which are typically
/// names starting with a capital letter (e.g. "Resolver", "Auth" etc.).  The
/// names of the associated binaries are derived from the module names, being
/// prefixed "b10-" and having the first letter of the module name lower-cased
/// (e.g. "b10-resolver", "b10-auth").  (It is a required convention that there
/// be this relationship between the names.)
///
/// In Kea we're not using module names, but we do still keep some capability to
/// run Kea servers in Bundy framework. For that reason the whole discussion here
/// applies only to case when Kea is compiled with Bundy configuration backend.
///
/// Within the binaries the root loggers are named after the binaries themselves.
/// (The reason for this is that the name of the logger is included in the
/// message logged, so making it clear which message comes from which Kea
/// process.) As logging is configured using module names, the configuration code
/// has to match these with the corresponding logger names. This function
/// converts a module name to a root logger name by lowercasing the first letter
/// of the module name and prepending "kea-".
///
/// \param instring String to convert.  (This may be empty, in which case
///        "kea-" will be returned.)
///
/// \return Converted string.
std::string
keaPrefix(const std::string& instring) {
    std::string result = instring;
    if (!result.empty()) {
        result[0] = tolower(result[0]);
    }
    return (std::string("kea-") + result);
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
    // Read name, adding prefix as required.
    std::string lname = logger->get("name")->stringValue();

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

// Copies the map for a logger, changing the name of the logger in the process.
// This is used because the map being copied is "const", so in order to
// change the name we need to create a new one.
//
// \param cur_logger Logger being copied.
// \param new_name New value of the "name" element at the top level.
//
// \return Pointer to the map with the updated element.
ConstElementPtr
copyLogger(ConstElementPtr& cur_logger, const std::string& new_name) {

    // Since we'll only be updating one first-level element and subsequent
    // use won't change the contents of the map, a shallow map copy is enough.
    ElementPtr new_logger(Element::createMap());
    new_logger->setValue(cur_logger->mapValue());
    new_logger->set("name", Element::create(new_name));

    return (new_logger);
}


} // end anonymous namespace


ConstElementPtr
getRelatedLoggers(ConstElementPtr loggers) {
    // Keep a list of names for easier lookup later
    std::set<std::string> our_names;
    const std::string& root_name = isc::log::getRootLoggerName();

    ElementPtr result = isc::data::Element::createList();

    BOOST_FOREACH(ConstElementPtr cur_logger, loggers->listValue()) {
        // Need to add the kea- prefix to names ready from the spec file.
        const std::string cur_name = cur_logger->get("name")->stringValue();
        const std::string mod_name = keaPrefix(cur_name);
        if (mod_name == root_name || mod_name.find(root_name + ".") == 0) {

            // Note this name so that we don't add a wildcard that matches it.
            our_names.insert(mod_name);

            // We want to store the logger with the modified name (i.e. with
            // the kea- prefix).  As we are dealing with const loggers, we
            // store a modified copy of the data.
            result->add(copyLogger(cur_logger, mod_name));
            LOG_DEBUG(config_logger, DBG_CONFIG_PROCESS, CONFIG_LOG_EXPLICIT)
                      .arg(cur_name);

        } else if (!cur_name.empty() && (cur_name[0] != '*')) {
            // Not a wildcard logger and we are ignoring it.
            LOG_DEBUG(config_logger, DBG_CONFIG_PROCESS,
                      CONFIG_LOG_IGNORE_EXPLICIT).arg(cur_name);
        }
    }

    // Now find the wildcard names (the one that start with "*").
    BOOST_FOREACH(ConstElementPtr cur_logger, loggers->listValue()) {
        const std::string cur_name = cur_logger->get("name")->stringValue();
        // If name is '*', or starts with '*.', replace * with root
        // logger name.
        if (cur_name == "*" || (cur_name.length() > 1 &&
            cur_name[0] == '*' && cur_name[1] == '.')) {

            // Substitute the "*" with the root name
            std::string mod_name = cur_name;
            mod_name.replace(0, 1, root_name);

            // Now add it to the result list, but only if a logger with
            // that name was not configured explicitly.
            if (our_names.find(mod_name) == our_names.end()) {

                // We substitute the name here, but as we are dealing with
                // consts, we need to copy the data.
                result->add(copyLogger(cur_logger, mod_name));
                LOG_DEBUG(config_logger, DBG_CONFIG_PROCESS,
                          CONFIG_LOG_WILD_MATCH).arg(cur_name);

            } else if (!cur_name.empty() && (cur_name[0] == '*')) {
                // Is a wildcard and we are ignoring it (because the wildcard
                // expands to a specification that we already encountered when
                // processing explicit names).
                LOG_DEBUG(config_logger, DBG_CONFIG_PROCESS,
                          CONFIG_LOG_IGNORE_WILD).arg(cur_name);
            }
        }
    }
    return (result);
}

void
default_logconfig_handler(const std::string& module_name,
                          ConstElementPtr new_config,
                          const ConfigData& config_data) {
    config_data.getModuleSpec().validateConfig(new_config, true);

    std::vector<isc::log::LoggerSpecification> specs;

    if (new_config->contains("loggers")) {
        ConstElementPtr loggers = getRelatedLoggers(new_config->get("loggers"));
        BOOST_FOREACH(ConstElementPtr logger,
                      loggers->listValue()) {
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
    int rcode = -1;
    ConstElementPtr err = parseAnswer(rcode, answer);
    if (rcode != 0) {
        LOG_ERROR(config_logger, CONFIG_MOD_SPEC_REJECT).arg(answer->str());
        isc_throw(CCSessionInitError, answer->str());
    }

    setLocalConfig(Element::createMap());
    // get any stored configuration from the manager
    if (config_handler_) {
        ConstElementPtr cmd =
            createCommand("get_config",
                          Element::fromJSON("{\"module_name\":\"" +
                                            module_name_ + "\"}"));
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

ModuleCCSession::~ModuleCCSession() {
    try {
        sendStopping();
    } catch (const std::exception& exc) {
        LOG_ERROR(config_logger,
                  CONFIG_CCSESSION_STOPPING).arg(exc.what());
    } catch (...) {
        LOG_ERROR(config_logger,
                  CONFIG_CCSESSION_STOPPING_UNKNOWN);
    }
};

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
        int rcode = -1;
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
    } else if (unhandled_callback_) {
        unhandled_callback_(cmd_str, target_module, arg);
    }
    return (ElementPtr());
}

int
ModuleCCSession::checkCommand() {
    ConstElementPtr cmd, routing, data;
    if (session_.group_recvmsg(routing, data, true)) {

        // In case the message is wanted asynchronously, it gets used.
        if (checkAsyncRecv(routing, data)) {
            return (0);
        }

        // In case it is notification, eat it.
        if (checkNotification(routing, data)) {
            return (0);
        }

        /* ignore result messages (in case we're out of sync, to prevent
         * pingpongs */
        if (data->getType() != Element::map ||
            data->contains(isc::cc::CC_PAYLOAD_RESULT)) {
            return (0);
        }
        ConstElementPtr arg;
        ConstElementPtr answer;
        try {
            std::string cmd_str = parseCommand(arg, data);
            std::string target_module =
                routing->get(isc::cc::CC_HEADER_GROUP)->stringValue();
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
        int rcode = -1;
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
                                 RemoteHandler handler,
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
    int rcode = -1;
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

void
ModuleCCSession::sendStopping() {
    // Inform the configuration manager that this module is stopping
    ConstElementPtr cmd(createCommand("stopping",
                                      Element::fromJSON(
                                          "{\"module_name\": \"" +
                                          module_name_ + "\"}")));
    // It's just an FYI, configmanager is not expected to respond.
    session_.group_sendmsg(cmd, "ConfigManager");
}

class ModuleCCSession::AsyncRecvRequest {
public: // Everything is public here, as the definition is hidden anyway
    AsyncRecvRequest(const AsyncRecvCallback& cb, const string& rcp, int sq,
                     bool reply) :
        callback(cb),
        recipient(rcp),
        seq(sq),
        is_reply(reply)
    {}
    const AsyncRecvCallback callback;
    const string recipient;
    const int seq;
    const bool is_reply;
};

ModuleCCSession::AsyncRecvRequestID
ModuleCCSession::groupRecvMsgAsync(const AsyncRecvCallback& callback,
                                   bool is_reply, int seq,
                                   const string& recipient) {
    // This just stores the request, the handling is done in checkCommand()

    // push_back would be simpler, but it does not return the iterator we need
    return (async_recv_requests_.insert(async_recv_requests_.end(),
                                        AsyncRecvRequest(callback, recipient,
                                                         seq, is_reply)));
}

bool
ModuleCCSession::checkAsyncRecv(const ConstElementPtr& envelope,
                                const ConstElementPtr& msg)
{
    for (AsyncRecvRequestID request(async_recv_requests_.begin());
         request != async_recv_requests_.end(); ++request) {
        // Just go through all the requests and look for a matching one
        if (requestMatch(*request, envelope)) {
            // We want the request to be still alive at the time we
            // call the callback. But we need to remove it on an exception
            // too, so we use the class. If just C++ had the finally keyword.
            class RequestDeleter {
            public:
                RequestDeleter(AsyncRecvRequests& requests,
                               AsyncRecvRequestID& request) :
                    requests_(requests),
                    request_(request)
                { }
                ~RequestDeleter() {
                    requests_.erase(request_);
                }
            private:
                AsyncRecvRequests& requests_;
                AsyncRecvRequestID& request_;
            };
            RequestDeleter deleter(async_recv_requests_, request);
            // Call the callback
            request->callback(envelope, msg, request);
            return (true);
        }
    }
    return (false);
}

bool
ModuleCCSession::requestMatch(const AsyncRecvRequest& request,
                              const ConstElementPtr& envelope) const
{
    if (request.is_reply != envelope->contains(isc::cc::CC_HEADER_REPLY)) {
        // Wrong type of message
        return (false);
    }
    if (request.is_reply &&
        (request.seq == -1 ||
         request.seq == envelope->get(isc::cc::CC_HEADER_REPLY)->intValue())) {
        // This is the correct reply
        return (true);
    }
    if (!request.is_reply &&
        (request.recipient.empty() || request.recipient ==
         envelope->get(isc::cc::CC_HEADER_GROUP)->stringValue())) {
        // This is the correct command
        return (true);
    }
    // If nothing from the above, we don't want it
    return (false);
}

void
ModuleCCSession::cancelAsyncRecv(const AsyncRecvRequestID& id) {
    async_recv_requests_.erase(id);
}

ConstElementPtr
ModuleCCSession::rpcCall(const std::string &command, const std::string &group,
                         const std::string &instance, const std::string &to,
                         const ConstElementPtr &params)
{
    ConstElementPtr command_el(createCommand(command, params));
    const int seq = groupSendMsg(command_el, group, instance, to, true);
    ConstElementPtr env, answer;
    LOG_DEBUG(config_logger, DBGLVL_TRACE_DETAIL, CONFIG_RPC_SEQ).arg(command).
        arg(group).arg(seq);
    groupRecvMsg(env, answer, true, seq);
    int rcode;
    const ConstElementPtr result(parseAnswer(rcode, answer));
    if (rcode == isc::cc::CC_REPLY_NO_RECPT) {
        isc_throw(RPCRecipientMissing, *answer);
    } else if (rcode != isc::cc::CC_REPLY_SUCCESS) {
        isc_throw_1(RPCError, *answer, rcode);
    } else {
        return (result);
    }
}

void
ModuleCCSession::notify(const std::string& group, const std::string& name,
                        const ConstElementPtr& params)
{
    const ElementPtr message(Element::createMap());
    const ElementPtr notification(Element::createList());
    notification->add(Element::create(name));
    if (params) {
        notification->add(params);
    }
    message->set(isc::cc::CC_PAYLOAD_NOTIFICATION, notification);
    groupSendMsg(message, isc::cc::CC_GROUP_NOTIFICATION_PREFIX + group,
                 isc::cc::CC_INSTANCE_WILDCARD,
                 isc::cc::CC_TO_WILDCARD, false);
}

ModuleCCSession::NotificationID
ModuleCCSession::subscribeNotification(const std::string& notification_group,
                                       const NotificationCallback& callback)
{
    // Either insert a new empty list of callbacks or get an existing one.
    // Either way, get the iterator for its position.
    const std::pair<SubscribedNotifications::iterator, bool>& inserted =
        notifications_.insert(
            std::pair<std::string, NotificationCallbacks>(notification_group,
                NotificationCallbacks()));
    if (inserted.second) {
        // It was newly inserted. In that case, we need to subscribe to the
        // group.
        session_.subscribe(isc::cc::CC_GROUP_NOTIFICATION_PREFIX +
                           notification_group);
    }
    // Insert the callback to the chain
    NotificationCallbacks& callbacks = inserted.first->second;
    const NotificationCallbacks::iterator& callback_id =
        callbacks.insert(callbacks.end(), callback);
    // Just pack the iterators to form the ID
    return (NotificationID(inserted.first, callback_id));
}

void
ModuleCCSession::unsubscribeNotification(const NotificationID& notification) {
    NotificationCallbacks& callbacks = notification.first->second;
    // Remove the callback
    callbacks.erase(notification.second);
    // If it became empty, remove it from the map and unsubscribe
    if (callbacks.empty()) {
        session_.unsubscribe(isc::cc::CC_GROUP_NOTIFICATION_PREFIX +
                             notification.first->first);
        notifications_.erase(notification.first);
    }
}

bool
ModuleCCSession::checkNotification(const data::ConstElementPtr& envelope,
                                   const data::ConstElementPtr& msg)
{
    if (msg->getType() != data::Element::map) {
        // If it's not a map, then it's not a notification
        return (false);
    }
    if (msg->contains(isc::cc::CC_PAYLOAD_NOTIFICATION)) {
        // There's a notification inside. Extract its parameters.
        const std::string& group =
            envelope->get(isc::cc::CC_HEADER_GROUP)->stringValue();
        const std::string& notification_group =
            group.substr(std::string(isc::cc::CC_GROUP_NOTIFICATION_PREFIX).
                         size());
        const data::ConstElementPtr& notification =
            msg->get(isc::cc::CC_PAYLOAD_NOTIFICATION);
        // The first one is the event that happened
        const std::string& event = notification->get(0)->stringValue();
        // Any other params are second. But they may be missing
        const data::ConstElementPtr params =
            notification->size() == 1 ? data::ConstElementPtr() :
            notification->get(1);
        // Find the chain of notification callbacks
        const SubscribedNotifications::iterator& chain_iter =
            notifications_.find(notification_group);
        if (chain_iter == notifications_.end()) {
            // This means we no longer have any notifications for this group.
            // This can happen legally as a race condition - if msgq sends
            // us a notification, but we unsubscribe before we get to it
            // in the input stream.
            return (false);
        }
        BOOST_FOREACH(const NotificationCallback& callback,
                      chain_iter->second) {
            callback(event, params);
        }
        return (true);
    }
    return (false); // Not a notification
}

}
}
