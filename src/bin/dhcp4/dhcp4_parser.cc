// A Bison parser, made by GNU Bison 3.4.1.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2019 Free Software Foundation, Inc.

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


// Suppress unused-variable warnings by "using" E.
#define YYUSE(E) ((void) (E))

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
#line 146 "dhcp4_parser.cc"


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
    :
#if PARSER4_DEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
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
      return yystos_[state];
  }

  Dhcp4Parser::stack_symbol_type::stack_symbol_type ()
  {}

  Dhcp4Parser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state), YY_MOVE (that.location))
  {
    switch (that.type_get ())
    {
      case 196: // value
      case 200: // map_value
      case 247: // socket_type
      case 250: // outbound_interface_value
      case 272: // db_type
      case 359: // hr_mode
      case 508: // ncr_protocol_value
      case 515: // replace_client_name_value
        value.YY_MOVE_OR_COPY< ElementPtr > (YY_MOVE (that.value));
        break;

      case 179: // "boolean"
        value.YY_MOVE_OR_COPY< bool > (YY_MOVE (that.value));
        break;

      case 178: // "floating point"
        value.YY_MOVE_OR_COPY< double > (YY_MOVE (that.value));
        break;

      case 177: // "integer"
        value.YY_MOVE_OR_COPY< int64_t > (YY_MOVE (that.value));
        break;

      case 176: // "constant string"
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
      case 196: // value
      case 200: // map_value
      case 247: // socket_type
      case 250: // outbound_interface_value
      case 272: // db_type
      case 359: // hr_mode
      case 508: // ncr_protocol_value
      case 515: // replace_client_name_value
        value.move< ElementPtr > (YY_MOVE (that.value));
        break;

      case 179: // "boolean"
        value.move< bool > (YY_MOVE (that.value));
        break;

      case 178: // "floating point"
        value.move< double > (YY_MOVE (that.value));
        break;

      case 177: // "integer"
        value.move< int64_t > (YY_MOVE (that.value));
        break;

      case 176: // "constant string"
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
  Dhcp4Parser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    switch (that.type_get ())
    {
      case 196: // value
      case 200: // map_value
      case 247: // socket_type
      case 250: // outbound_interface_value
      case 272: // db_type
      case 359: // hr_mode
      case 508: // ncr_protocol_value
      case 515: // replace_client_name_value
        value.move< ElementPtr > (that.value);
        break;

      case 179: // "boolean"
        value.move< bool > (that.value);
        break;

      case 178: // "floating point"
        value.move< double > (that.value);
        break;

      case 177: // "integer"
        value.move< int64_t > (that.value);
        break;

      case 176: // "constant string"
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
      case 176: // "constant string"
#line 258 "dhcp4_parser.yy"
        { yyoutput << yysym.value.template as < std::string > (); }
#line 408 "dhcp4_parser.cc"
        break;

      case 177: // "integer"
#line 258 "dhcp4_parser.yy"
        { yyoutput << yysym.value.template as < int64_t > (); }
#line 414 "dhcp4_parser.cc"
        break;

      case 178: // "floating point"
#line 258 "dhcp4_parser.yy"
        { yyoutput << yysym.value.template as < double > (); }
#line 420 "dhcp4_parser.cc"
        break;

      case 179: // "boolean"
#line 258 "dhcp4_parser.yy"
        { yyoutput << yysym.value.template as < bool > (); }
#line 426 "dhcp4_parser.cc"
        break;

      case 196: // value
#line 258 "dhcp4_parser.yy"
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 432 "dhcp4_parser.cc"
        break;

      case 200: // map_value
#line 258 "dhcp4_parser.yy"
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 438 "dhcp4_parser.cc"
        break;

      case 247: // socket_type
#line 258 "dhcp4_parser.yy"
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 444 "dhcp4_parser.cc"
        break;

      case 250: // outbound_interface_value
#line 258 "dhcp4_parser.yy"
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 450 "dhcp4_parser.cc"
        break;

      case 272: // db_type
#line 258 "dhcp4_parser.yy"
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 456 "dhcp4_parser.cc"
        break;

      case 359: // hr_mode
#line 258 "dhcp4_parser.yy"
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 462 "dhcp4_parser.cc"
        break;

      case 508: // ncr_protocol_value
#line 258 "dhcp4_parser.yy"
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 468 "dhcp4_parser.cc"
        break;

      case 515: // replace_client_name_value
#line 258 "dhcp4_parser.yy"
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 474 "dhcp4_parser.cc"
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
    // State.
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
    YYCDEBUG << "Entering state " << yystack_[0].state << '\n';

    // Accept?
    if (yystack_[0].state == yyfinal_)
      YYACCEPT;

    goto yybackup;


  /*-----------.
  | yybackup.  |
  `-----------*/
  yybackup:
    // Try to take a decision without lookahead.
    yyn = yypact_[yystack_[0].state];
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
      goto yydefault;

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
    yypush_ ("Shifting", yyn, YY_MOVE (yyla));
    goto yynewstate;


  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[yystack_[0].state];
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
      case 196: // value
      case 200: // map_value
      case 247: // socket_type
      case 250: // outbound_interface_value
      case 272: // db_type
      case 359: // hr_mode
      case 508: // ncr_protocol_value
      case 515: // replace_client_name_value
        yylhs.value.emplace< ElementPtr > ();
        break;

      case 179: // "boolean"
        yylhs.value.emplace< bool > ();
        break;

      case 178: // "floating point"
        yylhs.value.emplace< double > ();
        break;

      case 177: // "integer"
        yylhs.value.emplace< int64_t > ();
        break;

      case 176: // "constant string"
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
#line 267 "dhcp4_parser.yy"
    { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 741 "dhcp4_parser.cc"
    break;

  case 4:
#line 268 "dhcp4_parser.yy"
    { ctx.ctx_ = ctx.CONFIG; }
#line 747 "dhcp4_parser.cc"
    break;

  case 6:
#line 269 "dhcp4_parser.yy"
    { ctx.ctx_ = ctx.DHCP4; }
#line 753 "dhcp4_parser.cc"
    break;

  case 8:
#line 270 "dhcp4_parser.yy"
    { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 759 "dhcp4_parser.cc"
    break;

  case 10:
#line 271 "dhcp4_parser.yy"
    { ctx.ctx_ = ctx.SUBNET4; }
#line 765 "dhcp4_parser.cc"
    break;

  case 12:
#line 272 "dhcp4_parser.yy"
    { ctx.ctx_ = ctx.POOLS; }
#line 771 "dhcp4_parser.cc"
    break;

  case 14:
#line 273 "dhcp4_parser.yy"
    { ctx.ctx_ = ctx.RESERVATIONS; }
#line 777 "dhcp4_parser.cc"
    break;

  case 16:
#line 274 "dhcp4_parser.yy"
    { ctx.ctx_ = ctx.DHCP4; }
#line 783 "dhcp4_parser.cc"
    break;

  case 18:
#line 275 "dhcp4_parser.yy"
    { ctx.ctx_ = ctx.OPTION_DEF; }
#line 789 "dhcp4_parser.cc"
    break;

  case 20:
#line 276 "dhcp4_parser.yy"
    { ctx.ctx_ = ctx.OPTION_DATA; }
#line 795 "dhcp4_parser.cc"
    break;

  case 22:
#line 277 "dhcp4_parser.yy"
    { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 801 "dhcp4_parser.cc"
    break;

  case 24:
#line 278 "dhcp4_parser.yy"
    { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 807 "dhcp4_parser.cc"
    break;

  case 26:
#line 279 "dhcp4_parser.yy"
    { ctx.ctx_ = ctx.LOGGING; }
#line 813 "dhcp4_parser.cc"
    break;

  case 28:
#line 280 "dhcp4_parser.yy"
    { ctx.ctx_ = ctx.CONFIG_CONTROL; }
#line 819 "dhcp4_parser.cc"
    break;

  case 30:
#line 288 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 825 "dhcp4_parser.cc"
    break;

  case 31:
#line 289 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location))); }
#line 831 "dhcp4_parser.cc"
    break;

  case 32:
#line 290 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 837 "dhcp4_parser.cc"
    break;

  case 33:
#line 291 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 843 "dhcp4_parser.cc"
    break;

  case 34:
#line 292 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 849 "dhcp4_parser.cc"
    break;

  case 35:
#line 293 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 855 "dhcp4_parser.cc"
    break;

  case 36:
#line 294 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 861 "dhcp4_parser.cc"
    break;

  case 37:
#line 297 "dhcp4_parser.yy"
    {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as < ElementPtr > ());
}
#line 870 "dhcp4_parser.cc"
    break;

  case 38:
#line 302 "dhcp4_parser.yy"
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 881 "dhcp4_parser.cc"
    break;

  case 39:
#line 307 "dhcp4_parser.yy"
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 891 "dhcp4_parser.cc"
    break;

  case 40:
#line 313 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 897 "dhcp4_parser.cc"
    break;

  case 43:
#line 320 "dhcp4_parser.yy"
    {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 906 "dhcp4_parser.cc"
    break;

  case 44:
#line 324 "dhcp4_parser.yy"
    {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 916 "dhcp4_parser.cc"
    break;

  case 45:
#line 331 "dhcp4_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 925 "dhcp4_parser.cc"
    break;

  case 46:
#line 334 "dhcp4_parser.yy"
    {
    // list parsing complete. Put any sanity checking here
}
#line 933 "dhcp4_parser.cc"
    break;

  case 49:
#line 342 "dhcp4_parser.yy"
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 942 "dhcp4_parser.cc"
    break;

  case 50:
#line 346 "dhcp4_parser.yy"
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 951 "dhcp4_parser.cc"
    break;

  case 51:
#line 353 "dhcp4_parser.yy"
    {
    // List parsing about to start
}
#line 959 "dhcp4_parser.cc"
    break;

  case 52:
#line 355 "dhcp4_parser.yy"
    {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 968 "dhcp4_parser.cc"
    break;

  case 55:
#line 364 "dhcp4_parser.yy"
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 977 "dhcp4_parser.cc"
    break;

  case 56:
#line 368 "dhcp4_parser.yy"
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 986 "dhcp4_parser.cc"
    break;

  case 57:
#line 379 "dhcp4_parser.yy"
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as < std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 997 "dhcp4_parser.cc"
    break;

  case 58:
#line 389 "dhcp4_parser.yy"
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1008 "dhcp4_parser.cc"
    break;

  case 59:
#line 394 "dhcp4_parser.yy"
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.

    // Dhcp4 is required
    ctx.require("Dhcp4", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
}
#line 1021 "dhcp4_parser.cc"
    break;

  case 68:
#line 418 "dhcp4_parser.yy"
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Dhcp4", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP4);
}
#line 1034 "dhcp4_parser.cc"
    break;

  case 69:
#line 425 "dhcp4_parser.yy"
    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1044 "dhcp4_parser.cc"
    break;

  case 70:
#line 433 "dhcp4_parser.yy"
    {
    // Parse the Dhcp4 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1054 "dhcp4_parser.cc"
    break;

  case 71:
#line 437 "dhcp4_parser.yy"
    {
    // No global parameter is required
    // parsing completed
}
#line 1063 "dhcp4_parser.cc"
    break;

  case 117:
#line 493 "dhcp4_parser.yy"
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1072 "dhcp4_parser.cc"
    break;

  case 118:
#line 498 "dhcp4_parser.yy"
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-valid-lifetime", prf);
}
#line 1081 "dhcp4_parser.cc"
    break;

  case 119:
#line 503 "dhcp4_parser.yy"
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-valid-lifetime", prf);
}
#line 1090 "dhcp4_parser.cc"
    break;

  case 120:
#line 508 "dhcp4_parser.yy"
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1099 "dhcp4_parser.cc"
    break;

  case 121:
#line 513 "dhcp4_parser.yy"
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1108 "dhcp4_parser.cc"
    break;

  case 122:
#line 518 "dhcp4_parser.yy"
    {
    ElementPtr asl(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("allow-static-leases", asl);
}
#line 1117 "dhcp4_parser.cc"
    break;

  case 123:
#line 523 "dhcp4_parser.yy"
    {
    ElementPtr ctt(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("calculate-tee-times", ctt);
}
#line 1126 "dhcp4_parser.cc"
    break;

  case 124:
#line 528 "dhcp4_parser.yy"
    {
    ElementPtr t1(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t1-percent", t1);
}
#line 1135 "dhcp4_parser.cc"
    break;

  case 125:
#line 533 "dhcp4_parser.yy"
    {
    ElementPtr t2(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t2-percent", t2);
}
#line 1144 "dhcp4_parser.cc"
    break;

  case 126:
#line 538 "dhcp4_parser.yy"
    {
    ElementPtr dpp(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1153 "dhcp4_parser.cc"
    break;

  case 127:
#line 543 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1161 "dhcp4_parser.cc"
    break;

  case 128:
#line 545 "dhcp4_parser.yy"
    {
    ElementPtr stag(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-tag", stag);
    ctx.leave();
}
#line 1171 "dhcp4_parser.cc"
    break;

  case 129:
#line 551 "dhcp4_parser.yy"
    {
    ElementPtr echo(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("echo-client-id", echo);
}
#line 1180 "dhcp4_parser.cc"
    break;

  case 130:
#line 556 "dhcp4_parser.yy"
    {
    ElementPtr match(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("match-client-id", match);
}
#line 1189 "dhcp4_parser.cc"
    break;

  case 131:
#line 561 "dhcp4_parser.yy"
    {
    ElementPtr prf(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("authoritative", prf);
}
#line 1198 "dhcp4_parser.cc"
    break;

  case 132:
#line 567 "dhcp4_parser.yy"
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1209 "dhcp4_parser.cc"
    break;

  case 133:
#line 572 "dhcp4_parser.yy"
    {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1219 "dhcp4_parser.cc"
    break;

  case 143:
#line 591 "dhcp4_parser.yy"
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1229 "dhcp4_parser.cc"
    break;

  case 144:
#line 595 "dhcp4_parser.yy"
    {
    // No interfaces config param is required
    // parsing completed
}
#line 1238 "dhcp4_parser.cc"
    break;

  case 145:
#line 600 "dhcp4_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1249 "dhcp4_parser.cc"
    break;

  case 146:
#line 605 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1258 "dhcp4_parser.cc"
    break;

  case 147:
#line 610 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.DHCP_SOCKET_TYPE);
}
#line 1266 "dhcp4_parser.cc"
    break;

  case 148:
#line 612 "dhcp4_parser.yy"
    {
    ctx.stack_.back()->set("dhcp-socket-type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1275 "dhcp4_parser.cc"
    break;

  case 149:
#line 617 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("raw", ctx.loc2pos(yystack_[0].location))); }
#line 1281 "dhcp4_parser.cc"
    break;

  case 150:
#line 618 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("udp", ctx.loc2pos(yystack_[0].location))); }
#line 1287 "dhcp4_parser.cc"
    break;

  case 151:
#line 621 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.OUTBOUND_INTERFACE);
}
#line 1295 "dhcp4_parser.cc"
    break;

  case 152:
#line 623 "dhcp4_parser.yy"
    {
    ctx.stack_.back()->set("outbound-interface", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1304 "dhcp4_parser.cc"
    break;

  case 153:
#line 628 "dhcp4_parser.yy"
    {
    yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("same-as-inbound", ctx.loc2pos(yystack_[0].location)));
}
#line 1312 "dhcp4_parser.cc"
    break;

  case 154:
#line 630 "dhcp4_parser.yy"
    {
    yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("use-routing", ctx.loc2pos(yystack_[0].location)));
    }
#line 1320 "dhcp4_parser.cc"
    break;

  case 155:
#line 634 "dhcp4_parser.yy"
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1329 "dhcp4_parser.cc"
    break;

  case 156:
#line 640 "dhcp4_parser.yy"
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1340 "dhcp4_parser.cc"
    break;

  case 157:
#line 645 "dhcp4_parser.yy"
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1351 "dhcp4_parser.cc"
    break;

  case 158:
#line 652 "dhcp4_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sanity-checks", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SANITY_CHECKS);
}
#line 1362 "dhcp4_parser.cc"
    break;

  case 159:
#line 657 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1371 "dhcp4_parser.cc"
    break;

  case 163:
#line 667 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1379 "dhcp4_parser.cc"
    break;

  case 164:
#line 669 "dhcp4_parser.yy"
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
#line 1399 "dhcp4_parser.cc"
    break;

  case 165:
#line 685 "dhcp4_parser.yy"
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1410 "dhcp4_parser.cc"
    break;

  case 166:
#line 690 "dhcp4_parser.yy"
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1421 "dhcp4_parser.cc"
    break;

  case 167:
#line 697 "dhcp4_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1432 "dhcp4_parser.cc"
    break;

  case 168:
#line 702 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1441 "dhcp4_parser.cc"
    break;

  case 173:
#line 715 "dhcp4_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1451 "dhcp4_parser.cc"
    break;

  case 174:
#line 719 "dhcp4_parser.yy"
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1461 "dhcp4_parser.cc"
    break;

  case 198:
#line 752 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1469 "dhcp4_parser.cc"
    break;

  case 199:
#line 754 "dhcp4_parser.yy"
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1478 "dhcp4_parser.cc"
    break;

  case 200:
#line 759 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1484 "dhcp4_parser.cc"
    break;

  case 201:
#line 760 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1490 "dhcp4_parser.cc"
    break;

  case 202:
#line 761 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1496 "dhcp4_parser.cc"
    break;

  case 203:
#line 762 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1502 "dhcp4_parser.cc"
    break;

  case 204:
#line 765 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1510 "dhcp4_parser.cc"
    break;

  case 205:
#line 767 "dhcp4_parser.yy"
    {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1520 "dhcp4_parser.cc"
    break;

  case 206:
#line 773 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1528 "dhcp4_parser.cc"
    break;

  case 207:
#line 775 "dhcp4_parser.yy"
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1538 "dhcp4_parser.cc"
    break;

  case 208:
#line 781 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1546 "dhcp4_parser.cc"
    break;

  case 209:
#line 783 "dhcp4_parser.yy"
    {
    ElementPtr h(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1556 "dhcp4_parser.cc"
    break;

  case 210:
#line 789 "dhcp4_parser.yy"
    {
    ElementPtr p(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1565 "dhcp4_parser.cc"
    break;

  case 211:
#line 794 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1573 "dhcp4_parser.cc"
    break;

  case 212:
#line 796 "dhcp4_parser.yy"
    {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1583 "dhcp4_parser.cc"
    break;

  case 213:
#line 802 "dhcp4_parser.yy"
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1592 "dhcp4_parser.cc"
    break;

  case 214:
#line 807 "dhcp4_parser.yy"
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1601 "dhcp4_parser.cc"
    break;

  case 215:
#line 812 "dhcp4_parser.yy"
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1610 "dhcp4_parser.cc"
    break;

  case 216:
#line 817 "dhcp4_parser.yy"
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1619 "dhcp4_parser.cc"
    break;

  case 217:
#line 822 "dhcp4_parser.yy"
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("request-timeout", n);
}
#line 1628 "dhcp4_parser.cc"
    break;

  case 218:
#line 827 "dhcp4_parser.yy"
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-keepalive", n);
}
#line 1637 "dhcp4_parser.cc"
    break;

  case 219:
#line 832 "dhcp4_parser.yy"
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-nodelay", n);
}
#line 1646 "dhcp4_parser.cc"
    break;

  case 220:
#line 837 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1654 "dhcp4_parser.cc"
    break;

  case 221:
#line 839 "dhcp4_parser.yy"
    {
    ElementPtr cp(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1664 "dhcp4_parser.cc"
    break;

  case 222:
#line 845 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1672 "dhcp4_parser.cc"
    break;

  case 223:
#line 847 "dhcp4_parser.yy"
    {
    ElementPtr ks(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 1682 "dhcp4_parser.cc"
    break;

  case 224:
#line 853 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1690 "dhcp4_parser.cc"
    break;

  case 225:
#line 855 "dhcp4_parser.yy"
    {
    ElementPtr c(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("consistency", c);
    ctx.leave();
}
#line 1700 "dhcp4_parser.cc"
    break;

  case 226:
#line 861 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1708 "dhcp4_parser.cc"
    break;

  case 227:
#line 863 "dhcp4_parser.yy"
    {
    ElementPtr c(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("serial-consistency", c);
    ctx.leave();
}
#line 1718 "dhcp4_parser.cc"
    break;

  case 228:
#line 869 "dhcp4_parser.yy"
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 1727 "dhcp4_parser.cc"
    break;

  case 229:
#line 874 "dhcp4_parser.yy"
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 1736 "dhcp4_parser.cc"
    break;

  case 230:
#line 879 "dhcp4_parser.yy"
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-row-errors", n);
}
#line 1745 "dhcp4_parser.cc"
    break;

  case 231:
#line 885 "dhcp4_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1756 "dhcp4_parser.cc"
    break;

  case 232:
#line 890 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1765 "dhcp4_parser.cc"
    break;

  case 240:
#line 906 "dhcp4_parser.yy"
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1774 "dhcp4_parser.cc"
    break;

  case 241:
#line 911 "dhcp4_parser.yy"
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1783 "dhcp4_parser.cc"
    break;

  case 242:
#line 916 "dhcp4_parser.yy"
    {
    ElementPtr circuit(new StringElement("circuit-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(circuit);
}
#line 1792 "dhcp4_parser.cc"
    break;

  case 243:
#line 921 "dhcp4_parser.yy"
    {
    ElementPtr client(new StringElement("client-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(client);
}
#line 1801 "dhcp4_parser.cc"
    break;

  case 244:
#line 926 "dhcp4_parser.yy"
    {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 1810 "dhcp4_parser.cc"
    break;

  case 245:
#line 931 "dhcp4_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1821 "dhcp4_parser.cc"
    break;

  case 246:
#line 936 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1830 "dhcp4_parser.cc"
    break;

  case 251:
#line 949 "dhcp4_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1840 "dhcp4_parser.cc"
    break;

  case 252:
#line 953 "dhcp4_parser.yy"
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1850 "dhcp4_parser.cc"
    break;

  case 253:
#line 959 "dhcp4_parser.yy"
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1860 "dhcp4_parser.cc"
    break;

  case 254:
#line 963 "dhcp4_parser.yy"
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1870 "dhcp4_parser.cc"
    break;

  case 260:
#line 978 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1878 "dhcp4_parser.cc"
    break;

  case 261:
#line 980 "dhcp4_parser.yy"
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1888 "dhcp4_parser.cc"
    break;

  case 262:
#line 986 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1896 "dhcp4_parser.cc"
    break;

  case 263:
#line 988 "dhcp4_parser.yy"
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1905 "dhcp4_parser.cc"
    break;

  case 264:
#line 994 "dhcp4_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 1916 "dhcp4_parser.cc"
    break;

  case 265:
#line 999 "dhcp4_parser.yy"
    {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1926 "dhcp4_parser.cc"
    break;

  case 274:
#line 1017 "dhcp4_parser.yy"
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 1935 "dhcp4_parser.cc"
    break;

  case 275:
#line 1022 "dhcp4_parser.yy"
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 1944 "dhcp4_parser.cc"
    break;

  case 276:
#line 1027 "dhcp4_parser.yy"
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 1953 "dhcp4_parser.cc"
    break;

  case 277:
#line 1032 "dhcp4_parser.yy"
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 1962 "dhcp4_parser.cc"
    break;

  case 278:
#line 1037 "dhcp4_parser.yy"
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 1971 "dhcp4_parser.cc"
    break;

  case 279:
#line 1042 "dhcp4_parser.yy"
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 1980 "dhcp4_parser.cc"
    break;

  case 280:
#line 1050 "dhcp4_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet4", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET4);
}
#line 1991 "dhcp4_parser.cc"
    break;

  case 281:
#line 1055 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2000 "dhcp4_parser.cc"
    break;

  case 286:
#line 1075 "dhcp4_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2010 "dhcp4_parser.cc"
    break;

  case 287:
#line 1079 "dhcp4_parser.yy"
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
#line 2036 "dhcp4_parser.cc"
    break;

  case 288:
#line 1101 "dhcp4_parser.yy"
    {
    // Parse the subnet4 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2046 "dhcp4_parser.cc"
    break;

  case 289:
#line 1105 "dhcp4_parser.yy"
    {
    // The subnet subnet4 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2056 "dhcp4_parser.cc"
    break;

  case 322:
#line 1149 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2064 "dhcp4_parser.cc"
    break;

  case 323:
#line 1151 "dhcp4_parser.yy"
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 2074 "dhcp4_parser.cc"
    break;

  case 324:
#line 1157 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2082 "dhcp4_parser.cc"
    break;

  case 325:
#line 1159 "dhcp4_parser.yy"
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface", iface);
    ctx.leave();
}
#line 2092 "dhcp4_parser.cc"
    break;

  case 326:
#line 1165 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2100 "dhcp4_parser.cc"
    break;

  case 327:
#line 1167 "dhcp4_parser.yy"
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface-id", iface);
    ctx.leave();
}
#line 2110 "dhcp4_parser.cc"
    break;

  case 328:
#line 1173 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2118 "dhcp4_parser.cc"
    break;

  case 329:
#line 1175 "dhcp4_parser.yy"
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-subnet", iface);
    ctx.leave();
}
#line 2128 "dhcp4_parser.cc"
    break;

  case 330:
#line 1181 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2136 "dhcp4_parser.cc"
    break;

  case 331:
#line 1183 "dhcp4_parser.yy"
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 2146 "dhcp4_parser.cc"
    break;

  case 332:
#line 1189 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2154 "dhcp4_parser.cc"
    break;

  case 333:
#line 1191 "dhcp4_parser.yy"
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 2164 "dhcp4_parser.cc"
    break;

  case 334:
#line 1197 "dhcp4_parser.yy"
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2175 "dhcp4_parser.cc"
    break;

  case 335:
#line 1202 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2184 "dhcp4_parser.cc"
    break;

  case 336:
#line 1207 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 2192 "dhcp4_parser.cc"
    break;

  case 337:
#line 1209 "dhcp4_parser.yy"
    {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2201 "dhcp4_parser.cc"
    break;

  case 338:
#line 1214 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 2207 "dhcp4_parser.cc"
    break;

  case 339:
#line 1215 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 2213 "dhcp4_parser.cc"
    break;

  case 340:
#line 1216 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("global", ctx.loc2pos(yystack_[0].location))); }
#line 2219 "dhcp4_parser.cc"
    break;

  case 341:
#line 1217 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 2225 "dhcp4_parser.cc"
    break;

  case 342:
#line 1220 "dhcp4_parser.yy"
    {
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 2234 "dhcp4_parser.cc"
    break;

  case 343:
#line 1227 "dhcp4_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 2245 "dhcp4_parser.cc"
    break;

  case 344:
#line 1232 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2254 "dhcp4_parser.cc"
    break;

  case 349:
#line 1247 "dhcp4_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2264 "dhcp4_parser.cc"
    break;

  case 350:
#line 1251 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
}
#line 2272 "dhcp4_parser.cc"
    break;

  case 378:
#line 1290 "dhcp4_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 2283 "dhcp4_parser.cc"
    break;

  case 379:
#line 1295 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2292 "dhcp4_parser.cc"
    break;

  case 380:
#line 1303 "dhcp4_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2301 "dhcp4_parser.cc"
    break;

  case 381:
#line 1306 "dhcp4_parser.yy"
    {
    // parsing completed
}
#line 2309 "dhcp4_parser.cc"
    break;

  case 386:
#line 1322 "dhcp4_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2319 "dhcp4_parser.cc"
    break;

  case 387:
#line 1326 "dhcp4_parser.yy"
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2331 "dhcp4_parser.cc"
    break;

  case 388:
#line 1337 "dhcp4_parser.yy"
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2341 "dhcp4_parser.cc"
    break;

  case 389:
#line 1341 "dhcp4_parser.yy"
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2353 "dhcp4_parser.cc"
    break;

  case 405:
#line 1373 "dhcp4_parser.yy"
    {
    ElementPtr code(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 2362 "dhcp4_parser.cc"
    break;

  case 407:
#line 1380 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2370 "dhcp4_parser.cc"
    break;

  case 408:
#line 1382 "dhcp4_parser.yy"
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 2380 "dhcp4_parser.cc"
    break;

  case 409:
#line 1388 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2388 "dhcp4_parser.cc"
    break;

  case 410:
#line 1390 "dhcp4_parser.yy"
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 2398 "dhcp4_parser.cc"
    break;

  case 411:
#line 1396 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2406 "dhcp4_parser.cc"
    break;

  case 412:
#line 1398 "dhcp4_parser.yy"
    {
    ElementPtr space(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 2416 "dhcp4_parser.cc"
    break;

  case 414:
#line 1406 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2424 "dhcp4_parser.cc"
    break;

  case 415:
#line 1408 "dhcp4_parser.yy"
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 2434 "dhcp4_parser.cc"
    break;

  case 416:
#line 1414 "dhcp4_parser.yy"
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 2443 "dhcp4_parser.cc"
    break;

  case 417:
#line 1423 "dhcp4_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 2454 "dhcp4_parser.cc"
    break;

  case 418:
#line 1428 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2463 "dhcp4_parser.cc"
    break;

  case 423:
#line 1447 "dhcp4_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2473 "dhcp4_parser.cc"
    break;

  case 424:
#line 1451 "dhcp4_parser.yy"
    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 2482 "dhcp4_parser.cc"
    break;

  case 425:
#line 1459 "dhcp4_parser.yy"
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2492 "dhcp4_parser.cc"
    break;

  case 426:
#line 1463 "dhcp4_parser.yy"
    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 2501 "dhcp4_parser.cc"
    break;

  case 441:
#line 1496 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2509 "dhcp4_parser.cc"
    break;

  case 442:
#line 1498 "dhcp4_parser.yy"
    {
    ElementPtr data(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2519 "dhcp4_parser.cc"
    break;

  case 445:
#line 1508 "dhcp4_parser.yy"
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2528 "dhcp4_parser.cc"
    break;

  case 446:
#line 1513 "dhcp4_parser.yy"
    {
    ElementPtr persist(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 2537 "dhcp4_parser.cc"
    break;

  case 447:
#line 1521 "dhcp4_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2548 "dhcp4_parser.cc"
    break;

  case 448:
#line 1526 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2557 "dhcp4_parser.cc"
    break;

  case 453:
#line 1541 "dhcp4_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2567 "dhcp4_parser.cc"
    break;

  case 454:
#line 1545 "dhcp4_parser.yy"
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2577 "dhcp4_parser.cc"
    break;

  case 455:
#line 1551 "dhcp4_parser.yy"
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2587 "dhcp4_parser.cc"
    break;

  case 456:
#line 1555 "dhcp4_parser.yy"
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2597 "dhcp4_parser.cc"
    break;

  case 466:
#line 1574 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2605 "dhcp4_parser.cc"
    break;

  case 467:
#line 1576 "dhcp4_parser.yy"
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2615 "dhcp4_parser.cc"
    break;

  case 468:
#line 1582 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2623 "dhcp4_parser.cc"
    break;

  case 469:
#line 1584 "dhcp4_parser.yy"
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
#line 2650 "dhcp4_parser.cc"
    break;

  case 470:
#line 1607 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2658 "dhcp4_parser.cc"
    break;

  case 471:
#line 1609 "dhcp4_parser.yy"
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
#line 2687 "dhcp4_parser.cc"
    break;

  case 472:
#line 1637 "dhcp4_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 2698 "dhcp4_parser.cc"
    break;

  case 473:
#line 1642 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2707 "dhcp4_parser.cc"
    break;

  case 478:
#line 1655 "dhcp4_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2717 "dhcp4_parser.cc"
    break;

  case 479:
#line 1659 "dhcp4_parser.yy"
    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 2726 "dhcp4_parser.cc"
    break;

  case 480:
#line 1664 "dhcp4_parser.yy"
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2736 "dhcp4_parser.cc"
    break;

  case 481:
#line 1668 "dhcp4_parser.yy"
    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 2745 "dhcp4_parser.cc"
    break;

  case 501:
#line 1699 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2753 "dhcp4_parser.cc"
    break;

  case 502:
#line 1701 "dhcp4_parser.yy"
    {
    ElementPtr next_server(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("next-server", next_server);
    ctx.leave();
}
#line 2763 "dhcp4_parser.cc"
    break;

  case 503:
#line 1707 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2771 "dhcp4_parser.cc"
    break;

  case 504:
#line 1709 "dhcp4_parser.yy"
    {
    ElementPtr srv(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-hostname", srv);
    ctx.leave();
}
#line 2781 "dhcp4_parser.cc"
    break;

  case 505:
#line 1715 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2789 "dhcp4_parser.cc"
    break;

  case 506:
#line 1717 "dhcp4_parser.yy"
    {
    ElementPtr bootfile(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("boot-file-name", bootfile);
    ctx.leave();
}
#line 2799 "dhcp4_parser.cc"
    break;

  case 507:
#line 1723 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2807 "dhcp4_parser.cc"
    break;

  case 508:
#line 1725 "dhcp4_parser.yy"
    {
    ElementPtr addr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 2817 "dhcp4_parser.cc"
    break;

  case 509:
#line 1731 "dhcp4_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2828 "dhcp4_parser.cc"
    break;

  case 510:
#line 1736 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2837 "dhcp4_parser.cc"
    break;

  case 511:
#line 1741 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2845 "dhcp4_parser.cc"
    break;

  case 512:
#line 1743 "dhcp4_parser.yy"
    {
    ElementPtr d(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2855 "dhcp4_parser.cc"
    break;

  case 513:
#line 1749 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2863 "dhcp4_parser.cc"
    break;

  case 514:
#line 1751 "dhcp4_parser.yy"
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2873 "dhcp4_parser.cc"
    break;

  case 515:
#line 1757 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2881 "dhcp4_parser.cc"
    break;

  case 516:
#line 1759 "dhcp4_parser.yy"
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-id", hw);
    ctx.leave();
}
#line 2891 "dhcp4_parser.cc"
    break;

  case 517:
#line 1765 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2899 "dhcp4_parser.cc"
    break;

  case 518:
#line 1767 "dhcp4_parser.yy"
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("circuit-id", hw);
    ctx.leave();
}
#line 2909 "dhcp4_parser.cc"
    break;

  case 519:
#line 1773 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2917 "dhcp4_parser.cc"
    break;

  case 520:
#line 1775 "dhcp4_parser.yy"
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 2927 "dhcp4_parser.cc"
    break;

  case 521:
#line 1781 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2935 "dhcp4_parser.cc"
    break;

  case 522:
#line 1783 "dhcp4_parser.yy"
    {
    ElementPtr host(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2945 "dhcp4_parser.cc"
    break;

  case 523:
#line 1789 "dhcp4_parser.yy"
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2956 "dhcp4_parser.cc"
    break;

  case 524:
#line 1794 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2965 "dhcp4_parser.cc"
    break;

  case 525:
#line 1802 "dhcp4_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2976 "dhcp4_parser.cc"
    break;

  case 526:
#line 1807 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2985 "dhcp4_parser.cc"
    break;

  case 529:
#line 1819 "dhcp4_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2996 "dhcp4_parser.cc"
    break;

  case 530:
#line 1824 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3005 "dhcp4_parser.cc"
    break;

  case 533:
#line 1833 "dhcp4_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3015 "dhcp4_parser.cc"
    break;

  case 534:
#line 1837 "dhcp4_parser.yy"
    {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3025 "dhcp4_parser.cc"
    break;

  case 551:
#line 1866 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3033 "dhcp4_parser.cc"
    break;

  case 552:
#line 1868 "dhcp4_parser.yy"
    {
    ElementPtr test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 3043 "dhcp4_parser.cc"
    break;

  case 553:
#line 1874 "dhcp4_parser.yy"
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 3052 "dhcp4_parser.cc"
    break;

  case 554:
#line 1883 "dhcp4_parser.yy"
    {
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 3061 "dhcp4_parser.cc"
    break;

  case 555:
#line 1890 "dhcp4_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 3072 "dhcp4_parser.cc"
    break;

  case 556:
#line 1895 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3081 "dhcp4_parser.cc"
    break;

  case 564:
#line 1911 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3089 "dhcp4_parser.cc"
    break;

  case 565:
#line 1913 "dhcp4_parser.yy"
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 3099 "dhcp4_parser.cc"
    break;

  case 566:
#line 1919 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3107 "dhcp4_parser.cc"
    break;

  case 567:
#line 1921 "dhcp4_parser.yy"
    {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 3117 "dhcp4_parser.cc"
    break;

  case 568:
#line 1930 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3125 "dhcp4_parser.cc"
    break;

  case 569:
#line 1932 "dhcp4_parser.yy"
    {
    ElementPtr qc = yystack_[0].value.as < ElementPtr > ();
    ctx.stack_.back()->set("dhcp-queue-control", qc);

    // Doing this manually, because dhcp-queue-control
    // content is otherwise arbitrary
    if (!qc->contains("enable-queue")) {
        std::stringstream msg;
        msg << "'enable-queue' is required: ";
        msg  << "(" << qc->getPosition().str() << ")";
        error(yystack_[3].location, msg.str());
    }

    ConstElementPtr enable_queue = qc->get("enable-queue");
    if (enable_queue->getType() != Element::boolean) {
        std::stringstream msg;
        msg << "'enable-queue' must be boolean: ";
        msg  << "(" << qc->getPosition().str() << ")";
        error(yystack_[3].location, msg.str());
    }

    if (qc->contains("queue-type")) {
        ConstElementPtr queue_type = qc->get("queue-type");
        if (queue_type->getType() != Element::string) {
            std::stringstream msg;
            msg << "'queue-type' must be a string: ";
            msg  << "(" << qc->getPosition().str() << ")";
            error(yystack_[3].location, msg.str());
        }
    }

    ctx.leave();
}
#line 3163 "dhcp4_parser.cc"
    break;

  case 570:
#line 1968 "dhcp4_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 3174 "dhcp4_parser.cc"
    break;

  case 571:
#line 1973 "dhcp4_parser.yy"
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3185 "dhcp4_parser.cc"
    break;

  case 572:
#line 1980 "dhcp4_parser.yy"
    {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3195 "dhcp4_parser.cc"
    break;

  case 573:
#line 1984 "dhcp4_parser.yy"
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3205 "dhcp4_parser.cc"
    break;

  case 594:
#line 2014 "dhcp4_parser.yy"
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 3214 "dhcp4_parser.cc"
    break;

  case 595:
#line 2019 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3222 "dhcp4_parser.cc"
    break;

  case 596:
#line 2021 "dhcp4_parser.yy"
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 3232 "dhcp4_parser.cc"
    break;

  case 597:
#line 2027 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3240 "dhcp4_parser.cc"
    break;

  case 598:
#line 2029 "dhcp4_parser.yy"
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 3250 "dhcp4_parser.cc"
    break;

  case 599:
#line 2035 "dhcp4_parser.yy"
    {
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 3259 "dhcp4_parser.cc"
    break;

  case 600:
#line 2040 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3267 "dhcp4_parser.cc"
    break;

  case 601:
#line 2042 "dhcp4_parser.yy"
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 3277 "dhcp4_parser.cc"
    break;

  case 602:
#line 2048 "dhcp4_parser.yy"
    {
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 3286 "dhcp4_parser.cc"
    break;

  case 603:
#line 2053 "dhcp4_parser.yy"
    {
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 3295 "dhcp4_parser.cc"
    break;

  case 604:
#line 2058 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 3303 "dhcp4_parser.cc"
    break;

  case 605:
#line 2060 "dhcp4_parser.yy"
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3312 "dhcp4_parser.cc"
    break;

  case 606:
#line 2066 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 3318 "dhcp4_parser.cc"
    break;

  case 607:
#line 2067 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 3324 "dhcp4_parser.cc"
    break;

  case 608:
#line 2070 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 3332 "dhcp4_parser.cc"
    break;

  case 609:
#line 2072 "dhcp4_parser.yy"
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 3342 "dhcp4_parser.cc"
    break;

  case 610:
#line 2078 "dhcp4_parser.yy"
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 3351 "dhcp4_parser.cc"
    break;

  case 611:
#line 2083 "dhcp4_parser.yy"
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 3360 "dhcp4_parser.cc"
    break;

  case 612:
#line 2088 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 3368 "dhcp4_parser.cc"
    break;

  case 613:
#line 2090 "dhcp4_parser.yy"
    {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3377 "dhcp4_parser.cc"
    break;

  case 614:
#line 2096 "dhcp4_parser.yy"
    {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 3385 "dhcp4_parser.cc"
    break;

  case 615:
#line 2099 "dhcp4_parser.yy"
    {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 3393 "dhcp4_parser.cc"
    break;

  case 616:
#line 2102 "dhcp4_parser.yy"
    {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 3401 "dhcp4_parser.cc"
    break;

  case 617:
#line 2105 "dhcp4_parser.yy"
    {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 3409 "dhcp4_parser.cc"
    break;

  case 618:
#line 2108 "dhcp4_parser.yy"
    {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 3418 "dhcp4_parser.cc"
    break;

  case 619:
#line 2114 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3426 "dhcp4_parser.cc"
    break;

  case 620:
#line 2116 "dhcp4_parser.yy"
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 3436 "dhcp4_parser.cc"
    break;

  case 621:
#line 2122 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3444 "dhcp4_parser.cc"
    break;

  case 622:
#line 2124 "dhcp4_parser.yy"
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 3454 "dhcp4_parser.cc"
    break;

  case 623:
#line 2130 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3462 "dhcp4_parser.cc"
    break;

  case 624:
#line 2132 "dhcp4_parser.yy"
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 3472 "dhcp4_parser.cc"
    break;

  case 625:
#line 2141 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3480 "dhcp4_parser.cc"
    break;

  case 626:
#line 2143 "dhcp4_parser.yy"
    {
    ctx.stack_.back()->set("Dhcp6", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3489 "dhcp4_parser.cc"
    break;

  case 627:
#line 2148 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3497 "dhcp4_parser.cc"
    break;

  case 628:
#line 2150 "dhcp4_parser.yy"
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3506 "dhcp4_parser.cc"
    break;

  case 629:
#line 2155 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3514 "dhcp4_parser.cc"
    break;

  case 630:
#line 2157 "dhcp4_parser.yy"
    {
    ctx.stack_.back()->set("Control-agent", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3523 "dhcp4_parser.cc"
    break;

  case 631:
#line 2162 "dhcp4_parser.yy"
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 3534 "dhcp4_parser.cc"
    break;

  case 632:
#line 2167 "dhcp4_parser.yy"
    {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3544 "dhcp4_parser.cc"
    break;

  case 633:
#line 2173 "dhcp4_parser.yy"
    {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3554 "dhcp4_parser.cc"
    break;

  case 634:
#line 2177 "dhcp4_parser.yy"
    {
    // No config_control params are required
    // parsing completed
}
#line 3563 "dhcp4_parser.cc"
    break;

  case 639:
#line 2192 "dhcp4_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 3574 "dhcp4_parser.cc"
    break;

  case 640:
#line 2197 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3583 "dhcp4_parser.cc"
    break;

  case 641:
#line 2202 "dhcp4_parser.yy"
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-fetch-wait-time", value);
}
#line 3592 "dhcp4_parser.cc"
    break;

  case 642:
#line 2212 "dhcp4_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 3603 "dhcp4_parser.cc"
    break;

  case 643:
#line 2217 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3612 "dhcp4_parser.cc"
    break;

  case 644:
#line 2222 "dhcp4_parser.yy"
    {
    // Parse the Logging map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3622 "dhcp4_parser.cc"
    break;

  case 645:
#line 2226 "dhcp4_parser.yy"
    {
    // parsing completed
}
#line 3630 "dhcp4_parser.cc"
    break;

  case 649:
#line 2242 "dhcp4_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 3641 "dhcp4_parser.cc"
    break;

  case 650:
#line 2247 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3650 "dhcp4_parser.cc"
    break;

  case 653:
#line 2259 "dhcp4_parser.yy"
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 3660 "dhcp4_parser.cc"
    break;

  case 654:
#line 2263 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
}
#line 3668 "dhcp4_parser.cc"
    break;

  case 664:
#line 2280 "dhcp4_parser.yy"
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 3677 "dhcp4_parser.cc"
    break;

  case 665:
#line 2285 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3685 "dhcp4_parser.cc"
    break;

  case 666:
#line 2287 "dhcp4_parser.yy"
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 3695 "dhcp4_parser.cc"
    break;

  case 667:
#line 2293 "dhcp4_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 3706 "dhcp4_parser.cc"
    break;

  case 668:
#line 2298 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3715 "dhcp4_parser.cc"
    break;

  case 671:
#line 2307 "dhcp4_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3725 "dhcp4_parser.cc"
    break;

  case 672:
#line 2311 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
}
#line 3733 "dhcp4_parser.cc"
    break;

  case 680:
#line 2326 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3741 "dhcp4_parser.cc"
    break;

  case 681:
#line 2328 "dhcp4_parser.yy"
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 3751 "dhcp4_parser.cc"
    break;

  case 682:
#line 2334 "dhcp4_parser.yy"
    {
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 3760 "dhcp4_parser.cc"
    break;

  case 683:
#line 2339 "dhcp4_parser.yy"
    {
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 3769 "dhcp4_parser.cc"
    break;

  case 684:
#line 2344 "dhcp4_parser.yy"
    {
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 3778 "dhcp4_parser.cc"
    break;

  case 685:
#line 2349 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3786 "dhcp4_parser.cc"
    break;

  case 686:
#line 2351 "dhcp4_parser.yy"
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pattern", sev);
    ctx.leave();
}
#line 3796 "dhcp4_parser.cc"
    break;


#line 3800 "dhcp4_parser.cc"

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
          yyn = yypact_[yystack_[0].state];
          if (!yy_pact_value_is_default_ (yyn))
            {
              yyn += yyterror_;
              if (0 <= yyn && yyn <= yylast_ && yycheck_[yyn] == yyterror_)
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
      error_token.state = yyn;
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
    size_t yycount = 0;
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
         scanner and before detecting a syntax error.  Thus, state
         merging (from LALR or IELR) and default reductions corrupt the
         expected token list.  However, the list is correct for
         canonical LR with one exception: it will still contain any
         token that will not be accepted due to an error action in a
         later state.
    */
    if (!yyla.empty ())
      {
        int yytoken = yyla.type_get ();
        yyarg[yycount++] = yytname_[yytoken];
        int yyn = yypact_[yystate];
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
              if (yycheck_[yyx + yyn] == yyx && yyx != yyterror_
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
    size_t yyi = 0;
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


  const short Dhcp4Parser::yypact_ninf_ = -845;

  const signed char Dhcp4Parser::yytable_ninf_ = -1;

  const short
  Dhcp4Parser::yypact_[] =
  {
     320,  -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,
    -845,  -845,  -845,  -845,  -845,    71,    21,    37,    68,    89,
     116,   143,   168,   185,   196,   200,   231,   295,   298,   319,
    -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,
    -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,
    -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,
    -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,    21,  -125,
      17,   156,    61,   449,    51,   204,   172,   174,    86,   -51,
     482,   113,   253,  -845,   290,   316,   294,   323,   330,  -845,
    -845,  -845,  -845,  -845,   331,  -845,    44,  -845,  -845,  -845,
    -845,  -845,  -845,  -845,  -845,  -845,   340,   341,   342,  -845,
    -845,  -845,  -845,  -845,  -845,   343,   344,   345,   347,   348,
     349,   350,   351,   352,   354,  -845,  -845,  -845,  -845,  -845,
    -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,   356,  -845,
    -845,  -845,  -845,  -845,  -845,  -845,    62,  -845,  -845,  -845,
    -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,
    -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,
    -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,
    -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,
    -845,  -845,  -845,   357,  -845,    70,  -845,  -845,  -845,  -845,
    -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,   358,
    -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,
    -845,  -845,  -845,  -845,  -845,    78,  -845,  -845,  -845,  -845,
    -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,
    -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,
      90,  -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,
    -845,  -845,  -845,  -845,  -845,  -845,  -845,   359,   361,  -845,
    -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,
    -845,   360,  -845,  -845,   362,  -845,  -845,  -845,   365,  -845,
    -845,   363,   367,  -845,  -845,  -845,  -845,  -845,  -845,  -845,
    -845,  -845,  -845,  -845,  -845,  -845,   368,   369,  -845,  -845,
    -845,  -845,   366,   373,  -845,  -845,  -845,  -845,  -845,  -845,
    -845,  -845,  -845,  -845,  -845,  -845,   118,  -845,  -845,  -845,
     375,  -845,  -845,   377,  -845,   378,   379,  -845,  -845,   380,
     381,  -845,  -845,  -845,  -845,  -845,   119,  -845,  -845,  -845,
    -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,
    -845,  -845,  -845,   127,  -845,  -845,  -845,   384,   148,  -845,
    -845,  -845,  -845,    21,    21,  -845,   189,   388,   391,   392,
     393,   394,  -845,    17,  -845,   396,   399,   401,   233,   234,
     236,   406,   407,   412,   413,   415,   419,   247,   248,   250,
     265,   268,   254,   267,   199,   269,   271,   445,   458,   459,
     461,   462,   464,   466,   467,   468,   470,   476,   492,   493,
     321,   495,   496,   497,   498,   499,   500,   156,  -845,   501,
     511,   512,   338,    61,  -845,   517,   519,   520,   521,   522,
     523,   353,   524,   525,   527,   449,  -845,   528,    51,  -845,
     530,   537,   538,   540,   541,   544,   548,   549,  -845,   204,
    -845,   550,   551,   382,   552,   556,   557,   383,  -845,   174,
     559,   385,   386,  -845,    86,   563,   566,   160,  -845,   395,
     567,   568,   402,   569,   404,   405,   572,   574,   409,   410,
     580,   581,   482,  -845,   113,  -845,   582,   414,   253,  -845,
    -845,  -845,   586,   585,   587,    21,    21,    21,  -845,   588,
     589,   590,  -845,  -845,  -845,   417,   422,   423,   600,   602,
     618,  -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,
    -845,   448,   622,   626,   636,   637,   638,   471,   230,   639,
     641,   645,   646,   647,  -845,   648,   638,   649,   477,   481,
     654,  -845,   655,   300,   309,  -845,  -845,   487,   489,   491,
     663,   494,   502,  -845,   655,   503,   662,  -845,   504,  -845,
     655,   505,   506,   507,   509,   510,   513,   514,  -845,   515,
     516,  -845,   518,   526,   529,  -845,  -845,   531,  -845,  -845,
    -845,   532,    21,  -845,  -845,   533,   534,  -845,   535,  -845,
    -845,    14,   545,  -845,  -845,   -26,   536,  -845,  -845,   666,
    -845,  -845,    21,   156,   113,  -845,  -845,  -845,   253,    61,
     628,  -845,  -845,  -845,    60,    60,   665,  -845,   667,   668,
     670,   681,  -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,
     181,   686,   688,   689,    23,     4,  -845,   482,  -845,  -845,
     690,  -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,
    -845,  -845,   691,  -845,  -845,  -845,  -845,   232,  -845,  -845,
    -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,
    -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,
    -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,   665,
    -845,   166,   187,   188,   222,  -845,   223,  -845,  -845,  -845,
    -845,  -845,  -845,   695,   696,   697,   699,   700,  -845,  -845,
    -845,  -845,   702,   709,   710,   711,   712,   713,  -845,   237,
    -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,
    -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,
    -845,   238,  -845,   714,   715,  -845,  -845,   716,   718,  -845,
    -845,   717,   721,  -845,  -845,   719,   723,  -845,  -845,   722,
     724,  -845,  -845,  -845,  -845,  -845,  -845,    42,  -845,  -845,
    -845,  -845,  -845,  -845,  -845,   151,  -845,  -845,   725,   726,
    -845,  -845,   727,   729,  -845,   730,   731,   732,   733,   734,
     735,   256,  -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,
    -845,  -845,  -845,  -845,   264,  -845,  -845,  -845,   272,  -845,
     165,  -845,   543,  -845,   736,   737,  -845,  -845,  -845,  -845,
     738,   739,  -845,  -845,  -845,  -845,   740,   628,  -845,   743,
     744,   745,   746,   553,   562,   576,   564,   577,   748,   751,
     752,   753,   583,   584,   591,   592,   579,   593,    60,  -845,
    -845,    60,  -845,   665,   449,  -845,   667,   174,  -845,   668,
      86,  -845,   670,   575,  -845,   681,   181,  -845,    59,   686,
    -845,   204,  -845,   688,   -51,  -845,   689,   594,   595,   596,
     597,   598,   599,    23,  -845,   755,   758,     4,  -845,  -845,
     183,   690,  -845,  -845,   757,   761,    51,  -845,   691,   762,
    -845,  -845,   601,  -845,   303,   603,   604,   605,  -845,  -845,
    -845,  -845,  -845,   606,   607,   608,   609,  -845,  -845,  -845,
    -845,  -845,  -845,  -845,   273,  -845,   285,  -845,   759,  -845,
     770,  -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,
    -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,
     289,  -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,
    -845,  -845,   782,  -845,  -845,  -845,  -845,  -845,  -845,  -845,
    -845,  -845,   779,   785,  -845,  -845,  -845,  -845,  -845,   781,
    -845,   291,  -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,
     614,   615,  -845,  -845,   788,  -845,  -845,  -845,  -845,  -845,
     292,  -845,  -845,  -845,  -845,  -845,  -845,   617,   312,  -845,
     655,  -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,
    -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,   575,  -845,
     791,   620,  -845,    59,  -845,  -845,  -845,  -845,   792,   624,
     798,   183,  -845,  -845,  -845,  -845,  -845,   631,  -845,  -845,
     760,  -845,   640,  -845,  -845,   810,  -845,  -845,   198,  -845,
      54,   810,  -845,  -845,   818,   820,   829,  -845,   313,  -845,
    -845,  -845,  -845,  -845,  -845,  -845,   837,   671,   675,   676,
     840,    54,  -845,   684,  -845,  -845,  -845,   693,  -845,  -845,
    -845
  };

  const unsigned short
  Dhcp4Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,    28,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       1,    45,    38,    34,    33,    30,    31,    32,    37,     3,
      35,    36,    58,     5,    70,     7,   143,     9,   288,    11,
     455,    13,   480,    15,   380,    17,   388,    19,   425,    21,
     253,    23,   572,    25,   644,    27,   633,    29,    47,    41,
       0,     0,     0,     0,     0,   482,     0,   390,   427,     0,
       0,     0,     0,    49,     0,    48,     0,     0,    42,    68,
     642,   625,   627,   629,     0,    67,     0,    60,    62,    64,
      65,    66,    63,   631,   132,   158,     0,     0,     0,   501,
     503,   505,   156,   165,   167,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,   127,   280,   378,   417,   343,
     468,   470,   336,   231,   529,   472,   245,   264,     0,   555,
     568,   570,   621,   623,   649,   116,     0,    72,    74,    75,
      76,    77,    78,   115,   109,   110,   111,    79,   107,    96,
      97,    98,    82,    83,   104,    84,    85,    86,    90,    91,
      80,   108,    81,    88,    89,   102,   103,   105,    99,   100,
     101,    87,    92,    93,    94,    95,   113,   114,   106,   112,
     145,   147,   151,     0,   142,     0,   134,   136,   137,   138,
     139,   140,   141,   324,   326,   328,   447,   322,   330,     0,
     334,   332,   525,   321,   292,   293,   294,   295,   296,   320,
     317,   318,   319,   307,   308,     0,   290,   299,   312,   313,
     314,   300,   302,   303,   305,   301,   297,   298,   315,   316,
     304,   309,   310,   311,   306,   466,   465,   461,   462,   460,
       0,   457,   459,   463,   464,   523,   511,   513,   517,   515,
     521,   519,   507,   500,   494,   498,   499,     0,   483,   484,
     495,   496,   497,   491,   486,   492,   488,   489,   490,   493,
     487,     0,   407,   211,     0,   411,   409,   414,     0,   403,
     404,     0,   391,   392,   394,   406,   395,   396,   397,   413,
     398,   399,   400,   401,   402,   441,     0,     0,   439,   440,
     443,   444,     0,   428,   429,   431,   432,   433,   434,   435,
     436,   437,   438,   260,   262,   257,     0,   255,   258,   259,
       0,   595,   597,     0,   600,     0,     0,   604,   608,     0,
       0,   612,   619,   593,   591,   592,     0,   574,   576,   577,
     578,   579,   580,   581,   582,   583,   584,   585,   586,   587,
     588,   589,   590,     0,   646,   648,   639,     0,     0,   635,
     637,   638,    46,     0,     0,    39,     0,     0,     0,     0,
       0,     0,    57,     0,    59,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    71,     0,
       0,     0,     0,     0,   144,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   289,     0,     0,   456,
       0,     0,     0,     0,     0,     0,     0,     0,   481,     0,
     381,     0,     0,     0,     0,     0,     0,     0,   389,     0,
       0,     0,     0,   426,     0,     0,     0,     0,   254,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   573,     0,   645,     0,     0,     0,   634,
      50,    43,     0,     0,     0,     0,     0,     0,    61,     0,
       0,     0,   129,   130,   131,     0,     0,     0,     0,     0,
       0,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     126,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   554,     0,     0,     0,     0,     0,
       0,    73,     0,     0,     0,   155,   135,     0,     0,     0,
       0,     0,     0,   342,     0,     0,     0,   291,     0,   458,
       0,     0,     0,     0,     0,     0,     0,     0,   485,     0,
       0,   405,     0,     0,     0,   416,   393,     0,   445,   446,
     430,     0,     0,   256,   594,     0,     0,   599,     0,   602,
     603,     0,     0,   610,   611,     0,     0,   575,   647,     0,
     641,   636,     0,     0,     0,   626,   628,   630,     0,     0,
       0,   502,   504,   506,     0,     0,   169,   128,   282,   382,
     419,   345,    40,   469,   471,   338,   339,   340,   341,   337,
       0,     0,   474,   247,     0,     0,   569,     0,   622,   624,
       0,    51,   146,   149,   150,   148,   153,   154,   152,   325,
     327,   329,   449,   323,   331,   335,   333,     0,   467,   524,
     512,   514,   518,   516,   522,   520,   508,   408,   212,   412,
     410,   415,   442,   261,   263,   596,   598,   601,   606,   607,
     605,   609,   614,   615,   616,   617,   618,   613,   620,   169,
      44,     0,     0,     0,     0,   163,     0,   160,   162,   198,
     204,   206,   208,     0,     0,     0,     0,     0,   220,   222,
     224,   226,     0,     0,     0,     0,     0,     0,   197,     0,
     175,   177,   178,   179,   180,   181,   182,   183,   184,   185,
     186,   190,   191,   192,   187,   193,   194,   195,   188,   189,
     196,     0,   173,     0,   170,   171,   286,     0,   283,   284,
     386,     0,   383,   384,   423,     0,   420,   421,   349,     0,
     346,   347,   240,   241,   242,   243,   244,     0,   233,   235,
     236,   237,   238,   239,   533,     0,   531,   478,     0,   475,
     476,   251,     0,   248,   249,     0,     0,     0,     0,     0,
       0,     0,   266,   268,   269,   270,   271,   272,   273,   564,
     566,   563,   561,   562,     0,   557,   559,   560,     0,   653,
       0,   651,    53,   453,     0,   450,   451,   509,   527,   528,
       0,     0,    69,   643,   632,   133,     0,     0,   159,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   157,
     166,     0,   168,     0,     0,   281,     0,   390,   379,     0,
     427,   418,     0,     0,   344,     0,     0,   232,   535,     0,
     530,   482,   473,     0,     0,   246,     0,     0,     0,     0,
       0,     0,     0,     0,   265,     0,     0,     0,   556,   571,
       0,     0,   650,    55,     0,    54,     0,   448,     0,     0,
     526,   640,     0,   161,     0,     0,     0,     0,   210,   213,
     214,   215,   216,     0,     0,     0,     0,   228,   229,   217,
     218,   219,   230,   176,     0,   172,     0,   285,     0,   385,
       0,   422,   377,   368,   369,   370,   356,   357,   376,   373,
     374,   375,   359,   360,   353,   354,   355,   366,   367,   365,
       0,   351,   358,   371,   372,   361,   362,   363,   364,   348,
     234,   551,     0,   549,   550,   542,   543,   547,   548,   544,
     545,   546,     0,   536,   537,   539,   540,   541,   532,     0,
     477,     0,   250,   274,   275,   276,   277,   278,   279,   267,
       0,     0,   558,   667,     0,   665,   663,   657,   661,   662,
       0,   655,   659,   660,   658,   652,    52,     0,     0,   452,
       0,   164,   200,   201,   202,   203,   199,   205,   207,   209,
     221,   223,   225,   227,   174,   287,   387,   424,     0,   350,
       0,     0,   534,     0,   479,   252,   565,   567,     0,     0,
       0,     0,   654,    56,   454,   510,   352,     0,   553,   538,
       0,   664,     0,   656,   552,     0,   666,   671,     0,   669,
       0,     0,   668,   680,     0,     0,     0,   685,     0,   673,
     675,   676,   677,   678,   679,   670,     0,     0,     0,     0,
       0,     0,   672,     0,   682,   683,   684,     0,   674,   681,
     686
  };

  const short
  Dhcp4Parser::yypgoto_[] =
  {
    -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,
    -845,  -845,  -845,  -845,  -845,  -845,   -46,  -845,  -486,  -845,
     301,  -845,  -845,  -845,  -845,  -845,  -845,  -539,  -845,  -845,
    -845,   -70,  -845,  -845,  -845,   508,  -845,  -845,  -845,  -845,
     277,   469,   -55,   -54,   -27,   -24,    -9,     6,     9,    11,
      12,  -845,  -845,  -845,  -845,    19,    22,  -845,  -845,   274,
     465,  -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,
    -845,  -845,  -845,  -845,  -845,  -845,  -845,    57,  -845,  -845,
    -845,  -845,  -845,  -845,   201,  -845,    39,  -845,  -612,    45,
    -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,
     -35,  -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,
    -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,
    -845,  -845,  -845,    28,  -845,  -845,  -845,  -845,  -845,  -845,
    -845,  -845,  -845,    20,  -845,  -845,  -845,    25,   428,  -845,
    -845,  -845,  -845,  -845,  -845,  -845,    15,  -845,  -845,  -845,
    -845,  -845,  -845,  -844,  -845,  -845,  -845,    41,  -845,  -845,
    -845,    46,   472,  -845,  -845,  -845,  -845,  -845,  -845,  -845,
    -845,  -836,  -845,   -17,  -845,    -5,  -845,    24,  -845,  -845,
    -845,  -845,  -845,  -845,  -845,    36,  -845,  -845,  -126,   -65,
    -845,  -845,  -845,  -845,  -845,    47,  -845,  -845,  -845,    48,
    -845,   444,  -845,   -72,  -845,  -845,  -845,  -845,  -845,   -66,
    -845,  -845,  -845,  -845,  -845,    -7,  -845,  -845,  -845,    49,
    -845,  -845,  -845,    50,  -845,   440,  -845,  -845,  -845,  -845,
    -845,  -845,  -845,  -845,  -845,  -845,  -845,    10,  -845,  -845,
    -845,    13,   474,  -845,  -845,   -39,  -845,   -19,  -845,   -59,
    -845,  -845,  -845,    40,  -845,  -845,  -845,    43,  -845,   473,
     -58,  -845,   -52,  -845,    -1,  -845,   258,  -845,  -845,  -845,
    -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,
    -845,  -845,  -845,  -845,  -833,  -845,  -845,  -845,  -845,  -845,
      52,  -845,  -845,  -845,  -117,  -845,  -845,  -845,  -845,  -845,
    -845,  -845,  -845,    30,  -845,  -845,  -845,  -845,  -845,  -845,
    -845,  -845,  -845,  -845,   281,   437,  -845,  -845,  -845,  -845,
    -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,
    -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,   -64,  -845,
     -60,  -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,  -845,
    -845,  -845,   315,   432,  -845,  -845,  -845,  -845,  -845,  -845,
    -845,   322,   441,   -57,  -845,  -845,    33,  -845,  -845,  -114,
    -845,  -845,  -845,  -845,  -845,  -845,  -133,  -845,  -845,  -152,
    -845,  -845,  -845,  -845,  -845,  -845,  -845
  };

  const short
  Dhcp4Parser::yydefgoto_[] =
  {
      -1,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    38,    39,    40,    69,
     633,    87,    88,    41,    68,    84,    85,   652,   822,   904,
     905,   728,    43,    70,    96,    97,    98,   377,    45,    71,
     146,   147,   148,   149,   150,   151,   152,   153,   154,   155,
     156,   157,   158,   407,   159,   160,   161,   162,   386,   195,
     196,    47,    72,   197,   429,   198,   430,   655,   199,   431,
     658,   200,   163,   394,   164,   387,   706,   707,   708,   836,
     165,   395,   166,   396,   753,   754,   755,   861,   729,   730,
     731,   839,  1026,   732,   840,   733,   841,   734,   842,   735,
     736,   462,   737,   738,   739,   740,   741,   742,   743,   744,
     848,   745,   849,   746,   850,   747,   851,   748,   749,   750,
     167,   415,   777,   778,   779,   780,   781,   782,   783,   168,
     418,   792,   793,   794,   884,    61,    79,   326,   327,   328,
     475,   329,   476,   169,   419,   801,   802,   803,   804,   805,
     806,   807,   808,   170,   408,   757,   758,   759,   864,    49,
      73,   225,   226,   227,   439,   228,   435,   229,   436,   230,
     437,   231,   440,   232,   443,   233,   442,   171,   414,   639,
     235,   172,   411,   769,   770,   771,   873,   960,   961,   173,
     409,    55,    76,   761,   762,   763,   867,    57,    77,   291,
     292,   293,   294,   295,   296,   297,   461,   298,   465,   299,
     464,   300,   301,   466,   302,   174,   410,   765,   766,   767,
     870,    59,    78,   312,   313,   314,   315,   316,   470,   317,
     318,   319,   320,   237,   438,   824,   825,   826,   906,    51,
      74,   250,   251,   252,   447,   175,   412,   176,   413,   177,
     417,   788,   789,   790,   881,    53,    75,   267,   268,   269,
     178,   391,   179,   392,   180,   393,   273,   457,   829,   909,
     274,   451,   275,   452,   276,   454,   277,   453,   278,   456,
     279,   455,   280,   450,   244,   444,   830,   181,   416,   785,
     786,   878,   982,   983,   984,   985,   986,  1040,   987,   182,
     183,   421,   814,   815,   816,   895,   817,   896,   184,   422,
     185,   423,    63,    80,   346,   347,   348,   349,   480,   350,
     481,   351,   352,   483,   353,   354,   355,   486,   690,   356,
     487,   357,   358,   359,   490,   697,   360,   491,   186,   424,
     187,   425,    99,   379,   100,   380,   101,   381,   188,   385,
      67,    82,   368,   369,   370,   496,   371,   102,   378,    65,
      81,   363,   364,   189,   426,   820,   821,   900,  1010,  1011,
    1012,  1013,  1050,  1014,  1048,  1068,  1069,  1070,  1078,  1079,
    1080,  1086,  1081,  1082,  1083,  1084,  1090
  };

  const unsigned short
  Dhcp4Parser::yytable_[] =
  {
      95,   145,   194,   213,   246,   263,   310,   289,   308,   325,
     343,   281,   311,   751,   240,   241,   361,   270,   214,   215,
     362,   242,    83,   271,   365,   665,    31,    89,    32,   955,
      33,   669,   688,   201,   238,   253,   265,   956,   303,   321,
     968,   344,   290,   309,    42,   876,   216,   383,   877,   217,
     632,    86,   384,   202,   239,   254,   266,   247,   304,   322,
     632,   345,   323,   324,   218,   427,   236,   249,   264,   248,
     428,    30,   243,   433,   272,    44,   190,   191,   434,   219,
     192,   445,   220,   193,   221,   222,   446,   109,   110,   111,
     130,   131,   223,   448,   709,   224,    46,   234,   449,   710,
     711,   712,   713,   714,   715,   716,   717,   718,   719,   720,
     721,   722,   723,   724,   725,   726,   727,   692,   693,   694,
     695,   477,   492,    48,   128,    94,   478,   493,   809,   810,
     494,   127,   128,   283,   283,   495,   245,   130,   131,   795,
     796,   797,   798,   799,   800,   130,   131,   130,   131,   210,
      50,   498,   211,   696,   879,   689,   499,   880,   971,   972,
     283,   305,   284,   285,   306,   307,    90,   103,   901,   427,
     104,   902,   130,   131,   832,    52,    91,    92,    93,   105,
      94,   106,   107,   108,   109,   110,   111,   112,   113,   114,
     494,   498,    54,    94,   955,   833,   834,    34,    35,    36,
      37,  1071,   956,    56,  1072,   968,  1073,    58,   282,  1074,
    1075,  1076,  1077,   115,   116,   117,   118,   119,   120,   121,
     122,   123,   124,   125,   126,   433,   837,    94,   127,   128,
     835,   838,   109,   110,   111,    94,    94,    94,    60,   129,
     858,   858,   130,   131,   127,   859,   860,   132,   283,   934,
     284,   285,   133,   134,   286,   287,   288,   283,   135,   893,
     130,   131,    94,   144,   894,   366,   367,   897,   136,   130,
     131,   137,   898,   323,   324,   492,   858,   128,   138,   139,
     899,  1034,   140,   141,   772,   773,   774,   775,   445,   776,
     130,   131,  1038,  1035,   477,  1051,   372,  1039,   374,  1045,
    1052,   255,    62,   142,   143,    64,   144,   256,   257,   258,
     259,   260,   261,    95,   262,   448,  1091,   653,   654,   373,
    1054,  1092,   635,   636,   637,   638,    66,   500,   501,   656,
     657,   375,    94,   376,  1003,   382,  1004,  1005,  1022,  1023,
    1024,  1025,   262,   827,   388,   389,   390,   397,   398,   399,
      94,   400,   401,   402,   403,   404,   405,   145,   406,    94,
     420,   432,   441,   194,   459,   502,   463,   458,   460,   467,
     469,   468,   471,   472,   473,   213,   474,   528,   246,   479,
      94,   482,   484,   485,   488,   489,   240,   241,   497,   263,
     214,   215,   503,   242,   201,   504,   505,   506,   507,   289,
     509,   270,   310,   510,   308,   511,   238,   271,   311,   253,
     515,   516,   512,   513,   202,   514,   517,   518,   216,   519,
     265,   217,   343,   520,   521,   522,   239,   523,   361,   254,
     303,   247,   362,   526,   290,   321,   218,   365,   236,   309,
     266,   249,   524,   248,   243,   525,   527,   529,   530,   531,
     304,   219,   264,   344,   220,   322,   221,   222,   272,   615,
     616,   617,   532,   533,   223,   534,   535,   224,   536,   234,
     537,   538,   539,   345,   540,   107,   108,   109,   110,   111,
     541,  1055,     1,     2,     3,     4,     5,     6,     7,     8,
       9,    10,    11,    12,    13,    14,   542,   543,   544,   545,
     546,   547,   548,   549,   550,   552,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   553,   554,   555,   203,   204,
     205,   557,   128,   558,   559,   560,   561,   562,   564,   565,
     563,   566,   568,   206,   570,   130,   131,   207,   208,   209,
     132,   571,   572,   145,   573,   574,   684,   210,   575,   194,
     211,   135,   576,   577,   579,   580,   582,   365,   212,   581,
     583,   584,   585,   587,   588,   589,   700,   591,   130,   131,
     592,   595,   596,   598,   594,   811,   601,   343,   602,   597,
     201,   599,   600,   361,   605,   606,   609,   362,   603,   604,
     612,   610,   613,   621,   614,   618,   619,   620,   622,   623,
     202,   107,   108,   109,   110,   111,   812,   624,   344,   625,
     330,   331,   332,   333,   334,   335,   336,   337,   338,   339,
     340,   341,   342,   626,   627,    94,   813,   628,   345,   142,
     143,   629,   115,   116,   117,   118,   119,   120,   121,   122,
     123,   630,   631,   126,   640,    32,   641,   634,   128,   283,
     642,   643,   705,   648,   644,   645,   647,   649,    94,   650,
     651,   130,   131,   659,   208,   660,   132,   661,   662,   667,
     663,   699,   752,   210,   756,   760,   211,   764,   664,   666,
     668,   670,   671,   672,   212,   673,   674,   691,   768,   675,
     676,   677,   678,   784,   679,   787,   791,   819,   823,   843,
     844,   845,   680,   846,   847,   681,   852,   682,   683,   685,
     686,   687,   698,   853,   854,   855,   856,   857,   863,   903,
     862,   866,   865,   868,   869,   871,   872,   875,   874,   883,
     918,   882,   886,   885,   887,   888,   889,   890,   891,   892,
     908,   919,   907,   921,   912,   911,   910,   914,   915,   916,
     917,    94,   923,   920,   922,   924,   925,   926,   931,  1000,
     927,   928,  1001,  1016,  1017,  1065,  1020,  1036,   929,   930,
     932,   993,   994,   995,   996,   997,   998,  1021,  1037,  1027,
    1028,  1029,  1030,  1031,  1032,  1033,  1041,  1042,  1043,  1044,
    1046,  1047,  1049,  1053,   213,  1057,  1060,   289,   310,  1058,
     308,  1061,  1062,   942,   311,   240,   241,  1064,   973,   214,
     215,   263,   242,   975,   325,   965,  1066,  1067,   943,   944,
     979,   966,  1087,   270,  1088,   238,   980,   811,   303,   271,
    1006,   321,   290,  1089,   963,   309,   246,   216,   954,   977,
     217,  1093,   265,   974,  1097,   239,   945,   646,   304,   946,
    1094,   322,  1095,  1096,   964,   218,   957,   236,   812,   978,
    1099,  1008,   266,   243,   947,  1007,   962,   253,   958,  1100,
     219,   976,   967,   220,   264,   221,   222,   981,   813,   948,
     272,  1009,   949,   223,   950,   951,   224,   254,   234,   247,
     701,   508,   952,   704,   913,   953,   551,   959,   556,   249,
     831,   248,   935,   933,   970,   593,   992,   937,   999,   991,
     936,   969,  1056,   586,   590,   938,   939,   567,  1019,  1018,
     940,   941,   569,   990,   989,   828,  1059,  1002,   818,   607,
     611,   988,   578,   703,  1015,   608,   702,  1063,  1085,  1098,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   942,     0,
       0,     0,     0,   973,     0,     0,     0,     0,   975,     0,
     965,  1006,     0,   943,   944,   979,   966,     0,     0,     0,
       0,   980,     0,     0,     0,     0,     0,     0,     0,   963,
       0,     0,     0,   954,   977,     0,     0,     0,   974,     0,
       0,   945,  1008,     0,   946,     0,  1007,     0,     0,   964,
       0,   957,     0,     0,   978,     0,     0,     0,     0,   947,
       0,   962,  1009,   958,     0,     0,   976,   967,     0,     0,
       0,     0,   981,     0,   948,     0,     0,   949,     0,   950,
     951,     0,     0,     0,     0,     0,     0,   952,     0,     0,
     953,     0,   959
  };

  const short
  Dhcp4Parser::yycheck_[] =
  {
      70,    71,    72,    73,    74,    75,    78,    77,    78,    79,
      80,    76,    78,   625,    73,    73,    80,    75,    73,    73,
      80,    73,    68,    75,    81,   564,     5,    10,     7,   873,
       9,   570,    18,    72,    73,    74,    75,   873,    77,    78,
     873,    80,    77,    78,     7,     3,    73,     3,     6,    73,
     536,   176,     8,    72,    73,    74,    75,    74,    77,    78,
     546,    80,   113,   114,    73,     3,    73,    74,    75,    74,
       8,     0,    73,     3,    75,     7,    15,    16,     8,    73,
      19,     3,    73,    22,    73,    73,     8,    28,    29,    30,
      86,    87,    73,     3,    34,    73,     7,    73,     8,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,   143,   144,   145,
     146,     3,     3,     7,    73,   176,     8,     8,   124,   125,
       3,    72,    73,    74,    74,     8,    85,    86,    87,   116,
     117,   118,   119,   120,   121,    86,    87,    86,    87,    98,
       7,     3,   101,   179,     3,   141,     8,     6,    99,   100,
      74,    75,    76,    77,    78,    79,   149,    11,     3,     3,
      14,     6,    86,    87,     8,     7,   159,   160,   161,    23,
     176,    25,    26,    27,    28,    29,    30,    31,    32,    33,
       3,     3,     7,   176,  1038,     8,     8,   176,   177,   178,
     179,     3,  1038,     7,     6,  1038,   152,     7,    34,   155,
     156,   157,   158,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,    68,     3,     3,   176,    72,    73,
       8,     8,    28,    29,    30,   176,   176,   176,     7,    83,
       3,     3,    86,    87,    72,     8,     8,    91,    74,   861,
      76,    77,    96,    97,    80,    81,    82,    74,   102,     3,
      86,    87,   176,   150,     8,    12,    13,     3,   112,    86,
      87,   115,     8,   113,   114,     3,     3,    73,   122,   123,
       8,     8,   126,   127,   103,   104,   105,   106,     3,   108,
      86,    87,     3,     8,     3,     3,     6,     8,     4,     8,
       8,    97,     7,   147,   148,     7,   150,   103,   104,   105,
     106,   107,   108,   383,   110,     3,     3,    17,    18,     3,
       8,     8,    92,    93,    94,    95,     7,   373,   374,    20,
      21,     8,   176,     3,   151,     4,   153,   154,    35,    36,
      37,    38,   110,   111,     4,     4,     4,     4,     4,     4,
     176,     4,     4,     4,     4,     4,     4,   427,     4,   176,
       4,     4,     4,   433,     3,   176,     4,     8,     8,     4,
       3,     8,     4,     4,     8,   445,     3,   178,   448,     4,
     176,     4,     4,     4,     4,     4,   445,   445,     4,   459,
     445,   445,     4,   445,   433,     4,     4,     4,     4,   469,
       4,   459,   474,     4,   474,     4,   445,   459,   474,   448,
       4,     4,   179,   179,   433,   179,     4,     4,   445,     4,
     459,   445,   492,     4,   177,   177,   445,   177,   492,   448,
     469,   448,   492,   179,   469,   474,   445,   494,   445,   474,
     459,   448,   177,   448,   445,   177,   179,   178,   177,     4,
     469,   445,   459,   492,   445,   474,   445,   445,   459,   505,
     506,   507,     4,     4,   445,     4,     4,   445,     4,   445,
       4,     4,     4,   492,     4,    26,    27,    28,    29,    30,
       4,  1020,   162,   163,   164,   165,   166,   167,   168,   169,
     170,   171,   172,   173,   174,   175,     4,     4,   177,     4,
       4,     4,     4,     4,     4,     4,    57,    58,    59,    60,
      61,    62,    63,    64,    65,     4,     4,   179,    69,    70,
      71,     4,    73,     4,     4,     4,     4,     4,     4,     4,
     177,     4,     4,    84,     4,    86,    87,    88,    89,    90,
      91,     4,     4,   613,     4,     4,   592,    98,     4,   619,
     101,   102,     4,     4,     4,     4,     4,   614,   109,   177,
       4,     4,   179,     4,   179,   179,   612,     4,    86,    87,
       4,     4,     4,     4,   179,   645,     4,   647,     4,   177,
     619,   177,   177,   647,     4,     4,     4,   647,   179,   179,
       4,   177,     7,   176,     7,     7,     7,     7,   176,   176,
     619,    26,    27,    28,    29,    30,   645,     7,   647,     7,
     128,   129,   130,   131,   132,   133,   134,   135,   136,   137,
     138,   139,   140,     5,   176,   176,   645,     5,   647,   147,
     148,     5,    57,    58,    59,    60,    61,    62,    63,    64,
      65,     5,     5,    68,     5,     7,     5,   176,    73,    74,
       5,     5,    24,   176,     7,     7,     7,   176,   176,     5,
       5,    86,    87,   176,    89,   176,    91,   176,     5,     7,
     176,     5,     7,    98,     7,     7,   101,     7,   176,   176,
     176,   176,   176,   176,   109,   176,   176,   142,     7,   176,
     176,   176,   176,     7,   176,     7,     7,     7,     7,     4,
       4,     4,   176,     4,     4,   176,     4,   176,   176,   176,
     176,   176,   176,     4,     4,     4,     4,     4,     3,   176,
       6,     3,     6,     6,     3,     6,     3,     3,     6,     3,
     177,     6,     3,     6,     4,     4,     4,     4,     4,     4,
       3,   179,     6,   179,     4,     6,     8,     4,     4,     4,
       4,   176,     4,   177,   177,     4,     4,     4,   179,     4,
     177,   177,     4,     6,     3,     5,     4,     8,   177,   177,
     177,   177,   177,   177,   177,   177,   177,   176,     8,   176,
     176,   176,   176,   176,   176,   176,     4,     8,     3,     8,
     176,   176,     4,   176,   864,     4,     4,   867,   870,   179,
     870,   177,     4,   873,   870,   864,   864,   176,   878,   864,
     864,   881,   864,   878,   884,   873,   176,     7,   873,   873,
     878,   873,     4,   881,     4,   864,   878,   897,   867,   881,
     900,   870,   867,     4,   873,   870,   906,   864,   873,   878,
     864,     4,   881,   878,     4,   864,   873,   546,   867,   873,
     179,   870,   177,   177,   873,   864,   873,   864,   897,   878,
     176,   900,   881,   864,   873,   900,   873,   906,   873,   176,
     864,   878,   873,   864,   881,   864,   864,   878,   897,   873,
     881,   900,   873,   864,   873,   873,   864,   906,   864,   906,
     613,   383,   873,   619,   837,   873,   427,   873,   433,   906,
     699,   906,   863,   858,   876,   477,   886,   866,   893,   884,
     864,   875,  1038,   469,   474,   867,   869,   445,   908,   906,
     870,   872,   448,   883,   881,   667,  1043,   897,   647,   492,
     498,   879,   459,   618,   901,   494,   614,  1051,  1071,  1091,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1038,    -1,
      -1,    -1,    -1,  1043,    -1,    -1,    -1,    -1,  1043,    -1,
    1038,  1051,    -1,  1038,  1038,  1043,  1038,    -1,    -1,    -1,
      -1,  1043,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1038,
      -1,    -1,    -1,  1038,  1043,    -1,    -1,    -1,  1043,    -1,
      -1,  1038,  1051,    -1,  1038,    -1,  1051,    -1,    -1,  1038,
      -1,  1038,    -1,    -1,  1043,    -1,    -1,    -1,    -1,  1038,
      -1,  1038,  1051,  1038,    -1,    -1,  1043,  1038,    -1,    -1,
      -1,    -1,  1043,    -1,  1038,    -1,    -1,  1038,    -1,  1038,
    1038,    -1,    -1,    -1,    -1,    -1,    -1,  1038,    -1,    -1,
    1038,    -1,  1038
  };

  const unsigned short
  Dhcp4Parser::yystos_[] =
  {
       0,   162,   163,   164,   165,   166,   167,   168,   169,   170,
     171,   172,   173,   174,   175,   181,   182,   183,   184,   185,
     186,   187,   188,   189,   190,   191,   192,   193,   194,   195,
       0,     5,     7,     9,   176,   177,   178,   179,   196,   197,
     198,   203,     7,   212,     7,   218,     7,   241,     7,   339,
       7,   419,     7,   435,     7,   371,     7,   377,     7,   401,
       7,   315,     7,   492,     7,   539,     7,   530,   204,   199,
     213,   219,   242,   340,   420,   436,   372,   378,   402,   316,
     493,   540,   531,   196,   205,   206,   176,   201,   202,    10,
     149,   159,   160,   161,   176,   211,   214,   215,   216,   522,
     524,   526,   537,    11,    14,    23,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    68,    72,    73,    83,
      86,    87,    91,    96,    97,   102,   112,   115,   122,   123,
     126,   127,   147,   148,   150,   211,   220,   221,   222,   223,
     224,   225,   226,   227,   228,   229,   230,   231,   232,   234,
     235,   236,   237,   252,   254,   260,   262,   300,   309,   323,
     333,   357,   361,   369,   395,   425,   427,   429,   440,   442,
     444,   467,   479,   480,   488,   490,   518,   520,   528,   543,
      15,    16,    19,    22,   211,   239,   240,   243,   245,   248,
     251,   425,   427,    69,    70,    71,    84,    88,    89,    90,
      98,   101,   109,   211,   222,   223,   224,   225,   226,   227,
     228,   229,   230,   235,   236,   341,   342,   343,   345,   347,
     349,   351,   353,   355,   357,   360,   395,   413,   425,   427,
     429,   440,   442,   444,   464,    85,   211,   353,   355,   395,
     421,   422,   423,   425,   427,    97,   103,   104,   105,   106,
     107,   108,   110,   211,   395,   425,   427,   437,   438,   439,
     440,   442,   444,   446,   450,   452,   454,   456,   458,   460,
     462,   369,    34,    74,    76,    77,    80,    81,    82,   211,
     280,   379,   380,   381,   382,   383,   384,   385,   387,   389,
     391,   392,   394,   425,   427,    75,    78,    79,   211,   280,
     383,   389,   403,   404,   405,   406,   407,   409,   410,   411,
     412,   425,   427,   113,   114,   211,   317,   318,   319,   321,
     128,   129,   130,   131,   132,   133,   134,   135,   136,   137,
     138,   139,   140,   211,   425,   427,   494,   495,   496,   497,
     499,   501,   502,   504,   505,   506,   509,   511,   512,   513,
     516,   518,   520,   541,   542,   543,    12,    13,   532,   533,
     534,   536,     6,     3,     4,     8,     3,   217,   538,   523,
     525,   527,     4,     3,     8,   529,   238,   255,     4,     4,
       4,   441,   443,   445,   253,   261,   263,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,   233,   334,   370,
     396,   362,   426,   428,   358,   301,   468,   430,   310,   324,
       4,   481,   489,   491,   519,   521,   544,     3,     8,   244,
     246,   249,     4,     3,     8,   346,   348,   350,   414,   344,
     352,     4,   356,   354,   465,     3,     8,   424,     3,     8,
     463,   451,   453,   457,   455,   461,   459,   447,     8,     3,
       8,   386,   281,     4,   390,   388,   393,     4,     8,     3,
     408,     4,     4,     8,     3,   320,   322,     3,     8,     4,
     498,   500,     4,   503,     4,     4,   507,   510,     4,     4,
     514,   517,     3,     8,     3,     8,   535,     4,     3,     8,
     196,   196,   176,     4,     4,     4,     4,     4,   215,     4,
       4,     4,   179,   179,   179,     4,     4,     4,     4,     4,
       4,   177,   177,   177,   177,   177,   179,   179,   178,   178,
     177,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,   177,     4,     4,     4,     4,     4,
       4,   221,     4,     4,     4,   179,   240,     4,     4,     4,
       4,     4,     4,   177,     4,     4,     4,   342,     4,   422,
       4,     4,     4,     4,     4,     4,     4,     4,   439,     4,
       4,   177,     4,     4,     4,   179,   381,     4,   179,   179,
     405,     4,     4,   318,   179,     4,     4,   177,     4,   177,
     177,     4,     4,   179,   179,     4,     4,   495,   542,     4,
     177,   533,     4,     7,     7,   196,   196,   196,     7,     7,
       7,   176,   176,   176,     7,     7,     5,   176,     5,     5,
       5,     5,   198,   200,   176,    92,    93,    94,    95,   359,
       5,     5,     5,     5,     7,     7,   200,     7,   176,   176,
       5,     5,   207,    17,    18,   247,    20,    21,   250,   176,
     176,   176,     5,   176,   176,   207,   176,     7,   176,   207,
     176,   176,   176,   176,   176,   176,   176,   176,   176,   176,
     176,   176,   176,   176,   196,   176,   176,   176,    18,   141,
     508,   142,   143,   144,   145,   146,   179,   515,   176,     5,
     196,   220,   541,   532,   239,    24,   256,   257,   258,    34,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    55,    56,   211,   268,
     269,   270,   273,   275,   277,   279,   280,   282,   283,   284,
     285,   286,   287,   288,   289,   291,   293,   295,   297,   298,
     299,   268,     7,   264,   265,   266,     7,   335,   336,   337,
       7,   373,   374,   375,     7,   397,   398,   399,     7,   363,
     364,   365,   103,   104,   105,   106,   108,   302,   303,   304,
     305,   306,   307,   308,     7,   469,   470,     7,   431,   432,
     433,     7,   311,   312,   313,   116,   117,   118,   119,   120,
     121,   325,   326,   327,   328,   329,   330,   331,   332,   124,
     125,   211,   425,   427,   482,   483,   484,   486,   494,     7,
     545,   546,   208,     7,   415,   416,   417,   111,   446,   448,
     466,   264,     8,     8,     8,     8,   259,     3,     8,   271,
     274,   276,   278,     4,     4,     4,     4,     4,   290,   292,
     294,   296,     4,     4,     4,     4,     4,     4,     3,     8,
       8,   267,     6,     3,   338,     6,     3,   376,     6,     3,
     400,     6,     3,   366,     6,     3,     3,     6,   471,     3,
       6,   434,     6,     3,   314,     6,     3,     4,     4,     4,
       4,     4,     4,     3,     8,   485,   487,     3,     8,     8,
     547,     3,     6,   176,   209,   210,   418,     6,     3,   449,
       8,     6,     4,   257,     4,     4,     4,     4,   177,   179,
     177,   179,   177,     4,     4,     4,     4,   177,   177,   177,
     177,   179,   177,   269,   268,   266,   341,   337,   379,   375,
     403,   399,   211,   222,   223,   224,   225,   226,   227,   228,
     229,   230,   235,   236,   280,   333,   351,   353,   355,   357,
     367,   368,   395,   425,   427,   440,   442,   444,   464,   365,
     303,    99,   100,   211,   280,   369,   395,   425,   427,   440,
     442,   444,   472,   473,   474,   475,   476,   478,   470,   437,
     433,   317,   313,   177,   177,   177,   177,   177,   177,   326,
       4,     4,   483,   151,   153,   154,   211,   280,   425,   427,
     548,   549,   550,   551,   553,   546,     6,     3,   421,   417,
       4,   176,    35,    36,    37,    38,   272,   176,   176,   176,
     176,   176,   176,   176,     8,     8,     8,     8,     3,     8,
     477,     4,     8,     3,     8,     8,   176,   176,   554,     4,
     552,     3,     8,   176,     8,   207,   368,     4,   179,   474,
       4,   177,     4,   549,   176,     5,   176,     7,   555,   556,
     557,     3,     6,   152,   155,   156,   157,   158,   558,   559,
     560,   562,   563,   564,   565,   556,   561,     4,     4,     4,
     566,     3,     8,     4,   179,   177,   177,     4,   559,   176,
     176
  };

  const unsigned short
  Dhcp4Parser::yyr1_[] =
  {
       0,   180,   182,   181,   183,   181,   184,   181,   185,   181,
     186,   181,   187,   181,   188,   181,   189,   181,   190,   181,
     191,   181,   192,   181,   193,   181,   194,   181,   195,   181,
     196,   196,   196,   196,   196,   196,   196,   197,   199,   198,
     200,   201,   201,   202,   202,   204,   203,   205,   205,   206,
     206,   208,   207,   209,   209,   210,   210,   211,   213,   212,
     214,   214,   215,   215,   215,   215,   215,   215,   217,   216,
     219,   218,   220,   220,   221,   221,   221,   221,   221,   221,
     221,   221,   221,   221,   221,   221,   221,   221,   221,   221,
     221,   221,   221,   221,   221,   221,   221,   221,   221,   221,
     221,   221,   221,   221,   221,   221,   221,   221,   221,   221,
     221,   221,   221,   221,   221,   221,   221,   222,   223,   224,
     225,   226,   227,   228,   229,   230,   231,   233,   232,   234,
     235,   236,   238,   237,   239,   239,   240,   240,   240,   240,
     240,   240,   240,   242,   241,   244,   243,   246,   245,   247,
     247,   249,   248,   250,   250,   251,   253,   252,   255,   254,
     256,   256,   257,   259,   258,   261,   260,   263,   262,   264,
     264,   265,   265,   267,   266,   268,   268,   269,   269,   269,
     269,   269,   269,   269,   269,   269,   269,   269,   269,   269,
     269,   269,   269,   269,   269,   269,   269,   269,   271,   270,
     272,   272,   272,   272,   274,   273,   276,   275,   278,   277,
     279,   281,   280,   282,   283,   284,   285,   286,   287,   288,
     290,   289,   292,   291,   294,   293,   296,   295,   297,   298,
     299,   301,   300,   302,   302,   303,   303,   303,   303,   303,
     304,   305,   306,   307,   308,   310,   309,   311,   311,   312,
     312,   314,   313,   316,   315,   317,   317,   317,   318,   318,
     320,   319,   322,   321,   324,   323,   325,   325,   326,   326,
     326,   326,   326,   326,   327,   328,   329,   330,   331,   332,
     334,   333,   335,   335,   336,   336,   338,   337,   340,   339,
     341,   341,   342,   342,   342,   342,   342,   342,   342,   342,
     342,   342,   342,   342,   342,   342,   342,   342,   342,   342,
     342,   342,   342,   342,   342,   342,   342,   342,   342,   342,
     342,   342,   344,   343,   346,   345,   348,   347,   350,   349,
     352,   351,   354,   353,   356,   355,   358,   357,   359,   359,
     359,   359,   360,   362,   361,   363,   363,   364,   364,   366,
     365,   367,   367,   368,   368,   368,   368,   368,   368,   368,
     368,   368,   368,   368,   368,   368,   368,   368,   368,   368,
     368,   368,   368,   368,   368,   368,   368,   368,   370,   369,
     372,   371,   373,   373,   374,   374,   376,   375,   378,   377,
     379,   379,   380,   380,   381,   381,   381,   381,   381,   381,
     381,   381,   381,   381,   382,   383,   384,   386,   385,   388,
     387,   390,   389,   391,   393,   392,   394,   396,   395,   397,
     397,   398,   398,   400,   399,   402,   401,   403,   403,   404,
     404,   405,   405,   405,   405,   405,   405,   405,   405,   405,
     406,   408,   407,   409,   410,   411,   412,   414,   413,   415,
     415,   416,   416,   418,   417,   420,   419,   421,   421,   422,
     422,   422,   422,   422,   422,   422,   424,   423,   426,   425,
     428,   427,   430,   429,   431,   431,   432,   432,   434,   433,
     436,   435,   437,   437,   438,   438,   439,   439,   439,   439,
     439,   439,   439,   439,   439,   439,   439,   439,   439,   439,
     439,   441,   440,   443,   442,   445,   444,   447,   446,   449,
     448,   451,   450,   453,   452,   455,   454,   457,   456,   459,
     458,   461,   460,   463,   462,   465,   464,   466,   466,   468,
     467,   469,   469,   471,   470,   472,   472,   473,   473,   474,
     474,   474,   474,   474,   474,   474,   474,   474,   474,   474,
     475,   477,   476,   478,   479,   481,   480,   482,   482,   483,
     483,   483,   483,   483,   485,   484,   487,   486,   489,   488,
     491,   490,   493,   492,   494,   494,   495,   495,   495,   495,
     495,   495,   495,   495,   495,   495,   495,   495,   495,   495,
     495,   495,   495,   495,   496,   498,   497,   500,   499,   501,
     503,   502,   504,   505,   507,   506,   508,   508,   510,   509,
     511,   512,   514,   513,   515,   515,   515,   515,   515,   517,
     516,   519,   518,   521,   520,   523,   522,   525,   524,   527,
     526,   529,   528,   531,   530,   532,   532,   533,   533,   535,
     534,   536,   538,   537,   540,   539,   541,   541,   542,   544,
     543,   545,   545,   547,   546,   548,   548,   549,   549,   549,
     549,   549,   549,   549,   550,   552,   551,   554,   553,   555,
     555,   557,   556,   558,   558,   559,   559,   559,   559,   559,
     561,   560,   562,   563,   564,   566,   565
  };

  const unsigned char
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
       1,     1,     1,     1,     1,     1,     1,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     0,     4,     3,
       3,     3,     0,     6,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     0,     4,     0,     4,     0,     4,     1,
       1,     0,     4,     1,     1,     3,     0,     6,     0,     6,
       1,     3,     1,     0,     4,     0,     6,     0,     6,     0,
       1,     1,     3,     0,     4,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       1,     1,     1,     1,     0,     4,     0,     4,     0,     4,
       3,     0,     4,     3,     3,     3,     3,     3,     3,     3,
       0,     4,     0,     4,     0,     4,     0,     4,     3,     3,
       3,     0,     6,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     6,     0,     1,     1,
       3,     0,     4,     0,     4,     1,     3,     1,     1,     1,
       0,     4,     0,     4,     0,     6,     1,     3,     1,     1,
       1,     1,     1,     1,     3,     3,     3,     3,     3,     3,
       0,     6,     0,     1,     1,     3,     0,     4,     0,     4,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     4,     0,     4,     1,     1,
       1,     1,     3,     0,     6,     0,     1,     1,     3,     0,
       4,     1,     3,     1,     1,     1,     1,     1,     1,     1,
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
       1,     1,     1,     1,     0,     4,     0,     4,     0,     4,
       0,     6,     0,     4,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     3,     0,     4,     0,     4,     3,
       0,     4,     3,     3,     0,     4,     1,     1,     0,     4,
       3,     3,     0,     4,     1,     1,     1,     1,     1,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     6,     0,     4,     1,     3,     1,     1,     0,
       6,     3,     0,     6,     0,     4,     1,     3,     1,     0,
       6,     1,     3,     0,     4,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     3,     0,     4,     0,     6,     1,
       3,     0,     4,     1,     3,     1,     1,     1,     1,     1,
       0,     4,     3,     3,     3,     0,     4
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
  "\"rebind-timer\"", "\"allow-static-leases\"", "\"calculate-tee-times\"",
  "\"t1-percent\"", "\"t2-percent\"", "\"decline-probation-period\"",
  "\"server-tag\"", "\"subnet4\"", "\"4o6-interface\"",
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
  "\"socket-name\"", "\"dhcp-queue-control\"", "\"dhcp-ddns\"",
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
  "rebind_timer", "allow_static_leases", "calculate_tee_times",
  "t1_percent", "t2_percent", "decline_probation_period", "server_tag",
  "$@21", "echo_client_id", "match_client_id", "authoritative",
  "interfaces_config", "$@22", "interfaces_config_params",
  "interfaces_config_param", "sub_interfaces4", "$@23", "interfaces_list",
  "$@24", "dhcp_socket_type", "$@25", "socket_type", "outbound_interface",
  "$@26", "outbound_interface_value", "re_detect", "lease_database",
  "$@27", "sanity_checks", "$@28", "sanity_checks_params",
  "sanity_checks_param", "lease_checks", "$@29", "hosts_database", "$@30",
  "hosts_databases", "$@31", "database_list", "not_empty_database_list",
  "database", "$@32", "database_map_params", "database_map_param",
  "database_type", "$@33", "db_type", "user", "$@34", "password", "$@35",
  "host", "$@36", "port", "name", "$@37", "persist", "lfc_interval",
  "readonly", "connect_timeout", "request_timeout", "tcp_keepalive",
  "tcp_nodelay", "contact_points", "$@38", "keyspace", "$@39",
  "consistency", "$@40", "serial_consistency", "$@41",
  "max_reconnect_tries", "reconnect_wait_time", "max_row_errors",
  "host_reservation_identifiers", "$@42",
  "host_reservation_identifiers_list", "host_reservation_identifier",
  "duid_id", "hw_address_id", "circuit_id", "client_id", "flex_id",
  "hooks_libraries", "$@43", "hooks_libraries_list",
  "not_empty_hooks_libraries_list", "hooks_library", "$@44",
  "sub_hooks_library", "$@45", "hooks_params", "hooks_param", "library",
  "$@46", "parameters", "$@47", "expired_leases_processing", "$@48",
  "expired_leases_params", "expired_leases_param",
  "reclaim_timer_wait_time", "flush_reclaimed_timer_wait_time",
  "hold_reclaimed_time", "max_reclaim_leases", "max_reclaim_time",
  "unwarned_reclaim_cycles", "subnet4_list", "$@49",
  "subnet4_list_content", "not_empty_subnet4_list", "subnet4", "$@50",
  "sub_subnet4", "$@51", "subnet4_params", "subnet4_param", "subnet",
  "$@52", "subnet_4o6_interface", "$@53", "subnet_4o6_interface_id",
  "$@54", "subnet_4o6_subnet", "$@55", "interface", "$@56", "client_class",
  "$@57", "require_client_classes", "$@58", "reservation_mode", "$@59",
  "hr_mode", "id", "shared_networks", "$@60", "shared_networks_content",
  "shared_networks_list", "shared_network", "$@61",
  "shared_network_params", "shared_network_param", "option_def_list",
  "$@62", "sub_option_def_list", "$@63", "option_def_list_content",
  "not_empty_option_def_list", "option_def_entry", "$@64",
  "sub_option_def", "$@65", "option_def_params",
  "not_empty_option_def_params", "option_def_param", "option_def_name",
  "code", "option_def_code", "option_def_type", "$@66",
  "option_def_record_types", "$@67", "space", "$@68", "option_def_space",
  "option_def_encapsulate", "$@69", "option_def_array", "option_data_list",
  "$@70", "option_data_list_content", "not_empty_option_data_list",
  "option_data_entry", "$@71", "sub_option_data", "$@72",
  "option_data_params", "not_empty_option_data_params",
  "option_data_param", "option_data_name", "option_data_data", "$@73",
  "option_data_code", "option_data_space", "option_data_csv_format",
  "option_data_always_send", "pools_list", "$@74", "pools_list_content",
  "not_empty_pools_list", "pool_list_entry", "$@75", "sub_pool4", "$@76",
  "pool_params", "pool_param", "pool_entry", "$@77", "user_context",
  "$@78", "comment", "$@79", "reservations", "$@80", "reservations_list",
  "not_empty_reservations_list", "reservation", "$@81", "sub_reservation",
  "$@82", "reservation_params", "not_empty_reservation_params",
  "reservation_param", "next_server", "$@83", "server_hostname", "$@84",
  "boot_file_name", "$@85", "ip_address", "$@86", "ip_addresses", "$@87",
  "duid", "$@88", "hw_address", "$@89", "client_id_value", "$@90",
  "circuit_id_value", "$@91", "flex_id_value", "$@92", "hostname", "$@93",
  "reservation_client_classes", "$@94", "relay", "$@95", "relay_map",
  "client_classes", "$@96", "client_classes_list", "client_class_entry",
  "$@97", "client_class_params", "not_empty_client_class_params",
  "client_class_param", "client_class_name", "client_class_test", "$@98",
  "only_if_required", "dhcp4o6_port", "control_socket", "$@99",
  "control_socket_params", "control_socket_param", "control_socket_type",
  "$@100", "control_socket_name", "$@101", "dhcp_queue_control", "$@102",
  "dhcp_ddns", "$@103", "sub_dhcp_ddns", "$@104", "dhcp_ddns_params",
  "dhcp_ddns_param", "enable_updates", "qualifying_suffix", "$@105",
  "server_ip", "$@106", "server_port", "sender_ip", "$@107", "sender_port",
  "max_queue_size", "ncr_protocol", "$@108", "ncr_protocol_value",
  "ncr_format", "$@109", "override_no_update", "override_client_update",
  "replace_client_name", "$@110", "replace_client_name_value",
  "generated_prefix", "$@111", "hostname_char_set", "$@112",
  "hostname_char_replacement", "$@113", "dhcp6_json_object", "$@114",
  "dhcpddns_json_object", "$@115", "control_agent_json_object", "$@116",
  "config_control", "$@117", "sub_config_control", "$@118",
  "config_control_params", "config_control_param", "config_databases",
  "$@119", "config_fetch_wait_time", "logging_object", "$@120",
  "sub_logging", "$@121", "logging_params", "logging_param", "loggers",
  "$@122", "loggers_entries", "logger_entry", "$@123", "logger_params",
  "logger_param", "debuglevel", "severity", "$@124", "output_options_list",
  "$@125", "output_options_list_content", "output_entry", "$@126",
  "output_params_list", "output_params", "output", "$@127", "flush",
  "maxsize", "maxver", "pattern", "$@128", YY_NULLPTR
  };

#if PARSER4_DEBUG
  const unsigned short
  Dhcp4Parser::yyrline_[] =
  {
       0,   267,   267,   267,   268,   268,   269,   269,   270,   270,
     271,   271,   272,   272,   273,   273,   274,   274,   275,   275,
     276,   276,   277,   277,   278,   278,   279,   279,   280,   280,
     288,   289,   290,   291,   292,   293,   294,   297,   302,   302,
     313,   316,   317,   320,   324,   331,   331,   338,   339,   342,
     346,   353,   353,   360,   361,   364,   368,   379,   389,   389,
     405,   406,   410,   411,   412,   413,   414,   415,   418,   418,
     433,   433,   442,   443,   448,   449,   450,   451,   452,   453,
     454,   455,   456,   457,   458,   459,   460,   461,   462,   463,
     464,   465,   466,   467,   468,   469,   470,   471,   472,   473,
     474,   475,   476,   477,   478,   479,   480,   481,   482,   483,
     484,   485,   486,   487,   488,   489,   490,   493,   498,   503,
     508,   513,   518,   523,   528,   533,   538,   543,   543,   551,
     556,   561,   567,   567,   578,   579,   582,   583,   584,   585,
     586,   587,   588,   591,   591,   600,   600,   610,   610,   617,
     618,   621,   621,   628,   630,   634,   640,   640,   652,   652,
     662,   663,   665,   667,   667,   685,   685,   697,   697,   707,
     708,   711,   712,   715,   715,   725,   726,   729,   730,   731,
     732,   733,   734,   735,   736,   737,   738,   739,   740,   741,
     742,   743,   744,   745,   746,   747,   748,   749,   752,   752,
     759,   760,   761,   762,   765,   765,   773,   773,   781,   781,
     789,   794,   794,   802,   807,   812,   817,   822,   827,   832,
     837,   837,   845,   845,   853,   853,   861,   861,   869,   874,
     879,   885,   885,   895,   896,   899,   900,   901,   902,   903,
     906,   911,   916,   921,   926,   931,   931,   941,   942,   945,
     946,   949,   949,   959,   959,   969,   970,   971,   974,   975,
     978,   978,   986,   986,   994,   994,  1005,  1006,  1009,  1010,
    1011,  1012,  1013,  1014,  1017,  1022,  1027,  1032,  1037,  1042,
    1050,  1050,  1063,  1064,  1067,  1068,  1075,  1075,  1101,  1101,
    1112,  1113,  1117,  1118,  1119,  1120,  1121,  1122,  1123,  1124,
    1125,  1126,  1127,  1128,  1129,  1130,  1131,  1132,  1133,  1134,
    1135,  1136,  1137,  1138,  1139,  1140,  1141,  1142,  1143,  1144,
    1145,  1146,  1149,  1149,  1157,  1157,  1165,  1165,  1173,  1173,
    1181,  1181,  1189,  1189,  1197,  1197,  1207,  1207,  1214,  1215,
    1216,  1217,  1220,  1227,  1227,  1238,  1239,  1243,  1244,  1247,
    1247,  1255,  1256,  1259,  1260,  1261,  1262,  1263,  1264,  1265,
    1266,  1267,  1268,  1269,  1270,  1271,  1272,  1273,  1274,  1275,
    1276,  1277,  1278,  1279,  1280,  1281,  1282,  1283,  1290,  1290,
    1303,  1303,  1312,  1313,  1316,  1317,  1322,  1322,  1337,  1337,
    1351,  1352,  1355,  1356,  1359,  1360,  1361,  1362,  1363,  1364,
    1365,  1366,  1367,  1368,  1371,  1373,  1378,  1380,  1380,  1388,
    1388,  1396,  1396,  1404,  1406,  1406,  1414,  1423,  1423,  1435,
    1436,  1441,  1442,  1447,  1447,  1459,  1459,  1471,  1472,  1477,
    1478,  1483,  1484,  1485,  1486,  1487,  1488,  1489,  1490,  1491,
    1494,  1496,  1496,  1504,  1506,  1508,  1513,  1521,  1521,  1533,
    1534,  1537,  1538,  1541,  1541,  1551,  1551,  1561,  1562,  1565,
    1566,  1567,  1568,  1569,  1570,  1571,  1574,  1574,  1582,  1582,
    1607,  1607,  1637,  1637,  1647,  1648,  1651,  1652,  1655,  1655,
    1664,  1664,  1673,  1674,  1677,  1678,  1682,  1683,  1684,  1685,
    1686,  1687,  1688,  1689,  1690,  1691,  1692,  1693,  1694,  1695,
    1696,  1699,  1699,  1707,  1707,  1715,  1715,  1723,  1723,  1731,
    1731,  1741,  1741,  1749,  1749,  1757,  1757,  1765,  1765,  1773,
    1773,  1781,  1781,  1789,  1789,  1802,  1802,  1812,  1813,  1819,
    1819,  1829,  1830,  1833,  1833,  1843,  1844,  1847,  1848,  1851,
    1852,  1853,  1854,  1855,  1856,  1857,  1858,  1859,  1860,  1861,
    1864,  1866,  1866,  1874,  1883,  1890,  1890,  1900,  1901,  1904,
    1905,  1906,  1907,  1908,  1911,  1911,  1919,  1919,  1930,  1930,
    1968,  1968,  1980,  1980,  1990,  1991,  1994,  1995,  1996,  1997,
    1998,  1999,  2000,  2001,  2002,  2003,  2004,  2005,  2006,  2007,
    2008,  2009,  2010,  2011,  2014,  2019,  2019,  2027,  2027,  2035,
    2040,  2040,  2048,  2053,  2058,  2058,  2066,  2067,  2070,  2070,
    2078,  2083,  2088,  2088,  2096,  2099,  2102,  2105,  2108,  2114,
    2114,  2122,  2122,  2130,  2130,  2141,  2141,  2148,  2148,  2155,
    2155,  2162,  2162,  2173,  2173,  2183,  2184,  2188,  2189,  2192,
    2192,  2202,  2212,  2212,  2222,  2222,  2233,  2234,  2238,  2242,
    2242,  2254,  2255,  2259,  2259,  2267,  2268,  2271,  2272,  2273,
    2274,  2275,  2276,  2277,  2280,  2285,  2285,  2293,  2293,  2303,
    2304,  2307,  2307,  2315,  2316,  2319,  2320,  2321,  2322,  2323,
    2326,  2326,  2334,  2339,  2344,  2349,  2349
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
      *yycdebug_ << ' ' << i->state;
    *yycdebug_ << '\n';
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  Dhcp4Parser::yy_reduce_print_ (int yyrule)
  {
    unsigned yylno = yyrline_[yyrule];
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
#line 5143 "dhcp4_parser.cc"

#line 2358 "dhcp4_parser.yy"


void
isc::dhcp::Dhcp4Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
