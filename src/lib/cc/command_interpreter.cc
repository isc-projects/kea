// Copyright (C) 2009-2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <exceptions/exceptions.h>
#include <cc/command_interpreter.h>
#include <cc/data.h>
#include <string>
#include <set>

using namespace std;

using isc::data::Element;
using isc::data::ConstElementPtr;
using isc::data::ElementPtr;
using isc::data::JSONError;

namespace isc {
namespace config {

const char *CONTROL_COMMAND = "command";
const char *CONTROL_RESULT = "result";
const char *CONTROL_TEXT = "text";
const char *CONTROL_ARGUMENTS = "arguments";
const char *CONTROL_SERVICE = "service";
const char *CONTROL_REMOTE_ADDRESS = "remote-address";

// Full version, with status, text and arguments
ConstElementPtr
createAnswer(const int status_code, const std::string& text,
             const ConstElementPtr& arg) {
    if (status_code != 0 && text.empty()) {
        isc_throw(CtrlChannelError, "Text has to be provided for status_code != 0");
    }

    ElementPtr answer = Element::createMap();
    ElementPtr result = Element::create(status_code);
    answer->set(CONTROL_RESULT, result);

    if (!text.empty()) {
        answer->set(CONTROL_TEXT, Element::create(text));
    }
    if (arg) {
        answer->set(CONTROL_ARGUMENTS, arg);
    }
    return (answer);
}

ConstElementPtr
createAnswer() {
    return (createAnswer(CONTROL_RESULT_SUCCESS, string(""), ConstElementPtr()));
}

ConstElementPtr
createAnswer(const int status_code, const std::string& text) {
    return (createAnswer(status_code, text, ElementPtr()));
}

ConstElementPtr
createAnswer(const int status_code, const ConstElementPtr& arg) {
    return (createAnswer(status_code, "", arg));
}

ConstElementPtr
parseAnswerText(int &rcode, const ConstElementPtr& msg) {
    if (!msg) {
        isc_throw(CtrlChannelError, "invalid answer: no answer specified");
    }
    if (msg->getType() != Element::map) {
        isc_throw(CtrlChannelError, "invalid answer: expected toplevel entry to be a map, got "
                  << Element::typeToName(msg->getType()) << " instead");
    }
    if (!msg->contains(CONTROL_RESULT)) {
        isc_throw(CtrlChannelError,
                  "invalid answer: does not contain mandatory '" << CONTROL_RESULT << "'");
    }

    ConstElementPtr result = msg->get(CONTROL_RESULT);
    if (result->getType() != Element::integer) {
        isc_throw(CtrlChannelError, "invalid answer: expected '" << CONTROL_RESULT
                  << "' to be an integer, got "
                  << Element::typeToName(result->getType()) << " instead");
    }

    rcode = result->intValue();

    // If there are arguments, return them.
    return (msg->get(CONTROL_TEXT));
}

ConstElementPtr
parseAnswer(int &rcode, const ConstElementPtr& msg) {
    if (!msg) {
        isc_throw(CtrlChannelError, "invalid answer: no answer specified");
    }
    if (msg->getType() != Element::map) {
        isc_throw(CtrlChannelError, "invalid answer: expected toplevel entry to be a map, got "
                  << Element::typeToName(msg->getType()) << " instead");
    }
    if (!msg->contains(CONTROL_RESULT)) {
        isc_throw(CtrlChannelError,
                  "invalid answer: does not contain mandatory '" << CONTROL_RESULT << "'");
    }

    ConstElementPtr result = msg->get(CONTROL_RESULT);
    if (result->getType() != Element::integer) {
        isc_throw(CtrlChannelError, "invalid answer: expected '" << CONTROL_RESULT
                  << "' to be an integer, got "
                  << Element::typeToName(result->getType()) << " instead");
    }

    rcode = result->intValue();

    // If there are arguments, return them.
    ConstElementPtr args = msg->get(CONTROL_ARGUMENTS);
    if (args) {
        return (args);
    }

    // There are no arguments, let's try to return just the text status
    return (msg->get(CONTROL_TEXT));
}


std::string
answerToText(const ConstElementPtr& msg) {
    if (!msg) {
        isc_throw(CtrlChannelError, "invalid answer: no answer specified");
    }
    if (msg->getType() != Element::map) {
        isc_throw(CtrlChannelError, "invalid answer: expected toplevel entry to be a map, got "
                  << Element::typeToName(msg->getType()) << " instead");
    }
    if (!msg->contains(CONTROL_RESULT)) {
        isc_throw(CtrlChannelError,
                  "invalid answer: does not contain mandatory '" << CONTROL_RESULT << "'");
    }

    ConstElementPtr result = msg->get(CONTROL_RESULT);
    if (result->getType() != Element::integer) {
        isc_throw(CtrlChannelError, "invalid answer: expected '" << CONTROL_RESULT
                  << "' to be an integer, got " << Element::typeToName(result->getType())
                  << " instead");
    }

    stringstream txt;
    int rcode = result->intValue();
    if (rcode == 0) {
        txt << "success(0)";
    } else {
        txt << "failure(" << rcode << ")";
    }

    // Was any text provided? If yes, include it.
    ConstElementPtr txt_elem = msg->get(CONTROL_TEXT);
    if (txt_elem) {
        txt << ", text=" << txt_elem->stringValue();
    }

    return (txt.str());
}

ConstElementPtr
createCommand(const std::string& command) {
    return (createCommand(command, ElementPtr(), ""));
}

ConstElementPtr
createCommand(const std::string& command, ConstElementPtr arg) {
    return (createCommand(command, arg, ""));
}

ConstElementPtr
createCommand(const std::string& command, const std::string& service) {
    return (createCommand(command, ElementPtr(), service));
}

ConstElementPtr
createCommand(const std::string& command,
              ConstElementPtr arg,
              const std::string& service) {
    ElementPtr query = Element::createMap();
    ElementPtr cmd = Element::create(command);
    query->set(CONTROL_COMMAND, cmd);
    if (arg) {
        query->set(CONTROL_ARGUMENTS, arg);
    }
    if (!service.empty()) {
        ElementPtr services = Element::createList();
        services->add(Element::create(service));
        query->set(CONTROL_SERVICE, services);
    }
    return (query);
}

std::string
parseCommand(ConstElementPtr& arg, ConstElementPtr command) {
    if (!command) {
        isc_throw(CtrlChannelError, "invalid command: no command specified");
    }
    if (command->getType() != Element::map) {
        isc_throw(CtrlChannelError, "invalid command: expected toplevel entry to be a map, got "
                  << Element::typeToName(command->getType()) << " instead");
    }
    if (!command->contains(CONTROL_COMMAND)) {
        isc_throw(CtrlChannelError,
                  "invalid command: does not contain mandatory '" << CONTROL_COMMAND << "'");
    }

    // Make sure that all specified parameters are supported.
    auto const& command_params = command->mapValue();
    for (auto const& param : command_params) {
        if ((param.first != CONTROL_COMMAND) &&
            (param.first != CONTROL_ARGUMENTS) &&
            (param.first != CONTROL_SERVICE) &&
            (param.first != CONTROL_REMOTE_ADDRESS)) {
            isc_throw(CtrlChannelError,
                      "invalid command: unsupported parameter '" << param.first << "'");
        }
    }

    ConstElementPtr cmd = command->get(CONTROL_COMMAND);
    if (cmd->getType() != Element::string) {
        isc_throw(CtrlChannelError, "invalid command: expected '"
                  << CONTROL_COMMAND << "' to be a string, got "
                  << Element::typeToName(command->getType()) << " instead");
    }

    arg = command->get(CONTROL_ARGUMENTS);

    return (cmd->stringValue());
}

std::string
parseCommandWithArgs(ConstElementPtr& arg, ConstElementPtr command) {
    std::string command_name = parseCommand(arg, command);

    // This function requires arguments within the command.
    if (!arg) {
        isc_throw(CtrlChannelError,
                  "invalid command '" << command_name << "': no arguments specified");
    }

    // Arguments must be a map.
    if (arg->getType() != Element::map) {
        isc_throw(CtrlChannelError,
                  "invalid command '" << command_name << "': expected '"
                  << CONTROL_ARGUMENTS << "' to be a map, got "
                  << Element::typeToName(arg->getType()) << " instead");
    }

    // At least one argument is required.
    if (arg->size() == 0) {
        isc_throw(CtrlChannelError,
                  "invalid command '" << command_name << "': '"
                  << CONTROL_ARGUMENTS << "' is empty");
    }

    return (command_name);
}

ConstElementPtr
combineCommandsLists(const ConstElementPtr& response1,
                     const ConstElementPtr& response2) {
    // Usually when this method is called there should be two non-null
    // responses. If there is just a single response, return this
    // response.
    if (!response1 && response2) {
        return (response2);

    } else if (response1 && !response2) {
        return (response1);

    } else if (!response1 && !response2) {
        return (ConstElementPtr());

    } else {
        // Both responses are non-null so we need to combine the lists
        // of supported commands if the status codes are 0.
        int status_code;
        ConstElementPtr args1 = parseAnswer(status_code, response1);
        if (status_code != 0) {
            return (response1);
        }

        ConstElementPtr args2 = parseAnswer(status_code, response2);
        if (status_code != 0) {
            return (response2);
        }

        const std::vector<ElementPtr> vec1 = args1->listValue();
        const std::vector<ElementPtr> vec2 = args2->listValue();

        // Storing command names in a set guarantees that the non-unique
        // command names are aggregated.
        std::set<std::string> combined_set;
        for (auto const& v : vec1) {
            combined_set.insert(v->stringValue());
        }
        for (auto const& v : vec2) {
            combined_set.insert(v->stringValue());
        }

        // Create a combined list of commands.
        ElementPtr combined_list = Element::createList();
        for (auto const& s : combined_set) {
            combined_list->add(Element::create(s));
        }
        return (createAnswer(CONTROL_RESULT_SUCCESS, combined_list));
    }
}

}  // namespace config
}  // namespace isc
