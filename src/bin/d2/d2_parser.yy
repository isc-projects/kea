/* Copyright (C) 2017 Internet Systems Consortium, Inc. ("ISC")

   This Source Code Form is subject to the terms of the Mozilla Public
   License, v. 2.0. If a copy of the MPL was not distributed with this
   file, You can obtain one at http://mozilla.org/MPL/2.0/. */

%skeleton "lalr1.cc" /* -*- C++ -*- */
%require "3.0.0"
%defines
%define parser_class_name {D2Parser}
%define api.prefix {d2_parser_}
%define api.token.constructor
%define api.value.type variant
%define api.namespace {isc::d2}
%define parse.assert
%code requires
{
#include <string>
#include <cc/data.h>
#include <d2/d2_config.h>
#include <boost/lexical_cast.hpp>
#include <d2/parser_context_decl.h>

using namespace isc::d2;
using namespace isc::data;
using namespace std;
}
// The parsing context.
%param { isc::d2::D2ParserContext& ctx }
%locations
%define parse.trace
%define parse.error verbose
%code
{
#include <d2/parser_context.h>
}


%define api.token.prefix {TOKEN_}
// Tokens in an order which makes sense and related to the intented use.
// Actual regexps for tokens are defined in d2_lexer.ll.
%token
  END  0  "end of file"
  COMMA ","
  COLON ":"
  LSQUARE_BRACKET "["
  RSQUARE_BRACKET "]"
  LCURLY_BRACKET "{"
  RCURLY_BRACKET "}"
  NULL_TYPE "null"

  DHCP6 "Dhcp6"
  DHCP4 "Dhcp4"

  DHCPDDNS "DhcpDdns"
  IP_ADDRESS "ip-address"
  PORT "port"
  DNS_SERVER_TIMEOUT "dns-server-timeout"
  NCR_PROTOCOL "ncr-protocol"
  UDP "UDP"
  TCP "TCP"
  NCR_FORMAT "ncr-format"
  JSON "JSON"
  FORWARD_DDNS "forward-ddns"
  REVERSE_DDNS "reverse-ddns"
  TSIG_KEYS "tsig-keys"

  LOGGING "Logging"
  LOGGERS "loggers"
  NAME "name"
  OUTPUT_OPTIONS "output_options"
  OUTPUT "output"
  DEBUGLEVEL "debuglevel"
  SEVERITY "severity"

  // Not real tokens, just a way to signal what the parser is expected to
  // parse.
  TOPLEVEL_JSON
  TOPLEVEL_DHCPDDNS
  SUB_DHCPDDNS
;

%token <std::string> STRING "constant string"
%token <int64_t> INTEGER "integer"
%token <double> FLOAT "floating point"
%token <bool> BOOLEAN "boolean"

%type <ElementPtr> value
%type <ElementPtr> ncr_protocol_value

%printer { yyoutput << $$; } <*>;

%%

// The whole grammar starts with a map, because the config file
// constists of Dhcp, Logger and DhcpDdns entries in one big { }.
// We made the same for subparsers at the exception of the JSON value.
%start start;

start: TOPLEVEL_JSON { ctx.ctx_ = ctx.NO_KEYWORD; } sub_json
     | TOPLEVEL_DHCPDDNS { ctx.ctx_ = ctx.CONFIG; } syntax_map
     | SUB_DHCPDDNS { ctx.ctx_ = ctx.DHCPDDNS; } sub_dhcpddns
     ;

// ---- generic JSON parser ---------------------------------

// Note that ctx_ is NO_KEYWORD here

// Values rule
value: INTEGER { $$ = ElementPtr(new IntElement($1, ctx.loc2pos(@1))); }
     | FLOAT { $$ = ElementPtr(new DoubleElement($1, ctx.loc2pos(@1))); }
     | BOOLEAN { $$ = ElementPtr(new BoolElement($1, ctx.loc2pos(@1))); }
     | STRING { $$ = ElementPtr(new StringElement($1, ctx.loc2pos(@1))); }
     | NULL_TYPE { $$ = ElementPtr(new NullElement(ctx.loc2pos(@1))); }
     | map2 { $$ = ctx.stack_.back(); ctx.stack_.pop_back(); }
     | list_generic { $$ = ctx.stack_.back(); ctx.stack_.pop_back(); }
     ;

sub_json: value {
    // Push back the JSON value on the stack
    ctx.stack_.push_back($1);
};

map2: LCURLY_BRACKET {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(@1)));
    ctx.stack_.push_back(m);
} map_content RCURLY_BRACKET {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
};

// Assignments rule
map_content: %empty // empty map
           | not_empty_map
           ;

not_empty_map: STRING COLON value {
                  // map containing a single entry
                  ctx.stack_.back()->set($1, $3);
                  }
             | not_empty_map COMMA STRING COLON value {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set($3, $5);
                  }
             ;

list_generic: LSQUARE_BRACKET {
    ElementPtr l(new ListElement(ctx.loc2pos(@1)));
    ctx.stack_.push_back(l);
} list_content RSQUARE_BRACKET {
    // list parsing complete. Put any sanity checking here
};

//// This one is used in syntax parser.
//list2: LSQUARE_BRACKET {
//    // List parsing about to start
//} list_content RSQUARE_BRACKET {
//    // list parsing complete. Put any sanity checking here
//    //ctx.stack_.pop_back();
//};

list_content: %empty // Empty list
            | not_empty_list
            ;

not_empty_list: value {
                  // List consisting of a single element.
                  ctx.stack_.back()->add($1);
                  }
              | not_empty_list COMMA value {
                  // List ending with , and a value.
                  ctx.stack_.back()->add($3);
                  }
              ;

// ---- generic JSON parser ends here ----------------------------------

// ---- syntax checking parser starts here -----------------------------

// Unknown keyword in a map
unknown_map_entry: STRING COLON {
    const std::string& where = ctx.contextName();
    const std::string& keyword = $1;
    error(@1,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
};


// This defines the top-level { } that holds Dhcp6, Dhcp4, DhcpDdns or Logging
// objects.
syntax_map: LCURLY_BRACKET {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(@1)));
    ctx.stack_.push_back(m);
} global_objects RCURLY_BRACKET {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
};

// This represents top-level entries: Dhcp6, Dhcp4, DhcpDdns, Logging
global_objects: global_object
              | global_objects COMMA global_object
              ;

// This represents a single top level entry, e.g. Dhcp6 or DhcpDdns.
global_object: dhcp6_json_object
             | logging_object
             | dhcp4_json_object
             | dhcpddns_object
             | unknown_map_entry
             ;

// --- dhcp ddns ---------------------------------------------

dhcpddns_object: DHCPDDNS {
    ElementPtr m(new MapElement(ctx.loc2pos(@1)));
    ctx.stack_.back()->set("DhcpDdns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCPDDNS);
} COLON LCURLY_BRACKET dhcpddns_params RCURLY_BRACKET {
    ctx.stack_.pop_back();
    ctx.leave();
};

sub_dhcpddns: LCURLY_BRACKET {
    // Parse the dhcpddns map
    ElementPtr m(new MapElement(ctx.loc2pos(@1)));
    ctx.stack_.push_back(m);
} dhcpddns_params RCURLY_BRACKET {
    // parsing completed
};

dhcpddns_params: dhcpddns_param
                | dhcpddns_params COMMA dhcpddns_param
                ;
// These are teh top-level parameters allowed for DhcpDdns
dhcpddns_param: ip_address
               | port
               | dns_server_timeout
               | ncr_protocol
               | ncr_format
               | forward_ddns
               | reverse_ddns
               | tsig_keys
               | unknown_map_entry
               ;

ip_address: IP_ADDRESS {
    ctx.enter(ctx.NO_KEYWORD);
} COLON STRING {
    ElementPtr s(new StringElement($4, ctx.loc2pos(@4)));
    ctx.stack_.back()->set("ip-address", s);
    ctx.leave();
};

port: PORT COLON INTEGER {
    if ($3 <= 0) {
        error(@3, "port must be greater than zero");
    } 
    ElementPtr i(new IntElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("port", i);
};

dns_server_timeout: DNS_SERVER_TIMEOUT COLON INTEGER {
    if ($3 <= 0) {
        error(@3, "dns-server-timeout must be greater than zero");
    } else { 
        ElementPtr i(new IntElement($3, ctx.loc2pos(@3)));
        ctx.stack_.back()->set("dns-server-timeout", i);
    }
};

ncr_protocol: NCR_PROTOCOL {
    ctx.enter(ctx.NCR_PROTOCOL);
} COLON ncr_protocol_value {
    ctx.stack_.back()->set("ncr-protocol", $4);
    ctx.leave();
};

ncr_protocol_value:
    UDP { $$ = ElementPtr(new StringElement("UDP", ctx.loc2pos(@1))); }
  | TCP { $$ = ElementPtr(new StringElement("TCP", ctx.loc2pos(@1))); }
  ;

ncr_format: NCR_FORMAT {
    ctx.enter(ctx.NCR_FORMAT);
} COLON JSON {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(@4)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
};

forward_ddns : FORWARD_DDNS {
    ctx.enter(ctx.NO_KEYWORD);
} COLON value {
    ctx.stack_.back()->set("forward-ddns", $4);
    ctx.leave();
};

reverse_ddns : REVERSE_DDNS {
    ctx.enter(ctx.NO_KEYWORD);
} COLON value {
    ctx.stack_.back()->set("reverse-ddns", $4);
    ctx.leave();
};

tsig_keys : TSIG_KEYS {
    ctx.enter(ctx.NO_KEYWORD);
} COLON value {
    ctx.stack_.back()->set("tsig-keys", $4);
    ctx.leave();
};

dhcp6_json_object: DHCP6 {
    ctx.enter(ctx.NO_KEYWORD);
} COLON value {
    ctx.stack_.back()->set("Dhcp6", $4);
    ctx.leave();
};

dhcp4_json_object: DHCP4 {
    ctx.enter(ctx.NO_KEYWORD);
} COLON value {
    ctx.stack_.back()->set("Dhcp4", $4);
    ctx.leave();
};

// --- logging entry -----------------------------------------

// This defines the top level "Logging" object. It parses
// the following "Logging": { ... }. The ... is defined
// by logging_params
logging_object: LOGGING {
    ElementPtr m(new MapElement(ctx.loc2pos(@1)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
} COLON LCURLY_BRACKET logging_params RCURLY_BRACKET {
    ctx.stack_.pop_back();
    ctx.leave();
};

// This defines the list of allowed parameters that may appear
// in the top-level Logging object. It can either be a single
// parameter or several parameters separated by commas.
logging_params: logging_param
              | logging_params COMMA logging_param
              ;

// There's currently only one parameter defined, which is "loggers".
logging_param: loggers;

// "loggers", the only parameter currently defined in "Logging" object,
// is "Loggers": [ ... ].
loggers: LOGGERS {
    ElementPtr l(new ListElement(ctx.loc2pos(@1)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}  COLON LSQUARE_BRACKET loggers_entries RSQUARE_BRACKET {
    ctx.stack_.pop_back();
    ctx.leave();
};

// These are the parameters allowed in loggers: either one logger
// entry or multiple entries separate by commas.
loggers_entries: logger_entry
               | loggers_entries COMMA logger_entry
               ;

// This defines a single entry defined in loggers in Logging.
logger_entry: LCURLY_BRACKET {
    ElementPtr l(new MapElement(ctx.loc2pos(@1)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
} logger_params RCURLY_BRACKET {
    ctx.stack_.pop_back();
};

logger_params: logger_param
             | logger_params COMMA logger_param
             ;

logger_param: name
            | output_options_list
            | debuglevel
            | severity
            | unknown_map_entry
            ;

name: NAME {
    ctx.enter(ctx.NO_KEYWORD);
} COLON STRING {
    ElementPtr name(new StringElement($4, ctx.loc2pos(@4)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
};

debuglevel: DEBUGLEVEL COLON INTEGER {
    ElementPtr dl(new IntElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("debuglevel", dl);
};
severity: SEVERITY {
    ctx.enter(ctx.NO_KEYWORD);
} COLON STRING {
    ElementPtr sev(new StringElement($4, ctx.loc2pos(@4)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
};

output_options_list: OUTPUT_OPTIONS {
    ElementPtr l(new ListElement(ctx.loc2pos(@1)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
} COLON LSQUARE_BRACKET output_options_list_content RSQUARE_BRACKET {
    ctx.stack_.pop_back();
    ctx.leave();
};

output_options_list_content: output_entry
                           | output_options_list_content COMMA output_entry
                           ;

output_entry: LCURLY_BRACKET {
    ElementPtr m(new MapElement(ctx.loc2pos(@1)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
} output_params RCURLY_BRACKET {
    ctx.stack_.pop_back();
};

output_params: output_param
             | output_params COMMA output_param
             ;

output_param: OUTPUT {
    ctx.enter(ctx.NO_KEYWORD);
} COLON STRING {
    ElementPtr sev(new StringElement($4, ctx.loc2pos(@4)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
};

%%

void
isc::d2::D2Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
