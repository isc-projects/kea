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
#define yylex   parser6_lex



#include "dhcp6_parser.h"


// Unqualified %code blocks.
#line 34 "dhcp6_parser.yy"

#include <dhcp6/parser_context.h>

#line 52 "dhcp6_parser.cc"


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
#if PARSER6_DEBUG

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

#else // !PARSER6_DEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !PARSER6_DEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 14 "dhcp6_parser.yy"
namespace isc { namespace dhcp {
#line 145 "dhcp6_parser.cc"

  /// Build a parser object.
  Dhcp6Parser::Dhcp6Parser (isc::dhcp::Parser6Context& ctx_yyarg)
#if PARSER6_DEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
#else
    :
#endif
      ctx (ctx_yyarg)
  {}

  Dhcp6Parser::~Dhcp6Parser ()
  {}

  Dhcp6Parser::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------------.
  | symbol kinds.  |
  `---------------*/



  // by_state.
  Dhcp6Parser::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

  Dhcp6Parser::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
  Dhcp6Parser::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
  Dhcp6Parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  Dhcp6Parser::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

  Dhcp6Parser::symbol_kind_type
  Dhcp6Parser::by_state::kind () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return symbol_kind::S_YYEMPTY;
    else
      return YY_CAST (symbol_kind_type, yystos_[+state]);
  }

  Dhcp6Parser::stack_symbol_type::stack_symbol_type ()
  {}

  Dhcp6Parser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state), YY_MOVE (that.location))
  {
    switch (that.kind ())
    {
      case 214: // value
      case 218: // map_value
      case 259: // ddns_replace_client_name_value
      case 296: // db_type
      case 397: // hr_mode
      case 533: // duid_type
      case 576: // ncr_protocol_value
        value.YY_MOVE_OR_COPY< ElementPtr > (YY_MOVE (that.value));
        break;

      case 197: // "boolean"
        value.YY_MOVE_OR_COPY< bool > (YY_MOVE (that.value));
        break;

      case 196: // "floating point"
        value.YY_MOVE_OR_COPY< double > (YY_MOVE (that.value));
        break;

      case 195: // "integer"
        value.YY_MOVE_OR_COPY< int64_t > (YY_MOVE (that.value));
        break;

      case 194: // "constant string"
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

  Dhcp6Parser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s, YY_MOVE (that.location))
  {
    switch (that.kind ())
    {
      case 214: // value
      case 218: // map_value
      case 259: // ddns_replace_client_name_value
      case 296: // db_type
      case 397: // hr_mode
      case 533: // duid_type
      case 576: // ncr_protocol_value
        value.move< ElementPtr > (YY_MOVE (that.value));
        break;

      case 197: // "boolean"
        value.move< bool > (YY_MOVE (that.value));
        break;

      case 196: // "floating point"
        value.move< double > (YY_MOVE (that.value));
        break;

      case 195: // "integer"
        value.move< int64_t > (YY_MOVE (that.value));
        break;

      case 194: // "constant string"
        value.move< std::string > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

    // that is emptied.
    that.kind_ = symbol_kind::S_YYEMPTY;
  }

#if YY_CPLUSPLUS < 201103L
  Dhcp6Parser::stack_symbol_type&
  Dhcp6Parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case 214: // value
      case 218: // map_value
      case 259: // ddns_replace_client_name_value
      case 296: // db_type
      case 397: // hr_mode
      case 533: // duid_type
      case 576: // ncr_protocol_value
        value.copy< ElementPtr > (that.value);
        break;

      case 197: // "boolean"
        value.copy< bool > (that.value);
        break;

      case 196: // "floating point"
        value.copy< double > (that.value);
        break;

      case 195: // "integer"
        value.copy< int64_t > (that.value);
        break;

      case 194: // "constant string"
        value.copy< std::string > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    return *this;
  }

  Dhcp6Parser::stack_symbol_type&
  Dhcp6Parser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case 214: // value
      case 218: // map_value
      case 259: // ddns_replace_client_name_value
      case 296: // db_type
      case 397: // hr_mode
      case 533: // duid_type
      case 576: // ncr_protocol_value
        value.move< ElementPtr > (that.value);
        break;

      case 197: // "boolean"
        value.move< bool > (that.value);
        break;

      case 196: // "floating point"
        value.move< double > (that.value);
        break;

      case 195: // "integer"
        value.move< int64_t > (that.value);
        break;

      case 194: // "constant string"
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
  Dhcp6Parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if PARSER6_DEBUG
  template <typename Base>
  void
  Dhcp6Parser::yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const
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
      case 194: // "constant string"
#line 274 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < std::string > (); }
#line 400 "dhcp6_parser.cc"
        break;

      case 195: // "integer"
#line 274 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < int64_t > (); }
#line 406 "dhcp6_parser.cc"
        break;

      case 196: // "floating point"
#line 274 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < double > (); }
#line 412 "dhcp6_parser.cc"
        break;

      case 197: // "boolean"
#line 274 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < bool > (); }
#line 418 "dhcp6_parser.cc"
        break;

      case 214: // value
#line 274 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 424 "dhcp6_parser.cc"
        break;

      case 218: // map_value
#line 274 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 430 "dhcp6_parser.cc"
        break;

      case 259: // ddns_replace_client_name_value
#line 274 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 436 "dhcp6_parser.cc"
        break;

      case 296: // db_type
#line 274 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 442 "dhcp6_parser.cc"
        break;

      case 397: // hr_mode
#line 274 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 448 "dhcp6_parser.cc"
        break;

      case 533: // duid_type
#line 274 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 454 "dhcp6_parser.cc"
        break;

      case 576: // ncr_protocol_value
#line 274 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 460 "dhcp6_parser.cc"
        break;

      default:
        break;
    }
        yyo << ')';
      }
  }
#endif

  void
  Dhcp6Parser::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
  Dhcp6Parser::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
  Dhcp6Parser::yypop_ (int n)
  {
    yystack_.pop (n);
  }

#if PARSER6_DEBUG
  std::ostream&
  Dhcp6Parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  Dhcp6Parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  Dhcp6Parser::debug_level_type
  Dhcp6Parser::debug_level () const
  {
    return yydebug_;
  }

  void
  Dhcp6Parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // PARSER6_DEBUG

  Dhcp6Parser::state_type
  Dhcp6Parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - YYNTOKENS] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - YYNTOKENS];
  }

  bool
  Dhcp6Parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  Dhcp6Parser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  Dhcp6Parser::operator() ()
  {
    return parse ();
  }

  int
  Dhcp6Parser::parse ()
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
      case 214: // value
      case 218: // map_value
      case 259: // ddns_replace_client_name_value
      case 296: // db_type
      case 397: // hr_mode
      case 533: // duid_type
      case 576: // ncr_protocol_value
        yylhs.value.emplace< ElementPtr > ();
        break;

      case 197: // "boolean"
        yylhs.value.emplace< bool > ();
        break;

      case 196: // "floating point"
        yylhs.value.emplace< double > ();
        break;

      case 195: // "integer"
        yylhs.value.emplace< int64_t > ();
        break;

      case 194: // "constant string"
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
#line 283 "dhcp6_parser.yy"
                     { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 739 "dhcp6_parser.cc"
    break;

  case 4:
#line 284 "dhcp6_parser.yy"
                      { ctx.ctx_ = ctx.CONFIG; }
#line 745 "dhcp6_parser.cc"
    break;

  case 6:
#line 285 "dhcp6_parser.yy"
                 { ctx.ctx_ = ctx.DHCP6; }
#line 751 "dhcp6_parser.cc"
    break;

  case 8:
#line 286 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 757 "dhcp6_parser.cc"
    break;

  case 10:
#line 287 "dhcp6_parser.yy"
                   { ctx.ctx_ = ctx.SUBNET6; }
#line 763 "dhcp6_parser.cc"
    break;

  case 12:
#line 288 "dhcp6_parser.yy"
                 { ctx.ctx_ = ctx.POOLS; }
#line 769 "dhcp6_parser.cc"
    break;

  case 14:
#line 289 "dhcp6_parser.yy"
                   { ctx.ctx_ = ctx.PD_POOLS; }
#line 775 "dhcp6_parser.cc"
    break;

  case 16:
#line 290 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.RESERVATIONS; }
#line 781 "dhcp6_parser.cc"
    break;

  case 18:
#line 291 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.DHCP6; }
#line 787 "dhcp6_parser.cc"
    break;

  case 20:
#line 292 "dhcp6_parser.yy"
                      { ctx.ctx_ = ctx.OPTION_DEF; }
#line 793 "dhcp6_parser.cc"
    break;

  case 22:
#line 293 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.OPTION_DATA; }
#line 799 "dhcp6_parser.cc"
    break;

  case 24:
#line 294 "dhcp6_parser.yy"
                         { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 805 "dhcp6_parser.cc"
    break;

  case 26:
#line 295 "dhcp6_parser.yy"
                     { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 811 "dhcp6_parser.cc"
    break;

  case 28:
#line 296 "dhcp6_parser.yy"
                          { ctx.ctx_ = ctx.CONFIG_CONTROL; }
#line 817 "dhcp6_parser.cc"
    break;

  case 30:
#line 304 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 823 "dhcp6_parser.cc"
    break;

  case 31:
#line 305 "dhcp6_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location))); }
#line 829 "dhcp6_parser.cc"
    break;

  case 32:
#line 306 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 835 "dhcp6_parser.cc"
    break;

  case 33:
#line 307 "dhcp6_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 841 "dhcp6_parser.cc"
    break;

  case 34:
#line 308 "dhcp6_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 847 "dhcp6_parser.cc"
    break;

  case 35:
#line 309 "dhcp6_parser.yy"
            { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 853 "dhcp6_parser.cc"
    break;

  case 36:
#line 310 "dhcp6_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 859 "dhcp6_parser.cc"
    break;

  case 37:
#line 313 "dhcp6_parser.yy"
                {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as < ElementPtr > ());
}
#line 868 "dhcp6_parser.cc"
    break;

  case 38:
#line 318 "dhcp6_parser.yy"
                     {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 879 "dhcp6_parser.cc"
    break;

  case 39:
#line 323 "dhcp6_parser.yy"
                             {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 889 "dhcp6_parser.cc"
    break;

  case 40:
#line 329 "dhcp6_parser.yy"
                { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 895 "dhcp6_parser.cc"
    break;

  case 43:
#line 336 "dhcp6_parser.yy"
                                  {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 904 "dhcp6_parser.cc"
    break;

  case 44:
#line 340 "dhcp6_parser.yy"
                                                      {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 914 "dhcp6_parser.cc"
    break;

  case 45:
#line 347 "dhcp6_parser.yy"
                              {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 923 "dhcp6_parser.cc"
    break;

  case 46:
#line 350 "dhcp6_parser.yy"
                               {
    // list parsing complete. Put any sanity checking here
}
#line 931 "dhcp6_parser.cc"
    break;

  case 49:
#line 358 "dhcp6_parser.yy"
                      {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 940 "dhcp6_parser.cc"
    break;

  case 50:
#line 362 "dhcp6_parser.yy"
                                           {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 949 "dhcp6_parser.cc"
    break;

  case 51:
#line 369 "dhcp6_parser.yy"
                              {
    // List parsing about to start
}
#line 957 "dhcp6_parser.cc"
    break;

  case 52:
#line 371 "dhcp6_parser.yy"
                                       {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 966 "dhcp6_parser.cc"
    break;

  case 55:
#line 380 "dhcp6_parser.yy"
                               {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 975 "dhcp6_parser.cc"
    break;

  case 56:
#line 384 "dhcp6_parser.yy"
                                                            {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 984 "dhcp6_parser.cc"
    break;

  case 57:
#line 395 "dhcp6_parser.yy"
                                {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as < std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 995 "dhcp6_parser.cc"
    break;

  case 58:
#line 404 "dhcp6_parser.yy"
                           {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1006 "dhcp6_parser.cc"
    break;

  case 59:
#line 409 "dhcp6_parser.yy"
                                {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.

    // Dhcp6 is required
    ctx.require("Dhcp6", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
}
#line 1019 "dhcp6_parser.cc"
    break;

  case 63:
#line 427 "dhcp6_parser.yy"
                    {
    // This code is executed when we're about to start parsing
    // the content of the map
    // Prevent against duplicate.
    ctx.unique("Dhcp6", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Dhcp6", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP6);
}
#line 1034 "dhcp6_parser.cc"
    break;

  case 64:
#line 436 "dhcp6_parser.yy"
                                                    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1044 "dhcp6_parser.cc"
    break;

  case 65:
#line 444 "dhcp6_parser.yy"
                          {
    // Parse the Dhcp6 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1054 "dhcp6_parser.cc"
    break;

  case 66:
#line 448 "dhcp6_parser.yy"
                               {
    // No global parameter is required
    // parsing completed
}
#line 1063 "dhcp6_parser.cc"
    break;

  case 122:
#line 514 "dhcp6_parser.yy"
                               {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1071 "dhcp6_parser.cc"
    break;

  case 123:
#line 516 "dhcp6_parser.yy"
               {
    ElementPtr datadir(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data-directory", datadir);
    ctx.leave();
}
#line 1081 "dhcp6_parser.cc"
    break;

  case 124:
#line 522 "dhcp6_parser.yy"
                                                     {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("preferred-lifetime", prf);
}
#line 1090 "dhcp6_parser.cc"
    break;

  case 125:
#line 527 "dhcp6_parser.yy"
                                                             {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-preferred-lifetime", prf);
}
#line 1099 "dhcp6_parser.cc"
    break;

  case 126:
#line 532 "dhcp6_parser.yy"
                                                             {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-preferred-lifetime", prf);
}
#line 1108 "dhcp6_parser.cc"
    break;

  case 127:
#line 537 "dhcp6_parser.yy"
                                             {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1117 "dhcp6_parser.cc"
    break;

  case 128:
#line 542 "dhcp6_parser.yy"
                                                     {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-valid-lifetime", prf);
}
#line 1126 "dhcp6_parser.cc"
    break;

  case 129:
#line 547 "dhcp6_parser.yy"
                                                     {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-valid-lifetime", prf);
}
#line 1135 "dhcp6_parser.cc"
    break;

  case 130:
#line 552 "dhcp6_parser.yy"
                                       {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1144 "dhcp6_parser.cc"
    break;

  case 131:
#line 557 "dhcp6_parser.yy"
                                         {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1153 "dhcp6_parser.cc"
    break;

  case 132:
#line 562 "dhcp6_parser.yy"
                                                       {
    ElementPtr ctt(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("calculate-tee-times", ctt);
}
#line 1162 "dhcp6_parser.cc"
    break;

  case 133:
#line 567 "dhcp6_parser.yy"
                                   {
    ElementPtr t1(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t1-percent", t1);
}
#line 1171 "dhcp6_parser.cc"
    break;

  case 134:
#line 572 "dhcp6_parser.yy"
                                   {
    ElementPtr t2(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t2-percent", t2);
}
#line 1180 "dhcp6_parser.cc"
    break;

  case 135:
#line 577 "dhcp6_parser.yy"
                                                                 {
    ElementPtr dpp(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1189 "dhcp6_parser.cc"
    break;

  case 136:
#line 582 "dhcp6_parser.yy"
                                                   {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-send-updates", b);
}
#line 1198 "dhcp6_parser.cc"
    break;

  case 137:
#line 587 "dhcp6_parser.yy"
                                                               {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-no-update", b);
}
#line 1207 "dhcp6_parser.cc"
    break;

  case 138:
#line 592 "dhcp6_parser.yy"
                                                                       {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-client-update", b);
}
#line 1216 "dhcp6_parser.cc"
    break;

  case 139:
#line 597 "dhcp6_parser.yy"
                                                   {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 1224 "dhcp6_parser.cc"
    break;

  case 140:
#line 599 "dhcp6_parser.yy"
                                       {
    ctx.stack_.back()->set("ddns-replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1233 "dhcp6_parser.cc"
    break;

  case 141:
#line 605 "dhcp6_parser.yy"
                 {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1241 "dhcp6_parser.cc"
    break;

  case 142:
#line 608 "dhcp6_parser.yy"
          {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 1249 "dhcp6_parser.cc"
    break;

  case 143:
#line 611 "dhcp6_parser.yy"
           {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 1257 "dhcp6_parser.cc"
    break;

  case 144:
#line 614 "dhcp6_parser.yy"
                     {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1265 "dhcp6_parser.cc"
    break;

  case 145:
#line 617 "dhcp6_parser.yy"
            {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 1274 "dhcp6_parser.cc"
    break;

  case 146:
#line 623 "dhcp6_parser.yy"
                                             {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1282 "dhcp6_parser.cc"
    break;

  case 147:
#line 625 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-generated-prefix", s);
    ctx.leave();
}
#line 1292 "dhcp6_parser.cc"
    break;

  case 148:
#line 631 "dhcp6_parser.yy"
                                               {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1300 "dhcp6_parser.cc"
    break;

  case 149:
#line 633 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-qualifying-suffix", s);
    ctx.leave();
}
#line 1310 "dhcp6_parser.cc"
    break;

  case 150:
#line 639 "dhcp6_parser.yy"
                                     {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1318 "dhcp6_parser.cc"
    break;

  case 151:
#line 641 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 1328 "dhcp6_parser.cc"
    break;

  case 152:
#line 647 "dhcp6_parser.yy"
                                                     {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1336 "dhcp6_parser.cc"
    break;

  case 153:
#line 649 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 1346 "dhcp6_parser.cc"
    break;

  case 154:
#line 655 "dhcp6_parser.yy"
                                                       {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("store-extended-info", b);
}
#line 1355 "dhcp6_parser.cc"
    break;

  case 155:
#line 660 "dhcp6_parser.yy"
                                                                             {
    ElementPtr count(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-count", count);
}
#line 1364 "dhcp6_parser.cc"
    break;

  case 156:
#line 665 "dhcp6_parser.yy"
                                                                         {
    ElementPtr age(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-age", age);
}
#line 1373 "dhcp6_parser.cc"
    break;

  case 157:
#line 670 "dhcp6_parser.yy"
                       {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1381 "dhcp6_parser.cc"
    break;

  case 158:
#line 672 "dhcp6_parser.yy"
               {
    ElementPtr stag(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-tag", stag);
    ctx.leave();
}
#line 1391 "dhcp6_parser.cc"
    break;

  case 159:
#line 678 "dhcp6_parser.yy"
                                     {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1402 "dhcp6_parser.cc"
    break;

  case 160:
#line 683 "dhcp6_parser.yy"
                                                               {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1412 "dhcp6_parser.cc"
    break;

  case 161:
#line 689 "dhcp6_parser.yy"
                                {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1422 "dhcp6_parser.cc"
    break;

  case 162:
#line 693 "dhcp6_parser.yy"
                                          {
    // No interfaces config param is required
    // parsing completed
}
#line 1431 "dhcp6_parser.cc"
    break;

  case 170:
#line 709 "dhcp6_parser.yy"
                            {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1442 "dhcp6_parser.cc"
    break;

  case 171:
#line 714 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1451 "dhcp6_parser.cc"
    break;

  case 172:
#line 719 "dhcp6_parser.yy"
                                   {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1460 "dhcp6_parser.cc"
    break;

  case 173:
#line 724 "dhcp6_parser.yy"
                               {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1471 "dhcp6_parser.cc"
    break;

  case 174:
#line 729 "dhcp6_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1482 "dhcp6_parser.cc"
    break;

  case 175:
#line 736 "dhcp6_parser.yy"
                               {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1493 "dhcp6_parser.cc"
    break;

  case 176:
#line 741 "dhcp6_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1504 "dhcp6_parser.cc"
    break;

  case 177:
#line 748 "dhcp6_parser.yy"
                                 {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1515 "dhcp6_parser.cc"
    break;

  case 178:
#line 753 "dhcp6_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1524 "dhcp6_parser.cc"
    break;

  case 183:
#line 766 "dhcp6_parser.yy"
                         {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1534 "dhcp6_parser.cc"
    break;

  case 184:
#line 770 "dhcp6_parser.yy"
                                     {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1544 "dhcp6_parser.cc"
    break;

  case 208:
#line 803 "dhcp6_parser.yy"
                    {
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1552 "dhcp6_parser.cc"
    break;

  case 209:
#line 805 "dhcp6_parser.yy"
                {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1561 "dhcp6_parser.cc"
    break;

  case 210:
#line 810 "dhcp6_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1567 "dhcp6_parser.cc"
    break;

  case 211:
#line 811 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1573 "dhcp6_parser.cc"
    break;

  case 212:
#line 812 "dhcp6_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1579 "dhcp6_parser.cc"
    break;

  case 213:
#line 813 "dhcp6_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1585 "dhcp6_parser.cc"
    break;

  case 214:
#line 816 "dhcp6_parser.yy"
           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1593 "dhcp6_parser.cc"
    break;

  case 215:
#line 818 "dhcp6_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1603 "dhcp6_parser.cc"
    break;

  case 216:
#line 824 "dhcp6_parser.yy"
                   {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1611 "dhcp6_parser.cc"
    break;

  case 217:
#line 826 "dhcp6_parser.yy"
               {
    ElementPtr pwd(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1621 "dhcp6_parser.cc"
    break;

  case 218:
#line 832 "dhcp6_parser.yy"
           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1629 "dhcp6_parser.cc"
    break;

  case 219:
#line 834 "dhcp6_parser.yy"
               {
    ElementPtr h(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1639 "dhcp6_parser.cc"
    break;

  case 220:
#line 840 "dhcp6_parser.yy"
                         {
    ElementPtr p(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1648 "dhcp6_parser.cc"
    break;

  case 221:
#line 845 "dhcp6_parser.yy"
           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1656 "dhcp6_parser.cc"
    break;

  case 222:
#line 847 "dhcp6_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1666 "dhcp6_parser.cc"
    break;

  case 223:
#line 853 "dhcp6_parser.yy"
                               {
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1675 "dhcp6_parser.cc"
    break;

  case 224:
#line 858 "dhcp6_parser.yy"
                                         {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1684 "dhcp6_parser.cc"
    break;

  case 225:
#line 863 "dhcp6_parser.yy"
                                 {
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1693 "dhcp6_parser.cc"
    break;

  case 226:
#line 868 "dhcp6_parser.yy"
                                               {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1702 "dhcp6_parser.cc"
    break;

  case 227:
#line 873 "dhcp6_parser.yy"
                                                       {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 1711 "dhcp6_parser.cc"
    break;

  case 228:
#line 878 "dhcp6_parser.yy"
                                             {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-row-errors", n);
}
#line 1720 "dhcp6_parser.cc"
    break;

  case 229:
#line 883 "dhcp6_parser.yy"
                                               {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("request-timeout", n);
}
#line 1729 "dhcp6_parser.cc"
    break;

  case 230:
#line 888 "dhcp6_parser.yy"
                                           {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-keepalive", n);
}
#line 1738 "dhcp6_parser.cc"
    break;

  case 231:
#line 893 "dhcp6_parser.yy"
                                       {
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-nodelay", n);
}
#line 1747 "dhcp6_parser.cc"
    break;

  case 232:
#line 898 "dhcp6_parser.yy"
                               {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1755 "dhcp6_parser.cc"
    break;

  case 233:
#line 900 "dhcp6_parser.yy"
               {
    ElementPtr cp(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1765 "dhcp6_parser.cc"
    break;

  case 234:
#line 906 "dhcp6_parser.yy"
                                                       {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 1774 "dhcp6_parser.cc"
    break;

  case 235:
#line 911 "dhcp6_parser.yy"
                   {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1782 "dhcp6_parser.cc"
    break;

  case 236:
#line 913 "dhcp6_parser.yy"
               {
    ElementPtr ks(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 1792 "dhcp6_parser.cc"
    break;

  case 237:
#line 919 "dhcp6_parser.yy"
                         {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1800 "dhcp6_parser.cc"
    break;

  case 238:
#line 921 "dhcp6_parser.yy"
               {
    ElementPtr c(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("consistency", c);
    ctx.leave();
}
#line 1810 "dhcp6_parser.cc"
    break;

  case 239:
#line 927 "dhcp6_parser.yy"
                                       {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1818 "dhcp6_parser.cc"
    break;

  case 240:
#line 929 "dhcp6_parser.yy"
               {
    ElementPtr c(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("serial-consistency", c);
    ctx.leave();
}
#line 1828 "dhcp6_parser.cc"
    break;

  case 241:
#line 935 "dhcp6_parser.yy"
                             {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sanity-checks", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SANITY_CHECKS);
}
#line 1839 "dhcp6_parser.cc"
    break;

  case 242:
#line 940 "dhcp6_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1848 "dhcp6_parser.cc"
    break;

  case 246:
#line 950 "dhcp6_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1856 "dhcp6_parser.cc"
    break;

  case 247:
#line 952 "dhcp6_parser.yy"
               {

    if ( (string(yystack_[0].value.as < std::string > ()) == "none") ||
         (string(yystack_[0].value.as < std::string > ()) == "warn") ||
         (string(yystack_[0].value.as < std::string > ()) == "fix") ||
         (string(yystack_[0].value.as < std::string > ()) == "fix-del") ||
         (string(yystack_[0].value.as < std::string > ()) == "del")) {
        ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
        ctx.stack_.back()->set("lease-checks", user);
        ctx.leave();
    } else {
        error(yystack_[0].location, "Unsupported 'lease-checks value: " + string(yystack_[0].value.as < std::string > ()) +
              ", supported values are: none, warn, fix, fix-del, del");
    }
}
#line 1876 "dhcp6_parser.cc"
    break;

  case 248:
#line 968 "dhcp6_parser.yy"
                         {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("mac-sources", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.MAC_SOURCES);
}
#line 1887 "dhcp6_parser.cc"
    break;

  case 249:
#line 973 "dhcp6_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1896 "dhcp6_parser.cc"
    break;

  case 254:
#line 986 "dhcp6_parser.yy"
               {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1905 "dhcp6_parser.cc"
    break;

  case 255:
#line 991 "dhcp6_parser.yy"
                   {
    ElementPtr duid(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1914 "dhcp6_parser.cc"
    break;

  case 256:
#line 996 "dhcp6_parser.yy"
                                                           {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1925 "dhcp6_parser.cc"
    break;

  case 257:
#line 1001 "dhcp6_parser.yy"
                                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1934 "dhcp6_parser.cc"
    break;

  case 263:
#line 1015 "dhcp6_parser.yy"
                           {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1943 "dhcp6_parser.cc"
    break;

  case 264:
#line 1020 "dhcp6_parser.yy"
                  {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 1952 "dhcp6_parser.cc"
    break;

  case 265:
#line 1027 "dhcp6_parser.yy"
                                               {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay-supplied-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1963 "dhcp6_parser.cc"
    break;

  case 266:
#line 1032 "dhcp6_parser.yy"
                                                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1972 "dhcp6_parser.cc"
    break;

  case 267:
#line 1039 "dhcp6_parser.yy"
                                           {
    ElementPtr mt(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("multi-threading", mt);
    ctx.stack_.push_back(mt);
    ctx.enter(ctx.DHCP_MULTI_THREADING);
}
#line 1983 "dhcp6_parser.cc"
    break;

  case 268:
#line 1044 "dhcp6_parser.yy"
                                                             {
    // The enable parameter is required.
    ctx.require("enable-multi-threading", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1994 "dhcp6_parser.cc"
    break;

  case 277:
#line 1063 "dhcp6_parser.yy"
                                                             {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-multi-threading", b);
}
#line 2003 "dhcp6_parser.cc"
    break;

  case 278:
#line 1068 "dhcp6_parser.yy"
                                                 {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("thread-pool-size", prf);
}
#line 2012 "dhcp6_parser.cc"
    break;

  case 279:
#line 1073 "dhcp6_parser.yy"
                                                   {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("packet-queue-size", prf);
}
#line 2021 "dhcp6_parser.cc"
    break;

  case 280:
#line 1078 "dhcp6_parser.yy"
                                 {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 2032 "dhcp6_parser.cc"
    break;

  case 281:
#line 1083 "dhcp6_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2041 "dhcp6_parser.cc"
    break;

  case 286:
#line 1096 "dhcp6_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2051 "dhcp6_parser.cc"
    break;

  case 287:
#line 1100 "dhcp6_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2061 "dhcp6_parser.cc"
    break;

  case 288:
#line 1106 "dhcp6_parser.yy"
                                  {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2071 "dhcp6_parser.cc"
    break;

  case 289:
#line 1110 "dhcp6_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2081 "dhcp6_parser.cc"
    break;

  case 295:
#line 1125 "dhcp6_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2089 "dhcp6_parser.cc"
    break;

  case 296:
#line 1127 "dhcp6_parser.yy"
               {
    ElementPtr lib(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 2099 "dhcp6_parser.cc"
    break;

  case 297:
#line 1133 "dhcp6_parser.yy"
                       {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2107 "dhcp6_parser.cc"
    break;

  case 298:
#line 1135 "dhcp6_parser.yy"
                  {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2116 "dhcp6_parser.cc"
    break;

  case 299:
#line 1141 "dhcp6_parser.yy"
                                                     {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 2127 "dhcp6_parser.cc"
    break;

  case 300:
#line 1146 "dhcp6_parser.yy"
                                                            {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2137 "dhcp6_parser.cc"
    break;

  case 309:
#line 1164 "dhcp6_parser.yy"
                                                               {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 2146 "dhcp6_parser.cc"
    break;

  case 310:
#line 1169 "dhcp6_parser.yy"
                                                                               {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 2155 "dhcp6_parser.cc"
    break;

  case 311:
#line 1174 "dhcp6_parser.yy"
                                                       {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 2164 "dhcp6_parser.cc"
    break;

  case 312:
#line 1179 "dhcp6_parser.yy"
                                                     {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 2173 "dhcp6_parser.cc"
    break;

  case 313:
#line 1184 "dhcp6_parser.yy"
                                                 {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 2182 "dhcp6_parser.cc"
    break;

  case 314:
#line 1189 "dhcp6_parser.yy"
                                                               {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 2191 "dhcp6_parser.cc"
    break;

  case 315:
#line 1197 "dhcp6_parser.yy"
                      {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet6", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET6);
}
#line 2202 "dhcp6_parser.cc"
    break;

  case 316:
#line 1202 "dhcp6_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2211 "dhcp6_parser.cc"
    break;

  case 321:
#line 1222 "dhcp6_parser.yy"
                        {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2221 "dhcp6_parser.cc"
    break;

  case 322:
#line 1226 "dhcp6_parser.yy"
                                {
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
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2247 "dhcp6_parser.cc"
    break;

  case 323:
#line 1248 "dhcp6_parser.yy"
                            {
    // Parse the subnet6 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2257 "dhcp6_parser.cc"
    break;

  case 324:
#line 1252 "dhcp6_parser.yy"
                                {
    // The subnet subnet6 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2267 "dhcp6_parser.cc"
    break;

  case 363:
#line 1302 "dhcp6_parser.yy"
               {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2275 "dhcp6_parser.cc"
    break;

  case 364:
#line 1304 "dhcp6_parser.yy"
               {
    ElementPtr subnet(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 2285 "dhcp6_parser.cc"
    break;

  case 365:
#line 1310 "dhcp6_parser.yy"
                     {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2293 "dhcp6_parser.cc"
    break;

  case 366:
#line 1312 "dhcp6_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 2303 "dhcp6_parser.cc"
    break;

  case 367:
#line 1318 "dhcp6_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2311 "dhcp6_parser.cc"
    break;

  case 368:
#line 1320 "dhcp6_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 2321 "dhcp6_parser.cc"
    break;

  case 369:
#line 1326 "dhcp6_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2329 "dhcp6_parser.cc"
    break;

  case 370:
#line 1328 "dhcp6_parser.yy"
               {
    ElementPtr cls(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 2339 "dhcp6_parser.cc"
    break;

  case 371:
#line 1334 "dhcp6_parser.yy"
                                               {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2350 "dhcp6_parser.cc"
    break;

  case 372:
#line 1339 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2359 "dhcp6_parser.cc"
    break;

  case 373:
#line 1344 "dhcp6_parser.yy"
                                   {
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 2367 "dhcp6_parser.cc"
    break;

  case 374:
#line 1346 "dhcp6_parser.yy"
                {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2376 "dhcp6_parser.cc"
    break;

  case 375:
#line 1351 "dhcp6_parser.yy"
                  { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 2382 "dhcp6_parser.cc"
    break;

  case 376:
#line 1352 "dhcp6_parser.yy"
                     { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 2388 "dhcp6_parser.cc"
    break;

  case 377:
#line 1353 "dhcp6_parser.yy"
                { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("global", ctx.loc2pos(yystack_[0].location))); }
#line 2394 "dhcp6_parser.cc"
    break;

  case 378:
#line 1354 "dhcp6_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 2400 "dhcp6_parser.cc"
    break;

  case 379:
#line 1357 "dhcp6_parser.yy"
                     {
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 2409 "dhcp6_parser.cc"
    break;

  case 380:
#line 1362 "dhcp6_parser.yy"
                                         {
    ElementPtr rc(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 2418 "dhcp6_parser.cc"
    break;

  case 381:
#line 1369 "dhcp6_parser.yy"
                                 {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 2429 "dhcp6_parser.cc"
    break;

  case 382:
#line 1374 "dhcp6_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2438 "dhcp6_parser.cc"
    break;

  case 387:
#line 1389 "dhcp6_parser.yy"
                               {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2448 "dhcp6_parser.cc"
    break;

  case 388:
#line 1393 "dhcp6_parser.yy"
                                       {
    ctx.stack_.pop_back();
}
#line 2456 "dhcp6_parser.cc"
    break;

  case 424:
#line 1440 "dhcp6_parser.yy"
                            {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 2467 "dhcp6_parser.cc"
    break;

  case 425:
#line 1445 "dhcp6_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2476 "dhcp6_parser.cc"
    break;

  case 426:
#line 1453 "dhcp6_parser.yy"
                                    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2485 "dhcp6_parser.cc"
    break;

  case 427:
#line 1456 "dhcp6_parser.yy"
                                 {
    // parsing completed
}
#line 2493 "dhcp6_parser.cc"
    break;

  case 432:
#line 1472 "dhcp6_parser.yy"
                                 {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2503 "dhcp6_parser.cc"
    break;

  case 433:
#line 1476 "dhcp6_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2515 "dhcp6_parser.cc"
    break;

  case 434:
#line 1487 "dhcp6_parser.yy"
                               {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2525 "dhcp6_parser.cc"
    break;

  case 435:
#line 1491 "dhcp6_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2537 "dhcp6_parser.cc"
    break;

  case 451:
#line 1523 "dhcp6_parser.yy"
                         {
    ElementPtr code(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 2546 "dhcp6_parser.cc"
    break;

  case 453:
#line 1530 "dhcp6_parser.yy"
                      {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2554 "dhcp6_parser.cc"
    break;

  case 454:
#line 1532 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 2564 "dhcp6_parser.cc"
    break;

  case 455:
#line 1538 "dhcp6_parser.yy"
                                      {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2572 "dhcp6_parser.cc"
    break;

  case 456:
#line 1540 "dhcp6_parser.yy"
               {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 2582 "dhcp6_parser.cc"
    break;

  case 457:
#line 1546 "dhcp6_parser.yy"
             {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2590 "dhcp6_parser.cc"
    break;

  case 458:
#line 1548 "dhcp6_parser.yy"
               {
    ElementPtr space(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 2600 "dhcp6_parser.cc"
    break;

  case 460:
#line 1556 "dhcp6_parser.yy"
                                    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2608 "dhcp6_parser.cc"
    break;

  case 461:
#line 1558 "dhcp6_parser.yy"
               {
    ElementPtr encap(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 2618 "dhcp6_parser.cc"
    break;

  case 462:
#line 1564 "dhcp6_parser.yy"
                                      {
    ElementPtr array(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 2627 "dhcp6_parser.cc"
    break;

  case 463:
#line 1573 "dhcp6_parser.yy"
                              {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 2638 "dhcp6_parser.cc"
    break;

  case 464:
#line 1578 "dhcp6_parser.yy"
                                                                 {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2647 "dhcp6_parser.cc"
    break;

  case 469:
#line 1597 "dhcp6_parser.yy"
                                  {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2657 "dhcp6_parser.cc"
    break;

  case 470:
#line 1601 "dhcp6_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 2666 "dhcp6_parser.cc"
    break;

  case 471:
#line 1609 "dhcp6_parser.yy"
                                {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2676 "dhcp6_parser.cc"
    break;

  case 472:
#line 1613 "dhcp6_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 2685 "dhcp6_parser.cc"
    break;

  case 487:
#line 1646 "dhcp6_parser.yy"
                       {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2693 "dhcp6_parser.cc"
    break;

  case 488:
#line 1648 "dhcp6_parser.yy"
               {
    ElementPtr data(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2703 "dhcp6_parser.cc"
    break;

  case 491:
#line 1658 "dhcp6_parser.yy"
                                                 {
    ElementPtr space(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2712 "dhcp6_parser.cc"
    break;

  case 492:
#line 1663 "dhcp6_parser.yy"
                                                   {
    ElementPtr persist(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 2721 "dhcp6_parser.cc"
    break;

  case 493:
#line 1671 "dhcp6_parser.yy"
                  {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2732 "dhcp6_parser.cc"
    break;

  case 494:
#line 1676 "dhcp6_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2741 "dhcp6_parser.cc"
    break;

  case 499:
#line 1691 "dhcp6_parser.yy"
                                {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2751 "dhcp6_parser.cc"
    break;

  case 500:
#line 1695 "dhcp6_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2761 "dhcp6_parser.cc"
    break;

  case 501:
#line 1701 "dhcp6_parser.yy"
                          {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2771 "dhcp6_parser.cc"
    break;

  case 502:
#line 1705 "dhcp6_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2781 "dhcp6_parser.cc"
    break;

  case 512:
#line 1724 "dhcp6_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2789 "dhcp6_parser.cc"
    break;

  case 513:
#line 1726 "dhcp6_parser.yy"
               {
    ElementPtr pool(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2799 "dhcp6_parser.cc"
    break;

  case 514:
#line 1732 "dhcp6_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2807 "dhcp6_parser.cc"
    break;

  case 515:
#line 1734 "dhcp6_parser.yy"
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
#line 2834 "dhcp6_parser.cc"
    break;

  case 516:
#line 1757 "dhcp6_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2842 "dhcp6_parser.cc"
    break;

  case 517:
#line 1759 "dhcp6_parser.yy"
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
#line 2871 "dhcp6_parser.cc"
    break;

  case 518:
#line 1787 "dhcp6_parser.yy"
                        {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.PD_POOLS);
}
#line 2882 "dhcp6_parser.cc"
    break;

  case 519:
#line 1792 "dhcp6_parser.yy"
                                                              {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2891 "dhcp6_parser.cc"
    break;

  case 524:
#line 1807 "dhcp6_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2901 "dhcp6_parser.cc"
    break;

  case 525:
#line 1811 "dhcp6_parser.yy"
                                {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2913 "dhcp6_parser.cc"
    break;

  case 526:
#line 1819 "dhcp6_parser.yy"
                            {
    // Parse the pd-pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2923 "dhcp6_parser.cc"
    break;

  case 527:
#line 1823 "dhcp6_parser.yy"
                                {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2935 "dhcp6_parser.cc"
    break;

  case 541:
#line 1848 "dhcp6_parser.yy"
                  {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2943 "dhcp6_parser.cc"
    break;

  case 542:
#line 1850 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix", prf);
    ctx.leave();
}
#line 2953 "dhcp6_parser.cc"
    break;

  case 543:
#line 1856 "dhcp6_parser.yy"
                                        {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix-len", prf);
}
#line 2962 "dhcp6_parser.cc"
    break;

  case 544:
#line 1861 "dhcp6_parser.yy"
                                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2970 "dhcp6_parser.cc"
    break;

  case 545:
#line 1863 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix", prf);
    ctx.leave();
}
#line 2980 "dhcp6_parser.cc"
    break;

  case 546:
#line 1869 "dhcp6_parser.yy"
                                                       {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix-len", prf);
}
#line 2989 "dhcp6_parser.cc"
    break;

  case 547:
#line 1874 "dhcp6_parser.yy"
                                              {
    ElementPtr deleg(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("delegated-len", deleg);
}
#line 2998 "dhcp6_parser.cc"
    break;

  case 548:
#line 1882 "dhcp6_parser.yy"
                           {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 3009 "dhcp6_parser.cc"
    break;

  case 549:
#line 1887 "dhcp6_parser.yy"
                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3018 "dhcp6_parser.cc"
    break;

  case 554:
#line 1900 "dhcp6_parser.yy"
                            {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3028 "dhcp6_parser.cc"
    break;

  case 555:
#line 1904 "dhcp6_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 3037 "dhcp6_parser.cc"
    break;

  case 556:
#line 1909 "dhcp6_parser.yy"
                                {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3047 "dhcp6_parser.cc"
    break;

  case 557:
#line 1913 "dhcp6_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 3056 "dhcp6_parser.cc"
    break;

  case 573:
#line 1940 "dhcp6_parser.yy"
                           {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3067 "dhcp6_parser.cc"
    break;

  case 574:
#line 1945 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3076 "dhcp6_parser.cc"
    break;

  case 575:
#line 1950 "dhcp6_parser.yy"
                   {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3087 "dhcp6_parser.cc"
    break;

  case 576:
#line 1955 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3096 "dhcp6_parser.cc"
    break;

  case 577:
#line 1960 "dhcp6_parser.yy"
           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3104 "dhcp6_parser.cc"
    break;

  case 578:
#line 1962 "dhcp6_parser.yy"
               {
    ElementPtr d(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 3114 "dhcp6_parser.cc"
    break;

  case 579:
#line 1968 "dhcp6_parser.yy"
                       {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3122 "dhcp6_parser.cc"
    break;

  case 580:
#line 1970 "dhcp6_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 3132 "dhcp6_parser.cc"
    break;

  case 581:
#line 1976 "dhcp6_parser.yy"
                   {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3140 "dhcp6_parser.cc"
    break;

  case 582:
#line 1978 "dhcp6_parser.yy"
               {
    ElementPtr host(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 3150 "dhcp6_parser.cc"
    break;

  case 583:
#line 1984 "dhcp6_parser.yy"
                       {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3158 "dhcp6_parser.cc"
    break;

  case 584:
#line 1986 "dhcp6_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 3168 "dhcp6_parser.cc"
    break;

  case 585:
#line 1992 "dhcp6_parser.yy"
                                           {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3179 "dhcp6_parser.cc"
    break;

  case 586:
#line 1997 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3188 "dhcp6_parser.cc"
    break;

  case 587:
#line 2005 "dhcp6_parser.yy"
             {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 3199 "dhcp6_parser.cc"
    break;

  case 588:
#line 2010 "dhcp6_parser.yy"
                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3208 "dhcp6_parser.cc"
    break;

  case 591:
#line 2019 "dhcp6_parser.yy"
                       {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3216 "dhcp6_parser.cc"
    break;

  case 592:
#line 2021 "dhcp6_parser.yy"
               {
    ElementPtr addr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 3226 "dhcp6_parser.cc"
    break;

  case 593:
#line 2030 "dhcp6_parser.yy"
                               {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 3237 "dhcp6_parser.cc"
    break;

  case 594:
#line 2035 "dhcp6_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3246 "dhcp6_parser.cc"
    break;

  case 597:
#line 2044 "dhcp6_parser.yy"
                                   {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3256 "dhcp6_parser.cc"
    break;

  case 598:
#line 2048 "dhcp6_parser.yy"
                                     {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3266 "dhcp6_parser.cc"
    break;

  case 611:
#line 2073 "dhcp6_parser.yy"
                        {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3274 "dhcp6_parser.cc"
    break;

  case 612:
#line 2075 "dhcp6_parser.yy"
               {
    ElementPtr test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 3284 "dhcp6_parser.cc"
    break;

  case 613:
#line 2081 "dhcp6_parser.yy"
                                                 {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 3293 "dhcp6_parser.cc"
    break;

  case 614:
#line 2089 "dhcp6_parser.yy"
                     {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-id", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER_ID);
}
#line 3304 "dhcp6_parser.cc"
    break;

  case 615:
#line 2094 "dhcp6_parser.yy"
                                                       {
    // The type parameter is required.
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3315 "dhcp6_parser.cc"
    break;

  case 627:
#line 2116 "dhcp6_parser.yy"
                     {
    ctx.enter(ctx.DUID_TYPE);
}
#line 3323 "dhcp6_parser.cc"
    break;

  case 628:
#line 2118 "dhcp6_parser.yy"
                  {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3332 "dhcp6_parser.cc"
    break;

  case 629:
#line 2123 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("LLT", ctx.loc2pos(yystack_[0].location))); }
#line 3338 "dhcp6_parser.cc"
    break;

  case 630:
#line 2124 "dhcp6_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("EN", ctx.loc2pos(yystack_[0].location))); }
#line 3344 "dhcp6_parser.cc"
    break;

  case 631:
#line 2125 "dhcp6_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("LL", ctx.loc2pos(yystack_[0].location))); }
#line 3350 "dhcp6_parser.cc"
    break;

  case 632:
#line 2128 "dhcp6_parser.yy"
                           {
    ElementPtr htype(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("htype", htype);
}
#line 3359 "dhcp6_parser.cc"
    break;

  case 633:
#line 2133 "dhcp6_parser.yy"
                       {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3367 "dhcp6_parser.cc"
    break;

  case 634:
#line 2135 "dhcp6_parser.yy"
               {
    ElementPtr id(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("identifier", id);
    ctx.leave();
}
#line 3377 "dhcp6_parser.cc"
    break;

  case 635:
#line 2141 "dhcp6_parser.yy"
                         {
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("time", time);
}
#line 3386 "dhcp6_parser.cc"
    break;

  case 636:
#line 2146 "dhcp6_parser.yy"
                                           {
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enterprise-id", time);
}
#line 3395 "dhcp6_parser.cc"
    break;

  case 637:
#line 2153 "dhcp6_parser.yy"
                                         {
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 3404 "dhcp6_parser.cc"
    break;

  case 638:
#line 2160 "dhcp6_parser.yy"
                               {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 3415 "dhcp6_parser.cc"
    break;

  case 639:
#line 2165 "dhcp6_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3424 "dhcp6_parser.cc"
    break;

  case 647:
#line 2181 "dhcp6_parser.yy"
                         {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3432 "dhcp6_parser.cc"
    break;

  case 648:
#line 2183 "dhcp6_parser.yy"
               {
    ElementPtr stype(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 3442 "dhcp6_parser.cc"
    break;

  case 649:
#line 2189 "dhcp6_parser.yy"
                         {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3450 "dhcp6_parser.cc"
    break;

  case 650:
#line 2191 "dhcp6_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 3460 "dhcp6_parser.cc"
    break;

  case 651:
#line 2200 "dhcp6_parser.yy"
                                       {
    ElementPtr qc(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-queue-control", qc);
    ctx.stack_.push_back(qc);
    ctx.enter(ctx.DHCP_QUEUE_CONTROL);
}
#line 3471 "dhcp6_parser.cc"
    break;

  case 652:
#line 2205 "dhcp6_parser.yy"
                                                           {
    // The enable queue parameter is required.
    ctx.require("enable-queue", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3482 "dhcp6_parser.cc"
    break;

  case 661:
#line 2224 "dhcp6_parser.yy"
                                         {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-queue", b);
}
#line 3491 "dhcp6_parser.cc"
    break;

  case 662:
#line 2229 "dhcp6_parser.yy"
                       {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3499 "dhcp6_parser.cc"
    break;

  case 663:
#line 2231 "dhcp6_parser.yy"
               {
    ElementPtr qt(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("queue-type", qt);
    ctx.leave();
}
#line 3509 "dhcp6_parser.cc"
    break;

  case 664:
#line 2237 "dhcp6_parser.yy"
                                 {
    ElementPtr c(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("capacity", c);
}
#line 3518 "dhcp6_parser.cc"
    break;

  case 665:
#line 2242 "dhcp6_parser.yy"
                            {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3526 "dhcp6_parser.cc"
    break;

  case 666:
#line 2244 "dhcp6_parser.yy"
              {
    ctx.stack_.back()->set(yystack_[3].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3535 "dhcp6_parser.cc"
    break;

  case 667:
#line 2251 "dhcp6_parser.yy"
                     {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 3546 "dhcp6_parser.cc"
    break;

  case 668:
#line 2256 "dhcp6_parser.yy"
                                                       {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3557 "dhcp6_parser.cc"
    break;

  case 669:
#line 2263 "dhcp6_parser.yy"
                              {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3567 "dhcp6_parser.cc"
    break;

  case 670:
#line 2267 "dhcp6_parser.yy"
                                  {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3577 "dhcp6_parser.cc"
    break;

  case 691:
#line 2297 "dhcp6_parser.yy"
                                             {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 3586 "dhcp6_parser.cc"
    break;

  case 692:
#line 2302 "dhcp6_parser.yy"
                                     {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3594 "dhcp6_parser.cc"
    break;

  case 693:
#line 2304 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 3604 "dhcp6_parser.cc"
    break;

  case 694:
#line 2310 "dhcp6_parser.yy"
                     {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3612 "dhcp6_parser.cc"
    break;

  case 695:
#line 2312 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 3622 "dhcp6_parser.cc"
    break;

  case 696:
#line 2318 "dhcp6_parser.yy"
                                       {
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 3631 "dhcp6_parser.cc"
    break;

  case 697:
#line 2323 "dhcp6_parser.yy"
                     {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3639 "dhcp6_parser.cc"
    break;

  case 698:
#line 2325 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 3649 "dhcp6_parser.cc"
    break;

  case 699:
#line 2331 "dhcp6_parser.yy"
                                       {
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 3658 "dhcp6_parser.cc"
    break;

  case 700:
#line 2336 "dhcp6_parser.yy"
                                             {
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 3667 "dhcp6_parser.cc"
    break;

  case 701:
#line 2341 "dhcp6_parser.yy"
                           {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 3675 "dhcp6_parser.cc"
    break;

  case 702:
#line 2343 "dhcp6_parser.yy"
                           {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3684 "dhcp6_parser.cc"
    break;

  case 703:
#line 2349 "dhcp6_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 3690 "dhcp6_parser.cc"
    break;

  case 704:
#line 2350 "dhcp6_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 3696 "dhcp6_parser.cc"
    break;

  case 705:
#line 2353 "dhcp6_parser.yy"
                       {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 3704 "dhcp6_parser.cc"
    break;

  case 706:
#line 2355 "dhcp6_parser.yy"
             {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 3714 "dhcp6_parser.cc"
    break;

  case 707:
#line 2362 "dhcp6_parser.yy"
                                                         {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 3723 "dhcp6_parser.cc"
    break;

  case 708:
#line 2368 "dhcp6_parser.yy"
                                                                 {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 3732 "dhcp6_parser.cc"
    break;

  case 709:
#line 2374 "dhcp6_parser.yy"
                                             {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 3740 "dhcp6_parser.cc"
    break;

  case 710:
#line 2376 "dhcp6_parser.yy"
                                       {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3749 "dhcp6_parser.cc"
    break;

  case 711:
#line 2382 "dhcp6_parser.yy"
                                       {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3757 "dhcp6_parser.cc"
    break;

  case 712:
#line 2384 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 3767 "dhcp6_parser.cc"
    break;

  case 713:
#line 2391 "dhcp6_parser.yy"
                                         {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3775 "dhcp6_parser.cc"
    break;

  case 714:
#line 2393 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 3785 "dhcp6_parser.cc"
    break;

  case 715:
#line 2400 "dhcp6_parser.yy"
                                                         {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3793 "dhcp6_parser.cc"
    break;

  case 716:
#line 2402 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 3803 "dhcp6_parser.cc"
    break;

  case 717:
#line 2411 "dhcp6_parser.yy"
                               {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 3814 "dhcp6_parser.cc"
    break;

  case 718:
#line 2416 "dhcp6_parser.yy"
                                                            {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3824 "dhcp6_parser.cc"
    break;

  case 719:
#line 2422 "dhcp6_parser.yy"
                                   {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3834 "dhcp6_parser.cc"
    break;

  case 720:
#line 2426 "dhcp6_parser.yy"
                                       {
    // No config_control params are required
    // parsing completed
}
#line 3843 "dhcp6_parser.cc"
    break;

  case 725:
#line 2441 "dhcp6_parser.yy"
                                   {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 3854 "dhcp6_parser.cc"
    break;

  case 726:
#line 2446 "dhcp6_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3863 "dhcp6_parser.cc"
    break;

  case 727:
#line 2451 "dhcp6_parser.yy"
                                                             {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-fetch-wait-time", value);
}
#line 3872 "dhcp6_parser.cc"
    break;

  case 728:
#line 2458 "dhcp6_parser.yy"
                 {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 3883 "dhcp6_parser.cc"
    break;

  case 729:
#line 2463 "dhcp6_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3892 "dhcp6_parser.cc"
    break;

  case 732:
#line 2475 "dhcp6_parser.yy"
                             {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 3902 "dhcp6_parser.cc"
    break;

  case 733:
#line 2479 "dhcp6_parser.yy"
                               {
    ctx.stack_.pop_back();
}
#line 3910 "dhcp6_parser.cc"
    break;

  case 743:
#line 2496 "dhcp6_parser.yy"
                                     {
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 3919 "dhcp6_parser.cc"
    break;

  case 744:
#line 2501 "dhcp6_parser.yy"
                   {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3927 "dhcp6_parser.cc"
    break;

  case 745:
#line 2503 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 3937 "dhcp6_parser.cc"
    break;

  case 746:
#line 2509 "dhcp6_parser.yy"
                                    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 3948 "dhcp6_parser.cc"
    break;

  case 747:
#line 2514 "dhcp6_parser.yy"
                                                                    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3957 "dhcp6_parser.cc"
    break;

  case 750:
#line 2523 "dhcp6_parser.yy"
                             {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3967 "dhcp6_parser.cc"
    break;

  case 751:
#line 2527 "dhcp6_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 3975 "dhcp6_parser.cc"
    break;

  case 759:
#line 2542 "dhcp6_parser.yy"
               {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3983 "dhcp6_parser.cc"
    break;

  case 760:
#line 2544 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 3993 "dhcp6_parser.cc"
    break;

  case 761:
#line 2550 "dhcp6_parser.yy"
                           {
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 4002 "dhcp6_parser.cc"
    break;

  case 762:
#line 2555 "dhcp6_parser.yy"
                               {
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 4011 "dhcp6_parser.cc"
    break;

  case 763:
#line 2560 "dhcp6_parser.yy"
                             {
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 4020 "dhcp6_parser.cc"
    break;

  case 764:
#line 2565 "dhcp6_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4028 "dhcp6_parser.cc"
    break;

  case 765:
#line 2567 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pattern", sev);
    ctx.leave();
}
#line 4038 "dhcp6_parser.cc"
    break;


#line 4042 "dhcp6_parser.cc"

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
  Dhcp6Parser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what ());
  }

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  Dhcp6Parser::yytnamerr_ (const char *yystr)
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
  Dhcp6Parser::symbol_name (symbol_kind_type yysymbol)
  {
    return yytnamerr_ (yytname_[yysymbol]);
  }



  // Dhcp6Parser::context.
  Dhcp6Parser::context::context (const Dhcp6Parser& yyparser, const symbol_type& yyla)
    : yyparser_ (yyparser)
    , yyla_ (yyla)
  {}

  int
  Dhcp6Parser::context::expected_tokens (symbol_kind_type yyarg[], int yyargn) const
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
  Dhcp6Parser::yy_syntax_error_arguments_ (const context& yyctx,
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
  Dhcp6Parser::yysyntax_error_ (const context& yyctx) const
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


  const short Dhcp6Parser::yypact_ninf_ = -929;

  const signed char Dhcp6Parser::yytable_ninf_ = -1;

  const short
  Dhcp6Parser::yypact_[] =
  {
     427,  -929,  -929,  -929,  -929,  -929,  -929,  -929,  -929,  -929,
    -929,  -929,  -929,  -929,  -929,    41,    33,    44,    46,    50,
      52,    56,    62,    89,   101,   109,   132,   134,   148,   179,
    -929,  -929,  -929,  -929,  -929,  -929,  -929,  -929,  -929,  -929,
    -929,  -929,  -929,  -929,  -929,  -929,  -929,  -929,  -929,  -929,
    -929,  -929,  -929,  -929,  -929,  -929,  -929,  -929,  -929,  -929,
    -929,  -929,  -929,  -929,  -929,  -929,  -929,  -929,    33,  -123,
     225,   116,    27,   487,    51,   186,   261,    59,    71,   206,
     -65,   592,   119,  -929,   249,   259,   262,   255,   271,  -929,
      75,  -929,  -929,  -929,  -929,  -929,  -929,  -929,  -929,   280,
     303,   327,   330,   339,   345,   366,   390,   391,   398,   400,
     401,  -929,   408,   410,   412,   414,   416,  -929,  -929,  -929,
     417,  -929,  -929,  -929,  -929,  -929,  -929,  -929,  -929,  -929,
    -929,  -929,  -929,  -929,  -929,  -929,  -929,   420,  -929,  -929,
    -929,  -929,  -929,  -929,  -929,   421,  -929,    92,  -929,  -929,
    -929,  -929,  -929,  -929,  -929,  -929,  -929,  -929,  -929,  -929,
    -929,  -929,  -929,  -929,  -929,  -929,  -929,  -929,  -929,  -929,
    -929,  -929,  -929,  -929,  -929,  -929,  -929,  -929,  -929,  -929,
    -929,  -929,  -929,  -929,  -929,  -929,  -929,  -929,  -929,  -929,
    -929,  -929,  -929,  -929,  -929,  -929,  -929,  -929,  -929,  -929,
    -929,  -929,   422,  -929,    96,  -929,  -929,  -929,  -929,  -929,
    -929,  -929,  -929,  -929,  -929,   423,   424,  -929,  -929,  -929,
    -929,  -929,  -929,  -929,  -929,  -929,  -929,  -929,  -929,  -929,
    -929,  -929,  -929,  -929,  -929,  -929,  -929,  -929,  -929,  -929,
    -929,   112,  -929,  -929,  -929,  -929,  -929,  -929,  -929,  -929,
    -929,  -929,  -929,  -929,  -929,  -929,  -929,  -929,  -929,  -929,
    -929,  -929,  -929,   114,  -929,  -929,  -929,  -929,  -929,   426,
    -929,   432,   436,  -929,  -929,  -929,  -929,  -929,  -929,   115,
    -929,  -929,  -929,  -929,  -929,  -929,  -929,  -929,  -929,  -929,
    -929,  -929,  -929,  -929,  -929,  -929,  -929,   289,   350,  -929,
    -929,  -929,  -929,  -929,  -929,  -929,  -929,   325,  -929,  -929,
     437,  -929,  -929,  -929,   440,  -929,  -929,   334,   442,  -929,
    -929,  -929,  -929,  -929,  -929,  -929,  -929,  -929,  -929,  -929,
    -929,  -929,   446,   448,  -929,  -929,  -929,  -929,   385,   453,
    -929,  -929,  -929,  -929,  -929,  -929,  -929,  -929,  -929,  -929,
    -929,  -929,   184,  -929,  -929,  -929,   456,  -929,  -929,   457,
    -929,   460,   462,  -929,  -929,   463,   464,  -929,  -929,  -929,
    -929,  -929,  -929,  -929,   192,  -929,  -929,  -929,  -929,  -929,
    -929,  -929,  -929,  -929,  -929,  -929,  -929,  -929,  -929,  -929,
    -929,  -929,   465,   205,  -929,  -929,  -929,  -929,    33,    33,
    -929,   263,   466,   225,  -929,   468,   472,   473,   476,   477,
     478,   288,   291,   294,   298,   301,   305,   306,   308,   311,
     292,   302,   314,   480,   316,   318,   319,   320,   321,   511,
     516,   518,   326,   520,   521,   522,   523,   524,   525,   538,
     539,   540,   541,   549,   550,   552,   553,   554,   555,   365,
     557,   558,   559,   560,   562,   564,   565,  -929,   116,  -929,
     566,   384,    27,  -929,   567,   568,   578,   579,   580,   393,
     388,   582,   585,   587,   487,  -929,   589,    51,  -929,   590,
     402,   594,   404,   405,   186,  -929,   597,   598,   600,   601,
     617,   618,   622,  -929,   261,  -929,   624,   625,   435,   627,
     628,   629,   438,  -929,    71,   630,   439,   441,  -929,   206,
     633,   640,    74,  -929,   449,   641,   644,   454,   646,   458,
     459,   647,   648,   461,   467,   651,   655,   656,   657,   592,
    -929,   659,   470,   119,  -929,  -929,  -929,   662,   673,  -929,
     496,   686,   687,   693,   694,   697,  -929,  -929,  -929,  -929,
    -929,  -929,  -929,  -929,  -929,  -929,  -929,  -929,   509,  -929,
    -929,  -929,  -929,  -929,  -100,   510,   512,  -929,   700,   702,
     703,   704,   526,   272,   709,   712,   713,   714,   715,   716,
     718,   719,   720,   722,  -929,   723,   725,   726,   727,   531,
     532,   730,  -929,   731,  -929,  -929,   732,   733,   546,   561,
     563,  -929,  -929,   731,   569,   747,  -929,   570,  -929,   571,
    -929,   572,  -929,  -929,  -929,   731,   731,   731,   573,   574,
     575,   576,  -929,   577,   581,  -929,   583,   584,   586,  -929,
    -929,   588,  -929,  -929,  -929,   591,   704,  -929,  -929,   593,
     595,  -929,   596,  -929,  -929,    84,   608,  -929,  -929,  -100,
     602,   603,   604,  -929,   751,  -929,  -929,    33,   116,  -929,
     119,    27,   285,   285,   752,  -929,  -929,  -929,  -929,  -929,
    -929,  -929,  -929,  -929,   753,   766,   767,  -929,  -929,  -929,
    -929,  -929,  -929,  -929,  -929,   769,   -73,    33,   286,   676,
     774,   776,   777,   237,    64,    67,   202,   136,   592,  -929,
    -929,   781,  -929,  -929,   784,   787,  -929,  -929,  -929,  -929,
    -929,   -61,  -929,  -929,  -929,  -929,  -929,  -929,  -929,  -929,
    -929,  -929,  -929,  -929,  -929,  -929,  -929,  -929,  -929,  -929,
    -929,  -929,  -929,  -929,  -929,  -929,  -929,  -929,  -929,  -929,
    -929,   752,  -929,   216,   223,   235,  -929,  -929,  -929,  -929,
     754,   791,   795,   796,   797,  -929,   798,   799,  -929,  -929,
    -929,   800,   801,   802,   803,  -929,   287,  -929,  -929,  -929,
    -929,  -929,  -929,  -929,  -929,  -929,  -929,  -929,  -929,  -929,
    -929,  -929,  -929,  -929,  -929,  -929,  -929,  -929,   293,  -929,
     804,   805,  -929,  -929,   806,   808,  -929,  -929,   807,   811,
    -929,  -929,   809,   813,  -929,  -929,   812,   816,  -929,  -929,
    -929,    78,  -929,  -929,  -929,   814,  -929,  -929,  -929,   146,
    -929,  -929,  -929,  -929,   296,  -929,  -929,  -929,   198,  -929,
    -929,   815,   819,  -929,  -929,   817,   821,  -929,   822,   823,
     824,   825,   826,   827,   297,  -929,  -929,  -929,  -929,  -929,
    -929,  -929,  -929,  -929,   828,   829,   830,  -929,  -929,  -929,
    -929,   300,  -929,  -929,  -929,  -929,  -929,  -929,   831,   832,
     833,  -929,   329,  -929,  -929,  -929,  -929,  -929,  -929,  -929,
    -929,  -929,  -929,  -929,   332,  -929,  -929,  -929,   834,  -929,
     835,  -929,  -929,  -929,   338,  -929,  -929,  -929,  -929,  -929,
     347,  -929,   233,  -929,   615,  -929,   836,   837,  -929,  -929,
     838,   840,  -929,  -929,  -929,   839,  -929,   842,  -929,  -929,
    -929,   841,   845,   846,   847,   658,   649,   660,   661,   664,
     848,   665,   666,   850,   852,   853,   667,   668,   669,   670,
     285,  -929,  -929,   285,  -929,   752,   487,  -929,   753,    71,
    -929,   766,   206,  -929,   767,   623,  -929,   769,   -73,  -929,
    -929,   286,  -929,   860,   676,  -929,    38,   774,  -929,   261,
    -929,   776,   -65,  -929,   777,   672,   674,   675,   677,   678,
     679,   237,  -929,   864,   867,   681,   682,   684,    64,  -929,
     683,   688,   695,    67,  -929,   888,   889,   202,  -929,   705,
     904,   729,   905,   136,  -929,  -929,   164,   781,  -929,  -929,
     915,   907,    51,  -929,   784,   186,  -929,   787,   926,  -929,
    -929,   386,   631,   742,   755,  -929,  -929,  -929,  -929,  -929,
     761,  -929,  -929,   764,   768,   771,  -929,  -929,  -929,  -929,
    -929,   348,  -929,   349,  -929,   953,  -929,   961,  -929,  -929,
    -929,  -929,  -929,  -929,  -929,  -929,  -929,  -929,  -929,  -929,
    -929,  -929,  -929,  -929,  -929,  -929,  -929,  -929,  -929,  -929,
    -929,  -929,  -929,  -929,  -929,  -929,  -929,  -929,   374,  -929,
    -929,  -929,  -929,  -929,  -929,  -929,  -929,   783,  -929,  -929,
     977,  -929,  -929,  -929,  -929,  -929,   976,   983,  -929,  -929,
    -929,  -929,  -929,   980,  -929,   375,  -929,  -929,  -929,  -929,
    -929,  -929,  -929,  -929,    81,   818,  -929,  -929,  -929,  -929,
    -929,  -929,  -929,  -929,   820,   843,  -929,  -929,   844,  -929,
      33,  -929,  -929,   987,  -929,  -929,  -929,  -929,  -929,   376,
    -929,  -929,  -929,  -929,  -929,  -929,   849,   378,  -929,   382,
    -929,   851,  -929,  -929,  -929,  -929,  -929,  -929,  -929,  -929,
    -929,  -929,  -929,  -929,  -929,  -929,  -929,  -929,   623,  -929,
    -929,   989,   854,  -929,    38,  -929,  -929,  -929,  -929,  -929,
    -929,  -929,  -929,  -929,  -929,  -929,   991,   810,   992,   164,
    -929,  -929,  -929,  -929,  -929,  -929,   859,  -929,  -929,   994,
    -929,   861,  -929,  -929,   990,  -929,  -929,   253,  -929,    12,
     990,  -929,  -929,   996,   997,   998,  -929,   389,  -929,  -929,
    -929,  -929,  -929,  -929,  -929,   999,   857,   862,   863,  1002,
      12,  -929,   865,  -929,  -929,  -929,   866,  -929,  -929,  -929
  };

  const short
  Dhcp6Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,    28,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       1,    45,    38,    34,    33,    30,    31,    32,    37,     3,
      35,    36,    58,     5,    65,     7,   161,     9,   323,    11,
     501,    13,   526,    15,   556,    17,   426,    19,   434,    21,
     471,    23,   288,    25,   669,    27,   719,    29,    47,    41,
       0,     0,     0,     0,     0,     0,   558,     0,   436,   473,
       0,     0,     0,    49,     0,    48,     0,     0,    42,    63,
       0,    60,    62,   122,   717,   159,   173,   175,   177,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   157,     0,     0,     0,     0,     0,   139,   146,   148,
       0,   315,   424,   463,   514,   516,   373,   381,   248,   265,
     256,   241,   593,   548,   280,   299,   614,     0,   267,   638,
     651,   667,   150,   152,   728,     0,   121,     0,    67,    69,
      70,    71,    72,    73,    74,    75,    76,    77,   105,   106,
     107,    78,   111,   112,   113,   114,   115,   116,   109,   110,
     117,   118,   119,   103,    81,    82,    83,    84,   100,    85,
      87,    86,   120,    91,    92,    79,   104,    80,    89,    90,
      98,    99,   101,    88,    93,    94,    95,    96,    97,   102,
     108,   170,     0,   169,     0,   163,   165,   166,   167,   168,
     493,   518,   363,   365,   367,     0,     0,   371,   369,   587,
     362,   327,   328,   329,   330,   331,   332,   333,   334,   350,
     351,   352,   355,   356,   357,   358,   359,   360,   353,   354,
     361,     0,   325,   338,   339,   340,   343,   344,   346,   341,
     342,   335,   336,   348,   349,   337,   345,   347,   512,   511,
     507,   508,   506,     0,   503,   505,   509,   510,   541,     0,
     544,     0,     0,   540,   534,   535,   533,   538,   539,     0,
     528,   530,   531,   536,   537,   532,   585,   573,   575,   577,
     579,   581,   583,   572,   569,   570,   571,     0,   559,   560,
     564,   565,   562,   566,   567,   568,   563,     0,   453,   221,
       0,   457,   455,   460,     0,   449,   450,     0,   437,   438,
     440,   452,   441,   442,   443,   459,   444,   445,   446,   447,
     448,   487,     0,     0,   485,   486,   489,   490,     0,   474,
     475,   477,   478,   479,   480,   481,   482,   483,   484,   295,
     297,   292,     0,   290,   293,   294,     0,   692,   694,     0,
     697,     0,     0,   701,   705,     0,     0,   709,   711,   713,
     715,   690,   688,   689,     0,   671,   673,   674,   675,   676,
     677,   678,   679,   680,   681,   682,   683,   684,   685,   686,
     687,   725,     0,     0,   721,   723,   724,    46,     0,     0,
      39,     0,     0,     0,    59,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    57,     0,    66,
       0,     0,     0,   162,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   324,     0,     0,   502,     0,
       0,     0,     0,     0,     0,   527,     0,     0,     0,     0,
       0,     0,     0,   557,     0,   427,     0,     0,     0,     0,
       0,     0,     0,   435,     0,     0,     0,     0,   472,     0,
       0,     0,     0,   289,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     670,     0,     0,     0,   720,    50,    43,     0,     0,    61,
       0,     0,     0,     0,     0,     0,   124,   125,   126,   127,
     128,   129,   130,   131,   132,   133,   134,   135,     0,   155,
     156,   136,   137,   138,     0,     0,     0,   154,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   637,     0,     0,     0,     0,     0,
       0,     0,    68,     0,   172,   164,     0,     0,     0,     0,
       0,   379,   380,     0,     0,     0,   326,     0,   504,     0,
     543,     0,   546,   547,   529,     0,     0,     0,     0,     0,
       0,     0,   561,     0,     0,   451,     0,     0,     0,   462,
     439,     0,   491,   492,   476,     0,     0,   291,   691,     0,
       0,   696,     0,   699,   700,     0,     0,   707,   708,     0,
       0,     0,     0,   672,     0,   727,   722,     0,     0,   123,
       0,     0,     0,     0,   179,   158,   141,   142,   143,   144,
     145,   140,   147,   149,   317,   428,   465,    40,   515,   517,
     375,   376,   377,   378,   374,   383,     0,    47,     0,     0,
       0,   550,   282,     0,     0,     0,     0,     0,     0,   151,
     153,     0,    51,   171,   495,   520,   364,   366,   368,   372,
     370,     0,   513,   542,   545,   586,   574,   576,   578,   580,
     582,   584,   454,   222,   458,   456,   461,   488,   296,   298,
     693,   695,   698,   703,   704,   702,   706,   710,   712,   714,
     716,   179,    44,     0,     0,     0,   208,   214,   216,   218,
       0,     0,     0,     0,     0,   232,     0,     0,   235,   237,
     239,     0,     0,     0,     0,   207,     0,   185,   187,   188,
     189,   190,   191,   192,   193,   194,   195,   196,   199,   206,
     200,   201,   202,   197,   198,   203,   204,   205,     0,   183,
       0,   180,   181,   321,     0,   318,   319,   432,     0,   429,
     430,   469,     0,   466,   467,   387,     0,   384,   385,   254,
     255,     0,   250,   252,   253,     0,   263,   264,   260,     0,
     258,   261,   262,   246,     0,   243,   245,   597,     0,   595,
     554,     0,   551,   552,   286,     0,   283,   284,     0,     0,
       0,     0,     0,     0,     0,   301,   303,   304,   305,   306,
     307,   308,   627,   633,     0,     0,     0,   626,   623,   624,
     625,     0,   616,   618,   621,   619,   620,   622,     0,     0,
       0,   276,     0,   269,   271,   272,   273,   274,   275,   647,
     649,   646,   644,   645,     0,   640,   642,   643,     0,   662,
       0,   665,   658,   659,     0,   653,   655,   656,   657,   660,
       0,   732,     0,   730,    53,   499,     0,   496,   497,   524,
       0,   521,   522,   591,   590,     0,   589,     0,    64,   718,
     160,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   174,   176,     0,   178,     0,     0,   316,     0,   436,
     425,     0,   473,   464,     0,     0,   382,     0,     0,   249,
     266,     0,   257,     0,     0,   242,   599,     0,   594,   558,
     549,     0,     0,   281,     0,     0,     0,     0,     0,     0,
       0,     0,   300,     0,     0,     0,     0,     0,     0,   615,
       0,     0,     0,     0,   268,     0,     0,     0,   639,     0,
       0,     0,     0,     0,   652,   668,     0,     0,   729,    55,
       0,    54,     0,   494,     0,     0,   519,     0,     0,   588,
     726,     0,     0,     0,     0,   220,   223,   224,   225,   226,
       0,   234,   227,     0,     0,     0,   229,   230,   231,   228,
     186,     0,   182,     0,   320,     0,   431,     0,   468,   423,
     402,   403,   404,   406,   407,   408,   395,   396,   411,   412,
     413,   416,   417,   418,   419,   420,   421,   414,   415,   422,
     391,   392,   393,   394,   400,   401,   399,   405,     0,   389,
     397,   409,   410,   398,   386,   251,   259,     0,   244,   611,
       0,   609,   610,   606,   607,   608,     0,   600,   601,   603,
     604,   605,   596,     0,   553,     0,   285,   309,   310,   311,
     312,   313,   314,   302,     0,     0,   632,   635,   636,   617,
     277,   278,   279,   270,     0,     0,   641,   661,     0,   664,
       0,   654,   746,     0,   744,   742,   736,   740,   741,     0,
     734,   738,   739,   737,   731,    52,     0,     0,   498,     0,
     523,     0,   210,   211,   212,   213,   209,   215,   217,   219,
     233,   236,   238,   240,   184,   322,   433,   470,     0,   388,
     247,     0,     0,   598,     0,   555,   287,   629,   630,   631,
     628,   634,   648,   650,   663,   666,     0,     0,     0,     0,
     733,    56,   500,   525,   592,   390,     0,   613,   602,     0,
     743,     0,   735,   612,     0,   745,   750,     0,   748,     0,
       0,   747,   759,     0,     0,     0,   764,     0,   752,   754,
     755,   756,   757,   758,   749,     0,     0,     0,     0,     0,
       0,   751,     0,   761,   762,   763,     0,   753,   760,   765
  };

  const short
  Dhcp6Parser::yypgoto_[] =
  {
    -929,  -929,  -929,  -929,  -929,  -929,  -929,  -929,  -929,  -929,
    -929,  -929,  -929,  -929,  -929,  -929,   -10,  -929,  -534,  -929,
     372,  -929,  -929,  -929,  -929,   154,  -929,  -555,  -929,  -929,
    -929,   -71,  -929,  -929,  -929,   606,  -929,  -929,  -929,  -929,
     352,   605,  -929,  -929,   -59,   -43,   -42,   -40,   -39,   -28,
     -27,   -26,   -23,   -21,   -15,  -929,    -9,    -3,    -1,    17,
    -929,   362,    18,  -929,    20,  -929,    25,  -929,    28,  -929,
      30,  -929,  -929,  -929,  -929,  -929,  -929,  -929,  -929,   354,
     556,  -929,  -929,  -929,  -929,  -929,  -929,  -929,  -929,  -929,
     276,  -929,    76,  -929,  -641,    79,  -929,  -929,  -929,  -929,
    -929,  -929,  -929,  -929,  -929,  -929,   -67,  -929,  -679,  -929,
    -929,  -929,  -929,  -929,  -929,  -929,  -929,  -929,  -929,  -929,
    -929,  -929,  -929,  -929,  -929,  -929,  -929,  -929,  -929,    58,
    -929,  -929,  -929,  -929,  -929,    65,  -663,  -929,  -929,  -929,
    -929,    63,  -929,  -929,  -929,  -929,  -929,  -929,  -929,    34,
    -929,  -929,  -929,  -929,  -929,  -929,  -929,    55,  -929,  -929,
    -929,    48,   514,  -929,  -929,  -929,  -929,  -929,  -929,  -929,
      49,  -929,  -929,  -929,  -929,  -929,  -929,  -928,  -929,  -929,
    -929,    83,  -929,  -929,  -929,    86,   599,  -929,  -929,  -927,
    -929,  -926,  -929,    35,  -929,    37,  -929,    32,  -929,  -929,
    -929,  -920,  -929,  -929,  -929,  -929,    77,  -929,  -929,  -135,
     958,  -929,  -929,  -929,  -929,  -929,    85,  -929,  -929,  -929,
      90,  -929,   536,  -929,   -66,  -929,  -929,  -929,  -929,  -929,
     -47,  -929,  -929,  -929,  -929,  -929,    13,  -929,  -929,  -929,
      87,  -929,  -929,  -929,    94,  -929,   533,  -929,  -929,  -929,
    -929,  -929,  -929,  -929,  -929,  -929,  -929,  -929,    42,  -929,
    -929,  -929,    36,   607,  -929,  -929,   -55,  -929,     1,  -929,
    -929,  -929,  -929,  -929,    45,  -929,  -929,  -929,    29,   609,
    -929,  -929,  -929,  -929,  -929,  -929,  -929,   -57,  -929,  -929,
    -929,    93,  -929,  -929,  -929,    97,  -929,   610,   356,  -929,
    -929,  -929,  -929,  -929,  -929,  -929,  -929,  -929,  -929,  -929,
    -929,  -929,  -919,  -929,  -929,  -929,  -929,  -929,  -929,  -929,
      98,  -929,  -929,  -929,  -113,  -929,  -929,  -929,  -929,  -929,
    -929,  -929,    80,  -929,  -929,  -929,  -929,  -929,  -929,  -929,
    -929,  -929,  -929,  -929,  -929,    72,  -929,  -929,  -929,  -929,
    -929,  -929,  -929,    68,  -929,  -929,  -929,  -929,  -929,  -929,
    -929,  -929,  -929,  -929,   377,   543,  -929,  -929,  -929,  -929,
    -929,  -929,  -929,  -929,  -929,  -929,  -929,  -929,  -929,  -929,
    -929,  -929,  -929,  -929,  -929,  -929,  -929,  -929,  -929,  -929,
    -929,  -929,  -929,  -929,  -929,   418,   537,  -929,  -929,  -929,
    -929,  -929,  -929,    69,  -929,  -929,  -115,  -929,  -929,  -929,
    -929,  -929,  -929,  -133,  -929,  -929,  -151,  -929,  -929,  -929,
    -929,  -929,  -929,  -929
  };

  const short
  Dhcp6Parser::yydefgoto_[] =
  {
      -1,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    83,    39,    40,    69,
     678,    87,    88,    41,    68,    84,    85,   703,   904,  1010,
    1011,   765,    43,    70,    90,    91,    92,   402,    45,    71,
     147,   148,   149,   405,   150,   151,   152,   153,   154,   155,
     156,   157,   158,   159,   160,   161,   162,   163,   164,   165,
     429,   671,   166,   430,   167,   431,   168,   454,   169,   455,
     170,   171,   172,   173,   423,   174,   407,    47,    72,   204,
     205,   206,   460,   207,   175,   408,   176,   409,   177,   410,
     790,   791,   792,   943,   766,   767,   768,   921,  1156,   769,
     922,   770,   923,   771,   924,   772,   773,   497,   774,   775,
     776,   777,   778,   779,   780,   781,   782,   783,   930,   784,
     785,   933,   786,   934,   787,   935,   178,   443,   824,   825,
     826,   963,   179,   440,   811,   812,   813,   814,   180,   442,
     819,   820,   821,   822,   181,   441,   182,   450,   872,   873,
     874,   875,   876,   183,   446,   835,   836,   837,   972,    63,
      80,   352,   353,   354,   510,   355,   511,   184,   447,   844,
     845,   846,   847,   848,   849,   850,   851,   185,   433,   794,
     795,   796,   946,    49,    73,   241,   242,   243,   466,   244,
     467,   245,   468,   246,   472,   247,   471,   186,   438,   684,
     249,   250,   187,   439,   806,   807,   808,   955,  1078,  1079,
     188,   434,    57,    77,   798,   799,   800,   949,    59,    78,
     317,   318,   319,   320,   321,   322,   323,   496,   324,   500,
     325,   499,   326,   327,   501,   328,   189,   435,   802,   803,
     804,   952,    61,    79,   338,   339,   340,   341,   342,   505,
     343,   344,   345,   346,   252,   464,   906,   907,   908,  1012,
      51,    74,   263,   264,   265,   476,   190,   436,   191,   437,
     255,   465,   910,   911,   912,  1015,    53,    75,   279,   280,
     281,   479,   282,   283,   481,   284,   285,   192,   445,   831,
     832,   833,   969,    55,    76,   297,   298,   299,   300,   487,
     301,   488,   302,   489,   303,   490,   304,   491,   305,   492,
     306,   486,   257,   473,   915,   916,  1018,   193,   444,   828,
     829,   966,  1096,  1097,  1098,  1099,  1100,  1171,  1101,   194,
     448,   861,   862,   863,   983,  1180,   864,   865,   984,   866,
     867,   195,   196,   451,   884,   885,   886,   995,   887,   996,
     197,   452,   894,   895,   896,   897,  1000,   898,   899,  1002,
     198,   453,    65,    81,   374,   375,   376,   377,   515,   378,
     516,   379,   380,   518,   381,   382,   383,   521,   735,   384,
     522,   385,   386,   387,   525,   388,   526,   389,   527,   390,
     528,   199,   406,    67,    82,   393,   394,   395,   531,   396,
     200,   456,   902,   903,  1006,  1139,  1140,  1141,  1142,  1188,
    1143,  1186,  1207,  1208,  1209,  1217,  1218,  1219,  1225,  1220,
    1221,  1222,  1223,  1229
  };

  const short
  Dhcp6Parser::yytable_[] =
  {
     146,   203,   220,   259,   273,   293,    38,   315,   334,   351,
     371,   316,   335,   336,   221,   858,   256,   208,   253,   266,
     277,   295,   788,   329,   347,   818,   372,  1071,  1072,  1073,
     222,   223,   337,   224,   225,  1077,  1083,   677,    31,   809,
      32,    30,    33,   201,   202,   226,   227,   228,   709,   287,
     229,    42,   230,    44,   349,   350,   913,    46,   231,    48,
     715,   716,   717,    50,   232,   666,   667,   668,   669,    52,
     233,    86,   234,   209,   254,   267,   278,   296,   403,   330,
     348,   958,   373,   404,   959,   852,   251,   262,   276,   294,
     235,   236,   308,   237,   751,   458,    54,   670,   238,   462,
     459,   239,   677,   240,   463,   248,   123,   309,    56,   260,
     274,   261,   275,   124,   125,   474,    58,   477,   484,   123,
     475,   810,   478,   485,   124,   125,   122,    93,    94,   145,
     258,    95,   391,   392,    96,    97,    98,   124,   125,    60,
     309,    62,   310,   311,  1089,  1090,   312,   313,   314,   961,
     124,   125,   962,   124,   125,    64,   217,   124,   125,   218,
      99,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,   112,   113,   114,   115,   116,   117,   118,
     119,   120,   121,   122,   123,  1212,    66,   512,  1213,  1214,
    1215,  1216,   513,   349,   350,   529,   853,   854,   855,   856,
     530,   967,   124,   125,   968,   868,   869,   870,   533,   126,
    1177,  1178,  1179,   534,   127,   128,   129,   130,   131,   458,
     132,   145,   124,   125,   918,   133,   533,    34,    35,    36,
      37,   919,   145,   309,   134,    89,  1007,   135,   462,  1008,
    1071,  1072,  1073,   920,   136,   145,   733,   734,  1077,  1083,
     124,   125,   137,   138,   123,   397,  1210,   139,   145,  1211,
     140,   145,   398,   400,   141,   145,   399,   268,   269,   270,
     271,   272,   124,   125,   401,   309,   331,   310,   311,   332,
     333,   888,   889,   890,   411,   142,   143,   144,   124,   125,
     940,   217,   124,   125,   218,   941,   940,   493,   818,   964,
     981,   942,  1041,   988,   965,   982,   746,   412,   989,   858,
     145,   747,   748,   749,   750,   751,   752,   753,   754,   755,
     756,   757,   758,   759,   760,   761,   762,   763,   764,   123,
     891,   413,   993,   495,   414,   997,  1132,   994,  1133,  1134,
     998,  1003,   503,   415,   879,   880,  1004,   124,   125,   416,
     529,   940,   474,   494,   309,  1005,  1164,  1165,   145,   838,
     839,   840,   841,   842,   843,   286,   680,   681,   682,   683,
     417,   287,   288,   289,   290,   291,   292,  1168,   512,  1189,
     145,   477,  1169,  1176,  1190,   484,  1192,   146,   535,   536,
    1193,   203,  1230,   508,   418,   419,   145,  1231,   809,   816,
     145,   817,   420,   220,   421,   422,   259,   208,  1152,  1153,
    1154,  1155,   424,   273,   425,   221,   426,   256,   427,   253,
     428,   432,   266,   293,   449,   457,   461,   469,   470,   277,
     480,   222,   223,   315,   224,   225,   482,   316,   334,   295,
     483,   498,   335,   336,   502,   504,   226,   227,   228,   329,
     506,   229,   507,   230,   347,   145,   509,   537,   371,   231,
     514,   517,   337,   209,   519,   232,   520,   523,   524,   532,
     538,   233,   540,   234,   372,   254,   541,   542,   267,   145,
     543,   544,   545,   546,   558,   278,   547,   251,   555,   548,
     262,   235,   236,   549,   237,   296,   550,   276,   556,   238,
     551,   552,   239,   553,   240,   330,   248,   294,   554,   557,
     348,   559,   260,   560,   261,   564,   561,   562,   563,   274,
     565,   275,   566,   567,   568,   569,   570,   571,   572,   573,
     373,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   574,   575,   576,   577,   114,   115,   116,   117,
     118,   119,   120,   578,   579,   123,   580,   581,   582,   583,
     584,   585,   586,   587,   588,   210,   589,   211,   590,   591,
     593,   596,   597,   124,   125,   212,   213,   214,   215,   216,
     126,   594,   598,   599,   600,   602,   603,   146,   601,   604,
     203,   605,   217,   607,   609,   218,   133,   610,   611,   612,
     613,   615,   616,   219,   617,   618,   208,     1,     2,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,   619,   620,   857,   871,   881,   621,   371,   623,   624,
     625,   626,   627,   628,   631,   629,   632,   635,   633,   859,
     877,   882,   892,   372,   636,   639,   638,   742,   640,   641,
     642,   645,   646,   643,   644,   649,   142,   143,   647,   650,
     651,   652,   209,   654,   648,   655,   657,    99,   100,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   124,   125,
     658,   145,   114,   115,   116,   117,   118,   119,   120,   121,
     659,   123,   309,   660,   661,   860,   878,   883,   893,   373,
     662,   663,   664,   665,   672,   674,   673,   675,   676,   124,
     125,    32,   213,   214,   685,   216,   126,   686,   687,   688,
     679,   690,   689,   691,   692,   699,   700,   693,   217,   694,
     695,   218,   696,   697,   698,   701,   702,   704,   705,   219,
     706,   356,   357,   358,   359,   360,   361,   362,   363,   364,
     365,   366,   367,   368,   711,   707,   741,   708,   925,   789,
     793,   369,   370,   710,   712,   713,   714,   718,   719,   720,
     721,   722,   736,   797,   801,   723,   805,   724,   725,   823,
     726,   827,   727,   830,   834,   728,   145,   730,   901,   731,
     732,   905,   142,   143,   909,   926,   738,   739,   740,   927,
     928,   929,   931,   932,   936,   937,   938,   939,   945,  1009,
     944,   948,   947,   950,   951,   953,   954,   145,   956,   957,
     960,   970,   971,   973,   974,  1157,   975,   976,   977,   978,
     979,   980,   985,   986,   987,   990,   991,   992,   999,  1001,
    1014,   815,  1013,  1017,  1016,  1021,  1026,  1019,  1020,  1022,
    1023,  1024,  1030,  1025,  1033,  1027,  1034,  1035,  1028,  1029,
    1031,  1032,  1036,  1037,  1087,  1039,  1038,  1107,  1114,  1108,
    1109,  1115,  1110,  1111,  1112,   220,  1116,  1117,   315,  1118,
    1120,   334,   316,  1121,  1049,   335,   336,   221,  1070,   256,
    1122,   253,  1124,  1125,   329,  1091,  1050,   347,   293,  1092,
    1081,   351,  1127,   222,   223,   337,   224,   225,  1128,  1130,
    1146,  1094,  1051,  1052,   295,  1053,  1054,   857,   226,   227,
     228,  1145,   871,   229,  1129,   230,   881,  1055,  1056,  1057,
    1151,   231,  1058,   859,  1059,  1135,  1158,   232,   877,  1136,
    1060,   259,   882,   233,   273,   234,  1061,   254,   892,  1159,
     330,  1137,  1062,   348,  1063,  1160,  1082,   266,  1161,   251,
     277,  1166,  1162,   235,   236,  1163,   237,  1095,  1080,  1167,
     296,   238,  1064,  1065,   239,  1066,   240,  1170,   248,  1093,
    1067,  1172,   294,  1068,  1173,  1069,  1174,  1076,  1175,   860,
    1074,  1187,  1075,  1196,   878,  1199,  1201,  1206,   883,  1204,
    1226,  1227,  1228,  1232,   893,  1200,  1236,  1138,   729,   539,
     743,   737,  1181,   267,  1182,   745,   278,   917,   595,  1040,
    1105,  1042,  1088,  1085,  1086,   262,   637,  1123,   276,  1106,
    1113,  1044,  1043,  1195,  1084,   307,  1046,  1183,  1184,  1045,
     630,  1048,   634,  1191,  1149,  1194,  1047,   260,  1147,   261,
     274,  1197,   275,  1203,  1233,  1205,  1148,  1234,  1235,  1238,
    1239,  1198,  1150,   592,  1104,  1102,  1103,   914,  1119,  1126,
     656,  1131,   653,   606,  1202,   900,  1144,  1224,   744,  1237,
       0,     0,     0,     0,   608,     0,     0,     0,     0,     0,
       0,     0,     0,   614,     0,     0,     0,  1049,     0,     0,
       0,  1070,     0,  1091,   622,     0,     0,  1092,     0,  1050,
       0,     0,     0,  1081,     0,     0,     0,     0,  1135,  1094,
    1185,     0,  1136,     0,     0,  1051,  1052,     0,  1053,  1054,
       0,     0,     0,     0,  1137,     0,     0,     0,     0,     0,
    1055,  1056,  1057,     0,     0,  1058,     0,  1059,     0,     0,
       0,     0,     0,  1060,     0,     0,     0,     0,     0,  1061,
       0,     0,     0,     0,     0,  1062,     0,  1063,     0,  1082,
       0,     0,     0,     0,     0,  1095,     0,     0,     0,     0,
       0,  1080,     0,     0,     0,  1064,  1065,  1093,  1066,     0,
    1138,     0,     0,  1067,     0,     0,  1068,     0,  1069,     0,
    1076,     0,     0,  1074,     0,  1075
  };

  const short
  Dhcp6Parser::yycheck_[] =
  {
      71,    72,    73,    74,    75,    76,    16,    78,    79,    80,
      81,    78,    79,    79,    73,   694,    73,    72,    73,    74,
      75,    76,   663,    78,    79,   688,    81,   955,   955,   955,
      73,    73,    79,    73,    73,   955,   955,   571,     5,   112,
       7,     0,     9,    16,    17,    73,    73,    73,   603,   110,
      73,     7,    73,     7,   119,   120,   117,     7,    73,     7,
     615,   616,   617,     7,    73,   165,   166,   167,   168,     7,
      73,   194,    73,    72,    73,    74,    75,    76,     3,    78,
      79,     3,    81,     8,     6,    21,    73,    74,    75,    76,
      73,    73,    21,    73,    30,     3,     7,   197,    73,     3,
       8,    73,   636,    73,     8,    73,    68,    69,     7,    74,
      75,    74,    75,    86,    87,     3,     7,     3,     3,    68,
       8,   194,     8,     8,    86,    87,    67,    11,    12,   194,
      79,    15,    13,    14,    18,    19,    20,    86,    87,     7,
      69,     7,    71,    72,   106,   107,    75,    76,    77,     3,
      86,    87,     6,    86,    87,     7,   105,    86,    87,   108,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,   173,     7,     3,   176,   177,
     178,   179,     8,   119,   120,     3,   132,   133,   134,   135,
       8,     3,    86,    87,     6,   138,   139,   140,     3,    93,
     129,   130,   131,     8,    98,    99,   100,   101,   102,     3,
     104,   194,    86,    87,     8,   109,     3,   194,   195,   196,
     197,     8,   194,    69,   118,    10,     3,   121,     3,     6,
    1168,  1168,  1168,     8,   128,   194,   162,   163,  1168,  1168,
      86,    87,   136,   137,    68,     6,     3,   141,   194,     6,
     144,   194,     3,     8,   148,   194,     4,    81,    82,    83,
      84,    85,    86,    87,     3,    69,    70,    71,    72,    73,
      74,   145,   146,   147,     4,   169,   170,   171,    86,    87,
       3,   105,    86,    87,   108,     8,     3,     8,   961,     3,
       3,     8,   943,     3,     8,     8,    21,     4,     8,   988,
     194,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    68,
     194,     4,     3,     8,     4,     3,   172,     8,   174,   175,
       8,     3,     8,     4,   142,   143,     8,    86,    87,     4,
       3,     3,     3,     3,    69,     8,     8,     8,   194,   122,
     123,   124,   125,   126,   127,   104,    94,    95,    96,    97,
       4,   110,   111,   112,   113,   114,   115,     3,     3,     3,
     194,     3,     8,     8,     8,     3,     8,   458,   398,   399,
       8,   462,     3,     8,     4,     4,   194,     8,   112,   113,
     194,   115,     4,   474,     4,     4,   477,   462,    22,    23,
      24,    25,     4,   484,     4,   474,     4,   474,     4,   474,
       4,     4,   477,   494,     4,     4,     4,     4,     4,   484,
       4,   474,   474,   504,   474,   474,     4,   504,   509,   494,
       4,     4,   509,   509,     4,     3,   474,   474,   474,   504,
       4,   474,     4,   474,   509,   194,     3,   194,   529,   474,
       4,     4,   509,   462,     4,   474,     4,     4,     4,     4,
       4,   474,     4,   474,   529,   474,     4,     4,   477,   194,
       4,     4,     4,   195,     4,   484,   195,   474,   196,   195,
     477,   474,   474,   195,   474,   494,   195,   484,   196,   474,
     195,   195,   474,   195,   474,   504,   474,   494,   197,   195,
     509,   195,   477,   195,   477,     4,   197,   197,   197,   484,
       4,   484,     4,   197,     4,     4,     4,     4,     4,     4,
     529,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,     4,     4,     4,     4,    59,    60,    61,    62,
      63,    64,    65,     4,     4,    68,     4,     4,     4,     4,
     195,     4,     4,     4,     4,    78,     4,    80,     4,     4,
       4,     4,     4,    86,    87,    88,    89,    90,    91,    92,
      93,   197,     4,     4,     4,   197,     4,   658,   195,     4,
     661,     4,   105,     4,     4,   108,   109,   195,     4,   195,
     195,     4,     4,   116,     4,     4,   661,   180,   181,   182,
     183,   184,   185,   186,   187,   188,   189,   190,   191,   192,
     193,     4,     4,   694,   695,   696,     4,   698,     4,     4,
     195,     4,     4,     4,     4,   197,   197,     4,   197,   694,
     695,   696,   697,   698,     4,     4,   197,   657,     4,   195,
       4,     4,     4,   195,   195,     4,   169,   170,   197,     4,
       4,     4,   661,     4,   197,   195,     4,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    86,    87,
       7,   194,    59,    60,    61,    62,    63,    64,    65,    66,
     194,    68,    69,     7,     7,   694,   695,   696,   697,   698,
       7,     7,     5,   194,   194,     5,   194,     5,     5,    86,
      87,     7,    89,    90,     5,    92,    93,     5,     5,     5,
     194,     5,     7,     5,     5,   194,   194,     7,   105,     7,
       7,   108,     7,     7,     7,     5,     5,     5,     5,   116,
     194,   149,   150,   151,   152,   153,   154,   155,   156,   157,
     158,   159,   160,   161,     7,   194,     5,   194,     4,     7,
       7,   169,   170,   194,   194,   194,   194,   194,   194,   194,
     194,   194,   164,     7,     7,   194,     7,   194,   194,   103,
     194,     7,   194,     7,     7,   194,   194,   194,     7,   194,
     194,     7,   169,   170,     7,     4,   194,   194,   194,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     3,   194,
       6,     3,     6,     6,     3,     6,     3,   194,     6,     3,
       6,     6,     3,     6,     3,   194,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       3,   687,     6,     3,     6,     4,   197,     8,     6,     4,
       4,     4,     4,   195,     4,   195,     4,     4,   197,   195,
     195,   195,   195,   195,     4,   195,   197,   195,     4,   195,
     195,     4,   195,   195,   195,   946,   195,   195,   949,   195,
     197,   952,   949,   195,   955,   952,   952,   946,   955,   946,
     195,   946,     4,     4,   949,   966,   955,   952,   969,   966,
     955,   972,   197,   946,   946,   952,   946,   946,     4,     4,
       3,   966,   955,   955,   969,   955,   955,   988,   946,   946,
     946,     6,   993,   946,   195,   946,   997,   955,   955,   955,
       4,   946,   955,   988,   955,  1006,   194,   946,   993,  1006,
     955,  1012,   997,   946,  1015,   946,   955,   946,  1003,   194,
     949,  1006,   955,   952,   955,   194,   955,  1012,   194,   946,
    1015,     8,   194,   946,   946,   194,   946,   966,   955,     8,
     969,   946,   955,   955,   946,   955,   946,   194,   946,   966,
     955,     4,   969,   955,     8,   955,     3,   955,     8,   988,
     955,     4,   955,     4,   993,     4,     4,     7,   997,     5,
       4,     4,     4,     4,  1003,   195,     4,  1006,   636,   403,
     658,   649,   194,  1012,   194,   661,  1015,   741,   462,   940,
     972,   945,   964,   958,   961,  1012,   512,   993,  1015,   974,
     981,   948,   946,  1168,   957,    77,   951,   194,   194,   949,
     504,   954,   509,   194,  1015,   194,   952,  1012,  1012,  1012,
    1015,   197,  1015,   194,   197,   194,  1014,   195,   195,   194,
     194,  1174,  1017,   458,   971,   967,   969,   711,   988,   997,
     533,  1003,   529,   474,  1189,   698,  1007,  1210,   660,  1230,
      -1,    -1,    -1,    -1,   477,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   484,    -1,    -1,    -1,  1168,    -1,    -1,
      -1,  1168,    -1,  1174,   494,    -1,    -1,  1174,    -1,  1168,
      -1,    -1,    -1,  1168,    -1,    -1,    -1,    -1,  1189,  1174,
    1130,    -1,  1189,    -1,    -1,  1168,  1168,    -1,  1168,  1168,
      -1,    -1,    -1,    -1,  1189,    -1,    -1,    -1,    -1,    -1,
    1168,  1168,  1168,    -1,    -1,  1168,    -1,  1168,    -1,    -1,
      -1,    -1,    -1,  1168,    -1,    -1,    -1,    -1,    -1,  1168,
      -1,    -1,    -1,    -1,    -1,  1168,    -1,  1168,    -1,  1168,
      -1,    -1,    -1,    -1,    -1,  1174,    -1,    -1,    -1,    -1,
      -1,  1168,    -1,    -1,    -1,  1168,  1168,  1174,  1168,    -1,
    1189,    -1,    -1,  1168,    -1,    -1,  1168,    -1,  1168,    -1,
    1168,    -1,    -1,  1168,    -1,  1168
  };

  const short
  Dhcp6Parser::yystos_[] =
  {
       0,   180,   181,   182,   183,   184,   185,   186,   187,   188,
     189,   190,   191,   192,   193,   199,   200,   201,   202,   203,
     204,   205,   206,   207,   208,   209,   210,   211,   212,   213,
       0,     5,     7,     9,   194,   195,   196,   197,   214,   215,
     216,   221,     7,   230,     7,   236,     7,   275,     7,   381,
       7,   458,     7,   474,     7,   491,     7,   410,     7,   416,
       7,   440,     7,   357,     7,   560,     7,   591,   222,   217,
     231,   237,   276,   382,   459,   475,   492,   411,   417,   441,
     358,   561,   592,   214,   223,   224,   194,   219,   220,    10,
     232,   233,   234,    11,    12,    15,    18,    19,    20,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    86,    87,    93,    98,    99,   100,
     101,   102,   104,   109,   118,   121,   128,   136,   137,   141,
     144,   148,   169,   170,   171,   194,   229,   238,   239,   240,
     242,   243,   244,   245,   246,   247,   248,   249,   250,   251,
     252,   253,   254,   255,   256,   257,   260,   262,   264,   266,
     268,   269,   270,   271,   273,   282,   284,   286,   324,   330,
     336,   342,   344,   351,   365,   375,   395,   400,   408,   434,
     464,   466,   485,   515,   527,   539,   540,   548,   558,   589,
     598,    16,    17,   229,   277,   278,   279,   281,   464,   466,
      78,    80,    88,    89,    90,    91,    92,   105,   108,   116,
     229,   242,   243,   244,   245,   246,   247,   248,   249,   250,
     251,   252,   254,   255,   256,   257,   260,   262,   264,   266,
     268,   383,   384,   385,   387,   389,   391,   393,   395,   398,
     399,   434,   452,   464,   466,   468,   485,   510,    79,   229,
     391,   393,   434,   460,   461,   462,   464,   466,    81,    82,
      83,    84,    85,   229,   391,   393,   434,   464,   466,   476,
     477,   478,   480,   481,   483,   484,   104,   110,   111,   112,
     113,   114,   115,   229,   434,   464,   466,   493,   494,   495,
     496,   498,   500,   502,   504,   506,   508,   408,    21,    69,
      71,    72,    75,    76,    77,   229,   304,   418,   419,   420,
     421,   422,   423,   424,   426,   428,   430,   431,   433,   464,
     466,    70,    73,    74,   229,   304,   422,   428,   442,   443,
     444,   445,   446,   448,   449,   450,   451,   464,   466,   119,
     120,   229,   359,   360,   361,   363,   149,   150,   151,   152,
     153,   154,   155,   156,   157,   158,   159,   160,   161,   169,
     170,   229,   464,   466,   562,   563,   564,   565,   567,   569,
     570,   572,   573,   574,   577,   579,   580,   581,   583,   585,
     587,    13,    14,   593,   594,   595,   597,     6,     3,     4,
       8,     3,   235,     3,     8,   241,   590,   274,   283,   285,
     287,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,   272,     4,     4,     4,     4,     4,   258,
     261,   263,     4,   376,   409,   435,   465,   467,   396,   401,
     331,   343,   337,   325,   516,   486,   352,   366,   528,     4,
     345,   541,   549,   559,   265,   267,   599,     4,     3,     8,
     280,     4,     3,     8,   453,   469,   386,   388,   390,     4,
       4,   394,   392,   511,     3,     8,   463,     3,     8,   479,
       4,   482,     4,     4,     3,     8,   509,   497,   499,   501,
     503,   505,   507,     8,     3,     8,   425,   305,     4,   429,
     427,   432,     4,     8,     3,   447,     4,     4,     8,     3,
     362,   364,     3,     8,     4,   566,   568,     4,   571,     4,
       4,   575,   578,     4,     4,   582,   584,   586,   588,     3,
       8,   596,     4,     3,     8,   214,   214,   194,     4,   233,
       4,     4,     4,     4,     4,     4,   195,   195,   195,   195,
     195,   195,   195,   195,   197,   196,   196,   195,     4,   195,
     195,   197,   197,   197,     4,     4,     4,   197,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,   195,     4,     4,     4,     4,     4,
       4,     4,   239,     4,   197,   278,     4,     4,     4,     4,
       4,   195,   197,     4,     4,     4,   384,     4,   461,     4,
     195,     4,   195,   195,   477,     4,     4,     4,     4,     4,
       4,     4,   495,     4,     4,   195,     4,     4,     4,   197,
     420,     4,   197,   197,   444,     4,     4,   360,   197,     4,
       4,   195,     4,   195,   195,     4,     4,   197,   197,     4,
       4,     4,     4,   563,     4,   195,   594,     4,     7,   194,
       7,     7,     7,     7,     5,   194,   165,   166,   167,   168,
     197,   259,   194,   194,     5,     5,     5,   216,   218,   194,
      94,    95,    96,    97,   397,     5,     5,     5,     5,     7,
       5,     5,     5,     7,     7,     7,     7,     7,     7,   194,
     194,     5,     5,   225,     5,     5,   194,   194,   194,   225,
     194,     7,   194,   194,   194,   225,   225,   225,   194,   194,
     194,   194,   194,   194,   194,   194,   194,   194,   194,   218,
     194,   194,   194,   162,   163,   576,   164,   259,   194,   194,
     194,     5,   214,   238,   593,   277,    21,    26,    27,    28,
      29,    30,    31,    32,    33,    34,    35,    36,    37,    38,
      39,    40,    41,    42,    43,   229,   292,   293,   294,   297,
     299,   301,   303,   304,   306,   307,   308,   309,   310,   311,
     312,   313,   314,   315,   317,   318,   320,   322,   292,     7,
     288,   289,   290,     7,   377,   378,   379,     7,   412,   413,
     414,     7,   436,   437,   438,     7,   402,   403,   404,   112,
     194,   332,   333,   334,   335,   223,   113,   115,   334,   338,
     339,   340,   341,   103,   326,   327,   328,     7,   517,   518,
       7,   487,   488,   489,     7,   353,   354,   355,   122,   123,
     124,   125,   126,   127,   367,   368,   369,   370,   371,   372,
     373,   374,    21,   132,   133,   134,   135,   229,   306,   464,
     466,   529,   530,   531,   534,   535,   537,   538,   138,   139,
     140,   229,   346,   347,   348,   349,   350,   464,   466,   142,
     143,   229,   464,   466,   542,   543,   544,   546,   145,   146,
     147,   194,   464,   466,   550,   551,   552,   553,   555,   556,
     562,     7,   600,   601,   226,     7,   454,   455,   456,     7,
     470,   471,   472,   117,   496,   512,   513,   288,     8,     8,
       8,   295,   298,   300,   302,     4,     4,     4,     4,     4,
     316,     4,     4,   319,   321,   323,     4,     4,     4,     4,
       3,     8,     8,   291,     6,     3,   380,     6,     3,   415,
       6,     3,   439,     6,     3,   405,     6,     3,     3,     6,
       6,     3,     6,   329,     3,     8,   519,     3,     6,   490,
       6,     3,   356,     6,     3,     4,     4,     4,     4,     4,
       4,     3,     8,   532,   536,     4,     4,     4,     3,     8,
       4,     4,     4,     3,     8,   545,   547,     3,     8,     4,
     554,     4,   557,     3,     8,     8,   602,     3,     6,   194,
     227,   228,   457,     6,     3,   473,     6,     3,   514,     8,
       6,     4,     4,     4,     4,   195,   197,   195,   197,   195,
       4,   195,   195,     4,     4,     4,   195,   195,   197,   195,
     293,   292,   290,   383,   379,   418,   414,   442,   438,   229,
     242,   243,   244,   245,   246,   247,   248,   249,   250,   251,
     252,   254,   255,   256,   257,   260,   262,   264,   266,   268,
     304,   375,   387,   389,   391,   393,   395,   399,   406,   407,
     434,   464,   466,   510,   404,   333,   339,     4,   327,   106,
     107,   229,   304,   434,   464,   466,   520,   521,   522,   523,
     524,   526,   518,   493,   489,   359,   355,   195,   195,   195,
     195,   195,   195,   368,     4,     4,   195,   195,   195,   530,
     197,   195,   195,   347,     4,     4,   543,   197,     4,   195,
       4,   551,   172,   174,   175,   229,   304,   464,   466,   603,
     604,   605,   606,   608,   601,     6,     3,   460,   456,   476,
     472,     4,    22,    23,    24,    25,   296,   194,   194,   194,
     194,   194,   194,   194,     8,     8,     8,     8,     3,     8,
     194,   525,     4,     8,     3,     8,     8,   129,   130,   131,
     533,   194,   194,   194,   194,   214,   609,     4,   607,     3,
       8,   194,     8,     8,   194,   407,     4,   197,   522,     4,
     195,     4,   604,   194,     5,   194,     7,   610,   611,   612,
       3,     6,   173,   176,   177,   178,   179,   613,   614,   615,
     617,   618,   619,   620,   611,   616,     4,     4,     4,   621,
       3,     8,     4,   197,   195,   195,     4,   614,   194,   194
  };

  const short
  Dhcp6Parser::yyr1_[] =
  {
       0,   198,   200,   199,   201,   199,   202,   199,   203,   199,
     204,   199,   205,   199,   206,   199,   207,   199,   208,   199,
     209,   199,   210,   199,   211,   199,   212,   199,   213,   199,
     214,   214,   214,   214,   214,   214,   214,   215,   217,   216,
     218,   219,   219,   220,   220,   222,   221,   223,   223,   224,
     224,   226,   225,   227,   227,   228,   228,   229,   231,   230,
     232,   232,   233,   235,   234,   237,   236,   238,   238,   239,
     239,   239,   239,   239,   239,   239,   239,   239,   239,   239,
     239,   239,   239,   239,   239,   239,   239,   239,   239,   239,
     239,   239,   239,   239,   239,   239,   239,   239,   239,   239,
     239,   239,   239,   239,   239,   239,   239,   239,   239,   239,
     239,   239,   239,   239,   239,   239,   239,   239,   239,   239,
     239,   239,   241,   240,   242,   243,   244,   245,   246,   247,
     248,   249,   250,   251,   252,   253,   254,   255,   256,   258,
     257,   259,   259,   259,   259,   259,   261,   260,   263,   262,
     265,   264,   267,   266,   268,   269,   270,   272,   271,   274,
     273,   276,   275,   277,   277,   278,   278,   278,   278,   278,
     280,   279,   281,   283,   282,   285,   284,   287,   286,   288,
     288,   289,   289,   291,   290,   292,   292,   293,   293,   293,
     293,   293,   293,   293,   293,   293,   293,   293,   293,   293,
     293,   293,   293,   293,   293,   293,   293,   293,   295,   294,
     296,   296,   296,   296,   298,   297,   300,   299,   302,   301,
     303,   305,   304,   306,   307,   308,   309,   310,   311,   312,
     313,   314,   316,   315,   317,   319,   318,   321,   320,   323,
     322,   325,   324,   326,   326,   327,   329,   328,   331,   330,
     332,   332,   333,   333,   334,   335,   337,   336,   338,   338,
     339,   339,   339,   340,   341,   343,   342,   345,   344,   346,
     346,   347,   347,   347,   347,   347,   347,   348,   349,   350,
     352,   351,   353,   353,   354,   354,   356,   355,   358,   357,
     359,   359,   359,   360,   360,   362,   361,   364,   363,   366,
     365,   367,   367,   368,   368,   368,   368,   368,   368,   369,
     370,   371,   372,   373,   374,   376,   375,   377,   377,   378,
     378,   380,   379,   382,   381,   383,   383,   384,   384,   384,
     384,   384,   384,   384,   384,   384,   384,   384,   384,   384,
     384,   384,   384,   384,   384,   384,   384,   384,   384,   384,
     384,   384,   384,   384,   384,   384,   384,   384,   384,   384,
     384,   384,   384,   386,   385,   388,   387,   390,   389,   392,
     391,   394,   393,   396,   395,   397,   397,   397,   397,   398,
     399,   401,   400,   402,   402,   403,   403,   405,   404,   406,
     406,   407,   407,   407,   407,   407,   407,   407,   407,   407,
     407,   407,   407,   407,   407,   407,   407,   407,   407,   407,
     407,   407,   407,   407,   407,   407,   407,   407,   407,   407,
     407,   407,   407,   407,   409,   408,   411,   410,   412,   412,
     413,   413,   415,   414,   417,   416,   418,   418,   419,   419,
     420,   420,   420,   420,   420,   420,   420,   420,   420,   420,
     421,   422,   423,   425,   424,   427,   426,   429,   428,   430,
     432,   431,   433,   435,   434,   436,   436,   437,   437,   439,
     438,   441,   440,   442,   442,   443,   443,   444,   444,   444,
     444,   444,   444,   444,   444,   444,   445,   447,   446,   448,
     449,   450,   451,   453,   452,   454,   454,   455,   455,   457,
     456,   459,   458,   460,   460,   461,   461,   461,   461,   461,
     461,   461,   463,   462,   465,   464,   467,   466,   469,   468,
     470,   470,   471,   471,   473,   472,   475,   474,   476,   476,
     477,   477,   477,   477,   477,   477,   477,   477,   477,   477,
     477,   479,   478,   480,   482,   481,   483,   484,   486,   485,
     487,   487,   488,   488,   490,   489,   492,   491,   493,   493,
     494,   494,   495,   495,   495,   495,   495,   495,   495,   495,
     495,   495,   495,   497,   496,   499,   498,   501,   500,   503,
     502,   505,   504,   507,   506,   509,   508,   511,   510,   512,
     512,   514,   513,   516,   515,   517,   517,   519,   518,   520,
     520,   521,   521,   522,   522,   522,   522,   522,   522,   522,
     523,   525,   524,   526,   528,   527,   529,   529,   530,   530,
     530,   530,   530,   530,   530,   530,   530,   532,   531,   533,
     533,   533,   534,   536,   535,   537,   538,   539,   541,   540,
     542,   542,   543,   543,   543,   543,   543,   545,   544,   547,
     546,   549,   548,   550,   550,   551,   551,   551,   551,   551,
     551,   552,   554,   553,   555,   557,   556,   559,   558,   561,
     560,   562,   562,   563,   563,   563,   563,   563,   563,   563,
     563,   563,   563,   563,   563,   563,   563,   563,   563,   563,
     563,   564,   566,   565,   568,   567,   569,   571,   570,   572,
     573,   575,   574,   576,   576,   578,   577,   579,   580,   582,
     581,   584,   583,   586,   585,   588,   587,   590,   589,   592,
     591,   593,   593,   594,   594,   596,   595,   597,   599,   598,
     600,   600,   602,   601,   603,   603,   604,   604,   604,   604,
     604,   604,   604,   605,   607,   606,   609,   608,   610,   610,
     612,   611,   613,   613,   614,   614,   614,   614,   614,   616,
     615,   617,   618,   619,   621,   620
  };

  const signed char
  Dhcp6Parser::yyr2_[] =
  {
       0,     2,     0,     3,     0,     3,     0,     3,     0,     3,
       0,     3,     0,     3,     0,     3,     0,     3,     0,     3,
       0,     3,     0,     3,     0,     3,     0,     3,     0,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       1,     0,     1,     3,     5,     0,     4,     0,     1,     1,
       3,     0,     4,     0,     1,     1,     3,     2,     0,     4,
       1,     3,     1,     0,     6,     0,     4,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     0,
       4,     1,     1,     1,     1,     1,     0,     4,     0,     4,
       0,     4,     0,     4,     3,     3,     3,     0,     4,     0,
       6,     0,     4,     1,     3,     1,     1,     1,     1,     1,
       0,     4,     3,     0,     6,     0,     6,     0,     6,     0,
       1,     1,     3,     0,     4,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       1,     1,     1,     1,     0,     4,     0,     4,     0,     4,
       3,     0,     4,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     0,     4,     3,     0,     4,     0,     4,     0,
       4,     0,     6,     1,     3,     1,     0,     4,     0,     6,
       1,     3,     1,     1,     1,     1,     0,     6,     1,     3,
       1,     1,     1,     1,     1,     0,     6,     0,     6,     1,
       3,     1,     1,     1,     1,     1,     1,     3,     3,     3,
       0,     6,     0,     1,     1,     3,     0,     4,     0,     4,
       1,     3,     1,     1,     1,     0,     4,     0,     4,     0,
       6,     1,     3,     1,     1,     1,     1,     1,     1,     3,
       3,     3,     3,     3,     3,     0,     6,     0,     1,     1,
       3,     0,     4,     0,     4,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     1,     1,     1,     1,     3,
       3,     0,     6,     0,     1,     1,     3,     0,     4,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     6,     0,     4,     0,     1,
       1,     3,     0,     4,     0,     4,     0,     1,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     1,     0,     4,     0,     4,     0,     4,     1,
       0,     4,     3,     0,     6,     0,     1,     1,     3,     0,
       4,     0,     4,     0,     1,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     1,
       1,     3,     3,     0,     6,     0,     1,     1,     3,     0,
       4,     0,     4,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     0,     4,     0,     4,     0,     6,
       0,     1,     1,     3,     0,     4,     0,     4,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     3,     0,     4,     3,     3,     0,     6,
       0,     1,     1,     3,     0,     4,     0,     4,     0,     1,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     6,     1,
       1,     0,     4,     0,     6,     1,     3,     0,     4,     0,
       1,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     3,     0,     6,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     1,
       1,     1,     3,     0,     4,     3,     3,     3,     0,     6,
       1,     3,     1,     1,     1,     1,     1,     0,     4,     0,
       4,     0,     6,     1,     3,     1,     1,     1,     1,     1,
       1,     3,     0,     4,     3,     0,     4,     0,     6,     0,
       4,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     3,     0,     4,     0,     4,     3,     0,     4,     3,
       3,     0,     4,     1,     1,     0,     4,     3,     3,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     6,     0,
       4,     1,     3,     1,     1,     0,     6,     3,     0,     6,
       1,     3,     0,     4,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     3,     0,     4,     0,     6,     1,     3,
       0,     4,     1,     3,     1,     1,     1,     1,     1,     0,
       4,     3,     3,     3,     0,     4
  };


#if PARSER6_DEBUG || 1
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a YYNTOKENS, nonterminals.
  const char*
  const Dhcp6Parser::yytname_[] =
  {
  "\"end of file\"", "error", "\"invalid token\"", "\",\"", "\":\"",
  "\"[\"", "\"]\"", "\"{\"", "\"}\"", "\"null\"", "\"Dhcp6\"",
  "\"data-directory\"", "\"config-control\"", "\"config-databases\"",
  "\"config-fetch-wait-time\"", "\"interfaces-config\"", "\"interfaces\"",
  "\"re-detect\"", "\"lease-database\"", "\"hosts-database\"",
  "\"hosts-databases\"", "\"type\"", "\"memfile\"", "\"mysql\"",
  "\"postgresql\"", "\"cql\"", "\"user\"", "\"password\"", "\"host\"",
  "\"port\"", "\"persist\"", "\"lfc-interval\"", "\"readonly\"",
  "\"connect-timeout\"", "\"contact-points\"", "\"max-reconnect-tries\"",
  "\"reconnect-wait-time\"", "\"keyspace\"", "\"consistency\"",
  "\"serial-consistency\"", "\"request-timeout\"", "\"tcp-keepalive\"",
  "\"tcp-nodelay\"", "\"max-row-errors\"", "\"preferred-lifetime\"",
  "\"min-preferred-lifetime\"", "\"max-preferred-lifetime\"",
  "\"valid-lifetime\"", "\"min-valid-lifetime\"", "\"max-valid-lifetime\"",
  "\"renew-timer\"", "\"rebind-timer\"", "\"calculate-tee-times\"",
  "\"t1-percent\"", "\"t2-percent\"", "\"decline-probation-period\"",
  "\"server-tag\"", "\"statistic-default-sample-count\"",
  "\"statistic-default-sample-age\"", "\"ddns-send-updates\"",
  "\"ddns-override-no-update\"", "\"ddns-override-client-update\"",
  "\"ddns-replace-client-name\"", "\"ddns-generated-prefix\"",
  "\"ddns-qualifying-suffix\"", "\"store-extended-info\"", "\"subnet6\"",
  "\"option-def\"", "\"option-data\"", "\"name\"", "\"data\"", "\"code\"",
  "\"space\"", "\"csv-format\"", "\"always-send\"", "\"record-types\"",
  "\"encapsulate\"", "\"array\"", "\"pools\"", "\"pool\"", "\"pd-pools\"",
  "\"prefix\"", "\"prefix-len\"", "\"excluded-prefix\"",
  "\"excluded-prefix-len\"", "\"delegated-len\"", "\"user-context\"",
  "\"comment\"", "\"subnet\"", "\"interface\"", "\"interface-id\"",
  "\"id\"", "\"rapid-commit\"", "\"reservation-mode\"", "\"disabled\"",
  "\"out-of-pool\"", "\"global\"", "\"all\"", "\"shared-networks\"",
  "\"mac-sources\"", "\"relay-supplied-options\"",
  "\"host-reservation-identifiers\"", "\"sanity-checks\"",
  "\"lease-checks\"", "\"client-classes\"", "\"require-client-classes\"",
  "\"test\"", "\"only-if-required\"", "\"client-class\"",
  "\"reservations\"", "\"ip-addresses\"", "\"prefixes\"", "\"duid\"",
  "\"hw-address\"", "\"hostname\"", "\"flex-id\"", "\"relay\"",
  "\"ip-address\"", "\"hooks-libraries\"", "\"library\"", "\"parameters\"",
  "\"expired-leases-processing\"", "\"reclaim-timer-wait-time\"",
  "\"flush-reclaimed-timer-wait-time\"", "\"hold-reclaimed-time\"",
  "\"max-reclaim-leases\"", "\"max-reclaim-time\"",
  "\"unwarned-reclaim-cycles\"", "\"server-id\"", "\"LLT\"", "\"EN\"",
  "\"LL\"", "\"identifier\"", "\"htype\"", "\"time\"", "\"enterprise-id\"",
  "\"dhcp4o6-port\"", "\"multi-threading\"", "\"enable-multi-threading\"",
  "\"thread-pool-size\"", "\"packet-queue-size\"", "\"control-socket\"",
  "\"socket-type\"", "\"socket-name\"", "\"dhcp-queue-control\"",
  "\"enable-queue\"", "\"queue-type\"", "\"capacity\"", "\"dhcp-ddns\"",
  "\"enable-updates\"", "\"qualifying-suffix\"", "\"server-ip\"",
  "\"server-port\"", "\"sender-ip\"", "\"sender-port\"",
  "\"max-queue-size\"", "\"ncr-protocol\"", "\"ncr-format\"",
  "\"override-no-update\"", "\"override-client-update\"",
  "\"replace-client-name\"", "\"generated-prefix\"", "\"UDP\"", "\"TCP\"",
  "\"JSON\"", "\"when-present\"", "\"never\"", "\"always\"",
  "\"when-not-present\"", "\"hostname-char-set\"",
  "\"hostname-char-replacement\"", "\"loggers\"", "\"output_options\"",
  "\"output\"", "\"debuglevel\"", "\"severity\"", "\"flush\"",
  "\"maxsize\"", "\"maxver\"", "\"pattern\"", "TOPLEVEL_JSON",
  "TOPLEVEL_DHCP6", "SUB_DHCP6", "SUB_INTERFACES6", "SUB_SUBNET6",
  "SUB_POOL6", "SUB_PD_POOL", "SUB_RESERVATION", "SUB_OPTION_DEFS",
  "SUB_OPTION_DEF", "SUB_OPTION_DATA", "SUB_HOOKS_LIBRARY",
  "SUB_DHCP_DDNS", "SUB_CONFIG_CONTROL", "\"constant string\"",
  "\"integer\"", "\"floating point\"", "\"boolean\"", "$accept", "start",
  "$@1", "$@2", "$@3", "$@4", "$@5", "$@6", "$@7", "$@8", "$@9", "$@10",
  "$@11", "$@12", "$@13", "$@14", "value", "sub_json", "map2", "$@15",
  "map_value", "map_content", "not_empty_map", "list_generic", "$@16",
  "list_content", "not_empty_list", "list_strings", "$@17",
  "list_strings_content", "not_empty_list_strings", "unknown_map_entry",
  "syntax_map", "$@18", "global_objects", "global_object", "dhcp6_object",
  "$@19", "sub_dhcp6", "$@20", "global_params", "global_param",
  "data_directory", "$@21", "preferred_lifetime", "min_preferred_lifetime",
  "max_preferred_lifetime", "valid_lifetime", "min_valid_lifetime",
  "max_valid_lifetime", "renew_timer", "rebind_timer",
  "calculate_tee_times", "t1_percent", "t2_percent",
  "decline_probation_period", "ddns_send_updates",
  "ddns_override_no_update", "ddns_override_client_update",
  "ddns_replace_client_name", "$@22", "ddns_replace_client_name_value",
  "ddns_generated_prefix", "$@23", "ddns_qualifying_suffix", "$@24",
  "hostname_char_set", "$@25", "hostname_char_replacement", "$@26",
  "store_extended_info", "statistic_default_sample_count",
  "statistic_default_sample_age", "server_tag", "$@27",
  "interfaces_config", "$@28", "sub_interfaces6", "$@29",
  "interfaces_config_params", "interfaces_config_param", "interfaces_list",
  "$@30", "re_detect", "lease_database", "$@31", "hosts_database", "$@32",
  "hosts_databases", "$@33", "database_list", "not_empty_database_list",
  "database", "$@34", "database_map_params", "database_map_param",
  "database_type", "$@35", "db_type", "user", "$@36", "password", "$@37",
  "host", "$@38", "port", "name", "$@39", "persist", "lfc_interval",
  "readonly", "connect_timeout", "reconnect_wait_time", "max_row_errors",
  "request_timeout", "tcp_keepalive", "tcp_nodelay", "contact_points",
  "$@40", "max_reconnect_tries", "keyspace", "$@41", "consistency", "$@42",
  "serial_consistency", "$@43", "sanity_checks", "$@44",
  "sanity_checks_params", "sanity_checks_param", "lease_checks", "$@45",
  "mac_sources", "$@46", "mac_sources_list", "mac_sources_value",
  "duid_id", "string_id", "host_reservation_identifiers", "$@47",
  "host_reservation_identifiers_list", "host_reservation_identifier",
  "hw_address_id", "flex_id", "relay_supplied_options", "$@48",
  "dhcp_multi_threading", "$@49", "multi_threading_params",
  "multi_threading_param", "enable_multi_threading", "thread_pool_size",
  "packet_queue_size", "hooks_libraries", "$@50", "hooks_libraries_list",
  "not_empty_hooks_libraries_list", "hooks_library", "$@51",
  "sub_hooks_library", "$@52", "hooks_params", "hooks_param", "library",
  "$@53", "parameters", "$@54", "expired_leases_processing", "$@55",
  "expired_leases_params", "expired_leases_param",
  "reclaim_timer_wait_time", "flush_reclaimed_timer_wait_time",
  "hold_reclaimed_time", "max_reclaim_leases", "max_reclaim_time",
  "unwarned_reclaim_cycles", "subnet6_list", "$@56",
  "subnet6_list_content", "not_empty_subnet6_list", "subnet6", "$@57",
  "sub_subnet6", "$@58", "subnet6_params", "subnet6_param", "subnet",
  "$@59", "interface", "$@60", "interface_id", "$@61", "client_class",
  "$@62", "require_client_classes", "$@63", "reservation_mode", "$@64",
  "hr_mode", "id", "rapid_commit", "shared_networks", "$@65",
  "shared_networks_content", "shared_networks_list", "shared_network",
  "$@66", "shared_network_params", "shared_network_param",
  "option_def_list", "$@67", "sub_option_def_list", "$@68",
  "option_def_list_content", "not_empty_option_def_list",
  "option_def_entry", "$@69", "sub_option_def", "$@70",
  "option_def_params", "not_empty_option_def_params", "option_def_param",
  "option_def_name", "code", "option_def_code", "option_def_type", "$@71",
  "option_def_record_types", "$@72", "space", "$@73", "option_def_space",
  "option_def_encapsulate", "$@74", "option_def_array", "option_data_list",
  "$@75", "option_data_list_content", "not_empty_option_data_list",
  "option_data_entry", "$@76", "sub_option_data", "$@77",
  "option_data_params", "not_empty_option_data_params",
  "option_data_param", "option_data_name", "option_data_data", "$@78",
  "option_data_code", "option_data_space", "option_data_csv_format",
  "option_data_always_send", "pools_list", "$@79", "pools_list_content",
  "not_empty_pools_list", "pool_list_entry", "$@80", "sub_pool6", "$@81",
  "pool_params", "pool_param", "pool_entry", "$@82", "user_context",
  "$@83", "comment", "$@84", "pd_pools_list", "$@85",
  "pd_pools_list_content", "not_empty_pd_pools_list", "pd_pool_entry",
  "$@86", "sub_pd_pool", "$@87", "pd_pool_params", "pd_pool_param",
  "pd_prefix", "$@88", "pd_prefix_len", "excluded_prefix", "$@89",
  "excluded_prefix_len", "pd_delegated_len", "reservations", "$@90",
  "reservations_list", "not_empty_reservations_list", "reservation",
  "$@91", "sub_reservation", "$@92", "reservation_params",
  "not_empty_reservation_params", "reservation_param", "ip_addresses",
  "$@93", "prefixes", "$@94", "duid", "$@95", "hw_address", "$@96",
  "hostname", "$@97", "flex_id_value", "$@98",
  "reservation_client_classes", "$@99", "relay", "$@100", "relay_map",
  "ip_address", "$@101", "client_classes", "$@102", "client_classes_list",
  "client_class_entry", "$@103", "client_class_params",
  "not_empty_client_class_params", "client_class_param",
  "client_class_name", "client_class_test", "$@104", "only_if_required",
  "server_id", "$@105", "server_id_params", "server_id_param",
  "server_id_type", "$@106", "duid_type", "htype", "identifier", "$@107",
  "time", "enterprise_id", "dhcp4o6_port", "control_socket", "$@108",
  "control_socket_params", "control_socket_param", "socket_type", "$@109",
  "socket_name", "$@110", "dhcp_queue_control", "$@111",
  "queue_control_params", "queue_control_param", "enable_queue",
  "queue_type", "$@112", "capacity", "arbitrary_map_entry", "$@113",
  "dhcp_ddns", "$@114", "sub_dhcp_ddns", "$@115", "dhcp_ddns_params",
  "dhcp_ddns_param", "enable_updates", "qualifying_suffix", "$@116",
  "server_ip", "$@117", "server_port", "sender_ip", "$@118", "sender_port",
  "max_queue_size", "ncr_protocol", "$@119", "ncr_protocol_value",
  "ncr_format", "$@120", "dep_override_no_update",
  "dep_override_client_update", "dep_replace_client_name", "$@121",
  "dep_generated_prefix", "$@122", "dep_hostname_char_set", "$@123",
  "dep_hostname_char_replacement", "$@124", "config_control", "$@125",
  "sub_config_control", "$@126", "config_control_params",
  "config_control_param", "config_databases", "$@127",
  "config_fetch_wait_time", "loggers", "$@128", "loggers_entries",
  "logger_entry", "$@129", "logger_params", "logger_param", "debuglevel",
  "severity", "$@130", "output_options_list", "$@131",
  "output_options_list_content", "output_entry", "$@132",
  "output_params_list", "output_params", "output", "$@133", "flush",
  "maxsize", "maxver", "pattern", "$@134", YY_NULLPTR
  };
#endif


#if PARSER6_DEBUG
  const short
  Dhcp6Parser::yyrline_[] =
  {
       0,   283,   283,   283,   284,   284,   285,   285,   286,   286,
     287,   287,   288,   288,   289,   289,   290,   290,   291,   291,
     292,   292,   293,   293,   294,   294,   295,   295,   296,   296,
     304,   305,   306,   307,   308,   309,   310,   313,   318,   318,
     329,   332,   333,   336,   340,   347,   347,   354,   355,   358,
     362,   369,   369,   376,   377,   380,   384,   395,   404,   404,
     419,   420,   424,   427,   427,   444,   444,   453,   454,   459,
     460,   461,   462,   463,   464,   465,   466,   467,   468,   469,
     470,   471,   472,   473,   474,   475,   476,   477,   478,   479,
     480,   481,   482,   483,   484,   485,   486,   487,   488,   489,
     490,   491,   492,   493,   494,   495,   496,   497,   498,   499,
     500,   501,   502,   503,   504,   505,   506,   507,   508,   509,
     510,   511,   514,   514,   522,   527,   532,   537,   542,   547,
     552,   557,   562,   567,   572,   577,   582,   587,   592,   597,
     597,   605,   608,   611,   614,   617,   623,   623,   631,   631,
     639,   639,   647,   647,   655,   660,   665,   670,   670,   678,
     678,   689,   689,   698,   699,   702,   703,   704,   705,   706,
     709,   709,   719,   724,   724,   736,   736,   748,   748,   758,
     759,   762,   763,   766,   766,   776,   777,   780,   781,   782,
     783,   784,   785,   786,   787,   788,   789,   790,   791,   792,
     793,   794,   795,   796,   797,   798,   799,   800,   803,   803,
     810,   811,   812,   813,   816,   816,   824,   824,   832,   832,
     840,   845,   845,   853,   858,   863,   868,   873,   878,   883,
     888,   893,   898,   898,   906,   911,   911,   919,   919,   927,
     927,   935,   935,   945,   946,   948,   950,   950,   968,   968,
     978,   979,   982,   983,   986,   991,   996,   996,  1006,  1007,
    1010,  1011,  1012,  1015,  1020,  1027,  1027,  1039,  1039,  1051,
    1052,  1055,  1056,  1057,  1058,  1059,  1060,  1063,  1068,  1073,
    1078,  1078,  1088,  1089,  1092,  1093,  1096,  1096,  1106,  1106,
    1116,  1117,  1118,  1121,  1122,  1125,  1125,  1133,  1133,  1141,
    1141,  1152,  1153,  1156,  1157,  1158,  1159,  1160,  1161,  1164,
    1169,  1174,  1179,  1184,  1189,  1197,  1197,  1210,  1211,  1214,
    1215,  1222,  1222,  1248,  1248,  1259,  1260,  1264,  1265,  1266,
    1267,  1268,  1269,  1270,  1271,  1272,  1273,  1274,  1275,  1276,
    1277,  1278,  1279,  1280,  1281,  1282,  1283,  1284,  1285,  1286,
    1287,  1288,  1289,  1290,  1291,  1292,  1293,  1294,  1295,  1296,
    1297,  1298,  1299,  1302,  1302,  1310,  1310,  1318,  1318,  1326,
    1326,  1334,  1334,  1344,  1344,  1351,  1352,  1353,  1354,  1357,
    1362,  1369,  1369,  1380,  1381,  1385,  1386,  1389,  1389,  1397,
    1398,  1401,  1402,  1403,  1404,  1405,  1406,  1407,  1408,  1409,
    1410,  1411,  1412,  1413,  1414,  1415,  1416,  1417,  1418,  1419,
    1420,  1421,  1422,  1423,  1424,  1425,  1426,  1427,  1428,  1429,
    1430,  1431,  1432,  1433,  1440,  1440,  1453,  1453,  1462,  1463,
    1466,  1467,  1472,  1472,  1487,  1487,  1501,  1502,  1505,  1506,
    1509,  1510,  1511,  1512,  1513,  1514,  1515,  1516,  1517,  1518,
    1521,  1523,  1528,  1530,  1530,  1538,  1538,  1546,  1546,  1554,
    1556,  1556,  1564,  1573,  1573,  1585,  1586,  1591,  1592,  1597,
    1597,  1609,  1609,  1621,  1622,  1627,  1628,  1633,  1634,  1635,
    1636,  1637,  1638,  1639,  1640,  1641,  1644,  1646,  1646,  1654,
    1656,  1658,  1663,  1671,  1671,  1683,  1684,  1687,  1688,  1691,
    1691,  1701,  1701,  1711,  1712,  1715,  1716,  1717,  1718,  1719,
    1720,  1721,  1724,  1724,  1732,  1732,  1757,  1757,  1787,  1787,
    1799,  1800,  1803,  1804,  1807,  1807,  1819,  1819,  1831,  1832,
    1835,  1836,  1837,  1838,  1839,  1840,  1841,  1842,  1843,  1844,
    1845,  1848,  1848,  1856,  1861,  1861,  1869,  1874,  1882,  1882,
    1892,  1893,  1896,  1897,  1900,  1900,  1909,  1909,  1918,  1919,
    1922,  1923,  1927,  1928,  1929,  1930,  1931,  1932,  1933,  1934,
    1935,  1936,  1937,  1940,  1940,  1950,  1950,  1960,  1960,  1968,
    1968,  1976,  1976,  1984,  1984,  1992,  1992,  2005,  2005,  2015,
    2016,  2019,  2019,  2030,  2030,  2040,  2041,  2044,  2044,  2054,
    2055,  2058,  2059,  2062,  2063,  2064,  2065,  2066,  2067,  2068,
    2071,  2073,  2073,  2081,  2089,  2089,  2101,  2102,  2105,  2106,
    2107,  2108,  2109,  2110,  2111,  2112,  2113,  2116,  2116,  2123,
    2124,  2125,  2128,  2133,  2133,  2141,  2146,  2153,  2160,  2160,
    2170,  2171,  2174,  2175,  2176,  2177,  2178,  2181,  2181,  2189,
    2189,  2200,  2200,  2212,  2213,  2216,  2217,  2218,  2219,  2220,
    2221,  2224,  2229,  2229,  2237,  2242,  2242,  2251,  2251,  2263,
    2263,  2273,  2274,  2277,  2278,  2279,  2280,  2281,  2282,  2283,
    2284,  2285,  2286,  2287,  2288,  2289,  2290,  2291,  2292,  2293,
    2294,  2297,  2302,  2302,  2310,  2310,  2318,  2323,  2323,  2331,
    2336,  2341,  2341,  2349,  2350,  2353,  2353,  2362,  2368,  2374,
    2374,  2382,  2382,  2391,  2391,  2400,  2400,  2411,  2411,  2422,
    2422,  2432,  2433,  2437,  2438,  2441,  2441,  2451,  2458,  2458,
    2470,  2471,  2475,  2475,  2483,  2484,  2487,  2488,  2489,  2490,
    2491,  2492,  2493,  2496,  2501,  2501,  2509,  2509,  2519,  2520,
    2523,  2523,  2531,  2532,  2535,  2536,  2537,  2538,  2539,  2542,
    2542,  2550,  2555,  2560,  2565,  2565
  };

  void
  Dhcp6Parser::yy_stack_print_ () const
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
  Dhcp6Parser::yy_reduce_print_ (int yyrule) const
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
#endif // PARSER6_DEBUG


#line 14 "dhcp6_parser.yy"
} } // isc::dhcp
#line 5582 "dhcp6_parser.cc"

#line 2573 "dhcp6_parser.yy"


void
isc::dhcp::Dhcp6Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
