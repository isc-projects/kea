// A Bison parser, made by GNU Bison 3.6.4.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2020 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

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
#define yylex   d2_parser_lex



#include "d2_parser.h"


// Unqualified %code blocks.
#line 34 "d2_parser.yy"

#include <d2/parser_context.h>

#line 52 "d2_parser.cc"


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
#if D2_PARSER_DEBUG

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

#else // !D2_PARSER_DEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !D2_PARSER_DEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 14 "d2_parser.yy"
namespace isc { namespace d2 {
#line 145 "d2_parser.cc"

  /// Build a parser object.
  D2Parser::D2Parser (isc::d2::D2ParserContext& ctx_yyarg)
#if D2_PARSER_DEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
#else
    :
#endif
      ctx (ctx_yyarg)
  {}

  D2Parser::~D2Parser ()
  {}

  D2Parser::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------------.
  | symbol kinds.  |
  `---------------*/



  // by_state.
  D2Parser::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

  D2Parser::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
  D2Parser::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
  D2Parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  D2Parser::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

  D2Parser::symbol_kind_type
  D2Parser::by_state::kind () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return symbol_kind::S_YYEMPTY;
    else
      return YY_CAST (symbol_kind_type, yystos_[+state]);
  }

  D2Parser::stack_symbol_type::stack_symbol_type ()
  {}

  D2Parser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state), YY_MOVE (that.location))
  {
    switch (that.kind ())
    {
      case 68: // value
      case 72: // map_value
      case 96: // ncr_protocol_value
        value.YY_MOVE_OR_COPY< ElementPtr > (YY_MOVE (that.value));
        break;

      case 56: // "boolean"
        value.YY_MOVE_OR_COPY< bool > (YY_MOVE (that.value));
        break;

      case 55: // "floating point"
        value.YY_MOVE_OR_COPY< double > (YY_MOVE (that.value));
        break;

      case 54: // "integer"
        value.YY_MOVE_OR_COPY< int64_t > (YY_MOVE (that.value));
        break;

      case 53: // "constant string"
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

  D2Parser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s, YY_MOVE (that.location))
  {
    switch (that.kind ())
    {
      case 68: // value
      case 72: // map_value
      case 96: // ncr_protocol_value
        value.move< ElementPtr > (YY_MOVE (that.value));
        break;

      case 56: // "boolean"
        value.move< bool > (YY_MOVE (that.value));
        break;

      case 55: // "floating point"
        value.move< double > (YY_MOVE (that.value));
        break;

      case 54: // "integer"
        value.move< int64_t > (YY_MOVE (that.value));
        break;

      case 53: // "constant string"
        value.move< std::string > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

    // that is emptied.
    that.kind_ = symbol_kind::S_YYEMPTY;
  }

#if YY_CPLUSPLUS < 201103L
  D2Parser::stack_symbol_type&
  D2Parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case 68: // value
      case 72: // map_value
      case 96: // ncr_protocol_value
        value.copy< ElementPtr > (that.value);
        break;

      case 56: // "boolean"
        value.copy< bool > (that.value);
        break;

      case 55: // "floating point"
        value.copy< double > (that.value);
        break;

      case 54: // "integer"
        value.copy< int64_t > (that.value);
        break;

      case 53: // "constant string"
        value.copy< std::string > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    return *this;
  }

  D2Parser::stack_symbol_type&
  D2Parser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case 68: // value
      case 72: // map_value
      case 96: // ncr_protocol_value
        value.move< ElementPtr > (that.value);
        break;

      case 56: // "boolean"
        value.move< bool > (that.value);
        break;

      case 55: // "floating point"
        value.move< double > (that.value);
        break;

      case 54: // "integer"
        value.move< int64_t > (that.value);
        break;

      case 53: // "constant string"
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
  D2Parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if D2_PARSER_DEBUG
  template <typename Base>
  void
  D2Parser::yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
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
      case 53: // "constant string"
#line 111 "d2_parser.yy"
                 { yyoutput << yysym.value.template as < std::string > (); }
#line 384 "d2_parser.cc"
        break;

      case 54: // "integer"
#line 111 "d2_parser.yy"
                 { yyoutput << yysym.value.template as < int64_t > (); }
#line 390 "d2_parser.cc"
        break;

      case 55: // "floating point"
#line 111 "d2_parser.yy"
                 { yyoutput << yysym.value.template as < double > (); }
#line 396 "d2_parser.cc"
        break;

      case 56: // "boolean"
#line 111 "d2_parser.yy"
                 { yyoutput << yysym.value.template as < bool > (); }
#line 402 "d2_parser.cc"
        break;

      case 68: // value
#line 111 "d2_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 408 "d2_parser.cc"
        break;

      case 72: // map_value
#line 111 "d2_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 414 "d2_parser.cc"
        break;

      case 96: // ncr_protocol_value
#line 111 "d2_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 420 "d2_parser.cc"
        break;

      default:
        break;
    }
        yyo << ')';
      }
  }
#endif

  void
  D2Parser::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
  D2Parser::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
  D2Parser::yypop_ (int n)
  {
    yystack_.pop (n);
  }

#if D2_PARSER_DEBUG
  std::ostream&
  D2Parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  D2Parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  D2Parser::debug_level_type
  D2Parser::debug_level () const
  {
    return yydebug_;
  }

  void
  D2Parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // D2_PARSER_DEBUG

  D2Parser::state_type
  D2Parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - YYNTOKENS] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - YYNTOKENS];
  }

  bool
  D2Parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  D2Parser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  D2Parser::operator() ()
  {
    return parse ();
  }

  int
  D2Parser::parse ()
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
      case 68: // value
      case 72: // map_value
      case 96: // ncr_protocol_value
        yylhs.value.emplace< ElementPtr > ();
        break;

      case 56: // "boolean"
        yylhs.value.emplace< bool > ();
        break;

      case 55: // "floating point"
        yylhs.value.emplace< double > ();
        break;

      case 54: // "integer"
        yylhs.value.emplace< int64_t > ();
        break;

      case 53: // "constant string"
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
  case 2:
#line 120 "d2_parser.yy"
                     { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 695 "d2_parser.cc"
    break;

  case 4:
#line 121 "d2_parser.yy"
                         { ctx.ctx_ = ctx.CONFIG; }
#line 701 "d2_parser.cc"
    break;

  case 6:
#line 122 "d2_parser.yy"
                    { ctx.ctx_ = ctx.DHCPDDNS; }
#line 707 "d2_parser.cc"
    break;

  case 8:
#line 123 "d2_parser.yy"
                    { ctx.ctx_ = ctx.TSIG_KEY; }
#line 713 "d2_parser.cc"
    break;

  case 10:
#line 124 "d2_parser.yy"
                     { ctx.ctx_ = ctx.TSIG_KEYS; }
#line 719 "d2_parser.cc"
    break;

  case 12:
#line 125 "d2_parser.yy"
                       { ctx.ctx_ = ctx.DDNS_DOMAIN; }
#line 725 "d2_parser.cc"
    break;

  case 14:
#line 126 "d2_parser.yy"
                        { ctx.ctx_ = ctx.DDNS_DOMAINS; }
#line 731 "d2_parser.cc"
    break;

  case 16:
#line 127 "d2_parser.yy"
                      { ctx.ctx_ = ctx.DNS_SERVERS; }
#line 737 "d2_parser.cc"
    break;

  case 18:
#line 128 "d2_parser.yy"
                       { ctx.ctx_ = ctx.DNS_SERVERS; }
#line 743 "d2_parser.cc"
    break;

  case 20:
#line 136 "d2_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 749 "d2_parser.cc"
    break;

  case 21:
#line 137 "d2_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location))); }
#line 755 "d2_parser.cc"
    break;

  case 22:
#line 138 "d2_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 761 "d2_parser.cc"
    break;

  case 23:
#line 139 "d2_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 767 "d2_parser.cc"
    break;

  case 24:
#line 140 "d2_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 773 "d2_parser.cc"
    break;

  case 25:
#line 141 "d2_parser.yy"
            { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 779 "d2_parser.cc"
    break;

  case 26:
#line 142 "d2_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 785 "d2_parser.cc"
    break;

  case 27:
#line 145 "d2_parser.yy"
                {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as < ElementPtr > ());
}
#line 794 "d2_parser.cc"
    break;

  case 28:
#line 150 "d2_parser.yy"
                     {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 805 "d2_parser.cc"
    break;

  case 29:
#line 155 "d2_parser.yy"
                             {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 815 "d2_parser.cc"
    break;

  case 30:
#line 161 "d2_parser.yy"
                { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 821 "d2_parser.cc"
    break;

  case 33:
#line 168 "d2_parser.yy"
                                  {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 830 "d2_parser.cc"
    break;

  case 34:
#line 172 "d2_parser.yy"
                                                      {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 840 "d2_parser.cc"
    break;

  case 35:
#line 179 "d2_parser.yy"
                              {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 849 "d2_parser.cc"
    break;

  case 36:
#line 182 "d2_parser.yy"
                               {
    // list parsing complete. Put any sanity checking here
}
#line 857 "d2_parser.cc"
    break;

  case 39:
#line 190 "d2_parser.yy"
                      {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 866 "d2_parser.cc"
    break;

  case 40:
#line 194 "d2_parser.yy"
                                           {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 875 "d2_parser.cc"
    break;

  case 41:
#line 205 "d2_parser.yy"
                                {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as < std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 886 "d2_parser.cc"
    break;

  case 42:
#line 214 "d2_parser.yy"
                           {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 897 "d2_parser.cc"
    break;

  case 43:
#line 219 "d2_parser.yy"
                                {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 907 "d2_parser.cc"
    break;

  case 46:
#line 235 "d2_parser.yy"
                          {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("DhcpDdns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCPDDNS);
}
#line 918 "d2_parser.cc"
    break;

  case 47:
#line 240 "d2_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 927 "d2_parser.cc"
    break;

  case 48:
#line 245 "d2_parser.yy"
                             {
    // Parse the dhcpddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 937 "d2_parser.cc"
    break;

  case 49:
#line 249 "d2_parser.yy"
                                 {
    // parsing completed
}
#line 945 "d2_parser.cc"
    break;

  case 65:
#line 273 "d2_parser.yy"
                       {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 953 "d2_parser.cc"
    break;

  case 66:
#line 275 "d2_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", s);
    ctx.leave();
}
#line 963 "d2_parser.cc"
    break;

  case 67:
#line 281 "d2_parser.yy"
                         {
    if (yystack_[0].value.as < int64_t > () <= 0 || yystack_[0].value.as < int64_t > () >= 65536 ) {
        error(yystack_[0].location, "port must be greater than zero but less than 65536");
    }
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", i);
}
#line 975 "d2_parser.cc"
    break;

  case 68:
#line 289 "d2_parser.yy"
                                                     {
    if (yystack_[0].value.as < int64_t > () <= 0) {
        error(yystack_[0].location, "dns-server-timeout must be greater than zero");
    } else {
        ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
        ctx.stack_.back()->set("dns-server-timeout", i);
    }
}
#line 988 "d2_parser.cc"
    break;

  case 69:
#line 298 "d2_parser.yy"
                           {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 996 "d2_parser.cc"
    break;

  case 70:
#line 300 "d2_parser.yy"
                           {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1005 "d2_parser.cc"
    break;

  case 71:
#line 306 "d2_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 1011 "d2_parser.cc"
    break;

  case 72:
#line 307 "d2_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 1017 "d2_parser.cc"
    break;

  case 73:
#line 310 "d2_parser.yy"
                       {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 1025 "d2_parser.cc"
    break;

  case 74:
#line 312 "d2_parser.yy"
             {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 1035 "d2_parser.cc"
    break;

  case 75:
#line 318 "d2_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1043 "d2_parser.cc"
    break;

  case 76:
#line 320 "d2_parser.yy"
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
#line 1070 "d2_parser.cc"
    break;

  case 77:
#line 343 "d2_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1078 "d2_parser.cc"
    break;

  case 78:
#line 345 "d2_parser.yy"
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
#line 1107 "d2_parser.cc"
    break;

  case 79:
#line 370 "d2_parser.yy"
                            {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("forward-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.FORWARD_DDNS);
}
#line 1118 "d2_parser.cc"
    break;

  case 80:
#line 375 "d2_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1127 "d2_parser.cc"
    break;

  case 81:
#line 380 "d2_parser.yy"
                            {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reverse-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.REVERSE_DDNS);
}
#line 1138 "d2_parser.cc"
    break;

  case 82:
#line 385 "d2_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1147 "d2_parser.cc"
    break;

  case 89:
#line 404 "d2_parser.yy"
                           {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-domains", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.DDNS_DOMAINS);
}
#line 1158 "d2_parser.cc"
    break;

  case 90:
#line 409 "d2_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1167 "d2_parser.cc"
    break;

  case 91:
#line 414 "d2_parser.yy"
                                  {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 1176 "d2_parser.cc"
    break;

  case 92:
#line 417 "d2_parser.yy"
                                   {
    // parsing completed
}
#line 1184 "d2_parser.cc"
    break;

  case 97:
#line 429 "d2_parser.yy"
                            {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1194 "d2_parser.cc"
    break;

  case 98:
#line 433 "d2_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 1202 "d2_parser.cc"
    break;

  case 99:
#line 437 "d2_parser.yy"
                                {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1211 "d2_parser.cc"
    break;

  case 100:
#line 440 "d2_parser.yy"
                                    {
    // parsing completed
}
#line 1219 "d2_parser.cc"
    break;

  case 109:
#line 457 "d2_parser.yy"
                       {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1227 "d2_parser.cc"
    break;

  case 110:
#line 459 "d2_parser.yy"
               {
    if (yystack_[0].value.as < std::string > () == "") {
        error(yystack_[1].location, "Ddns domain name cannot be blank");
    }
    ElementPtr elem(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1241 "d2_parser.cc"
    break;

  case 111:
#line 469 "d2_parser.yy"
                               {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1249 "d2_parser.cc"
    break;

  case 112:
#line 471 "d2_parser.yy"
               {
    ElementPtr elem(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("key-name", name);
    ctx.leave();
}
#line 1260 "d2_parser.cc"
    break;

  case 113:
#line 481 "d2_parser.yy"
                         {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dns-servers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.DNS_SERVERS);
}
#line 1271 "d2_parser.cc"
    break;

  case 114:
#line 486 "d2_parser.yy"
                                                        {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1280 "d2_parser.cc"
    break;

  case 115:
#line 491 "d2_parser.yy"
                                 {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 1289 "d2_parser.cc"
    break;

  case 116:
#line 494 "d2_parser.yy"
                                  {
    // parsing completed
}
#line 1297 "d2_parser.cc"
    break;

  case 119:
#line 502 "d2_parser.yy"
                           {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1307 "d2_parser.cc"
    break;

  case 120:
#line 506 "d2_parser.yy"
                                   {
    ctx.stack_.pop_back();
}
#line 1315 "d2_parser.cc"
    break;

  case 121:
#line 510 "d2_parser.yy"
                               {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1324 "d2_parser.cc"
    break;

  case 122:
#line 513 "d2_parser.yy"
                                   {
    // parsing completed
}
#line 1332 "d2_parser.cc"
    break;

  case 131:
#line 529 "d2_parser.yy"
                              {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1340 "d2_parser.cc"
    break;

  case 132:
#line 531 "d2_parser.yy"
               {
    if (yystack_[0].value.as < std::string > () != "") {
        error(yystack_[1].location, "hostname is not yet supported");
    }
    ElementPtr elem(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", name);
    ctx.leave();
}
#line 1354 "d2_parser.cc"
    break;

  case 133:
#line 541 "d2_parser.yy"
                                  {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1362 "d2_parser.cc"
    break;

  case 134:
#line 543 "d2_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", s);
    ctx.leave();
}
#line 1372 "d2_parser.cc"
    break;

  case 135:
#line 549 "d2_parser.yy"
                                    {
    if (yystack_[0].value.as < int64_t > () <= 0 || yystack_[0].value.as < int64_t > () >= 65536 ) {
        error(yystack_[0].location, "port must be greater than zero but less than 65536");
    }
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", i);
}
#line 1384 "d2_parser.cc"
    break;

  case 136:
#line 563 "d2_parser.yy"
                     {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tsig-keys", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.TSIG_KEYS);
}
#line 1395 "d2_parser.cc"
    break;

  case 137:
#line 568 "d2_parser.yy"
                                                       {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1404 "d2_parser.cc"
    break;

  case 138:
#line 573 "d2_parser.yy"
                               {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 1413 "d2_parser.cc"
    break;

  case 139:
#line 576 "d2_parser.yy"
                                 {
    // parsing completed
}
#line 1421 "d2_parser.cc"
    break;

  case 144:
#line 588 "d2_parser.yy"
                         {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1431 "d2_parser.cc"
    break;

  case 145:
#line 592 "d2_parser.yy"
                                 {
    ctx.stack_.pop_back();
}
#line 1439 "d2_parser.cc"
    break;

  case 146:
#line 596 "d2_parser.yy"
                             {
    // Parse tsig key list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1449 "d2_parser.cc"
    break;

  case 147:
#line 600 "d2_parser.yy"
                                 {
    // parsing completed
}
#line 1457 "d2_parser.cc"
    break;

  case 157:
#line 618 "d2_parser.yy"
                    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1465 "d2_parser.cc"
    break;

  case 158:
#line 620 "d2_parser.yy"
               {
    if (yystack_[0].value.as < std::string > () == "") {
        error(yystack_[1].location, "TSIG key name cannot be blank");
    }
    ElementPtr elem(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1479 "d2_parser.cc"
    break;

  case 159:
#line 630 "d2_parser.yy"
                              {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1487 "d2_parser.cc"
    break;

  case 160:
#line 632 "d2_parser.yy"
               {
    if (yystack_[0].value.as < std::string > () == "") {
        error(yystack_[1].location, "TSIG key algorithm cannot be blank");
    }
    ElementPtr elem(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("algorithm", elem);
    ctx.leave();
}
#line 1500 "d2_parser.cc"
    break;

  case 161:
#line 641 "d2_parser.yy"
                                                {
    if (yystack_[0].value.as < int64_t > () < 0 || (yystack_[0].value.as < int64_t > () > 0  && (yystack_[0].value.as < int64_t > () % 8 != 0))) {
        error(yystack_[0].location, "TSIG key digest-bits must either be zero or a positive, multiple of eight");
    }
    ElementPtr elem(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("digest-bits", elem);
}
#line 1512 "d2_parser.cc"
    break;

  case 162:
#line 649 "d2_parser.yy"
                        {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1520 "d2_parser.cc"
    break;

  case 163:
#line 651 "d2_parser.yy"
               {
    if (yystack_[0].value.as < std::string > () == "") {
        error(yystack_[1].location, "TSIG key secret cannot be blank");
    }
    ElementPtr elem(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("secret", elem);
    ctx.leave();
}
#line 1533 "d2_parser.cc"
    break;

  case 164:
#line 665 "d2_parser.yy"
                               {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 1544 "d2_parser.cc"
    break;

  case 165:
#line 670 "d2_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1553 "d2_parser.cc"
    break;

  case 173:
#line 686 "d2_parser.yy"
                                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1561 "d2_parser.cc"
    break;

  case 174:
#line 688 "d2_parser.yy"
               {
    ElementPtr stype(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 1571 "d2_parser.cc"
    break;

  case 175:
#line 694 "d2_parser.yy"
                                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1579 "d2_parser.cc"
    break;

  case 176:
#line 696 "d2_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 1589 "d2_parser.cc"
    break;

  case 177:
#line 704 "d2_parser.yy"
                 {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 1600 "d2_parser.cc"
    break;

  case 178:
#line 709 "d2_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1609 "d2_parser.cc"
    break;

  case 181:
#line 721 "d2_parser.yy"
                             {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 1619 "d2_parser.cc"
    break;

  case 182:
#line 725 "d2_parser.yy"
                               {
    ctx.stack_.pop_back();
}
#line 1627 "d2_parser.cc"
    break;

  case 192:
#line 742 "d2_parser.yy"
           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1635 "d2_parser.cc"
    break;

  case 193:
#line 744 "d2_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1645 "d2_parser.cc"
    break;

  case 194:
#line 750 "d2_parser.yy"
                                     {
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 1654 "d2_parser.cc"
    break;

  case 195:
#line 754 "d2_parser.yy"
                   {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1662 "d2_parser.cc"
    break;

  case 196:
#line 756 "d2_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 1672 "d2_parser.cc"
    break;

  case 197:
#line 762 "d2_parser.yy"
                                    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 1683 "d2_parser.cc"
    break;

  case 198:
#line 767 "d2_parser.yy"
                                                                    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1692 "d2_parser.cc"
    break;

  case 201:
#line 776 "d2_parser.yy"
                             {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1702 "d2_parser.cc"
    break;

  case 202:
#line 780 "d2_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 1710 "d2_parser.cc"
    break;

  case 210:
#line 795 "d2_parser.yy"
               {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1718 "d2_parser.cc"
    break;

  case 211:
#line 797 "d2_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 1728 "d2_parser.cc"
    break;

  case 212:
#line 803 "d2_parser.yy"
                           {
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 1737 "d2_parser.cc"
    break;

  case 213:
#line 808 "d2_parser.yy"
                               {
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 1746 "d2_parser.cc"
    break;

  case 214:
#line 813 "d2_parser.yy"
                             {
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 1755 "d2_parser.cc"
    break;

  case 215:
#line 818 "d2_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1763 "d2_parser.cc"
    break;

  case 216:
#line 820 "d2_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pattern", sev);
    ctx.leave();
}
#line 1773 "d2_parser.cc"
    break;


#line 1777 "d2_parser.cc"

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
  D2Parser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what ());
  }

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  D2Parser::yytnamerr_ (const char *yystr)
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
  D2Parser::symbol_name (symbol_kind_type yysymbol)
  {
    return yytnamerr_ (yytname_[yysymbol]);
  }



  // D2Parser::context.
  D2Parser::context::context (const D2Parser& yyparser, const symbol_type& yyla)
    : yyparser_ (yyparser)
    , yyla_ (yyla)
  {}

  int
  D2Parser::context::expected_tokens (symbol_kind_type yyarg[], int yyargn) const
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
  D2Parser::yy_syntax_error_arguments_ (const context& yyctx,
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
  D2Parser::yysyntax_error_ (const context& yyctx) const
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


  const signed char D2Parser::yypact_ninf_ = -83;

  const signed char D2Parser::yytable_ninf_ = -1;

  const short
  D2Parser::yypact_[] =
  {
      38,   -83,   -83,   -83,   -83,   -83,   -83,   -83,   -83,   -83,
       7,     1,     2,     8,    17,    26,    34,    53,    60,    86,
     -83,   -83,   -83,   -83,   -83,   -83,   -83,   -83,   -83,   -83,
     -83,   -83,   -83,   -83,   -83,   -83,   -83,   -83,   -83,   -83,
     -83,   -83,   -83,   -83,   -83,   -83,   -83,   -83,     1,    40,
       3,     6,    15,    94,    46,    95,    10,   105,   -83,   115,
     110,   118,   121,   128,   -83,   131,   -83,   -83,   -83,   151,
     152,   -83,   -83,   -83,   -83,   -83,   -83,   -83,   -83,   -83,
     153,   -83,    39,   -83,   -83,   -83,   -83,   -83,   -83,   -83,
     -83,   -83,   -83,   -83,   -83,   -83,   -83,   154,   -83,   -83,
     -83,   -83,   -83,    45,   -83,   -83,   -83,   -83,   -83,   -83,
     135,   148,   -83,   -83,   -83,   -83,   -83,   -83,   -83,    61,
     -83,   -83,   -83,   -83,   -83,   155,   156,   -83,   -83,   158,
     -83,   -83,   -83,   -83,    70,   -83,   -83,   -83,   -83,   -83,
      43,   -83,   -83,     1,     1,   -83,   111,   159,   -83,   161,
     106,   112,   163,   164,   165,   166,   167,   168,   169,   170,
     171,   -83,     6,   -83,   172,   123,   174,   175,    15,   -83,
      15,   -83,    94,   176,   177,   178,    46,   -83,    46,   -83,
      95,   181,   136,   185,    10,   -83,    10,   105,   -83,   -83,
     -83,   187,   186,   139,   -83,   -83,    59,   179,   188,   141,
     189,   192,   195,   194,   197,   -83,   150,   -83,   157,   160,
     -83,    97,   -83,   162,   199,   173,   -83,   100,   -83,   182,
     -83,   183,   -83,   101,   -83,     1,     6,   -83,   -83,   -83,
     -83,   -83,   -83,   -83,   -83,     9,     9,    94,    19,   198,
     -83,   -83,   -83,   -83,   -83,   105,   -83,   -83,   -83,   -83,
     -83,   -83,   107,   -83,   -83,   134,   -83,   -83,   -83,   137,
     200,   -83,   -83,   -83,   -83,   -83,   140,   -83,   -83,   -83,
     -83,   108,   -83,   117,   -83,   203,     9,   -83,   -83,   -83,
     204,   205,    19,   -83,    41,   198,   -83,   -83,   206,   -83,
     184,   190,   -83,   -83,   -83,   208,   -83,   -83,   -83,   -83,
     144,   -83,   -83,   -83,   -83,   -83,   -83,    95,   -83,   -83,
     210,   212,   180,   213,    41,   -83,   214,   193,   216,   -83,
     196,   -83,   -83,   -83,   211,   -83,   -83,   147,   -83,    55,
     211,   -83,   -83,   215,   218,   219,   -83,   146,   -83,   -83,
     -83,   -83,   -83,   -83,   -83,   221,   191,   201,   202,   223,
      55,   -83,   207,   -83,   -83,   -83,   217,   -83,   -83,   -83
  };

  const unsigned char
  D2Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       1,    35,    28,    24,    23,    20,    21,    22,    27,     3,
      25,    26,    42,     5,    48,     7,   146,     9,   138,    11,
      99,    13,    91,    15,   121,    17,   115,    19,    37,    31,
       0,     0,     0,   140,     0,    93,     0,     0,    39,     0,
      38,     0,     0,    32,    46,     0,    44,    45,    65,     0,
       0,    69,    73,    75,    77,    79,    81,   136,   164,   177,
       0,    64,     0,    50,    52,    53,    54,    55,    56,    62,
      63,    57,    58,    59,    60,    61,   159,     0,   162,   157,
     156,   154,   155,     0,   148,   150,   151,   152,   153,   144,
       0,   141,   142,   111,   113,   109,   108,   106,   107,     0,
     101,   103,   104,   105,    97,     0,    94,    95,   133,     0,
     131,   130,   128,   129,     0,   123,   125,   126,   127,   119,
       0,   117,    36,     0,     0,    29,     0,     0,    43,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    41,     0,    49,     0,     0,     0,     0,     0,   147,
       0,   139,     0,     0,     0,     0,     0,   100,     0,    92,
       0,     0,     0,     0,     0,   122,     0,     0,   116,    40,
      33,     0,     0,     0,    67,    68,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    51,     0,   161,     0,     0,
     149,     0,   143,     0,     0,     0,   102,     0,    96,     0,
     135,     0,   124,     0,   118,     0,     0,    66,    71,    72,
      70,    74,    30,    76,    78,    83,    83,   140,     0,     0,
     160,   163,   158,   145,   112,     0,   110,    98,   134,   132,
     120,    34,     0,    89,    88,     0,    84,    85,    87,     0,
       0,   173,   175,   172,   170,   171,     0,   166,   168,   169,
     181,     0,   179,     0,    47,     0,     0,    80,    82,   137,
       0,     0,     0,   165,     0,     0,   178,   114,     0,    86,
       0,     0,   167,   192,   197,     0,   195,   191,   189,   190,
       0,   183,   185,   187,   188,   186,   180,    93,   174,   176,
       0,     0,     0,     0,     0,   182,     0,     0,     0,   194,
       0,   184,    90,   193,     0,   196,   201,     0,   199,     0,
       0,   198,   210,     0,     0,     0,   215,     0,   203,   205,
     206,   207,   208,   209,   200,     0,     0,     0,     0,     0,
       0,   202,     0,   212,   213,   214,     0,   204,   211,   216
  };

  const signed char
  D2Parser::yypgoto_[] =
  {
     -83,   -83,   -83,   -83,   -83,   -83,   -83,   -83,   -83,   -83,
     -83,   -37,   -83,    30,   -83,   -83,   -83,   -83,   -83,   -83,
     -83,   -83,   -52,   -83,   -83,   -83,   -83,   -83,   -83,   -83,
     -83,    12,    67,   -83,   -83,   -83,   -83,   -83,   -83,   -83,
     -83,   -83,   -51,   -83,   -40,   -83,   -83,   -83,   -83,   -83,
       4,   -83,   -35,   -83,   -83,   -83,   -83,   -68,   -83,    65,
     -83,   -83,   -83,    72,    75,   -83,   -83,   -83,   -83,   -83,
     -83,   -83,   -83,    13,    66,   -83,   -83,   -83,    62,    68,
     -83,   -83,   -83,   -83,   -83,   -83,   -83,   -83,   -83,    20,
     -83,    82,   -83,   -83,   -83,    89,    93,   -83,   -83,   -83,
     -83,   -83,   -83,   -83,   -83,   -83,   -83,   -18,   -83,   -83,
     -83,   -83,   -83,   -83,   -83,   -20,   -83,   -83,   -48,   -83,
     -83,   -83,   -83,   -83,   -83,   -83,   -83,   -63,   -83,   -83,
     -82,   -83,   -83,   -83,   -83,   -83,   -83,   -83
  };

  const short
  D2Parser::yydefgoto_[] =
  {
      -1,    10,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    28,    29,    30,    49,   233,    62,    63,    31,    48,
      59,    60,    81,    33,    50,    65,    66,    67,   147,    35,
      51,    82,    83,    84,   149,    85,    86,    87,   152,   230,
      88,   153,    89,   154,    90,   155,    91,   156,    92,   157,
     255,   256,   257,   258,   275,    43,    55,   125,   126,   127,
     178,    41,    54,   119,   120,   121,   175,   122,   173,   123,
     174,    47,    57,   140,   141,   186,    45,    56,   134,   135,
     136,   183,   137,   181,   138,    93,   158,    39,    53,   110,
     111,   112,   170,    37,    52,   103,   104,   105,   167,   106,
     164,   107,   108,   166,    94,   159,   266,   267,   268,   280,
     269,   281,    95,   160,   271,   272,   284,   300,   301,   302,
     310,   303,   304,   313,   305,   311,   327,   328,   329,   337,
     338,   339,   345,   340,   341,   342,   343,   349
  };

  const short
  D2Parser::yytable_[] =
  {
     100,   101,   116,   117,   131,   132,    21,    20,    22,    32,
      23,    58,   102,    64,   118,    34,   133,    68,    69,    70,
      71,   128,   129,    72,    36,    73,    74,    75,    76,    73,
      74,    38,   253,    77,    73,    74,   130,    78,    73,    74,
      79,    40,   162,    96,    97,    98,   187,   163,   168,   188,
      99,   261,   262,   169,    24,    25,    26,    27,    42,    80,
      73,    74,    80,    80,   176,    73,    74,    44,    80,   177,
     113,   114,    80,   184,   228,   229,   293,   294,   185,   295,
     296,   115,     1,     2,     3,     4,     5,     6,     7,     8,
       9,    46,   332,    61,    80,   333,   334,   335,   336,    80,
     168,   109,   124,   176,   184,   243,   189,   190,   247,   250,
     162,   285,   139,   143,   286,   274,   100,   101,   100,   101,
     187,   142,   144,   287,   116,   117,   116,   117,   102,   145,
     102,   146,   131,   132,   131,   132,   118,   276,   118,   148,
     276,   171,   277,   282,   133,   278,   133,   314,   283,   350,
     330,   172,   315,   331,   351,   150,   151,   161,   165,   180,
     194,   179,   182,   192,   191,   193,   195,   196,   197,   198,
     199,   200,   201,   202,   203,   204,   206,   207,   208,   209,
     213,   214,   215,   254,   254,   219,   263,   264,   251,   221,
     220,   225,   227,   226,   234,    22,   235,   231,   265,   236,
     237,   238,   239,   240,   245,   270,   279,   288,   290,   291,
     241,   307,   312,   242,   317,   244,   318,   320,   326,   346,
     322,   324,   347,   348,   254,   352,   246,   356,   232,   205,
     263,   264,   297,   298,   319,   248,   249,   308,   252,   316,
     259,   289,   265,   309,   299,   218,   323,   353,   223,   325,
     217,   216,   222,   224,   212,   354,   355,   260,   273,   211,
     358,   210,   297,   298,   292,   306,   321,   344,   357,     0,
     359,     0,     0,     0,   299
  };

  const short
  D2Parser::yycheck_[] =
  {
      52,    52,    54,    54,    56,    56,     5,     0,     7,     7,
       9,    48,    52,    10,    54,     7,    56,    11,    12,    13,
      14,    11,    12,    17,     7,    19,    20,    21,    22,    19,
      20,     5,    23,    27,    19,    20,    26,    31,    19,    20,
      34,     7,     3,    28,    29,    30,     3,     8,     3,     6,
      35,    32,    33,     8,    53,    54,    55,    56,     5,    53,
      19,    20,    53,    53,     3,    19,    20,     7,    53,     8,
      24,    25,    53,     3,    15,    16,    35,    36,     8,    38,
      39,    35,    44,    45,    46,    47,    48,    49,    50,    51,
      52,     5,    37,    53,    53,    40,    41,    42,    43,    53,
       3,     7,     7,     3,     3,     8,   143,   144,     8,     8,
       3,     3,     7,     3,     6,     8,   168,   168,   170,   170,
       3,     6,     4,     6,   176,   176,   178,   178,   168,     8,
     170,     3,   184,   184,   186,   186,   176,     3,   178,     8,
       3,     6,     8,     3,   184,     8,   186,     3,     8,     3,
       3,     3,     8,     6,     8,     4,     4,     4,     4,     3,
      54,     6,     4,     4,    53,     4,    54,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,    54,     4,     4,
       4,     4,     4,   235,   236,     4,   238,   238,   225,     4,
      54,     4,    53,     7,    53,     7,     7,    18,   238,     7,
       5,     7,     5,    53,     5,     7,     6,     4,     4,     4,
      53,     5,     4,    53,     4,    53,     4,     4,     7,     4,
       6,     5,     4,     4,   276,     4,    53,     4,   198,   162,
     282,   282,   284,   284,    54,    53,    53,    53,   226,   307,
     236,   276,   282,    53,   284,   180,    53,    56,   186,    53,
     178,   176,   184,   187,   172,    54,    54,   237,   245,   170,
      53,   168,   314,   314,   282,   285,   314,   330,   350,    -1,
      53,    -1,    -1,    -1,   314
  };

  const unsigned char
  D2Parser::yystos_[] =
  {
       0,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
       0,     5,     7,     9,    53,    54,    55,    56,    68,    69,
      70,    75,     7,    80,     7,    86,     7,   150,     5,   144,
       7,   118,     5,   112,     7,   133,     5,   128,    76,    71,
      81,    87,   151,   145,   119,   113,   134,   129,    68,    77,
      78,    53,    73,    74,    10,    82,    83,    84,    11,    12,
      13,    14,    17,    19,    20,    21,    22,    27,    31,    34,
      53,    79,    88,    89,    90,    92,    93,    94,    97,    99,
     101,   103,   105,   142,   161,   169,    28,    29,    30,    35,
      79,    99,   101,   152,   153,   154,   156,   158,   159,     7,
     146,   147,   148,    24,    25,    35,    79,    99,   101,   120,
     121,   122,   124,   126,     7,   114,   115,   116,    11,    12,
      26,    79,    99,   101,   135,   136,   137,   139,   141,     7,
     130,   131,     6,     3,     4,     8,     3,    85,     8,    91,
       4,     4,    95,    98,   100,   102,   104,   106,   143,   162,
     170,     4,     3,     8,   157,     4,   160,   155,     3,     8,
     149,     6,     3,   125,   127,   123,     3,     8,   117,     6,
       3,   140,     4,   138,     3,     8,   132,     3,     6,    68,
      68,    53,     4,     4,    54,    54,     4,     4,     4,     4,
       4,     4,     4,     4,     4,    89,     4,    54,     4,     4,
     153,   152,   148,     4,     4,     4,   121,   120,   116,     4,
      54,     4,   136,   135,   131,     4,     7,    53,    15,    16,
      96,    18,    70,    72,    53,     7,     7,     5,     7,     5,
      53,    53,    53,     8,    53,     5,    53,     8,    53,    53,
       8,    68,    88,    23,    79,   107,   108,   109,   110,   107,
     146,    32,    33,    79,    99,   101,   163,   164,   165,   167,
       7,   171,   172,   130,     8,   111,     3,     8,     8,     6,
     166,   168,     3,     8,   173,     3,     6,     6,     4,   109,
       4,     4,   164,    35,    36,    38,    39,    79,    99,   101,
     174,   175,   176,   178,   179,   181,   172,     5,    53,    53,
     177,   182,     4,   180,     3,     8,   114,     4,     4,    54,
       4,   175,     6,    53,     5,    53,     7,   183,   184,   185,
       3,     6,    37,    40,    41,    42,    43,   186,   187,   188,
     190,   191,   192,   193,   184,   189,     4,     4,     4,   194,
       3,     8,     4,    56,    54,    54,     4,   187,    53,    53
  };

  const unsigned char
  D2Parser::yyr1_[] =
  {
       0,    57,    59,    58,    60,    58,    61,    58,    62,    58,
      63,    58,    64,    58,    65,    58,    66,    58,    67,    58,
      68,    68,    68,    68,    68,    68,    68,    69,    71,    70,
      72,    73,    73,    74,    74,    76,    75,    77,    77,    78,
      78,    79,    81,    80,    82,    83,    85,    84,    87,    86,
      88,    88,    89,    89,    89,    89,    89,    89,    89,    89,
      89,    89,    89,    89,    89,    91,    90,    92,    93,    95,
      94,    96,    96,    98,    97,   100,    99,   102,   101,   104,
     103,   106,   105,   107,   107,   108,   108,   109,   109,   111,
     110,   113,   112,   114,   114,   115,   115,   117,   116,   119,
     118,   120,   120,   121,   121,   121,   121,   121,   121,   123,
     122,   125,   124,   127,   126,   129,   128,   130,   130,   132,
     131,   134,   133,   135,   135,   136,   136,   136,   136,   136,
     136,   138,   137,   140,   139,   141,   143,   142,   145,   144,
     146,   146,   147,   147,   149,   148,   151,   150,   152,   152,
     153,   153,   153,   153,   153,   153,   153,   155,   154,   157,
     156,   158,   160,   159,   162,   161,   163,   163,   164,   164,
     164,   164,   164,   166,   165,   168,   167,   170,   169,   171,
     171,   173,   172,   174,   174,   175,   175,   175,   175,   175,
     175,   175,   177,   176,   178,   180,   179,   182,   181,   183,
     183,   185,   184,   186,   186,   187,   187,   187,   187,   187,
     189,   188,   190,   191,   192,   194,   193
  };

  const signed char
  D2Parser::yyr2_[] =
  {
       0,     2,     0,     3,     0,     3,     0,     3,     0,     3,
       0,     3,     0,     3,     0,     3,     0,     3,     0,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       1,     0,     1,     3,     5,     0,     4,     0,     1,     1,
       3,     2,     0,     4,     1,     1,     0,     6,     0,     4,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     3,     3,     0,
       4,     1,     1,     0,     4,     0,     4,     0,     4,     0,
       6,     0,     6,     0,     1,     1,     3,     1,     1,     0,
       6,     0,     4,     0,     1,     1,     3,     0,     4,     0,
       4,     1,     3,     1,     1,     1,     1,     1,     1,     0,
       4,     0,     4,     0,     6,     0,     4,     1,     3,     0,
       4,     0,     4,     1,     3,     1,     1,     1,     1,     1,
       1,     0,     4,     0,     4,     3,     0,     6,     0,     4,
       0,     1,     1,     3,     0,     4,     0,     4,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     0,
       4,     3,     0,     4,     0,     6,     1,     3,     1,     1,
       1,     1,     1,     0,     4,     0,     4,     0,     6,     1,
       3,     0,     4,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     3,     0,     4,     0,     6,     1,
       3,     0,     4,     1,     3,     1,     1,     1,     1,     1,
       0,     4,     3,     3,     3,     0,     4
  };


#if D2_PARSER_DEBUG || 1
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a YYNTOKENS, nonterminals.
  const char*
  const D2Parser::yytname_[] =
  {
  "\"end of file\"", "error", "\"invalid token\"", "\",\"", "\":\"",
  "\"[\"", "\"]\"", "\"{\"", "\"}\"", "\"null\"", "\"DhcpDdns\"",
  "\"ip-address\"", "\"port\"", "\"dns-server-timeout\"",
  "\"ncr-protocol\"", "\"UDP\"", "\"TCP\"", "\"ncr-format\"", "\"JSON\"",
  "\"user-context\"", "\"comment\"", "\"forward-ddns\"",
  "\"reverse-ddns\"", "\"ddns-domains\"", "\"key-name\"",
  "\"dns-servers\"", "\"hostname\"", "\"tsig-keys\"", "\"algorithm\"",
  "\"digest-bits\"", "\"secret\"", "\"control-socket\"", "\"socket-type\"",
  "\"socket-name\"", "\"loggers\"", "\"name\"", "\"output_options\"",
  "\"output\"", "\"debuglevel\"", "\"severity\"", "\"flush\"",
  "\"maxsize\"", "\"maxver\"", "\"pattern\"", "TOPLEVEL_JSON",
  "TOPLEVEL_DHCPDDNS", "SUB_DHCPDDNS", "SUB_TSIG_KEY", "SUB_TSIG_KEYS",
  "SUB_DDNS_DOMAIN", "SUB_DDNS_DOMAINS", "SUB_DNS_SERVER",
  "SUB_DNS_SERVERS", "\"constant string\"", "\"integer\"",
  "\"floating point\"", "\"boolean\"", "$accept", "start", "$@1", "$@2",
  "$@3", "$@4", "$@5", "$@6", "$@7", "$@8", "$@9", "value", "sub_json",
  "map2", "$@10", "map_value", "map_content", "not_empty_map",
  "list_generic", "$@11", "list_content", "not_empty_list",
  "unknown_map_entry", "syntax_map", "$@12", "global_objects",
  "global_object", "dhcpddns_object", "$@13", "sub_dhcpddns", "$@14",
  "dhcpddns_params", "dhcpddns_param", "ip_address", "$@15", "port",
  "dns_server_timeout", "ncr_protocol", "$@16", "ncr_protocol_value",
  "ncr_format", "$@17", "user_context", "$@18", "comment", "$@19",
  "forward_ddns", "$@20", "reverse_ddns", "$@21", "ddns_mgr_params",
  "not_empty_ddns_mgr_params", "ddns_mgr_param", "ddns_domains", "$@22",
  "sub_ddns_domains", "$@23", "ddns_domain_list",
  "not_empty_ddns_domain_list", "ddns_domain", "$@24", "sub_ddns_domain",
  "$@25", "ddns_domain_params", "ddns_domain_param", "ddns_domain_name",
  "$@26", "ddns_domain_key_name", "$@27", "dns_servers", "$@28",
  "sub_dns_servers", "$@29", "dns_server_list", "dns_server", "$@30",
  "sub_dns_server", "$@31", "dns_server_params", "dns_server_param",
  "dns_server_hostname", "$@32", "dns_server_ip_address", "$@33",
  "dns_server_port", "tsig_keys", "$@34", "sub_tsig_keys", "$@35",
  "tsig_keys_list", "not_empty_tsig_keys_list", "tsig_key", "$@36",
  "sub_tsig_key", "$@37", "tsig_key_params", "tsig_key_param",
  "tsig_key_name", "$@38", "tsig_key_algorithm", "$@39",
  "tsig_key_digest_bits", "tsig_key_secret", "$@40", "control_socket",
  "$@41", "control_socket_params", "control_socket_param",
  "control_socket_type", "$@42", "control_socket_name", "$@43", "loggers",
  "$@44", "loggers_entries", "logger_entry", "$@45", "logger_params",
  "logger_param", "name", "$@46", "debuglevel", "severity", "$@47",
  "output_options_list", "$@48", "output_options_list_content",
  "output_entry", "$@49", "output_params_list", "output_params", "output",
  "$@50", "flush", "maxsize", "maxver", "pattern", "$@51", YY_NULLPTR
  };
#endif


#if D2_PARSER_DEBUG
  const short
  D2Parser::yyrline_[] =
  {
       0,   120,   120,   120,   121,   121,   122,   122,   123,   123,
     124,   124,   125,   125,   126,   126,   127,   127,   128,   128,
     136,   137,   138,   139,   140,   141,   142,   145,   150,   150,
     161,   164,   165,   168,   172,   179,   179,   186,   187,   190,
     194,   205,   214,   214,   226,   230,   235,   235,   245,   245,
     253,   254,   258,   259,   260,   261,   262,   263,   264,   265,
     266,   267,   268,   269,   270,   273,   273,   281,   289,   298,
     298,   306,   307,   310,   310,   318,   318,   343,   343,   370,
     370,   380,   380,   390,   391,   394,   395,   398,   399,   404,
     404,   414,   414,   421,   422,   425,   426,   429,   429,   437,
     437,   444,   445,   448,   449,   450,   451,   452,   453,   457,
     457,   469,   469,   481,   481,   491,   491,   498,   499,   502,
     502,   510,   510,   517,   518,   521,   522,   523,   524,   525,
     526,   529,   529,   541,   541,   549,   563,   563,   573,   573,
     580,   581,   584,   585,   588,   588,   596,   596,   605,   606,
     609,   610,   611,   612,   613,   614,   615,   618,   618,   630,
     630,   641,   649,   649,   665,   665,   675,   676,   679,   680,
     681,   682,   683,   686,   686,   694,   694,   704,   704,   716,
     717,   721,   721,   729,   730,   733,   734,   735,   736,   737,
     738,   739,   742,   742,   750,   754,   754,   762,   762,   772,
     773,   776,   776,   784,   785,   788,   789,   790,   791,   792,
     795,   795,   803,   808,   813,   818,   818
  };

  void
  D2Parser::yy_stack_print_ () const
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
  D2Parser::yy_reduce_print_ (int yyrule) const
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
#endif // D2_PARSER_DEBUG


#line 14 "d2_parser.yy"
} } // isc::d2
#line 2524 "d2_parser.cc"

#line 826 "d2_parser.yy"


void
isc::d2::D2Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
