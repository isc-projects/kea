// Copyright (C) 2018-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <cc/data.h>
#include <exceptions/exceptions.h>
#include <netconf/netconf_log.h>
#include <netconf/netconf_parser.h>
#include <netconf/parser_context.h>

#include <fstream>
#include <limits>
#include <sstream>

namespace isc {
namespace netconf {

ParserContext::ParserContext()
  : sfile_(0), ctx_(NO_KEYWORDS), trace_scanning_(false), trace_parsing_(false)
{
}

ParserContext::~ParserContext()
{
}

isc::data::ElementPtr
ParserContext::parseString(string const& str, ParserType parser_type)
{
    scanStringBegin(str, parser_type);
    return (parseCommon());
}

isc::data::ElementPtr
ParserContext::parseFile(string const& filename, ParserType parser_type) {
    FILE* f = fopen(filename.c_str(), "r");
    if (!f) {
        isc_throw(ParseError, "Unable to open file " << filename);
    }
    scanFileBegin(f, filename, parser_type);
    return (parseCommon());
}

isc::data::ElementPtr
ParserContext::parseCommon() {
    isc::netconf::NetconfParser parser(*this);
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
ParserContext::error(const isc::netconf::location& loc,
                     string const& what,
                     size_t pos)
{
    if (pos == 0) {
        isc_throw(ParseError, loc << ": " << what);
    } else {
        isc_throw(ParseError, loc << " (near " << pos << "): " << what);
    }
}

void
ParserContext::error(string const& what)
{
    isc_throw(ParseError, what);
}

void
ParserContext::fatal(string const& what)
{
    isc_throw(ParseError, what);
}

isc::data::Element::Position
ParserContext::loc2pos(isc::netconf::location& loc)
{
    string const& file = *loc.begin.filename;
    const uint32_t line = loc.begin.line;
    const uint32_t pos = loc.begin.column;
    return (isc::data::Element::Position(file, line, pos));
}

void
ParserContext::require(string const& name,
                       isc::data::Element::Position open_loc,
                       isc::data::Element::Position close_loc)
{
    ConstElementPtr value = stack_.back()->get(name);
    if (!value) {
        isc_throw(ParseError,
                  "missing parameter '" << name << "' ("
                  << stack_.back()->getPosition() << ") ["
                  << contextName() << " map between "
                  << open_loc << " and " << close_loc << "]");
    }
}

void
ParserContext::unique(string const& name,
                      isc::data::Element::Position loc)
{
    ConstElementPtr value = stack_.back()->get(name);
    if (value) {
        if (ctx_ != NO_KEYWORDS) {
            isc_throw(ParseError, loc << ": duplicate " << name
                      << " entries in " << contextName()
                      << " map (previous at " << value->getPosition() << ")");
        } else {
            isc_throw(ParseError, loc << ": duplicate " << name
                      << " entries in JSON"
                      << " map (previous at " << value->getPosition() << ")");
        }
    }
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

string const
ParserContext::contextName()
{
    switch (ctx_) {
    case NO_KEYWORDS:
        return ("__no keywords__");
    case CONFIG:
        return ("toplevel");
    case NETCONF:
        return ("Netconf");
    case MANAGED_SERVERS:
        return ("managed-servers");
    case SERVER:
        return ("managed-servers entry");
    case CONTROL_SOCKET:
        return ("control-socket");
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

void
ParserContext::warning(const isc::netconf::location& loc,
                       string const& what) {
    ostringstream msg;
    msg << loc << ": " << what;
    LOG_WARN(netconf_logger, NETCONF_CONFIG_SYNTAX_WARNING)
        .arg(msg.str());
}

void
ParserContext::warnAboutExtraCommas(const isc::netconf::location& loc) {
    warning(loc, "Extraneous comma. A piece of configuration may have been omitted.");
}

}  // namespace netconf
}  // namespace isc
