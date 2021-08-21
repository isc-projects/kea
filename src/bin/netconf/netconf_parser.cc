// A Bison parser, made by GNU Bison 3.7.6.

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

  /*---------------.
  | symbol kinds.  |
  `---------------*/



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
  NetconfParser::yypop_ (int n)
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
  NetconfParser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  NetconfParser::yy_table_value_is_error_ (int yyvalue)
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
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 812 "netconf_parser.cc"
    break;

  case 24: // not_empty_map: not_empty_map "," "constant string" ":" value
#line 184 "netconf_parser.yy"
                                                      {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 822 "netconf_parser.cc"
    break;

  case 25: // $@6: %empty
#line 191 "netconf_parser.yy"
                              {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 831 "netconf_parser.cc"
    break;

  case 26: // list_generic: "[" $@6 list_content "]"
#line 194 "netconf_parser.yy"
                               {
}
#line 838 "netconf_parser.cc"
    break;

  case 29: // not_empty_list: value
#line 201 "netconf_parser.yy"
                      {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 847 "netconf_parser.cc"
    break;

  case 30: // not_empty_list: not_empty_list "," value
#line 205 "netconf_parser.yy"
                                           {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 856 "netconf_parser.cc"
    break;

  case 31: // unknown_map_entry: "constant string" ":"
#line 218 "netconf_parser.yy"
                                {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as < std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 867 "netconf_parser.cc"
    break;

  case 32: // $@7: %empty
#line 226 "netconf_parser.yy"
                                   {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 878 "netconf_parser.cc"
    break;

  case 33: // netconf_syntax_map: "{" $@7 global_objects "}"
#line 231 "netconf_parser.yy"
                                {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 888 "netconf_parser.cc"
    break;

  case 37: // $@8: %empty
#line 247 "netconf_parser.yy"
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
#line 907 "netconf_parser.cc"
    break;

  case 38: // netconf_object: "Netconf" $@8 ":" "{" global_params "}"
#line 260 "netconf_parser.yy"
                                                    {
    // Ok, we're done with parsing Netconf. Let's take the map
    // off the stack.
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 918 "netconf_parser.cc"
    break;

  case 52: // boot_update: "boot-update" ":" "boolean"
#line 288 "netconf_parser.yy"
                                       {
    ElementPtr flag(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("boot-update", flag);
}
#line 927 "netconf_parser.cc"
    break;

  case 53: // subscribe_changes: "subscribe-changes" ":" "boolean"
#line 293 "netconf_parser.yy"
                                                   {
    ElementPtr flag(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subscribe-changes", flag);
}
#line 936 "netconf_parser.cc"
    break;

  case 54: // validate_changes: "validate-changes" ":" "boolean"
#line 298 "netconf_parser.yy"
                                                 {
    ElementPtr flag(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("validate-changes", flag);
}
#line 945 "netconf_parser.cc"
    break;

  case 55: // $@9: %empty
#line 303 "netconf_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 953 "netconf_parser.cc"
    break;

  case 56: // user_context: "user-context" $@9 ":" map_value
#line 305 "netconf_parser.yy"
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
#line 980 "netconf_parser.cc"
    break;

  case 57: // $@10: %empty
#line 328 "netconf_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 988 "netconf_parser.cc"
    break;

  case 58: // comment: "comment" $@10 ":" "constant string"
#line 330 "netconf_parser.yy"
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
#line 1017 "netconf_parser.cc"
    break;

  case 59: // $@11: %empty
#line 356 "netconf_parser.yy"
                                 {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1028 "netconf_parser.cc"
    break;

  case 60: // hooks_libraries: "hooks-libraries" $@11 ":" "[" hooks_libraries_list "]"
#line 361 "netconf_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1037 "netconf_parser.cc"
    break;

  case 65: // $@12: %empty
#line 374 "netconf_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1047 "netconf_parser.cc"
    break;

  case 66: // hooks_library: "{" $@12 hooks_params "}"
#line 378 "netconf_parser.yy"
                              {
    ctx.stack_.pop_back();
}
#line 1055 "netconf_parser.cc"
    break;

  case 72: // $@13: %empty
#line 391 "netconf_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1063 "netconf_parser.cc"
    break;

  case 73: // library: "library" $@13 ":" "constant string"
#line 393 "netconf_parser.yy"
               {
    ElementPtr lib(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1073 "netconf_parser.cc"
    break;

  case 74: // $@14: %empty
#line 399 "netconf_parser.yy"
                       {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1081 "netconf_parser.cc"
    break;

  case 75: // parameters: "parameters" $@14 ":" map_value
#line 401 "netconf_parser.yy"
                  {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1090 "netconf_parser.cc"
    break;

  case 76: // $@15: %empty
#line 409 "netconf_parser.yy"
                                                      {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[2].location)));
    ctx.stack_.back()->set("managed-servers", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.MANAGED_SERVERS);
}
#line 1101 "netconf_parser.cc"
    break;

  case 77: // managed_servers: "managed-servers" ":" "{" $@15 servers_entries "}"
#line 414 "netconf_parser.yy"
                                 {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1110 "netconf_parser.cc"
    break;

  case 87: // $@16: %empty
#line 438 "netconf_parser.yy"
                           {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER);
}
#line 1121 "netconf_parser.cc"
    break;

  case 88: // dhcp4_server: "dhcp4" $@16 ":" "{" managed_server_params "}"
#line 443 "netconf_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1130 "netconf_parser.cc"
    break;

  case 89: // $@17: %empty
#line 449 "netconf_parser.yy"
                           {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp6", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER);
}
#line 1141 "netconf_parser.cc"
    break;

  case 90: // dhcp6_server: "dhcp6" $@17 ":" "{" managed_server_params "}"
#line 454 "netconf_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1150 "netconf_parser.cc"
    break;

  case 91: // $@18: %empty
#line 460 "netconf_parser.yy"
                     {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("d2", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER);
}
#line 1161 "netconf_parser.cc"
    break;

  case 92: // d2_server: "d2" $@18 ":" "{" managed_server_params "}"
#line 465 "netconf_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1170 "netconf_parser.cc"
    break;

  case 93: // $@19: %empty
#line 471 "netconf_parser.yy"
                     {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ca", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER);
}
#line 1181 "netconf_parser.cc"
    break;

  case 94: // ca_server: "ca" $@19 ":" "{" managed_server_params "}"
#line 476 "netconf_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1190 "netconf_parser.cc"
    break;

  case 105: // $@20: %empty
#line 498 "netconf_parser.yy"
             {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1198 "netconf_parser.cc"
    break;

  case 106: // model: "model" $@20 ":" "constant string"
#line 500 "netconf_parser.yy"
               {
    ElementPtr model(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("model", model);
    ctx.leave();
}
#line 1208 "netconf_parser.cc"
    break;

  case 107: // $@21: %empty
#line 507 "netconf_parser.yy"
                               {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 1219 "netconf_parser.cc"
    break;

  case 108: // control_socket: "control-socket" $@21 ":" "{" control_socket_params "}"
#line 512 "netconf_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1228 "netconf_parser.cc"
    break;

  case 117: // $@22: %empty
#line 530 "netconf_parser.yy"
                         {
    ctx.enter(ctx.SOCKET_TYPE);
}
#line 1236 "netconf_parser.cc"
    break;

  case 118: // socket_type: "socket-type" $@22 ":" socket_type_value
#line 532 "netconf_parser.yy"
                          {
    ctx.stack_.back()->set("socket-type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1245 "netconf_parser.cc"
    break;

  case 119: // socket_type_value: "unix"
#line 538 "netconf_parser.yy"
                         { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("unix", ctx.loc2pos(yystack_[0].location))); }
#line 1251 "netconf_parser.cc"
    break;

  case 120: // socket_type_value: "http"
#line 539 "netconf_parser.yy"
                         { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("http", ctx.loc2pos(yystack_[0].location))); }
#line 1257 "netconf_parser.cc"
    break;

  case 121: // socket_type_value: "stdout"
#line 540 "netconf_parser.yy"
                           { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("stdout", ctx.loc2pos(yystack_[0].location))); }
#line 1263 "netconf_parser.cc"
    break;

  case 122: // $@23: %empty
#line 543 "netconf_parser.yy"
                         {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1271 "netconf_parser.cc"
    break;

  case 123: // socket_name: "socket-name" $@23 ":" "constant string"
#line 545 "netconf_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 1281 "netconf_parser.cc"
    break;

  case 124: // $@24: %empty
#line 552 "netconf_parser.yy"
                       {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1289 "netconf_parser.cc"
    break;

  case 125: // socket_url: "socket-url" $@24 ":" "constant string"
#line 554 "netconf_parser.yy"
               {
    ElementPtr url(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-url", url);
    ctx.leave();
}
#line 1299 "netconf_parser.cc"
    break;

  case 126: // $@25: %empty
#line 564 "netconf_parser.yy"
                 {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 1310 "netconf_parser.cc"
    break;

  case 127: // loggers: "loggers" $@25 ":" "[" loggers_entries "]"
#line 569 "netconf_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1319 "netconf_parser.cc"
    break;

  case 130: // $@26: %empty
#line 581 "netconf_parser.yy"
                             {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 1329 "netconf_parser.cc"
    break;

  case 131: // logger_entry: "{" $@26 logger_params "}"
#line 585 "netconf_parser.yy"
                               {
    ctx.stack_.pop_back();
}
#line 1337 "netconf_parser.cc"
    break;

  case 141: // $@27: %empty
#line 602 "netconf_parser.yy"
           {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1345 "netconf_parser.cc"
    break;

  case 142: // name: "name" $@27 ":" "constant string"
#line 604 "netconf_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1355 "netconf_parser.cc"
    break;

  case 143: // debuglevel: "debuglevel" ":" "integer"
#line 610 "netconf_parser.yy"
                                     {
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 1364 "netconf_parser.cc"
    break;

  case 144: // $@28: %empty
#line 615 "netconf_parser.yy"
                   {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1372 "netconf_parser.cc"
    break;

  case 145: // severity: "severity" $@28 ":" "constant string"
#line 617 "netconf_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 1382 "netconf_parser.cc"
    break;

  case 146: // $@29: %empty
#line 623 "netconf_parser.yy"
                                    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 1393 "netconf_parser.cc"
    break;

  case 147: // output_options_list: "output_options" $@29 ":" "[" output_options_list_content "]"
#line 628 "netconf_parser.yy"
                                                                    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1402 "netconf_parser.cc"
    break;

  case 150: // $@30: %empty
#line 637 "netconf_parser.yy"
                             {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1412 "netconf_parser.cc"
    break;

  case 151: // output_entry: "{" $@30 output_params_list "}"
#line 641 "netconf_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 1420 "netconf_parser.cc"
    break;

  case 159: // $@31: %empty
#line 656 "netconf_parser.yy"
               {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1428 "netconf_parser.cc"
    break;

  case 160: // output: "output" $@31 ":" "constant string"
#line 658 "netconf_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 1438 "netconf_parser.cc"
    break;

  case 161: // flush: "flush" ":" "boolean"
#line 664 "netconf_parser.yy"
                           {
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 1447 "netconf_parser.cc"
    break;

  case 162: // maxsize: "maxsize" ":" "integer"
#line 669 "netconf_parser.yy"
                               {
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 1456 "netconf_parser.cc"
    break;

  case 163: // maxver: "maxver" ":" "integer"
#line 674 "netconf_parser.yy"
                             {
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 1465 "netconf_parser.cc"
    break;

  case 164: // $@32: %empty
#line 679 "netconf_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORDS);
}
#line 1473 "netconf_parser.cc"
    break;

  case 165: // pattern: "pattern" $@32 ":" "constant string"
#line 681 "netconf_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pattern", sev);
    ctx.leave();
}
#line 1483 "netconf_parser.cc"
    break;


#line 1487 "netconf_parser.cc"

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

    int yyn = yypact_[+yyparser_.yystack_[0].state];
    if (!yy_pact_value_is_default_ (yyn))
      {
        /* Start YYX at -YYN if negative to avoid negative indexes in
           YYCHECK.  In other words, skip the first -YYN actions for
           this state because they are default actions.  */
        int yyxbegin = yyn < 0 ? -yyn : 0;
        // Stay within bounds of both yycheck and yytname.
        int yychecklim = yylast_ - yyn + 1;
        int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
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


  const signed char NetconfParser::yypact_ninf_ = -81;

  const signed char NetconfParser::yytable_ninf_ = -1;

  const short
  NetconfParser::yypact_[] =
  {
      73,   -81,   -81,   -81,    27,    15,    25,    57,   -81,   -81,
     -81,   -81,   -81,   -81,   -81,   -81,   -81,   -81,   -81,   -81,
     -81,   -81,   -81,   -81,    15,   -12,    43,    -1,   -81,    59,
      70,    76,    75,    86,   -81,    22,   -81,   -81,   -81,   -81,
     120,   121,   122,   123,   -81,   -81,   124,   -81,    91,   126,
     -81,   -81,   -81,   -81,   -81,   -81,   -81,   -81,   -81,   -81,
      15,    15,   -81,    85,   127,    43,   -81,   128,   129,    87,
      88,    89,   131,   130,   135,   -81,   -81,    -1,   -81,   -81,
     136,   134,   -81,   137,    97,   -81,   -81,   -81,   -81,   138,
     140,   -81,    15,    -1,   -81,   -81,   -81,    67,   142,   143,
     -81,   144,   -81,   -81,   -81,   -81,   -81,   145,   148,   -81,
     -81,   -81,   -81,   -81,   -81,   149,   151,   -81,   -81,    13,
     -81,   -81,   152,   153,   154,   155,   -81,    67,   -24,   -81,
     142,    45,   143,   -81,   156,   157,   158,   159,   -81,   -81,
     -81,   -81,    26,   -81,   -81,   -81,   -81,   -81,   -81,   163,
     -81,   -81,   -81,   -81,    39,   -81,   -81,   -81,   -81,   -81,
     -81,    24,    24,    24,    24,   164,   165,   -13,   -81,   166,
     167,   114,   168,    45,   -81,   -81,   -81,   -81,   -81,   -81,
     -81,   -81,   -81,    40,   -81,   -81,   -81,    46,    95,    99,
     116,   137,   -81,   117,   169,   -81,   132,   -81,   171,   172,
      24,   -81,   -81,   -81,   -81,   -81,   -81,   -81,   173,   -81,
     133,   174,   -81,   -81,    20,   -81,   -81,    65,    56,   173,
     -81,   -81,   -81,   -81,   -81,   -81,   -81,   105,   -81,   -81,
     -81,   -81,   -81,   175,   178,   179,   -81,   106,   -81,   -81,
     -81,   -81,   -81,   -81,   -81,   180,   181,   182,    65,   -81,
     183,   125,   147,   150,   184,    56,   -81,    94,   160,   161,
     -81,   162,   -81,   -81,   -81,   170,   -81,   -81,   -81,   -81,
     -81,   -81,   -81,   -81,   -81
  };

  const unsigned char
  NetconfParser::yydefact_[] =
  {
       0,     2,     4,     6,     0,     0,     0,     0,     1,    25,
      18,    15,    14,    11,    12,    13,     3,    10,    16,    17,
      32,     5,     8,     7,    27,    21,     0,    39,    29,     0,
      28,     0,     0,    22,    37,     0,    34,    36,    55,    57,
       0,     0,     0,     0,    59,   126,     0,    51,     0,    40,
      41,    43,    44,    45,    49,    50,    47,    46,    48,    26,
       0,     0,    19,     0,     0,     0,    33,     0,     0,     0,
       0,     0,     0,     0,     0,    31,     9,     0,    30,    23,
       0,     0,    35,     0,     0,    52,    53,    54,    76,     0,
       0,    42,     0,    39,    20,    56,    58,    78,    61,     0,
      24,     0,    87,    89,    91,    93,    86,     0,    79,    80,
      82,    83,    84,    85,    65,     0,    62,    63,   130,     0,
     128,    38,     0,     0,     0,     0,    77,     0,     0,    60,
       0,     0,     0,   127,     0,     0,     0,     0,    81,    72,
      74,    69,     0,    67,    70,    71,    64,   141,   146,     0,
     144,   140,   138,   139,     0,   132,   134,   136,   137,   135,
     129,     0,     0,     0,     0,     0,     0,     0,    66,     0,
       0,     0,     0,     0,   131,   105,   107,   104,    98,    99,
     100,   102,   103,     0,    95,    97,   101,     0,     0,     0,
       0,     0,    68,     0,     0,   143,     0,   133,     0,     0,
       0,    88,    90,    92,    94,    73,    75,   142,     0,   145,
       0,     0,    96,   150,     0,   148,   106,     0,     0,     0,
     147,   117,   122,   124,   116,   114,   115,     0,   109,   111,
     112,   113,   159,     0,     0,     0,   164,     0,   152,   154,
     155,   156,   157,   158,   149,     0,     0,     0,     0,   108,
       0,     0,     0,     0,     0,     0,   151,     0,     0,     0,
     110,     0,   161,   162,   163,     0,   153,   119,   120,   121,
     118,   123,   125,   160,   165
  };

  const short
  NetconfParser::yypgoto_[] =
  {
     -81,   -81,   -81,   -81,   -81,   -81,   -81,   -81,   -20,   -80,
     -81,    -2,   -81,   -81,   -81,   -81,   -81,   -81,   -27,   -81,
     -81,   -81,   139,   -81,   -81,   101,   -81,   118,   -22,   -19,
     -18,   -26,   -81,   -25,   -81,   -81,   -81,   -81,   -81,    68,
     -81,   -81,    30,   -81,   -81,   -81,   -81,   -81,   -81,   -81,
     -81,    72,   -81,   -81,   -81,   -81,   -81,   -81,   -81,   -81,
     -41,     0,   -81,   -81,   -81,   -81,   -81,   -47,   -81,   -81,
     -81,   -81,   -81,   -81,   -81,   -81,   -81,   -81,    71,   -81,
     -81,    29,   -81,   -81,   -81,   -81,   -81,   -81,   -81,   -81,
     -11,   -81,   -81,   -46,   -81,   -81,   -81,   -81,   -81,   -81,
     -81
  };

  const short
  NetconfParser::yydefgoto_[] =
  {
       0,     4,     5,     6,     7,    23,    27,    16,    17,    18,
      25,    95,    32,    33,    19,    24,    29,    30,   177,    21,
      26,    35,    36,    37,    64,    48,    49,    50,   178,   179,
     180,   181,    67,   182,    68,    56,    73,   115,   116,   117,
     128,   142,   143,   144,   165,   145,   166,    57,    97,   107,
     108,   109,   110,   122,   111,   123,   112,   124,   113,   125,
     183,   184,   185,   198,   186,   199,   227,   228,   229,   245,
     270,   230,   246,   231,   247,    58,    74,   119,   120,   131,
     154,   155,   156,   169,   157,   158,   172,   159,   170,   214,
     215,   218,   237,   238,   239,   250,   240,   241,   242,   243,
     254
  };

  const short
  NetconfParser::yytable_[] =
  {
      47,    54,    55,    94,    28,    51,   139,   140,    52,    53,
      38,    39,    40,    41,    42,    43,   132,   139,   140,   133,
       9,    46,    10,   219,    11,    65,   220,     8,    44,   167,
      66,    45,    20,    31,   168,    38,    39,    40,    41,    42,
      78,    79,   173,   200,    46,   175,   176,   174,   201,   200,
      47,    54,    55,    34,   202,    51,    38,    39,    52,    53,
      12,    13,    14,    15,    22,    59,    47,    54,    55,    46,
     106,    51,   100,    60,    52,    53,    38,    39,   147,   148,
      61,   149,   150,    62,   102,   103,   104,   105,   221,    63,
      46,   232,   222,   223,   233,   234,   235,   236,   200,    76,
     106,   141,   200,   203,   151,   152,   153,   204,   248,   255,
      46,    94,    46,   249,   256,     1,     2,     3,   267,   268,
     269,   187,   188,   189,    69,    70,    71,    72,    75,    77,
      80,    81,    83,    84,    89,    85,    86,    87,    88,    90,
      92,    93,    96,    98,    10,    99,   151,   152,   153,   114,
     118,   127,   121,   126,   130,   129,   134,   135,   136,   137,
     195,   205,   207,   161,   162,   163,   164,   171,   190,   191,
     193,   194,   196,   262,   208,   210,   211,   209,   216,   251,
     213,   217,   252,   253,   257,   258,   259,   261,   265,   206,
     224,   225,   226,   263,   101,    91,   264,   192,   146,   138,
     212,   260,   197,   160,    82,   271,   272,   273,   244,   266,
       0,     0,     0,     0,     0,   274,     0,     0,     0,     0,
       0,   224,   225,   226
  };

  const short
  NetconfParser::yycheck_[] =
  {
      27,    27,    27,    83,    24,    27,    30,    31,    27,    27,
      11,    12,    13,    14,    15,    16,     3,    30,    31,     6,
       5,    45,     7,     3,     9,     3,     6,     0,    29,     3,
       8,    32,     7,    45,     8,    11,    12,    13,    14,    15,
      60,    61,     3,     3,    45,    21,    22,     8,     8,     3,
      77,    77,    77,    10,     8,    77,    11,    12,    77,    77,
      45,    46,    47,    48,     7,     6,    93,    93,    93,    45,
      97,    93,    92,     3,    93,    93,    11,    12,    33,    34,
       4,    36,    37,     8,    17,    18,    19,    20,    23,     3,
      45,    35,    27,    28,    38,    39,    40,    41,     3,     8,
     127,   128,     3,     8,   131,   131,   131,     8,     3,     3,
      45,   191,    45,     8,     8,    42,    43,    44,    24,    25,
      26,   162,   163,   164,     4,     4,     4,     4,     4,     3,
      45,     4,     4,     4,     4,    48,    48,    48,     7,     4,
       4,     7,    45,     5,     7,     5,   173,   173,   173,     7,
       7,     3,     8,     8,     3,     6,     4,     4,     4,     4,
      46,    45,    45,     7,     7,     7,     7,     4,     4,     4,
       4,     4,     4,    48,     5,     4,     4,    45,    45,     4,
       7,     7,     4,     4,     4,     4,     4,     4,     4,   191,
     217,   217,   217,    46,    93,    77,    46,   167,   130,   127,
     200,   248,   173,   132,    65,    45,    45,    45,   219,   255,
      -1,    -1,    -1,    -1,    -1,    45,    -1,    -1,    -1,    -1,
      -1,   248,   248,   248
  };

  const unsigned char
  NetconfParser::yystos_[] =
  {
       0,    42,    43,    44,    50,    51,    52,    53,     0,     5,
       7,     9,    45,    46,    47,    48,    56,    57,    58,    63,
       7,    68,     7,    54,    64,    59,    69,    55,    57,    65,
      66,    45,    61,    62,    10,    70,    71,    72,    11,    12,
      13,    14,    15,    16,    29,    32,    45,    67,    74,    75,
      76,    77,    78,    79,    80,    82,    84,    96,   124,     6,
       3,     4,     8,     3,    73,     3,     8,    81,    83,     4,
       4,     4,     4,    85,   125,     4,     8,     3,    57,    57,
      45,     4,    71,     4,     4,    48,    48,    48,     7,     4,
       4,    76,     4,     7,    58,    60,    45,    97,     5,     5,
      57,    74,    17,    18,    19,    20,    67,    98,    99,   100,
     101,   103,   105,   107,     7,    86,    87,    88,     7,   126,
     127,     8,   102,   104,   106,   108,     8,     3,    89,     6,
       3,   128,     3,     6,     4,     4,     4,     4,   100,    30,
      31,    67,    90,    91,    92,    94,    88,    33,    34,    36,
      37,    67,    80,    82,   129,   130,   131,   133,   134,   136,
     127,     7,     7,     7,     7,    93,    95,     3,     8,   132,
     137,     4,   135,     3,     8,    21,    22,    67,    77,    78,
      79,    80,    82,   109,   110,   111,   113,   109,   109,   109,
       4,     4,    91,     4,     4,    46,     4,   130,   112,   114,
       3,     8,     8,     8,     8,    45,    60,    45,     5,    45,
       4,     4,   110,     7,   138,   139,    45,     7,   140,     3,
       6,    23,    27,    28,    67,    80,    82,   115,   116,   117,
     120,   122,    35,    38,    39,    40,    41,   141,   142,   143,
     145,   146,   147,   148,   139,   118,   121,   123,     3,     8,
     144,     4,     4,     4,   149,     3,     8,     4,     4,     4,
     116,     4,    48,    46,    46,     4,   142,    24,    25,    26,
     119,    45,    45,    45,    45
  };

  const unsigned char
  NetconfParser::yyr1_[] =
  {
       0,    49,    51,    50,    52,    50,    53,    50,    55,    54,
      56,    57,    57,    57,    57,    57,    57,    57,    59,    58,
      60,    61,    61,    62,    62,    64,    63,    65,    65,    66,
      66,    67,    69,    68,    70,    70,    71,    73,    72,    74,
      74,    75,    75,    76,    76,    76,    76,    76,    76,    76,
      76,    76,    77,    78,    79,    81,    80,    83,    82,    85,
      84,    86,    86,    87,    87,    89,    88,    90,    90,    90,
      91,    91,    93,    92,    95,    94,    97,    96,    98,    98,
      99,    99,   100,   100,   100,   100,   100,   102,   101,   104,
     103,   106,   105,   108,   107,   109,   109,   110,   110,   110,
     110,   110,   110,   110,   110,   112,   111,   114,   113,   115,
     115,   116,   116,   116,   116,   116,   116,   118,   117,   119,
     119,   119,   121,   120,   123,   122,   125,   124,   126,   126,
     128,   127,   129,   129,   130,   130,   130,   130,   130,   130,
     130,   132,   131,   133,   135,   134,   137,   136,   138,   138,
     140,   139,   141,   141,   142,   142,   142,   142,   142,   144,
     143,   145,   146,   147,   149,   148
  };

  const signed char
  NetconfParser::yyr2_[] =
  {
       0,     2,     0,     3,     0,     3,     0,     3,     0,     4,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       1,     0,     1,     3,     5,     0,     4,     0,     1,     1,
       3,     2,     0,     4,     1,     3,     1,     0,     6,     0,
       1,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     3,     3,     0,     4,     0,     4,     0,
       6,     0,     1,     1,     3,     0,     4,     1,     3,     1,
       1,     1,     0,     4,     0,     4,     0,     6,     0,     1,
       1,     3,     1,     1,     1,     1,     1,     0,     6,     0,
       6,     0,     6,     0,     6,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     0,     6,     1,
       3,     1,     1,     1,     1,     1,     1,     0,     4,     1,
       1,     1,     0,     4,     0,     4,     0,     6,     1,     3,
       0,     4,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     3,     0,     4,     0,     6,     1,     3,
       0,     4,     1,     3,     1,     1,     1,     1,     1,     0,
       4,     3,     3,     3,     0,     4
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
  "netconf_syntax_map", "$@7", "global_objects", "global_object",
  "netconf_object", "$@8", "global_params", "not_empty_global_params",
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
     166,   171,   172,   180,   184,   191,   191,   197,   198,   201,
     205,   218,   226,   226,   238,   239,   243,   247,   247,   267,
     268,   271,   272,   277,   278,   279,   280,   281,   282,   283,
     284,   285,   288,   293,   298,   303,   303,   328,   328,   356,
     356,   366,   367,   370,   371,   374,   374,   382,   383,   384,
     387,   388,   391,   391,   399,   399,   409,   409,   419,   420,
     423,   424,   430,   431,   432,   433,   434,   438,   438,   449,
     449,   460,   460,   471,   471,   482,   483,   487,   488,   489,
     490,   491,   492,   493,   494,   498,   498,   507,   507,   518,
     519,   522,   523,   524,   525,   526,   527,   530,   530,   538,
     539,   540,   543,   543,   552,   552,   564,   564,   576,   577,
     581,   581,   589,   590,   593,   594,   595,   596,   597,   598,
     599,   602,   602,   610,   615,   615,   623,   623,   633,   634,
     637,   637,   645,   646,   649,   650,   651,   652,   653,   656,
     656,   664,   669,   674,   679,   679
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
#line 2168 "netconf_parser.cc"

#line 687 "netconf_parser.yy"


void
isc::netconf::NetconfParser::error(const location_type& loc,
                               const std::string& what)
{
    ctx.error(loc, what);
}
