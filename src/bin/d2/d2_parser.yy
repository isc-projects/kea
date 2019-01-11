/* Copyright (C) 2017-2018 Internet Systems Consortium, Inc. ("ISC")

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
  CONTROL_AGENT "Control-agent"

  DHCPDDNS "DhcpDdns"
  IP_ADDRESS "ip-address"
  PORT "port"
  DNS_SERVER_TIMEOUT "dns-server-timeout"
  NCR_PROTOCOL "ncr-protocol"
  UDP "UDP"
  TCP "TCP"
  NCR_FORMAT "ncr-format"
  JSON "JSON"
  USER_CONTEXT "user-context"
  COMMENT "comment"
  FORWARD_DDNS "forward-ddns"
  REVERSE_DDNS "reverse-ddns"
  DDNS_DOMAINS "ddns-domains"
  KEY_NAME "key-name"
  DNS_SERVERS "dns-servers"
  HOSTNAME "hostname"
  TSIG_KEYS "tsig-keys"
  ALGORITHM "algorithm"
  DIGEST_BITS "digest-bits"
  SECRET "secret"

  CONTROL_SOCKET "control-socket"
  SOCKET_TYPE "socket-type"
  SOCKET_NAME "socket-name"

  LOGGING "Logging"
  LOGGERS "loggers"
  NAME "name"
  OUTPUT_OPTIONS "output_options"
  OUTPUT "output"
  DEBUGLEVEL "debuglevel"
  SEVERITY "severity"
  FLUSH "flush"
  MAXSIZE "maxsize"
  MAXVER "maxver"

  // Not real tokens, just a way to signal what the parser is expected to
  // parse.
  TOPLEVEL_JSON
  TOPLEVEL_DHCPDDNS
  SUB_DHCPDDNS
  SUB_TSIG_KEY
  SUB_TSIG_KEYS
  SUB_DDNS_DOMAIN
  SUB_DDNS_DOMAINS
  SUB_DNS_SERVER
  SUB_DNS_SERVERS
;

%token <std::string> STRING "constant string"
%token <int64_t> INTEGER "integer"
%token <double> FLOAT "floating point"
%token <bool> BOOLEAN "boolean"

%type <ElementPtr> value
%type <ElementPtr> map_value
%type <ElementPtr> ncr_protocol_value

%printer { yyoutput << $$; } <*>;

%%

// The whole grammar starts with a map, because the config file
// consists of Dhcp, Logger and DhcpDdns entries in one big { }.
// We made the same for subparsers at the exception of the JSON value.
%start start;

start: TOPLEVEL_JSON { ctx.ctx_ = ctx.NO_KEYWORD; } sub_json
     | TOPLEVEL_DHCPDDNS { ctx.ctx_ = ctx.CONFIG; } syntax_map
     | SUB_DHCPDDNS { ctx.ctx_ = ctx.DHCPDDNS; } sub_dhcpddns
     | SUB_TSIG_KEY { ctx.ctx_ = ctx.TSIG_KEY; } sub_tsig_key
     | SUB_TSIG_KEYS { ctx.ctx_ = ctx.TSIG_KEYS; } sub_tsig_keys
     | SUB_DDNS_DOMAIN { ctx.ctx_ = ctx.DDNS_DOMAIN; } sub_ddns_domain
     | SUB_DDNS_DOMAINS { ctx.ctx_ = ctx.DDNS_DOMAINS; } sub_ddns_domains
     | SUB_DNS_SERVER { ctx.ctx_ = ctx.DNS_SERVERS; } sub_dns_server
     | SUB_DNS_SERVERS { ctx.ctx_ = ctx.DNS_SERVERS; } sub_dns_servers
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
             | control_agent_json_object
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

// These are the top-level parameters allowed for DhcpDdns
dhcpddns_param: ip_address
              | port
              | dns_server_timeout
              | ncr_protocol
              | ncr_format
              | forward_ddns
              | reverse_ddns
              | tsig_keys
              | control_socket
              | user_context
              | comment
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
    if ($3 <= 0 || $3 >= 65536 ) {
        error(@3, "port must be greater than zero but less than 65536");
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

forward_ddns : FORWARD_DDNS {
    ElementPtr m(new MapElement(ctx.loc2pos(@1)));
    ctx.stack_.back()->set("forward-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.FORWARD_DDNS);
} COLON LCURLY_BRACKET ddns_mgr_params RCURLY_BRACKET {
    ctx.stack_.pop_back();
    ctx.leave();
};

reverse_ddns : REVERSE_DDNS {
    ElementPtr m(new MapElement(ctx.loc2pos(@1)));
    ctx.stack_.back()->set("reverse-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.REVERSE_DDNS);
} COLON LCURLY_BRACKET ddns_mgr_params RCURLY_BRACKET {
    ctx.stack_.pop_back();
    ctx.leave();
};

ddns_mgr_params: %empty
               | not_empty_ddns_mgr_params
               ;

not_empty_ddns_mgr_params: ddns_mgr_param
                         | ddns_mgr_params COMMA ddns_mgr_param
                         ;

ddns_mgr_param: ddns_domains
              | unknown_map_entry
              ;


// --- ddns-domains ----------------------------------------
ddns_domains: DDNS_DOMAINS {
    ElementPtr l(new ListElement(ctx.loc2pos(@1)));
    ctx.stack_.back()->set("ddns-domains", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.DDNS_DOMAINS);
} COLON LSQUARE_BRACKET ddns_domain_list RSQUARE_BRACKET {
    ctx.stack_.pop_back();
    ctx.leave();
};

sub_ddns_domains: LSQUARE_BRACKET {
    ElementPtr l(new ListElement(ctx.loc2pos(@1)));
    ctx.stack_.push_back(l);
} ddns_domain_list RSQUARE_BRACKET {
    // parsing completed
}

ddns_domain_list: %empty
              | not_empty_ddns_domain_list
              ;

not_empty_ddns_domain_list: ddns_domain
                        | not_empty_ddns_domain_list COMMA ddns_domain
                        ;

ddns_domain: LCURLY_BRACKET {
    ElementPtr m(new MapElement(ctx.loc2pos(@1)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
} ddns_domain_params RCURLY_BRACKET {
    ctx.stack_.pop_back();
};

sub_ddns_domain: LCURLY_BRACKET {
    ElementPtr m(new MapElement(ctx.loc2pos(@1)));
    ctx.stack_.push_back(m);
} ddns_domain_params RCURLY_BRACKET {
    // parsing completed
};

ddns_domain_params: ddns_domain_param
                  | ddns_domain_params COMMA ddns_domain_param
                  ;

ddns_domain_param: ddns_domain_name
                 | ddns_domain_key_name
                 | dns_servers
                 | user_context
                 | comment
                 | unknown_map_entry
                 ;

//  @todo NAME needs to be an FQDN sort of thing
ddns_domain_name: NAME {
    ctx.enter(ctx.NO_KEYWORD);
} COLON STRING {
    if ($4 == "") {
        error(@3, "Ddns domain name cannot be blank");
    }
    ElementPtr elem(new StringElement($4, ctx.loc2pos(@4)));
    ElementPtr name(new StringElement($4, ctx.loc2pos(@4)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
};

ddns_domain_key_name: KEY_NAME {
    ctx.enter(ctx.NO_KEYWORD);
} COLON STRING {
    ElementPtr elem(new StringElement($4, ctx.loc2pos(@4)));
    ElementPtr name(new StringElement($4, ctx.loc2pos(@4)));
    ctx.stack_.back()->set("key-name", name);
    ctx.leave();
};

// --- end ddns-domains ----------------------------------------

// --- dns-servers ----------------------------------------
dns_servers: DNS_SERVERS {
    ElementPtr l(new ListElement(ctx.loc2pos(@1)));
    ctx.stack_.back()->set("dns-servers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.DNS_SERVERS);
} COLON LSQUARE_BRACKET dns_server_list RSQUARE_BRACKET {
    ctx.stack_.pop_back();
    ctx.leave();
};

sub_dns_servers: LSQUARE_BRACKET {
    ElementPtr l(new ListElement(ctx.loc2pos(@1)));
    ctx.stack_.push_back(l);
} dns_server_list RSQUARE_BRACKET {
    // parsing completed
}

dns_server_list: dns_server
               | dns_server_list COMMA dns_server
               ;

dns_server: LCURLY_BRACKET {
    ElementPtr m(new MapElement(ctx.loc2pos(@1)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
} dns_server_params RCURLY_BRACKET {
    ctx.stack_.pop_back();
};

sub_dns_server: LCURLY_BRACKET {
    ElementPtr m(new MapElement(ctx.loc2pos(@1)));
    ctx.stack_.push_back(m);
} dns_server_params RCURLY_BRACKET {
    // parsing completed
};

dns_server_params: dns_server_param
               | dns_server_params COMMA dns_server_param
               ;

dns_server_param: dns_server_hostname
              | dns_server_ip_address
              | dns_server_port
              | user_context
              | comment
              | unknown_map_entry
              ;

dns_server_hostname: HOSTNAME {
    ctx.enter(ctx.NO_KEYWORD);
} COLON STRING {
    if ($4 != "") {
        error(@3, "hostname is not yet supported");
    }
    ElementPtr elem(new StringElement($4, ctx.loc2pos(@4)));
    ElementPtr name(new StringElement($4, ctx.loc2pos(@4)));
    ctx.stack_.back()->set("hostname", name);
    ctx.leave();
};

dns_server_ip_address: IP_ADDRESS {
    ctx.enter(ctx.NO_KEYWORD);
} COLON STRING {
    ElementPtr s(new StringElement($4, ctx.loc2pos(@4)));
    ctx.stack_.back()->set("ip-address", s);
    ctx.leave();
};

dns_server_port: PORT COLON INTEGER {
    if ($3 <= 0 || $3 >= 65536 ) {
        error(@3, "port must be greater than zero but less than 65536");
    }
    ElementPtr i(new IntElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("port", i);
};

// --- end of dns-servers ---------------------------------



// --- tsig-keys ----------------------------------------
// "tsig-keys" : [ ... ]
tsig_keys: TSIG_KEYS {
    ElementPtr l(new ListElement(ctx.loc2pos(@1)));
    ctx.stack_.back()->set("tsig-keys", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.TSIG_KEYS);
} COLON LSQUARE_BRACKET tsig_keys_list RSQUARE_BRACKET {
    ctx.stack_.pop_back();
    ctx.leave();
};

sub_tsig_keys: LSQUARE_BRACKET {
    ElementPtr l(new ListElement(ctx.loc2pos(@1)));
    ctx.stack_.push_back(l);
} tsig_keys_list RSQUARE_BRACKET {
    // parsing completed
}

tsig_keys_list: %empty
              | not_empty_tsig_keys_list
              ;

not_empty_tsig_keys_list: tsig_key
                        | not_empty_tsig_keys_list COMMA tsig_key
                        ;

tsig_key: LCURLY_BRACKET {
    ElementPtr m(new MapElement(ctx.loc2pos(@1)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
} tsig_key_params RCURLY_BRACKET {
    ctx.stack_.pop_back();
};

sub_tsig_key: LCURLY_BRACKET {
    // Parse tsig key list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(@1)));
    ctx.stack_.push_back(m);
} tsig_key_params RCURLY_BRACKET {
    // parsing completed
};


tsig_key_params: tsig_key_param
               | tsig_key_params COMMA tsig_key_param
               ;

tsig_key_param: tsig_key_name
              | tsig_key_algorithm
              | tsig_key_digest_bits
              | tsig_key_secret
              | user_context
              | comment
              | unknown_map_entry
              ;

tsig_key_name: NAME {
    ctx.enter(ctx.NO_KEYWORD);
} COLON STRING {
    if ($4 == "") {
        error(@3, "TSIG key name cannot be blank");
    }
    ElementPtr elem(new StringElement($4, ctx.loc2pos(@4)));
    ElementPtr name(new StringElement($4, ctx.loc2pos(@4)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
};

tsig_key_algorithm: ALGORITHM {
    ctx.enter(ctx.NO_KEYWORD);
} COLON STRING {
    if ($4 == "") {
        error(@3, "TSIG key algorithm cannot be blank");
    }
    ElementPtr elem(new StringElement($4, ctx.loc2pos(@4)));
    ctx.stack_.back()->set("algorithm", elem);
    ctx.leave();
};

tsig_key_digest_bits: DIGEST_BITS COLON INTEGER {
    if ($3 < 0 || ($3 > 0  && ($3 % 8 != 0))) {
        error(@3, "TSIG key digest-bits must either be zero or a positive, multiple of eight");
    }
    ElementPtr elem(new IntElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("digest-bits", elem);
};

tsig_key_secret: SECRET {
    ctx.enter(ctx.NO_KEYWORD);
} COLON STRING {
    if ($4 == "") {
        error(@3, "TSIG key secret cannot be blank");
    }
    ElementPtr elem(new StringElement($4, ctx.loc2pos(@4)));
    ctx.stack_.back()->set("secret", elem);
    ctx.leave();
};


// --- end of tsig-keys ---------------------------------

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

// ----------------------------------------------------------------

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

control_agent_json_object: CONTROL_AGENT {
    ctx.enter(ctx.NO_KEYWORD);
} COLON value {
    ctx.stack_.back()->set("Control-agent", $4);
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
            | user_context
            | comment
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
}

maxsize: MAXSIZE COLON INTEGER {
    ElementPtr maxsize(new IntElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("maxsize", maxsize);
}

maxver: MAXVER COLON INTEGER {
    ElementPtr maxver(new IntElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("maxver", maxver);
}

%%

void
isc::d2::D2Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
