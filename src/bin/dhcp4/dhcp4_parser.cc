// A Bison parser, made by GNU Bison 3.5.1.

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
#define yylex   parser4_lex



#include "dhcp4_parser.h"


// Unqualified %code blocks.
#line 34 "dhcp4_parser.yy"

#include <dhcp4/parser_context.h>

#line 51 "dhcp4_parser.cc"


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
      yystack_print_ ();                \
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
#line 143 "dhcp4_parser.cc"


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
  | Symbol types.  |
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

  Dhcp4Parser::symbol_number_type
  Dhcp4Parser::by_state::type_get () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return empty_symbol;
    else
      return yystos_[+state];
  }

  Dhcp4Parser::stack_symbol_type::stack_symbol_type ()
  {}

  Dhcp4Parser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state), YY_MOVE (that.location))
  {
    switch (that.type_get ())
    {
      case 218: // value
      case 222: // map_value
      case 265: // ddns_replace_client_name_value
      case 292: // socket_type
      case 295: // outbound_interface_value
      case 317: // db_type
      case 335: // on_fail_mode
      case 414: // hr_mode
      case 569: // ncr_protocol_value
        value.YY_MOVE_OR_COPY< ElementPtr > (YY_MOVE (that.value));
        break;

      case 202: // "boolean"
        value.YY_MOVE_OR_COPY< bool > (YY_MOVE (that.value));
        break;

      case 201: // "floating point"
        value.YY_MOVE_OR_COPY< double > (YY_MOVE (that.value));
        break;

      case 200: // "integer"
        value.YY_MOVE_OR_COPY< int64_t > (YY_MOVE (that.value));
        break;

      case 199: // "constant string"
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
    switch (that.type_get ())
    {
      case 218: // value
      case 222: // map_value
      case 265: // ddns_replace_client_name_value
      case 292: // socket_type
      case 295: // outbound_interface_value
      case 317: // db_type
      case 335: // on_fail_mode
      case 414: // hr_mode
      case 569: // ncr_protocol_value
        value.move< ElementPtr > (YY_MOVE (that.value));
        break;

      case 202: // "boolean"
        value.move< bool > (YY_MOVE (that.value));
        break;

      case 201: // "floating point"
        value.move< double > (YY_MOVE (that.value));
        break;

      case 200: // "integer"
        value.move< int64_t > (YY_MOVE (that.value));
        break;

      case 199: // "constant string"
        value.move< std::string > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

    // that is emptied.
    that.type = empty_symbol;
  }

#if YY_CPLUSPLUS < 201103L
  Dhcp4Parser::stack_symbol_type&
  Dhcp4Parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    switch (that.type_get ())
    {
      case 218: // value
      case 222: // map_value
      case 265: // ddns_replace_client_name_value
      case 292: // socket_type
      case 295: // outbound_interface_value
      case 317: // db_type
      case 335: // on_fail_mode
      case 414: // hr_mode
      case 569: // ncr_protocol_value
        value.copy< ElementPtr > (that.value);
        break;

      case 202: // "boolean"
        value.copy< bool > (that.value);
        break;

      case 201: // "floating point"
        value.copy< double > (that.value);
        break;

      case 200: // "integer"
        value.copy< int64_t > (that.value);
        break;

      case 199: // "constant string"
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
    switch (that.type_get ())
    {
      case 218: // value
      case 222: // map_value
      case 265: // ddns_replace_client_name_value
      case 292: // socket_type
      case 295: // outbound_interface_value
      case 317: // db_type
      case 335: // on_fail_mode
      case 414: // hr_mode
      case 569: // ncr_protocol_value
        value.move< ElementPtr > (that.value);
        break;

      case 202: // "boolean"
        value.move< bool > (that.value);
        break;

      case 201: // "floating point"
        value.move< double > (that.value);
        break;

      case 200: // "integer"
        value.move< int64_t > (that.value);
        break;

      case 199: // "constant string"
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
  Dhcp4Parser::yy_print_ (std::ostream& yyo,
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
      case 199: // "constant string"
#line 283 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < std::string > (); }
#line 451 "dhcp4_parser.cc"
        break;

      case 200: // "integer"
#line 283 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < int64_t > (); }
#line 457 "dhcp4_parser.cc"
        break;

      case 201: // "floating point"
#line 283 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < double > (); }
#line 463 "dhcp4_parser.cc"
        break;

      case 202: // "boolean"
#line 283 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < bool > (); }
#line 469 "dhcp4_parser.cc"
        break;

      case 218: // value
#line 283 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 475 "dhcp4_parser.cc"
        break;

      case 222: // map_value
#line 283 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 481 "dhcp4_parser.cc"
        break;

      case 265: // ddns_replace_client_name_value
#line 283 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 487 "dhcp4_parser.cc"
        break;

      case 292: // socket_type
#line 283 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 493 "dhcp4_parser.cc"
        break;

      case 295: // outbound_interface_value
#line 283 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 499 "dhcp4_parser.cc"
        break;

      case 317: // db_type
#line 283 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 505 "dhcp4_parser.cc"
        break;

      case 335: // on_fail_mode
#line 283 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 511 "dhcp4_parser.cc"
        break;

      case 414: // hr_mode
#line 283 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 517 "dhcp4_parser.cc"
        break;

      case 569: // ncr_protocol_value
#line 283 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 523 "dhcp4_parser.cc"
        break;

      default:
        break;
    }
    yyo << ')';
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
    int yyr = yypgoto_[yysym - yyntokens_] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - yyntokens_];
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
      case 218: // value
      case 222: // map_value
      case 265: // ddns_replace_client_name_value
      case 292: // socket_type
      case 295: // outbound_interface_value
      case 317: // db_type
      case 335: // on_fail_mode
      case 414: // hr_mode
      case 569: // ncr_protocol_value
        yylhs.value.emplace< ElementPtr > ();
        break;

      case 202: // "boolean"
        yylhs.value.emplace< bool > ();
        break;

      case 201: // "floating point"
        yylhs.value.emplace< double > ();
        break;

      case 200: // "integer"
        yylhs.value.emplace< int64_t > ();
        break;

      case 199: // "constant string"
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
#line 292 "dhcp4_parser.yy"
                     { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 792 "dhcp4_parser.cc"
    break;

  case 4:
#line 293 "dhcp4_parser.yy"
                      { ctx.ctx_ = ctx.CONFIG; }
#line 798 "dhcp4_parser.cc"
    break;

  case 6:
#line 294 "dhcp4_parser.yy"
                 { ctx.ctx_ = ctx.DHCP4; }
#line 804 "dhcp4_parser.cc"
    break;

  case 8:
#line 295 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 810 "dhcp4_parser.cc"
    break;

  case 10:
#line 296 "dhcp4_parser.yy"
                   { ctx.ctx_ = ctx.SUBNET4; }
#line 816 "dhcp4_parser.cc"
    break;

  case 12:
#line 297 "dhcp4_parser.yy"
                 { ctx.ctx_ = ctx.POOLS; }
#line 822 "dhcp4_parser.cc"
    break;

  case 14:
#line 298 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.RESERVATIONS; }
#line 828 "dhcp4_parser.cc"
    break;

  case 16:
#line 299 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.DHCP4; }
#line 834 "dhcp4_parser.cc"
    break;

  case 18:
#line 300 "dhcp4_parser.yy"
                      { ctx.ctx_ = ctx.OPTION_DEF; }
#line 840 "dhcp4_parser.cc"
    break;

  case 20:
#line 301 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.OPTION_DATA; }
#line 846 "dhcp4_parser.cc"
    break;

  case 22:
#line 302 "dhcp4_parser.yy"
                         { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 852 "dhcp4_parser.cc"
    break;

  case 24:
#line 303 "dhcp4_parser.yy"
                     { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 858 "dhcp4_parser.cc"
    break;

  case 26:
#line 304 "dhcp4_parser.yy"
                          { ctx.ctx_ = ctx.CONFIG_CONTROL; }
#line 864 "dhcp4_parser.cc"
    break;

  case 28:
#line 312 "dhcp4_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 870 "dhcp4_parser.cc"
    break;

  case 29:
#line 313 "dhcp4_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location))); }
#line 876 "dhcp4_parser.cc"
    break;

  case 30:
#line 314 "dhcp4_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 882 "dhcp4_parser.cc"
    break;

  case 31:
#line 315 "dhcp4_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 888 "dhcp4_parser.cc"
    break;

  case 32:
#line 316 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 894 "dhcp4_parser.cc"
    break;

  case 33:
#line 317 "dhcp4_parser.yy"
            { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 900 "dhcp4_parser.cc"
    break;

  case 34:
#line 318 "dhcp4_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 906 "dhcp4_parser.cc"
    break;

  case 35:
#line 321 "dhcp4_parser.yy"
                {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as < ElementPtr > ());
}
#line 915 "dhcp4_parser.cc"
    break;

  case 36:
#line 326 "dhcp4_parser.yy"
                     {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 926 "dhcp4_parser.cc"
    break;

  case 37:
#line 331 "dhcp4_parser.yy"
                             {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 936 "dhcp4_parser.cc"
    break;

  case 38:
#line 337 "dhcp4_parser.yy"
                { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 942 "dhcp4_parser.cc"
    break;

  case 41:
#line 344 "dhcp4_parser.yy"
                                  {
                  // map containing a single entry
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 952 "dhcp4_parser.cc"
    break;

  case 42:
#line 349 "dhcp4_parser.yy"
                                                      {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.unique(yystack_[2].value.as < std::string > (), ctx.loc2pos(yystack_[2].location));
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 963 "dhcp4_parser.cc"
    break;

  case 43:
#line 355 "dhcp4_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 971 "dhcp4_parser.cc"
    break;

  case 44:
#line 360 "dhcp4_parser.yy"
                              {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 980 "dhcp4_parser.cc"
    break;

  case 45:
#line 363 "dhcp4_parser.yy"
                               {
    // list parsing complete. Put any sanity checking here
}
#line 988 "dhcp4_parser.cc"
    break;

  case 48:
#line 371 "dhcp4_parser.yy"
                      {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 997 "dhcp4_parser.cc"
    break;

  case 49:
#line 375 "dhcp4_parser.yy"
                                           {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 1006 "dhcp4_parser.cc"
    break;

  case 50:
#line 379 "dhcp4_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 1014 "dhcp4_parser.cc"
    break;

  case 51:
#line 385 "dhcp4_parser.yy"
                              {
    // List parsing about to start
}
#line 1022 "dhcp4_parser.cc"
    break;

  case 52:
#line 387 "dhcp4_parser.yy"
                                       {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 1031 "dhcp4_parser.cc"
    break;

  case 55:
#line 396 "dhcp4_parser.yy"
                               {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 1040 "dhcp4_parser.cc"
    break;

  case 56:
#line 400 "dhcp4_parser.yy"
                                                            {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 1049 "dhcp4_parser.cc"
    break;

  case 57:
#line 404 "dhcp4_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 1057 "dhcp4_parser.cc"
    break;

  case 58:
#line 414 "dhcp4_parser.yy"
                                {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as < std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 1068 "dhcp4_parser.cc"
    break;

  case 59:
#line 423 "dhcp4_parser.yy"
                           {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1079 "dhcp4_parser.cc"
    break;

  case 60:
#line 428 "dhcp4_parser.yy"
                               {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.

    // Dhcp4 is required
    ctx.require("Dhcp4", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
}
#line 1092 "dhcp4_parser.cc"
    break;

  case 61:
#line 438 "dhcp4_parser.yy"
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
#line 1107 "dhcp4_parser.cc"
    break;

  case 62:
#line 447 "dhcp4_parser.yy"
                                                    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1117 "dhcp4_parser.cc"
    break;

  case 64:
#line 455 "dhcp4_parser.yy"
                                         {
    ctx.warnAboutExtraCommas(yystack_[0].location);
}
#line 1125 "dhcp4_parser.cc"
    break;

  case 65:
#line 461 "dhcp4_parser.yy"
                          {
    // Parse the Dhcp4 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1135 "dhcp4_parser.cc"
    break;

  case 66:
#line 465 "dhcp4_parser.yy"
                               {
    // No global parameter is required
    // parsing completed
}
#line 1144 "dhcp4_parser.cc"
    break;

  case 69:
#line 472 "dhcp4_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 1152 "dhcp4_parser.cc"
    break;

  case 134:
#line 545 "dhcp4_parser.yy"
                                             {
    ctx.unique("valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1162 "dhcp4_parser.cc"
    break;

  case 135:
#line 551 "dhcp4_parser.yy"
                                                     {
    ctx.unique("min-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-valid-lifetime", prf);
}
#line 1172 "dhcp4_parser.cc"
    break;

  case 136:
#line 557 "dhcp4_parser.yy"
                                                     {
    ctx.unique("max-valid-lifetime", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-valid-lifetime", prf);
}
#line 1182 "dhcp4_parser.cc"
    break;

  case 137:
#line 563 "dhcp4_parser.yy"
                                       {
    ctx.unique("renew-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1192 "dhcp4_parser.cc"
    break;

  case 138:
#line 569 "dhcp4_parser.yy"
                                         {
    ctx.unique("rebind-timer", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1202 "dhcp4_parser.cc"
    break;

  case 139:
#line 575 "dhcp4_parser.yy"
                                                       {
    ctx.unique("calculate-tee-times", ctx.loc2pos(yystack_[2].location));
    ElementPtr ctt(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("calculate-tee-times", ctt);
}
#line 1212 "dhcp4_parser.cc"
    break;

  case 140:
#line 581 "dhcp4_parser.yy"
                                   {
    ctx.unique("t1-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t1(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t1-percent", t1);
}
#line 1222 "dhcp4_parser.cc"
    break;

  case 141:
#line 587 "dhcp4_parser.yy"
                                   {
    ctx.unique("t2-percent", ctx.loc2pos(yystack_[2].location));
    ElementPtr t2(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t2-percent", t2);
}
#line 1232 "dhcp4_parser.cc"
    break;

  case 142:
#line 593 "dhcp4_parser.yy"
                                             {
    ctx.unique("cache-threshold", ctx.loc2pos(yystack_[2].location));
    ElementPtr ct(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-threshold", ct);
}
#line 1242 "dhcp4_parser.cc"
    break;

  case 143:
#line 599 "dhcp4_parser.yy"
                                           {
    ctx.unique("cache-max-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr cm(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cache-max-age", cm);
}
#line 1252 "dhcp4_parser.cc"
    break;

  case 144:
#line 605 "dhcp4_parser.yy"
                                                                 {
    ctx.unique("decline-probation-period", ctx.loc2pos(yystack_[2].location));
    ElementPtr dpp(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1262 "dhcp4_parser.cc"
    break;

  case 145:
#line 611 "dhcp4_parser.yy"
                       {
    ctx.unique("server-tag", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1271 "dhcp4_parser.cc"
    break;

  case 146:
#line 614 "dhcp4_parser.yy"
               {
    ElementPtr stag(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-tag", stag);
    ctx.leave();
}
#line 1281 "dhcp4_parser.cc"
    break;

  case 147:
#line 620 "dhcp4_parser.yy"
                                                       {
    ctx.unique("parked-packet-limit", ctx.loc2pos(yystack_[2].location));
    ElementPtr ppl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("parked-packet-limit", ppl);
}
#line 1291 "dhcp4_parser.cc"
    break;

  case 148:
#line 626 "dhcp4_parser.yy"
                                             {
    ctx.unique("echo-client-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr echo(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("echo-client-id", echo);
}
#line 1301 "dhcp4_parser.cc"
    break;

  case 149:
#line 632 "dhcp4_parser.yy"
                                               {
    ctx.unique("match-client-id", ctx.loc2pos(yystack_[2].location));
    ElementPtr match(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("match-client-id", match);
}
#line 1311 "dhcp4_parser.cc"
    break;

  case 150:
#line 638 "dhcp4_parser.yy"
                                           {
    ctx.unique("authoritative", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("authoritative", prf);
}
#line 1321 "dhcp4_parser.cc"
    break;

  case 151:
#line 644 "dhcp4_parser.yy"
                                                   {
    ctx.unique("ddns-send-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-send-updates", b);
}
#line 1331 "dhcp4_parser.cc"
    break;

  case 152:
#line 650 "dhcp4_parser.yy"
                                                               {
    ctx.unique("ddns-override-no-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-no-update", b);
}
#line 1341 "dhcp4_parser.cc"
    break;

  case 153:
#line 656 "dhcp4_parser.yy"
                                                                       {
    ctx.unique("ddns-override-client-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-client-update", b);
}
#line 1351 "dhcp4_parser.cc"
    break;

  case 154:
#line 662 "dhcp4_parser.yy"
                                                   {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
    ctx.unique("ddns-replace-client-name", ctx.loc2pos(yystack_[0].location));
}
#line 1360 "dhcp4_parser.cc"
    break;

  case 155:
#line 665 "dhcp4_parser.yy"
                                       {
    ctx.stack_.back()->set("ddns-replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1369 "dhcp4_parser.cc"
    break;

  case 156:
#line 671 "dhcp4_parser.yy"
                 {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1377 "dhcp4_parser.cc"
    break;

  case 157:
#line 674 "dhcp4_parser.yy"
          {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 1385 "dhcp4_parser.cc"
    break;

  case 158:
#line 677 "dhcp4_parser.yy"
           {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 1393 "dhcp4_parser.cc"
    break;

  case 159:
#line 680 "dhcp4_parser.yy"
                     {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1401 "dhcp4_parser.cc"
    break;

  case 160:
#line 683 "dhcp4_parser.yy"
            {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 1410 "dhcp4_parser.cc"
    break;

  case 161:
#line 689 "dhcp4_parser.yy"
                                             {
    ctx.unique("ddns-generated-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1419 "dhcp4_parser.cc"
    break;

  case 162:
#line 692 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-generated-prefix", s);
    ctx.leave();
}
#line 1429 "dhcp4_parser.cc"
    break;

  case 163:
#line 698 "dhcp4_parser.yy"
                                               {
    ctx.unique("ddns-qualifying-suffix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1438 "dhcp4_parser.cc"
    break;

  case 164:
#line 701 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-qualifying-suffix", s);
    ctx.leave();
}
#line 1448 "dhcp4_parser.cc"
    break;

  case 165:
#line 707 "dhcp4_parser.yy"
                                                         {
    ctx.unique("ddns-update-on-renew", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-update-on-renew", b);
}
#line 1458 "dhcp4_parser.cc"
    break;

  case 166:
#line 713 "dhcp4_parser.yy"
                                                                         {
    ctx.unique("ddns-use-conflict-resolution", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-use-conflict-resolution", b);
}
#line 1468 "dhcp4_parser.cc"
    break;

  case 167:
#line 719 "dhcp4_parser.yy"
                                     {
    ctx.unique("hostname-char-set", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1477 "dhcp4_parser.cc"
    break;

  case 168:
#line 722 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 1487 "dhcp4_parser.cc"
    break;

  case 169:
#line 728 "dhcp4_parser.yy"
                                                     {
    ctx.unique("hostname-char-replacement", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1496 "dhcp4_parser.cc"
    break;

  case 170:
#line 731 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 1506 "dhcp4_parser.cc"
    break;

  case 171:
#line 737 "dhcp4_parser.yy"
                                                       {
    ctx.unique("store-extended-info", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("store-extended-info", b);
}
#line 1516 "dhcp4_parser.cc"
    break;

  case 172:
#line 743 "dhcp4_parser.yy"
                                                                             {
    ctx.unique("statistic-default-sample-count", ctx.loc2pos(yystack_[2].location));
    ElementPtr count(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-count", count);
}
#line 1526 "dhcp4_parser.cc"
    break;

  case 173:
#line 749 "dhcp4_parser.yy"
                                                                         {
    ctx.unique("statistic-default-sample-age", ctx.loc2pos(yystack_[2].location));
    ElementPtr age(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-age", age);
}
#line 1536 "dhcp4_parser.cc"
    break;

  case 174:
#line 755 "dhcp4_parser.yy"
                                                                                 {
    ctx.unique("early-global-reservations-lookup", ctx.loc2pos(yystack_[2].location));
    ElementPtr early(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("early-global-reservations-lookup", early);
}
#line 1546 "dhcp4_parser.cc"
    break;

  case 175:
#line 761 "dhcp4_parser.yy"
                                                             {
    ctx.unique("ip-reservations-unique", ctx.loc2pos(yystack_[2].location));
    ElementPtr unique(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-reservations-unique", unique);
}
#line 1556 "dhcp4_parser.cc"
    break;

  case 176:
#line 767 "dhcp4_parser.yy"
                                                                   {
    ctx.unique("reservations-lookup-first", ctx.loc2pos(yystack_[2].location));
    ElementPtr first(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-lookup-first", first);
}
#line 1566 "dhcp4_parser.cc"
    break;

  case 177:
#line 773 "dhcp4_parser.yy"
                                     {
    ctx.unique("interfaces-config", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1578 "dhcp4_parser.cc"
    break;

  case 178:
#line 779 "dhcp4_parser.yy"
                                                               {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1588 "dhcp4_parser.cc"
    break;

  case 181:
#line 787 "dhcp4_parser.yy"
                                                         {
                            ctx.warnAboutExtraCommas(yystack_[0].location);
                            }
#line 1596 "dhcp4_parser.cc"
    break;

  case 189:
#line 801 "dhcp4_parser.yy"
                                {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1606 "dhcp4_parser.cc"
    break;

  case 190:
#line 805 "dhcp4_parser.yy"
                                          {
    // No interfaces config param is required
    // parsing completed
}
#line 1615 "dhcp4_parser.cc"
    break;

  case 191:
#line 810 "dhcp4_parser.yy"
                            {
    ctx.unique("interfaces", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1627 "dhcp4_parser.cc"
    break;

  case 192:
#line 816 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1636 "dhcp4_parser.cc"
    break;

  case 193:
#line 821 "dhcp4_parser.yy"
                                   {
    ctx.unique("dhcp-socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DHCP_SOCKET_TYPE);
}
#line 1645 "dhcp4_parser.cc"
    break;

  case 194:
#line 824 "dhcp4_parser.yy"
                    {
    ctx.stack_.back()->set("dhcp-socket-type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1654 "dhcp4_parser.cc"
    break;

  case 195:
#line 829 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("raw", ctx.loc2pos(yystack_[0].location))); }
#line 1660 "dhcp4_parser.cc"
    break;

  case 196:
#line 830 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("udp", ctx.loc2pos(yystack_[0].location))); }
#line 1666 "dhcp4_parser.cc"
    break;

  case 197:
#line 833 "dhcp4_parser.yy"
                                       {
    ctx.unique("outbound-interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.OUTBOUND_INTERFACE);
}
#line 1675 "dhcp4_parser.cc"
    break;

  case 198:
#line 836 "dhcp4_parser.yy"
                                 {
    ctx.stack_.back()->set("outbound-interface", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1684 "dhcp4_parser.cc"
    break;

  case 199:
#line 841 "dhcp4_parser.yy"
                                          {
    yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("same-as-inbound", ctx.loc2pos(yystack_[0].location)));
}
#line 1692 "dhcp4_parser.cc"
    break;

  case 200:
#line 843 "dhcp4_parser.yy"
                {
    yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("use-routing", ctx.loc2pos(yystack_[0].location)));
    }
#line 1700 "dhcp4_parser.cc"
    break;

  case 201:
#line 847 "dhcp4_parser.yy"
                                   {
    ctx.unique("re-detect", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1710 "dhcp4_parser.cc"
    break;

  case 202:
#line 854 "dhcp4_parser.yy"
                               {
    ctx.unique("lease-database", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1722 "dhcp4_parser.cc"
    break;

  case 203:
#line 860 "dhcp4_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1733 "dhcp4_parser.cc"
    break;

  case 204:
#line 867 "dhcp4_parser.yy"
                             {
    ctx.unique("sanity-checks", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sanity-checks", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SANITY_CHECKS);
}
#line 1745 "dhcp4_parser.cc"
    break;

  case 205:
#line 873 "dhcp4_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1754 "dhcp4_parser.cc"
    break;

  case 208:
#line 880 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 1762 "dhcp4_parser.cc"
    break;

  case 210:
#line 887 "dhcp4_parser.yy"
                           {
    ctx.unique("lease-checks", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1771 "dhcp4_parser.cc"
    break;

  case 211:
#line 890 "dhcp4_parser.yy"
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
#line 1791 "dhcp4_parser.cc"
    break;

  case 212:
#line 906 "dhcp4_parser.yy"
                               {
    ctx.unique("hosts-database", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1803 "dhcp4_parser.cc"
    break;

  case 213:
#line 912 "dhcp4_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1814 "dhcp4_parser.cc"
    break;

  case 214:
#line 919 "dhcp4_parser.yy"
                                 {
    ctx.unique("hosts-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1826 "dhcp4_parser.cc"
    break;

  case 215:
#line 925 "dhcp4_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1835 "dhcp4_parser.cc"
    break;

  case 220:
#line 936 "dhcp4_parser.yy"
                                                       {
                           ctx.warnAboutExtraCommas(yystack_[0].location);
                           }
#line 1843 "dhcp4_parser.cc"
    break;

  case 221:
#line 941 "dhcp4_parser.yy"
                         {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1853 "dhcp4_parser.cc"
    break;

  case 222:
#line 945 "dhcp4_parser.yy"
                                     {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1863 "dhcp4_parser.cc"
    break;

  case 225:
#line 953 "dhcp4_parser.yy"
                                               {
                       ctx.warnAboutExtraCommas(yystack_[0].location);
                       }
#line 1871 "dhcp4_parser.cc"
    break;

  case 245:
#line 979 "dhcp4_parser.yy"
                    {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1880 "dhcp4_parser.cc"
    break;

  case 246:
#line 982 "dhcp4_parser.yy"
                {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1889 "dhcp4_parser.cc"
    break;

  case 247:
#line 987 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1895 "dhcp4_parser.cc"
    break;

  case 248:
#line 988 "dhcp4_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1901 "dhcp4_parser.cc"
    break;

  case 249:
#line 989 "dhcp4_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1907 "dhcp4_parser.cc"
    break;

  case 250:
#line 992 "dhcp4_parser.yy"
           {
    ctx.unique("user", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1916 "dhcp4_parser.cc"
    break;

  case 251:
#line 995 "dhcp4_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1926 "dhcp4_parser.cc"
    break;

  case 252:
#line 1001 "dhcp4_parser.yy"
                   {
    ctx.unique("password", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1935 "dhcp4_parser.cc"
    break;

  case 253:
#line 1004 "dhcp4_parser.yy"
               {
    ElementPtr pwd(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1945 "dhcp4_parser.cc"
    break;

  case 254:
#line 1010 "dhcp4_parser.yy"
           {
    ctx.unique("host", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1954 "dhcp4_parser.cc"
    break;

  case 255:
#line 1013 "dhcp4_parser.yy"
               {
    ElementPtr h(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1964 "dhcp4_parser.cc"
    break;

  case 256:
#line 1019 "dhcp4_parser.yy"
                         {
    ctx.unique("port", ctx.loc2pos(yystack_[2].location));
    ElementPtr p(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1974 "dhcp4_parser.cc"
    break;

  case 257:
#line 1025 "dhcp4_parser.yy"
           {
    ctx.unique("name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1983 "dhcp4_parser.cc"
    break;

  case 258:
#line 1028 "dhcp4_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1993 "dhcp4_parser.cc"
    break;

  case 259:
#line 1034 "dhcp4_parser.yy"
                               {
    ctx.unique("persist", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 2003 "dhcp4_parser.cc"
    break;

  case 260:
#line 1040 "dhcp4_parser.yy"
                                         {
    ctx.unique("lfc-interval", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 2013 "dhcp4_parser.cc"
    break;

  case 261:
#line 1046 "dhcp4_parser.yy"
                                 {
    ctx.unique("readonly", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 2023 "dhcp4_parser.cc"
    break;

  case 262:
#line 1052 "dhcp4_parser.yy"
                                               {
    ctx.unique("connect-timeout", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 2033 "dhcp4_parser.cc"
    break;

  case 263:
#line 1058 "dhcp4_parser.yy"
                                                       {
    ctx.unique("max-reconnect-tries", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 2043 "dhcp4_parser.cc"
    break;

  case 264:
#line 1064 "dhcp4_parser.yy"
                                                       {
    ctx.unique("reconnect-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 2053 "dhcp4_parser.cc"
    break;

  case 265:
#line 1070 "dhcp4_parser.yy"
                 {
    ctx.unique("on-fail", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.DATABASE_ON_FAIL);
}
#line 2062 "dhcp4_parser.cc"
    break;

  case 266:
#line 1073 "dhcp4_parser.yy"
                     {
    ctx.stack_.back()->set("on-fail", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2071 "dhcp4_parser.cc"
    break;

  case 267:
#line 1078 "dhcp4_parser.yy"
                              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("stop-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 2077 "dhcp4_parser.cc"
    break;

  case 268:
#line 1079 "dhcp4_parser.yy"
                               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-exit", ctx.loc2pos(yystack_[0].location))); }
#line 2083 "dhcp4_parser.cc"
    break;

  case 269:
#line 1080 "dhcp4_parser.yy"
                                   { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("serve-retry-continue", ctx.loc2pos(yystack_[0].location))); }
#line 2089 "dhcp4_parser.cc"
    break;

  case 270:
#line 1083 "dhcp4_parser.yy"
                                             {
    ctx.unique("max-row-errors", ctx.loc2pos(yystack_[2].location));
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-row-errors", n);
}
#line 2099 "dhcp4_parser.cc"
    break;

  case 271:
#line 1089 "dhcp4_parser.yy"
                           {
    ctx.unique("trust-anchor", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2108 "dhcp4_parser.cc"
    break;

  case 272:
#line 1092 "dhcp4_parser.yy"
               {
    ElementPtr ca(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("trust-anchor", ca);
    ctx.leave();
}
#line 2118 "dhcp4_parser.cc"
    break;

  case 273:
#line 1098 "dhcp4_parser.yy"
                     {
    ctx.unique("cert-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2127 "dhcp4_parser.cc"
    break;

  case 274:
#line 1101 "dhcp4_parser.yy"
               {
    ElementPtr cert(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cert-file", cert);
    ctx.leave();
}
#line 2137 "dhcp4_parser.cc"
    break;

  case 275:
#line 1107 "dhcp4_parser.yy"
                   {
    ctx.unique("key-file", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2146 "dhcp4_parser.cc"
    break;

  case 276:
#line 1110 "dhcp4_parser.yy"
               {
    ElementPtr key(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("key-file", key);
    ctx.leave();
}
#line 2156 "dhcp4_parser.cc"
    break;

  case 277:
#line 1116 "dhcp4_parser.yy"
                         {
    ctx.unique("cipher-list", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2165 "dhcp4_parser.cc"
    break;

  case 278:
#line 1119 "dhcp4_parser.yy"
               {
    ElementPtr cl(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("cipher-list", cl);
    ctx.leave();
}
#line 2175 "dhcp4_parser.cc"
    break;

  case 279:
#line 1125 "dhcp4_parser.yy"
                                                           {
    ctx.unique("host-reservation-identifiers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 2187 "dhcp4_parser.cc"
    break;

  case 280:
#line 1131 "dhcp4_parser.yy"
                                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2196 "dhcp4_parser.cc"
    break;

  case 283:
#line 1138 "dhcp4_parser.yy"
                                              {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 2204 "dhcp4_parser.cc"
    break;

  case 289:
#line 1150 "dhcp4_parser.yy"
              {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 2213 "dhcp4_parser.cc"
    break;

  case 290:
#line 1155 "dhcp4_parser.yy"
                          {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 2222 "dhcp4_parser.cc"
    break;

  case 291:
#line 1160 "dhcp4_parser.yy"
                       {
    ElementPtr circuit(new StringElement("circuit-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(circuit);
}
#line 2231 "dhcp4_parser.cc"
    break;

  case 292:
#line 1165 "dhcp4_parser.yy"
                     {
    ElementPtr client(new StringElement("client-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(client);
}
#line 2240 "dhcp4_parser.cc"
    break;

  case 293:
#line 1170 "dhcp4_parser.yy"
                 {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 2249 "dhcp4_parser.cc"
    break;

  case 294:
#line 1177 "dhcp4_parser.yy"
                                           {
    ctx.unique("multi-threading", ctx.loc2pos(yystack_[0].location));
    ElementPtr mt(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("multi-threading", mt);
    ctx.stack_.push_back(mt);
    ctx.enter(ctx.DHCP_MULTI_THREADING);
}
#line 2261 "dhcp4_parser.cc"
    break;

  case 295:
#line 1183 "dhcp4_parser.yy"
                                                             {
    // The enable parameter is required.
    ctx.require("enable-multi-threading", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2272 "dhcp4_parser.cc"
    break;

  case 298:
#line 1192 "dhcp4_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 2280 "dhcp4_parser.cc"
    break;

  case 305:
#line 1205 "dhcp4_parser.yy"
                                                             {
    ctx.unique("enable-multi-threading", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-multi-threading", b);
}
#line 2290 "dhcp4_parser.cc"
    break;

  case 306:
#line 1211 "dhcp4_parser.yy"
                                                 {
    ctx.unique("thread-pool-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("thread-pool-size", prf);
}
#line 2300 "dhcp4_parser.cc"
    break;

  case 307:
#line 1217 "dhcp4_parser.yy"
                                                   {
    ctx.unique("packet-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("packet-queue-size", prf);
}
#line 2310 "dhcp4_parser.cc"
    break;

  case 308:
#line 1223 "dhcp4_parser.yy"
                                 {
    ctx.unique("hooks-libraries", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 2322 "dhcp4_parser.cc"
    break;

  case 309:
#line 1229 "dhcp4_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2331 "dhcp4_parser.cc"
    break;

  case 314:
#line 1240 "dhcp4_parser.yy"
                                           {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 2339 "dhcp4_parser.cc"
    break;

  case 315:
#line 1245 "dhcp4_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2349 "dhcp4_parser.cc"
    break;

  case 316:
#line 1249 "dhcp4_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2359 "dhcp4_parser.cc"
    break;

  case 317:
#line 1255 "dhcp4_parser.yy"
                                  {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2369 "dhcp4_parser.cc"
    break;

  case 318:
#line 1259 "dhcp4_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2379 "dhcp4_parser.cc"
    break;

  case 321:
#line 1267 "dhcp4_parser.yy"
                                 {
                ctx.warnAboutExtraCommas(yystack_[0].location);
                }
#line 2387 "dhcp4_parser.cc"
    break;

  case 325:
#line 1277 "dhcp4_parser.yy"
                 {
    ctx.unique("library", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2396 "dhcp4_parser.cc"
    break;

  case 326:
#line 1280 "dhcp4_parser.yy"
               {
    ElementPtr lib(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 2406 "dhcp4_parser.cc"
    break;

  case 327:
#line 1286 "dhcp4_parser.yy"
                       {
    ctx.unique("parameters", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2415 "dhcp4_parser.cc"
    break;

  case 328:
#line 1289 "dhcp4_parser.yy"
                  {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2424 "dhcp4_parser.cc"
    break;

  case 329:
#line 1295 "dhcp4_parser.yy"
                                                     {
    ctx.unique("expired-leases-processing", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 2436 "dhcp4_parser.cc"
    break;

  case 330:
#line 1301 "dhcp4_parser.yy"
                                                            {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2446 "dhcp4_parser.cc"
    break;

  case 333:
#line 1309 "dhcp4_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 2454 "dhcp4_parser.cc"
    break;

  case 340:
#line 1322 "dhcp4_parser.yy"
                                                               {
    ctx.unique("reclaim-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 2464 "dhcp4_parser.cc"
    break;

  case 341:
#line 1328 "dhcp4_parser.yy"
                                                                               {
    ctx.unique("flush-reclaimed-timer-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 2474 "dhcp4_parser.cc"
    break;

  case 342:
#line 1334 "dhcp4_parser.yy"
                                                       {
    ctx.unique("hold-reclaimed-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 2484 "dhcp4_parser.cc"
    break;

  case 343:
#line 1340 "dhcp4_parser.yy"
                                                     {
    ctx.unique("max-reclaim-leases", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 2494 "dhcp4_parser.cc"
    break;

  case 344:
#line 1346 "dhcp4_parser.yy"
                                                 {
    ctx.unique("max-reclaim-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 2504 "dhcp4_parser.cc"
    break;

  case 345:
#line 1352 "dhcp4_parser.yy"
                                                               {
    ctx.unique("unwarned-reclaim-cycles", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 2514 "dhcp4_parser.cc"
    break;

  case 346:
#line 1361 "dhcp4_parser.yy"
                      {
    ctx.unique("subnet4", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet4", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET4);
}
#line 2526 "dhcp4_parser.cc"
    break;

  case 347:
#line 1367 "dhcp4_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2535 "dhcp4_parser.cc"
    break;

  case 352:
#line 1381 "dhcp4_parser.yy"
                                                     {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 2543 "dhcp4_parser.cc"
    break;

  case 353:
#line 1390 "dhcp4_parser.yy"
                        {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2553 "dhcp4_parser.cc"
    break;

  case 354:
#line 1394 "dhcp4_parser.yy"
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
#line 2579 "dhcp4_parser.cc"
    break;

  case 355:
#line 1416 "dhcp4_parser.yy"
                            {
    // Parse the subnet4 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2589 "dhcp4_parser.cc"
    break;

  case 356:
#line 1420 "dhcp4_parser.yy"
                                {
    // The subnet subnet4 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2599 "dhcp4_parser.cc"
    break;

  case 359:
#line 1429 "dhcp4_parser.yy"
                                     {
                  ctx.warnAboutExtraCommas(yystack_[0].location);
                  }
#line 2607 "dhcp4_parser.cc"
    break;

  case 405:
#line 1482 "dhcp4_parser.yy"
               {
    ctx.unique("subnet", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2616 "dhcp4_parser.cc"
    break;

  case 406:
#line 1485 "dhcp4_parser.yy"
               {
    ElementPtr subnet(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 2626 "dhcp4_parser.cc"
    break;

  case 407:
#line 1491 "dhcp4_parser.yy"
                                           {
    ctx.unique("4o6-interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2635 "dhcp4_parser.cc"
    break;

  case 408:
#line 1494 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface", iface);
    ctx.leave();
}
#line 2645 "dhcp4_parser.cc"
    break;

  case 409:
#line 1500 "dhcp4_parser.yy"
                                                 {
    ctx.unique("4o6-interface-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2654 "dhcp4_parser.cc"
    break;

  case 410:
#line 1503 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface-id", iface);
    ctx.leave();
}
#line 2664 "dhcp4_parser.cc"
    break;

  case 411:
#line 1509 "dhcp4_parser.yy"
                                     {
    ctx.unique("4o6-subnet", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2673 "dhcp4_parser.cc"
    break;

  case 412:
#line 1512 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-subnet", iface);
    ctx.leave();
}
#line 2683 "dhcp4_parser.cc"
    break;

  case 413:
#line 1518 "dhcp4_parser.yy"
                     {
    ctx.unique("interface", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2692 "dhcp4_parser.cc"
    break;

  case 414:
#line 1521 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 2702 "dhcp4_parser.cc"
    break;

  case 415:
#line 1527 "dhcp4_parser.yy"
                           {
    ctx.unique("client-class", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2711 "dhcp4_parser.cc"
    break;

  case 416:
#line 1530 "dhcp4_parser.yy"
               {
    ElementPtr cls(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 2721 "dhcp4_parser.cc"
    break;

  case 417:
#line 1536 "dhcp4_parser.yy"
                                               {
    ctx.unique("require-client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2733 "dhcp4_parser.cc"
    break;

  case 418:
#line 1542 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2742 "dhcp4_parser.cc"
    break;

  case 419:
#line 1547 "dhcp4_parser.yy"
                                                       {
    ctx.unique("reservations-global", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-global", b);
}
#line 2752 "dhcp4_parser.cc"
    break;

  case 420:
#line 1553 "dhcp4_parser.yy"
                                                             {
    ctx.unique("reservations-in-subnet", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-in-subnet", b);
}
#line 2762 "dhcp4_parser.cc"
    break;

  case 421:
#line 1559 "dhcp4_parser.yy"
                                                                 {
    ctx.unique("reservations-out-of-pool", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations-out-of-pool", b);
}
#line 2772 "dhcp4_parser.cc"
    break;

  case 422:
#line 1565 "dhcp4_parser.yy"
                                   {
    ctx.unique("reservation-mode", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 2781 "dhcp4_parser.cc"
    break;

  case 423:
#line 1568 "dhcp4_parser.yy"
                {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2790 "dhcp4_parser.cc"
    break;

  case 424:
#line 1573 "dhcp4_parser.yy"
                  { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 2796 "dhcp4_parser.cc"
    break;

  case 425:
#line 1574 "dhcp4_parser.yy"
                     { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 2802 "dhcp4_parser.cc"
    break;

  case 426:
#line 1575 "dhcp4_parser.yy"
                { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("global", ctx.loc2pos(yystack_[0].location))); }
#line 2808 "dhcp4_parser.cc"
    break;

  case 427:
#line 1576 "dhcp4_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 2814 "dhcp4_parser.cc"
    break;

  case 428:
#line 1579 "dhcp4_parser.yy"
                     {
    ctx.unique("id", ctx.loc2pos(yystack_[2].location));
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 2824 "dhcp4_parser.cc"
    break;

  case 429:
#line 1587 "dhcp4_parser.yy"
                                 {
    ctx.unique("shared-networks", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 2836 "dhcp4_parser.cc"
    break;

  case 430:
#line 1593 "dhcp4_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2845 "dhcp4_parser.cc"
    break;

  case 435:
#line 1606 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 2853 "dhcp4_parser.cc"
    break;

  case 436:
#line 1611 "dhcp4_parser.yy"
                               {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2863 "dhcp4_parser.cc"
    break;

  case 437:
#line 1615 "dhcp4_parser.yy"
                                       {
    ctx.stack_.pop_back();
}
#line 2871 "dhcp4_parser.cc"
    break;

  case 440:
#line 1621 "dhcp4_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 2879 "dhcp4_parser.cc"
    break;

  case 481:
#line 1672 "dhcp4_parser.yy"
                            {
    ctx.unique("option-def", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 2891 "dhcp4_parser.cc"
    break;

  case 482:
#line 1678 "dhcp4_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2900 "dhcp4_parser.cc"
    break;

  case 483:
#line 1686 "dhcp4_parser.yy"
                                    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2909 "dhcp4_parser.cc"
    break;

  case 484:
#line 1689 "dhcp4_parser.yy"
                                 {
    // parsing completed
}
#line 2917 "dhcp4_parser.cc"
    break;

  case 489:
#line 1701 "dhcp4_parser.yy"
                                                           {
                             ctx.warnAboutExtraCommas(yystack_[0].location);
                             }
#line 2925 "dhcp4_parser.cc"
    break;

  case 490:
#line 1708 "dhcp4_parser.yy"
                                 {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2935 "dhcp4_parser.cc"
    break;

  case 491:
#line 1712 "dhcp4_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2947 "dhcp4_parser.cc"
    break;

  case 492:
#line 1723 "dhcp4_parser.yy"
                               {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2957 "dhcp4_parser.cc"
    break;

  case 493:
#line 1727 "dhcp4_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2969 "dhcp4_parser.cc"
    break;

  case 498:
#line 1743 "dhcp4_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 2977 "dhcp4_parser.cc"
    break;

  case 510:
#line 1762 "dhcp4_parser.yy"
                         {
    ctx.unique("code", ctx.loc2pos(yystack_[2].location));
    ElementPtr code(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 2987 "dhcp4_parser.cc"
    break;

  case 512:
#line 1770 "dhcp4_parser.yy"
                      {
    ctx.unique("type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2996 "dhcp4_parser.cc"
    break;

  case 513:
#line 1773 "dhcp4_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 3006 "dhcp4_parser.cc"
    break;

  case 514:
#line 1779 "dhcp4_parser.yy"
                                      {
    ctx.unique("record-types", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3015 "dhcp4_parser.cc"
    break;

  case 515:
#line 1782 "dhcp4_parser.yy"
               {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 3025 "dhcp4_parser.cc"
    break;

  case 516:
#line 1788 "dhcp4_parser.yy"
             {
    ctx.unique("space", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3034 "dhcp4_parser.cc"
    break;

  case 517:
#line 1791 "dhcp4_parser.yy"
               {
    ElementPtr space(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 3044 "dhcp4_parser.cc"
    break;

  case 519:
#line 1799 "dhcp4_parser.yy"
                                    {
    ctx.unique("encapsulate", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3053 "dhcp4_parser.cc"
    break;

  case 520:
#line 1802 "dhcp4_parser.yy"
               {
    ElementPtr encap(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 3063 "dhcp4_parser.cc"
    break;

  case 521:
#line 1808 "dhcp4_parser.yy"
                                      {
    ctx.unique("array", ctx.loc2pos(yystack_[2].location));
    ElementPtr array(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 3073 "dhcp4_parser.cc"
    break;

  case 522:
#line 1818 "dhcp4_parser.yy"
                              {
    ctx.unique("option-data", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 3085 "dhcp4_parser.cc"
    break;

  case 523:
#line 1824 "dhcp4_parser.yy"
                                                                 {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3094 "dhcp4_parser.cc"
    break;

  case 528:
#line 1839 "dhcp4_parser.yy"
                                                             {
                              ctx.warnAboutExtraCommas(yystack_[0].location);
                              }
#line 3102 "dhcp4_parser.cc"
    break;

  case 529:
#line 1846 "dhcp4_parser.yy"
                                  {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3112 "dhcp4_parser.cc"
    break;

  case 530:
#line 1850 "dhcp4_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 3121 "dhcp4_parser.cc"
    break;

  case 531:
#line 1858 "dhcp4_parser.yy"
                                {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3131 "dhcp4_parser.cc"
    break;

  case 532:
#line 1862 "dhcp4_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 3140 "dhcp4_parser.cc"
    break;

  case 537:
#line 1878 "dhcp4_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3148 "dhcp4_parser.cc"
    break;

  case 548:
#line 1898 "dhcp4_parser.yy"
                       {
    ctx.unique("data", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3157 "dhcp4_parser.cc"
    break;

  case 549:
#line 1901 "dhcp4_parser.yy"
               {
    ElementPtr data(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 3167 "dhcp4_parser.cc"
    break;

  case 552:
#line 1911 "dhcp4_parser.yy"
                                                 {
    ctx.unique("csv-format", ctx.loc2pos(yystack_[2].location));
    ElementPtr space(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 3177 "dhcp4_parser.cc"
    break;

  case 553:
#line 1917 "dhcp4_parser.yy"
                                                   {
    ctx.unique("always-send", ctx.loc2pos(yystack_[2].location));
    ElementPtr persist(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 3187 "dhcp4_parser.cc"
    break;

  case 554:
#line 1926 "dhcp4_parser.yy"
                  {
    ctx.unique("pools", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 3199 "dhcp4_parser.cc"
    break;

  case 555:
#line 1932 "dhcp4_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3208 "dhcp4_parser.cc"
    break;

  case 560:
#line 1945 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 3216 "dhcp4_parser.cc"
    break;

  case 561:
#line 1950 "dhcp4_parser.yy"
                                {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3226 "dhcp4_parser.cc"
    break;

  case 562:
#line 1954 "dhcp4_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3236 "dhcp4_parser.cc"
    break;

  case 563:
#line 1960 "dhcp4_parser.yy"
                          {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3246 "dhcp4_parser.cc"
    break;

  case 564:
#line 1964 "dhcp4_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3256 "dhcp4_parser.cc"
    break;

  case 567:
#line 1972 "dhcp4_parser.yy"
                               {
               ctx.warnAboutExtraCommas(yystack_[0].location);
               }
#line 3264 "dhcp4_parser.cc"
    break;

  case 575:
#line 1986 "dhcp4_parser.yy"
                 {
    ctx.unique("pool", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3273 "dhcp4_parser.cc"
    break;

  case 576:
#line 1989 "dhcp4_parser.yy"
               {
    ElementPtr pool(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 3283 "dhcp4_parser.cc"
    break;

  case 577:
#line 1995 "dhcp4_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3291 "dhcp4_parser.cc"
    break;

  case 578:
#line 1997 "dhcp4_parser.yy"
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
#line 3318 "dhcp4_parser.cc"
    break;

  case 579:
#line 2020 "dhcp4_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3326 "dhcp4_parser.cc"
    break;

  case 580:
#line 2022 "dhcp4_parser.yy"
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
#line 3355 "dhcp4_parser.cc"
    break;

  case 581:
#line 2050 "dhcp4_parser.yy"
                           {
    ctx.unique("reservations", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 3367 "dhcp4_parser.cc"
    break;

  case 582:
#line 2056 "dhcp4_parser.yy"
                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3376 "dhcp4_parser.cc"
    break;

  case 587:
#line 2067 "dhcp4_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 3384 "dhcp4_parser.cc"
    break;

  case 588:
#line 2072 "dhcp4_parser.yy"
                            {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3394 "dhcp4_parser.cc"
    break;

  case 589:
#line 2076 "dhcp4_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 3403 "dhcp4_parser.cc"
    break;

  case 590:
#line 2081 "dhcp4_parser.yy"
                                {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3413 "dhcp4_parser.cc"
    break;

  case 591:
#line 2085 "dhcp4_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 3422 "dhcp4_parser.cc"
    break;

  case 596:
#line 2096 "dhcp4_parser.yy"
                                         {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3430 "dhcp4_parser.cc"
    break;

  case 612:
#line 2119 "dhcp4_parser.yy"
                         {
    ctx.unique("next-server", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3439 "dhcp4_parser.cc"
    break;

  case 613:
#line 2122 "dhcp4_parser.yy"
               {
    ElementPtr next_server(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("next-server", next_server);
    ctx.leave();
}
#line 3449 "dhcp4_parser.cc"
    break;

  case 614:
#line 2128 "dhcp4_parser.yy"
                                 {
    ctx.unique("server-hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3458 "dhcp4_parser.cc"
    break;

  case 615:
#line 2131 "dhcp4_parser.yy"
               {
    ElementPtr srv(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-hostname", srv);
    ctx.leave();
}
#line 3468 "dhcp4_parser.cc"
    break;

  case 616:
#line 2137 "dhcp4_parser.yy"
                               {
    ctx.unique("boot-file-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3477 "dhcp4_parser.cc"
    break;

  case 617:
#line 2140 "dhcp4_parser.yy"
               {
    ElementPtr bootfile(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("boot-file-name", bootfile);
    ctx.leave();
}
#line 3487 "dhcp4_parser.cc"
    break;

  case 618:
#line 2146 "dhcp4_parser.yy"
                       {
    ctx.unique("ip-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3496 "dhcp4_parser.cc"
    break;

  case 619:
#line 2149 "dhcp4_parser.yy"
               {
    ElementPtr addr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 3506 "dhcp4_parser.cc"
    break;

  case 620:
#line 2155 "dhcp4_parser.yy"
                           {
    ctx.unique("ip-addresses", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3518 "dhcp4_parser.cc"
    break;

  case 621:
#line 2161 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3527 "dhcp4_parser.cc"
    break;

  case 622:
#line 2166 "dhcp4_parser.yy"
           {
    ctx.unique("duid", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3536 "dhcp4_parser.cc"
    break;

  case 623:
#line 2169 "dhcp4_parser.yy"
               {
    ElementPtr d(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 3546 "dhcp4_parser.cc"
    break;

  case 624:
#line 2175 "dhcp4_parser.yy"
                       {
    ctx.unique("hw-address", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3555 "dhcp4_parser.cc"
    break;

  case 625:
#line 2178 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 3565 "dhcp4_parser.cc"
    break;

  case 626:
#line 2184 "dhcp4_parser.yy"
                           {
    ctx.unique("client-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3574 "dhcp4_parser.cc"
    break;

  case 627:
#line 2187 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-id", hw);
    ctx.leave();
}
#line 3584 "dhcp4_parser.cc"
    break;

  case 628:
#line 2193 "dhcp4_parser.yy"
                             {
    ctx.unique("circuit-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3593 "dhcp4_parser.cc"
    break;

  case 629:
#line 2196 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("circuit-id", hw);
    ctx.leave();
}
#line 3603 "dhcp4_parser.cc"
    break;

  case 630:
#line 2202 "dhcp4_parser.yy"
                       {
    ctx.unique("flex-id", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3612 "dhcp4_parser.cc"
    break;

  case 631:
#line 2205 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 3622 "dhcp4_parser.cc"
    break;

  case 632:
#line 2211 "dhcp4_parser.yy"
                   {
    ctx.unique("hostname", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3631 "dhcp4_parser.cc"
    break;

  case 633:
#line 2214 "dhcp4_parser.yy"
               {
    ElementPtr host(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 3641 "dhcp4_parser.cc"
    break;

  case 634:
#line 2220 "dhcp4_parser.yy"
                                           {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3653 "dhcp4_parser.cc"
    break;

  case 635:
#line 2226 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3662 "dhcp4_parser.cc"
    break;

  case 636:
#line 2234 "dhcp4_parser.yy"
             {
    ctx.unique("relay", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 3674 "dhcp4_parser.cc"
    break;

  case 637:
#line 2240 "dhcp4_parser.yy"
                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3683 "dhcp4_parser.cc"
    break;

  case 640:
#line 2252 "dhcp4_parser.yy"
                               {
    ctx.unique("client-classes", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 3695 "dhcp4_parser.cc"
    break;

  case 641:
#line 2258 "dhcp4_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3704 "dhcp4_parser.cc"
    break;

  case 644:
#line 2265 "dhcp4_parser.yy"
                                               {
                       ctx.warnAboutExtraCommas(yystack_[0].location);
                       }
#line 3712 "dhcp4_parser.cc"
    break;

  case 645:
#line 2270 "dhcp4_parser.yy"
                                   {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3722 "dhcp4_parser.cc"
    break;

  case 646:
#line 2274 "dhcp4_parser.yy"
                                     {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3732 "dhcp4_parser.cc"
    break;

  case 651:
#line 2286 "dhcp4_parser.yy"
                                          {
        ctx.warnAboutExtraCommas(yystack_[0].location);
        }
#line 3740 "dhcp4_parser.cc"
    break;

  case 667:
#line 2309 "dhcp4_parser.yy"
                        {
    ctx.unique("test", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3749 "dhcp4_parser.cc"
    break;

  case 668:
#line 2312 "dhcp4_parser.yy"
               {
    ElementPtr test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 3759 "dhcp4_parser.cc"
    break;

  case 669:
#line 2318 "dhcp4_parser.yy"
                                                 {
    ctx.unique("only-if-required", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 3769 "dhcp4_parser.cc"
    break;

  case 670:
#line 2326 "dhcp4_parser.yy"
                                         {
    ctx.unique("dhcp4o6-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 3779 "dhcp4_parser.cc"
    break;

  case 671:
#line 2334 "dhcp4_parser.yy"
                               {
    ctx.unique("control-socket", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 3791 "dhcp4_parser.cc"
    break;

  case 672:
#line 2340 "dhcp4_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3800 "dhcp4_parser.cc"
    break;

  case 675:
#line 2347 "dhcp4_parser.yy"
                                                   {
                          ctx.warnAboutExtraCommas(yystack_[0].location);
                          }
#line 3808 "dhcp4_parser.cc"
    break;

  case 681:
#line 2359 "dhcp4_parser.yy"
                                 {
    ctx.unique("socket-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3817 "dhcp4_parser.cc"
    break;

  case 682:
#line 2362 "dhcp4_parser.yy"
               {
    ElementPtr stype(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 3827 "dhcp4_parser.cc"
    break;

  case 683:
#line 2368 "dhcp4_parser.yy"
                                 {
    ctx.unique("socket-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3836 "dhcp4_parser.cc"
    break;

  case 684:
#line 2371 "dhcp4_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 3846 "dhcp4_parser.cc"
    break;

  case 685:
#line 2380 "dhcp4_parser.yy"
                                       {
    ctx.unique("dhcp-queue-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr qc(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-queue-control", qc);
    ctx.stack_.push_back(qc);
    ctx.enter(ctx.DHCP_QUEUE_CONTROL);
}
#line 3858 "dhcp4_parser.cc"
    break;

  case 686:
#line 2386 "dhcp4_parser.yy"
                                                           {
    // The enable queue parameter is required.
    ctx.require("enable-queue", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3869 "dhcp4_parser.cc"
    break;

  case 689:
#line 2395 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 3877 "dhcp4_parser.cc"
    break;

  case 696:
#line 2408 "dhcp4_parser.yy"
                                         {
    ctx.unique("enable-queue", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-queue", b);
}
#line 3887 "dhcp4_parser.cc"
    break;

  case 697:
#line 2414 "dhcp4_parser.yy"
                       {
    ctx.unique("queue-type", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3896 "dhcp4_parser.cc"
    break;

  case 698:
#line 2417 "dhcp4_parser.yy"
               {
    ElementPtr qt(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("queue-type", qt);
    ctx.leave();
}
#line 3906 "dhcp4_parser.cc"
    break;

  case 699:
#line 2423 "dhcp4_parser.yy"
                                 {
    ctx.unique("capacity", ctx.loc2pos(yystack_[2].location));
    ElementPtr c(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("capacity", c);
}
#line 3916 "dhcp4_parser.cc"
    break;

  case 700:
#line 2429 "dhcp4_parser.yy"
                            {
    ctx.unique(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3925 "dhcp4_parser.cc"
    break;

  case 701:
#line 2432 "dhcp4_parser.yy"
              {
    ctx.stack_.back()->set(yystack_[3].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3934 "dhcp4_parser.cc"
    break;

  case 702:
#line 2439 "dhcp4_parser.yy"
                     {
    ctx.unique("dhcp-ddns", ctx.loc2pos(yystack_[0].location));
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 3946 "dhcp4_parser.cc"
    break;

  case 703:
#line 2445 "dhcp4_parser.yy"
                                                       {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3957 "dhcp4_parser.cc"
    break;

  case 704:
#line 2452 "dhcp4_parser.yy"
                              {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3967 "dhcp4_parser.cc"
    break;

  case 705:
#line 2456 "dhcp4_parser.yy"
                                  {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3977 "dhcp4_parser.cc"
    break;

  case 708:
#line 2464 "dhcp4_parser.yy"
                                         {
                    ctx.warnAboutExtraCommas(yystack_[0].location);
                    }
#line 3985 "dhcp4_parser.cc"
    break;

  case 727:
#line 2489 "dhcp4_parser.yy"
                                             {
    ctx.unique("enable-updates", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 3995 "dhcp4_parser.cc"
    break;

  case 728:
#line 2495 "dhcp4_parser.yy"
                     {
    ctx.unique("server-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4004 "dhcp4_parser.cc"
    break;

  case 729:
#line 2498 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 4014 "dhcp4_parser.cc"
    break;

  case 730:
#line 2504 "dhcp4_parser.yy"
                                       {
    ctx.unique("server-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 4024 "dhcp4_parser.cc"
    break;

  case 731:
#line 2510 "dhcp4_parser.yy"
                     {
    ctx.unique("sender-ip", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4033 "dhcp4_parser.cc"
    break;

  case 732:
#line 2513 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 4043 "dhcp4_parser.cc"
    break;

  case 733:
#line 2519 "dhcp4_parser.yy"
                                       {
    ctx.unique("sender-port", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 4053 "dhcp4_parser.cc"
    break;

  case 734:
#line 2525 "dhcp4_parser.yy"
                                             {
    ctx.unique("max-queue-size", ctx.loc2pos(yystack_[2].location));
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 4063 "dhcp4_parser.cc"
    break;

  case 735:
#line 2531 "dhcp4_parser.yy"
                           {
    ctx.unique("ncr-protocol", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 4072 "dhcp4_parser.cc"
    break;

  case 736:
#line 2534 "dhcp4_parser.yy"
                           {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4081 "dhcp4_parser.cc"
    break;

  case 737:
#line 2540 "dhcp4_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 4087 "dhcp4_parser.cc"
    break;

  case 738:
#line 2541 "dhcp4_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 4093 "dhcp4_parser.cc"
    break;

  case 739:
#line 2544 "dhcp4_parser.yy"
                       {
    ctx.unique("ncr-format", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NCR_FORMAT);
}
#line 4102 "dhcp4_parser.cc"
    break;

  case 740:
#line 2547 "dhcp4_parser.yy"
             {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 4112 "dhcp4_parser.cc"
    break;

  case 741:
#line 2554 "dhcp4_parser.yy"
                                         {
    ctx.unique("qualifying-suffix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4121 "dhcp4_parser.cc"
    break;

  case 742:
#line 2557 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 4131 "dhcp4_parser.cc"
    break;

  case 743:
#line 2564 "dhcp4_parser.yy"
                                                         {
    ctx.unique("override-no-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 4141 "dhcp4_parser.cc"
    break;

  case 744:
#line 2571 "dhcp4_parser.yy"
                                                                 {
    ctx.unique("override-client-update", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 4151 "dhcp4_parser.cc"
    break;

  case 745:
#line 2578 "dhcp4_parser.yy"
                                             {
    ctx.unique("replace-client-name", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 4160 "dhcp4_parser.cc"
    break;

  case 746:
#line 2581 "dhcp4_parser.yy"
                                       {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 4169 "dhcp4_parser.cc"
    break;

  case 747:
#line 2587 "dhcp4_parser.yy"
                                       {
    ctx.unique("generated-prefix", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4178 "dhcp4_parser.cc"
    break;

  case 748:
#line 2590 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 4188 "dhcp4_parser.cc"
    break;

  case 749:
#line 2597 "dhcp4_parser.yy"
                                         {
    ctx.unique("hostname-char-set", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4197 "dhcp4_parser.cc"
    break;

  case 750:
#line 2600 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 4207 "dhcp4_parser.cc"
    break;

  case 751:
#line 2607 "dhcp4_parser.yy"
                                                         {
    ctx.unique("hostname-char-replacement", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4216 "dhcp4_parser.cc"
    break;

  case 752:
#line 2610 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 4226 "dhcp4_parser.cc"
    break;

  case 753:
#line 2619 "dhcp4_parser.yy"
                               {
    ctx.unique("config-control", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 4238 "dhcp4_parser.cc"
    break;

  case 754:
#line 2625 "dhcp4_parser.yy"
                                                            {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4248 "dhcp4_parser.cc"
    break;

  case 755:
#line 2631 "dhcp4_parser.yy"
                                   {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 4258 "dhcp4_parser.cc"
    break;

  case 756:
#line 2635 "dhcp4_parser.yy"
                                       {
    // No config_control params are required
    // parsing completed
}
#line 4267 "dhcp4_parser.cc"
    break;

  case 759:
#line 2643 "dhcp4_parser.yy"
                                                   {
                         ctx.warnAboutExtraCommas(yystack_[0].location);
                         }
#line 4275 "dhcp4_parser.cc"
    break;

  case 762:
#line 2653 "dhcp4_parser.yy"
                                   {
    ctx.unique("config-databases", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 4287 "dhcp4_parser.cc"
    break;

  case 763:
#line 2659 "dhcp4_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4296 "dhcp4_parser.cc"
    break;

  case 764:
#line 2664 "dhcp4_parser.yy"
                                                             {
    ctx.unique("config-fetch-wait-time", ctx.loc2pos(yystack_[2].location));
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-fetch-wait-time", value);
}
#line 4306 "dhcp4_parser.cc"
    break;

  case 765:
#line 2672 "dhcp4_parser.yy"
                 {
    ctx.unique("loggers", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 4318 "dhcp4_parser.cc"
    break;

  case 766:
#line 2678 "dhcp4_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4327 "dhcp4_parser.cc"
    break;

  case 769:
#line 2687 "dhcp4_parser.yy"
                                       {
                   ctx.warnAboutExtraCommas(yystack_[0].location);
                   }
#line 4335 "dhcp4_parser.cc"
    break;

  case 770:
#line 2693 "dhcp4_parser.yy"
                             {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 4345 "dhcp4_parser.cc"
    break;

  case 771:
#line 2697 "dhcp4_parser.yy"
                               {
    ctx.stack_.pop_back();
}
#line 4353 "dhcp4_parser.cc"
    break;

  case 774:
#line 2703 "dhcp4_parser.yy"
                                   {
                 ctx.warnAboutExtraCommas(yystack_[0].location);
                 }
#line 4361 "dhcp4_parser.cc"
    break;

  case 782:
#line 2717 "dhcp4_parser.yy"
                                     {
    ctx.unique("debuglevel", ctx.loc2pos(yystack_[2].location));
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 4371 "dhcp4_parser.cc"
    break;

  case 783:
#line 2723 "dhcp4_parser.yy"
                   {
    ctx.unique("severity", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4380 "dhcp4_parser.cc"
    break;

  case 784:
#line 2726 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 4390 "dhcp4_parser.cc"
    break;

  case 785:
#line 2732 "dhcp4_parser.yy"
                                    {
    ctx.unique("output_options", ctx.loc2pos(yystack_[0].location));
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 4402 "dhcp4_parser.cc"
    break;

  case 786:
#line 2738 "dhcp4_parser.yy"
                                                                    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4411 "dhcp4_parser.cc"
    break;

  case 789:
#line 2745 "dhcp4_parser.yy"
                                                               {
                               ctx.warnAboutExtraCommas(yystack_[0].location);
                               }
#line 4419 "dhcp4_parser.cc"
    break;

  case 790:
#line 2750 "dhcp4_parser.yy"
                             {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 4429 "dhcp4_parser.cc"
    break;

  case 791:
#line 2754 "dhcp4_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 4437 "dhcp4_parser.cc"
    break;

  case 794:
#line 2760 "dhcp4_parser.yy"
                                             {
                      ctx.warnAboutExtraCommas(yystack_[0].location);
                      }
#line 4445 "dhcp4_parser.cc"
    break;

  case 800:
#line 2772 "dhcp4_parser.yy"
               {
    ctx.unique("output", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4454 "dhcp4_parser.cc"
    break;

  case 801:
#line 2775 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 4464 "dhcp4_parser.cc"
    break;

  case 802:
#line 2781 "dhcp4_parser.yy"
                           {
    ctx.unique("flush", ctx.loc2pos(yystack_[2].location));
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 4474 "dhcp4_parser.cc"
    break;

  case 803:
#line 2787 "dhcp4_parser.yy"
                               {
    ctx.unique("maxsize", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 4484 "dhcp4_parser.cc"
    break;

  case 804:
#line 2793 "dhcp4_parser.yy"
                             {
    ctx.unique("maxver", ctx.loc2pos(yystack_[2].location));
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 4494 "dhcp4_parser.cc"
    break;

  case 805:
#line 2799 "dhcp4_parser.yy"
                 {
    ctx.unique("pattern", ctx.loc2pos(yystack_[0].location));
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4503 "dhcp4_parser.cc"
    break;

  case 806:
#line 2802 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pattern", sev);
    ctx.leave();
}
#line 4513 "dhcp4_parser.cc"
    break;

  case 807:
#line 2808 "dhcp4_parser.yy"
                             {
    ctx.unique("compatibility", ctx.loc2pos(yystack_[0].location));
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("compatibility", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.COMPATIBILITY);
}
#line 4525 "dhcp4_parser.cc"
    break;

  case 808:
#line 2814 "dhcp4_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 4534 "dhcp4_parser.cc"
    break;

  case 811:
#line 2821 "dhcp4_parser.yy"
                                                 {
                        ctx.warnAboutExtraCommas(yystack_[0].location);
                        }
#line 4542 "dhcp4_parser.cc"
    break;

  case 814:
#line 2830 "dhcp4_parser.yy"
                                                             {
    ctx.unique("lenient-option-parsing", ctx.loc2pos(yystack_[2].location));
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lenient-option-parsing", b);
}
#line 4552 "dhcp4_parser.cc"
    break;


#line 4556 "dhcp4_parser.cc"

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
  Dhcp4Parser::error (const syntax_error& yyexc)
  {
    error (yyexc.location, yyexc.what ());
  }

  // Generate an error message.
  std::string
  Dhcp4Parser::yysyntax_error_ (state_type yystate, const symbol_type& yyla) const
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


  const short Dhcp4Parser::yypact_ninf_ = -959;

  const signed char Dhcp4Parser::yytable_ninf_ = -1;

  const short
  Dhcp4Parser::yypact_[] =
  {
     391,  -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,
    -959,  -959,  -959,  -959,    28,    38,    26,    82,    92,    94,
     110,   122,   161,   187,   201,   214,   225,   266,  -959,  -959,
    -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,
    -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,
    -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,
    -959,  -959,  -959,  -959,    38,  -151,   186,   184,    36,   626,
     -14,    67,   -34,   252,   285,   -92,   250,   171,  -959,   275,
     282,   288,    59,   286,  -959,    41,  -959,  -959,  -959,  -959,
     307,   313,   335,  -959,  -959,  -959,  -959,  -959,  -959,   338,
     339,   343,   344,   349,   361,   362,   385,   387,   388,   413,
    -959,   415,   418,   419,   421,   422,  -959,  -959,  -959,   423,
     424,   425,  -959,  -959,  -959,   426,  -959,  -959,  -959,  -959,
     427,   428,   429,  -959,  -959,  -959,  -959,  -959,   430,  -959,
    -959,  -959,  -959,  -959,  -959,   431,   433,   434,  -959,  -959,
     438,  -959,    56,  -959,  -959,  -959,  -959,  -959,  -959,  -959,
    -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,
    -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,
    -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,
    -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,
    -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,
    -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,
     439,  -959,    85,  -959,  -959,  -959,  -959,  -959,  -959,  -959,
    -959,  -959,  -959,  -959,  -959,  -959,   440,  -959,  -959,  -959,
    -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,
    -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,
    -959,  -959,  -959,  -959,   102,  -959,  -959,  -959,  -959,  -959,
    -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,
    -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,
    -959,  -959,   105,  -959,  -959,  -959,  -959,  -959,  -959,  -959,
    -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,   293,
     326,  -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,
    -959,  -959,  -959,   302,  -959,  -959,   441,  -959,  -959,  -959,
     442,  -959,  -959,   445,   444,  -959,  -959,  -959,  -959,  -959,
    -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,   450,   452,
    -959,  -959,  -959,  -959,   449,   455,  -959,  -959,  -959,  -959,
    -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,   138,  -959,
    -959,  -959,   457,  -959,  -959,   463,  -959,   466,   468,  -959,
    -959,   469,   470,  -959,  -959,  -959,  -959,  -959,  -959,  -959,
     145,  -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,
    -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,   471,   146,
    -959,  -959,  -959,  -959,    38,    38,  -959,   260,   474,  -959,
    -959,   475,   482,   483,   287,   290,   291,   492,   493,   496,
     499,   500,   501,   308,   311,   312,   314,   315,   319,   309,
     321,   322,   327,   329,   512,   330,   331,   332,   333,   337,
     513,   514,   529,   345,   350,   353,   533,   536,   537,   357,
     541,   547,   554,   555,   360,   363,   367,   559,   566,   569,
     570,   571,   390,   587,   588,   589,   590,   591,   592,   395,
     396,   397,   596,   597,  -959,   184,  -959,   598,   599,   600,
     403,    36,  -959,   602,   603,   604,   605,   606,   607,   412,
     609,   610,   611,   626,  -959,   612,   -14,  -959,   613,   614,
     615,   616,   618,   620,   621,   622,  -959,    67,  -959,   623,
     624,   432,   625,   627,   630,   435,  -959,   252,   631,   436,
     443,  -959,   285,   632,   636,   -60,  -959,   446,   637,   638,
     447,   639,   451,   459,   640,   642,   448,   460,   645,   657,
     659,   661,   250,  -959,   662,   467,   171,  -959,  -959,  -959,
     664,   663,   665,   670,   671,  -959,  -959,  -959,   472,   480,
     481,   674,   686,   689,  -959,  -959,  -959,  -959,  -959,  -959,
    -959,  -959,  -959,  -959,  -959,   497,  -959,  -959,  -959,  -959,
    -959,   -91,   507,   511,  -959,  -959,  -959,   690,   707,   708,
    -959,   709,   713,   516,   274,  -959,  -959,  -959,   716,   717,
     719,   726,   725,  -959,   727,   731,   732,   734,   534,   543,
    -959,  -959,  -959,   740,   739,  -959,   742,   188,    60,  -959,
    -959,   549,   550,   551,   747,   556,   557,  -959,   742,   558,
     746,  -959,   560,  -959,   742,   561,   562,   563,   564,   565,
     567,   568,  -959,   572,   573,  -959,   574,   575,   576,  -959,
    -959,   577,  -959,  -959,  -959,   578,   713,  -959,  -959,   579,
     580,  -959,   581,  -959,  -959,    13,   465,  -959,  -959,   -91,
     582,   583,   584,  -959,   749,  -959,  -959,    38,   184,   171,
      36,   741,  -959,  -959,  -959,   117,   117,   751,  -959,  -959,
    -959,  -959,  -959,  -959,  -959,  -959,  -959,   761,   762,   763,
     777,  -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,    80,
     778,   779,   780,   263,   -17,    75,    79,   250,  -959,  -959,
     781,  -146,  -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,
    -959,  -959,  -959,   782,  -959,  -959,  -959,  -959,   205,  -959,
    -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,
    -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,
    -959,  -959,  -959,  -959,  -959,  -959,  -959,   751,  -959,   173,
     189,   215,  -959,   222,  -959,  -959,  -959,  -959,  -959,  -959,
     786,   787,   788,   789,   790,   791,   794,  -959,   795,  -959,
    -959,  -959,  -959,  -959,   226,  -959,  -959,  -959,  -959,  -959,
    -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,
    -959,  -959,  -959,  -959,   228,  -959,   796,   666,  -959,  -959,
     797,   798,  -959,  -959,   799,   801,  -959,  -959,   800,   804,
    -959,  -959,   802,   806,  -959,  -959,  -959,  -959,  -959,  -959,
      84,  -959,  -959,  -959,  -959,  -959,  -959,  -959,   115,  -959,
    -959,   805,   807,  -959,  -959,   808,   809,  -959,   811,   812,
     813,   814,   815,   816,   262,  -959,  -959,  -959,  -959,  -959,
    -959,  -959,   817,   818,   819,  -959,   264,  -959,  -959,  -959,
    -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,   268,  -959,
    -959,  -959,   820,  -959,   822,  -959,  -959,  -959,   279,  -959,
    -959,  -959,  -959,  -959,   295,  -959,   125,  -959,   823,  -959,
     296,  -959,  -959,   601,  -959,   824,   810,  -959,  -959,  -959,
    -959,   821,   825,  -959,  -959,  -959,   828,   741,  -959,   829,
     830,   831,   832,   628,   635,   641,   643,   644,   646,   647,
     834,   648,   835,   836,   838,   839,   117,  -959,  -959,   117,
    -959,   751,   626,  -959,   761,   252,  -959,   762,   285,  -959,
     763,  1225,  -959,   777,    80,  -959,   278,   778,  -959,    67,
    -959,   779,   -92,  -959,   780,   649,   650,   651,   652,   653,
     654,   263,  -959,   655,   656,   658,   -17,  -959,   851,   855,
      75,  -959,   660,   856,   667,   857,    79,  -959,  -959,   191,
     781,  -959,   668,  -146,  -959,  -959,   858,   860,   -14,  -959,
     782,   861,  -959,  -959,   669,  -959,   351,   672,   673,   675,
    -959,  -959,  -959,  -959,  -959,  -959,  -959,   365,  -959,   676,
     677,   678,   679,  -959,   297,  -959,   306,  -959,   865,  -959,
     871,  -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,
    -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,
    -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,
    -959,  -959,  -959,  -959,  -959,   310,  -959,  -959,  -959,  -959,
    -959,  -959,  -959,  -959,  -959,  -959,  -959,   862,  -959,  -959,
    -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,
     872,   866,  -959,  -959,  -959,  -959,  -959,   873,  -959,   316,
    -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,
    -959,  -959,   683,   684,  -959,  -959,   685,  -959,    38,  -959,
    -959,   881,  -959,  -959,  -959,  -959,  -959,   317,  -959,  -959,
    -959,  -959,  -959,  -959,  -959,  -959,   687,   318,  -959,   742,
    -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,
    -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,
    1225,  -959,   883,   688,  -959,   278,  -959,  -959,  -959,  -959,
    -959,  -959,   884,   691,   885,   191,  -959,  -959,  -959,  -959,
    -959,   693,  -959,  -959,   888,  -959,   695,  -959,  -959,   889,
    -959,  -959,   144,  -959,   -38,   889,  -959,  -959,   893,   895,
     896,  -959,   325,  -959,  -959,  -959,  -959,  -959,  -959,  -959,
     898,   701,   710,   718,   904,   -38,  -959,   714,  -959,  -959,
    -959,   720,  -959,  -959,  -959
  };

  const short
  Dhcp4Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     1,    44,
      36,    32,    31,    28,    29,    30,    35,     3,    33,    34,
      59,     5,    65,     7,   189,     9,   355,    11,   563,    13,
     590,    15,   483,    17,   492,    19,   531,    21,   317,    23,
     704,    25,   755,    27,    46,    39,     0,     0,     0,     0,
       0,   592,     0,   494,   533,     0,     0,     0,    48,     0,
      47,     0,     0,    40,    61,     0,    63,   753,   177,   204,
       0,     0,     0,   612,   614,   616,   202,   212,   214,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     145,     0,     0,     0,     0,     0,   154,   161,   163,     0,
       0,     0,   346,   481,   522,     0,   429,   577,   579,   422,
       0,     0,     0,   279,   640,   581,   308,   329,     0,   294,
     671,   685,   702,   167,   169,     0,     0,     0,   765,   807,
       0,   133,     0,    67,    70,    71,    72,    73,    74,   108,
     109,   110,   111,   112,    75,   103,   132,    92,    93,    94,
     116,   117,   118,   119,   120,   121,   122,   123,   114,   115,
     124,   125,   126,   128,   129,   130,    78,    79,   100,    80,
      81,    82,   127,    86,    87,    76,   105,   106,   107,   104,
      77,    84,    85,    98,    99,   101,    95,    96,    97,    83,
      88,    89,    90,    91,   102,   113,   131,   191,   193,   197,
       0,   188,     0,   179,   182,   183,   184,   185,   186,   187,
     407,   409,   411,   554,   405,   413,     0,   417,   415,   636,
     404,   360,   361,   362,   363,   364,   388,   389,   390,   391,
     392,   378,   379,   393,   394,   395,   396,   397,   398,   399,
     400,   401,   402,   403,     0,   357,   367,   383,   384,   385,
     368,   370,   371,   374,   375,   376,   373,   369,   365,   366,
     386,   387,   372,   380,   381,   382,   377,   575,   574,   570,
     571,   569,     0,   565,   568,   572,   573,   634,   622,   624,
     628,   626,   632,   630,   618,   611,   605,   609,   610,     0,
     593,   594,   606,   607,   608,   602,   597,   603,   599,   600,
     601,   604,   598,     0,   512,   257,     0,   516,   514,   519,
       0,   508,   509,     0,   495,   496,   499,   511,   500,   501,
     502,   518,   503,   504,   505,   506,   507,   548,     0,     0,
     546,   547,   550,   551,     0,   534,   535,   538,   539,   540,
     541,   542,   543,   544,   545,   325,   327,   322,     0,   319,
     323,   324,     0,   741,   728,     0,   731,     0,     0,   735,
     739,     0,     0,   745,   747,   749,   751,   726,   724,   725,
       0,   706,   709,   710,   711,   712,   713,   714,   715,   716,
     721,   717,   718,   719,   720,   722,   723,   762,     0,     0,
     757,   760,   761,    45,    50,     0,    37,    43,     0,    64,
      60,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    58,    69,    66,     0,     0,     0,
       0,   181,   190,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   359,   356,     0,   567,   564,     0,     0,
       0,     0,     0,     0,     0,     0,   591,   596,   484,     0,
       0,     0,     0,     0,     0,     0,   493,   498,     0,     0,
       0,   532,   537,     0,     0,   321,   318,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   708,   705,     0,     0,   759,   756,    49,    41,
       0,     0,     0,     0,     0,   148,   149,   150,     0,     0,
       0,     0,     0,     0,   134,   135,   136,   137,   138,   139,
     140,   141,   142,   143,   144,     0,   172,   173,   151,   152,
     153,     0,     0,     0,   165,   166,   171,     0,     0,     0,
     147,     0,     0,     0,     0,   419,   420,   421,     0,     0,
       0,     0,     0,   670,     0,     0,     0,     0,     0,     0,
     174,   175,   176,     0,     0,    68,     0,     0,     0,   201,
     180,     0,     0,     0,     0,     0,     0,   428,     0,     0,
       0,   358,     0,   566,     0,     0,     0,     0,     0,     0,
       0,     0,   595,     0,     0,   510,     0,     0,     0,   521,
     497,     0,   552,   553,   536,     0,     0,   320,   727,     0,
       0,   730,     0,   733,   734,     0,     0,   743,   744,     0,
       0,     0,     0,   707,     0,   764,   758,     0,     0,     0,
       0,     0,   613,   615,   617,     0,     0,   216,   146,   156,
     157,   158,   159,   160,   155,   162,   164,   348,   485,   524,
     431,    38,   578,   580,   424,   425,   426,   427,   423,     0,
       0,   583,   310,     0,     0,     0,     0,     0,   168,   170,
       0,     0,    51,   192,   195,   196,   194,   199,   200,   198,
     408,   410,   412,   556,   406,   414,   418,   416,     0,   576,
     635,   623,   625,   629,   627,   633,   631,   619,   513,   258,
     517,   515,   520,   549,   326,   328,   742,   729,   732,   737,
     738,   736,   740,   746,   748,   750,   752,   216,    42,     0,
       0,     0,   210,     0,   206,   209,   245,   250,   252,   254,
       0,     0,     0,     0,     0,     0,     0,   265,     0,   271,
     273,   275,   277,   244,     0,   223,   226,   227,   228,   229,
     230,   231,   232,   233,   234,   235,   236,   237,   238,   239,
     240,   241,   242,   243,     0,   221,     0,   217,   218,   353,
       0,   349,   350,   490,     0,   486,   487,   529,     0,   525,
     526,   436,     0,   432,   433,   289,   290,   291,   292,   293,
       0,   281,   284,   285,   286,   287,   288,   645,     0,   642,
     588,     0,   584,   585,   315,     0,   311,   312,     0,     0,
       0,     0,     0,     0,     0,   331,   334,   335,   336,   337,
     338,   339,     0,     0,     0,   304,     0,   296,   299,   300,
     301,   302,   303,   681,   683,   680,   678,   679,     0,   673,
     676,   677,     0,   697,     0,   700,   693,   694,     0,   687,
     690,   691,   692,   695,     0,   770,     0,   767,     0,   813,
       0,   809,   812,    53,   561,     0,   557,   558,   620,   638,
     639,     0,     0,    62,   754,   178,     0,   208,   205,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   225,   203,   213,     0,
     215,   220,     0,   347,   352,   494,   482,   489,   533,   523,
     528,     0,   430,   435,   283,   280,   647,   644,   641,   592,
     582,   587,     0,   309,   314,     0,     0,     0,     0,     0,
       0,   333,   330,     0,     0,     0,   298,   295,     0,     0,
     675,   672,     0,     0,     0,     0,   689,   686,   703,     0,
     769,   766,     0,   811,   808,    55,     0,    54,     0,   555,
     560,     0,   637,   763,     0,   207,     0,     0,     0,     0,
     256,   259,   260,   261,   262,   263,   264,     0,   270,     0,
       0,     0,     0,   224,     0,   219,     0,   351,     0,   488,
       0,   527,   480,   459,   460,   461,   444,   445,   464,   465,
     466,   467,   468,   447,   448,   469,   470,   471,   472,   473,
     474,   475,   476,   477,   478,   479,   441,   442,   443,   457,
     458,   454,   455,   456,   453,     0,   438,   446,   462,   463,
     449,   450,   451,   452,   434,   282,   667,     0,   662,   663,
     664,   665,   666,   655,   656,   660,   661,   657,   658,   659,
       0,   648,   649,   652,   653,   654,   643,     0,   586,     0,
     313,   340,   341,   342,   343,   344,   345,   332,   305,   306,
     307,   297,     0,     0,   674,   696,     0,   699,     0,   688,
     785,     0,   783,   781,   775,   779,   780,     0,   772,   777,
     778,   776,   768,   814,   810,    52,    57,     0,   559,     0,
     211,   247,   248,   249,   246,   251,   253,   255,   267,   268,
     269,   266,   272,   274,   276,   278,   222,   354,   491,   530,
     440,   437,     0,     0,   646,   651,   589,   316,   682,   684,
     698,   701,     0,     0,     0,   774,   771,    56,   562,   621,
     439,     0,   669,   650,     0,   782,     0,   773,   668,     0,
     784,   790,     0,   787,     0,   789,   786,   800,     0,     0,
       0,   805,     0,   792,   795,   796,   797,   798,   799,   788,
       0,     0,     0,     0,     0,   794,   791,     0,   802,   803,
     804,     0,   793,   801,   806
  };

  const short
  Dhcp4Parser::yypgoto_[] =
  {
    -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,
    -959,  -959,  -959,  -959,  -959,   -54,  -959,  -560,  -959,   271,
    -959,  -959,  -959,  -959,  -959,  -959,  -617,  -959,  -959,  -959,
     -67,  -959,  -959,  -959,  -959,  -959,  -959,  -959,   246,   477,
       4,    10,    23,   -40,   -23,   -12,    22,    25,    29,    33,
    -959,  -959,  -959,  -959,  -959,    35,    40,    43,    45,    46,
      47,  -959,   261,    50,  -959,    51,  -959,    53,    57,    58,
    -959,    61,  -959,    63,  -959,  -959,  -959,  -959,  -959,  -959,
    -959,   280,   461,  -959,  -959,  -959,  -959,  -959,  -959,  -959,
    -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,    32,
    -959,  -959,  -959,  -959,  -959,  -959,   196,  -959,    16,  -959,
    -684,    34,  -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,
    -959,  -959,   -33,  -959,  -959,  -959,  -959,  -959,  -959,  -959,
    -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,
    -959,  -959,  -959,  -959,  -959,    15,  -959,  -959,  -959,  -959,
    -959,  -959,  -959,  -959,   -18,  -959,  -959,  -959,  -959,  -959,
    -959,  -959,    19,  -959,  -959,  -959,    55,   498,  -959,  -959,
    -959,  -959,  -959,  -959,  -959,    52,  -959,  -959,  -959,  -959,
    -959,  -959,  -958,  -959,  -959,  -959,    74,  -959,  -959,  -959,
      83,   539,  -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,
    -956,  -959,   -65,  -959,    70,  -959,    64,    65,    68,    69,
    -959,  -959,  -959,  -959,  -959,  -959,  -959,    71,  -959,  -959,
    -134,   -46,  -959,  -959,  -959,  -959,  -959,    81,  -959,  -959,
    -959,    86,  -959,   520,  -959,   -63,  -959,  -959,  -959,  -959,
    -959,   -42,  -959,  -959,  -959,  -959,  -959,   -35,  -959,  -959,
    -959,    87,  -959,  -959,  -959,    88,  -959,   517,  -959,  -959,
    -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,    30,
    -959,  -959,  -959,    37,   546,  -959,  -959,   -51,  -959,    -8,
    -959,   -39,  -959,  -959,  -959,    72,  -959,  -959,  -959,    89,
    -959,   542,   -55,  -959,   -15,  -959,     3,  -959,   323,  -959,
    -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,
    -959,  -959,  -959,  -959,  -959,  -959,  -947,  -959,  -959,  -959,
    -959,  -959,    77,  -959,  -959,  -959,  -127,  -959,  -959,  -959,
    -959,  -959,  -959,  -959,  -959,    62,  -959,  -959,  -959,  -959,
    -959,  -959,  -959,    54,  -959,  -959,  -959,  -959,  -959,  -959,
    -959,  -959,  -959,  -959,   334,   515,  -959,  -959,  -959,  -959,
    -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,
    -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,  -959,
    -959,  -959,  -959,  -959,  -959,   374,   508,  -959,  -959,  -959,
    -959,  -959,  -959,    66,  -959,  -959,  -130,  -959,  -959,  -959,
    -959,  -959,  -959,  -149,  -959,  -959,  -166,  -959,  -959,  -959,
    -959,  -959,  -959,  -959,  -959,  -959,  -959,    73,  -959
  };

  const short
  Dhcp4Parser::yydefgoto_[] =
  {
      -1,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    36,    37,    38,    65,   712,
      82,    83,    39,    64,    79,    80,   733,   923,  1016,  1017,
     803,    41,    66,    85,   418,    86,    43,    67,   152,   153,
     154,   155,   156,   157,   158,   159,   160,   161,   162,   163,
     164,   165,   444,   166,   167,   168,   169,   170,   171,   172,
     173,   450,   704,   174,   451,   175,   452,   176,   177,   178,
     477,   179,   478,   180,   181,   182,   183,   184,   185,   186,
     422,   222,   223,    45,    68,   224,   487,   225,   488,   736,
     226,   489,   739,   227,   187,   430,   188,   423,   783,   784,
     785,   936,   189,   431,   190,   432,   826,   827,   828,   959,
     804,   805,   806,   939,  1164,   807,   940,   808,   941,   809,
     942,   810,   811,   520,   812,   813,   814,   815,   816,   817,
     818,   950,  1171,   819,   820,   952,   821,   953,   822,   954,
     823,   955,   191,   467,   850,   851,   852,   853,   854,   855,
     856,   192,   473,   886,   887,   888,   889,   890,   193,   470,
     865,   866,   867,   982,    59,    75,   368,   369,   370,   533,
     371,   534,   194,   471,   874,   875,   876,   877,   878,   879,
     880,   881,   195,   456,   830,   831,   832,   962,    47,    69,
     264,   265,   266,   497,   267,   493,   268,   494,   269,   495,
     270,   498,   271,   501,   272,   500,   196,   197,   198,   199,
     463,   718,   277,   200,   460,   842,   843,   844,   971,  1085,
    1086,   201,   457,    53,    72,   834,   835,   836,   965,    55,
      73,   333,   334,   335,   336,   337,   338,   339,   519,   340,
     523,   341,   522,   342,   343,   524,   344,   202,   458,   838,
     839,   840,   968,    57,    74,   354,   355,   356,   357,   358,
     528,   359,   360,   361,   362,   279,   496,   925,   926,   927,
    1018,    49,    70,   292,   293,   294,   505,   203,   461,   204,
     462,   205,   469,   861,   862,   863,   979,    51,    71,   309,
     310,   311,   206,   427,   207,   428,   208,   429,   315,   515,
     930,  1021,   316,   509,   317,   510,   318,   512,   319,   511,
     320,   514,   321,   513,   322,   508,   286,   502,   931,   209,
     468,   858,   859,   976,  1110,  1111,  1112,  1113,  1114,  1182,
    1115,   210,   211,   474,   898,   899,   900,   998,   901,   999,
     212,   475,   908,   909,   910,   911,  1003,   912,   913,  1005,
     213,   476,    61,    76,   390,   391,   392,   393,   539,   394,
     395,   541,   396,   397,   398,   544,   771,   399,   545,   400,
     538,   401,   402,   403,   548,   404,   549,   405,   550,   406,
     551,   214,   421,    63,    77,   409,   410,   411,   554,   412,
     215,   482,   916,   917,  1009,  1147,  1148,  1149,  1150,  1194,
    1151,  1192,  1212,  1213,  1214,  1222,  1223,  1224,  1230,  1225,
    1226,  1227,  1228,  1234,   216,   483,   920,   921,   922
  };

  const short
  Dhcp4Parser::yytable_[] =
  {
     151,   221,   240,   288,   305,   289,   331,   350,   367,   387,
      78,   352,   824,  1077,   283,  1078,   312,   228,   280,   295,
     307,   746,   345,   363,  1093,   388,   323,   750,    28,   244,
     282,   769,   353,    40,   278,   291,   306,   365,   366,   918,
     332,   351,   711,    29,   419,    30,   245,    31,    81,   420,
     123,   217,   218,   150,   284,   219,   313,   246,   220,   485,
     229,   281,   296,   308,   486,   346,   364,   416,   389,   365,
     366,   124,   285,   241,   314,   699,   700,   701,   702,   242,
     737,   738,   127,   128,   287,   127,   128,   974,   491,    42,
     975,   247,   243,   492,   248,    93,    94,    95,   249,    44,
     237,    46,   250,   238,   251,   503,   711,   150,   506,   252,
     504,   703,   253,   507,   254,   255,   256,    48,   977,   257,
     258,   978,   259,   882,   883,   884,   260,   261,  1010,    50,
     262,  1011,   263,   273,   274,   127,   128,   275,   276,  1217,
     290,   535,  1218,  1219,  1220,  1221,   536,  1215,   552,   556,
    1216,   786,   124,   553,   557,   787,   788,   789,   790,   791,
     792,   793,   794,   795,   796,   797,   127,   128,    52,   798,
     799,   800,   801,   802,   127,   128,   485,   770,   127,   128,
     297,   933,   150,   407,   408,   150,   298,   299,   300,   301,
     302,   303,   556,   304,    54,    87,    84,   934,    88,   845,
     846,   847,   848,   325,   849,   734,   735,    89,    56,    90,
      91,    92,    93,    94,    95,    96,    97,    98,   491,   893,
     894,    58,  1077,   935,  1078,   937,   902,   903,   904,   956,
     938,   956,    60,  1093,   957,   150,   958,    32,    33,    34,
      35,    99,   100,   101,   102,   103,   104,   105,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,   116,   117,
     118,   119,   120,   121,   122,   991,   150,   996,   123,   124,
     992,  1000,   997,    62,   150,  1044,  1001,   325,   905,   125,
     126,   413,  1006,   127,   128,   414,   324,  1007,   129,   417,
     127,   128,   415,   130,   131,   132,   133,   134,   552,  1013,
     956,   516,   135,  1008,  1014,  1176,    93,    94,    95,   503,
     518,   424,   136,  1180,  1177,   137,   150,   425,  1181,   535,
    1195,   506,   138,   139,  1187,  1196,  1198,   140,  1235,   517,
     141,   304,   928,  1236,   142,    99,   100,   101,   325,   426,
     326,   327,   433,   434,   328,   329,   330,   435,   436,   127,
     128,   127,   128,   437,   143,   144,   145,   146,   147,   148,
     558,   559,   123,   124,   325,   438,   439,  1140,   149,  1141,
    1142,   325,   347,   326,   327,   348,   349,   127,   128,   714,
     715,   716,   717,   150,   127,   128,  1161,  1162,  1163,   440,
     150,   441,   442,  1096,  1097,   868,   869,   870,   871,   872,
     873,   372,   373,   374,   375,   376,   377,   378,   379,   380,
     381,   382,   383,   384,  1168,  1169,  1170,   443,   151,   445,
     385,   386,   446,   447,   221,   448,   449,   453,   454,   455,
     459,   464,   465,   466,   472,   479,   240,   480,   481,   288,
     228,   289,   484,   490,   499,   521,   525,   527,   283,   150,
     305,   150,   280,   526,   529,   295,   530,   531,   532,   560,
     331,   537,   312,   244,   282,   350,   307,   540,   278,   352,
     542,   291,   543,   546,   547,   555,   345,   150,   561,   562,
     245,   363,   306,   229,   150,   387,   563,   564,   284,   565,
     353,   246,   566,   567,   332,   281,   568,   569,   296,   351,
     570,   388,   313,   571,   572,   573,   285,   241,   574,   308,
     580,   575,   576,   242,   577,   578,   585,   591,   592,   346,
     314,   579,   581,   582,   364,   247,   243,   583,   248,   584,
     586,   587,   249,   593,   588,   589,   250,   597,   251,   590,
     598,   599,  1199,   252,   389,   601,   253,   594,   254,   255,
     256,   602,   595,   257,   258,   596,   259,   600,   603,   604,
     260,   261,   605,   608,   262,   606,   263,   273,   274,   607,
     609,   275,   276,   610,   611,   612,   290,     1,     2,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
     613,   614,   615,   616,   617,   618,   619,   620,   621,   622,
     623,   624,   626,   627,   628,   629,   631,   632,   633,   634,
     635,   636,   637,   638,   639,   640,   642,   644,   645,   646,
     647,   151,   648,   221,   649,   650,   651,   653,   654,   656,
     772,   657,   655,   778,   658,   661,   665,   659,   662,   228,
     666,   669,   670,   672,   675,   663,   676,   671,   668,   679,
     677,   673,    91,    92,    93,    94,    95,   885,   895,   674,
     387,   680,   678,   681,   919,   682,   684,   685,   687,   961,
     688,   692,   689,   891,   896,   906,   388,   690,   691,   693,
     694,   695,   229,    99,   100,   101,   102,   103,   104,   105,
     106,   107,   108,   696,   697,   707,   698,   113,   114,   115,
     116,   117,   118,   119,   120,   121,   705,   230,   231,   232,
     706,   124,   708,   709,   710,   713,   892,   897,   907,   389,
      30,   719,   720,   233,   721,   127,   128,   234,   235,   236,
     129,   722,   723,   728,   724,   130,   131,   132,   725,   726,
     237,   727,   729,   238,   135,   730,   731,   732,   740,   741,
     742,   239,   743,   748,   777,   744,   745,   747,   825,   749,
     751,   752,   753,   754,   755,   782,   756,   757,   829,   833,
     837,   758,   759,   760,   761,   762,   763,   764,   766,   767,
     768,   774,   775,   776,   841,   857,   860,   864,   915,   924,
     943,   944,   945,   946,   947,   948,   143,   144,   949,   951,
    1015,   964,   960,   963,   967,   966,   969,   970,   972,   973,
     981,   980,   984,  1020,   983,   985,   986,   987,   988,   989,
     990,   993,   994,   995,  1002,   150,  1004,  1012,  1030,  1022,
    1019,  1023,  1024,  1026,  1027,  1028,  1029,  1031,  1037,  1039,
    1040,  1032,  1041,  1042,  1034,  1033,  1035,  1036,  1038,  1121,
    1122,  1123,  1124,  1125,  1126,  1132,  1129,  1128,  1130,  1133,
    1136,  1138,  1135,  1156,  1155,  1159,  1183,  1137,  1160,  1185,
    1153,  1165,  1166,  1178,  1167,  1172,  1173,  1174,  1175,  1179,
    1184,  1186,  1188,  1189,  1190,  1193,  1197,  1201,  1204,  1206,
    1202,  1205,  1208,  1209,  1210,   240,  1211,  1231,   331,  1232,
    1233,   350,  1237,  1238,  1052,   352,  1079,   283,  1241,  1098,
    1239,   280,   305,  1243,   345,   367,  1090,   363,  1240,  1244,
    1088,  1107,   244,   282,   312,  1105,   353,   278,   307,   885,
    1103,  1056,   332,   895,   779,   351,  1087,   765,  1076,   245,
     773,  1104,  1143,  1102,   306,   891,   919,   284,  1057,   896,
     246,   288,   630,   289,   281,   906,  1091,   346,  1145,  1058,
     364,  1108,   625,  1089,   313,   285,   241,   295,  1106,  1025,
     781,   308,   242,   932,  1092,  1053,  1144,  1045,  1131,  1109,
    1099,  1054,   314,   291,   247,   243,  1100,   248,   892,  1095,
    1043,   249,   897,  1059,  1055,   250,  1060,   251,   907,  1101,
    1061,  1146,   252,  1120,  1062,   253,  1063,   254,   255,   256,
     296,  1064,   257,   258,  1065,   259,  1066,  1067,  1068,   260,
     261,  1069,  1070,   262,  1071,   263,   273,   274,  1072,  1073,
     275,   276,  1074,   667,  1075,  1081,  1082,  1119,  1047,  1083,
    1084,  1080,   641,  1127,  1094,  1046,  1200,   660,  1049,   664,
    1158,  1048,   643,  1118,  1116,  1157,  1050,  1051,  1203,   652,
    1139,   914,  1134,   780,   686,  1207,  1229,   683,  1117,  1242,
       0,   929,     0,     0,     0,     0,  1152,     0,     0,     0,
       0,     0,     0,     0,  1191,     0,  1154,     0,   290,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,  1052,     0,  1079,     0,     0,  1098,     0,
       0,     0,     0,     0,     0,  1090,     0,     0,  1143,  1088,
    1107,     0,     0,     0,  1105,     0,     0,     0,     0,  1103,
    1056,     0,     0,     0,  1145,  1087,     0,  1076,     0,     0,
    1104,     0,  1102,     0,     0,     0,     0,  1057,     0,     0,
       0,     0,  1144,     0,     0,  1091,     0,     0,  1058,     0,
    1108,     0,  1089,     0,     0,     0,     0,  1106,     0,     0,
       0,     0,     0,  1092,  1053,     0,     0,  1146,  1109,  1099,
    1054,     0,     0,     0,     0,  1100,     0,     0,     0,     0,
       0,     0,  1059,  1055,     0,  1060,     0,     0,  1101,  1061,
       0,     0,     0,  1062,     0,  1063,     0,     0,     0,     0,
    1064,     0,     0,  1065,     0,  1066,  1067,  1068,     0,     0,
    1069,  1070,     0,  1071,     0,     0,     0,  1072,  1073,     0,
       0,  1074,     0,  1075,  1081,  1082,     0,     0,  1083,  1084,
    1080,    91,    92,    93,    94,    95,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    99,   100,   101,   102,   103,   104,   105,   106,
     107,   108,     0,     0,     0,     0,   113,   114,   115,   116,
     117,   118,   119,   120,   121,   122,     0,     0,     0,     0,
     124,   325,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   127,   128,     0,   235,     0,   129,
       0,     0,     0,     0,   130,   131,   132,     0,     0,   237,
       0,     0,   238,     0,     0,     0,     0,     0,     0,     0,
     239,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   143,   144,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   150
  };

  const short
  Dhcp4Parser::yycheck_[] =
  {
      67,    68,    69,    70,    71,    70,    73,    74,    75,    76,
      64,    74,   696,   971,    69,   971,    71,    68,    69,    70,
      71,   638,    73,    74,   971,    76,    72,   644,     0,    69,
      69,    18,    74,     7,    69,    70,    71,   129,   130,   185,
      73,    74,   602,     5,     3,     7,    69,     9,   199,     8,
      84,    15,    16,   199,    69,    19,    71,    69,    22,     3,
      68,    69,    70,    71,     8,    73,    74,     8,    76,   129,
     130,    85,    69,    69,    71,   166,   167,   168,   169,    69,
      20,    21,    99,   100,    98,    99,   100,     3,     3,     7,
       6,    69,    69,     8,    69,    28,    29,    30,    69,     7,
     114,     7,    69,   117,    69,     3,   666,   199,     3,    69,
       8,   202,    69,     8,    69,    69,    69,     7,     3,    69,
      69,     6,    69,   140,   141,   142,    69,    69,     3,     7,
      69,     6,    69,    69,    69,    99,   100,    69,    69,   177,
      70,     3,   180,   181,   182,   183,     8,     3,     3,     3,
       6,    34,    85,     8,     8,    38,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    99,   100,     7,    52,
      53,    54,    55,    56,    99,   100,     3,   164,    99,   100,
     113,     8,   199,    12,    13,   199,   119,   120,   121,   122,
     123,   124,     3,   126,     7,    11,    10,     8,    14,   119,
     120,   121,   122,    86,   124,    17,    18,    23,     7,    25,
      26,    27,    28,    29,    30,    31,    32,    33,     3,   144,
     145,     7,  1180,     8,  1180,     3,   147,   148,   149,     3,
       8,     3,     7,  1180,     8,   199,     8,   199,   200,   201,
     202,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    68,    69,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,     3,   199,     3,    84,    85,
       8,     3,     8,     7,   199,   959,     8,    86,   199,    95,
      96,     6,     3,    99,   100,     3,    34,     8,   104,     3,
      99,   100,     4,   109,   110,   111,   112,   113,     3,     3,
       3,     8,   118,     8,     8,     8,    28,    29,    30,     3,
       8,     4,   128,     3,     8,   131,   199,     4,     8,     3,
       3,     3,   138,   139,     8,     8,     8,   143,     3,     3,
     146,   126,   127,     8,   150,    57,    58,    59,    86,     4,
      88,    89,     4,     4,    92,    93,    94,     4,     4,    99,
     100,    99,   100,     4,   170,   171,   172,   173,   174,   175,
     414,   415,    84,    85,    86,     4,     4,   176,   184,   178,
     179,    86,    87,    88,    89,    90,    91,    99,   100,   105,
     106,   107,   108,   199,    99,   100,    35,    36,    37,     4,
     199,     4,     4,   115,   116,   132,   133,   134,   135,   136,
     137,   151,   152,   153,   154,   155,   156,   157,   158,   159,
     160,   161,   162,   163,    49,    50,    51,     4,   485,     4,
     170,   171,     4,     4,   491,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,   503,     4,     4,   506,
     491,   506,     4,     4,     4,     4,     4,     3,   503,   199,
     517,   199,   503,     8,     4,   506,     4,     8,     3,   199,
     527,     4,   517,   503,   503,   532,   517,     4,   503,   532,
       4,   506,     4,     4,     4,     4,   527,   199,     4,     4,
     503,   532,   517,   491,   199,   552,     4,     4,   503,   202,
     532,   503,   202,   202,   527,   503,     4,     4,   506,   532,
       4,   552,   517,     4,     4,     4,   503,   503,   200,   517,
     201,   200,   200,   503,   200,   200,     4,     4,     4,   527,
     517,   202,   201,   201,   532,   503,   503,   200,   503,   200,
     200,   200,   503,     4,   202,   202,   503,     4,   503,   202,
       4,     4,  1159,   503,   552,     4,   503,   202,   503,   503,
     503,     4,   202,   503,   503,   202,   503,   200,     4,     4,
     503,   503,   202,     4,   503,   202,   503,   503,   503,   202,
       4,   503,   503,     4,     4,     4,   506,   186,   187,   188,
     189,   190,   191,   192,   193,   194,   195,   196,   197,   198,
     200,     4,     4,     4,     4,     4,     4,   202,   202,   202,
       4,     4,     4,     4,     4,   202,     4,     4,     4,     4,
       4,     4,   200,     4,     4,     4,     4,     4,     4,     4,
       4,   688,     4,   690,     4,     4,     4,     4,     4,     4,
     165,     4,   200,   687,     4,     4,     4,   202,   202,   690,
       4,     4,     4,     4,     4,   202,     4,   200,   202,     4,
     202,   200,    26,    27,    28,    29,    30,   724,   725,   200,
     727,     4,   202,     4,   731,     4,     4,   200,     4,     3,
       7,   199,     7,   724,   725,   726,   727,     7,     7,   199,
     199,     7,   690,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,     7,     5,     5,   199,    71,    72,    73,
      74,    75,    76,    77,    78,    79,   199,    81,    82,    83,
     199,    85,     5,     5,     5,   199,   724,   725,   726,   727,
       7,     5,     5,    97,     5,    99,   100,   101,   102,   103,
     104,     5,     7,   199,     7,   109,   110,   111,     7,     7,
     114,     7,   199,   117,   118,     5,     7,     5,   199,   199,
     199,   125,     5,     7,     5,   199,   199,   199,     7,   199,
     199,   199,   199,   199,   199,    24,   199,   199,     7,     7,
       7,   199,   199,   199,   199,   199,   199,   199,   199,   199,
     199,   199,   199,   199,     7,     7,     7,     7,     7,     7,
       4,     4,     4,     4,     4,     4,   170,   171,     4,     4,
     199,     3,     6,     6,     3,     6,     6,     3,     6,     3,
       3,     6,     3,     3,     6,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,   199,     4,     4,   200,     8,
       6,     6,     4,     4,     4,     4,     4,   202,     4,     4,
       4,   200,     4,     4,   200,   202,   200,   200,   200,   200,
     200,   200,   200,   200,   200,     4,   200,   202,   200,     4,
       4,     4,   202,     3,     6,     4,     4,   200,   199,     3,
     202,   199,   199,     8,   199,   199,   199,   199,   199,     8,
       8,     8,   199,   199,   199,     4,   199,     4,     4,     4,
     202,   200,   199,     5,   199,   962,     7,     4,   965,     4,
       4,   968,     4,   202,   971,   968,   971,   962,     4,   976,
     200,   962,   979,   199,   965,   982,   971,   968,   200,   199,
     971,   976,   962,   962,   979,   976,   968,   962,   979,   996,
     976,   971,   965,  1000,   688,   968,   971,   666,   971,   962,
     679,   976,  1009,   976,   979,   996,  1013,   962,   971,  1000,
     962,  1018,   491,  1018,   962,  1006,   971,   965,  1009,   971,
     968,   976,   485,   971,   979,   962,   962,  1018,   976,   937,
     690,   979,   962,   777,   971,   971,  1009,   961,   996,   976,
     976,   971,   979,  1018,   962,   962,   976,   962,   996,   974,
     956,   962,  1000,   971,   971,   962,   971,   962,  1006,   976,
     971,  1009,   962,   984,   971,   962,   971,   962,   962,   962,
    1018,   971,   962,   962,   971,   962,   971,   971,   971,   962,
     962,   971,   971,   962,   971,   962,   962,   962,   971,   971,
     962,   962,   971,   535,   971,   971,   971,   982,   964,   971,
     971,   971,   503,   991,   973,   962,  1180,   527,   967,   532,
    1020,   965,   506,   981,   977,  1018,   968,   970,  1185,   517,
    1006,   727,  1000,   689,   556,  1195,  1215,   552,   979,  1235,
      -1,   748,    -1,    -1,    -1,    -1,  1010,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,  1138,    -1,  1013,    -1,  1018,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,  1180,    -1,  1180,    -1,    -1,  1185,    -1,
      -1,    -1,    -1,    -1,    -1,  1180,    -1,    -1,  1195,  1180,
    1185,    -1,    -1,    -1,  1185,    -1,    -1,    -1,    -1,  1185,
    1180,    -1,    -1,    -1,  1195,  1180,    -1,  1180,    -1,    -1,
    1185,    -1,  1185,    -1,    -1,    -1,    -1,  1180,    -1,    -1,
      -1,    -1,  1195,    -1,    -1,  1180,    -1,    -1,  1180,    -1,
    1185,    -1,  1180,    -1,    -1,    -1,    -1,  1185,    -1,    -1,
      -1,    -1,    -1,  1180,  1180,    -1,    -1,  1195,  1185,  1185,
    1180,    -1,    -1,    -1,    -1,  1185,    -1,    -1,    -1,    -1,
      -1,    -1,  1180,  1180,    -1,  1180,    -1,    -1,  1185,  1180,
      -1,    -1,    -1,  1180,    -1,  1180,    -1,    -1,    -1,    -1,
    1180,    -1,    -1,  1180,    -1,  1180,  1180,  1180,    -1,    -1,
    1180,  1180,    -1,  1180,    -1,    -1,    -1,  1180,  1180,    -1,
      -1,  1180,    -1,  1180,  1180,  1180,    -1,    -1,  1180,  1180,
    1180,    26,    27,    28,    29,    30,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    -1,    -1,    -1,    -1,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    -1,    -1,    -1,    -1,
      85,    86,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    99,   100,    -1,   102,    -1,   104,
      -1,    -1,    -1,    -1,   109,   110,   111,    -1,    -1,   114,
      -1,    -1,   117,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
     125,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,   170,   171,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,   199
  };

  const short
  Dhcp4Parser::yystos_[] =
  {
       0,   186,   187,   188,   189,   190,   191,   192,   193,   194,
     195,   196,   197,   198,   204,   205,   206,   207,   208,   209,
     210,   211,   212,   213,   214,   215,   216,   217,     0,     5,
       7,     9,   199,   200,   201,   202,   218,   219,   220,   225,
       7,   234,     7,   239,     7,   286,     7,   391,     7,   474,
       7,   490,     7,   426,     7,   432,     7,   456,     7,   367,
       7,   555,     7,   586,   226,   221,   235,   240,   287,   392,
     475,   491,   427,   433,   457,   368,   556,   587,   218,   227,
     228,   199,   223,   224,    10,   236,   238,    11,    14,    23,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      68,    69,    70,    71,    72,    73,    74,    75,    76,    77,
      78,    79,    80,    84,    85,    95,    96,    99,   100,   104,
     109,   110,   111,   112,   113,   118,   128,   131,   138,   139,
     143,   146,   150,   170,   171,   172,   173,   174,   175,   184,
     199,   233,   241,   242,   243,   244,   245,   246,   247,   248,
     249,   250,   251,   252,   253,   254,   256,   257,   258,   259,
     260,   261,   262,   263,   266,   268,   270,   271,   272,   274,
     276,   277,   278,   279,   280,   281,   282,   297,   299,   305,
     307,   345,   354,   361,   375,   385,   409,   410,   411,   412,
     416,   424,   450,   480,   482,   484,   495,   497,   499,   522,
     534,   535,   543,   553,   584,   593,   617,    15,    16,    19,
      22,   233,   284,   285,   288,   290,   293,   296,   480,   482,
      81,    82,    83,    97,   101,   102,   103,   114,   117,   125,
     233,   243,   244,   245,   246,   247,   248,   249,   250,   251,
     252,   258,   259,   260,   261,   262,   263,   266,   268,   270,
     271,   272,   274,   276,   393,   394,   395,   397,   399,   401,
     403,   405,   407,   409,   410,   411,   412,   415,   450,   468,
     480,   482,   484,   495,   497,   499,   519,    98,   233,   405,
     407,   450,   476,   477,   478,   480,   482,   113,   119,   120,
     121,   122,   123,   124,   126,   233,   450,   480,   482,   492,
     493,   494,   495,   497,   499,   501,   505,   507,   509,   511,
     513,   515,   517,   424,    34,    86,    88,    89,    92,    93,
      94,   233,   325,   434,   435,   436,   437,   438,   439,   440,
     442,   444,   446,   447,   449,   480,   482,    87,    90,    91,
     233,   325,   438,   444,   458,   459,   460,   461,   462,   464,
     465,   466,   467,   480,   482,   129,   130,   233,   369,   370,
     371,   373,   151,   152,   153,   154,   155,   156,   157,   158,
     159,   160,   161,   162,   163,   170,   171,   233,   480,   482,
     557,   558,   559,   560,   562,   563,   565,   566,   567,   570,
     572,   574,   575,   576,   578,   580,   582,    12,    13,   588,
     589,   590,   592,     6,     3,     4,     8,     3,   237,     3,
       8,   585,   283,   300,     4,     4,     4,   496,   498,   500,
     298,   306,   308,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,   255,     4,     4,     4,     4,     4,
     264,   267,   269,     4,     4,     4,   386,   425,   451,     4,
     417,   481,   483,   413,     4,     4,     4,   346,   523,   485,
     362,   376,     4,   355,   536,   544,   554,   273,   275,     4,
       4,     4,   594,   618,     4,     3,     8,   289,   291,   294,
       4,     3,     8,   398,   400,   402,   469,   396,   404,     4,
     408,   406,   520,     3,     8,   479,     3,     8,   518,   506,
     508,   512,   510,   516,   514,   502,     8,     3,     8,   441,
     326,     4,   445,   443,   448,     4,     8,     3,   463,     4,
       4,     8,     3,   372,   374,     3,     8,     4,   573,   561,
       4,   564,     4,     4,   568,   571,     4,     4,   577,   579,
     581,   583,     3,     8,   591,     4,     3,     8,   218,   218,
     199,     4,     4,     4,     4,   202,   202,   202,     4,     4,
       4,     4,     4,     4,   200,   200,   200,   200,   200,   202,
     201,   201,   201,   200,   200,     4,   200,   200,   202,   202,
     202,     4,     4,     4,   202,   202,   202,     4,     4,     4,
     200,     4,     4,     4,     4,   202,   202,   202,     4,     4,
       4,     4,     4,   200,     4,     4,     4,     4,     4,     4,
     202,   202,   202,     4,     4,   242,     4,     4,     4,   202,
     285,     4,     4,     4,     4,     4,     4,   200,     4,     4,
       4,   394,     4,   477,     4,     4,     4,     4,     4,     4,
       4,     4,   494,     4,     4,   200,     4,     4,     4,   202,
     436,     4,   202,   202,   460,     4,     4,   370,   202,     4,
       4,   200,     4,   200,   200,     4,     4,   202,   202,     4,
       4,     4,     4,   558,     4,   200,   589,     4,     7,     7,
       7,     7,   199,   199,   199,     7,     7,     5,   199,   166,
     167,   168,   169,   202,   265,   199,   199,     5,     5,     5,
       5,   220,   222,   199,   105,   106,   107,   108,   414,     5,
       5,     5,     5,     7,     7,     7,     7,     7,   199,   199,
       5,     7,     5,   229,    17,    18,   292,    20,    21,   295,
     199,   199,   199,     5,   199,   199,   229,   199,     7,   199,
     229,   199,   199,   199,   199,   199,   199,   199,   199,   199,
     199,   199,   199,   199,   199,   222,   199,   199,   199,    18,
     164,   569,   165,   265,   199,   199,   199,     5,   218,   241,
     588,   284,    24,   301,   302,   303,    34,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    52,    53,
      54,    55,    56,   233,   313,   314,   315,   318,   320,   322,
     324,   325,   327,   328,   329,   330,   331,   332,   333,   336,
     337,   339,   341,   343,   313,     7,   309,   310,   311,     7,
     387,   388,   389,     7,   428,   429,   430,     7,   452,   453,
     454,     7,   418,   419,   420,   119,   120,   121,   122,   124,
     347,   348,   349,   350,   351,   352,   353,     7,   524,   525,
       7,   486,   487,   488,     7,   363,   364,   365,   132,   133,
     134,   135,   136,   137,   377,   378,   379,   380,   381,   382,
     383,   384,   140,   141,   142,   233,   356,   357,   358,   359,
     360,   480,   482,   144,   145,   233,   480,   482,   537,   538,
     539,   541,   147,   148,   149,   199,   480,   482,   545,   546,
     547,   548,   550,   551,   557,     7,   595,   596,   185,   233,
     619,   620,   621,   230,     7,   470,   471,   472,   127,   501,
     503,   521,   309,     8,     8,     8,   304,     3,     8,   316,
     319,   321,   323,     4,     4,     4,     4,     4,     4,     4,
     334,     4,   338,   340,   342,   344,     3,     8,     8,   312,
       6,     3,   390,     6,     3,   431,     6,     3,   455,     6,
       3,   421,     6,     3,     3,     6,   526,     3,     6,   489,
       6,     3,   366,     6,     3,     4,     4,     4,     4,     4,
       4,     3,     8,     4,     4,     4,     3,     8,   540,   542,
       3,     8,     4,   549,     4,   552,     3,     8,     8,   597,
       3,     6,     4,     3,     8,   199,   231,   232,   473,     6,
       3,   504,     8,     6,     4,   302,     4,     4,     4,     4,
     200,   202,   200,   202,   200,   200,   200,     4,   200,     4,
       4,     4,     4,   314,   313,   311,   393,   389,   434,   430,
     458,   454,   233,   243,   244,   245,   246,   247,   248,   249,
     250,   251,   252,   258,   259,   260,   261,   262,   263,   266,
     268,   270,   271,   272,   274,   276,   325,   385,   403,   405,
     407,   409,   410,   411,   412,   422,   423,   450,   480,   482,
     495,   497,   499,   519,   420,   348,   115,   116,   233,   243,
     244,   245,   325,   424,   450,   480,   482,   495,   497,   499,
     527,   528,   529,   530,   531,   533,   525,   492,   488,   369,
     365,   200,   200,   200,   200,   200,   200,   378,   202,   200,
     200,   357,     4,     4,   538,   202,     4,   200,     4,   546,
     176,   178,   179,   233,   325,   480,   482,   598,   599,   600,
     601,   603,   596,   202,   620,     6,     3,   476,   472,     4,
     199,    35,    36,    37,   317,   199,   199,   199,    49,    50,
      51,   335,   199,   199,   199,   199,     8,     8,     8,     8,
       3,     8,   532,     4,     8,     3,     8,     8,   199,   199,
     199,   218,   604,     4,   602,     3,     8,   199,     8,   229,
     423,     4,   202,   529,     4,   200,     4,   599,   199,     5,
     199,     7,   605,   606,   607,     3,     6,   177,   180,   181,
     182,   183,   608,   609,   610,   612,   613,   614,   615,   606,
     611,     4,     4,     4,   616,     3,     8,     4,   202,   200,
     200,     4,   609,   199,   199
  };

  const short
  Dhcp4Parser::yyr1_[] =
  {
       0,   203,   205,   204,   206,   204,   207,   204,   208,   204,
     209,   204,   210,   204,   211,   204,   212,   204,   213,   204,
     214,   204,   215,   204,   216,   204,   217,   204,   218,   218,
     218,   218,   218,   218,   218,   219,   221,   220,   222,   223,
     223,   224,   224,   224,   226,   225,   227,   227,   228,   228,
     228,   230,   229,   231,   231,   232,   232,   232,   233,   235,
     234,   237,   236,   236,   238,   240,   239,   241,   241,   241,
     242,   242,   242,   242,   242,   242,   242,   242,   242,   242,
     242,   242,   242,   242,   242,   242,   242,   242,   242,   242,
     242,   242,   242,   242,   242,   242,   242,   242,   242,   242,
     242,   242,   242,   242,   242,   242,   242,   242,   242,   242,
     242,   242,   242,   242,   242,   242,   242,   242,   242,   242,
     242,   242,   242,   242,   242,   242,   242,   242,   242,   242,
     242,   242,   242,   242,   243,   244,   245,   246,   247,   248,
     249,   250,   251,   252,   253,   255,   254,   256,   257,   258,
     259,   260,   261,   262,   264,   263,   265,   265,   265,   265,
     265,   267,   266,   269,   268,   270,   271,   273,   272,   275,
     274,   276,   277,   278,   279,   280,   281,   283,   282,   284,
     284,   284,   285,   285,   285,   285,   285,   285,   285,   287,
     286,   289,   288,   291,   290,   292,   292,   294,   293,   295,
     295,   296,   298,   297,   300,   299,   301,   301,   301,   302,
     304,   303,   306,   305,   308,   307,   309,   309,   310,   310,
     310,   312,   311,   313,   313,   313,   314,   314,   314,   314,
     314,   314,   314,   314,   314,   314,   314,   314,   314,   314,
     314,   314,   314,   314,   314,   316,   315,   317,   317,   317,
     319,   318,   321,   320,   323,   322,   324,   326,   325,   327,
     328,   329,   330,   331,   332,   334,   333,   335,   335,   335,
     336,   338,   337,   340,   339,   342,   341,   344,   343,   346,
     345,   347,   347,   347,   348,   348,   348,   348,   348,   349,
     350,   351,   352,   353,   355,   354,   356,   356,   356,   357,
     357,   357,   357,   357,   357,   358,   359,   360,   362,   361,
     363,   363,   364,   364,   364,   366,   365,   368,   367,   369,
     369,   369,   369,   370,   370,   372,   371,   374,   373,   376,
     375,   377,   377,   377,   378,   378,   378,   378,   378,   378,
     379,   380,   381,   382,   383,   384,   386,   385,   387,   387,
     388,   388,   388,   390,   389,   392,   391,   393,   393,   393,
     394,   394,   394,   394,   394,   394,   394,   394,   394,   394,
     394,   394,   394,   394,   394,   394,   394,   394,   394,   394,
     394,   394,   394,   394,   394,   394,   394,   394,   394,   394,
     394,   394,   394,   394,   394,   394,   394,   394,   394,   394,
     394,   394,   394,   394,   394,   396,   395,   398,   397,   400,
     399,   402,   401,   404,   403,   406,   405,   408,   407,   409,
     410,   411,   413,   412,   414,   414,   414,   414,   415,   417,
     416,   418,   418,   419,   419,   419,   421,   420,   422,   422,
     422,   423,   423,   423,   423,   423,   423,   423,   423,   423,
     423,   423,   423,   423,   423,   423,   423,   423,   423,   423,
     423,   423,   423,   423,   423,   423,   423,   423,   423,   423,
     423,   423,   423,   423,   423,   423,   423,   423,   423,   423,
     423,   425,   424,   427,   426,   428,   428,   429,   429,   429,
     431,   430,   433,   432,   434,   434,   435,   435,   435,   436,
     436,   436,   436,   436,   436,   436,   436,   436,   436,   437,
     438,   439,   441,   440,   443,   442,   445,   444,   446,   448,
     447,   449,   451,   450,   452,   452,   453,   453,   453,   455,
     454,   457,   456,   458,   458,   459,   459,   459,   460,   460,
     460,   460,   460,   460,   460,   460,   460,   461,   463,   462,
     464,   465,   466,   467,   469,   468,   470,   470,   471,   471,
     471,   473,   472,   475,   474,   476,   476,   476,   477,   477,
     477,   477,   477,   477,   477,   479,   478,   481,   480,   483,
     482,   485,   484,   486,   486,   487,   487,   487,   489,   488,
     491,   490,   492,   492,   493,   493,   493,   494,   494,   494,
     494,   494,   494,   494,   494,   494,   494,   494,   494,   494,
     494,   494,   496,   495,   498,   497,   500,   499,   502,   501,
     504,   503,   506,   505,   508,   507,   510,   509,   512,   511,
     514,   513,   516,   515,   518,   517,   520,   519,   521,   521,
     523,   522,   524,   524,   524,   526,   525,   527,   527,   528,
     528,   528,   529,   529,   529,   529,   529,   529,   529,   529,
     529,   529,   529,   529,   529,   529,   530,   532,   531,   533,
     534,   536,   535,   537,   537,   537,   538,   538,   538,   538,
     538,   540,   539,   542,   541,   544,   543,   545,   545,   545,
     546,   546,   546,   546,   546,   546,   547,   549,   548,   550,
     552,   551,   554,   553,   556,   555,   557,   557,   557,   558,
     558,   558,   558,   558,   558,   558,   558,   558,   558,   558,
     558,   558,   558,   558,   558,   558,   558,   559,   561,   560,
     562,   564,   563,   565,   566,   568,   567,   569,   569,   571,
     570,   573,   572,   574,   575,   577,   576,   579,   578,   581,
     580,   583,   582,   585,   584,   587,   586,   588,   588,   588,
     589,   589,   591,   590,   592,   594,   593,   595,   595,   595,
     597,   596,   598,   598,   598,   599,   599,   599,   599,   599,
     599,   599,   600,   602,   601,   604,   603,   605,   605,   605,
     607,   606,   608,   608,   608,   609,   609,   609,   609,   609,
     611,   610,   612,   613,   614,   616,   615,   618,   617,   619,
     619,   619,   620,   620,   621
  };

  const signed char
  Dhcp4Parser::yyr2_[] =
  {
       0,     2,     0,     3,     0,     3,     0,     3,     0,     3,
       0,     3,     0,     3,     0,     3,     0,     3,     0,     3,
       0,     3,     0,     3,     0,     3,     0,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     1,     0,
       1,     3,     5,     2,     0,     4,     0,     1,     1,     3,
       2,     0,     4,     0,     1,     1,     3,     2,     2,     0,
       4,     0,     6,     1,     2,     0,     4,     1,     3,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     0,     4,     3,     3,     3,
       3,     3,     3,     3,     0,     4,     1,     1,     1,     1,
       1,     0,     4,     0,     4,     3,     3,     0,     4,     0,
       4,     3,     3,     3,     3,     3,     3,     0,     6,     1,
       3,     2,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     0,     4,     0,     4,     1,     1,     0,     4,     1,
       1,     3,     0,     6,     0,     6,     1,     3,     2,     1,
       0,     4,     0,     6,     0,     6,     0,     1,     1,     3,
       2,     0,     4,     1,     3,     2,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     1,     1,     1,
       0,     4,     0,     4,     0,     4,     3,     0,     4,     3,
       3,     3,     3,     3,     3,     0,     4,     1,     1,     1,
       3,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       6,     1,     3,     2,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     6,     1,     3,     2,     1,
       1,     1,     1,     1,     1,     3,     3,     3,     0,     6,
       0,     1,     1,     3,     2,     0,     4,     0,     4,     1,
       3,     2,     1,     1,     1,     0,     4,     0,     4,     0,
       6,     1,     3,     2,     1,     1,     1,     1,     1,     1,
       3,     3,     3,     3,     3,     3,     0,     6,     0,     1,
       1,     3,     2,     0,     4,     0,     4,     1,     3,     2,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     3,
       3,     3,     0,     4,     1,     1,     1,     1,     3,     0,
       6,     0,     1,     1,     3,     2,     0,     4,     1,     3,
       2,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     6,     0,     4,     0,     1,     1,     3,     2,
       0,     4,     0,     4,     0,     1,     1,     3,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     1,     0,     4,     0,     4,     0,     4,     1,     0,
       4,     3,     0,     6,     0,     1,     1,     3,     2,     0,
       4,     0,     4,     0,     1,     1,     3,     2,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       1,     1,     3,     3,     0,     6,     0,     1,     1,     3,
       2,     0,     4,     0,     4,     1,     3,     2,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     0,     4,     0,
       4,     0,     6,     0,     1,     1,     3,     2,     0,     4,
       0,     4,     0,     1,     1,     3,     2,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     6,     1,     1,
       0,     6,     1,     3,     2,     0,     4,     0,     1,     1,
       3,     2,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     3,
       3,     0,     6,     1,     3,     2,     1,     1,     1,     1,
       1,     0,     4,     0,     4,     0,     6,     1,     3,     2,
       1,     1,     1,     1,     1,     1,     3,     0,     4,     3,
       0,     4,     0,     6,     0,     4,     1,     3,     2,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     3,     0,     4,
       3,     0,     4,     3,     3,     0,     4,     1,     1,     0,
       4,     0,     4,     3,     3,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     6,     0,     4,     1,     3,     2,
       1,     1,     0,     6,     3,     0,     6,     1,     3,     2,
       0,     4,     1,     3,     2,     1,     1,     1,     1,     1,
       1,     1,     3,     0,     4,     0,     6,     1,     3,     2,
       0,     4,     1,     3,     2,     1,     1,     1,     1,     1,
       0,     4,     3,     3,     3,     0,     4,     0,     6,     1,
       3,     2,     1,     1,     3
  };



  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a yyntokens_, nonterminals.
  const char*
  const Dhcp4Parser::yytname_[] =
  {
  "\"end of file\"", "error", "$undefined", "\",\"", "\":\"", "\"[\"",
  "\"]\"", "\"{\"", "\"}\"", "\"null\"", "\"Dhcp4\"", "\"config-control\"",
  "\"config-databases\"", "\"config-fetch-wait-time\"",
  "\"interfaces-config\"", "\"interfaces\"", "\"dhcp-socket-type\"",
  "\"raw\"", "\"udp\"", "\"outbound-interface\"", "\"same-as-inbound\"",
  "\"use-routing\"", "\"re-detect\"", "\"sanity-checks\"",
  "\"lease-checks\"", "\"echo-client-id\"", "\"match-client-id\"",
  "\"authoritative\"", "\"next-server\"", "\"server-hostname\"",
  "\"boot-file-name\"", "\"lease-database\"", "\"hosts-database\"",
  "\"hosts-databases\"", "\"type\"", "\"memfile\"", "\"mysql\"",
  "\"postgresql\"", "\"user\"", "\"password\"", "\"host\"", "\"port\"",
  "\"persist\"", "\"lfc-interval\"", "\"readonly\"", "\"connect-timeout\"",
  "\"max-reconnect-tries\"", "\"reconnect-wait-time\"", "\"on-fail\"",
  "\"stop-retry-exit\"", "\"serve-retry-exit\"",
  "\"serve-retry-continue\"", "\"max-row-errors\"", "\"trust-anchor\"",
  "\"cert-file\"", "\"key-file\"", "\"cipher-list\"", "\"valid-lifetime\"",
  "\"min-valid-lifetime\"", "\"max-valid-lifetime\"", "\"renew-timer\"",
  "\"rebind-timer\"", "\"calculate-tee-times\"", "\"t1-percent\"",
  "\"t2-percent\"", "\"cache-threshold\"", "\"cache-max-age\"",
  "\"decline-probation-period\"", "\"server-tag\"",
  "\"statistic-default-sample-count\"", "\"statistic-default-sample-age\"",
  "\"ddns-send-updates\"", "\"ddns-override-no-update\"",
  "\"ddns-override-client-update\"", "\"ddns-replace-client-name\"",
  "\"ddns-generated-prefix\"", "\"ddns-qualifying-suffix\"",
  "\"ddns-update-on-renew\"", "\"ddns-use-conflict-resolution\"",
  "\"store-extended-info\"", "\"subnet4\"", "\"4o6-interface\"",
  "\"4o6-interface-id\"", "\"4o6-subnet\"", "\"option-def\"",
  "\"option-data\"", "\"name\"", "\"data\"", "\"code\"", "\"space\"",
  "\"csv-format\"", "\"always-send\"", "\"record-types\"",
  "\"encapsulate\"", "\"array\"", "\"parked-packet-limit\"",
  "\"shared-networks\"", "\"pools\"", "\"pool\"", "\"user-context\"",
  "\"comment\"", "\"subnet\"", "\"interface\"", "\"id\"",
  "\"reservation-mode\"", "\"disabled\"", "\"out-of-pool\"", "\"global\"",
  "\"all\"", "\"reservations-global\"", "\"reservations-in-subnet\"",
  "\"reservations-out-of-pool\"", "\"host-reservation-identifiers\"",
  "\"client-classes\"", "\"require-client-classes\"", "\"test\"",
  "\"only-if-required\"", "\"client-class\"", "\"reservations\"",
  "\"duid\"", "\"hw-address\"", "\"circuit-id\"", "\"client-id\"",
  "\"hostname\"", "\"flex-id\"", "\"relay\"", "\"ip-address\"",
  "\"ip-addresses\"", "\"hooks-libraries\"", "\"library\"",
  "\"parameters\"", "\"expired-leases-processing\"",
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
  "\"hostname-char-set\"", "\"hostname-char-replacement\"",
  "\"early-global-reservations-lookup\"", "\"ip-reservations-unique\"",
  "\"reservations-lookup-first\"", "\"loggers\"", "\"output_options\"",
  "\"output\"", "\"debuglevel\"", "\"severity\"", "\"flush\"",
  "\"maxsize\"", "\"maxver\"", "\"pattern\"", "\"compatibility\"",
  "\"lenient-option-parsing\"", "TOPLEVEL_JSON", "TOPLEVEL_DHCP4",
  "SUB_DHCP4", "SUB_INTERFACES4", "SUB_SUBNET4", "SUB_POOL4",
  "SUB_RESERVATION", "SUB_OPTION_DEFS", "SUB_OPTION_DEF",
  "SUB_OPTION_DATA", "SUB_HOOKS_LIBRARY", "SUB_DHCP_DDNS",
  "SUB_CONFIG_CONTROL", "\"constant string\"", "\"integer\"",
  "\"floating point\"", "\"boolean\"", "$accept", "start", "$@1", "$@2",
  "$@3", "$@4", "$@5", "$@6", "$@7", "$@8", "$@9", "$@10", "$@11", "$@12",
  "$@13", "value", "sub_json", "map2", "$@14", "map_value", "map_content",
  "not_empty_map", "list_generic", "$@15", "list_content",
  "not_empty_list", "list_strings", "$@16", "list_strings_content",
  "not_empty_list_strings", "unknown_map_entry", "syntax_map", "$@17",
  "global_object", "$@18", "global_object_comma", "sub_dhcp4", "$@19",
  "global_params", "global_param", "valid_lifetime", "min_valid_lifetime",
  "max_valid_lifetime", "renew_timer", "rebind_timer",
  "calculate_tee_times", "t1_percent", "t2_percent", "cache_threshold",
  "cache_max_age", "decline_probation_period", "server_tag", "$@20",
  "parked_packet_limit", "echo_client_id", "match_client_id",
  "authoritative", "ddns_send_updates", "ddns_override_no_update",
  "ddns_override_client_update", "ddns_replace_client_name", "$@21",
  "ddns_replace_client_name_value", "ddns_generated_prefix", "$@22",
  "ddns_qualifying_suffix", "$@23", "ddns_update_on_renew",
  "ddns_use_conflict_resolution", "hostname_char_set", "$@24",
  "hostname_char_replacement", "$@25", "store_extended_info",
  "statistic_default_sample_count", "statistic_default_sample_age",
  "early_global_reservations_lookup", "ip_reservations_unique",
  "reservations_lookup_first", "interfaces_config", "$@26",
  "interfaces_config_params", "interfaces_config_param", "sub_interfaces4",
  "$@27", "interfaces_list", "$@28", "dhcp_socket_type", "$@29",
  "socket_type", "outbound_interface", "$@30", "outbound_interface_value",
  "re_detect", "lease_database", "$@31", "sanity_checks", "$@32",
  "sanity_checks_params", "sanity_checks_param", "lease_checks", "$@33",
  "hosts_database", "$@34", "hosts_databases", "$@35", "database_list",
  "not_empty_database_list", "database", "$@36", "database_map_params",
  "database_map_param", "database_type", "$@37", "db_type", "user", "$@38",
  "password", "$@39", "host", "$@40", "port", "name", "$@41", "persist",
  "lfc_interval", "readonly", "connect_timeout", "max_reconnect_tries",
  "reconnect_wait_time", "on_fail", "$@42", "on_fail_mode",
  "max_row_errors", "trust_anchor", "$@43", "cert_file", "$@44",
  "key_file", "$@45", "cipher_list", "$@46",
  "host_reservation_identifiers", "$@47",
  "host_reservation_identifiers_list", "host_reservation_identifier",
  "duid_id", "hw_address_id", "circuit_id", "client_id", "flex_id",
  "dhcp_multi_threading", "$@48", "multi_threading_params",
  "multi_threading_param", "enable_multi_threading", "thread_pool_size",
  "packet_queue_size", "hooks_libraries", "$@49", "hooks_libraries_list",
  "not_empty_hooks_libraries_list", "hooks_library", "$@50",
  "sub_hooks_library", "$@51", "hooks_params", "hooks_param", "library",
  "$@52", "parameters", "$@53", "expired_leases_processing", "$@54",
  "expired_leases_params", "expired_leases_param",
  "reclaim_timer_wait_time", "flush_reclaimed_timer_wait_time",
  "hold_reclaimed_time", "max_reclaim_leases", "max_reclaim_time",
  "unwarned_reclaim_cycles", "subnet4_list", "$@55",
  "subnet4_list_content", "not_empty_subnet4_list", "subnet4", "$@56",
  "sub_subnet4", "$@57", "subnet4_params", "subnet4_param", "subnet",
  "$@58", "subnet_4o6_interface", "$@59", "subnet_4o6_interface_id",
  "$@60", "subnet_4o6_subnet", "$@61", "interface", "$@62", "client_class",
  "$@63", "require_client_classes", "$@64", "reservations_global",
  "reservations_in_subnet", "reservations_out_of_pool", "reservation_mode",
  "$@65", "hr_mode", "id", "shared_networks", "$@66",
  "shared_networks_content", "shared_networks_list", "shared_network",
  "$@67", "shared_network_params", "shared_network_param",
  "option_def_list", "$@68", "sub_option_def_list", "$@69",
  "option_def_list_content", "not_empty_option_def_list",
  "option_def_entry", "$@70", "sub_option_def", "$@71",
  "option_def_params", "not_empty_option_def_params", "option_def_param",
  "option_def_name", "code", "option_def_code", "option_def_type", "$@72",
  "option_def_record_types", "$@73", "space", "$@74", "option_def_space",
  "option_def_encapsulate", "$@75", "option_def_array", "option_data_list",
  "$@76", "option_data_list_content", "not_empty_option_data_list",
  "option_data_entry", "$@77", "sub_option_data", "$@78",
  "option_data_params", "not_empty_option_data_params",
  "option_data_param", "option_data_name", "option_data_data", "$@79",
  "option_data_code", "option_data_space", "option_data_csv_format",
  "option_data_always_send", "pools_list", "$@80", "pools_list_content",
  "not_empty_pools_list", "pool_list_entry", "$@81", "sub_pool4", "$@82",
  "pool_params", "pool_param", "pool_entry", "$@83", "user_context",
  "$@84", "comment", "$@85", "reservations", "$@86", "reservations_list",
  "not_empty_reservations_list", "reservation", "$@87", "sub_reservation",
  "$@88", "reservation_params", "not_empty_reservation_params",
  "reservation_param", "next_server", "$@89", "server_hostname", "$@90",
  "boot_file_name", "$@91", "ip_address", "$@92", "ip_addresses", "$@93",
  "duid", "$@94", "hw_address", "$@95", "client_id_value", "$@96",
  "circuit_id_value", "$@97", "flex_id_value", "$@98", "hostname", "$@99",
  "reservation_client_classes", "$@100", "relay", "$@101", "relay_map",
  "client_classes", "$@102", "client_classes_list", "client_class_entry",
  "$@103", "client_class_params", "not_empty_client_class_params",
  "client_class_param", "client_class_name", "client_class_test", "$@104",
  "only_if_required", "dhcp4o6_port", "control_socket", "$@105",
  "control_socket_params", "control_socket_param", "control_socket_type",
  "$@106", "control_socket_name", "$@107", "dhcp_queue_control", "$@108",
  "queue_control_params", "queue_control_param", "enable_queue",
  "queue_type", "$@109", "capacity", "arbitrary_map_entry", "$@110",
  "dhcp_ddns", "$@111", "sub_dhcp_ddns", "$@112", "dhcp_ddns_params",
  "dhcp_ddns_param", "enable_updates", "server_ip", "$@113", "server_port",
  "sender_ip", "$@114", "sender_port", "max_queue_size", "ncr_protocol",
  "$@115", "ncr_protocol_value", "ncr_format", "$@116",
  "dep_qualifying_suffix", "$@117", "dep_override_no_update",
  "dep_override_client_update", "dep_replace_client_name", "$@118",
  "dep_generated_prefix", "$@119", "dep_hostname_char_set", "$@120",
  "dep_hostname_char_replacement", "$@121", "config_control", "$@122",
  "sub_config_control", "$@123", "config_control_params",
  "config_control_param", "config_databases", "$@124",
  "config_fetch_wait_time", "loggers", "$@125", "loggers_entries",
  "logger_entry", "$@126", "logger_params", "logger_param", "debuglevel",
  "severity", "$@127", "output_options_list", "$@128",
  "output_options_list_content", "output_entry", "$@129",
  "output_params_list", "output_params", "output", "$@130", "flush",
  "maxsize", "maxver", "pattern", "$@131", "compatibility", "$@132",
  "compatibility_params", "compatibility_param", "lenient_option_parsing", YY_NULLPTR
  };

#if PARSER4_DEBUG
  const short
  Dhcp4Parser::yyrline_[] =
  {
       0,   292,   292,   292,   293,   293,   294,   294,   295,   295,
     296,   296,   297,   297,   298,   298,   299,   299,   300,   300,
     301,   301,   302,   302,   303,   303,   304,   304,   312,   313,
     314,   315,   316,   317,   318,   321,   326,   326,   337,   340,
     341,   344,   349,   355,   360,   360,   367,   368,   371,   375,
     379,   385,   385,   392,   393,   396,   400,   404,   414,   423,
     423,   438,   438,   452,   455,   461,   461,   470,   471,   472,
     479,   480,   481,   482,   483,   484,   485,   486,   487,   488,
     489,   490,   491,   492,   493,   494,   495,   496,   497,   498,
     499,   500,   501,   502,   503,   504,   505,   506,   507,   508,
     509,   510,   511,   512,   513,   514,   515,   516,   517,   518,
     519,   520,   521,   522,   523,   524,   525,   526,   527,   528,
     529,   530,   531,   532,   533,   534,   535,   536,   537,   538,
     539,   540,   541,   542,   545,   551,   557,   563,   569,   575,
     581,   587,   593,   599,   605,   611,   611,   620,   626,   632,
     638,   644,   650,   656,   662,   662,   671,   674,   677,   680,
     683,   689,   689,   698,   698,   707,   713,   719,   719,   728,
     728,   737,   743,   749,   755,   761,   767,   773,   773,   785,
     786,   787,   792,   793,   794,   795,   796,   797,   798,   801,
     801,   810,   810,   821,   821,   829,   830,   833,   833,   841,
     843,   847,   854,   854,   867,   867,   878,   879,   880,   885,
     887,   887,   906,   906,   919,   919,   930,   931,   934,   935,
     936,   941,   941,   951,   952,   953,   958,   959,   960,   961,
     962,   963,   964,   965,   966,   967,   968,   969,   970,   971,
     972,   973,   974,   975,   976,   979,   979,   987,   988,   989,
     992,   992,  1001,  1001,  1010,  1010,  1019,  1025,  1025,  1034,
    1040,  1046,  1052,  1058,  1064,  1070,  1070,  1078,  1079,  1080,
    1083,  1089,  1089,  1098,  1098,  1107,  1107,  1116,  1116,  1125,
    1125,  1136,  1137,  1138,  1143,  1144,  1145,  1146,  1147,  1150,
    1155,  1160,  1165,  1170,  1177,  1177,  1190,  1191,  1192,  1197,
    1198,  1199,  1200,  1201,  1202,  1205,  1211,  1217,  1223,  1223,
    1234,  1235,  1238,  1239,  1240,  1245,  1245,  1255,  1255,  1265,
    1266,  1267,  1270,  1273,  1274,  1277,  1277,  1286,  1286,  1295,
    1295,  1307,  1308,  1309,  1314,  1315,  1316,  1317,  1318,  1319,
    1322,  1328,  1334,  1340,  1346,  1352,  1361,  1361,  1375,  1376,
    1379,  1380,  1381,  1390,  1390,  1416,  1416,  1427,  1428,  1429,
    1435,  1436,  1437,  1438,  1439,  1440,  1441,  1442,  1443,  1444,
    1445,  1446,  1447,  1448,  1449,  1450,  1451,  1452,  1453,  1454,
    1455,  1456,  1457,  1458,  1459,  1460,  1461,  1462,  1463,  1464,
    1465,  1466,  1467,  1468,  1469,  1470,  1471,  1472,  1473,  1474,
    1475,  1476,  1477,  1478,  1479,  1482,  1482,  1491,  1491,  1500,
    1500,  1509,  1509,  1518,  1518,  1527,  1527,  1536,  1536,  1547,
    1553,  1559,  1565,  1565,  1573,  1574,  1575,  1576,  1579,  1587,
    1587,  1599,  1600,  1604,  1605,  1606,  1611,  1611,  1619,  1620,
    1621,  1626,  1627,  1628,  1629,  1630,  1631,  1632,  1633,  1634,
    1635,  1636,  1637,  1638,  1639,  1640,  1641,  1642,  1643,  1644,
    1645,  1646,  1647,  1648,  1649,  1650,  1651,  1652,  1653,  1654,
    1655,  1656,  1657,  1658,  1659,  1660,  1661,  1662,  1663,  1664,
    1665,  1672,  1672,  1686,  1686,  1695,  1696,  1699,  1700,  1701,
    1708,  1708,  1723,  1723,  1737,  1738,  1741,  1742,  1743,  1748,
    1749,  1750,  1751,  1752,  1753,  1754,  1755,  1756,  1757,  1760,
    1762,  1768,  1770,  1770,  1779,  1779,  1788,  1788,  1797,  1799,
    1799,  1808,  1818,  1818,  1831,  1832,  1837,  1838,  1839,  1846,
    1846,  1858,  1858,  1870,  1871,  1876,  1877,  1878,  1885,  1886,
    1887,  1888,  1889,  1890,  1891,  1892,  1893,  1896,  1898,  1898,
    1907,  1909,  1911,  1917,  1926,  1926,  1939,  1940,  1943,  1944,
    1945,  1950,  1950,  1960,  1960,  1970,  1971,  1972,  1977,  1978,
    1979,  1980,  1981,  1982,  1983,  1986,  1986,  1995,  1995,  2020,
    2020,  2050,  2050,  2061,  2062,  2065,  2066,  2067,  2072,  2072,
    2081,  2081,  2090,  2091,  2094,  2095,  2096,  2102,  2103,  2104,
    2105,  2106,  2107,  2108,  2109,  2110,  2111,  2112,  2113,  2114,
    2115,  2116,  2119,  2119,  2128,  2128,  2137,  2137,  2146,  2146,
    2155,  2155,  2166,  2166,  2175,  2175,  2184,  2184,  2193,  2193,
    2202,  2202,  2211,  2211,  2220,  2220,  2234,  2234,  2245,  2246,
    2252,  2252,  2263,  2264,  2265,  2270,  2270,  2280,  2281,  2284,
    2285,  2286,  2291,  2292,  2293,  2294,  2295,  2296,  2297,  2298,
    2299,  2300,  2301,  2302,  2303,  2304,  2307,  2309,  2309,  2318,
    2326,  2334,  2334,  2345,  2346,  2347,  2352,  2353,  2354,  2355,
    2356,  2359,  2359,  2368,  2368,  2380,  2380,  2393,  2394,  2395,
    2400,  2401,  2402,  2403,  2404,  2405,  2408,  2414,  2414,  2423,
    2429,  2429,  2439,  2439,  2452,  2452,  2462,  2463,  2464,  2469,
    2470,  2471,  2472,  2473,  2474,  2475,  2476,  2477,  2478,  2479,
    2480,  2481,  2482,  2483,  2484,  2485,  2486,  2489,  2495,  2495,
    2504,  2510,  2510,  2519,  2525,  2531,  2531,  2540,  2541,  2544,
    2544,  2554,  2554,  2564,  2571,  2578,  2578,  2587,  2587,  2597,
    2597,  2607,  2607,  2619,  2619,  2631,  2631,  2641,  2642,  2643,
    2649,  2650,  2653,  2653,  2664,  2672,  2672,  2685,  2686,  2687,
    2693,  2693,  2701,  2702,  2703,  2708,  2709,  2710,  2711,  2712,
    2713,  2714,  2717,  2723,  2723,  2732,  2732,  2743,  2744,  2745,
    2750,  2750,  2758,  2759,  2760,  2765,  2766,  2767,  2768,  2769,
    2772,  2772,  2781,  2787,  2793,  2799,  2799,  2808,  2808,  2819,
    2820,  2821,  2826,  2827,  2830
  };

  // Print the state stack on the debug stream.
  void
  Dhcp4Parser::yystack_print_ ()
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
  Dhcp4Parser::yy_reduce_print_ (int yyrule)
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
#line 6082 "dhcp4_parser.cc"

#line 2836 "dhcp4_parser.yy"


void
isc::dhcp::Dhcp4Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
