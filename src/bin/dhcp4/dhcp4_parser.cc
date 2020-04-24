// A Bison parser, made by GNU Bison 3.5.4.

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
      case 211: // value
      case 215: // map_value
      case 256: // ddns_replace_client_name_value
      case 278: // socket_type
      case 281: // outbound_interface_value
      case 303: // db_type
      case 397: // hr_mode
      case 552: // ncr_protocol_value
        value.YY_MOVE_OR_COPY< ElementPtr > (YY_MOVE (that.value));
        break;

      case 194: // "boolean"
        value.YY_MOVE_OR_COPY< bool > (YY_MOVE (that.value));
        break;

      case 193: // "floating point"
        value.YY_MOVE_OR_COPY< double > (YY_MOVE (that.value));
        break;

      case 192: // "integer"
        value.YY_MOVE_OR_COPY< int64_t > (YY_MOVE (that.value));
        break;

      case 191: // "constant string"
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
      case 211: // value
      case 215: // map_value
      case 256: // ddns_replace_client_name_value
      case 278: // socket_type
      case 281: // outbound_interface_value
      case 303: // db_type
      case 397: // hr_mode
      case 552: // ncr_protocol_value
        value.move< ElementPtr > (YY_MOVE (that.value));
        break;

      case 194: // "boolean"
        value.move< bool > (YY_MOVE (that.value));
        break;

      case 193: // "floating point"
        value.move< double > (YY_MOVE (that.value));
        break;

      case 192: // "integer"
        value.move< int64_t > (YY_MOVE (that.value));
        break;

      case 191: // "constant string"
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
      case 211: // value
      case 215: // map_value
      case 256: // ddns_replace_client_name_value
      case 278: // socket_type
      case 281: // outbound_interface_value
      case 303: // db_type
      case 397: // hr_mode
      case 552: // ncr_protocol_value
        value.copy< ElementPtr > (that.value);
        break;

      case 194: // "boolean"
        value.copy< bool > (that.value);
        break;

      case 193: // "floating point"
        value.copy< double > (that.value);
        break;

      case 192: // "integer"
        value.copy< int64_t > (that.value);
        break;

      case 191: // "constant string"
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
      case 211: // value
      case 215: // map_value
      case 256: // ddns_replace_client_name_value
      case 278: // socket_type
      case 281: // outbound_interface_value
      case 303: // db_type
      case 397: // hr_mode
      case 552: // ncr_protocol_value
        value.move< ElementPtr > (that.value);
        break;

      case 194: // "boolean"
        value.move< bool > (that.value);
        break;

      case 193: // "floating point"
        value.move< double > (that.value);
        break;

      case 192: // "integer"
        value.move< int64_t > (that.value);
        break;

      case 191: // "constant string"
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
      case 191: // "constant string"
#line 274 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < std::string > (); }
#line 447 "dhcp4_parser.cc"
        break;

      case 192: // "integer"
#line 274 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < int64_t > (); }
#line 453 "dhcp4_parser.cc"
        break;

      case 193: // "floating point"
#line 274 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < double > (); }
#line 459 "dhcp4_parser.cc"
        break;

      case 194: // "boolean"
#line 274 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < bool > (); }
#line 465 "dhcp4_parser.cc"
        break;

      case 211: // value
#line 274 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 471 "dhcp4_parser.cc"
        break;

      case 215: // map_value
#line 274 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 477 "dhcp4_parser.cc"
        break;

      case 256: // ddns_replace_client_name_value
#line 274 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 483 "dhcp4_parser.cc"
        break;

      case 278: // socket_type
#line 274 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 489 "dhcp4_parser.cc"
        break;

      case 281: // outbound_interface_value
#line 274 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 495 "dhcp4_parser.cc"
        break;

      case 303: // db_type
#line 274 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 501 "dhcp4_parser.cc"
        break;

      case 397: // hr_mode
#line 274 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 507 "dhcp4_parser.cc"
        break;

      case 552: // ncr_protocol_value
#line 274 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 513 "dhcp4_parser.cc"
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
      case 211: // value
      case 215: // map_value
      case 256: // ddns_replace_client_name_value
      case 278: // socket_type
      case 281: // outbound_interface_value
      case 303: // db_type
      case 397: // hr_mode
      case 552: // ncr_protocol_value
        yylhs.value.emplace< ElementPtr > ();
        break;

      case 194: // "boolean"
        yylhs.value.emplace< bool > ();
        break;

      case 193: // "floating point"
        yylhs.value.emplace< double > ();
        break;

      case 192: // "integer"
        yylhs.value.emplace< int64_t > ();
        break;

      case 191: // "constant string"
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
#line 283 "dhcp4_parser.yy"
                     { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 781 "dhcp4_parser.cc"
    break;

  case 4:
#line 284 "dhcp4_parser.yy"
                      { ctx.ctx_ = ctx.CONFIG; }
#line 787 "dhcp4_parser.cc"
    break;

  case 6:
#line 285 "dhcp4_parser.yy"
                 { ctx.ctx_ = ctx.DHCP4; }
#line 793 "dhcp4_parser.cc"
    break;

  case 8:
#line 286 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 799 "dhcp4_parser.cc"
    break;

  case 10:
#line 287 "dhcp4_parser.yy"
                   { ctx.ctx_ = ctx.SUBNET4; }
#line 805 "dhcp4_parser.cc"
    break;

  case 12:
#line 288 "dhcp4_parser.yy"
                 { ctx.ctx_ = ctx.POOLS; }
#line 811 "dhcp4_parser.cc"
    break;

  case 14:
#line 289 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.RESERVATIONS; }
#line 817 "dhcp4_parser.cc"
    break;

  case 16:
#line 290 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.DHCP4; }
#line 823 "dhcp4_parser.cc"
    break;

  case 18:
#line 291 "dhcp4_parser.yy"
                      { ctx.ctx_ = ctx.OPTION_DEF; }
#line 829 "dhcp4_parser.cc"
    break;

  case 20:
#line 292 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.OPTION_DATA; }
#line 835 "dhcp4_parser.cc"
    break;

  case 22:
#line 293 "dhcp4_parser.yy"
                         { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 841 "dhcp4_parser.cc"
    break;

  case 24:
#line 294 "dhcp4_parser.yy"
                     { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 847 "dhcp4_parser.cc"
    break;

  case 26:
#line 295 "dhcp4_parser.yy"
                   { ctx.ctx_ = ctx.LOGGING; }
#line 853 "dhcp4_parser.cc"
    break;

  case 28:
#line 296 "dhcp4_parser.yy"
                          { ctx.ctx_ = ctx.CONFIG_CONTROL; }
#line 859 "dhcp4_parser.cc"
    break;

  case 30:
#line 304 "dhcp4_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 865 "dhcp4_parser.cc"
    break;

  case 31:
#line 305 "dhcp4_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location))); }
#line 871 "dhcp4_parser.cc"
    break;

  case 32:
#line 306 "dhcp4_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 877 "dhcp4_parser.cc"
    break;

  case 33:
#line 307 "dhcp4_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 883 "dhcp4_parser.cc"
    break;

  case 34:
#line 308 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 889 "dhcp4_parser.cc"
    break;

  case 35:
#line 309 "dhcp4_parser.yy"
            { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 895 "dhcp4_parser.cc"
    break;

  case 36:
#line 310 "dhcp4_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 901 "dhcp4_parser.cc"
    break;

  case 37:
#line 313 "dhcp4_parser.yy"
                {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as < ElementPtr > ());
}
#line 910 "dhcp4_parser.cc"
    break;

  case 38:
#line 318 "dhcp4_parser.yy"
                     {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 921 "dhcp4_parser.cc"
    break;

  case 39:
#line 323 "dhcp4_parser.yy"
                             {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 931 "dhcp4_parser.cc"
    break;

  case 40:
#line 329 "dhcp4_parser.yy"
                { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 937 "dhcp4_parser.cc"
    break;

  case 43:
#line 336 "dhcp4_parser.yy"
                                  {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 946 "dhcp4_parser.cc"
    break;

  case 44:
#line 340 "dhcp4_parser.yy"
                                                      {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 956 "dhcp4_parser.cc"
    break;

  case 45:
#line 347 "dhcp4_parser.yy"
                              {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 965 "dhcp4_parser.cc"
    break;

  case 46:
#line 350 "dhcp4_parser.yy"
                               {
    // list parsing complete. Put any sanity checking here
}
#line 973 "dhcp4_parser.cc"
    break;

  case 49:
#line 358 "dhcp4_parser.yy"
                      {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 982 "dhcp4_parser.cc"
    break;

  case 50:
#line 362 "dhcp4_parser.yy"
                                           {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 991 "dhcp4_parser.cc"
    break;

  case 51:
#line 369 "dhcp4_parser.yy"
                              {
    // List parsing about to start
}
#line 999 "dhcp4_parser.cc"
    break;

  case 52:
#line 371 "dhcp4_parser.yy"
                                       {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 1008 "dhcp4_parser.cc"
    break;

  case 55:
#line 380 "dhcp4_parser.yy"
                               {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 1017 "dhcp4_parser.cc"
    break;

  case 56:
#line 384 "dhcp4_parser.yy"
                                                            {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 1026 "dhcp4_parser.cc"
    break;

  case 57:
#line 395 "dhcp4_parser.yy"
                                {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as < std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 1037 "dhcp4_parser.cc"
    break;

  case 58:
#line 405 "dhcp4_parser.yy"
                           {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1048 "dhcp4_parser.cc"
    break;

  case 59:
#line 410 "dhcp4_parser.yy"
                                {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.

    // Dhcp4 is required
    ctx.require("Dhcp4", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
}
#line 1061 "dhcp4_parser.cc"
    break;

  case 68:
#line 434 "dhcp4_parser.yy"
                    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Dhcp4", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP4);
}
#line 1074 "dhcp4_parser.cc"
    break;

  case 69:
#line 441 "dhcp4_parser.yy"
                                                    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1084 "dhcp4_parser.cc"
    break;

  case 70:
#line 449 "dhcp4_parser.yy"
                          {
    // Parse the Dhcp4 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1094 "dhcp4_parser.cc"
    break;

  case 71:
#line 453 "dhcp4_parser.yy"
                               {
    // No global parameter is required
    // parsing completed
}
#line 1103 "dhcp4_parser.cc"
    break;

  case 126:
#line 518 "dhcp4_parser.yy"
                                             {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1112 "dhcp4_parser.cc"
    break;

  case 127:
#line 523 "dhcp4_parser.yy"
                                                     {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-valid-lifetime", prf);
}
#line 1121 "dhcp4_parser.cc"
    break;

  case 128:
#line 528 "dhcp4_parser.yy"
                                                     {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-valid-lifetime", prf);
}
#line 1130 "dhcp4_parser.cc"
    break;

  case 129:
#line 533 "dhcp4_parser.yy"
                                       {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1139 "dhcp4_parser.cc"
    break;

  case 130:
#line 538 "dhcp4_parser.yy"
                                         {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1148 "dhcp4_parser.cc"
    break;

  case 131:
#line 543 "dhcp4_parser.yy"
                                                       {
    ElementPtr ctt(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("calculate-tee-times", ctt);
}
#line 1157 "dhcp4_parser.cc"
    break;

  case 132:
#line 548 "dhcp4_parser.yy"
                                   {
    ElementPtr t1(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t1-percent", t1);
}
#line 1166 "dhcp4_parser.cc"
    break;

  case 133:
#line 553 "dhcp4_parser.yy"
                                   {
    ElementPtr t2(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t2-percent", t2);
}
#line 1175 "dhcp4_parser.cc"
    break;

  case 134:
#line 558 "dhcp4_parser.yy"
                                                                 {
    ElementPtr dpp(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1184 "dhcp4_parser.cc"
    break;

  case 135:
#line 563 "dhcp4_parser.yy"
                       {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1192 "dhcp4_parser.cc"
    break;

  case 136:
#line 565 "dhcp4_parser.yy"
               {
    ElementPtr stag(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-tag", stag);
    ctx.leave();
}
#line 1202 "dhcp4_parser.cc"
    break;

  case 137:
#line 571 "dhcp4_parser.yy"
                                             {
    ElementPtr echo(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("echo-client-id", echo);
}
#line 1211 "dhcp4_parser.cc"
    break;

  case 138:
#line 576 "dhcp4_parser.yy"
                                               {
    ElementPtr match(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("match-client-id", match);
}
#line 1220 "dhcp4_parser.cc"
    break;

  case 139:
#line 581 "dhcp4_parser.yy"
                                           {
    ElementPtr prf(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("authoritative", prf);
}
#line 1229 "dhcp4_parser.cc"
    break;

  case 140:
#line 586 "dhcp4_parser.yy"
                                                   {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-send-updates", b);
}
#line 1238 "dhcp4_parser.cc"
    break;

  case 141:
#line 591 "dhcp4_parser.yy"
                                                               {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-no-update", b);
}
#line 1247 "dhcp4_parser.cc"
    break;

  case 142:
#line 596 "dhcp4_parser.yy"
                                                                       {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-client-update", b);
}
#line 1256 "dhcp4_parser.cc"
    break;

  case 143:
#line 601 "dhcp4_parser.yy"
                                                   {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 1264 "dhcp4_parser.cc"
    break;

  case 144:
#line 603 "dhcp4_parser.yy"
                                       {
    ctx.stack_.back()->set("ddns-replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1273 "dhcp4_parser.cc"
    break;

  case 145:
#line 609 "dhcp4_parser.yy"
                 {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1281 "dhcp4_parser.cc"
    break;

  case 146:
#line 612 "dhcp4_parser.yy"
          {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 1289 "dhcp4_parser.cc"
    break;

  case 147:
#line 615 "dhcp4_parser.yy"
           {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 1297 "dhcp4_parser.cc"
    break;

  case 148:
#line 618 "dhcp4_parser.yy"
                     {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1305 "dhcp4_parser.cc"
    break;

  case 149:
#line 621 "dhcp4_parser.yy"
            {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 1314 "dhcp4_parser.cc"
    break;

  case 150:
#line 627 "dhcp4_parser.yy"
                                             {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1322 "dhcp4_parser.cc"
    break;

  case 151:
#line 629 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-generated-prefix", s);
    ctx.leave();
}
#line 1332 "dhcp4_parser.cc"
    break;

  case 152:
#line 635 "dhcp4_parser.yy"
                                               {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1340 "dhcp4_parser.cc"
    break;

  case 153:
#line 637 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-qualifying-suffix", s);
    ctx.leave();
}
#line 1350 "dhcp4_parser.cc"
    break;

  case 154:
#line 643 "dhcp4_parser.yy"
                                     {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1358 "dhcp4_parser.cc"
    break;

  case 155:
#line 645 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 1368 "dhcp4_parser.cc"
    break;

  case 156:
#line 651 "dhcp4_parser.yy"
                                                     {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1376 "dhcp4_parser.cc"
    break;

  case 157:
#line 653 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 1386 "dhcp4_parser.cc"
    break;

  case 158:
#line 659 "dhcp4_parser.yy"
                                                       {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("store-extended-info", b);
}
#line 1395 "dhcp4_parser.cc"
    break;

  case 159:
#line 664 "dhcp4_parser.yy"
                                                                             {
    ElementPtr count(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-count", count);
}
#line 1404 "dhcp4_parser.cc"
    break;

  case 160:
#line 669 "dhcp4_parser.yy"
                                                                         {
    ElementPtr age(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-age", age);
}
#line 1413 "dhcp4_parser.cc"
    break;

  case 161:
#line 674 "dhcp4_parser.yy"
                                     {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1424 "dhcp4_parser.cc"
    break;

  case 162:
#line 679 "dhcp4_parser.yy"
                                                               {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1434 "dhcp4_parser.cc"
    break;

  case 172:
#line 698 "dhcp4_parser.yy"
                                {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1444 "dhcp4_parser.cc"
    break;

  case 173:
#line 702 "dhcp4_parser.yy"
                                          {
    // No interfaces config param is required
    // parsing completed
}
#line 1453 "dhcp4_parser.cc"
    break;

  case 174:
#line 707 "dhcp4_parser.yy"
                            {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1464 "dhcp4_parser.cc"
    break;

  case 175:
#line 712 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1473 "dhcp4_parser.cc"
    break;

  case 176:
#line 717 "dhcp4_parser.yy"
                                   {
    ctx.enter(ctx.DHCP_SOCKET_TYPE);
}
#line 1481 "dhcp4_parser.cc"
    break;

  case 177:
#line 719 "dhcp4_parser.yy"
                    {
    ctx.stack_.back()->set("dhcp-socket-type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1490 "dhcp4_parser.cc"
    break;

  case 178:
#line 724 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("raw", ctx.loc2pos(yystack_[0].location))); }
#line 1496 "dhcp4_parser.cc"
    break;

  case 179:
#line 725 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("udp", ctx.loc2pos(yystack_[0].location))); }
#line 1502 "dhcp4_parser.cc"
    break;

  case 180:
#line 728 "dhcp4_parser.yy"
                                       {
    ctx.enter(ctx.OUTBOUND_INTERFACE);
}
#line 1510 "dhcp4_parser.cc"
    break;

  case 181:
#line 730 "dhcp4_parser.yy"
                                 {
    ctx.stack_.back()->set("outbound-interface", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1519 "dhcp4_parser.cc"
    break;

  case 182:
#line 735 "dhcp4_parser.yy"
                                          {
    yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("same-as-inbound", ctx.loc2pos(yystack_[0].location)));
}
#line 1527 "dhcp4_parser.cc"
    break;

  case 183:
#line 737 "dhcp4_parser.yy"
                {
    yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("use-routing", ctx.loc2pos(yystack_[0].location)));
    }
#line 1535 "dhcp4_parser.cc"
    break;

  case 184:
#line 741 "dhcp4_parser.yy"
                                   {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1544 "dhcp4_parser.cc"
    break;

  case 185:
#line 747 "dhcp4_parser.yy"
                               {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1555 "dhcp4_parser.cc"
    break;

  case 186:
#line 752 "dhcp4_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1566 "dhcp4_parser.cc"
    break;

  case 187:
#line 759 "dhcp4_parser.yy"
                             {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sanity-checks", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SANITY_CHECKS);
}
#line 1577 "dhcp4_parser.cc"
    break;

  case 188:
#line 764 "dhcp4_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1586 "dhcp4_parser.cc"
    break;

  case 192:
#line 774 "dhcp4_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1594 "dhcp4_parser.cc"
    break;

  case 193:
#line 776 "dhcp4_parser.yy"
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
#line 1614 "dhcp4_parser.cc"
    break;

  case 194:
#line 792 "dhcp4_parser.yy"
                               {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1625 "dhcp4_parser.cc"
    break;

  case 195:
#line 797 "dhcp4_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1636 "dhcp4_parser.cc"
    break;

  case 196:
#line 804 "dhcp4_parser.yy"
                                 {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1647 "dhcp4_parser.cc"
    break;

  case 197:
#line 809 "dhcp4_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1656 "dhcp4_parser.cc"
    break;

  case 202:
#line 822 "dhcp4_parser.yy"
                         {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1666 "dhcp4_parser.cc"
    break;

  case 203:
#line 826 "dhcp4_parser.yy"
                                     {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1676 "dhcp4_parser.cc"
    break;

  case 227:
#line 859 "dhcp4_parser.yy"
                    {
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1684 "dhcp4_parser.cc"
    break;

  case 228:
#line 861 "dhcp4_parser.yy"
                {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1693 "dhcp4_parser.cc"
    break;

  case 229:
#line 866 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1699 "dhcp4_parser.cc"
    break;

  case 230:
#line 867 "dhcp4_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1705 "dhcp4_parser.cc"
    break;

  case 231:
#line 868 "dhcp4_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1711 "dhcp4_parser.cc"
    break;

  case 232:
#line 869 "dhcp4_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1717 "dhcp4_parser.cc"
    break;

  case 233:
#line 872 "dhcp4_parser.yy"
           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1725 "dhcp4_parser.cc"
    break;

  case 234:
#line 874 "dhcp4_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1735 "dhcp4_parser.cc"
    break;

  case 235:
#line 880 "dhcp4_parser.yy"
                   {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1743 "dhcp4_parser.cc"
    break;

  case 236:
#line 882 "dhcp4_parser.yy"
               {
    ElementPtr pwd(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1753 "dhcp4_parser.cc"
    break;

  case 237:
#line 888 "dhcp4_parser.yy"
           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1761 "dhcp4_parser.cc"
    break;

  case 238:
#line 890 "dhcp4_parser.yy"
               {
    ElementPtr h(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1771 "dhcp4_parser.cc"
    break;

  case 239:
#line 896 "dhcp4_parser.yy"
                         {
    ElementPtr p(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1780 "dhcp4_parser.cc"
    break;

  case 240:
#line 901 "dhcp4_parser.yy"
           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1788 "dhcp4_parser.cc"
    break;

  case 241:
#line 903 "dhcp4_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1798 "dhcp4_parser.cc"
    break;

  case 242:
#line 909 "dhcp4_parser.yy"
                               {
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1807 "dhcp4_parser.cc"
    break;

  case 243:
#line 914 "dhcp4_parser.yy"
                                         {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1816 "dhcp4_parser.cc"
    break;

  case 244:
#line 919 "dhcp4_parser.yy"
                                 {
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1825 "dhcp4_parser.cc"
    break;

  case 245:
#line 924 "dhcp4_parser.yy"
                                               {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1834 "dhcp4_parser.cc"
    break;

  case 246:
#line 929 "dhcp4_parser.yy"
                                               {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("request-timeout", n);
}
#line 1843 "dhcp4_parser.cc"
    break;

  case 247:
#line 934 "dhcp4_parser.yy"
                                           {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-keepalive", n);
}
#line 1852 "dhcp4_parser.cc"
    break;

  case 248:
#line 939 "dhcp4_parser.yy"
                                       {
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-nodelay", n);
}
#line 1861 "dhcp4_parser.cc"
    break;

  case 249:
#line 944 "dhcp4_parser.yy"
                               {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1869 "dhcp4_parser.cc"
    break;

  case 250:
#line 946 "dhcp4_parser.yy"
               {
    ElementPtr cp(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1879 "dhcp4_parser.cc"
    break;

  case 251:
#line 952 "dhcp4_parser.yy"
                   {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1887 "dhcp4_parser.cc"
    break;

  case 252:
#line 954 "dhcp4_parser.yy"
               {
    ElementPtr ks(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 1897 "dhcp4_parser.cc"
    break;

  case 253:
#line 960 "dhcp4_parser.yy"
                         {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1905 "dhcp4_parser.cc"
    break;

  case 254:
#line 962 "dhcp4_parser.yy"
               {
    ElementPtr c(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("consistency", c);
    ctx.leave();
}
#line 1915 "dhcp4_parser.cc"
    break;

  case 255:
#line 968 "dhcp4_parser.yy"
                                       {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1923 "dhcp4_parser.cc"
    break;

  case 256:
#line 970 "dhcp4_parser.yy"
               {
    ElementPtr c(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("serial-consistency", c);
    ctx.leave();
}
#line 1933 "dhcp4_parser.cc"
    break;

  case 257:
#line 976 "dhcp4_parser.yy"
                                                       {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 1942 "dhcp4_parser.cc"
    break;

  case 258:
#line 981 "dhcp4_parser.yy"
                                                       {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 1951 "dhcp4_parser.cc"
    break;

  case 259:
#line 986 "dhcp4_parser.yy"
                                             {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-row-errors", n);
}
#line 1960 "dhcp4_parser.cc"
    break;

  case 260:
#line 992 "dhcp4_parser.yy"
                                                           {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1971 "dhcp4_parser.cc"
    break;

  case 261:
#line 997 "dhcp4_parser.yy"
                                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1980 "dhcp4_parser.cc"
    break;

  case 269:
#line 1013 "dhcp4_parser.yy"
               {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1989 "dhcp4_parser.cc"
    break;

  case 270:
#line 1018 "dhcp4_parser.yy"
                           {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1998 "dhcp4_parser.cc"
    break;

  case 271:
#line 1023 "dhcp4_parser.yy"
                        {
    ElementPtr circuit(new StringElement("circuit-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(circuit);
}
#line 2007 "dhcp4_parser.cc"
    break;

  case 272:
#line 1028 "dhcp4_parser.yy"
                      {
    ElementPtr client(new StringElement("client-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(client);
}
#line 2016 "dhcp4_parser.cc"
    break;

  case 273:
#line 1033 "dhcp4_parser.yy"
                 {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 2025 "dhcp4_parser.cc"
    break;

  case 274:
#line 1040 "dhcp4_parser.yy"
                                           {
    ElementPtr mt(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("multi-threading", mt);
    ctx.stack_.push_back(mt);
    ctx.enter(ctx.DHCP_MULTI_THREADING);
}
#line 2036 "dhcp4_parser.cc"
    break;

  case 275:
#line 1045 "dhcp4_parser.yy"
                                                             {
    // The enable parameter is required.
    ctx.require("enable-multi-threading", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2047 "dhcp4_parser.cc"
    break;

  case 284:
#line 1064 "dhcp4_parser.yy"
                                                             {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-multi-threading", b);
}
#line 2056 "dhcp4_parser.cc"
    break;

  case 285:
#line 1069 "dhcp4_parser.yy"
                                                 {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("thread-pool-size", prf);
}
#line 2065 "dhcp4_parser.cc"
    break;

  case 286:
#line 1074 "dhcp4_parser.yy"
                                                   {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("packet-queue-size", prf);
}
#line 2074 "dhcp4_parser.cc"
    break;

  case 287:
#line 1079 "dhcp4_parser.yy"
                                 {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 2085 "dhcp4_parser.cc"
    break;

  case 288:
#line 1084 "dhcp4_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2094 "dhcp4_parser.cc"
    break;

  case 293:
#line 1097 "dhcp4_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2104 "dhcp4_parser.cc"
    break;

  case 294:
#line 1101 "dhcp4_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2114 "dhcp4_parser.cc"
    break;

  case 295:
#line 1107 "dhcp4_parser.yy"
                                  {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2124 "dhcp4_parser.cc"
    break;

  case 296:
#line 1111 "dhcp4_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2134 "dhcp4_parser.cc"
    break;

  case 302:
#line 1126 "dhcp4_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2142 "dhcp4_parser.cc"
    break;

  case 303:
#line 1128 "dhcp4_parser.yy"
               {
    ElementPtr lib(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 2152 "dhcp4_parser.cc"
    break;

  case 304:
#line 1134 "dhcp4_parser.yy"
                       {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2160 "dhcp4_parser.cc"
    break;

  case 305:
#line 1136 "dhcp4_parser.yy"
              {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2169 "dhcp4_parser.cc"
    break;

  case 306:
#line 1142 "dhcp4_parser.yy"
                                                     {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 2180 "dhcp4_parser.cc"
    break;

  case 307:
#line 1147 "dhcp4_parser.yy"
                                                            {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2190 "dhcp4_parser.cc"
    break;

  case 316:
#line 1165 "dhcp4_parser.yy"
                                                               {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 2199 "dhcp4_parser.cc"
    break;

  case 317:
#line 1170 "dhcp4_parser.yy"
                                                                               {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 2208 "dhcp4_parser.cc"
    break;

  case 318:
#line 1175 "dhcp4_parser.yy"
                                                       {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 2217 "dhcp4_parser.cc"
    break;

  case 319:
#line 1180 "dhcp4_parser.yy"
                                                     {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 2226 "dhcp4_parser.cc"
    break;

  case 320:
#line 1185 "dhcp4_parser.yy"
                                                 {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 2235 "dhcp4_parser.cc"
    break;

  case 321:
#line 1190 "dhcp4_parser.yy"
                                                               {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 2244 "dhcp4_parser.cc"
    break;

  case 322:
#line 1198 "dhcp4_parser.yy"
                      {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet4", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET4);
}
#line 2255 "dhcp4_parser.cc"
    break;

  case 323:
#line 1203 "dhcp4_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2264 "dhcp4_parser.cc"
    break;

  case 328:
#line 1223 "dhcp4_parser.yy"
                        {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2274 "dhcp4_parser.cc"
    break;

  case 329:
#line 1227 "dhcp4_parser.yy"
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
#line 2300 "dhcp4_parser.cc"
    break;

  case 330:
#line 1249 "dhcp4_parser.yy"
                            {
    // Parse the subnet4 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2310 "dhcp4_parser.cc"
    break;

  case 331:
#line 1253 "dhcp4_parser.yy"
                                {
    // The subnet subnet4 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2320 "dhcp4_parser.cc"
    break;

  case 372:
#line 1305 "dhcp4_parser.yy"
               {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2328 "dhcp4_parser.cc"
    break;

  case 373:
#line 1307 "dhcp4_parser.yy"
               {
    ElementPtr subnet(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 2338 "dhcp4_parser.cc"
    break;

  case 374:
#line 1313 "dhcp4_parser.yy"
                                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2346 "dhcp4_parser.cc"
    break;

  case 375:
#line 1315 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface", iface);
    ctx.leave();
}
#line 2356 "dhcp4_parser.cc"
    break;

  case 376:
#line 1321 "dhcp4_parser.yy"
                                                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2364 "dhcp4_parser.cc"
    break;

  case 377:
#line 1323 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface-id", iface);
    ctx.leave();
}
#line 2374 "dhcp4_parser.cc"
    break;

  case 378:
#line 1329 "dhcp4_parser.yy"
                                     {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2382 "dhcp4_parser.cc"
    break;

  case 379:
#line 1331 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-subnet", iface);
    ctx.leave();
}
#line 2392 "dhcp4_parser.cc"
    break;

  case 380:
#line 1337 "dhcp4_parser.yy"
                     {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2400 "dhcp4_parser.cc"
    break;

  case 381:
#line 1339 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 2410 "dhcp4_parser.cc"
    break;

  case 382:
#line 1345 "dhcp4_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2418 "dhcp4_parser.cc"
    break;

  case 383:
#line 1347 "dhcp4_parser.yy"
               {
    ElementPtr cls(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 2428 "dhcp4_parser.cc"
    break;

  case 384:
#line 1353 "dhcp4_parser.yy"
                                               {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2439 "dhcp4_parser.cc"
    break;

  case 385:
#line 1358 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2448 "dhcp4_parser.cc"
    break;

  case 386:
#line 1363 "dhcp4_parser.yy"
                                   {
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 2456 "dhcp4_parser.cc"
    break;

  case 387:
#line 1365 "dhcp4_parser.yy"
                {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2465 "dhcp4_parser.cc"
    break;

  case 388:
#line 1370 "dhcp4_parser.yy"
                  { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 2471 "dhcp4_parser.cc"
    break;

  case 389:
#line 1371 "dhcp4_parser.yy"
                     { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 2477 "dhcp4_parser.cc"
    break;

  case 390:
#line 1372 "dhcp4_parser.yy"
                { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("global", ctx.loc2pos(yystack_[0].location))); }
#line 2483 "dhcp4_parser.cc"
    break;

  case 391:
#line 1373 "dhcp4_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 2489 "dhcp4_parser.cc"
    break;

  case 392:
#line 1376 "dhcp4_parser.yy"
                     {
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 2498 "dhcp4_parser.cc"
    break;

  case 393:
#line 1383 "dhcp4_parser.yy"
                                 {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 2509 "dhcp4_parser.cc"
    break;

  case 394:
#line 1388 "dhcp4_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2518 "dhcp4_parser.cc"
    break;

  case 399:
#line 1403 "dhcp4_parser.yy"
                               {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2528 "dhcp4_parser.cc"
    break;

  case 400:
#line 1407 "dhcp4_parser.yy"
                                       {
    ctx.stack_.pop_back();
}
#line 2536 "dhcp4_parser.cc"
    break;

  case 436:
#line 1454 "dhcp4_parser.yy"
                            {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 2547 "dhcp4_parser.cc"
    break;

  case 437:
#line 1459 "dhcp4_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2556 "dhcp4_parser.cc"
    break;

  case 438:
#line 1467 "dhcp4_parser.yy"
                                    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2565 "dhcp4_parser.cc"
    break;

  case 439:
#line 1470 "dhcp4_parser.yy"
                                 {
    // parsing completed
}
#line 2573 "dhcp4_parser.cc"
    break;

  case 444:
#line 1486 "dhcp4_parser.yy"
                                 {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2583 "dhcp4_parser.cc"
    break;

  case 445:
#line 1490 "dhcp4_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2595 "dhcp4_parser.cc"
    break;

  case 446:
#line 1501 "dhcp4_parser.yy"
                               {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2605 "dhcp4_parser.cc"
    break;

  case 447:
#line 1505 "dhcp4_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2617 "dhcp4_parser.cc"
    break;

  case 463:
#line 1537 "dhcp4_parser.yy"
                         {
    ElementPtr code(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 2626 "dhcp4_parser.cc"
    break;

  case 465:
#line 1544 "dhcp4_parser.yy"
                      {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2634 "dhcp4_parser.cc"
    break;

  case 466:
#line 1546 "dhcp4_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 2644 "dhcp4_parser.cc"
    break;

  case 467:
#line 1552 "dhcp4_parser.yy"
                                      {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2652 "dhcp4_parser.cc"
    break;

  case 468:
#line 1554 "dhcp4_parser.yy"
               {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 2662 "dhcp4_parser.cc"
    break;

  case 469:
#line 1560 "dhcp4_parser.yy"
             {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2670 "dhcp4_parser.cc"
    break;

  case 470:
#line 1562 "dhcp4_parser.yy"
               {
    ElementPtr space(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 2680 "dhcp4_parser.cc"
    break;

  case 472:
#line 1570 "dhcp4_parser.yy"
                                    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2688 "dhcp4_parser.cc"
    break;

  case 473:
#line 1572 "dhcp4_parser.yy"
               {
    ElementPtr encap(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 2698 "dhcp4_parser.cc"
    break;

  case 474:
#line 1578 "dhcp4_parser.yy"
                                      {
    ElementPtr array(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 2707 "dhcp4_parser.cc"
    break;

  case 475:
#line 1587 "dhcp4_parser.yy"
                              {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 2718 "dhcp4_parser.cc"
    break;

  case 476:
#line 1592 "dhcp4_parser.yy"
                                                                 {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2727 "dhcp4_parser.cc"
    break;

  case 481:
#line 1611 "dhcp4_parser.yy"
                                  {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2737 "dhcp4_parser.cc"
    break;

  case 482:
#line 1615 "dhcp4_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 2746 "dhcp4_parser.cc"
    break;

  case 483:
#line 1623 "dhcp4_parser.yy"
                                {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2756 "dhcp4_parser.cc"
    break;

  case 484:
#line 1627 "dhcp4_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 2765 "dhcp4_parser.cc"
    break;

  case 499:
#line 1660 "dhcp4_parser.yy"
                       {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2773 "dhcp4_parser.cc"
    break;

  case 500:
#line 1662 "dhcp4_parser.yy"
               {
    ElementPtr data(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2783 "dhcp4_parser.cc"
    break;

  case 503:
#line 1672 "dhcp4_parser.yy"
                                                 {
    ElementPtr space(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2792 "dhcp4_parser.cc"
    break;

  case 504:
#line 1677 "dhcp4_parser.yy"
                                                   {
    ElementPtr persist(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 2801 "dhcp4_parser.cc"
    break;

  case 505:
#line 1685 "dhcp4_parser.yy"
                  {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2812 "dhcp4_parser.cc"
    break;

  case 506:
#line 1690 "dhcp4_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2821 "dhcp4_parser.cc"
    break;

  case 511:
#line 1705 "dhcp4_parser.yy"
                                {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2831 "dhcp4_parser.cc"
    break;

  case 512:
#line 1709 "dhcp4_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2841 "dhcp4_parser.cc"
    break;

  case 513:
#line 1715 "dhcp4_parser.yy"
                          {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2851 "dhcp4_parser.cc"
    break;

  case 514:
#line 1719 "dhcp4_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2861 "dhcp4_parser.cc"
    break;

  case 524:
#line 1738 "dhcp4_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2869 "dhcp4_parser.cc"
    break;

  case 525:
#line 1740 "dhcp4_parser.yy"
               {
    ElementPtr pool(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2879 "dhcp4_parser.cc"
    break;

  case 526:
#line 1746 "dhcp4_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2887 "dhcp4_parser.cc"
    break;

  case 527:
#line 1748 "dhcp4_parser.yy"
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
#line 2914 "dhcp4_parser.cc"
    break;

  case 528:
#line 1771 "dhcp4_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2922 "dhcp4_parser.cc"
    break;

  case 529:
#line 1773 "dhcp4_parser.yy"
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
#line 2951 "dhcp4_parser.cc"
    break;

  case 530:
#line 1801 "dhcp4_parser.yy"
                           {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 2962 "dhcp4_parser.cc"
    break;

  case 531:
#line 1806 "dhcp4_parser.yy"
                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2971 "dhcp4_parser.cc"
    break;

  case 536:
#line 1819 "dhcp4_parser.yy"
                            {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2981 "dhcp4_parser.cc"
    break;

  case 537:
#line 1823 "dhcp4_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 2990 "dhcp4_parser.cc"
    break;

  case 538:
#line 1828 "dhcp4_parser.yy"
                                {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3000 "dhcp4_parser.cc"
    break;

  case 539:
#line 1832 "dhcp4_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 3009 "dhcp4_parser.cc"
    break;

  case 559:
#line 1863 "dhcp4_parser.yy"
                         {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3017 "dhcp4_parser.cc"
    break;

  case 560:
#line 1865 "dhcp4_parser.yy"
               {
    ElementPtr next_server(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("next-server", next_server);
    ctx.leave();
}
#line 3027 "dhcp4_parser.cc"
    break;

  case 561:
#line 1871 "dhcp4_parser.yy"
                                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3035 "dhcp4_parser.cc"
    break;

  case 562:
#line 1873 "dhcp4_parser.yy"
               {
    ElementPtr srv(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-hostname", srv);
    ctx.leave();
}
#line 3045 "dhcp4_parser.cc"
    break;

  case 563:
#line 1879 "dhcp4_parser.yy"
                               {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3053 "dhcp4_parser.cc"
    break;

  case 564:
#line 1881 "dhcp4_parser.yy"
               {
    ElementPtr bootfile(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("boot-file-name", bootfile);
    ctx.leave();
}
#line 3063 "dhcp4_parser.cc"
    break;

  case 565:
#line 1887 "dhcp4_parser.yy"
                       {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3071 "dhcp4_parser.cc"
    break;

  case 566:
#line 1889 "dhcp4_parser.yy"
               {
    ElementPtr addr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 3081 "dhcp4_parser.cc"
    break;

  case 567:
#line 1895 "dhcp4_parser.yy"
                           {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3092 "dhcp4_parser.cc"
    break;

  case 568:
#line 1900 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3101 "dhcp4_parser.cc"
    break;

  case 569:
#line 1905 "dhcp4_parser.yy"
           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3109 "dhcp4_parser.cc"
    break;

  case 570:
#line 1907 "dhcp4_parser.yy"
               {
    ElementPtr d(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 3119 "dhcp4_parser.cc"
    break;

  case 571:
#line 1913 "dhcp4_parser.yy"
                       {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3127 "dhcp4_parser.cc"
    break;

  case 572:
#line 1915 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 3137 "dhcp4_parser.cc"
    break;

  case 573:
#line 1921 "dhcp4_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3145 "dhcp4_parser.cc"
    break;

  case 574:
#line 1923 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-id", hw);
    ctx.leave();
}
#line 3155 "dhcp4_parser.cc"
    break;

  case 575:
#line 1929 "dhcp4_parser.yy"
                             {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3163 "dhcp4_parser.cc"
    break;

  case 576:
#line 1931 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("circuit-id", hw);
    ctx.leave();
}
#line 3173 "dhcp4_parser.cc"
    break;

  case 577:
#line 1937 "dhcp4_parser.yy"
                       {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3181 "dhcp4_parser.cc"
    break;

  case 578:
#line 1939 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 3191 "dhcp4_parser.cc"
    break;

  case 579:
#line 1945 "dhcp4_parser.yy"
                   {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3199 "dhcp4_parser.cc"
    break;

  case 580:
#line 1947 "dhcp4_parser.yy"
               {
    ElementPtr host(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 3209 "dhcp4_parser.cc"
    break;

  case 581:
#line 1953 "dhcp4_parser.yy"
                                           {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3220 "dhcp4_parser.cc"
    break;

  case 582:
#line 1958 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3229 "dhcp4_parser.cc"
    break;

  case 583:
#line 1966 "dhcp4_parser.yy"
             {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 3240 "dhcp4_parser.cc"
    break;

  case 584:
#line 1971 "dhcp4_parser.yy"
                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3249 "dhcp4_parser.cc"
    break;

  case 587:
#line 1983 "dhcp4_parser.yy"
                               {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 3260 "dhcp4_parser.cc"
    break;

  case 588:
#line 1988 "dhcp4_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3269 "dhcp4_parser.cc"
    break;

  case 591:
#line 1997 "dhcp4_parser.yy"
                                   {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3279 "dhcp4_parser.cc"
    break;

  case 592:
#line 2001 "dhcp4_parser.yy"
                                     {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3289 "dhcp4_parser.cc"
    break;

  case 609:
#line 2030 "dhcp4_parser.yy"
                        {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3297 "dhcp4_parser.cc"
    break;

  case 610:
#line 2032 "dhcp4_parser.yy"
               {
    ElementPtr test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 3307 "dhcp4_parser.cc"
    break;

  case 611:
#line 2038 "dhcp4_parser.yy"
                                                 {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 3316 "dhcp4_parser.cc"
    break;

  case 612:
#line 2045 "dhcp4_parser.yy"
                                         {
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 3325 "dhcp4_parser.cc"
    break;

  case 613:
#line 2052 "dhcp4_parser.yy"
                               {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 3336 "dhcp4_parser.cc"
    break;

  case 614:
#line 2057 "dhcp4_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3345 "dhcp4_parser.cc"
    break;

  case 622:
#line 2073 "dhcp4_parser.yy"
                                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3353 "dhcp4_parser.cc"
    break;

  case 623:
#line 2075 "dhcp4_parser.yy"
               {
    ElementPtr stype(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 3363 "dhcp4_parser.cc"
    break;

  case 624:
#line 2081 "dhcp4_parser.yy"
                                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3371 "dhcp4_parser.cc"
    break;

  case 625:
#line 2083 "dhcp4_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 3381 "dhcp4_parser.cc"
    break;

  case 626:
#line 2092 "dhcp4_parser.yy"
                                       {
    ElementPtr qc(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-queue-control", qc);
    ctx.stack_.push_back(qc);
    ctx.enter(ctx.DHCP_QUEUE_CONTROL);
}
#line 3392 "dhcp4_parser.cc"
    break;

  case 627:
#line 2097 "dhcp4_parser.yy"
                                                           {
    // The enable queue parameter is required.
    ctx.require("enable-queue", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3403 "dhcp4_parser.cc"
    break;

  case 636:
#line 2116 "dhcp4_parser.yy"
                                         {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-queue", b);
}
#line 3412 "dhcp4_parser.cc"
    break;

  case 637:
#line 2121 "dhcp4_parser.yy"
                       {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3420 "dhcp4_parser.cc"
    break;

  case 638:
#line 2123 "dhcp4_parser.yy"
               {
    ElementPtr qt(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("queue-type", qt);
    ctx.leave();
}
#line 3430 "dhcp4_parser.cc"
    break;

  case 639:
#line 2129 "dhcp4_parser.yy"
                                 {
    ElementPtr c(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("capacity", c);
}
#line 3439 "dhcp4_parser.cc"
    break;

  case 640:
#line 2134 "dhcp4_parser.yy"
                            {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3447 "dhcp4_parser.cc"
    break;

  case 641:
#line 2136 "dhcp4_parser.yy"
              {
    ctx.stack_.back()->set(yystack_[3].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3456 "dhcp4_parser.cc"
    break;

  case 642:
#line 2143 "dhcp4_parser.yy"
                     {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 3467 "dhcp4_parser.cc"
    break;

  case 643:
#line 2148 "dhcp4_parser.yy"
                                                       {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3478 "dhcp4_parser.cc"
    break;

  case 644:
#line 2155 "dhcp4_parser.yy"
                              {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3488 "dhcp4_parser.cc"
    break;

  case 645:
#line 2159 "dhcp4_parser.yy"
                                  {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3498 "dhcp4_parser.cc"
    break;

  case 666:
#line 2189 "dhcp4_parser.yy"
                                             {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 3507 "dhcp4_parser.cc"
    break;

  case 667:
#line 2194 "dhcp4_parser.yy"
                     {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3515 "dhcp4_parser.cc"
    break;

  case 668:
#line 2196 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 3525 "dhcp4_parser.cc"
    break;

  case 669:
#line 2202 "dhcp4_parser.yy"
                                       {
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 3534 "dhcp4_parser.cc"
    break;

  case 670:
#line 2207 "dhcp4_parser.yy"
                     {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3542 "dhcp4_parser.cc"
    break;

  case 671:
#line 2209 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 3552 "dhcp4_parser.cc"
    break;

  case 672:
#line 2215 "dhcp4_parser.yy"
                                       {
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 3561 "dhcp4_parser.cc"
    break;

  case 673:
#line 2220 "dhcp4_parser.yy"
                                             {
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 3570 "dhcp4_parser.cc"
    break;

  case 674:
#line 2225 "dhcp4_parser.yy"
                           {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 3578 "dhcp4_parser.cc"
    break;

  case 675:
#line 2227 "dhcp4_parser.yy"
                           {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3587 "dhcp4_parser.cc"
    break;

  case 676:
#line 2233 "dhcp4_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 3593 "dhcp4_parser.cc"
    break;

  case 677:
#line 2234 "dhcp4_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 3599 "dhcp4_parser.cc"
    break;

  case 678:
#line 2237 "dhcp4_parser.yy"
                       {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 3607 "dhcp4_parser.cc"
    break;

  case 679:
#line 2239 "dhcp4_parser.yy"
             {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 3617 "dhcp4_parser.cc"
    break;

  case 680:
#line 2246 "dhcp4_parser.yy"
                                         {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3625 "dhcp4_parser.cc"
    break;

  case 681:
#line 2248 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 3635 "dhcp4_parser.cc"
    break;

  case 682:
#line 2255 "dhcp4_parser.yy"
                                                         {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 3644 "dhcp4_parser.cc"
    break;

  case 683:
#line 2261 "dhcp4_parser.yy"
                                                                 {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 3653 "dhcp4_parser.cc"
    break;

  case 684:
#line 2267 "dhcp4_parser.yy"
                                             {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 3661 "dhcp4_parser.cc"
    break;

  case 685:
#line 2269 "dhcp4_parser.yy"
                                       {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3670 "dhcp4_parser.cc"
    break;

  case 686:
#line 2275 "dhcp4_parser.yy"
                                       {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3678 "dhcp4_parser.cc"
    break;

  case 687:
#line 2277 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 3688 "dhcp4_parser.cc"
    break;

  case 688:
#line 2284 "dhcp4_parser.yy"
                                         {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3696 "dhcp4_parser.cc"
    break;

  case 689:
#line 2286 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 3706 "dhcp4_parser.cc"
    break;

  case 690:
#line 2293 "dhcp4_parser.yy"
                                                         {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3714 "dhcp4_parser.cc"
    break;

  case 691:
#line 2295 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 3724 "dhcp4_parser.cc"
    break;

  case 692:
#line 2304 "dhcp4_parser.yy"
                         {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3732 "dhcp4_parser.cc"
    break;

  case 693:
#line 2306 "dhcp4_parser.yy"
              {
    ctx.stack_.back()->set("Dhcp6", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3741 "dhcp4_parser.cc"
    break;

  case 694:
#line 2311 "dhcp4_parser.yy"
                               {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3749 "dhcp4_parser.cc"
    break;

  case 695:
#line 2313 "dhcp4_parser.yy"
              {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3758 "dhcp4_parser.cc"
    break;

  case 696:
#line 2318 "dhcp4_parser.yy"
                                         {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3766 "dhcp4_parser.cc"
    break;

  case 697:
#line 2320 "dhcp4_parser.yy"
              {
    ctx.stack_.back()->set("Control-agent", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3775 "dhcp4_parser.cc"
    break;

  case 698:
#line 2327 "dhcp4_parser.yy"
                               {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 3786 "dhcp4_parser.cc"
    break;

  case 699:
#line 2332 "dhcp4_parser.yy"
                                                            {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3796 "dhcp4_parser.cc"
    break;

  case 700:
#line 2338 "dhcp4_parser.yy"
                                   {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3806 "dhcp4_parser.cc"
    break;

  case 701:
#line 2342 "dhcp4_parser.yy"
                                       {
    // No config_control params are required
    // parsing completed
}
#line 3815 "dhcp4_parser.cc"
    break;

  case 706:
#line 2357 "dhcp4_parser.yy"
                                   {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 3826 "dhcp4_parser.cc"
    break;

  case 707:
#line 2362 "dhcp4_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3835 "dhcp4_parser.cc"
    break;

  case 708:
#line 2367 "dhcp4_parser.yy"
                                                             {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-fetch-wait-time", value);
}
#line 3844 "dhcp4_parser.cc"
    break;

  case 709:
#line 2377 "dhcp4_parser.yy"
                        {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 3855 "dhcp4_parser.cc"
    break;

  case 710:
#line 2382 "dhcp4_parser.yy"
                                                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3864 "dhcp4_parser.cc"
    break;

  case 711:
#line 2387 "dhcp4_parser.yy"
                            {
    // Parse the Logging map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3874 "dhcp4_parser.cc"
    break;

  case 712:
#line 2391 "dhcp4_parser.yy"
                                {
    // parsing completed
}
#line 3882 "dhcp4_parser.cc"
    break;

  case 716:
#line 2407 "dhcp4_parser.yy"
                 {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 3893 "dhcp4_parser.cc"
    break;

  case 717:
#line 2412 "dhcp4_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3902 "dhcp4_parser.cc"
    break;

  case 720:
#line 2424 "dhcp4_parser.yy"
                             {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 3912 "dhcp4_parser.cc"
    break;

  case 721:
#line 2428 "dhcp4_parser.yy"
                               {
    ctx.stack_.pop_back();
}
#line 3920 "dhcp4_parser.cc"
    break;

  case 731:
#line 2445 "dhcp4_parser.yy"
                                     {
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 3929 "dhcp4_parser.cc"
    break;

  case 732:
#line 2450 "dhcp4_parser.yy"
                   {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3937 "dhcp4_parser.cc"
    break;

  case 733:
#line 2452 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 3947 "dhcp4_parser.cc"
    break;

  case 734:
#line 2458 "dhcp4_parser.yy"
                                    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 3958 "dhcp4_parser.cc"
    break;

  case 735:
#line 2463 "dhcp4_parser.yy"
                                                                    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3967 "dhcp4_parser.cc"
    break;

  case 738:
#line 2472 "dhcp4_parser.yy"
                             {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3977 "dhcp4_parser.cc"
    break;

  case 739:
#line 2476 "dhcp4_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 3985 "dhcp4_parser.cc"
    break;

  case 747:
#line 2491 "dhcp4_parser.yy"
               {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3993 "dhcp4_parser.cc"
    break;

  case 748:
#line 2493 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 4003 "dhcp4_parser.cc"
    break;

  case 749:
#line 2499 "dhcp4_parser.yy"
                           {
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 4012 "dhcp4_parser.cc"
    break;

  case 750:
#line 2504 "dhcp4_parser.yy"
                               {
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 4021 "dhcp4_parser.cc"
    break;

  case 751:
#line 2509 "dhcp4_parser.yy"
                             {
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 4030 "dhcp4_parser.cc"
    break;

  case 752:
#line 2514 "dhcp4_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 4038 "dhcp4_parser.cc"
    break;

  case 753:
#line 2516 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pattern", sev);
    ctx.leave();
}
#line 4048 "dhcp4_parser.cc"
    break;


#line 4052 "dhcp4_parser.cc"

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


  const short Dhcp4Parser::yypact_ninf_ = -939;

  const signed char Dhcp4Parser::yytable_ninf_ = -1;

  const short
  Dhcp4Parser::yypact_[] =
  {
     370,  -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,
    -939,  -939,  -939,  -939,  -939,    32,    43,    33,    50,    67,
      69,    71,    83,    90,   112,   121,   127,   129,   157,   171,
    -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,
    -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,
    -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,
    -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,    43,  -162,
      24,   200,   107,   637,    -8,    54,   -33,    91,    58,   -67,
     223,  -112,   134,  -939,   178,    62,   191,   189,   209,  -939,
    -939,  -939,  -939,  -939,   216,  -939,    35,  -939,  -939,  -939,
    -939,  -939,  -939,  -939,  -939,  -939,   218,   220,   240,  -939,
    -939,  -939,  -939,  -939,  -939,   242,   250,   252,   273,   275,
     283,   285,   309,   332,  -939,   336,   339,   360,   378,   385,
    -939,  -939,  -939,   392,  -939,  -939,  -939,  -939,  -939,  -939,
    -939,  -939,  -939,  -939,  -939,  -939,   399,  -939,  -939,  -939,
    -939,  -939,  -939,  -939,  -939,    48,  -939,  -939,  -939,  -939,
    -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,
    -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,
    -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,
    -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,
    -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,
    -939,   401,  -939,    59,  -939,  -939,  -939,  -939,  -939,  -939,
    -939,  -939,  -939,  -939,  -939,  -939,  -939,   409,  -939,  -939,
    -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,
    -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,
    -939,    72,  -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,
    -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,
    -939,  -939,  -939,  -939,  -939,  -939,    85,  -939,  -939,  -939,
    -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,
    -939,  -939,  -939,   412,   418,  -939,  -939,  -939,  -939,  -939,
    -939,  -939,  -939,  -939,  -939,  -939,  -939,   414,  -939,  -939,
     419,  -939,  -939,  -939,   421,  -939,  -939,   422,   424,  -939,
    -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,
    -939,  -939,   425,   428,  -939,  -939,  -939,  -939,   426,   430,
    -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,
    -939,  -939,   113,  -939,  -939,  -939,   431,  -939,  -939,   433,
    -939,   439,   442,  -939,  -939,   444,   445,  -939,  -939,  -939,
    -939,  -939,  -939,  -939,   174,  -939,  -939,  -939,  -939,  -939,
    -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,
    -939,   244,  -939,  -939,  -939,   446,   245,  -939,  -939,  -939,
    -939,    43,    43,  -939,   262,   455,   456,   458,   459,   460,
    -939,    24,  -939,   461,   463,   465,   276,   279,   281,   472,
     477,   479,   480,   481,   483,   296,   297,   299,   302,   307,
     301,   310,   314,   318,   498,   320,   321,   312,   324,   327,
     510,   511,   516,   331,   524,   525,   526,   528,   529,   530,
     531,   532,   533,   534,   535,   537,   350,   539,   557,   558,
     559,   560,   561,   562,   200,  -939,   563,   564,   565,   377,
     107,  -939,   566,   568,   569,   570,   571,   572,   386,   573,
     575,   576,   637,  -939,   577,    -8,  -939,   578,   579,   580,
     581,   582,   583,   584,   585,  -939,    54,  -939,   586,   587,
     400,   590,   591,   592,   403,  -939,    91,   594,   406,   407,
    -939,    58,   598,   599,   204,  -939,   410,   602,   603,   416,
     605,   420,   427,   606,   607,   423,   429,   609,   610,   612,
     614,   223,  -939,  -112,  -939,   616,   432,   134,  -939,  -939,
    -939,   617,   615,   618,    43,    43,    43,  -939,   619,   620,
     621,  -939,  -939,  -939,   438,   440,   441,   623,   628,   632,
    -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,   447,
    -939,  -939,  -939,  -939,  -939,     2,   448,   450,  -939,   638,
     639,   640,   641,   635,   457,     3,   642,   648,   649,   651,
     650,  -939,   652,   653,   654,   661,   467,   478,   665,  -939,
     666,   363,   398,  -939,  -939,   482,   484,   485,   667,   486,
     487,  -939,   666,   488,   673,  -939,   490,  -939,   666,   491,
     492,   493,   494,   495,   496,   497,  -939,   502,   512,  -939,
     513,   514,   522,  -939,  -939,   536,  -939,  -939,  -939,   546,
      43,  -939,  -939,   547,   548,  -939,   549,  -939,  -939,    31,
     517,  -939,  -939,     2,   550,   551,   553,  -939,  -939,   697,
    -939,  -939,    43,   200,  -112,  -939,  -939,  -939,   134,   107,
     693,  -939,  -939,  -939,   305,   305,   712,  -939,  -939,  -939,
    -939,  -939,  -939,  -939,  -939,  -939,   713,   714,   715,   716,
    -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,   172,   717,
     718,   719,   114,    60,    14,    17,   223,  -939,  -939,   721,
    -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,
    -939,   723,  -939,  -939,  -939,  -939,   292,  -939,  -939,  -939,
    -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,
    -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,
    -939,  -939,  -939,  -939,  -939,   712,  -939,   247,   293,   294,
     300,  -939,   303,  -939,  -939,  -939,  -939,  -939,  -939,   741,
     744,   745,   746,   747,  -939,  -939,  -939,  -939,   748,   749,
     751,   752,   753,   754,  -939,   304,  -939,  -939,  -939,  -939,
    -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,
    -939,  -939,  -939,  -939,  -939,  -939,  -939,   306,  -939,   755,
     756,  -939,  -939,   757,   759,  -939,  -939,   758,   762,  -939,
    -939,   760,   764,  -939,  -939,   763,   765,  -939,  -939,  -939,
    -939,  -939,  -939,    38,  -939,  -939,  -939,  -939,  -939,  -939,
    -939,    88,  -939,  -939,   766,   767,  -939,  -939,   768,   770,
    -939,   771,   772,   773,   774,   775,   776,   313,  -939,  -939,
    -939,  -939,  -939,  -939,  -939,   777,   778,   779,  -939,   316,
    -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,
    -939,   319,  -939,  -939,  -939,   780,  -939,   781,  -939,  -939,
    -939,   325,  -939,  -939,  -939,  -939,  -939,   326,  -939,   168,
    -939,   595,  -939,   782,   784,  -939,  -939,  -939,  -939,   783,
     786,  -939,  -939,  -939,  -939,   785,   693,  -939,   789,   790,
     791,   792,   611,   596,   613,   604,   622,   793,   797,   798,
     800,   624,   625,   626,   627,   629,   630,   305,  -939,  -939,
     305,  -939,   712,   637,  -939,   713,    91,  -939,   714,    58,
    -939,   715,  1166,  -939,   716,   172,  -939,   109,   717,  -939,
      54,  -939,   718,   -67,  -939,   719,   633,   634,   643,   644,
     645,   646,   114,  -939,   636,   647,   655,    60,  -939,   802,
     803,    14,  -939,   656,   804,   657,   805,    17,  -939,  -939,
     124,   721,  -939,  -939,   806,   807,    -8,  -939,   723,   809,
    -939,  -939,   660,  -939,   371,   662,   663,   664,  -939,  -939,
    -939,  -939,  -939,   668,   669,   670,   671,  -939,  -939,  -939,
    -939,  -939,  -939,  -939,   329,  -939,   376,  -939,   812,  -939,
     813,  -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,
    -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,
    -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,   380,  -939,
    -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,
     811,  -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,
     816,   808,  -939,  -939,  -939,  -939,  -939,   819,  -939,   387,
    -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,
    -939,  -939,   672,   674,  -939,  -939,   675,  -939,    43,  -939,
    -939,   825,  -939,  -939,  -939,  -939,  -939,   389,  -939,  -939,
    -939,  -939,  -939,  -939,   676,   390,  -939,   666,  -939,  -939,
    -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,
    -939,  -939,  -939,  -939,  -939,  1166,  -939,   827,   658,  -939,
     109,  -939,  -939,  -939,  -939,  -939,  -939,   828,   677,   829,
     124,  -939,  -939,  -939,  -939,  -939,   679,  -939,  -939,   835,
    -939,   680,  -939,  -939,   834,  -939,  -939,   207,  -939,   -40,
     834,  -939,  -939,   830,   838,   839,  -939,   396,  -939,  -939,
    -939,  -939,  -939,  -939,  -939,   840,   678,   682,   683,   841,
     -40,  -939,   686,  -939,  -939,  -939,   687,  -939,  -939,  -939
  };

  const short
  Dhcp4Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,    28,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       1,    45,    38,    34,    33,    30,    31,    32,    37,     3,
      35,    36,    58,     5,    70,     7,   172,     9,   330,    11,
     513,    13,   538,    15,   438,    17,   446,    19,   483,    21,
     295,    23,   644,    25,   711,    27,   700,    29,    47,    41,
       0,     0,     0,     0,     0,   540,     0,   448,   485,     0,
       0,     0,     0,    49,     0,    48,     0,     0,    42,    68,
     709,   692,   694,   696,     0,    67,     0,    60,    62,    64,
      65,    66,    63,   698,   161,   187,     0,     0,     0,   559,
     561,   563,   185,   194,   196,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   135,     0,     0,     0,     0,     0,
     143,   150,   152,     0,   322,   436,   475,   393,   526,   528,
     386,   260,   587,   530,   287,   306,     0,   274,   613,   626,
     642,   154,   156,   716,   125,     0,    72,    74,    75,    76,
      77,    78,   109,   110,   111,    79,   107,    96,    97,    98,
     115,   116,   117,   118,   119,   120,   113,   114,   121,   122,
     123,    82,    83,   104,    84,    85,    86,   124,    90,    91,
      80,   108,    81,    88,    89,   102,   103,   105,    99,   100,
     101,    87,    92,    93,    94,    95,   106,   112,   174,   176,
     180,     0,   171,     0,   163,   165,   166,   167,   168,   169,
     170,   374,   376,   378,   505,   372,   380,     0,   384,   382,
     583,   371,   334,   335,   336,   337,   338,   359,   360,   361,
     349,   350,   362,   363,   364,   365,   366,   367,   368,   369,
     370,     0,   332,   341,   354,   355,   356,   342,   344,   345,
     347,   343,   339,   340,   357,   358,   346,   351,   352,   353,
     348,   524,   523,   519,   520,   518,     0,   515,   517,   521,
     522,   581,   569,   571,   575,   573,   579,   577,   565,   558,
     552,   556,   557,     0,   541,   542,   553,   554,   555,   549,
     544,   550,   546,   547,   548,   551,   545,     0,   465,   240,
       0,   469,   467,   472,     0,   461,   462,     0,   449,   450,
     452,   464,   453,   454,   455,   471,   456,   457,   458,   459,
     460,   499,     0,     0,   497,   498,   501,   502,     0,   486,
     487,   489,   490,   491,   492,   493,   494,   495,   496,   302,
     304,   299,     0,   297,   300,   301,     0,   680,   667,     0,
     670,     0,     0,   674,   678,     0,     0,   684,   686,   688,
     690,   665,   663,   664,     0,   646,   648,   649,   650,   651,
     652,   653,   654,   655,   660,   656,   657,   658,   659,   661,
     662,     0,   713,   715,   706,     0,     0,   702,   704,   705,
      46,     0,     0,    39,     0,     0,     0,     0,     0,     0,
      57,     0,    59,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    71,     0,     0,     0,     0,
       0,   173,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   331,     0,     0,   514,     0,     0,     0,
       0,     0,     0,     0,     0,   539,     0,   439,     0,     0,
       0,     0,     0,     0,     0,   447,     0,     0,     0,     0,
     484,     0,     0,     0,     0,   296,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   645,     0,   712,     0,     0,     0,   701,    50,
      43,     0,     0,     0,     0,     0,     0,    61,     0,     0,
       0,   137,   138,   139,     0,     0,     0,     0,     0,     0,
     126,   127,   128,   129,   130,   131,   132,   133,   134,     0,
     159,   160,   140,   141,   142,     0,     0,     0,   158,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   612,     0,     0,     0,     0,     0,     0,     0,    73,
       0,     0,     0,   184,   164,     0,     0,     0,     0,     0,
       0,   392,     0,     0,     0,   333,     0,   516,     0,     0,
       0,     0,     0,     0,     0,     0,   543,     0,     0,   463,
       0,     0,     0,   474,   451,     0,   503,   504,   488,     0,
       0,   298,   666,     0,     0,   669,     0,   672,   673,     0,
       0,   682,   683,     0,     0,     0,     0,   647,   714,     0,
     708,   703,     0,     0,     0,   693,   695,   697,     0,     0,
       0,   560,   562,   564,     0,     0,   198,   136,   145,   146,
     147,   148,   149,   144,   151,   153,   324,   440,   477,   395,
      40,   527,   529,   388,   389,   390,   391,   387,     0,     0,
     532,   289,     0,     0,     0,     0,     0,   155,   157,     0,
      51,   175,   178,   179,   177,   182,   183,   181,   375,   377,
     379,   507,   373,   381,   385,   383,     0,   525,   582,   570,
     572,   576,   574,   580,   578,   566,   466,   241,   470,   468,
     473,   500,   303,   305,   681,   668,   671,   676,   677,   675,
     679,   685,   687,   689,   691,   198,    44,     0,     0,     0,
       0,   192,     0,   189,   191,   227,   233,   235,   237,     0,
       0,     0,     0,     0,   249,   251,   253,   255,     0,     0,
       0,     0,     0,     0,   226,     0,   204,   206,   207,   208,
     209,   210,   211,   212,   213,   214,   215,   219,   220,   221,
     216,   222,   223,   224,   217,   218,   225,     0,   202,     0,
     199,   200,   328,     0,   325,   326,   444,     0,   441,   442,
     481,     0,   478,   479,   399,     0,   396,   397,   269,   270,
     271,   272,   273,     0,   262,   264,   265,   266,   267,   268,
     591,     0,   589,   536,     0,   533,   534,   293,     0,   290,
     291,     0,     0,     0,     0,     0,     0,     0,   308,   310,
     311,   312,   313,   314,   315,     0,     0,     0,   283,     0,
     276,   278,   279,   280,   281,   282,   622,   624,   621,   619,
     620,     0,   615,   617,   618,     0,   637,     0,   640,   633,
     634,     0,   628,   630,   631,   632,   635,     0,   720,     0,
     718,    53,   511,     0,   508,   509,   567,   585,   586,     0,
       0,    69,   710,   699,   162,     0,     0,   188,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   186,   195,
       0,   197,     0,     0,   323,     0,   448,   437,     0,   485,
     476,     0,     0,   394,     0,     0,   261,   593,     0,   588,
     540,   531,     0,     0,   288,     0,     0,     0,     0,     0,
       0,     0,     0,   307,     0,     0,     0,     0,   275,     0,
       0,     0,   614,     0,     0,     0,     0,     0,   627,   643,
       0,     0,   717,    55,     0,    54,     0,   506,     0,     0,
     584,   707,     0,   190,     0,     0,     0,     0,   239,   242,
     243,   244,   245,     0,     0,     0,     0,   257,   258,   246,
     247,   248,   259,   205,     0,   201,     0,   327,     0,   443,
       0,   480,   435,   418,   419,   420,   406,   407,   423,   424,
     425,   409,   410,   426,   427,   428,   429,   430,   431,   432,
     433,   434,   403,   404,   405,   416,   417,   415,     0,   401,
     408,   421,   422,   411,   412,   413,   414,   398,   263,   609,
       0,   607,   608,   600,   601,   605,   606,   602,   603,   604,
       0,   594,   595,   597,   598,   599,   590,     0,   535,     0,
     292,   316,   317,   318,   319,   320,   321,   309,   284,   285,
     286,   277,     0,     0,   616,   636,     0,   639,     0,   629,
     734,     0,   732,   730,   724,   728,   729,     0,   722,   726,
     727,   725,   719,    52,     0,     0,   510,     0,   193,   229,
     230,   231,   232,   228,   234,   236,   238,   250,   252,   254,
     256,   203,   329,   445,   482,     0,   400,     0,     0,   592,
       0,   537,   294,   623,   625,   638,   641,     0,     0,     0,
       0,   721,    56,   512,   568,   402,     0,   611,   596,     0,
     731,     0,   723,   610,     0,   733,   738,     0,   736,     0,
       0,   735,   747,     0,     0,     0,   752,     0,   740,   742,
     743,   744,   745,   746,   737,     0,     0,     0,     0,     0,
       0,   739,     0,   749,   750,   751,     0,   741,   748,   753
  };

  const short
  Dhcp4Parser::yypgoto_[] =
  {
    -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,
    -939,  -939,  -939,  -939,  -939,  -939,     0,  -939,   177,  -939,
    -939,  -939,  -939,  -939,  -939,  -939,  -939,  -587,  -939,  -939,
    -939,   -70,  -939,  -939,  -939,   435,  -939,  -939,  -939,  -939,
     108,   384,   -43,   -31,   -27,    -4,    -2,     8,    16,    19,
    -939,  -939,  -939,  -939,    22,    23,    26,    27,    29,    34,
    -939,   203,    37,  -939,    40,  -939,    41,  -939,    42,  -939,
      44,  -939,  -939,  -939,  -939,   188,   388,  -939,  -939,  -939,
    -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,
    -939,  -939,  -939,   -52,  -939,  -939,  -939,  -939,  -939,  -939,
     126,  -939,   -74,  -939,  -662,   -41,  -939,  -939,  -939,  -939,
    -939,  -939,  -939,  -939,  -939,  -939,   -66,  -939,  -939,  -939,
    -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,
    -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,   -42,
    -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,   -89,  -939,
    -939,  -939,  -939,  -939,  -939,  -939,   -64,  -939,  -939,  -939,
     -46,   383,  -939,  -939,  -939,  -939,  -939,  -939,  -939,   -35,
    -939,  -939,  -939,  -939,  -939,  -939,  -938,  -939,  -939,  -939,
     -15,  -939,  -939,  -939,   -25,   449,  -939,  -939,  -939,  -939,
    -939,  -939,  -939,  -939,  -936,  -939,   -68,  -939,    46,  -939,
      45,  -939,  -939,  -939,  -939,  -939,  -939,  -939,   -20,  -939,
    -939,  -201,   -49,  -939,  -939,  -939,  -939,  -939,     5,  -939,
    -939,  -939,    -1,  -939,   489,  -939,   -45,  -939,  -939,  -939,
    -939,  -939,   -39,  -939,  -939,  -939,  -939,  -939,   -38,  -939,
    -939,  -939,     1,  -939,  -939,  -939,     6,  -939,   499,  -939,
    -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,
      -7,  -939,  -939,  -939,    -6,   515,  -939,  -939,   -54,  -939,
     -14,  -939,   -28,  -939,  -939,  -939,    39,  -939,  -939,  -939,
      47,  -939,   503,   -58,  -939,    -3,  -939,     4,  -939,   277,
    -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,
    -939,  -939,  -939,  -939,  -939,  -939,  -939,  -924,  -939,  -939,
    -939,  -939,  -939,    51,  -939,  -939,  -939,  -148,  -939,  -939,
    -939,  -939,  -939,  -939,  -939,  -939,    25,  -939,  -939,  -939,
    -939,  -939,  -939,  -939,    18,  -939,  -939,  -939,  -939,  -939,
    -939,  -939,  -939,  -939,  -939,   298,   500,  -939,  -939,  -939,
    -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,
    -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,
    -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,  -939,
    -939,  -939,   340,   474,  -939,  -939,  -939,  -939,  -939,  -939,
    -939,   348,   501,   -59,  -939,  -939,    28,  -939,  -939,  -147,
    -939,  -939,  -939,  -939,  -939,  -939,  -166,  -939,  -939,  -185,
    -939,  -939,  -939,  -939,  -939,  -939,  -939
  };

  const short
  Dhcp4Parser::yydefgoto_[] =
  {
      -1,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    38,    39,    40,    69,
     691,    87,    88,    41,    68,    84,    85,   711,   901,   994,
     995,   784,    43,    70,    96,    97,    98,   405,    45,    71,
     155,   156,   157,   158,   159,   160,   161,   162,   163,   164,
     165,   166,   434,   167,   168,   169,   170,   171,   172,   173,
     440,   683,   174,   441,   175,   442,   176,   461,   177,   462,
     178,   179,   180,   181,   414,   213,   214,    47,    72,   215,
     466,   216,   467,   714,   217,   468,   717,   218,   182,   422,
     183,   415,   762,   763,   764,   915,   184,   423,   185,   424,
     809,   810,   811,   940,   785,   786,   787,   918,  1133,   788,
     919,   789,   920,   790,   921,   791,   792,   499,   793,   794,
     795,   796,   797,   798,   799,   800,   927,   801,   928,   802,
     929,   803,   930,   804,   805,   806,   186,   451,   833,   834,
     835,   836,   837,   838,   839,   187,   457,   869,   870,   871,
     872,   873,   188,   454,   848,   849,   850,   963,    61,    79,
     352,   353,   354,   512,   355,   513,   189,   455,   857,   858,
     859,   860,   861,   862,   863,   864,   190,   444,   813,   814,
     815,   943,    49,    73,   251,   252,   253,   476,   254,   472,
     255,   473,   256,   474,   257,   477,   258,   480,   259,   479,
     191,   450,   697,   261,   192,   447,   825,   826,   827,   952,
    1058,  1059,   193,   445,    55,    76,   817,   818,   819,   946,
      57,    77,   317,   318,   319,   320,   321,   322,   323,   498,
     324,   502,   325,   501,   326,   327,   503,   328,   194,   446,
     821,   822,   823,   949,    59,    78,   338,   339,   340,   341,
     342,   507,   343,   344,   345,   346,   263,   475,   903,   904,
     905,   996,    51,    74,   276,   277,   278,   484,   195,   448,
     196,   449,   197,   453,   844,   845,   846,   960,    53,    75,
     293,   294,   295,   198,   419,   199,   420,   200,   421,   299,
     494,   908,   999,   300,   488,   301,   489,   302,   491,   303,
     490,   304,   493,   305,   492,   306,   487,   270,   481,   909,
     201,   452,   841,   842,   957,  1080,  1081,  1082,  1083,  1084,
    1147,  1085,   202,   203,   458,   881,   882,   883,   979,   884,
     980,   204,   459,   891,   892,   893,   894,   984,   895,   896,
     986,   205,   460,    63,    80,   374,   375,   376,   377,   518,
     378,   379,   520,   380,   381,   382,   523,   749,   383,   524,
     384,   517,   385,   386,   387,   527,   388,   528,   389,   529,
     390,   530,    99,   407,   100,   408,   101,   409,   206,   413,
      67,    82,   396,   397,   398,   535,   399,   102,   406,    65,
      81,   391,   392,   207,   463,   899,   900,   990,  1117,  1118,
    1119,  1120,  1159,  1121,  1157,  1177,  1178,  1179,  1187,  1188,
    1189,  1195,  1190,  1191,  1192,  1193,  1199
  };

  const short
  Dhcp4Parser::yytable_[] =
  {
      95,   154,   212,   231,   272,   289,   273,   315,   334,   351,
     371,   316,   335,   807,  1053,   267,  1054,   296,   219,   264,
     279,   291,   393,   329,   347,   724,   372,   307,  1066,    86,
     232,   728,    30,   336,    89,   262,   275,   290,   411,   337,
      42,   955,   233,   412,   956,   266,   234,   135,    31,   747,
      32,   464,    33,   153,   349,   350,   465,    44,   220,   265,
     280,   292,   470,   330,   348,   401,   373,   471,    83,   235,
     268,   236,   297,   136,    46,   482,    48,   269,    50,   298,
     483,   237,   109,   110,   111,   271,   138,   139,   485,   238,
      52,   958,   239,   486,   959,   240,   241,    54,   228,   242,
     243,   229,   244,   693,   694,   695,   696,   245,   138,   139,
     246,   138,   139,   247,   248,   249,   514,   250,   260,    56,
     274,   515,   208,   209,    94,   308,   210,  1182,    58,   211,
    1183,  1184,  1185,  1186,    60,   136,    62,   109,   110,   111,
     309,   331,   310,   311,   332,   333,   394,   395,   138,   139,
     876,   877,   138,   139,   138,   139,   885,   886,   887,   281,
     678,   679,   680,   681,    64,   282,   283,   284,   285,   286,
     287,   991,   288,   309,   992,   310,   311,   531,    66,   312,
     313,   314,   532,    94,   400,   138,   139,   748,    90,   135,
     136,   309,   865,   866,   867,   402,   682,   403,    91,    92,
      93,   138,   139,   138,   139,    94,   309,  1053,   888,  1054,
    1180,   103,   404,  1181,   104,    94,  1069,  1070,   138,   139,
     410,  1066,   416,   105,   417,   106,   107,   108,   109,   110,
     111,   112,   113,   114,    34,    35,    36,    37,   851,   852,
     853,   854,   855,   856,   418,    94,   425,   533,   537,    94,
     464,    94,   534,   538,   426,   911,   427,   115,   116,   117,
     118,   119,   120,   121,   122,   123,   124,   125,   126,   127,
     128,   129,   130,   131,   132,   133,   134,   428,  1024,   429,
     135,   136,    94,   828,   829,   830,   831,   430,   832,   431,
    1110,   137,  1111,  1112,   138,   139,   533,   537,    94,   140,
      94,   912,   913,   470,   141,   142,   916,   937,   914,   937,
     143,   917,   938,   432,   939,    94,   972,   138,   139,   977,
     144,   973,   981,   145,   978,   349,   350,   982,   987,   531,
     146,   147,   937,   988,   989,   148,   433,  1141,   149,   765,
     435,    95,   150,   436,   766,   767,   768,   769,   770,   771,
     772,   773,   774,   775,   776,   777,   778,   779,   780,   781,
     782,   783,   151,   152,   437,   153,   356,   357,   358,   359,
     360,   361,   362,   363,   364,   365,   366,   367,   368,   482,
     712,   713,   438,  1145,  1142,   369,   370,   309,  1146,   439,
     514,    94,  1160,   485,   154,  1152,   443,  1161,  1163,  1200,
     212,   539,   540,   456,  1201,   469,  1129,  1130,  1131,  1132,
     288,   906,   231,   478,    94,   272,   219,   273,   715,   716,
     495,   496,   497,   500,   267,   504,   289,   506,   264,   508,
     505,   279,   509,   511,   510,   516,   315,   519,   296,   232,
     316,   334,   291,   521,   262,   335,   522,   275,   525,   526,
     536,   233,   329,   541,   266,   234,   220,   347,   290,   542,
     543,   371,   544,   545,   546,   548,   336,   549,   265,   550,
     551,   280,   337,   552,   393,   553,   554,   372,   235,   268,
     236,   555,   292,   556,   557,   558,   269,   559,   560,   561,
     237,   562,   330,   297,   563,   565,    94,   348,   238,   564,
     298,   239,   569,   566,   240,   241,   572,   567,   242,   243,
     568,   244,   570,   571,   575,   576,   245,   373,   573,   246,
     577,   574,   247,   248,   249,   578,   250,   260,   579,   580,
     581,   274,   582,   583,   584,   585,   586,   587,   588,   589,
    1164,   590,   591,   592,   665,   666,   667,     1,     2,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,   593,   594,   595,   596,   597,   598,   600,   601,   602,
     605,   603,   606,   607,   608,   609,   610,   612,   611,   613,
     614,   616,   618,   619,   620,   621,   622,   623,   624,   625,
     627,   628,   629,   154,   630,   631,   632,   633,   635,   212,
     636,   637,   639,   640,   642,   393,   643,   644,   645,   646,
     649,   650,   647,   653,   654,   219,   655,   651,   656,   648,
     659,   662,   663,   652,   660,   664,   668,   669,   670,   671,
     674,   672,   673,   868,   878,   675,   371,   676,   677,   684,
     743,   685,    32,   686,   687,   688,   689,   698,   692,   874,
     879,   889,   372,   699,   700,   220,   701,   702,   707,   703,
     704,   705,   756,   107,   108,   109,   110,   111,   706,   708,
     709,   710,   721,   718,   750,   719,   720,   722,   723,   725,
     726,   727,   729,   730,   731,   732,   733,   734,   735,   875,
     880,   890,   373,   736,   115,   116,   117,   118,   119,   120,
     121,   122,   755,   737,   738,   739,   127,   128,   129,   130,
     131,   132,   133,   740,   221,   222,   223,   761,   136,   808,
     812,   816,   820,   824,   840,   843,   847,   741,   898,   224,
     902,   138,   139,   225,   226,   227,   140,   742,   744,   745,
     746,   752,   753,   228,   754,   922,   229,   143,   923,   924,
     925,   926,   931,   932,   230,   933,   934,   935,   936,   942,
     690,   941,   945,   944,   947,   948,   950,   951,   954,   953,
     962,   757,   961,   965,   964,   966,   967,   968,   969,   970,
     971,   974,   975,   976,   983,   985,   993,   998,   997,  1002,
    1009,  1000,  1001,  1004,  1005,  1006,  1007,  1013,  1011,   151,
     152,  1014,  1015,  1008,  1016,  1010,  1102,  1103,  1106,  1108,
    1124,  1150,  1123,  1127,  1012,  1148,  1017,  1018,  1019,  1020,
    1143,  1144,  1022,  1021,  1149,  1091,  1092,  1151,    94,  1158,
    1098,  1166,  1169,  1171,  1196,  1093,  1094,  1095,  1096,  1099,
    1174,  1176,  1197,  1198,  1202,  1206,   547,  1100,   599,  1107,
    1105,  1128,  1167,  1134,  1135,  1136,   751,   760,   604,  1137,
    1138,  1139,  1140,  1153,  1003,  1154,  1155,  1162,  1025,  1170,
    1173,  1175,  1203,   231,  1204,  1205,   315,  1208,  1209,   334,
     316,   910,  1032,   335,  1055,   267,  1052,  1071,  1101,   264,
     289,  1072,   329,   351,  1063,   347,  1023,   641,  1061,  1077,
     232,  1090,   296,  1075,   336,   262,   291,   868,  1073,  1033,
     337,   878,   233,  1068,  1060,   266,   234,  1089,  1026,  1074,
    1113,  1034,   290,   874,  1114,  1035,   272,   879,   273,   265,
    1027,   615,   330,   889,  1067,   348,  1115,  1097,  1062,   235,
     268,   236,   279,  1076,  1165,  1028,   292,   269,  1036,  1064,
    1037,   237,  1031,  1029,  1078,  1030,  1065,   297,   275,   238,
    1038,  1079,   239,   875,   298,   240,   241,   880,  1039,   242,
     243,  1040,   244,   890,  1041,  1042,  1116,   245,  1043,  1044,
     246,  1045,   280,   247,   248,   249,  1046,   250,   260,  1047,
    1125,  1126,  1048,  1049,  1050,   634,  1051,  1057,  1056,   626,
     617,  1088,  1168,   907,   897,  1109,  1104,  1087,   759,  1086,
     638,   661,   758,  1172,  1194,  1207,     0,     0,     0,  1122,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   657,     0,     0,   658,     0,     0,     0,     0,     0,
       0,     0,   274,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,  1032,     0,  1055,     0,  1052,
    1071,     0,     0,     0,  1072,     0,     0,  1063,     0,     0,
    1113,  1061,  1077,     0,  1114,     0,  1075,     0,     0,     0,
       0,  1073,  1033,     0,     0,     0,  1115,  1060,  1156,     0,
       0,     0,  1074,     0,  1034,     0,     0,     0,  1035,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,  1062,     0,     0,     0,     0,  1076,     0,     0,     0,
       0,  1036,  1064,  1037,     0,     0,  1116,  1078,     0,  1065,
       0,     0,     0,  1038,  1079,     0,     0,     0,     0,     0,
       0,  1039,     0,     0,  1040,     0,     0,  1041,  1042,     0,
       0,  1043,  1044,     0,  1045,     0,     0,     0,     0,  1046,
       0,     0,  1047,     0,     0,  1048,  1049,  1050,     0,  1051,
    1057,  1056,   107,   108,   109,   110,   111,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   115,   116,   117,   118,   119,   120,   121,
     122,     0,     0,     0,     0,   127,   128,   129,   130,   131,
     132,   133,   134,     0,     0,     0,     0,   136,   309,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     138,   139,     0,   226,     0,   140,     0,     0,     0,     0,
       0,     0,   228,     0,     0,   229,     0,     0,     0,     0,
       0,     0,     0,   230,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   151,   152,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    94
  };

  const short
  Dhcp4Parser::yycheck_[] =
  {
      70,    71,    72,    73,    74,    75,    74,    77,    78,    79,
      80,    77,    78,   675,   952,    73,   952,    75,    72,    73,
      74,    75,    81,    77,    78,   612,    80,    76,   952,   191,
      73,   618,     0,    78,    10,    73,    74,    75,     3,    78,
       7,     3,    73,     8,     6,    73,    73,    80,     5,    18,
       7,     3,     9,   165,   121,   122,     8,     7,    72,    73,
      74,    75,     3,    77,    78,     3,    80,     8,    68,    73,
      73,    73,    75,    81,     7,     3,     7,    73,     7,    75,
       8,    73,    28,    29,    30,    93,    94,    95,     3,    73,
       7,     3,    73,     8,     6,    73,    73,     7,   106,    73,
      73,   109,    73,   100,   101,   102,   103,    73,    94,    95,
      73,    94,    95,    73,    73,    73,     3,    73,    73,     7,
      74,     8,    15,    16,   191,    34,    19,   167,     7,    22,
     170,   171,   172,   173,     7,    81,     7,    28,    29,    30,
      82,    83,    84,    85,    86,    87,    12,    13,    94,    95,
     136,   137,    94,    95,    94,    95,   139,   140,   141,   105,
     158,   159,   160,   161,     7,   111,   112,   113,   114,   115,
     116,     3,   118,    82,     6,    84,    85,     3,     7,    88,
      89,    90,     8,   191,     6,    94,    95,   156,   164,    80,
      81,    82,   132,   133,   134,     4,   194,     8,   174,   175,
     176,    94,    95,    94,    95,   191,    82,  1145,   191,  1145,
       3,    11,     3,     6,    14,   191,   107,   108,    94,    95,
       4,  1145,     4,    23,     4,    25,    26,    27,    28,    29,
      30,    31,    32,    33,   191,   192,   193,   194,   124,   125,
     126,   127,   128,   129,     4,   191,     4,     3,     3,   191,
       3,   191,     8,     8,     4,     8,     4,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    68,    69,
      70,    71,    72,    73,    74,    75,    76,     4,   940,     4,
      80,    81,   191,   111,   112,   113,   114,     4,   116,     4,
     166,    91,   168,   169,    94,    95,     3,     3,   191,    99,
     191,     8,     8,     3,   104,   105,     3,     3,     8,     3,
     110,     8,     8,     4,     8,   191,     3,    94,    95,     3,
     120,     8,     3,   123,     8,   121,   122,     8,     3,     3,
     130,   131,     3,     8,     8,   135,     4,     8,   138,    34,
       4,   411,   142,     4,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,   162,   163,     4,   165,   143,   144,   145,   146,
     147,   148,   149,   150,   151,   152,   153,   154,   155,     3,
      17,    18,     4,     3,     8,   162,   163,    82,     8,     4,
       3,   191,     3,     3,   464,     8,     4,     8,     8,     3,
     470,   401,   402,     4,     8,     4,    35,    36,    37,    38,
     118,   119,   482,     4,   191,   485,   470,   485,    20,    21,
       8,     3,     8,     4,   482,     4,   496,     3,   482,     4,
       8,   485,     4,     3,     8,     4,   506,     4,   496,   482,
     506,   511,   496,     4,   482,   511,     4,   485,     4,     4,
       4,   482,   506,   191,   482,   482,   470,   511,   496,     4,
       4,   531,     4,     4,     4,     4,   511,     4,   482,     4,
     194,   485,   511,   194,   533,   194,     4,   531,   482,   482,
     482,     4,   496,     4,     4,     4,   482,     4,   192,   192,
     482,   192,   506,   496,   192,   194,   191,   511,   482,   192,
     496,   482,     4,   193,   482,   482,   194,   193,   482,   482,
     192,   482,   192,   192,     4,     4,   482,   531,   194,   482,
       4,   194,   482,   482,   482,   194,   482,   482,     4,     4,
       4,   485,     4,     4,     4,     4,     4,     4,     4,     4,
    1127,     4,   192,     4,   544,   545,   546,   177,   178,   179,
     180,   181,   182,   183,   184,   185,   186,   187,   188,   189,
     190,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,   194,     4,     4,     4,     4,     4,     4,   192,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,   192,   663,     4,     4,     4,   194,     4,   669,
     194,   194,     4,     4,   194,   664,     4,     4,   192,     4,
       4,     4,   192,     4,     4,   669,     4,   194,     4,   192,
       4,     4,     7,   194,   192,     7,     7,     7,     7,   191,
       7,   191,   191,   703,   704,     7,   706,     5,   191,   191,
     640,   191,     7,     5,     5,     5,     5,     5,   191,   703,
     704,   705,   706,     5,     5,   669,     5,     7,   191,     7,
       7,     7,   662,    26,    27,    28,    29,    30,     7,   191,
       5,     5,     5,   191,   157,   191,   191,   191,   191,   191,
       7,   191,   191,   191,   191,   191,   191,   191,   191,   703,
     704,   705,   706,   191,    57,    58,    59,    60,    61,    62,
      63,    64,     5,   191,   191,   191,    69,    70,    71,    72,
      73,    74,    75,   191,    77,    78,    79,    24,    81,     7,
       7,     7,     7,     7,     7,     7,     7,   191,     7,    92,
       7,    94,    95,    96,    97,    98,    99,   191,   191,   191,
     191,   191,   191,   106,   191,     4,   109,   110,     4,     4,
       4,     4,     4,     4,   117,     4,     4,     4,     4,     3,
     583,     6,     3,     6,     6,     3,     6,     3,     3,     6,
       3,   663,     6,     3,     6,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,   191,     3,     6,     4,
     194,     8,     6,     4,     4,     4,     4,     4,   194,   162,
     163,     4,     4,   192,     4,   192,     4,     4,     4,     4,
       3,     3,     6,     4,   192,     4,   192,   192,   192,   192,
       8,     8,   192,   194,     8,   192,   192,     8,   191,     4,
     194,     4,     4,     4,     4,   192,   192,   192,   192,   192,
       5,     7,     4,     4,     4,     4,   411,   192,   464,   192,
     194,   191,   194,   191,   191,   191,   653,   669,   470,   191,
     191,   191,   191,   191,   916,   191,   191,   191,   942,   192,
     191,   191,   194,   943,   192,   192,   946,   191,   191,   949,
     946,   755,   952,   949,   952,   943,   952,   957,   977,   943,
     960,   957,   946,   963,   952,   949,   937,   514,   952,   957,
     943,   965,   960,   957,   949,   943,   960,   977,   957,   952,
     949,   981,   943,   955,   952,   943,   943,   963,   943,   957,
     990,   952,   960,   977,   990,   952,   996,   981,   996,   943,
     945,   482,   946,   987,   954,   949,   990,   972,   952,   943,
     943,   943,   996,   957,  1145,   946,   960,   943,   952,   952,
     952,   943,   951,   948,   957,   949,   952,   960,   996,   943,
     952,   957,   943,   977,   960,   943,   943,   981,   952,   943,
     943,   952,   943,   987,   952,   952,   990,   943,   952,   952,
     943,   952,   996,   943,   943,   943,   952,   943,   943,   952,
     996,   998,   952,   952,   952,   506,   952,   952,   952,   496,
     485,   962,  1150,   726,   706,   987,   981,   960,   668,   958,
     511,   537,   664,  1160,  1180,  1200,    -1,    -1,    -1,   991,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,   531,    -1,    -1,   533,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,   996,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,  1145,    -1,  1145,    -1,  1145,
    1150,    -1,    -1,    -1,  1150,    -1,    -1,  1145,    -1,    -1,
    1160,  1145,  1150,    -1,  1160,    -1,  1150,    -1,    -1,    -1,
      -1,  1150,  1145,    -1,    -1,    -1,  1160,  1145,  1108,    -1,
      -1,    -1,  1150,    -1,  1145,    -1,    -1,    -1,  1145,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,  1145,    -1,    -1,    -1,    -1,  1150,    -1,    -1,    -1,
      -1,  1145,  1145,  1145,    -1,    -1,  1160,  1150,    -1,  1145,
      -1,    -1,    -1,  1145,  1150,    -1,    -1,    -1,    -1,    -1,
      -1,  1145,    -1,    -1,  1145,    -1,    -1,  1145,  1145,    -1,
      -1,  1145,  1145,    -1,  1145,    -1,    -1,    -1,    -1,  1145,
      -1,    -1,  1145,    -1,    -1,  1145,  1145,  1145,    -1,  1145,
    1145,  1145,    26,    27,    28,    29,    30,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    57,    58,    59,    60,    61,    62,    63,
      64,    -1,    -1,    -1,    -1,    69,    70,    71,    72,    73,
      74,    75,    76,    -1,    -1,    -1,    -1,    81,    82,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      94,    95,    -1,    97,    -1,    99,    -1,    -1,    -1,    -1,
      -1,    -1,   106,    -1,    -1,   109,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,   117,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   162,   163,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,   191
  };

  const short
  Dhcp4Parser::yystos_[] =
  {
       0,   177,   178,   179,   180,   181,   182,   183,   184,   185,
     186,   187,   188,   189,   190,   196,   197,   198,   199,   200,
     201,   202,   203,   204,   205,   206,   207,   208,   209,   210,
       0,     5,     7,     9,   191,   192,   193,   194,   211,   212,
     213,   218,     7,   227,     7,   233,     7,   272,     7,   377,
       7,   457,     7,   473,     7,   409,     7,   415,     7,   439,
       7,   353,     7,   538,     7,   584,     7,   575,   219,   214,
     228,   234,   273,   378,   458,   474,   410,   416,   440,   354,
     539,   585,   576,   211,   220,   221,   191,   216,   217,    10,
     164,   174,   175,   176,   191,   226,   229,   230,   231,   567,
     569,   571,   582,    11,    14,    23,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    80,    81,    91,    94,    95,
      99,   104,   105,   110,   120,   123,   130,   131,   135,   138,
     142,   162,   163,   165,   226,   235,   236,   237,   238,   239,
     240,   241,   242,   243,   244,   245,   246,   248,   249,   250,
     251,   252,   253,   254,   257,   259,   261,   263,   265,   266,
     267,   268,   283,   285,   291,   293,   331,   340,   347,   361,
     371,   395,   399,   407,   433,   463,   465,   467,   478,   480,
     482,   505,   517,   518,   526,   536,   573,   588,    15,    16,
      19,    22,   226,   270,   271,   274,   276,   279,   282,   463,
     465,    77,    78,    79,    92,    96,    97,    98,   106,   109,
     117,   226,   237,   238,   239,   240,   241,   242,   243,   244,
     249,   250,   251,   252,   253,   254,   257,   259,   261,   263,
     265,   379,   380,   381,   383,   385,   387,   389,   391,   393,
     395,   398,   433,   451,   463,   465,   467,   478,   480,   482,
     502,    93,   226,   391,   393,   433,   459,   460,   461,   463,
     465,   105,   111,   112,   113,   114,   115,   116,   118,   226,
     433,   463,   465,   475,   476,   477,   478,   480,   482,   484,
     488,   490,   492,   494,   496,   498,   500,   407,    34,    82,
      84,    85,    88,    89,    90,   226,   311,   417,   418,   419,
     420,   421,   422,   423,   425,   427,   429,   430,   432,   463,
     465,    83,    86,    87,   226,   311,   421,   427,   441,   442,
     443,   444,   445,   447,   448,   449,   450,   463,   465,   121,
     122,   226,   355,   356,   357,   359,   143,   144,   145,   146,
     147,   148,   149,   150,   151,   152,   153,   154,   155,   162,
     163,   226,   463,   465,   540,   541,   542,   543,   545,   546,
     548,   549,   550,   553,   555,   557,   558,   559,   561,   563,
     565,   586,   587,   588,    12,    13,   577,   578,   579,   581,
       6,     3,     4,     8,     3,   232,   583,   568,   570,   572,
       4,     3,     8,   574,   269,   286,     4,     4,     4,   479,
     481,   483,   284,   292,   294,     4,     4,     4,     4,     4,
       4,     4,     4,     4,   247,     4,     4,     4,     4,     4,
     255,   258,   260,     4,   372,   408,   434,   400,   464,   466,
     396,   332,   506,   468,   348,   362,     4,   341,   519,   527,
     537,   262,   264,   589,     3,     8,   275,   277,   280,     4,
       3,     8,   384,   386,   388,   452,   382,   390,     4,   394,
     392,   503,     3,     8,   462,     3,     8,   501,   489,   491,
     495,   493,   499,   497,   485,     8,     3,     8,   424,   312,
       4,   428,   426,   431,     4,     8,     3,   446,     4,     4,
       8,     3,   358,   360,     3,     8,     4,   556,   544,     4,
     547,     4,     4,   551,   554,     4,     4,   560,   562,   564,
     566,     3,     8,     3,     8,   580,     4,     3,     8,   211,
     211,   191,     4,     4,     4,     4,     4,   230,     4,     4,
       4,   194,   194,   194,     4,     4,     4,     4,     4,     4,
     192,   192,   192,   192,   192,   194,   193,   193,   192,     4,
     192,   192,   194,   194,   194,     4,     4,     4,   194,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,   192,     4,     4,     4,     4,     4,     4,     4,   236,
       4,     4,     4,   194,   271,     4,     4,     4,     4,     4,
       4,   192,     4,     4,     4,   380,     4,   460,     4,     4,
       4,     4,     4,     4,     4,     4,   477,     4,     4,   192,
       4,     4,     4,   194,   419,     4,   194,   194,   443,     4,
       4,   356,   194,     4,     4,   192,     4,   192,   192,     4,
       4,   194,   194,     4,     4,     4,     4,   541,   587,     4,
     192,   578,     4,     7,     7,   211,   211,   211,     7,     7,
       7,   191,   191,   191,     7,     7,     5,   191,   158,   159,
     160,   161,   194,   256,   191,   191,     5,     5,     5,     5,
     213,   215,   191,   100,   101,   102,   103,   397,     5,     5,
       5,     5,     7,     7,     7,     7,     7,   191,   191,     5,
       5,   222,    17,    18,   278,    20,    21,   281,   191,   191,
     191,     5,   191,   191,   222,   191,     7,   191,   222,   191,
     191,   191,   191,   191,   191,   191,   191,   191,   191,   191,
     191,   191,   191,   211,   191,   191,   191,    18,   156,   552,
     157,   256,   191,   191,   191,     5,   211,   235,   586,   577,
     270,    24,   287,   288,   289,    34,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,   226,   299,   300,   301,   304,   306,
     308,   310,   311,   313,   314,   315,   316,   317,   318,   319,
     320,   322,   324,   326,   328,   329,   330,   299,     7,   295,
     296,   297,     7,   373,   374,   375,     7,   411,   412,   413,
       7,   435,   436,   437,     7,   401,   402,   403,   111,   112,
     113,   114,   116,   333,   334,   335,   336,   337,   338,   339,
       7,   507,   508,     7,   469,   470,   471,     7,   349,   350,
     351,   124,   125,   126,   127,   128,   129,   363,   364,   365,
     366,   367,   368,   369,   370,   132,   133,   134,   226,   342,
     343,   344,   345,   346,   463,   465,   136,   137,   226,   463,
     465,   520,   521,   522,   524,   139,   140,   141,   191,   463,
     465,   528,   529,   530,   531,   533,   534,   540,     7,   590,
     591,   223,     7,   453,   454,   455,   119,   484,   486,   504,
     295,     8,     8,     8,     8,   290,     3,     8,   302,   305,
     307,   309,     4,     4,     4,     4,     4,   321,   323,   325,
     327,     4,     4,     4,     4,     4,     4,     3,     8,     8,
     298,     6,     3,   376,     6,     3,   414,     6,     3,   438,
       6,     3,   404,     6,     3,     3,     6,   509,     3,     6,
     472,     6,     3,   352,     6,     3,     4,     4,     4,     4,
       4,     4,     3,     8,     4,     4,     4,     3,     8,   523,
     525,     3,     8,     4,   532,     4,   535,     3,     8,     8,
     592,     3,     6,   191,   224,   225,   456,     6,     3,   487,
       8,     6,     4,   288,     4,     4,     4,     4,   192,   194,
     192,   194,   192,     4,     4,     4,     4,   192,   192,   192,
     192,   194,   192,   300,   299,   297,   379,   375,   417,   413,
     441,   437,   226,   237,   238,   239,   240,   241,   242,   243,
     244,   249,   250,   251,   252,   253,   254,   257,   259,   261,
     263,   265,   311,   371,   389,   391,   393,   395,   405,   406,
     433,   463,   465,   478,   480,   482,   502,   403,   334,   107,
     108,   226,   311,   407,   433,   463,   465,   478,   480,   482,
     510,   511,   512,   513,   514,   516,   508,   475,   471,   355,
     351,   192,   192,   192,   192,   192,   192,   364,   194,   192,
     192,   343,     4,     4,   521,   194,     4,   192,     4,   529,
     166,   168,   169,   226,   311,   463,   465,   593,   594,   595,
     596,   598,   591,     6,     3,   459,   455,     4,   191,    35,
      36,    37,    38,   303,   191,   191,   191,   191,   191,   191,
     191,     8,     8,     8,     8,     3,     8,   515,     4,     8,
       3,     8,     8,   191,   191,   191,   211,   599,     4,   597,
       3,     8,   191,     8,   222,   406,     4,   194,   512,     4,
     192,     4,   594,   191,     5,   191,     7,   600,   601,   602,
       3,     6,   167,   170,   171,   172,   173,   603,   604,   605,
     607,   608,   609,   610,   601,   606,     4,     4,     4,   611,
       3,     8,     4,   194,   192,   192,     4,   604,   191,   191
  };

  const short
  Dhcp4Parser::yyr1_[] =
  {
       0,   195,   197,   196,   198,   196,   199,   196,   200,   196,
     201,   196,   202,   196,   203,   196,   204,   196,   205,   196,
     206,   196,   207,   196,   208,   196,   209,   196,   210,   196,
     211,   211,   211,   211,   211,   211,   211,   212,   214,   213,
     215,   216,   216,   217,   217,   219,   218,   220,   220,   221,
     221,   223,   222,   224,   224,   225,   225,   226,   228,   227,
     229,   229,   230,   230,   230,   230,   230,   230,   232,   231,
     234,   233,   235,   235,   236,   236,   236,   236,   236,   236,
     236,   236,   236,   236,   236,   236,   236,   236,   236,   236,
     236,   236,   236,   236,   236,   236,   236,   236,   236,   236,
     236,   236,   236,   236,   236,   236,   236,   236,   236,   236,
     236,   236,   236,   236,   236,   236,   236,   236,   236,   236,
     236,   236,   236,   236,   236,   236,   237,   238,   239,   240,
     241,   242,   243,   244,   245,   247,   246,   248,   249,   250,
     251,   252,   253,   255,   254,   256,   256,   256,   256,   256,
     258,   257,   260,   259,   262,   261,   264,   263,   265,   266,
     267,   269,   268,   270,   270,   271,   271,   271,   271,   271,
     271,   271,   273,   272,   275,   274,   277,   276,   278,   278,
     280,   279,   281,   281,   282,   284,   283,   286,   285,   287,
     287,   288,   290,   289,   292,   291,   294,   293,   295,   295,
     296,   296,   298,   297,   299,   299,   300,   300,   300,   300,
     300,   300,   300,   300,   300,   300,   300,   300,   300,   300,
     300,   300,   300,   300,   300,   300,   300,   302,   301,   303,
     303,   303,   303,   305,   304,   307,   306,   309,   308,   310,
     312,   311,   313,   314,   315,   316,   317,   318,   319,   321,
     320,   323,   322,   325,   324,   327,   326,   328,   329,   330,
     332,   331,   333,   333,   334,   334,   334,   334,   334,   335,
     336,   337,   338,   339,   341,   340,   342,   342,   343,   343,
     343,   343,   343,   343,   344,   345,   346,   348,   347,   349,
     349,   350,   350,   352,   351,   354,   353,   355,   355,   355,
     356,   356,   358,   357,   360,   359,   362,   361,   363,   363,
     364,   364,   364,   364,   364,   364,   365,   366,   367,   368,
     369,   370,   372,   371,   373,   373,   374,   374,   376,   375,
     378,   377,   379,   379,   380,   380,   380,   380,   380,   380,
     380,   380,   380,   380,   380,   380,   380,   380,   380,   380,
     380,   380,   380,   380,   380,   380,   380,   380,   380,   380,
     380,   380,   380,   380,   380,   380,   380,   380,   380,   380,
     380,   380,   382,   381,   384,   383,   386,   385,   388,   387,
     390,   389,   392,   391,   394,   393,   396,   395,   397,   397,
     397,   397,   398,   400,   399,   401,   401,   402,   402,   404,
     403,   405,   405,   406,   406,   406,   406,   406,   406,   406,
     406,   406,   406,   406,   406,   406,   406,   406,   406,   406,
     406,   406,   406,   406,   406,   406,   406,   406,   406,   406,
     406,   406,   406,   406,   406,   406,   408,   407,   410,   409,
     411,   411,   412,   412,   414,   413,   416,   415,   417,   417,
     418,   418,   419,   419,   419,   419,   419,   419,   419,   419,
     419,   419,   420,   421,   422,   424,   423,   426,   425,   428,
     427,   429,   431,   430,   432,   434,   433,   435,   435,   436,
     436,   438,   437,   440,   439,   441,   441,   442,   442,   443,
     443,   443,   443,   443,   443,   443,   443,   443,   444,   446,
     445,   447,   448,   449,   450,   452,   451,   453,   453,   454,
     454,   456,   455,   458,   457,   459,   459,   460,   460,   460,
     460,   460,   460,   460,   462,   461,   464,   463,   466,   465,
     468,   467,   469,   469,   470,   470,   472,   471,   474,   473,
     475,   475,   476,   476,   477,   477,   477,   477,   477,   477,
     477,   477,   477,   477,   477,   477,   477,   477,   477,   479,
     478,   481,   480,   483,   482,   485,   484,   487,   486,   489,
     488,   491,   490,   493,   492,   495,   494,   497,   496,   499,
     498,   501,   500,   503,   502,   504,   504,   506,   505,   507,
     507,   509,   508,   510,   510,   511,   511,   512,   512,   512,
     512,   512,   512,   512,   512,   512,   512,   512,   513,   515,
     514,   516,   517,   519,   518,   520,   520,   521,   521,   521,
     521,   521,   523,   522,   525,   524,   527,   526,   528,   528,
     529,   529,   529,   529,   529,   529,   530,   532,   531,   533,
     535,   534,   537,   536,   539,   538,   540,   540,   541,   541,
     541,   541,   541,   541,   541,   541,   541,   541,   541,   541,
     541,   541,   541,   541,   541,   541,   542,   544,   543,   545,
     547,   546,   548,   549,   551,   550,   552,   552,   554,   553,
     556,   555,   557,   558,   560,   559,   562,   561,   564,   563,
     566,   565,   568,   567,   570,   569,   572,   571,   574,   573,
     576,   575,   577,   577,   578,   578,   580,   579,   581,   583,
     582,   585,   584,   586,   586,   587,   589,   588,   590,   590,
     592,   591,   593,   593,   594,   594,   594,   594,   594,   594,
     594,   595,   597,   596,   599,   598,   600,   600,   602,   601,
     603,   603,   604,   604,   604,   604,   604,   606,   605,   607,
     608,   609,   611,   610
  };

  const signed char
  Dhcp4Parser::yyr2_[] =
  {
       0,     2,     0,     3,     0,     3,     0,     3,     0,     3,
       0,     3,     0,     3,     0,     3,     0,     3,     0,     3,
       0,     3,     0,     3,     0,     3,     0,     3,     0,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       1,     0,     1,     3,     5,     0,     4,     0,     1,     1,
       3,     0,     4,     0,     1,     1,     3,     2,     0,     4,
       1,     3,     1,     1,     1,     1,     1,     1,     0,     6,
       0,     4,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     0,     4,     3,     3,     3,
       3,     3,     3,     0,     4,     1,     1,     1,     1,     1,
       0,     4,     0,     4,     0,     4,     0,     4,     3,     3,
       3,     0,     6,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     0,     4,     0,     4,     1,     1,
       0,     4,     1,     1,     3,     0,     6,     0,     6,     1,
       3,     1,     0,     4,     0,     6,     0,     6,     0,     1,
       1,     3,     0,     4,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     1,
       1,     1,     1,     0,     4,     0,     4,     0,     4,     3,
       0,     4,     3,     3,     3,     3,     3,     3,     3,     0,
       4,     0,     4,     0,     4,     0,     4,     3,     3,     3,
       0,     6,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     6,     1,     3,     1,     1,
       1,     1,     1,     1,     3,     3,     3,     0,     6,     0,
       1,     1,     3,     0,     4,     0,     4,     1,     3,     1,
       1,     1,     0,     4,     0,     4,     0,     6,     1,     3,
       1,     1,     1,     1,     1,     1,     3,     3,     3,     3,
       3,     3,     0,     6,     0,     1,     1,     3,     0,     4,
       0,     4,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     1,     1,
       1,     1,     3,     0,     6,     0,     1,     1,     3,     0,
       4,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     6,     0,     4,
       0,     1,     1,     3,     0,     4,     0,     4,     0,     1,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     3,     1,     0,     4,     0,     4,     0,
       4,     1,     0,     4,     3,     0,     6,     0,     1,     1,
       3,     0,     4,     0,     4,     0,     1,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     1,     1,     3,     3,     0,     6,     0,     1,     1,
       3,     0,     4,     0,     4,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     0,     4,     0,     4,
       0,     6,     0,     1,     1,     3,     0,     4,     0,     4,
       0,     1,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     6,     1,     1,     0,     6,     1,
       3,     0,     4,     0,     1,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     3,     3,     0,     6,     1,     3,     1,     1,     1,
       1,     1,     0,     4,     0,     4,     0,     6,     1,     3,
       1,     1,     1,     1,     1,     1,     3,     0,     4,     3,
       0,     4,     0,     6,     0,     4,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     0,     4,     3,
       0,     4,     3,     3,     0,     4,     1,     1,     0,     4,
       0,     4,     3,     3,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     6,
       0,     4,     1,     3,     1,     1,     0,     6,     3,     0,
       6,     0,     4,     1,     3,     1,     0,     6,     1,     3,
       0,     4,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     3,     0,     4,     0,     6,     1,     3,     0,     4,
       1,     3,     1,     1,     1,     1,     1,     0,     4,     3,
       3,     3,     0,     4
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
  "\"postgresql\"", "\"cql\"", "\"user\"", "\"password\"", "\"host\"",
  "\"port\"", "\"persist\"", "\"lfc-interval\"", "\"readonly\"",
  "\"connect-timeout\"", "\"contact-points\"", "\"keyspace\"",
  "\"consistency\"", "\"serial-consistency\"", "\"max-reconnect-tries\"",
  "\"reconnect-wait-time\"", "\"request-timeout\"", "\"tcp-keepalive\"",
  "\"tcp-nodelay\"", "\"max-row-errors\"", "\"valid-lifetime\"",
  "\"min-valid-lifetime\"", "\"max-valid-lifetime\"", "\"renew-timer\"",
  "\"rebind-timer\"", "\"calculate-tee-times\"", "\"t1-percent\"",
  "\"t2-percent\"", "\"decline-probation-period\"", "\"server-tag\"",
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
  "\"hostname-char-set\"", "\"hostname-char-replacement\"", "\"Logging\"",
  "\"loggers\"", "\"output_options\"", "\"output\"", "\"debuglevel\"",
  "\"severity\"", "\"flush\"", "\"maxsize\"", "\"maxver\"", "\"pattern\"",
  "\"Dhcp6\"", "\"DhcpDdns\"", "\"Control-agent\"", "TOPLEVEL_JSON",
  "TOPLEVEL_DHCP4", "SUB_DHCP4", "SUB_INTERFACES4", "SUB_SUBNET4",
  "SUB_POOL4", "SUB_RESERVATION", "SUB_OPTION_DEFS", "SUB_OPTION_DEF",
  "SUB_OPTION_DATA", "SUB_HOOKS_LIBRARY", "SUB_DHCP_DDNS", "SUB_LOGGING",
  "SUB_CONFIG_CONTROL", "\"constant string\"", "\"integer\"",
  "\"floating point\"", "\"boolean\"", "$accept", "start", "$@1", "$@2",
  "$@3", "$@4", "$@5", "$@6", "$@7", "$@8", "$@9", "$@10", "$@11", "$@12",
  "$@13", "$@14", "value", "sub_json", "map2", "$@15", "map_value",
  "map_content", "not_empty_map", "list_generic", "$@16", "list_content",
  "not_empty_list", "list_strings", "$@17", "list_strings_content",
  "not_empty_list_strings", "unknown_map_entry", "syntax_map", "$@18",
  "global_objects", "global_object", "dhcp4_object", "$@19", "sub_dhcp4",
  "$@20", "global_params", "global_param", "valid_lifetime",
  "min_valid_lifetime", "max_valid_lifetime", "renew_timer",
  "rebind_timer", "calculate_tee_times", "t1_percent", "t2_percent",
  "decline_probation_period", "server_tag", "$@21", "echo_client_id",
  "match_client_id", "authoritative", "ddns_send_updates",
  "ddns_override_no_update", "ddns_override_client_update",
  "ddns_replace_client_name", "$@22", "ddns_replace_client_name_value",
  "ddns_generated_prefix", "$@23", "ddns_qualifying_suffix", "$@24",
  "hostname_char_set", "$@25", "hostname_char_replacement", "$@26",
  "store_extended_info", "statistic_default_sample_count",
  "statistic_default_sample_age", "interfaces_config", "$@27",
  "interfaces_config_params", "interfaces_config_param", "sub_interfaces4",
  "$@28", "interfaces_list", "$@29", "dhcp_socket_type", "$@30",
  "socket_type", "outbound_interface", "$@31", "outbound_interface_value",
  "re_detect", "lease_database", "$@32", "sanity_checks", "$@33",
  "sanity_checks_params", "sanity_checks_param", "lease_checks", "$@34",
  "hosts_database", "$@35", "hosts_databases", "$@36", "database_list",
  "not_empty_database_list", "database", "$@37", "database_map_params",
  "database_map_param", "database_type", "$@38", "db_type", "user", "$@39",
  "password", "$@40", "host", "$@41", "port", "name", "$@42", "persist",
  "lfc_interval", "readonly", "connect_timeout", "request_timeout",
  "tcp_keepalive", "tcp_nodelay", "contact_points", "$@43", "keyspace",
  "$@44", "consistency", "$@45", "serial_consistency", "$@46",
  "max_reconnect_tries", "reconnect_wait_time", "max_row_errors",
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
  "$@63", "require_client_classes", "$@64", "reservation_mode", "$@65",
  "hr_mode", "id", "shared_networks", "$@66", "shared_networks_content",
  "shared_networks_list", "shared_network", "$@67",
  "shared_network_params", "shared_network_param", "option_def_list",
  "$@68", "sub_option_def_list", "$@69", "option_def_list_content",
  "not_empty_option_def_list", "option_def_entry", "$@70",
  "sub_option_def", "$@71", "option_def_params",
  "not_empty_option_def_params", "option_def_param", "option_def_name",
  "code", "option_def_code", "option_def_type", "$@72",
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
  "dep_hostname_char_replacement", "$@121", "dhcp6_json_object", "$@122",
  "dhcpddns_json_object", "$@123", "control_agent_json_object", "$@124",
  "config_control", "$@125", "sub_config_control", "$@126",
  "config_control_params", "config_control_param", "config_databases",
  "$@127", "config_fetch_wait_time", "logging_object", "$@128",
  "sub_logging", "$@129", "logging_params", "logging_param", "loggers",
  "$@130", "loggers_entries", "logger_entry", "$@131", "logger_params",
  "logger_param", "debuglevel", "severity", "$@132", "output_options_list",
  "$@133", "output_options_list_content", "output_entry", "$@134",
  "output_params_list", "output_params", "output", "$@135", "flush",
  "maxsize", "maxver", "pattern", "$@136", YY_NULLPTR
  };

#if PARSER4_DEBUG
  const short
  Dhcp4Parser::yyrline_[] =
  {
       0,   283,   283,   283,   284,   284,   285,   285,   286,   286,
     287,   287,   288,   288,   289,   289,   290,   290,   291,   291,
     292,   292,   293,   293,   294,   294,   295,   295,   296,   296,
     304,   305,   306,   307,   308,   309,   310,   313,   318,   318,
     329,   332,   333,   336,   340,   347,   347,   354,   355,   358,
     362,   369,   369,   376,   377,   380,   384,   395,   405,   405,
     421,   422,   426,   427,   428,   429,   430,   431,   434,   434,
     449,   449,   458,   459,   464,   465,   466,   467,   468,   469,
     470,   471,   472,   473,   474,   475,   476,   477,   478,   479,
     480,   481,   482,   483,   484,   485,   486,   487,   488,   489,
     490,   491,   492,   493,   494,   495,   496,   497,   498,   499,
     500,   501,   502,   503,   504,   505,   506,   507,   508,   509,
     510,   511,   512,   513,   514,   515,   518,   523,   528,   533,
     538,   543,   548,   553,   558,   563,   563,   571,   576,   581,
     586,   591,   596,   601,   601,   609,   612,   615,   618,   621,
     627,   627,   635,   635,   643,   643,   651,   651,   659,   664,
     669,   674,   674,   685,   686,   689,   690,   691,   692,   693,
     694,   695,   698,   698,   707,   707,   717,   717,   724,   725,
     728,   728,   735,   737,   741,   747,   747,   759,   759,   769,
     770,   772,   774,   774,   792,   792,   804,   804,   814,   815,
     818,   819,   822,   822,   832,   833,   836,   837,   838,   839,
     840,   841,   842,   843,   844,   845,   846,   847,   848,   849,
     850,   851,   852,   853,   854,   855,   856,   859,   859,   866,
     867,   868,   869,   872,   872,   880,   880,   888,   888,   896,
     901,   901,   909,   914,   919,   924,   929,   934,   939,   944,
     944,   952,   952,   960,   960,   968,   968,   976,   981,   986,
     992,   992,  1002,  1003,  1006,  1007,  1008,  1009,  1010,  1013,
    1018,  1023,  1028,  1033,  1040,  1040,  1052,  1053,  1056,  1057,
    1058,  1059,  1060,  1061,  1064,  1069,  1074,  1079,  1079,  1089,
    1090,  1093,  1094,  1097,  1097,  1107,  1107,  1117,  1118,  1119,
    1122,  1123,  1126,  1126,  1134,  1134,  1142,  1142,  1153,  1154,
    1157,  1158,  1159,  1160,  1161,  1162,  1165,  1170,  1175,  1180,
    1185,  1190,  1198,  1198,  1211,  1212,  1215,  1216,  1223,  1223,
    1249,  1249,  1260,  1261,  1265,  1266,  1267,  1268,  1269,  1270,
    1271,  1272,  1273,  1274,  1275,  1276,  1277,  1278,  1279,  1280,
    1281,  1282,  1283,  1284,  1285,  1286,  1287,  1288,  1289,  1290,
    1291,  1292,  1293,  1294,  1295,  1296,  1297,  1298,  1299,  1300,
    1301,  1302,  1305,  1305,  1313,  1313,  1321,  1321,  1329,  1329,
    1337,  1337,  1345,  1345,  1353,  1353,  1363,  1363,  1370,  1371,
    1372,  1373,  1376,  1383,  1383,  1394,  1395,  1399,  1400,  1403,
    1403,  1411,  1412,  1415,  1416,  1417,  1418,  1419,  1420,  1421,
    1422,  1423,  1424,  1425,  1426,  1427,  1428,  1429,  1430,  1431,
    1432,  1433,  1434,  1435,  1436,  1437,  1438,  1439,  1440,  1441,
    1442,  1443,  1444,  1445,  1446,  1447,  1454,  1454,  1467,  1467,
    1476,  1477,  1480,  1481,  1486,  1486,  1501,  1501,  1515,  1516,
    1519,  1520,  1523,  1524,  1525,  1526,  1527,  1528,  1529,  1530,
    1531,  1532,  1535,  1537,  1542,  1544,  1544,  1552,  1552,  1560,
    1560,  1568,  1570,  1570,  1578,  1587,  1587,  1599,  1600,  1605,
    1606,  1611,  1611,  1623,  1623,  1635,  1636,  1641,  1642,  1647,
    1648,  1649,  1650,  1651,  1652,  1653,  1654,  1655,  1658,  1660,
    1660,  1668,  1670,  1672,  1677,  1685,  1685,  1697,  1698,  1701,
    1702,  1705,  1705,  1715,  1715,  1725,  1726,  1729,  1730,  1731,
    1732,  1733,  1734,  1735,  1738,  1738,  1746,  1746,  1771,  1771,
    1801,  1801,  1811,  1812,  1815,  1816,  1819,  1819,  1828,  1828,
    1837,  1838,  1841,  1842,  1846,  1847,  1848,  1849,  1850,  1851,
    1852,  1853,  1854,  1855,  1856,  1857,  1858,  1859,  1860,  1863,
    1863,  1871,  1871,  1879,  1879,  1887,  1887,  1895,  1895,  1905,
    1905,  1913,  1913,  1921,  1921,  1929,  1929,  1937,  1937,  1945,
    1945,  1953,  1953,  1966,  1966,  1976,  1977,  1983,  1983,  1993,
    1994,  1997,  1997,  2007,  2008,  2011,  2012,  2015,  2016,  2017,
    2018,  2019,  2020,  2021,  2022,  2023,  2024,  2025,  2028,  2030,
    2030,  2038,  2045,  2052,  2052,  2062,  2063,  2066,  2067,  2068,
    2069,  2070,  2073,  2073,  2081,  2081,  2092,  2092,  2104,  2105,
    2108,  2109,  2110,  2111,  2112,  2113,  2116,  2121,  2121,  2129,
    2134,  2134,  2143,  2143,  2155,  2155,  2165,  2166,  2169,  2170,
    2171,  2172,  2173,  2174,  2175,  2176,  2177,  2178,  2179,  2180,
    2181,  2182,  2183,  2184,  2185,  2186,  2189,  2194,  2194,  2202,
    2207,  2207,  2215,  2220,  2225,  2225,  2233,  2234,  2237,  2237,
    2246,  2246,  2255,  2261,  2267,  2267,  2275,  2275,  2284,  2284,
    2293,  2293,  2304,  2304,  2311,  2311,  2318,  2318,  2327,  2327,
    2338,  2338,  2348,  2349,  2353,  2354,  2357,  2357,  2367,  2377,
    2377,  2387,  2387,  2398,  2399,  2403,  2407,  2407,  2419,  2420,
    2424,  2424,  2432,  2433,  2436,  2437,  2438,  2439,  2440,  2441,
    2442,  2445,  2450,  2450,  2458,  2458,  2468,  2469,  2472,  2472,
    2480,  2481,  2484,  2485,  2486,  2487,  2488,  2491,  2491,  2499,
    2504,  2509,  2514,  2514
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
#line 5525 "dhcp4_parser.cc"

#line 2522 "dhcp4_parser.yy"


void
isc::dhcp::Dhcp4Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
