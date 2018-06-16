// Copyright (C) 2017-2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <agent/parser_context.h>
#include <agent/agent_parser.h>
#include <exceptions/exceptions.h>
#include <cc/dhcp_config_error.h>
#include <cc/data.h>
#include <fstream>
#include <limits>

namespace isc {
namespace agent {

ParserContext::ParserContext()
  : sfile_(0), ctx_(NO_KEYWORDS), trace_scanning_(false), trace_parsing_(false)
{
}

ParserContext::~ParserContext()
{
}

isc::data::ElementPtr
ParserContext::parseString(const std::string& str, ParserType parser_type)
{
    scanStringBegin(str, parser_type);
    return (parseCommon());
}

isc::data::ElementPtr
ParserContext::parseFile(const std::string& filename, ParserType parser_type) {
    FILE* f = fopen(filename.c_str(), "r");
    if (!f) {
        isc_throw(ParseError, "Unable to open file " << filename);
    }
    scanFileBegin(f, filename, parser_type);
    return (parseCommon());
}

isc::data::ElementPtr
ParserContext::parseCommon() {
    isc::agent::AgentParser parser(*this);
    // Uncomment this to get detailed parser logs.
    // trace_parsing_ = true;
    parser.set_debug_level(trace_parsing_);
    try {
        int res = parser.parse();
        if (res != 0) {
            isc_throw(ParseError, "Parser abort");
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
        isc_throw(ParseError, "Expected exactly one terminal Element expected, found "
                  << stack_.size());
    }
}


void
ParserContext::error(const isc::agent::location& loc, const std::string& what)
{
    isc_throw(ParseError, loc << ": " << what);
}

void
ParserContext::error(const std::string& what)
{
    isc_throw(ParseError, what);
}

void
ParserContext::fatal(const std::string& what)
{
    isc_throw(ParseError, what);
}

isc::data::Element::Position
ParserContext::loc2pos(isc::agent::location& loc)
{
    const std::string& file = *loc.begin.filename;
    const uint32_t line = loc.begin.line;
    const uint32_t pos = loc.begin.column;
    return (isc::data::Element::Position(file, line, pos));
}

void
ParserContext::enter(const LexerContext& ctx)
{
    cstack_.push_back(ctx_);
    ctx_ = ctx;
}

void
ParserContext::leave()
{
    if (cstack_.empty()) {
        fatal("unbalanced syntactic context");
    }
    ctx_ = cstack_.back();
    cstack_.pop_back();
}

const std::string
ParserContext::contextName()
{
    switch (ctx_) {
    case NO_KEYWORDS:
        return ("__no keywords__");
    case CONFIG:
        return ("toplevel");
    case AGENT:
        return ("Control-agent");
    case LOGGING:
        return ("Logging");
    case CONTROL_SOCKETS:
        return ("control-sockets");
    case SERVER:
        return ("xxx-server");
    case SOCKET_TYPE:
        return ("socket-type");
    case HOOKS_LIBRARIES:
        return ("hooks-libraries");
    case LOGGERS:
        return ("loggers");
    case OUTPUT_OPTIONS:
        return ("output-options");
    default:
        return ("__unknown__");
    }
}

};
};
