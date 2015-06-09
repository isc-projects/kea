// Copyright (C) 2009,2015  Internet Systems Consortium, Inc. ("ISC")
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

#include <exceptions/exceptions.h>
#include <config/command_interpreter.h>
#include <string>
#include <cc/data.h>

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
    return (createAnswer(0, string(""), ConstElementPtr()));
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
parseAnswer(int &rcode, const ConstElementPtr& msg) {
    if (!msg) {
        isc_throw(CtrlChannelError, "No answer specified");
    }
    if (msg->getType() != Element::map) {
        isc_throw(CtrlChannelError,
                  "Invalid answer Element specified, expected map");
    }
    if (!msg->contains(CONTROL_RESULT)) {
        isc_throw(CtrlChannelError,
                  "Invalid answer specified, does not contain mandatory 'result'");
    }

    ConstElementPtr result = msg->get(CONTROL_RESULT);
    if (result->getType() != Element::integer) {
            isc_throw(CtrlChannelError,
                      "Result element in answer message is not a string");
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

ConstElementPtr
createCommand(const std::string& command) {
    return (createCommand(command, ElementPtr()));
}

ConstElementPtr
createCommand(const std::string& command, ConstElementPtr arg) {
    ElementPtr query = Element::createMap();
    ElementPtr cmd = Element::create(command);
    query->set(CONTROL_COMMAND, cmd);
    if (arg) {
        query->set(CONTROL_ARGUMENTS, arg);
    }
    return (query);
}

std::string
parseCommand(ConstElementPtr& arg, ConstElementPtr command) {
    if (!command) {
        isc_throw(CtrlChannelError, "No command specified");
    }
    if (command->getType() != Element::map) {
        isc_throw(CtrlChannelError, "Invalid command Element specified, expected map");
    }
    if (!command->contains(CONTROL_COMMAND)) {
        isc_throw(CtrlChannelError,
                  "Invalid answer specified, does not contain mandatory 'command'");
    }

    ConstElementPtr cmd = command->get(CONTROL_COMMAND);
    if (cmd->getType() != Element::string) {
        isc_throw(CtrlChannelError,
                  "'command' element in command message is not a string");
    }

    arg = command->get(CONTROL_ARGUMENTS);

    return (cmd->stringValue());
}

}
}
