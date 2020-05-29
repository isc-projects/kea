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
#define yylex   parser4_lex



#include "dhcp4_parser.h"


// Unqualified %code blocks.
#line 34 "dhcp4_parser.yy"

#include <dhcp4/parser_context.h>

#line 52 "dhcp4_parser.cc"


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
#if PARSER4_DEBUG

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

#else // !PARSER4_DEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YYUSE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !PARSER4_DEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 14 "dhcp4_parser.yy"
namespace isc { namespace dhcp {
#line 145 "dhcp4_parser.cc"

  /// Build a parser object.
  Dhcp4Parser::Dhcp4Parser (isc::dhcp::Parser4Context& ctx_yyarg)
#if PARSER4_DEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
#else
    :
#endif
      ctx (ctx_yyarg)
  {}

  Dhcp4Parser::~Dhcp4Parser ()
  {}

  Dhcp4Parser::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------------.
  | symbol kinds.  |
  `---------------*/



  // by_state.
  Dhcp4Parser::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

  Dhcp4Parser::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
  Dhcp4Parser::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
  Dhcp4Parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  Dhcp4Parser::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

  Dhcp4Parser::symbol_kind_type
  Dhcp4Parser::by_state::kind () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return symbol_kind::S_YYEMPTY;
    else
      return YY_CAST (symbol_kind_type, yystos_[+state]);
  }

  Dhcp4Parser::stack_symbol_type::stack_symbol_type ()
  {}

  Dhcp4Parser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state), YY_MOVE (that.location))
  {
    switch (that.kind ())
    {
      case 205: // value
      case 209: // map_value
      case 250: // ddns_replace_client_name_value
      case 272: // socket_type
      case 275: // outbound_interface_value
      case 297: // db_type
      case 391: // hr_mode
      case 546: // ncr_protocol_value
        value.YY_MOVE_OR_COPY< ElementPtr > (YY_MOVE (that.value));
        break;

      case 189: // "boolean"
        value.YY_MOVE_OR_COPY< bool > (YY_MOVE (that.value));
        break;

      case 188: // "floating point"
        value.YY_MOVE_OR_COPY< double > (YY_MOVE (that.value));
        break;

      case 187: // "integer"
        value.YY_MOVE_OR_COPY< int64_t > (YY_MOVE (that.value));
        break;

      case 186: // "constant string"
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

  Dhcp4Parser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s, YY_MOVE (that.location))
  {
    switch (that.kind ())
    {
      case 205: // value
      case 209: // map_value
      case 250: // ddns_replace_client_name_value
      case 272: // socket_type
      case 275: // outbound_interface_value
      case 297: // db_type
      case 391: // hr_mode
      case 546: // ncr_protocol_value
        value.move< ElementPtr > (YY_MOVE (that.value));
        break;

      case 189: // "boolean"
        value.move< bool > (YY_MOVE (that.value));
        break;

      case 188: // "floating point"
        value.move< double > (YY_MOVE (that.value));
        break;

      case 187: // "integer"
        value.move< int64_t > (YY_MOVE (that.value));
        break;

      case 186: // "constant string"
        value.move< std::string > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

    // that is emptied.
    that.kind_ = symbol_kind::S_YYEMPTY;
  }

#if YY_CPLUSPLUS < 201103L
  Dhcp4Parser::stack_symbol_type&
  Dhcp4Parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case 205: // value
      case 209: // map_value
      case 250: // ddns_replace_client_name_value
      case 272: // socket_type
      case 275: // outbound_interface_value
      case 297: // db_type
      case 391: // hr_mode
      case 546: // ncr_protocol_value
        value.copy< ElementPtr > (that.value);
        break;

      case 189: // "boolean"
        value.copy< bool > (that.value);
        break;

      case 188: // "floating point"
        value.copy< double > (that.value);
        break;

      case 187: // "integer"
        value.copy< int64_t > (that.value);
        break;

      case 186: // "constant string"
        value.copy< std::string > (that.value);
        break;

      default:
        break;
    }

    location = that.location;
    return *this;
  }

  Dhcp4Parser::stack_symbol_type&
  Dhcp4Parser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case 205: // value
      case 209: // map_value
      case 250: // ddns_replace_client_name_value
      case 272: // socket_type
      case 275: // outbound_interface_value
      case 297: // db_type
      case 391: // hr_mode
      case 546: // ncr_protocol_value
        value.move< ElementPtr > (that.value);
        break;

      case 189: // "boolean"
        value.move< bool > (that.value);
        break;

      case 188: // "floating point"
        value.move< double > (that.value);
        break;

      case 187: // "integer"
        value.move< int64_t > (that.value);
        break;

      case 186: // "constant string"
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
  Dhcp4Parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if PARSER4_DEBUG
  template <typename Base>
  void
  Dhcp4Parser::yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const
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
      case 186: // "constant string"
#line 268 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < std::string > (); }
#line 404 "dhcp4_parser.cc"
        break;

      case 187: // "integer"
#line 268 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < int64_t > (); }
#line 410 "dhcp4_parser.cc"
        break;

      case 188: // "floating point"
#line 268 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < double > (); }
#line 416 "dhcp4_parser.cc"
        break;

      case 189: // "boolean"
#line 268 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < bool > (); }
#line 422 "dhcp4_parser.cc"
        break;

      case 205: // value
#line 268 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 428 "dhcp4_parser.cc"
        break;

      case 209: // map_value
#line 268 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 434 "dhcp4_parser.cc"
        break;

      case 250: // ddns_replace_client_name_value
#line 268 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 440 "dhcp4_parser.cc"
        break;

      case 272: // socket_type
#line 268 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 446 "dhcp4_parser.cc"
        break;

      case 275: // outbound_interface_value
#line 268 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 452 "dhcp4_parser.cc"
        break;

      case 297: // db_type
#line 268 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 458 "dhcp4_parser.cc"
        break;

      case 391: // hr_mode
#line 268 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 464 "dhcp4_parser.cc"
        break;

      case 546: // ncr_protocol_value
#line 268 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 470 "dhcp4_parser.cc"
        break;

      default:
        break;
    }
        yyo << ')';
      }
  }
#endif

  void
  Dhcp4Parser::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
  Dhcp4Parser::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
  Dhcp4Parser::yypop_ (int n)
  {
    yystack_.pop (n);
  }

#if PARSER4_DEBUG
  std::ostream&
  Dhcp4Parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  Dhcp4Parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  Dhcp4Parser::debug_level_type
  Dhcp4Parser::debug_level () const
  {
    return yydebug_;
  }

  void
  Dhcp4Parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // PARSER4_DEBUG

  Dhcp4Parser::state_type
  Dhcp4Parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - YYNTOKENS] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - YYNTOKENS];
  }

  bool
  Dhcp4Parser::yy_pact_value_is_default_ (int yyvalue)
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  Dhcp4Parser::yy_table_value_is_error_ (int yyvalue)
  {
    return yyvalue == yytable_ninf_;
  }

  int
  Dhcp4Parser::operator() ()
  {
    return parse ();
  }

  int
  Dhcp4Parser::parse ()
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
      case 205: // value
      case 209: // map_value
      case 250: // ddns_replace_client_name_value
      case 272: // socket_type
      case 275: // outbound_interface_value
      case 297: // db_type
      case 391: // hr_mode
      case 546: // ncr_protocol_value
        yylhs.value.emplace< ElementPtr > ();
        break;

      case 189: // "boolean"
        yylhs.value.emplace< bool > ();
        break;

      case 188: // "floating point"
        yylhs.value.emplace< double > ();
        break;

      case 187: // "integer"
        yylhs.value.emplace< int64_t > ();
        break;

      case 186: // "constant string"
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
#line 277 "dhcp4_parser.yy"
                     { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 750 "dhcp4_parser.cc"
    break;

  case 4:
#line 278 "dhcp4_parser.yy"
                      { ctx.ctx_ = ctx.CONFIG; }
#line 756 "dhcp4_parser.cc"
    break;

  case 6:
#line 279 "dhcp4_parser.yy"
                 { ctx.ctx_ = ctx.DHCP4; }
#line 762 "dhcp4_parser.cc"
    break;

  case 8:
#line 280 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 768 "dhcp4_parser.cc"
    break;

  case 10:
#line 281 "dhcp4_parser.yy"
                   { ctx.ctx_ = ctx.SUBNET4; }
#line 774 "dhcp4_parser.cc"
    break;

  case 12:
#line 282 "dhcp4_parser.yy"
                 { ctx.ctx_ = ctx.POOLS; }
#line 780 "dhcp4_parser.cc"
    break;

  case 14:
#line 283 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.RESERVATIONS; }
#line 786 "dhcp4_parser.cc"
    break;

  case 16:
#line 284 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.DHCP4; }
#line 792 "dhcp4_parser.cc"
    break;

  case 18:
#line 285 "dhcp4_parser.yy"
                      { ctx.ctx_ = ctx.OPTION_DEF; }
#line 798 "dhcp4_parser.cc"
    break;

  case 20:
#line 286 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.OPTION_DATA; }
#line 804 "dhcp4_parser.cc"
    break;

  case 22:
#line 287 "dhcp4_parser.yy"
                         { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 810 "dhcp4_parser.cc"
    break;

  case 24:
#line 288 "dhcp4_parser.yy"
                     { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 816 "dhcp4_parser.cc"
    break;

  case 26:
#line 289 "dhcp4_parser.yy"
                          { ctx.ctx_ = ctx.CONFIG_CONTROL; }
#line 822 "dhcp4_parser.cc"
    break;

  case 28:
#line 297 "dhcp4_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 828 "dhcp4_parser.cc"
    break;

  case 29:
#line 298 "dhcp4_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location))); }
#line 834 "dhcp4_parser.cc"
    break;

  case 30:
#line 299 "dhcp4_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 840 "dhcp4_parser.cc"
    break;

  case 31:
#line 300 "dhcp4_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 846 "dhcp4_parser.cc"
    break;

  case 32:
#line 301 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 852 "dhcp4_parser.cc"
    break;

  case 33:
#line 302 "dhcp4_parser.yy"
            { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 858 "dhcp4_parser.cc"
    break;

  case 34:
#line 303 "dhcp4_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 864 "dhcp4_parser.cc"
    break;

  case 35:
#line 306 "dhcp4_parser.yy"
                {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as < ElementPtr > ());
}
#line 873 "dhcp4_parser.cc"
    break;

  case 36:
#line 311 "dhcp4_parser.yy"
                     {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 884 "dhcp4_parser.cc"
    break;

  case 37:
#line 316 "dhcp4_parser.yy"
                             {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 894 "dhcp4_parser.cc"
    break;

  case 38:
#line 322 "dhcp4_parser.yy"
                { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 900 "dhcp4_parser.cc"
    break;

  case 41:
#line 329 "dhcp4_parser.yy"
                                  {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 909 "dhcp4_parser.cc"
    break;

  case 42:
#line 333 "dhcp4_parser.yy"
                                                      {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 919 "dhcp4_parser.cc"
    break;

  case 43:
#line 340 "dhcp4_parser.yy"
                              {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 928 "dhcp4_parser.cc"
    break;

  case 44:
#line 343 "dhcp4_parser.yy"
                               {
    // list parsing complete. Put any sanity checking here
}
#line 936 "dhcp4_parser.cc"
    break;

  case 47:
#line 351 "dhcp4_parser.yy"
                      {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 945 "dhcp4_parser.cc"
    break;

  case 48:
#line 355 "dhcp4_parser.yy"
                                           {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 954 "dhcp4_parser.cc"
    break;

  case 49:
#line 362 "dhcp4_parser.yy"
                              {
    // List parsing about to start
}
#line 962 "dhcp4_parser.cc"
    break;

  case 50:
#line 364 "dhcp4_parser.yy"
                                       {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 971 "dhcp4_parser.cc"
    break;

  case 53:
#line 373 "dhcp4_parser.yy"
                               {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 980 "dhcp4_parser.cc"
    break;

  case 54:
#line 377 "dhcp4_parser.yy"
                                                            {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 989 "dhcp4_parser.cc"
    break;

  case 55:
#line 388 "dhcp4_parser.yy"
                                {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as < std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 1000 "dhcp4_parser.cc"
    break;

  case 56:
#line 397 "dhcp4_parser.yy"
                           {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1011 "dhcp4_parser.cc"
    break;

  case 57:
#line 402 "dhcp4_parser.yy"
                                {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.

    // Dhcp4 is required
    ctx.require("Dhcp4", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
}
#line 1024 "dhcp4_parser.cc"
    break;

  case 61:
#line 420 "dhcp4_parser.yy"
                    {
    // This code is executed when we're about to start parsing
    // the content of the map
    // Prevent against duplicate.
    ctx.unique("Dhcp4", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Dhcp4", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP4);
}
#line 1039 "dhcp4_parser.cc"
    break;

  case 62:
#line 429 "dhcp4_parser.yy"
                                                    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1049 "dhcp4_parser.cc"
    break;

  case 63:
#line 437 "dhcp4_parser.yy"
                          {
    // Parse the Dhcp4 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1059 "dhcp4_parser.cc"
    break;

  case 64:
#line 441 "dhcp4_parser.yy"
                               {
    // No global parameter is required
    // parsing completed
}
#line 1068 "dhcp4_parser.cc"
    break;

  case 119:
#line 506 "dhcp4_parser.yy"
                                             {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1077 "dhcp4_parser.cc"
    break;

  case 120:
#line 511 "dhcp4_parser.yy"
                                                     {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-valid-lifetime", prf);
}
#line 1086 "dhcp4_parser.cc"
    break;

  case 121:
#line 516 "dhcp4_parser.yy"
                                                     {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-valid-lifetime", prf);
}
#line 1095 "dhcp4_parser.cc"
    break;

  case 122:
#line 521 "dhcp4_parser.yy"
                                       {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1104 "dhcp4_parser.cc"
    break;

  case 123:
#line 526 "dhcp4_parser.yy"
                                         {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1113 "dhcp4_parser.cc"
    break;

  case 124:
#line 531 "dhcp4_parser.yy"
                                                       {
    ElementPtr ctt(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("calculate-tee-times", ctt);
}
#line 1122 "dhcp4_parser.cc"
    break;

  case 125:
#line 536 "dhcp4_parser.yy"
                                   {
    ElementPtr t1(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t1-percent", t1);
}
#line 1131 "dhcp4_parser.cc"
    break;

  case 126:
#line 541 "dhcp4_parser.yy"
                                   {
    ElementPtr t2(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t2-percent", t2);
}
#line 1140 "dhcp4_parser.cc"
    break;

  case 127:
#line 546 "dhcp4_parser.yy"
                                                                 {
    ElementPtr dpp(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1149 "dhcp4_parser.cc"
    break;

  case 128:
#line 551 "dhcp4_parser.yy"
                       {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1157 "dhcp4_parser.cc"
    break;

  case 129:
#line 553 "dhcp4_parser.yy"
               {
    ElementPtr stag(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-tag", stag);
    ctx.leave();
}
#line 1167 "dhcp4_parser.cc"
    break;

  case 130:
#line 559 "dhcp4_parser.yy"
                                             {
    ElementPtr echo(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("echo-client-id", echo);
}
#line 1176 "dhcp4_parser.cc"
    break;

  case 131:
#line 564 "dhcp4_parser.yy"
                                               {
    ElementPtr match(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("match-client-id", match);
}
#line 1185 "dhcp4_parser.cc"
    break;

  case 132:
#line 569 "dhcp4_parser.yy"
                                           {
    ElementPtr prf(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("authoritative", prf);
}
#line 1194 "dhcp4_parser.cc"
    break;

  case 133:
#line 574 "dhcp4_parser.yy"
                                                   {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-send-updates", b);
}
#line 1203 "dhcp4_parser.cc"
    break;

  case 134:
#line 579 "dhcp4_parser.yy"
                                                               {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-no-update", b);
}
#line 1212 "dhcp4_parser.cc"
    break;

  case 135:
#line 584 "dhcp4_parser.yy"
                                                                       {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-client-update", b);
}
#line 1221 "dhcp4_parser.cc"
    break;

  case 136:
#line 589 "dhcp4_parser.yy"
                                                   {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 1229 "dhcp4_parser.cc"
    break;

  case 137:
#line 591 "dhcp4_parser.yy"
                                       {
    ctx.stack_.back()->set("ddns-replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1238 "dhcp4_parser.cc"
    break;

  case 138:
#line 597 "dhcp4_parser.yy"
                 {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1246 "dhcp4_parser.cc"
    break;

  case 139:
#line 600 "dhcp4_parser.yy"
          {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 1254 "dhcp4_parser.cc"
    break;

  case 140:
#line 603 "dhcp4_parser.yy"
           {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 1262 "dhcp4_parser.cc"
    break;

  case 141:
#line 606 "dhcp4_parser.yy"
                     {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1270 "dhcp4_parser.cc"
    break;

  case 142:
#line 609 "dhcp4_parser.yy"
            {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 1279 "dhcp4_parser.cc"
    break;

  case 143:
#line 615 "dhcp4_parser.yy"
                                             {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1287 "dhcp4_parser.cc"
    break;

  case 144:
#line 617 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-generated-prefix", s);
    ctx.leave();
}
#line 1297 "dhcp4_parser.cc"
    break;

  case 145:
#line 623 "dhcp4_parser.yy"
                                               {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1305 "dhcp4_parser.cc"
    break;

  case 146:
#line 625 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-qualifying-suffix", s);
    ctx.leave();
}
#line 1315 "dhcp4_parser.cc"
    break;

  case 147:
#line 631 "dhcp4_parser.yy"
                                     {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1323 "dhcp4_parser.cc"
    break;

  case 148:
#line 633 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 1333 "dhcp4_parser.cc"
    break;

  case 149:
#line 639 "dhcp4_parser.yy"
                                                     {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1341 "dhcp4_parser.cc"
    break;

  case 150:
#line 641 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 1351 "dhcp4_parser.cc"
    break;

  case 151:
#line 647 "dhcp4_parser.yy"
                                                       {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("store-extended-info", b);
}
#line 1360 "dhcp4_parser.cc"
    break;

  case 152:
#line 652 "dhcp4_parser.yy"
                                                                             {
    ElementPtr count(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-count", count);
}
#line 1369 "dhcp4_parser.cc"
    break;

  case 153:
#line 657 "dhcp4_parser.yy"
                                                                         {
    ElementPtr age(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-age", age);
}
#line 1378 "dhcp4_parser.cc"
    break;

  case 154:
#line 662 "dhcp4_parser.yy"
                                     {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1389 "dhcp4_parser.cc"
    break;

  case 155:
#line 667 "dhcp4_parser.yy"
                                                               {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1399 "dhcp4_parser.cc"
    break;

  case 165:
#line 686 "dhcp4_parser.yy"
                                {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1409 "dhcp4_parser.cc"
    break;

  case 166:
#line 690 "dhcp4_parser.yy"
                                          {
    // No interfaces config param is required
    // parsing completed
}
#line 1418 "dhcp4_parser.cc"
    break;

  case 167:
#line 695 "dhcp4_parser.yy"
                            {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1429 "dhcp4_parser.cc"
    break;

  case 168:
#line 700 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1438 "dhcp4_parser.cc"
    break;

  case 169:
#line 705 "dhcp4_parser.yy"
                                   {
    ctx.enter(ctx.DHCP_SOCKET_TYPE);
}
#line 1446 "dhcp4_parser.cc"
    break;

  case 170:
#line 707 "dhcp4_parser.yy"
                    {
    ctx.stack_.back()->set("dhcp-socket-type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1455 "dhcp4_parser.cc"
    break;

  case 171:
#line 712 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("raw", ctx.loc2pos(yystack_[0].location))); }
#line 1461 "dhcp4_parser.cc"
    break;

  case 172:
#line 713 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("udp", ctx.loc2pos(yystack_[0].location))); }
#line 1467 "dhcp4_parser.cc"
    break;

  case 173:
#line 716 "dhcp4_parser.yy"
                                       {
    ctx.enter(ctx.OUTBOUND_INTERFACE);
}
#line 1475 "dhcp4_parser.cc"
    break;

  case 174:
#line 718 "dhcp4_parser.yy"
                                 {
    ctx.stack_.back()->set("outbound-interface", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1484 "dhcp4_parser.cc"
    break;

  case 175:
#line 723 "dhcp4_parser.yy"
                                          {
    yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("same-as-inbound", ctx.loc2pos(yystack_[0].location)));
}
#line 1492 "dhcp4_parser.cc"
    break;

  case 176:
#line 725 "dhcp4_parser.yy"
                {
    yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("use-routing", ctx.loc2pos(yystack_[0].location)));
    }
#line 1500 "dhcp4_parser.cc"
    break;

  case 177:
#line 729 "dhcp4_parser.yy"
                                   {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1509 "dhcp4_parser.cc"
    break;

  case 178:
#line 735 "dhcp4_parser.yy"
                               {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1520 "dhcp4_parser.cc"
    break;

  case 179:
#line 740 "dhcp4_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1531 "dhcp4_parser.cc"
    break;

  case 180:
#line 747 "dhcp4_parser.yy"
                             {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sanity-checks", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SANITY_CHECKS);
}
#line 1542 "dhcp4_parser.cc"
    break;

  case 181:
#line 752 "dhcp4_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1551 "dhcp4_parser.cc"
    break;

  case 185:
#line 762 "dhcp4_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1559 "dhcp4_parser.cc"
    break;

  case 186:
#line 764 "dhcp4_parser.yy"
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
#line 1579 "dhcp4_parser.cc"
    break;

  case 187:
#line 780 "dhcp4_parser.yy"
                               {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1590 "dhcp4_parser.cc"
    break;

  case 188:
#line 785 "dhcp4_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1601 "dhcp4_parser.cc"
    break;

  case 189:
#line 792 "dhcp4_parser.yy"
                                 {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1612 "dhcp4_parser.cc"
    break;

  case 190:
#line 797 "dhcp4_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1621 "dhcp4_parser.cc"
    break;

  case 195:
#line 810 "dhcp4_parser.yy"
                         {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1631 "dhcp4_parser.cc"
    break;

  case 196:
#line 814 "dhcp4_parser.yy"
                                     {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1641 "dhcp4_parser.cc"
    break;

  case 220:
#line 847 "dhcp4_parser.yy"
                    {
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1649 "dhcp4_parser.cc"
    break;

  case 221:
#line 849 "dhcp4_parser.yy"
                {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1658 "dhcp4_parser.cc"
    break;

  case 222:
#line 854 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1664 "dhcp4_parser.cc"
    break;

  case 223:
#line 855 "dhcp4_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1670 "dhcp4_parser.cc"
    break;

  case 224:
#line 856 "dhcp4_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1676 "dhcp4_parser.cc"
    break;

  case 225:
#line 857 "dhcp4_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1682 "dhcp4_parser.cc"
    break;

  case 226:
#line 860 "dhcp4_parser.yy"
           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1690 "dhcp4_parser.cc"
    break;

  case 227:
#line 862 "dhcp4_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1700 "dhcp4_parser.cc"
    break;

  case 228:
#line 868 "dhcp4_parser.yy"
                   {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1708 "dhcp4_parser.cc"
    break;

  case 229:
#line 870 "dhcp4_parser.yy"
               {
    ElementPtr pwd(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1718 "dhcp4_parser.cc"
    break;

  case 230:
#line 876 "dhcp4_parser.yy"
           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1726 "dhcp4_parser.cc"
    break;

  case 231:
#line 878 "dhcp4_parser.yy"
               {
    ElementPtr h(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1736 "dhcp4_parser.cc"
    break;

  case 232:
#line 884 "dhcp4_parser.yy"
                         {
    ElementPtr p(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1745 "dhcp4_parser.cc"
    break;

  case 233:
#line 889 "dhcp4_parser.yy"
           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1753 "dhcp4_parser.cc"
    break;

  case 234:
#line 891 "dhcp4_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1763 "dhcp4_parser.cc"
    break;

  case 235:
#line 897 "dhcp4_parser.yy"
                               {
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1772 "dhcp4_parser.cc"
    break;

  case 236:
#line 902 "dhcp4_parser.yy"
                                         {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1781 "dhcp4_parser.cc"
    break;

  case 237:
#line 907 "dhcp4_parser.yy"
                                 {
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1790 "dhcp4_parser.cc"
    break;

  case 238:
#line 912 "dhcp4_parser.yy"
                                               {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1799 "dhcp4_parser.cc"
    break;

  case 239:
#line 917 "dhcp4_parser.yy"
                                               {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("request-timeout", n);
}
#line 1808 "dhcp4_parser.cc"
    break;

  case 240:
#line 922 "dhcp4_parser.yy"
                                           {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-keepalive", n);
}
#line 1817 "dhcp4_parser.cc"
    break;

  case 241:
#line 927 "dhcp4_parser.yy"
                                       {
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-nodelay", n);
}
#line 1826 "dhcp4_parser.cc"
    break;

  case 242:
#line 932 "dhcp4_parser.yy"
                               {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1834 "dhcp4_parser.cc"
    break;

  case 243:
#line 934 "dhcp4_parser.yy"
               {
    ElementPtr cp(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1844 "dhcp4_parser.cc"
    break;

  case 244:
#line 940 "dhcp4_parser.yy"
                   {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1852 "dhcp4_parser.cc"
    break;

  case 245:
#line 942 "dhcp4_parser.yy"
               {
    ElementPtr ks(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 1862 "dhcp4_parser.cc"
    break;

  case 246:
#line 948 "dhcp4_parser.yy"
                         {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1870 "dhcp4_parser.cc"
    break;

  case 247:
#line 950 "dhcp4_parser.yy"
               {
    ElementPtr c(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("consistency", c);
    ctx.leave();
}
#line 1880 "dhcp4_parser.cc"
    break;

  case 248:
#line 956 "dhcp4_parser.yy"
                                       {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1888 "dhcp4_parser.cc"
    break;

  case 249:
#line 958 "dhcp4_parser.yy"
               {
    ElementPtr c(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("serial-consistency", c);
    ctx.leave();
}
#line 1898 "dhcp4_parser.cc"
    break;

  case 250:
#line 964 "dhcp4_parser.yy"
                                                       {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 1907 "dhcp4_parser.cc"
    break;

  case 251:
#line 969 "dhcp4_parser.yy"
                                                       {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 1916 "dhcp4_parser.cc"
    break;

  case 252:
#line 974 "dhcp4_parser.yy"
                                             {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-row-errors", n);
}
#line 1925 "dhcp4_parser.cc"
    break;

  case 253:
#line 980 "dhcp4_parser.yy"
                                                           {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1936 "dhcp4_parser.cc"
    break;

  case 254:
#line 985 "dhcp4_parser.yy"
                                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1945 "dhcp4_parser.cc"
    break;

  case 262:
#line 1001 "dhcp4_parser.yy"
               {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1954 "dhcp4_parser.cc"
    break;

  case 263:
#line 1006 "dhcp4_parser.yy"
                           {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1963 "dhcp4_parser.cc"
    break;

  case 264:
#line 1011 "dhcp4_parser.yy"
                        {
    ElementPtr circuit(new StringElement("circuit-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(circuit);
}
#line 1972 "dhcp4_parser.cc"
    break;

  case 265:
#line 1016 "dhcp4_parser.yy"
                      {
    ElementPtr client(new StringElement("client-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(client);
}
#line 1981 "dhcp4_parser.cc"
    break;

  case 266:
#line 1021 "dhcp4_parser.yy"
                 {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 1990 "dhcp4_parser.cc"
    break;

  case 267:
#line 1028 "dhcp4_parser.yy"
                                           {
    ElementPtr mt(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("multi-threading", mt);
    ctx.stack_.push_back(mt);
    ctx.enter(ctx.DHCP_MULTI_THREADING);
}
#line 2001 "dhcp4_parser.cc"
    break;

  case 268:
#line 1033 "dhcp4_parser.yy"
                                                             {
    // The enable parameter is required.
    ctx.require("enable-multi-threading", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2012 "dhcp4_parser.cc"
    break;

  case 277:
#line 1052 "dhcp4_parser.yy"
                                                             {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-multi-threading", b);
}
#line 2021 "dhcp4_parser.cc"
    break;

  case 278:
#line 1057 "dhcp4_parser.yy"
                                                 {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("thread-pool-size", prf);
}
#line 2030 "dhcp4_parser.cc"
    break;

  case 279:
#line 1062 "dhcp4_parser.yy"
                                                   {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("packet-queue-size", prf);
}
#line 2039 "dhcp4_parser.cc"
    break;

  case 280:
#line 1067 "dhcp4_parser.yy"
                                 {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 2050 "dhcp4_parser.cc"
    break;

  case 281:
#line 1072 "dhcp4_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2059 "dhcp4_parser.cc"
    break;

  case 286:
#line 1085 "dhcp4_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2069 "dhcp4_parser.cc"
    break;

  case 287:
#line 1089 "dhcp4_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2079 "dhcp4_parser.cc"
    break;

  case 288:
#line 1095 "dhcp4_parser.yy"
                                  {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2089 "dhcp4_parser.cc"
    break;

  case 289:
#line 1099 "dhcp4_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2099 "dhcp4_parser.cc"
    break;

  case 295:
#line 1114 "dhcp4_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2107 "dhcp4_parser.cc"
    break;

  case 296:
#line 1116 "dhcp4_parser.yy"
               {
    ElementPtr lib(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 2117 "dhcp4_parser.cc"
    break;

  case 297:
#line 1122 "dhcp4_parser.yy"
                       {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2125 "dhcp4_parser.cc"
    break;

  case 298:
#line 1124 "dhcp4_parser.yy"
              {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2134 "dhcp4_parser.cc"
    break;

  case 299:
#line 1130 "dhcp4_parser.yy"
                                                     {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 2145 "dhcp4_parser.cc"
    break;

  case 300:
#line 1135 "dhcp4_parser.yy"
                                                            {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2155 "dhcp4_parser.cc"
    break;

  case 309:
#line 1153 "dhcp4_parser.yy"
                                                               {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 2164 "dhcp4_parser.cc"
    break;

  case 310:
#line 1158 "dhcp4_parser.yy"
                                                                               {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 2173 "dhcp4_parser.cc"
    break;

  case 311:
#line 1163 "dhcp4_parser.yy"
                                                       {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 2182 "dhcp4_parser.cc"
    break;

  case 312:
#line 1168 "dhcp4_parser.yy"
                                                     {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 2191 "dhcp4_parser.cc"
    break;

  case 313:
#line 1173 "dhcp4_parser.yy"
                                                 {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 2200 "dhcp4_parser.cc"
    break;

  case 314:
#line 1178 "dhcp4_parser.yy"
                                                               {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 2209 "dhcp4_parser.cc"
    break;

  case 315:
#line 1186 "dhcp4_parser.yy"
                      {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet4", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET4);
}
#line 2220 "dhcp4_parser.cc"
    break;

  case 316:
#line 1191 "dhcp4_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2229 "dhcp4_parser.cc"
    break;

  case 321:
#line 1211 "dhcp4_parser.yy"
                        {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2239 "dhcp4_parser.cc"
    break;

  case 322:
#line 1215 "dhcp4_parser.yy"
                                {
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
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2265 "dhcp4_parser.cc"
    break;

  case 323:
#line 1237 "dhcp4_parser.yy"
                            {
    // Parse the subnet4 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2275 "dhcp4_parser.cc"
    break;

  case 324:
#line 1241 "dhcp4_parser.yy"
                                {
    // The subnet subnet4 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2285 "dhcp4_parser.cc"
    break;

  case 365:
#line 1293 "dhcp4_parser.yy"
               {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2293 "dhcp4_parser.cc"
    break;

  case 366:
#line 1295 "dhcp4_parser.yy"
               {
    ElementPtr subnet(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 2303 "dhcp4_parser.cc"
    break;

  case 367:
#line 1301 "dhcp4_parser.yy"
                                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2311 "dhcp4_parser.cc"
    break;

  case 368:
#line 1303 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface", iface);
    ctx.leave();
}
#line 2321 "dhcp4_parser.cc"
    break;

  case 369:
#line 1309 "dhcp4_parser.yy"
                                                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2329 "dhcp4_parser.cc"
    break;

  case 370:
#line 1311 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface-id", iface);
    ctx.leave();
}
#line 2339 "dhcp4_parser.cc"
    break;

  case 371:
#line 1317 "dhcp4_parser.yy"
                                     {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2347 "dhcp4_parser.cc"
    break;

  case 372:
#line 1319 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-subnet", iface);
    ctx.leave();
}
#line 2357 "dhcp4_parser.cc"
    break;

  case 373:
#line 1325 "dhcp4_parser.yy"
                     {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2365 "dhcp4_parser.cc"
    break;

  case 374:
#line 1327 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 2375 "dhcp4_parser.cc"
    break;

  case 375:
#line 1333 "dhcp4_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2383 "dhcp4_parser.cc"
    break;

  case 376:
#line 1335 "dhcp4_parser.yy"
               {
    ElementPtr cls(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 2393 "dhcp4_parser.cc"
    break;

  case 377:
#line 1341 "dhcp4_parser.yy"
                                               {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2404 "dhcp4_parser.cc"
    break;

  case 378:
#line 1346 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2413 "dhcp4_parser.cc"
    break;

  case 379:
#line 1351 "dhcp4_parser.yy"
                                   {
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 2421 "dhcp4_parser.cc"
    break;

  case 380:
#line 1353 "dhcp4_parser.yy"
                {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2430 "dhcp4_parser.cc"
    break;

  case 381:
#line 1358 "dhcp4_parser.yy"
                  { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 2436 "dhcp4_parser.cc"
    break;

  case 382:
#line 1359 "dhcp4_parser.yy"
                     { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 2442 "dhcp4_parser.cc"
    break;

  case 383:
#line 1360 "dhcp4_parser.yy"
                { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("global", ctx.loc2pos(yystack_[0].location))); }
#line 2448 "dhcp4_parser.cc"
    break;

  case 384:
#line 1361 "dhcp4_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 2454 "dhcp4_parser.cc"
    break;

  case 385:
#line 1364 "dhcp4_parser.yy"
                     {
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 2463 "dhcp4_parser.cc"
    break;

  case 386:
#line 1371 "dhcp4_parser.yy"
                                 {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 2474 "dhcp4_parser.cc"
    break;

  case 387:
#line 1376 "dhcp4_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2483 "dhcp4_parser.cc"
    break;

  case 392:
#line 1391 "dhcp4_parser.yy"
                               {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2493 "dhcp4_parser.cc"
    break;

  case 393:
#line 1395 "dhcp4_parser.yy"
                                       {
    ctx.stack_.pop_back();
}
#line 2501 "dhcp4_parser.cc"
    break;

  case 429:
#line 1442 "dhcp4_parser.yy"
                            {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 2512 "dhcp4_parser.cc"
    break;

  case 430:
#line 1447 "dhcp4_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2521 "dhcp4_parser.cc"
    break;

  case 431:
#line 1455 "dhcp4_parser.yy"
                                    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2530 "dhcp4_parser.cc"
    break;

  case 432:
#line 1458 "dhcp4_parser.yy"
                                 {
    // parsing completed
}
#line 2538 "dhcp4_parser.cc"
    break;

  case 437:
#line 1474 "dhcp4_parser.yy"
                                 {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2548 "dhcp4_parser.cc"
    break;

  case 438:
#line 1478 "dhcp4_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2560 "dhcp4_parser.cc"
    break;

  case 439:
#line 1489 "dhcp4_parser.yy"
                               {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2570 "dhcp4_parser.cc"
    break;

  case 440:
#line 1493 "dhcp4_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2582 "dhcp4_parser.cc"
    break;

  case 456:
#line 1525 "dhcp4_parser.yy"
                         {
    ElementPtr code(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 2591 "dhcp4_parser.cc"
    break;

  case 458:
#line 1532 "dhcp4_parser.yy"
                      {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2599 "dhcp4_parser.cc"
    break;

  case 459:
#line 1534 "dhcp4_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 2609 "dhcp4_parser.cc"
    break;

  case 460:
#line 1540 "dhcp4_parser.yy"
                                      {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2617 "dhcp4_parser.cc"
    break;

  case 461:
#line 1542 "dhcp4_parser.yy"
               {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 2627 "dhcp4_parser.cc"
    break;

  case 462:
#line 1548 "dhcp4_parser.yy"
             {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2635 "dhcp4_parser.cc"
    break;

  case 463:
#line 1550 "dhcp4_parser.yy"
               {
    ElementPtr space(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 2645 "dhcp4_parser.cc"
    break;

  case 465:
#line 1558 "dhcp4_parser.yy"
                                    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2653 "dhcp4_parser.cc"
    break;

  case 466:
#line 1560 "dhcp4_parser.yy"
               {
    ElementPtr encap(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 2663 "dhcp4_parser.cc"
    break;

  case 467:
#line 1566 "dhcp4_parser.yy"
                                      {
    ElementPtr array(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 2672 "dhcp4_parser.cc"
    break;

  case 468:
#line 1575 "dhcp4_parser.yy"
                              {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 2683 "dhcp4_parser.cc"
    break;

  case 469:
#line 1580 "dhcp4_parser.yy"
                                                                 {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2692 "dhcp4_parser.cc"
    break;

  case 474:
#line 1599 "dhcp4_parser.yy"
                                  {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2702 "dhcp4_parser.cc"
    break;

  case 475:
#line 1603 "dhcp4_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 2711 "dhcp4_parser.cc"
    break;

  case 476:
#line 1611 "dhcp4_parser.yy"
                                {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2721 "dhcp4_parser.cc"
    break;

  case 477:
#line 1615 "dhcp4_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 2730 "dhcp4_parser.cc"
    break;

  case 492:
#line 1648 "dhcp4_parser.yy"
                       {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2738 "dhcp4_parser.cc"
    break;

  case 493:
#line 1650 "dhcp4_parser.yy"
               {
    ElementPtr data(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2748 "dhcp4_parser.cc"
    break;

  case 496:
#line 1660 "dhcp4_parser.yy"
                                                 {
    ElementPtr space(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2757 "dhcp4_parser.cc"
    break;

  case 497:
#line 1665 "dhcp4_parser.yy"
                                                   {
    ElementPtr persist(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 2766 "dhcp4_parser.cc"
    break;

  case 498:
#line 1673 "dhcp4_parser.yy"
                  {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2777 "dhcp4_parser.cc"
    break;

  case 499:
#line 1678 "dhcp4_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2786 "dhcp4_parser.cc"
    break;

  case 504:
#line 1693 "dhcp4_parser.yy"
                                {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2796 "dhcp4_parser.cc"
    break;

  case 505:
#line 1697 "dhcp4_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2806 "dhcp4_parser.cc"
    break;

  case 506:
#line 1703 "dhcp4_parser.yy"
                          {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2816 "dhcp4_parser.cc"
    break;

  case 507:
#line 1707 "dhcp4_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2826 "dhcp4_parser.cc"
    break;

  case 517:
#line 1726 "dhcp4_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2834 "dhcp4_parser.cc"
    break;

  case 518:
#line 1728 "dhcp4_parser.yy"
               {
    ElementPtr pool(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2844 "dhcp4_parser.cc"
    break;

  case 519:
#line 1734 "dhcp4_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2852 "dhcp4_parser.cc"
    break;

  case 520:
#line 1736 "dhcp4_parser.yy"
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
#line 2879 "dhcp4_parser.cc"
    break;

  case 521:
#line 1759 "dhcp4_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2887 "dhcp4_parser.cc"
    break;

  case 522:
#line 1761 "dhcp4_parser.yy"
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
#line 2916 "dhcp4_parser.cc"
    break;

  case 523:
#line 1789 "dhcp4_parser.yy"
                           {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 2927 "dhcp4_parser.cc"
    break;

  case 524:
#line 1794 "dhcp4_parser.yy"
                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2936 "dhcp4_parser.cc"
    break;

  case 529:
#line 1807 "dhcp4_parser.yy"
                            {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2946 "dhcp4_parser.cc"
    break;

  case 530:
#line 1811 "dhcp4_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 2955 "dhcp4_parser.cc"
    break;

  case 531:
#line 1816 "dhcp4_parser.yy"
                                {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2965 "dhcp4_parser.cc"
    break;

  case 532:
#line 1820 "dhcp4_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 2974 "dhcp4_parser.cc"
    break;

  case 552:
#line 1851 "dhcp4_parser.yy"
                         {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2982 "dhcp4_parser.cc"
    break;

  case 553:
#line 1853 "dhcp4_parser.yy"
               {
    ElementPtr next_server(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("next-server", next_server);
    ctx.leave();
}
#line 2992 "dhcp4_parser.cc"
    break;

  case 554:
#line 1859 "dhcp4_parser.yy"
                                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3000 "dhcp4_parser.cc"
    break;

  case 555:
#line 1861 "dhcp4_parser.yy"
               {
    ElementPtr srv(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-hostname", srv);
    ctx.leave();
}
#line 3010 "dhcp4_parser.cc"
    break;

  case 556:
#line 1867 "dhcp4_parser.yy"
                               {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3018 "dhcp4_parser.cc"
    break;

  case 557:
#line 1869 "dhcp4_parser.yy"
               {
    ElementPtr bootfile(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("boot-file-name", bootfile);
    ctx.leave();
}
#line 3028 "dhcp4_parser.cc"
    break;

  case 558:
#line 1875 "dhcp4_parser.yy"
                       {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3036 "dhcp4_parser.cc"
    break;

  case 559:
#line 1877 "dhcp4_parser.yy"
               {
    ElementPtr addr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 3046 "dhcp4_parser.cc"
    break;

  case 560:
#line 1883 "dhcp4_parser.yy"
                           {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3057 "dhcp4_parser.cc"
    break;

  case 561:
#line 1888 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3066 "dhcp4_parser.cc"
    break;

  case 562:
#line 1893 "dhcp4_parser.yy"
           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3074 "dhcp4_parser.cc"
    break;

  case 563:
#line 1895 "dhcp4_parser.yy"
               {
    ElementPtr d(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 3084 "dhcp4_parser.cc"
    break;

  case 564:
#line 1901 "dhcp4_parser.yy"
                       {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3092 "dhcp4_parser.cc"
    break;

  case 565:
#line 1903 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 3102 "dhcp4_parser.cc"
    break;

  case 566:
#line 1909 "dhcp4_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3110 "dhcp4_parser.cc"
    break;

  case 567:
#line 1911 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-id", hw);
    ctx.leave();
}
#line 3120 "dhcp4_parser.cc"
    break;

  case 568:
#line 1917 "dhcp4_parser.yy"
                             {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3128 "dhcp4_parser.cc"
    break;

  case 569:
#line 1919 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("circuit-id", hw);
    ctx.leave();
}
#line 3138 "dhcp4_parser.cc"
    break;

  case 570:
#line 1925 "dhcp4_parser.yy"
                       {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3146 "dhcp4_parser.cc"
    break;

  case 571:
#line 1927 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 3156 "dhcp4_parser.cc"
    break;

  case 572:
#line 1933 "dhcp4_parser.yy"
                   {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3164 "dhcp4_parser.cc"
    break;

  case 573:
#line 1935 "dhcp4_parser.yy"
               {
    ElementPtr host(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 3174 "dhcp4_parser.cc"
    break;

  case 574:
#line 1941 "dhcp4_parser.yy"
                                           {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3185 "dhcp4_parser.cc"
    break;

  case 575:
#line 1946 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3194 "dhcp4_parser.cc"
    break;

  case 576:
#line 1954 "dhcp4_parser.yy"
             {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 3205 "dhcp4_parser.cc"
    break;

  case 577:
#line 1959 "dhcp4_parser.yy"
                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3214 "dhcp4_parser.cc"
    break;

  case 580:
#line 1971 "dhcp4_parser.yy"
                               {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 3225 "dhcp4_parser.cc"
    break;

  case 581:
#line 1976 "dhcp4_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3234 "dhcp4_parser.cc"
    break;

  case 584:
#line 1985 "dhcp4_parser.yy"
                                   {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3244 "dhcp4_parser.cc"
    break;

  case 585:
#line 1989 "dhcp4_parser.yy"
                                     {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3254 "dhcp4_parser.cc"
    break;

  case 602:
#line 2018 "dhcp4_parser.yy"
                        {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3262 "dhcp4_parser.cc"
    break;

  case 603:
#line 2020 "dhcp4_parser.yy"
               {
    ElementPtr test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 3272 "dhcp4_parser.cc"
    break;

  case 604:
#line 2026 "dhcp4_parser.yy"
                                                 {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 3281 "dhcp4_parser.cc"
    break;

  case 605:
#line 2033 "dhcp4_parser.yy"
                                         {
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 3290 "dhcp4_parser.cc"
    break;

  case 606:
#line 2040 "dhcp4_parser.yy"
                               {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 3301 "dhcp4_parser.cc"
    break;

  case 607:
#line 2045 "dhcp4_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3310 "dhcp4_parser.cc"
    break;

  case 615:
#line 2061 "dhcp4_parser.yy"
                                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3318 "dhcp4_parser.cc"
    break;

  case 616:
#line 2063 "dhcp4_parser.yy"
               {
    ElementPtr stype(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 3328 "dhcp4_parser.cc"
    break;

  case 617:
#line 2069 "dhcp4_parser.yy"
                                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3336 "dhcp4_parser.cc"
    break;

  case 618:
#line 2071 "dhcp4_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 3346 "dhcp4_parser.cc"
    break;

  case 619:
#line 2080 "dhcp4_parser.yy"
                                       {
    ElementPtr qc(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-queue-control", qc);
    ctx.stack_.push_back(qc);
    ctx.enter(ctx.DHCP_QUEUE_CONTROL);
}
#line 3357 "dhcp4_parser.cc"
    break;

  case 620:
#line 2085 "dhcp4_parser.yy"
                                                           {
    // The enable queue parameter is required.
    ctx.require("enable-queue", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3368 "dhcp4_parser.cc"
    break;

  case 629:
#line 2104 "dhcp4_parser.yy"
                                         {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-queue", b);
}
#line 3377 "dhcp4_parser.cc"
    break;

  case 630:
#line 2109 "dhcp4_parser.yy"
                       {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3385 "dhcp4_parser.cc"
    break;

  case 631:
#line 2111 "dhcp4_parser.yy"
               {
    ElementPtr qt(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("queue-type", qt);
    ctx.leave();
}
#line 3395 "dhcp4_parser.cc"
    break;

  case 632:
#line 2117 "dhcp4_parser.yy"
                                 {
    ElementPtr c(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("capacity", c);
}
#line 3404 "dhcp4_parser.cc"
    break;

  case 633:
#line 2122 "dhcp4_parser.yy"
                            {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3412 "dhcp4_parser.cc"
    break;

  case 634:
#line 2124 "dhcp4_parser.yy"
              {
    ctx.stack_.back()->set(yystack_[3].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3421 "dhcp4_parser.cc"
    break;

  case 635:
#line 2131 "dhcp4_parser.yy"
                     {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 3432 "dhcp4_parser.cc"
    break;

  case 636:
#line 2136 "dhcp4_parser.yy"
                                                       {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3443 "dhcp4_parser.cc"
    break;

  case 637:
#line 2143 "dhcp4_parser.yy"
                              {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3453 "dhcp4_parser.cc"
    break;

  case 638:
#line 2147 "dhcp4_parser.yy"
                                  {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3463 "dhcp4_parser.cc"
    break;

  case 659:
#line 2177 "dhcp4_parser.yy"
                                             {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 3472 "dhcp4_parser.cc"
    break;

  case 660:
#line 2182 "dhcp4_parser.yy"
                     {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3480 "dhcp4_parser.cc"
    break;

  case 661:
#line 2184 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 3490 "dhcp4_parser.cc"
    break;

  case 662:
#line 2190 "dhcp4_parser.yy"
                                       {
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 3499 "dhcp4_parser.cc"
    break;

  case 663:
#line 2195 "dhcp4_parser.yy"
                     {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3507 "dhcp4_parser.cc"
    break;

  case 664:
#line 2197 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 3517 "dhcp4_parser.cc"
    break;

  case 665:
#line 2203 "dhcp4_parser.yy"
                                       {
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 3526 "dhcp4_parser.cc"
    break;

  case 666:
#line 2208 "dhcp4_parser.yy"
                                             {
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 3535 "dhcp4_parser.cc"
    break;

  case 667:
#line 2213 "dhcp4_parser.yy"
                           {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 3543 "dhcp4_parser.cc"
    break;

  case 668:
#line 2215 "dhcp4_parser.yy"
                           {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3552 "dhcp4_parser.cc"
    break;

  case 669:
#line 2221 "dhcp4_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 3558 "dhcp4_parser.cc"
    break;

  case 670:
#line 2222 "dhcp4_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 3564 "dhcp4_parser.cc"
    break;

  case 671:
#line 2225 "dhcp4_parser.yy"
                       {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 3572 "dhcp4_parser.cc"
    break;

  case 672:
#line 2227 "dhcp4_parser.yy"
             {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 3582 "dhcp4_parser.cc"
    break;

  case 673:
#line 2234 "dhcp4_parser.yy"
                                         {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3590 "dhcp4_parser.cc"
    break;

  case 674:
#line 2236 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 3600 "dhcp4_parser.cc"
    break;

  case 675:
#line 2243 "dhcp4_parser.yy"
                                                         {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 3609 "dhcp4_parser.cc"
    break;

  case 676:
#line 2249 "dhcp4_parser.yy"
                                                                 {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 3618 "dhcp4_parser.cc"
    break;

  case 677:
#line 2255 "dhcp4_parser.yy"
                                             {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 3626 "dhcp4_parser.cc"
    break;

  case 678:
#line 2257 "dhcp4_parser.yy"
                                       {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3635 "dhcp4_parser.cc"
    break;

  case 679:
#line 2263 "dhcp4_parser.yy"
                                       {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3643 "dhcp4_parser.cc"
    break;

  case 680:
#line 2265 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 3653 "dhcp4_parser.cc"
    break;

  case 681:
#line 2272 "dhcp4_parser.yy"
                                         {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3661 "dhcp4_parser.cc"
    break;

  case 682:
#line 2274 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 3671 "dhcp4_parser.cc"
    break;

  case 683:
#line 2281 "dhcp4_parser.yy"
                                                         {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3679 "dhcp4_parser.cc"
    break;

  case 684:
#line 2283 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 3689 "dhcp4_parser.cc"
    break;

  case 685:
#line 2292 "dhcp4_parser.yy"
                               {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 3700 "dhcp4_parser.cc"
    break;

  case 686:
#line 2297 "dhcp4_parser.yy"
                                                            {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3710 "dhcp4_parser.cc"
    break;

  case 687:
#line 2303 "dhcp4_parser.yy"
                                   {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3720 "dhcp4_parser.cc"
    break;

  case 688:
#line 2307 "dhcp4_parser.yy"
                                       {
    // No config_control params are required
    // parsing completed
}
#line 3729 "dhcp4_parser.cc"
    break;

  case 693:
#line 2322 "dhcp4_parser.yy"
                                   {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 3740 "dhcp4_parser.cc"
    break;

  case 694:
#line 2327 "dhcp4_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3749 "dhcp4_parser.cc"
    break;

  case 695:
#line 2332 "dhcp4_parser.yy"
                                                             {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-fetch-wait-time", value);
}
#line 3758 "dhcp4_parser.cc"
    break;

  case 696:
#line 2339 "dhcp4_parser.yy"
                 {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 3769 "dhcp4_parser.cc"
    break;

  case 697:
#line 2344 "dhcp4_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3778 "dhcp4_parser.cc"
    break;

  case 700:
#line 2356 "dhcp4_parser.yy"
                             {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 3788 "dhcp4_parser.cc"
    break;

  case 701:
#line 2360 "dhcp4_parser.yy"
                               {
    ctx.stack_.pop_back();
}
#line 3796 "dhcp4_parser.cc"
    break;

  case 711:
#line 2377 "dhcp4_parser.yy"
                                     {
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 3805 "dhcp4_parser.cc"
    break;

  case 712:
#line 2382 "dhcp4_parser.yy"
                   {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3813 "dhcp4_parser.cc"
    break;

  case 713:
#line 2384 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 3823 "dhcp4_parser.cc"
    break;

  case 714:
#line 2390 "dhcp4_parser.yy"
                                    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 3834 "dhcp4_parser.cc"
    break;

  case 715:
#line 2395 "dhcp4_parser.yy"
                                                                    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3843 "dhcp4_parser.cc"
    break;

  case 718:
#line 2404 "dhcp4_parser.yy"
                             {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3853 "dhcp4_parser.cc"
    break;

  case 719:
#line 2408 "dhcp4_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 3861 "dhcp4_parser.cc"
    break;

  case 727:
#line 2423 "dhcp4_parser.yy"
               {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3869 "dhcp4_parser.cc"
    break;

  case 728:
#line 2425 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 3879 "dhcp4_parser.cc"
    break;

  case 729:
#line 2431 "dhcp4_parser.yy"
                           {
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 3888 "dhcp4_parser.cc"
    break;

  case 730:
#line 2436 "dhcp4_parser.yy"
                               {
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 3897 "dhcp4_parser.cc"
    break;

  case 731:
#line 2441 "dhcp4_parser.yy"
                             {
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 3906 "dhcp4_parser.cc"
    break;

  case 732:
#line 2446 "dhcp4_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3914 "dhcp4_parser.cc"
    break;

  case 733:
#line 2448 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pattern", sev);
    ctx.leave();
}
#line 3924 "dhcp4_parser.cc"
    break;


#line 3928 "dhcp4_parser.cc"

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
  Dhcp4Parser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what ());
  }

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  Dhcp4Parser::yytnamerr_ (const char *yystr)
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
  Dhcp4Parser::symbol_name (symbol_kind_type yysymbol)
  {
    return yytnamerr_ (yytname_[yysymbol]);
  }



  // Dhcp4Parser::context.
  Dhcp4Parser::context::context (const Dhcp4Parser& yyparser, const symbol_type& yyla)
    : yyparser_ (yyparser)
    , yyla_ (yyla)
  {}

  int
  Dhcp4Parser::context::expected_tokens (symbol_kind_type yyarg[], int yyargn) const
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
  Dhcp4Parser::yy_syntax_error_arguments_ (const context& yyctx,
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
  Dhcp4Parser::yysyntax_error_ (const context& yyctx) const
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


  const short Dhcp4Parser::yypact_ninf_ = -895;

  const signed char Dhcp4Parser::yytable_ninf_ = -1;

  const short
  Dhcp4Parser::yypact_[] =
  {
     374,  -895,  -895,  -895,  -895,  -895,  -895,  -895,  -895,  -895,
    -895,  -895,  -895,  -895,    39,    41,    72,   101,   111,   131,
     133,   157,   159,   166,   169,   173,   176,   189,  -895,  -895,
    -895,  -895,  -895,  -895,  -895,  -895,  -895,  -895,  -895,  -895,
    -895,  -895,  -895,  -895,  -895,  -895,  -895,  -895,  -895,  -895,
    -895,  -895,  -895,  -895,  -895,  -895,  -895,  -895,  -895,  -895,
    -895,  -895,  -895,  -895,    41,  -139,    71,   174,    67,   572,
      84,   229,   -29,   269,    65,   -79,   383,    18,  -895,   151,
     167,    83,   190,   212,  -895,    58,  -895,  -895,  -895,  -895,
    -895,   214,   248,   258,  -895,  -895,  -895,  -895,  -895,  -895,
     259,   260,   267,   268,   276,   277,   279,   294,   295,  -895,
     296,   307,   311,   325,   331,  -895,  -895,  -895,   335,  -895,
    -895,  -895,  -895,  -895,  -895,  -895,  -895,  -895,  -895,  -895,
    -895,   342,  -895,  -895,  -895,  -895,  -895,  -895,  -895,   344,
    -895,    82,  -895,  -895,  -895,  -895,  -895,  -895,  -895,  -895,
    -895,  -895,  -895,  -895,  -895,  -895,  -895,  -895,  -895,  -895,
    -895,  -895,  -895,  -895,  -895,  -895,  -895,  -895,  -895,  -895,
    -895,  -895,  -895,  -895,  -895,  -895,  -895,  -895,  -895,  -895,
    -895,  -895,  -895,  -895,  -895,  -895,  -895,  -895,  -895,  -895,
    -895,  -895,  -895,  -895,  -895,  -895,  -895,   345,  -895,    89,
    -895,  -895,  -895,  -895,  -895,  -895,  -895,  -895,  -895,  -895,
    -895,  -895,  -895,   367,  -895,  -895,  -895,  -895,  -895,  -895,
    -895,  -895,  -895,  -895,  -895,  -895,  -895,  -895,  -895,  -895,
    -895,  -895,  -895,  -895,  -895,  -895,  -895,    97,  -895,  -895,
    -895,  -895,  -895,  -895,  -895,  -895,  -895,  -895,  -895,  -895,
    -895,  -895,  -895,  -895,  -895,  -895,  -895,  -895,  -895,  -895,
    -895,  -895,   138,  -895,  -895,  -895,  -895,  -895,  -895,  -895,
    -895,  -895,  -895,  -895,  -895,  -895,  -895,  -895,  -895,   310,
     349,  -895,  -895,  -895,  -895,  -895,  -895,  -895,  -895,  -895,
    -895,  -895,  -895,   364,  -895,  -895,   371,  -895,  -895,  -895,
     384,  -895,  -895,   379,   386,  -895,  -895,  -895,  -895,  -895,
    -895,  -895,  -895,  -895,  -895,  -895,  -895,  -895,   387,   388,
    -895,  -895,  -895,  -895,   382,   390,  -895,  -895,  -895,  -895,
    -895,  -895,  -895,  -895,  -895,  -895,  -895,  -895,   150,  -895,
    -895,  -895,   391,  -895,  -895,   392,  -895,   396,   397,  -895,
    -895,   398,   399,  -895,  -895,  -895,  -895,  -895,  -895,  -895,
     164,  -895,  -895,  -895,  -895,  -895,  -895,  -895,  -895,  -895,
    -895,  -895,  -895,  -895,  -895,  -895,  -895,  -895,   400,   181,
    -895,  -895,  -895,  -895,    41,    41,  -895,   219,   403,    71,
    -895,   405,   407,   408,   225,   227,   228,   415,   421,   424,
     426,   427,   428,   254,   255,   257,   262,   264,   246,   270,
     275,   265,   441,   280,   282,   281,   284,   287,   442,   443,
     452,   292,   453,   461,   462,   467,   480,   481,   484,   485,
     488,   490,   491,   492,   313,   493,   498,   499,   503,   506,
     507,   508,  -895,   174,  -895,   510,   511,   512,   328,    67,
    -895,   514,   515,   516,   517,   518,   520,   338,   535,   536,
     537,   572,  -895,   538,    84,  -895,   539,   540,   556,   558,
     559,   560,   561,   562,  -895,   229,  -895,   563,   567,   385,
     569,   570,   571,   389,  -895,   269,   573,   394,   395,  -895,
      65,   575,   576,    73,  -895,   401,   577,   581,   402,   583,
     404,   406,   584,   588,   414,   417,   590,   591,   592,   593,
     383,  -895,   604,   422,    18,  -895,  -895,  -895,   606,   605,
    -895,   607,   608,   609,  -895,  -895,  -895,   425,   431,   432,
     612,   617,   620,  -895,  -895,  -895,  -895,  -895,  -895,  -895,
    -895,  -895,   451,  -895,  -895,  -895,  -895,  -895,  -105,   454,
     466,  -895,   622,   623,   633,   634,   641,   468,   278,   650,
     651,   652,   653,   658,  -895,   670,   672,   673,   676,   473,
     500,   679,  -895,   680,    93,   188,  -895,  -895,   501,   502,
     504,   686,   509,   513,  -895,   680,   525,   685,  -895,   526,
    -895,   680,   527,   528,   543,   544,   545,   546,   547,  -895,
     550,   551,  -895,   552,   553,   564,  -895,  -895,   565,  -895,
    -895,  -895,   568,    41,  -895,  -895,   574,   578,  -895,   579,
    -895,  -895,    15,   419,  -895,  -895,  -105,   580,   582,   585,
    -895,   688,  -895,  -895,    41,   174,    18,    67,   589,  -895,
    -895,  -895,    81,    81,   687,  -895,  -895,  -895,  -895,  -895,
    -895,  -895,  -895,  -895,   689,   690,   691,   693,  -895,  -895,
    -895,  -895,  -895,  -895,  -895,  -895,   -39,   694,   695,   716,
     163,    80,   191,   180,   383,  -895,  -895,   717,  -895,  -895,
    -895,  -895,  -895,  -895,  -895,  -895,  -895,  -895,  -895,   718,
    -895,  -895,  -895,  -895,   107,  -895,  -895,  -895,  -895,  -895,
    -895,  -895,  -895,  -895,  -895,  -895,  -895,  -895,  -895,  -895,
    -895,  -895,  -895,  -895,  -895,  -895,  -895,  -895,  -895,  -895,
    -895,  -895,  -895,   687,  -895,   183,   184,   208,  -895,   216,
    -895,  -895,  -895,  -895,  -895,  -895,   722,   738,   740,   742,
     743,  -895,  -895,  -895,  -895,   744,   745,   749,   752,   753,
     755,  -895,   253,  -895,  -895,  -895,  -895,  -895,  -895,  -895,
    -895,  -895,  -895,  -895,  -895,  -895,  -895,  -895,  -895,  -895,
    -895,  -895,  -895,  -895,   274,  -895,   756,   758,  -895,  -895,
     761,   766,  -895,  -895,   764,   769,  -895,  -895,   767,   771,
    -895,  -895,   770,   772,  -895,  -895,  -895,  -895,  -895,  -895,
      34,  -895,  -895,  -895,  -895,  -895,  -895,  -895,    46,  -895,
    -895,   773,   774,  -895,  -895,   775,   777,  -895,   778,   779,
     780,   781,   782,   783,   298,  -895,  -895,  -895,  -895,  -895,
    -895,  -895,   784,   785,   786,  -895,   299,  -895,  -895,  -895,
    -895,  -895,  -895,  -895,  -895,  -895,  -895,  -895,   305,  -895,
    -895,  -895,   787,  -895,   788,  -895,  -895,  -895,   314,  -895,
    -895,  -895,  -895,  -895,   322,  -895,    61,  -895,   610,  -895,
     789,   790,  -895,  -895,  -895,  -895,   791,   792,  -895,  -895,
    -895,   793,   589,  -895,   796,   797,   798,   799,   618,   615,
     619,   621,   624,   803,   808,   809,   810,   628,   629,   630,
     631,   632,   635,    81,  -895,  -895,    81,  -895,   687,   572,
    -895,   689,   269,  -895,   690,    65,  -895,   691,   646,  -895,
     693,   -39,  -895,    74,   694,  -895,   229,  -895,   695,   -79,
    -895,   716,   636,   637,   638,   639,   640,   642,   163,  -895,
     644,   643,   647,    80,  -895,   815,   816,   191,  -895,   648,
     824,   649,   827,   180,  -895,  -895,   128,   717,  -895,  -895,
     829,   835,    84,  -895,   718,   836,  -895,  -895,   655,  -895,
     348,   657,   660,   661,  -895,  -895,  -895,  -895,  -895,   664,
     671,   684,   696,  -895,  -895,  -895,  -895,  -895,  -895,  -895,
     323,  -895,   347,  -895,   831,  -895,   857,  -895,  -895,  -895,
    -895,  -895,  -895,  -895,  -895,  -895,  -895,  -895,  -895,  -895,
    -895,  -895,  -895,  -895,  -895,  -895,  -895,  -895,  -895,  -895,
    -895,  -895,  -895,  -895,   353,  -895,  -895,  -895,  -895,  -895,
    -895,  -895,  -895,  -895,  -895,  -895,   840,  -895,  -895,  -895,
    -895,  -895,  -895,  -895,  -895,  -895,   858,   883,  -895,  -895,
    -895,  -895,  -895,   879,  -895,   359,  -895,  -895,  -895,  -895,
    -895,  -895,  -895,  -895,  -895,  -895,  -895,  -895,   713,   714,
    -895,  -895,   720,  -895,    41,  -895,  -895,   899,  -895,  -895,
    -895,  -895,  -895,   362,  -895,  -895,  -895,  -895,  -895,  -895,
     727,   365,  -895,   680,  -895,  -895,  -895,  -895,  -895,  -895,
    -895,  -895,  -895,  -895,  -895,  -895,  -895,  -895,  -895,  -895,
    -895,   646,  -895,   910,   732,  -895,    74,  -895,  -895,  -895,
    -895,  -895,  -895,   918,   737,   955,   128,  -895,  -895,  -895,
    -895,  -895,   794,  -895,  -895,   959,  -895,   795,  -895,  -895,
     953,  -895,  -895,    90,  -895,   -27,   953,  -895,  -895,   964,
     965,   966,  -895,   366,  -895,  -895,  -895,  -895,  -895,  -895,
    -895,   967,   800,   801,   804,   968,   -27,  -895,   806,  -895,
    -895,  -895,   807,  -895,  -895,  -895
  };

  const short
  Dhcp4Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     1,    43,
      36,    32,    31,    28,    29,    30,    35,     3,    33,    34,
      56,     5,    63,     7,   165,     9,   323,    11,   506,    13,
     531,    15,   431,    17,   439,    19,   476,    21,   288,    23,
     637,    25,   687,    27,    45,    39,     0,     0,     0,     0,
       0,   533,     0,   441,   478,     0,     0,     0,    47,     0,
      46,     0,     0,    40,    61,     0,    58,    60,   685,   154,
     180,     0,     0,     0,   552,   554,   556,   178,   187,   189,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   128,
       0,     0,     0,     0,     0,   136,   143,   145,     0,   315,
     429,   468,   386,   519,   521,   379,   253,   580,   523,   280,
     299,     0,   267,   606,   619,   635,   147,   149,   696,     0,
     118,     0,    65,    67,    68,    69,    70,    71,   102,   103,
     104,    72,   100,    89,    90,    91,   108,   109,   110,   111,
     112,   113,   106,   107,   114,   115,   116,    75,    76,    97,
      77,    78,    79,   117,    83,    84,    73,   101,    74,    81,
      82,    95,    96,    98,    92,    93,    94,    80,    85,    86,
      87,    88,    99,   105,   167,   169,   173,     0,   164,     0,
     156,   158,   159,   160,   161,   162,   163,   367,   369,   371,
     498,   365,   373,     0,   377,   375,   576,   364,   327,   328,
     329,   330,   331,   352,   353,   354,   342,   343,   355,   356,
     357,   358,   359,   360,   361,   362,   363,     0,   325,   334,
     347,   348,   349,   335,   337,   338,   340,   336,   332,   333,
     350,   351,   339,   344,   345,   346,   341,   517,   516,   512,
     513,   511,     0,   508,   510,   514,   515,   574,   562,   564,
     568,   566,   572,   570,   558,   551,   545,   549,   550,     0,
     534,   535,   546,   547,   548,   542,   537,   543,   539,   540,
     541,   544,   538,     0,   458,   233,     0,   462,   460,   465,
       0,   454,   455,     0,   442,   443,   445,   457,   446,   447,
     448,   464,   449,   450,   451,   452,   453,   492,     0,     0,
     490,   491,   494,   495,     0,   479,   480,   482,   483,   484,
     485,   486,   487,   488,   489,   295,   297,   292,     0,   290,
     293,   294,     0,   673,   660,     0,   663,     0,     0,   667,
     671,     0,     0,   677,   679,   681,   683,   658,   656,   657,
       0,   639,   641,   642,   643,   644,   645,   646,   647,   648,
     653,   649,   650,   651,   652,   654,   655,   693,     0,     0,
     689,   691,   692,    44,     0,     0,    37,     0,     0,     0,
      57,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    55,     0,    64,     0,     0,     0,     0,     0,
     166,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   324,     0,     0,   507,     0,     0,     0,     0,
       0,     0,     0,     0,   532,     0,   432,     0,     0,     0,
       0,     0,     0,     0,   440,     0,     0,     0,     0,   477,
       0,     0,     0,     0,   289,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   638,     0,     0,     0,   688,    48,    41,     0,     0,
      59,     0,     0,     0,   130,   131,   132,     0,     0,     0,
       0,     0,     0,   119,   120,   121,   122,   123,   124,   125,
     126,   127,     0,   152,   153,   133,   134,   135,     0,     0,
       0,   151,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   605,     0,     0,     0,     0,     0,
       0,     0,    66,     0,     0,     0,   177,   157,     0,     0,
       0,     0,     0,     0,   385,     0,     0,     0,   326,     0,
     509,     0,     0,     0,     0,     0,     0,     0,     0,   536,
       0,     0,   456,     0,     0,     0,   467,   444,     0,   496,
     497,   481,     0,     0,   291,   659,     0,     0,   662,     0,
     665,   666,     0,     0,   675,   676,     0,     0,     0,     0,
     640,     0,   695,   690,     0,     0,     0,     0,     0,   553,
     555,   557,     0,     0,   191,   129,   138,   139,   140,   141,
     142,   137,   144,   146,   317,   433,   470,   388,    38,   520,
     522,   381,   382,   383,   384,   380,     0,     0,   525,   282,
       0,     0,     0,     0,     0,   148,   150,     0,    49,   168,
     171,   172,   170,   175,   176,   174,   368,   370,   372,   500,
     366,   374,   378,   376,     0,   518,   575,   563,   565,   569,
     567,   573,   571,   559,   459,   234,   463,   461,   466,   493,
     296,   298,   674,   661,   664,   669,   670,   668,   672,   678,
     680,   682,   684,   191,    42,     0,     0,     0,   185,     0,
     182,   184,   220,   226,   228,   230,     0,     0,     0,     0,
       0,   242,   244,   246,   248,     0,     0,     0,     0,     0,
       0,   219,     0,   197,   199,   200,   201,   202,   203,   204,
     205,   206,   207,   208,   212,   213,   214,   209,   215,   216,
     217,   210,   211,   218,     0,   195,     0,   192,   193,   321,
       0,   318,   319,   437,     0,   434,   435,   474,     0,   471,
     472,   392,     0,   389,   390,   262,   263,   264,   265,   266,
       0,   255,   257,   258,   259,   260,   261,   584,     0,   582,
     529,     0,   526,   527,   286,     0,   283,   284,     0,     0,
       0,     0,     0,     0,     0,   301,   303,   304,   305,   306,
     307,   308,     0,     0,     0,   276,     0,   269,   271,   272,
     273,   274,   275,   615,   617,   614,   612,   613,     0,   608,
     610,   611,     0,   630,     0,   633,   626,   627,     0,   621,
     623,   624,   625,   628,     0,   700,     0,   698,    51,   504,
       0,   501,   502,   560,   578,   579,     0,     0,    62,   686,
     155,     0,     0,   181,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   179,   188,     0,   190,     0,     0,
     316,     0,   441,   430,     0,   478,   469,     0,     0,   387,
       0,     0,   254,   586,     0,   581,   533,   524,     0,     0,
     281,     0,     0,     0,     0,     0,     0,     0,     0,   300,
       0,     0,     0,     0,   268,     0,     0,     0,   607,     0,
       0,     0,     0,     0,   620,   636,     0,     0,   697,    53,
       0,    52,     0,   499,     0,     0,   577,   694,     0,   183,
       0,     0,     0,     0,   232,   235,   236,   237,   238,     0,
       0,     0,     0,   250,   251,   239,   240,   241,   252,   198,
       0,   194,     0,   320,     0,   436,     0,   473,   428,   411,
     412,   413,   399,   400,   416,   417,   418,   402,   403,   419,
     420,   421,   422,   423,   424,   425,   426,   427,   396,   397,
     398,   409,   410,   408,     0,   394,   401,   414,   415,   404,
     405,   406,   407,   391,   256,   602,     0,   600,   601,   593,
     594,   598,   599,   595,   596,   597,     0,   587,   588,   590,
     591,   592,   583,     0,   528,     0,   285,   309,   310,   311,
     312,   313,   314,   302,   277,   278,   279,   270,     0,     0,
     609,   629,     0,   632,     0,   622,   714,     0,   712,   710,
     704,   708,   709,     0,   702,   706,   707,   705,   699,    50,
       0,     0,   503,     0,   186,   222,   223,   224,   225,   221,
     227,   229,   231,   243,   245,   247,   249,   196,   322,   438,
     475,     0,   393,     0,     0,   585,     0,   530,   287,   616,
     618,   631,   634,     0,     0,     0,     0,   701,    54,   505,
     561,   395,     0,   604,   589,     0,   711,     0,   703,   603,
       0,   713,   718,     0,   716,     0,     0,   715,   727,     0,
       0,     0,   732,     0,   720,   722,   723,   724,   725,   726,
     717,     0,     0,     0,     0,     0,     0,   719,     0,   729,
     730,   731,     0,   721,   728,   733
  };

  const short
  Dhcp4Parser::yypgoto_[] =
  {
    -895,  -895,  -895,  -895,  -895,  -895,  -895,  -895,  -895,  -895,
    -895,  -895,  -895,  -895,  -895,   -52,  -895,   222,  -895,  -895,
    -895,  -895,  -895,  -895,  -895,  -895,  -570,  -895,  -895,  -895,
     -67,  -895,  -895,  -895,   586,  -895,  -895,  -895,  -895,   339,
     351,   -40,   -28,   -24,    -1,     1,    11,    19,    22,  -895,
    -895,  -895,  -895,    25,    26,    29,    30,    32,    37,  -895,
     350,    40,  -895,    43,  -895,    44,  -895,    45,  -895,    47,
    -895,  -895,  -895,  -895,   336,   529,  -895,  -895,  -895,  -895,
    -895,  -895,  -895,  -895,  -895,  -895,  -895,  -895,  -895,  -895,
    -895,  -895,    95,  -895,  -895,  -895,  -895,  -895,  -895,   256,
    -895,    75,  -895,  -630,    79,  -895,  -895,  -895,  -895,  -895,
    -895,  -895,  -895,  -895,  -895,   -63,  -895,  -895,  -895,  -895,
    -895,  -895,  -895,  -895,  -895,  -895,  -895,  -895,  -895,  -895,
    -895,  -895,  -895,  -895,  -895,  -895,  -895,  -895,    63,  -895,
    -895,  -895,  -895,  -895,  -895,  -895,  -895,    42,  -895,  -895,
    -895,  -895,  -895,  -895,  -895,    55,  -895,  -895,  -895,    66,
     494,  -895,  -895,  -895,  -895,  -895,  -895,  -895,    52,  -895,
    -895,  -895,  -895,  -895,  -895,  -894,  -895,  -895,  -895,    85,
    -895,  -895,  -895,    88,   533,  -895,  -895,  -895,  -895,  -895,
    -895,  -895,  -895,  -891,  -895,   -65,  -895,    49,  -895,    48,
    -895,  -895,  -895,  -895,  -895,  -895,  -895,    78,  -895,  -895,
    -112,   -46,  -895,  -895,  -895,  -895,  -895,    86,  -895,  -895,
    -895,    91,  -895,   519,  -895,   -42,  -895,  -895,  -895,  -895,
    -895,   -36,  -895,  -895,  -895,  -895,  -895,   -35,  -895,  -895,
    -895,    92,  -895,  -895,  -895,    87,  -895,   522,  -895,  -895,
    -895,  -895,  -895,  -895,  -895,  -895,  -895,  -895,  -895,    50,
    -895,  -895,  -895,    51,   541,  -895,  -895,   -51,  -895,   -11,
    -895,   -25,  -895,  -895,  -895,    96,  -895,  -895,  -895,    94,
    -895,   531,   -55,  -895,     0,  -895,     7,  -895,   316,  -895,
    -895,  -895,  -895,  -895,  -895,  -895,  -895,  -895,  -895,  -895,
    -895,  -895,  -895,  -895,  -895,  -895,  -890,  -895,  -895,  -895,
    -895,  -895,    77,  -895,  -895,  -895,  -109,  -895,  -895,  -895,
    -895,  -895,  -895,  -895,  -895,    68,  -895,  -895,  -895,  -895,
    -895,  -895,  -895,    64,  -895,  -895,  -895,  -895,  -895,  -895,
    -895,  -895,  -895,  -895,   334,   521,  -895,  -895,  -895,  -895,
    -895,  -895,  -895,  -895,  -895,  -895,  -895,  -895,  -895,  -895,
    -895,  -895,  -895,  -895,  -895,  -895,  -895,  -895,  -895,  -895,
    -895,  -895,  -895,  -895,  -895,   380,   505,  -895,  -895,  -895,
    -895,  -895,  -895,    69,  -895,  -895,  -108,  -895,  -895,  -895,
    -895,  -895,  -895,  -125,  -895,  -895,  -143,  -895,  -895,  -895,
    -895,  -895,  -895,  -895
  };

  const short
  Dhcp4Parser::yydefgoto_[] =
  {
      -1,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    36,    37,    38,    65,   659,
      82,    83,    39,    64,    79,    80,   679,   868,   960,   961,
     751,    41,    66,    85,    86,    87,   388,    43,    67,   141,
     142,   143,   144,   145,   146,   147,   148,   149,   150,   151,
     152,   412,   153,   154,   155,   156,   157,   158,   159,   418,
     651,   160,   419,   161,   420,   162,   439,   163,   440,   164,
     165,   166,   167,   392,   199,   200,    45,    68,   201,   445,
     202,   446,   682,   203,   447,   685,   204,   168,   400,   169,
     393,   729,   730,   731,   881,   170,   401,   171,   402,   776,
     777,   778,   906,   752,   753,   754,   884,  1099,   755,   885,
     756,   886,   757,   887,   758,   759,   478,   760,   761,   762,
     763,   764,   765,   766,   767,   893,   768,   894,   769,   895,
     770,   896,   771,   772,   773,   172,   429,   800,   801,   802,
     803,   804,   805,   806,   173,   435,   836,   837,   838,   839,
     840,   174,   432,   815,   816,   817,   929,    59,    75,   338,
     339,   340,   491,   341,   492,   175,   433,   824,   825,   826,
     827,   828,   829,   830,   831,   176,   422,   780,   781,   782,
     909,    47,    69,   237,   238,   239,   455,   240,   451,   241,
     452,   242,   453,   243,   456,   244,   459,   245,   458,   177,
     428,   665,   247,   178,   425,   792,   793,   794,   918,  1024,
    1025,   179,   423,    53,    72,   784,   785,   786,   912,    55,
      73,   303,   304,   305,   306,   307,   308,   309,   477,   310,
     481,   311,   480,   312,   313,   482,   314,   180,   424,   788,
     789,   790,   915,    57,    74,   324,   325,   326,   327,   328,
     486,   329,   330,   331,   332,   249,   454,   870,   871,   872,
     962,    49,    70,   262,   263,   264,   463,   181,   426,   182,
     427,   183,   431,   811,   812,   813,   926,    51,    71,   279,
     280,   281,   184,   397,   185,   398,   186,   399,   285,   473,
     875,   965,   286,   467,   287,   468,   288,   470,   289,   469,
     290,   472,   291,   471,   292,   466,   256,   460,   876,   187,
     430,   808,   809,   923,  1046,  1047,  1048,  1049,  1050,  1113,
    1051,   188,   189,   436,   848,   849,   850,   945,   851,   946,
     190,   437,   858,   859,   860,   861,   950,   862,   863,   952,
     191,   438,    61,    76,   360,   361,   362,   363,   497,   364,
     365,   499,   366,   367,   368,   502,   717,   369,   503,   370,
     496,   371,   372,   373,   506,   374,   507,   375,   508,   376,
     509,   192,   391,    63,    77,   379,   380,   381,   512,   382,
     193,   441,   866,   867,   956,  1083,  1084,  1085,  1086,  1125,
    1087,  1123,  1143,  1144,  1145,  1153,  1154,  1155,  1161,  1156,
    1157,  1158,  1159,  1165
  };

  const short
  Dhcp4Parser::yytable_[] =
  {
     140,   198,   217,   258,   275,   259,   301,   320,   337,   357,
     302,   321,    78,   774,   253,   692,   282,   205,   250,   265,
     277,   696,   315,   333,  1019,   358,   293,  1020,  1032,   218,
     377,   378,   322,   715,   248,   261,   276,   921,   323,    28,
     922,   219,   335,   336,   252,   220,    29,    81,    30,   924,
      31,   120,   925,   646,   647,   648,   649,   206,   251,   266,
     278,   389,   316,   334,   957,   359,   390,   958,   221,   254,
     222,   283,   795,   796,   797,   798,   255,   799,   284,    40,
     223,    84,   194,   195,   650,   443,   196,   385,   224,   197,
     444,   225,   449,  1146,   226,   227,  1147,   450,   228,   229,
     461,   230,    94,    95,    96,   462,   231,   139,    42,   232,
     680,   681,   233,   234,   235,   732,   236,   246,    44,   260,
     733,   734,   735,   736,   737,   738,   739,   740,   741,   742,
     743,   744,   745,   746,   747,   748,   749,   750,    46,  1148,
      48,   464,  1149,  1150,  1151,  1152,   465,   295,   317,   296,
     297,   318,   319,   493,   120,   121,   295,   383,   494,   123,
     124,   123,   124,   295,    50,   121,    52,   510,   123,   124,
     384,   716,   511,    54,   123,   124,    56,   257,   123,   124,
      58,  1035,  1036,    60,   514,    88,   443,   514,    89,   515,
     214,   878,   879,   215,   335,   336,    62,    90,   386,    91,
      92,    93,    94,    95,    96,    97,    98,    99,   683,   684,
     295,   449,   832,   833,   834,   387,   880,  1019,   394,   882,
    1020,  1032,   123,   124,   883,   274,   873,    32,    33,    34,
      35,   100,   101,   102,   103,   104,   105,   106,   107,   108,
     109,   110,   111,   112,   113,   114,   115,   116,   117,   118,
     119,   139,   395,   139,   120,   121,   903,    94,    95,    96,
     139,   904,   396,   403,   404,   122,   139,   139,   123,   124,
     139,   405,   406,   125,   123,   124,   990,   903,   126,   127,
     407,   408,   905,   409,   128,   123,   124,   818,   819,   820,
     821,   822,   823,  1076,   129,  1077,  1078,   130,   410,   411,
     413,   938,   943,   294,   131,   132,   939,   944,   947,   133,
     121,   414,   134,   948,   139,   415,   135,   953,   474,   852,
     853,   854,   954,   123,   124,   510,   903,   843,   844,   416,
     955,  1107,   516,   517,   267,   417,   136,   137,   138,   421,
     268,   269,   270,   271,   272,   273,   434,   274,   442,   448,
     461,   295,   475,   296,   297,  1108,  1111,   298,   299,   300,
     139,  1112,   493,   123,   124,  1126,   855,  1118,   464,  1166,
    1127,   457,   476,  1129,  1167,   479,   140,   139,   661,   662,
     663,   664,   198,  1095,  1096,  1097,  1098,   484,   483,   485,
     489,   487,   488,   490,   217,   495,   498,   258,   205,   259,
     500,   501,   504,   505,   513,   518,   253,   519,   275,   521,
     250,   522,   523,   265,   524,   139,   525,   526,   301,   527,
     282,   218,   302,   320,   277,   528,   248,   321,   529,   261,
     530,   531,   532,   219,   315,   538,   252,   220,   206,   333,
     276,   533,   534,   357,   535,   542,   548,   549,   322,   536,
     251,   537,   541,   266,   323,   139,   550,   552,   539,   358,
     221,   254,   222,   540,   278,   553,   554,   543,   255,   544,
     545,   555,   223,   546,   316,   283,   547,   123,   124,   334,
     224,   551,   284,   225,   556,   557,   226,   227,   558,   559,
     228,   229,   560,   230,   561,   562,   563,   565,   231,   359,
     564,   232,   566,   567,   233,   234,   235,   568,   236,   246,
     569,   570,   571,   260,   573,   574,   575,   576,   578,   579,
     580,   581,   582,  1130,   583,   584,   342,   343,   344,   345,
     346,   347,   348,   349,   350,   351,   352,   353,   354,   585,
     586,   587,   589,   591,   592,   355,   356,     1,     2,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
     593,   711,   594,   595,   596,   597,   598,   600,   140,   139,
     198,   601,   602,   603,   604,   605,   718,   608,   606,   612,
     613,   616,   724,   609,   610,   617,   205,   619,   622,   618,
     615,   620,   623,   621,   626,   627,   628,   629,    92,    93,
      94,    95,    96,   624,   835,   845,   625,   357,   631,   632,
     634,   639,   635,   728,   636,   637,   638,   640,   641,   642,
     841,   846,   856,   358,   643,   644,   206,   654,   655,   100,
     101,   102,   103,   104,   105,   106,   107,   645,   656,   657,
     652,   112,   113,   114,   115,   116,   117,   118,    30,   207,
     208,   209,   653,   121,   660,   666,   667,   668,   669,   675,
     842,   847,   857,   359,   210,   670,   123,   124,   211,   212,
     213,   125,    92,    93,    94,    95,    96,   671,   214,   672,
     673,   215,   128,   674,   677,   678,   676,   686,   687,   216,
     688,   689,   694,   723,   775,   690,   779,   783,   787,   691,
     791,   807,   810,   100,   101,   102,   103,   104,   105,   106,
     107,   693,   695,   697,   698,   112,   113,   114,   115,   116,
     117,   118,   119,   814,   865,   869,   888,   121,   295,   699,
     700,   701,   702,   703,   136,   137,   704,   705,   706,   707,
     123,   124,   889,   212,   890,   125,   891,   892,   897,   898,
     708,   709,   214,   899,   710,   215,   900,   901,   139,   902,
     712,   908,   907,   216,   713,   714,   720,   910,   721,   911,
     913,   722,   914,   916,   917,   920,   919,   928,   658,   927,
     931,   930,   932,   933,   934,   935,   936,   937,   940,   941,
     942,   949,   951,   964,   572,   963,   959,   968,   967,   966,
     970,   971,   972,   973,   975,   974,   976,   979,   136,   137,
     977,   978,   980,   981,   982,   983,   984,   985,   986,  1068,
    1069,   987,   988,  1057,  1058,  1059,  1060,  1061,  1072,  1062,
    1065,  1074,   139,  1064,  1066,  1089,  1073,  1071,  1090,  1109,
    1093,  1094,   217,  1100,  1114,   301,  1101,  1102,   320,   302,
    1103,   998,   321,  1021,   253,  1018,  1037,  1104,   250,   275,
    1038,   315,   337,  1029,   333,  1110,  1115,  1027,  1043,   218,
    1105,   282,  1041,   322,   248,   277,   835,  1039,   999,   323,
     845,   219,  1106,  1026,   252,   220,  1116,  1117,  1040,  1079,
    1000,   276,   841,  1080,  1001,   258,   846,   259,   251,  1119,
    1120,   316,   856,  1124,   334,  1081,  1121,  1028,   221,   254,
     222,   265,  1042,  1128,  1132,   278,   255,  1002,  1030,  1003,
     223,  1133,  1135,  1044,  1136,  1031,   283,   261,   224,  1004,
    1045,   225,   842,   284,   226,   227,   847,  1005,   228,   229,
    1006,   230,   857,  1007,  1008,  1082,   231,  1009,  1010,   232,
    1011,   266,   233,   234,   235,  1012,   236,   246,  1013,  1137,
    1142,  1014,  1015,  1016,  1140,  1017,  1023,  1022,  1162,  1163,
    1164,  1168,  1172,   727,   725,   520,   719,   969,   577,   877,
    1139,  1141,   989,   991,  1034,  1067,  1056,   614,  1170,  1169,
    1063,  1171,  1174,  1175,   588,  1055,   993,   992,  1033,  1131,
     995,  1052,   996,   994,   607,   590,   599,  1134,   864,   997,
     874,   260,   611,  1091,  1092,  1070,   726,  1075,  1138,   633,
    1053,  1160,  1122,  1173,  1054,     0,  1088,     0,     0,     0,
       0,   630,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   998,     0,  1021,     0,  1018,  1037,
       0,     0,     0,  1038,     0,     0,  1029,     0,     0,  1079,
    1027,  1043,     0,  1080,     0,  1041,     0,     0,     0,     0,
    1039,   999,     0,     0,     0,  1081,  1026,     0,     0,     0,
       0,  1040,     0,  1000,     0,     0,     0,  1001,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    1028,     0,     0,     0,     0,  1042,     0,     0,     0,     0,
    1002,  1030,  1003,     0,     0,  1082,  1044,     0,  1031,     0,
       0,     0,  1004,  1045,     0,     0,     0,     0,     0,     0,
    1005,     0,     0,  1006,     0,     0,  1007,  1008,     0,     0,
    1009,  1010,     0,  1011,     0,     0,     0,     0,  1012,     0,
       0,  1013,     0,     0,  1014,  1015,  1016,     0,  1017,  1023,
    1022
  };

  const short
  Dhcp4Parser::yycheck_[] =
  {
      67,    68,    69,    70,    71,    70,    73,    74,    75,    76,
      73,    74,    64,   643,    69,   585,    71,    68,    69,    70,
      71,   591,    73,    74,   918,    76,    72,   918,   918,    69,
      12,    13,    74,    18,    69,    70,    71,     3,    74,     0,
       6,    69,   121,   122,    69,    69,     5,   186,     7,     3,
       9,    80,     6,   158,   159,   160,   161,    68,    69,    70,
      71,     3,    73,    74,     3,    76,     8,     6,    69,    69,
      69,    71,   111,   112,   113,   114,    69,   116,    71,     7,
      69,    10,    15,    16,   189,     3,    19,     4,    69,    22,
       8,    69,     3,     3,    69,    69,     6,     8,    69,    69,
       3,    69,    28,    29,    30,     8,    69,   186,     7,    69,
      17,    18,    69,    69,    69,    34,    69,    69,     7,    70,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,     7,   166,
       7,     3,   169,   170,   171,   172,     8,    82,    83,    84,
      85,    86,    87,     3,    80,    81,    82,     6,     8,    94,
      95,    94,    95,    82,     7,    81,     7,     3,    94,    95,
       3,   156,     8,     7,    94,    95,     7,    93,    94,    95,
       7,   107,   108,     7,     3,    11,     3,     3,    14,     8,
     106,     8,     8,   109,   121,   122,     7,    23,     8,    25,
      26,    27,    28,    29,    30,    31,    32,    33,    20,    21,
      82,     3,   132,   133,   134,     3,     8,  1111,     4,     3,
    1111,  1111,    94,    95,     8,   118,   119,   186,   187,   188,
     189,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,   186,     4,   186,    80,    81,     3,    28,    29,    30,
     186,     8,     4,     4,     4,    91,   186,   186,    94,    95,
     186,     4,     4,    99,    94,    95,   906,     3,   104,   105,
       4,     4,     8,     4,   110,    94,    95,   124,   125,   126,
     127,   128,   129,   165,   120,   167,   168,   123,     4,     4,
       4,     3,     3,    34,   130,   131,     8,     8,     3,   135,
      81,     4,   138,     8,   186,     4,   142,     3,     8,   139,
     140,   141,     8,    94,    95,     3,     3,   136,   137,     4,
       8,     8,   384,   385,   105,     4,   162,   163,   164,     4,
     111,   112,   113,   114,   115,   116,     4,   118,     4,     4,
       3,    82,     3,    84,    85,     8,     3,    88,    89,    90,
     186,     8,     3,    94,    95,     3,   186,     8,     3,     3,
       8,     4,     8,     8,     8,     4,   443,   186,   100,   101,
     102,   103,   449,    35,    36,    37,    38,     8,     4,     3,
       8,     4,     4,     3,   461,     4,     4,   464,   449,   464,
       4,     4,     4,     4,     4,   186,   461,     4,   475,     4,
     461,     4,     4,   464,   189,   186,   189,   189,   485,     4,
     475,   461,   485,   490,   475,     4,   461,   490,     4,   464,
       4,     4,     4,   461,   485,   189,   461,   461,   449,   490,
     475,   187,   187,   510,   187,     4,     4,     4,   490,   187,
     461,   187,   187,   464,   490,   186,     4,     4,   188,   510,
     461,   461,   461,   188,   475,     4,     4,   187,   461,   187,
     189,     4,   461,   189,   485,   475,   189,    94,    95,   490,
     461,   189,   475,   461,     4,     4,   461,   461,     4,     4,
     461,   461,     4,   461,     4,     4,     4,     4,   461,   510,
     187,   461,     4,     4,   461,   461,   461,     4,   461,   461,
       4,     4,     4,   464,     4,     4,     4,   189,     4,     4,
       4,     4,     4,  1093,     4,   187,   143,   144,   145,   146,
     147,   148,   149,   150,   151,   152,   153,   154,   155,     4,
       4,     4,     4,     4,     4,   162,   163,   173,   174,   175,
     176,   177,   178,   179,   180,   181,   182,   183,   184,   185,
       4,   613,     4,     4,     4,     4,     4,     4,   635,   186,
     637,     4,   187,     4,     4,     4,   157,     4,   189,     4,
       4,     4,   634,   189,   189,     4,   637,     4,     4,   187,
     189,   187,     4,   187,     4,     4,     4,     4,    26,    27,
      28,    29,    30,   189,   671,   672,   189,   674,     4,   187,
       4,   186,     7,    24,     7,     7,     7,   186,   186,     7,
     671,   672,   673,   674,     7,     5,   637,     5,     5,    57,
      58,    59,    60,    61,    62,    63,    64,   186,     5,     5,
     186,    69,    70,    71,    72,    73,    74,    75,     7,    77,
      78,    79,   186,    81,   186,     5,     5,     5,     5,   186,
     671,   672,   673,   674,    92,     7,    94,    95,    96,    97,
      98,    99,    26,    27,    28,    29,    30,     7,   106,     7,
       7,   109,   110,     7,     5,     5,   186,   186,   186,   117,
     186,     5,     7,     5,     7,   186,     7,     7,     7,   186,
       7,     7,     7,    57,    58,    59,    60,    61,    62,    63,
      64,   186,   186,   186,   186,    69,    70,    71,    72,    73,
      74,    75,    76,     7,     7,     7,     4,    81,    82,   186,
     186,   186,   186,   186,   162,   163,   186,   186,   186,   186,
      94,    95,     4,    97,     4,    99,     4,     4,     4,     4,
     186,   186,   106,     4,   186,   109,     4,     4,   186,     4,
     186,     3,     6,   117,   186,   186,   186,     6,   186,     3,
       6,   186,     3,     6,     3,     3,     6,     3,   556,     6,
       3,     6,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     3,   443,     6,   186,     4,     6,     8,
       4,     4,     4,     4,   189,   187,   187,     4,   162,   163,
     189,   187,     4,     4,     4,   187,   187,   187,   187,     4,
       4,   189,   187,   187,   187,   187,   187,   187,     4,   187,
     187,     4,   186,   189,   187,     6,   187,   189,     3,     8,
       4,   186,   909,   186,     4,   912,   186,   186,   915,   912,
     186,   918,   915,   918,   909,   918,   923,   186,   909,   926,
     923,   912,   929,   918,   915,     8,     8,   918,   923,   909,
     186,   926,   923,   915,   909,   926,   943,   923,   918,   915,
     947,   909,   186,   918,   909,   909,     3,     8,   923,   956,
     918,   926,   943,   956,   918,   962,   947,   962,   909,   186,
     186,   912,   953,     4,   915,   956,   186,   918,   909,   909,
     909,   962,   923,   186,     4,   926,   909,   918,   918,   918,
     909,   189,     4,   923,   187,   918,   926,   962,   909,   918,
     923,   909,   943,   926,   909,   909,   947,   918,   909,   909,
     918,   909,   953,   918,   918,   956,   909,   918,   918,   909,
     918,   962,   909,   909,   909,   918,   909,   909,   918,     4,
       7,   918,   918,   918,     5,   918,   918,   918,     4,     4,
       4,     4,     4,   637,   635,   389,   626,   882,   449,   723,
     186,   186,   903,   908,   921,   943,   931,   493,   187,   189,
     938,   187,   186,   186,   461,   929,   911,   909,   920,  1111,
     914,   924,   915,   912,   485,   464,   475,  1116,   674,   917,
     694,   962,   490,   962,   964,   947,   636,   953,  1126,   514,
     926,  1146,  1074,  1166,   928,    -1,   957,    -1,    -1,    -1,
      -1,   510,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,  1111,    -1,  1111,    -1,  1111,  1116,
      -1,    -1,    -1,  1116,    -1,    -1,  1111,    -1,    -1,  1126,
    1111,  1116,    -1,  1126,    -1,  1116,    -1,    -1,    -1,    -1,
    1116,  1111,    -1,    -1,    -1,  1126,  1111,    -1,    -1,    -1,
      -1,  1116,    -1,  1111,    -1,    -1,    -1,  1111,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    1111,    -1,    -1,    -1,    -1,  1116,    -1,    -1,    -1,    -1,
    1111,  1111,  1111,    -1,    -1,  1126,  1116,    -1,  1111,    -1,
      -1,    -1,  1111,  1116,    -1,    -1,    -1,    -1,    -1,    -1,
    1111,    -1,    -1,  1111,    -1,    -1,  1111,  1111,    -1,    -1,
    1111,  1111,    -1,  1111,    -1,    -1,    -1,    -1,  1111,    -1,
      -1,  1111,    -1,    -1,  1111,  1111,  1111,    -1,  1111,  1111,
    1111
  };

  const short
  Dhcp4Parser::yystos_[] =
  {
       0,   173,   174,   175,   176,   177,   178,   179,   180,   181,
     182,   183,   184,   185,   191,   192,   193,   194,   195,   196,
     197,   198,   199,   200,   201,   202,   203,   204,     0,     5,
       7,     9,   186,   187,   188,   189,   205,   206,   207,   212,
       7,   221,     7,   227,     7,   266,     7,   371,     7,   451,
       7,   467,     7,   403,     7,   409,     7,   433,     7,   347,
       7,   532,     7,   563,   213,   208,   222,   228,   267,   372,
     452,   468,   404,   410,   434,   348,   533,   564,   205,   214,
     215,   186,   210,   211,    10,   223,   224,   225,    11,    14,
      23,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
      80,    81,    91,    94,    95,    99,   104,   105,   110,   120,
     123,   130,   131,   135,   138,   142,   162,   163,   164,   186,
     220,   229,   230,   231,   232,   233,   234,   235,   236,   237,
     238,   239,   240,   242,   243,   244,   245,   246,   247,   248,
     251,   253,   255,   257,   259,   260,   261,   262,   277,   279,
     285,   287,   325,   334,   341,   355,   365,   389,   393,   401,
     427,   457,   459,   461,   472,   474,   476,   499,   511,   512,
     520,   530,   561,   570,    15,    16,    19,    22,   220,   264,
     265,   268,   270,   273,   276,   457,   459,    77,    78,    79,
      92,    96,    97,    98,   106,   109,   117,   220,   231,   232,
     233,   234,   235,   236,   237,   238,   243,   244,   245,   246,
     247,   248,   251,   253,   255,   257,   259,   373,   374,   375,
     377,   379,   381,   383,   385,   387,   389,   392,   427,   445,
     457,   459,   461,   472,   474,   476,   496,    93,   220,   385,
     387,   427,   453,   454,   455,   457,   459,   105,   111,   112,
     113,   114,   115,   116,   118,   220,   427,   457,   459,   469,
     470,   471,   472,   474,   476,   478,   482,   484,   486,   488,
     490,   492,   494,   401,    34,    82,    84,    85,    88,    89,
      90,   220,   305,   411,   412,   413,   414,   415,   416,   417,
     419,   421,   423,   424,   426,   457,   459,    83,    86,    87,
     220,   305,   415,   421,   435,   436,   437,   438,   439,   441,
     442,   443,   444,   457,   459,   121,   122,   220,   349,   350,
     351,   353,   143,   144,   145,   146,   147,   148,   149,   150,
     151,   152,   153,   154,   155,   162,   163,   220,   457,   459,
     534,   535,   536,   537,   539,   540,   542,   543,   544,   547,
     549,   551,   552,   553,   555,   557,   559,    12,    13,   565,
     566,   567,   569,     6,     3,     4,     8,     3,   226,     3,
       8,   562,   263,   280,     4,     4,     4,   473,   475,   477,
     278,   286,   288,     4,     4,     4,     4,     4,     4,     4,
       4,     4,   241,     4,     4,     4,     4,     4,   249,   252,
     254,     4,   366,   402,   428,   394,   458,   460,   390,   326,
     500,   462,   342,   356,     4,   335,   513,   521,   531,   256,
     258,   571,     4,     3,     8,   269,   271,   274,     4,     3,
       8,   378,   380,   382,   446,   376,   384,     4,   388,   386,
     497,     3,     8,   456,     3,     8,   495,   483,   485,   489,
     487,   493,   491,   479,     8,     3,     8,   418,   306,     4,
     422,   420,   425,     4,     8,     3,   440,     4,     4,     8,
       3,   352,   354,     3,     8,     4,   550,   538,     4,   541,
       4,     4,   545,   548,     4,     4,   554,   556,   558,   560,
       3,     8,   568,     4,     3,     8,   205,   205,   186,     4,
     224,     4,     4,     4,   189,   189,   189,     4,     4,     4,
       4,     4,     4,   187,   187,   187,   187,   187,   189,   188,
     188,   187,     4,   187,   187,   189,   189,   189,     4,     4,
       4,   189,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,   187,     4,     4,     4,     4,     4,
       4,     4,   230,     4,     4,     4,   189,   265,     4,     4,
       4,     4,     4,     4,   187,     4,     4,     4,   374,     4,
     454,     4,     4,     4,     4,     4,     4,     4,     4,   471,
       4,     4,   187,     4,     4,     4,   189,   413,     4,   189,
     189,   437,     4,     4,   350,   189,     4,     4,   187,     4,
     187,   187,     4,     4,   189,   189,     4,     4,     4,     4,
     535,     4,   187,   566,     4,     7,     7,     7,     7,   186,
     186,   186,     7,     7,     5,   186,   158,   159,   160,   161,
     189,   250,   186,   186,     5,     5,     5,     5,   207,   209,
     186,   100,   101,   102,   103,   391,     5,     5,     5,     5,
       7,     7,     7,     7,     7,   186,   186,     5,     5,   216,
      17,    18,   272,    20,    21,   275,   186,   186,   186,     5,
     186,   186,   216,   186,     7,   186,   216,   186,   186,   186,
     186,   186,   186,   186,   186,   186,   186,   186,   186,   186,
     186,   205,   186,   186,   186,    18,   156,   546,   157,   250,
     186,   186,   186,     5,   205,   229,   565,   264,    24,   281,
     282,   283,    34,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,   220,   293,   294,   295,   298,   300,   302,   304,   305,
     307,   308,   309,   310,   311,   312,   313,   314,   316,   318,
     320,   322,   323,   324,   293,     7,   289,   290,   291,     7,
     367,   368,   369,     7,   405,   406,   407,     7,   429,   430,
     431,     7,   395,   396,   397,   111,   112,   113,   114,   116,
     327,   328,   329,   330,   331,   332,   333,     7,   501,   502,
       7,   463,   464,   465,     7,   343,   344,   345,   124,   125,
     126,   127,   128,   129,   357,   358,   359,   360,   361,   362,
     363,   364,   132,   133,   134,   220,   336,   337,   338,   339,
     340,   457,   459,   136,   137,   220,   457,   459,   514,   515,
     516,   518,   139,   140,   141,   186,   457,   459,   522,   523,
     524,   525,   527,   528,   534,     7,   572,   573,   217,     7,
     447,   448,   449,   119,   478,   480,   498,   289,     8,     8,
       8,   284,     3,     8,   296,   299,   301,   303,     4,     4,
       4,     4,     4,   315,   317,   319,   321,     4,     4,     4,
       4,     4,     4,     3,     8,     8,   292,     6,     3,   370,
       6,     3,   408,     6,     3,   432,     6,     3,   398,     6,
       3,     3,     6,   503,     3,     6,   466,     6,     3,   346,
       6,     3,     4,     4,     4,     4,     4,     4,     3,     8,
       4,     4,     4,     3,     8,   517,   519,     3,     8,     4,
     526,     4,   529,     3,     8,     8,   574,     3,     6,   186,
     218,   219,   450,     6,     3,   481,     8,     6,     4,   282,
       4,     4,     4,     4,   187,   189,   187,   189,   187,     4,
       4,     4,     4,   187,   187,   187,   187,   189,   187,   294,
     293,   291,   373,   369,   411,   407,   435,   431,   220,   231,
     232,   233,   234,   235,   236,   237,   238,   243,   244,   245,
     246,   247,   248,   251,   253,   255,   257,   259,   305,   365,
     383,   385,   387,   389,   399,   400,   427,   457,   459,   472,
     474,   476,   496,   397,   328,   107,   108,   220,   305,   401,
     427,   457,   459,   472,   474,   476,   504,   505,   506,   507,
     508,   510,   502,   469,   465,   349,   345,   187,   187,   187,
     187,   187,   187,   358,   189,   187,   187,   337,     4,     4,
     515,   189,     4,   187,     4,   523,   165,   167,   168,   220,
     305,   457,   459,   575,   576,   577,   578,   580,   573,     6,
       3,   453,   449,     4,   186,    35,    36,    37,    38,   297,
     186,   186,   186,   186,   186,   186,   186,     8,     8,     8,
       8,     3,     8,   509,     4,     8,     3,     8,     8,   186,
     186,   186,   205,   581,     4,   579,     3,     8,   186,     8,
     216,   400,     4,   189,   506,     4,   187,     4,   576,   186,
       5,   186,     7,   582,   583,   584,     3,     6,   166,   169,
     170,   171,   172,   585,   586,   587,   589,   590,   591,   592,
     583,   588,     4,     4,     4,   593,     3,     8,     4,   189,
     187,   187,     4,   586,   186,   186
  };

  const short
  Dhcp4Parser::yyr1_[] =
  {
       0,   190,   192,   191,   193,   191,   194,   191,   195,   191,
     196,   191,   197,   191,   198,   191,   199,   191,   200,   191,
     201,   191,   202,   191,   203,   191,   204,   191,   205,   205,
     205,   205,   205,   205,   205,   206,   208,   207,   209,   210,
     210,   211,   211,   213,   212,   214,   214,   215,   215,   217,
     216,   218,   218,   219,   219,   220,   222,   221,   223,   223,
     224,   226,   225,   228,   227,   229,   229,   230,   230,   230,
     230,   230,   230,   230,   230,   230,   230,   230,   230,   230,
     230,   230,   230,   230,   230,   230,   230,   230,   230,   230,
     230,   230,   230,   230,   230,   230,   230,   230,   230,   230,
     230,   230,   230,   230,   230,   230,   230,   230,   230,   230,
     230,   230,   230,   230,   230,   230,   230,   230,   230,   231,
     232,   233,   234,   235,   236,   237,   238,   239,   241,   240,
     242,   243,   244,   245,   246,   247,   249,   248,   250,   250,
     250,   250,   250,   252,   251,   254,   253,   256,   255,   258,
     257,   259,   260,   261,   263,   262,   264,   264,   265,   265,
     265,   265,   265,   265,   265,   267,   266,   269,   268,   271,
     270,   272,   272,   274,   273,   275,   275,   276,   278,   277,
     280,   279,   281,   281,   282,   284,   283,   286,   285,   288,
     287,   289,   289,   290,   290,   292,   291,   293,   293,   294,
     294,   294,   294,   294,   294,   294,   294,   294,   294,   294,
     294,   294,   294,   294,   294,   294,   294,   294,   294,   294,
     296,   295,   297,   297,   297,   297,   299,   298,   301,   300,
     303,   302,   304,   306,   305,   307,   308,   309,   310,   311,
     312,   313,   315,   314,   317,   316,   319,   318,   321,   320,
     322,   323,   324,   326,   325,   327,   327,   328,   328,   328,
     328,   328,   329,   330,   331,   332,   333,   335,   334,   336,
     336,   337,   337,   337,   337,   337,   337,   338,   339,   340,
     342,   341,   343,   343,   344,   344,   346,   345,   348,   347,
     349,   349,   349,   350,   350,   352,   351,   354,   353,   356,
     355,   357,   357,   358,   358,   358,   358,   358,   358,   359,
     360,   361,   362,   363,   364,   366,   365,   367,   367,   368,
     368,   370,   369,   372,   371,   373,   373,   374,   374,   374,
     374,   374,   374,   374,   374,   374,   374,   374,   374,   374,
     374,   374,   374,   374,   374,   374,   374,   374,   374,   374,
     374,   374,   374,   374,   374,   374,   374,   374,   374,   374,
     374,   374,   374,   374,   374,   376,   375,   378,   377,   380,
     379,   382,   381,   384,   383,   386,   385,   388,   387,   390,
     389,   391,   391,   391,   391,   392,   394,   393,   395,   395,
     396,   396,   398,   397,   399,   399,   400,   400,   400,   400,
     400,   400,   400,   400,   400,   400,   400,   400,   400,   400,
     400,   400,   400,   400,   400,   400,   400,   400,   400,   400,
     400,   400,   400,   400,   400,   400,   400,   400,   400,   402,
     401,   404,   403,   405,   405,   406,   406,   408,   407,   410,
     409,   411,   411,   412,   412,   413,   413,   413,   413,   413,
     413,   413,   413,   413,   413,   414,   415,   416,   418,   417,
     420,   419,   422,   421,   423,   425,   424,   426,   428,   427,
     429,   429,   430,   430,   432,   431,   434,   433,   435,   435,
     436,   436,   437,   437,   437,   437,   437,   437,   437,   437,
     437,   438,   440,   439,   441,   442,   443,   444,   446,   445,
     447,   447,   448,   448,   450,   449,   452,   451,   453,   453,
     454,   454,   454,   454,   454,   454,   454,   456,   455,   458,
     457,   460,   459,   462,   461,   463,   463,   464,   464,   466,
     465,   468,   467,   469,   469,   470,   470,   471,   471,   471,
     471,   471,   471,   471,   471,   471,   471,   471,   471,   471,
     471,   471,   473,   472,   475,   474,   477,   476,   479,   478,
     481,   480,   483,   482,   485,   484,   487,   486,   489,   488,
     491,   490,   493,   492,   495,   494,   497,   496,   498,   498,
     500,   499,   501,   501,   503,   502,   504,   504,   505,   505,
     506,   506,   506,   506,   506,   506,   506,   506,   506,   506,
     506,   507,   509,   508,   510,   511,   513,   512,   514,   514,
     515,   515,   515,   515,   515,   517,   516,   519,   518,   521,
     520,   522,   522,   523,   523,   523,   523,   523,   523,   524,
     526,   525,   527,   529,   528,   531,   530,   533,   532,   534,
     534,   535,   535,   535,   535,   535,   535,   535,   535,   535,
     535,   535,   535,   535,   535,   535,   535,   535,   535,   536,
     538,   537,   539,   541,   540,   542,   543,   545,   544,   546,
     546,   548,   547,   550,   549,   551,   552,   554,   553,   556,
     555,   558,   557,   560,   559,   562,   561,   564,   563,   565,
     565,   566,   566,   568,   567,   569,   571,   570,   572,   572,
     574,   573,   575,   575,   576,   576,   576,   576,   576,   576,
     576,   577,   579,   578,   581,   580,   582,   582,   584,   583,
     585,   585,   586,   586,   586,   586,   586,   588,   587,   589,
     590,   591,   593,   592
  };

  const signed char
  Dhcp4Parser::yyr2_[] =
  {
       0,     2,     0,     3,     0,     3,     0,     3,     0,     3,
       0,     3,     0,     3,     0,     3,     0,     3,     0,     3,
       0,     3,     0,     3,     0,     3,     0,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     1,     0,
       1,     3,     5,     0,     4,     0,     1,     1,     3,     0,
       4,     0,     1,     1,     3,     2,     0,     4,     1,     3,
       1,     0,     6,     0,     4,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     0,     4,
       3,     3,     3,     3,     3,     3,     0,     4,     1,     1,
       1,     1,     1,     0,     4,     0,     4,     0,     4,     0,
       4,     3,     3,     3,     0,     6,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     0,     4,     0,
       4,     1,     1,     0,     4,     1,     1,     3,     0,     6,
       0,     6,     1,     3,     1,     0,     4,     0,     6,     0,
       6,     0,     1,     1,     3,     0,     4,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     1,     1,     1,     1,     0,     4,     0,     4,
       0,     4,     3,     0,     4,     3,     3,     3,     3,     3,
       3,     3,     0,     4,     0,     4,     0,     4,     0,     4,
       3,     3,     3,     0,     6,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     6,     1,
       3,     1,     1,     1,     1,     1,     1,     3,     3,     3,
       0,     6,     0,     1,     1,     3,     0,     4,     0,     4,
       1,     3,     1,     1,     1,     0,     4,     0,     4,     0,
       6,     1,     3,     1,     1,     1,     1,     1,     1,     3,
       3,     3,     3,     3,     3,     0,     6,     0,     1,     1,
       3,     0,     4,     0,     4,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     1,     1,     1,     1,     3,     0,     6,     0,     1,
       1,     3,     0,     4,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       6,     0,     4,     0,     1,     1,     3,     0,     4,     0,
       4,     0,     1,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     1,     0,     4,
       0,     4,     0,     4,     1,     0,     4,     3,     0,     6,
       0,     1,     1,     3,     0,     4,     0,     4,     0,     1,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     1,     1,     3,     3,     0,     6,
       0,     1,     1,     3,     0,     4,     0,     4,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     0,
       4,     0,     4,     0,     6,     0,     1,     1,     3,     0,
       4,     0,     4,     0,     1,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     6,     1,     1,
       0,     6,     1,     3,     0,     4,     0,     1,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     3,     3,     0,     6,     1,     3,
       1,     1,     1,     1,     1,     0,     4,     0,     4,     0,
       6,     1,     3,     1,     1,     1,     1,     1,     1,     3,
       0,     4,     3,     0,     4,     0,     6,     0,     4,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       0,     4,     3,     0,     4,     3,     3,     0,     4,     1,
       1,     0,     4,     0,     4,     3,     3,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     6,     0,     4,     1,
       3,     1,     1,     0,     6,     3,     0,     6,     1,     3,
       0,     4,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     3,     0,     4,     0,     6,     1,     3,     0,     4,
       1,     3,     1,     1,     1,     1,     1,     0,     4,     3,
       3,     3,     0,     4
  };


#if PARSER4_DEBUG || 1
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a YYNTOKENS, nonterminals.
  const char*
  const Dhcp4Parser::yytname_[] =
  {
  "\"end of file\"", "error", "\"invalid token\"", "\",\"", "\":\"",
  "\"[\"", "\"]\"", "\"{\"", "\"}\"", "\"null\"", "\"Dhcp4\"",
  "\"config-control\"", "\"config-databases\"",
  "\"config-fetch-wait-time\"", "\"interfaces-config\"", "\"interfaces\"",
  "\"dhcp-socket-type\"", "\"raw\"", "\"udp\"", "\"outbound-interface\"",
  "\"same-as-inbound\"", "\"use-routing\"", "\"re-detect\"",
  "\"sanity-checks\"", "\"lease-checks\"", "\"echo-client-id\"",
  "\"match-client-id\"", "\"authoritative\"", "\"next-server\"",
  "\"server-hostname\"", "\"boot-file-name\"", "\"lease-database\"",
  "\"hosts-database\"", "\"hosts-databases\"", "\"type\"", "\"memfile\"",
  "\"mysql\"", "\"postgresql\"", "\"cql\"", "\"user\"", "\"password\"",
  "\"host\"", "\"port\"", "\"persist\"", "\"lfc-interval\"",
  "\"readonly\"", "\"connect-timeout\"", "\"contact-points\"",
  "\"keyspace\"", "\"consistency\"", "\"serial-consistency\"",
  "\"max-reconnect-tries\"", "\"reconnect-wait-time\"",
  "\"request-timeout\"", "\"tcp-keepalive\"", "\"tcp-nodelay\"",
  "\"max-row-errors\"", "\"valid-lifetime\"", "\"min-valid-lifetime\"",
  "\"max-valid-lifetime\"", "\"renew-timer\"", "\"rebind-timer\"",
  "\"calculate-tee-times\"", "\"t1-percent\"", "\"t2-percent\"",
  "\"decline-probation-period\"", "\"server-tag\"",
  "\"statistic-default-sample-count\"", "\"statistic-default-sample-age\"",
  "\"ddns-send-updates\"", "\"ddns-override-no-update\"",
  "\"ddns-override-client-update\"", "\"ddns-replace-client-name\"",
  "\"ddns-generated-prefix\"", "\"ddns-qualifying-suffix\"",
  "\"store-extended-info\"", "\"subnet4\"", "\"4o6-interface\"",
  "\"4o6-interface-id\"", "\"4o6-subnet\"", "\"option-def\"",
  "\"option-data\"", "\"name\"", "\"data\"", "\"code\"", "\"space\"",
  "\"csv-format\"", "\"always-send\"", "\"record-types\"",
  "\"encapsulate\"", "\"array\"", "\"shared-networks\"", "\"pools\"",
  "\"pool\"", "\"user-context\"", "\"comment\"", "\"subnet\"",
  "\"interface\"", "\"id\"", "\"reservation-mode\"", "\"disabled\"",
  "\"out-of-pool\"", "\"global\"", "\"all\"",
  "\"host-reservation-identifiers\"", "\"client-classes\"",
  "\"require-client-classes\"", "\"test\"", "\"only-if-required\"",
  "\"client-class\"", "\"reservations\"", "\"duid\"", "\"hw-address\"",
  "\"circuit-id\"", "\"client-id\"", "\"hostname\"", "\"flex-id\"",
  "\"relay\"", "\"ip-address\"", "\"ip-addresses\"", "\"hooks-libraries\"",
  "\"library\"", "\"parameters\"", "\"expired-leases-processing\"",
  "\"reclaim-timer-wait-time\"", "\"flush-reclaimed-timer-wait-time\"",
  "\"hold-reclaimed-time\"", "\"max-reclaim-leases\"",
  "\"max-reclaim-time\"", "\"unwarned-reclaim-cycles\"",
  "\"dhcp4o6-port\"", "\"multi-threading\"", "\"enable-multi-threading\"",
  "\"thread-pool-size\"", "\"packet-queue-size\"", "\"control-socket\"",
  "\"socket-type\"", "\"socket-name\"", "\"dhcp-queue-control\"",
  "\"enable-queue\"", "\"queue-type\"", "\"capacity\"", "\"dhcp-ddns\"",
  "\"enable-updates\"", "\"qualifying-suffix\"", "\"server-ip\"",
  "\"server-port\"", "\"sender-ip\"", "\"sender-port\"",
  "\"max-queue-size\"", "\"ncr-protocol\"", "\"ncr-format\"",
  "\"override-no-update\"", "\"override-client-update\"",
  "\"replace-client-name\"", "\"generated-prefix\"", "\"tcp\"", "\"JSON\"",
  "\"when-present\"", "\"never\"", "\"always\"", "\"when-not-present\"",
  "\"hostname-char-set\"", "\"hostname-char-replacement\"", "\"loggers\"",
  "\"output_options\"", "\"output\"", "\"debuglevel\"", "\"severity\"",
  "\"flush\"", "\"maxsize\"", "\"maxver\"", "\"pattern\"", "TOPLEVEL_JSON",
  "TOPLEVEL_DHCP4", "SUB_DHCP4", "SUB_INTERFACES4", "SUB_SUBNET4",
  "SUB_POOL4", "SUB_RESERVATION", "SUB_OPTION_DEFS", "SUB_OPTION_DEF",
  "SUB_OPTION_DATA", "SUB_HOOKS_LIBRARY", "SUB_DHCP_DDNS",
  "SUB_CONFIG_CONTROL", "\"constant string\"", "\"integer\"",
  "\"floating point\"", "\"boolean\"", "$accept", "start", "$@1", "$@2",
  "$@3", "$@4", "$@5", "$@6", "$@7", "$@8", "$@9", "$@10", "$@11", "$@12",
  "$@13", "value", "sub_json", "map2", "$@14", "map_value", "map_content",
  "not_empty_map", "list_generic", "$@15", "list_content",
  "not_empty_list", "list_strings", "$@16", "list_strings_content",
  "not_empty_list_strings", "unknown_map_entry", "syntax_map", "$@17",
  "global_objects", "global_object", "dhcp4_object", "$@18", "sub_dhcp4",
  "$@19", "global_params", "global_param", "valid_lifetime",
  "min_valid_lifetime", "max_valid_lifetime", "renew_timer",
  "rebind_timer", "calculate_tee_times", "t1_percent", "t2_percent",
  "decline_probation_period", "server_tag", "$@20", "echo_client_id",
  "match_client_id", "authoritative", "ddns_send_updates",
  "ddns_override_no_update", "ddns_override_client_update",
  "ddns_replace_client_name", "$@21", "ddns_replace_client_name_value",
  "ddns_generated_prefix", "$@22", "ddns_qualifying_suffix", "$@23",
  "hostname_char_set", "$@24", "hostname_char_replacement", "$@25",
  "store_extended_info", "statistic_default_sample_count",
  "statistic_default_sample_age", "interfaces_config", "$@26",
  "interfaces_config_params", "interfaces_config_param", "sub_interfaces4",
  "$@27", "interfaces_list", "$@28", "dhcp_socket_type", "$@29",
  "socket_type", "outbound_interface", "$@30", "outbound_interface_value",
  "re_detect", "lease_database", "$@31", "sanity_checks", "$@32",
  "sanity_checks_params", "sanity_checks_param", "lease_checks", "$@33",
  "hosts_database", "$@34", "hosts_databases", "$@35", "database_list",
  "not_empty_database_list", "database", "$@36", "database_map_params",
  "database_map_param", "database_type", "$@37", "db_type", "user", "$@38",
  "password", "$@39", "host", "$@40", "port", "name", "$@41", "persist",
  "lfc_interval", "readonly", "connect_timeout", "request_timeout",
  "tcp_keepalive", "tcp_nodelay", "contact_points", "$@42", "keyspace",
  "$@43", "consistency", "$@44", "serial_consistency", "$@45",
  "max_reconnect_tries", "reconnect_wait_time", "max_row_errors",
  "host_reservation_identifiers", "$@46",
  "host_reservation_identifiers_list", "host_reservation_identifier",
  "duid_id", "hw_address_id", "circuit_id", "client_id", "flex_id",
  "dhcp_multi_threading", "$@47", "multi_threading_params",
  "multi_threading_param", "enable_multi_threading", "thread_pool_size",
  "packet_queue_size", "hooks_libraries", "$@48", "hooks_libraries_list",
  "not_empty_hooks_libraries_list", "hooks_library", "$@49",
  "sub_hooks_library", "$@50", "hooks_params", "hooks_param", "library",
  "$@51", "parameters", "$@52", "expired_leases_processing", "$@53",
  "expired_leases_params", "expired_leases_param",
  "reclaim_timer_wait_time", "flush_reclaimed_timer_wait_time",
  "hold_reclaimed_time", "max_reclaim_leases", "max_reclaim_time",
  "unwarned_reclaim_cycles", "subnet4_list", "$@54",
  "subnet4_list_content", "not_empty_subnet4_list", "subnet4", "$@55",
  "sub_subnet4", "$@56", "subnet4_params", "subnet4_param", "subnet",
  "$@57", "subnet_4o6_interface", "$@58", "subnet_4o6_interface_id",
  "$@59", "subnet_4o6_subnet", "$@60", "interface", "$@61", "client_class",
  "$@62", "require_client_classes", "$@63", "reservation_mode", "$@64",
  "hr_mode", "id", "shared_networks", "$@65", "shared_networks_content",
  "shared_networks_list", "shared_network", "$@66",
  "shared_network_params", "shared_network_param", "option_def_list",
  "$@67", "sub_option_def_list", "$@68", "option_def_list_content",
  "not_empty_option_def_list", "option_def_entry", "$@69",
  "sub_option_def", "$@70", "option_def_params",
  "not_empty_option_def_params", "option_def_param", "option_def_name",
  "code", "option_def_code", "option_def_type", "$@71",
  "option_def_record_types", "$@72", "space", "$@73", "option_def_space",
  "option_def_encapsulate", "$@74", "option_def_array", "option_data_list",
  "$@75", "option_data_list_content", "not_empty_option_data_list",
  "option_data_entry", "$@76", "sub_option_data", "$@77",
  "option_data_params", "not_empty_option_data_params",
  "option_data_param", "option_data_name", "option_data_data", "$@78",
  "option_data_code", "option_data_space", "option_data_csv_format",
  "option_data_always_send", "pools_list", "$@79", "pools_list_content",
  "not_empty_pools_list", "pool_list_entry", "$@80", "sub_pool4", "$@81",
  "pool_params", "pool_param", "pool_entry", "$@82", "user_context",
  "$@83", "comment", "$@84", "reservations", "$@85", "reservations_list",
  "not_empty_reservations_list", "reservation", "$@86", "sub_reservation",
  "$@87", "reservation_params", "not_empty_reservation_params",
  "reservation_param", "next_server", "$@88", "server_hostname", "$@89",
  "boot_file_name", "$@90", "ip_address", "$@91", "ip_addresses", "$@92",
  "duid", "$@93", "hw_address", "$@94", "client_id_value", "$@95",
  "circuit_id_value", "$@96", "flex_id_value", "$@97", "hostname", "$@98",
  "reservation_client_classes", "$@99", "relay", "$@100", "relay_map",
  "client_classes", "$@101", "client_classes_list", "client_class_entry",
  "$@102", "client_class_params", "not_empty_client_class_params",
  "client_class_param", "client_class_name", "client_class_test", "$@103",
  "only_if_required", "dhcp4o6_port", "control_socket", "$@104",
  "control_socket_params", "control_socket_param", "control_socket_type",
  "$@105", "control_socket_name", "$@106", "dhcp_queue_control", "$@107",
  "queue_control_params", "queue_control_param", "enable_queue",
  "queue_type", "$@108", "capacity", "arbitrary_map_entry", "$@109",
  "dhcp_ddns", "$@110", "sub_dhcp_ddns", "$@111", "dhcp_ddns_params",
  "dhcp_ddns_param", "enable_updates", "server_ip", "$@112", "server_port",
  "sender_ip", "$@113", "sender_port", "max_queue_size", "ncr_protocol",
  "$@114", "ncr_protocol_value", "ncr_format", "$@115",
  "dep_qualifying_suffix", "$@116", "dep_override_no_update",
  "dep_override_client_update", "dep_replace_client_name", "$@117",
  "dep_generated_prefix", "$@118", "dep_hostname_char_set", "$@119",
  "dep_hostname_char_replacement", "$@120", "config_control", "$@121",
  "sub_config_control", "$@122", "config_control_params",
  "config_control_param", "config_databases", "$@123",
  "config_fetch_wait_time", "loggers", "$@124", "loggers_entries",
  "logger_entry", "$@125", "logger_params", "logger_param", "debuglevel",
  "severity", "$@126", "output_options_list", "$@127",
  "output_options_list_content", "output_entry", "$@128",
  "output_params_list", "output_params", "output", "$@129", "flush",
  "maxsize", "maxver", "pattern", "$@130", YY_NULLPTR
  };
#endif


#if PARSER4_DEBUG
  const short
  Dhcp4Parser::yyrline_[] =
  {
       0,   277,   277,   277,   278,   278,   279,   279,   280,   280,
     281,   281,   282,   282,   283,   283,   284,   284,   285,   285,
     286,   286,   287,   287,   288,   288,   289,   289,   297,   298,
     299,   300,   301,   302,   303,   306,   311,   311,   322,   325,
     326,   329,   333,   340,   340,   347,   348,   351,   355,   362,
     362,   369,   370,   373,   377,   388,   397,   397,   412,   413,
     417,   420,   420,   437,   437,   446,   447,   452,   453,   454,
     455,   456,   457,   458,   459,   460,   461,   462,   463,   464,
     465,   466,   467,   468,   469,   470,   471,   472,   473,   474,
     475,   476,   477,   478,   479,   480,   481,   482,   483,   484,
     485,   486,   487,   488,   489,   490,   491,   492,   493,   494,
     495,   496,   497,   498,   499,   500,   501,   502,   503,   506,
     511,   516,   521,   526,   531,   536,   541,   546,   551,   551,
     559,   564,   569,   574,   579,   584,   589,   589,   597,   600,
     603,   606,   609,   615,   615,   623,   623,   631,   631,   639,
     639,   647,   652,   657,   662,   662,   673,   674,   677,   678,
     679,   680,   681,   682,   683,   686,   686,   695,   695,   705,
     705,   712,   713,   716,   716,   723,   725,   729,   735,   735,
     747,   747,   757,   758,   760,   762,   762,   780,   780,   792,
     792,   802,   803,   806,   807,   810,   810,   820,   821,   824,
     825,   826,   827,   828,   829,   830,   831,   832,   833,   834,
     835,   836,   837,   838,   839,   840,   841,   842,   843,   844,
     847,   847,   854,   855,   856,   857,   860,   860,   868,   868,
     876,   876,   884,   889,   889,   897,   902,   907,   912,   917,
     922,   927,   932,   932,   940,   940,   948,   948,   956,   956,
     964,   969,   974,   980,   980,   990,   991,   994,   995,   996,
     997,   998,  1001,  1006,  1011,  1016,  1021,  1028,  1028,  1040,
    1041,  1044,  1045,  1046,  1047,  1048,  1049,  1052,  1057,  1062,
    1067,  1067,  1077,  1078,  1081,  1082,  1085,  1085,  1095,  1095,
    1105,  1106,  1107,  1110,  1111,  1114,  1114,  1122,  1122,  1130,
    1130,  1141,  1142,  1145,  1146,  1147,  1148,  1149,  1150,  1153,
    1158,  1163,  1168,  1173,  1178,  1186,  1186,  1199,  1200,  1203,
    1204,  1211,  1211,  1237,  1237,  1248,  1249,  1253,  1254,  1255,
    1256,  1257,  1258,  1259,  1260,  1261,  1262,  1263,  1264,  1265,
    1266,  1267,  1268,  1269,  1270,  1271,  1272,  1273,  1274,  1275,
    1276,  1277,  1278,  1279,  1280,  1281,  1282,  1283,  1284,  1285,
    1286,  1287,  1288,  1289,  1290,  1293,  1293,  1301,  1301,  1309,
    1309,  1317,  1317,  1325,  1325,  1333,  1333,  1341,  1341,  1351,
    1351,  1358,  1359,  1360,  1361,  1364,  1371,  1371,  1382,  1383,
    1387,  1388,  1391,  1391,  1399,  1400,  1403,  1404,  1405,  1406,
    1407,  1408,  1409,  1410,  1411,  1412,  1413,  1414,  1415,  1416,
    1417,  1418,  1419,  1420,  1421,  1422,  1423,  1424,  1425,  1426,
    1427,  1428,  1429,  1430,  1431,  1432,  1433,  1434,  1435,  1442,
    1442,  1455,  1455,  1464,  1465,  1468,  1469,  1474,  1474,  1489,
    1489,  1503,  1504,  1507,  1508,  1511,  1512,  1513,  1514,  1515,
    1516,  1517,  1518,  1519,  1520,  1523,  1525,  1530,  1532,  1532,
    1540,  1540,  1548,  1548,  1556,  1558,  1558,  1566,  1575,  1575,
    1587,  1588,  1593,  1594,  1599,  1599,  1611,  1611,  1623,  1624,
    1629,  1630,  1635,  1636,  1637,  1638,  1639,  1640,  1641,  1642,
    1643,  1646,  1648,  1648,  1656,  1658,  1660,  1665,  1673,  1673,
    1685,  1686,  1689,  1690,  1693,  1693,  1703,  1703,  1713,  1714,
    1717,  1718,  1719,  1720,  1721,  1722,  1723,  1726,  1726,  1734,
    1734,  1759,  1759,  1789,  1789,  1799,  1800,  1803,  1804,  1807,
    1807,  1816,  1816,  1825,  1826,  1829,  1830,  1834,  1835,  1836,
    1837,  1838,  1839,  1840,  1841,  1842,  1843,  1844,  1845,  1846,
    1847,  1848,  1851,  1851,  1859,  1859,  1867,  1867,  1875,  1875,
    1883,  1883,  1893,  1893,  1901,  1901,  1909,  1909,  1917,  1917,
    1925,  1925,  1933,  1933,  1941,  1941,  1954,  1954,  1964,  1965,
    1971,  1971,  1981,  1982,  1985,  1985,  1995,  1996,  1999,  2000,
    2003,  2004,  2005,  2006,  2007,  2008,  2009,  2010,  2011,  2012,
    2013,  2016,  2018,  2018,  2026,  2033,  2040,  2040,  2050,  2051,
    2054,  2055,  2056,  2057,  2058,  2061,  2061,  2069,  2069,  2080,
    2080,  2092,  2093,  2096,  2097,  2098,  2099,  2100,  2101,  2104,
    2109,  2109,  2117,  2122,  2122,  2131,  2131,  2143,  2143,  2153,
    2154,  2157,  2158,  2159,  2160,  2161,  2162,  2163,  2164,  2165,
    2166,  2167,  2168,  2169,  2170,  2171,  2172,  2173,  2174,  2177,
    2182,  2182,  2190,  2195,  2195,  2203,  2208,  2213,  2213,  2221,
    2222,  2225,  2225,  2234,  2234,  2243,  2249,  2255,  2255,  2263,
    2263,  2272,  2272,  2281,  2281,  2292,  2292,  2303,  2303,  2313,
    2314,  2318,  2319,  2322,  2322,  2332,  2339,  2339,  2351,  2352,
    2356,  2356,  2364,  2365,  2368,  2369,  2370,  2371,  2372,  2373,
    2374,  2377,  2382,  2382,  2390,  2390,  2400,  2401,  2404,  2404,
    2412,  2413,  2416,  2417,  2418,  2419,  2420,  2423,  2423,  2431,
    2436,  2441,  2446,  2446
  };

  void
  Dhcp4Parser::yy_stack_print_ () const
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
  Dhcp4Parser::yy_reduce_print_ (int yyrule) const
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
#endif // PARSER4_DEBUG


#line 14 "dhcp4_parser.yy"
} } // isc::dhcp
#line 5422 "dhcp4_parser.cc"

#line 2454 "dhcp4_parser.yy"


void
isc::dhcp::Dhcp4Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
