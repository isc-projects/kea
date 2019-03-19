/* Copyright (C) 2016-2019 Internet Systems Consortium, Inc. ("ISC")

   This Source Code Form is subject to the terms of the Mozilla Public
   License, v. 2.0. If a copy of the MPL was not distributed with this
   file, You can obtain one at http://mozilla.org/MPL/2.0/. */

%skeleton "lalr1.cc" /* -*- C++ -*- */
%require "3.0.0"
%defines
%define parser_class_name {Dhcp4Parser}
%define api.prefix {parser4_}
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
#include <dhcp4/parser_context_decl.h>

using namespace isc::dhcp;
using namespace isc::data;
using namespace std;
}
// The parsing context.
%param { isc::dhcp::Parser4Context& ctx }
%locations
%define parse.trace
%define parse.error verbose
%code
{
#include <dhcp4/parser_context.h>
}


%define api.token.prefix {TOKEN_}
// Tokens in an order which makes sense and related to the intented use.
// Actual regexps for tokens are defined in dhcp4_lexer.ll.
%token
  END  0  "end of file"
  COMMA ","
  COLON ":"
  LSQUARE_BRACKET "["
  RSQUARE_BRACKET "]"
  LCURLY_BRACKET "{"
  RCURLY_BRACKET "}"
  NULL_TYPE "null"

  DHCP4 "Dhcp4"

  CONFIG_CONTROL "config-control"
  CONFIG_DATABASES "config-databases"
  CONFIG_FETCH_WAIT_TIME "config-fetch-wait-time"

  INTERFACES_CONFIG "interfaces-config"
  INTERFACES "interfaces"
  DHCP_SOCKET_TYPE "dhcp-socket-type"
  RAW "raw"
  UDP "udp"
  OUTBOUND_INTERFACE "outbound-interface"
  SAME_AS_INBOUND "same-as-inbound"
  USE_ROUTING "use-routing"
  RE_DETECT "re-detect"

  SANITY_CHECKS "sanity-checks"
  LEASE_CHECKS "lease-checks"

  ECHO_CLIENT_ID "echo-client-id"
  MATCH_CLIENT_ID "match-client-id"
  AUTHORITATIVE "authoritative"
  NEXT_SERVER "next-server"
  SERVER_HOSTNAME "server-hostname"
  BOOT_FILE_NAME "boot-file-name"

  LEASE_DATABASE "lease-database"
  HOSTS_DATABASE "hosts-database"
  HOSTS_DATABASES "hosts-databases"
  TYPE "type"
  MEMFILE "memfile"
  MYSQL "mysql"
  POSTGRESQL "postgresql"
  CQL "cql"
  USER "user"
  PASSWORD "password"
  HOST "host"
  PORT "port"
  PERSIST "persist"
  LFC_INTERVAL "lfc-interval"
  READONLY "readonly"
  CONNECT_TIMEOUT "connect-timeout"
  CONTACT_POINTS "contact-points"
  KEYSPACE "keyspace"
  CONSISTENCY "consistency"
  SERIAL_CONSISTENCY "serial-consistency"
  MAX_RECONNECT_TRIES "max-reconnect-tries"
  RECONNECT_WAIT_TIME "reconnect-wait-time"
  REQUEST_TIMEOUT "request-timeout"
  TCP_KEEPALIVE "tcp-keepalive"
  TCP_NODELAY "tcp-nodelay"

  VALID_LIFETIME "valid-lifetime"
  RENEW_TIMER "renew-timer"
  REBIND_TIMER "rebind-timer"
  CALCULATE_TEE_TIMES "calculate-tee-times"
  T1_PERCENT "t1-percent"
  T2_PERCENT "t2-percent"
  DECLINE_PROBATION_PERIOD "decline-probation-period"
  SERVER_TAG "server-tag"
  SUBNET4 "subnet4"
  SUBNET_4O6_INTERFACE "4o6-interface"
  SUBNET_4O6_INTERFACE_ID "4o6-interface-id"
  SUBNET_4O6_SUBNET "4o6-subnet"
  OPTION_DEF "option-def"
  OPTION_DATA "option-data"
  NAME "name"
  DATA "data"
  CODE "code"
  SPACE "space"
  CSV_FORMAT "csv-format"
  ALWAYS_SEND "always-send"
  RECORD_TYPES "record-types"
  ENCAPSULATE "encapsulate"
  ARRAY "array"

  SHARED_NETWORKS "shared-networks"

  POOLS "pools"
  POOL "pool"
  USER_CONTEXT "user-context"
  COMMENT "comment"

  SUBNET "subnet"
  INTERFACE "interface"
  ID "id"
  RESERVATION_MODE "reservation-mode"
  DISABLED "disabled"
  OUT_OF_POOL "out-of-pool"
  GLOBAL "global"
  ALL "all"

  HOST_RESERVATION_IDENTIFIERS "host-reservation-identifiers"

  CLIENT_CLASSES "client-classes"
  REQUIRE_CLIENT_CLASSES "require-client-classes"
  TEST "test"
  ONLY_IF_REQUIRED "only-if-required"
  CLIENT_CLASS "client-class"

  RESERVATIONS "reservations"
  DUID "duid"
  HW_ADDRESS "hw-address"
  CIRCUIT_ID "circuit-id"
  CLIENT_ID "client-id"
  HOSTNAME "hostname"
  FLEX_ID "flex-id"

  RELAY "relay"
  IP_ADDRESS "ip-address"
  IP_ADDRESSES "ip-addresses"

  HOOKS_LIBRARIES "hooks-libraries"
  LIBRARY "library"
  PARAMETERS "parameters"

  EXPIRED_LEASES_PROCESSING "expired-leases-processing"
  RECLAIM_TIMER_WAIT_TIME "reclaim-timer-wait-time"
  FLUSH_RECLAIMED_TIMER_WAIT_TIME "flush-reclaimed-timer-wait-time"
  HOLD_RECLAIMED_TIME "hold-reclaimed-time"
  MAX_RECLAIM_LEASES "max-reclaim-leases"
  MAX_RECLAIM_TIME "max-reclaim-time"
  UNWARNED_RECLAIM_CYCLES "unwarned-reclaim-cycles"

  DHCP4O6_PORT "dhcp4o6-port"

  CONTROL_SOCKET "control-socket"
  SOCKET_TYPE "socket-type"
  SOCKET_NAME "socket-name"

  DHCP_QUEUE_CONTROL "dhcp-queue-control"

  DHCP_DDNS "dhcp-ddns"
  ENABLE_UPDATES "enable-updates"
  QUALIFYING_SUFFIX "qualifying-suffix"
  SERVER_IP "server-ip"
  SERVER_PORT "server-port"
  SENDER_IP "sender-ip"
  SENDER_PORT "sender-port"
  MAX_QUEUE_SIZE "max-queue-size"
  NCR_PROTOCOL "ncr-protocol"
  NCR_FORMAT "ncr-format"
  OVERRIDE_NO_UPDATE "override-no-update"
  OVERRIDE_CLIENT_UPDATE "override-client-update"
  REPLACE_CLIENT_NAME "replace-client-name"
  GENERATED_PREFIX "generated-prefix"
  TCP "tcp"
  JSON "JSON"
  WHEN_PRESENT "when-present"
  NEVER "never"
  ALWAYS "always"
  WHEN_NOT_PRESENT "when-not-present"
  HOSTNAME_CHAR_SET "hostname-char-set"
  HOSTNAME_CHAR_REPLACEMENT "hostname-char-replacement"

  LOGGING "Logging"
  LOGGERS "loggers"
  OUTPUT_OPTIONS "output_options"
  OUTPUT "output"
  DEBUGLEVEL "debuglevel"
  SEVERITY "severity"
  FLUSH "flush"
  MAXSIZE "maxsize"
  MAXVER "maxver"

  DHCP6 "Dhcp6"
  DHCPDDNS "DhcpDdns"
  CONTROL_AGENT "Control-agent"

 // Not real tokens, just a way to signal what the parser is expected to
 // parse.
  TOPLEVEL_JSON
  TOPLEVEL_DHCP4
  SUB_DHCP4
  SUB_INTERFACES4
  SUB_SUBNET4
  SUB_POOL4
  SUB_RESERVATION
  SUB_OPTION_DEFS
  SUB_OPTION_DEF
  SUB_OPTION_DATA
  SUB_HOOKS_LIBRARY
  SUB_DHCP_DDNS
  SUB_LOGGING
  SUB_CONFIG_CONTROL
;

%token <std::string> STRING "constant string"
%token <int64_t> INTEGER "integer"
%token <double> FLOAT "floating point"
%token <bool> BOOLEAN "boolean"

%type <ElementPtr> value
%type <ElementPtr> map_value
%type <ElementPtr> socket_type
%type <ElementPtr> outbound_interface_value
%type <ElementPtr> db_type
%type <ElementPtr> hr_mode
%type <ElementPtr> ncr_protocol_value
%type <ElementPtr> replace_client_name_value

%printer { yyoutput << $$; } <*>;

%%

// The whole grammar starts with a map, because the config file
// consists of Dhcp, Logger and DhcpDdns entries in one big { }.
// We made the same for subparsers at the exception of the JSON value.
%start start;

start: TOPLEVEL_JSON { ctx.ctx_ = ctx.NO_KEYWORD; } sub_json
     | TOPLEVEL_DHCP4 { ctx.ctx_ = ctx.CONFIG; } syntax_map
     | SUB_DHCP4 { ctx.ctx_ = ctx.DHCP4; } sub_dhcp4
     | SUB_INTERFACES4 { ctx.ctx_ = ctx.INTERFACES_CONFIG; } sub_interfaces4
     | SUB_SUBNET4 { ctx.ctx_ = ctx.SUBNET4; } sub_subnet4
     | SUB_POOL4 { ctx.ctx_ = ctx.POOLS; } sub_pool4
     | SUB_RESERVATION { ctx.ctx_ = ctx.RESERVATIONS; } sub_reservation
     | SUB_OPTION_DEFS { ctx.ctx_ = ctx.DHCP4; } sub_option_def_list
     | SUB_OPTION_DEF { ctx.ctx_ = ctx.OPTION_DEF; } sub_option_def
     | SUB_OPTION_DATA { ctx.ctx_ = ctx.OPTION_DATA; } sub_option_data
     | SUB_HOOKS_LIBRARY { ctx.ctx_ = ctx.HOOKS_LIBRARIES; } sub_hooks_library
     | SUB_DHCP_DDNS { ctx.ctx_ = ctx.DHCP_DDNS; } sub_dhcp_ddns
     | SUB_LOGGING { ctx.ctx_ = ctx.LOGGING; } sub_logging
     | SUB_CONFIG_CONTROL { ctx.ctx_ = ctx.CONFIG_CONTROL; } sub_config_control
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

map_value: map2 { $$ = ctx.stack_.back(); ctx.stack_.pop_back(); };

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

// This one is used in syntax parser and is restricted to strings.
list_strings: LSQUARE_BRACKET {
    // List parsing about to start
} list_strings_content RSQUARE_BRACKET {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
};

list_strings_content: %empty // Empty list
                    | not_empty_list_strings
                    ;

not_empty_list_strings: STRING {
                          ElementPtr s(new StringElement($1, ctx.loc2pos(@1)));
                          ctx.stack_.back()->add(s);
                          }
                      | not_empty_list_strings COMMA STRING {
                          ElementPtr s(new StringElement($3, ctx.loc2pos(@3)));
                          ctx.stack_.back()->add(s);
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


// This defines the top-level { } that holds Control-agent, Dhcp6, Dhcp4,
// DhcpDdns or Logging objects.
syntax_map: LCURLY_BRACKET {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(@1)));
    ctx.stack_.push_back(m);
} global_objects RCURLY_BRACKET {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.

    // Dhcp4 is required
    ctx.require("Dhcp4", ctx.loc2pos(@1), ctx.loc2pos(@4));
};

// This represents top-level entries: Control-agent, Dhcp6, Dhcp4,
// DhcpDdns, Logging
global_objects: global_object
              | global_objects COMMA global_object
              ;

// This represents a single top level entry, e.g. Dhcp4 or DhcpDdns.
global_object: dhcp4_object
             | logging_object
             | dhcp6_json_object
             | dhcpddns_json_object
             | control_agent_json_object
             | unknown_map_entry
             ;

dhcp4_object: DHCP4 {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(@1)));
    ctx.stack_.back()->set("Dhcp4", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP4);
} COLON LCURLY_BRACKET global_params RCURLY_BRACKET {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
};

// subparser: similar to the corresponding rule but without parent
// so the stack is empty at the rule entry.
sub_dhcp4: LCURLY_BRACKET {
    // Parse the Dhcp4 map
    ElementPtr m(new MapElement(ctx.loc2pos(@1)));
    ctx.stack_.push_back(m);
} global_params RCURLY_BRACKET {
    // No global parameter is required
    // parsing completed
};

global_params: global_param
             | global_params COMMA global_param
             ;

// These are the parameters that are allowed in the top-level for
// Dhcp4.
global_param: valid_lifetime
            | renew_timer
            | rebind_timer
            | decline_probation_period
            | subnet4_list
            | shared_networks
            | interfaces_config
            | lease_database
            | hosts_database
            | hosts_databases
            | host_reservation_identifiers
            | client_classes
            | option_def_list
            | option_data_list
            | hooks_libraries
            | expired_leases_processing
            | dhcp4o6_port
            | control_socket
            | dhcp_queue_control
            | dhcp_ddns
            | echo_client_id
            | match_client_id
            | authoritative
            | next_server
            | server_hostname
            | boot_file_name
            | user_context
            | comment
            | sanity_checks
            | reservations
            | config_control
            | server_tag
            | reservation_mode
            | calculate_tee_times
            | t1_percent
            | t2_percent
            | unknown_map_entry
            ;

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

calculate_tee_times: CALCULATE_TEE_TIMES COLON BOOLEAN {
    ElementPtr ctt(new BoolElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("calculate-tee-times", ctt);
};

t1_percent: T1_PERCENT COLON FLOAT {
    ElementPtr t1(new DoubleElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("t1-percent", t1);
};

t2_percent: T2_PERCENT COLON FLOAT {
    ElementPtr t2(new DoubleElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("t2-percent", t2);
};

decline_probation_period: DECLINE_PROBATION_PERIOD COLON INTEGER {
    ElementPtr dpp(new IntElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
};

server_tag: SERVER_TAG  {
    ctx.enter(ctx.NO_KEYWORD);
} COLON STRING {
    ElementPtr stag(new StringElement($4, ctx.loc2pos(@4)));
    ctx.stack_.back()->set("server-tag", stag);
    ctx.leave();
};

echo_client_id: ECHO_CLIENT_ID COLON BOOLEAN {
    ElementPtr echo(new BoolElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("echo-client-id", echo);
};

match_client_id: MATCH_CLIENT_ID COLON BOOLEAN {
    ElementPtr match(new BoolElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("match-client-id", match);
};

authoritative: AUTHORITATIVE COLON BOOLEAN {
    ElementPtr prf(new BoolElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("authoritative", prf);
};


interfaces_config: INTERFACES_CONFIG {
    ElementPtr i(new MapElement(ctx.loc2pos(@1)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
} COLON LCURLY_BRACKET interfaces_config_params RCURLY_BRACKET {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
};

interfaces_config_params: interfaces_config_param
                        | interfaces_config_params COMMA interfaces_config_param
                        ;

interfaces_config_param: interfaces_list
                       | dhcp_socket_type
                       | outbound_interface
                       | re_detect
                       | user_context
                       | comment
                       | unknown_map_entry
                       ;

sub_interfaces4: LCURLY_BRACKET {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(@1)));
    ctx.stack_.push_back(m);
} interfaces_config_params RCURLY_BRACKET {
    // No interfaces config param is required
    // parsing completed
};

interfaces_list: INTERFACES {
    ElementPtr l(new ListElement(ctx.loc2pos(@1)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
} COLON list_strings {
    ctx.stack_.pop_back();
    ctx.leave();
};

dhcp_socket_type: DHCP_SOCKET_TYPE {
    ctx.enter(ctx.DHCP_SOCKET_TYPE);
} COLON socket_type {
    ctx.stack_.back()->set("dhcp-socket-type", $4);
    ctx.leave();
};

socket_type: RAW { $$ = ElementPtr(new StringElement("raw", ctx.loc2pos(@1))); }
           | UDP { $$ = ElementPtr(new StringElement("udp", ctx.loc2pos(@1))); }
           ;

outbound_interface: OUTBOUND_INTERFACE {
    ctx.enter(ctx.OUTBOUND_INTERFACE);
} COLON outbound_interface_value {
    ctx.stack_.back()->set("outbound-interface", $4);
    ctx.leave();
};

outbound_interface_value: SAME_AS_INBOUND {
    $$ = ElementPtr(new StringElement("same-as-inbound", ctx.loc2pos(@1)));
} | USE_ROUTING {
    $$ = ElementPtr(new StringElement("use-routing", ctx.loc2pos(@1)));
    } ;

re_detect: RE_DETECT COLON BOOLEAN {
    ElementPtr b(new BoolElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("re-detect", b);
};


lease_database: LEASE_DATABASE {
    ElementPtr i(new MapElement(ctx.loc2pos(@1)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
} COLON LCURLY_BRACKET database_map_params RCURLY_BRACKET {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(@4), ctx.loc2pos(@6));
    ctx.stack_.pop_back();
    ctx.leave();
};

sanity_checks: SANITY_CHECKS {
    ElementPtr m(new MapElement(ctx.loc2pos(@1)));
    ctx.stack_.back()->set("sanity-checks", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SANITY_CHECKS);
} COLON LCURLY_BRACKET sanity_checks_params RCURLY_BRACKET {
    ctx.stack_.pop_back();
    ctx.leave();
};

sanity_checks_params: sanity_checks_param
                    | sanity_checks_params COMMA sanity_checks_param;

sanity_checks_param: lease_checks;

lease_checks: LEASE_CHECKS {
    ctx.enter(ctx.NO_KEYWORD);
} COLON STRING {

    if ( (string($4) == "none") ||
         (string($4) == "warn") ||
         (string($4) == "fix") ||
         (string($4) == "fix-del") ||
         (string($4) == "del")) {
        ElementPtr user(new StringElement($4, ctx.loc2pos(@4)));
        ctx.stack_.back()->set("lease-checks", user);
        ctx.leave();
    } else {
        error(@4, "Unsupported 'lease-checks value: " + string($4) +
              ", supported values are: none, warn, fix, fix-del, del");
    }
}

hosts_database: HOSTS_DATABASE {
    ElementPtr i(new MapElement(ctx.loc2pos(@1)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
} COLON LCURLY_BRACKET database_map_params RCURLY_BRACKET {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(@4), ctx.loc2pos(@6));
    ctx.stack_.pop_back();
    ctx.leave();
};

hosts_databases: HOSTS_DATABASES {
    ElementPtr l(new ListElement(ctx.loc2pos(@1)));
    ctx.stack_.back()->set("hosts-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOSTS_DATABASE);
} COLON LSQUARE_BRACKET database_list RSQUARE_BRACKET {
    ctx.stack_.pop_back();
    ctx.leave();
};

database_list: %empty
             | not_empty_database_list
             ;

not_empty_database_list: database
                       | not_empty_database_list COMMA database
                       ;

database: LCURLY_BRACKET {
    ElementPtr m(new MapElement(ctx.loc2pos(@1)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
} database_map_params RCURLY_BRACKET {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(@1), ctx.loc2pos(@4));
    ctx.stack_.pop_back();
};

database_map_params: database_map_param
                   | database_map_params COMMA database_map_param
                   ;

database_map_param: database_type
                  | user
                  | password
                  | host
                  | port
                  | name
                  | persist
                  | lfc_interval
                  | readonly
                  | connect_timeout
                  | contact_points
                  | max_reconnect_tries
                  | reconnect_wait_time
                  | request_timeout
                  | tcp_keepalive
                  | tcp_nodelay
                  | keyspace
                  | consistency
                  | serial_consistency
                  | unknown_map_entry
                  ;

database_type: TYPE {
    ctx.enter(ctx.DATABASE_TYPE);
} COLON db_type {
    ctx.stack_.back()->set("type", $4);
    ctx.leave();
};

db_type: MEMFILE { $$ = ElementPtr(new StringElement("memfile", ctx.loc2pos(@1))); }
       | MYSQL { $$ = ElementPtr(new StringElement("mysql", ctx.loc2pos(@1))); }
       | POSTGRESQL { $$ = ElementPtr(new StringElement("postgresql", ctx.loc2pos(@1))); }
       | CQL { $$ = ElementPtr(new StringElement("cql", ctx.loc2pos(@1))); }
       ;

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

port: PORT COLON INTEGER {
    ElementPtr p(new IntElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("port", p);
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

connect_timeout: CONNECT_TIMEOUT COLON INTEGER {
    ElementPtr n(new IntElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("connect-timeout", n);
};

request_timeout: REQUEST_TIMEOUT COLON INTEGER {
    ElementPtr n(new IntElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("request-timeout", n);
};

tcp_keepalive: TCP_KEEPALIVE COLON INTEGER {
    ElementPtr n(new IntElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("tcp-keepalive", n);
};

tcp_nodelay: TCP_NODELAY COLON BOOLEAN {
    ElementPtr n(new BoolElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("tcp-nodelay", n);
};

contact_points: CONTACT_POINTS {
    ctx.enter(ctx.NO_KEYWORD);
} COLON STRING {
    ElementPtr cp(new StringElement($4, ctx.loc2pos(@4)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
};

keyspace: KEYSPACE {
    ctx.enter(ctx.NO_KEYWORD);
} COLON STRING {
    ElementPtr ks(new StringElement($4, ctx.loc2pos(@4)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
};

consistency: CONSISTENCY {
    ctx.enter(ctx.NO_KEYWORD);
} COLON STRING {
    ElementPtr c(new StringElement($4, ctx.loc2pos(@4)));
    ctx.stack_.back()->set("consistency", c);
    ctx.leave();
};

serial_consistency: SERIAL_CONSISTENCY {
    ctx.enter(ctx.NO_KEYWORD);
} COLON STRING {
    ElementPtr c(new StringElement($4, ctx.loc2pos(@4)));
    ctx.stack_.back()->set("serial-consistency", c);
    ctx.leave();
};

max_reconnect_tries: MAX_RECONNECT_TRIES COLON INTEGER {
    ElementPtr n(new IntElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
};

reconnect_wait_time: RECONNECT_WAIT_TIME COLON INTEGER {
    ElementPtr n(new IntElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
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
                           | circuit_id
                           | client_id
                           | flex_id
                           ;

duid_id : DUID {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(@1)));
    ctx.stack_.back()->add(duid);
};

hw_address_id : HW_ADDRESS {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(@1)));
    ctx.stack_.back()->add(hwaddr);
};

circuit_id : CIRCUIT_ID {
    ElementPtr circuit(new StringElement("circuit-id", ctx.loc2pos(@1)));
    ctx.stack_.back()->add(circuit);
};

client_id : CLIENT_ID {
    ElementPtr client(new StringElement("client-id", ctx.loc2pos(@1)));
    ctx.stack_.back()->add(client);
};

flex_id: FLEX_ID {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(@1)));
    ctx.stack_.back()->add(flex_id);
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
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(@1), ctx.loc2pos(@4));
    ctx.stack_.pop_back();
};

sub_hooks_library: LCURLY_BRACKET {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(@1)));
    ctx.stack_.push_back(m);
} hooks_params RCURLY_BRACKET {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(@1), ctx.loc2pos(@4));
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
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
} COLON LCURLY_BRACKET expired_leases_params RCURLY_BRACKET {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
};

expired_leases_params: expired_leases_param
                     | expired_leases_params COMMA expired_leases_param
                     ;

expired_leases_param: reclaim_timer_wait_time
                    | flush_reclaimed_timer_wait_time
                    | hold_reclaimed_time
                    | max_reclaim_leases
                    | max_reclaim_time
                    | unwarned_reclaim_cycles
                    ;

reclaim_timer_wait_time: RECLAIM_TIMER_WAIT_TIME COLON INTEGER {
    ElementPtr value(new IntElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
};

flush_reclaimed_timer_wait_time: FLUSH_RECLAIMED_TIMER_WAIT_TIME COLON INTEGER {
    ElementPtr value(new IntElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
};

hold_reclaimed_time: HOLD_RECLAIMED_TIME COLON INTEGER {
    ElementPtr value(new IntElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
};

max_reclaim_leases: MAX_RECLAIM_LEASES COLON INTEGER {
    ElementPtr value(new IntElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
};

max_reclaim_time: MAX_RECLAIM_TIME COLON INTEGER {
    ElementPtr value(new IntElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("max-reclaim-time", value);
};

unwarned_reclaim_cycles: UNWARNED_RECLAIM_CYCLES COLON INTEGER {
    ElementPtr value(new IntElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
};

// --- subnet4 ------------------------------------------
// This defines subnet4 as a list of maps.
// "subnet4": [ ... ]
subnet4_list: SUBNET4 {
    ElementPtr l(new ListElement(ctx.loc2pos(@1)));
    ctx.stack_.back()->set("subnet4", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET4);
} COLON LSQUARE_BRACKET subnet4_list_content RSQUARE_BRACKET {
    ctx.stack_.pop_back();
    ctx.leave();
};

// This defines the ... in "subnet4": [ ... ]
// It can either be empty (no subnets defined), have one subnet
// or have multiple subnets separate by comma.
subnet4_list_content: %empty
                    | not_empty_subnet4_list
                    ;

not_empty_subnet4_list: subnet4
                      | not_empty_subnet4_list COMMA subnet4
                      ;

// --- Subnet definitions -------------------------------

// This defines a single subnet, i.e. a single map with
// subnet4 array.
subnet4: LCURLY_BRACKET {
    ElementPtr m(new MapElement(ctx.loc2pos(@1)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
} subnet4_params RCURLY_BRACKET {
    // Once we reached this place, the subnet parsing is now complete.
    // If we want to, we can implement default values here.
    // In particular we can do things like this:
    // if (!ctx.stack_.back()->get("interface")) {
    //     ctx.stack_.back()->set("interface", StringElement("loopback"));
    // }
    //
    // We can also stack up one level (Dhcp4) and copy over whatever
    // global parameters we want to:
    // if (!ctx.stack_.back()->get("renew-timer")) {
    //     ElementPtr renew = ctx_stack_[...].get("renew-timer");
    //     if (renew) {
    //         ctx.stack_.back()->set("renew-timer", renew);
    //     }
    // }

    // The subnet subnet4 parameter is required
    ctx.require("subnet", ctx.loc2pos(@1), ctx.loc2pos(@4));
    ctx.stack_.pop_back();
};

sub_subnet4: LCURLY_BRACKET {
    // Parse the subnet4 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(@1)));
    ctx.stack_.push_back(m);
} subnet4_params RCURLY_BRACKET {
    // The subnet subnet4 parameter is required
    ctx.require("subnet", ctx.loc2pos(@1), ctx.loc2pos(@4));
    // parsing completed
};

// This defines that subnet can have one or more parameters.
subnet4_params: subnet4_param
              | subnet4_params COMMA subnet4_param
              ;

// This defines a list of allowed parameters for each subnet.
subnet4_param: valid_lifetime
             | renew_timer
             | rebind_timer
             | option_data_list
             | pools_list
             | subnet
             | interface
             | id
             | client_class
             | require_client_classes
             | reservations
             | reservation_mode
             | relay
             | match_client_id
             | authoritative
             | next_server
             | server_hostname
             | boot_file_name
             | subnet_4o6_interface
             | subnet_4o6_interface_id
             | subnet_4o6_subnet
             | user_context
             | comment
             | calculate_tee_times
             | t1_percent
             | t2_percent
             | unknown_map_entry
             ;

subnet: SUBNET {
    ctx.enter(ctx.NO_KEYWORD);
} COLON STRING {
    ElementPtr subnet(new StringElement($4, ctx.loc2pos(@4)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
};

subnet_4o6_interface: SUBNET_4O6_INTERFACE {
    ctx.enter(ctx.NO_KEYWORD);
} COLON STRING {
    ElementPtr iface(new StringElement($4, ctx.loc2pos(@4)));
    ctx.stack_.back()->set("4o6-interface", iface);
    ctx.leave();
};

subnet_4o6_interface_id: SUBNET_4O6_INTERFACE_ID {
    ctx.enter(ctx.NO_KEYWORD);
} COLON STRING {
    ElementPtr iface(new StringElement($4, ctx.loc2pos(@4)));
    ctx.stack_.back()->set("4o6-interface-id", iface);
    ctx.leave();
};

subnet_4o6_subnet: SUBNET_4O6_SUBNET {
    ctx.enter(ctx.NO_KEYWORD);
} COLON STRING {
    ElementPtr iface(new StringElement($4, ctx.loc2pos(@4)));
    ctx.stack_.back()->set("4o6-subnet", iface);
    ctx.leave();
};

interface: INTERFACE {
    ctx.enter(ctx.NO_KEYWORD);
} COLON STRING {
    ElementPtr iface(new StringElement($4, ctx.loc2pos(@4)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
};

client_class: CLIENT_CLASS {
    ctx.enter(ctx.NO_KEYWORD);
} COLON STRING {
    ElementPtr cls(new StringElement($4, ctx.loc2pos(@4)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
};

require_client_classes: REQUIRE_CLIENT_CLASSES {
    ElementPtr c(new ListElement(ctx.loc2pos(@1)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
} COLON list_strings {
    ctx.stack_.pop_back();
    ctx.leave();
};

reservation_mode: RESERVATION_MODE {
    ctx.enter(ctx.RESERVATION_MODE);
} COLON hr_mode {
    ctx.stack_.back()->set("reservation-mode", $4);
    ctx.leave();
};

hr_mode: DISABLED { $$ = ElementPtr(new StringElement("disabled", ctx.loc2pos(@1))); }
       | OUT_OF_POOL { $$ = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(@1))); }
       | GLOBAL { $$ = ElementPtr(new StringElement("global", ctx.loc2pos(@1))); }
       | ALL { $$ = ElementPtr(new StringElement("all", ctx.loc2pos(@1))); }
       ;

id: ID COLON INTEGER {
    ElementPtr id(new IntElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("id", id);
};

// ---- shared-networks ---------------------

shared_networks: SHARED_NETWORKS {
    ElementPtr l(new ListElement(ctx.loc2pos(@1)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
} COLON LSQUARE_BRACKET shared_networks_content RSQUARE_BRACKET {
    ctx.stack_.pop_back();
    ctx.leave();
};

// This allows 0 or more shared network definitions.
shared_networks_content: %empty
                       | shared_networks_list
                       ;

// This allows 1 or more shared network definitions.
shared_networks_list: shared_network
                    | shared_networks_list COMMA shared_network
                    ;

shared_network: LCURLY_BRACKET {
    ElementPtr m(new MapElement(ctx.loc2pos(@1)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
} shared_network_params RCURLY_BRACKET {
    ctx.stack_.pop_back();
};

shared_network_params: shared_network_param
                     | shared_network_params COMMA shared_network_param
                     ;

shared_network_param: name
                    | subnet4_list
                    | interface
                    | renew_timer
                    | rebind_timer
                    | option_data_list
                    | match_client_id
                    | authoritative
                    | next_server
                    | server_hostname
                    | boot_file_name
                    | relay
                    | reservation_mode
                    | client_class
                    | require_client_classes
                    | valid_lifetime
                    | user_context
                    | comment
                    | calculate_tee_times
                    | t1_percent
                    | t2_percent
                    | unknown_map_entry
                    ;

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

// This defines the top level scope when the parser is told to parse
// option definitions. It works as a subset limited to option
// definitions
sub_option_def_list: LCURLY_BRACKET {
    ElementPtr m(new MapElement(ctx.loc2pos(@1)));
    ctx.stack_.push_back(m);
} option_def_list RCURLY_BRACKET {
    // parsing completed
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
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(@1), ctx.loc2pos(@4));
    ctx.require("code", ctx.loc2pos(@1), ctx.loc2pos(@4));
    ctx.require("type", ctx.loc2pos(@1), ctx.loc2pos(@4));
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
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(@1), ctx.loc2pos(@4));
    ctx.require("code", ctx.loc2pos(@1), ctx.loc2pos(@4));
    ctx.require("type", ctx.loc2pos(@1), ctx.loc2pos(@4));
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
                | user_context
                | comment
                | unknown_map_entry
                ;

option_def_name: name;

code: CODE COLON INTEGER {
    ElementPtr code(new IntElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("code", code);
};

option_def_code: code;

option_def_type: TYPE {
    ctx.enter(ctx.NO_KEYWORD);
} COLON STRING {
    ElementPtr prf(new StringElement($4, ctx.loc2pos(@4)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
};

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
// in several places, but most notably in subnet4 entries.
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
    /// @todo: the code or name parameters are required.
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
    /// @todo: the code or name parameters are required.
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
                 | option_data_always_send
                 | user_context
                 | comment
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

option_data_always_send: ALWAYS_SEND COLON BOOLEAN {
    ElementPtr persist(new BoolElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("always-send", persist);
};

// ---- pools ------------------------------------

// This defines the "pools": [ ... ] entry that may appear in subnet4.
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
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(@1), ctx.loc2pos(@4));
    ctx.stack_.pop_back();
};

sub_pool4: LCURLY_BRACKET {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(@1)));
    ctx.stack_.push_back(m);
} pool_params RCURLY_BRACKET {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(@1), ctx.loc2pos(@4));
    // parsing completed
};

pool_params: pool_param
           | pool_params COMMA pool_param
           ;

pool_param: pool_entry
          | option_data_list
          | client_class
          | require_client_classes
          | user_context
          | comment
          | unknown_map_entry
          ;

pool_entry: POOL {
    ctx.enter(ctx.NO_KEYWORD);
} COLON STRING {
    ElementPtr pool(new StringElement($4, ctx.loc2pos(@4)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
};

user_context: USER_CONTEXT {
    ctx.enter(ctx.NO_KEYWORD);
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
    ctx.enter(ctx.NO_KEYWORD);
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

// --- end of pools definition -------------------------------

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
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
};

sub_reservation: LCURLY_BRACKET {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(@1)));
    ctx.stack_.push_back(m);
} reservation_params RCURLY_BRACKET {
    /// @todo: an identifier parameter is required.
    // parsing completed
};

reservation_params: %empty
                  | not_empty_reservation_params
                  ;

not_empty_reservation_params: reservation_param
    | not_empty_reservation_params COMMA reservation_param
    ;

/// @todo probably need to add mac-address as well here
reservation_param: duid
                 | reservation_client_classes
                 | client_id_value
                 | circuit_id_value
                 | flex_id_value
                 | ip_address
                 | hw_address
                 | hostname
                 | option_data_list
                 | next_server
                 | server_hostname
                 | boot_file_name
                 | user_context
                 | comment
                 | unknown_map_entry
                 ;

next_server: NEXT_SERVER {
    ctx.enter(ctx.NO_KEYWORD);
} COLON STRING {
    ElementPtr next_server(new StringElement($4, ctx.loc2pos(@4)));
    ctx.stack_.back()->set("next-server", next_server);
    ctx.leave();
};

server_hostname: SERVER_HOSTNAME {
    ctx.enter(ctx.NO_KEYWORD);
} COLON STRING {
    ElementPtr srv(new StringElement($4, ctx.loc2pos(@4)));
    ctx.stack_.back()->set("server-hostname", srv);
    ctx.leave();
};

boot_file_name: BOOT_FILE_NAME {
    ctx.enter(ctx.NO_KEYWORD);
} COLON STRING {
    ElementPtr bootfile(new StringElement($4, ctx.loc2pos(@4)));
    ctx.stack_.back()->set("boot-file-name", bootfile);
    ctx.leave();
};

ip_address: IP_ADDRESS {
    ctx.enter(ctx.NO_KEYWORD);
} COLON STRING {
    ElementPtr addr(new StringElement($4, ctx.loc2pos(@4)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
};

ip_addresses: IP_ADDRESSES {
    ElementPtr l(new ListElement(ctx.loc2pos(@1)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
} COLON list_strings {
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

client_id_value: CLIENT_ID {
    ctx.enter(ctx.NO_KEYWORD);
} COLON STRING {
    ElementPtr hw(new StringElement($4, ctx.loc2pos(@4)));
    ctx.stack_.back()->set("client-id", hw);
    ctx.leave();
};

circuit_id_value: CIRCUIT_ID {
    ctx.enter(ctx.NO_KEYWORD);
} COLON STRING {
    ElementPtr hw(new StringElement($4, ctx.loc2pos(@4)));
    ctx.stack_.back()->set("circuit-id", hw);
    ctx.leave();
};

flex_id_value: FLEX_ID {
    ctx.enter(ctx.NO_KEYWORD);
} COLON STRING {
    ElementPtr hw(new StringElement($4, ctx.loc2pos(@4)));
    ctx.stack_.back()->set("flex-id", hw);
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
} COLON list_strings {
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

relay_map: ip_address
         | ip_addresses
         ;

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

client_classes_list: client_class_entry
                   | client_classes_list COMMA client_class_entry
                   ;

client_class_entry: LCURLY_BRACKET {
    ElementPtr m(new MapElement(ctx.loc2pos(@1)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
} client_class_params RCURLY_BRACKET {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(@1), ctx.loc2pos(@4));
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
                  | only_if_required
                  | option_def_list
                  | option_data_list
                  | next_server
                  | server_hostname
                  | boot_file_name
                  | user_context
                  | comment
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

only_if_required: ONLY_IF_REQUIRED COLON BOOLEAN {
    ElementPtr b(new BoolElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("only-if-required", b);
};

// --- end of client classes ---------------------------------

// was server-id but in is DHCPv6-only

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

control_socket_param: control_socket_type
                    | control_socket_name
                    | user_context
                    | comment
                    | unknown_map_entry
                    ;

control_socket_type: SOCKET_TYPE {
    ctx.enter(ctx.NO_KEYWORD);
} COLON STRING {
    ElementPtr stype(new StringElement($4, ctx.loc2pos(@4)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
};

control_socket_name: SOCKET_NAME {
    ctx.enter(ctx.NO_KEYWORD);
} COLON STRING {
    ElementPtr name(new StringElement($4, ctx.loc2pos(@4)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
};


// --- dhcp-queue-control ---------------------------------------------

dhcp_queue_control: DHCP_QUEUE_CONTROL {
    ctx.enter(ctx.NO_KEYWORD);
} COLON map_value {
    ElementPtr qc = $4;
    ctx.stack_.back()->set("dhcp-queue-control", qc);

    // Doing this manually, because dhcp-queue-control
    // content is otherwise arbitrary
    if (!qc->contains("enable-queue")) {
        std::stringstream msg;
        msg << "'enable-queue' is required: ";
        msg  << "(" << qc->getPosition().str() << ")";
        error(@1, msg.str());
    }

    ConstElementPtr enable_queue = qc->get("enable-queue");
    if (enable_queue->getType() != Element::boolean) {
        std::stringstream msg;
        msg << "'enable-queue' must be boolean: ";
        msg  << "(" << qc->getPosition().str() << ")";
        error(@1, msg.str());
    }

    if (qc->contains("queue-type")) {
        ConstElementPtr queue_type = qc->get("queue-type");
        if (queue_type->getType() != Element::string) {
            std::stringstream msg;
            msg << "'queue-type' must be a string: ";
            msg  << "(" << qc->getPosition().str() << ")";
            error(@1, msg.str());
        }
    }

    ctx.leave();
};

// --- dhcp ddns ---------------------------------------------

dhcp_ddns: DHCP_DDNS {
    ElementPtr m(new MapElement(ctx.loc2pos(@1)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
} COLON LCURLY_BRACKET dhcp_ddns_params RCURLY_BRACKET {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(@4), ctx.loc2pos(@6));
    ctx.stack_.pop_back();
    ctx.leave();
};

sub_dhcp_ddns: LCURLY_BRACKET {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(@1)));
    ctx.stack_.push_back(m);
} dhcp_ddns_params RCURLY_BRACKET {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(@1), ctx.loc2pos(@4));
    // parsing completed
};

dhcp_ddns_params: dhcp_ddns_param
                | dhcp_ddns_params COMMA dhcp_ddns_param
                ;

dhcp_ddns_param: enable_updates
               | qualifying_suffix
               | server_ip
               | server_port
               | sender_ip
               | sender_port
               | max_queue_size
               | ncr_protocol
               | ncr_format
               | override_no_update
               | override_client_update
               | replace_client_name
               | generated_prefix
               | hostname_char_set
               | hostname_char_replacement
               | user_context
               | comment
               | unknown_map_entry
               ;

enable_updates: ENABLE_UPDATES COLON BOOLEAN {
    ElementPtr b(new BoolElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("enable-updates", b);
};

qualifying_suffix: QUALIFYING_SUFFIX {
    ctx.enter(ctx.NO_KEYWORD);
} COLON STRING {
    ElementPtr s(new StringElement($4, ctx.loc2pos(@4)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
};

server_ip: SERVER_IP {
    ctx.enter(ctx.NO_KEYWORD);
} COLON STRING {
    ElementPtr s(new StringElement($4, ctx.loc2pos(@4)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
};

server_port: SERVER_PORT COLON INTEGER {
    ElementPtr i(new IntElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("server-port", i);
};

sender_ip: SENDER_IP {
    ctx.enter(ctx.NO_KEYWORD);
} COLON STRING {
    ElementPtr s(new StringElement($4, ctx.loc2pos(@4)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
};

sender_port: SENDER_PORT COLON INTEGER {
    ElementPtr i(new IntElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("sender-port", i);
};

max_queue_size: MAX_QUEUE_SIZE COLON INTEGER {
    ElementPtr i(new IntElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("max-queue-size", i);
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

override_no_update: OVERRIDE_NO_UPDATE COLON BOOLEAN {
    ElementPtr b(new BoolElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("override-no-update", b);
};

override_client_update: OVERRIDE_CLIENT_UPDATE COLON BOOLEAN {
    ElementPtr b(new BoolElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("override-client-update", b);
};

replace_client_name: REPLACE_CLIENT_NAME {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
} COLON replace_client_name_value {
    ctx.stack_.back()->set("replace-client-name", $4);
    ctx.leave();
};

replace_client_name_value:
    WHEN_PRESENT {
      $$ = ElementPtr(new StringElement("when-present", ctx.loc2pos(@1)));
      }
  | NEVER {
      $$ = ElementPtr(new StringElement("never", ctx.loc2pos(@1)));
      }
  | ALWAYS {
      $$ = ElementPtr(new StringElement("always", ctx.loc2pos(@1)));
      }
  | WHEN_NOT_PRESENT {
      $$ = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(@1)));
      }
  | BOOLEAN  {
      error(@1, "boolean values for the replace-client-name are "
                "no longer supported");
      }
  ;

generated_prefix: GENERATED_PREFIX {
    ctx.enter(ctx.NO_KEYWORD);
} COLON STRING {
    ElementPtr s(new StringElement($4, ctx.loc2pos(@4)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
};

hostname_char_set: HOSTNAME_CHAR_SET {
    ctx.enter(ctx.NO_KEYWORD);
} COLON STRING {
    ElementPtr s(new StringElement($4, ctx.loc2pos(@4)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
};

hostname_char_replacement: HOSTNAME_CHAR_REPLACEMENT {
    ctx.enter(ctx.NO_KEYWORD);
} COLON STRING {
    ElementPtr s(new StringElement($4, ctx.loc2pos(@4)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
};


// JSON entries for Dhcp4 and DhcpDdns

dhcp6_json_object: DHCP6 {
    ctx.enter(ctx.NO_KEYWORD);
} COLON value {
    ctx.stack_.back()->set("Dhcp6", $4);
    ctx.leave();
};

dhcpddns_json_object: DHCPDDNS {
    ctx.enter(ctx.NO_KEYWORD);
} COLON value {
    ctx.stack_.back()->set("DhcpDdns", $4);
    ctx.leave();
};

control_agent_json_object: CONTROL_AGENT {
    ctx.enter(ctx.NO_KEYWORD);
} COLON value {
    ctx.stack_.back()->set("Control-agent", $4);
    ctx.leave();
};

config_control: CONFIG_CONTROL {
    ElementPtr i(new MapElement(ctx.loc2pos(@1)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
} COLON LCURLY_BRACKET config_control_params RCURLY_BRACKET {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
};

sub_config_control: LCURLY_BRACKET {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(@1)));
    ctx.stack_.push_back(m);
} config_control_params RCURLY_BRACKET {
    // No config_control params are required
    // parsing completed
};

// This defines that subnet can have one or more parameters.
config_control_params: config_control_param
                     | config_control_params COMMA config_control_param
                     ;

// This defines a list of allowed parameters for each subnet.
config_control_param: config_databases
                    | config_fetch_wait_time
                    ;

config_databases: CONFIG_DATABASES {
    ElementPtr l(new ListElement(ctx.loc2pos(@1)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
} COLON LSQUARE_BRACKET database_list RSQUARE_BRACKET {
    ctx.stack_.pop_back();
    ctx.leave();
};

config_fetch_wait_time: CONFIG_FETCH_WAIT_TIME COLON INTEGER {
    ElementPtr value(new IntElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("config-fetch-wait-time", value);
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

sub_logging: LCURLY_BRACKET {
    // Parse the Logging map
    ElementPtr m(new MapElement(ctx.loc2pos(@1)));
    ctx.stack_.push_back(m);
} logging_params RCURLY_BRACKET {
    // parsing completed
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
// is "loggers": [ ... ].
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
    ctx.enter(ctx.NO_KEYWORD);
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
isc::dhcp::Dhcp4Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
