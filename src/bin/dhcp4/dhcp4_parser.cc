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
      case 205: // value
      case 209: // map_value
      case 250: // ddns_replace_client_name_value
      case 270: // socket_type
      case 273: // outbound_interface_value
      case 295: // db_type
      case 382: // hr_mode
      case 537: // ncr_protocol_value
        value.YY_MOVE_OR_COPY< ElementPtr > (YY_MOVE (that.value));
        break;

      case 188: // "boolean"
        value.YY_MOVE_OR_COPY< bool > (YY_MOVE (that.value));
        break;

      case 187: // "floating point"
        value.YY_MOVE_OR_COPY< double > (YY_MOVE (that.value));
        break;

      case 186: // "integer"
        value.YY_MOVE_OR_COPY< int64_t > (YY_MOVE (that.value));
        break;

      case 185: // "constant string"
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
      case 205: // value
      case 209: // map_value
      case 250: // ddns_replace_client_name_value
      case 270: // socket_type
      case 273: // outbound_interface_value
      case 295: // db_type
      case 382: // hr_mode
      case 537: // ncr_protocol_value
        value.move< ElementPtr > (YY_MOVE (that.value));
        break;

      case 188: // "boolean"
        value.move< bool > (YY_MOVE (that.value));
        break;

      case 187: // "floating point"
        value.move< double > (YY_MOVE (that.value));
        break;

      case 186: // "integer"
        value.move< int64_t > (YY_MOVE (that.value));
        break;

      case 185: // "constant string"
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
      case 205: // value
      case 209: // map_value
      case 250: // ddns_replace_client_name_value
      case 270: // socket_type
      case 273: // outbound_interface_value
      case 295: // db_type
      case 382: // hr_mode
      case 537: // ncr_protocol_value
        value.copy< ElementPtr > (that.value);
        break;

      case 188: // "boolean"
        value.copy< bool > (that.value);
        break;

      case 187: // "floating point"
        value.copy< double > (that.value);
        break;

      case 186: // "integer"
        value.copy< int64_t > (that.value);
        break;

      case 185: // "constant string"
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
      case 205: // value
      case 209: // map_value
      case 250: // ddns_replace_client_name_value
      case 270: // socket_type
      case 273: // outbound_interface_value
      case 295: // db_type
      case 382: // hr_mode
      case 537: // ncr_protocol_value
        value.move< ElementPtr > (that.value);
        break;

      case 188: // "boolean"
        value.move< bool > (that.value);
        break;

      case 187: // "floating point"
        value.move< double > (that.value);
        break;

      case 186: // "integer"
        value.move< int64_t > (that.value);
        break;

      case 185: // "constant string"
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
      case 185: // "constant string"
#line 267 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < std::string > (); }
#line 447 "dhcp4_parser.cc"
        break;

      case 186: // "integer"
#line 267 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < int64_t > (); }
#line 453 "dhcp4_parser.cc"
        break;

      case 187: // "floating point"
#line 267 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < double > (); }
#line 459 "dhcp4_parser.cc"
        break;

      case 188: // "boolean"
#line 267 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < bool > (); }
#line 465 "dhcp4_parser.cc"
        break;

      case 205: // value
#line 267 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 471 "dhcp4_parser.cc"
        break;

      case 209: // map_value
#line 267 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 477 "dhcp4_parser.cc"
        break;

      case 250: // ddns_replace_client_name_value
#line 267 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 483 "dhcp4_parser.cc"
        break;

      case 270: // socket_type
#line 267 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 489 "dhcp4_parser.cc"
        break;

      case 273: // outbound_interface_value
#line 267 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 495 "dhcp4_parser.cc"
        break;

      case 295: // db_type
#line 267 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 501 "dhcp4_parser.cc"
        break;

      case 382: // hr_mode
#line 267 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 507 "dhcp4_parser.cc"
        break;

      case 537: // ncr_protocol_value
#line 267 "dhcp4_parser.yy"
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
      case 205: // value
      case 209: // map_value
      case 250: // ddns_replace_client_name_value
      case 270: // socket_type
      case 273: // outbound_interface_value
      case 295: // db_type
      case 382: // hr_mode
      case 537: // ncr_protocol_value
        yylhs.value.emplace< ElementPtr > ();
        break;

      case 188: // "boolean"
        yylhs.value.emplace< bool > ();
        break;

      case 187: // "floating point"
        yylhs.value.emplace< double > ();
        break;

      case 186: // "integer"
        yylhs.value.emplace< int64_t > ();
        break;

      case 185: // "constant string"
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
#line 276 "dhcp4_parser.yy"
                     { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 781 "dhcp4_parser.cc"
    break;

  case 4:
#line 277 "dhcp4_parser.yy"
                      { ctx.ctx_ = ctx.CONFIG; }
#line 787 "dhcp4_parser.cc"
    break;

  case 6:
#line 278 "dhcp4_parser.yy"
                 { ctx.ctx_ = ctx.DHCP4; }
#line 793 "dhcp4_parser.cc"
    break;

  case 8:
#line 279 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 799 "dhcp4_parser.cc"
    break;

  case 10:
#line 280 "dhcp4_parser.yy"
                   { ctx.ctx_ = ctx.SUBNET4; }
#line 805 "dhcp4_parser.cc"
    break;

  case 12:
#line 281 "dhcp4_parser.yy"
                 { ctx.ctx_ = ctx.POOLS; }
#line 811 "dhcp4_parser.cc"
    break;

  case 14:
#line 282 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.RESERVATIONS; }
#line 817 "dhcp4_parser.cc"
    break;

  case 16:
#line 283 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.DHCP4; }
#line 823 "dhcp4_parser.cc"
    break;

  case 18:
#line 284 "dhcp4_parser.yy"
                      { ctx.ctx_ = ctx.OPTION_DEF; }
#line 829 "dhcp4_parser.cc"
    break;

  case 20:
#line 285 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.OPTION_DATA; }
#line 835 "dhcp4_parser.cc"
    break;

  case 22:
#line 286 "dhcp4_parser.yy"
                         { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 841 "dhcp4_parser.cc"
    break;

  case 24:
#line 287 "dhcp4_parser.yy"
                     { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 847 "dhcp4_parser.cc"
    break;

  case 26:
#line 288 "dhcp4_parser.yy"
                   { ctx.ctx_ = ctx.LOGGING; }
#line 853 "dhcp4_parser.cc"
    break;

  case 28:
#line 289 "dhcp4_parser.yy"
                          { ctx.ctx_ = ctx.CONFIG_CONTROL; }
#line 859 "dhcp4_parser.cc"
    break;

  case 30:
#line 297 "dhcp4_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 865 "dhcp4_parser.cc"
    break;

  case 31:
#line 298 "dhcp4_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location))); }
#line 871 "dhcp4_parser.cc"
    break;

  case 32:
#line 299 "dhcp4_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 877 "dhcp4_parser.cc"
    break;

  case 33:
#line 300 "dhcp4_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 883 "dhcp4_parser.cc"
    break;

  case 34:
#line 301 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 889 "dhcp4_parser.cc"
    break;

  case 35:
#line 302 "dhcp4_parser.yy"
            { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 895 "dhcp4_parser.cc"
    break;

  case 36:
#line 303 "dhcp4_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 901 "dhcp4_parser.cc"
    break;

  case 37:
#line 306 "dhcp4_parser.yy"
                {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as < ElementPtr > ());
}
#line 910 "dhcp4_parser.cc"
    break;

  case 38:
#line 311 "dhcp4_parser.yy"
                     {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 921 "dhcp4_parser.cc"
    break;

  case 39:
#line 316 "dhcp4_parser.yy"
                             {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 931 "dhcp4_parser.cc"
    break;

  case 40:
#line 322 "dhcp4_parser.yy"
                { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 937 "dhcp4_parser.cc"
    break;

  case 43:
#line 329 "dhcp4_parser.yy"
                                  {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 946 "dhcp4_parser.cc"
    break;

  case 44:
#line 333 "dhcp4_parser.yy"
                                                      {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 956 "dhcp4_parser.cc"
    break;

  case 45:
#line 340 "dhcp4_parser.yy"
                              {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 965 "dhcp4_parser.cc"
    break;

  case 46:
#line 343 "dhcp4_parser.yy"
                               {
    // list parsing complete. Put any sanity checking here
}
#line 973 "dhcp4_parser.cc"
    break;

  case 49:
#line 351 "dhcp4_parser.yy"
                      {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 982 "dhcp4_parser.cc"
    break;

  case 50:
#line 355 "dhcp4_parser.yy"
                                           {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 991 "dhcp4_parser.cc"
    break;

  case 51:
#line 362 "dhcp4_parser.yy"
                              {
    // List parsing about to start
}
#line 999 "dhcp4_parser.cc"
    break;

  case 52:
#line 364 "dhcp4_parser.yy"
                                       {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 1008 "dhcp4_parser.cc"
    break;

  case 55:
#line 373 "dhcp4_parser.yy"
                               {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 1017 "dhcp4_parser.cc"
    break;

  case 56:
#line 377 "dhcp4_parser.yy"
                                                            {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 1026 "dhcp4_parser.cc"
    break;

  case 57:
#line 388 "dhcp4_parser.yy"
                                {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as < std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 1037 "dhcp4_parser.cc"
    break;

  case 58:
#line 398 "dhcp4_parser.yy"
                           {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1048 "dhcp4_parser.cc"
    break;

  case 59:
#line 403 "dhcp4_parser.yy"
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
#line 427 "dhcp4_parser.yy"
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
#line 434 "dhcp4_parser.yy"
                                                    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1084 "dhcp4_parser.cc"
    break;

  case 70:
#line 442 "dhcp4_parser.yy"
                          {
    // Parse the Dhcp4 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1094 "dhcp4_parser.cc"
    break;

  case 71:
#line 446 "dhcp4_parser.yy"
                               {
    // No global parameter is required
    // parsing completed
}
#line 1103 "dhcp4_parser.cc"
    break;

  case 123:
#line 508 "dhcp4_parser.yy"
                                             {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1112 "dhcp4_parser.cc"
    break;

  case 124:
#line 513 "dhcp4_parser.yy"
                                                     {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-valid-lifetime", prf);
}
#line 1121 "dhcp4_parser.cc"
    break;

  case 125:
#line 518 "dhcp4_parser.yy"
                                                     {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-valid-lifetime", prf);
}
#line 1130 "dhcp4_parser.cc"
    break;

  case 126:
#line 523 "dhcp4_parser.yy"
                                       {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1139 "dhcp4_parser.cc"
    break;

  case 127:
#line 528 "dhcp4_parser.yy"
                                         {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1148 "dhcp4_parser.cc"
    break;

  case 128:
#line 533 "dhcp4_parser.yy"
                                                       {
    ElementPtr ctt(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("calculate-tee-times", ctt);
}
#line 1157 "dhcp4_parser.cc"
    break;

  case 129:
#line 538 "dhcp4_parser.yy"
                                   {
    ElementPtr t1(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t1-percent", t1);
}
#line 1166 "dhcp4_parser.cc"
    break;

  case 130:
#line 543 "dhcp4_parser.yy"
                                   {
    ElementPtr t2(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t2-percent", t2);
}
#line 1175 "dhcp4_parser.cc"
    break;

  case 131:
#line 548 "dhcp4_parser.yy"
                                                                 {
    ElementPtr dpp(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1184 "dhcp4_parser.cc"
    break;

  case 132:
#line 553 "dhcp4_parser.yy"
                        {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1192 "dhcp4_parser.cc"
    break;

  case 133:
#line 555 "dhcp4_parser.yy"
               {
    ElementPtr stag(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-tag", stag);
    ctx.leave();
}
#line 1202 "dhcp4_parser.cc"
    break;

  case 134:
#line 561 "dhcp4_parser.yy"
                                             {
    ElementPtr echo(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("echo-client-id", echo);
}
#line 1211 "dhcp4_parser.cc"
    break;

  case 135:
#line 566 "dhcp4_parser.yy"
                                               {
    ElementPtr match(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("match-client-id", match);
}
#line 1220 "dhcp4_parser.cc"
    break;

  case 136:
#line 571 "dhcp4_parser.yy"
                                           {
    ElementPtr prf(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("authoritative", prf);
}
#line 1229 "dhcp4_parser.cc"
    break;

  case 137:
#line 576 "dhcp4_parser.yy"
                                                   {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-send-updates", b);
}
#line 1238 "dhcp4_parser.cc"
    break;

  case 138:
#line 581 "dhcp4_parser.yy"
                                                               {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-no-update", b);
}
#line 1247 "dhcp4_parser.cc"
    break;

  case 139:
#line 586 "dhcp4_parser.yy"
                                                                       {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-client-update", b);
}
#line 1256 "dhcp4_parser.cc"
    break;

  case 140:
#line 591 "dhcp4_parser.yy"
                                                   {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 1264 "dhcp4_parser.cc"
    break;

  case 141:
#line 593 "dhcp4_parser.yy"
                                       {
    ctx.stack_.back()->set("ddns-replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1273 "dhcp4_parser.cc"
    break;

  case 142:
#line 599 "dhcp4_parser.yy"
                 {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1281 "dhcp4_parser.cc"
    break;

  case 143:
#line 602 "dhcp4_parser.yy"
          {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 1289 "dhcp4_parser.cc"
    break;

  case 144:
#line 605 "dhcp4_parser.yy"
           {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 1297 "dhcp4_parser.cc"
    break;

  case 145:
#line 608 "dhcp4_parser.yy"
                     {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1305 "dhcp4_parser.cc"
    break;

  case 146:
#line 611 "dhcp4_parser.yy"
             {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 1314 "dhcp4_parser.cc"
    break;

  case 147:
#line 617 "dhcp4_parser.yy"
                                             {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1322 "dhcp4_parser.cc"
    break;

  case 148:
#line 619 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-generated-prefix", s);
    ctx.leave();
}
#line 1332 "dhcp4_parser.cc"
    break;

  case 149:
#line 625 "dhcp4_parser.yy"
                                               {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1340 "dhcp4_parser.cc"
    break;

  case 150:
#line 627 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-qualifying-suffix", s);
    ctx.leave();
}
#line 1350 "dhcp4_parser.cc"
    break;

  case 151:
#line 633 "dhcp4_parser.yy"
                                     {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1358 "dhcp4_parser.cc"
    break;

  case 152:
#line 635 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 1368 "dhcp4_parser.cc"
    break;

  case 153:
#line 641 "dhcp4_parser.yy"
                                                     {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1376 "dhcp4_parser.cc"
    break;

  case 154:
#line 643 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 1386 "dhcp4_parser.cc"
    break;

  case 155:
#line 649 "dhcp4_parser.yy"
                                                       {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("store-extended-info", b);
}
#line 1395 "dhcp4_parser.cc"
    break;

  case 156:
#line 654 "dhcp4_parser.yy"
                                     {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1406 "dhcp4_parser.cc"
    break;

  case 157:
#line 659 "dhcp4_parser.yy"
                                                               {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1416 "dhcp4_parser.cc"
    break;

  case 167:
#line 678 "dhcp4_parser.yy"
                                {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1426 "dhcp4_parser.cc"
    break;

  case 168:
#line 682 "dhcp4_parser.yy"
                                          {
    // No interfaces config param is required
    // parsing completed
}
#line 1435 "dhcp4_parser.cc"
    break;

  case 169:
#line 687 "dhcp4_parser.yy"
                            {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1446 "dhcp4_parser.cc"
    break;

  case 170:
#line 692 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1455 "dhcp4_parser.cc"
    break;

  case 171:
#line 697 "dhcp4_parser.yy"
                                   {
    ctx.enter(ctx.DHCP_SOCKET_TYPE);
}
#line 1463 "dhcp4_parser.cc"
    break;

  case 172:
#line 699 "dhcp4_parser.yy"
                    {
    ctx.stack_.back()->set("dhcp-socket-type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1472 "dhcp4_parser.cc"
    break;

  case 173:
#line 704 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("raw", ctx.loc2pos(yystack_[0].location))); }
#line 1478 "dhcp4_parser.cc"
    break;

  case 174:
#line 705 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("udp", ctx.loc2pos(yystack_[0].location))); }
#line 1484 "dhcp4_parser.cc"
    break;

  case 175:
#line 708 "dhcp4_parser.yy"
                                       {
    ctx.enter(ctx.OUTBOUND_INTERFACE);
}
#line 1492 "dhcp4_parser.cc"
    break;

  case 176:
#line 710 "dhcp4_parser.yy"
                                 {
    ctx.stack_.back()->set("outbound-interface", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1501 "dhcp4_parser.cc"
    break;

  case 177:
#line 715 "dhcp4_parser.yy"
                                          {
    yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("same-as-inbound", ctx.loc2pos(yystack_[0].location)));
}
#line 1509 "dhcp4_parser.cc"
    break;

  case 178:
#line 717 "dhcp4_parser.yy"
                {
    yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("use-routing", ctx.loc2pos(yystack_[0].location)));
    }
#line 1517 "dhcp4_parser.cc"
    break;

  case 179:
#line 721 "dhcp4_parser.yy"
                                   {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1526 "dhcp4_parser.cc"
    break;

  case 180:
#line 727 "dhcp4_parser.yy"
                               {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1537 "dhcp4_parser.cc"
    break;

  case 181:
#line 732 "dhcp4_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1548 "dhcp4_parser.cc"
    break;

  case 182:
#line 739 "dhcp4_parser.yy"
                             {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sanity-checks", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SANITY_CHECKS);
}
#line 1559 "dhcp4_parser.cc"
    break;

  case 183:
#line 744 "dhcp4_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1568 "dhcp4_parser.cc"
    break;

  case 187:
#line 754 "dhcp4_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1576 "dhcp4_parser.cc"
    break;

  case 188:
#line 756 "dhcp4_parser.yy"
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
#line 1596 "dhcp4_parser.cc"
    break;

  case 189:
#line 772 "dhcp4_parser.yy"
                               {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1607 "dhcp4_parser.cc"
    break;

  case 190:
#line 777 "dhcp4_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1618 "dhcp4_parser.cc"
    break;

  case 191:
#line 784 "dhcp4_parser.yy"
                                 {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1629 "dhcp4_parser.cc"
    break;

  case 192:
#line 789 "dhcp4_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1638 "dhcp4_parser.cc"
    break;

  case 197:
#line 802 "dhcp4_parser.yy"
                         {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1648 "dhcp4_parser.cc"
    break;

  case 198:
#line 806 "dhcp4_parser.yy"
                                     {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1658 "dhcp4_parser.cc"
    break;

  case 222:
#line 839 "dhcp4_parser.yy"
                    {
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1666 "dhcp4_parser.cc"
    break;

  case 223:
#line 841 "dhcp4_parser.yy"
                {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1675 "dhcp4_parser.cc"
    break;

  case 224:
#line 846 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1681 "dhcp4_parser.cc"
    break;

  case 225:
#line 847 "dhcp4_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1687 "dhcp4_parser.cc"
    break;

  case 226:
#line 848 "dhcp4_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1693 "dhcp4_parser.cc"
    break;

  case 227:
#line 849 "dhcp4_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1699 "dhcp4_parser.cc"
    break;

  case 228:
#line 852 "dhcp4_parser.yy"
           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1707 "dhcp4_parser.cc"
    break;

  case 229:
#line 854 "dhcp4_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1717 "dhcp4_parser.cc"
    break;

  case 230:
#line 860 "dhcp4_parser.yy"
                   {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1725 "dhcp4_parser.cc"
    break;

  case 231:
#line 862 "dhcp4_parser.yy"
               {
    ElementPtr pwd(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1735 "dhcp4_parser.cc"
    break;

  case 232:
#line 868 "dhcp4_parser.yy"
           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1743 "dhcp4_parser.cc"
    break;

  case 233:
#line 870 "dhcp4_parser.yy"
               {
    ElementPtr h(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1753 "dhcp4_parser.cc"
    break;

  case 234:
#line 876 "dhcp4_parser.yy"
                         {
    ElementPtr p(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1762 "dhcp4_parser.cc"
    break;

  case 235:
#line 881 "dhcp4_parser.yy"
           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1770 "dhcp4_parser.cc"
    break;

  case 236:
#line 883 "dhcp4_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1780 "dhcp4_parser.cc"
    break;

  case 237:
#line 889 "dhcp4_parser.yy"
                               {
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1789 "dhcp4_parser.cc"
    break;

  case 238:
#line 894 "dhcp4_parser.yy"
                                         {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1798 "dhcp4_parser.cc"
    break;

  case 239:
#line 899 "dhcp4_parser.yy"
                                 {
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1807 "dhcp4_parser.cc"
    break;

  case 240:
#line 904 "dhcp4_parser.yy"
                                               {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1816 "dhcp4_parser.cc"
    break;

  case 241:
#line 909 "dhcp4_parser.yy"
                                               {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("request-timeout", n);
}
#line 1825 "dhcp4_parser.cc"
    break;

  case 242:
#line 914 "dhcp4_parser.yy"
                                           {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-keepalive", n);
}
#line 1834 "dhcp4_parser.cc"
    break;

  case 243:
#line 919 "dhcp4_parser.yy"
                                       {
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-nodelay", n);
}
#line 1843 "dhcp4_parser.cc"
    break;

  case 244:
#line 924 "dhcp4_parser.yy"
                               {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1851 "dhcp4_parser.cc"
    break;

  case 245:
#line 926 "dhcp4_parser.yy"
               {
    ElementPtr cp(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1861 "dhcp4_parser.cc"
    break;

  case 246:
#line 932 "dhcp4_parser.yy"
                   {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1869 "dhcp4_parser.cc"
    break;

  case 247:
#line 934 "dhcp4_parser.yy"
               {
    ElementPtr ks(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 1879 "dhcp4_parser.cc"
    break;

  case 248:
#line 940 "dhcp4_parser.yy"
                         {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1887 "dhcp4_parser.cc"
    break;

  case 249:
#line 942 "dhcp4_parser.yy"
               {
    ElementPtr c(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("consistency", c);
    ctx.leave();
}
#line 1897 "dhcp4_parser.cc"
    break;

  case 250:
#line 948 "dhcp4_parser.yy"
                                       {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1905 "dhcp4_parser.cc"
    break;

  case 251:
#line 950 "dhcp4_parser.yy"
               {
    ElementPtr c(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("serial-consistency", c);
    ctx.leave();
}
#line 1915 "dhcp4_parser.cc"
    break;

  case 252:
#line 956 "dhcp4_parser.yy"
                                                       {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 1924 "dhcp4_parser.cc"
    break;

  case 253:
#line 961 "dhcp4_parser.yy"
                                                       {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 1933 "dhcp4_parser.cc"
    break;

  case 254:
#line 966 "dhcp4_parser.yy"
                                             {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-row-errors", n);
}
#line 1942 "dhcp4_parser.cc"
    break;

  case 255:
#line 972 "dhcp4_parser.yy"
                                                           {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1953 "dhcp4_parser.cc"
    break;

  case 256:
#line 977 "dhcp4_parser.yy"
                                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1962 "dhcp4_parser.cc"
    break;

  case 264:
#line 993 "dhcp4_parser.yy"
               {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1971 "dhcp4_parser.cc"
    break;

  case 265:
#line 998 "dhcp4_parser.yy"
                           {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1980 "dhcp4_parser.cc"
    break;

  case 266:
#line 1003 "dhcp4_parser.yy"
                        {
    ElementPtr circuit(new StringElement("circuit-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(circuit);
}
#line 1989 "dhcp4_parser.cc"
    break;

  case 267:
#line 1008 "dhcp4_parser.yy"
                      {
    ElementPtr client(new StringElement("client-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(client);
}
#line 1998 "dhcp4_parser.cc"
    break;

  case 268:
#line 1013 "dhcp4_parser.yy"
                 {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 2007 "dhcp4_parser.cc"
    break;

  case 269:
#line 1018 "dhcp4_parser.yy"
                                 {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 2018 "dhcp4_parser.cc"
    break;

  case 270:
#line 1023 "dhcp4_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2027 "dhcp4_parser.cc"
    break;

  case 275:
#line 1036 "dhcp4_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2037 "dhcp4_parser.cc"
    break;

  case 276:
#line 1040 "dhcp4_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2047 "dhcp4_parser.cc"
    break;

  case 277:
#line 1046 "dhcp4_parser.yy"
                                  {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2057 "dhcp4_parser.cc"
    break;

  case 278:
#line 1050 "dhcp4_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2067 "dhcp4_parser.cc"
    break;

  case 284:
#line 1065 "dhcp4_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2075 "dhcp4_parser.cc"
    break;

  case 285:
#line 1067 "dhcp4_parser.yy"
               {
    ElementPtr lib(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 2085 "dhcp4_parser.cc"
    break;

  case 286:
#line 1073 "dhcp4_parser.yy"
                       {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2093 "dhcp4_parser.cc"
    break;

  case 287:
#line 1075 "dhcp4_parser.yy"
              {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2102 "dhcp4_parser.cc"
    break;

  case 288:
#line 1081 "dhcp4_parser.yy"
                                                     {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 2113 "dhcp4_parser.cc"
    break;

  case 289:
#line 1086 "dhcp4_parser.yy"
                                                            {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2123 "dhcp4_parser.cc"
    break;

  case 298:
#line 1104 "dhcp4_parser.yy"
                                                               {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 2132 "dhcp4_parser.cc"
    break;

  case 299:
#line 1109 "dhcp4_parser.yy"
                                                                               {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 2141 "dhcp4_parser.cc"
    break;

  case 300:
#line 1114 "dhcp4_parser.yy"
                                                       {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 2150 "dhcp4_parser.cc"
    break;

  case 301:
#line 1119 "dhcp4_parser.yy"
                                                     {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 2159 "dhcp4_parser.cc"
    break;

  case 302:
#line 1124 "dhcp4_parser.yy"
                                                 {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 2168 "dhcp4_parser.cc"
    break;

  case 303:
#line 1129 "dhcp4_parser.yy"
                                                               {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 2177 "dhcp4_parser.cc"
    break;

  case 304:
#line 1137 "dhcp4_parser.yy"
                      {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet4", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET4);
}
#line 2188 "dhcp4_parser.cc"
    break;

  case 305:
#line 1142 "dhcp4_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2197 "dhcp4_parser.cc"
    break;

  case 310:
#line 1162 "dhcp4_parser.yy"
                        {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2207 "dhcp4_parser.cc"
    break;

  case 311:
#line 1166 "dhcp4_parser.yy"
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
#line 2233 "dhcp4_parser.cc"
    break;

  case 312:
#line 1188 "dhcp4_parser.yy"
                            {
    // Parse the subnet4 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2243 "dhcp4_parser.cc"
    break;

  case 313:
#line 1192 "dhcp4_parser.yy"
                                {
    // The subnet subnet4 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2253 "dhcp4_parser.cc"
    break;

  case 354:
#line 1244 "dhcp4_parser.yy"
               {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2261 "dhcp4_parser.cc"
    break;

  case 355:
#line 1246 "dhcp4_parser.yy"
               {
    ElementPtr subnet(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 2271 "dhcp4_parser.cc"
    break;

  case 356:
#line 1252 "dhcp4_parser.yy"
                                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2279 "dhcp4_parser.cc"
    break;

  case 357:
#line 1254 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface", iface);
    ctx.leave();
}
#line 2289 "dhcp4_parser.cc"
    break;

  case 358:
#line 1260 "dhcp4_parser.yy"
                                                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2297 "dhcp4_parser.cc"
    break;

  case 359:
#line 1262 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface-id", iface);
    ctx.leave();
}
#line 2307 "dhcp4_parser.cc"
    break;

  case 360:
#line 1268 "dhcp4_parser.yy"
                                     {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2315 "dhcp4_parser.cc"
    break;

  case 361:
#line 1270 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-subnet", iface);
    ctx.leave();
}
#line 2325 "dhcp4_parser.cc"
    break;

  case 362:
#line 1276 "dhcp4_parser.yy"
                     {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2333 "dhcp4_parser.cc"
    break;

  case 363:
#line 1278 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 2343 "dhcp4_parser.cc"
    break;

  case 364:
#line 1284 "dhcp4_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2351 "dhcp4_parser.cc"
    break;

  case 365:
#line 1286 "dhcp4_parser.yy"
               {
    ElementPtr cls(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 2361 "dhcp4_parser.cc"
    break;

  case 366:
#line 1292 "dhcp4_parser.yy"
                                               {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2372 "dhcp4_parser.cc"
    break;

  case 367:
#line 1297 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2381 "dhcp4_parser.cc"
    break;

  case 368:
#line 1302 "dhcp4_parser.yy"
                                   {
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 2389 "dhcp4_parser.cc"
    break;

  case 369:
#line 1304 "dhcp4_parser.yy"
                {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2398 "dhcp4_parser.cc"
    break;

  case 370:
#line 1309 "dhcp4_parser.yy"
                  { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 2404 "dhcp4_parser.cc"
    break;

  case 371:
#line 1310 "dhcp4_parser.yy"
                     { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 2410 "dhcp4_parser.cc"
    break;

  case 372:
#line 1311 "dhcp4_parser.yy"
                { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("global", ctx.loc2pos(yystack_[0].location))); }
#line 2416 "dhcp4_parser.cc"
    break;

  case 373:
#line 1312 "dhcp4_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 2422 "dhcp4_parser.cc"
    break;

  case 374:
#line 1315 "dhcp4_parser.yy"
                     {
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 2431 "dhcp4_parser.cc"
    break;

  case 375:
#line 1322 "dhcp4_parser.yy"
                                 {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 2442 "dhcp4_parser.cc"
    break;

  case 376:
#line 1327 "dhcp4_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2451 "dhcp4_parser.cc"
    break;

  case 381:
#line 1342 "dhcp4_parser.yy"
                               {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2461 "dhcp4_parser.cc"
    break;

  case 382:
#line 1346 "dhcp4_parser.yy"
                                       {
    ctx.stack_.pop_back();
}
#line 2469 "dhcp4_parser.cc"
    break;

  case 418:
#line 1393 "dhcp4_parser.yy"
                            {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 2480 "dhcp4_parser.cc"
    break;

  case 419:
#line 1398 "dhcp4_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2489 "dhcp4_parser.cc"
    break;

  case 420:
#line 1406 "dhcp4_parser.yy"
                                    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2498 "dhcp4_parser.cc"
    break;

  case 421:
#line 1409 "dhcp4_parser.yy"
                                 {
    // parsing completed
}
#line 2506 "dhcp4_parser.cc"
    break;

  case 426:
#line 1425 "dhcp4_parser.yy"
                                 {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2516 "dhcp4_parser.cc"
    break;

  case 427:
#line 1429 "dhcp4_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2528 "dhcp4_parser.cc"
    break;

  case 428:
#line 1440 "dhcp4_parser.yy"
                               {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2538 "dhcp4_parser.cc"
    break;

  case 429:
#line 1444 "dhcp4_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2550 "dhcp4_parser.cc"
    break;

  case 445:
#line 1476 "dhcp4_parser.yy"
                         {
    ElementPtr code(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 2559 "dhcp4_parser.cc"
    break;

  case 447:
#line 1483 "dhcp4_parser.yy"
                      {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2567 "dhcp4_parser.cc"
    break;

  case 448:
#line 1485 "dhcp4_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 2577 "dhcp4_parser.cc"
    break;

  case 449:
#line 1491 "dhcp4_parser.yy"
                                      {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2585 "dhcp4_parser.cc"
    break;

  case 450:
#line 1493 "dhcp4_parser.yy"
               {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 2595 "dhcp4_parser.cc"
    break;

  case 451:
#line 1499 "dhcp4_parser.yy"
             {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2603 "dhcp4_parser.cc"
    break;

  case 452:
#line 1501 "dhcp4_parser.yy"
               {
    ElementPtr space(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 2613 "dhcp4_parser.cc"
    break;

  case 454:
#line 1509 "dhcp4_parser.yy"
                                    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2621 "dhcp4_parser.cc"
    break;

  case 455:
#line 1511 "dhcp4_parser.yy"
               {
    ElementPtr encap(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 2631 "dhcp4_parser.cc"
    break;

  case 456:
#line 1517 "dhcp4_parser.yy"
                                      {
    ElementPtr array(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 2640 "dhcp4_parser.cc"
    break;

  case 457:
#line 1526 "dhcp4_parser.yy"
                              {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 2651 "dhcp4_parser.cc"
    break;

  case 458:
#line 1531 "dhcp4_parser.yy"
                                                                 {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2660 "dhcp4_parser.cc"
    break;

  case 463:
#line 1550 "dhcp4_parser.yy"
                                  {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2670 "dhcp4_parser.cc"
    break;

  case 464:
#line 1554 "dhcp4_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 2679 "dhcp4_parser.cc"
    break;

  case 465:
#line 1562 "dhcp4_parser.yy"
                                {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2689 "dhcp4_parser.cc"
    break;

  case 466:
#line 1566 "dhcp4_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 2698 "dhcp4_parser.cc"
    break;

  case 481:
#line 1599 "dhcp4_parser.yy"
                       {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2706 "dhcp4_parser.cc"
    break;

  case 482:
#line 1601 "dhcp4_parser.yy"
               {
    ElementPtr data(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2716 "dhcp4_parser.cc"
    break;

  case 485:
#line 1611 "dhcp4_parser.yy"
                                                 {
    ElementPtr space(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2725 "dhcp4_parser.cc"
    break;

  case 486:
#line 1616 "dhcp4_parser.yy"
                                                   {
    ElementPtr persist(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 2734 "dhcp4_parser.cc"
    break;

  case 487:
#line 1624 "dhcp4_parser.yy"
                  {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2745 "dhcp4_parser.cc"
    break;

  case 488:
#line 1629 "dhcp4_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2754 "dhcp4_parser.cc"
    break;

  case 493:
#line 1644 "dhcp4_parser.yy"
                                {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2764 "dhcp4_parser.cc"
    break;

  case 494:
#line 1648 "dhcp4_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2774 "dhcp4_parser.cc"
    break;

  case 495:
#line 1654 "dhcp4_parser.yy"
                          {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2784 "dhcp4_parser.cc"
    break;

  case 496:
#line 1658 "dhcp4_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2794 "dhcp4_parser.cc"
    break;

  case 506:
#line 1677 "dhcp4_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2802 "dhcp4_parser.cc"
    break;

  case 507:
#line 1679 "dhcp4_parser.yy"
               {
    ElementPtr pool(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2812 "dhcp4_parser.cc"
    break;

  case 508:
#line 1685 "dhcp4_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2820 "dhcp4_parser.cc"
    break;

  case 509:
#line 1687 "dhcp4_parser.yy"
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
#line 2847 "dhcp4_parser.cc"
    break;

  case 510:
#line 1710 "dhcp4_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2855 "dhcp4_parser.cc"
    break;

  case 511:
#line 1712 "dhcp4_parser.yy"
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
#line 2884 "dhcp4_parser.cc"
    break;

  case 512:
#line 1740 "dhcp4_parser.yy"
                           {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 2895 "dhcp4_parser.cc"
    break;

  case 513:
#line 1745 "dhcp4_parser.yy"
                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2904 "dhcp4_parser.cc"
    break;

  case 518:
#line 1758 "dhcp4_parser.yy"
                            {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2914 "dhcp4_parser.cc"
    break;

  case 519:
#line 1762 "dhcp4_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 2923 "dhcp4_parser.cc"
    break;

  case 520:
#line 1767 "dhcp4_parser.yy"
                                {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2933 "dhcp4_parser.cc"
    break;

  case 521:
#line 1771 "dhcp4_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 2942 "dhcp4_parser.cc"
    break;

  case 541:
#line 1802 "dhcp4_parser.yy"
                         {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2950 "dhcp4_parser.cc"
    break;

  case 542:
#line 1804 "dhcp4_parser.yy"
               {
    ElementPtr next_server(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("next-server", next_server);
    ctx.leave();
}
#line 2960 "dhcp4_parser.cc"
    break;

  case 543:
#line 1810 "dhcp4_parser.yy"
                                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2968 "dhcp4_parser.cc"
    break;

  case 544:
#line 1812 "dhcp4_parser.yy"
               {
    ElementPtr srv(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-hostname", srv);
    ctx.leave();
}
#line 2978 "dhcp4_parser.cc"
    break;

  case 545:
#line 1818 "dhcp4_parser.yy"
                               {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2986 "dhcp4_parser.cc"
    break;

  case 546:
#line 1820 "dhcp4_parser.yy"
               {
    ElementPtr bootfile(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("boot-file-name", bootfile);
    ctx.leave();
}
#line 2996 "dhcp4_parser.cc"
    break;

  case 547:
#line 1826 "dhcp4_parser.yy"
                       {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3004 "dhcp4_parser.cc"
    break;

  case 548:
#line 1828 "dhcp4_parser.yy"
               {
    ElementPtr addr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 3014 "dhcp4_parser.cc"
    break;

  case 549:
#line 1834 "dhcp4_parser.yy"
                           {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3025 "dhcp4_parser.cc"
    break;

  case 550:
#line 1839 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3034 "dhcp4_parser.cc"
    break;

  case 551:
#line 1844 "dhcp4_parser.yy"
           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3042 "dhcp4_parser.cc"
    break;

  case 552:
#line 1846 "dhcp4_parser.yy"
               {
    ElementPtr d(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 3052 "dhcp4_parser.cc"
    break;

  case 553:
#line 1852 "dhcp4_parser.yy"
                       {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3060 "dhcp4_parser.cc"
    break;

  case 554:
#line 1854 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 3070 "dhcp4_parser.cc"
    break;

  case 555:
#line 1860 "dhcp4_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3078 "dhcp4_parser.cc"
    break;

  case 556:
#line 1862 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-id", hw);
    ctx.leave();
}
#line 3088 "dhcp4_parser.cc"
    break;

  case 557:
#line 1868 "dhcp4_parser.yy"
                             {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3096 "dhcp4_parser.cc"
    break;

  case 558:
#line 1870 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("circuit-id", hw);
    ctx.leave();
}
#line 3106 "dhcp4_parser.cc"
    break;

  case 559:
#line 1876 "dhcp4_parser.yy"
                       {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3114 "dhcp4_parser.cc"
    break;

  case 560:
#line 1878 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 3124 "dhcp4_parser.cc"
    break;

  case 561:
#line 1884 "dhcp4_parser.yy"
                   {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3132 "dhcp4_parser.cc"
    break;

  case 562:
#line 1886 "dhcp4_parser.yy"
               {
    ElementPtr host(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 3142 "dhcp4_parser.cc"
    break;

  case 563:
#line 1892 "dhcp4_parser.yy"
                                           {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3153 "dhcp4_parser.cc"
    break;

  case 564:
#line 1897 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3162 "dhcp4_parser.cc"
    break;

  case 565:
#line 1905 "dhcp4_parser.yy"
             {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 3173 "dhcp4_parser.cc"
    break;

  case 566:
#line 1910 "dhcp4_parser.yy"
                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3182 "dhcp4_parser.cc"
    break;

  case 569:
#line 1922 "dhcp4_parser.yy"
                               {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 3193 "dhcp4_parser.cc"
    break;

  case 570:
#line 1927 "dhcp4_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3202 "dhcp4_parser.cc"
    break;

  case 573:
#line 1936 "dhcp4_parser.yy"
                                   {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3212 "dhcp4_parser.cc"
    break;

  case 574:
#line 1940 "dhcp4_parser.yy"
                                     {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3222 "dhcp4_parser.cc"
    break;

  case 591:
#line 1969 "dhcp4_parser.yy"
                        {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3230 "dhcp4_parser.cc"
    break;

  case 592:
#line 1971 "dhcp4_parser.yy"
               {
    ElementPtr test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 3240 "dhcp4_parser.cc"
    break;

  case 593:
#line 1977 "dhcp4_parser.yy"
                                                 {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 3249 "dhcp4_parser.cc"
    break;

  case 594:
#line 1986 "dhcp4_parser.yy"
                                         {
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 3258 "dhcp4_parser.cc"
    break;

  case 595:
#line 1993 "dhcp4_parser.yy"
                               {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 3269 "dhcp4_parser.cc"
    break;

  case 596:
#line 1998 "dhcp4_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3278 "dhcp4_parser.cc"
    break;

  case 604:
#line 2014 "dhcp4_parser.yy"
                                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3286 "dhcp4_parser.cc"
    break;

  case 605:
#line 2016 "dhcp4_parser.yy"
               {
    ElementPtr stype(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 3296 "dhcp4_parser.cc"
    break;

  case 606:
#line 2022 "dhcp4_parser.yy"
                                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3304 "dhcp4_parser.cc"
    break;

  case 607:
#line 2024 "dhcp4_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 3314 "dhcp4_parser.cc"
    break;

  case 608:
#line 2033 "dhcp4_parser.yy"
                                       {
    ElementPtr qc(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-queue-control", qc);
    ctx.stack_.push_back(qc);
    ctx.enter(ctx.DHCP_QUEUE_CONTROL);
}
#line 3325 "dhcp4_parser.cc"
    break;

  case 609:
#line 2038 "dhcp4_parser.yy"
                                                           {
    // The enable queue parameter is required.
    ctx.require("enable-queue", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3336 "dhcp4_parser.cc"
    break;

  case 618:
#line 2057 "dhcp4_parser.yy"
                                         {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-queue", b);
}
#line 3345 "dhcp4_parser.cc"
    break;

  case 619:
#line 2062 "dhcp4_parser.yy"
                       {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3353 "dhcp4_parser.cc"
    break;

  case 620:
#line 2064 "dhcp4_parser.yy"
               {
    ElementPtr qt(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("queue-type", qt);
    ctx.leave();
}
#line 3363 "dhcp4_parser.cc"
    break;

  case 621:
#line 2070 "dhcp4_parser.yy"
                                 {
    ElementPtr c(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("capacity", c);
}
#line 3372 "dhcp4_parser.cc"
    break;

  case 622:
#line 2075 "dhcp4_parser.yy"
                            {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3380 "dhcp4_parser.cc"
    break;

  case 623:
#line 2077 "dhcp4_parser.yy"
              {
    ctx.stack_.back()->set(yystack_[3].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3389 "dhcp4_parser.cc"
    break;

  case 624:
#line 2084 "dhcp4_parser.yy"
                     {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 3400 "dhcp4_parser.cc"
    break;

  case 625:
#line 2089 "dhcp4_parser.yy"
                                                       {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3411 "dhcp4_parser.cc"
    break;

  case 626:
#line 2096 "dhcp4_parser.yy"
                              {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3421 "dhcp4_parser.cc"
    break;

  case 627:
#line 2100 "dhcp4_parser.yy"
                                  {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3431 "dhcp4_parser.cc"
    break;

  case 648:
#line 2130 "dhcp4_parser.yy"
                                             {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 3440 "dhcp4_parser.cc"
    break;

  case 649:
#line 2135 "dhcp4_parser.yy"
                     {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3448 "dhcp4_parser.cc"
    break;

  case 650:
#line 2137 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 3458 "dhcp4_parser.cc"
    break;

  case 651:
#line 2143 "dhcp4_parser.yy"
                                       {
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 3467 "dhcp4_parser.cc"
    break;

  case 652:
#line 2148 "dhcp4_parser.yy"
                     {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3475 "dhcp4_parser.cc"
    break;

  case 653:
#line 2150 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 3485 "dhcp4_parser.cc"
    break;

  case 654:
#line 2156 "dhcp4_parser.yy"
                                       {
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 3494 "dhcp4_parser.cc"
    break;

  case 655:
#line 2161 "dhcp4_parser.yy"
                                             {
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 3503 "dhcp4_parser.cc"
    break;

  case 656:
#line 2166 "dhcp4_parser.yy"
                           {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 3511 "dhcp4_parser.cc"
    break;

  case 657:
#line 2168 "dhcp4_parser.yy"
                           {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3520 "dhcp4_parser.cc"
    break;

  case 658:
#line 2174 "dhcp4_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 3526 "dhcp4_parser.cc"
    break;

  case 659:
#line 2175 "dhcp4_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 3532 "dhcp4_parser.cc"
    break;

  case 660:
#line 2178 "dhcp4_parser.yy"
                       {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 3540 "dhcp4_parser.cc"
    break;

  case 661:
#line 2180 "dhcp4_parser.yy"
             {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 3550 "dhcp4_parser.cc"
    break;

  case 662:
#line 2187 "dhcp4_parser.yy"
                                         {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3558 "dhcp4_parser.cc"
    break;

  case 663:
#line 2189 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 3568 "dhcp4_parser.cc"
    break;

  case 664:
#line 2196 "dhcp4_parser.yy"
                                                         {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 3577 "dhcp4_parser.cc"
    break;

  case 665:
#line 2202 "dhcp4_parser.yy"
                                                                 {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 3586 "dhcp4_parser.cc"
    break;

  case 666:
#line 2208 "dhcp4_parser.yy"
                                             {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 3594 "dhcp4_parser.cc"
    break;

  case 667:
#line 2210 "dhcp4_parser.yy"
                                       {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3603 "dhcp4_parser.cc"
    break;

  case 668:
#line 2216 "dhcp4_parser.yy"
                                       {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3611 "dhcp4_parser.cc"
    break;

  case 669:
#line 2218 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 3621 "dhcp4_parser.cc"
    break;

  case 670:
#line 2225 "dhcp4_parser.yy"
                                         {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3629 "dhcp4_parser.cc"
    break;

  case 671:
#line 2227 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 3639 "dhcp4_parser.cc"
    break;

  case 672:
#line 2234 "dhcp4_parser.yy"
                                                         {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3647 "dhcp4_parser.cc"
    break;

  case 673:
#line 2236 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 3657 "dhcp4_parser.cc"
    break;

  case 674:
#line 2245 "dhcp4_parser.yy"
                         {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3665 "dhcp4_parser.cc"
    break;

  case 675:
#line 2247 "dhcp4_parser.yy"
              {
    ctx.stack_.back()->set("Dhcp6", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3674 "dhcp4_parser.cc"
    break;

  case 676:
#line 2252 "dhcp4_parser.yy"
                               {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3682 "dhcp4_parser.cc"
    break;

  case 677:
#line 2254 "dhcp4_parser.yy"
              {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3691 "dhcp4_parser.cc"
    break;

  case 678:
#line 2259 "dhcp4_parser.yy"
                                         {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3699 "dhcp4_parser.cc"
    break;

  case 679:
#line 2261 "dhcp4_parser.yy"
              {
    ctx.stack_.back()->set("Control-agent", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3708 "dhcp4_parser.cc"
    break;

  case 680:
#line 2266 "dhcp4_parser.yy"
                               {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 3719 "dhcp4_parser.cc"
    break;

  case 681:
#line 2271 "dhcp4_parser.yy"
                                                            {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3729 "dhcp4_parser.cc"
    break;

  case 682:
#line 2277 "dhcp4_parser.yy"
                                   {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3739 "dhcp4_parser.cc"
    break;

  case 683:
#line 2281 "dhcp4_parser.yy"
                                       {
    // No config_control params are required
    // parsing completed
}
#line 3748 "dhcp4_parser.cc"
    break;

  case 688:
#line 2296 "dhcp4_parser.yy"
                                   {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 3759 "dhcp4_parser.cc"
    break;

  case 689:
#line 2301 "dhcp4_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3768 "dhcp4_parser.cc"
    break;

  case 690:
#line 2306 "dhcp4_parser.yy"
                                                             {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-fetch-wait-time", value);
}
#line 3777 "dhcp4_parser.cc"
    break;

  case 691:
#line 2316 "dhcp4_parser.yy"
                        {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 3788 "dhcp4_parser.cc"
    break;

  case 692:
#line 2321 "dhcp4_parser.yy"
                                                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3797 "dhcp4_parser.cc"
    break;

  case 693:
#line 2326 "dhcp4_parser.yy"
                            {
    // Parse the Logging map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3807 "dhcp4_parser.cc"
    break;

  case 694:
#line 2330 "dhcp4_parser.yy"
                                {
    // parsing completed
}
#line 3815 "dhcp4_parser.cc"
    break;

  case 698:
#line 2346 "dhcp4_parser.yy"
                 {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 3826 "dhcp4_parser.cc"
    break;

  case 699:
#line 2351 "dhcp4_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3835 "dhcp4_parser.cc"
    break;

  case 702:
#line 2363 "dhcp4_parser.yy"
                             {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 3845 "dhcp4_parser.cc"
    break;

  case 703:
#line 2367 "dhcp4_parser.yy"
                               {
    ctx.stack_.pop_back();
}
#line 3853 "dhcp4_parser.cc"
    break;

  case 713:
#line 2384 "dhcp4_parser.yy"
                                     {
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 3862 "dhcp4_parser.cc"
    break;

  case 714:
#line 2389 "dhcp4_parser.yy"
                   {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3870 "dhcp4_parser.cc"
    break;

  case 715:
#line 2391 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 3880 "dhcp4_parser.cc"
    break;

  case 716:
#line 2397 "dhcp4_parser.yy"
                                    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 3891 "dhcp4_parser.cc"
    break;

  case 717:
#line 2402 "dhcp4_parser.yy"
                                                                    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3900 "dhcp4_parser.cc"
    break;

  case 720:
#line 2411 "dhcp4_parser.yy"
                             {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3910 "dhcp4_parser.cc"
    break;

  case 721:
#line 2415 "dhcp4_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 3918 "dhcp4_parser.cc"
    break;

  case 729:
#line 2430 "dhcp4_parser.yy"
               {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3926 "dhcp4_parser.cc"
    break;

  case 730:
#line 2432 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 3936 "dhcp4_parser.cc"
    break;

  case 731:
#line 2438 "dhcp4_parser.yy"
                           {
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 3945 "dhcp4_parser.cc"
    break;

  case 732:
#line 2443 "dhcp4_parser.yy"
                               {
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 3954 "dhcp4_parser.cc"
    break;

  case 733:
#line 2448 "dhcp4_parser.yy"
                             {
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 3963 "dhcp4_parser.cc"
    break;

  case 734:
#line 2453 "dhcp4_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3971 "dhcp4_parser.cc"
    break;

  case 735:
#line 2455 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pattern", sev);
    ctx.leave();
}
#line 3981 "dhcp4_parser.cc"
    break;


#line 3985 "dhcp4_parser.cc"

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


  const short Dhcp4Parser::yypact_ninf_ = -905;

  const signed char Dhcp4Parser::yytable_ninf_ = -1;

  const short
  Dhcp4Parser::yypact_[] =
  {
     390,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,
    -905,  -905,  -905,  -905,  -905,    46,    27,    28,    71,    79,
      81,    83,    95,   105,   121,   131,   139,   141,   159,   176,
    -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,
    -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,
    -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,
    -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,    27,  -148,
      20,   168,    25,   584,    -9,    21,   -36,    67,   198,   -14,
     403,  -103,   211,  -905,   114,    58,   164,   184,   204,  -905,
    -905,  -905,  -905,  -905,   212,  -905,    40,  -905,  -905,  -905,
    -905,  -905,  -905,  -905,  -905,  -905,   262,   269,   271,  -905,
    -905,  -905,  -905,  -905,  -905,   273,   301,   316,   346,   347,
     348,   370,   371,   372,  -905,   373,   374,   375,  -905,  -905,
    -905,   376,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,
    -905,  -905,  -905,  -905,   377,  -905,  -905,  -905,  -905,  -905,
    -905,  -905,    66,  -905,  -905,  -905,  -905,  -905,  -905,  -905,
    -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,
    -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,
    -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,
    -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,
    -905,  -905,  -905,  -905,  -905,   378,  -905,    68,  -905,  -905,
    -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,
    -905,   380,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,
    -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,
    -905,  -905,  -905,  -905,  -905,   133,  -905,  -905,  -905,  -905,
    -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,
    -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,
     137,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,
    -905,  -905,  -905,  -905,  -905,  -905,  -905,   243,   292,  -905,
    -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,
    -905,   322,  -905,  -905,   382,  -905,  -905,  -905,   383,  -905,
    -905,   381,   385,  -905,  -905,  -905,  -905,  -905,  -905,  -905,
    -905,  -905,  -905,  -905,  -905,  -905,   386,   388,  -905,  -905,
    -905,  -905,   389,   391,  -905,  -905,  -905,  -905,  -905,  -905,
    -905,  -905,  -905,  -905,  -905,  -905,   155,  -905,  -905,  -905,
     392,  -905,  -905,   394,  -905,   395,   396,  -905,  -905,   397,
     398,  -905,  -905,  -905,  -905,  -905,  -905,  -905,   240,  -905,
    -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,
    -905,  -905,  -905,  -905,  -905,   242,  -905,  -905,  -905,   401,
     250,  -905,  -905,  -905,  -905,    27,    27,  -905,   208,   404,
     405,   406,   408,   409,  -905,    20,  -905,   410,   411,   414,
     219,   232,   233,   418,   419,   420,   421,   424,   427,   248,
     249,   251,   253,   257,   254,   261,   263,   258,   442,   272,
     274,   276,   443,   447,   450,   280,   451,   453,   455,   457,
     466,   467,   470,   471,   472,   474,   477,   479,   300,   480,
     484,   486,   488,   490,   494,   168,  -905,   497,   501,   502,
     331,    25,  -905,   513,   514,   516,   520,   524,   525,   344,
     528,   529,   530,   584,  -905,   531,    -9,  -905,   532,   533,
     534,   535,   549,   550,   551,   552,  -905,    21,  -905,   553,
     554,   393,   571,   572,   574,   402,  -905,    67,   576,   407,
     413,  -905,   198,   578,   579,    61,  -905,   415,   580,   581,
     400,   585,   412,   416,   587,   588,   428,   429,   589,   590,
     592,   593,   403,  -905,  -103,  -905,   595,   422,   211,  -905,
    -905,  -905,   600,   599,   602,    27,    27,    27,  -905,   608,
     611,   612,  -905,  -905,  -905,   435,   437,   439,   618,   619,
     623,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,
     444,  -905,  -905,  -905,    32,   445,   446,  -905,   627,   628,
     633,   634,   642,   465,   247,   635,   653,   657,   659,   658,
    -905,   660,   661,   662,   481,   485,   670,  -905,   682,   267,
     288,  -905,  -905,   504,   505,   508,   689,   510,   511,  -905,
     682,   512,   691,  -905,   515,  -905,   682,   517,   518,   519,
     521,   522,   523,   526,  -905,   527,   536,  -905,   537,   546,
     547,  -905,  -905,   548,  -905,  -905,  -905,   557,    27,  -905,
    -905,   558,   559,  -905,   560,  -905,  -905,    15,   456,  -905,
    -905,    32,   561,   562,   565,  -905,  -905,   696,  -905,  -905,
      27,   168,  -103,  -905,  -905,  -905,   211,    25,   681,  -905,
    -905,  -905,   315,   315,   702,  -905,  -905,  -905,  -905,  -905,
    -905,  -905,  -905,  -905,   703,   727,   730,   731,  -905,  -905,
    -905,  -905,  -905,  -905,  -905,  -905,    63,   732,   745,   747,
     189,   125,    69,   403,  -905,  -905,   748,  -905,  -905,  -905,
    -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,   749,  -905,
    -905,  -905,  -905,   202,  -905,  -905,  -905,  -905,  -905,  -905,
    -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,
    -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,
    -905,  -905,   702,  -905,   256,   259,   260,   266,  -905,   284,
    -905,  -905,  -905,  -905,  -905,  -905,   753,   754,   755,   757,
     758,  -905,  -905,  -905,  -905,   760,   761,   762,   763,   764,
     766,  -905,   285,  -905,  -905,  -905,  -905,  -905,  -905,  -905,
    -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,
    -905,  -905,  -905,  -905,   291,  -905,   767,   769,  -905,  -905,
     768,   772,  -905,  -905,   770,   774,  -905,  -905,   773,   775,
    -905,  -905,   776,   777,  -905,  -905,  -905,  -905,  -905,  -905,
      74,  -905,  -905,  -905,  -905,  -905,  -905,  -905,    93,  -905,
    -905,   778,   780,  -905,  -905,   779,   783,  -905,   784,   785,
     786,   787,   788,   789,   295,  -905,  -905,  -905,  -905,  -905,
    -905,  -905,  -905,  -905,  -905,  -905,  -905,   298,  -905,  -905,
    -905,   790,  -905,   791,  -905,  -905,  -905,   299,  -905,  -905,
    -905,  -905,  -905,   314,  -905,   113,  -905,   596,  -905,   781,
     793,  -905,  -905,  -905,  -905,   792,   795,  -905,  -905,  -905,
    -905,   794,   681,  -905,   798,   799,   800,   801,   613,   609,
     620,   621,   622,   803,   806,   807,   810,   629,   630,   631,
     632,   636,   637,   315,  -905,  -905,   315,  -905,   702,   584,
    -905,   703,    67,  -905,   727,   198,  -905,   730,   656,  -905,
     731,    63,  -905,    64,   732,  -905,    21,  -905,   745,   -14,
    -905,   747,   639,   640,   641,   643,   644,   645,   189,  -905,
     815,   816,   125,  -905,   646,   817,   647,   818,    69,  -905,
    -905,    59,   748,  -905,  -905,   822,   829,    -9,  -905,   749,
     831,  -905,  -905,   651,  -905,   305,   652,   654,   655,  -905,
    -905,  -905,  -905,  -905,   663,   665,   666,   668,  -905,  -905,
    -905,  -905,  -905,  -905,  -905,   318,  -905,   320,  -905,   830,
    -905,   834,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,
    -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,
    -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,   326,
    -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,
    -905,   839,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,
    -905,   836,   842,  -905,  -905,  -905,  -905,  -905,   838,  -905,
     328,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,   669,
     671,  -905,  -905,   675,  -905,    27,  -905,  -905,   843,  -905,
    -905,  -905,  -905,  -905,   329,  -905,  -905,  -905,  -905,  -905,
    -905,   679,   330,  -905,   682,  -905,  -905,  -905,  -905,  -905,
    -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,
    -905,  -905,   656,  -905,   863,   685,  -905,    64,  -905,  -905,
    -905,  -905,  -905,  -905,   870,   692,   873,    59,  -905,  -905,
    -905,  -905,  -905,   695,  -905,  -905,   882,  -905,   705,  -905,
    -905,   881,  -905,  -905,   161,  -905,  -102,   881,  -905,  -905,
     888,   889,   892,  -905,   336,  -905,  -905,  -905,  -905,  -905,
    -905,  -905,   894,   712,   717,   720,   903,  -102,  -905,   724,
    -905,  -905,  -905,   726,  -905,  -905,  -905
  };

  const short
  Dhcp4Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,    28,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       1,    45,    38,    34,    33,    30,    31,    32,    37,     3,
      35,    36,    58,     5,    70,     7,   167,     9,   312,    11,
     495,    13,   520,    15,   420,    17,   428,    19,   465,    21,
     277,    23,   626,    25,   693,    27,   682,    29,    47,    41,
       0,     0,     0,     0,     0,   522,     0,   430,   467,     0,
       0,     0,     0,    49,     0,    48,     0,     0,    42,    68,
     691,   674,   676,   678,     0,    67,     0,    60,    62,    64,
      65,    66,    63,   680,   156,   182,     0,     0,     0,   541,
     543,   545,   180,   189,   191,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   132,     0,     0,     0,   140,   147,
     149,     0,   304,   418,   457,   375,   508,   510,   368,   255,
     569,   512,   269,   288,     0,   595,   608,   624,   151,   153,
     698,   122,     0,    72,    74,    75,    76,    77,    78,   109,
     110,   111,    79,   107,    96,    97,    98,   115,   116,   117,
     118,   119,   120,   113,   114,   121,    82,    83,   104,    84,
      85,    86,    90,    91,    80,   108,    81,    88,    89,   102,
     103,   105,    99,   100,   101,    87,    92,    93,    94,    95,
     106,   112,   169,   171,   175,     0,   166,     0,   158,   160,
     161,   162,   163,   164,   165,   356,   358,   360,   487,   354,
     362,     0,   366,   364,   565,   353,   316,   317,   318,   319,
     320,   341,   342,   343,   331,   332,   344,   345,   346,   347,
     348,   349,   350,   351,   352,     0,   314,   323,   336,   337,
     338,   324,   326,   327,   329,   325,   321,   322,   339,   340,
     328,   333,   334,   335,   330,   506,   505,   501,   502,   500,
       0,   497,   499,   503,   504,   563,   551,   553,   557,   555,
     561,   559,   547,   540,   534,   538,   539,     0,   523,   524,
     535,   536,   537,   531,   526,   532,   528,   529,   530,   533,
     527,     0,   447,   235,     0,   451,   449,   454,     0,   443,
     444,     0,   431,   432,   434,   446,   435,   436,   437,   453,
     438,   439,   440,   441,   442,   481,     0,     0,   479,   480,
     483,   484,     0,   468,   469,   471,   472,   473,   474,   475,
     476,   477,   478,   284,   286,   281,     0,   279,   282,   283,
       0,   662,   649,     0,   652,     0,     0,   656,   660,     0,
       0,   666,   668,   670,   672,   647,   645,   646,     0,   628,
     630,   631,   632,   633,   634,   635,   636,   637,   642,   638,
     639,   640,   641,   643,   644,     0,   695,   697,   688,     0,
       0,   684,   686,   687,    46,     0,     0,    39,     0,     0,
       0,     0,     0,     0,    57,     0,    59,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    71,     0,     0,     0,
       0,     0,   168,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   313,     0,     0,   496,     0,     0,
       0,     0,     0,     0,     0,     0,   521,     0,   421,     0,
       0,     0,     0,     0,     0,     0,   429,     0,     0,     0,
       0,   466,     0,     0,     0,     0,   278,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   627,     0,   694,     0,     0,     0,   683,
      50,    43,     0,     0,     0,     0,     0,     0,    61,     0,
       0,     0,   134,   135,   136,     0,     0,     0,     0,     0,
       0,   123,   124,   125,   126,   127,   128,   129,   130,   131,
       0,   137,   138,   139,     0,     0,     0,   155,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     594,     0,     0,     0,     0,     0,     0,    73,     0,     0,
       0,   179,   159,     0,     0,     0,     0,     0,     0,   374,
       0,     0,     0,   315,     0,   498,     0,     0,     0,     0,
       0,     0,     0,     0,   525,     0,     0,   445,     0,     0,
       0,   456,   433,     0,   485,   486,   470,     0,     0,   280,
     648,     0,     0,   651,     0,   654,   655,     0,     0,   664,
     665,     0,     0,     0,     0,   629,   696,     0,   690,   685,
       0,     0,     0,   675,   677,   679,     0,     0,     0,   542,
     544,   546,     0,     0,   193,   133,   142,   143,   144,   145,
     146,   141,   148,   150,   306,   422,   459,   377,    40,   509,
     511,   370,   371,   372,   373,   369,     0,     0,   514,   271,
       0,     0,     0,     0,   152,   154,     0,    51,   170,   173,
     174,   172,   177,   178,   176,   357,   359,   361,   489,   355,
     363,   367,   365,     0,   507,   564,   552,   554,   558,   556,
     562,   560,   548,   448,   236,   452,   450,   455,   482,   285,
     287,   663,   650,   653,   658,   659,   657,   661,   667,   669,
     671,   673,   193,    44,     0,     0,     0,     0,   187,     0,
     184,   186,   222,   228,   230,   232,     0,     0,     0,     0,
       0,   244,   246,   248,   250,     0,     0,     0,     0,     0,
       0,   221,     0,   199,   201,   202,   203,   204,   205,   206,
     207,   208,   209,   210,   214,   215,   216,   211,   217,   218,
     219,   212,   213,   220,     0,   197,     0,   194,   195,   310,
       0,   307,   308,   426,     0,   423,   424,   463,     0,   460,
     461,   381,     0,   378,   379,   264,   265,   266,   267,   268,
       0,   257,   259,   260,   261,   262,   263,   573,     0,   571,
     518,     0,   515,   516,   275,     0,   272,   273,     0,     0,
       0,     0,     0,     0,     0,   290,   292,   293,   294,   295,
     296,   297,   604,   606,   603,   601,   602,     0,   597,   599,
     600,     0,   619,     0,   622,   615,   616,     0,   610,   612,
     613,   614,   617,     0,   702,     0,   700,    53,   493,     0,
     490,   491,   549,   567,   568,     0,     0,    69,   692,   681,
     157,     0,     0,   183,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   181,   190,     0,   192,     0,     0,
     305,     0,   430,   419,     0,   467,   458,     0,     0,   376,
       0,     0,   256,   575,     0,   570,   522,   513,     0,     0,
     270,     0,     0,     0,     0,     0,     0,     0,     0,   289,
       0,     0,     0,   596,     0,     0,     0,     0,     0,   609,
     625,     0,     0,   699,    55,     0,    54,     0,   488,     0,
       0,   566,   689,     0,   185,     0,     0,     0,     0,   234,
     237,   238,   239,   240,     0,     0,     0,     0,   252,   253,
     241,   242,   243,   254,   200,     0,   196,     0,   309,     0,
     425,     0,   462,   417,   400,   401,   402,   388,   389,   405,
     406,   407,   391,   392,   408,   409,   410,   411,   412,   413,
     414,   415,   416,   385,   386,   387,   398,   399,   397,     0,
     383,   390,   403,   404,   393,   394,   395,   396,   380,   258,
     591,     0,   589,   590,   582,   583,   587,   588,   584,   585,
     586,     0,   576,   577,   579,   580,   581,   572,     0,   517,
       0,   274,   298,   299,   300,   301,   302,   303,   291,     0,
       0,   598,   618,     0,   621,     0,   611,   716,     0,   714,
     712,   706,   710,   711,     0,   704,   708,   709,   707,   701,
      52,     0,     0,   492,     0,   188,   224,   225,   226,   227,
     223,   229,   231,   233,   245,   247,   249,   251,   198,   311,
     427,   464,     0,   382,     0,     0,   574,     0,   519,   276,
     605,   607,   620,   623,     0,     0,     0,     0,   703,    56,
     494,   550,   384,     0,   593,   578,     0,   713,     0,   705,
     592,     0,   715,   720,     0,   718,     0,     0,   717,   729,
       0,     0,     0,   734,     0,   722,   724,   725,   726,   727,
     728,   719,     0,     0,     0,     0,     0,     0,   721,     0,
     731,   732,   733,     0,   723,   730,   735
  };

  const short
  Dhcp4Parser::yypgoto_[] =
  {
    -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,
    -905,  -905,  -905,  -905,  -905,  -905,   -23,  -905,   342,  -905,
    -905,  -905,  -905,  -905,  -905,  -905,  -905,  -578,  -905,  -905,
    -905,   -70,  -905,  -905,  -905,   569,  -905,  -905,  -905,  -905,
     264,   462,   -47,   -44,    -1,    16,    18,    24,    30,    31,
    -905,  -905,  -905,  -905,    34,    35,    36,    37,    38,    42,
    -905,   279,    48,  -905,    49,  -905,    50,  -905,    52,  -905,
      53,  -905,  -905,   294,   469,  -905,  -905,  -905,  -905,  -905,
    -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,
    -905,    87,  -905,  -905,  -905,  -905,  -905,  -905,   181,  -905,
      57,  -905,  -644,    72,  -905,  -905,  -905,  -905,  -905,  -905,
    -905,  -905,  -905,  -905,   -39,  -905,  -905,  -905,  -905,  -905,
    -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,
    -905,  -905,  -905,  -905,  -905,  -905,  -905,    56,  -905,  -905,
    -905,  -905,  -905,  -905,  -905,  -905,  -905,    43,  -905,  -905,
    -905,    47,   483,  -905,  -905,  -905,  -905,  -905,  -905,  -905,
      41,  -905,  -905,  -905,  -905,  -905,  -905,  -904,  -905,  -905,
    -905,    70,  -905,  -905,  -905,    73,   538,  -905,  -905,  -905,
    -905,  -905,  -905,  -905,  -905,  -903,  -905,   -43,  -905,    55,
    -905,    54,  -905,  -905,  -905,  -905,  -905,  -905,  -905,    60,
    -905,  -905,  -119,   -63,  -905,  -905,  -905,  -905,  -905,    75,
    -905,  -905,  -905,    76,  -905,   498,  -905,   -66,  -905,  -905,
    -905,  -905,  -905,   -64,  -905,  -905,  -905,  -905,  -905,    -7,
    -905,  -905,  -905,    77,  -905,  -905,  -905,    78,  -905,   492,
    -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,
    -905,    33,  -905,  -905,  -905,    29,   539,  -905,  -905,   -57,
    -905,   -20,  -905,   -62,  -905,  -905,  -905,    62,  -905,  -905,
    -905,    65,  -905,   540,     0,  -905,     6,  -905,    12,  -905,
     293,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,
    -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -901,  -905,
    -905,  -905,  -905,  -905,    80,  -905,  -905,  -905,  -120,  -905,
    -905,  -905,  -905,  -905,  -905,  -905,  -905,    82,  -905,  -905,
    -905,  -905,  -905,  -905,  -905,    51,  -905,  -905,  -905,  -905,
    -905,  -905,  -905,  -905,  -905,  -905,   312,   491,  -905,  -905,
    -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,
    -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,
    -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,  -905,
    -905,  -905,  -905,   351,   482,  -905,  -905,  -905,  -905,  -905,
    -905,  -905,   356,   493,   -75,  -905,  -905,    84,  -905,  -905,
    -115,  -905,  -905,  -905,  -905,  -905,  -905,  -131,  -905,  -905,
    -149,  -905,  -905,  -905,  -905,  -905,  -905,  -905
  };

  const short
  Dhcp4Parser::yydefgoto_[] =
  {
      -1,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    38,    39,    40,    69,
     679,    87,    88,    41,    68,    84,    85,   698,   877,   965,
     966,   771,    43,    70,    96,    97,    98,   399,    45,    71,
     152,   153,   154,   155,   156,   157,   158,   159,   160,   161,
     162,   163,   428,   164,   165,   166,   167,   168,   169,   170,
     432,   671,   171,   433,   172,   434,   173,   452,   174,   453,
     175,   176,   408,   207,   208,    47,    72,   209,   457,   210,
     458,   701,   211,   459,   704,   212,   177,   416,   178,   409,
     749,   750,   751,   891,   179,   417,   180,   418,   796,   797,
     798,   916,   772,   773,   774,   894,  1100,   775,   895,   776,
     896,   777,   897,   778,   779,   490,   780,   781,   782,   783,
     784,   785,   786,   787,   903,   788,   904,   789,   905,   790,
     906,   791,   792,   793,   181,   443,   820,   821,   822,   823,
     824,   825,   826,   182,   446,   835,   836,   837,   939,    61,
      79,   346,   347,   348,   503,   349,   504,   183,   447,   844,
     845,   846,   847,   848,   849,   850,   851,   184,   436,   800,
     801,   802,   919,    49,    73,   245,   246,   247,   467,   248,
     463,   249,   464,   250,   465,   251,   468,   252,   471,   253,
     470,   185,   442,   685,   255,   186,   439,   812,   813,   814,
     928,  1029,  1030,   187,   437,    55,    76,   804,   805,   806,
     922,    57,    77,   311,   312,   313,   314,   315,   316,   317,
     489,   318,   493,   319,   492,   320,   321,   494,   322,   188,
     438,   808,   809,   810,   925,    59,    78,   332,   333,   334,
     335,   336,   498,   337,   338,   339,   340,   257,   466,   879,
     880,   881,   967,    51,    74,   270,   271,   272,   475,   189,
     440,   190,   441,   191,   445,   831,   832,   833,   936,    53,
      75,   287,   288,   289,   192,   413,   193,   414,   194,   415,
     293,   485,   884,   970,   294,   479,   295,   480,   296,   482,
     297,   481,   298,   484,   299,   483,   300,   478,   264,   472,
     885,   195,   444,   828,   829,   933,  1051,  1052,  1053,  1054,
    1055,  1114,  1056,   196,   197,   449,   857,   858,   859,   950,
     860,   951,   198,   450,   867,   868,   869,   870,   955,   871,
     872,   957,   199,   451,    63,    80,   368,   369,   370,   371,
     509,   372,   373,   511,   374,   375,   376,   514,   736,   377,
     515,   378,   508,   379,   380,   381,   518,   382,   519,   383,
     520,   384,   521,    99,   401,   100,   402,   101,   403,   200,
     407,    67,    82,   390,   391,   392,   526,   393,   102,   400,
      65,    81,   385,   386,   201,   454,   875,   876,   961,  1084,
    1085,  1086,  1087,  1126,  1088,  1124,  1144,  1145,  1146,  1154,
    1155,  1156,  1162,  1157,  1158,  1159,  1160,  1166
  };

  const short
  Dhcp4Parser::yytable_[] =
  {
      95,   151,   206,   225,   266,   283,   387,   309,   328,   345,
     365,   260,   330,   301,   331,   213,   258,   273,   285,   794,
     323,   341,   711,   366,  1024,  1025,   226,  1037,   715,   227,
      89,   267,    31,   734,    32,    42,    33,    86,   310,   329,
     202,   203,   133,   405,   204,    83,    30,   205,   406,   109,
     110,   111,   214,   259,   274,   286,   150,   324,   342,  1149,
     367,   395,  1150,  1151,  1152,  1153,   256,   269,   284,   455,
     134,   461,   228,   261,   456,   290,   462,   931,    44,   262,
     932,   291,   265,   136,   137,   263,    46,   292,    48,   229,
      50,   230,   109,   110,   111,   222,   934,   231,   223,   935,
     134,   302,    52,   232,   233,   343,   344,   234,   235,   236,
     237,   238,    54,   136,   137,   239,   962,   136,   137,   963,
     394,   240,   241,   242,   275,   243,   244,   254,    56,   268,
     276,   277,   278,   279,   280,   281,   473,   282,    58,   303,
     476,   474,   133,   134,   303,   477,    60,   303,    62,   304,
     305,   136,   137,   306,   307,   308,   136,   137,   505,   136,
     137,   136,   137,   506,  1147,   735,    64,  1148,   396,  1040,
    1041,    94,   815,   816,   817,   818,    94,   819,    90,   103,
     343,   344,   104,    66,   666,   667,   668,   669,    91,    92,
      93,   105,   397,   106,   107,   108,   109,   110,   111,   112,
     113,   114,   861,   862,   863,    94,    94,   398,  1024,  1025,
      94,  1037,    34,    35,    36,    37,   404,   136,   137,  1077,
     670,  1078,  1079,   388,   389,   115,   116,   117,   118,   119,
     120,   121,   122,   123,   124,   125,   126,   127,   128,   129,
     130,   131,   132,   522,    94,   524,   133,   134,   523,    94,
     525,   486,    94,   528,   864,   852,   853,   135,   529,   455,
     136,   137,   524,   528,   887,   138,   410,   888,   889,   461,
     139,   140,   995,   411,   890,   412,   141,   419,   303,   325,
     304,   305,   326,   327,   699,   700,   142,   892,   913,   143,
     136,   137,   893,   914,   913,   487,   144,   145,   948,   915,
     146,   952,   958,   949,   147,   420,   953,   959,   702,   703,
      94,   838,   839,   840,   841,   842,   843,   522,   282,   882,
     421,   913,   960,   473,   148,   149,  1108,   150,  1109,  1112,
     488,   505,  1127,   476,  1113,    95,  1119,  1128,  1130,  1167,
    1096,  1097,  1098,  1099,  1168,   681,   682,   683,   684,   752,
     422,   423,   424,    94,   753,   754,   755,   756,   757,   758,
     759,   760,   761,   762,   763,   764,   765,   766,   767,   768,
     769,   770,   530,   531,   425,   426,   427,   429,   430,   431,
     435,   448,   460,    94,   469,   151,   491,   495,   497,   496,
     499,   206,   500,   532,   502,   303,   507,   501,   510,   512,
     513,   516,   517,   225,   213,   527,   266,   542,   533,   534,
     535,   260,   536,   537,   539,   540,   258,   283,   541,   273,
     543,   544,   545,   546,   547,   548,   226,   309,   549,   227,
     285,   550,   328,   267,   551,   552,   330,   553,   331,   554,
     323,   214,   556,   555,   559,   341,   560,   564,   557,   387,
     558,   565,   365,   259,   566,   568,   274,   569,   310,   570,
     561,   571,   562,   329,   563,   366,   256,   286,   567,   269,
     572,   573,   228,   261,   574,   575,   576,   324,   577,   262,
     284,   578,   342,   579,   581,   263,   580,   290,   582,   229,
     583,   230,   584,   291,   585,   136,   137,   231,   586,   292,
      94,   588,   367,   232,   233,   589,   590,   234,   235,   236,
     237,   238,   653,   654,   655,   239,  1131,   593,   594,   591,
     595,   240,   241,   242,   596,   243,   244,   254,   597,   598,
     599,   268,   600,   601,   602,   604,   606,   607,   608,   609,
     350,   351,   352,   353,   354,   355,   356,   357,   358,   359,
     360,   361,   362,   610,   611,   612,   613,   615,   616,   363,
     364,     1,     2,     3,     4,     5,     6,     7,     8,     9,
      10,    11,    12,    13,    14,   618,   619,   387,   620,   617,
     623,   151,   627,   628,   631,   632,   633,   206,    94,   634,
     621,   637,   638,   641,   642,   624,   643,   644,   635,   647,
     213,   625,   636,   630,   650,   730,   651,   737,   648,   652,
     107,   108,   109,   110,   111,   656,   639,   640,   657,   658,
     659,   854,   660,   365,   661,   662,   663,   743,   664,   665,
     672,   673,   674,   675,   855,   865,   366,   214,   676,   677,
     686,   115,   116,   117,   118,   119,   120,   121,   122,    32,
     680,   125,   126,   127,   128,   129,   130,   131,   687,   215,
     216,   217,   688,   134,   689,   690,   694,   691,   692,   693,
     695,   856,   866,   367,   218,   696,   136,   137,   219,   220,
     221,   138,   107,   108,   109,   110,   111,   697,   222,   705,
     706,   223,   141,   707,   708,   709,   710,   712,   713,   224,
     714,   742,   716,   717,   718,   748,   719,   720,   721,   795,
     799,   722,   723,   115,   116,   117,   118,   119,   120,   121,
     122,   724,   725,   125,   126,   127,   128,   129,   130,   131,
     132,   726,   727,   728,   803,   134,   303,   807,   811,   827,
     148,   149,   729,   731,   732,   733,   739,   740,   136,   137,
     741,   220,   830,   138,   834,   874,   878,   898,   899,   900,
     222,   901,   902,   223,   907,   908,   909,   910,   911,    94,
     912,   224,   918,   917,   920,   921,   923,   924,   927,   926,
     930,   964,   929,   938,   937,   940,   941,   968,   942,   943,
     944,   945,   946,   947,   954,   956,   969,   980,   973,   979,
     971,   972,   975,   976,   977,   978,   981,   984,   983,   982,
     985,   986,   148,   149,   987,   988,   989,   990,   991,  1069,
    1070,  1073,  1075,   993,   992,  1062,  1063,  1064,  1090,  1065,
    1066,  1067,  1091,  1074,  1072,  1094,  1095,  1101,  1110,  1102,
    1103,    94,  1111,  1115,  1116,  1117,  1118,  1125,  1104,   225,
    1105,  1106,   309,  1107,  1120,   328,  1121,   260,  1003,   330,
    1122,   331,   258,  1042,  1129,   323,   283,  1133,   341,   345,
    1044,  1032,   226,  1134,  1136,   227,  1046,  1138,  1137,   285,
    1140,  1004,   854,   310,  1005,  1026,   329,  1141,  1143,  1023,
    1142,  1080,  1163,  1164,  1043,   855,  1165,   266,  1169,   259,
    1170,   865,   324,  1171,  1082,   342,  1172,  1173,  1033,  1175,
     273,  1176,   256,  1047,   678,   744,   286,   587,   228,   261,
     738,  1031,  1081,   886,   267,   262,  1045,  1006,  1034,   284,
     592,   263,   856,  1048,  1035,   229,   290,   230,   866,  1049,
    1036,  1083,   291,   231,  1007,  1050,  1008,   274,   292,   232,
     233,   747,  1009,   234,   235,   236,   237,   238,  1010,  1011,
     269,   239,  1012,  1013,  1014,  1015,  1016,   240,   241,   242,
    1017,   243,   244,   254,   538,   996,  1018,  1019,  1020,   974,
    1021,  1022,  1028,  1027,  1061,   994,  1060,  1039,   629,  1068,
    1038,   998,   997,  1132,   626,   622,  1092,  1135,   999,  1000,
    1059,  1058,  1093,  1001,  1002,   873,   883,   746,   745,  1076,
     649,   603,  1139,   645,  1057,   605,  1161,   646,  1174,     0,
       0,     0,   268,     0,     0,     0,     0,   614,     0,     0,
       0,     0,     0,     0,  1071,     0,     0,     0,     0,     0,
       0,     0,  1003,     0,     0,     0,  1089,  1042,     0,     0,
       0,     0,  1123,     0,  1044,  1032,     0,  1080,     0,     0,
    1046,     0,     0,     0,     0,  1004,     0,     0,  1005,  1026,
    1082,     0,     0,  1023,     0,     0,     0,     0,  1043,     0,
       0,     0,     0,     0,     0,     0,     0,     0,  1081,     0,
       0,     0,  1033,     0,     0,     0,     0,  1047,     0,     0,
       0,     0,     0,     0,     0,  1031,     0,  1083,     0,     0,
    1045,  1006,  1034,     0,     0,     0,     0,  1048,  1035,     0,
       0,     0,     0,  1049,  1036,     0,     0,     0,  1007,  1050,
    1008,     0,     0,     0,     0,     0,  1009,     0,     0,     0,
       0,     0,  1010,  1011,     0,     0,  1012,  1013,  1014,  1015,
    1016,     0,     0,     0,  1017,     0,     0,     0,     0,     0,
    1018,  1019,  1020,     0,  1021,  1022,  1028,  1027
  };

  const short
  Dhcp4Parser::yycheck_[] =
  {
      70,    71,    72,    73,    74,    75,    81,    77,    78,    79,
      80,    73,    78,    76,    78,    72,    73,    74,    75,   663,
      77,    78,   600,    80,   928,   928,    73,   928,   606,    73,
      10,    74,     5,    18,     7,     7,     9,   185,    77,    78,
      15,    16,    78,     3,    19,    68,     0,    22,     8,    28,
      29,    30,    72,    73,    74,    75,   159,    77,    78,   161,
      80,     3,   164,   165,   166,   167,    73,    74,    75,     3,
      79,     3,    73,    73,     8,    75,     8,     3,     7,    73,
       6,    75,    91,    92,    93,    73,     7,    75,     7,    73,
       7,    73,    28,    29,    30,   104,     3,    73,   107,     6,
      79,    34,     7,    73,    73,   119,   120,    73,    73,    73,
      73,    73,     7,    92,    93,    73,     3,    92,    93,     6,
       6,    73,    73,    73,   103,    73,    73,    73,     7,    74,
     109,   110,   111,   112,   113,   114,     3,   116,     7,    80,
       3,     8,    78,    79,    80,     8,     7,    80,     7,    82,
      83,    92,    93,    86,    87,    88,    92,    93,     3,    92,
      93,    92,    93,     8,     3,   150,     7,     6,     4,   105,
     106,   185,   109,   110,   111,   112,   185,   114,   158,    11,
     119,   120,    14,     7,   152,   153,   154,   155,   168,   169,
     170,    23,     8,    25,    26,    27,    28,    29,    30,    31,
      32,    33,   133,   134,   135,   185,   185,     3,  1112,  1112,
     185,  1112,   185,   186,   187,   188,     4,    92,    93,   160,
     188,   162,   163,    12,    13,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,     3,   185,     3,    78,    79,     8,   185,
       8,     8,   185,     3,   185,   130,   131,    89,     8,     3,
      92,    93,     3,     3,     8,    97,     4,     8,     8,     3,
     102,   103,   916,     4,     8,     4,   108,     4,    80,    81,
      82,    83,    84,    85,    17,    18,   118,     3,     3,   121,
      92,    93,     8,     8,     3,     3,   128,   129,     3,     8,
     132,     3,     3,     8,   136,     4,     8,     8,    20,    21,
     185,   122,   123,   124,   125,   126,   127,     3,   116,   117,
       4,     3,     8,     3,   156,   157,     8,   159,     8,     3,
       8,     3,     3,     3,     8,   405,     8,     8,     8,     3,
      35,    36,    37,    38,     8,    98,    99,   100,   101,    34,
       4,     4,     4,   185,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,   395,   396,     4,     4,     4,     4,     4,     4,
       4,     4,     4,   185,     4,   455,     4,     4,     3,     8,
       4,   461,     4,   185,     3,    80,     4,     8,     4,     4,
       4,     4,     4,   473,   461,     4,   476,   188,     4,     4,
       4,   473,     4,     4,     4,     4,   473,   487,     4,   476,
     188,   188,     4,     4,     4,     4,   473,   497,     4,   473,
     487,     4,   502,   476,   186,   186,   502,   186,   502,   186,
     497,   461,   188,   186,   186,   502,     4,     4,   187,   524,
     187,     4,   522,   473,     4,     4,   476,     4,   497,     4,
     188,     4,   188,   502,   188,   522,   473,   487,   188,   476,
       4,     4,   473,   473,     4,     4,     4,   497,     4,   473,
     487,     4,   502,     4,     4,   473,   186,   487,     4,   473,
       4,   473,     4,   487,     4,    92,    93,   473,     4,   487,
     185,     4,   522,   473,   473,     4,     4,   473,   473,   473,
     473,   473,   535,   536,   537,   473,  1094,     4,     4,   188,
       4,   473,   473,   473,     4,   473,   473,   473,     4,     4,
     186,   476,     4,     4,     4,     4,     4,     4,     4,     4,
     137,   138,   139,   140,   141,   142,   143,   144,   145,   146,
     147,   148,   149,     4,     4,     4,     4,     4,     4,   156,
     157,   171,   172,   173,   174,   175,   176,   177,   178,   179,
     180,   181,   182,   183,   184,     4,     4,   652,     4,   186,
       4,   651,     4,     4,     4,     4,   186,   657,   185,     4,
     188,     4,     4,     4,     4,   188,     4,     4,   186,     4,
     657,   188,   186,   188,     4,   628,     7,   151,   186,     7,
      26,    27,    28,    29,    30,     7,   188,   188,     7,     7,
     185,   691,   185,   693,   185,     7,     7,   650,     5,   185,
     185,   185,     5,     5,   691,   692,   693,   657,     5,     5,
       5,    57,    58,    59,    60,    61,    62,    63,    64,     7,
     185,    67,    68,    69,    70,    71,    72,    73,     5,    75,
      76,    77,     5,    79,     5,     7,   185,     7,     7,     7,
     185,   691,   692,   693,    90,     5,    92,    93,    94,    95,
      96,    97,    26,    27,    28,    29,    30,     5,   104,   185,
     185,   107,   108,   185,     5,   185,   185,   185,     7,   115,
     185,     5,   185,   185,   185,    24,   185,   185,   185,     7,
       7,   185,   185,    57,    58,    59,    60,    61,    62,    63,
      64,   185,   185,    67,    68,    69,    70,    71,    72,    73,
      74,   185,   185,   185,     7,    79,    80,     7,     7,     7,
     156,   157,   185,   185,   185,   185,   185,   185,    92,    93,
     185,    95,     7,    97,     7,     7,     7,     4,     4,     4,
     104,     4,     4,   107,     4,     4,     4,     4,     4,   185,
       4,   115,     3,     6,     6,     3,     6,     3,     3,     6,
       3,   185,     6,     3,     6,     6,     3,     6,     4,     4,
       4,     4,     4,     4,     4,     4,     3,   188,     4,   186,
       8,     6,     4,     4,     4,     4,   186,     4,   186,   188,
       4,     4,   156,   157,     4,   186,   186,   186,   186,     4,
       4,     4,     4,   186,   188,   186,   186,   186,     6,   186,
     186,   186,     3,   186,   188,     4,   185,   185,     8,   185,
     185,   185,     8,     4,     8,     3,     8,     4,   185,   919,
     185,   185,   922,   185,   185,   925,   185,   919,   928,   925,
     185,   925,   919,   933,   185,   922,   936,     4,   925,   939,
     933,   928,   919,   188,     4,   919,   933,     4,   186,   936,
     185,   928,   952,   922,   928,   928,   925,     5,     7,   928,
     185,   961,     4,     4,   933,   952,     4,   967,     4,   919,
     188,   958,   922,   186,   961,   925,   186,     4,   928,   185,
     967,   185,   919,   933,   572,   651,   936,   455,   919,   919,
     641,   928,   961,   742,   967,   919,   933,   928,   928,   936,
     461,   919,   952,   933,   928,   919,   936,   919,   958,   933,
     928,   961,   936,   919,   928,   933,   928,   967,   936,   919,
     919,   657,   928,   919,   919,   919,   919,   919,   928,   928,
     967,   919,   928,   928,   928,   928,   928,   919,   919,   919,
     928,   919,   919,   919,   405,   918,   928,   928,   928,   892,
     928,   928,   928,   928,   941,   913,   939,   931,   505,   948,
     930,   921,   919,  1112,   502,   497,   967,  1117,   922,   924,
     938,   936,   969,   925,   927,   693,   713,   656,   652,   958,
     528,   473,  1127,   522,   934,   476,  1147,   524,  1167,    -1,
      -1,    -1,   967,    -1,    -1,    -1,    -1,   487,    -1,    -1,
      -1,    -1,    -1,    -1,   952,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,  1112,    -1,    -1,    -1,   962,  1117,    -1,    -1,
      -1,    -1,  1075,    -1,  1117,  1112,    -1,  1127,    -1,    -1,
    1117,    -1,    -1,    -1,    -1,  1112,    -1,    -1,  1112,  1112,
    1127,    -1,    -1,  1112,    -1,    -1,    -1,    -1,  1117,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1127,    -1,
      -1,    -1,  1112,    -1,    -1,    -1,    -1,  1117,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,  1112,    -1,  1127,    -1,    -1,
    1117,  1112,  1112,    -1,    -1,    -1,    -1,  1117,  1112,    -1,
      -1,    -1,    -1,  1117,  1112,    -1,    -1,    -1,  1112,  1117,
    1112,    -1,    -1,    -1,    -1,    -1,  1112,    -1,    -1,    -1,
      -1,    -1,  1112,  1112,    -1,    -1,  1112,  1112,  1112,  1112,
    1112,    -1,    -1,    -1,  1112,    -1,    -1,    -1,    -1,    -1,
    1112,  1112,  1112,    -1,  1112,  1112,  1112,  1112
  };

  const short
  Dhcp4Parser::yystos_[] =
  {
       0,   171,   172,   173,   174,   175,   176,   177,   178,   179,
     180,   181,   182,   183,   184,   190,   191,   192,   193,   194,
     195,   196,   197,   198,   199,   200,   201,   202,   203,   204,
       0,     5,     7,     9,   185,   186,   187,   188,   205,   206,
     207,   212,     7,   221,     7,   227,     7,   264,     7,   362,
       7,   442,     7,   458,     7,   394,     7,   400,     7,   424,
       7,   338,     7,   523,     7,   569,     7,   560,   213,   208,
     222,   228,   265,   363,   443,   459,   395,   401,   425,   339,
     524,   570,   561,   205,   214,   215,   185,   210,   211,    10,
     158,   168,   169,   170,   185,   220,   223,   224,   225,   552,
     554,   556,   567,    11,    14,    23,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    78,    79,    89,    92,    93,    97,   102,
     103,   108,   118,   121,   128,   129,   132,   136,   156,   157,
     159,   220,   229,   230,   231,   232,   233,   234,   235,   236,
     237,   238,   239,   240,   242,   243,   244,   245,   246,   247,
     248,   251,   253,   255,   257,   259,   260,   275,   277,   283,
     285,   323,   332,   346,   356,   380,   384,   392,   418,   448,
     450,   452,   463,   465,   467,   490,   502,   503,   511,   521,
     558,   573,    15,    16,    19,    22,   220,   262,   263,   266,
     268,   271,   274,   448,   450,    75,    76,    77,    90,    94,
      95,    96,   104,   107,   115,   220,   231,   232,   233,   234,
     235,   236,   237,   238,   243,   244,   245,   246,   247,   248,
     251,   253,   255,   257,   259,   364,   365,   366,   368,   370,
     372,   374,   376,   378,   380,   383,   418,   436,   448,   450,
     452,   463,   465,   467,   487,    91,   220,   376,   378,   418,
     444,   445,   446,   448,   450,   103,   109,   110,   111,   112,
     113,   114,   116,   220,   418,   448,   450,   460,   461,   462,
     463,   465,   467,   469,   473,   475,   477,   479,   481,   483,
     485,   392,    34,    80,    82,    83,    86,    87,    88,   220,
     303,   402,   403,   404,   405,   406,   407,   408,   410,   412,
     414,   415,   417,   448,   450,    81,    84,    85,   220,   303,
     406,   412,   426,   427,   428,   429,   430,   432,   433,   434,
     435,   448,   450,   119,   120,   220,   340,   341,   342,   344,
     137,   138,   139,   140,   141,   142,   143,   144,   145,   146,
     147,   148,   149,   156,   157,   220,   448,   450,   525,   526,
     527,   528,   530,   531,   533,   534,   535,   538,   540,   542,
     543,   544,   546,   548,   550,   571,   572,   573,    12,    13,
     562,   563,   564,   566,     6,     3,     4,     8,     3,   226,
     568,   553,   555,   557,     4,     3,     8,   559,   261,   278,
       4,     4,     4,   464,   466,   468,   276,   284,   286,     4,
       4,     4,     4,     4,     4,     4,     4,     4,   241,     4,
       4,     4,   249,   252,   254,     4,   357,   393,   419,   385,
     449,   451,   381,   324,   491,   453,   333,   347,     4,   504,
     512,   522,   256,   258,   574,     3,     8,   267,   269,   272,
       4,     3,     8,   369,   371,   373,   437,   367,   375,     4,
     379,   377,   488,     3,     8,   447,     3,     8,   486,   474,
     476,   480,   478,   484,   482,   470,     8,     3,     8,   409,
     304,     4,   413,   411,   416,     4,     8,     3,   431,     4,
       4,     8,     3,   343,   345,     3,     8,     4,   541,   529,
       4,   532,     4,     4,   536,   539,     4,     4,   545,   547,
     549,   551,     3,     8,     3,     8,   565,     4,     3,     8,
     205,   205,   185,     4,     4,     4,     4,     4,   224,     4,
       4,     4,   188,   188,   188,     4,     4,     4,     4,     4,
       4,   186,   186,   186,   186,   186,   188,   187,   187,   186,
       4,   188,   188,   188,     4,     4,     4,   188,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     4,
     186,     4,     4,     4,     4,     4,     4,   230,     4,     4,
       4,   188,   263,     4,     4,     4,     4,     4,     4,   186,
       4,     4,     4,   365,     4,   445,     4,     4,     4,     4,
       4,     4,     4,     4,   462,     4,     4,   186,     4,     4,
       4,   188,   404,     4,   188,   188,   428,     4,     4,   341,
     188,     4,     4,   186,     4,   186,   186,     4,     4,   188,
     188,     4,     4,     4,     4,   526,   572,     4,   186,   563,
       4,     7,     7,   205,   205,   205,     7,     7,     7,   185,
     185,   185,     7,     7,     5,   185,   152,   153,   154,   155,
     188,   250,   185,   185,     5,     5,     5,     5,   207,   209,
     185,    98,    99,   100,   101,   382,     5,     5,     5,     5,
       7,     7,     7,     7,   185,   185,     5,     5,   216,    17,
      18,   270,    20,    21,   273,   185,   185,   185,     5,   185,
     185,   216,   185,     7,   185,   216,   185,   185,   185,   185,
     185,   185,   185,   185,   185,   185,   185,   185,   185,   185,
     205,   185,   185,   185,    18,   150,   537,   151,   250,   185,
     185,   185,     5,   205,   229,   571,   562,   262,    24,   279,
     280,   281,    34,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
      56,   220,   291,   292,   293,   296,   298,   300,   302,   303,
     305,   306,   307,   308,   309,   310,   311,   312,   314,   316,
     318,   320,   321,   322,   291,     7,   287,   288,   289,     7,
     358,   359,   360,     7,   396,   397,   398,     7,   420,   421,
     422,     7,   386,   387,   388,   109,   110,   111,   112,   114,
     325,   326,   327,   328,   329,   330,   331,     7,   492,   493,
       7,   454,   455,   456,     7,   334,   335,   336,   122,   123,
     124,   125,   126,   127,   348,   349,   350,   351,   352,   353,
     354,   355,   130,   131,   220,   448,   450,   505,   506,   507,
     509,   133,   134,   135,   185,   448,   450,   513,   514,   515,
     516,   518,   519,   525,     7,   575,   576,   217,     7,   438,
     439,   440,   117,   469,   471,   489,   287,     8,     8,     8,
       8,   282,     3,     8,   294,   297,   299,   301,     4,     4,
       4,     4,     4,   313,   315,   317,   319,     4,     4,     4,
       4,     4,     4,     3,     8,     8,   290,     6,     3,   361,
       6,     3,   399,     6,     3,   423,     6,     3,   389,     6,
       3,     3,     6,   494,     3,     6,   457,     6,     3,   337,
       6,     3,     4,     4,     4,     4,     4,     4,     3,     8,
     508,   510,     3,     8,     4,   517,     4,   520,     3,     8,
       8,   577,     3,     6,   185,   218,   219,   441,     6,     3,
     472,     8,     6,     4,   280,     4,     4,     4,     4,   186,
     188,   186,   188,   186,     4,     4,     4,     4,   186,   186,
     186,   186,   188,   186,   292,   291,   289,   364,   360,   402,
     398,   426,   422,   220,   231,   232,   233,   234,   235,   236,
     237,   238,   243,   244,   245,   246,   247,   248,   251,   253,
     255,   257,   259,   303,   356,   374,   376,   378,   380,   390,
     391,   418,   448,   450,   463,   465,   467,   487,   388,   326,
     105,   106,   220,   303,   392,   418,   448,   450,   463,   465,
     467,   495,   496,   497,   498,   499,   501,   493,   460,   456,
     340,   336,   186,   186,   186,   186,   186,   186,   349,     4,
       4,   506,   188,     4,   186,     4,   514,   160,   162,   163,
     220,   303,   448,   450,   578,   579,   580,   581,   583,   576,
       6,     3,   444,   440,     4,   185,    35,    36,    37,    38,
     295,   185,   185,   185,   185,   185,   185,   185,     8,     8,
       8,     8,     3,     8,   500,     4,     8,     3,     8,     8,
     185,   185,   185,   205,   584,     4,   582,     3,     8,   185,
       8,   216,   391,     4,   188,   497,     4,   186,     4,   579,
     185,     5,   185,     7,   585,   586,   587,     3,     6,   161,
     164,   165,   166,   167,   588,   589,   590,   592,   593,   594,
     595,   586,   591,     4,     4,     4,   596,     3,     8,     4,
     188,   186,   186,     4,   589,   185,   185
  };

  const short
  Dhcp4Parser::yyr1_[] =
  {
       0,   189,   191,   190,   192,   190,   193,   190,   194,   190,
     195,   190,   196,   190,   197,   190,   198,   190,   199,   190,
     200,   190,   201,   190,   202,   190,   203,   190,   204,   190,
     205,   205,   205,   205,   205,   205,   205,   206,   208,   207,
     209,   210,   210,   211,   211,   213,   212,   214,   214,   215,
     215,   217,   216,   218,   218,   219,   219,   220,   222,   221,
     223,   223,   224,   224,   224,   224,   224,   224,   226,   225,
     228,   227,   229,   229,   230,   230,   230,   230,   230,   230,
     230,   230,   230,   230,   230,   230,   230,   230,   230,   230,
     230,   230,   230,   230,   230,   230,   230,   230,   230,   230,
     230,   230,   230,   230,   230,   230,   230,   230,   230,   230,
     230,   230,   230,   230,   230,   230,   230,   230,   230,   230,
     230,   230,   230,   231,   232,   233,   234,   235,   236,   237,
     238,   239,   241,   240,   242,   243,   244,   245,   246,   247,
     249,   248,   250,   250,   250,   250,   250,   252,   251,   254,
     253,   256,   255,   258,   257,   259,   261,   260,   262,   262,
     263,   263,   263,   263,   263,   263,   263,   265,   264,   267,
     266,   269,   268,   270,   270,   272,   271,   273,   273,   274,
     276,   275,   278,   277,   279,   279,   280,   282,   281,   284,
     283,   286,   285,   287,   287,   288,   288,   290,   289,   291,
     291,   292,   292,   292,   292,   292,   292,   292,   292,   292,
     292,   292,   292,   292,   292,   292,   292,   292,   292,   292,
     292,   292,   294,   293,   295,   295,   295,   295,   297,   296,
     299,   298,   301,   300,   302,   304,   303,   305,   306,   307,
     308,   309,   310,   311,   313,   312,   315,   314,   317,   316,
     319,   318,   320,   321,   322,   324,   323,   325,   325,   326,
     326,   326,   326,   326,   327,   328,   329,   330,   331,   333,
     332,   334,   334,   335,   335,   337,   336,   339,   338,   340,
     340,   340,   341,   341,   343,   342,   345,   344,   347,   346,
     348,   348,   349,   349,   349,   349,   349,   349,   350,   351,
     352,   353,   354,   355,   357,   356,   358,   358,   359,   359,
     361,   360,   363,   362,   364,   364,   365,   365,   365,   365,
     365,   365,   365,   365,   365,   365,   365,   365,   365,   365,
     365,   365,   365,   365,   365,   365,   365,   365,   365,   365,
     365,   365,   365,   365,   365,   365,   365,   365,   365,   365,
     365,   365,   365,   365,   367,   366,   369,   368,   371,   370,
     373,   372,   375,   374,   377,   376,   379,   378,   381,   380,
     382,   382,   382,   382,   383,   385,   384,   386,   386,   387,
     387,   389,   388,   390,   390,   391,   391,   391,   391,   391,
     391,   391,   391,   391,   391,   391,   391,   391,   391,   391,
     391,   391,   391,   391,   391,   391,   391,   391,   391,   391,
     391,   391,   391,   391,   391,   391,   391,   391,   393,   392,
     395,   394,   396,   396,   397,   397,   399,   398,   401,   400,
     402,   402,   403,   403,   404,   404,   404,   404,   404,   404,
     404,   404,   404,   404,   405,   406,   407,   409,   408,   411,
     410,   413,   412,   414,   416,   415,   417,   419,   418,   420,
     420,   421,   421,   423,   422,   425,   424,   426,   426,   427,
     427,   428,   428,   428,   428,   428,   428,   428,   428,   428,
     429,   431,   430,   432,   433,   434,   435,   437,   436,   438,
     438,   439,   439,   441,   440,   443,   442,   444,   444,   445,
     445,   445,   445,   445,   445,   445,   447,   446,   449,   448,
     451,   450,   453,   452,   454,   454,   455,   455,   457,   456,
     459,   458,   460,   460,   461,   461,   462,   462,   462,   462,
     462,   462,   462,   462,   462,   462,   462,   462,   462,   462,
     462,   464,   463,   466,   465,   468,   467,   470,   469,   472,
     471,   474,   473,   476,   475,   478,   477,   480,   479,   482,
     481,   484,   483,   486,   485,   488,   487,   489,   489,   491,
     490,   492,   492,   494,   493,   495,   495,   496,   496,   497,
     497,   497,   497,   497,   497,   497,   497,   497,   497,   497,
     498,   500,   499,   501,   502,   504,   503,   505,   505,   506,
     506,   506,   506,   506,   508,   507,   510,   509,   512,   511,
     513,   513,   514,   514,   514,   514,   514,   514,   515,   517,
     516,   518,   520,   519,   522,   521,   524,   523,   525,   525,
     526,   526,   526,   526,   526,   526,   526,   526,   526,   526,
     526,   526,   526,   526,   526,   526,   526,   526,   527,   529,
     528,   530,   532,   531,   533,   534,   536,   535,   537,   537,
     539,   538,   541,   540,   542,   543,   545,   544,   547,   546,
     549,   548,   551,   550,   553,   552,   555,   554,   557,   556,
     559,   558,   561,   560,   562,   562,   563,   563,   565,   564,
     566,   568,   567,   570,   569,   571,   571,   572,   574,   573,
     575,   575,   577,   576,   578,   578,   579,   579,   579,   579,
     579,   579,   579,   580,   582,   581,   584,   583,   585,   585,
     587,   586,   588,   588,   589,   589,   589,   589,   589,   591,
     590,   592,   593,   594,   596,   595
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
       1,     1,     1,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     0,     4,     3,     3,     3,     3,     3,     3,
       0,     4,     1,     1,     1,     1,     1,     0,     4,     0,
       4,     0,     4,     0,     4,     3,     0,     6,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     0,
       4,     0,     4,     1,     1,     0,     4,     1,     1,     3,
       0,     6,     0,     6,     1,     3,     1,     0,     4,     0,
       6,     0,     6,     0,     1,     1,     3,     0,     4,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     1,     1,     1,     1,     0,     4,
       0,     4,     0,     4,     3,     0,     4,     3,     3,     3,
       3,     3,     3,     3,     0,     4,     0,     4,     0,     4,
       0,     4,     3,     3,     3,     0,     6,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       6,     0,     1,     1,     3,     0,     4,     0,     4,     1,
       3,     1,     1,     1,     0,     4,     0,     4,     0,     6,
       1,     3,     1,     1,     1,     1,     1,     1,     3,     3,
       3,     3,     3,     3,     0,     6,     0,     1,     1,     3,
       0,     4,     0,     4,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       1,     1,     1,     1,     3,     0,     6,     0,     1,     1,
       3,     0,     4,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     6,
       0,     4,     0,     1,     1,     3,     0,     4,     0,     4,
       0,     1,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     3,     1,     0,     4,     0,
       4,     0,     4,     1,     0,     4,     3,     0,     6,     0,
       1,     1,     3,     0,     4,     0,     4,     0,     1,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     1,     1,     3,     3,     0,     6,     0,
       1,     1,     3,     0,     4,     0,     4,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     0,     4,
       0,     4,     0,     6,     0,     1,     1,     3,     0,     4,
       0,     4,     0,     1,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     6,     1,     1,     0,
       6,     1,     3,     0,     4,     0,     1,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     3,     3,     0,     6,     1,     3,     1,
       1,     1,     1,     1,     0,     4,     0,     4,     0,     6,
       1,     3,     1,     1,     1,     1,     1,     1,     3,     0,
       4,     3,     0,     4,     0,     6,     0,     4,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     3,     0,
       4,     3,     0,     4,     3,     3,     0,     4,     1,     1,
       0,     4,     0,     4,     3,     3,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     6,     0,     4,     1,     3,     1,     1,     0,     6,
       3,     0,     6,     0,     4,     1,     3,     1,     0,     6,
       1,     3,     0,     4,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     3,     0,     4,     0,     6,     1,     3,
       0,     4,     1,     3,     1,     1,     1,     1,     1,     0,
       4,     3,     3,     3,     0,     4
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
  "\"dhcp4o6-port\"", "\"control-socket\"", "\"socket-type\"",
  "\"socket-name\"", "\"dhcp-queue-control\"", "\"enable-queue\"",
  "\"queue-type\"", "\"capacity\"", "\"dhcp-ddns\"", "\"enable-updates\"",
  "\"qualifying-suffix\"", "\"server-ip\"", "\"server-port\"",
  "\"sender-ip\"", "\"sender-port\"", "\"max-queue-size\"",
  "\"ncr-protocol\"", "\"ncr-format\"", "\"override-no-update\"",
  "\"override-client-update\"", "\"replace-client-name\"",
  "\"generated-prefix\"", "\"tcp\"", "\"JSON\"", "\"when-present\"",
  "\"never\"", "\"always\"", "\"when-not-present\"",
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
  "store_extended_info", "interfaces_config", "$@27",
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
  "hooks_libraries", "$@48", "hooks_libraries_list",
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
  "dep_hostname_char_replacement", "$@120", "dhcp6_json_object", "$@121",
  "dhcpddns_json_object", "$@122", "control_agent_json_object", "$@123",
  "config_control", "$@124", "sub_config_control", "$@125",
  "config_control_params", "config_control_param", "config_databases",
  "$@126", "config_fetch_wait_time", "logging_object", "$@127",
  "sub_logging", "$@128", "logging_params", "logging_param", "loggers",
  "$@129", "loggers_entries", "logger_entry", "$@130", "logger_params",
  "logger_param", "debuglevel", "severity", "$@131", "output_options_list",
  "$@132", "output_options_list_content", "output_entry", "$@133",
  "output_params_list", "output_params", "output", "$@134", "flush",
  "maxsize", "maxver", "pattern", "$@135", YY_NULLPTR
  };

#if PARSER4_DEBUG
  const short
  Dhcp4Parser::yyrline_[] =
  {
       0,   276,   276,   276,   277,   277,   278,   278,   279,   279,
     280,   280,   281,   281,   282,   282,   283,   283,   284,   284,
     285,   285,   286,   286,   287,   287,   288,   288,   289,   289,
     297,   298,   299,   300,   301,   302,   303,   306,   311,   311,
     322,   325,   326,   329,   333,   340,   340,   347,   348,   351,
     355,   362,   362,   369,   370,   373,   377,   388,   398,   398,
     414,   415,   419,   420,   421,   422,   423,   424,   427,   427,
     442,   442,   451,   452,   457,   458,   459,   460,   461,   462,
     463,   464,   465,   466,   467,   468,   469,   470,   471,   472,
     473,   474,   475,   476,   477,   478,   479,   480,   481,   482,
     483,   484,   485,   486,   487,   488,   489,   490,   491,   492,
     493,   494,   495,   496,   497,   498,   499,   500,   501,   502,
     503,   504,   505,   508,   513,   518,   523,   528,   533,   538,
     543,   548,   553,   553,   561,   566,   571,   576,   581,   586,
     591,   591,   599,   602,   605,   608,   611,   617,   617,   625,
     625,   633,   633,   641,   641,   649,   654,   654,   665,   666,
     669,   670,   671,   672,   673,   674,   675,   678,   678,   687,
     687,   697,   697,   704,   705,   708,   708,   715,   717,   721,
     727,   727,   739,   739,   749,   750,   752,   754,   754,   772,
     772,   784,   784,   794,   795,   798,   799,   802,   802,   812,
     813,   816,   817,   818,   819,   820,   821,   822,   823,   824,
     825,   826,   827,   828,   829,   830,   831,   832,   833,   834,
     835,   836,   839,   839,   846,   847,   848,   849,   852,   852,
     860,   860,   868,   868,   876,   881,   881,   889,   894,   899,
     904,   909,   914,   919,   924,   924,   932,   932,   940,   940,
     948,   948,   956,   961,   966,   972,   972,   982,   983,   986,
     987,   988,   989,   990,   993,   998,  1003,  1008,  1013,  1018,
    1018,  1028,  1029,  1032,  1033,  1036,  1036,  1046,  1046,  1056,
    1057,  1058,  1061,  1062,  1065,  1065,  1073,  1073,  1081,  1081,
    1092,  1093,  1096,  1097,  1098,  1099,  1100,  1101,  1104,  1109,
    1114,  1119,  1124,  1129,  1137,  1137,  1150,  1151,  1154,  1155,
    1162,  1162,  1188,  1188,  1199,  1200,  1204,  1205,  1206,  1207,
    1208,  1209,  1210,  1211,  1212,  1213,  1214,  1215,  1216,  1217,
    1218,  1219,  1220,  1221,  1222,  1223,  1224,  1225,  1226,  1227,
    1228,  1229,  1230,  1231,  1232,  1233,  1234,  1235,  1236,  1237,
    1238,  1239,  1240,  1241,  1244,  1244,  1252,  1252,  1260,  1260,
    1268,  1268,  1276,  1276,  1284,  1284,  1292,  1292,  1302,  1302,
    1309,  1310,  1311,  1312,  1315,  1322,  1322,  1333,  1334,  1338,
    1339,  1342,  1342,  1350,  1351,  1354,  1355,  1356,  1357,  1358,
    1359,  1360,  1361,  1362,  1363,  1364,  1365,  1366,  1367,  1368,
    1369,  1370,  1371,  1372,  1373,  1374,  1375,  1376,  1377,  1378,
    1379,  1380,  1381,  1382,  1383,  1384,  1385,  1386,  1393,  1393,
    1406,  1406,  1415,  1416,  1419,  1420,  1425,  1425,  1440,  1440,
    1454,  1455,  1458,  1459,  1462,  1463,  1464,  1465,  1466,  1467,
    1468,  1469,  1470,  1471,  1474,  1476,  1481,  1483,  1483,  1491,
    1491,  1499,  1499,  1507,  1509,  1509,  1517,  1526,  1526,  1538,
    1539,  1544,  1545,  1550,  1550,  1562,  1562,  1574,  1575,  1580,
    1581,  1586,  1587,  1588,  1589,  1590,  1591,  1592,  1593,  1594,
    1597,  1599,  1599,  1607,  1609,  1611,  1616,  1624,  1624,  1636,
    1637,  1640,  1641,  1644,  1644,  1654,  1654,  1664,  1665,  1668,
    1669,  1670,  1671,  1672,  1673,  1674,  1677,  1677,  1685,  1685,
    1710,  1710,  1740,  1740,  1750,  1751,  1754,  1755,  1758,  1758,
    1767,  1767,  1776,  1777,  1780,  1781,  1785,  1786,  1787,  1788,
    1789,  1790,  1791,  1792,  1793,  1794,  1795,  1796,  1797,  1798,
    1799,  1802,  1802,  1810,  1810,  1818,  1818,  1826,  1826,  1834,
    1834,  1844,  1844,  1852,  1852,  1860,  1860,  1868,  1868,  1876,
    1876,  1884,  1884,  1892,  1892,  1905,  1905,  1915,  1916,  1922,
    1922,  1932,  1933,  1936,  1936,  1946,  1947,  1950,  1951,  1954,
    1955,  1956,  1957,  1958,  1959,  1960,  1961,  1962,  1963,  1964,
    1967,  1969,  1969,  1977,  1986,  1993,  1993,  2003,  2004,  2007,
    2008,  2009,  2010,  2011,  2014,  2014,  2022,  2022,  2033,  2033,
    2045,  2046,  2049,  2050,  2051,  2052,  2053,  2054,  2057,  2062,
    2062,  2070,  2075,  2075,  2084,  2084,  2096,  2096,  2106,  2107,
    2110,  2111,  2112,  2113,  2114,  2115,  2116,  2117,  2118,  2119,
    2120,  2121,  2122,  2123,  2124,  2125,  2126,  2127,  2130,  2135,
    2135,  2143,  2148,  2148,  2156,  2161,  2166,  2166,  2174,  2175,
    2178,  2178,  2187,  2187,  2196,  2202,  2208,  2208,  2216,  2216,
    2225,  2225,  2234,  2234,  2245,  2245,  2252,  2252,  2259,  2259,
    2266,  2266,  2277,  2277,  2287,  2288,  2292,  2293,  2296,  2296,
    2306,  2316,  2316,  2326,  2326,  2337,  2338,  2342,  2346,  2346,
    2358,  2359,  2363,  2363,  2371,  2372,  2375,  2376,  2377,  2378,
    2379,  2380,  2381,  2384,  2389,  2389,  2397,  2397,  2407,  2408,
    2411,  2411,  2419,  2420,  2423,  2424,  2425,  2426,  2427,  2430,
    2430,  2438,  2443,  2448,  2453,  2453
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
#line 5398 "dhcp4_parser.cc"

#line 2462 "dhcp4_parser.yy"


void
isc::dhcp::Dhcp4Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
