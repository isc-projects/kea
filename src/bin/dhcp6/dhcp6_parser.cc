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


// Suppress unused-variable warnings by "using" E.
#define YYUSE(E) ((void) (E))

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
#line 146 "dhcp6_parser.cc"


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
    :
#if PARSER6_DEBUG
      yydebug_ (false),
      yycdebug_ (&std::cerr),
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
      return yystos_[state];
  }

  Dhcp6Parser::stack_symbol_type::stack_symbol_type ()
  {}

  Dhcp6Parser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state), YY_MOVE (that.location))
  {
    switch (that.type_get ())
    {
      case 198: // value
      case 202: // map_value
      case 259: // db_type
      case 352: // hr_mode
      case 488: // duid_type
      case 523: // ncr_protocol_value
      case 530: // replace_client_name_value
        value.YY_MOVE_OR_COPY< ElementPtr > (YY_MOVE (that.value));
        break;

      case 180: // "boolean"
        value.YY_MOVE_OR_COPY< bool > (YY_MOVE (that.value));
        break;

      case 179: // "floating point"
        value.YY_MOVE_OR_COPY< double > (YY_MOVE (that.value));
        break;

      case 178: // "integer"
        value.YY_MOVE_OR_COPY< int64_t > (YY_MOVE (that.value));
        break;

      case 177: // "constant string"
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
      case 198: // value
      case 202: // map_value
      case 259: // db_type
      case 352: // hr_mode
      case 488: // duid_type
      case 523: // ncr_protocol_value
      case 530: // replace_client_name_value
        value.move< ElementPtr > (YY_MOVE (that.value));
        break;

      case 180: // "boolean"
        value.move< bool > (YY_MOVE (that.value));
        break;

      case 179: // "floating point"
        value.move< double > (YY_MOVE (that.value));
        break;

      case 178: // "integer"
        value.move< int64_t > (YY_MOVE (that.value));
        break;

      case 177: // "constant string"
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
  Dhcp6Parser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    switch (that.type_get ())
    {
      case 198: // value
      case 202: // map_value
      case 259: // db_type
      case 352: // hr_mode
      case 488: // duid_type
      case 523: // ncr_protocol_value
      case 530: // replace_client_name_value
        value.move< ElementPtr > (that.value);
        break;

      case 180: // "boolean"
        value.move< bool > (that.value);
        break;

      case 179: // "floating point"
        value.move< double > (that.value);
        break;

      case 178: // "integer"
        value.move< int64_t > (that.value);
        break;

      case 177: // "constant string"
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
      case 177: // "constant string"
#line 256 "dhcp6_parser.yy"
        { yyoutput << yysym.value.template as < std::string > (); }
#line 405 "dhcp6_parser.cc"
        break;

      case 178: // "integer"
#line 256 "dhcp6_parser.yy"
        { yyoutput << yysym.value.template as < int64_t > (); }
#line 411 "dhcp6_parser.cc"
        break;

      case 179: // "floating point"
#line 256 "dhcp6_parser.yy"
        { yyoutput << yysym.value.template as < double > (); }
#line 417 "dhcp6_parser.cc"
        break;

      case 180: // "boolean"
#line 256 "dhcp6_parser.yy"
        { yyoutput << yysym.value.template as < bool > (); }
#line 423 "dhcp6_parser.cc"
        break;

      case 198: // value
#line 256 "dhcp6_parser.yy"
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 429 "dhcp6_parser.cc"
        break;

      case 202: // map_value
#line 256 "dhcp6_parser.yy"
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 435 "dhcp6_parser.cc"
        break;

      case 259: // db_type
#line 256 "dhcp6_parser.yy"
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 441 "dhcp6_parser.cc"
        break;

      case 352: // hr_mode
#line 256 "dhcp6_parser.yy"
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 447 "dhcp6_parser.cc"
        break;

      case 488: // duid_type
#line 256 "dhcp6_parser.yy"
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 453 "dhcp6_parser.cc"
        break;

      case 523: // ncr_protocol_value
#line 256 "dhcp6_parser.yy"
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 459 "dhcp6_parser.cc"
        break;

      case 530: // replace_client_name_value
#line 256 "dhcp6_parser.yy"
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 465 "dhcp6_parser.cc"
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
      case 198: // value
      case 202: // map_value
      case 259: // db_type
      case 352: // hr_mode
      case 488: // duid_type
      case 523: // ncr_protocol_value
      case 530: // replace_client_name_value
        yylhs.value.emplace< ElementPtr > ();
        break;

      case 180: // "boolean"
        yylhs.value.emplace< bool > ();
        break;

      case 179: // "floating point"
        yylhs.value.emplace< double > ();
        break;

      case 178: // "integer"
        yylhs.value.emplace< int64_t > ();
        break;

      case 177: // "constant string"
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
#line 265 "dhcp6_parser.yy"
    { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 731 "dhcp6_parser.cc"
    break;

  case 4:
#line 266 "dhcp6_parser.yy"
    { ctx.ctx_ = ctx.CONFIG; }
#line 737 "dhcp6_parser.cc"
    break;

  case 6:
#line 267 "dhcp6_parser.yy"
    { ctx.ctx_ = ctx.DHCP6; }
#line 743 "dhcp6_parser.cc"
    break;

  case 8:
#line 268 "dhcp6_parser.yy"
    { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 749 "dhcp6_parser.cc"
    break;

  case 10:
#line 269 "dhcp6_parser.yy"
    { ctx.ctx_ = ctx.SUBNET6; }
#line 755 "dhcp6_parser.cc"
    break;

  case 12:
#line 270 "dhcp6_parser.yy"
    { ctx.ctx_ = ctx.POOLS; }
#line 761 "dhcp6_parser.cc"
    break;

  case 14:
#line 271 "dhcp6_parser.yy"
    { ctx.ctx_ = ctx.PD_POOLS; }
#line 767 "dhcp6_parser.cc"
    break;

  case 16:
#line 272 "dhcp6_parser.yy"
    { ctx.ctx_ = ctx.RESERVATIONS; }
#line 773 "dhcp6_parser.cc"
    break;

  case 18:
#line 273 "dhcp6_parser.yy"
    { ctx.ctx_ = ctx.DHCP6; }
#line 779 "dhcp6_parser.cc"
    break;

  case 20:
#line 274 "dhcp6_parser.yy"
    { ctx.ctx_ = ctx.OPTION_DEF; }
#line 785 "dhcp6_parser.cc"
    break;

  case 22:
#line 275 "dhcp6_parser.yy"
    { ctx.ctx_ = ctx.OPTION_DATA; }
#line 791 "dhcp6_parser.cc"
    break;

  case 24:
#line 276 "dhcp6_parser.yy"
    { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 797 "dhcp6_parser.cc"
    break;

  case 26:
#line 277 "dhcp6_parser.yy"
    { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 803 "dhcp6_parser.cc"
    break;

  case 28:
#line 278 "dhcp6_parser.yy"
    { ctx.ctx_ = ctx.LOGGING; }
#line 809 "dhcp6_parser.cc"
    break;

  case 30:
#line 279 "dhcp6_parser.yy"
    { ctx.ctx_ = ctx.CONFIG_CONTROL; }
#line 815 "dhcp6_parser.cc"
    break;

  case 32:
#line 287 "dhcp6_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 821 "dhcp6_parser.cc"
    break;

  case 33:
#line 288 "dhcp6_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location))); }
#line 827 "dhcp6_parser.cc"
    break;

  case 34:
#line 289 "dhcp6_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 833 "dhcp6_parser.cc"
    break;

  case 35:
#line 290 "dhcp6_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 839 "dhcp6_parser.cc"
    break;

  case 36:
#line 291 "dhcp6_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 845 "dhcp6_parser.cc"
    break;

  case 37:
#line 292 "dhcp6_parser.yy"
    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 851 "dhcp6_parser.cc"
    break;

  case 38:
#line 293 "dhcp6_parser.yy"
    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 857 "dhcp6_parser.cc"
    break;

  case 39:
#line 296 "dhcp6_parser.yy"
    {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as < ElementPtr > ());
}
#line 866 "dhcp6_parser.cc"
    break;

  case 40:
#line 301 "dhcp6_parser.yy"
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 877 "dhcp6_parser.cc"
    break;

  case 41:
#line 306 "dhcp6_parser.yy"
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 887 "dhcp6_parser.cc"
    break;

  case 42:
#line 312 "dhcp6_parser.yy"
    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 893 "dhcp6_parser.cc"
    break;

  case 45:
#line 319 "dhcp6_parser.yy"
    {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 902 "dhcp6_parser.cc"
    break;

  case 46:
#line 323 "dhcp6_parser.yy"
    {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 912 "dhcp6_parser.cc"
    break;

  case 47:
#line 330 "dhcp6_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 921 "dhcp6_parser.cc"
    break;

  case 48:
#line 333 "dhcp6_parser.yy"
    {
    // list parsing complete. Put any sanity checking here
}
#line 929 "dhcp6_parser.cc"
    break;

  case 51:
#line 341 "dhcp6_parser.yy"
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 938 "dhcp6_parser.cc"
    break;

  case 52:
#line 345 "dhcp6_parser.yy"
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 947 "dhcp6_parser.cc"
    break;

  case 53:
#line 352 "dhcp6_parser.yy"
    {
    // List parsing about to start
}
#line 955 "dhcp6_parser.cc"
    break;

  case 54:
#line 354 "dhcp6_parser.yy"
    {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 964 "dhcp6_parser.cc"
    break;

  case 57:
#line 363 "dhcp6_parser.yy"
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 973 "dhcp6_parser.cc"
    break;

  case 58:
#line 367 "dhcp6_parser.yy"
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 982 "dhcp6_parser.cc"
    break;

  case 59:
#line 378 "dhcp6_parser.yy"
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as < std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 993 "dhcp6_parser.cc"
    break;

  case 60:
#line 388 "dhcp6_parser.yy"
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1004 "dhcp6_parser.cc"
    break;

  case 61:
#line 393 "dhcp6_parser.yy"
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.

    // Dhcp6 is required
    ctx.require("Dhcp6", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
}
#line 1017 "dhcp6_parser.cc"
    break;

  case 70:
#line 416 "dhcp6_parser.yy"
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Dhcp6", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP6);
}
#line 1030 "dhcp6_parser.cc"
    break;

  case 71:
#line 423 "dhcp6_parser.yy"
    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1040 "dhcp6_parser.cc"
    break;

  case 72:
#line 431 "dhcp6_parser.yy"
    {
    // Parse the Dhcp6 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1050 "dhcp6_parser.cc"
    break;

  case 73:
#line 435 "dhcp6_parser.yy"
    {
    // No global parameter is required
    // parsing completed
}
#line 1059 "dhcp6_parser.cc"
    break;

  case 115:
#line 487 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1067 "dhcp6_parser.cc"
    break;

  case 116:
#line 489 "dhcp6_parser.yy"
    {
    ElementPtr datadir(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data-directory", datadir);
    ctx.leave();
}
#line 1077 "dhcp6_parser.cc"
    break;

  case 117:
#line 495 "dhcp6_parser.yy"
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("preferred-lifetime", prf);
}
#line 1086 "dhcp6_parser.cc"
    break;

  case 118:
#line 500 "dhcp6_parser.yy"
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1095 "dhcp6_parser.cc"
    break;

  case 119:
#line 505 "dhcp6_parser.yy"
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1104 "dhcp6_parser.cc"
    break;

  case 120:
#line 510 "dhcp6_parser.yy"
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1113 "dhcp6_parser.cc"
    break;

  case 121:
#line 515 "dhcp6_parser.yy"
    {
    ElementPtr ctt(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("calculate-tee-times", ctt);
}
#line 1122 "dhcp6_parser.cc"
    break;

  case 122:
#line 520 "dhcp6_parser.yy"
    {
    ElementPtr t1(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t1-percent", t1);
}
#line 1131 "dhcp6_parser.cc"
    break;

  case 123:
#line 525 "dhcp6_parser.yy"
    {
    ElementPtr t2(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t2-percent", t2);
}
#line 1140 "dhcp6_parser.cc"
    break;

  case 124:
#line 530 "dhcp6_parser.yy"
    {
    ElementPtr dpp(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1149 "dhcp6_parser.cc"
    break;

  case 125:
#line 535 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1157 "dhcp6_parser.cc"
    break;

  case 126:
#line 537 "dhcp6_parser.yy"
    {
    ElementPtr stag(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-tag", stag);
    ctx.leave();
}
#line 1167 "dhcp6_parser.cc"
    break;

  case 127:
#line 543 "dhcp6_parser.yy"
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1178 "dhcp6_parser.cc"
    break;

  case 128:
#line 548 "dhcp6_parser.yy"
    {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1188 "dhcp6_parser.cc"
    break;

  case 129:
#line 554 "dhcp6_parser.yy"
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1198 "dhcp6_parser.cc"
    break;

  case 130:
#line 558 "dhcp6_parser.yy"
    {
    // No interfaces config param is required
    // parsing completed
}
#line 1207 "dhcp6_parser.cc"
    break;

  case 138:
#line 574 "dhcp6_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1218 "dhcp6_parser.cc"
    break;

  case 139:
#line 579 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1227 "dhcp6_parser.cc"
    break;

  case 140:
#line 584 "dhcp6_parser.yy"
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1236 "dhcp6_parser.cc"
    break;

  case 141:
#line 590 "dhcp6_parser.yy"
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1247 "dhcp6_parser.cc"
    break;

  case 142:
#line 595 "dhcp6_parser.yy"
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1258 "dhcp6_parser.cc"
    break;

  case 143:
#line 602 "dhcp6_parser.yy"
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1269 "dhcp6_parser.cc"
    break;

  case 144:
#line 607 "dhcp6_parser.yy"
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1280 "dhcp6_parser.cc"
    break;

  case 145:
#line 614 "dhcp6_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1291 "dhcp6_parser.cc"
    break;

  case 146:
#line 619 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1300 "dhcp6_parser.cc"
    break;

  case 151:
#line 632 "dhcp6_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1310 "dhcp6_parser.cc"
    break;

  case 152:
#line 636 "dhcp6_parser.yy"
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1320 "dhcp6_parser.cc"
    break;

  case 175:
#line 668 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1328 "dhcp6_parser.cc"
    break;

  case 176:
#line 670 "dhcp6_parser.yy"
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1337 "dhcp6_parser.cc"
    break;

  case 177:
#line 675 "dhcp6_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1343 "dhcp6_parser.cc"
    break;

  case 178:
#line 676 "dhcp6_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1349 "dhcp6_parser.cc"
    break;

  case 179:
#line 677 "dhcp6_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1355 "dhcp6_parser.cc"
    break;

  case 180:
#line 678 "dhcp6_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1361 "dhcp6_parser.cc"
    break;

  case 181:
#line 681 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1369 "dhcp6_parser.cc"
    break;

  case 182:
#line 683 "dhcp6_parser.yy"
    {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1379 "dhcp6_parser.cc"
    break;

  case 183:
#line 689 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1387 "dhcp6_parser.cc"
    break;

  case 184:
#line 691 "dhcp6_parser.yy"
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1397 "dhcp6_parser.cc"
    break;

  case 185:
#line 697 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1405 "dhcp6_parser.cc"
    break;

  case 186:
#line 699 "dhcp6_parser.yy"
    {
    ElementPtr h(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1415 "dhcp6_parser.cc"
    break;

  case 187:
#line 705 "dhcp6_parser.yy"
    {
    ElementPtr p(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1424 "dhcp6_parser.cc"
    break;

  case 188:
#line 710 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1432 "dhcp6_parser.cc"
    break;

  case 189:
#line 712 "dhcp6_parser.yy"
    {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1442 "dhcp6_parser.cc"
    break;

  case 190:
#line 718 "dhcp6_parser.yy"
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1451 "dhcp6_parser.cc"
    break;

  case 191:
#line 723 "dhcp6_parser.yy"
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1460 "dhcp6_parser.cc"
    break;

  case 192:
#line 728 "dhcp6_parser.yy"
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1469 "dhcp6_parser.cc"
    break;

  case 193:
#line 733 "dhcp6_parser.yy"
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1478 "dhcp6_parser.cc"
    break;

  case 194:
#line 738 "dhcp6_parser.yy"
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 1487 "dhcp6_parser.cc"
    break;

  case 195:
#line 743 "dhcp6_parser.yy"
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("request-timeout", n);
}
#line 1496 "dhcp6_parser.cc"
    break;

  case 196:
#line 748 "dhcp6_parser.yy"
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-keepalive", n);
}
#line 1505 "dhcp6_parser.cc"
    break;

  case 197:
#line 753 "dhcp6_parser.yy"
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-nodelay", n);
}
#line 1514 "dhcp6_parser.cc"
    break;

  case 198:
#line 758 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1522 "dhcp6_parser.cc"
    break;

  case 199:
#line 760 "dhcp6_parser.yy"
    {
    ElementPtr cp(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1532 "dhcp6_parser.cc"
    break;

  case 200:
#line 766 "dhcp6_parser.yy"
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 1541 "dhcp6_parser.cc"
    break;

  case 201:
#line 771 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1549 "dhcp6_parser.cc"
    break;

  case 202:
#line 773 "dhcp6_parser.yy"
    {
    ElementPtr ks(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 1559 "dhcp6_parser.cc"
    break;

  case 203:
#line 779 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1567 "dhcp6_parser.cc"
    break;

  case 204:
#line 781 "dhcp6_parser.yy"
    {
    ElementPtr c(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("consistency", c);
    ctx.leave();
}
#line 1577 "dhcp6_parser.cc"
    break;

  case 205:
#line 787 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1585 "dhcp6_parser.cc"
    break;

  case 206:
#line 789 "dhcp6_parser.yy"
    {
    ElementPtr c(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("serial-consistency", c);
    ctx.leave();
}
#line 1595 "dhcp6_parser.cc"
    break;

  case 207:
#line 795 "dhcp6_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sanity-checks", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SANITY_CHECKS);
}
#line 1606 "dhcp6_parser.cc"
    break;

  case 208:
#line 800 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1615 "dhcp6_parser.cc"
    break;

  case 212:
#line 810 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1623 "dhcp6_parser.cc"
    break;

  case 213:
#line 812 "dhcp6_parser.yy"
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
#line 1643 "dhcp6_parser.cc"
    break;

  case 214:
#line 828 "dhcp6_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("mac-sources", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.MAC_SOURCES);
}
#line 1654 "dhcp6_parser.cc"
    break;

  case 215:
#line 833 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1663 "dhcp6_parser.cc"
    break;

  case 220:
#line 846 "dhcp6_parser.yy"
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1672 "dhcp6_parser.cc"
    break;

  case 221:
#line 851 "dhcp6_parser.yy"
    {
    ElementPtr duid(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1681 "dhcp6_parser.cc"
    break;

  case 222:
#line 856 "dhcp6_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1692 "dhcp6_parser.cc"
    break;

  case 223:
#line 861 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1701 "dhcp6_parser.cc"
    break;

  case 229:
#line 875 "dhcp6_parser.yy"
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1710 "dhcp6_parser.cc"
    break;

  case 230:
#line 880 "dhcp6_parser.yy"
    {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 1719 "dhcp6_parser.cc"
    break;

  case 231:
#line 887 "dhcp6_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay-supplied-options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1730 "dhcp6_parser.cc"
    break;

  case 232:
#line 892 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1739 "dhcp6_parser.cc"
    break;

  case 233:
#line 897 "dhcp6_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1750 "dhcp6_parser.cc"
    break;

  case 234:
#line 902 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1759 "dhcp6_parser.cc"
    break;

  case 239:
#line 915 "dhcp6_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1769 "dhcp6_parser.cc"
    break;

  case 240:
#line 919 "dhcp6_parser.yy"
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1779 "dhcp6_parser.cc"
    break;

  case 241:
#line 925 "dhcp6_parser.yy"
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1789 "dhcp6_parser.cc"
    break;

  case 242:
#line 929 "dhcp6_parser.yy"
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1799 "dhcp6_parser.cc"
    break;

  case 248:
#line 944 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1807 "dhcp6_parser.cc"
    break;

  case 249:
#line 946 "dhcp6_parser.yy"
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1817 "dhcp6_parser.cc"
    break;

  case 250:
#line 952 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1825 "dhcp6_parser.cc"
    break;

  case 251:
#line 954 "dhcp6_parser.yy"
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1834 "dhcp6_parser.cc"
    break;

  case 252:
#line 960 "dhcp6_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 1845 "dhcp6_parser.cc"
    break;

  case 253:
#line 965 "dhcp6_parser.yy"
    {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1855 "dhcp6_parser.cc"
    break;

  case 262:
#line 983 "dhcp6_parser.yy"
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 1864 "dhcp6_parser.cc"
    break;

  case 263:
#line 988 "dhcp6_parser.yy"
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 1873 "dhcp6_parser.cc"
    break;

  case 264:
#line 993 "dhcp6_parser.yy"
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 1882 "dhcp6_parser.cc"
    break;

  case 265:
#line 998 "dhcp6_parser.yy"
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 1891 "dhcp6_parser.cc"
    break;

  case 266:
#line 1003 "dhcp6_parser.yy"
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 1900 "dhcp6_parser.cc"
    break;

  case 267:
#line 1008 "dhcp6_parser.yy"
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 1909 "dhcp6_parser.cc"
    break;

  case 268:
#line 1016 "dhcp6_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet6", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET6);
}
#line 1920 "dhcp6_parser.cc"
    break;

  case 269:
#line 1021 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1929 "dhcp6_parser.cc"
    break;

  case 274:
#line 1041 "dhcp6_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1939 "dhcp6_parser.cc"
    break;

  case 275:
#line 1045 "dhcp6_parser.yy"
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
#line 1965 "dhcp6_parser.cc"
    break;

  case 276:
#line 1067 "dhcp6_parser.yy"
    {
    // Parse the subnet6 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1975 "dhcp6_parser.cc"
    break;

  case 277:
#line 1071 "dhcp6_parser.yy"
    {
    // The subnet subnet6 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1985 "dhcp6_parser.cc"
    break;

  case 303:
#line 1108 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1993 "dhcp6_parser.cc"
    break;

  case 304:
#line 1110 "dhcp6_parser.yy"
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 2003 "dhcp6_parser.cc"
    break;

  case 305:
#line 1116 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2011 "dhcp6_parser.cc"
    break;

  case 306:
#line 1118 "dhcp6_parser.yy"
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 2021 "dhcp6_parser.cc"
    break;

  case 307:
#line 1124 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2029 "dhcp6_parser.cc"
    break;

  case 308:
#line 1126 "dhcp6_parser.yy"
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface-id", iface);
    ctx.leave();
}
#line 2039 "dhcp6_parser.cc"
    break;

  case 309:
#line 1132 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2047 "dhcp6_parser.cc"
    break;

  case 310:
#line 1134 "dhcp6_parser.yy"
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 2057 "dhcp6_parser.cc"
    break;

  case 311:
#line 1140 "dhcp6_parser.yy"
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2068 "dhcp6_parser.cc"
    break;

  case 312:
#line 1145 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2077 "dhcp6_parser.cc"
    break;

  case 313:
#line 1150 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 2085 "dhcp6_parser.cc"
    break;

  case 314:
#line 1152 "dhcp6_parser.yy"
    {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2094 "dhcp6_parser.cc"
    break;

  case 315:
#line 1157 "dhcp6_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 2100 "dhcp6_parser.cc"
    break;

  case 316:
#line 1158 "dhcp6_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 2106 "dhcp6_parser.cc"
    break;

  case 317:
#line 1159 "dhcp6_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("global", ctx.loc2pos(yystack_[0].location))); }
#line 2112 "dhcp6_parser.cc"
    break;

  case 318:
#line 1160 "dhcp6_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 2118 "dhcp6_parser.cc"
    break;

  case 319:
#line 1163 "dhcp6_parser.yy"
    {
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 2127 "dhcp6_parser.cc"
    break;

  case 320:
#line 1168 "dhcp6_parser.yy"
    {
    ElementPtr rc(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rapid-commit", rc);
}
#line 2136 "dhcp6_parser.cc"
    break;

  case 321:
#line 1176 "dhcp6_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 2147 "dhcp6_parser.cc"
    break;

  case 322:
#line 1181 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2156 "dhcp6_parser.cc"
    break;

  case 327:
#line 1196 "dhcp6_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2166 "dhcp6_parser.cc"
    break;

  case 328:
#line 1200 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
}
#line 2174 "dhcp6_parser.cc"
    break;

  case 351:
#line 1234 "dhcp6_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 2185 "dhcp6_parser.cc"
    break;

  case 352:
#line 1239 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2194 "dhcp6_parser.cc"
    break;

  case 353:
#line 1247 "dhcp6_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2203 "dhcp6_parser.cc"
    break;

  case 354:
#line 1250 "dhcp6_parser.yy"
    {
    // parsing completed
}
#line 2211 "dhcp6_parser.cc"
    break;

  case 359:
#line 1266 "dhcp6_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2221 "dhcp6_parser.cc"
    break;

  case 360:
#line 1270 "dhcp6_parser.yy"
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2233 "dhcp6_parser.cc"
    break;

  case 361:
#line 1281 "dhcp6_parser.yy"
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2243 "dhcp6_parser.cc"
    break;

  case 362:
#line 1285 "dhcp6_parser.yy"
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2255 "dhcp6_parser.cc"
    break;

  case 378:
#line 1317 "dhcp6_parser.yy"
    {
    ElementPtr code(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 2264 "dhcp6_parser.cc"
    break;

  case 380:
#line 1324 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2272 "dhcp6_parser.cc"
    break;

  case 381:
#line 1326 "dhcp6_parser.yy"
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 2282 "dhcp6_parser.cc"
    break;

  case 382:
#line 1332 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2290 "dhcp6_parser.cc"
    break;

  case 383:
#line 1334 "dhcp6_parser.yy"
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 2300 "dhcp6_parser.cc"
    break;

  case 384:
#line 1340 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2308 "dhcp6_parser.cc"
    break;

  case 385:
#line 1342 "dhcp6_parser.yy"
    {
    ElementPtr space(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 2318 "dhcp6_parser.cc"
    break;

  case 387:
#line 1350 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2326 "dhcp6_parser.cc"
    break;

  case 388:
#line 1352 "dhcp6_parser.yy"
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 2336 "dhcp6_parser.cc"
    break;

  case 389:
#line 1358 "dhcp6_parser.yy"
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 2345 "dhcp6_parser.cc"
    break;

  case 390:
#line 1367 "dhcp6_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 2356 "dhcp6_parser.cc"
    break;

  case 391:
#line 1372 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2365 "dhcp6_parser.cc"
    break;

  case 396:
#line 1391 "dhcp6_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2375 "dhcp6_parser.cc"
    break;

  case 397:
#line 1395 "dhcp6_parser.yy"
    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 2384 "dhcp6_parser.cc"
    break;

  case 398:
#line 1403 "dhcp6_parser.yy"
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2394 "dhcp6_parser.cc"
    break;

  case 399:
#line 1407 "dhcp6_parser.yy"
    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 2403 "dhcp6_parser.cc"
    break;

  case 414:
#line 1440 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2411 "dhcp6_parser.cc"
    break;

  case 415:
#line 1442 "dhcp6_parser.yy"
    {
    ElementPtr data(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2421 "dhcp6_parser.cc"
    break;

  case 418:
#line 1452 "dhcp6_parser.yy"
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2430 "dhcp6_parser.cc"
    break;

  case 419:
#line 1457 "dhcp6_parser.yy"
    {
    ElementPtr persist(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 2439 "dhcp6_parser.cc"
    break;

  case 420:
#line 1465 "dhcp6_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2450 "dhcp6_parser.cc"
    break;

  case 421:
#line 1470 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2459 "dhcp6_parser.cc"
    break;

  case 426:
#line 1485 "dhcp6_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2469 "dhcp6_parser.cc"
    break;

  case 427:
#line 1489 "dhcp6_parser.yy"
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2479 "dhcp6_parser.cc"
    break;

  case 428:
#line 1495 "dhcp6_parser.yy"
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2489 "dhcp6_parser.cc"
    break;

  case 429:
#line 1499 "dhcp6_parser.yy"
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
}
#line 2498 "dhcp6_parser.cc"
    break;

  case 439:
#line 1517 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2506 "dhcp6_parser.cc"
    break;

  case 440:
#line 1519 "dhcp6_parser.yy"
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2516 "dhcp6_parser.cc"
    break;

  case 441:
#line 1525 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2524 "dhcp6_parser.cc"
    break;

  case 442:
#line 1527 "dhcp6_parser.yy"
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
#line 2551 "dhcp6_parser.cc"
    break;

  case 443:
#line 1550 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2559 "dhcp6_parser.cc"
    break;

  case 444:
#line 1552 "dhcp6_parser.yy"
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
#line 2588 "dhcp6_parser.cc"
    break;

  case 445:
#line 1580 "dhcp6_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pd-pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.PD_POOLS);
}
#line 2599 "dhcp6_parser.cc"
    break;

  case 446:
#line 1585 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2608 "dhcp6_parser.cc"
    break;

  case 451:
#line 1600 "dhcp6_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2618 "dhcp6_parser.cc"
    break;

  case 452:
#line 1604 "dhcp6_parser.yy"
    {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2630 "dhcp6_parser.cc"
    break;

  case 453:
#line 1612 "dhcp6_parser.yy"
    {
    // Parse the pd-pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2640 "dhcp6_parser.cc"
    break;

  case 454:
#line 1616 "dhcp6_parser.yy"
    {
    // The prefix, prefix len and delegated len parameters are required.
    ctx.require("prefix", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("prefix-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("delegated-len", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2652 "dhcp6_parser.cc"
    break;

  case 468:
#line 1641 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2660 "dhcp6_parser.cc"
    break;

  case 469:
#line 1643 "dhcp6_parser.yy"
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix", prf);
    ctx.leave();
}
#line 2670 "dhcp6_parser.cc"
    break;

  case 470:
#line 1649 "dhcp6_parser.yy"
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefix-len", prf);
}
#line 2679 "dhcp6_parser.cc"
    break;

  case 471:
#line 1654 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2687 "dhcp6_parser.cc"
    break;

  case 472:
#line 1656 "dhcp6_parser.yy"
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix", prf);
    ctx.leave();
}
#line 2697 "dhcp6_parser.cc"
    break;

  case 473:
#line 1662 "dhcp6_parser.yy"
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("excluded-prefix-len", prf);
}
#line 2706 "dhcp6_parser.cc"
    break;

  case 474:
#line 1667 "dhcp6_parser.yy"
    {
    ElementPtr deleg(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("delegated-len", deleg);
}
#line 2715 "dhcp6_parser.cc"
    break;

  case 475:
#line 1675 "dhcp6_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 2726 "dhcp6_parser.cc"
    break;

  case 476:
#line 1680 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2735 "dhcp6_parser.cc"
    break;

  case 481:
#line 1693 "dhcp6_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2745 "dhcp6_parser.cc"
    break;

  case 482:
#line 1697 "dhcp6_parser.yy"
    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 2754 "dhcp6_parser.cc"
    break;

  case 483:
#line 1702 "dhcp6_parser.yy"
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2764 "dhcp6_parser.cc"
    break;

  case 484:
#line 1706 "dhcp6_parser.yy"
    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 2773 "dhcp6_parser.cc"
    break;

  case 500:
#line 1733 "dhcp6_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2784 "dhcp6_parser.cc"
    break;

  case 501:
#line 1738 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2793 "dhcp6_parser.cc"
    break;

  case 502:
#line 1743 "dhcp6_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("prefixes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2804 "dhcp6_parser.cc"
    break;

  case 503:
#line 1748 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2813 "dhcp6_parser.cc"
    break;

  case 504:
#line 1753 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2821 "dhcp6_parser.cc"
    break;

  case 505:
#line 1755 "dhcp6_parser.yy"
    {
    ElementPtr d(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2831 "dhcp6_parser.cc"
    break;

  case 506:
#line 1761 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2839 "dhcp6_parser.cc"
    break;

  case 507:
#line 1763 "dhcp6_parser.yy"
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2849 "dhcp6_parser.cc"
    break;

  case 508:
#line 1769 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2857 "dhcp6_parser.cc"
    break;

  case 509:
#line 1771 "dhcp6_parser.yy"
    {
    ElementPtr host(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2867 "dhcp6_parser.cc"
    break;

  case 510:
#line 1777 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2875 "dhcp6_parser.cc"
    break;

  case 511:
#line 1779 "dhcp6_parser.yy"
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 2885 "dhcp6_parser.cc"
    break;

  case 512:
#line 1785 "dhcp6_parser.yy"
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2896 "dhcp6_parser.cc"
    break;

  case 513:
#line 1790 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2905 "dhcp6_parser.cc"
    break;

  case 514:
#line 1798 "dhcp6_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2916 "dhcp6_parser.cc"
    break;

  case 515:
#line 1803 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2925 "dhcp6_parser.cc"
    break;

  case 518:
#line 1812 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2933 "dhcp6_parser.cc"
    break;

  case 519:
#line 1814 "dhcp6_parser.yy"
    {
    ElementPtr addr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 2943 "dhcp6_parser.cc"
    break;

  case 520:
#line 1823 "dhcp6_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2954 "dhcp6_parser.cc"
    break;

  case 521:
#line 1828 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2963 "dhcp6_parser.cc"
    break;

  case 524:
#line 1837 "dhcp6_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2973 "dhcp6_parser.cc"
    break;

  case 525:
#line 1841 "dhcp6_parser.yy"
    {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2983 "dhcp6_parser.cc"
    break;

  case 538:
#line 1866 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2991 "dhcp6_parser.cc"
    break;

  case 539:
#line 1868 "dhcp6_parser.yy"
    {
    ElementPtr test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 3001 "dhcp6_parser.cc"
    break;

  case 540:
#line 1874 "dhcp6_parser.yy"
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 3010 "dhcp6_parser.cc"
    break;

  case 541:
#line 1882 "dhcp6_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-id", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SERVER_ID);
}
#line 3021 "dhcp6_parser.cc"
    break;

  case 542:
#line 1887 "dhcp6_parser.yy"
    {
    // The type parameter is required.
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3032 "dhcp6_parser.cc"
    break;

  case 554:
#line 1909 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.DUID_TYPE);
}
#line 3040 "dhcp6_parser.cc"
    break;

  case 555:
#line 1911 "dhcp6_parser.yy"
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3049 "dhcp6_parser.cc"
    break;

  case 556:
#line 1916 "dhcp6_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("LLT", ctx.loc2pos(yystack_[0].location))); }
#line 3055 "dhcp6_parser.cc"
    break;

  case 557:
#line 1917 "dhcp6_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("EN", ctx.loc2pos(yystack_[0].location))); }
#line 3061 "dhcp6_parser.cc"
    break;

  case 558:
#line 1918 "dhcp6_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("LL", ctx.loc2pos(yystack_[0].location))); }
#line 3067 "dhcp6_parser.cc"
    break;

  case 559:
#line 1921 "dhcp6_parser.yy"
    {
    ElementPtr htype(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("htype", htype);
}
#line 3076 "dhcp6_parser.cc"
    break;

  case 560:
#line 1926 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3084 "dhcp6_parser.cc"
    break;

  case 561:
#line 1928 "dhcp6_parser.yy"
    {
    ElementPtr id(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("identifier", id);
    ctx.leave();
}
#line 3094 "dhcp6_parser.cc"
    break;

  case 562:
#line 1934 "dhcp6_parser.yy"
    {
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("time", time);
}
#line 3103 "dhcp6_parser.cc"
    break;

  case 563:
#line 1939 "dhcp6_parser.yy"
    {
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enterprise-id", time);
}
#line 3112 "dhcp6_parser.cc"
    break;

  case 564:
#line 1946 "dhcp6_parser.yy"
    {
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 3121 "dhcp6_parser.cc"
    break;

  case 565:
#line 1953 "dhcp6_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 3132 "dhcp6_parser.cc"
    break;

  case 566:
#line 1958 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3141 "dhcp6_parser.cc"
    break;

  case 574:
#line 1974 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3149 "dhcp6_parser.cc"
    break;

  case 575:
#line 1976 "dhcp6_parser.yy"
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 3159 "dhcp6_parser.cc"
    break;

  case 576:
#line 1982 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3167 "dhcp6_parser.cc"
    break;

  case 577:
#line 1984 "dhcp6_parser.yy"
    {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 3177 "dhcp6_parser.cc"
    break;

  case 578:
#line 1992 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3185 "dhcp6_parser.cc"
    break;

  case 579:
#line 1994 "dhcp6_parser.yy"
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

    // queue-enable is mandatory
    ConstElementPtr enable_queue = qc->get("enable-queue");
    if (enable_queue->getType() != Element::boolean) {
        std::stringstream msg;
        msg << "'enable-queue' must be boolean: ";
        msg  << "(" << qc->getPosition().str() << ")";
        error(yystack_[3].location, msg.str());
     }

    // if queue-type is supplied make sure it's a string
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
#line 3225 "dhcp6_parser.cc"
    break;

  case 580:
#line 2032 "dhcp6_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 3236 "dhcp6_parser.cc"
    break;

  case 581:
#line 2037 "dhcp6_parser.yy"
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3247 "dhcp6_parser.cc"
    break;

  case 582:
#line 2044 "dhcp6_parser.yy"
    {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3257 "dhcp6_parser.cc"
    break;

  case 583:
#line 2048 "dhcp6_parser.yy"
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3267 "dhcp6_parser.cc"
    break;

  case 604:
#line 2078 "dhcp6_parser.yy"
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 3276 "dhcp6_parser.cc"
    break;

  case 605:
#line 2083 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3284 "dhcp6_parser.cc"
    break;

  case 606:
#line 2085 "dhcp6_parser.yy"
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 3294 "dhcp6_parser.cc"
    break;

  case 607:
#line 2091 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3302 "dhcp6_parser.cc"
    break;

  case 608:
#line 2093 "dhcp6_parser.yy"
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 3312 "dhcp6_parser.cc"
    break;

  case 609:
#line 2099 "dhcp6_parser.yy"
    {
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 3321 "dhcp6_parser.cc"
    break;

  case 610:
#line 2104 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3329 "dhcp6_parser.cc"
    break;

  case 611:
#line 2106 "dhcp6_parser.yy"
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 3339 "dhcp6_parser.cc"
    break;

  case 612:
#line 2112 "dhcp6_parser.yy"
    {
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 3348 "dhcp6_parser.cc"
    break;

  case 613:
#line 2117 "dhcp6_parser.yy"
    {
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 3357 "dhcp6_parser.cc"
    break;

  case 614:
#line 2122 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 3365 "dhcp6_parser.cc"
    break;

  case 615:
#line 2124 "dhcp6_parser.yy"
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3374 "dhcp6_parser.cc"
    break;

  case 616:
#line 2130 "dhcp6_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 3380 "dhcp6_parser.cc"
    break;

  case 617:
#line 2131 "dhcp6_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 3386 "dhcp6_parser.cc"
    break;

  case 618:
#line 2134 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 3394 "dhcp6_parser.cc"
    break;

  case 619:
#line 2136 "dhcp6_parser.yy"
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 3404 "dhcp6_parser.cc"
    break;

  case 620:
#line 2142 "dhcp6_parser.yy"
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 3413 "dhcp6_parser.cc"
    break;

  case 621:
#line 2147 "dhcp6_parser.yy"
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 3422 "dhcp6_parser.cc"
    break;

  case 622:
#line 2152 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 3430 "dhcp6_parser.cc"
    break;

  case 623:
#line 2154 "dhcp6_parser.yy"
    {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3439 "dhcp6_parser.cc"
    break;

  case 624:
#line 2160 "dhcp6_parser.yy"
    {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 3447 "dhcp6_parser.cc"
    break;

  case 625:
#line 2163 "dhcp6_parser.yy"
    {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 3455 "dhcp6_parser.cc"
    break;

  case 626:
#line 2166 "dhcp6_parser.yy"
    {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 3463 "dhcp6_parser.cc"
    break;

  case 627:
#line 2169 "dhcp6_parser.yy"
    {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 3471 "dhcp6_parser.cc"
    break;

  case 628:
#line 2172 "dhcp6_parser.yy"
    {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 3480 "dhcp6_parser.cc"
    break;

  case 629:
#line 2178 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3488 "dhcp6_parser.cc"
    break;

  case 630:
#line 2180 "dhcp6_parser.yy"
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 3498 "dhcp6_parser.cc"
    break;

  case 631:
#line 2186 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3506 "dhcp6_parser.cc"
    break;

  case 632:
#line 2188 "dhcp6_parser.yy"
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 3516 "dhcp6_parser.cc"
    break;

  case 633:
#line 2194 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3524 "dhcp6_parser.cc"
    break;

  case 634:
#line 2196 "dhcp6_parser.yy"
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 3534 "dhcp6_parser.cc"
    break;

  case 635:
#line 2204 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3542 "dhcp6_parser.cc"
    break;

  case 636:
#line 2206 "dhcp6_parser.yy"
    {
    ctx.stack_.back()->set("Dhcp4", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3551 "dhcp6_parser.cc"
    break;

  case 637:
#line 2211 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3559 "dhcp6_parser.cc"
    break;

  case 638:
#line 2213 "dhcp6_parser.yy"
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3568 "dhcp6_parser.cc"
    break;

  case 639:
#line 2218 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3576 "dhcp6_parser.cc"
    break;

  case 640:
#line 2220 "dhcp6_parser.yy"
    {
    ctx.stack_.back()->set("Control-agent", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3585 "dhcp6_parser.cc"
    break;

  case 641:
#line 2227 "dhcp6_parser.yy"
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 3596 "dhcp6_parser.cc"
    break;

  case 642:
#line 2232 "dhcp6_parser.yy"
    {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3606 "dhcp6_parser.cc"
    break;

  case 643:
#line 2238 "dhcp6_parser.yy"
    {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3616 "dhcp6_parser.cc"
    break;

  case 644:
#line 2242 "dhcp6_parser.yy"
    {
    // No config_control params are required
    // parsing completed
}
#line 3625 "dhcp6_parser.cc"
    break;

  case 649:
#line 2257 "dhcp6_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 3636 "dhcp6_parser.cc"
    break;

  case 650:
#line 2262 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3645 "dhcp6_parser.cc"
    break;

  case 651:
#line 2267 "dhcp6_parser.yy"
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-fetch-wait-time", value);
}
#line 3654 "dhcp6_parser.cc"
    break;

  case 652:
#line 2277 "dhcp6_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 3665 "dhcp6_parser.cc"
    break;

  case 653:
#line 2282 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3674 "dhcp6_parser.cc"
    break;

  case 654:
#line 2287 "dhcp6_parser.yy"
    {
    // Parse the Logging map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3684 "dhcp6_parser.cc"
    break;

  case 655:
#line 2291 "dhcp6_parser.yy"
    {
    // parsing completed
}
#line 3692 "dhcp6_parser.cc"
    break;

  case 659:
#line 2307 "dhcp6_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 3703 "dhcp6_parser.cc"
    break;

  case 660:
#line 2312 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3712 "dhcp6_parser.cc"
    break;

  case 663:
#line 2324 "dhcp6_parser.yy"
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 3722 "dhcp6_parser.cc"
    break;

  case 664:
#line 2328 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
}
#line 3730 "dhcp6_parser.cc"
    break;

  case 674:
#line 2345 "dhcp6_parser.yy"
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 3739 "dhcp6_parser.cc"
    break;

  case 675:
#line 2350 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3747 "dhcp6_parser.cc"
    break;

  case 676:
#line 2352 "dhcp6_parser.yy"
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 3757 "dhcp6_parser.cc"
    break;

  case 677:
#line 2358 "dhcp6_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 3768 "dhcp6_parser.cc"
    break;

  case 678:
#line 2363 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3777 "dhcp6_parser.cc"
    break;

  case 681:
#line 2372 "dhcp6_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3787 "dhcp6_parser.cc"
    break;

  case 682:
#line 2376 "dhcp6_parser.yy"
    {
    ctx.stack_.pop_back();
}
#line 3795 "dhcp6_parser.cc"
    break;

  case 689:
#line 2390 "dhcp6_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3803 "dhcp6_parser.cc"
    break;

  case 690:
#line 2392 "dhcp6_parser.yy"
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 3813 "dhcp6_parser.cc"
    break;

  case 691:
#line 2398 "dhcp6_parser.yy"
    {
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 3822 "dhcp6_parser.cc"
    break;

  case 692:
#line 2403 "dhcp6_parser.yy"
    {
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 3831 "dhcp6_parser.cc"
    break;

  case 693:
#line 2408 "dhcp6_parser.yy"
    {
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 3840 "dhcp6_parser.cc"
    break;


#line 3844 "dhcp6_parser.cc"

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


  const short Dhcp6Parser::yypact_ninf_ = -855;

  const signed char Dhcp6Parser::yytable_ninf_ = -1;

  const short
  Dhcp6Parser::yypact_[] =
  {
     317,  -855,  -855,  -855,  -855,  -855,  -855,  -855,  -855,  -855,
    -855,  -855,  -855,  -855,  -855,  -855,    46,    70,    63,    65,
      71,   100,   169,   170,   201,   212,   217,   245,   270,   271,
     280,   298,  -855,  -855,  -855,  -855,  -855,  -855,  -855,  -855,
    -855,  -855,  -855,  -855,  -855,  -855,  -855,  -855,  -855,  -855,
    -855,  -855,  -855,  -855,  -855,  -855,  -855,  -855,  -855,  -855,
    -855,  -855,  -855,  -855,  -855,  -855,  -855,  -855,  -855,  -855,
    -855,  -855,    70,   -33,    32,    74,    27,   216,   249,   229,
     377,   149,    76,   398,   -10,   391,   105,   138,  -855,   252,
     303,   311,   305,   313,  -855,  -855,  -855,  -855,  -855,   321,
    -855,    37,  -855,  -855,  -855,  -855,  -855,  -855,  -855,  -855,
    -855,  -855,  -855,  -855,   322,   330,   331,   343,   347,   351,
     365,   367,  -855,  -855,  -855,  -855,  -855,  -855,  -855,  -855,
    -855,  -855,  -855,  -855,  -855,  -855,  -855,  -855,  -855,   368,
    -855,  -855,  -855,  -855,  -855,  -855,  -855,    73,  -855,  -855,
    -855,  -855,  -855,  -855,  -855,  -855,  -855,  -855,  -855,  -855,
    -855,  -855,  -855,  -855,  -855,  -855,  -855,  -855,  -855,  -855,
    -855,  -855,  -855,  -855,  -855,  -855,  -855,  -855,  -855,  -855,
    -855,  -855,  -855,  -855,  -855,  -855,  -855,  -855,   375,  -855,
     127,  -855,  -855,  -855,  -855,  -855,  -855,  -855,  -855,  -855,
    -855,   385,   397,  -855,  -855,  -855,  -855,  -855,  -855,  -855,
    -855,  -855,  -855,  -855,   133,  -855,  -855,  -855,  -855,  -855,
    -855,  -855,  -855,  -855,  -855,  -855,  -855,  -855,  -855,  -855,
    -855,  -855,  -855,  -855,  -855,  -855,   137,  -855,  -855,  -855,
    -855,  -855,   407,  -855,   428,   438,  -855,  -855,  -855,  -855,
    -855,  -855,   160,  -855,  -855,  -855,  -855,  -855,  -855,  -855,
    -855,  -855,  -855,  -855,  -855,  -855,  -855,  -855,  -855,  -855,
     346,   378,  -855,  -855,  -855,  -855,  -855,  -855,  -855,  -855,
     440,  -855,  -855,   442,  -855,  -855,  -855,   447,  -855,  -855,
     451,   457,  -855,  -855,  -855,  -855,  -855,  -855,  -855,  -855,
    -855,  -855,  -855,  -855,  -855,   461,   462,  -855,  -855,  -855,
    -855,   460,   466,  -855,  -855,  -855,  -855,  -855,  -855,  -855,
    -855,  -855,  -855,  -855,  -855,   171,  -855,  -855,  -855,   468,
    -855,  -855,   490,  -855,   491,   492,  -855,  -855,   493,   494,
    -855,  -855,  -855,  -855,  -855,   172,  -855,  -855,  -855,  -855,
    -855,  -855,  -855,  -855,  -855,  -855,  -855,  -855,  -855,  -855,
    -855,  -855,   181,  -855,  -855,  -855,   495,   182,  -855,  -855,
    -855,  -855,    70,    70,  -855,   323,   497,   498,   499,   500,
     501,  -855,    32,  -855,   502,   504,   507,   508,   509,   510,
     337,   339,   340,   356,   336,   354,   357,   360,   531,   537,
     538,   539,   544,   545,   546,   547,   548,   549,   551,   552,
     553,   554,   555,   556,   557,   384,   559,   562,   563,   567,
     570,   572,    74,  -855,   573,   399,    27,  -855,   574,   576,
     577,   578,   579,   406,   405,   582,   583,   584,   216,  -855,
     588,   249,  -855,   590,   418,   593,   420,   421,   229,  -855,
     596,   597,   598,   599,   600,   601,   602,  -855,   377,  -855,
     603,   604,   431,   606,   607,   608,   433,  -855,    76,   612,
     439,   441,  -855,   398,   614,   616,   -18,  -855,   443,   618,
     620,   448,   621,   449,   450,   625,   626,   452,   453,   630,
     631,   391,  -855,   105,  -855,   632,   459,   138,  -855,  -855,
    -855,   634,   633,   635,    70,    70,    70,  -855,   464,   636,
     637,   638,   639,   642,  -855,  -855,  -855,  -855,  -855,  -855,
    -855,  -855,   471,   644,   645,   647,   646,   477,    33,   650,
     651,   652,   653,   654,   655,   657,   658,   659,   660,  -855,
     661,   646,   662,   482,   487,   665,  -855,   666,  -855,  -855,
     667,   668,   488,   503,   505,  -855,  -855,   666,   506,   669,
    -855,   511,  -855,   512,  -855,   513,  -855,  -855,  -855,   666,
     666,   666,   514,   515,   516,   517,  -855,   518,   519,  -855,
     520,   521,   522,  -855,  -855,   523,  -855,  -855,  -855,   524,
      70,  -855,  -855,   525,   526,  -855,   527,  -855,  -855,    24,
     496,  -855,  -855,    26,   528,  -855,  -855,   670,  -855,  -855,
      70,    74,   105,  -855,  -855,  -855,  -855,   138,    27,   200,
     200,   671,  -855,   672,   674,   677,  -855,  -855,  -855,  -855,
    -855,  -855,  -855,  -855,   678,   -27,    70,   324,   585,   679,
     680,   699,   163,    36,    18,  -855,   391,  -855,  -855,   700,
    -855,  -855,   701,   702,  -855,  -855,  -855,  -855,  -855,   -44,
    -855,  -855,  -855,  -855,  -855,  -855,  -855,  -855,  -855,  -855,
    -855,  -855,  -855,  -855,  -855,  -855,  -855,  -855,  -855,  -855,
    -855,  -855,  -855,  -855,  -855,  -855,  -855,  -855,  -855,  -855,
    -855,  -855,   671,  -855,   191,   195,   202,   208,  -855,  -855,
    -855,  -855,   673,   706,   707,   708,   709,  -855,   710,   711,
    -855,  -855,  -855,   712,   713,   714,  -855,   276,  -855,  -855,
    -855,  -855,  -855,  -855,  -855,  -855,  -855,  -855,  -855,  -855,
    -855,  -855,  -855,  -855,  -855,  -855,  -855,  -855,   278,  -855,
     715,   716,  -855,  -855,   717,   719,  -855,  -855,   718,   722,
    -855,  -855,   720,   724,  -855,  -855,   723,   725,  -855,  -855,
    -855,   126,  -855,  -855,  -855,   726,  -855,  -855,  -855,   180,
    -855,  -855,  -855,  -855,   301,  -855,  -855,  -855,   214,  -855,
    -855,   727,   728,  -855,  -855,   729,   731,  -855,   732,   733,
     734,   735,   736,   737,   309,  -855,  -855,  -855,  -855,  -855,
    -855,  -855,  -855,  -855,   738,   739,   740,  -855,  -855,  -855,
    -855,   316,  -855,  -855,  -855,  -855,  -855,  -855,  -855,  -855,
    -855,  -855,  -855,   334,  -855,  -855,  -855,   338,  -855,   251,
    -855,   543,  -855,   741,   742,  -855,  -855,   743,   745,  -855,
    -855,  -855,   744,  -855,   747,  -855,  -855,  -855,  -855,   746,
     750,   751,   752,   568,   550,   580,   571,   581,   753,   586,
     587,   756,   757,   758,   589,   591,   592,   200,  -855,  -855,
     200,  -855,   671,   216,  -855,   672,    76,  -855,   674,   398,
    -855,   677,   284,  -855,   678,   -27,  -855,  -855,   324,  -855,
     759,   585,  -855,    10,   679,  -855,   377,  -855,   680,   -10,
    -855,   699,   595,   605,   609,   610,   611,   613,   163,  -855,
     762,   764,   615,   617,   619,    36,  -855,   766,   767,    18,
    -855,  -855,   355,   700,  -855,  -855,   768,   772,   249,  -855,
     701,   229,  -855,   702,   773,  -855,  -855,   221,   623,   624,
     627,  -855,  -855,  -855,  -855,  -855,   629,  -855,  -855,   640,
     641,   675,  -855,  -855,  -855,  -855,   341,  -855,   342,  -855,
     770,  -855,   771,  -855,  -855,  -855,  -855,  -855,  -855,  -855,
    -855,  -855,  -855,  -855,  -855,  -855,  -855,  -855,  -855,  -855,
     350,  -855,  -855,  -855,  -855,  -855,  -855,  -855,  -855,   686,
    -855,  -855,   776,  -855,  -855,  -855,  -855,  -855,   774,   778,
    -855,  -855,  -855,  -855,  -855,   777,  -855,   358,  -855,  -855,
    -855,  -855,  -855,  -855,  -855,  -855,   318,   697,  -855,  -855,
    -855,  -855,   703,   704,  -855,  -855,   780,  -855,  -855,  -855,
    -855,  -855,   362,  -855,  -855,  -855,  -855,  -855,  -855,   705,
     379,  -855,   388,  -855,   721,  -855,  -855,  -855,  -855,  -855,
    -855,  -855,  -855,  -855,  -855,  -855,  -855,  -855,  -855,  -855,
    -855,   284,  -855,  -855,   782,   648,  -855,    10,  -855,  -855,
    -855,  -855,  -855,  -855,  -855,  -855,  -855,   786,   643,   788,
     355,  -855,  -855,  -855,  -855,  -855,  -855,   730,  -855,  -855,
     789,  -855,   748,  -855,  -855,   769,  -855,  -855,   263,  -855,
     -52,   769,  -855,  -855,   792,   794,   803,   400,  -855,  -855,
    -855,  -855,  -855,  -855,   805,   749,   656,   754,   -52,  -855,
     760,  -855,  -855,  -855,  -855,  -855
  };

  const unsigned short
  Dhcp6Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,    28,    30,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     1,    47,    40,    36,    35,    32,    33,    34,
      39,     3,    37,    38,    60,     5,    72,     7,   129,     9,
     276,    11,   428,    13,   453,    15,   483,    17,   353,    19,
     361,    21,   398,    23,   241,    25,   582,    27,   654,    29,
     643,    31,    49,    43,     0,     0,     0,     0,     0,     0,
     485,     0,   363,   400,     0,     0,     0,     0,    51,     0,
      50,     0,     0,    44,    70,   652,   635,   637,   639,     0,
      69,     0,    62,    64,    66,    67,    68,    65,   115,   641,
     127,   141,   143,   145,     0,     0,     0,     0,     0,     0,
       0,     0,   125,   268,   351,   390,   441,   443,   313,   321,
     214,   231,   222,   207,   520,   475,   233,   252,   541,     0,
     565,   578,   580,   631,   633,   659,   114,     0,    74,    76,
      77,    78,    79,    80,   108,   109,   110,    81,   106,    84,
      85,    86,    87,   103,    88,    90,    89,    94,    95,    82,
     107,    83,    92,    93,   101,   102,   104,    91,    96,    97,
      98,    99,   100,   112,   113,   105,   111,   138,     0,   137,
       0,   131,   133,   134,   135,   136,   420,   445,   303,   305,
     307,     0,     0,   311,   309,   514,   302,   280,   281,   282,
     283,   299,   300,   301,     0,   278,   287,   288,   289,   292,
     293,   295,   290,   291,   284,   285,   297,   298,   286,   294,
     296,   439,   438,   434,   435,   433,     0,   430,   432,   436,
     437,   468,     0,   471,     0,     0,   467,   461,   462,   460,
     465,   466,     0,   455,   457,   458,   463,   464,   459,   512,
     500,   502,   504,   506,   508,   510,   499,   496,   497,   498,
       0,   486,   487,   491,   492,   489,   493,   494,   495,   490,
       0,   380,   188,     0,   384,   382,   387,     0,   376,   377,
       0,   364,   365,   367,   379,   368,   369,   370,   386,   371,
     372,   373,   374,   375,   414,     0,     0,   412,   413,   416,
     417,     0,   401,   402,   404,   405,   406,   407,   408,   409,
     410,   411,   248,   250,   245,     0,   243,   246,   247,     0,
     605,   607,     0,   610,     0,     0,   614,   618,     0,     0,
     622,   629,   603,   601,   602,     0,   584,   586,   587,   588,
     589,   590,   591,   592,   593,   594,   595,   596,   597,   598,
     599,   600,     0,   656,   658,   649,     0,     0,   645,   647,
     648,    48,     0,     0,    41,     0,     0,     0,     0,     0,
       0,    59,     0,    61,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    73,     0,     0,     0,   130,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   277,
       0,     0,   429,     0,     0,     0,     0,     0,     0,   454,
       0,     0,     0,     0,     0,     0,     0,   484,     0,   354,
       0,     0,     0,     0,     0,     0,     0,   362,     0,     0,
       0,     0,   399,     0,     0,     0,     0,   242,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   583,     0,   655,     0,     0,     0,   644,    52,
      45,     0,     0,     0,     0,     0,     0,    63,     0,     0,
       0,     0,     0,     0,   117,   118,   119,   120,   121,   122,
     123,   124,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   564,
       0,     0,     0,     0,     0,     0,    75,     0,   140,   132,
       0,     0,     0,     0,     0,   319,   320,     0,     0,     0,
     279,     0,   431,     0,   470,     0,   473,   474,   456,     0,
       0,     0,     0,     0,     0,     0,   488,     0,     0,   378,
       0,     0,     0,   389,   366,     0,   418,   419,   403,     0,
       0,   244,   604,     0,     0,   609,     0,   612,   613,     0,
       0,   620,   621,     0,     0,   585,   657,     0,   651,   646,
       0,     0,     0,   636,   638,   640,   116,     0,     0,     0,
       0,   147,   126,   270,   355,   392,    42,   442,   444,   315,
     316,   317,   318,   314,   323,     0,    49,     0,     0,     0,
     477,   235,     0,     0,     0,   579,     0,   632,   634,     0,
      53,   139,   422,   447,   304,   306,   308,   312,   310,     0,
     440,   469,   472,   513,   501,   503,   505,   507,   509,   511,
     381,   189,   385,   383,   388,   415,   249,   251,   606,   608,
     611,   616,   617,   615,   619,   624,   625,   626,   627,   628,
     623,   630,   147,    46,     0,     0,     0,     0,   175,   181,
     183,   185,     0,     0,     0,     0,     0,   198,     0,     0,
     201,   203,   205,     0,     0,     0,   174,     0,   153,   155,
     156,   157,   158,   159,   160,   161,   162,   163,   164,   167,
     168,   169,   170,   165,   166,   171,   172,   173,     0,   151,
       0,   148,   149,   274,     0,   271,   272,   359,     0,   356,
     357,   396,     0,   393,   394,   327,     0,   324,   325,   220,
     221,     0,   216,   218,   219,     0,   229,   230,   226,     0,
     224,   227,   228,   212,     0,   209,   211,   524,     0,   522,
     481,     0,   478,   479,   239,     0,   236,   237,     0,     0,
       0,     0,     0,     0,     0,   254,   256,   257,   258,   259,
     260,   261,   554,   560,     0,     0,     0,   553,   550,   551,
     552,     0,   543,   545,   548,   546,   547,   549,   574,   576,
     573,   571,   572,     0,   567,   569,   570,     0,   663,     0,
     661,    55,   426,     0,   423,   424,   451,     0,   448,   449,
     518,   517,     0,   516,     0,    71,   653,   642,   128,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   142,   144,
       0,   146,     0,     0,   269,     0,   363,   352,     0,   400,
     391,     0,     0,   322,     0,     0,   215,   232,     0,   223,
       0,     0,   208,   526,     0,   521,   485,   476,     0,     0,
     234,     0,     0,     0,     0,     0,     0,     0,     0,   253,
       0,     0,     0,     0,     0,     0,   542,     0,     0,     0,
     566,   581,     0,     0,   660,    57,     0,    56,     0,   421,
       0,     0,   446,     0,     0,   515,   650,     0,     0,     0,
       0,   187,   190,   191,   192,   193,     0,   200,   194,     0,
       0,     0,   195,   196,   197,   154,     0,   150,     0,   273,
       0,   358,     0,   395,   350,   342,   344,   335,   336,   347,
     348,   349,   331,   332,   333,   334,   340,   341,   339,   343,
       0,   329,   337,   345,   346,   338,   326,   217,   225,     0,
     210,   538,     0,   536,   537,   533,   534,   535,     0,   527,
     528,   530,   531,   532,   523,     0,   480,     0,   238,   262,
     263,   264,   265,   266,   267,   255,     0,     0,   559,   562,
     563,   544,     0,     0,   568,   677,     0,   675,   673,   667,
     671,   672,     0,   665,   669,   670,   668,   662,    54,     0,
       0,   425,     0,   450,     0,   177,   178,   179,   180,   176,
     182,   184,   186,   199,   202,   204,   206,   152,   275,   360,
     397,     0,   328,   213,     0,     0,   525,     0,   482,   240,
     556,   557,   558,   555,   561,   575,   577,     0,     0,     0,
       0,   664,    58,   427,   452,   519,   330,     0,   540,   529,
       0,   674,     0,   666,   539,     0,   676,   681,     0,   679,
       0,     0,   678,   689,     0,     0,     0,     0,   683,   685,
     686,   687,   688,   680,     0,     0,     0,     0,     0,   682,
       0,   691,   692,   693,   684,   690
  };

  const short
  Dhcp6Parser::yypgoto_[] =
  {
    -855,  -855,  -855,  -855,  -855,  -855,  -855,  -855,  -855,  -855,
    -855,  -855,  -855,  -855,  -855,  -855,  -855,    41,  -855,  -457,
    -855,   273,  -855,  -855,  -855,  -855,   194,  -855,  -459,  -855,
    -855,  -855,   -74,  -855,  -855,  -855,   434,  -855,  -855,  -855,
    -855,   220,   410,  -855,  -855,   -70,   -46,   -40,   -36,   -22,
     -17,   -14,  -855,  -855,  -855,  -855,  -855,  -855,  -855,   231,
     413,  -855,  -855,  -855,  -855,  -855,  -855,  -855,  -855,  -855,
     187,  -855,    11,  -855,  -602,    17,  -855,  -855,  -855,  -855,
    -855,  -855,  -855,  -855,  -855,  -855,   -21,  -855,  -630,  -855,
    -855,  -855,  -855,  -855,  -855,  -855,  -855,  -855,  -855,  -855,
    -855,  -855,  -855,  -855,  -855,  -855,  -855,  -855,    -4,  -855,
    -855,  -855,  -855,  -855,     4,  -621,  -855,  -855,  -855,  -855,
       0,  -855,  -855,  -855,  -855,  -855,  -855,  -855,  -855,    -9,
    -855,  -855,  -855,    -8,   419,  -855,  -855,  -855,  -855,  -855,
    -855,  -855,   -12,  -855,  -855,  -855,  -855,  -855,  -855,  -854,
    -855,  -855,  -855,    19,  -855,  -855,  -855,    30,   467,  -855,
    -855,  -849,  -855,  -847,  -855,   -11,  -855,    -5,  -855,     3,
    -855,  -855,  -855,  -846,  -855,  -855,  -855,  -855,    13,  -855,
    -855,  -161,   823,  -855,  -855,  -855,  -855,  -855,    28,  -855,
    -855,  -855,    34,  -855,   444,  -855,   -69,  -855,  -855,  -855,
    -855,  -855,   -66,  -855,  -855,  -855,  -855,  -855,   -58,  -855,
    -855,  -855,    35,  -855,  -855,  -855,    29,  -855,   436,  -855,
    -855,  -855,  -855,  -855,  -855,  -855,  -855,  -855,  -855,  -855,
     -19,  -855,  -855,  -855,   -15,   473,  -855,  -855,   -53,  -855,
     -29,  -855,  -855,  -855,  -855,  -855,    -6,  -855,  -855,  -855,
     -16,   470,  -855,  -855,  -855,  -855,  -855,  -855,  -855,   -62,
    -855,  -855,  -855,    21,  -855,  -855,  -855,    25,  -855,   472,
     265,  -855,  -855,  -855,  -855,  -855,  -855,  -855,  -855,  -855,
    -855,  -855,  -855,  -855,  -843,  -855,  -855,  -855,  -855,  -855,
    -855,  -855,    39,  -855,  -855,  -855,  -145,  -855,  -855,  -855,
    -855,  -855,  -855,  -855,    16,  -855,  -855,  -855,  -855,  -855,
    -855,  -855,  -855,  -855,  -855,  -855,  -855,     9,  -855,  -855,
    -855,  -855,  -855,  -855,  -855,  -855,  -855,  -855,   288,   445,
    -855,  -855,  -855,  -855,  -855,  -855,  -855,  -855,  -855,  -855,
    -855,  -855,  -855,  -855,  -855,  -855,  -855,  -855,  -855,  -855,
    -855,  -855,   -73,  -855,   -51,  -855,  -855,  -855,  -855,  -855,
    -855,  -855,  -855,  -855,  -855,  -855,   325,   446,  -855,  -855,
    -855,  -855,  -855,  -855,  -855,   326,   454,   -48,  -855,  -855,
      12,  -855,  -855,  -141,  -855,  -855,  -855,  -855,  -855,  -855,
    -160,  -855,  -855,  -178,  -855,  -855,  -855,  -855,  -855
  };

  const short
  Dhcp6Parser::yydefgoto_[] =
  {
      -1,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    88,    41,    42,
      73,   627,    92,    93,    43,    72,    89,    90,   651,   831,
     926,   927,   716,    45,    74,   101,   102,   103,   376,    47,
      75,   147,   148,   149,   384,   150,   151,   152,   153,   154,
     155,   156,   157,   158,   398,   159,   386,    49,    76,   190,
     191,   192,   424,   193,   160,   387,   161,   388,   162,   389,
     740,   741,   742,   870,   717,   718,   719,   849,  1049,   720,
     850,   721,   851,   722,   852,   723,   724,   461,   725,   726,
     727,   728,   729,   730,   731,   732,   733,   858,   734,   735,
     861,   736,   862,   737,   863,   163,   409,   774,   775,   776,
     890,   164,   406,   761,   762,   763,   764,   165,   408,   769,
     770,   771,   772,   166,   407,   167,   412,   785,   786,   787,
     899,    65,    84,   325,   326,   327,   474,   328,   475,   168,
     413,   794,   795,   796,   797,   798,   799,   800,   801,   169,
     399,   744,   745,   746,   873,    51,    77,   214,   215,   216,
     430,   217,   431,   218,   432,   219,   436,   220,   435,   170,
     404,   633,   222,   223,   171,   405,   756,   757,   758,   882,
     980,   981,   172,   400,    59,    81,   748,   749,   750,   876,
      61,    82,   290,   291,   292,   293,   294,   295,   296,   460,
     297,   464,   298,   463,   299,   300,   465,   301,   173,   401,
     752,   753,   754,   879,    63,    83,   311,   312,   313,   314,
     315,   469,   316,   317,   318,   319,   225,   428,   833,   834,
     835,   928,    53,    78,   236,   237,   238,   440,   174,   402,
     175,   403,   228,   429,   837,   838,   839,   931,    55,    79,
     252,   253,   254,   443,   255,   256,   445,   257,   258,   176,
     411,   781,   782,   783,   896,    57,    80,   270,   271,   272,
     273,   451,   274,   452,   275,   453,   276,   454,   277,   455,
     278,   456,   279,   450,   230,   437,   842,   843,   934,   177,
     410,   778,   779,   893,   998,   999,  1000,  1001,  1002,  1064,
    1003,   178,   414,   811,   812,   813,   910,  1073,   814,   815,
     911,   816,   817,   179,   180,   416,   823,   824,   825,   917,
     826,   918,   181,   417,   182,   418,    67,    85,   345,   346,
     347,   348,   479,   349,   480,   350,   351,   482,   352,   353,
     354,   485,   683,   355,   486,   356,   357,   358,   489,   690,
     359,   490,   183,   419,   184,   420,   104,   378,   105,   379,
     106,   380,   185,   385,    71,    87,   367,   368,   369,   495,
     370,   107,   377,    69,    86,   362,   363,   186,   421,   829,
     830,   922,  1032,  1033,  1034,  1035,  1079,  1036,  1077,  1098,
    1099,  1100,  1107,  1108,  1109,  1114,  1110,  1111,  1112
  };

  const unsigned short
  Dhcp6Parser::yytable_[] =
  {
     100,   146,   189,   206,   232,   246,   266,   207,   288,   307,
     324,   342,   360,   808,   309,   229,   768,   310,   738,   224,
     235,   249,   267,   194,   226,   239,   250,   268,   973,   302,
     320,   208,   343,   974,   361,   975,   979,   209,   364,   985,
     382,   210,    94,   187,   188,   383,    32,   195,   227,   240,
     251,   269,   260,   303,   321,   211,   344,   802,    40,   840,
     212,   289,   308,   213,   125,   282,   703,   233,   247,   626,
      44,   759,    46,   234,   248,    33,   422,    34,    48,    35,
     221,   423,   126,   127,   626,   108,   109,   322,   323,   110,
     126,   127,   111,   112,   113,   322,   323,   281,   657,   126,
     127,  1103,   991,   992,  1104,  1105,  1106,    50,   126,   127,
     663,   664,   665,   629,   630,   631,   632,   114,   115,   116,
     117,   118,   119,   120,   121,   122,   123,   124,   125,   885,
     426,   282,   886,   283,   284,   427,   438,   285,   286,   287,
     441,   439,   818,   819,    91,   442,   126,   127,   126,   127,
     760,   365,   366,   128,   803,   804,   805,   806,   129,   130,
     131,   132,   133,   448,   134,   681,   682,    99,   449,   135,
     685,   686,   687,   688,   476,   491,    52,    54,   136,   477,
     492,   137,    95,   888,   493,   497,   889,    99,   138,   494,
     498,    96,    97,    98,   422,    99,   139,   140,   493,   845,
     141,   142,   124,   846,    99,   497,   689,   973,    56,    99,
     847,   426,   974,    99,   975,   979,   848,   894,   985,    58,
     895,   698,   143,   144,    60,   145,   699,   700,   701,   702,
     703,   704,   705,   706,   707,   708,   709,   710,   711,   712,
     713,   714,   715,  1045,  1046,  1047,  1048,    36,    37,    38,
      39,    99,    62,    99,   923,   282,   145,   924,   371,   114,
     115,   116,   117,   118,   119,   120,  1101,   768,   956,  1102,
     125,   788,   789,   790,   791,   792,   793,    64,    66,   867,
     196,   867,   197,   125,   868,   808,   869,    68,   126,   127,
     198,   199,   200,   201,   202,   128,   241,   242,   243,   244,
     245,   126,   127,   125,   891,    70,   372,   203,   100,   892,
     204,   135,   908,   374,   231,   373,   375,   909,   205,   915,
     203,   126,   127,   204,   916,   381,   390,   114,   115,   116,
     117,   118,   119,   120,   391,   392,   123,   919,   125,   282,
     203,   491,   920,   204,   867,   438,   921,   393,   146,  1057,
    1058,   394,   189,  1061,   457,   395,   126,   127,  1062,   199,
     200,   476,   202,   128,   206,  1080,  1069,   232,   207,   396,
    1081,   397,   415,   194,   246,   203,   229,    99,   204,   425,
     224,   458,   441,   235,   266,   226,   205,  1083,   239,   433,
     249,   448,   208,    99,   288,   250,  1084,   195,   209,   307,
     267,   434,   210,  1118,   309,   268,    99,   310,  1119,   227,
     282,   444,   240,   499,   500,   302,   211,   342,   360,   251,
     320,   212,   759,   766,   213,   767,    99,   126,   127,   269,
     233,   125,   446,  1070,  1071,  1072,   234,   247,   343,   303,
     361,   221,   447,   248,   321,   364,   462,   289,   459,   126,
     127,   466,   308,   282,   304,   283,   284,   305,   306,   467,
     468,    99,   344,   126,   127,   470,   471,   259,   472,   473,
     126,   127,   478,   260,   261,   262,   263,   264,   265,     1,
       2,     3,     4,     5,     6,     7,     8,     9,    10,    11,
      12,    13,    14,    15,   481,   483,   484,   487,   488,   496,
     501,   502,   503,   504,   505,   506,   508,  1025,   509,  1026,
    1027,   510,   511,   512,   513,   514,   518,   515,   516,   329,
     330,   331,   332,   333,   334,   335,   336,   337,   338,   339,
     340,   341,    99,   519,   517,   522,   520,   146,   521,   143,
     144,   523,   524,   525,   189,   613,   614,   615,   526,   527,
     528,   529,   530,   531,    99,   532,   533,   534,   535,   536,
     537,   538,   539,   540,   364,   194,   541,   542,    99,   807,
     820,   543,   342,   360,   544,    99,   545,   547,   550,   548,
     551,   552,   553,   554,   555,   556,   557,   558,   559,   195,
     809,   821,   561,   343,   563,   361,   564,   565,   566,   567,
     569,   570,   571,   572,   573,   574,   575,   577,   578,   579,
     580,   581,   582,   583,   810,   822,   585,   344,   589,   586,
     590,   587,   593,   592,   594,   596,   595,   597,   598,   599,
     600,   677,   601,   602,   603,   604,   607,   608,   610,   684,
     611,   616,   612,   617,   618,   619,   620,   621,   622,   623,
     624,   693,   625,    34,   628,   634,   635,   636,   637,   647,
     639,   638,   640,   641,   648,   654,   642,   643,   644,   646,
     649,   650,   652,   653,   773,   692,   659,   853,   739,   743,
     655,   747,   656,   658,   751,   755,   777,   780,   660,   661,
     662,   666,   667,   668,   669,   670,   671,   672,   673,   674,
     675,   676,   678,   679,   680,   691,   784,   828,   832,   836,
     854,   855,   856,   857,   859,   860,   864,   865,   866,   872,
     925,   871,   875,   874,   877,   878,   880,   881,   884,   883,
     942,   898,   887,   897,   901,   900,   902,   903,   904,   905,
     906,   907,   912,   913,   914,   930,   941,   929,   933,   932,
     937,   944,   935,   936,   938,   939,   940,   946,   943,   945,
     949,   950,   951,   989,   947,   948,  1016,   952,  1017,   953,
    1022,  1023,   954,  1009,  1038,  1039,  1097,  1044,  1059,  1060,
    1065,  1067,  1066,  1010,  1078,  1068,  1087,  1011,  1012,  1013,
    1090,  1014,  1092,  1018,  1095,  1019,  1115,  1020,  1116,   206,
    1050,  1051,   288,   207,  1052,   307,  1053,  1117,   964,  1120,
     309,   229,   965,   310,   645,   224,   507,  1054,  1055,   993,
     226,  1091,   266,   302,   982,   324,   320,   208,  1088,   983,
     765,   694,   546,   209,  1122,   995,   966,   210,   267,   549,
     996,   807,   967,   268,   227,   820,   968,   303,  1028,   697,
     321,   211,  1056,   984,   232,   289,   212,   246,   308,   213,
     969,   972,   809,  1063,   997,   970,   821,   269,   971,  1030,
     235,   976,   994,   249,  1074,   239,   221,   977,   250,   844,
    1075,  1076,  1082,   957,   955,   978,   810,   990,   988,   987,
     822,  1007,  1008,  1031,   959,   591,  1015,   986,  1085,   240,
    1086,  1029,   251,   958,   280,   560,   961,  1094,   962,   588,
     960,  1041,   584,  1040,   562,  1042,   963,   233,   568,  1006,
     247,  1005,  1089,   234,   841,  1096,   248,  1043,  1024,  1121,
     576,  1021,  1123,  1004,   827,  1037,   605,  1125,   695,  1093,
    1124,  1113,   696,   609,     0,     0,     0,   606,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   964,     0,     0,
       0,   965,     0,   993,     0,     0,     0,     0,     0,     0,
       0,     0,     0,   982,     0,     0,  1028,     0,   983,   995,
       0,     0,     0,     0,   996,   966,     0,     0,     0,     0,
       0,   967,     0,     0,     0,   968,     0,  1030,     0,     0,
       0,     0,   984,     0,     0,     0,     0,     0,   997,   969,
     972,     0,     0,     0,   970,     0,   994,   971,     0,     0,
     976,  1031,     0,     0,     0,     0,   977,     0,     0,  1029,
       0,     0,     0,     0,   978
  };

  const short
  Dhcp6Parser::yycheck_[] =
  {
      74,    75,    76,    77,    78,    79,    80,    77,    82,    83,
      84,    85,    85,   643,    83,    77,   637,    83,   620,    77,
      78,    79,    80,    76,    77,    78,    79,    80,   882,    82,
      83,    77,    85,   882,    85,   882,   882,    77,    86,   882,
       3,    77,    10,    16,    17,     8,     0,    76,    77,    78,
      79,    80,    96,    82,    83,    77,    85,    21,    17,   103,
      77,    82,    83,    77,    54,    55,    30,    78,    79,   526,
       7,    98,     7,    78,    79,     5,     3,     7,     7,     9,
      77,     8,    72,    73,   541,    11,    12,   105,   106,    15,
      72,    73,    18,    19,    20,   105,   106,    21,   557,    72,
      73,   153,    92,    93,   156,   157,   158,     7,    72,    73,
     569,   570,   571,    80,    81,    82,    83,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,     3,
       3,    55,     6,    57,    58,     8,     3,    61,    62,    63,
       3,     8,   124,   125,   177,     8,    72,    73,    72,    73,
     177,    13,    14,    79,   118,   119,   120,   121,    84,    85,
      86,    87,    88,     3,    90,   141,   142,   177,     8,    95,
     144,   145,   146,   147,     3,     3,     7,     7,   104,     8,
       8,   107,   150,     3,     3,     3,     6,   177,   114,     8,
       8,   159,   160,   161,     3,   177,   122,   123,     3,     8,
     126,   127,    53,     8,   177,     3,   180,  1061,     7,   177,
       8,     3,  1061,   177,  1061,  1061,     8,     3,  1061,     7,
       6,    21,   148,   149,     7,   151,    26,    27,    28,    29,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    22,    23,    24,    25,   177,   178,   179,
     180,   177,     7,   177,     3,    55,   151,     6,     6,    43,
      44,    45,    46,    47,    48,    49,     3,   888,   870,     6,
      54,   108,   109,   110,   111,   112,   113,     7,     7,     3,
      64,     3,    66,    54,     8,   915,     8,     7,    72,    73,
      74,    75,    76,    77,    78,    79,    67,    68,    69,    70,
      71,    72,    73,    54,     3,     7,     3,    91,   382,     8,
      94,    95,     3,     8,    65,     4,     3,     8,   102,     3,
      91,    72,    73,    94,     8,     4,     4,    43,    44,    45,
      46,    47,    48,    49,     4,     4,    52,     3,    54,    55,
      91,     3,     8,    94,     3,     3,     8,     4,   422,     8,
       8,     4,   426,     3,     8,     4,    72,    73,     8,    75,
      76,     3,    78,    79,   438,     3,     8,   441,   438,     4,
       8,     4,     4,   426,   448,    91,   438,   177,    94,     4,
     438,     3,     3,   441,   458,   438,   102,     8,   441,     4,
     448,     3,   438,   177,   468,   448,     8,   426,   438,   473,
     458,     4,   438,     3,   473,   458,   177,   473,     8,   438,
      55,     4,   441,   372,   373,   468,   438,   491,   491,   448,
     473,   438,    98,    99,   438,   101,   177,    72,    73,   458,
     441,    54,     4,   115,   116,   117,   441,   448,   491,   468,
     491,   438,     4,   448,   473,   493,     4,   468,     8,    72,
      73,     4,   473,    55,    56,    57,    58,    59,    60,     8,
       3,   177,   491,    72,    73,     4,     4,    90,     8,     3,
      72,    73,     4,    96,    97,    98,    99,   100,   101,   162,
     163,   164,   165,   166,   167,   168,   169,   170,   171,   172,
     173,   174,   175,   176,     4,     4,     4,     4,     4,     4,
     177,     4,     4,     4,     4,     4,     4,   152,     4,   154,
     155,     4,     4,     4,     4,   178,   180,   178,   178,   128,
     129,   130,   131,   132,   133,   134,   135,   136,   137,   138,
     139,   140,   177,   179,   178,     4,   179,   611,   178,   148,
     149,     4,     4,     4,   618,   504,   505,   506,     4,     4,
       4,     4,     4,     4,   177,     4,     4,     4,     4,     4,
       4,     4,   178,     4,   612,   618,     4,     4,   177,   643,
     644,     4,   646,   646,     4,   177,     4,     4,     4,   180,
       4,     4,     4,     4,   178,   180,     4,     4,     4,   618,
     643,   644,     4,   646,     4,   646,   178,     4,   178,   178,
       4,     4,     4,     4,     4,     4,     4,     4,     4,   178,
       4,     4,     4,   180,   643,   644,     4,   646,     4,   180,
       4,   180,     4,   180,     4,     4,   178,   178,   178,     4,
       4,   590,   180,   180,     4,     4,     4,   178,     4,   143,
       7,   177,     7,     7,     7,     7,     7,     5,   177,     5,
       5,   610,     5,     7,   177,     5,     5,     5,     5,   177,
       5,     7,     5,     5,   177,   177,     7,     7,     7,     7,
       5,     5,     5,     5,    89,     5,     7,     4,     7,     7,
     177,     7,   177,   177,     7,     7,     7,     7,   177,   177,
     177,   177,   177,   177,   177,   177,   177,   177,   177,   177,
     177,   177,   177,   177,   177,   177,     7,     7,     7,     7,
       4,     4,     4,     4,     4,     4,     4,     4,     4,     3,
     177,     6,     3,     6,     6,     3,     6,     3,     3,     6,
     180,     3,     6,     6,     3,     6,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     3,   178,     6,     3,     6,
       4,   180,     8,     6,     4,     4,     4,     4,   178,   178,
       4,     4,     4,     4,   178,   178,     4,   178,     4,   178,
       4,     4,   180,   178,     6,     3,     7,     4,     8,     8,
       4,     3,     8,   178,     4,     8,     4,   178,   178,   178,
       4,   178,     4,   178,     5,   178,     4,   178,     4,   873,
     177,   177,   876,   873,   177,   879,   177,     4,   882,     4,
     879,   873,   882,   879,   541,   873,   382,   177,   177,   893,
     873,   178,   896,   876,   882,   899,   879,   873,   180,   882,
     636,   611,   422,   873,   178,   893,   882,   873,   896,   426,
     893,   915,   882,   896,   873,   919,   882,   876,   922,   618,
     879,   873,   177,   882,   928,   876,   873,   931,   879,   873,
     882,   882,   915,   177,   893,   882,   919,   896,   882,   922,
     928,   882,   893,   931,   177,   928,   873,   882,   931,   692,
     177,   177,   177,   872,   867,   882,   915,   891,   888,   885,
     919,   899,   901,   922,   875,   476,   908,   884,   177,   928,
    1061,   922,   931,   873,    81,   438,   878,   177,   879,   473,
     876,   930,   468,   928,   441,   931,   881,   928,   448,   898,
     931,   896,  1067,   928,   659,   177,   931,   933,   919,   180,
     458,   915,   178,   894,   646,   923,   491,   177,   612,  1080,
    1118,  1101,   617,   497,    -1,    -1,    -1,   493,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,  1061,    -1,    -1,
      -1,  1061,    -1,  1067,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,  1061,    -1,    -1,  1080,    -1,  1061,  1067,
      -1,    -1,    -1,    -1,  1067,  1061,    -1,    -1,    -1,    -1,
      -1,  1061,    -1,    -1,    -1,  1061,    -1,  1080,    -1,    -1,
      -1,    -1,  1061,    -1,    -1,    -1,    -1,    -1,  1067,  1061,
    1061,    -1,    -1,    -1,  1061,    -1,  1067,  1061,    -1,    -1,
    1061,  1080,    -1,    -1,    -1,    -1,  1061,    -1,    -1,  1080,
      -1,    -1,    -1,    -1,  1061
  };

  const unsigned short
  Dhcp6Parser::yystos_[] =
  {
       0,   162,   163,   164,   165,   166,   167,   168,   169,   170,
     171,   172,   173,   174,   175,   176,   182,   183,   184,   185,
     186,   187,   188,   189,   190,   191,   192,   193,   194,   195,
     196,   197,     0,     5,     7,     9,   177,   178,   179,   180,
     198,   199,   200,   205,     7,   214,     7,   220,     7,   238,
       7,   336,     7,   413,     7,   429,     7,   446,     7,   365,
       7,   371,     7,   395,     7,   312,     7,   507,     7,   554,
       7,   545,   206,   201,   215,   221,   239,   337,   414,   430,
     447,   366,   372,   396,   313,   508,   555,   546,   198,   207,
     208,   177,   203,   204,    10,   150,   159,   160,   161,   177,
     213,   216,   217,   218,   537,   539,   541,   552,    11,    12,
      15,    18,    19,    20,    43,    44,    45,    46,    47,    48,
      49,    50,    51,    52,    53,    54,    72,    73,    79,    84,
      85,    86,    87,    88,    90,    95,   104,   107,   114,   122,
     123,   126,   127,   148,   149,   151,   213,   222,   223,   224,
     226,   227,   228,   229,   230,   231,   232,   233,   234,   236,
     245,   247,   249,   286,   292,   298,   304,   306,   320,   330,
     350,   355,   363,   389,   419,   421,   440,   470,   482,   494,
     495,   503,   505,   533,   535,   543,   558,    16,    17,   213,
     240,   241,   242,   244,   419,   421,    64,    66,    74,    75,
      76,    77,    78,    91,    94,   102,   213,   226,   227,   228,
     229,   230,   231,   232,   338,   339,   340,   342,   344,   346,
     348,   350,   353,   354,   389,   407,   419,   421,   423,   440,
     465,    65,   213,   346,   348,   389,   415,   416,   417,   419,
     421,    67,    68,    69,    70,    71,   213,   346,   348,   389,
     419,   421,   431,   432,   433,   435,   436,   438,   439,    90,
      96,    97,    98,    99,   100,   101,   213,   389,   419,   421,
     448,   449,   450,   451,   453,   455,   457,   459,   461,   463,
     363,    21,    55,    57,    58,    61,    62,    63,   213,   267,
     373,   374,   375,   376,   377,   378,   379,   381,   383,   385,
     386,   388,   419,   421,    56,    59,    60,   213,   267,   377,
     383,   397,   398,   399,   400,   401,   403,   404,   405,   406,
     419,   421,   105,   106,   213,   314,   315,   316,   318,   128,
     129,   130,   131,   132,   133,   134,   135,   136,   137,   138,
     139,   140,   213,   419,   421,   509,   510,   511,   512,   514,
     516,   517,   519,   520,   521,   524,   526,   527,   528,   531,
     533,   535,   556,   557,   558,    13,    14,   547,   548,   549,
     551,     6,     3,     4,     8,     3,   219,   553,   538,   540,
     542,     4,     3,     8,   225,   544,   237,   246,   248,   250,
       4,     4,     4,     4,     4,     4,     4,     4,   235,   331,
     364,   390,   420,   422,   351,   356,   293,   305,   299,   287,
     471,   441,   307,   321,   483,     4,   496,   504,   506,   534,
     536,   559,     3,     8,   243,     4,     3,     8,   408,   424,
     341,   343,   345,     4,     4,   349,   347,   466,     3,     8,
     418,     3,     8,   434,     4,   437,     4,     4,     3,     8,
     464,   452,   454,   456,   458,   460,   462,     8,     3,     8,
     380,   268,     4,   384,   382,   387,     4,     8,     3,   402,
       4,     4,     8,     3,   317,   319,     3,     8,     4,   513,
     515,     4,   518,     4,     4,   522,   525,     4,     4,   529,
     532,     3,     8,     3,     8,   550,     4,     3,     8,   198,
     198,   177,     4,     4,     4,     4,     4,   217,     4,     4,
       4,     4,     4,     4,   178,   178,   178,   178,   180,   179,
     179,   178,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,   178,
       4,     4,     4,     4,     4,     4,   223,     4,   180,   241,
       4,     4,     4,     4,     4,   178,   180,     4,     4,     4,
     339,     4,   416,     4,   178,     4,   178,   178,   432,     4,
       4,     4,     4,     4,     4,     4,   450,     4,     4,   178,
       4,     4,     4,   180,   375,     4,   180,   180,   399,     4,
       4,   315,   180,     4,     4,   178,     4,   178,   178,     4,
       4,   180,   180,     4,     4,   510,   557,     4,   178,   548,
       4,     7,     7,   198,   198,   198,   177,     7,     7,     7,
       7,     5,   177,     5,     5,     5,   200,   202,   177,    80,
      81,    82,    83,   352,     5,     5,     5,     5,     7,     5,
       5,     5,     7,     7,     7,   202,     7,   177,   177,     5,
       5,   209,     5,     5,   177,   177,   177,   209,   177,     7,
     177,   177,   177,   209,   209,   209,   177,   177,   177,   177,
     177,   177,   177,   177,   177,   177,   177,   198,   177,   177,
     177,   141,   142,   523,   143,   144,   145,   146,   147,   180,
     530,   177,     5,   198,   222,   556,   547,   240,    21,    26,
      27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
      37,    38,    39,    40,    41,    42,   213,   255,   256,   257,
     260,   262,   264,   266,   267,   269,   270,   271,   272,   273,
     274,   275,   276,   277,   279,   280,   282,   284,   255,     7,
     251,   252,   253,     7,   332,   333,   334,     7,   367,   368,
     369,     7,   391,   392,   393,     7,   357,   358,   359,    98,
     177,   294,   295,   296,   297,   207,    99,   101,   296,   300,
     301,   302,   303,    89,   288,   289,   290,     7,   472,   473,
       7,   442,   443,   444,     7,   308,   309,   310,   108,   109,
     110,   111,   112,   113,   322,   323,   324,   325,   326,   327,
     328,   329,    21,   118,   119,   120,   121,   213,   269,   419,
     421,   484,   485,   486,   489,   490,   492,   493,   124,   125,
     213,   419,   421,   497,   498,   499,   501,   509,     7,   560,
     561,   210,     7,   409,   410,   411,     7,   425,   426,   427,
     103,   451,   467,   468,   251,     8,     8,     8,     8,   258,
     261,   263,   265,     4,     4,     4,     4,     4,   278,     4,
       4,   281,   283,   285,     4,     4,     4,     3,     8,     8,
     254,     6,     3,   335,     6,     3,   370,     6,     3,   394,
       6,     3,   360,     6,     3,     3,     6,     6,     3,     6,
     291,     3,     8,   474,     3,     6,   445,     6,     3,   311,
       6,     3,     4,     4,     4,     4,     4,     4,     3,     8,
     487,   491,     4,     4,     4,     3,     8,   500,   502,     3,
       8,     8,   562,     3,     6,   177,   211,   212,   412,     6,
       3,   428,     6,     3,   469,     8,     6,     4,     4,     4,
       4,   178,   180,   178,   180,   178,     4,   178,   178,     4,
       4,     4,   178,   178,   180,   256,   255,   253,   338,   334,
     373,   369,   397,   393,   213,   226,   227,   228,   229,   230,
     231,   232,   267,   330,   342,   344,   346,   348,   350,   354,
     361,   362,   389,   419,   421,   465,   359,   295,   301,     4,
     289,    92,    93,   213,   267,   389,   419,   421,   475,   476,
     477,   478,   479,   481,   473,   448,   444,   314,   310,   178,
     178,   178,   178,   178,   178,   323,     4,     4,   178,   178,
     178,   485,     4,     4,   498,   152,   154,   155,   213,   267,
     419,   421,   563,   564,   565,   566,   568,   561,     6,     3,
     415,   411,   431,   427,     4,    22,    23,    24,    25,   259,
     177,   177,   177,   177,   177,   177,   177,     8,     8,     8,
       8,     3,     8,   177,   480,     4,     8,     3,     8,     8,
     115,   116,   117,   488,   177,   177,   177,   569,     4,   567,
       3,     8,   177,     8,     8,   177,   362,     4,   180,   477,
       4,   178,     4,   564,   177,     5,   177,     7,   570,   571,
     572,     3,     6,   153,   156,   157,   158,   573,   574,   575,
     577,   578,   579,   571,   576,     4,     4,     4,     3,     8,
       4,   180,   178,   178,   574,   177
  };

  const unsigned short
  Dhcp6Parser::yyr1_[] =
  {
       0,   181,   183,   182,   184,   182,   185,   182,   186,   182,
     187,   182,   188,   182,   189,   182,   190,   182,   191,   182,
     192,   182,   193,   182,   194,   182,   195,   182,   196,   182,
     197,   182,   198,   198,   198,   198,   198,   198,   198,   199,
     201,   200,   202,   203,   203,   204,   204,   206,   205,   207,
     207,   208,   208,   210,   209,   211,   211,   212,   212,   213,
     215,   214,   216,   216,   217,   217,   217,   217,   217,   217,
     219,   218,   221,   220,   222,   222,   223,   223,   223,   223,
     223,   223,   223,   223,   223,   223,   223,   223,   223,   223,
     223,   223,   223,   223,   223,   223,   223,   223,   223,   223,
     223,   223,   223,   223,   223,   223,   223,   223,   223,   223,
     223,   223,   223,   223,   223,   225,   224,   226,   227,   228,
     229,   230,   231,   232,   233,   235,   234,   237,   236,   239,
     238,   240,   240,   241,   241,   241,   241,   241,   243,   242,
     244,   246,   245,   248,   247,   250,   249,   251,   251,   252,
     252,   254,   253,   255,   255,   256,   256,   256,   256,   256,
     256,   256,   256,   256,   256,   256,   256,   256,   256,   256,
     256,   256,   256,   256,   256,   258,   257,   259,   259,   259,
     259,   261,   260,   263,   262,   265,   264,   266,   268,   267,
     269,   270,   271,   272,   273,   274,   275,   276,   278,   277,
     279,   281,   280,   283,   282,   285,   284,   287,   286,   288,
     288,   289,   291,   290,   293,   292,   294,   294,   295,   295,
     296,   297,   299,   298,   300,   300,   301,   301,   301,   302,
     303,   305,   304,   307,   306,   308,   308,   309,   309,   311,
     310,   313,   312,   314,   314,   314,   315,   315,   317,   316,
     319,   318,   321,   320,   322,   322,   323,   323,   323,   323,
     323,   323,   324,   325,   326,   327,   328,   329,   331,   330,
     332,   332,   333,   333,   335,   334,   337,   336,   338,   338,
     339,   339,   339,   339,   339,   339,   339,   339,   339,   339,
     339,   339,   339,   339,   339,   339,   339,   339,   339,   339,
     339,   339,   339,   341,   340,   343,   342,   345,   344,   347,
     346,   349,   348,   351,   350,   352,   352,   352,   352,   353,
     354,   356,   355,   357,   357,   358,   358,   360,   359,   361,
     361,   362,   362,   362,   362,   362,   362,   362,   362,   362,
     362,   362,   362,   362,   362,   362,   362,   362,   362,   362,
     362,   364,   363,   366,   365,   367,   367,   368,   368,   370,
     369,   372,   371,   373,   373,   374,   374,   375,   375,   375,
     375,   375,   375,   375,   375,   375,   375,   376,   377,   378,
     380,   379,   382,   381,   384,   383,   385,   387,   386,   388,
     390,   389,   391,   391,   392,   392,   394,   393,   396,   395,
     397,   397,   398,   398,   399,   399,   399,   399,   399,   399,
     399,   399,   399,   400,   402,   401,   403,   404,   405,   406,
     408,   407,   409,   409,   410,   410,   412,   411,   414,   413,
     415,   415,   416,   416,   416,   416,   416,   416,   416,   418,
     417,   420,   419,   422,   421,   424,   423,   425,   425,   426,
     426,   428,   427,   430,   429,   431,   431,   432,   432,   432,
     432,   432,   432,   432,   432,   432,   432,   432,   434,   433,
     435,   437,   436,   438,   439,   441,   440,   442,   442,   443,
     443,   445,   444,   447,   446,   448,   448,   449,   449,   450,
     450,   450,   450,   450,   450,   450,   450,   450,   450,   450,
     452,   451,   454,   453,   456,   455,   458,   457,   460,   459,
     462,   461,   464,   463,   466,   465,   467,   467,   469,   468,
     471,   470,   472,   472,   474,   473,   475,   475,   476,   476,
     477,   477,   477,   477,   477,   477,   477,   478,   480,   479,
     481,   483,   482,   484,   484,   485,   485,   485,   485,   485,
     485,   485,   485,   485,   487,   486,   488,   488,   488,   489,
     491,   490,   492,   493,   494,   496,   495,   497,   497,   498,
     498,   498,   498,   498,   500,   499,   502,   501,   504,   503,
     506,   505,   508,   507,   509,   509,   510,   510,   510,   510,
     510,   510,   510,   510,   510,   510,   510,   510,   510,   510,
     510,   510,   510,   510,   511,   513,   512,   515,   514,   516,
     518,   517,   519,   520,   522,   521,   523,   523,   525,   524,
     526,   527,   529,   528,   530,   530,   530,   530,   530,   532,
     531,   534,   533,   536,   535,   538,   537,   540,   539,   542,
     541,   544,   543,   546,   545,   547,   547,   548,   548,   550,
     549,   551,   553,   552,   555,   554,   556,   556,   557,   559,
     558,   560,   560,   562,   561,   563,   563,   564,   564,   564,
     564,   564,   564,   564,   565,   567,   566,   569,   568,   570,
     570,   572,   571,   573,   573,   574,   574,   574,   574,   576,
     575,   577,   578,   579
  };

  const unsigned char
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
       1,     1,     1,     1,     1,     0,     4,     3,     3,     3,
       3,     3,     3,     3,     3,     0,     4,     0,     6,     0,
       4,     1,     3,     1,     1,     1,     1,     1,     0,     4,
       3,     0,     6,     0,     6,     0,     6,     0,     1,     1,
       3,     0,     4,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     1,     1,     1,
       1,     0,     4,     0,     4,     0,     4,     3,     0,     4,
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
       1,     1,     1,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     1,     1,     1,     1,     3,
       3,     0,     6,     0,     1,     1,     3,     0,     4,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     6,     0,     4,     0,     1,     1,     3,     0,
       4,     0,     4,     0,     1,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     3,     1,
       0,     4,     0,     4,     0,     4,     1,     0,     4,     3,
       0,     6,     0,     1,     1,     3,     0,     4,     0,     4,
       0,     1,     1,     3,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     1,     1,     3,     3,
       0,     6,     0,     1,     1,     3,     0,     4,     0,     4,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     0,     4,     0,     4,     0,     6,     0,     1,     1,
       3,     0,     4,     0,     4,     1,     3,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       3,     0,     4,     3,     3,     0,     6,     0,     1,     1,
       3,     0,     4,     0,     4,     0,     1,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     4,     0,     4,     0,     4,     0,     4,     0,     4,
       0,     4,     0,     4,     0,     6,     1,     1,     0,     4,
       0,     6,     1,     3,     0,     4,     0,     1,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       3,     0,     6,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     0,     4,     1,     1,     1,     3,
       0,     4,     3,     3,     3,     0,     6,     1,     3,     1,
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
       3,     0,     4,     1,     3,     1,     1,     1,     1,     0,
       4,     3,     3,     3
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
  "\"tcp-nodelay\"", "\"preferred-lifetime\"", "\"valid-lifetime\"",
  "\"renew-timer\"", "\"rebind-timer\"", "\"calculate-tee-times\"",
  "\"t1-percent\"", "\"t2-percent\"", "\"decline-probation-period\"",
  "\"server-tag\"", "\"subnet6\"", "\"option-def\"", "\"option-data\"",
  "\"name\"", "\"data\"", "\"code\"", "\"space\"", "\"csv-format\"",
  "\"always-send\"", "\"record-types\"", "\"encapsulate\"", "\"array\"",
  "\"pools\"", "\"pool\"", "\"pd-pools\"", "\"prefix\"", "\"prefix-len\"",
  "\"excluded-prefix\"", "\"excluded-prefix-len\"", "\"delegated-len\"",
  "\"user-context\"", "\"comment\"", "\"subnet\"", "\"interface\"",
  "\"interface-id\"", "\"id\"", "\"rapid-commit\"", "\"reservation-mode\"",
  "\"disabled\"", "\"out-of-pool\"", "\"global\"", "\"all\"",
  "\"shared-networks\"", "\"mac-sources\"", "\"relay-supplied-options\"",
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
  "\"socket-name\"", "\"dhcp-queue-control\"", "\"dhcp-ddns\"",
  "\"enable-updates\"", "\"qualifying-suffix\"", "\"server-ip\"",
  "\"server-port\"", "\"sender-ip\"", "\"sender-port\"",
  "\"max-queue-size\"", "\"ncr-protocol\"", "\"ncr-format\"",
  "\"override-no-update\"", "\"override-client-update\"",
  "\"replace-client-name\"", "\"generated-prefix\"", "\"UDP\"", "\"TCP\"",
  "\"JSON\"", "\"when-present\"", "\"never\"", "\"always\"",
  "\"when-not-present\"", "\"hostname-char-set\"",
  "\"hostname-char-replacement\"", "\"Logging\"", "\"loggers\"",
  "\"output_options\"", "\"output\"", "\"debuglevel\"", "\"severity\"",
  "\"flush\"", "\"maxsize\"", "\"maxver\"", "\"Dhcp4\"", "\"DhcpDdns\"",
  "\"Control-agent\"", "TOPLEVEL_JSON", "TOPLEVEL_DHCP6", "SUB_DHCP6",
  "SUB_INTERFACES6", "SUB_SUBNET6", "SUB_POOL6", "SUB_PD_POOL",
  "SUB_RESERVATION", "SUB_OPTION_DEFS", "SUB_OPTION_DEF",
  "SUB_OPTION_DATA", "SUB_HOOKS_LIBRARY", "SUB_DHCP_DDNS", "SUB_LOGGING",
  "SUB_CONFIG_CONTROL", "\"constant string\"", "\"integer\"",
  "\"floating point\"", "\"boolean\"", "$accept", "start", "$@1", "$@2",
  "$@3", "$@4", "$@5", "$@6", "$@7", "$@8", "$@9", "$@10", "$@11", "$@12",
  "$@13", "$@14", "$@15", "value", "sub_json", "map2", "$@16", "map_value",
  "map_content", "not_empty_map", "list_generic", "$@17", "list_content",
  "not_empty_list", "list_strings", "$@18", "list_strings_content",
  "not_empty_list_strings", "unknown_map_entry", "syntax_map", "$@19",
  "global_objects", "global_object", "dhcp6_object", "$@20", "sub_dhcp6",
  "$@21", "global_params", "global_param", "data_directory", "$@22",
  "preferred_lifetime", "valid_lifetime", "renew_timer", "rebind_timer",
  "calculate_tee_times", "t1_percent", "t2_percent",
  "decline_probation_period", "server_tag", "$@23", "interfaces_config",
  "$@24", "sub_interfaces6", "$@25", "interfaces_config_params",
  "interfaces_config_param", "interfaces_list", "$@26", "re_detect",
  "lease_database", "$@27", "hosts_database", "$@28", "hosts_databases",
  "$@29", "database_list", "not_empty_database_list", "database", "$@30",
  "database_map_params", "database_map_param", "database_type", "$@31",
  "db_type", "user", "$@32", "password", "$@33", "host", "$@34", "port",
  "name", "$@35", "persist", "lfc_interval", "readonly", "connect_timeout",
  "reconnect_wait_time", "request_timeout", "tcp_keepalive", "tcp_nodelay",
  "contact_points", "$@36", "max_reconnect_tries", "keyspace", "$@37",
  "consistency", "$@38", "serial_consistency", "$@39", "sanity_checks",
  "$@40", "sanity_checks_params", "sanity_checks_param", "lease_checks",
  "$@41", "mac_sources", "$@42", "mac_sources_list", "mac_sources_value",
  "duid_id", "string_id", "host_reservation_identifiers", "$@43",
  "host_reservation_identifiers_list", "host_reservation_identifier",
  "hw_address_id", "flex_id", "relay_supplied_options", "$@44",
  "hooks_libraries", "$@45", "hooks_libraries_list",
  "not_empty_hooks_libraries_list", "hooks_library", "$@46",
  "sub_hooks_library", "$@47", "hooks_params", "hooks_param", "library",
  "$@48", "parameters", "$@49", "expired_leases_processing", "$@50",
  "expired_leases_params", "expired_leases_param",
  "reclaim_timer_wait_time", "flush_reclaimed_timer_wait_time",
  "hold_reclaimed_time", "max_reclaim_leases", "max_reclaim_time",
  "unwarned_reclaim_cycles", "subnet6_list", "$@51",
  "subnet6_list_content", "not_empty_subnet6_list", "subnet6", "$@52",
  "sub_subnet6", "$@53", "subnet6_params", "subnet6_param", "subnet",
  "$@54", "interface", "$@55", "interface_id", "$@56", "client_class",
  "$@57", "require_client_classes", "$@58", "reservation_mode", "$@59",
  "hr_mode", "id", "rapid_commit", "shared_networks", "$@60",
  "shared_networks_content", "shared_networks_list", "shared_network",
  "$@61", "shared_network_params", "shared_network_param",
  "option_def_list", "$@62", "sub_option_def_list", "$@63",
  "option_def_list_content", "not_empty_option_def_list",
  "option_def_entry", "$@64", "sub_option_def", "$@65",
  "option_def_params", "not_empty_option_def_params", "option_def_param",
  "option_def_name", "code", "option_def_code", "option_def_type", "$@66",
  "option_def_record_types", "$@67", "space", "$@68", "option_def_space",
  "option_def_encapsulate", "$@69", "option_def_array", "option_data_list",
  "$@70", "option_data_list_content", "not_empty_option_data_list",
  "option_data_entry", "$@71", "sub_option_data", "$@72",
  "option_data_params", "not_empty_option_data_params",
  "option_data_param", "option_data_name", "option_data_data", "$@73",
  "option_data_code", "option_data_space", "option_data_csv_format",
  "option_data_always_send", "pools_list", "$@74", "pools_list_content",
  "not_empty_pools_list", "pool_list_entry", "$@75", "sub_pool6", "$@76",
  "pool_params", "pool_param", "pool_entry", "$@77", "user_context",
  "$@78", "comment", "$@79", "pd_pools_list", "$@80",
  "pd_pools_list_content", "not_empty_pd_pools_list", "pd_pool_entry",
  "$@81", "sub_pd_pool", "$@82", "pd_pool_params", "pd_pool_param",
  "pd_prefix", "$@83", "pd_prefix_len", "excluded_prefix", "$@84",
  "excluded_prefix_len", "pd_delegated_len", "reservations", "$@85",
  "reservations_list", "not_empty_reservations_list", "reservation",
  "$@86", "sub_reservation", "$@87", "reservation_params",
  "not_empty_reservation_params", "reservation_param", "ip_addresses",
  "$@88", "prefixes", "$@89", "duid", "$@90", "hw_address", "$@91",
  "hostname", "$@92", "flex_id_value", "$@93",
  "reservation_client_classes", "$@94", "relay", "$@95", "relay_map",
  "ip_address", "$@96", "client_classes", "$@97", "client_classes_list",
  "client_class_entry", "$@98", "client_class_params",
  "not_empty_client_class_params", "client_class_param",
  "client_class_name", "client_class_test", "$@99", "only_if_required",
  "server_id", "$@100", "server_id_params", "server_id_param",
  "server_id_type", "$@101", "duid_type", "htype", "identifier", "$@102",
  "time", "enterprise_id", "dhcp4o6_port", "control_socket", "$@103",
  "control_socket_params", "control_socket_param", "socket_type", "$@104",
  "socket_name", "$@105", "dhcp_queue_control", "$@106", "dhcp_ddns",
  "$@107", "sub_dhcp_ddns", "$@108", "dhcp_ddns_params", "dhcp_ddns_param",
  "enable_updates", "qualifying_suffix", "$@109", "server_ip", "$@110",
  "server_port", "sender_ip", "$@111", "sender_port", "max_queue_size",
  "ncr_protocol", "$@112", "ncr_protocol_value", "ncr_format", "$@113",
  "override_no_update", "override_client_update", "replace_client_name",
  "$@114", "replace_client_name_value", "generated_prefix", "$@115",
  "hostname_char_set", "$@116", "hostname_char_replacement", "$@117",
  "dhcp4_json_object", "$@118", "dhcpddns_json_object", "$@119",
  "control_agent_json_object", "$@120", "config_control", "$@121",
  "sub_config_control", "$@122", "config_control_params",
  "config_control_param", "config_databases", "$@123",
  "config_fetch_wait_time", "logging_object", "$@124", "sub_logging",
  "$@125", "logging_params", "logging_param", "loggers", "$@126",
  "loggers_entries", "logger_entry", "$@127", "logger_params",
  "logger_param", "debuglevel", "severity", "$@128", "output_options_list",
  "$@129", "output_options_list_content", "output_entry", "$@130",
  "output_params_list", "output_params", "output", "$@131", "flush",
  "maxsize", "maxver", YY_NULLPTR
  };

#if PARSER6_DEBUG
  const unsigned short
  Dhcp6Parser::yyrline_[] =
  {
       0,   265,   265,   265,   266,   266,   267,   267,   268,   268,
     269,   269,   270,   270,   271,   271,   272,   272,   273,   273,
     274,   274,   275,   275,   276,   276,   277,   277,   278,   278,
     279,   279,   287,   288,   289,   290,   291,   292,   293,   296,
     301,   301,   312,   315,   316,   319,   323,   330,   330,   337,
     338,   341,   345,   352,   352,   359,   360,   363,   367,   378,
     388,   388,   403,   404,   408,   409,   410,   411,   412,   413,
     416,   416,   431,   431,   440,   441,   446,   447,   448,   449,
     450,   451,   452,   453,   454,   455,   456,   457,   458,   459,
     460,   461,   462,   463,   464,   465,   466,   467,   468,   469,
     470,   471,   472,   473,   474,   475,   476,   477,   478,   479,
     480,   481,   482,   483,   484,   487,   487,   495,   500,   505,
     510,   515,   520,   525,   530,   535,   535,   543,   543,   554,
     554,   563,   564,   567,   568,   569,   570,   571,   574,   574,
     584,   590,   590,   602,   602,   614,   614,   624,   625,   628,
     629,   632,   632,   642,   643,   646,   647,   648,   649,   650,
     651,   652,   653,   654,   655,   656,   657,   658,   659,   660,
     661,   662,   663,   664,   665,   668,   668,   675,   676,   677,
     678,   681,   681,   689,   689,   697,   697,   705,   710,   710,
     718,   723,   728,   733,   738,   743,   748,   753,   758,   758,
     766,   771,   771,   779,   779,   787,   787,   795,   795,   805,
     806,   808,   810,   810,   828,   828,   838,   839,   842,   843,
     846,   851,   856,   856,   866,   867,   870,   871,   872,   875,
     880,   887,   887,   897,   897,   907,   908,   911,   912,   915,
     915,   925,   925,   935,   936,   937,   940,   941,   944,   944,
     952,   952,   960,   960,   971,   972,   975,   976,   977,   978,
     979,   980,   983,   988,   993,   998,  1003,  1008,  1016,  1016,
    1029,  1030,  1033,  1034,  1041,  1041,  1067,  1067,  1078,  1079,
    1083,  1084,  1085,  1086,  1087,  1088,  1089,  1090,  1091,  1092,
    1093,  1094,  1095,  1096,  1097,  1098,  1099,  1100,  1101,  1102,
    1103,  1104,  1105,  1108,  1108,  1116,  1116,  1124,  1124,  1132,
    1132,  1140,  1140,  1150,  1150,  1157,  1158,  1159,  1160,  1163,
    1168,  1176,  1176,  1187,  1188,  1192,  1193,  1196,  1196,  1204,
    1205,  1208,  1209,  1210,  1211,  1212,  1213,  1214,  1215,  1216,
    1217,  1218,  1219,  1220,  1221,  1222,  1223,  1224,  1225,  1226,
    1227,  1234,  1234,  1247,  1247,  1256,  1257,  1260,  1261,  1266,
    1266,  1281,  1281,  1295,  1296,  1299,  1300,  1303,  1304,  1305,
    1306,  1307,  1308,  1309,  1310,  1311,  1312,  1315,  1317,  1322,
    1324,  1324,  1332,  1332,  1340,  1340,  1348,  1350,  1350,  1358,
    1367,  1367,  1379,  1380,  1385,  1386,  1391,  1391,  1403,  1403,
    1415,  1416,  1421,  1422,  1427,  1428,  1429,  1430,  1431,  1432,
    1433,  1434,  1435,  1438,  1440,  1440,  1448,  1450,  1452,  1457,
    1465,  1465,  1477,  1478,  1481,  1482,  1485,  1485,  1495,  1495,
    1504,  1505,  1508,  1509,  1510,  1511,  1512,  1513,  1514,  1517,
    1517,  1525,  1525,  1550,  1550,  1580,  1580,  1592,  1593,  1596,
    1597,  1600,  1600,  1612,  1612,  1624,  1625,  1628,  1629,  1630,
    1631,  1632,  1633,  1634,  1635,  1636,  1637,  1638,  1641,  1641,
    1649,  1654,  1654,  1662,  1667,  1675,  1675,  1685,  1686,  1689,
    1690,  1693,  1693,  1702,  1702,  1711,  1712,  1715,  1716,  1720,
    1721,  1722,  1723,  1724,  1725,  1726,  1727,  1728,  1729,  1730,
    1733,  1733,  1743,  1743,  1753,  1753,  1761,  1761,  1769,  1769,
    1777,  1777,  1785,  1785,  1798,  1798,  1808,  1809,  1812,  1812,
    1823,  1823,  1833,  1834,  1837,  1837,  1847,  1848,  1851,  1852,
    1855,  1856,  1857,  1858,  1859,  1860,  1861,  1864,  1866,  1866,
    1874,  1882,  1882,  1894,  1895,  1898,  1899,  1900,  1901,  1902,
    1903,  1904,  1905,  1906,  1909,  1909,  1916,  1917,  1918,  1921,
    1926,  1926,  1934,  1939,  1946,  1953,  1953,  1963,  1964,  1967,
    1968,  1969,  1970,  1971,  1974,  1974,  1982,  1982,  1992,  1992,
    2032,  2032,  2044,  2044,  2054,  2055,  2058,  2059,  2060,  2061,
    2062,  2063,  2064,  2065,  2066,  2067,  2068,  2069,  2070,  2071,
    2072,  2073,  2074,  2075,  2078,  2083,  2083,  2091,  2091,  2099,
    2104,  2104,  2112,  2117,  2122,  2122,  2130,  2131,  2134,  2134,
    2142,  2147,  2152,  2152,  2160,  2163,  2166,  2169,  2172,  2178,
    2178,  2186,  2186,  2194,  2194,  2204,  2204,  2211,  2211,  2218,
    2218,  2227,  2227,  2238,  2238,  2248,  2249,  2253,  2254,  2257,
    2257,  2267,  2277,  2277,  2287,  2287,  2298,  2299,  2303,  2307,
    2307,  2319,  2320,  2324,  2324,  2332,  2333,  2336,  2337,  2338,
    2339,  2340,  2341,  2342,  2345,  2350,  2350,  2358,  2358,  2368,
    2369,  2372,  2372,  2380,  2381,  2384,  2385,  2386,  2387,  2390,
    2390,  2398,  2403,  2408
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
      *yycdebug_ << ' ' << i->state;
    *yycdebug_ << '\n';
  }

  // Report on the debug stream that the rule \a yyrule is going to be reduced.
  void
  Dhcp6Parser::yy_reduce_print_ (int yyrule)
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
#endif // PARSER6_DEBUG


#line 14 "dhcp6_parser.yy"
} } // isc::dhcp
#line 5199 "dhcp6_parser.cc"

#line 2413 "dhcp6_parser.yy"


void
isc::dhcp::Dhcp6Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
