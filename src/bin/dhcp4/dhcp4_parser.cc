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
      case 193: // value
      case 197: // map_value
      case 243: // socket_type
      case 246: // outbound_interface_value
      case 268: // db_type
      case 354: // hr_mode
      case 503: // ncr_protocol_value
      case 510: // replace_client_name_value
        value.YY_MOVE_OR_COPY< ElementPtr > (YY_MOVE (that.value));
        break;

      case 176: // "boolean"
        value.YY_MOVE_OR_COPY< bool > (YY_MOVE (that.value));
        break;

      case 175: // "floating point"
        value.YY_MOVE_OR_COPY< double > (YY_MOVE (that.value));
        break;

      case 174: // "integer"
        value.YY_MOVE_OR_COPY< int64_t > (YY_MOVE (that.value));
        break;

      case 173: // "constant string"
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
      case 193: // value
      case 197: // map_value
      case 243: // socket_type
      case 246: // outbound_interface_value
      case 268: // db_type
      case 354: // hr_mode
      case 503: // ncr_protocol_value
      case 510: // replace_client_name_value
        value.move< ElementPtr > (YY_MOVE (that.value));
        break;

      case 176: // "boolean"
        value.move< bool > (YY_MOVE (that.value));
        break;

      case 175: // "floating point"
        value.move< double > (YY_MOVE (that.value));
        break;

      case 174: // "integer"
        value.move< int64_t > (YY_MOVE (that.value));
        break;

      case 173: // "constant string"
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
      case 193: // value
      case 197: // map_value
      case 243: // socket_type
      case 246: // outbound_interface_value
      case 268: // db_type
      case 354: // hr_mode
      case 503: // ncr_protocol_value
      case 510: // replace_client_name_value
        value.move< ElementPtr > (that.value);
        break;

      case 176: // "boolean"
        value.move< bool > (that.value);
        break;

      case 175: // "floating point"
        value.move< double > (that.value);
        break;

      case 174: // "integer"
        value.move< int64_t > (that.value);
        break;

      case 173: // "constant string"
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
      case 173: // "constant string"
#line 255 "dhcp4_parser.yy"
        { yyoutput << yysym.value.template as < std::string > (); }
#line 408 "dhcp4_parser.cc"
        break;

      case 174: // "integer"
#line 255 "dhcp4_parser.yy"
        { yyoutput << yysym.value.template as < int64_t > (); }
#line 414 "dhcp4_parser.cc"
        break;

      case 175: // "floating point"
#line 255 "dhcp4_parser.yy"
        { yyoutput << yysym.value.template as < double > (); }
#line 420 "dhcp4_parser.cc"
        break;

      case 176: // "boolean"
#line 255 "dhcp4_parser.yy"
        { yyoutput << yysym.value.template as < bool > (); }
#line 426 "dhcp4_parser.cc"
        break;

      case 193: // value
#line 255 "dhcp4_parser.yy"
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 432 "dhcp4_parser.cc"
        break;

      case 197: // map_value
#line 255 "dhcp4_parser.yy"
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 438 "dhcp4_parser.cc"
        break;

      case 243: // socket_type
#line 255 "dhcp4_parser.yy"
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 444 "dhcp4_parser.cc"
        break;

      case 246: // outbound_interface_value
#line 255 "dhcp4_parser.yy"
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 450 "dhcp4_parser.cc"
        break;

      case 268: // db_type
#line 255 "dhcp4_parser.yy"
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 456 "dhcp4_parser.cc"
        break;

      case 354: // hr_mode
#line 255 "dhcp4_parser.yy"
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 462 "dhcp4_parser.cc"
        break;

      case 503: // ncr_protocol_value
#line 255 "dhcp4_parser.yy"
        { yyoutput << yysym.value.template as < ElementPtr > (); }
#line 468 "dhcp4_parser.cc"
        break;

      case 510: // replace_client_name_value
#line 255 "dhcp4_parser.yy"
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
      case 193: // value
      case 197: // map_value
      case 243: // socket_type
      case 246: // outbound_interface_value
      case 268: // db_type
      case 354: // hr_mode
      case 503: // ncr_protocol_value
      case 510: // replace_client_name_value
        yylhs.value.emplace< ElementPtr > ();
        break;

      case 176: // "boolean"
        yylhs.value.emplace< bool > ();
        break;

      case 175: // "floating point"
        yylhs.value.emplace< double > ();
        break;

      case 174: // "integer"
        yylhs.value.emplace< int64_t > ();
        break;

      case 173: // "constant string"
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
#line 264 "dhcp4_parser.yy"
    { ctx.ctx_ = ctx.NO_KEYWORD; }
#line 741 "dhcp4_parser.cc"
    break;

  case 4:
#line 265 "dhcp4_parser.yy"
    { ctx.ctx_ = ctx.CONFIG; }
#line 747 "dhcp4_parser.cc"
    break;

  case 6:
#line 266 "dhcp4_parser.yy"
    { ctx.ctx_ = ctx.DHCP4; }
#line 753 "dhcp4_parser.cc"
    break;

  case 8:
#line 267 "dhcp4_parser.yy"
    { ctx.ctx_ = ctx.INTERFACES_CONFIG; }
#line 759 "dhcp4_parser.cc"
    break;

  case 10:
#line 268 "dhcp4_parser.yy"
    { ctx.ctx_ = ctx.SUBNET4; }
#line 765 "dhcp4_parser.cc"
    break;

  case 12:
#line 269 "dhcp4_parser.yy"
    { ctx.ctx_ = ctx.POOLS; }
#line 771 "dhcp4_parser.cc"
    break;

  case 14:
#line 270 "dhcp4_parser.yy"
    { ctx.ctx_ = ctx.RESERVATIONS; }
#line 777 "dhcp4_parser.cc"
    break;

  case 16:
#line 271 "dhcp4_parser.yy"
    { ctx.ctx_ = ctx.DHCP4; }
#line 783 "dhcp4_parser.cc"
    break;

  case 18:
#line 272 "dhcp4_parser.yy"
    { ctx.ctx_ = ctx.OPTION_DEF; }
#line 789 "dhcp4_parser.cc"
    break;

  case 20:
#line 273 "dhcp4_parser.yy"
    { ctx.ctx_ = ctx.OPTION_DATA; }
#line 795 "dhcp4_parser.cc"
    break;

  case 22:
#line 274 "dhcp4_parser.yy"
    { ctx.ctx_ = ctx.HOOKS_LIBRARIES; }
#line 801 "dhcp4_parser.cc"
    break;

  case 24:
#line 275 "dhcp4_parser.yy"
    { ctx.ctx_ = ctx.DHCP_DDNS; }
#line 807 "dhcp4_parser.cc"
    break;

  case 26:
#line 276 "dhcp4_parser.yy"
    { ctx.ctx_ = ctx.LOGGING; }
#line 813 "dhcp4_parser.cc"
    break;

  case 28:
#line 277 "dhcp4_parser.yy"
    { ctx.ctx_ = ctx.CONFIG_CONTROL; }
#line 819 "dhcp4_parser.cc"
    break;

  case 30:
#line 285 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location))); }
#line 825 "dhcp4_parser.cc"
    break;

  case 31:
#line 286 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location))); }
#line 831 "dhcp4_parser.cc"
    break;

  case 32:
#line 287 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location))); }
#line 837 "dhcp4_parser.cc"
    break;

  case 33:
#line 288 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location))); }
#line 843 "dhcp4_parser.cc"
    break;

  case 34:
#line 289 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new NullElement(ctx.loc2pos(yystack_[0].location))); }
#line 849 "dhcp4_parser.cc"
    break;

  case 35:
#line 290 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 855 "dhcp4_parser.cc"
    break;

  case 36:
#line 291 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 861 "dhcp4_parser.cc"
    break;

  case 37:
#line 294 "dhcp4_parser.yy"
    {
    // Push back the JSON value on the stack
    ctx.stack_.push_back(yystack_[0].value.as < ElementPtr > ());
}
#line 870 "dhcp4_parser.cc"
    break;

  case 38:
#line 299 "dhcp4_parser.yy"
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 881 "dhcp4_parser.cc"
    break;

  case 39:
#line 304 "dhcp4_parser.yy"
    {
    // map parsing completed. If we ever want to do any wrap up
    // (maybe some sanity checking), this would be the best place
    // for it.
}
#line 891 "dhcp4_parser.cc"
    break;

  case 40:
#line 310 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ctx.stack_.back(); ctx.stack_.pop_back(); }
#line 897 "dhcp4_parser.cc"
    break;

  case 43:
#line 317 "dhcp4_parser.yy"
    {
                  // map containing a single entry
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 906 "dhcp4_parser.cc"
    break;

  case 44:
#line 321 "dhcp4_parser.yy"
    {
                  // map consisting of a shorter map followed by
                  // comma and string:value
                  ctx.stack_.back()->set(yystack_[2].value.as < std::string > (), yystack_[0].value.as < ElementPtr > ());
                  }
#line 916 "dhcp4_parser.cc"
    break;

  case 45:
#line 328 "dhcp4_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(l);
}
#line 925 "dhcp4_parser.cc"
    break;

  case 46:
#line 331 "dhcp4_parser.yy"
    {
    // list parsing complete. Put any sanity checking here
}
#line 933 "dhcp4_parser.cc"
    break;

  case 49:
#line 339 "dhcp4_parser.yy"
    {
                  // List consisting of a single element.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 942 "dhcp4_parser.cc"
    break;

  case 50:
#line 343 "dhcp4_parser.yy"
    {
                  // List ending with , and a value.
                  ctx.stack_.back()->add(yystack_[0].value.as < ElementPtr > ());
                  }
#line 951 "dhcp4_parser.cc"
    break;

  case 51:
#line 350 "dhcp4_parser.yy"
    {
    // List parsing about to start
}
#line 959 "dhcp4_parser.cc"
    break;

  case 52:
#line 352 "dhcp4_parser.yy"
    {
    // list parsing complete. Put any sanity checking here
    //ctx.stack_.pop_back();
}
#line 968 "dhcp4_parser.cc"
    break;

  case 55:
#line 361 "dhcp4_parser.yy"
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 977 "dhcp4_parser.cc"
    break;

  case 56:
#line 365 "dhcp4_parser.yy"
    {
                          ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
                          ctx.stack_.back()->add(s);
                          }
#line 986 "dhcp4_parser.cc"
    break;

  case 57:
#line 376 "dhcp4_parser.yy"
    {
    const std::string& where = ctx.contextName();
    const std::string& keyword = yystack_[1].value.as < std::string > ();
    error(yystack_[1].location,
          "got unexpected keyword \"" + keyword + "\" in " + where + " map.");
}
#line 997 "dhcp4_parser.cc"
    break;

  case 58:
#line 386 "dhcp4_parser.yy"
    {
    // This code is executed when we're about to start parsing
    // the content of the map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1008 "dhcp4_parser.cc"
    break;

  case 59:
#line 391 "dhcp4_parser.yy"
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
#line 415 "dhcp4_parser.yy"
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
#line 422 "dhcp4_parser.yy"
    {
    // No global parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1044 "dhcp4_parser.cc"
    break;

  case 70:
#line 430 "dhcp4_parser.yy"
    {
    // Parse the Dhcp4 map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1054 "dhcp4_parser.cc"
    break;

  case 71:
#line 434 "dhcp4_parser.yy"
    {
    // No global parameter is required
    // parsing completed
}
#line 1063 "dhcp4_parser.cc"
    break;

  case 116:
#line 489 "dhcp4_parser.yy"
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1072 "dhcp4_parser.cc"
    break;

  case 117:
#line 494 "dhcp4_parser.yy"
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-valid-lifetime", prf);
}
#line 1081 "dhcp4_parser.cc"
    break;

  case 118:
#line 499 "dhcp4_parser.yy"
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-valid-lifetime", prf);
}
#line 1090 "dhcp4_parser.cc"
    break;

  case 119:
#line 504 "dhcp4_parser.yy"
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1099 "dhcp4_parser.cc"
    break;

  case 120:
#line 509 "dhcp4_parser.yy"
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1108 "dhcp4_parser.cc"
    break;

  case 121:
#line 514 "dhcp4_parser.yy"
    {
    ElementPtr ctt(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("calculate-tee-times", ctt);
}
#line 1117 "dhcp4_parser.cc"
    break;

  case 122:
#line 519 "dhcp4_parser.yy"
    {
    ElementPtr t1(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t1-percent", t1);
}
#line 1126 "dhcp4_parser.cc"
    break;

  case 123:
#line 524 "dhcp4_parser.yy"
    {
    ElementPtr t2(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t2-percent", t2);
}
#line 1135 "dhcp4_parser.cc"
    break;

  case 124:
#line 529 "dhcp4_parser.yy"
    {
    ElementPtr dpp(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1144 "dhcp4_parser.cc"
    break;

  case 125:
#line 534 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1152 "dhcp4_parser.cc"
    break;

  case 126:
#line 536 "dhcp4_parser.yy"
    {
    ElementPtr stag(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-tag", stag);
    ctx.leave();
}
#line 1162 "dhcp4_parser.cc"
    break;

  case 127:
#line 542 "dhcp4_parser.yy"
    {
    ElementPtr echo(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("echo-client-id", echo);
}
#line 1171 "dhcp4_parser.cc"
    break;

  case 128:
#line 547 "dhcp4_parser.yy"
    {
    ElementPtr match(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("match-client-id", match);
}
#line 1180 "dhcp4_parser.cc"
    break;

  case 129:
#line 552 "dhcp4_parser.yy"
    {
    ElementPtr prf(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("authoritative", prf);
}
#line 1189 "dhcp4_parser.cc"
    break;

  case 130:
#line 558 "dhcp4_parser.yy"
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1200 "dhcp4_parser.cc"
    break;

  case 131:
#line 563 "dhcp4_parser.yy"
    {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1210 "dhcp4_parser.cc"
    break;

  case 141:
#line 582 "dhcp4_parser.yy"
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1220 "dhcp4_parser.cc"
    break;

  case 142:
#line 586 "dhcp4_parser.yy"
    {
    // No interfaces config param is required
    // parsing completed
}
#line 1229 "dhcp4_parser.cc"
    break;

  case 143:
#line 591 "dhcp4_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1240 "dhcp4_parser.cc"
    break;

  case 144:
#line 596 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1249 "dhcp4_parser.cc"
    break;

  case 145:
#line 601 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.DHCP_SOCKET_TYPE);
}
#line 1257 "dhcp4_parser.cc"
    break;

  case 146:
#line 603 "dhcp4_parser.yy"
    {
    ctx.stack_.back()->set("dhcp-socket-type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1266 "dhcp4_parser.cc"
    break;

  case 147:
#line 608 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("raw", ctx.loc2pos(yystack_[0].location))); }
#line 1272 "dhcp4_parser.cc"
    break;

  case 148:
#line 609 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("udp", ctx.loc2pos(yystack_[0].location))); }
#line 1278 "dhcp4_parser.cc"
    break;

  case 149:
#line 612 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.OUTBOUND_INTERFACE);
}
#line 1286 "dhcp4_parser.cc"
    break;

  case 150:
#line 614 "dhcp4_parser.yy"
    {
    ctx.stack_.back()->set("outbound-interface", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1295 "dhcp4_parser.cc"
    break;

  case 151:
#line 619 "dhcp4_parser.yy"
    {
    yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("same-as-inbound", ctx.loc2pos(yystack_[0].location)));
}
#line 1303 "dhcp4_parser.cc"
    break;

  case 152:
#line 621 "dhcp4_parser.yy"
    {
    yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("use-routing", ctx.loc2pos(yystack_[0].location)));
    }
#line 1311 "dhcp4_parser.cc"
    break;

  case 153:
#line 625 "dhcp4_parser.yy"
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1320 "dhcp4_parser.cc"
    break;

  case 154:
#line 631 "dhcp4_parser.yy"
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1331 "dhcp4_parser.cc"
    break;

  case 155:
#line 636 "dhcp4_parser.yy"
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1342 "dhcp4_parser.cc"
    break;

  case 156:
#line 643 "dhcp4_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sanity-checks", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SANITY_CHECKS);
}
#line 1353 "dhcp4_parser.cc"
    break;

  case 157:
#line 648 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1362 "dhcp4_parser.cc"
    break;

  case 161:
#line 658 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1370 "dhcp4_parser.cc"
    break;

  case 162:
#line 660 "dhcp4_parser.yy"
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
#line 676 "dhcp4_parser.yy"
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1401 "dhcp4_parser.cc"
    break;

  case 164:
#line 681 "dhcp4_parser.yy"
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1412 "dhcp4_parser.cc"
    break;

  case 165:
#line 688 "dhcp4_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1423 "dhcp4_parser.cc"
    break;

  case 166:
#line 693 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1432 "dhcp4_parser.cc"
    break;

  case 171:
#line 706 "dhcp4_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1442 "dhcp4_parser.cc"
    break;

  case 172:
#line 710 "dhcp4_parser.yy"
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1452 "dhcp4_parser.cc"
    break;

  case 195:
#line 742 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1460 "dhcp4_parser.cc"
    break;

  case 196:
#line 744 "dhcp4_parser.yy"
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1469 "dhcp4_parser.cc"
    break;

  case 197:
#line 749 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1475 "dhcp4_parser.cc"
    break;

  case 198:
#line 750 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1481 "dhcp4_parser.cc"
    break;

  case 199:
#line 751 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1487 "dhcp4_parser.cc"
    break;

  case 200:
#line 752 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1493 "dhcp4_parser.cc"
    break;

  case 201:
#line 755 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1501 "dhcp4_parser.cc"
    break;

  case 202:
#line 757 "dhcp4_parser.yy"
    {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1511 "dhcp4_parser.cc"
    break;

  case 203:
#line 763 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1519 "dhcp4_parser.cc"
    break;

  case 204:
#line 765 "dhcp4_parser.yy"
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1529 "dhcp4_parser.cc"
    break;

  case 205:
#line 771 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1537 "dhcp4_parser.cc"
    break;

  case 206:
#line 773 "dhcp4_parser.yy"
    {
    ElementPtr h(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1547 "dhcp4_parser.cc"
    break;

  case 207:
#line 779 "dhcp4_parser.yy"
    {
    ElementPtr p(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1556 "dhcp4_parser.cc"
    break;

  case 208:
#line 784 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1564 "dhcp4_parser.cc"
    break;

  case 209:
#line 786 "dhcp4_parser.yy"
    {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1574 "dhcp4_parser.cc"
    break;

  case 210:
#line 792 "dhcp4_parser.yy"
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1583 "dhcp4_parser.cc"
    break;

  case 211:
#line 797 "dhcp4_parser.yy"
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1592 "dhcp4_parser.cc"
    break;

  case 212:
#line 802 "dhcp4_parser.yy"
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1601 "dhcp4_parser.cc"
    break;

  case 213:
#line 807 "dhcp4_parser.yy"
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1610 "dhcp4_parser.cc"
    break;

  case 214:
#line 812 "dhcp4_parser.yy"
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("request-timeout", n);
}
#line 1619 "dhcp4_parser.cc"
    break;

  case 215:
#line 817 "dhcp4_parser.yy"
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-keepalive", n);
}
#line 1628 "dhcp4_parser.cc"
    break;

  case 216:
#line 822 "dhcp4_parser.yy"
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-nodelay", n);
}
#line 1637 "dhcp4_parser.cc"
    break;

  case 217:
#line 827 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1645 "dhcp4_parser.cc"
    break;

  case 218:
#line 829 "dhcp4_parser.yy"
    {
    ElementPtr cp(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1655 "dhcp4_parser.cc"
    break;

  case 219:
#line 835 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1663 "dhcp4_parser.cc"
    break;

  case 220:
#line 837 "dhcp4_parser.yy"
    {
    ElementPtr ks(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 1673 "dhcp4_parser.cc"
    break;

  case 221:
#line 843 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1681 "dhcp4_parser.cc"
    break;

  case 222:
#line 845 "dhcp4_parser.yy"
    {
    ElementPtr c(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("consistency", c);
    ctx.leave();
}
#line 1691 "dhcp4_parser.cc"
    break;

  case 223:
#line 851 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1699 "dhcp4_parser.cc"
    break;

  case 224:
#line 853 "dhcp4_parser.yy"
    {
    ElementPtr c(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("serial-consistency", c);
    ctx.leave();
}
#line 1709 "dhcp4_parser.cc"
    break;

  case 225:
#line 859 "dhcp4_parser.yy"
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 1718 "dhcp4_parser.cc"
    break;

  case 226:
#line 864 "dhcp4_parser.yy"
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 1727 "dhcp4_parser.cc"
    break;

  case 227:
#line 869 "dhcp4_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1738 "dhcp4_parser.cc"
    break;

  case 228:
#line 874 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1747 "dhcp4_parser.cc"
    break;

  case 236:
#line 890 "dhcp4_parser.yy"
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1756 "dhcp4_parser.cc"
    break;

  case 237:
#line 895 "dhcp4_parser.yy"
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1765 "dhcp4_parser.cc"
    break;

  case 238:
#line 900 "dhcp4_parser.yy"
    {
    ElementPtr circuit(new StringElement("circuit-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(circuit);
}
#line 1774 "dhcp4_parser.cc"
    break;

  case 239:
#line 905 "dhcp4_parser.yy"
    {
    ElementPtr client(new StringElement("client-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(client);
}
#line 1783 "dhcp4_parser.cc"
    break;

  case 240:
#line 910 "dhcp4_parser.yy"
    {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 1792 "dhcp4_parser.cc"
    break;

  case 241:
#line 915 "dhcp4_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1803 "dhcp4_parser.cc"
    break;

  case 242:
#line 920 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1812 "dhcp4_parser.cc"
    break;

  case 247:
#line 933 "dhcp4_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1822 "dhcp4_parser.cc"
    break;

  case 248:
#line 937 "dhcp4_parser.yy"
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1832 "dhcp4_parser.cc"
    break;

  case 249:
#line 943 "dhcp4_parser.yy"
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1842 "dhcp4_parser.cc"
    break;

  case 250:
#line 947 "dhcp4_parser.yy"
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1852 "dhcp4_parser.cc"
    break;

  case 256:
#line 962 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1860 "dhcp4_parser.cc"
    break;

  case 257:
#line 964 "dhcp4_parser.yy"
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1870 "dhcp4_parser.cc"
    break;

  case 258:
#line 970 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1878 "dhcp4_parser.cc"
    break;

  case 259:
#line 972 "dhcp4_parser.yy"
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1887 "dhcp4_parser.cc"
    break;

  case 260:
#line 978 "dhcp4_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 1898 "dhcp4_parser.cc"
    break;

  case 261:
#line 983 "dhcp4_parser.yy"
    {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1908 "dhcp4_parser.cc"
    break;

  case 270:
#line 1001 "dhcp4_parser.yy"
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 1917 "dhcp4_parser.cc"
    break;

  case 271:
#line 1006 "dhcp4_parser.yy"
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 1926 "dhcp4_parser.cc"
    break;

  case 272:
#line 1011 "dhcp4_parser.yy"
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 1935 "dhcp4_parser.cc"
    break;

  case 273:
#line 1016 "dhcp4_parser.yy"
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 1944 "dhcp4_parser.cc"
    break;

  case 274:
#line 1021 "dhcp4_parser.yy"
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 1953 "dhcp4_parser.cc"
    break;

  case 275:
#line 1026 "dhcp4_parser.yy"
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 1962 "dhcp4_parser.cc"
    break;

  case 276:
#line 1034 "dhcp4_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet4", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET4);
}
#line 1973 "dhcp4_parser.cc"
    break;

  case 277:
#line 1039 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1982 "dhcp4_parser.cc"
    break;

  case 282:
#line 1059 "dhcp4_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1992 "dhcp4_parser.cc"
    break;

  case 283:
#line 1063 "dhcp4_parser.yy"
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
#line 2018 "dhcp4_parser.cc"
    break;

  case 284:
#line 1085 "dhcp4_parser.yy"
    {
    // Parse the subnet4 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2028 "dhcp4_parser.cc"
    break;

  case 285:
#line 1089 "dhcp4_parser.yy"
    {
    // The subnet subnet4 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2038 "dhcp4_parser.cc"
    break;

  case 317:
#line 1132 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2046 "dhcp4_parser.cc"
    break;

  case 318:
#line 1134 "dhcp4_parser.yy"
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 2056 "dhcp4_parser.cc"
    break;

  case 319:
#line 1140 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2064 "dhcp4_parser.cc"
    break;

  case 320:
#line 1142 "dhcp4_parser.yy"
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface", iface);
    ctx.leave();
}
#line 2074 "dhcp4_parser.cc"
    break;

  case 321:
#line 1148 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2082 "dhcp4_parser.cc"
    break;

  case 322:
#line 1150 "dhcp4_parser.yy"
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface-id", iface);
    ctx.leave();
}
#line 2092 "dhcp4_parser.cc"
    break;

  case 323:
#line 1156 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2100 "dhcp4_parser.cc"
    break;

  case 324:
#line 1158 "dhcp4_parser.yy"
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-subnet", iface);
    ctx.leave();
}
#line 2110 "dhcp4_parser.cc"
    break;

  case 325:
#line 1164 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2118 "dhcp4_parser.cc"
    break;

  case 326:
#line 1166 "dhcp4_parser.yy"
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 2128 "dhcp4_parser.cc"
    break;

  case 327:
#line 1172 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2136 "dhcp4_parser.cc"
    break;

  case 328:
#line 1174 "dhcp4_parser.yy"
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 2146 "dhcp4_parser.cc"
    break;

  case 329:
#line 1180 "dhcp4_parser.yy"
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2157 "dhcp4_parser.cc"
    break;

  case 330:
#line 1185 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2166 "dhcp4_parser.cc"
    break;

  case 331:
#line 1190 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 2174 "dhcp4_parser.cc"
    break;

  case 332:
#line 1192 "dhcp4_parser.yy"
    {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2183 "dhcp4_parser.cc"
    break;

  case 333:
#line 1197 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 2189 "dhcp4_parser.cc"
    break;

  case 334:
#line 1198 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 2195 "dhcp4_parser.cc"
    break;

  case 335:
#line 1199 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("global", ctx.loc2pos(yystack_[0].location))); }
#line 2201 "dhcp4_parser.cc"
    break;

  case 336:
#line 1200 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 2207 "dhcp4_parser.cc"
    break;

  case 337:
#line 1203 "dhcp4_parser.yy"
    {
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 2216 "dhcp4_parser.cc"
    break;

  case 338:
#line 1210 "dhcp4_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 2227 "dhcp4_parser.cc"
    break;

  case 339:
#line 1215 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2236 "dhcp4_parser.cc"
    break;

  case 344:
#line 1230 "dhcp4_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2246 "dhcp4_parser.cc"
    break;

  case 345:
#line 1234 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
}
#line 2254 "dhcp4_parser.cc"
    break;

  case 372:
#line 1272 "dhcp4_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 2265 "dhcp4_parser.cc"
    break;

  case 373:
#line 1277 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2274 "dhcp4_parser.cc"
    break;

  case 374:
#line 1285 "dhcp4_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2283 "dhcp4_parser.cc"
    break;

  case 375:
#line 1288 "dhcp4_parser.yy"
    {
    // parsing completed
}
#line 2291 "dhcp4_parser.cc"
    break;

  case 380:
#line 1304 "dhcp4_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2301 "dhcp4_parser.cc"
    break;

  case 381:
#line 1308 "dhcp4_parser.yy"
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2313 "dhcp4_parser.cc"
    break;

  case 382:
#line 1319 "dhcp4_parser.yy"
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2323 "dhcp4_parser.cc"
    break;

  case 383:
#line 1323 "dhcp4_parser.yy"
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2335 "dhcp4_parser.cc"
    break;

  case 399:
#line 1355 "dhcp4_parser.yy"
    {
    ElementPtr code(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 2344 "dhcp4_parser.cc"
    break;

  case 401:
#line 1362 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2352 "dhcp4_parser.cc"
    break;

  case 402:
#line 1364 "dhcp4_parser.yy"
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 2362 "dhcp4_parser.cc"
    break;

  case 403:
#line 1370 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2370 "dhcp4_parser.cc"
    break;

  case 404:
#line 1372 "dhcp4_parser.yy"
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 2380 "dhcp4_parser.cc"
    break;

  case 405:
#line 1378 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2388 "dhcp4_parser.cc"
    break;

  case 406:
#line 1380 "dhcp4_parser.yy"
    {
    ElementPtr space(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 2398 "dhcp4_parser.cc"
    break;

  case 408:
#line 1388 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2406 "dhcp4_parser.cc"
    break;

  case 409:
#line 1390 "dhcp4_parser.yy"
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 2416 "dhcp4_parser.cc"
    break;

  case 410:
#line 1396 "dhcp4_parser.yy"
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 2425 "dhcp4_parser.cc"
    break;

  case 411:
#line 1405 "dhcp4_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 2436 "dhcp4_parser.cc"
    break;

  case 412:
#line 1410 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2445 "dhcp4_parser.cc"
    break;

  case 417:
#line 1429 "dhcp4_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2455 "dhcp4_parser.cc"
    break;

  case 418:
#line 1433 "dhcp4_parser.yy"
    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 2464 "dhcp4_parser.cc"
    break;

  case 419:
#line 1441 "dhcp4_parser.yy"
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2474 "dhcp4_parser.cc"
    break;

  case 420:
#line 1445 "dhcp4_parser.yy"
    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 2483 "dhcp4_parser.cc"
    break;

  case 435:
#line 1478 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2491 "dhcp4_parser.cc"
    break;

  case 436:
#line 1480 "dhcp4_parser.yy"
    {
    ElementPtr data(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2501 "dhcp4_parser.cc"
    break;

  case 439:
#line 1490 "dhcp4_parser.yy"
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2510 "dhcp4_parser.cc"
    break;

  case 440:
#line 1495 "dhcp4_parser.yy"
    {
    ElementPtr persist(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 2519 "dhcp4_parser.cc"
    break;

  case 441:
#line 1503 "dhcp4_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2530 "dhcp4_parser.cc"
    break;

  case 442:
#line 1508 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2539 "dhcp4_parser.cc"
    break;

  case 447:
#line 1523 "dhcp4_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2549 "dhcp4_parser.cc"
    break;

  case 448:
#line 1527 "dhcp4_parser.yy"
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2559 "dhcp4_parser.cc"
    break;

  case 449:
#line 1533 "dhcp4_parser.yy"
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2569 "dhcp4_parser.cc"
    break;

  case 450:
#line 1537 "dhcp4_parser.yy"
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2579 "dhcp4_parser.cc"
    break;

  case 460:
#line 1556 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2587 "dhcp4_parser.cc"
    break;

  case 461:
#line 1558 "dhcp4_parser.yy"
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2597 "dhcp4_parser.cc"
    break;

  case 462:
#line 1564 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2605 "dhcp4_parser.cc"
    break;

  case 463:
#line 1566 "dhcp4_parser.yy"
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
#line 2632 "dhcp4_parser.cc"
    break;

  case 464:
#line 1589 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2640 "dhcp4_parser.cc"
    break;

  case 465:
#line 1591 "dhcp4_parser.yy"
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
#line 2669 "dhcp4_parser.cc"
    break;

  case 466:
#line 1619 "dhcp4_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 2680 "dhcp4_parser.cc"
    break;

  case 467:
#line 1624 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2689 "dhcp4_parser.cc"
    break;

  case 472:
#line 1637 "dhcp4_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2699 "dhcp4_parser.cc"
    break;

  case 473:
#line 1641 "dhcp4_parser.yy"
    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 2708 "dhcp4_parser.cc"
    break;

  case 474:
#line 1646 "dhcp4_parser.yy"
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2718 "dhcp4_parser.cc"
    break;

  case 475:
#line 1650 "dhcp4_parser.yy"
    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 2727 "dhcp4_parser.cc"
    break;

  case 495:
#line 1681 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2735 "dhcp4_parser.cc"
    break;

  case 496:
#line 1683 "dhcp4_parser.yy"
    {
    ElementPtr next_server(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("next-server", next_server);
    ctx.leave();
}
#line 2745 "dhcp4_parser.cc"
    break;

  case 497:
#line 1689 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2753 "dhcp4_parser.cc"
    break;

  case 498:
#line 1691 "dhcp4_parser.yy"
    {
    ElementPtr srv(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-hostname", srv);
    ctx.leave();
}
#line 2763 "dhcp4_parser.cc"
    break;

  case 499:
#line 1697 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2771 "dhcp4_parser.cc"
    break;

  case 500:
#line 1699 "dhcp4_parser.yy"
    {
    ElementPtr bootfile(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("boot-file-name", bootfile);
    ctx.leave();
}
#line 2781 "dhcp4_parser.cc"
    break;

  case 501:
#line 1705 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2789 "dhcp4_parser.cc"
    break;

  case 502:
#line 1707 "dhcp4_parser.yy"
    {
    ElementPtr addr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 2799 "dhcp4_parser.cc"
    break;

  case 503:
#line 1713 "dhcp4_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2810 "dhcp4_parser.cc"
    break;

  case 504:
#line 1718 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2819 "dhcp4_parser.cc"
    break;

  case 505:
#line 1723 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2827 "dhcp4_parser.cc"
    break;

  case 506:
#line 1725 "dhcp4_parser.yy"
    {
    ElementPtr d(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2837 "dhcp4_parser.cc"
    break;

  case 507:
#line 1731 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2845 "dhcp4_parser.cc"
    break;

  case 508:
#line 1733 "dhcp4_parser.yy"
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2855 "dhcp4_parser.cc"
    break;

  case 509:
#line 1739 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2863 "dhcp4_parser.cc"
    break;

  case 510:
#line 1741 "dhcp4_parser.yy"
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-id", hw);
    ctx.leave();
}
#line 2873 "dhcp4_parser.cc"
    break;

  case 511:
#line 1747 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2881 "dhcp4_parser.cc"
    break;

  case 512:
#line 1749 "dhcp4_parser.yy"
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("circuit-id", hw);
    ctx.leave();
}
#line 2891 "dhcp4_parser.cc"
    break;

  case 513:
#line 1755 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2899 "dhcp4_parser.cc"
    break;

  case 514:
#line 1757 "dhcp4_parser.yy"
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 2909 "dhcp4_parser.cc"
    break;

  case 515:
#line 1763 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2917 "dhcp4_parser.cc"
    break;

  case 516:
#line 1765 "dhcp4_parser.yy"
    {
    ElementPtr host(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2927 "dhcp4_parser.cc"
    break;

  case 517:
#line 1771 "dhcp4_parser.yy"
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2938 "dhcp4_parser.cc"
    break;

  case 518:
#line 1776 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2947 "dhcp4_parser.cc"
    break;

  case 519:
#line 1784 "dhcp4_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2958 "dhcp4_parser.cc"
    break;

  case 520:
#line 1789 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2967 "dhcp4_parser.cc"
    break;

  case 523:
#line 1801 "dhcp4_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2978 "dhcp4_parser.cc"
    break;

  case 524:
#line 1806 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2987 "dhcp4_parser.cc"
    break;

  case 527:
#line 1815 "dhcp4_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2997 "dhcp4_parser.cc"
    break;

  case 528:
#line 1819 "dhcp4_parser.yy"
    {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3007 "dhcp4_parser.cc"
    break;

  case 545:
#line 1848 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3015 "dhcp4_parser.cc"
    break;

  case 546:
#line 1850 "dhcp4_parser.yy"
    {
    ElementPtr test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 3025 "dhcp4_parser.cc"
    break;

  case 547:
#line 1856 "dhcp4_parser.yy"
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 3034 "dhcp4_parser.cc"
    break;

  case 548:
#line 1865 "dhcp4_parser.yy"
    {
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 3043 "dhcp4_parser.cc"
    break;

  case 549:
#line 1872 "dhcp4_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 3054 "dhcp4_parser.cc"
    break;

  case 550:
#line 1877 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3063 "dhcp4_parser.cc"
    break;

  case 558:
#line 1893 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3071 "dhcp4_parser.cc"
    break;

  case 559:
#line 1895 "dhcp4_parser.yy"
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 3081 "dhcp4_parser.cc"
    break;

  case 560:
#line 1901 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3089 "dhcp4_parser.cc"
    break;

  case 561:
#line 1903 "dhcp4_parser.yy"
    {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 3099 "dhcp4_parser.cc"
    break;

  case 562:
#line 1912 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3107 "dhcp4_parser.cc"
    break;

  case 563:
#line 1914 "dhcp4_parser.yy"
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
#line 3145 "dhcp4_parser.cc"
    break;

  case 564:
#line 1950 "dhcp4_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 3156 "dhcp4_parser.cc"
    break;

  case 565:
#line 1955 "dhcp4_parser.yy"
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3167 "dhcp4_parser.cc"
    break;

  case 566:
#line 1962 "dhcp4_parser.yy"
    {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3177 "dhcp4_parser.cc"
    break;

  case 567:
#line 1966 "dhcp4_parser.yy"
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3187 "dhcp4_parser.cc"
    break;

  case 588:
#line 1996 "dhcp4_parser.yy"
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 3196 "dhcp4_parser.cc"
    break;

  case 589:
#line 2001 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3204 "dhcp4_parser.cc"
    break;

  case 590:
#line 2003 "dhcp4_parser.yy"
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 3214 "dhcp4_parser.cc"
    break;

  case 591:
#line 2009 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3222 "dhcp4_parser.cc"
    break;

  case 592:
#line 2011 "dhcp4_parser.yy"
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 3232 "dhcp4_parser.cc"
    break;

  case 593:
#line 2017 "dhcp4_parser.yy"
    {
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 3241 "dhcp4_parser.cc"
    break;

  case 594:
#line 2022 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3249 "dhcp4_parser.cc"
    break;

  case 595:
#line 2024 "dhcp4_parser.yy"
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 3259 "dhcp4_parser.cc"
    break;

  case 596:
#line 2030 "dhcp4_parser.yy"
    {
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 3268 "dhcp4_parser.cc"
    break;

  case 597:
#line 2035 "dhcp4_parser.yy"
    {
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 3277 "dhcp4_parser.cc"
    break;

  case 598:
#line 2040 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 3285 "dhcp4_parser.cc"
    break;

  case 599:
#line 2042 "dhcp4_parser.yy"
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3294 "dhcp4_parser.cc"
    break;

  case 600:
#line 2048 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 3300 "dhcp4_parser.cc"
    break;

  case 601:
#line 2049 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 3306 "dhcp4_parser.cc"
    break;

  case 602:
#line 2052 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 3314 "dhcp4_parser.cc"
    break;

  case 603:
#line 2054 "dhcp4_parser.yy"
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 3324 "dhcp4_parser.cc"
    break;

  case 604:
#line 2060 "dhcp4_parser.yy"
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 3333 "dhcp4_parser.cc"
    break;

  case 605:
#line 2065 "dhcp4_parser.yy"
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 3342 "dhcp4_parser.cc"
    break;

  case 606:
#line 2070 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 3350 "dhcp4_parser.cc"
    break;

  case 607:
#line 2072 "dhcp4_parser.yy"
    {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3359 "dhcp4_parser.cc"
    break;

  case 608:
#line 2078 "dhcp4_parser.yy"
    {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 3367 "dhcp4_parser.cc"
    break;

  case 609:
#line 2081 "dhcp4_parser.yy"
    {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 3375 "dhcp4_parser.cc"
    break;

  case 610:
#line 2084 "dhcp4_parser.yy"
    {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 3383 "dhcp4_parser.cc"
    break;

  case 611:
#line 2087 "dhcp4_parser.yy"
    {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 3391 "dhcp4_parser.cc"
    break;

  case 612:
#line 2090 "dhcp4_parser.yy"
    {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 3400 "dhcp4_parser.cc"
    break;

  case 613:
#line 2096 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3408 "dhcp4_parser.cc"
    break;

  case 614:
#line 2098 "dhcp4_parser.yy"
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 3418 "dhcp4_parser.cc"
    break;

  case 615:
#line 2104 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3426 "dhcp4_parser.cc"
    break;

  case 616:
#line 2106 "dhcp4_parser.yy"
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 3436 "dhcp4_parser.cc"
    break;

  case 617:
#line 2112 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3444 "dhcp4_parser.cc"
    break;

  case 618:
#line 2114 "dhcp4_parser.yy"
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 3454 "dhcp4_parser.cc"
    break;

  case 619:
#line 2123 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3462 "dhcp4_parser.cc"
    break;

  case 620:
#line 2125 "dhcp4_parser.yy"
    {
    ctx.stack_.back()->set("Dhcp6", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3471 "dhcp4_parser.cc"
    break;

  case 621:
#line 2130 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3479 "dhcp4_parser.cc"
    break;

  case 622:
#line 2132 "dhcp4_parser.yy"
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3488 "dhcp4_parser.cc"
    break;

  case 623:
#line 2137 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3496 "dhcp4_parser.cc"
    break;

  case 624:
#line 2139 "dhcp4_parser.yy"
    {
    ctx.stack_.back()->set("Control-agent", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3505 "dhcp4_parser.cc"
    break;

  case 625:
#line 2144 "dhcp4_parser.yy"
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 3516 "dhcp4_parser.cc"
    break;

  case 626:
#line 2149 "dhcp4_parser.yy"
    {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3526 "dhcp4_parser.cc"
    break;

  case 627:
#line 2155 "dhcp4_parser.yy"
    {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3536 "dhcp4_parser.cc"
    break;

  case 628:
#line 2159 "dhcp4_parser.yy"
    {
    // No config_control params are required
    // parsing completed
}
#line 3545 "dhcp4_parser.cc"
    break;

  case 633:
#line 2174 "dhcp4_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 3556 "dhcp4_parser.cc"
    break;

  case 634:
#line 2179 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3565 "dhcp4_parser.cc"
    break;

  case 635:
#line 2184 "dhcp4_parser.yy"
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-fetch-wait-time", value);
}
#line 3574 "dhcp4_parser.cc"
    break;

  case 636:
#line 2194 "dhcp4_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 3585 "dhcp4_parser.cc"
    break;

  case 637:
#line 2199 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3594 "dhcp4_parser.cc"
    break;

  case 638:
#line 2204 "dhcp4_parser.yy"
    {
    // Parse the Logging map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3604 "dhcp4_parser.cc"
    break;

  case 639:
#line 2208 "dhcp4_parser.yy"
    {
    // parsing completed
}
#line 3612 "dhcp4_parser.cc"
    break;

  case 643:
#line 2224 "dhcp4_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 3623 "dhcp4_parser.cc"
    break;

  case 644:
#line 2229 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3632 "dhcp4_parser.cc"
    break;

  case 647:
#line 2241 "dhcp4_parser.yy"
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 3642 "dhcp4_parser.cc"
    break;

  case 648:
#line 2245 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
}
#line 3650 "dhcp4_parser.cc"
    break;

  case 658:
#line 2262 "dhcp4_parser.yy"
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 3659 "dhcp4_parser.cc"
    break;

  case 659:
#line 2267 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3667 "dhcp4_parser.cc"
    break;

  case 660:
#line 2269 "dhcp4_parser.yy"
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 3677 "dhcp4_parser.cc"
    break;

  case 661:
#line 2275 "dhcp4_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 3688 "dhcp4_parser.cc"
    break;

  case 662:
#line 2280 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3697 "dhcp4_parser.cc"
    break;

  case 665:
#line 2289 "dhcp4_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3707 "dhcp4_parser.cc"
    break;

  case 666:
#line 2293 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
}
#line 3715 "dhcp4_parser.cc"
    break;

  case 673:
#line 2307 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3723 "dhcp4_parser.cc"
    break;

  case 674:
#line 2309 "dhcp4_parser.yy"
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 3733 "dhcp4_parser.cc"
    break;

  case 675:
#line 2315 "dhcp4_parser.yy"
    {
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 3742 "dhcp4_parser.cc"
    break;

  case 676:
#line 2320 "dhcp4_parser.yy"
    {
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 3751 "dhcp4_parser.cc"
    break;

  case 677:
#line 2325 "dhcp4_parser.yy"
    {
    ElementPtr maxver(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxver", maxver);
}
#line 3760 "dhcp4_parser.cc"
    break;


#line 3764 "dhcp4_parser.cc"

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


  const short Dhcp4Parser::yypact_ninf_ = -837;

  const signed char Dhcp4Parser::yytable_ninf_ = -1;

  const short
  Dhcp4Parser::yypact_[] =
  {
     318,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,    50,    21,    74,    86,    90,
     108,   119,   136,   147,   165,   182,   223,   224,   225,   237,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,    21,     5,
      17,   154,    29,    60,    67,   233,   183,    26,   270,   -49,
     515,   111,    58,  -837,   259,   263,   276,   274,   288,  -837,
    -837,  -837,  -837,  -837,   291,  -837,    44,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,   301,   309,   315,  -837,
    -837,  -837,  -837,  -837,  -837,   317,   319,   325,   326,   328,
     329,   336,   344,   345,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,   346,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,    88,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,   354,  -837,    91,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,   356,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,   104,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,   122,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,   284,   366,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,   286,  -837,
    -837,   369,  -837,  -837,  -837,   371,  -837,  -837,   314,   367,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,   372,   373,  -837,  -837,  -837,  -837,   370,
     376,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,   168,  -837,  -837,  -837,   377,  -837,  -837,
     380,  -837,   384,   387,  -837,  -837,   388,   389,  -837,  -837,
    -837,  -837,  -837,   185,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
     218,  -837,  -837,  -837,   390,   239,  -837,  -837,  -837,  -837,
      21,    21,  -837,   207,   392,   395,   397,   403,   404,  -837,
      17,  -837,   405,   407,   408,   243,   244,   245,   409,   411,
     419,   425,   434,   437,   268,   285,   287,   296,   297,   282,
     299,   316,   331,   440,   441,   458,   468,   469,   471,   488,
     489,   498,   499,   502,   503,   504,   337,   508,   509,   510,
     511,   512,   513,   154,  -837,   514,   516,   517,   343,    29,
    -837,   520,   522,   524,   525,   526,   527,   358,   529,   531,
     532,    60,  -837,   535,    67,  -837,   536,   538,   539,   542,
     543,   544,   545,   546,  -837,   233,  -837,   547,   549,   381,
     550,   552,   553,   382,  -837,    26,   555,   386,   391,  -837,
     270,   556,   559,    -3,  -837,   393,   560,   561,   394,   562,
     399,   400,   567,   572,   401,   410,   575,   576,   515,  -837,
     111,  -837,   577,   413,    58,  -837,  -837,  -837,   579,   578,
     581,    21,    21,    21,  -837,   582,   583,   584,  -837,  -837,
    -837,   420,   421,   423,   590,   591,   587,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,   429,   599,   600,   601,
     602,   603,   435,   271,   604,   607,   608,   609,   610,  -837,
     611,   603,   613,   442,   443,   617,  -837,   649,   144,   184,
    -837,  -837,   482,   483,   485,   654,   490,   491,  -837,   649,
     492,   655,  -837,   493,  -837,   649,   494,   495,   496,   497,
     500,   501,   505,  -837,   506,   507,  -837,   518,   519,   521,
    -837,  -837,   523,  -837,  -837,  -837,   528,    21,  -837,  -837,
     530,   533,  -837,   534,  -837,  -837,    14,   444,  -837,  -837,
      65,   537,  -837,  -837,   666,  -837,  -837,    21,   154,   111,
    -837,  -837,  -837,    58,    29,   648,  -837,  -837,  -837,   585,
     585,   668,  -837,   669,   670,   674,   675,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,    31,   676,   677,   678,   171,
      18,  -837,   515,  -837,  -837,   679,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,   680,  -837,  -837,
    -837,  -837,   114,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,   668,  -837,   242,   248,   249,   252,
    -837,   265,  -837,  -837,  -837,  -837,  -837,  -837,   685,   686,
     689,   691,   693,  -837,  -837,  -837,  -837,   694,   695,   696,
     698,   700,  -837,   269,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,   273,  -837,   699,   705,  -837,  -837,
     703,   708,  -837,  -837,   706,   710,  -837,  -837,   709,   711,
    -837,  -837,   712,   713,  -837,  -837,  -837,  -837,  -837,  -837,
      77,  -837,  -837,  -837,  -837,  -837,  -837,  -837,   133,  -837,
    -837,   714,   716,  -837,  -837,   715,   719,  -837,   720,   721,
     722,   723,   724,   725,   290,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,   298,  -837,  -837,
    -837,   300,  -837,   152,  -837,   557,  -837,   717,   728,  -837,
    -837,  -837,  -837,   726,   727,  -837,  -837,  -837,  -837,   731,
     648,  -837,   732,   733,   734,   735,   558,   541,   566,   565,
     568,   739,   740,   741,   742,   573,   574,   580,   586,   588,
     585,  -837,  -837,   585,  -837,   668,    60,  -837,   669,    26,
    -837,   670,   270,  -837,   674,   438,  -837,   675,    31,  -837,
     199,   676,  -837,   233,  -837,   677,   -49,  -837,   678,   589,
     592,   593,   594,   595,   596,   171,  -837,   745,   746,    18,
    -837,  -837,    85,   679,  -837,  -837,   747,   748,    67,  -837,
     680,   751,  -837,  -837,   598,  -837,   330,   605,   606,   612,
    -837,  -837,  -837,  -837,  -837,   614,   615,   618,   620,  -837,
    -837,  -837,  -837,  -837,  -837,   304,  -837,   306,  -837,   744,
    -837,   749,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
     308,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,   752,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,   753,   756,  -837,  -837,  -837,  -837,  -837,   754,
    -837,   312,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
     621,   626,  -837,  -837,   761,  -837,  -837,  -837,  -837,  -837,
     323,  -837,  -837,  -837,  -837,  -837,  -837,   635,   348,  -837,
     649,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,   438,  -837,
     768,   597,  -837,   199,  -837,  -837,  -837,  -837,   770,   640,
     771,    85,  -837,  -837,  -837,  -837,  -837,   636,  -837,  -837,
     772,  -837,   643,  -837,  -837,   769,  -837,  -837,   195,  -837,
     -77,   769,  -837,  -837,   776,   777,   778,   349,  -837,  -837,
    -837,  -837,  -837,  -837,   779,   657,   651,   662,   -77,  -837,
     671,  -837,  -837,  -837,  -837,  -837
  };

  const unsigned short
  Dhcp4Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,    28,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       1,    45,    38,    34,    33,    30,    31,    32,    37,     3,
      35,    36,    58,     5,    70,     7,   141,     9,   284,    11,
     449,    13,   474,    15,   374,    17,   382,    19,   419,    21,
     249,    23,   566,    25,   638,    27,   627,    29,    47,    41,
       0,     0,     0,     0,     0,   476,     0,   384,   421,     0,
       0,     0,     0,    49,     0,    48,     0,     0,    42,    68,
     636,   619,   621,   623,     0,    67,     0,    60,    62,    64,
      65,    66,    63,   625,   130,   156,     0,     0,     0,   495,
     497,   499,   154,   163,   165,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   125,   276,   372,   411,   338,   462,
     464,   331,   227,   523,   466,   241,   260,     0,   549,   562,
     564,   615,   617,   643,   115,     0,    72,    74,    75,    76,
      77,    78,   109,   110,   111,    79,   107,    96,    97,    98,
      82,    83,   104,    84,    85,    86,    90,    91,    80,   108,
      81,    88,    89,   102,   103,   105,    99,   100,   101,    87,
      92,    93,    94,    95,   113,   114,   106,   112,   143,   145,
     149,     0,   140,     0,   132,   134,   135,   136,   137,   138,
     139,   319,   321,   323,   441,   317,   325,     0,   329,   327,
     519,   316,   288,   289,   290,   291,   292,   313,   314,   315,
     303,   304,     0,   286,   295,   308,   309,   310,   296,   298,
     299,   301,   297,   293,   294,   311,   312,   300,   305,   306,
     307,   302,   460,   459,   455,   456,   454,     0,   451,   453,
     457,   458,   517,   505,   507,   511,   509,   515,   513,   501,
     494,   488,   492,   493,     0,   477,   478,   489,   490,   491,
     485,   480,   486,   482,   483,   484,   487,   481,     0,   401,
     208,     0,   405,   403,   408,     0,   397,   398,     0,   385,
     386,   388,   400,   389,   390,   391,   407,   392,   393,   394,
     395,   396,   435,     0,     0,   433,   434,   437,   438,     0,
     422,   423,   425,   426,   427,   428,   429,   430,   431,   432,
     256,   258,   253,     0,   251,   254,   255,     0,   589,   591,
       0,   594,     0,     0,   598,   602,     0,     0,   606,   613,
     587,   585,   586,     0,   568,   570,   571,   572,   573,   574,
     575,   576,   577,   578,   579,   580,   581,   582,   583,   584,
       0,   640,   642,   633,     0,     0,   629,   631,   632,    46,
       0,     0,    39,     0,     0,     0,     0,     0,     0,    57,
       0,    59,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    71,     0,     0,     0,     0,     0,
     142,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,   285,     0,     0,   450,     0,     0,     0,     0,
       0,     0,     0,     0,   475,     0,   375,     0,     0,     0,
       0,     0,     0,     0,   383,     0,     0,     0,     0,   420,
       0,     0,     0,     0,   250,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   567,
       0,   639,     0,     0,     0,   628,    50,    43,     0,     0,
       0,     0,     0,     0,    61,     0,     0,     0,   127,   128,
     129,     0,     0,     0,     0,     0,     0,   116,   117,   118,
     119,   120,   121,   122,   123,   124,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   548,
       0,     0,     0,     0,     0,     0,    73,     0,     0,     0,
     153,   133,     0,     0,     0,     0,     0,     0,   337,     0,
       0,     0,   287,     0,   452,     0,     0,     0,     0,     0,
       0,     0,     0,   479,     0,     0,   399,     0,     0,     0,
     410,   387,     0,   439,   440,   424,     0,     0,   252,   588,
       0,     0,   593,     0,   596,   597,     0,     0,   604,   605,
       0,     0,   569,   641,     0,   635,   630,     0,     0,     0,
     620,   622,   624,     0,     0,     0,   496,   498,   500,     0,
       0,   167,   126,   278,   376,   413,   340,    40,   463,   465,
     333,   334,   335,   336,   332,     0,     0,   468,   243,     0,
       0,   563,     0,   616,   618,     0,    51,   144,   147,   148,
     146,   151,   152,   150,   320,   322,   324,   443,   318,   326,
     330,   328,     0,   461,   518,   506,   508,   512,   510,   516,
     514,   502,   402,   209,   406,   404,   409,   436,   257,   259,
     590,   592,   595,   600,   601,   599,   603,   608,   609,   610,
     611,   612,   607,   614,   167,    44,     0,     0,     0,     0,
     161,     0,   158,   160,   195,   201,   203,   205,     0,     0,
       0,     0,     0,   217,   219,   221,   223,     0,     0,     0,
       0,     0,   194,     0,   173,   175,   176,   177,   178,   179,
     180,   181,   182,   183,   184,   188,   189,   190,   185,   191,
     192,   193,   186,   187,     0,   171,     0,   168,   169,   282,
       0,   279,   280,   380,     0,   377,   378,   417,     0,   414,
     415,   344,     0,   341,   342,   236,   237,   238,   239,   240,
       0,   229,   231,   232,   233,   234,   235,   527,     0,   525,
     472,     0,   469,   470,   247,     0,   244,   245,     0,     0,
       0,     0,     0,     0,     0,   262,   264,   265,   266,   267,
     268,   269,   558,   560,   557,   555,   556,     0,   551,   553,
     554,     0,   647,     0,   645,    53,   447,     0,   444,   445,
     503,   521,   522,     0,     0,    69,   637,   626,   131,     0,
       0,   157,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,   155,   164,     0,   166,     0,     0,   277,     0,   384,
     373,     0,   421,   412,     0,     0,   339,     0,     0,   228,
     529,     0,   524,   476,   467,     0,     0,   242,     0,     0,
       0,     0,     0,     0,     0,     0,   261,     0,     0,     0,
     550,   565,     0,     0,   644,    55,     0,    54,     0,   442,
       0,     0,   520,   634,     0,   159,     0,     0,     0,     0,
     207,   210,   211,   212,   213,     0,     0,     0,     0,   225,
     226,   214,   215,   216,   174,     0,   170,     0,   281,     0,
     379,     0,   416,   371,   363,   364,   365,   351,   352,   368,
     369,   370,   354,   355,   348,   349,   350,   361,   362,   360,
       0,   346,   353,   366,   367,   356,   357,   358,   359,   343,
     230,   545,     0,   543,   544,   536,   537,   541,   542,   538,
     539,   540,     0,   530,   531,   533,   534,   535,   526,     0,
     471,     0,   246,   270,   271,   272,   273,   274,   275,   263,
       0,     0,   552,   661,     0,   659,   657,   651,   655,   656,
       0,   649,   653,   654,   652,   646,    52,     0,     0,   446,
       0,   162,   197,   198,   199,   200,   196,   202,   204,   206,
     218,   220,   222,   224,   172,   283,   381,   418,     0,   345,
       0,     0,   528,     0,   473,   248,   559,   561,     0,     0,
       0,     0,   648,    56,   448,   504,   347,     0,   547,   532,
       0,   658,     0,   650,   546,     0,   660,   665,     0,   663,
       0,     0,   662,   673,     0,     0,     0,     0,   667,   669,
     670,   671,   672,   664,     0,     0,     0,     0,     0,   666,
       0,   675,   676,   677,   668,   674
  };

  const short
  Dhcp4Parser::yypgoto_[] =
  {
    -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,   -46,  -837,  -466,  -837,
     311,  -837,  -837,  -837,  -837,  -837,  -837,  -534,  -837,  -837,
    -837,   -70,  -837,  -837,  -837,   459,  -837,  -837,  -837,  -837,
     176,   422,   -55,   -54,   -27,   -24,    -9,     6,     9,    11,
    -837,  -837,  -837,  -837,    12,    19,  -837,  -837,   228,   432,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,    52,  -837,  -837,  -837,
    -837,  -837,  -837,   186,  -837,    28,  -837,  -607,    35,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,   -35,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,    20,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,     8,  -837,  -837,  -837,    13,   417,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,     7,  -837,  -837,  -837,  -837,  -837,
    -837,  -836,  -837,  -837,  -837,    36,  -837,  -837,  -837,    39,
     455,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -828,
    -837,   -17,  -837,    -5,  -837,    22,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,    30,  -837,  -837,  -130,   -65,  -837,  -837,
    -837,  -837,  -837,    38,  -837,  -837,  -837,    41,  -837,   436,
    -837,   -72,  -837,  -837,  -837,  -837,  -837,   -66,  -837,  -837,
    -837,  -837,  -837,    -7,  -837,  -837,  -837,    40,  -837,  -837,
    -837,    43,  -837,   433,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,     2,  -837,  -837,  -837,    10,
     462,  -837,  -837,   -39,  -837,   -19,  -837,   -59,  -837,  -837,
    -837,    32,  -837,  -837,  -837,    37,  -837,   454,   -58,  -837,
     -52,  -837,    -1,  -837,   250,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,  -825,  -837,  -837,  -837,  -837,  -837,    42,  -837,
    -837,  -837,  -122,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,    25,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,   275,   427,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,   -64,  -837,   -60,  -837,
    -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,  -837,
     303,   424,  -837,  -837,  -837,  -837,  -837,  -837,  -837,   310,
     430,   -57,  -837,  -837,    33,  -837,  -837,  -120,  -837,  -837,
    -837,  -837,  -837,  -837,  -139,  -837,  -837,  -155,  -837,  -837,
    -837,  -837,  -837
  };

  const short
  Dhcp4Parser::yydefgoto_[] =
  {
      -1,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    38,    39,    40,    69,
     628,    87,    88,    41,    68,    84,    85,   647,   815,   896,
     897,   722,    43,    70,    96,    97,    98,   374,    45,    71,
     145,   146,   147,   148,   149,   150,   151,   152,   153,   154,
     155,   156,   403,   157,   158,   159,   160,   383,   193,   194,
      47,    72,   195,   425,   196,   426,   650,   197,   427,   653,
     198,   161,   391,   162,   384,   701,   702,   703,   829,   163,
     392,   164,   393,   746,   747,   748,   853,   723,   724,   725,
     832,  1016,   726,   833,   727,   834,   728,   835,   729,   730,
     458,   731,   732,   733,   734,   735,   736,   737,   738,   841,
     739,   842,   740,   843,   741,   844,   742,   743,   165,   411,
     770,   771,   772,   773,   774,   775,   776,   166,   414,   785,
     786,   787,   876,    61,    79,   323,   324,   325,   471,   326,
     472,   167,   415,   794,   795,   796,   797,   798,   799,   800,
     801,   168,   404,   750,   751,   752,   856,    49,    73,   222,
     223,   224,   435,   225,   431,   226,   432,   227,   433,   228,
     436,   229,   439,   230,   438,   169,   410,   634,   232,   170,
     407,   762,   763,   764,   865,   950,   951,   171,   405,    55,
      76,   754,   755,   756,   859,    57,    77,   288,   289,   290,
     291,   292,   293,   294,   457,   295,   461,   296,   460,   297,
     298,   462,   299,   172,   406,   758,   759,   760,   862,    59,
      78,   309,   310,   311,   312,   313,   466,   314,   315,   316,
     317,   234,   434,   817,   818,   819,   898,    51,    74,   247,
     248,   249,   443,   173,   408,   174,   409,   175,   413,   781,
     782,   783,   873,    53,    75,   264,   265,   266,   176,   388,
     177,   389,   178,   390,   270,   453,   822,   901,   271,   447,
     272,   448,   273,   450,   274,   449,   275,   452,   276,   451,
     277,   446,   241,   440,   823,   179,   412,   778,   779,   870,
     972,   973,   974,   975,   976,  1030,   977,   180,   181,   417,
     807,   808,   809,   887,   810,   888,   182,   418,   183,   419,
      63,    80,   343,   344,   345,   346,   476,   347,   477,   348,
     349,   479,   350,   351,   352,   482,   685,   353,   483,   354,
     355,   356,   486,   692,   357,   487,   184,   420,   185,   421,
      99,   376,   100,   377,   101,   378,   186,   382,    67,    82,
     365,   366,   367,   492,   368,   102,   375,    65,    81,   360,
     361,   187,   422,   813,   814,   892,  1000,  1001,  1002,  1003,
    1040,  1004,  1038,  1058,  1059,  1060,  1067,  1068,  1069,  1074,
    1070,  1071,  1072
  };

  const unsigned short
  Dhcp4Parser::yytable_[] =
  {
      95,   144,   192,   211,   243,   260,   307,   286,   305,   322,
     340,   278,   308,   744,   237,   238,   358,   267,   212,   213,
     359,   239,    83,   268,   362,   660,    31,    89,    32,   945,
      33,   664,   683,   199,   235,   250,   262,   946,   300,   318,
     958,   341,   287,   306,   188,   189,   214,   380,   190,   215,
      30,   191,   381,   200,   236,   251,   263,   244,   301,   319,
     279,   342,   320,   321,   216,   627,   233,   246,   261,   245,
     363,   364,   240,  1063,   269,   627,  1064,  1065,  1066,   217,
     868,    42,   218,   869,   219,   220,   107,   108,   109,   110,
     111,   423,   221,    44,   429,   231,   424,    46,   280,   430,
     281,   282,   129,   130,   283,   284,   285,   441,   320,   321,
     129,   130,   442,   129,   130,    48,   115,   116,   117,   118,
     119,   120,   121,   122,    94,   444,    50,   201,   202,   203,
     445,   127,   765,   766,   767,   768,   871,   769,   127,   872,
     802,   803,   204,    52,   129,   130,   205,   206,   207,   131,
     242,   129,   130,   684,    54,   893,   208,   280,   894,   209,
     134,   648,   649,   208,    90,   103,   209,   210,   104,   129,
     130,   473,    56,    91,    92,    93,   474,   105,    86,   106,
     107,   108,   109,   110,   111,   112,   113,   114,   488,    58,
      94,    94,   945,   489,    34,    35,    36,    37,  1061,    94,
     946,  1062,    94,   958,   651,   652,   687,   688,   689,   690,
     115,   116,   117,   118,   119,   120,   121,   122,   123,   124,
     125,   490,   259,   820,   126,   127,   491,   109,   110,   111,
      60,    62,    64,    94,   993,   128,   994,   995,   129,   130,
      94,   691,   494,   131,    66,   423,   925,   495,   132,   133,
     825,   490,   494,   126,   134,   429,   826,   827,    94,   143,
     828,   109,   110,   111,   135,   369,   370,   136,   830,   126,
     127,   280,   850,   831,   137,   138,   850,   851,   139,   140,
     371,   852,   372,   129,   130,   788,   789,   790,   791,   792,
     793,   373,   454,   885,   456,   379,   961,   962,   886,   141,
     142,   889,   143,   488,   127,   385,   890,   850,   891,   441,
      95,  1028,  1024,   386,  1025,   473,  1029,   129,   130,   387,
    1035,   394,   464,   395,   496,   497,  1041,    94,   252,   396,
     397,  1042,   398,   399,   253,   254,   255,   256,   257,   258,
     400,   259,   280,   302,   281,   282,   303,   304,   401,   402,
     416,   444,  1078,   144,   129,   130,  1044,  1079,   428,   192,
     437,   630,   631,   632,   633,  1012,  1013,  1014,  1015,   455,
     465,   211,    94,   459,   243,   463,   467,   468,   469,   470,
     498,   475,   237,   238,   478,   260,   212,   213,   480,   239,
     199,   481,   484,   485,   493,   286,   499,   267,   307,   500,
     305,   501,   235,   268,   308,   250,    94,   502,   503,   505,
     200,   506,   507,   511,   214,   512,   262,   215,   340,   508,
     509,   510,   236,   513,   358,   251,   300,   244,   359,   514,
     287,   318,   216,   362,   233,   306,   263,   246,   515,   245,
     240,   516,   517,    94,   526,   527,   301,   217,   261,   341,
     218,   319,   219,   220,   269,   610,   611,   612,   522,   518,
     221,   519,   528,   231,   107,   108,   109,   110,   111,   342,
     520,   521,   529,   530,   523,   531,  1045,     1,     2,     3,
       4,     5,     6,     7,     8,     9,    10,    11,    12,    13,
      14,   524,   532,   533,   115,   116,   117,   118,   119,   120,
     121,   122,   534,   535,   125,   525,   536,   537,   538,   127,
     280,   539,   540,   541,   542,   543,   544,   545,   547,   550,
     548,   549,   129,   130,   552,   206,   553,   131,   554,   555,
     556,   557,   558,   559,   208,   560,   561,   209,   144,   563,
     565,   679,   566,   567,   192,   210,   568,   569,   570,   571,
     572,   574,   362,   575,   577,   576,   578,   579,   580,   582,
     586,   695,   583,   587,   590,   591,   593,   584,   592,   589,
     804,   596,   340,   594,   595,   199,   597,   598,   358,   600,
     601,   604,   359,   607,   686,   608,   599,   605,   609,   613,
     614,   615,   621,   616,   617,   200,   618,   619,   620,   129,
     130,   805,   622,   341,   623,   624,   625,   626,   629,   635,
      32,    94,   636,   637,   638,   643,   644,   639,   640,   704,
     642,   806,   645,   342,   705,   706,   707,   708,   709,   710,
     711,   712,   713,   714,   715,   716,   717,   718,   719,   720,
     721,   327,   328,   329,   330,   331,   332,   333,   334,   335,
     336,   337,   338,   339,   646,   654,   655,   280,   656,   657,
     141,   142,   662,   658,   659,   661,   663,   665,   666,   667,
     668,   694,   700,   669,   670,   745,   749,   753,   671,   672,
     673,   757,   761,   777,   780,   784,   812,   816,    94,   836,
     837,   674,   675,   838,   676,   839,   677,   840,   845,   846,
     847,   678,   848,   680,   849,   854,   681,   682,   855,   857,
     693,   858,   860,   861,   864,   863,   867,   911,   866,   875,
     874,   877,   878,   899,   879,   880,   881,   882,   883,   884,
     895,   900,   910,   903,   902,   904,   906,   907,   908,   909,
     912,   913,   914,   915,   916,   917,   918,   919,   920,   990,
     991,  1007,  1026,  1006,   921,  1010,  1031,  1027,    94,  1033,
     922,  1032,  1034,   983,   923,  1039,   984,   985,   986,   987,
     988,  1011,  1047,  1048,  1050,  1052,  1057,  1055,  1017,  1018,
    1075,  1076,  1077,  1080,   696,  1019,   211,  1020,  1021,   286,
     307,  1022,   305,  1023,  1036,   933,   308,   237,   238,  1037,
     963,   212,   213,   260,   239,   965,   322,   955,  1043,  1054,
     934,   935,   969,   956,  1051,   267,  1056,   235,   970,   804,
     300,   268,   996,   318,   287,  1082,   953,   306,   243,   214,
     944,   967,   215,  1081,   262,   964,  1083,   236,   936,   504,
     301,   937,   699,   319,  1085,   546,   954,   216,   947,   233,
     805,   968,   641,   998,   263,   240,   938,   997,   952,   250,
     948,   551,   217,   966,   957,   218,   261,   219,   220,   971,
     806,   939,   269,   999,   940,   221,   941,   942,   231,   251,
     824,   244,   905,   926,   943,   924,   982,   949,   960,   981,
     588,   246,   989,   245,   928,   927,   562,   959,  1046,   930,
     929,   581,  1009,   585,   932,   931,   564,   980,  1008,   573,
     979,  1049,   821,   978,   992,   602,   698,   811,   606,   697,
     603,  1053,  1073,  1084,     0,     0,  1005,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   933,     0,
       0,     0,     0,   963,     0,     0,     0,     0,   965,     0,
     955,   996,     0,   934,   935,   969,   956,     0,     0,     0,
       0,   970,     0,     0,     0,     0,     0,     0,     0,   953,
       0,     0,     0,   944,   967,     0,     0,     0,   964,     0,
       0,   936,   998,     0,   937,     0,   997,     0,     0,   954,
       0,   947,     0,     0,   968,     0,     0,     0,     0,   938,
       0,   952,   999,   948,     0,     0,   966,   957,     0,     0,
       0,     0,   971,     0,   939,     0,     0,   940,     0,   941,
     942,     0,     0,     0,     0,     0,     0,   943,     0,     0,
     949
  };

  const short
  Dhcp4Parser::yycheck_[] =
  {
      70,    71,    72,    73,    74,    75,    78,    77,    78,    79,
      80,    76,    78,   620,    73,    73,    80,    75,    73,    73,
      80,    73,    68,    75,    81,   559,     5,    10,     7,   865,
       9,   565,    18,    72,    73,    74,    75,   865,    77,    78,
     865,    80,    77,    78,    15,    16,    73,     3,    19,    73,
       0,    22,     8,    72,    73,    74,    75,    74,    77,    78,
      34,    80,   111,   112,    73,   531,    73,    74,    75,    74,
      12,    13,    73,   150,    75,   541,   153,   154,   155,    73,
       3,     7,    73,     6,    73,    73,    26,    27,    28,    29,
      30,     3,    73,     7,     3,    73,     8,     7,    72,     8,
      74,    75,    84,    85,    78,    79,    80,     3,   111,   112,
      84,    85,     8,    84,    85,     7,    56,    57,    58,    59,
      60,    61,    62,    63,   173,     3,     7,    67,    68,    69,
       8,    71,   101,   102,   103,   104,     3,   106,    71,     6,
     122,   123,    82,     7,    84,    85,    86,    87,    88,    89,
      83,    84,    85,   139,     7,     3,    96,    72,     6,    99,
     100,    17,    18,    96,   147,    11,    99,   107,    14,    84,
      85,     3,     7,   156,   157,   158,     8,    23,   173,    25,
      26,    27,    28,    29,    30,    31,    32,    33,     3,     7,
     173,   173,  1028,     8,   173,   174,   175,   176,     3,   173,
    1028,     6,   173,  1028,    20,    21,   141,   142,   143,   144,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,     3,   108,   109,    70,    71,     8,    28,    29,    30,
       7,     7,     7,   173,   149,    81,   151,   152,    84,    85,
     173,   176,     3,    89,     7,     3,   853,     8,    94,    95,
       8,     3,     3,    70,   100,     3,     8,     8,   173,   148,
       8,    28,    29,    30,   110,     6,     3,   113,     3,    70,
      71,    72,     3,     8,   120,   121,     3,     8,   124,   125,
       4,     8,     8,    84,    85,   114,   115,   116,   117,   118,
     119,     3,     8,     3,     8,     4,    97,    98,     8,   145,
     146,     3,   148,     3,    71,     4,     8,     3,     8,     3,
     380,     3,     8,     4,     8,     3,     8,    84,    85,     4,
       8,     4,     8,     4,   370,   371,     3,   173,    95,     4,
       4,     8,     4,     4,   101,   102,   103,   104,   105,   106,
       4,   108,    72,    73,    74,    75,    76,    77,     4,     4,
       4,     3,     3,   423,    84,    85,     8,     8,     4,   429,
       4,    90,    91,    92,    93,    35,    36,    37,    38,     3,
       3,   441,   173,     4,   444,     4,     4,     4,     8,     3,
     173,     4,   441,   441,     4,   455,   441,   441,     4,   441,
     429,     4,     4,     4,     4,   465,     4,   455,   470,     4,
     470,     4,   441,   455,   470,   444,   173,     4,     4,     4,
     429,     4,     4,     4,   441,     4,   455,   441,   488,   176,
     176,   176,   441,     4,   488,   444,   465,   444,   488,     4,
     465,   470,   441,   490,   441,   470,   455,   444,     4,   444,
     441,     4,   174,   173,     4,     4,   465,   441,   455,   488,
     441,   470,   441,   441,   455,   501,   502,   503,   176,   174,
     441,   174,     4,   441,    26,    27,    28,    29,    30,   488,
     174,   174,     4,     4,   175,     4,  1010,   159,   160,   161,
     162,   163,   164,   165,   166,   167,   168,   169,   170,   171,
     172,   175,     4,     4,    56,    57,    58,    59,    60,    61,
      62,    63,     4,     4,    66,   174,     4,     4,     4,    71,
      72,   174,     4,     4,     4,     4,     4,     4,     4,   176,
       4,     4,    84,    85,     4,    87,     4,    89,     4,     4,
       4,     4,   174,     4,    96,     4,     4,    99,   608,     4,
       4,   587,     4,     4,   614,   107,     4,     4,     4,     4,
       4,     4,   609,     4,     4,   174,     4,     4,   176,     4,
       4,   607,   176,     4,     4,     4,     4,   176,   174,   176,
     640,     4,   642,   174,   174,   614,     4,   176,   642,     4,
       4,     4,   642,     4,   140,     7,   176,   174,     7,     7,
       7,     7,     5,   173,   173,   614,   173,     7,     7,    84,
      85,   640,   173,   642,     5,     5,     5,     5,   173,     5,
       7,   173,     5,     5,     5,   173,   173,     7,     7,    34,
       7,   640,     5,   642,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,   126,   127,   128,   129,   130,   131,   132,   133,   134,
     135,   136,   137,   138,     5,   173,   173,    72,   173,     5,
     145,   146,     7,   173,   173,   173,   173,   173,   173,   173,
     173,     5,    24,   173,   173,     7,     7,     7,   173,   173,
     173,     7,     7,     7,     7,     7,     7,     7,   173,     4,
       4,   173,   173,     4,   173,     4,   173,     4,     4,     4,
       4,   173,     4,   173,     4,     6,   173,   173,     3,     6,
     173,     3,     6,     3,     3,     6,     3,   176,     6,     3,
       6,     6,     3,     6,     4,     4,     4,     4,     4,     4,
     173,     3,   174,     6,     8,     4,     4,     4,     4,     4,
     174,   176,   174,     4,     4,     4,     4,   174,   174,     4,
       4,     3,     8,     6,   174,     4,     4,     8,   173,     3,
     174,     8,     8,   174,   176,     4,   174,   174,   174,   174,
     174,   173,     4,   176,     4,     4,     7,     5,   173,   173,
       4,     4,     4,     4,   608,   173,   856,   173,   173,   859,
     862,   173,   862,   173,   173,   865,   862,   856,   856,   173,
     870,   856,   856,   873,   856,   870,   876,   865,   173,   173,
     865,   865,   870,   865,   174,   873,   173,   856,   870,   889,
     859,   873,   892,   862,   859,   174,   865,   862,   898,   856,
     865,   870,   856,   176,   873,   870,   174,   856,   865,   380,
     859,   865,   614,   862,   173,   423,   865,   856,   865,   856,
     889,   870,   541,   892,   873,   856,   865,   892,   865,   898,
     865,   429,   856,   870,   865,   856,   873,   856,   856,   870,
     889,   865,   873,   892,   865,   856,   865,   865,   856,   898,
     694,   898,   830,   855,   865,   850,   878,   865,   868,   876,
     473,   898,   885,   898,   858,   856,   441,   867,  1028,   861,
     859,   465,   900,   470,   864,   862,   444,   875,   898,   455,
     873,  1033,   662,   871,   889,   488,   613,   642,   494,   609,
     490,  1041,  1061,  1078,    -1,    -1,   893,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1028,    -1,
      -1,    -1,    -1,  1033,    -1,    -1,    -1,    -1,  1033,    -1,
    1028,  1041,    -1,  1028,  1028,  1033,  1028,    -1,    -1,    -1,
      -1,  1033,    -1,    -1,    -1,    -1,    -1,    -1,    -1,  1028,
      -1,    -1,    -1,  1028,  1033,    -1,    -1,    -1,  1033,    -1,
      -1,  1028,  1041,    -1,  1028,    -1,  1041,    -1,    -1,  1028,
      -1,  1028,    -1,    -1,  1033,    -1,    -1,    -1,    -1,  1028,
      -1,  1028,  1041,  1028,    -1,    -1,  1033,  1028,    -1,    -1,
      -1,    -1,  1033,    -1,  1028,    -1,    -1,  1028,    -1,  1028,
    1028,    -1,    -1,    -1,    -1,    -1,    -1,  1028,    -1,    -1,
    1028
  };

  const unsigned short
  Dhcp4Parser::yystos_[] =
  {
       0,   159,   160,   161,   162,   163,   164,   165,   166,   167,
     168,   169,   170,   171,   172,   178,   179,   180,   181,   182,
     183,   184,   185,   186,   187,   188,   189,   190,   191,   192,
       0,     5,     7,     9,   173,   174,   175,   176,   193,   194,
     195,   200,     7,   209,     7,   215,     7,   237,     7,   334,
       7,   414,     7,   430,     7,   366,     7,   372,     7,   396,
       7,   310,     7,   487,     7,   534,     7,   525,   201,   196,
     210,   216,   238,   335,   415,   431,   367,   373,   397,   311,
     488,   535,   526,   193,   202,   203,   173,   198,   199,    10,
     147,   156,   157,   158,   173,   208,   211,   212,   213,   517,
     519,   521,   532,    11,    14,    23,    25,    26,    27,    28,
      29,    30,    31,    32,    33,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    70,    71,    81,    84,
      85,    89,    94,    95,   100,   110,   113,   120,   121,   124,
     125,   145,   146,   148,   208,   217,   218,   219,   220,   221,
     222,   223,   224,   225,   226,   227,   228,   230,   231,   232,
     233,   248,   250,   256,   258,   295,   304,   318,   328,   352,
     356,   364,   390,   420,   422,   424,   435,   437,   439,   462,
     474,   475,   483,   485,   513,   515,   523,   538,    15,    16,
      19,    22,   208,   235,   236,   239,   241,   244,   247,   420,
     422,    67,    68,    69,    82,    86,    87,    88,    96,    99,
     107,   208,   219,   220,   221,   222,   223,   224,   225,   226,
     231,   232,   336,   337,   338,   340,   342,   344,   346,   348,
     350,   352,   355,   390,   408,   420,   422,   424,   435,   437,
     439,   459,    83,   208,   348,   350,   390,   416,   417,   418,
     420,   422,    95,   101,   102,   103,   104,   105,   106,   108,
     208,   390,   420,   422,   432,   433,   434,   435,   437,   439,
     441,   445,   447,   449,   451,   453,   455,   457,   364,    34,
      72,    74,    75,    78,    79,    80,   208,   276,   374,   375,
     376,   377,   378,   379,   380,   382,   384,   386,   387,   389,
     420,   422,    73,    76,    77,   208,   276,   378,   384,   398,
     399,   400,   401,   402,   404,   405,   406,   407,   420,   422,
     111,   112,   208,   312,   313,   314,   316,   126,   127,   128,
     129,   130,   131,   132,   133,   134,   135,   136,   137,   138,
     208,   420,   422,   489,   490,   491,   492,   494,   496,   497,
     499,   500,   501,   504,   506,   507,   508,   511,   513,   515,
     536,   537,   538,    12,    13,   527,   528,   529,   531,     6,
       3,     4,     8,     3,   214,   533,   518,   520,   522,     4,
       3,     8,   524,   234,   251,     4,     4,     4,   436,   438,
     440,   249,   257,   259,     4,     4,     4,     4,     4,     4,
       4,     4,     4,   229,   329,   365,   391,   357,   421,   423,
     353,   296,   463,   425,   305,   319,     4,   476,   484,   486,
     514,   516,   539,     3,     8,   240,   242,   245,     4,     3,
       8,   341,   343,   345,   409,   339,   347,     4,   351,   349,
     460,     3,     8,   419,     3,     8,   458,   446,   448,   452,
     450,   456,   454,   442,     8,     3,     8,   381,   277,     4,
     385,   383,   388,     4,     8,     3,   403,     4,     4,     8,
       3,   315,   317,     3,     8,     4,   493,   495,     4,   498,
       4,     4,   502,   505,     4,     4,   509,   512,     3,     8,
       3,     8,   530,     4,     3,     8,   193,   193,   173,     4,
       4,     4,     4,     4,   212,     4,     4,     4,   176,   176,
     176,     4,     4,     4,     4,     4,     4,   174,   174,   174,
     174,   174,   176,   175,   175,   174,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,     4,     4,   174,
       4,     4,     4,     4,     4,     4,   218,     4,     4,     4,
     176,   236,     4,     4,     4,     4,     4,     4,   174,     4,
       4,     4,   337,     4,   417,     4,     4,     4,     4,     4,
       4,     4,     4,   434,     4,     4,   174,     4,     4,     4,
     176,   376,     4,   176,   176,   400,     4,     4,   313,   176,
       4,     4,   174,     4,   174,   174,     4,     4,   176,   176,
       4,     4,   490,   537,     4,   174,   528,     4,     7,     7,
     193,   193,   193,     7,     7,     7,   173,   173,   173,     7,
       7,     5,   173,     5,     5,     5,     5,   195,   197,   173,
      90,    91,    92,    93,   354,     5,     5,     5,     5,     7,
       7,   197,     7,   173,   173,     5,     5,   204,    17,    18,
     243,    20,    21,   246,   173,   173,   173,     5,   173,   173,
     204,   173,     7,   173,   204,   173,   173,   173,   173,   173,
     173,   173,   173,   173,   173,   173,   173,   173,   173,   193,
     173,   173,   173,    18,   139,   503,   140,   141,   142,   143,
     144,   176,   510,   173,     5,   193,   217,   536,   527,   235,
      24,   252,   253,   254,    34,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    51,    52,    53,
      54,    55,   208,   264,   265,   266,   269,   271,   273,   275,
     276,   278,   279,   280,   281,   282,   283,   284,   285,   287,
     289,   291,   293,   294,   264,     7,   260,   261,   262,     7,
     330,   331,   332,     7,   368,   369,   370,     7,   392,   393,
     394,     7,   358,   359,   360,   101,   102,   103,   104,   106,
     297,   298,   299,   300,   301,   302,   303,     7,   464,   465,
       7,   426,   427,   428,     7,   306,   307,   308,   114,   115,
     116,   117,   118,   119,   320,   321,   322,   323,   324,   325,
     326,   327,   122,   123,   208,   420,   422,   477,   478,   479,
     481,   489,     7,   540,   541,   205,     7,   410,   411,   412,
     109,   441,   443,   461,   260,     8,     8,     8,     8,   255,
       3,     8,   267,   270,   272,   274,     4,     4,     4,     4,
       4,   286,   288,   290,   292,     4,     4,     4,     4,     4,
       3,     8,     8,   263,     6,     3,   333,     6,     3,   371,
       6,     3,   395,     6,     3,   361,     6,     3,     3,     6,
     466,     3,     6,   429,     6,     3,   309,     6,     3,     4,
       4,     4,     4,     4,     4,     3,     8,   480,   482,     3,
       8,     8,   542,     3,     6,   173,   206,   207,   413,     6,
       3,   444,     8,     6,     4,   253,     4,     4,     4,     4,
     174,   176,   174,   176,   174,     4,     4,     4,     4,   174,
     174,   174,   174,   176,   265,   264,   262,   336,   332,   374,
     370,   398,   394,   208,   219,   220,   221,   222,   223,   224,
     225,   226,   231,   232,   276,   328,   346,   348,   350,   352,
     362,   363,   390,   420,   422,   435,   437,   439,   459,   360,
     298,    97,    98,   208,   276,   364,   390,   420,   422,   435,
     437,   439,   467,   468,   469,   470,   471,   473,   465,   432,
     428,   312,   308,   174,   174,   174,   174,   174,   174,   321,
       4,     4,   478,   149,   151,   152,   208,   276,   420,   422,
     543,   544,   545,   546,   548,   541,     6,     3,   416,   412,
       4,   173,    35,    36,    37,    38,   268,   173,   173,   173,
     173,   173,   173,   173,     8,     8,     8,     8,     3,     8,
     472,     4,     8,     3,     8,     8,   173,   173,   549,     4,
     547,     3,     8,   173,     8,   204,   363,     4,   176,   469,
       4,   174,     4,   544,   173,     5,   173,     7,   550,   551,
     552,     3,     6,   150,   153,   154,   155,   553,   554,   555,
     557,   558,   559,   551,   556,     4,     4,     4,     3,     8,
       4,   176,   174,   174,   554,   173
  };

  const unsigned short
  Dhcp4Parser::yyr1_[] =
  {
       0,   177,   179,   178,   180,   178,   181,   178,   182,   178,
     183,   178,   184,   178,   185,   178,   186,   178,   187,   178,
     188,   178,   189,   178,   190,   178,   191,   178,   192,   178,
     193,   193,   193,   193,   193,   193,   193,   194,   196,   195,
     197,   198,   198,   199,   199,   201,   200,   202,   202,   203,
     203,   205,   204,   206,   206,   207,   207,   208,   210,   209,
     211,   211,   212,   212,   212,   212,   212,   212,   214,   213,
     216,   215,   217,   217,   218,   218,   218,   218,   218,   218,
     218,   218,   218,   218,   218,   218,   218,   218,   218,   218,
     218,   218,   218,   218,   218,   218,   218,   218,   218,   218,
     218,   218,   218,   218,   218,   218,   218,   218,   218,   218,
     218,   218,   218,   218,   218,   218,   219,   220,   221,   222,
     223,   224,   225,   226,   227,   229,   228,   230,   231,   232,
     234,   233,   235,   235,   236,   236,   236,   236,   236,   236,
     236,   238,   237,   240,   239,   242,   241,   243,   243,   245,
     244,   246,   246,   247,   249,   248,   251,   250,   252,   252,
     253,   255,   254,   257,   256,   259,   258,   260,   260,   261,
     261,   263,   262,   264,   264,   265,   265,   265,   265,   265,
     265,   265,   265,   265,   265,   265,   265,   265,   265,   265,
     265,   265,   265,   265,   265,   267,   266,   268,   268,   268,
     268,   270,   269,   272,   271,   274,   273,   275,   277,   276,
     278,   279,   280,   281,   282,   283,   284,   286,   285,   288,
     287,   290,   289,   292,   291,   293,   294,   296,   295,   297,
     297,   298,   298,   298,   298,   298,   299,   300,   301,   302,
     303,   305,   304,   306,   306,   307,   307,   309,   308,   311,
     310,   312,   312,   312,   313,   313,   315,   314,   317,   316,
     319,   318,   320,   320,   321,   321,   321,   321,   321,   321,
     322,   323,   324,   325,   326,   327,   329,   328,   330,   330,
     331,   331,   333,   332,   335,   334,   336,   336,   337,   337,
     337,   337,   337,   337,   337,   337,   337,   337,   337,   337,
     337,   337,   337,   337,   337,   337,   337,   337,   337,   337,
     337,   337,   337,   337,   337,   337,   337,   339,   338,   341,
     340,   343,   342,   345,   344,   347,   346,   349,   348,   351,
     350,   353,   352,   354,   354,   354,   354,   355,   357,   356,
     358,   358,   359,   359,   361,   360,   362,   362,   363,   363,
     363,   363,   363,   363,   363,   363,   363,   363,   363,   363,
     363,   363,   363,   363,   363,   363,   363,   363,   363,   363,
     363,   363,   365,   364,   367,   366,   368,   368,   369,   369,
     371,   370,   373,   372,   374,   374,   375,   375,   376,   376,
     376,   376,   376,   376,   376,   376,   376,   376,   377,   378,
     379,   381,   380,   383,   382,   385,   384,   386,   388,   387,
     389,   391,   390,   392,   392,   393,   393,   395,   394,   397,
     396,   398,   398,   399,   399,   400,   400,   400,   400,   400,
     400,   400,   400,   400,   401,   403,   402,   404,   405,   406,
     407,   409,   408,   410,   410,   411,   411,   413,   412,   415,
     414,   416,   416,   417,   417,   417,   417,   417,   417,   417,
     419,   418,   421,   420,   423,   422,   425,   424,   426,   426,
     427,   427,   429,   428,   431,   430,   432,   432,   433,   433,
     434,   434,   434,   434,   434,   434,   434,   434,   434,   434,
     434,   434,   434,   434,   434,   436,   435,   438,   437,   440,
     439,   442,   441,   444,   443,   446,   445,   448,   447,   450,
     449,   452,   451,   454,   453,   456,   455,   458,   457,   460,
     459,   461,   461,   463,   462,   464,   464,   466,   465,   467,
     467,   468,   468,   469,   469,   469,   469,   469,   469,   469,
     469,   469,   469,   469,   470,   472,   471,   473,   474,   476,
     475,   477,   477,   478,   478,   478,   478,   478,   480,   479,
     482,   481,   484,   483,   486,   485,   488,   487,   489,   489,
     490,   490,   490,   490,   490,   490,   490,   490,   490,   490,
     490,   490,   490,   490,   490,   490,   490,   490,   491,   493,
     492,   495,   494,   496,   498,   497,   499,   500,   502,   501,
     503,   503,   505,   504,   506,   507,   509,   508,   510,   510,
     510,   510,   510,   512,   511,   514,   513,   516,   515,   518,
     517,   520,   519,   522,   521,   524,   523,   526,   525,   527,
     527,   528,   528,   530,   529,   531,   533,   532,   535,   534,
     536,   536,   537,   539,   538,   540,   540,   542,   541,   543,
     543,   544,   544,   544,   544,   544,   544,   544,   545,   547,
     546,   549,   548,   550,   550,   552,   551,   553,   553,   554,
     554,   554,   554,   556,   555,   557,   558,   559
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
       1,     1,     1,     1,     1,     0,     4,     1,     1,     1,
       1,     0,     4,     0,     4,     0,     4,     3,     0,     4,
       3,     3,     3,     3,     3,     3,     3,     0,     4,     0,
       4,     0,     4,     0,     4,     3,     3,     0,     6,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     0,     6,     0,     1,     1,     3,     0,     4,     0,
       4,     1,     3,     1,     1,     1,     0,     4,     0,     4,
       0,     6,     1,     3,     1,     1,     1,     1,     1,     1,
       3,     3,     3,     3,     3,     3,     0,     6,     0,     1,
       1,     3,     0,     4,     0,     4,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     1,     1,     1,     1,     3,     0,     6,
       0,     1,     1,     3,     0,     4,     1,     3,     1,     1,
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
       0,     4,     0,     4,     0,     6,     0,     4,     1,     3,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     3,     0,
       4,     0,     4,     3,     0,     4,     3,     3,     0,     4,
       1,     1,     0,     4,     3,     3,     0,     4,     1,     1,
       1,     1,     1,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     6,     0,     4,     1,
       3,     1,     1,     0,     6,     3,     0,     6,     0,     4,
       1,     3,     1,     0,     6,     1,     3,     0,     4,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     3,     0,
       4,     0,     6,     1,     3,     0,     4,     1,     3,     1,
       1,     1,     1,     0,     4,     3,     3,     3
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
  "\"tcp-nodelay\"", "\"valid-lifetime\"", "\"min-valid-lifetime\"",
  "\"max-valid-lifetime\"", "\"renew-timer\"", "\"rebind-timer\"",
  "\"calculate-tee-times\"", "\"t1-percent\"", "\"t2-percent\"",
  "\"decline-probation-period\"", "\"server-tag\"", "\"subnet4\"",
  "\"4o6-interface\"", "\"4o6-interface-id\"", "\"4o6-subnet\"",
  "\"option-def\"", "\"option-data\"", "\"name\"", "\"data\"", "\"code\"",
  "\"space\"", "\"csv-format\"", "\"always-send\"", "\"record-types\"",
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
  "\"severity\"", "\"flush\"", "\"maxsize\"", "\"maxver\"", "\"Dhcp6\"",
  "\"DhcpDdns\"", "\"Control-agent\"", "TOPLEVEL_JSON", "TOPLEVEL_DHCP4",
  "SUB_DHCP4", "SUB_INTERFACES4", "SUB_SUBNET4", "SUB_POOL4",
  "SUB_RESERVATION", "SUB_OPTION_DEFS", "SUB_OPTION_DEF",
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
  "max_reconnect_tries", "reconnect_wait_time",
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
  "maxsize", "maxver", YY_NULLPTR
  };

#if PARSER4_DEBUG
  const unsigned short
  Dhcp4Parser::yyrline_[] =
  {
       0,   264,   264,   264,   265,   265,   266,   266,   267,   267,
     268,   268,   269,   269,   270,   270,   271,   271,   272,   272,
     273,   273,   274,   274,   275,   275,   276,   276,   277,   277,
     285,   286,   287,   288,   289,   290,   291,   294,   299,   299,
     310,   313,   314,   317,   321,   328,   328,   335,   336,   339,
     343,   350,   350,   357,   358,   361,   365,   376,   386,   386,
     402,   403,   407,   408,   409,   410,   411,   412,   415,   415,
     430,   430,   439,   440,   445,   446,   447,   448,   449,   450,
     451,   452,   453,   454,   455,   456,   457,   458,   459,   460,
     461,   462,   463,   464,   465,   466,   467,   468,   469,   470,
     471,   472,   473,   474,   475,   476,   477,   478,   479,   480,
     481,   482,   483,   484,   485,   486,   489,   494,   499,   504,
     509,   514,   519,   524,   529,   534,   534,   542,   547,   552,
     558,   558,   569,   570,   573,   574,   575,   576,   577,   578,
     579,   582,   582,   591,   591,   601,   601,   608,   609,   612,
     612,   619,   621,   625,   631,   631,   643,   643,   653,   654,
     656,   658,   658,   676,   676,   688,   688,   698,   699,   702,
     703,   706,   706,   716,   717,   720,   721,   722,   723,   724,
     725,   726,   727,   728,   729,   730,   731,   732,   733,   734,
     735,   736,   737,   738,   739,   742,   742,   749,   750,   751,
     752,   755,   755,   763,   763,   771,   771,   779,   784,   784,
     792,   797,   802,   807,   812,   817,   822,   827,   827,   835,
     835,   843,   843,   851,   851,   859,   864,   869,   869,   879,
     880,   883,   884,   885,   886,   887,   890,   895,   900,   905,
     910,   915,   915,   925,   926,   929,   930,   933,   933,   943,
     943,   953,   954,   955,   958,   959,   962,   962,   970,   970,
     978,   978,   989,   990,   993,   994,   995,   996,   997,   998,
    1001,  1006,  1011,  1016,  1021,  1026,  1034,  1034,  1047,  1048,
    1051,  1052,  1059,  1059,  1085,  1085,  1096,  1097,  1101,  1102,
    1103,  1104,  1105,  1106,  1107,  1108,  1109,  1110,  1111,  1112,
    1113,  1114,  1115,  1116,  1117,  1118,  1119,  1120,  1121,  1122,
    1123,  1124,  1125,  1126,  1127,  1128,  1129,  1132,  1132,  1140,
    1140,  1148,  1148,  1156,  1156,  1164,  1164,  1172,  1172,  1180,
    1180,  1190,  1190,  1197,  1198,  1199,  1200,  1203,  1210,  1210,
    1221,  1222,  1226,  1227,  1230,  1230,  1238,  1239,  1242,  1243,
    1244,  1245,  1246,  1247,  1248,  1249,  1250,  1251,  1252,  1253,
    1254,  1255,  1256,  1257,  1258,  1259,  1260,  1261,  1262,  1263,
    1264,  1265,  1272,  1272,  1285,  1285,  1294,  1295,  1298,  1299,
    1304,  1304,  1319,  1319,  1333,  1334,  1337,  1338,  1341,  1342,
    1343,  1344,  1345,  1346,  1347,  1348,  1349,  1350,  1353,  1355,
    1360,  1362,  1362,  1370,  1370,  1378,  1378,  1386,  1388,  1388,
    1396,  1405,  1405,  1417,  1418,  1423,  1424,  1429,  1429,  1441,
    1441,  1453,  1454,  1459,  1460,  1465,  1466,  1467,  1468,  1469,
    1470,  1471,  1472,  1473,  1476,  1478,  1478,  1486,  1488,  1490,
    1495,  1503,  1503,  1515,  1516,  1519,  1520,  1523,  1523,  1533,
    1533,  1543,  1544,  1547,  1548,  1549,  1550,  1551,  1552,  1553,
    1556,  1556,  1564,  1564,  1589,  1589,  1619,  1619,  1629,  1630,
    1633,  1634,  1637,  1637,  1646,  1646,  1655,  1656,  1659,  1660,
    1664,  1665,  1666,  1667,  1668,  1669,  1670,  1671,  1672,  1673,
    1674,  1675,  1676,  1677,  1678,  1681,  1681,  1689,  1689,  1697,
    1697,  1705,  1705,  1713,  1713,  1723,  1723,  1731,  1731,  1739,
    1739,  1747,  1747,  1755,  1755,  1763,  1763,  1771,  1771,  1784,
    1784,  1794,  1795,  1801,  1801,  1811,  1812,  1815,  1815,  1825,
    1826,  1829,  1830,  1833,  1834,  1835,  1836,  1837,  1838,  1839,
    1840,  1841,  1842,  1843,  1846,  1848,  1848,  1856,  1865,  1872,
    1872,  1882,  1883,  1886,  1887,  1888,  1889,  1890,  1893,  1893,
    1901,  1901,  1912,  1912,  1950,  1950,  1962,  1962,  1972,  1973,
    1976,  1977,  1978,  1979,  1980,  1981,  1982,  1983,  1984,  1985,
    1986,  1987,  1988,  1989,  1990,  1991,  1992,  1993,  1996,  2001,
    2001,  2009,  2009,  2017,  2022,  2022,  2030,  2035,  2040,  2040,
    2048,  2049,  2052,  2052,  2060,  2065,  2070,  2070,  2078,  2081,
    2084,  2087,  2090,  2096,  2096,  2104,  2104,  2112,  2112,  2123,
    2123,  2130,  2130,  2137,  2137,  2144,  2144,  2155,  2155,  2165,
    2166,  2170,  2171,  2174,  2174,  2184,  2194,  2194,  2204,  2204,
    2215,  2216,  2220,  2224,  2224,  2236,  2237,  2241,  2241,  2249,
    2250,  2253,  2254,  2255,  2256,  2257,  2258,  2259,  2262,  2267,
    2267,  2275,  2275,  2285,  2286,  2289,  2289,  2297,  2298,  2301,
    2302,  2303,  2304,  2307,  2307,  2315,  2320,  2325
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
#line 5094 "dhcp4_parser.cc"

#line 2330 "dhcp4_parser.yy"


void
isc::dhcp::Dhcp4Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
