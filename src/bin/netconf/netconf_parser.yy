/* Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")

   This Source Code Form is subject to the terms of the Mozilla Public
   License, v. 2.0. If a copy of the MPL was not distributed with this
   file, You can obtain one at http://mozilla.org/MPL/2.0/. */

%skeleton "lalr1.cc" /* -*- C++ -*- */
%require "3.0.0"
%defines
%define parser_class_name {NetconfParser}
%define api.prefix {netconf_}
%define api.token.constructor
%define api.value.type variant
%define api.namespace {isc::netconf}
%define parse.assert
%code requires
{
#include <string>
#include <cc/data.h>
#include <boost/lexical_cast.hpp>
#include <netconf/parser_context_decl.h>

using namespace isc::netconf;
using namespace isc::data;
using namespace std;
}
// The parsing context.
%param { isc::netconf::ParserContext& ctx }
%locations
%define parse.trace
%define parse.error verbose
%code
{
#include <netconf/parser_context.h>
}


%define api.token.prefix {TOKEN_}
// Tokens in an order which makes sense and related to the intented use.
// Actual regexps for tokens are defined in netconf_lexer.ll.
%token
  END  0  "end of file"
  COMMA ","
  COLON ":"
  LSQUARE_BRACKET "["
  RSQUARE_BRACKET "]"
  LCURLY_BRACKET "{"
  RCURLY_BRACKET "}"
  NULL_TYPE "null"

  NETCONF "Netconf"

  USER_CONTEXT "user-context"
  COMMENT "comment"

  MANAGED_SERVERS "managed-servers"
  DHCP4_SERVER "dhcp4"
  DHCP6_SERVER "dhcp6"
  D2_SERVER "d2"
  CA_SERVER "ca"
  MODEL "model"
  CONTROL_SOCKET "control-socket"
  TYPE "type"
  UNIX "unix"
  HTTP "http"
  STDOUT "stdout"
  NAME "name"
  HOST "host"
  PORT "port"

  HOOKS_LIBRARIES "hooks-libraries"
  LIBRARY "library"
  PARAMETERS "parameters"

  LOGGING "Logging"
  LOGGERS "loggers"
  OUTPUT_OPTIONS "output_options"
  OUTPUT "output"
  DEBUGLEVEL "debuglevel"
  SEVERITY "severity"
  FLUSH "flush"
  MAXSIZE "maxsize"
  MAXVER "maxver"

  DHCP4 "Dhcp4"
  DHCP6 "Dhcp6"
  DHCPDDNS "DhcpDdns"
  CONTROL_AGENT "Control-agent"

  // Not real tokens, just a way to signal what the parser is expected to
  // parse. This define the starting point. It either can be full grammar
  // (START_NETCONF), part of the grammar related to control-netconf (START_SUB_NETCONF)
  // or can be any valid JSON (START_JSON)
  START_JSON
  START_NETCONF
  START_SUB_NETCONF
;

%token <std::string> STRING "constant string"
%token <int64_t> INTEGER "integer"
%token <double> FLOAT "floating point"
%token <bool> BOOLEAN "boolean"

%type <ElementPtr> value
%type <ElementPtr> map_value
%type <ElementPtr> socket_type_value

%printer { yyoutput << $$; } <*>;

%%

// The whole grammar starts with a map, because the config file
// consists of Control-Netconf, DhcpX, Logger and DhcpDdns entries in one big { }.
%start start;

// The starting token can be one of those listed below. Note these are
// "fake" tokens. They're produced by the lexer before any input text
// is parsed.
start: START_JSON      { ctx.ctx_ = ctx.NO_KEYWORDS; } json
     | START_NETCONF     { ctx.ctx_ = ctx.CONFIG; } netconf_syntax_map
     | START_SUB_NETCONF { ctx.ctx_ = ctx.NETCONF; } sub_netconf
     ;

// This rule defines a "shortcut". Instead of specifying the whole structure
// expected by full grammar, we can tell the parser to start from content of
// the Control-netconf. This is very useful for unit-testing, so we don't need
// to repeat the outer map and "Control-netconf" map. We can simply provide
// the contents of that map.
sub_netconf: LCURLY_BRACKET {
    // Parse the Control-netconf map
    ElementPtr m(new MapElement(ctx.loc2pos(@1)));
    ctx.stack_.push_back(m);
} global_params RCURLY_BRACKET {
    // parsing completed
};

// --- generic JSON parser -----------------------------------------------------

// json expression can be a value. What value means is defined below.
json: value {
    // Push back the JSON value on the stack
    ctx.stack_.push_back($1);
};

// Rules for value. This can be one of the primary types allowed in JSON.
value: INTEGER { $$ = ElementPtr(new IntElement($1, ctx.loc2pos(@1))); }
     | FLOAT { $$ = ElementPtr(new DoubleElement($1, ctx.loc2pos(@1))); }
     | BOOLEAN { $$ = ElementPtr(new BoolElement($1, ctx.loc2pos(@1))); }
     | STRING { $$ = ElementPtr(new StringElement($1, ctx.loc2pos(@1))); }
     | NULL_TYPE { $$ = ElementPtr(new NullElement(ctx.loc2pos(@1))); }
     | map { $$ = ctx.stack_.back(); ctx.stack_.pop_back(); }
     | list_generic { $$ = ctx.stack_.back(); ctx.stack_.pop_back(); }
     ;

// Rule for map. It will start with {, have some content and will end with }.
map: LCURLY_BRACKET {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(@1)));
    ctx.stack_.push_back(m);
} map_content RCURLY_BRACKET {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
};

map_value: map { $$ = ctx.stack_.back(); ctx.stack_.pop_back(); };

// Rule for map content. In some cases it is allowed to have an empty map,
// so we should say that explicitly. In most cases, though, there will
// be some actual content inside. That's defined by not_empty_map
map_content: %empty // empty map
           | not_empty_map
           ;

// Rule for content of the map. It can have one of two formats:
// 1) string: value
// 2) non_empty_map , string: value
// The first case covers a single entry, while the second case
// covers all longer lists recursively.
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
};

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

// --- generic JSON parser ends here -------------------------------------------

// --- syntax checking parser starts here --------------------------------------

// Unknown keyword in a map. This clever rule can be added to any map
// if you want to have a nice expression printed when unknown (mistyped?)
// parameter is found.
unknown_map_entry: STRING COLON {
    const std::string& where = ctx.contextName();
    const std::string& keyword = $1;
    error(@1,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
};

// This defines the top-level { } that holds Netconf, Dhcp6, Dhcp4,
// DhcpDdns, Control-agent or Logging objects.
netconf_syntax_map: LCURLY_BRACKET {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(@1)));
    ctx.stack_.push_back(m);
} global_objects RCURLY_BRACKET {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
};

// This represents top-level entries: Control-netconf, Logging, possibly others
global_objects: global_object
              | global_objects COMMA global_object
              ;

// This represents a single top level entry, e.g. Control-netconf, Dhcp6 or DhcpDdns.
global_object: netconf_object
             | logging_object
             | dhcp4_json_object
             | dhcp6_json_object
             | dhcpddns_json_object
             | control_agent_object
             | unknown_map_entry
             ;

// This define the Control-netconf object.
netconf_object: NETCONF {

    // Let's create a MapElement that will represent it, add it to the
    // top level map (that's already on the stack) and put the new map
    // on the stack as well, so child elements will be able to add
    // themselves to it.
    ElementPtr m(new MapElement(ctx.loc2pos(@1)));
    ctx.stack_.back()->set("Netconf", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.NETCONF);
} COLON LCURLY_BRACKET global_params RCURLY_BRACKET {
    // Ok, we're done with parsing control-netconf. Let's take the map
    // off the stack.
    ctx.stack_.pop_back();
    ctx.leave();
};

global_params: global_param
             | global_params COMMA global_param
             ;

// These are the parameters that are allowed in the top-level for
// Netconf.
global_param: managed_servers
            | hooks_libraries
            | user_context
            | comment
            | unknown_map_entry
            ;

user_context: USER_CONTEXT {
    ctx.enter(ctx.NO_KEYWORDS);
} COLON map_value {
    ElementPtr parent = ctx.stack_.back();
    ElementPtr user_context = $4;
    ConstElementPtr old = parent->get("user-context");

    // Handle already existing user context
    if (old) {
        // Check if it was a comment or a duplicate
        if ((old->size() != 1) || !old->contains("comment")) {
            std::stringstream msg;
            msg << "duplicate user-context entries (previous at "
                << old->getPosition().str() << ")";
            error(@1, msg.str());
        }
        // Merge the comment
        user_context->set("comment", old->get("comment"));
    }

    // Set the user context
    parent->set("user-context", user_context);
    ctx.leave();
};

comment: COMMENT {
    ctx.enter(ctx.NO_KEYWORDS);
} COLON STRING {
    ElementPtr parent = ctx.stack_.back();
    ElementPtr user_context(new MapElement(ctx.loc2pos(@1)));
    ElementPtr comment(new StringElement($4, ctx.loc2pos(@4)));
    user_context->set("comment", comment);

    // Handle already existing user context
    ConstElementPtr old = parent->get("user-context");
    if (old) {
        // Check for duplicate comment
        if (old->contains("comment")) {
            std::stringstream msg;
            msg << "duplicate user-context/comment entries (previous at "
                << old->getPosition().str() << ")";
            error(@1, msg.str());
        }
        // Merge the user context in the comment
        merge(user_context, old);
    }

    // Set the user context
    parent->set("user-context", user_context);
    ctx.leave();
};

// --- hooks-libraries ---------------------------------------------------------
hooks_libraries: HOOKS_LIBRARIES {
    ElementPtr l(new ListElement(ctx.loc2pos(@1)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
} COLON LSQUARE_BRACKET hooks_libraries_list RSQUARE_BRACKET {
    ctx.stack_.pop_back();
    ctx.leave();
};

hooks_libraries_list: %empty
                    | not_empty_hooks_libraries_list
                    ;

not_empty_hooks_libraries_list: hooks_library
    | not_empty_hooks_libraries_list COMMA hooks_library
    ;

hooks_library: LCURLY_BRACKET {
    ElementPtr m(new MapElement(ctx.loc2pos(@1)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
} hooks_params RCURLY_BRACKET {
    ctx.stack_.pop_back();
};

hooks_params: hooks_param
            | hooks_params COMMA hooks_param
            | unknown_map_entry
            ;

hooks_param: library
           | parameters
           ;

library: LIBRARY {
    ctx.enter(ctx.NO_KEYWORDS);
} COLON STRING {
    ElementPtr lib(new StringElement($4, ctx.loc2pos(@4)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
};

parameters: PARAMETERS {
    ctx.enter(ctx.NO_KEYWORDS);
} COLON value {
    ctx.stack_.back()->set("parameters", $4);
    ctx.leave();
};

// --- hooks-libraries end here ------------------------------------------------

// --- managed-servsers starts here ---------------------------------------------
managed_servers: MANAGED_SERVERS COLON LCURLY_BRACKET {
    ElementPtr m(new MapElement(ctx.loc2pos(@1)));
    ctx.stack_.back()->set("managed-servers", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.MANAGED_SERVERS);
} servers_entries RCURLY_BRACKET {
    ctx.stack_.pop_back();
    ctx.leave();
};

servers_entries: %empty
               | not_empty_servers_entries
               ;

not_empty_servers_entries: server_entry
                         | not_empty_servers_entries COMMA server_entry
                         ;


// We currently support four types of servers: DHCPv4, DHCPv6, D2 and CA
// (even though D2 socket support is not yet merged).
server_entry: dhcp4_server
            | dhcp6_server
            | d2_server
            | ca_server
            | unknown_map_entry
            ;

// That's an entry for dhcp4 server.
dhcp4_server: DHCP4_SERVER {
    ElementPtr m(new MapElement(ctx.loc2pos(@1)));
    ctx.stack_.back()->set("dhcp4", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER);
} COLON LCURLY_BRACKET managed_server_params RCURLY_BRACKET {
    ctx.stack_.pop_back();
    ctx.leave();
};

// That's an entry for dhcp6 server.
dhcp6_server: DHCP6_SERVER {
    ElementPtr m(new MapElement(ctx.loc2pos(@1)));
    ctx.stack_.back()->set("dhcp6", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER);
} COLON LCURLY_BRACKET managed_server_params RCURLY_BRACKET {
    ctx.stack_.pop_back();
    ctx.leave();
};

// That's an entry for d2 server.
d2_server: D2_SERVER {
    ElementPtr m(new MapElement(ctx.loc2pos(@1)));
    ctx.stack_.back()->set("d2", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER);
} COLON LCURLY_BRACKET managed_server_params RCURLY_BRACKET {
    ctx.stack_.pop_back();
    ctx.leave();
};

// That's an entry for ca server.
ca_server: CA_SERVER {
    ElementPtr m(new MapElement(ctx.loc2pos(@1)));
    ctx.stack_.back()->set("ca", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER);
} COLON LCURLY_BRACKET managed_server_params RCURLY_BRACKET {
    ctx.stack_.pop_back();
    ctx.leave();
};

// Server parameters consist of one or more parameters.
managed_server_params: managed_server_param
                     | managed_server_params COMMA managed_server_param
                     ;

// We currently support two server parameters: model and control-socket.
managed_server_param: model
                    | control_socket
                    | user_context
                    | comment
                    | unknown_map_entry
                    ;
                    
// YANG model
model: MODEL {
    ctx.enter(ctx.NO_KEYWORDS);
} COLON STRING {
    ElementPtr model(new StringElement($4, ctx.loc2pos(@4)));
    ctx.stack_.back()->set("model", model);
    ctx.leave();
};

// Control socket.
control_socket: CONTROL_SOCKET {
    ElementPtr m(new MapElement(ctx.loc2pos(@1)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
} COLON LCURLY_BRACKET control_socket_params RCURLY_BRACKET {
    ctx.stack_.pop_back();
    ctx.leave();
};

// control-socket parameters
control_socket_params: control_socket_param
                     | control_socket_params COMMA control_socket_param
                     ;

control_socket_param: socket_type
                    | name
                    | host
                    | port
                    | user_context
                    | comment
                    | unknown_map_entry
                    ;

socket_type: TYPE {
    ctx.enter(ctx.SOCKET_TYPE);
} COLON socket_type_value {
    ctx.stack_.back()->set("type", $4);
    ctx.leave();
};

// We currently allow unix, http and stdout control socket types.
socket_type_value : UNIX { $$ = ElementPtr(new StringElement("unix", ctx.loc2pos(@1))); }
                  | HTTP { $$ = ElementPtr(new StringElement("http", ctx.loc2pos(@1))); }
                  | STDOUT { $$ = ElementPtr(new StringElement("stdout", ctx.loc2pos(@1))); }
                  ;
// Unix name.
name: NAME {
    ctx.enter(ctx.NO_KEYWORDS);
} COLON STRING {
    ElementPtr name(new StringElement($4, ctx.loc2pos(@4)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
};

// HTTP host.
host: HOST {
    ctx.enter(ctx.NO_KEYWORDS);
} COLON STRING {
    ElementPtr host(new StringElement($4, ctx.loc2pos(@4)));
    ctx.stack_.back()->set("host", host);
    ctx.leave();
};

// HTTP PORT
port: PORT COLON INTEGER {
    ElementPtr port(new IntElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("port", port);
};

// --- managed-servers end here ------------------------------------------------

// JSON entries for other global objects (Dhcp4,Dhcp6 and DhcpDdns)
dhcp4_json_object: DHCP4 {
    ctx.enter(ctx.NO_KEYWORDS);
} COLON value {
    ctx.stack_.back()->set("Dhcp4", $4);
    ctx.leave();
};

dhcp6_json_object: DHCP6 {
    ctx.enter(ctx.NO_KEYWORDS);
} COLON value {
    ctx.stack_.back()->set("Dhcp6", $4);
    ctx.leave();
};

dhcpddns_json_object: DHCPDDNS {
    ctx.enter(ctx.NO_KEYWORDS);
} COLON value {
    ctx.stack_.back()->set("DhcpDdns", $4);
    ctx.leave();
};

control_agent_object: CONTROL_AGENT {
    ctx.enter(ctx.NO_KEYWORDS);
} COLON value {
    ctx.stack_.back()->set("Control-agent", $4);
    ctx.leave();
};


// --- Logging starts here -----------------------------------------------------

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
            | user_context
            | comment
            | unknown_map_entry
            ;

debuglevel: DEBUGLEVEL COLON INTEGER {
    ElementPtr dl(new IntElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("debuglevel", dl);
};

severity: SEVERITY {
    ctx.enter(ctx.NO_KEYWORDS);
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
} output_params_list RCURLY_BRACKET {
    ctx.stack_.pop_back();
};

output_params_list: output_params
             | output_params_list COMMA output_params
             ;

output_params: output
             | flush
             | maxsize
             | maxver
             ;

output: OUTPUT {
    ctx.enter(ctx.NO_KEYWORDS);
} COLON STRING {
    ElementPtr sev(new StringElement($4, ctx.loc2pos(@4)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
};

flush: FLUSH COLON BOOLEAN {
    ElementPtr flush(new BoolElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("flush", flush);
};

maxsize: MAXSIZE COLON INTEGER {
    ElementPtr maxsize(new IntElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("maxsize", maxsize);
};

maxver: MAXVER COLON INTEGER {
    ElementPtr maxver(new IntElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("maxver", maxver);
};

%%

void
isc::netconf::NetconfParser::error(const location_type& loc,
                               const std::string& what)
{
    ctx.error(loc, what);
}
