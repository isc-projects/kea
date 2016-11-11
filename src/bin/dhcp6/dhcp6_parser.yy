/* Copyright (C) 2015-2016 Internet Systems Consortium, Inc. ("ISC")

   This Source Code Form is subject to the terms of the Mozilla Public
   License, v. 2.0. If a copy of the MPL was not distributed with this
   file, You can obtain one at http://mozilla.org/MPL/2.0/. */

%skeleton "lalr1.cc" /* -*- C++ -*- */
%require "3.0.0"
%defines
%define parser_class_name {Dhcp6Parser}
%define api.prefix {parser6_}
%define api.token.constructor
%define api.value.type variant
%define api.namespace {isc::dhcp}
%define parse.assert
%code requires
{
#include <string>
#include <cc/data.h>
#include <dhcp/option.h>
#include <boost/lexical_cast.hpp>
#include <dhcp6/parser_context_decl.h>

using namespace isc::dhcp;
using namespace isc::data;
using namespace std;
}
// The parsing context.
%param { isc::dhcp::Parser6Context& ctx }
%locations
%define parse.trace
%define parse.error verbose
%code
{
#include <dhcp6/parser_context.h>

}

%define api.token.prefix {TOKEN_}
// Tokens in an order which makes sense and related to the intented use.
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
  INTERFACES_CONFIG "interfaces-config"
  INTERFACES "interfaces"
  LEASE_DATABASE "lease-database"
  TYPE "type"
  PREFERRED_LIFETIME "preferred-lifetime"
  VALID_LIFETIME "valid-lifetime"
  RENEW_TIMER "renew-timer"
  REBIND_TIMER "rebind-timer"
  SUBNET6 "subnet6"
  OPTION_DATA "option-data"
  NAME "name"
  DATA "data"
  CODE "code"
  POOLS "pools"
  POOL "pool"
  SUBNET "subnet"
  INTERFACE "interface"

  LOGGING "Logging"
  LOGGERS "loggers"
  OUTPUT_OPTIONS "output_options"
  OUTPUT "output"
  DEBUGLEVEL "debuglevel"
  SEVERITY "severity"
;

%token <std::string> STRING "constant string"
%token <int64_t> INTEGER "integer"
%token <double> FLOAT "floating point"
%token <bool> BOOLEAN "boolean"

%type <ElementPtr> value

%printer { yyoutput << $$; } <*>;

%%
// The whole grammar starts with a map, because the config file
// constists of Dhcp, Logger and DhcpDdns entries in one big { }.
// %start map - this will parse everything as generic JSON
// %start dhcp6_map - this will parse everything with Dhcp6 syntax checking
%start syntax_map;

// ---- generic JSON parser ---------------------------------

// Values rule
value : INTEGER { $$ = ElementPtr(new IntElement($1)); }
     | FLOAT { $$ = ElementPtr(new DoubleElement($1)); }
     | BOOLEAN { $$ = ElementPtr(new BoolElement($1)); }
     | STRING { $$ = ElementPtr(new StringElement($1)); }
     | NULL_TYPE { $$ = ElementPtr(new NullElement()); }
     | map { $$ = ctx.stack_.back(); ctx.stack_.pop_back(); }
     | list { $$ = ctx.stack_.back(); ctx.stack_.pop_back(); }
    ;

map: LCURLY_BRACKET {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement());
    ctx.stack_.push_back(m);
} map_content RCURLY_BRACKET {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
};

// Assignments rule
map_content:  { /* do nothing, it's an empty map */ }
    | STRING COLON value {
        // map containing a single entry
        ctx.stack_.back()->set($1, $3);
    }
    | map_content COMMA STRING COLON value {
        // map consisting of a shorter map followed by comma and string:value
        ctx.stack_.back()->set($3, $5);
    }
    ;

list: LSQUARE_BRACKET {
    // List parsing about to start
} list_content RSQUARE_BRACKET {
    // list parsing complete. Put any sanity checking here
};

list_content: { /* do nothing, it's an empty list */ }
    | value {
        // List consisting of a single element.
        ctx.stack_.back()->add($1);
    }
    | list_content COMMA value {
        // List ending with , and a value.
        ctx.stack_.back()->add($3);
    }
    ;

// ---- generic JSON parser ends here ----------------------------------

// ---- syntax checking parser starts here -----------------------------

// This defines the top-level { } that holds Dhcp6, Dhcp4, DhcpDdns or Logging
// objects.
syntax_map: LCURLY_BRACKET {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement());
    ctx.stack_.push_back(m);
} global_objects RCURLY_BRACKET {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
};

// This represents a single top level entry, e.g. Dhcp6 or DhcpDdns.
global_object: dhcp6_object
| logging_object;

// This represents top-level entries: Dhcp6, Dhcp4, DhcpDdns, Logging
global_objects
: global_object
| global_objects COMMA global_object
;

dhcp6_object: DHCP6 COLON LCURLY_BRACKET {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement());
    ctx.stack_.back()->set("Dhcp6", m);
    ctx.stack_.push_back(m);
} global_params RCURLY_BRACKET {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
    ctx.stack_.pop_back();
};

global_params: global_param
| global_params COMMA global_param;

// These are the parameters that are allowed in the top-level for
// Dhcp6.
global_param
: preferred_lifetime
| valid_lifetime
| renew_timer
| rebind_timer
| subnet6_list
| interfaces_config
| lease_database
;

preferred_lifetime: PREFERRED_LIFETIME COLON INTEGER {
    ElementPtr prf(new IntElement($3));
    ctx.stack_.back()->set("preferred-lifetime", prf);
};

valid_lifetime: VALID_LIFETIME COLON INTEGER {
    ElementPtr prf(new IntElement($3));
    ctx.stack_.back()->set("valid-lifetime", prf);
};

renew_timer: RENEW_TIMER COLON INTEGER {
    ElementPtr prf(new IntElement($3));
    ctx.stack_.back()->set("renew-timer", prf);
};

rebind_timer: REBIND_TIMER COLON INTEGER {
    ElementPtr prf(new IntElement($3));
    ctx.stack_.back()->set("rebind-timer", prf);
};

interfaces_config: INTERFACES_CONFIG COLON {
    ElementPtr i(new MapElement());
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
 } LCURLY_BRACKET interface_config_map RCURLY_BRACKET {
    ctx.stack_.pop_back();
};

interface_config_map: INTERFACES {
    ElementPtr l(new ListElement());
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
 } COLON list {
     ctx.stack_.pop_back();
 }

lease_database: LEASE_DATABASE {
    ElementPtr i(new MapElement());
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
}
COLON LCURLY_BRACKET lease_database_map_params {
     ctx.stack_.pop_back();
} RCURLY_BRACKET;

lease_database_map_params: lease_database_map_param
| lease_database_map_params COMMA lease_database_map_param;

lease_database_map_param: lease_database_type;

lease_database_type: TYPE COLON STRING {
    ElementPtr prf(new StringElement($3));
    ctx.stack_.back()->set("type", prf);
};

// This defines subnet6 as a list of maps.
// "subnet6": [ ... ]
subnet6_list: SUBNET6 COLON LSQUARE_BRACKET {
    ElementPtr l(new ListElement());
    ctx.stack_.back()->set("subnet6", l);
    ctx.stack_.push_back(l);
} subnet6_list_content RSQUARE_BRACKET {
    ctx.stack_.pop_back();
};

// This defines the ... in "subnet6": [ ... ]
// It can either be empty (no subnets defined), have one subnet
// or have multiple subnets separate by comma.
subnet6_list_content: { /* no subnets defined at all */ }
| subnet6
| subnet6_list_content COMMA subnet6
;

// This defines a single subnet, i.e. a single map with
// subnet6 array.
subnet6: LCURLY_BRACKET {
    ElementPtr m(new MapElement());
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
} subnet6_params {
    ctx.stack_.pop_back();
} RCURLY_BRACKET;

subnet6_params: subnet6_param
| subnet6_params COMMA subnet6_param;

subnet6_param: { /* empty list */ }
| option_data_list
| pools_list
| SUBNET COLON STRING {
    ElementPtr name(new StringElement($3)); ctx.stack_.back()->set("subnet", name);

 }
| INTERFACE COLON STRING {
    ElementPtr name(new StringElement($3)); ctx.stack_.back()->set("interface", name);
 }
;

// ---- option-data --------------------------

// This defines the "option-data": [ ... ] entry that may appear
// in several places, but most notably in subnet6 entries.
option_data_list: OPTION_DATA {
    ElementPtr l(new ListElement());
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
} COLON LSQUARE_BRACKET option_data_list_content RSQUARE_BRACKET {
    ctx.stack_.pop_back();
};

// This defines the content of option-data. It may be empty,
// have one entry or multiple entries separated by comma.
option_data_list_content: { }
| option_data_entry
| option_data_list_content COMMA option_data_entry;

// This defines th content of a single entry { ... } within
// option-data list.
option_data_entry: LCURLY_BRACKET {
    ElementPtr m(new MapElement());
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
} option_data_params RCURLY_BRACKET {
    ctx.stack_.pop_back();
};

// This defines parameters specified inside the map that itself
// is an entry in option-data list.
option_data_params: {}
| option_data_param
| option_data_params COMMA option_data_param;

option_data_param:
NAME COLON STRING {
    ElementPtr name(new StringElement($3)); ctx.stack_.back()->set("name", name);
}
| DATA COLON STRING {
    ElementPtr data(new StringElement($3)); ctx.stack_.back()->set("data", data);
}
| CODE COLON INTEGER {
    ElementPtr code(new IntElement($3)); ctx.stack_.back()->set("code", code);
};

// ---- pools ------------------------------------

// This defines the "pools": [ ... ] entry that may appear in subnet6.
pools_list: POOLS COLON {
    ElementPtr l(new ListElement());
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
} LSQUARE_BRACKET pools_list_content RSQUARE_BRACKET {
    ctx.stack_.pop_back();
};

// Pools may be empty, contain a single pool entry or multiple entries
// separate by commas.
pools_list_content: { }
| pool_entry
| pools_list_content COMMA pool_entry;

pool_entry: LCURLY_BRACKET {
    ElementPtr m(new MapElement());
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
} pool_params RCURLY_BRACKET {
    ctx.stack_.pop_back();
};

pool_params: pool_param
| pool_params COMMA pool_param;

pool_param: POOL COLON STRING {
    ElementPtr pool(new StringElement($3)); ctx.stack_.back()->set("pool", pool);
}
| option_data_list;

// --- end of pools definition -------------------------------

// --- logging entry -----------------------------------------

// This defines the top level "Logging" object. It parses
// the following "Logging": { ... }. The ... is defined
// by logging_params
logging_object: LOGGING COLON LCURLY_BRACKET {
    ElementPtr m(new MapElement());
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
} logging_params RCURLY_BRACKET {
    ctx.stack_.pop_back();
};

// This defines the list of allowed parameters that may appear
// in the top-level Logging object. It can either be a single
// parameter or several parameters separated by commas.
logging_params: logging_param
| logging_params COMMA logging_param;

// There's currently only one parameter defined, which is "loggers".
logging_param: loggers;

// "loggers", the only parameter currently defined in "Logging" object,
// is "Loggers": [ ... ].
loggers: LOGGERS COLON {
    ElementPtr l(new ListElement());
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
} LSQUARE_BRACKET loggers_entries RSQUARE_BRACKET {
    ctx.stack_.pop_back();
};

// These are the parameters allowed in loggers: either one logger
// entry or multiple entries separate by commas.
loggers_entries: logger_entry
| loggers_entries COMMA logger_entry;

// This defines a single entry defined in loggers in Logging.
logger_entry: LCURLY_BRACKET {
    ElementPtr l(new MapElement());
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
} logger_params RCURLY_BRACKET {
    ctx.stack_.pop_back();
};

logger_params: logger_param
| logger_params COMMA logger_param;

logger_param: logger_name
| output_options_list
| debuglevel
| severity
;

logger_name: NAME COLON STRING {
    ElementPtr name(new StringElement($3)); ctx.stack_.back()->set("name", name);
};

debuglevel: DEBUGLEVEL COLON INTEGER {
    ElementPtr dl(new IntElement($3)); ctx.stack_.back()->set("debuglevel", dl);
};
severity: SEVERITY COLON STRING {
    ElementPtr sev(new StringElement($3)); ctx.stack_.back()->set("severity", sev);
};

output_options_list: OUTPUT_OPTIONS COLON {
    ElementPtr l(new ListElement());
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
} LSQUARE_BRACKET output_options_list_content RSQUARE_BRACKET {
    ctx.stack_.pop_back();
};

output_options_list_content: output_entry
| output_options_list_content COMMA output_entry;

output_entry: LCURLY_BRACKET {
    ElementPtr m(new MapElement());
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
} output_params RCURLY_BRACKET {
    ctx.stack_.pop_back();
};

output_params: output_param
| output_params COMMA output_param;

output_param: OUTPUT COLON STRING {
    ElementPtr sev(new StringElement($3)); ctx.stack_.back()->set("output", sev);
};



%%

void
isc::dhcp::Dhcp6Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
