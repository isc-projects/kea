// Copyright (C) 2025 Ada Logcis Ltd.
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
////////////////////////////////////////////////////////////////////////////////
// Copyright (C) 2025 Ada Logcis Ltd.
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
////////////////////////////////////////////////////////////////////////////////
#include <config.h>
#include <fuzzer/FuzzedDataProvider.h>

#include <d2/parser_context.h>
#include <d2srv/d2_cfg_mgr.h>
#include <d2srv/d2_simple_parser.h>
#include <d2srv/d2_update_message.h>
#include <dhcp_ddns/ncr_msg.h>
#include <dns/message.h>
#include <dns/name.h>
#include <dns/tsig.h>
#include <dns/tsigkey.h>

#include <cc/data.h>
#include <exceptions/exceptions.h>

#include <cstddef>
#include <cstdint>
#include <string>
#include <memory>

using namespace isc::d2;
using namespace isc::data;
using namespace isc::dhcp_ddns;
using namespace isc::dns;
using namespace isc::util;

static const D2ParserContext::ParserType types[] = {
    D2ParserContext::PARSER_JSON,
    D2ParserContext::PARSER_DHCPDDNS,
    D2ParserContext::PARSER_SUB_DHCPDDNS,
    D2ParserContext::PARSER_TSIG_KEY,
    D2ParserContext::PARSER_TSIG_KEYS,
    D2ParserContext::PARSER_DDNS_DOMAIN,
    D2ParserContext::PARSER_DDNS_DOMAINS,
    D2ParserContext::PARSER_DNS_SERVER,
    D2ParserContext::PARSER_DNS_SERVERS,
    D2ParserContext::PARSER_HOOKS_LIBRARY
};

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
    FuzzedDataProvider fdp(data, size);
    bool checkOnly = fdp.ConsumeBool();
    uint8_t index = fdp.ConsumeIntegralInRange<uint8_t>(0, static_cast<uint8_t>(sizeof(types) / sizeof(types[0]) - 1));

    D2SimpleParser simpleParser;
    D2CfgContextPtr ctxPtr(new D2CfgContext());
    D2ParserContext ctx;
    ElementPtr elem;

    // Generate random parsing mode
    D2ParserContext::ParserType type = types[index];

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
        D2SimpleParser::setAllDefaults(elem);
        simpleParser.parse(ctxPtr, elem, checkOnly);
    } catch (const isc::Exception&) {
        // Slient exceptions
    }

    // Prepare buffer
    InputBuffer buf(reinterpret_cast<const uint8_t*>(payload.data()), payload.size());

    // Target NameChangeRequest::fromtFormat
    try {
        NameChangeRequest::fromFormat(NameChangeFormat::FMT_JSON, buf);
    } catch (const isc::Exception&) {
        // Slient exceptions
    }

    // Target Message fromWire
    try {
        Message msg(Message::PARSE);
        msg.fromWire(buf);
    } catch (const isc::Exception&) {
        // Slient exceptions
    }

    // Target D2UpdateMessage fromWire (Inbound)
    try {
        TSIGKey tsigkey("fuzz_key:fuzz_key");
        TSIGContext tsigctx(tsigkey);
        D2UpdateMessage message(D2UpdateMessage::INBOUND);
        message.fromWire(payload.data(), payload.size(), &tsigctx) ;
    } catch (const isc::Exception&) {
        // Slient exceptions
    }

    // Target D2UpdateMessage fromWire (Outbound)
    try {
        TSIGKey tsigkey("fuzz_key:fuzz_key");
        TSIGContext tsigctx(tsigkey);
        D2UpdateMessage message(D2UpdateMessage::OUTBOUND);
        message.fromWire(payload.data(), payload.size(), &tsigctx);
    } catch (const isc::Exception&) {
        // Slient exceptions
    }

    return 0;
}
