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
      case 207: // value
      case 211: // map_value
      case 252: // ddns_replace_client_name_value
      case 274: // socket_type
      case 277: // outbound_interface_value
      case 299: // db_type
      case 386: // hr_mode
      case 541: // ncr_protocol_value
        value.YY_MOVE_OR_COPY< ElementPtr > (YY_MOVE (that.value));
        break;

      case 190: // "boolean"
        value.YY_MOVE_OR_COPY< bool > (YY_MOVE (that.value));
        break;

      case 189: // "floating point"
        value.YY_MOVE_OR_COPY< double > (YY_MOVE (that.value));
        break;

      case 188: // "integer"
        value.YY_MOVE_OR_COPY< int64_t > (YY_MOVE (that.value));
        break;

      case 187: // "constant string"
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
      case 207: // value
      case 211: // map_value
      case 252: // ddns_replace_client_name_value
      case 274: // socket_type
      case 277: // outbound_interface_value
      case 299: // db_type
      case 386: // hr_mode
      case 541: // ncr_protocol_value
        value.move< ElementPtr > (YY_MOVE (that.value));
        break;

      case 190: // "boolean"
        value.move< bool > (YY_MOVE (that.value));
        break;

      case 189: // "floating point"
        value.move< double > (YY_MOVE (that.value));
        break;

      case 188: // "integer"
        value.move< int64_t > (YY_MOVE (that.value));
        break;

      case 187: // "constant string"
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
      case 207: // value
      case 211: // map_value
      case 252: // ddns_replace_client_name_value
      case 274: // socket_type
      case 277: // outbound_interface_value
      case 299: // db_type
      case 386: // hr_mode
      case 541: // ncr_protocol_value
        value.copy< ElementPtr > (that.value);
        break;

      case 190: // "boolean"
        value.copy< bool > (that.value);
        break;

      case 189: // "floating point"
        value.copy< double > (that.value);
        break;

      case 188: // "integer"
        value.copy< int64_t > (that.value);
        break;

      case 187: // "constant string"
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
      case 207: // value
      case 211: // map_value
      case 252: // ddns_replace_client_name_value
      case 274: // socket_type
      case 277: // outbound_interface_value
      case 299: // db_type
      case 386: // hr_mode
      case 541: // ncr_protocol_value
        value.move< ElementPtr > (that.value);
        break;

      case 190: // "boolean"
        value.move< bool > (that.value);
        break;

      case 189: // "floating point"
        value.move< double > (that.value);
        break;

      case 188: // "integer"
        value.move< int64_t > (that.value);
        break;

      case 187: // "constant string"
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
      case 187: // "constant string"
#line 269 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < std::string > (); }
#line 447 "dhcp4_parser.cc"
        break;

      case 188: // "integer"
#line 269 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < int64_t > (); }
#line 453 "dhcp4_parser.cc"
        break;

      case 189: // "floating point"
#line 269 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < double > (); }
#line 459 "dhcp4_parser.cc"
        break;

      case 190: // "boolean"
#line 269 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < bool > (); }
#line 465 "dhcp4_parser.cc"
        break;

      case 207: // value
#line 269 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 471 "dhcp4_parser.cc"
        break;

      case 211: // map_value
#line 269 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 477 "dhcp4_parser.cc"
        break;

      case 252: // ddns_replace_client_name_value
#line 269 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 483 "dhcp4_parser.cc"
        break;

      case 274: // socket_type
#line 269 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 489 "dhcp4_parser.cc"
        break;

      case 277: // outbound_interface_value
#line 269 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 495 "dhcp4_parser.cc"
        break;

      case 299: // db_type
#line 269 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 501 "dhcp4_parser.cc"
        break;

      case 386: // hr_mode
#line 269 "dhcp4_parser.yy"
                 { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 507 "dhcp4_parser.cc"
        break;

      case 541: // ncr_protocol_value
#line 269 "dhcp4_parser.yy"
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
      case 207: // value
      case 211: // map_value
      case 252: // ddns_replace_client_name_value
      case 274: // socket_type
      case 277: // outbound_interface_value
      case 299: // db_type
      case 386: // hr_mode
      case 541: // ncr_protocol_value
        yylhs.value.emplace< ElementPtr > ();
        break;

      case 190: // "boolean"
        yylhs.value.emplace< bool > ();
        break;

      case 189: // "floating point"
        yylhs.value.emplace< double > ();
        break;

      case 188: // "integer"
        yylhs.value.emplace< int64_t > ();
        break;

      case 187: // "constant string"
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
#line 278 "dhcp4_parser.yy"
                     { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 781 "dhcp4_parser.cc"
    break;

  case 4:
#line 279 "dhcp4_parser.yy"
                      { ctx.ctx_ = ctx.CONFIG; }
#line 787 "dhcp4_parser.cc"
    break;

  case 6:
#line 280 "dhcp4_parser.yy"
                 { ctx.ctx_ = ctx.DHCP4; }
#line 793 "dhcp4_parser.cc"
    break;

  case 8:
#line 281 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 799 "dhcp4_parser.cc"
    break;

  case 10:
#line 282 "dhcp4_parser.yy"
                   { ctx.ctx_ = ctx.SUBNET4; }
#line 805 "dhcp4_parser.cc"
    break;

  case 12:
#line 283 "dhcp4_parser.yy"
                 { ctx.ctx_ = ctx.POOLS; }
#line 811 "dhcp4_parser.cc"
    break;

  case 14:
#line 284 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.RESERVATIONS; }
#line 817 "dhcp4_parser.cc"
    break;

  case 16:
#line 285 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.DHCP4; }
#line 823 "dhcp4_parser.cc"
    break;

  case 18:
#line 286 "dhcp4_parser.yy"
                      { ctx.ctx_ = ctx.OPTION_DEF; }
#line 829 "dhcp4_parser.cc"
    break;

  case 20:
#line 287 "dhcp4_parser.yy"
                       { ctx.ctx_ = ctx.OPTION_DATA; }
#line 835 "dhcp4_parser.cc"
    break;

  case 22:
#line 288 "dhcp4_parser.yy"
                         { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 841 "dhcp4_parser.cc"
    break;

  case 24:
#line 289 "dhcp4_parser.yy"
                     { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 847 "dhcp4_parser.cc"
    break;

  case 26:
#line 290 "dhcp4_parser.yy"
                   { ctx.ctx_ = ctx.LOGGING; }
#line 853 "dhcp4_parser.cc"
    break;

  case 28:
#line 291 "dhcp4_parser.yy"
                          { ctx.ctx_ = ctx.CONFIG_CONTROL; }
#line 859 "dhcp4_parser.cc"
    break;

  case 30:
#line 299 "dhcp4_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 865 "dhcp4_parser.cc"
    break;

  case 31:
#line 300 "dhcp4_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location))); }
#line 871 "dhcp4_parser.cc"
    break;

  case 32:
#line 301 "dhcp4_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 877 "dhcp4_parser.cc"
    break;

  case 33:
#line 302 "dhcp4_parser.yy"
              { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 883 "dhcp4_parser.cc"
    break;

  case 34:
#line 303 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 889 "dhcp4_parser.cc"
    break;

  case 35:
#line 304 "dhcp4_parser.yy"
            { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 895 "dhcp4_parser.cc"
    break;

  case 36:
#line 305 "dhcp4_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 901 "dhcp4_parser.cc"
    break;

  case 37:
#line 308 "dhcp4_parser.yy"
                {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as < ElementPtr > ());
}
#line 910 "dhcp4_parser.cc"
    break;

  case 38:
#line 313 "dhcp4_parser.yy"
                     {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 921 "dhcp4_parser.cc"
    break;

  case 39:
#line 318 "dhcp4_parser.yy"
                             {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 931 "dhcp4_parser.cc"
    break;

  case 40:
#line 324 "dhcp4_parser.yy"
                { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 937 "dhcp4_parser.cc"
    break;

  case 43:
#line 331 "dhcp4_parser.yy"
                                  {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 946 "dhcp4_parser.cc"
    break;

  case 44:
#line 335 "dhcp4_parser.yy"
                                                      {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 956 "dhcp4_parser.cc"
    break;

  case 45:
#line 342 "dhcp4_parser.yy"
                              {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 965 "dhcp4_parser.cc"
    break;

  case 46:
#line 345 "dhcp4_parser.yy"
                               {
    // list parsing complete. Put any sanity checking here
}
#line 973 "dhcp4_parser.cc"
    break;

  case 49:
#line 353 "dhcp4_parser.yy"
                      {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 982 "dhcp4_parser.cc"
    break;

  case 50:
#line 357 "dhcp4_parser.yy"
                                           {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 991 "dhcp4_parser.cc"
    break;

  case 51:
#line 364 "dhcp4_parser.yy"
                              {
    // List parsing about to start
}
#line 999 "dhcp4_parser.cc"
    break;

  case 52:
#line 366 "dhcp4_parser.yy"
                                       {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 1008 "dhcp4_parser.cc"
    break;

  case 55:
#line 375 "dhcp4_parser.yy"
                               {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 1017 "dhcp4_parser.cc"
    break;

  case 56:
#line 379 "dhcp4_parser.yy"
                                                            {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 1026 "dhcp4_parser.cc"
    break;

  case 57:
#line 390 "dhcp4_parser.yy"
                                {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as < std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 1037 "dhcp4_parser.cc"
    break;

  case 58:
#line 400 "dhcp4_parser.yy"
                           {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1048 "dhcp4_parser.cc"
    break;

  case 59:
#line 405 "dhcp4_parser.yy"
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
#line 429 "dhcp4_parser.yy"
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
#line 436 "dhcp4_parser.yy"
                                                    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1084 "dhcp4_parser.cc"
    break;

  case 70:
#line 444 "dhcp4_parser.yy"
                          {
    // Parse the Dhcp4 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1094 "dhcp4_parser.cc"
    break;

  case 71:
#line 448 "dhcp4_parser.yy"
                               {
    // No global parameter is required
    // parsing completed
}
#line 1103 "dhcp4_parser.cc"
    break;

  case 125:
#line 512 "dhcp4_parser.yy"
                                             {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1112 "dhcp4_parser.cc"
    break;

  case 126:
#line 517 "dhcp4_parser.yy"
                                                     {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-valid-lifetime", prf);
}
#line 1121 "dhcp4_parser.cc"
    break;

  case 127:
#line 522 "dhcp4_parser.yy"
                                                     {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-valid-lifetime", prf);
}
#line 1130 "dhcp4_parser.cc"
    break;

  case 128:
#line 527 "dhcp4_parser.yy"
                                       {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1139 "dhcp4_parser.cc"
    break;

  case 129:
#line 532 "dhcp4_parser.yy"
                                         {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1148 "dhcp4_parser.cc"
    break;

  case 130:
#line 537 "dhcp4_parser.yy"
                                                       {
    ElementPtr ctt(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("calculate-tee-times", ctt);
}
#line 1157 "dhcp4_parser.cc"
    break;

  case 131:
#line 542 "dhcp4_parser.yy"
                                   {
    ElementPtr t1(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t1-percent", t1);
}
#line 1166 "dhcp4_parser.cc"
    break;

  case 132:
#line 547 "dhcp4_parser.yy"
                                   {
    ElementPtr t2(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t2-percent", t2);
}
#line 1175 "dhcp4_parser.cc"
    break;

  case 133:
#line 552 "dhcp4_parser.yy"
                                                                 {
    ElementPtr dpp(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1184 "dhcp4_parser.cc"
    break;

  case 134:
#line 557 "dhcp4_parser.yy"
                       {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1192 "dhcp4_parser.cc"
    break;

  case 135:
#line 559 "dhcp4_parser.yy"
               {
    ElementPtr stag(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-tag", stag);
    ctx.leave();
}
#line 1202 "dhcp4_parser.cc"
    break;

  case 136:
#line 565 "dhcp4_parser.yy"
                                             {
    ElementPtr echo(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("echo-client-id", echo);
}
#line 1211 "dhcp4_parser.cc"
    break;

  case 137:
#line 570 "dhcp4_parser.yy"
                                               {
    ElementPtr match(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("match-client-id", match);
}
#line 1220 "dhcp4_parser.cc"
    break;

  case 138:
#line 575 "dhcp4_parser.yy"
                                           {
    ElementPtr prf(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("authoritative", prf);
}
#line 1229 "dhcp4_parser.cc"
    break;

  case 139:
#line 580 "dhcp4_parser.yy"
                                                   {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-send-updates", b);
}
#line 1238 "dhcp4_parser.cc"
    break;

  case 140:
#line 585 "dhcp4_parser.yy"
                                                               {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-no-update", b);
}
#line 1247 "dhcp4_parser.cc"
    break;

  case 141:
#line 590 "dhcp4_parser.yy"
                                                                       {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-override-client-update", b);
}
#line 1256 "dhcp4_parser.cc"
    break;

  case 142:
#line 595 "dhcp4_parser.yy"
                                                   {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 1264 "dhcp4_parser.cc"
    break;

  case 143:
#line 597 "dhcp4_parser.yy"
                                       {
    ctx.stack_.back()->set("ddns-replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1273 "dhcp4_parser.cc"
    break;

  case 144:
#line 603 "dhcp4_parser.yy"
                 {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1281 "dhcp4_parser.cc"
    break;

  case 145:
#line 606 "dhcp4_parser.yy"
          {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 1289 "dhcp4_parser.cc"
    break;

  case 146:
#line 609 "dhcp4_parser.yy"
           {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 1297 "dhcp4_parser.cc"
    break;

  case 147:
#line 612 "dhcp4_parser.yy"
                     {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 1305 "dhcp4_parser.cc"
    break;

  case 148:
#line 615 "dhcp4_parser.yy"
             {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 1314 "dhcp4_parser.cc"
    break;

  case 149:
#line 621 "dhcp4_parser.yy"
                                             {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1322 "dhcp4_parser.cc"
    break;

  case 150:
#line 623 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-generated-prefix", s);
    ctx.leave();
}
#line 1332 "dhcp4_parser.cc"
    break;

  case 151:
#line 629 "dhcp4_parser.yy"
                                               {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1340 "dhcp4_parser.cc"
    break;

  case 152:
#line 631 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ddns-qualifying-suffix", s);
    ctx.leave();
}
#line 1350 "dhcp4_parser.cc"
    break;

  case 153:
#line 637 "dhcp4_parser.yy"
                                     {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1358 "dhcp4_parser.cc"
    break;

  case 154:
#line 639 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 1368 "dhcp4_parser.cc"
    break;

  case 155:
#line 645 "dhcp4_parser.yy"
                                                     {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1376 "dhcp4_parser.cc"
    break;

  case 156:
#line 647 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 1386 "dhcp4_parser.cc"
    break;

  case 157:
#line 653 "dhcp4_parser.yy"
                                                       {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("store-extended-info", b);
}
#line 1395 "dhcp4_parser.cc"
    break;

  case 158:
#line 658 "dhcp4_parser.yy"
                                                                             {
    ElementPtr count(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-count", count);
}
#line 1404 "dhcp4_parser.cc"
    break;

  case 159:
#line 663 "dhcp4_parser.yy"
                                                                         {
    ElementPtr age(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("statistic-default-sample-age", age);
}
#line 1413 "dhcp4_parser.cc"
    break;

  case 160:
#line 668 "dhcp4_parser.yy"
                                     {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1424 "dhcp4_parser.cc"
    break;

  case 161:
#line 673 "dhcp4_parser.yy"
                                                               {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1434 "dhcp4_parser.cc"
    break;

  case 171:
#line 692 "dhcp4_parser.yy"
                                {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1444 "dhcp4_parser.cc"
    break;

  case 172:
#line 696 "dhcp4_parser.yy"
                                          {
    // No interfaces config param is required
    // parsing completed
}
#line 1453 "dhcp4_parser.cc"
    break;

  case 173:
#line 701 "dhcp4_parser.yy"
                            {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1464 "dhcp4_parser.cc"
    break;

  case 174:
#line 706 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1473 "dhcp4_parser.cc"
    break;

  case 175:
#line 711 "dhcp4_parser.yy"
                                   {
    ctx.enter(ctx.DHCP_SOCKET_TYPE);
}
#line 1481 "dhcp4_parser.cc"
    break;

  case 176:
#line 713 "dhcp4_parser.yy"
                    {
    ctx.stack_.back()->set("dhcp-socket-type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1490 "dhcp4_parser.cc"
    break;

  case 177:
#line 718 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("raw", ctx.loc2pos(yystack_[0].location))); }
#line 1496 "dhcp4_parser.cc"
    break;

  case 178:
#line 719 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("udp", ctx.loc2pos(yystack_[0].location))); }
#line 1502 "dhcp4_parser.cc"
    break;

  case 179:
#line 722 "dhcp4_parser.yy"
                                       {
    ctx.enter(ctx.OUTBOUND_INTERFACE);
}
#line 1510 "dhcp4_parser.cc"
    break;

  case 180:
#line 724 "dhcp4_parser.yy"
                                 {
    ctx.stack_.back()->set("outbound-interface", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1519 "dhcp4_parser.cc"
    break;

  case 181:
#line 729 "dhcp4_parser.yy"
                                          {
    yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("same-as-inbound", ctx.loc2pos(yystack_[0].location)));
}
#line 1527 "dhcp4_parser.cc"
    break;

  case 182:
#line 731 "dhcp4_parser.yy"
                {
    yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("use-routing", ctx.loc2pos(yystack_[0].location)));
    }
#line 1535 "dhcp4_parser.cc"
    break;

  case 183:
#line 735 "dhcp4_parser.yy"
                                   {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1544 "dhcp4_parser.cc"
    break;

  case 184:
#line 741 "dhcp4_parser.yy"
                               {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1555 "dhcp4_parser.cc"
    break;

  case 185:
#line 746 "dhcp4_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1566 "dhcp4_parser.cc"
    break;

  case 186:
#line 753 "dhcp4_parser.yy"
                             {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sanity-checks", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SANITY_CHECKS);
}
#line 1577 "dhcp4_parser.cc"
    break;

  case 187:
#line 758 "dhcp4_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1586 "dhcp4_parser.cc"
    break;

  case 191:
#line 768 "dhcp4_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1594 "dhcp4_parser.cc"
    break;

  case 192:
#line 770 "dhcp4_parser.yy"
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

  case 193:
#line 786 "dhcp4_parser.yy"
                               {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1625 "dhcp4_parser.cc"
    break;

  case 194:
#line 791 "dhcp4_parser.yy"
                                                          {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1636 "dhcp4_parser.cc"
    break;

  case 195:
#line 798 "dhcp4_parser.yy"
                                 {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1647 "dhcp4_parser.cc"
    break;

  case 196:
#line 803 "dhcp4_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1656 "dhcp4_parser.cc"
    break;

  case 201:
#line 816 "dhcp4_parser.yy"
                         {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1666 "dhcp4_parser.cc"
    break;

  case 202:
#line 820 "dhcp4_parser.yy"
                                     {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1676 "dhcp4_parser.cc"
    break;

  case 226:
#line 853 "dhcp4_parser.yy"
                    {
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1684 "dhcp4_parser.cc"
    break;

  case 227:
#line 855 "dhcp4_parser.yy"
                {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1693 "dhcp4_parser.cc"
    break;

  case 228:
#line 860 "dhcp4_parser.yy"
                 { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1699 "dhcp4_parser.cc"
    break;

  case 229:
#line 861 "dhcp4_parser.yy"
               { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1705 "dhcp4_parser.cc"
    break;

  case 230:
#line 862 "dhcp4_parser.yy"
                    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1711 "dhcp4_parser.cc"
    break;

  case 231:
#line 863 "dhcp4_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1717 "dhcp4_parser.cc"
    break;

  case 232:
#line 866 "dhcp4_parser.yy"
           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1725 "dhcp4_parser.cc"
    break;

  case 233:
#line 868 "dhcp4_parser.yy"
               {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1735 "dhcp4_parser.cc"
    break;

  case 234:
#line 874 "dhcp4_parser.yy"
                   {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1743 "dhcp4_parser.cc"
    break;

  case 235:
#line 876 "dhcp4_parser.yy"
               {
    ElementPtr pwd(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1753 "dhcp4_parser.cc"
    break;

  case 236:
#line 882 "dhcp4_parser.yy"
           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1761 "dhcp4_parser.cc"
    break;

  case 237:
#line 884 "dhcp4_parser.yy"
               {
    ElementPtr h(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1771 "dhcp4_parser.cc"
    break;

  case 238:
#line 890 "dhcp4_parser.yy"
                         {
    ElementPtr p(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1780 "dhcp4_parser.cc"
    break;

  case 239:
#line 895 "dhcp4_parser.yy"
           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1788 "dhcp4_parser.cc"
    break;

  case 240:
#line 897 "dhcp4_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1798 "dhcp4_parser.cc"
    break;

  case 241:
#line 903 "dhcp4_parser.yy"
                               {
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1807 "dhcp4_parser.cc"
    break;

  case 242:
#line 908 "dhcp4_parser.yy"
                                         {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1816 "dhcp4_parser.cc"
    break;

  case 243:
#line 913 "dhcp4_parser.yy"
                                 {
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1825 "dhcp4_parser.cc"
    break;

  case 244:
#line 918 "dhcp4_parser.yy"
                                               {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1834 "dhcp4_parser.cc"
    break;

  case 245:
#line 923 "dhcp4_parser.yy"
                                               {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("request-timeout", n);
}
#line 1843 "dhcp4_parser.cc"
    break;

  case 246:
#line 928 "dhcp4_parser.yy"
                                           {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-keepalive", n);
}
#line 1852 "dhcp4_parser.cc"
    break;

  case 247:
#line 933 "dhcp4_parser.yy"
                                       {
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-nodelay", n);
}
#line 1861 "dhcp4_parser.cc"
    break;

  case 248:
#line 938 "dhcp4_parser.yy"
                               {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1869 "dhcp4_parser.cc"
    break;

  case 249:
#line 940 "dhcp4_parser.yy"
               {
    ElementPtr cp(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1879 "dhcp4_parser.cc"
    break;

  case 250:
#line 946 "dhcp4_parser.yy"
                   {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1887 "dhcp4_parser.cc"
    break;

  case 251:
#line 948 "dhcp4_parser.yy"
               {
    ElementPtr ks(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 1897 "dhcp4_parser.cc"
    break;

  case 252:
#line 954 "dhcp4_parser.yy"
                         {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1905 "dhcp4_parser.cc"
    break;

  case 253:
#line 956 "dhcp4_parser.yy"
               {
    ElementPtr c(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("consistency", c);
    ctx.leave();
}
#line 1915 "dhcp4_parser.cc"
    break;

  case 254:
#line 962 "dhcp4_parser.yy"
                                       {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1923 "dhcp4_parser.cc"
    break;

  case 255:
#line 964 "dhcp4_parser.yy"
               {
    ElementPtr c(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("serial-consistency", c);
    ctx.leave();
}
#line 1933 "dhcp4_parser.cc"
    break;

  case 256:
#line 970 "dhcp4_parser.yy"
                                                       {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 1942 "dhcp4_parser.cc"
    break;

  case 257:
#line 975 "dhcp4_parser.yy"
                                                       {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 1951 "dhcp4_parser.cc"
    break;

  case 258:
#line 980 "dhcp4_parser.yy"
                                             {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-row-errors", n);
}
#line 1960 "dhcp4_parser.cc"
    break;

  case 259:
#line 986 "dhcp4_parser.yy"
                                                           {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1971 "dhcp4_parser.cc"
    break;

  case 260:
#line 991 "dhcp4_parser.yy"
                                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1980 "dhcp4_parser.cc"
    break;

  case 268:
#line 1007 "dhcp4_parser.yy"
               {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1989 "dhcp4_parser.cc"
    break;

  case 269:
#line 1012 "dhcp4_parser.yy"
                           {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1998 "dhcp4_parser.cc"
    break;

  case 270:
#line 1017 "dhcp4_parser.yy"
                        {
    ElementPtr circuit(new StringElement("circuit-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(circuit);
}
#line 2007 "dhcp4_parser.cc"
    break;

  case 271:
#line 1022 "dhcp4_parser.yy"
                      {
    ElementPtr client(new StringElement("client-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(client);
}
#line 2016 "dhcp4_parser.cc"
    break;

  case 272:
#line 1027 "dhcp4_parser.yy"
                 {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 2025 "dhcp4_parser.cc"
    break;

  case 273:
#line 1032 "dhcp4_parser.yy"
                                 {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 2036 "dhcp4_parser.cc"
    break;

  case 274:
#line 1037 "dhcp4_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2045 "dhcp4_parser.cc"
    break;

  case 279:
#line 1050 "dhcp4_parser.yy"
                              {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2055 "dhcp4_parser.cc"
    break;

  case 280:
#line 1054 "dhcp4_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2065 "dhcp4_parser.cc"
    break;

  case 281:
#line 1060 "dhcp4_parser.yy"
                                  {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2075 "dhcp4_parser.cc"
    break;

  case 282:
#line 1064 "dhcp4_parser.yy"
                              {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2085 "dhcp4_parser.cc"
    break;

  case 288:
#line 1079 "dhcp4_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2093 "dhcp4_parser.cc"
    break;

  case 289:
#line 1081 "dhcp4_parser.yy"
               {
    ElementPtr lib(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 2103 "dhcp4_parser.cc"
    break;

  case 290:
#line 1087 "dhcp4_parser.yy"
                       {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2111 "dhcp4_parser.cc"
    break;

  case 291:
#line 1089 "dhcp4_parser.yy"
              {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2120 "dhcp4_parser.cc"
    break;

  case 292:
#line 1095 "dhcp4_parser.yy"
                                                     {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 2131 "dhcp4_parser.cc"
    break;

  case 293:
#line 1100 "dhcp4_parser.yy"
                                                            {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2141 "dhcp4_parser.cc"
    break;

  case 302:
#line 1118 "dhcp4_parser.yy"
                                                               {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 2150 "dhcp4_parser.cc"
    break;

  case 303:
#line 1123 "dhcp4_parser.yy"
                                                                               {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 2159 "dhcp4_parser.cc"
    break;

  case 304:
#line 1128 "dhcp4_parser.yy"
                                                       {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 2168 "dhcp4_parser.cc"
    break;

  case 305:
#line 1133 "dhcp4_parser.yy"
                                                     {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 2177 "dhcp4_parser.cc"
    break;

  case 306:
#line 1138 "dhcp4_parser.yy"
                                                 {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 2186 "dhcp4_parser.cc"
    break;

  case 307:
#line 1143 "dhcp4_parser.yy"
                                                               {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 2195 "dhcp4_parser.cc"
    break;

  case 308:
#line 1151 "dhcp4_parser.yy"
                      {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet4", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET4);
}
#line 2206 "dhcp4_parser.cc"
    break;

  case 309:
#line 1156 "dhcp4_parser.yy"
                                                             {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2215 "dhcp4_parser.cc"
    break;

  case 314:
#line 1176 "dhcp4_parser.yy"
                        {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2225 "dhcp4_parser.cc"
    break;

  case 315:
#line 1180 "dhcp4_parser.yy"
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
#line 2251 "dhcp4_parser.cc"
    break;

  case 316:
#line 1202 "dhcp4_parser.yy"
                            {
    // Parse the subnet4 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2261 "dhcp4_parser.cc"
    break;

  case 317:
#line 1206 "dhcp4_parser.yy"
                                {
    // The subnet subnet4 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2271 "dhcp4_parser.cc"
    break;

  case 358:
#line 1258 "dhcp4_parser.yy"
               {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2279 "dhcp4_parser.cc"
    break;

  case 359:
#line 1260 "dhcp4_parser.yy"
               {
    ElementPtr subnet(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 2289 "dhcp4_parser.cc"
    break;

  case 360:
#line 1266 "dhcp4_parser.yy"
                                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2297 "dhcp4_parser.cc"
    break;

  case 361:
#line 1268 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface", iface);
    ctx.leave();
}
#line 2307 "dhcp4_parser.cc"
    break;

  case 362:
#line 1274 "dhcp4_parser.yy"
                                                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2315 "dhcp4_parser.cc"
    break;

  case 363:
#line 1276 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface-id", iface);
    ctx.leave();
}
#line 2325 "dhcp4_parser.cc"
    break;

  case 364:
#line 1282 "dhcp4_parser.yy"
                                     {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2333 "dhcp4_parser.cc"
    break;

  case 365:
#line 1284 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-subnet", iface);
    ctx.leave();
}
#line 2343 "dhcp4_parser.cc"
    break;

  case 366:
#line 1290 "dhcp4_parser.yy"
                     {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2351 "dhcp4_parser.cc"
    break;

  case 367:
#line 1292 "dhcp4_parser.yy"
               {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 2361 "dhcp4_parser.cc"
    break;

  case 368:
#line 1298 "dhcp4_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2369 "dhcp4_parser.cc"
    break;

  case 369:
#line 1300 "dhcp4_parser.yy"
               {
    ElementPtr cls(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 2379 "dhcp4_parser.cc"
    break;

  case 370:
#line 1306 "dhcp4_parser.yy"
                                               {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2390 "dhcp4_parser.cc"
    break;

  case 371:
#line 1311 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2399 "dhcp4_parser.cc"
    break;

  case 372:
#line 1316 "dhcp4_parser.yy"
                                   {
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 2407 "dhcp4_parser.cc"
    break;

  case 373:
#line 1318 "dhcp4_parser.yy"
                {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2416 "dhcp4_parser.cc"
    break;

  case 374:
#line 1323 "dhcp4_parser.yy"
                  { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 2422 "dhcp4_parser.cc"
    break;

  case 375:
#line 1324 "dhcp4_parser.yy"
                     { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 2428 "dhcp4_parser.cc"
    break;

  case 376:
#line 1325 "dhcp4_parser.yy"
                { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("global", ctx.loc2pos(yystack_[0].location))); }
#line 2434 "dhcp4_parser.cc"
    break;

  case 377:
#line 1326 "dhcp4_parser.yy"
             { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 2440 "dhcp4_parser.cc"
    break;

  case 378:
#line 1329 "dhcp4_parser.yy"
                     {
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 2449 "dhcp4_parser.cc"
    break;

  case 379:
#line 1336 "dhcp4_parser.yy"
                                 {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 2460 "dhcp4_parser.cc"
    break;

  case 380:
#line 1341 "dhcp4_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2469 "dhcp4_parser.cc"
    break;

  case 385:
#line 1356 "dhcp4_parser.yy"
                               {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2479 "dhcp4_parser.cc"
    break;

  case 386:
#line 1360 "dhcp4_parser.yy"
                                       {
    ctx.stack_.pop_back();
}
#line 2487 "dhcp4_parser.cc"
    break;

  case 422:
#line 1407 "dhcp4_parser.yy"
                            {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 2498 "dhcp4_parser.cc"
    break;

  case 423:
#line 1412 "dhcp4_parser.yy"
                                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2507 "dhcp4_parser.cc"
    break;

  case 424:
#line 1420 "dhcp4_parser.yy"
                                    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2516 "dhcp4_parser.cc"
    break;

  case 425:
#line 1423 "dhcp4_parser.yy"
                                 {
    // parsing completed
}
#line 2524 "dhcp4_parser.cc"
    break;

  case 430:
#line 1439 "dhcp4_parser.yy"
                                 {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2534 "dhcp4_parser.cc"
    break;

  case 431:
#line 1443 "dhcp4_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2546 "dhcp4_parser.cc"
    break;

  case 432:
#line 1454 "dhcp4_parser.yy"
                               {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2556 "dhcp4_parser.cc"
    break;

  case 433:
#line 1458 "dhcp4_parser.yy"
                                   {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2568 "dhcp4_parser.cc"
    break;

  case 449:
#line 1490 "dhcp4_parser.yy"
                         {
    ElementPtr code(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 2577 "dhcp4_parser.cc"
    break;

  case 451:
#line 1497 "dhcp4_parser.yy"
                      {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2585 "dhcp4_parser.cc"
    break;

  case 452:
#line 1499 "dhcp4_parser.yy"
               {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 2595 "dhcp4_parser.cc"
    break;

  case 453:
#line 1505 "dhcp4_parser.yy"
                                      {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2603 "dhcp4_parser.cc"
    break;

  case 454:
#line 1507 "dhcp4_parser.yy"
               {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 2613 "dhcp4_parser.cc"
    break;

  case 455:
#line 1513 "dhcp4_parser.yy"
             {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2621 "dhcp4_parser.cc"
    break;

  case 456:
#line 1515 "dhcp4_parser.yy"
               {
    ElementPtr space(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 2631 "dhcp4_parser.cc"
    break;

  case 458:
#line 1523 "dhcp4_parser.yy"
                                    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2639 "dhcp4_parser.cc"
    break;

  case 459:
#line 1525 "dhcp4_parser.yy"
               {
    ElementPtr encap(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 2649 "dhcp4_parser.cc"
    break;

  case 460:
#line 1531 "dhcp4_parser.yy"
                                      {
    ElementPtr array(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 2658 "dhcp4_parser.cc"
    break;

  case 461:
#line 1540 "dhcp4_parser.yy"
                              {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 2669 "dhcp4_parser.cc"
    break;

  case 462:
#line 1545 "dhcp4_parser.yy"
                                                                 {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2678 "dhcp4_parser.cc"
    break;

  case 467:
#line 1564 "dhcp4_parser.yy"
                                  {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2688 "dhcp4_parser.cc"
    break;

  case 468:
#line 1568 "dhcp4_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 2697 "dhcp4_parser.cc"
    break;

  case 469:
#line 1576 "dhcp4_parser.yy"
                                {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2707 "dhcp4_parser.cc"
    break;

  case 470:
#line 1580 "dhcp4_parser.yy"
                                    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 2716 "dhcp4_parser.cc"
    break;

  case 485:
#line 1613 "dhcp4_parser.yy"
                       {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2724 "dhcp4_parser.cc"
    break;

  case 486:
#line 1615 "dhcp4_parser.yy"
               {
    ElementPtr data(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2734 "dhcp4_parser.cc"
    break;

  case 489:
#line 1625 "dhcp4_parser.yy"
                                                 {
    ElementPtr space(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2743 "dhcp4_parser.cc"
    break;

  case 490:
#line 1630 "dhcp4_parser.yy"
                                                   {
    ElementPtr persist(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 2752 "dhcp4_parser.cc"
    break;

  case 491:
#line 1638 "dhcp4_parser.yy"
                  {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2763 "dhcp4_parser.cc"
    break;

  case 492:
#line 1643 "dhcp4_parser.yy"
                                                           {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2772 "dhcp4_parser.cc"
    break;

  case 497:
#line 1658 "dhcp4_parser.yy"
                                {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2782 "dhcp4_parser.cc"
    break;

  case 498:
#line 1662 "dhcp4_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2792 "dhcp4_parser.cc"
    break;

  case 499:
#line 1668 "dhcp4_parser.yy"
                          {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2802 "dhcp4_parser.cc"
    break;

  case 500:
#line 1672 "dhcp4_parser.yy"
                             {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2812 "dhcp4_parser.cc"
    break;

  case 510:
#line 1691 "dhcp4_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2820 "dhcp4_parser.cc"
    break;

  case 511:
#line 1693 "dhcp4_parser.yy"
               {
    ElementPtr pool(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2830 "dhcp4_parser.cc"
    break;

  case 512:
#line 1699 "dhcp4_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2838 "dhcp4_parser.cc"
    break;

  case 513:
#line 1701 "dhcp4_parser.yy"
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
#line 2865 "dhcp4_parser.cc"
    break;

  case 514:
#line 1724 "dhcp4_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2873 "dhcp4_parser.cc"
    break;

  case 515:
#line 1726 "dhcp4_parser.yy"
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
#line 2902 "dhcp4_parser.cc"
    break;

  case 516:
#line 1754 "dhcp4_parser.yy"
                           {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 2913 "dhcp4_parser.cc"
    break;

  case 517:
#line 1759 "dhcp4_parser.yy"
                                                          {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2922 "dhcp4_parser.cc"
    break;

  case 522:
#line 1772 "dhcp4_parser.yy"
                            {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2932 "dhcp4_parser.cc"
    break;

  case 523:
#line 1776 "dhcp4_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 2941 "dhcp4_parser.cc"
    break;

  case 524:
#line 1781 "dhcp4_parser.yy"
                                {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2951 "dhcp4_parser.cc"
    break;

  case 525:
#line 1785 "dhcp4_parser.yy"
                                    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 2960 "dhcp4_parser.cc"
    break;

  case 545:
#line 1816 "dhcp4_parser.yy"
                         {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2968 "dhcp4_parser.cc"
    break;

  case 546:
#line 1818 "dhcp4_parser.yy"
               {
    ElementPtr next_server(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("next-server", next_server);
    ctx.leave();
}
#line 2978 "dhcp4_parser.cc"
    break;

  case 547:
#line 1824 "dhcp4_parser.yy"
                                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2986 "dhcp4_parser.cc"
    break;

  case 548:
#line 1826 "dhcp4_parser.yy"
               {
    ElementPtr srv(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-hostname", srv);
    ctx.leave();
}
#line 2996 "dhcp4_parser.cc"
    break;

  case 549:
#line 1832 "dhcp4_parser.yy"
                               {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3004 "dhcp4_parser.cc"
    break;

  case 550:
#line 1834 "dhcp4_parser.yy"
               {
    ElementPtr bootfile(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("boot-file-name", bootfile);
    ctx.leave();
}
#line 3014 "dhcp4_parser.cc"
    break;

  case 551:
#line 1840 "dhcp4_parser.yy"
                       {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3022 "dhcp4_parser.cc"
    break;

  case 552:
#line 1842 "dhcp4_parser.yy"
               {
    ElementPtr addr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 3032 "dhcp4_parser.cc"
    break;

  case 553:
#line 1848 "dhcp4_parser.yy"
                           {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3043 "dhcp4_parser.cc"
    break;

  case 554:
#line 1853 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3052 "dhcp4_parser.cc"
    break;

  case 555:
#line 1858 "dhcp4_parser.yy"
           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3060 "dhcp4_parser.cc"
    break;

  case 556:
#line 1860 "dhcp4_parser.yy"
               {
    ElementPtr d(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 3070 "dhcp4_parser.cc"
    break;

  case 557:
#line 1866 "dhcp4_parser.yy"
                       {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3078 "dhcp4_parser.cc"
    break;

  case 558:
#line 1868 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 3088 "dhcp4_parser.cc"
    break;

  case 559:
#line 1874 "dhcp4_parser.yy"
                           {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3096 "dhcp4_parser.cc"
    break;

  case 560:
#line 1876 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-id", hw);
    ctx.leave();
}
#line 3106 "dhcp4_parser.cc"
    break;

  case 561:
#line 1882 "dhcp4_parser.yy"
                             {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3114 "dhcp4_parser.cc"
    break;

  case 562:
#line 1884 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("circuit-id", hw);
    ctx.leave();
}
#line 3124 "dhcp4_parser.cc"
    break;

  case 563:
#line 1890 "dhcp4_parser.yy"
                       {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3132 "dhcp4_parser.cc"
    break;

  case 564:
#line 1892 "dhcp4_parser.yy"
               {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 3142 "dhcp4_parser.cc"
    break;

  case 565:
#line 1898 "dhcp4_parser.yy"
                   {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3150 "dhcp4_parser.cc"
    break;

  case 566:
#line 1900 "dhcp4_parser.yy"
               {
    ElementPtr host(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 3160 "dhcp4_parser.cc"
    break;

  case 567:
#line 1906 "dhcp4_parser.yy"
                                           {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3171 "dhcp4_parser.cc"
    break;

  case 568:
#line 1911 "dhcp4_parser.yy"
                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3180 "dhcp4_parser.cc"
    break;

  case 569:
#line 1919 "dhcp4_parser.yy"
             {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 3191 "dhcp4_parser.cc"
    break;

  case 570:
#line 1924 "dhcp4_parser.yy"
                                                {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3200 "dhcp4_parser.cc"
    break;

  case 573:
#line 1936 "dhcp4_parser.yy"
                               {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 3211 "dhcp4_parser.cc"
    break;

  case 574:
#line 1941 "dhcp4_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3220 "dhcp4_parser.cc"
    break;

  case 577:
#line 1950 "dhcp4_parser.yy"
                                   {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3230 "dhcp4_parser.cc"
    break;

  case 578:
#line 1954 "dhcp4_parser.yy"
                                     {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3240 "dhcp4_parser.cc"
    break;

  case 595:
#line 1983 "dhcp4_parser.yy"
                        {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3248 "dhcp4_parser.cc"
    break;

  case 596:
#line 1985 "dhcp4_parser.yy"
               {
    ElementPtr test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 3258 "dhcp4_parser.cc"
    break;

  case 597:
#line 1991 "dhcp4_parser.yy"
                                                 {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 3267 "dhcp4_parser.cc"
    break;

  case 598:
#line 2000 "dhcp4_parser.yy"
                                         {
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 3276 "dhcp4_parser.cc"
    break;

  case 599:
#line 2007 "dhcp4_parser.yy"
                               {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 3287 "dhcp4_parser.cc"
    break;

  case 600:
#line 2012 "dhcp4_parser.yy"
                                                            {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3296 "dhcp4_parser.cc"
    break;

  case 608:
#line 2028 "dhcp4_parser.yy"
                                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3304 "dhcp4_parser.cc"
    break;

  case 609:
#line 2030 "dhcp4_parser.yy"
               {
    ElementPtr stype(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 3314 "dhcp4_parser.cc"
    break;

  case 610:
#line 2036 "dhcp4_parser.yy"
                                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3322 "dhcp4_parser.cc"
    break;

  case 611:
#line 2038 "dhcp4_parser.yy"
               {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 3332 "dhcp4_parser.cc"
    break;

  case 612:
#line 2047 "dhcp4_parser.yy"
                                       {
    ElementPtr qc(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-queue-control", qc);
    ctx.stack_.push_back(qc);
    ctx.enter(ctx.DHCP_QUEUE_CONTROL);
}
#line 3343 "dhcp4_parser.cc"
    break;

  case 613:
#line 2052 "dhcp4_parser.yy"
                                                           {
    // The enable queue parameter is required.
    ctx.require("enable-queue", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3354 "dhcp4_parser.cc"
    break;

  case 622:
#line 2071 "dhcp4_parser.yy"
                                         {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-queue", b);
}
#line 3363 "dhcp4_parser.cc"
    break;

  case 623:
#line 2076 "dhcp4_parser.yy"
                       {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3371 "dhcp4_parser.cc"
    break;

  case 624:
#line 2078 "dhcp4_parser.yy"
               {
    ElementPtr qt(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("queue-type", qt);
    ctx.leave();
}
#line 3381 "dhcp4_parser.cc"
    break;

  case 625:
#line 2084 "dhcp4_parser.yy"
                                 {
    ElementPtr c(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("capacity", c);
}
#line 3390 "dhcp4_parser.cc"
    break;

  case 626:
#line 2089 "dhcp4_parser.yy"
                            {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3398 "dhcp4_parser.cc"
    break;

  case 627:
#line 2091 "dhcp4_parser.yy"
              {
    ctx.stack_.back()->set(yystack_[3].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3407 "dhcp4_parser.cc"
    break;

  case 628:
#line 2098 "dhcp4_parser.yy"
                     {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 3418 "dhcp4_parser.cc"
    break;

  case 629:
#line 2103 "dhcp4_parser.yy"
                                                       {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3429 "dhcp4_parser.cc"
    break;

  case 630:
#line 2110 "dhcp4_parser.yy"
                              {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3439 "dhcp4_parser.cc"
    break;

  case 631:
#line 2114 "dhcp4_parser.yy"
                                  {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3449 "dhcp4_parser.cc"
    break;

  case 652:
#line 2144 "dhcp4_parser.yy"
                                             {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 3458 "dhcp4_parser.cc"
    break;

  case 653:
#line 2149 "dhcp4_parser.yy"
                     {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3466 "dhcp4_parser.cc"
    break;

  case 654:
#line 2151 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 3476 "dhcp4_parser.cc"
    break;

  case 655:
#line 2157 "dhcp4_parser.yy"
                                       {
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 3485 "dhcp4_parser.cc"
    break;

  case 656:
#line 2162 "dhcp4_parser.yy"
                     {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3493 "dhcp4_parser.cc"
    break;

  case 657:
#line 2164 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 3503 "dhcp4_parser.cc"
    break;

  case 658:
#line 2170 "dhcp4_parser.yy"
                                       {
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 3512 "dhcp4_parser.cc"
    break;

  case 659:
#line 2175 "dhcp4_parser.yy"
                                             {
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 3521 "dhcp4_parser.cc"
    break;

  case 660:
#line 2180 "dhcp4_parser.yy"
                           {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 3529 "dhcp4_parser.cc"
    break;

  case 661:
#line 2182 "dhcp4_parser.yy"
                           {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3538 "dhcp4_parser.cc"
    break;

  case 662:
#line 2188 "dhcp4_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 3544 "dhcp4_parser.cc"
    break;

  case 663:
#line 2189 "dhcp4_parser.yy"
        { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 3550 "dhcp4_parser.cc"
    break;

  case 664:
#line 2192 "dhcp4_parser.yy"
                       {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 3558 "dhcp4_parser.cc"
    break;

  case 665:
#line 2194 "dhcp4_parser.yy"
             {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 3568 "dhcp4_parser.cc"
    break;

  case 666:
#line 2201 "dhcp4_parser.yy"
                                         {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3576 "dhcp4_parser.cc"
    break;

  case 667:
#line 2203 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 3586 "dhcp4_parser.cc"
    break;

  case 668:
#line 2210 "dhcp4_parser.yy"
                                                         {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 3595 "dhcp4_parser.cc"
    break;

  case 669:
#line 2216 "dhcp4_parser.yy"
                                                                 {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 3604 "dhcp4_parser.cc"
    break;

  case 670:
#line 2222 "dhcp4_parser.yy"
                                             {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 3612 "dhcp4_parser.cc"
    break;

  case 671:
#line 2224 "dhcp4_parser.yy"
                                       {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3621 "dhcp4_parser.cc"
    break;

  case 672:
#line 2230 "dhcp4_parser.yy"
                                       {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3629 "dhcp4_parser.cc"
    break;

  case 673:
#line 2232 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 3639 "dhcp4_parser.cc"
    break;

  case 674:
#line 2239 "dhcp4_parser.yy"
                                         {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3647 "dhcp4_parser.cc"
    break;

  case 675:
#line 2241 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 3657 "dhcp4_parser.cc"
    break;

  case 676:
#line 2248 "dhcp4_parser.yy"
                                                         {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3665 "dhcp4_parser.cc"
    break;

  case 677:
#line 2250 "dhcp4_parser.yy"
               {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 3675 "dhcp4_parser.cc"
    break;

  case 678:
#line 2259 "dhcp4_parser.yy"
                         {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3683 "dhcp4_parser.cc"
    break;

  case 679:
#line 2261 "dhcp4_parser.yy"
              {
    ctx.stack_.back()->set("Dhcp6", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3692 "dhcp4_parser.cc"
    break;

  case 680:
#line 2266 "dhcp4_parser.yy"
                               {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3700 "dhcp4_parser.cc"
    break;

  case 681:
#line 2268 "dhcp4_parser.yy"
              {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3709 "dhcp4_parser.cc"
    break;

  case 682:
#line 2273 "dhcp4_parser.yy"
                                         {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3717 "dhcp4_parser.cc"
    break;

  case 683:
#line 2275 "dhcp4_parser.yy"
              {
    ctx.stack_.back()->set("Control-agent", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3726 "dhcp4_parser.cc"
    break;

  case 684:
#line 2280 "dhcp4_parser.yy"
                               {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 3737 "dhcp4_parser.cc"
    break;

  case 685:
#line 2285 "dhcp4_parser.yy"
                                                            {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3747 "dhcp4_parser.cc"
    break;

  case 686:
#line 2291 "dhcp4_parser.yy"
                                   {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3757 "dhcp4_parser.cc"
    break;

  case 687:
#line 2295 "dhcp4_parser.yy"
                                       {
    // No config_control params are required
    // parsing completed
}
#line 3766 "dhcp4_parser.cc"
    break;

  case 692:
#line 2310 "dhcp4_parser.yy"
                                   {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 3777 "dhcp4_parser.cc"
    break;

  case 693:
#line 2315 "dhcp4_parser.yy"
                                                      {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3786 "dhcp4_parser.cc"
    break;

  case 694:
#line 2320 "dhcp4_parser.yy"
                                                             {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-fetch-wait-time", value);
}
#line 3795 "dhcp4_parser.cc"
    break;

  case 695:
#line 2330 "dhcp4_parser.yy"
                        {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 3806 "dhcp4_parser.cc"
    break;

  case 696:
#line 2335 "dhcp4_parser.yy"
                                                     {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3815 "dhcp4_parser.cc"
    break;

  case 697:
#line 2340 "dhcp4_parser.yy"
                            {
    // Parse the Logging map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3825 "dhcp4_parser.cc"
    break;

  case 698:
#line 2344 "dhcp4_parser.yy"
                                {
    // parsing completed
}
#line 3833 "dhcp4_parser.cc"
    break;

  case 702:
#line 2360 "dhcp4_parser.yy"
                 {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 3844 "dhcp4_parser.cc"
    break;

  case 703:
#line 2365 "dhcp4_parser.yy"
                                                         {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3853 "dhcp4_parser.cc"
    break;

  case 706:
#line 2377 "dhcp4_parser.yy"
                             {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 3863 "dhcp4_parser.cc"
    break;

  case 707:
#line 2381 "dhcp4_parser.yy"
                               {
    ctx.stack_.pop_back();
}
#line 3871 "dhcp4_parser.cc"
    break;

  case 717:
#line 2398 "dhcp4_parser.yy"
                                     {
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 3880 "dhcp4_parser.cc"
    break;

  case 718:
#line 2403 "dhcp4_parser.yy"
                   {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3888 "dhcp4_parser.cc"
    break;

  case 719:
#line 2405 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 3898 "dhcp4_parser.cc"
    break;

  case 720:
#line 2411 "dhcp4_parser.yy"
                                    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 3909 "dhcp4_parser.cc"
    break;

  case 721:
#line 2416 "dhcp4_parser.yy"
                                                                    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3918 "dhcp4_parser.cc"
    break;

  case 724:
#line 2425 "dhcp4_parser.yy"
                             {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3928 "dhcp4_parser.cc"
    break;

  case 725:
#line 2429 "dhcp4_parser.yy"
                                    {
    ctx.stack_.pop_back();
}
#line 3936 "dhcp4_parser.cc"
    break;

  case 733:
#line 2444 "dhcp4_parser.yy"
               {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3944 "dhcp4_parser.cc"
    break;

  case 734:
#line 2446 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 3954 "dhcp4_parser.cc"
    break;

  case 735:
#line 2452 "dhcp4_parser.yy"
                           {
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 3963 "dhcp4_parser.cc"
    break;

  case 736:
#line 2457 "dhcp4_parser.yy"
                               {
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 3972 "dhcp4_parser.cc"
    break;

  case 737:
#line 2462 "dhcp4_parser.yy"
                             {
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 3981 "dhcp4_parser.cc"
    break;

  case 738:
#line 2467 "dhcp4_parser.yy"
                 {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3989 "dhcp4_parser.cc"
    break;

  case 739:
#line 2469 "dhcp4_parser.yy"
               {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pattern", sev);
    ctx.leave();
}
#line 3999 "dhcp4_parser.cc"
    break;


#line 4003 "dhcp4_parser.cc"

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


  const short Dhcp4Parser::yypact_ninf_ = -915;

  const signed char Dhcp4Parser::yytable_ninf_ = -1;

  const short
  Dhcp4Parser::yypact_[] =
  {
     384,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,
    -915,  -915,  -915,  -915,  -915,    56,    28,    23,    67,    73,
      77,    79,    81,   107,   117,   123,   142,   146,   150,   162,
    -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,
    -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,
    -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,
    -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,    28,  -128,
      17,   169,    25,   290,   -45,   596,   -11,    66,   211,   -59,
     578,   -55,   289,  -915,   131,   113,   174,   195,   204,  -915,
    -915,  -915,  -915,  -915,   209,  -915,    43,  -915,  -915,  -915,
    -915,  -915,  -915,  -915,  -915,  -915,   242,   265,   280,  -915,
    -915,  -915,  -915,  -915,  -915,   310,   325,   331,   332,   333,
     334,   336,   337,   338,  -915,   339,   340,   341,   342,   362,
    -915,  -915,  -915,   366,  -915,  -915,  -915,  -915,  -915,  -915,
    -915,  -915,  -915,  -915,  -915,  -915,   368,  -915,  -915,  -915,
    -915,  -915,  -915,  -915,    62,  -915,  -915,  -915,  -915,  -915,
    -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,
    -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,
    -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,
    -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,
    -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,   369,
    -915,    68,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,
    -915,  -915,  -915,  -915,  -915,   370,  -915,  -915,  -915,  -915,
    -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,
    -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,    74,
    -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,
    -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,
    -915,  -915,  -915,  -915,    75,  -915,  -915,  -915,  -915,  -915,
    -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,
    -915,   213,   245,  -915,  -915,  -915,  -915,  -915,  -915,  -915,
    -915,  -915,  -915,  -915,  -915,   274,  -915,  -915,   371,  -915,
    -915,  -915,   374,  -915,  -915,   373,   376,  -915,  -915,  -915,
    -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,
     379,   386,  -915,  -915,  -915,  -915,   385,   389,  -915,  -915,
    -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,
      87,  -915,  -915,  -915,   390,  -915,  -915,   391,  -915,   397,
     398,  -915,  -915,   399,   400,  -915,  -915,  -915,  -915,  -915,
    -915,  -915,    93,  -915,  -915,  -915,  -915,  -915,  -915,  -915,
    -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,   109,
    -915,  -915,  -915,   401,   110,  -915,  -915,  -915,  -915,    28,
      28,  -915,   219,   404,   407,   409,   410,   411,  -915,    17,
    -915,   412,   414,   415,   230,   231,   234,   422,   423,   424,
     425,   426,   427,   246,   249,   252,   253,   255,   260,   256,
     263,   266,   449,   269,   272,   271,   276,   284,   452,   459,
     461,   286,   463,   464,   466,   476,   477,   478,   480,   483,
     485,   486,   488,   490,   308,   494,   496,   497,   498,   502,
     503,   169,  -915,   507,   508,   519,   314,    25,  -915,   520,
     521,   522,   526,   531,   532,   350,   567,   568,   569,   290,
    -915,   570,   -45,  -915,   571,   572,   573,   574,   575,   576,
     577,   579,  -915,   596,  -915,   580,   582,   402,   583,   584,
     587,   403,  -915,    66,   588,   406,   408,  -915,   211,   590,
     593,   -79,  -915,   413,   595,   597,   416,   598,   417,   418,
     603,   605,   420,   421,   608,   610,   616,   617,   578,  -915,
     -55,  -915,   618,   435,   289,  -915,  -915,  -915,   623,   621,
     625,    28,    28,    28,  -915,   626,   627,   629,  -915,  -915,
    -915,   443,   450,   451,   632,   633,   636,  -915,  -915,  -915,
    -915,  -915,  -915,  -915,  -915,  -915,   467,  -915,  -915,  -915,
    -915,  -915,   -22,   468,   469,  -915,   652,   661,   662,   663,
     667,   482,   221,   670,   671,   673,   677,   678,  -915,   682,
     685,   686,   509,   510,   689,  -915,   694,   273,   291,  -915,
    -915,   513,   515,   516,   699,   518,   528,  -915,   694,   529,
     706,  -915,   543,  -915,   694,   544,   545,   546,   547,   548,
     551,   552,  -915,   553,   554,  -915,   555,   556,   557,  -915,
    -915,   558,  -915,  -915,  -915,   559,    28,  -915,  -915,   562,
     563,  -915,   564,  -915,  -915,    14,   447,  -915,  -915,   -22,
     565,   566,   581,  -915,  -915,   749,  -915,  -915,    28,   169,
     -55,  -915,  -915,  -915,   289,    25,   731,  -915,  -915,  -915,
     500,   500,   750,  -915,  -915,  -915,  -915,  -915,  -915,  -915,
    -915,  -915,   751,   752,   753,   754,  -915,  -915,  -915,  -915,
    -915,  -915,  -915,  -915,    51,   755,   756,   757,   130,    90,
       4,   578,  -915,  -915,   759,  -915,  -915,  -915,  -915,  -915,
    -915,  -915,  -915,  -915,  -915,  -915,   760,  -915,  -915,  -915,
    -915,   207,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,
    -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,
    -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,
     750,  -915,   128,   135,   144,   178,  -915,   202,  -915,  -915,
    -915,  -915,  -915,  -915,   765,   766,   767,   768,   769,  -915,
    -915,  -915,  -915,   770,   771,   773,   774,   775,   776,  -915,
     216,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,
    -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,
    -915,  -915,   217,  -915,   778,   779,  -915,  -915,   780,   782,
    -915,  -915,   781,   785,  -915,  -915,   783,   787,  -915,  -915,
     786,   788,  -915,  -915,  -915,  -915,  -915,  -915,    99,  -915,
    -915,  -915,  -915,  -915,  -915,  -915,   176,  -915,  -915,   789,
     790,  -915,  -915,   791,   793,  -915,   777,   794,   795,   796,
     797,   798,   244,  -915,  -915,  -915,  -915,  -915,  -915,  -915,
    -915,  -915,  -915,  -915,  -915,   258,  -915,  -915,  -915,   799,
    -915,   800,  -915,  -915,  -915,   259,  -915,  -915,  -915,  -915,
    -915,   262,  -915,   187,  -915,   607,  -915,   801,   802,  -915,
    -915,  -915,  -915,   748,   803,  -915,  -915,  -915,  -915,   804,
     731,  -915,   806,   807,   808,   809,   628,   624,   630,   631,
     634,   811,   813,   815,   816,   635,   637,   638,   639,   640,
     641,   500,  -915,  -915,   500,  -915,   750,   290,  -915,   751,
      66,  -915,   752,   211,  -915,   753,   589,  -915,   754,    51,
    -915,    64,   755,  -915,   596,  -915,   756,   -59,  -915,   757,
     643,   644,   645,   646,   647,   648,   130,  -915,   820,   824,
      90,  -915,   649,   833,   650,   836,     4,  -915,  -915,   193,
     759,  -915,  -915,   835,   839,   -45,  -915,   760,   840,  -915,
    -915,   619,  -915,   296,   656,   658,   659,  -915,  -915,  -915,
    -915,  -915,   660,   664,   665,   666,  -915,  -915,  -915,  -915,
    -915,  -915,  -915,   268,  -915,   275,  -915,   841,  -915,   842,
    -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,
    -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,
    -915,  -915,  -915,  -915,  -915,  -915,  -915,   277,  -915,  -915,
    -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,   844,
    -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,   846,
     852,  -915,  -915,  -915,  -915,  -915,   848,  -915,   278,  -915,
    -915,  -915,  -915,  -915,  -915,  -915,  -915,   672,   674,  -915,
    -915,   675,  -915,    28,  -915,  -915,   854,  -915,  -915,  -915,
    -915,  -915,   301,  -915,  -915,  -915,  -915,  -915,  -915,   681,
     305,  -915,   694,  -915,  -915,  -915,  -915,  -915,  -915,  -915,
    -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,
     589,  -915,   860,   691,  -915,    64,  -915,  -915,  -915,  -915,
    -915,  -915,   868,   687,   878,   193,  -915,  -915,  -915,  -915,
    -915,   698,  -915,  -915,   881,  -915,   701,  -915,  -915,   888,
    -915,  -915,   208,  -915,     7,   888,  -915,  -915,   892,   894,
     896,  -915,   307,  -915,  -915,  -915,  -915,  -915,  -915,  -915,
     897,   714,   718,   720,   907,     7,  -915,   727,  -915,  -915,
    -915,   728,  -915,  -915,  -915
  };

  const short
  Dhcp4Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,    28,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       1,    45,    38,    34,    33,    30,    31,    32,    37,     3,
      35,    36,    58,     5,    70,     7,   171,     9,   316,    11,
     499,    13,   524,    15,   424,    17,   432,    19,   469,    21,
     281,    23,   630,    25,   697,    27,   686,    29,    47,    41,
       0,     0,     0,     0,     0,   526,     0,   434,   471,     0,
       0,     0,     0,    49,     0,    48,     0,     0,    42,    68,
     695,   678,   680,   682,     0,    67,     0,    60,    62,    64,
      65,    66,    63,   684,   160,   186,     0,     0,     0,   545,
     547,   549,   184,   193,   195,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   134,     0,     0,     0,     0,     0,
     142,   149,   151,     0,   308,   422,   461,   379,   512,   514,
     372,   259,   573,   516,   273,   292,     0,   599,   612,   628,
     153,   155,   702,   124,     0,    72,    74,    75,    76,    77,
      78,   109,   110,   111,    79,   107,    96,    97,    98,   115,
     116,   117,   118,   119,   120,   113,   114,   121,   122,   123,
      82,    83,   104,    84,    85,    86,    90,    91,    80,   108,
      81,    88,    89,   102,   103,   105,    99,   100,   101,    87,
      92,    93,    94,    95,   106,   112,   173,   175,   179,     0,
     170,     0,   162,   164,   165,   166,   167,   168,   169,   360,
     362,   364,   491,   358,   366,     0,   370,   368,   569,   357,
     320,   321,   322,   323,   324,   345,   346,   347,   335,   336,
     348,   349,   350,   351,   352,   353,   354,   355,   356,     0,
     318,   327,   340,   341,   342,   328,   330,   331,   333,   329,
     325,   326,   343,   344,   332,   337,   338,   339,   334,   510,
     509,   505,   506,   504,     0,   501,   503,   507,   508,   567,
     555,   557,   561,   559,   565,   563,   551,   544,   538,   542,
     543,     0,   527,   528,   539,   540,   541,   535,   530,   536,
     532,   533,   534,   537,   531,     0,   451,   239,     0,   455,
     453,   458,     0,   447,   448,     0,   435,   436,   438,   450,
     439,   440,   441,   457,   442,   443,   444,   445,   446,   485,
       0,     0,   483,   484,   487,   488,     0,   472,   473,   475,
     476,   477,   478,   479,   480,   481,   482,   288,   290,   285,
       0,   283,   286,   287,     0,   666,   653,     0,   656,     0,
       0,   660,   664,     0,     0,   670,   672,   674,   676,   651,
     649,   650,     0,   632,   634,   635,   636,   637,   638,   639,
     640,   641,   646,   642,   643,   644,   645,   647,   648,     0,
     699,   701,   692,     0,     0,   688,   690,   691,    46,     0,
       0,    39,     0,     0,     0,     0,     0,     0,    57,     0,
      59,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    71,     0,     0,     0,     0,     0,   172,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     317,     0,     0,   500,     0,     0,     0,     0,     0,     0,
       0,     0,   525,     0,   425,     0,     0,     0,     0,     0,
       0,     0,   433,     0,     0,     0,     0,   470,     0,     0,
       0,     0,   282,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   631,
       0,   698,     0,     0,     0,   687,    50,    43,     0,     0,
       0,     0,     0,     0,    61,     0,     0,     0,   136,   137,
     138,     0,     0,     0,     0,     0,     0,   125,   126,   127,
     128,   129,   130,   131,   132,   133,     0,   158,   159,   139,
     140,   141,     0,     0,     0,   157,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   598,     0,
       0,     0,     0,     0,     0,    73,     0,     0,     0,   183,
     163,     0,     0,     0,     0,     0,     0,   378,     0,     0,
       0,   319,     0,   502,     0,     0,     0,     0,     0,     0,
       0,     0,   529,     0,     0,   449,     0,     0,     0,   460,
     437,     0,   489,   490,   474,     0,     0,   284,   652,     0,
       0,   655,     0,   658,   659,     0,     0,   668,   669,     0,
       0,     0,     0,   633,   700,     0,   694,   689,     0,     0,
       0,   679,   681,   683,     0,     0,     0,   546,   548,   550,
       0,     0,   197,   135,   144,   145,   146,   147,   148,   143,
     150,   152,   310,   426,   463,   381,    40,   513,   515,   374,
     375,   376,   377,   373,     0,     0,   518,   275,     0,     0,
       0,     0,   154,   156,     0,    51,   174,   177,   178,   176,
     181,   182,   180,   361,   363,   365,   493,   359,   367,   371,
     369,     0,   511,   568,   556,   558,   562,   560,   566,   564,
     552,   452,   240,   456,   454,   459,   486,   289,   291,   667,
     654,   657,   662,   663,   661,   665,   671,   673,   675,   677,
     197,    44,     0,     0,     0,     0,   191,     0,   188,   190,
     226,   232,   234,   236,     0,     0,     0,     0,     0,   248,
     250,   252,   254,     0,     0,     0,     0,     0,     0,   225,
       0,   203,   205,   206,   207,   208,   209,   210,   211,   212,
     213,   214,   218,   219,   220,   215,   221,   222,   223,   216,
     217,   224,     0,   201,     0,   198,   199,   314,     0,   311,
     312,   430,     0,   427,   428,   467,     0,   464,   465,   385,
       0,   382,   383,   268,   269,   270,   271,   272,     0,   261,
     263,   264,   265,   266,   267,   577,     0,   575,   522,     0,
     519,   520,   279,     0,   276,   277,     0,     0,     0,     0,
       0,     0,     0,   294,   296,   297,   298,   299,   300,   301,
     608,   610,   607,   605,   606,     0,   601,   603,   604,     0,
     623,     0,   626,   619,   620,     0,   614,   616,   617,   618,
     621,     0,   706,     0,   704,    53,   497,     0,   494,   495,
     553,   571,   572,     0,     0,    69,   696,   685,   161,     0,
       0,   187,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   185,   194,     0,   196,     0,     0,   309,     0,
     434,   423,     0,   471,   462,     0,     0,   380,     0,     0,
     260,   579,     0,   574,   526,   517,     0,     0,   274,     0,
       0,     0,     0,     0,     0,     0,     0,   293,     0,     0,
       0,   600,     0,     0,     0,     0,     0,   613,   629,     0,
       0,   703,    55,     0,    54,     0,   492,     0,     0,   570,
     693,     0,   189,     0,     0,     0,     0,   238,   241,   242,
     243,   244,     0,     0,     0,     0,   256,   257,   245,   246,
     247,   258,   204,     0,   200,     0,   313,     0,   429,     0,
     466,   421,   404,   405,   406,   392,   393,   409,   410,   411,
     395,   396,   412,   413,   414,   415,   416,   417,   418,   419,
     420,   389,   390,   391,   402,   403,   401,     0,   387,   394,
     407,   408,   397,   398,   399,   400,   384,   262,   595,     0,
     593,   594,   586,   587,   591,   592,   588,   589,   590,     0,
     580,   581,   583,   584,   585,   576,     0,   521,     0,   278,
     302,   303,   304,   305,   306,   307,   295,     0,     0,   602,
     622,     0,   625,     0,   615,   720,     0,   718,   716,   710,
     714,   715,     0,   708,   712,   713,   711,   705,    52,     0,
       0,   496,     0,   192,   228,   229,   230,   231,   227,   233,
     235,   237,   249,   251,   253,   255,   202,   315,   431,   468,
       0,   386,     0,     0,   578,     0,   523,   280,   609,   611,
     624,   627,     0,     0,     0,     0,   707,    56,   498,   554,
     388,     0,   597,   582,     0,   717,     0,   709,   596,     0,
     719,   724,     0,   722,     0,     0,   721,   733,     0,     0,
       0,   738,     0,   726,   728,   729,   730,   731,   732,   723,
       0,     0,     0,     0,     0,     0,   725,     0,   735,   736,
     737,     0,   727,   734,   739
  };

  const short
  Dhcp4Parser::yypgoto_[] =
  {
    -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,
    -915,  -915,  -915,  -915,  -915,  -915,   -23,  -915,   343,  -915,
    -915,  -915,  -915,  -915,  -915,  -915,  -915,  -580,  -915,  -915,
    -915,   -70,  -915,  -915,  -915,   550,  -915,  -915,  -915,  -915,
     279,   456,   -47,   -44,    -1,    16,    18,    24,    30,    31,
    -915,  -915,  -915,  -915,    34,    35,    36,    37,    38,    42,
    -915,   270,    48,  -915,    49,  -915,    50,  -915,    52,  -915,
      53,  -915,  -915,  -915,  -915,   257,   458,  -915,  -915,  -915,
    -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,
    -915,  -915,  -915,    82,  -915,  -915,  -915,  -915,  -915,  -915,
     181,  -915,     2,  -915,  -652,    71,  -915,  -915,  -915,  -915,
    -915,  -915,  -915,  -915,  -915,  -915,   -39,  -915,  -915,  -915,
    -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,
    -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,    44,
    -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,    45,
    -915,  -915,  -915,    40,   484,  -915,  -915,  -915,  -915,  -915,
    -915,  -915,    41,  -915,  -915,  -915,  -915,  -915,  -915,  -914,
    -915,  -915,  -915,    69,  -915,  -915,  -915,    72,   514,  -915,
    -915,  -915,  -915,  -915,  -915,  -915,  -915,  -912,  -915,   -43,
    -915,    55,  -915,    54,  -915,  -915,  -915,  -915,  -915,  -915,
    -915,    58,  -915,  -915,  -120,   -63,  -915,  -915,  -915,  -915,
    -915,    70,  -915,  -915,  -915,    76,  -915,   501,  -915,   -66,
    -915,  -915,  -915,  -915,  -915,   -64,  -915,  -915,  -915,  -915,
    -915,    -7,  -915,  -915,  -915,    78,  -915,  -915,  -915,    83,
    -915,   493,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,
    -915,  -915,  -915,    26,  -915,  -915,  -915,    32,   523,  -915,
    -915,   -57,  -915,   -20,  -915,   -62,  -915,  -915,  -915,    63,
    -915,  -915,  -915,    80,  -915,   517,     0,  -915,     6,  -915,
      12,  -915,   287,  -915,  -915,  -915,  -915,  -915,  -915,  -915,
    -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,
    -911,  -915,  -915,  -915,  -915,  -915,    84,  -915,  -915,  -915,
    -114,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,    57,
    -915,  -915,  -915,  -915,  -915,  -915,  -915,    46,  -915,  -915,
    -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,   313,   487,
    -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,
    -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,
    -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,  -915,
    -915,  -915,  -915,  -915,  -915,   354,   489,  -915,  -915,  -915,
    -915,  -915,  -915,  -915,   359,   491,   -75,  -915,  -915,    59,
    -915,  -915,  -115,  -915,  -915,  -915,  -915,  -915,  -915,  -133,
    -915,  -915,  -150,  -915,  -915,  -915,  -915,  -915,  -915,  -915
  };

  const short
  Dhcp4Parser::yydefgoto_[] =
  {
      -1,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    38,    39,    40,    69,
     687,    87,    88,    41,    68,    84,    85,   706,   885,   973,
     974,   779,    43,    70,    96,    97,    98,   403,    45,    71,
     154,   155,   156,   157,   158,   159,   160,   161,   162,   163,
     164,   165,   432,   166,   167,   168,   169,   170,   171,   172,
     438,   679,   173,   439,   174,   440,   175,   458,   176,   459,
     177,   178,   179,   180,   412,   211,   212,    47,    72,   213,
     463,   214,   464,   709,   215,   465,   712,   216,   181,   420,
     182,   413,   757,   758,   759,   899,   183,   421,   184,   422,
     804,   805,   806,   924,   780,   781,   782,   902,  1108,   783,
     903,   784,   904,   785,   905,   786,   787,   496,   788,   789,
     790,   791,   792,   793,   794,   795,   911,   796,   912,   797,
     913,   798,   914,   799,   800,   801,   185,   449,   828,   829,
     830,   831,   832,   833,   834,   186,   452,   843,   844,   845,
     947,    61,    79,   350,   351,   352,   509,   353,   510,   187,
     453,   852,   853,   854,   855,   856,   857,   858,   859,   188,
     442,   808,   809,   810,   927,    49,    73,   249,   250,   251,
     473,   252,   469,   253,   470,   254,   471,   255,   474,   256,
     477,   257,   476,   189,   448,   693,   259,   190,   445,   820,
     821,   822,   936,  1037,  1038,   191,   443,    55,    76,   812,
     813,   814,   930,    57,    77,   315,   316,   317,   318,   319,
     320,   321,   495,   322,   499,   323,   498,   324,   325,   500,
     326,   192,   444,   816,   817,   818,   933,    59,    78,   336,
     337,   338,   339,   340,   504,   341,   342,   343,   344,   261,
     472,   887,   888,   889,   975,    51,    74,   274,   275,   276,
     481,   193,   446,   194,   447,   195,   451,   839,   840,   841,
     944,    53,    75,   291,   292,   293,   196,   417,   197,   418,
     198,   419,   297,   491,   892,   978,   298,   485,   299,   486,
     300,   488,   301,   487,   302,   490,   303,   489,   304,   484,
     268,   478,   893,   199,   450,   836,   837,   941,  1059,  1060,
    1061,  1062,  1063,  1122,  1064,   200,   201,   455,   865,   866,
     867,   958,   868,   959,   202,   456,   875,   876,   877,   878,
     963,   879,   880,   965,   203,   457,    63,    80,   372,   373,
     374,   375,   515,   376,   377,   517,   378,   379,   380,   520,
     744,   381,   521,   382,   514,   383,   384,   385,   524,   386,
     525,   387,   526,   388,   527,    99,   405,   100,   406,   101,
     407,   204,   411,    67,    82,   394,   395,   396,   532,   397,
     102,   404,    65,    81,   389,   390,   205,   460,   883,   884,
     969,  1092,  1093,  1094,  1095,  1134,  1096,  1132,  1152,  1153,
    1154,  1162,  1163,  1164,  1170,  1165,  1166,  1167,  1168,  1174
  };

  const short
  Dhcp4Parser::yytable_[] =
  {
      95,   153,   210,   229,   270,   287,   391,   313,   332,   349,
     369,   264,   334,   305,   335,   217,   262,   277,   289,   802,
     327,   345,  1032,   370,  1033,  1045,   230,    89,   719,   231,
      42,   271,   742,    31,   723,    32,   136,    33,   314,   333,
     206,   207,   347,   348,   208,    83,   409,   209,   269,   138,
     139,   410,   218,   263,   278,   290,    30,   328,   346,    86,
     371,   226,   347,   348,   227,   461,   260,   273,   288,   135,
     462,   467,   232,   265,    44,   294,   468,   479,   482,   266,
      46,   295,   480,   483,    48,   267,    50,   296,    52,   233,
     511,   234,   109,   110,   111,   512,   528,   235,   138,   139,
     306,   529,   939,   236,   237,   940,   152,   238,   239,   240,
     241,   242,   530,   534,    54,   243,   399,   531,   535,   138,
     139,   244,   245,   246,    56,   247,   248,   258,    94,   272,
      58,   461,   674,   675,   676,   677,   895,   398,   530,   869,
     870,   871,    94,   896,   135,   136,   307,   534,   307,    60,
     308,   309,   897,    62,   310,   311,   312,    64,   138,   139,
     138,   139,   823,   824,   825,   826,   743,   827,   678,    66,
    1157,  1048,  1049,  1158,  1159,  1160,  1161,    90,   400,   942,
     103,   467,   943,   104,   138,   139,   898,    91,    92,    93,
     970,   872,   105,   971,   106,   107,   108,   109,   110,   111,
     112,   113,   114,   401,    94,   900,  1032,   402,  1033,  1045,
     901,  1155,    94,   408,  1156,    34,    35,    36,    37,   921,
     921,   492,   860,   861,   922,   923,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   124,   125,   126,   127,   128,
     129,   130,   131,   132,   133,   134,   414,   956,   493,   135,
     136,    94,   957,    94,   846,   847,   848,   849,   850,   851,
     137,   960,   966,   138,   139,   528,   961,   967,   140,   415,
     968,   921,  1003,   141,   142,   307,  1116,    94,   479,   143,
    1120,   511,   494,  1117,   416,  1121,  1127,   138,   139,   144,
     707,   708,   145,   307,   329,   308,   309,   330,   331,   146,
     147,   392,   393,   148,  1135,   138,   139,   149,   482,  1136,
    1175,   710,   711,  1138,   423,  1176,   107,   108,   109,   110,
     111,   689,   690,   691,   692,   286,   890,   150,   151,   424,
     152,  1104,  1105,  1106,  1107,   425,   426,   427,   428,    95,
     429,   430,   431,   433,   434,   435,   436,   115,   116,   117,
     118,   119,   120,   121,   122,  1085,    94,  1086,  1087,   127,
     128,   129,   130,   131,   132,   133,   437,   219,   220,   221,
     441,   136,   454,   466,   475,   497,   536,   537,   501,   503,
      94,   502,   222,   505,   138,   139,   223,   224,   225,   140,
     506,   153,   508,   507,   513,   516,   226,   210,    94,   227,
     143,   518,   519,   522,   523,   533,   538,   228,   539,   229,
     217,   540,   270,   541,   542,   543,   545,   264,   546,   547,
     548,   549,   262,   287,   550,   277,   551,   552,   553,   554,
     555,   556,   230,   313,   557,   231,   289,   558,   332,   271,
     559,   560,   334,   561,   335,   563,   327,   218,   150,   151,
     562,   345,   564,   566,   565,   391,   572,   567,   369,   263,
     568,   569,   278,   573,   314,   574,   570,   576,   577,   333,
     578,   370,   260,   290,   571,   273,   575,    94,   232,   265,
     579,   580,   581,   328,   582,   266,   288,   583,   346,   584,
     585,   267,   586,   294,   587,   233,   588,   234,   589,   295,
     590,   591,   592,   235,   599,   296,   593,   594,   371,   236,
     237,   596,   597,   238,   239,   240,   241,   242,   661,   662,
     663,   243,  1139,   598,   601,   602,   603,   244,   245,   246,
     604,   247,   248,   258,   760,   605,   606,   272,   607,   761,
     762,   763,   764,   765,   766,   767,   768,   769,   770,   771,
     772,   773,   774,   775,   776,   777,   778,     1,     2,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,   608,   609,   610,   612,   614,   615,   616,   617,   618,
     619,   620,   307,   621,   623,   391,   624,   626,   627,   153,
     625,   628,   631,   629,   635,   210,   632,   636,   633,   639,
     745,   640,   642,   638,   641,   643,   644,   645,   217,   646,
     647,   648,   649,   738,   650,   107,   108,   109,   110,   111,
     651,   652,   655,   656,   109,   110,   111,   658,   659,   862,
     667,   369,   660,   664,   665,   751,   666,   668,   669,   670,
     671,   672,   863,   873,   370,   218,   115,   116,   117,   118,
     119,   120,   121,   122,   673,   680,   681,   682,   127,   128,
     129,   130,   131,   132,   133,   134,   683,   684,   685,   688,
     136,   307,   138,   139,    32,   694,   695,   136,   696,   864,
     874,   371,   697,   138,   139,   698,   224,    94,   140,   699,
     138,   139,   700,   701,   704,   226,   702,   703,   227,   705,
     713,   279,   714,   715,   716,   717,   228,   280,   281,   282,
     283,   284,   285,   721,   286,   718,   720,   354,   355,   356,
     357,   358,   359,   360,   361,   362,   363,   364,   365,   366,
     722,   724,   725,   726,   727,   728,   367,   368,   729,   730,
     731,   732,   733,   734,   735,   736,   737,   150,   151,   739,
     740,   741,   747,   748,   750,   756,   979,   803,   807,   811,
     815,   819,   835,   838,   842,    94,   882,   886,   749,   906,
     907,   908,   909,   910,   915,   916,    94,   917,   918,   919,
     920,   950,   926,    94,   925,   929,   928,   931,   932,   934,
     935,   938,   937,   946,   972,   945,   949,   948,   951,   952,
     953,   954,   955,   962,   964,   977,  1103,   976,   981,   980,
     983,   984,   985,   986,   988,   992,   987,   993,   989,   994,
     995,   990,   991,   996,  1077,   997,   998,   999,  1078,  1001,
    1000,  1070,  1071,  1072,  1073,  1074,  1075,  1081,  1082,  1080,
    1083,  1098,  1099,  1109,  1102,  1110,  1111,  1112,  1123,  1118,
    1119,  1113,  1114,  1115,  1124,  1125,  1126,   229,  1133,  1128,
     313,  1129,  1130,   332,  1141,   264,  1011,   334,  1137,   335,
     262,  1050,  1144,   327,   287,  1145,   345,   349,  1052,  1040,
     230,  1142,  1146,   231,  1054,  1148,  1149,   289,  1150,  1012,
     862,   314,  1013,  1034,   333,  1151,  1171,  1031,  1172,  1088,
    1173,  1177,  1051,   863,  1178,   270,  1179,   263,  1180,   873,
     328,  1181,  1090,   346,  1183,  1184,  1041,   595,   277,   746,
     260,  1055,   755,   686,   290,   600,   232,   265,  1004,  1039,
    1089,   894,   271,   266,  1053,  1014,  1042,   288,   752,   267,
     864,  1056,  1043,   233,   294,   234,   874,  1057,  1044,  1091,
     295,   235,  1015,  1058,  1016,   278,   296,   236,   237,   544,
    1017,   238,   239,   240,   241,   242,  1018,  1019,   273,   243,
    1020,  1021,  1022,  1023,  1024,   244,   245,   246,  1025,   247,
     248,   258,   982,  1047,  1026,  1027,  1028,  1068,  1029,  1030,
    1036,  1035,  1002,   611,  1069,   637,  1046,  1076,  1006,  1005,
    1140,   634,  1008,  1101,   630,   613,  1007,  1100,   891,  1067,
     622,  1143,  1084,  1010,   881,   653,  1009,  1079,   754,   753,
    1147,   654,  1169,   657,  1066,  1182,  1065,     0,     0,  1097,
     272,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    1011,     0,     0,     0,     0,  1050,     0,     0,     0,     0,
    1131,     0,  1052,  1040,     0,  1088,     0,     0,  1054,     0,
       0,     0,     0,  1012,     0,     0,  1013,  1034,  1090,     0,
       0,  1031,     0,     0,     0,     0,  1051,     0,     0,     0,
       0,     0,     0,     0,     0,     0,  1089,     0,     0,     0,
    1041,     0,     0,     0,     0,  1055,     0,     0,     0,     0,
       0,     0,     0,  1039,     0,  1091,     0,     0,  1053,  1014,
    1042,     0,     0,     0,     0,  1056,  1043,     0,     0,     0,
       0,  1057,  1044,     0,     0,     0,  1015,  1058,  1016,     0,
       0,     0,     0,     0,  1017,     0,     0,     0,     0,     0,
    1018,  1019,     0,     0,  1020,  1021,  1022,  1023,  1024,     0,
       0,     0,  1025,     0,     0,     0,     0,     0,  1026,  1027,
    1028,     0,  1029,  1030,  1036,  1035
  };

  const short
  Dhcp4Parser::yycheck_[] =
  {
      70,    71,    72,    73,    74,    75,    81,    77,    78,    79,
      80,    73,    78,    76,    78,    72,    73,    74,    75,   671,
      77,    78,   936,    80,   936,   936,    73,    10,   608,    73,
       7,    74,    18,     5,   614,     7,    81,     9,    77,    78,
      15,    16,   121,   122,    19,    68,     3,    22,    93,    94,
      95,     8,    72,    73,    74,    75,     0,    77,    78,   187,
      80,   106,   121,   122,   109,     3,    73,    74,    75,    80,
       8,     3,    73,    73,     7,    75,     8,     3,     3,    73,
       7,    75,     8,     8,     7,    73,     7,    75,     7,    73,
       3,    73,    28,    29,    30,     8,     3,    73,    94,    95,
      34,     8,     3,    73,    73,     6,   161,    73,    73,    73,
      73,    73,     3,     3,     7,    73,     3,     8,     8,    94,
      95,    73,    73,    73,     7,    73,    73,    73,   187,    74,
       7,     3,   154,   155,   156,   157,     8,     6,     3,   135,
     136,   137,   187,     8,    80,    81,    82,     3,    82,     7,
      84,    85,     8,     7,    88,    89,    90,     7,    94,    95,
      94,    95,   111,   112,   113,   114,   152,   116,   190,     7,
     163,   107,   108,   166,   167,   168,   169,   160,     4,     3,
      11,     3,     6,    14,    94,    95,     8,   170,   171,   172,
       3,   187,    23,     6,    25,    26,    27,    28,    29,    30,
      31,    32,    33,     8,   187,     3,  1120,     3,  1120,  1120,
       8,     3,   187,     4,     6,   187,   188,   189,   190,     3,
       3,     8,   132,   133,     8,     8,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,     4,     3,     3,    80,
      81,   187,     8,   187,   124,   125,   126,   127,   128,   129,
      91,     3,     3,    94,    95,     3,     8,     8,    99,     4,
       8,     3,   924,   104,   105,    82,     8,   187,     3,   110,
       3,     3,     8,     8,     4,     8,     8,    94,    95,   120,
      17,    18,   123,    82,    83,    84,    85,    86,    87,   130,
     131,    12,    13,   134,     3,    94,    95,   138,     3,     8,
       3,    20,    21,     8,     4,     8,    26,    27,    28,    29,
      30,   100,   101,   102,   103,   118,   119,   158,   159,     4,
     161,    35,    36,    37,    38,     4,     4,     4,     4,   409,
       4,     4,     4,     4,     4,     4,     4,    57,    58,    59,
      60,    61,    62,    63,    64,   162,   187,   164,   165,    69,
      70,    71,    72,    73,    74,    75,     4,    77,    78,    79,
       4,    81,     4,     4,     4,     4,   399,   400,     4,     3,
     187,     8,    92,     4,    94,    95,    96,    97,    98,    99,
       4,   461,     3,     8,     4,     4,   106,   467,   187,   109,
     110,     4,     4,     4,     4,     4,   187,   117,     4,   479,
     467,     4,   482,     4,     4,     4,     4,   479,     4,     4,
     190,   190,   479,   493,   190,   482,     4,     4,     4,     4,
       4,     4,   479,   503,   188,   479,   493,   188,   508,   482,
     188,   188,   508,   188,   508,   189,   503,   467,   158,   159,
     190,   508,   189,     4,   188,   530,     4,   188,   528,   479,
     188,   190,   482,     4,   503,     4,   190,     4,     4,   508,
       4,   528,   479,   493,   190,   482,   190,   187,   479,   479,
       4,     4,     4,   503,     4,   479,   493,     4,   508,     4,
       4,   479,     4,   493,     4,   479,   188,   479,     4,   493,
       4,     4,     4,   479,   190,   493,     4,     4,   528,   479,
     479,     4,     4,   479,   479,   479,   479,   479,   541,   542,
     543,   479,  1102,     4,     4,     4,     4,   479,   479,   479,
       4,   479,   479,   479,    34,     4,     4,   482,   188,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,   173,   174,   175,
     176,   177,   178,   179,   180,   181,   182,   183,   184,   185,
     186,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,    82,     4,     4,   660,     4,     4,     4,   659,
     188,     4,     4,   190,     4,   665,   190,     4,   190,     4,
     153,     4,     4,   190,   188,   188,   188,     4,   665,     4,
     190,   190,     4,   636,     4,    26,    27,    28,    29,    30,
       4,     4,     4,   188,    28,    29,    30,     4,     7,   699,
     187,   701,     7,     7,     7,   658,     7,   187,   187,     7,
       7,     5,   699,   700,   701,   665,    57,    58,    59,    60,
      61,    62,    63,    64,   187,   187,   187,     5,    69,    70,
      71,    72,    73,    74,    75,    76,     5,     5,     5,   187,
      81,    82,    94,    95,     7,     5,     5,    81,     5,   699,
     700,   701,     5,    94,    95,     7,    97,   187,    99,     7,
      94,    95,     7,     7,     5,   106,   187,   187,   109,     5,
     187,   105,   187,   187,     5,   187,   117,   111,   112,   113,
     114,   115,   116,     7,   118,   187,   187,   139,   140,   141,
     142,   143,   144,   145,   146,   147,   148,   149,   150,   151,
     187,   187,   187,   187,   187,   187,   158,   159,   187,   187,
     187,   187,   187,   187,   187,   187,   187,   158,   159,   187,
     187,   187,   187,   187,     5,    24,     8,     7,     7,     7,
       7,     7,     7,     7,     7,   187,     7,     7,   187,     4,
       4,     4,     4,     4,     4,     4,   187,     4,     4,     4,
       4,     4,     3,   187,     6,     3,     6,     6,     3,     6,
       3,     3,     6,     3,   187,     6,     3,     6,     4,     4,
       4,     4,     4,     4,     4,     3,   187,     6,     4,     6,
       4,     4,     4,     4,   190,     4,   188,     4,   188,     4,
       4,   190,   188,   188,     4,   188,   188,   188,     4,   188,
     190,   188,   188,   188,   188,   188,   188,     4,   188,   190,
       4,     6,     3,   187,     4,   187,   187,   187,     4,     8,
       8,   187,   187,   187,     8,     3,     8,   927,     4,   187,
     930,   187,   187,   933,     4,   927,   936,   933,   187,   933,
     927,   941,     4,   930,   944,   188,   933,   947,   941,   936,
     927,   190,     4,   927,   941,   187,     5,   944,   187,   936,
     960,   930,   936,   936,   933,     7,     4,   936,     4,   969,
       4,     4,   941,   960,   190,   975,   188,   927,   188,   966,
     930,     4,   969,   933,   187,   187,   936,   461,   975,   649,
     927,   941,   665,   580,   944,   467,   927,   927,   926,   936,
     969,   750,   975,   927,   941,   936,   936,   944,   659,   927,
     960,   941,   936,   927,   944,   927,   966,   941,   936,   969,
     944,   927,   936,   941,   936,   975,   944,   927,   927,   409,
     936,   927,   927,   927,   927,   927,   936,   936,   975,   927,
     936,   936,   936,   936,   936,   927,   927,   927,   936,   927,
     927,   927,   900,   939,   936,   936,   936,   947,   936,   936,
     936,   936,   921,   479,   949,   511,   938,   956,   929,   927,
    1120,   508,   932,   977,   503,   482,   930,   975,   721,   946,
     493,  1125,   966,   935,   701,   528,   933,   960,   664,   660,
    1135,   530,  1155,   534,   944,  1175,   942,    -1,    -1,   970,
     975,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    1120,    -1,    -1,    -1,    -1,  1125,    -1,    -1,    -1,    -1,
    1083,    -1,  1125,  1120,    -1,  1135,    -1,    -1,  1125,    -1,
      -1,    -1,    -1,  1120,    -1,    -1,  1120,  1120,  1135,    -1,
      -1,  1120,    -1,    -1,    -1,    -1,  1125,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,  1135,    -1,    -1,    -1,
    1120,    -1,    -1,    -1,    -1,  1125,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,  1120,    -1,  1135,    -1,    -1,  1125,  1120,
    1120,    -1,    -1,    -1,    -1,  1125,  1120,    -1,    -1,    -1,
      -1,  1125,  1120,    -1,    -1,    -1,  1120,  1125,  1120,    -1,
      -1,    -1,    -1,    -1,  1120,    -1,    -1,    -1,    -1,    -1,
    1120,  1120,    -1,    -1,  1120,  1120,  1120,  1120,  1120,    -1,
      -1,    -1,  1120,    -1,    -1,    -1,    -1,    -1,  1120,  1120,
    1120,    -1,  1120,  1120,  1120,  1120
  };

  const short
  Dhcp4Parser::yystos_[] =
  {
       0,   173,   174,   175,   176,   177,   178,   179,   180,   181,
     182,   183,   184,   185,   186,   192,   193,   194,   195,   196,
     197,   198,   199,   200,   201,   202,   203,   204,   205,   206,
       0,     5,     7,     9,   187,   188,   189,   190,   207,   208,
     209,   214,     7,   223,     7,   229,     7,   268,     7,   366,
       7,   446,     7,   462,     7,   398,     7,   404,     7,   428,
       7,   342,     7,   527,     7,   573,     7,   564,   215,   210,
     224,   230,   269,   367,   447,   463,   399,   405,   429,   343,
     528,   574,   565,   207,   216,   217,   187,   212,   213,    10,
     160,   170,   171,   172,   187,   222,   225,   226,   227,   556,
     558,   560,   571,    11,    14,    23,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    69,    70,    71,
      72,    73,    74,    75,    76,    80,    81,    91,    94,    95,
      99,   104,   105,   110,   120,   123,   130,   131,   134,   138,
     158,   159,   161,   222,   231,   232,   233,   234,   235,   236,
     237,   238,   239,   240,   241,   242,   244,   245,   246,   247,
     248,   249,   250,   253,   255,   257,   259,   261,   262,   263,
     264,   279,   281,   287,   289,   327,   336,   350,   360,   384,
     388,   396,   422,   452,   454,   456,   467,   469,   471,   494,
     506,   507,   515,   525,   562,   577,    15,    16,    19,    22,
     222,   266,   267,   270,   272,   275,   278,   452,   454,    77,
      78,    79,    92,    96,    97,    98,   106,   109,   117,   222,
     233,   234,   235,   236,   237,   238,   239,   240,   245,   246,
     247,   248,   249,   250,   253,   255,   257,   259,   261,   368,
     369,   370,   372,   374,   376,   378,   380,   382,   384,   387,
     422,   440,   452,   454,   456,   467,   469,   471,   491,    93,
     222,   380,   382,   422,   448,   449,   450,   452,   454,   105,
     111,   112,   113,   114,   115,   116,   118,   222,   422,   452,
     454,   464,   465,   466,   467,   469,   471,   473,   477,   479,
     481,   483,   485,   487,   489,   396,    34,    82,    84,    85,
      88,    89,    90,   222,   307,   406,   407,   408,   409,   410,
     411,   412,   414,   416,   418,   419,   421,   452,   454,    83,
      86,    87,   222,   307,   410,   416,   430,   431,   432,   433,
     434,   436,   437,   438,   439,   452,   454,   121,   122,   222,
     344,   345,   346,   348,   139,   140,   141,   142,   143,   144,
     145,   146,   147,   148,   149,   150,   151,   158,   159,   222,
     452,   454,   529,   530,   531,   532,   534,   535,   537,   538,
     539,   542,   544,   546,   547,   548,   550,   552,   554,   575,
     576,   577,    12,    13,   566,   567,   568,   570,     6,     3,
       4,     8,     3,   228,   572,   557,   559,   561,     4,     3,
       8,   563,   265,   282,     4,     4,     4,   468,   470,   472,
     280,   288,   290,     4,     4,     4,     4,     4,     4,     4,
       4,     4,   243,     4,     4,     4,     4,     4,   251,   254,
     256,     4,   361,   397,   423,   389,   453,   455,   385,   328,
     495,   457,   337,   351,     4,   508,   516,   526,   258,   260,
     578,     3,     8,   271,   273,   276,     4,     3,     8,   373,
     375,   377,   441,   371,   379,     4,   383,   381,   492,     3,
       8,   451,     3,     8,   490,   478,   480,   484,   482,   488,
     486,   474,     8,     3,     8,   413,   308,     4,   417,   415,
     420,     4,     8,     3,   435,     4,     4,     8,     3,   347,
     349,     3,     8,     4,   545,   533,     4,   536,     4,     4,
     540,   543,     4,     4,   549,   551,   553,   555,     3,     8,
       3,     8,   569,     4,     3,     8,   207,   207,   187,     4,
       4,     4,     4,     4,   226,     4,     4,     4,   190,   190,
     190,     4,     4,     4,     4,     4,     4,   188,   188,   188,
     188,   188,   190,   189,   189,   188,     4,   188,   188,   190,
     190,   190,     4,     4,     4,   190,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,   188,     4,
       4,     4,     4,     4,     4,   232,     4,     4,     4,   190,
     267,     4,     4,     4,     4,     4,     4,   188,     4,     4,
       4,   369,     4,   449,     4,     4,     4,     4,     4,     4,
       4,     4,   466,     4,     4,   188,     4,     4,     4,   190,
     408,     4,   190,   190,   432,     4,     4,   345,   190,     4,
       4,   188,     4,   188,   188,     4,     4,   190,   190,     4,
       4,     4,     4,   530,   576,     4,   188,   567,     4,     7,
       7,   207,   207,   207,     7,     7,     7,   187,   187,   187,
       7,     7,     5,   187,   154,   155,   156,   157,   190,   252,
     187,   187,     5,     5,     5,     5,   209,   211,   187,   100,
     101,   102,   103,   386,     5,     5,     5,     5,     7,     7,
       7,     7,   187,   187,     5,     5,   218,    17,    18,   274,
      20,    21,   277,   187,   187,   187,     5,   187,   187,   218,
     187,     7,   187,   218,   187,   187,   187,   187,   187,   187,
     187,   187,   187,   187,   187,   187,   187,   187,   207,   187,
     187,   187,    18,   152,   541,   153,   252,   187,   187,   187,
       5,   207,   231,   575,   566,   266,    24,   283,   284,   285,
      34,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    51,    52,    53,    54,    55,    56,   222,
     295,   296,   297,   300,   302,   304,   306,   307,   309,   310,
     311,   312,   313,   314,   315,   316,   318,   320,   322,   324,
     325,   326,   295,     7,   291,   292,   293,     7,   362,   363,
     364,     7,   400,   401,   402,     7,   424,   425,   426,     7,
     390,   391,   392,   111,   112,   113,   114,   116,   329,   330,
     331,   332,   333,   334,   335,     7,   496,   497,     7,   458,
     459,   460,     7,   338,   339,   340,   124,   125,   126,   127,
     128,   129,   352,   353,   354,   355,   356,   357,   358,   359,
     132,   133,   222,   452,   454,   509,   510,   511,   513,   135,
     136,   137,   187,   452,   454,   517,   518,   519,   520,   522,
     523,   529,     7,   579,   580,   219,     7,   442,   443,   444,
     119,   473,   475,   493,   291,     8,     8,     8,     8,   286,
       3,     8,   298,   301,   303,   305,     4,     4,     4,     4,
       4,   317,   319,   321,   323,     4,     4,     4,     4,     4,
       4,     3,     8,     8,   294,     6,     3,   365,     6,     3,
     403,     6,     3,   427,     6,     3,   393,     6,     3,     3,
       6,   498,     3,     6,   461,     6,     3,   341,     6,     3,
       4,     4,     4,     4,     4,     4,     3,     8,   512,   514,
       3,     8,     4,   521,     4,   524,     3,     8,     8,   581,
       3,     6,   187,   220,   221,   445,     6,     3,   476,     8,
       6,     4,   284,     4,     4,     4,     4,   188,   190,   188,
     190,   188,     4,     4,     4,     4,   188,   188,   188,   188,
     190,   188,   296,   295,   293,   368,   364,   406,   402,   430,
     426,   222,   233,   234,   235,   236,   237,   238,   239,   240,
     245,   246,   247,   248,   249,   250,   253,   255,   257,   259,
     261,   307,   360,   378,   380,   382,   384,   394,   395,   422,
     452,   454,   467,   469,   471,   491,   392,   330,   107,   108,
     222,   307,   396,   422,   452,   454,   467,   469,   471,   499,
     500,   501,   502,   503,   505,   497,   464,   460,   344,   340,
     188,   188,   188,   188,   188,   188,   353,     4,     4,   510,
     190,     4,   188,     4,   518,   162,   164,   165,   222,   307,
     452,   454,   582,   583,   584,   585,   587,   580,     6,     3,
     448,   444,     4,   187,    35,    36,    37,    38,   299,   187,
     187,   187,   187,   187,   187,   187,     8,     8,     8,     8,
       3,     8,   504,     4,     8,     3,     8,     8,   187,   187,
     187,   207,   588,     4,   586,     3,     8,   187,     8,   218,
     395,     4,   190,   501,     4,   188,     4,   583,   187,     5,
     187,     7,   589,   590,   591,     3,     6,   163,   166,   167,
     168,   169,   592,   593,   594,   596,   597,   598,   599,   590,
     595,     4,     4,     4,   600,     3,     8,     4,   190,   188,
     188,     4,   593,   187,   187
  };

  const short
  Dhcp4Parser::yyr1_[] =
  {
       0,   191,   193,   192,   194,   192,   195,   192,   196,   192,
     197,   192,   198,   192,   199,   192,   200,   192,   201,   192,
     202,   192,   203,   192,   204,   192,   205,   192,   206,   192,
     207,   207,   207,   207,   207,   207,   207,   208,   210,   209,
     211,   212,   212,   213,   213,   215,   214,   216,   216,   217,
     217,   219,   218,   220,   220,   221,   221,   222,   224,   223,
     225,   225,   226,   226,   226,   226,   226,   226,   228,   227,
     230,   229,   231,   231,   232,   232,   232,   232,   232,   232,
     232,   232,   232,   232,   232,   232,   232,   232,   232,   232,
     232,   232,   232,   232,   232,   232,   232,   232,   232,   232,
     232,   232,   232,   232,   232,   232,   232,   232,   232,   232,
     232,   232,   232,   232,   232,   232,   232,   232,   232,   232,
     232,   232,   232,   232,   232,   233,   234,   235,   236,   237,
     238,   239,   240,   241,   243,   242,   244,   245,   246,   247,
     248,   249,   251,   250,   252,   252,   252,   252,   252,   254,
     253,   256,   255,   258,   257,   260,   259,   261,   262,   263,
     265,   264,   266,   266,   267,   267,   267,   267,   267,   267,
     267,   269,   268,   271,   270,   273,   272,   274,   274,   276,
     275,   277,   277,   278,   280,   279,   282,   281,   283,   283,
     284,   286,   285,   288,   287,   290,   289,   291,   291,   292,
     292,   294,   293,   295,   295,   296,   296,   296,   296,   296,
     296,   296,   296,   296,   296,   296,   296,   296,   296,   296,
     296,   296,   296,   296,   296,   296,   298,   297,   299,   299,
     299,   299,   301,   300,   303,   302,   305,   304,   306,   308,
     307,   309,   310,   311,   312,   313,   314,   315,   317,   316,
     319,   318,   321,   320,   323,   322,   324,   325,   326,   328,
     327,   329,   329,   330,   330,   330,   330,   330,   331,   332,
     333,   334,   335,   337,   336,   338,   338,   339,   339,   341,
     340,   343,   342,   344,   344,   344,   345,   345,   347,   346,
     349,   348,   351,   350,   352,   352,   353,   353,   353,   353,
     353,   353,   354,   355,   356,   357,   358,   359,   361,   360,
     362,   362,   363,   363,   365,   364,   367,   366,   368,   368,
     369,   369,   369,   369,   369,   369,   369,   369,   369,   369,
     369,   369,   369,   369,   369,   369,   369,   369,   369,   369,
     369,   369,   369,   369,   369,   369,   369,   369,   369,   369,
     369,   369,   369,   369,   369,   369,   369,   369,   371,   370,
     373,   372,   375,   374,   377,   376,   379,   378,   381,   380,
     383,   382,   385,   384,   386,   386,   386,   386,   387,   389,
     388,   390,   390,   391,   391,   393,   392,   394,   394,   395,
     395,   395,   395,   395,   395,   395,   395,   395,   395,   395,
     395,   395,   395,   395,   395,   395,   395,   395,   395,   395,
     395,   395,   395,   395,   395,   395,   395,   395,   395,   395,
     395,   395,   397,   396,   399,   398,   400,   400,   401,   401,
     403,   402,   405,   404,   406,   406,   407,   407,   408,   408,
     408,   408,   408,   408,   408,   408,   408,   408,   409,   410,
     411,   413,   412,   415,   414,   417,   416,   418,   420,   419,
     421,   423,   422,   424,   424,   425,   425,   427,   426,   429,
     428,   430,   430,   431,   431,   432,   432,   432,   432,   432,
     432,   432,   432,   432,   433,   435,   434,   436,   437,   438,
     439,   441,   440,   442,   442,   443,   443,   445,   444,   447,
     446,   448,   448,   449,   449,   449,   449,   449,   449,   449,
     451,   450,   453,   452,   455,   454,   457,   456,   458,   458,
     459,   459,   461,   460,   463,   462,   464,   464,   465,   465,
     466,   466,   466,   466,   466,   466,   466,   466,   466,   466,
     466,   466,   466,   466,   466,   468,   467,   470,   469,   472,
     471,   474,   473,   476,   475,   478,   477,   480,   479,   482,
     481,   484,   483,   486,   485,   488,   487,   490,   489,   492,
     491,   493,   493,   495,   494,   496,   496,   498,   497,   499,
     499,   500,   500,   501,   501,   501,   501,   501,   501,   501,
     501,   501,   501,   501,   502,   504,   503,   505,   506,   508,
     507,   509,   509,   510,   510,   510,   510,   510,   512,   511,
     514,   513,   516,   515,   517,   517,   518,   518,   518,   518,
     518,   518,   519,   521,   520,   522,   524,   523,   526,   525,
     528,   527,   529,   529,   530,   530,   530,   530,   530,   530,
     530,   530,   530,   530,   530,   530,   530,   530,   530,   530,
     530,   530,   531,   533,   532,   534,   536,   535,   537,   538,
     540,   539,   541,   541,   543,   542,   545,   544,   546,   547,
     549,   548,   551,   550,   553,   552,   555,   554,   557,   556,
     559,   558,   561,   560,   563,   562,   565,   564,   566,   566,
     567,   567,   569,   568,   570,   572,   571,   574,   573,   575,
     575,   576,   578,   577,   579,   579,   581,   580,   582,   582,
     583,   583,   583,   583,   583,   583,   583,   584,   586,   585,
     588,   587,   589,   589,   591,   590,   592,   592,   593,   593,
     593,   593,   593,   595,   594,   596,   597,   598,   600,   599
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
       1,     1,     1,     1,     1,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     0,     4,     3,     3,     3,     3,
       3,     3,     0,     4,     1,     1,     1,     1,     1,     0,
       4,     0,     4,     0,     4,     0,     4,     3,     3,     3,
       0,     6,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     0,     4,     0,     4,     0,     4,     1,     1,     0,
       4,     1,     1,     3,     0,     6,     0,     6,     1,     3,
       1,     0,     4,     0,     6,     0,     6,     0,     1,     1,
       3,     0,     4,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     0,     4,     1,     1,
       1,     1,     0,     4,     0,     4,     0,     4,     3,     0,
       4,     3,     3,     3,     3,     3,     3,     3,     0,     4,
       0,     4,     0,     4,     0,     4,     3,     3,     3,     0,
       6,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     0,     6,     0,     1,     1,     3,     0,
       4,     0,     4,     1,     3,     1,     1,     1,     0,     4,
       0,     4,     0,     6,     1,     3,     1,     1,     1,     1,
       1,     1,     3,     3,     3,     3,     3,     3,     0,     6,
       0,     1,     1,     3,     0,     4,     0,     4,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     1,     1,     1,     1,     3,     0,
       6,     0,     1,     1,     3,     0,     4,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     6,     0,     4,     0,     1,     1,     3,
       0,     4,     0,     4,     0,     1,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     3,
       1,     0,     4,     0,     4,     0,     4,     1,     0,     4,
       3,     0,     6,     0,     1,     1,     3,     0,     4,     0,
       4,     0,     1,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     1,     1,     3,
       3,     0,     6,     0,     1,     1,     3,     0,     4,     0,
       4,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     0,     4,     0,     4,     0,     6,     0,     1,
       1,     3,     0,     4,     0,     4,     0,     1,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       6,     1,     1,     0,     6,     1,     3,     0,     4,     0,
       1,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     3,     3,     0,
       6,     1,     3,     1,     1,     1,     1,     1,     0,     4,
       0,     4,     0,     6,     1,     3,     1,     1,     1,     1,
       1,     1,     3,     0,     4,     3,     0,     4,     0,     6,
       0,     4,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     3,     0,     4,     3,     0,     4,     3,     3,
       0,     4,     1,     1,     0,     4,     0,     4,     3,     3,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     6,     0,     4,     1,     3,
       1,     1,     0,     6,     3,     0,     6,     0,     4,     1,
       3,     1,     0,     6,     1,     3,     0,     4,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     3,     0,     4,
       0,     6,     1,     3,     0,     4,     1,     3,     1,     1,
       1,     1,     1,     0,     4,     3,     3,     3,     0,     4
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
       0,   278,   278,   278,   279,   279,   280,   280,   281,   281,
     282,   282,   283,   283,   284,   284,   285,   285,   286,   286,
     287,   287,   288,   288,   289,   289,   290,   290,   291,   291,
     299,   300,   301,   302,   303,   304,   305,   308,   313,   313,
     324,   327,   328,   331,   335,   342,   342,   349,   350,   353,
     357,   364,   364,   371,   372,   375,   379,   390,   400,   400,
     416,   417,   421,   422,   423,   424,   425,   426,   429,   429,
     444,   444,   453,   454,   459,   460,   461,   462,   463,   464,
     465,   466,   467,   468,   469,   470,   471,   472,   473,   474,
     475,   476,   477,   478,   479,   480,   481,   482,   483,   484,
     485,   486,   487,   488,   489,   490,   491,   492,   493,   494,
     495,   496,   497,   498,   499,   500,   501,   502,   503,   504,
     505,   506,   507,   508,   509,   512,   517,   522,   527,   532,
     537,   542,   547,   552,   557,   557,   565,   570,   575,   580,
     585,   590,   595,   595,   603,   606,   609,   612,   615,   621,
     621,   629,   629,   637,   637,   645,   645,   653,   658,   663,
     668,   668,   679,   680,   683,   684,   685,   686,   687,   688,
     689,   692,   692,   701,   701,   711,   711,   718,   719,   722,
     722,   729,   731,   735,   741,   741,   753,   753,   763,   764,
     766,   768,   768,   786,   786,   798,   798,   808,   809,   812,
     813,   816,   816,   826,   827,   830,   831,   832,   833,   834,
     835,   836,   837,   838,   839,   840,   841,   842,   843,   844,
     845,   846,   847,   848,   849,   850,   853,   853,   860,   861,
     862,   863,   866,   866,   874,   874,   882,   882,   890,   895,
     895,   903,   908,   913,   918,   923,   928,   933,   938,   938,
     946,   946,   954,   954,   962,   962,   970,   975,   980,   986,
     986,   996,   997,  1000,  1001,  1002,  1003,  1004,  1007,  1012,
    1017,  1022,  1027,  1032,  1032,  1042,  1043,  1046,  1047,  1050,
    1050,  1060,  1060,  1070,  1071,  1072,  1075,  1076,  1079,  1079,
    1087,  1087,  1095,  1095,  1106,  1107,  1110,  1111,  1112,  1113,
    1114,  1115,  1118,  1123,  1128,  1133,  1138,  1143,  1151,  1151,
    1164,  1165,  1168,  1169,  1176,  1176,  1202,  1202,  1213,  1214,
    1218,  1219,  1220,  1221,  1222,  1223,  1224,  1225,  1226,  1227,
    1228,  1229,  1230,  1231,  1232,  1233,  1234,  1235,  1236,  1237,
    1238,  1239,  1240,  1241,  1242,  1243,  1244,  1245,  1246,  1247,
    1248,  1249,  1250,  1251,  1252,  1253,  1254,  1255,  1258,  1258,
    1266,  1266,  1274,  1274,  1282,  1282,  1290,  1290,  1298,  1298,
    1306,  1306,  1316,  1316,  1323,  1324,  1325,  1326,  1329,  1336,
    1336,  1347,  1348,  1352,  1353,  1356,  1356,  1364,  1365,  1368,
    1369,  1370,  1371,  1372,  1373,  1374,  1375,  1376,  1377,  1378,
    1379,  1380,  1381,  1382,  1383,  1384,  1385,  1386,  1387,  1388,
    1389,  1390,  1391,  1392,  1393,  1394,  1395,  1396,  1397,  1398,
    1399,  1400,  1407,  1407,  1420,  1420,  1429,  1430,  1433,  1434,
    1439,  1439,  1454,  1454,  1468,  1469,  1472,  1473,  1476,  1477,
    1478,  1479,  1480,  1481,  1482,  1483,  1484,  1485,  1488,  1490,
    1495,  1497,  1497,  1505,  1505,  1513,  1513,  1521,  1523,  1523,
    1531,  1540,  1540,  1552,  1553,  1558,  1559,  1564,  1564,  1576,
    1576,  1588,  1589,  1594,  1595,  1600,  1601,  1602,  1603,  1604,
    1605,  1606,  1607,  1608,  1611,  1613,  1613,  1621,  1623,  1625,
    1630,  1638,  1638,  1650,  1651,  1654,  1655,  1658,  1658,  1668,
    1668,  1678,  1679,  1682,  1683,  1684,  1685,  1686,  1687,  1688,
    1691,  1691,  1699,  1699,  1724,  1724,  1754,  1754,  1764,  1765,
    1768,  1769,  1772,  1772,  1781,  1781,  1790,  1791,  1794,  1795,
    1799,  1800,  1801,  1802,  1803,  1804,  1805,  1806,  1807,  1808,
    1809,  1810,  1811,  1812,  1813,  1816,  1816,  1824,  1824,  1832,
    1832,  1840,  1840,  1848,  1848,  1858,  1858,  1866,  1866,  1874,
    1874,  1882,  1882,  1890,  1890,  1898,  1898,  1906,  1906,  1919,
    1919,  1929,  1930,  1936,  1936,  1946,  1947,  1950,  1950,  1960,
    1961,  1964,  1965,  1968,  1969,  1970,  1971,  1972,  1973,  1974,
    1975,  1976,  1977,  1978,  1981,  1983,  1983,  1991,  2000,  2007,
    2007,  2017,  2018,  2021,  2022,  2023,  2024,  2025,  2028,  2028,
    2036,  2036,  2047,  2047,  2059,  2060,  2063,  2064,  2065,  2066,
    2067,  2068,  2071,  2076,  2076,  2084,  2089,  2089,  2098,  2098,
    2110,  2110,  2120,  2121,  2124,  2125,  2126,  2127,  2128,  2129,
    2130,  2131,  2132,  2133,  2134,  2135,  2136,  2137,  2138,  2139,
    2140,  2141,  2144,  2149,  2149,  2157,  2162,  2162,  2170,  2175,
    2180,  2180,  2188,  2189,  2192,  2192,  2201,  2201,  2210,  2216,
    2222,  2222,  2230,  2230,  2239,  2239,  2248,  2248,  2259,  2259,
    2266,  2266,  2273,  2273,  2280,  2280,  2291,  2291,  2301,  2302,
    2306,  2307,  2310,  2310,  2320,  2330,  2330,  2340,  2340,  2351,
    2352,  2356,  2360,  2360,  2372,  2373,  2377,  2377,  2385,  2386,
    2389,  2390,  2391,  2392,  2393,  2394,  2395,  2398,  2403,  2403,
    2411,  2411,  2421,  2422,  2425,  2425,  2433,  2434,  2437,  2438,
    2439,  2440,  2441,  2444,  2444,  2452,  2457,  2462,  2467,  2467
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
#line 5423 "dhcp4_parser.cc"

#line 2476 "dhcp4_parser.yy"


void
isc::dhcp::Dhcp4Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
