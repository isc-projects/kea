// Copyright (C) 2017-2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <d2/d2_parser.h>
#include <d2/parser_context.h>
#include <exceptions/exceptions.h>
#include <cc/data.h>
#include <boost/lexical_cast.hpp>
#include <fstream>
#include <limits>

namespace isc {
namespace d2 {

D2ParserContext::D2ParserContext()
  : sfile_(0), ctx_(NO_KEYWORD), trace_scanning_(false), trace_parsing_(false)
{
}

isc::data::ElementPtr
D2ParserContext::parseString(const std::string& str, ParserType parser_type)
{
    scanStringBegin(str, parser_type);
    return (parseCommon());
}

isc::data::ElementPtr
D2ParserContext::parseFile(const std::string& filename, ParserType parser_type) {
    FILE* f = fopen(filename.c_str(), "r");
    if (!f) {
        isc_throw(D2ParseError, "Unable to open file " << filename);
    }
    scanFileBegin(f, filename, parser_type);
    return (parseCommon());
}

isc::data::ElementPtr
D2ParserContext::parseCommon() {
    isc::d2::D2Parser parser(*this);
    // Uncomment this to get detailed parser logs.
    // trace_parsing_ = true;
    parser.set_debug_level(trace_parsing_);
    try {
        int res = parser.parse();
        if (res != 0) {
            isc_throw(D2ParseError, "Parser abort");
        }
        scanEnd();
    }
    catch (...) {
        scanEnd();
        throw;
    }
    if (stack_.size() == 1) {
        return (stack_[0]);
    } else {
        isc_throw(D2ParseError, "Expected exactly one terminal Element expected, found "
                  << stack_.size());
    }
}


void
D2ParserContext::error(const isc::d2::location& loc, const std::string& what)
{
    isc_throw(D2ParseError, loc << ": " << what);
}

void
D2ParserContext::error (const std::string& what)
{
    isc_throw(D2ParseError, what);
}

void
D2ParserContext::fatal (const std::string& what)
{
    isc_throw(D2ParseError, what);
}

isc::data::Element::Position
D2ParserContext::loc2pos(isc::d2::location& loc)
{
    const std::string& file = *loc.begin.filename;
    const uint32_t line = loc.begin.line;
    const uint32_t pos = loc.begin.column;
    return (isc::data::Element::Position(file, line, pos));
}

void
D2ParserContext::enter(const ParserContext& ctx)
{
    cstack_.push_back(ctx_);
    ctx_ = ctx;
}

void
D2ParserContext::leave()
{
    if (cstack_.empty()) {
        fatal("unbalanced syntactic context");
    }

    ctx_ = cstack_.back();
    cstack_.pop_back();
}

const std::string
D2ParserContext::contextName()
{
    switch (ctx_) {
    case NO_KEYWORD:
        return ("__no keyword__");
    case CONFIG:
        return ("toplevel");
    case DHCPDDNS:
        return ("DhcpDdns");
    case TSIG_KEY:
        return ("tsig-key");
    case TSIG_KEYS:
        return ("tsig-keys");
    case ALGORITHM:
        return("algorithm");
    case DIGEST_BITS:
        return("digest-bits");
    case SECRET:
        return("secret");
    case FORWARD_DDNS:
        return("forward-ddns");
    case REVERSE_DDNS:
        return("reverse-ddns");
    case DDNS_DOMAIN:
        return("ddns-domain");
    case DDNS_DOMAINS:
        return("ddns-domains");
    case DNS_SERVER:
        return("dns-server");
    case DNS_SERVERS:
        return("dns-servers");
    case CONTROL_SOCKET:
        return("control-socket");
    case LOGGING:
        return ("Logging");
    case LOGGERS:
        return ("loggers");
    case OUTPUT_OPTIONS:
        return ("output-options");
    case NCR_PROTOCOL:
        return ("ncr-protocol");
    case NCR_FORMAT:
        return ("ncr-format");
    default:
        return ("__unknown__");
    }
}

};
};
