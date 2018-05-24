// Copyright (C) 2016-2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <dhcp6/parser_context.h>
#include <dhcp6/dhcp6_parser.h>
#include <exceptions/exceptions.h>
#include <cc/data.h>
#include <boost/lexical_cast.hpp>
#include <fstream>
#include <limits>

namespace isc {
namespace dhcp {

Parser6Context::Parser6Context()
  : ctx_(NO_KEYWORD), trace_scanning_(false), trace_parsing_(false)
{
}

Parser6Context::~Parser6Context()
{
}

isc::data::ElementPtr
Parser6Context::parseString(const std::string& str, ParserType parser_type)
{
    scanStringBegin(str, parser_type);
    return (parseCommon());
}

isc::data::ElementPtr
Parser6Context::parseFile(const std::string& filename, ParserType parser_type) {
    FILE* f = fopen(filename.c_str(), "r");
    if (!f) {
        isc_throw(Dhcp6ParseError, "Unable to open file " << filename);
    }
    scanFileBegin(f, filename, parser_type);
    return (parseCommon());
}

isc::data::ElementPtr
Parser6Context::parseCommon() {
    isc::dhcp::Dhcp6Parser parser(*this);
    // Uncomment this to get detailed parser logs.
    // trace_parsing_ = true;
    parser.set_debug_level(trace_parsing_);
    try {
        int res = parser.parse();
        if (res != 0) {
            isc_throw(Dhcp6ParseError, "Parser abort");
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
        isc_throw(Dhcp6ParseError, "Expected exactly one terminal Element expected, found "
                  << stack_.size());
    }
}


void
Parser6Context::error(const isc::dhcp::location& loc, const std::string& what)
{
    isc_throw(Dhcp6ParseError, loc << ": " << what);
}

void
Parser6Context::error (const std::string& what)
{
    isc_throw(Dhcp6ParseError, what);
}

void
Parser6Context::fatal (const std::string& what)
{
    isc_throw(Dhcp6ParseError, what);
}

isc::data::Element::Position
Parser6Context::loc2pos(isc::dhcp::location& loc)
{
    const std::string& file = *loc.begin.filename;
    const uint32_t line = loc.begin.line;
    const uint32_t pos = loc.begin.column;
    return (isc::data::Element::Position(file, line, pos));
}

void
Parser6Context::require(const std::string& name,
                        isc::data::Element::Position open_loc,
                        isc::data::Element::Position close_loc)
{
    ConstElementPtr value = stack_.back()->get(name);
    if (!value) {
        isc_throw(Dhcp6ParseError,
                  "missing parameter '" << name << "' ("
                  << stack_.back()->getPosition() << ") ["
                  << contextName() << " map between "
                  << open_loc << " and " << close_loc << "]");
    }
}

void
Parser6Context::enter(const ParserContext& ctx)
{
    cstack_.push_back(ctx_);
    ctx_ = ctx;
}

void
Parser6Context::leave()
{
#if 1
    if (cstack_.empty()) {
        fatal("unbalanced syntactic context");
    }
#endif
    ctx_ = cstack_.back();
    cstack_.pop_back();
}

const std::string
Parser6Context::contextName()
{
    switch (ctx_) {
    case NO_KEYWORD:
        return ("__no keyword__");
    case CONFIG:
        return ("toplevel");
    case DHCP6:
        return ("Dhcp6");
    case LOGGING:
        return ("Logging");
    case INTERFACES_CONFIG:
        return ("interfaces-config");
    case LEASE_DATABASE:
        return ("lease-database");
    case HOSTS_DATABASE:
        return ("hosts-database");
    case DATABASE_TYPE:
        return ("database-type");
    case MAC_SOURCES:
        return ("mac-sources");
    case HOST_RESERVATION_IDENTIFIERS:
        return ("host-reservation-identifiers");
    case HOOKS_LIBRARIES:
        return ("hooks-libraries");
    case SUBNET6:
        return ("subnet6");
    case RESERVATION_MODE:
        return ("reservation-mode");
    case OPTION_DEF:
        return ("option-def");
    case OPTION_DATA:
        return ("option-data");
    case CLIENT_CLASSES:
        return ("client-classes");
    case EXPIRED_LEASES_PROCESSING:
        return ("expired-leases-processing");
    case SERVER_ID:
        return ("server-id");
    case DUID_TYPE:
        return ("duid-type");
    case CONTROL_SOCKET:
        return ("control-socket");
    case POOLS:
        return ("pools");
    case PD_POOLS:
        return ("pd-pools");
    case RESERVATIONS:
        return ("reservations");
    case RELAY:
        return ("relay");
    case LOGGERS:
        return ("loggers");
    case OUTPUT_OPTIONS:
        return ("output-options");
    case DHCP_DDNS:
        return ("dhcp-ddns");
    case NCR_PROTOCOL:
        return ("ncr-protocol");
    case NCR_FORMAT:
        return ("ncr-format");
    case REPLACE_CLIENT_NAME:
        return ("replace-client-name");
    case SHARED_NETWORK:
        return ("shared-networks");
     default:
        return ("__unknown__");
    }
}

};
};
