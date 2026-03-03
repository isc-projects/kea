// Copyright (C) 2025 Ada Logcis Ltd.
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
////////////////////////////////////////////////////////////////////////////////
#include "config.h"
#include <fuzzer/FuzzedDataProvider.h>

#include <agent/parser_context.h>
#include <agent/simple_parser.h>
#include <agent/ca_cfg_mgr.h>

#include <cc/data.h>
#include <exceptions/exceptions.h>

#include <string>
#include <memory>

using namespace isc::agent;
using namespace isc::data;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
    FuzzedDataProvider fdp(data, size);
    bool checkOnly = fdp.ConsumeBool();

    AgentSimpleParser simpleParser;
    CtrlAgentCfgContextPtr ctxPtr(new CtrlAgentCfgContext());
    ParserContext ctx;
    ElementPtr elem;

    // Generate random parsing mode
    const uint8_t mode = fdp.ConsumeIntegralInRange<uint8_t>(0, 2);
    ParserContext::ParserType type = ParserContext::PARSER_JSON;
    if (mode == 1) {
        type = ParserContext::PARSER_AGENT;
    } else if (mode == 2) {
        type = ParserContext::PARSER_SUB_AGENT;
    }

    const std::string payload = fdp.ConsumeRemainingBytesAsString();

    // Target context parseString
    try {
        ctx.parseString(payload, type);
    } catch (const isc::Exception&) {
        // Slient exceptions
    }

    // Parse payload to JSON
    try {
        elem = Element::fromJSON(payload);
    } catch (...) {
        // If failed to parse the payload, early exit
        return 0;
    }

    // Target SimpleParser
    try {
        AgentSimpleParser::setAllDefaults(elem);
        simpleParser.checkTlsSetup(elem);
        simpleParser.parse(ctxPtr, elem, checkOnly);
    } catch (const isc::Exception&) {
        // Slient exceptions
    }

    return 0;
}
