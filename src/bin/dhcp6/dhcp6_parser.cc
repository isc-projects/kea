// A Bison parser, made by GNU Bison 3.5.3.

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

// Undocumented macros, especially those whose name start with YY_,
// are private implementation details.  Do not rely on them.


// Take the name prefix into account.
#define yylex   parser6_lex



#include "dhcp6_parser.h"


// Unqualified %code blocks.
#line 34 "dhcp6_parser.yy"

#include <dhcp6/parser_context.h>

#line 51 "dhcp6_parser.cc"


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
      yystack_print_ ();                \
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
#line 143 "dhcp6_parser.cc"


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
  | Symbol types.  |
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

  Dhcp6Parser::symbol_number_type
  Dhcp6Parser::by_state::type_get () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[+state];
  }

  Dhcp6Parser::stack_symbol_type::stack_symbol_type ()
  {}

  Dhcp6Parser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state), YY_MOVE (that.location))
  {
    switch (that.type_get ())
    {
      case 216: // value
      case 220: // map_value
      case 261: // ddns_replace_client_name_value
      case 298: // db_type
      case 392: // hr_mode
      case 528: // duid_type
      case 571: // ncr_protocol_value
        value.YY_MOVE_OR_COPY< ElementPtr > (YY_MOVE (that.value));
        break;

      case 198: // "boolean"
        value.YY_MOVE_OR_COPY< bool > (YY_MOVE (that.value));
        break;

      case 197: // "floating point"
        value.YY_MOVE_OR_COPY< double > (YY_MOVE (that.value));
        break;

      case 196: // "integer"
        value.YY_MOVE_OR_COPY< int64_t > (YY_MOVE (that.value));
        break;

      case 195: // "constant string"
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
    switch (that.type_get ())
    {
      case 216: // value
      case 220: // map_value
      case 261: // ddns_replace_client_name_value
      case 298: // db_type
      case 392: // hr_mode
      case 528: // duid_type
      case 571: // ncr_protocol_value
        value.move< ElementPtr > (YY_MOVE (that.value));
        break;

      case 198: // "boolean"
        value.move< bool > (YY_MOVE (that.value));
        break;

      case 197: // "floating point"
        value.move< double > (YY_MOVE (that.value));
        break;

      case 196: // "integer"
        value.move< int64_t > (YY_MOVE (that.value));
        break;

      case 195: // "constant string"
        value.move< std::string > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

    // that is emptied.
    that.type = empty_symbol;
  }

#if YY_CPLUSPLUS < 201103L
  Dhcp6Parser::stack_symbol_type&
  Dhcp6Parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    switch (that.type_get ())
    {
      case 216: // value
      case 220: // map_value
      case 261: // ddns_replace_client_name_value
      case 298: // db_type
      case 392: // hr_mode
      case 528: // duid_type
      case 571: // ncr_protocol_value
        value.copy< ElementPtr > (that.value);
        break;

      case 198: // "boolean"
        value.copy< bool > (that.value);
        break;

      case 197: // "floating point"
        value.copy< double > (that.value);
        break;

      case 196: // "integer"
        value.copy< int64_t > (that.value);
        break;

      case 195: // "constant string"
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
    switch (that.type_get ())
    {
      case 216: // value
      case 220: // map_value
      case 261: // ddns_replace_client_name_value
      case 298: // db_type
      case 392: // hr_mode
      case 528: // duid_type
      case 571: // ncr_protocol_value
        value.move< ElementPtr > (that.value);
        break;

      case 198: // "boolean"
        value.move< bool > (that.value);
        break;

      case 197: // "floating point"
        value.move< double > (that.value);
        break;

      case 196: // "integer"
        value.move< int64_t > (that.value);
        break;

      case 195: // "constant string"
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
  Dhcp6Parser::yy_print_ (std::ostream& yyo,
                                     const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YYUSE (yyoutput);
    symbol_number_type yytype = yysym.type_get ();
#if defined __GNUC__ && ! defined __clang__ && ! defined __ICC && __GNUC__ * 100 + __GNUC_MINOR__ <= 408
    // Avoid a (spurious) G++ 4.8 warning about "array subscript is
    // below array bounds".
    if (yysym.empty ())
      std::abort ();
#endif
    yyo << (yytype < yyntokens_ ? "token" : "nterm")
        << ' ' << yytname_[yytype] << " ("
        << yysym.location << ": ";
    switch (yytype)
    {
      case 195: // "constant string"
#line 274 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < std::string > (); }
#line 443 "dhcp6_parser.cc"
        break;

      case 196: // "integer"
#line 274 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < int64_t > (); }
#line 449 "dhcp6_parser.cc"
        break;

      case 197: // "floating point"
#line 274 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < double > (); }
#line 455 "dhcp6_parser.cc"
        break;

      case 198: // "boolean"
#line 274 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < bool > (); }
#line 461 "dhcp6_parser.cc"
        break;

      case 216: // value
#line 274 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 467 "dhcp6_parser.cc"
        break;

      case 220: // map_value
#line 274 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 473 "dhcp6_parser.cc"
        break;

      case 261: // ddns_replace_client_name_value
#line 274 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 479 "dhcp6_parser.cc"
        break;

      case 298: // db_type
#line 274 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 485 "dhcp6_parser.cc"
        break;

      case 392: // hr_mode
#line 274 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 491 "dhcp6_parser.cc"
        break;

      case 528: // duid_type
#line 274 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 497 "dhcp6_parser.cc"
        break;

      case 571: // ncr_protocol_value
#line 274 "dhcp6_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 503 "dhcp6_parser.cc"
        break;

      default:
        break;
    }
    yyo << ')';
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
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
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
        YYCDEBUG << "Reading a token: ";
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

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.type_get ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.type_get ())
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
      case 216: // value
      case 220: // map_value
      case 261: // ddns_replace_client_name_value
      case 298: // db_type
      case 392: // hr_mode
      case 528: // duid_type
      case 571: // ncr_protocol_value
        yylhs.value.emplace< ElementPtr > ();
        break;

      case 198: // "boolean"
        yylhs.value.emplace< bool > ();
        break;

      case 197: // "floating point"
        yylhs.value.emplace< double > ();
        break;

      case 196: // "integer"
        yylhs.value.emplace< int64_t > ();
        break;

      case 195: // "constant string"
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
#line 770 "dhcp6_parser.cc"
    break;

  case 4:
#line 284 "dhcp6_parser.yy"
                      { ctx.ctx_ = ctx.CONFIG; }
#line 776 "dhcp6_parser.cc"
    break;

  case 6:
#line 285 "dhcp6_parser.yy"
                 { ctx.ctx_ = ctx.DHCP6; }
#line 782 "dhcp6_parser.cc"
    break;

  case 8:
#line 286 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 788 "dhcp6_parser.cc"
    break;

  case 10:
#line 287 "dhcp6_parser.yy"
                   { ctx.ctx_ = ctx.SUBNET6; }
#line 794 "dhcp6_parser.cc"
    break;

  case 12:
#line 288 "dhcp6_parser.yy"
                 { ctx.ctx_ = ctx.POOLS; }
#line 800 "dhcp6_parser.cc"
    break;

  case 14:
#line 289 "dhcp6_parser.yy"
                   { ctx.ctx_ = ctx.PD_POOLS; }
#line 806 "dhcp6_parser.cc"
    break;

  case 16:
#line 290 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.RESERVATIONS; }
#line 812 "dhcp6_parser.cc"
    break;

  case 18:
#line 291 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.DHCP6; }
#line 818 "dhcp6_parser.cc"
    break;

  case 20:
#line 292 "dhcp6_parser.yy"
                      { ctx.ctx_ = ctx.OPTION_DEF; }
#line 824 "dhcp6_parser.cc"
    break;

  case 22:
#line 293 "dhcp6_parser.yy"
                       { ctx.ctx_ = ctx.OPTION_DATA; }
#line 830 "dhcp6_parser.cc"
    break;

  case 24:
#line 294 "dhcp6_parser.yy"
                         { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 836 "dhcp6_parser.cc"
    break;

  case 26:
#line 295 "dhcp6_parser.yy"
                     { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 842 "dhcp6_parser.cc"
    break;

  case 28:
#line 296 "dhcp6_parser.yy"
                   { ctx.ctx_ = ctx.LOGGING; }
#line 848 "dhcp6_parser.cc"
    break;

  case 30:
#line 297 "dhcp6_parser.yy"
                          { ctx.ctx_ = ctx.CONFIG_CONTROL; }
#line 854 "dhcp6_parser.cc"
    break;

  case 32:
#line 305 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 860 "dhcp6_parser.cc"
    break;

  case 33:
#line 306 "dhcp6_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location))); }
#line 866 "dhcp6_parser.cc"
    break;

  case 34:
#line 307 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 872 "dhcp6_parser.cc"
    break;

  case 35:
#line 308 "dhcp6_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 878 "dhcp6_parser.cc"
    break;

  case 36:
#line 309 "dhcp6_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 884 "dhcp6_parser.cc"
    break;

  case 37:
#line 310 "dhcp6_parser.yy"
            { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 890 "dhcp6_parser.cc"
    break;

  case 38:
#line 311 "dhcp6_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 896 "dhcp6_parser.cc"
    break;

  case 39:
#line 314 "dhcp6_parser.yy"
                {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as < ElementPtr > ());
}
#line 905 "dhcp6_parser.cc"
    break;

  case 40:
#line 319 "dhcp6_parser.yy"
                     {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 916 "dhcp6_parser.cc"
    break;

  case 41:
#line 324 "dhcp6_parser.yy"
                             {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 926 "dhcp6_parser.cc"
    break;

  case 42:
#line 330 "dhcp6_parser.yy"
                { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 932 "dhcp6_parser.cc"
    break;

  case 45:
#line 337 "dhcp6_parser.yy"
                                  {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 941 "dhcp6_parser.cc"
    break;

  case 46:
#line 341 "dhcp6_parser.yy"
                                                      {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 951 "dhcp6_parser.cc"
    break;

  case 47:
#line 348 "dhcp6_parser.yy"
                              {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 960 "dhcp6_parser.cc"
    break;

  case 48:
#line 351 "dhcp6_parser.yy"
                               {
    // list parsing complete. Put any sanity checking here
}
#line 968 "dhcp6_parser.cc"
    break;

  case 51:
#line 359 "dhcp6_parser.yy"
                      {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 977 "dhcp6_parser.cc"
    break;

  case 52:
#line 363 "dhcp6_parser.yy"
                                           {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 986 "dhcp6_parser.cc"
    break;

  case 53:
#line 370 "dhcp6_parser.yy"
                              {
    // List parsing about to start
}
#line 994 "dhcp6_parser.cc"
    break;

  case 54:
#line 372 "dhcp6_parser.yy"
                                       {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 1003 "dhcp6_parser.cc"
    break;

  case 57:
#line 381 "dhcp6_parser.yy"
                               {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 1012 "dhcp6_parser.cc"
    break;

  case 58:
#line 385 "dhcp6_parser.yy"
                                                            {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 1021 "dhcp6_parser.cc"
    break;

  case 59:
#line 396 "dhcp6_parser.yy"
                                {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as < std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 1032 "dhcp6_parser.cc"
    break;

  case 60:
#line 406 "dhcp6_parser.yy"
                           {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1043 "dhcp6_parser.cc"
    break;

  case 61:
#line 411 "dhcp6_parser.yy"
                                {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.

    // Dhcp6 is required
    ctx.require("Dhcp6", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
}
#line 1056 "dhcp6_parser.cc"
    break;

  case 70:
#line 434 "dhcp6_parser.yy"
                    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Dhcp6", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP6);
}
#line 1069 "dhcp6_parser.cc"
    break;

  case 71:
#line 441 "dhcp6_parser.yy"
                                                    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1079 "dhcp6_parser.cc"
    break;

  case 72:
#line 449 "dhcp6_parser.yy"
                          {
    // Parse the Dhcp6 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1089 "dhcp6_parser.cc"
    break;

  case 73:
#line 453 "dhcp6_parser.yy"
                               {
    // No global parameter is required
    // parsing completed
}
#line 1098 "dhcp6_parser.cc"
    break;

  case 128:
#line 518 "dhcp6_parser.yy"
                               {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1106 "dhcp6_parser.cc"
    break;

  case 129:
#line 520 "dhcp6_parser.yy"
               {
    ElementPtr datadir(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data-directory", datadir);
    ctx.leave();
}
#line 1116 "dhcp6_parser.cc"
    break;

  case 130:
#line 526 "dhcp6_parser.yy"
                                                     {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("preferred-lifetime", prf);
}
#line 1125 "dhcp6_parser.cc"
    break;

  case 131:
#line 531 "dhcp6_parser.yy"
                                                             {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-preferred-lifetime", prf);
}
#line 1134 "dhcp6_parser.cc"
    break;

  case 132:
#line 536 "dhcp6_parser.yy"
                                                             {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-preferred-lifetime", prf);
}
#line 1143 "dhcp6_parser.cc"
    break;

  case 133:
#line 541 "dhcp6_parser.yy"
                                             {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1152 "dhcp6_parser.cc"
    break;

  case 134:
#line 546 "dhcp6_parser.yy"
                                                     {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-valid-lifetime", prf);
}
#line 1161 "dhcp6_parser.cc"
    break;

  case 135:
#line 551 "dhcp6_parser.yy"
                                                     {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-valid-lifetime", prf);
}
#line 1170 "dhcp6_parser.cc"
    break;

  case 136:
#line 556 "dhcp6_parser.yy"
                                       {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1179 "dhcp6_parser.cc"
    break;

  case 137:
#line 561 "dhcp6_parser.yy"
                                         {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1188 "dhcp6_parser.cc"
    break;

  case 138:
#line 566 "dhcp6_parser.yy"
                                                       {
    ElementPtr ctt(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("calculate-tee-times", ctt);
}
#line 1197 "dhcp6_parser.cc"
    break;

  case 139:
#line 571 "dhcp6_parser.yy"
                                   {
    ElementPtr t1(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t1-percent", t1);
}
#line 1206 "dhcp6_parser.cc"
    break;

  case 140:
#line 576 "dhcp6_parser.yy"
                                   {
    ElementPtr t2(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t2-percent", t2);
}
#line 1215 "dhcp6_parser.cc"
    break;

  case 141:
#line 581 "dhcp6_parser.yy"
                                                                 {
    ElementPtr dpp(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1224 "dhcp6_parser.cc"
    break;

  case 142:
#line 586 "dhcp6_parser.yy"
                                                   {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-send-updates", b);
}
#line 1233 "dhcp6_parser.cc"
    break;

  case 143:
#line 591 "dhcp6_parser.yy"
                                                               {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-no-update", b);
}
#line 1242 "dhcp6_parser.cc"
    break;

  case 144:
#line 596 "dhcp6_parser.yy"
                                                                       {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-client-update", b);
}
#line 1251 "dhcp6_parser.cc"
    break;

  case 145:
#line 601 "dhcp6_parser.yy"
                                                   {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 1259 "dhcp6_parser.cc"
    break;

  case 146:
#line 603 "dhcp6_parser.yy"
                                       {
    ctx.stack_.back()->set("ddns-replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1268 "dhcp6_parser.cc"
    break;

  case 147:
#line 609 "dhcp6_parser.yy"
                 {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1276 "dhcp6_parser.cc"
    break;

  case 148:
#line 612 "dhcp6_parser.yy"
          {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 1284 "dhcp6_parser.cc"
    break;

  case 149:
#line 615 "dhcp6_parser.yy"
           {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 1292 "dhcp6_parser.cc"
    break;

  case 150:
#line 618 "dhcp6_parser.yy"
                     {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1300 "dhcp6_parser.cc"
    break;

  case 151:
#line 621 "dhcp6_parser.yy"
             {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 1309 "dhcp6_parser.cc"
    break;

  case 152:
#line 627 "dhcp6_parser.yy"
                                             {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1317 "dhcp6_parser.cc"
    break;

  case 153:
#line 629 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-generated-prefix", s);
    ctx.leave();
}
#line 1327 "dhcp6_parser.cc"
    break;

  case 154:
#line 635 "dhcp6_parser.yy"
                                               {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1335 "dhcp6_parser.cc"
    break;

  case 155:
#line 637 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-qualifying-suffix", s);
    ctx.leave();
}
#line 1345 "dhcp6_parser.cc"
    break;

  case 156:
#line 643 "dhcp6_parser.yy"
                                     {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1353 "dhcp6_parser.cc"
    break;

  case 157:
#line 645 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 1363 "dhcp6_parser.cc"
    break;

  case 158:
#line 651 "dhcp6_parser.yy"
                                                     {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1371 "dhcp6_parser.cc"
    break;

  case 159:
#line 653 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 1381 "dhcp6_parser.cc"
    break;

  case 160:
#line 659 "dhcp6_parser.yy"
                                                       {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("store-extended-info", b);
}
#line 1390 "dhcp6_parser.cc"
    break;

  case 161:
#line 664 "dhcp6_parser.yy"
                                                                             {
    ElementPtr count(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-count", count);
}
#line 1399 "dhcp6_parser.cc"
    break;

  case 162:
#line 669 "dhcp6_parser.yy"
                                                                         {
    ElementPtr age(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-age", age);
}
#line 1408 "dhcp6_parser.cc"
    break;

  case 163:
#line 674 "dhcp6_parser.yy"
                       {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1416 "dhcp6_parser.cc"
    break;

  case 164:
#line 676 "dhcp6_parser.yy"
               {
    ElementPtr stag(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-tag", stag);
    ctx.leave();
}
#line 1426 "dhcp6_parser.cc"
    break;

  case 165:
#line 682 "dhcp6_parser.yy"
                                     {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1437 "dhcp6_parser.cc"
    break;

  case 166:
#line 687 "dhcp6_parser.yy"
                                                               {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1447 "dhcp6_parser.cc"
    break;

  case 167:
#line 693 "dhcp6_parser.yy"
                                {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1457 "dhcp6_parser.cc"
    break;

  case 168:
#line 697 "dhcp6_parser.yy"
                                          {
    // No interfaces config param is required
    // parsing completed
}
#line 1466 "dhcp6_parser.cc"
    break;

  case 176:
#line 713 "dhcp6_parser.yy"
                            {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1477 "dhcp6_parser.cc"
    break;

  case 177:
#line 718 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1486 "dhcp6_parser.cc"
    break;

  case 178:
#line 723 "dhcp6_parser.yy"
                                   {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1495 "dhcp6_parser.cc"
    break;

  case 179:
#line 729 "dhcp6_parser.yy"
                               {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1506 "dhcp6_parser.cc"
    break;

  case 180:
#line 734 "dhcp6_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1517 "dhcp6_parser.cc"
    break;

  case 181:
#line 741 "dhcp6_parser.yy"
                               {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1528 "dhcp6_parser.cc"
    break;

  case 182:
#line 746 "dhcp6_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1539 "dhcp6_parser.cc"
    break;

  case 183:
#line 753 "dhcp6_parser.yy"
                                 {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1550 "dhcp6_parser.cc"
    break;

  case 184:
#line 758 "dhcp6_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1559 "dhcp6_parser.cc"
    break;

  case 189:
#line 771 "dhcp6_parser.yy"
                         {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1569 "dhcp6_parser.cc"
    break;

  case 190:
#line 775 "dhcp6_parser.yy"
                                     {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1579 "dhcp6_parser.cc"
    break;

  case 214:
#line 808 "dhcp6_parser.yy"
                    {
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1587 "dhcp6_parser.cc"
    break;

  case 215:
#line 810 "dhcp6_parser.yy"
                {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1596 "dhcp6_parser.cc"
    break;

  case 216:
#line 815 "dhcp6_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1602 "dhcp6_parser.cc"
    break;

  case 217:
#line 816 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1608 "dhcp6_parser.cc"
    break;

  case 218:
#line 817 "dhcp6_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1614 "dhcp6_parser.cc"
    break;

  case 219:
#line 818 "dhcp6_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1620 "dhcp6_parser.cc"
    break;

  case 220:
#line 821 "dhcp6_parser.yy"
           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1628 "dhcp6_parser.cc"
    break;

  case 221:
#line 823 "dhcp6_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1638 "dhcp6_parser.cc"
    break;

  case 222:
#line 829 "dhcp6_parser.yy"
                   {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1646 "dhcp6_parser.cc"
    break;

  case 223:
#line 831 "dhcp6_parser.yy"
               {
    ElementPtr pwd(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1656 "dhcp6_parser.cc"
    break;

  case 224:
#line 837 "dhcp6_parser.yy"
           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1664 "dhcp6_parser.cc"
    break;

  case 225:
#line 839 "dhcp6_parser.yy"
               {
    ElementPtr h(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1674 "dhcp6_parser.cc"
    break;

  case 226:
#line 845 "dhcp6_parser.yy"
                         {
    ElementPtr p(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1683 "dhcp6_parser.cc"
    break;

  case 227:
#line 850 "dhcp6_parser.yy"
           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1691 "dhcp6_parser.cc"
    break;

  case 228:
#line 852 "dhcp6_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1701 "dhcp6_parser.cc"
    break;

  case 229:
#line 858 "dhcp6_parser.yy"
                               {
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1710 "dhcp6_parser.cc"
    break;

  case 230:
#line 863 "dhcp6_parser.yy"
                                         {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1719 "dhcp6_parser.cc"
    break;

  case 231:
#line 868 "dhcp6_parser.yy"
                                 {
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1728 "dhcp6_parser.cc"
    break;

  case 232:
#line 873 "dhcp6_parser.yy"
                                               {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1737 "dhcp6_parser.cc"
    break;

  case 233:
#line 878 "dhcp6_parser.yy"
                                                       {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 1746 "dhcp6_parser.cc"
    break;

  case 234:
#line 883 "dhcp6_parser.yy"
                                             {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-row-errors", n);
}
#line 1755 "dhcp6_parser.cc"
    break;

  case 235:
#line 888 "dhcp6_parser.yy"
                                               {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("request-timeout", n);
}
#line 1764 "dhcp6_parser.cc"
    break;

  case 236:
#line 893 "dhcp6_parser.yy"
                                           {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-keepalive", n);
}
#line 1773 "dhcp6_parser.cc"
    break;

  case 237:
#line 898 "dhcp6_parser.yy"
                                       {
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-nodelay", n);
}
#line 1782 "dhcp6_parser.cc"
    break;

  case 238:
#line 903 "dhcp6_parser.yy"
                               {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1790 "dhcp6_parser.cc"
    break;

  case 239:
#line 905 "dhcp6_parser.yy"
               {
    ElementPtr cp(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1800 "dhcp6_parser.cc"
    break;

  case 240:
#line 911 "dhcp6_parser.yy"
                                                       {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 1809 "dhcp6_parser.cc"
    break;

  case 241:
#line 916 "dhcp6_parser.yy"
                   {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1817 "dhcp6_parser.cc"
    break;

  case 242:
#line 918 "dhcp6_parser.yy"
               {
    ElementPtr ks(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 1827 "dhcp6_parser.cc"
    break;

  case 243:
#line 924 "dhcp6_parser.yy"
                         {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1835 "dhcp6_parser.cc"
    break;

  case 244:
#line 926 "dhcp6_parser.yy"
               {
    ElementPtr c(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("consistency", c);
    ctx.leave();
}
#line 1845 "dhcp6_parser.cc"
    break;

  case 245:
#line 932 "dhcp6_parser.yy"
                                       {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1853 "dhcp6_parser.cc"
    break;

  case 246:
#line 934 "dhcp6_parser.yy"
               {
    ElementPtr c(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("serial-consistency", c);
    ctx.leave();
}
#line 1863 "dhcp6_parser.cc"
    break;

  case 247:
#line 940 "dhcp6_parser.yy"
                             {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sanity-checks", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SANITY_CHECKS);
}
#line 1874 "dhcp6_parser.cc"
    break;

  case 248:
#line 945 "dhcp6_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1883 "dhcp6_parser.cc"
    break;

  case 252:
#line 955 "dhcp6_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1891 "dhcp6_parser.cc"
    break;

  case 253:
#line 957 "dhcp6_parser.yy"
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
#line 1911 "dhcp6_parser.cc"
    break;

  case 254:
#line 973 "dhcp6_parser.yy"
                         {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("mac-sources", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.MAC_SOURCES);
}
#line 1922 "dhcp6_parser.cc"
    break;

  case 255:
#line 978 "dhcp6_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1931 "dhcp6_parser.cc"
    break;

  case 260:
#line 991 "dhcp6_parser.yy"
               {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1940 "dhcp6_parser.cc"
    break;

  case 261:
#line 996 "dhcp6_parser.yy"
                   {
    ElementPtr duid(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1949 "dhcp6_parser.cc"
    break;

  case 262:
#line 1001 "dhcp6_parser.yy"
                                                           {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1960 "dhcp6_parser.cc"
    break;

  case 263:
#line 1006 "dhcp6_parser.yy"
                                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1969 "dhcp6_parser.cc"
    break;

  case 269:
#line 1020 "dhcp6_parser.yy"
                           {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1978 "dhcp6_parser.cc"
    break;

  case 270:
#line 1025 "dhcp6_parser.yy"
                  {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 1987 "dhcp6_parser.cc"
    break;

  case 271:
#line 1032 "dhcp6_parser.yy"
                                               {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay-supplied-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1998 "dhcp6_parser.cc"
    break;

  case 272:
#line 1037 "dhcp6_parser.yy"
                                                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2007 "dhcp6_parser.cc"
    break;

  case 273:
#line 1042 "dhcp6_parser.yy"
                                 {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 2018 "dhcp6_parser.cc"
    break;

  case 274:
#line 1047 "dhcp6_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2027 "dhcp6_parser.cc"
    break;

  case 279:
#line 1060 "dhcp6_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2037 "dhcp6_parser.cc"
    break;

  case 280:
#line 1064 "dhcp6_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2047 "dhcp6_parser.cc"
    break;

  case 281:
#line 1070 "dhcp6_parser.yy"
                                  {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2057 "dhcp6_parser.cc"
    break;

  case 282:
#line 1074 "dhcp6_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2067 "dhcp6_parser.cc"
    break;

  case 288:
#line 1089 "dhcp6_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2075 "dhcp6_parser.cc"
    break;

  case 289:
#line 1091 "dhcp6_parser.yy"
               {
    ElementPtr lib(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 2085 "dhcp6_parser.cc"
    break;

  case 290:
#line 1097 "dhcp6_parser.yy"
                       {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2093 "dhcp6_parser.cc"
    break;

  case 291:
#line 1099 "dhcp6_parser.yy"
              {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2102 "dhcp6_parser.cc"
    break;

  case 292:
#line 1105 "dhcp6_parser.yy"
                                                     {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 2113 "dhcp6_parser.cc"
    break;

  case 293:
#line 1110 "dhcp6_parser.yy"
                                                            {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2123 "dhcp6_parser.cc"
    break;

  case 302:
#line 1128 "dhcp6_parser.yy"
                                                               {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 2132 "dhcp6_parser.cc"
    break;

  case 303:
#line 1133 "dhcp6_parser.yy"
                                                                               {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 2141 "dhcp6_parser.cc"
    break;

  case 304:
#line 1138 "dhcp6_parser.yy"
                                                       {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 2150 "dhcp6_parser.cc"
    break;

  case 305:
#line 1143 "dhcp6_parser.yy"
                                                     {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 2159 "dhcp6_parser.cc"
    break;

  case 306:
#line 1148 "dhcp6_parser.yy"
                                                 {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 2168 "dhcp6_parser.cc"
    break;

  case 307:
#line 1153 "dhcp6_parser.yy"
                                                               {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 2177 "dhcp6_parser.cc"
    break;

  case 308:
#line 1161 "dhcp6_parser.yy"
                      {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet6", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET6);
}
#line 2188 "dhcp6_parser.cc"
    break;

  case 309:
#line 1166 "dhcp6_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2197 "dhcp6_parser.cc"
    break;

  case 314:
#line 1186 "dhcp6_parser.yy"
                        {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2207 "dhcp6_parser.cc"
    break;

  case 315:
#line 1190 "dhcp6_parser.yy"
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
#line 2233 "dhcp6_parser.cc"
    break;

  case 316:
#line 1212 "dhcp6_parser.yy"
                            {
    // Parse the subnet6 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2243 "dhcp6_parser.cc"
    break;

  case 317:
#line 1216 "dhcp6_parser.yy"
                                {
    // The subnet subnet6 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2253 "dhcp6_parser.cc"
    break;

  case 356:
#line 1266 "dhcp6_parser.yy"
               {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2261 "dhcp6_parser.cc"
    break;

  case 357:
#line 1268 "dhcp6_parser.yy"
               {
    ElementPtr subnet(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 2271 "dhcp6_parser.cc"
    break;

  case 358:
#line 1274 "dhcp6_parser.yy"
                     {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2279 "dhcp6_parser.cc"
    break;

  case 359:
#line 1276 "dhcp6_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 2289 "dhcp6_parser.cc"
    break;

  case 360:
#line 1282 "dhcp6_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2297 "dhcp6_parser.cc"
    break;

  case 361:
#line 1284 "dhcp6_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 2307 "dhcp6_parser.cc"
    break;

  case 362:
#line 1290 "dhcp6_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2315 "dhcp6_parser.cc"
    break;

  case 363:
#line 1292 "dhcp6_parser.yy"
               {
    ElementPtr cls(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 2325 "dhcp6_parser.cc"
    break;

  case 364:
#line 1298 "dhcp6_parser.yy"
                                               {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2336 "dhcp6_parser.cc"
    break;

  case 365:
#line 1303 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2345 "dhcp6_parser.cc"
    break;

  case 366:
#line 1308 "dhcp6_parser.yy"
                                   {
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 2353 "dhcp6_parser.cc"
    break;

  case 367:
#line 1310 "dhcp6_parser.yy"
                {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2362 "dhcp6_parser.cc"
    break;

  case 368:
#line 1315 "dhcp6_parser.yy"
                  { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 2368 "dhcp6_parser.cc"
    break;

  case 369:
#line 1316 "dhcp6_parser.yy"
                     { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 2374 "dhcp6_parser.cc"
    break;

  case 370:
#line 1317 "dhcp6_parser.yy"
                { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("global", ctx.loc2pos(yystack_[0].location))); }
#line 2380 "dhcp6_parser.cc"
    break;

  case 371:
#line 1318 "dhcp6_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 2386 "dhcp6_parser.cc"
    break;

  case 372:
#line 1321 "dhcp6_parser.yy"
                     {
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 2395 "dhcp6_parser.cc"
    break;

  case 373:
#line 1326 "dhcp6_parser.yy"
                                         {
    ElementPtr rc(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 2404 "dhcp6_parser.cc"
    break;

  case 374:
#line 1334 "dhcp6_parser.yy"
                                 {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 2415 "dhcp6_parser.cc"
    break;

  case 375:
#line 1339 "dhcp6_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2424 "dhcp6_parser.cc"
    break;

  case 380:
#line 1354 "dhcp6_parser.yy"
                               {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2434 "dhcp6_parser.cc"
    break;

  case 381:
#line 1358 "dhcp6_parser.yy"
                                       {
    ctx.stack_.pop_back();
}
#line 2442 "dhcp6_parser.cc"
    break;

  case 417:
#line 1405 "dhcp6_parser.yy"
                            {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 2453 "dhcp6_parser.cc"
    break;

  case 418:
#line 1410 "dhcp6_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2462 "dhcp6_parser.cc"
    break;

  case 419:
#line 1418 "dhcp6_parser.yy"
                                    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2471 "dhcp6_parser.cc"
    break;

  case 420:
#line 1421 "dhcp6_parser.yy"
                                 {
    // parsing completed
}
#line 2479 "dhcp6_parser.cc"
    break;

  case 425:
#line 1437 "dhcp6_parser.yy"
                                 {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2489 "dhcp6_parser.cc"
    break;

  case 426:
#line 1441 "dhcp6_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2501 "dhcp6_parser.cc"
    break;

  case 427:
#line 1452 "dhcp6_parser.yy"
                               {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2511 "dhcp6_parser.cc"
    break;

  case 428:
#line 1456 "dhcp6_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2523 "dhcp6_parser.cc"
    break;

  case 444:
#line 1488 "dhcp6_parser.yy"
                         {
    ElementPtr code(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 2532 "dhcp6_parser.cc"
    break;

  case 446:
#line 1495 "dhcp6_parser.yy"
                      {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2540 "dhcp6_parser.cc"
    break;

  case 447:
#line 1497 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 2550 "dhcp6_parser.cc"
    break;

  case 448:
#line 1503 "dhcp6_parser.yy"
                                      {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2558 "dhcp6_parser.cc"
    break;

  case 449:
#line 1505 "dhcp6_parser.yy"
               {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 2568 "dhcp6_parser.cc"
    break;

  case 450:
#line 1511 "dhcp6_parser.yy"
             {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2576 "dhcp6_parser.cc"
    break;

  case 451:
#line 1513 "dhcp6_parser.yy"
               {
    ElementPtr space(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 2586 "dhcp6_parser.cc"
    break;

  case 453:
#line 1521 "dhcp6_parser.yy"
                                    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2594 "dhcp6_parser.cc"
    break;

  case 454:
#line 1523 "dhcp6_parser.yy"
               {
    ElementPtr encap(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 2604 "dhcp6_parser.cc"
    break;

  case 455:
#line 1529 "dhcp6_parser.yy"
                                      {
    ElementPtr array(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 2613 "dhcp6_parser.cc"
    break;

  case 456:
#line 1538 "dhcp6_parser.yy"
                              {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 2624 "dhcp6_parser.cc"
    break;

  case 457:
#line 1543 "dhcp6_parser.yy"
                                                                 {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2633 "dhcp6_parser.cc"
    break;

  case 462:
#line 1562 "dhcp6_parser.yy"
                                  {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2643 "dhcp6_parser.cc"
    break;

  case 463:
#line 1566 "dhcp6_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 2652 "dhcp6_parser.cc"
    break;

  case 464:
#line 1574 "dhcp6_parser.yy"
                                {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2662 "dhcp6_parser.cc"
    break;

  case 465:
#line 1578 "dhcp6_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 2671 "dhcp6_parser.cc"
    break;

  case 480:
#line 1611 "dhcp6_parser.yy"
                       {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2679 "dhcp6_parser.cc"
    break;

  case 481:
#line 1613 "dhcp6_parser.yy"
               {
    ElementPtr data(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2689 "dhcp6_parser.cc"
    break;

  case 484:
#line 1623 "dhcp6_parser.yy"
                                                 {
    ElementPtr space(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2698 "dhcp6_parser.cc"
    break;

  case 485:
#line 1628 "dhcp6_parser.yy"
                                                   {
    ElementPtr persist(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 2707 "dhcp6_parser.cc"
    break;

  case 486:
#line 1636 "dhcp6_parser.yy"
                  {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2718 "dhcp6_parser.cc"
    break;

  case 487:
#line 1641 "dhcp6_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2727 "dhcp6_parser.cc"
    break;

  case 492:
#line 1656 "dhcp6_parser.yy"
                                {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2737 "dhcp6_parser.cc"
    break;

  case 493:
#line 1660 "dhcp6_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2747 "dhcp6_parser.cc"
    break;

  case 494:
#line 1666 "dhcp6_parser.yy"
                          {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2757 "dhcp6_parser.cc"
    break;

  case 495:
#line 1670 "dhcp6_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
}
#line 2766 "dhcp6_parser.cc"
    break;

  case 505:
#line 1688 "dhcp6_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2774 "dhcp6_parser.cc"
    break;

  case 506:
#line 1690 "dhcp6_parser.yy"
               {
    ElementPtr pool(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2784 "dhcp6_parser.cc"
    break;

  case 507:
#line 1696 "dhcp6_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2792 "dhcp6_parser.cc"
    break;

  case 508:
#line 1698 "dhcp6_parser.yy"
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
#line 2819 "dhcp6_parser.cc"
    break;

  case 509:
#line 1721 "dhcp6_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2827 "dhcp6_parser.cc"
    break;

  case 510:
#line 1723 "dhcp6_parser.yy"
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
#line 2856 "dhcp6_parser.cc"
    break;

  case 511:
#line 1751 "dhcp6_parser.yy"
                        {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.PD_POOLS);
}
#line 2867 "dhcp6_parser.cc"
    break;

  case 512:
#line 1756 "dhcp6_parser.yy"
                                                              {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2876 "dhcp6_parser.cc"
    break;

  case 517:
#line 1771 "dhcp6_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2886 "dhcp6_parser.cc"
    break;

  case 518:
#line 1775 "dhcp6_parser.yy"
                                {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2898 "dhcp6_parser.cc"
    break;

  case 519:
#line 1783 "dhcp6_parser.yy"
                            {
    // Parse the pd-pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2908 "dhcp6_parser.cc"
    break;

  case 520:
#line 1787 "dhcp6_parser.yy"
                                {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2920 "dhcp6_parser.cc"
    break;

  case 534:
#line 1812 "dhcp6_parser.yy"
                  {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2928 "dhcp6_parser.cc"
    break;

  case 535:
#line 1814 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix", prf);
    ctx.leave();
}
#line 2938 "dhcp6_parser.cc"
    break;

  case 536:
#line 1820 "dhcp6_parser.yy"
                                        {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix-len", prf);
}
#line 2947 "dhcp6_parser.cc"
    break;

  case 537:
#line 1825 "dhcp6_parser.yy"
                                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2955 "dhcp6_parser.cc"
    break;

  case 538:
#line 1827 "dhcp6_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix", prf);
    ctx.leave();
}
#line 2965 "dhcp6_parser.cc"
    break;

  case 539:
#line 1833 "dhcp6_parser.yy"
                                                       {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix-len", prf);
}
#line 2974 "dhcp6_parser.cc"
    break;

  case 540:
#line 1838 "dhcp6_parser.yy"
                                              {
    ElementPtr deleg(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("delegated-len", deleg);
}
#line 2983 "dhcp6_parser.cc"
    break;

  case 541:
#line 1846 "dhcp6_parser.yy"
                           {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 2994 "dhcp6_parser.cc"
    break;

  case 542:
#line 1851 "dhcp6_parser.yy"
                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3003 "dhcp6_parser.cc"
    break;

  case 547:
#line 1864 "dhcp6_parser.yy"
                            {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3013 "dhcp6_parser.cc"
    break;

  case 548:
#line 1868 "dhcp6_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 3022 "dhcp6_parser.cc"
    break;

  case 549:
#line 1873 "dhcp6_parser.yy"
                                {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3032 "dhcp6_parser.cc"
    break;

  case 550:
#line 1877 "dhcp6_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 3041 "dhcp6_parser.cc"
    break;

  case 566:
#line 1904 "dhcp6_parser.yy"
                           {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3052 "dhcp6_parser.cc"
    break;

  case 567:
#line 1909 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3061 "dhcp6_parser.cc"
    break;

  case 568:
#line 1914 "dhcp6_parser.yy"
                    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3072 "dhcp6_parser.cc"
    break;

  case 569:
#line 1919 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3081 "dhcp6_parser.cc"
    break;

  case 570:
#line 1924 "dhcp6_parser.yy"
           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3089 "dhcp6_parser.cc"
    break;

  case 571:
#line 1926 "dhcp6_parser.yy"
               {
    ElementPtr d(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 3099 "dhcp6_parser.cc"
    break;

  case 572:
#line 1932 "dhcp6_parser.yy"
                       {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3107 "dhcp6_parser.cc"
    break;

  case 573:
#line 1934 "dhcp6_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 3117 "dhcp6_parser.cc"
    break;

  case 574:
#line 1940 "dhcp6_parser.yy"
                   {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3125 "dhcp6_parser.cc"
    break;

  case 575:
#line 1942 "dhcp6_parser.yy"
               {
    ElementPtr host(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 3135 "dhcp6_parser.cc"
    break;

  case 576:
#line 1948 "dhcp6_parser.yy"
                       {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3143 "dhcp6_parser.cc"
    break;

  case 577:
#line 1950 "dhcp6_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 3153 "dhcp6_parser.cc"
    break;

  case 578:
#line 1956 "dhcp6_parser.yy"
                                           {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3164 "dhcp6_parser.cc"
    break;

  case 579:
#line 1961 "dhcp6_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3173 "dhcp6_parser.cc"
    break;

  case 580:
#line 1969 "dhcp6_parser.yy"
             {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 3184 "dhcp6_parser.cc"
    break;

  case 581:
#line 1974 "dhcp6_parser.yy"
                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3193 "dhcp6_parser.cc"
    break;

  case 584:
#line 1983 "dhcp6_parser.yy"
                       {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3201 "dhcp6_parser.cc"
    break;

  case 585:
#line 1985 "dhcp6_parser.yy"
               {
    ElementPtr addr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 3211 "dhcp6_parser.cc"
    break;

  case 586:
#line 1994 "dhcp6_parser.yy"
                               {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 3222 "dhcp6_parser.cc"
    break;

  case 587:
#line 1999 "dhcp6_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3231 "dhcp6_parser.cc"
    break;

  case 590:
#line 2008 "dhcp6_parser.yy"
                                   {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3241 "dhcp6_parser.cc"
    break;

  case 591:
#line 2012 "dhcp6_parser.yy"
                                     {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3251 "dhcp6_parser.cc"
    break;

  case 604:
#line 2037 "dhcp6_parser.yy"
                        {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3259 "dhcp6_parser.cc"
    break;

  case 605:
#line 2039 "dhcp6_parser.yy"
               {
    ElementPtr test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 3269 "dhcp6_parser.cc"
    break;

  case 606:
#line 2045 "dhcp6_parser.yy"
                                                 {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 3278 "dhcp6_parser.cc"
    break;

  case 607:
#line 2053 "dhcp6_parser.yy"
                     {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-id", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER_ID);
}
#line 3289 "dhcp6_parser.cc"
    break;

  case 608:
#line 2058 "dhcp6_parser.yy"
                                                       {
    // The type parameter is required.
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3300 "dhcp6_parser.cc"
    break;

  case 620:
#line 2080 "dhcp6_parser.yy"
                     {
    ctx.enter(ctx.DUID_TYPE);
}
#line 3308 "dhcp6_parser.cc"
    break;

  case 621:
#line 2082 "dhcp6_parser.yy"
                  {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3317 "dhcp6_parser.cc"
    break;

  case 622:
#line 2087 "dhcp6_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("LLT", ctx.loc2pos(yystack_[0].location))); }
#line 3323 "dhcp6_parser.cc"
    break;

  case 623:
#line 2088 "dhcp6_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("EN", ctx.loc2pos(yystack_[0].location))); }
#line 3329 "dhcp6_parser.cc"
    break;

  case 624:
#line 2089 "dhcp6_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("LL", ctx.loc2pos(yystack_[0].location))); }
#line 3335 "dhcp6_parser.cc"
    break;

  case 625:
#line 2092 "dhcp6_parser.yy"
                           {
    ElementPtr htype(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("htype", htype);
}
#line 3344 "dhcp6_parser.cc"
    break;

  case 626:
#line 2097 "dhcp6_parser.yy"
                       {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3352 "dhcp6_parser.cc"
    break;

  case 627:
#line 2099 "dhcp6_parser.yy"
               {
    ElementPtr id(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("identifier", id);
    ctx.leave();
}
#line 3362 "dhcp6_parser.cc"
    break;

  case 628:
#line 2105 "dhcp6_parser.yy"
                         {
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("time", time);
}
#line 3371 "dhcp6_parser.cc"
    break;

  case 629:
#line 2110 "dhcp6_parser.yy"
                                           {
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enterprise-id", time);
}
#line 3380 "dhcp6_parser.cc"
    break;

  case 630:
#line 2117 "dhcp6_parser.yy"
                                         {
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 3389 "dhcp6_parser.cc"
    break;

  case 631:
#line 2124 "dhcp6_parser.yy"
                               {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 3400 "dhcp6_parser.cc"
    break;

  case 632:
#line 2129 "dhcp6_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3409 "dhcp6_parser.cc"
    break;

  case 640:
#line 2145 "dhcp6_parser.yy"
                         {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3417 "dhcp6_parser.cc"
    break;

  case 641:
#line 2147 "dhcp6_parser.yy"
               {
    ElementPtr stype(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 3427 "dhcp6_parser.cc"
    break;

  case 642:
#line 2153 "dhcp6_parser.yy"
                         {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3435 "dhcp6_parser.cc"
    break;

  case 643:
#line 2155 "dhcp6_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 3445 "dhcp6_parser.cc"
    break;

  case 644:
#line 2163 "dhcp6_parser.yy"
                                       {
    ElementPtr qc(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-queue-control", qc);
    ctx.stack_.push_back(qc);
    ctx.enter(ctx.DHCP_QUEUE_CONTROL);
}
#line 3456 "dhcp6_parser.cc"
    break;

  case 645:
#line 2168 "dhcp6_parser.yy"
                                                           {
    // The enable queue parameter is required.
    ctx.require("enable-queue", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3467 "dhcp6_parser.cc"
    break;

  case 654:
#line 2187 "dhcp6_parser.yy"
                                         {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-queue", b);
}
#line 3476 "dhcp6_parser.cc"
    break;

  case 655:
#line 2192 "dhcp6_parser.yy"
                       {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3484 "dhcp6_parser.cc"
    break;

  case 656:
#line 2194 "dhcp6_parser.yy"
               {
    ElementPtr qt(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("queue-type", qt);
    ctx.leave();
}
#line 3494 "dhcp6_parser.cc"
    break;

  case 657:
#line 2200 "dhcp6_parser.yy"
                                 {
    ElementPtr c(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("capacity", c);
}
#line 3503 "dhcp6_parser.cc"
    break;

  case 658:
#line 2205 "dhcp6_parser.yy"
                            {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3511 "dhcp6_parser.cc"
    break;

  case 659:
#line 2207 "dhcp6_parser.yy"
              {
    ctx.stack_.back()->set(yystack_[3].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3520 "dhcp6_parser.cc"
    break;

  case 660:
#line 2214 "dhcp6_parser.yy"
                     {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 3531 "dhcp6_parser.cc"
    break;

  case 661:
#line 2219 "dhcp6_parser.yy"
                                                       {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3542 "dhcp6_parser.cc"
    break;

  case 662:
#line 2226 "dhcp6_parser.yy"
                              {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3552 "dhcp6_parser.cc"
    break;

  case 663:
#line 2230 "dhcp6_parser.yy"
                                  {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3562 "dhcp6_parser.cc"
    break;

  case 684:
#line 2260 "dhcp6_parser.yy"
                                             {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 3571 "dhcp6_parser.cc"
    break;

  case 685:
#line 2265 "dhcp6_parser.yy"
                                     {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3579 "dhcp6_parser.cc"
    break;

  case 686:
#line 2267 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 3589 "dhcp6_parser.cc"
    break;

  case 687:
#line 2273 "dhcp6_parser.yy"
                     {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3597 "dhcp6_parser.cc"
    break;

  case 688:
#line 2275 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 3607 "dhcp6_parser.cc"
    break;

  case 689:
#line 2281 "dhcp6_parser.yy"
                                       {
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 3616 "dhcp6_parser.cc"
    break;

  case 690:
#line 2286 "dhcp6_parser.yy"
                     {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3624 "dhcp6_parser.cc"
    break;

  case 691:
#line 2288 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 3634 "dhcp6_parser.cc"
    break;

  case 692:
#line 2294 "dhcp6_parser.yy"
                                       {
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 3643 "dhcp6_parser.cc"
    break;

  case 693:
#line 2299 "dhcp6_parser.yy"
                                             {
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 3652 "dhcp6_parser.cc"
    break;

  case 694:
#line 2304 "dhcp6_parser.yy"
                           {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 3660 "dhcp6_parser.cc"
    break;

  case 695:
#line 2306 "dhcp6_parser.yy"
                           {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3669 "dhcp6_parser.cc"
    break;

  case 696:
#line 2312 "dhcp6_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 3675 "dhcp6_parser.cc"
    break;

  case 697:
#line 2313 "dhcp6_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 3681 "dhcp6_parser.cc"
    break;

  case 698:
#line 2316 "dhcp6_parser.yy"
                       {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 3689 "dhcp6_parser.cc"
    break;

  case 699:
#line 2318 "dhcp6_parser.yy"
             {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 3699 "dhcp6_parser.cc"
    break;

  case 700:
#line 2325 "dhcp6_parser.yy"
                                                         {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 3708 "dhcp6_parser.cc"
    break;

  case 701:
#line 2331 "dhcp6_parser.yy"
                                                                 {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 3717 "dhcp6_parser.cc"
    break;

  case 702:
#line 2337 "dhcp6_parser.yy"
                                             {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 3725 "dhcp6_parser.cc"
    break;

  case 703:
#line 2339 "dhcp6_parser.yy"
                                       {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3734 "dhcp6_parser.cc"
    break;

  case 704:
#line 2345 "dhcp6_parser.yy"
                                       {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3742 "dhcp6_parser.cc"
    break;

  case 705:
#line 2347 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 3752 "dhcp6_parser.cc"
    break;

  case 706:
#line 2354 "dhcp6_parser.yy"
                                         {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3760 "dhcp6_parser.cc"
    break;

  case 707:
#line 2356 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 3770 "dhcp6_parser.cc"
    break;

  case 708:
#line 2363 "dhcp6_parser.yy"
                                                         {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3778 "dhcp6_parser.cc"
    break;

  case 709:
#line 2365 "dhcp6_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 3788 "dhcp6_parser.cc"
    break;

  case 710:
#line 2373 "dhcp6_parser.yy"
                         {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3796 "dhcp6_parser.cc"
    break;

  case 711:
#line 2375 "dhcp6_parser.yy"
              {
    ctx.stack_.back()->set("Dhcp4", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3805 "dhcp6_parser.cc"
    break;

  case 712:
#line 2380 "dhcp6_parser.yy"
                               {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3813 "dhcp6_parser.cc"
    break;

  case 713:
#line 2382 "dhcp6_parser.yy"
              {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3822 "dhcp6_parser.cc"
    break;

  case 714:
#line 2387 "dhcp6_parser.yy"
                                         {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3830 "dhcp6_parser.cc"
    break;

  case 715:
#line 2389 "dhcp6_parser.yy"
              {
    ctx.stack_.back()->set("Control-agent", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3839 "dhcp6_parser.cc"
    break;

  case 716:
#line 2396 "dhcp6_parser.yy"
                               {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 3850 "dhcp6_parser.cc"
    break;

  case 717:
#line 2401 "dhcp6_parser.yy"
                                                            {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3860 "dhcp6_parser.cc"
    break;

  case 718:
#line 2407 "dhcp6_parser.yy"
                                   {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3870 "dhcp6_parser.cc"
    break;

  case 719:
#line 2411 "dhcp6_parser.yy"
                                       {
    // No config_control params are required
    // parsing completed
}
#line 3879 "dhcp6_parser.cc"
    break;

  case 724:
#line 2426 "dhcp6_parser.yy"
                                   {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 3890 "dhcp6_parser.cc"
    break;

  case 725:
#line 2431 "dhcp6_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3899 "dhcp6_parser.cc"
    break;

  case 726:
#line 2436 "dhcp6_parser.yy"
                                                             {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-fetch-wait-time", value);
}
#line 3908 "dhcp6_parser.cc"
    break;

  case 727:
#line 2446 "dhcp6_parser.yy"
                        {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 3919 "dhcp6_parser.cc"
    break;

  case 728:
#line 2451 "dhcp6_parser.yy"
                                                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3928 "dhcp6_parser.cc"
    break;

  case 729:
#line 2456 "dhcp6_parser.yy"
                            {
    // Parse the Logging map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3938 "dhcp6_parser.cc"
    break;

  case 730:
#line 2460 "dhcp6_parser.yy"
                                {
    // parsing completed
}
#line 3946 "dhcp6_parser.cc"
    break;

  case 734:
#line 2476 "dhcp6_parser.yy"
                 {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 3957 "dhcp6_parser.cc"
    break;

  case 735:
#line 2481 "dhcp6_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3966 "dhcp6_parser.cc"
    break;

  case 738:
#line 2493 "dhcp6_parser.yy"
                             {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 3976 "dhcp6_parser.cc"
    break;

  case 739:
#line 2497 "dhcp6_parser.yy"
                               {
    ctx.stack_.pop_back();
}
#line 3984 "dhcp6_parser.cc"
    break;

  case 749:
#line 2514 "dhcp6_parser.yy"
                                     {
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 3993 "dhcp6_parser.cc"
    break;

  case 750:
#line 2519 "dhcp6_parser.yy"
                   {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4001 "dhcp6_parser.cc"
    break;

  case 751:
#line 2521 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 4011 "dhcp6_parser.cc"
    break;

  case 752:
#line 2527 "dhcp6_parser.yy"
                                    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 4022 "dhcp6_parser.cc"
    break;

  case 753:
#line 2532 "dhcp6_parser.yy"
                                                                    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4031 "dhcp6_parser.cc"
    break;

  case 756:
#line 2541 "dhcp6_parser.yy"
                             {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4041 "dhcp6_parser.cc"
    break;

  case 757:
#line 2545 "dhcp6_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 4049 "dhcp6_parser.cc"
    break;

  case 765:
#line 2560 "dhcp6_parser.yy"
               {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4057 "dhcp6_parser.cc"
    break;

  case 766:
#line 2562 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 4067 "dhcp6_parser.cc"
    break;

  case 767:
#line 2568 "dhcp6_parser.yy"
                           {
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 4076 "dhcp6_parser.cc"
    break;

  case 768:
#line 2573 "dhcp6_parser.yy"
                               {
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 4085 "dhcp6_parser.cc"
    break;

  case 769:
#line 2578 "dhcp6_parser.yy"
                             {
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 4094 "dhcp6_parser.cc"
    break;

  case 770:
#line 2583 "dhcp6_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4102 "dhcp6_parser.cc"
    break;

  case 771:
#line 2585 "dhcp6_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pattern", sev);
    ctx.leave();
}
#line 4112 "dhcp6_parser.cc"
    break;


#line 4116 "dhcp6_parser.cc"

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
      YY_STACK_PRINT ();

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
        error (yyla.location, yysyntax_error_ (yystack_[0].state, yyla));
      }


    yyerror_range[1].location = yyla.location;
    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.type_get () == yyeof_)
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
    goto yyerrlab1;


  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    {
      stack_symbol_type error_token;
      for (;;)
        {
          yyn = yypact_[+yystack_[0].state];
          if (!yy_pact_value_is_default_ (yyn))
            {
              yyn += yy_error_token_;
              if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yy_error_token_)
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

  // Generate an error message.
  std::string
  Dhcp6Parser::yysyntax_error_ (state_type yystate, const symbol_type& yyla) const
  {
    // Number of reported tokens (one for the "unexpected", one per
    // "expected").
    std::ptrdiff_t yycount = 0;
    // Its maximum.
    enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
    // Arguments of yyformat.
    char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];

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
    if (!yyla.empty ())
      {
        symbol_number_type yytoken = yyla.type_get ();
        yyarg[yycount++] = yytname_[yytoken];

        int yyn = yypact_[+yystate];
        if (!yy_pact_value_is_default_ (yyn))
          {
            /* Start YYX at -YYN if negative to avoid negative indexes in
               YYCHECK.  In other words, skip the first -YYN actions for
               this state because they are default actions.  */
            int yyxbegin = yyn < 0 ? -yyn : 0;
            // Stay within bounds of both yycheck and yytname.
            int yychecklim = yylast_ - yyn + 1;
            int yyxend = yychecklim < yyntokens_ ? yychecklim : yyntokens_;
            for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
              if (yycheck_[yyx + yyn] == yyx && yyx != yy_error_token_
                  && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
                {
                  if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                    {
                      yycount = 1;
                      break;
                    }
                  else
                    yyarg[yycount++] = yytname_[yyx];
                }
          }
      }

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
          yyres += yytnamerr_ (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const short Dhcp6Parser::yypact_ninf_ = -945;

  const signed char Dhcp6Parser::yytable_ninf_ = -1;

  const short
  Dhcp6Parser::yypact_[] =
  {
     452,  -945,  -945,  -945,  -945,  -945,  -945,  -945,  -945,  -945,
    -945,  -945,  -945,  -945,  -945,  -945,    66,    31,    73,    76,
      95,   160,   166,   168,   175,   177,   186,   196,   262,   280,
     286,   297,  -945,  -945,  -945,  -945,  -945,  -945,  -945,  -945,
    -945,  -945,  -945,  -945,  -945,  -945,  -945,  -945,  -945,  -945,
    -945,  -945,  -945,  -945,  -945,  -945,  -945,  -945,  -945,  -945,
    -945,  -945,  -945,  -945,  -945,  -945,  -945,  -945,  -945,  -945,
    -945,  -945,    31,  -149,    29,   199,    28,   514,   126,    75,
      77,    27,    20,   260,   -41,   538,   -15,    46,  -945,   269,
     274,   279,   298,   316,  -945,  -945,  -945,  -945,  -945,   322,
    -945,    49,  -945,  -945,  -945,  -945,  -945,  -945,  -945,  -945,
    -945,  -945,  -945,  -945,   324,   340,   365,   366,   419,   427,
     429,   432,   442,   443,   445,   455,  -945,   456,   463,   466,
     470,   471,  -945,  -945,  -945,   472,  -945,  -945,  -945,  -945,
    -945,  -945,  -945,  -945,  -945,  -945,  -945,  -945,  -945,  -945,
    -945,  -945,   477,  -945,  -945,  -945,  -945,  -945,  -945,  -945,
     101,  -945,  -945,  -945,  -945,  -945,  -945,  -945,  -945,  -945,
    -945,  -945,  -945,  -945,  -945,  -945,  -945,  -945,  -945,  -945,
    -945,  -945,  -945,  -945,  -945,  -945,  -945,  -945,  -945,  -945,
    -945,  -945,  -945,  -945,  -945,  -945,  -945,  -945,  -945,  -945,
    -945,  -945,  -945,  -945,  -945,  -945,  -945,  -945,  -945,  -945,
    -945,  -945,  -945,  -945,   479,  -945,   109,  -945,  -945,  -945,
    -945,  -945,  -945,  -945,  -945,  -945,  -945,   481,   482,  -945,
    -945,  -945,  -945,  -945,  -945,  -945,  -945,  -945,  -945,  -945,
    -945,  -945,  -945,  -945,  -945,  -945,  -945,  -945,  -945,  -945,
    -945,  -945,  -945,   143,  -945,  -945,  -945,  -945,  -945,  -945,
    -945,  -945,  -945,  -945,  -945,  -945,  -945,  -945,  -945,  -945,
    -945,  -945,  -945,  -945,  -945,   147,  -945,  -945,  -945,  -945,
    -945,   486,  -945,   487,   491,  -945,  -945,  -945,  -945,  -945,
    -945,   171,  -945,  -945,  -945,  -945,  -945,  -945,  -945,  -945,
    -945,  -945,  -945,  -945,  -945,  -945,  -945,  -945,  -945,   330,
     359,  -945,  -945,  -945,  -945,  -945,  -945,  -945,  -945,   393,
    -945,  -945,   494,  -945,  -945,  -945,   501,  -945,  -945,   403,
     503,  -945,  -945,  -945,  -945,  -945,  -945,  -945,  -945,  -945,
    -945,  -945,  -945,  -945,   504,   505,  -945,  -945,  -945,  -945,
     499,   507,  -945,  -945,  -945,  -945,  -945,  -945,  -945,  -945,
    -945,  -945,  -945,  -945,   194,  -945,  -945,  -945,   508,  -945,
    -945,   513,  -945,   516,   517,  -945,  -945,   519,   520,  -945,
    -945,  -945,  -945,  -945,  -945,  -945,   201,  -945,  -945,  -945,
    -945,  -945,  -945,  -945,  -945,  -945,  -945,  -945,  -945,  -945,
    -945,  -945,  -945,   213,  -945,  -945,  -945,   521,   217,  -945,
    -945,  -945,  -945,    31,    31,  -945,   331,   525,   526,   528,
     529,   532,  -945,    29,  -945,   533,   534,   536,   537,   539,
     540,   353,   354,   355,   356,   357,   373,   374,   375,   313,
     383,   384,   376,   541,   387,   388,   389,   390,   391,   542,
     543,   544,   392,   550,   581,   582,   587,   589,   591,   592,
     593,   594,   595,   605,   606,   608,   609,   610,   612,   422,
     613,   616,   617,   622,   623,   624,   199,  -945,   625,   449,
      28,  -945,   646,   648,   649,   651,   652,   461,   460,   655,
     656,   657,   514,  -945,   658,   126,  -945,   659,   473,   664,
     474,   475,    75,  -945,   668,   669,   670,   671,   673,   674,
     678,  -945,    77,  -945,   692,   693,   502,   695,   696,   697,
     509,  -945,    20,   698,   510,   512,  -945,   260,   701,   702,
     122,  -945,   515,   707,   708,   522,   715,   524,   527,   717,
     718,   530,   531,   720,   721,   722,   723,   538,  -945,   -15,
    -945,   726,   535,    46,  -945,  -945,  -945,   728,   727,   729,
      31,    31,    31,  -945,   545,   730,   731,   732,   734,   737,
    -945,  -945,  -945,  -945,  -945,  -945,  -945,  -945,  -945,  -945,
    -945,  -945,   548,  -945,  -945,  -945,  -945,  -945,   -99,   549,
     551,  -945,   740,   742,   743,   744,   554,   288,   745,   747,
     748,   749,   750,   751,   753,   754,   755,   756,  -945,   757,
     758,   759,   560,   565,   762,  -945,   763,  -945,  -945,   764,
     765,   566,   576,   577,  -945,  -945,   763,   578,   767,  -945,
     580,  -945,   583,  -945,   584,  -945,  -945,  -945,   763,   763,
     763,   585,   586,   588,   590,  -945,   596,   597,  -945,   598,
     599,   600,  -945,  -945,   601,  -945,  -945,  -945,   602,    31,
    -945,  -945,   603,   604,  -945,   607,  -945,  -945,   157,   575,
    -945,  -945,   -99,   611,   614,   615,  -945,  -945,   771,  -945,
    -945,    31,   199,   -15,  -945,  -945,  -945,  -945,    46,    28,
      99,    99,   770,  -945,  -945,  -945,  -945,  -945,  -945,  -945,
    -945,  -945,   775,   777,   779,  -945,  -945,  -945,  -945,  -945,
    -945,  -945,  -945,   780,   -51,    31,   367,   685,   782,   783,
     793,   187,    37,   202,    35,   538,  -945,  -945,   794,  -945,
    -945,   796,   797,  -945,  -945,  -945,  -945,  -945,   -68,  -945,
    -945,  -945,  -945,  -945,  -945,  -945,  -945,  -945,  -945,  -945,
    -945,  -945,  -945,  -945,  -945,  -945,  -945,  -945,  -945,  -945,
    -945,  -945,  -945,  -945,  -945,  -945,  -945,  -945,   770,  -945,
     268,   270,   276,   287,  -945,  -945,  -945,  -945,   801,   803,
     804,   807,   808,  -945,   809,   810,  -945,  -945,  -945,   811,
     812,   813,   814,  -945,   315,  -945,  -945,  -945,  -945,  -945,
    -945,  -945,  -945,  -945,  -945,  -945,  -945,  -945,  -945,  -945,
    -945,  -945,  -945,  -945,  -945,  -945,   334,  -945,   815,   816,
    -945,  -945,   817,   819,  -945,  -945,   818,   822,  -945,  -945,
     820,   824,  -945,  -945,   823,   825,  -945,  -945,  -945,    70,
    -945,  -945,  -945,   826,  -945,  -945,  -945,    87,  -945,  -945,
    -945,  -945,   342,  -945,  -945,  -945,   102,  -945,  -945,   827,
     828,  -945,  -945,   829,   831,  -945,   832,   833,   834,   835,
     836,   837,   348,  -945,  -945,  -945,  -945,  -945,  -945,  -945,
    -945,  -945,   838,   839,   840,  -945,  -945,  -945,  -945,   349,
    -945,  -945,  -945,  -945,  -945,  -945,  -945,  -945,  -945,  -945,
    -945,   350,  -945,  -945,  -945,   841,  -945,   842,  -945,  -945,
    -945,   351,  -945,  -945,  -945,  -945,  -945,   352,  -945,   146,
    -945,   635,  -945,   843,   844,  -945,  -945,   845,   847,  -945,
    -945,  -945,   846,  -945,   849,  -945,  -945,  -945,  -945,   848,
     852,   853,   854,   663,   650,   665,   662,   666,   859,   672,
     675,   860,   861,   862,   676,   677,   679,   680,    99,  -945,
    -945,    99,  -945,   770,   514,  -945,   775,    20,  -945,   777,
     260,  -945,   779,   327,  -945,   780,   -51,  -945,  -945,   367,
    -945,   863,   685,  -945,    79,   782,  -945,    77,  -945,   783,
     -41,  -945,   793,   682,   683,   684,   686,   687,   688,   187,
    -945,   865,   866,   689,   690,   691,    37,  -945,   870,   871,
     202,  -945,   694,   877,   699,   884,    35,  -945,  -945,   153,
     794,  -945,  -945,   883,   850,   126,  -945,   796,    75,  -945,
     797,   887,  -945,  -945,   417,   703,   710,   713,  -945,  -945,
    -945,  -945,  -945,   719,  -945,  -945,   724,   725,   733,  -945,
    -945,  -945,  -945,  -945,   358,  -945,   360,  -945,   889,  -945,
     895,  -945,  -945,  -945,  -945,  -945,  -945,  -945,  -945,  -945,
    -945,  -945,  -945,  -945,  -945,  -945,  -945,  -945,  -945,  -945,
    -945,  -945,  -945,  -945,  -945,  -945,  -945,  -945,  -945,  -945,
    -945,   395,  -945,  -945,  -945,  -945,  -945,  -945,  -945,  -945,
     746,  -945,  -945,   917,  -945,  -945,  -945,  -945,  -945,   915,
     922,  -945,  -945,  -945,  -945,  -945,   919,  -945,   396,  -945,
    -945,  -945,  -945,  -945,  -945,  -945,  -945,   296,   760,  -945,
    -945,  -945,  -945,   769,   791,  -945,  -945,   798,  -945,    31,
    -945,  -945,   938,  -945,  -945,  -945,  -945,  -945,   397,  -945,
    -945,  -945,  -945,  -945,  -945,   800,   404,  -945,   407,  -945,
     821,  -945,  -945,  -945,  -945,  -945,  -945,  -945,  -945,  -945,
    -945,  -945,  -945,  -945,  -945,  -945,  -945,   327,  -945,  -945,
     946,   768,  -945,    79,  -945,  -945,  -945,  -945,  -945,  -945,
    -945,  -945,  -945,  -945,  -945,   953,   795,   985,   153,  -945,
    -945,  -945,  -945,  -945,  -945,   830,  -945,  -945,   987,  -945,
     851,  -945,  -945,   999,  -945,  -945,   299,  -945,    25,   999,
    -945,  -945,  1003,  1006,  1010,  -945,   421,  -945,  -945,  -945,
    -945,  -945,  -945,  -945,  1011,   855,   856,   858,  1014,    25,
    -945,   864,  -945,  -945,  -945,   867,  -945,  -945,  -945
  };

  const short
  Dhcp6Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,    28,    30,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     1,    47,    40,    36,    35,    32,    33,    34,
      39,     3,    37,    38,    60,     5,    72,     7,   167,     9,
     316,    11,   494,    13,   519,    15,   549,    17,   419,    19,
     427,    21,   464,    23,   281,    25,   662,    27,   729,    29,
     718,    31,    49,    43,     0,     0,     0,     0,     0,     0,
     551,     0,   429,   466,     0,     0,     0,     0,    51,     0,
      50,     0,     0,    44,    70,   727,   710,   712,   714,     0,
      69,     0,    62,    64,    66,    67,    68,    65,   128,   716,
     165,   179,   181,   183,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   163,     0,     0,     0,
       0,     0,   145,   152,   154,     0,   308,   417,   456,   507,
     509,   366,   374,   254,   271,   262,   247,   586,   541,   273,
     292,   607,     0,   631,   644,   660,   156,   158,   734,   127,
       0,    74,    76,    77,    78,    79,    80,    81,    82,    83,
      84,   112,   113,   114,    85,   118,   119,   120,   121,   122,
     123,   116,   117,   124,   125,   126,   110,    88,    89,    90,
      91,   107,    92,    94,    93,    98,    99,    86,   111,    87,
      96,    97,   105,   106,   108,    95,   100,   101,   102,   103,
     104,   109,   115,   176,     0,   175,     0,   169,   171,   172,
     173,   174,   486,   511,   356,   358,   360,     0,     0,   364,
     362,   580,   355,   320,   321,   322,   323,   324,   325,   326,
     327,   343,   344,   345,   348,   349,   350,   351,   352,   353,
     346,   347,   354,     0,   318,   331,   332,   333,   336,   337,
     339,   334,   335,   328,   329,   341,   342,   330,   338,   340,
     505,   504,   500,   501,   499,     0,   496,   498,   502,   503,
     534,     0,   537,     0,     0,   533,   527,   528,   526,   531,
     532,     0,   521,   523,   524,   529,   530,   525,   578,   566,
     568,   570,   572,   574,   576,   565,   562,   563,   564,     0,
     552,   553,   557,   558,   555,   559,   560,   561,   556,     0,
     446,   227,     0,   450,   448,   453,     0,   442,   443,     0,
     430,   431,   433,   445,   434,   435,   436,   452,   437,   438,
     439,   440,   441,   480,     0,     0,   478,   479,   482,   483,
       0,   467,   468,   470,   471,   472,   473,   474,   475,   476,
     477,   288,   290,   285,     0,   283,   286,   287,     0,   685,
     687,     0,   690,     0,     0,   694,   698,     0,     0,   702,
     704,   706,   708,   683,   681,   682,     0,   664,   666,   667,
     668,   669,   670,   671,   672,   673,   674,   675,   676,   677,
     678,   679,   680,     0,   731,   733,   724,     0,     0,   720,
     722,   723,    48,     0,     0,    41,     0,     0,     0,     0,
       0,     0,    59,     0,    61,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    73,     0,     0,
       0,   168,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   317,     0,     0,   495,     0,     0,     0,
       0,     0,     0,   520,     0,     0,     0,     0,     0,     0,
       0,   550,     0,   420,     0,     0,     0,     0,     0,     0,
       0,   428,     0,     0,     0,     0,   465,     0,     0,     0,
       0,   282,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   663,     0,
     730,     0,     0,     0,   719,    52,    45,     0,     0,     0,
       0,     0,     0,    63,     0,     0,     0,     0,     0,     0,
     130,   131,   132,   133,   134,   135,   136,   137,   138,   139,
     140,   141,     0,   161,   162,   142,   143,   144,     0,     0,
       0,   160,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   630,     0,
       0,     0,     0,     0,     0,    75,     0,   178,   170,     0,
       0,     0,     0,     0,   372,   373,     0,     0,     0,   319,
       0,   497,     0,   536,     0,   539,   540,   522,     0,     0,
       0,     0,     0,     0,     0,   554,     0,     0,   444,     0,
       0,     0,   455,   432,     0,   484,   485,   469,     0,     0,
     284,   684,     0,     0,   689,     0,   692,   693,     0,     0,
     700,   701,     0,     0,     0,     0,   665,   732,     0,   726,
     721,     0,     0,     0,   711,   713,   715,   129,     0,     0,
       0,     0,   185,   164,   147,   148,   149,   150,   151,   146,
     153,   155,   310,   421,   458,    42,   508,   510,   368,   369,
     370,   371,   367,   376,     0,    49,     0,     0,     0,   543,
     275,     0,     0,     0,     0,     0,   157,   159,     0,    53,
     177,   488,   513,   357,   359,   361,   365,   363,     0,   506,
     535,   538,   579,   567,   569,   571,   573,   575,   577,   447,
     228,   451,   449,   454,   481,   289,   291,   686,   688,   691,
     696,   697,   695,   699,   703,   705,   707,   709,   185,    46,
       0,     0,     0,     0,   214,   220,   222,   224,     0,     0,
       0,     0,     0,   238,     0,     0,   241,   243,   245,     0,
       0,     0,     0,   213,     0,   191,   193,   194,   195,   196,
     197,   198,   199,   200,   201,   202,   205,   212,   206,   207,
     208,   203,   204,   209,   210,   211,     0,   189,     0,   186,
     187,   314,     0,   311,   312,   425,     0,   422,   423,   462,
       0,   459,   460,   380,     0,   377,   378,   260,   261,     0,
     256,   258,   259,     0,   269,   270,   266,     0,   264,   267,
     268,   252,     0,   249,   251,   590,     0,   588,   547,     0,
     544,   545,   279,     0,   276,   277,     0,     0,     0,     0,
       0,     0,     0,   294,   296,   297,   298,   299,   300,   301,
     620,   626,     0,     0,     0,   619,   616,   617,   618,     0,
     609,   611,   614,   612,   613,   615,   640,   642,   639,   637,
     638,     0,   633,   635,   636,     0,   655,     0,   658,   651,
     652,     0,   646,   648,   649,   650,   653,     0,   738,     0,
     736,    55,   492,     0,   489,   490,   517,     0,   514,   515,
     584,   583,     0,   582,     0,    71,   728,   717,   166,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   180,
     182,     0,   184,     0,     0,   309,     0,   429,   418,     0,
     466,   457,     0,     0,   375,     0,     0,   255,   272,     0,
     263,     0,     0,   248,   592,     0,   587,   551,   542,     0,
       0,   274,     0,     0,     0,     0,     0,     0,     0,     0,
     293,     0,     0,     0,     0,     0,     0,   608,     0,     0,
       0,   632,     0,     0,     0,     0,     0,   645,   661,     0,
       0,   735,    57,     0,    56,     0,   487,     0,     0,   512,
       0,     0,   581,   725,     0,     0,     0,     0,   226,   229,
     230,   231,   232,     0,   240,   233,     0,     0,     0,   235,
     236,   237,   234,   192,     0,   188,     0,   313,     0,   424,
       0,   461,   416,   395,   396,   397,   399,   400,   401,   388,
     389,   404,   405,   406,   409,   410,   411,   412,   413,   414,
     407,   408,   415,   384,   385,   386,   387,   393,   394,   392,
     398,     0,   382,   390,   402,   403,   391,   379,   257,   265,
       0,   250,   604,     0,   602,   603,   599,   600,   601,     0,
     593,   594,   596,   597,   598,   589,     0,   546,     0,   278,
     302,   303,   304,   305,   306,   307,   295,     0,     0,   625,
     628,   629,   610,     0,     0,   634,   654,     0,   657,     0,
     647,   752,     0,   750,   748,   742,   746,   747,     0,   740,
     744,   745,   743,   737,    54,     0,     0,   491,     0,   516,
       0,   216,   217,   218,   219,   215,   221,   223,   225,   239,
     242,   244,   246,   190,   315,   426,   463,     0,   381,   253,
       0,     0,   591,     0,   548,   280,   622,   623,   624,   621,
     627,   641,   643,   656,   659,     0,     0,     0,     0,   739,
      58,   493,   518,   585,   383,     0,   606,   595,     0,   749,
       0,   741,   605,     0,   751,   756,     0,   754,     0,     0,
     753,   765,     0,     0,     0,   770,     0,   758,   760,   761,
     762,   763,   764,   755,     0,     0,     0,     0,     0,     0,
     757,     0,   767,   768,   769,     0,   759,   766,   771
  };

  const short
  Dhcp6Parser::yypgoto_[] =
  {
    -945,  -945,  -945,  -945,  -945,  -945,  -945,  -945,  -945,  -945,
    -945,  -945,  -945,  -945,  -945,  -945,  -945,    -5,  -945,   225,
    -945,  -945,  -945,  -945,  -945,  -945,   304,  -945,  -358,  -945,
    -945,  -945,   -74,  -945,  -945,  -945,   618,  -945,  -945,  -945,
    -945,   339,   546,  -945,  -945,   -62,   -42,   -40,   -34,   -30,
     -29,   -27,   -26,     4,     5,     7,  -945,     8,     9,    10,
      11,  -945,   361,    21,  -945,    23,  -945,    24,  -945,    26,
    -945,    36,  -945,  -945,  -945,  -945,  -945,  -945,  -945,  -945,
     335,   547,  -945,  -945,  -945,  -945,  -945,  -945,  -945,  -945,
    -945,   255,  -945,    63,  -945,  -665,    71,  -945,  -945,  -945,
    -945,  -945,  -945,  -945,  -945,  -945,  -945,   -66,  -945,  -699,
    -945,  -945,  -945,  -945,  -945,  -945,  -945,  -945,  -945,  -945,
    -945,  -945,  -945,  -945,  -945,  -945,  -945,  -945,  -945,  -945,
      48,  -945,  -945,  -945,  -945,  -945,    52,  -688,  -945,  -945,
    -945,  -945,    53,  -945,  -945,  -945,  -945,  -945,  -945,  -945,
    -945,    42,  -945,  -945,  -945,    41,   506,  -945,  -945,  -945,
    -945,  -945,  -945,  -945,    38,  -945,  -945,  -945,  -945,  -945,
    -945,  -944,  -945,  -945,  -945,    69,  -945,  -945,  -945,    74,
     552,  -945,  -945,  -942,  -945,  -941,  -945,    32,  -945,    40,
    -945,    39,  -945,  -945,  -945,  -940,  -945,  -945,  -945,  -945,
      64,  -945,  -945,  -137,   961,  -945,  -945,  -945,  -945,  -945,
      78,  -945,  -945,  -945,    81,  -945,   523,  -945,   -76,  -945,
    -945,  -945,  -945,  -945,   -70,  -945,  -945,  -945,  -945,  -945,
     -24,  -945,  -945,  -945,    83,  -945,  -945,  -945,    80,  -945,
     553,  -945,  -945,  -945,  -945,  -945,  -945,  -945,  -945,  -945,
    -945,  -945,    16,  -945,  -945,  -945,    33,   556,  -945,  -945,
     -58,  -945,    -8,  -945,  -945,  -945,  -945,  -945,    19,  -945,
    -945,  -945,    43,   559,  -945,  -945,  -945,  -945,  -945,  -945,
    -945,   -47,  -945,  -945,  -945,    67,  -945,  -945,  -945,    82,
    -945,   555,   325,  -945,  -945,  -945,  -945,  -945,  -945,  -945,
    -945,  -945,  -945,  -945,  -945,  -945,  -939,  -945,  -945,  -945,
    -945,  -945,  -945,  -945,    85,  -945,  -945,  -945,  -119,  -945,
    -945,  -945,  -945,  -945,  -945,  -945,    60,  -945,  -945,  -945,
    -945,  -945,  -945,  -945,  -945,  -945,  -945,  -945,  -945,    62,
    -945,  -945,  -945,  -945,  -945,  -945,  -945,    57,  -945,  -945,
    -945,  -945,  -945,  -945,  -945,  -945,  -945,  -945,   362,   557,
    -945,  -945,  -945,  -945,  -945,  -945,  -945,  -945,  -945,  -945,
    -945,  -945,  -945,  -945,  -945,  -945,  -945,  -945,  -945,  -945,
    -945,  -945,  -945,  -945,  -945,  -945,  -945,  -945,  -945,  -945,
    -945,  -945,  -945,  -945,  -945,   386,   561,  -945,  -945,  -945,
    -945,  -945,  -945,  -945,   394,   558,   -72,  -945,  -945,    55,
    -945,  -945,  -122,  -945,  -945,  -945,  -945,  -945,  -945,  -141,
    -945,  -945,  -160,  -945,  -945,  -945,  -945,  -945,  -945,  -945
  };

  const short
  Dhcp6Parser::yydefgoto_[] =
  {
      -1,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    88,    41,    42,
      73,   706,    92,    93,    43,    72,    89,    90,   730,   921,
    1023,  1024,   793,    45,    74,   101,   102,   103,   417,    47,
      75,   160,   161,   162,   425,   163,   164,   165,   166,   167,
     168,   169,   170,   171,   172,   173,   174,   175,   176,   177,
     178,   449,   699,   179,   450,   180,   451,   181,   473,   182,
     474,   183,   184,   185,   186,   443,   187,   427,    49,    76,
     216,   217,   218,   478,   219,   188,   428,   189,   429,   190,
     430,   818,   819,   820,   961,   794,   795,   796,   939,  1165,
     797,   940,   798,   941,   799,   942,   800,   801,   515,   802,
     803,   804,   805,   806,   807,   808,   809,   810,   811,   948,
     812,   813,   951,   814,   952,   815,   953,   191,   463,   852,
     853,   854,   981,   192,   460,   839,   840,   841,   842,   193,
     462,   847,   848,   849,   850,   194,   461,   195,   466,   863,
     864,   865,   990,    65,    84,   364,   365,   366,   528,   367,
     529,   196,   467,   872,   873,   874,   875,   876,   877,   878,
     879,   197,   453,   822,   823,   824,   964,    51,    77,   253,
     254,   255,   484,   256,   485,   257,   486,   258,   490,   259,
     489,   198,   458,   712,   261,   262,   199,   459,   834,   835,
     836,   973,  1091,  1092,   200,   454,    59,    81,   826,   827,
     828,   967,    61,    82,   329,   330,   331,   332,   333,   334,
     335,   514,   336,   518,   337,   517,   338,   339,   519,   340,
     201,   455,   830,   831,   832,   970,    63,    83,   350,   351,
     352,   353,   354,   523,   355,   356,   357,   358,   264,   482,
     923,   924,   925,  1025,    53,    78,   275,   276,   277,   494,
     202,   456,   203,   457,   267,   483,   927,   928,   929,  1028,
      55,    79,   291,   292,   293,   497,   294,   295,   499,   296,
     297,   204,   465,   859,   860,   861,   987,    57,    80,   309,
     310,   311,   312,   505,   313,   506,   314,   507,   315,   508,
     316,   509,   317,   510,   318,   504,   269,   491,   932,   933,
    1031,   205,   464,   856,   857,   984,  1109,  1110,  1111,  1112,
    1113,  1180,  1114,   206,   468,   889,   890,   891,  1001,  1189,
     892,   893,  1002,   894,   895,   207,   208,   470,   901,   902,
     903,  1008,   904,  1009,   209,   471,   911,   912,   913,   914,
    1013,   915,   916,  1015,   210,   472,    67,    85,   386,   387,
     388,   389,   533,   390,   534,   391,   392,   536,   393,   394,
     395,   539,   762,   396,   540,   397,   398,   399,   543,   400,
     544,   401,   545,   402,   546,   104,   419,   105,   420,   106,
     421,   211,   426,    71,    87,   408,   409,   410,   551,   411,
     107,   418,    69,    86,   403,   404,   212,   475,   919,   920,
    1019,  1148,  1149,  1150,  1151,  1197,  1152,  1195,  1216,  1217,
    1218,  1226,  1227,  1228,  1234,  1229,  1230,  1231,  1232,  1238
  };

  const short
  Dhcp6Parser::yytable_[] =
  {
     100,   159,   215,   232,   271,   285,   305,   348,   327,   346,
     363,   383,    40,   349,   405,   233,   328,   347,   220,   265,
     278,   289,   307,   886,   341,   359,   816,   384,   846,  1084,
     268,  1085,  1086,  1090,  1096,   234,    33,   235,    34,    94,
      35,   320,   299,   236,   213,   214,    91,   237,   238,   930,
     239,   240,   423,   263,   274,   288,   306,   424,   880,   406,
     407,   837,   694,   695,   696,   697,    32,   779,   221,   266,
     279,   290,   308,   976,   342,   360,   977,   385,   361,   362,
      44,   241,   242,    46,   243,   244,   245,   246,   247,   321,
     979,   322,   323,   980,   137,   324,   325,   326,   248,   698,
     249,   250,    48,   251,   476,   985,   139,   140,   986,   477,
     272,   286,   480,   252,   139,   140,   260,   481,   273,   287,
     774,   139,   140,   139,   140,   775,   776,   777,   778,   779,
     780,   781,   782,   783,   784,   785,   786,   787,   788,   789,
     790,   791,   792,   138,   838,   138,   492,   138,   321,  1020,
     495,   493,  1021,   158,    99,   496,   280,   281,   282,   283,
     284,   139,   140,   139,   140,   139,   140,    50,   321,   881,
     882,   883,   884,    52,   502,    54,   905,   906,   907,   503,
     229,   298,    56,   230,    58,  1102,  1103,   299,   300,   301,
     302,   303,   304,    60,   138,  1221,    95,   530,  1222,  1223,
    1224,  1225,   531,    62,   547,   270,    96,    97,    98,   548,
     108,   109,   139,   140,   110,    99,   549,   111,   112,   113,
     553,   550,   321,    99,    99,   554,    36,    37,    38,    39,
     908,   229,    99,  1084,   230,  1085,  1086,  1090,  1096,   139,
     140,   361,   362,   114,   115,   116,   117,   118,   119,   120,
     121,   122,   123,   124,   125,   126,   127,   128,   129,   130,
     131,   132,   133,   134,   135,   136,   137,   138,   736,    64,
      99,   476,    99,   549,    99,   412,   935,   413,   936,   553,
     742,   743,   744,   414,   937,   139,   140,    66,   139,   140,
     480,   846,   141,    68,    99,   938,  1054,   142,   143,   144,
     145,   146,  1219,   147,    70,  1220,   415,   886,   148,   866,
     867,   868,   869,   870,   871,   760,   761,   149,   958,   416,
     150,    99,  1141,   959,  1142,  1143,   422,   151,   431,   321,
     343,   322,   323,   344,   345,   152,   153,   958,   511,   154,
     896,   897,   960,   155,   432,   982,   139,   140,    99,   100,
     983,   999,  1006,  1010,  1016,   547,  1000,  1007,  1011,  1017,
    1018,   958,   512,   492,   156,   157,  1173,   158,  1174,   433,
     434,   114,   115,   116,   117,   118,   119,   120,   121,   122,
     123,   124,   708,   709,   710,   711,   129,   130,   131,   132,
     133,   134,   135,   136,    99,   138,   321,    99,  1177,   530,
    1198,   513,   159,  1178,  1185,  1199,   215,   495,   555,   556,
     502,   521,  1201,   139,   140,  1202,   225,   226,   232,   228,
     141,   271,   220,   435,  1239,  1186,  1187,  1188,   285,  1240,
     233,   436,   229,   437,   265,   230,   438,   278,   305,  1161,
    1162,  1163,  1164,   231,   289,   268,   439,   440,   327,   441,
     234,   348,   235,   346,   307,    99,   328,   349,   236,   442,
     444,   347,   237,   238,   341,   239,   240,   445,   263,   359,
     446,   274,   221,   383,   447,   448,   452,   405,   288,   837,
     844,   469,   845,   479,   266,   487,   488,   279,   306,   384,
     498,   500,   156,   157,   290,   501,   241,   242,   516,   243,
     244,   245,   246,   247,   308,   520,   522,   526,   524,   525,
     527,   578,   532,   248,   342,   249,   250,   535,   251,   360,
     537,   538,    99,   541,   542,   552,   557,   272,   252,   558,
     559,   260,   560,   561,   286,   273,   562,   564,   565,   385,
     566,   567,   287,   568,   569,   582,   588,   589,   590,   570,
     571,   572,   573,   574,   592,   684,   685,   686,   114,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   575,
     576,   577,   581,   129,   130,   131,   132,   133,   134,   135,
     579,   580,   138,   583,   584,   593,   594,   585,   586,   587,
     591,   595,   222,   596,   223,   597,   598,   599,   600,   601,
     139,   140,   224,   225,   226,   227,   228,   141,   159,   602,
     603,   405,   604,   605,   606,   215,   607,   609,   608,   229,
     610,   611,   230,   148,   139,   140,   612,   613,   614,   616,
     231,   220,     1,     2,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,    15,   617,   885,   898,
     619,   383,   620,   621,   756,   622,   623,   624,   625,   626,
     627,   628,   630,   632,   887,   899,   909,   384,   634,   633,
     635,   636,   638,   639,   640,   641,   769,   642,   643,   156,
     157,   221,   644,   368,   369,   370,   371,   372,   373,   374,
     375,   376,   377,   378,   379,   380,   646,   647,   648,   649,
     650,   651,   654,   381,   382,   658,   659,   652,   655,    99,
     656,   662,   663,   661,   888,   900,   910,   385,   664,   665,
     666,   668,   669,   667,   672,   673,   674,   675,   670,   671,
     678,   679,   681,    99,   682,   763,   683,   688,   689,   690,
     687,   691,   692,   693,   700,   702,   701,   703,   704,   707,
     713,    34,   714,   715,   716,   726,   718,   717,   719,   720,
     727,   733,   721,   722,   723,   724,   725,   728,   729,   731,
     732,   734,   735,   737,   738,   739,   768,   817,   740,   741,
     745,   746,   821,   747,   825,   748,   829,   833,   851,   855,
     858,   749,   750,   751,   752,   753,   754,   755,   757,   758,
     862,   918,   759,   922,   926,   943,   765,   944,   945,   766,
     767,   946,   947,   949,   950,   954,   955,   956,   957,   963,
     705,   962,   966,   965,   968,   969,   971,   972,   975,   974,
    1022,   989,   978,   988,   992,   991,   993,   994,   995,   996,
     997,   998,  1003,  1004,  1005,  1012,  1014,  1027,  1039,  1026,
    1030,  1029,  1034,  1155,  1032,  1033,  1035,  1036,  1037,  1038,
    1041,  1040,  1042,  1043,  1046,  1047,  1048,  1100,  1044,  1127,
    1128,  1045,  1049,  1050,  1133,  1134,  1052,  1051,  1120,  1121,
    1122,  1137,  1123,  1124,  1125,  1129,  1130,  1131,  1139,  1154,
     232,  1160,  1136,   327,   348,  1138,   346,  1175,  1166,  1062,
     349,   328,   233,  1176,   347,  1167,   265,  1083,  1168,   341,
    1104,  1063,   359,   305,  1169,  1094,   363,   268,  1105,  1170,
    1171,  1181,   234,  1182,   235,  1183,  1107,  1184,  1172,   307,
     236,  1064,   885,  1065,   237,   238,   898,   239,   240,  1066,
     263,  1179,  1196,  1067,  1068,  1144,  1069,  1070,   887,  1093,
    1205,   271,   899,  1145,   285,  1190,   266,  1208,   909,   342,
    1106,  1146,   360,   306,  1191,  1095,  1206,   278,   241,   242,
     289,   243,   244,   245,   246,   247,  1108,  1071,  1072,   308,
    1073,  1074,  1075,  1076,  1077,   248,  1192,   249,   250,  1210,
     251,  1209,  1213,  1193,  1078,  1200,  1079,  1080,   888,  1081,
     252,   274,   900,   260,   288,  1087,  1215,  1235,   910,  1082,
    1236,  1147,  1089,  1088,  1237,  1241,  1203,   279,  1245,   843,
     290,   770,   615,   934,   773,  1212,  1055,   618,  1098,  1053,
    1101,  1118,  1099,   764,  1119,  1057,   660,  1126,  1056,  1097,
    1204,   563,   319,  1157,   629,   653,  1214,  1059,  1058,  1159,
    1060,   631,  1243,  1242,  1244,  1061,  1117,   272,  1156,  1247,
     286,   637,  1248,   931,  1207,   273,  1132,   645,   287,  1116,
    1115,  1158,  1135,  1140,   772,  1153,  1211,   771,  1233,  1246,
     657,     0,     0,     0,     0,     0,     0,   917,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  1062,   676,     0,     0,   677,     0,  1104,
       0,  1083,     0,     0,   680,  1063,     0,  1105,     0,  1094,
       0,     0,     0,     0,  1144,  1107,     0,     0,     0,     0,
       0,     0,  1145,     0,  1194,  1064,     0,  1065,     0,     0,
    1146,     0,     0,  1066,     0,     0,     0,  1067,  1068,     0,
    1069,  1070,     0,  1093,     0,     0,     0,     0,     0,  1106,
       0,     0,     0,     0,     0,     0,     0,     0,     0,  1095,
       0,     0,     0,     0,     0,  1108,     0,     0,     0,     0,
       0,  1071,  1072,     0,  1073,  1074,  1075,  1076,  1077,     0,
    1147,     0,     0,     0,     0,     0,     0,     0,  1078,     0,
    1079,  1080,     0,  1081,     0,     0,     0,     0,     0,  1087,
       0,     0,     0,  1082,     0,     0,  1089,  1088
  };

  const short
  Dhcp6Parser::yycheck_[] =
  {
      74,    75,    76,    77,    78,    79,    80,    83,    82,    83,
      84,    85,    17,    83,    86,    77,    82,    83,    76,    77,
      78,    79,    80,   722,    82,    83,   691,    85,   716,   973,
      77,   973,   973,   973,   973,    77,     5,    77,     7,    10,
       9,    21,   110,    77,    16,    17,   195,    77,    77,   117,
      77,    77,     3,    77,    78,    79,    80,     8,    21,    13,
      14,   112,   161,   162,   163,   164,     0,    30,    76,    77,
      78,    79,    80,     3,    82,    83,     6,    85,   119,   120,
       7,    77,    77,     7,    77,    77,    77,    77,    77,    69,
       3,    71,    72,     6,    67,    75,    76,    77,    77,   198,
      77,    77,     7,    77,     3,     3,    86,    87,     6,     8,
      78,    79,     3,    77,    86,    87,    77,     8,    78,    79,
      21,    86,    87,    86,    87,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,    68,   195,    68,     3,    68,    69,     3,
       3,     8,     6,   168,   195,     8,    81,    82,    83,    84,
      85,    86,    87,    86,    87,    86,    87,     7,    69,   132,
     133,   134,   135,     7,     3,     7,   141,   142,   143,     8,
     105,   104,     7,   108,     7,   106,   107,   110,   111,   112,
     113,   114,   115,     7,    68,   170,   167,     3,   173,   174,
     175,   176,     8,     7,     3,    79,   177,   178,   179,     8,
      11,    12,    86,    87,    15,   195,     3,    18,    19,    20,
       3,     8,    69,   195,   195,     8,   195,   196,   197,   198,
     195,   105,   195,  1177,   108,  1177,  1177,  1177,  1177,    86,
      87,   119,   120,    44,    45,    46,    47,    48,    49,    50,
      51,    52,    53,    54,    55,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,   626,     7,
     195,     3,   195,     3,   195,     6,     8,     3,     8,     3,
     638,   639,   640,     4,     8,    86,    87,     7,    86,    87,
       3,   979,    93,     7,   195,     8,   961,    98,    99,   100,
     101,   102,     3,   104,     7,     6,     8,  1006,   109,   122,
     123,   124,   125,   126,   127,   158,   159,   118,     3,     3,
     121,   195,   169,     8,   171,   172,     4,   128,     4,    69,
      70,    71,    72,    73,    74,   136,   137,     3,     8,   140,
     138,   139,     8,   144,     4,     3,    86,    87,   195,   423,
       8,     3,     3,     3,     3,     3,     8,     8,     8,     8,
       8,     3,     3,     3,   165,   166,     8,   168,     8,     4,
       4,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    94,    95,    96,    97,    59,    60,    61,    62,
      63,    64,    65,    66,   195,    68,    69,   195,     3,     3,
       3,     8,   476,     8,     8,     8,   480,     3,   413,   414,
       3,     8,     8,    86,    87,     8,    89,    90,   492,    92,
      93,   495,   480,     4,     3,   129,   130,   131,   502,     8,
     492,     4,   105,     4,   492,   108,     4,   495,   512,    22,
      23,    24,    25,   116,   502,   492,     4,     4,   522,     4,
     492,   527,   492,   527,   512,   195,   522,   527,   492,     4,
       4,   527,   492,   492,   522,   492,   492,     4,   492,   527,
       4,   495,   480,   547,     4,     4,     4,   549,   502,   112,
     113,     4,   115,     4,   492,     4,     4,   495,   512,   547,
       4,     4,   165,   166,   502,     4,   492,   492,     4,   492,
     492,   492,   492,   492,   512,     4,     3,     8,     4,     4,
       3,   198,     4,   492,   522,   492,   492,     4,   492,   527,
       4,     4,   195,     4,     4,     4,   195,   495,   492,     4,
       4,   492,     4,     4,   502,   495,     4,     4,     4,   547,
       4,     4,   502,     4,     4,     4,     4,     4,     4,   196,
     196,   196,   196,   196,     4,   560,   561,   562,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,   196,
     196,   196,   196,    59,    60,    61,    62,    63,    64,    65,
     197,   197,    68,   196,   196,     4,     4,   198,   198,   198,
     198,     4,    78,     4,    80,     4,     4,     4,     4,     4,
      86,    87,    88,    89,    90,    91,    92,    93,   682,     4,
       4,   683,     4,     4,     4,   689,     4,     4,   196,   105,
       4,     4,   108,   109,    86,    87,     4,     4,     4,     4,
     116,   689,   180,   181,   182,   183,   184,   185,   186,   187,
     188,   189,   190,   191,   192,   193,   194,   198,   722,   723,
       4,   725,     4,     4,   659,     4,     4,   196,   198,     4,
       4,     4,     4,     4,   722,   723,   724,   725,     4,   196,
     196,   196,     4,     4,     4,     4,   681,     4,     4,   165,
     166,   689,     4,   145,   146,   147,   148,   149,   150,   151,
     152,   153,   154,   155,   156,   157,     4,     4,   196,     4,
       4,     4,     4,   165,   166,     4,     4,   198,   198,   195,
     198,     4,     4,   198,   722,   723,   724,   725,   196,     4,
     196,     4,     4,   196,     4,     4,     4,     4,   198,   198,
       4,   196,     4,   195,     7,   160,     7,     7,     7,     7,
     195,     7,     5,   195,   195,     5,   195,     5,     5,   195,
       5,     7,     5,     5,     5,   195,     5,     7,     5,     5,
     195,   195,     7,     7,     7,     7,     7,     5,     5,     5,
       5,   195,   195,   195,     7,   195,     5,     7,   195,   195,
     195,   195,     7,   195,     7,   195,     7,     7,   103,     7,
       7,   195,   195,   195,   195,   195,   195,   195,   195,   195,
       7,     7,   195,     7,     7,     4,   195,     4,     4,   195,
     195,     4,     4,     4,     4,     4,     4,     4,     4,     3,
     595,     6,     3,     6,     6,     3,     6,     3,     3,     6,
     195,     3,     6,     6,     3,     6,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     3,   198,     6,
       3,     6,     4,     3,     8,     6,     4,     4,     4,   196,
     198,   196,   196,     4,     4,     4,     4,     4,   196,     4,
       4,   196,   196,   196,     4,     4,   196,   198,   196,   196,
     196,     4,   196,   196,   196,   196,   196,   196,     4,     6,
     964,     4,   198,   967,   970,   196,   970,     8,   195,   973,
     970,   967,   964,     8,   970,   195,   964,   973,   195,   967,
     984,   973,   970,   987,   195,   973,   990,   964,   984,   195,
     195,     4,   964,     8,   964,     3,   984,     8,   195,   987,
     964,   973,  1006,   973,   964,   964,  1010,   964,   964,   973,
     964,   195,     4,   973,   973,  1019,   973,   973,  1006,   973,
       4,  1025,  1010,  1019,  1028,   195,   964,     4,  1016,   967,
     984,  1019,   970,   987,   195,   973,   198,  1025,   964,   964,
    1028,   964,   964,   964,   964,   964,   984,   973,   973,   987,
     973,   973,   973,   973,   973,   964,   195,   964,   964,     4,
     964,   196,     5,   195,   973,   195,   973,   973,  1006,   973,
     964,  1025,  1010,   964,  1028,   973,     7,     4,  1016,   973,
       4,  1019,   973,   973,     4,     4,   195,  1025,     4,   715,
    1028,   682,   476,   768,   689,   195,   963,   480,   976,   958,
     982,   990,   979,   672,   992,   966,   530,   999,   964,   975,
    1177,   423,    81,  1027,   492,   522,   195,   969,   967,  1030,
     970,   495,   196,   198,   196,   972,   989,  1025,  1025,   195,
    1028,   502,   195,   738,  1183,  1025,  1006,   512,  1028,   987,
     985,  1028,  1010,  1016,   688,  1020,  1198,   683,  1219,  1239,
     527,    -1,    -1,    -1,    -1,    -1,    -1,   725,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,  1177,   547,    -1,    -1,   549,    -1,  1183,
      -1,  1177,    -1,    -1,   553,  1177,    -1,  1183,    -1,  1177,
      -1,    -1,    -1,    -1,  1198,  1183,    -1,    -1,    -1,    -1,
      -1,    -1,  1198,    -1,  1139,  1177,    -1,  1177,    -1,    -1,
    1198,    -1,    -1,  1177,    -1,    -1,    -1,  1177,  1177,    -1,
    1177,  1177,    -1,  1177,    -1,    -1,    -1,    -1,    -1,  1183,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1177,
      -1,    -1,    -1,    -1,    -1,  1183,    -1,    -1,    -1,    -1,
      -1,  1177,  1177,    -1,  1177,  1177,  1177,  1177,  1177,    -1,
    1198,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1177,    -1,
    1177,  1177,    -1,  1177,    -1,    -1,    -1,    -1,    -1,  1177,
      -1,    -1,    -1,  1177,    -1,    -1,  1177,  1177
  };

  const short
  Dhcp6Parser::yystos_[] =
  {
       0,   180,   181,   182,   183,   184,   185,   186,   187,   188,
     189,   190,   191,   192,   193,   194,   200,   201,   202,   203,
     204,   205,   206,   207,   208,   209,   210,   211,   212,   213,
     214,   215,     0,     5,     7,     9,   195,   196,   197,   198,
     216,   217,   218,   223,     7,   232,     7,   238,     7,   277,
       7,   376,     7,   453,     7,   469,     7,   486,     7,   405,
       7,   411,     7,   435,     7,   352,     7,   555,     7,   601,
       7,   592,   224,   219,   233,   239,   278,   377,   454,   470,
     487,   406,   412,   436,   353,   556,   602,   593,   216,   225,
     226,   195,   221,   222,    10,   167,   177,   178,   179,   195,
     231,   234,   235,   236,   584,   586,   588,   599,    11,    12,
      15,    18,    19,    20,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    86,
      87,    93,    98,    99,   100,   101,   102,   104,   109,   118,
     121,   128,   136,   137,   140,   144,   165,   166,   168,   231,
     240,   241,   242,   244,   245,   246,   247,   248,   249,   250,
     251,   252,   253,   254,   255,   256,   257,   258,   259,   262,
     264,   266,   268,   270,   271,   272,   273,   275,   284,   286,
     288,   326,   332,   338,   344,   346,   360,   370,   390,   395,
     403,   429,   459,   461,   480,   510,   522,   534,   535,   543,
     553,   590,   605,    16,    17,   231,   279,   280,   281,   283,
     459,   461,    78,    80,    88,    89,    90,    91,    92,   105,
     108,   116,   231,   244,   245,   246,   247,   248,   249,   250,
     251,   252,   253,   254,   256,   257,   258,   259,   262,   264,
     266,   268,   270,   378,   379,   380,   382,   384,   386,   388,
     390,   393,   394,   429,   447,   459,   461,   463,   480,   505,
      79,   231,   386,   388,   429,   455,   456,   457,   459,   461,
      81,    82,    83,    84,    85,   231,   386,   388,   429,   459,
     461,   471,   472,   473,   475,   476,   478,   479,   104,   110,
     111,   112,   113,   114,   115,   231,   429,   459,   461,   488,
     489,   490,   491,   493,   495,   497,   499,   501,   503,   403,
      21,    69,    71,    72,    75,    76,    77,   231,   306,   413,
     414,   415,   416,   417,   418,   419,   421,   423,   425,   426,
     428,   459,   461,    70,    73,    74,   231,   306,   417,   423,
     437,   438,   439,   440,   441,   443,   444,   445,   446,   459,
     461,   119,   120,   231,   354,   355,   356,   358,   145,   146,
     147,   148,   149,   150,   151,   152,   153,   154,   155,   156,
     157,   165,   166,   231,   459,   461,   557,   558,   559,   560,
     562,   564,   565,   567,   568,   569,   572,   574,   575,   576,
     578,   580,   582,   603,   604,   605,    13,    14,   594,   595,
     596,   598,     6,     3,     4,     8,     3,   237,   600,   585,
     587,   589,     4,     3,     8,   243,   591,   276,   285,   287,
     289,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,   274,     4,     4,     4,     4,     4,   260,
     263,   265,     4,   371,   404,   430,   460,   462,   391,   396,
     333,   345,   339,   327,   511,   481,   347,   361,   523,     4,
     536,   544,   554,   267,   269,   606,     3,     8,   282,     4,
       3,     8,   448,   464,   381,   383,   385,     4,     4,   389,
     387,   506,     3,     8,   458,     3,     8,   474,     4,   477,
       4,     4,     3,     8,   504,   492,   494,   496,   498,   500,
     502,     8,     3,     8,   420,   307,     4,   424,   422,   427,
       4,     8,     3,   442,     4,     4,     8,     3,   357,   359,
       3,     8,     4,   561,   563,     4,   566,     4,     4,   570,
     573,     4,     4,   577,   579,   581,   583,     3,     8,     3,
       8,   597,     4,     3,     8,   216,   216,   195,     4,     4,
       4,     4,     4,   235,     4,     4,     4,     4,     4,     4,
     196,   196,   196,   196,   196,   196,   196,   196,   198,   197,
     197,   196,     4,   196,   196,   198,   198,   198,     4,     4,
       4,   198,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,   196,     4,
       4,     4,     4,     4,     4,   241,     4,   198,   280,     4,
       4,     4,     4,     4,   196,   198,     4,     4,     4,   379,
       4,   456,     4,   196,     4,   196,   196,   472,     4,     4,
       4,     4,     4,     4,     4,   490,     4,     4,   196,     4,
       4,     4,   198,   415,     4,   198,   198,   439,     4,     4,
     355,   198,     4,     4,   196,     4,   196,   196,     4,     4,
     198,   198,     4,     4,     4,     4,   558,   604,     4,   196,
     595,     4,     7,     7,   216,   216,   216,   195,     7,     7,
       7,     7,     5,   195,   161,   162,   163,   164,   198,   261,
     195,   195,     5,     5,     5,   218,   220,   195,    94,    95,
      96,    97,   392,     5,     5,     5,     5,     7,     5,     5,
       5,     7,     7,     7,     7,     7,   195,   195,     5,     5,
     227,     5,     5,   195,   195,   195,   227,   195,     7,   195,
     195,   195,   227,   227,   227,   195,   195,   195,   195,   195,
     195,   195,   195,   195,   195,   195,   216,   195,   195,   195,
     158,   159,   571,   160,   261,   195,   195,   195,     5,   216,
     240,   603,   594,   279,    21,    26,    27,    28,    29,    30,
      31,    32,    33,    34,    35,    36,    37,    38,    39,    40,
      41,    42,    43,   231,   294,   295,   296,   299,   301,   303,
     305,   306,   308,   309,   310,   311,   312,   313,   314,   315,
     316,   317,   319,   320,   322,   324,   294,     7,   290,   291,
     292,     7,   372,   373,   374,     7,   407,   408,   409,     7,
     431,   432,   433,     7,   397,   398,   399,   112,   195,   334,
     335,   336,   337,   225,   113,   115,   336,   340,   341,   342,
     343,   103,   328,   329,   330,     7,   512,   513,     7,   482,
     483,   484,     7,   348,   349,   350,   122,   123,   124,   125,
     126,   127,   362,   363,   364,   365,   366,   367,   368,   369,
      21,   132,   133,   134,   135,   231,   308,   459,   461,   524,
     525,   526,   529,   530,   532,   533,   138,   139,   231,   459,
     461,   537,   538,   539,   541,   141,   142,   143,   195,   459,
     461,   545,   546,   547,   548,   550,   551,   557,     7,   607,
     608,   228,     7,   449,   450,   451,     7,   465,   466,   467,
     117,   491,   507,   508,   290,     8,     8,     8,     8,   297,
     300,   302,   304,     4,     4,     4,     4,     4,   318,     4,
       4,   321,   323,   325,     4,     4,     4,     4,     3,     8,
       8,   293,     6,     3,   375,     6,     3,   410,     6,     3,
     434,     6,     3,   400,     6,     3,     3,     6,     6,     3,
       6,   331,     3,     8,   514,     3,     6,   485,     6,     3,
     351,     6,     3,     4,     4,     4,     4,     4,     4,     3,
       8,   527,   531,     4,     4,     4,     3,     8,   540,   542,
       3,     8,     4,   549,     4,   552,     3,     8,     8,   609,
       3,     6,   195,   229,   230,   452,     6,     3,   468,     6,
       3,   509,     8,     6,     4,     4,     4,     4,   196,   198,
     196,   198,   196,     4,   196,   196,     4,     4,     4,   196,
     196,   198,   196,   295,   294,   292,   378,   374,   413,   409,
     437,   433,   231,   244,   245,   246,   247,   248,   249,   250,
     251,   252,   253,   254,   256,   257,   258,   259,   262,   264,
     266,   268,   270,   306,   370,   382,   384,   386,   388,   390,
     394,   401,   402,   429,   459,   461,   505,   399,   335,   341,
       4,   329,   106,   107,   231,   306,   429,   459,   461,   515,
     516,   517,   518,   519,   521,   513,   488,   484,   354,   350,
     196,   196,   196,   196,   196,   196,   363,     4,     4,   196,
     196,   196,   525,     4,     4,   538,   198,     4,   196,     4,
     546,   169,   171,   172,   231,   306,   459,   461,   610,   611,
     612,   613,   615,   608,     6,     3,   455,   451,   471,   467,
       4,    22,    23,    24,    25,   298,   195,   195,   195,   195,
     195,   195,   195,     8,     8,     8,     8,     3,     8,   195,
     520,     4,     8,     3,     8,     8,   129,   130,   131,   528,
     195,   195,   195,   195,   216,   616,     4,   614,     3,     8,
     195,     8,     8,   195,   402,     4,   198,   517,     4,   196,
       4,   611,   195,     5,   195,     7,   617,   618,   619,     3,
       6,   170,   173,   174,   175,   176,   620,   621,   622,   624,
     625,   626,   627,   618,   623,     4,     4,     4,   628,     3,
       8,     4,   198,   196,   196,     4,   621,   195,   195
  };

  const short
  Dhcp6Parser::yyr1_[] =
  {
       0,   199,   201,   200,   202,   200,   203,   200,   204,   200,
     205,   200,   206,   200,   207,   200,   208,   200,   209,   200,
     210,   200,   211,   200,   212,   200,   213,   200,   214,   200,
     215,   200,   216,   216,   216,   216,   216,   216,   216,   217,
     219,   218,   220,   221,   221,   222,   222,   224,   223,   225,
     225,   226,   226,   228,   227,   229,   229,   230,   230,   231,
     233,   232,   234,   234,   235,   235,   235,   235,   235,   235,
     237,   236,   239,   238,   240,   240,   241,   241,   241,   241,
     241,   241,   241,   241,   241,   241,   241,   241,   241,   241,
     241,   241,   241,   241,   241,   241,   241,   241,   241,   241,
     241,   241,   241,   241,   241,   241,   241,   241,   241,   241,
     241,   241,   241,   241,   241,   241,   241,   241,   241,   241,
     241,   241,   241,   241,   241,   241,   241,   241,   243,   242,
     244,   245,   246,   247,   248,   249,   250,   251,   252,   253,
     254,   255,   256,   257,   258,   260,   259,   261,   261,   261,
     261,   261,   263,   262,   265,   264,   267,   266,   269,   268,
     270,   271,   272,   274,   273,   276,   275,   278,   277,   279,
     279,   280,   280,   280,   280,   280,   282,   281,   283,   285,
     284,   287,   286,   289,   288,   290,   290,   291,   291,   293,
     292,   294,   294,   295,   295,   295,   295,   295,   295,   295,
     295,   295,   295,   295,   295,   295,   295,   295,   295,   295,
     295,   295,   295,   295,   297,   296,   298,   298,   298,   298,
     300,   299,   302,   301,   304,   303,   305,   307,   306,   308,
     309,   310,   311,   312,   313,   314,   315,   316,   318,   317,
     319,   321,   320,   323,   322,   325,   324,   327,   326,   328,
     328,   329,   331,   330,   333,   332,   334,   334,   335,   335,
     336,   337,   339,   338,   340,   340,   341,   341,   341,   342,
     343,   345,   344,   347,   346,   348,   348,   349,   349,   351,
     350,   353,   352,   354,   354,   354,   355,   355,   357,   356,
     359,   358,   361,   360,   362,   362,   363,   363,   363,   363,
     363,   363,   364,   365,   366,   367,   368,   369,   371,   370,
     372,   372,   373,   373,   375,   374,   377,   376,   378,   378,
     379,   379,   379,   379,   379,   379,   379,   379,   379,   379,
     379,   379,   379,   379,   379,   379,   379,   379,   379,   379,
     379,   379,   379,   379,   379,   379,   379,   379,   379,   379,
     379,   379,   379,   379,   379,   379,   381,   380,   383,   382,
     385,   384,   387,   386,   389,   388,   391,   390,   392,   392,
     392,   392,   393,   394,   396,   395,   397,   397,   398,   398,
     400,   399,   401,   401,   402,   402,   402,   402,   402,   402,
     402,   402,   402,   402,   402,   402,   402,   402,   402,   402,
     402,   402,   402,   402,   402,   402,   402,   402,   402,   402,
     402,   402,   402,   402,   402,   402,   402,   404,   403,   406,
     405,   407,   407,   408,   408,   410,   409,   412,   411,   413,
     413,   414,   414,   415,   415,   415,   415,   415,   415,   415,
     415,   415,   415,   416,   417,   418,   420,   419,   422,   421,
     424,   423,   425,   427,   426,   428,   430,   429,   431,   431,
     432,   432,   434,   433,   436,   435,   437,   437,   438,   438,
     439,   439,   439,   439,   439,   439,   439,   439,   439,   440,
     442,   441,   443,   444,   445,   446,   448,   447,   449,   449,
     450,   450,   452,   451,   454,   453,   455,   455,   456,   456,
     456,   456,   456,   456,   456,   458,   457,   460,   459,   462,
     461,   464,   463,   465,   465,   466,   466,   468,   467,   470,
     469,   471,   471,   472,   472,   472,   472,   472,   472,   472,
     472,   472,   472,   472,   474,   473,   475,   477,   476,   478,
     479,   481,   480,   482,   482,   483,   483,   485,   484,   487,
     486,   488,   488,   489,   489,   490,   490,   490,   490,   490,
     490,   490,   490,   490,   490,   490,   492,   491,   494,   493,
     496,   495,   498,   497,   500,   499,   502,   501,   504,   503,
     506,   505,   507,   507,   509,   508,   511,   510,   512,   512,
     514,   513,   515,   515,   516,   516,   517,   517,   517,   517,
     517,   517,   517,   518,   520,   519,   521,   523,   522,   524,
     524,   525,   525,   525,   525,   525,   525,   525,   525,   525,
     527,   526,   528,   528,   528,   529,   531,   530,   532,   533,
     534,   536,   535,   537,   537,   538,   538,   538,   538,   538,
     540,   539,   542,   541,   544,   543,   545,   545,   546,   546,
     546,   546,   546,   546,   547,   549,   548,   550,   552,   551,
     554,   553,   556,   555,   557,   557,   558,   558,   558,   558,
     558,   558,   558,   558,   558,   558,   558,   558,   558,   558,
     558,   558,   558,   558,   559,   561,   560,   563,   562,   564,
     566,   565,   567,   568,   570,   569,   571,   571,   573,   572,
     574,   575,   577,   576,   579,   578,   581,   580,   583,   582,
     585,   584,   587,   586,   589,   588,   591,   590,   593,   592,
     594,   594,   595,   595,   597,   596,   598,   600,   599,   602,
     601,   603,   603,   604,   606,   605,   607,   607,   609,   608,
     610,   610,   611,   611,   611,   611,   611,   611,   611,   612,
     614,   613,   616,   615,   617,   617,   619,   618,   620,   620,
     621,   621,   621,   621,   621,   623,   622,   624,   625,   626,
     628,   627
  };

  const signed char
  Dhcp6Parser::yyr2_[] =
  {
       0,     2,     0,     3,     0,     3,     0,     3,     0,     3,
       0,     3,     0,     3,     0,     3,     0,     3,     0,     3,
       0,     3,     0,     3,     0,     3,     0,     3,     0,     3,
       0,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     1,     0,     1,     3,     5,     0,     4,     0,
       1,     1,     3,     0,     4,     0,     1,     1,     3,     2,
       0,     4,     1,     3,     1,     1,     1,     1,     1,     1,
       0,     6,     0,     4,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     0,     4,     1,     1,     1,
       1,     1,     0,     4,     0,     4,     0,     4,     0,     4,
       3,     3,     3,     0,     4,     0,     6,     0,     4,     1,
       3,     1,     1,     1,     1,     1,     0,     4,     3,     0,
       6,     0,     6,     0,     6,     0,     1,     1,     3,     0,
       4,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     1,     1,     1,     1,
       0,     4,     0,     4,     0,     4,     3,     0,     4,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     0,     4,
       3,     0,     4,     0,     4,     0,     4,     0,     6,     1,
       3,     1,     0,     4,     0,     6,     1,     3,     1,     1,
       1,     1,     0,     6,     1,     3,     1,     1,     1,     1,
       1,     0,     6,     0,     6,     0,     1,     1,     3,     0,
       4,     0,     4,     1,     3,     1,     1,     1,     0,     4,
       0,     4,     0,     6,     1,     3,     1,     1,     1,     1,
       1,     1,     3,     3,     3,     3,     3,     3,     0,     6,
       0,     1,     1,     3,     0,     4,     0,     4,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     1,     1,
       1,     1,     3,     3,     0,     6,     0,     1,     1,     3,
       0,     4,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     6,     0,
       4,     0,     1,     1,     3,     0,     4,     0,     4,     0,
       1,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     1,     0,     4,     0,     4,
       0,     4,     1,     0,     4,     3,     0,     6,     0,     1,
       1,     3,     0,     4,     0,     4,     0,     1,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     1,     1,     3,     3,     0,     6,     0,     1,
       1,     3,     0,     4,     0,     4,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     0,     4,     0,
       4,     0,     6,     0,     1,     1,     3,     0,     4,     0,
       4,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     3,     0,     4,     3,
       3,     0,     6,     0,     1,     1,     3,     0,     4,     0,
       4,     0,     1,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     6,     1,     1,     0,     4,     0,     6,     1,     3,
       0,     4,     0,     1,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     3,     0,     6,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     1,     1,     1,     3,     0,     4,     3,     3,
       3,     0,     6,     1,     3,     1,     1,     1,     1,     1,
       0,     4,     0,     4,     0,     6,     1,     3,     1,     1,
       1,     1,     1,     1,     3,     0,     4,     3,     0,     4,
       0,     6,     0,     4,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     0,     4,     0,     4,     3,
       0,     4,     3,     3,     0,     4,     1,     1,     0,     4,
       3,     3,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     6,     0,     4,
       1,     3,     1,     1,     0,     6,     3,     0,     6,     0,
       4,     1,     3,     1,     0,     6,     1,     3,     0,     4,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     3,
       0,     4,     0,     6,     1,     3,     0,     4,     1,     3,
       1,     1,     1,     1,     1,     0,     4,     3,     3,     3,
       0,     4
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const Dhcp6Parser::yytname_[] =
  {
  "\"end of file\"", "error", "$undefined", "\",\"", "\":\"", "\"[\"",
  "\"]\"", "\"{\"", "\"}\"", "\"null\"", "\"Dhcp6\"", "\"data-directory\"",
  "\"config-control\"", "\"config-databases\"",
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
  "\"dhcp4o6-port\"", "\"control-socket\"", "\"socket-type\"",
  "\"socket-name\"", "\"dhcp-queue-control\"", "\"enable-queue\"",
  "\"queue-type\"", "\"capacity\"", "\"dhcp-ddns\"", "\"enable-updates\"",
  "\"qualifying-suffix\"", "\"server-ip\"", "\"server-port\"",
  "\"sender-ip\"", "\"sender-port\"", "\"max-queue-size\"",
  "\"ncr-protocol\"", "\"ncr-format\"", "\"override-no-update\"",
  "\"override-client-update\"", "\"replace-client-name\"",
  "\"generated-prefix\"", "\"UDP\"", "\"TCP\"", "\"JSON\"",
  "\"when-present\"", "\"never\"", "\"always\"", "\"when-not-present\"",
  "\"hostname-char-set\"", "\"hostname-char-replacement\"", "\"Logging\"",
  "\"loggers\"", "\"output_options\"", "\"output\"", "\"debuglevel\"",
  "\"severity\"", "\"flush\"", "\"maxsize\"", "\"maxver\"", "\"pattern\"",
  "\"Dhcp4\"", "\"DhcpDdns\"", "\"Control-agent\"", "TOPLEVEL_JSON",
  "TOPLEVEL_DHCP6", "SUB_DHCP6", "SUB_INTERFACES6", "SUB_SUBNET6",
  "SUB_POOL6", "SUB_PD_POOL", "SUB_RESERVATION", "SUB_OPTION_DEFS",
  "SUB_OPTION_DEF", "SUB_OPTION_DATA", "SUB_HOOKS_LIBRARY",
  "SUB_DHCP_DDNS", "SUB_LOGGING", "SUB_CONFIG_CONTROL",
  "\"constant string\"", "\"integer\"", "\"floating point\"",
  "\"boolean\"", "$accept", "start", "$@1", "$@2", "$@3", "$@4", "$@5",
  "$@6", "$@7", "$@8", "$@9", "$@10", "$@11", "$@12", "$@13", "$@14",
  "$@15", "value", "sub_json", "map2", "$@16", "map_value", "map_content",
  "not_empty_map", "list_generic", "$@17", "list_content",
  "not_empty_list", "list_strings", "$@18", "list_strings_content",
  "not_empty_list_strings", "unknown_map_entry", "syntax_map", "$@19",
  "global_objects", "global_object", "dhcp6_object", "$@20", "sub_dhcp6",
  "$@21", "global_params", "global_param", "data_directory", "$@22",
  "preferred_lifetime", "min_preferred_lifetime", "max_preferred_lifetime",
  "valid_lifetime", "min_valid_lifetime", "max_valid_lifetime",
  "renew_timer", "rebind_timer", "calculate_tee_times", "t1_percent",
  "t2_percent", "decline_probation_period", "ddns_send_updates",
  "ddns_override_no_update", "ddns_override_client_update",
  "ddns_replace_client_name", "$@23", "ddns_replace_client_name_value",
  "ddns_generated_prefix", "$@24", "ddns_qualifying_suffix", "$@25",
  "hostname_char_set", "$@26", "hostname_char_replacement", "$@27",
  "store_extended_info", "statistic_default_sample_count",
  "statistic_default_sample_age", "server_tag", "$@28",
  "interfaces_config", "$@29", "sub_interfaces6", "$@30",
  "interfaces_config_params", "interfaces_config_param", "interfaces_list",
  "$@31", "re_detect", "lease_database", "$@32", "hosts_database", "$@33",
  "hosts_databases", "$@34", "database_list", "not_empty_database_list",
  "database", "$@35", "database_map_params", "database_map_param",
  "database_type", "$@36", "db_type", "user", "$@37", "password", "$@38",
  "host", "$@39", "port", "name", "$@40", "persist", "lfc_interval",
  "readonly", "connect_timeout", "reconnect_wait_time", "max_row_errors",
  "request_timeout", "tcp_keepalive", "tcp_nodelay", "contact_points",
  "$@41", "max_reconnect_tries", "keyspace", "$@42", "consistency", "$@43",
  "serial_consistency", "$@44", "sanity_checks", "$@45",
  "sanity_checks_params", "sanity_checks_param", "lease_checks", "$@46",
  "mac_sources", "$@47", "mac_sources_list", "mac_sources_value",
  "duid_id", "string_id", "host_reservation_identifiers", "$@48",
  "host_reservation_identifiers_list", "host_reservation_identifier",
  "hw_address_id", "flex_id", "relay_supplied_options", "$@49",
  "hooks_libraries", "$@50", "hooks_libraries_list",
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
  "dep_hostname_char_replacement", "$@124", "dhcp4_json_object", "$@125",
  "dhcpddns_json_object", "$@126", "control_agent_json_object", "$@127",
  "config_control", "$@128", "sub_config_control", "$@129",
  "config_control_params", "config_control_param", "config_databases",
  "$@130", "config_fetch_wait_time", "logging_object", "$@131",
  "sub_logging", "$@132", "logging_params", "logging_param", "loggers",
  "$@133", "loggers_entries", "logger_entry", "$@134", "logger_params",
  "logger_param", "debuglevel", "severity", "$@135", "output_options_list",
  "$@136", "output_options_list_content", "output_entry", "$@137",
  "output_params_list", "output_params", "output", "$@138", "flush",
  "maxsize", "maxver", "pattern", "$@139", YY_NULLPTR
  };

#if PARSER6_DEBUG
  const short
  Dhcp6Parser::yyrline_[] =
  {
       0,   283,   283,   283,   284,   284,   285,   285,   286,   286,
     287,   287,   288,   288,   289,   289,   290,   290,   291,   291,
     292,   292,   293,   293,   294,   294,   295,   295,   296,   296,
     297,   297,   305,   306,   307,   308,   309,   310,   311,   314,
     319,   319,   330,   333,   334,   337,   341,   348,   348,   355,
     356,   359,   363,   370,   370,   377,   378,   381,   385,   396,
     406,   406,   421,   422,   426,   427,   428,   429,   430,   431,
     434,   434,   449,   449,   458,   459,   464,   465,   466,   467,
     468,   469,   470,   471,   472,   473,   474,   475,   476,   477,
     478,   479,   480,   481,   482,   483,   484,   485,   486,   487,
     488,   489,   490,   491,   492,   493,   494,   495,   496,   497,
     498,   499,   500,   501,   502,   503,   504,   505,   506,   507,
     508,   509,   510,   511,   512,   513,   514,   515,   518,   518,
     526,   531,   536,   541,   546,   551,   556,   561,   566,   571,
     576,   581,   586,   591,   596,   601,   601,   609,   612,   615,
     618,   621,   627,   627,   635,   635,   643,   643,   651,   651,
     659,   664,   669,   674,   674,   682,   682,   693,   693,   702,
     703,   706,   707,   708,   709,   710,   713,   713,   723,   729,
     729,   741,   741,   753,   753,   763,   764,   767,   768,   771,
     771,   781,   782,   785,   786,   787,   788,   789,   790,   791,
     792,   793,   794,   795,   796,   797,   798,   799,   800,   801,
     802,   803,   804,   805,   808,   808,   815,   816,   817,   818,
     821,   821,   829,   829,   837,   837,   845,   850,   850,   858,
     863,   868,   873,   878,   883,   888,   893,   898,   903,   903,
     911,   916,   916,   924,   924,   932,   932,   940,   940,   950,
     951,   953,   955,   955,   973,   973,   983,   984,   987,   988,
     991,   996,  1001,  1001,  1011,  1012,  1015,  1016,  1017,  1020,
    1025,  1032,  1032,  1042,  1042,  1052,  1053,  1056,  1057,  1060,
    1060,  1070,  1070,  1080,  1081,  1082,  1085,  1086,  1089,  1089,
    1097,  1097,  1105,  1105,  1116,  1117,  1120,  1121,  1122,  1123,
    1124,  1125,  1128,  1133,  1138,  1143,  1148,  1153,  1161,  1161,
    1174,  1175,  1178,  1179,  1186,  1186,  1212,  1212,  1223,  1224,
    1228,  1229,  1230,  1231,  1232,  1233,  1234,  1235,  1236,  1237,
    1238,  1239,  1240,  1241,  1242,  1243,  1244,  1245,  1246,  1247,
    1248,  1249,  1250,  1251,  1252,  1253,  1254,  1255,  1256,  1257,
    1258,  1259,  1260,  1261,  1262,  1263,  1266,  1266,  1274,  1274,
    1282,  1282,  1290,  1290,  1298,  1298,  1308,  1308,  1315,  1316,
    1317,  1318,  1321,  1326,  1334,  1334,  1345,  1346,  1350,  1351,
    1354,  1354,  1362,  1363,  1366,  1367,  1368,  1369,  1370,  1371,
    1372,  1373,  1374,  1375,  1376,  1377,  1378,  1379,  1380,  1381,
    1382,  1383,  1384,  1385,  1386,  1387,  1388,  1389,  1390,  1391,
    1392,  1393,  1394,  1395,  1396,  1397,  1398,  1405,  1405,  1418,
    1418,  1427,  1428,  1431,  1432,  1437,  1437,  1452,  1452,  1466,
    1467,  1470,  1471,  1474,  1475,  1476,  1477,  1478,  1479,  1480,
    1481,  1482,  1483,  1486,  1488,  1493,  1495,  1495,  1503,  1503,
    1511,  1511,  1519,  1521,  1521,  1529,  1538,  1538,  1550,  1551,
    1556,  1557,  1562,  1562,  1574,  1574,  1586,  1587,  1592,  1593,
    1598,  1599,  1600,  1601,  1602,  1603,  1604,  1605,  1606,  1609,
    1611,  1611,  1619,  1621,  1623,  1628,  1636,  1636,  1648,  1649,
    1652,  1653,  1656,  1656,  1666,  1666,  1675,  1676,  1679,  1680,
    1681,  1682,  1683,  1684,  1685,  1688,  1688,  1696,  1696,  1721,
    1721,  1751,  1751,  1763,  1764,  1767,  1768,  1771,  1771,  1783,
    1783,  1795,  1796,  1799,  1800,  1801,  1802,  1803,  1804,  1805,
    1806,  1807,  1808,  1809,  1812,  1812,  1820,  1825,  1825,  1833,
    1838,  1846,  1846,  1856,  1857,  1860,  1861,  1864,  1864,  1873,
    1873,  1882,  1883,  1886,  1887,  1891,  1892,  1893,  1894,  1895,
    1896,  1897,  1898,  1899,  1900,  1901,  1904,  1904,  1914,  1914,
    1924,  1924,  1932,  1932,  1940,  1940,  1948,  1948,  1956,  1956,
    1969,  1969,  1979,  1980,  1983,  1983,  1994,  1994,  2004,  2005,
    2008,  2008,  2018,  2019,  2022,  2023,  2026,  2027,  2028,  2029,
    2030,  2031,  2032,  2035,  2037,  2037,  2045,  2053,  2053,  2065,
    2066,  2069,  2070,  2071,  2072,  2073,  2074,  2075,  2076,  2077,
    2080,  2080,  2087,  2088,  2089,  2092,  2097,  2097,  2105,  2110,
    2117,  2124,  2124,  2134,  2135,  2138,  2139,  2140,  2141,  2142,
    2145,  2145,  2153,  2153,  2163,  2163,  2175,  2176,  2179,  2180,
    2181,  2182,  2183,  2184,  2187,  2192,  2192,  2200,  2205,  2205,
    2214,  2214,  2226,  2226,  2236,  2237,  2240,  2241,  2242,  2243,
    2244,  2245,  2246,  2247,  2248,  2249,  2250,  2251,  2252,  2253,
    2254,  2255,  2256,  2257,  2260,  2265,  2265,  2273,  2273,  2281,
    2286,  2286,  2294,  2299,  2304,  2304,  2312,  2313,  2316,  2316,
    2325,  2331,  2337,  2337,  2345,  2345,  2354,  2354,  2363,  2363,
    2373,  2373,  2380,  2380,  2387,  2387,  2396,  2396,  2407,  2407,
    2417,  2418,  2422,  2423,  2426,  2426,  2436,  2446,  2446,  2456,
    2456,  2467,  2468,  2472,  2476,  2476,  2488,  2489,  2493,  2493,
    2501,  2502,  2505,  2506,  2507,  2508,  2509,  2510,  2511,  2514,
    2519,  2519,  2527,  2527,  2537,  2538,  2541,  2541,  2549,  2550,
    2553,  2554,  2555,  2556,  2557,  2560,  2560,  2568,  2573,  2578,
    2583,  2583
  };

  // Print the state stack on the debug stream.
  void
  Dhcp6Parser::yystack_print_ ()
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << int (i->state);
    *yycdebug_ << '\n';
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  Dhcp6Parser::yy_reduce_print_ (int yyrule)
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
#line 5585 "dhcp6_parser.cc"

#line 2591 "dhcp6_parser.yy"


void
isc::dhcp::Dhcp6Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
