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

  case 25: // $@6: %empty
#line 193 "netconf_parser.yy"
                              {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 833 "netconf_parser.cc"
    break;

  case 26: // list_generic: "[" $@6 list_content "]"
#line 196 "netconf_parser.yy"
                               {
}
#line 840 "netconf_parser.cc"
    break;

  case 29: // not_empty_list: value
#line 203 "netconf_parser.yy"
                      {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 849 "netconf_parser.cc"
    break;

  case 30: // not_empty_list: not_empty_list "," value
#line 207 "netconf_parser.yy"
                                           {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 858 "netconf_parser.cc"
    break;

  case 31: // unknown_map_entry: "constant string" ":"
#line 220 "netconf_parser.yy"
                                {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as < std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 869 "netconf_parser.cc"
    break;

  case 32: // $@7: %empty
#line 228 "netconf_parser.yy"
                                   {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 880 "netconf_parser.cc"
    break;

  case 33: // netconf_syntax_map: "{" $@7 global_object "}"
#line 233 "netconf_parser.yy"
                               {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 890 "netconf_parser.cc"
    break;

  case 34: // $@8: %empty
#line 240 "netconf_parser.yy"
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
#line 909 "netconf_parser.cc"
    break;

  case 35: // global_object: "Netconf" $@8 ":" "{" global_params "}"
#line 253 "netconf_parser.yy"
                                                    {
    // Ok, we're done with parsing Netconf. Let's take the map
    // off the stack.
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 920 "netconf_parser.cc"
    break;

  case 49: // boot_update: "boot-update" ":" "boolean"
#line 281 "netconf_parser.yy"
                                       {
    ctx.unique("boot-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr flag(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("boot-update", flag);
}
#line 930 "netconf_parser.cc"
    break;

  case 50: // subscribe_changes: "subscribe-changes" ":" "boolean"
#line 287 "netconf_parser.yy"
                                                   {
    ctx.unique("subscribe-changes", ctx.loc2pos(yystack_[2].location));
    ElementPtr flag(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subscribe-changes", flag);
}
#line 940 "netconf_parser.cc"
    break;

  case 51: // validate_changes: "validate-changes" ":" "boolean"
#line 293 "netconf_parser.yy"
                                                 {
    ctx.unique("validate-changes", ctx.loc2pos(yystack_[2].location));
    ElementPtr flag(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("validate-changes", flag);
}
#line 950 "netconf_parser.cc"
    break;

  case 52: // $@9: %empty
#line 299 "netconf_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 958 "netconf_parser.cc"
    break;

  case 53: // user_context: "user-context" $@9 ":" map_value
#line 301 "netconf_parser.yy"
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
#line 985 "netconf_parser.cc"
    break;

  case 54: // $@10: %empty
#line 324 "netconf_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 993 "netconf_parser.cc"
    break;

  case 55: // comment: "comment" $@10 ":" "constant string"
#line 326 "netconf_parser.yy"
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
#line 1022 "netconf_parser.cc"
    break;

  case 56: // $@11: %empty
#line 352 "netconf_parser.yy"
                                 {
    ctx.unique("hooks-libraries", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1034 "netconf_parser.cc"
    break;

  case 57: // hooks_libraries: "hooks-libraries" $@11 ":" "[" hooks_libraries_list "]"
#line 358 "netconf_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1043 "netconf_parser.cc"
    break;

  case 62: // $@12: %empty
#line 371 "netconf_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1053 "netconf_parser.cc"
    break;

  case 63: // hooks_library: "{" $@12 hooks_params "}"
#line 375 "netconf_parser.yy"
                              {
    ctx.stack_.pop_back();
}
#line 1061 "netconf_parser.cc"
    break;

  case 69: // $@13: %empty
#line 388 "netconf_parser.yy"
                 {
    ctx.unique("library", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1070 "netconf_parser.cc"
    break;

  case 70: // library: "library" $@13 ":" "constant string"
#line 391 "netconf_parser.yy"
               {
    ElementPtr lib(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1080 "netconf_parser.cc"
    break;

  case 71: // $@14: %empty
#line 397 "netconf_parser.yy"
                       {
    ctx.unique("parameters", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1089 "netconf_parser.cc"
    break;

  case 72: // parameters: "parameters" $@14 ":" map_value
#line 400 "netconf_parser.yy"
                  {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1098 "netconf_parser.cc"
    break;

  case 73: // $@15: %empty
#line 408 "netconf_parser.yy"
                                                      {
    ctx.unique("managed-servers", ctx.loc2pos(yystack_[2].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[2].location)));
    ctx.stack_.back()->set("managed-servers", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.MANAGED_SERVERS);
}
#line 1110 "netconf_parser.cc"
    break;

  case 74: // managed_servers: "managed-servers" ":" "{" $@15 servers_entries "}"
#line 414 "netconf_parser.yy"
                                 {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1119 "netconf_parser.cc"
    break;

  case 84: // $@16: %empty
#line 438 "netconf_parser.yy"
                           {
    ctx.unique("dhcp4", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER);
}
#line 1131 "netconf_parser.cc"
    break;

  case 85: // dhcp4_server: "dhcp4" $@16 ":" "{" managed_server_params "}"
#line 444 "netconf_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1140 "netconf_parser.cc"
    break;

  case 86: // $@17: %empty
#line 450 "netconf_parser.yy"
                           {
    ctx.unique("dhcp6", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp6", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER);
}
#line 1152 "netconf_parser.cc"
    break;

  case 87: // dhcp6_server: "dhcp6" $@17 ":" "{" managed_server_params "}"
#line 456 "netconf_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1161 "netconf_parser.cc"
    break;

  case 88: // $@18: %empty
#line 462 "netconf_parser.yy"
                     {
    ctx.unique("d2", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("d2", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER);
}
#line 1173 "netconf_parser.cc"
    break;

  case 89: // d2_server: "d2" $@18 ":" "{" managed_server_params "}"
#line 468 "netconf_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1182 "netconf_parser.cc"
    break;

  case 90: // $@19: %empty
#line 474 "netconf_parser.yy"
                     {
    ctx.unique("ca", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ca", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER);
}
#line 1194 "netconf_parser.cc"
    break;

  case 91: // ca_server: "ca" $@19 ":" "{" managed_server_params "}"
#line 480 "netconf_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1203 "netconf_parser.cc"
    break;

  case 102: // $@20: %empty
#line 502 "netconf_parser.yy"
             {
    ctx.unique("model", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1212 "netconf_parser.cc"
    break;

  case 103: // model: "model" $@20 ":" "constant string"
#line 505 "netconf_parser.yy"
               {
    ElementPtr model(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("model", model);
    ctx.leave();
}
#line 1222 "netconf_parser.cc"
    break;

  case 104: // $@21: %empty
#line 512 "netconf_parser.yy"
                               {
    ctx.unique("control-socket", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 1234 "netconf_parser.cc"
    break;

  case 105: // control_socket: "control-socket" $@21 ":" "{" control_socket_params "}"
#line 518 "netconf_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1243 "netconf_parser.cc"
    break;

  case 114: // $@22: %empty
#line 536 "netconf_parser.yy"
                         {
    ctx.unique("socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.SOCKET_TYPE);
}
#line 1252 "netconf_parser.cc"
    break;

  case 115: // socket_type: "socket-type" $@22 ":" socket_type_value
#line 539 "netconf_parser.yy"
                          {
    ctx.stack_.back()->set("socket-type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1261 "netconf_parser.cc"
    break;

  case 116: // socket_type_value: "unix"
#line 545 "netconf_parser.yy"
                         { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("unix", ctx.loc2pos(yystack_[0].location))); }
#line 1267 "netconf_parser.cc"
    break;

  case 117: // socket_type_value: "http"
#line 546 "netconf_parser.yy"
                         { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("http", ctx.loc2pos(yystack_[0].location))); }
#line 1273 "netconf_parser.cc"
    break;

  case 118: // socket_type_value: "stdout"
#line 547 "netconf_parser.yy"
                           { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("stdout", ctx.loc2pos(yystack_[0].location))); }
#line 1279 "netconf_parser.cc"
    break;

  case 119: // $@23: %empty
#line 550 "netconf_parser.yy"
                         {
    ctx.unique("socket-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1288 "netconf_parser.cc"
    break;

  case 120: // socket_name: "socket-name" $@23 ":" "constant string"
#line 553 "netconf_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 1298 "netconf_parser.cc"
    break;

  case 121: // $@24: %empty
#line 560 "netconf_parser.yy"
                       {
    ctx.unique("socket-url", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1307 "netconf_parser.cc"
    break;

  case 122: // socket_url: "socket-url" $@24 ":" "constant string"
#line 563 "netconf_parser.yy"
               {
    ElementPtr url(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-url", url);
    ctx.leave();
}
#line 1317 "netconf_parser.cc"
    break;

  case 123: // $@25: %empty
#line 573 "netconf_parser.yy"
                 {
    ctx.unique("loggers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 1329 "netconf_parser.cc"
    break;

  case 124: // loggers: "loggers" $@25 ":" "[" loggers_entries "]"
#line 579 "netconf_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1338 "netconf_parser.cc"
    break;

  case 127: // $@26: %empty
#line 591 "netconf_parser.yy"
                             {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 1348 "netconf_parser.cc"
    break;

  case 128: // logger_entry: "{" $@26 logger_params "}"
#line 595 "netconf_parser.yy"
                               {
    ctx.stack_.pop_back();
}
#line 1356 "netconf_parser.cc"
    break;

  case 138: // $@27: %empty
#line 612 "netconf_parser.yy"
           {
    ctx.unique("name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1365 "netconf_parser.cc"
    break;

  case 139: // name: "name" $@27 ":" "constant string"
#line 615 "netconf_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1375 "netconf_parser.cc"
    break;

  case 140: // debuglevel: "debuglevel" ":" "integer"
#line 621 "netconf_parser.yy"
                                     {
    ctx.unique("debuglevel", ctx.loc2pos(yystack_[2].location));
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 1385 "netconf_parser.cc"
    break;

  case 141: // $@28: %empty
#line 627 "netconf_parser.yy"
                   {
    ctx.unique("severity", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1394 "netconf_parser.cc"
    break;

  case 142: // severity: "severity" $@28 ":" "constant string"
#line 630 "netconf_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 1404 "netconf_parser.cc"
    break;

  case 143: // $@29: %empty
#line 636 "netconf_parser.yy"
                                    {
    ctx.unique("output_options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 1416 "netconf_parser.cc"
    break;

  case 144: // output_options_list: "output_options" $@29 ":" "[" output_options_list_content "]"
#line 642 "netconf_parser.yy"
                                                                    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1425 "netconf_parser.cc"
    break;

  case 147: // $@30: %empty
#line 651 "netconf_parser.yy"
                             {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1435 "netconf_parser.cc"
    break;

  case 148: // output_entry: "{" $@30 output_params_list "}"
#line 655 "netconf_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 1443 "netconf_parser.cc"
    break;

  case 156: // $@31: %empty
#line 670 "netconf_parser.yy"
               {
    ctx.unique("output", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1452 "netconf_parser.cc"
    break;

  case 157: // output: "output" $@31 ":" "constant string"
#line 673 "netconf_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 1462 "netconf_parser.cc"
    break;

  case 158: // flush: "flush" ":" "boolean"
#line 679 "netconf_parser.yy"
                           {
    ctx.unique("flush", ctx.loc2pos(yystack_[2].location));
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 1472 "netconf_parser.cc"
    break;

  case 159: // maxsize: "maxsize" ":" "integer"
#line 685 "netconf_parser.yy"
                               {
    ctx.unique("maxsize", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 1482 "netconf_parser.cc"
    break;

  case 160: // maxver: "maxver" ":" "integer"
#line 691 "netconf_parser.yy"
                             {
    ctx.unique("maxver", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 1492 "netconf_parser.cc"
    break;

  case 161: // $@32: %empty
#line 697 "netconf_parser.yy"
                 {
    ctx.unique("pattern", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1501 "netconf_parser.cc"
    break;

  case 162: // pattern: "pattern" $@32 ":" "constant string"
#line 700 "netconf_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pattern", sev);
    ctx.leave();
}
#line 1511 "netconf_parser.cc"
    break;


#line 1515 "netconf_parser.cc"

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


  const signed char NetconfParser::yypact_ninf_ = -77;

  const signed char NetconfParser::yytable_ninf_ = -1;

  const short
  NetconfParser::yypact_[] =
  {
      72,   -77,   -77,   -77,    30,    12,     9,    35,   -77,   -77,
     -77,   -77,   -77,   -77,   -77,   -77,   -77,   -77,   -77,   -77,
     -77,   -77,   -77,   -77,    12,    -2,    55,    -1,   -77,    63,
      74,    80,    71,    92,   -77,    95,   -77,   -77,   104,   116,
     121,   122,   -77,   -77,   123,   -77,    97,   125,   -77,   -77,
     -77,   -77,   -77,   -77,   -77,   -77,   -77,   -77,    12,    12,
     -77,    84,   126,   -77,   127,   128,    85,    86,    87,   129,
     133,   134,   -77,   -77,    -1,   -77,   -77,   135,   138,   139,
      96,   -77,   -77,   -77,   -77,   142,   143,   -77,    12,    -1,
     -77,   -77,   -77,    16,   144,   145,   -77,   132,   -77,   -77,
     -77,   -77,   -77,   141,   147,   -77,   -77,   -77,   -77,   -77,
     -77,   148,   150,   -77,   -77,    75,   -77,   -77,   151,   152,
     153,   154,   -77,    16,    -4,   -77,   144,    76,   145,   -77,
     155,   156,   157,   158,   -77,   -77,   -77,   -77,    17,   -77,
     -77,   -77,   -77,   -77,   -77,   162,   -77,   -77,   -77,   -77,
      21,   -77,   -77,   -77,   -77,   -77,   -77,    61,    61,    61,
      61,   163,   164,    23,   -77,   165,   166,   113,   167,    76,
     -77,   -77,   -77,   -77,   -77,   -77,   -77,   -77,   -77,    29,
     -77,   -77,   -77,    42,    43,    77,   115,   139,   -77,   130,
     168,   -77,   131,   -77,   170,   173,    61,   -77,   -77,   -77,
     -77,   -77,   -77,   -77,   171,   -77,   136,   172,   -77,   -77,
     101,   -77,   -77,    -5,    51,   171,   -77,   -77,   -77,   -77,
     -77,   -77,   -77,    90,   -77,   -77,   -77,   -77,   -77,   176,
     178,   179,   -77,    91,   -77,   -77,   -77,   -77,   -77,   -77,
     -77,   180,   181,   185,    -5,   -77,   186,   124,   146,   149,
     187,    51,   -77,    93,   159,   160,   -77,   161,   -77,   -77,
     -77,   169,   -77,   -77,   -77,   -77,   -77,   -77,   -77,   -77,
     -77
  };

  const unsigned char
  NetconfParser::yydefact_[] =
  {
       0,     2,     4,     6,     0,     0,     0,     0,     1,    25,
      18,    15,    14,    11,    12,    13,     3,    10,    16,    17,
      32,     5,     8,     7,    27,    21,     0,    36,    29,     0,
      28,     0,     0,    22,    34,     0,    52,    54,     0,     0,
       0,     0,    56,   123,     0,    48,     0,    37,    38,    40,
      41,    42,    46,    47,    44,    43,    45,    26,     0,     0,
      19,     0,     0,    33,     0,     0,     0,     0,     0,     0,
       0,     0,    31,     9,     0,    30,    23,     0,     0,     0,
       0,    49,    50,    51,    73,     0,     0,    39,     0,    36,
      20,    53,    55,    75,    58,     0,    24,     0,    84,    86,
      88,    90,    83,     0,    76,    77,    79,    80,    81,    82,
      62,     0,    59,    60,   127,     0,   125,    35,     0,     0,
       0,     0,    74,     0,     0,    57,     0,     0,     0,   124,
       0,     0,     0,     0,    78,    69,    71,    66,     0,    64,
      67,    68,    61,   138,   143,     0,   141,   137,   135,   136,
       0,   129,   131,   133,   134,   132,   126,     0,     0,     0,
       0,     0,     0,     0,    63,     0,     0,     0,     0,     0,
     128,   102,   104,   101,    95,    96,    97,    99,   100,     0,
      92,    94,    98,     0,     0,     0,     0,     0,    65,     0,
       0,   140,     0,   130,     0,     0,     0,    85,    87,    89,
      91,    70,    72,   139,     0,   142,     0,     0,    93,   147,
       0,   145,   103,     0,     0,     0,   144,   114,   119,   121,
     113,   111,   112,     0,   106,   108,   109,   110,   156,     0,
       0,     0,   161,     0,   149,   151,   152,   153,   154,   155,
     146,     0,     0,     0,     0,   105,     0,     0,     0,     0,
       0,     0,   148,     0,     0,     0,   107,     0,   158,   159,
     160,     0,   150,   116,   117,   118,   115,   120,   122,   157,
     162
  };

  const short
  NetconfParser::yypgoto_[] =
  {
     -77,   -77,   -77,   -77,   -77,   -77,   -77,   -77,   -20,   -76,
     -77,     6,   -77,   -77,   -77,   -77,   -77,   -77,   -27,   -77,
     -77,   -77,   -77,   105,   -77,   137,   -22,   -19,   -18,   -26,
     -77,   -25,   -77,   -77,   -77,   -77,   -77,    70,   -77,   -77,
      34,   -77,   -77,   -77,   -77,   -77,   -77,   -77,   -77,    38,
     -77,   -77,   -77,   -77,   -77,   -77,   -77,   -77,   -36,     2,
     -77,   -77,   -77,   -77,   -77,   -45,   -77,   -77,   -77,   -77,
     -77,   -77,   -77,   -77,   -77,   -77,    73,   -77,   -77,    31,
     -77,   -77,   -77,   -77,   -77,   -77,   -77,   -77,   -13,   -77,
     -77,   -48,   -77,   -77,   -77,   -77,   -77,   -77,   -77
  };

  const short
  NetconfParser::yydefgoto_[] =
  {
       0,     4,     5,     6,     7,    23,    27,    16,    17,    18,
      25,    91,    32,    33,    19,    24,    29,    30,   173,    21,
      26,    35,    62,    46,    47,    48,   174,   175,   176,   177,
      64,   178,    65,    54,    70,   111,   112,   113,   124,   138,
     139,   140,   161,   141,   162,    55,    93,   103,   104,   105,
     106,   118,   107,   119,   108,   120,   109,   121,   179,   180,
     181,   194,   182,   195,   223,   224,   225,   241,   266,   226,
     242,   227,   243,    56,    71,   115,   116,   127,   150,   151,
     152,   165,   153,   154,   168,   155,   166,   210,   211,   214,
     233,   234,   235,   246,   236,   237,   238,   239,   250
  };

  const short
  NetconfParser::yytable_[] =
  {
      45,    52,    53,    90,    28,    49,    36,    37,    50,    51,
      36,    37,    38,    39,    40,    41,    20,     9,   217,    10,
     163,    11,   218,   219,   169,   164,   135,   136,    42,   170,
       8,    43,   196,    98,    99,   100,   101,   197,    75,    76,
      44,    44,    22,    31,    44,   196,   196,    45,    52,    53,
     198,   199,    49,   135,   136,    50,    51,    12,    13,    14,
      15,    44,    45,    52,    53,    34,   102,    49,    96,    57,
      50,    51,    36,    37,    38,    39,    40,    58,   128,    60,
     196,   129,   171,   172,    59,   200,   228,    36,    37,   229,
     230,   231,   232,   244,   251,    61,   102,   137,   245,   252,
     147,   148,   149,    63,   215,    73,    44,   216,    66,   143,
     144,    90,   145,   146,     1,     2,     3,   263,   264,   265,
      67,    44,   183,   184,   185,    68,    69,    72,    74,    77,
      78,    79,    80,    81,    82,    83,    84,    85,    86,    88,
     117,    92,   147,   148,   149,    89,    10,    94,    95,   122,
     123,   110,   114,   126,   125,   130,   131,   132,   133,   191,
     201,   134,   157,   158,   159,   160,   167,   186,   187,   189,
     190,   192,   258,   204,   206,   203,   205,   207,   209,   213,
     247,   212,   248,   249,   253,   254,   220,   221,   222,   255,
     257,   261,   259,   202,    97,   260,   142,   188,   208,   256,
     193,   156,   240,   262,   267,   268,   269,     0,     0,     0,
       0,    87,     0,     0,   270,     0,     0,   220,   221,   222
  };

  const short
  NetconfParser::yycheck_[] =
  {
      27,    27,    27,    79,    24,    27,    11,    12,    27,    27,
      11,    12,    13,    14,    15,    16,     7,     5,    23,     7,
       3,     9,    27,    28,     3,     8,    30,    31,    29,     8,
       0,    32,     3,    17,    18,    19,    20,     8,    58,    59,
      45,    45,     7,    45,    45,     3,     3,    74,    74,    74,
       8,     8,    74,    30,    31,    74,    74,    45,    46,    47,
      48,    45,    89,    89,    89,    10,    93,    89,    88,     6,
      89,    89,    11,    12,    13,    14,    15,     3,     3,     8,
       3,     6,    21,    22,     4,     8,    35,    11,    12,    38,
      39,    40,    41,     3,     3,     3,   123,   124,     8,     8,
     127,   127,   127,     8,     3,     8,    45,     6,     4,    33,
      34,   187,    36,    37,    42,    43,    44,    24,    25,    26,
       4,    45,   158,   159,   160,     4,     4,     4,     3,    45,
       4,     4,     4,    48,    48,    48,     7,     4,     4,     4,
       8,    45,   169,   169,   169,     7,     7,     5,     5,     8,
       3,     7,     7,     3,     6,     4,     4,     4,     4,    46,
      45,   123,     7,     7,     7,     7,     4,     4,     4,     4,
       4,     4,    48,     5,     4,    45,    45,     4,     7,     7,
       4,    45,     4,     4,     4,     4,   213,   213,   213,     4,
       4,     4,    46,   187,    89,    46,   126,   163,   196,   244,
     169,   128,   215,   251,    45,    45,    45,    -1,    -1,    -1,
      -1,    74,    -1,    -1,    45,    -1,    -1,   244,   244,   244
  };

  const unsigned char
  NetconfParser::yystos_[] =
  {
       0,    42,    43,    44,    50,    51,    52,    53,     0,     5,
       7,     9,    45,    46,    47,    48,    56,    57,    58,    63,
       7,    68,     7,    54,    64,    59,    69,    55,    57,    65,
      66,    45,    61,    62,    10,    70,    11,    12,    13,    14,
      15,    16,    29,    32,    45,    67,    72,    73,    74,    75,
      76,    77,    78,    80,    82,    94,   122,     6,     3,     4,
       8,     3,    71,     8,    79,    81,     4,     4,     4,     4,
      83,   123,     4,     8,     3,    57,    57,    45,     4,     4,
       4,    48,    48,    48,     7,     4,     4,    74,     4,     7,
      58,    60,    45,    95,     5,     5,    57,    72,    17,    18,
      19,    20,    67,    96,    97,    98,    99,   101,   103,   105,
       7,    84,    85,    86,     7,   124,   125,     8,   100,   102,
     104,   106,     8,     3,    87,     6,     3,   126,     3,     6,
       4,     4,     4,     4,    98,    30,    31,    67,    88,    89,
      90,    92,    86,    33,    34,    36,    37,    67,    78,    80,
     127,   128,   129,   131,   132,   134,   125,     7,     7,     7,
       7,    91,    93,     3,     8,   130,   135,     4,   133,     3,
       8,    21,    22,    67,    75,    76,    77,    78,    80,   107,
     108,   109,   111,   107,   107,   107,     4,     4,    89,     4,
       4,    46,     4,   128,   110,   112,     3,     8,     8,     8,
       8,    45,    60,    45,     5,    45,     4,     4,   108,     7,
     136,   137,    45,     7,   138,     3,     6,    23,    27,    28,
      67,    78,    80,   113,   114,   115,   118,   120,    35,    38,
      39,    40,    41,   139,   140,   141,   143,   144,   145,   146,
     137,   116,   119,   121,     3,     8,   142,     4,     4,     4,
     147,     3,     8,     4,     4,     4,   114,     4,    48,    46,
      46,     4,   140,    24,    25,    26,   117,    45,    45,    45,
      45
  };

  const unsigned char
  NetconfParser::yyr1_[] =
  {
       0,    49,    51,    50,    52,    50,    53,    50,    55,    54,
      56,    57,    57,    57,    57,    57,    57,    57,    59,    58,
      60,    61,    61,    62,    62,    64,    63,    65,    65,    66,
      66,    67,    69,    68,    71,    70,    72,    72,    73,    73,
      74,    74,    74,    74,    74,    74,    74,    74,    74,    75,
      76,    77,    79,    78,    81,    80,    83,    82,    84,    84,
      85,    85,    87,    86,    88,    88,    88,    89,    89,    91,
      90,    93,    92,    95,    94,    96,    96,    97,    97,    98,
      98,    98,    98,    98,   100,    99,   102,   101,   104,   103,
     106,   105,   107,   107,   108,   108,   108,   108,   108,   108,
     108,   108,   110,   109,   112,   111,   113,   113,   114,   114,
     114,   114,   114,   114,   116,   115,   117,   117,   117,   119,
     118,   121,   120,   123,   122,   124,   124,   126,   125,   127,
     127,   128,   128,   128,   128,   128,   128,   128,   130,   129,
     131,   133,   132,   135,   134,   136,   136,   138,   137,   139,
     139,   140,   140,   140,   140,   140,   142,   141,   143,   144,
     145,   147,   146
  };

  const signed char
  NetconfParser::yyr2_[] =
  {
       0,     2,     0,     3,     0,     3,     0,     3,     0,     4,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       1,     0,     1,     3,     5,     0,     4,     0,     1,     1,
       3,     2,     0,     4,     0,     6,     0,     1,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       3,     3,     0,     4,     0,     4,     0,     6,     0,     1,
       1,     3,     0,     4,     1,     3,     1,     1,     1,     0,
       4,     0,     4,     0,     6,     0,     1,     1,     3,     1,
       1,     1,     1,     1,     0,     6,     0,     6,     0,     6,
       0,     6,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     0,     6,     1,     3,     1,     1,
       1,     1,     1,     1,     0,     4,     1,     1,     1,     0,
       4,     0,     4,     0,     6,     1,     3,     0,     4,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       3,     0,     4,     0,     6,     1,     3,     0,     4,     1,
       3,     1,     1,     1,     1,     1,     0,     4,     3,     3,
       3,     0,     4
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
  "netconf_syntax_map", "$@7", "global_object", "$@8", "global_params",
  "not_empty_global_params", "global_param", "boot_update",
  "subscribe_changes", "validate_changes", "user_context", "$@9",
  "comment", "$@10", "hooks_libraries", "$@11", "hooks_libraries_list",
  "not_empty_hooks_libraries_list", "hooks_library", "$@12",
  "hooks_params", "hooks_param", "library", "$@13", "parameters", "$@14",
  "managed_servers", "$@15", "servers_entries",
  "not_empty_servers_entries", "server_entry", "dhcp4_server", "$@16",
  "dhcp6_server", "$@17", "d2_server", "$@18", "ca_server", "$@19",
  "managed_server_params", "managed_server_param", "model", "$@20",
  "control_socket", "$@21", "control_socket_params",
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
     166,   171,   172,   180,   185,   193,   193,   199,   200,   203,
     207,   220,   228,   228,   240,   240,   260,   261,   264,   265,
     270,   271,   272,   273,   274,   275,   276,   277,   278,   281,
     287,   293,   299,   299,   324,   324,   352,   352,   363,   364,
     367,   368,   371,   371,   379,   380,   381,   384,   385,   388,
     388,   397,   397,   408,   408,   419,   420,   423,   424,   430,
     431,   432,   433,   434,   438,   438,   450,   450,   462,   462,
     474,   474,   486,   487,   491,   492,   493,   494,   495,   496,
     497,   498,   502,   502,   512,   512,   524,   525,   528,   529,
     530,   531,   532,   533,   536,   536,   545,   546,   547,   550,
     550,   560,   560,   573,   573,   586,   587,   591,   591,   599,
     600,   603,   604,   605,   606,   607,   608,   609,   612,   612,
     621,   627,   627,   636,   636,   647,   648,   651,   651,   659,
     660,   663,   664,   665,   666,   667,   670,   670,   679,   685,
     691,   697,   697
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
#line 2195 "netconf_parser.cc"

#line 706 "netconf_parser.yy"


void
isc::netconf::NetconfParser::error(const location_type& loc,
                               const std::string& what)
{
    ctx.error(loc, what);
}
