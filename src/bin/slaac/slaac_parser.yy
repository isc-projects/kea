/* Copyright (C) 2019 Internet Systems Consortium, Inc. ("ISC")

   This Source Code Form is subject to the terms of the Mozilla Public
   License, v. 2.0. If a copy of the MPL was not distributed with this
   file, You can obtain one at http://mozilla.org/MPL/2.0/. */

%skeleton "lalr1.cc" /* -*- C++ -*- */
%require "3.0.0"
%defines
%define parser_class_name {SlaacParser}
%define api.prefix {slaac_}
%define api.token.constructor
%define api.value.type variant
%define api.namespace {isc::slaac}
%define parse.assert
%code requires
{
#include <string>
#include <cc/data.h>
#include <boost/lexical_cast.hpp>
#include <slaac/parser_context_decl.h>

using namespace isc::slaac;
using namespace isc::data;
using namespace std;
}
// The parsing context.
%param { isc::slaac::ParserContext& ctx }
%locations
%define parse.trace
%define parse.error verbose
%code
{
#include <slaac/parser_context.h>
}


%define api.token.prefix {TOKEN_}
// Tokens in an order which makes sense and related to the intented use.
// Actual regexps for tokens are defined in slaac_lexer.ll.
%token
  END  0  "end of file"
  COMMA ","
  COLON ":"
  LSQUARE_BRACKET "["
  RSQUARE_BRACKET "]"
  LCURLY_BRACKET "{"
  RCURLY_BRACKET "}"
  NULL_TYPE "null"

  SLAAC "Slaac"

  USER_CONTEXT "user-context"
  COMMENT "comment"

  INTERFACES_CONFIG "interfaces-config"
  INTERFACES "interfaces"

  HOP_LIMIT "hop-limit"
  MANAGED_FLAG "managed-flag"
  OTHER_FLAG "other-flag"
  ROUTER_LIFETIME "router-lifetime"
  REACHABLE_TIME "reachable-time"
  RETRANS_TIMER "retrans-timer"

  SOURCE_LL_ADDRESS "source-ll-address"
  MTU "mtu"
  UNIVERSAL_RA "universal-ra"
  PREFIX_INFOS "prefix-infos"

  PREFIX "prefix"
  ON_LINK_FLAG "on-link-flag"
  ADDRESS_CONFIG_FLAG "address-config-flag"
  VALID_LIFETIME "valid-lifetime"
  PREFERRED_LIFETIME "preferred-lifetime"

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
  // parse. This define the starting point. It either can be full grammar
  // (START_SLAAC), part of the grammar related to Slaac (START_SUB_SLAAC)
  // or can be any valid JSON (START_JSON)
  START_JSON
  START_SLAAC
  START_SUB_SLAAC
;

%token <std::string> STRING "constant string"
%token <int64_t> INTEGER "integer"
%token <double> FLOAT "floating point"
%token <bool> BOOLEAN "boolean"

%type <ElementPtr> value
%type <ElementPtr> map_value

%printer { yyoutput << $$; } <*>;

%%

// The whole grammar starts with a map, because the config file
// consists of Slaac entry in one big { }.
%start start;

// The starting token can be one of those listed below. Note these are
// "fake" tokens. They're produced by the lexer before any input text
// is parsed.
start: START_JSON      { ctx.ctx_ = ctx.NO_KEYWORDS; } json
     | START_SLAAC     { ctx.ctx_ = ctx.CONFIG; } slaac_syntax_map
     | START_SUB_SLAAC { ctx.ctx_ = ctx.SLAAC; } sub_slaac
     ;

// This rule defines a "shortcut". Instead of specifying the whole structure
// expected by full grammar, we can tell the parser to start from content of
// the Slaac. This is very useful for unit-testing, so we don't need
// to repeat the outer map and "Slaac" map. We can simply provide
// the contents of that map.
sub_slaac: LCURLY_BRACKET {
    // Parse the Slaac map
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

// This defines the top-level { } that holds Slaac object.
slaac_syntax_map: LCURLY_BRACKET {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(@1)));
    ctx.stack_.push_back(m);
} slaac_object RCURLY_BRACKET {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
};

// This define the Slaac object.
slaac_object: SLAAC {

    // Let's create a MapElement that will represent it, add it to the
    // top level map (that's already on the stack) and put the new map
    // on the stack as well, so child elements will be able to add
    // themselves to it.
    ElementPtr m(new MapElement(ctx.loc2pos(@1)));
    ctx.stack_.back()->set("Slaac", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SLAAC);
} COLON LCURLY_BRACKET global_params RCURLY_BRACKET {
    // Ok, we're done with parsing Slaac. Let's take the map
    // off the stack.
    ctx.stack_.pop_back();
    ctx.leave();
};

global_params: %empty
             | not_empty_global_params
             ;

not_empty_global_params: global_param
                       | not_empty_global_params COMMA global_param
                       ;

// These are the parameters that are allowed in the top-level for
// Slaac.
global_param: interfaces_config
            | loggers
            | hop_limit
            | managed_flag
            | other_flag
            | router_lifetime
            | reachable_time
            | retrans_timer
            | source_ll_address
            | mtu
            | universal_ra
            | prefix_infos
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
                       | unknown_map_entry
                       ;

interfaces_list: INTERFACES {
    ElementPtr l(new ListElement(ctx.loc2pos(@1)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORDS);
} COLON list_strings {
    ctx.stack_.pop_back();
    ctx.leave();
};

hop_limit: HOP_LIMIT COLON INTEGER {
    ElementPtr hl(new IntElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("hop-limit", hl);
};

managed_flag: MANAGED_FLAG COLON BOOLEAN {
    ElementPtr f(new BoolElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("managed-flag", f);
};

other_flag: OTHER_FLAG COLON BOOLEAN {
    ElementPtr f(new BoolElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("other-flag", f);
};

router_lifetime: ROUTER_LIFETIME COLON INTEGER {
    ElementPtr rl(new IntElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("router-lifetime", rl);
};

reachable_time: REACHABLE_TIME COLON INTEGER {
    ElementPtr rt(new IntElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("reachable-time", rt);
};

retrans_timer: RETRANS_TIMER COLON INTEGER {
    ElementPtr rt(new IntElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("retrans-timer", rt);
};

source_ll_address: SOURCE_LL_ADDRESS COLON BOOLEAN {
    ElementPtr lla(new BoolElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("source-ll-address", lla);
};

mtu: MTU COLON INTEGER {
    ElementPtr mtu(new IntElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("mtu", mtu);
};

// In theory a map with an "ietf" entry but simple accept any JSON.
universal_ra: UNIVERSAL_RA {
    ctx.enter(ctx.NO_KEYWORDS);
} COLON value {
    ctx.stack_.back()->set("universal-ra", $4);
    ctx.leave();
};

prefix_infos: PREFIX_INFOS {
    ElementPtr l(new LisElement(ctx.loc2pos(@1)));
    ctx.stack_.back()->set("prefix-infos", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.PREFIX_INFOS);
} COLON LSQUARE_BRACKET prefix_info_list RSQUARE_BRACKET {
    ctx.stack_.pop_back();
    ctx.leave();
};

prefix_info_list: %empty
                | not_empty_prefix_info_list
                ;

not_empty_prefix_info_list: prefix_info
                          | not_empty_prefix_info_list COMMA prefix_info
                          ;

prefix_info: LCURLY_BRACKET {
    ElementPtr m(new MapElement(ctx.loc2pos(@1)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
} prefix_info_params RCURLY_BRACKET {
    // The prefix parameter is required
    ctx.require("prefix", ctx.loc2pos(@1), ctx.loc2pos(@4));
    ctx.stack_.pop_back();
};

prefix_info_params: prefix_info_param
                  | prefix_info_params COMMA prefix_info_param
                  ;

prefix_info_param: prefix
                 | on_link_flag
                 | address_config_flag
                 | valid_lifetime
                 | preferred_lifetime
                 | user_context
                 | comment
                 | unknown_map_entry
                 ;

prefix: PREFIX {
    ctx.enter(ctx.NO_KEYWORDS);
} COLON STRING {
    ElementPtr pref(new StringElement($4, ctx.loc2pos(@4)));
    ctx.stack_.back()->set("prefix", pref);
    ctx.leave();
};

on_link_flag: ON_LINK_FLAG COLON BOOLEAN {
    ElementPtr f(new BoolElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("on-link-flag", f);
};

address_config_flag: ADDRESS_CONFIG_FLAG COLON BOOLEAN {
    ElementPtr f(new BoolElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("address-config-flag", f);
};

valid_lifetime: VALID_LIFETIME COLON INTEGER {
    ElementPtr rl(new IntElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("valid-lifetime", rl);
};

preferred_lifetime: PREFERRED_LIFETIME COLON INTEGER {
    ElementPtr rl(new IntElement($3, ctx.loc2pos(@3)));
    ctx.stack_.back()->set("preferred-lifetime", rl);
};

// --- Logging starts here -----------------------------------------------------

// "loggers", the only parameter which was defined in "Logging" object,
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
    ctx.enter(ctx.NO_KEYWORDS);
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
isc::slaac::SlaacParser::error(const location_type& loc,
                               const std::string& what)
{
    ctx.error(loc, what);
}
