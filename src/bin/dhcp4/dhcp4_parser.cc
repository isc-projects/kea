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

  case 114:
#line 487 "dhcp4_parser.yy"
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("valid-lifetime", prf);
}
#line 1072 "dhcp4_parser.cc"
    break;

  case 115:
#line 492 "dhcp4_parser.yy"
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("min-valid-lifetime", prf);
}
#line 1081 "dhcp4_parser.cc"
    break;

  case 116:
#line 497 "dhcp4_parser.yy"
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-valid-lifetime", prf);
}
#line 1090 "dhcp4_parser.cc"
    break;

  case 117:
#line 502 "dhcp4_parser.yy"
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("renew-timer", prf);
}
#line 1099 "dhcp4_parser.cc"
    break;

  case 118:
#line 507 "dhcp4_parser.yy"
    {
    ElementPtr prf(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("rebind-timer", prf);
}
#line 1108 "dhcp4_parser.cc"
    break;

  case 119:
#line 512 "dhcp4_parser.yy"
    {
    ElementPtr ctt(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("calculate-tee-times", ctt);
}
#line 1117 "dhcp4_parser.cc"
    break;

  case 120:
#line 517 "dhcp4_parser.yy"
    {
    ElementPtr t1(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t1-percent", t1);
}
#line 1126 "dhcp4_parser.cc"
    break;

  case 121:
#line 522 "dhcp4_parser.yy"
    {
    ElementPtr t2(new DoubleElement(yystack_[0].value.as < double > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("t2-percent", t2);
}
#line 1135 "dhcp4_parser.cc"
    break;

  case 122:
#line 527 "dhcp4_parser.yy"
    {
    ElementPtr dpp(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("decline-probation-period", dpp);
}
#line 1144 "dhcp4_parser.cc"
    break;

  case 123:
#line 532 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1152 "dhcp4_parser.cc"
    break;

  case 124:
#line 534 "dhcp4_parser.yy"
    {
    ElementPtr stag(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-tag", stag);
    ctx.leave();
}
#line 1162 "dhcp4_parser.cc"
    break;

  case 125:
#line 540 "dhcp4_parser.yy"
    {
    ElementPtr echo(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("echo-client-id", echo);
}
#line 1171 "dhcp4_parser.cc"
    break;

  case 126:
#line 545 "dhcp4_parser.yy"
    {
    ElementPtr match(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("match-client-id", match);
}
#line 1180 "dhcp4_parser.cc"
    break;

  case 127:
#line 550 "dhcp4_parser.yy"
    {
    ElementPtr prf(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("authoritative", prf);
}
#line 1189 "dhcp4_parser.cc"
    break;

  case 128:
#line 556 "dhcp4_parser.yy"
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces-config", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.INTERFACES_CONFIG);
}
#line 1200 "dhcp4_parser.cc"
    break;

  case 129:
#line 561 "dhcp4_parser.yy"
    {
    // No interfaces config param is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1210 "dhcp4_parser.cc"
    break;

  case 139:
#line 580 "dhcp4_parser.yy"
    {
    // Parse the interfaces-config map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1220 "dhcp4_parser.cc"
    break;

  case 140:
#line 584 "dhcp4_parser.yy"
    {
    // No interfaces config param is required
    // parsing completed
}
#line 1229 "dhcp4_parser.cc"
    break;

  case 141:
#line 589 "dhcp4_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interfaces", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1240 "dhcp4_parser.cc"
    break;

  case 142:
#line 594 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1249 "dhcp4_parser.cc"
    break;

  case 143:
#line 599 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.DHCP_SOCKET_TYPE);
}
#line 1257 "dhcp4_parser.cc"
    break;

  case 144:
#line 601 "dhcp4_parser.yy"
    {
    ctx.stack_.back()->set("dhcp-socket-type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1266 "dhcp4_parser.cc"
    break;

  case 145:
#line 606 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("raw", ctx.loc2pos(yystack_[0].location))); }
#line 1272 "dhcp4_parser.cc"
    break;

  case 146:
#line 607 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("udp", ctx.loc2pos(yystack_[0].location))); }
#line 1278 "dhcp4_parser.cc"
    break;

  case 147:
#line 610 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.OUTBOUND_INTERFACE);
}
#line 1286 "dhcp4_parser.cc"
    break;

  case 148:
#line 612 "dhcp4_parser.yy"
    {
    ctx.stack_.back()->set("outbound-interface", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1295 "dhcp4_parser.cc"
    break;

  case 149:
#line 617 "dhcp4_parser.yy"
    {
    yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("same-as-inbound", ctx.loc2pos(yystack_[0].location)));
}
#line 1303 "dhcp4_parser.cc"
    break;

  case 150:
#line 619 "dhcp4_parser.yy"
    {
    yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("use-routing", ctx.loc2pos(yystack_[0].location)));
    }
#line 1311 "dhcp4_parser.cc"
    break;

  case 151:
#line 623 "dhcp4_parser.yy"
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("re-detect", b);
}
#line 1320 "dhcp4_parser.cc"
    break;

  case 152:
#line 629 "dhcp4_parser.yy"
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lease-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.LEASE_DATABASE);
}
#line 1331 "dhcp4_parser.cc"
    break;

  case 153:
#line 634 "dhcp4_parser.yy"
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1342 "dhcp4_parser.cc"
    break;

  case 154:
#line 641 "dhcp4_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sanity-checks", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.SANITY_CHECKS);
}
#line 1353 "dhcp4_parser.cc"
    break;

  case 155:
#line 646 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1362 "dhcp4_parser.cc"
    break;

  case 159:
#line 656 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1370 "dhcp4_parser.cc"
    break;

  case 160:
#line 658 "dhcp4_parser.yy"
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

  case 161:
#line 674 "dhcp4_parser.yy"
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-database", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1401 "dhcp4_parser.cc"
    break;

  case 162:
#line 679 "dhcp4_parser.yy"
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1412 "dhcp4_parser.cc"
    break;

  case 163:
#line 686 "dhcp4_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hosts-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOSTS_DATABASE);
}
#line 1423 "dhcp4_parser.cc"
    break;

  case 164:
#line 691 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1432 "dhcp4_parser.cc"
    break;

  case 169:
#line 704 "dhcp4_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1442 "dhcp4_parser.cc"
    break;

  case 170:
#line 708 "dhcp4_parser.yy"
    {
    // The type parameter is required
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1452 "dhcp4_parser.cc"
    break;

  case 193:
#line 740 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.DATABASE_TYPE);
}
#line 1460 "dhcp4_parser.cc"
    break;

  case 194:
#line 742 "dhcp4_parser.yy"
    {
    ctx.stack_.back()->set("type", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1469 "dhcp4_parser.cc"
    break;

  case 195:
#line 747 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("memfile", ctx.loc2pos(yystack_[0].location))); }
#line 1475 "dhcp4_parser.cc"
    break;

  case 196:
#line 748 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("mysql", ctx.loc2pos(yystack_[0].location))); }
#line 1481 "dhcp4_parser.cc"
    break;

  case 197:
#line 749 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("postgresql", ctx.loc2pos(yystack_[0].location))); }
#line 1487 "dhcp4_parser.cc"
    break;

  case 198:
#line 750 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("cql", ctx.loc2pos(yystack_[0].location))); }
#line 1493 "dhcp4_parser.cc"
    break;

  case 199:
#line 753 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1501 "dhcp4_parser.cc"
    break;

  case 200:
#line 755 "dhcp4_parser.yy"
    {
    ElementPtr user(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("user", user);
    ctx.leave();
}
#line 1511 "dhcp4_parser.cc"
    break;

  case 201:
#line 761 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1519 "dhcp4_parser.cc"
    break;

  case 202:
#line 763 "dhcp4_parser.yy"
    {
    ElementPtr pwd(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("password", pwd);
    ctx.leave();
}
#line 1529 "dhcp4_parser.cc"
    break;

  case 203:
#line 769 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1537 "dhcp4_parser.cc"
    break;

  case 204:
#line 771 "dhcp4_parser.yy"
    {
    ElementPtr h(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host", h);
    ctx.leave();
}
#line 1547 "dhcp4_parser.cc"
    break;

  case 205:
#line 777 "dhcp4_parser.yy"
    {
    ElementPtr p(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("port", p);
}
#line 1556 "dhcp4_parser.cc"
    break;

  case 206:
#line 782 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1564 "dhcp4_parser.cc"
    break;

  case 207:
#line 784 "dhcp4_parser.yy"
    {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("name", name);
    ctx.leave();
}
#line 1574 "dhcp4_parser.cc"
    break;

  case 208:
#line 790 "dhcp4_parser.yy"
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("persist", n);
}
#line 1583 "dhcp4_parser.cc"
    break;

  case 209:
#line 795 "dhcp4_parser.yy"
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("lfc-interval", n);
}
#line 1592 "dhcp4_parser.cc"
    break;

  case 210:
#line 800 "dhcp4_parser.yy"
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("readonly", n);
}
#line 1601 "dhcp4_parser.cc"
    break;

  case 211:
#line 805 "dhcp4_parser.yy"
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("connect-timeout", n);
}
#line 1610 "dhcp4_parser.cc"
    break;

  case 212:
#line 810 "dhcp4_parser.yy"
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("request-timeout", n);
}
#line 1619 "dhcp4_parser.cc"
    break;

  case 213:
#line 815 "dhcp4_parser.yy"
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-keepalive", n);
}
#line 1628 "dhcp4_parser.cc"
    break;

  case 214:
#line 820 "dhcp4_parser.yy"
    {
    ElementPtr n(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("tcp-nodelay", n);
}
#line 1637 "dhcp4_parser.cc"
    break;

  case 215:
#line 825 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1645 "dhcp4_parser.cc"
    break;

  case 216:
#line 827 "dhcp4_parser.yy"
    {
    ElementPtr cp(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("contact-points", cp);
    ctx.leave();
}
#line 1655 "dhcp4_parser.cc"
    break;

  case 217:
#line 833 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1663 "dhcp4_parser.cc"
    break;

  case 218:
#line 835 "dhcp4_parser.yy"
    {
    ElementPtr ks(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("keyspace", ks);
    ctx.leave();
}
#line 1673 "dhcp4_parser.cc"
    break;

  case 219:
#line 841 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1681 "dhcp4_parser.cc"
    break;

  case 220:
#line 843 "dhcp4_parser.yy"
    {
    ElementPtr c(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("consistency", c);
    ctx.leave();
}
#line 1691 "dhcp4_parser.cc"
    break;

  case 221:
#line 849 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1699 "dhcp4_parser.cc"
    break;

  case 222:
#line 851 "dhcp4_parser.yy"
    {
    ElementPtr c(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("serial-consistency", c);
    ctx.leave();
}
#line 1709 "dhcp4_parser.cc"
    break;

  case 223:
#line 857 "dhcp4_parser.yy"
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reconnect-tries", n);
}
#line 1718 "dhcp4_parser.cc"
    break;

  case 224:
#line 862 "dhcp4_parser.yy"
    {
    ElementPtr n(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reconnect-wait-time", n);
}
#line 1727 "dhcp4_parser.cc"
    break;

  case 225:
#line 867 "dhcp4_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("host-reservation-identifiers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOST_RESERVATION_IDENTIFIERS);
}
#line 1738 "dhcp4_parser.cc"
    break;

  case 226:
#line 872 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1747 "dhcp4_parser.cc"
    break;

  case 234:
#line 888 "dhcp4_parser.yy"
    {
    ElementPtr duid(new StringElement("duid", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(duid);
}
#line 1756 "dhcp4_parser.cc"
    break;

  case 235:
#line 893 "dhcp4_parser.yy"
    {
    ElementPtr hwaddr(new StringElement("hw-address", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(hwaddr);
}
#line 1765 "dhcp4_parser.cc"
    break;

  case 236:
#line 898 "dhcp4_parser.yy"
    {
    ElementPtr circuit(new StringElement("circuit-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(circuit);
}
#line 1774 "dhcp4_parser.cc"
    break;

  case 237:
#line 903 "dhcp4_parser.yy"
    {
    ElementPtr client(new StringElement("client-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(client);
}
#line 1783 "dhcp4_parser.cc"
    break;

  case 238:
#line 908 "dhcp4_parser.yy"
    {
    ElementPtr flex_id(new StringElement("flex-id", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(flex_id);
}
#line 1792 "dhcp4_parser.cc"
    break;

  case 239:
#line 913 "dhcp4_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hooks-libraries", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.HOOKS_LIBRARIES);
}
#line 1803 "dhcp4_parser.cc"
    break;

  case 240:
#line 918 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1812 "dhcp4_parser.cc"
    break;

  case 245:
#line 931 "dhcp4_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1822 "dhcp4_parser.cc"
    break;

  case 246:
#line 935 "dhcp4_parser.yy"
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 1832 "dhcp4_parser.cc"
    break;

  case 247:
#line 941 "dhcp4_parser.yy"
    {
    // Parse the hooks-libraries list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 1842 "dhcp4_parser.cc"
    break;

  case 248:
#line 945 "dhcp4_parser.yy"
    {
    // The library hooks parameter is required
    ctx.require("library", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 1852 "dhcp4_parser.cc"
    break;

  case 254:
#line 960 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1860 "dhcp4_parser.cc"
    break;

  case 255:
#line 962 "dhcp4_parser.yy"
    {
    ElementPtr lib(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("library", lib);
    ctx.leave();
}
#line 1870 "dhcp4_parser.cc"
    break;

  case 256:
#line 968 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 1878 "dhcp4_parser.cc"
    break;

  case 257:
#line 970 "dhcp4_parser.yy"
    {
    ctx.stack_.back()->set("parameters", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 1887 "dhcp4_parser.cc"
    break;

  case 258:
#line 976 "dhcp4_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("expired-leases-processing", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.EXPIRED_LEASES_PROCESSING);
}
#line 1898 "dhcp4_parser.cc"
    break;

  case 259:
#line 981 "dhcp4_parser.yy"
    {
    // No expired lease parameter is required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1908 "dhcp4_parser.cc"
    break;

  case 268:
#line 999 "dhcp4_parser.yy"
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reclaim-timer-wait-time", value);
}
#line 1917 "dhcp4_parser.cc"
    break;

  case 269:
#line 1004 "dhcp4_parser.yy"
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush-reclaimed-timer-wait-time", value);
}
#line 1926 "dhcp4_parser.cc"
    break;

  case 270:
#line 1009 "dhcp4_parser.yy"
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hold-reclaimed-time", value);
}
#line 1935 "dhcp4_parser.cc"
    break;

  case 271:
#line 1014 "dhcp4_parser.yy"
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-leases", value);
}
#line 1944 "dhcp4_parser.cc"
    break;

  case 272:
#line 1019 "dhcp4_parser.yy"
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-reclaim-time", value);
}
#line 1953 "dhcp4_parser.cc"
    break;

  case 273:
#line 1024 "dhcp4_parser.yy"
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("unwarned-reclaim-cycles", value);
}
#line 1962 "dhcp4_parser.cc"
    break;

  case 274:
#line 1032 "dhcp4_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet4", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SUBNET4);
}
#line 1973 "dhcp4_parser.cc"
    break;

  case 275:
#line 1037 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 1982 "dhcp4_parser.cc"
    break;

  case 280:
#line 1057 "dhcp4_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 1992 "dhcp4_parser.cc"
    break;

  case 281:
#line 1061 "dhcp4_parser.yy"
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

  case 282:
#line 1083 "dhcp4_parser.yy"
    {
    // Parse the subnet4 list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2028 "dhcp4_parser.cc"
    break;

  case 283:
#line 1087 "dhcp4_parser.yy"
    {
    // The subnet subnet4 parameter is required
    ctx.require("subnet", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2038 "dhcp4_parser.cc"
    break;

  case 315:
#line 1130 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2046 "dhcp4_parser.cc"
    break;

  case 316:
#line 1132 "dhcp4_parser.yy"
    {
    ElementPtr subnet(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("subnet", subnet);
    ctx.leave();
}
#line 2056 "dhcp4_parser.cc"
    break;

  case 317:
#line 1138 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2064 "dhcp4_parser.cc"
    break;

  case 318:
#line 1140 "dhcp4_parser.yy"
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface", iface);
    ctx.leave();
}
#line 2074 "dhcp4_parser.cc"
    break;

  case 319:
#line 1146 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2082 "dhcp4_parser.cc"
    break;

  case 320:
#line 1148 "dhcp4_parser.yy"
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-interface-id", iface);
    ctx.leave();
}
#line 2092 "dhcp4_parser.cc"
    break;

  case 321:
#line 1154 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2100 "dhcp4_parser.cc"
    break;

  case 322:
#line 1156 "dhcp4_parser.yy"
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("4o6-subnet", iface);
    ctx.leave();
}
#line 2110 "dhcp4_parser.cc"
    break;

  case 323:
#line 1162 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2118 "dhcp4_parser.cc"
    break;

  case 324:
#line 1164 "dhcp4_parser.yy"
    {
    ElementPtr iface(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("interface", iface);
    ctx.leave();
}
#line 2128 "dhcp4_parser.cc"
    break;

  case 325:
#line 1170 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2136 "dhcp4_parser.cc"
    break;

  case 326:
#line 1172 "dhcp4_parser.yy"
    {
    ElementPtr cls(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-class", cls);
    ctx.leave();
}
#line 2146 "dhcp4_parser.cc"
    break;

  case 327:
#line 1178 "dhcp4_parser.yy"
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("require-client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2157 "dhcp4_parser.cc"
    break;

  case 328:
#line 1183 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2166 "dhcp4_parser.cc"
    break;

  case 329:
#line 1188 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.RESERVATION_MODE);
}
#line 2174 "dhcp4_parser.cc"
    break;

  case 330:
#line 1190 "dhcp4_parser.yy"
    {
    ctx.stack_.back()->set("reservation-mode", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 2183 "dhcp4_parser.cc"
    break;

  case 331:
#line 1195 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("disabled", ctx.loc2pos(yystack_[0].location))); }
#line 2189 "dhcp4_parser.cc"
    break;

  case 332:
#line 1196 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("out-of-pool", ctx.loc2pos(yystack_[0].location))); }
#line 2195 "dhcp4_parser.cc"
    break;

  case 333:
#line 1197 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("global", ctx.loc2pos(yystack_[0].location))); }
#line 2201 "dhcp4_parser.cc"
    break;

  case 334:
#line 1198 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("all", ctx.loc2pos(yystack_[0].location))); }
#line 2207 "dhcp4_parser.cc"
    break;

  case 335:
#line 1201 "dhcp4_parser.yy"
    {
    ElementPtr id(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("id", id);
}
#line 2216 "dhcp4_parser.cc"
    break;

  case 336:
#line 1208 "dhcp4_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("shared-networks", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.SHARED_NETWORK);
}
#line 2227 "dhcp4_parser.cc"
    break;

  case 337:
#line 1213 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2236 "dhcp4_parser.cc"
    break;

  case 342:
#line 1228 "dhcp4_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2246 "dhcp4_parser.cc"
    break;

  case 343:
#line 1232 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
}
#line 2254 "dhcp4_parser.cc"
    break;

  case 370:
#line 1270 "dhcp4_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-def", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DEF);
}
#line 2265 "dhcp4_parser.cc"
    break;

  case 371:
#line 1275 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2274 "dhcp4_parser.cc"
    break;

  case 372:
#line 1283 "dhcp4_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2283 "dhcp4_parser.cc"
    break;

  case 373:
#line 1286 "dhcp4_parser.yy"
    {
    // parsing completed
}
#line 2291 "dhcp4_parser.cc"
    break;

  case 378:
#line 1302 "dhcp4_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2301 "dhcp4_parser.cc"
    break;

  case 379:
#line 1306 "dhcp4_parser.yy"
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2313 "dhcp4_parser.cc"
    break;

  case 380:
#line 1317 "dhcp4_parser.yy"
    {
    // Parse the option-def list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2323 "dhcp4_parser.cc"
    break;

  case 381:
#line 1321 "dhcp4_parser.yy"
    {
    // The name, code and type option def parameters are required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("code", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.require("type", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2335 "dhcp4_parser.cc"
    break;

  case 397:
#line 1353 "dhcp4_parser.yy"
    {
    ElementPtr code(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("code", code);
}
#line 2344 "dhcp4_parser.cc"
    break;

  case 399:
#line 1360 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2352 "dhcp4_parser.cc"
    break;

  case 400:
#line 1362 "dhcp4_parser.yy"
    {
    ElementPtr prf(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("type", prf);
    ctx.leave();
}
#line 2362 "dhcp4_parser.cc"
    break;

  case 401:
#line 1368 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2370 "dhcp4_parser.cc"
    break;

  case 402:
#line 1370 "dhcp4_parser.yy"
    {
    ElementPtr rtypes(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("record-types", rtypes);
    ctx.leave();
}
#line 2380 "dhcp4_parser.cc"
    break;

  case 403:
#line 1376 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2388 "dhcp4_parser.cc"
    break;

  case 404:
#line 1378 "dhcp4_parser.yy"
    {
    ElementPtr space(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("space", space);
    ctx.leave();
}
#line 2398 "dhcp4_parser.cc"
    break;

  case 406:
#line 1386 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2406 "dhcp4_parser.cc"
    break;

  case 407:
#line 1388 "dhcp4_parser.yy"
    {
    ElementPtr encap(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("encapsulate", encap);
    ctx.leave();
}
#line 2416 "dhcp4_parser.cc"
    break;

  case 408:
#line 1394 "dhcp4_parser.yy"
    {
    ElementPtr array(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("array", array);
}
#line 2425 "dhcp4_parser.cc"
    break;

  case 409:
#line 1403 "dhcp4_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("option-data", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OPTION_DATA);
}
#line 2436 "dhcp4_parser.cc"
    break;

  case 410:
#line 1408 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2445 "dhcp4_parser.cc"
    break;

  case 415:
#line 1427 "dhcp4_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2455 "dhcp4_parser.cc"
    break;

  case 416:
#line 1431 "dhcp4_parser.yy"
    {
    /// @todo: the code or name parameters are required.
    ctx.stack_.pop_back();
}
#line 2464 "dhcp4_parser.cc"
    break;

  case 417:
#line 1439 "dhcp4_parser.yy"
    {
    // Parse the option-data list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2474 "dhcp4_parser.cc"
    break;

  case 418:
#line 1443 "dhcp4_parser.yy"
    {
    /// @todo: the code or name parameters are required.
    // parsing completed
}
#line 2483 "dhcp4_parser.cc"
    break;

  case 433:
#line 1476 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2491 "dhcp4_parser.cc"
    break;

  case 434:
#line 1478 "dhcp4_parser.yy"
    {
    ElementPtr data(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("data", data);
    ctx.leave();
}
#line 2501 "dhcp4_parser.cc"
    break;

  case 437:
#line 1488 "dhcp4_parser.yy"
    {
    ElementPtr space(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("csv-format", space);
}
#line 2510 "dhcp4_parser.cc"
    break;

  case 438:
#line 1493 "dhcp4_parser.yy"
    {
    ElementPtr persist(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("always-send", persist);
}
#line 2519 "dhcp4_parser.cc"
    break;

  case 439:
#line 1501 "dhcp4_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pools", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.POOLS);
}
#line 2530 "dhcp4_parser.cc"
    break;

  case 440:
#line 1506 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2539 "dhcp4_parser.cc"
    break;

  case 445:
#line 1521 "dhcp4_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2549 "dhcp4_parser.cc"
    break;

  case 446:
#line 1525 "dhcp4_parser.yy"
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 2559 "dhcp4_parser.cc"
    break;

  case 447:
#line 1531 "dhcp4_parser.yy"
    {
    // Parse the pool list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2569 "dhcp4_parser.cc"
    break;

  case 448:
#line 1535 "dhcp4_parser.yy"
    {
    // The pool parameter is required.
    ctx.require("pool", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 2579 "dhcp4_parser.cc"
    break;

  case 458:
#line 1554 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2587 "dhcp4_parser.cc"
    break;

  case 459:
#line 1556 "dhcp4_parser.yy"
    {
    ElementPtr pool(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("pool", pool);
    ctx.leave();
}
#line 2597 "dhcp4_parser.cc"
    break;

  case 460:
#line 1562 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2605 "dhcp4_parser.cc"
    break;

  case 461:
#line 1564 "dhcp4_parser.yy"
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

  case 462:
#line 1587 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2640 "dhcp4_parser.cc"
    break;

  case 463:
#line 1589 "dhcp4_parser.yy"
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

  case 464:
#line 1617 "dhcp4_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("reservations", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.RESERVATIONS);
}
#line 2680 "dhcp4_parser.cc"
    break;

  case 465:
#line 1622 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2689 "dhcp4_parser.cc"
    break;

  case 470:
#line 1635 "dhcp4_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2699 "dhcp4_parser.cc"
    break;

  case 471:
#line 1639 "dhcp4_parser.yy"
    {
    /// @todo: an identifier parameter is required.
    ctx.stack_.pop_back();
}
#line 2708 "dhcp4_parser.cc"
    break;

  case 472:
#line 1644 "dhcp4_parser.yy"
    {
    // Parse the reservations list entry map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 2718 "dhcp4_parser.cc"
    break;

  case 473:
#line 1648 "dhcp4_parser.yy"
    {
    /// @todo: an identifier parameter is required.
    // parsing completed
}
#line 2727 "dhcp4_parser.cc"
    break;

  case 493:
#line 1679 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2735 "dhcp4_parser.cc"
    break;

  case 494:
#line 1681 "dhcp4_parser.yy"
    {
    ElementPtr next_server(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("next-server", next_server);
    ctx.leave();
}
#line 2745 "dhcp4_parser.cc"
    break;

  case 495:
#line 1687 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2753 "dhcp4_parser.cc"
    break;

  case 496:
#line 1689 "dhcp4_parser.yy"
    {
    ElementPtr srv(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-hostname", srv);
    ctx.leave();
}
#line 2763 "dhcp4_parser.cc"
    break;

  case 497:
#line 1695 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2771 "dhcp4_parser.cc"
    break;

  case 498:
#line 1697 "dhcp4_parser.yy"
    {
    ElementPtr bootfile(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("boot-file-name", bootfile);
    ctx.leave();
}
#line 2781 "dhcp4_parser.cc"
    break;

  case 499:
#line 1703 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2789 "dhcp4_parser.cc"
    break;

  case 500:
#line 1705 "dhcp4_parser.yy"
    {
    ElementPtr addr(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-address", addr);
    ctx.leave();
}
#line 2799 "dhcp4_parser.cc"
    break;

  case 501:
#line 1711 "dhcp4_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ip-addresses", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2810 "dhcp4_parser.cc"
    break;

  case 502:
#line 1716 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2819 "dhcp4_parser.cc"
    break;

  case 503:
#line 1721 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2827 "dhcp4_parser.cc"
    break;

  case 504:
#line 1723 "dhcp4_parser.yy"
    {
    ElementPtr d(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("duid", d);
    ctx.leave();
}
#line 2837 "dhcp4_parser.cc"
    break;

  case 505:
#line 1729 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2845 "dhcp4_parser.cc"
    break;

  case 506:
#line 1731 "dhcp4_parser.yy"
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hw-address", hw);
    ctx.leave();
}
#line 2855 "dhcp4_parser.cc"
    break;

  case 507:
#line 1737 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2863 "dhcp4_parser.cc"
    break;

  case 508:
#line 1739 "dhcp4_parser.yy"
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-id", hw);
    ctx.leave();
}
#line 2873 "dhcp4_parser.cc"
    break;

  case 509:
#line 1745 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2881 "dhcp4_parser.cc"
    break;

  case 510:
#line 1747 "dhcp4_parser.yy"
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("circuit-id", hw);
    ctx.leave();
}
#line 2891 "dhcp4_parser.cc"
    break;

  case 511:
#line 1753 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2899 "dhcp4_parser.cc"
    break;

  case 512:
#line 1755 "dhcp4_parser.yy"
    {
    ElementPtr hw(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flex-id", hw);
    ctx.leave();
}
#line 2909 "dhcp4_parser.cc"
    break;

  case 513:
#line 1761 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2917 "dhcp4_parser.cc"
    break;

  case 514:
#line 1763 "dhcp4_parser.yy"
    {
    ElementPtr host(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname", host);
    ctx.leave();
}
#line 2927 "dhcp4_parser.cc"
    break;

  case 515:
#line 1769 "dhcp4_parser.yy"
    {
    ElementPtr c(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", c);
    ctx.stack_.push_back(c);
    ctx.enter(ctx.NO_KEYWORD);
}
#line 2938 "dhcp4_parser.cc"
    break;

  case 516:
#line 1774 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2947 "dhcp4_parser.cc"
    break;

  case 517:
#line 1782 "dhcp4_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("relay", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.RELAY);
}
#line 2958 "dhcp4_parser.cc"
    break;

  case 518:
#line 1787 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2967 "dhcp4_parser.cc"
    break;

  case 521:
#line 1799 "dhcp4_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("client-classes", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CLIENT_CLASSES);
}
#line 2978 "dhcp4_parser.cc"
    break;

  case 522:
#line 1804 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 2987 "dhcp4_parser.cc"
    break;

  case 525:
#line 1813 "dhcp4_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 2997 "dhcp4_parser.cc"
    break;

  case 526:
#line 1817 "dhcp4_parser.yy"
    {
    // The name client class parameter is required.
    ctx.require("name", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
}
#line 3007 "dhcp4_parser.cc"
    break;

  case 543:
#line 1846 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3015 "dhcp4_parser.cc"
    break;

  case 544:
#line 1848 "dhcp4_parser.yy"
    {
    ElementPtr test(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("test", test);
    ctx.leave();
}
#line 3025 "dhcp4_parser.cc"
    break;

  case 545:
#line 1854 "dhcp4_parser.yy"
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("only-if-required", b);
}
#line 3034 "dhcp4_parser.cc"
    break;

  case 546:
#line 1863 "dhcp4_parser.yy"
    {
    ElementPtr time(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp4o6-port", time);
}
#line 3043 "dhcp4_parser.cc"
    break;

  case 547:
#line 1870 "dhcp4_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("control-socket", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.CONTROL_SOCKET);
}
#line 3054 "dhcp4_parser.cc"
    break;

  case 548:
#line 1875 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3063 "dhcp4_parser.cc"
    break;

  case 556:
#line 1891 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3071 "dhcp4_parser.cc"
    break;

  case 557:
#line 1893 "dhcp4_parser.yy"
    {
    ElementPtr stype(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-type", stype);
    ctx.leave();
}
#line 3081 "dhcp4_parser.cc"
    break;

  case 558:
#line 1899 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3089 "dhcp4_parser.cc"
    break;

  case 559:
#line 1901 "dhcp4_parser.yy"
    {
    ElementPtr name(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("socket-name", name);
    ctx.leave();
}
#line 3099 "dhcp4_parser.cc"
    break;

  case 560:
#line 1910 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3107 "dhcp4_parser.cc"
    break;

  case 561:
#line 1912 "dhcp4_parser.yy"
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

  case 562:
#line 1948 "dhcp4_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("dhcp-ddns", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.DHCP_DDNS);
}
#line 3156 "dhcp4_parser.cc"
    break;

  case 563:
#line 1953 "dhcp4_parser.yy"
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[2].location), ctx.loc2pos(yystack_[0].location));
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3167 "dhcp4_parser.cc"
    break;

  case 564:
#line 1960 "dhcp4_parser.yy"
    {
    // Parse the dhcp-ddns map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3177 "dhcp4_parser.cc"
    break;

  case 565:
#line 1964 "dhcp4_parser.yy"
    {
    // The enable updates DHCP DDNS parameter is required.
    ctx.require("enable-updates", ctx.loc2pos(yystack_[3].location), ctx.loc2pos(yystack_[0].location));
    // parsing completed
}
#line 3187 "dhcp4_parser.cc"
    break;

  case 586:
#line 1994 "dhcp4_parser.yy"
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("enable-updates", b);
}
#line 3196 "dhcp4_parser.cc"
    break;

  case 587:
#line 1999 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3204 "dhcp4_parser.cc"
    break;

  case 588:
#line 2001 "dhcp4_parser.yy"
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("qualifying-suffix", s);
    ctx.leave();
}
#line 3214 "dhcp4_parser.cc"
    break;

  case 589:
#line 2007 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3222 "dhcp4_parser.cc"
    break;

  case 590:
#line 2009 "dhcp4_parser.yy"
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-ip", s);
    ctx.leave();
}
#line 3232 "dhcp4_parser.cc"
    break;

  case 591:
#line 2015 "dhcp4_parser.yy"
    {
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("server-port", i);
}
#line 3241 "dhcp4_parser.cc"
    break;

  case 592:
#line 2020 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3249 "dhcp4_parser.cc"
    break;

  case 593:
#line 2022 "dhcp4_parser.yy"
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-ip", s);
    ctx.leave();
}
#line 3259 "dhcp4_parser.cc"
    break;

  case 594:
#line 2028 "dhcp4_parser.yy"
    {
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("sender-port", i);
}
#line 3268 "dhcp4_parser.cc"
    break;

  case 595:
#line 2033 "dhcp4_parser.yy"
    {
    ElementPtr i(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("max-queue-size", i);
}
#line 3277 "dhcp4_parser.cc"
    break;

  case 596:
#line 2038 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NCR_PROTOCOL);
}
#line 3285 "dhcp4_parser.cc"
    break;

  case 597:
#line 2040 "dhcp4_parser.yy"
    {
    ctx.stack_.back()->set("ncr-protocol", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3294 "dhcp4_parser.cc"
    break;

  case 598:
#line 2046 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("UDP", ctx.loc2pos(yystack_[0].location))); }
#line 3300 "dhcp4_parser.cc"
    break;

  case 599:
#line 2047 "dhcp4_parser.yy"
    { yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("TCP", ctx.loc2pos(yystack_[0].location))); }
#line 3306 "dhcp4_parser.cc"
    break;

  case 600:
#line 2050 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NCR_FORMAT);
}
#line 3314 "dhcp4_parser.cc"
    break;

  case 601:
#line 2052 "dhcp4_parser.yy"
    {
    ElementPtr json(new StringElement("JSON", ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("ncr-format", json);
    ctx.leave();
}
#line 3324 "dhcp4_parser.cc"
    break;

  case 602:
#line 2058 "dhcp4_parser.yy"
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-no-update", b);
}
#line 3333 "dhcp4_parser.cc"
    break;

  case 603:
#line 2063 "dhcp4_parser.yy"
    {
    ElementPtr b(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("override-client-update", b);
}
#line 3342 "dhcp4_parser.cc"
    break;

  case 604:
#line 2068 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.REPLACE_CLIENT_NAME);
}
#line 3350 "dhcp4_parser.cc"
    break;

  case 605:
#line 2070 "dhcp4_parser.yy"
    {
    ctx.stack_.back()->set("replace-client-name", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3359 "dhcp4_parser.cc"
    break;

  case 606:
#line 2076 "dhcp4_parser.yy"
    {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 3367 "dhcp4_parser.cc"
    break;

  case 607:
#line 2079 "dhcp4_parser.yy"
    {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("never", ctx.loc2pos(yystack_[0].location)));
      }
#line 3375 "dhcp4_parser.cc"
    break;

  case 608:
#line 2082 "dhcp4_parser.yy"
    {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("always", ctx.loc2pos(yystack_[0].location)));
      }
#line 3383 "dhcp4_parser.cc"
    break;

  case 609:
#line 2085 "dhcp4_parser.yy"
    {
      yylhs.value.as < ElementPtr > () = ElementPtr(new StringElement("when-not-present", ctx.loc2pos(yystack_[0].location)));
      }
#line 3391 "dhcp4_parser.cc"
    break;

  case 610:
#line 2088 "dhcp4_parser.yy"
    {
      error(yystack_[0].location, "boolean values for the replace-client-name are "
                "no longer supported");
      }
#line 3400 "dhcp4_parser.cc"
    break;

  case 611:
#line 2094 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3408 "dhcp4_parser.cc"
    break;

  case 612:
#line 2096 "dhcp4_parser.yy"
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("generated-prefix", s);
    ctx.leave();
}
#line 3418 "dhcp4_parser.cc"
    break;

  case 613:
#line 2102 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3426 "dhcp4_parser.cc"
    break;

  case 614:
#line 2104 "dhcp4_parser.yy"
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-set", s);
    ctx.leave();
}
#line 3436 "dhcp4_parser.cc"
    break;

  case 615:
#line 2110 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3444 "dhcp4_parser.cc"
    break;

  case 616:
#line 2112 "dhcp4_parser.yy"
    {
    ElementPtr s(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("hostname-char-replacement", s);
    ctx.leave();
}
#line 3454 "dhcp4_parser.cc"
    break;

  case 617:
#line 2121 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3462 "dhcp4_parser.cc"
    break;

  case 618:
#line 2123 "dhcp4_parser.yy"
    {
    ctx.stack_.back()->set("Dhcp6", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3471 "dhcp4_parser.cc"
    break;

  case 619:
#line 2128 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3479 "dhcp4_parser.cc"
    break;

  case 620:
#line 2130 "dhcp4_parser.yy"
    {
    ctx.stack_.back()->set("DhcpDdns", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3488 "dhcp4_parser.cc"
    break;

  case 621:
#line 2135 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3496 "dhcp4_parser.cc"
    break;

  case 622:
#line 2137 "dhcp4_parser.yy"
    {
    ctx.stack_.back()->set("Control-agent", yystack_[0].value.as < ElementPtr > ());
    ctx.leave();
}
#line 3505 "dhcp4_parser.cc"
    break;

  case 623:
#line 2142 "dhcp4_parser.yy"
    {
    ElementPtr i(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-control", i);
    ctx.stack_.push_back(i);
    ctx.enter(ctx.CONFIG_CONTROL);
}
#line 3516 "dhcp4_parser.cc"
    break;

  case 624:
#line 2147 "dhcp4_parser.yy"
    {
    // No config control params are required
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3526 "dhcp4_parser.cc"
    break;

  case 625:
#line 2153 "dhcp4_parser.yy"
    {
    // Parse the config-control map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3536 "dhcp4_parser.cc"
    break;

  case 626:
#line 2157 "dhcp4_parser.yy"
    {
    // No config_control params are required
    // parsing completed
}
#line 3545 "dhcp4_parser.cc"
    break;

  case 631:
#line 2172 "dhcp4_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-databases", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.CONFIG_DATABASE);
}
#line 3556 "dhcp4_parser.cc"
    break;

  case 632:
#line 2177 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3565 "dhcp4_parser.cc"
    break;

  case 633:
#line 2182 "dhcp4_parser.yy"
    {
    ElementPtr value(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("config-fetch-wait-time", value);
}
#line 3574 "dhcp4_parser.cc"
    break;

  case 634:
#line 2192 "dhcp4_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("Logging", m);
    ctx.stack_.push_back(m);
    ctx.enter(ctx.LOGGING);
}
#line 3585 "dhcp4_parser.cc"
    break;

  case 635:
#line 2197 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3594 "dhcp4_parser.cc"
    break;

  case 636:
#line 2202 "dhcp4_parser.yy"
    {
    // Parse the Logging map
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.push_back(m);
}
#line 3604 "dhcp4_parser.cc"
    break;

  case 637:
#line 2206 "dhcp4_parser.yy"
    {
    // parsing completed
}
#line 3612 "dhcp4_parser.cc"
    break;

  case 641:
#line 2222 "dhcp4_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("loggers", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.LOGGERS);
}
#line 3623 "dhcp4_parser.cc"
    break;

  case 642:
#line 2227 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3632 "dhcp4_parser.cc"
    break;

  case 645:
#line 2239 "dhcp4_parser.yy"
    {
    ElementPtr l(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(l);
    ctx.stack_.push_back(l);
}
#line 3642 "dhcp4_parser.cc"
    break;

  case 646:
#line 2243 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
}
#line 3650 "dhcp4_parser.cc"
    break;

  case 656:
#line 2260 "dhcp4_parser.yy"
    {
    ElementPtr dl(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("debuglevel", dl);
}
#line 3659 "dhcp4_parser.cc"
    break;

  case 657:
#line 2265 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3667 "dhcp4_parser.cc"
    break;

  case 658:
#line 2267 "dhcp4_parser.yy"
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("severity", sev);
    ctx.leave();
}
#line 3677 "dhcp4_parser.cc"
    break;

  case 659:
#line 2273 "dhcp4_parser.yy"
    {
    ElementPtr l(new ListElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output_options", l);
    ctx.stack_.push_back(l);
    ctx.enter(ctx.OUTPUT_OPTIONS);
}
#line 3688 "dhcp4_parser.cc"
    break;

  case 660:
#line 2278 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
    ctx.leave();
}
#line 3697 "dhcp4_parser.cc"
    break;

  case 663:
#line 2287 "dhcp4_parser.yy"
    {
    ElementPtr m(new MapElement(ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->add(m);
    ctx.stack_.push_back(m);
}
#line 3707 "dhcp4_parser.cc"
    break;

  case 664:
#line 2291 "dhcp4_parser.yy"
    {
    ctx.stack_.pop_back();
}
#line 3715 "dhcp4_parser.cc"
    break;

  case 671:
#line 2305 "dhcp4_parser.yy"
    {
    ctx.enter(ctx.NO_KEYWORD);
}
#line 3723 "dhcp4_parser.cc"
    break;

  case 672:
#line 2307 "dhcp4_parser.yy"
    {
    ElementPtr sev(new StringElement(yystack_[0].value.as < std::string > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("output", sev);
    ctx.leave();
}
#line 3733 "dhcp4_parser.cc"
    break;

  case 673:
#line 2313 "dhcp4_parser.yy"
    {
    ElementPtr flush(new BoolElement(yystack_[0].value.as < bool > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("flush", flush);
}
#line 3742 "dhcp4_parser.cc"
    break;

  case 674:
#line 2318 "dhcp4_parser.yy"
    {
    ElementPtr maxsize(new IntElement(yystack_[0].value.as < int64_t > (), ctx.loc2pos(yystack_[0].location)));
    ctx.stack_.back()->set("maxsize", maxsize);
}
#line 3751 "dhcp4_parser.cc"
    break;

  case 675:
#line 2323 "dhcp4_parser.yy"
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


  const short Dhcp4Parser::yypact_ninf_ = -847;

  const signed char Dhcp4Parser::yytable_ninf_ = -1;

  const short
  Dhcp4Parser::yypact_[] =
  {
     325,  -847,  -847,  -847,  -847,  -847,  -847,  -847,  -847,  -847,
    -847,  -847,  -847,  -847,  -847,    32,    22,    33,    40,    44,
      73,    95,   104,   108,   115,   121,   125,   135,   151,   158,
    -847,  -847,  -847,  -847,  -847,  -847,  -847,  -847,  -847,  -847,
    -847,  -847,  -847,  -847,  -847,  -847,  -847,  -847,  -847,  -847,
    -847,  -847,  -847,  -847,  -847,  -847,  -847,  -847,  -847,  -847,
    -847,  -847,  -847,  -847,  -847,  -847,  -847,  -847,    22,  -103,
       6,   145,    59,   272,    41,    15,    79,   237,   177,   -35,
     468,    51,    26,  -847,   206,   210,   221,   219,   228,  -847,
    -847,  -847,  -847,  -847,   231,  -847,    56,  -847,  -847,  -847,
    -847,  -847,  -847,  -847,  -847,  -847,   252,   285,   286,  -847,
    -847,  -847,  -847,  -847,  -847,   299,   300,   302,   303,   306,
     309,   316,   319,   322,  -847,  -847,  -847,  -847,  -847,  -847,
    -847,  -847,  -847,  -847,  -847,  -847,  -847,   323,  -847,  -847,
    -847,  -847,  -847,    58,  -847,  -847,  -847,  -847,  -847,  -847,
    -847,  -847,  -847,  -847,  -847,  -847,  -847,  -847,  -847,  -847,
    -847,  -847,  -847,  -847,  -847,  -847,  -847,  -847,  -847,  -847,
    -847,  -847,  -847,  -847,  -847,  -847,  -847,  -847,  -847,  -847,
    -847,  -847,  -847,  -847,  -847,  -847,  -847,   332,  -847,   105,
    -847,  -847,  -847,  -847,  -847,  -847,  -847,  -847,  -847,  -847,
    -847,  -847,  -847,   340,  -847,  -847,  -847,  -847,  -847,  -847,
    -847,  -847,  -847,  -847,  -847,  -847,  -847,  -847,   106,  -847,
    -847,  -847,  -847,  -847,  -847,  -847,  -847,  -847,  -847,  -847,
    -847,  -847,  -847,  -847,  -847,  -847,  -847,  -847,  -847,  -847,
    -847,  -847,  -847,   128,  -847,  -847,  -847,  -847,  -847,  -847,
    -847,  -847,  -847,  -847,  -847,  -847,  -847,  -847,  -847,  -847,
     330,   342,  -847,  -847,  -847,  -847,  -847,  -847,  -847,  -847,
    -847,  -847,  -847,  -847,   354,  -847,  -847,   359,  -847,  -847,
    -847,   362,  -847,  -847,   357,   371,  -847,  -847,  -847,  -847,
    -847,  -847,  -847,  -847,  -847,  -847,  -847,  -847,  -847,   374,
     382,  -847,  -847,  -847,  -847,   368,   389,  -847,  -847,  -847,
    -847,  -847,  -847,  -847,  -847,  -847,  -847,  -847,  -847,   138,
    -847,  -847,  -847,   394,  -847,  -847,   397,  -847,   399,   400,
    -847,  -847,   403,   404,  -847,  -847,  -847,  -847,  -847,  -847,
    -847,   142,  -847,  -847,  -847,  -847,  -847,  -847,  -847,  -847,
    -847,  -847,  -847,  -847,  -847,  -847,  -847,  -847,   149,  -847,
    -847,  -847,   408,   186,  -847,  -847,  -847,  -847,    22,    22,
    -847,   242,   414,   422,   423,   424,   438,  -847,     6,  -847,
     440,   446,   448,   217,   277,   283,   456,   460,   463,   464,
     471,   472,   304,   305,   307,   308,   324,   301,   333,   336,
     335,   476,   495,   508,   509,   510,   513,   514,   515,   516,
     517,   518,   519,   520,   351,   522,   523,   526,   528,   145,
    -847,   530,   531,   533,   365,    59,  -847,   540,   541,   542,
     543,   544,   545,   376,   550,   551,   552,   272,  -847,   553,
      41,  -847,   554,   555,   558,   559,   560,   561,   562,   563,
    -847,    15,  -847,   565,   567,   398,   569,   570,   571,   401,
    -847,   237,   572,   405,   406,  -847,   177,   574,   575,   -23,
    -847,   407,   576,   580,   411,   583,   415,   416,   587,   589,
     431,   432,   605,   606,   607,   608,   468,  -847,    51,  -847,
     611,   442,    26,  -847,  -847,  -847,   615,   614,   616,    22,
      22,    22,  -847,   617,   618,   619,  -847,  -847,  -847,   449,
     454,   455,   622,   623,   626,  -847,  -847,  -847,  -847,  -847,
    -847,  -847,  -847,  -847,   459,   628,   629,   630,   631,   632,
     465,   331,   635,   637,   638,   639,   640,  -847,   641,   632,
     642,   645,  -847,   646,    78,   146,  -847,  -847,   473,   479,
     480,   649,   482,   483,  -847,   646,   484,   651,  -847,   486,
    -847,   646,   487,   488,   489,   490,   491,   492,   493,  -847,
     494,   496,  -847,   497,   498,   499,  -847,  -847,   500,  -847,
    -847,  -847,   501,    22,  -847,  -847,   502,   503,  -847,   504,
    -847,  -847,    30,   505,  -847,  -847,   -37,   506,   507,   511,
    -847,  -847,   663,  -847,  -847,    22,   145,    51,  -847,  -847,
    -847,    26,    59,   613,  -847,  -847,  -847,   233,   233,   671,
    -847,   674,   675,   676,   678,  -847,  -847,  -847,  -847,  -847,
    -847,  -847,  -847,   116,   679,   680,   681,    68,    70,  -847,
     468,   682,  -847,  -847,  -847,  -847,  -847,  -847,  -847,  -847,
    -847,  -847,  -847,   683,  -847,  -847,  -847,  -847,    82,  -847,
    -847,  -847,  -847,  -847,  -847,  -847,  -847,  -847,  -847,  -847,
    -847,  -847,  -847,  -847,  -847,  -847,  -847,  -847,  -847,  -847,
    -847,  -847,  -847,  -847,  -847,  -847,  -847,  -847,  -847,  -847,
    -847,  -847,   671,  -847,   220,   230,   234,   238,  -847,   256,
    -847,  -847,  -847,  -847,  -847,  -847,   687,   688,   689,   690,
     691,  -847,  -847,  -847,  -847,   692,   693,   694,   695,   696,
    -847,   260,  -847,  -847,  -847,  -847,  -847,  -847,  -847,  -847,
    -847,  -847,  -847,  -847,  -847,  -847,  -847,  -847,  -847,  -847,
    -847,  -847,   289,  -847,   697,   698,  -847,  -847,   699,   701,
    -847,  -847,   700,   704,  -847,  -847,   702,   706,  -847,  -847,
     705,   707,  -847,  -847,  -847,  -847,  -847,  -847,    76,  -847,
    -847,  -847,  -847,  -847,  -847,  -847,   218,  -847,  -847,   708,
     709,  -847,  -847,   710,   712,  -847,   713,   714,   715,   716,
     717,   718,   311,  -847,  -847,  -847,  -847,  -847,  -847,  -847,
    -847,  -847,  -847,  -847,  -847,   334,  -847,  -847,  -847,   343,
    -847,   241,  -847,   529,  -847,   719,   720,  -847,  -847,  -847,
    -847,   721,   722,  -847,  -847,  -847,  -847,   723,   613,  -847,
     726,   727,   728,   729,   539,   548,   564,   566,   573,   730,
     731,   732,   733,   577,   578,   579,   581,   568,   233,  -847,
    -847,   233,  -847,   671,   272,  -847,   674,   237,  -847,   675,
     177,  -847,   676,   444,  -847,   678,   116,  -847,    63,   679,
    -847,    15,  -847,   680,   -35,  -847,   681,   582,   584,   585,
     586,   588,   590,    68,  -847,   735,   736,    70,  -847,  -847,
     -22,   682,  -847,  -847,   737,   738,    41,  -847,   683,   741,
    -847,  -847,   592,  -847,   402,   593,   594,   595,  -847,  -847,
    -847,  -847,  -847,   596,   597,   598,   599,  -847,  -847,  -847,
    -847,  -847,  -847,   344,  -847,   345,  -847,   740,  -847,   742,
    -847,  -847,  -847,  -847,  -847,  -847,  -847,  -847,  -847,  -847,
    -847,  -847,  -847,  -847,  -847,  -847,  -847,  -847,   361,  -847,
    -847,  -847,  -847,  -847,  -847,  -847,  -847,  -847,  -847,  -847,
     745,  -847,  -847,  -847,  -847,  -847,  -847,  -847,  -847,  -847,
     746,   743,  -847,  -847,  -847,  -847,  -847,   749,  -847,   372,
    -847,  -847,  -847,  -847,  -847,  -847,  -847,  -847,   600,   601,
    -847,  -847,   757,  -847,  -847,  -847,  -847,  -847,   379,  -847,
    -847,  -847,  -847,  -847,  -847,   602,   381,  -847,   646,  -847,
    -847,  -847,  -847,  -847,  -847,  -847,  -847,  -847,  -847,  -847,
    -847,  -847,  -847,  -847,  -847,  -847,   444,  -847,   759,   603,
    -847,    63,  -847,  -847,  -847,  -847,   772,   604,   773,   -22,
    -847,  -847,  -847,  -847,  -847,   609,  -847,  -847,   775,  -847,
     610,  -847,  -847,   774,  -847,  -847,   254,  -847,   141,   774,
    -847,  -847,   781,   782,   785,   387,  -847,  -847,  -847,  -847,
    -847,  -847,   787,   621,   625,   633,   141,  -847,   652,  -847,
    -847,  -847,  -847,  -847
  };

  const unsigned short
  Dhcp4Parser::yydefact_[] =
  {
       0,     2,     4,     6,     8,    10,    12,    14,    16,    18,
      20,    22,    24,    26,    28,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       1,    45,    38,    34,    33,    30,    31,    32,    37,     3,
      35,    36,    58,     5,    70,     7,   139,     9,   282,    11,
     447,    13,   472,    15,   372,    17,   380,    19,   417,    21,
     247,    23,   564,    25,   636,    27,   625,    29,    47,    41,
       0,     0,     0,     0,     0,   474,     0,   382,   419,     0,
       0,     0,     0,    49,     0,    48,     0,     0,    42,    68,
     634,   617,   619,   621,     0,    67,     0,    60,    62,    64,
      65,    66,    63,   623,   128,   154,     0,     0,     0,   493,
     495,   497,   152,   161,   163,     0,     0,     0,     0,     0,
       0,     0,     0,     0,   123,   274,   370,   409,   336,   460,
     462,   329,   225,   521,   464,   239,   258,     0,   547,   560,
     562,   641,   113,     0,    72,    74,    75,    76,    77,    78,
     109,   110,   111,    79,   107,    96,    97,    98,    82,    83,
     104,    84,    85,    86,    90,    91,    80,   108,    81,    88,
      89,   102,   103,   105,    99,   100,   101,    87,    92,    93,
      94,    95,   106,   112,   141,   143,   147,     0,   138,     0,
     130,   132,   133,   134,   135,   136,   137,   317,   319,   321,
     439,   315,   323,     0,   327,   325,   517,   314,   286,   287,
     288,   289,   290,   311,   312,   313,   301,   302,     0,   284,
     293,   306,   307,   308,   294,   296,   297,   299,   295,   291,
     292,   309,   310,   298,   303,   304,   305,   300,   458,   457,
     453,   454,   452,     0,   449,   451,   455,   456,   515,   503,
     505,   509,   507,   513,   511,   499,   492,   486,   490,   491,
       0,   475,   476,   487,   488,   489,   483,   478,   484,   480,
     481,   482,   485,   479,     0,   399,   206,     0,   403,   401,
     406,     0,   395,   396,     0,   383,   384,   386,   398,   387,
     388,   389,   405,   390,   391,   392,   393,   394,   433,     0,
       0,   431,   432,   435,   436,     0,   420,   421,   423,   424,
     425,   426,   427,   428,   429,   430,   254,   256,   251,     0,
     249,   252,   253,     0,   587,   589,     0,   592,     0,     0,
     596,   600,     0,     0,   604,   611,   613,   615,   585,   583,
     584,     0,   566,   568,   569,   570,   571,   572,   573,   574,
     575,   576,   577,   578,   579,   580,   581,   582,     0,   638,
     640,   631,     0,     0,   627,   629,   630,    46,     0,     0,
      39,     0,     0,     0,     0,     0,     0,    57,     0,    59,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      71,     0,     0,     0,     0,     0,   140,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   283,     0,
       0,   448,     0,     0,     0,     0,     0,     0,     0,     0,
     473,     0,   373,     0,     0,     0,     0,     0,     0,     0,
     381,     0,     0,     0,     0,   418,     0,     0,     0,     0,
     248,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   565,     0,   637,
       0,     0,     0,   626,    50,    43,     0,     0,     0,     0,
       0,     0,    61,     0,     0,     0,   125,   126,   127,     0,
       0,     0,     0,     0,     0,   114,   115,   116,   117,   118,
     119,   120,   121,   122,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   546,     0,     0,
       0,     0,    73,     0,     0,     0,   151,   131,     0,     0,
       0,     0,     0,     0,   335,     0,     0,     0,   285,     0,
     450,     0,     0,     0,     0,     0,     0,     0,     0,   477,
       0,     0,   397,     0,     0,     0,   408,   385,     0,   437,
     438,   422,     0,     0,   250,   586,     0,     0,   591,     0,
     594,   595,     0,     0,   602,   603,     0,     0,     0,     0,
     567,   639,     0,   633,   628,     0,     0,     0,   618,   620,
     622,     0,     0,     0,   494,   496,   498,     0,     0,   165,
     124,   276,   374,   411,   338,    40,   461,   463,   331,   332,
     333,   334,   330,     0,     0,   466,   241,     0,     0,   561,
       0,     0,    51,   142,   145,   146,   144,   149,   150,   148,
     318,   320,   322,   441,   316,   324,   328,   326,     0,   459,
     516,   504,   506,   510,   508,   514,   512,   500,   400,   207,
     404,   402,   407,   434,   255,   257,   588,   590,   593,   598,
     599,   597,   601,   606,   607,   608,   609,   610,   605,   612,
     614,   616,   165,    44,     0,     0,     0,     0,   159,     0,
     156,   158,   193,   199,   201,   203,     0,     0,     0,     0,
       0,   215,   217,   219,   221,     0,     0,     0,     0,     0,
     192,     0,   171,   173,   174,   175,   176,   177,   178,   179,
     180,   181,   182,   186,   187,   188,   183,   189,   190,   191,
     184,   185,     0,   169,     0,   166,   167,   280,     0,   277,
     278,   378,     0,   375,   376,   415,     0,   412,   413,   342,
       0,   339,   340,   234,   235,   236,   237,   238,     0,   227,
     229,   230,   231,   232,   233,   525,     0,   523,   470,     0,
     467,   468,   245,     0,   242,   243,     0,     0,     0,     0,
       0,     0,     0,   260,   262,   263,   264,   265,   266,   267,
     556,   558,   555,   553,   554,     0,   549,   551,   552,     0,
     645,     0,   643,    53,   445,     0,   442,   443,   501,   519,
     520,     0,     0,    69,   635,   624,   129,     0,     0,   155,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,   153,
     162,     0,   164,     0,     0,   275,     0,   382,   371,     0,
     419,   410,     0,     0,   337,     0,     0,   226,   527,     0,
     522,   474,   465,     0,     0,   240,     0,     0,     0,     0,
       0,     0,     0,     0,   259,     0,     0,     0,   548,   563,
       0,     0,   642,    55,     0,    54,     0,   440,     0,     0,
     518,   632,     0,   157,     0,     0,     0,     0,   205,   208,
     209,   210,   211,     0,     0,     0,     0,   223,   224,   212,
     213,   214,   172,     0,   168,     0,   279,     0,   377,     0,
     414,   369,   361,   362,   363,   349,   350,   366,   367,   368,
     352,   353,   346,   347,   348,   359,   360,   358,     0,   344,
     351,   364,   365,   354,   355,   356,   357,   341,   228,   543,
       0,   541,   542,   534,   535,   539,   540,   536,   537,   538,
       0,   528,   529,   531,   532,   533,   524,     0,   469,     0,
     244,   268,   269,   270,   271,   272,   273,   261,     0,     0,
     550,   659,     0,   657,   655,   649,   653,   654,     0,   647,
     651,   652,   650,   644,    52,     0,     0,   444,     0,   160,
     195,   196,   197,   198,   194,   200,   202,   204,   216,   218,
     220,   222,   170,   281,   379,   416,     0,   343,     0,     0,
     526,     0,   471,   246,   557,   559,     0,     0,     0,     0,
     646,    56,   446,   502,   345,     0,   545,   530,     0,   656,
       0,   648,   544,     0,   658,   663,     0,   661,     0,     0,
     660,   671,     0,     0,     0,     0,   665,   667,   668,   669,
     670,   662,     0,     0,     0,     0,     0,   664,     0,   673,
     674,   675,   666,   672
  };

  const short
  Dhcp4Parser::yypgoto_[] =
  {
    -847,  -847,  -847,  -847,  -847,  -847,  -847,  -847,  -847,  -847,
    -847,  -847,  -847,  -847,  -847,  -847,   -44,  -847,  -483,  -847,
     187,  -847,  -847,  -847,  -847,  -847,  -847,  -525,  -847,  -847,
    -847,   -70,  -847,  -847,  -847,   417,  -847,  -847,  -847,  -847,
     200,   373,   -54,   -24,    -5,    -4,    -1,    11,    14,    17,
    -847,  -847,  -847,  -847,    21,    25,  -847,  -847,   198,   388,
    -847,  -847,  -847,  -847,  -847,  -847,  -847,  -847,  -847,  -847,
    -847,  -847,  -847,  -847,  -847,  -847,   -16,  -847,  -847,  -847,
    -847,  -847,  -847,   123,  -847,   -31,  -847,  -603,   -30,  -847,
    -847,  -847,  -847,  -847,  -847,  -847,  -847,  -847,  -847,   -36,
    -847,  -847,  -847,  -847,  -847,  -847,  -847,  -847,  -847,  -847,
    -847,  -847,  -847,  -847,  -847,  -847,  -847,  -847,  -847,  -847,
    -847,   -33,  -847,  -847,  -847,  -847,  -847,  -847,  -847,  -847,
    -847,   -47,  -847,  -847,  -847,   -38,   378,  -847,  -847,  -847,
    -847,  -847,  -847,  -847,   -42,  -847,  -847,  -847,  -847,  -847,
    -847,  -846,  -847,  -847,  -847,   -14,  -847,  -847,  -847,    -9,
     420,  -847,  -847,  -847,  -847,  -847,  -847,  -847,  -847,  -845,
    -847,    23,  -847,    29,  -847,    28,  -847,  -847,  -847,  -847,
    -847,  -847,  -847,     7,  -847,  -847,  -143,   -65,  -847,  -847,
    -847,  -847,  -847,    31,  -847,  -847,  -847,    36,  -847,   426,
    -847,   -72,  -847,  -847,  -847,  -847,  -847,   -64,  -847,  -847,
    -847,  -847,  -847,   -40,  -847,  -847,  -847,    27,  -847,  -847,
    -847,    34,  -847,   419,  -847,  -847,  -847,  -847,  -847,  -847,
    -847,  -847,  -847,  -847,  -847,    -3,  -847,  -847,  -847,     0,
     457,  -847,  -847,   -52,  -847,   -20,  -847,   -60,  -847,  -847,
    -847,    35,  -847,  -847,  -847,    38,  -847,   447,    -8,  -847,
      -2,  -847,    10,  -847,   243,  -847,  -847,  -847,  -847,  -847,
    -847,  -847,  -847,  -847,  -847,  -847,  -847,  -847,  -847,  -847,
    -847,  -847,  -826,  -847,  -847,  -847,  -847,  -847,    37,  -847,
    -847,  -847,  -132,  -847,  -847,  -847,  -847,  -847,  -847,  -847,
    -847,    13,  -847,  -847,  -847,  -847,  -847,  -847,  -847,  -847,
    -847,  -847,   262,   418,  -847,  -847,  -847,  -847,  -847,  -847,
    -847,  -847,  -847,  -847,  -847,  -847,  -847,  -847,  -847,  -847,
    -847,  -847,  -847,  -847,  -847,  -847,  -847,  -847,  -847,  -847,
    -847,  -847,  -847,  -847,  -847,  -847,  -847,  -847,  -847,  -847,
     292,   413,  -847,  -847,  -847,  -847,  -847,  -847,  -847,   310,
     425,   -69,  -847,  -847,    16,  -847,  -847,  -129,  -847,  -847,
    -847,  -847,  -847,  -847,  -148,  -847,  -847,  -164,  -847,  -847,
    -847,  -847,  -847
  };

  const short
  Dhcp4Parser::yydefgoto_[] =
  {
      -1,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    29,    38,    39,    40,    69,
     626,    87,    88,    41,    68,    84,    85,   643,   813,   894,
     895,   720,    43,    70,    96,    97,    98,   372,    45,    71,
     143,   144,   145,   146,   147,   148,   149,   150,   151,   152,
     153,   154,   401,   155,   156,   157,   158,   381,   189,   190,
      47,    72,   191,   421,   192,   422,   646,   193,   423,   649,
     194,   159,   389,   160,   382,   699,   700,   701,   827,   161,
     390,   162,   391,   744,   745,   746,   851,   721,   722,   723,
     830,  1014,   724,   831,   725,   832,   726,   833,   727,   728,
     454,   729,   730,   731,   732,   733,   734,   735,   736,   839,
     737,   840,   738,   841,   739,   842,   740,   741,   163,   409,
     768,   769,   770,   771,   772,   773,   774,   164,   412,   783,
     784,   785,   874,    61,    79,   319,   320,   321,   467,   322,
     468,   165,   413,   792,   793,   794,   795,   796,   797,   798,
     799,   166,   402,   748,   749,   750,   854,    49,    73,   218,
     219,   220,   431,   221,   427,   222,   428,   223,   429,   224,
     432,   225,   435,   226,   434,   167,   408,   632,   228,   168,
     405,   760,   761,   762,   863,   948,   949,   169,   403,    55,
      76,   752,   753,   754,   857,    57,    77,   284,   285,   286,
     287,   288,   289,   290,   453,   291,   457,   292,   456,   293,
     294,   458,   295,   170,   404,   756,   757,   758,   860,    59,
      78,   305,   306,   307,   308,   309,   462,   310,   311,   312,
     313,   230,   430,   815,   816,   817,   896,    51,    74,   243,
     244,   245,   439,   171,   406,   172,   407,   173,   411,   779,
     780,   781,   871,    53,    75,   260,   261,   262,   174,   386,
     175,   387,   176,   388,   266,   449,   820,   899,   267,   443,
     268,   444,   269,   446,   270,   445,   271,   448,   272,   447,
     273,   442,   237,   436,   821,   177,   410,   776,   777,   868,
     970,   971,   972,   973,   974,  1028,   975,   178,   179,   415,
     805,   806,   807,   885,   808,   886,   180,   416,   181,   417,
      63,    80,   341,   342,   343,   344,   472,   345,   473,   346,
     347,   475,   348,   349,   350,   478,   681,   351,   479,   352,
     353,   354,   482,   688,   355,   483,   356,   484,   357,   485,
      99,   374,   100,   375,   101,   376,   182,   380,    67,    82,
     363,   364,   365,   490,   366,   102,   373,    65,    81,   358,
     359,   183,   418,   811,   812,   890,   998,   999,  1000,  1001,
    1038,  1002,  1036,  1056,  1057,  1058,  1065,  1066,  1067,  1072,
    1068,  1069,  1070
  };

  const unsigned short
  Dhcp4Parser::yytable_[] =
  {
      95,   142,   188,   207,   239,   256,   303,   282,   301,   318,
     338,   274,   360,   233,   304,   742,    89,   943,   944,   208,
     195,   231,   246,   258,    83,   296,   314,    31,   339,    32,
     656,    33,    30,   229,   242,   257,   660,   956,   361,   362,
      42,   283,   302,   109,   110,   111,   625,    44,   679,   209,
     276,    46,   196,   232,   247,   259,   625,   297,   315,   378,
     340,   419,   129,   130,   379,   234,   420,   263,   210,   211,
      86,   235,   212,   264,   184,   185,   316,   317,   186,   866,
      48,   187,   867,   236,   213,   265,   127,   214,   316,   317,
     215,   109,   110,   111,   216,   644,   645,   240,   217,   129,
     130,   227,    50,   241,   683,   684,   685,   686,   425,   437,
     248,    52,   127,   426,   438,    54,   249,   250,   251,   252,
     253,   254,    56,   255,   238,   129,   130,   991,    58,   992,
     993,   440,    60,   126,   127,   276,   441,   204,    94,   687,
     205,   469,    62,   129,   130,   486,   470,   129,   130,   126,
     487,    94,   488,    90,   129,   130,   103,   489,    64,   104,
     959,   960,    91,    92,    93,    66,   647,   648,   105,   680,
     106,   107,   108,   109,   110,   111,   112,   113,   114,    94,
     943,   944,   786,   787,   788,   789,   790,   791,    94,   492,
     255,   818,   800,   801,   493,    34,    35,    36,    37,   141,
     956,   115,   116,   117,   118,   119,   120,   121,   122,   123,
     124,   125,   367,   368,    94,   126,   127,   763,   764,   765,
     766,   869,   767,   419,   870,   369,   128,   370,   823,   129,
     130,   371,    94,   488,   131,   377,    94,   492,   824,   132,
     133,   425,   825,    94,   891,   134,   826,   892,   923,   276,
     298,   277,   278,   299,   300,   135,   383,  1059,   136,   828,
    1060,   129,   130,   848,   829,   137,   138,   702,   849,   139,
     140,   275,   703,   704,   705,   706,   707,   708,   709,   710,
     711,   712,   713,   714,   715,   716,   717,   718,   719,   384,
     385,  1061,   848,   141,  1062,  1063,  1064,   850,   107,   108,
     109,   110,   111,   392,   393,   276,   394,   395,    95,   276,
     396,   277,   278,   397,   883,   279,   280,   281,    94,   884,
     398,   129,   130,   399,   494,   495,   400,   414,   115,   116,
     117,   118,   119,   120,   121,   122,   424,   887,   450,   197,
     198,   199,   888,   127,   433,   451,   486,   848,   437,   142,
      94,   889,  1022,  1023,   200,   188,   129,   130,   201,   202,
     203,   131,   452,   455,  1026,   460,   459,   207,   204,  1027,
     239,   205,   134,   195,   461,   469,   465,   233,   463,   206,
    1033,   256,  1039,   208,   440,   231,   464,  1040,   246,  1042,
    1076,   282,   466,   506,   303,  1077,   301,   229,   471,   258,
     242,   474,   304,   476,   477,   196,    94,   480,   481,   296,
      94,   257,   491,   209,   314,   496,   338,   232,   497,   360,
     247,   628,   629,   630,   631,   283,   498,   499,   500,   234,
     302,   259,   210,   211,   339,   235,   212,  1010,  1011,  1012,
    1013,   297,   501,   263,   503,    94,   315,   236,   213,   264,
     504,   214,   505,   507,   215,   608,   609,   610,   216,   508,
     509,   265,   217,   240,   510,   227,   340,   511,   512,   241,
     107,   108,   109,   110,   111,   513,   514,   520,   515,   516,
     524,   517,   518,  1043,     1,     2,     3,     4,     5,     6,
       7,     8,     9,    10,    11,    12,    13,    14,   519,   525,
     115,   116,   117,   118,   119,   120,   121,   122,   521,   523,
     125,   522,   526,   527,   528,   127,   276,   529,   530,   531,
     532,   533,   534,   535,   536,   537,   538,   539,   129,   130,
     540,   202,   541,   131,   543,   544,   142,   545,   360,   675,
     204,   546,   188,   205,   548,   549,   550,   551,   552,   553,
     554,   206,   129,   130,   555,   556,   557,   559,   561,   562,
     195,   693,   563,   564,   565,   566,   567,   568,   802,   570,
     338,   571,   572,   573,   574,   575,   578,   576,   582,   583,
     586,   579,   580,   585,   587,   588,   803,   589,   339,   590,
     591,   592,   196,   593,   323,   324,   325,   326,   327,   328,
     329,   330,   331,   332,   333,   334,   335,   594,   595,   596,
     597,   598,   599,   336,   337,   602,   603,    94,   804,   605,
     340,   606,   614,   607,   611,   612,   613,   615,   616,   617,
     618,   619,   620,   621,   622,   623,   624,   698,   627,    32,
     633,    94,   634,   635,   636,   682,   650,   637,   638,   640,
     641,   642,   651,   652,   653,   654,   655,   657,   658,   659,
     661,   662,   663,   664,   665,   666,   667,   668,   692,   669,
     670,   671,   672,   673,   674,   676,   677,   678,   743,   689,
     690,   747,   751,   755,   691,   759,   775,   778,   782,   810,
     814,   834,   835,   836,   837,   838,   843,   844,   845,   846,
     847,   853,   893,   852,   856,   855,   858,   859,   861,   862,
     865,   864,   873,   908,   872,   876,   875,   877,   878,   879,
     880,   881,   882,   898,   909,   897,   639,   902,   901,   900,
     904,   905,   906,   907,   913,   914,   915,   916,   910,   988,
     989,  1005,   911,  1004,   921,  1008,  1031,   912,  1024,  1029,
    1025,   917,   918,   919,  1030,   920,   981,  1032,   982,   983,
     984,  1037,   985,  1045,   986,  1009,  1015,  1016,  1017,  1018,
    1019,  1020,  1021,  1034,  1035,  1041,  1048,  1050,  1049,  1046,
    1053,  1055,  1052,  1054,   207,  1073,  1074,   282,   303,  1075,
     301,  1078,   542,   931,   233,   502,   304,  1079,   961,  1080,
     208,   256,   231,   963,   318,   296,   694,  1081,   314,   932,
     697,   951,   903,   547,   229,   822,   965,   802,   922,   258,
     994,   283,   924,   950,   302,  1083,   239,   942,   964,   980,
     209,   257,   962,   958,   232,   803,   979,   297,   996,   933,
     315,   987,   926,   952,   246,   925,   234,   584,   966,   210,
     211,   259,   235,   212,   995,   953,   242,   558,   934,   935,
     967,   954,   936,   263,   236,   213,   968,   804,   214,   264,
     997,   215,   957,   955,   937,   216,   247,   938,   969,   217,
     939,   265,   227,  1044,   940,   581,   945,   577,   941,   930,
     928,   947,   946,   927,   929,  1007,  1006,   560,   569,  1047,
     990,   819,   809,   696,   600,   604,   976,  1003,   978,   977,
    1051,  1071,  1082,   601,     0,     0,     0,   695,     0,   240,
       0,     0,     0,     0,     0,   241,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,   931,     0,     0,     0,
       0,   961,     0,     0,     0,     0,   963,     0,     0,   994,
       0,     0,   932,     0,   951,     0,     0,     0,     0,   965,
       0,     0,     0,     0,     0,     0,   950,   996,     0,     0,
     942,   964,     0,     0,     0,   962,     0,     0,     0,     0,
       0,     0,   933,   995,     0,     0,   952,     0,     0,     0,
       0,   966,     0,     0,     0,     0,     0,     0,   953,   997,
       0,   934,   935,   967,   954,   936,     0,     0,     0,   968,
       0,     0,     0,     0,     0,     0,   955,   937,     0,     0,
     938,   969,     0,   939,     0,     0,     0,   940,     0,   945,
       0,   941,     0,     0,   947,   946
  };

  const short
  Dhcp4Parser::yycheck_[] =
  {
      70,    71,    72,    73,    74,    75,    78,    77,    78,    79,
      80,    76,    81,    73,    78,   618,    10,   863,   863,    73,
      72,    73,    74,    75,    68,    77,    78,     5,    80,     7,
     555,     9,     0,    73,    74,    75,   561,   863,    12,    13,
       7,    77,    78,    28,    29,    30,   529,     7,    18,    73,
      72,     7,    72,    73,    74,    75,   539,    77,    78,     3,
      80,     3,    84,    85,     8,    73,     8,    75,    73,    73,
     173,    73,    73,    75,    15,    16,   111,   112,    19,     3,
       7,    22,     6,    73,    73,    75,    71,    73,   111,   112,
      73,    28,    29,    30,    73,    17,    18,    74,    73,    84,
      85,    73,     7,    74,   141,   142,   143,   144,     3,     3,
      95,     7,    71,     8,     8,     7,   101,   102,   103,   104,
     105,   106,     7,   108,    83,    84,    85,   149,     7,   151,
     152,     3,     7,    70,    71,    72,     8,    96,   173,   176,
      99,     3,     7,    84,    85,     3,     8,    84,    85,    70,
       8,   173,     3,   147,    84,    85,    11,     8,     7,    14,
      97,    98,   156,   157,   158,     7,    20,    21,    23,   139,
      25,    26,    27,    28,    29,    30,    31,    32,    33,   173,
    1026,  1026,   114,   115,   116,   117,   118,   119,   173,     3,
     108,   109,   122,   123,     8,   173,   174,   175,   176,   148,
    1026,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,     6,     3,   173,    70,    71,   101,   102,   103,
     104,     3,   106,     3,     6,     4,    81,     8,     8,    84,
      85,     3,   173,     3,    89,     4,   173,     3,     8,    94,
      95,     3,     8,   173,     3,   100,     8,     6,   851,    72,
      73,    74,    75,    76,    77,   110,     4,     3,   113,     3,
       6,    84,    85,     3,     8,   120,   121,    34,     8,   124,
     125,    34,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    51,    52,    53,    54,    55,     4,
       4,   150,     3,   148,   153,   154,   155,     8,    26,    27,
      28,    29,    30,     4,     4,    72,     4,     4,   378,    72,
       4,    74,    75,     4,     3,    78,    79,    80,   173,     8,
       4,    84,    85,     4,   368,   369,     4,     4,    56,    57,
      58,    59,    60,    61,    62,    63,     4,     3,     8,    67,
      68,    69,     8,    71,     4,     3,     3,     3,     3,   419,
     173,     8,     8,     8,    82,   425,    84,    85,    86,    87,
      88,    89,     8,     4,     3,     8,     4,   437,    96,     8,
     440,    99,   100,   425,     3,     3,     8,   437,     4,   107,
       8,   451,     3,   437,     3,   437,     4,     8,   440,     8,
       3,   461,     3,   176,   466,     8,   466,   437,     4,   451,
     440,     4,   466,     4,     4,   425,   173,     4,     4,   461,
     173,   451,     4,   437,   466,   173,   486,   437,     4,   488,
     440,    90,    91,    92,    93,   461,     4,     4,     4,   437,
     466,   451,   437,   437,   486,   437,   437,    35,    36,    37,
      38,   461,     4,   451,     4,   173,   466,   437,   437,   451,
       4,   437,     4,   176,   437,   499,   500,   501,   437,   176,
       4,   451,   437,   440,     4,   437,   486,     4,     4,   440,
      26,    27,    28,    29,    30,     4,     4,   176,   174,   174,
       4,   174,   174,  1008,   159,   160,   161,   162,   163,   164,
     165,   166,   167,   168,   169,   170,   171,   172,   174,     4,
      56,    57,    58,    59,    60,    61,    62,    63,   175,   174,
      66,   175,     4,     4,     4,    71,    72,     4,     4,     4,
       4,     4,     4,     4,     4,   174,     4,     4,    84,    85,
       4,    87,     4,    89,     4,     4,   606,     4,   607,   583,
      96,   176,   612,    99,     4,     4,     4,     4,     4,     4,
     174,   107,    84,    85,     4,     4,     4,     4,     4,     4,
     612,   605,     4,     4,     4,     4,     4,     4,   638,     4,
     640,     4,   174,     4,     4,     4,     4,   176,     4,     4,
       4,   176,   176,   176,     4,   174,   638,     4,   640,   174,
     174,     4,   612,     4,   126,   127,   128,   129,   130,   131,
     132,   133,   134,   135,   136,   137,   138,   176,   176,     4,
       4,     4,     4,   145,   146,     4,   174,   173,   638,     4,
     640,     7,   173,     7,     7,     7,     7,   173,   173,     7,
       7,     5,   173,     5,     5,     5,     5,    24,   173,     7,
       5,   173,     5,     5,     5,   140,   173,     7,     7,     7,
       5,     5,   173,   173,     5,   173,   173,   173,     7,   173,
     173,   173,   173,   173,   173,   173,   173,   173,     5,   173,
     173,   173,   173,   173,   173,   173,   173,   173,     7,   173,
     173,     7,     7,     7,   173,     7,     7,     7,     7,     7,
       7,     4,     4,     4,     4,     4,     4,     4,     4,     4,
       4,     3,   173,     6,     3,     6,     6,     3,     6,     3,
       3,     6,     3,   174,     6,     3,     6,     4,     4,     4,
       4,     4,     4,     3,   176,     6,   539,     4,     6,     8,
       4,     4,     4,     4,     4,     4,     4,     4,   174,     4,
       4,     3,   176,     6,   176,     4,     3,   174,     8,     4,
       8,   174,   174,   174,     8,   174,   174,     8,   174,   174,
     174,     4,   174,     4,   174,   173,   173,   173,   173,   173,
     173,   173,   173,   173,   173,   173,     4,     4,   174,   176,
       5,     7,   173,   173,   854,     4,     4,   857,   860,     4,
     860,     4,   419,   863,   854,   378,   860,   176,   868,   174,
     854,   871,   854,   868,   874,   857,   606,   174,   860,   863,
     612,   863,   828,   425,   854,   692,   868,   887,   848,   871,
     890,   857,   853,   863,   860,   173,   896,   863,   868,   876,
     854,   871,   868,   866,   854,   887,   874,   857,   890,   863,
     860,   883,   856,   863,   896,   854,   854,   469,   868,   854,
     854,   871,   854,   854,   890,   863,   896,   437,   863,   863,
     868,   863,   863,   871,   854,   854,   868,   887,   854,   871,
     890,   854,   865,   863,   863,   854,   896,   863,   868,   854,
     863,   871,   854,  1026,   863,   466,   863,   461,   863,   862,
     859,   863,   863,   857,   860,   898,   896,   440,   451,  1031,
     887,   658,   640,   611,   486,   492,   869,   891,   873,   871,
    1039,  1059,  1076,   488,    -1,    -1,    -1,   607,    -1,   896,
      -1,    -1,    -1,    -1,    -1,   896,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,  1026,    -1,    -1,    -1,
      -1,  1031,    -1,    -1,    -1,    -1,  1031,    -1,    -1,  1039,
      -1,    -1,  1026,    -1,  1026,    -1,    -1,    -1,    -1,  1031,
      -1,    -1,    -1,    -1,    -1,    -1,  1026,  1039,    -1,    -1,
    1026,  1031,    -1,    -1,    -1,  1031,    -1,    -1,    -1,    -1,
      -1,    -1,  1026,  1039,    -1,    -1,  1026,    -1,    -1,    -1,
      -1,  1031,    -1,    -1,    -1,    -1,    -1,    -1,  1026,  1039,
      -1,  1026,  1026,  1031,  1026,  1026,    -1,    -1,    -1,  1031,
      -1,    -1,    -1,    -1,    -1,    -1,  1026,  1026,    -1,    -1,
    1026,  1031,    -1,  1026,    -1,    -1,    -1,  1026,    -1,  1026,
      -1,  1026,    -1,    -1,  1026,  1026
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
     125,   148,   208,   217,   218,   219,   220,   221,   222,   223,
     224,   225,   226,   227,   228,   230,   231,   232,   233,   248,
     250,   256,   258,   295,   304,   318,   328,   352,   356,   364,
     390,   420,   422,   424,   435,   437,   439,   462,   474,   475,
     483,   485,   523,   538,    15,    16,    19,    22,   208,   235,
     236,   239,   241,   244,   247,   420,   422,    67,    68,    69,
      82,    86,    87,    88,    96,    99,   107,   208,   219,   220,
     221,   222,   223,   224,   225,   226,   231,   232,   336,   337,
     338,   340,   342,   344,   346,   348,   350,   352,   355,   390,
     408,   420,   422,   424,   435,   437,   439,   459,    83,   208,
     348,   350,   390,   416,   417,   418,   420,   422,    95,   101,
     102,   103,   104,   105,   106,   108,   208,   390,   420,   422,
     432,   433,   434,   435,   437,   439,   441,   445,   447,   449,
     451,   453,   455,   457,   364,    34,    72,    74,    75,    78,
      79,    80,   208,   276,   374,   375,   376,   377,   378,   379,
     380,   382,   384,   386,   387,   389,   420,   422,    73,    76,
      77,   208,   276,   378,   384,   398,   399,   400,   401,   402,
     404,   405,   406,   407,   420,   422,   111,   112,   208,   312,
     313,   314,   316,   126,   127,   128,   129,   130,   131,   132,
     133,   134,   135,   136,   137,   138,   145,   146,   208,   420,
     422,   489,   490,   491,   492,   494,   496,   497,   499,   500,
     501,   504,   506,   507,   508,   511,   513,   515,   536,   537,
     538,    12,    13,   527,   528,   529,   531,     6,     3,     4,
       8,     3,   214,   533,   518,   520,   522,     4,     3,     8,
     524,   234,   251,     4,     4,     4,   436,   438,   440,   249,
     257,   259,     4,     4,     4,     4,     4,     4,     4,     4,
       4,   229,   329,   365,   391,   357,   421,   423,   353,   296,
     463,   425,   305,   319,     4,   476,   484,   486,   539,     3,
       8,   240,   242,   245,     4,     3,     8,   341,   343,   345,
     409,   339,   347,     4,   351,   349,   460,     3,     8,   419,
       3,     8,   458,   446,   448,   452,   450,   456,   454,   442,
       8,     3,     8,   381,   277,     4,   385,   383,   388,     4,
       8,     3,   403,     4,     4,     8,     3,   315,   317,     3,
       8,     4,   493,   495,     4,   498,     4,     4,   502,   505,
       4,     4,   509,   512,   514,   516,     3,     8,     3,     8,
     530,     4,     3,     8,   193,   193,   173,     4,     4,     4,
       4,     4,   212,     4,     4,     4,   176,   176,   176,     4,
       4,     4,     4,     4,     4,   174,   174,   174,   174,   174,
     176,   175,   175,   174,     4,     4,     4,     4,     4,     4,
       4,     4,     4,     4,     4,     4,     4,   174,     4,     4,
       4,     4,   218,     4,     4,     4,   176,   236,     4,     4,
       4,     4,     4,     4,   174,     4,     4,     4,   337,     4,
     417,     4,     4,     4,     4,     4,     4,     4,     4,   434,
       4,     4,   174,     4,     4,     4,   176,   376,     4,   176,
     176,   400,     4,     4,   313,   176,     4,     4,   174,     4,
     174,   174,     4,     4,   176,   176,     4,     4,     4,     4,
     490,   537,     4,   174,   528,     4,     7,     7,   193,   193,
     193,     7,     7,     7,   173,   173,   173,     7,     7,     5,
     173,     5,     5,     5,     5,   195,   197,   173,    90,    91,
      92,    93,   354,     5,     5,     5,     5,     7,     7,   197,
       7,     5,     5,   204,    17,    18,   243,    20,    21,   246,
     173,   173,   173,     5,   173,   173,   204,   173,     7,   173,
     204,   173,   173,   173,   173,   173,   173,   173,   173,   173,
     173,   173,   173,   173,   173,   193,   173,   173,   173,    18,
     139,   503,   140,   141,   142,   143,   144,   176,   510,   173,
     173,   173,     5,   193,   217,   536,   527,   235,    24,   252,
     253,   254,    34,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    51,    52,    53,    54,    55,
     208,   264,   265,   266,   269,   271,   273,   275,   276,   278,
     279,   280,   281,   282,   283,   284,   285,   287,   289,   291,
     293,   294,   264,     7,   260,   261,   262,     7,   330,   331,
     332,     7,   368,   369,   370,     7,   392,   393,   394,     7,
     358,   359,   360,   101,   102,   103,   104,   106,   297,   298,
     299,   300,   301,   302,   303,     7,   464,   465,     7,   426,
     427,   428,     7,   306,   307,   308,   114,   115,   116,   117,
     118,   119,   320,   321,   322,   323,   324,   325,   326,   327,
     122,   123,   208,   420,   422,   477,   478,   479,   481,   489,
       7,   540,   541,   205,     7,   410,   411,   412,   109,   441,
     443,   461,   260,     8,     8,     8,     8,   255,     3,     8,
     267,   270,   272,   274,     4,     4,     4,     4,     4,   286,
     288,   290,   292,     4,     4,     4,     4,     4,     3,     8,
       8,   263,     6,     3,   333,     6,     3,   371,     6,     3,
     395,     6,     3,   361,     6,     3,     3,     6,   466,     3,
       6,   429,     6,     3,   309,     6,     3,     4,     4,     4,
       4,     4,     4,     3,     8,   480,   482,     3,     8,     8,
     542,     3,     6,   173,   206,   207,   413,     6,     3,   444,
       8,     6,     4,   253,     4,     4,     4,     4,   174,   176,
     174,   176,   174,     4,     4,     4,     4,   174,   174,   174,
     174,   176,   265,   264,   262,   336,   332,   374,   370,   398,
     394,   208,   219,   220,   221,   222,   223,   224,   225,   226,
     231,   232,   276,   328,   346,   348,   350,   352,   362,   363,
     390,   420,   422,   435,   437,   439,   459,   360,   298,    97,
      98,   208,   276,   364,   390,   420,   422,   435,   437,   439,
     467,   468,   469,   470,   471,   473,   465,   432,   428,   312,
     308,   174,   174,   174,   174,   174,   174,   321,     4,     4,
     478,   149,   151,   152,   208,   276,   420,   422,   543,   544,
     545,   546,   548,   541,     6,     3,   416,   412,     4,   173,
      35,    36,    37,    38,   268,   173,   173,   173,   173,   173,
     173,   173,     8,     8,     8,     8,     3,     8,   472,     4,
       8,     3,     8,     8,   173,   173,   549,     4,   547,     3,
       8,   173,     8,   204,   363,     4,   176,   469,     4,   174,
       4,   544,   173,     5,   173,     7,   550,   551,   552,     3,
       6,   150,   153,   154,   155,   553,   554,   555,   557,   558,
     559,   551,   556,     4,     4,     4,     3,     8,     4,   176,
     174,   174,   554,   173
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
     218,   218,   218,   218,   219,   220,   221,   222,   223,   224,
     225,   226,   227,   229,   228,   230,   231,   232,   234,   233,
     235,   235,   236,   236,   236,   236,   236,   236,   236,   238,
     237,   240,   239,   242,   241,   243,   243,   245,   244,   246,
     246,   247,   249,   248,   251,   250,   252,   252,   253,   255,
     254,   257,   256,   259,   258,   260,   260,   261,   261,   263,
     262,   264,   264,   265,   265,   265,   265,   265,   265,   265,
     265,   265,   265,   265,   265,   265,   265,   265,   265,   265,
     265,   265,   265,   267,   266,   268,   268,   268,   268,   270,
     269,   272,   271,   274,   273,   275,   277,   276,   278,   279,
     280,   281,   282,   283,   284,   286,   285,   288,   287,   290,
     289,   292,   291,   293,   294,   296,   295,   297,   297,   298,
     298,   298,   298,   298,   299,   300,   301,   302,   303,   305,
     304,   306,   306,   307,   307,   309,   308,   311,   310,   312,
     312,   312,   313,   313,   315,   314,   317,   316,   319,   318,
     320,   320,   321,   321,   321,   321,   321,   321,   322,   323,
     324,   325,   326,   327,   329,   328,   330,   330,   331,   331,
     333,   332,   335,   334,   336,   336,   337,   337,   337,   337,
     337,   337,   337,   337,   337,   337,   337,   337,   337,   337,
     337,   337,   337,   337,   337,   337,   337,   337,   337,   337,
     337,   337,   337,   337,   337,   339,   338,   341,   340,   343,
     342,   345,   344,   347,   346,   349,   348,   351,   350,   353,
     352,   354,   354,   354,   354,   355,   357,   356,   358,   358,
     359,   359,   361,   360,   362,   362,   363,   363,   363,   363,
     363,   363,   363,   363,   363,   363,   363,   363,   363,   363,
     363,   363,   363,   363,   363,   363,   363,   363,   363,   363,
     365,   364,   367,   366,   368,   368,   369,   369,   371,   370,
     373,   372,   374,   374,   375,   375,   376,   376,   376,   376,
     376,   376,   376,   376,   376,   376,   377,   378,   379,   381,
     380,   383,   382,   385,   384,   386,   388,   387,   389,   391,
     390,   392,   392,   393,   393,   395,   394,   397,   396,   398,
     398,   399,   399,   400,   400,   400,   400,   400,   400,   400,
     400,   400,   401,   403,   402,   404,   405,   406,   407,   409,
     408,   410,   410,   411,   411,   413,   412,   415,   414,   416,
     416,   417,   417,   417,   417,   417,   417,   417,   419,   418,
     421,   420,   423,   422,   425,   424,   426,   426,   427,   427,
     429,   428,   431,   430,   432,   432,   433,   433,   434,   434,
     434,   434,   434,   434,   434,   434,   434,   434,   434,   434,
     434,   434,   434,   436,   435,   438,   437,   440,   439,   442,
     441,   444,   443,   446,   445,   448,   447,   450,   449,   452,
     451,   454,   453,   456,   455,   458,   457,   460,   459,   461,
     461,   463,   462,   464,   464,   466,   465,   467,   467,   468,
     468,   469,   469,   469,   469,   469,   469,   469,   469,   469,
     469,   469,   470,   472,   471,   473,   474,   476,   475,   477,
     477,   478,   478,   478,   478,   478,   480,   479,   482,   481,
     484,   483,   486,   485,   488,   487,   489,   489,   490,   490,
     490,   490,   490,   490,   490,   490,   490,   490,   490,   490,
     490,   490,   490,   490,   490,   490,   491,   493,   492,   495,
     494,   496,   498,   497,   499,   500,   502,   501,   503,   503,
     505,   504,   506,   507,   509,   508,   510,   510,   510,   510,
     510,   512,   511,   514,   513,   516,   515,   518,   517,   520,
     519,   522,   521,   524,   523,   526,   525,   527,   527,   528,
     528,   530,   529,   531,   533,   532,   535,   534,   536,   536,
     537,   539,   538,   540,   540,   542,   541,   543,   543,   544,
     544,   544,   544,   544,   544,   544,   545,   547,   546,   549,
     548,   550,   550,   552,   551,   553,   553,   554,   554,   554,
     554,   556,   555,   557,   558,   559
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
       1,     1,     1,     1,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     0,     4,     3,     3,     3,     0,     6,
       1,     3,     1,     1,     1,     1,     1,     1,     1,     0,
       4,     0,     4,     0,     4,     1,     1,     0,     4,     1,
       1,     3,     0,     6,     0,     6,     1,     3,     1,     0,
       4,     0,     6,     0,     6,     0,     1,     1,     3,     0,
       4,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     0,     4,     1,     1,     1,     1,     0,
       4,     0,     4,     0,     4,     3,     0,     4,     3,     3,
       3,     3,     3,     3,     3,     0,     4,     0,     4,     0,
       4,     0,     4,     3,     3,     0,     6,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     0,
       6,     0,     1,     1,     3,     0,     4,     0,     4,     1,
       3,     1,     1,     1,     0,     4,     0,     4,     0,     6,
       1,     3,     1,     1,     1,     1,     1,     1,     3,     3,
       3,     3,     3,     3,     0,     6,     0,     1,     1,     3,
       0,     4,     0,     4,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     1,     1,     1,     1,     3,     0,     6,     0,     1,
       1,     3,     0,     4,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       0,     6,     0,     4,     0,     1,     1,     3,     0,     4,
       0,     4,     0,     1,     1,     3,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     3,     1,     0,
       4,     0,     4,     0,     4,     1,     0,     4,     3,     0,
       6,     0,     1,     1,     3,     0,     4,     0,     4,     0,
       1,     1,     3,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     0,     4,     1,     1,     3,     3,     0,
       6,     0,     1,     1,     3,     0,     4,     0,     4,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     0,     4,
       0,     4,     0,     4,     0,     6,     0,     1,     1,     3,
       0,     4,     0,     4,     0,     1,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     4,     0,     4,     0,     6,     1,
       1,     0,     6,     1,     3,     0,     4,     0,     1,     1,
       3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     0,     4,     3,     3,     0,     6,     1,
       3,     1,     1,     1,     1,     1,     0,     4,     0,     4,
       0,     4,     0,     6,     0,     4,     1,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
       1,     1,     1,     1,     1,     1,     3,     0,     4,     0,
       4,     3,     0,     4,     3,     3,     0,     4,     1,     1,
       0,     4,     3,     3,     0,     4,     1,     1,     1,     1,
       1,     0,     4,     0,     4,     0,     4,     0,     4,     0,
       4,     0,     4,     0,     6,     0,     4,     1,     3,     1,
       1,     0,     6,     3,     0,     6,     0,     4,     1,     3,
       1,     0,     6,     1,     3,     0,     4,     1,     3,     1,
       1,     1,     1,     1,     1,     1,     3,     0,     4,     0,
       6,     1,     3,     0,     4,     1,     3,     1,     1,     1,
       1,     0,     4,     3,     3,     3
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
     481,   482,   483,   484,   487,   492,   497,   502,   507,   512,
     517,   522,   527,   532,   532,   540,   545,   550,   556,   556,
     567,   568,   571,   572,   573,   574,   575,   576,   577,   580,
     580,   589,   589,   599,   599,   606,   607,   610,   610,   617,
     619,   623,   629,   629,   641,   641,   651,   652,   654,   656,
     656,   674,   674,   686,   686,   696,   697,   700,   701,   704,
     704,   714,   715,   718,   719,   720,   721,   722,   723,   724,
     725,   726,   727,   728,   729,   730,   731,   732,   733,   734,
     735,   736,   737,   740,   740,   747,   748,   749,   750,   753,
     753,   761,   761,   769,   769,   777,   782,   782,   790,   795,
     800,   805,   810,   815,   820,   825,   825,   833,   833,   841,
     841,   849,   849,   857,   862,   867,   867,   877,   878,   881,
     882,   883,   884,   885,   888,   893,   898,   903,   908,   913,
     913,   923,   924,   927,   928,   931,   931,   941,   941,   951,
     952,   953,   956,   957,   960,   960,   968,   968,   976,   976,
     987,   988,   991,   992,   993,   994,   995,   996,   999,  1004,
    1009,  1014,  1019,  1024,  1032,  1032,  1045,  1046,  1049,  1050,
    1057,  1057,  1083,  1083,  1094,  1095,  1099,  1100,  1101,  1102,
    1103,  1104,  1105,  1106,  1107,  1108,  1109,  1110,  1111,  1112,
    1113,  1114,  1115,  1116,  1117,  1118,  1119,  1120,  1121,  1122,
    1123,  1124,  1125,  1126,  1127,  1130,  1130,  1138,  1138,  1146,
    1146,  1154,  1154,  1162,  1162,  1170,  1170,  1178,  1178,  1188,
    1188,  1195,  1196,  1197,  1198,  1201,  1208,  1208,  1219,  1220,
    1224,  1225,  1228,  1228,  1236,  1237,  1240,  1241,  1242,  1243,
    1244,  1245,  1246,  1247,  1248,  1249,  1250,  1251,  1252,  1253,
    1254,  1255,  1256,  1257,  1258,  1259,  1260,  1261,  1262,  1263,
    1270,  1270,  1283,  1283,  1292,  1293,  1296,  1297,  1302,  1302,
    1317,  1317,  1331,  1332,  1335,  1336,  1339,  1340,  1341,  1342,
    1343,  1344,  1345,  1346,  1347,  1348,  1351,  1353,  1358,  1360,
    1360,  1368,  1368,  1376,  1376,  1384,  1386,  1386,  1394,  1403,
    1403,  1415,  1416,  1421,  1422,  1427,  1427,  1439,  1439,  1451,
    1452,  1457,  1458,  1463,  1464,  1465,  1466,  1467,  1468,  1469,
    1470,  1471,  1474,  1476,  1476,  1484,  1486,  1488,  1493,  1501,
    1501,  1513,  1514,  1517,  1518,  1521,  1521,  1531,  1531,  1541,
    1542,  1545,  1546,  1547,  1548,  1549,  1550,  1551,  1554,  1554,
    1562,  1562,  1587,  1587,  1617,  1617,  1627,  1628,  1631,  1632,
    1635,  1635,  1644,  1644,  1653,  1654,  1657,  1658,  1662,  1663,
    1664,  1665,  1666,  1667,  1668,  1669,  1670,  1671,  1672,  1673,
    1674,  1675,  1676,  1679,  1679,  1687,  1687,  1695,  1695,  1703,
    1703,  1711,  1711,  1721,  1721,  1729,  1729,  1737,  1737,  1745,
    1745,  1753,  1753,  1761,  1761,  1769,  1769,  1782,  1782,  1792,
    1793,  1799,  1799,  1809,  1810,  1813,  1813,  1823,  1824,  1827,
    1828,  1831,  1832,  1833,  1834,  1835,  1836,  1837,  1838,  1839,
    1840,  1841,  1844,  1846,  1846,  1854,  1863,  1870,  1870,  1880,
    1881,  1884,  1885,  1886,  1887,  1888,  1891,  1891,  1899,  1899,
    1910,  1910,  1948,  1948,  1960,  1960,  1970,  1971,  1974,  1975,
    1976,  1977,  1978,  1979,  1980,  1981,  1982,  1983,  1984,  1985,
    1986,  1987,  1988,  1989,  1990,  1991,  1994,  1999,  1999,  2007,
    2007,  2015,  2020,  2020,  2028,  2033,  2038,  2038,  2046,  2047,
    2050,  2050,  2058,  2063,  2068,  2068,  2076,  2079,  2082,  2085,
    2088,  2094,  2094,  2102,  2102,  2110,  2110,  2121,  2121,  2128,
    2128,  2135,  2135,  2142,  2142,  2153,  2153,  2163,  2164,  2168,
    2169,  2172,  2172,  2182,  2192,  2192,  2202,  2202,  2213,  2214,
    2218,  2222,  2222,  2234,  2235,  2239,  2239,  2247,  2248,  2251,
    2252,  2253,  2254,  2255,  2256,  2257,  2260,  2265,  2265,  2273,
    2273,  2283,  2284,  2287,  2287,  2295,  2296,  2299,  2300,  2301,
    2302,  2305,  2305,  2313,  2318,  2323
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

#line 2328 "dhcp4_parser.yy"


void
isc::dhcp::Dhcp4Parser::error(const location_type& loc,
                              const std::string& what)
{
    ctx.error(loc, what);
}
