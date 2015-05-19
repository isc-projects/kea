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

}
}
