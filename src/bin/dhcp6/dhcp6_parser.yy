/* Copyright (C) 2016 Internet Systems Consortium, Inc. ("ISC")

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
// Actual regexps for tokens are defined in dhcp6_lexer.ll.
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
  HOSTS_DATABASE "hosts-database"
  TYPE "type"
  USER "user"
  PASSWORD "password"
  HOST "host"
  PERSIST "persist"
  LFC_INTERVAL "lfc-interval"
  READONLY "readonly"

  PREFERRED_LIFETIME "preferred-lifetime"
  VALID_LIFETIME "valid-lifetime"
  RENEW_TIMER "renew-timer"
  REBIND_TIMER "rebind-timer"
  DECLINE_PROBATION_PERIOD "decline-probation-period"
  SUBNET6 "subnet6"
  OPTION_DEF "option-def"
  OPTION_DATA "option-data"
  NAME "name"
  DATA "data"
  CODE "code"
  SPACE "space"
  CSV_FORMAT "csv-format"
  RECORD_TYPES "record-types"
  ENCAPSULATE "encapsulate"
  ARRAY "array"

  POOLS "pools"
  POOL "pool"
  PD_POOLS "pd-pools"
  PREFIX "prefix"
  PREFIX_LEN "prefix-len"
  EXCLUDED_PREFIX "excluded-prefix"
  EXCLUDED_PREFIX_LEN "excluded-prefix-len"
  DELEGATED_LEN "delegated-len"

  SUBNET "subnet"
  INTERFACE "interface"
  INTERFACE_ID "interface-id"
  ID "id"
  RAPID_COMMIT "rapid-commit"
  RESERVATION_MODE "reservation-mode"

  MAC_SOURCES "mac-sources"
  RELAY_SUPPLIED_OPTIONS "relay-supplied-options"
  HOST_RESERVATION_IDENTIFIERS "host-reservation-identifiers"

  CLIENT_CLASSES "client-classes"
  TEST "test"
  CLIENT_CLASS "client-class"

  RESERVATIONS "reservations"
  IP_ADDRESSES "ip-addresses"
  PREFIXES "prefixes"
  DUID "duid"
  HW_ADDRESS "hw-address"
  HOSTNAME "hostname"

  RELAY "relay"
  IP_ADDRESS "ip-address"

  HOOKS_LIBRARIES "hooks-libraries"
  LIBRARY "library"
  PARAMETERS "parameters"

  EXPIRED_LEASES_PROCESSING "expired-leases-processing"

  SERVER_ID "server-id"
  IDENTIFIER "identifier"
  HTYPE "htype"
  TIME "time"
  ENTERPRISE_ID "enterprise-id"

  DHCP4O6_PORT "dhcp4o6-port"

  CONTROL_SOCKET "control-socket"
  SOCKET_TYPE "socket-type"
  SOCKET_NAME "socket-name"

  DHCP_DDNS "dhcp-ddns"

 /// @todo: Implement proper parsing for those parameters in Dhcp6/dhcp-ddns/*.
 /// This should be part of the #5043 ticket. Listing the keywords here for
 /// completeness.

 // These are tokens defined in Dhcp6/dhcp-ddns/*
 // They're not
 //  ENABLE_UPDATES "enable-updates"
 //  SERVER_IP "server-ip"
 //  SENDER_IP "sender-ip"
 //  SENDER_PORT "sender-port"
 //  MAX_QUEUE_SIZE "max-queue-size"
 //  NCR_PROTOCOL "ncr-protocol"
 //  NCR_FORMAT "ncr-format"
 //  ALWAYS_INCLUDE_FQDN "always-include-fqdn"
 //  OVERRDIDE_NO_UPDATE "override-no-update"
 //  OVERRDIDE_CLIENT_UPDATE "override-client-update"
 //  REPLACE_CLIENT_NAME "replace-client-name"
 //  GENERATED_PREFIX "generated-prefix"
 //  QUALIFYING_SUFFIX "qualifying-suffix"

  LOGGING "Logging"
  LOGGERS "loggers"
  OUTPUT_OPTIONS "output_options"
  OUTPUT "output"
  DEBUGLEVEL "debuglevel"
  SEVERITY "severity"

  DHCP4 "Dhcp4"
  DHCPDDNS "DhcpDdns"

 // Not real tokens, just a way to signal what the parser is expected to
 // parse.
  TOPLEVEL_JSON
  TOPLEVEL_DHCP6
  SUB_DHCP6
  SUB_INTERFACES6
  SUB_SUBNET6
  SUB_POOL6
  SUB_PD_POOL
  SUB_RESERVATION
  SUB_OPTION_DEF
  SUB_OPTION_DATA
  SUB_HOOKS_LIBRARY
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
// We made the same for subparsers at the exception of the JSON value.
%start start;

start: TOPLEVEL_JSON { ctx.ctx_ = ctx.NO_KEYWORD; } sub_json
     | TOPLEVEL_DHCP6 { ctx.ctx_ = ctx.CONFIG; } syntax_map
     | SUB_DHCP6 { ctx.ctx_ = ctx.DHCP6; } sub_dhcp6
     | SUB_INTERFACES6 { ctx.ctx_ = ctx.INTERFACES_CONFIG; } sub_interfaces6
     | SUB_SUBNET6 { ctx.ctx_ = ctx.SUBNET6; } sub_subnet6
     | SUB_POOL6 { ctx.ctx_ = ctx.POOLS; } sub_pool6
     | SUB_PD_POOL { ctx.ctx_ = ctx.PD_POOLS; } sub_pd_pool
     | SUB_RESERVATION { ctx.ctx_ = ctx.RESERVATIONS; } sub_reservation
     | SUB_OPTION_DEF { ctx.ctx_ = ctx.OPTION_DEF; } sub_option_def
     | SUB_OPTION_DATA { ctx.ctx_ = ctx.OPTION_DATA; } sub_option_data
     | SUB_HOOKS_LIBRARY { ctx.ctx_ = ctx.HOOKS_LIBRARIES; } sub_hooks_library
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

// This one is used in syntax parser.
list2: LSQUARE_BRACKET {
    // List parsing about to start
} list_content RSQUARE_BRACKET {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
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
global_object: dhcp6_object
             | logging_object
             | dhcp4_json_object
             | dhcpddns_json_object
             | unknown_map_entry
             ;

dhcp6_object: DHCP6 {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(@1)));
    ctx.stack_.back()->set("Dhcp6", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP6);
} COLON LCURLY_BRACKET global_params RCURLY_BRACKET {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
    ctx.stack_.pop_back();
    ctx.leave();
};

// subparser: similar to the corresponding rule but without parent
// so the stack is empty at the rule entry.
sub_dhcp6: LCURLY_BRACKET {
    // Parse the Dhcp6 map
    ElementPtr m(new MapElement(ctx.loc2pos(@1)));
    ctx.stack_.push_back(m);
} global_params RCURLY_BRACKET {
    // parsing completed
};

global_params: global_param
             | global_params COMMA global_param
             ;

// These are the parameters that are allowed in the top-level for
// Dhcp6.
global_param: preferred_lifetime
            | valid_lifetime
            | renew_timer
            | rebind_timer
            | decline_probation_period
            | subnet6_list
            | interfaces_config
            | lease_database
            | hosts_database
            | mac_sources
            | relay_supplied_options
            | host_reservation_identifiers
            | client_classes
            | option_def_list
            | option_data_list
            | hooks_libraries
            | expired_leases_processing
            | server_id
            | dhcp4o6_port
            | control_socket
            | dhcp_ddns
            | unknown_map_entry
            ;

preferred_lifetime: PREFERRED_LIFETIME COLON INTEGER {
    ElementPtr prf(new IntElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("preferred-lifetime", prf);
};

valid_lifetime: VALID_LIFETIME COLON INTEGER {
    ElementPtr prf(new IntElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("valid-lifetime", prf);
};

renew_timer: RENEW_TIMER COLON INTEGER {
    ElementPtr prf(new IntElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("renew-timer", prf);
};

rebind_timer: REBIND_TIMER COLON INTEGER {
    ElementPtr prf(new IntElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("rebind-timer", prf);
};

decline_probation_period: DECLINE_PROBATION_PERIOD COLON INTEGER {
    ElementPtr dpp(new IntElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
};

interfaces_config: INTERFACES_CONFIG {
    ElementPtr i(new MapElement(ctx.loc2pos(@1)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
} COLON LCURLY_BRACKET interface_config_map RCURLY_BRACKET {
    ctx.stack_.pop_back();
    ctx.leave();
};

sub_interfaces6: LCURLY_BRACKET {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(@1)));
    ctx.stack_.push_back(m);
} interface_config_map RCURLY_BRACKET {
    // parsing completed
};

interface_config_map: INTERFACES {
    ElementPtr l(new ListElement(ctx.loc2pos(@1)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
} COLON list2 {
    ctx.stack_.pop_back();
    ctx.leave();
};

lease_database: LEASE_DATABASE {
    ElementPtr i(new MapElement(ctx.loc2pos(@1)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
} COLON LCURLY_BRACKET database_map_params RCURLY_BRACKET {
    ctx.stack_.pop_back();
    ctx.leave();
};

hosts_database: HOSTS_DATABASE {
    ElementPtr i(new MapElement(ctx.loc2pos(@1)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
} COLON LCURLY_BRACKET database_map_params RCURLY_BRACKET {
    ctx.stack_.pop_back();
    ctx.leave();
};

database_map_params: database_map_param
                   | database_map_params COMMA database_map_param
                   ;

database_map_param: type
                  | user
                  | password
                  | host
                  | name
                  | persist
                  | lfc_interval
                  | readonly
                  | unknown_map_entry
;

type: TYPE {
    ctx.enter(ctx.NO_KEYWORD);
} COLON STRING {
    ElementPtr prf(new StringElement($4, ctx.loc2pos(@4)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
};

user: USER {
    ctx.enter(ctx.NO_KEYWORD);
} COLON STRING {
    ElementPtr user(new StringElement($4, ctx.loc2pos(@4)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
};

password: PASSWORD {
    ctx.enter(ctx.NO_KEYWORD);
} COLON STRING {
    ElementPtr pwd(new StringElement($4, ctx.loc2pos(@4)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
};

host: HOST {
    ctx.enter(ctx.NO_KEYWORD);
} COLON STRING {
    ElementPtr h(new StringElement($4, ctx.loc2pos(@4)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
};

name: NAME {
    ctx.enter(ctx.NO_KEYWORD);
} COLON STRING {
    ElementPtr name(new StringElement($4, ctx.loc2pos(@4)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
};

persist: PERSIST COLON BOOLEAN {
    ElementPtr n(new BoolElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("persist", n);
};

lfc_interval: LFC_INTERVAL COLON INTEGER {
    ElementPtr n(new IntElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("lfc-interval", n);
};

readonly: READONLY COLON BOOLEAN {
    ElementPtr n(new BoolElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("readonly", n);
};

mac_sources: MAC_SOURCES {
    ElementPtr l(new ListElement(ctx.loc2pos(@1)));
    ctx.stack_.back()->set("mac-sources", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.MAC_SOURCES);
} COLON LSQUARE_BRACKET mac_sources_list RSQUARE_BRACKET {
    ctx.stack_.pop_back();
    ctx.leave();
};

mac_sources_list: mac_sources_value
                | mac_sources_list COMMA mac_sources_value
;

mac_sources_value: duid_id
                 | string_id
                 ;

duid_id : DUID {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(@1)));
    ctx.stack_.back()->add(duid);
};

string_id : STRING {
    ElementPtr duid(new StringElement($1, ctx.loc2pos(@1)));
    ctx.stack_.back()->add(duid);
};

host_reservation_identifiers: HOST_RESERVATION_IDENTIFIERS {
    ElementPtr l(new ListElement(ctx.loc2pos(@1)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
} COLON LSQUARE_BRACKET host_reservation_identifiers_list RSQUARE_BRACKET {
    ctx.stack_.pop_back();
    ctx.leave();
};

host_reservation_identifiers_list: host_reservation_identifier
    | host_reservation_identifiers_list COMMA host_reservation_identifier
    ;

host_reservation_identifier: duid_id
                           | hw_address_id
                           ;

hw_address_id : HW_ADDRESS {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(@1)));
    ctx.stack_.back()->add(hwaddr);
};

relay_supplied_options: RELAY_SUPPLIED_OPTIONS {
    ElementPtr l(new ListElement(ctx.loc2pos(@1)));
    ctx.stack_.back()->set("relay-supplied-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
} COLON list2 {
    ctx.stack_.pop_back();
    ctx.leave();
};

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

sub_hooks_library: LCURLY_BRACKET {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(@1)));
    ctx.stack_.push_back(m);
} hooks_params RCURLY_BRACKET {
    // parsing completed
};

hooks_params: hooks_param
            | hooks_params COMMA hooks_param
            | unknown_map_entry
            ;

hooks_param: library
           | parameters
           ;

library: LIBRARY {
    ctx.enter(ctx.NO_KEYWORD);
} COLON STRING {
    ElementPtr lib(new StringElement($4, ctx.loc2pos(@4)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
};

parameters: PARAMETERS {
    ctx.enter(ctx.NO_KEYWORD);
} COLON value {
    ctx.stack_.back()->set("parameters", $4);
    ctx.leave();
};

// --- expired-leases-processing ------------------------
expired_leases_processing: EXPIRED_LEASES_PROCESSING {
    ElementPtr m(new MapElement(ctx.loc2pos(@1)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.NO_KEYWORD);
} COLON LCURLY_BRACKET expired_leases_params RCURLY_BRACKET {
    ctx.stack_.pop_back();
    ctx.leave();
};

expired_leases_params: expired_leases_param
                     | expired_leases_params COMMA expired_leases_param
                     ;

// This is a bit of a simplification. But it can also serve as an example.
// Instead of explicitly listing all allowed expired leases parameters, we
// simply say that all of them as integers.
expired_leases_param: STRING COLON INTEGER {
    ElementPtr value(new IntElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set($1, value);
};

// --- subnet6 ------------------------------------------
// This defines subnet6 as a list of maps.
// "subnet6": [ ... ]
subnet6_list: SUBNET6 {
    ElementPtr l(new ListElement(ctx.loc2pos(@1)));
    ctx.stack_.back()->set("subnet6", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET6);
} COLON LSQUARE_BRACKET subnet6_list_content RSQUARE_BRACKET {
    ctx.stack_.pop_back();
    ctx.leave();
};

// This defines the ... in "subnet6": [ ... ]
// It can either be empty (no subnets defined), have one subnet
// or have multiple subnets separate by comma.
subnet6_list_content: %empty
                    | not_empty_subnet6_list
                    ;

not_empty_subnet6_list: subnet6
                      | not_empty_subnet6_list COMMA subnet6
                      ;

// --- Subnet definitions -------------------------------

// This defines a single subnet, i.e. a single map with
// subnet6 array.
subnet6: LCURLY_BRACKET {
    ElementPtr m(new MapElement(ctx.loc2pos(@1)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
} subnet6_params RCURLY_BRACKET {
    // Once we reached this place, the subnet parsing is now complete.
    // If we want to, we can implement default values here.
    // In particular we can do things like this:
    // if (!ctx.stack_.back()->get("interface")) {
    //     ctx.stack_.back()->set("interface", StringElement("loopback"));
    // }
    //
    // We can also stack up one level (Dhcp6) and copy over whatever
    // global parameters we want to:
    // if (!ctx.stack_.back()->get("renew-timer")) {
    //     ElementPtr renew = ctx_stack_[...].get("renew-timer");
    //     if (renew) {
    //         ctx.stack_.back()->set("renew-timer", renew);
    //     }
    // }
    ctx.stack_.pop_back();
};

sub_subnet6: LCURLY_BRACKET {
    // Parse the subnet6 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(@1)));
    ctx.stack_.push_back(m);
} subnet6_params RCURLY_BRACKET {
    // parsing completed
};

// This defines that subnet can have one or more parameters.
subnet6_params: subnet6_param
              | subnet6_params COMMA subnet6_param
              ;

// This defines a list of allowed parameters for each subnet.
subnet6_param: preferred_lifetime
             | valid_lifetime
             | renew_timer
             | rebind_timer
             | option_data_list
             | pools_list
             | pd_pools_list
             | subnet
             | interface
             | interface_id
             | id
             | rapid_commit
             | client_class
             | reservations
             | reservation_mode
             | relay
             | unknown_map_entry
             ;

subnet: SUBNET {
    ctx.enter(ctx.NO_KEYWORD);
} COLON STRING {
    ElementPtr subnet(new StringElement($4, ctx.loc2pos(@4)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
};

interface: INTERFACE {
    ctx.enter(ctx.NO_KEYWORD);
} COLON STRING {
    ElementPtr iface(new StringElement($4, ctx.loc2pos(@4)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
};

interface_id: INTERFACE_ID {
    ctx.enter(ctx.NO_KEYWORD);
} COLON STRING {
    ElementPtr iface(new StringElement($4, ctx.loc2pos(@4)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
};

client_class: CLIENT_CLASS {
    ctx.enter(ctx.CLIENT_CLASS);
} COLON STRING {
    ElementPtr cls(new StringElement($4, ctx.loc2pos(@4)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
};

reservation_mode: RESERVATION_MODE {
    ctx.enter(ctx.NO_KEYWORD);
} COLON STRING {
    ElementPtr rm(new StringElement($4, ctx.loc2pos(@4)));
    ctx.stack_.back()->set("reservation-mode", rm);
    ctx.leave();
};

id: ID COLON INTEGER {
    ElementPtr id(new IntElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("id", id);
};

rapid_commit: RAPID_COMMIT COLON BOOLEAN {
    ElementPtr rc(new BoolElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("rapid-commit", rc);
};

// ---- option-def --------------------------

// This defines the "option-def": [ ... ] entry that may appear
// at a global option.
option_def_list: OPTION_DEF {
    ElementPtr l(new ListElement(ctx.loc2pos(@1)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
} COLON LSQUARE_BRACKET option_def_list_content RSQUARE_BRACKET {
    ctx.stack_.pop_back();
    ctx.leave();
};

// This defines the content of option-def. It may be empty,
// have one entry or multiple entries separated by comma.
option_def_list_content: %empty
                       | not_empty_option_def_list
                       ;

not_empty_option_def_list: option_def_entry
                         | not_empty_option_def_list COMMA option_def_entry
                          ;

// This defines the content of a single entry { ... } within
// option-def list.
option_def_entry: LCURLY_BRACKET {
    ElementPtr m(new MapElement(ctx.loc2pos(@1)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
} option_def_params RCURLY_BRACKET {
    ctx.stack_.pop_back();
};

// This defines the top level scope when the parser is told to parse a single
// option definition. It's almost exactly the same as option_def_entry, except
// that it does leave its value on stack.
sub_option_def: LCURLY_BRACKET {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(@1)));
    ctx.stack_.push_back(m);
} option_def_params RCURLY_BRACKET {
    // parsing completed
};

// This defines parameters specified inside the map that itself
// is an entry in option-def list.
option_def_params: %empty
                 | not_empty_option_def_params
                 ;

not_empty_option_def_params: option_def_param
                           | not_empty_option_def_params COMMA option_def_param
                           ;

option_def_param: option_def_name
                | option_def_code
                | option_def_type
                | option_def_record_types
                | option_def_space
                | option_def_encapsulate
                | option_def_array
                | unknown_map_entry
                ;

option_def_name: name;

code: CODE COLON INTEGER {
    ElementPtr code(new IntElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("code", code);
};

option_def_code: code;

option_def_type: type;

option_def_record_types: RECORD_TYPES {
    ctx.enter(ctx.NO_KEYWORD);
} COLON STRING {
    ElementPtr rtypes(new StringElement($4, ctx.loc2pos(@4)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
};

space: SPACE {
    ctx.enter(ctx.NO_KEYWORD);
} COLON STRING {
    ElementPtr space(new StringElement($4, ctx.loc2pos(@4)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
};

option_def_space: space;

option_def_encapsulate: ENCAPSULATE {
    ctx.enter(ctx.NO_KEYWORD);
} COLON STRING {
    ElementPtr encap(new StringElement($4, ctx.loc2pos(@4)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
};

option_def_array: ARRAY COLON BOOLEAN {
    ElementPtr array(new BoolElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("array", array);
};

// ---- option-data --------------------------

// This defines the "option-data": [ ... ] entry that may appear
// in several places, but most notably in subnet6 entries.
option_data_list: OPTION_DATA {
    ElementPtr l(new ListElement(ctx.loc2pos(@1)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
} COLON LSQUARE_BRACKET option_data_list_content RSQUARE_BRACKET {
    ctx.stack_.pop_back();
    ctx.leave();
};

// This defines the content of option-data. It may be empty,
// have one entry or multiple entries separated by comma.
option_data_list_content: %empty
                        | not_empty_option_data_list
                        ;

// This defines the content of option-data list. It can either
// be a single value or multiple entries separated by comma.
not_empty_option_data_list: option_data_entry
                          | not_empty_option_data_list COMMA option_data_entry
                          ;

// This defines th content of a single entry { ... } within
// option-data list.
option_data_entry: LCURLY_BRACKET {
    ElementPtr m(new MapElement(ctx.loc2pos(@1)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
} option_data_params RCURLY_BRACKET {
    ctx.stack_.pop_back();
};

// This defines the top level scope when the parser is told to parse a single
// option data. It's almost exactly the same as option_data_entry, except
// that it does leave its value on stack.
sub_option_data: LCURLY_BRACKET {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(@1)));
    ctx.stack_.push_back(m);
} option_data_params RCURLY_BRACKET {
    // parsing completed
};

// This defines parameters specified inside the map that itself
// is an entry in option-data list. It can either be empty
// or have a non-empty list of parameters.
option_data_params: %empty
                  | not_empty_option_data_params
                  ;

// Those parameters can either be a single parameter or
// a list of parameters separated by comma.
not_empty_option_data_params: option_data_param
    | not_empty_option_data_params COMMA option_data_param
    ;

// Each single option-data parameter can be one of the following
// expressions.
option_data_param: option_data_name
                 | option_data_data
                 | option_data_code
                 | option_data_space
                 | option_data_csv_format
                 | unknown_map_entry
                 ;

option_data_name: name;

option_data_data: DATA {
    ctx.enter(ctx.NO_KEYWORD);
} COLON STRING {
    ElementPtr data(new StringElement($4, ctx.loc2pos(@4)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
};

option_data_code: code;

option_data_space: space;

option_data_csv_format: CSV_FORMAT COLON BOOLEAN {
    ElementPtr space(new BoolElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("csv-format", space);
};

// ---- pools ------------------------------------

// This defines the "pools": [ ... ] entry that may appear in subnet6.
pools_list: POOLS {
    ElementPtr l(new ListElement(ctx.loc2pos(@1)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
} COLON LSQUARE_BRACKET pools_list_content RSQUARE_BRACKET {
    ctx.stack_.pop_back();
    ctx.leave();
};

// Pools may be empty, contain a single pool entry or multiple entries
// separate by commas.
pools_list_content: %empty
                  | not_empty_pools_list
                  ;

not_empty_pools_list: pool_list_entry
                    | not_empty_pools_list COMMA pool_list_entry
                    ;

pool_list_entry: LCURLY_BRACKET {
    ElementPtr m(new MapElement(ctx.loc2pos(@1)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
} pool_params RCURLY_BRACKET {
    ctx.stack_.pop_back();
};

sub_pool6: LCURLY_BRACKET {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(@1)));
    ctx.stack_.push_back(m);
} pool_params RCURLY_BRACKET {
    // parsing completed
};

pool_params: pool_param
           | pool_params COMMA pool_param
           ;

pool_param: pool_entry
          | option_data_list
          | unknown_map_entry
          ;

pool_entry: POOL {
    ctx.enter(ctx.NO_KEYWORD);
} COLON STRING {
    ElementPtr pool(new StringElement($4, ctx.loc2pos(@4)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
};

// --- end of pools definition -------------------------------

// --- pd-pools ----------------------------------------------
pd_pools_list: PD_POOLS {
    ElementPtr l(new ListElement(ctx.loc2pos(@1)));
    ctx.stack_.back()->set("pd-pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.PD_POOLS);
} COLON LSQUARE_BRACKET pd_pools_list_content RSQUARE_BRACKET {
    ctx.stack_.pop_back();
    ctx.leave();
};

// Pools may be empty, contain a single pool entry or multiple entries
// separate by commas.
pd_pools_list_content: %empty
                     | not_empty_pd_pools_list
                     ;

not_empty_pd_pools_list: pd_pool_entry
                       | not_empty_pd_pools_list COMMA pd_pool_entry
                       ;

pd_pool_entry: LCURLY_BRACKET {
    ElementPtr m(new MapElement(ctx.loc2pos(@1)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
} pd_pool_params RCURLY_BRACKET {
    ctx.stack_.pop_back();
};

sub_pd_pool: LCURLY_BRACKET {
    // Parse the pd-pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(@1)));
    ctx.stack_.push_back(m);
} pd_pool_params RCURLY_BRACKET {
    // parsing completed
};

pd_pool_params: pd_pool_param
              | pd_pool_params COMMA pd_pool_param
              ;

pd_pool_param: pd_prefix
             | pd_prefix_len
             | pd_delegated_len
             | option_data_list
             | excluded_prefix
             | excluded_prefix_len
             | unknown_map_entry
             ;

pd_prefix: PREFIX {
    ctx.enter(ctx.NO_KEYWORD);
} COLON STRING {
    ElementPtr prf(new StringElement($4, ctx.loc2pos(@4)));
    ctx.stack_.back()->set("prefix", prf);
    ctx.leave();
};

pd_prefix_len: PREFIX_LEN COLON INTEGER {
    ElementPtr prf(new IntElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("prefix-len", prf);
};

excluded_prefix: EXCLUDED_PREFIX {
    ctx.enter(ctx.NO_KEYWORD);
} COLON STRING {
    ElementPtr prf(new StringElement($4, ctx.loc2pos(@4)));
    ctx.stack_.back()->set("excluded-prefix", prf);
    ctx.leave();
};

excluded_prefix_len: EXCLUDED_PREFIX_LEN COLON INTEGER {
    ElementPtr prf(new IntElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("excluded-prefix-len", prf);
};

pd_delegated_len: DELEGATED_LEN COLON INTEGER {
    ElementPtr deleg(new IntElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("delegated-len", deleg);
};

// --- end of pd-pools ---------------------------------------

// --- reservations ------------------------------------------
reservations: RESERVATIONS {
    ElementPtr l(new ListElement(ctx.loc2pos(@1)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
} COLON LSQUARE_BRACKET reservations_list RSQUARE_BRACKET {
    ctx.stack_.pop_back();
    ctx.leave();
};

reservations_list: %empty
                 | not_empty_reservations_list
                 ;

not_empty_reservations_list: reservation
                           | not_empty_reservations_list COMMA reservation
                           ;

reservation: LCURLY_BRACKET {
    ElementPtr m(new MapElement(ctx.loc2pos(@1)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
} reservation_params RCURLY_BRACKET {
    ctx.stack_.pop_back();
};

sub_reservation: LCURLY_BRACKET {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(@1)));
    ctx.stack_.push_back(m);
} reservation_params RCURLY_BRACKET {
    // parsing completed
};

reservation_params: %empty
                  | not_empty_reservation_params
                  ;

not_empty_reservation_params: reservation_param
    | not_empty_reservation_params COMMA reservation_param
    ;

// @todo probably need to add mac-address as well here
reservation_param: duid
                 | reservation_client_classes
                 | ip_addresses
                 | prefixes
                 | hw_address
                 | hostname
                 | option_data_list
                 | unknown_map_entry
                 ;

ip_addresses: IP_ADDRESSES {
    ElementPtr l(new ListElement(ctx.loc2pos(@1)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
} COLON list2 {
    ctx.stack_.pop_back();
    ctx.leave();
};

prefixes: PREFIXES  {
    ElementPtr l(new ListElement(ctx.loc2pos(@1)));
    ctx.stack_.back()->set("prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
} COLON list2 {
    ctx.stack_.pop_back();
    ctx.leave();
};

duid: DUID {
    ctx.enter(ctx.NO_KEYWORD);
} COLON STRING {
    ElementPtr d(new StringElement($4, ctx.loc2pos(@4)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
};

hw_address: HW_ADDRESS {
    ctx.enter(ctx.NO_KEYWORD);
} COLON STRING {
    ElementPtr hw(new StringElement($4, ctx.loc2pos(@4)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
};

hostname: HOSTNAME {
    ctx.enter(ctx.NO_KEYWORD);
} COLON STRING {
    ElementPtr host(new StringElement($4, ctx.loc2pos(@4)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
};

reservation_client_classes: CLIENT_CLASSES {
    ElementPtr c(new ListElement(ctx.loc2pos(@1)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
} COLON list2 {
    ctx.stack_.pop_back();
    ctx.leave();
};

// --- end of reservations definitions -----------------------

// --- relay -------------------------------------------------
relay: RELAY {
    ElementPtr m(new MapElement(ctx.loc2pos(@1)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
} COLON LCURLY_BRACKET relay_map RCURLY_BRACKET {
    ctx.stack_.pop_back();
    ctx.leave();
};

relay_map: IP_ADDRESS {
    ctx.enter(ctx.NO_KEYWORD);
} COLON STRING {
    ElementPtr ip(new StringElement($4, ctx.loc2pos(@4)));
    ctx.stack_.back()->set("ip-address", ip);
    ctx.leave();
};

// --- end of relay definitions ------------------------------

// --- client classes ----------------------------------------
client_classes: CLIENT_CLASSES {
    ElementPtr l(new ListElement(ctx.loc2pos(@1)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
} COLON LSQUARE_BRACKET client_classes_list RSQUARE_BRACKET {
    ctx.stack_.pop_back();
    ctx.leave();
};

client_classes_list: client_class
                   | client_classes_list COMMA client_class
                   ;

client_class: LCURLY_BRACKET {
    ElementPtr m(new MapElement(ctx.loc2pos(@1)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
} client_class_params RCURLY_BRACKET {
    ctx.stack_.pop_back();
};

client_class_params: %empty
                   | not_empty_client_class_params
                   ;

not_empty_client_class_params: client_class_param
    | not_empty_client_class_params COMMA client_class_param
    ;

client_class_param: client_class_name
                  | client_class_test
                  | option_data_list
                  | unknown_map_entry
                  ;

client_class_name: name;

client_class_test: TEST {
    ctx.enter(ctx.NO_KEYWORD);
} COLON STRING {
    ElementPtr test(new StringElement($4, ctx.loc2pos(@4)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
};

// --- end of client classes ---------------------------------

// --- server-id ---------------------------------------------
server_id: SERVER_ID {
    ElementPtr m(new MapElement(ctx.loc2pos(@1)));
    ctx.stack_.back()->set("server-id", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER_ID);
} COLON LCURLY_BRACKET server_id_params RCURLY_BRACKET {
    ctx.stack_.pop_back();
    ctx.leave();
};

server_id_params: server_id_param
                | server_id_params COMMA server_id_param
                ;

server_id_param: type
               | identifier
               | time
               | htype
               | enterprise_id
               | persist
               | unknown_map_entry
               ;

htype: HTYPE COLON INTEGER {
    ElementPtr htype(new IntElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("htype", htype);
};

identifier: IDENTIFIER {
    ctx.enter(ctx.NO_KEYWORD);
} COLON STRING {
    ElementPtr id(new StringElement($4, ctx.loc2pos(@4)));
    ctx.stack_.back()->set("identifier", id);
    ctx.leave();
};

time: TIME COLON INTEGER {
    ElementPtr time(new IntElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("time", time);
};

enterprise_id: ENTERPRISE_ID COLON INTEGER {
    ElementPtr time(new IntElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("enterprise-id", time);
};

// --- end of server-id --------------------------------------

dhcp4o6_port: DHCP4O6_PORT COLON INTEGER {
    ElementPtr time(new IntElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
};

// --- control socket ----------------------------------------

control_socket: CONTROL_SOCKET {
    ElementPtr m(new MapElement(ctx.loc2pos(@1)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
} COLON LCURLY_BRACKET control_socket_params RCURLY_BRACKET {
    ctx.stack_.pop_back();
    ctx.leave();
};

control_socket_params: control_socket_param
                     | control_socket_params COMMA control_socket_param
                     ;

control_socket_param: socket_type
                    | socket_name
                    ;

socket_type: SOCKET_TYPE {
    ctx.enter(ctx.NO_KEYWORD);
} COLON STRING {
    ElementPtr stype(new StringElement($4, ctx.loc2pos(@4)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
};

socket_name: SOCKET_NAME {
    ctx.enter(ctx.NO_KEYWORD);
} COLON STRING {
    ElementPtr name(new StringElement($4, ctx.loc2pos(@4)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
};

// --- dhcp ddns ---------------------------------------------

dhcp_ddns: DHCP_DDNS {
    ElementPtr m(new MapElement(ctx.loc2pos(@1)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.NO_KEYWORD);
} COLON LCURLY_BRACKET not_empty_map RCURLY_BRACKET {
    ctx.stack_.pop_back();
    ctx.leave();
};

// JSON entries for Dhcp4 and DhcpDdns

dhcp4_json_object: DHCP4 {
    ctx.enter(ctx.NO_KEYWORD);
} COLON value {
    ctx.stack_.back()->set("Dhcp4", $4);
    ctx.leave();
};

dhcpddns_json_object: DHCPDDNS {
    ctx.enter(ctx.NO_KEYWORD);
} COLON value {
    ctx.stack_.back()->set("DhcpDdns", $4);
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
isc::dhcp::Dhcp6Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
