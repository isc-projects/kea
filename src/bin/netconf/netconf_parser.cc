// A Bison parser, made by GNU Bison 3.8.2.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2021 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.

// DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
// especially those whose name start with YY_ or yy_.  They are
// private implementation details that can be changed or removed.


// Take the name prefix into account.
#define yylex   netconf_lex



#include "netconf_parser.h"


// Unqualified %code blocks.
#line 33 "netconf_parser.yy"

#include <netconf/parser_context.h>

#line 52 "netconf_parser.cc"


#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif


// Whether we are compiled with exception support.
#ifndef YY_EXCEPTIONS
# if defined __GNUC__ && !defined __EXCEPTIONS
#  define YY_EXCEPTIONS 0
# else
#  define YY_EXCEPTIONS 1
# endif
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K].location)
/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

# ifndef YYLLOC_DEFAULT
#  define YYLLOC_DEFAULT(Current, Rhs, N)                               \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).begin  = YYRHSLOC (Rhs, 1).begin;                   \
          (Current).end    = YYRHSLOC (Rhs, N).end;                     \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).begin = (Current).end = YYRHSLOC (Rhs, 0).end;      \
        }                                                               \
    while (false)
# endif


// Enable debugging if requested.
#if NETCONF_DEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << '\n';                       \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yy_stack_print_ ();                \
  } while (false)

#else // !NETCONF_DEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YY_USE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !NETCONF_DEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 14 "netconf_parser.yy"
namespace isc { namespace netconf {
#line 145 "netconf_parser.cc"

  /// Build a parser object.
  NetconfParser::NetconfParser (isc::netconf::ParserContext& ctx_yyarg)
#if NETCONF_DEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
#else
    :
#endif
      ctx (ctx_yyarg)
  {}

  NetconfParser::~NetconfParser ()
  {}

  NetconfParser::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------.
  | symbol.  |
  `---------*/



  // by_state.
  NetconfParser::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

  NetconfParser::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
  NetconfParser::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
  NetconfParser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  NetconfParser::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

  NetconfParser::symbol_kind_type
  NetconfParser::by_state::kind () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return symbol_kind::S_YYEMPTY;
    else
      return YY_CAST (symbol_kind_type, yystos_[+state]);
  }

  NetconfParser::stack_symbol_type::stack_symbol_type ()
  {}

  NetconfParser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state), YY_MOVE (that.location))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_value: // value
      case symbol_kind::S_map_value: // map_value
      case symbol_kind::S_socket_type_value: // socket_type_value
        value.YY_MOVE_OR_COPY< ElementPtr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_BOOLEAN: // "boolean"
        value.YY_MOVE_OR_COPY< bool > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_FLOAT: // "floating point"
        value.YY_MOVE_OR_COPY< double > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_INTEGER: // "integer"
        value.YY_MOVE_OR_COPY< int64_t > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_STRING: // "constant string"
        value.YY_MOVE_OR_COPY< std::string > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

#if 201103L <= YY_CPLUSPLUS
    // that is emptied.
    that.state = empty_state;
#endif
  }

  NetconfParser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s, YY_MOVE (that.location))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_value: // value
      case symbol_kind::S_map_value: // map_value
      case symbol_kind::S_socket_type_value: // socket_type_value
        value.move< ElementPtr > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_BOOLEAN: // "boolean"
        value.move< bool > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_FLOAT: // "floating point"
        value.move< double > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_INTEGER: // "integer"
        value.move< int64_t > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_STRING: // "constant string"
        value.move< std::string > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

    // that is emptied.
    that.kind_ = symbol_kind::S_YYEMPTY;
  }

#if YY_CPLUSPLUS < 201103L
  NetconfParser::stack_symbol_type&
  NetconfParser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_value: // value
      case symbol_kind::S_map_value: // map_value
      case symbol_kind::S_socket_type_value: // socket_type_value
        value.copy< ElementPtr > (that.value);
        break;

      case symbol_kind::S_BOOLEAN: // "boolean"
        value.copy< bool > (that.value);
        break;

      case symbol_kind::S_FLOAT: // "floating point"
        value.copy< double > (that.value);
        break;

      case symbol_kind::S_INTEGER: // "integer"
        value.copy< int64_t > (that.value);
        break;

      case symbol_kind::S_STRING: // "constant string"
        value.copy< std::string > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    return *this;
  }

  NetconfParser::stack_symbol_type&
  NetconfParser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_value: // value
      case symbol_kind::S_map_value: // map_value
      case symbol_kind::S_socket_type_value: // socket_type_value
        value.move< ElementPtr > (that.value);
        break;

      case symbol_kind::S_BOOLEAN: // "boolean"
        value.move< bool > (that.value);
        break;

      case symbol_kind::S_FLOAT: // "floating point"
        value.move< double > (that.value);
        break;

      case symbol_kind::S_INTEGER: // "integer"
        value.move< int64_t > (that.value);
        break;

      case symbol_kind::S_STRING: // "constant string"
        value.move< std::string > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    // that is emptied.
    that.state = empty_state;
    return *this;
  }
#endif

  template <typename Base>
  void
  NetconfParser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if NETCONF_DEBUG
  template <typename Base>
  void
  NetconfParser::yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YY_USE (yyoutput);
    if (yysym.empty ())
      yyo << "empty symbol";
    else
      {
        symbol_kind_type yykind = yysym.kind ();
        yyo << (yykind < YYNTOKENS ? "token" : "nterm")
            << ' ' << yysym.name () << " ("
            << yysym.location << ": ";
        switch (yykind)
    {
      case symbol_kind::S_STRING: // "constant string"
#line 107 "netconf_parser.yy"
                 { yyoutput << yysym.value.template as < std::string > (); }
#line 384 "netconf_parser.cc"
        break;

      case symbol_kind::S_INTEGER: // "integer"
#line 107 "netconf_parser.yy"
                 { yyoutput << yysym.value.template as < int64_t > (); }
#line 390 "netconf_parser.cc"
        break;

      case symbol_kind::S_FLOAT: // "floating point"
#line 107 "netconf_parser.yy"
                 { yyoutput << yysym.value.template as < double > (); }
#line 396 "netconf_parser.cc"
        break;

      case symbol_kind::S_BOOLEAN: // "boolean"
#line 107 "netconf_parser.yy"
                 { yyoutput << yysym.value.template as < bool > (); }
#line 402 "netconf_parser.cc"
        break;

      case symbol_kind::S_value: // value
#line 107 "netconf_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 408 "netconf_parser.cc"
        break;

      case symbol_kind::S_map_value: // map_value
#line 107 "netconf_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 414 "netconf_parser.cc"
        break;

      case symbol_kind::S_socket_type_value: // socket_type_value
#line 107 "netconf_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 420 "netconf_parser.cc"
        break;

      default:
        break;
    }
        yyo << ')';
      }
  }
#endif

  void
  NetconfParser::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
  NetconfParser::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
  NetconfParser::yypop_ (int n) YY_NOEXCEPT
  {
    yystack_.pop (n);
  }

#if NETCONF_DEBUG
  std::ostream&
  NetconfParser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  NetconfParser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  NetconfParser::debug_level_type
  NetconfParser::debug_level () const
  {
    return yydebug_;
  }

  void
  NetconfParser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // NETCONF_DEBUG

  NetconfParser::state_type
  NetconfParser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - YYNTOKENS] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - YYNTOKENS];
  }

  bool
  NetconfParser::yy_pact_value_is_default_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  NetconfParser::yy_table_value_is_error_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yytable_ninf_;
  }

  int
  NetconfParser::operator() ()
  {
    return parse ();
  }

  int
  NetconfParser::parse ()
  {
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The locations where the error started and ended.
    stack_symbol_type yyerror_range[3];

    /// The return value of parse ().
    int yyresult;

#if YY_EXCEPTIONS
    try
#endif // YY_EXCEPTIONS
      {
    YYCDEBUG << "Starting parse\n";


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, YY_MOVE (yyla));

  /*-----------------------------------------------.
  | yynewstate -- push a new symbol on the stack.  |
  `-----------------------------------------------*/
  yynewstate:
    YYCDEBUG << "Entering state " << int (yystack_[0].state) << '\n';
    YY_STACK_PRINT ();

    // Accept?
    if (yystack_[0].state == yyfinal_)
      YYACCEPT;

    goto yybackup;


  /*-----------.
  | yybackup.  |
  `-----------*/
  yybackup:
    // Try to take a decision without lookahead.
    yyn = yypact_[+yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token\n";
#if YY_EXCEPTIONS
        try
#endif // YY_EXCEPTIONS
          {
            symbol_type yylookahead (yylex (ctx));
            yyla.move (yylookahead);
          }
#if YY_EXCEPTIONS
        catch (const syntax_error& yyexc)
          {
            YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
            error (yyexc);
            goto yyerrlab1;
          }
#endif // YY_EXCEPTIONS
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    if (yyla.kind () == symbol_kind::S_YYerror)
    {
      // The scanner already issued an error message, process directly
      // to error recovery.  But do not keep the error token as
      // lookahead, it is too special and may lead us to an endless
      // loop in error recovery. */
      yyla.kind_ = symbol_kind::S_YYUNDEF;
      goto yyerrlab1;
    }

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.kind ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.kind ())
      {
        goto yydefault;
      }

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", state_type (yyn), YY_MOVE (yyla));
    goto yynewstate;


  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[+yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;


  /*-----------------------------.
  | yyreduce -- do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_ (yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
      switch (yyr1_[yyn])
    {
      case symbol_kind::S_value: // value
      case symbol_kind::S_map_value: // map_value
      case symbol_kind::S_socket_type_value: // socket_type_value
        yylhs.value.emplace< ElementPtr > ();
        break;

      case symbol_kind::S_BOOLEAN: // "boolean"
        yylhs.value.emplace< bool > ();
        break;

      case symbol_kind::S_FLOAT: // "floating point"
        yylhs.value.emplace< double > ();
        break;

      case symbol_kind::S_INTEGER: // "integer"
        yylhs.value.emplace< int64_t > ();
        break;

      case symbol_kind::S_STRING: // "constant string"
        yylhs.value.emplace< std::string > ();
        break;

      default:
        break;
    }


      // Default location.
      {
        stack_type::slice range (yystack_, yylen);
        YYLLOC_DEFAULT (yylhs.location, range, yylen);
        yyerror_range[1].location = yylhs.location;
      }

      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
#if YY_EXCEPTIONS
      try
#endif // YY_EXCEPTIONS
        {
          switch (yyn)
            {
  case 2: // $@1: %empty
#line 118 "netconf_parser.yy"
                       { ctx.ctx_ = ctx.NO_KEYWORDS; }
#line 695 "netconf_parser.cc"
    break;

  case 4: // $@2: %empty
#line 119 "netconf_parser.yy"
                         { ctx.ctx_ = ctx.CONFIG; }
#line 701 "netconf_parser.cc"
    break;

  case 6: // $@3: %empty
#line 120 "netconf_parser.yy"
                         { ctx.ctx_ = ctx.NETCONF; }
#line 707 "netconf_parser.cc"
    break;

  case 8: // $@4: %empty
#line 128 "netconf_parser.yy"
                            {
    // Parse the Netconf map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 717 "netconf_parser.cc"
    break;

  case 9: // sub_netconf: "{" $@4 global_params "}"
#line 132 "netconf_parser.yy"
                               {
    // parsing completed
}
#line 725 "netconf_parser.cc"
    break;

  case 10: // json: value
#line 139 "netconf_parser.yy"
            {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as < ElementPtr > ());
}
#line 734 "netconf_parser.cc"
    break;

  case 11: // value: "integer"
#line 145 "netconf_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 740 "netconf_parser.cc"
    break;

  case 12: // value: "floating point"
#line 146 "netconf_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location))); }
#line 746 "netconf_parser.cc"
    break;

  case 13: // value: "boolean"
#line 147 "netconf_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 752 "netconf_parser.cc"
    break;

  case 14: // value: "constant string"
#line 148 "netconf_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 758 "netconf_parser.cc"
    break;

  case 15: // value: "null"
#line 149 "netconf_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 764 "netconf_parser.cc"
    break;

  case 16: // value: map
#line 150 "netconf_parser.yy"
           { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 770 "netconf_parser.cc"
    break;

  case 17: // value: list_generic
#line 151 "netconf_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 776 "netconf_parser.cc"
    break;

  case 18: // $@5: %empty
#line 155 "netconf_parser.yy"
                    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 787 "netconf_parser.cc"
    break;

  case 19: // map: "{" $@5 map_content "}"
#line 160 "netconf_parser.yy"
                             {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 797 "netconf_parser.cc"
    break;

  case 20: // map_value: map
#line 166 "netconf_parser.yy"
               { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 803 "netconf_parser.cc"
    break;

  case 23: // not_empty_map: "constant string" ":" value
#line 180 "netconf_parser.yy"
                                  {
                  // map containing a single entry
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 813 "netconf_parser.cc"
    break;

  case 24: // not_empty_map: not_empty_map "," "constant string" ":" value
#line 185 "netconf_parser.yy"
                                                      {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 824 "netconf_parser.cc"
    break;

  case 25: // not_empty_map: not_empty_map ","
#line 191 "netconf_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 832 "netconf_parser.cc"
    break;

  case 26: // $@6: %empty
#line 196 "netconf_parser.yy"
                              {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 841 "netconf_parser.cc"
    break;

  case 27: // list_generic: "[" $@6 list_content "]"
#line 199 "netconf_parser.yy"
                               {
}
#line 848 "netconf_parser.cc"
    break;

  case 30: // not_empty_list: value
#line 206 "netconf_parser.yy"
                      {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 857 "netconf_parser.cc"
    break;

  case 31: // not_empty_list: not_empty_list "," value
#line 210 "netconf_parser.yy"
                                           {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 866 "netconf_parser.cc"
    break;

  case 32: // not_empty_list: not_empty_list ","
#line 214 "netconf_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 874 "netconf_parser.cc"
    break;

  case 33: // unknown_map_entry: "constant string" ":"
#line 226 "netconf_parser.yy"
                                {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as < std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 885 "netconf_parser.cc"
    break;

  case 34: // $@7: %empty
#line 234 "netconf_parser.yy"
                                   {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 896 "netconf_parser.cc"
    break;

  case 35: // netconf_syntax_map: "{" $@7 global_object "}"
#line 239 "netconf_parser.yy"
                               {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 906 "netconf_parser.cc"
    break;

  case 36: // $@8: %empty
#line 246 "netconf_parser.yy"
                       {
    // Let's create a MapElement that will represent it, add it to the
    // top level map (that's already on the stack) and put the new map
    // on the stack as well, so child elements will be able to add
    // themselves to it.

    // Prevent against duplicate.
    ctx.unique("Netconf", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Netconf", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.NETCONF);
}
#line 924 "netconf_parser.cc"
    break;

  case 37: // global_object: "Netconf" $@8 ":" "{" global_params "}"
#line 258 "netconf_parser.yy"
                                                    {
    // Ok, we're done with parsing Netconf. Let's take the map
    // off the stack.
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 935 "netconf_parser.cc"
    break;

  case 39: // global_object_comma: global_object ","
#line 267 "netconf_parser.yy"
                                         {
    ctx.warnAboutExtraCommas(yystack_[0].location);
}
#line 943 "netconf_parser.cc"
    break;

  case 44: // not_empty_global_params: not_empty_global_params ","
#line 278 "netconf_parser.yy"
                                                       {
                           ctx.warnAboutExtraCommas(yystack_[0].location);
                           }
#line 951 "netconf_parser.cc"
    break;

  case 54: // boot_update: "boot-update" ":" "boolean"
#line 296 "netconf_parser.yy"
                                       {
    ctx.unique("boot-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr flag(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("boot-update", flag);
}
#line 961 "netconf_parser.cc"
    break;

  case 55: // subscribe_changes: "subscribe-changes" ":" "boolean"
#line 302 "netconf_parser.yy"
                                                   {
    ctx.unique("subscribe-changes", ctx.loc2pos(yystack_[2].location));
    ElementPtr flag(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subscribe-changes", flag);
}
#line 971 "netconf_parser.cc"
    break;

  case 56: // validate_changes: "validate-changes" ":" "boolean"
#line 308 "netconf_parser.yy"
                                                 {
    ctx.unique("validate-changes", ctx.loc2pos(yystack_[2].location));
    ElementPtr flag(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("validate-changes", flag);
}
#line 981 "netconf_parser.cc"
    break;

  case 57: // $@9: %empty
#line 314 "netconf_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 989 "netconf_parser.cc"
    break;

  case 58: // user_context: "user-context" $@9 ":" map_value
#line 316 "netconf_parser.yy"
                  {
    ElementPtr parent = ctx.stack_.back();
    ElementPtr user_context = yystack_[0].value.as < ElementPtr > ();
    ConstElementPtr old = parent->get("user-context");

    // Handle already existing user context
    if (old) {
        // Check if it was a comment or a duplicate
        if ((old->size() != 1) || !old->contains("comment")) {
            std::stringstream msg;
            msg << "duplicate user-context entries (previous at "
                << old->getPosition().str() << ")";
            error(yystack_[3].location, msg.str());
        }
        // Merge the comment
        user_context->set("comment", old->get("comment"));
    }

    // Set the user context
    parent->set("user-context", user_context);
    ctx.leave();
}
#line 1016 "netconf_parser.cc"
    break;

  case 59: // $@10: %empty
#line 339 "netconf_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1024 "netconf_parser.cc"
    break;

  case 60: // comment: "comment" $@10 ":" "constant string"
#line 341 "netconf_parser.yy"
               {
    ElementPtr parent = ctx.stack_.back();
    ElementPtr user_context(new MapElement(ctx.loc2pos(yystack_[3].location)));
    ElementPtr comment(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    user_context->set("comment", comment);

    // Handle already existing user context
    ConstElementPtr old = parent->get("user-context");
    if (old) {
        // Check for duplicate comment
        if (old->contains("comment")) {
            std::stringstream msg;
            msg << "duplicate user-context/comment entries (previous at "
                << old->getPosition().str() << ")";
            error(yystack_[3].location, msg.str());
        }
        // Merge the user context in the comment
        merge(user_context, old);
    }

    // Set the user context
    parent->set("user-context", user_context);
    ctx.leave();
}
#line 1053 "netconf_parser.cc"
    break;

  case 61: // $@11: %empty
#line 367 "netconf_parser.yy"
                                 {
    ctx.unique("hooks-libraries", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1065 "netconf_parser.cc"
    break;

  case 62: // hooks_libraries: "hooks-libraries" $@11 ":" "[" hooks_libraries_list "]"
#line 373 "netconf_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1074 "netconf_parser.cc"
    break;

  case 67: // not_empty_hooks_libraries_list: not_empty_hooks_libraries_list ","
#line 384 "netconf_parser.yy"
                                           {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 1082 "netconf_parser.cc"
    break;

  case 68: // $@12: %empty
#line 389 "netconf_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1092 "netconf_parser.cc"
    break;

  case 69: // hooks_library: "{" $@12 hooks_params "}"
#line 393 "netconf_parser.yy"
                              {
    ctx.stack_.pop_back();
}
#line 1100 "netconf_parser.cc"
    break;

  case 72: // hooks_params: hooks_params ","
#line 399 "netconf_parser.yy"
                                 {
              ctx.warnAboutExtraCommas(yystack_[0].location);
              }
#line 1108 "netconf_parser.cc"
    break;

  case 76: // $@13: %empty
#line 409 "netconf_parser.yy"
                 {
    ctx.unique("library", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1117 "netconf_parser.cc"
    break;

  case 77: // library: "library" $@13 ":" "constant string"
#line 412 "netconf_parser.yy"
               {
    ElementPtr lib(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1127 "netconf_parser.cc"
    break;

  case 78: // $@14: %empty
#line 418 "netconf_parser.yy"
                       {
    ctx.unique("parameters", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1136 "netconf_parser.cc"
    break;

  case 79: // parameters: "parameters" $@14 ":" map_value
#line 421 "netconf_parser.yy"
                  {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1145 "netconf_parser.cc"
    break;

  case 80: // $@15: %empty
#line 429 "netconf_parser.yy"
                                                      {
    ctx.unique("managed-servers", ctx.loc2pos(yystack_[2].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[2].location)));
    ctx.stack_.back()->set("managed-servers", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.MANAGED_SERVERS);
}
#line 1157 "netconf_parser.cc"
    break;

  case 81: // managed_servers: "managed-servers" ":" "{" $@15 servers_entries "}"
#line 435 "netconf_parser.yy"
                                 {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1166 "netconf_parser.cc"
    break;

  case 86: // not_empty_servers_entries: not_empty_servers_entries ","
#line 446 "netconf_parser.yy"
                                                           {
                             ctx.warnAboutExtraCommas(yystack_[0].location);
                             }
#line 1174 "netconf_parser.cc"
    break;

  case 92: // $@16: %empty
#line 462 "netconf_parser.yy"
                           {
    ctx.unique("dhcp4", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER);
}
#line 1186 "netconf_parser.cc"
    break;

  case 93: // dhcp4_server: "dhcp4" $@16 ":" "{" managed_server_params "}"
#line 468 "netconf_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1195 "netconf_parser.cc"
    break;

  case 94: // $@17: %empty
#line 474 "netconf_parser.yy"
                           {
    ctx.unique("dhcp6", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp6", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER);
}
#line 1207 "netconf_parser.cc"
    break;

  case 95: // dhcp6_server: "dhcp6" $@17 ":" "{" managed_server_params "}"
#line 480 "netconf_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1216 "netconf_parser.cc"
    break;

  case 96: // $@18: %empty
#line 486 "netconf_parser.yy"
                     {
    ctx.unique("d2", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("d2", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER);
}
#line 1228 "netconf_parser.cc"
    break;

  case 97: // d2_server: "d2" $@18 ":" "{" managed_server_params "}"
#line 492 "netconf_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1237 "netconf_parser.cc"
    break;

  case 98: // $@19: %empty
#line 498 "netconf_parser.yy"
                     {
    ctx.unique("ca", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ca", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER);
}
#line 1249 "netconf_parser.cc"
    break;

  case 99: // ca_server: "ca" $@19 ":" "{" managed_server_params "}"
#line 504 "netconf_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1258 "netconf_parser.cc"
    break;

  case 102: // managed_server_params: managed_server_params ","
#line 512 "netconf_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 1266 "netconf_parser.cc"
    break;

  case 111: // $@20: %empty
#line 529 "netconf_parser.yy"
             {
    ctx.unique("model", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1275 "netconf_parser.cc"
    break;

  case 112: // model: "model" $@20 ":" "constant string"
#line 532 "netconf_parser.yy"
               {
    ElementPtr model(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("model", model);
    ctx.leave();
}
#line 1285 "netconf_parser.cc"
    break;

  case 113: // $@21: %empty
#line 539 "netconf_parser.yy"
                               {
    ctx.unique("control-socket", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 1297 "netconf_parser.cc"
    break;

  case 114: // control_socket: "control-socket" $@21 ":" "{" control_socket_params "}"
#line 545 "netconf_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1306 "netconf_parser.cc"
    break;

  case 117: // control_socket_params: control_socket_params ","
#line 553 "netconf_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 1314 "netconf_parser.cc"
    break;

  case 124: // $@22: %empty
#line 566 "netconf_parser.yy"
                         {
    ctx.unique("socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.SOCKET_TYPE);
}
#line 1323 "netconf_parser.cc"
    break;

  case 125: // socket_type: "socket-type" $@22 ":" socket_type_value
#line 569 "netconf_parser.yy"
                          {
    ctx.stack_.back()->set("socket-type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1332 "netconf_parser.cc"
    break;

  case 126: // socket_type_value: "unix"
#line 575 "netconf_parser.yy"
                         { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("unix", ctx.loc2pos(yystack_[0].location))); }
#line 1338 "netconf_parser.cc"
    break;

  case 127: // socket_type_value: "http"
#line 576 "netconf_parser.yy"
                         { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("http", ctx.loc2pos(yystack_[0].location))); }
#line 1344 "netconf_parser.cc"
    break;

  case 128: // socket_type_value: "stdout"
#line 577 "netconf_parser.yy"
                           { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("stdout", ctx.loc2pos(yystack_[0].location))); }
#line 1350 "netconf_parser.cc"
    break;

  case 129: // $@23: %empty
#line 580 "netconf_parser.yy"
                         {
    ctx.unique("socket-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1359 "netconf_parser.cc"
    break;

  case 130: // socket_name: "socket-name" $@23 ":" "constant string"
#line 583 "netconf_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 1369 "netconf_parser.cc"
    break;

  case 131: // $@24: %empty
#line 590 "netconf_parser.yy"
                       {
    ctx.unique("socket-url", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1378 "netconf_parser.cc"
    break;

  case 132: // socket_url: "socket-url" $@24 ":" "constant string"
#line 593 "netconf_parser.yy"
               {
    ElementPtr url(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-url", url);
    ctx.leave();
}
#line 1388 "netconf_parser.cc"
    break;

  case 133: // $@25: %empty
#line 603 "netconf_parser.yy"
                 {
    ctx.unique("loggers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 1400 "netconf_parser.cc"
    break;

  case 134: // loggers: "loggers" $@25 ":" "[" loggers_entries "]"
#line 609 "netconf_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1409 "netconf_parser.cc"
    break;

  case 137: // loggers_entries: loggers_entries ","
#line 618 "netconf_parser.yy"
                                       {
                   ctx.warnAboutExtraCommas(yystack_[0].location);
                   }
#line 1417 "netconf_parser.cc"
    break;

  case 138: // $@26: %empty
#line 624 "netconf_parser.yy"
                             {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 1427 "netconf_parser.cc"
    break;

  case 139: // logger_entry: "{" $@26 logger_params "}"
#line 628 "netconf_parser.yy"
                               {
    ctx.stack_.pop_back();
}
#line 1435 "netconf_parser.cc"
    break;

  case 142: // logger_params: logger_params ","
#line 634 "netconf_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 1443 "netconf_parser.cc"
    break;

  case 150: // $@27: %empty
#line 648 "netconf_parser.yy"
           {
    ctx.unique("name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1452 "netconf_parser.cc"
    break;

  case 151: // name: "name" $@27 ":" "constant string"
#line 651 "netconf_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1462 "netconf_parser.cc"
    break;

  case 152: // debuglevel: "debuglevel" ":" "integer"
#line 657 "netconf_parser.yy"
                                     {
    ctx.unique("debuglevel", ctx.loc2pos(yystack_[2].location));
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 1472 "netconf_parser.cc"
    break;

  case 153: // $@28: %empty
#line 663 "netconf_parser.yy"
                   {
    ctx.unique("severity", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1481 "netconf_parser.cc"
    break;

  case 154: // severity: "severity" $@28 ":" "constant string"
#line 666 "netconf_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 1491 "netconf_parser.cc"
    break;

  case 155: // $@29: %empty
#line 672 "netconf_parser.yy"
                                    {
    ctx.unique("output_options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 1503 "netconf_parser.cc"
    break;

  case 156: // output_options_list: "output_options" $@29 ":" "[" output_options_list_content "]"
#line 678 "netconf_parser.yy"
                                                                    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1512 "netconf_parser.cc"
    break;

  case 159: // output_options_list_content: output_options_list_content ","
#line 685 "netconf_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 1520 "netconf_parser.cc"
    break;

  case 160: // $@30: %empty
#line 690 "netconf_parser.yy"
                             {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1530 "netconf_parser.cc"
    break;

  case 161: // output_entry: "{" $@30 output_params_list "}"
#line 694 "netconf_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 1538 "netconf_parser.cc"
    break;

  case 164: // output_params_list: output_params_list ","
#line 700 "netconf_parser.yy"
                                        {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 1546 "netconf_parser.cc"
    break;

  case 170: // $@31: %empty
#line 712 "netconf_parser.yy"
               {
    ctx.unique("output", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1555 "netconf_parser.cc"
    break;

  case 171: // output: "output" $@31 ":" "constant string"
#line 715 "netconf_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 1565 "netconf_parser.cc"
    break;

  case 172: // flush: "flush" ":" "boolean"
#line 721 "netconf_parser.yy"
                           {
    ctx.unique("flush", ctx.loc2pos(yystack_[2].location));
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 1575 "netconf_parser.cc"
    break;

  case 173: // maxsize: "maxsize" ":" "integer"
#line 727 "netconf_parser.yy"
                               {
    ctx.unique("maxsize", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 1585 "netconf_parser.cc"
    break;

  case 174: // maxver: "maxver" ":" "integer"
#line 733 "netconf_parser.yy"
                             {
    ctx.unique("maxver", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 1595 "netconf_parser.cc"
    break;

  case 175: // $@32: %empty
#line 739 "netconf_parser.yy"
                 {
    ctx.unique("pattern", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1604 "netconf_parser.cc"
    break;

  case 176: // pattern: "pattern" $@32 ":" "constant string"
#line 742 "netconf_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pattern", sev);
    ctx.leave();
}
#line 1614 "netconf_parser.cc"
    break;


#line 1618 "netconf_parser.cc"

            default:
              break;
            }
        }
#if YY_EXCEPTIONS
      catch (const syntax_error& yyexc)
        {
          YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
          error (yyexc);
          YYERROR;
        }
#endif // YY_EXCEPTIONS
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, YY_MOVE (yylhs));
    }
    goto yynewstate;


  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        context yyctx (*this, yyla);
        std::string msg = yysyntax_error_ (yyctx);
        error (yyla.location, YY_MOVE (msg));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.kind () == symbol_kind::S_YYEOF)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:
    /* Pacify compilers when the user code never invokes YYERROR and
       the label yyerrorlab therefore never appears in user code.  */
    if (false)
      YYERROR;

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    YY_STACK_PRINT ();
    goto yyerrlab1;


  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    // Pop stack until we find a state that shifts the error token.
    for (;;)
      {
        yyn = yypact_[+yystack_[0].state];
        if (!yy_pact_value_is_default_ (yyn))
          {
            yyn += symbol_kind::S_YYerror;
            if (0 <= yyn && yyn <= yylast_
                && yycheck_[yyn] == symbol_kind::S_YYerror)
              {
                yyn = yytable_[yyn];
                if (0 < yyn)
                  break;
              }
          }

        // Pop the current state because it cannot handle the error token.
        if (yystack_.size () == 1)
          YYABORT;

        yyerror_range[1].location = yystack_[0].location;
        yy_destroy_ ("Error: popping", yystack_[0]);
        yypop_ ();
        YY_STACK_PRINT ();
      }
    {
      stack_symbol_type error_token;

      yyerror_range[2].location = yyla.location;
      YYLLOC_DEFAULT (error_token.location, yyerror_range, 2);

      // Shift the error token.
      error_token.state = state_type (yyn);
      yypush_ ("Shifting", YY_MOVE (error_token));
    }
    goto yynewstate;


  /*-------------------------------------.
  | yyacceptlab -- YYACCEPT comes here.  |
  `-------------------------------------*/
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;


  /*-----------------------------------.
  | yyabortlab -- YYABORT comes here.  |
  `-----------------------------------*/
  yyabortlab:
    yyresult = 1;
    goto yyreturn;


  /*-----------------------------------------------------.
  | yyreturn -- parsing is finished, return the result.  |
  `-----------------------------------------------------*/
  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    YY_STACK_PRINT ();
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
#if YY_EXCEPTIONS
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack\n";
        // Do not try to display the values of the reclaimed symbols,
        // as their printers might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
#endif // YY_EXCEPTIONS
  }

  void
  NetconfParser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what ());
  }

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  NetconfParser::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr;
        char const *yyp = yystr;

        for (;;)
          switch (*++yyp)
            {
            case '\'':
            case ',':
              goto do_not_strip_quotes;

            case '\\':
              if (*++yyp != '\\')
                goto do_not_strip_quotes;
              else
                goto append;

            append:
            default:
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }

  std::string
  NetconfParser::symbol_name (symbol_kind_type yysymbol)
  {
    return yytnamerr_ (yytname_[yysymbol]);
  }



  // NetconfParser::context.
  NetconfParser::context::context (const NetconfParser& yyparser, const symbol_type& yyla)
    : yyparser_ (yyparser)
    , yyla_ (yyla)
  {}

  int
  NetconfParser::context::expected_tokens (symbol_kind_type yyarg[], int yyargn) const
  {
    // Actual number of expected tokens
    int yycount = 0;

    const int yyn = yypact_[+yyparser_.yystack_[0].state];
    if (!yy_pact_value_is_default_ (yyn))
      {
        /* Start YYX at -YYN if negative to avoid negative indexes in
           YYCHECK.  In other words, skip the first -YYN actions for
           this state because they are default actions.  */
        const int yyxbegin = yyn < 0 ? -yyn : 0;
        // Stay within bounds of both yycheck and yytname.
        const int yychecklim = yylast_ - yyn + 1;
        const int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
        for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
          if (yycheck_[yyx + yyn] == yyx && yyx != symbol_kind::S_YYerror
              && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
            {
              if (!yyarg)
                ++yycount;
              else if (yycount == yyargn)
                return 0;
              else
                yyarg[yycount++] = YY_CAST (symbol_kind_type, yyx);
            }
      }

    if (yyarg && yycount == 0 && 0 < yyargn)
      yyarg[0] = symbol_kind::S_YYEMPTY;
    return yycount;
  }






  int
  NetconfParser::yy_syntax_error_arguments_ (const context& yyctx,
                                                 symbol_kind_type yyarg[], int yyargn) const
  {
    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yyla) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yyla.  (However, yyla is currently not documented for users.)
       - Of course, the expected token list depends on states to have
         correct lookahead information, and it depends on the parser not
         to perform extra reductions after fetching a lookahead from the
         scanner and before detecting a syntax error.  Thus, state merging
         (from LALR or IELR) and default reductions corrupt the expected
         token list.  However, the list is correct for canonical LR with
         one exception: it will still contain any token that will not be
         accepted due to an error action in a later state.
    */

    if (!yyctx.lookahead ().empty ())
      {
        if (yyarg)
          yyarg[0] = yyctx.token ();
        int yyn = yyctx.expected_tokens (yyarg ? yyarg + 1 : yyarg, yyargn - 1);
        return yyn + 1;
      }
    return 0;
  }

  // Generate an error message.
  std::string
  NetconfParser::yysyntax_error_ (const context& yyctx) const
  {
    // Its maximum.
    enum { YYARGS_MAX = 5 };
    // Arguments of yyformat.
    symbol_kind_type yyarg[YYARGS_MAX];
    int yycount = yy_syntax_error_arguments_ (yyctx, yyarg, YYARGS_MAX);

    char const* yyformat = YY_NULLPTR;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
      default: // Avoid compiler warnings.
        YYCASE_ (0, YY_("syntax error"));
        YYCASE_ (1, YY_("syntax error, unexpected %s"));
        YYCASE_ (2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_ (3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_ (4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_ (5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    std::string yyres;
    // Argument number.
    std::ptrdiff_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += symbol_name (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const signed char NetconfParser::yypact_ninf_ = -79;

  const signed char NetconfParser::yytable_ninf_ = -1;

  const short
  NetconfParser::yypact_[] =
  {
      -8,   -79,   -79,   -79,    16,    14,    13,    15,   -79,   -79,
     -79,   -79,   -79,   -79,   -79,   -79,   -79,   -79,   -79,   -79,
     -79,   -79,   -79,   -79,    14,     2,    45,    -1,   -79,    61,
      68,    75,    73,    79,   -79,    30,   -79,   -79,   -79,    89,
      90,   123,   124,   -79,   -79,   125,   -79,   108,    94,   -79,
     -79,   -79,   -79,   -79,   -79,   -79,   -79,   -79,   -79,    14,
      14,   -79,    85,   127,   -79,   -79,   128,   129,    86,    87,
      88,   130,   134,   135,   -79,   -79,    -1,   -79,   -79,   136,
     140,   141,    96,   -79,   -79,   -79,   -79,   137,   138,   -79,
      14,    -1,   -79,   -79,   -79,     7,   142,   143,   -79,   144,
     -79,   -79,   -79,   -79,   -79,   145,   148,   -79,   -79,   -79,
     -79,   -79,   -79,   149,   151,   -79,   -79,    50,   -79,   -79,
     152,   153,   154,   155,   -79,     7,   -13,   -79,   142,    76,
     143,   -79,   156,   157,   158,   159,   -79,   -79,   -79,   -79,
      34,   -79,   -79,   -79,   -79,   -79,   -79,   163,   -79,   -79,
     -79,   -79,    40,   -79,   -79,   -79,   -79,   -79,   -79,    63,
      63,    63,    63,   164,   165,   -24,   -79,   166,   167,   116,
     168,    76,   -79,   -79,   -79,   -79,   -79,   -79,   -79,   -79,
     -79,    92,   -79,   -79,   -79,    93,   111,   112,   131,   141,
     -79,   132,   169,   -79,   133,   -79,   171,   175,    63,   -79,
     -79,   -79,   -79,   -79,   -79,   -79,   173,   -79,   139,   174,
     -79,   -79,    77,   -79,   -79,    18,    51,   173,   -79,   -79,
     -79,   -79,   -79,   -79,   -79,   114,   -79,   -79,   -79,   -79,
     -79,   178,   179,   181,   -79,   115,   -79,   -79,   -79,   -79,
     -79,   -79,   -79,   182,   183,   187,    18,   -79,   188,   113,
     147,   150,   190,    51,   -79,    81,   160,   161,   -79,   162,
     -79,   -79,   -79,   170,   -79,   -79,   -79,   -79,   -79,   -79,
     -79,   -79,   -79
  };

  const unsigned char
  NetconfParser::yydefact_[] =
  {
       0,     2,     4,     6,     0,     0,     0,     0,     1,    26,
      18,    15,    14,    11,    12,    13,     3,    10,    16,    17,
      34,     5,     8,     7,    28,    21,     0,    40,    30,     0,
      29,     0,     0,    22,    36,     0,    38,    57,    59,     0,
       0,     0,     0,    61,   133,     0,    53,     0,    41,    42,
      45,    46,    47,    51,    52,    49,    48,    50,    27,    32,
       0,    19,    25,     0,    39,    35,     0,     0,     0,     0,
       0,     0,     0,     0,    33,     9,    44,    31,    23,     0,
       0,     0,     0,    54,    55,    56,    80,     0,     0,    43,
       0,    40,    20,    58,    60,    82,    63,     0,    24,     0,
      92,    94,    96,    98,    91,     0,    83,    84,    87,    88,
      89,    90,    68,     0,    64,    65,   138,     0,   135,    37,
       0,     0,     0,     0,    81,    86,     0,    62,    67,     0,
     137,   134,     0,     0,     0,     0,    85,    76,    78,    73,
       0,    70,    74,    75,    66,   150,   155,     0,   153,   149,
     147,   148,     0,   140,   143,   145,   146,   144,   136,     0,
       0,     0,     0,     0,     0,    72,    69,     0,     0,     0,
       0,   142,   139,   111,   113,   110,   104,   105,   106,   108,
     109,     0,   100,   103,   107,     0,     0,     0,     0,     0,
      71,     0,     0,   152,     0,   141,     0,     0,   102,    93,
      95,    97,    99,    77,    79,   151,     0,   154,     0,     0,
     101,   160,     0,   157,   112,     0,     0,   159,   156,   124,
     129,   131,   123,   121,   122,     0,   115,   118,   119,   120,
     170,     0,     0,     0,   175,     0,   162,   165,   166,   167,
     168,   169,   158,     0,     0,     0,   117,   114,     0,     0,
       0,     0,     0,   164,   161,     0,     0,     0,   116,     0,
     172,   173,   174,     0,   163,   126,   127,   128,   125,   130,
     132,   171,   176
  };

  const signed char
  NetconfParser::yypgoto_[] =
  {
     -79,   -79,   -79,   -79,   -79,   -79,   -79,   -79,   -20,   -78,
     -79,   -29,   -79,   -79,   -79,   -79,   -79,   -79,   -27,   -79,
     -79,   -79,   -79,   -79,    82,   -79,   119,   -22,   -19,   -18,
     -26,   -79,   -25,   -79,   -79,   -79,   -79,   -79,    69,   -79,
     -79,    33,   -79,   -79,   -79,   -79,   -79,   -79,   -79,   -79,
      74,   -79,   -79,   -79,   -79,   -79,   -79,   -79,   -79,   -36,
       3,   -79,   -79,   -79,   -79,   -79,   -46,   -79,   -79,   -79,
     -79,   -79,   -79,   -79,   -79,   -79,   -79,    72,   -79,   -79,
      32,   -79,   -79,   -79,   -79,   -79,   -79,   -79,   -79,    -9,
     -79,   -79,   -49,   -79,   -79,   -79,   -79,   -79,   -79,   -79
  };

  const short
  NetconfParser::yydefgoto_[] =
  {
       0,     4,     5,     6,     7,    23,    27,    16,    17,    18,
      25,    93,    32,    33,    19,    24,    29,    30,   175,    21,
      26,    35,    63,    36,    47,    48,    49,   176,   177,   178,
     179,    66,   180,    67,    55,    72,   113,   114,   115,   126,
     140,   141,   142,   163,   143,   164,    56,    95,   105,   106,
     107,   108,   120,   109,   121,   110,   122,   111,   123,   181,
     182,   183,   196,   184,   197,   225,   226,   227,   243,   268,
     228,   244,   229,   245,    57,    73,   117,   118,   129,   152,
     153,   154,   167,   155,   156,   170,   157,   168,   212,   213,
     216,   235,   236,   237,   248,   238,   239,   240,   241,   252
  };

  const short
  NetconfParser::yytable_[] =
  {
      46,    53,    54,    92,    28,    50,   137,   138,    51,    52,
      37,    38,    39,    40,    41,    42,     8,   137,   138,     9,
      20,    10,    22,    11,   100,   101,   102,   103,    43,    37,
      38,    44,    45,    64,     1,     2,     3,   165,    65,    77,
      78,   219,   166,   171,    45,   220,   221,    31,   172,    46,
      53,    54,    45,   130,    50,    34,   131,    51,    52,    12,
      13,    14,    15,    45,    46,    53,    54,    58,   104,    50,
      98,    59,    51,    52,    37,    38,    39,    40,    41,    60,
     217,    61,    62,   218,   173,   174,   230,    37,    38,   231,
     232,   233,   234,    68,    69,   198,   198,    76,   104,   139,
     199,   200,   149,   150,   151,   265,   266,   267,    45,   145,
     146,    92,   147,   148,   198,   198,    75,   246,   253,   201,
     202,    45,   247,   254,   185,   186,   187,    70,    71,    74,
      79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
      90,    94,    96,    97,   149,   150,   151,    91,    10,   112,
     116,   125,   119,   124,   128,   127,   132,   133,   134,   135,
     204,   260,   193,   159,   160,   161,   162,   169,   188,   189,
     191,   192,   194,    99,   206,   208,   203,   205,   207,   209,
     211,   215,   249,   250,   214,   251,   255,   256,   222,   223,
     224,   257,   259,   261,   263,    89,   262,   144,   190,   136,
     258,   210,   158,   195,   264,   269,   270,   271,   242,     0,
       0,     0,     0,     0,     0,   272,     0,     0,     0,   222,
     223,   224
  };

  const short
  NetconfParser::yycheck_[] =
  {
      27,    27,    27,    81,    24,    27,    30,    31,    27,    27,
      11,    12,    13,    14,    15,    16,     0,    30,    31,     5,
       7,     7,     7,     9,    17,    18,    19,    20,    29,    11,
      12,    32,    45,     3,    42,    43,    44,     3,     8,    59,
      60,    23,     8,     3,    45,    27,    28,    45,     8,    76,
      76,    76,    45,     3,    76,    10,     6,    76,    76,    45,
      46,    47,    48,    45,    91,    91,    91,     6,    95,    91,
      90,     3,    91,    91,    11,    12,    13,    14,    15,     4,
       3,     8,     3,     6,    21,    22,    35,    11,    12,    38,
      39,    40,    41,     4,     4,     3,     3,     3,   125,   126,
       8,     8,   129,   129,   129,    24,    25,    26,    45,    33,
      34,   189,    36,    37,     3,     3,     8,     3,     3,     8,
       8,    45,     8,     8,   160,   161,   162,     4,     4,     4,
      45,     4,     4,     4,    48,    48,    48,     7,     4,     4,
       4,    45,     5,     5,   171,   171,   171,     7,     7,     7,
       7,     3,     8,     8,     3,     6,     4,     4,     4,     4,
     189,    48,    46,     7,     7,     7,     7,     4,     4,     4,
       4,     4,     4,    91,     5,     4,    45,    45,    45,     4,
       7,     7,     4,     4,    45,     4,     4,     4,   215,   215,
     215,     4,     4,    46,     4,    76,    46,   128,   165,   125,
     246,   198,   130,   171,   253,    45,    45,    45,   217,    -1,
      -1,    -1,    -1,    -1,    -1,    45,    -1,    -1,    -1,   246,
     246,   246
  };

  const unsigned char
  NetconfParser::yystos_[] =
  {
       0,    42,    43,    44,    50,    51,    52,    53,     0,     5,
       7,     9,    45,    46,    47,    48,    56,    57,    58,    63,
       7,    68,     7,    54,    64,    59,    69,    55,    57,    65,
      66,    45,    61,    62,    10,    70,    72,    11,    12,    13,
      14,    15,    16,    29,    32,    45,    67,    73,    74,    75,
      76,    77,    78,    79,    81,    83,    95,   123,     6,     3,
       4,     8,     3,    71,     3,     8,    80,    82,     4,     4,
       4,     4,    84,   124,     4,     8,     3,    57,    57,    45,
       4,     4,     4,    48,    48,    48,     7,     4,     4,    75,
       4,     7,    58,    60,    45,    96,     5,     5,    57,    73,
      17,    18,    19,    20,    67,    97,    98,    99,   100,   102,
     104,   106,     7,    85,    86,    87,     7,   125,   126,     8,
     101,   103,   105,   107,     8,     3,    88,     6,     3,   127,
       3,     6,     4,     4,     4,     4,    99,    30,    31,    67,
      89,    90,    91,    93,    87,    33,    34,    36,    37,    67,
      79,    81,   128,   129,   130,   132,   133,   135,   126,     7,
       7,     7,     7,    92,    94,     3,     8,   131,   136,     4,
     134,     3,     8,    21,    22,    67,    76,    77,    78,    79,
      81,   108,   109,   110,   112,   108,   108,   108,     4,     4,
      90,     4,     4,    46,     4,   129,   111,   113,     3,     8,
       8,     8,     8,    45,    60,    45,     5,    45,     4,     4,
     109,     7,   137,   138,    45,     7,   139,     3,     6,    23,
      27,    28,    67,    79,    81,   114,   115,   116,   119,   121,
      35,    38,    39,    40,    41,   140,   141,   142,   144,   145,
     146,   147,   138,   117,   120,   122,     3,     8,   143,     4,
       4,     4,   148,     3,     8,     4,     4,     4,   115,     4,
      48,    46,    46,     4,   141,    24,    25,    26,   118,    45,
      45,    45,    45
  };

  const unsigned char
  NetconfParser::yyr1_[] =
  {
       0,    49,    51,    50,    52,    50,    53,    50,    55,    54,
      56,    57,    57,    57,    57,    57,    57,    57,    59,    58,
      60,    61,    61,    62,    62,    62,    64,    63,    65,    65,
      66,    66,    66,    67,    69,    68,    71,    70,    70,    72,
      73,    73,    74,    74,    74,    75,    75,    75,    75,    75,
      75,    75,    75,    75,    76,    77,    78,    80,    79,    82,
      81,    84,    83,    85,    85,    86,    86,    86,    88,    87,
      89,    89,    89,    89,    90,    90,    92,    91,    94,    93,
      96,    95,    97,    97,    98,    98,    98,    99,    99,    99,
      99,    99,   101,   100,   103,   102,   105,   104,   107,   106,
     108,   108,   108,   109,   109,   109,   109,   109,   109,   109,
     109,   111,   110,   113,   112,   114,   114,   114,   115,   115,
     115,   115,   115,   115,   117,   116,   118,   118,   118,   120,
     119,   122,   121,   124,   123,   125,   125,   125,   127,   126,
     128,   128,   128,   129,   129,   129,   129,   129,   129,   129,
     131,   130,   132,   134,   133,   136,   135,   137,   137,   137,
     139,   138,   140,   140,   140,   141,   141,   141,   141,   141,
     143,   142,   144,   145,   146,   148,   147
  };

  const signed char
  NetconfParser::yyr2_[] =
  {
       0,     2,     0,     3,     0,     3,     0,     3,     0,     4,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       1,     0,     1,     3,     5,     2,     0,     4,     0,     1,
       1,     3,     2,     2,     0,     4,     0,     6,     1,     2,
       0,     1,     1,     3,     2,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     3,     3,     0,     4,     0,
       4,     0,     6,     0,     1,     1,     3,     2,     0,     4,
       1,     3,     2,     1,     1,     1,     0,     4,     0,     4,
       0,     6,     0,     1,     1,     3,     2,     1,     1,     1,
       1,     1,     0,     6,     0,     6,     0,     6,     0,     6,
       1,     3,     2,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     0,     6,     1,     3,     2,     1,     1,
       1,     1,     1,     1,     0,     4,     1,     1,     1,     0,
       4,     0,     4,     0,     6,     1,     3,     2,     0,     4,
       1,     3,     2,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     3,     0,     4,     0,     6,     1,     3,     2,
       0,     4,     1,     3,     2,     1,     1,     1,     1,     1,
       0,     4,     3,     3,     3,     0,     4
  };


#if NETCONF_DEBUG || 1
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a YYNTOKENS, nonterminals.
  const char*
  const NetconfParser::yytname_[] =
  {
  "\"end of file\"", "error", "\"invalid token\"", "\",\"", "\":\"",
  "\"[\"", "\"]\"", "\"{\"", "\"}\"", "\"null\"", "\"Netconf\"",
  "\"user-context\"", "\"comment\"", "\"boot-update\"",
  "\"subscribe-changes\"", "\"validate-changes\"", "\"managed-servers\"",
  "\"dhcp4\"", "\"dhcp6\"", "\"d2\"", "\"ca\"", "\"model\"",
  "\"control-socket\"", "\"socket-type\"", "\"unix\"", "\"http\"",
  "\"stdout\"", "\"socket-name\"", "\"socket-url\"", "\"hooks-libraries\"",
  "\"library\"", "\"parameters\"", "\"loggers\"", "\"name\"",
  "\"output_options\"", "\"output\"", "\"debuglevel\"", "\"severity\"",
  "\"flush\"", "\"maxsize\"", "\"maxver\"", "\"pattern\"", "START_JSON",
  "START_NETCONF", "START_SUB_NETCONF", "\"constant string\"",
  "\"integer\"", "\"floating point\"", "\"boolean\"", "$accept", "start",
  "$@1", "$@2", "$@3", "sub_netconf", "$@4", "json", "value", "map", "$@5",
  "map_value", "map_content", "not_empty_map", "list_generic", "$@6",
  "list_content", "not_empty_list", "unknown_map_entry",
  "netconf_syntax_map", "$@7", "global_object", "$@8",
  "global_object_comma", "global_params", "not_empty_global_params",
  "global_param", "boot_update", "subscribe_changes", "validate_changes",
  "user_context", "$@9", "comment", "$@10", "hooks_libraries", "$@11",
  "hooks_libraries_list", "not_empty_hooks_libraries_list",
  "hooks_library", "$@12", "hooks_params", "hooks_param", "library",
  "$@13", "parameters", "$@14", "managed_servers", "$@15",
  "servers_entries", "not_empty_servers_entries", "server_entry",
  "dhcp4_server", "$@16", "dhcp6_server", "$@17", "d2_server", "$@18",
  "ca_server", "$@19", "managed_server_params", "managed_server_param",
  "model", "$@20", "control_socket", "$@21", "control_socket_params",
  "control_socket_param", "socket_type", "$@22", "socket_type_value",
  "socket_name", "$@23", "socket_url", "$@24", "loggers", "$@25",
  "loggers_entries", "logger_entry", "$@26", "logger_params",
  "logger_param", "name", "$@27", "debuglevel", "severity", "$@28",
  "output_options_list", "$@29", "output_options_list_content",
  "output_entry", "$@30", "output_params_list", "output_params", "output",
  "$@31", "flush", "maxsize", "maxver", "pattern", "$@32", YY_NULLPTR
  };
#endif


#if NETCONF_DEBUG
  const short
  NetconfParser::yyrline_[] =
  {
       0,   118,   118,   118,   119,   119,   120,   120,   128,   128,
     139,   145,   146,   147,   148,   149,   150,   151,   155,   155,
     166,   171,   172,   180,   185,   191,   196,   196,   202,   203,
     206,   210,   214,   226,   234,   234,   246,   246,   264,   267,
     272,   273,   276,   277,   278,   285,   286,   287,   288,   289,
     290,   291,   292,   293,   296,   302,   308,   314,   314,   339,
     339,   367,   367,   378,   379,   382,   383,   384,   389,   389,
     397,   398,   399,   402,   405,   406,   409,   409,   418,   418,
     429,   429,   440,   441,   444,   445,   446,   454,   455,   456,
     457,   458,   462,   462,   474,   474,   486,   486,   498,   498,
     510,   511,   512,   518,   519,   520,   521,   522,   523,   524,
     525,   529,   529,   539,   539,   551,   552,   553,   558,   559,
     560,   561,   562,   563,   566,   566,   575,   576,   577,   580,
     580,   590,   590,   603,   603,   616,   617,   618,   624,   624,
     632,   633,   634,   639,   640,   641,   642,   643,   644,   645,
     648,   648,   657,   663,   663,   672,   672,   683,   684,   685,
     690,   690,   698,   699,   700,   705,   706,   707,   708,   709,
     712,   712,   721,   727,   733,   739,   739
  };

  void
  NetconfParser::yy_stack_print_ () const
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << int (i->state);
    *yycdebug_ << '\n';
  }

  void
  NetconfParser::yy_reduce_print_ (int yyrule) const
  {
    int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):\n";
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // NETCONF_DEBUG


#line 14 "netconf_parser.yy"
} } // isc::netconf
#line 2303 "netconf_parser.cc"

#line 748 "netconf_parser.yy"


void
isc::netconf::NetconfParser::error(const location_type& loc,
                               const std::string& what)
{
    ctx.error(loc, what);
}
