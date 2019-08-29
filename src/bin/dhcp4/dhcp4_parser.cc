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
      case 195: // value
      case 199: // map_value
      case 245: // socket_type
      case 248: // outbound_interface_value
      case 270: // db_type
      case 357: // hr_mode
      case 506: // ncr_protocol_value
      case 513: // replace_client_name_value
        value.YY_MOVE_OR_COPY< ElementPtr > (YY_MOVE (that.value));
        break;

      case 178: // "boolean"
        value.YY_MOVE_OR_COPY< bool > (YY_MOVE (that.value));
        break;

      case 177: // "floating point"
        value.YY_MOVE_OR_COPY< double > (YY_MOVE (that.value));
        break;

      case 176: // "integer"
        value.YY_MOVE_OR_COPY< int64_t > (YY_MOVE (that.value));
        break;

      case 175: // "constant string"
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
      case 195: // value
      case 199: // map_value
      case 245: // socket_type
      case 248: // outbound_interface_value
      case 270: // db_type
      case 357: // hr_mode
      case 506: // ncr_protocol_value
      case 513: // replace_client_name_value
        value.move< ElementPtr > (YY_MOVE (that.value));
        break;

      case 178: // "boolean"
        value.move< bool > (YY_MOVE (that.value));
        break;

      case 177: // "floating point"
        value.move< double > (YY_MOVE (that.value));
        break;

      case 176: // "integer"
        value.move< int64_t > (YY_MOVE (that.value));
        break;

      case 175: // "constant string"
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
      case 195: // value
      case 199: // map_value
      case 245: // socket_type
      case 248: // outbound_interface_value
      case 270: // db_type
      case 357: // hr_mode
      case 506: // ncr_protocol_value
      case 513: // replace_client_name_value
        value.move< ElementPtr > (that.value);
        break;

      case 178: // "boolean"
        value.move< bool > (that.value);
        break;

      case 177: // "floating point"
        value.move< double > (that.value);
        break;

      case 176: // "integer"
        value.move< int64_t > (that.value);
        break;

      case 175: // "constant string"
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
      case 175: // "constant string"
#line 257 "dhcp4_parser.yy"
        { yyoutput << yysym.value.template as < std::string > (); }
#line 408 "dhcp4_parser.cc"
        break;

      case 176: // "integer"
#line 257 "dhcp4_parser.yy"
        { yyoutput << yysym.value.template as < int64_t > (); }
#line 414 "dhcp4_parser.cc"
        break;

      case 177: // "floating point"
#line 257 "dhcp4_parser.yy"
        { yyoutput << yysym.value.template as < double > (); }
#line 420 "dhcp4_parser.cc"
        break;

      case 178: // "boolean"
#line 257 "dhcp4_parser.yy"
        { yyoutput << yysym.value.template as < bool > (); }
#line 426 "dhcp4_parser.cc"
        break;

      case 195: // value
#line 257 "dhcp4_parser.yy"
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 432 "dhcp4_parser.cc"
        break;

      case 199: // map_value
#line 257 "dhcp4_parser.yy"
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 438 "dhcp4_parser.cc"
        break;

      case 245: // socket_type
#line 257 "dhcp4_parser.yy"
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 444 "dhcp4_parser.cc"
        break;

      case 248: // outbound_interface_value
#line 257 "dhcp4_parser.yy"
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 450 "dhcp4_parser.cc"
        break;

      case 270: // db_type
#line 257 "dhcp4_parser.yy"
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 456 "dhcp4_parser.cc"
        break;

      case 357: // hr_mode
#line 257 "dhcp4_parser.yy"
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 462 "dhcp4_parser.cc"
        break;

      case 506: // ncr_protocol_value
#line 257 "dhcp4_parser.yy"
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 468 "dhcp4_parser.cc"
        break;

      case 513: // replace_client_name_value
#line 257 "dhcp4_parser.yy"
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
      case 195: // value
      case 199: // map_value
      case 245: // socket_type
      case 248: // outbound_interface_value
      case 270: // db_type
      case 357: // hr_mode
      case 506: // ncr_protocol_value
      case 513: // replace_client_name_value
        yylhs.value.emplace< ElementPtr > ();
        break;

      case 178: // "boolean"
        yylhs.value.emplace< bool > ();
        break;

      case 177: // "floating point"
        yylhs.value.emplace< double > ();
        break;

      case 176: // "integer"
        yylhs.value.emplace< int64_t > ();
        break;

      case 175: // "constant string"
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
#line 266 "dhcp4_parser.yy"
    { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 741 "dhcp4_parser.cc"
    break;

  case 4:
#line 267 "dhcp4_parser.yy"
    { ctx.ctx_ = ctx.CONFIG; }
#line 747 "dhcp4_parser.cc"
    break;

  case 6:
#line 268 "dhcp4_parser.yy"
    { ctx.ctx_ = ctx.DHCP4; }
#line 753 "dhcp4_parser.cc"
    break;

  case 8:
#line 269 "dhcp4_parser.yy"
    { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 759 "dhcp4_parser.cc"
    break;

  case 10:
#line 270 "dhcp4_parser.yy"
    { ctx.ctx_ = ctx.SUBNET4; }
#line 765 "dhcp4_parser.cc"
    break;

  case 12:
#line 271 "dhcp4_parser.yy"
    { ctx.ctx_ = ctx.POOLS; }
#line 771 "dhcp4_parser.cc"
    break;

  case 14:
#line 272 "dhcp4_parser.yy"
    { ctx.ctx_ = ctx.RESERVATIONS; }
#line 777 "dhcp4_parser.cc"
    break;

  case 16:
#line 273 "dhcp4_parser.yy"
    { ctx.ctx_ = ctx.DHCP4; }
#line 783 "dhcp4_parser.cc"
    break;

  case 18:
#line 274 "dhcp4_parser.yy"
    { ctx.ctx_ = ctx.OPTION_DEF; }
#line 789 "dhcp4_parser.cc"
    break;

  case 20:
#line 275 "dhcp4_parser.yy"
    { ctx.ctx_ = ctx.OPTION_DATA; }
#line 795 "dhcp4_parser.cc"
    break;

  case 22:
#line 276 "dhcp4_parser.yy"
    { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 801 "dhcp4_parser.cc"
    break;

  case 24:
#line 277 "dhcp4_parser.yy"
    { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 807 "dhcp4_parser.cc"
    break;

  case 26:
#line 278 "dhcp4_parser.yy"
    { ctx.ctx_ = ctx.LOGGING; }
#line 813 "dhcp4_parser.cc"
    break;

  case 28:
#line 279 "dhcp4_parser.yy"
    { ctx.ctx_ = ctx.CONFIG_CONTROL; }
#line 819 "dhcp4_parser.cc"
    break;

  case 30:
#line 287 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 825 "dhcp4_parser.cc"
    break;

  case 31:
#line 288 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location))); }
#line 831 "dhcp4_parser.cc"
    break;

  case 32:
#line 289 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 837 "dhcp4_parser.cc"
    break;

  case 33:
#line 290 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 843 "dhcp4_parser.cc"
    break;

  case 34:
#line 291 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 849 "dhcp4_parser.cc"
    break;

  case 35:
#line 292 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 855 "dhcp4_parser.cc"
    break;

  case 36:
#line 293 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 861 "dhcp4_parser.cc"
    break;

  case 37:
#line 296 "dhcp4_parser.yy"
    {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as < ElementPtr > ());
}
#line 870 "dhcp4_parser.cc"
    break;

  case 38:
#line 301 "dhcp4_parser.yy"
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 881 "dhcp4_parser.cc"
    break;

  case 39:
#line 306 "dhcp4_parser.yy"
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 891 "dhcp4_parser.cc"
    break;

  case 40:
#line 312 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 897 "dhcp4_parser.cc"
    break;

  case 43:
#line 319 "dhcp4_parser.yy"
    {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 906 "dhcp4_parser.cc"
    break;

  case 44:
#line 323 "dhcp4_parser.yy"
    {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 916 "dhcp4_parser.cc"
    break;

  case 45:
#line 330 "dhcp4_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 925 "dhcp4_parser.cc"
    break;

  case 46:
#line 333 "dhcp4_parser.yy"
    {
    // list parsing complete. Put any sanity checking here
}
#line 933 "dhcp4_parser.cc"
    break;

  case 49:
#line 341 "dhcp4_parser.yy"
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 942 "dhcp4_parser.cc"
    break;

  case 50:
#line 345 "dhcp4_parser.yy"
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 951 "dhcp4_parser.cc"
    break;

  case 51:
#line 352 "dhcp4_parser.yy"
    {
    // List parsing about to start
}
#line 959 "dhcp4_parser.cc"
    break;

  case 52:
#line 354 "dhcp4_parser.yy"
    {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 968 "dhcp4_parser.cc"
    break;

  case 55:
#line 363 "dhcp4_parser.yy"
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 977 "dhcp4_parser.cc"
    break;

  case 56:
#line 367 "dhcp4_parser.yy"
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 986 "dhcp4_parser.cc"
    break;

  case 57:
#line 378 "dhcp4_parser.yy"
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as < std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 997 "dhcp4_parser.cc"
    break;

  case 58:
#line 388 "dhcp4_parser.yy"
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1008 "dhcp4_parser.cc"
    break;

  case 59:
#line 393 "dhcp4_parser.yy"
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
#line 417 "dhcp4_parser.yy"
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
#line 424 "dhcp4_parser.yy"
    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1044 "dhcp4_parser.cc"
    break;

  case 70:
#line 432 "dhcp4_parser.yy"
    {
    // Parse the Dhcp4 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1054 "dhcp4_parser.cc"
    break;

  case 71:
#line 436 "dhcp4_parser.yy"
    {
    // No global parameter is required
    // parsing completed
}
#line 1063 "dhcp4_parser.cc"
    break;

  case 116:
#line 491 "dhcp4_parser.yy"
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1072 "dhcp4_parser.cc"
    break;

  case 117:
#line 496 "dhcp4_parser.yy"
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-valid-lifetime", prf);
}
#line 1081 "dhcp4_parser.cc"
    break;

  case 118:
#line 501 "dhcp4_parser.yy"
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-valid-lifetime", prf);
}
#line 1090 "dhcp4_parser.cc"
    break;

  case 119:
#line 506 "dhcp4_parser.yy"
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1099 "dhcp4_parser.cc"
    break;

  case 120:
#line 511 "dhcp4_parser.yy"
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1108 "dhcp4_parser.cc"
    break;

  case 121:
#line 516 "dhcp4_parser.yy"
    {
    ElementPtr ctt(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("calculate-tee-times", ctt);
}
#line 1117 "dhcp4_parser.cc"
    break;

  case 122:
#line 521 "dhcp4_parser.yy"
    {
    ElementPtr t1(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t1-percent", t1);
}
#line 1126 "dhcp4_parser.cc"
    break;

  case 123:
#line 526 "dhcp4_parser.yy"
    {
    ElementPtr t2(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t2-percent", t2);
}
#line 1135 "dhcp4_parser.cc"
    break;

  case 124:
#line 531 "dhcp4_parser.yy"
    {
    ElementPtr dpp(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1144 "dhcp4_parser.cc"
    break;

  case 125:
#line 536 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1152 "dhcp4_parser.cc"
    break;

  case 126:
#line 538 "dhcp4_parser.yy"
    {
    ElementPtr stag(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-tag", stag);
    ctx.leave();
}
#line 1162 "dhcp4_parser.cc"
    break;

  case 127:
#line 544 "dhcp4_parser.yy"
    {
    ElementPtr echo(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("echo-client-id", echo);
}
#line 1171 "dhcp4_parser.cc"
    break;

  case 128:
#line 549 "dhcp4_parser.yy"
    {
    ElementPtr match(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("match-client-id", match);
}
#line 1180 "dhcp4_parser.cc"
    break;

  case 129:
#line 554 "dhcp4_parser.yy"
    {
    ElementPtr prf(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("authoritative", prf);
}
#line 1189 "dhcp4_parser.cc"
    break;

  case 130:
#line 560 "dhcp4_parser.yy"
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1200 "dhcp4_parser.cc"
    break;

  case 131:
#line 565 "dhcp4_parser.yy"
    {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1210 "dhcp4_parser.cc"
    break;

  case 141:
#line 584 "dhcp4_parser.yy"
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1220 "dhcp4_parser.cc"
    break;

  case 142:
#line 588 "dhcp4_parser.yy"
    {
    // No interfaces config param is required
    // parsing completed
}
#line 1229 "dhcp4_parser.cc"
    break;

  case 143:
#line 593 "dhcp4_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1240 "dhcp4_parser.cc"
    break;

  case 144:
#line 598 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1249 "dhcp4_parser.cc"
    break;

  case 145:
#line 603 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.DHCP_SOCKET_TYPE);
}
#line 1257 "dhcp4_parser.cc"
    break;

  case 146:
#line 605 "dhcp4_parser.yy"
    {
    ctx.stack_.back()->set("dhcp-socket-type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1266 "dhcp4_parser.cc"
    break;

  case 147:
#line 610 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("raw", ctx.loc2pos(yystack_[0].location))); }
#line 1272 "dhcp4_parser.cc"
    break;

  case 148:
#line 611 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("udp", ctx.loc2pos(yystack_[0].location))); }
#line 1278 "dhcp4_parser.cc"
    break;

  case 149:
#line 614 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.OUTBOUND_INTERFACE);
}
#line 1286 "dhcp4_parser.cc"
    break;

  case 150:
#line 616 "dhcp4_parser.yy"
    {
    ctx.stack_.back()->set("outbound-interface", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1295 "dhcp4_parser.cc"
    break;

  case 151:
#line 621 "dhcp4_parser.yy"
    {
    yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("same-as-inbound", ctx.loc2pos(yystack_[0].location)));
}
#line 1303 "dhcp4_parser.cc"
    break;

  case 152:
#line 623 "dhcp4_parser.yy"
    {
    yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("use-routing", ctx.loc2pos(yystack_[0].location)));
    }
#line 1311 "dhcp4_parser.cc"
    break;

  case 153:
#line 627 "dhcp4_parser.yy"
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1320 "dhcp4_parser.cc"
    break;

  case 154:
#line 633 "dhcp4_parser.yy"
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1331 "dhcp4_parser.cc"
    break;

  case 155:
#line 638 "dhcp4_parser.yy"
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1342 "dhcp4_parser.cc"
    break;

  case 156:
#line 645 "dhcp4_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sanity-checks", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SANITY_CHECKS);
}
#line 1353 "dhcp4_parser.cc"
    break;

  case 157:
#line 650 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1362 "dhcp4_parser.cc"
    break;

  case 161:
#line 660 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1370 "dhcp4_parser.cc"
    break;

  case 162:
#line 662 "dhcp4_parser.yy"
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
#line 1390 "dhcp4_parser.cc"
    break;

  case 163:
#line 678 "dhcp4_parser.yy"
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1401 "dhcp4_parser.cc"
    break;

  case 164:
#line 683 "dhcp4_parser.yy"
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1412 "dhcp4_parser.cc"
    break;

  case 165:
#line 690 "dhcp4_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1423 "dhcp4_parser.cc"
    break;

  case 166:
#line 695 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1432 "dhcp4_parser.cc"
    break;

  case 171:
#line 708 "dhcp4_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1442 "dhcp4_parser.cc"
    break;

  case 172:
#line 712 "dhcp4_parser.yy"
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1452 "dhcp4_parser.cc"
    break;

  case 196:
#line 745 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1460 "dhcp4_parser.cc"
    break;

  case 197:
#line 747 "dhcp4_parser.yy"
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1469 "dhcp4_parser.cc"
    break;

  case 198:
#line 752 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1475 "dhcp4_parser.cc"
    break;

  case 199:
#line 753 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1481 "dhcp4_parser.cc"
    break;

  case 200:
#line 754 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1487 "dhcp4_parser.cc"
    break;

  case 201:
#line 755 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1493 "dhcp4_parser.cc"
    break;

  case 202:
#line 758 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1501 "dhcp4_parser.cc"
    break;

  case 203:
#line 760 "dhcp4_parser.yy"
    {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1511 "dhcp4_parser.cc"
    break;

  case 204:
#line 766 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1519 "dhcp4_parser.cc"
    break;

  case 205:
#line 768 "dhcp4_parser.yy"
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1529 "dhcp4_parser.cc"
    break;

  case 206:
#line 774 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1537 "dhcp4_parser.cc"
    break;

  case 207:
#line 776 "dhcp4_parser.yy"
    {
    ElementPtr h(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1547 "dhcp4_parser.cc"
    break;

  case 208:
#line 782 "dhcp4_parser.yy"
    {
    ElementPtr p(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1556 "dhcp4_parser.cc"
    break;

  case 209:
#line 787 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1564 "dhcp4_parser.cc"
    break;

  case 210:
#line 789 "dhcp4_parser.yy"
    {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1574 "dhcp4_parser.cc"
    break;

  case 211:
#line 795 "dhcp4_parser.yy"
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1583 "dhcp4_parser.cc"
    break;

  case 212:
#line 800 "dhcp4_parser.yy"
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1592 "dhcp4_parser.cc"
    break;

  case 213:
#line 805 "dhcp4_parser.yy"
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1601 "dhcp4_parser.cc"
    break;

  case 214:
#line 810 "dhcp4_parser.yy"
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1610 "dhcp4_parser.cc"
    break;

  case 215:
#line 815 "dhcp4_parser.yy"
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("request-timeout", n);
}
#line 1619 "dhcp4_parser.cc"
    break;

  case 216:
#line 820 "dhcp4_parser.yy"
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-keepalive", n);
}
#line 1628 "dhcp4_parser.cc"
    break;

  case 217:
#line 825 "dhcp4_parser.yy"
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-nodelay", n);
}
#line 1637 "dhcp4_parser.cc"
    break;

  case 218:
#line 830 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1645 "dhcp4_parser.cc"
    break;

  case 219:
#line 832 "dhcp4_parser.yy"
    {
    ElementPtr cp(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1655 "dhcp4_parser.cc"
    break;

  case 220:
#line 838 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1663 "dhcp4_parser.cc"
    break;

  case 221:
#line 840 "dhcp4_parser.yy"
    {
    ElementPtr ks(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 1673 "dhcp4_parser.cc"
    break;

  case 222:
#line 846 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1681 "dhcp4_parser.cc"
    break;

  case 223:
#line 848 "dhcp4_parser.yy"
    {
    ElementPtr c(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("consistency", c);
    ctx.leave();
}
#line 1691 "dhcp4_parser.cc"
    break;

  case 224:
#line 854 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1699 "dhcp4_parser.cc"
    break;

  case 225:
#line 856 "dhcp4_parser.yy"
    {
    ElementPtr c(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("serial-consistency", c);
    ctx.leave();
}
#line 1709 "dhcp4_parser.cc"
    break;

  case 226:
#line 862 "dhcp4_parser.yy"
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 1718 "dhcp4_parser.cc"
    break;

  case 227:
#line 867 "dhcp4_parser.yy"
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 1727 "dhcp4_parser.cc"
    break;

  case 228:
#line 872 "dhcp4_parser.yy"
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-row-errors", n);
}
#line 1736 "dhcp4_parser.cc"
    break;

  case 229:
#line 878 "dhcp4_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1747 "dhcp4_parser.cc"
    break;

  case 230:
#line 883 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1756 "dhcp4_parser.cc"
    break;

  case 238:
#line 899 "dhcp4_parser.yy"
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1765 "dhcp4_parser.cc"
    break;

  case 239:
#line 904 "dhcp4_parser.yy"
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1774 "dhcp4_parser.cc"
    break;

  case 240:
#line 909 "dhcp4_parser.yy"
    {
    ElementPtr circuit(new StringElement("circuit-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(circuit);
}
#line 1783 "dhcp4_parser.cc"
    break;

  case 241:
#line 914 "dhcp4_parser.yy"
    {
    ElementPtr client(new StringElement("client-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(client);
}
#line 1792 "dhcp4_parser.cc"
    break;

  case 242:
#line 919 "dhcp4_parser.yy"
    {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 1801 "dhcp4_parser.cc"
    break;

  case 243:
#line 924 "dhcp4_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1812 "dhcp4_parser.cc"
    break;

  case 244:
#line 929 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1821 "dhcp4_parser.cc"
    break;

  case 249:
#line 942 "dhcp4_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1831 "dhcp4_parser.cc"
    break;

  case 250:
#line 946 "dhcp4_parser.yy"
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1841 "dhcp4_parser.cc"
    break;

  case 251:
#line 952 "dhcp4_parser.yy"
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1851 "dhcp4_parser.cc"
    break;

  case 252:
#line 956 "dhcp4_parser.yy"
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1861 "dhcp4_parser.cc"
    break;

  case 258:
#line 971 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1869 "dhcp4_parser.cc"
    break;

  case 259:
#line 973 "dhcp4_parser.yy"
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1879 "dhcp4_parser.cc"
    break;

  case 260:
#line 979 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1887 "dhcp4_parser.cc"
    break;

  case 261:
#line 981 "dhcp4_parser.yy"
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1896 "dhcp4_parser.cc"
    break;

  case 262:
#line 987 "dhcp4_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 1907 "dhcp4_parser.cc"
    break;

  case 263:
#line 992 "dhcp4_parser.yy"
    {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1917 "dhcp4_parser.cc"
    break;

  case 272:
#line 1010 "dhcp4_parser.yy"
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 1926 "dhcp4_parser.cc"
    break;

  case 273:
#line 1015 "dhcp4_parser.yy"
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 1935 "dhcp4_parser.cc"
    break;

  case 274:
#line 1020 "dhcp4_parser.yy"
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 1944 "dhcp4_parser.cc"
    break;

  case 275:
#line 1025 "dhcp4_parser.yy"
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 1953 "dhcp4_parser.cc"
    break;

  case 276:
#line 1030 "dhcp4_parser.yy"
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 1962 "dhcp4_parser.cc"
    break;

  case 277:
#line 1035 "dhcp4_parser.yy"
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 1971 "dhcp4_parser.cc"
    break;

  case 278:
#line 1043 "dhcp4_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet4", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET4);
}
#line 1982 "dhcp4_parser.cc"
    break;

  case 279:
#line 1048 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1991 "dhcp4_parser.cc"
    break;

  case 284:
#line 1068 "dhcp4_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2001 "dhcp4_parser.cc"
    break;

  case 285:
#line 1072 "dhcp4_parser.yy"
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
#line 2027 "dhcp4_parser.cc"
    break;

  case 286:
#line 1094 "dhcp4_parser.yy"
    {
    // Parse the subnet4 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2037 "dhcp4_parser.cc"
    break;

  case 287:
#line 1098 "dhcp4_parser.yy"
    {
    // The subnet subnet4 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2047 "dhcp4_parser.cc"
    break;

  case 319:
#line 1141 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2055 "dhcp4_parser.cc"
    break;

  case 320:
#line 1143 "dhcp4_parser.yy"
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 2065 "dhcp4_parser.cc"
    break;

  case 321:
#line 1149 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2073 "dhcp4_parser.cc"
    break;

  case 322:
#line 1151 "dhcp4_parser.yy"
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface", iface);
    ctx.leave();
}
#line 2083 "dhcp4_parser.cc"
    break;

  case 323:
#line 1157 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2091 "dhcp4_parser.cc"
    break;

  case 324:
#line 1159 "dhcp4_parser.yy"
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface-id", iface);
    ctx.leave();
}
#line 2101 "dhcp4_parser.cc"
    break;

  case 325:
#line 1165 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2109 "dhcp4_parser.cc"
    break;

  case 326:
#line 1167 "dhcp4_parser.yy"
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-subnet", iface);
    ctx.leave();
}
#line 2119 "dhcp4_parser.cc"
    break;

  case 327:
#line 1173 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2127 "dhcp4_parser.cc"
    break;

  case 328:
#line 1175 "dhcp4_parser.yy"
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 2137 "dhcp4_parser.cc"
    break;

  case 329:
#line 1181 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2145 "dhcp4_parser.cc"
    break;

  case 330:
#line 1183 "dhcp4_parser.yy"
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 2155 "dhcp4_parser.cc"
    break;

  case 331:
#line 1189 "dhcp4_parser.yy"
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2166 "dhcp4_parser.cc"
    break;

  case 332:
#line 1194 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2175 "dhcp4_parser.cc"
    break;

  case 333:
#line 1199 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 2183 "dhcp4_parser.cc"
    break;

  case 334:
#line 1201 "dhcp4_parser.yy"
    {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2192 "dhcp4_parser.cc"
    break;

  case 335:
#line 1206 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 2198 "dhcp4_parser.cc"
    break;

  case 336:
#line 1207 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 2204 "dhcp4_parser.cc"
    break;

  case 337:
#line 1208 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("global", ctx.loc2pos(yystack_[0].location))); }
#line 2210 "dhcp4_parser.cc"
    break;

  case 338:
#line 1209 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 2216 "dhcp4_parser.cc"
    break;

  case 339:
#line 1212 "dhcp4_parser.yy"
    {
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 2225 "dhcp4_parser.cc"
    break;

  case 340:
#line 1219 "dhcp4_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 2236 "dhcp4_parser.cc"
    break;

  case 341:
#line 1224 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2245 "dhcp4_parser.cc"
    break;

  case 346:
#line 1239 "dhcp4_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2255 "dhcp4_parser.cc"
    break;

  case 347:
#line 1243 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
}
#line 2263 "dhcp4_parser.cc"
    break;

  case 374:
#line 1281 "dhcp4_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 2274 "dhcp4_parser.cc"
    break;

  case 375:
#line 1286 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2283 "dhcp4_parser.cc"
    break;

  case 376:
#line 1294 "dhcp4_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2292 "dhcp4_parser.cc"
    break;

  case 377:
#line 1297 "dhcp4_parser.yy"
    {
    // parsing completed
}
#line 2300 "dhcp4_parser.cc"
    break;

  case 382:
#line 1313 "dhcp4_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2310 "dhcp4_parser.cc"
    break;

  case 383:
#line 1317 "dhcp4_parser.yy"
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2322 "dhcp4_parser.cc"
    break;

  case 384:
#line 1328 "dhcp4_parser.yy"
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2332 "dhcp4_parser.cc"
    break;

  case 385:
#line 1332 "dhcp4_parser.yy"
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2344 "dhcp4_parser.cc"
    break;

  case 401:
#line 1364 "dhcp4_parser.yy"
    {
    ElementPtr code(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 2353 "dhcp4_parser.cc"
    break;

  case 403:
#line 1371 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2361 "dhcp4_parser.cc"
    break;

  case 404:
#line 1373 "dhcp4_parser.yy"
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 2371 "dhcp4_parser.cc"
    break;

  case 405:
#line 1379 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2379 "dhcp4_parser.cc"
    break;

  case 406:
#line 1381 "dhcp4_parser.yy"
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 2389 "dhcp4_parser.cc"
    break;

  case 407:
#line 1387 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2397 "dhcp4_parser.cc"
    break;

  case 408:
#line 1389 "dhcp4_parser.yy"
    {
    ElementPtr space(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 2407 "dhcp4_parser.cc"
    break;

  case 410:
#line 1397 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2415 "dhcp4_parser.cc"
    break;

  case 411:
#line 1399 "dhcp4_parser.yy"
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 2425 "dhcp4_parser.cc"
    break;

  case 412:
#line 1405 "dhcp4_parser.yy"
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 2434 "dhcp4_parser.cc"
    break;

  case 413:
#line 1414 "dhcp4_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 2445 "dhcp4_parser.cc"
    break;

  case 414:
#line 1419 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2454 "dhcp4_parser.cc"
    break;

  case 419:
#line 1438 "dhcp4_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2464 "dhcp4_parser.cc"
    break;

  case 420:
#line 1442 "dhcp4_parser.yy"
    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 2473 "dhcp4_parser.cc"
    break;

  case 421:
#line 1450 "dhcp4_parser.yy"
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2483 "dhcp4_parser.cc"
    break;

  case 422:
#line 1454 "dhcp4_parser.yy"
    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 2492 "dhcp4_parser.cc"
    break;

  case 437:
#line 1487 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2500 "dhcp4_parser.cc"
    break;

  case 438:
#line 1489 "dhcp4_parser.yy"
    {
    ElementPtr data(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2510 "dhcp4_parser.cc"
    break;

  case 441:
#line 1499 "dhcp4_parser.yy"
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2519 "dhcp4_parser.cc"
    break;

  case 442:
#line 1504 "dhcp4_parser.yy"
    {
    ElementPtr persist(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 2528 "dhcp4_parser.cc"
    break;

  case 443:
#line 1512 "dhcp4_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2539 "dhcp4_parser.cc"
    break;

  case 444:
#line 1517 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2548 "dhcp4_parser.cc"
    break;

  case 449:
#line 1532 "dhcp4_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2558 "dhcp4_parser.cc"
    break;

  case 450:
#line 1536 "dhcp4_parser.yy"
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2568 "dhcp4_parser.cc"
    break;

  case 451:
#line 1542 "dhcp4_parser.yy"
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2578 "dhcp4_parser.cc"
    break;

  case 452:
#line 1546 "dhcp4_parser.yy"
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2588 "dhcp4_parser.cc"
    break;

  case 462:
#line 1565 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2596 "dhcp4_parser.cc"
    break;

  case 463:
#line 1567 "dhcp4_parser.yy"
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2606 "dhcp4_parser.cc"
    break;

  case 464:
#line 1573 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2614 "dhcp4_parser.cc"
    break;

  case 465:
#line 1575 "dhcp4_parser.yy"
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
#line 2641 "dhcp4_parser.cc"
    break;

  case 466:
#line 1598 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2649 "dhcp4_parser.cc"
    break;

  case 467:
#line 1600 "dhcp4_parser.yy"
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
#line 2678 "dhcp4_parser.cc"
    break;

  case 468:
#line 1628 "dhcp4_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 2689 "dhcp4_parser.cc"
    break;

  case 469:
#line 1633 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2698 "dhcp4_parser.cc"
    break;

  case 474:
#line 1646 "dhcp4_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2708 "dhcp4_parser.cc"
    break;

  case 475:
#line 1650 "dhcp4_parser.yy"
    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 2717 "dhcp4_parser.cc"
    break;

  case 476:
#line 1655 "dhcp4_parser.yy"
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2727 "dhcp4_parser.cc"
    break;

  case 477:
#line 1659 "dhcp4_parser.yy"
    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 2736 "dhcp4_parser.cc"
    break;

  case 497:
#line 1690 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2744 "dhcp4_parser.cc"
    break;

  case 498:
#line 1692 "dhcp4_parser.yy"
    {
    ElementPtr next_server(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("next-server", next_server);
    ctx.leave();
}
#line 2754 "dhcp4_parser.cc"
    break;

  case 499:
#line 1698 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2762 "dhcp4_parser.cc"
    break;

  case 500:
#line 1700 "dhcp4_parser.yy"
    {
    ElementPtr srv(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-hostname", srv);
    ctx.leave();
}
#line 2772 "dhcp4_parser.cc"
    break;

  case 501:
#line 1706 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2780 "dhcp4_parser.cc"
    break;

  case 502:
#line 1708 "dhcp4_parser.yy"
    {
    ElementPtr bootfile(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("boot-file-name", bootfile);
    ctx.leave();
}
#line 2790 "dhcp4_parser.cc"
    break;

  case 503:
#line 1714 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2798 "dhcp4_parser.cc"
    break;

  case 504:
#line 1716 "dhcp4_parser.yy"
    {
    ElementPtr addr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 2808 "dhcp4_parser.cc"
    break;

  case 505:
#line 1722 "dhcp4_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2819 "dhcp4_parser.cc"
    break;

  case 506:
#line 1727 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2828 "dhcp4_parser.cc"
    break;

  case 507:
#line 1732 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2836 "dhcp4_parser.cc"
    break;

  case 508:
#line 1734 "dhcp4_parser.yy"
    {
    ElementPtr d(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2846 "dhcp4_parser.cc"
    break;

  case 509:
#line 1740 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2854 "dhcp4_parser.cc"
    break;

  case 510:
#line 1742 "dhcp4_parser.yy"
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2864 "dhcp4_parser.cc"
    break;

  case 511:
#line 1748 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2872 "dhcp4_parser.cc"
    break;

  case 512:
#line 1750 "dhcp4_parser.yy"
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-id", hw);
    ctx.leave();
}
#line 2882 "dhcp4_parser.cc"
    break;

  case 513:
#line 1756 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2890 "dhcp4_parser.cc"
    break;

  case 514:
#line 1758 "dhcp4_parser.yy"
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("circuit-id", hw);
    ctx.leave();
}
#line 2900 "dhcp4_parser.cc"
    break;

  case 515:
#line 1764 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2908 "dhcp4_parser.cc"
    break;

  case 516:
#line 1766 "dhcp4_parser.yy"
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 2918 "dhcp4_parser.cc"
    break;

  case 517:
#line 1772 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2926 "dhcp4_parser.cc"
    break;

  case 518:
#line 1774 "dhcp4_parser.yy"
    {
    ElementPtr host(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2936 "dhcp4_parser.cc"
    break;

  case 519:
#line 1780 "dhcp4_parser.yy"
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2947 "dhcp4_parser.cc"
    break;

  case 520:
#line 1785 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2956 "dhcp4_parser.cc"
    break;

  case 521:
#line 1793 "dhcp4_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2967 "dhcp4_parser.cc"
    break;

  case 522:
#line 1798 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2976 "dhcp4_parser.cc"
    break;

  case 525:
#line 1810 "dhcp4_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2987 "dhcp4_parser.cc"
    break;

  case 526:
#line 1815 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2996 "dhcp4_parser.cc"
    break;

  case 529:
#line 1824 "dhcp4_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3006 "dhcp4_parser.cc"
    break;

  case 530:
#line 1828 "dhcp4_parser.yy"
    {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3016 "dhcp4_parser.cc"
    break;

  case 547:
#line 1857 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3024 "dhcp4_parser.cc"
    break;

  case 548:
#line 1859 "dhcp4_parser.yy"
    {
    ElementPtr test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 3034 "dhcp4_parser.cc"
    break;

  case 549:
#line 1865 "dhcp4_parser.yy"
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 3043 "dhcp4_parser.cc"
    break;

  case 550:
#line 1874 "dhcp4_parser.yy"
    {
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 3052 "dhcp4_parser.cc"
    break;

  case 551:
#line 1881 "dhcp4_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 3063 "dhcp4_parser.cc"
    break;

  case 552:
#line 1886 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3072 "dhcp4_parser.cc"
    break;

  case 560:
#line 1902 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3080 "dhcp4_parser.cc"
    break;

  case 561:
#line 1904 "dhcp4_parser.yy"
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 3090 "dhcp4_parser.cc"
    break;

  case 562:
#line 1910 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3098 "dhcp4_parser.cc"
    break;

  case 563:
#line 1912 "dhcp4_parser.yy"
    {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 3108 "dhcp4_parser.cc"
    break;

  case 564:
#line 1921 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3116 "dhcp4_parser.cc"
    break;

  case 565:
#line 1923 "dhcp4_parser.yy"
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
#line 3154 "dhcp4_parser.cc"
    break;

  case 566:
#line 1959 "dhcp4_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 3165 "dhcp4_parser.cc"
    break;

  case 567:
#line 1964 "dhcp4_parser.yy"
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3176 "dhcp4_parser.cc"
    break;

  case 568:
#line 1971 "dhcp4_parser.yy"
    {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3186 "dhcp4_parser.cc"
    break;

  case 569:
#line 1975 "dhcp4_parser.yy"
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3196 "dhcp4_parser.cc"
    break;

  case 590:
#line 2005 "dhcp4_parser.yy"
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 3205 "dhcp4_parser.cc"
    break;

  case 591:
#line 2010 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3213 "dhcp4_parser.cc"
    break;

  case 592:
#line 2012 "dhcp4_parser.yy"
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 3223 "dhcp4_parser.cc"
    break;

  case 593:
#line 2018 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3231 "dhcp4_parser.cc"
    break;

  case 594:
#line 2020 "dhcp4_parser.yy"
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 3241 "dhcp4_parser.cc"
    break;

  case 595:
#line 2026 "dhcp4_parser.yy"
    {
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 3250 "dhcp4_parser.cc"
    break;

  case 596:
#line 2031 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3258 "dhcp4_parser.cc"
    break;

  case 597:
#line 2033 "dhcp4_parser.yy"
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 3268 "dhcp4_parser.cc"
    break;

  case 598:
#line 2039 "dhcp4_parser.yy"
    {
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 3277 "dhcp4_parser.cc"
    break;

  case 599:
#line 2044 "dhcp4_parser.yy"
    {
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 3286 "dhcp4_parser.cc"
    break;

  case 600:
#line 2049 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 3294 "dhcp4_parser.cc"
    break;

  case 601:
#line 2051 "dhcp4_parser.yy"
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3303 "dhcp4_parser.cc"
    break;

  case 602:
#line 2057 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 3309 "dhcp4_parser.cc"
    break;

  case 603:
#line 2058 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 3315 "dhcp4_parser.cc"
    break;

  case 604:
#line 2061 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 3323 "dhcp4_parser.cc"
    break;

  case 605:
#line 2063 "dhcp4_parser.yy"
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 3333 "dhcp4_parser.cc"
    break;

  case 606:
#line 2069 "dhcp4_parser.yy"
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 3342 "dhcp4_parser.cc"
    break;

  case 607:
#line 2074 "dhcp4_parser.yy"
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 3351 "dhcp4_parser.cc"
    break;

  case 608:
#line 2079 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 3359 "dhcp4_parser.cc"
    break;

  case 609:
#line 2081 "dhcp4_parser.yy"
    {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3368 "dhcp4_parser.cc"
    break;

  case 610:
#line 2087 "dhcp4_parser.yy"
    {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 3376 "dhcp4_parser.cc"
    break;

  case 611:
#line 2090 "dhcp4_parser.yy"
    {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 3384 "dhcp4_parser.cc"
    break;

  case 612:
#line 2093 "dhcp4_parser.yy"
    {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 3392 "dhcp4_parser.cc"
    break;

  case 613:
#line 2096 "dhcp4_parser.yy"
    {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 3400 "dhcp4_parser.cc"
    break;

  case 614:
#line 2099 "dhcp4_parser.yy"
    {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 3409 "dhcp4_parser.cc"
    break;

  case 615:
#line 2105 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3417 "dhcp4_parser.cc"
    break;

  case 616:
#line 2107 "dhcp4_parser.yy"
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 3427 "dhcp4_parser.cc"
    break;

  case 617:
#line 2113 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3435 "dhcp4_parser.cc"
    break;

  case 618:
#line 2115 "dhcp4_parser.yy"
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 3445 "dhcp4_parser.cc"
    break;

  case 619:
#line 2121 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3453 "dhcp4_parser.cc"
    break;

  case 620:
#line 2123 "dhcp4_parser.yy"
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 3463 "dhcp4_parser.cc"
    break;

  case 621:
#line 2132 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3471 "dhcp4_parser.cc"
    break;

  case 622:
#line 2134 "dhcp4_parser.yy"
    {
    ctx.stack_.back()->set("Dhcp6", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3480 "dhcp4_parser.cc"
    break;

  case 623:
#line 2139 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3488 "dhcp4_parser.cc"
    break;

  case 624:
#line 2141 "dhcp4_parser.yy"
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3497 "dhcp4_parser.cc"
    break;

  case 625:
#line 2146 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3505 "dhcp4_parser.cc"
    break;

  case 626:
#line 2148 "dhcp4_parser.yy"
    {
    ctx.stack_.back()->set("Control-agent", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3514 "dhcp4_parser.cc"
    break;

  case 627:
#line 2153 "dhcp4_parser.yy"
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 3525 "dhcp4_parser.cc"
    break;

  case 628:
#line 2158 "dhcp4_parser.yy"
    {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3535 "dhcp4_parser.cc"
    break;

  case 629:
#line 2164 "dhcp4_parser.yy"
    {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3545 "dhcp4_parser.cc"
    break;

  case 630:
#line 2168 "dhcp4_parser.yy"
    {
    // No config_control params are required
    // parsing completed
}
#line 3554 "dhcp4_parser.cc"
    break;

  case 635:
#line 2183 "dhcp4_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 3565 "dhcp4_parser.cc"
    break;

  case 636:
#line 2188 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3574 "dhcp4_parser.cc"
    break;

  case 637:
#line 2193 "dhcp4_parser.yy"
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-fetch-wait-time", value);
}
#line 3583 "dhcp4_parser.cc"
    break;

  case 638:
#line 2203 "dhcp4_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 3594 "dhcp4_parser.cc"
    break;

  case 639:
#line 2208 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3603 "dhcp4_parser.cc"
    break;

  case 640:
#line 2213 "dhcp4_parser.yy"
    {
    // Parse the Logging map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3613 "dhcp4_parser.cc"
    break;

  case 641:
#line 2217 "dhcp4_parser.yy"
    {
    // parsing completed
}
#line 3621 "dhcp4_parser.cc"
    break;

  case 645:
#line 2233 "dhcp4_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 3632 "dhcp4_parser.cc"
    break;

  case 646:
#line 2238 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3641 "dhcp4_parser.cc"
    break;

  case 649:
#line 2250 "dhcp4_parser.yy"
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 3651 "dhcp4_parser.cc"
    break;

  case 650:
#line 2254 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
}
#line 3659 "dhcp4_parser.cc"
    break;

  case 660:
#line 2271 "dhcp4_parser.yy"
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 3668 "dhcp4_parser.cc"
    break;

  case 661:
#line 2276 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3676 "dhcp4_parser.cc"
    break;

  case 662:
#line 2278 "dhcp4_parser.yy"
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 3686 "dhcp4_parser.cc"
    break;

  case 663:
#line 2284 "dhcp4_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 3697 "dhcp4_parser.cc"
    break;

  case 664:
#line 2289 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3706 "dhcp4_parser.cc"
    break;

  case 667:
#line 2298 "dhcp4_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3716 "dhcp4_parser.cc"
    break;

  case 668:
#line 2302 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
}
#line 3724 "dhcp4_parser.cc"
    break;

  case 676:
#line 2317 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3732 "dhcp4_parser.cc"
    break;

  case 677:
#line 2319 "dhcp4_parser.yy"
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 3742 "dhcp4_parser.cc"
    break;

  case 678:
#line 2325 "dhcp4_parser.yy"
    {
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 3751 "dhcp4_parser.cc"
    break;

  case 679:
#line 2330 "dhcp4_parser.yy"
    {
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 3760 "dhcp4_parser.cc"
    break;

  case 680:
#line 2335 "dhcp4_parser.yy"
    {
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 3769 "dhcp4_parser.cc"
    break;

  case 681:
#line 2340 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3777 "dhcp4_parser.cc"
    break;

  case 682:
#line 2342 "dhcp4_parser.yy"
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pattern", sev);
    ctx.leave();
}
#line 3787 "dhcp4_parser.cc"
    break;


#line 3791 "dhcp4_parser.cc"

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


  const short Dhcp4Parser::yypact_ninf_ = -832;

  const signed char Dhcp4Parser::yytable_ninf_ = -1;

  const short
  Dhcp4Parser::yypact_[] =
  {
     363,  -832,  -832,  -832,  -832,  -832,  -832,  -832,  -832,  -832,
    -832,  -832,  -832,  -832,  -832,    29,    21,    25,    53,   108,
     128,   135,   137,   160,   162,   171,   184,   199,   203,   228,
    -832,  -832,  -832,  -832,  -832,  -832,  -832,  -832,  -832,  -832,
    -832,  -832,  -832,  -832,  -832,  -832,  -832,  -832,  -832,  -832,
    -832,  -832,  -832,  -832,  -832,  -832,  -832,  -832,  -832,  -832,
    -832,  -832,  -832,  -832,  -832,  -832,  -832,  -832,    21,  -123,
      17,   122,    71,   226,   173,   233,    10,    41,   287,   -50,
     478,    89,   147,  -832,   254,   275,   225,   285,   296,  -832,
    -832,  -832,  -832,  -832,   304,  -832,    62,  -832,  -832,  -832,
    -832,  -832,  -832,  -832,  -832,  -832,   316,   317,   318,  -832,
    -832,  -832,  -832,  -832,  -832,   326,   327,   328,   352,   353,
     354,   377,   380,   384,  -832,  -832,  -832,  -832,  -832,  -832,
    -832,  -832,  -832,  -832,  -832,  -832,  -832,   392,  -832,  -832,
    -832,  -832,  -832,  -832,  -832,    68,  -832,  -832,  -832,  -832,
    -832,  -832,  -832,  -832,  -832,  -832,  -832,  -832,  -832,  -832,
    -832,  -832,  -832,  -832,  -832,  -832,  -832,  -832,  -832,  -832,
    -832,  -832,  -832,  -832,  -832,  -832,  -832,  -832,  -832,  -832,
    -832,  -832,  -832,  -832,  -832,  -832,  -832,  -832,  -832,  -832,
    -832,   395,  -832,    70,  -832,  -832,  -832,  -832,  -832,  -832,
    -832,  -832,  -832,  -832,  -832,  -832,  -832,   402,  -832,  -832,
    -832,  -832,  -832,  -832,  -832,  -832,  -832,  -832,  -832,  -832,
    -832,  -832,    80,  -832,  -832,  -832,  -832,  -832,  -832,  -832,
    -832,  -832,  -832,  -832,  -832,  -832,  -832,  -832,  -832,  -832,
    -832,  -832,  -832,  -832,  -832,  -832,  -832,    86,  -832,  -832,
    -832,  -832,  -832,  -832,  -832,  -832,  -832,  -832,  -832,  -832,
    -832,  -832,  -832,  -832,   292,   404,  -832,  -832,  -832,  -832,
    -832,  -832,  -832,  -832,  -832,  -832,  -832,  -832,   401,  -832,
    -832,   407,  -832,  -832,  -832,   408,  -832,  -832,   405,   412,
    -832,  -832,  -832,  -832,  -832,  -832,  -832,  -832,  -832,  -832,
    -832,  -832,  -832,   416,   417,  -832,  -832,  -832,  -832,   411,
     420,  -832,  -832,  -832,  -832,  -832,  -832,  -832,  -832,  -832,
    -832,  -832,  -832,   115,  -832,  -832,  -832,   425,  -832,  -832,
     434,  -832,   454,   455,  -832,  -832,   457,   460,  -832,  -832,
    -832,  -832,  -832,   116,  -832,  -832,  -832,  -832,  -832,  -832,
    -832,  -832,  -832,  -832,  -832,  -832,  -832,  -832,  -832,  -832,
     126,  -832,  -832,  -832,   461,   129,  -832,  -832,  -832,  -832,
      21,    21,  -832,   291,   463,   464,   466,   467,   477,  -832,
      17,  -832,   479,   480,   481,   308,   311,   312,   487,   488,
     489,   490,   491,   492,   321,   322,   323,   330,   331,   324,
     332,   333,   335,   500,   504,   509,   510,   512,   513,   514,
     515,   516,   517,   518,   535,   536,   366,   539,   541,   542,
     543,   544,   545,   122,  -832,   546,   547,   549,   376,    71,
    -832,   551,   552,   553,   554,   555,   556,   386,   561,   562,
     563,   226,  -832,   564,   173,  -832,   565,   567,   569,   570,
     572,   573,   575,   576,  -832,   233,  -832,   577,   579,   409,
     580,   582,   583,   410,  -832,    41,   585,   413,   414,  -832,
     287,   589,   590,    90,  -832,   418,   593,   594,   423,   596,
     426,   428,   614,   615,   442,   444,   622,   623,   478,  -832,
      89,  -832,   624,   453,   147,  -832,  -832,  -832,   626,   625,
     627,    21,    21,    21,  -832,   628,   629,   630,  -832,  -832,
    -832,   456,   458,   465,   631,   632,   636,  -832,  -832,  -832,
    -832,  -832,  -832,  -832,  -832,  -832,   468,   637,   639,   640,
     641,   642,   472,   276,   643,   645,   646,   647,   648,  -832,
     649,   642,   650,   483,   484,   655,  -832,   656,   274,   230,
    -832,  -832,   493,   494,   495,   657,   496,   497,  -832,   656,
     498,   658,  -832,   499,  -832,   656,   501,   502,   503,   505,
     506,   507,   508,  -832,   511,   519,  -832,   520,   521,   522,
    -832,  -832,   523,  -832,  -832,  -832,   524,    21,  -832,  -832,
     525,   526,  -832,   527,  -832,  -832,    26,   534,  -832,  -832,
      -4,   528,  -832,  -832,   659,  -832,  -832,    21,   122,    89,
    -832,  -832,  -832,   147,    71,   660,  -832,  -832,  -832,    57,
      57,   672,  -832,   678,   680,   681,   682,  -832,  -832,  -832,
    -832,  -832,  -832,  -832,  -832,   117,   683,   684,   685,   260,
     180,  -832,   478,  -832,  -832,   686,  -832,  -832,  -832,  -832,
    -832,  -832,  -832,  -832,  -832,  -832,  -832,   697,  -832,  -832,
    -832,  -832,   172,  -832,  -832,  -832,  -832,  -832,  -832,  -832,
    -832,  -832,  -832,  -832,  -832,  -832,  -832,  -832,  -832,  -832,
    -832,  -832,  -832,  -832,  -832,  -832,  -832,  -832,  -832,  -832,
    -832,  -832,  -832,  -832,   672,  -832,   165,   187,   197,   222,
    -832,   223,  -832,  -832,  -832,  -832,  -832,  -832,   662,   663,
     701,   702,   703,  -832,  -832,  -832,  -832,   704,   705,   706,
     707,   708,   709,  -832,   231,  -832,  -832,  -832,  -832,  -832,
    -832,  -832,  -832,  -832,  -832,  -832,  -832,  -832,  -832,  -832,
    -832,  -832,  -832,  -832,  -832,  -832,   234,  -832,   710,   651,
    -832,  -832,   711,   712,  -832,  -832,   713,   715,  -832,  -832,
     714,   718,  -832,  -832,   716,   720,  -832,  -832,  -832,  -832,
    -832,  -832,    45,  -832,  -832,  -832,  -832,  -832,  -832,  -832,
      74,  -832,  -832,   719,   721,  -832,  -832,   722,   723,  -832,
     725,   726,   727,   728,   729,   730,   264,  -832,  -832,  -832,
    -832,  -832,  -832,  -832,  -832,  -832,  -832,  -832,  -832,   271,
    -832,  -832,  -832,   272,  -832,   125,  -832,   560,  -832,   731,
     724,  -832,  -832,  -832,  -832,   732,   733,  -832,  -832,  -832,
    -832,   734,   660,  -832,   737,   738,   739,   740,   538,   485,
     571,   558,   574,   741,   742,   744,   745,   578,   581,   584,
     586,   587,   588,    57,  -832,  -832,    57,  -832,   672,   226,
    -832,   678,    41,  -832,   680,   287,  -832,   681,   415,  -832,
     682,   117,  -832,   142,   683,  -832,   233,  -832,   684,   -50,
    -832,   685,   591,   592,   595,   597,   598,   599,   260,  -832,
     747,   748,   180,  -832,  -832,   191,   686,  -832,  -832,   749,
     750,   173,  -832,   697,   752,  -832,  -832,   601,  -832,   356,
     602,   603,   604,  -832,  -832,  -832,  -832,  -832,   605,   606,
     607,   608,  -832,  -832,  -832,  -832,  -832,  -832,  -832,   298,
    -832,   299,  -832,   751,  -832,   753,  -832,  -832,  -832,  -832,
    -832,  -832,  -832,  -832,  -832,  -832,  -832,  -832,  -832,  -832,
    -832,  -832,  -832,  -832,   325,  -832,  -832,  -832,  -832,  -832,
    -832,  -832,  -832,  -832,  -832,  -832,   754,  -832,  -832,  -832,
    -832,  -832,  -832,  -832,  -832,  -832,   755,   763,  -832,  -832,
    -832,  -832,  -832,   761,  -832,   342,  -832,  -832,  -832,  -832,
    -832,  -832,  -832,  -832,   609,   610,  -832,  -832,   766,  -832,
    -832,  -832,  -832,  -832,   343,  -832,  -832,  -832,  -832,  -832,
    -832,   611,   344,  -832,   656,  -832,  -832,  -832,  -832,  -832,
    -832,  -832,  -832,  -832,  -832,  -832,  -832,  -832,  -832,  -832,
    -832,  -832,   415,  -832,   768,   612,  -832,   142,  -832,  -832,
    -832,  -832,   783,   618,   784,   191,  -832,  -832,  -832,  -832,
    -832,   616,  -832,  -832,   791,  -832,   644,  -832,  -832,   790,
    -832,  -832,   140,  -832,     7,   790,  -832,  -832,   798,   807,
     808,  -832,   346,  -832,  -832,  -832,  -832,  -832,  -832,  -832,
     813,   661,   652,   666,   832,     7,  -832,   670,  -832,  -832,
    -832,   673,  -832,  -832,  -832
  };

  const unsigned short
  Dhcp4Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,    28,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       1,    45,    38,    34,    33,    30,    31,    32,    37,     3,
      35,    36,    58,     5,    70,     7,   141,     9,   286,    11,
     451,    13,   476,    15,   376,    17,   384,    19,   421,    21,
     251,    23,   568,    25,   640,    27,   629,    29,    47,    41,
       0,     0,     0,     0,     0,   478,     0,   386,   423,     0,
       0,     0,     0,    49,     0,    48,     0,     0,    42,    68,
     638,   621,   623,   625,     0,    67,     0,    60,    62,    64,
      65,    66,    63,   627,   130,   156,     0,     0,     0,   497,
     499,   501,   154,   163,   165,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   125,   278,   374,   413,   340,   464,
     466,   333,   229,   525,   468,   243,   262,     0,   551,   564,
     566,   617,   619,   645,   115,     0,    72,    74,    75,    76,
      77,    78,   109,   110,   111,    79,   107,    96,    97,    98,
      82,    83,   104,    84,    85,    86,    90,    91,    80,   108,
      81,    88,    89,   102,   103,   105,    99,   100,   101,    87,
      92,    93,    94,    95,   113,   114,   106,   112,   143,   145,
     149,     0,   140,     0,   132,   134,   135,   136,   137,   138,
     139,   321,   323,   325,   443,   319,   327,     0,   331,   329,
     521,   318,   290,   291,   292,   293,   294,   315,   316,   317,
     305,   306,     0,   288,   297,   310,   311,   312,   298,   300,
     301,   303,   299,   295,   296,   313,   314,   302,   307,   308,
     309,   304,   462,   461,   457,   458,   456,     0,   453,   455,
     459,   460,   519,   507,   509,   513,   511,   517,   515,   503,
     496,   490,   494,   495,     0,   479,   480,   491,   492,   493,
     487,   482,   488,   484,   485,   486,   489,   483,     0,   403,
     209,     0,   407,   405,   410,     0,   399,   400,     0,   387,
     388,   390,   402,   391,   392,   393,   409,   394,   395,   396,
     397,   398,   437,     0,     0,   435,   436,   439,   440,     0,
     424,   425,   427,   428,   429,   430,   431,   432,   433,   434,
     258,   260,   255,     0,   253,   256,   257,     0,   591,   593,
       0,   596,     0,     0,   600,   604,     0,     0,   608,   615,
     589,   587,   588,     0,   570,   572,   573,   574,   575,   576,
     577,   578,   579,   580,   581,   582,   583,   584,   585,   586,
       0,   642,   644,   635,     0,     0,   631,   633,   634,    46,
       0,     0,    39,     0,     0,     0,     0,     0,     0,    57,
       0,    59,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    71,     0,     0,     0,     0,     0,
     142,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   287,     0,     0,   452,     0,     0,     0,     0,
       0,     0,     0,     0,   477,     0,   377,     0,     0,     0,
       0,     0,     0,     0,   385,     0,     0,     0,     0,   422,
       0,     0,     0,     0,   252,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   569,
       0,   641,     0,     0,     0,   630,    50,    43,     0,     0,
       0,     0,     0,     0,    61,     0,     0,     0,   127,   128,
     129,     0,     0,     0,     0,     0,     0,   116,   117,   118,
     119,   120,   121,   122,   123,   124,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   550,
       0,     0,     0,     0,     0,     0,    73,     0,     0,     0,
     153,   133,     0,     0,     0,     0,     0,     0,   339,     0,
       0,     0,   289,     0,   454,     0,     0,     0,     0,     0,
       0,     0,     0,   481,     0,     0,   401,     0,     0,     0,
     412,   389,     0,   441,   442,   426,     0,     0,   254,   590,
       0,     0,   595,     0,   598,   599,     0,     0,   606,   607,
       0,     0,   571,   643,     0,   637,   632,     0,     0,     0,
     622,   624,   626,     0,     0,     0,   498,   500,   502,     0,
       0,   167,   126,   280,   378,   415,   342,    40,   465,   467,
     335,   336,   337,   338,   334,     0,     0,   470,   245,     0,
       0,   565,     0,   618,   620,     0,    51,   144,   147,   148,
     146,   151,   152,   150,   322,   324,   326,   445,   320,   328,
     332,   330,     0,   463,   520,   508,   510,   514,   512,   518,
     516,   504,   404,   210,   408,   406,   411,   438,   259,   261,
     592,   594,   597,   602,   603,   601,   605,   610,   611,   612,
     613,   614,   609,   616,   167,    44,     0,     0,     0,     0,
     161,     0,   158,   160,   196,   202,   204,   206,     0,     0,
       0,     0,     0,   218,   220,   222,   224,     0,     0,     0,
       0,     0,     0,   195,     0,   173,   175,   176,   177,   178,
     179,   180,   181,   182,   183,   184,   188,   189,   190,   185,
     191,   192,   193,   186,   187,   194,     0,   171,     0,   168,
     169,   284,     0,   281,   282,   382,     0,   379,   380,   419,
       0,   416,   417,   346,     0,   343,   344,   238,   239,   240,
     241,   242,     0,   231,   233,   234,   235,   236,   237,   529,
       0,   527,   474,     0,   471,   472,   249,     0,   246,   247,
       0,     0,     0,     0,     0,     0,     0,   264,   266,   267,
     268,   269,   270,   271,   560,   562,   559,   557,   558,     0,
     553,   555,   556,     0,   649,     0,   647,    53,   449,     0,
     446,   447,   505,   523,   524,     0,     0,    69,   639,   628,
     131,     0,     0,   157,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   155,   164,     0,   166,     0,     0,
     279,     0,   386,   375,     0,   423,   414,     0,     0,   341,
       0,     0,   230,   531,     0,   526,   478,   469,     0,     0,
     244,     0,     0,     0,     0,     0,     0,     0,     0,   263,
       0,     0,     0,   552,   567,     0,     0,   646,    55,     0,
      54,     0,   444,     0,     0,   522,   636,     0,   159,     0,
       0,     0,     0,   208,   211,   212,   213,   214,     0,     0,
       0,     0,   226,   227,   215,   216,   217,   228,   174,     0,
     170,     0,   283,     0,   381,     0,   418,   373,   365,   366,
     367,   353,   354,   370,   371,   372,   356,   357,   350,   351,
     352,   363,   364,   362,     0,   348,   355,   368,   369,   358,
     359,   360,   361,   345,   232,   547,     0,   545,   546,   538,
     539,   543,   544,   540,   541,   542,     0,   532,   533,   535,
     536,   537,   528,     0,   473,     0,   248,   272,   273,   274,
     275,   276,   277,   265,     0,     0,   554,   663,     0,   661,
     659,   653,   657,   658,     0,   651,   655,   656,   654,   648,
      52,     0,     0,   448,     0,   162,   198,   199,   200,   201,
     197,   203,   205,   207,   219,   221,   223,   225,   172,   285,
     383,   420,     0,   347,     0,     0,   530,     0,   475,   250,
     561,   563,     0,     0,     0,     0,   650,    56,   450,   506,
     349,     0,   549,   534,     0,   660,     0,   652,   548,     0,
     662,   667,     0,   665,     0,     0,   664,   676,     0,     0,
       0,   681,     0,   669,   671,   672,   673,   674,   675,   666,
       0,     0,     0,     0,     0,     0,   668,     0,   678,   679,
     680,     0,   670,   677,   682
  };

  const short
  Dhcp4Parser::yypgoto_[] =
  {
    -832,  -832,  -832,  -832,  -832,  -832,  -832,  -832,  -832,  -832,
    -832,  -832,  -832,  -832,  -832,  -832,   -46,  -832,  -491,  -832,
     306,  -832,  -832,  -832,  -832,  -832,  -832,  -534,  -832,  -832,
    -832,   -70,  -832,  -832,  -832,   475,  -832,  -832,  -832,  -832,
     256,   462,   -55,   -54,   -27,   -24,    -9,     6,     9,    11,
    -832,  -832,  -832,  -832,    12,    19,  -832,  -832,   269,   459,
    -832,  -832,  -832,  -832,  -832,  -832,  -832,  -832,  -832,  -832,
    -832,  -832,  -832,  -832,  -832,  -832,    54,  -832,  -832,  -832,
    -832,  -832,  -832,   195,  -832,    33,  -832,  -607,    39,  -832,
    -832,  -832,  -832,  -832,  -832,  -832,  -832,  -832,  -832,   -35,
    -832,  -832,  -832,  -832,  -832,  -832,  -832,  -832,  -832,  -832,
    -832,  -832,  -832,  -832,  -832,  -832,  -832,  -832,  -832,  -832,
    -832,  -832,    24,  -832,  -832,  -832,  -832,  -832,  -832,  -832,
    -832,  -832,    16,  -832,  -832,  -832,    14,   427,  -832,  -832,
    -832,  -832,  -832,  -832,  -832,    13,  -832,  -832,  -832,  -832,
    -832,  -832,  -831,  -832,  -832,  -832,    37,  -832,  -832,  -832,
      40,   469,  -832,  -832,  -832,  -832,  -832,  -832,  -832,  -832,
    -823,  -832,   -17,  -832,    -5,  -832,    22,  -832,  -832,  -832,
    -832,  -832,  -832,  -832,    32,  -832,  -832,  -129,   -65,  -832,
    -832,  -832,  -832,  -832,    42,  -832,  -832,  -832,    43,  -832,
     439,  -832,   -72,  -832,  -832,  -832,  -832,  -832,   -66,  -832,
    -832,  -832,  -832,  -832,    -7,  -832,  -832,  -832,    44,  -832,
    -832,  -832,    47,  -832,   437,  -832,  -832,  -832,  -832,  -832,
    -832,  -832,  -832,  -832,  -832,  -832,     5,  -832,  -832,  -832,
       8,   470,  -832,  -832,   -39,  -832,   -19,  -832,   -59,  -832,
    -832,  -832,    35,  -832,  -832,  -832,    46,  -832,   471,   -58,
    -832,   -52,  -832,    -1,  -832,   253,  -832,  -832,  -832,  -832,
    -832,  -832,  -832,  -832,  -832,  -832,  -832,  -832,  -832,  -832,
    -832,  -832,  -832,  -821,  -832,  -832,  -832,  -832,  -832,    49,
    -832,  -832,  -832,  -121,  -832,  -832,  -832,  -832,  -832,  -832,
    -832,  -832,    27,  -832,  -832,  -832,  -832,  -832,  -832,  -832,
    -832,  -832,  -832,   278,   429,  -832,  -832,  -832,  -832,  -832,
    -832,  -832,  -832,  -832,  -832,  -832,  -832,  -832,  -832,  -832,
    -832,  -832,  -832,  -832,  -832,  -832,  -832,   -64,  -832,   -60,
    -832,  -832,  -832,  -832,  -832,  -832,  -832,  -832,  -832,  -832,
    -832,   305,   430,  -832,  -832,  -832,  -832,  -832,  -832,  -832,
     319,   431,   -57,  -832,  -832,    31,  -832,  -832,  -120,  -832,
    -832,  -832,  -832,  -832,  -832,  -136,  -832,  -832,  -155,  -832,
    -832,  -832,  -832,  -832,  -832,  -832
  };

  const short
  Dhcp4Parser::yydefgoto_[] =
  {
      -1,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    38,    39,    40,    69,
     628,    87,    88,    41,    68,    84,    85,   647,   817,   899,
     900,   723,    43,    70,    96,    97,    98,   374,    45,    71,
     145,   146,   147,   148,   149,   150,   151,   152,   153,   154,
     155,   156,   403,   157,   158,   159,   160,   383,   193,   194,
      47,    72,   195,   425,   196,   426,   650,   197,   427,   653,
     198,   161,   391,   162,   384,   701,   702,   703,   831,   163,
     392,   164,   393,   748,   749,   750,   856,   724,   725,   726,
     834,  1020,   727,   835,   728,   836,   729,   837,   730,   731,
     458,   732,   733,   734,   735,   736,   737,   738,   739,   843,
     740,   844,   741,   845,   742,   846,   743,   744,   745,   165,
     411,   772,   773,   774,   775,   776,   777,   778,   166,   414,
     787,   788,   789,   879,    61,    79,   323,   324,   325,   471,
     326,   472,   167,   415,   796,   797,   798,   799,   800,   801,
     802,   803,   168,   404,   752,   753,   754,   859,    49,    73,
     222,   223,   224,   435,   225,   431,   226,   432,   227,   433,
     228,   436,   229,   439,   230,   438,   169,   410,   634,   232,
     170,   407,   764,   765,   766,   868,   954,   955,   171,   405,
      55,    76,   756,   757,   758,   862,    57,    77,   288,   289,
     290,   291,   292,   293,   294,   457,   295,   461,   296,   460,
     297,   298,   462,   299,   172,   406,   760,   761,   762,   865,
      59,    78,   309,   310,   311,   312,   313,   466,   314,   315,
     316,   317,   234,   434,   819,   820,   821,   901,    51,    74,
     247,   248,   249,   443,   173,   408,   174,   409,   175,   413,
     783,   784,   785,   876,    53,    75,   264,   265,   266,   176,
     388,   177,   389,   178,   390,   270,   453,   824,   904,   271,
     447,   272,   448,   273,   450,   274,   449,   275,   452,   276,
     451,   277,   446,   241,   440,   825,   179,   412,   780,   781,
     873,   976,   977,   978,   979,   980,  1034,   981,   180,   181,
     417,   809,   810,   811,   890,   812,   891,   182,   418,   183,
     419,    63,    80,   343,   344,   345,   346,   476,   347,   477,
     348,   349,   479,   350,   351,   352,   482,   685,   353,   483,
     354,   355,   356,   486,   692,   357,   487,   184,   420,   185,
     421,    99,   376,   100,   377,   101,   378,   186,   382,    67,
      82,   365,   366,   367,   492,   368,   102,   375,    65,    81,
     360,   361,   187,   422,   815,   816,   895,  1004,  1005,  1006,
    1007,  1044,  1008,  1042,  1062,  1063,  1064,  1072,  1073,  1074,
    1080,  1075,  1076,  1077,  1078,  1084
  };

  const unsigned short
  Dhcp4Parser::yytable_[] =
  {
      95,   144,   192,   211,   243,   260,   307,   286,   305,   322,
     340,   278,   308,   746,   237,   238,   358,   267,   212,   213,
     359,   239,    83,   268,   362,   660,    31,    89,    32,    30,
      33,   664,    42,   199,   235,   250,   262,   949,   300,   318,
     627,   341,   287,   306,   683,   950,   214,   962,   871,   215,
     627,   872,    86,   200,   236,   251,   263,   244,   301,   319,
      44,   342,   320,   321,   216,   380,   233,   246,   261,   245,
     381,   423,   240,   429,   269,   279,   424,   874,   430,   217,
     875,   126,   218,   441,   219,   220,   188,   189,   442,   444,
     190,   704,   221,   191,   445,   231,   705,   706,   707,   708,
     709,   710,   711,   712,   713,   714,   715,   716,   717,   718,
     719,   720,   721,   722,   280,    46,   281,   282,   473,   488,
     283,   284,   285,   474,   489,    94,   129,   130,   896,   490,
     280,   897,   494,   103,   491,    48,   104,   495,   687,   688,
     689,   690,    50,  1065,    52,   105,  1066,   106,   107,   108,
     109,   110,   111,   112,   113,   114,   129,   130,  1067,   363,
     364,  1068,  1069,  1070,  1071,    90,   684,    54,   423,    56,
     109,   110,   111,   827,   691,    91,    92,    93,    58,   115,
     116,   117,   118,   119,   120,   121,   122,   123,   124,   125,
     490,    60,    94,   126,   127,   828,    34,    35,    36,    37,
     494,   949,   320,   321,   128,   829,    62,   129,   130,   950,
      64,   962,   131,   126,   127,   280,    94,   132,   133,   767,
     768,   769,   770,   134,   771,   429,   832,   129,   130,   371,
     830,   833,    94,   135,   853,    66,   136,   853,   143,   854,
     965,   966,   855,   137,   138,   127,    94,   139,   140,   929,
     651,   652,   107,   108,   109,   110,   111,   242,   129,   130,
     369,   109,   110,   111,   280,   129,   130,   888,   141,   142,
     208,   143,   889,   209,   892,   488,   129,   130,   370,   893,
     894,   259,   822,   115,   116,   117,   118,   119,   120,   121,
     122,   648,   649,   372,   201,   202,   203,    94,   127,   373,
     454,   853,   441,   804,   805,   127,  1028,  1029,   379,   204,
      95,   129,   130,   205,   206,   207,   131,    94,   129,   130,
     385,   386,   387,   208,   496,   497,   209,   134,  1032,   252,
     394,   395,   396,  1033,   210,   253,   254,   255,   256,   257,
     258,   997,   259,   998,   999,   473,  1045,   444,    94,  1085,
    1039,  1046,  1048,   144,  1086,    94,   397,   398,   399,   192,
     280,   302,   281,   282,   303,   304,    94,   630,   631,   632,
     633,   211,   129,   130,   243,   790,   791,   792,   793,   794,
     795,   400,   237,   238,   401,   260,   212,   213,   402,   239,
     199,  1016,  1017,  1018,  1019,   286,   416,   267,   307,   428,
     305,    94,   235,   268,   308,   250,   437,   455,    94,   456,
     200,   459,   463,   464,   214,   465,   262,   215,   340,   469,
     467,   468,   236,   470,   358,   251,   300,   244,   359,   475,
     287,   318,   216,   362,   233,   306,   263,   246,   478,   245,
     240,   107,   108,   109,   110,   111,   301,   217,   261,   341,
     218,   319,   219,   220,   269,   610,   611,   612,   480,   481,
     221,   484,    94,   231,   485,   493,   498,   499,   500,   342,
     501,   502,   115,   116,   117,   118,   119,   120,   121,   122,
    1049,   503,   125,   505,   506,   507,   508,   127,   280,   509,
     510,   511,   512,   513,   514,   515,   516,   517,   518,   519,
     129,   130,   522,   206,   526,   131,   520,   521,   527,   523,
     524,   525,   208,   528,   529,   209,   530,   531,   532,   533,
     534,   535,   536,   210,     1,     2,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,   144,   537,
     538,   679,   539,   540,   192,   541,   542,   543,   544,   545,
     547,   548,   362,   549,   550,   552,   553,   554,   555,   556,
     557,   695,   558,   129,   130,   559,   560,   561,   563,   565,
     806,   566,   340,   567,   568,   199,   569,   570,   358,   571,
     572,   574,   359,   575,   577,   576,   578,   579,   580,   582,
      94,   583,   584,   586,   587,   200,   589,   590,   591,   592,
     593,   807,   594,   341,   595,   327,   328,   329,   330,   331,
     332,   333,   334,   335,   336,   337,   338,   339,   596,   597,
     598,   808,   599,   342,   141,   142,   600,   601,   604,   605,
     607,   616,   608,   617,   609,   613,   614,   615,   619,   620,
     618,   621,   623,   622,   624,   625,   626,   629,   635,    32,
     636,   637,   638,    94,   858,   639,   640,   642,   643,   644,
     645,   646,   657,   914,   694,   662,   838,   839,   654,   655,
     656,   658,   659,   661,   663,   686,   665,   666,   667,   747,
     668,   669,   670,   671,   700,   751,   672,   755,   759,   763,
     779,   782,   786,   814,   673,   674,   675,   676,   677,   678,
     680,   681,   682,   693,   818,   840,   841,   842,   847,   848,
     849,   850,   851,   852,   913,   861,   857,   860,   864,   863,
     866,   867,   869,   870,   878,   877,   881,   903,   880,   882,
     883,   884,   885,   886,   887,   898,   916,   902,   907,   906,
     905,   909,   910,   911,   912,   918,   919,   915,   920,   921,
     917,   994,   995,  1011,   922,  1010,  1014,   923,  1035,  1030,
     924,  1031,   925,  1036,   927,   926,  1037,   987,   988,  1038,
    1043,   989,  1051,   990,   991,   992,  1015,  1021,  1022,  1023,
    1024,  1025,  1026,  1027,  1040,  1041,  1047,  1054,  1056,   211,
    1052,  1058,   286,   307,  1055,   305,  1059,  1061,   937,   308,
     237,   238,  1081,   967,   212,   213,   260,   239,   969,   322,
     959,  1082,  1083,   938,   939,   973,   960,  1087,   267,  1060,
     235,   974,   806,   300,   268,  1000,   318,   287,  1089,   957,
     306,   243,   214,   948,   971,   215,  1091,   262,   968,  1088,
     236,   940,  1090,   301,   941,  1093,   319,   641,  1094,   958,
     216,   951,   233,   807,   972,   504,  1002,   263,   240,   942,
    1001,   956,   250,   952,   696,   217,   970,   961,   218,   261,
     219,   220,   975,   808,   943,   269,  1003,   944,   221,   945,
     946,   231,   251,   699,   244,   546,   908,   947,   551,   826,
     953,   930,   928,   985,   246,   964,   245,   986,   932,   931,
     588,   993,   963,  1050,   581,   933,   934,   585,  1013,  1012,
     562,   936,   935,   984,   564,   823,  1053,   602,   698,   996,
     813,   603,   983,   982,   606,  1057,   573,  1009,   697,  1079,
    1092,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   937,     0,     0,     0,     0,   967,     0,     0,
       0,     0,   969,     0,   959,  1000,     0,   938,   939,   973,
     960,     0,     0,     0,     0,   974,     0,     0,     0,     0,
       0,     0,     0,   957,     0,     0,     0,   948,   971,     0,
       0,     0,   968,     0,     0,   940,  1002,     0,   941,     0,
    1001,     0,     0,   958,     0,   951,     0,     0,   972,     0,
       0,     0,     0,   942,     0,   956,  1003,   952,     0,     0,
     970,   961,     0,     0,     0,     0,   975,     0,   943,     0,
       0,   944,     0,   945,   946,     0,     0,     0,     0,     0,
       0,   947,     0,     0,   953
  };

  const short
  Dhcp4Parser::yycheck_[] =
  {
      70,    71,    72,    73,    74,    75,    78,    77,    78,    79,
      80,    76,    78,   620,    73,    73,    80,    75,    73,    73,
      80,    73,    68,    75,    81,   559,     5,    10,     7,     0,
       9,   565,     7,    72,    73,    74,    75,   868,    77,    78,
     531,    80,    77,    78,    18,   868,    73,   868,     3,    73,
     541,     6,   175,    72,    73,    74,    75,    74,    77,    78,
       7,    80,   112,   113,    73,     3,    73,    74,    75,    74,
       8,     3,    73,     3,    75,    34,     8,     3,     8,    73,
       6,    71,    73,     3,    73,    73,    15,    16,     8,     3,
      19,    34,    73,    22,     8,    73,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    51,    52,
      53,    54,    55,    56,    73,     7,    75,    76,     3,     3,
      79,    80,    81,     8,     8,   175,    85,    86,     3,     3,
      73,     6,     3,    11,     8,     7,    14,     8,   142,   143,
     144,   145,     7,     3,     7,    23,     6,    25,    26,    27,
      28,    29,    30,    31,    32,    33,    85,    86,   151,    12,
      13,   154,   155,   156,   157,   148,   140,     7,     3,     7,
      28,    29,    30,     8,   178,   158,   159,   160,     7,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
       3,     7,   175,    71,    72,     8,   175,   176,   177,   178,
       3,  1032,   112,   113,    82,     8,     7,    85,    86,  1032,
       7,  1032,    90,    71,    72,    73,   175,    95,    96,   102,
     103,   104,   105,   101,   107,     3,     3,    85,    86,     4,
       8,     8,   175,   111,     3,     7,   114,     3,   149,     8,
      98,    99,     8,   121,   122,    72,   175,   125,   126,   856,
      20,    21,    26,    27,    28,    29,    30,    84,    85,    86,
       6,    28,    29,    30,    73,    85,    86,     3,   146,   147,
      97,   149,     8,   100,     3,     3,    85,    86,     3,     8,
       8,   109,   110,    57,    58,    59,    60,    61,    62,    63,
      64,    17,    18,     8,    68,    69,    70,   175,    72,     3,
       8,     3,     3,   123,   124,    72,     8,     8,     4,    83,
     380,    85,    86,    87,    88,    89,    90,   175,    85,    86,
       4,     4,     4,    97,   370,   371,   100,   101,     3,    96,
       4,     4,     4,     8,   108,   102,   103,   104,   105,   106,
     107,   150,   109,   152,   153,     3,     3,     3,   175,     3,
       8,     8,     8,   423,     8,   175,     4,     4,     4,   429,
      73,    74,    75,    76,    77,    78,   175,    91,    92,    93,
      94,   441,    85,    86,   444,   115,   116,   117,   118,   119,
     120,     4,   441,   441,     4,   455,   441,   441,     4,   441,
     429,    35,    36,    37,    38,   465,     4,   455,   470,     4,
     470,   175,   441,   455,   470,   444,     4,     3,   175,     8,
     429,     4,     4,     8,   441,     3,   455,   441,   488,     8,
       4,     4,   441,     3,   488,   444,   465,   444,   488,     4,
     465,   470,   441,   490,   441,   470,   455,   444,     4,   444,
     441,    26,    27,    28,    29,    30,   465,   441,   455,   488,
     441,   470,   441,   441,   455,   501,   502,   503,     4,     4,
     441,     4,   175,   441,     4,     4,   175,     4,     4,   488,
       4,     4,    57,    58,    59,    60,    61,    62,    63,    64,
    1014,     4,    67,     4,     4,     4,   178,    72,    73,   178,
     178,     4,     4,     4,     4,     4,     4,   176,   176,   176,
      85,    86,   178,    88,     4,    90,   176,   176,     4,   177,
     177,   176,    97,     4,     4,   100,     4,     4,     4,     4,
       4,     4,     4,   108,   161,   162,   163,   164,   165,   166,
     167,   168,   169,   170,   171,   172,   173,   174,   608,     4,
       4,   587,   176,     4,   614,     4,     4,     4,     4,     4,
       4,     4,   609,     4,   178,     4,     4,     4,     4,     4,
       4,   607,   176,    85,    86,     4,     4,     4,     4,     4,
     640,     4,   642,     4,     4,   614,     4,     4,   642,     4,
       4,     4,   642,     4,     4,   176,     4,     4,   178,     4,
     175,   178,   178,     4,     4,   614,   178,     4,     4,   176,
       4,   640,   176,   642,   176,   127,   128,   129,   130,   131,
     132,   133,   134,   135,   136,   137,   138,   139,     4,     4,
     178,   640,   178,   642,   146,   147,     4,     4,     4,   176,
       4,   175,     7,   175,     7,     7,     7,     7,     7,     7,
     175,     5,     5,   175,     5,     5,     5,   175,     5,     7,
       5,     5,     5,   175,     3,     7,     7,     7,   175,   175,
       5,     5,     5,   178,     5,     7,     4,     4,   175,   175,
     175,   175,   175,   175,   175,   141,   175,   175,   175,     7,
     175,   175,   175,   175,    24,     7,   175,     7,     7,     7,
       7,     7,     7,     7,   175,   175,   175,   175,   175,   175,
     175,   175,   175,   175,     7,     4,     4,     4,     4,     4,
       4,     4,     4,     4,   176,     3,     6,     6,     3,     6,
       6,     3,     6,     3,     3,     6,     3,     3,     6,     4,
       4,     4,     4,     4,     4,   175,   178,     6,     4,     6,
       8,     4,     4,     4,     4,     4,     4,   176,     4,     4,
     176,     4,     4,     3,   176,     6,     4,   176,     4,     8,
     176,     8,   176,     8,   176,   178,     3,   176,   176,     8,
       4,   176,     4,   176,   176,   176,   175,   175,   175,   175,
     175,   175,   175,   175,   175,   175,   175,     4,     4,   859,
     178,   175,   862,   865,   176,   865,     5,     7,   868,   865,
     859,   859,     4,   873,   859,   859,   876,   859,   873,   879,
     868,     4,     4,   868,   868,   873,   868,     4,   876,   175,
     859,   873,   892,   862,   876,   895,   865,   862,   176,   868,
     865,   901,   859,   868,   873,   859,     4,   876,   873,   178,
     859,   868,   176,   862,   868,   175,   865,   541,   175,   868,
     859,   868,   859,   892,   873,   380,   895,   876,   859,   868,
     895,   868,   901,   868,   608,   859,   873,   868,   859,   876,
     859,   859,   873,   892,   868,   876,   895,   868,   859,   868,
     868,   859,   901,   614,   901,   423,   832,   868,   429,   694,
     868,   858,   853,   879,   901,   871,   901,   881,   861,   859,
     473,   888,   870,  1032,   465,   862,   864,   470,   903,   901,
     441,   867,   865,   878,   444,   662,  1037,   488,   613,   892,
     642,   490,   876,   874,   494,  1045,   455,   896,   609,  1065,
    1085,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,  1032,    -1,    -1,    -1,    -1,  1037,    -1,    -1,
      -1,    -1,  1037,    -1,  1032,  1045,    -1,  1032,  1032,  1037,
    1032,    -1,    -1,    -1,    -1,  1037,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,  1032,    -1,    -1,    -1,  1032,  1037,    -1,
      -1,    -1,  1037,    -1,    -1,  1032,  1045,    -1,  1032,    -1,
    1045,    -1,    -1,  1032,    -1,  1032,    -1,    -1,  1037,    -1,
      -1,    -1,    -1,  1032,    -1,  1032,  1045,  1032,    -1,    -1,
    1037,  1032,    -1,    -1,    -1,    -1,  1037,    -1,  1032,    -1,
      -1,  1032,    -1,  1032,  1032,    -1,    -1,    -1,    -1,    -1,
      -1,  1032,    -1,    -1,  1032
  };

  const unsigned short
  Dhcp4Parser::yystos_[] =
  {
       0,   161,   162,   163,   164,   165,   166,   167,   168,   169,
     170,   171,   172,   173,   174,   180,   181,   182,   183,   184,
     185,   186,   187,   188,   189,   190,   191,   192,   193,   194,
       0,     5,     7,     9,   175,   176,   177,   178,   195,   196,
     197,   202,     7,   211,     7,   217,     7,   239,     7,   337,
       7,   417,     7,   433,     7,   369,     7,   375,     7,   399,
       7,   313,     7,   490,     7,   537,     7,   528,   203,   198,
     212,   218,   240,   338,   418,   434,   370,   376,   400,   314,
     491,   538,   529,   195,   204,   205,   175,   200,   201,    10,
     148,   158,   159,   160,   175,   210,   213,   214,   215,   520,
     522,   524,   535,    11,    14,    23,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    71,    72,    82,    85,
      86,    90,    95,    96,   101,   111,   114,   121,   122,   125,
     126,   146,   147,   149,   210,   219,   220,   221,   222,   223,
     224,   225,   226,   227,   228,   229,   230,   232,   233,   234,
     235,   250,   252,   258,   260,   298,   307,   321,   331,   355,
     359,   367,   393,   423,   425,   427,   438,   440,   442,   465,
     477,   478,   486,   488,   516,   518,   526,   541,    15,    16,
      19,    22,   210,   237,   238,   241,   243,   246,   249,   423,
     425,    68,    69,    70,    83,    87,    88,    89,    97,   100,
     108,   210,   221,   222,   223,   224,   225,   226,   227,   228,
     233,   234,   339,   340,   341,   343,   345,   347,   349,   351,
     353,   355,   358,   393,   411,   423,   425,   427,   438,   440,
     442,   462,    84,   210,   351,   353,   393,   419,   420,   421,
     423,   425,    96,   102,   103,   104,   105,   106,   107,   109,
     210,   393,   423,   425,   435,   436,   437,   438,   440,   442,
     444,   448,   450,   452,   454,   456,   458,   460,   367,    34,
      73,    75,    76,    79,    80,    81,   210,   278,   377,   378,
     379,   380,   381,   382,   383,   385,   387,   389,   390,   392,
     423,   425,    74,    77,    78,   210,   278,   381,   387,   401,
     402,   403,   404,   405,   407,   408,   409,   410,   423,   425,
     112,   113,   210,   315,   316,   317,   319,   127,   128,   129,
     130,   131,   132,   133,   134,   135,   136,   137,   138,   139,
     210,   423,   425,   492,   493,   494,   495,   497,   499,   500,
     502,   503,   504,   507,   509,   510,   511,   514,   516,   518,
     539,   540,   541,    12,    13,   530,   531,   532,   534,     6,
       3,     4,     8,     3,   216,   536,   521,   523,   525,     4,
       3,     8,   527,   236,   253,     4,     4,     4,   439,   441,
     443,   251,   259,   261,     4,     4,     4,     4,     4,     4,
       4,     4,     4,   231,   332,   368,   394,   360,   424,   426,
     356,   299,   466,   428,   308,   322,     4,   479,   487,   489,
     517,   519,   542,     3,     8,   242,   244,   247,     4,     3,
       8,   344,   346,   348,   412,   342,   350,     4,   354,   352,
     463,     3,     8,   422,     3,     8,   461,   449,   451,   455,
     453,   459,   457,   445,     8,     3,     8,   384,   279,     4,
     388,   386,   391,     4,     8,     3,   406,     4,     4,     8,
       3,   318,   320,     3,     8,     4,   496,   498,     4,   501,
       4,     4,   505,   508,     4,     4,   512,   515,     3,     8,
       3,     8,   533,     4,     3,     8,   195,   195,   175,     4,
       4,     4,     4,     4,   214,     4,     4,     4,   178,   178,
     178,     4,     4,     4,     4,     4,     4,   176,   176,   176,
     176,   176,   178,   177,   177,   176,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,   176,
       4,     4,     4,     4,     4,     4,   220,     4,     4,     4,
     178,   238,     4,     4,     4,     4,     4,     4,   176,     4,
       4,     4,   340,     4,   420,     4,     4,     4,     4,     4,
       4,     4,     4,   437,     4,     4,   176,     4,     4,     4,
     178,   379,     4,   178,   178,   403,     4,     4,   316,   178,
       4,     4,   176,     4,   176,   176,     4,     4,   178,   178,
       4,     4,   493,   540,     4,   176,   531,     4,     7,     7,
     195,   195,   195,     7,     7,     7,   175,   175,   175,     7,
       7,     5,   175,     5,     5,     5,     5,   197,   199,   175,
      91,    92,    93,    94,   357,     5,     5,     5,     5,     7,
       7,   199,     7,   175,   175,     5,     5,   206,    17,    18,
     245,    20,    21,   248,   175,   175,   175,     5,   175,   175,
     206,   175,     7,   175,   206,   175,   175,   175,   175,   175,
     175,   175,   175,   175,   175,   175,   175,   175,   175,   195,
     175,   175,   175,    18,   140,   506,   141,   142,   143,   144,
     145,   178,   513,   175,     5,   195,   219,   539,   530,   237,
      24,   254,   255,   256,    34,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,    56,   210,   266,   267,   268,   271,   273,   275,
     277,   278,   280,   281,   282,   283,   284,   285,   286,   287,
     289,   291,   293,   295,   296,   297,   266,     7,   262,   263,
     264,     7,   333,   334,   335,     7,   371,   372,   373,     7,
     395,   396,   397,     7,   361,   362,   363,   102,   103,   104,
     105,   107,   300,   301,   302,   303,   304,   305,   306,     7,
     467,   468,     7,   429,   430,   431,     7,   309,   310,   311,
     115,   116,   117,   118,   119,   120,   323,   324,   325,   326,
     327,   328,   329,   330,   123,   124,   210,   423,   425,   480,
     481,   482,   484,   492,     7,   543,   544,   207,     7,   413,
     414,   415,   110,   444,   446,   464,   262,     8,     8,     8,
       8,   257,     3,     8,   269,   272,   274,   276,     4,     4,
       4,     4,     4,   288,   290,   292,   294,     4,     4,     4,
       4,     4,     4,     3,     8,     8,   265,     6,     3,   336,
       6,     3,   374,     6,     3,   398,     6,     3,   364,     6,
       3,     3,     6,   469,     3,     6,   432,     6,     3,   312,
       6,     3,     4,     4,     4,     4,     4,     4,     3,     8,
     483,   485,     3,     8,     8,   545,     3,     6,   175,   208,
     209,   416,     6,     3,   447,     8,     6,     4,   255,     4,
       4,     4,     4,   176,   178,   176,   178,   176,     4,     4,
       4,     4,   176,   176,   176,   176,   178,   176,   267,   266,
     264,   339,   335,   377,   373,   401,   397,   210,   221,   222,
     223,   224,   225,   226,   227,   228,   233,   234,   278,   331,
     349,   351,   353,   355,   365,   366,   393,   423,   425,   438,
     440,   442,   462,   363,   301,    98,    99,   210,   278,   367,
     393,   423,   425,   438,   440,   442,   470,   471,   472,   473,
     474,   476,   468,   435,   431,   315,   311,   176,   176,   176,
     176,   176,   176,   324,     4,     4,   481,   150,   152,   153,
     210,   278,   423,   425,   546,   547,   548,   549,   551,   544,
       6,     3,   419,   415,     4,   175,    35,    36,    37,    38,
     270,   175,   175,   175,   175,   175,   175,   175,     8,     8,
       8,     8,     3,     8,   475,     4,     8,     3,     8,     8,
     175,   175,   552,     4,   550,     3,     8,   175,     8,   206,
     366,     4,   178,   472,     4,   176,     4,   547,   175,     5,
     175,     7,   553,   554,   555,     3,     6,   151,   154,   155,
     156,   157,   556,   557,   558,   560,   561,   562,   563,   554,
     559,     4,     4,     4,   564,     3,     8,     4,   178,   176,
     176,     4,   557,   175,   175
  };

  const unsigned short
  Dhcp4Parser::yyr1_[] =
  {
       0,   179,   181,   180,   182,   180,   183,   180,   184,   180,
     185,   180,   186,   180,   187,   180,   188,   180,   189,   180,
     190,   180,   191,   180,   192,   180,   193,   180,   194,   180,
     195,   195,   195,   195,   195,   195,   195,   196,   198,   197,
     199,   200,   200,   201,   201,   203,   202,   204,   204,   205,
     205,   207,   206,   208,   208,   209,   209,   210,   212,   211,
     213,   213,   214,   214,   214,   214,   214,   214,   216,   215,
     218,   217,   219,   219,   220,   220,   220,   220,   220,   220,
     220,   220,   220,   220,   220,   220,   220,   220,   220,   220,
     220,   220,   220,   220,   220,   220,   220,   220,   220,   220,
     220,   220,   220,   220,   220,   220,   220,   220,   220,   220,
     220,   220,   220,   220,   220,   220,   221,   222,   223,   224,
     225,   226,   227,   228,   229,   231,   230,   232,   233,   234,
     236,   235,   237,   237,   238,   238,   238,   238,   238,   238,
     238,   240,   239,   242,   241,   244,   243,   245,   245,   247,
     246,   248,   248,   249,   251,   250,   253,   252,   254,   254,
     255,   257,   256,   259,   258,   261,   260,   262,   262,   263,
     263,   265,   264,   266,   266,   267,   267,   267,   267,   267,
     267,   267,   267,   267,   267,   267,   267,   267,   267,   267,
     267,   267,   267,   267,   267,   267,   269,   268,   270,   270,
     270,   270,   272,   271,   274,   273,   276,   275,   277,   279,
     278,   280,   281,   282,   283,   284,   285,   286,   288,   287,
     290,   289,   292,   291,   294,   293,   295,   296,   297,   299,
     298,   300,   300,   301,   301,   301,   301,   301,   302,   303,
     304,   305,   306,   308,   307,   309,   309,   310,   310,   312,
     311,   314,   313,   315,   315,   315,   316,   316,   318,   317,
     320,   319,   322,   321,   323,   323,   324,   324,   324,   324,
     324,   324,   325,   326,   327,   328,   329,   330,   332,   331,
     333,   333,   334,   334,   336,   335,   338,   337,   339,   339,
     340,   340,   340,   340,   340,   340,   340,   340,   340,   340,
     340,   340,   340,   340,   340,   340,   340,   340,   340,   340,
     340,   340,   340,   340,   340,   340,   340,   340,   340,   342,
     341,   344,   343,   346,   345,   348,   347,   350,   349,   352,
     351,   354,   353,   356,   355,   357,   357,   357,   357,   358,
     360,   359,   361,   361,   362,   362,   364,   363,   365,   365,
     366,   366,   366,   366,   366,   366,   366,   366,   366,   366,
     366,   366,   366,   366,   366,   366,   366,   366,   366,   366,
     366,   366,   366,   366,   368,   367,   370,   369,   371,   371,
     372,   372,   374,   373,   376,   375,   377,   377,   378,   378,
     379,   379,   379,   379,   379,   379,   379,   379,   379,   379,
     380,   381,   382,   384,   383,   386,   385,   388,   387,   389,
     391,   390,   392,   394,   393,   395,   395,   396,   396,   398,
     397,   400,   399,   401,   401,   402,   402,   403,   403,   403,
     403,   403,   403,   403,   403,   403,   404,   406,   405,   407,
     408,   409,   410,   412,   411,   413,   413,   414,   414,   416,
     415,   418,   417,   419,   419,   420,   420,   420,   420,   420,
     420,   420,   422,   421,   424,   423,   426,   425,   428,   427,
     429,   429,   430,   430,   432,   431,   434,   433,   435,   435,
     436,   436,   437,   437,   437,   437,   437,   437,   437,   437,
     437,   437,   437,   437,   437,   437,   437,   439,   438,   441,
     440,   443,   442,   445,   444,   447,   446,   449,   448,   451,
     450,   453,   452,   455,   454,   457,   456,   459,   458,   461,
     460,   463,   462,   464,   464,   466,   465,   467,   467,   469,
     468,   470,   470,   471,   471,   472,   472,   472,   472,   472,
     472,   472,   472,   472,   472,   472,   473,   475,   474,   476,
     477,   479,   478,   480,   480,   481,   481,   481,   481,   481,
     483,   482,   485,   484,   487,   486,   489,   488,   491,   490,
     492,   492,   493,   493,   493,   493,   493,   493,   493,   493,
     493,   493,   493,   493,   493,   493,   493,   493,   493,   493,
     494,   496,   495,   498,   497,   499,   501,   500,   502,   503,
     505,   504,   506,   506,   508,   507,   509,   510,   512,   511,
     513,   513,   513,   513,   513,   515,   514,   517,   516,   519,
     518,   521,   520,   523,   522,   525,   524,   527,   526,   529,
     528,   530,   530,   531,   531,   533,   532,   534,   536,   535,
     538,   537,   539,   539,   540,   542,   541,   543,   543,   545,
     544,   546,   546,   547,   547,   547,   547,   547,   547,   547,
     548,   550,   549,   552,   551,   553,   553,   555,   554,   556,
     556,   557,   557,   557,   557,   557,   559,   558,   560,   561,
     562,   564,   563
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
       1,     1,     1,     1,     1,     1,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     0,     4,     3,     3,     3,
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
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     1,     1,     1,     1,     3,
       0,     6,     0,     1,     1,     3,     0,     4,     1,     3,
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
       0,     1,     1,     3,     0,     4,     0,     4,     0,     1,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     6,     1,     1,     0,     6,     1,     3,     0,
       4,     0,     1,     1,     3,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     3,
       3,     0,     6,     1,     3,     1,     1,     1,     1,     1,
       0,     4,     0,     4,     0,     4,     0,     6,     0,     4,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       3,     0,     4,     0,     4,     3,     0,     4,     3,     3,
       0,     4,     1,     1,     0,     4,     3,     3,     0,     4,
       1,     1,     1,     1,     1,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     6,     0,
       4,     1,     3,     1,     1,     0,     6,     3,     0,     6,
       0,     4,     1,     3,     1,     0,     6,     1,     3,     0,
       4,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       3,     0,     4,     0,     6,     1,     3,     0,     4,     1,
       3,     1,     1,     1,     1,     1,     0,     4,     3,     3,
       3,     0,     4
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
  "\"subnet4\"", "\"4o6-interface\"", "\"4o6-interface-id\"",
  "\"4o6-subnet\"", "\"option-def\"", "\"option-data\"", "\"name\"",
  "\"data\"", "\"code\"", "\"space\"", "\"csv-format\"", "\"always-send\"",
  "\"record-types\"", "\"encapsulate\"", "\"array\"",
  "\"shared-networks\"", "\"pools\"", "\"pool\"", "\"user-context\"",
  "\"comment\"", "\"subnet\"", "\"interface\"", "\"id\"",
  "\"reservation-mode\"", "\"disabled\"", "\"out-of-pool\"", "\"global\"",
  "\"all\"", "\"host-reservation-identifiers\"", "\"client-classes\"",
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
  "rebind_timer", "calculate_tee_times", "t1_percent", "t2_percent",
  "decline_probation_period", "server_tag", "$@21", "echo_client_id",
  "match_client_id", "authoritative", "interfaces_config", "$@22",
  "interfaces_config_params", "interfaces_config_param", "sub_interfaces4",
  "$@23", "interfaces_list", "$@24", "dhcp_socket_type", "$@25",
  "socket_type", "outbound_interface", "$@26", "outbound_interface_value",
  "re_detect", "lease_database", "$@27", "sanity_checks", "$@28",
  "sanity_checks_params", "sanity_checks_param", "lease_checks", "$@29",
  "hosts_database", "$@30", "hosts_databases", "$@31", "database_list",
  "not_empty_database_list", "database", "$@32", "database_map_params",
  "database_map_param", "database_type", "$@33", "db_type", "user", "$@34",
  "password", "$@35", "host", "$@36", "port", "name", "$@37", "persist",
  "lfc_interval", "readonly", "connect_timeout", "request_timeout",
  "tcp_keepalive", "tcp_nodelay", "contact_points", "$@38", "keyspace",
  "$@39", "consistency", "$@40", "serial_consistency", "$@41",
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
       0,   266,   266,   266,   267,   267,   268,   268,   269,   269,
     270,   270,   271,   271,   272,   272,   273,   273,   274,   274,
     275,   275,   276,   276,   277,   277,   278,   278,   279,   279,
     287,   288,   289,   290,   291,   292,   293,   296,   301,   301,
     312,   315,   316,   319,   323,   330,   330,   337,   338,   341,
     345,   352,   352,   359,   360,   363,   367,   378,   388,   388,
     404,   405,   409,   410,   411,   412,   413,   414,   417,   417,
     432,   432,   441,   442,   447,   448,   449,   450,   451,   452,
     453,   454,   455,   456,   457,   458,   459,   460,   461,   462,
     463,   464,   465,   466,   467,   468,   469,   470,   471,   472,
     473,   474,   475,   476,   477,   478,   479,   480,   481,   482,
     483,   484,   485,   486,   487,   488,   491,   496,   501,   506,
     511,   516,   521,   526,   531,   536,   536,   544,   549,   554,
     560,   560,   571,   572,   575,   576,   577,   578,   579,   580,
     581,   584,   584,   593,   593,   603,   603,   610,   611,   614,
     614,   621,   623,   627,   633,   633,   645,   645,   655,   656,
     658,   660,   660,   678,   678,   690,   690,   700,   701,   704,
     705,   708,   708,   718,   719,   722,   723,   724,   725,   726,
     727,   728,   729,   730,   731,   732,   733,   734,   735,   736,
     737,   738,   739,   740,   741,   742,   745,   745,   752,   753,
     754,   755,   758,   758,   766,   766,   774,   774,   782,   787,
     787,   795,   800,   805,   810,   815,   820,   825,   830,   830,
     838,   838,   846,   846,   854,   854,   862,   867,   872,   878,
     878,   888,   889,   892,   893,   894,   895,   896,   899,   904,
     909,   914,   919,   924,   924,   934,   935,   938,   939,   942,
     942,   952,   952,   962,   963,   964,   967,   968,   971,   971,
     979,   979,   987,   987,   998,   999,  1002,  1003,  1004,  1005,
    1006,  1007,  1010,  1015,  1020,  1025,  1030,  1035,  1043,  1043,
    1056,  1057,  1060,  1061,  1068,  1068,  1094,  1094,  1105,  1106,
    1110,  1111,  1112,  1113,  1114,  1115,  1116,  1117,  1118,  1119,
    1120,  1121,  1122,  1123,  1124,  1125,  1126,  1127,  1128,  1129,
    1130,  1131,  1132,  1133,  1134,  1135,  1136,  1137,  1138,  1141,
    1141,  1149,  1149,  1157,  1157,  1165,  1165,  1173,  1173,  1181,
    1181,  1189,  1189,  1199,  1199,  1206,  1207,  1208,  1209,  1212,
    1219,  1219,  1230,  1231,  1235,  1236,  1239,  1239,  1247,  1248,
    1251,  1252,  1253,  1254,  1255,  1256,  1257,  1258,  1259,  1260,
    1261,  1262,  1263,  1264,  1265,  1266,  1267,  1268,  1269,  1270,
    1271,  1272,  1273,  1274,  1281,  1281,  1294,  1294,  1303,  1304,
    1307,  1308,  1313,  1313,  1328,  1328,  1342,  1343,  1346,  1347,
    1350,  1351,  1352,  1353,  1354,  1355,  1356,  1357,  1358,  1359,
    1362,  1364,  1369,  1371,  1371,  1379,  1379,  1387,  1387,  1395,
    1397,  1397,  1405,  1414,  1414,  1426,  1427,  1432,  1433,  1438,
    1438,  1450,  1450,  1462,  1463,  1468,  1469,  1474,  1475,  1476,
    1477,  1478,  1479,  1480,  1481,  1482,  1485,  1487,  1487,  1495,
    1497,  1499,  1504,  1512,  1512,  1524,  1525,  1528,  1529,  1532,
    1532,  1542,  1542,  1552,  1553,  1556,  1557,  1558,  1559,  1560,
    1561,  1562,  1565,  1565,  1573,  1573,  1598,  1598,  1628,  1628,
    1638,  1639,  1642,  1643,  1646,  1646,  1655,  1655,  1664,  1665,
    1668,  1669,  1673,  1674,  1675,  1676,  1677,  1678,  1679,  1680,
    1681,  1682,  1683,  1684,  1685,  1686,  1687,  1690,  1690,  1698,
    1698,  1706,  1706,  1714,  1714,  1722,  1722,  1732,  1732,  1740,
    1740,  1748,  1748,  1756,  1756,  1764,  1764,  1772,  1772,  1780,
    1780,  1793,  1793,  1803,  1804,  1810,  1810,  1820,  1821,  1824,
    1824,  1834,  1835,  1838,  1839,  1842,  1843,  1844,  1845,  1846,
    1847,  1848,  1849,  1850,  1851,  1852,  1855,  1857,  1857,  1865,
    1874,  1881,  1881,  1891,  1892,  1895,  1896,  1897,  1898,  1899,
    1902,  1902,  1910,  1910,  1921,  1921,  1959,  1959,  1971,  1971,
    1981,  1982,  1985,  1986,  1987,  1988,  1989,  1990,  1991,  1992,
    1993,  1994,  1995,  1996,  1997,  1998,  1999,  2000,  2001,  2002,
    2005,  2010,  2010,  2018,  2018,  2026,  2031,  2031,  2039,  2044,
    2049,  2049,  2057,  2058,  2061,  2061,  2069,  2074,  2079,  2079,
    2087,  2090,  2093,  2096,  2099,  2105,  2105,  2113,  2113,  2121,
    2121,  2132,  2132,  2139,  2139,  2146,  2146,  2153,  2153,  2164,
    2164,  2174,  2175,  2179,  2180,  2183,  2183,  2193,  2203,  2203,
    2213,  2213,  2224,  2225,  2229,  2233,  2233,  2245,  2246,  2250,
    2250,  2258,  2259,  2262,  2263,  2264,  2265,  2266,  2267,  2268,
    2271,  2276,  2276,  2284,  2284,  2294,  2295,  2298,  2298,  2306,
    2307,  2310,  2311,  2312,  2313,  2314,  2317,  2317,  2325,  2330,
    2335,  2340,  2340
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
#line 5127 "dhcp4_parser.cc"

#line 2349 "dhcp4_parser.yy"


void
isc::dhcp::Dhcp4Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
