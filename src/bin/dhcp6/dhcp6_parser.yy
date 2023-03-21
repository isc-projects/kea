/* Copyright (C) 2016-2023 Internet Systems Consortium, Inc. ("ISC")

   This Source Code Form is subject to the terms of the Mozilla Public
   License, v. 2.0. If a copy of the MPL was not distributed with this
   file, You can obtain one at http://mozilla.org/MPL/2.0/. */

%skeleton "lalr1.cc" /* -*- C++ -*- */
%require "3.3.0"
%defines
%define api.parser.class {Dhcp6Parser}
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
// Tokens in an order which makes sense and related to the intended use.
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

  DATA_DIRECTORY "data-directory"
  CONFIG_CONTROL "config-control"
  CONFIG_DATABASES "config-databases"
  CONFIG_FETCH_WAIT_TIME "config-fetch-wait-time"

  INTERFACES_CONFIG "interfaces-config"
  INTERFACES "interfaces"
  RE_DETECT "re-detect"
  SERVICE_SOCKETS_REQUIRE_ALL "service-sockets-require-all"
  SERVICE_SOCKETS_RETRY_WAIT_TIME "service-sockets-retry-wait-time"
  SERVICE_SOCKETS_MAX_RETRIES "service-sockets-max-retries"

  LEASE_DATABASE "lease-database"
  HOSTS_DATABASE "hosts-database"
  HOSTS_DATABASES "hosts-databases"
  TYPE "type"
  MEMFILE "memfile"
  MYSQL "mysql"
  POSTGRESQL "postgresql"
  USER "user"
  PASSWORD "password"
  HOST "host"
  PORT "port"
  PERSIST "persist"
  LFC_INTERVAL "lfc-interval"
  READONLY "readonly"
  CONNECT_TIMEOUT "connect-timeout"
  READ_TIMEOUT "read-timeout"
  WRITE_TIMEOUT "write-timeout"
  TCP_USER_TIMEOUT "tcp-user-timeout"
  MAX_RECONNECT_TRIES "max-reconnect-tries"
  RECONNECT_WAIT_TIME "reconnect-wait-time"
  ON_FAIL "on-fail"
  STOP_RETRY_EXIT "stop-retry-exit"
  SERVE_RETRY_EXIT "serve-retry-exit"
  SERVE_RETRY_CONTINUE "serve-retry-continue"
  MAX_ROW_ERRORS "max-row-errors"
  TRUST_ANCHOR "trust-anchor"
  CERT_FILE "cert-file"
  KEY_FILE "key-file"
  CIPHER_LIST "cipher-list"

  PREFERRED_LIFETIME "preferred-lifetime"
  MIN_PREFERRED_LIFETIME "min-preferred-lifetime"
  MAX_PREFERRED_LIFETIME "max-preferred-lifetime"
  VALID_LIFETIME "valid-lifetime"
  MIN_VALID_LIFETIME "min-valid-lifetime"
  MAX_VALID_LIFETIME "max-valid-lifetime"
  RENEW_TIMER "renew-timer"
  REBIND_TIMER "rebind-timer"
  CALCULATE_TEE_TIMES "calculate-tee-times"
  T1_PERCENT "t1-percent"
  T2_PERCENT "t2-percent"
  CACHE_THRESHOLD "cache-threshold"
  CACHE_MAX_AGE "cache-max-age"
  DECLINE_PROBATION_PERIOD "decline-probation-period"
  SERVER_TAG "server-tag"
  STATISTIC_DEFAULT_SAMPLE_COUNT "statistic-default-sample-count"
  STATISTIC_DEFAULT_SAMPLE_AGE "statistic-default-sample-age"
  DDNS_SEND_UPDATES "ddns-send-updates"
  DDNS_OVERRIDE_NO_UPDATE "ddns-override-no-update"
  DDNS_OVERRIDE_CLIENT_UPDATE "ddns-override-client-update"
  DDNS_REPLACE_CLIENT_NAME "ddns-replace-client-name"
  DDNS_GENERATED_PREFIX "ddns-generated-prefix"
  DDNS_QUALIFYING_SUFFIX "ddns-qualifying-suffix"
  DDNS_UPDATE_ON_RENEW "ddns-update-on-renew"
  DDNS_USE_CONFLICT_RESOLUTION "ddns-use-conflict-resolution"
  DDNS_TTL_PERCENT "ddns-ttl-percent"
  STORE_EXTENDED_INFO "store-extended-info"
  SUBNET6 "subnet6"
  OPTION_DEF "option-def"
  OPTION_DATA "option-data"
  NAME "name"
  DATA "data"
  CODE "code"
  SPACE "space"
  CSV_FORMAT "csv-format"
  ALWAYS_SEND "always-send"
  NEVER_SEND "never-send"
  RECORD_TYPES "record-types"
  ENCAPSULATE "encapsulate"
  ARRAY "array"
  PARKED_PACKET_LIMIT "parked-packet-limit"
  ALLOCATOR "allocator"
  PD_ALLOCATOR "pd-allocator"

  SHARED_NETWORKS "shared-networks"

  POOLS "pools"
  POOL "pool"
  PD_POOLS "pd-pools"
  PREFIX "prefix"
  PREFIX_LEN "prefix-len"
  EXCLUDED_PREFIX "excluded-prefix"
  EXCLUDED_PREFIX_LEN "excluded-prefix-len"
  DELEGATED_LEN "delegated-len"
  USER_CONTEXT "user-context"
  COMMENT "comment"

  SUBNET "subnet"
  INTERFACE "interface"
  INTERFACE_ID "interface-id"
  ID "id"
  RAPID_COMMIT "rapid-commit"
  RESERVATION_MODE "reservation-mode"
  DISABLED "disabled"
  OUT_OF_POOL "out-of-pool"
  GLOBAL "global"
  ALL "all"
  RESERVATIONS_GLOBAL "reservations-global"
  RESERVATIONS_IN_SUBNET "reservations-in-subnet"
  RESERVATIONS_OUT_OF_POOL "reservations-out-of-pool"

  MAC_SOURCES "mac-sources"
  RELAY_SUPPLIED_OPTIONS "relay-supplied-options"
  HOST_RESERVATION_IDENTIFIERS "host-reservation-identifiers"

  SANITY_CHECKS "sanity-checks"
  LEASE_CHECKS "lease-checks"
  EXTENDED_INFO_CHECKS "extended-info-checks"

  CLIENT_CLASSES "client-classes"
  REQUIRE_CLIENT_CLASSES "require-client-classes"
  TEST "test"
  TEMPLATE_TEST "template-test"
  ONLY_IF_REQUIRED "only-if-required"
  CLIENT_CLASS "client-class"

  RESERVATIONS "reservations"
  IP_ADDRESSES "ip-addresses"
  PREFIXES "prefixes"
  DUID "duid"
  HW_ADDRESS "hw-address"
  HOSTNAME "hostname"
  FLEX_ID "flex-id"

  RELAY "relay"
  IP_ADDRESS "ip-address"

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

  SERVER_ID "server-id"
  LLT "LLT"
  EN "EN"
  LL "LL"
  IDENTIFIER "identifier"
  HTYPE "htype"
  TIME "time"
  ENTERPRISE_ID "enterprise-id"

  DHCP4O6_PORT "dhcp4o6-port"

  DHCP_MULTI_THREADING "multi-threading"
  ENABLE_MULTI_THREADING "enable-multi-threading"
  THREAD_POOL_SIZE "thread-pool-size"
  PACKET_QUEUE_SIZE "packet-queue-size"

  CONTROL_SOCKET "control-socket"
  SOCKET_TYPE "socket-type"
  SOCKET_NAME "socket-name"

  DHCP_QUEUE_CONTROL "dhcp-queue-control"
  ENABLE_QUEUE "enable-queue"
  QUEUE_TYPE "queue-type"
  CAPACITY "capacity"

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
  UDP "UDP"
  TCP "TCP"
  JSON "JSON"
  WHEN_PRESENT "when-present"
  NEVER "never"
  ALWAYS "always"
  WHEN_NOT_PRESENT "when-not-present"
  HOSTNAME_CHAR_SET "hostname-char-set"
  HOSTNAME_CHAR_REPLACEMENT "hostname-char-replacement"
  EARLY_GLOBAL_RESERVATIONS_LOOKUP "early-global-reservations-lookup"
  IP_RESERVATIONS_UNIQUE "ip-reservations-unique"
  RESERVATIONS_LOOKUP_FIRST "reservations-lookup-first"

  LOGGERS "loggers"
  OUTPUT_OPTIONS "output_options"
  OUTPUT "output"
  DEBUGLEVEL "debuglevel"
  SEVERITY "severity"
  FLUSH "flush"
  MAXSIZE "maxsize"
  MAXVER "maxver"
  PATTERN "pattern"

  COMPATIBILITY "compatibility"
  LENIENT_OPTION_PARSING "lenient-option-parsing"

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
  SUB_OPTION_DEFS
  SUB_OPTION_DEF
  SUB_OPTION_DATA
  SUB_HOOKS_LIBRARY
  SUB_DHCP_DDNS
  SUB_CONFIG_CONTROL
;

%token <std::string> STRING "constant string"
%token <int64_t> INTEGER "integer"
%token <double> FLOAT "floating point"
%token <bool> BOOLEAN "boolean"

%type <ElementPtr> value
%type <ElementPtr> map_value
%type <ElementPtr> db_type
%type <ElementPtr> on_fail_mode
%type <ElementPtr> hr_mode
%type <ElementPtr> duid_type
%type <ElementPtr> ncr_protocol_value
%type <ElementPtr> ddns_replace_client_name_value

%printer { yyoutput << $$; } <*>;

%%

// The whole grammar starts with a map, because the config file
// consists of Dhcp, Logger and DhcpDdns entries in one big { }.
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
     | SUB_OPTION_DEFS { ctx.ctx_ = ctx.DHCP6; } sub_option_def_list
     | SUB_OPTION_DEF { ctx.ctx_ = ctx.OPTION_DEF; } sub_option_def
     | SUB_OPTION_DATA { ctx.ctx_ = ctx.OPTION_DATA; } sub_option_data
     | SUB_HOOKS_LIBRARY { ctx.ctx_ = ctx.HOOKS_LIBRARIES; } sub_hooks_library
     | SUB_DHCP_DDNS { ctx.ctx_ = ctx.DHCP_DDNS; } sub_dhcp_ddns
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
                  ctx.unique($1, ctx.loc2pos(@1));
                  ctx.stack_.back()->set($1, $3);
                  }
             | not_empty_map COMMA STRING COLON value {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.unique($3, ctx.loc2pos(@3));
                  ctx.stack_.back()->set($3, $5);
                  }
             | not_empty_map COMMA {
                 ctx.warnAboutExtraCommas(@2);
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
              | not_empty_list COMMA {
                  ctx.warnAboutExtraCommas(@2);
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
                      | not_empty_list_strings COMMA {
                          ctx.warnAboutExtraCommas(@2);
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


// This defines the top-level { } that holds Dhcp6 only object.
syntax_map: LCURLY_BRACKET {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(@1)));
    ctx.stack_.push_back(m);
} global_object RCURLY_BRACKET {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.

    // Dhcp6 is required
    ctx.require("Dhcp6", ctx.loc2pos(@1), ctx.loc2pos(@4));
};

// This represents the single top level entry, e.g. Dhcp6.
global_object: DHCP6 {
    // This code is executed when we're about to start parsing
    // the content of the map
    // Prevent against duplicate.
    ctx.unique("Dhcp6", ctx.loc2pos(@1));
    ElementPtr m(new MapElement(ctx.loc2pos(@1)));
    ctx.stack_.back()->set("Dhcp6", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP6);
} COLON LCURLY_BRACKET global_params RCURLY_BRACKET {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
             | global_object_comma
             ;

global_object_comma: global_object COMMA {
    ctx.warnAboutExtraCommas(@2);
};

// subparser: similar to the corresponding rule but without parent
// so the stack is empty at the rule entry.
sub_dhcp6: LCURLY_BRACKET {
    // Parse the Dhcp6 map
    ElementPtr m(new MapElement(ctx.loc2pos(@1)));
    ctx.stack_.push_back(m);
} global_params RCURLY_BRACKET {
    // No global parameter is required
    // parsing completed
};

global_params: global_param
             | global_params COMMA global_param
             | global_params COMMA {
                 ctx.warnAboutExtraCommas(@2);
                 }
             ;

// These are the parameters that are allowed in the top-level for
// Dhcp6.
global_param: data_directory
            | preferred_lifetime
            | min_preferred_lifetime
            | max_preferred_lifetime
            | valid_lifetime
            | min_valid_lifetime
            | max_valid_lifetime
            | renew_timer
            | rebind_timer
            | decline_probation_period
            | subnet6_list
            | shared_networks
            | interfaces_config
            | lease_database
            | hosts_database
            | hosts_databases
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
            | dhcp_queue_control
            | dhcp_ddns
            | user_context
            | comment
            | sanity_checks
            | reservations
            | config_control
            | server_tag
            | reservation_mode
            | reservations_global
            | reservations_in_subnet
            | reservations_out_of_pool
            | calculate_tee_times
            | t1_percent
            | t2_percent
            | cache_threshold
            | cache_max_age
            | loggers
            | hostname_char_set
            | hostname_char_replacement
            | ddns_send_updates
            | ddns_override_no_update
            | ddns_override_client_update
            | ddns_replace_client_name
            | ddns_generated_prefix
            | ddns_qualifying_suffix
            | ddns_update_on_renew
            | ddns_use_conflict_resolution
            | ddns_ttl_percent
            | store_extended_info
            | statistic_default_sample_count
            | statistic_default_sample_age
            | dhcp_multi_threading
            | early_global_reservations_lookup
            | ip_reservations_unique
            | reservations_lookup_first
            | compatibility
            | parked_packet_limit
            | allocator
            | pd_allocator
            | unknown_map_entry
            ;

data_directory: DATA_DIRECTORY {
    ctx.unique("data-directory", ctx.loc2pos(@1));
    ctx.enter(ctx.NO_KEYWORD);
} COLON STRING {
    ElementPtr datadir(new StringElement($4, ctx.loc2pos(@4)));
    ctx.stack_.back()->set("data-directory", datadir);
    ctx.leave();
};

preferred_lifetime: PREFERRED_LIFETIME COLON INTEGER {
    ctx.unique("preferred-lifetime", ctx.loc2pos(@1));
    ElementPtr prf(new IntElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("preferred-lifetime", prf);
};

min_preferred_lifetime: MIN_PREFERRED_LIFETIME COLON INTEGER {
    ctx.unique("min-preferred-lifetime", ctx.loc2pos(@1));
    ElementPtr prf(new IntElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("min-preferred-lifetime", prf);
};

max_preferred_lifetime: MAX_PREFERRED_LIFETIME COLON INTEGER {
    ctx.unique("max-preferred-lifetime", ctx.loc2pos(@1));
    ElementPtr prf(new IntElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("max-preferred-lifetime", prf);
};

valid_lifetime: VALID_LIFETIME COLON INTEGER {
    ctx.unique("valid-lifetime", ctx.loc2pos(@1));
    ElementPtr prf(new IntElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("valid-lifetime", prf);
};

min_valid_lifetime: MIN_VALID_LIFETIME COLON INTEGER {
    ctx.unique("min-valid-lifetime", ctx.loc2pos(@1));
    ElementPtr prf(new IntElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("min-valid-lifetime", prf);
};

max_valid_lifetime: MAX_VALID_LIFETIME COLON INTEGER {
    ctx.unique("max-valid-lifetime", ctx.loc2pos(@1));
    ElementPtr prf(new IntElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("max-valid-lifetime", prf);
};

renew_timer: RENEW_TIMER COLON INTEGER {
    ctx.unique("renew-timer", ctx.loc2pos(@1));
    ElementPtr prf(new IntElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("renew-timer", prf);
};

rebind_timer: REBIND_TIMER COLON INTEGER {
    ctx.unique("rebind-timer", ctx.loc2pos(@1));
    ElementPtr prf(new IntElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("rebind-timer", prf);
};

calculate_tee_times: CALCULATE_TEE_TIMES COLON BOOLEAN {
    ctx.unique("calculate-tee-times", ctx.loc2pos(@1));
    ElementPtr ctt(new BoolElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("calculate-tee-times", ctt);
};

t1_percent: T1_PERCENT COLON FLOAT {
    ctx.unique("t1-percent", ctx.loc2pos(@1));
    ElementPtr t1(new DoubleElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("t1-percent", t1);
};

t2_percent: T2_PERCENT COLON FLOAT {
    ctx.unique("t2-percent", ctx.loc2pos(@1));
    ElementPtr t2(new DoubleElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("t2-percent", t2);
};

cache_threshold: CACHE_THRESHOLD COLON FLOAT {
    ctx.unique("cache-threshold", ctx.loc2pos(@1));
    ElementPtr ct(new DoubleElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("cache-threshold", ct);
};

cache_max_age: CACHE_MAX_AGE COLON INTEGER {
    ctx.unique("cache-max-age", ctx.loc2pos(@1));
    ElementPtr cm(new IntElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("cache-max-age", cm);
};

decline_probation_period: DECLINE_PROBATION_PERIOD COLON INTEGER {
    ctx.unique("decline-probation-period", ctx.loc2pos(@1));
    ElementPtr dpp(new IntElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
};

ddns_send_updates: DDNS_SEND_UPDATES COLON BOOLEAN {
    ctx.unique("ddns-send-updates", ctx.loc2pos(@1));
    ElementPtr b(new BoolElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("ddns-send-updates", b);
};

ddns_override_no_update: DDNS_OVERRIDE_NO_UPDATE COLON BOOLEAN {
    ctx.unique("ddns-override-no-update", ctx.loc2pos(@1));
    ElementPtr b(new BoolElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("ddns-override-no-update", b);
};

ddns_override_client_update: DDNS_OVERRIDE_CLIENT_UPDATE COLON BOOLEAN {
    ctx.unique("ddns-override-client-update", ctx.loc2pos(@1));
    ElementPtr b(new BoolElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("ddns-override-client-update", b);
};

ddns_replace_client_name: DDNS_REPLACE_CLIENT_NAME {
    ctx.unique("ddns-replace-client-name", ctx.loc2pos(@1));
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
} COLON ddns_replace_client_name_value {
    ctx.stack_.back()->set("ddns-replace-client-name", $4);
    ctx.leave();
};

ddns_replace_client_name_value:
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
  | BOOLEAN {
      error(@1, "boolean values for the replace-client-name are "
                "no longer supported");
      }
  ;

ddns_generated_prefix: DDNS_GENERATED_PREFIX {
    ctx.unique("ddns-generated-prefix", ctx.loc2pos(@1));
    ctx.enter(ctx.NO_KEYWORD);
} COLON STRING {
    ElementPtr s(new StringElement($4, ctx.loc2pos(@4)));
    ctx.stack_.back()->set("ddns-generated-prefix", s);
    ctx.leave();
};

ddns_qualifying_suffix: DDNS_QUALIFYING_SUFFIX {
    ctx.unique("ddns-qualifying-suffix", ctx.loc2pos(@1));
    ctx.enter(ctx.NO_KEYWORD);
} COLON STRING {
    ElementPtr s(new StringElement($4, ctx.loc2pos(@4)));
    ctx.stack_.back()->set("ddns-qualifying-suffix", s);
    ctx.leave();
};

ddns_update_on_renew: DDNS_UPDATE_ON_RENEW COLON BOOLEAN {
    ctx.unique("ddns-update-on-renew", ctx.loc2pos(@1));
    ElementPtr b(new BoolElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("ddns-update-on-renew", b);
};

ddns_use_conflict_resolution: DDNS_USE_CONFLICT_RESOLUTION COLON BOOLEAN {
    ctx.unique("ddns-use-conflict-resolution", ctx.loc2pos(@1));
    ElementPtr b(new BoolElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("ddns-use-conflict-resolution", b);
};

ddns_ttl_percent: DDNS_TTL_PERCENT COLON FLOAT {
    ctx.unique("ddns-ttl-percent", ctx.loc2pos(@1));
    ElementPtr ttl(new DoubleElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("ddns-ttl-percent", ttl);
};

hostname_char_set: HOSTNAME_CHAR_SET {
    ctx.unique("hostname-char-set", ctx.loc2pos(@1));
    ctx.enter(ctx.NO_KEYWORD);
} COLON STRING {
    ElementPtr s(new StringElement($4, ctx.loc2pos(@4)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
};

hostname_char_replacement: HOSTNAME_CHAR_REPLACEMENT {
    ctx.unique("hostname-char-replacement", ctx.loc2pos(@1));
    ctx.enter(ctx.NO_KEYWORD);
} COLON STRING {
    ElementPtr s(new StringElement($4, ctx.loc2pos(@4)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
};

store_extended_info: STORE_EXTENDED_INFO COLON BOOLEAN {
    ctx.unique("store-extended-info", ctx.loc2pos(@1));
    ElementPtr b(new BoolElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("store-extended-info", b);
};

statistic_default_sample_count: STATISTIC_DEFAULT_SAMPLE_COUNT COLON INTEGER {
    ctx.unique("statistic-default-sample-count", ctx.loc2pos(@1));
    ElementPtr count(new IntElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("statistic-default-sample-count", count);
};

statistic_default_sample_age: STATISTIC_DEFAULT_SAMPLE_AGE COLON INTEGER {
    ctx.unique("statistic-default-sample-age", ctx.loc2pos(@1));
    ElementPtr age(new IntElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("statistic-default-sample-age", age);
};

server_tag: SERVER_TAG {
    ctx.unique("server-tag", ctx.loc2pos(@1));
    ctx.enter(ctx.NO_KEYWORD);
} COLON STRING {
    ElementPtr stag(new StringElement($4, ctx.loc2pos(@4)));
    ctx.stack_.back()->set("server-tag", stag);
    ctx.leave();
};

parked_packet_limit: PARKED_PACKET_LIMIT COLON INTEGER {
    ctx.unique("parked-packet-limit", ctx.loc2pos(@1));
    ElementPtr ppl(new IntElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("parked-packet-limit", ppl);
};

allocator: ALLOCATOR {
    ctx.unique("allocator", ctx.loc2pos(@1));
    ctx.enter(ctx.NO_KEYWORD);
} COLON STRING {
    ElementPtr al(new StringElement($4, ctx.loc2pos(@4)));
    ctx.stack_.back()->set("allocator", al);
    ctx.leave();
};

pd_allocator: PD_ALLOCATOR {
    ctx.unique("pd-allocator", ctx.loc2pos(@1));
    ctx.enter(ctx.NO_KEYWORD);
} COLON STRING {
    ElementPtr al(new StringElement($4, ctx.loc2pos(@4)));
    ctx.stack_.back()->set("pd-allocator", al);
    ctx.leave();
};

early_global_reservations_lookup: EARLY_GLOBAL_RESERVATIONS_LOOKUP COLON BOOLEAN {
    ctx.unique("early-global-reservations-lookup", ctx.loc2pos(@1));
    ElementPtr early(new BoolElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("early-global-reservations-lookup", early);
};

ip_reservations_unique: IP_RESERVATIONS_UNIQUE COLON BOOLEAN {
    ctx.unique("ip-reservations-unique", ctx.loc2pos(@1));
    ElementPtr unique(new BoolElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("ip-reservations-unique", unique);
};

reservations_lookup_first: RESERVATIONS_LOOKUP_FIRST COLON BOOLEAN {
    ctx.unique("reservations-lookup-first", ctx.loc2pos(@1));
    ElementPtr first(new BoolElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("reservations-lookup-first", first);
};

interfaces_config: INTERFACES_CONFIG {
    ctx.unique("interfaces-config", ctx.loc2pos(@1));
    ElementPtr i(new MapElement(ctx.loc2pos(@1)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
} COLON LCURLY_BRACKET interfaces_config_params RCURLY_BRACKET {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
};

sub_interfaces6: LCURLY_BRACKET {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(@1)));
    ctx.stack_.push_back(m);
} interfaces_config_params RCURLY_BRACKET {
    // No interfaces config param is required
    // parsing completed
};

interfaces_config_params: interfaces_config_param
                        | interfaces_config_params COMMA interfaces_config_param
                        | interfaces_config_params COMMA {
                            ctx.warnAboutExtraCommas(@2);
                            }
                        ;

interfaces_config_param: interfaces_list
                       | re_detect
                       | service_sockets_require_all
                       | service_sockets_retry_wait_time
                       | service_sockets_max_retries
                       | user_context
                       | comment
                       | unknown_map_entry
                       ;

interfaces_list: INTERFACES {
    ctx.unique("interfaces", ctx.loc2pos(@1));
    ElementPtr l(new ListElement(ctx.loc2pos(@1)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
} COLON list_strings {
    ctx.stack_.pop_back();
    ctx.leave();
};

re_detect: RE_DETECT COLON BOOLEAN {
    ctx.unique("re-detect", ctx.loc2pos(@1));
    ElementPtr b(new BoolElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("re-detect", b);
};

service_sockets_require_all: SERVICE_SOCKETS_REQUIRE_ALL COLON BOOLEAN {
    ctx.unique("service-sockets-require-all", ctx.loc2pos(@1));
    ElementPtr b(new BoolElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("service-sockets-require-all", b);
};

service_sockets_retry_wait_time: SERVICE_SOCKETS_RETRY_WAIT_TIME COLON INTEGER {
    ctx.unique("service-sockets-retry-wait-time", ctx.loc2pos(@1));
    ElementPtr n(new IntElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("service-sockets-retry-wait-time", n);
};

service_sockets_max_retries: SERVICE_SOCKETS_MAX_RETRIES COLON INTEGER {
    ctx.unique("service-sockets-max-retries", ctx.loc2pos(@1));
    ElementPtr n(new IntElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("service-sockets-max-retries", n);
};

lease_database: LEASE_DATABASE {
    ctx.unique("lease-database", ctx.loc2pos(@1));
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

hosts_database: HOSTS_DATABASE {
    ctx.unique("hosts-database", ctx.loc2pos(@1));
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
    ctx.unique("hosts-databases", ctx.loc2pos(@1));
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
                       | not_empty_database_list COMMA {
                           ctx.warnAboutExtraCommas(@2);
                           }
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
                   | database_map_params COMMA {
                       ctx.warnAboutExtraCommas(@2);
                       }
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
                  | read_timeout
                  | write_timeout
                  | tcp_user_timeout
                  | max_reconnect_tries
                  | reconnect_wait_time
                  | on_fail
                  | max_row_errors
                  | trust_anchor
                  | cert_file
                  | key_file
                  | cipher_list
                  | unknown_map_entry
                  ;

database_type: TYPE {
    ctx.unique("type", ctx.loc2pos(@1));
    ctx.enter(ctx.DATABASE_TYPE);
} COLON db_type {
    ctx.stack_.back()->set("type", $4);
    ctx.leave();
};

db_type: MEMFILE { $$ = ElementPtr(new StringElement("memfile", ctx.loc2pos(@1))); }
       | MYSQL { $$ = ElementPtr(new StringElement("mysql", ctx.loc2pos(@1))); }
       | POSTGRESQL { $$ = ElementPtr(new StringElement("postgresql", ctx.loc2pos(@1))); }
       ;

user: USER {
    ctx.unique("user", ctx.loc2pos(@1));
    ctx.enter(ctx.NO_KEYWORD);
} COLON STRING {
    ElementPtr user(new StringElement($4, ctx.loc2pos(@4)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
};

password: PASSWORD {
    ctx.unique("password", ctx.loc2pos(@1));
    ctx.enter(ctx.NO_KEYWORD);
} COLON STRING {
    ElementPtr pwd(new StringElement($4, ctx.loc2pos(@4)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
};

host: HOST {
    ctx.unique("host", ctx.loc2pos(@1));
    ctx.enter(ctx.NO_KEYWORD);
} COLON STRING {
    ElementPtr h(new StringElement($4, ctx.loc2pos(@4)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
};

port: PORT COLON INTEGER {
    ctx.unique("port", ctx.loc2pos(@1));
    ElementPtr p(new IntElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("port", p);
};

name: NAME {
    ctx.unique("name", ctx.loc2pos(@1));
    ctx.enter(ctx.NO_KEYWORD);
} COLON STRING {
    ElementPtr name(new StringElement($4, ctx.loc2pos(@4)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
};

persist: PERSIST COLON BOOLEAN {
    ctx.unique("persist", ctx.loc2pos(@1));
    ElementPtr n(new BoolElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("persist", n);
};

lfc_interval: LFC_INTERVAL COLON INTEGER {
    ctx.unique("lfc-interval", ctx.loc2pos(@1));
    ElementPtr n(new IntElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("lfc-interval", n);
};

readonly: READONLY COLON BOOLEAN {
    ctx.unique("readonly", ctx.loc2pos(@1));
    ElementPtr n(new BoolElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("readonly", n);
};

connect_timeout: CONNECT_TIMEOUT COLON INTEGER {
    ctx.unique("connect-timeout", ctx.loc2pos(@1));
    ElementPtr n(new IntElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("connect-timeout", n);
};

read_timeout: READ_TIMEOUT COLON INTEGER {
    ctx.unique("read-timeout", ctx.loc2pos(@1));
    ElementPtr n(new IntElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("read-timeout", n);
};

write_timeout: WRITE_TIMEOUT COLON INTEGER {
    ctx.unique("write-timeout", ctx.loc2pos(@1));
    ElementPtr n(new IntElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("write-timeout", n);
};

tcp_user_timeout: TCP_USER_TIMEOUT COLON INTEGER {
    ctx.unique("tcp-user-timeout", ctx.loc2pos(@1));
    ElementPtr n(new IntElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("tcp-user-timeout", n);
};


reconnect_wait_time: RECONNECT_WAIT_TIME COLON INTEGER {
    ctx.unique("reconnect-wait-time", ctx.loc2pos(@1));
    ElementPtr n(new IntElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
};

on_fail: ON_FAIL {
    ctx.unique("on-fail", ctx.loc2pos(@1));
    ctx.enter(ctx.DATABASE_ON_FAIL);
} COLON on_fail_mode {
    ctx.stack_.back()->set("on-fail", $4);
    ctx.leave();
};

on_fail_mode: STOP_RETRY_EXIT { $$ = ElementPtr(new StringElement("stop-retry-exit", ctx.loc2pos(@1))); }
            | SERVE_RETRY_EXIT { $$ = ElementPtr(new StringElement("serve-retry-exit", ctx.loc2pos(@1))); }
            | SERVE_RETRY_CONTINUE { $$ = ElementPtr(new StringElement("serve-retry-continue", ctx.loc2pos(@1))); }
            ;

max_row_errors: MAX_ROW_ERRORS COLON INTEGER {
    ctx.unique("max-row-errors", ctx.loc2pos(@1));
    ElementPtr n(new IntElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("max-row-errors", n);
};

max_reconnect_tries: MAX_RECONNECT_TRIES COLON INTEGER {
    ctx.unique("max-reconnect-tries", ctx.loc2pos(@1));
    ElementPtr n(new IntElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
};

trust_anchor: TRUST_ANCHOR {
    ctx.unique("trust-anchor", ctx.loc2pos(@1));
    ctx.enter(ctx.NO_KEYWORD);
} COLON STRING {
    ElementPtr ca(new StringElement($4, ctx.loc2pos(@4)));
    ctx.stack_.back()->set("trust-anchor", ca);
    ctx.leave();
};

cert_file: CERT_FILE {
    ctx.unique("cert-file", ctx.loc2pos(@1));
    ctx.enter(ctx.NO_KEYWORD);
} COLON STRING {
    ElementPtr cert(new StringElement($4, ctx.loc2pos(@4)));
    ctx.stack_.back()->set("cert-file", cert);
    ctx.leave();
};

key_file: KEY_FILE {
    ctx.unique("key-file", ctx.loc2pos(@1));
    ctx.enter(ctx.NO_KEYWORD);
} COLON STRING {
    ElementPtr key(new StringElement($4, ctx.loc2pos(@4)));
    ctx.stack_.back()->set("key-file", key);
    ctx.leave();
};

cipher_list: CIPHER_LIST {
    ctx.unique("cipher-list", ctx.loc2pos(@1));
    ctx.enter(ctx.NO_KEYWORD);
} COLON STRING {
    ElementPtr cl(new StringElement($4, ctx.loc2pos(@4)));
    ctx.stack_.back()->set("cipher-list", cl);
    ctx.leave();
};

sanity_checks: SANITY_CHECKS {
    ctx.unique("sanity-checks", ctx.loc2pos(@1));
    ElementPtr m(new MapElement(ctx.loc2pos(@1)));
    ctx.stack_.back()->set("sanity-checks", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SANITY_CHECKS);
} COLON LCURLY_BRACKET sanity_checks_params RCURLY_BRACKET {
    ctx.stack_.pop_back();
    ctx.leave();
};

sanity_checks_params: sanity_checks_param
                    | sanity_checks_params COMMA sanity_checks_param
                    | sanity_checks_params COMMA {
                        ctx.warnAboutExtraCommas(@2);
                        }
                    ;

sanity_checks_param: lease_checks
                   | extended_info_checks
                   ;

lease_checks: LEASE_CHECKS {
    ctx.unique("lease-checks", ctx.loc2pos(@1));
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

extended_info_checks: EXTENDED_INFO_CHECKS {
    ctx.unique("extended-info-checks", ctx.loc2pos(@1));
    ctx.enter(ctx.NO_KEYWORD);
} COLON STRING {

    if ( (string($4) == "none") ||
         (string($4) == "fix") ||
         (string($4) == "strict") ||
         (string($4) == "pedantic")) {
        ElementPtr user(new StringElement($4, ctx.loc2pos(@4)));
        ctx.stack_.back()->set("extended-info-checks", user);
        ctx.leave();
    } else {
        error(@4, "Unsupported 'extended-info-checks value: " + string($4) +
              ", supported values are: none, fix, strict, pedantic");
    }
}

mac_sources: MAC_SOURCES {
    ctx.unique("mac-sources", ctx.loc2pos(@1));
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
                | mac_sources_list COMMA {
                    ctx.warnAboutExtraCommas(@2);
                    }
                ;

mac_sources_value: duid_id
                 | string_id
                 ;

duid_id: DUID {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(@1)));
    ctx.stack_.back()->add(duid);
};

string_id: STRING {
    ElementPtr duid(new StringElement($1, ctx.loc2pos(@1)));
    ctx.stack_.back()->add(duid);
};

host_reservation_identifiers: HOST_RESERVATION_IDENTIFIERS {
    ctx.unique("host-reservation-identifiers", ctx.loc2pos(@1));
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
    | host_reservation_identifiers_list COMMA {
        ctx.warnAboutExtraCommas(@2);
        }
    ;

host_reservation_identifier: duid_id
                           | hw_address_id
                           | flex_id
                           ;

hw_address_id: HW_ADDRESS {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(@1)));
    ctx.stack_.back()->add(hwaddr);
};

flex_id: FLEX_ID {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(@1)));
    ctx.stack_.back()->add(flex_id);
};

// list_content below accepts any value when options are by name (string)
// or by code (number)
relay_supplied_options: RELAY_SUPPLIED_OPTIONS {
    ctx.unique("relay-supplied-options", ctx.loc2pos(@1));
    ElementPtr l(new ListElement(ctx.loc2pos(@1)));
    ctx.stack_.back()->set("relay-supplied-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
} COLON LSQUARE_BRACKET list_content RSQUARE_BRACKET {
    ctx.stack_.pop_back();
    ctx.leave();
};

// --- multi-threading ------------------------------------------------

dhcp_multi_threading: DHCP_MULTI_THREADING {
    ctx.unique("multi-threading", ctx.loc2pos(@1));
    ElementPtr mt(new MapElement(ctx.loc2pos(@1)));
    ctx.stack_.back()->set("multi-threading", mt);
    ctx.stack_.push_back(mt);
    ctx.enter(ctx.DHCP_MULTI_THREADING);
} COLON LCURLY_BRACKET multi_threading_params RCURLY_BRACKET {
    // The enable parameter is required.
    ctx.require("enable-multi-threading", ctx.loc2pos(@4), ctx.loc2pos(@6));
    ctx.stack_.pop_back();
    ctx.leave();
};

multi_threading_params: multi_threading_param
                      | multi_threading_params COMMA multi_threading_param
                      | multi_threading_params COMMA {
                          ctx.warnAboutExtraCommas(@2);
                          }
                      ;

multi_threading_param: enable_multi_threading
                     | thread_pool_size
                     | packet_queue_size
                     | user_context
                     | comment
                     | unknown_map_entry
                     ;

enable_multi_threading: ENABLE_MULTI_THREADING COLON BOOLEAN {
    ctx.unique("enable-multi-threading", ctx.loc2pos(@1));
    ElementPtr b(new BoolElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("enable-multi-threading", b);
};

thread_pool_size: THREAD_POOL_SIZE COLON INTEGER {
    ctx.unique("thread-pool-size", ctx.loc2pos(@1));
    ElementPtr prf(new IntElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("thread-pool-size", prf);
};

packet_queue_size: PACKET_QUEUE_SIZE COLON INTEGER {
    ctx.unique("packet-queue-size", ctx.loc2pos(@1));
    ElementPtr prf(new IntElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("packet-queue-size", prf);
};

hooks_libraries: HOOKS_LIBRARIES {
    ctx.unique("hooks-libraries", ctx.loc2pos(@1));
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
    | not_empty_hooks_libraries_list COMMA {
        ctx.warnAboutExtraCommas(@2);
        }
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
            | hooks_params COMMA {
                ctx.warnAboutExtraCommas(@2);
                }
            | unknown_map_entry
            ;

hooks_param: library
           | parameters
           ;

library: LIBRARY {
    ctx.unique("library", ctx.loc2pos(@1));
    ctx.enter(ctx.NO_KEYWORD);
} COLON STRING {
    ElementPtr lib(new StringElement($4, ctx.loc2pos(@4)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
};

parameters: PARAMETERS {
    ctx.unique("parameters", ctx.loc2pos(@1));
    ctx.enter(ctx.NO_KEYWORD);
} COLON map_value {
    ctx.stack_.back()->set("parameters", $4);
    ctx.leave();
};

// --- expired-leases-processing ------------------------
expired_leases_processing: EXPIRED_LEASES_PROCESSING {
    ctx.unique("expired-leases-processing", ctx.loc2pos(@1));
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
                     | expired_leases_params COMMA {
                         ctx.warnAboutExtraCommas(@2);
                         }
                     ;

expired_leases_param: reclaim_timer_wait_time
                    | flush_reclaimed_timer_wait_time
                    | hold_reclaimed_time
                    | max_reclaim_leases
                    | max_reclaim_time
                    | unwarned_reclaim_cycles
                    ;

reclaim_timer_wait_time: RECLAIM_TIMER_WAIT_TIME COLON INTEGER {
    ctx.unique("reclaim-timer-wait-time", ctx.loc2pos(@1));
    ElementPtr value(new IntElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
};

flush_reclaimed_timer_wait_time: FLUSH_RECLAIMED_TIMER_WAIT_TIME COLON INTEGER {
    ctx.unique("flush-reclaimed-timer-wait-time", ctx.loc2pos(@1));
    ElementPtr value(new IntElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
};

hold_reclaimed_time: HOLD_RECLAIMED_TIME COLON INTEGER {
    ctx.unique("hold-reclaimed-time", ctx.loc2pos(@1));
    ElementPtr value(new IntElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
};

max_reclaim_leases: MAX_RECLAIM_LEASES COLON INTEGER {
    ctx.unique("max-reclaim-leases", ctx.loc2pos(@1));
    ElementPtr value(new IntElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
};

max_reclaim_time: MAX_RECLAIM_TIME COLON INTEGER {
    ctx.unique("max-reclaim-time", ctx.loc2pos(@1));
    ElementPtr value(new IntElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("max-reclaim-time", value);
};

unwarned_reclaim_cycles: UNWARNED_RECLAIM_CYCLES COLON INTEGER {
    ctx.unique("unwarned-reclaim-cycles", ctx.loc2pos(@1));
    ElementPtr value(new IntElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
};

// --- subnet6 ------------------------------------------
// This defines subnet6 as a list of maps.
// "subnet6": [ ... ]
subnet6_list: SUBNET6 {
    ctx.unique("subnet6", ctx.loc2pos(@1));
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
                      | not_empty_subnet6_list COMMA {
                          ctx.warnAboutExtraCommas(@2);
                          }
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

    // The subnet subnet6 parameter is required
    ctx.require("subnet", ctx.loc2pos(@1), ctx.loc2pos(@4));
    ctx.stack_.pop_back();
};

sub_subnet6: LCURLY_BRACKET {
    // Parse the subnet6 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(@1)));
    ctx.stack_.push_back(m);
} subnet6_params RCURLY_BRACKET {
    // The subnet subnet6 parameter is required
    ctx.require("subnet", ctx.loc2pos(@1), ctx.loc2pos(@4));
    // parsing completed
};

// This defines that subnet can have one or more parameters.
subnet6_params: subnet6_param
              | subnet6_params COMMA subnet6_param
              | subnet6_params COMMA {
                  ctx.warnAboutExtraCommas(@2);
                  }
              ;

// This defines a list of allowed parameters for each subnet.
subnet6_param: preferred_lifetime
             | min_preferred_lifetime
             | max_preferred_lifetime
             | valid_lifetime
             | min_valid_lifetime
             | max_valid_lifetime
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
             | require_client_classes
             | reservations
             | reservation_mode
             | reservations_global
             | reservations_in_subnet
             | reservations_out_of_pool
             | relay
             | user_context
             | comment
             | calculate_tee_times
             | t1_percent
             | t2_percent
             | cache_threshold
             | cache_max_age
             | hostname_char_set
             | hostname_char_replacement
             | ddns_send_updates
             | ddns_override_no_update
             | ddns_override_client_update
             | ddns_replace_client_name
             | ddns_generated_prefix
             | ddns_qualifying_suffix
             | ddns_update_on_renew
             | ddns_use_conflict_resolution
             | ddns_ttl_percent
             | store_extended_info
             | allocator
             | pd_allocator
             | unknown_map_entry
             ;

subnet: SUBNET {
    ctx.unique("subnet", ctx.loc2pos(@1));
    ctx.enter(ctx.NO_KEYWORD);
} COLON STRING {
    ElementPtr subnet(new StringElement($4, ctx.loc2pos(@4)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
};

interface: INTERFACE {
    ctx.unique("interface", ctx.loc2pos(@1));
    ctx.enter(ctx.NO_KEYWORD);
} COLON STRING {
    ElementPtr iface(new StringElement($4, ctx.loc2pos(@4)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
};

interface_id: INTERFACE_ID {
    ctx.unique("interface-id", ctx.loc2pos(@1));
    ctx.enter(ctx.NO_KEYWORD);
} COLON STRING {
    ElementPtr iface(new StringElement($4, ctx.loc2pos(@4)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
};

client_class: CLIENT_CLASS {
    ctx.unique("client-class", ctx.loc2pos(@1));
    ctx.enter(ctx.NO_KEYWORD);
} COLON STRING {
    ElementPtr cls(new StringElement($4, ctx.loc2pos(@4)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
};

require_client_classes: REQUIRE_CLIENT_CLASSES {
    ctx.unique("require-client-classes", ctx.loc2pos(@1));
    ElementPtr c(new ListElement(ctx.loc2pos(@1)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
} COLON list_strings {
    ctx.stack_.pop_back();
    ctx.leave();
};

reservations_global: RESERVATIONS_GLOBAL COLON BOOLEAN {
    ctx.unique("reservations-global", ctx.loc2pos(@1));
    ElementPtr b(new BoolElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("reservations-global", b);
};

reservations_in_subnet: RESERVATIONS_IN_SUBNET COLON BOOLEAN {
    ctx.unique("reservations-in-subnet", ctx.loc2pos(@1));
    ElementPtr b(new BoolElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("reservations-in-subnet", b);
};

reservations_out_of_pool: RESERVATIONS_OUT_OF_POOL COLON BOOLEAN {
    ctx.unique("reservations-out-of-pool", ctx.loc2pos(@1));
    ElementPtr b(new BoolElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("reservations-out-of-pool", b);
};

reservation_mode: RESERVATION_MODE {
    ctx.unique("reservation-mode", ctx.loc2pos(@1));
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
    ctx.unique("id", ctx.loc2pos(@1));
    ElementPtr id(new IntElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("id", id);
};

rapid_commit: RAPID_COMMIT COLON BOOLEAN {
    ctx.unique("rapid-commit", ctx.loc2pos(@1));
    ElementPtr rc(new BoolElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("rapid-commit", rc);
};

// ---- shared-networks ---------------------

shared_networks: SHARED_NETWORKS {
    ctx.unique("shared-networks", ctx.loc2pos(@1));
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
                    | shared_networks_list COMMA {
                        ctx.warnAboutExtraCommas(@2);
                        }
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
                     | shared_network_params COMMA {
                         ctx.warnAboutExtraCommas(@2);
                         }
                     ;

shared_network_param: name
                    | subnet6_list
                    | interface
                    | interface_id
                    | renew_timer
                    | rebind_timer
                    | option_data_list
                    | relay
                    | reservation_mode
                    | reservations_global
                    | reservations_in_subnet
                    | reservations_out_of_pool
                    | client_class
                    | require_client_classes
                    | preferred_lifetime
                    | min_preferred_lifetime
                    | max_preferred_lifetime
                    | rapid_commit
                    | valid_lifetime
                    | min_valid_lifetime
                    | max_valid_lifetime
                    | user_context
                    | comment
                    | calculate_tee_times
                    | t1_percent
                    | t2_percent
                    | cache_threshold
                    | cache_max_age
                    | hostname_char_set
                    | hostname_char_replacement
                    | ddns_send_updates
                    | ddns_override_no_update
                    | ddns_override_client_update
                    | ddns_replace_client_name
                    | ddns_generated_prefix
                    | ddns_qualifying_suffix
                    | ddns_update_on_renew
                    | ddns_use_conflict_resolution
                    | ddns_ttl_percent
                    | store_extended_info
                    | allocator
                    | pd_allocator
                    | unknown_map_entry
                    ;

// ---- option-def --------------------------

// This defines the "option-def": [ ... ] entry that may appear
// at a global option.
option_def_list: OPTION_DEF {
    ctx.unique("option-def", ctx.loc2pos(@1));
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
                         | not_empty_option_def_list COMMA {
                             ctx.warnAboutExtraCommas(@2);
                             }
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
                           | not_empty_option_def_params COMMA {
                               ctx.warnAboutExtraCommas(@2);
                               }
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
    ctx.unique("code", ctx.loc2pos(@1));
    ElementPtr code(new IntElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("code", code);
};

option_def_code: code;

option_def_type: TYPE {
    ctx.unique("type", ctx.loc2pos(@1));
    ctx.enter(ctx.NO_KEYWORD);
} COLON STRING {
    ElementPtr prf(new StringElement($4, ctx.loc2pos(@4)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
};

option_def_record_types: RECORD_TYPES {
    ctx.unique("record-types", ctx.loc2pos(@1));
    ctx.enter(ctx.NO_KEYWORD);
} COLON STRING {
    ElementPtr rtypes(new StringElement($4, ctx.loc2pos(@4)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
};

space: SPACE {
    ctx.unique("space", ctx.loc2pos(@1));
    ctx.enter(ctx.NO_KEYWORD);
} COLON STRING {
    ElementPtr space(new StringElement($4, ctx.loc2pos(@4)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
};

option_def_space: space;

option_def_encapsulate: ENCAPSULATE {
    ctx.unique("encapsulate", ctx.loc2pos(@1));
    ctx.enter(ctx.NO_KEYWORD);
} COLON STRING {
    ElementPtr encap(new StringElement($4, ctx.loc2pos(@4)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
};

option_def_array: ARRAY COLON BOOLEAN {
    ctx.unique("array", ctx.loc2pos(@1));
    ElementPtr array(new BoolElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("array", array);
};

// ---- option-data --------------------------

// This defines the "option-data": [ ... ] entry that may appear
// in several places, but most notably in subnet6 entries.
option_data_list: OPTION_DATA {
    ctx.unique("option-data", ctx.loc2pos(@1));
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
                          | not_empty_option_data_list COMMA {
                              ctx.warnAboutExtraCommas(@2);
                              }
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
    | not_empty_option_data_params COMMA {
        ctx.warnAboutExtraCommas(@2);
        }
    ;

// Each single option-data parameter can be one of the following
// expressions.
option_data_param: option_data_name
                 | option_data_data
                 | option_data_code
                 | option_data_space
                 | option_data_csv_format
                 | option_data_always_send
                 | option_data_never_send
                 | user_context
                 | comment
                 | unknown_map_entry
                 ;

option_data_name: name;

option_data_data: DATA {
    ctx.unique("data", ctx.loc2pos(@1));
    ctx.enter(ctx.NO_KEYWORD);
} COLON STRING {
    ElementPtr data(new StringElement($4, ctx.loc2pos(@4)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
};

option_data_code: code;

option_data_space: space;

option_data_csv_format: CSV_FORMAT COLON BOOLEAN {
    ctx.unique("csv-format", ctx.loc2pos(@1));
    ElementPtr csv(new BoolElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("csv-format", csv);
};

option_data_always_send: ALWAYS_SEND COLON BOOLEAN {
    ctx.unique("always-send", ctx.loc2pos(@1));
    ElementPtr persist(new BoolElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("always-send", persist);
};

option_data_never_send: NEVER_SEND COLON BOOLEAN {
    ctx.unique("never-send", ctx.loc2pos(@1));
    ElementPtr cancel(new BoolElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("never-send", cancel);
};

// ---- pools ------------------------------------

// This defines the "pools": [ ... ] entry that may appear in subnet6.
pools_list: POOLS {
    ctx.unique("pools", ctx.loc2pos(@1));
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
                    | not_empty_pools_list COMMA {
                        ctx.warnAboutExtraCommas(@2);
                        }
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

sub_pool6: LCURLY_BRACKET {
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
           | pool_params COMMA {
               ctx.warnAboutExtraCommas(@2);
               }
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
    ctx.unique("pool", ctx.loc2pos(@1));
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

// --- pd-pools ----------------------------------------------
pd_pools_list: PD_POOLS {
    ctx.unique("pd-pools", ctx.loc2pos(@1));
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
                       | not_empty_pd_pools_list COMMA {
                           ctx.warnAboutExtraCommas(@2);
                           }
                       ;

pd_pool_entry: LCURLY_BRACKET {
    ElementPtr m(new MapElement(ctx.loc2pos(@1)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
} pd_pool_params RCURLY_BRACKET {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(@1), ctx.loc2pos(@4));
    ctx.require("prefix-len", ctx.loc2pos(@1), ctx.loc2pos(@4));
    ctx.require("delegated-len", ctx.loc2pos(@1), ctx.loc2pos(@4));
    ctx.stack_.pop_back();
};

sub_pd_pool: LCURLY_BRACKET {
    // Parse the pd-pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(@1)));
    ctx.stack_.push_back(m);
} pd_pool_params RCURLY_BRACKET {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(@1), ctx.loc2pos(@4));
    ctx.require("prefix-len", ctx.loc2pos(@1), ctx.loc2pos(@4));
    ctx.require("delegated-len", ctx.loc2pos(@1), ctx.loc2pos(@4));
    // parsing completed
};

pd_pool_params: pd_pool_param
              | pd_pool_params COMMA pd_pool_param
              | pd_pool_params COMMA {
                  ctx.warnAboutExtraCommas(@2);
                  }
              ;

pd_pool_param: pd_prefix
             | pd_prefix_len
             | pd_delegated_len
             | option_data_list
             | client_class
             | require_client_classes
             | excluded_prefix
             | excluded_prefix_len
             | user_context
             | comment
             | unknown_map_entry
             ;

pd_prefix: PREFIX {
    ctx.unique("prefix", ctx.loc2pos(@1));
    ctx.enter(ctx.NO_KEYWORD);
} COLON STRING {
    ElementPtr prf(new StringElement($4, ctx.loc2pos(@4)));
    ctx.stack_.back()->set("prefix", prf);
    ctx.leave();
};

pd_prefix_len: PREFIX_LEN COLON INTEGER {
    ctx.unique("prefix-len", ctx.loc2pos(@1));
    ElementPtr prf(new IntElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("prefix-len", prf);
};

excluded_prefix: EXCLUDED_PREFIX {
    ctx.unique("excluded-prefix", ctx.loc2pos(@1));
    ctx.enter(ctx.NO_KEYWORD);
} COLON STRING {
    ElementPtr prf(new StringElement($4, ctx.loc2pos(@4)));
    ctx.stack_.back()->set("excluded-prefix", prf);
    ctx.leave();
};

excluded_prefix_len: EXCLUDED_PREFIX_LEN COLON INTEGER {
    ctx.unique("excluded-prefix-len", ctx.loc2pos(@1));
    ElementPtr prf(new IntElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("excluded-prefix-len", prf);
};

pd_delegated_len: DELEGATED_LEN COLON INTEGER {
    ctx.unique("delegated-len", ctx.loc2pos(@1));
    ElementPtr deleg(new IntElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("delegated-len", deleg);
};

// --- end of pd-pools ---------------------------------------

// --- reservations ------------------------------------------
reservations: RESERVATIONS {
    ctx.unique("reservations", ctx.loc2pos(@1));
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
                           | not_empty_reservations_list COMMA {
                               ctx.warnAboutExtraCommas(@2);
                               }
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
    | not_empty_reservation_params COMMA {
        ctx.warnAboutExtraCommas(@2);
        }
    ;

/// @todo probably need to add mac-address as well here
reservation_param: duid
                 | reservation_client_classes
                 | ip_addresses
                 | prefixes
                 | hw_address
                 | hostname
                 | flex_id_value
                 | option_data_list
                 | user_context
                 | comment
                 | unknown_map_entry
                 ;

ip_addresses: IP_ADDRESSES {
    ctx.unique("ip-addresses", ctx.loc2pos(@1));
    ElementPtr l(new ListElement(ctx.loc2pos(@1)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
} COLON list_strings {
    ctx.stack_.pop_back();
    ctx.leave();
};

prefixes: PREFIXES {
    ctx.unique("prefixes", ctx.loc2pos(@1));
    ElementPtr l(new ListElement(ctx.loc2pos(@1)));
    ctx.stack_.back()->set("prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
} COLON list_strings {
    ctx.stack_.pop_back();
    ctx.leave();
};

duid: DUID {
    ctx.unique("duid", ctx.loc2pos(@1));
    ctx.enter(ctx.NO_KEYWORD);
} COLON STRING {
    ElementPtr d(new StringElement($4, ctx.loc2pos(@4)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
};

hw_address: HW_ADDRESS {
    ctx.unique("hw-address", ctx.loc2pos(@1));
    ctx.enter(ctx.NO_KEYWORD);
} COLON STRING {
    ElementPtr hw(new StringElement($4, ctx.loc2pos(@4)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
};

hostname: HOSTNAME {
    ctx.unique("hostname", ctx.loc2pos(@1));
    ctx.enter(ctx.NO_KEYWORD);
} COLON STRING {
    ElementPtr host(new StringElement($4, ctx.loc2pos(@4)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
};

flex_id_value: FLEX_ID {
    ctx.unique("flex-id", ctx.loc2pos(@1));
    ctx.enter(ctx.NO_KEYWORD);
} COLON STRING {
    ElementPtr hw(new StringElement($4, ctx.loc2pos(@4)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
};

reservation_client_classes: CLIENT_CLASSES {
    ctx.unique("client-classes", ctx.loc2pos(@1));
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
    ctx.unique("relay", ctx.loc2pos(@1));
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

ip_address: IP_ADDRESS {
    ctx.unique("ip-address", ctx.loc2pos(@1));
    ctx.enter(ctx.NO_KEYWORD);
} COLON STRING {
    ElementPtr addr(new StringElement($4, ctx.loc2pos(@4)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
};

// --- end of relay definitions ------------------------------

// --- client classes ----------------------------------------
client_classes: CLIENT_CLASSES {
    ctx.unique("client-classes", ctx.loc2pos(@1));
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
                   | client_classes_list COMMA {
                       ctx.warnAboutExtraCommas(@2);
                       }
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
    | not_empty_client_class_params COMMA {
        ctx.warnAboutExtraCommas(@2);
        }
    ;

client_class_param: client_class_name
                  | client_class_test
                  | client_class_template_test
                  | only_if_required
                  | option_data_list
                  | user_context
                  | comment
                  | preferred_lifetime
                  | min_preferred_lifetime
                  | max_preferred_lifetime
                  | valid_lifetime
                  | min_valid_lifetime
                  | max_valid_lifetime
                  | unknown_map_entry
                  ;

client_class_name: name;

client_class_test: TEST {
    ctx.unique("test", ctx.loc2pos(@1));
    ctx.enter(ctx.NO_KEYWORD);
} COLON STRING {
    ElementPtr test(new StringElement($4, ctx.loc2pos(@4)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
};

client_class_template_test: TEMPLATE_TEST {
    ctx.unique("template-test", ctx.loc2pos(@1));
    ctx.enter(ctx.NO_KEYWORD);
} COLON STRING {
    ElementPtr template_test(new StringElement($4, ctx.loc2pos(@4)));
    ctx.stack_.back()->set("template-test", template_test);
    ctx.leave();
};

only_if_required: ONLY_IF_REQUIRED COLON BOOLEAN {
    ctx.unique("only-if-required", ctx.loc2pos(@1));
    ElementPtr b(new BoolElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("only-if-required", b);
};

// --- end of client classes ---------------------------------

// --- server-id ---------------------------------------------
server_id: SERVER_ID {
    ctx.unique("server-id", ctx.loc2pos(@1));
    ElementPtr m(new MapElement(ctx.loc2pos(@1)));
    ctx.stack_.back()->set("server-id", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER_ID);
} COLON LCURLY_BRACKET server_id_params RCURLY_BRACKET {
    // The type parameter is required.
    ctx.require("type", ctx.loc2pos(@4), ctx.loc2pos(@6));
    ctx.stack_.pop_back();
    ctx.leave();
};

server_id_params: server_id_param
                | server_id_params COMMA server_id_param
                | server_id_params COMMA {
                    ctx.warnAboutExtraCommas(@2);
                    }
                ;

server_id_param: server_id_type
               | identifier
               | time
               | htype
               | enterprise_id
               | persist
               | user_context
               | comment
               | unknown_map_entry
               ;

server_id_type: TYPE {
    ctx.unique("type", ctx.loc2pos(@1));
    ctx.enter(ctx.DUID_TYPE);
} COLON duid_type {
    ctx.stack_.back()->set("type", $4);
    ctx.leave();
};

duid_type: LLT { $$ = ElementPtr(new StringElement("LLT", ctx.loc2pos(@1))); }
         | EN { $$ = ElementPtr(new StringElement("EN", ctx.loc2pos(@1))); }
         | LL { $$ = ElementPtr(new StringElement("LL", ctx.loc2pos(@1))); }
         ;

htype: HTYPE COLON INTEGER {
    ctx.unique("htype", ctx.loc2pos(@1));
    ElementPtr htype(new IntElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("htype", htype);
};

identifier: IDENTIFIER {
    ctx.unique("identifier", ctx.loc2pos(@1));
    ctx.enter(ctx.NO_KEYWORD);
} COLON STRING {
    ElementPtr id(new StringElement($4, ctx.loc2pos(@4)));
    ctx.stack_.back()->set("identifier", id);
    ctx.leave();
};

time: TIME COLON INTEGER {
    ctx.unique("time", ctx.loc2pos(@1));
    ElementPtr time(new IntElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("time", time);
};

enterprise_id: ENTERPRISE_ID COLON INTEGER {
    ctx.unique("enterprise-id", ctx.loc2pos(@1));
    ElementPtr time(new IntElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("enterprise-id", time);
};

// --- end of server-id --------------------------------------

dhcp4o6_port: DHCP4O6_PORT COLON INTEGER {
    ctx.unique("dhcp4o6-port", ctx.loc2pos(@1));
    ElementPtr time(new IntElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
};

// --- control socket ----------------------------------------

control_socket: CONTROL_SOCKET {
    ctx.unique("control-socket", ctx.loc2pos(@1));
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
                     | control_socket_params COMMA {
                         ctx.warnAboutExtraCommas(@2);
                         }
                     ;

control_socket_param: socket_type
                    | socket_name
                    | user_context
                    | comment
                    | unknown_map_entry
                    ;

socket_type: SOCKET_TYPE {
    ctx.unique("socket-type", ctx.loc2pos(@1));
    ctx.enter(ctx.NO_KEYWORD);
} COLON STRING {
    ElementPtr stype(new StringElement($4, ctx.loc2pos(@4)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
};

socket_name: SOCKET_NAME {
    ctx.unique("socket-name", ctx.loc2pos(@1));
    ctx.enter(ctx.NO_KEYWORD);
} COLON STRING {
    ElementPtr name(new StringElement($4, ctx.loc2pos(@4)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
};


// --- dhcp-queue-control ---------------------------------------------

dhcp_queue_control: DHCP_QUEUE_CONTROL {
    ctx.unique("dhcp-queue-control", ctx.loc2pos(@1));
    ElementPtr qc(new MapElement(ctx.loc2pos(@1)));
    ctx.stack_.back()->set("dhcp-queue-control", qc);
    ctx.stack_.push_back(qc);
    ctx.enter(ctx.DHCP_QUEUE_CONTROL);
} COLON LCURLY_BRACKET queue_control_params RCURLY_BRACKET {
    // The enable queue parameter is required.
    ctx.require("enable-queue", ctx.loc2pos(@4), ctx.loc2pos(@6));
    ctx.stack_.pop_back();
    ctx.leave();
};

queue_control_params: queue_control_param
                    | queue_control_params COMMA queue_control_param
                    | queue_control_params COMMA {
                        ctx.warnAboutExtraCommas(@2);
                        }
                    ;

queue_control_param: enable_queue
                   | queue_type
                   | capacity
                   | user_context
                   | comment
                   | arbitrary_map_entry
                   ;

enable_queue: ENABLE_QUEUE COLON BOOLEAN {
    ctx.unique("enable-queue", ctx.loc2pos(@1));
    ElementPtr b(new BoolElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("enable-queue", b);
};

queue_type: QUEUE_TYPE {
    ctx.unique("queue-type", ctx.loc2pos(@1));
    ctx.enter(ctx.NO_KEYWORD);
} COLON STRING {
    ElementPtr qt(new StringElement($4, ctx.loc2pos(@4)));
    ctx.stack_.back()->set("queue-type", qt);
    ctx.leave();
};

capacity: CAPACITY COLON INTEGER {
    ctx.unique("capacity", ctx.loc2pos(@1));
    ElementPtr c(new IntElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("capacity", c);
};

arbitrary_map_entry: STRING {
    ctx.unique($1, ctx.loc2pos(@1));
    ctx.enter(ctx.NO_KEYWORD);
} COLON value {
    ctx.stack_.back()->set($1, $4);
    ctx.leave();
};

// --- dhcp ddns ---------------------------------------------

dhcp_ddns: DHCP_DDNS {
    ctx.unique("dhcp-ddns", ctx.loc2pos(@1));
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
                | dhcp_ddns_params COMMA {
                    ctx.warnAboutExtraCommas(@2);
                    }
                ;

dhcp_ddns_param: enable_updates
               | server_ip
               | server_port
               | sender_ip
               | sender_port
               | max_queue_size
               | ncr_protocol
               | ncr_format
               | dep_override_no_update
               | dep_override_client_update
               | dep_replace_client_name
               | dep_generated_prefix
               | dep_qualifying_suffix
               | dep_hostname_char_set
               | dep_hostname_char_replacement
               | user_context
               | comment
               | unknown_map_entry
               ;

enable_updates: ENABLE_UPDATES COLON BOOLEAN {
    ctx.unique("enable-updates", ctx.loc2pos(@1));
    ElementPtr b(new BoolElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("enable-updates", b);
};

// Deprecated, moved to global/network scopes. Eventually it should be removed.
dep_qualifying_suffix: QUALIFYING_SUFFIX {
    ctx.unique("qualifying-suffix", ctx.loc2pos(@1));
    ctx.enter(ctx.NO_KEYWORD);
} COLON STRING {
    ElementPtr s(new StringElement($4, ctx.loc2pos(@4)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
};

server_ip: SERVER_IP {
    ctx.unique("server-ip", ctx.loc2pos(@1));
    ctx.enter(ctx.NO_KEYWORD);
} COLON STRING {
    ElementPtr s(new StringElement($4, ctx.loc2pos(@4)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
};

server_port: SERVER_PORT COLON INTEGER {
    ctx.unique("server-port", ctx.loc2pos(@1));
    ElementPtr i(new IntElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("server-port", i);
};

sender_ip: SENDER_IP {
    ctx.unique("sender-ip", ctx.loc2pos(@1));
    ctx.enter(ctx.NO_KEYWORD);
} COLON STRING {
    ElementPtr s(new StringElement($4, ctx.loc2pos(@4)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
};

sender_port: SENDER_PORT COLON INTEGER {
    ctx.unique("sender-port", ctx.loc2pos(@1));
    ElementPtr i(new IntElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("sender-port", i);
};

max_queue_size: MAX_QUEUE_SIZE COLON INTEGER {
    ctx.unique("max-queue-size", ctx.loc2pos(@1));
    ElementPtr i(new IntElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("max-queue-size", i);
};

ncr_protocol: NCR_PROTOCOL {
    ctx.unique("ncr-protocol", ctx.loc2pos(@1));
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
    ctx.unique("ncr-format", ctx.loc2pos(@1));
    ctx.enter(ctx.NCR_FORMAT);
} COLON JSON {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(@4)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
};

// Deprecated, moved to global/network scopes. Eventually it should be removed.
dep_override_no_update: OVERRIDE_NO_UPDATE COLON BOOLEAN {
    ctx.unique("override-no-update", ctx.loc2pos(@1));
    ElementPtr b(new BoolElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("override-no-update", b);
};

// Deprecated, moved to global/network scopes. Eventually it should be removed.
dep_override_client_update: OVERRIDE_CLIENT_UPDATE COLON BOOLEAN {
    ctx.unique("override-client-update", ctx.loc2pos(@1));
    ElementPtr b(new BoolElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("override-client-update", b);
};

// Deprecated, moved to global/network scopes. Eventually it should be removed.
dep_replace_client_name: REPLACE_CLIENT_NAME {
    ctx.unique("replace-client-name", ctx.loc2pos(@1));
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
} COLON ddns_replace_client_name_value {
    ctx.stack_.back()->set("replace-client-name", $4);
    ctx.leave();
};

// Deprecated, moved to global/network scopes. Eventually it should be removed.
dep_generated_prefix: GENERATED_PREFIX {
    ctx.unique("generated-prefix", ctx.loc2pos(@1));
    ctx.enter(ctx.NO_KEYWORD);
} COLON STRING {
    ElementPtr s(new StringElement($4, ctx.loc2pos(@4)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
};

// Deprecated, moved to global/network scopes. Eventually it should be removed.
dep_hostname_char_set: HOSTNAME_CHAR_SET {
    ctx.unique("hostname-char-set", ctx.loc2pos(@1));
    ctx.enter(ctx.NO_KEYWORD);
} COLON STRING {
    ElementPtr s(new StringElement($4, ctx.loc2pos(@4)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
};

// Deprecated, moved to global/network scopes. Eventually it should be removed.
dep_hostname_char_replacement: HOSTNAME_CHAR_REPLACEMENT {
    ctx.unique("hostname-char-replacement", ctx.loc2pos(@1));
    ctx.enter(ctx.NO_KEYWORD);
} COLON STRING {
    ElementPtr s(new StringElement($4, ctx.loc2pos(@4)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
};


// Config control information element

config_control: CONFIG_CONTROL {
    ctx.unique("config-control", ctx.loc2pos(@1));
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
                     | config_control_params COMMA {
                         ctx.warnAboutExtraCommas(@2);
                         }
                     ;

// This defines a list of allowed parameters for each subnet.
config_control_param: config_databases
                    | config_fetch_wait_time
                    ;

config_databases: CONFIG_DATABASES {
    ctx.unique("config-databases", ctx.loc2pos(@1));
    ElementPtr l(new ListElement(ctx.loc2pos(@1)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
} COLON LSQUARE_BRACKET database_list RSQUARE_BRACKET {
    ctx.stack_.pop_back();
    ctx.leave();
};

config_fetch_wait_time: CONFIG_FETCH_WAIT_TIME COLON INTEGER {
    ctx.unique("config-fetch-wait-time", ctx.loc2pos(@1));
    ElementPtr value(new IntElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("config-fetch-wait-time", value);
};

// --- loggers entry -----------------------------------------

loggers: LOGGERS {
    ctx.unique("loggers", ctx.loc2pos(@1));
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
               | loggers_entries COMMA {
                   ctx.warnAboutExtraCommas(@2);
                   }
               ;

// This defines a single entry defined in loggers.
logger_entry: LCURLY_BRACKET {
    ElementPtr l(new MapElement(ctx.loc2pos(@1)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
} logger_params RCURLY_BRACKET {
    ctx.stack_.pop_back();
};

logger_params: logger_param
             | logger_params COMMA logger_param
             | logger_params COMMA {
                 ctx.warnAboutExtraCommas(@2);
                 }
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
    ctx.unique("debuglevel", ctx.loc2pos(@1));
    ElementPtr dl(new IntElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("debuglevel", dl);
};

severity: SEVERITY {
    ctx.unique("severity", ctx.loc2pos(@1));
    ctx.enter(ctx.NO_KEYWORD);
} COLON STRING {
    ElementPtr sev(new StringElement($4, ctx.loc2pos(@4)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
};

output_options_list: OUTPUT_OPTIONS {
    ctx.unique("output_options", ctx.loc2pos(@1));
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
                           | output_options_list_content COMMA {
                               ctx.warnAboutExtraCommas(@2);
                               }
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
                  | output_params_list COMMA {
                      ctx.warnAboutExtraCommas(@2);
                      }
                  ;

output_params: output
             | flush
             | maxsize
             | maxver
             | pattern
             ;

output: OUTPUT {
    ctx.unique("output", ctx.loc2pos(@1));
    ctx.enter(ctx.NO_KEYWORD);
} COLON STRING {
    ElementPtr sev(new StringElement($4, ctx.loc2pos(@4)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
};

flush: FLUSH COLON BOOLEAN {
    ctx.unique("flush", ctx.loc2pos(@1));
    ElementPtr flush(new BoolElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("flush", flush);
};

maxsize: MAXSIZE COLON INTEGER {
    ctx.unique("maxsize", ctx.loc2pos(@1));
    ElementPtr maxsize(new IntElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("maxsize", maxsize);
};

maxver: MAXVER COLON INTEGER {
    ctx.unique("maxver", ctx.loc2pos(@1));
    ElementPtr maxver(new IntElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("maxver", maxver);
};

pattern: PATTERN {
    ctx.unique("pattern", ctx.loc2pos(@1));
    ctx.enter(ctx.NO_KEYWORD);
} COLON STRING {
    ElementPtr sev(new StringElement($4, ctx.loc2pos(@4)));
    ctx.stack_.back()->set("pattern", sev);
    ctx.leave();
};

compatibility: COMPATIBILITY {
    ctx.unique("compatibility", ctx.loc2pos(@1));
    ElementPtr i(new MapElement(ctx.loc2pos(@1)));
    ctx.stack_.back()->set("compatibility", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.COMPATIBILITY);
} COLON LCURLY_BRACKET compatibility_params RCURLY_BRACKET {
    ctx.stack_.pop_back();
    ctx.leave();
};

compatibility_params: compatibility_param
                    | compatibility_params COMMA compatibility_param
                    | compatibility_params COMMA {
                        ctx.warnAboutExtraCommas(@2);
                        }
                    ;

compatibility_param: lenient_option_parsing
                   | unknown_map_entry
                   ;

lenient_option_parsing: LENIENT_OPTION_PARSING COLON BOOLEAN {
    ctx.unique("lenient-option-parsing", ctx.loc2pos(@1));
    ElementPtr b(new BoolElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("lenient-option-parsing", b);
};

%%

void
isc::dhcp::Dhcp6Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
